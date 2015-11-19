//
//  CocosDelegate.mm
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/19.
//
#include "CocosDelegate.h"

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "jsb_cocos2dx_auto.hpp"
#include "jsb_cocos2dx_extension_auto.hpp"
#include "jsb_cocos2dx_builder_auto.hpp"
#include "jsb_cocos2dx_spine_auto.hpp"
#include "extension/jsb_cocos2dx_extension_manual.h"
#include "cocostudio/jsb_cocos2dx_studio_manual.h"
#include "jsb_cocos2dx_studio_auto.hpp"
#include "jsb_cocos2dx_ui_auto.hpp"
#include "ui/jsb_cocos2dx_ui_manual.h"
#include "spine/jsb_cocos2dx_spine_manual.h"
#include "cocos2d_specifics.hpp"
#include "cocosbuilder/cocosbuilder_specifics.hpp"
#include "localstorage/js_bindings_system_registration.h"
#include "jsb_opengl_registration.h"
#include "network/XMLHTTPRequest.h"
#include "network/jsb_websocket.h"
#include "network/jsb_socketio.h"
#include "cocosbuilder/js_bindings_ccbreader.h"
#include "jsb_cocos2dx_audioengine_auto.hpp"

#include "jsb_anysdk_protocols_auto.hpp"
#include "manualanysdkbindings.hpp"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/CCJavascriptJavaBridge.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/ios/JavaScriptObjCBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jsb_cocos2dx_experimental_webView_auto.hpp"
#include "experimental/jsb_cocos2dx_experimental_webView_manual.h"
#include "jsb_cocos2dx_experimental_video_auto.hpp"
#include "experimental/jsb_cocos2dx_experimental_video_manual.h"
#endif

#include "jsb_cocosruntime.h"

USING_NS_CC;
using namespace CocosDenshion;

extern void registerDefaultClasses(JSContext* cx, JS::HandleObject global);

CocosAppDelegate::CocosAppDelegate()
{
}

CocosAppDelegate::~CocosAppDelegate()
{
    pure_all_anysdk_Listener();
    ScriptEngineManager::destroyInstance();
    SimpleAudioEngine::end();
}

void CocosAppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

void CocosAppDelegate::setGameResRoot(const std::string &rootDir)
{
    if(rootDir[rootDir.length() - 1] != '/')
        gameResRoot = rootDir + "/";
    else
        gameResRoot = rootDir;
}

void CocosAppDelegate::setEngineResDir(const std::string &resDir)
{
    engineResDir = resDir;
}

bool CocosAppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = cocos2d::GLViewImpl::createWithRect("cocos-runtime", Rect(0,0,900,640));
        director->setOpenGLView(glview);
    }
    
    auto fileUtils = FileUtils::getInstance();
    fileUtils->setDefaultResourceRootPath(gameResRoot);
    fileUtils->addSearchPath("");
    fileUtils->addSearchPath(engineResDir);

    ScriptingCore* sc = ScriptingCore::getInstance();
    
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_cocos2dx_js_core);
    sc->addRegisterCallback(jsb_register_system);
    
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);

    sc->addRegisterCallback(JSB_register_opengl);
    
    sc->addRegisterCallback(MinXmlHttpRequest::_js_register);
    sc->addRegisterCallback(register_jsb_websocket);
	sc->addRegisterCallback(register_jsb_socketio);

    sc->addRegisterCallback(register_all_cocos2dx_builder);
    sc->addRegisterCallback(register_CCBuilderReader);

    sc->addRegisterCallback(register_all_cocos2dx_ui);
    sc->addRegisterCallback(register_all_cocos2dx_ui_manual);
    sc->addRegisterCallback(register_all_cocos2dx_studio);
    sc->addRegisterCallback(register_all_cocos2dx_studio_manual);
    
    sc->addRegisterCallback(register_all_cocos2dx_spine);
    sc->addRegisterCallback(register_all_cocos2dx_spine_manual);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sc->addRegisterCallback(JavascriptJavaBridge::_js_register);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    sc->addRegisterCallback(JavaScriptObjCBridge::_js_register);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sc->addRegisterCallback(register_all_cocos2dx_experimental_webView);
    sc->addRegisterCallback(register_all_cocos2dx_experimental_webView_manual);
    sc->addRegisterCallback(register_all_cocos2dx_experimental_video);
    sc->addRegisterCallback(register_all_cocos2dx_experimental_video_manual);
#endif
    
    sc->addRegisterCallback(register_all_cocos2dx_audioengine);
    
    //cocos runtime
    sc->addRegisterCallback(jsb_register_cocosruntime);
    
    sc->addRegisterCallback(register_all_anysdk_framework);
    sc->addRegisterCallback(register_all_anysdk_manual);
    
    sc->start();
    
    sc->runScript("script/jsb_boot.js");
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    sc->enableDebugger();
#endif
    
    auto pEngine = ScriptingCore::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
    
    //todo：游戏入口由服务器获取的配置确定
    ScriptingCore::getInstance()->runScript("main.js");
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void CocosAppDelegate::applicationDidEnterBackground()
{
    auto director = Director::getInstance();
    director->stopAnimation();
    director->getEventDispatcher()->dispatchCustomEvent("game_on_hide");
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();    
}

// this function will be called when the app is active again
void CocosAppDelegate::applicationWillEnterForeground()
{
    auto director = Director::getInstance();
    director->startAnimation();
    director->getEventDispatcher()->dispatchCustomEvent("game_on_show");
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
