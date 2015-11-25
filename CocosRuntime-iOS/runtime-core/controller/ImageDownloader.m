//
//  ImageDownloader.m
//  CocosJSRuntime
//
//  Created by Rye on 11/20/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import "ImageDownloader.h"
#import "FileUtil.h"
#import "FileDownloader.h"

#define MAX_DOWNLOAD_COUNT 30

static NSMutableArray *downloadInfos;
static NSInteger currentDownloadIndex;

@implementation ImageDownloader

@synthesize currentDownloadInfo;

- (ImageDownloader*) initWith:(DownloadInfo *)info callback:(RTImageCallback)callback
{
    if (self = [super init]) {
        currentDownloadInfo = info;
        imageCallback = callback;
    }
    return self;
}

- (void) start
{
    if (nil == currentDownloadInfo.config) {
        NSLog(@"ImageDownloader config is NULL");
    }
    
    NSMutableDictionary *configJson = [NSJSONSerialization JSONObjectWithData:[currentDownloadInfo.config dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:nil];
    NSURL *url = [NSURL URLWithString:[configJson objectForKey:@"url"]];
    NSString *option = [configJson objectForKey:@"option"];
    NSInteger width = 0, height = 0;
    if (![@"null" isEqualToString:option]) {
        NSDictionary *optionJson = [NSJSONSerialization JSONObjectWithData:[option dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:nil];
        width = [[optionJson objectForKey:@"width"] integerValue];
        height = [[optionJson objectForKey:@"height"] integerValue];
    }
    NSString *pictureName = [configJson objectForKey:@"picName"];
    NSString *pictureDir = [configJson objectForKey:[[FileUtil getGamesPath] stringByAppendingPathComponent:@"game_icons"]];
    NSString *pictruePath = [pictureDir stringByAppendingPathComponent:pictureName];
    NSLog(@"===> ImageDownloader icon path is %@", pictruePath);
    
    [configJson setValue:pictruePath forKey:@"picPath"];
    [configJson setValue:[NSNumber numberWithBool:FALSE] forKey:@"isSuccess"];
    
    [FileUtil ensureDirectory:pictureDir];
    
    if ([FileUtil fileExists:pictruePath]) {
        NSLog(@"===> Icon exists, path is %@", pictruePath);
        [configJson setValue:[NSNumber numberWithBool:TRUE] forKey:@"isSuccess"];
        // todo 返回数据
        return;
    }
    
    FileDownloader *fileDownloader = [[FileDownloader alloc] initWithURL:url targetPath:pictruePath delegate:[[ImageDownloadDelegateImpl alloc] init]];
    [fileDownloader start];
}


- (void) notifyResult: (NSString*)result
{
    if (nil != imageCallback) {
        imageCallback(currentDownloadInfo.config, currentDownloadInfo.extension);
    }
}

- (RTImageCallback) getImageCallback
{
    return imageCallback;
}

+ (void) continueDownloading: (RTImageCallback)callback
{
    if (currentDownloadIndex - 1 > 0) {
        currentDownloadIndex--;
    }
    
    while (currentDownloadIndex < MAX_DOWNLOAD_COUNT && downloadInfos.count != 0) {
        [[[ImageDownloader alloc] initWith: [downloadInfos objectAtIndex:0] callback:callback] start];
        [downloadInfos removeObjectAtIndex:0];
        currentDownloadIndex++;
    }
}

+ (void) downloadImageFile: (NSString*)json extesion:(long)ext callback:(RTImageCallback)callback;
{
    DownloadInfo* info = [[DownloadInfo alloc] initWith:json extension:ext];
    if (currentDownloadIndex < MAX_DOWNLOAD_COUNT) {
        [[[ImageDownloader alloc] initWith:info callback:callback] start];
        currentDownloadIndex++;
    } else {
        [downloadInfos addObject:info];
    }
}


@end

@implementation ImageDownloadDelegateImpl

- (ImageDownloadDelegateImpl*) initWith: (ImageDownloader*)downloader config:(NSMutableDictionary*) config scaledToSize:(CGSize)size imageFormat:(NSString *)format
{
    if (self = [super init]) {
        imageDownloader = downloader;
        configDict = config;
        targetSize = size;
        imageFormat = format;
    }
    return self;
}

- (void) onDownloadSuccess: (NSString*) path
{
    [ImageDownloader continueDownloading: [imageDownloader getImageCallback]];
    UIImage *image = [UIImage imageWithContentsOfFile:path];
    if (0 != targetSize.width || 0 != targetSize.height) {
        UIGraphicsBeginImageContext(targetSize);
        [image drawInRect:CGRectMake(0, 0, targetSize.width, targetSize.height)];
        UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
        NSData *data = nil;
        if ([@".png" isEqualToString:imageFormat]) {
            data = UIImagePNGRepresentation(newImage);
        } else {
            data = UIImageJPEGRepresentation(newImage, 0.9f);
        }
        [data writeToFile:path atomically:FALSE];
    }
    NSData *configData = [NSJSONSerialization dataWithJSONObject:configDict options:NSJSONWritingPrettyPrinted error:nil];
    NSString *result = [[NSString alloc] initWithData:configData encoding:NSUTF8StringEncoding];
    [imageDownloader notifyResult:result];
}

- (void) onDownloadFailed
{
    [ImageDownloader continueDownloading: [imageDownloader getImageCallback]];
    NSData *configData = [NSJSONSerialization dataWithJSONObject:configDict options:NSJSONWritingPrettyPrinted error:nil];
    NSString *result = [[NSString alloc] initWithData:configData encoding:NSUTF8StringEncoding];
    [imageDownloader notifyResult:result];
}

- (void) onDownloadCancel
{
    [ImageDownloader continueDownloading: [imageDownloader getImageCallback]];
}

@end

