//
//  FUBodyViewModel.m
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/7.
//

#import "FUBodyViewModel.h"
#import "FUBodyModel.h"

@interface FUBodyViewModel ()

@property (nonatomic, copy) NSArray<FUBodyModel *> *bodies;

@end

@implementation FUBodyViewModel

- (instancetype)init {
    self = [super init];
    if (self) {
        self.bodies = [self defaultBodies];
        _selectedIndex = -1;
    }
    return self;
}

#pragma mark - Instance methods

- (void)setBodyValue:(double)value {
    if (self.selectedIndex < 0 || self.selectedIndex >= self.bodies.count) {
        return;
    }
    FUBodyModel *model = self.bodies[self.selectedIndex];
    model.currentValue = value;
    [self setValue:model.currentValue forType:model.type];
}

- (void)setAllBodyValues {
    for (FUBodyModel *body in self.bodies) {
        [self setValue:body.currentValue forType:body.type];
    }
}

- (void)recoverAllBodyValuesToDefault {
    for (FUBodyModel *body in self.bodies) {
        body.currentValue = body.defaultValue;
        [self setValue:body.currentValue forType:body.type];
    }
}

- (double)currentValueAtIndex:(NSUInteger)index {
    return self.bodies[index].currentValue;
}

- (double)defaultValueAtIndex:(NSUInteger)index {
    return self.bodies[index].defaultValue;
}

- (BOOL)defaultValueInMiddleAtIndex:(NSUInteger)index {
    return self.bodies[index].defaultValueInMiddle;
}

- (NSString *)nameAtIndex:(NSUInteger)index {
    return self.bodies[index].name;
}

- (UIImage *)iconAtIndex:(NSUInteger)index {
    return [UIImage imageNamed:self.bodies[index].name];
}

#pragma mark - Private methods

- (void)setValue:(double)value forType:(FUBeautyBodyItem)type {
    switch (type) {
        case FUBeautyBodyItemSlim:
            [FURenderKit shareRenderKit].bodyBeauty.bodySlimStrength = value;
            break;
        case FUBeautyBodyItemLongLeg:
            [FURenderKit shareRenderKit].bodyBeauty.legSlimStrength = value;
            break;
        case FUBeautyBodyItemThinWaist:
            [FURenderKit shareRenderKit].bodyBeauty.waistSlimStrength = value;
            break;
        case FUBeautyBodyItemBeautyShoulder:
            [FURenderKit shareRenderKit].bodyBeauty.shoulderSlimStrength = value;
            break;
        case FUBeautyBodyItemBeautyButtock:
            [FURenderKit shareRenderKit].bodyBeauty.hipSlimStrength = value;
            break;
        case FUBeautyBodyItemSmallHead:
            [FURenderKit shareRenderKit].bodyBeauty.headSlim = value;
            break;
        case FUBeautyBodyItemThinLeg:
            [FURenderKit shareRenderKit].bodyBeauty.legSlim = value;
            break;
    }
}

#pragma mark - Getters

- (BOOL)isDefaultValue {
    for (FUBodyModel *body in self.bodies) {
        int currentIntValue = body.defaultValueInMiddle ? (int)(body.currentValue * 100 - 50) : (int)(body.currentValue * 100);
        int defaultIntValue = body.defaultValueInMiddle ? (int)(body.defaultValue * 100 - 50) : (int)(body.defaultValue * 100);
        if (currentIntValue != defaultIntValue) {
            return NO;
        }
    }
    return YES;
}

- (NSArray<FUBodyModel *> *)defaultBodies {
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    NSString *path = [bundle pathForResource:@"body" ofType:@"json"];
    NSArray<NSDictionary *> *bodyData = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:path] options:NSJSONReadingMutableContainers error:nil];
    NSMutableArray *bodies = [[NSMutableArray alloc] init];
    for (NSDictionary *dictionary in bodyData) {
        FUBodyModel *model = [[FUBodyModel alloc] init];
        [model setValuesForKeysWithDictionary:dictionary];
        [bodies addObject:model];
    }
    return [bodies copy];
}

@end
