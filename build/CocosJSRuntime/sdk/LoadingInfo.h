//
//  LoadingInfo.h
//  CocosJSRuntime
//
//  Created by Rye on 11/6/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

enum LoadingType
{
    PROGRESS,
    WAIT
};

@interface LoadingInfo : NSObject
{
    NSString *loadingName;
    NSString *loadingTip;
    NSInteger percentOfTotal; // 0 ~ 100
    enum LoadingType loadingType;
    float startPercent;
    NSInteger index;
}

@property NSString *loadingName, *loadingTip;
@property NSInteger percentOfTotal, index;
@property enum LoadingType loadingType;
@property float startPercent;

- (LoadingInfo*) initWith: (NSString*)name percent:(NSInteger)percent type:(enum LoadingType)type tip:(NSString*)tip;
@end


