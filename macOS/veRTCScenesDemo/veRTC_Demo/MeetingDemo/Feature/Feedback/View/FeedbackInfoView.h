//
//  FeedbackInfoView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface FeedbackInfoView : NSView

@property (nonatomic, copy) void (^clickInfoCancelBlock)(void);

@property (nonatomic, copy) void (^clickInfoSubmitBlock)(void);

@end

NS_ASSUME_NONNULL_END
