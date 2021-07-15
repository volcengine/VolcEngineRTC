//
//  MeetingPickerCompoments.m
//  quickstart
//
//  Created by  on 2021/3/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "MeetingPickerCompoments.h"

@interface MeetingPickerCompoments () <UIPickerViewDelegate,UIPickerViewDataSource>

@property (nonatomic, strong) UIPickerView *pickerView;
@property (nonatomic, weak) UIView *superView;
@property (nonatomic, assign) CGFloat currentHeight;
@property (nonatomic, copy) NSArray *dataLists;

@property (nonatomic, strong) UIView *maskView;
@property (nonatomic, strong) UIView *contentView;
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UIButton *cancelButton;
@property (nonatomic, strong) UIButton *confirmButton;

@property (nonatomic, assign) NSInteger selectRow;
@property (nonatomic, strong) id selectItem;

@end

@implementation MeetingPickerCompoments


- (instancetype)initWithHeight:(CGFloat)height superView:(UIView *)superView {
    self = [super init];
    if (self) {
        _selectRow = 0;
        _selectItem = nil;
        _superView = superView;
        _currentHeight = height + [DeviceInforTool getVirtualHomeHeight];
    }
    return self;
}

- (void)cancelButtonAction:(UIButton *)sender {
    __weak __typeof(self) wself = self;
    [self dismiss:^{
        if (wself.clickDismissBlock) {
            wself.clickDismissBlock(YES, wself.selectItem, wself.selectRow);
        }
    }];
}

- (void)confirmButtonAction:(UIButton *)sender {
    __weak __typeof(self) wself = self;
    [self dismiss:^{
        if (wself.clickDismissBlock) {
            wself.clickDismissBlock(NO, wself.selectItem, wself.selectRow);
        }
    }];
}

#pragma mark - Publish Action

- (void)show:(NSArray *)dataLists selectItem:(id)item {
    [self addSubViewAndConstraints];
    
    self.dataLists = dataLists;
    [self.pickerView reloadAllComponents];
    self.selectItem = dataLists.firstObject;
    
    if (item) {
        NSInteger row = 0;
        if ([item isKindOfClass:[NSArray class]]) {
            for (int i = 0; i < dataLists.count; i++) {
                NSArray *data = dataLists[i];
                if ([data isEqualToArray:item]) {
                    row = i;
                    break;
                }
            }
        } else if ([item isKindOfClass:[NSNumber class]]) {
            for (int i = 0; i < dataLists.count; i++) {
                NSNumber *number = dataLists[i];
                if (number.intValue == ((NSNumber *)item).intValue) {
                    row = i;
                    break;
                }
            }
        }
        self.selectItem = item;
        self.selectRow = row;
        [self.pickerView selectRow:row inComponent:0 animated:NO];
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [UIView animateWithDuration:0.25 animations:^{
            [self.contentView mas_updateConstraints:^(MASConstraintMaker *make) {
                make.bottom.equalTo(self.maskView).offset(0);
            }];
            [self.contentView.superview layoutIfNeeded];
        }];
    });
}

- (void)setTitleStr:(NSString *)titleStr {
    _titleStr = titleStr;
    self.titleLabel.text = titleStr;
}

#pragma mark - Private Action

- (void)dismiss:(void (^)(void))block {
    dispatch_async(dispatch_get_main_queue(), ^{
        [UIView animateWithDuration:0.25 animations:^{
            [self.contentView mas_updateConstraints:^(MASConstraintMaker *make) {
                make.bottom.equalTo(self.maskView).offset(self.currentHeight);
            }];
            [self.contentView.superview layoutIfNeeded];
        }];
    });
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.25 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self.maskView removeAllSubviews];
        [self.maskView removeFromSuperview];
        if (block) {
            block();
        }
    });
}

