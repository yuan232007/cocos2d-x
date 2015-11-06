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
    [loadingProgressController setOnLoadingProgressDelegate: [[OnLoadingProgressDelegateImpl alloc]init]];
}

+ (void) startPreRuntime: (GameInfo*) info proxy: (MttGameEngine*) proxy
{
    if (proxy == nil) {
        NSLog(@"===> ERROR: Proxy is empty.");
        return;
    }
    NSLog(@"===> CocosRuntime startPreRuntime");
    [PreRunGame start:info proxy:proxy];
}

+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate
{
    [CocosRuntimeGroup preloadResGroups:groupsString delegate:delegate];
}

+ (void) notifyProgress: (NSInteger) progressOffset unzipDone: (BOOL) unzipDone isFailed: (BOOL) isFailed
{
    // todo 用于通知回调
    /*
    if (isFailed) {
        [resDownloadDelegate onLoadingProgress:(downloadGroupSize + progressOffset) :true];
    } else {
        NSInteger progress = 1.0 * (downloadGroupSize + progressOffset) / totalSize * 100;
        [resDownloadDelegate onLoadingProgress:progress :false];
        
        if (unzipDone) {
            downloadGroupSize += progressOffset;
        }
    }*/
}

- (LoadingProgressController*) getLoadingProgressController
{
    return loadingProgressController;
}

@end

@implementation OnLoadingProgressDelegateImpl

- (void) onUpdateOfLoadingInfo: (LoadingInfo*) currentLoadingInfo
{
    
}

- (void) onAllLoaingFinish
{
    
}

@end


