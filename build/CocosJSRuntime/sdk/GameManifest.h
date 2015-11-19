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

@property (nonatomic,strong) NSMutableArray* allResGroups;

+(GameManifest*) readFromFile: (NSString*) path;
@end

@interface File : NSObject
{
    NSString *fileMD5;
    NSString *fileName;
}

- (File*) initWith:(NSString*)name md5:(NSString*)md5;

@property NSString *fileMD5, *fileName;
@end