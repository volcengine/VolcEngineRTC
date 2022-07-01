//
//  BeautyBarView.m
//  quickstart

#import "BeautyBarView.h"
#import "EffectButton.h"
#import "Masonry.h"
#import "BeautyModel.h"

@interface BeautyBarView ()
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UISegmentedControl *segment;

@property (nonatomic, strong) UILabel *sliderLabel;
@property (nonatomic, strong) UISlider *slider;

@property (nonatomic, strong) UIView *buttonListView;

@property (nonatomic, strong) NSMutableArray <NSArray <EffectModel *> *> *dataArray;
@end

@implementation BeautyBarView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.backgroundColor = [UIColor whiteColor];

        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
          make.left.mas_equalTo(20);
          make.top.mas_equalTo(45);
        }];

        [self addSubview:self.segment];
        [self.segment mas_makeConstraints:^(MASConstraintMaker *make) {
          make.top.equalTo(self.titleLabel.mas_bottom).offset(20);
          make.left.mas_equalTo(20);
          make.right.mas_equalTo(-20);
        }];

        [self addSubview:self.sliderLabel];
        [self.sliderLabel mas_makeConstraints:^(MASConstraintMaker *make) {
          make.left.mas_equalTo(20);
          make.top.equalTo(self.segment.mas_bottom).offset(35);
        }];

        [self addSubview:self.slider];
        [self.slider mas_makeConstraints:^(MASConstraintMaker *make) {
          make.centerY.equalTo(self.sliderLabel);
          make.left.equalTo(self.sliderLabel.mas_right).offset(30);
          make.right.mas_equalTo(-20);
        }];

        [self addSubview:self.buttonListView];
        [self.buttonListView mas_makeConstraints:^(MASConstraintMaker *make) {
          make.left.mas_equalTo(20);
          make.top.equalTo(self.segment.mas_bottom).offset(90);
          make.bottom.equalTo(self);
          make.right.mas_offset(-20);
        }];

        [self loadData];
    }
    return self;
}

- (void)loadData {
    NSMutableArray *jsonList = [NSMutableArray array];
    [jsonList addObject:[BeautyModel beautyList]];
    [jsonList addObject:[BeautyModel stickerList]];
    [jsonList addObject:[BeautyModel filterList]];
    [jsonList addObject:[BeautyModel virtualBackgroundList]];
    
    for (int i = 0; i < jsonList.count; i++) {
        NSArray *sectionList = jsonList[i];
        NSMutableArray *modelList = [NSMutableArray array];
        for (int j = 0; j < sectionList.count; j++) {
            EffectModel *model = [[EffectModel alloc] init];
            model.type = i;
            model.selected = NO;
            model.value = 0;
            model.dic = sectionList[j];
            [modelList addObject:model];
        }
        [self.dataArray addObject:[modelList copy]];
    }
    [self segmentValueChanged:nil];
}

- (void)layoutSubviews {
    [super layoutSubviews];

    UIBezierPath *cornerRadiusPath = [UIBezierPath bezierPathWithRoundedRect:self.bounds byRoundingCorners:UIRectCornerTopRight | UIRectCornerTopLeft cornerRadii:CGSizeMake(32, 32)];
    CAShapeLayer *cornerRadiusLayer = [[CAShapeLayer alloc] init];

    cornerRadiusLayer.frame = self.bounds;

    cornerRadiusLayer.path = cornerRadiusPath.CGPath;

    self.layer.mask = cornerRadiusLayer;
}

- (void)buttonClicked:(UIButton *)button {
    for (EffectButton *subButton in self.buttonListView.subviews) {
        if (subButton == button) {
            if (self.segment.selectedSegmentIndex == 1) {
                //贴纸
                subButton.selected = !subButton.selected;
                subButton.model.selected = subButton.selected;
            } else if (self.segment.selectedSegmentIndex == 2) {
                //滤镜
                subButton.selected = YES;
                subButton.model.selected = YES;
                subButton.model.value = 0;
                self.slider.value = subButton.model.value;
            } else if (self.segment.selectedSegmentIndex == 0) {
                //美颜
                subButton.selected = YES;
                subButton.model.selected = YES;
                self.slider.value = subButton.model.value;
            } else if (self.segment.selectedSegmentIndex == 3) {
                //背景分割
                subButton.selected = !subButton.selected;
                subButton.model.selected = subButton.selected;
            } else {
                //error
            }

            if ([self.delegate respondsToSelector:@selector(beautyBarView:didClickedEffect:)]) {
                [self.delegate beautyBarView:self didClickedEffect:subButton.model];
            }
        } else {
            subButton.selected = NO;
            subButton.model.selected = NO;
        }
    }
}

- (void)sliderValueChanged:(UISlider *)slider {
    for (EffectButton *button in self.buttonListView.subviews) {
        if (button.selected) {
            button.model.value = slider.value;
            if ([self.delegate respondsToSelector:@selector(beautyBarView:didChangeEffectValue:)]) {
                [self.delegate beautyBarView:self didChangeEffectValue:button.model];
            }
        }
    }
}

