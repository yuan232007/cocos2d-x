//
//  DownloadInfo.m
//  CocosJSRuntime
//
//  Created by Rye on 11/24/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "DownloadInfo.h"

@implementation DownloadInfo
@synthesize extension, config;

- (DownloadInfo*) initWith:(NSString *)json extension:(long)ext
{
    if (self = [super init]) {
        config = json;
        extension = ext;
    }
    return self;
}

@end
