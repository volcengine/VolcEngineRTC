#import "SettingsService.h"

static NSString *const kSettingsResolutions = @"kQSSettingsResolutions";
static NSString *const kSettingsFrameRate = @"kQSSettingsFrameRate";
static NSString *const kSettingsKBitRate = @"kQSSettingsKBitRate";
static NSString *const kSettingsScreenResolutions = @"kQSSettingsScreenResolutions";
static NSString *const kSettingsScreenFrameRate = @"kQSSettingsScreenFrameRate";
static NSString *const kSettingsScreenKBitRate = @"kQSSettingsScreenKBitRate";
static NSString *const kQSSettingsOpenParam = @"kQSSettingsOpenParam";

@implementation SettingsService

#pragma mark - Login info

//Resolution
+ (CGSize)defaultResolution {
    return CGSizeMake(360, 640);
}

+ (CGSize)getResolution {
    return [[[self getResolutions] firstObject] CGSizeValue];
}

+ (NSArray *)getResolutionArray {
    NSArray *resolutionArr = [[NSUserDefaults standardUserDefaults] arrayForKey:kSettingsResolutions];
    if (!resolutionArr) {
        resolutionArr = @[ @([self defaultResolution].width),
                           @([self defaultResolution].height)];
    }
    return resolutionArr;
}

+ (NSArray<NSValue *> *)getResolutions {
    NSArray *resolutionArr = [[NSUserDefaults standardUserDefaults] arrayForKey:kSettingsResolutions];
    NSArray *defaultResolution = @[ @([self defaultResolution]) ];
    if ([resolutionArr count] == 0) {
        return defaultResolution;
    }
    if ([[resolutionArr firstObject] isKindOfClass:[[defaultResolution firstObject] class]]) {
        return resolutionArr;
    }
    NSMutableArray *resolutionArrSize = [[NSMutableArray alloc] init];
    for (int i = 0; i < [resolutionArr count]; i += 2) {
        CGSize size = CGSizeMake([resolutionArr[i] integerValue], [resolutionArr[i + 1] integerValue]);
        [resolutionArrSize addObject:@(size)];
    }
    return resolutionArrSize;
}

+ (void)setResolutions:(NSArray<NSValue *> *)resolutions {
    [[NSUserDefaults standardUserDefaults] setObject:resolutions forKey:kSettingsResolutions];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

//FrameRate
+ (int)getFrameRate {
    int frameRate = (int)[[NSUserDefaults standardUserDefaults] integerForKey:kSettingsFrameRate];
    return frameRate > 0 ? frameRate : 15;
}

+ (void)setFrameRate:(int)frameRate {
    [[NSUserDefaults standardUserDefaults] setInteger:frameRate forKey:kSettingsFrameRate];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

//BitRate 
+ (int)getKBitRate {
    int bitrate = (int)[[NSUserDefaults standardUserDefaults] integerForKey:kSettingsKBitRate];
    return bitrate > 0 ? bitrate : 400;
}

+ (void)setKBitRate:(int)kbitRate {
    [[NSUserDefaults standardUserDefaults] setInteger:kbitRate forKey:kSettingsKBitRate];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

#pragma mark - screen
//Resolution
+ (CGSize)defaultScreenResolution {
    return CGSizeMake(1080, 1920);
}

+ (CGSize)getScreenResolution {
    return [[[self getScreenResolutions] firstObject] CGSizeValue];
}

+ (NSArray *)getScreenResolutionArray {
    NSArray *resolutionArr = [[NSUserDefaults standardUserDefaults] arrayForKey:kSettingsScreenResolutions];
    if (!resolutionArr) {
        resolutionArr = @[ @([self defaultScreenResolution].width),
                           @([self defaultScreenResolution].height)];
    }
    return resolutionArr;
}

+ (NSArray<NSValue *> *)getScreenResolutions {
    NSArray *resolutionArr = [[NSUserDefaults standardUserDefaults] arrayForKey:kSettingsScreenResolutions];
    NSArray *defaultResolution = @[ @([self defaultScreenResolution]) ];
    if ([resolutionArr count] == 0) {
        return defaultResolution;
    }
    if ([[resolutionArr firstObject] isKindOfClass:[[defaultResolution firstObject] class]]) {
        return resolutionArr;
    }
    NSMutableArray *resolutionArrSize = [[NSMutableArray alloc] init];
    for (int i = 0; i < [resolutionArr count]; i += 2) {
        CGSize size = CGSizeMake([resolutionArr[i] integerValue], [resolutionArr[i + 1] integerValue]);
        [resolutionArrSize addObject:@(size)];
    }
    return resolutionArrSize;
}

+ (void)setScreenResolutions:(NSArray<NSValue *> *)resolutions {
    [[NSUserDefaults standardUserDefaults] setObject:resolutions forKey:kSettingsScreenResolutions];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

//FrameRate
+ (int)getScreenFrameRate {
    int frameRate = (int)[[NSUserDefaults standardUserDefaults] integerForKey:kSettingsScreenFrameRate];
    return frameRate > 0 ? frameRate : 15;
}

+ (void)setScreenFrameRate:(int)frameRate {
    [[NSUserDefaults standardUserDefaults] setInteger:frameRate forKey:kSettingsScreenFrameRate];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

//BitRate
+ (int)getScreenKBitRate {
    int bitrate = (int)[[NSUserDefaults standardUserDefaults] integerForKey:kSettingsScreenKBitRate];
    return bitrate > 0 ? bitrate : 2000;
}

+ (void)setScreenKBitRate:(int)kbitRate {
    [[NSUserDefaults standardUserDefaults] setInteger:kbitRate forKey:kSettingsScreenKBitRate];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

//Param
+ (BOOL)getOpenParam {
    return [[NSUserDefaults standardUserDefaults] boolForKey:kQSSettingsOpenParam];
}

+ (void)setOpenParam:(BOOL)isOpenParam {
    [[NSUserDefaults standardUserDefaults] setBool:isOpenParam forKey:kQSSettingsOpenParam];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

@end
