//
//  SetingView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import "SetingView.h"
#import "MeetingSelectComponents.h"
#import "BitRateSelectView.h"
#import "MeetingBaseSetingComponents.h"
#import "MeetingMockDataCompoments.h"
#import "MeetingRecordComponents.h"
#import "BaseSilder.h"

@interface SetingView ()

@property (nonatomic, strong) NSView *navView;
@property (nonatomic, strong) NSView *bottomView;

@property (nonatomic, strong) MeetingSelectComponents *resolutionSelectView;
@property (nonatomic, strong) MeetingSelectComponents *frameRateSelectView;
@property (nonatomic, strong) BitRateSelectView *bitRateSelectView;

@property (nonatomic, strong) MeetingSelectComponents *screenResolutionSelectView;
@property (nonatomic, strong) MeetingSelectComponents *screenFrameRateSelectView;
@property (nonatomic, strong) BitRateSelectView *screenBitRateSelectView;

@property (nonatomic, strong) MeetingSelectComponents *micSelectView;
@property (nonatomic, strong) MeetingSelectComponents *cameraSelectView;
@property (nonatomic, strong) MeetingRecordComponents *pathSelectView;
@property (nonatomic, strong) MeetingRecordComponents *hostPathSelectView;
@property (nonatomic, strong) MeetingBaseSetingComponents *switchParamenterView;

@property (nonatomic, strong) NSMutableDictionary *dataDic;

@property (nonatomic, strong) SetingDeviceModel *currentMicInputDevice;
@property (nonatomic, strong) SetingDeviceModel *currentCameraInputDevice;

@end


@implementation SetingView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColor:[NSColor whiteColor]];
        
        [self addSubviewAndConstraints];

        __weak __typeof(self) wself = self;
        // Video
        self.resolutionSelectView.clickBlock = ^(NSString * _Nonnull key) {
            [wself changeParam];
        };
        self.frameRateSelectView.clickBlock = ^(NSString * _Nonnull key) {
            [wself changeParam];
        };
        self.bitRateSelectView.sliderValueChangedBlock = ^(NSInteger value) {
            [wself changeParam];
        };
        
        // Screnn
        self.screenResolutionSelectView.clickBlock = ^(NSString * _Nonnull key) {
            [wself changeParam];
        };
        self.screenFrameRateSelectView.clickBlock = ^(NSString * _Nonnull key) {
            [wself changeParam];
        };
        self.screenBitRateSelectView.sliderValueChangedBlock = ^(NSInteger value) {
            [wself changeParam];
        };

        // Device
        self.micSelectView.clickBlock = ^(NSString * _Nonnull key) {
            wself.currentMicInputDevice = [wself getSetingDeviceModelWithDeviceName:key isMic:YES];
            [wself changeParam];
        };
        self.cameraSelectView.clickBlock = ^(NSString * _Nonnull key) {
            wself.currentCameraInputDevice = [wself getSetingDeviceModelWithDeviceName:key isMic:NO];
            [wself changeParam];
        };
        self.pathSelectView.clickBlock = ^(NSString * _Nonnull key) {
            MeetingControlRecordModel *modle = [wself modelToTimerStr:key isHost:NO];
            if (key.length > 0 && modle) {
                [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:modle.download_url]];
            }
        };
        self.hostPathSelectView.clickBlock = ^(NSString * _Nonnull key) {
            MeetingControlRecordModel *modle = [wself modelToTimerStr:key isHost:YES];
            if (key.length > 0 && modle) {
                [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:modle.download_url]];
            }
        };
        self.hostPathSelectView.deleteBlock = ^(NSString * _Nonnull key) {
            __block MeetingControlRecordModel *modle = [wself modelToTimerStr:key isHost:YES];
            [MeetingControlCompoments deleteVideoRecord:modle.vid block:^(MeetingControlAckModel * _Nonnull ackModel) {
                if (ackModel.result) {
                    NSMutableArray *lists = [wself.hostPathSelectView.dataLists mutableCopy];
                    [lists removeObject:[wself getTimerStrWithModel:modle]];
                    wself.hostPathSelectView.dataLists = [lists copy];
                } else {
                    [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:ackModel.message];
                }
            }];
        };
    }
    return self;
}

