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

static GameInfo* s_rtGameInfo = nil;
static GameManifest* s_rtGameManifest = nil;
static id<LoadingDelegate> s_rtLoadingDelegate = nil;
static GameConfig* s_rtGameConfig = nil;

@implementation PreRunGame
+ (void) start: (NSString*) gameKey delegate:(id<LoadingDelegate>)delegate
{
    NSLog(@"===> PreRunGame start");
    s_rtLoadingDelegate = delegate;
    [PreRunGame checkStatusBeforeRunGame: gameKey];
}

+ (void) reset
{
    s_rtGameInfo = nil;
    s_rtGameManifest = nil;
    s_rtLoadingDelegate = nil;
    s_rtGameConfig = nil;
}

+ (void) checkStatusBeforeRunGame: (NSString*)gameKey
{
    NSLog(@"===> PreRunGame checkStatusBeforeRunGame: %@", gameKey);
    [NetworkController requestGameInfoByGameKey:gameKey callback:^(GameInfo *info, BOOL isFailed) {
        NSLog(@"===> PreRunGame checkStatusBeforeRunGame: GameInfo: %@", info);
        if (isFailed) {
            [s_rtLoadingDelegate onLoadingError];
        } else {
            s_rtGameInfo = info;
            
            [PreRunGame downloadRemoteConfigFile];
        }
    }];
}

+ (void) downloadRemoteConfigFile
{
    NSLog(@"===> LocalConfig %@", [FileUtil getLocalConfigPath:s_rtGameInfo]);
    NSLog(@"===> PreRunGame downloadRemoteConfigFile");
//    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[[s_rtGameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:[FileUtil getConfigFileName]];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getRemoteConfigPath:s_rtGameInfo] delegate:[[ConfigDownloadDelegateImpl alloc] init]];
        NSLog(@"===> remote config file url: %@", requestString);
        [fileDownload start];
//    });
}

+ (void) updateLocalConfigFile: (NSString*) path
{
    NSLog(@"updateLocalConfigFile %@", path);
    [FileUtil moveFileFrom:path to:[FileUtil getLocalConfigPath:s_rtGameInfo] overwrite:true];
    [PreRunGame checkLocalManifestFile];
}

+ (void) checkLocalManifestFile
{
    NSLog(@"===> checkLocalManifestFile ");
    NSString *localManifestPath = [FileUtil getLocalManifestPath:s_rtGameInfo :s_rtGameConfig];
    if ([FileUtil fileExists:localManifestPath] && [PreRunGame isLocalManifestMD5Correct]) {
        s_rtGameManifest = [GameManifest readFromFile:localManifestPath];
        [CocosRuntimeGroup initialize:s_rtGameInfo config:s_rtGameConfig manifest:s_rtGameManifest];
        [PreRunGame checkEntryFile];
    } else {
        [PreRunGame downloadRemoteManifestFile];
    }
}

+ (void) downloadRemoteManifestFile
{
    NSString *requestString = [[[s_rtGameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:@"manifest.cpk"];
    NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
    FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getManifestCpkPath:s_rtGameInfo :s_rtGameConfig] delegate:[[ManifestDownloadDelegateImpl alloc] init]];
    [fileDownload start];
}

+ (GameConfig*) parseGameConfigFile: (NSString*) path
{
    return [GameConfig parseFromFile:path];
}

+ (GameConfig*)getGameConfig
{
    return s_rtGameConfig;
}

+ (void) checkEntryFile
{
    NSLog(@"===> checkEntryFile");
    if ([FileUtil fileExists:[FileUtil getLocalEntryPath:s_rtGameInfo :s_rtGameConfig]] && [PreRunGame isLocalEntryMD5Correct]) {
        [PreRunGame checkProjectJsonFile];
    } else {
        [PreRunGame downloadEntryFile];
    }
}

+ (void) downloadEntryFile
{
    NSLog(@"===> downloadEntryFile");
    NSString *requestString = [[[s_rtGameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:[s_rtGameConfig entryName]];
    NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
    FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getLocalEntryPath:s_rtGameInfo :s_rtGameConfig] delegate:[[EntryDownloadDelegateImpl alloc] init]];
    [fileDownload start];
}

