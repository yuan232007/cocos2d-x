//
//  GroupVersionManager.h
//  CocosJSRuntime
//
//  Created by Rye on 11/12/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GroupVersionManager : NSObject
{
    NSString *groupVersionFilePath;
    NSMutableDictionary *groupVersionCodeJson;
}

- (GroupVersionManager*) initWith: (NSString*) currentGameRootPath;
- (void) destory;

/**
 * 删除本地缓存的资源版本文件中对应的分组
 */
- (void) deleteGroupVersionCode: (NSString*)groupName;

/**
 * 删除本地缓存的资源版本文件中对应的分组
 */
- (void) deleteGroupVersionCode:(NSString *)groupName toCommit:(BOOL)toCommit;

/**
 * 设置本地缓存的资源版本文件中对应的分组版本
 */
- (void) setGroupVersionCode: (NSString*)groupName versionCode:(NSInteger)code;

/**
 * 设置本地缓存的资源版本文件中对应的分组
 */
- (void) setGroupVersionCode: (NSString*)groupName versionCode:(NSInteger)code toCommit:(BOOL)commit;

/**
 * 获得本地缓存的资源版本文件中对应的分组版本
 */
- (NSInteger) getVersionCode: (NSString*)groupName;

/**
 * 将文件版本信息写入本地缓存
 */
- (void) commit;
@end
