#import "SettingsService.h"
#import "UserListViewController.h"
#import "MeetingSocketIOManager.h"

@interface UserListViewController () <UITableViewDelegate, UITableViewDataSource, UIScrollViewDelegate>

@property (nonatomic, strong) UITableView *settingsTableView;
@property (nonatomic, strong) BaseButton *muteAllButton;
@property (nonatomic, assign) BOOL isEdit;

@end

@implementation UserListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
    self.isEdit = NO;
    
    [self.view addSubview:self.muteAllButton];
    [self.muteAllButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(343);
        make.height.mas_equalTo(44);
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(-[DeviceInforTool getVirtualHomeHeight] - 32/2);
    }];
    
    [self.view addSubview:self.settingsTableView];
    [self.settingsTableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.top.equalTo(self.navView.mas_bottom);
        if (self.isLoginHost) {
            make.bottom.equalTo(self.muteAllButton.mas_top).offset(-32/2);
        } else {
            make.bottom.equalTo(self.view);
        }
    }];
    
    self.muteAllButton.hidden = !self.isLoginHost;
}

#pragma mark - Action Method

- (void)muteAllButtonAction {
    [MeetingControlCompoments muteUser:@"" block:^(BOOL result, MeetingControlAckModel * _Nonnull model) {
        if (!model.result) {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:model.message];
        }
    }];
}

#pragma mark - Publish Action

- (void)setIsLoginHost:(BOOL)isLoginHost {
    _isLoginHost = isLoginHost;
    
    if (self.settingsTableView.superview) {
        [self.settingsTableView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(self.view);
            make.top.equalTo(self.navView.mas_bottom);
            if (isLoginHost) {
                make.bottom.equalTo(self.muteAllButton.mas_top).offset(-32/2);
            } else {
                make.bottom.equalTo(self.view);
            }
        }];
    }
    self.muteAllButton.hidden = !isLoginHost;
}

- (void)setVideoSessions:(NSMutableArray<RoomVideoSession *> *)videoSessions {
    _videoSessions = videoSessions;
    
    [self settingsTableViewReloadData];
    self.navTitle = [NSString stringWithFormat:@"参会人(%lu)", (unsigned long)[videoSessions count]];
}

#pragma mark - UIScrollViewDelegate

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    self.isEdit = YES;
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    self.isEdit = NO;
}


#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView willBeginEditingRowAtIndexPath:(NSIndexPath *)indexPath {
    self.isEdit = YES;
}

- (void)tableView:(UITableView *)tableView didEndEditingRowAtIndexPath:(nullable NSIndexPath *)indexPath {
    self.isEdit = NO;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UserListCell *cell = [tableView dequeueReusableCellWithIdentifier:@"UserListCellID" forIndexPath:indexPath];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.videoSession = [self.videoSessions objectAtIndex:indexPath.row];
    return cell;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    BOOL isCanEdit = NO;
    if (self.isLoginHost) {
        if (indexPath.row < self.videoSessions.count) {
            RoomVideoSession *model = self.videoSessions[indexPath.row];
            if ([model.uid isEqualToString:self.localVideoSession.uid]) {
                isCanEdit = NO;
            } else {
                isCanEdit = YES;
            }
        }
    }
    return isCanEdit;
}

- (NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath {
    __weak __typeof(self) wself = self;
    RoomVideoSession *model = self.videoSessions[indexPath.row];
    UITableViewRowAction *hostAction = [UITableViewRowAction rowActionWithStyle:UITableViewRowActionStyleDestructive title:@"移交主持人" handler:^(UITableViewRowAction * _Nonnull action, NSIndexPath * _Nonnull indexPath) {
        NSLog(@"点击了移交主持人");
        AlertActionModel *model1 = [[AlertActionModel alloc] init];
        model1.title = @"确定";
        AlertActionModel *model2 = [[AlertActionModel alloc] init];
        model2.title = @"取消";
        NSString *message = [NSString stringWithFormat:@"是否将主持人移交给：%@", model.name];
        [[AlertActionManager shareAlertActionManager] showWithMessage:message actions:@[model2, model1]];
        model1.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
            [wself changeHost:model.uid];
        };
    }];
    hostAction.backgroundColor = [UIColor colorFromHexString:@"#4080FF"];
    NSString *message = !model.isEnableAudio ? @"请求开麦" : @"静音";
    UITableViewRowAction *muteAction = [UITableViewRowAction
                                        rowActionWithStyle:UITableViewRowActionStyleNormal
                                        title:message
                                        handler:^(UITableViewRowAction * _Nonnull action,
                                                  NSIndexPath * _Nonnull indexPath) {
        //mute
        [wself muteUserOrAskMic:model];
    }];
    muteAction.backgroundColor = [UIColor colorFromHexString:@"#FF7D00"];
    return @[hostAction, muteAction];
}
 
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath{
    editingStyle = UITableViewCellEditingStyleDelete;
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.videoSessions.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 127/2;
}

#pragma mark - Private Action

- (void)settingsTableViewReloadData {
    if (!self.isEdit) {
        [self.settingsTableView reloadData];
    }
}

- (void)muteUserOrAskMic:(RoomVideoSession *)videoSession {
    BOOL isOpenAudio = videoSession.isEnableAudio;
    if (isOpenAudio) {
        //mute microphone
        [MeetingControlCompoments muteUser:videoSession.uid block:^(BOOL result, MeetingControlAckModel * _Nonnull model) {
                    
        }];
    } else {
        //Ask microphone On
        [MeetingControlCompoments askMicOn:videoSession.uid block:^(BOOL result) {
                    
        }];
    }
}

- (void)changeHost:(NSString *)uid {
    [MeetingControlCompoments changeHost:uid block:^(BOOL result, MeetingControlAckModel * _Nonnull model) {
        if (!model.result) {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:model.message];
        }
    }];
}

#pragma mark - getter

- (UITableView *)settingsTableView {
    if (!_settingsTableView) {
        _settingsTableView = [[UITableView alloc] init];
        _settingsTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _settingsTableView.delegate = self;
        _settingsTableView.dataSource = self;
        [_settingsTableView registerClass:[UserListCell class] forCellReuseIdentifier:@"UserListCellID"];
        _settingsTableView.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
    }
    return _settingsTableView;
}

- (BaseButton *)muteAllButton {
    if (!_muteAllButton) {
        _muteAllButton = [[BaseButton alloc] init];
        [_muteAllButton addTarget:self action:@selector(muteAllButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_muteAllButton bingImage:[UIImage imageNamed:@"meeting_par_muteall"] status:ButtonStatusNone];
        _muteAllButton.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
        _muteAllButton.layer.masksToBounds = YES;
        _muteAllButton.layer.cornerRadius = 22;
        _muteAllButton.imageEdgeInsets = UIEdgeInsetsMake(10, 0, 10, 0);
        _muteAllButton.imageView.contentMode = UIViewContentModeScaleAspectFit;
        _muteAllButton.hidden = YES;
    }
    return _muteAllButton;
}

@end
