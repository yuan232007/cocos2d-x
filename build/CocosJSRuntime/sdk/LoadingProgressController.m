//
//  LoadingProgressController.m
//  CocosJSRuntime
//
//  Created by Rye on 11/6/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "LoadingProgressController.h"

@implementation LoadingProgressController

@synthesize LoadingInfoList, LoadingInfoDict,onLoadingProgressDelegate;

- (LoadingProgressController*) init
{
    self = [super init];
//    self.LoadingInfoList = [NSMutableArray arrayWithCapacity:10];
//    self.LoadingInfoDict = [NSMutableDictionary dictionaryWithCapacity:10];
    return self;
}

- (void) reset
{
    
}
@end
