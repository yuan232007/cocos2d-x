//
//  GameConfig.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "GameConfig.h"

@implementation GameConfig

@synthesize descript, designResolutionPolicy, entryMD5, entryName, gameName, gameType, manifestMD5, manifestName, orientation, packageName, projectMD5, projectName, security, versionName, engine, engineVersion;

@synthesize designResolutionHeight, designResolutionWidth, entrySize, manifestSize, projectSize,
versionCode, toolVersion;

+ (GameConfig*) parseFromFile:(NSString *)path
{
    GameConfig* gameConfig = [[GameConfig alloc] init];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSData *data = [fileManager contentsAtPath: path];
    NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
    
    gameConfig.descript = [jsonDict objectForKey:@"description"];
    
    NSDictionary *resolution = [jsonDict objectForKey:@"design_resolution"];
    gameConfig.designResolutionHeight = [[resolution objectForKey:@"height"] integerValue];
    gameConfig.designResolutionWidth = [[resolution objectForKey:@"width"] integerValue];
    gameConfig.designResolutionPolicy = [resolution objectForKey:@"policy"];
    
    gameConfig.engine = [jsonDict objectForKey:@"engine"];
    gameConfig.engineVersion = [jsonDict objectForKey:@"engine_version"];
    
    NSDictionary *entry = [jsonDict objectForKey:@"entry_file"];
    gameConfig.entryMD5 = [entry objectForKey:@"md5"];
    gameConfig.entryName = [entry objectForKey:@"name"];
    gameConfig.entrySize = [[entry objectForKey:@"size"] integerValue];
    
    gameConfig.gameName = [jsonDict objectForKey:@"game_name"];
    gameConfig.gameType = [jsonDict objectForKey:@"game_type"];
    
    NSDictionary *manifest = [jsonDict objectForKey:@"manifest_file"];
    gameConfig.manifestMD5 = [manifest objectForKey:@"md5"];
    gameConfig.manifestName = [manifest objectForKey:@"name"];
    gameConfig.manifestSize = [[manifest objectForKey:@"size"] integerValue];
    
    gameConfig.orientation = [jsonDict objectForKey:@"orientation"];
    gameConfig.packageName = [jsonDict objectForKey:@"package_name"];
    
    NSDictionary *project = [jsonDict objectForKey:@"project_json_file"];
    gameConfig.projectMD5 = [project objectForKey:@"md5"];
    gameConfig.projectName = [project objectForKey:@"name"];
    gameConfig.projectSize = [[project objectForKey:@"size"] integerValue];
    
    gameConfig.security = [jsonDict objectForKey:@"security"];
    gameConfig.toolVersion = [[jsonDict objectForKey:@"tool_version"] integerValue];
    gameConfig.versionCode = [[jsonDict objectForKey:@"version_code"] integerValue];
    gameConfig.versionName = [jsonDict objectForKey:@"verison_name"];
    
    return gameConfig;
}

@end
