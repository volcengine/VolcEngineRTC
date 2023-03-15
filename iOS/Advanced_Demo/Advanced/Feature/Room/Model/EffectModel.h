//
//  BeautyModel.h
//  quickstart


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, EffectModelType) {
    EffectModelTypeBeauty   = 0,
    EffectModelTypeFilter   = 1,
    EffectModelTypeSticker  = 2,
    EffectModelTypeVirtual  = 3,
};

@interface EffectModel : NSObject

@property (nonatomic, assign) EffectModelType type;

@property (nonatomic, assign) float value;

@property (nonatomic, assign) BOOL selected;

@property (nonatomic, copy) NSDictionary *dic;

@end

NS_ASSUME_NONNULL_END
