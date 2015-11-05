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
#import "FileDownload.h"
#import "MttGameEngine.h"
#import "FileDownloadAdapter.h"

@interface PreRunGame : NSObject
+ (void) start: (GameInfo*) info proxy: (MttGameEngine*) proxy;
+ (void) reset;

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
+ (void) notifyProgress: (NSInteger) progress isFailed: (BOOL) isFailed;
+ (void) notifyGameInitEnd;

/**
 * 开始游戏
 */
+ (void) startGame;

/**
 * 检查本地 config.json 的 md5 值是否正确
 */
+ (BOOL) isLocalConfigMD5Correct;
+ (BOOL) isLocalBootGroupMD5Correct;

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

+ (void) preloadBootGroup;
@end

/*
 * 下载 config.json
 */
@interface ConfigDownloadDelegateImpl : FileDownloadAdapter
- (NSString*) onTempDownloaded:(NSString *)locationPath;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end

/**
 * 下载 mainifest.json
 */
@interface ManifestDownloadDelegateImpl : FileDownloadAdapter
- (NSString*) onTempDownloaded:(NSString *)locationPath;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end

/**
 * 下载 main.jsc
 */
@interface EntryDownloadDelegateImpl : FileDownloadAdapter
- (NSString*) onTempDownloaded:(NSString *)locationPath;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end

/**
 * 下载 project-runtime.json
 */
@interface ProjectDownloadDelegateImpl : FileDownloadAdapter
- (NSString*) onTempDownloaded:(NSString *)locationPath;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
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
- (NSString*) onTempDownloaded:(NSString *)locationPath;
- (void) onDownloadSuccess:(NSString *)path;
- (void) onDownloadFailed;
@end