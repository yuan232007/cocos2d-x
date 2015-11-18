//
//  FileDownloadAdapter.h
//  CocosJSRuntime
//
//  Created by Rye on 10/29/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FileDownloadDelegate.h"

@interface FileDownloadAdapter : NSObject <FileDownloadDelegate>
- (void) onDownloadStart;
- (void) onDownloadProgress: (long) progress max:(long)max;
- (void) onDownloadSuccess: (NSString*) path;
- (void) onDownloadFailed;
- (void) onDownloadCancel;
- (void) onDownloadRetry;
@end
