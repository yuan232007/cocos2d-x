//
//  ZipHelper.h
//  CocosJSRuntime
//
//  Created by WenhaiLin on 15/10/19.
//
#ifndef _RUNTIME_ZIP_HELPER_H
#define _RUNTIME_ZIP_HELPER_H

#import <Foundation/Foundation.h>

@protocol ZipArchiveDelegate;

@interface ZipHelper: NSObject

// Unzip
+ (BOOL)unzipFileAtPath:(NSString *)zipFilePath
          toDestination:(NSString *)destination;
/*
 * zipFilePath: 要处理的压缩包文件全路径
 * destination: 解压路径
 * progressHandler: 解压过程回调，可为nil
 *     entry：当前正解压的文件
 *     entryNumber: 已解压的文件数
 *     total: 压缩包内文件总数
 * completionHandler: 解压结束(解压过程出差会导致解压提前结束)回调，可为nil
 *     zipFilePath: 解压成功 --> 压缩包路径， 解压失败 --> nil
 *     succeeded:   解压成功 --> YES，      解压失败 --> NO
 *     error:       解压成功 --> nil，      解压失败 --> 错误信息
 */
+ (BOOL)unzipFileAtPath:(NSString *)zipFilePath
          toDestination:(NSString *)destination
        progressHandler:(void (^)(NSString *entry, long entryNumber, long total))progressHandler
      completionHandler:(void (^)(NSString *zipFilePath, BOOL succeeded, NSError *error))completionHandler;

// Zip
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL open;
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL close;

@end

#endif /* _RUNTIME_ZIP_HELPER_H */
