//
//  RoomUserModel.m
//  SceneRTCDemo
//
//  Created by on 2021/3/9.
//

#import "RoomUserModel.h"

@implementation RoomUserModel

- (instancetype)initWithUid:(NSString *)uid {
    self = [super init];
    if (self) {
        self.name = uid;
    }
    return self;
}

- (NSView *)streamView {
    if (!_streamView) {
        _streamView = [[NSView alloc] init];
        _streamView.hidden = YES;
        ByteRtcVideoCanvas *byteRtcVideoCanvas = [[ByteRtcVideoCanvas alloc] init];
        byteRtcVideoCanvas.uid = self.name;
        byteRtcVideoCanvas.renderMode = ByteRtc_Render_Hidden;
        byteRtcVideoCanvas.view.backgroundColor = [NSColor clearColor];
        byteRtcVideoCanvas.view = _streamView;
        if (self.isOneself) {
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
    roomUserModel.roomId = meetingControlUserModel.room_id;
    roomUserModel.isHost = meetingControlUserModel.is_host;
    roomUserModel.audioType = meetingControlUserModel.is_mic_on ? 1 : 2;
    roomUserModel.isOpenVideo = meetingControlUserModel.is_camera_on;
    roomUserModel.isOpenScreen = meetingControlUserModel.is_sharing;
    
    return roomUserModel;
}

@end
