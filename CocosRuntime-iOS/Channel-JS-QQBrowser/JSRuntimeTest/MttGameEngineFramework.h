#import <Foundation/Foundation.h>
#import "MttGameEngineDelegate.h"
#import "MttGameEngineProtocol.h"

@interface MttGameEngineFramework : NSObject<MttGameEngineDelegate>

+ (MttGameEngineFramework *)sharedInstance;

- (void)updateRuntimeEngine:(id<MttGameEngineProtocol>)engine;

- (void)testEngineFunction:(UIView*)rootView;

@end