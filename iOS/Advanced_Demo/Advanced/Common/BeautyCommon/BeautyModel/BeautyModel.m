//
//  BeautyModel.m
//  Advanced
//
//

#import "BeautyModel.h"

@implementation BeautyModel

+ (NSArray *)sectionList {
    return @[ @"美颜",
              @"贴纸",
              @"滤镜",
              @"背景分割" ];
}

+ (NSArray *)beautyList {
    NSDictionary *dic1 = @{@"index" : @(0),
                           @"key"   : @"whiten",
                           @"name"  : @"美白",
                           @"type"  : @"beauty",
    };

    NSDictionary *dic2 = @{@"index" : @(1),
                           @"key"   : @"smooth",
                           @"name"  : @"磨皮",
                           @"type"  : @"beauty",
    };
    NSDictionary *dic3 = @{@"index" : @(2),
                           @"key"   : @"Internal_Deform_Eye",
                           @"name"  : @"大眼",
                           @"type"  : @"reshape",
    };
    NSDictionary *dic4 = @{@"index" : @(3),
                           @"key"   : @"Internal_Deform_Overall",
                           @"name"  : @"瘦脸",
                           @"type"  : @"reshape",
    };
    return @[ dic1, dic2, dic3, dic4 ];
}

+ (NSArray *)stickerList {
    NSDictionary *dic1 = @{@"index" : @(0),
                           @"key"   : @"heimaoyanjing",
                           @"name"  : @"黑猫眼镜",
    };
    NSDictionary *dic2 = @{@"index" : @(1),
                           @"key"   : @"zhaocaimao",
                           @"name"  : @"招财猫",
    };
    NSDictionary *dic3 = @{@"index" : @(2),
                           @"key"   : @"kejiganqueaixiong",
                           @"name"  : @"缺爱熊",
    };
    NSDictionary *dic4 = @{@"index" : @(3),
                           @"key"   : @"mofabaoshi",
                           @"name"  : @"魔法宝石",
    };
    NSDictionary *dic5 = @{@"index" : @(4),
                           @"key"   : @"longjuanfeng",
                           @"name"  : @"龙卷风",
    };
    NSDictionary *dic6 = @{@"index" : @(5),
                           @"key"   : @"meihouwang",
                           @"name"  : @"美猴王",
    };
    NSDictionary *dic7 = @{@"index" : @(6),
                           @"key"   : @"manhualian",
                           @"name"  : @"漫画脸",
    };
    return @[ dic1, dic2, dic3, dic4, dic5, dic6, dic7 ];
}

+ (NSArray *)filterList {
    NSDictionary *dic1 = @{@"index" : @(0),
                           @"key"   : @"Filter_06_03",
                           @"name"  : @"蜜桃",
    };
    NSDictionary *dic2 = @{@"index" : @(1),
                           @"key"   : @"Filter_37_L5",
                           @"name"  : @"清透",
    };
    NSDictionary *dic3 = @{@"index" : @(2),
                           @"key"   : @"Filter_35_L3",
                           @"name"  : @"夜色",
    };
    NSDictionary *dic4 = @{@"index" : @(3),
                           @"key"   : @"Filter_30_Po8",
                           @"name"  : @"冷氧",
    };
    return @[ dic1, dic2, dic3, dic4 ];
}

+ (NSArray *)virtualBackgroundList {
    NSDictionary *dic1 = @{@"index" : @(0),
                           @"name"  : @"纯色",
                           @"type"   : @"color",
    };
    NSDictionary *dic2 = @{@"index" : @(1),
                           @"name"  : @"图片",
                           @"type"   : @"image",
    };
    return @[ dic1, dic2 ];
}

@end
