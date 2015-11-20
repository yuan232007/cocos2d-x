//
//  GroupPatch.h
//  CocosJSRuntime
//
//  Created by Rye on 11/11/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GroupPatch : NSObject
{
    NSString *patchMD5;
    NSString *patchURL;
    NSInteger patchSize;
}

@property NSString *patchMD5, *patchURL;
@property NSInteger patchSize;

@end
