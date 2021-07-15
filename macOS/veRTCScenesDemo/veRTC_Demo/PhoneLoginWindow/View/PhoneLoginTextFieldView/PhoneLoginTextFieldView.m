//
//  PhoneLoginTextfileView.m
//  veRTC_Demo
//
//  Created by  on 2021/6/7.
//

typedef NS_ENUM(NSInteger, TextFieldStatus) {
    TextFieldStatusNone,
    TextFieldStatusActive,
    TextFieldStatusErrorLength,
    TextFieldStatusErrorIllegal,
};

#import "PhoneLoginTextFieldView.h"
#import "BaseTextField.h"

@interface PhoneLoginTextFieldView () <NSTextFieldDelegate>

@property (nonatomic, strong) NSView *maskView;

@property (nonatomic, strong) BaseTextField *textField;

@property (nonatomic, strong) NSLabel *errorLabel;

@property (nonatomic, assign) TextFieldStatus textFieldStatus;

@end

@implementation PhoneLoginTextFieldView
@synthesize text = _text;

- (instancetype)init {
    self = [super init];
    if (self) {
        self.wantsLayer = YES;
        self.layer.masksToBounds = NO;
        _isIllegal = NO;
        self.textFieldStatus = TextFieldStatusNone;
        [self setBackgroundColor:[NSColor clearColor]];
        
        [self addSubview:self.maskView];
        [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubview:self.textField];
        [self.textField mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self.mas_left).offset(16);
            make.right.equalTo(self).offset(-16);
            make.centerY.equalTo(self);
        }];
        
        [self addSubview:self.errorLabel];
        [self.errorLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.mas_bottom).offset(4);
            make.left.equalTo(self).offset(0);
        }];
        
        __weak __typeof(self) wself = self;
        self.textField.changeFirstResponder = ^(BOOL isFirst) {
            if (wself.textFieldStatus == TextFieldStatusErrorLength ||
                wself.textFieldStatus == TextFieldStatusErrorIllegal) {
                
            } else {
                wself.textFieldStatus = isFirst ? TextFieldStatusActive : TextFieldStatusNone;
            }
        };
    }
    return self;
}

#pragma mark - Private Action

- (void)setTextFieldStatus:(TextFieldStatus)textFieldStatus {
    _textFieldStatus = textFieldStatus;
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(dismissErrorLabel:) object:self.textField];
    switch (textFieldStatus) {
        case TextFieldStatusNone:
            self.maskView.layer.borderWidth = 0;
            self.errorLabel.text = @"";
            _isIllegal = NO;
            break;
        case TextFieldStatusActive:
            if (self.isNeedBorder) {
                self.maskView.layer.borderColor = [NSColor colorFromHexString:@"#4080FF"].CGColor;
                self.maskView.layer.borderWidth = 1;
            }
            self.errorLabel.text = @"";
            _isIllegal = NO;
            break;
        case TextFieldStatusErrorLength:
            self.maskView.layer.borderColor = [NSColor colorFromHexString:@"#F53F3F"].CGColor;
            self.maskView.layer.borderWidth = 1;
            self.errorLabel.text = self.errorStr;
            _isIllegal = NO;
            [self performSelector:@selector(dismissErrorLabel:) withObject:self.textField afterDelay:2];
            break;
        case TextFieldStatusErrorIllegal:
            self.maskView.layer.borderColor = [NSColor colorFromHexString:@"#F53F3F"].CGColor;
            self.maskView.layer.borderWidth = 1;
            self.errorLabel.text = self.errorStr;
            _isIllegal = YES;
            break;
            
        default:
            break;
    }
    if (IsEmptyStr(self.textField.stringValue)) {
        _isIllegal = YES;
    }
    if (self.changeInputIllegal) {
        self.changeInputIllegal(self.isIllegal);
    }
}

- (void)dismissErrorLabel:(NSTextField *)textField {
    self.textFieldStatus = self.textField.isFirstResponder ? TextFieldStatusActive : TextFieldStatusNone;
}

