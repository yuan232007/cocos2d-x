//
//  LoadingProgressController.h
//  CocosJSRuntime
//
//  Created by Rye on 11/6/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OnLoadingProgressDelegate.h"

@interface LoadingProgressController : NSObject
{
    NSMutableArray *LoadingInfoList;
    NSMutableDictionary *LoadingInfoDict;
    id<OnLoadingProgressDelegate> onLoadingProgressDelegate;
}

@property NSMutableArray *LoadingInfoList;
@property NSMutableDictionary *LoadingInfoDict;
@property id<OnLoadingProgressDelegate> onLoadingProgressDelegate;


- (LoadingProgressController*) init;
- (void) reset;
@end