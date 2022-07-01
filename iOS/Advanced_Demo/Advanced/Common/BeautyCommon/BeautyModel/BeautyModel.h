//
//  BeautyModel.h
//  Advanced
//
//  Created by bytedance on 2022/5/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BeautyModel : NSObject

+ (NSArray *)sectionList;

+ (NSArray *)beautyList;

+ (NSArray *)stickerList;

+ (NSArray *)filterList;

+ (NSArray *)virtualBackgroundList;

@end

NS_ASSUME_NONNULL_END
