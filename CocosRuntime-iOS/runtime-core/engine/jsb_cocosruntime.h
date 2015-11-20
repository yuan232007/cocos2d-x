//
//  jsb_cocosruntime.h
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/23.
//
#ifndef __JSB_COCOSRUNTIME_H__
#define __JSB_COCOSRUNTIME_H__

#include "spidermonkey/jsapi.h"

void jsb_register_cocosruntime(JSContext *_cx, JS::HandleObject object);

#endif /* __JSB_COCOSRUNTIME_H__ */
