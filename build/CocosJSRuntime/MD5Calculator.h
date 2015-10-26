//
//  MD5Calculator.h
//  iOSTest
//
//  Created by Rye on 10/20/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>

@interface NSString (MD5Calculator)
- (NSString *)md5;
@end

@interface NSData (MD5Calculator)
- (NSString*)md5;
@end

//@interface MD5Calculator : NSObject 
//+ (NSString*) getFileMD5WithPath: (NSString*)path;
//@end