+ (void) checkProjectJsonFile
{
    if ([FileUtil fileExists:[FileUtil getLocalProjectPath:s_rtGameInfo :s_rtGameConfig]] && [PreRunGame isLocalProjectMD5Correct]) {
        [PreRunGame checkBootGroup];
    } else {
        [PreRunGame downloadProjectJsonFile];
    }
}

+ (void) downloadProjectJsonFile
{
    NSString *requestString = [[s_rtGameInfo downloadUrl] stringByAppendingPathComponent:[s_rtGameConfig projectName]];
    NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
    FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl targetPath:[FileUtil getLocalProjectPath:s_rtGameInfo :s_rtGameConfig] delegate:[[ProjectDownloadDelegateImpl alloc] init]];
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
    if (s_rtLoadingDelegate != nil) {
        [s_rtLoadingDelegate onLoadingProgress:progress max:max];
    }
}

+ (void) notifyPreRunGameError
{
    if (s_rtLoadingDelegate != nil) {
        [s_rtLoadingDelegate onLoadingError];
    }
}

+ (void) startGame
{
    NSLog(@"===> start game.");
    if (s_rtLoadingDelegate != nil) {
        [s_rtLoadingDelegate onLoadingCompleted];
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
    NSString *localConfigMD5 = [FileUtil getFileMD5: [FileUtil getLocalConfigPath:s_rtGameInfo]];
    NSString *remoteConfigMD5 = [FileUtil getFileMD5:[FileUtil getRemoteConfigPath:s_rtGameInfo]];
    if ([localConfigMD5 isEqualToString:remoteConfigMD5]) {
        return true;
    }
    return false;
}

+ (BOOL) isLocalManifestMD5Correct
{
    NSString *localManifestMD5 = [FileUtil getFileMD5:[FileUtil getLocalManifestPath:s_rtGameInfo :s_rtGameConfig]];
    if ([localManifestMD5 isEqualToString:[s_rtGameConfig manifestMD5]]) {
        return true;
    }
    return false;
}

+ (BOOL) isLocalProjectMD5Correct
{
    NSString *localProjectMD5 = [FileUtil getFileMD5:[FileUtil getLocalProjectPath:s_rtGameInfo :s_rtGameConfig]];
    if ([localProjectMD5 isEqualToString:[s_rtGameConfig projectMD5]]) {
        return true;
    }
    return false;
}

+ (BOOL) isLocalEntryMD5Correct
{
    NSLog(@"===> Entry md5:%@", [FileUtil getLocalEntryPath:s_rtGameInfo :s_rtGameConfig]);
    NSString *localEntryMD5 = [FileUtil getFileMD5:[FileUtil getLocalEntryPath:s_rtGameInfo :s_rtGameConfig]];
    if ([localEntryMD5 isEqualToString:[s_rtGameConfig entryMD5]]) {
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
        s_rtGameConfig = config;
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
    NSString* targetPath = [FileUtil getLocalManifestPath:s_rtGameInfo :s_rtGameConfig];
    
    if (![FileUtil ensureDirectory:[FileUtil getParentDirectory:targetPath]]
        || ![ZipHelper unzipFileAtPath:path toDestination:[FileUtil getGameRootPath:s_rtGameInfo]]) {
        [PreRunGame notifyPreRunGameError];
        return;
    }
    [FileUtil removeFile:path];
    
    if ([FileUtil fileExists:targetPath] && [PreRunGame isLocalManifestMD5Correct]) {
        s_rtGameManifest = [GameManifest readFromFile:targetPath];
        [CocosRuntimeGroup initialize:s_rtGameInfo config:s_rtGameConfig manifest:s_rtGameManifest];
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
    float progressOffset = 80.0f * written / resGroup.groupSize;
    [PreRunGame notifyProgress: progressOffset max:100.0l];
}

- (void) onSuccessOfDownload: (long) total
{
    NSLog(@"===> Boot Download SUCCESS");
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

- (void) onProgressOfUnzip: (long) written total:(long) total
{
    float progressOffset = 80.0f + ((float) (written) / total) * 20;
    [PreRunGame notifyProgress:progressOffset max:100.0l];
}

@end
