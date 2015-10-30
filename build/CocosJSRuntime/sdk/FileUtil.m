//
//  FileUtil.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "FileUtil.h"
#import "ChannelConfig.h"
#import <CommonCrypto/CommonDigest.h>

@implementation FileUtil

+ (NSString*) getCocosRuntimeRootPath
{
    return [ChannelConfig getCocosRuntimeRootPath];
}

+ (NSString*) getGamesPath
{
    return [[FileUtil getCocosRuntimeRootPath] stringByAppendingString: @"/Games"];
}

+ (NSString*) getRemoteConfigPath:(GameInfo *)info
{
    return [[[[[FileUtil getGamesPath] stringByAppendingString:@"/"]
              stringByAppendingString:remoteConfigFileNamePrefix]
             stringByAppendingString:@"."]
            stringByAppendingString:[info gameKey]];
}

+ (NSString*) getGameRootPath:(GameInfo *)info
{
    return [[[FileUtil getGamesPath] stringByAppendingString:@"/"] stringByAppendingString: [info gameKey]];
}

+ (NSString*) getLocalConfigPath:(GameInfo *)info
{
    return [[[FileUtil getGameRootPath:info] stringByAppendingString:@"/"] stringByAppendingString:configFileName];
}

+ (NSString*) getLocalManifestPath:(GameInfo *)info :(GameConfig *)config
{
    return [[[FileUtil getGameRootPath:info] stringByAppendingString:@"/"] stringByAppendingString: [config manifestName]];
}

+ (NSString*) getLocalProjectPath:(GameInfo *)info :(GameConfig *)config
{
    return [[[FileUtil getGameRootPath:info] stringByAppendingString:@"/"] stringByAppendingString:[config projectName]];
}

+ (NSString*) getLocalEntryPath:(GameInfo *)info :(GameConfig *)config
{
    return [[[FileUtil getGameRootPath:info] stringByAppendingString:@"/"] stringByAppendingString:[config entryName]];
}

+ (NSString*) getLocalGameGroupRootPath:(GameInfo *)info
{
    return [[FileUtil getGameRootPath:info] stringByAppendingString:@"/group"];
}

+ (NSString*) getLocalGroupPath:(GameInfo *)info group:(ResGroup *)group
{
    return [[[FileUtil getGameRootPath:info] stringByAppendingString:@"/"] stringByAppendingString:[group groupURL]];
}

+ (NSString*) getLocalBootGroupPath:(GameInfo *)info group:(GameConfig *)config
{
    return [[[FileUtil getGameRootPath:info] stringByAppendingString:@"/"] stringByAppendingString:@"boot.cpk"];
}

+ (void) ensureDirectory:(NSString *)path
{
    NSError* error;
    if (![[NSFileManager defaultManager] createDirectoryAtPath:path withIntermediateDirectories: TRUE attributes: Nil error: &error]) {
        @throw error;
    }
}

+ (NSString*) getParentDirectory:(NSString *)path
{
    return [path stringByDeletingLastPathComponent];
}

+ (NSString*) getBaseName:(NSString *)path
{
    return [path lastPathComponent];
}

+ (BOOL) fileExists:(NSString *)path
{
    return [[NSFileManager defaultManager] fileExistsAtPath:path];
}

+ (id) readJsonFromFile:(NSString *)path
{
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSData *data = [fileManager contentsAtPath: path];
    return [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
}

+ (void) writeJsonToFile:(NSJSONSerialization *)json
{
    
}

+ (void) moveFileFrom:(NSString *)fromPath to:(NSString*)toPath overwrite:(BOOL)overwrite
{
    NSError *error;
    [FileUtil ensureDirectory: [FileUtil getParentDirectory:toPath]];
    BOOL ret = false;
    if (overwrite) {
        if ([FileUtil fileExists:toPath]){
            ret = [[NSFileManager defaultManager] removeItemAtPath:toPath error:&error];
        }
        ret = [[NSFileManager defaultManager] moveItemAtPath:fromPath toPath:toPath error:&error];
    } else {
        ret = [[NSFileManager defaultManager] moveItemAtPath:fromPath toPath:toPath error:&error];
    }
    
    if (!ret) {
        @throw [[NSException alloc] init];
    }
}

+ (NSString*) getFileMD5:(NSString *)path
{
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSData *data = [fileManager contentsAtPath: path];
    const char* original_str = (const char *)[data bytes];
    unsigned char digist[CC_MD5_DIGEST_LENGTH]; //CC_MD5_DIGEST_LENGTH = 16
    CC_MD5(original_str, (uint)strlen(original_str), digist);
    NSMutableString* outPutStr = [NSMutableString stringWithCapacity:10];
    for(int  i =0; i<CC_MD5_DIGEST_LENGTH;i++){
        [outPutStr appendFormat:@"%02x",digist[i]];//小写x表示输出的是小写MD5，大写X表示输出的是大写MD5
    }
    return [outPutStr lowercaseString];
}

+ (NSString*) getConfigFileName
{
    return configFileName;
}

@end