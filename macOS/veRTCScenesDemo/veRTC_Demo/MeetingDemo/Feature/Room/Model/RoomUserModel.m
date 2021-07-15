//
//  RoomUserModel.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import "RoomUserModel.h"

@implementation RoomUserModel

- (instancetype)initWithUid:(NSString *)uid {
    self = [super init];
    if (self) {
        self.uid = uid;
    }
    return self;
}

- (NSView *)streamView {
    if (!_streamView) {
        _streamView = [[NSView alloc] init];
        _streamView.hidden = YES;
        ByteRtcVideoCanvas *byteRtcVideoCanvas = [[ByteRtcVideoCanvas alloc] init];
        byteRtcVideoCanvas.uid = self.uid;
        byteRtcVideoCanvas.renderMode = ByteRtc_Render_Hidden;
        byteRtcVideoCanvas.view.backgroundColor = [NSColor clearColor];
        byteRtcVideoCanvas.view = _streamView;
        if (self.isSelf) {
            //Local Video
            [[MeetingRTCManager shareMeetingRTCManager] setupLocalVideo:byteRtcVideoCanvas];
        } else {
            //Remote Video
            [[MeetingRTCManager shareMeetingRTCManager] setupRemoteVideo:byteRtcVideoCanvas];
        }
    }
    return _streamView;
}

+ (RoomUserModel *)roomUserModelToMeetingControlUserModel:(MeetingControlUserModel *)meetingControlUserModel {
    RoomUserModel *roomUserModel = [[RoomUserModel alloc] initWithUid:meetingControlUserModel.user_id];
    roomUserModel.name = meetingControlUserModel.user_name;
    roomUserModel.roomId = meetingControlUserModel.room_id;
    roomUserModel.isHost = meetingControlUserModel.is_host;
    roomUserModel.isEnableMic = meetingControlUserModel.is_mic_on;
    roomUserModel.isEnableCamera = meetingControlUserModel.is_camera_on;
    roomUserModel.isOpenScreen = meetingControlUserModel.is_sharing;
    roomUserModel.userUniform = meetingControlUserModel.user_uniform_id;
    
    return roomUserModel;
}

- (BOOL)isSelf {
    if ([self.uid isEqualToString:[LocalUserCompoments userModel].uid]) {
        return YES;
    } else {
        return NO;
    }
}

- (BOOL)isVideoStream {
    if ([self.uid isEqualToString:[LocalUserCompoments userModel].uid]) {
        return YES;
    } else {
        return _isVideoStream;
    }
}

@end
