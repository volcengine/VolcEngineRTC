//
//  FeedbackView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import "FeedbackView.h"

@interface FeedbackView ()

@property (nonatomic, strong) NSLabel *titleLabel;
@property (nonatomic, strong) NSView *lineView;
@property (nonatomic, strong) TrackButton *goodButton;
@property (nonatomic, strong) TrackButton *badButton;
@property (nonatomic, strong) NSButton *cancelButton;

@end

@implementation FeedbackView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(24);
            make.top.mas_equalTo(24);
        }];
        
        [self addSubview:self.lineView];
        [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(1, 32));
            make.centerX.equalTo(self);
            make.bottom.mas_equalTo(-28);
        }];
        
        [self addSubview:self.goodButton];
        [self.goodButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(40, 40));
            make.right.equalTo(self.lineView.mas_left).offset(-40);
            make.bottom.mas_equalTo(-24);
        }];
        
        [self addSubview:self.badButton];
        [self.badButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(40, 40));
            make.left.equalTo(self.lineView.mas_right).offset(40);
            make.bottom.mas_equalTo(-24);
        }];
        
        [self addSubview:self.cancelButton];
        [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(20, 20));
            make.top.mas_equalTo(24);
            make.right.equalTo(self).offset(-24);
        }];
    }
    return self;
}

- (void)cancelButtonAction {
    if ([self.deleagte respondsToSelector:@selector(feedbackView:clickButton:)]) {
        [self.deleagte feedbackView:self clickButton:3];
    }
}

- (void)goodButtonAction {
    if ([self.deleagte respondsToSelector:@selector(feedbackView:clickButton:)]) {
        [self.deleagte feedbackView:self clickButton:1];
    }
}

- (void)badButtonAction {
    if ([self.deleagte respondsToSelector:@selector(feedbackView:clickButton:)]) {
        [self.deleagte feedbackView:self clickButton:2];
    }
}

#pragma mark - getter

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
        _titleLabel.font = [NSFont systemFontOfSize:14 weight:NSFontWeightRegular];
        _titleLabel.text = @"本次通话体验如何？";
    }
    return _titleLabel;
}

- (NSView *)lineView {
    if (!_lineView) {
        _lineView = [[NSView alloc] init];
        [_lineView setBackgroundColorWithHexString:@"#E5E6EB"];
    }
    return _lineView;
}

- (TrackButton *)goodButton {
    if (!_goodButton) {
        _goodButton = [[TrackButton alloc] init];
        
        [_goodButton bingImageWithStatus:TrackButtonStatusDefault image:[NSImage imageNamed:@"meeting_feedback_good"]];
        [_goodButton bingImageWithStatus:TrackButtonStatusActive image:[NSImage imageNamed:@"meeting_feedback_good_select"]];
        [_goodButton bingImageWithStatus:TrackButtonStatusHover image:[NSImage imageNamed:@"meeting_feedback_good_select"]];
        
        [_goodButton setBackgroundColor:[NSColor clearColor]];
        [_goodButton setTarget:self];
        [_goodButton setAction:@selector(goodButtonAction)];
    }
    return _goodButton;
}

- (TrackButton *)badButton {
    if (!_badButton) {
        _badButton = [[TrackButton alloc] init];
        [_badButton bingImageWithStatus:TrackButtonStatusDefault image:[NSImage imageNamed:@"meeting_feedback_bad"]];
        [_badButton bingImageWithStatus:TrackButtonStatusActive image:[NSImage imageNamed:@"meeting_feedback_bad_select"]];
        [_badButton bingImageWithStatus:TrackButtonStatusHover image:[NSImage imageNamed:@"meeting_feedback_bad_select"]];
        
        [_badButton setBackgroundColor:[NSColor clearColor]];
        [_badButton setTarget:self];
        [_badButton setAction:@selector(badButtonAction)];
    }
    return _badButton;
}

- (NSButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[NSButton alloc] init];
        [_cancelButton setImage:[NSImage imageNamed:@"meeting_set_cancel"]];
        [_cancelButton setBackgroundColor:[NSColor clearColor]];
        [_cancelButton setTarget:self];
        [_cancelButton setAction:@selector(cancelButtonAction)];
    }
    return _cancelButton;
}











@end
