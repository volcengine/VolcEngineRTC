//
//  ToastView.m
//  veRTC_Demo
//
//  Created by  on 2021/6/3.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "ToastView.h"

@interface ToastView ()

@property (nonatomic, strong) UIView *bgView;

@end


@implementation ToastView

- (instancetype)initWithMeeage:(NSString *)message {
    self = [super init];
    if (self) {
        self.bgView = [[UIView alloc] init];
        self.bgView.backgroundColor = [UIColor colorFromHexString:@"#394254"];
        self.bgView.layer.cornerRadius = 4;
        self.bgView.layer.masksToBounds = YES;
        
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.textColor = [UIColor colorFromHexString:@"#FFFFFF"];
        titleLabel.font = [UIFont systemFontOfSize:16.0 * (SCREEN_WIDTH / 375) weight:UIFontWeightRegular];
        titleLabel.text = message;
        
        UIImageView *iconImageView = [[UIImageView alloc] init];
        iconImageView.image = [UIImage imageNamed:@"meeting_end_waring"];
        
        [self addSubview:self.bgView];
        [self.bgView addSubview:iconImageView];
        [self.bgView addSubview:titleLabel];
        
        [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self).offset(10);
            make.right.equalTo(self).offset(-10);
            make.top.bottom.equalTo(self);
        }];
        
        [iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(16.0 * (SCREEN_WIDTH / 375), 16.0 * (SCREEN_WIDTH / 375)));
            make.centerY.equalTo(self.bgView);
            make.left.equalTo(self.bgView).offset(16.0 * (SCREEN_WIDTH / 375));
        }];
        
        [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(self.bgView);
            make.left.equalTo(iconImageView.mas_right).offset(16.0 * (SCREEN_WIDTH / 375));
        }];
    }
    return self;
}

@end
