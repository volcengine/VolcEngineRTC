//
//  LoginBottonErrorView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface LoginBottonErrorView : NSView

@property (nonatomic, copy) NSString *title;

@property (nonatomic, copy) NSString *message;

+ (LoginBottonErrorView *)shareLoginBottonErrorView;

- (void)show:(NSView *)superView;

- (void)dismiss;

@end

NS_ASSUME_NONNULL_END
