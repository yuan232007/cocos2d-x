//
//  ImageDownloader.h
//  CocosJSRuntime
//
//  Created by Rye on 11/20/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "DownloadInfo.h"
#import "FileDownloadAdapter.h"

typedef void (^RTImageCallback)(NSString* json, long extension);

@interface ImageDownloader : NSObject
{
    DownloadInfo *currentDownloadInfo;
    RTImageCallback imageCallback;
}

@property DownloadInfo *currentDownloadInfo;

- (ImageDownloader*) initWith: (DownloadInfo*) info callback:(RTImageCallback)callback;
- (void) start;
- (void) notifyResult: (NSString*)result;
- (RTImageCallback) getImageCallback;

+ (void) continueDownloading: (RTImageCallback)callback;
+ (void) downloadImageFile: (NSString*)json extesion:(long)ext callback:(RTImageCallback)callback;
@end

@interface ImageDownloadDelegateImpl : FileDownloadAdapter
{
    ImageDownloader *imageDownloader;
    NSMutableDictionary *configDict;
    CGSize targetSize;
    NSString* imageFormat;
}

- (ImageDownloadDelegateImpl*) initWith: (ImageDownloader*)downloader config:(NSMutableDictionary*) config scaledToSize:(CGSize)size imageFormat:(NSString*)format;
- (void) onDownloadSuccess: (NSString*) path;
- (void) onDownloadFailed;
- (void) onDownloadCancel;
@end