//
//  BeautyBarView.h
//  quickstart


#import <UIKit/UIKit.h>
#import "EffectModel.h"

@class BeautyBarView;
@protocol BeautyBarViewDelegate <NSObject>

- (void)beautyBarView:(BeautyBarView *_Nonnull)barView didClickedEffect:(EffectModel *_Nonnull)model;

- (void)beautyBarView:(BeautyBarView *_Nonnull)barView didChangeEffectValue:(EffectModel *_Nonnull)model;

@end

NS_ASSUME_NONNULL_BEGIN

@interface BeautyBarView : UIView
@property (nonatomic, weak) id<BeautyBarViewDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
