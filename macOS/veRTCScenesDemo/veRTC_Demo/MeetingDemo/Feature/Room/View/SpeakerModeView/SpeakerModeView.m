//
//  SpeakerModeView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import "SpeakerModeView.h"

//1440 - (12 * 7)
static const NSInteger ItemWidth = 160;

@interface SpeakerModeView ()

@property (nonatomic, strong) NSView *avatarListView;
@property (nonatomic, strong) NSView *screenView;

@property (nonatomic, assign) BOOL avatarHidden;

@end

@implementation SpeakerModeView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.avatarHidden = NO;
        [self addSubviewAndConstraints];
    }
    return self;
}

- (void)addSubviewAndConstraints {
    [self addSubview:self.avatarListView];
    [self.avatarListView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(0);
        make.height.mas_equalTo(92);
        make.centerX.top.equalTo(self);
    }];
    
    for (int i = 0; i < MaxAvatarNumber - 1; i++) {
        RoomAvatarRenderView *avatarView = [[RoomAvatarRenderView alloc] init];
        avatarView.avatarStatus = RoomAvatarStatusSpaker;
        [self.avatarListView addSubview:avatarView];
    }
    
    [self addSubview:self.screenView];
    [self.screenView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.bottom.equalTo(self);
        make.right.equalTo(self).offset(0);
        make.top.equalTo(self.avatarListView.mas_bottom).offset(8);
    }];
}

- (void)resizeSubviewsWithOldSize:(NSSize)oldSize {
    if (self.avatarListView.frame.size.width > oldSize.width) {
        //left
        [self.avatarListView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(self.avatarHidden ? 0 : 92);
            make.left.top.equalTo(self);
        }];
    } else {
        //center X
        [self.avatarListView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(self.avatarHidden ? 0 : 92);
            make.centerX.equalTo(self).offset(0);
            make.top.equalTo(self);
        }];
    }
    
    if (self.dataLists.count > 0) {
        NSInteger dataCount = MIN(self.dataLists.count, 8);
        CGFloat width = (dataCount * ItemWidth) + ((dataCount - 1) * 16);
        [self.avatarListView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.width.mas_equalTo(width);
        }];
    }
}

#pragma mark - Publish Action

- (void)setHidden:(BOOL)hidden {
    [super setHidden:hidden];
    
    if (hidden) {
        for (RoomAvatarRenderView *view in self.avatarListView.subviews) {
            view.userModel = nil;
        }
    }
}

- (void)setDataLists:(NSArray<RoomUserModel *> *)dataLists {
    _dataLists = dataLists;
    
    if (self.hidden || dataLists.count <= 0) {
        return;
    }
    
    NSMutableArray *viewLists = [[NSMutableArray alloc] init];
    for (int i = 0; i < self.avatarListView.subviews.count; i++) {
        RoomAvatarRenderView *avatarView = self.avatarListView.subviews[i];
        if (i < dataLists.count) {
            avatarView.hidden = NO;
            avatarView.userModel = dataLists[i];
            [viewLists addObject:avatarView];
        } else {
            avatarView.hidden = YES;
            avatarView.userModel = nil;
        }
    }
    
    NSInteger dataCount = MIN(self.dataLists.count, 8);
    CGFloat width = (dataCount * ItemWidth) + ((dataCount - 1) * 16);
    [self.avatarListView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(width);
    }];
    
    if (viewLists.count >= 2) {
        [viewLists mas_remakeConstraints:^(MASConstraintMaker *make) {
            
        }];
        [viewLists mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedItemLength:ItemWidth leadSpacing:0 tailSpacing:0];
        [viewLists mas_updateConstraints:^(MASConstraintMaker *make) {
            make.top.height.equalTo(self.avatarListView);
        }];
    }
    
    [self layout];
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    NSView *windowView = appDelegate.windowManager.currentWindowController.window.contentView;
    NSSize windowSize = CGSizeMake(windowView.frame.size.width, windowView.frame.size.height);
    [self resizeSubviewsWithOldSize:windowSize];
}

- (void)setScreenStreamsUid:(NSString *)screenStreamsUid {
    _screenStreamsUid = screenStreamsUid;
    if (screenStreamsUid && screenStreamsUid.length > 0) {
        [[MeetingRTCManager shareMeetingRTCManager] setupRemoteScreen:self.screenView uid:screenStreamsUid];
        [[MeetingRTCManager shareMeetingRTCManager] subscribeScreenStream:screenStreamsUid];
    } else {
        [[MeetingRTCManager shareMeetingRTCManager] setupRemoteScreen:nil uid:screenStreamsUid];
        [[MeetingRTCManager shareMeetingRTCManager] unsubscribeScreen:screenStreamsUid];
    }
}

- (void)updateAvatarHidden:(BOOL)isHidden {
    self.avatarHidden = isHidden;
    if (isHidden) {
        [self.avatarListView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(0);
        }];
    } else {
        [self.avatarListView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(92);
        }];
    }
}

#pragma mark - getter

- (NSView *)avatarListView {
    if (!_avatarListView) {
        _avatarListView = [[NSView alloc] init];
        [_avatarListView setBackgroundColor:[NSColor clearColor]];
    }
    return _avatarListView;
}

- (NSView *)screenView {
    if (!_screenView) {
        _screenView = [[NSView alloc] init];
    }
    return _screenView;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
