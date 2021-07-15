//
//  ParamView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import "ParamView.h"

@interface ParamView ()

@property (nonatomic, strong) NSMutableArray<NSLabel *> *viewLists;

@property (nonatomic, strong) GCDTimer *timer;

@end

@implementation ParamView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColorWithHexString:@"#1D2129" andAlpha:(0.5 * 255)];
        
        for (int i = 0; i < 16; i++) {
            NSLabel *label = [[NSLabel alloc] init];
            [self updateLabel:label];
            [self addSubview:label];
            [self.viewLists addObject:label];
        }
        
        [self.viewLists mas_distributeViewsAlongAxis:MASAxisTypeVertical withFixedSpacing:8 leadSpacing:8 tailSpacing:8];
        [self.viewLists mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self).offset(8);
            make.right.equalTo(self).offset(-8);
        }];

        for (int i = 0; i < self.viewLists.count; i++) {
            NSLabel *label = (NSLabel *)self.viewLists[i];
            label.text = [self getMeessageWithModel:nil index:i];
        }
        
        __weak __typeof(self) wself = self;
        [self.timer startTimerWithSpace:1.5 block:^(BOOL result) {
            [wself timerMethod];
        }];
    }
    return self;
}

- (void)setParamModel:(ParamModel *)paramModel {
    _paramModel = paramModel;
}

- (void)timerMethod {
    for (int i = 0; i < self.viewLists.count; i++) {
        NSLabel *label = (NSLabel *)self.viewLists[i];
        label.text = [self getMeessageWithModel:self.paramModel index:i];
    }
}

- (NSString *)getMeessageWithModel:(ParamModel *)paramInfoModel index:(NSInteger)index {
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

- (void)updateLabel:(NSLabel *)label {
    label.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    label.textColor = [NSColor whiteColor];
}

- (NSString *)stringEmpty:(NSString *)str {
    return (IsEmptyStr(str)) ? @"0" : str;
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
