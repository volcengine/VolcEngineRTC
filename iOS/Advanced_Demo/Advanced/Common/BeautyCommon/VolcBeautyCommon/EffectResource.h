//
//  EffectResource.h
//  quickstart


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface EffectResource : NSObject

/// 获取 license 路径
+ (NSString *)licensePath;

/// 获取 ModelResource 路径
+ (NSString *)modelPath;

/// 获取 ComposeMakeup/美颜 路径
+ (NSString *)beautyCameraPath;

/// 获取 ComposeMakeup/美形 路径
+ (NSString *)reshapeCameraPath;

/// 获取 ModelResource/背景分割模型 路径
+ (NSString *)getByteEffectPortraitPath;

/// 获取贴纸路径
/// @param stickerName 贴纸文件名
+ (NSString *)stickerPathWithName:(NSString *)stickerName;

/// 获取滤镜路径
/// @param filterName 滤镜文件名
+ (NSString *)filterPathWithName:(NSString *)filterName;

@end

NS_ASSUME_NONNULL_END
