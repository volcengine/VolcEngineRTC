//
//  MenuUpgradeModel.h
//  veRTC_Demo
//
//  Created by  on 2021/6/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MenuUpgradeModel : NSObject

@property (nonatomic, copy) NSString *text;

@property (nonatomic, copy) NSString *url;

@property (nonatomic, assign) NSInteger state;

@end

NS_ASSUME_NONNULL_END
