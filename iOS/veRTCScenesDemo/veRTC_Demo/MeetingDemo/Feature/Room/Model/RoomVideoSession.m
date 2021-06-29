//
//  RoomVideoSession.m
//  quickstart
//
//  Created by on 2021/4/2.
//  Copyright © 2021. All rights reserved.
//

#import "RoomVideoSession.h"

@implementation RoomVideoSession

- (instancetype)initWithUid:(NSString *)uid {
    self = [super init];
    if (self) {
        self.uid = uid;
    }
    return self;
}

- (UIView *)streamView {
    if (!_streamView) {
        _streamView = [[UIView alloc] init];
        ByteRtcVideoCanvas *byteRtcVideoCanvas = [[ByteRtcVideoCanvas alloc] init];
        byteRtcVideoCanvas.uid = self.uid;
        byteRtcVideoCanvas.renderMode = ByteRtc_Render_Hidden;
        byteRtcVideoCanvas.view.backgroundColor = [UIColor clearColor];
        byteRtcVideoCanvas.view = _streamView;
        if (self.isLoginUser) {
            //Local Video
            [[MeetingRTCManager shareRtc] setupLocalVideo:byteRtcVideoCanvas];
        } else {
            //Remote Video
            [[MeetingRTCManager shareRtc] setupRemoteVideo:byteRtcVideoCanvas];
        }
    }
    return _streamView;
}

+ (RoomVideoSession *)roomVideoSessionToMeetingControlUserModel:(MeetingControlUserModel *)meetingControlUserModel {
    RoomVideoSession *roomVideoSession = [[RoomVideoSession alloc] initWithUid:meetingControlUserModel.user_id];
    roomVideoSession.roomId = meetingControlUserModel.room_id;
    roomVideoSession.isScreen = meetingControlUserModel.is_sharing;
    roomVideoSession.isLoginUser = NO;
    roomVideoSession.isHost = meetingControlUserModel.is_host;

    roomVideoSession.audioType = meetingControlUserModel.is_mic_on ? 1 : 2;
    roomVideoSession.isEnableVideo = meetingControlUserModel.is_camera_on;
    return roomVideoSession;
}

@end
