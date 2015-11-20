//
//  NetworkController.m
//  CocosJSRuntime
//
//  Created by Rye on 11/13/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "NetworkController.h"
#import "GameInfo.h"
#import "ChannelConfig.h"

#define COCOS_ONLINE_ADDRESS @"http://playerapi.coco.cn"
#define COCOS_SANDBOX_ADDRESS @"http://cocosplay.ucenter.appget.cn"
#define COCOS_OFFLINE_ADDRESS @"http://192.168.52.80"
#define COCOS_STAGING_ADDRESS @"http://staging.cocosplay.coco.cn"

@implementation NetworkController

+ (void) requestGameInfoByGameKey: (NSString*)gameKey callback:(void (^)(GameInfo *, BOOL))callback
{
    NSString *urlString = [[[[[[COCOS_STAGING_ADDRESS stringByAppendingString:@"/capi/apiv5/gamepackage?"] stringByAppendingString:@"gamekey="] stringByAppendingString:gameKey] stringByAppendingString:@"&arch=armeabi"] stringByAppendingString:@"&chn="] stringByAppendingString:[ChannelConfig getChannelID]];
    
    NSLog(@"===> NetworkController requestGameInfoByGameKey requestURL: %@", urlString);
    
    NSURL *url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    [request setHTTPMethod:@"GET"];
    [request setTimeoutInterval:20];
    [[[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        if (error == nil) {
            NSError *jsonError = nil;
            NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&jsonError];
            if (jsonError == nil && [[dict allKeys] containsObject:@"data"]) {
                GameInfo *info = [[GameInfo alloc] initWithDictionary:[dict objectForKey:@"data"]];
                if (info != nil) {
                    callback(info, FALSE);
                    return;
                }
            }
        }
        callback(nil, TRUE);
    }] resume];
    
}

+ (NSURLSession*) getCurrentSession: (id<NSURLSessionDelegate>)delegate
{
    dispatch_once_t predicate = 0;
    __block NSURLSession *currentSession;
    // 使用 dispatch_once 创建单例
    dispatch_once(&predicate, ^{
        NSURLSessionConfiguration* config =  [NSURLSessionConfiguration defaultSessionConfiguration];
        currentSession = [NSURLSession sessionWithConfiguration:config delegate:delegate delegateQueue: nil];
    });
    return currentSession;
}


@end
