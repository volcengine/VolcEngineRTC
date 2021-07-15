//
//  GalleryModeLineView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import "GalleryModeLineView.h"

@interface GalleryModeLineView ()

@end

@implementation GalleryModeLineView

- (instancetype)init {
    self = [super init];
    if (self) {
        NSMutableArray *lists = [[NSMutableArray alloc] init];
        for (int i = 0; i < 3; i++) {
            RoomAvatarRenderView *avatarView = [[RoomAvatarRenderView alloc] init];
            [lists addObject:avatarView];
            [self addSubview:avatarView];
        }
        _avatarViewLists = [lists copy];
    }
    return self;
}

@end