#pragma mark - Publish Action

- (void)textBecomeFirstResponder {
    [self.textField becomeFirstResponder];
}

- (void)setText:(NSString *)text {
    self.textField.stringValue = text;
}

- (NSString *)text {
    return self.textField.stringValue;
}

- (void)setRightSpace:(CGFloat)rightSpace {
    _rightSpace = rightSpace;
    
    [self.textField mas_updateConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self).offset(-rightSpace);
    }];
}

- (void)setPlaceholderStr:(NSString *)placeholderStr {
    _placeholderStr = placeholderStr;
    
    NSAttributedString *attrString = [[NSAttributedString alloc] initWithString:placeholderStr attributes:
    @{NSForegroundColorAttributeName:[NSColor colorFromHexString:@"#4E5969"],
                 NSFontAttributeName:self.textField.font
         }];
    
    self.textField.placeholderAttributedString = attrString;
}

#pragma mark - NSTextFieldDelegate

- (void)controlTextDidChange:(NSNotification *)notification {
    NSTextField *textField = (NSTextField *)notification.object;
    if (textField.stringValue.length > 0) {
        if ([self isLengthLimit:textField] || ![LocalUserCompoments isMatchUserName:textField.stringValue]) {
            if ([self isLengthLimit:textField]) {
                self.textFieldStatus = TextFieldStatusErrorLength;
                NSString *text = textField.stringValue;
                textField.stringValue = [text substringToIndex:self.maxLimit];
            }
            if (![LocalUserCompoments isMatchUserName:textField.stringValue]) {
                self.textFieldStatus = TextFieldStatusErrorIllegal;
            }
        } else {
            self.textFieldStatus = TextFieldStatusActive;
        }
    } else {
        self.textFieldStatus = self.textField.isFirstResponder ? TextFieldStatusActive : TextFieldStatusNone;
    }
}

- (BOOL)isLengthLimit:(NSTextField *)textField {
    if (textField.stringValue.length > self.maxLimit) {
        return YES;
    } else {
        return NO;
    }
}

- (BOOL)control:(NSControl *)control textView:(NSTextView *)textView doCommandBySelector:(SEL)commandSelector {
    if (commandSelector == @selector(insertTab:)) {
        if (self.keyboardClickTab) {
            self.keyboardClickTab();
        }
        return YES;
    } else if (commandSelector == @selector(insertNewline:)) {
        if (self.keyboardClickEnter) {
            self.keyboardClickEnter();
        }
        return YES;
    } else {
        return NO;
    }
}

#pragma mark - getter

- (NSView *)maskView {
    if (!_maskView) {
        _maskView = [[NSView alloc] init];
        _maskView.backgroundColor = [NSColor colorFromRGBHexString:@"#1C222D"];
        _maskView.wantsLayer = YES;
        _maskView.layer.cornerRadius = 8;
        _maskView.layer.masksToBounds = YES;
    }
    return _maskView;
}

- (BaseTextField *)textField {
    if (!_textField) {
        _textField = [[BaseTextField alloc] init];
        _textField.textColor = [NSColor blackColor];
        _textField.font = [NSFont systemFontOfSize:14 weight:NSFontWeightRegular];
        _textField.delegate = self;
        _textField.bezelStyle = NSBezelStyleTexturedSquare;
        _textField.bordered = NO;
        [_textField setBackgroundColor:[NSColor clearColor]];
        [_textField.window makeFirstResponder:nil];
        [_textField setFocusRingType:NSFocusRingTypeNone];
        _textField.maximumNumberOfLines = 1;
        
        _textField.textColor = [NSColor whiteColor];
    }
    return _textField;
}

- (NSLabel *)errorLabel {
    if (!_errorLabel) {
        _errorLabel = [[NSLabel alloc] init];
        _errorLabel.font = [NSFont systemFontOfSize:14];
        _errorLabel.textColor = [NSColor colorFromHexString:@"#F53F3F"];
    }
    return _errorLabel;
}

@end
