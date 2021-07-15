//
//  UIColor+String.m
//  quickstart
//
//  Created by  on 2021/3/22.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "UIColor+String.h"

@implementation UIColor (String)


+ (UIColor *)colorFromRGBHexString:(NSString *)hexString {
    if (!hexString || hexString.length<0) {
        return [UIColor clearColor];
    }
    unsigned rgbValue = 0;
    NSScanner *scanner = [NSScanner scannerWithString:hexString];
    [scanner setScanLocation:1]; // bypass '#' character
    [scanner scanHexInt:&rgbValue];
    return [UIColor colorWithRed:((rgbValue & 0xFF0000) >> 16)/255.0 green:((rgbValue & 0xFF00) >> 8)/255.0 blue:(rgbValue & 0xFF)/255.0 alpha:1.0];
}

+ (UIColor *)colorFromRGBHexString:(NSString *)hexString andAlpha:(NSInteger)alpha {
    if (!hexString || hexString.length<0) {
        return [UIColor clearColor];
    }
    unsigned rgbValue = 0;
    NSScanner *scanner = [NSScanner scannerWithString:hexString];
    [scanner setScanLocation:1]; // bypass '#' character
    [scanner scanHexInt:&rgbValue];
    return [UIColor colorWithRed:((rgbValue & 0xFF0000) >> 16)/255.0 green:((rgbValue & 0xFF00) >> 8)/255.0 blue:(rgbValue & 0xFF)/255.0 alpha:alpha/255.0];
}

+ (UIColor *)colorFromRGBAHexString:(NSString *)hexString {
    if (!hexString || hexString.length<0) {
        return [UIColor clearColor];
    }
    unsigned rgbValue = 0;
    NSScanner *scanner = [NSScanner scannerWithString:hexString];
    [scanner setScanLocation:1]; // bypass '#' character
    [scanner scanHexInt:&rgbValue];
    return [UIColor colorWithRed:((rgbValue & 0xFF000000) >> 24)/255.0 green:((rgbValue & 0xFF0000) >> 16)/255.0 blue:((rgbValue & 0xFF00)  >> 8)/255.0 alpha:(rgbValue & 0xFF)/255.0];
}

+ (UIColor *)colorFromHexString:(NSString *)hexString {
    if (!hexString) {
        return [UIColor clearColor];
    }
    
    if (hexString.length == 7) {
        return [UIColor colorFromRGBHexString:hexString];
    } else if (hexString.length == 9) {
        return [UIColor colorFromRGBAHexString:hexString];
    } else {
        return [UIColor clearColor];
    }
}

@end
