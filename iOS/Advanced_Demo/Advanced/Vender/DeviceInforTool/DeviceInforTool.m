//
//  DeviceInforTool.m
//  quickstart
//

#import "DeviceInforTool.h"

@implementation DeviceInforTool

#pragma mark - Publish Action

+ (BOOL)isIpad {
    NSString *deviceType = [UIDevice currentDevice].model;
    if ([deviceType isEqualToString:@"iPhone"]) {
        // iPhone
        return NO;
    } else if ([deviceType isEqualToString:@"iPod touch"]) {
        // iPod Touch
        return NO;
    } else if ([deviceType isEqualToString:@"iPad"]) {
        // iPad
        return YES;
    }
    return NO;
}

+ (CGFloat)getStatusBarHight {
    float statusBarHeight = 0;
    if (@available(iOS 13.0, *)) {
        UIStatusBarManager *statusBarManager = [UIApplication sharedApplication].windows.firstObject.windowScene.statusBarManager;
        statusBarHeight = statusBarManager.statusBarFrame.size.height;
    } else {
        statusBarHeight = [UIApplication sharedApplication].statusBarFrame.size.height;
    }
    return statusBarHeight;
}

+ (CGFloat)getVirtualHomeHeight {
    CGFloat virtualHomeHeight = 0;
    if (@available(iOS 11.0, *)) {
        UIWindow *keyWindow = [UIApplication sharedApplication].keyWindow;
        virtualHomeHeight = keyWindow.safeAreaInsets.bottom;
    }
    return virtualHomeHeight;
}

+ (UIEdgeInsets)getSafeAreaInsets{
    UIEdgeInsets safeAreaInsets = UIEdgeInsetsZero;
    if (@available(iOS 11.0, *)) {
        UIWindow *keyWindow = [UIApplication sharedApplication].keyWindow;
        safeAreaInsets = keyWindow.safeAreaInsets;
    }
    return safeAreaInsets;
}

+ (UIViewController *)topViewController {
    UIViewController *resultVC;
    resultVC = [self _topViewController:[[UIApplication sharedApplication].keyWindow rootViewController]];
    while (resultVC.presentedViewController) {
        resultVC = [self _topViewController:resultVC.presentedViewController];
    }
    if ([resultVC isKindOfClass:[UIAlertController class]]) {
        resultVC = [self _topViewController:[[UIApplication sharedApplication].keyWindow rootViewController]];
    }
    return resultVC;
}

+ (UIViewController *)_topViewController:(UIViewController *)vc {
    if ([vc isKindOfClass:[UINavigationController class]]) {
        return [self _topViewController:[(UINavigationController *)vc topViewController]];
    } else if ([vc isKindOfClass:[UITabBarController class]]) {
        return [self _topViewController:[(UITabBarController *)vc selectedViewController]];
    } else {
        return vc;
    }
    return nil;
}

@end
