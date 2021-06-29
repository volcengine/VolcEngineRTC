//
//  ParticipantCell.h
//  SceneRTCDemo
//
//  Created by on 2021/3/10.
//

#import <Cocoa/Cocoa.h>
#import "ParticipantModel.h"

@interface ParticipantCell : NSTableCellView

@property (nonatomic, assign) BOOL isLoginHost;

@property (nonatomic, strong) ParticipantModel *participantModel;

@property (nonatomic, copy) void (^clickChangeHost)(NSString *uid);

@end
