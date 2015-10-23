//
//  MttGameEngineFramework.h
//  mtt
//
//  Created by stevencai on 15/9/29.
//  Copyright (c) 2015年 Tencent. All rights reserved.
//

#import "MttGameEngineFramework.h"
#import <objc/NSObject.h>
#import <dlfcn.h>

extern void* s_dylibHandle;

@interface MttGameEngineFramework()
@property (nonatomic, strong) id<MttGameEngineProtocol>   engineGame;
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

- (UIView*)getNavigationView
{
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    
    UIView* navigationView = [[UIView alloc] initWithFrame:CGRectMake(screenSize.width - 110, 100, 100, 200)];
    
    UIButton * quitButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [quitButton setFrame:CGRectMake(0, 0, 100, 30)];
    [quitButton setBackgroundColor:[UIColor darkGrayColor]];
    [quitButton setTitle:@"quit" forState:UIControlStateNormal];
    [quitButton addTarget:self action:@selector(testQuitEngine) forControlEvents:UIControlEventTouchUpInside];
    [navigationView addSubview:quitButton];
    
    UIButton * pauseButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [pauseButton setFrame:CGRectMake(0, 40, 100, 30)];
    [pauseButton setBackgroundColor:[UIColor darkGrayColor]];
    [pauseButton setTitle:@"pause" forState:UIControlStateNormal];
    [pauseButton addTarget:self action:@selector(testPauseEngine) forControlEvents:UIControlEventTouchUpInside];
    [navigationView addSubview:pauseButton];
    
    UIButton * resumeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [resumeButton setFrame:CGRectMake(0, 80, 100, 30)];
    [resumeButton setBackgroundColor:[UIColor darkGrayColor]];
    [resumeButton setTitle:@"resume" forState:UIControlStateNormal];
    [resumeButton addTarget:self action:@selector(testResumeEngine) forControlEvents:UIControlEventTouchUpInside];
    [navigationView addSubview:resumeButton];
    
    self.navigationView = navigationView;
    
    return navigationView;
}

- (void)testQuitEngine
{
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onStop)]) {
        [self.engineGame game_engine_onStop];
        
        if (self.navigationView != nil) {
            [self.navigationView removeFromSuperview];
            self.navigationView = nil;
        }
        
        if (s_dylibHandle) {
            dlclose(s_dylibHandle);
            s_dylibHandle = NULL;
        }
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

- (void)testEngineFunction:(UIView *)rootView
{
    if (nil == self.engineGame) {
        NSLog(@"h5game engine nil!");
        return;
    }
    
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_set_runtime_proxy:)]) {
        [self.engineGame game_engine_set_runtime_proxy:self];
    }
    
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_init:)]) {
        [self.engineGame game_engine_init:nil];
    }
    
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_get_view)]) {
        UIView* view = [self.engineGame game_engine_get_view];
        if (nil == view) {
            printf("view is nil\n");
        } else {
            if (rootView != nil) {
                [rootView addSubview:view];
                
                [rootView addSubview:[self getNavigationView]];
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

- (id)x5GamePlayer_get_value:(NSString*)key
{
    NSLog(@"x5GamePlayer_get_value");
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
    NSLog(@"x5GamePlayer_send_msg");
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