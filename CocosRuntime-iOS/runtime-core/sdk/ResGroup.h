//
//  ResGroup.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"
#import "GroupPatch.h"

@interface ResGroup : NSObject
{
    NSString *groupMD5;
    NSString *groupName;
    NSInteger groupPriority;
    NSInteger groupSize;
    NSString *groupURL;
    NSMutableArray *fileList;
    BOOL isUpdated;
    NSMutableDictionary *groupPatches;
}

@property NSString *groupMD5, *groupName, *groupURL;
@property NSInteger groupPriority, groupSize;
@property NSMutableArray *fileList;
@property BOOL isUpdated;
@property NSMutableDictionary *groupPatches;

- (ResGroup*) initWith: (NSString*)infoMD5 md5: (NSString*)md5 name: (NSString*) name priority: (NSInteger) priority size: (NSInteger) size url: (NSString*) url files: (NSMutableArray*) files patches:(NSMutableDictionary*)patches;

/**
 * 检查本组的文件是否已经是最新的
 */
- (BOOL) isUpdated: (GameInfo*) info;

/**
 * 检查所有属于本组的文件是否所有的MD5值都一样
 */
- (BOOL) isAllFilesMD5Correct: (GameInfo*)info;

/**
 * 根据补丁名字获取补丁
 */
- (GroupPatch*) getPatch: (NSString*) patchName;
@end

