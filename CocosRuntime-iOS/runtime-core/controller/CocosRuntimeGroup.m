//
//  CocosRuntimeGroup.m
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "CocosRuntimeGroup.h"
#import "FileDownloader.h"
#import "FileUtil.h"
#import "ZipHelper.h"
#import "CocosRuntime.h"
#import "LoadingProgressController.h"
#import "GroupVersionManager.h"
#import "CocosRuntimeGroupPatch.h"
#import "RTNetworkHelper.h"

static GameInfo *gameInfo = nil;
static GameConfig *gameConfig = nil;
static GameManifest *gameManifest = nil;
static NSMutableArray *resGroups = nil;
static NSMutableDictionary *resGroupDict = nil;

/* 当前正在下载的组名 */
static NSString *currentDownloadName = nil;

/* 当前正在下载的组 */
static ResGroup *currentDownloadGroup = nil;

/* 之前的预加载组名 */
static NSString *prevPreloadGroupName = @"";

/* 等待的下载队列，元素是组名 */
static NSMutableArray *waitingDownloadGroups = nil;

/* 当前静默下载的组在所有组中的索引 */
static int currentDownloadIndex = 0;

/* 静默下载是否开启 */
static BOOL silentDownloadEnabled = FALSE;

/* 是否有正在下载的组 */
static BOOL isGroupDownloading = FALSE;

/* 是否处于静默下载状态 */
static BOOL isInSilentDownloadState = FALSE;

/* 当前的文件下载器*/
static FileDownloader *currentFileDownloader = nil;

/* 是否处于取消下载的状态 */
static BOOL isInCancelDownloadState = FALSE;

/**/
static id<LoadingDelegate> loadingDelegate = nil;

/**/
static LoadingProgressController *loadingController = nil;

static GroupVersionManager *groupVersionManager = nil;

static CocosRuntimeGroupPatch *cocosRuntimeGroupPatch;

static RTNetworkHelper *networkHelper = nil;

@implementation CocosRuntimeGroup
+ (void) initialize: (GameInfo*) info config: (GameConfig*) config manifest: (GameManifest*) manifest
{
    NSLog(@"CocosRuntimeGroup initialize");
    waitingDownloadGroups = [NSMutableArray arrayWithCapacity:20];
    gameInfo = info;
    gameConfig = config;
    gameManifest = manifest;
    resGroups = [manifest allResGroups];
    resGroupDict = [CocosRuntimeGroup getAllResGroupDict:resGroups];
    loadingController = [[LoadingProgressController alloc] initWith:[[OnLoadingProgressDelegateImpl alloc] init]];
    groupVersionManager = [[GroupVersionManager alloc] initWith:[FileUtil getGameRootPath:gameInfo]];
    cocosRuntimeGroupPatch = [[CocosRuntimeGroupPatch alloc] init];
    [CocosRuntimeGroup initNetworkHelper];
}

+ (GroupVersionManager*) getGroupVersionManager
{
    return groupVersionManager;
}

+ (void) initNetworkHelper
{
    networkHelper = [[RTNetworkHelper alloc] init];
    [networkHelper setListener:^(RTNetworkType networkType) {
        switch (networkType) {
            case NetworkType_WiFi:
                [CocosRuntimeGroup setSilentDownloadEnabled:TRUE];
                if (FALSE == isGroupDownloading) {
                    [CocosRuntimeGroup silentDownloadNextGroup];
                }
                break;
            
            case NetworkType_Mobile:
                [CocosRuntimeGroup setSilentDownloadEnabled:FALSE];
                break;
                
            case NetworkType_NotReachable:
                [CocosRuntimeGroup setSilentDownloadEnabled:FALSE];
                break;
                
            default:
                break;
        }
    }];
}

+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate
{
    NSLog(@"CocosRuntimeGroup initialize: %@", groupsString);

    loadingDelegate = delegate;

    if (![CocosRuntimeGroup needToDownloadGroup:groupsString]) {
        [delegate onLoadingCompleted];
        return;
    }
    
    [CocosRuntimeGroup setInSilentDownloadState:FALSE];
    
    if (currentDownloadGroup == nil || ![waitingDownloadGroups containsObject:currentDownloadGroup.groupName]) {
        isInCancelDownloadState = TRUE;
        isGroupDownloading = FALSE;
        [CocosRuntimeGroup cancelCurrentDownload];
        // todo 取消之后的监听，解压之类的
        // Since we will cancel current download, the current download needs to be started again.
        // Therefore, decrease the index to make getNextResGroupForDownload happy.
        [CocosRuntimeGroup decreaseIndexOfSilentDownload];
        isInCancelDownloadState = FALSE;
        [CocosRuntimeGroup startDownloadGroups];
    }
    
    NSLog(@"===> preload resource groups: %@", groupsString);
    [CocosRuntimeGroup startDownloadGroups];
}

