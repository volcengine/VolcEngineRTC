//
//  FUDemoManager.m
//  FUDemo
//
//  Created by 项林平 on 2021/6/17.
//

#import "FUDemoManager.h"

#import "FUBeautySkinView.h"
#import "FUBeautyShapeView.h"
#import "FUBeautyFilterView.h"
#import "FUStickerView.h"
#import "FUMakeupView.h"
#import "FUBodyView.h"

#import "FUSegmentBar.h"
#import "FUAlertManager.h"

#import "authpack.h"

@interface FUDemoManager ()<FUSegmentBarDelegate>

/// 底部功能选择栏
@property (nonatomic, strong) FUSegmentBar *bottomBar;
/// 美肤功能视图
@property (nonatomic, strong) FUBeautySkinView *skinView;
/// 美型功能视图
@property (nonatomic, strong) FUBeautyShapeView *shapeView;
/// 滤镜功能视图
@property (nonatomic, strong) FUBeautyFilterView *filterView;
/// 贴纸功能视图
@property (nonatomic, strong) FUStickerView *stickerView;
/// 美妆功能视图
@property (nonatomic, strong) FUMakeupView *makeupView;
/// 美体功能视图
@property (nonatomic, strong) FUBodyView *bodyView;

@property (nonatomic, strong) UIView *showingView;

/// 效果开关
@property (nonatomic, strong) UISwitch *renderSwitch;
/// 提示标签
@property (nonatomic, strong) UILabel *trackTipLabel;

@property (nonatomic, weak) UIView *targetView;
@property (nonatomic, assign) CGFloat demoOriginY;

@end

@implementation FUDemoManager

static FUDemoManager *demoManager = nil;
static dispatch_once_t onceToken;

+ (instancetype)shared {
    dispatch_once(&onceToken, ^{
        demoManager = [[FUDemoManager alloc] init];
    });
    return demoManager;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        self.shouldRender = YES;
    }
    return self;
}

+ (void)setupFUSDK {
    [FURenderKit setLogLevel:FU_LOG_LEVEL_INFO];
    FUSetupConfig *setupConfig = [[FUSetupConfig alloc] init];
    setupConfig.authPack = FUAuthPackMake(g_auth_package, sizeof(g_auth_package));
    // 初始化 FURenderKit
    [FURenderKit setupWithSetupConfig:setupConfig];
    
    // 加载人脸 AI 模型
    NSString *faceAIPath = [[NSBundle mainBundle] pathForResource:@"ai_face_processor" ofType:@"bundle"];
    [FUAIKit loadAIModeWithAIType:FUAITYPE_FACEPROCESSOR dataPath:faceAIPath];
    
    // 加载身体 AI 模型
    NSString *bodyAIPath = [[NSBundle mainBundle] pathForResource:@"ai_human_processor" ofType:@"bundle"];
    [FUAIKit loadAIModeWithAIType:FUAITYPE_HUMAN_PROCESSOR dataPath:bodyAIPath];
    
    [FUAIKit shareKit].maxTrackFaces = 4;
    
    // 设置人脸算法质量
    [FUAIKit shareKit].faceProcessorFaceLandmarkQuality = [FURenderKit devicePerformanceLevel] == FUDevicePerformanceLevelHigh ? FUFaceProcessorFaceLandmarkQualityHigh : FUFaceProcessorFaceLandmarkQualityMedium;
    
    // 设置小脸检测是否打开
    [FUAIKit shareKit].faceProcessorDetectSmallFace = [FURenderKit devicePerformanceLevel] == FUDevicePerformanceLevelHigh;
        
    // 美颜默认加载
    [self loadDefaultBeauty];
}

- (void)addDemoViewToView:(UIView *)view originY:(CGFloat)originY {
    NSAssert(view, @"目标控制器不能为空");
    self.targetView = view;
    self.demoOriginY = originY;
    
    [view addSubview:self.bottomBar];
    [view addSubview:self.skinView];
    [view addSubview:self.shapeView];
    [view addSubview:self.filterView];
    [view addSubview:self.stickerView];
    [view addSubview:self.makeupView];
    [view addSubview:self.bodyView];
    
    [view addSubview:self.trackTipLabel];
    [view addSubview:self.renderSwitch];
}

- (void)checkAITrackedResult {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (self.showingView == self.bodyView) {
            self.trackTipLabel.hidden = [FUAIKit aiHumanProcessorNums] > 0;
            self.trackTipLabel.text = FULocalizedString(@"未检测到人体");
        } else {
            self.trackTipLabel.hidden = [FUAIKit aiFaceProcessorNums] > 0;
            self.trackTipLabel.text = FULocalizedString(@"未检测到人脸");
        }
    });
}

#pragma mark - Private methods

/// 显示功能视图
/// @param functionView 功能视图
- (void)showFunctionView:(UIView *)functionView {
    if (!functionView) {
        return;
    }
    functionView.hidden = NO;
    [UIView animateWithDuration:0.15 delay:0 options:UIViewAnimationOptionCurveEaseOut animations:^{
        functionView.transform = CGAffineTransformMakeScale(1, 1);
        functionView.alpha = 1;
    } completion:^(BOOL finished) {
    }];
}


