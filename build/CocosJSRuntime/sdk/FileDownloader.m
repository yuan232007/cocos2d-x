//
//  FileDownload.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "FileDownloader.h"
#import "NetworkController.h"
#import "FileUtil.h"

@implementation FileDownloader

-(FileDownloader*) initWithURL:(NSURL *)url targetPath:(NSString*)path delegate:(id<FileDownloadDelegate>)delegate
{
    if (self = [super init]) {
        requestURL = url;
        targetPath = path;
        tempPath = [path stringByAppendingString:@".tmp"];
        fileDownloadDelegate = delegate;
        receivedSize = 0;
        totalSize = 0;
    }
    return self;
}

- (void) start
{
    NSLog(@"===> FileDownload startDownload");
    [fileDownloadDelegate onDownloadStart];
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:requestURL];
    
    if ([FileUtil fileExists:tempPath] && (receivedSize = [FileUtil getFileSize:tempPath]) > 0) {
        NSString *requestRange = [NSString stringWithFormat:@"bytes=%llu-", receivedSize];
        [request setValue:requestRange forHTTPHeaderField:@"Range"];
        
        NSLog(@"===> Broken-Point Continuely-Transfer %@ from %lld bytes", tempPath, receivedSize);
    } else {
        int fileDescriptor = open([tempPath UTF8String], O_CREAT | O_EXCL | O_RDWR, 0666);
        if (fileDescriptor > 0) {
            close(fileDescriptor);
        }
    }
    
    downloadTask = [[NetworkController getCurrentSession: self] dataTaskWithRequest:request];
    [downloadTask resume];
}

- (void) cancel
{
    if (downloadTask != nil) {
        [downloadTask cancel];
    }
}

- (void) URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
     didReceiveData:(NSData *)data
{
    NSHTTPURLResponse *response = (NSHTTPURLResponse*)dataTask.response;
    if (200 == response.statusCode) {
        totalSize = dataTask.countOfBytesExpectedToReceive;
    } else if (206 == response.statusCode) {
        NSString *contentRange = [response.allHeaderFields valueForKey:@"Content-Range"];
        if ([contentRange hasPrefix:@"bytes"]) {
            NSArray *bytes = [contentRange componentsSeparatedByCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@" -/"]];
            if (4 == [bytes count]) {
                totalSize = [[bytes objectAtIndex:3] longLongValue];
            }
        }
    } else if (416 == response.statusCode) {
        NSLog(@"===> Download 416 HTTP Status code Error");
        NSString *contentRange = [response.allHeaderFields valueForKey:@"Content-Range"];
        if ([contentRange hasPrefix:@"bytes"]) {
            NSArray *bytes = [contentRange componentsSeparatedByCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@" -/"]];
            if (3 == [bytes count]) {
                totalSize = [[bytes objectAtIndex:2] longLongValue];
                if (receivedSize == totalSize) {
                    // 下载完成
                    [self onTempFileDownloaded];
                } else {
                    // 出错
                    NSLog(@"===> Download 416 HTTP Status code Error, Delete temp file.");
                    [FileUtil removeFile:tempPath];
                    [fileDownloadDelegate onDownloadFailed];
                }
            }
        }
        return;
    } else {
        //其他情况还没发现
        return;
    }
    
    NSFileHandle *fileHandler = [NSFileHandle fileHandleForUpdatingAtPath:tempPath];
    [fileHandler seekToEndOfFile];
    [fileHandler writeData:data];
    [fileHandler closeFile];
    
    receivedSize += data.length;
    
    // 更新进度
    [fileDownloadDelegate onDownloadProgress:receivedSize max:totalSize];
}

/**
 * 无论是否下载成功都会回调
 */
- (void) URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didCompleteWithError:(NSError *)error
{
    if (error != nil) {
        [fileDownloadDelegate onDownloadFailed];
    } else {
        [self onTempFileDownloaded];
    }
}

/**
 * 断点下载完毕之后，移动临时文件到目标路径并删除临时文件
 */
- (void) onTempFileDownloaded
{
    if ([FileUtil moveFileFrom:tempPath to:targetPath overwrite:TRUE]) {
        [fileDownloadDelegate onDownloadSuccess:targetPath];
    } else {
        [FileUtil removeFile:tempPath];
        [fileDownloadDelegate onDownloadFailed];
    }
}

@end
