//
//  CocosRuntimeGroup.h
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"
#import "GameConfig.h"
#import "GameManifest.h"
#import "ResGroup.h"
#import "LoadingDelegate.h"
#import "FileDownloadAdapter.h"
#import "MttGameEngineProtocol.h"

#define PROGRESS_MAX 100
#define PROGRESS_INVALID -1

@interface CocosRuntimeGroup : NSObject
+ (void) initialize: (GameInfo*) info config: (GameConfig*) config manifest: (GameManifest*) manifest;
+ (NSMutableArray*) getAllResGroups;
+ (void) prepareWaitingDownloadGroups: (NSString*) groupsString;
+ (void) notifyProgress: (NSInteger) progressOffset unzipDone: (BOOL) unzipDone isFailed: (BOOL) isFailed;
+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate;
+ (void) preloadNextGroup;
+ (NSString*) getCurrentGroupNameFromWaitingGroups;
+ (BOOL) isGroupUpdated: (NSString*) name;
+ (NSMutableDictionary*) getAllResGroupDict: (NSMutableArray*) resGroupArray;
+ (ResGroup*) findGroupByName: (NSString*) name;
+ (BOOL) isGroupMD5Correct: (NSString*) md5 path: (NSString*) path;

/**
 * 解压指定分组
 */
+ (BOOL) unzipGroupFrom: (NSString*) fromPath to: (NSString*) toPath overwrite: (BOOL) overwrite;
+ (void) updateResGroup: (GameInfo*) gameInfo group: (ResGroup*) resGroup;

/**
 * 检查本地 cpk 是否存在, 如果不存在活着 MD5 值不同，则重新下载
 */
+ (void) checkResGroup: (GameInfo*) gameInfo group: (ResGroup*) resGroup;

/**
 * 下载游戏分组
 */
+ (void) downloadResGroup: (GameInfo*) gameInfo group: (ResGroup*) resGroup;
+ (void) remoteFirstGroupFromWaitingDownload;
@end

/**
 * 下载分组资源回调
 */
@interface ResourceGroupDownloadImpl : FileDownloadAdapter
{
    ResGroup* resGroup;
}
- (ResourceGroupDownloadImpl*) initWith: (ResGroup*) resGroup;
- (void) onDownloadProgress:(double)progress;
- (NSString*) onTempDownloaded:(NSString *)locationPath;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end
