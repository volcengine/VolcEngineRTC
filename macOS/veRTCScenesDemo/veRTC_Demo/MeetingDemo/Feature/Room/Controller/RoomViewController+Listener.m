//
//  RoomViewController+Listener.m
//  SceneRTCDemo
//
//  Created by on 2021/3/16.
//

#import "RoomViewController+Listener.h"

@implementation RoomViewController (Listener)

- (void)addSocketListener {
    __weak __typeof(self) wself = self;
    [MeetingControlCompoments onUserMicStatusChangeWithBlock:^(NSString * _Nonnull uid, BOOL result) {
        //update par ui
        if (wself && wself.participantViewController) {
            [wself.participantViewController updateUserMicStatus:result uid:uid];
        }
        [wself updateRenderModeViewWithMicStatus:uid enableMic:result];
    }];

    //Microphone change group notice
    [MeetingControlCompoments onMuteUserWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            if ([uid isEqualToString:wself.loginModel.uid]) {
                //Close microphone
                wself.loginModel.isEnableAudio = NO;
                [MeetingControlCompoments turnOffMic];
                [[MeetingRTCManager shareMeetingRTCManager] enableLocalAudio:NO];
                [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"你已被主持人静音"];
                [wself.roomBottomBarView updateButtonStatus:BottomBarStatusMic close:YES];
            }
            //update par ui
            if (wself.participantViewController) {
                [wself.participantViewController updateUserMicStatus:NO uid:uid];
            }

        }
    }];

    //Camera change
    [MeetingControlCompoments onUserCameraStatusChangeWithBlock:^(NSString * _Nonnull uid, BOOL result) {
        //update par ui
        if (wself) {
            if (wself.participantViewController) {
                [wself.participantViewController updateUserCameraStatus:result uid:uid];
            }
            [wself updateRenderModeViewWithCameraStatus:uid enableCamera:result];
        }
    }];

    //Asking Microphone On
    [MeetingControlCompoments onAskingMicOnWithBlock:^(NSString * _Nonnull uid) {
        if (wself && [uid isEqualToString:wself.loginModel.uid]) {
            //Open microphone
            [[MeetingAlertCompoments share] showWithTitle:@"主持人邀请你打开麦克风" clickBlock:^(BOOL result) {
                if (result) {
                    [MeetingControlCompoments turnOnMic];
                    [[MeetingRTCManager shareMeetingRTCManager] enableLocalAudio:YES];
                    wself.loginModel.isEnableAudio = YES;
                    [wself updateRenderModeViewWithMicStatus:uid enableMic:YES];
                    [wself.roomBottomBarView updateButtonStatus:BottomBarStatusMic close:NO];
                    if (wself.participantViewController) {
                        [wself.participantViewController updateUserMicStatus:YES uid:uid];
                    }
                }
            }];
        }
    }];

    //Host
    [MeetingControlCompoments onHostChangeWithBlock:^(NSString * _Nonnull formerHostUid, NSString * _Nonnull hostUid) {
        if (wself) {
            //update par and render ui
            wself.currentRoomModel.host_id = hostUid;
            [wself updateCurrentUserListHostStatus];
            [wself updateRenderModeViewUserRankeWithAudioVolume:nil];
            wself.participantViewController.isLoginHost = [wself.loginModel.uid isEqualToString:hostUid] ? YES : NO;
            [wself.participantViewController updateUserHostStatusWithUid:hostUid];
        }
    }];

    //Mute all user microphone
    [MeetingControlCompoments onMuteAllWithBlock:^(BOOL result) {
        if (wself) {
            if (![wself.currentRoomModel.host_id isEqualToString:wself.loginModel.uid]) {
                if (wself.loginModel.isEnableAudio) {
                    wself.loginModel.isEnableAudio = NO;
                    [wself updateRenderModeViewWithMicStatus:wself.loginModel.uid enableMic:NO];
                    [[MeetingRTCManager shareMeetingRTCManager] enableLocalAudio:NO];
                    [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"你已被主持人静音"];
                    [wself.roomBottomBarView updateButtonStatus:BottomBarStatusMic close:YES];
                }
            }
            [wself.participantViewController updateUserMicStatus:NO uid:@""];
        }
    }];

    //User Join
    [MeetingControlCompoments onUserJoinMeetingWithBlock:^(MeetingControlUserModel * _Nonnull model) {
        if (wself) {
            RoomUserModel *roomUserModel = [RoomUserModel roomUserModelToMeetingControlUserModel:model];
            if (![roomUserModel.name isEqualToString:wself.loginModel.uid]) {
                [wself addUser:roomUserModel];
            }
            [wself.participantViewController loadDataWithGetMeetingUserInfo];
        }
    }];

    //User Leave
    [MeetingControlCompoments onUserLeaveMeetingWithBlock:^(NSString * _Nonnull uid) {
        [wself removeUser:uid];
        [wself.participantViewController loadDataWithGetMeetingUserInfo];
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
                if (!result || ![uid isEqualToString:wself.loginModel.uid]) {
                    [wself updateModeWithStatus:result ? RoomModeStatusSpaker : RoomModeStatusGallery];
                }
                [wself updateRenderModeViewWithScreenStatus:uid enableScreen:result];
                [wself.participantViewController updateUserScreenStatus:result uid:uid];
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
    if ([self.currentRoomModel.screen_shared_uid isEqualToString:self.loginModel.uid]) {
        //User screen sharing
        [[NSNotificationCenter defaultCenter] postNotificationName:NoticeCloseEndWindowName object:@"leave"];
    } else {
        [self hangUpAction];
    }
    if (![self.currentRoomModel.host_id isEqualToString:self.loginModel.uid]) {
        //host does not need to be toast
    }
}

@end
