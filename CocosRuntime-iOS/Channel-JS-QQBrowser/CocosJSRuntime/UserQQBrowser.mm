#import "UserQQBrowser.h"
#import "Wrapper.h"
#import "UserWrapper.h"
#import "PluginHelper.h"
#import "MttGameEngine.h"

#include "platform/CCFileUtils.h"

#define OUTPUT_LOG(...)     [PluginHelper logDebug:__VA_ARGS__]

static UserQQBrowser *s_userQQBrowserInstance = nil;

typedef enum
{
    ACTION_RET_USER = 8000,
    ACTION_RET_REFRESH_TOKEN_SUCCESS,
    ACTION_RET_REFRESH_TOKEN_FAIL,
    ACTION_RET_SEND_TO_DESKTOP_SUCCESS,
    ACTION_RET_SEND_TO_DESKTOP_FAIL,
    ACTION_RET_GET_AVAILABLE_LOGIN_TYPE_SUCCESS,
    ACTION_RET_GET_AVAILABLE_LOGIN_TYPE_FAIL,
    ACTION_RET_GET_USER_INFO_SUCCESS,
    ACTION_RET_GET_USER_INFO_FAIL
}USER_RET_EXCODE;

@interface UserQQBrowser()
@property (nonatomic, weak) id<MttGameEngineDelegate> x5Delegate;
@property(nonatomic,strong) NSString *appID;
@property(nonatomic,strong) NSString *appSig;
@property(nonatomic,strong) NSString *loginType;
@property(nonatomic,strong) NSString *qbOpenID;
@property(nonatomic,strong) NSString *qbOpenKey;
@property(nonatomic,strong) NSString *refreshToken;
@property(nonatomic,strong) NSString *avatarUrl;

@property(nonatomic,strong) NSString *gameToken;
@property(nonatomic,strong) NSString *gameTokenFile;

@end

@implementation UserQQBrowser

- (id)init {
    if ([super init]) {
        s_userQQBrowserInstance = self;
        _isLogined = false;
        _isDebug = false;
        _x5Delegate = [MttGameEngine getEngineDelegate];
        [self configDeveloperInfo:[PluginHelper getParamsInfo]];
        [self onActionResult:ACTION_RET_INIT_SUCCESS msg:@"UserQQBrowser init success!"];
    }
    return self;
}

- (void)configDeveloperInfo:(NSMutableDictionary *)devInfo {
    OUTPUT_LOG(@"UserQQBrowser in configDeveloperInfo:%@", devInfo);
}

- (void)setDebugMode:(BOOL)debug
{
    _isDebug = debug;
}

- (void)debugLog:(NSString *)msg
{
    [_x5Delegate x5GamePlayer_send_msg:[NSDictionary dictionaryWithObjectsAndKeys:msg,@"debug msg", nil]];
}

- (void)delayLoginCall
{
    struct timeval currTime;
    gettimeofday(&currTime, NULL);
    long millisTime = currTime.tv_sec * 1000 + currTime.tv_usec / 1000 + 7000000;
    
    
    NSDictionary *loginResult = [NSDictionary dictionaryWithObjectsAndKeys:_avatarUrl, @"avatarUrl",
                                 _qbOpenID, @"qbopenid",
                                 _qbOpenKey, @"qbopenkey",
                                 _refreshToken, @"refreshToken",
                                 @"",@"msg",
                                 @"L",@"nickName",
                                 @"0",@"result",
                                 @"",@"rspsig",
                                 @"qq",@"loginType",
                                 [[NSNumber alloc] initWithLong:millisTime],@"expireIn",
                                 nil];
    
    [self onActionResult:ACTION_RET_LOGIN_SUCCESS msg:[UserQQBrowser dictToJSONString:loginResult]];
}

