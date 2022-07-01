//
//  RoomSettingView.m
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "NotifyCommon.h"
#import "RoomSettingView.h"
#import "SettingView.h"

@interface RoomSettingView ()
@property (nonatomic, strong) SettingView *videoSettingView;
@property (nonatomic, strong) SettingView *renderSettingView;
@property (nonatomic, strong) SettingView *notifySettingView;
@end

@implementation RoomSettingView

- (instancetype)initWithRtcKit:(ByteRTCEngineKit *)rtcKit {
    if (self = [super init]) {
        self.backgroundColor = [UIColor whiteColor];

        [self addSubview:self.videoSettingView];
        [self.videoSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
          make.top.mas_equalTo(30);
          make.left.right.equalTo(self);
          make.height.mas_equalTo(185);
        }];
        self.videoSettingView.title = @"视频参数";

        __weak typeof(self) weakSelf = self;

        SettingSliderModel *bitRateModel = [[SettingSliderModel alloc] initWithMinValue:200 maxBitrate:1000 defaultValue:400];
        bitRateModel.title = @"码率";
        bitRateModel.suffix = @"kbps";
        [bitRateModel setSliderValueDidChanged:^(NSInteger value) {
          weakSelf.roomSetting.bitrate = value;
        }];

        NSArray *resolutionArray = @[ @"1080*1920",
                                      @"720*1280",
                                      @"540*960",
                                      @"480*640",
                                      @"480*480",
                                      @"360*640",
                                      @"240*320",
                                      @"180*320",
                                      @"160*160" ];

        SettingOptionArrayModel *resolutionModel = [[SettingOptionArrayModel alloc] initWithOptionArray:resolutionArray defaultIndex:5];
        resolutionModel.title = @"分辨率";
        [resolutionModel setDidSelectedIndex:^(NSInteger index, NSString *_Nonnull title) {
          [weakSelf updateBitrate:bitRateModel withResolutionIndex:index];
        }];

        SettingOptionArrayModel *fpsModel = [[SettingOptionArrayModel alloc] initWithOptionArray:@[ @"15fps", @"20fps", @"24fps" ] defaultIndex:0];
        fpsModel.title = @"帧率";
        [fpsModel setDidSelectedIndex:^(NSInteger index, NSString *_Nonnull title) {
          [weakSelf updateFps:index];
        }];

        self.videoSettingView.dataArray = @[ resolutionModel, fpsModel, bitRateModel ];

        [self addSubview:self.renderSettingView];
        [self.renderSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
          make.top.equalTo(self.videoSettingView.mas_bottom).offset(30);
          make.left.right.equalTo(self);
          make.height.mas_equalTo(95);
        }];
        self.renderSettingView.title = @"渲染设定";

        SettingOptionArrayModel *mirrorModel = [[SettingOptionArrayModel alloc] initWithOptionArray:@[ @"无镜像", @"渲染镜像", @"渲染和编码镜像" ] defaultIndex:1];
        mirrorModel.title = @"镜像模式";
        [mirrorModel setDidSelectedIndex:^(NSInteger index, NSString *_Nonnull title) {
          weakSelf.roomSetting.localRenderMirror = index;
        }];

        self.renderSettingView.dataArray = @[ mirrorModel ];

        //消息
        [self addSubview:self.notifySettingView];
        [self.notifySettingView mas_makeConstraints:^(MASConstraintMaker *make) {
          make.top.equalTo(self.renderSettingView.mas_bottom).offset(30);
          make.left.right.equalTo(self);
          make.height.mas_equalTo(140);
        }];
        self.notifySettingView.title = @"消息";

        SettingTextFieldModel *seiModel = [[SettingTextFieldModel alloc] initWithTitle:@"发送SEI消息" defaultStr:@""];
        seiModel.alertTitle = @"发送SEI消息";
        seiModel.alertMessage = @"你可以使用 SEI 信息实现多种场景，如歌词同步、布局切换等";
        seiModel.placeholders = @[ @"SEI 消息", @"重复次数" ];
        __weak __typeof(self) wself = self;
        __block NSString *notifyMessage = @"";
        seiModel.inputBlock = ^(NSInteger index, NSString *_Nonnull valueStr) {
          if (index == 0) {
              notifyMessage = valueStr;
          } else if (index == 1) {
              [wself sendSEIMessageRtcKit:rtcKit
                                  message:notifyMessage
                              repeatCount:[valueStr intValue]];
          }
        };

        SettingOptionArrayModel *timeModel = [[SettingOptionArrayModel alloc] initWithOptionArray:@[ @"二进制消息", @"文本消息" ] defaultIndex:-1];
        timeModel.title = @"发送实时消息";
        timeModel.describe = @"文本信息（如文字，用户名等，大小<62KB）\n二进制信息（如二维码，图片等，大小<46KB）";
        [timeModel setDidSelectedIndex:^(NSInteger index, NSString *_Nonnull title) {
          NotifyCommon *notifyCommon = [[NotifyCommon alloc] initWithType:(index == 0) ? NotifyStatusData : NotifyStatusText superView:wself rtcKit:rtcKit];
          [wself addSubview:notifyCommon];
          [notifyCommon mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(wself);
          }];
        }];

        self.notifySettingView.dataArray =
            @[
                seiModel,
                timeModel,
            ];
    }
    return self;
}

