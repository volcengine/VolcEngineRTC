//
//  NSView+Snippet.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import "NSView+Snippet.h"

@implementation NSView (Snippet)

- (void)setBackgroundColor:(NSColor *)color {
    if (!self.wantsLayer) {
        self.wantsLayer = YES;
    }
    self.layer.backgroundColor = color.CGColor;
}

- (void)setBackgroundColorWithHexString:(NSString *)hexString {
    NSColor *color = [NSColor colorFromRGBHexString:hexString];
    [self setBackgroundColor:color];
}

- (void)setBackgroundColorWithHexString:(NSString *)hexString andAlpha:(NSInteger)alpha {
    NSColor *color = [NSColor colorFromRGBHexString:hexString andAlpha:alpha];
    [self setBackgroundColor:color];
}

- (void)removeAllSubView {
    while (self.subviews.count > 0) {
        NSView *view = (NSView *)self.subviews.firstObject;
        [view removeFromSuperview];
        view = nil;
    }
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
