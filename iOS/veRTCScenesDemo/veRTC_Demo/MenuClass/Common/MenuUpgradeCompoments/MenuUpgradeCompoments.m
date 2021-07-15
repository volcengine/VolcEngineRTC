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

#pragma mark - Publish Action

- (void)checkUpgrade {
    NSString *appVer = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    NSString *sdkVersion = [[MeetingRTCManager shareRtc] getSdkVersion];
    __weak __typeof(self) wself = self;
    [[VoiceSocketIOManager shareSocketManager] connectWithSdkVersion:sdkVersion block:^(BOOL relust) {
        if (relust && wself.isShow == NO) {
            [VoiceControlCompoments getAuditStateAppVersion:appVer
                                                      block:^(MenuUpgradeModel * _Nonnull upgradeModel,
                                                              VoiceControlAckModel * _Nonnull ackModel) {
                if (ackModel.result && upgradeModel.state == 1) {
                    [wself showAlert:upgradeModel];
                }
            }];
        }
    }];
}

- (void)stopUpgrade {
    [[VoiceSocketIOManager shareSocketManager] disConnect];
}

#pragma mark - Private Action

- (void)showAlert:(MenuUpgradeModel * _Nonnull)upgradeModel {
    AlertActionModel *alertModel = [[AlertActionModel alloc] init];
    alertModel.title = @"确定";
    AlertActionModel *cancelModel = [[AlertActionModel alloc] init];
    cancelModel.title = @"取消";
    [[AlertActionManager shareAlertActionManager] showWithMessage:@"应用有更新，\n立即去下载最新版本？"
                                                          actions:@[cancelModel, alertModel]];
    self.isShow = YES;
    alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
        if ([action.title isEqualToString:@"确定"]) {
            if (NOEmptyStr(upgradeModel.url)) {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:upgradeModel.url]
                                                   options:@{}
                                         completionHandler:^(BOOL success) {
                    
                }];
            }
        }
    };
}

@end
