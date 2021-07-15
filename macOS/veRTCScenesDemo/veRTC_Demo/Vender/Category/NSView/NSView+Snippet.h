//
//  NSView+Snippet.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSView (Snippet)

- (void)setBackgroundColor:(NSColor *)color;

- (void)setBackgroundColorWithHexString:(NSString *)hexString;

- (void)setBackgroundColorWithHexString:(NSString *)hexString andAlpha:(NSInteger)alpha;

- (void)removeAllSubView;

- (void)removeAllAutoLayout;

@end

NS_ASSUME_NONNULL_END
