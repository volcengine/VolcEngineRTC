//
//  WindowManager.m
//  SceneRTCDemo
//
//  Created by on 2021/3/2.
//

#import "WindowManager.h"
#import "MeetingWindowController.h"
#import "ScreenBottomWindowController.h"
#import "MeetingEndWindowController.h"
#import "MeetingToastWindowController.h"

@interface WindowManager () <NSWindowDelegate>

@property (nonatomic, strong) MeetingWindowController *meetingWindow;

@property (nonatomic, strong) MeetingEndWindowController *endWindowController;
@property (nonatomic, strong) MeetingToastWindowController *toastWindowController;
@property (nonatomic, assign) BOOL isSendScreen;

@end

@implementation WindowManager

- (instancetype)init {
    self = [super init];
    if (self) {
        _isSendScreen = NO;
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillClose:) name:NSWindowWillCloseNotification object:nil];
    }
    return self;
}

- (void)windowWillClose:(NSNotification *)notification {
    NSWindow *window = notification.object;
    if (window == self.meetingWindow.window && !_isSendScreen) {
        [NSApp terminate:self];
    }
}

#pragma mark - Publish Action

- (void)start {
    self.meetingWindow.window.delegate = self;
    [self.meetingWindow showWindow:nil];
    _currentWindowController = self.meetingWindow;
}

- (void)stop {
    
}

- (void)awake {
    [self.meetingWindow.window orderFront:nil];
}

- (void)showPreference {
    
}

#pragma mark - NSWindowDelegate

- (BOOL)windowShouldClose:(NSWindow *)sender {
    if (sender == self.meetingWindow.window) {
        if ([self.meetingWindow isNeedClose]) {
            return YES;
        } else {
            [self.meetingWindow showEndView];
            return NO;
        }
    } else {
        return YES;
    }
}

#pragma mark - Meeting

- (void)showMeetingWindowController {
    _isSendScreen = NO;
    [_currentWindowController close];
    [self.meetingWindow showWindow:nil];
    _currentWindowController = self.meetingWindow;
}

#pragma mark - toast

- (void)showToastWindowController:(NSString *)message {
    
    int displayID = 0;
    NSArray *screenArray = [NSScreen screens];
    for (int i = 0; i < screenArray.count; i++) {
        NSDictionary *screenDescription = [[screenArray objectAtIndex:i] deviceDescription];
        displayID = [[screenDescription objectForKey:@"NSScreenNumber"] intValue];
    }
    
    __weak __typeof(self) wself = self;
    [self.toastWindowController showWindow:@(displayID)];
    [self.toastWindowController showWithMessage:message block:^(BOOL result) {
        [wself.toastWindowController close];
        wself.toastWindowController = nil;
    }];
    self.toastWindowController.window.contentView.hidden = YES;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [[MeetingRTCManager shareMeetingRTCManager] updateScreenParameters];
    });
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        self.toastWindowController.window.contentView.hidden = NO;
    });
}

#pragma mark - Screen bottom

- (void)showScreenBottomWindowController:(LoginModel *)loginModel roomModel:(MeetingControlRoomModel *)roomModel {
    _isSendScreen = YES;
    [_currentWindowController close];
    ScreenBottomWindowController *screenBottomWindowController = [[ScreenBottomWindowController alloc] initWithWindowNibName:@"ScreenBottomWindowController"];
    screenBottomWindowController.loginModel = loginModel;
    screenBottomWindowController.roomModel = roomModel;
    [screenBottomWindowController.window setMovableByWindowBackground:YES];
    [screenBottomWindowController showWindow:nil];
    [screenBottomWindowController.window setBackgroundColor:[NSColor clearColor]];
    screenBottomWindowController.window.level = 21;
     
    _currentWindowController = screenBottomWindowController;
}

#pragma mark - End

- (void)showEndWindowController:(LoginModel *)loginModel roomModel:(MeetingControlRoomModel *)roomModel {
    self.endWindowController.loginModel = loginModel;
    self.endWindowController.roomModel = roomModel;
    [self.endWindowController showWindow:nil];
    [self.endWindowController show];
}

- (void)closeEndWindowController {
    [self.endWindowController close];
}

#pragma mark - getter

- (MeetingEndWindowController *)endWindowController {
    if (!_endWindowController) {
        _endWindowController = [[MeetingEndWindowController alloc] initWithWindowNibName:@"MeetingEndWindowController"];
       [_endWindowController.window setMovableByWindowBackground:YES];
       [_endWindowController.window setBackgroundColor:[NSColor clearColor]];
        _endWindowController.window.level = 20;
    }
    return _endWindowController;
}

- (MeetingToastWindowController *)toastWindowController {
    if (!_toastWindowController) {
        _toastWindowController = [[MeetingToastWindowController alloc] initWithWindowNibName:@"MeetingToastWindowController"];
       [_toastWindowController.window setMovableByWindowBackground:YES];
       [_toastWindowController.window setBackgroundColor:[NSColor clearColor]];
        _toastWindowController.window.level = 21;
    }
    return _toastWindowController;
}

- (MeetingWindowController *)meetingWindow {
    if (!_meetingWindow) {
        _meetingWindow = [[MeetingWindowController alloc] initWithWindowNibName:@"MeetingWindowController"];
        [_meetingWindow.window setMinSize:CGSizeMake(960, 700)];
    }
    return _meetingWindow;
}

@end
