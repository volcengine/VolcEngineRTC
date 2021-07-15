//
//  UIViewController+Orientation.h
//  quickstart
//
//  Created by  on 2021/3/24.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIViewController (Orientation)

- (void)setDeviceInterfaceOrientation:(UIDeviceOrientation)orientation;

- (void)addOrientationNotice;

- (void)orientationDidChang:(BOOL)isLandscape;

- (void)setAllowAutoRotate:(BOOL)isRotate;

@end

NS_ASSUME_NONNULL_END
