//
//  SocialTemplate.h
//
//

#import <Foundation/Foundation.h>
#import "InterfaceSocial.h"

@interface SocialQQBrowser : NSObject <InterfaceSocial>

@property(nonatomic,assign) BOOL bDebug;
/**
 *  login in socail system
 */
- (void)signIn;

/**
 *  logout in socail system
 */
- (void)signOut;
/**
 *  submit the socre for leaderboard
 *
 *  @param leaderboardID the identifier of leaderboard
 *  @param score         the score
 */
- (void)submitScore:(NSString *)leaderboardID withScore:(long)score;

/**
 *  show the leaderboard
 *
 *  @param leaderboardID the identifier of leaderboard
 */
- (void)showLeaderboard:(NSString *)leaderboardID;

/**
 *   unlock achievements of game
 *
 *  @param achInfo the content of achievement
 */
- (void)unlockAchievement:(NSMutableDictionary*) achInfo;

/**
 *  show achievements of game
 */
- (void)showAchievements;
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
 *  init SDK
 *
 *  @param cpInfo the parameters of SDK
 */
- (void)configDeveloperInfo:(NSMutableDictionary *)cpInfo;

- (BOOL) isFunctionSupported : (NSString*) functionName;

@end
