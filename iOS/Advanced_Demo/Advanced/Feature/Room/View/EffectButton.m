//
//  EffectButton.m
//  quickstart

#import "EffectButton.h"

@implementation EffectButton

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.titleLabel.font = [UIFont systemFontOfSize:13];

        self.backgroundColor = [UIColor groupTableViewBackgroundColor];
        
        [self setTitleColor:[UIColor systemBlueColor] forState:UIControlStateNormal];
        [self setTitleColor:[UIColor whiteColor] forState:UIControlStateSelected];
    }
    return self;
}

- (void)setModel:(EffectModel *)model {
    _model = model;
    [self setTitle:model.dic[@"name"] forState:UIControlStateNormal];
}

- (void)setSelected:(BOOL)selected {
    [super setSelected:selected];
    if (selected) {
        self.backgroundColor = [UIColor systemBlueColor];
    } else {
        self.backgroundColor = [UIColor groupTableViewBackgroundColor];
    }
}

- (void)layoutSubviews {
    [super layoutSubviews];

    self.layer.cornerRadius = self.bounds.size.height * 0.5;
    self.layer.masksToBounds = YES;
}
@end
