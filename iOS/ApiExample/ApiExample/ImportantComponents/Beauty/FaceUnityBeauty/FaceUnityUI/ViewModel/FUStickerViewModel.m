//
//  FUStickerViewModel.m
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/6.
//

#import "FUStickerViewModel.h"
#import "FUStickerModel.h"
#import <FURenderKit/FURenderKit.h>

@interface FUStickerViewModel ()

@property (nonatomic, copy) NSArray<FUStickerModel *> *stickers;
/// 当前的贴纸
@property (nonatomic, strong) FUSticker *currentSticker;

@end

@implementation FUStickerViewModel

- (instancetype)init {
    self = [super init];
    if (self) {
        _selectedIndex = 0;
    }
    return self;
}

- (UIImage *)stickerIconAtIndex:(NSUInteger)index {
    FUStickerModel *model = self.stickers[index];
    return [UIImage imageNamed:model.icon];
}

- (void)setSelectedIndex:(NSInteger)selectedIndex {
    if (selectedIndex == 0) {
        [[FURenderKit shareRenderKit].stickerContainer removeAllSticks];
        _selectedIndex = 0;
        return;
    }
    FUStickerModel *model = self.stickers[selectedIndex];
    NSString *path = [[NSBundle mainBundle] pathForResource:model.bundleName ofType:@"bundle"];
    FUSticker *sticker = [[FUSticker alloc] initWithPath:path name:@"sticker"];
    if (self.currentSticker) {
        [[FURenderKit shareRenderKit].stickerContainer replaceSticker:self.currentSticker withSticker:sticker completion:nil];
    } else {
        [[FURenderKit shareRenderKit].stickerContainer addSticker:sticker completion:nil];
    }
    _selectedIndex = selectedIndex;
    self.currentSticker = sticker;
}

- (NSArray<FUStickerModel *> *)stickers {
    if (!_stickers) {
        NSBundle *bundle = [NSBundle bundleForClass:[self class]];
        NSString *path = [bundle pathForResource:@"stickers" ofType:@"json"];
        NSArray<NSDictionary *> *data = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:path] options:NSJSONReadingMutableContainers error:nil];
        NSMutableArray *stickers = [[NSMutableArray alloc] init];
        for (NSDictionary *dictionary in data) {
            FUStickerModel *model = [[FUStickerModel alloc] init];
            [model setValuesForKeysWithDictionary:dictionary];
            [stickers addObject:model];
        }
        _stickers = [stickers copy];
    }
    return _stickers;
}

@end
