//
//  LoadingDelegate.h
//  CocosJSRuntime
//
//  Created by Rye on 10/27/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

#ifndef COCOS_RUNTIME_LOADING_DELEGATE_H
#define COCOS_RUNTIME_LOADING_DELEGATE_H

#import <Foundation/Foundation.h>

@protocol LoadingDelegate <NSObject>

- (void) onLoadingProgress:(NSInteger)progress :(bool) isFailed;
- (void) onPreRunGameCompleted;
@end

#endif