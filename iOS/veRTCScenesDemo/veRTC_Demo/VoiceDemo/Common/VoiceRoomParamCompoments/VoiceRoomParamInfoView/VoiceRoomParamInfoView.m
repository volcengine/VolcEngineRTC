//
//  VoiceRoomParamInfoView.m
//  veRTC_Demo
//
//  Created by  on 2021/4/9.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomParamInfoView.h"
#import "UIView+Fillet.h"

@interface VoiceRoomParamInfoView ()

@property (nonatomic, strong) NSMutableArray<UILabel *> *viewLists;

@end

@implementation VoiceRoomParamInfoView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor colorFromRGBHexString:@"#272E3B"];
        
        for (int i = 0; i < 7; i++) {
            UILabel *label = [[UILabel alloc] init];
            [self addSubview:label];
            [self.viewLists addObject:label];
        }
        [self.viewLists mas_distributeViewsAlongAxis:MASAxisTypeVertical withFixedSpacing:12
                                         leadSpacing:20
                                         tailSpacing:30 + [DeviceInforTool getVirtualHomeHeight]];
        [self.viewLists mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self).offset(20);
            make.right.equalTo(self).offset(-20);
        }];
        
        for (int i = 0; i < self.viewLists.count; i++) {
            UILabel *label = (UILabel *)self.viewLists[i];
            [self getMeessageWithModel:nil index:i label:label];
        }
    }
    return self;
}

#pragma mark - Publish Action

- (void)setParamInfoModel:(VoiceRoomParamInfoModel *)paramInfoModel {
    _paramInfoModel = paramInfoModel;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        for (int i = 0; i < self.viewLists.count; i++) {
            UILabel *label = (UILabel *)self.viewLists[i];
            [self getMeessageWithModel:paramInfoModel index:i label:label];
        }
    });
}

- (void)getMeessageWithModel:(VoiceRoomParamInfoModel *)paramInfoModel index:(NSInteger)index label:(UILabel *)label {
    NSString *title = @"";
    NSString *str = @"";
    switch (index) {
        case 0:
            title = @"音频上行声道数：";
            str = [NSString stringWithFormat:@"%@%@", title, [self stringEmpty:paramInfoModel.numChannels]];
            [self updateLabel:label allText:str title:title];
            break;
        case 1:
            title = @"音频上行采样率：";
            str = [NSString stringWithFormat:@"%@%@", title, [self stringEmpty:paramInfoModel.sentSampleRate]];
            [self updateLabel:label allText:str title:title];
            break;
        case 2:
            title = @"音频上行码率：";
            str = [NSString stringWithFormat:@"%@%@kbps", title, [self stringEmpty:paramInfoModel.sentKBitrate]];
            [self updateLabel:label allText:str title:title];
            break;
        case 3:
            title = @"音频上行丢包率：";
            str = [NSString stringWithFormat:@"%@%@%%", title, [self stringEmpty:paramInfoModel.audioLossRate]];
            [self updateLabel:label allText:str title:title];
            break;
        case 4:
            title = @"音频下行码率：";
            str = [NSString stringWithFormat:@"%@%@kbps", title, [self stringEmpty:paramInfoModel.recordKBitrate]];
            [self updateLabel:label allText:str title:title];
            break;
        case 5:
            title = @"音频下行丢包率：";
            str = [NSString stringWithFormat:@"%@%@%%", title, [self stringEmpty:paramInfoModel.recordLossRate]];
            [self updateLabel:label allText:str title:title];
            break;
        case 6:
            title = @"延迟：";
            str = [NSString stringWithFormat:@"%@%@ms", title, [self stringEmpty:paramInfoModel.rtt]];
            [self updateLabel:label allText:str title:title];
            break;
            
        default:
            break;
    }
}

#pragma mark - Private Action

- (void)updateLabel:(UILabel *)label allText:(NSString *)allText title:(NSString *)title {
    NSMutableAttributedString *textStr = [[NSMutableAttributedString alloc] initWithString:allText];
    NSRange range = [[textStr string] rangeOfString:title];
    NSRange range2 = NSMakeRange(range.length, allText.length - range.length);
    [textStr addAttribute:NSForegroundColorAttributeName value:[UIColor colorFromHexString:@"#86909C"] range:range];
    [textStr addAttribute:NSForegroundColorAttributeName value:[UIColor whiteColor] range:range2];

    label.attributedText = textStr;
}

- (NSString *)stringEmpty:(NSString *)str {
    return (IsEmptyStr(str)) ? @"0" : str;
}

- (void)maskButtonAction {
    
}

#pragma mark - getter

- (NSMutableArray *)viewLists {
    if (!_viewLists) {
        _viewLists = [[NSMutableArray alloc] init];
    }
    return _viewLists;
}

@end
