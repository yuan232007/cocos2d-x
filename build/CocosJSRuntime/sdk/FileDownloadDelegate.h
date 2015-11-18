//
//  FileDownloadDelegate.h
//  CocosJSRuntime
//
//  Created by Rye on 10/28/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FileDownloadDelegate

/**
 * 下载开始前
 */
- (void) onDownloadStart;

/**
 * 下载进度通知
 */
- (void) onDownloadProgress: (long) progress max:(long)max;

/**
 * 下载成功, 参数为另存之后的文件地址
 */
- (void) onDownloadSuccess: (NSString*) path;

/**
 * 下载失败
 */
- (void) onDownloadFailed;

/**
 * 下载取消
 */
- (void) onDownloadCancel;

/**
 * 重试下载
 */
- (void) onDownloadRetry;
@end