- (void)updateBitrate:(SettingSliderModel *)bitRateModel withResolutionIndex:(NSInteger)index {
    NSInteger minValue = 0;
    NSInteger maxValue = 0;
    NSInteger currentValue = bitRateModel.currentValue;

    CGSize resolution = CGSizeZero;

    switch (index) {
        case 0: {
            minValue = 800;
            maxValue = 3000;
            resolution = CGSizeMake(1080, 1920);
        } break;
        case 1: {
            minValue = 500;
            maxValue = 2000;
            resolution = CGSizeMake(720, 1280);
        } break;
        case 2: {
            minValue = 400;
            maxValue = 1600;
            resolution = CGSizeMake(540, 960);
        } break;
        case 3: {
            minValue = 250;
            maxValue = 1000;
            resolution = CGSizeMake(480, 640);
        } break;
        case 4: {
            minValue = 200;
            maxValue = 1000;
            resolution = CGSizeMake(480, 480);
        } break;
        case 5: {
            minValue = 200;
            maxValue = 1000;
            resolution = CGSizeMake(360, 640);
        } break;
        case 6: {
            minValue = 100;
            maxValue = 400;
            resolution = CGSizeMake(240, 320);
        } break;
        case 7: {
            minValue = 80;
            maxValue = 350;
            resolution = CGSizeMake(180, 320);
        } break;
        case 8: {
            minValue = 40;
            maxValue = 150;
            resolution = CGSizeMake(160, 160);
        } break;
        default: {
        } break;
    }

    bitRateModel.minValue = minValue;
    bitRateModel.maxValue = maxValue;
    bitRateModel.currentValue = currentValue;

    self.roomSetting.resolution = resolution;
    self.roomSetting.bitrate = currentValue;
}

- (void)updateFps:(NSInteger)index {
    NSInteger fps = 0;
    switch (index) {
        case 0: {
            fps = 15;
        } break;
        case 1: {
            fps = 20;
        } break;
        case 2: {
            fps = 24;
        } break;

        default: {
        } break;
    }
    self.roomSetting.fps = fps;
}

#pragma mark - Private Action

- (void)sendSEIMessageRtcKit:(ByteRTCEngineKit *)rtcKit
                     message:(NSString *)message
                 repeatCount:(int)repeatCount {
    NSData *data = [message dataUsingEncoding:NSUTF8StringEncoding];
    [rtcKit sendSEIMessage:ByteRTCStreamIndexMain andMessage:data andRepeatCount:repeatCount];
}

#pragma mark - getter

- (SettingView *)videoSettingView {
    if (!_videoSettingView) {
        _videoSettingView = [[SettingView alloc] init];
    }
    return _videoSettingView;
}

- (SettingView *)renderSettingView {
    if (!_renderSettingView) {
        _renderSettingView = [[SettingView alloc] init];
    }
    return _renderSettingView;
}

- (SettingView *)notifySettingView {
    if (!_notifySettingView) {
        _notifySettingView = [[SettingView alloc] init];
    }
    return _notifySettingView;
}
@end
