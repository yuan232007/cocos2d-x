//
//  LoadingAdapter4Tencent.m
//  CocosJSRuntime
//
//  Created by Rye on 11/6/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "LoadingAdapter4Tencent.h"

@implementation LoadingAdapter4Tencent

- (LoadingAdapter4Tencent*) initWith:(RTPreloadCallback)callback
{
    self = [super init];
    if (self != nil) {
        reloadCallback = callback;
    }
    
    return self;
}

- (void) onLoadingError
{
    NSLog(@"===> LoadingAdapter4Tencent onLoadingError");
    reloadCallback(PROGRESS_INVALID, TRUE);
}

- (void) onLoadingCompleted
{
    NSLog(@"===> LoadingAdapter4Tencent onLoadingCompleted");
    reloadCallback(PROGRESS_MAX, FALSE);
}

- (void) onLoadingProgress:(float)progress max:(float)max
{
    if (progress == max) {
        return;
    }
    reloadCallback(((progress / max) * PROGRESS_MAX), FALSE);
    NSLog(@"########## %f", ((progress / max) * PROGRESS_MAX));
}

@end
