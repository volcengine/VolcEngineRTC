//
//  MeetingTextFileComponents.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import "MeetingTextFileComponents.h"
#import "MeetingToastComponents.h"

@interface MeetingTextFileComponents () <NSTextFieldDelegate>

@property (nonatomic, strong) NSTextField *textField;

@end

@implementation MeetingTextFileComponents
@synthesize text = _text;

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColorWithHexString:@"#F2F3F5"];
        self.maxLength = -1;
        [self addSubview:self.cancelButton];
        [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(20, 20));
            make.right.equalTo(self.mas_right).offset(-11);
            make.centerY.equalTo(self);
        }];
        
        [self addSubview:self.textField];
        [self.textField mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self.mas_left).offset(16);
            make.right.equalTo(self.cancelButton.mas_left).offset(-4);
            make.centerY.equalTo(self);
        }];
    }
    return self;
}

#pragma mark - Publish Action
- (void)setText:(NSString *)text {
    _text = text;
    if (NOEmptyStr(text)) {
        self.textField.stringValue = text;
    }
}

- (NSString *)text {
    return self.textField.stringValue;
}

- (void)cancelButtonAction {

}

- (void)setPlaceholderString:(NSString *)placeholderString {
    _placeholderString = placeholderString;
    
    NSAttributedString *attrString = [[NSAttributedString alloc] initWithString:placeholderString
                                                                     attributes:
                                      @{NSForegroundColorAttributeName:[NSColor colorFromHexString:@"#86909C"],
                                                   NSFontAttributeName:self.textField.font
                                      }];
    self.textField.placeholderAttributedString = attrString;
}

- (void)textBecomeFirstResponder {
    [self.textField becomeFirstResponder];
}

- (void)controlTextDidChange:(NSNotification *)notification {
    NSTextField *textField = (NSTextField *)notification.object;

    BOOL isExceed = [self isExceedMaximLength:self.textField];
    if (isExceed) {
        //show toast
        [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"输入长度超过18位字符。"];
    }
    
    if (self.isCheckNumberEng || self.isCheckAll) {
        BOOL isIllegal = NO;
        if (self.isCheckNumberEng) {
            isIllegal = ![LocalUserCompoments isMatchRoomID:textField.stringValue];
        }
        if (self.isCheckAll) {
            isIllegal = ![LocalUserCompoments isMatchUserName:textField.stringValue];
        }

        if ([self.delegate respondsToSelector:@selector(meetingTextFileComponents:checkInputIllegal:)]) {
            [self.delegate meetingTextFileComponents:self checkInputIllegal:isIllegal];
        }
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

#pragma mark - Private Action

- (BOOL)isExceedMaximLength:(NSTextField *)textField {
    BOOL isExceed = NO;
    NSString *text = textField.stringValue;
    if (self.maxLength >= 0) {
        if (text.length > self.maxLength) {
            textField.stringValue = [text substringToIndex:self.maxLength];
            isExceed = YES;
        }
    }
    return isExceed;
}

#pragma mark - getter

- (NSTextField *)textField {
    if (!_textField) {
        _textField = [[NSTextField alloc] init];
        _textField.textColor = [NSColor blackColor];
        _textField.font = [NSFont systemFontOfSize:14 weight:NSFontWeightRegular];
        _textField.delegate = self;
        _textField.bezelStyle = NSBezelStyleTexturedSquare;
        _textField.bordered = NO;
        [_textField setBackgroundColor:[NSColor clearColor]];
        [_textField.window makeFirstResponder:nil];
        [_textField setFocusRingType:NSFocusRingTypeNone];
        _textField.maximumNumberOfLines = 1;
    }
    return _textField;
}

- (NSButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[NSButton alloc] init];
        [_cancelButton setImage:[NSImage imageNamed:@"meeting_login_error"]];
        [_cancelButton setBackgroundColor:[NSColor clearColor]];
        [_cancelButton setAction:@selector(cancelButtonAction)];
        _cancelButton.hidden = YES;
    }
    return _cancelButton;
}

@end
