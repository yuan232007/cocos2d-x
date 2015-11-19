//
//  LoadingInfo.m
//  CocosJSRuntime
//
//  Created by Rye on 11/6/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "LoadingInfo.h"

@implementation LoadingInfo

@synthesize loadingName, loadingTip, loadingType, percentOfTotal, startPercent, index;

- (LoadingInfo*) initWith:(NSString *)name percent:(NSInteger)percent type:(enum LoadingType)type tip:(NSString *)tip
{
    self = [super init];
    if (self != nil) {
        self.loadingName = name;
        self.loadingTip = tip;
        self.percentOfTotal = percent;
        self.loadingType = type;
    }
    return self;
}
@end
