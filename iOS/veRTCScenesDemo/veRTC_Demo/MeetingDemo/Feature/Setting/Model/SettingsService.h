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

// Screen Resolution
+ (CGSize)getScreenResolution;
+ (NSArray *)getScreenResolutionArray;
+ (void)setScreenResolutions:(NSArray<NSValue *> *)resolutions;

// Screen Frame rate
+ (int)getScreenFrameRate;
+ (void)setScreenFrameRate:(int)frameRate;

// Screen Bit rate
+ (int)getScreenKBitRate;
+ (void)setScreenKBitRate:(int)kbitRate;

// View real-time video parameters
+ (BOOL)getOpenParam;
+ (void)setOpenParam:(BOOL)isOpenParam;

@end
