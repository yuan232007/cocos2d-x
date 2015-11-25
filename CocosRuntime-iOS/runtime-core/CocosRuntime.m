//
//  CocosRuntime.m
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "CocosRuntime.h"
#import "PreRunGame.h"
#import "CocosRuntimeGroup.h"
#import "FileUtil.h"

/**/
static GameInfo *gameInfo = nil;

@implementation CocosRuntime
+ (void) initialize
{
}

+ (void) startPreRuntime: (NSString*) gameKey delegate: (id<LoadingDelegate>) delegate
{
    if (delegate == nil) {
        NSLog(@"===> ERROR: Proxy is empty.");
        return;
    }
    NSLog(@"===> CocosRuntime startPreRuntime");
    [PreRunGame start:gameKey delegate:delegate];
}

+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate
{
    [CocosRuntimeGroup preloadResGroups:groupsString delegate:delegate];
}

+ (void) downloadAvatarImageFile: (NSString*)config extension:(long)ext callback:(RTImageCallback)callback;
{
    [ImageDownloader downloadImageFile:config extesion:ext callback:callback];
}

+ (void) reset
{
    [PreRunGame reset];
    [CocosRuntimeGroup reset];
}

@end
