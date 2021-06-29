//
//  ParticipantModel.m
//  SceneRTCDemo
//
//  Created by on 2021/3/10.
//

#import "ParticipantModel.h"

@implementation ParticipantModel

+ (ParticipantModel *)participantModelToMeetingControlUserModel:(MeetingControlUserModel *)meetingControlUserModel {
    ParticipantModel *participantModel = [[ParticipantModel alloc] init];
    RoomUserModel *roomUserModel = [RoomUserModel roomUserModelToMeetingControlUserModel:meetingControlUserModel];
    participantModel.roomUserModel = roomUserModel;
    return participantModel;
}

@end
