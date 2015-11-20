//
//  OnLoadingProgressDelegate.h
//  CocosJSRuntime
//
//  Created by Rye on 11/6/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LoadingInfo.h"

@protocol OnLoadingProgressDelegate

- (void) onUpdateOfLoadingInfo: (LoadingInfo*) currentLoadingInfo;
- (void) onAllLoaingFinish;

@end