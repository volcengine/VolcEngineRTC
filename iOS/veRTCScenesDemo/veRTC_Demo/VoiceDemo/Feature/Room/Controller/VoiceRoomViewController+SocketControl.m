//
//  VoiceRoomViewController+SocketControl.m
//  veRTC_Demo
//
//  Created by  on 2021/5/28.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomViewController+SocketControl.h"

@implementation VoiceRoomViewController (SocketControl)

- (void)addSocketListener {
    __weak __typeof(self) wself = self;
    [VoiceControlCompoments onJoinMeetingWithBlock:^(VoiceControlUserModel * _Nonnull userModel) {
        if (wself) {
            [wself addUser:userModel];
        }
    }];
    
    [VoiceControlCompoments onLeaveMeetingWithBlock:^(VoiceControlUserModel * _Nonnull userModel) {
        if (wself) {
            [wself removeUser:userModel];
        }
    }];

    [VoiceControlCompoments onRaiseHandsMicWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            //Received notification of raising hands
            [wself receivedRaiseHandWithUser:uid];
        }
    }];
    
    [VoiceControlCompoments onInviteMicWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            //The audience receives the invitation to the microphone notification
            [wself receivedRaiseHandInviteWithAudience];
        }
    }];
    
    [VoiceControlCompoments onMicOnWithBlock:^(VoiceControlUserModel * _Nonnull userModel) {
        if (wself) {
            //Notification of successful user registration
            [wself receivedRaiseHandSucceedWithUser:userModel];
        }
    }];
    
    [VoiceControlCompoments onMicOffWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            //Notification of successful user downloading
            [wself receivedLowerHandSucceedWithUser:uid];
        }
    }];
    
    [VoiceControlCompoments onMuteMicWithBlock:^(NSString * _Nonnull uid) {
        if (wself) {
            [wself receivedMicChangeWithMute:YES uid:uid];
        }
    }];
    
    [VoiceControlCompoments onUnmuteMic:^(NSString * _Nonnull uid) {
        if (wself) {
            [wself receivedMicChangeWithMute:NO uid:uid];
        }
    }];
    
    [VoiceControlCompoments onHostChange:^(NSString * _Nonnull formerHostID, VoiceControlUserModel *hostUser) {
        if (wself) {
            [wself receivedHostChangeWithNewHostUid:hostUser];
        }
    }];

    [VoiceControlCompoments onMeetingEnd:^(BOOL result) {
        if (wself) {
            [wself hangUp];
        }
    }];
}
@end
