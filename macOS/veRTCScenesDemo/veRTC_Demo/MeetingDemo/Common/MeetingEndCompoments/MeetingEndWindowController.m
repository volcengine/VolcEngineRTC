//
//  MeetingEndWindowController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/29.
//

#import "MeetingEndWindowController.h"
#import "MeetingEndCompoments.h"

@interface MeetingEndWindowController ()

@property (nonatomic, strong) MeetingEndCompoments *endCompoments;

@end

@implementation MeetingEndWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
}

- (void)show {
    BOOL host = [self.roomModel.host_id isEqualToString:[LocalUserCompoments userModel].uid];
    [self.endCompoments showWithStatus:host ? MeetingEndStatusHost : MeetingEndStatusNone view:self.window.contentView];
    __weak __typeof(self) wself = self;
    self.endCompoments.clickButtonBlock = ^(MeetingButtonStatus status) {
        NSString *key = @"";
        if (status == MeetingButtonStatusEnd) {
            key = @"end";
        } else if (status == MeetingButtonStatusLeave) {
            key = @"leave";
        } else if (status == MeetingButtonStatusCancel) {
            key = @"cancel";
        }
        [[NSNotificationCenter defaultCenter] postNotificationName:NotificationLoginExpired object:key];
        wself.endCompoments = nil;
    };
}

- (MeetingEndCompoments *)endCompoments {
    if (!_endCompoments) {
        _endCompoments = [[MeetingEndCompoments alloc] init];
        _endCompoments.isWindow = YES;
    }
    return _endCompoments;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}


@end
