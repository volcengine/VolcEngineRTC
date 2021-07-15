//
//  UserCell.m
//  veRTC_Demo
//
//  Created by  on 2021/5/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "UserCell.h"

@interface UserCell ()

@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UILabel *desTitleLabel;
@property (nonatomic, strong) UIImageView *moreImageView;

@end

@implementation UserCell


- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        [self createUIComponents];
    }
    return self;
}

- (void)setModel:(MenuCellModel *)model {
    _model = model;
    self.titleLabel.text = model.title;
    if ([model.title isEqualToString:@"用户名"]) {
        self.desTitleLabel.text = [LocalUserComponents userModel].name;
    } else {
        self.desTitleLabel.text = model.desTitle;
    }
    
    CGFloat desRight = 0;
    if (model.isMore) {
        desRight = -40;
        self.moreImageView.hidden = NO;
    } else {
        desRight = -16;
        self.moreImageView.hidden = YES;
    }

    [self.desTitleLabel mas_updateConstraints:^(MASConstraintMaker *make) {
        make.right.mas_equalTo(desRight);
    }];
}

#pragma mark - Private Action

- (void)createUIComponents {
    [self.contentView addSubview:self.titleLabel];
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.contentView).offset(16);
        make.centerY.equalTo(self.contentView);
    }];
    
    [self.contentView addSubview:self.desTitleLabel];
    [self.desTitleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.mas_equalTo(-16);
        make.centerY.equalTo(self.titleLabel);
    }];
    
    [self.contentView addSubview:self.moreImageView];
    [self.moreImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(16, 16));
        make.right.mas_equalTo(-16);
        make.centerY.equalTo(self.titleLabel);
    }];
    
    [self.contentView addSubview:self.lineView];
    [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(16.f);
        make.height.mas_equalTo(XH_1PX_WIDTH);
        make.bottom.equalTo(self.contentView);
        make.right.equalTo(self.contentView);
    }];
}

#pragma mark - Private Action



#pragma mark - getter

- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor whiteColor];
        _titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        _titleLabel.numberOfLines = 2;
    }
    return _titleLabel;
}

- (UILabel *)desTitleLabel {
    if (!_desTitleLabel) {
        _desTitleLabel = [[UILabel alloc] init];
        _desTitleLabel.textColor = [UIColor colorFromHexString:@"#86909C"];
        _desTitleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
    }
    return _desTitleLabel;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
    }
    return _lineView;
}

- (UIImageView *)moreImageView {
    if (!_moreImageView) {
        _moreImageView = [[UIImageView alloc] init];
        _moreImageView.image = [UIImage imageNamed:@"menu_list_more"];
    }
    return _moreImageView;
}

@end
