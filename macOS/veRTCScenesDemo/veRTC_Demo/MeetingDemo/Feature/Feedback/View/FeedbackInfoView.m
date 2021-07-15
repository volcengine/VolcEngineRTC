//
//  FeedbackInfoView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import "FeedbackInfoView.h"
#import "MeetingTextViewCompoments.h"

@interface FeedbackInfoView ()

@property (nonatomic, strong) NSLabel *titleLabel;
@property (nonatomic, strong) NSLabel *subTitleLabel;
@property (nonatomic, strong) TrackButton *info1Button;
@property (nonatomic, strong) TrackButton *info2Button;
@property (nonatomic, strong) TrackButton *info3Button;
@property (nonatomic, strong) TrackButton *info4Button;
@property (nonatomic, strong) MeetingTextViewCompoments *textView;

@property (nonatomic, strong) NSButton *cancelButton;
@property (nonatomic, strong) NSButton *submitButton;

@property (nonatomic, strong) NSButton *closeButton;

@end

@implementation FeedbackInfoView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubviewAndConstraints];
    }
    return self;
}

- (void)cancelButtonAction {
    if (self.clickInfoCancelBlock) {
        self.clickInfoCancelBlock();
    }
}

- (void)confirmButtonAction {
    
    if (self.clickInfoSubmitBlock) {
        self.clickInfoSubmitBlock();
    }
    if (self.clickInfoCancelBlock) {
        self.clickInfoCancelBlock();
    }
}

- (void)info1ButtonAction:(TrackButton *)sender {
    sender.isClose = !sender.isClose;
    [self updateButton:sender];
}

- (void)info2ButtonAction:(TrackButton *)sender {
    sender.isClose = !sender.isClose;
    [self updateButton:sender];
}

- (void)info3ButtonAction:(TrackButton *)sender {
    sender.isClose = !sender.isClose;
    [self updateButton:sender];
}

- (void)info4ButtonAction:(TrackButton *)sender {
    sender.isClose = !sender.isClose;
    [self updateButton:sender];
}

- (void)updateButton:(TrackButton *)button {
    if (button.isClose) {
        [button setBackgroundColor:[NSColor colorFromHexString:@"#E8F3FF"]];
        [button setTitleColor:@"#165DFF" title:button.title];
    } else {
        [button setBackgroundColor:[NSColor colorFromHexString:@"#F2F3F8"]];
        [button setTitleColor:@"#1D2129" title:button.title];
    }
}

#pragma mark - Private Action

- (void)addSubviewAndConstraints {
    [self addSubview:self.titleLabel];
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(32);
        make.top.mas_equalTo(32);
    }];
    
    [self addSubview:self.subTitleLabel];
    [self.subTitleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(32);
        make.top.mas_equalTo(126);
    }];
    
    [self addSubview:self.info1Button];
    [self.info1Button mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(32);
        make.top.mas_equalTo(70);
        make.size.mas_equalTo(CGSizeMake(80, 32));
    }];
    
    [self addSubview:self.info2Button];
    [self.info2Button mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.info1Button.mas_right).offset(16);
        make.top.mas_equalTo(70);
        make.size.mas_equalTo(CGSizeMake(104, 32));
    }];
    
    [self addSubview:self.info3Button];
    [self.info3Button mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.info2Button.mas_right).offset(16);
        make.top.mas_equalTo(70);
        make.size.mas_equalTo(CGSizeMake(80, 32));
    }];
    
    [self addSubview:self.info4Button];
    [self.info4Button mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.info3Button.mas_right).offset(16);
        make.top.mas_equalTo(70);
        make.size.mas_equalTo(CGSizeMake(80, 32));
    }];
    
    [self addSubview:self.textView];
    [self.textView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(416, 54));
        make.centerX.equalTo(self);
        make.top.equalTo(self.subTitleLabel.mas_bottom).offset(16);
    }];
    
    [self addSubview:self.submitButton];
    [self.submitButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.mas_centerX).offset(6);
        make.bottom.mas_equalTo(-32);
        make.size.mas_equalTo(CGSizeMake(56, 32));
    }];
    
    [self addSubview:self.cancelButton];
    [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.submitButton.mas_left).offset(-12);
        make.bottom.mas_equalTo(-32);
        make.size.mas_equalTo(CGSizeMake(56, 32));
    }];

    
    [self addSubview:self.closeButton];
    [self.closeButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(20, 20));
        make.top.mas_equalTo(24);
        make.right.equalTo(self).offset(-24);
    }];
}

