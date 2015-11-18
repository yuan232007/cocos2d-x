//
//  FileDownload.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FileDownloadDelegate.h"

@interface FileDownloader : NSObject <NSURLSessionTaskDelegate>
{
    NSURL* requestURL;
    NSString *tempPath;
    NSString *targetPath;
    NSURLSessionDataTask *downloadTask;
    id<FileDownloadDelegate> fileDownloadDelegate;
    long long receivedSize;
    long long totalSize;
}

- (FileDownloader*) initWithURL: (NSURL*) url targetPath:(NSString*)path delegate: (id<FileDownloadDelegate>) delegate;

/**
 * 开始下载
 */
- (void) start;

/**
 * 取消下载
 */
- (void) cancel;

- (void) URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
    didReceiveData:(NSData *)data;

- (void) URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didCompleteWithError:(NSError *)error;

- (void) onTempFileDownloaded;
@end
