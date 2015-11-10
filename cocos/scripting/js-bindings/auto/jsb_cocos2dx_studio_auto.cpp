#include "jsb_cocos2dx_studio_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "cocostudio/jsb_cocos2dx_studio_conversions.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_cocostudio_ActionObject_class;
JSObject *jsb_cocostudio_ActionObject_prototype;

bool js_cocos2dx_studio_ActionObject_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_setCurrentTime : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_setCurrentTime : Error processing arguments");
        cobj->setCurrentTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_setCurrentTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_pause : Invalid Native Object");
    if (argc == 0) {
        cobj->pause();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_pause : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_setName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_setName : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_setName : Error processing arguments");
        cobj->setName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_setName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_setUnitTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_setUnitTime : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_setUnitTime : Error processing arguments");
        cobj->setUnitTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_setUnitTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_getTotalTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getTotalTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTotalTime();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getTotalTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_getName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getName : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getName();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_stop : Invalid Native Object");
    if (argc == 0) {
        cobj->stop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ActionObject* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_play : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::CallFunc* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::CallFunc*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->play(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj->play();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_play : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ActionObject_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getCurrentTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCurrentTime();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getCurrentTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_removeActionNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_removeActionNode : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ActionNode* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ActionNode*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_removeActionNode : Error processing arguments");
        cobj->removeActionNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_removeActionNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_getLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getLoop : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getLoop();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getLoop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_initWithBinary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_initWithBinary : Invalid Native Object");
    if (argc == 3) {
        cocostudio::CocoLoader* arg0 = nullptr;
        cocostudio::stExpCocoNode* arg1 = nullptr;
        cocos2d::Ref* arg2 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::CocoLoader*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        #pragma warning NO CONVERSION TO NATIVE FOR stExpCocoNode*
		ok = false;
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_initWithBinary : Error processing arguments");
        cobj->initWithBinary(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_initWithBinary : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_studio_ActionObject_addActionNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_addActionNode : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ActionNode* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ActionNode*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_addActionNode : Error processing arguments");
        cobj->addActionNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_addActionNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_getUnitTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getUnitTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getUnitTime();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getUnitTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_isPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_isPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPlaying();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_isPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_updateToFrameByTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_updateToFrameByTime : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_updateToFrameByTime : Error processing arguments");
        cobj->updateToFrameByTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_updateToFrameByTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_setLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_setLoop : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_setLoop : Error processing arguments");
        cobj->setLoop(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_setLoop : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_simulationActionUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_simulationActionUpdate : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_simulationActionUpdate : Error processing arguments");
        cobj->simulationActionUpdate(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_simulationActionUpdate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ActionObject* cobj = new (std::nothrow) cocostudio::ActionObject();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::ActionObject> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::ActionObject");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_cocostudio_ActionObject_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ActionObject)", obj);
}
void js_register_cocos2dx_studio_ActionObject(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ActionObject_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ActionObject_class->name = "ActionObject";
    jsb_cocostudio_ActionObject_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ActionObject_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ActionObject_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ActionObject_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ActionObject_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ActionObject_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ActionObject_class->convert = JS_ConvertStub;
    jsb_cocostudio_ActionObject_class->finalize = js_cocostudio_ActionObject_finalize;
    jsb_cocostudio_ActionObject_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setCurrentTime", js_cocos2dx_studio_ActionObject_setCurrentTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_cocos2dx_studio_ActionObject_pause, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setName", js_cocos2dx_studio_ActionObject_setName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUnitTime", js_cocos2dx_studio_ActionObject_setUnitTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTotalTime", js_cocos2dx_studio_ActionObject_getTotalTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getName", js_cocos2dx_studio_ActionObject_getName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_studio_ActionObject_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_studio_ActionObject_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentTime", js_cocos2dx_studio_ActionObject_getCurrentTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeActionNode", js_cocos2dx_studio_ActionObject_removeActionNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLoop", js_cocos2dx_studio_ActionObject_getLoop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithBinary", js_cocos2dx_studio_ActionObject_initWithBinary, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addActionNode", js_cocos2dx_studio_ActionObject_addActionNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUnitTime", js_cocos2dx_studio_ActionObject_getUnitTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPlaying", js_cocos2dx_studio_ActionObject_isPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateToFrameByTime", js_cocos2dx_studio_ActionObject_updateToFrameByTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoop", js_cocos2dx_studio_ActionObject_setLoop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("simulationActionUpdate", js_cocos2dx_studio_ActionObject_simulationActionUpdate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_ActionObject_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocostudio_ActionObject_class,
        js_cocos2dx_studio_ActionObject_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ActionObject", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::ActionObject> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_ActionObject_class;
        p->proto = jsb_cocostudio_ActionObject_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_ActionManagerEx_class;
JSObject *jsb_cocostudio_ActionManagerEx_prototype;

bool js_cocos2dx_studio_ActionManagerEx_stopActionByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_stopActionByName : Invalid Native Object");
    if (argc == 2) {
        const char* arg0 = nullptr;
        const char* arg1 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_stopActionByName : Error processing arguments");
        cocostudio::ActionObject* ret = cobj->stopActionByName(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ActionObject>(cx, (cocostudio::ActionObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_stopActionByName : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_getActionByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_getActionByName : Invalid Native Object");
    if (argc == 2) {
        const char* arg0 = nullptr;
        const char* arg1 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_getActionByName : Error processing arguments");
        cocostudio::ActionObject* ret = cobj->getActionByName(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ActionObject>(cx, (cocostudio::ActionObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_getActionByName : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_initWithBinary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithBinary : Invalid Native Object");
    if (argc == 4) {
        const char* arg0 = nullptr;
        cocos2d::Ref* arg1 = nullptr;
        cocostudio::CocoLoader* arg2 = nullptr;
        cocostudio::stExpCocoNode* arg3 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocostudio::CocoLoader*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        #pragma warning NO CONVERSION TO NATIVE FOR stExpCocoNode*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithBinary : Error processing arguments");
        cobj->initWithBinary(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_initWithBinary : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_playActionByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ActionManagerEx* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_playActionByName : Invalid Native Object");
    do {
        if (argc == 3) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            cocos2d::CallFunc* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(2).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::CallFunc*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocostudio::ActionObject* ret = cobj->playActionByName(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ActionObject>(cx, (cocostudio::ActionObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            cocostudio::ActionObject* ret = cobj->playActionByName(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ActionObject>(cx, (cocostudio::ActionObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_playActionByName : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_releaseActions(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_releaseActions : Invalid Native Object");
    if (argc == 0) {
        cobj->releaseActions();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_releaseActions : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::ActionManagerEx::destroyInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_destroyInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ActionManagerEx_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::ActionManagerEx* ret = cocostudio::ActionManagerEx::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ActionManagerEx>(cx, (cocostudio::ActionManagerEx*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_getInstance : wrong number of arguments");
    return false;
}


void js_cocostudio_ActionManagerEx_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ActionManagerEx)", obj);
}
void js_register_cocos2dx_studio_ActionManagerEx(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ActionManagerEx_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ActionManagerEx_class->name = "ActionManager";
    jsb_cocostudio_ActionManagerEx_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ActionManagerEx_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ActionManagerEx_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ActionManagerEx_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ActionManagerEx_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ActionManagerEx_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ActionManagerEx_class->convert = JS_ConvertStub;
    jsb_cocostudio_ActionManagerEx_class->finalize = js_cocostudio_ActionManagerEx_finalize;
    jsb_cocostudio_ActionManagerEx_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("stopActionByName", js_cocos2dx_studio_ActionManagerEx_stopActionByName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionByName", js_cocos2dx_studio_ActionManagerEx_getActionByName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithBinary", js_cocos2dx_studio_ActionManagerEx_initWithBinary, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playActionByName", js_cocos2dx_studio_ActionManagerEx_playActionByName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("releaseActions", js_cocos2dx_studio_ActionManagerEx_releaseActions, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destroyInstance", js_cocos2dx_studio_ActionManagerEx_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_cocos2dx_studio_ActionManagerEx_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ActionManagerEx_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocostudio_ActionManagerEx_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ActionManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::ActionManagerEx> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_ActionManagerEx_class;
        p->proto = jsb_cocostudio_ActionManagerEx_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_ComAttribute_class;
JSObject *jsb_cocostudio_ComAttribute_prototype;

bool js_cocos2dx_studio_ComAttribute_getFloat(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_getFloat : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getFloat : Error processing arguments");
        double ret = cobj->getFloat(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        double arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getFloat : Error processing arguments");
        double ret = cobj->getFloat(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_getFloat : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_getBool(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_getBool : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getBool : Error processing arguments");
        bool ret = cobj->getBool(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getBool : Error processing arguments");
        bool ret = cobj->getBool(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_getBool : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_getString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_getString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getString : Error processing arguments");
        std::string ret = cobj->getString(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getString : Error processing arguments");
        std::string ret = cobj->getString(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_getString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_setFloat(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_setFloat : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        double arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_setFloat : Error processing arguments");
        cobj->setFloat(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_setFloat : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_setString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_setString : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_setString : Error processing arguments");
        cobj->setString(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_setString : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_setInt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_setInt : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        int arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_setInt : Error processing arguments");
        cobj->setInt(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_setInt : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_parse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_parse : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_parse : Error processing arguments");
        bool ret = cobj->parse(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_parse : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_getInt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_getInt : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getInt : Error processing arguments");
        int ret = cobj->getInt(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        int arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getInt : Error processing arguments");
        int ret = cobj->getInt(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_getInt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_setBool(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_setBool : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_setBool : Error processing arguments");
        cobj->setBool(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_setBool : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::ComAttribute* ret = cocostudio::ComAttribute::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ComAttribute>(cx, (cocostudio::ComAttribute*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ComAttribute_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ComAttribute* cobj = new (std::nothrow) cocostudio::ComAttribute();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::ComAttribute> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::ComAttribute");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_Component_prototype;

void js_cocostudio_ComAttribute_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ComAttribute)", obj);
}
void js_register_cocos2dx_studio_ComAttribute(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComAttribute_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComAttribute_class->name = "ComAttribute";
    jsb_cocostudio_ComAttribute_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComAttribute_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComAttribute_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComAttribute_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComAttribute_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComAttribute_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComAttribute_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComAttribute_class->finalize = js_cocostudio_ComAttribute_finalize;
    jsb_cocostudio_ComAttribute_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getFloat", js_cocos2dx_studio_ComAttribute_getFloat, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBool", js_cocos2dx_studio_ComAttribute_getBool, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getString", js_cocos2dx_studio_ComAttribute_getString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFloat", js_cocos2dx_studio_ComAttribute_setFloat, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setString", js_cocos2dx_studio_ComAttribute_setString, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInt", js_cocos2dx_studio_ComAttribute_setInt, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("parse", js_cocos2dx_studio_ComAttribute_parse, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInt", js_cocos2dx_studio_ComAttribute_getInt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBool", js_cocos2dx_studio_ComAttribute_setBool, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComAttribute_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ComAttribute_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Component_prototype),
        jsb_cocostudio_ComAttribute_class,
        js_cocos2dx_studio_ComAttribute_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ComAttribute", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::ComAttribute> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_ComAttribute_class;
        p->proto = jsb_cocostudio_ComAttribute_prototype;
        p->parentProto = jsb_cocos2d_Component_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_ComAudio_class;
JSObject *jsb_cocostudio_ComAudio_prototype;

bool js_cocos2dx_studio_ComAudio_stopAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_stopAllEffects : Invalid Native Object");
    if (argc == 0) {
        cobj->stopAllEffects();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_stopAllEffects : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_getEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_getEffectsVolume : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEffectsVolume();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_getEffectsVolume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_stopEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_stopEffect : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_stopEffect : Error processing arguments");
        cobj->stopEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_stopEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getBackgroundMusicVolume();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->willPlayBackgroundMusic();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume : Error processing arguments");
        cobj->setBackgroundMusicVolume(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_end(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_end : Invalid Native Object");
    if (argc == 0) {
        cobj->end();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_end : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_stopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ComAudio* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_stopBackgroundMusic : Invalid Native Object");
    do {
        if (argc == 0) {
            cobj->stopBackgroundMusic();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            bool arg0;
            arg0 = JS::ToBoolean(args.get(0));
            cobj->stopBackgroundMusic(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_stopBackgroundMusic : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ComAudio_pauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_pauseBackgroundMusic : Invalid Native Object");
    if (argc == 0) {
        cobj->pauseBackgroundMusic();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_pauseBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBackgroundMusicPlaying();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_isLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_isLoop : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLoop();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_isLoop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_resumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_resumeAllEffects : Invalid Native Object");
    if (argc == 0) {
        cobj->resumeAllEffects();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_resumeAllEffects : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_pauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_pauseAllEffects : Invalid Native Object");
    if (argc == 0) {
        cobj->pauseAllEffects();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_pauseAllEffects : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_preloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_preloadBackgroundMusic : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_preloadBackgroundMusic : Error processing arguments");
        cobj->preloadBackgroundMusic(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_preloadBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_playBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ComAudio* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_playBackgroundMusic : Invalid Native Object");
    do {
        if (argc == 1) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            cobj->playBackgroundMusic(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->playBackgroundMusic(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj->playBackgroundMusic();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_playBackgroundMusic : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ComAudio_playEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ComAudio* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_playEffect : Invalid Native Object");
    do {
        if (argc == 1) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            unsigned int ret = cobj->playEffect(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = uint32_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            unsigned int ret = cobj->playEffect(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = uint32_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            unsigned int ret = cobj->playEffect();
            jsval jsret = JSVAL_NULL;
            jsret = uint32_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_playEffect : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ComAudio_preloadEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_preloadEffect : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_preloadEffect : Error processing arguments");
        cobj->preloadEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_preloadEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_setLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_setLoop : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_setLoop : Error processing arguments");
        cobj->setLoop(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_setLoop : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_unloadEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_unloadEffect : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_unloadEffect : Error processing arguments");
        cobj->unloadEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_unloadEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_rewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_rewindBackgroundMusic : Invalid Native Object");
    if (argc == 0) {
        cobj->rewindBackgroundMusic();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_rewindBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_pauseEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_pauseEffect : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_pauseEffect : Error processing arguments");
        cobj->pauseEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_pauseEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_resumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_resumeBackgroundMusic : Invalid Native Object");
    if (argc == 0) {
        cobj->resumeBackgroundMusic();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_resumeBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_setFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_setFile : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_setFile : Error processing arguments");
        cobj->setFile(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_setFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_setEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_setEffectsVolume : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_setEffectsVolume : Error processing arguments");
        cobj->setEffectsVolume(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_setEffectsVolume : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_getFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_getFile : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getFile();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_getFile : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_resumeEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_resumeEffect : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_resumeEffect : Error processing arguments");
        cobj->resumeEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_resumeEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::ComAudio* ret = cocostudio::ComAudio::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ComAudio>(cx, (cocostudio::ComAudio*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ComAudio_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ComAudio* cobj = new (std::nothrow) cocostudio::ComAudio();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::ComAudio> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::ComAudio");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_Component_prototype;

void js_cocostudio_ComAudio_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ComAudio)", obj);
}
void js_register_cocos2dx_studio_ComAudio(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComAudio_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComAudio_class->name = "ComAudio";
    jsb_cocostudio_ComAudio_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComAudio_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComAudio_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComAudio_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComAudio_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComAudio_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComAudio_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComAudio_class->finalize = js_cocostudio_ComAudio_finalize;
    jsb_cocostudio_ComAudio_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("stopAllEffects", js_cocos2dx_studio_ComAudio_stopAllEffects, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEffectsVolume", js_cocos2dx_studio_ComAudio_getEffectsVolume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopEffect", js_cocos2dx_studio_ComAudio_stopEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackgroundMusicVolume", js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("willPlayBackgroundMusic", js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackgroundMusicVolume", js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("end", js_cocos2dx_studio_ComAudio_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopBackgroundMusic", js_cocos2dx_studio_ComAudio_stopBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseBackgroundMusic", js_cocos2dx_studio_ComAudio_pauseBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBackgroundMusicPlaying", js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoop", js_cocos2dx_studio_ComAudio_isLoop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeAllEffects", js_cocos2dx_studio_ComAudio_resumeAllEffects, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseAllEffects", js_cocos2dx_studio_ComAudio_pauseAllEffects, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("preloadBackgroundMusic", js_cocos2dx_studio_ComAudio_preloadBackgroundMusic, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playBackgroundMusic", js_cocos2dx_studio_ComAudio_playBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playEffect", js_cocos2dx_studio_ComAudio_playEffect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("preloadEffect", js_cocos2dx_studio_ComAudio_preloadEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoop", js_cocos2dx_studio_ComAudio_setLoop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unloadEffect", js_cocos2dx_studio_ComAudio_unloadEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("rewindBackgroundMusic", js_cocos2dx_studio_ComAudio_rewindBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseEffect", js_cocos2dx_studio_ComAudio_pauseEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeBackgroundMusic", js_cocos2dx_studio_ComAudio_resumeBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFile", js_cocos2dx_studio_ComAudio_setFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEffectsVolume", js_cocos2dx_studio_ComAudio_setEffectsVolume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFile", js_cocos2dx_studio_ComAudio_getFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeEffect", js_cocos2dx_studio_ComAudio_resumeEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComAudio_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ComAudio_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Component_prototype),
        jsb_cocostudio_ComAudio_class,
        js_cocos2dx_studio_ComAudio_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ComAudio", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::ComAudio> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_ComAudio_class;
        p->proto = jsb_cocostudio_ComAudio_prototype;
        p->parentProto = jsb_cocos2d_Component_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_InputDelegate_class;
JSObject *jsb_cocostudio_InputDelegate_prototype;

bool js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isAccelerometerEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setKeypadEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setKeypadEnabled : Error processing arguments");
        cobj->setKeypadEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setKeypadEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_getTouchMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_getTouchMode : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getTouchMode();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_getTouchMode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled : Error processing arguments");
        cobj->setAccelerometerEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_isKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_isKeypadEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isKeypadEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_isKeypadEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_isTouchEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTouchEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_isTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setTouchPriority(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchPriority : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchPriority : Error processing arguments");
        cobj->setTouchPriority(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setTouchPriority : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_getTouchPriority(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_getTouchPriority : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getTouchPriority();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_getTouchPriority : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchEnabled : Error processing arguments");
        cobj->setTouchEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setTouchMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchMode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Touch::DispatchMode arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchMode : Error processing arguments");
        cobj->setTouchMode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setTouchMode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

void js_cocostudio_InputDelegate_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (InputDelegate)", obj);
}
void js_register_cocos2dx_studio_InputDelegate(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_InputDelegate_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_InputDelegate_class->name = "InputDelegate";
    jsb_cocostudio_InputDelegate_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_InputDelegate_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_InputDelegate_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_InputDelegate_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_InputDelegate_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_InputDelegate_class->resolve = JS_ResolveStub;
    jsb_cocostudio_InputDelegate_class->convert = JS_ConvertStub;
    jsb_cocostudio_InputDelegate_class->finalize = js_cocostudio_InputDelegate_finalize;
    jsb_cocostudio_InputDelegate_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isAccelerometerEnabled", js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setKeypadEnabled", js_cocos2dx_studio_InputDelegate_setKeypadEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchMode", js_cocos2dx_studio_InputDelegate_getTouchMode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAccelerometerEnabled", js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isKeypadEnabled", js_cocos2dx_studio_InputDelegate_isKeypadEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTouchEnabled", js_cocos2dx_studio_InputDelegate_isTouchEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchPriority", js_cocos2dx_studio_InputDelegate_setTouchPriority, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchPriority", js_cocos2dx_studio_InputDelegate_getTouchPriority, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchEnabled", js_cocos2dx_studio_InputDelegate_setTouchEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchMode", js_cocos2dx_studio_InputDelegate_setTouchMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_InputDelegate_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocostudio_InputDelegate_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "InputDelegate", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::InputDelegate> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_InputDelegate_class;
        p->proto = jsb_cocostudio_InputDelegate_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_ComController_class;
JSObject *jsb_cocostudio_ComController_prototype;

bool js_cocos2dx_studio_ComController_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::ComController* ret = cocostudio::ComController::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ComController>(cx, (cocostudio::ComController*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComController_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ComController_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ComController* cobj = new (std::nothrow) cocostudio::ComController();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::ComController> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::ComController");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}static bool js_cocos2dx_studio_ComController_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocostudio::ComController *nobj = new (std::nothrow) cocostudio::ComController();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::ComController");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}

extern JSObject *jsb_cocos2d_Component_prototype;

void js_cocostudio_ComController_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ComController)", obj);
}
    
void js_register_cocos2dx_studio_ComController(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComController_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComController_class->name = "ComController";
    jsb_cocostudio_ComController_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComController_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComController_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComController_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComController_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComController_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComController_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComController_class->finalize = js_cocostudio_ComController_finalize;
    jsb_cocostudio_ComController_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("ctor", js_cocos2dx_studio_ComController_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComController_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ComController_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Component_prototype),
        jsb_cocostudio_ComController_class,
        js_cocos2dx_studio_ComController_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ComController", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::ComController> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_ComController_class;
        p->proto = jsb_cocostudio_ComController_prototype;
        p->parentProto = jsb_cocos2d_Component_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
    anonEvaluate(cx, global, "(function () { ccs.ComController.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocostudio_ComRender_class;
JSObject *jsb_cocostudio_ComRender_prototype;

bool js_cocos2dx_studio_ComRender_setNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComRender* cobj = (cocostudio::ComRender *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComRender_setNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComRender_setNode : Error processing arguments");
        cobj->setNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComRender_setNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComRender_getNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComRender* cobj = (cocostudio::ComRender *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComRender_getNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComRender_getNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComRender_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            cocostudio::ComRender* ret = cocostudio::ComRender::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ComRender>(cx, (cocostudio::ComRender*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocostudio::ComRender* ret = cocostudio::ComRender::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ComRender>(cx, (cocostudio::ComRender*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_studio_ComRender_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ComRender_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ComRender* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) cocostudio::ComRender(arg0, arg1);
            cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
            if (_ccobj) {
                _ccobj->autorelease();
            }

            TypeTest<cocostudio::ComRender> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            // obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            JS::RootedObject proto(cx, typeClass->proto.get());
            JS::RootedObject parent(cx, typeClass->parentProto.get());
            obj = JS_NewObject(cx, typeClass->jsclass, proto, parent);

            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            AddNamedObjectRoot(cx, &p->obj, "cocostudio::ComRender");
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj = new (std::nothrow) cocostudio::ComRender();
            cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
            if (_ccobj) {
                _ccobj->autorelease();
            }

            TypeTest<cocostudio::ComRender> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            // obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            JS::RootedObject proto(cx, typeClass->proto.get());
            JS::RootedObject parent(cx, typeClass->parentProto.get());
            obj = JS_NewObject(cx, typeClass->jsclass, proto, parent);

            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            AddNamedObjectRoot(cx, &p->obj, "cocostudio::ComRender");
        }
    } while(0);

    if (cobj) {
        if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
                ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);

        args.rval().set(OBJECT_TO_JSVAL(obj));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComRender_constructor : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_cocostudio_ComRender_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ComRender)", obj);
}
void js_register_cocos2dx_studio_ComRender(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComRender_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComRender_class->name = "ComRender";
    jsb_cocostudio_ComRender_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComRender_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComRender_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComRender_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComRender_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComRender_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComRender_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComRender_class->finalize = js_cocostudio_ComRender_finalize;
    jsb_cocostudio_ComRender_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setNode", js_cocos2dx_studio_ComRender_setNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNode", js_cocos2dx_studio_ComRender_getNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComRender_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ComRender_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Component_prototype),
        jsb_cocostudio_ComRender_class,
        js_cocos2dx_studio_ComRender_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ComRender", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::ComRender> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_ComRender_class;
        p->proto = jsb_cocostudio_ComRender_prototype;
        p->parentProto = jsb_cocos2d_Component_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_Frame_class;
JSObject *jsb_cocostudio_timeline_Frame_prototype;

bool js_cocos2dx_studio_Frame_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_clone : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::Frame* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::Frame>(cx, (cocostudio::timeline::Frame*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_setTweenType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setTweenType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::tweenfunc::TweenType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setTweenType : Error processing arguments");
        cobj->setTweenType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setTweenType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_setNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setNode : Error processing arguments");
        cobj->setNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_setTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setTimeline : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Timeline* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Timeline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setTimeline : Error processing arguments");
        cobj->setTimeline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setTimeline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_isEnterWhenPassed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_isEnterWhenPassed : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isEnterWhenPassed();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_isEnterWhenPassed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_getTweenType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_getTweenType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getTweenType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_getTweenType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_getFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_getFrameIndex : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getFrameIndex();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_getFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_apply(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_apply : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_apply : Error processing arguments");
        cobj->apply(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_apply : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_isTween(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_isTween : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTween();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_isTween : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_setFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setFrameIndex : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setFrameIndex : Error processing arguments");
        cobj->setFrameIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_setTween(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setTween : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setTween : Error processing arguments");
        cobj->setTween(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setTween : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_getTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_getTimeline : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::Timeline* ret = cobj->getTimeline();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::Timeline>(cx, (cocostudio::timeline::Timeline*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_getTimeline : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_getNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_getNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_getNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

void js_cocostudio_timeline_Frame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Frame)", obj);
}
void js_register_cocos2dx_studio_Frame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_Frame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_Frame_class->name = "Frame";
    jsb_cocostudio_timeline_Frame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_Frame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_Frame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_Frame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_Frame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_Frame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_Frame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_Frame_class->finalize = js_cocostudio_timeline_Frame_finalize;
    jsb_cocostudio_timeline_Frame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("clone", js_cocos2dx_studio_Frame_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTweenType", js_cocos2dx_studio_Frame_setTweenType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNode", js_cocos2dx_studio_Frame_setNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTimeline", js_cocos2dx_studio_Frame_setTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isEnterWhenPassed", js_cocos2dx_studio_Frame_isEnterWhenPassed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTweenType", js_cocos2dx_studio_Frame_getTweenType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameIndex", js_cocos2dx_studio_Frame_getFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("apply", js_cocos2dx_studio_Frame_apply, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTween", js_cocos2dx_studio_Frame_isTween, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFrameIndex", js_cocos2dx_studio_Frame_setFrameIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTween", js_cocos2dx_studio_Frame_setTween, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeline", js_cocos2dx_studio_Frame_getTimeline, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNode", js_cocos2dx_studio_Frame_getNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_timeline_Frame_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocostudio_timeline_Frame_class,
        dummy_constructor<cocostudio::timeline::Frame>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Frame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::Frame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_Frame_class;
        p->proto = jsb_cocostudio_timeline_Frame_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_VisibleFrame_class;
JSObject *jsb_cocostudio_timeline_VisibleFrame_prototype;

bool js_cocos2dx_studio_VisibleFrame_isVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::VisibleFrame* cobj = (cocostudio::timeline::VisibleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_VisibleFrame_isVisible : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isVisible();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_VisibleFrame_isVisible : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_VisibleFrame_setVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::VisibleFrame* cobj = (cocostudio::timeline::VisibleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_VisibleFrame_setVisible : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_VisibleFrame_setVisible : Error processing arguments");
        cobj->setVisible(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_VisibleFrame_setVisible : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_VisibleFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::VisibleFrame* ret = cocostudio::timeline::VisibleFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::VisibleFrame>(cx, (cocostudio::timeline::VisibleFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_VisibleFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_VisibleFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::VisibleFrame* cobj = new (std::nothrow) cocostudio::timeline::VisibleFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::VisibleFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::VisibleFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_VisibleFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (VisibleFrame)", obj);
}
void js_register_cocos2dx_studio_VisibleFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_VisibleFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_VisibleFrame_class->name = "VisibleFrame";
    jsb_cocostudio_timeline_VisibleFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_VisibleFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_VisibleFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_VisibleFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_VisibleFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_VisibleFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_VisibleFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_VisibleFrame_class->finalize = js_cocostudio_timeline_VisibleFrame_finalize;
    jsb_cocostudio_timeline_VisibleFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isVisible", js_cocos2dx_studio_VisibleFrame_isVisible, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVisible", js_cocos2dx_studio_VisibleFrame_setVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_VisibleFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_VisibleFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_VisibleFrame_class,
        js_cocos2dx_studio_VisibleFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "VisibleFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::VisibleFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_VisibleFrame_class;
        p->proto = jsb_cocostudio_timeline_VisibleFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_TextureFrame_class;
JSObject *jsb_cocostudio_timeline_TextureFrame_prototype;

bool js_cocos2dx_studio_TextureFrame_getTextureName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::TextureFrame* cobj = (cocostudio::timeline::TextureFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_TextureFrame_getTextureName : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getTextureName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_TextureFrame_getTextureName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_TextureFrame_setTextureName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::TextureFrame* cobj = (cocostudio::timeline::TextureFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_TextureFrame_setTextureName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_TextureFrame_setTextureName : Error processing arguments");
        cobj->setTextureName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_TextureFrame_setTextureName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_TextureFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::TextureFrame* ret = cocostudio::timeline::TextureFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::TextureFrame>(cx, (cocostudio::timeline::TextureFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_TextureFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_TextureFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::TextureFrame* cobj = new (std::nothrow) cocostudio::timeline::TextureFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::TextureFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::TextureFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_TextureFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TextureFrame)", obj);
}
void js_register_cocos2dx_studio_TextureFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_TextureFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_TextureFrame_class->name = "TextureFrame";
    jsb_cocostudio_timeline_TextureFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_TextureFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_TextureFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_TextureFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_TextureFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_TextureFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_TextureFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_TextureFrame_class->finalize = js_cocostudio_timeline_TextureFrame_finalize;
    jsb_cocostudio_timeline_TextureFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getTextureName", js_cocos2dx_studio_TextureFrame_getTextureName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextureName", js_cocos2dx_studio_TextureFrame_setTextureName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_TextureFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_TextureFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_TextureFrame_class,
        js_cocos2dx_studio_TextureFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "TextureFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::TextureFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_TextureFrame_class;
        p->proto = jsb_cocostudio_timeline_TextureFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_RotationFrame_class;
JSObject *jsb_cocostudio_timeline_RotationFrame_prototype;

bool js_cocos2dx_studio_RotationFrame_setRotation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::RotationFrame* cobj = (cocostudio::timeline::RotationFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_RotationFrame_setRotation : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_RotationFrame_setRotation : Error processing arguments");
        cobj->setRotation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_RotationFrame_setRotation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_RotationFrame_getRotation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::RotationFrame* cobj = (cocostudio::timeline::RotationFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_RotationFrame_getRotation : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRotation();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_RotationFrame_getRotation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_RotationFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::RotationFrame* ret = cocostudio::timeline::RotationFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::RotationFrame>(cx, (cocostudio::timeline::RotationFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_RotationFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_RotationFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::RotationFrame* cobj = new (std::nothrow) cocostudio::timeline::RotationFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::RotationFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::RotationFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_RotationFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RotationFrame)", obj);
}
void js_register_cocos2dx_studio_RotationFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_RotationFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_RotationFrame_class->name = "RotationFrame";
    jsb_cocostudio_timeline_RotationFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_RotationFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_RotationFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_RotationFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_RotationFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_RotationFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_RotationFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_RotationFrame_class->finalize = js_cocostudio_timeline_RotationFrame_finalize;
    jsb_cocostudio_timeline_RotationFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setRotation", js_cocos2dx_studio_RotationFrame_setRotation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRotation", js_cocos2dx_studio_RotationFrame_getRotation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_RotationFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_RotationFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_RotationFrame_class,
        js_cocos2dx_studio_RotationFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RotationFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::RotationFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_RotationFrame_class;
        p->proto = jsb_cocostudio_timeline_RotationFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_SkewFrame_class;
JSObject *jsb_cocostudio_timeline_SkewFrame_prototype;

bool js_cocos2dx_studio_SkewFrame_getSkewY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkewFrame* cobj = (cocostudio::timeline::SkewFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkewFrame_getSkewY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSkewY();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_getSkewY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_SkewFrame_setSkewX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkewFrame* cobj = (cocostudio::timeline::SkewFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkewFrame_setSkewX : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_SkewFrame_setSkewX : Error processing arguments");
        cobj->setSkewX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_setSkewX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_SkewFrame_setSkewY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkewFrame* cobj = (cocostudio::timeline::SkewFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkewFrame_setSkewY : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_SkewFrame_setSkewY : Error processing arguments");
        cobj->setSkewY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_setSkewY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_SkewFrame_getSkewX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkewFrame* cobj = (cocostudio::timeline::SkewFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkewFrame_getSkewX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSkewX();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_getSkewX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_SkewFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::SkewFrame* ret = cocostudio::timeline::SkewFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::SkewFrame>(cx, (cocostudio::timeline::SkewFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_SkewFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::SkewFrame* cobj = new (std::nothrow) cocostudio::timeline::SkewFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::SkewFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::SkewFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_SkewFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SkewFrame)", obj);
}
void js_register_cocos2dx_studio_SkewFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_SkewFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_SkewFrame_class->name = "SkewFrame";
    jsb_cocostudio_timeline_SkewFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_SkewFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_SkewFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_SkewFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_SkewFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_SkewFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_SkewFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_SkewFrame_class->finalize = js_cocostudio_timeline_SkewFrame_finalize;
    jsb_cocostudio_timeline_SkewFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getSkewY", js_cocos2dx_studio_SkewFrame_getSkewY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSkewX", js_cocos2dx_studio_SkewFrame_setSkewX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSkewY", js_cocos2dx_studio_SkewFrame_setSkewY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSkewX", js_cocos2dx_studio_SkewFrame_getSkewX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_SkewFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_SkewFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_SkewFrame_class,
        js_cocos2dx_studio_SkewFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SkewFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::SkewFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_SkewFrame_class;
        p->proto = jsb_cocostudio_timeline_SkewFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_RotationSkewFrame_class;
JSObject *jsb_cocostudio_timeline_RotationSkewFrame_prototype;

bool js_cocos2dx_studio_RotationSkewFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::RotationSkewFrame* ret = cocostudio::timeline::RotationSkewFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::RotationSkewFrame>(cx, (cocostudio::timeline::RotationSkewFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_RotationSkewFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_RotationSkewFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::RotationSkewFrame* cobj = new (std::nothrow) cocostudio::timeline::RotationSkewFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::RotationSkewFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::RotationSkewFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_SkewFrame_prototype;

void js_cocostudio_timeline_RotationSkewFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RotationSkewFrame)", obj);
}
void js_register_cocos2dx_studio_RotationSkewFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_RotationSkewFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_RotationSkewFrame_class->name = "RotationSkewFrame";
    jsb_cocostudio_timeline_RotationSkewFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->finalize = js_cocostudio_timeline_RotationSkewFrame_finalize;
    jsb_cocostudio_timeline_RotationSkewFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_RotationSkewFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_RotationSkewFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_SkewFrame_prototype),
        jsb_cocostudio_timeline_RotationSkewFrame_class,
        js_cocos2dx_studio_RotationSkewFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RotationSkewFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::RotationSkewFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_RotationSkewFrame_class;
        p->proto = jsb_cocostudio_timeline_RotationSkewFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_SkewFrame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_PositionFrame_class;
JSObject *jsb_cocostudio_timeline_PositionFrame_prototype;

bool js_cocos2dx_studio_PositionFrame_getX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_getX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getX();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_getX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_getY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_getY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getY();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_getY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_setPosition : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_PositionFrame_setPosition : Error processing arguments");
        cobj->setPosition(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_setPosition : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_setX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_setX : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_PositionFrame_setX : Error processing arguments");
        cobj->setX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_setX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_setY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_setY : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_PositionFrame_setY : Error processing arguments");
        cobj->setY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_setY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_getPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_getPosition : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getPosition();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_getPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::PositionFrame* ret = cocostudio::timeline::PositionFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::PositionFrame>(cx, (cocostudio::timeline::PositionFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_PositionFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::PositionFrame* cobj = new (std::nothrow) cocostudio::timeline::PositionFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::PositionFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::PositionFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_PositionFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PositionFrame)", obj);
}
void js_register_cocos2dx_studio_PositionFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_PositionFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_PositionFrame_class->name = "PositionFrame";
    jsb_cocostudio_timeline_PositionFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_PositionFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_PositionFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_PositionFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_PositionFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_PositionFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_PositionFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_PositionFrame_class->finalize = js_cocostudio_timeline_PositionFrame_finalize;
    jsb_cocostudio_timeline_PositionFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getX", js_cocos2dx_studio_PositionFrame_getX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getY", js_cocos2dx_studio_PositionFrame_getY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPosition", js_cocos2dx_studio_PositionFrame_setPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setX", js_cocos2dx_studio_PositionFrame_setX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setY", js_cocos2dx_studio_PositionFrame_setY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPosition", js_cocos2dx_studio_PositionFrame_getPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_PositionFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_PositionFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_PositionFrame_class,
        js_cocos2dx_studio_PositionFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "PositionFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::PositionFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_PositionFrame_class;
        p->proto = jsb_cocostudio_timeline_PositionFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_ScaleFrame_class;
JSObject *jsb_cocostudio_timeline_ScaleFrame_prototype;

bool js_cocos2dx_studio_ScaleFrame_setScaleY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_setScaleY : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ScaleFrame_setScaleY : Error processing arguments");
        cobj->setScaleY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_setScaleY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_setScaleX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_setScaleX : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ScaleFrame_setScaleX : Error processing arguments");
        cobj->setScaleX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_setScaleX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_getScaleY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_getScaleY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getScaleY();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_getScaleY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_getScaleX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_getScaleX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getScaleX();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_getScaleX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_setScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_setScale : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ScaleFrame_setScale : Error processing arguments");
        cobj->setScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_setScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::ScaleFrame* ret = cocostudio::timeline::ScaleFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::ScaleFrame>(cx, (cocostudio::timeline::ScaleFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ScaleFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ScaleFrame* cobj = new (std::nothrow) cocostudio::timeline::ScaleFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::ScaleFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::ScaleFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_ScaleFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ScaleFrame)", obj);
}
void js_register_cocos2dx_studio_ScaleFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ScaleFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ScaleFrame_class->name = "ScaleFrame";
    jsb_cocostudio_timeline_ScaleFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ScaleFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ScaleFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ScaleFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ScaleFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ScaleFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ScaleFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ScaleFrame_class->finalize = js_cocostudio_timeline_ScaleFrame_finalize;
    jsb_cocostudio_timeline_ScaleFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setScaleY", js_cocos2dx_studio_ScaleFrame_setScaleY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScaleX", js_cocos2dx_studio_ScaleFrame_setScaleX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getScaleY", js_cocos2dx_studio_ScaleFrame_getScaleY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getScaleX", js_cocos2dx_studio_ScaleFrame_getScaleX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale", js_cocos2dx_studio_ScaleFrame_setScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ScaleFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_ScaleFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_ScaleFrame_class,
        js_cocos2dx_studio_ScaleFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ScaleFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::ScaleFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_ScaleFrame_class;
        p->proto = jsb_cocostudio_timeline_ScaleFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_AnchorPointFrame_class;
JSObject *jsb_cocostudio_timeline_AnchorPointFrame_prototype;

bool js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::AnchorPointFrame* cobj = (cocostudio::timeline::AnchorPointFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint : Error processing arguments");
        cobj->setAnchorPoint(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::AnchorPointFrame* cobj = (cocostudio::timeline::AnchorPointFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getAnchorPoint();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_AnchorPointFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::AnchorPointFrame* ret = cocostudio::timeline::AnchorPointFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::AnchorPointFrame>(cx, (cocostudio::timeline::AnchorPointFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_AnchorPointFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_AnchorPointFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::AnchorPointFrame* cobj = new (std::nothrow) cocostudio::timeline::AnchorPointFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::AnchorPointFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::AnchorPointFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_AnchorPointFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AnchorPointFrame)", obj);
}
void js_register_cocos2dx_studio_AnchorPointFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_AnchorPointFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_AnchorPointFrame_class->name = "AnchorPointFrame";
    jsb_cocostudio_timeline_AnchorPointFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->finalize = js_cocostudio_timeline_AnchorPointFrame_finalize;
    jsb_cocostudio_timeline_AnchorPointFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setAnchorPoint", js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnchorPoint", js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_AnchorPointFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_AnchorPointFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_AnchorPointFrame_class,
        js_cocos2dx_studio_AnchorPointFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "AnchorPointFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::AnchorPointFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_AnchorPointFrame_class;
        p->proto = jsb_cocostudio_timeline_AnchorPointFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_InnerActionFrame_class;
JSObject *jsb_cocostudio_timeline_InnerActionFrame_prototype;

bool js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getEndFrameIndex();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getStartFrameIndex();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_getInnerActionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_getInnerActionType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getInnerActionType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_getInnerActionType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex : Error processing arguments");
        cobj->setEndFrameIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setEnterWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setEnterWithName : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setEnterWithName : Error processing arguments");
        cobj->setEnterWithName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setEnterWithName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex : Error processing arguments");
        cobj->setSingleFrameIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex : Error processing arguments");
        cobj->setStartFrameIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getSingleFrameIndex();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setInnerActionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setInnerActionType : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::InnerActionType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setInnerActionType : Error processing arguments");
        cobj->setInnerActionType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setInnerActionType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setAnimationName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setAnimationName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setAnimationName : Error processing arguments");
        cobj->setAnimationName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setAnimationName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::InnerActionFrame* ret = cocostudio::timeline::InnerActionFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::InnerActionFrame>(cx, (cocostudio::timeline::InnerActionFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_InnerActionFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::InnerActionFrame* cobj = new (std::nothrow) cocostudio::timeline::InnerActionFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::InnerActionFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::InnerActionFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_InnerActionFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (InnerActionFrame)", obj);
}
void js_register_cocos2dx_studio_InnerActionFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_InnerActionFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_InnerActionFrame_class->name = "InnerActionFrame";
    jsb_cocostudio_timeline_InnerActionFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->finalize = js_cocostudio_timeline_InnerActionFrame_finalize;
    jsb_cocostudio_timeline_InnerActionFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getEndFrameIndex", js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartFrameIndex", js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInnerActionType", js_cocos2dx_studio_InnerActionFrame_getInnerActionType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndFrameIndex", js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEnterWithName", js_cocos2dx_studio_InnerActionFrame_setEnterWithName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSingleFrameIndex", js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartFrameIndex", js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSingleFrameIndex", js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInnerActionType", js_cocos2dx_studio_InnerActionFrame_setInnerActionType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimationName", js_cocos2dx_studio_InnerActionFrame_setAnimationName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_InnerActionFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_InnerActionFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_InnerActionFrame_class,
        js_cocos2dx_studio_InnerActionFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "InnerActionFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::InnerActionFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_InnerActionFrame_class;
        p->proto = jsb_cocostudio_timeline_InnerActionFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_ColorFrame_class;
JSObject *jsb_cocostudio_timeline_ColorFrame_prototype;

bool js_cocos2dx_studio_ColorFrame_getColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ColorFrame* cobj = (cocostudio::timeline::ColorFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColorFrame_getColor : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Color3B ret = cobj->getColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColorFrame_getColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ColorFrame_setColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ColorFrame* cobj = (cocostudio::timeline::ColorFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColorFrame_setColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color3B arg0;
        ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ColorFrame_setColor : Error processing arguments");
        cobj->setColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColorFrame_setColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ColorFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::ColorFrame* ret = cocostudio::timeline::ColorFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::ColorFrame>(cx, (cocostudio::timeline::ColorFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ColorFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ColorFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ColorFrame* cobj = new (std::nothrow) cocostudio::timeline::ColorFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::ColorFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::ColorFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_ColorFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ColorFrame)", obj);
}
void js_register_cocos2dx_studio_ColorFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ColorFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ColorFrame_class->name = "ColorFrame";
    jsb_cocostudio_timeline_ColorFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ColorFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ColorFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ColorFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ColorFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ColorFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ColorFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ColorFrame_class->finalize = js_cocostudio_timeline_ColorFrame_finalize;
    jsb_cocostudio_timeline_ColorFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getColor", js_cocos2dx_studio_ColorFrame_getColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setColor", js_cocos2dx_studio_ColorFrame_setColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ColorFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_ColorFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_ColorFrame_class,
        js_cocos2dx_studio_ColorFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ColorFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::ColorFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_ColorFrame_class;
        p->proto = jsb_cocostudio_timeline_ColorFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_AlphaFrame_class;
JSObject *jsb_cocostudio_timeline_AlphaFrame_prototype;

bool js_cocos2dx_studio_AlphaFrame_getAlpha(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::AlphaFrame* cobj = (cocostudio::timeline::AlphaFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AlphaFrame_getAlpha : Invalid Native Object");
    if (argc == 0) {
        uint16_t ret = cobj->getAlpha();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AlphaFrame_getAlpha : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_AlphaFrame_setAlpha(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::AlphaFrame* cobj = (cocostudio::timeline::AlphaFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AlphaFrame_setAlpha : Invalid Native Object");
    if (argc == 1) {
        uint16_t arg0;
        ok &= jsval_to_uint16(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_AlphaFrame_setAlpha : Error processing arguments");
        cobj->setAlpha(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AlphaFrame_setAlpha : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_AlphaFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::AlphaFrame* ret = cocostudio::timeline::AlphaFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::AlphaFrame>(cx, (cocostudio::timeline::AlphaFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_AlphaFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_AlphaFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::AlphaFrame* cobj = new (std::nothrow) cocostudio::timeline::AlphaFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::AlphaFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::AlphaFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_AlphaFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AlphaFrame)", obj);
}
void js_register_cocos2dx_studio_AlphaFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_AlphaFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_AlphaFrame_class->name = "AlphaFrame";
    jsb_cocostudio_timeline_AlphaFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_AlphaFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_AlphaFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_AlphaFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_AlphaFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_AlphaFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_AlphaFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_AlphaFrame_class->finalize = js_cocostudio_timeline_AlphaFrame_finalize;
    jsb_cocostudio_timeline_AlphaFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAlpha", js_cocos2dx_studio_AlphaFrame_getAlpha, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAlpha", js_cocos2dx_studio_AlphaFrame_setAlpha, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_AlphaFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_AlphaFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_AlphaFrame_class,
        js_cocos2dx_studio_AlphaFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "AlphaFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::AlphaFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_AlphaFrame_class;
        p->proto = jsb_cocostudio_timeline_AlphaFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_EventFrame_class;
JSObject *jsb_cocostudio_timeline_EventFrame_prototype;

bool js_cocos2dx_studio_EventFrame_setEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::EventFrame* cobj = (cocostudio::timeline::EventFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_EventFrame_setEvent : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_EventFrame_setEvent : Error processing arguments");
        cobj->setEvent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_EventFrame_setEvent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_EventFrame_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::EventFrame* cobj = (cocostudio::timeline::EventFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_EventFrame_init : Invalid Native Object");
    if (argc == 0) {
        cobj->init();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_EventFrame_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_EventFrame_getEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::EventFrame* cobj = (cocostudio::timeline::EventFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_EventFrame_getEvent : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getEvent();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_EventFrame_getEvent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_EventFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::EventFrame* ret = cocostudio::timeline::EventFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::EventFrame>(cx, (cocostudio::timeline::EventFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_EventFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_EventFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::EventFrame* cobj = new (std::nothrow) cocostudio::timeline::EventFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::EventFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::EventFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_EventFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EventFrame)", obj);
}
void js_register_cocos2dx_studio_EventFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_EventFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_EventFrame_class->name = "EventFrame";
    jsb_cocostudio_timeline_EventFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_EventFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_EventFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_EventFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_EventFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_EventFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_EventFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_EventFrame_class->finalize = js_cocostudio_timeline_EventFrame_finalize;
    jsb_cocostudio_timeline_EventFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setEvent", js_cocos2dx_studio_EventFrame_setEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_EventFrame_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEvent", js_cocos2dx_studio_EventFrame_getEvent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_EventFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_EventFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_EventFrame_class,
        js_cocos2dx_studio_EventFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "EventFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::EventFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_EventFrame_class;
        p->proto = jsb_cocostudio_timeline_EventFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_ZOrderFrame_class;
JSObject *jsb_cocostudio_timeline_ZOrderFrame_prototype;

bool js_cocos2dx_studio_ZOrderFrame_getZOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ZOrderFrame* cobj = (cocostudio::timeline::ZOrderFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ZOrderFrame_getZOrder : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getZOrder();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ZOrderFrame_getZOrder : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ZOrderFrame_setZOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ZOrderFrame* cobj = (cocostudio::timeline::ZOrderFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ZOrderFrame_setZOrder : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ZOrderFrame_setZOrder : Error processing arguments");
        cobj->setZOrder(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ZOrderFrame_setZOrder : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ZOrderFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::ZOrderFrame* ret = cocostudio::timeline::ZOrderFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::ZOrderFrame>(cx, (cocostudio::timeline::ZOrderFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ZOrderFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ZOrderFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ZOrderFrame* cobj = new (std::nothrow) cocostudio::timeline::ZOrderFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::ZOrderFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::ZOrderFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_ZOrderFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ZOrderFrame)", obj);
}
void js_register_cocos2dx_studio_ZOrderFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ZOrderFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ZOrderFrame_class->name = "ZOrderFrame";
    jsb_cocostudio_timeline_ZOrderFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->finalize = js_cocostudio_timeline_ZOrderFrame_finalize;
    jsb_cocostudio_timeline_ZOrderFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getZOrder", js_cocos2dx_studio_ZOrderFrame_getZOrder, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZOrder", js_cocos2dx_studio_ZOrderFrame_setZOrder, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ZOrderFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_ZOrderFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_ZOrderFrame_class,
        js_cocos2dx_studio_ZOrderFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ZOrderFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::ZOrderFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_ZOrderFrame_class;
        p->proto = jsb_cocostudio_timeline_ZOrderFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_BlendFuncFrame_class;
JSObject *jsb_cocostudio_timeline_BlendFuncFrame_prototype;

bool js_cocos2dx_studio_BlendFuncFrame_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BlendFuncFrame* cobj = (cocostudio::timeline::BlendFuncFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BlendFuncFrame_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        cocos2d::BlendFunc ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BlendFuncFrame_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BlendFuncFrame_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BlendFuncFrame* cobj = (cocostudio::timeline::BlendFuncFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BlendFuncFrame_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BlendFuncFrame_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BlendFuncFrame_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BlendFuncFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::BlendFuncFrame* ret = cocostudio::timeline::BlendFuncFrame::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::BlendFuncFrame>(cx, (cocostudio::timeline::BlendFuncFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_BlendFuncFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_BlendFuncFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::BlendFuncFrame* cobj = new (std::nothrow) cocostudio::timeline::BlendFuncFrame();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::BlendFuncFrame> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::BlendFuncFrame");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_cocostudio_timeline_BlendFuncFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (BlendFuncFrame)", obj);
}
void js_register_cocos2dx_studio_BlendFuncFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_BlendFuncFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_BlendFuncFrame_class->name = "BlendFuncFrame";
    jsb_cocostudio_timeline_BlendFuncFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->finalize = js_cocostudio_timeline_BlendFuncFrame_finalize;
    jsb_cocostudio_timeline_BlendFuncFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBlendFunc", js_cocos2dx_studio_BlendFuncFrame_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_studio_BlendFuncFrame_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_BlendFuncFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_BlendFuncFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_Frame_prototype),
        jsb_cocostudio_timeline_BlendFuncFrame_class,
        js_cocos2dx_studio_BlendFuncFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "BlendFuncFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::BlendFuncFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_BlendFuncFrame_class;
        p->proto = jsb_cocostudio_timeline_BlendFuncFrame_prototype;
        p->parentProto = jsb_cocostudio_timeline_Frame_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_Timeline_class;
JSObject *jsb_cocostudio_timeline_Timeline_prototype;

bool js_cocos2dx_studio_Timeline_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_clone : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::Timeline* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::Timeline>(cx, (cocostudio::timeline::Timeline*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_gotoFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_gotoFrame : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_gotoFrame : Error processing arguments");
        cobj->gotoFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_gotoFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_setNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_setNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_setNode : Error processing arguments");
        cobj->setNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_setNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_getActionTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_getActionTimeline : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::ActionTimeline* ret = cobj->getActionTimeline();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::ActionTimeline>(cx, (cocostudio::timeline::ActionTimeline*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_getActionTimeline : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_insertFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_insertFrame : Invalid Native Object");
    if (argc == 2) {
        cocostudio::timeline::Frame* arg0 = nullptr;
        int arg1 = 0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Frame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_insertFrame : Error processing arguments");
        cobj->insertFrame(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_insertFrame : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Timeline_setActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_setActionTag : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_setActionTag : Error processing arguments");
        cobj->setActionTag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_setActionTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_addFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_addFrame : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Frame* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Frame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_addFrame : Error processing arguments");
        cobj->addFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_addFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_getFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_getFrames : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vector<cocostudio::timeline::Frame *>& ret = cobj->getFrames();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_getFrames : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_getActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_getActionTag : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getActionTag();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_getActionTag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_getNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_getNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_getNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_removeFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_removeFrame : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Frame* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Frame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_removeFrame : Error processing arguments");
        cobj->removeFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_removeFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_setActionTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_setActionTimeline : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::ActionTimeline* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::ActionTimeline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_setActionTimeline : Error processing arguments");
        cobj->setActionTimeline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_setActionTimeline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_stepToFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_stepToFrame : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_stepToFrame : Error processing arguments");
        cobj->stepToFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_stepToFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::Timeline* ret = cocostudio::timeline::Timeline::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::Timeline>(cx, (cocostudio::timeline::Timeline*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_Timeline_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::Timeline* cobj = new (std::nothrow) cocostudio::timeline::Timeline();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::Timeline> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::Timeline");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_cocostudio_timeline_Timeline_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Timeline)", obj);
}
void js_register_cocos2dx_studio_Timeline(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_Timeline_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_Timeline_class->name = "Timeline";
    jsb_cocostudio_timeline_Timeline_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_Timeline_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_Timeline_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_Timeline_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_Timeline_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_Timeline_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_Timeline_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_Timeline_class->finalize = js_cocostudio_timeline_Timeline_finalize;
    jsb_cocostudio_timeline_Timeline_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("clone", js_cocos2dx_studio_Timeline_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoFrame", js_cocos2dx_studio_Timeline_gotoFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNode", js_cocos2dx_studio_Timeline_setNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTimeline", js_cocos2dx_studio_Timeline_getActionTimeline, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertFrame", js_cocos2dx_studio_Timeline_insertFrame, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActionTag", js_cocos2dx_studio_Timeline_setActionTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addFrame", js_cocos2dx_studio_Timeline_addFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrames", js_cocos2dx_studio_Timeline_getFrames, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTag", js_cocos2dx_studio_Timeline_getActionTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNode", js_cocos2dx_studio_Timeline_getNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFrame", js_cocos2dx_studio_Timeline_removeFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActionTimeline", js_cocos2dx_studio_Timeline_setActionTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stepToFrame", js_cocos2dx_studio_Timeline_stepToFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_Timeline_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_Timeline_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocostudio_timeline_Timeline_class,
        js_cocos2dx_studio_Timeline_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Timeline", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::Timeline> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_Timeline_class;
        p->proto = jsb_cocostudio_timeline_Timeline_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_ActionTimelineData_class;
JSObject *jsb_cocostudio_timeline_ActionTimelineData_prototype;

bool js_cocos2dx_studio_ActionTimelineData_setActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimelineData* cobj = (cocostudio::timeline::ActionTimelineData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimelineData_setActionTag : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimelineData_setActionTag : Error processing arguments");
        cobj->setActionTag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimelineData_setActionTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimelineData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimelineData* cobj = (cocostudio::timeline::ActionTimelineData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimelineData_init : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimelineData_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimelineData_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimelineData_getActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimelineData* cobj = (cocostudio::timeline::ActionTimelineData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimelineData_getActionTag : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getActionTag();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimelineData_getActionTag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimelineData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimelineData_create : Error processing arguments");
        cocostudio::timeline::ActionTimelineData* ret = cocostudio::timeline::ActionTimelineData::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::ActionTimelineData>(cx, (cocostudio::timeline::ActionTimelineData*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimelineData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ActionTimelineData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ActionTimelineData* cobj = new (std::nothrow) cocostudio::timeline::ActionTimelineData();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::ActionTimelineData> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::ActionTimelineData");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_cocostudio_timeline_ActionTimelineData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ActionTimelineData)", obj);
}
void js_register_cocos2dx_studio_ActionTimelineData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ActionTimelineData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ActionTimelineData_class->name = "ActionTimelineData";
    jsb_cocostudio_timeline_ActionTimelineData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->finalize = js_cocostudio_timeline_ActionTimelineData_finalize;
    jsb_cocostudio_timeline_ActionTimelineData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setActionTag", js_cocos2dx_studio_ActionTimelineData_setActionTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_ActionTimelineData_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTag", js_cocos2dx_studio_ActionTimelineData_getActionTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ActionTimelineData_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_ActionTimelineData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocostudio_timeline_ActionTimelineData_class,
        js_cocos2dx_studio_ActionTimelineData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ActionTimelineData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::ActionTimelineData> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_ActionTimelineData_class;
        p->proto = jsb_cocostudio_timeline_ActionTimelineData_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_ActionTimeline_class;
JSObject *jsb_cocostudio_timeline_ActionTimeline_prototype;

bool js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc : Invalid Native Object");
    if (argc == 1) {
        std::function<void (cocostudio::timeline::Frame *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](cocostudio::timeline::Frame* larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::Frame>(cx, (cocostudio::timeline::Frame*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(1, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc : Error processing arguments");
        cobj->setFrameEventCallFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs : Invalid Native Object");
    if (argc == 0) {
        cobj->clearFrameEndCallFuncs();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::function<void ()> arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
		    if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(1)));
		        auto lambda = [=]() -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(0, nullptr, &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg1 = lambda;
		    }
		    else
		    {
		        arg1 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc : Error processing arguments");
        cobj->setAnimationEndCallFunc(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_addTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_addTimeline : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Timeline* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Timeline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_addTimeline : Error processing arguments");
        cobj->addTimeline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_addTimeline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getCurrentFrame : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCurrentFrame();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getCurrentFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getStartFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getStartFrame : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getStartFrame();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getStartFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_pause : Invalid Native Object");
    if (argc == 0) {
        cobj->pause();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_pause : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_removeTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_removeTimeline : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Timeline* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Timeline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_removeTimeline : Error processing arguments");
        cobj->removeTimeline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_removeTimeline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc : Invalid Native Object");
    if (argc == 1) {
        std::function<void ()> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=]() -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(0, nullptr, &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc : Error processing arguments");
        cobj->setLastFrameCallFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists : Error processing arguments");
        bool ret = cobj->IsAnimationInfoExists(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getTimelines(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getTimelines : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vector<cocostudio::timeline::Timeline *>& ret = cobj->getTimelines();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getTimelines : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_play : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_play : Error processing arguments");
        cobj->play(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_play : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getAnimationInfo : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_getAnimationInfo : Error processing arguments");
        const cocostudio::timeline::AnimationInfo& ret = cobj->getAnimationInfo(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = animationInfo_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getAnimationInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_resume : Invalid Native Object");
    if (argc == 0) {
        cobj->resume();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_resume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc : Invalid Native Object");
    if (argc == 3) {
        int arg0 = 0;
        std::string arg1;
        std::function<void ()> arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
		    if(JS_TypeOfValue(cx, args.get(2)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(2)));
		        auto lambda = [=]() -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(0, nullptr, &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg2 = lambda;
		    }
		    else
		    {
		        arg2 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc : Error processing arguments");
        cobj->addFrameEndCallFunc(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_removeAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_removeAnimationInfo : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_removeAnimationInfo : Error processing arguments");
        cobj->removeAnimationInfo(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_removeAnimationInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getTimeSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getTimeSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTimeSpeed();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getTimeSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_addAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_addAnimationInfo : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::AnimationInfo arg0;
        ok &= jsval_to_animationInfo(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_addAnimationInfo : Error processing arguments");
        cobj->addAnimationInfo(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_addAnimationInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getDuration : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getDuration();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getDuration : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause : Error processing arguments");
        cobj->gotoFrameAndPause(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_isPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_isPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPlaying();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_isPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs : Error processing arguments");
        cobj->removeFrameEndCallFuncs(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay : Invalid Native Object");
    do {
        if (argc == 2) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->gotoFrameAndPlay(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cobj->gotoFrameAndPlay(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 3) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            cobj->gotoFrameAndPlay(arg0, arg1, arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 4) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            int arg2 = 0;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            bool arg3;
            arg3 = JS::ToBoolean(args.get(3));
            cobj->gotoFrameAndPlay(arg0, arg1, arg2, arg3);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc : Invalid Native Object");
    if (argc == 0) {
        cobj->clearFrameEventCallFunc();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getEndFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getEndFrame : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getEndFrame();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getEndFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setTimeSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setTimeSpeed : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setTimeSpeed : Error processing arguments");
        cobj->setTimeSpeed(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setTimeSpeed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc : Invalid Native Object");
    if (argc == 0) {
        cobj->clearLastFrameCallFunc();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setDuration : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setDuration : Error processing arguments");
        cobj->setDuration(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setDuration : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setCurrentFrame : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setCurrentFrame : Error processing arguments");
        cobj->setCurrentFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setCurrentFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc : Invalid Native Object");
    if (argc == 2) {
        int arg0 = 0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc : Error processing arguments");
        cobj->removeFrameEndCallFunc(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::ActionTimeline* ret = cocostudio::timeline::ActionTimeline::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::ActionTimeline>(cx, (cocostudio::timeline::ActionTimeline*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ActionTimeline_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ActionTimeline* cobj = new (std::nothrow) cocostudio::timeline::ActionTimeline();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::ActionTimeline> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::ActionTimeline");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_Action_prototype;

void js_cocostudio_timeline_ActionTimeline_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ActionTimeline)", obj);
}
void js_register_cocos2dx_studio_ActionTimeline(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ActionTimeline_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ActionTimeline_class->name = "ActionTimeline";
    jsb_cocostudio_timeline_ActionTimeline_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ActionTimeline_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ActionTimeline_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ActionTimeline_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ActionTimeline_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ActionTimeline_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ActionTimeline_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ActionTimeline_class->finalize = js_cocostudio_timeline_ActionTimeline_finalize;
    jsb_cocostudio_timeline_ActionTimeline_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setFrameEventCallFunc", js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearFrameEndCallFuncs", js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimationEndCallFunc", js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addTimeline", js_cocos2dx_studio_ActionTimeline_addTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentFrame", js_cocos2dx_studio_ActionTimeline_getCurrentFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartFrame", js_cocos2dx_studio_ActionTimeline_getStartFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_cocos2dx_studio_ActionTimeline_pause, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_ActionTimeline_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeTimeline", js_cocos2dx_studio_ActionTimeline_removeTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLastFrameCallFunc", js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isAnimationInfoExists", js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimelines", js_cocos2dx_studio_ActionTimeline_getTimelines, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_studio_ActionTimeline_play, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimationInfo", js_cocos2dx_studio_ActionTimeline_getAnimationInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_cocos2dx_studio_ActionTimeline_resume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addFrameEndCallFunc", js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAnimationInfo", js_cocos2dx_studio_ActionTimeline_removeAnimationInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeSpeed", js_cocos2dx_studio_ActionTimeline_getTimeSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addAnimationInfo", js_cocos2dx_studio_ActionTimeline_addAnimationInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDuration", js_cocos2dx_studio_ActionTimeline_getDuration, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoFrameAndPause", js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPlaying", js_cocos2dx_studio_ActionTimeline_isPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFrameEndCallFuncs", js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoFrameAndPlay", js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearFrameEventCallFunc", js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndFrame", js_cocos2dx_studio_ActionTimeline_getEndFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTimeSpeed", js_cocos2dx_studio_ActionTimeline_setTimeSpeed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearLastFrameCallFunc", js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDuration", js_cocos2dx_studio_ActionTimeline_setDuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCurrentFrame", js_cocos2dx_studio_ActionTimeline_setCurrentFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFrameEndCallFunc", js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ActionTimeline_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_ActionTimeline_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Action_prototype),
        jsb_cocostudio_timeline_ActionTimeline_class,
        js_cocos2dx_studio_ActionTimeline_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ActionTimeline", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::ActionTimeline> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_ActionTimeline_class;
        p->proto = jsb_cocostudio_timeline_ActionTimeline_prototype;
        p->parentProto = jsb_cocos2d_Action_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocostudio_timeline_BoneNode_class;
JSObject *jsb_cocostudio_timeline_BoneNode_prototype;

bool js_cocos2dx_studio_BoneNode_getDebugDrawWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getDebugDrawWidth : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDebugDrawWidth();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getDebugDrawWidth : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getChildBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getChildBones : Invalid Native Object");
    do {
        if (argc == 0) {
            cocos2d::Vector<cocostudio::timeline::BoneNode *>& ret = cobj->getChildBones();
            jsval jsret = JSVAL_NULL;
            jsret = ccvector_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            const cocos2d::Vector<cocostudio::timeline::BoneNode *>& ret = cobj->getChildBones();
            jsval jsret = JSVAL_NULL;
            jsret = ccvector_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getChildBones : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getAllSubBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getAllSubBones : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocostudio::timeline::BoneNode *> ret = cobj->getAllSubBones();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getAllSubBones : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawEnabled : Error processing arguments");
        cobj->setDebugDrawEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setDebugDrawEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getVisibleSkinsRect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getVisibleSkinsRect : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getVisibleSkinsRect();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getVisibleSkinsRect : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getAllSubSkins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getAllSubSkins : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *> ret = cobj->getAllSubSkins();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getAllSubSkins : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_displaySkin(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_displaySkin : Invalid Native Object");
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->displaySkin(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::timeline::SkinNode*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->displaySkin(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_displaySkin : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_isDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_isDebugDrawEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isDebugDrawEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_isDebugDrawEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_addSkin(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_addSkin : Invalid Native Object");
    do {
        if (argc == 3) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::timeline::SkinNode*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            cobj->addSkin(arg0, arg1, arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::timeline::SkinNode*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->addSkin(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_addSkin : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_getRootSkeletonNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getRootSkeletonNode : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::SkeletonNode* ret = cobj->getRootSkeletonNode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::SkeletonNode>(cx, (cocostudio::timeline::SkeletonNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getRootSkeletonNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setDebugDrawLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawLength : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawLength : Error processing arguments");
        cobj->setDebugDrawLength(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setDebugDrawLength : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getSkins(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getSkins : Invalid Native Object");
    do {
        if (argc == 0) {
            cocos2d::Vector<cocos2d::Node *>& ret = cobj->getSkins();
            jsval jsret = JSVAL_NULL;
            jsret = ccvector_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::Node *>& ret = cobj->getSkins();
            jsval jsret = JSVAL_NULL;
            jsret = ccvector_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getSkins : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_getVisibleSkins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getVisibleSkins : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *> ret = cobj->getVisibleSkins();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getVisibleSkins : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setDebugDrawWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawWidth : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawWidth : Error processing arguments");
        cobj->setDebugDrawWidth(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setDebugDrawWidth : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getDebugDrawLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getDebugDrawLength : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDebugDrawLength();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getDebugDrawLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setDebugDrawColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4F arg0;
        ok &= jsval_to_cccolor4f(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawColor : Error processing arguments");
        cobj->setDebugDrawColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setDebugDrawColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getDebugDrawColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getDebugDrawColor : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Color4F ret = cobj->getDebugDrawColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor4f_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getDebugDrawColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cocostudio::timeline::BoneNode* ret = cocostudio::timeline::BoneNode::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::BoneNode>(cx, (cocostudio::timeline::BoneNode*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocostudio::timeline::BoneNode* ret = cocostudio::timeline::BoneNode::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::BoneNode>(cx, (cocostudio::timeline::BoneNode*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = new (std::nothrow) cocostudio::timeline::BoneNode();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::BoneNode> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::BoneNode");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}static bool js_cocos2dx_studio_BoneNode_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocostudio::timeline::BoneNode *nobj = new (std::nothrow) cocostudio::timeline::BoneNode();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::BoneNode");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}

extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocostudio_timeline_BoneNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (BoneNode)", obj);
}
    
void js_register_cocos2dx_studio_BoneNode(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_BoneNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_BoneNode_class->name = "BoneNode";
    jsb_cocostudio_timeline_BoneNode_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_BoneNode_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_BoneNode_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_BoneNode_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_BoneNode_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_BoneNode_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_BoneNode_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_BoneNode_class->finalize = js_cocostudio_timeline_BoneNode_finalize;
    jsb_cocostudio_timeline_BoneNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getDebugDrawWidth", js_cocos2dx_studio_BoneNode_getDebugDrawWidth, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getChildBones", js_cocos2dx_studio_BoneNode_getChildBones, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_studio_BoneNode_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAllSubBones", js_cocos2dx_studio_BoneNode_getAllSubBones, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_studio_BoneNode_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawEnabled", js_cocos2dx_studio_BoneNode_setDebugDrawEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVisibleSkinsRect", js_cocos2dx_studio_BoneNode_getVisibleSkinsRect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAllSubSkins", js_cocos2dx_studio_BoneNode_getAllSubSkins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("displaySkin", js_cocos2dx_studio_BoneNode_displaySkin, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isDebugDrawEnabled", js_cocos2dx_studio_BoneNode_isDebugDrawEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addSkin", js_cocos2dx_studio_BoneNode_addSkin, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRootSkeletonNode", js_cocos2dx_studio_BoneNode_getRootSkeletonNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawLength", js_cocos2dx_studio_BoneNode_setDebugDrawLength, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSkins", js_cocos2dx_studio_BoneNode_getSkins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVisibleSkins", js_cocos2dx_studio_BoneNode_getVisibleSkins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawWidth", js_cocos2dx_studio_BoneNode_setDebugDrawWidth, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDebugDrawLength", js_cocos2dx_studio_BoneNode_getDebugDrawLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawColor", js_cocos2dx_studio_BoneNode_setDebugDrawColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDebugDrawColor", js_cocos2dx_studio_BoneNode_getDebugDrawColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_studio_BoneNode_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_BoneNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_BoneNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_cocostudio_timeline_BoneNode_class,
        js_cocos2dx_studio_BoneNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "BoneNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::BoneNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_BoneNode_class;
        p->proto = jsb_cocostudio_timeline_BoneNode_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
    anonEvaluate(cx, global, "(function () { ccs.BoneNode.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocostudio_timeline_SkeletonNode_class;
JSObject *jsb_cocostudio_timeline_SkeletonNode_prototype;

bool js_cocos2dx_studio_SkeletonNode_getBoneNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkeletonNode* cobj = (cocostudio::timeline::SkeletonNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkeletonNode_getBoneNode : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_SkeletonNode_getBoneNode : Error processing arguments");
        cocostudio::timeline::BoneNode* ret = cobj->getBoneNode(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::BoneNode>(cx, (cocostudio::timeline::BoneNode*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_getBoneNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_SkeletonNode_changeSkins(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::SkeletonNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::SkeletonNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkeletonNode_changeSkins : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->changeSkins(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::map<std::string, std::string> arg0;
            ok &= jsval_to_std_map_string_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->changeSkins(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_changeSkins : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_SkeletonNode_addSkinGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkeletonNode* cobj = (cocostudio::timeline::SkeletonNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkeletonNode_addSkinGroup : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::map<std::string, std::string> arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_map_string_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_SkeletonNode_addSkinGroup : Error processing arguments");
        cobj->addSkinGroup(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_addSkinGroup : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkeletonNode* cobj = (cocostudio::timeline::SkeletonNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Map<std::string, cocostudio::timeline::BoneNode *>& ret = cobj->getAllSubBonesMap();
        jsval jsret = JSVAL_NULL;
        jsret = ccmap_string_key_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_SkeletonNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::timeline::SkeletonNode* ret = cocostudio::timeline::SkeletonNode::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::timeline::SkeletonNode>(cx, (cocostudio::timeline::SkeletonNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_SkeletonNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::SkeletonNode* cobj = new (std::nothrow) cocostudio::timeline::SkeletonNode();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::timeline::SkeletonNode> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::SkeletonNode");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}static bool js_cocos2dx_studio_SkeletonNode_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocostudio::timeline::SkeletonNode *nobj = new (std::nothrow) cocostudio::timeline::SkeletonNode();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::timeline::SkeletonNode");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}

extern JSObject *jsb_cocostudio_timeline_BoneNode_prototype;

void js_cocostudio_timeline_SkeletonNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SkeletonNode)", obj);
}
    
void js_register_cocos2dx_studio_SkeletonNode(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_SkeletonNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_SkeletonNode_class->name = "SkeletonNode";
    jsb_cocostudio_timeline_SkeletonNode_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_SkeletonNode_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_SkeletonNode_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_SkeletonNode_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_SkeletonNode_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_SkeletonNode_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_SkeletonNode_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_SkeletonNode_class->finalize = js_cocostudio_timeline_SkeletonNode_finalize;
    jsb_cocostudio_timeline_SkeletonNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBoneNode", js_cocos2dx_studio_SkeletonNode_getBoneNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeSkins", js_cocos2dx_studio_SkeletonNode_changeSkins, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addSkinGroup", js_cocos2dx_studio_SkeletonNode_addSkinGroup, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAllSubBonesMap", js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_studio_SkeletonNode_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_SkeletonNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_SkeletonNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocostudio_timeline_BoneNode_prototype),
        jsb_cocostudio_timeline_SkeletonNode_class,
        js_cocos2dx_studio_SkeletonNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SkeletonNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::timeline::SkeletonNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_timeline_SkeletonNode_class;
        p->proto = jsb_cocostudio_timeline_SkeletonNode_prototype;
        p->parentProto = jsb_cocostudio_timeline_BoneNode_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
    anonEvaluate(cx, global, "(function () { ccs.SkeletonNode.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocostudio_ComExtensionData_class;
JSObject *jsb_cocostudio_ComExtensionData_prototype;

bool js_cocos2dx_studio_ComExtensionData_setActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComExtensionData* cobj = (cocostudio::ComExtensionData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComExtensionData_setActionTag : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComExtensionData_setActionTag : Error processing arguments");
        cobj->setActionTag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_setActionTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComExtensionData_getCustomProperty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComExtensionData* cobj = (cocostudio::ComExtensionData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComExtensionData_getCustomProperty : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getCustomProperty();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_getCustomProperty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComExtensionData_getActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComExtensionData* cobj = (cocostudio::ComExtensionData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComExtensionData_getActionTag : Invalid Native Object");
    if (argc == 0) {
        const int ret = cobj->getActionTag();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_getActionTag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComExtensionData_setCustomProperty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComExtensionData* cobj = (cocostudio::ComExtensionData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComExtensionData_setCustomProperty : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComExtensionData_setCustomProperty : Error processing arguments");
        cobj->setCustomProperty(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_setCustomProperty : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComExtensionData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::ComExtensionData* ret = cocostudio::ComExtensionData::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ComExtensionData>(cx, (cocostudio::ComExtensionData*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ComExtensionData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ComExtensionData* cobj = new (std::nothrow) cocostudio::ComExtensionData();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocostudio::ComExtensionData> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocostudio::ComExtensionData");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_Component_prototype;

void js_cocostudio_ComExtensionData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ComExtensionData)", obj);
}
void js_register_cocos2dx_studio_ComExtensionData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComExtensionData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComExtensionData_class->name = "ComExtensionData";
    jsb_cocostudio_ComExtensionData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComExtensionData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComExtensionData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComExtensionData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComExtensionData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComExtensionData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComExtensionData_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComExtensionData_class->finalize = js_cocostudio_ComExtensionData_finalize;
    jsb_cocostudio_ComExtensionData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setActionTag", js_cocos2dx_studio_ComExtensionData_setActionTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCustomProperty", js_cocos2dx_studio_ComExtensionData_getCustomProperty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTag", js_cocos2dx_studio_ComExtensionData_getActionTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCustomProperty", js_cocos2dx_studio_ComExtensionData_setCustomProperty, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComExtensionData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ComExtensionData_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Component_prototype),
        jsb_cocostudio_ComExtensionData_class,
        js_cocos2dx_studio_ComExtensionData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ComExtensionData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocostudio::ComExtensionData> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocostudio_ComExtensionData_class;
        p->proto = jsb_cocostudio_ComExtensionData_prototype;
        p->parentProto = jsb_cocos2d_Component_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ccs", &ns);

    js_register_cocos2dx_studio_BoneNode(cx, ns);
    js_register_cocos2dx_studio_SkeletonNode(cx, ns);
    js_register_cocos2dx_studio_Frame(cx, ns);
    js_register_cocos2dx_studio_ScaleFrame(cx, ns);
    js_register_cocos2dx_studio_ComAudio(cx, ns);
    js_register_cocos2dx_studio_ActionTimelineData(cx, ns);
    js_register_cocos2dx_studio_ColorFrame(cx, ns);
    js_register_cocos2dx_studio_RotationFrame(cx, ns);
    js_register_cocos2dx_studio_ZOrderFrame(cx, ns);
    js_register_cocos2dx_studio_Timeline(cx, ns);
    js_register_cocos2dx_studio_InputDelegate(cx, ns);
    js_register_cocos2dx_studio_ComController(cx, ns);
    js_register_cocos2dx_studio_PositionFrame(cx, ns);
    js_register_cocos2dx_studio_SkewFrame(cx, ns);
    js_register_cocos2dx_studio_RotationSkewFrame(cx, ns);
    js_register_cocos2dx_studio_VisibleFrame(cx, ns);
    js_register_cocos2dx_studio_ActionTimeline(cx, ns);
    js_register_cocos2dx_studio_ActionObject(cx, ns);
    js_register_cocos2dx_studio_EventFrame(cx, ns);
    js_register_cocos2dx_studio_ComAttribute(cx, ns);
    js_register_cocos2dx_studio_BlendFuncFrame(cx, ns);
    js_register_cocos2dx_studio_InnerActionFrame(cx, ns);
    js_register_cocos2dx_studio_ActionManagerEx(cx, ns);
    js_register_cocos2dx_studio_ComRender(cx, ns);
    js_register_cocos2dx_studio_AlphaFrame(cx, ns);
    js_register_cocos2dx_studio_ComExtensionData(cx, ns);
    js_register_cocos2dx_studio_AnchorPointFrame(cx, ns);
    js_register_cocos2dx_studio_TextureFrame(cx, ns);
}

