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

#define FileHashDefaultChunkSizeForReadingData 1024*8

@implementation FileUtil

+ (NSString*) getCocosRuntimeRootPath
{
    return [ChannelConfig getCocosRuntimeRootPath];
}

+ (NSString*) getGamesPath
{
    return [[FileUtil getCocosRuntimeRootPath] stringByAppendingString: @"Games"];
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
    return [[[FileUtil getGameRootPath:info] stringByAppendingPathComponent:@"group"] stringByAppendingPathComponent:@"boot.cpk"];
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
    return (__bridge_transfer NSString *)FileMD5HashCreateWithPath((__bridge CFStringRef)path, FileHashDefaultChunkSizeForReadingData);
}

+ (NSString*) getConfigFileName
{
    return configFileName;
}

CFStringRef FileMD5HashCreateWithPath(CFStringRef filePath,size_t chunkSizeForReadingData) {
    // Declare needed variables
    CFStringRef result = NULL;
    CFReadStreamRef readStream = NULL;
    // Get the file URL
    CFURLRef fileURL =
    CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                                  (CFStringRef)filePath,
                                  kCFURLPOSIXPathStyle,
                                  (Boolean)false);
    if (!fileURL) goto done;
    // Create and open the read stream
    readStream = CFReadStreamCreateWithFile(kCFAllocatorDefault,
                                            (CFURLRef)fileURL);

    if (!readStream) goto done;
    bool didSucceed = (bool)CFReadStreamOpen(readStream);
    if (!didSucceed) goto done;
    // Initialize the hash object
    CC_MD5_CTX hashObject;
    
    CC_MD5_Init(&hashObject);
    
    // Make sure chunkSizeForReadingData is valid
    if (!chunkSizeForReadingData) {
        chunkSizeForReadingData = FileHashDefaultChunkSizeForReadingData;
    }
    
    // Feed the data to the hash object
    bool hasMoreData = true;
    
    while (hasMoreData) {
        uint8_t buffer[chunkSizeForReadingData];
        CFIndex readBytesCount = CFReadStreamRead(readStream,(UInt8 *)buffer,(CFIndex)sizeof(buffer));
        if (readBytesCount == -1) break;
        if (readBytesCount == 0) {
            hasMoreData = false;
            continue;
        }
        
        CC_MD5_Update(&hashObject,(const void *)buffer,(CC_LONG)readBytesCount);
    }
    
    // Check if the read operation succeeded
    didSucceed = !hasMoreData;
    
    // Compute the hash digest
    unsigned char digest[CC_MD5_DIGEST_LENGTH];
    
    CC_MD5_Final(digest, &hashObject);
    
    // Abort if the read operation failed
    if (!didSucceed) goto done;
    
    // Compute the string result
    char hash[2 * sizeof(digest) + 1];
    for (size_t i = 0; i < sizeof(digest); ++i) {
        snprintf(hash + (2 * i), 3, "%02x", (int)(digest[i]));
    }
    
    result = CFStringCreateWithCString(kCFAllocatorDefault,(const char *)hash,kCFStringEncodingUTF8);
    
done:
    if (readStream) {
        CFReadStreamClose(readStream);
        CFRelease(readStream);
    }

    if (fileURL) {
        CFRelease(fileURL);
    }
    return result;
}
@end