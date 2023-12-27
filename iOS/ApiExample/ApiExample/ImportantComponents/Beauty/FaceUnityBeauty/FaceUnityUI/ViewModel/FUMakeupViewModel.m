//
//  FUMakeupViewModel.m
//  FUDemo
//
//  Created by 项林平 on 2021/6/15.
//

#import "FUMakeupViewModel.h"
#import "FUMakeupModel.h"
#import "FUDefines.h"

#import <FURenderKit/FURenderKit.h>

@interface FUMakeupViewModel ()

@property (nonatomic, copy) NSArray<FUMakeupModel *> *combinationMakeups;

@property (nonatomic, assign) NSInteger selectedIndex;

@end

@implementation FUMakeupViewModel

- (instancetype)init {
    self = [super init];
    if (self) {
        _selectedIndex = 0;
    }
    return self;
}

- (void)selectCombinationMakeupAtIndex:(NSInteger)index {
    if (index == 0) {
        // 卸妆
        [FURenderKit shareRenderKit].makeup = nil;
        self.selectedIndex = 0;
        return;
    }
    self.selectedIndex = index;
    NSString *path = [[NSBundle mainBundle] pathForResource:@"face_makeup" ofType:@"bundle"];
    if (![FURenderKit shareRenderKit].makeup) {
        FUMakeup *makeup = [[FUMakeup alloc] initWithPath:path name:@"makeup"];
        // 高端机打开全脸分割
        makeup.makeupSegmentation = [FURenderKit devicePerformanceLevel] == FUDevicePerformanceLevelHigh;
        [FURenderKit shareRenderKit].makeup = makeup;
    }
    FUMakeupModel *model = self.combinationMakeups[index];
    NSString *bundlePath = [[NSBundle mainBundle] pathForResource:model.bundleName ofType:@"bundle"];
    FUItem *item = [[FUItem alloc] initWithPath:bundlePath name:model.bundleName];
    [[FURenderKit shareRenderKit].makeup updateMakeupPackage:item needCleanSubItem:NO];
    [FURenderKit shareRenderKit].makeup.intensity = model.value;
}

- (NSString *)combinationMakeupNameAtIndex:(NSUInteger)index {
    FUMakeupModel *model = self.combinationMakeups[index];
    return FULocalizedString(model.name);
}

- (UIImage *)combinationMakeupIconAtIndex:(NSUInteger)index {
    FUMakeupModel *model = self.combinationMakeups[index];
    return [UIImage imageNamed:model.icon];
}


#pragma mark - Setters

- (void)setSelectedMakeupValue:(double)selectedMakeupValue {
    if (self.selectedIndex < 0 || self.selectedIndex >= self.combinationMakeups.count) {
        return;
    }
    FUMakeupModel *model = self.combinationMakeups[self.selectedIndex];
    model.value = selectedMakeupValue;
    [FURenderKit shareRenderKit].makeup.intensity = model.value;
}

#pragma mark - Getters

- (NSArray<FUMakeupModel *> *)combinationMakeups {
    if (!_combinationMakeups) {
        NSBundle *bundle = [NSBundle bundleForClass:[self class]];
        NSString *path = [bundle pathForResource:@"combination_makeups" ofType:@"json"];
        NSArray<NSDictionary *> *data = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:path] options:NSJSONReadingMutableContainers error:nil];
        NSMutableArray *makeups = [[NSMutableArray alloc] init];
        for (NSDictionary *dictionary in data) {
            FUMakeupModel *model = [[FUMakeupModel alloc] init];
            [model setValuesForKeysWithDictionary:dictionary];
            [makeups addObject:model];
        }
        _combinationMakeups = [makeups copy];
    }
    return _combinationMakeups;
}

- (double)selectedMakeupValue {
    return self.combinationMakeups[self.selectedIndex].value;
}


@end
