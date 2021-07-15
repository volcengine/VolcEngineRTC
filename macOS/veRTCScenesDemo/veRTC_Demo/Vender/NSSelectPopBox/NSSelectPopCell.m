//
//  NSSelectPopCell.m
//  veRTC_Demo
//
//  Created by  on 2021/6/11.
//

#import "NSSelectPopCell.h"

@interface NSSelectPopCell ()

@property (nonatomic, strong) NSLabel *nameLabel;

@property (nonatomic, strong) TrackButton *hostButton;

@property (nonatomic, strong) NSButton *maskButton;

@property (nonatomic, strong) NSView *maskView;

@end

@implementation NSSelectPopCell

- (void)awakeFromNib {
    [self setBackgroundColor:[NSColor clearColor]];
    [self updateTrackingAreas];
    
    [self addSubview:self.maskView];
    [self addSubview:self.nameLabel];
    [self addSubview:self.maskButton];
    [self addSubview:self.hostButton];
    
    [self.nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self).offset(12);
        make.centerY.equalTo(self);
    }];
    
    [self.hostButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(12, 12));
        make.right.equalTo(self).offset(-12);
        make.centerY.equalTo(self);
    }];
    
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
    
    [self.maskButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
}

#pragma mark - Click Actuion

- (void)hostButtonAction {
    if (self.clickDeleteBlock) {
        self.clickDeleteBlock(self.messageStr);
    }
}

#pragma mark - Publish Action

- (void)setMessageStr:(NSString *)messageStr {
    _messageStr = messageStr;
    
    self.nameLabel.text = messageStr;
}

- (void)mouseEntered:(NSEvent *)event {
    [self trackWithEnter:YES];
}

- (void)mouseExited:(NSEvent *)event {
    [self trackWithEnter:NO];
}

- (void)scrollWheel:(NSEvent *)event {
    [super scrollWheel:event];
    
    [self trackWithEnter:NO];
}

#pragma mark - Private Action

- (void)trackWithEnter:(BOOL)isEnter {
    [self updateEnterStatus:isEnter];
}

- (void)updateEnterStatus:(BOOL)isEnter {
    if (isEnter) {
        self.maskView.hidden = NO;
        self.hostButton.hidden = self.isDelete ? NO : YES;
    } else {
        self.maskView.hidden = YES;
        self.hostButton.hidden = YES;
    }
}

- (void)updateTrackingAreas {
    NSArray * trackingAreas = [self trackingAreas];
    for (NSTrackingArea *area in trackingAreas) {
        [self removeTrackingArea:area];
    }
    
    NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:self.bounds
                                                                options:(NSTrackingMouseEnteredAndExited |
                                                                         NSTrackingMouseMoved |
                                                                         NSTrackingActiveInActiveApp |
                                                                         NSTrackingInVisibleRect |
                                                                         NSTrackingAssumeInside |
                                                                         NSTrackingCursorUpdate)
                                                                  owner:self
                                                               userInfo:nil];
    [self addTrackingArea:trackingArea];
}


- (void)maskButtonAction:(NSButton *)sender {
    if (self.clickBlock) {
        self.clickBlock(self.messageStr);
    }
}

#pragma mark - getter

- (NSLabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[NSLabel alloc] init];
        _nameLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
        _nameLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _nameLabel.lineBreakMode = NSLineBreakByTruncatingTail;
        [_nameLabel setBackgroundColor:[NSColor clearColor]];
        _nameLabel.enabled = NO;
    }
    return _nameLabel;
}

- (TrackButton *)hostButton {
    if (!_hostButton) {
        _hostButton = [[TrackButton alloc] init];
        _hostButton.hidden = YES;
        [_hostButton setTarget:self];
        [_hostButton setAction:@selector(hostButtonAction)];
        [_hostButton setBackgroundColor:[NSColor clearColor]];
        [_hostButton bingImageWithType:NO image:[NSImage imageNamed:@"meeting_set_delete"]];
    }
    return _hostButton;
}

- (NSButton *)maskButton {
    if (!_maskButton) {
        _maskButton = [[NSButton alloc] init];
        [_maskButton setBackgroundColor:[NSColor clearColor]];
        [_maskButton setTarget:self];
        [_maskButton setAction:@selector(maskButtonAction:)];
    }
    return _maskButton;
}

- (NSView *)maskView {
    if (!_maskView) {
        _maskView = [[NSView alloc] init];
        _maskView.hidden = YES;
        [_maskView setBackgroundColorWithHexString:@"#F2F3F8"];
    }
    return _maskView;
}

@end
