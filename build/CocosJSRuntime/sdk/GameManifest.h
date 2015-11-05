//
//  GameManifest.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ResGroup.h"

@interface GameManifest : NSObject
{
    NSMutableArray* allResGroups;
}

@property NSMutableArray* allResGroups;

+(GameManifest*) readFromFile: (NSString*) path;
@end
