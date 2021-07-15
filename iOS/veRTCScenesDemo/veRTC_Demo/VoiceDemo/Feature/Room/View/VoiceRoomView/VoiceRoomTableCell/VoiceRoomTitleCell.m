//
//  VoiceRoomTitleCell.m
//  veRTC_Demo
//
//  Created by  on 2021/5/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomTitleCell.h"

@interface VoiceRoomTitleCell ()

@property (nonatomic, strong) UILabel *titleLabel;

@end

@implementation VoiceRoomTitleCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        
        [self.contentView addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.contentView).offset(20);
            make.bottom.equalTo(self.contentView).offset(-20);
            make.left.equalTo(self.contentView).offset(20);
            make.right.equalTo(self.contentView).offset(-20);
        }];
    }
    return self;
}

- (void)setTitleStr:(NSString *)titleStr {
    _titleStr = titleStr;
    
    titleStr = [titleStr stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    self.titleLabel.text = titleStr;
}


- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor whiteColor];
        _titleLabel.font = [UIFont systemFontOfSize:24];
        _titleLabel.numberOfLines = 2;
    }
    return _titleLabel;
}

@end
