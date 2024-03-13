//
//  FUDefines.h
//  FUDemo
//
//  Created by 项林平 on 2021/6/15.
//

#import <CoreGraphics/CoreGraphics.h>
#import <FURenderKit/FURenderKit.h>

#pragma mark - 宏

#define FULocalizedString(key) NSLocalizedStringFromTable(key, @"FaceUnity", nil)


#pragma mark - 枚举

/// 功能模块
typedef NS_ENUM(NSInteger, FUModuleType) {
    FUModuleTypeBeautySkin,             // 美肤
    FUModuleTypeBeautyShape,            // 美型
    FUModuleTypeBeautyFilter,           // 滤镜
    FUModuleTypeSticker,                // 贴纸
    FUModuleTypeMakeup,                 // 美妆
    FUModuleTypeBody                    // 美体
};

typedef NS_ENUM(NSUInteger, FUBeautySkin) {
    FUBeautySkinBlurLevel = 0,
    FUBeautySkinColorLevel,
    FUBeautySkinRedLevel,
    FUBeautySkinSharpen,
    FUBeautySkinFaceThreed,
    FUBeautySkinEyeBright,
    FUBeautySkinToothWhiten,
    FUBeautySkinRemovePouchStrength,
    FUBeautySkinRemoveNasolabialFoldsStrength
};

typedef NS_ENUM(NSUInteger, FUBeautyShape) {
    FUBeautyShapeCheekThinning = 0,
    FUBeautyShapeCheekV,
    FUBeautyShapeCheekNarrow,
    FUBeautyShapeCheekShort,
    FUBeautyShapeCheekSmall,
    FUBeautyShapeCheekbones,
    FUBeautyShapeLowerJaw,
    FUBeautyShapeEyeEnlarging,
    FUBeautyShapeEyeCircle,
    FUBeautyShapeChin,
    FUBeautyShapeForehead,
    FUBeautyShapeNose,
    FUBeautyShapeMouth,
    FUBeautyShapeLipThick,
    FUBeautyShapeEyeHeight,
    FUBeautyShapeCanthus,
    FUBeautyShapeEyeLid,
    FUBeautyShapeEyeSpace,
    FUBeautyShapeEyeRotate,
    FUBeautyShapeLongNose,
    FUBeautyShapePhiltrum,
    FUBeautyShapeSmile,
    FUBeautyShapeBrowHeight,
    FUBeautyShapeBrowSpace,
    FUBeautyShapeBrowThick
};

/// 美体模块子功能
typedef NS_ENUM(NSUInteger, FUBeautyBodyItem) {
    FUBeautyBodyItemSlim,                   // 瘦身
    FUBeautyBodyItemLongLeg,                // 长腿
    FUBeautyBodyItemThinWaist,              // 细腰
    FUBeautyBodyItemBeautyShoulder,         // 美肩
    FUBeautyBodyItemBeautyButtock,          // 美臀
    FUBeautyBodyItemSmallHead,              // 小头
    FUBeautyBodyItemThinLeg,                // 瘦腿
};


#pragma mark - 常量

static CGFloat const FUBottomBarHeight = 49.f;

static CGFloat const FUFunctionViewHeight = 118.f;

static CGFloat const FUFunctionSliderHeight = 30.f;

#pragma mark - 内联函数

static inline CGFloat FUSafaAreaBottomInsets() {
    if (@available(iOS 11.0, *)) {
        return [UIApplication sharedApplication].delegate.window.safeAreaInsets.bottom;
    }
    return 0;
}


