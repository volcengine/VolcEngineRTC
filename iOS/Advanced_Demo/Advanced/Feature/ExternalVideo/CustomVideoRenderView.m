//
//  CustomVideoRenderView.m


#import "CustomVideoRenderView.h"
#import "CustomFrameRender.h"
#import "Masonry.h"

@interface CustomVideoRenderView ()

@property (nonatomic, strong) UIImageView *renderImageView;

@end

@implementation CustomVideoRenderView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self addSubview:self.renderImageView];
        [self.renderImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        self.clipsToBounds = YES;
    }
    return self;
}

#pragma mark - ByteRTCVideoSinkDelegate

- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
             extendedData:(NSData * _Nullable)extendedData {
    [CustomFrameRender renderImageBuffer:pixelBuffer
                                 forView:self.renderImageView
                                rotation:[self deviceOrientationRotation:rotation]];
}

- (VideoRotation)deviceOrientationRotation:(ByteRTCVideoRotation)rotation {
    VideoRotation videoRotation = VideoRotation_0;
    switch (rotation) {
        case ByteRTCVideoRotation0:
            videoRotation = VideoRotation_0;
            break;
        case ByteRTCVideoRotation90:
            videoRotation = VideoRotation_90;
            break;
        case ByteRTCVideoRotation180:
            videoRotation = VideoRotation_180;
            break;
        case ByteRTCVideoRotation270:
            videoRotation = VideoRotation_270;
            break;
        default:
            // Ignore.
            break;
    }
    return videoRotation;
}

#pragma mark - getter

- (UIImageView *)renderImageView {
    if (!_renderImageView) {
        _renderImageView = [[UIImageView alloc] init];
    }
    return _renderImageView;
}


@end
