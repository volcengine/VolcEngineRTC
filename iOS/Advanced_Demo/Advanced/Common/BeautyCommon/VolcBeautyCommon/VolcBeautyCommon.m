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

@end

@implementation VolcBeautyCommon

- (instancetype)initWithRtcKit:(ByteRTCVideo *)rtcVideo {
    self = [super init];
    if (self) {
        self.rtcVideo = rtcVideo;
        
        /// license 验证
        NSString *licensePath = [EffectResource licensePath];
        int errorCode = [self.rtcVideo checkVideoEffectLicense:licensePath];
        if (errorCode == 0) {
            NSLog(@"VolcBeautyCommon check license success");
        } else {
            NSLog(@"VolcBeautyCommon check license failed %d", errorCode);
        }
        
        /// 注册视频特效算法模型
        NSString *modelPath = [EffectResource modelPath];
        if (modelPath) {
            [self.rtcVideo setVideoEffectAlgoModelPath:modelPath];
        }
        
        /// 背景分割初始化
        NSString *portraitPath = [EffectResource getByteEffectPortraitPath];
        int virtualResult = [self.rtcVideo initVirtualBackground:licensePath
                                                     withModel:portraitPath];
        if (virtualResult == 0) {
            NSLog(@"VolcBeautyCommon init virtual success");
        } else {
            NSLog(@"VolcBeautyCommon init virtual failed %d", virtualResult);
        }

        /// 创建视频特效引擎
        int isEnable = [self.rtcVideo enableVideoEffect:YES];
        if (isEnable == 0) {
            NSLog(@"VolcBeautyCommon enable video effect success");
        } else {
            NSLog(@"VolcBeautyCommon enable video effect failed %d", isEnable);
        }

        /// 设置视频特效素材包
        NSString *beautyPath = [EffectResource beautyCameraPath];
        NSString *resharppath = [EffectResource reshapeCameraPath];
        self.makeupNodes = @[ beautyPath, resharppath ];
        int isEffectNodes = [self.rtcVideo setVideoEffectNodes:self.makeupNodes];
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
        [self.rtcVideo setVideoEffectNodes:allNodes];
    } else {
        [self.rtcVideo setVideoEffectNodes:self.makeupNodes];
    }
}

- (void)didClickedFilterEffect:(NSString *)path
                         value:(CGFloat)value {
    [self.rtcVideo setVideoEffectColorFilter:path];
    [self.rtcVideo setVideoEffectColorFilterIntensity:value];
}

- (void)didChangeFilterEffect:(CGFloat)value {
    [self.rtcVideo setVideoEffectColorFilterIntensity:value];
}

- (void)didClickedVirtualEffect:(NSString *)type
                       selected:(BOOL)isSelected {
    if (isSelected) {
        ByteRTCVirtualBackgroundSource *source = [[ByteRTCVirtualBackgroundSource alloc] init];
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
        int result = [self.rtcVideo enableVirtualBackground:source];
        if (result != 0) {
            [[ToastComponents shareToastComponents] showWithMessage:@"开启背景分割失败"];
        }
    } else {
        [self.rtcVideo disableVirtualBackground];
    }
}

- (void)didChangeBeautyEffect:(NSString *)key
                        value:(CGFloat)value  {
    // 美颜
    NSString *path = [EffectResource beautyCameraPath];
    [self.rtcVideo updateVideoEffectNode:path
                               nodeKey:key
                             nodeValue:value];
}

- (void)didChangeReshapeEffect:(NSString *)key
                         value:(CGFloat)value {
    // 美形
    NSString *path = [EffectResource reshapeCameraPath];
    [self.rtcVideo updateVideoEffectNode:path
                               nodeKey:key
                             nodeValue:value];
}

- (void)didDefaultSetting {
    [self.rtcVideo setVideoEffectColorFilter:[EffectResource filterPathWithName:@"Filter_06_03"]];
    [self.rtcVideo setVideoEffectColorFilterIntensity:0.0];
}

@end
