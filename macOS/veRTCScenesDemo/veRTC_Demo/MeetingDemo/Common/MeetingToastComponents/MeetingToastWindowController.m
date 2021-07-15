//
//  MeetingToastWindowController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/29.
//

#import "MeetingToastWindowController.h"
#import "MeetingToastComponents.h"

@interface MeetingToastWindowController ()

@end

@implementation MeetingToastWindowController

- (void)windowDidLoad {
    [super windowDidLoad];

}

- (void)showWithMessage:(NSString *)message block:(void (^)(BOOL result))block {
    [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:message view:self.window.contentView block:block];
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}

@end
