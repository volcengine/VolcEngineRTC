//
//  GalleryModeView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import "GalleryModeView.h"
#import "RoomAvatarRenderView.h"
#import "GalleryModeLineView.h"

@interface GalleryModeView ()

@property (nonatomic, strong) GalleryModeLineView *topView;
@property (nonatomic, strong) GalleryModeLineView *centerView;
@property (nonatomic, strong) GalleryModeLineView *bottomView;

@end

@implementation GalleryModeView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.bottomView];
        [self addSubview:self.centerView];
        [self addSubview:self.topView];
    }
    return self;
}

- (void)layout {
    [super layout];
    
    CGFloat viewWidth = self.frame.size.width;
    CGFloat viewHeight = self.frame.size.height;
    CGFloat itemHeight = viewHeight;
    CGFloat itemSpace = 24;
    if (self.dataLists.count == 1) {
        //format 1
        self.topView.hidden = NO;
        self.centerView.hidden = YES;
        self.bottomView.hidden = YES;
        self.topView.frame = CGRectMake(0,
                                        0,
                                        viewWidth,
                                        itemHeight);
        self.centerView.frame = CGRectZero;
        self.bottomView.frame = CGRectZero;
        
        [self updateSpaceHorizontalWithDataLists:self.dataLists lineView:self.topView lineXaxNum:1 avatarStatus:RoomAvatarStatusGalleryOne];
    } else if (self.dataLists.count == 2) {
        //format 1 * 2
        self.topView.hidden = NO;
        self.centerView.hidden = YES;
        self.bottomView.hidden = YES;
        itemHeight = viewHeight - 150 - 200;
        self.topView.frame = CGRectMake(0,
                                        150,
                                        viewWidth,
                                        itemHeight);
        self.centerView.frame = CGRectZero;
        self.bottomView.frame = CGRectZero;
        
        [self updateSpaceHorizontalWithDataLists:self.dataLists lineView:self.topView lineXaxNum:2 avatarStatus:RoomAvatarStatusGalleryTwo];
    } else if (self.dataLists.count == 3 || self.dataLists.count == 4) {
        //format 2 * 2
        self.topView.hidden = NO;
        self.centerView.hidden = NO;
        self.bottomView.hidden = YES;
        itemHeight = (self.frame.size.height - itemSpace - 60) / 2;
        self.topView.frame = CGRectMake(0,
                                        0,
                                        viewWidth,
                                        itemHeight);
        self.centerView.frame = CGRectMake(0,
                                           itemHeight + itemSpace,
                                           viewWidth,
                                           itemHeight);
        self.bottomView.frame = CGRectZero;

        NSInteger lineMaxNum = 2;
        NSArray *topLists = [self.dataLists subarrayWithRange:NSMakeRange(0, lineMaxNum)];
        NSArray *bottomLists = [self.dataLists subarrayWithRange:NSMakeRange(lineMaxNum, self.dataLists.count - lineMaxNum)];
        [self updateSpaceHorizontalWithDataLists:topLists lineView:self.topView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryFour];
        [self updateSpaceHorizontalWithDataLists:bottomLists lineView:self.centerView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryFour];
    } else if (self.dataLists.count == 5 || self.dataLists.count == 6) {
        //format 2 * 3
        self.topView.hidden = NO;
        self.centerView.hidden = NO;
        self.bottomView.hidden = YES;
        itemHeight = (self.frame.size.height - itemSpace - 60) / 2;
        self.topView.frame = CGRectMake(0,
                                        0,
                                        viewWidth,
                                        itemHeight);
        self.centerView.frame = CGRectMake(0,
                                           itemHeight + itemSpace,
                                           viewWidth,
                                           itemHeight);
        self.bottomView.frame = CGRectZero;

        NSInteger lineMaxNum = 3;
        NSArray *topLists = [self.dataLists subarrayWithRange:NSMakeRange(0, lineMaxNum)];
        NSArray *bottomLists = [self.dataLists subarrayWithRange:NSMakeRange(lineMaxNum, self.dataLists.count - lineMaxNum)];
        [self updateSpaceHorizontalWithDataLists:topLists lineView:self.topView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryFour];
        [self updateSpaceHorizontalWithDataLists:bottomLists lineView:self.centerView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryFour];
    } else if (self.dataLists.count > 6) {
        //format 3 * 3
        self.topView.hidden = NO;
        self.centerView.hidden = NO;
        self.bottomView.hidden = NO;
        itemHeight = (self.frame.size.height - (itemSpace * 2) - 60) / 3;
        self.topView.frame = CGRectMake(0,
                                        0,
                                        viewWidth,
                                        itemHeight);
        self.centerView.frame = CGRectMake(0,
                                           itemHeight + itemSpace,
                                           viewWidth,
                                           itemHeight);
        self.bottomView.frame = CGRectMake(0,
                                           (itemHeight + itemSpace) * 2,
                                           viewWidth,
                                           itemHeight);
        
        //Display at most Three in a row
        NSInteger lineMaxNum = 3;
        NSArray *topLists = [self.dataLists subarrayWithRange:NSMakeRange(0, lineMaxNum)];
        NSArray *centerLists = [self.dataLists subarrayWithRange:NSMakeRange(lineMaxNum, self.dataLists.count - lineMaxNum)];
        NSArray *bottomLists = nil;
        if (self.dataLists.count > lineMaxNum * 2) {
            bottomLists = [self.dataLists subarrayWithRange:NSMakeRange(lineMaxNum * 2, self.dataLists.count - (lineMaxNum * 2))];
        }

        [self updateSpaceHorizontalWithDataLists:topLists lineView:self.topView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryNine];
        [self updateSpaceHorizontalWithDataLists:centerLists lineView:self.centerView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryNine];
        [self updateSpaceHorizontalWithDataLists:bottomLists lineView:self.bottomView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryNine];
    } else {
        //error
    }
}

