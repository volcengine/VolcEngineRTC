#import "NSColor+CorlorString.h"


@implementation NSColor (CorlorString)

+ (NSColor *)colorFromRGBHexString:(NSString *)hexString {
    if (!hexString || hexString.length<0) {
        return [NSColor clearColor];
    }
    unsigned rgbValue = 0;
    NSScanner *scanner = [NSScanner scannerWithString:hexString];
    [scanner setScanLocation:1]; // bypass '#' character
    [scanner scanHexInt:&rgbValue];
    return [NSColor colorWithRed:((rgbValue & 0xFF0000) >> 16)/255.0 green:((rgbValue & 0xFF00) >> 8)/255.0 blue:(rgbValue & 0xFF)/255.0 alpha:1.0];
}

+ (NSColor *)colorFromRGBHexString:(NSString *)hexString andAlpha:(NSInteger)alpha {
    if (!hexString || hexString.length<0) {
        return [NSColor clearColor];
    }
    unsigned rgbValue = 0;
    NSScanner *scanner = [NSScanner scannerWithString:hexString];
    [scanner setScanLocation:1]; // bypass '#' character
    [scanner scanHexInt:&rgbValue];
    return [NSColor colorWithRed:((rgbValue & 0xFF0000) >> 16)/255.0 green:((rgbValue & 0xFF00) >> 8)/255.0 blue:(rgbValue & 0xFF)/255.0 alpha:alpha/255.0];
}

+ (NSColor *)colorFromRGBAHexString:(NSString *)hexString {
    if (!hexString || hexString.length<0) {
        return [NSColor clearColor];
    }
    unsigned rgbValue = 0;
    NSScanner *scanner = [NSScanner scannerWithString:hexString];
    [scanner setScanLocation:1]; // bypass '#' character
    [scanner scanHexInt:&rgbValue];
    return [NSColor colorWithRed:((rgbValue & 0xFF000000) >> 24)/255.0 green:((rgbValue & 0xFF0000) >> 16)/255.0 blue:((rgbValue & 0xFF00)  >> 8)/255.0 alpha:(rgbValue & 0xFF)/255.0];
}

+ (NSColor *)colorFromHexString:(NSString *)hexString {
    if (!hexString) {
        return [NSColor clearColor];
    }
    
    if (hexString.length == 7) {
        return [NSColor colorFromRGBHexString:hexString];
    } else if (hexString.length == 9) {
        return [NSColor colorFromRGBAHexString:hexString];
    } else {
        return [NSColor clearColor];
    }
}

@end
