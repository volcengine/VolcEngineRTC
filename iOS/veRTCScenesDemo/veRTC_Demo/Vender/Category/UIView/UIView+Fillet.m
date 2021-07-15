//
//  UIView+Fillet.m
//  veRTC_Demo
//
//  Created by  on 2021/4/9.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "UIView+Fillet.h"

@implementation UIView (Fillet)

- (void)filletWithRadius:(CGFloat)radius corner:(FilletStatus)corner {
    UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:self.bounds byRoundingCorners:corner cornerRadii:CGSizeMake(radius, radius)];
    CAShapeLayer *maskLayer = [[CAShapeLayer alloc] init];
    maskLayer.frame = self.bounds;
    maskLayer.path = path.CGPath;
    self.layer.mask = maskLayer;
}

- (void)removeAllAutoLayout {
    [self removeConstraints:self.constraints];
    for (NSLayoutConstraint *constraint in self.superview.constraints) {
        if ([constraint.firstItem isEqual:self]) {
            [self.superview removeConstraint:constraint];
        }
    }
}


@end
