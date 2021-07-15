//
//  RoomParamInfoView.m
//  veRTC_Demo
//
//  Created by  on 2021/4/9.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "RoomParamInfoView.h"
#import "UIView+Fillet.h"
#import "GCDTimer.h"

@interface RoomParamInfoView ()

@property (nonatomic, strong) UIView *bgView;

@property (nonatomic, strong) NSMutableArray<UILabel *> *viewLists;

@property (nonatomic, strong) GCDTimer *timer;

@end

@implementation RoomParamInfoView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor colorFromRGBHexString:@"#1D2129" andAlpha:(0.5 * 255)];
        
        [self addSubview:self.bgView];
        
        for (int i = 0; i < 16; i++) {
            UILabel *label = [[UILabel alloc] init];
            [self updateLabel:label];
            [self addSubview:label];
            [self.viewLists addObject:label];
        }
        [self.viewLists mas_distributeViewsAlongAxis:MASAxisTypeVertical withFixedSpacing:6 leadSpacing:10 tailSpacing:10];
        [self.viewLists mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self).offset(10);
            make.right.equalTo(self).offset(-10);
        }];
        
        [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        for (int i = 0; i < self.viewLists.count; i++) {
            UILabel *label = (UILabel *)self.viewLists[i];
            label.text = [self getMeessageWithModel:nil index:i];
        }
        
        __weak __typeof(self) wself = self;
        [self.timer startTimerWithSpace:1.5 block:^(BOOL result) {
            [wself timerMethod];
        }];
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    [self.bgView filletWithRadius:15 corner:FilletStatusTopRight];
}

- (void)timerMethod {
    for (int i = 0; i < self.viewLists.count; i++) {
        UILabel *label = (UILabel *)self.viewLists[i];
        label.text = [self getMeessageWithModel:self.paramInfoModel index:i];
    }
}

#pragma mark - Publish Action

- (void)setParamInfoModel:(RoomParamInfoModel *)paramInfoModel {
    _paramInfoModel = paramInfoModel;

}

- (NSString *)getMeessageWithModel:(RoomParamInfoModel *)paramInfoModel index:(NSInteger)index {
    NSString *str = @"";
    switch (index) {
        case 0:
            str = @"[LOCAL]";
            break;
        case 1:
            str = @"RES：";
            str = [NSString stringWithFormat:@"%@%@", str, [self stringEmpty:paramInfoModel.local_res]];
            break;
        case 2:
            str = @"FPS：";
            str = [NSString stringWithFormat:@"%@%@", str, [self stringEmpty:paramInfoModel.local_fps]];
            break;
        case 3:
            str = @"BIT(VIDEO): ";
            str = [NSString stringWithFormat:@"%@%@kbps", str, [self stringEmpty:paramInfoModel.local_bit_video]];
            break;
        case 4:
            str = @"BIT(AUDIO):";
            str = [NSString stringWithFormat:@"%@%@kbps", str, [self stringEmpty:paramInfoModel.local_bit_audio]];
            break;
        case 5:
            str = @"";
            break;
        case 6:
            str = @"[REMOTE]";
            break;
        case 7:
            str = @"RTT(VIDEO)：";
            str = [NSString stringWithFormat:@"%@%@ms", str, [self stringEmpty:paramInfoModel.remote_rtt_video]];
            break;
        case 8:
            str = @"RTT(AUDIO)：";
            str = [NSString stringWithFormat:@"%@%@ms", str, [self stringEmpty:paramInfoModel.remote_rtt_audio]];
            break;
        case 9:
            str = @"CPU：";
            str = [NSString stringWithFormat:@"%@%@%%|%@%%", str, [self stringEmpty:paramInfoModel.remote_cpu_avg], [self stringEmpty:paramInfoModel.remote_cpu_max]];
            break;
        case 10:
            str = @"BIT(VIDEO):";
            str = [NSString stringWithFormat:@"%@%@kbps", str, [self stringEmpty:paramInfoModel.remote_bit_video]];
            break;
        case 11:
            str = @"BIT(AUDIO): ";
            str = [NSString stringWithFormat:@"%@%@kbps", str, [self stringEmpty:paramInfoModel.remote_bit_audio]];
            break;
        case 12:
            str = @"RES：";
            str = [NSString stringWithFormat:@"%@%@-%@", str, [self stringEmpty:paramInfoModel.remote_res_min], [self stringEmpty:paramInfoModel.remote_res_max]];
            break;
        case 13:
            str = @"FPS：";
            str = [NSString stringWithFormat:@"%@%@-%@", str, [self stringEmpty:paramInfoModel.remote_fps_min], [self stringEmpty:paramInfoModel.remote_fps_max]];
            break;
        case 14:
            str = @"LOSS（VEDIO）：";
            str = [NSString stringWithFormat:@"%@%@%%", str, [self stringEmpty:paramInfoModel.remote_loss_video]];
            break;
        case 15:
            str = @"LOSS(AUDIO)：";
            str = [NSString stringWithFormat:@"%@%@%%", str, [self stringEmpty:paramInfoModel.remote_loss_audio]];
            break;
            
        default:
            break;
    }
    return str;
}

#pragma mark - Private Action

- (void)updateLabel:(UILabel *)label {
    label.font = [UIFont systemFontOfSize:10 weight:UIFontWeightRegular];
    label.textColor = [UIColor whiteColor];
}

- (NSString *)stringEmpty:(NSString *)str {
    return (IsEmptyStr(str)) ? @"0" : str;
}

#pragma mark - getter

- (UIView *)bgView {
    if (!_bgView) {
        _bgView = [[UIView alloc] init];
        _bgView.backgroundColor = [UIColor colorFromRGBHexString:@"#1D2129" andAlpha:0.5 * 255];
    }
    return _bgView;
}

- (NSMutableArray *)viewLists {
    if (!_viewLists) {
        _viewLists = [[NSMutableArray alloc] init];
    }
    return _viewLists;
}

- (GCDTimer *)timer {
    if (!_timer) {
        _timer = [[GCDTimer alloc] init];
    }
    return _timer;
}

@end
