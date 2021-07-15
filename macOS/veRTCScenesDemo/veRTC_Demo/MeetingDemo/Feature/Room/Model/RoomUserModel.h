//
//  RoomUserModel.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import <Foundation/Foundation.h>

@interface RoomUserModel : BaseUserModel

- (instancetype)initWithUid:(NSString *)uid;

@property (nonatomic, copy) NSString *userUniform;

@property (nonatomic, copy) NSString *roomId;

@property (nonatomic, assign) BOOL isHost;

@property (nonatomic, assign) BOOL isSelf;

@property (nonatomic, assign) BOOL isEnableMic;

@property (nonatomic, assign) BOOL isEnableCamera;

@property (nonatomic, assign) BOOL isOpenScreen;

@property (nonatomic, assign) BOOL isVideoStream;

@property (nonatomic, assign) BOOL isMaxVolume;

@property (nonatomic, strong) NSView *streamView;

//User volume information, the volume value range is [0, 255]
@property (nonatomic, assign) NSUInteger volume;

@property (nonatomic, assign) BOOL isTrack;

+ (RoomUserModel *)roomUserModelToMeetingControlUserModel:(MeetingControlUserModel *)meetingControlUserModel;

@end
