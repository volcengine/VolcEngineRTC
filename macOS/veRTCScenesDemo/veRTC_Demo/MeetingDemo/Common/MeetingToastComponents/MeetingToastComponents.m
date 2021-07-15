//
//  MeetingToastComponents.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import "MeetingToastComponents.h"

@interface MeetingToastComponents ()

@property (nonatomic, strong) NSView *bgView;

@end

@implementation MeetingToastComponents

+ (MeetingToastComponents *)shareMeetingToastComponents {
    static dispatch_once_t onceToken ;
    static MeetingToastComponents *toastComponents = nil;
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

- (void)showWithMessage:(NSString *)message view:(NSView *)windowView keep:(BOOL)isKeep block:(void (^)(BOOL result))block {
    if (message.length <= 0) {
        return;
    }
    if (!self.bgView) {
        self.bgView = [[NSView alloc] init];
    } else {
        return;
    }
    [self.bgView setBackgroundColorWithHexString:@"#ffffff"];
    self.bgView.wantsLayer = YES;
    self.bgView.layer.cornerRadius = 2;
    self.bgView.layer.masksToBounds = YES;
    
    NSLabel *titleLabel = [[NSLabel alloc] init];
    titleLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
    titleLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    titleLabel.text = message;
    
    NSImageView *iconImageView = [[NSImageView alloc] init];
    iconImageView.image = [NSImage imageNamed:@"meeting_end_waring"];
    
    NSButton *cancelButton = [[NSButton alloc] init];
    [cancelButton setImage:[NSImage imageNamed:@"meeting_toast_cancel"]];
    [cancelButton setTarget:self];
    [cancelButton setAction:@selector(cancelButtonAction:)];
    
    [windowView addSubview:self.bgView];
    [self.bgView addSubview:iconImageView];
    [self.bgView addSubview:titleLabel];
    [self.bgView addSubview:cancelButton];
    
    [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo((windowView.frame.size.height < 70) ? 0 : 70);
        make.height.mas_equalTo(36);
        make.centerX.equalTo(windowView);
        make.width.equalTo(titleLabel).offset(80);
    }];
    
    [iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(16, 16));
        make.centerY.equalTo(self.bgView);
        make.left.equalTo(self.bgView).offset(16);
    }];
    
    [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.bgView);
        make.left.equalTo(iconImageView.mas_right).offset(8);
    }];
    
    [cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(16, 16));
        make.centerY.equalTo(self.bgView);
        make.right.equalTo(self.bgView).offset(-16);
    }];
    
    if (!isKeep) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self dismiss];
            if (block) {
                block(YES);
            }
        });
    }
}

- (void)showWithMessage:(NSString *)message view:(NSView *)windowView block:(void (^)(BOOL result))block {
    [self showWithMessage:message view:windowView keep:NO block:block];
}

- (void)showWithMessage:(NSString *)message view:(NSView *)windowView {
    [self showWithMessage:message view:windowView block:^(BOOL result) {
        
    }];
}

- (void)showWithMessage:(NSString *)message {
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    NSView *windowView = appDelegate.windowManager.currentWindowController.window.contentView;
    [self showWithMessage:message view:windowView];
}

- (void)dismiss {
    [self.bgView removeAllSubView];
    [self.bgView removeFromSuperview];
    self.bgView = nil;
}


- (void)cancelButtonAction:(NSButton *)sender {
    [self dismiss];
}

#pragma mark - getter


@end