#pragma mark - Private Action

- (void)updateSpaceHorizontalWithDataLists:(NSArray *)dataLists lineView:(GalleryModeLineView *)lineView lineXaxNum:(NSInteger)maxNum avatarStatus:(RoomAvatarStatus)avatarStatus {
    CGFloat itemSpace = 24;
    for (int i = 0; i < lineView.avatarViewLists.count; i++) {
        RoomAvatarRenderView *avatarView = lineView.avatarViewLists[i];
        avatarView.avatarStatus = avatarStatus;
        if (i < dataLists.count) {
            avatarView.hidden = NO;
            avatarView.userModel = dataLists[i];
        } else {
            avatarView.hidden = YES;
            avatarView.userModel = nil;
        }
        CGFloat viewWidth = self.frame.size.width;
        CGFloat itemWidth = (viewWidth - (itemSpace * (maxNum + 1))) / maxNum;
        CGFloat itemLeft = (i * itemWidth) + (itemSpace * (i + 1));
        if (maxNum == 1) {
            itemWidth = self.frame.size.width;
            itemLeft = 0;
        }
        avatarView.frame = CGRectMake(itemLeft,
                                      0,
                                      itemWidth,
                                      lineView.bounds.size.height);
    }
}

#pragma mark - Publish Action


- (void)setHidden:(BOOL)hidden {
    [super setHidden:hidden];
}

- (void)setDataLists:(NSArray<RoomUserModel *> *)dataLists {
    _dataLists = dataLists;
    
    if (self.hidden) {
        return;
    }
 
    [self setNeedsLayout:YES];
}

#pragma mark - getter

- (GalleryModeLineView *)topView {
    if (!_topView) {
        _topView = [[GalleryModeLineView alloc] init];
        [_topView setBackgroundColor:[NSColor clearColor]];
    }
    return _topView;
}

- (GalleryModeLineView *)centerView {
    if (!_centerView) {
        _centerView = [[GalleryModeLineView alloc] init];
        [_centerView setBackgroundColor:[NSColor clearColor]];
    }
    return _centerView;
}

- (GalleryModeLineView *)bottomView {
    if (!_bottomView) {
        _bottomView = [[GalleryModeLineView alloc] init];
        [_bottomView setBackgroundColor:[NSColor clearColor]];
    }
    return _bottomView;
}

- (BOOL)isFlipped {
    return YES;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
