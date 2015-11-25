#import "MttGameEngineFramework.h"
#import <objc/NSObject.h>
#import "UserQQBrowser.h"

@interface MttGameEngineFramework()
@property (nonatomic, strong) id<MttGameEngineProtocol>   engineGame;
@property (strong, nonatomic) UIView *rootView;
@property (strong, nonatomic) UIView *navigationView;
@property (strong, nonatomic) UIView *gameView;
@property (strong, nonatomic) UIView *gameRootView;
@property (nonatomic, strong) UIProgressView* progressView;
@property (nonatomic, strong) NSString* gameKey;
@property (nonatomic,assign) int loadProgress;
@end

@implementation MttGameEngineFramework

+ (MttGameEngineFramework *)sharedInstance
{
    static dispatch_once_t once;
    static MttGameEngineFramework * __singleton__;
    dispatch_once( &once, ^{ __singleton__ = [[MttGameEngineFramework alloc] init]; } );
    return __singleton__;
}

- (void)setTestGameKey:(NSString *)gameKey
{
    _gameKey = gameKey;
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
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    _progressView = [[UIProgressView alloc] init];
    _progressView.frame = CGRectMake(30, screenSize.height * 0.8f, screenSize.width - 60, 50);
    
    [_progressView setProgressViewStyle:UIProgressViewStyleDefault];
    _progressView.progress = 0.0;
    _progressView.trackTintColor = [UIColor grayColor];
    _progressView.progressTintColor = [UIColor greenColor];
    _progressView.transform = CGAffineTransformMakeScale(1.0f, 5.0f);
    [rootView addSubview:_progressView];
    
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_init:)]) {
        [self.engineGame game_engine_init:nil];
    }
}

- (id)x5GamePlayer_get_value:(NSString*)key
{
    NSLog(@"%s:%@", __FUNCTION__, key);
    
    if ([key isEqualToString:@"gameKey"]) {
        return _gameKey;
    }
    
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
    NSLog(@"%s\n", __FUNCTION__);
    return NO;
}

- (void)x5GamePlayer_stop_game_engine
{
    NSLog(@"%s\n", __FUNCTION__);
    [self testQuitEngine];
}

- (id)x5GamePlayer_invoke_Method:(NSString*)method bundle:(NSDictionary*)bundle
{
    NSLog(@"%s\n", __FUNCTION__);
    return nil;
}

- (void)x5GamePlayer_refresh_token:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)x5GamePlayer_login:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)x5GamePlayer_logout:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)x5GamePlayer_get_game_friends:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)x5GamePlayer_pay:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)x5GamePlayer_share:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)x5GamePlayer_getUserInfo:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)x5GamePlayer_getAvailableLoginType:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)engine_init_end
{
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_get_view)]) {
        self.gameView = [self.engineGame game_engine_get_view];
        if (nil == self.gameView) {
            printf("game view is nil\n");
        } else if(self.rootView != nil){
            CGSize screenSize = [UIScreen mainScreen].bounds.size;
            self.gameRootView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, screenSize.width, screenSize.height)];
            [self.rootView addSubview:self.gameRootView];
            [self.gameRootView addSubview:self.gameView];
            [self.gameRootView addSubview:[self getNavigationView]];
            
            [[UserQQBrowser getInstance] setDebugMode:YES];
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

- (void)updateProgress
{
    [_progressView setProgress:(_loadProgress / 100.0f)];
}

- (void)x5GamePlayer_send_msg:(NSDictionary*)jsonObj
{
    NSString* msg = [jsonObj objectForKey:@"type"];
    if (msg != nil) {
        if ([msg isEqualToString:MSG_ON_LOAD_GAME_END]) {
            [self performSelectorOnMainThread:@selector(engine_init_end) withObject:self waitUntilDone:false];
        }
        else if ([msg isEqualToString:MSG_ON_GAME_LOADING_PROGRESS]) {
            NSString* progress = [jsonObj objectForKey:@"progress"];
            _loadProgress = [progress intValue];
            [self performSelectorOnMainThread:@selector(updateProgress) withObject:self waitUntilDone:NO];
        }
    }
}

- (UIView*)getNavigationView
{
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    
    UIView* navigationView = [[UIView alloc] initWithFrame:CGRectMake(20, screenSize.height * 0.3f,
                                                                      screenSize.width * 0.18f, screenSize.height * 0.05f)];
    
    UIButton * quitButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [quitButton setFrame:CGRectMake(0, 0, screenSize.width * 0.18f, screenSize.height * 0.05f)];
    [quitButton setBackgroundColor:[UIColor darkGrayColor]];
    [quitButton setTitle:@"quit" forState:UIControlStateNormal];
    [quitButton addTarget:self action:@selector(testQuitEngine) forControlEvents:UIControlEventTouchUpInside];
    [navigationView addSubview:quitButton];
    
    self.navigationView = navigationView;
    
    return navigationView;
}

- (void)testQuitEngine
{
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onStop)]) {
        [self.engineGame game_engine_onStop];
        
        [self.gameRootView removeFromSuperview];
        [_progressView removeFromSuperview];
        
        self.gameRootView = nil;
        _progressView = nil;
        self.navigationView = nil;
        self.gameView = nil;
    }
}

- (void)testPauseEngine
{
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onPause)]) {
        [self.engineGame game_engine_onPause];
    }
}

- (void)testResumeEngine
{
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onResume)]) {
        [self.engineGame game_engine_onResume];
    }
}

- (void)x5GamePlayer_send_to_desktop:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

- (void)x5GamePlayer_open_topicCircle:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback
{
    NSLog(@"%s\n", __FUNCTION__);
}

@end