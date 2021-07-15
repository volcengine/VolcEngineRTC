//
//  BaseUserModel.h
//  veRTC_Demo
//
//  Created by  on 2021/6/28.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseUserModel : NSObject

@property (nonatomic, copy) NSString *phone;

@property (nonatomic, copy) NSString *uid;

@property (nonatomic, copy) NSString *name;

@end

NS_ASSUME_NONNULL_END
