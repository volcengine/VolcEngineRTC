//
//  NavigationBarViewController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import "NavigationBarViewController.h"
#import "NavBarVersionView.h"
#import "NavBarRoomView.h"

@interface NavigationBarViewController ()

@property (nonatomic, strong) NavBarVersionView *versionView;
@property (nonatomic, strong) NavBarRoomView *roomView;
@property (nonatomic, strong) NSImageView *iconImageView;

@end

@implementation NavigationBarViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.view setBackgroundColorWithHexString:@"#1D2129"];
    [self addSubviewAndConstraints];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateRoomExpandList:) name:NoticeUpdateRoomExpandListName object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateRoomRecord:) name:NoticeUpdateRoomRecordName object:nil];
    
    [self updateUIWithStatus:NavigationBarStatusLogin];
    
}
#pragma mark - NSNotification Method

- (void)updateRoomExpandList:(NSNotification *)notification {
    NSNumber *isExpand = (NSNumber *)notification.object;
    self.roomView.isExpandList = [isExpand boolValue];
}

- (void)updateRoomRecord:(NSNotification *)notification {
    NSNumber *isRecord = (NSNumber *)notification.object;
    self.roomView.isRecord = [isRecord boolValue];
}

#pragma mark - Publish Action

- (void)updateUIWithStatus:(NavigationBarStatus)status {
    if (status == NavigationBarStatusRoom) {
        [self.view addSubview:self.roomView];
        [self.roomView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.top.bottom.equalTo(self.view);
            make.right.equalTo(self.view).offset(0);
        }];
        
        [self.versionView removeAllAutoLayout];
        [self.versionView removeAllSubView];
        [self.versionView removeFromSuperview];
        self.versionView = nil;        
    } else {
        [self.view addSubview:self.versionView];
        [self.versionView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self.view);
        }];
        
        [self.roomView removeAllAutoLayout];
        [self.roomView removeAllSubView];
        [self.roomView removeFromSuperview];
        self.roomView = nil;
    }
}

- (void)setLoginModel:(LoginModel *)loginModel {
    _loginModel = loginModel;
    
    self.roomView.loginModel = loginModel;
}

- (void)setMeetingTime:(NSInteger)meetingTime {
    _meetingTime = meetingTime;
    
    self.roomView.meetingTime = meetingTime;
}

#pragma mark - Private Action

- (void)addSubviewAndConstraints {
    [self.view addSubview:self.iconImageView];
    [self.iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(156, 20));
        make.left.mas_equalTo(24);
        make.centerY.equalTo(self.view);
    }];
}

#pragma mark - getter

- (NavBarVersionView *)versionView {
    if (!_versionView) {
        _versionView = [[NavBarVersionView alloc] init];
        [_versionView setBackgroundColor:[NSColor clearColor]];
    }
    return _versionView;
}

- (NavBarRoomView *)roomView {
    if (!_roomView) {
        _roomView = [[NavBarRoomView alloc] init];
        [_roomView setBackgroundColor:[NSColor clearColor]];
    }
    return _roomView;
}

- (NSImageView *)iconImageView {
    if (!_iconImageView) {
        _iconImageView = [[NSImageView alloc] init];
        [_iconImageView setBackgroundColor:[NSColor clearColor]];
        _iconImageView.image = [NSImage imageNamed:@"meeting_icon"];
    }
    return _iconImageView;
}

@end
