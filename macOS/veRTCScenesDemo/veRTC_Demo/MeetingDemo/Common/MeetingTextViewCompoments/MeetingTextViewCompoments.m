//
//  MeetingTextViewCompoments.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import "MeetingTextViewCompoments.h"

@interface MeetingTextViewCompoments () <NSTextViewDelegate>

@property (nonatomic, strong) NSTextView *textView;
@property (nonatomic, strong) NSScrollView *scrollView;
@property (nonatomic, strong) NSLabel *placeholderLabel;
@property (nonatomic, strong) NSLabel *numLabel;

@end

@implementation MeetingTextViewCompoments

- (instancetype)init {
    self = [super init];
    if (self) {
        self.scrollView.documentView = self.textView;
        [self addSubview:self.scrollView];
        [self.scrollView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(15.6);
            make.right.mas_equalTo(-15.6);
            make.top.mas_equalTo(5);
            make.bottom.mas_equalTo(-5);
        }];
        
        [self.textView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.top.equalTo(self);
            make.right.equalTo(self.scrollView.mas_right).offset(-50);
            make.height.mas_equalTo(FLT_MAX);
        }];
        
        [self addSubview:self.placeholderLabel];
        [self.placeholderLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.mas_equalTo(20);
            make.top.mas_equalTo(5);
        }];
        
        [self addSubview:self.numLabel];
        [self.numLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.mas_equalTo(-10.4);
            make.bottom.mas_equalTo(-4);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)setFont:(NSFont *)font {
    _font = font;
    self.textView.font = font;
}

- (void)setTextColor:(NSColor *)textColor {
    _textColor = textColor;
    self.textView.textColor = textColor;
}

- (void)setPlaceholderString:(NSString *)placeholderString {
    _placeholderString = placeholderString;
    
    self.placeholderLabel.text = placeholderString;
}

- (void)textViewDidChangeSelection:(NSNotification *)notification {
    NSTextView *textView = (NSTextView *)notification.object;
    
    [self isExceedMaximLength:textView];
    
    if (textView.string.length > 0) {
        self.placeholderLabel.hidden = YES;
    } else {
        self.placeholderLabel.hidden = NO;
    }
    
    self.numLabel.text = [NSString stringWithFormat:@"%ld/500", (long)textView.string.length];
}

- (BOOL)isExceedMaximLength:(NSTextView *)textView {
    BOOL isExceed = NO;
    NSString *text = textView.string;
    if (text.length > 500) {
        dispatch_async(dispatch_get_main_queue(), ^{
            textView.string = [text substringToIndex:500];;
        });
        isExceed = YES;
    }
    return isExceed;
}

#pragma mark - getter

- (NSTextView *)textView {
    if (!_textView) {
        _textView = [[NSTextView alloc] init];
        [_textView setBackgroundColorWithHexString:@"#F2F3F8"];
        [_textView setMaxSize:NSMakeSize(FLT_MAX, FLT_MAX)];
        _textView.textContainer.maximumNumberOfLines = 0;
        _textView.verticallyResizable = YES;
        _textView.horizontallyResizable = NO;
        [[_textView textContainer] setContainerSize:NSMakeSize(FLT_MAX, FLT_MAX)];
        [[_textView textContainer] setWidthTracksTextView:YES];
        _textView.delegate = self;
    }
    return _textView;
}

- (NSScrollView *)scrollView {
    if (!_scrollView) {
        _scrollView = [[NSScrollView alloc] init];
        _scrollView.borderType = NSNoBorder;
        _scrollView.hasVerticalScroller = YES;
        _scrollView.hasHorizontalScroller = NO;
        _scrollView.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
        
        [_scrollView setBackgroundColorWithHexString:@"#F2F3F8"];
    }
    return _scrollView;
}

- (NSLabel *)placeholderLabel {
    if (!_placeholderLabel) {
        _placeholderLabel = [[NSLabel alloc] init];
        _placeholderLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _placeholderLabel.textColor = [NSColor colorFromHexString:@"#86909C"];
    }
    return _placeholderLabel;
}

- (NSLabel *)numLabel {
    if (!_numLabel) {
        _numLabel = [[NSLabel alloc] init];
        _numLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _numLabel.textColor = [NSColor colorFromHexString:@"#86909C"];
        _numLabel.text = @"0/500";
    }
    return _numLabel;
}

@end
