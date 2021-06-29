//
//  AlertActionManager.m
//  quickstart

#import "AlertActionManager.h"
#import <UIKit/UIKit.h>

@implementation AlertActionManager

+ (AlertActionManager *)shareAlertActionManager {
    static dispatch_once_t onceToken;
    static AlertActionManager *alertActionManager;
    dispatch_once(&onceToken, ^{
        alertActionManager = [[AlertActionManager alloc] init];
    });
    return alertActionManager;
}

#pragma mark - Publish Action

- (void)showWithMessage:(NSString *)message {
    [self showWithMessage:message actions:nil];
}

- (void)showWithMessage:(NSString *)message actions:(NSArray<AlertActionModel *> *)actions {
    if (message.length <= 0) {
        return;
    }
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"" message:message preferredStyle:UIAlertControllerStyleAlert];
    for (int i = 0; i < actions.count; i++) {
        AlertActionModel *model = actions[i];
        UIAlertAction *alertAction = [UIAlertAction actionWithTitle:model.title style:UIAlertActionStyleDefault handler:^(UIAlertAction *_Nonnull action) {
            if (model.alertModelClickBlock) {
                model.alertModelClickBlock(action);
            }
        }];
        [alert addAction:alertAction];
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController *rootVC = [DeviceInforTool topViewController];
        [rootVC presentViewController:alert animated:YES completion:nil];
    });
}

@end
