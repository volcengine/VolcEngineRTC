//
//  RoomSetting.m
//  Advanced
//
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
