//
//  IAPChannel.h
//

#import <Foundation/Foundation.h>
#import "InterfaceIAP.h"

@interface IAPQQBrowser : NSObject <InterfaceIAP>

/**
 *  pay for product
 *
 *  @param profuctInfo the information of the product
 key:Product_Id value: the identifier of product
 key:Product_Name value: the name of product
 key:Product_Price value: the price of product, denominated as the yuan.
 key:Product_Count value: the count of product
 key:Role_Id value:the identifier of role
 key:Role_Name value: the name of role
 key:Role_Grade value: the grade of role
 key:Role_Balance value: the virtual currency amount of role
 key:Server_Id value: the identifier of paying server
 key:EXT value: Extended Parameters
 * @note the rule of production maybe changes,please the description is subject to the wiki(http://docs.anysdk.com/IAPSystem#.E6.94.AF.E4.BB.98)
 */
- (void)payForProduct:(NSMutableDictionary *)productInfo;

/**
 *  get the order identifier
 *
 *  @return the order identifier
 */
- (NSString *)getOrderId;

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
 *  init SDK
 *
 *  @param cpInfo the parameters of SDK
 */
- (void)configDeveloperInfo:(NSMutableDictionary *)cpInfo;


/*-------IAP------*/
/**
 *  pay callback function
 *
 *  @param status  status about the payment
 *  @param message other message
 */
- (void)onPayResult:(int)status msg:(NSString *)message;

@end
