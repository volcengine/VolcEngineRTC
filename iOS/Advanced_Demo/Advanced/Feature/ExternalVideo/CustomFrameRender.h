//
//  CustomFrameRender.h


#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, VideoRotation) {
    VideoRotation_0 = 0,
    VideoRotation_90 = 90,
    VideoRotation_180 = 180,
    VideoRotation_270 = 270
};

NS_ASSUME_NONNULL_BEGIN

@interface CustomFrameRender : NSObject

+ (void)renderImageBuffer:(CVImageBufferRef)imageBufer forView:(UIImageView*)imageView rotation:(VideoRotation)rotation;

+ (void)clearImageView:(UIImageView*)imageView;

@end

NS_ASSUME_NONNULL_END
