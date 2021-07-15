//
//  VoiceIMCompoments.m
//  veRTC_Demo
//
//  Created by  on 2021/5/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceIMCompoments.h"
#import "VoiceIMView.h"

@interface VoiceIMCompoments ()

@property (nonatomic, strong) VoiceIMView *voiceIMView;

@end

@implementation VoiceIMCompoments

- (instancetype)initWithSuperView:(UIView *)superView {
    self = [super init];
    if (self) {
        [superView addSubview:self.voiceIMView];
        [self.voiceIMView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(20);
            make.bottom.mas_equalTo(-10 - ([DeviceInforTool getVirtualHomeHeight] + 64));
            make.height.mas_equalTo(115);
            make.width.mas_equalTo(275);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)addIM:(VoiceIMModel *)model {
    NSMutableArray *datas = [[NSMutableArray alloc] initWithArray:self.voiceIMView.dataLists];
    [datas addObject:model];
    self.voiceIMView.dataLists = [datas copy];
}

#pragma mark - getter

- (VoiceIMView *)voiceIMView {
    if (!_voiceIMView) {
        _voiceIMView = [[VoiceIMView alloc] init];
    }
    return _voiceIMView;
}

@end
