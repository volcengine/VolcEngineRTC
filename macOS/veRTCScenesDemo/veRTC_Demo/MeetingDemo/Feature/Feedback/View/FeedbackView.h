//
//  FeedbackView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import <Cocoa/Cocoa.h>
@class FeedbackView;

@protocol FeedbackViewDeleagte <NSObject>

- (void)feedbackView:(FeedbackView *_Nullable)feedbackView clickButton:(NSInteger)type;

@end

NS_ASSUME_NONNULL_BEGIN

@interface FeedbackView : NSView

@property (nonatomic, weak) id<FeedbackViewDeleagte> deleagte;


@end

NS_ASSUME_NONNULL_END
