//
//  CustomVideoRenderView.h


#import <UIKit/UIKit.h>
#import <VolcEngineRTC/objc/ByteRTCVideo.h>

NS_ASSUME_NONNULL_BEGIN

@interface CustomVideoRenderView : UIView <ByteRTCVideoSinkDelegate>

@end

NS_ASSUME_NONNULL_END