- (void)loginWithParams:(NSMutableDictionary*)info
{
    OUTPUT_LOG(@"call func:%s info:%@", __FUNCTION__, info);
    [self resetUserPlugin];
    
    _appID = [info objectForKey:@"appid"];
    _appSig = [info objectForKey:@"appsig"];
    _loginType = [info objectForKey:@"loginType"];
    
    if(_isDebug) {
        _isLogined = true;
        _qbOpenID = @"taBoVS558UXGPc5PE1nqgzbrjx4-EP37o6aFrKjUnU9OAEd_-FnEzA";
        _qbOpenKey = @"MvL0kGspU0c-63UfA6sUG1wD40uD8j0zTz9-RfZrLRIvoP6_Ws0Wgpv534zrwejuiBm1b5fzF95bNh1mi0pg05UCbaTkZLtndYc5S45z92OGp2yGnkvqO2Iefbd4rsf5bDE1lB5VGvg";
        _refreshToken = @"eJzBzLYCmaS9ec-I92NDmCSHseU5xQpAsj3KiavWBk5L9cLLdzjC9IINLBR2wo4E0j2rqwaifEF164l13nv4mqE1cjqxJ00LuKH-hgsslRNSBICAJtD9GA";
        _avatarUrl = @"http://q4.qlogo.cn/g?b=qq&k=h2rrhrEUdr4qQ0cL2qSQgQ&s=100&t=528";
        
        [self performSelector:@selector(delayLoginCall) withObject:nil afterDelay:1.f];
    }
    else {
        [_x5Delegate x5GamePlayer_login:info callback:^(NSDictionary *result) {
            [_x5Delegate x5GamePlayer_send_msg:result];
            auto fu = cocos2d::FileUtils::getInstance();
            fu->writeStringToFile( [[UserQQBrowser dictToJSONString:result] cStringUsingEncoding:NSUTF8StringEncoding], fu->getWritablePath() + "/loginResult.txt");
            
            NSNumber *loginRet = [result objectForKey:@"result"];
            if (loginRet) {
                int retCode = [loginRet intValue];
                switch (retCode) {
                    case 0:
                    {
                        _isLogined = true;
                        _qbOpenID = [NSString stringWithString:[result objectForKey:@"qbopenid"]];
                        _qbOpenKey = [NSString stringWithString:[result objectForKey:@"qbopenkey"]];
                        _refreshToken = [NSString stringWithString:[result objectForKey:@"refreshToken"]];
                        _avatarUrl = [NSString stringWithString:[result objectForKey:@"avatarUrl"]];
                        
                        NSMutableDictionary* loginInfo = [result mutableCopy];
                        [loginInfo setObject:_qbOpenID forKey:@"accountID"];
                        
                        [self onActionResult:ACTION_RET_LOGIN_SUCCESS msg:[UserQQBrowser dictToJSONString:loginInfo]];
                        return;
                    }
                    case -1:
                    {
                        [self onActionResult:ACTION_RET_LOGIN_CANCEL msg:[UserQQBrowser dictToJSONString:result]];
                        return;
                    }
                    default:
                    {
                        [self onActionResult:ACTION_RET_LOGIN_FAIL msg:[UserQQBrowser dictToJSONString:result]];
                        return;
                    }
                }
            }
        }];
    }
}

- (void)x5_login:(NSMutableDictionary*)info
{
    OUTPUT_LOG(@"call func:%s", __FUNCTION__);
    [self loginWithParams:info];
}

//需要确认是否需要
- (NSString*)x5_getToken
{
    OUTPUT_LOG(@"call func:%s", __FUNCTION__);
    //登录成功后token需要保存到本地，进入游戏后会先读取保存的token
    if (_gameToken == nil) {
        if (_gameTokenFile == nil) {
            _gameTokenFile = [NSString stringWithFormat:@"%@gameToken.json",[_x5Delegate x5GamePlayer_get_value:@"TokenDir"]];
        }
        auto token = cocos2d::FileUtils::getInstance()->getStringFromFile([_gameTokenFile cStringUsingEncoding:NSUTF8StringEncoding]);
        _gameToken = [NSString stringWithCString:token.c_str() encoding:NSUTF8StringEncoding];
    }
    
    if (_gameToken == nil || [_gameToken length] == 0) {
        return @"{}";
    }
    
    return _gameToken;
}