#pragma mark - getter

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        [_titleLabel setBackgroundColor:[NSColor clearColor]];
        _titleLabel.text = @"具体问题反馈";
        _titleLabel.font = [NSFont systemFontOfSize:14 weight:NSFontWeightRegular];
        _titleLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
    }
    return _titleLabel;
}

- (NSLabel *)subTitleLabel {
    if (!_subTitleLabel) {
        _subTitleLabel = [[NSLabel alloc] init];
        [_subTitleLabel setBackgroundColor:[NSColor clearColor]];
        _subTitleLabel.text = @"其他反馈问题";
        _subTitleLabel.font = [NSFont systemFontOfSize:14 weight:NSFontWeightRegular];
        _subTitleLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
    }
    return _subTitleLabel;
}

- (TrackButton *)info1Button {
    if (!_info1Button) {
        _info1Button = [[TrackButton alloc] init];
        [_info1Button setTitleColor:@"#1D2129" title:@"视频卡顿"];
        [_info1Button setBackgroundColorWithHexString:@"#F2F3F8"];
        [_info1Button setTarget:self];
        [_info1Button setAction:@selector(info1ButtonAction:)];
        _info1Button.wantsLayer = YES;
        _info1Button.layer.masksToBounds = YES;
        _info1Button.layer.cornerRadius = 2;
    }
    return _info1Button;
}

- (TrackButton *)info2Button {
    if (!_info2Button) {
        _info2Button = [[TrackButton alloc] init];
        [_info2Button setBackgroundColorWithHexString:@"#F2F3F8"];
        [_info2Button setTitleColor:@"#1D2129" title:@"共享内容故障"];
        [_info2Button setTarget:self];
        [_info2Button setAction:@selector(info1ButtonAction:)];
        _info2Button.wantsLayer = YES;
        _info2Button.layer.masksToBounds = YES;
        _info2Button.layer.cornerRadius = 2;
    }
    return _info2Button;
}

- (TrackButton *)info3Button {
    if (!_info3Button) {
        _info3Button = [[TrackButton alloc] init];
        [_info3Button setBackgroundColorWithHexString:@"#F2F3F8"];
        [_info3Button setTitleColor:@"#1D2129" title:@"音频卡顿"];
        [_info3Button setTarget:self];
        [_info3Button setAction:@selector(info1ButtonAction:)];
        _info3Button.wantsLayer = YES;
        _info3Button.layer.masksToBounds = YES;
        _info3Button.layer.cornerRadius = 2;
    }
    return _info3Button;
}
- (TrackButton *)info4Button {
    if (!_info4Button) {
        _info4Button = [[TrackButton alloc] init];
        [_info4Button setBackgroundColorWithHexString:@"#F2F3F8"];
        [_info4Button setTitleColor:@"#1D2129" title:@"其他问题"];
        [_info4Button setTarget:self];
        [_info4Button setAction:@selector(info1ButtonAction:)];
        _info4Button.wantsLayer = YES;
        _info4Button.layer.masksToBounds = YES;
        _info4Button.layer.cornerRadius = 2;
    }
    return _info4Button;
}

- (MeetingTextViewCompoments *)textView {
    if (!_textView) {
        _textView = [[MeetingTextViewCompoments alloc] init];
        [_textView setBackgroundColorWithHexString:@"#F2F3F8"];
        _textView.wantsLayer = YES;
        _textView.layer.masksToBounds = YES;
        _textView.layer.cornerRadius = 2;
        
        _textView.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _textView.textColor = [NSColor colorFromHexString:@"#1D2129"];
        _textView.placeholderString = @"最多可输入500个字符";
    }
    return _textView;
}

- (NSButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[NSButton alloc] init];
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
- (NSButton *)submitButton {
    if (!_submitButton) {
        _submitButton = [[NSButton alloc] init];
        _submitButton = [[NSButton alloc] init];
        [_submitButton setBackgroundColorWithHexString:@"#1664FF"];
        [_submitButton setTitleColor:@"#FFFFFF" title:@"提交"];
        [_submitButton setTarget:self];
        [_submitButton setAction:@selector(confirmButtonAction)];
        _submitButton.wantsLayer = YES;
        _submitButton.layer.masksToBounds = YES;
        _submitButton.layer.cornerRadius = 2;
    }
    return _submitButton;
}

- (NSButton *)closeButton {
    if (!_closeButton) {
        _closeButton = [[NSButton alloc] init];
        [_closeButton setImage:[NSImage imageNamed:@"meeting_set_cancel"]];
        [_closeButton setBackgroundColor:[NSColor clearColor]];
        [_closeButton setTarget:self];
        [_closeButton setAction:@selector(cancelButtonAction)];
    }
    return _closeButton;
}

@end
