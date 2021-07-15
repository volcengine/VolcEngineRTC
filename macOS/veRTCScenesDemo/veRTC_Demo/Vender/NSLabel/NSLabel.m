//
//  NSLabel.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import "NSLabel.h"

@implementation NSLabel

- (instancetype)init {
    self = [super init];
    if (self) {
        self.editable = NO;
        self.bezeled = NO;
        self.drawsBackground = NO;
        self.selectable = YES;
    }
    return self;
}

- (void)setText:(NSString *)text {
    if (text == nil) {
        text = @"";
    }
    _text = text;
    self.stringValue = text;
}

- (void)setOneLine:(BOOL)oneLine {
    _oneLine = oneLine;
    if (oneLine) {
        [self.cell setLineBreakMode:NSLineBreakByCharWrapping];
        [self.cell setTruncatesLastVisibleLine:YES];
    } else {
        [self.cell setLineBreakMode:NSLineBreakByWordWrapping];
        [self.cell setTruncatesLastVisibleLine:NO];
    }
}

- (void)setLineSpacing:(CGFloat)lineSpacing{
    _lineSpacing = lineSpacing;
    NSString *text = self.text ? self.text : self.stringValue;
    if (!text) {
        return;
    }
    NSMutableParagraphStyle *textParagraph = [[NSMutableParagraphStyle alloc] init];
    [textParagraph setLineSpacing:lineSpacing];
    NSDictionary *attrDic = [NSDictionary dictionaryWithObjectsAndKeys:textParagraph,NSParagraphStyleAttributeName,nil];
    NSAttributedString *attrString = [[NSAttributedString alloc] initWithString:text attributes:attrDic];
    [self setAttributedStringValue:attrString];
}

@end
