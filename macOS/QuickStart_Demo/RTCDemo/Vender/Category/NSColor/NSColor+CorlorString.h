#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSColor (CorlorString)
+ (NSColor *)colorFromRGBHexString:(NSString *)hexString;

+ (NSColor *)colorFromRGBHexString:(NSString *)hexString andAlpha:(NSInteger)alpha;

+ (NSColor *)colorFromRGBAHexString:(NSString *)hexString;

+ (NSColor *)colorFromHexString:(NSString *)hexString;
@end

NS_ASSUME_NONNULL_END
