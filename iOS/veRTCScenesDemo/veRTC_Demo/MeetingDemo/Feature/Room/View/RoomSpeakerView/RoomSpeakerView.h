//
//  RoomSpeakerView.h
//  quickstart
//
//  Created by  on 2021/3/25.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface RoomSpeakerView : UIView

@property (nonatomic, strong) RoomVideoSession *localVideoSession;

@property (nonatomic, strong) MeetingControlRoomModel *currentRoomModel;

@property (nonatomic, copy) void (^clickOrientationBlock)(void);

@property (nonatomic, copy) void (^clickCloseBlock)(void);

@property (nonatomic, assign) BOOL isLandscape;

@property (nonatomic, copy) NSString *screenStreamsUid;

- (void)bindVideoSessions:(NSArray<RoomVideoSession *> *)videoSessions;

@end

