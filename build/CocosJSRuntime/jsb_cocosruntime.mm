//
//  jsb_cocosruntime.mm
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/23.
//
#include "jsb_cocosruntime.h"
#include "cocos2d_specifics.hpp"
#include "network/RTNetworkHelper.h"
#import "sdk/CocosRuntime.h"
#import "sdk/LoadingAdapter4Tencent.h"

static std::function<void (int percent, bool isFailed)> s_downloadCallback;

class JSPreloadCallbackWrapper: public JSCallbackWrapper {
public:
    void eventCallbackFunc(int percent, bool isFailed)
    {
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            CCLOG("preload percent:%d,isFailed:%d", percent, isFailed);
            
            if (s_downloadCallback == nullptr) {
                return;
            }
            JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::RootedObject thisObj(cx, getJSCallbackThis().toObjectOrNull());
            JS::RootedValue callback(cx, getJSCallbackFunc());
            JS::RootedValue retval(cx);
            
            if (!callback.isNullOrUndefined())
            {
                char statusText[60];
                sprintf(statusText, "{percent:%d, isCompleted:%s, isFailed:%s}", percent,
                        (percent >= 100 && !isFailed) ? "true" : "false",
                        isFailed ? "true" : "false");
                jsval status = c_string_to_jsval(cx, statusText);
                
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                
                JS_CallFunctionValue(cx, thisObj, callback, JS::HandleValueArray::fromMarkedLocation(1, &status), &retval);
            }
        });
    }
};

class RTCallbacksComponent: public cocos2d::Component {
public:
    RTCallbacksComponent() {
        setName(NAME);
    }
    
    virtual ~RTCallbacksComponent() {
        s_downloadCallback = nullptr;
    }
    
    JSBinding::Dictionary callbacks;
    static const std::string NAME;
};

const std::string RTCallbacksComponent::NAME = "JSB_RTCallback";

USING_NS_CC;

static bool JSB_runtime_preload(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 3, cx, false, "JSB_runtime_preload Invalid number of arguments" );
    
    auto args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    std::string resGroups = "";
    auto arg0Handle = args.get(0);

    if (JS_IsArrayObject(cx, arg0Handle)) {
        ValueVector arrVal;
        ok = jsval_to_ccvaluevector(cx, arg0Handle, &arrVal);

        for (size_t i = 0; i < arrVal.size(); i++) {
            if (! resGroups.empty()) {
                resGroups += ":";
            }
            resGroups += arrVal[i].asString();
        }
    }
    else {
        ok &= jsval_to_std_string(cx, args.get(0), &resGroups);
    }

    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    do {
        if (JS_TypeOfValue(cx, args[1]) == JSTYPE_FUNCTION) {
            auto cbObject= args.get(2).toObjectOrNull();;
            
            auto proxy = jsb_get_js_proxy(cbObject);
            auto loadLayer = (cocos2d::Layer*)(proxy ? proxy->ptr : nullptr);
            auto callbackComp = static_cast<RTCallbacksComponent*>(loadLayer->getComponent(RTCallbacksComponent::NAME));
            if (callbackComp == nullptr) {
                callbackComp = new (std::nothrow) RTCallbacksComponent;
                callbackComp->autorelease();
                loadLayer->addComponent(callbackComp);
            }
            
            auto cbWapper = new (std::nothrow) JSPreloadCallbackWrapper;
            cbWapper->autorelease();
            cbWapper->setJSCallbackFunc(args.get(1));
            cbWapper->setJSCallbackThis(args.get(2));
            callbackComp->callbacks.insert("JSPreloadCallbackWrapper", cbWapper);
            
            auto lambda = [cbWapper](int percent, bool isFailed){
                cbWapper->eventCallbackFunc(percent, isFailed);
            };
            s_downloadCallback = lambda;
        }
        else {
            s_downloadCallback = nullptr;
        }
    } while (false);
    
    if (s_downloadCallback) {
        NSString* groups = [NSString stringWithUTF8String:resGroups.c_str()];
        LoadingAdapter4Tencent *delegate = [[LoadingAdapter4Tencent alloc] initWith:^(int progress, bool isFailed){
                if (s_downloadCallback) {
                    s_downloadCallback(progress, isFailed);
                }
        }];
        [CocosRuntime preloadResGroups: groups delegate:delegate];
    }
    
    args.rval().setUndefined();
    
    return true;
}

static bool JSB_runtime_getNetworkType(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2( argc == 0, cx, false, "JSB_runtime_getNetworkType Invalid number of arguments" );
    
    auto args = JS::CallArgsFromVp(argc, vp);
    int status = [RTNetworkHelper getNetworkType];
    args.rval().set(INT_TO_JSVAL(status));
    
    return true;
}

void jsb_register_cocosruntime(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject runtimeObj(cx);
    get_or_create_js_obj(cx, global, "runtime", &runtimeObj);

    JS_DefineFunction(cx, runtimeObj, "preload", JSB_runtime_preload, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    
    JS_DefineFunction(cx, runtimeObj, "getNetworkType", JSB_runtime_getNetworkType, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
}
