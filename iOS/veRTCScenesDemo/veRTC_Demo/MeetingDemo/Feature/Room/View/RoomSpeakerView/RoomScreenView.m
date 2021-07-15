//
//  RoomScreenView.m
//  quickstart
//
//  Created by  on 2021/3/25.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "RoomScreenView.h"

@interface RoomScreenView ()

@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) BaseButton *closeShareButton;
@property (nonatomic, strong) UILabel *desLabel;

@end


@implementation RoomScreenView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.titleLabel];
        [self addSubview:self.closeShareButton];
        [self addSubview:self.desLabel];
        
        [self addConstraints];
    }
    return self;
}

- (void)closeShareButtonAction {
    if (self.clickCloseBlock) {
        self.clickCloseBlock();
    }
}

- (void)addConstraints {
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(60);
        make.centerX.equalTo(self);
    }];
    
    [self.closeShareButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self).offset(15);
        make.centerX.equalTo(self);
    }];
    
    [self.desLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.closeShareButton.mas_bottom).offset(40);
        make.centerX.equalTo(self);
    }];
}

#pragma mark - getter

- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor whiteColor];
        _titleLabel.font = [UIFont systemFontOfSize:17];
        _titleLabel.text = @"你正在共享屏幕";
    }
    return _titleLabel;
}
- (BaseButton *)closeShareButton {
    if (!_closeShareButton) {
        _closeShareButton = [[BaseButton alloc] init];
        [_closeShareButton addTarget:self action:@selector(closeShareButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_closeShareButton bingImage:[UIImage imageNamed:@"meeting_room_close_screen"] status:ButtonStatusNone];
    }
    return _closeShareButton;
}


- (UILabel *)desLabel {
    if (!_desLabel) {
        _desLabel = [[UILabel alloc] init];
        _desLabel.textColor = [UIColor colorFromHexString:@"#86909C"];
        _desLabel.font = [UIFont systemFontOfSize:17];
        _desLabel.text = @"停止共享";
    }
    return _desLabel;
}
@end
