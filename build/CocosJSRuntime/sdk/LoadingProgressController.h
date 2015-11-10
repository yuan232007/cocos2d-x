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
    NSMutableArray *loadingInfoList;
    NSMutableDictionary *loadingInfoDict;
    NSInteger currentLoadingIndex;
    id<OnLoadingProgressDelegate> onLoadingProgressDelegate;
}

@property NSMutableDictionary *loadingInfoDict;
@property id<OnLoadingProgressDelegate> onLoadingProgressDelegate;

- (LoadingProgressController*) init;
- (LoadingProgressController*) initWith: (id<OnLoadingProgressDelegate>) delegate;
- (void) reset;
- (void) setLoadingInfoList: (NSMutableArray*) list;
- (void) setCurrentLoadingIndex: (NSInteger) index;
- (void) setCUrrentLoadingIndexByName: (NSString*) name;

/**
 * 通知所有的载入操作都完成
 */
- (void) notifyAllLoadingFinish;

/**
 * 将载入单元的百分比转化成全部的载入百分比进度
 */
- (float) percentFromSingleToGlobal: (float)singlePercent;
@end