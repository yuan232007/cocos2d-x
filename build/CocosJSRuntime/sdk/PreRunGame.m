//
//  PreRunGame.m
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "PreRunGame.h"
#import "FileUtil.h"
#import "CocosRuntimeGroup.h"
#import "ZipHelper.h"
#import "NetworkController.h"
#import "RTNetworkHelper.h"

#define PROGRESS_MAX 100
#define PROGRESS_INVALID -1

static GameInfo* gameInfo = nil;
static GameManifest* gameManifest = nil;
static FileDownloader* fileDownload = nil;
static id<LoadingDelegate> loadingDelegate = nil;
static GameConfig* gameConfig = nil;

@implementation PreRunGame
+ (void) start: (NSString*) gameKey delegate:(id<LoadingDelegate>)delegate
{
    NSLog(@"===> PreRunGame start");
    loadingDelegate = delegate;
    [PreRunGame checkStatusBeforeRunGame: gameKey];
}

+ (void) reset
{
    
}

+ (void) checkStatusBeforeRunGame: (NSString*)gameKey
{
    NSLog(@"===> PreRunGame checkStatusBeforeRunGame: %@", gameKey);
    [NetworkController requestGameInfoByGameKey:gameKey callback:^(GameInfo *info, BOOL isFailed) {
        NSLog(@"===> PreRunGame checkStatusBeforeRunGame: GameInfo: %@", gameInfo);
        if (isFailed) {
            [loadingDelegate onLoadingError];
        } else {
            gameInfo = info;
            
            //************** for debug ************
            NSString *gameDownloadUrl = @"http://192.168.31.236:63342/4/";
            NSString *gameKey = @"Ryeeeeee";
            NSString *gameName = @"天天挂传奇";
            gameInfo = [[GameInfo alloc] initWithKey:gameKey withUrl:gameDownloadUrl withName:gameName];
            //**************************************
            [PreRunGame downloadRemoteConfigFile];
        }
    }];
}

+ (void) downloadRemoteConfigFile
{
    NSLog(@"===> LocalConfig %@", [FileUtil getLocalConfigPath:gameInfo]);
    NSLog(@"===> PreRunGame downloadRemoteConfigFile");
//    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:[FileUtil getConfigFileName]];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getRemoteConfigPath:gameInfo] delegate:[[ConfigDownloadDelegateImpl alloc] init]];
        NSLog(@"===> remote config file url: %@", requestString);
        [fileDownload start];
//    });
}

+ (void) updateLocalConfigFile: (NSString*) path
{
    NSLog(@"updateLocalConfigFile %@", path);
    [FileUtil moveFileFrom:path to:[FileUtil getLocalConfigPath:gameInfo] overwrite:true];
    [PreRunGame checkLocalManifestFile];
}

+ (void) checkLocalManifestFile
{
    NSLog(@"===> checkLocalManifestFile ");
    NSString *localManifestPath = [FileUtil getLocalManifestPath:gameInfo :gameConfig];
    if ([FileUtil fileExists:localManifestPath] && [PreRunGame isLocalManifestMD5Correct]) {
        gameManifest = [GameManifest readFromFile:localManifestPath];
        [CocosRuntimeGroup initialize:gameInfo config:gameConfig manifest:gameManifest];
        [PreRunGame checkEntryFile];
    } else {
        [PreRunGame downloadRemoteManifestFile];
    }
}

+ (void) downloadRemoteManifestFile
{
    NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:@"manifest.cpk"];
    NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
    FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getManifestCpkPath:gameInfo :gameConfig] delegate:[[ManifestDownloadDelegateImpl alloc] init]];
    [fileDownload start];
}

+ (GameConfig*) parseGameConfigFile: (NSString*) path
{
    return [GameConfig parseFromFile:path];
}

