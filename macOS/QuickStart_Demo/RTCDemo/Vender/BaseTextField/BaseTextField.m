//
//  BaseTextField.m
//  veRTC_Demo


#import "BaseTextField.h"

@implementation BaseTextField

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (BOOL)becomeFirstResponder {
    BOOL result = [super becomeFirstResponder];
    _isFirstResponder = YES;
    
    if (self.changeFirstResponder) {
        self.changeFirstResponder(_isFirstResponder);
    }
    return result;
}

- (BOOL)resignFirstResponder {
    BOOL result = [super resignFirstResponder];
    
    return result;
}

- (void)textDidEndEditing:(NSNotification *)notification {
    [super textDidEndEditing:notification];
    
    _isFirstResponder = NO;
    if (self.changeFirstResponder) {
        self.changeFirstResponder(_isFirstResponder);
    }
}

@end
