//
//  ParticipantModel.h
//  SceneRTCDemo
//
//  Created by on 2021/3/10.
//

#import <Foundation/Foundation.h>
#import "RoomUserModel.h"
#import "MeetingControlUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ParticipantModel : NSObject

@property (nonatomic, strong) RoomUserModel *roomUserModel;

@property (nonatomic, assign) BOOL isTrack;

+ (ParticipantModel *)participantModelToMeetingControlUserModel:(MeetingControlUserModel *)meetingControlUserModel;

@end

NS_ASSUME_NONNULL_END
