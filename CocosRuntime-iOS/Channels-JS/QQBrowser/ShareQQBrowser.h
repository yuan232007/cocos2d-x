//
//  ShareTemplate.h
//

#import <Foundation/Foundation.h>
#import "InterfaceShare.h"

@interface ShareQQBrowser : NSObject <InterfaceShare>

@property(nonatomic,assign) BOOL bDebug;

/**
 *  share
 *
 *  @param shareInfo the content of share
 *  @note  the description is subject to the wiki(http://docs.anysdk.com/IAPSystem#.E6.94.AF.E4.BB.98)
 */
- (void)share:(NSMutableDictionary *)shareInfo;
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


@end