/// 隐藏功能视图
/// @param functionView 功能视图
/// @param animated 是否需要动画（切换功能时先隐藏当前显示的视图不需要动画，直接隐藏时需要动画）
- (void)hideFunctionView:(UIView *)functionView animated:(BOOL)animated {
    if (!functionView) {
        return;
    }
    if (animated) {
        [UIView animateWithDuration:0.15 delay:0 options:UIViewAnimationOptionCurveEaseIn animations:^{
            functionView.transform = CGAffineTransformMakeScale(1, 0.001);
            functionView.alpha = 0;
        } completion:^(BOOL finished) {
            functionView.hidden = YES;
        }];
    } else {
        functionView.transform = CGAffineTransformMakeScale(1, 0.001);
        functionView.alpha = 0;
        functionView.hidden = YES;
    }
}

#pragma mark - Event response
- (void)renderSwitchAction:(UISwitch *)sender {
    self.shouldRender = sender.isOn;
}

#pragma mark - FUSegmentBarDelegate

- (void)segmentBar:(FUSegmentBar *)segmentBar didSelectItemAtIndex:(NSUInteger)index {
    [FUAIKit shareKit].maxTrackFaces = index == FUModuleTypeBody ? 1 : 4;
    UIView *needShowView = nil;
    switch (index) {
        case FUModuleTypeBeautySkin:{
            needShowView = self.skinView;
        }
            break;
        case FUModuleTypeBeautyShape:{
            needShowView = self.shapeView;
        }
            break;
        case FUModuleTypeBeautyFilter:{
            needShowView = self.filterView;
        }
            break;
        case FUModuleTypeSticker:{
            needShowView = self.stickerView;
        }
            break;
        case FUModuleTypeMakeup:{
            needShowView = self.makeupView;
        }
            break;
        case FUModuleTypeBody:{
            if (![FURenderKit shareRenderKit].bodyBeauty) {
                // 加载默认美体
                [FUDemoManager loadDefaultBody];
            }
            needShowView = self.bodyView;
        }
            break;
    }
    if (needShowView && needShowView.hidden) {
        if (self.showingView) {
            // 先隐藏当前功能视图
            [self hideFunctionView:self.showingView animated:NO];
        }
        [self showFunctionView:needShowView];
        self.renderSwitch.transform = CGAffineTransformMakeTranslation(0, -CGRectGetHeight(needShowView.frame));
        self.renderSwitch.hidden = NO;
        self.showingView = needShowView;
    }
}

#pragma mark - Getters
- (FUSegmentBar *)bottomBar {
    if (!_bottomBar) {
        _bottomBar = [[FUSegmentBar alloc] initWithFrame:CGRectMake(0, self.demoOriginY, CGRectGetWidth(self.targetView.bounds), 49) titles:@[FULocalizedString(@"美肤"), FULocalizedString(@"美型"), FULocalizedString(@"滤镜"), FULocalizedString(@"贴纸"),  FULocalizedString(@"美妆"), FULocalizedString(@"美体")] configuration:[FUSegmentBarConfigurations new]];
        _bottomBar.delegate = self;
    }
    return _bottomBar;
}

- (FUBeautySkinView *)skinView {
    if (!_skinView) {
        _skinView = [[FUBeautySkinView alloc] initWithFrame:CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight)];
        _skinView.layer.anchorPoint = CGPointMake(0.5, 1);
        // 设置了anchorPoint需要重新设置frame
        _skinView.frame = CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight);
        // 默认隐藏
        [self hideFunctionView:_skinView animated:NO];
    }
    return _skinView;
}

- (FUBeautyShapeView *)shapeView {
    if (!_shapeView) {
        _shapeView = [[FUBeautyShapeView alloc] initWithFrame:CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight)];
        _shapeView.layer.anchorPoint = CGPointMake(0.5, 1);
        _shapeView.frame = CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight);
        // 默认隐藏
        [self hideFunctionView:_shapeView animated:NO];
    }
    return _shapeView;
}

- (FUBeautyFilterView *)filterView {
    if (!_filterView) {
        _filterView = [[FUBeautyFilterView alloc] initWithFrame:CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight)];
        _filterView.layer.anchorPoint = CGPointMake(0.5, 1);
        _filterView.frame = CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight);
        // 默认隐藏
        [self hideFunctionView:_filterView animated:NO];
    }
    return _filterView;
}

- (FUStickerView *)stickerView {
    if (!_stickerView) {
        _stickerView = [[FUStickerView alloc] initWithFrame:CGRectMake(0, self.demoOriginY - FUFunctionViewHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight)];
        _stickerView.layer.anchorPoint = CGPointMake(0.5, 1);
        _stickerView.frame = CGRectMake(0, self.demoOriginY - FUFunctionViewHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight);
        // 默认隐藏
        [self hideFunctionView:_stickerView animated:NO];
    }
    return _stickerView;
}

