//
//  RoomVideoSession.h
//  quickstart
//
//  Created by  on 2021/4/2.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

static const NSInteger MaxAvatarNumber = 6;

@interface RoomVideoSession : NSObject

@property (nonatomic, copy) NSString *uid;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *userUniform;
@property (nonatomic, copy) NSString *roomId;
@property (nonatomic, assign) BOOL isScreen;
@property (nonatomic, assign) BOOL isLoginUser;
@property (nonatomic, assign) BOOL isHost;
@property (nonatomic, assign) BOOL isEnableVideo;
@property (nonatomic, assign) BOOL isEnableAudio;
@property (nonatomic, assign) BOOL isVideoStream;
@property (nonatomic, strong) UIView *streamView;
@property (nonatomic, assign) NSUInteger volume;
@property (nonatomic, copy) NSString *token;
@property (nonatomic, copy) NSString *appid;

/*
 * Sorting rules: the host ranks first, himself ranks second,
 and then is sorted by volume, and the rest is sorted by user joining time
 */
@property (nonatomic, assign) NSInteger rankeFactor;

/*
 * Max volume user
 */
@property (nonatomic, assign) BOOL isMaxVolume;

- (instancetype)initWithUid:(NSString *)uid;

+ (RoomVideoSession *)roomVideoSessionToMeetingControlUserModel:(MeetingControlUserModel *)meetingControlUserModel;

@end