#pragma mark - private action
- (void)segmentValueChanged:(UISegmentedControl *)segment {
    NSArray *modelArray = self.dataArray[self.segment.selectedSegmentIndex];

    for (UIView *subView in self.buttonListView.subviews) {
        [subView removeFromSuperview];
    }

    for (int i = 0; i < modelArray.count; i++) {
        EffectModel *model = modelArray[i];
        EffectButton *button = [[EffectButton alloc] init];
        button.model = model;

        [button addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];

        [self.buttonListView addSubview:button];

        NSInteger row = i / 4;
        NSInteger col = i % 4;
        [button mas_makeConstraints:^(MASConstraintMaker *make) {
          make.top.mas_equalTo(row * (30 + 36));
          make.centerX.equalTo(self.buttonListView).multipliedBy(0.5 * col + 0.25);
          make.width.mas_equalTo(70);
          make.height.mas_equalTo(36);
        }];
    }

    switch (segment.selectedSegmentIndex) {
        case 0: //美颜
        {
            [self.buttonListView mas_updateConstraints:^(MASConstraintMaker *make) {
              make.top.equalTo(self.segment.mas_bottom).offset(90);
            }];

            self.sliderLabel.text = @"美颜强度";
            self.sliderLabel.hidden = NO;
            self.slider.hidden = NO;

            EffectButton *button = self.buttonListView.subviews.firstObject;
            button.selected = YES;

            EffectModel *model = modelArray[0];

            self.slider.value = model.value;

        } break;
        case 1: //贴纸
        {
            [self.buttonListView mas_updateConstraints:^(MASConstraintMaker *make) {
              make.top.equalTo(self.segment.mas_bottom).offset(36);
            }];

            self.sliderLabel.hidden = YES;
            self.slider.hidden = YES;

            for (EffectButton *button in self.buttonListView.subviews) {
                button.selected = button.model.selected;
            }
        } break;
        case 2: //滤镜
        {
            [self.buttonListView mas_updateConstraints:^(MASConstraintMaker *make) {
              make.top.equalTo(self.segment.mas_bottom).offset(90);
            }];

            self.sliderLabel.text = @"滤镜强度";
            self.sliderLabel.hidden = NO;
            self.slider.hidden = NO;

            // 之前选中过
            BOOL selected = NO;
            for (EffectButton *button in self.buttonListView.subviews) {
                if (button.model.selected) {
                    button.selected = YES;
                    self.slider.value = button.model.value;
                    selected = YES;
                }
            }

            if (selected == NO) {
                //之前没有选中过,默认第一个
                EffectButton *button = self.buttonListView.subviews.firstObject;
                button.selected = YES;

                EffectModel *model = modelArray[0];
                self.slider.value = model.value;
            }
        } break;
        case 3: //背景分割
        {
            [self.buttonListView mas_updateConstraints:^(MASConstraintMaker *make) {
              make.top.equalTo(self.segment.mas_bottom).offset(36);
            }];

            self.sliderLabel.hidden = YES;
            self.slider.hidden = YES;

            // 之前选中过
            BOOL selected = NO;
            for (EffectButton *button in self.buttonListView.subviews) {
                if (button.model.selected) {
                    button.selected = YES;
                    selected = YES;
                }
            }

            if (selected == NO) {
                //之前没有选中过,默认第一个
                EffectButton *button = self.buttonListView.subviews.firstObject;
                button.selected = NO;
            }
        } break;
    }
}

#pragma mark - getter

- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.font = [UIFont systemFontOfSize:28];
        _titleLabel.text = @"特效";
    }
    return _titleLabel;
}

- (UISegmentedControl *)segment {
    if (!_segment) {
        _segment = [[UISegmentedControl alloc] initWithItems:[BeautyModel sectionList]];
        _segment.selectedSegmentIndex = 0;
        [_segment addTarget:self action:@selector(segmentValueChanged:) forControlEvents:UIControlEventValueChanged];
    }
    return _segment;
}

- (UISlider *)slider {
    if (!_slider) {
        _slider = [[UISlider alloc] init];
        [_slider addTarget:self action:@selector(sliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    }
    return _slider;
}

- (UIView *)buttonListView {
    if (!_buttonListView) {
        _buttonListView = [[UIView alloc] init];
    }
    return _buttonListView;
}

- (UILabel *)sliderLabel {
    if (!_sliderLabel) {
        _sliderLabel = [[UILabel alloc] init];
        _sliderLabel.font = [UIFont systemFontOfSize:17];
        _sliderLabel.text = @"美颜强度";
    }
    return _sliderLabel;
}

- (NSMutableArray<NSArray <EffectModel *> *> *)dataArray {
    if (!_dataArray) {
        _dataArray = [[NSMutableArray alloc] init];
    }
    return _dataArray;
}
@end
