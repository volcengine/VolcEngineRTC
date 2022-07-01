//
//  EffectResource.m
//  quickstart

#import "EffectResource.h"

@implementation EffectResource

#define CVLicenseName @""

+ (NSString *)licensePath {
    NSString *bunldePath = [[NSBundle mainBundle] pathForResource:@"LicenseBag" ofType:@"bundle"];
    NSString *licensePath = [NSString stringWithFormat:@"%@/%@", bunldePath, CVLicenseName];

    [self checkPathExsit:licensePath];

    return licensePath;
}

+ (NSString *)modelPath {
    NSString *modelPath = [[NSBundle mainBundle] pathForResource:@"ModelResource" ofType:@"bundle"];

    [self checkPathExsit:modelPath];

    return modelPath;
}

+ (NSString *)getByteEffectPortraitPath {
    NSString *portraitPrefix = [[NSBundle mainBundle] pathForResource:@"ModelResource" ofType:@"bundle"];
    NSString *name = @"tt_matting_v13.0.model";
    NSString *path = [NSString stringWithFormat:@"%@/mattingmodel/%@", portraitPrefix, name];
    [self checkPathExsit:path];

    return path;
}

+ (NSString *)beautyCameraPath {
    NSString *bunldePath = [[NSBundle mainBundle] pathForResource:@"ComposeMakeup" ofType:@"bundle"];
    NSString *beautyCameraPath = [NSString stringWithFormat:@"%@/ComposeMakeup/beauty_IOS_live", bunldePath];

    [self checkPathExsit:beautyCameraPath];

    return beautyCameraPath;
}

+ (NSString *)reshapeCameraPath {
    NSString *bunldePath = [[NSBundle mainBundle] pathForResource:@"ComposeMakeup" ofType:@"bundle"];
    NSString *reshapeCameraPath = [NSString stringWithFormat:@"%@/ComposeMakeup/reshape_live", bunldePath];

    [self checkPathExsit:reshapeCameraPath];

    return reshapeCameraPath;
}

+ (NSString *)stickerPathWithName:(NSString *)stickerName {
    NSString *bunldePath = [[NSBundle mainBundle] pathForResource:@"StickerResource" ofType:@"bundle"];
    NSString *stickerPath = [NSString stringWithFormat:@"%@/stickers/%@", bunldePath, stickerName];

    [self checkPathExsit:stickerPath];

    return stickerPath;
}

+ (NSString *)filterPathWithName:(NSString *)filterName {
    NSString *bunldePath = [[NSBundle mainBundle] pathForResource:@"FilterResource" ofType:@"bundle"];
    NSString *filterPath = [NSString stringWithFormat:@"%@/Filter/%@", bunldePath, filterName];

    [self checkPathExsit:filterPath];

    return filterPath;
}

+ (void)checkPathExsit:(NSString *)path {
    BOOL isDirectory;
    BOOL exist = [[NSFileManager defaultManager] fileExistsAtPath:path isDirectory:&isDirectory];

    if (!exist) {
        NSLog(@"EffectResource path is not exist \n%@", path);
    }
}
@end
