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
+ (BOOL)unzipFileAtPath:(NSString *)path
          toDestination:(NSString *)destination;

+ (BOOL)unzipFileAtPath:(NSString *)path
          toDestination:(NSString *)destination
              overwrite:(BOOL)overwrite
               password:(NSString *)password
                  error:(NSError *)error;

// Zip
+ (BOOL)createZipFileAtPath:(NSString *)path
           withFilesAtPaths:(NSArray *)paths;

+ (BOOL)createZipFileAtPath:(NSString *)path
    withContentsOfDirectory:(NSString *)directoryPath;

+ (BOOL)createZipFileAtPath:(NSString *)path
    withContentsOfDirectory:(NSString *)directoryPath
        keepParentDirectory:(BOOL)keepParentDirectory;

- (instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL open;
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL close;

@end

#endif /* _RUNTIME_ZIP_HELPER_H */
