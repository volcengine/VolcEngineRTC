//
//  RoomAvatarRenderTagView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import "RoomAvatarRenderTagView.h"

@interface RoomAvatarRenderTagView ()

@property (nonatomic, strong) UIView *bgView;
@property (nonatomic, strong) UIImageView *screenImageView;
@property (nonatomic, strong) UILabel *nameLabel;
@property (nonatomic, strong) UIButton *hostButton;

@end

@implementation RoomAvatarRenderTagView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.bgView];
        [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubview:self.screenImageView];
        [self.screenImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(16, 16));
            make.left.equalTo(self).offset(4);
            make.centerY.equalTo(self);
        }];

        [self addSubview:self.nameLabel];
        [self.nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(self);
        }];
        
        [self addSubview:self.hostButton];
        [self.hostButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(44, 16));
            make.right.equalTo(self).offset(-4);
            make.centerY.equalTo(self);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)setUserModel:(RoomVideoSession *)userModel {
    _userModel = userModel;

    self.screenImageView.hidden = !userModel.isScreen;
    self.hostButton.hidden = !userModel.isHost;
    self.nameLabel.text = userModel.name;


    [self.nameLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
        if (userModel.isScreen) {
            make.centerY.equalTo(self);
            make.left.equalTo(self.screenImageView.mas_right).offset(4);
        } else {
            make.centerY.equalTo(self);
            make.left.equalTo(self).offset(8);
        }
    }];

    CGFloat hostWidth = userModel.isHost ? 52 : 8;
    CGFloat screenWidth = userModel.isScreen ? 24 : 8;
    [self mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(self.nameLabel.mas_width).offset(screenWidth + hostWidth);
    }];
}

- (void)setHiddenBG:(BOOL)hiddenBG {
    _hiddenBG = hiddenBG;
    self.bgView.hidden = hiddenBG;
}

- (void)setFont:(UIFont *)font {
    _font = font;
    self.nameLabel.font = font;
}

- (void)setTextColor:(UIColor *)textColor {
    _textColor = textColor;
    self.nameLabel.textColor = textColor;
}


#pragma mark - getter

- (UIImageView *)screenImageView {
    if (!_screenImageView) {
        _screenImageView = [[UIImageView alloc] init];
        _screenImageView.image = [UIImage imageNamed:@"meeting_par_screen"];
    }
    return _screenImageView;
}

- (UILabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[UILabel alloc] init];
        _nameLabel.textColor = [UIColor colorFromHexString:@"#FFFFFF"];
        NSInteger fontNum = 12;
        _nameLabel.font = [UIFont systemFontOfSize:fontNum weight:UIFontWeightRegular];
    }
    return _nameLabel;
}

- (UIButton *)hostButton {
    if (!_hostButton) {
        _hostButton = [[UIButton alloc] init];
        [_hostButton setTitle:@"主持人" forState:UIControlStateNormal];
        [_hostButton setTitleColor:[UIColor colorFromHexString:@"#4080FF"] forState:UIControlStateNormal];
        _hostButton.titleLabel.font = [UIFont systemFontOfSize:12];
        _hostButton.backgroundColor = [UIColor colorFromRGBHexString:@"#1D2129" andAlpha:0.8 * 255];
        _hostButton.layer.masksToBounds = YES;
        _hostButton.layer.cornerRadius = 2;
    }
    return _hostButton;
}

- (UIView *)bgView {
    if (!_bgView) {
        _bgView = [[UIView alloc] init];
        _bgView.backgroundColor = [UIColor colorFromRGBHexString:@"#272E3B" andAlpha:(0.7 * 255.0)];
        _bgView.layer.cornerRadius = 2;
        _bgView.layer.masksToBounds = YES;
    }
    return _bgView;
}

@end
