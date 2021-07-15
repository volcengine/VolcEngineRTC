//
//  LoginBottonErrorView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import "LoginBottonErrorView.h"

@interface LoginBottonErrorView ()

@property (nonatomic, strong) NSView *bgView;
@property (nonatomic, strong) NSLabel *titleLabel;
@property (nonatomic, strong) NSLabel *messageLabel;

@end

@implementation LoginBottonErrorView


+ (LoginBottonErrorView *)shareLoginBottonErrorView {
    static dispatch_once_t onceToken ;
    static LoginBottonErrorView *toastComponents = nil;
    dispatch_once(&onceToken, ^{
        toastComponents = [[self alloc] init];
    });
    return toastComponents ;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        
    }
    return self;
}

#pragma mark - Publish Action

- (void)show:(NSView *)superView {
    [superView addSubview:self.bgView];
    [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(240, 131));
        make.centerX.equalTo(superView);
        make.bottom.mas_equalTo(-200);
    }];
    
    [superView addSubview:self.titleLabel];
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.equalTo(self.bgView).offset(16);
    }];
    
    [superView addSubview:self.messageLabel];
    [self.messageLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.bgView).offset(16);
        make.top.equalTo(self.titleLabel.mas_bottom).offset(4);
    }];
}

- (void)dismiss {
    [self.bgView removeFromSuperview];
    [self.messageLabel removeFromSuperview];
    [self.titleLabel removeFromSuperview];
}

- (void)setTitle:(NSString *)title {
    _title = title;
    self.titleLabel.stringValue = title;
}

- (void)setMessage:(NSString *)message {
    _message = message;
    self.messageLabel.stringValue = message;
    self.messageLabel.lineSpacing = 5;
}

#pragma mark - getter

- (NSView *)bgView {
    if (!_bgView) {
        _bgView = [[NSView alloc] init];
        [_bgView setBackgroundColorWithHexString:@"#ffffff"];
        _bgView.wantsLayer = YES;
        _bgView.layer.cornerRadius = 2;
        _bgView.layer.masksToBounds = YES;
    }
    return _bgView;
}

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.textColor = [NSColor colorFromHexString:@"#F53F3F"];
        _titleLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    }
    return _titleLabel;
}


- (NSLabel *)messageLabel {
    if (!_messageLabel) {
        _messageLabel = [[NSLabel alloc] init];
        _messageLabel.textColor = [NSColor colorFromHexString:@"#000000"];
        _messageLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _messageLabel.maximumNumberOfLines = 0;
    }
    return _messageLabel;
}

@end
