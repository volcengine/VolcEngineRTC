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
        //update par ui
        if (wself) {
            [wself updateRenderModeViewWithCameraStatus:uid enableCamera:result];
        }
    }];
    
    //Mute all user microphone
    [MeetingControlCompoments onMuteAllWithBlock:^(BOOL result) {
        if (wself) {
            //update self
            if (![wself.currentRoomModel.host_id isEqualToString:[LocalUserCompoments userModel].uid]) {
                if (wself.loginModel.isEnableAudio) {
                    wself.loginModel.isEnableAudio = NO;
                    [wself updateRenderModeViewWithMicStatus:[LocalUserCompoments userModel].uid enableMic:NO];
                    [[MeetingRTCManager shareMeetingRTCManager] enableLocalAudio:NO];
                    [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"你已被主持人静音"];
                    [wself.roomBottomBarView updateButtonStatus:BottomBarStatusMic close:YES];
                }
            }
            //update all user
            [wself updateRenderModeViewWithMicStatus:@"" enableMic:NO];
        }
    }];

    //Microphone change group notice
    [MeetingControlCompoments onMuteUserWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            if ([uid isEqualToString:[LocalUserCompoments userModel].uid]) {
                //Close microphone
                wself.loginModel.isEnableAudio = NO;
                [MeetingControlCompoments turnOffMic];
                [wself updateRenderModeViewWithMicStatus:uid enableMic:NO];
                [[MeetingRTCManager shareMeetingRTCManager] enableLocalAudio:NO];
                [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"你已被主持人静音"];
                [wself.roomBottomBarView updateButtonStatus:BottomBarStatusMic close:YES];
            }
        }
    }];


    //Asking Microphone On
    [MeetingControlCompoments onAskingMicOnWithBlock:^(NSString * _Nonnull uid) {
        if (wself && [uid isEqualToString:[LocalUserCompoments userModel].uid]) {
            //Open microphone
            [[MeetingAlertCompoments share] showWithTitle:@"主持人邀请你打开麦克风" clickBlock:^(BOOL result) {
                if (result) {
                    wself.loginModel.isEnableAudio = YES;
                    [MeetingControlCompoments turnOnMic];
                    [wself updateRenderModeViewWithMicStatus:uid enableMic:YES];
                    [[MeetingRTCManager shareMeetingRTCManager] enableLocalAudio:YES];
                    [wself.roomBottomBarView updateButtonStatus:BottomBarStatusMic close:NO];
                }
            }];
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
            RoomUserModel *roomUserModel = [RoomUserModel roomUserModelToMeetingControlUserModel:model];
            if (![roomUserModel.uid isEqualToString:[LocalUserCompoments userModel].uid]) {
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
            [wself meetingEnd];
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"相同ID用户已登录，您已被强制下线！"];
        }
    }];

    //Record
    [MeetingControlCompoments onRecordWithBlock:^(BOOL result) {
        if (wself) {
            wself.currentRoomModel.record = result;
            [wself.roomBottomBarView updateButtonStatus:BottomBarStatusRecord close:YES];
            [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomRecordName object:@(YES)];
        }
    }];

    //Share screen
    [MeetingControlCompoments onShareScreenStatusChangedWithBlock:^(NSString * _Nonnull uid, BOOL result) {
        if (wself) {
            //uid
            dispatch_async(dispatch_get_main_queue(), ^{
                wself.currentRoomModel.screen_shared_uid = result ? uid : @"";
                if (!result || ![uid isEqualToString:[LocalUserCompoments userModel].uid]) {
                    [wself updateModeWithStatus:result ? RoomModeStatusSpaker : RoomModeStatusGallery];
                }
                [wself updateRenderModeViewWithScreenStatus:uid enableScreen:result];
                [wself.roomBottomBarView updateButtonStatus:BottomBarStatusScreenShare close:result];
            });
        }
    }];

    //Meeting end
    [MeetingControlCompoments onMeetingEndWithBlock:^(BOOL result) {
        if (wself) {
            [wself meetingEnd];
        }
    }];
}

- (void)meetingEnd {
    if ([self.currentRoomModel.screen_shared_uid isEqualToString:[LocalUserCompoments userModel].uid]) {
        //User screen sharing
        [[NSNotificationCenter defaultCenter] postNotificationName:NoticeCloseEndWindowName object:@"leave"];
    } else {
        [self hangUpAction];
    }
    if (![self.currentRoomModel.host_id isEqualToString:[LocalUserCompoments userModel].uid]) {
        //host does not need to be toast
    }
}

@end
