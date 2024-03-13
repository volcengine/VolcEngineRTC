//
//  FUMakeupView.h
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/6.
//

#import <UIKit/UIKit.h>
#import "FUMakeupViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface FUMakeupView : UIView

- (instancetype)initWithFrame:(CGRect)frame viewModel:(FUMakeupViewModel *)viewModel;

@end

@interface FUMakeupCell : UICollectionViewCell

@property (nonatomic, strong, readonly) UIImageView *imageView;
@property (nonatomic, strong, readonly) UILabel *textLabel;

@end

NS_ASSUME_NONNULL_END
