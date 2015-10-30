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
}

@property NSString *gameKey, *downloadUrl, *gameName;

- (GameInfo*) initWithKey: (NSString*) key withUrl:(NSString*) url withName:(NSString*) gameName;
@end
