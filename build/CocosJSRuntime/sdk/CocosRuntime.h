//
//  CocosRuntime.h
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameInfo.h"
#import "MttGameEngine.h"

@interface CocosRuntime : NSObject
+ (void) startPreRuntime: (GameInfo*) info proxy: (MttGameEngine*) proxy;
@end
