#import <Foundation/Foundation.h>

/**
 * 这个文件的接口都不能改，name也不能改
 *
 */

#ifndef MTT_GAME_ENGINE_DELEGATE_H
#define MTT_GAME_ENGINE_DELEGATE_H

/**
 * 浮动按钮展开收到的消息
 * 调用gameengine_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_HOVER_MENU_SHOW
 * }
 */
#define MSG_ON_HOVER_MENU_SHOW @"hover_menu_show"

/**
 * app切入后台的消息（仅针对H5游戏）
 */
#define MSG_ON_APP_ENTER_BACKGROUND @"app_enter_background"

/**
 * app切入前台的消息（仅针对H5游戏）
 */
#define MSG_ON_APP_ENTER_FOREGROUND @"app_enter_foreground"

/**
 * 浮动按钮收回收到的消息
 * 调用gameengine_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_HOVER_MENU_HIDE
 * }
 */
#define MSG_ON_HOVER_MENU_HIDE @"hover_menu_hide"

/**
 * 网络异常的情况下，重新加载游戏的消息
 * 调用gameengine_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_RELOAD_GAME
 * }
 */
#define MSG_ON_RELOAD_GAME @"reload_game"
#endif


@protocol MttGameEngineDelegate <NSObject>

@optional
/**
 * 获取x5GamePlayer侧key所对应的的值
 *
 * @param key
 * @return
 */
- (id)x5GamePlayer_get_value:(NSString*)key;

/**
 * 设置x5GamePlayer侧key所对应的的值
 *
 * @param key
 * @param value
 * @return
 */
- (BOOL)x5GamePlayer_set_value:(NSString*)key value:(id)value;

/**
 * 游戏引擎请求终止游戏
 */
- (void)x5GamePlayer_stop_game_engine;

/**
 * 调用某个方法
 *
 * @param method 方法名
 * @param bundle 存有方法所用的参数
 * @return
 */
- (id)x5GamePlayer_invoke_Method:(NSString*)method bundle:(NSDictionary*)bundle;

//游戏引擎通过这个接口发送消息给x5GamePlayer
- (void)x5GamePlayer_send_msg:(NSDictionary*)jsonObj;

/**
 * 续期token
 * JSONObject 包含如下数据{"appid": "", "qbopenid" : "", "refreshToken", ""}，调用结束后
 * 通过callback通知runtime，callback中的JSONObject包含如下数据：
 * {
 * "result":, //result为0说明函数执行成功，否则失败
 * "msg": "", //传回的提示信息
 * "qbopenid": "",
 * "qbopenkey":""
 * }
 **/
- (void)x5GamePlayer_refresh_token:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 * 授权
 * JSONObject 包含如下数据
 * {
 * "appid": "",
 * "appsig" : "",
 * "appsigData", ""
 * "logintype", "" // "wx" or "qq"
 * }，调用结束后
 * 通过callback通知runtime，callback中的JSONObject包含如下数据：
 * {
 * "result":, //result为0说明函数执行成功，否则失败
 * "msg": "", //传回的提示信息
 * "qbopenid": "",
 * "qbopenkey":"",
 * "refreshToken":"",
 * "nickName":"",
 * "avatarUrl":""
 * }
 */
- (void)x5GamePlayer_login:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 * 注销登录
 * JSONObject 包含如下数据
 {
 　　"appid": "",
 　　"qbopenid" : "",
 　　"loginType" : "" //之前登录的类型，"wx"为微信登陆，"qq"为手Q登陆，"all"为所有类型登录
 }，调用结束后
 * 通过callback通知runtime，callback中的JSONObject包含如下数据：
 * {
 　　"result":, //result为0说明函数执行成功，负责失败，
 "msg": "", //传回的提示信息
 
 }
 */
- (void)x5GamePlayer_logout:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 * 获取同玩好友的信息
 * JSONObject 包含如下数据{"appid": "", "appsig" : "", "qbopenid" "", "qbopenkey"
 * : ""}，调用结束后
 * 通过callback通知runtime，callback中的JSONObject包含如下数据：
 * {
 * "result":, //result为0说明函数执行成功，否则失败
 * "msg": "", //传回的提示信息
 * "friends": [] //数组中传回同玩好友的qbopenid
 * }
 */

