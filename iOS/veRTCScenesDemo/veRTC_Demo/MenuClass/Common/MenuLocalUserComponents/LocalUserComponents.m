//
//  LocalUserComponents.m
//  veRTC_Demo
//
//  Created by  on 2021/5/28.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "LocalUserComponents.h"

@implementation LocalUserComponents

#pragma mark - Publish Action

+ (BaseUserModel *)userModel {
    NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"KUserinfoDic"];
    BaseUserModel *user = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    if (user == nil || ![user isKindOfClass:[BaseUserModel class]]) {
        user = [[BaseUserModel alloc] init];
    }
    return user;
}

+ (void)updateLocalUserModel:(BaseUserModel *)userModel {
    if (userModel && [userModel isKindOfClass:[BaseUserModel class]]) {
        NSData *data = [NSKeyedArchiver archivedDataWithRootObject:userModel];
        [[NSUserDefaults standardUserDefaults] setObject:data forKey:@"KUserinfoDic"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    } else if (userModel == nil) {
        [[NSUserDefaults standardUserDefaults] setObject:nil forKey:@"KUserinfoDic"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

#pragma mark - tool

+ (BOOL)isMatchUserName:(NSString *)userName {
    if (IsEmptyStr(userName)) {
        return YES;
    }
    NSString *match = @"^[\u4e00-\u9fa5_a-zA-Z0-9]+$";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF matches %@", match];
    return [predicate evaluateWithObject:userName];
}

+ (BOOL)isMatchRoomID:(NSString *)roomid {
    if (IsEmptyStr(roomid)) {
        return YES;
    }
    NSString *match = @"^[A-Za-z0-9@._-]+$";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF matches %@", match];
    return [predicate evaluateWithObject:roomid];
}

+ (BOOL)isMatchNumber:(NSString *)number {
    if (IsEmptyStr(number)) {
        return YES;
    }
    NSString *match = @"[0-9]*";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF matches %@", match];
    return [predicate evaluateWithObject:number];
}

@end
