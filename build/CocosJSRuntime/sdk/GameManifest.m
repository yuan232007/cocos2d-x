//
//  GameManifest.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "GameManifest.h"
#import "FileUtil.h"

@implementation GameManifest

@synthesize resGroupArray;

+(GameManifest*) readFromFile:(NSString *)path
{
    GameManifest *manifest = [[GameManifest alloc]init];
    NSDictionary *jsonDict = (NSDictionary*)[FileUtil readJsonFromFile: path];
    NSMutableArray *resGroupArray = [jsonDict objectForKey:@"res_groups"];
    [manifest setResGroupArray:resGroupArray];
    return manifest;
}
@end