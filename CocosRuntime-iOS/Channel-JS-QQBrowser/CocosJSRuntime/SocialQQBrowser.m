#import "SocialQQBrowser.h"
#import "Wrapper.h"
#import "SocialWrapper.h"
#import "PluginHelper.h"
#import "MttGameEngine.h"
#import "UserQQBrowser.h"

#define OUTPUT_LOG(...)     [PluginHelper logDebug:__VA_ARGS__]

typedef enum
{
    SOCIAL_USER = 8000,
    SOCIAL_GET_FRIENDS_INFO_SUCCESS,
    SOCIAL_GET_FRIENDS_INFO_FAIL,
    SOCIAL_OPEN_TOPIC_CIRCLE_SUCCESS,
    SOCIAL_OPEN_TOPIC_CIRCLE_FAIL,
    SOCIAL_GET_FRIENDS_INFO_CANCEL,
    SOCIAL_GET_FRIENDS_INFO_NEED_LOGIN_AGAIN
}SOCIAL_RET_EXCODE;

@implementation SocialQQBrowser

- (id)init {
    if ([super init]) {
        [self configDeveloperInfo:[PluginHelper getParamsInfo]];
    }
    return self;
}

- (void)configDeveloperInfo:(NSMutableDictionary *)cpInfo {
    OUTPUT_LOG(@"config params:%@",cpInfo);
}

- (void)getFriendsInfo
{
    UserQQBrowser* userInstance = [UserQQBrowser getInstance];
    NSString *errorMsg = nil;
    int retCode = SOCIAL_GET_FRIENDS_INFO_FAIL;
    
    do {
        if (userInstance == nil || ![userInstance isLogined]) {
            retCode = SOCIAL_GET_FRIENDS_INFO_NEED_LOGIN_AGAIN;
            errorMsg = @"UserQQBrowser didn't init yet!";
            break;
        }
        
        NSDictionary* appInfoForX5 = [[NSDictionary alloc] initWithObjectsAndKeys:
                                               [userInstance getAppID], @"appid",
                                               [userInstance getAppSig], @"appsig",
                                               [userInstance getAppOpenID], @"qbopenid",
                                               [userInstance getAppOpenKey], @"qbopenkey",
                                               nil];
        
        [[MttGameEngine getEngineDelegate] x5GamePlayer_get_game_friends:appInfoForX5 callback:^(NSDictionary *dict) {
            int retCode = [[dict objectForKey:@"result"] intValue];
            NSString* retMsg = [UserQQBrowser dictToJSONString:dict];
            switch (retCode) {
                case 0:
                    [SocialWrapper onSocialResult:self retCode:SOCIAL_GET_FRIENDS_INFO_SUCCESS retMsg:retMsg];
                    break;
                case -1:
                    [SocialWrapper onSocialResult:self retCode:SOCIAL_GET_FRIENDS_INFO_CANCEL retMsg:retMsg];
                    break;
                case -3:
                    [SocialWrapper onSocialResult:self retCode:SOCIAL_GET_FRIENDS_INFO_NEED_LOGIN_AGAIN retMsg:retMsg];
                    break;
                default:
                    [SocialWrapper onSocialResult:self retCode:SOCIAL_GET_FRIENDS_INFO_FAIL retMsg:retMsg];
                    break;
            }
        }];
    } while (false);
    
    if (errorMsg) {
        NSString* msg = [UserQQBrowser dictToJSONString:
                         [NSDictionary dictionaryWithObjectsAndKeys:errorMsg,@"error", nil]];
        [SocialWrapper onSocialResult:self retCode:retCode retMsg:msg];
    }
}

- (void)openTopicCircle
{
    UserQQBrowser* userInstance = [UserQQBrowser getInstance];
    if (userInstance && [userInstance isLogined]) {
        NSDictionary* appInfo = [[NSDictionary alloc] initWithObjectsAndKeys:
                                 [userInstance getAppID],@"appid", nil];
        [[MttGameEngine getEngineDelegate] x5GamePlayer_open_topicCircle:appInfo callback:^(NSDictionary *dict) {
            
        }];
    }
}

- (BOOL)isFunctionSupported:(NSString *)functionName {
    OUTPUT_LOG(@"call func:%s info:%@", __FUNCTION__, functionName);
    
    NSString *temp  = [functionName stringByAppendingString:@":"];
    SEL sel = NSSelectorFromString(functionName);
    SEL sel_param = NSSelectorFromString(temp);
    
    return [self respondsToSelector:sel] || [self respondsToSelector:sel_param];
}

- (void)signIn {
}

- (void)signOut {
}

- (void)submitScore:(NSString *)leaderboardID withScore:(long)score {
}

- (void)showLeaderboard:(NSString *)leaderboardID {
}

- (void)unlockAchievement:(NSMutableDictionary *)achInfo {
}

- (void)showAchievements {
}

- (NSString *)getSDKVersion {
	return kSDKVersion;
}

- (NSString *)getPluginVersion {
	return kPluginVersion;
}

@end
