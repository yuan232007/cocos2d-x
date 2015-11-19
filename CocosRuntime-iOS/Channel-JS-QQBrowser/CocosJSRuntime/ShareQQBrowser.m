#import "ShareQQBrowser.h"
#import "Wrapper.h"
#import "ShareWrapper.h"
#import "PluginHelper.h"
#import "UserQQBrowser.h"
#import "MttGameEngine.h"

#define OUTPUT_LOG(...)     [PluginHelper logDebug:__VA_ARGS__]

@implementation ShareQQBrowser

- (id)init {
    if ([super init]) {
        [self configDeveloperInfo:[PluginHelper getParamsInfo]];
    }
    return self;
}

- (void)configDeveloperInfo:(NSMutableDictionary *)cpInfo {
    OUTPUT_LOG(@"config params:%@",cpInfo);
}

- (void)share:(NSMutableDictionary *)shareInfo {
    OUTPUT_LOG(@"share:%@ invoked!\n", shareInfo);
    UserQQBrowser* userInstance = [UserQQBrowser getInstance];
    NSString *errorMsg = nil;
    int retCode = SHARERESULT_FAIL;
    
    do {
        if (userInstance == nil) {
            errorMsg = @"UserQQBrowser didn't init yet!";
            break;
        }
        
        NSString* titleUrl = [shareInfo objectForKey:@"titleUrl"];
        if (titleUrl == nil) {
            errorMsg = @"titleUrl is nil!";
            break;
        }
        
        NSString* title = [shareInfo objectForKey:@"title"];
        if (title == nil) {
            errorMsg = @"title is nil!";
            break;
        }
        
        NSString* description = [shareInfo objectForKey:@"description"];
        if (description == nil) {
            errorMsg = @"description is nil!";
            break;
        }
        
        NSString* imageUrl = [shareInfo objectForKey:@"imageUrl"];
        if (imageUrl == nil) {
            errorMsg = @"imageUrl is nil!";
            break;
        }
        
        NSString* imageTitle = [shareInfo objectForKey:@"imageTitle"];
        if (imageTitle == nil) {
            errorMsg = @"imageTitle is nil!";
            break;
        }
        
        NSString* text = [shareInfo objectForKey:@"text"];
        if (text == nil) {
            errorMsg = @"";
            break;
        }
        
        NSMutableDictionary* shareInfoForX5 = [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                                               titleUrl, @"url",
                                               title, @"title",
                                               description, @"description",
                                               imageUrl, @"img_url",
                                               imageTitle, @"img_title",
                                               text, @"cus_txt",
                                               nil];
        
        [[MttGameEngine getEngineDelegate] x5GamePlayer_share:shareInfoForX5 callback:^(NSDictionary *dict) {
            int retCode = [[dict objectForKey:@"result"] intValue];
            switch (retCode) {
                case 0:
                    [ShareWrapper onShareResult:self retCode:SHARERESULT_SUCCESS retMsg:[UserQQBrowser dictToJSONString:dict]];
                    break;
                case -1:
                    [ShareWrapper onShareResult:self retCode:SHARERESULT_CANCEL retMsg:[UserQQBrowser dictToJSONString:dict]];
                    break;
                default:
                    [ShareWrapper onShareResult:self retCode:SHARERESULT_FAIL retMsg:[UserQQBrowser dictToJSONString:dict]];
                    break;
            }
        }];
    } while (false);
    
    if (errorMsg) {
        NSString* msg = [UserQQBrowser dictToJSONString:
                         [NSDictionary dictionaryWithObjectsAndKeys:errorMsg,@"error", nil]];
        [ShareWrapper onShareResult:self retCode:retCode retMsg:msg];
    }
}

- (NSString *)getSDKVersion {
	return kSDKVersion;
}

- (NSString *)getPluginVersion {
	return kPluginVersion;
}

@end