- (void)addSubViewAndConstraints {
    [_superView addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(_superView);
    }];
    
    [self.maskView addSubview:self.contentView];
    [self.contentView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.maskView);
        make.bottom.equalTo(self.maskView).offset(_currentHeight);
        make.height.mas_equalTo(_currentHeight);
    }];
    
    [self.contentView addSubview:self.titleLabel];
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(108/2);
        make.width.top.centerX.equalTo(self.contentView);
    }];
    
    [self.contentView addSubview:self.cancelButton];
    [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.height.mas_equalTo(44);
        make.left.equalTo(self.titleLabel).offset(18);
        make.centerY.equalTo(self.titleLabel);
    }];
    
    [self.contentView addSubview:self.confirmButton];
    [self.confirmButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.height.mas_equalTo(44);
        make.right.equalTo(self.titleLabel).offset(-18);
        make.centerY.equalTo(self.titleLabel);
    }];
    
    [self.contentView addSubview:self.pickerView];
    [self.pickerView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.bottom.equalTo(self.contentView);
        make.top.equalTo(self.titleLabel.mas_bottom);
    }];
}
#pragma mark - UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}


- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return self.dataLists.count;
}


#pragma mark - UIPickerViewDelegate

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    NSArray *resolutions = self.dataLists[row];
    self.selectItem = resolutions;
    self.selectRow = row;
}

- (UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view{
    id item = self.dataLists[row];
    NSString *titleString = @"";
    if ([item isKindOfClass:[NSArray class]]) {
        titleString = [NSString stringWithFormat:@"%@*%@", item[0], item[1]];
    } else if ([item isKindOfClass:[NSNumber class]]) {
        titleString = [NSString stringWithFormat:@"%@", item];
    }
    UILabel *genderLabel = [[UILabel alloc] init];
    genderLabel.textAlignment = NSTextAlignmentCenter;
    genderLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
    genderLabel.font = [UIFont systemFontOfSize:16];
    genderLabel.text = titleString;
    return genderLabel;
}

- (CGFloat)pickerView:(UIPickerView *)pickerView widthForComponent:(NSInteger)component {
    return SCREEN_WIDTH;
}

- (CGFloat)pickerView:(UIPickerView *)pickerView rowHeightForComponent:(NSInteger)component {
    return 44;
}

#pragma mark - getter

- (UIView *)maskView {
    if (!_maskView) {
        _maskView = [[UIView alloc] init];
        _maskView.backgroundColor = [UIColor colorFromRGBHexString:@"#101319" andAlpha:0.5 * 255];
    }
    return _maskView;
}

- (UIPickerView *)pickerView {
    if (_pickerView == nil) {
        _pickerView = [[UIPickerView alloc] init];
        _pickerView.backgroundColor = [UIColor clearColor];
        _pickerView.delegate = self;
        _pickerView.dataSource = self;
    }
    return _pickerView;
}


- (UIView *)contentView {
    if (!_contentView) {
        _contentView = [[UIView alloc] init];
        _contentView.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
    }
    return _contentView;
}
- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
        _titleLabel.textAlignment = NSTextAlignmentCenter;
    }
    return _titleLabel;
}

- (UIButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[UIButton alloc] init];
        [_cancelButton addTarget:self action:@selector(cancelButtonAction:) forControlEvents:UIControlEventTouchUpInside];
        _cancelButton.backgroundColor = [UIColor clearColor];
        [_cancelButton setTitle:@"取消" forState:UIControlStateNormal];
        _cancelButton.titleLabel.font = [UIFont systemFontOfSize:15 weight:UIFontWeightRegular];
        [_cancelButton setTitleColor:[UIColor colorFromHexString:@"#86909C"] forState:UIControlStateNormal];
    }
    return _cancelButton;
}

- (UIButton *)confirmButton {
    if (!_confirmButton) {
        _confirmButton = [[UIButton alloc] init];
        [_confirmButton addTarget:self action:@selector(confirmButtonAction:) forControlEvents:UIControlEventTouchUpInside];
        _confirmButton.backgroundColor = [UIColor clearColor];
        [_confirmButton setTitle:@"确定" forState:UIControlStateNormal];
        _confirmButton.titleLabel.font = [UIFont systemFontOfSize:15 weight:UIFontWeightRegular];
        [_confirmButton setTitleColor:[UIColor colorFromHexString:@"#4080FF"] forState:UIControlStateNormal];
    }
    return _confirmButton;
}


- (void)dealloc {
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}

@end
