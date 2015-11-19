#import "IAPQQBrowser.H"
#include <sys/time.h>

#import "UserQQBrowser.h"
#import "Wrapper.h"
#import "IAPWrapper.h"
#import "JsonParser.h"
#import "PluginHelper.h"
#import "MttGameEngine.h"


#define OUTPUT_LOG(...)     [PluginHelper logDebug:__VA_ARGS__]

typedef enum
{
    PAYRESULT_USER = 8000,
    PAYRESULT_NEED_LOGIN_AGAIN
}IAP_RET_EXCODE;

@interface IAPQQBrowser ()

@property (strong, nonatomic) NSMutableDictionary *productInfo;
@property (strong, nonatomic) NSString *orderID;

@end

@implementation IAPQQBrowser

- (id)init {
    if ([super init]){
        [self configDeveloperInfo:[PluginHelper getParamsInfo]];
        [self onPayResult:PAYRESULT_INIT_SUCCESS msg:@""];
    }
    return self;
}

- (void)configDeveloperInfo:(NSMutableDictionary *)cpInfo {
   OUTPUT_LOG(@"config params:%@",cpInfo);
}

- (void)doPayment
{
    NSString *errorMsg = nil;
    int retCode = PAYRESULT_FAIL;
    
    do {
        NSString *productPrice, *productName, *productCount, *productID, *ext;
        @try {
            productID = [_productInfo objectForKey:@"Product_Id"];
            productName = [_productInfo objectForKey:@"Product_Name"];
            productPrice = [_productInfo objectForKey:@"Product_Price"];
            productCount = [_productInfo objectForKey:@"Product_Count"];
            ext = [_productInfo objectForKey:@"EXT"];
            if (productName == nil || productCount == nil || productID == nil || productPrice == nil) {
                errorMsg = [NSString stringWithFormat:
                            @"ProductInfo is incomplete! Product_Id:%@,Product_Name:%@,Product_Price:%@,Product_Count:%@",
                            productID, productName, productPrice, productCount];
                
                retCode = PAYRESULT_PRODUCTIONINFOR_INCOMPLETE;
                break;
            }
        }
        @catch (NSException *exception) {
            retCode = PAYRESULT_PRODUCTIONINFOR_INCOMPLETE;
            errorMsg = [NSString stringWithFormat:
                        @"ProductInfo is incomplete! Product_Id:%@,Product_Name:%@,Product_Price:%@,Product_Count:%@",
                        productID, productName, productPrice, productCount];
            break;
        }
        
        if (ext == nil) {
            ext = @"";
        }
        
        NSMutableDictionary *productForX5 = [[NSMutableDictionary alloc] init];
        UserQQBrowser* userInstance = [UserQQBrowser getInstance];
        [productForX5 setObject:[userInstance getAppID] forKey:@"appid"];
        [productForX5 setObject:[userInstance getAppSig] forKey:@"appsig"];
        [productForX5 setObject:[userInstance getAppOpenID] forKey:@"qbopenid"];
        [productForX5 setObject:[userInstance getAppOpenKey] forKey:@"qbopenkey"];
        
        [productForX5 setObject:productID forKey:@"Product_Id"];
        [productForX5 setObject:productName forKey:@"Product_Name"];
        [productForX5 setObject:productPrice forKey:@"Product_Price"];
        [productForX5 setObject:productCount forKey:@"Product_Count"];
        
        NSString *payItem = [NSString stringWithFormat:@"%@*%@*%@", productID, productCount, productPrice];
        [productForX5 setObject:payItem forKey:@"payItem"];
        [productForX5 setObject:productName forKey:@"payInfo"];
        [productForX5 setObject:ext forKey:@"customMeta"];
        
        float payAmount = [productPrice floatValue] * [productCount intValue];
        [productForX5 setObject:[[NSNumber alloc] initWithFloat:payAmount] forKey:@"payAmount"];
        
        struct timeval currTime;
        gettimeofday(&currTime, NULL);
        long millisTime = currTime.tv_sec * 1000 + currTime.tv_usec / 1000;
        [productForX5 setObject:[[NSNumber alloc] initWithLong:millisTime] forKey:@"reqTime"];
        
        [[MttGameEngine getEngineDelegate] x5GamePlayer_pay:productForX5 callback:^(NSDictionary *dict) {
            NSMutableDictionary *payResult = [dict mutableCopy];
            NSString* customMeta = [payResult objectForKey:@"customMeta"];
            if (customMeta) {
                [payResult setObject:customMeta forKey:@"ext"];
            }
            else {
                [payResult setObject:@"" forKey:@"ext"];
            }
            [payResult setObject:@"CNY" forKey:@"type"];
            [payResult setObject:[userInstance getUserID] forKey:@"accountID"];
            NSString* realSaveNum = [payResult objectForKey:@"realSaveNum"];
            if (realSaveNum) {
                int realAmount = [realSaveNum intValue] * 10;
                [payResult setObject:[[NSNumber alloc] initWithInt:realAmount] forKey:@"amount"];
            }
            
            int retCode = [[dict objectForKey:@"result"] intValue];
            switch (retCode) {
                case 0:
                    [self onPayResult:PAYRESULT_SUCCESS msg:[UserQQBrowser dictToJSONString:payResult]];
                    break;
                case -1:
                    [self onPayResult:PAYRESULT_CANCEL msg:[UserQQBrowser dictToJSONString:payResult]];
                    break;
                case -2:
                    [self onPayResult:PAYRESULT_FAIL msg:[UserQQBrowser dictToJSONString:payResult]];
                    break;
                case -3:
                    [self onPayResult:PAYRESULT_NEED_LOGIN_AGAIN msg:[UserQQBrowser dictToJSONString:payResult]];
                    break;
                default:
                    [self onPayResult:PAYRESULT_FAIL msg:[UserQQBrowser dictToJSONString:payResult]];
                    break;
            }
        }];
    } while (false);
    
    if (errorMsg) {
        NSString* msg = [UserQQBrowser dictToJSONString:
                         [NSDictionary dictionaryWithObjectsAndKeys:errorMsg,@"error", nil]];
        [self onPayResult:retCode msg:msg];
    }
}

