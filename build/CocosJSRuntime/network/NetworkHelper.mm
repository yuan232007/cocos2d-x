//
//  NetworkHelper.mm
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/28.
//

#import "NetworkHelper.h"
#import "Reachability.h"

@interface NetworkHelper()

@property Reachability* reachability;

-(id) init;
- (void)reachabilityChanged:(NSNotification *)note;

@end

@implementation NetworkHelper

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
    NetworkType networkType = NetworkType_NotReachable;
    
    Reachability* curReach = [note object];
    if ([curReach isKindOfClass:[Reachability class]]) {
        NetworkStatus status = [curReach currentReachabilityStatus];
        switch (status) {
            case NotReachable:
                break;
            case ReachableViaWWAN:
                networkType = NetworkType_Mobile;
                break;
            case ReachableViaWiFi:
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

- (void)setListener:(void (^)(NetworkType))callback
{
    if (self.reachability == nil) {
        self.reachability = [Reachability reachabilityWithHostName:@"www.baidu.com"];
    }
    self.networkChangeBlock = callback;
    
    [self.reachability startNotifier];
}

+ (NetworkType)getNetworkType
{
    NetworkType networkType = NetworkType_NotReachable;
    
    auto hostReach = [Reachability reachabilityWithHostName:@"www.baidu.com"];
    
    switch ([hostReach currentReachabilityStatus]) {
        case NotReachable:
            break;
        case ReachableViaWWAN:
            networkType = NetworkType_Mobile;
            break;
        case ReachableViaWiFi:
            networkType = NetworkType_WiFi;
            break;
        default:
            break;
    }
    
    return networkType;
}

@end