//
//  SetingViewController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import <Cocoa/Cocoa.h>
@class SetingViewController;
NS_ASSUME_NONNULL_BEGIN

@protocol SetingViewControllerDelegate <NSObject>

- (void)setingViewController:(SetingViewController *)setingViewController cancelAction:(BOOL)isCancel;

@end

@interface SetingViewController : NSViewController

@property (nonatomic, weak) id<SetingViewControllerDelegate> delegate;

+ (BOOL)getParamSwitch;

@end

NS_ASSUME_NONNULL_END
