//
//  FUBeautyFilterView.h
//  FUBeautyComponent
//
//  Created by 项林平 on 2022/6/21.
//

#import <UIKit/UIKit.h>
#import "FUBeautyFilterViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface FUBeautyFilterView : UIView

- (instancetype)initWithFrame:(CGRect)frame viewModel:(FUBeautyFilterViewModel *)viewModel;

@end

@interface FUBeautyFilterCell : UICollectionViewCell

@property (nonatomic, strong, readonly) UIImageView *imageView;
@property (nonatomic, strong, readonly) UILabel *textLabel;

@end

NS_ASSUME_NONNULL_END
