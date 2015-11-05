#import <Foundation/Foundation.h>
#import "MttGameEngineProtocol.h"

@interface Cocosv3GameEngineFactory : NSObject

+ (id<MttGameEngineProtocol>)CreateGameRuntimeEngine;

@end