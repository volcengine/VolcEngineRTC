//
//  SetingViewController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import "SetingViewController.h"
#import "SetingView.h"

@interface SetingViewController ()<SetingViewDelegate>

@property (nonatomic, strong) NSButton *maskView;
@property (nonatomic, strong) SetingView *setingView;
@property (nonatomic, strong) SetingModel *setingModel;
@end

@implementation SetingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [[NSApplication sharedApplication].mainWindow makeFirstResponder:0];
    [self.view setBackgroundColor:[NSColor clearColor]];
    
    [self.view addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];

    [self.view addSubview:self.setingView];
    [self.setingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(720, 540));
        make.centerY.equalTo(self.view).offset(-60);
        make.centerX.equalTo(self.view);
    }];

    self.setingView.micInputDeviceLists = [self getMicInputDeviceLists];
    self.setingView.cameraInputDeviceLists = [self getCameraInputDeviceLists];
    self.setingView.setingModel = self.setingModel;
    [self loadDataWithHistoryVideoRecord];
}

#pragma mark - Publish Action

+ (BOOL)getParamSwitch {
    NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"SetingModelCacheKey"];
    SetingModel *setingModel = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    if (setingModel) {
        return setingModel.isOpenParam;
    } else {
        return NO;;
    }
}

#pragma mark - SetingViewDelegate

- (void)setingView:(SetingView *)setingView cancelAction:(BOOL)isCancel {
    if ([self.delegate respondsToSelector:@selector(setingViewController:cancelAction:)]) {
        [self.delegate setingViewController:self cancelAction:YES];
    }
}

- (void)setingView:(SetingView *)setingView confirmAction:(BOOL)isConfirm {
    //cache
    NSData *data = [NSKeyedArchiver archivedDataWithRootObject:self.setingModel];
    [[NSUserDefaults standardUserDefaults] setValue:data forKey:@"SetingModelCacheKey"];
    [[NSUserDefaults standardUserDefaults] synchronize];

    //update rtc sdk
    [[MeetingRTCManager shareMeetingRTCManager] setVideoProfiles:self.setingModel];
    [self updateDevice];
    
    //close view
    if ([self.delegate respondsToSelector:@selector(setingViewController:cancelAction:)]) {
        [self.delegate setingViewController:self cancelAction:YES];
    }
}

- (void)setingView:(SetingView *)setingView changeParam:(SetingModel *)setingModel {
    self.setingModel = setingModel;
}

#pragma mark - Private Action

- (void)loadDataWithHistoryVideoRecord {
    __weak __typeof(self) wself = self;
    [MeetingControlCompoments getHistoryVideoRecordWithBlock:^(NSArray<MeetingControlRecordModel *> * _Nonnull recordLists, MeetingControlAckModel * _Nonnull model) {
        NSMutableArray *lists = [[NSMutableArray alloc] init];
        NSMutableArray *hostLists = [[NSMutableArray alloc] init];
        for (int i = 0; i < recordLists.count; i++) {
            MeetingControlRecordModel *model = recordLists[i];
            if (model.video_holder) {
                [hostLists addObject:model];
            } else {
                [lists addObject:model];
            }
        }
        wself.setingView.historyVideoRecordLists = [lists copy];
        wself.setingView.historyHostVideoRecordLists = [hostLists copy];
    }];
}

- (void)updateDevice {
    NSString *selectDeviceID = self.setingModel.micInputDevice.deviceID;
    NSString *deviceID = [[MeetingRTCManager shareMeetingRTCManager] getMicDeviceID];
    if (NOEmptyStr(selectDeviceID) && ![selectDeviceID isEqualToString:deviceID]) {
        //Need to switch Mic equipment
        [[MeetingRTCManager shareMeetingRTCManager] setMicDevice:selectDeviceID];
    }
    
    NSString *selectCameraDeviceID = self.setingModel.cameraInputDevice.deviceID;
    NSString *currentCameraDeviceID = [[MeetingRTCManager shareMeetingRTCManager] getCameraDeviceID];
    if (NOEmptyStr(selectCameraDeviceID) && ![selectCameraDeviceID isEqualToString:currentCameraDeviceID]) {
        //Need to switch Camera equipment
        [[MeetingRTCManager shareMeetingRTCManager] setCameraDevice:selectCameraDeviceID];
    }
}

- (NSArray *)getMicInputDeviceLists {
    NSMutableArray *micInputDeviceLists = [[NSMutableArray alloc] init];
    ByteRtcAudioDeviceCollection *recordingDevicesLists = [[MeetingRTCManager shareMeetingRTCManager] getRecordingDevices];
    int cnt1 = [recordingDevicesLists getCount];
    for (int i = 0; i < cnt1; i ++) {
        NSString *deviceID = [[NSString alloc]init];
        NSString *deviceName= [[NSString alloc]init];
        [recordingDevicesLists getDevice:i DeviceName:&deviceName DeviceID:&deviceID];
        SetingDeviceModel *deviceModel = [[SetingDeviceModel alloc] init];
        deviceModel.deviceName = deviceName;
        deviceModel.deviceID = deviceID;
        [micInputDeviceLists addObject:deviceModel];
    }
    return [micInputDeviceLists copy];
}

- (NSArray *)getCameraInputDeviceLists {
    NSMutableArray *deviceLists = [[NSMutableArray alloc] init];
    ByteRtcVideoDeviceCollection *device = [[MeetingRTCManager shareMeetingRTCManager] getVideoDeviceDevices];
    int cnt1 = [device getCount];
    for (int i = 0; i < cnt1; i ++) {
        NSString *deviceID = [[NSString alloc]init];
        NSString *deviceName= [[NSString alloc]init];
        [device getDevice:i DeviceName:&deviceName DeviceID:&deviceID];
        SetingDeviceModel *deviceModel = [[SetingDeviceModel alloc] init];
        deviceModel.deviceName = deviceName;
        deviceModel.deviceID = deviceID;
        [deviceLists addObject:deviceModel];
    }
    return [deviceLists copy];
}

#pragma mark - getter

- (SetingView *)setingView {
    if (!_setingView) {
        _setingView = [[SetingView alloc] init];
        _setingView.delegate = self;
        _setingView.wantsLayer = YES;
        _setingView.layer.cornerRadius = 2;
        _setingView.layer.masksToBounds = YES;
    }
    return _setingView;
}

- (NSButton *)maskView {
    if (!_maskView) {
        _maskView = [[NSButton alloc] init];
        [_maskView setBackgroundColorWithHexString:@"000000" andAlpha:0.5 * 255];
    }
    return _maskView;
}

- (SetingModel *)setingModel {
    if (!_setingModel) {
        NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"SetingModelCacheKey"];
        SetingModel *setingModel = [NSKeyedUnarchiver unarchiveObjectWithData:data];
        if (setingModel) {
            _setingModel = setingModel;
        } else {
            _setingModel = [[SetingModel alloc] init];
        }
    }
    return _setingModel;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}



@end
