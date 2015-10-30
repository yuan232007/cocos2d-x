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
} NetworkType;

@interface NetworkHelper : NSObject

@property (nonatomic, weak) void(^networkChangeBlock)(NetworkType);

+ (NetworkType)getNetworkType;

- (void)setListener:(void(^)(NetworkType networkType))callback;

@end