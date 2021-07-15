//
//  UserNameViewController.m
//  veRTC_Demo
//
//  Created by  on 2021/5/18.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "UserViewController.h"
#import "UserCell.h"
#import "UserHeadView.h"
#import "UserNameViewController.h"

@interface UserViewController ()<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) UITableView *roomTableView;
@property (nonatomic, copy) NSArray *dataLists;
@property (nonatomic, strong) UserHeadView *headView;
@property (nonatomic, strong) BaseButton *logoutButton;

@end

@implementation UserViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
    
    [self.view addSubview:self.logoutButton];
    [self.logoutButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(44);
        make.bottom.equalTo(self.view).offset(-64 - [DeviceInforTool getVirtualHomeHeight] - 16);
        make.left.equalTo(self.view).offset(16);
        make.right.equalTo(self.view).offset(-16);
    }];
    
    [self.view addSubview:self.roomTableView];
    [self.roomTableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.view).offset([DeviceInforTool getStatusBarHight]);
        make.bottom.equalTo(self.logoutButton.mas_top).offset(-5);
        make.left.right.equalTo(self.view);
    }];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.headView.nameString = [LocalUserComponents userModel].name;
    [self.roomTableView reloadData];
}

#pragma mark - Publish Action

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UserCell *cell = [tableView dequeueReusableCellWithIdentifier:@"UserCellID" forIndexPath:indexPath];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.model = self.dataLists[indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    MenuCellModel *model = self.dataLists[indexPath.row];
    if (model.isMore) {
        if ([model.title isEqualToString:@"用户名"]) {
            UserNameViewController *next = [[UserNameViewController alloc] init];
            [self.navigationController pushViewController:next animated:YES];
        } else if ([model.title isEqualToString:@"隐私协议"]) {
            [self jumpToWeb:@"https://www.volcengine.com/docs/6348/68918"];
        } else if ([model.title isEqualToString:@"服务协议"]) {
            [self jumpToWeb:@"https://www.volcengine.com/docs/6348/68917"];
        } else if ([model.title isEqualToString:@"免责声明"]) {
            [self jumpToWeb:@"https://www.volcengine.com/docs/6348/68916"];
        } else {
            
        }
    }
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 60;
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataLists.count;
}

#pragma mark - Private Action

- (void)jumpToWeb:(NSString *)url {
    if (url && [url isKindOfClass:[NSString class]] && url.length > 0) {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]
                                           options:@{}
                                 completionHandler:^(BOOL success) {
            
        }];
    }
}

#pragma mark - Private Action

- (void)onClickLogoutRoom {
    [[NSNotificationCenter defaultCenter] postNotificationName:NotificationLoginExpired object:nil];
}

#pragma mark - getter

- (NSArray *)dataLists {
    if (!_dataLists) {
        NSMutableArray *lists = [[NSMutableArray alloc] init];
        
        MenuCellModel *model1 = [[MenuCellModel alloc] init];
        model1.title = @"用户名";
        model1.desTitle = @"";
        model1.isMore = YES;
        [lists addObject:model1];
        
        MenuCellModel *model2 = [[MenuCellModel alloc] init];
        model2.title = @"隐私协议";
        model2.isMore = YES;
        [lists addObject:model2];
        
        MenuCellModel *model3 = [[MenuCellModel alloc] init];
        model3.title = @"服务协议";
        model3.isMore = YES;
        [lists addObject:model3];
        
        MenuCellModel *model4 = [[MenuCellModel alloc] init];
        model4.title = @"免责声明";
        model4.isMore = YES;
        [lists addObject:model4];
        
        NSString *sdkVer = [[VoiceRTCManager shareRtc] getSdkVersion];
        NSString *appVer = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
        
        MenuCellModel *model5 = [[MenuCellModel alloc] init];
        model5.title = @"App版本";
        model5.desTitle = [NSString stringWithFormat:@"v%@", appVer];
        [lists addObject:model5];
        
        MenuCellModel *model6 = [[MenuCellModel alloc] init];
        model6.title = @"SDK版本";
        model6.desTitle = [NSString stringWithFormat:@"v%@", sdkVer];
        [lists addObject:model6];
        
        _dataLists = [lists copy];
    }
    return _dataLists;
}

- (UITableView *)roomTableView {
    if (!_roomTableView) {
        _roomTableView = [[UITableView alloc] init];
        _roomTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _roomTableView.delegate = self;
        _roomTableView.dataSource = self;
        [_roomTableView registerClass:UserCell.class forCellReuseIdentifier:@"UserCellID"];
        _roomTableView.backgroundColor = [UIColor clearColor];
        _roomTableView.rowHeight = UITableViewAutomaticDimension;
        _roomTableView.tableHeaderView = self.headView;
    }
    return _roomTableView;
}

- (BaseButton *)logoutButton {
    if (!_logoutButton) {
        _logoutButton = [[BaseButton alloc] init];
        _logoutButton.backgroundColor = [UIColor clearColor];
        _logoutButton.layer.masksToBounds = YES;
        _logoutButton.layer.cornerRadius = 44/2;
        _logoutButton.layer.borderWidth = XH_1PX_WIDTH;
        [_logoutButton setTitle:@"退出登录" forState:UIControlStateNormal];
        _logoutButton.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_logoutButton addTarget:self action:@selector(onClickLogoutRoom) forControlEvents:UIControlEventTouchUpInside];
        _logoutButton.layer.borderColor = [UIColor colorFromHexString:@"#86909C"].CGColor;
        [_logoutButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    }
    return _logoutButton;
}

- (UserHeadView *)headView {
    if (!_headView) {
        _headView = [[UserHeadView alloc] init];
        _headView.frame = CGRectMake(0, 0, SCREEN_WIDTH, 160);
    }
    return _headView;
}

@end
