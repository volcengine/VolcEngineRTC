//
//  VolcBeautyCommon.h
//  Advanced
//
//  Created by bytedance on 2022/2/11.
//

#import <Foundation/Foundation.h>
#import "EffectResource.h"
#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VolcBeautyCommon : NSObject

/// 初始化
/// @param rtcKit RTC 引擎
- (instancetype)initWithRtcKit:(ByteRTCEngineKit *)rtcKit;

/// 选择贴纸
/// @param path 贴纸路径
/// @param isSelected 选中、取消选中
- (void)didClickedStickerEffect:(NSString *)path
                       selected:(BOOL)isSelected;

/// 选择滤镜
/// @param path 滤镜路径
/// @param value 滤镜强度，取值范围 [0,1]，超出范围时设置无效
- (void)didClickedFilterEffect:(NSString *)path
                         value:(CGFloat)value;

/// 更新滤镜强度
/// @param value 滤镜强度，取值范围 [0,1]，超出范围时设置无效
- (void)didChangeFilterEffect:(CGFloat)value;

/// 选择背景分割
/// @param type 颜色背景、图片背景
/// @param isSelected 选中、取消选中
- (void)didClickedVirtualEffect:(NSString *)type
                       selected:(BOOL)isSelected;


/// 选择美颜
/// @param key 美颜Key
/// @param value 取值范围为 [0,1]，超出该范围设置无效。
- (void)didChangeBeautyEffect:(NSString *)key
                        value:(CGFloat)value;

/// 选择美形
/// @param key 美形Key
/// @param value 取值范围为 [0,1]，超出该范围设置无效。
- (void)didChangeReshapeEffect:(NSString *)key
                         value:(CGFloat)value;

/// 默认展示数据
- (void)didDefaultSetting;

@end

NS_ASSUME_NONNULL_END
