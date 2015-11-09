//
//  CocosRuntime.h
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"
#import "MttGameEngine.h"
#import "FileDownloadAdapter.h"
#import "ResGroup.h"
#import "OnLoadingProgressDelegate.h"
#import "LoadingProgressController.h"


@interface CocosRuntime : NSObject
+ (void) initialize;
+ (void) startPreRuntime: (GameInfo*) info proxy: (MttGameEngine*) proxy;
+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate;
+ (void) notifyProgress: (NSInteger) progressOffset unzipDone: (BOOL) unzipDone isFailed: (BOOL) isFailed;
+ (LoadingProgressController*) getLoadingProgressController;
@end

@interface OnLoadingProgressDelegateImpl : NSObject <OnLoadingProgressDelegate>

- (void) onUpdateOfLoadingInfo: (LoadingInfo*) currentLoadingInfo;
- (void) onAllLoaingFinish;
@end