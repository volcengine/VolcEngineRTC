//
//  SettingOptionArrayModel.h
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "SettingBaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingOptionArrayModel : SettingBaseModel
@property (nonatomic, copy) NSArray<NSString *> *optionArray;
@property (nonatomic, assign) NSInteger currentIndex;
@property (nonatomic, copy) void(^didSelectedIndex)(NSInteger index,NSString *title);

- (instancetype)initWithOptionArray:(NSArray<NSString *> *)optionArray defaultIndex:(NSInteger)defaultIndex;
@end

NS_ASSUME_NONNULL_END
