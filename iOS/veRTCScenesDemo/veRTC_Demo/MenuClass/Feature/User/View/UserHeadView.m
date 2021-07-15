//
//  UserHeadView.m
//  veRTC_Demo
//
//  Created by  on 2021/5/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "UserHeadView.h"
#import "VoiceAvatarCompoments.h"

@interface UserHeadView ()

@property (nonatomic, strong) VoiceAvatarCompoments *avatarView;

@end

@implementation UserHeadView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.avatarView];
        [self.avatarView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(80, 80));
            make.center.equalTo(self);
        }];
    }
    return self;
}

- (void)setNameString:(NSString *)nameString {
    _nameString = nameString;
    
    self.avatarView.text = nameString;
}

- (VoiceAvatarCompoments *)avatarView {
    if (!_avatarView) {
        _avatarView = [[VoiceAvatarCompoments alloc] init];
        _avatarView.layer.cornerRadius = 40;
        _avatarView.layer.masksToBounds = YES;
        _avatarView.fontSize = 32;
    }
    return _avatarView;
}


@end
