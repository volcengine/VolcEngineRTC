//
//  FUBeautySkinViewModel.m
//  FUDemo
//
//  Created by 项林平 on 2021/6/11.
//

#import "FUBeautySkinViewModel.h"
#import "FUBeautySkinModel.h"

@interface FUBeautySkinViewModel ()

@property (nonatomic, copy) NSArray<FUBeautySkinModel *> *beautySkins;

@end

@implementation FUBeautySkinViewModel

- (instancetype)init {
    self = [super init];
    if (self) {
        self.beautySkins = [self defaultSkins];
        _selectedIndex = -1;
        
        [self setAllSkinValues];
    }
    return self;
}

#pragma mark - Instance methods

- (void)setSkinValue:(double)value {
    if (self.selectedIndex < 0 || self.selectedIndex >= self.beautySkins.count) {
        return;
    }
    FUBeautySkinModel *model = self.beautySkins[self.selectedIndex];
    model.currentValue = value * model.ratio;
    [self setValue:model.currentValue forType:model.type];
}

- (void)setAllSkinValues {
    for (FUBeautySkinModel *skin in self.beautySkins) {
        [self setValue:skin.currentValue forType:skin.type];
    }
}

- (void)recoverAllSkinValuesToDefault {
    for (FUBeautySkinModel *skin in self.beautySkins) {
        skin.currentValue = skin.defaultValue;
        [self setValue:skin.currentValue forType:skin.type];
    }
}

#pragma mark - Private methods

- (void)setValue:(double)value forType:(FUBeautySkin)type {
    switch (type) {
        case FUBeautySkinBlurLevel:
            [FURenderKit shareRenderKit].beauty.blurLevel = value;
            break;
        case FUBeautySkinColorLevel:
            [FURenderKit shareRenderKit].beauty.colorLevel = value;
            break;
        case FUBeautySkinRedLevel:
            [FURenderKit shareRenderKit].beauty.redLevel = value;
            break;
        case FUBeautySkinSharpen:
            [FURenderKit shareRenderKit].beauty.sharpen = value;
            break;
        case FUBeautySkinFaceThreed:
            [FURenderKit shareRenderKit].beauty.faceThreed = value;
            break;
        case FUBeautySkinEyeBright:
            [FURenderKit shareRenderKit].beauty.eyeBright = value;
            break;
        case FUBeautySkinToothWhiten:
            [FURenderKit shareRenderKit].beauty.toothWhiten = value;
            break;
        case FUBeautySkinRemovePouchStrength:
            [FURenderKit shareRenderKit].beauty.removePouchStrength = value;
            break;
        case FUBeautySkinRemoveNasolabialFoldsStrength:
            [FURenderKit shareRenderKit].beauty.removeNasolabialFoldsStrength = value;
            break;
    }
}

#pragma mark - Getters

- (BOOL)isDefaultValue {
    for (FUBeautySkinModel *skin in self.beautySkins) {
        int currentIntValue = skin.defaultValueInMiddle ? (int)(skin.currentValue / skin.ratio * 100 - 50) : (int)(skin.currentValue / skin.ratio * 100);
        int defaultIntValue = skin.defaultValueInMiddle ? (int)(skin.defaultValue / skin.ratio * 100 - 50) : (int)(skin.defaultValue / skin.ratio * 100);
        if (currentIntValue != defaultIntValue) {
            return NO;
        }
    }
    return YES;
}

- (NSArray<FUBeautySkinModel *> *)defaultSkins {
    NSBundle *bundle = [NSBundle bundleForClass:[self class]];
    NSString *skinPath = [bundle pathForResource:@"beauty_skin" ofType:@"json"];
    NSArray<NSDictionary *> *skinData = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:skinPath] options:NSJSONReadingMutableContainers error:nil];
    NSMutableArray *skins = [[NSMutableArray alloc] init];
    for (NSDictionary *dictionary in skinData) {
        FUBeautySkinModel *model = [[FUBeautySkinModel alloc] init];
        [model setValuesForKeysWithDictionary:dictionary];
        [skins addObject:model];
    }
    return [skins copy];
}

@end
