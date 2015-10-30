#import <Foundation/Foundation.h>
#import "MttGameEngineProtocol.h"
#import "sdk/LoadingDelegate.h"

@interface MttGameEngine : NSObject<MttGameEngineProtocol, LoadingDelegate>


@end