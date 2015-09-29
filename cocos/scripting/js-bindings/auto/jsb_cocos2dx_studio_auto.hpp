#include "base/ccConfig.h"
#ifndef __cocos2dx_studio_h__
#define __cocos2dx_studio_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocostudio_ActionObject_class;
extern JSObject *jsb_cocostudio_ActionObject_prototype;

bool js_cocos2dx_studio_ActionObject_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionObject_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionObject(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ActionObject_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_setName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_setUnitTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getTotalTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_removeActionNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_initWithBinary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_addActionNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getUnitTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_isPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_updateToFrameByTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_simulationActionUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_ActionObject(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ActionManagerEx_class;
extern JSObject *jsb_cocostudio_ActionManagerEx_prototype;

bool js_cocos2dx_studio_ActionManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionManagerEx_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionManagerEx(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ActionManagerEx_stopActionByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_getActionByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_initWithBinary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_playActionByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_releaseActions(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComAttribute_class;
extern JSObject *jsb_cocostudio_ComAttribute_prototype;

bool js_cocos2dx_studio_ComAttribute_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComAttribute_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComAttribute(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComAttribute_getFloat(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_getBool(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_getString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_setFloat(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_setString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_setInt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_parse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_getInt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_setBool(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_ComAttribute(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComAudio_class;
extern JSObject *jsb_cocostudio_ComAudio_prototype;

bool js_cocos2dx_studio_ComAudio_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComAudio_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComAudio(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComAudio_stopAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_getEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_stopEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_end(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_stopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_pauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_isLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_resumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_pauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_preloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_playBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_playEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_preloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_unloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_rewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_pauseEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_resumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_setFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_setEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_getFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_resumeEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_ComAudio(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_InputDelegate_class;
extern JSObject *jsb_cocostudio_InputDelegate_prototype;

bool js_cocos2dx_studio_InputDelegate_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_InputDelegate_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_InputDelegate(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_getTouchMode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_isKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setTouchPriority(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_getTouchPriority(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setTouchMode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComController_class;
extern JSObject *jsb_cocostudio_ComController_prototype;

bool js_cocos2dx_studio_ComController_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComController_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComController(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComController_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComController_ComController(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComRender_class;
extern JSObject *jsb_cocostudio_ComRender_prototype;

bool js_cocos2dx_studio_ComRender_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComRender_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComRender(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComRender_setNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComRender_getNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComRender_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComRender_ComRender(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_Frame_class;
extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

bool js_cocos2dx_studio_Frame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Frame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Frame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_Frame_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setTweenType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_isEnterWhenPassed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_getTweenType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_getFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_apply(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_isTween(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setTween(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_getTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_getNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_VisibleFrame_class;
extern JSObject *jsb_cocostudio_timeline_VisibleFrame_prototype;

bool js_cocos2dx_studio_VisibleFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_VisibleFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_VisibleFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_VisibleFrame_isVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_VisibleFrame_setVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_VisibleFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_VisibleFrame_VisibleFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_TextureFrame_class;
extern JSObject *jsb_cocostudio_timeline_TextureFrame_prototype;

bool js_cocos2dx_studio_TextureFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_TextureFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_TextureFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_TextureFrame_getTextureName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureFrame_setTextureName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureFrame_TextureFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_RotationFrame_class;
extern JSObject *jsb_cocostudio_timeline_RotationFrame_prototype;

bool js_cocos2dx_studio_RotationFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_RotationFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_RotationFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_RotationFrame_setRotation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_RotationFrame_getRotation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_RotationFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_RotationFrame_RotationFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_SkewFrame_class;
extern JSObject *jsb_cocostudio_timeline_SkewFrame_prototype;

bool js_cocos2dx_studio_SkewFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_SkewFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_SkewFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_SkewFrame_getSkewY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_setSkewX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_setSkewY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_getSkewX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_SkewFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_RotationSkewFrame_class;
extern JSObject *jsb_cocostudio_timeline_RotationSkewFrame_prototype;

bool js_cocos2dx_studio_RotationSkewFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_RotationSkewFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_RotationSkewFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_RotationSkewFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_RotationSkewFrame_RotationSkewFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_PositionFrame_class;
extern JSObject *jsb_cocostudio_timeline_PositionFrame_prototype;

bool js_cocos2dx_studio_PositionFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_PositionFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_PositionFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_PositionFrame_getX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_getY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_setPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_setX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_setY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_getPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_PositionFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ScaleFrame_class;
extern JSObject *jsb_cocostudio_timeline_ScaleFrame_prototype;

bool js_cocos2dx_studio_ScaleFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ScaleFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ScaleFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ScaleFrame_setScaleY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_setScaleX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_getScaleY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_getScaleX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_setScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_ScaleFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_AnchorPointFrame_class;
extern JSObject *jsb_cocostudio_timeline_AnchorPointFrame_prototype;

bool js_cocos2dx_studio_AnchorPointFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_AnchorPointFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_AnchorPointFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnchorPointFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnchorPointFrame_AnchorPointFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_InnerActionFrame_class;
extern JSObject *jsb_cocostudio_timeline_InnerActionFrame_prototype;

bool js_cocos2dx_studio_InnerActionFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_InnerActionFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_InnerActionFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_getInnerActionType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setEnterWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setInnerActionType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setAnimationName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_InnerActionFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ColorFrame_class;
extern JSObject *jsb_cocostudio_timeline_ColorFrame_prototype;

bool js_cocos2dx_studio_ColorFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ColorFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ColorFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ColorFrame_getColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColorFrame_setColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColorFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColorFrame_ColorFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_AlphaFrame_class;
extern JSObject *jsb_cocostudio_timeline_AlphaFrame_prototype;

bool js_cocos2dx_studio_AlphaFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_AlphaFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_AlphaFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_AlphaFrame_getAlpha(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AlphaFrame_setAlpha(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AlphaFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AlphaFrame_AlphaFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_EventFrame_class;
extern JSObject *jsb_cocostudio_timeline_EventFrame_prototype;

bool js_cocos2dx_studio_EventFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_EventFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_EventFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_EventFrame_setEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_EventFrame_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_EventFrame_getEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_EventFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_EventFrame_EventFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ZOrderFrame_class;
extern JSObject *jsb_cocostudio_timeline_ZOrderFrame_prototype;

bool js_cocos2dx_studio_ZOrderFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ZOrderFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ZOrderFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ZOrderFrame_getZOrder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ZOrderFrame_setZOrder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ZOrderFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ZOrderFrame_ZOrderFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_BlendFuncFrame_class;
extern JSObject *jsb_cocostudio_timeline_BlendFuncFrame_prototype;

bool js_cocos2dx_studio_BlendFuncFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_BlendFuncFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_BlendFuncFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_BlendFuncFrame_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BlendFuncFrame_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BlendFuncFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BlendFuncFrame_BlendFuncFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_Timeline_class;
extern JSObject *jsb_cocostudio_timeline_Timeline_prototype;

bool js_cocos2dx_studio_Timeline_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Timeline_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Timeline(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_Timeline_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_gotoFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_setNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_getActionTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_insertFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_setActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_addFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_getFrames(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_getActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_getNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_removeFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_setActionTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_stepToFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_Timeline(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ActionTimelineData_class;
extern JSObject *jsb_cocostudio_timeline_ActionTimelineData_prototype;

bool js_cocos2dx_studio_ActionTimelineData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionTimelineData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionTimelineData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ActionTimelineData_setActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimelineData_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimelineData_getActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimelineData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimelineData_ActionTimelineData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ActionTimeline_class;
extern JSObject *jsb_cocostudio_timeline_ActionTimeline_prototype;

bool js_cocos2dx_studio_ActionTimeline_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionTimeline_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionTimeline(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_addTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getStartFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_removeTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getTimelines(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_removeAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getTimeSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_addAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_isPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getEndFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setTimeSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_ActionTimeline(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_BoneNode_class;
extern JSObject *jsb_cocostudio_timeline_BoneNode_prototype;

bool js_cocos2dx_studio_BoneNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_BoneNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_BoneNode(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_BoneNode_getDebugDrawWidth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getChildBones(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getAllSubBones(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getVisibleSkinsRect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getAllSubSkins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_displaySkin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_isDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_addSkin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getRootSkeletonNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setDebugDrawLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getSkins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getVisibleSkins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setDebugDrawWidth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getDebugDrawLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setDebugDrawColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getDebugDrawColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_BoneNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_SkeletonNode_class;
extern JSObject *jsb_cocostudio_timeline_SkeletonNode_prototype;

bool js_cocos2dx_studio_SkeletonNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_SkeletonNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_SkeletonNode(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_SkeletonNode_getBoneNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_changeSkins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_addSkinGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_SkeletonNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComExtensionData_class;
extern JSObject *jsb_cocostudio_ComExtensionData_prototype;

bool js_cocos2dx_studio_ComExtensionData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComExtensionData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComExtensionData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComExtensionData_setActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_getCustomProperty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_getActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_setCustomProperty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_ComExtensionData(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_studio_h__
