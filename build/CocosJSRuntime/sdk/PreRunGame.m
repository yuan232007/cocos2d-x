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

#define PROGRESS_MAX 100
#define PROGRESS_INVALID -1

// fixme: 暂时写死，由于工具为了兼容旧版本数据（js），多了一层目录
#define COMPAT_VERSION_PATH @"33"

static GameInfo* gameInfo = nil;
static NSString* remoteConfigPath = nil;
static NSString* localConfigPath = nil;
static GameManifest* gameManifest = nil;
static FileDownload* fileDownload = nil;
static MttGameEngine* mttGameEngine = nil;
static GameConfig* gameConfig = nil;

@implementation PreRunGame
+ (void) start: (GameInfo*) info proxy: (MttGameEngine*) proxy
{
    NSLog(@"===> PreRunGame start");
    gameInfo = info;
    remoteConfigPath = [FileUtil getRemoteConfigPath:gameInfo];
    localConfigPath = [FileUtil getLocalConfigPath:gameInfo];
    mttGameEngine = proxy;
    [PreRunGame downloadRemoteConfigFile];
}

+ (void) reset
{
    
}

+ (void) downloadRemoteConfigFile
{
    NSLog(@"===> PreRunGame downloadRemoteConfigFile");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:[FileUtil getConfigFileName]];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownload *fileDownload = [[FileDownload alloc] initWithURL:requestUrl delegate:[[ConfigDownloadDelegateImpl alloc] init]];
        NSLog(@"===> remote config file url: %@", requestString);
        [fileDownload startDownload];
    });
}

+ (void) updateLocalConfigFile: (NSString*) path
{
    NSLog(@"updateLocalConfigFile %@", path);
    @try {
        [FileUtil moveFileFrom:path to:[FileUtil getLocalConfigPath:gameInfo] overwrite:true];
        [PreRunGame checkLocalManifestFile];
    }
    @catch (NSException *exception) {
        NSLog(@"updateLocalConfigFile Error");
    }
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
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:@"manifest.cpk"];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownload *fileDownload = [[FileDownload alloc] initWithURL:requestUrl delegate:[[ManifestDownloadDelegateImpl alloc] init]];
        [fileDownload startDownload];
    });
}

+ (void) parseGameConfigFile: (NSString*) path
{
    gameConfig = [GameConfig parseFromFile:path];
}

+ (void) checkEntryFile
{
    NSLog(@"===> checkEntryFile");
    if ([FileUtil fileExists:[FileUtil getLocalEntryPath:gameInfo :gameConfig]]) {
        [PreRunGame checkProjectJsonFile];
    } else {
        [PreRunGame downloadEntryFile];
    }
}

+ (void) downloadEntryFile
{
    NSLog(@"===> downloadEntryFile");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:[gameConfig entryName]];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownload *fileDownload = [[FileDownload alloc] initWithURL:requestUrl delegate:[[EntryDownloadDelegateImpl alloc] init]];
        [fileDownload startDownload];
    });
}

+ (void) checkProjectJsonFile
{
    if ([FileUtil fileExists:[FileUtil getLocalProjectPath:gameInfo :gameConfig]]) {
        [PreRunGame checkBootGroup];
    } else {
        [PreRunGame downloadProjectJsonFile];
    }
}

+ (void) downloadProjectJsonFile
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[gameInfo downloadUrl] stringByAppendingPathComponent:[gameConfig projectName]];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownload *fileDownload = [[FileDownload alloc] initWithURL:requestUrl delegate:[[ProjectDownloadDelegateImpl alloc] init]];
        [fileDownload startDownload];
    });
}

+ (void) deleteNoRefGroups
{
    NSLog(@"===> deleteNoRefGroups");
}

+ (void) checkBootGroup
{
    if ([FileUtil fileExists:[FileUtil getLocalBootGroupPath:gameInfo group:gameConfig]]) {
        [PreRunGame startGame];
    } else {
        NSLog(@"===> preloading bootgroup");
        [PreRunGame preloadBootGroup];
    }
}

+ (void) notifyProgress: (NSInteger) progress isFailed: (BOOL) isFailed
{
    if (mttGameEngine != nil) {
        [mttGameEngine onLoadingProgress:progress :isFailed];
    }
}

+ (void) notifyGameInitEnd
{
    if (mttGameEngine != nil) {
        [mttGameEngine onPreRunGameCompleted];
    }
}

+ (void) startGame
{
    NSLog(@"===> start game.");
    if (mttGameEngine != nil) {
        [mttGameEngine onLoadingProgress:100 :false];
        [mttGameEngine onPreRunGameCompleted];
    }
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

+ (BOOL) isLocalBootGroupMD5Correct
{
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
    NSString *localEntryMD5 = [FileUtil getFileMD5:[FileUtil getLocalEntryPath:gameInfo :gameConfig]];
    if ([localEntryMD5 isEqualToString:[gameConfig entryMD5]]) {
        return true;
    }
    return false;
}

+ (void) preloadBootGroup
{
    NSLog(@"===> preload boot group");
    ResGroup* resGroup = [CocosRuntimeGroup findGroupByName:@"boot"];
    if (resGroup != nil) {
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            NSString *requestString = [[[gameInfo downloadUrl]
                                         stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                       stringByAppendingPathComponent:resGroup.groupURL];
            NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
            
            BootGroupDownloadImpl* resDownloadImpl =  [[BootGroupDownloadImpl alloc] initWith:resGroup];
            FileDownload *fileDownload = [[FileDownload alloc] initWithURL:requestUrl delegate:resDownloadImpl];
            [fileDownload startDownload];
        });
    } else {
        NSLog(@"===> Couldn't find boot group");
    }
}