+ (void) reset
{
    [CocosRuntimeGroup setInSilentDownloadState:FALSE];
    waitingDownloadGroups = [NSMutableArray arrayWithCapacity:20];
    currentDownloadIndex = 0;
    currentFileDownloader = nil;
    prevPreloadGroupName = @"";
    [CocosRuntimeGroup cancelCurrentDownload];
    loadingController = nil;
    [CocosRuntimeGroup clearDownloadState];
}

+ (void) clearDownloadState
{
    currentDownloadGroup = nil;
    isGroupDownloading = FALSE;
}

+ (void) updateGroup: (NSString*)groupName delegate: (id<OnGroupUpdateDelegate>) delegate
{
    ResGroup *resGroup = [CocosRuntimeGroup findGroupByName:groupName];
    if (resGroup == nil) {
        NSLog(@"===> Can't find (%@) section in 'res_groups' of 'manifest.json'", groupName);
        return;
    }

    if ([resGroup isUpdated:gameInfo]) {
        NSLog(@"===> (%@) was updated, don't need to update it again!", groupName);
        // 如果检测到资源分组已经是最新的，则通知分组下载完毕和解压完毕
        [groupVersionManager setGroupVersionCode:groupName versionCode:[gameConfig versionCode]];
        [delegate onSuccessOfDownload:resGroup.groupSize];
        [delegate onSuccessOfUnzip:resGroup.groupSize];
        
    } else {
        // Whether the patch which version is correct was included by the group.
        // Fetch the patch from remote server
        // According to patch's MD5. Checking the patch is correct.
        // Using these patch.
        
        NSInteger versionCode = [groupVersionManager getVersionCode:groupName];
        NSString *versionString = [NSString stringWithFormat: @"%ld", (long)versionCode];
        GroupPatch *patch = [cocosRuntimeGroupPatch findPatch:groupName versionCode: versionString];
        
        if (patch == nil) {
            NSString *groupPath = [FileUtil getLocalGroupPath:gameInfo group:resGroup];
            if ([FileUtil fileExists:groupPath]) {
                if ([[resGroup groupMD5] isEqualToString:[FileUtil getFileMD5:groupPath]]) {
                    NSLog(@"===> The group (%@) exists, unzip it ...", [resGroup groupURL]);
                    [delegate onSuccessOfDownload:[resGroup groupSize]];
                    [CocosRuntimeGroup unzipGroup:resGroup delegate:delegate];
                } else {
                    [FileUtil removeFile:groupPath];
                }
            }
            
            [CocosRuntimeGroup deleteGroup:groupName];
            
            [CocosRuntimeGroup downloadResGroup:gameInfo group:resGroup delegate:delegate];
        } else {
            NSString *patchPath = [FileUtil getGroupPatchPackagePath:gameInfo groupName:groupName version:versionString];
            if ([FileUtil fileExists:patchPath]) {
                if ([cocosRuntimeGroupPatch isPatchPackageMD5Correct:groupName version:versionString path:patchPath]) {
                    [delegate onSuccessOfDownload:[patch patchSize]];
                    [cocosRuntimeGroupPatch unzipPatch:groupName version:versionString delegate:delegate];
                    return;
                } else {
                    [FileUtil removeFile:patchPath];
                }
            }
            
            [cocosRuntimeGroupPatch updatePatch:[patch patchURL] groupName:groupName version:versionString delegate:delegate];
        }
    }
}

+ (GameConfig*) getGameConfig
{
    return gameConfig;
}

+ (void) unzipGroup: (ResGroup*)group delegate:(id<OnGroupUpdateDelegate>)delegate
{
    NSString *groupPath = [FileUtil getLocalGroupPath:gameInfo group: group];
    
    [ZipHelper unzipFileAtPath:groupPath
            toDestination:[FileUtil getGameRootPath:gameInfo]
            progressHandler:^(NSString *entry, long entryNumber, long total) {
                NSLog(@"!!!! Unzip onProgress: %ld/%ld", entryNumber, total);
                [delegate onProgressOfUnzip:entryNumber total:total];
            }
            completionHandler:^(NSString *zipFilePath, BOOL succeeded, NSError *error) {
                if (error == nil) {
                    NSLog(@"===> unzip (%@) success", [group groupURL]);
                    [groupVersionManager setGroupVersionCode:group.groupName versionCode:[gameConfig versionCode]];
                    [FileUtil removeFile:groupPath];
                    [delegate onSuccessOfUnzip:group.groupSize];
                } else {
                    // fixme: 不要写死
                    [delegate onFailureOfUnzip:@"解压错误"];
                    NSLog(@"===> unzip error");
                }
            }
     ];
}

