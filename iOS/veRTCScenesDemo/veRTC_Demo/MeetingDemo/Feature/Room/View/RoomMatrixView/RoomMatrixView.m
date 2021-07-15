#import "RoomMatrixView.h"
#import "RoomAvatarRenderView.h"
#import "GalleryModeLineView.h"
#import "UIView+Fillet.h"

@interface RoomMatrixView ()

@property (nonatomic, strong) GalleryModeLineView *topView;
@property (nonatomic, strong) GalleryModeLineView *centerView;
@property (nonatomic, strong) GalleryModeLineView *bottomView;

@property (nonatomic, strong) NSString *currentUids;

@end

@implementation RoomMatrixView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.topView];
        [self addSubview:self.centerView];
        [self addSubview:self.bottomView];
    }
    return self;
}

#pragma mark - Publish Action


- (void)setHidden:(BOOL)hidden {
    [super setHidden:hidden];
    
    self.currentUids = @"";
}

- (void)bindVideoSessions:(NSArray<RoomVideoSession *> *)videoSessions {
    NSArray *dataLists = [videoSessions subarrayWithRange:NSMakeRange(0, MIN(videoSessions.count, 9))];;
    
    [self.topView removeAllSubviews];
    [self.centerView removeAllSubviews];
    [self.bottomView removeAllSubviews];
    
    [self.topView removeAllAutoLayout];
    [self.centerView removeAllAutoLayout];
    [self.bottomView removeAllAutoLayout];
    
    if (dataLists.count == 1) {
        //format 1
        [self.centerView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.left.top.bottom.equalTo(self);
            make.right.equalTo(self).offset(0);
        }];
        
        [self updateSpaceHorizontalWithDataLists:dataLists lineView:self.centerView lineXaxNum:1 avatarStatus:RoomAvatarStatusGalleryOne];
    } else if (dataLists.count == 2) {
        //format 2 * 1
        NSMutableArray *liveViewLists = [[NSMutableArray alloc] init];
        [liveViewLists addObject:self.topView];
        [liveViewLists addObject:self.bottomView];
    
        [liveViewLists mas_distributeViewsAlongAxis:MASAxisTypeVertical withFixedSpacing:20 leadSpacing:20 tailSpacing:20];
        [liveViewLists mas_updateConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self).offset(16);
            make.right.equalTo(self).offset(-16);
        }];

        NSInteger lineMaxNum = 1;
        NSArray *topLists = [dataLists subarrayWithRange:NSMakeRange(0, lineMaxNum)];
        NSArray *bottomLists = [dataLists subarrayWithRange:NSMakeRange(lineMaxNum, dataLists.count - lineMaxNum)];
        [self updateSpaceHorizontalWithDataLists:topLists lineView:self.topView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryNone];
        [self updateSpaceHorizontalWithDataLists:bottomLists lineView:self.bottomView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryNone];
        
    } else if (dataLists.count == 3 || dataLists.count == 4) {
        //format 2 * 2
        NSMutableArray *liveViewLists = [[NSMutableArray alloc] init];
        [liveViewLists addObject:self.topView];
        [liveViewLists addObject:self.bottomView];
    
        [liveViewLists mas_distributeViewsAlongAxis:MASAxisTypeVertical withFixedSpacing:20 leadSpacing:20 tailSpacing:20];
        [liveViewLists mas_updateConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self).offset(16);
            make.right.equalTo(self).offset(-16);
        }];

        NSInteger lineMaxNum = 2;
        NSArray *topLists = [dataLists subarrayWithRange:NSMakeRange(0, lineMaxNum)];
        NSArray *bottomLists = [dataLists subarrayWithRange:NSMakeRange(lineMaxNum, dataLists.count - lineMaxNum)];
        [self updateSpaceHorizontalWithDataLists:topLists lineView:self.topView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryNone];
        [self updateSpaceHorizontalWithDataLists:bottomLists lineView:self.bottomView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryNone];
    } else if (dataLists.count >= 5) {
        //format 3 * 3
        NSMutableArray *liveViewLists = [[NSMutableArray alloc] init];
        [liveViewLists addObject:self.topView];
        [liveViewLists addObject:self.centerView];
        [liveViewLists addObject:self.bottomView];
        
        [liveViewLists mas_distributeViewsAlongAxis:MASAxisTypeVertical withFixedSpacing:12 leadSpacing:12 tailSpacing:12];
        [liveViewLists mas_updateConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self).offset(16);
            make.right.equalTo(self).offset(-16);
        }];
        
        //Display at most Three in a row
        NSInteger lineMaxNum = 2;
        NSArray *topLists = [dataLists subarrayWithRange:NSMakeRange(0, lineMaxNum)];
        NSArray *centerLists = [dataLists subarrayWithRange:NSMakeRange(lineMaxNum, dataLists.count - lineMaxNum)];
        NSArray *bottomLists = nil;
        if (dataLists.count > lineMaxNum * 2) {
            bottomLists = [dataLists subarrayWithRange:NSMakeRange(lineMaxNum * 2, dataLists.count - (lineMaxNum * 2))];
        }

        [self updateSpaceHorizontalWithDataLists:topLists lineView:self.topView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryFull];
        [self updateSpaceHorizontalWithDataLists:centerLists lineView:self.centerView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryFull];
        [self updateSpaceHorizontalWithDataLists:bottomLists lineView:self.bottomView lineXaxNum:lineMaxNum avatarStatus:RoomAvatarStatusGalleryFull];
    } else {
        //error
    }
}

