//
//  VoiceRoomViewController.m
//  veRTC_Demo
//
//  Created by  on 2021/5/18.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomListsViewController.h"
#import "VoiceCreateRoomViewController.h"
#import "VoiceRoomViewController.h"
#import "VoiceRoomTableView.h"

@interface VoiceRoomListsViewController () <VoiceRoomTableViewDelegate>

@property (nonatomic, strong) UIButton *createButton;
@property (nonatomic, strong) VoiceRoomTableView *roomTableView;
@property (nonatomic, copy) NSString *currentAppid;

@end

@implementation VoiceRoomListsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.bgView.hidden = NO;
    self.navView.backgroundColor = [UIColor clearColor];
    
    NSString *sdkVersion = [[MeetingRTCManager shareRtc] getSdkVersion];
    [[VoiceSocketIOManager shareSocketManager] connectWithSdkVersion:sdkVersion block:^(BOOL relust) {
        if (relust) {
            [self loadDataWithGetLists];
        }
    }];
    
    [self.view addSubview:self.roomTableView];
    [self.roomTableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.left.right.equalTo(self.view);
        make.top.equalTo(self.navView.mas_bottom);
    }];
    
    [self.view addSubview:self.createButton];
    [self.createButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(132, 44));
        make.right.equalTo(self.view).offset(-20);
        make.bottom.equalTo(self.view).offset(- 20 - [DeviceInforTool getVirtualHomeHeight]);
    }];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navTitle = @"语音沙龙";
    self.rightTitle = @"刷新";
    
    if ([VoiceSocketIOManager shareSocketManager].connectStatus == VoiceConnectStatusSuccess) {
        [self loadDataWithGetLists];
    }
}

- (void)rightButtonAction:(BaseButton *)sender {
    [super rightButtonAction:sender];
    
    [self loadDataWithGetLists];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
}

#pragma mark - load data

- (void)loadDataWithGetLists {
    [VoiceControlCompoments getMeetingsWithBlock:^(NSArray * _Nonnull lists, VoiceControlAckModel * _Nonnull model) {
        self.roomTableView.dataLists = lists;
    }];
}

#pragma mark - VoiceRoomTableViewDelegate

- (void)voiceRoomTableView:(VoiceRoomTableView *)voiceRoomTableView didSelectRowAtIndexPath:(VoiceControlRoomModel *)model {
    VoiceRoomViewController *next = [[VoiceRoomViewController alloc] init];
    next.roomID = model.room_id;
    next.userName = [LocalUserComponents userModel].name;
    [self.navigationController pushViewController:next animated:YES];
}

#pragma mark - Touch Action

- (void)createButtonAction {
    VoiceCreateRoomViewController *next = [[VoiceCreateRoomViewController alloc] init];
    [self.navigationController pushViewController:next animated:YES];
}

#pragma mark - getter

- (UIButton *)createButton {
    if (!_createButton) {
        _createButton = [[UIButton alloc] init];
        _createButton.backgroundColor = [UIColor colorFromHexString:@"#4080FF"];
        [_createButton addTarget:self action:@selector(createButtonAction) forControlEvents:UIControlEventTouchUpInside];
        _createButton.layer.cornerRadius = 22;
        _createButton.layer.masksToBounds = YES;
        
        UIImageView *iconImageView = [[UIImageView alloc] init];
        iconImageView.image = [UIImage imageNamed:@"voice_add"];
        [_createButton addSubview:iconImageView];
        [iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(20, 20));
            make.centerY.equalTo(_createButton);
            make.left.mas_equalTo(20);
        }];
        
        UILabel *titleLabel = [[UILabel alloc] init];
        titleLabel.text = @"创建房间";
        titleLabel.textColor = [UIColor whiteColor];
        titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_createButton addSubview:titleLabel];
        [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(_createButton);
            make.left.equalTo(iconImageView.mas_right).offset(8);
        }];
    }
    return _createButton;
}

- (VoiceRoomTableView *)roomTableView {
    if (!_roomTableView) {
        _roomTableView = [[VoiceRoomTableView alloc] init];
        _roomTableView.delegate = self;
    }
    return _roomTableView;
}

- (void)dealloc {
    [[VoiceSocketIOManager shareSocketManager] disConnect];
    [[VoiceRTCManager shareRtc] destroy];
}


@end
