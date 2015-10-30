//
//  GameInfo.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GameInfo : NSObject
{
    NSString *gameKey;
    NSString *downloadUrl;
    NSString *gameName;
    NSString *gameVersionName;
    NSInteger gameVersionCode;
}

@property NSString *gameKey, *downloadUrl, *gameName, *gameVersionName;
@property NSInteger gameVersionCode;

- (GameInfo*) initWithKey: (NSString*) key withUrl:(NSString*) url withName:(NSString*) gameName withVersionName:(NSString*) versionName withVersionCode: (NSInteger) versionCode;
@end
