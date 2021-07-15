//
//  NSButton+Snippet.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import "NSButton+Snippet.h"

@implementation NSButton (Snippet)

- (instancetype)init {
    self = [super init];
    if (self) {
        self.title = @"";
        self.bezelStyle = NSBezelStyleTexturedSquare;
        self.bordered = NO;
    }
    return self;
}

- (void)setTitleColor:(NSString *)hexString title:(NSString *)title {
    [self setTitleColor:hexString andAlpha:1 * 255 title:title];
}

- (void)setTitleColor:(NSString *)hexString andAlpha:(NSInteger)andAlpha title:(NSString *)title {
    NSColor *color = [NSColor colorFromRGBHexString:hexString andAlpha:andAlpha];
    NSMutableParagraphStyle *btnStyle = [[NSMutableParagraphStyle alloc] init];
    btnStyle.alignment = NSTextAlignmentCenter;
    NSDictionary *dicAtt = @{NSForegroundColorAttributeName : color, NSParagraphStyleAttributeName : btnStyle};
    self.title = title;
    NSMutableAttributedString *attTitle = [[NSMutableAttributedString alloc] initWithAttributedString:self.attributedTitle];

    [attTitle replaceCharactersInRange:NSMakeRange(0, title.length) withString:title];
    [attTitle addAttributes:dicAtt range:NSMakeRange(0, title.length)];

    self.attributedTitle = attTitle;
}

@end
