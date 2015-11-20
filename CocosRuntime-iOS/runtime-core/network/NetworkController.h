//
//  NetworkController.h
//  CocosJSRuntime
//
//  Created by Rye on 11/13/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"

@interface NetworkController : NSObject

/**
 * 根据 GameKey 获取游戏信息
 */
+ (void) requestGameInfoByGameKey: (NSString*)gameKey callback:(void (^)(GameInfo *gameInfo, BOOL isFailed))callback;
+ (NSURLSession*) getCurrentSession: (id<NSURLSessionDelegate>)delegate;

@end
