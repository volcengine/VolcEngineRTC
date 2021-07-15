//
//  BaseSilderCell.m
//  veRTC_Demo
//
//  Created by  on 2021/6/8.
//

#import "BaseSilderCell.h"
#import "BaseSilder.h"

#define SLIDER_DEFAUT_HEIGHT               3.0
#define SLIDER_DEFAUT_BAR_RADIUS           1.5
#define SLIDER_DEFAUT_KNOB_WIDTH           12.0
#define SLIDER_DEFAUT_KNOB_HEIGHT          12.0

@interface BaseSilderCell ()

@property (nonatomic, strong) IBInspectable NSColor *sliderProgressColor;
@property (nonatomic, strong) IBInspectable NSColor *sliderBackgroundColor;
@property (nonatomic, assign) IBInspectable CGFloat sliderHeight;
@property (nonatomic, assign) IBInspectable CGFloat sliderBarRadius;
@property (nonatomic, assign) IBInspectable CGFloat sliderKnobWidth;
@property (nonatomic, assign) IBInspectable CGFloat sliderKnobHeight;

@end

@implementation BaseSilderCell

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.sliderProgressColor = [NSColor colorFromHexString:@"#1664FF"];
        self.sliderBackgroundColor = [NSColor colorFromHexString:@"#E5E8EF"];
        self.sliderHeight = SLIDER_DEFAUT_HEIGHT;
        self.sliderBarRadius = SLIDER_DEFAUT_BAR_RADIUS;
        self.sliderKnobWidth = SLIDER_DEFAUT_KNOB_WIDTH;
        self.sliderKnobHeight = SLIDER_DEFAUT_KNOB_HEIGHT;
    }
    return self;
}


- (void)drawBarInside:(NSRect)rect flipped:(BOOL)flipped {
    rect.size.height = self.sliderHeight;
    // Bar radius
    CGFloat barRadius = self.sliderBarRadius;
    // Knob position depending on control min/max value and current control value.
    CGFloat value = ([self doubleValue]  - [self minValue]) / ([self maxValue] - [self minValue]);
    // Final Left Part Width
    CGFloat finalWidth = value * ([[self controlView] frame].size.width - self.sliderKnobWidth);
    
    // Left Part Rect
    NSRect leftRect = rect;
    leftRect.size.width = finalWidth;
    
    // Draw Left Part
    NSBezierPath* bg = [NSBezierPath bezierPathWithRoundedRect: rect xRadius: barRadius yRadius: barRadius];
    [self.sliderBackgroundColor setFill];
    [bg fill];
    
    // Draw Right Part
    NSBezierPath* active = [NSBezierPath bezierPathWithRoundedRect: leftRect xRadius: barRadius yRadius: barRadius];
    [self.sliderProgressColor setFill];
    [active fill];
}

@end
