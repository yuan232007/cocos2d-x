#import "Cocosv3GameEngineFactory.h"
#import "MttGameEngine.h"

@implementation Cocosv3GameEngineFactory

+ (id<MttGameEngineProtocol>)CreateGameRuntimeEngine
{
    return [[MttGameEngine alloc] init];
}

@end