#import "LoginView.h"
#import "NSColor+CorlorString.h"
#import "NSView+Snippet.h"
#import "NSButton+Snippet.h"
#import "Masonry.h"
#import "NSLabel.h"
#import "BaseTextField.h"

#define TEXTFIELD_MAX_LENGTH 18

@interface LoginView ()

@property (nonatomic, strong) NSImageView *roomImageView;
@property (nonatomic, strong) NSImageView *userImageView;
@property (nonatomic, strong) BaseTextField *roomIdTextField;
@property (nonatomic, strong) BaseTextField *userIdTextField;
@property (nonatomic, strong) NSButton *startLoginRoomBtn;

@end

@implementation LoginView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColor:[NSColor colorFromRGBHexString:@"#FFFFFF"]];
        [self setupUI];
    }
    return self;
}

- (void)setupUI {
    NSLabel *titleLable = [[NSLabel alloc] init];
    titleLable.font = [NSFont systemFontOfSize:32];;
    titleLable.text = @"登录";
    titleLable.textColor = [NSColor colorFromHexString:@"#333333"];
    titleLable.alignment = NSTextAlignmentCenter;
    [self addSubview:titleLable];
    [titleLable mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(15);
        make.left.mas_equalTo(32);
    }];
    
    [self addSubview:self.roomImageView];
    [self.roomImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(109);
        make.centerX.equalTo(self);
        make.size.mas_equalTo(CGSizeMake(326, 38));
    }];
    
    _roomIdTextField = [[BaseTextField alloc] init];
    _roomIdTextField.textColor = [NSColor blackColor];
    [_roomIdTextField setBackgroundColor:[NSColor clearColor]];
    _roomIdTextField.bordered = NO;
    [_roomIdTextField setFocusRingType:NSFocusRingTypeNone];
    _roomIdTextField.maximumNumberOfLines = 1;
    NSMutableAttributedString *attriString1 = [[NSMutableAttributedString alloc]
                                               initWithString:@"房间ID"];
    [attriString1 addAttribute:NSForegroundColorAttributeName
                         value:[NSColor colorFromHexString:@"#C1C1C1"]
                         range:NSMakeRange(0, attriString1.length)];
    _roomIdTextField.placeholderAttributedString = attriString1;
    [self addSubview:_roomIdTextField];
    [_roomIdTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.roomImageView);
        make.centerY.equalTo(self.roomImageView).offset(4);
        make.size.mas_equalTo(CGSizeMake(300, 24));
    }];
    
    
    [self addSubview:self.userImageView];
    [self.userImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.roomImageView.mas_bottom).offset(24);
        make.centerX.equalTo(self);
        make.size.mas_equalTo(CGSizeMake(326, 38));
    }];
    
    _userIdTextField = [[BaseTextField alloc] init];
    _userIdTextField.textColor = [NSColor blackColor];
    [_userIdTextField setBackgroundColor:[NSColor clearColor]];
    _userIdTextField.bordered = NO;
    [_userIdTextField setFocusRingType:NSFocusRingTypeNone];
    _userIdTextField.maximumNumberOfLines = 1;
    NSMutableAttributedString *attriString = [[NSMutableAttributedString alloc]
                                              initWithString:@"用户ID"];
    [attriString addAttribute:NSForegroundColorAttributeName
                        value:[NSColor colorFromHexString:@"#C1C1C1"]
                        range:NSMakeRange(0, attriString.length)];
    _userIdTextField.placeholderAttributedString = attriString;
    [self addSubview:_userIdTextField];
    [_userIdTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.userImageView);
        make.centerY.equalTo(self.userImageView).offset(4);
        make.size.mas_equalTo(CGSizeMake(300, 24));
    }];
    
    _startLoginRoomBtn = [[NSButton alloc] init];
    _startLoginRoomBtn.ignoresMultiClick = YES;
    [_startLoginRoomBtn setTitleColor:@"#FFFFFF" title:@"进入房间"];
    [_startLoginRoomBtn setTarget:self];
    [_startLoginRoomBtn setAction:@selector(startLoginRoomBtnClick)];
    [_startLoginRoomBtn setBackgroundColor:[NSColor colorFromHexString:@"#2F88FF"]];
    _startLoginRoomBtn.wantsLayer = YES;
    _startLoginRoomBtn.layer.cornerRadius = 4;
    _startLoginRoomBtn.layer.masksToBounds = YES;
    _startLoginRoomBtn.font = [NSFont systemFontOfSize:18];
    [self addSubview:_startLoginRoomBtn];
    [_startLoginRoomBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(_userIdTextField.mas_bottom).mas_offset(39);
        make.left.mas_equalTo(32);
        make.size.mas_equalTo(CGSizeMake(326, 38));
    }];
}

#pragma mark - ClickEvents

- (void)startLoginRoomBtnClick {
    if (self.clickBlock) {
        self.clickBlock(_roomIdTextField.stringValue, _userIdTextField.stringValue);
    }
}

#pragma mark - getter

- (NSImageView *)roomImageView {
    if (!_roomImageView) {
        _roomImageView = [[NSImageView alloc] init];
        _roomImageView.image = [NSImage imageNamed:@"login_b"];
    }
    return _roomImageView;
}

- (NSImageView *)userImageView {
    if (!_userImageView) {
        _userImageView = [[NSImageView alloc] init];
        _userImageView.image = [NSImage imageNamed:@"login_b"];
    }
    return _userImageView;
}

- (void)dealloc {
    
}

@end

