//
//  ParticipantViewController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
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
    }
    return self;
}

#pragma mark - Publish Action

- (void)setVideoSessions:(NSArray<RoomUserModel *> *)videoSessions {
    _videoSessions = videoSessions;
    
    self.listView.dataLists = videoSessions;
    self.titleLabel.text = [NSString stringWithFormat:@"参会人（%lu）", (unsigned long)self.listView.dataLists.count];
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