- (void)payForProduct:(NSMutableDictionary *)productInfo {
    OUTPUT_LOG(@"payForProduct %@ invoked.\n",productInfo);
    
    NSString *errorMsg = nil;
    int retCode = PAYRESULT_FAIL;
    do {
        if (productInfo == nil) {
            retCode = PAYRESULT_FAIL;
            errorMsg = @"ProductInfo is nil!";
            break;
        }
        
        if (![[UserQQBrowser getInstance] isLogined]) {
            retCode = PAYRESULT_FAIL;
            errorMsg = @"User didn't login!";
            break;
        }
        
        if (![PluginHelper networkReachable]) {
            retCode = PAYRESULT_NETWORK_ERROR;
            errorMsg = @"Network is unreachable!";
            break;
        }
        
        _productInfo = [productInfo mutableCopy];
        [self doPayment];
    } while (false);
    
    if (errorMsg) {
        NSString* msg = [UserQQBrowser dictToJSONString:
                         [NSDictionary dictionaryWithObjectsAndKeys:errorMsg,@"error", nil]];
        [self onPayResult:retCode msg:msg];
    }
}

- (void)getPayOrderId:(NSMutableDictionary *)productInfo {
    
}

- (void)onGetPayOrderId:(NSData *)data {
}

- (NSString *)getOrderId {
    OUTPUT_LOG(@"getOrderId invoked!\n");
    return _orderID;
}

- (NSString *)getSDKVersion {
    return kSDKVersion;
}

- (NSString *)getPluginVersion {
    return kPluginVersion;
}

- (NSString *)getPluginId {
    return @"cocos_runtime_qqbrowser_iap";
}

/*-------IAP------*/

- (void)payInSDK {
    // TODO get the params used by the SDK
    //_notifyUrl= [IAPWrapper replaceNotifyURL:[self class] url:_notifyUrl];
    
    OUTPUT_LOG(@"payInSDK params: \n");
    
    // TODO call payment function supported by the SDK
}

- (void)onPayResult:(int)status msg:(NSString *)message {
    NSLog(@"onPayResult,status:%@, message:%@\n",[NSNumber numberWithInt:status],message);
    [IAPWrapper onPayResult:self retCode:status retMsg:message];
}

@end
