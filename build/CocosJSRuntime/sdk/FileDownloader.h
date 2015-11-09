//
//  FileDownload.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FileDownloadDelegate.h"

@interface FileDownloader : NSObject <NSURLSessionDownloadDelegate>
{
    NSURL* requestURL;
    NSURLSessionDownloadTask *downloadTask;
    id<FileDownloadDelegate> fileDownloadDelegate;
}

@property NSURLSessionDownloadTask *downloadTask;

- (FileDownloader*) initWithURL: (NSURL*) url delegate: (id<FileDownloadDelegate>) delegate;
-(void) startDownload;
-(NSURLSession*) getCurrentSession;
-(void) URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didFinishDownloadingToURL:(NSURL *)location;
-(void) URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didWriteData:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite;
-(void) URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didResumeAtOffset:(int64_t)fileOffset expectedTotalBytes:(int64_t)expectedTotalBytes;
-(void) URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didCompleteWithError:(NSError *)error;

@end
