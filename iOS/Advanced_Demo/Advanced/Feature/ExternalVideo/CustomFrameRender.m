//
//  CustomFrameRender.m


#import "CustomFrameRender.h"

@implementation CustomFrameRender

+ (void)clearImageView:(UIImageView*)imageView {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIGraphicsBeginImageContext(imageView.bounds.size);
        UIColor * color = [UIColor clearColor];
        [color setFill];
        UIImage * image = UIGraphicsGetImageFromCurrentImageContext();
        imageView.image = image;
        UIGraphicsEndImageContext();
    });
}

+ (void)renderImageBuffer:(CVImageBufferRef)imageBufer forView:(UIImageView *)imageView rotation:(VideoRotation)rotation {
    CFRetain(imageBufer);
        
        
        CIImage *ciImage = [CIImage imageWithCVImageBuffer:imageBufer];
        
        CIContext *context = [CIContext contextWithOptions:nil];
        CGImageRef cgImage = [context
                                 createCGImage:ciImage
                                 fromRect:CGRectMake(0, 0,
                                                     CVPixelBufferGetWidth(imageBufer),
                                                     CVPixelBufferGetHeight(imageBufer))];
        
        UIImageOrientation imageOrientation;
        switch (rotation) {
            case VideoRotation_0:
                imageOrientation = UIImageOrientationUp;
                break;
            case VideoRotation_90:
                imageOrientation = UIImageOrientationRight;
                break;
            case VideoRotation_180:
                imageOrientation = UIImageOrientationDown;
                break;
            case VideoRotation_270:
                imageOrientation = UIImageOrientationLeft;
                break;

            default:
                break;
        }
        
    UIImage *image = [[UIImage alloc] initWithCGImage:cgImage scale:1.0 orientation:imageOrientation];
    dispatch_async(dispatch_get_main_queue(), ^{
        imageView.contentMode = UIViewContentModeScaleAspectFill;
        imageView.image = image;
    });
    
    CGImageRelease(cgImage);
    CFRelease(imageBufer);
}

@end
