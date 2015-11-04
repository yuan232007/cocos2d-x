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
    
    UIButton * btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setFrame:CGRectMake(10, 50, 300, 50)];
    [btn setBackgroundColor:[UIColor darkGrayColor]];
    [btn setTitle:@"Unzip game resources and test" forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(unzipResourcesAndTest) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSString *)docPath {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0]; // Get documents folder
    return documentsDirectory;
}

- (void)unzipResourcesAndTest {
    NSString * docPath = [self docPath];
    NSString * destPath = [docPath stringByAppendingPathComponent:@"DylibDemo"];
    
    //Don't use the cache
    if ([[NSFileManager defaultManager] fileExistsAtPath:destPath]) {
        [[NSFileManager defaultManager] removeItemAtPath:destPath error:nil];
    }
    
    self.engineGame = [MttGameEngineFactory CreateGameRuntimeEngine];
    
    UIView* rootView = [self view];
    [[MttGameEngineFramework sharedInstance] updateRuntimeEngine:self.engineGame];
    [[MttGameEngineFramework sharedInstance] testEngineFunction:rootView];
}

@end
