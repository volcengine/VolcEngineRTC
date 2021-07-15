//
//  ParticipantCell.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import <Cocoa/Cocoa.h>
#import "RoomUserModel.h"

@interface ParticipantCell : NSTableCellView

@property (nonatomic, assign) BOOL isLoginHost;

@property (nonatomic, strong) RoomUserModel *roomUserModel;

@property (nonatomic, copy) void (^clickChangeHost)(NSString *uid, NSString *name);

@property (nonatomic, copy) void (^moveTrackBlock)(NSString *uid);

@end
