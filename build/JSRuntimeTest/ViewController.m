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
    
    //解压本地游戏资源
    NSString *resPath = [[NSBundle mainBundle] pathForResource:@"gameResources" ofType:@"zip"];
    if (resPath.length > 0) {
        NSString * resDestPath = [docPath stringByAppendingPathComponent:@"gameResources"];
        
        if ([[NSFileManager defaultManager] fileExistsAtPath:resDestPath]) {
            [[NSFileManager defaultManager] removeItemAtPath:resDestPath error:nil];
        }
        
        [ZipHelper unzipFileAtPath:resPath toDestination:resDestPath];
    }
    
    
    self.engineGame = [MttGameEngineFactory CreateGameRuntimeEngine];
    
    UIView* rootView = [self view];
    [[MttGameEngineFramework sharedInstance] updateRuntimeEngine:self.engineGame];
    [[MttGameEngineFramework sharedInstance] testEngineFunction:rootView];
    
    [rootView addSubview:[self getNavigationView]];
}

- (UIView*)getNavigationView
{
    CGSize screenSize = [UIScreen mainScreen].bounds.size;
    
    UIView* navigationView = [[UIView alloc] initWithFrame:CGRectMake(screenSize.width - 110, 100, 100, 200)];
    
    UIButton * quitButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [quitButton setFrame:CGRectMake(0, 0, 100, 30)];
    [quitButton setBackgroundColor:[UIColor darkGrayColor]];
    [quitButton setTitle:@"quit" forState:UIControlStateNormal];
    [quitButton addTarget:self action:@selector(testQuitEngine) forControlEvents:UIControlEventTouchUpInside];
    [navigationView addSubview:quitButton];
    
    UIButton * pauseButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [pauseButton setFrame:CGRectMake(0, 40, 100, 30)];
    [pauseButton setBackgroundColor:[UIColor darkGrayColor]];
    [pauseButton setTitle:@"pause" forState:UIControlStateNormal];
    [pauseButton addTarget:self action:@selector(testPauseEngine) forControlEvents:UIControlEventTouchUpInside];
    [navigationView addSubview:pauseButton];
    
    UIButton * resumeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [resumeButton setFrame:CGRectMake(0, 80, 100, 30)];
    [resumeButton setBackgroundColor:[UIColor darkGrayColor]];
    [resumeButton setTitle:@"resume" forState:UIControlStateNormal];
    [resumeButton addTarget:self action:@selector(testResumeEngine) forControlEvents:UIControlEventTouchUpInside];
    [navigationView addSubview:resumeButton];
    
    self.navigationView = navigationView;
    
    return navigationView;
}

- (void)testQuitEngine
{
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onStop)]) {
        [self.engineGame game_engine_onStop];
        
        if (self.navigationView != nil) {
            [self.navigationView removeFromSuperview];
            self.navigationView = nil;
        }
    }
}

- (void)testPauseEngine
{
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onPause)]) {
        [self.engineGame game_engine_onPause];
    }
}

- (void)testResumeEngine
{
    if (self.engineGame && [self.engineGame respondsToSelector:@selector(game_engine_onResume)]) {
        [self.engineGame game_engine_onResume];
    }
}

@end
