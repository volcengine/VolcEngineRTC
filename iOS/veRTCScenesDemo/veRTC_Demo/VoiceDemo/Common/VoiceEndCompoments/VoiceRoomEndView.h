//
//  VoiceRoomEndView.h
//  veRTC_Demo
//
//  Created by  on 2021/5/18.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

//UI
typedef NS_ENUM(NSInteger, VoiceButtonColorType) {
    VoiceButtonColorTypeNone,
    VoiceButtonColorTypeRemind,
};

//form
typedef NS_ENUM(NSInteger, VoiceEndStatus) {
    VoiceEndStatusAudience,
    VoiceEndStatusHost,
    VoiceEndStatusHostOnly,
};

//button status
typedef NS_ENUM(NSInteger, VoiceButtonStatus) {
    VoiceButtonStatusEnd,
    VoiceButtonStatusLeave,
    VoiceButtonStatusCancel,
};

@interface VoiceRoomEndView : UIView

@property (nonatomic, copy) void (^clickButtonBlock)(VoiceButtonStatus status);

@property (nonatomic, assign) VoiceEndStatus VoiceEndStatus;

@end

NS_ASSUME_NONNULL_END
