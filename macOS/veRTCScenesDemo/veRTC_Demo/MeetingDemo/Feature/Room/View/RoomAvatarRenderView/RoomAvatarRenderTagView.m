//
//  RoomAvatarRenderTagView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import "RoomAvatarRenderTagView.h"

@interface RoomAvatarRenderTagView ()

@property (nonatomic, strong) NSView *bgView;
@property (nonatomic, strong) NSImageView *screenImageView;
@property (nonatomic, strong) NSLabel *nameLabel;
@property (nonatomic, strong) NSButton *hostButton;

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

- (void)setUserModel:(RoomUserModel *)userModel {
    _userModel = userModel;
    
    self.screenImageView.hidden = !userModel.isOpenScreen;
    self.hostButton.hidden = !userModel.isHost;
    self.nameLabel.text = userModel.name;
    
    
    [self.nameLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
        if (userModel.isOpenScreen) {
            make.centerY.equalTo(self);
            make.left.equalTo(self.screenImageView.mas_right).offset(4);
        } else {
            make.centerY.equalTo(self);
            make.left.equalTo(self).offset(8);
        }
    }];
    
    CGFloat hostWidth = userModel.isHost ? 52 : 8;
    CGFloat screenWidth = userModel.isOpenScreen ? 24 : 8;
    [self mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(self.nameLabel.mas_width).offset(screenWidth + hostWidth);
    }];
}

- (void)setFont:(NSFont *)font {
    _font = font;
    self.nameLabel.font = font;
}

- (void)setTextColor:(NSColor *)textColor {
    _textColor = textColor;
    self.nameLabel.textColor = textColor;
}

#pragma mark - getter

- (NSImageView *)screenImageView {
    if (!_screenImageView) {
        _screenImageView = [[NSImageView alloc] init];
        _screenImageView.image = [NSImage imageNamed:@"meeting_par_screen"];
    }
    return _screenImageView;
}

- (NSLabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[NSLabel alloc] init];
        _nameLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        NSInteger fontNum = 12;
        _nameLabel.font = [NSFont systemFontOfSize:fontNum weight:NSFontWeightRegular];
    }
    return _nameLabel;
}

- (NSButton *)hostButton {
    if (!_hostButton) {
        _hostButton = [[NSButton alloc] init];
        [_hostButton setTitleColor:@"#4080FF" title:@"主持人"];
        [_hostButton setBackgroundColorWithHexString:@"#1D2129"];
        _hostButton.wantsLayer = YES;
        _hostButton.layer.masksToBounds = YES;
        _hostButton.layer.cornerRadius = 2;
    }
    return _hostButton;
}

- (NSView *)bgView {
    if (!_bgView) {
        _bgView = [[NSView alloc] init];
        [_bgView setBackgroundColorWithHexString:@"#272E3B" andAlpha:(0.7 * 255.0)];
        _bgView.wantsLayer = YES;
        _bgView.layer.cornerRadius = 2;
        _bgView.layer.masksToBounds = YES;
    }
    return _bgView;
}

@end
