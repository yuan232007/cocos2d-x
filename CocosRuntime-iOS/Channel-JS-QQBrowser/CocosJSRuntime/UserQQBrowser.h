//
//  UserQQBrowser.h
//

#import <Foundation/Foundation.h>
#import "InterfaceUser.h"

#define  kSDKVersion  @"1.0.0"
#define  kPluginVersion  @"1.0.0"
#define  kPluginID  @"cocos_runtime_qqbrowser_user"
#define  kLoginCnl  @"QQBrowser"

@interface UserQQBrowser : NSObject <InterfaceUser>

@property(nonatomic,assign) BOOL isLogined;
@property(nonatomic,assign) BOOL isDebug;

+ (UserQQBrowser *)getInstance;

+ (NSString*)dictToJSONString:(id)dict;

- (NSString*)getAppID;
- (NSString*)getAppSig;
- (NSString*)getAppOpenID;
- (NSString*)getAppOpenKey;

- (void) setDebugMode: (BOOL) debug;
- (void)debugLog:(NSString*)msg;

/**
 *  user login
 */
- (void)login;

/**
 *  get the status of login
 *
 *  @return  status of login
 */
- (BOOL)isLogined;

/**
 *  get user identifier
 *
 *  @return user identifier
 */
- (NSString *)getUserID;

/**
 *  get the version of SDK
 *
 *  @return the version of SDK
 */
- (NSString *)getSDKVersion;

/**
 *  get the version of plugin
 *
 *  @return the version of plugin
 */
- (NSString *)getPluginVersion;

/**
 *  get the identifier of plugin
 *
 *  @return the identifier of plugin
 */
- (NSString *)getPluginId;

/**
 *  whether function is supported
 *
 *  @param functionName the name of function
 *
 *  @return return If the function is supported, return true
 or if the function is  not supported, return false
 */
- (BOOL)isFunctionSupported:(NSString *)functionName;

/**
 *  init SDK
 *
 *  @param cpInfo the parameters of SDK
 */
- (void)configDeveloperInfo:(NSMutableDictionary *)cpInfo;

/********* self need *********/
/**
 *  user callback function
 *
 *  @param status  other status about the user
 *  @param message other message
 */
- (void)onActionResult:(int)status msg:(NSString*)message;

@end