- (void)updateSpaceHorizontalWithDataLists:(NSArray *)dataLists lineView:(GalleryModeLineView *)lineView lineXaxNum:(NSInteger)maxNum avatarStatus:(RoomAvatarStatus)avatarStatus {
    if (maxNum <= 1) {
        RoomAvatarRenderView *avatarView = lineView.avatarViewLists.firstObject;
        avatarView.avatarStatus = avatarStatus;
        avatarView.userModel = dataLists.firstObject;
        [lineView addSubview:avatarView];
        [avatarView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(lineView);
        }];
    } else {
        NSMutableArray *viewLists = [[NSMutableArray alloc] init];
        for (int i = 0; i < maxNum; i++) {
            RoomAvatarRenderView *avatarView = lineView.avatarViewLists[i];
            avatarView.avatarStatus = avatarStatus;
            [lineView addSubview:avatarView];
            [viewLists addObject:avatarView];

            if (i < dataLists.count) {
                avatarView.userModel = dataLists[i];
                avatarView.hidden = NO;
            } else {
                avatarView.userModel = nil;
                avatarView.hidden = YES;
            }
        }

        [viewLists mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedSpacing:16 leadSpacing:0 tailSpacing:0];
        [viewLists mas_updateConstraints:^(MASConstraintMaker *make) {
            make.top.bottom.equalTo(lineView);
        }];
    }
}

#pragma mark - Private Action

- (BOOL)isNeedRefreshWithModels:(NSArray<RoomVideoSession *> *)dataLists {
    BOOL isRefres = NO;
    NSArray *uids = [self getUidsWithModels:dataLists];
    NSString *tempUids = @"";
    for (int i = 0; i < uids.count; i++) {
        tempUids = [NSString stringWithFormat:@"%@%@", tempUids, uids[i]];
    }
    
    if (dataLists.count == 1) {
        RoomVideoSession *model = dataLists.firstObject;
        tempUids = [NSString stringWithFormat:@"%@-%ld", model.uid, (long)model.isEnableVideo];
        if (![tempUids isEqualToString:self.currentUids]) {
            isRefres = YES;
            self.currentUids = tempUids;
        }
    } else {
        if (tempUids.length > 0 && ![self.currentUids isEqualToString:tempUids]) {
            isRefres = YES;
            self.currentUids = tempUids;
        }
    }
    
    return isRefres;
}

- (NSArray<NSString *> *)getUidsWithModels:(NSArray<RoomVideoSession *> *)dataLists {
    NSInteger maxLen = MIN(dataLists.count, 9);
    NSArray *lists = [dataLists subarrayWithRange:NSMakeRange(0, maxLen)];
    NSMutableArray *uids = [[NSMutableArray alloc] init];
    for (int i = 0; i < lists.count; i++) {
        RoomVideoSession *userModel = lists[i];
        NSString *cansKey = userModel.isVideoStream ? @"1" : @"0";
        NSString *videoID = [NSString stringWithFormat:@"%@%@|", userModel.uid, cansKey];
        [uids addObject:videoID];
    }
    return [uids copy];
}

#pragma mark - getter

- (GalleryModeLineView *)topView {
    if (!_topView) {
        _topView = [[GalleryModeLineView alloc] init];
        _topView.backgroundColor = [UIColor clearColor];
    }
    return _topView;
}

- (GalleryModeLineView *)centerView {
    if (!_centerView) {
        _centerView = [[GalleryModeLineView alloc] init];
        _centerView.backgroundColor = [UIColor clearColor];
    }
    return _centerView;
}

- (GalleryModeLineView *)bottomView {
    if (!_bottomView) {
        _bottomView = [[GalleryModeLineView alloc] init];
        _bottomView.backgroundColor = [UIColor clearColor];
    }
    return _bottomView;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
