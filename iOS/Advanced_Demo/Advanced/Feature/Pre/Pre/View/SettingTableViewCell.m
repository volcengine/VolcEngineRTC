//
//  SettingTableViewCell.m
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "SettingTableViewCell.h"

@interface SettingTableViewCell ()
@property (nonatomic, strong) UISwitch *switchView;
@property (nonatomic, strong) UISlider *slider;
@end

@implementation SettingTableViewCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    if (self = [super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
        self.selectionStyle = UITableViewCellSelectionStyleNone;

        [self.contentView addSubview:self.slider];
    }
    return self;
}

- (void)setModel:(SettingBaseModel *)model {
    _model = model;
    self.textLabel.text = model.title;

    switch (model.cellType) {
        case SettingTableViewCellType_Switch: {
            self.accessoryType = UITableViewCellAccessoryNone;
            self.accessoryView = self.switchView;
            self.slider.hidden = YES;
            self.detailTextLabel.text = @"";

            SettingSwitchModel *switchModel = (SettingSwitchModel *)model;
            self.switchView.on = switchModel.isOn;
        } break;
        case SettingTableViewCellType_OptionArray: {
            self.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
            self.slider.hidden = YES;
            self.accessoryView = nil;

            SettingOptionArrayModel *optionModel = (SettingOptionArrayModel *)model;
            NSInteger index = optionModel.currentIndex;
            NSString *text = index >= 0 ? optionModel.optionArray[index] : @"";
            self.detailTextLabel.text = text;
        } break;
        case SettingTableViewCellType_Slider: {
            self.accessoryType = UITableViewCellAccessoryNone;
            self.slider.hidden = NO;
            self.accessoryView = nil;

            SettingSliderModel *sliderModel = (SettingSliderModel *)model;
            self.slider.value = (sliderModel.currentValue - sliderModel.minValue) * 1.0 / (sliderModel.maxValue - sliderModel.minValue);
            self.detailTextLabel.text = [NSString stringWithFormat:@"%ld%@", sliderModel.currentValue, sliderModel.suffix];
        } break;
        case SettingTableViewCellType_Button: {
            self.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
            self.slider.hidden = YES;
            self.accessoryView = nil;

            SettingButtonModel *sliderModel = (SettingButtonModel *)model;
            self.detailTextLabel.text = sliderModel.describe;
        } break;
        case SettingTableViewCellType_TextField: {
            self.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
            self.slider.hidden = YES;
            self.accessoryView = nil;

            SettingTextFieldModel *textFieldModel = (SettingTextFieldModel *)model;
            self.detailTextLabel.text = [textFieldModel.describe stringByAppendingString:textFieldModel.unit];
        } break;
        case SettingTableViewCellType_Label: {
            self.accessoryType = UITableViewCellAccessoryNone;
            self.slider.hidden = YES;
            self.accessoryView = nil;

            SettingTextFieldModel *sliderModel = (SettingTextFieldModel *)model;
            self.detailTextLabel.text = sliderModel.describe;
        } break;

        default: {
        } break;
    }
}

- (void)switchValueDidChanged:(UISwitch *)sender {
    if (self.model.cellType == SettingTableViewCellType_Switch) {
        SettingSwitchModel *model = (SettingSwitchModel *)self.model;
        model.isOn = sender.isOn;
        if (model.switchDidChangeStatus) {
            model.switchDidChangeStatus(sender.isOn);
        }
    }
}

- (void)sliderValueDidChanged:(UISlider *)slider {
    if (self.model.cellType == SettingTableViewCellType_Slider) {
        SettingSliderModel *sliderModel = (SettingSliderModel *)self.model;

        sliderModel.currentValue = slider.value * (sliderModel.maxValue - sliderModel.minValue) + sliderModel.minValue;

        self.detailTextLabel.text = [NSString stringWithFormat:@"%ld%@", sliderModel.currentValue, sliderModel.suffix];

        if (sliderModel.sliderValueDidChanged) {
            sliderModel.sliderValueDidChanged(sliderModel.currentValue);
        }
    }
}

- (void)layoutSubviews {
    [super layoutSubviews];

    CGRect contenViewFrame = self.contentView.frame;
    CGRect textLabelFrame = self.textLabel.frame;
    CGRect detailLabelFrame = self.detailTextLabel.frame;
    CGSize sliderSize = self.slider.bounds.size;

    CGFloat sliderX = textLabelFrame.origin.x + textLabelFrame.size.width + 10;
    CGFloat sliderY = (contenViewFrame.size.height - sliderSize.height) * 0.5;
    CGFloat sliderW = detailLabelFrame.origin.x - sliderX - 20;
    CGFloat sliderH = sliderSize.height;

    self.slider.frame = CGRectMake(sliderX, sliderY, sliderW, sliderH);
}

#pragma mark - getter

- (UISwitch *)switchView {
    if (!_switchView) {
        _switchView = [[UISwitch alloc] init];
        [_switchView addTarget:self action:@selector(switchValueDidChanged:) forControlEvents:UIControlEventValueChanged];
    }
    return _switchView;
}

- (UISlider *)slider {
    if (!_slider) {
        _slider = [[UISlider alloc] init];
        [_slider addTarget:self action:@selector(sliderValueDidChanged:) forControlEvents:UIControlEventValueChanged];
    }
    return _slider;
}
@end
