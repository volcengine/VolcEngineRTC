//
//  BaseSilder.m
//  veRTC_Demo
//
//  Created by  on 2021/6/8.
//

#import "BaseSilder.h"
#import "BaseSilderCell.h"

@implementation BaseSilder

- (instancetype)init {
    self = [super init];
    if (self) {
        if(![self.cell isKindOfClass:[BaseSilderCell class]]) {
            self.cell = [[BaseSilderCell alloc] init];
        }
    }
    return self;
}

@end
