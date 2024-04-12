//
//  VolcBeautyCommon.m
//  Advanced
//
//

#import "EffectResource.h"
#import "SettingView.h"
#import "VolcBeautyCommon.h"

@interface VolcBeautyCommon ()

@property (nonatomic, weak) ByteRTCVideo *rtcVideo;
@property (nonatomic, strong) NSArray *makeupNodes;
@property (nonatomic, strong) ByteRTCVideoEffect *rtcVideoEffect;
@end

@implementation VolcBeautyCommon

- (instancetype)initWithRtcKit:(ByteRTCVideo *)rtcVideo {
    self = [super init];
    if (self) {
        self.rtcVideo = rtcVideo;
        self.rtcVideoEffect = [rtcVideo getVideoEffectInterface];
        
        /// license 验证
        NSString *licensePath = [EffectResource licensePath];

        NSString *modelPath = [EffectResource modelPath];
        
        int errorCode = [self.rtcVideoEffect initCVResource:licensePath withAlgoModelDir:modelPath];
        
        if (errorCode == 0) {
            NSLog(@"VolcBeautyCommon initCVResource success");
        } else {
            NSLog(@"VolcBeautyCommon initCVResource failed %d", errorCode);
        }
        
        /// 创建视频特效引擎
        int isEnable = [self.rtcVideoEffect enableVideoEffect];
        if (isEnable == 0) {
            NSLog(@"VolcBeautyCommon enable video effect success");
        } else {
            NSLog(@"VolcBeautyCommon enable video effect failed %d", isEnable);
        }
        
        /// 设置视频特效素材包
        NSString *beautyPath = [EffectResource beautyCameraPath];
        NSString *resharppath = [EffectResource reshapeCameraPath];
        self.makeupNodes = @[ beautyPath, resharppath ];
        int isEffectNodes = [self.rtcVideoEffect setEffectNodes:self.makeupNodes];
        if (isEffectNodes == 0) {
            NSLog(@"VolcBeautyCommon enable effect nodes success");
        } else {
            NSLog(@"VolcBeautyCommon enable effect nodes failed %d", isEnable);
        }
    }
    return self;
}

- (void)didClickedStickerEffect:(NSString *)path
                       selected:(BOOL)isSelected {
    if (isSelected) {
        NSArray *allNodes = [self.makeupNodes arrayByAddingObject:path];
        [self.rtcVideoEffect setEffectNodes:allNodes];
    } else {
        [self.rtcVideoEffect setEffectNodes:self.makeupNodes];
    }
}

- (void)didClickedFilterEffect:(NSString *)path
                         value:(CGFloat)value {
    [self.rtcVideoEffect setColorFilter:path];
    [self.rtcVideoEffect setColorFilterIntensity:value];
}

- (void)didChangeFilterEffect:(CGFloat)value {
    [self.rtcVideoEffect setColorFilterIntensity:value];
}

- (void)didClickedVirtualEffect:(NSString *)type
                       selected:(BOOL)isSelected {
    ByteRTCVirtualBackgroundSource *source = [[ByteRTCVirtualBackgroundSource alloc] init];

    if (isSelected) {
        if ([type isEqualToString:@"image"]) {
            // 图片
            NSString *path = [[NSBundle mainBundle] pathForResource:@"background" ofType:@"jpg"];
            source.sourceType = ByteRTCVirtualBackgroundSourceTypeImage;
            source.sourcePath = path;
        } else {
            // 纯色
            source.sourceType = ByteRTCVirtualBackgroundSourceTypeColor;
            source.sourceColor = 0xff1678ff;
        }
        /// 背景分割初始化
        NSString *portraitPath = [EffectResource getByteEffectPortraitPath];
        
        int result = [self.rtcVideoEffect enableVirtualBackground:portraitPath withSource:source];
        if (result != 0) {
            [[ToastComponents shareToastComponents] showWithMessage:@"开启背景分割失败"];
        }
    } else {
        [self.rtcVideoEffect disableVirtualBackground];
    }
}

- (void)didChangeBeautyEffect:(NSString *)key
                        value:(CGFloat)value  {
    // 美颜
    NSString *path = [EffectResource beautyCameraPath];
    [self.rtcVideoEffect updateEffectNode:path
                               key:key
                             value:value];
}

- (void)didChangeReshapeEffect:(NSString *)key
                         value:(CGFloat)value {
    // 美形
    NSString *path = [EffectResource reshapeCameraPath];
    [self.rtcVideoEffect updateEffectNode:path
                               key:key
                             value:value];
}

- (void)didDefaultSetting {
    [self.rtcVideoEffect setColorFilter:[EffectResource filterPathWithName:@"Filter_06_03"]];
    [self.rtcVideoEffect setColorFilterIntensity:0.0];
}

@end
