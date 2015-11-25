//
//  DownloadInfo.h
//  CocosJSRuntime
//
//  Created by Rye on 11/24/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DownloadInfo : NSObject
{
    NSString *config;
    long extension;
}
@property NSString *config;
@property long extension;

- (DownloadInfo*) initWith: (NSString*) json extension:(long)ext;
@end
