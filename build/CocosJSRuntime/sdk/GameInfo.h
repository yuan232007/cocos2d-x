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
    /* 游戏唯一标识 */
    NSString *gameKey;
    /* 游戏下载地址，为最上层目录，后续JS兼容版本必须在此地址后拼接指定文件夹 */
    NSString *downloadUrl;
    /* 游戏名称 */
    NSString *gameName;
}

@property NSString *gameKey, *downloadUrl, *gameName;

- (GameInfo*) initWithKey: (NSString*) key withUrl:(NSString*) url withName:(NSString*) gameName;
- (GameInfo*) initWithDictionary: (NSDictionary*)dictonary;
@end
