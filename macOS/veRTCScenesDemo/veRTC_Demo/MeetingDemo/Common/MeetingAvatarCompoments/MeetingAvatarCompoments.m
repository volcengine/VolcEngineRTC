//
//  MeetingAvatarCompoments.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "MeetingAvatarCompoments.h"

@interface MeetingAvatarCompoments ()

@property (nonatomic, strong) NSLabel *avatarLabel;
@property (nonatomic, strong) NSView *avatarBgView;

@end

@implementation MeetingAvatarCompoments

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.avatarBgView];
        [self.avatarBgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubview:self.avatarLabel];
        [self.avatarLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(self.avatarBgView);
        }];
    }
    return self;
}

- (void)setFontSize:(NSInteger)fontSize {
    _fontSize = fontSize;
    
    self.avatarLabel.font = [NSFont systemFontOfSize:fontSize weight:NSFontWeightMedium];
}

- (void)setText:(NSString *)text {
    _text = text;
    
    if (NOEmptyStr(text)) {
        if (text.length > 0) {
            self.avatarLabel.text = [text substringToIndex:1];
        }
    }
}

#pragma mark - getter

- (NSView *)avatarBgView {
    if (!_avatarBgView) {
        _avatarBgView = [[NSView alloc] init];
        [_avatarBgView setBackgroundColorWithHexString:@"#4E5969"];
    }
    return _avatarBgView;
}

- (NSLabel *)avatarLabel {
    if (!_avatarLabel) {
        _avatarLabel = [[NSLabel alloc] init];
        _avatarLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        
    }
    return _avatarLabel;
}

@end
