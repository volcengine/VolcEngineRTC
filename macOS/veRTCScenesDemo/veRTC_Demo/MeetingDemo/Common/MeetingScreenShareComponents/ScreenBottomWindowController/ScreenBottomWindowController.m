//
//  ScreenBottomWindowController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/28.
//

#import "ScreenBottomWindowController.h"
#import "RoomBottomBarView.h"
#import "AppDelegate.h"

@interface ScreenBottomWindowController () <RoomBottomBarViewDelegate>

@property (nonatomic, strong) RoomBottomBarView *roomBottomBarView;

@end

@implementation ScreenBottomWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
    self.window.contentView.wantsLayer = YES;
    self.window.contentView.layer.masksToBounds = NO;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateRoomRecord:) name:NoticeUpdateRoomRecordName object:nil];
    
    [self.window.contentView addSubview:self.roomBottomBarView];
    [self.roomBottomBarView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.bottom.equalTo(self.window.contentView);
        make.height.mas_equalTo(48);
    }];
    
    [self.roomBottomBarView updateButtonStatus:BottomBarStatusMic close:!self.loginModel.isEnableAudio];
    [self.roomBottomBarView updateButtonStatus:BottomBarStatusVideo close:!self.loginModel.isEnableVideo];
    [self.roomBottomBarView updateButtonStatus:BottomBarStatusScreenShare close:YES];
    [self.roomBottomBarView updateButtonStatus:BottomBarStatusRecord close:self.roomModel.record];
}

#pragma mark - NSNotificationCenter

- (void)updateRoomRecord:(NSNotification *)notification {
    NSNumber *isRecord = (NSNumber *)notification.object;
    [self.roomBottomBarView updateButtonStatus:BottomBarStatusRecord close:[isRecord boolValue]];
}

#pragma mark - RoomBottomBarViewDelegate

- (void)roomBottomBarView:(RoomBottomBarView *)roomBottomBarView didSelectItemsAtButton:(RoomBottomBarModel *)roomBottomBarModel button:(nonnull TrackButton *)button {
    switch (roomBottomBarModel.status) {
        case BottomBarStatusMic:
            button.isClose = !button.isClose;
            button.tipTitle = button.isClose ? @"麦克风" : @"麦克风";
            
            //sdk api
            [[MeetingRTCManager shareMeetingRTCManager] enableLocalAudio:!button.isClose];
            
            //socket api
            if (button.isClose) {
                [MeetingControlCompoments turnOffMic];
            } else {
                [MeetingControlCompoments turnOnMic];
            }
            [[NSNotificationCenter defaultCenter] postNotificationName:NoticeScreenUpdateRoomMicName object:@(button.isClose)];
            break;
        case BottomBarStatusVideo:
            button.isClose = !button.isClose;
            button.tipTitle = button.isClose ? @"摄像头" : @"摄像头";
            
            //sdk api
            [[MeetingRTCManager shareMeetingRTCManager] enableLocalVideo:!button.isClose];
            
            //socket api
            if (button.isClose) {
                [MeetingControlCompoments turnOffCamera];
            } else {
                [MeetingControlCompoments turnOnCamera];
            }
            [[NSNotificationCenter defaultCenter] postNotificationName:NoticeScreenUpdateRoomCameraName object:@(button.isClose)];
            break;
        case BottomBarStatusScreenShare:
            if (button.isClose) {
                [MeetingControlCompoments endShareScreen];
                [[MeetingRTCManager shareMeetingRTCManager] stopScreenCapture];
                AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
                [(WindowManager *)(appDelegate.windowManager) showMeetingWindowController:NO];
            }
            break;
        case BottomBarStatusRecord:
            if (!button.isClose) {
                if ([self.roomModel.host_id isEqualToString:[LocalUserCompoments userModel].uid]) {
                    button.isClose = YES;
                    [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomRecordName object:@(button.isClose)];
                    [[NSNotificationCenter defaultCenter] postNotificationName:NoticeScreenBottomStartRecordName object:nil];
                } else {
                    [self showToastWindow:@"如需录制会议，请提醒主持人开启录制。"];
                }
            }
            break;
        case BottomBarStatusPeople:
            [self showToastWindow:@"停止屏幕共享后可查看参会者列表"];
            break;
        case BottomBarStatusSeting:
            [self showToastWindow:@"停止屏幕共享后可进入会议设置页"];
            break;
        case BottomBarStatusHangUp:
            [[NSNotificationCenter defaultCenter] postNotificationName:NoticeShowEndWindowName object:nil];
            break;
            
        default:
            break;
    }
}

- (void)showToastWindow:(NSString *)message {
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    [(WindowManager *)(appDelegate.windowManager) showToastWindowController:message];
}

#pragma mark - getter

- (RoomBottomBarView *)roomBottomBarView {
    if (!_roomBottomBarView) {
        _roomBottomBarView = [[RoomBottomBarView alloc] initWithStatus:RoomBottomBarStatsuScreen];
        _roomBottomBarView.delegate = self;
    }
    return _roomBottomBarView;
}

@end
