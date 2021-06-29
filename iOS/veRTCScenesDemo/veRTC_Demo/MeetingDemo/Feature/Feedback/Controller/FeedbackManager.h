//
//  FeedbackManager.h
//  quickstart

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface FeedbackManager : NSObject

@property (nonatomic, copy) void (^clickCancelBlock)(void);

/*
 * Show feedback view
 */
- (void)show;

/*
 * Close the keyboard showing the view
 */
- (void)textFieldResignFirstResponder;

@end

NS_ASSUME_NONNULL_END
