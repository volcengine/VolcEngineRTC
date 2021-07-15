//
//  RoomBottomLeftBarView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import "RoomBottomLeftBarView.h"
#import "SystemAuthority.h"

@interface RoomBottomLeftBarView ()

@property (nonatomic, strong) NSMutableArray *dataLists;

@property (nonatomic, strong) NSMutableArray *buttonLists;

@end

@implementation RoomBottomLeftBarView

- (void)loadData:(RoomBottomBarStatus)status {
    RoomBottomBarModel *model1 = [[RoomBottomBarModel alloc] init];
    model1.status = BottomBarStatusMic;
    [self.dataLists addObject:model1];
    
    RoomBottomBarModel *model2 = [[RoomBottomBarModel alloc] init];
    model2.status = BottomBarStatusVideo;
    [self.dataLists addObject:model2];
    
    RoomBottomBarModel *model3 = [[RoomBottomBarModel alloc] init];
    model3.status = BottomBarStatusScreenShare;
    [self.dataLists addObject:model3];
    
    RoomBottomBarModel *model4 = [[RoomBottomBarModel alloc] init];
    model4.status = BottomBarStatusRecord;
    [self.dataLists addObject:model4];
    
    RoomBottomBarModel *model5 = [[RoomBottomBarModel alloc] init];
    model5.status = BottomBarStatusPeople;
    [self.dataLists addObject:model5];
    
    RoomBottomBarModel *model6 = [[RoomBottomBarModel alloc] init];
    model6.status = BottomBarStatusSeting;
    [self.dataLists addObject:model6];
}

- (instancetype)initWithStatus:(RoomBottomBarStatus)status {
    self = [super init];
    if (self) {
        [self loadData:status];
        for (int i = 0; i < self.dataLists.count; i++) {
            RoomBottomBarModel *model = self.dataLists[i];
            TrackButton *button = [[TrackButton alloc] init];
            button.tag = 3000 + i;
            button.wantsLayer = YES;
            [button setTarget:self];
            [button setAction:@selector(buttonAction:)];
            button.layer.masksToBounds = YES;
            button.layer.cornerRadius = 2;
            
            [button bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor clearColor]];
            [button bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#272E3B"]];
            [button bingBackColorWithStatus:TrackButtonStatusActive color:[NSColor colorFromHexString:@"#101319"]];
            
            [self updateButtonImageWithStatus:model.status button:button];
            [self addSubview:button];
            [self.buttonLists addObject:button];
        }
        [self.buttonLists mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedItemLength:36 leadSpacing:20 tailSpacing:12];
        [self.buttonLists mas_makeConstraints:^(MASConstraintMaker *make) {
            make.height.mas_equalTo(36);
            make.centerY.equalTo(self);
        }];
        
        [self updateSystemAuthority];
    }
    return self;
}

#pragma mark - Publish Action

- (void)updateButtonStatus:(BottomBarStatus)status close:(BOOL)isClose {
    if (status == BottomBarStatusMic) {
        TrackButton *button = self.buttonLists.firstObject;
        button.isClose = isClose;
    } else if (status == BottomBarStatusVideo) {
        if (self.buttonLists.count >= 2) {
            TrackButton *button = self.buttonLists[1];
            button.isClose = isClose;
        }
    }
    else if (status == BottomBarStatusRecord) {
        if (self.buttonLists.count >= 4) {
            TrackButton *button = self.buttonLists[3];
            button.isClose = isClose;
        }
    }
    else if (status == BottomBarStatusScreenShare) {
        if (self.buttonLists.count >= 3) {
            TrackButton *button = self.buttonLists[2];
            button.isClose = isClose;
        }
    } else if (status == BottomBarStatusPeople) {
        if (self.buttonLists.count >= 4) {
            TrackButton *button = self.buttonLists[4];
            button.isClose = isClose;
        }
    } else {
        
    }
}

- (void)clickButtonStatus:(BottomBarStatus)status {
    TrackButton *button = nil;
    if (status == BottomBarStatusMic) {
        button = self.buttonLists.firstObject;
    } else if (status == BottomBarStatusVideo) {
        button = self.buttonLists[1];
    }
    if (button) {
        button.simulation = YES;
        [self buttonAction:button];
    }
}

