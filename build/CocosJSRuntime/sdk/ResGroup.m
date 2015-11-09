//
//  ResGroup.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "ResGroup.h"
#import "FileUtil.h"

@implementation ResGroup

@synthesize groupMD5, groupName, groupURL, groupPriority, groupSize, fileList, isUpdated;

-(ResGroup*) initWith:(NSString *)infoMD5 md5:(NSString *)md5 name:(NSString *)name priority:(NSInteger)priority size:(NSInteger)size url:(NSString *)url files:(NSMutableArray *)files
{
    if (self = [super init]) {
        self.groupMD5 = md5;
        self.groupName = name;
        self.groupURL = url;
        self.groupPriority = priority;
        self.groupSize = size;
        self.fileList = files;
        self->isUpdated = FALSE;
    }
    return self;
}

- (BOOL) isUpdated: (GameInfo*) info
{
    if (isUpdated) {
        return TRUE;
    } else {
        return [self isAllFilesMD5Correct: info];
    }
}

- (BOOL) isAllFilesMD5Correct: (GameInfo*) info
{
    for (File *file in [self fileList]) {
        NSString *localMD5 = [[FileUtil getFileMD5:[FileUtil getGameRootPath:info]] stringByAppendingPathComponent:[file name]];
        if (![localMD5 isEqualToString:localMD5]) {
            return FALSE;
        }
    }
    return TRUE;
}

@end

@implementation File

@synthesize md5, name;

@end
