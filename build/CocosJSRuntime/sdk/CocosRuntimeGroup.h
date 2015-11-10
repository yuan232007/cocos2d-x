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
#import "MttGameEngineProtocol.h"
#import "FileDownloadAdapter.h"
#import "OnGroupUpdateDelegate.h"
#import "OnLoadingProgressDelegate.h"

#define PROGRESS_MAX 100
#define PROGRESS_INVALID -1
#define GROUP_UNZIP @"unzip"
#define GROUP_DOWNLOAD @"download"

@interface CocosRuntimeGroup : NSObject
+ (void) initialize: (GameInfo*) info config: (GameConfig*) config manifest: (GameManifest*) manifest;
+ (NSString*) getCurrentGroupNameFromWaitingGroups;
+ (BOOL) isGroupUpdated: (NSString*) name;
+ (NSMutableDictionary*) getAllResGroupDict: (NSMutableArray*) resGroupArray;
+ (ResGroup*) findGroupByName: (NSString*) name;
+ (BOOL) isGroupMD5Correct: (NSString*) md5 path: (NSString*) path;
+ (BOOL) isDownloadIndexValid: (NSInteger)index;
+ (ResGroup*) getResGroupByIndex: (NSInteger)index;
+ (void) removeFirstGroupFromWaitingDownload;
+ (void) removeGroupFromWaitingDownload: (NSString*)groupName;
+ (NSString*) getFirstGroupFromWaitingDownload;
+ (void) reset;
+ (BOOL) needToDownloadGroup: (NSString*)groupString;

+ (id<LoadingDelegate>) getLoadingDelegate;

/**
 * 开始下载等待队列里的第一个分组，没有则通知下载结束
 */
+ (void) startDownloadGroups;

/**
 * 准备等待下载队列，进度信息
 */
+ (void) prepareWaitingDownloadGroups: (NSString*) groupsString;

/**
 * 根据分组名更新分组，先检查是否分组处于已更新状态，如果未更新则下载分组
 */
+ (void) updateGroup: (NSString*)groupName  delegate:(id<OnGroupUpdateDelegate>) delegate;

/**
 * 预加载分组，开放给游戏的接口
 */
+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate;

/**
 * 下载游戏分组
 */
+ (void) downloadResGroup: (GameInfo*) gameInfo group: (ResGroup*) resGroup delegate: (id<OnGroupUpdateDelegate>) delegate;

/**
 * 解压指定分组
 */
+ (BOOL) unzipGroupFrom: (NSString*) fromPath to: (NSString*) toPath overwrite: (BOOL) overwrite;

+ (BOOL) isInCancelDownloadState;

/**
 * 取消当前正在下载的任务
 */
+ (void) cancelCurrentDownload;

/*************************************** Silent Download **********************************/

/**
 * 是否开启静默下载
 */
+ (BOOL) isSilentDownloadEnabled;

/**
 * 设置是否开启静默下载
 */
+ (void) setSilentDownloadEnabled: (BOOL) isEnabled;

/**
 * 开始静默下载下一个分组
 */
+ (void) silentDownloadNextGroup;

/**
 * 增加静默下载的索引
 */
+ (int) increaseIndexOfSilentDownload;

/**
 * 减少静默下载的索引
 */
+ (int) decreaseIndexOfSilentDownload;

/**
 * 获得下一个要静默下载的分组
 */
+ (ResGroup*) getNextResGroupForDownload;

/**
 * 设置是否处于静默下载的状态
 */
+ (void) setInSilentDownloadState: (BOOL)inSilentDownload;

+ (BOOL) isInSilentDownloadState;

+ (void) clearDownloadState;

@end

/**
 * 下载分组资源监听
 */
@interface ResourceGroupDownloadImpl : FileDownloadAdapter
{
    ResGroup* resGroup;
    id<OnGroupUpdateDelegate> onGroupUpdateDelegate;
}
- (ResourceGroupDownloadImpl*) initWith: (ResGroup*) resGroup groupDelegate: (id<OnGroupUpdateDelegate>)delegate;
- (void) onDownloadProgress:(long)progress max:(long)max;
- (NSString*) onTempDownloaded:(NSString *)locationPath;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end

/**
 * 分组更新监听
 */
@interface OnGroupUpdateDelegateImpl : NSObject <OnGroupUpdateDelegate>
{
    ResGroup* resGroup;
}
- (OnGroupUpdateDelegateImpl*) initWith: (ResGroup*) group;
- (void) onProgressOfDownload: (long) written total:(long) total;
- (void) onSuccessOfDownload: (long) total;
- (void) onFailureOfDownload: (NSString*) errorMsg;
- (void) onSuccessOfUnzip: (long)total;
- (void) onFailureOfUnzip: (NSString*) errorMsg;
- (void) onProgressOfUnzip: (float) percent;
@end

/**
 * 抽象的进度监听
 */
@interface OnLoadingProgressDelegateImpl : NSObject <OnLoadingProgressDelegate>
- (void) onUpdateOfLoadingInfo: (LoadingInfo*) currentLoadingInfo;
- (void) onAllLoaingFinish;
@end


