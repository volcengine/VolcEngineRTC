//
//  UIView+Fillet.h
//  veRTC_Demo
//
//  Created by  on 2021/4/9.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, FilletStatus) {
    FilletStatusTopLeft = 1 << 0,
    FilletStatusTopRight = 1 << 1,
    FilletStatusBottomLeft = 1 << 0,
    FilletStatusBottomRight = 1 << 0,
};

NS_ASSUME_NONNULL_BEGIN

@interface UIView (Fillet)

- (void)filletWithRadius:(CGFloat)radius corner:(FilletStatus)corner;

- (void)removeAllAutoLayout;

@end

NS_ASSUME_NONNULL_END
