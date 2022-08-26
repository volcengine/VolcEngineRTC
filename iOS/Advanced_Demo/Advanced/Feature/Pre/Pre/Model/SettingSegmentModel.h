//
//  SettingSegmentModel.h
//  Advanced
//
//

#import "SettingBaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingSegmentModel : SettingBaseModel

@property (nonatomic, assign) NSInteger selectedIndex;

@property (nonatomic, strong) NSArray<NSString *> *actionTitles;

@property (nonatomic, copy) void(^segmentDidChangeSelectedIndex)(NSInteger index);

- (instancetype)initWithDefaultSelectedIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