@end

@implementation ConfigDownloadDelegateImpl : FileDownloadAdapter

- (NSString*) onTempDownloaded:(NSString *)locationPath
{
    NSLog(@"===> Config Download location: %@", locationPath);
    NSString* targetPath = [FileUtil getRemoteConfigPath:gameInfo];
    NSLog(@"===> new location %@", targetPath);
    @try {
        NSLog(@"===> parent directory of target: %@", [FileUtil getParentDirectory:targetPath]);
        [FileUtil ensureDirectory:[FileUtil getParentDirectory:targetPath]];
        [FileUtil moveFileFrom:locationPath to:targetPath overwrite:true];
        [PreRunGame parseGameConfigFile:targetPath];
        return targetPath;
    }
    @catch (NSError *error) {
        NSLog(@"===> move config file error %@", [error description]);
    }
    @catch (NSException *exception) {
        NSLog(@"===> move config file exception %@", [exception description]);
    }

}

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> onDownloadSuccess %@", path);
    [PreRunGame updateLocalConfigFile:path];
}

- (void) onDownloadFailed
{
    [PreRunGame notifyProgress:PROGRESS_INVALID isFailed:true];
}

@end

@implementation ManifestDownloadDelegateImpl : FileDownloadAdapter

- (NSString*) onTempDownloaded:(NSString *)locationPath
{
    @try {
        NSString* targetPath = [FileUtil getLocalManifestPath:gameInfo :gameConfig];
        if (![ZipHelper unzipFileAtPath:locationPath toDestination:[FileUtil getGameRootPath:gameInfo]]) {
            @throw [[NSException alloc] init];
        }
        NSLog(@"===> new location %@", targetPath);
        return targetPath;
    }
    @catch (NSException *exception) {
        NSLog(@"===> unzip file error");
    }
}

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> onManifestDownloadSuccess");
    gameManifest = [GameManifest readFromFile:path];
    [CocosRuntimeGroup initialize:gameInfo config:gameConfig manifest:gameManifest];
    [PreRunGame checkEntryFile];
}

- (void) onDownloadFailed
{
    [PreRunGame notifyProgress:PROGRESS_INVALID isFailed:true];
}

@end

@implementation EntryDownloadDelegateImpl : FileDownloadAdapter
- (NSString*) onTempDownloaded:(NSString *)locationPath
{
    NSString* targetPath = [FileUtil getLocalEntryPath:gameInfo :gameConfig];
    @try {
        [FileUtil ensureDirectory:[FileUtil getParentDirectory:targetPath]];
        [FileUtil moveFileFrom:locationPath to:targetPath overwrite:true];
        NSLog(@"===> new location %@", targetPath);
        return targetPath;
    }
    @catch (NSError *error) {
        NSLog(@"===> move file error");
    }
}

- (void) onDownloadSuccess:(NSString *)path
{
    [PreRunGame checkProjectJsonFile];
}

- (void) onDownloadFailed
{
    [PreRunGame notifyProgress:PROGRESS_INVALID isFailed:true];
}
@end

@implementation ProjectDownloadDelegateImpl : FileDownloadAdapter
- (NSString*) onTempDownloaded:(NSString *)locationPath
{
    @try {
        NSString* targetPath = [FileUtil getLocalProjectPath:gameInfo :gameConfig];
        NSLog(@"===> new location %@", targetPath);
        [FileUtil ensureDirectory:[FileUtil getParentDirectory:targetPath]];
        [FileUtil moveFileFrom:locationPath to:targetPath overwrite:true];
        return targetPath;
    }
    @catch (NSError *error) {
        NSLog(@"===> move file error");
    }
}

- (void) onDownloadSuccess:(NSString *)path
{
    [PreRunGame checkBootGroup];
}

- (void) onDownloadFailed
{
    [PreRunGame notifyProgress:PROGRESS_INVALID isFailed:true];
}
@end

@implementation BootGroupDownloadImpl

- (BootGroupDownloadImpl*) initWith:(ResGroup *)group
{
    if (self = [super init]) {
        resGroup = group;
    }
    return self;
}

- (void) onDownloadProgress:(double)progress
{
    NSInteger progressOffset = 80 * progress;
    [PreRunGame notifyProgress:progressOffset isFailed:false];
}

- (NSString*) onTempDownloaded:(NSString *)locationPath
{
    return locationPath;
}

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> BootGroupDownloadDelegateImpl Success");
    
    NSString *targetPath = [FileUtil getLocalGroupPath:gameInfo group: resGroup];
    @try {
        [FileUtil ensureDirectory:[FileUtil getParentDirectory:targetPath]];
        [FileUtil moveFileFrom:path to:targetPath overwrite:true];
        
        NSLog(@"===> download %@", resGroup.groupURL);
        
        if (![CocosRuntimeGroup unzipGroupFrom: targetPath to: [FileUtil getGameRootPath:gameInfo] overwrite: true]) {
            NSLog(@"===> unzip success");
            @throw [[NSException alloc]init];
        }
        
        [PreRunGame notifyProgress: resGroup.groupSize isFailed: false];
        [PreRunGame startGame];
    }
    @catch (NSException *exception) {
        NSLog(@"move file error");
        [PreRunGame notifyProgress: resGroup.groupSize isFailed: true];
    }
}

- (void) onDownloadFailed
{
    [PreRunGame notifyProgress: resGroup.groupSize isFailed: true];
    NSLog(@"===> BootGroupDownloadDelegateImpl onDownloadFailed");
}
@end
