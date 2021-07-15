//
//  RoomBottomView.m
//  quickstart
//
//  Created by  on 2021/3/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "RoomBottomView.h"

@interface RoomBottomView ()

@property (nonatomic, strong) UIView *contentView;
@property (nonatomic, strong) UIView *moreView;
@property (nonatomic, strong) UIView *lineView;

@property (nonatomic, strong) NSMutableArray *buttonLists;

@end

@implementation RoomBottomView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.clipsToBounds = NO;
        self.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
        
        [self addSubview:self.moreView];
        [self.moreView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(self);
            make.height.mas_equalTo(148/2);
            make.top.equalTo(self).offset(0);
        }];
        
        [self addSubview:self.contentView];
        [self.contentView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubviewAndConstraints];
    }
    return self;
}

- (void)buttonAction:(RoomItemButton *)sender {
    RoomBottomStatus status = sender.tag - 3000;
    
    if (status == RoomBottomStatusMore) {
        sender.status = (sender.status == ButtonStatusActive) ? ButtonStatusNone : ButtonStatusActive;
        if (sender.status == ButtonStatusActive) {
            self.moreView.hidden = NO;
            sender.isAction = YES;
        }
        CGFloat time = 0.25;
        [UIView animateWithDuration:time animations:^{
            [self.moreView mas_updateConstraints:^(MASConstraintMaker *make) {
                make.top.equalTo(self).offset(sender.status == ButtonStatusActive ? (-148/2) : 0);
            }];
            [self.moreView.superview layoutIfNeeded];
        }];
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(time * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            if (sender.status == ButtonStatusNone) {
                self.moreView.hidden = YES;
                sender.isAction = NO;
            }
        });
    } else {
        if ([self.delegate respondsToSelector:@selector(roomBottomView:itemButton:didSelectStatus:)]) {
            [self.delegate roomBottomView:self itemButton:sender didSelectStatus:status];
        }
    }
}

- (void)dismissMoreView {
    if (self.moreView.hidden) {
        return;
    }
    NSString *title = [self getdesTitleWithStatus:RoomBottomStatusMore];
    RoomItemButton *selectButton = nil;
    for (RoomItemButton *button in self.buttonLists) {
        if ([button.desTitle isEqualToString:title]) {
            selectButton = button;
            break;
        }
    }
    if (selectButton) {
        if (selectButton.status == ButtonStatusActive) {
            [self buttonAction:selectButton];
        }
    }
}

- (void)addSubviewAndConstraints {
    NSInteger groupNum = 5;
    for (int i = 0; i < groupNum * 2; i++) {
        RoomItemButton *button = [[RoomItemButton alloc] init];
        button.tag = 3000 + i;
        UIImage *image = [self getImageWithStatus:i];
        [button bingImage:image status:ButtonStatusNone];
        [button bingImage:[self getSelectImageWithStatus:i] status:ButtonStatusActive];
        button.desTitle = [self getdesTitleWithStatus:i];
        [button addTarget:self action:@selector(buttonAction:) forControlEvents:UIControlEventTouchUpInside];
        [button setImageEdgeInsets:UIEdgeInsetsMake(10, 0, 30, 0)];
        button.imageView.contentMode = UIViewContentModeScaleAspectFit;
        button.hidden = image ? NO : YES;
        if (i < groupNum) {
            [self.contentView addSubview:button];
        } else {
            [self.moreView addSubview:button];
        }
        [self.buttonLists addObject:button];
    }
    
    [self.contentView.subviews mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedItemLength:150/2 leadSpacing:0 tailSpacing:0];
    [self.contentView.subviews mas_updateConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.contentView);
        make.bottom.mas_equalTo(-[DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.moreView.subviews mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedItemLength:150/2 leadSpacing:0 tailSpacing:0];
    [self.moreView.subviews mas_updateConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.moreView);
        make.bottom.equalTo(self.moreView).offset(-10);
    }];
    
    [self.moreView addSubview:self.lineView];
    [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.left.right.equalTo(_moreView);
        make.height.mas_equalTo(XH_1PX_WIDTH);
    }];
}

