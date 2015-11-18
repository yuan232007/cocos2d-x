//
//  ResGroup.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "ResGroup.h"
#import "FileUtil.h"
#import "GameManifest.h"

@implementation ResGroup

@synthesize groupMD5, groupName, groupURL, groupPriority, groupSize, fileList, isUpdated, groupPatches;

-(ResGroup*) initWith:(NSString *)infoMD5 md5:(NSString *)md5 name:(NSString *)name priority:(NSInteger)priority size:(NSInteger)size url:(NSString *)url files:(NSMutableArray *)files patches:(NSMutableDictionary *)patches
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
        NSString *path = [[FileUtil getGameRootPath:info] stringByAppendingPathComponent:[file fileName]];
        NSString *localMD5 = [FileUtil getFileMD5:path];
        if (![[file fileMD5] isEqualToString:localMD5]) {
            return FALSE;
        }
    }
    return TRUE;
}

- (GroupPatch*) getPatch:(NSString *)patchName
{
    return [groupPatches objectForKey:patchName];
}
@end