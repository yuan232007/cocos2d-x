//
//  CocosRuntimeGroupPatch.m
//  CocosJSRuntime
//
//  Created by Rye on 11/11/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "CocosRuntimeGroupPatch.h"
#import "FileUtil.h"
#import "ZipHelper.h"
#import "FileDownloader.h"
#import "CocosRuntimeGroup.h"

@implementation CocosRuntimeGroupPatch

@synthesize gameInfo;

- (CocosRuntimeGroupPatch*) initWith:(GameInfo *)info groupVersionManager:(GroupVersionManager *)manager
{
    self = [super init];
    if (self != nil) {
        totalSize = 1;
        groupVersionManager = manager;
    }
    return self;
}

- (void) unzipPatch: (NSString*) groupName version:(NSString*)version delegate:(id<OnGroupUpdateDelegate>)delegate
{
    // todo 添加解压的进度通知
//    NSString *patchName = [@"patch_" stringByAppendingString:version];
//    NSString *currentPatch = [FileUtil getLocalGroupPatchPathByName:gameInfo name:groupName];
    NSString* patchPath = [FileUtil getGroupPatchPackagePath: gameInfo groupName:groupName version:version];
    
    [ZipHelper unzipFileAtPath:patchPath
            toDestination:[FileUtil getGameRootPath:gameInfo]
            progressHandler:^(NSString *entry, long entryNumber, long total) {
                [delegate onProgressOfUnzip:entryNumber total:total];
            }
            completionHandler:^(NSString *zipFilePath, BOOL succeeded, NSError *error) {
                if (error == nil) {
                    [FileUtil removeFile:patchPath];
                    [self deleteFileFromDeleteList:groupName];
                    NSInteger latestVersionCode = [[CocosRuntimeGroup getGameConfig] versionCode];
                    [groupVersionManager setGroupVersionCode:groupName versionCode:latestVersionCode];
                    [delegate onSuccessOfUnzip: totalSize];
                } else {
                    NSLog(@"===> CocosRuntimeGroupPatch unzip FAILED patch: %@", patchPath);
                    // fixme: 错误信息不要写死
                    [delegate onFailureOfUnzip:@"解压补丁包失败"];
                }
            }
    ];
}

- (void) downloadPatch:(GroupPatch*)patch groupName:(NSString *)name version:(NSString *)version delegate:(id<OnGroupUpdateDelegate>)delegate
{
    NSURL *requestUrl = [[NSURL alloc]initWithString:[[gameInfo downloadUrl] stringByAppendingPathComponent:[patch patchURL]]];
    NSString *localPatchPath = [FileUtil getGroupPatchPackagePath:gameInfo groupName:name version:version];
    PatchDownloadDelegateImpl* downloadDelegate = [[PatchDownloadDelegateImpl alloc] initWith:self patch:patch versionCode:version groupName:name groupDelegate:delegate];
    currentFileDownloader = [[FileDownloader alloc] initWithURL:requestUrl targetPath:localPatchPath delegate:downloadDelegate];
    [currentFileDownloader start];
}

- (BOOL) isPatchPackageMD5Correct: (NSString*)groupName version:(NSString*)code path:(NSString*)path
{
    ResGroup *resGroup = [CocosRuntimeGroup findGroupByName:groupName];
    GroupPatch *patch = [resGroup getPatch:groupName];
    if ([[patch patchMD5] isEqualToString:[FileUtil getFileMD5:path]]) {
        NSLog(@"===> The MD5 of patch zip (%@) is CORRECT!", code);
        return TRUE;
    }
    NSLog(@"===> The MD5 of patch zip (%@) is WRONG!", code);
    return FALSE;
}

- (void) deleteFileFromDeleteList:(NSString *)groupName
{
    NSString *deletedFilePath = [FileUtil getGroupDeletedFilePath: gameInfo groupName:groupName];
    if (![FileUtil fileExists:deletedFilePath]) {
        NSLog(@"===> cc-deleted-files-%@.json does NOT exist", groupName);
        return;
    }
    
    NSMutableArray *deleteArray = (NSMutableArray*)[FileUtil readJsonFromFile:deletedFilePath];
    for (NSInteger i = 0; deleteArray.count; i++) {
        NSString *fileName = [deleteArray objectAtIndex:i];
        NSString *path = [[FileUtil getGameRootPath:gameInfo] stringByAppendingPathComponent:fileName];
        if (![FileUtil fileExists:path]) {
            NSLog(@"Deleting file FAILED (%@)", path);
            continue;
        }
        [FileUtil removeFile:path];
        NSLog(@"===> Delete (%@) SUCCESS", path);
    }
    [FileUtil removeFile:deletedFilePath];
}

- (void) updatePatch: (NSString*)url groupName:(NSString*)name version:(NSString*)version delegate:(id<OnGroupUpdateDelegate>)delegate
{
    NSLog(@"CocosRuntimeGroupPatch updatePatch url:%@", url);
    [self downloadPatch:url groupName:name version:version delegate:delegate];
}

- (GroupPatch*) findPatch: (NSString*)groupName versionCode:(NSString*)version
{
    if (groupName == nil || [groupName length] == 0 || version == nil || [version length] == 0) {
        return nil;
    }
    
    ResGroup *resGroup = [CocosRuntimeGroup findGroupByName: groupName];
    if (resGroup == nil) {
        return nil;
    }
    
    return [resGroup getPatch:version];
}

@end

@implementation PatchDownloadDelegateImpl : FileDownloadAdapter
- (PatchDownloadDelegateImpl*) initWith: (CocosRuntimeGroupPatch*)runtimePatch patch:(GroupPatch*)patch versionCode:(NSString*)code groupName:(NSString*)name groupDelegate: (id<OnGroupUpdateDelegate>)delegate
{
    self = [super init];
    if (self != nil) {
        groupPatch = patch;
        onGroupUpdateDelegate = delegate;
        versionCode = code;
        groupName = name;
        cocosRuntimeGroupPatch = runtimePatch;
    }
    return self;
}

- (void) onDownloadSuccess:(NSString *)path
{
    [onGroupUpdateDelegate onSuccessOfDownload:[groupPatch patchSize]];
    if (![cocosRuntimeGroupPatch isPatchPackageMD5Correct:groupName version:versionCode path:path]) {
        [FileUtil removeFile:path];
        NSLog(@"===> Download patch (%@) md5 is WRONG", groupName);
        [onGroupUpdateDelegate onFailureOfDownload:@"下载分组错误"];
    }
    
    [cocosRuntimeGroupPatch unzipPatch:groupName version:versionCode delegate:onGroupUpdateDelegate];
}

- (void) onDownloadFailed
{
    NSLog(@"===> Download patch (%@) FAILED!", [groupPatch patchURL]);
    // fixme 写死的错误信息
    [onGroupUpdateDelegate onFailureOfDownload:@"下载分组错误"];
}
@end