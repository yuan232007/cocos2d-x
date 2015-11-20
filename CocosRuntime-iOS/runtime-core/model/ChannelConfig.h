//
//  ChannelConfig.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ChannelConfig : NSObject

+ (void) setChannelID: (NSString*) channel;
+ (NSString*) getChannelID;

+ (void) setCocosRuntimeRootPath: (NSString*) path;
+ (NSString*) getCocosRuntimeRootPath;
@end
