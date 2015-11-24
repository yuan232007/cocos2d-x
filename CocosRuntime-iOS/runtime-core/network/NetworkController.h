//
//  NetworkController.h
//  CocosJSRuntime
//
//  Created by Rye on 11/13/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"

typedef enum : NSInteger {
    RTServerAddress_ONLINE,//线上游戏用
    RTServerAddress_STAGING,//准线上游戏
    RTServerAddress_SANDBOX//沙盒
} RTServerAddress;

@interface NetworkController : NSObject

/**
 * 根据 GameKey 获取游戏信息
 */
+ (void) requestGameInfoByGameKey: (NSString*)gameKey callback:(void (^)(GameInfo *gameInfo, BOOL isFailed))callback;
+ (NSURLSession*) getCurrentSession: (id<NSURLSessionDelegate>)delegate;

+ (void)setRTServerAddress:(RTServerAddress)address;

@end
