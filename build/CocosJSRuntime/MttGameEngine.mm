#import "MttGameEngine.h"

#include "ScriptingCore.h"
#import "cocos2d.h"
#import "CocosDelegate.h"
#import "platform/ios/CCEAGLView-ios.h"
#include "audio/include/SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h"

#import "CocosRuntime.h"
#import "ChannelConfig.h"
#import "CocosRuntimeGroup.h"

using namespace CocosDenshion;

static CocosAppDelegate s_application;

@interface MttGameEngine()
@property (nonatomic, weak) id<MttGameEngineDelegate> delegate;
@end

@implementation MttGameEngine

//初始化游戏引擎
- (void)game_engine_init:(NSString*)jsonStr
{
    NSLog(@"game_engine_init");
    // todo
    NSString* gameDownloadUrl = @"http://192.168.31.236:8888/";
    NSString* gameKey = @"Ryeeeeee";
    NSString* gameName = @"TestGameDemo";
    NSString* gameVersionName = @"1.0";
    NSInteger gameVersionCode = 1;
    
    NSString *channelRuntimeRootPath = [NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, true)[0] stringByAppendingString:@"/CocosRuntime"];
    [ChannelConfig setCocosRuntimeRootPath: channelRuntimeRootPath];
    
    GameInfo* gameInfo = [[GameInfo alloc] initWithKey:gameKey withUrl:gameDownloadUrl withName:gameName withVersionName:gameVersionName withVersionCode:gameVersionCode];
    MttGameEngine* a = self;
    [CocosRuntime startPreRuntime:gameInfo proxy:a];
}

//得到用于显示的view
- (UIView*)game_engine_get_view;
{
    auto orientation = [UIApplication sharedApplication].statusBarOrientation;
    auto screenSize = [UIScreen mainScreen].bounds.size;
    
    if (UIInterfaceOrientationIsLandscape(orientation)) {
        NSLog(@"Interface orientation is landscape");
    } else {
        NSLog(@"Interface orientation is portrait");
    }
    
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: CGRectMake(0, 0, screenSize.width, screenSize.height)//[window bounds]
                                         pixelFormat: kEAGLColorFormatRGBA8
                                         depthFormat: GL_DEPTH24_STENCIL8_OES
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    [eaglView setMultipleTouchEnabled:YES];
    
    auto glview = cocos2d::GLViewImpl::createWithEAGLView((__bridge void*)eaglView);
    if(glview != nullptr)
    {
        cocos2d::Director::getInstance()->setOpenGLView(glview);
        cocos2d::Application::getInstance()->run();
    }
    
    return eaglView;
}

//暂停游戏
- (void)game_engine_onPause
{
    NSLog(@"game_engine_onPause");
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

//恢复游戏
- (void)game_engine_onResume
{
    NSLog(@"game_engine_onResume");
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

//退出游戏
- (void)game_engine_onStop
{
    NSLog(@"game_engine_onStop");
    
    SimpleAudioEngine::getInstance()->stopAllEffects();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::end();
    
    cocos2d::Director::getInstance()->end();
}

//设置GameEngineRuntimeProxy对象
- (void)game_engine_set_runtime_proxy:(id<MttGameEngineDelegate>)proxy
{
    self.delegate = proxy;
    NSLog(@"game_engine_set_runtime_proxy");
    
    if (self.delegate) {
        //[self testEngineProxy];
    } else {
        NSLog(@"game_engine_set_runtime_proxy error, nil");
    }
}

//调用某个方法， method为方法名， bundle存有方法所用的参数
- (void)game_engine_invoke_method:(NSString*)method bundle:(NSDictionary*)bundle
{
    NSLog(@"game_engine_invoke_method");
}

//获取游戏引擎key所对应的的值
- (id)game_engine_get_value:(NSString*)key
{
    NSLog(@"game_engine_get_value key : %@", key);
    return nil;
}

//x5通过这个接口发送消息给game engine
- (void)game_engine_send_msg:(NSDictionary*)jsonObj
{
    NSLog(@"game_engine_send_msg");
}

- (void) onLoadingProgress:(NSInteger)progress :(bool) isFailed;
{
    NSLog(@"===> onLoadingProgress: progress:%ld isFailed:%d", (long)progress, isFailed);
}

- (void) onPreRunGameCompleted
{
    NSLog(@"===> onPreRunGameCompleted");
    [CocosRuntimeGroup preloadResGroups:@"docs:examples:src" delegate:self];
}

- (void)testEngineProxy
{
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_get_value:)]) {
        [self.delegate x5GamePlayer_get_value:nil];
    }

    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_set_value:value:)]) {
        [self.delegate x5GamePlayer_set_value:nil value:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_invoke_Method:bundle:)]) {
        [self.delegate x5GamePlayer_invoke_Method:nil bundle:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_refresh_token:callback:)]) {
        [self.delegate x5GamePlayer_refresh_token:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_login:callback:)]) {
        [self.delegate x5GamePlayer_login:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_logout:callback:)]) {
        [self.delegate x5GamePlayer_logout:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_get_game_friends:callback:)]) {
        [self.delegate x5GamePlayer_get_game_friends:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_pay:callback:)]) {
        [self.delegate x5GamePlayer_pay:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_share:callback:)]) {
        [self.delegate x5GamePlayer_share:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_getUserInfo:callback:)]) {
        [self.delegate x5GamePlayer_getUserInfo:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_getAvailableLoginType:callback:)]) {
        [self.delegate x5GamePlayer_getAvailableLoginType:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_send_to_desktop:callback:)]) {
        [self.delegate x5GamePlayer_send_to_desktop:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_open_topicCircle:callback:)]) {
        [self.delegate x5GamePlayer_open_topicCircle:nil callback:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_send_msg:)]) {
        [self.delegate x5GamePlayer_send_msg:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(x5GamePlayer_stop_game_engine)]) {
        [self.delegate x5GamePlayer_stop_game_engine];
    }
}

@end