//
//  CocosRuntimeGroup.m
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "CocosRuntimeGroup.h"
#import "FileDownload.h"
#import "FileUtil.h"
#import "ZipHelper.h"

static GameInfo *gameInfo = nil;
static GameConfig *gameConfig = nil;
static GameManifest *gameManifest = nil;
static NSMutableArray *resGroup = nil;
static NSMutableDictionary *resGroupDict = nil;
static NSMutableArray *waitingDownloadGroups = nil;
static NSString* currentDownloadName = nil;
static id<LoadingDelegate> resDownloadDelegate = nil;
static NSInteger totalSize = 0;
static NSInteger downloadGroupSize = 0;

@implementation CocosRuntimeGroup
+ (void) initialize: (GameInfo*) info config: (GameConfig*) config manifest: (GameManifest*) manifest
{
    gameInfo = info;
    gameConfig = config;
    gameManifest = manifest;
    resGroup = [CocosRuntimeGroup getAllResGroups];
    resGroupDict = [CocosRuntimeGroup getAllResGroupDict:resGroup];
    waitingDownloadGroups = [NSMutableArray arrayWithCapacity:20];
}

+ (NSMutableArray*) getAllResGroups
{
    NSMutableArray* allResGroups = [NSMutableArray arrayWithCapacity:20];
    for (NSDictionary* resGroupDict in gameManifest.resGroupArray) {
        ResGroup* resGroup = [[ResGroup alloc] init];
        [resGroup setGroupMD5:[resGroupDict objectForKey:@"md5"]];
        [resGroup setGroupName:[resGroupDict objectForKey:@"name"]];
        [resGroup setGroupPriority:[[resGroupDict objectForKey:@"priority"] integerValue]];
        [resGroup setGroupSize:[[resGroupDict objectForKey:@"size"] integerValue]];
        [resGroup setGroupURL:[resGroupDict objectForKey:@"url"]];
        [allResGroups addObject:resGroup];
    }
    return allResGroups;
}

+ (void) prepareWaitingDownloadGroups: (NSString*) groupsString
{
    NSArray *groupsNameArray = [groupsString componentsSeparatedByString:@":"];
    NSLog(@"===> prepareWaitingDownloadGroups:%@", groupsNameArray);
    totalSize = 0;
    for (NSString *groupName in groupsNameArray) {
        if ([self isGroupUpdated:groupName]) {
            continue;
        }
        
        if ([waitingDownloadGroups containsObject:groupName]) {
            continue;
        }
        
        [waitingDownloadGroups addObject:groupName];
        
        ResGroup *resGroup = [self findGroupByName:groupName];
        if (resGroup != nil) {
            totalSize += resGroup.groupSize;
        }
    }
}

+ (void) notifyProgress: (NSInteger) progressOffset unzipDone: (BOOL) unzipDone isFailed: (BOOL) isFailed
{
    if (isFailed) {
        [resDownloadDelegate onLoadingProgress:(downloadGroupSize + progressOffset) :true];
    } else {
        NSInteger progress = 1.0 * (downloadGroupSize + progressOffset) / totalSize * 100;
        [resDownloadDelegate onLoadingProgress:progress :false];
        
        if (unzipDone) {
            downloadGroupSize += progressOffset;
        }
    }
}

+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate
{
    NSLog(@"===> preload resource groups: %@", groupsString);
    resDownloadDelegate = delegate;
    [CocosRuntimeGroup prepareWaitingDownloadGroups:groupsString];
    [CocosRuntimeGroup preloadNextGroup];
}

+ (void) preloadNextGroup
{
    NSLog(@"===> preload Next group");
    if (waitingDownloadGroups == nil || waitingDownloadGroups.count == 0) {
        [resDownloadDelegate onLoadingProgress:PROGRESS_MAX :false];
        return;
    }
    
    currentDownloadName = [CocosRuntimeGroup getCurrentGroupNameFromWaitingGroups];
    ResGroup *currentResGroup = [CocosRuntimeGroup findGroupByName:currentDownloadName];
    if (currentResGroup != nil) {
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            [CocosRuntimeGroup downloadResGroup:gameInfo group:currentResGroup];
        });
    } else {
        NSLog(@"===> Couldn't find %@ group:", currentDownloadName);
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

+ (BOOL) isGroupUpdated: (NSString*) name
{
    return false;
}

+ (NSMutableDictionary*) getAllResGroupDict: (NSMutableArray*) resGroupArray
{
    resGroupDict = [NSMutableDictionary dictionaryWithCapacity:20];
    for (ResGroup *resGroup in resGroupArray) {
        [resGroupDict setObject:resGroup forKey:resGroup.groupName];
    }
    return resGroupDict;
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

+ (BOOL) unzipGroupFrom: (NSString*) fromPath to: (NSString*) toPath overwrite: (BOOL) overwrite
{
    return [ZipHelper unzipFileAtPath:fromPath toDestination:toPath];
}

+ (void) updateResGroup: (GameInfo*) gameInfo group: (ResGroup*) resGroup
{
    [CocosRuntimeGroup checkResGroup:gameInfo group:resGroup];
}

+ (void) checkResGroup: (GameInfo*) gameInfo group: (ResGroup*) resGroup
{
    NSString* localGroupPath = [FileUtil getLocalGroupPath:gameInfo group:resGroup];
    if ([CocosRuntimeGroup isGroupMD5Correct:resGroup.groupMD5 path:localGroupPath]) {
        [CocosRuntimeGroup unzipGroupFrom:localGroupPath to: [FileUtil getGameRootPath:gameInfo] overwrite: true];
    } else {
        [CocosRuntimeGroup downloadResGroup:gameInfo group:resGroup];
    }
}

+ (void) downloadResGroup: (GameInfo*) gameInfo group: (ResGroup*) resGroup
{
    NSURL *requestUrl = [[NSURL alloc]initWithString:[[[gameInfo downloadUrl] stringByAppendingPathComponent:@"/"] stringByAppendingPathComponent:resGroup.groupURL]];
    
    ResourceGroupDownloadImpl* resDownloadImpl =  [[ResourceGroupDownloadImpl alloc] initWith:resGroup];
    FileDownload *fileDownload = [[FileDownload alloc] initWithURL:requestUrl delegate:resDownloadImpl];
    [fileDownload startDownload];
}

+ (void) remoteFirstGroupFromWaitingDownload
{
    if (waitingDownloadGroups.count != 0) {
        [waitingDownloadGroups removeObjectAtIndex:0];
    }
}

@end

@implementation ResourceGroupDownloadImpl

- (ResourceGroupDownloadImpl*) initWith:(ResGroup *)group
{
    if (self = [super init]) {
        resGroup = group;
    }
    return self;
}

- (void) onDownloadProgress:(double)progress
{
    NSInteger progressOffset = resGroup.groupSize * 0.8 * progress;
    [CocosRuntimeGroup notifyProgress: progressOffset unzipDone: false isFailed: false];
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
        }
        
        [CocosRuntimeGroup notifyProgress: resGroup.groupSize unzipDone: false isFailed: false];
        [CocosRuntimeGroup remoteFirstGroupFromWaitingDownload];
        [CocosRuntimeGroup preloadNextGroup];
    }
    @catch (NSException *exception) {
        NSLog(@"move file error");
        [CocosRuntimeGroup notifyProgress: resGroup.groupSize unzipDone: true isFailed: true];
    }
}

- (void) onDownloadFailed
{
    NSLog(@"===> BootGroupDownloadDelegateImpl onDownloadFailed");
    [CocosRuntimeGroup notifyProgress: resGroup.groupSize unzipDone: true isFailed: true];
}
@end




