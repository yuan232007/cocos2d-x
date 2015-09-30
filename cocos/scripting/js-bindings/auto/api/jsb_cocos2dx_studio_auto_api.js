/**
 * @module cocos2dx_studio
 */
var ccs = ccs || {};

/**
 * @class ActionObject
 */
ccs.ActionObject = {

/**
 * @method setCurrentTime
 * @param {float} arg0
 */
setCurrentTime : function (
float 
)
{
},

/**
 * @method pause
 */
pause : function (
)
{
},

/**
 * @method setName
 * @param {char} arg0
 */
setName : function (
char 
)
{
},

/**
 * @method setUnitTime
 * @param {float} arg0
 */
setUnitTime : function (
float 
)
{
},

/**
 * @method getTotalTime
 * @return {float}
 */
getTotalTime : function (
)
{
    return 0;
},

/**
 * @method getName
 * @return {char}
 */
getName : function (
)
{
    return 0;
},

/**
 * @method stop
 */
stop : function (
)
{
},

/**
 * @method play
* @param {cc.CallFunc} callfunc
*/
play : function(
callfunc 
)
{
},

/**
 * @method getCurrentTime
 * @return {float}
 */
getCurrentTime : function (
)
{
    return 0;
},

/**
 * @method removeActionNode
 * @param {ccs.ActionNode} arg0
 */
removeActionNode : function (
actionnode 
)
{
},

/**
 * @method getLoop
 * @return {bool}
 */
getLoop : function (
)
{
    return false;
},

/**
 * @method initWithBinary
 * @param {ccs.CocoLoader} arg0
 * @param {ccs.stExpCocoNode} arg1
 * @param {cc.Ref} arg2
 */
initWithBinary : function (
cocoloader, 
stexpcoconode, 
ref 
)
{
},

/**
 * @method addActionNode
 * @param {ccs.ActionNode} arg0
 */
addActionNode : function (
actionnode 
)
{
},

/**
 * @method getUnitTime
 * @return {float}
 */
getUnitTime : function (
)
{
    return 0;
},

/**
 * @method isPlaying
 * @return {bool}
 */
isPlaying : function (
)
{
    return false;
},

/**
 * @method updateToFrameByTime
 * @param {float} arg0
 */
updateToFrameByTime : function (
float 
)
{
},

/**
 * @method setLoop
 * @param {bool} arg0
 */
setLoop : function (
bool 
)
{
},

/**
 * @method simulationActionUpdate
 * @param {float} arg0
 */
simulationActionUpdate : function (
float 
)
{
},

/**
 * @method ActionObject
 * @constructor
 */
ActionObject : function (
)
{
},

};

/**
 * @class ActionManagerEx
 */
