#import <Foundation/Foundation.h>
#import "MttGameEngineProtocol.h"

@interface MttGameEngineFactory : NSObject

+ (id<MttGameEngineProtocol>)CreateGameRuntimeEngine;

@end