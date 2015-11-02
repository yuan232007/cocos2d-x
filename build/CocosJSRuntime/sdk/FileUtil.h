//
//  FileUtil.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"
#import "ResGroup.h"
#import "GameConfig.h"

static NSString* remoteConfigFileNamePrefix = @"config.json.remote";
static NSString* configFileName = @"config.json";

@interface FileUtil : NSObject
/**
 * 获取 CocosRuntime 文件存取根目录
 * $CacheRootPath/CocosRuntime
 */
+ (NSString*) getCocosRuntimeRootPath;

/**
 * 获取游戏存储根目录
 * $CacheRootPath/CocosRuntime/Games
 */
+ (NSString*) getGamesPath;

/**
 * 获取服务端下载的 config.json 的存储路径
 * $CacheRootPath/CocosRuntime/Games/config.json.remote.$GameKey
 */
+ (NSString*) getRemoteConfigPath: (GameInfo*) info;

/**
 * 获取游戏根目录
 * $CacheRootPath/CocosRuntime/Games/$GameKey
 */
+ (NSString*) getGameRootPath: (GameInfo*) info;

/**
 * 获得游戏的 config.json 文件
 * $CacheRootPath/CocosRuntime/Games/$GameKey/config.json
 */
+ (NSString*) getLocalConfigPath: (GameInfo*) info;

/**
 * 获得游戏的 manifest.json 文件
 * $CacheRootPath/CocosRuntime/Games/$GameKey/manifest.json
 */
+ (NSString*) getLocalManifestPath: (GameInfo*) info :(GameConfig*) config;

/**
 * 获得游戏的 project-runtime.json 文件
 * $CacheRootPath/CocosRuntime/Games/$GameKey/project-runtime.json
 */
+ (NSString*) getLocalProjectPath: (GameInfo*) info :(GameConfig*) config;

/**
 * 获得游戏的 main.jsc 文件
 * $CacheRootPath/CocosRuntime/Games/$GameKey/main.jsc
 */
+ (NSString*) getLocalEntryPath: (GameInfo*) info :(GameConfig*) config;

/**
 * 获取游戏组存储根路径
 */
+ (NSString*) getLocalGameGroupRootPath: (GameInfo*) info;

/**
 * 根据 ResGroup 和 GameInfo 获取本地 Group 的存放路径
 */
+ (NSString*) getLocalGroupPath: (GameInfo*) info group: (ResGroup*) group;

/**
 * 获得游戏的 boot.cpk 文件
 * $CacheRootPath/CocosRuntime/Games/$GameKey/boot.cpk
 */
+ (NSString*) getLocalBootGroupPath: (GameInfo*) info group: (GameConfig*) config;

/**
 * 确保目录存在, 会补全中间缺少的目录，如果创建出错则抛出异常
 */
+ (void) ensureDirectory: (NSString*) path;

/**
 * 获取父目录
 */
+ (NSString*) getParentDirectory: (NSString*) path;

/**
 * 获取文件名
 */
+ (NSString*) getBaseName: (NSString*) path;

/**
 * 移动文件
 */
+ (void) moveFileFrom: (NSString*) fromPath to: (NSString*) toPath overwrite: (BOOL) overwrite;

/*
 * 判断文件是否存在
 */
+ (BOOL) fileExists: (NSString*) path;

/*
 * 从文件读取 JSON 数据
 */
+ (NSJSONSerialization*) readJsonFromFile: (NSString*) path;

/**
 * 将 JSON 数据写入到文件中
 */
+ (void) writeJsonToFile: (NSJSONSerialization*) json;

/**
 * 获得文件的 md5 值
 */
+ (NSString*) getFileMD5: (NSString*) path;

/**
 * 获取配置文件名
 */
+ (NSString*) getConfigFileName;
@end
