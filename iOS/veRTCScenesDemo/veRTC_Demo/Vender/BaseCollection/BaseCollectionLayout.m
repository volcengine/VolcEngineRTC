//
//  BaseCollectionLayout.m
//  veRTC_Demo
//
//  Created by  on 2021/5/19.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "BaseCollectionLayout.h"

@implementation BaseCollectionLayout

- (CGFloat)minimumInteritemSpacing {
    return 0;
}

- (UIEdgeInsets)sectionInset{
    return UIEdgeInsetsMake(0, 0, 0, 0);
}

- (NSArray*)layoutAttributesForElementsInRect:(CGRect)rect { 
    NSMutableArray* attributes = [[super layoutAttributesForElementsInRect:rect] mutableCopy];
    
    return attributes;
}

@end