#pragma mark - Publish Action

- (void)setSetingModel:(SetingModel *)setingModel {
    _setingModel = setingModel;

    //Video resolution
    self.resolutionSelectView.stringValue = [self getResolutionSizeKey:setingModel.resolutionSize.width
                                                                height:setingModel.resolutionSize.height];

    //Video frame rate
    self.frameRateSelectView.stringValue = [NSString stringWithFormat:@"%ld fps", (long)self.setingModel.frameRate];

    //Video bit rate
    NSDictionary *dic = self.dataDic[self.resolutionSelectView.stringValue];
    [self.bitRateSelectView updateMinValue:[dic[@"minBitRate"] floatValue]
                                  maxValue:[dic[@"maxBitRate"] floatValue]];
    [self.bitRateSelectView updateValue:setingModel.bitRate];
    
    //Screen resolution
    self.screenResolutionSelectView.stringValue = [self getResolutionSizeKey:setingModel.screenResolutionSize.width
                                                                      height:setingModel.screenResolutionSize.height];

    //Screen frame rate
    self.screenFrameRateSelectView.stringValue = [NSString stringWithFormat:@"%ld fps", (long)self.setingModel.screenFrameRate];

    //Screen bit rate
    NSDictionary *screenDic = self.dataDic[self.screenResolutionSelectView.stringValue];
    [self.screenBitRateSelectView updateMinValue:[screenDic[@"minBitRate"] floatValue]
                                        maxValue:[screenDic[@"maxBitRate"] floatValue]];
    [self.screenBitRateSelectView updateValue:setingModel.screenBitRate];

    //param switch
    NSSwitch *switchView = [self.switchParamenterView viewWithTag:3000];
    switchView.state = setingModel.isOpenParam ? NSControlStateValueOn : NSControlStateValueOff;
}

- (void)setMicInputDeviceLists:(NSArray<SetingDeviceModel *> *)micInputDeviceLists {
    _micInputDeviceLists = micInputDeviceLists;

    //microphone
    SetingDeviceModel *currentModel = nil;
    NSMutableArray *deviceNamelists = [[NSMutableArray alloc] init];
    for (int i = 0; i < micInputDeviceLists.count; i++) {
        SetingDeviceModel *deviceModel = micInputDeviceLists[i];
        [deviceNamelists addObject:deviceModel.deviceName];
        if ([deviceModel.deviceID isEqualToString:[[MeetingRTCManager shareMeetingRTCManager] getMicDeviceID]]) {
            currentModel = deviceModel;
        }
    }
    self.micSelectView.dataLists = [deviceNamelists copy];
    self.micSelectView.stringValue = currentModel.deviceName;
    self.currentMicInputDevice = currentModel;
    [self changeParam];
}

- (void)setCameraInputDeviceLists:(NSArray<SetingDeviceModel *> *)cameraInputDeviceLists {
    _cameraInputDeviceLists = cameraInputDeviceLists;

    //camera
    SetingDeviceModel *currentModel = nil;
    NSMutableArray *deviceNamelists = [[NSMutableArray alloc] init];
    for (int i = 0; i < cameraInputDeviceLists.count; i++) {
        SetingDeviceModel *deviceModel = cameraInputDeviceLists[i];
        [deviceNamelists addObject:deviceModel.deviceName];
        if ([deviceModel.deviceID isEqualToString:[[MeetingRTCManager shareMeetingRTCManager] getCameraDeviceID]]) {
            currentModel = deviceModel;
        }
    }
    self.cameraSelectView.dataLists = [deviceNamelists copy];
    self.cameraSelectView.stringValue = currentModel.deviceName;
    self.currentCameraInputDevice = currentModel;
    [self changeParam];
}

