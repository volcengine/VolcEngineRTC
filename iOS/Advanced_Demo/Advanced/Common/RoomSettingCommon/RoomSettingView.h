//
//  RoomSettingView.h
//  Advanced
//
//

#import <VolcEngineRTC/objc/ByteRTCVideo.h>
#import <UIKit/UIKit.h>
#import "RoomSetting.h"

NS_ASSUME_NONNULL_BEGIN

@interface RoomSettingView : UIView

- (instancetype)initWithRtcKit:(ByteRTCVideo *)rtcVideo
                rtcRoom:(ByteRTCRoom *)rtcRoom;

@property (nonatomic, strong) RoomSetting *roomSetting;

@end

NS_ASSUME_NONNULL_END
