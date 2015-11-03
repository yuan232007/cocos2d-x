#import "MttGameEngineFramework.h"
#import <objc/NSObject.h>

@interface MttGameEngineFramework()
@property (nonatomic, strong) id<MttGameEngineProtocol>   engineGame;
@property (strong, nonatomic) UIView *rootView;
@end

@implementation MttGameEngineFramework

+ (MttGameEngineFramework *)sharedInstance
{
    static dispatch_once_t once;
    static MttGameEngineFramework * __singleton__;
    dispatch_once( &once, ^{ __singleton__ = [[MttGameEngineFramework alloc] init]; } );
    return __singleton__;
}

- (void)updateRuntimeEngine:(id<MttGameEngineProtocol>)engine
{
    self.engineGame = engine;
}

- (void)testEngineFunction:(UIView *)rootView
{
    if (nil == self.engineGame) {
        NSLog(@"h5game engine nil!");
        return;
    }
    
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_set_runtime_proxy:)]) {
        [self.engineGame game_engine_set_runtime_proxy:self];
    }
    
    self.rootView = rootView;
    
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_init:)]) {
        /*char tmp[300];
        sprintf(tmp, "{gameId:\"%s\", engineName:\"%s\", localDebug:1, orientation:\"%s\", gameName:\"%s\", gameIconUrl:\"%s\", runUrl:\"%s\",gameUrl : \"%s\",ext:\"{gameKey:\"%s\", enableSilentDownload:false, packageName:\"%s\", resUrl:\"%s\", emotion:\"%s\"}\"}",
                "2466856218",
                "cocos-v3",
                "portrait",
                "打飞机游戏",
                "http://tencent.cocosruntime.com/tencent/unittest/icon.png",
                "http://tencent.cocosruntime.com/tencent/unittest/gameshare.html",
                "http://tencent.cocosruntime.com/tencent/unittest/gameshare.html",
                "ULY1R3O6MB",
                "org.cocos2dx.moonwarriors.v3",
                "http://192.168.54.90:8010/rt-test/moonwarriors/",
                "emotiontest");*/
        
        /*NSString *gameInfo = [NSString stringWithFormat:@"{gameId: %@, engineName: %@, localDebug: 1,\
        orientation : %@, gameName : %@, gameIconUrl : %@, runUrl: %@, gameUrl : %@,\
        ext: { gameKey: %@, enableSilentDownload: false, packageName: %@, resUrl: %@, emotion: %@}}",
                              @"2466856218",
                              @"cocos-v3",
                              @"portrait",
                              @"打飞机游戏",
                              @"http://tencent.cocosruntime.com/tencent/unittest/icon.png",
                              @"http://tencent.cocosruntime.com/tencent/unittest/gameshare.html",
                              @"http://tencent.cocosruntime.com/tencent/unittest/gameshare.html",
                              @"ULY1R3O6MB",
                              @"org.cocos2dx.moonwarriors.v3",
                              @"http://192.168.54.90:8010/rt-test/moonwarriors/",
                              @"emotiontest"];*/
        
        [self.engineGame game_engine_init:nil];
    }
}

- (id)x5GamePlayer_get_value:(NSString*)key
{
    NSLog(@"x5GamePlayer_get_value");
    
    if ([key isEqualToString:@"CacheDir"]) {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        
        return [documentsDirectory stringByAppendingString:@"/engineFile/cocos-v3/cache/"];
    }
    
    if ([key isEqualToString:@"LibDir"]) {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        
        return [documentsDirectory stringByAppendingString:@"/engineFile/cocos-v3/"];
    }
    
    if ([key isEqualToString:@"TokenDir"]) {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        
        return [documentsDirectory stringByAppendingString:@"/engineFile/cocos-v3/token/"];
    }
    
    return nil;
}

- (BOOL)x5GamePlayer_set_value:(NSString*)key value:(id)value
{
    NSLog(@"x5GamePlayer_set_value");
    return NO;
}

- (void)x5GamePlayer_stop_game_engine
{
    NSLog(@"x5GamePlayer_stop_game_engine");
}

- (id)x5GamePlayer_invoke_Method:(NSString*)method bundle:(NSDictionary*)bundle
{
    NSLog(@"x5GamePlayer_invoke_Method");
    return nil;
}

- (void)x5GamePlayer_refresh_token:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_refresh_token");
}

- (void)x5GamePlayer_login:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_login");
}

- (void)x5GamePlayer_logout:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_logout");
}

- (void)x5GamePlayer_get_game_friends:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_get_game_friends");
}

- (void)x5GamePlayer_pay:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_pay");
}

- (void)x5GamePlayer_share:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_share");
}

- (void)x5GamePlayer_getUserInfo:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_getUserInfo");
}

- (void)x5GamePlayer_getAvailableLoginType:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_getAvailableLoginType");
}

- (void)x5GamePlayer_send_msg:(NSDictionary*)jsonObj
{
    //NSLog(@"x5GamePlayer_send_msg");
    NSString* msg = [jsonObj objectForKey:@"type"];
    if (msg != nil && [msg isEqualToString:MSG_ON_LOAD_GAME_END]) {
        if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_get_view)]) {
            UIView* view = [self.engineGame game_engine_get_view];
            if (nil == view) {
                printf("view is nil\n");
            } else {
                if (self.rootView != nil) {
                    [self.rootView addSubview:view];
                }
            }
        }
        
        if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onPause)]) {
            [self.engineGame game_engine_onPause];
        }
        
        if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onResume)]) {
            [self.engineGame game_engine_onResume];
        }
        
        if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_invoke_method:bundle:)]) {
            [self.engineGame game_engine_invoke_method:nil bundle:nil];
        }
        
        if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_get_value:)]) {
            [self.engineGame game_engine_get_value:nil];
        }
        
        if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_send_msg:)]) {
            [self.engineGame game_engine_send_msg:nil];
        }
    }
}

- (void)x5GamePlayer_send_to_desktop:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_send_to_desktop");
}

- (void)x5GamePlayer_open_topicCircle:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"x5GamePlayer_open_topicCircle");
}

@end