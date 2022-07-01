//
//  NotifyCommon.h
//  Advanced
//
//  Created by bytedance on 2022/3/17.
//

#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>
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
                      rtcKit:(ByteRTCEngineKit *)rtcKit;

@end

NS_ASSUME_NONNULL_END
