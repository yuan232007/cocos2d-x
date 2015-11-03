//
//  GameManifest.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "GameManifest.h"
#import "FileUtil.h"

@implementation GameManifest

@synthesize allResGroups;

+ (GameManifest*) readFromFile:(NSString *)path
{
    GameManifest *manifest = [[GameManifest alloc] init];
    NSDictionary *jsonDict = (NSDictionary*)[FileUtil readJsonFromFile: path];
    [manifest setAllResGroups: [manifest getAllResGroupsFromDict: jsonDict]];
    return manifest;
}

/* 获得游戏分组信息 */
- (NSMutableArray*) getAllResGroupsFromDict: (NSDictionary*) manifestDict
{
    NSMutableArray *resGroupArray = [manifestDict objectForKey:@"res_groups"];
    
    NSMutableArray* groups = [NSMutableArray arrayWithCapacity:20];
    for (NSDictionary* resGroupDict in resGroupArray) {
        ResGroup* resGroup = [[ResGroup alloc] init];
        [resGroup setGroupMD5:[resGroupDict objectForKey:@"md5"]];
        [resGroup setGroupName:[resGroupDict objectForKey:@"name"]];
        [resGroup setGroupPriority:[[resGroupDict objectForKey:@"priority"] integerValue]];
        [resGroup setGroupSize:[[resGroupDict objectForKey:@"size"] integerValue]];
        [resGroup setGroupURL:[resGroupDict objectForKey:@"url"]];
        [groups addObject:resGroup];
    }
    return groups;
}
@end