- (void)setHistoryVideoRecordLists:(NSArray<MeetingControlRecordModel *> *)historyVideoRecordLists {
    _historyVideoRecordLists = historyVideoRecordLists;

    NSMutableArray<NSString *> *pathLists = [[NSMutableArray alloc] init];
    for (int i = 0; i < historyVideoRecordLists.count; i++) {
        MeetingControlRecordModel *model = historyVideoRecordLists[i];
        [pathLists addObject:[self getTimerStrWithModel:model]];
    }
    //path
    self.pathSelectView.stringValue = @"选择历史会议点击链接查看";
    self.pathSelectView.dataLists = [pathLists copy];
}

- (void)setHistoryHostVideoRecordLists:(NSArray<MeetingControlRecordModel *> *)historyHostVideoRecordLists {
    _historyHostVideoRecordLists = historyHostVideoRecordLists;

    NSMutableArray<NSString *> *pathLists = [[NSMutableArray alloc] init];
    for (int i = 0; i < historyHostVideoRecordLists.count; i++) {
        MeetingControlRecordModel *model = historyHostVideoRecordLists[i];
        [pathLists addObject:[self getTimerStrWithModel:model]];
    }
    //path
    self.hostPathSelectView.stringValue = @"会议录制者有权在此处查看和删除录像";
    self.hostPathSelectView.dataLists = [pathLists copy];
}

- (NSString *)getTimerStrWithModel:(MeetingControlRecordModel *)model {
    NSInteger time = model.created_at / 1000000000;
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:time];
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    return [formatter stringFromDate:date];;
}

- (MeetingControlRecordModel *)modelToTimerStr:(NSString *)str isHost:(BOOL)isHost {
    MeetingControlRecordModel *cModel = nil;
    NSArray<MeetingControlRecordModel *> *lists = isHost ? self.historyHostVideoRecordLists : self.historyVideoRecordLists;
    for (MeetingControlRecordModel *model in lists) {
        NSString *timeStr = [self getTimerStrWithModel:model];
        if ([timeStr isEqualToString:str]) {
            cModel = model;
            break;
        }
    }
    return cModel;
}

- (void)changeParam {
    NSSwitch *switchView = [self.switchParamenterView viewWithTag:3000];
    
    // Video
    NSDictionary *dic = self.dataDic[self.resolutionSelectView.stringValue];
    self.setingModel.resolutionSize = NSMakeSize([dic[@"w"] floatValue], [dic[@"h"] floatValue]);
    self.setingModel.frameRate = [self.frameRateSelectView.stringValue floatValue];
    [self.bitRateSelectView updateMinValue:[dic[@"minBitRate"] floatValue]
                                  maxValue:[dic[@"maxBitRate"] floatValue]];
    self.setingModel.bitRate = self.bitRateSelectView.numValue;
    
    // Screen
    NSDictionary *screenDic = self.dataDic[self.screenResolutionSelectView.stringValue];
    self.setingModel.screenResolutionSize = NSMakeSize([screenDic[@"w"] floatValue], [screenDic[@"h"] floatValue]);
    self.setingModel.screenFrameRate = [self.screenFrameRateSelectView.stringValue floatValue];
    [self.screenBitRateSelectView updateMinValue:[screenDic[@"minBitRate"] floatValue]
                                        maxValue:[screenDic[@"maxBitRate"] floatValue]];
    self.setingModel.screenBitRate = self.screenBitRateSelectView.numValue;
    
    self.setingModel.isOpenParam = (switchView.state == NSControlStateValueOn) ? YES : NO;
    
    self.setingModel.micInputDevice = self.currentMicInputDevice;
    self.setingModel.cameraInputDevice = self.currentCameraInputDevice;
    
    if ([self.delegate respondsToSelector:@selector(setingView:changeParam:)]) {
        [self.delegate setingView:self changeParam:self.setingModel];
    }
}

- (void)cancelButtonAction {
    if ([self.delegate respondsToSelector:@selector(setingView:cancelAction:)]) {
        [self.delegate setingView:self cancelAction:YES];
    }
}

