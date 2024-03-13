//
//  FUMakeupModel.h
//  XPYCamera
//
//  Created by 项林平 on 2021/7/19.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FUMakeupModel : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *bundleName;
@property (nonatomic, copy) NSString *icon;
@property (nonatomic, assign) double value;

@end

NS_ASSUME_NONNULL_END
