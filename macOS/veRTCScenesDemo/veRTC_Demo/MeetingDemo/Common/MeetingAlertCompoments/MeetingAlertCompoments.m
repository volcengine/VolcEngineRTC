//
//  MeetingAlertCompoments.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import "MeetingAlertCompoments.h"

@interface MeetingAlertCompoments ()

@property (nonatomic, strong) NSView *contenView;
@property (nonatomic, strong) NSImageView *iconImageView;
@property (nonatomic, strong) NSLabel *titleLabel;
@property (nonatomic, strong) NSButton *cancelButton;
@property (nonatomic, strong) NSButton *confirmButton;

@property (nonatomic, copy) void (^clickButtonAction)(BOOL result);

@end

@implementation MeetingAlertCompoments

+ (MeetingAlertCompoments *)share {
    static MeetingAlertCompoments *meetingAlertCompoments = nil;
    static dispatch_once_t onceToken ;
    dispatch_once(&onceToken, ^{
        meetingAlertCompoments = [[self alloc] init];
    });
    return meetingAlertCompoments ;
}

- (void)showWithTitle:(NSString *)title clickBlock:(void (^)(BOOL result))block {
    [self addSubviewAndConstraints];
    
    self.clickButtonAction = block;
    self.titleLabel.text = title;
}

- (void)confirmButtonAction {
    [self dismiss];
    if (self.clickButtonAction) {
        self.clickButtonAction(YES);
    }
}

- (void)cancelButtonAction {
    [self dismiss];
    if (self.clickButtonAction) {
        self.clickButtonAction(NO);
    }
}

- (void)dismiss {
    [self.contenView removeAllSubView];
    [self.contenView removeFromSuperview];
    self.contenView = nil;
}

- (void)addSubviewAndConstraints {
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    NSView *windowView = appDelegate.windowManager.currentWindowController.window.contentView;
    
    [windowView addSubview:self.contenView];
    [self.contenView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(150);
        make.center.equalTo(windowView);
    }];
    
    [self.contenView addSubview:self.iconImageView];
    [self.iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(20, 20));
        make.left.equalTo(self.contenView).offset(95);
        make.top.equalTo(self.contenView).offset(33);
    }];
    
    [self.contenView addSubview:self.titleLabel];
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.iconImageView);
        make.left.equalTo(self.iconImageView.mas_right).offset(8);
    }];
    
    [self.contenView addSubview:self.confirmButton];
    [self.confirmButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(56, 32));
        make.bottom.equalTo(self.contenView).offset(-32);
        make.left.equalTo(self.contenView.mas_centerX).offset(6);
    }];
    
    [self.contenView addSubview:self.cancelButton];
    [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(56, 32));
        make.bottom.equalTo(self.contenView).offset(-32);
        make.right.equalTo(self.confirmButton.mas_left).offset(-12);
    }];
    
    [self.contenView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(self.titleLabel.mas_width).offset(95 * 2 + 30);
    }];
}

#pragma mark - getter

- (NSView *)contenView {
    if (!_contenView) {
        _contenView = [[NSView alloc] init];
        [_contenView setBackgroundColor:[NSColor whiteColor]];
        _contenView.wantsLayer = YES;
        _contenView.layer.masksToBounds = YES;
        _contenView.layer.cornerRadius = 2;
    }
    return _contenView;
}

- (NSImageView *)iconImageView {
    if (!_iconImageView) {
        _iconImageView = [[NSImageView alloc] init];
        [_iconImageView setBackgroundColor:[NSColor clearColor]];
        _iconImageView.image = [NSImage imageNamed:@"meeting_end_waring"];
    }
    return _iconImageView;
}

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
        _titleLabel.font = [NSFont systemFontOfSize:14 weight:NSFontWeightMedium];
    }
    return _titleLabel;
}

- (NSButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[NSButton alloc] init];
        [_cancelButton setBackgroundColorWithHexString:@"#F2F3F8"];
        [_cancelButton setTitleColor:@"#1D2129" title:@"取消"];
        [_cancelButton setTarget:self];
        [_cancelButton setAction:@selector(cancelButtonAction)];
        _cancelButton.wantsLayer = YES;
        _cancelButton.layer.masksToBounds = YES;
        _cancelButton.layer.cornerRadius = 2;
    }
    return _cancelButton;
}

- (NSButton *)confirmButton {
    if (!_confirmButton) {
        _confirmButton = [[NSButton alloc] init];
        [_confirmButton setBackgroundColorWithHexString:@"#1664FF"];
        [_confirmButton setTitleColor:@"#FFFFFF" title:@"确定"];
        [_confirmButton setTarget:self];
        [_confirmButton setAction:@selector(confirmButtonAction)];
        _confirmButton.wantsLayer = YES;
        _confirmButton.layer.masksToBounds = YES;
        _confirmButton.layer.cornerRadius = 2;
    }
    return _confirmButton;
}

@end
