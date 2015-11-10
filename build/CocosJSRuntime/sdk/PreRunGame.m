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
static FileDownloader* fileDownload = nil;
static id<LoadingDelegate> loadingDelegate = nil;
static GameConfig* gameConfig = nil;

@implementation PreRunGame
+ (void) start: (GameInfo*) info delegate:(id<LoadingDelegate>)delegate
{
    NSLog(@"===> PreRunGame start");
    gameInfo = info;
    remoteConfigPath = [FileUtil getRemoteConfigPath:gameInfo];
    localConfigPath = [FileUtil getLocalConfigPath:gameInfo];
    loadingDelegate = delegate;
    [PreRunGame downloadRemoteConfigFile];
}

+ (void) reset
{
    
}

+ (void) downloadRemoteConfigFile
{
    NSLog(@"===> LocalConfig %@", [FileUtil getLocalConfigPath:gameInfo]);
    NSLog(@"===> PreRunGame downloadRemoteConfigFile");
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:[FileUtil getConfigFileName]];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl delegate:[[ConfigDownloadDelegateImpl alloc] init]];
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
//    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:@"manifest.cpk"];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl delegate:[[ManifestDownloadDelegateImpl alloc] init]];
        [fileDownload startDownload];
//    });
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
//    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[[gameInfo downloadUrl] stringByAppendingPathComponent:COMPAT_VERSION_PATH]
                                   stringByAppendingPathComponent:[gameConfig entryName]];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl delegate:[[EntryDownloadDelegateImpl alloc] init]];
        [fileDownload startDownload];
//    });
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
//    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        NSString *requestString = [[gameInfo downloadUrl] stringByAppendingPathComponent:[gameConfig projectName]];
        NSURL *requestUrl = [[NSURL alloc] initWithString:requestString];
        FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl delegate:[[ProjectDownloadDelegateImpl alloc] init]];
        [fileDownload startDownload];
//    });
}

+ (void) deleteNoRefGroups
{
    NSLog(@"===> deleteNoRefGroups");
}

+ (void) checkBootGroup
{
    if ([FileUtil fileExists:[FileUtil getLocalBootGroupPath:gameInfo group:gameConfig]] && [PreRunGame isLocalBootGroupMD5Correct]) {
        [PreRunGame startGame];
    } else {
        NSLog(@"===> preloading bootgroup");
        [PreRunGame preloadBootGroup];
    }
}

+ (void) notifyProgress: (float) progress max:(float)max
{
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
    NSLog(@"boot cpk md5:%@", [FileUtil getLocalBootGroupPath:gameInfo group:gameConfig]);
    NSString *localBootMD5 = [FileUtil getFileMD5:[FileUtil getLocalBootGroupPath:gameInfo group:gameConfig]];
    ResGroup* resGroup = [CocosRuntimeGroup findGroupByName:@"boot"];
    if ([localBootMD5 isEqualToString:resGroup.groupMD5]) {
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
    NSLog(@"ENtry md5:%@", [FileUtil getLocalEntryPath:gameInfo :gameConfig]);
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
            FileDownloader *fileDownload = [[FileDownloader alloc] initWithURL:requestUrl delegate:resDownloadImpl];
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
        GameConfig *config = [PreRunGame parseGameConfigFile:targetPath];
        if (config == nil) {
            return nil;
        } else {
            gameConfig = config;
        }
        return targetPath;
    }
    @catch (NSError *error) {
        NSLog(@"===> move config file error %@", [error description]);
    }
    @catch (NSException *exception) {
        NSLog(@"===> move config file exception %@", [exception description]);
    }
    
    return nil;
}

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> onDownloadSuccess %@", path);
    [PreRunGame updateLocalConfigFile:path];
}

- (void) onDownloadFailed
{
    NSLog(@"===> onDownloadFailed config.json");
    [PreRunGame notifyPreRunGameError];
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
    
    return nil;
}

- (void) onDownloadSuccess:(NSString *)path
{
    NSLog(@"===> onManifestDownloadSuccess");
    if ([FileUtil fileExists:path] && [PreRunGame isLocalManifestMD5Correct]) {
        gameManifest = [GameManifest readFromFile:path];
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
- (NSString*) onTempDownloaded:(NSString *)locationPath
{
    NSString* targetPath = [FileUtil getLocalEntryPath:gameInfo :gameConfig];
    @try {
        [FileUtil ensureDirectory:[FileUtil getParentDirectory:targetPath]];
        [FileUtil moveFileFrom:locationPath to:targetPath overwrite:true];
        NSLog(@"===> new Entry location %@", targetPath);
        return targetPath;
    }
    @catch (NSError *error) {
        NSLog(@"===> move Entry file error");
    }
    return nil;
}

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
    return nil;
}

- (void) onDownloadSuccess:(NSString *)path
{
    if ([FileUtil fileExists:[FileUtil getLocalProjectPath:gameInfo :gameConfig]] && [PreRunGame isLocalProjectMD5Correct]) {
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
    [PreRunGame notifyProgress: progressOffset max:100.0l];
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
        if (![FileUtil fileExists:[FileUtil getLocalBootGroupPath:gameInfo group:gameConfig]] || ![PreRunGame isLocalBootGroupMD5Correct]) {
            @throw [[NSException alloc]init];
        }
        NSLog(@"===> download %@", resGroup.groupURL);
        
        if (![CocosRuntimeGroup unzipGroupFrom: targetPath to: [FileUtil getGameRootPath:gameInfo] overwrite: true]) {
            @throw [[NSException alloc]init];
        }
        
        [PreRunGame notifyProgress: resGroup.groupSize max:100.0l];
        [PreRunGame startGame];
    }
    @catch (NSException *exception) {
        NSLog(@"move file error");
        [PreRunGame notifyPreRunGameError];
    }
}

- (void) onDownloadFailed
{
    [PreRunGame notifyPreRunGameError];
    NSLog(@"===> BootGroupDownloadDelegateImpl onDownloadFailed");
}
@end
