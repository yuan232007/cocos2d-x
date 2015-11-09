//
//  ResGroup.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"

@interface ResGroup : NSObject
{
    NSString *groupMD5;
    NSString *groupName;
    NSInteger groupPriority;
    NSInteger groupSize;
    NSString *groupURL;
    NSMutableArray *fileList;
    BOOL isUpdated;
}

@property NSString *groupMD5, *groupName, *groupURL;
@property NSInteger groupPriority, groupSize;
@property NSMutableArray *fileList;
@property BOOL isUpdated;

- (ResGroup*) initWith: (NSString*)infoMD5 md5: (NSString*)md5 name: (NSString*) name priority: (NSInteger) priority size: (NSInteger) size url: (NSString*) url files: (NSMutableArray*) files;

/**
 * 检查本组的文件是否已经是最新的
 */
- (BOOL) isUpdated: (GameInfo*) info;

/**
 * 检查所有属于本组的文件是否所有的MD5值都一样
 */
- (BOOL) isAllFilesMD5Correct: (GameInfo*)info;
@end

@interface File : NSObject
{
    NSString *md5;
    NSString *name;
}

@property NSString *md5, *name;
@end