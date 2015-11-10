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
static LoadingProgressController *loadingProgressController;

@implementation CocosRuntime
+ (void) initialize
{
    loadingProgressController = [[LoadingProgressController alloc] init];
    [loadingProgressController setOnLoadingProgressDelegate: [[OnLoadingProgressDelegateImpl alloc] init]];
}

+ (void) startPreRuntime: (GameInfo*) info delegate: (id<LoadingDelegate>) delegate
{
    if (delegate == nil) {
        NSLog(@"===> ERROR: Proxy is empty.");
        return;
    }
    NSLog(@"===> CocosRuntime startPreRuntime");
    [PreRunGame start:info delegate:delegate];
}

+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate
{
    [CocosRuntimeGroup preloadResGroups:groupsString delegate:delegate];
}

+ (void) preloadResGroupsInternal:(NSString *)groupsString delegate:(id<LoadingDelegate>)delegate
{
    
}

+ (LoadingProgressController*) getLoadingProgressController
{
    return loadingProgressController;
}

@end




