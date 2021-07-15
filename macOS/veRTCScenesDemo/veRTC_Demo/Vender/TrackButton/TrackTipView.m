//
//  TrackTipView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/14.
//

#import "TrackTipView.h"

@interface TrackTipView ()

@property (nonatomic, strong) NSImageView *arrowImageView;

@property (nonatomic, strong) NSView *contentView;

@property (nonatomic, strong) NSLabel *titleLabel;

@end

@implementation TrackTipView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.arrowImageView];
        [self.arrowImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(10, 4));
            make.bottom.equalTo(self);
            make.centerX.equalTo(self).offset(-self.offsetX);
        }];
        
        [self addSubview:self.contentView];
        [self.contentView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.top.equalTo(self);
            make.bottom.mas_equalTo(-3);
        }];
        
        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(self.contentView);
        }];
        
        [self mas_updateConstraints:^(MASConstraintMaker *make) {
            make.width.equalTo(self.titleLabel.mas_width).offset(24);
        }];
    }
    return self;
}

- (void)setTitle:(NSString *)title {
    _title = title;
    
    self.titleLabel.text = title;
}

- (void)setOffsetX:(CGFloat)offsetX {
    _offsetX = offsetX;
    
    [self.arrowImageView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self).offset(-self.offsetX);
    }];
}

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.textColor = [NSColor whiteColor];
        _titleLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    }
    return _titleLabel;
}

- (NSView *)contentView {
    if (!_contentView) {
        _contentView = [[NSView alloc] init];
        [_contentView setBackgroundColorWithHexString:@"#1D2129"];
        _contentView.wantsLayer = YES;
        _contentView.layer.masksToBounds = YES;
        _contentView.layer.cornerRadius = 2;
    }
    return _contentView;
}

- (NSImageView *)arrowImageView {
    if (!_arrowImageView) {
        _arrowImageView = [[NSImageView alloc] init];
        _arrowImageView.image = [NSImage imageNamed:@"meeting_tip_arrow"];
        [_arrowImageView setBackgroundColor:[NSColor clearColor]];
    }
    return _arrowImageView;
}

@end
