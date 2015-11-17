//
//  GroupVersionManager.m
//  CocosJSRuntime
//
//  Created by Rye on 11/12/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "GroupVersionManager.h"
#import "FileUtil.h"

#define GROUP_VERSION_CODE_FILE_NAME @"group-ver.json"

@implementation GroupVersionManager

- (void) init: (NSString*) currentGameRootPath 
{
    groupVersionFilePath = [currentGameRootPath stringByAppendingPathComponent:GROUP_VERSION_CODE_FILE_NAME];
    groupVersionCodeJson = (NSMutableDictionary*)[FileUtil readJsonFromFile:groupVersionFilePath];
    if (groupVersionCodeJson == nil) {
        groupVersionCodeJson = [NSMutableDictionary dictionaryWithCapacity:20];
    }
}

- (void) destory
{
    groupVersionCodeJson = nil;
}

- (void) deleteGroupVersionCode: (NSString*)groupName
{
    [self deleteGroupVersionCode:groupName toCommit:TRUE];
}

- (void) deleteGroupVersionCode:(NSString *)groupName toCommit:(BOOL)toCommit
{
    if (groupVersionCodeJson == nil) {
        NSLog(@"CocosRuntimeGroup.init wasn't invoked!, deleteVersionCode takes no effects");
        return;
    }
    
    if ([[groupVersionCodeJson allKeys] containsObject:groupName]) {
        NSLog(@"Removing (%@) in group-ver.json", groupName);
        [groupVersionCodeJson removeObjectForKey:groupName];
        if (toCommit) {
            [self commit];
        }
    }
}

- (void) setGroupVersionCode: (NSString*)groupName versionCode:(NSInteger)code
{
    [self setGroupVersionCode:groupName versionCode:code toCommit:TRUE];
}

- (void) setGroupVersionCode: (NSString*)groupName versionCode:(NSInteger)code toCommit:(BOOL)commit
{
    if (groupVersionCodeJson == nil) {
        NSLog(@"CocosRuntimeGroup.init wasn't invoked!, setVersionCode takes no effects");
        return;
    }
    
    [groupVersionCodeJson setValue:[NSNumber numberWithInteger:code] forKey:groupName];
    if (commit) {
        [self commit];
    }
}

- (NSInteger) getVersionCode: (NSString*)groupName
{
    if ([[groupVersionCodeJson allKeys] containsObject:groupName]) {
        return [[groupVersionCodeJson objectForKey:groupName] integerValue];
    }
    return -1;
}

- (void) commit
{
    if (groupVersionCodeJson == nil) {
        NSLog(@"Oops, groupVersionCodeJson is NIL, commit will take no effects");
        return;
    }
    [FileUtil writeJsonToFile:groupVersionFilePath json:groupVersionCodeJson];
}

@end
