//
//  VoiceRoomUserListtCell.m
//  veRTC_Demo
//
//  Created by  on 2021/5/19.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomUserListtCell.h"
#import "VoiceAvatarCompoments.h"

@interface VoiceRoomUserListtCell ()

@property (nonatomic, strong) UILabel *nameLabel;
@property (nonatomic, strong) BaseButton *rightButton;
@property (nonatomic, strong) VoiceAvatarCompoments *avatarView;

@end

@implementation VoiceRoomUserListtCell


- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        [self createUIComponents];
    }
    return self;
}

- (void)setModel:(VoiceControlUserModel *)model {
    _model = model;
    self.nameLabel.text = model.user_name;
    self.avatarView.text = model.user_name;
    CGFloat buttonWidth = 0;
    
    if (model.user_status == 0) {
        [self.rightButton setTitle:@"邀请上麦" forState:UIControlStateNormal];
        self.rightButton.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
        buttonWidth = 96;
    } else if (model.user_status == 1) {
        [self.rightButton setTitle:@"同意" forState:UIControlStateNormal];
        self.rightButton.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
        buttonWidth = 64;
    } else if (model.user_status == 2) {
        [self.rightButton setTitle:@"下麦" forState:UIControlStateNormal];
        self.rightButton.backgroundColor = [UIColor colorFromRGBHexString:@"#4080FF"];
        buttonWidth = 64;
    } else {
        
    }
    [self.rightButton mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(buttonWidth);
    }];
}


- (void)createUIComponents {
    [self.contentView addSubview:self.avatarView];
    [self.avatarView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(40, 40));
        make.left.mas_equalTo(16);
        make.bottom.equalTo(self.contentView);
    }];
    
    [self.contentView addSubview:self.rightButton];
    [self.rightButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(64);
        make.height.mas_equalTo(30);
        make.right.mas_equalTo(-16);
        make.centerY.equalTo(self.avatarView);
    }];
    
    [self.contentView addSubview:self.nameLabel];
    [self.nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.avatarView.mas_right).mas_offset(9);
        make.centerY.equalTo(self.avatarView);
        make.right.mas_lessThanOrEqualTo(self.rightButton.mas_left).offset(-9);
    }];
}

- (void)rightButtonAction:(BaseButton *)sender {
    if ([self.delegate respondsToSelector:@selector(voiceRoomUserListtCell:clickButton:)]) {
        [self.delegate voiceRoomUserListtCell:self clickButton:self.model];
    }
}

#pragma mark - getter

- (BaseButton *)rightButton {
    if (!_rightButton) {
        _rightButton = [[BaseButton alloc] init];
        _rightButton.layer.cornerRadius = 15;
        _rightButton.layer.masksToBounds = YES;
        _rightButton.titleLabel.font = [UIFont systemFontOfSize:16];
        [_rightButton addTarget:self action:@selector(rightButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _rightButton;
}

- (VoiceAvatarCompoments *)avatarView {
    if (!_avatarView) {
        _avatarView = [[VoiceAvatarCompoments alloc] init];
        _avatarView.layer.cornerRadius = 20;
        _avatarView.layer.masksToBounds = YES;
        _avatarView.fontSize = 20;
    }
    return _avatarView;
}

- (UILabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[UILabel alloc] init];
        _nameLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
        _nameLabel.font = [UIFont systemFontOfSize:16];
    }
    return _nameLabel;
}

@end
