//
//  FUStickerView.h
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/6.
//

#import <UIKit/UIKit.h>
#import "FUStickerViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface FUStickerView : UIView

- (instancetype)initWithFrame:(CGRect)frame viewModel:(FUStickerViewModel *)viewModel;

@end

@interface FUStickerCell : UICollectionViewCell

@property (nonatomic, strong, readonly) UIImageView *imageView;

@end

NS_ASSUME_NONNULL_END