+ (void) prepareWaitingDownloadGroups: (NSString*) groupsString
{
    NSArray *groupsNameArray = [groupsString componentsSeparatedByString:@":"];
    NSLog(@"===> prepareWaitingDownloadGroups:%@", groupsNameArray);
    
    currentDownloadName = [groupsNameArray objectAtIndex:0];
    long totalSize = -1;
    for (NSString *groupName in groupsNameArray) {
        if ([self isGroupUpdated:groupName]) {
            continue;
        }
        
        if ([waitingDownloadGroups containsObject:groupName]) {
            continue;
        }
        
        [waitingDownloadGroups addObject:groupName];
        
        ResGroup *resGroup = [CocosRuntimeGroup findGroupByName:groupName];
        if (resGroup != nil) {
            totalSize += resGroup.groupSize;
        }
    }
    
    // if downloading group is in the waiting download list, complete the download process first
    if (currentDownloadGroup != nil && [waitingDownloadGroups containsObject:currentDownloadGroup.groupName]) {
        [CocosRuntimeGroup removeGroupFromWaitingDownload: currentDownloadGroup.groupName];
        [waitingDownloadGroups insertObject:currentDownloadGroup.groupName atIndex:0];
    }
    
    // 将此次等待下载的进度进行保存
    if (waitingDownloadGroups.count != 0) {
        NSMutableArray *loadingInfos = [NSMutableArray arrayWithCapacity:10];
        for (NSString *groupName in waitingDownloadGroups) {
            ResGroup *resGroup = [CocosRuntimeGroup findGroupByName:groupName];
            if (resGroup != nil) {
                // 先计算每一个分组占所有待下载分组的百分比，而每一个分组中，下载占80%，解压占20%
                float percent = (float)(resGroup.groupSize / totalSize) * 100;
                
                LoadingInfo* downloadInfo = [[LoadingInfo alloc] initWith:[GROUP_DOWNLOAD stringByAppendingString: groupName] percent:(NSInteger)(percent * 0.8) type:PROGRESS tip:resGroup.groupName];
                LoadingInfo* unzipInfo = [[LoadingInfo alloc] initWith:[GROUP_UNZIP stringByAppendingString: groupName] percent:(NSInteger)(percent * 0.2) type:PROGRESS tip:resGroup.groupName];
                [loadingInfos addObject: downloadInfo];
                [loadingInfos addObject: unzipInfo];
            }
        }
        [[CocosRuntime getLoadingProgressController] setLoadingInfoList:loadingInfos];
    }
    
}

+ (id<LoadingDelegate>) getLoadingDelegate
{
    return loadingDelegate;
}

+ (BOOL) needToDownloadGroup: (NSString*)groupString
{
    [CocosRuntimeGroup prepareWaitingDownloadGroups:groupString];
    if (waitingDownloadGroups.count == 0) {
        NSLog(@"%@ were downloaded, no need to download again!", groupString);
        return FALSE;
    }
    return TRUE;
}

+ (NSMutableDictionary*) getAllResGroupDict: (NSMutableArray*) resGroupArray
{
    resGroupDict = [NSMutableDictionary dictionaryWithCapacity:20];
    for (ResGroup *resGroup in resGroupArray) {
        [resGroupDict setObject:resGroup forKey:resGroup.groupName];
    }
    return resGroupDict;
}

+ (BOOL) isGroupUpdated: (NSString*) name
{
    ResGroup *group = [CocosRuntimeGroup findGroupByName:name];
    return group == nil ? FALSE : [group isUpdated:gameInfo];
}

+ (ResGroup*) findGroupByName: (NSString*) name
{
    return [resGroupDict objectForKey:name];
}

+ (BOOL) isGroupMD5Correct: (NSString*) md5 path: (NSString*) path
{
    NSString* fileMD5 = [FileUtil getFileMD5:path];
    if ([fileMD5 isEqualToString:fileMD5]) {
        return true;
    }
    return false;
}

