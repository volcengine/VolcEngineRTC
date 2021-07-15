//
//  ScenesItemButton.m
//  veRTC_Demo
//
//  Created by  on 2021/5/26.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "ScenesItemButton.h"

@interface ScenesItemButton ()

@property (nonatomic, strong) UIView *bgView;
@property (nonatomic, strong) UIView *bgSelectView;

@end

@implementation ScenesItemButton

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.bgView];
        [self addSubview:self.bgSelectView];
        
        [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        [self.bgSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addTarget:self action:@selector(touchUp:) forControlEvents:UIControlEventTouchUpInside];
        [self addTarget:self action:@selector(touchUp:) forControlEvents:UIControlEventTouchUpOutside];
        [self addTarget:self action:@selector(touchDown:) forControlEvents:UIControlEventTouchDown];
        [self addTarget:self action:@selector(touchUp:) forControlEvents:UIControlEventTouchCancel];
    }
    return self;
}

#pragma mark - Publish Action

- (void)addItemLayer {
    [self addItemBgGradientLayer];
    [self addItemSelectBgGradientLayer];
}

#pragma mark - Private Action

- (void)touchUp:(UIButton *)sender {
    self.bgView.hidden = NO;
    self.bgSelectView.hidden = YES;
}

- (void)touchDown:(UIButton *)sender {
    self.bgView.hidden = YES;
    self.bgSelectView.hidden = NO;
}

- (void)addItemBgGradientLayer {
    UIColor *startColor = [UIColor colorFromHexString:@"#39455B"];
    UIColor *endColor = [UIColor colorFromRGBHexString:@"#39455B"];
    CAGradientLayer *gradientLayer = [CAGradientLayer layer];
    gradientLayer.frame = self.bgView.bounds;
    gradientLayer.colors = @[(__bridge id)[startColor colorWithAlphaComponent:1.0].CGColor,
                             (__bridge id)[endColor colorWithAlphaComponent:0.5].CGColor];
    gradientLayer.startPoint = CGPointMake(0.5, .0);
    gradientLayer.endPoint = CGPointMake(0.5, 1.0);
    [self.bgView.layer addSublayer:gradientLayer];
}

- (void)addItemSelectBgGradientLayer {
    UIColor *startColor = [UIColor colorFromRGBHexString:@"#39455B"];
    UIColor *endColor = [UIColor colorFromHexString:@"#39455B"];
    CAGradientLayer *gradientLayer = [CAGradientLayer layer];
    gradientLayer.frame = self.bgSelectView.bounds;
    gradientLayer.colors = @[(__bridge id)[startColor colorWithAlphaComponent:0.5].CGColor,
                             (__bridge id)[endColor colorWithAlphaComponent:1.0].CGColor];
    gradientLayer.startPoint = CGPointMake(0.5, .0);
    gradientLayer.endPoint = CGPointMake(0.5, 1.0);
    [self.bgSelectView.layer addSublayer:gradientLayer];
}

- (UIView *)bgView {
    if (!_bgView) {
        _bgView = [[UIView alloc] init];
        _bgView.userInteractionEnabled = NO;
    }
    return _bgView;
}

- (UIView *)bgSelectView {
    if (!_bgSelectView) {
        _bgSelectView = [[UIView alloc] init];
        _bgSelectView.userInteractionEnabled = NO;
        _bgSelectView.hidden = YES;
    }
    return _bgSelectView;
}

@end
