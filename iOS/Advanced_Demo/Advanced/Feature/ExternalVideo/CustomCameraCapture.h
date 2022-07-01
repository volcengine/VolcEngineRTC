//
//  CustomCameraCapture.h


#import <AVFoundation/AVFoundation.h>
@class CustomCameraCapture;

NS_ASSUME_NONNULL_BEGIN

@protocol CustomCameraCaptureDelegate <NSObject>

- (void)customCameraCapture:(CustomCameraCapture *)customCameraCapture didOutputBuffer:(CVImageBufferRef)buffer time:(CMTime)time;

@end

@interface CustomCameraCapture : NSObject

@property (nonatomic, weak) id<CustomCameraCaptureDelegate> captureDelegate;

- (BOOL)startCamera;

- (BOOL)stopCamera;

- (BOOL)switchCameraIsFront:(BOOL)isFront;

@end

NS_ASSUME_NONNULL_END
