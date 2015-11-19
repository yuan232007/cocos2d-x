#import "MttGameEngineFactory.h"
#import "MttGameEngine.h"

@implementation MttGameEngineFactory

+ (id<MttGameEngineProtocol>)CreateGameRuntimeEngine
{
    return [[MttGameEngine alloc] init];
}

@end