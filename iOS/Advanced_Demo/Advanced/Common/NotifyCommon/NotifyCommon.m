//
//  NotifyCommon.m
//  Advanced
//
//

#import "NotifyCommon.h"
#import "SettingView.h"

@interface NotifyCommon ()

@property (nonatomic, strong) SettingView *settingView;
@property (nonatomic, strong) UIButton *backButton;
@property (nonatomic, weak) ByteRTCRoom *rtcRoom;

@end

@implementation NotifyCommon

#pragma mark - Publish Action

- (instancetype)initWithType:(NotifyStatus)notiftStatus
                   superView:(UIView *)superView
                     rtcRoom:(nonnull ByteRTCRoom *)rtcRoom {
    self = [super init];
    if (self) {
        _rtcRoom = rtcRoom;
        self.backgroundColor = [UIColor whiteColor];
        NSMutableArray *dataList = [[NSMutableArray alloc] init];

        [self addSubview:self.settingView];
        [self.settingView mas_makeConstraints:^(MASConstraintMaker *make) {
          make.top.mas_equalTo(30);
          make.left.right.equalTo(self);
          make.height.mas_equalTo(220);
        }];
        self.settingView.title = @"实时消息";
        SettingTextFieldModel *peerFieldModel = [[SettingTextFieldModel alloc] initWithTitle:@"点对点消息" defaultStr:@""];
        peerFieldModel.alertTitle = @"发送点对点消息";
        peerFieldModel.alertMessage = @"您可以使用点对点消息实现多种场景，如用户状态同步，文件播放进度同步等。";
        peerFieldModel.placeholders = @[ @"接收用户ID", @"消息" ];
        __weak __typeof(self) wself = self;
        peerFieldModel.inputBlock = ^(NSInteger index, NSString *_Nonnull valueStr) {
          if (index == 0) {
              [dataList removeAllObjects];
          }
          [dataList addObject:valueStr];
          if (index == 1) {
              [wself sendMessageType:notiftStatus
                          sendStatus:NotifySendStatusUser
                            dataList:[dataList copy]];
          }
        };

        SettingTextFieldModel *broadcastFieldModel = [[SettingTextFieldModel alloc] initWithTitle:@"广播消息" defaultStr:@""];
        broadcastFieldModel.alertTitle = @"发送广播消息";
        broadcastFieldModel.alertMessage = @"您可以使用广播消息实现多种场景，如赠送礼物，笔记同步等。";
        broadcastFieldModel.placeholders = @[ @"消息" ];
        broadcastFieldModel.inputBlock = ^(NSInteger index, NSString *_Nonnull valueStr) {
          if (index == 0) {
              [dataList removeAllObjects];
          }
          [dataList addObject:valueStr];
          [wself sendMessageType:notiftStatus
                      sendStatus:NotifySendStatusRoom
                        dataList:[dataList copy]];
        };

        self.settingView.dataArray =
            @[ peerFieldModel, broadcastFieldModel ];

        [self addSubview:self.backButton];
        [self.backButton mas_makeConstraints:^(MASConstraintMaker *make) {
          make.left.mas_equalTo(20);
          make.bottom.equalTo(self).offset(-30);
          make.right.mas_equalTo(-20);
          make.height.mas_equalTo(44);
        }];
    }
    return self;
}

- (void)sendMessageType:(NotifyStatus)notiftStatus
             sendStatus:(NotifySendStatus)sendStatus
               dataList:(NSArray *)dataList {
    if (notiftStatus == NotifyStatusText) {
        if (sendStatus == NotifySendStatusUser) {
            [self sendUserMessage:dataList[1] uid:dataList[0]];
        } else {
            [self sendRoomMessage:dataList[0]];
        }
    } else {
        if (sendStatus == NotifySendStatusUser) {
            [self sendUserBinaryMessage:dataList[1] uid:dataList[0]];
        } else {
            [self sendRoomBinaryMessage:dataList[0]];
        }
    }
}

- (void)sendUserMessage:(NSString *)message
                    uid:(NSString *)uid {
    [_rtcRoom sendUserMessage:uid message:message config:0];
}

- (void)sendUserBinaryMessage:(NSString *)message
                          uid:(NSString *)uid {
    NSData *data = [message dataUsingEncoding:NSUTF8StringEncoding];
    [_rtcRoom sendUserBinaryMessage:uid message:data config:0];
}

- (void)sendRoomMessage:(NSString *)message {
    [_rtcRoom sendRoomMessage:message];
}

- (void)sendRoomBinaryMessage:(NSString *)message {
    NSData *data = [message dataUsingEncoding:NSUTF8StringEncoding];
    [_rtcRoom sendRoomBinaryMessage:data];
}

- (void)backButtonAction {
    [self removeFromSuperview];
}

- (void)show {
}

#pragma mark - Getter

- (SettingView *)settingView {
    if (!_settingView) {
        _settingView = [[SettingView alloc] init];
    }
    return _settingView;
}

- (UIButton *)backButton {
    if (!_backButton) {
        _backButton = [[UIButton alloc] init];
        [_backButton setTitle:@"返回" forState:UIControlStateNormal];
        _backButton.backgroundColor = [UIColor systemBlueColor];
        [_backButton addTarget:self action:@selector(backButtonAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _backButton;
}

@end
