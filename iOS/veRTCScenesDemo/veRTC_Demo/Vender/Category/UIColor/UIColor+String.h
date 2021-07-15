//
//  UIColor+String.h
//  quickstart
//
//  Created by  on 2021/3/22.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (String)

+ (UIColor *)colorFromRGBHexString:(NSString *)hexString;

+ (UIColor *)colorFromRGBHexString:(NSString *)hexString andAlpha:(NSInteger)alpha;

+ (UIColor *)colorFromRGBAHexString:(NSString *)hexString;

+ (UIColor *)colorFromHexString:(NSString *)hexString;

@end

NS_ASSUME_NONNULL_END
