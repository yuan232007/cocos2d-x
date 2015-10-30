//
//  GameInfo.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "GameInfo.h"

@implementation GameInfo

- (GameInfo*) initWithKey:(NSString *)key withUrl:(NSString *)url withName:(NSString *)name withVersionName:(NSString *)versionName withVersionCode:(NSInteger)versionCode
{
    if (self = [super init]) {
        gameKey = key;
        downloadUrl = url;
        gameName = name;
        gameVersionName = versionName;
        gameVersionCode = versionCode;
    }
    
    return self;
}

@synthesize gameKey, gameName, gameVersionCode, gameVersionName, downloadUrl;

@end
