#import "ViewController.h"
#import "ZipHelper.h"
#import <dlfcn.h>

#import "MttGameEngineProtocol.h"
#import "MttGameEngineFramework.h"
#import "MttGameEngineFactory.h"


@interface ViewController ()

@property (nonatomic, strong) id<MttGameEngineProtocol>   engineGame;

@end

@implementation ViewController

#pragma mark - LifeCycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    
    UIButton * btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setFrame:CGRectMake(20, 50, screenSize.width - 40, 50)];
    [btn setBackgroundColor:[UIColor darkGrayColor]];
    [btn setTitle:@"测试 带头大哥" forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(test_dtdg) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
    
    UIButton * btn2 = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn2 setFrame:CGRectMake(20, 110, screenSize.width - 40, 50)];
    [btn2 setBackgroundColor:[UIColor darkGrayColor]];
    [btn2 setTitle:@"测试 天天挂传奇" forState:UIControlStateNormal];
    [btn2 addTarget:self action:@selector(test_ttgcq) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn2];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (NSString *)docPath {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    // Get documents folder
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return documentsDirectory;
}

- (void)test_dtdg {
    [self unzipResourcesAndTest:@"442290542"];
}

- (void)test_ttgcq {
    [self unzipResourcesAndTest:@"442290958"];
}

- (void)unzipResourcesAndTest:(NSString*)gameKey
{
    NSString * docPath = [self docPath];
    NSString * destPath = [docPath stringByAppendingPathComponent:@"DylibDemo"];
    
    //Don't use the cache
    if ([[NSFileManager defaultManager] fileExistsAtPath:destPath]) {
        [[NSFileManager defaultManager] removeItemAtPath:destPath error:nil];
    }
    
    self.engineGame = [MttGameEngineFactory CreateGameRuntimeEngine];
    
    UIView* rootView = [self view];
    [[MttGameEngineFramework sharedInstance] setTestGameKey:gameKey];
    [[MttGameEngineFramework sharedInstance] updateRuntimeEngine:self.engineGame];
    [[MttGameEngineFramework sharedInstance] testEngineFunction:rootView];
}

@end