- (void)updateButtonImageWithStatus:(BottomBarStatus)status button:(TrackButton *)button {
    if (status == BottomBarStatusMic) {
        [button bingImageWithType:NO image:[NSImage imageNamed:@"meeting_bar_mic"]];
        [button bingImageWithType:YES image:[NSImage imageNamed:@"meeting_bar_mic_close"]];
        button.tipTitle = @"麦克风";
    } else if (status == BottomBarStatusVideo) {
        [button bingImageWithType:NO image:[NSImage imageNamed:@"meeting_bar_video"]];
        [button bingImageWithType:YES image:[NSImage imageNamed:@"meeting_bar_video_close"]];
        button.tipTitle = @"摄像头";
    } else if (status == BottomBarStatusScreenShare) {
        [button bingImageWithType:NO image:[NSImage imageNamed:@"meeting_bar_screen"]];
        [button bingImageWithType:YES image:[NSImage imageNamed:@"meeting_bar_screen_close"]];
        button.tipTitle = @"屏幕共享";
    } else if (status == BottomBarStatusRecord) {
        [button bingImageWithType:NO image:[NSImage imageNamed:@"meeting_bar_record"]];
        [button bingImageWithType:YES image:[NSImage imageNamed:@"meeting_bar_record_close"]];
        button.tipTitle = @"开启录制";
    } else if (status == BottomBarStatusPeople) {
        [button bingImageWithType:NO image:[NSImage imageNamed:@"meeting_bar_people"]];
        [button bingImageWithType:YES image:[NSImage imageNamed:@"meeting_bar_people_s"]];
        button.tipTitle = @"参会人列表";
    } else if (status == BottomBarStatusSeting) {
        [button setImage:[NSImage imageNamed:@"meeting_bar_set"]];
        button.tipTitle = @"设置";
    }
}

- (void)buttonAction:(TrackButton *)sender {
    NSInteger index = sender.tag - 3000;
    RoomBottomBarModel *model = self.dataLists[index];
    if (model.status == BottomBarStatusMic) {
        [SystemAuthority authorMicphone:^(BOOL granted) {
            if (granted) {
                if ([self.delegate respondsToSelector:@selector(roomBottomLeftBarView:didSelectItemsAtButton:button:)]) {
                    [self.delegate roomBottomLeftBarView:self didSelectItemsAtButton:model button:sender];
                }
            } else {
                if (!sender.simulation) {
                    [[MeetingAlertCompoments share] showWithTitle:@"麦克风权限已关闭，请至设备设置页开启。" clickBlock:^(BOOL result) {
                        if (result) {
                            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"x-apple.systempreferences:com.apple.preference.security?Privacy"]];
                        }
                    }];
                } else {
                    sender.simulation = NO;
                }
            }
        }];
    } else if (model.status == BottomBarStatusVideo) {
        [SystemAuthority authorCamera:^(BOOL granted) {
            if (granted) {
                if ([self.delegate respondsToSelector:@selector(roomBottomLeftBarView:didSelectItemsAtButton:button:)]) {
                    [self.delegate roomBottomLeftBarView:self didSelectItemsAtButton:model button:sender];
                }
            } else {
                if (!sender.simulation) {
                    [[MeetingAlertCompoments share] showWithTitle:@"摄像头权限已关闭，请至设备设置页开启。" clickBlock:^(BOOL result) {
                        if (result) {
                            [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"x-apple.systempreferences:com.apple.preference.security?Privacy"]];
                        }
                    }];
                } else {
                    sender.simulation = NO;
                }
            }
        }];
    } else {
        if ([self.delegate respondsToSelector:@selector(roomBottomLeftBarView:didSelectItemsAtButton:button:)]) {
            [self.delegate roomBottomLeftBarView:self didSelectItemsAtButton:model button:sender];
        }
    }
    
}

#pragma mark - Private Action

- (void)updateSystemAuthority {
    TrackButton *cameraButton = self.buttonLists[1];
    [SystemAuthority authorCamera:^(BOOL granted) {
        if (!granted) {
            cameraButton.isClose = YES;
        }
    }];
    
    TrackButton *micButton = self.buttonLists.firstObject;
    [SystemAuthority authorMicphone:^(BOOL granted) {
        if (!granted) {
            micButton.isClose = YES;
        }
    }];
}


#pragma mark - getter

- (NSMutableArray *)buttonLists {
    if (!_buttonLists) {
        _buttonLists = [[NSMutableArray alloc] init];
    }
    return _buttonLists;
}

- (NSMutableArray *)dataLists {
    if (!_dataLists) {
        _dataLists = [[NSMutableArray alloc] init];
    }
    return _dataLists;
}

@end
