//
//  VoiceUserAvatarCell.m
//  veRTC_Demo
//
//  Created by  on 2021/5/19.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceUserAvatarCell.h"
#import "VoiceAvatarCompoments.h"

@interface VoiceUserAvatarCell ()

@property (nonatomic, strong) VoiceAvatarCompoments *avatarView;
@property (nonatomic, strong) UILabel *titleLabel;

// Audience
@property (nonatomic, strong) UIImageView *audienceRaiseHandImageView;

// Mic
@property (nonatomic, strong) UIView *micAvatarSpeakView;

@end

@implementation VoiceUserAvatarCell

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.contentView.backgroundColor = [UIColor clearColor];
        [self addSubview:self.avatarView];
        [self.avatarView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(60, 60));
            make.top.centerX.equalTo(self.contentView);
        }];
        
        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.centerX.equalTo(self.contentView);
            make.left.mas_lessThanOrEqualTo(self.contentView).offset(0);
            make.right.mas_lessThanOrEqualTo(self.contentView).offset(0);
        }];

        [self addSubview:self.audienceRaiseHandImageView];
        [self.audienceRaiseHandImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self.avatarView);
        }];
        
        [self addSubview:self.micAvatarSpeakView];
        [self.micAvatarSpeakView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self.avatarView);
        }];
    }
    return self;
}

- (void)setStatus:(AvatarCellStatus)status {
    _status = status;
    
    NSInteger itemWidth = 60;
    NSInteger fontSize = 24;
    NSInteger nameFontSize = 16;
    if (status == AvatarCellStatusAudience) {
        itemWidth = 40;
        fontSize = 20;
        nameFontSize = 12;
        
        
    } else if (status == AvatarCellStatusMic) {
        
    } else {
        
    }
    
    
    [self.avatarView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(itemWidth, itemWidth));
    }];
    self.avatarView.fontSize = fontSize;
    self.titleLabel.font = [UIFont systemFontOfSize:nameFontSize];
    self.avatarView.layer.cornerRadius = itemWidth / 2;
    self.micAvatarSpeakView.layer.cornerRadius = itemWidth / 2;
}

- (void)setModel:(VoiceControlUserModel *)model {
    _model = model;
    self.titleLabel.text = model.user_name;
    self.avatarView.text = model.user_name;
    
    if (self.status == AvatarCellStatusAudience) {
        self.audienceRaiseHandImageView.hidden = model.user_status == 1 ? NO : YES;
        self.micAvatarSpeakView.hidden = YES;
    } else if (self.status == AvatarCellStatusMic) {
        if (model.is_mic_on) {
            self.micAvatarSpeakView.hidden = model.volume >= 10 ? NO : YES;
        } else {
            self.micAvatarSpeakView.hidden = YES;
        }
        self.audienceRaiseHandImageView.hidden = YES;
    } else {
        self.micAvatarSpeakView.hidden = YES;
        self.audienceRaiseHandImageView.hidden = YES;
    }

}

#pragma mark - getter

- (UILabel *)titleLabel {
    if (_titleLabel == nil) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor whiteColor];
        _titleLabel.textAlignment = NSTextAlignmentCenter;
    }
    return _titleLabel;
}

- (VoiceAvatarCompoments *)avatarView {
    if (_avatarView == nil) {
        _avatarView = [[VoiceAvatarCompoments alloc] init];
        _avatarView.layer.masksToBounds = YES;
    }
    return _avatarView;
}

- (UIImageView *)audienceRaiseHandImageView {
    if (!_audienceRaiseHandImageView) {
        _audienceRaiseHandImageView = [[UIImageView alloc] init];
        _audienceRaiseHandImageView.image = [UIImage imageNamed:@"voice_raise_hande"];
        _audienceRaiseHandImageView.hidden = YES;
    }
    return _audienceRaiseHandImageView;
}

- (UIView *)micAvatarSpeakView {
    if (!_micAvatarSpeakView) {
        _micAvatarSpeakView = [[UIView alloc] init];
        _micAvatarSpeakView.layer.masksToBounds = YES;
        _micAvatarSpeakView.layer.borderWidth = 2;
        _micAvatarSpeakView.layer.borderColor = [UIColor colorFromHexString:@"#4080FF"].CGColor;
        _micAvatarSpeakView.hidden = YES;
    }
    return _micAvatarSpeakView;
}

@end