+ (bool) isDownloadIndexValid: (NSInteger)index
{
    if (index >= 0 && index < resGroups.count) {
        return true;
    }
    return false;
}

+ (ResGroup*) getResGroupByIndex: (NSInteger)index
{
    return [resGroups objectAtIndex:index];
}

+ (void) removeGroupFromWaitingDownload: (NSString*)groupName
{
    if (waitingDownloadGroups.count == 0) {
        return;
    }
    
    for (NSInteger i = waitingDownloadGroups.count - 1; i >= 0; i--) {
        if ([[waitingDownloadGroups objectAtIndex:i] isEqualToString:groupName]) {
            [waitingDownloadGroups removeObjectAtIndex: i];
        }
    }
}

+ (NSString*) getCurrentGroupNameFromWaitingGroups
{
    if (waitingDownloadGroups == nil || waitingDownloadGroups.count == 0) {
        return nil;
    } else {
        return waitingDownloadGroups.firstObject;
    }
}

+ (BOOL) isInCancelDownloadState
{
    return isInCancelDownloadState;
}

+ (NSString*) getFirstGroupFromWaitingDownload
{
    if (waitingDownloadGroups != nil) {
        return [waitingDownloadGroups objectAtIndex:0];
    }
    return nil;
}

+ (void) removeFirstGroupFromWaitingDownload
{
    if (waitingDownloadGroups != nil && waitingDownloadGroups.count != 0) {
        [waitingDownloadGroups removeObjectAtIndex:0];
    }
}

+ (void) downloadResGroup: (GameInfo*) gameInfo group: (ResGroup*) resGroup delegate: (id<OnGroupUpdateDelegate>) delegate
{
    if (resGroup == nil) {
        NSLog(@"resGroup is null in startDownload!");
        return;
    }
    
    NSString *groupName = resGroup.groupName;
    if (isGroupDownloading) {
        NSLog(@"Oops, previous group: %@ , current group: %@", prevPreloadGroupName, groupName);
        return;
    }
    
    currentDownloadGroup = resGroup;
    isGroupDownloading = TRUE;
    prevPreloadGroupName = groupName;
    
    [loadingController setCurrentLoadingIndexByName:[GROUP_DOWNLOAD stringByAppendingString:[resGroup groupName]]];
    
    // 如果是 Boot 分组，由于其中包含了所有的JS脚本，为了兼容JS编译版本的改变，Boot分组必须累加一个新版本兼容目录，从这个目录下下载
    NSURL *requestUrl = nil;
    if ([@"boot" isEqualToString:groupName]) {
        requestUrl = [[NSURL alloc]initWithString:[[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH] stringByAppendingPathComponent:resGroup.groupURL]];
    } else {
        requestUrl = [[NSURL alloc]initWithString:[[gameInfo downloadUrl] stringByAppendingPathComponent:resGroup.groupURL]];
    }
    
    
    ResourceGroupDownloadImpl* resDownloadImpl =  [[ResourceGroupDownloadImpl alloc] initWith:resGroup groupDelegate:delegate];
    currentFileDownloader = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getLocalGroupPath:gameInfo group: resGroup] delegate:resDownloadImpl];
    [currentFileDownloader start];
}

+ (void) startDownloadGroups
{
    if (waitingDownloadGroups.count == 0) {
        NSLog(@"waiting download groups is empty now, download done!");
        [loadingController notifyAllLoadingFinish];
        return;
    }
    currentDownloadName = [CocosRuntimeGroup getFirstGroupFromWaitingDownload];
    ResGroup* resGroup = [CocosRuntimeGroup findGroupByName:currentDownloadName];
    
    [loadingController setCurrentLoadingIndexByName:[GROUP_DOWNLOAD stringByAppendingString:currentDownloadName]];
    
    OnGroupUpdateDelegateImpl* groupUpdateDelegate = [[OnGroupUpdateDelegateImpl alloc]initWith:resGroup];
    [CocosRuntimeGroup updateGroup:currentDownloadName delegate:groupUpdateDelegate];
}

+ (void) cancelCurrentDownload
{
    // todo 添加取消通知
    currentDownloadName = nil;
    if (currentFileDownloader != nil) {
        [currentFileDownloader cancel];
        currentFileDownloader = nil;
    }
    
    isInCancelDownloadState = FALSE;
}

