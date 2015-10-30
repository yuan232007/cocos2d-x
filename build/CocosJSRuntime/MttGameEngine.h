//
//  MttGameEngine.h
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/19.
//
#import <Foundation/Foundation.h>
#import "MttGameEngineProtocol.h"
#import "sdk/LoadingDelegate.h"

@interface MttGameEngine : NSObject<MttGameEngineProtocol, LoadingDelegate>


@end