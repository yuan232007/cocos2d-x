//
//  PreRunGame.h
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"
#import "GameConfig.h"
#import "GameManifest.h"
#import "FileDownloader.h"
#import "MttGameEngine.h"
#import "FileDownloadAdapter.h"
#import "LoadingDelegate.h"
#import "OnGroupUpdateDelegate.h"

@interface PreRunGame : NSObject

+ (void) start: (NSString*) gameKey delegate: (id<LoadingDelegate>) delegate;
+ (void) reset;

/**
 * 在下载游戏前先验证游戏，根据 GameKey 去服务端获取游戏信息
 */
+ (void) checkStatusBeforeRunGame: (NSString*)gameKey;

/**
 * 下载 config.json
 */
+ (void) downloadRemoteConfigFile;

/**
 * 更新本地 config.json
 */
+ (void) updateLocalConfigFile: (NSString*) path;

/**
 * 检查本地 manifest.json
 */
+ (void) checkLocalManifestFile;

/**
 * 下载 manifest.json
 */
+ (void) downloadRemoteManifestFile;

/**
 * 解析游戏配置文件
 */
+ (GameConfig*) parseGameConfigFile: (NSString*) path;

/**
 * 检查 main.jsc
 */
+ (void) checkEntryFile;

/**
 * 下载 main.jsc
 */
+ (void) downloadEntryFile;

/**
 * 检查 project-runtime.json
 */
+ (void) checkProjectJsonFile;

/**
 * 下载 project-runtime.json
 */
+ (void) downloadProjectJsonFile;

/**
 * 删除不相关的组
 */
+ (void) deleteNoRefGroups;

/**
 * 检查首场景资源
 */
+ (void) checkBootGroup;

/**
 * 通知进度
 */
+ (void) notifyProgress: (float)progress max:(float)max;

/**
 * 通知 PreRunGame 出错
 */
+ (void) notifyPreRunGameError;

/**
 * 开始游戏
 */
+ (void) startGame;

/**
 * 检查本地 config.json 的 md5 值是否正确
 */
+ (BOOL) isLocalConfigMD5Correct;

/**
 * 检查本地 manifest.json 的 md5 值是否正确
 */
+ (BOOL) isLocalManifestMD5Correct;

/**
 * 检查本地 project-runtime.json 的 md5 值是否正确
 */
+ (BOOL) isLocalProjectMD5Correct;

/**
 * 检查本地 main.jsc 的 md5 值是否正确
 */
+ (BOOL) isLocalEntryMD5Correct;
@end

/*
 * 下载 config.json
 */
@interface ConfigDownloadDelegateImpl : FileDownloadAdapter
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end

/**
 * 下载 mainifest.json
 */
@interface ManifestDownloadDelegateImpl : FileDownloadAdapter
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end

/**
 * 下载 main.jsc
 */
@interface EntryDownloadDelegateImpl : FileDownloadAdapter
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end

/**
 * 下载 project-runtime.json
 */
@interface ProjectDownloadDelegateImpl : FileDownloadAdapter
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end

/**
 * Boot 分组更新监听
 */
@interface OnBootGroupUpdateDelegateImpl : NSObject <OnGroupUpdateDelegate>
{
    ResGroup* resGroup;
}
- (OnBootGroupUpdateDelegateImpl*) initWith: (ResGroup*) group;
- (void) onProgressOfDownload: (long) written total:(long) total;
- (void) onSuccessOfDownload: (long) total;
- (void) onFailureOfDownload: (NSString*) errorMsg;
- (void) onSuccessOfUnzip: (long)total;
- (void) onFailureOfUnzip: (NSString*) errorMsg;
- (void) onProgressOfUnzip: (float) percent;
@end

/**
 * 下载分组资源回调
 */
@interface BootGroupDownloadImpl : FileDownloadAdapter
{
    ResGroup* resGroup;
}
- (BootGroupDownloadImpl*) initWith: (ResGroup*) resGroup;
- (void) onDownloadProgress:(double)progress;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end