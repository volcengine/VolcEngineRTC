#import <UIKit/UIKit.h>

@interface SettingsService : NSObject

#pragma mark - Login info

// Resolution
+ (CGSize)getResolution;
+ (NSArray *)getResolutionArray;
+ (void)setResolutions:(NSArray<NSValue *> *)resolutions;

// Frame rate
+ (int)getFrameRate;
+ (void)setFrameRate:(int)frameRate;

// Bit rate
+ (int)getKBitRate;
+ (void)setKBitRate:(int)kbitRate;

// View real-time video parameters
+ (BOOL)getOpenParam;
+ (void)setOpenParam:(BOOL)isOpenParam;

@end