+ (void) deleteGroup: (NSString*)groupName
{
    [groupVersionManager deleteGroupVersionCode:groupName];
    NSString *groupJsonFilePath = [FileUtil getGroupJsonFilePath:gameInfo groupName:groupName];
    if (![FileUtil fileExists:groupJsonFilePath]) {
        return;
    }
    
    NSDictionary *dict = (NSDictionary*)[FileUtil readJsonFromFile:groupJsonFilePath];
    if (dict == nil) {
        return;
    }
    
    NSArray *files = [dict objectForKey:@"files"];
    if (files != nil) {
        for (NSDictionary *file in files) {
            NSString *path = [[FileUtil getGameRootPath:gameInfo] stringByAppendingPathComponent:[file objectForKey:@"name"]];
            if ([FileUtil fileExists:path]) {
                [FileUtil removeFile:path];
            }
        }
    }
    
    [FileUtil removeFile:groupJsonFilePath];
}

/************************************ SilentDownload ********************************/

+ (BOOL) isSilentDownloadEnabled
{
    return silentDownloadEnabled;
}

+ (void) setSilentDownloadEnabled: (BOOL)isEnabled
{
    silentDownloadEnabled = isEnabled;
}

+ (int) increaseIndexOfSilentDownload
{
    ++currentDownloadIndex;
    NSLog(@"increase current download index: %d", currentDownloadIndex);
    return currentDownloadIndex;
}

+ (int) decreaseIndexOfSilentDownload
{
    --currentDownloadIndex;
    NSLog(@"decrease current download index: %d", currentDownloadIndex);
    return currentDownloadIndex;
}

+ (ResGroup*) getNextResGroupForDownload
{
    ResGroup* resGroup = nil;
    int nextDownloadIndex = [CocosRuntimeGroup increaseIndexOfSilentDownload];
    if ([CocosRuntimeGroup isDownloadIndexValid:nextDownloadIndex]) {
        resGroup = [CocosRuntimeGroup getResGroupByIndex:nextDownloadIndex];
    } else {
        NSLog(@"All group resources are downloaded, no need to download! Index = %d", nextDownloadIndex);
    }
    return resGroup;
}

+ (void) setInSilentDownloadState: (BOOL)inSilentDownload
{
    isInSilentDownloadState = inSilentDownload;
    if (isInSilentDownloadState) {
        // todo 设置解压线程等级为低
    } else {
        // todo 设置解压线程等级为正常
    }
}

+ (BOOL) isInSilentDownloadState
{
    return isInSilentDownloadState;
}

+ (void) silentDownloadNextGroup
{
    if (!silentDownloadEnabled) {
        return;
    }
    
    if (isGroupDownloading) {
        NSLog(@"group (%@) is downloading, don't start silent download! ", prevPreloadGroupName);
        return;
    }
    
    ResGroup *resGroup = [CocosRuntimeGroup getNextResGroupForDownload];
    if (resGroup == nil) {
        return;
    }
    
    NSLog(@"onSilentDownloadNextGroup (%@)", resGroup.groupName);
    [CocosRuntimeGroup prepareWaitingDownloadGroups:resGroup.groupName];
    if (waitingDownloadGroups.count == 0) {
        // todo 判断游戏是否已经关闭
        [CocosRuntimeGroup silentDownloadNextGroup];
    } else {
        [CocosRuntimeGroup setInSilentDownloadState:TRUE];
        [CocosRuntimeGroup startDownloadGroups];
    }
}
@end

@implementation ResourceGroupDownloadImpl

- (ResourceGroupDownloadImpl*) initWith:(ResGroup *)group groupDelegate: (id<OnGroupUpdateDelegate>)delegate
{
    if (self = [super init]) {
        resGroup = group;
        onGroupUpdateDelegate = delegate;
    }
    return self;
}

- (void) onDownloadProgress:(long)progress max:(long)max
{
    [onGroupUpdateDelegate onProgressOfDownload:progress total:max];
}

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> GroupDownloadDelegateImpl Success");
    
    if (![resGroup.groupMD5 isEqualToString:[FileUtil getFileMD5:path]]) {
        // fixme: 不要写死
        [onGroupUpdateDelegate onFailureOfDownload:@"下载错误"];
        return;
    }

    [onGroupUpdateDelegate onSuccessOfDownload:resGroup.groupSize];
        
    NSLog(@"===> download %@", resGroup.groupURL);
    [CocosRuntimeGroup unzipGroup:resGroup delegate:onGroupUpdateDelegate];
}

- (void) onDownloadFailed
{
    NSLog(@"===> GroupDownloadDelegateImpl onDownloadFailed");
    [onGroupUpdateDelegate onFailureOfDownload:@"下载错误"];
}
@end

