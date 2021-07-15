//
//  UserNameViewController.m
//  veRTC_Demo
//
//  Created by  on 2021/5/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "UserNameViewController.h"
#import "VocieCreateTextFieldView.h"

@interface UserNameViewController ()

@property (nonatomic, strong) VocieCreateTextFieldView *userNameTextFieldView;

@end

@implementation UserNameViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
    
    [self.view addSubview:self.userNameTextFieldView];
    [self.userNameTextFieldView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(16);
        make.right.mas_equalTo(-16);
        make.height.mas_equalTo(32);
        make.top.equalTo(self.navView.mas_bottom).offset(30);
    }];
    
    [self.userNameTextFieldView becomeFirstResponder];
    
    self.userNameTextFieldView.text = [LocalUserComponents userModel].name;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navTitle = @"设置名称";
    self.rightTitle = @"确定";
}

- (void)rightButtonAction:(BaseButton *)sender {
    if (![LocalUserComponents isMatchUserName:self.userNameTextFieldView.text] ||
        self.userNameTextFieldView.text.length <= 0) {
        return;
    }
    __weak __typeof(self) wself = self;
    BaseUserModel *userModel = [LocalUserComponents userModel];
    userModel.name = self.userNameTextFieldView.text;
    [VoiceControlCompoments changeUserName:userModel
                                     block:^(VoiceControlAckModel * _Nonnull ackModel) {
        if (ackModel.result) {
            [LocalUserComponents updateLocalUserModel:userModel];
            [wself.navigationController popViewControllerAnimated:YES];
        } else {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:ackModel.message];
        }
    }];
}

#pragma mark - getter

- (VocieCreateTextFieldView *)userNameTextFieldView {
    if (!_userNameTextFieldView) {
        _userNameTextFieldView = [[VocieCreateTextFieldView alloc] initWithModify:YES];
        _userNameTextFieldView.placeholderStr = @"请输入用户昵称";
        _userNameTextFieldView.maxLimit = 18;
    }
    return _userNameTextFieldView;
}

@end
