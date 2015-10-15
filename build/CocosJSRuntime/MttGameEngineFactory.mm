//
//  MttGameEngineFactory.m
//  mtt
//
//  Created by stevencai on 15/9/29.
//  Copyright (c) 2015年 Tencent. All rights reserved.
//

#import "MttGameEngineFactory.h"
#import "MttGameEngine.h"

@implementation MttGameEngineFactory

+ (id<MttGameEngineProtocol>)CreateGameRuntimeEngine
{
    return [[MttGameEngine alloc] init];
}

@end