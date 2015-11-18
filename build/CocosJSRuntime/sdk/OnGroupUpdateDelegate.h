//
//  onGroupUpdateDelegate.h
//  CocosJSRuntime
//
//  Created by Rye on 11/5/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol OnGroupUpdateDelegate
- (void) onProgressOfDownload: (long) written total:(long) total;
- (void) onSuccessOfDownload: (long) total;
- (void) onFailureOfDownload: (NSString*) errorMsg;
- (void) onSuccessOfUnzip: (long)total;
- (void) onFailureOfUnzip: (NSString*) errorMsg;
- (void) onProgressOfUnzip: (float) percent;
@end
