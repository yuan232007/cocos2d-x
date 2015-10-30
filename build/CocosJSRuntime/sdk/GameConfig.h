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
    NSString *bootGroupMD5;
    NSString *bootGroupName;
    NSInteger bootGroupSize;
    
    NSString *descript;
    
    NSInteger designResolutionHeight;
    NSString *designResolutionPolicy;
    NSInteger designResolutionWidth;
    
    NSString *entryMD5;
    NSString *entryName;
    NSInteger entrySize;
    
    NSString *gameName;
    NSString *gameType;
    
    NSString *manifestMD5;
    NSString *manifestName;
    NSInteger manifestSize;
    
    NSString *orientation;
    NSString *packageName;
    
    NSString *projectMD5;
    NSString *projectName;
    NSInteger projectSize;
    
    NSString *runtimeVersion;
    NSString *security;
    NSInteger versionCode;
    NSString *versionName;
}

@property NSString *bootGroupMD5, *bootGroupName, *descript, *designResolutionPolicy, *entryMD5, *entryName, *gameName, *gameType, *manifestMD5, *manifestName, *orientation, *packageName, *projectMD5, *projectName, *runtimeVersion, *security, *versionName;

@property NSInteger bootGroupSize, designResolutionHeight, designResolutionWidth, entrySize, manifestSize, projectSize, versionCode;

+ (GameConfig*) parseFromFile: (NSString*) path;

@end
