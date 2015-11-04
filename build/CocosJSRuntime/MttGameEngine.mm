//
//  MttGameEngine.mm
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/19.
//
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
#import "FileUtil.h"

using namespace CocosDenshion;

static CocosAppDelegate s_application;

@interface MttGameEngine()

@property (nonatomic, weak) id<MttGameEngineDelegate> delegate;

@end

@implementation MttGameEngine

//初始化游戏引擎
- (void)game_engine_init:(NSString*)jsonStr
{
    if (self.delegate != nil) {
        NSString* cacheDir = [self.delegate x5GamePlayer_get_value:@"CacheDir"];
        if (cacheDir != nil) {
            [ChannelConfig setCocosRuntimeRootPath:cacheDir];
        }
        else {
            NSString *channelRuntimeRootPath = [NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, true)[0] stringByAppendingString:@"/CocosRuntime"];
            [ChannelConfig setCocosRuntimeRootPath: channelRuntimeRootPath];
        }
    }
    
    NSString* gameKey,*gameDownloadUrl,*gameName;
    if (jsonStr != nil) {
        NSDictionary * gameInfoDirt = [NSJSONSerialization JSONObjectWithData:[jsonStr dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:nil];
        if(gameInfoDirt != nil) {
            gameName = [gameInfoDirt objectForKey:@"gameName"];
            NSString* gameExt = [gameInfoDirt objectForKey:@"ext"];
            
            if (gameExt != nil) {
                NSDictionary* gameExtInfo = [NSJSONSerialization JSONObjectWithData:[gameExt dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:nil];
                
                if (gameExtInfo != nil) {
                    gameKey = [gameExtInfo objectForKey:@"gameKey"];
                    gameDownloadUrl = [gameExtInfo objectForKey:@"resUrl"];
                }
            }
        }
    }
    else {
        gameDownloadUrl = @"http://182.254.241.97/ios-runtime-test/moonwarriors";
        gameKey = @"ULY1R3O6MB";
        gameName = @"打飞机游戏";
    }
    
    GameInfo* gameInfo = [[GameInfo alloc] initWithKey:gameKey withUrl:gameDownloadUrl withName:gameName];
    [CocosRuntime startPreRuntime:gameInfo proxy:self];
    
    if(self.delegate) {
        [self.delegate x5GamePlayer_send_msg:
         [NSDictionary dictionaryWithObjectsAndKeys:MSG_ON_LOAD_GAME_START,@"type", nil]];
    }
    
    NSString* libDir = [self.delegate x5GamePlayer_get_value:@"LibDir"];
    s_application.setEngineResDir([libDir cStringUsingEncoding:NSUTF8StringEncoding]);
    
    auto gameResRoot = [[FileUtil getGameRootPath:gameInfo] cStringUsingEncoding:NSUTF8StringEncoding];
    s_application.setGameResRoot(gameResRoot);
}

//得到用于显示的view
- (UIView*)game_engine_get_view;
{
    /*
    if ([orientationConfig  isEqual: @"d"]) {
        NSNumber *value = [NSNumber numberWithInt:UIInterfaceOrientationLandscapeLeft];
        [[UIDevice currentDevice] setValue:value forKey:@"orientation"];
    } else {
        NSNumber *value = [NSNumber numberWithInt:UIInterfaceOrientationPortrait];
        [[UIDevice currentDevice] setValue:value forKey:@"orientation"];
    }*/
    
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
    
    if (self.delegate == nil) {
        NSLog(@"game_engine_set_runtime_proxy error, nil");
    }
}

//调用某个方法， method为方法名， bundle存有方法所用的参数
- (void)game_engine_invoke_method:(NSString*)method bundle:(NSDictionary*)bundle
{
}

//获取游戏引擎key所对应的的值
- (id)game_engine_get_value:(NSString*)key
{
    return nil;
}

//x5通过这个接口发送消息给game engine
- (void)game_engine_send_msg:(NSDictionary*)jsonObj
{
}

- (void) onLoadingProgress:(NSInteger)progress :(bool) isFailed;
{
    NSLog(@"onLoadingProgress:%ld", (long)progress);
    if (isFailed) {
        [self.delegate x5GamePlayer_send_msg:
         [NSDictionary dictionaryWithObjectsAndKeys:MSG_ON_NETWORK_ERR,@"type", nil]];
    } else {
        NSString* progressText = [NSString stringWithFormat:@"%ld",(long)progress];
        [self.delegate x5GamePlayer_send_msg:
         [NSDictionary dictionaryWithObjectsAndKeys:MSG_ON_GAME_LOADING_PROGRESS,@"type",
          progressText, @"progress", @"102400", @"size", nil]];
    }
}

- (void) onPreRunGameCompleted
{
    NSLog(@"onPreRunGameCompleted");
    [self.delegate x5GamePlayer_send_msg:
     [NSDictionary dictionaryWithObjectsAndKeys:MSG_ON_LOAD_GAME_END,@"type", nil]];
}

@end