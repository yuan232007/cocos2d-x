//
//  MttGameEngineFramework.h
//  mtt
//
//  Created by stevencai on 15/9/29.
//  Copyright (c) 2015年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MttGameEngineDelegate.h"
#import "MttGameEngineProtocol.h"

@interface MttGameEngineFramework : NSObject<MttGameEngineDelegate>

@property (strong, nonatomic) UIView *navigationView;

+ (MttGameEngineFramework *)sharedInstance;

- (void)updateRuntimeEngine:(id<MttGameEngineProtocol>)engine;

- (void)testEngineFunction:(UIView*)rootView;

- (UIView*)getNavigationView;

- (void)testQuitEngine;
- (void)testPauseEngine;
- (void)testResumeEngine;

@end