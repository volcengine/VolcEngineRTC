//
//  FeedbackInputView.m
//  quickstart
//
//  Created by  on 2021/3/25.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "FeedbackInputView.h"

@interface FeedbackInputView () <UITextViewDelegate>

@property (nonatomic, strong) UITextView *textView;

@property (nonatomic, strong) UILabel *placeholderLabel;

@end

@implementation FeedbackInputView

- (instancetype)init {
    self = [super init];
    if (self) {
        
        [self addSubview:self.textView];
        [self addSubview:self.placeholderLabel];
        
        [self.placeholderLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.left.mas_equalTo(12);
        }];
        
        [self.textView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.left.mas_equalTo(5);
            make.bottom.right.mas_equalTo(-5);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)resignFirstResponder {
    [self.textView resignFirstResponder];
}

- (void)setFont:(UIFont *)font {
    self.textView.font = font;
}

- (void)setTextColor:(UIColor *)textColor {
    self.textView.textColor = textColor;
}

#pragma mark - UITextViewDelegate

- (void)textViewDidChange:(UITextView *)textView {
    self.placeholderLabel.hidden = textView.text.length > 0 ? YES : NO;
    
    NSInteger maxLength = 500;
    if(textView.text.length > maxLength) {
        textView.text = [textView.text substringToIndex:maxLength];
    }
}

#pragma mark - getter

- (UILabel *)placeholderLabel {
    if (!_placeholderLabel) {
        _placeholderLabel = [[UILabel alloc] init];
        _placeholderLabel.font = [UIFont systemFontOfSize:32/2];
        _placeholderLabel.textColor = [UIColor colorFromHexString:@"#4E5969"];
        _placeholderLabel.text = @"最多可输入500个字符";
    }
    return _placeholderLabel;
}

- (UITextView *)textView {
    if (!_textView) {
        _textView = [[UITextView alloc] init];
        _textView.delegate = self;
        _textView.backgroundColor = [UIColor clearColor];
    }
    return _textView;
}

@end
