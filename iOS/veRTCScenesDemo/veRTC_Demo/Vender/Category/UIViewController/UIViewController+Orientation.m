//
//  UIViewController+Orientation.m
//  quickstart
//
//  Created by  on 2021/3/24.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "UIViewController+Orientation.h"
#import "AppDelegate.h"

@implementation UIViewController (Orientation)

- (void)addOrientationNotice {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onDeviceOrientationDidChange)
                                                 name:UIApplicationDidChangeStatusBarOrientationNotification
                                                   object:nil];
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
}

- (void)setAllowAutoRotate:(BOOL)isRotate {
    AppDelegate *delegate = (AppDelegate*)[UIApplication sharedApplication].delegate;
    delegate.allowAutoRotate = isRotate;
}

- (void)onDeviceOrientationDidChange {
    BOOL isLandscape = NO;
    UIInterfaceOrientation interfaceOrientation = [[UIApplication sharedApplication] statusBarOrientation];
    switch (interfaceOrientation) {
        
        case UIInterfaceOrientationUnknown:
            break;
        
        case UIInterfaceOrientationPortrait:
            break;
        
        case UIInterfaceOrientationPortraitUpsideDown:
            break;
        
        case UIInterfaceOrientationLandscapeLeft:
            isLandscape = YES;
            break;
        
        case UIInterfaceOrientationLandscapeRight:
            isLandscape = YES;
            break;
    
        default:
            break;
    }
    [self orientationDidChang:isLandscape];
}

- (void)orientationDidChang:(BOOL)isLandscape {
    //在 UIViewController 重写
    //Rewrite in UIViewController
}

- (void)setDeviceInterfaceOrientation:(UIDeviceOrientation)orientation {
    if ([[UIDevice currentDevice] respondsToSelector:@selector(setOrientation:)]) {
        [[UIDevice currentDevice] setValue:[NSNumber numberWithInteger:orientation] forKey:@"orientation"];
    }
}

@end
