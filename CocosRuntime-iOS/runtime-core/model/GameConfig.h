//
//  GameConfig.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GameConfig : NSObject
{
    /* 游戏描述 */
    NSString *descript;
    
    /* 设计分辨率高度 */
    NSInteger designResolutionHeight;
    /* 设计分辨率适配原则 */
    NSString *designResolutionPolicy;
    /* 设计分辨率宽度 */
    NSInteger designResolutionWidth;
    
    /* 引擎语言 */
    NSString *engine;
    /* 引擎版本 */
    NSString *engineVersion;
    
    /* 入口文件 md5 */
    NSString *entryMD5;
    /* 入口文件名称 */
    NSString *entryName;
    /* 入口文件大小 */
    NSInteger entrySize;
    
    /* 游戏名称 */
    NSString *gameName;
    /* 游戏类型 */
    NSString *gameType;
    
    /* 分组清单文件md5 */
    NSString *manifestMD5;
    /* 分组清单文件名 */
    NSString *manifestName;
    /* 分组清单文件大小 */
    NSInteger manifestSize;
    
    /* 游戏横竖屏 */
    NSString *orientation;
    /* 游戏包名 */
    NSString *packageName;
    
    /* 项目文件md5 */
    NSString *projectMD5;
    /* 项目文件名 */
    NSString *projectName;
    /* 游戏引擎配置相关 */
    NSInteger projectSize;
    /* 安全码 */
    NSString *security;
    /* 打包版本工具 */
    NSInteger toolVersion;
    /* 游戏版本号 */
    NSInteger versionCode;
    /* 游戏版本名 */
    NSString *versionName;
    
    NSMutableDictionary* allConfig;
}

@property NSString *descript, *designResolutionPolicy, *entryMD5, *entryName, *gameName, *gameType, *manifestMD5, *manifestName, *orientation, *packageName, *projectMD5, *projectName, *security, *versionName, *engine, *engineVersion;

@property NSInteger designResolutionHeight, designResolutionWidth, entrySize, manifestSize, projectSize, versionCode, toolVersion;

@property NSMutableDictionary* allConfig;

+ (GameConfig*) parseFromFile: (NSString*) path;

- (NSMutableDictionary*)getGameConfig;

@end
