/*
 * Created by LinWenhai on 20/10/13.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "jsb_cocos2dx_studio_manual.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "cocostudio/CocoStudio.h"

static bool js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx : Invalid Native Object");
    if (argc == 3) {
        const char* arg0;
        const char* arg1;
        cocos2d::Ref* arg2;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        rapidjson::Document arg1Jsondoc;
        arg1Jsondoc.Parse<0>(arg1);
        if (arg1Jsondoc.HasParseError()) {
            CCLOG("GetParseError %d\n",arg1Jsondoc.GetParseError());
        }
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx : Error processing arguments");
        cobj->initWithDictionary(arg0, arg1Jsondoc, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}

static bool js_cocos2dx_studio_Frame_setEasingParams(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if(argc == 1)
    {
        JS::RootedObject jsobj(cx);
        bool ok = args.get(0).isObject() && JS_ValueToObject( cx, args.get(0), &jsobj );
        JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
        JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "argument must be an array");

        std::vector<float> arg0;
        uint32_t length = 0;
        ok &= JS_GetArrayLength(cx, jsobj, & length);
        arg0.reserve(length);

        for (uint32_t i = 0; i < length; ++i)
        {
            JS::RootedValue value(cx);
            if (JS_GetElement(cx, jsobj, i, &value))
            {
                arg0.push_back(value.toNumber());
            }
            else
            {
                ok = false;
                break;
            }
        }
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setEasingParams : Error processing arguments");

        cobj->setEasingParams(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

static bool js_cocos2dx_studio_Frame_getEasingParams(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if(argc == 0)
    {
        const std::vector<float> ret = cobj->getEasingParams();

        JS::RootedObject jsobj(cx, JS_NewArrayObject(cx, ret.size()));
        bool ok = true;
        for(size_t i = 0; i < ret.size(); ++i)
        {
            ok &= JS_SetElement(cx, jsobj, i, ret[i]);
        }
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_getEasingParams : Error processing arguments");

        args.rval().set(OBJECT_TO_JSVAL(jsobj));
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

extern JSObject* jsb_cocostudio_AnimationData_prototype;
extern JSObject* jsb_cocostudio_ActionManagerEx_prototype;
extern JSObject* jsb_cocostudio_timeline_Frame_prototype;

void register_all_cocos2dx_studio_manual(JSContext* cx, JS::HandleObject global)
{
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocostudio_ActionManagerEx_prototype), "initWithDictionaryEx", js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    JS::RootedObject frame(cx, jsb_cocostudio_timeline_Frame_prototype);
    JS_DefineFunction(cx, frame, "setEasingParams", js_cocos2dx_studio_Frame_setEasingParams, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, frame, "getEasingParams", js_cocos2dx_studio_Frame_getEasingParams, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE);
}