- (void)confirmButtonAction {
    if ([self.delegate respondsToSelector:@selector(setingView:confirmAction:)]) {
        [self.delegate setingView:self confirmAction:YES];
    }
}

- (void)switchVieAction:(NSSwitch *)switchView {
    [self changeParam];
}

#pragma mark - Private Action

- (NSArray *)getResolutionLists {
    NSMutableArray *lists = [[NSMutableArray alloc] init];
    NSArray *resolutionData = [MeetingMockDataCompoments sharedInstance].resolutionData;
    for (int i = 0; i < resolutionData.count; i++) {
        NSDictionary *dic = resolutionData[i];
        NSString *key = [self getResolutionSizeKey:[dic[@"w"] floatValue] height:[dic[@"h"] floatValue]];
        [lists addObject:key];
        [self.dataDic setValue:dic forKey:key];
    }
    return [lists copy];
}

- (SetingDeviceModel *)getSetingDeviceModelWithDeviceName:(NSString *)name isMic:(BOOL)isMic {
    SetingDeviceModel *model = nil;
    NSArray *lists = isMic ? self.micInputDeviceLists : self.cameraInputDeviceLists;
    for (int i = 0; i < lists.count; i++) {
        SetingDeviceModel *tempModel = lists[i];
        if ([tempModel.deviceName isEqualToString:name]) {
            model = tempModel;
            break;
        }
    }
    return model;
}

- (void)addSubviewAndConstraints {
    [self addSubview:self.navView];
    [self.navView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.right.mas_equalTo(self);
        make.height.mas_equalTo(46);
    }];

    [self addSubview:self.bottomView];
    [self.bottomView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.bottom.right.equalTo(self);
        make.height.mas_equalTo(70);
    }];

    [self addSubview:self.resolutionSelectView];
    [self.resolutionSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(120);
        make.top.equalTo(self.navView.mas_bottom).offset(20);
        make.size.mas_equalTo(CGSizeMake(160, 32));
    }];
    
    [self addSubview:self.frameRateSelectView];
    [self.frameRateSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.resolutionSelectView);
        make.top.equalTo(self.resolutionSelectView.mas_bottom).offset(20);
        make.size.mas_equalTo(CGSizeMake(160, 32));
    }];
    
    [self addSubview:self.bitRateSelectView];
    [self.bitRateSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.resolutionSelectView);
        make.top.equalTo(self.frameRateSelectView.mas_bottom).offset(20);
        make.size.mas_equalTo(CGSizeMake(96 + 8 + 56, 32));
    }];
    
    [self addSubview:self.screenResolutionSelectView];
    [self.screenResolutionSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(464);
        make.top.equalTo(self.resolutionSelectView);
        make.size.mas_equalTo(CGSizeMake(160, 32));
    }];
    
    [self addSubview:self.screenFrameRateSelectView];
    [self.screenFrameRateSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.screenResolutionSelectView);
        make.top.equalTo(self.frameRateSelectView);
        make.size.mas_equalTo(CGSizeMake(160, 32));
    }];
    
    [self addSubview:self.screenBitRateSelectView];
    [self.screenBitRateSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.screenResolutionSelectView);
        make.top.equalTo(self.bitRateSelectView);
        make.size.mas_equalTo(CGSizeMake(96 + 8 + 56, 32));
    }];
    
    [self addSubview:self.micSelectView];
    [self.micSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.resolutionSelectView);
        make.top.equalTo(self.bitRateSelectView.mas_bottom).offset(20);
        make.size.mas_equalTo(CGSizeMake(160, 32));
    }];
    
    [self addSubview:self.cameraSelectView];
    [self.cameraSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.resolutionSelectView);
        make.top.equalTo(self.micSelectView.mas_bottom).offset(20);
        make.size.mas_equalTo(CGSizeMake(160, 32));
    }];
    
    [self addSubview:self.pathSelectView];
    [self.pathSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.resolutionSelectView);
        make.top.equalTo(self.cameraSelectView.mas_bottom).offset(20);
        make.size.mas_equalTo(CGSizeMake(320, 32));
    }];
    
    [self addSubview:self.hostPathSelectView];
    [self.hostPathSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.resolutionSelectView);
        make.top.equalTo(self.pathSelectView.mas_bottom).offset(20);
        make.size.mas_equalTo(CGSizeMake(320, 32));
    }];

    [self addSubview:self.switchParamenterView];
    [self.switchParamenterView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.resolutionSelectView);
        make.top.equalTo(self.hostPathSelectView.mas_bottom).offset(20);
        make.size.mas_equalTo(CGSizeMake(160, 32));
    }];
}

