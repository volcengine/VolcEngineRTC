//
//  VoiceIMModel.h
//  veRTC_Demo
//
//  Created by  on 2021/5/28.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VoiceIMModel : NSObject

@property (nonatomic, assign) BOOL isJoin;

@property (nonatomic, strong) VoiceControlUserModel *userModel;

@end

NS_ASSUME_NONNULL_END
