//
//  BaseUserModel.m
//  veRTC_Demo
//
//  Created by  on 2021/6/28.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "BaseUserModel.h"

@implementation BaseUserModel

- (void)encodeWithCoder:(NSCoder *)coder {
    [coder encodeObject:self.phone forKey:@"phone"];
    [coder encodeObject:self.uid forKey:@"uid"];
    [coder encodeObject:self.name forKey:@"name"];
}

- (instancetype)initWithCoder:(NSCoder *)coder {
    self = [super init];
    if (self) {
        self.uid = [coder decodeObjectForKey:@"uid"];
        self.name = [coder decodeObjectForKey:@"name"];
        self.phone = [coder decodeObjectForKey:@"phone"];
    }
    return self;
}

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"uid" : @"user_id",
             @"name" : @"user_name"};
}

@end
