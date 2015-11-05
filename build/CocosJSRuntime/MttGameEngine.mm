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

static CocosAppDelegate* s_application = nullptr;

@interface MttGameEngine()

@property (nonatomic, weak) id<MttGameEngineDelegate> delegate;

@end

@implementation MttGameEngine

//初始化游戏引擎
- (void)game_engine_init:(NSString*)gameInfoJson
{
    if (self.delegate == nil) {
        return;
    }
    
    if (s_application == nullptr) {
        s_application = new (std::nothrow) CocosAppDelegate;
    }
    
    //从浏览器配置的CacheDir、LibDir，获取失败直接返回
    NSString* cacheDir = [self.delegate x5GamePlayer_get_value:@"CacheDir"];
    NSString* libDir = [self.delegate x5GamePlayer_get_value:@"LibDir"];
    if (cacheDir != nil && libDir != nil) {
        [ChannelConfig setCocosRuntimeRootPath:cacheDir];
        s_application->setEngineResDir([libDir cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    else {
        NSString* errorMsg = [NSString stringWithFormat:@"game_engine_init:get value failed! CacheDir:%@, LibDir:%@", cacheDir, libDir];
        [self.delegate x5GamePlayer_send_msg:
         [NSDictionary dictionaryWithObjectsAndKeys:errorMsg, @"error", nil]];
        return;
    }
    
    //解析game info取得game name、game key、game download url
    NSString* gameKey,*gameDownloadUrl,*gameName;
    if (gameInfoJson != nil) {
        bool gameInfoInitFlag = false;
        do {
            NSDictionary * gameInfo = [NSJSONSerialization JSONObjectWithData:[gameInfoJson dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:nil];
            
            if (gameInfo == nil) { break;}
            gameName = [gameInfo objectForKey:@"gameName"];
            
            NSString* gameExt = [gameInfo objectForKey:@"ext"];
            if (gameExt == nil) { break;}
            
            NSDictionary* gameExtInfo = [NSJSONSerialization JSONObjectWithData:[gameExt dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:nil];
            if (gameExtInfo == nil) { break;}
            
            gameKey = [gameExtInfo objectForKey:@"gameKey"];
            gameDownloadUrl = [gameExtInfo objectForKey:@"resUrl"];
            gameInfoInitFlag = true;
        } while (false);
        
        if (gameInfoInitFlag == false) {
            [self.delegate x5GamePlayer_send_msg:
             [NSDictionary dictionaryWithObjectsAndKeys:@"game_engine_init:get 'CacheDir' value failed!",@"error", nil]];
            return;
        }
    }
    else {
        gameDownloadUrl = @"http://182.254.241.97/ios-runtime-test/moonwarriors";
        gameKey = @"ULY1R3O6MB";
        gameName = @"打飞机游戏";
    }
    
    //从服务器获取游戏配置并下载第一个boot分组
    GameInfo* gameInfo = [[GameInfo alloc] initWithKey:gameKey withUrl:gameDownloadUrl withName:gameName];
    [CocosRuntime startPreRuntime:gameInfo proxy:self];
    
    //通知浏览器已经开始下载
    [self.delegate x5GamePlayer_send_msg:
     [NSDictionary dictionaryWithObjectsAndKeys:MSG_ON_LOAD_GAME_START,@"type", nil]];
    
    auto gameResRoot = [[FileUtil getGameRootPath:gameInfo] cStringUsingEncoding:NSUTF8StringEncoding];
    s_application->setGameResRoot(gameResRoot);
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
        CCLOG("Interface orientation is landscape");
    } else {
        CCLOG("Interface orientation is portrait");
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
    CCLOG("game_engine_onPause");
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

//恢复游戏
- (void)game_engine_onResume
{
    CCLOG("game_engine_onResume");
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

//退出游戏
- (void)game_engine_onStop
{
    CCLOG("game_engine_onStop");
    
    SimpleAudioEngine::getInstance()->stopAllEffects();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::end();
    
    cocos2d::Director::getInstance()->end();
    
    s_application = nullptr;
}

//设置GameEngineRuntimeProxy对象
- (void)game_engine_set_runtime_proxy:(id<MttGameEngineDelegate>)proxy
{
    self.delegate = proxy;
    
    if (self.delegate == nil) {
        CCLOG("game_engine_set_runtime_proxy error, nil");
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
    CCLOG("onLoadingProgress:%ld", (long)progress);
    if (isFailed) {
        [self.delegate x5GamePlayer_send_msg:
         [NSDictionary dictionaryWithObjectsAndKeys:MSG_ON_NETWORK_ERR,@"type", nil]];
    } else {
        long fixProgress = (long)progress;
        if (fixProgress > 100) {
            fixProgress = 100;
        }
        NSString* progressText = [NSString stringWithFormat:@"%ld",fixProgress];
        [self.delegate x5GamePlayer_send_msg:
         [NSDictionary dictionaryWithObjectsAndKeys:MSG_ON_GAME_LOADING_PROGRESS,@"type",
          progressText, @"progress", @"102400", @"size", nil]];
    }
}

- (void) onPreRunGameCompleted
{
    CCLOG("onPreRunGameCompleted");
    [self.delegate x5GamePlayer_send_msg:
     [NSDictionary dictionaryWithObjectsAndKeys:MSG_ON_LOAD_GAME_END,@"type", nil]];
}

@end