+ (void) checkEntryFile
{
    NSLog(@"===> checkEntryFile");
    if ([FileUtil fileExists:[FileUtil getLocalEntryPath:gameInfo :gameConfig]] && [PreRunGame isLocalEntryMD5Correct]) {
        [PreRunGame checkProjectJsonFile];
    } else {
        [PreRunGame downloadEntryFile];
    }
}

+ (void) downloadEntryFile
{
    NSLog(@"===> downloadEntryFile");
    NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:[gameConfig entryName]];
    NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
    FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getLocalEntryPath:gameInfo :gameConfig] delegate:[[EntryDownloadDelegateImpl alloc] init]];
    [fileDownload start];
}

+ (void) checkProjectJsonFile
{
    if ([FileUtil fileExists:[FileUtil getLocalProjectPath:gameInfo :gameConfig]] && [PreRunGame isLocalProjectMD5Correct]) {
        [PreRunGame checkBootGroup];
    } else {
        [PreRunGame downloadProjectJsonFile];
    }
}

+ (void) downloadProjectJsonFile
{
    NSString *requestString = [[gameInfo downloadUrl] stringByAppendingPathComponent:[gameConfig projectName]];
    NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
    FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getLocalProjectPath:gameInfo :gameConfig] delegate:[[ProjectDownloadDelegateImpl alloc] init]];
    [fileDownload start];
}

+ (void) deleteNoRefGroups
{
    NSLog(@"===> deleteNoRefGroups");
}

+ (void) checkBootGroup
{
    ResGroup *resGroup = [CocosRuntimeGroup findGroupByName:@"boot"];
    [CocosRuntimeGroup updateGroup:@"boot" delegate:[[OnBootGroupUpdateDelegateImpl alloc] initWith:resGroup]];
}

+ (void) notifyProgress: (float) progress max:(float)max
{
    NSLog(@"PreRunGame notifyProgress progress:%f max: %f", progress, max);
    if (loadingDelegate != nil) {
        [loadingDelegate onLoadingProgress:progress max:max];
    }
}

+ (void) notifyPreRunGameError
{
    if (loadingDelegate != nil) {
        [loadingDelegate onLoadingError];
    }
}

+ (void) startGame
{
    NSLog(@"===> start game.");
    if (loadingDelegate != nil) {
        [loadingDelegate onLoadingCompleted];
    }
    
    // 只有在 Wi-Fi 环境下才开启静默下载
    if (NetworkType_WiFi == [RTNetworkHelper getNetworkType]) {
        [CocosRuntimeGroup setSilentDownloadEnabled:TRUE];
    } else {
        [CocosRuntimeGroup setSilentDownloadEnabled:FALSE];
    }
    [CocosRuntimeGroup silentDownloadNextGroup];
}

+ (BOOL) isLocalConfigMD5Correct
{
    NSString *localConfigMD5 = [FileUtil getFileMD5: [FileUtil getLocalConfigPath:gameInfo]];
    NSString *remoteConfigMD5 = [FileUtil getFileMD5:[FileUtil getRemoteConfigPath:gameInfo]];
    if ([localConfigMD5 isEqualToString:remoteConfigMD5]) {
        return true;
    }
    return false;
}

+ (BOOL) isLocalManifestMD5Correct
{
    NSString *localManifestMD5 = [FileUtil getFileMD5:[FileUtil getLocalManifestPath:gameInfo :gameConfig]];
    if ([localManifestMD5 isEqualToString:[gameConfig manifestMD5]]) {
        return true;
    }
    return false;
}

+ (BOOL) isLocalProjectMD5Correct
{
    NSString *localProjectMD5 = [FileUtil getFileMD5:[FileUtil getLocalProjectPath:gameInfo :gameConfig]];
    if ([localProjectMD5 isEqualToString:[gameConfig projectMD5]]) {
        return true;
    }
    return false;
}