- (void)x5_setToken:(NSString*)jsonStr
{
    _gameToken = [NSString stringWithString:jsonStr];
    if (_gameTokenFile == nil) {
        _gameTokenFile = [NSString stringWithFormat:@"%@gameToken.json",[_x5Delegate x5GamePlayer_get_value:@"TokenDir"]];
    }
    cocos2d::FileUtils::getInstance()->writeStringToFile([_gameToken cStringUsingEncoding:NSUTF8StringEncoding], [_gameTokenFile cStringUsingEncoding:NSUTF8StringEncoding]);
}

- (void)x5_refreshToken:(NSMutableDictionary*)info
{
    OUTPUT_LOG(@"call func:%s info:%@", __FUNCTION__, info);
    [self resetUserPlugin];
    
    _appID = [info objectForKey:@"appid"];
    _appSig = [info objectForKey:@"appsig"];
    _refreshToken = [info objectForKey:@"refreshToken"];
    
    [_x5Delegate x5GamePlayer_refresh_token:info callback:^(NSDictionary *result) {
        NSNumber *loginRet = [result objectForKey:@"result"];
        if (loginRet) {
            int retCode = [loginRet intValue];
            switch (retCode) {
                case 0:
                {
                    _isLogined = true;
                    _qbOpenID = [NSString stringWithString:[result objectForKey:@"qbopenid"]];
                    _qbOpenKey = [NSString stringWithString:[result objectForKey:@"qbopenkey"]];
                    
                    [self onActionResult:ACTION_RET_REFRESH_TOKEN_SUCCESS msg:[UserQQBrowser dictToJSONString:result]];
                    break;
                }
                default:
                {
                    [self onActionResult:ACTION_RET_REFRESH_TOKEN_FAIL msg:[UserQQBrowser dictToJSONString:result]];
                    break;
                }
            }
        }
    }];
}

- (void)logout
{
    OUTPUT_LOG(@"call func:%s", __FUNCTION__);
    
    NSString *errorMsg = nil;
    int retCode = ACTION_RET_LOGOUT_FAIL;
    
    do {
        if (_appID == nil) {
            errorMsg = @"appid is nil,please login or refreshToken firsl!";
            break;
        }
        
        if (_qbOpenID == nil) {
            errorMsg = @"qbopenid is nil,please login or refreshToken firsl!";
            break;
        }
        
#if COCOS2D_DEBUG
        [self resetUserPlugin];
        NSDictionary* logoutRet = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithInt:0],
                                   @"resule", @"logout success",@"msg",nil];
        [self onActionResult:ACTION_RET_LOGOUT_SUCCESS msg:[UserQQBrowser dictToJSONString:logoutRet]];
#else
        NSDictionary *loginInfo = [NSDictionary dictionaryWithObjectsAndKeys:_appID, @"appid",
                                   _qbOpenID, @"qbopenid",
                                   _loginType, @"logintype",
                                   nil];
        
        [_x5Delegate x5GamePlayer_logout:loginInfo callback:^(NSDictionary *result) {
            int retCode = [[result objectForKey:@"result"] intValue];
            switch (retCode) {
                case 0:
                    [self resetUserPlugin];
                    [self onActionResult:ACTION_RET_LOGOUT_SUCCESS msg:[UserQQBrowser dictToJSONString:result]];
                    break;
                default:
                    [self onActionResult:ACTION_RET_LOGOUT_FAIL msg:[UserQQBrowser dictToJSONString:result]];
                    break;
            }
        }];
#endif
    } while (false);
    
    if (errorMsg) {
        NSString* msg = [UserQQBrowser dictToJSONString:
                         [NSDictionary dictionaryWithObjectsAndKeys:errorMsg,@"error", nil]];
        [self onActionResult:retCode msg:msg];
    }
}

- (void)getUserInfo
{
    OUTPUT_LOG(@"call func:%s", __FUNCTION__);
    if (_isLogined) {
        NSDictionary *appInfo = [NSDictionary dictionaryWithObjectsAndKeys:_appID, @"appid",
                                 _qbOpenID, @"qbopenid",
                                 _qbOpenKey, @"qbopenkey",
                                 nil];
        
        [_x5Delegate x5GamePlayer_getUserInfo:appInfo callback:^(NSDictionary *result) {
            int retCode = [[result objectForKey:@"result"] intValue];
            switch (retCode) {
                case 0:
                    [self onActionResult:ACTION_RET_GET_USER_INFO_SUCCESS msg:[UserQQBrowser dictToJSONString:result]];
                    break;
                default:
                    [self onActionResult:ACTION_RET_GET_USER_INFO_FAIL msg:[UserQQBrowser dictToJSONString:result]];
                    break;
            }
        }];
    }
}

