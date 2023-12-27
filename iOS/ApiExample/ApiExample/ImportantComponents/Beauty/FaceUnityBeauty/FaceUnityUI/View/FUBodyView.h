//
//  FUBodyView.h
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/7.
//

#import <UIKit/UIKit.h>
#import "FUBodyViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface FUBodyView : UIView

- (instancetype)initWithFrame:(CGRect)frame viewModel:(FUBodyViewModel *)viewModel;

@end

@interface FUBodyCell : UICollectionViewCell

@property (nonatomic, strong, readonly) UIImageView *imageView;

@property (nonatomic, strong, readonly) UILabel *textLabel;

@property (nonatomic, assign) double currentValue;

@property (nonatomic, assign) double defaultValue;

@property (nonatomic, copy) NSString *imageName;

@property (nonatomic, assign) BOOL defaultInMiddle;

@end

NS_ASSUME_NONNULL_END
