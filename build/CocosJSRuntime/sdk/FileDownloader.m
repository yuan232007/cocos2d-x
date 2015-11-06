//
//  FileDownload.m
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "FileDownloader.h"

@implementation FileDownloader

-(FileDownloader*) initWithURL:(NSURL *)url delegate:(id<FileDownloadDelegate>)delegate
{
    if (self = [super init]) {
        requestURL = url;
        fileDownloadDelegate = delegate;
    }
    return self;
}

-(void) startDownload
{
    NSLog(@"===> FileDownload startDownload");
    [fileDownloadDelegate onDownloadStart];
    [[[self getCurrentSession] downloadTaskWithRequest:[NSURLRequest requestWithURL:requestURL]] resume];
}

-(NSURLSession*) getCurrentSession
{
    dispatch_once_t predicate = 0;
    __block NSURLSession *currentSession;
    // 使用 dispatch_once 创建单例
    dispatch_once(&predicate, ^{
        NSURLSessionConfiguration* config =  [NSURLSessionConfiguration defaultSessionConfiguration];
        currentSession = [NSURLSession sessionWithConfiguration:config delegate:self delegateQueue: nil];
    });
    return currentSession;
}

/* Sent when a download task that has completed a download.  The delegate should
 * copy or move the file at the given location to a new location as it will be
 * removed when the delegate message returns. URLSession:task:didCompleteWithError: will
 * still be called.
 */
-(void) URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didFinishDownloadingToURL:(NSURL *)location
{
    NSLog(@"===> location: %@", location.path);
    NSString *movedPath = [fileDownloadDelegate onTempDownloaded:location.path];
    if (movedPath != nil) {
        [fileDownloadDelegate onDownloadSuccess:movedPath];
    } else {
        [fileDownloadDelegate onDownloadFailed];
    }
}

-(void) URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didWriteData:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite
{
    // 下载过程中会回调，可以用于监听下载进度
    double written = (double) totalBytesWritten;
    double total = (double) totalBytesExpectedToWrite;
    double progress = written / total;
    [fileDownloadDelegate onDownloadProgress:progress];
}

/* Sent when a download has been resumed. If a download failed with an
 * error, the -userInfo dictionary of the error will contain an
 * NSURLSessionDownloadTaskResumeData key, whose value is the resume
 * data.
 */
-(void) URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didResumeAtOffset:(int64_t)fileOffset expectedTotalBytes:(int64_t)expectedTotalBytes
{
    // 下载偏移，主要用于暂停续传
    NSLog(@"download pause and resume");
}

/**
 * 无论是否下载成功都会回调
 */
-(void) URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didCompleteWithError:(NSError *)error
{
    if (error != nil) {
        [fileDownloadDelegate onDownloadFailed];
    }
}

@end
