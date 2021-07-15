//
//  VoiceIMCell.m
//  veRTC_Demo
//
//  Created by  on 2021/5/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceIMCell.h"

@interface VoiceIMCell ()

@property (nonatomic, strong) UIView *bgView;
@property (nonatomic, strong) UILabel *roomNameLabel;

@end

@implementation VoiceIMCell


- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        [self createUIComponents];
    }
    return self;
}

- (void)setModel:(VoiceIMModel *)model {
    _model = model;
    NSString *unitStr = model.isJoin ? @"加入了房间" : @"离开房间";
    NSString *roomName = [NSString stringWithFormat:@"%@ %@", model.userModel.user_name, unitStr];
    [self setLineSpace:5 withText:roomName inLabel:self.roomNameLabel];
}

#pragma mark - Private Action

- (void)createUIComponents {
    [self.contentView addSubview:self.bgView];
    [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.contentView).offset(10);
        make.bottom.left.equalTo(self.contentView);
    }];
    
    [self.bgView addSubview:self.roomNameLabel];
    [self.roomNameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.bgView).offset(16);
        make.top.equalTo(self.bgView).offset(5);
        make.right.equalTo(self.bgView).offset(-16);
        make.bottom.equalTo(self.bgView).offset(-5);
        make.right.mas_lessThanOrEqualTo(self.contentView.mas_right);
    }];
}

#pragma mark - Private Action

- (void)setLineSpace:(CGFloat)lineSpace withText:(NSString *)text inLabel:(UILabel *)label{
    if (!text || !label) {
        return;
    }
    NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
    paragraphStyle.lineSpacing = lineSpace;
    paragraphStyle.lineBreakMode = label.lineBreakMode;
    paragraphStyle.alignment = label.textAlignment;
    
    NSMutableAttributedString *attributedString = [[NSMutableAttributedString alloc] initWithString:text];
    [attributedString addAttribute:NSParagraphStyleAttributeName value:paragraphStyle range:NSMakeRange(0, [text length])];
    label.attributedText = attributedString;
}

#pragma mark - getter

- (UILabel *)roomNameLabel {
    if (!_roomNameLabel) {
        _roomNameLabel = [[UILabel alloc] init];
        _roomNameLabel.textColor = [UIColor whiteColor];
        _roomNameLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        _roomNameLabel.numberOfLines = 0;
    }
    return _roomNameLabel;
}

- (UIView *)bgView {
    if (!_bgView) {
        _bgView = [[UIView alloc] init];
        _bgView.backgroundColor = [UIColor colorFromRGBHexString:@"#1D2129" andAlpha:0.9 * 255];
        _bgView.layer.cornerRadius = 15;
        _bgView.layer.masksToBounds = YES;
    }
    return _bgView;
}

@end
