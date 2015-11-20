//
//  LoadingProgressController.m
//  CocosJSRuntime
//
//  Created by Rye on 11/6/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "LoadingProgressController.h"

@implementation LoadingProgressController

@synthesize loadingInfoDict, onLoadingProgressDelegate;

- (LoadingProgressController*) init
{
    self = [super init];
    return self;
}

- (LoadingProgressController*) initWith: (id<OnLoadingProgressDelegate>) delegate
{
    self = [super init];
    if (self != nil) {
        onLoadingProgressDelegate = delegate;
    }
    return self;
}

- (void) reset
{
    // todo 清楚状态
}

- (void) notifyAllLoadingFinish
{
    if (onLoadingProgressDelegate != nil) {
        [onLoadingProgressDelegate onAllLoaingFinish];
    }
    [self reset];
}

- (float) percentFromSingleToGlobal: (float)singlePercent
{
    if (loadingInfoList == nil || currentLoadingIndex < 0 || currentLoadingIndex >= loadingInfoList.count) {
        return singlePercent;
    }
    
    float startPercent = [[loadingInfoList objectAtIndex:currentLoadingIndex] startPercent];
    float globalPercent = [[loadingInfoList objectAtIndex:currentLoadingIndex] percentOfTotal] / 100.0f * singlePercent + startPercent;
    return globalPercent;
}

- (void) setLoadingInfoList: (NSMutableArray*) list
{
    loadingInfoList = list;
    NSInteger percent = 0;
    if (loadingInfoDict == nil) {
        loadingInfoDict = [NSMutableDictionary dictionaryWithCapacity:20];
    }
    
    [loadingInfoDict removeAllObjects];
    currentLoadingIndex = 0;
    
    for (NSInteger i = 0; i < loadingInfoList.count; i++) {
        LoadingInfo *info = [loadingInfoList objectAtIndex:i];
        NSLog(@"===> loading info: %@", info);
        [info setIndex:i];
        [info setStartPercent:percent];
        percent += [info percentOfTotal];
        [loadingInfoDict setValue:info forKey:[info loadingName]];
    }
    
    NSLog(@"Total percent is %ld , it should be 100", (long)percent);
}

- (void) setCurrentLoadingIndex: (NSInteger) index
{
    if (loadingInfoList == nil || index < 0 || index >= loadingInfoList.count) {
        NSLog(@"===> Invalid index:%ld", (long)index);
    } else {
        currentLoadingIndex = index;
        LoadingInfo *info = [loadingInfoList objectAtIndex:currentLoadingIndex];
        [onLoadingProgressDelegate onUpdateOfLoadingInfo:info];
    }
}

- (void) setCurrentLoadingIndexByName: (NSString*) name
{
    if (loadingInfoList != nil && loadingInfoDict != nil) {
        LoadingInfo *info = [loadingInfoDict objectForKey:name];
        if (info != nil) {
            [self setCurrentLoadingIndex:[info index]];
        } else {
            NSLog(@"===> There isn't (%@) in loading info array!", name);
        }
    } else {
        NSLog(@"===> Invalid name of loading info!");
    }
}

@end
