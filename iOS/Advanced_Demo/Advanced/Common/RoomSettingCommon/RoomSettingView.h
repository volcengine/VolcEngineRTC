//
//  RoomSettingView.h
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>
#import <UIKit/UIKit.h>
#import "RoomSetting.h"

NS_ASSUME_NONNULL_BEGIN

@interface RoomSettingView : UIView

- (instancetype)initWithRtcKit:(ByteRTCEngineKit *)rtcKit;

@property (nonatomic, strong) RoomSetting *roomSetting;

@end

NS_ASSUME_NONNULL_END
