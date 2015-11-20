//
//  NetworkHelper.h
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/28.
//
#import <Foundation/Foundation.h>

typedef enum : NSInteger {
    NetworkType_NotReachable = -1,
    NetworkType_Mobile,
    NetworkType_WiFi
} RTNetworkType;

@interface RTNetworkHelper : NSObject

@property (nonatomic, weak) void(^networkChangeBlock)(RTNetworkType);

+ (RTNetworkType)getNetworkType;

- (void)setListener:(void(^)(RTNetworkType networkType))callback;

@end