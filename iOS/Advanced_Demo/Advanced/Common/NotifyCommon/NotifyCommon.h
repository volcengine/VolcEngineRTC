//
//  NotifyCommon.h
//  Advanced
//
//

#import <VolcEngineRTC/objc/ByteRTCRoom.h>
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, NotifyStatus) {
    NotifyStatusText,
    NotifyStatusData,
};

typedef NS_ENUM(NSInteger, NotifySendStatus) {
    NotifySendStatusUser,
    NotifySendStatusRoom,
};

NS_ASSUME_NONNULL_BEGIN

@interface NotifyCommon : UIView

- (instancetype)initWithType:(NotifyStatus)notiftStatus
                   superView:(UIView *)superView
                     rtcRoom:(ByteRTCRoom *)rtcRoom;

@end

NS_ASSUME_NONNULL_END
