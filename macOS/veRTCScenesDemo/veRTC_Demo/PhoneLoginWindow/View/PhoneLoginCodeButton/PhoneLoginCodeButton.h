//
//  PhoneLoginCodeButton.h
//  veRTC_Demo
//
//  Created by  on 2021/6/6.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, LoginCodeStatus) {
    LoginCodeStatusNone,
    LoginCodeStatusLoading,
    LoginCodeStatusCountdown,
    LoginCodeStatusAgain,
};

@interface PhoneLoginCodeButton : TrackButton

@property (nonatomic, assign) LoginCodeStatus loginCodeStatus;

@property (nonatomic, assign) BOOL isDisabled;

@end

NS_ASSUME_NONNULL_END
