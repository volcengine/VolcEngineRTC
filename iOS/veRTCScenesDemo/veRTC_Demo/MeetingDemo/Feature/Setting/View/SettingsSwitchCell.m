#import "SettingsSwitchCell.h"
#import <Masonry.h>

@interface SettingsSwitchCell ()

@property (nonatomic, strong) UILabel *settingsLabel;
@property (nonatomic, strong) UISwitch *settingsSwitch;
@property (nonatomic, strong) UIView *lineView;

@property (nonatomic, copy) void (^valueChangeCallback)(BOOL on);

@end

@implementation SettingsSwitchCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        [self createUIComponents];
    }
    return self;
}

- (void)createUIComponents {
    [self.contentView addSubview:self.settingsLabel];
    [self.settingsLabel mas_makeConstraints:^(MASConstraintMaker *make) {
      make.left.equalTo(self.contentView).mas_offset(15.f);
      make.centerY.equalTo(self.contentView);
    }];

    self.settingsSwitch = [[UISwitch alloc] init];
    self.settingsSwitch.onTintColor = [UIColor colorFromHexString:@"#4080FF"];
    [self.contentView addSubview:self.settingsSwitch];
    [self.settingsSwitch mas_makeConstraints:^(MASConstraintMaker *make) {
      make.right.equalTo(self.contentView).mas_offset(-15.f);
      make.centerY.equalTo(self.contentView);
    }];
    [self.settingsSwitch addTarget:self
                            action:@selector(switchValueChange:)
                  forControlEvents:UIControlEventTouchUpInside];
    
    [self.contentView addSubview:self.lineView];
    [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(32/2.f);
        make.height.mas_equalTo(XH_1PX_WIDTH);
        make.right.bottom.equalTo(self.contentView);
    }];
}

- (void)prepareForReuse {
    [super prepareForReuse];
    self.valueChangeCallback = nil;
}

- (void)switchValueChangeCallback:(void (^)(BOOL on))callback {
    self.valueChangeCallback = callback;
}

- (void)setSwitchOn:(BOOL)on {
    self.settingsSwitch.on = on;
}

- (void)switchValueChange:(UISwitch *)sender {
    if (self.valueChangeCallback != nil) {
        self.valueChangeCallback(sender.on);
    }
}

- (void)setSwitchAccessibilityIdentifier:(NSString *)accessId {
    self.settingsSwitch.isAccessibilityElement = YES;
    self.settingsSwitch.accessibilityIdentifier = accessId;
    self.settingsSwitch.accessibilityLabel = accessId;
}

#pragma mark - getter

- (UILabel *)settingsLabel {
    if (!_settingsLabel) {
        _settingsLabel = [[UILabel alloc] init];
        _settingsLabel.textColor = [UIColor whiteColor];
        _settingsLabel.font = [UIFont systemFontOfSize:16];
    }
    return _settingsLabel;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
    }
    return _lineView;
}

@end
