//
//  RoomBottomBarView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import "RoomBottomBarView.h"
#import "RoomBottomLeftBarView.h"

@interface RoomBottomBarView () <RoomBottomLeftBarViewDelegate>

@property (nonatomic, strong) RoomBottomLeftBarView *leftBarView;
@property (nonatomic, strong) NSView *lineView;
@property (nonatomic, strong) TrackButton *hangUpButton;

@property (nonatomic, assign) CGPoint touchPoint;
@property (nonatomic, assign) RoomBottomBarStatus currentRoomBottomBarStatus;
@end

@implementation RoomBottomBarView

- (instancetype)initWithStatus:(RoomBottomBarStatus)status {
    self = [super init];
    if (self) {
        _currentRoomBottomBarStatus = status;
        [self setBackgroundColorWithHexString:@"#1D2129"];
        self.wantsLayer = YES;
        self.layer.cornerRadius = 24;
        self.layer.masksToBounds = YES;
        
        [self addSubview:self.leftBarView];
        [self.leftBarView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.top.bottom.equalTo(self);
            make.right.equalTo(self).offset(-80);
        }];
        
        [self addSubview:self.lineView];
        [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(1, 24));
            make.left.equalTo(self.leftBarView.mas_right);
            make.centerY.equalTo(self);
        }];
        
        [self addSubview:self.hangUpButton];
        [self.hangUpButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(36, 36));
            make.centerY.equalTo(self);
            make.right.equalTo(self).offset(-20);
        }];
        
        
        AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
        NSView *windowView = appDelegate.windowManager.currentWindowController.window.contentView;
        NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:windowView.bounds
                                                                    options:(NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved |
                                                                             NSTrackingActiveInKeyWindow)
                                                                      owner:self
                                                                   userInfo:nil];

        [self addTrackingArea:trackingArea];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidResize:) name:NSWindowDidResizeNotification object:nil];
    }
    return self;
}

#pragma mark - Publish Action

- (void)updateButtonStatus:(BottomBarStatus)status close:(BOOL)isClose {
    [self.leftBarView updateButtonStatus:status close:isClose];
}

- (void)clickButtonStatus:(BottomBarStatus)status {
    [self.leftBarView clickButtonStatus:status];
}

- (void)setIsDragged:(BOOL)isDragged {
    _isDragged = isDragged;
    
    [self windowDidResize:nil];
}

#pragma mark - Click Action

- (void)hangUpButtonAction {
    RoomBottomBarModel *model = [[RoomBottomBarModel alloc] init];
    model.status = BottomBarStatusHangUp;
    if ([self.delegate respondsToSelector:@selector(roomBottomBarView:didSelectItemsAtButton:button:)]) {
        [self.delegate roomBottomBarView:self didSelectItemsAtButton:model button:nil];
    }
}

#pragma mark - RoomBottomLeftBarViewDelegate

- (void)roomBottomLeftBarView:(RoomBottomLeftBarView *)roomBottomBarView didSelectItemsAtButton:(RoomBottomBarModel *)roomBottomBarModel button:(nonnull TrackButton *)button {
    
    if ([self.delegate respondsToSelector:@selector(roomBottomBarView:didSelectItemsAtButton:button:)]) {
        [self.delegate roomBottomBarView:self didSelectItemsAtButton:roomBottomBarModel button:button];
    }
}

#pragma mark - Private Action

- (void)mouseDown:(NSEvent *)event {
    [super mouseDown:event];
    NSPoint touchPoint = [event locationInWindow];
    _touchPoint = [self convertPoint:touchPoint fromView:self.superview];
}

- (void)mouseDragged:(NSEvent *)event {
    [super mouseDragged:event];
    
    if (!self.isDragged) {
        return;
    }
    NSView *windowView = self.superview;
    NSPoint touchPoint = [event locationInWindow];
    
    CGFloat bottomValue = touchPoint.y - _touchPoint.y;
    CGFloat leftValue = touchPoint.x - _touchPoint.x;
    
    if (bottomValue <= 0) {
        bottomValue = 0;
    }
    if (bottomValue >= windowView.frame.size.height - self.frame.size.height - self.superview.frame.origin.y) {
        bottomValue = windowView.frame.size.height - self.frame.size.height - self.superview.frame.origin.y;
    }
    if (leftValue <= 0) {
        leftValue = 0;
    }
    if (leftValue >= windowView.frame.size.width - self.frame.size.width) {
        leftValue = windowView.frame.size.width - self.frame.size.width;
    }
    
    [self mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(400, 48));
        make.bottom.mas_equalTo(-(bottomValue));
        make.left.mas_equalTo(leftValue);
    }];
}

- (void)windowDidResize:(NSNotification *)aNotification {
    [self mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(400, 48));
        make.bottom.mas_equalTo(-8);
        make.centerX.equalTo(self.superview);
    }];
}

#pragma mark - getter

- (RoomBottomLeftBarView *)leftBarView {
    if (!_leftBarView) {
        _leftBarView = [[RoomBottomLeftBarView alloc] initWithStatus:_currentRoomBottomBarStatus];
        _leftBarView.wantsLayer = YES;
        _leftBarView.layer.backgroundColor = [NSColor clearColor].CGColor;
        _leftBarView.delegate = self;
    }
    return _leftBarView;
}

- (NSView *)lineView {
    if (!_lineView) {
        _lineView = [[NSView alloc] init];
        [_lineView setBackgroundColorWithHexString:@"#4E5969"];
    }
    return _lineView;
}

- (TrackButton *)hangUpButton {
    if (!_hangUpButton) {
        _hangUpButton = [[TrackButton alloc] init];
        _hangUpButton.wantsLayer = YES;
        [_hangUpButton setTarget:self];
        [_hangUpButton setAction:@selector(hangUpButtonAction)];
        
        [_hangUpButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor clearColor]];
        [_hangUpButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#272E3B"]];
        [_hangUpButton bingBackColorWithStatus:TrackButtonStatusActive color:[NSColor colorFromHexString:@"#101319"]];
        
        _hangUpButton.layer.masksToBounds = YES;
        _hangUpButton.layer.cornerRadius = 2;
        [_hangUpButton setImage:[NSImage imageNamed:@"meeting_bar_hangup"]];
        _hangUpButton.tipTitle = @"结束通话";
    }
    return _hangUpButton;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}

@end
