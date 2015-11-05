//
//  NetworkHelper.mm
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/28.
//

#import "RTNetworkHelper.h"
#import "RTReachability.h"

@interface RTNetworkHelper()

@property RTReachability* reachability;

-(id) init;
- (void)reachabilityChanged:(NSNotification *)note;

@end

@implementation RTNetworkHelper

- (id)init
{
    if (self = [super init]) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reachabilityChanged:) name:kReachabilityChangedNotification object:nil];
    }
    
    return self;
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kReachabilityChangedNotification object:nil];
}

-(void)reachabilityChanged:(NSNotification *)note
{
    RTNetworkType networkType = NetworkType_NotReachable;
    
    RTReachability* curReach = [note object];
    if ([curReach isKindOfClass:[RTReachability class]]) {
        RTNetworkStatus status = [curReach currentReachabilityStatus];
        switch (status) {
            case RTNotReachable:
                break;
            case RTReachableViaWWAN:
                networkType = NetworkType_Mobile;
                break;
            case RTReachableViaWiFi:
                networkType = NetworkType_WiFi;
                break;
            default:
                break;
        }
    }
    
    if (self.networkChangeBlock != nil) {
        self.networkChangeBlock(networkType);
    }
}

- (void)setListener:(void (^)(RTNetworkType))callback
{
    if (self.reachability == nil) {
        self.reachability = [RTReachability reachabilityWithHostName:@"www.baidu.com"];
    }
    self.networkChangeBlock = callback;
    
    [self.reachability startNotifier];
}

+ (RTNetworkType)getNetworkType
{
    RTNetworkType networkType = NetworkType_NotReachable;
    
    auto hostReach = [RTReachability reachabilityWithHostName:@"www.baidu.com"];
    
    switch ([hostReach currentReachabilityStatus]) {
        case RTNotReachable:
            break;
        case RTReachableViaWWAN:
            networkType = NetworkType_Mobile;
            break;
        case RTReachableViaWiFi:
            networkType = NetworkType_WiFi;
            break;
        default:
            break;
    }
    
    return networkType;
}

@end