ccs.ActionManager = {

/**
 * @method stopActionByName
 * @param {char} arg0
 * @param {char} arg1
 * @return {ccs.ActionObject}
 */
stopActionByName : function (
char, 
char 
)
{
    return ccs.ActionObject;
},

/**
 * @method getActionByName
 * @param {char} arg0
 * @param {char} arg1
 * @return {ccs.ActionObject}
 */
getActionByName : function (
char, 
char 
)
{
    return ccs.ActionObject;
},

/**
 * @method initWithBinary
 * @param {char} arg0
 * @param {cc.Ref} arg1
 * @param {ccs.CocoLoader} arg2
 * @param {ccs.stExpCocoNode} arg3
 */
initWithBinary : function (
char, 
ref, 
cocoloader, 
stexpcoconode 
)
{
},

/**
 * @method playActionByName
* @param {char|char} char
* @param {char|char} char
* @param {cc.CallFunc} callfunc
* @return {ccs.ActionObject|ccs.ActionObject}
*/
playActionByName : function(
char,
char,
callfunc 
)
{
    return ccs.ActionObject;
},

/**
 * @method releaseActions
 */
releaseActions : function (
)
{
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {ccs.ActionManagerEx}
 */
getInstance : function (
)
{
    return ccs.ActionManagerEx;
},

};

/**
 * @class ComAttribute
 */
ccs.ComAttribute = {

/**
 * @method getFloat
 * @param {String} arg0
 * @param {float} arg1
 * @return {float}
 */
getFloat : function (
str, 
float 
)
{
    return 0;
},

/**
 * @method getBool
 * @param {String} arg0
 * @param {bool} arg1
 * @return {bool}
 */
getBool : function (
str, 
bool 
)
{
    return false;
},

/**
 * @method getString
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
getString : function (
str, 
str 
)
{
    return ;
},

/**
 * @method setFloat
 * @param {String} arg0
 * @param {float} arg1
 */
setFloat : function (
str, 
float 
)
{
},

/**
 * @method setString
 * @param {String} arg0
 * @param {String} arg1
 */
setString : function (
str, 
str 
)
{
},

/**
 * @method setInt
 * @param {String} arg0
 * @param {int} arg1
 */
setInt : function (
str, 
int 
)
{
},

/**
 * @method parse
 * @param {String} arg0
 * @return {bool}
 */
parse : function (
str 
)
{
    return false;
},

/**
 * @method getInt
 * @param {String} arg0
 * @param {int} arg1
 * @return {int}
 */
getInt : function (
str, 
int 
)
{
    return 0;
},

/**
 * @method setBool
 * @param {String} arg0
 * @param {bool} arg1
 */
setBool : function (
str, 
bool 
)
{
},

/**
 * @method create
 * @return {ccs.ComAttribute}
 */
create : function (
)
{
    return ccs.ComAttribute;
},

/**
 * @method ComAttribute
 * @constructor
 */
ComAttribute : function (
)
{
},

};

/**
 * @class ComAudio
 */
ccs.ComAudio = {

/**
 * @method stopAllEffects
 */
stopAllEffects : function (
)
{
},

/**
 * @method getEffectsVolume
 * @return {float}
 */
getEffectsVolume : function (
)
{
    return 0;
},

/**
 * @method stopEffect
 * @param {unsigned int} arg0
 */
stopEffect : function (
int 
)
{
},

/**
 * @method getBackgroundMusicVolume
 * @return {float}
 */
getBackgroundMusicVolume : function (
)
{
    return 0;
},

/**
 * @method willPlayBackgroundMusic
 * @return {bool}
 */
willPlayBackgroundMusic : function (
)
{
    return false;
},

/**
 * @method setBackgroundMusicVolume
 * @param {float} arg0
 */
setBackgroundMusicVolume : function (
float 
)
{
},

/**
 * @method end
 */
end : function (
)
{
},

/**
 * @method stopBackgroundMusic
* @param {bool} bool
*/
stopBackgroundMusic : function(
bool 
)
{
},

/**
 * @method pauseBackgroundMusic
 */
pauseBackgroundMusic : function (
)
{
},

/**
 * @method isBackgroundMusicPlaying
 * @return {bool}
 */
isBackgroundMusicPlaying : function (
)
{
    return false;
},

/**
 * @method isLoop
 * @return {bool}
 */
isLoop : function (
)
{
    return false;
},

/**
 * @method resumeAllEffects
 */
resumeAllEffects : function (
)
{
},

/**
 * @method pauseAllEffects
 */
pauseAllEffects : function (
)
{
},

/**
 * @method preloadBackgroundMusic
 * @param {char} arg0
 */
preloadBackgroundMusic : function (
char 
)
{
},

/**
 * @method playBackgroundMusic
* @param {char|char} char
* @param {bool} bool
*/
playBackgroundMusic : function(
char,
bool 
)
{
},

/**
 * @method playEffect
* @param {char|char} char
* @param {bool} bool
* @return {unsigned int|unsigned int|unsigned int}
*/
playEffect : function(
char,
bool 
)
{
    return 0;
},

/**
 * @method preloadEffect
 * @param {char} arg0
 */
preloadEffect : function (
char 
)
{
},

/**
 * @method setLoop
 * @param {bool} arg0
 */
setLoop : function (
bool 
)
{
},

/**
 * @method unloadEffect
 * @param {char} arg0
 */
unloadEffect : function (
char 
)
{
},

/**
 * @method rewindBackgroundMusic
 */
rewindBackgroundMusic : function (
)
{
},

/**
 * @method pauseEffect
 * @param {unsigned int} arg0
 */
pauseEffect : function (
int 
)
{
},

/**
 * @method resumeBackgroundMusic
 */
resumeBackgroundMusic : function (
)
{
},

/**
 * @method setFile
 * @param {char} arg0
 */
setFile : function (
char 
)
{
},

/**
 * @method setEffectsVolume
 * @param {float} arg0
 */
setEffectsVolume : function (
float 
)
{
},

/**
 * @method getFile
 * @return {char}
 */
getFile : function (
)
{
    return 0;
},

/**
 * @method resumeEffect
 * @param {unsigned int} arg0
 */
resumeEffect : function (
int 
)
{
},

/**
 * @method create
 * @return {ccs.ComAudio}
 */
create : function (
)
{
    return ccs.ComAudio;
},

/**
 * @method ComAudio
 * @constructor
 */
ComAudio : function (
)
{
},

};

/**
 * @class InputDelegate
 */
ccs.InputDelegate = {

/**
 * @method isAccelerometerEnabled
 * @return {bool}
 */
isAccelerometerEnabled : function (
)
{
    return false;
},

/**
 * @method setKeypadEnabled
 * @param {bool} arg0
 */
setKeypadEnabled : function (
bool 
)
{
},

/**
 * @method getTouchMode
 * @return {cc.Touch::DispatchMode}
 */
getTouchMode : function (
)
{
    return 0;
},

/**
 * @method setAccelerometerEnabled
 * @param {bool} arg0
 */
setAccelerometerEnabled : function (
bool 
)
{
},

/**
 * @method isKeypadEnabled
 * @return {bool}
 */
isKeypadEnabled : function (
)
{
    return false;
},

/**
 * @method isTouchEnabled
 * @return {bool}
 */
isTouchEnabled : function (
)
{
    return false;
},

/**
 * @method setTouchPriority
 * @param {int} arg0
 */
setTouchPriority : function (
int 
)
{
},

/**
 * @method getTouchPriority
 * @return {int}
 */
getTouchPriority : function (
)
{
    return 0;
},

/**
 * @method setTouchEnabled
 * @param {bool} arg0
 */
setTouchEnabled : function (
bool 
)
{
},

/**
 * @method setTouchMode
 * @param {cc.Touch::DispatchMode} arg0
 */
setTouchMode : function (
dispatchmode 
)
{
},

};

/**
 * @class ComController
 */
ccs.ComController = {

/**
 * @method create
 * @return {ccs.ComController}
 */
create : function (
)
{
    return ccs.ComController;
},

/**
 * @method ComController
 * @constructor
 */
ComController : function (
)
{
},

};

/**
 * @class ComRender
 */
ccs.ComRender = {

/**
 * @method setNode
 * @param {cc.Node} arg0
 */
setNode : function (
node 
)
{
},

/**
 * @method getNode
 * @return {cc.Node}
 */
getNode : function (
)
{
    return cc.Node;
},

/**
 * @method create
* @param {cc.Node} node
* @param {char} char
* @return {ccs.ComRender|ccs.ComRender}
*/
create : function(
node,
char 
)
{
    return ccs.ComRender;
},

/**
 * @method ComRender
 * @constructor
* @param {cc.Node} node
* @param {char} char
*/
ComRender : function(
node,
char 
)
{
},

};

/**
 * @class Frame
 */
ccs.Frame = {

/**
 * @method clone
 * @return {ccs.timeline::Frame}
 */
clone : function (
)
{
    return ccs.timeline::Frame;
},

/**
 * @method setTweenType
 * @param {cc.tweenfunc::TweenType} arg0
 */
setTweenType : function (
tweentype 
)
{
},

/**
 * @method setNode
 * @param {cc.Node} arg0
 */
setNode : function (
node 
)
{
},

/**
 * @method setTimeline
 * @param {ccs.timeline::Timeline} arg0
 */
setTimeline : function (
timeline 
)
{
},

/**
 * @method isEnterWhenPassed
 * @return {bool}
 */
isEnterWhenPassed : function (
)
{
    return false;
},

/**
 * @method getTweenType
 * @return {cc.tweenfunc::TweenType}
 */
getTweenType : function (
)
{
    return 0;
},

/**
 * @method getFrameIndex
 * @return {unsigned int}
 */
getFrameIndex : function (
)
{
    return 0;
},

/**
 * @method apply
 * @param {float} arg0
 */
apply : function (
float 
)
{
},

/**
 * @method isTween
 * @return {bool}
 */
isTween : function (
)
{
    return false;
},

/**
 * @method setFrameIndex
 * @param {unsigned int} arg0
 */
setFrameIndex : function (
int 
)
{
},

/**
 * @method setTween
 * @param {bool} arg0
 */
setTween : function (
bool 
)
{
},

/**
 * @method getTimeline
 * @return {ccs.timeline::Timeline}
 */
getTimeline : function (
)
{
    return ccs.timeline::Timeline;
},

/**
 * @method getNode
 * @return {cc.Node}
 */
getNode : function (
)
{
    return cc.Node;
},

};

/**
 * @class VisibleFrame
 */
ccs.VisibleFrame = {

/**
 * @method isVisible
 * @return {bool}
 */
isVisible : function (
)
{
    return false;
},

/**
 * @method setVisible
 * @param {bool} arg0
 */
setVisible : function (
bool 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::VisibleFrame}
 */
create : function (
)
{
    return ccs.timeline::VisibleFrame;
},

/**
 * @method VisibleFrame
 * @constructor
 */
VisibleFrame : function (
)
{
},

};

/**
 * @class TextureFrame
 */
ccs.TextureFrame = {

/**
 * @method getTextureName
 * @return {String}
 */
getTextureName : function (
)
{
    return ;
},

/**
 * @method setTextureName
 * @param {String} arg0
 */
setTextureName : function (
str 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::TextureFrame}
 */
create : function (
)
{
    return ccs.timeline::TextureFrame;
},

/**
 * @method TextureFrame
 * @constructor
 */
TextureFrame : function (
)
{
},

};

/**
 * @class RotationFrame
 */
ccs.RotationFrame = {

/**
 * @method setRotation
 * @param {float} arg0
 */
setRotation : function (
float 
)
{
},

/**
 * @method getRotation
 * @return {float}
 */
getRotation : function (
)
{
    return 0;
},

/**
 * @method create
 * @return {ccs.timeline::RotationFrame}
 */
create : function (
)
{
    return ccs.timeline::RotationFrame;
},

/**
 * @method RotationFrame
 * @constructor
 */
RotationFrame : function (
)
{
},

};

/**
 * @class SkewFrame
 */
ccs.SkewFrame = {

/**
 * @method getSkewY
 * @return {float}
 */
getSkewY : function (
)
{
    return 0;
},

/**
 * @method setSkewX
 * @param {float} arg0
 */
setSkewX : function (
float 
)
{
},

/**
 * @method setSkewY
 * @param {float} arg0
 */
setSkewY : function (
float 
)
{
},

/**
 * @method getSkewX
 * @return {float}
 */
getSkewX : function (
)
{
    return 0;
},

/**
 * @method create
 * @return {ccs.timeline::SkewFrame}
 */
create : function (
)
{
    return ccs.timeline::SkewFrame;
},

/**
 * @method SkewFrame
 * @constructor
 */
SkewFrame : function (
)
{
},

};

/**
 * @class RotationSkewFrame
 */
ccs.RotationSkewFrame = {

/**
 * @method create
 * @return {ccs.timeline::RotationSkewFrame}
 */
create : function (
)
{
    return ccs.timeline::RotationSkewFrame;
},

/**
 * @method RotationSkewFrame
 * @constructor
 */
RotationSkewFrame : function (
)
{
},

};

/**
 * @class PositionFrame
 */
ccs.PositionFrame = {

/**
 * @method getX
 * @return {float}
 */
getX : function (
)
{
    return 0;
},

/**
 * @method getY
 * @return {float}
 */
getY : function (
)
{
    return 0;
},

/**
 * @method setPosition
 * @param {vec2_object} arg0
 */
setPosition : function (
vec2 
)
{
},

/**
 * @method setX
 * @param {float} arg0
 */
setX : function (
float 
)
{
},

/**
 * @method setY
 * @param {float} arg0
 */
setY : function (
float 
)
{
},

/**
 * @method getPosition
 * @return {vec2_object}
 */
getPosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method create
 * @return {ccs.timeline::PositionFrame}
 */
create : function (
)
{
    return ccs.timeline::PositionFrame;
},

/**
 * @method PositionFrame
 * @constructor
 */
PositionFrame : function (
)
{
},

};

/**
 * @class ScaleFrame
 */
ccs.ScaleFrame = {

/**
 * @method setScaleY
 * @param {float} arg0
 */
setScaleY : function (
float 
)
{
},

/**
 * @method setScaleX
 * @param {float} arg0
 */
setScaleX : function (
float 
)
{
},

/**
 * @method getScaleY
 * @return {float}
 */
getScaleY : function (
)
{
    return 0;
},

/**
 * @method getScaleX
 * @return {float}
 */
getScaleX : function (
)
{
    return 0;
},

/**
 * @method setScale
 * @param {float} arg0
 */
setScale : function (
float 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::ScaleFrame}
 */
create : function (
)
{
    return ccs.timeline::ScaleFrame;
},

/**
 * @method ScaleFrame
 * @constructor
 */
ScaleFrame : function (
)
{
},

};

/**
 * @class AnchorPointFrame
 */
ccs.AnchorPointFrame = {

/**
 * @method setAnchorPoint
 * @param {vec2_object} arg0
 */
setAnchorPoint : function (
vec2 
)
{
},

/**
 * @method getAnchorPoint
 * @return {vec2_object}
 */
getAnchorPoint : function (
)
{
    return cc.Vec2;
},

/**
 * @method create
 * @return {ccs.timeline::AnchorPointFrame}
 */
create : function (
)
{
    return ccs.timeline::AnchorPointFrame;
},

/**
 * @method AnchorPointFrame
 * @constructor
 */
AnchorPointFrame : function (
)
{
},

};

/**
 * @class InnerActionFrame
 */
ccs.InnerActionFrame = {

/**
 * @method getEndFrameIndex
 * @return {int}
 */
getEndFrameIndex : function (
)
{
    return 0;
},

/**
 * @method getStartFrameIndex
 * @return {int}
 */
getStartFrameIndex : function (
)
{
    return 0;
},

/**
 * @method getInnerActionType
 * @return {ccs.timeline::InnerActionType}
 */
getInnerActionType : function (
)
{
    return 0;
},

/**
 * @method setEndFrameIndex
 * @param {int} arg0
 */
setEndFrameIndex : function (
int 
)
{
},

/**
 * @method setEnterWithName
 * @param {bool} arg0
 */
setEnterWithName : function (
bool 
)
{
},

/**
 * @method setSingleFrameIndex
 * @param {int} arg0
 */
setSingleFrameIndex : function (
int 
)
{
},

/**
 * @method setStartFrameIndex
 * @param {int} arg0
 */
setStartFrameIndex : function (
int 
)
{
},

/**
 * @method getSingleFrameIndex
 * @return {int}
 */
getSingleFrameIndex : function (
)
{
    return 0;
},

/**
 * @method setInnerActionType
 * @param {ccs.timeline::InnerActionType} arg0
 */
setInnerActionType : function (
inneractiontype 
)
{
},

/**
 * @method setAnimationName
 * @param {String} arg0
 */
setAnimationName : function (
str 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::InnerActionFrame}
 */
create : function (
)
{
    return ccs.timeline::InnerActionFrame;
},

/**
 * @method InnerActionFrame
 * @constructor
 */
InnerActionFrame : function (
)
{
},

};

/**
 * @class ColorFrame
 */
ccs.ColorFrame = {

/**
 * @method getColor
 * @return {color3b_object}
 */
getColor : function (
)
{
    return cc.Color3B;
},

/**
 * @method setColor
 * @param {color3b_object} arg0
 */
setColor : function (
color3b 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::ColorFrame}
 */
create : function (
)
{
    return ccs.timeline::ColorFrame;
},

/**
 * @method ColorFrame
 * @constructor
 */
ColorFrame : function (
)
{
},

};

/**
 * @class AlphaFrame
 */
ccs.AlphaFrame = {

/**
 * @method getAlpha
 * @return {unsigned char}
 */
getAlpha : function (
)
{
    return 0;
},

/**
 * @method setAlpha
 * @param {unsigned char} arg0
 */
setAlpha : function (
char 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::AlphaFrame}
 */
create : function (
)
{
    return ccs.timeline::AlphaFrame;
},

/**
 * @method AlphaFrame
 * @constructor
 */
AlphaFrame : function (
)
{
},

};

/**
 * @class EventFrame
 */
ccs.EventFrame = {

/**
 * @method setEvent
 * @param {String} arg0
 */
setEvent : function (
str 
)
{
},

/**
 * @method init
 */
init : function (
)
{
},

/**
 * @method getEvent
 * @return {String}
 */
getEvent : function (
)
{
    return ;
},

/**
 * @method create
 * @return {ccs.timeline::EventFrame}
 */
create : function (
)
{
    return ccs.timeline::EventFrame;
},

/**
 * @method EventFrame
 * @constructor
 */
EventFrame : function (
)
{
},

};

/**
 * @class ZOrderFrame
 */
ccs.ZOrderFrame = {

/**
 * @method getZOrder
 * @return {int}
 */
getZOrder : function (
)
{
    return 0;
},

/**
 * @method setZOrder
 * @param {int} arg0
 */
setZOrder : function (
int 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::ZOrderFrame}
 */
create : function (
)
{
    return ccs.timeline::ZOrderFrame;
},

/**
 * @method ZOrderFrame
 * @constructor
 */
ZOrderFrame : function (
)
{
},

};

/**
 * @class BlendFuncFrame
 */
ccs.BlendFuncFrame = {

/**
 * @method getBlendFunc
 * @return {cc.BlendFunc}
 */
getBlendFunc : function (
)
{
    return cc.BlendFunc;
},

/**
 * @method setBlendFunc
 * @param {cc.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::BlendFuncFrame}
 */
create : function (
)
{
    return ccs.timeline::BlendFuncFrame;
},

/**
 * @method BlendFuncFrame
 * @constructor
 */
BlendFuncFrame : function (
)
{
},

};

/**
 * @class Timeline
 */
ccs.Timeline = {

/**
 * @method clone
 * @return {ccs.timeline::Timeline}
 */
clone : function (
)
{
    return ccs.timeline::Timeline;
},

/**
 * @method gotoFrame
 * @param {int} arg0
 */
gotoFrame : function (
int 
)
{
},

/**
 * @method setNode
 * @param {cc.Node} arg0
 */
setNode : function (
node 
)
{
},

/**
 * @method getActionTimeline
 * @return {ccs.timeline::ActionTimeline}
 */
getActionTimeline : function (
)
{
    return ccs.timeline::ActionTimeline;
},

/**
 * @method insertFrame
 * @param {ccs.timeline::Frame} arg0
 * @param {int} arg1
 */
insertFrame : function (
frame, 
int 
)
{
},

/**
 * @method setActionTag
 * @param {int} arg0
 */
setActionTag : function (
int 
)
{
},

/**
 * @method addFrame
 * @param {ccs.timeline::Frame} arg0
 */
addFrame : function (
frame 
)
{
},

/**
 * @method getFrames
 * @return {Array}
 */
getFrames : function (
)
{
    return new Array();
},

/**
 * @method getActionTag
 * @return {int}
 */
getActionTag : function (
)
{
    return 0;
},

/**
 * @method getNode
 * @return {cc.Node}
 */
getNode : function (
)
{
    return cc.Node;
},

/**
 * @method removeFrame
 * @param {ccs.timeline::Frame} arg0
 */
removeFrame : function (
frame 
)
{
},

/**
 * @method setActionTimeline
 * @param {ccs.timeline::ActionTimeline} arg0
 */
setActionTimeline : function (
actiontimeline 
)
{
},

/**
 * @method stepToFrame
 * @param {int} arg0
 */
stepToFrame : function (
int 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::Timeline}
 */
create : function (
)
{
    return ccs.timeline::Timeline;
},

/**
 * @method Timeline
 * @constructor
 */
Timeline : function (
)
{
},

};

/**
 * @class ActionTimelineData
 */
ccs.ActionTimelineData = {

/**
 * @method setActionTag
 * @param {int} arg0
 */
setActionTag : function (
int 
)
{
},

/**
 * @method init
 * @param {int} arg0
 * @return {bool}
 */
init : function (
int 
)
{
    return false;
},

/**
 * @method getActionTag
 * @return {int}
 */
getActionTag : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {int} arg0
 * @return {ccs.timeline::ActionTimelineData}
 */
create : function (
int 
)
{
    return ccs.timeline::ActionTimelineData;
},

/**
 * @method ActionTimelineData
 * @constructor
 */
ActionTimelineData : function (
)
{
},

};

/**
 * @class ActionTimeline
 */
ccs.ActionTimeline = {

/**
 * @method setFrameEventCallFunc
 * @param {function} arg0
 */
setFrameEventCallFunc : function (
func 
)
{
},

/**
 * @method clearFrameEndCallFuncs
 */
clearFrameEndCallFuncs : function (
)
{
},

/**
 * @method setAnimationEndCallFunc
 * @param {String} arg0
 * @param {function} arg1
 */
setAnimationEndCallFunc : function (
str, 
func 
)
{
},

/**
 * @method addTimeline
 * @param {ccs.timeline::Timeline} arg0
 */
addTimeline : function (
timeline 
)
{
},

/**
 * @method getCurrentFrame
 * @return {int}
 */
getCurrentFrame : function (
)
{
    return 0;
},

/**
 * @method getStartFrame
 * @return {int}
 */
getStartFrame : function (
)
{
    return 0;
},

/**
 * @method pause
 */
pause : function (
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method removeTimeline
 * @param {ccs.timeline::Timeline} arg0
 */
removeTimeline : function (
timeline 
)
{
},

/**
 * @method setLastFrameCallFunc
 * @param {function} arg0
 */
setLastFrameCallFunc : function (
func 
)
{
},

/**
 * @method IsAnimationInfoExists
 * @param {String} arg0
 * @return {bool}
 */
IsAnimationInfoExists : function (
str 
)
{
    return false;
},

/**
 * @method getTimelines
 * @return {Array}
 */
getTimelines : function (
)
{
    return new Array();
},

/**
 * @method play
 * @param {String} arg0
 * @param {bool} arg1
 */
play : function (
str, 
bool 
)
{
},

/**
 * @method getAnimationInfo
 * @param {String} arg0
 * @return {ccs.timeline::AnimationInfo}
 */
getAnimationInfo : function (
str 
)
{
    return ccs.timeline::AnimationInfo;
},

/**
 * @method resume
 */
resume : function (
)
{
},

/**
 * @method addFrameEndCallFunc
 * @param {int} arg0
 * @param {String} arg1
 * @param {function} arg2
 */
addFrameEndCallFunc : function (
int, 
str, 
func 
)
{
},

/**
 * @method removeAnimationInfo
 * @param {String} arg0
 */
removeAnimationInfo : function (
str 
)
{
},

/**
 * @method getTimeSpeed
 * @return {float}
 */
getTimeSpeed : function (
)
{
    return 0;
},

/**
 * @method addAnimationInfo
 * @param {ccs.timeline::AnimationInfo} arg0
 */
addAnimationInfo : function (
animationinfo 
)
{
},

/**
 * @method getDuration
 * @return {int}
 */
getDuration : function (
)
{
    return 0;
},

/**
 * @method gotoFrameAndPause
 * @param {int} arg0
 */
gotoFrameAndPause : function (
int 
)
{
},

/**
 * @method isPlaying
 * @return {bool}
 */
isPlaying : function (
)
{
    return false;
},

/**
 * @method removeFrameEndCallFuncs
 * @param {int} arg0
 */
removeFrameEndCallFuncs : function (
int 
)
{
},

/**
 * @method gotoFrameAndPlay
* @param {int|int|int|int} int
* @param {bool|int|int} bool
* @param {bool|int} bool
* @param {bool} bool
*/
gotoFrameAndPlay : function(
int,
int,
int,
bool 
)
{
},

/**
 * @method clearFrameEventCallFunc
 */
clearFrameEventCallFunc : function (
)
{
},

/**
 * @method getEndFrame
 * @return {int}
 */
getEndFrame : function (
)
{
    return 0;
},

/**
 * @method setTimeSpeed
 * @param {float} arg0
 */
setTimeSpeed : function (
float 
)
{
},

/**
 * @method clearLastFrameCallFunc
 */
clearLastFrameCallFunc : function (
)
{
},

/**
 * @method setDuration
 * @param {int} arg0
 */
setDuration : function (
int 
)
{
},

/**
 * @method setCurrentFrame
 * @param {int} arg0
 */
setCurrentFrame : function (
int 
)
{
},

/**
 * @method removeFrameEndCallFunc
 * @param {int} arg0
 * @param {String} arg1
 */
removeFrameEndCallFunc : function (
int, 
str 
)
{
},

/**
 * @method create
 * @return {ccs.timeline::ActionTimeline}
 */
create : function (
)
{
    return ccs.timeline::ActionTimeline;
},

/**
 * @method ActionTimeline
 * @constructor
 */
ActionTimeline : function (
)
{
},

};

/**
 * @class BoneNode
 */
ccs.BoneNode = {

/**
 * @method getDebugDrawWidth
 * @return {float}
 */
getDebugDrawWidth : function (
)
{
    return 0;
},

/**
 * @method getChildBones
* @return {Array|Array}
*/
getChildBones : function(
)
{
    return new Array();
},

/**
 * @method getBlendFunc
 * @return {cc.BlendFunc}
 */
getBlendFunc : function (
)
{
    return cc.BlendFunc;
},

/**
 * @method getAllSubBones
 * @return {Array}
 */
getAllSubBones : function (
)
{
    return new Array();
},

/**
 * @method setBlendFunc
 * @param {cc.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method setDebugDrawEnabled
 * @param {bool} arg0
 */
setDebugDrawEnabled : function (
bool 
)
{
},

/**
 * @method getVisibleSkinsRect
 * @return {rect_object}
 */
getVisibleSkinsRect : function (
)
{
    return cc.Rect;
},

/**
 * @method getAllSubSkins
 * @return {Array}
 */
getAllSubSkins : function (
)
{
    return new Array();
},

/**
 * @method displaySkin
* @param {String|cc.Node} str
* @param {bool|bool} bool
*/
displaySkin : function(
node,
bool 
)
{
},

/**
 * @method isDebugDrawEnabled
 * @return {bool}
 */
isDebugDrawEnabled : function (
)
{
    return false;
},

/**
 * @method addSkin
* @param {cc.Node|cc.Node} node
* @param {bool|bool} bool
* @param {bool} bool
*/
addSkin : function(
node,
bool,
bool 
)
{
},

/**
 * @method getRootSkeletonNode
 * @return {ccs.timeline::SkeletonNode}
 */
getRootSkeletonNode : function (
)
{
    return ccs.timeline::SkeletonNode;
},

/**
 * @method setDebugDrawLength
 * @param {float} arg0
 */
setDebugDrawLength : function (
float 
)
{
},

/**
 * @method getSkins
* @return {Array|Array}
*/
getSkins : function(
)
{
    return new Array();
},

/**
 * @method getVisibleSkins
 * @return {Array}
 */
getVisibleSkins : function (
)
{
    return new Array();
},

/**
 * @method setDebugDrawWidth
 * @param {float} arg0
 */
setDebugDrawWidth : function (
float 
)
{
},

/**
 * @method getDebugDrawLength
 * @return {float}
 */
getDebugDrawLength : function (
)
{
    return 0;
},

/**
 * @method setDebugDrawColor
 * @param {color4f_object} arg0
 */
setDebugDrawColor : function (
color4f 
)
{
},

/**
 * @method getDebugDrawColor
 * @return {color4f_object}
 */
getDebugDrawColor : function (
)
{
    return cc.Color4F;
},

/**
 * @method create
* @param {int} int
* @return {ccs.timeline::BoneNode|ccs.timeline::BoneNode}
*/
create : function(
int 
)
{
    return ccs.timeline::BoneNode;
},

/**
 * @method BoneNode
 * @constructor
 */
BoneNode : function (
)
{
},

};

/**
 * @class SkeletonNode
 */
ccs.SkeletonNode = {

/**
 * @method getBoneNode
 * @param {String} arg0
 * @return {ccs.timeline::BoneNode}
 */
getBoneNode : function (
str 
)
{
    return ccs.timeline::BoneNode;
},

/**
 * @method changeSkins
* @param {String|map_object} str
*/
changeSkins : function(
map 
)
{
},

/**
 * @method addSkinGroup
 * @param {String} arg0
 * @param {map_object} arg1
 */
addSkinGroup : function (
str, 
map 
)
{
},

/**
 * @method getAllSubBonesMap
 * @return {map_object}
 */
getAllSubBonesMap : function (
)
{
    return map_object;
},

/**
 * @method create
 * @return {ccs.timeline::SkeletonNode}
 */
create : function (
)
{
    return ccs.timeline::SkeletonNode;
},

/**
 * @method SkeletonNode
 * @constructor
 */
SkeletonNode : function (
)
{
},

};

/**
 * @class ComExtensionData
 */
ccs.ComExtensionData = {

/**
 * @method setActionTag
 * @param {int} arg0
 */
setActionTag : function (
int 
)
{
},

/**
 * @method getCustomProperty
 * @return {String}
 */
getCustomProperty : function (
)
{
    return ;
},

/**
 * @method getActionTag
 * @return {int}
 */
getActionTag : function (
)
{
    return 0;
},

/**
 * @method setCustomProperty
 * @param {String} arg0
 */
setCustomProperty : function (
str 
)
{
},

/**
 * @method create
 * @return {ccs.ComExtensionData}
 */
create : function (
)
{
    return ccs.ComExtensionData;
},

/**
 * @method ComExtensionData
 * @constructor
 */
ComExtensionData : function (
)
{
},

};
