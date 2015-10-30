//
//  ViewController.h
//  JSRuntimeTest
//
//  Created by cocos on 15/10/16.
//  Copyright © 2015年 cocos. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (strong, nonatomic) UIView *navigationView;

- (UIView*)getNavigationView;

- (void)testQuitEngine;
- (void)testPauseEngine;
- (void)testResumeEngine;

@end

