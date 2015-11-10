//
//  CocosRuntime.h
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"
#import "FileDownloadAdapter.h"
#import "ResGroup.h"
#import "OnLoadingProgressDelegate.h"
#import "LoadingProgressController.h"
#import "LoadingAdapter4Tencent.h"


@interface CocosRuntime : NSObject
+ (void) initialize;
+ (void) startPreRuntime: (GameInfo*) info delegate: (id<LoadingDelegate>) delegate;
+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate;
+ (LoadingProgressController*) getLoadingProgressController;
@end

