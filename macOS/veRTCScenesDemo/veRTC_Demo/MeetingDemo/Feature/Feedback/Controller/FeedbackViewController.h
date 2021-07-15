//
//  FeedbackViewController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface FeedbackViewController : NSViewController

@property (nonatomic, copy) void (^clickCancelBlock)(void);

@end

NS_ASSUME_NONNULL_END
