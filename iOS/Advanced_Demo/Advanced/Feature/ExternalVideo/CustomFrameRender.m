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
    dispatch_async(dispatch_get_main_queue(), ^{
        imageView.image = [UIImage imageWithCIImage:[CIImage imageWithCVImageBuffer:imageBufer]];
        imageView.contentMode = UIViewContentModeScaleAspectFill;
        switch (rotation) {
            case VideoRotation_0:
                imageView.transform = CGAffineTransformMakeRotation(0);
                break;
            case VideoRotation_90:
                imageView.transform = CGAffineTransformMakeRotation(M_PI_2);
                break;
            case VideoRotation_180:
                imageView.transform = CGAffineTransformMakeRotation(M_PI);
                break;
            case VideoRotation_270:
                imageView.transform = CGAffineTransformMakeRotation(M_PI_2 + M_PI);
                break;
                
            default:
                break;
        }
        imageView.transform = CGAffineTransformScale(imageView.transform, 1.2, 1.2);
        CFRelease(imageBufer);
    });
}

@end
