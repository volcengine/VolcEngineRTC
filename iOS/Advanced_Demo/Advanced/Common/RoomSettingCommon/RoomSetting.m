//
//  RoomSetting.m
//  Advanced
//
//  Created by bytedance on 2021/12/8.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "RoomSetting.h"

@implementation RoomSetting
- (instancetype)init {
    if (self = [super init]) {
        self.resolution = CGSizeMake(360, 640);
        self.fps = 15;
        self.bitrate = 400;
        // 默认仅本地渲染镜像
        self.localRenderMirror = 1;
    }
    return self;
}

+ (instancetype)defaultSetting {
    return [[self alloc] init];
}

@end
