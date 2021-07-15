//
//  NSButton+Snippet.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSButton (Snippet)

- (instancetype)init;

- (void)setTitleColor:(NSString *)hexString title:(NSString *)title;

- (void)setTitleColor:(NSString *)hexString andAlpha:(NSInteger)andAlpha title:(NSString *)title;

@end

NS_ASSUME_NONNULL_END
