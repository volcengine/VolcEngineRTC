//
//  RoomUserModel.h
//  SceneRTCDemo
//
//  Created by on 2021/3/9.
//

#import <Foundation/Foundation.h>

@interface RoomUserModel : NSObject

- (instancetype)initWithUid:(NSString *)uid;

@property (nonatomic, copy) NSString *name;

@property (nonatomic, copy) NSString *roomId;

@property (nonatomic, assign) BOOL isHost;

@property (nonatomic, assign) BOOL isOneself;

//1 开启; 2关闭; 3说话中
//1 open; 2 close; 3 talking
@property (nonatomic, assign) NSInteger audioType;

@property (nonatomic, assign) BOOL isOpenVideo;

@property (nonatomic, assign) BOOL isOpenScreen;

@property (nonatomic, assign) BOOL isVideoStream;

@property (nonatomic, assign) BOOL isMaxVolume;

@property (nonatomic, strong) NSView *streamView;

//User volume information, the volume value range is [0, 255]
@property (nonatomic, assign) NSUInteger volume;

//Ranking factor
@property (nonatomic, assign) NSUInteger rankeFactor;

+ (RoomUserModel *)roomUserModelToMeetingControlUserModel:(MeetingControlUserModel *)meetingControlUserModel;

@end
