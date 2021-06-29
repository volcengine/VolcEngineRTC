#import "BaseComboBox.h"

@interface BaseComboBox ()

@property (nonatomic, strong) NSButton *button;

@end

@implementation BaseComboBox

- (instancetype)init {
    self = [super init];
    if (self) {
        self.usesDataSource = YES;
        self.wantsLayer = YES;
        [self addSubview:self.button];
        [self.button mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.mas_equalTo(self);
        }];
    }
    return self;
}

- (void)setFontSize:(CGFloat)fontSize {
    _fontSize = fontSize;
    super.font = [NSFont systemFontOfSize:fontSize weight:NSFontWeightRegular];
}

- (void)buttonClick {
    [(NSComboBoxCell*)self.cell performSelector:@selector(popUp:)];
}

#pragma mark - getter

- (NSButton *)button {
    if (!_button) {
        _button = [[NSButton alloc] init];
        _button.title = @"";
        [_button setTarget:self];
        [_button setAction:@selector(buttonClick)];
        _button.wantsLayer = YES;
        _button.layer.backgroundColor = [NSColor clearColor].CGColor;
    }
    return _button;
}

@end