- (NSString *)getResolutionSizeKey:(CGFloat)width height:(CGFloat)height {
    NSString *key = [NSString stringWithFormat:@"%ld * %ld", (long)width, (long)height];
    return key;
}

#pragma mark - getter

- (MeetingSelectComponents *)resolutionSelectView {
    if (!_resolutionSelectView) {
        _resolutionSelectView = [[MeetingSelectComponents alloc] init];
        _resolutionSelectView.title = @"分辨率";
        _resolutionSelectView.dataLists = [self getResolutionLists];
    }
    return _resolutionSelectView;
}

- (MeetingSelectComponents *)frameRateSelectView {
    if (!_frameRateSelectView) {
        _frameRateSelectView = [[MeetingSelectComponents alloc] init];
        _frameRateSelectView.title = @"帧率";
        _frameRateSelectView.dataLists = [MeetingMockDataCompoments sharedInstance].framerateData;
    }
    return _frameRateSelectView;
}

- (BitRateSelectView *)bitRateSelectView {
    if (!_bitRateSelectView) {
        _bitRateSelectView = [[BitRateSelectView alloc] init];
        _bitRateSelectView.title = @"码率";
        _bitRateSelectView.unitStr = @"kbps";
    }
    return _bitRateSelectView;
}

- (MeetingSelectComponents *)screenResolutionSelectView {
    if (!_screenResolutionSelectView) {
        _screenResolutionSelectView = [[MeetingSelectComponents alloc] init];
        _screenResolutionSelectView.title = @"屏幕共享分辨率";
        _screenResolutionSelectView.dataLists = [self getResolutionLists];
    }
    return _screenResolutionSelectView;
}

- (MeetingSelectComponents *)screenFrameRateSelectView {
    if (!_screenFrameRateSelectView) {
        _screenFrameRateSelectView = [[MeetingSelectComponents alloc] init];
        _screenFrameRateSelectView.title = @"屏幕共享帧率";
        _screenFrameRateSelectView.dataLists = [MeetingMockDataCompoments sharedInstance].framerateData;
    }
    return _screenFrameRateSelectView;
}

- (BitRateSelectView *)screenBitRateSelectView {
    if (!_screenBitRateSelectView) {
        _screenBitRateSelectView = [[BitRateSelectView alloc] init];
        _screenBitRateSelectView.title = @"屏幕共享码率";
        _screenBitRateSelectView.unitStr = @"kbps";
    }
    return _screenBitRateSelectView;
}

- (MeetingSelectComponents *)micSelectView {
    if (!_micSelectView) {
        _micSelectView = [[MeetingSelectComponents alloc] init];
        _micSelectView.title = @"麦克风";
        _micSelectView.dataLists = [MeetingMockDataCompoments sharedInstance].micInputDeviceData;
    }
    return _micSelectView;
}

- (MeetingSelectComponents *)cameraSelectView {
    if (!_cameraSelectView) {
        _cameraSelectView = [[MeetingSelectComponents alloc] init];
        _cameraSelectView.title = @"摄像头";
        _cameraSelectView.dataLists = [MeetingMockDataCompoments sharedInstance].cameraDeviceData;
    }
    return _cameraSelectView;
}

- (MeetingRecordComponents *)pathSelectView {
    if (!_pathSelectView) {
        _pathSelectView = [[MeetingRecordComponents alloc] init];
        _pathSelectView.title = @"查看历史会议";
        _pathSelectView.isDelete = NO;
    }
    return _pathSelectView;
}

