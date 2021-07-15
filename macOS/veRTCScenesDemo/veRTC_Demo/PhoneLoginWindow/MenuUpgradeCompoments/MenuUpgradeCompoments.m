//
//  MenuUpgradeCompoments.m
//  veRTC_Demo
//
//  Created by  on 2021/6/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "MenuUpgradeCompoments.h"

@interface MenuUpgradeCompoments ()

@property (nonatomic, assign) BOOL isShow;

@end

@implementation MenuUpgradeCompoments

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.isShow = NO;
    }
    return self;
}

- (void)checkUpgrade {
    NSString *sdkVersion = [[MeetingRTCManager shareMeetingRTCManager] getSdkVersion];
    __weak __typeof(self) wself = self;
    [[MeetingSocketIOManager shareSocketManager] connectWithSdkVersion:sdkVersion block:^(BOOL relust) {
        if (relust && self.isShow == NO) {
            wself.isShow = YES;
            [MeetingControlCompoments getAuditState:^(MenuUpgradeModel * _Nonnull upgradeModel, MeetingControlAckModel * _Nonnull ackModel) {
                if (ackModel.result && upgradeModel.state == 1) {
                    [wself showAlert:upgradeModel];
                }
            }];
            
            [MeetingControlCompoments verifyLoginToken];
        }
    }];
}

- (void)stopUpgrade {
    [[MeetingSocketIOManager shareSocketManager] disConnect];
}

#pragma mark - Private Action

- (void)showAlert:(MenuUpgradeModel * _Nonnull)upgradeModel {
    [[MeetingAlertCompoments share] showWithTitle:@"应用有更新，\n立即去下载最新版本？"
                                       clickBlock:^(BOOL result) {
        if (result) {
            if (NOEmptyStr(upgradeModel.url)) {
                [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:upgradeModel.url]];
            }
        }
    }];
}

@end