- (void)updateButtonStatus:(RoomBottomStatus)status close:(BOOL)isClose {
    NSString *title = [self getdesTitleWithStatus:status];
    RoomItemButton *selectButton = nil;
    for (RoomItemButton *button in self.buttonLists) {
        if ([button.desTitle isEqualToString:title]) {
            selectButton = button;
            break;
        }
    }
    if (selectButton) {
        selectButton.status = isClose ? ButtonStatusActive : ButtonStatusNone;
    }
}

- (ButtonStatus)getButtonStatus:(RoomBottomStatus)status {
    NSString *title = [self getdesTitleWithStatus:status];
    RoomItemButton *selectButton = nil;
    for (RoomItemButton *button in self.buttonLists) {
        if ([button.desTitle isEqualToString:title]) {
            selectButton = button;
            break;
        }
    }
    if (selectButton) {
        return selectButton.status;
    } else {
        return ButtonStatusNone;
    }
}

#pragma mark - Private Action

- (NSString *)getdesTitleWithStatus:(RoomBottomStatus)status {
    NSString *name = @"";
    switch (status) {
        case RoomBottomStatusMic:
            name = @"麦克风";
            break;
        case RoomBottomStatusCamera:
            name = @"摄像头";
            break;
        case RoomBottomStatusScreen:
            name = @"共享";
            break;
        case RoomBottomStatusPar:
            name = @"参会人";
            break;
        case RoomBottomStatusMore:
            name = @"更多";
            break;
        case RoomBottomStatusRecord:
            name = @"录制";
            break;
        case RoomBottomStatusAudio:
            name = @"扬声器";
            break;
        case RoomBottomStatusSet:
            name = @"设置";
            break;
        default:
            break;
    }
    return name;
}

- (UIImage *)getImageWithStatus:(RoomBottomStatus)status {
    NSString *name = @"";
    switch (status) {
        case RoomBottomStatusMic:
            name = @"meeting_room_mic";
            break;
        case RoomBottomStatusCamera:
            name = @"meeting_room_video";
            break;
        case RoomBottomStatusScreen:
            name = @"meeting_room_screen";
            break;
        case RoomBottomStatusPar:
            name = @"meeting_room_par";
            break;
        case RoomBottomStatusMore:
            name = @"meeting_room_more";
            break;
        case RoomBottomStatusRecord:
            name = @"meeting_room_recor";
            break;
        case RoomBottomStatusAudio:
            name = @"meeting_room_audio";
            break;
        case RoomBottomStatusSet:
            name = @"meeting_room_set";
            break;
        default:
            break;
    }
    return [UIImage imageNamed:name];
}

- (UIImage *)getSelectImageWithStatus:(RoomBottomStatus)status {
    NSString *name = @"";
    switch (status) {
        case RoomBottomStatusMic:
            name = @"meeting_room_mic_s";
            break;
        case RoomBottomStatusCamera:
            name = @"meeting_room_video_s";
            break;
        case RoomBottomStatusMore:
            name = @"meeting_room_more_s";
            break;
        case RoomBottomStatusRecord:
            name = @"meeting_room_recor_s";
            break;
        case RoomBottomStatusScreen:
            name = @"meeting_par_screen_s";
            break;
        case RoomBottomStatusAudio:
            name = @"meeting_room_earpiece";
            break;
        default:
            break;
    }
    return [UIImage imageNamed:name];
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event {
    
    if (!self.isUserInteractionEnabled || self.isHidden || self.alpha <= 0.01) {
        return nil;
    }
    
    UIView *view = [super hitTest:point withEvent:event];
    CGPoint convertedPoint = [self.moreView convertPoint:point fromView:self];
    UIView *hitTestView = [self.moreView hitTest:convertedPoint withEvent:event];
    if (hitTestView) {
        return hitTestView;
    } else {
        return view;
    }
}


#pragma mark - getter

- (UIView *)contentView {
    if (!_contentView) {
        _contentView = [[UIView alloc] init];
        _contentView.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
    }
    return _contentView;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
        
    }
    return _lineView;
}

- (UIView *)moreView {
    if (!_moreView) {
        _moreView = [[UIView alloc] init];
        _moreView.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
        _moreView.hidden = YES;
    }
    return _moreView;
}

- (NSMutableArray *)buttonLists {
    if (!_buttonLists) {
        _buttonLists = [[NSMutableArray alloc] init];
    }
    return _buttonLists;
}

@end
