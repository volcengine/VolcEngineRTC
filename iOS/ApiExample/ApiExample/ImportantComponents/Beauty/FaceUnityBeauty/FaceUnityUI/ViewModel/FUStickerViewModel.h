//
//  FUStickerViewModel.h
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/6.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class FUStickerModel;

NS_ASSUME_NONNULL_BEGIN

@interface FUStickerViewModel : NSObject

@property (nonatomic, copy, readonly) NSArray<FUStickerModel *> *stickers;
/// 选中滤镜索引
@property (nonatomic, assign) NSInteger selectedIndex;

- (UIImage *)stickerIconAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
