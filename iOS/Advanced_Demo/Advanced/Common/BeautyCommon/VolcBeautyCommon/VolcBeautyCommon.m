//
//  VolcBeautyCommon.m
//  Advanced
//
//  Created by bytedance on 2022/2/11.
//

#import "EffectResource.h"
#import "SettingView.h"
#import "VolcBeautyCommon.h"

@interface VolcBeautyCommon ()

@property (nonatomic, weak) ByteRTCEngineKit *rtcKit;
@property (nonatomic, strong) NSArray *makeupNodes;

@end

@implementation VolcBeautyCommon

- (instancetype)initWithRtcKit:(ByteRTCEngineKit *)rtcKit {
    self = [super init];
    if (self) {
        self.rtcKit = rtcKit;
        
        /// license 验证
        NSString *licensePath = [EffectResource licensePath];
        int errorCode = [self.rtcKit checkVideoEffectLicense:licensePath];
        if (errorCode == 0) {
            NSLog(@"VolcBeautyCommon check license success");
        } else {
            NSLog(@"VolcBeautyCommon check license failed %d", errorCode);
        }
        
        /// 注册视频特效算法模型
        NSString *modelPath = [EffectResource modelPath];
        if (modelPath) {
            [self.rtcKit setVideoEffectAlgoModelPath:modelPath];
        }
        
        /// 背景分割初始化
        NSString *portraitPath = [EffectResource getByteEffectPortraitPath];
        int virtualResult = [self.rtcKit initVirtualBackground:licensePath
                                                     withModel:portraitPath];
        if (virtualResult == 0) {
            NSLog(@"VolcBeautyCommon init virtual success");
        } else {
            NSLog(@"VolcBeautyCommon init virtual failed %d", virtualResult);
        }

        /// 创建视频特效引擎
        int isEnable = [self.rtcKit enableVideoEffect:YES];
        if (isEnable == 0) {
            NSLog(@"VolcBeautyCommon enable video effect success");
        } else {
            NSLog(@"VolcBeautyCommon enable video effect failed %d", isEnable);
        }

        /// 设置视频特效素材包
        NSString *beautyPath = [EffectResource beautyCameraPath];
        NSString *resharppath = [EffectResource reshapeCameraPath];
        self.makeupNodes = @[ beautyPath, resharppath ];
        int isEffectNodes = [self.rtcKit setVideoEffectNodes:self.makeupNodes];
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
        [self.rtcKit setVideoEffectNodes:allNodes];
    } else {
        [self.rtcKit setVideoEffectNodes:self.makeupNodes];
    }
}

- (void)didClickedFilterEffect:(NSString *)path
                         value:(CGFloat)value {
    [self.rtcKit setVideoEffectColorFilter:path];
    [self.rtcKit setVideoEffectColorFilterIntensity:value];
}

- (void)didChangeFilterEffect:(CGFloat)value {
    [self.rtcKit setVideoEffectColorFilterIntensity:value];
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
        int result = [self.rtcKit enableVirtualBackground:source];
        if (result != 0) {
            [[ToastComponents shareToastComponents] showWithMessage:@"开启背景分割失败"];
        }
    } else {
        [self.rtcKit disableVirtualBackground];
    }
}

- (void)didChangeBeautyEffect:(NSString *)key
                        value:(CGFloat)value  {
    // 美颜
    NSString *path = [EffectResource beautyCameraPath];
    [self.rtcKit updateVideoEffectNode:path
                               nodeKey:key
                             nodeValue:value];
}

- (void)didChangeReshapeEffect:(NSString *)key
                         value:(CGFloat)value {
    // 美形
    NSString *path = [EffectResource reshapeCameraPath];
    [self.rtcKit updateVideoEffectNode:path
                               nodeKey:key
                             nodeValue:value];
}

- (void)didDefaultSetting {
    [self.rtcKit setVideoEffectColorFilter:[EffectResource filterPathWithName:@"Filter_06_03"]];
    [self.rtcKit setVideoEffectColorFilterIntensity:0.0];
}

@end
