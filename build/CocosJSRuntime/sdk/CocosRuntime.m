//
//  CocosRuntime.m
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "CocosRuntime.h"
#import "PreRunGame.h"

static GameInfo* gameInfo = nil;

@implementation CocosRuntime
+ (void) startPreRuntime: (GameInfo*) info proxy: (MttGameEngine*) proxy
{
    if (proxy == nil) {
        NSLog(@"===> ERROR: Proxy is empty.");
        return;
    }
    NSLog(@"===> CocosRuntime startPreRuntime");
    [PreRunGame start:info proxy:proxy];
}
@end
