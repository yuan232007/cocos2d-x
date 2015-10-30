//
//  ChannelConfig.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "ChannelConfig.h"

NSString *channelID;
NSString *cocosRuntimeRootPath;

@implementation ChannelConfig

+ (void) setChannelID:(NSString *)channel
{
    channelID = channel;
}

+ (NSString*) getChannelID
{
    return channelID;
}

+ (void) setCocosRuntimeRootPath:(NSString *)path
{
    cocosRuntimeRootPath = path;
}

+ (NSString*) getCocosRuntimeRootPath
{
    return cocosRuntimeRootPath;
}

@end
