//
//  MeetingBaseSetingComponents.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import "MeetingBaseSetingComponents.h"

@interface MeetingBaseSetingComponents ()

@property (nonatomic, strong) NSLabel *titleLabel;

@end

@implementation MeetingBaseSetingComponents

- (instancetype)init {
    self = [super init];
    if (self) {
        self.wantsLayer = YES;
        self.layer.masksToBounds = NO;
        
        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(self.mas_left).offset(-16);
            make.centerY.equalTo(self);
        }];
    }
    return self;
}


- (void)setTitle:(NSString *)title {
    _title = title;
    self.titleLabel.text = title;
}

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.textColor = [NSColor colorFromHexString:@"#4E5969"];
        _titleLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _titleLabel.wantsLayer = YES;
    }
    return _titleLabel;
}

@end

