//
//  LiveView.h
//  advanced
//

#import <UIKit/UIKit.h>
#import "CustomVideoRenderView.h"
#import <VolcEngineRTC/VolcEngineRTC.h>

NS_ASSUME_NONNULL_BEGIN

@interface UserLiveView : UIView
@property (nonatomic, copy) NSString *uid;
@property (nonatomic, strong) ByteRTCRemoteStreamKey *streamKey;

@property (nonatomic, assign) BOOL useCustomRender;

@property (nonatomic, strong) UIView  *liveView;
@property (nonatomic, strong) CustomVideoRenderView *customRenderView;

@end

NS_ASSUME_NONNULL_END
