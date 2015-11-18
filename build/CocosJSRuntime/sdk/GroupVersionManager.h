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
- (void) deleteGroupVersionCode: (NSString*)groupName;
- (void) deleteGroupVersionCode:(NSString *)groupName toCommit:(BOOL)toCommit;
- (void) setGroupVersionCode: (NSString*)groupName versionCode:(NSInteger)code;
- (void) setGroupVersionCode: (NSString*)groupName versionCode:(NSInteger)code toCommit:(BOOL)commit;
- (NSInteger) getVersionCode: (NSString*)groupName;
- (void) commit;
@end