/***
 * 参数jsonObj目前没有用，可以传null
 * 调用结束后通过callback通知runtime。Callback中的JSONObject包含如下数据:
 * "result":, //result为0说明函数执行成功，否则失败
 * "msg": "", //传回的提示信息
 */
- (void)x5GamePlayer_get_game_friends:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 * 支付
 * JSONObject 包含如下数据，
 * {
 * "appid":"",
 * "appsig":"",
 * "qbopenid":"",
 * "qbopenkey":"",
 * "payItem" : "",
 * //购买明细,应用可以自己控制批价格式的定义，比如可为xxx*1;yyy*2,表示xxx一件和yyy两件。长度小于512字符。
 * "payInfo" : "", //购买描述,应用可以自己控制批价格式的定义，比如可为name*desc。长度小于255字符，utf8编码
 * "reqTime" : "", //请求发生的时间
 * "customMeta", "", //透传参数
 * }
 * 调用结束后通过callback通知runtime,Callback中的JSONObject包含如下数据：
 * {
 * "result":, //result为0说明函数执行成功，否则失败
 * "msg": "", //传回的提示信息
 * "realSaveNum": //实际支付的数目
 * }
 ***/
- (void)x5GamePlayer_pay:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 * 分享
 * JSONObject 包含如下数据:
 * {
 * "url":'', //分享后点击的页面url
 * "title":'',//分享界面的标题
 * "description":'',//分享界面的描述
 * "img_url":'',//分享内容插图url
 * "img_title":'',//分享内容插图的标题
 * "cus_txt":'',//本地sharewindow编辑框中默认填写的内容
 * }
 * 调用结束后通过callback通知runtime。Callback中的JSONObject包含如下数据:
 * {
 * "result": , //result为0说明分享成功,-1就是分享取消
 * "app": , //分享到哪个app
 * UNKNOWN = -1; // 未知
 * WECHAT = 1; // 微信
 * QZONE = 3; // qq空间
 * QQ = 4; // qq好友
 * TIMELINE = 8; // 朋友圈
 * }
 ***/
- (void)x5GamePlayer_share:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 * 获取用户信息
 * JSONObject 包含如下数据:
 * {
 * "appid":'',
 * "qbopenid":'',
 * "qbopenkey":''
 * }
 * 调用结束后通过callback通知runtime。Callback中的JSONObject包含如下数据:
 * {
 * "result": , //result为0说明分享成功,-1就是分享取消
 * "msg": , //传回的提示信息
 * "nickName": , //昵称
 * "avatarUrl": , //头像
 * "sex": , //性别, 0未知，1男，2女
 * "city": , //城市
 * "language": , //语言
 * "isVip": , //是否vip, 1是，0不是
 * "province": , //省份
 * "country": , //国家
 * }
 ***/
- (void)x5GamePlayer_getUserInfo:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 * 获取可用登录类型
 * JSONObject 包含如下数据:
 * {
 * "appid":'',
 * }
 * 调用结束后通过callback通知runtime。Callback中的JSONObject包含如下数据:
 * {
 * "result": , //result为0说明分享成功,-1就是分享取消
 * "msg": , //传回的提示信息
 * "loginTypes"://可用登录类型数组[]
 *   "loginType": //类型，"wx"、"qq"或者"guest",
 *   "accInfo": //如果不为空，标识本地已有该类型的身份信息，游戏可以跳过登陆界面直接调用login接口
 *     "nickName": //昵称
 *     "avatarUrl": //头像
 * }
 ***/
- (void)x5GamePlayer_getAvailableLoginType:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 发送桌面
 JSONObject 包含如下数据
 {
 　　"ext", "", //传个runtime的其他参数
 }，
 调用结束后通过callback通知runtime，callback中的JSONObject包含如下数据：
 {
 "result":, //result为0说明函数执行成功，否则失败
 "msg": "", //传回的提示信息
 }
 **/
- (void)x5GamePlayer_send_to_desktop:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

/**
 * 打开话题圈
 * JSONObject 包含如下数据:
 * {
 * "appid":"",
 * }
 * 调用结束后通过callback通知runtime。Callback中的JSONObject包含如下数据:
 * {
 * "result": , //result为0说明打开成功,-1就是打开失败或者取消
 * }
 ***/
- (void)x5GamePlayer_open_topicCircle:(NSDictionary*)jsonObj callback:(void (^)(NSDictionary* dict))callback;

@end