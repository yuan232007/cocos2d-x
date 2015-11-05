#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MttGameEngineDelegate.h"

#ifndef MTT_GAME_ENGINE_PROTOCOL_H
#define MTT_GAME_ENGINE_PROTOCOL_H
/**
 * 这个文件的接口都不能改，name也不能改
 *
 */

/**
 * 游戏开始加载的时候发的消息
 * 调用x5GamePlayer_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_LOAD_GAME_START
 * }
 */
#define MSG_ON_LOAD_GAME_START @"ge_load_game_start"

/**
 * 游戏加载结束的时候发的消息
 * 调用x5GamePlayer_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_LOAD_GAME_END
 * }
 */
#define MSG_ON_LOAD_GAME_END @"ge_load_game_end"

/**
 * 游戏加载过程中发的消息
 * 调用x5GamePlayer_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_GAME_LOADING_PROGRESS,
 * "progress" : 下载的进度的百分比, String类型
 * "size" : ? 资源文件的总大小， String类型
 * }
 */
#define MSG_ON_GAME_LOADING_PROGRESS @"ge_loading_progress"

/**
 * 网络出错,收到这个消息是,x5会弹出是否重新加载的对话框
 * 调用x5GamePlayer_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_NETWORK_ERR
 * }
 */
#define MSG_ON_NETWORK_ERR @"ge_network_err"

/**
 * 存储空间满，收到这个消息是,x5会弹框，提示用户
 * 调用x5GamePlayer_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_STORAGE_FULL
 * }
 */
#define MSG_ON_STORAGE_FULL @"ge_storage_full"

/**
 * runtime校验失败
 * 用过可能会修改runtime文件，导致校验失败。
 * 调用x5GamePlayer_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_RUNTIME_CHECK_FAIL
 * }
 */
#define MSG_ON_RUNTIME_CHECK_FAIL @"ge_runtime_check_fail"

/**
 * 游戏资源校验失败
 * 下载游戏资源是出现问题，runtime这时会重新下在游戏资源
 * 调用x5GamePlayer_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_GAME_RES_CHECK_FAIL
 * }
 */
#define MSG_ON_GAME_RES_CHECK_FAIL @"ge_game_res_check_fail"

/**
 * 需要更新runtime
 * 可能出现游戏需要特定版本的runtime, runtime通过这个消息去通知浏览器更新最新的runtime
 * 调用x5GamePlayer_send_msg(JSONObject jsonObj), JSONObject包括如下信息
 * {
 * "type" : MSG_ON_NEED_UPDATE_GE
 * }
 */
#define MSG_ON_NEED_UPDATE_GE @"ge_game_need_update_runtime"
#endif


@protocol MttGameEngineProtocol <NSObject>

@optional
//初始化游戏引擎
- (void)game_engine_init:(NSString*)jsonStr;
    
//得到用于显示的view
- (UIView*)game_engine_get_view;
    
//暂停游戏
- (void)game_engine_onPause;
    
//恢复游戏
- (void)game_engine_onResume;
    
//退出游戏
- (void)game_engine_onStop;
    
//设置GameEngineRuntimeProxy对象
- (void)game_engine_set_runtime_proxy:(id<MttGameEngineDelegate>)proxy;
    
//调用某个方法， method为方法名， bundle存有方法所用的参数
- (void)game_engine_invoke_method:(NSString*)method bundle:(NSDictionary*)bundle;
    
//获取游戏引擎key所对应的的值
- (id)game_engine_get_value:(NSString*)key;
    
//x5通过这个接口发送消息给game engine
- (void)game_engine_send_msg:(NSDictionary*)jsonObj;
@end