- (FUMakeupView *)makeupView {
    if (!_makeupView) {
        _makeupView = [[FUMakeupView alloc] initWithFrame:CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight)];
        _makeupView.layer.anchorPoint = CGPointMake(0.5, 1);
        _makeupView.frame = CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight);
        // 默认隐藏
        [self hideFunctionView:_makeupView animated:NO];
    }
    return _makeupView;
}

- (FUBodyView *)bodyView {
    if (!_bodyView) {
        _bodyView = [[FUBodyView alloc] initWithFrame:CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight)];
        _bodyView.layer.anchorPoint = CGPointMake(0.5, 1);
        _bodyView.frame = CGRectMake(0, self.demoOriginY - FUFunctionViewHeight - FUFunctionSliderHeight, CGRectGetWidth(self.targetView.bounds), FUFunctionViewHeight + FUFunctionSliderHeight);
        // 默认隐藏
        [self hideFunctionView:_bodyView animated:NO];
    }
    return _bodyView;
}

- (UISwitch *)renderSwitch {
    if (!_renderSwitch) {
        _renderSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(10, CGRectGetMinY(self.bottomBar.frame) - 40, 80, 30)];
        [_renderSwitch addTarget:self action:@selector(renderSwitchAction:) forControlEvents:UIControlEventValueChanged];
        _renderSwitch.on = YES;
        _renderSwitch.hidden = YES;
    }
    return _renderSwitch;
}

- (UILabel *)trackTipLabel {
    if (!_trackTipLabel) {
        _trackTipLabel = [[UILabel alloc] initWithFrame:CGRectMake(CGRectGetMidX(self.targetView.frame) - 70, CGRectGetMidY(self.targetView.frame) - 12, 140, 24)];
        _trackTipLabel.textColor = [UIColor whiteColor];
        _trackTipLabel.font = [UIFont systemFontOfSize:17];
        _trackTipLabel.textAlignment = NSTextAlignmentCenter;
        _trackTipLabel.hidden = YES;
    }
    return _trackTipLabel;
}

#pragma mark - Class methods

+ (void)destory {
    [FURenderKit destroy];
    onceToken = 0;
    demoManager = nil;
}

+ (void)resetTrackedResult {
    [FUAIKit resetTrackedResult];
}

+ (void)updateBeautyBlurEffect {
    if (![FURenderKit shareRenderKit].beauty || ![FURenderKit shareRenderKit].beauty.enable) {
        return;
    }
    if ([FURenderKit devicePerformanceLevel] == FUDevicePerformanceLevelHigh) {
        // 根据人脸置信度设置不同磨皮效果
        CGFloat score = [FUAIKit fuFaceProcessorGetConfidenceScore:0];
        if (score > 0.95) {
            [FURenderKit shareRenderKit].beauty.blurType = 3;
            [FURenderKit shareRenderKit].beauty.blurUseMask = YES;
        } else {
            [FURenderKit shareRenderKit].beauty.blurType = 2;
            [FURenderKit shareRenderKit].beauty.blurUseMask = NO;
        }
    } else {
        // 设置精细磨皮效果
        [FURenderKit shareRenderKit].beauty.blurType = 2;
        [FURenderKit shareRenderKit].beauty.blurUseMask = NO;
    }
}

/// 加载默认美颜
+ (void)loadDefaultBeauty {
    NSString *path = [[NSBundle mainBundle] pathForResource:@"face_beautification" ofType:@"bundle"];
    FUBeauty *beauty = [[FUBeauty alloc] initWithPath:path name:@"FUBeauty"];
    beauty.heavyBlur = 0;
    // 默认均匀磨皮
    beauty.blurType = 3;
    // 默认精细变形
    beauty.faceShape = 4;
    // 高性能设备设置去黑眼圈、去法令纹、大眼、嘴型最新效果
    if ([FURenderKit devicePerformanceLevel] == FUDevicePerformanceLevelHigh) {
        [beauty addPropertyMode:FUBeautyPropertyMode2 forKey:FUModeKeyRemovePouchStrength];
        [beauty addPropertyMode:FUBeautyPropertyMode2 forKey:FUModeKeyRemoveNasolabialFoldsStrength];
        [beauty addPropertyMode:FUBeautyPropertyMode3 forKey:FUModeKeyEyeEnlarging];
        [beauty addPropertyMode:FUBeautyPropertyMode3 forKey:FUModeKeyIntensityMouth];
    }
    [FURenderKit shareRenderKit].beauty = beauty;
}

/// 加载默认美体
+ (void)loadDefaultBody {
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"body_slim" ofType:@"bundle"];
    FUBodyBeauty *bodyBeauty = [[FUBodyBeauty alloc] initWithPath:filePath name:@"body_slim"];
    [FURenderKit shareRenderKit].bodyBeauty = bodyBeauty;
}

@end
