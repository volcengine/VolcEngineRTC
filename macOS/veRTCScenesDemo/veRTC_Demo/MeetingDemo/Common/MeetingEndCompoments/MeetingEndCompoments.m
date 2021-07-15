//
//  MeetingEndCompoments.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "MeetingEndCompoments.h"
#import "MeetingEndView.h"

@interface MeetingEndCompoments ()

@property (nonatomic, strong) MeetingEndView *endView;

@property (nonatomic, strong) NSButton *maskView;

@end

@implementation MeetingEndCompoments

- (instancetype)init {
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void)setIsWindow:(BOOL)isWindow {
    _isWindow = isWindow;
    
    self.maskView.hidden = isWindow ? YES : NO;
}

#pragma mark - Publish Action

- (void)showWithStatus:(MeetingEndStatus)status {
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    NSWindow *window = appDelegate.windowManager.currentWindowController.window;
    
    [self showWithStatus:status view:window.contentView];
}

- (void)showWithStatus:(MeetingEndStatus)status view:(NSView *)view {
    [view addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(view);
    }];
    
    [view addSubview:self.endView];
    [self.endView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(400);
        make.center.equalTo(view);
    }];
    
    self.endView.meetingEndStatus = status;
    __weak __typeof(self) wself = self;
    self.endView.clickButtonBlock = ^(MeetingButtonStatus status) {
        [wself dismissEndView];
        if (wself.clickButtonBlock) {
            wself.clickButtonBlock(status);
        }
    };
}

- (void)dismissEndView {
    [self.endView removeFromSuperview];
    self.endView = nil;
    [self.maskView removeFromSuperview];
    self.maskView = nil;
}

#pragma mark - getter

- (MeetingEndView *)endView {
    if (!_endView) {
        _endView = [[MeetingEndView alloc] init];
        [_endView setBackgroundColor:[NSColor whiteColor]];
    }
    return _endView;
}

- (NSButton *)maskView {
    if (!_maskView) {
        _maskView = [[NSButton alloc] init];
        [_maskView setBackgroundColorWithHexString:@"000000" andAlpha:0.5 * 255];
    }
    return _maskView;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}

@end
