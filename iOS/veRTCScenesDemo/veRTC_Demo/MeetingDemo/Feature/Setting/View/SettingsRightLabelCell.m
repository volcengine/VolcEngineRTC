#import "SettingsRightLabelCell.h"
#import "SettingsService.h"
#import <Masonry.h>

@interface SettingsRightLabelCell ()

@property (nonatomic, strong) UILabel *settingsLabel;
@property (nonatomic, strong) UILabel *settingsRightLabel;
@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) UIImageView *moreImageView;

@end

@implementation SettingsRightLabelCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        [self createUIComponents];
    }
    return self;
}

#pragma mark - Private Action

- (void)createUIComponents {
    [self.contentView addSubview:self.settingsLabel];
    [self.settingsLabel setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
    [self.settingsLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.contentView).mas_offset(32/2.f);
        make.centerY.equalTo(self.contentView);
    }];

    [self.contentView addSubview:self.settingsRightLabel];
    [self.settingsRightLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.contentView).mas_offset(-80/2.f);
        make.centerY.equalTo(self.contentView);
    }];
    
    [self.contentView addSubview:self.moreImageView];
    [self.moreImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(32/2, 32/2));
        make.right.equalTo(self.contentView).mas_offset(-32/2.f);
        make.centerY.equalTo(self.contentView);
    }];
    
    [self.contentView addSubview:self.lineView];
    [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(32/2.f);
        make.height.mas_equalTo(XH_1PX_WIDTH);
        make.right.bottom.equalTo(self.contentView);
    }];
}

#pragma mark - getter

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
        _moreImageView.image = [UIImage imageNamed:@"meeting_set_more"];
    }
    return _moreImageView;
}

- (UILabel *)settingsRightLabel {
    if (!_settingsRightLabel) {
        _settingsRightLabel = [[UILabel alloc] init];
        _settingsRightLabel.textColor = [UIColor colorFromHexString:@"#86909C"];
        _settingsRightLabel.font = [UIFont systemFontOfSize:16];
    }
    return _settingsRightLabel;
}

- (UILabel *)settingsLabel {
    if (!_settingsLabel) {
        _settingsLabel = [[UILabel alloc] init];
        _settingsLabel.textColor = [UIColor whiteColor];
        _settingsLabel.font = [UIFont systemFontOfSize:16];
    }
    return _settingsLabel;
}

@end
