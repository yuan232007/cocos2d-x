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

/**
 * 开始下载游戏配置和首场景资源，成功之后将回调以运行游戏
 */
+ (void) startPreRuntime: (NSString*) gameKey delegate: (id<LoadingDelegate>) delegate;

/**
 * 预加载分组资源, 各个分组之间用分组名称拼接并以逗号分隔
 */
+ (void) preloadResGroups: (NSString*) groupsString delegate: (id<LoadingDelegate>) delegate;
+ (void) reset;
@end