- (void)sendToDesktop:(NSMutableDictionary*)info
{
    OUTPUT_LOG(@"call func:%s info:%@", __FUNCTION__, info);

    [_x5Delegate x5GamePlayer_send_to_desktop:info callback:^(NSDictionary *result) {
        int retCode = [[result objectForKey:@"result"] intValue];
        switch (retCode) {
            case 0:
                [self onActionResult:ACTION_RET_SEND_TO_DESKTOP_SUCCESS msg:[UserQQBrowser dictToJSONString:result]];
                break;
            default:
                [self onActionResult:ACTION_RET_SEND_TO_DESKTOP_FAIL msg:[UserQQBrowser dictToJSONString:result]];
                break;
        }
    }];
}

- (void)x5_sendToDesktop:(NSMutableDictionary*)info
{
    OUTPUT_LOG(@"call func:%s info:%@", __FUNCTION__, info);
    [self sendToDesktop:info];
}

- (void)getAvailableLoginType:(NSMutableDictionary*)info
{
    OUTPUT_LOG(@"call func:%s info:%@", __FUNCTION__, info);

    [_x5Delegate x5GamePlayer_getAvailableLoginType:info callback:^(NSDictionary *result) {
        int retCode = [[result objectForKey:@"result"] intValue];
        switch (retCode) {
            case 0:
                [self onActionResult:ACTION_RET_GET_AVAILABLE_LOGIN_TYPE_SUCCESS msg:[UserQQBrowser dictToJSONString:result]];
                break;
            default:
                [self onActionResult:ACTION_RET_GET_AVAILABLE_LOGIN_TYPE_FAIL msg:[UserQQBrowser dictToJSONString:result]];
                break;
        }
    }];
}

- (void)onActionResult:(int)status msg:(NSString *)message {
    OUTPUT_LOG(@"onActionResult,status:%@, message:%@\n",[NSNumber numberWithInt:status],message);
    [UserWrapper onActionResult:self retCode:status retMsg:message];
}

- (void)login {
}

- (BOOL)isLogined {
    OUTPUT_LOG(@"call func:%s", __FUNCTION__);
    return _isLogined;
}

- (BOOL)isFunctionSupported:(NSString *)functionName {
    OUTPUT_LOG(@"call func:%s info:%@", __FUNCTION__, functionName);
    
    NSString *temp  = [functionName stringByAppendingString:@":"];
    SEL sel = NSSelectorFromString(functionName);
    SEL sel_param = NSSelectorFromString(temp);
    
    return [self respondsToSelector:sel] || [self respondsToSelector:sel_param];
}

- (void)resetUserPlugin
{
    _isLogined = false;
    _appID = nil;
    _appSig = nil;
    _qbOpenID = nil;
    _qbOpenKey = nil;
    _loginType = nil;
    _refreshToken = nil;
    _gameToken = nil;
    _avatarUrl = nil;
}

- (NSString *)getUserID {
    return _qbOpenID;
}

- (NSString *)getSDKVersion {
    return kSDKVersion;
}

- (NSString *)getPluginVersion {
    return kPluginVersion;
}

- (NSString *)getPluginId {
    return kPluginID;
}

- (void)getAccessToken {
    OUTPUT_LOG(@"call func:%s", __FUNCTION__);
}

- (NSString*)getAppID
{
    return _appID;
}

- (NSString*)getAppSig
{
    return _appSig;
}

- (NSString*)getAppOpenID
{
    return _qbOpenID;
}

- (NSString*)getAppOpenKey
{
    return _qbOpenKey;
}

+ (UserQQBrowser *)getInstance {
    return s_userQQBrowserInstance;
}

+ (NSString*)dictToJSONString:(id)dict
{
    NSString* ret = [[NSString alloc] initWithData:[NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:nil] encoding:NSUTF8StringEncoding];
    
    return ret;
}

@end


