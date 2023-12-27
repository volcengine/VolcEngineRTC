//
//  FUBeautyFilterViewModel.m
//  FUBeautyComponent
//
//  Created by 项林平 on 2022/7/7.
//

#import "FUBeautyFilterViewModel.h"
#import "FUBeautyFilterModel.h"
#import "FUDefines.h"

#import <FURenderKit/FURenderKit.h>

@interface FUBeautyFilterViewModel ()

@property (nonatomic, copy) NSArray<FUBeautyFilterModel *> *beautyFilters;

@end

@implementation FUBeautyFilterViewModel

#pragma mark - Initializer

- (instancetype)init {
    self = [super init];
    if (self) {
        self.beautyFilters = [self defaultFilters];
        // 默认索引为1
        _selectedIndex = 1;
        [self setCurrentFilter];
    }
    return self;
}

#pragma mark - Instance methods

- (void)setSelectedIndex:(NSInteger)selectedIndex {
    if (selectedIndex < 0 || selectedIndex >= self.beautyFilters.count) {
        return;
    }
    [self setFilter:self.beautyFilters[selectedIndex].filterName level:self.beautyFilters[selectedIndex].filterLevel];
    _selectedIndex = selectedIndex;
}

- (void)setCurrentFilter {
    if (self.selectedIndex < 0 || self.selectedIndex >= self.beautyFilters.count) {
        return;
    }
    [self setFilter:self.beautyFilters[self.selectedIndex].filterName level:self.beautyFilters[self.selectedIndex].filterLevel];
}

- (void)setFilterValue:(double)value {
    if (self.selectedIndex < 0 || self.selectedIndex >= self.beautyFilters.count) {
        return;
    }
    FUBeautyFilterModel *model = self.beautyFilters[self.selectedIndex];
    model.filterLevel = value;
    [FURenderKit shareRenderKit].beauty.filterLevel = model.filterLevel;
}

- (NSString *)filterNameAtIndex:(NSUInteger)index {
    FUBeautyFilterModel *model = self.beautyFilters[index];
    return FULocalizedString(model.filterName);
}

- (UIImage *)filterIconAtIndex:(NSUInteger)index {
    FUBeautyFilterModel *model = self.beautyFilters[index];
    return [UIImage imageNamed:model.filterName];
}

- (double)filterValueAtIndex:(NSUInteger)index {
    FUBeautyFilterModel *model = self.beautyFilters[index];
    return model.filterLevel;
}

#pragma mark - Private methods

- (void)setFilter:(NSString *)filterName level:(double)filterLevel {
    [FURenderKit shareRenderKit].beauty.filterName = filterName;
    [FURenderKit shareRenderKit].beauty.filterLevel = filterLevel;
}

#pragma mark - Getters

- (NSArray<FUBeautyFilterModel *> *)defaultFilters {
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    NSString *filterPath = [bundle pathForResource:@"beauty_filter" ofType:@"json"];
    NSArray<NSDictionary *> *filterData = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:filterPath] options:NSJSONReadingMutableContainers error:nil];
    NSMutableArray *filters = [[NSMutableArray alloc] init];
    for (NSDictionary *dictionary in filterData) {
        FUBeautyFilterModel *model = [[FUBeautyFilterModel alloc] init];
        [model setValuesForKeysWithDictionary:dictionary];
        [filters addObject:model];
    }
    return [filters copy];
}

@end
