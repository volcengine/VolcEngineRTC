//
//  LocalUserCompoments.h
//  veRTC_Demo
//
//  Created by  on 2021/5/28.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseUserModel.h"

@interface LocalUserCompoments : NSObject

+ (BaseUserModel *)userModel;

+ (void)updateLocalUserModel:(BaseUserModel *)userModel;

+ (BOOL)isMatchUserName:(NSString *)userName;

+ (BOOL)isMatchRoomID:(NSString *)roomid;

+ (BOOL)isMatchNumber:(NSString *)number;

@end