/****************************** 分组更新监听 ***************************/

@implementation OnGroupUpdateDelegateImpl

- (OnGroupUpdateDelegateImpl*) initWith:(ResGroup *)group
{
    if (self = [super init]) {
        resGroup = group;
    }
    return self;
}

- (void) onProgressOfDownload: (long) written total:(long) total
{
    float percent = [loadingController percentFromSingleToGlobal:(100.0f * written / resGroup.groupSize)];
    if (!isInSilentDownloadState) {
        [loadingDelegate onLoadingProgress:percent max:PROGRESS_MAX];
    }
}

- (void) onSuccessOfDownload: (long) total
{
    [loadingController setCurrentLoadingIndexByName:[GROUP_UNZIP stringByAppendingString:resGroup.groupName]];
}

- (void) onFailureOfDownload: (NSString*) errorMsg
{
    // 下载失败，如果是处于静默下载状态中，则继续重试静默下载, 否则向宿主反馈下载错误
    [CocosRuntimeGroup clearDownloadState];
    if ([CocosRuntimeGroup isSilentDownloadEnabled] && [CocosRuntimeGroup isInSilentDownloadState]) {
        [CocosRuntimeGroup decreaseIndexOfSilentDownload];
        [CocosRuntimeGroup silentDownloadNextGroup];
    } else {
        [[CocosRuntimeGroup getLoadingDelegate] onLoadingError];
    }
}

- (void) onSuccessOfUnzip: (long)total
{
    [CocosRuntimeGroup removeGroupFromWaitingDownload:resGroup.groupName];
    if (currentDownloadGroup != nil && ![currentDownloadGroup.groupName isEqualToString:resGroup.groupName]) {
        NSLog(@"Oops, some errors happened, current download group name: %@ downloaded group name: %@",currentDownloadGroup.groupName, resGroup.groupName);
        return;
    }
    
    if (currentDownloadGroup != nil) {
        [currentDownloadGroup setIsUpdated:TRUE];
    }
    
    [CocosRuntimeGroup clearDownloadState];
    
    // 如果还有其他分组需要下载，则先不进行静默下载
    // 如果没有待下载分组，则会直接返回，执行下方逻辑
    [CocosRuntimeGroup startDownloadGroups];
    
    if (waitingDownloadGroups.count == 0 && [CocosRuntimeGroup isSilentDownloadEnabled] && ![CocosRuntimeGroup isInCancelDownloadState]) {
        [CocosRuntimeGroup silentDownloadNextGroup];
    } else {
        NSLog(@"===> Don't silent download ..., isInCancelDownload: %d", [CocosRuntimeGroup isInCancelDownloadState]);
    }
}

- (void) onFailureOfUnzip: (NSString*) errorMsg
{
    // todo 填写错误类型
    [CocosRuntimeGroup clearDownloadState];
    if ([CocosRuntimeGroup isInSilentDownloadState]) {
        [CocosRuntimeGroup decreaseIndexOfSilentDownload];
        [CocosRuntimeGroup silentDownloadNextGroup];
    } else {
        NSLog(@"===> onFailureOfUnzip");
        [loadingDelegate onLoadingError];
    }
}

- (void) onProgressOfUnzip: (long) written total:(long) total
{
    // 如果是不是静默下载，则发送更新界面的通知
    if (![CocosRuntimeGroup isInSilentDownloadState]) {
        NSLog(@"===> onProgressOfUnzip: %f", ((float) (written) / total) * 100);
        NSInteger globalPercent = [loadingController percentFromSingleToGlobal:((float) (written) / total) * 100];
        [loadingDelegate onLoadingProgress:globalPercent max:100.0f];
    }
}
@end

@implementation OnLoadingProgressDelegateImpl

- (void) onUpdateOfLoadingInfo: (LoadingInfo*) currentLoadingInfo
{
    // 不是静默下载就回调通知给宿主
    if (![CocosRuntimeGroup isInSilentDownloadState] && loadingDelegate != nil) {
        NSLog(@"onUpdateOfLoadingInfo: %@", currentLoadingInfo);
        [loadingDelegate onLoadingProgress:[currentLoadingInfo startPercent] max:PROGRESS_MAX];
    }
}

- (void) onAllLoaingFinish
{
    // 不是静默下载就回调通知给宿主
    if (![CocosRuntimeGroup isInSilentDownloadState] && loadingDelegate != nil) {
        [loadingDelegate onLoadingCompleted];
    }
}

@end
