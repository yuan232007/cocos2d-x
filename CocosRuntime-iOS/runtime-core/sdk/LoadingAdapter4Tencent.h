//
//  LoadingAdapter4Tencent.h
//  CocosJSRuntime
//
//  Created by Rye on 11/6/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LoadingDelegate.h"

#define PROGRESS_INVALID -1
#define PROGRESS_MAX 100

typedef void(^RTPreloadCallback)(int progress, bool isFailed);

/**
 * 使用适配器模式，将不同宿主的回调通知进度接口适配到内部的 LoadingDelegate 接口
 */
@interface LoadingAdapter4Tencent : NSObject <LoadingDelegate>
{
    RTPreloadCallback reloadCallback;
}

- (LoadingAdapter4Tencent*) initWith: (RTPreloadCallback) callback;
@end
