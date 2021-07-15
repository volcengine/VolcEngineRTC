//
//  RoomViewController+Listener.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import "RoomViewController+Listener.h"

@implementation RoomViewController (Listener)

- (void)addSocketListener {
    __weak __typeof(self) wself = self;
    [MeetingControlCompoments onUserMicStatusChangeWithBlock:^(NSString * _Nonnull uid, BOOL result) {
        if (wself) {
            [wself updateRenderModeViewWithMicStatus:uid enableMic:result];
        }
    }];
    
    //Camera change
    [MeetingControlCompoments onUserCameraStatusChangeWithBlock:^(NSString * _Nonnull uid, BOOL result) {
        if (wself) {
            //update par ui
            [wself updateRenderModeViewWithCameraStatus:uid enableCamera:result];
        }
    }];
    
    //Mute all user microphone
    [MeetingControlCompoments onMuteAllWithBlock:^(BOOL result) {
        if (wself && ![wself.currentRoomModel.host_id isEqualToString:wself.localVideoSession.uid]) {
            ButtonStatus status = [wself.bottomView getButtonStatus:RoomBottomStatusMic];
            if (status == ButtonStatusNone) {
                [[MeetingRTCManager shareRtc] enableLocalAudio:NO];
                wself.localVideoSession.isEnableAudio = NO;
                [wself updateRenderModeViewWithMicStatus:wself.localVideoSession.uid enableMic:NO];
                [wself.bottomView updateButtonStatus:RoomBottomStatusMic close:YES];
                [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"你已被主持人静音"];
            }
        }
    }];

    //Microphone change group notice
    [MeetingControlCompoments onMuteUserWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            if ([uid isEqualToString:wself.localVideoSession.uid]) {
                ButtonStatus status = [wself.bottomView getButtonStatus:RoomBottomStatusMic];
                if (status == ButtonStatusNone) {
                    //Close microphone
                    [MeetingControlCompoments turnOffMic];
                    [[MeetingRTCManager shareRtc] enableLocalAudio:NO];
                    wself.localVideoSession.isEnableAudio = NO;
                    [wself updateRenderModeViewWithMicStatus:uid enableMic:NO];
                    [wself.bottomView updateButtonStatus:RoomBottomStatusMic close:YES];
                    [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"你已被主持人静音"];
                }
            }
        }
    }];

    //Asking Microphone On
    [MeetingControlCompoments onAskingMicOnWithBlock:^(NSString * _Nonnull uid) {
        if (wself && [uid isEqualToString:wself.localVideoSession.uid]) {
            //Open microphone
            AlertActionModel *alertCancelModel = [[AlertActionModel alloc] init];
            alertCancelModel.title = @"取消";
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = @"确定";
            alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
                if ([action.title isEqualToString:@"确定"]) {
                    [MeetingControlCompoments turnOnMic];
                    [[MeetingRTCManager shareRtc] enableLocalAudio:YES];
                    wself.localVideoSession.isEnableAudio = YES;
                    [wself updateRenderModeViewWithMicStatus:uid enableMic:YES];
                    [wself.bottomView updateButtonStatus:RoomBottomStatusMic close:NO];
                }
            };
            [[AlertActionManager shareAlertActionManager] showWithMessage:@"主持人邀请你打开麦克风" actions:@[alertCancelModel, alertModel]];
        }
    }];

    //Host
    [MeetingControlCompoments onHostChangeWithBlock:^(NSString * _Nonnull formerHostUid, NSString * _Nonnull hostUid) {
        if (wself) {
            //update par and render ui
            wself.currentRoomModel.host_id = hostUid;
            [wself updateRenderModeViewWithHost:hostUid];
        }
    }];

    //User Join
    [MeetingControlCompoments onUserJoinMeetingWithBlock:^(MeetingControlUserModel * _Nonnull model) {
        if (wself) {
            RoomVideoSession *roomUserModel = [RoomVideoSession roomVideoSessionToMeetingControlUserModel:model];
            if (![roomUserModel.uid isEqualToString:wself.localVideoSession.uid]) {
                [wself addUser:roomUserModel];
            }
        }
    }];

    //User Leave
    [MeetingControlCompoments onUserLeaveMeetingWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            [wself removeUser:uid];
        }
    }];
    
    //User Kicked Off
    [MeetingControlCompoments onUserKickedOffWithBlock:^(BOOL result) {
        if (wself) {
            [wself hangUp];
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = @"确定";
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                [[AlertActionManager shareAlertActionManager] showWithMessage:@"相同ID用户已登录，您已被强制下线！" actions:@[alertModel]];
            });
        }
    }];

    //Record
    [MeetingControlCompoments onRecordWithBlock:^(BOOL result) {
        if (wself) {
            wself.currentRoomModel.record = result;
            [wself updateRecordTipStatusWithHidden:NO];
            [wself.bottomView updateButtonStatus:RoomBottomStatusRecord close:YES];
        }
    }];

    //Share screen
    [MeetingControlCompoments onShareScreenStatusChangedWithBlock:^(NSString * _Nonnull uid, BOOL result) {
        if (wself) {
            //uid
            dispatch_async(dispatch_get_main_queue(), ^{
                wself.currentRoomModel.screen_shared_uid = result ? uid : @"";
                [wself updateModeWithStatus:result ? RoomModeStatusSpaker : RoomModeStatusGallery];
                [wself updateRenderModeViewWithScreenStatus:uid enableScreen:result];
                [wself.bottomView updateButtonStatus:RoomBottomStatusScreen close:result];
                if (!result) {
                    //Close screen sharing needs to restore orientation
                    [wself restoreScreenOrientation];
                }
            });
        }
    }];

    //Meeting end
    [MeetingControlCompoments onMeetingEndWithBlock:^(BOOL result) {
        if (wself) {
            [wself hangUp];
        }
    }];
    
}

@end
