//
//  MeetingEndView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

//UI
typedef NS_ENUM(NSInteger, ButtonColorType) {
    ButtonColorTypeNone = 3001,
    ButtonColorTypeRemind,
    ButtonColorTypeDisable,
};

//form
typedef NS_ENUM(NSInteger, MeetingEndStatus) {
    MeetingEndStatusNone,
    MeetingEndStatusHost,
};

//button status
typedef NS_ENUM(NSInteger, MeetingButtonStatus) {
    MeetingButtonStatusEnd,
    MeetingButtonStatusLeave,
    MeetingButtonStatusCancel,
};

@interface MeetingEndView : NSView

@property (nonatomic, copy) void (^clickButtonBlock)(MeetingButtonStatus status);

@property (nonatomic, assign) MeetingEndStatus meetingEndStatus;

@end

NS_ASSUME_NONNULL_END
