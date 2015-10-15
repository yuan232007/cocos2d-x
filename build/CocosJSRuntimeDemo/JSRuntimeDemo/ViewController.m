//
//  ViewController.m
//  DylibDemo
//
//  Created by kinglong huang on 9/29/15.
//  Copyright (c) 2015 kinglong huang. All rights reserved.
//

#import "ViewController.h"
#import "Main.h"
#import <dlfcn.h>

#import "MttGameEngineProtocol.h"
#import "MttGameEngineFramework.h"


@interface ViewController ()

@property (nonatomic, strong) UILabel * copyrightLabel;

@end

@implementation ViewController

#pragma mark - LifeCycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    UIButton * btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setFrame:CGRectMake(10, 50, 160, 30)];
    [btn setBackgroundColor:[UIColor darkGrayColor]];
    [btn setTitle:@"Download and load" forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(downloadDylibAndRetriveTheCopyrightInfo) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
    
    
    self.copyrightLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 100, self.view.frame.size.width, 40)];
    [self.copyrightLabel setTextAlignment:NSTextAlignmentCenter];
    [self.copyrightLabel setBackgroundColor:[UIColor lightGrayColor]];
    [self.view addSubview:self.copyrightLabel];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Private

- (NSString *)docPath {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0]; // Get documents folder
    return documentsDirectory;
}

- (BOOL)dlopenLoadDylibWithPath:(NSString *)path
{
    void *libHandle = NULL;
    libHandle = dlopen([path cStringUsingEncoding:NSUTF8StringEncoding], RTLD_NOW);
    if (libHandle == NULL) {
        char *error = dlerror();
        printf("dlopen error: %s\n", error);
    } else {
        NSLog(@"dlopen load framework success.");
        return YES;
    }
    return NO;
}

#pragma mark - Dylib

- (void)downloadDylibAndRetriveTheCopyrightInfo {
    [self.copyrightLabel setText:@""];
    
    NSString * docPath = [self docPath];
    NSString * destPath = [docPath stringByAppendingPathComponent:@"DylibDemo"];
    
    //Don't use the cache
    if ([[NSFileManager defaultManager] fileExistsAtPath:destPath]) {
        [[NSFileManager defaultManager] removeItemAtPath:destPath error:nil];
    }
    
    //解压本地游戏资源
    NSString *resPath = [[NSBundle mainBundle] pathForResource:@"gameResources" ofType:@"zip"];
    if (resPath.length > 0) {
        NSString * resDestPath = [docPath stringByAppendingPathComponent:@"gameResources"];

        if ([[NSFileManager defaultManager] fileExistsAtPath:resDestPath]) {
            [[NSFileManager defaultManager] removeItemAtPath:resDestPath error:nil];
        }
        
        [Main unzipFileAtPath:resPath toDestination:resDestPath];
    }
    
    // 直接本地加载
    NSString *path = [[NSBundle mainBundle] pathForResource:@"CocosJSRuntime.dylib" ofType:@"zip"];
    
    if (path.length > 0) {
        [Main unzipFileAtPath:path toDestination:destPath];
        NSString *lipPath = [destPath stringByAppendingPathComponent:@"CocosJSRuntime.dylib"];
        [self updateCopyrightWithDyLibWithPath:lipPath];
        return;
    }
    
    
    /*
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSURLRequest * urlReq = [NSURLRequest requestWithURL:[NSURL URLWithString:@"http://klstudio.cn/CopyrightDylib.dylib.zip"]];
        NSURLResponse * response = nil;
        NSError * error = nil;
        NSData * result = [NSURLConnection sendSynchronousRequest:urlReq returningResponse:&response error:&error];
        if (!error) {
            NSString *dataPath = [docPath stringByAppendingPathComponent:@"CopyrightDylib.zip"];
            [result writeToFile:dataPath atomically:YES];
            [Main unzipFileAtPath:dataPath
                    toDestination:destPath];
            NSString *lipPath = [destPath stringByAppendingPathComponent:@"CopyrightDylib.dylib"];
            [self updateCopyrightWithDyLibWithPath:lipPath];
        }
    });
     */
}

- (void)updateCopyrightWithDyLibWithPath:(NSString *)libPath {
    if ([self dlopenLoadDylibWithPath:libPath]) {
        Class KLFactoryClass = NSClassFromString(@"MttGameEngineFactory");
        if (KLFactoryClass) {
            SEL selector = NSSelectorFromString(@"CreateGameRuntimeEngine");
            if ([[KLFactoryClass class] respondsToSelector:selector]) {
                UIView* rootView = [self view];
                id<MttGameEngineProtocol> object = [[KLFactoryClass class] performSelector:selector];
                
                dispatch_async(dispatch_get_main_queue(), ^{
                    [[MttGameEngineFramework sharedInstance] updateRuntimeEngine:object];
                    
                    [[MttGameEngineFramework sharedInstance] testEngineFunction:rootView];
                });
            }
            
        }
    }
}

@end
