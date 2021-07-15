//
//  VocieTextFileView.m
//  veRTC_Demo
//
//  Created by  on 2021/5/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VocieCreateTextFieldView.h"

@interface VocieCreateTextFieldView ()

@property (nonatomic, strong) UITextField *textField;

@property (nonatomic, strong) UIView *lineView;

@property (nonatomic, strong) BaseButton *cancelButton;

@property (nonatomic, strong) UILabel *errorLabel;

@end

@implementation VocieCreateTextFieldView
@synthesize text = _text;

- (instancetype)initWithModify:(BOOL)isModify {
    self = [super init];
    if (self) {
        self.clipsToBounds = NO;
        _isIllega = NO;
        self.backgroundColor = [UIColor clearColor];
        
        [self addSubview:self.textField];
        [self addSubview:self.cancelButton];
        [self addSubview:self.lineView];
        [self addSubview:self.errorLabel];
        
        self.cancelButton.hidden = !isModify;
        [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(20, 20));
            make.right.equalTo(self);
            make.top.equalTo(self);
        }];
        
        [self.textField mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.top.equalTo(self);
            make.height.mas_equalTo(20);
            if (isModify) {
                make.right.equalTo(self.cancelButton.mas_left).offset(-16);
            } else {
                make.right.equalTo(self).offset(-16);
            }
        }];
        
        [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.centerX.equalTo(self);
            make.height.mas_equalTo(XH_1PX_WIDTH);
            if (isModify) {
                make.width.mas_equalTo(SCREEN_WIDTH);
            } else {
                make.width.equalTo(self);
            }
        }];
        
        [self addSubview:self.errorLabel];
        [self.errorLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self);
            make.top.mas_equalTo(self.mas_bottom).offset(2);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)setRightSpace:(CGFloat)rightSpace {
    _rightSpace = rightSpace;
    
    [self.textField mas_updateConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self).offset(-rightSpace);
    }];
}

- (void)setBoardType:(UIKeyboardType)boardType {
    _boardType = boardType;
    
    self.textField.keyboardType = boardType;
}

- (void)setText:(NSString *)text {
    _text = text;
    
    self.textField.text = text;
}

- (NSString *)text {
    return self.textField.text;
}

- (void)resignFirstResponder {
    [self.textField resignFirstResponder];
}

- (void)becomeFirstResponder {
    [self.textField becomeFirstResponder];
}

- (void)setPlaceholderStr:(NSString *)placeholderStr {
    _placeholderStr = placeholderStr;
    
    NSAttributedString *attrString = [[NSAttributedString alloc] initWithString:placeholderStr attributes:
    @{NSForegroundColorAttributeName:[UIColor colorFromHexString:@"#86909C"],
                 NSFontAttributeName:self.textField.font
         }];
    self.textField.attributedPlaceholder = attrString;
}

- (void)setIsModify:(BOOL)isModify {
    _isModify = isModify;
    
}

#pragma mark - touch action

- (void)cancelButtonAction {
    self.textField.text = @"";
}

- (void)roomNumTextFieldChange:(UITextField *)textField {
    if (self.maxLimit <= 0) {
        //No Limit
        return;
    }
    
    NSInteger maxLimit = self.maxLimit;
    BOOL isIllega = ![LocalUserComponents isMatchUserName:textField.text];
    if (self.isOnlyNumber) {
        isIllega = ![LocalUserComponents isMatchNumber:textField.text];
    }
    BOOL isMaxLimit = textField.text.length > maxLimit;
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(dismissErrorLabel:) object:textField];
    if (isMaxLimit || isIllega) {
        NSString *message = @"";
        if (IsEmptyStr(self.errorMessage)) {
            message = [NSString stringWithFormat:@"仅支持中文、字母、数字，1-%ld位", (long)self.maxLimit];
        } else {
            message = self.errorMessage;
        }
        self.errorLabel.text = message;
        self.errorLabel.hidden = NO;
        if (isMaxLimit && isIllega) {
            textField.text = [textField.text substringToIndex:maxLimit];
        } else if (isMaxLimit) {
            [self performSelector:@selector(dismissErrorLabel:) withObject:textField afterDelay:2];
            textField.text = [textField.text substringToIndex:maxLimit];
        } else {
            
        }
        _isIllega = isIllega;
    } else {
        [self dismissErrorLabel:textField];
        _isIllega = NO;
    }
    
    if (self.textFieldChangeBlock) {
        self.textFieldChangeBlock(textField.text);
    }
}

- (void)dismissErrorLabel:(UITextField *)textField {
    self.errorLabel.hidden = YES;
}

#pragma mark - getter

- (UITextField *)textField {
    if (!_textField) {
        _textField = [[UITextField alloc] init];
        _textField.textColor = [UIColor whiteColor];
        _textField.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_textField addTarget:self action:@selector(roomNumTextFieldChange:) forControlEvents:UIControlEventEditingChanged];
    }
    return _textField;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromRGBHexString:@"#86909C"];
    }
    return _lineView;
}

- (BaseButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [BaseButton buttonWithType:UIButtonTypeCustom];
        [_cancelButton setImage:[UIImage imageNamed:@"menu_user_name"] forState:UIControlStateNormal];
        [_cancelButton addTarget:self action:@selector(cancelButtonAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _cancelButton;
}

- (UILabel *)errorLabel {
    if (!_errorLabel) {
        _errorLabel = [[UILabel alloc] init];
        _errorLabel.textColor = [UIColor colorFromHexString:@"#F53F3F"];
        _errorLabel.font = [UIFont systemFontOfSize:12];
        _errorLabel.hidden = YES;
    }
    return _errorLabel;
}

@end
