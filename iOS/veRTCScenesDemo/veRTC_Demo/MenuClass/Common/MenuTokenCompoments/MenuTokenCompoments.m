//
//  MenuTokenCompoments.m
//  veRTC_Demo
//
//  Created by  on 2021/7/2.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "MenuTokenCompoments.h"

@implementation MenuTokenCompoments

+ (void)updateToken:(NSString *)token {
    if (IsEmptyStr(token)) {
        token = @"";
    }
    [[NSUserDefaults standardUserDefaults] setObject:token forKey:@"KMenuTokenCompoments"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

+ (NSString *)token {
    NSString *token = [[NSUserDefaults standardUserDefaults] objectForKey:@"KMenuTokenCompoments"];
    return token;
}

@end
