//
//  CocosRuntimeGroupPatch.h
//  CocosJSRuntime
//
//  Created by Rye on 11/11/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"
#import "GroupPatch.h"
#import "OnGroupUpdateDelegate.h"
#import "FileDownloadAdapter.h"
#import "FileDownloader.h"
#import "ResGroup.h"
#import "GroupVersionManager.h"
#import "CocosRuntimeGroup.h"

@interface CocosRuntimeGroupPatch : NSObject
{
    GameInfo *gameInfo;
    NSInteger totalSize;
    FileDownloader *currentFileDownloader;
    GroupVersionManager *groupVersionManager;
}

@property GameInfo* gameInfo;

- (CocosRuntimeGroupPatch*) initWith: (GameInfo*)info groupVersionManager:(GroupVersionManager*)manager;
- (BOOL) isPatchPackageMD5Correct: (NSString*)groupName version:(NSString*)code path:(NSString*)path;
- (void) unzipPatch: (NSString*) groupName version:(NSString*)version delegate:(id<OnGroupUpdateDelegate>)delegate;
- (void) downloadPatch: (NSString*)url groupName:(NSString*)name version:(NSString*)version delegate:(id<OnGroupUpdateDelegate>)delegate;
- (void) deleteFileFromDeleteList: (NSString*) groupName;
- (void) updatePatch: (NSString*)url groupName:(NSString*)name version:(NSString*)version delegate:(id<OnGroupUpdateDelegate>)delegate;
- (GroupPatch*) findPatch: (NSString*)groupName versionCode:(NSString*)version;
@end

@interface PatchDownloadDelegateImpl : FileDownloadAdapter
{
    CocosRuntimeGroupPatch *cocosRuntimeGroupPatch;
    GroupPatch *groupPatch;
    NSString *versionCode;
    NSString *groupName;
    id<OnGroupUpdateDelegate> onGroupUpdateDelegate;
}
- (PatchDownloadDelegateImpl*) initWith: (CocosRuntimeGroupPatch*)runtimePatch patch:(GroupPatch*)patch versionCode:(NSString*)code groupName:(NSString*)name groupDelegate: (id<OnGroupUpdateDelegate>)delegate;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;

@end