//
//  RenderView.m
//  RTCDemo


#import "RenderView.h"
#import "Masonry.h"
#import "NSColor+CorlorString.h"
#import "NSView+Snippet.h"
#import "UserRenderView.h"

@interface RenderView ()

@property (nonatomic, strong) UserRenderView *localView;
@property (nonatomic, strong) UserRenderView *remote1View;
@property (nonatomic, strong) UserRenderView *remote2View;
@property (nonatomic, strong) UserRenderView *remote3View;
@property (nonatomic, strong) NSMutableArray<UserRenderView *> *renderViewList;
@property (nonatomic, strong) ByteRTCVideo *videoEngine;
@property (nonatomic, copy) NSString *loginUid;

@end

@implementation RenderView

- (instancetype)initWithRTC:(ByteRTCVideo *)videoEngine localUid:(NSString *)uid {
    self = [super init];
    if (self) {
        _videoEngine = videoEngine;
        _loginUid = uid;
        
        [self addSubview:self.localView];
        [self.localView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.left.equalTo(self);
            make.width.height.equalTo(self).multipliedBy(0.5);
        }];
        
        [self addSubview:self.remote1View];
        [self.remote1View mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.right.equalTo(self);
            make.width.height.equalTo(self).multipliedBy(0.5);
        }];

        [self addSubview:self.remote2View];
        [self.remote2View mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.left.equalTo(self);
            make.width.height.equalTo(self).multipliedBy(0.5);
        }];

        [self addSubview:self.remote3View];
        [self.remote3View mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.bottom.equalTo(self);
            make.width.height.equalTo(self).multipliedBy(0.5);
        }];
        
        [self.renderViewList addObject:self.localView];
        [self.renderViewList addObject:self.remote1View];
        [self.renderViewList addObject:self.remote2View];
        [self.renderViewList addObject:self.remote3View];
    }
    return self;
}

#pragma mark - Publish Action

- (void)addUser:(NSString *)uid roomid:(NSString *)roomId {

    if ([self.loginUid isEqualToString:uid]) {
        // Local Video
        self.localView.uid = uid;

        ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
        canvas.uid = uid;
        canvas.renderMode = ByteRTCRenderModeHidden;
        canvas.view.backgroundColor = [NSColor redColor];
        canvas.view = self.localView.videoView;
        canvas.roomId = roomId;

        /// 设置本地视频渲染视图
        [self.videoEngine setLocalVideoCanvas:ByteRTCStreamIndexMain withCanvas:canvas];
    } else {
        // Remote Video
        UserRenderView *renderView = [self getRemoteView:uid];
        
        if (renderView) {
            // Update UI
            renderView.uid = uid;

            ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
            canvas.uid = uid;
            canvas.renderMode = ByteRTCRenderModeHidden;
            canvas.view.backgroundColor = [NSColor redColor];
            canvas.view = renderView.videoView;
            canvas.roomId = roomId;
            /// 设置远端用户视频渲染视图
            [self.videoEngine setRemoteVideoCanvas:uid withIndex:ByteRTCStreamIndexMain withCanvas:canvas];
        }

    }
}

- (void)removeUser:(NSString *)uid roomid:(NSString *)roomId {
    for (UserRenderView *renderView in self.renderViewList) {
        if ([renderView.uid isEqualToString:uid]) {
            ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
            canvas.uid = uid;
            canvas.renderMode = ByteRTCRenderModeHidden;
            canvas.view.backgroundColor = [NSColor redColor];
            canvas.view = nil;
            canvas.roomId = roomId;

            [self.videoEngine setRemoteVideoCanvas:uid withIndex:ByteRTCStreamIndexMain withCanvas:canvas];

            // Update UI
            dispatch_async(dispatch_get_main_queue(), ^{
                renderView.uid = @"";
            });
            break;
        }
    }
}

#pragma mark - Private Action

- (UserRenderView *)getRemoteView:(NSString *)uid {
    UserRenderView *showRenderView = nil;
    NSMutableArray<UserRenderView *> *list = [[NSMutableArray alloc] init];
    [list addObject:self.remote1View];
    [list addObject:self.remote2View];
    [list addObject:self.remote3View];
    
    for (int i = 0; i < list.count; i++) {
        UserRenderView *renderView = list[i];
        if ([renderView.uid isEqualToString:uid]) {
            showRenderView = renderView;
            break;
        }
    }
    
    if (!showRenderView) {
        if (self.remote1View.uid.length <= 0) {
            showRenderView = self.remote1View;
        } else if (self.remote2View.uid.length <= 0) {
            showRenderView = self.remote2View;
        } else if (self.remote3View.uid.length <= 0) {
            showRenderView = self.remote3View;
        } else {
            
        }
    }
  
    return showRenderView;
}

#pragma mark - getter

- (UserRenderView *)localView {
    if (!_localView) {
        _localView = [[UserRenderView alloc] init];
    }
    return _localView;
}

- (UserRenderView *)remote1View {
    if (!_remote1View) {
        _remote1View = [[UserRenderView alloc] init];
    }
    return _remote1View;
}

- (UserRenderView *)remote2View {
    if (!_remote2View) {
        _remote2View = [[UserRenderView alloc] init];
    }
    return _remote2View;
}

- (UserRenderView *)remote3View {
    if (!_remote3View) {
        _remote3View = [[UserRenderView alloc] init];
    }
    return _remote3View;
}

- (NSMutableArray<UserRenderView *> *)renderViewList {
    if (!_renderViewList) {
        _renderViewList = [[NSMutableArray alloc] init];
    }
    return _renderViewList;
}

@end