+ (BOOL) isLocalEntryMD5Correct
{
    NSLog(@"===> Entry md5:%@", [FileUtil getLocalEntryPath:gameInfo :gameConfig]);
    NSString *localEntryMD5 = [FileUtil getFileMD5:[FileUtil getLocalEntryPath:gameInfo :gameConfig]];
    if ([localEntryMD5 isEqualToString:[gameConfig entryMD5]]) {
        return true;
    }
    return false;
}

@end

@implementation ConfigDownloadDelegateImpl : FileDownloadAdapter

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> onDownloadSuccess %@", path);
    GameConfig *config = [PreRunGame parseGameConfigFile:path];
    if (config != nil) {
        gameConfig = config;
    } else {
        [PreRunGame notifyPreRunGameError];
    }
    
    [PreRunGame updateLocalConfigFile:path];
}

- (void) onDownloadFailed
{
    NSLog(@"===> onDownloadFailed config.json");
    [PreRunGame notifyPreRunGameError];
}

@end

@implementation ManifestDownloadDelegateImpl : FileDownloadAdapter

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> onManifestDownloadSuccess");
    NSString* targetPath = [FileUtil getLocalManifestPath:gameInfo :gameConfig];
    
    if (![FileUtil ensureDirectory:[FileUtil getParentDirectory:targetPath]]
        || ![ZipHelper unzipFileAtPath:path toDestination:[FileUtil getGameRootPath:gameInfo]]) {
        [PreRunGame notifyPreRunGameError];
        return;
    }
    [FileUtil removeFile:path];
    
    if ([FileUtil fileExists:targetPath] && [PreRunGame isLocalManifestMD5Correct]) {
        gameManifest = [GameManifest readFromFile:targetPath];
        [CocosRuntimeGroup initialize:gameInfo config:gameConfig manifest:gameManifest];
        [PreRunGame checkEntryFile];
    } else {
        // todo 重新下载
        [PreRunGame notifyPreRunGameError];
    }
}

- (void) onDownloadFailed
{
    [PreRunGame notifyPreRunGameError];
}

@end

@implementation EntryDownloadDelegateImpl : FileDownloadAdapter

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> Entry Download Success: %@", path);
    if ([FileUtil fileExists:path] && [PreRunGame isLocalEntryMD5Correct]) {
        [PreRunGame checkProjectJsonFile];
    } else {
        [PreRunGame notifyPreRunGameError];
    }

}

- (void) onDownloadFailed
{
    [PreRunGame notifyPreRunGameError];
}
@end

@implementation ProjectDownloadDelegateImpl : FileDownloadAdapter

- (void) onDownloadSuccess:(NSString *)path
{
    if ([FileUtil fileExists:path] && [PreRunGame isLocalProjectMD5Correct]) {
        [PreRunGame checkBootGroup];
    } else {
        [PreRunGame notifyPreRunGameError];
    }
}

- (void) onDownloadFailed
{
    [PreRunGame notifyPreRunGameError];
}
@end

@implementation OnBootGroupUpdateDelegateImpl

- (OnBootGroupUpdateDelegateImpl*) initWith: (ResGroup*) group
{
    if (self = [super init]) {
        resGroup = group;
    }
    return self;
}

- (void) onProgressOfDownload: (long) written total:(long) total
{
    NSInteger progressOffset = 80 * (float)(written / total);
    [PreRunGame notifyProgress: progressOffset max:100.0l];
}

- (void) onSuccessOfDownload: (long) total
{
    return;
}

- (void) onFailureOfDownload: (NSString*) errorMsg
{
    [PreRunGame notifyPreRunGameError];
    NSLog(@"===> BootGroupDownloadDelegateImpl onDownloadFailed");
}

- (void) onSuccessOfUnzip: (long)total
{
    [PreRunGame startGame];
}

- (void) onFailureOfUnzip: (NSString*) errorMsg
{
    [PreRunGame notifyPreRunGameError];
    NSLog(@"===> BootGroupDownloadDelegateImpl onDownloadFailed");
}

- (void) onProgressOfUnzip: (float) percent
{
    return;
}

@end
