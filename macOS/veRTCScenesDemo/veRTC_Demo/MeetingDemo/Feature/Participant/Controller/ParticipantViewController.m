//
//  ParticipantViewController.m
//  SceneRTCDemo
//
//  Created by on 2021/3/9.
//

#import "ParticipantViewController.h"
#import "ParticipantListsView.h"

@interface ParticipantViewController ()

@property (nonatomic, strong) NSLabel *titleLabel;
@property (nonatomic, strong) NSButton *cancelButton;
@property (nonatomic, strong) ParticipantListsView *listView;
@property (nonatomic, strong) NSButton *muteAllButton;

@end

@implementation ParticipantViewController

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColorWithHexString:@"#101319"];
        
        [self addSubviewAndConstraints];
        
        [self loadDataWithGetMeetingUserInfo];
    }
    return self;
}

#pragma mark - Publish Action

- (void)loadDataWithGetMeetingUserInfo {
    [MeetingControlCompoments getMeetingUserInfo:@"" block:^(NSArray<MeetingControlUserModel *> * _Nonnull userLists, MeetingControlAckModel * _Nonnull model) {
        NSMutableArray *dataLists = [[NSMutableArray alloc] init];
        for (int i = 0; i < userLists.count; i++) {
            ParticipantModel *participantModel = [ParticipantModel participantModelToMeetingControlUserModel:userLists[i]];
            //is oneself
            if ([participantModel.roomUserModel.name isEqualToString:self.loginModel.uid]) {
                participantModel.roomUserModel.isOneself = YES;
            }
            [dataLists addObject:participantModel];
        }
        self.listView.dataLists = [dataLists copy];
        self.titleLabel.text = [NSString stringWithFormat:@"参会人（%lu）", (unsigned long)self.listView.dataLists.count];
    }];
}

- (void)updateUserMicStatus:(BOOL)isOpen uid:(NSString *)uid {
    BOOL isRefresh = NO;
    NSArray *lists = self.listView.dataLists;
    for (ParticipantModel *model in lists) {
        if (uid && [uid isKindOfClass:[NSString class]] &&uid.length > 0) {
            //Update a person's microphone
            if ([model.roomUserModel.name isEqualToString:uid]) {
                model.roomUserModel.audioType = isOpen ? 1 : 2;
                isRefresh = YES;
                break;
            }
        } else {
            //Update everyone microphone
            if (!model.roomUserModel.isHost) {
                model.roomUserModel.audioType = isOpen ? 1 : 2;
            }
            isRefresh = YES;
        }
    }
    if (isRefresh) {
        self.listView.dataLists = lists;
    }
}

- (void)updateUserCameraStatus:(BOOL)isOpen uid:(NSString *)uid {
    BOOL isRefresh = NO;
    NSArray *lists = self.listView.dataLists;
    for (ParticipantModel *model in lists) {
        if ([model.roomUserModel.name isEqualToString:uid]) {
            model.roomUserModel.isOpenVideo = isOpen;
            isRefresh = YES;
            break;
        }
    }
    if (isRefresh) {
        self.listView.dataLists = lists;
    }
}

- (void)updateUserScreenStatus:(BOOL)isOpen uid:(NSString *)uid {
    for (ParticipantModel *model in self.listView.dataLists) {
        if ([model.roomUserModel.name isEqualToString:uid]) {
            model.roomUserModel.isOpenScreen = isOpen;
        } else {
            model.roomUserModel.isOpenScreen = NO;
        }
    }
}

- (void)updateUserHostStatusWithUid:(NSString *)uid {
    ParticipantModel *hostModel = nil;
    for (ParticipantModel *model in self.listView.dataLists) {
        if ([model.roomUserModel.name isEqualToString:uid]) {
            model.roomUserModel.isHost = YES;
            hostModel = model;
        } else {
            model.roomUserModel.isHost = NO;
        }
    }
    if (hostModel) {
        NSMutableArray *lists = [self.listView.dataLists mutableCopy];
        [lists removeObject:hostModel];
        [lists insertObject:hostModel atIndex:0];
        self.listView.dataLists = [lists copy];
    }
}

- (void)setIsLoginHost:(BOOL)isLoginHost {
    _isLoginHost = isLoginHost;
    self.listView.isLoginHost = isLoginHost;
    
    if (isLoginHost) {
        [self.muteAllButton mas_updateConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(32);
        }];
    } else {
        [self.muteAllButton mas_updateConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(0);
        }];
    }
}

- (void)updateUserMicStatus:(NSDictionary<NSString *,NSNumber *> *)speakUid {
    for (ParticipantModel *model in self.listView.dataLists) {
        NSNumber *number = speakUid[model.roomUserModel.name];
        if (model.roomUserModel.audioType == 1 || model.roomUserModel.audioType == 3) {
            if (number && number.integerValue > 0) {
                model.roomUserModel.audioType = 3;
            } else {
                if (model.roomUserModel.audioType == 3) {
                    model.roomUserModel.audioType = 1;
                } else {

                }
            }
        } else {
            
        }
    }
    self.listView.dataLists = self.listView.dataLists;
}

#pragma mark - Action Method

- (void)cancelButtonAction {
    if (self.clickCancelBlock) {
        self.clickCancelBlock(YES);
    }
}

- (void)muteAllButtonAction {
    //Mute all user
    [MeetingControlCompoments muteUser:@"" block:^(BOOL result, MeetingControlAckModel * _Nonnull model) {
        if (!model.result) {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:model.message];
        }
    }];
}

#pragma mark - Private Action

- (void)addSubviewAndConstraints {
    [self addSubview:self.titleLabel];
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.mas_equalTo(16);
    }];
    
    [self addSubview:self.cancelButton];
    [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(20, 20));
        make.top.mas_equalTo(16);
        make.right.mas_equalTo(-16);
    }];
    
    [self addSubview:self.muteAllButton];
    [self.muteAllButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(16);
        make.bottom.right.mas_equalTo(-16);
        make.height.mas_equalTo(32);
    }];

    [self addSubview:self.listView];
    [self.listView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self);
        make.top.mas_equalTo(56);
        make.bottom.equalTo(self.muteAllButton.mas_top).offset(-16);
    }];
}

#pragma mark - getter

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _titleLabel.font = [NSFont systemFontOfSize:16 weight:NSFontWeightMedium];
        _titleLabel.text = @"参会人（0）";
    }
    return _titleLabel;
}

- (NSButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[NSButton alloc] init];
        [_cancelButton setImage:[NSImage imageNamed:@"meeting_partner_cancel"]];
        [_cancelButton setBackgroundColor:[NSColor clearColor]];
        [_cancelButton setTarget:self];
        [_cancelButton setAction:@selector(cancelButtonAction)];
    }
    return _cancelButton;
}

- (ParticipantListsView *)listView {
    if (!_listView) {
        _listView = [[ParticipantListsView alloc] init];
    }
    return _listView;
}

- (NSButton *)muteAllButton {
    if (!_muteAllButton) {
        _muteAllButton = [[NSButton alloc] init];
        [_muteAllButton setBackgroundColorWithHexString:@"#272E3B"];
        [_muteAllButton setImage:[NSImage imageNamed:@"meeting_partner_allmute"]];
        [_muteAllButton setTarget:self];
        [_muteAllButton setAction:@selector(muteAllButtonAction)];
    }
    return _muteAllButton;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}

@end
