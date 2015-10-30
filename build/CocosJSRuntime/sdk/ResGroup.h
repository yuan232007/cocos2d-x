//
//  ResGroup.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ResGroup : NSObject
{
    NSString *groupInfoMD5;
    NSString *groupMD5;
    NSString *groupName;
    NSInteger groupPriority;
    NSInteger groupSize;
    NSString *groupURL;
}

@property NSString *groupInfoMD5, *groupMD5, *groupName, *groupURL;
@property NSInteger groupPriority, groupSize;

-(ResGroup*) initWith: (NSString*)infoMD5 md5: (NSString*)md5 name: (NSString*) name priority: (NSInteger) priority size: (NSInteger) size url: (NSString*) url;

@end