- (MeetingRecordComponents *)hostPathSelectView {
    if (!_hostPathSelectView) {
        _hostPathSelectView = [[MeetingRecordComponents alloc] init];
        _hostPathSelectView.title = @"我的云录制";
        _hostPathSelectView.isDelete = YES;
    }
    return _hostPathSelectView;
}

- (MeetingBaseSetingComponents *)switchParamenterView {
    if (!_switchParamenterView) {
        _switchParamenterView = [[MeetingBaseSetingComponents alloc] init];
        _switchParamenterView.title = @"实时视频参数";

        NSSwitch *switchView = [[NSSwitch alloc] init];
        switchView.tag = 3000;
        switchView.state = NSControlStateValueOff;
        [switchView setTarget:self];
        [switchView setAction:@selector(switchVieAction:)];
        [_switchParamenterView addSubview:switchView];
        [switchView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.centerY.equalTo(_switchParamenterView);
        }];
    }
    return _switchParamenterView;
}

- (NSView *)navView {
    if (!_navView) {
        _navView = [[NSView alloc] init];
        [_navView setBackgroundColor:[NSColor clearColor]];

        NSLabel *label = [[NSLabel alloc] init];
        label.text = @"会议设置";
        label.font = [NSFont systemFontOfSize:14 weight:NSFontWeightMedium];
        label.textColor = [NSColor blackColor];
        [_navView addSubview:label];
        [label mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(_navView);
        }];

        NSView *lineView = [[NSView alloc] init];
        [lineView setBackgroundColorWithHexString:@"#E5E8EF"];
        [_navView addSubview:lineView];
        [lineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(1);
            make.left.right.bottom.equalTo(_navView);
        }];

        NSButton *cancelButton = [[NSButton alloc] init];
        [cancelButton setImage:[NSImage imageNamed:@"meeting_set_cancel"]];
        [cancelButton setBackgroundColor:[NSColor clearColor]];
        [_navView addSubview:cancelButton];
        [cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(13, 16));
            make.centerY.mas_equalTo(_navView);
            make.right.mas_equalTo(-16);
        }];
        [cancelButton setTarget:self];
        [cancelButton setAction:@selector(cancelButtonAction)];
    }
    return _navView;
}

- (NSView *)bottomView {
    if (!_bottomView) {
        _bottomView = [[NSView alloc] init];
        [_bottomView setBackgroundColor:[NSColor clearColor]];

        NSView *lineView = [[NSView alloc] init];
        [lineView setBackgroundColorWithHexString:@"#E5E8EF"];
        [_bottomView addSubview:lineView];
        [lineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(1);
            make.left.right.top.equalTo(_bottomView);
        }];

        NSButton *confirmButton = [[NSButton alloc] init];
        [confirmButton setTitleColor:@"#FFFFFF" title:@"完成"];
        [confirmButton setBackgroundColorWithHexString:@"#1664FF"];
        [_bottomView addSubview:confirmButton];
        [confirmButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(56, 32));
            make.centerY.equalTo(_bottomView);
            make.right.equalTo(_bottomView).offset(-20);
        }];
        [confirmButton setTarget:self];
        [confirmButton setAction:@selector(confirmButtonAction)];

        NSButton *cancelButton = [[NSButton alloc] init];
        [cancelButton setTitleColor:@"#1D2129" title:@"取消"];
        [cancelButton setBackgroundColorWithHexString:@"#F2F3F8"];
        [_bottomView addSubview:cancelButton];
        [cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(56, 32));
            make.centerY.mas_equalTo(_bottomView);
            make.right.equalTo(confirmButton.mas_left).offset(-12);
        }];
        [cancelButton setTarget:self];
        [cancelButton setAction:@selector(cancelButtonAction)];
        
       
    }
    return _bottomView;
}

- (NSMutableDictionary *)dataDic {
    if (!_dataDic) {
        _dataDic = [[NSMutableDictionary alloc] init];
    }
    return _dataDic;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}

@end
