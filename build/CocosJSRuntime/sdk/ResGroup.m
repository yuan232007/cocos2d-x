//
//  ResGroup.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "ResGroup.h"

@implementation ResGroup

@synthesize groupInfoMD5, groupMD5, groupName, groupURL;
@synthesize groupPriority, groupSize;

-(ResGroup*) initWith:(NSString *)infoMD5 md5:(NSString *)md5 name:(NSString *)name priority:(NSInteger)priority size:(NSInteger)size url:(NSString *)url
{
    if (self = [super init]) {
        self.groupInfoMD5 = infoMD5;
        self.groupMD5 = md5;
        self.groupName = name;
        self.groupURL = url;
        self.groupPriority = priority;
        self.groupSize = size;
    }
    return self;
}

@end
