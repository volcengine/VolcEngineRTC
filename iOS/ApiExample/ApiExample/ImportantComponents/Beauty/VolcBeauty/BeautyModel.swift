//
//  BeautyModel.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/31.
//  Copyright © 2021 bytedance. All rights reserved.
//

import Foundation

struct BeautyModel {
    static func sectionList() -> [String] {
        return ["美颜",
                "滤镜",
                "贴纸",
                "背景分割"]
    }
    
    static func beautyList() -> [[String: Any]] {
        let dic1: [String: Any] = ["index": 0,
                                   "key": "whiten",
                                   "name": "美白",
                                   "subType": EffectModelSubType.beauty]
        
        let dic2: [String: Any] = ["index": 1,
                                   "key": "smooth",
                                   "name": "磨皮",
                                   "subType": EffectModelSubType.beauty]
        
        let dic3: [String: Any] = ["index": 2,
                                   "key": "Internal_Deform_Eye",
                                   "name": "大眼",
                                   "subType": EffectModelSubType.reshape]
        
        let dic4: [String: Any] = ["index": 3,
                                   "key": "Internal_Deform_Overall",
                                   "name": "瘦脸",
                                   "subType": EffectModelSubType.reshape]
        
        return [dic1, dic2, dic3, dic4]
    }
    
    static func stickerList() -> [[String: Any]] {
        let dic1: [String: Any] = ["index": 0,
                                   "key": "stickers_heimaoyanjing",
                                   "name": "黑猫眼镜"]
        
        let dic2: [String: Any] = ["index": 1,
                                   "key": "stickers_zhaocaimao",
                                   "name": "招财猫"]
        
        let dic3: [String: Any] = ["index": 2,
                                   "key": "stickers_kejiganqueaixiong",
                                   "name": "缺爱熊"]
        
        let dic4: [String: Any] = ["index": 3,
                                   "key": "stickers_mofabaoshi",
                                   "name": "魔法宝石"]
        
        let dic5: [String: Any] = ["index": 4,
                                   "key": "stickers_caihongtu",
                                   "name": "彩虹兔"]
        
        let dic6: [String: Any] = ["index": 5,
                                   "key": "stickers_gongzhumianju",
                                   "name": "公主面具"]
        
        let dic7: [String: Any] = ["index": 6,
                                   "key": "stickers_huahua",
                                   "name": "花花"]
        
        let dic8: [String: Any] = ["index": 7,
                                   "key": "stickers_tiaowuhuoji",
                                   "name": "跳舞火鸡"]
        
        return [dic1, dic2, dic3, dic4, dic5, dic6, dic7, dic8]
    }
    
    static func filterList() -> [[String: Any]] {
        let dic1: [String: Any] = ["index": 0,
                                   "key": "Filter_06_03",
                                   "name": "蜜桃"]
        
        let dic2: [String: Any] = ["index": 1,
                                   "key": "Filter_37_L5",
                                   "name": "清透"]
        
        let dic3: [String: Any] = ["index": 2,
                                   "key": "Filter_35_L3",
                                   "name": "夜色"]
        
        let dic4: [String: Any] = ["index": 3,
                                   "key": "Filter_30_Po8",
                                   "name": "冷氧"]
        
        return [dic1, dic2, dic3, dic4]
    }
    
    static func virtualBackgroundList() -> [[String: Any]] {
        let dic1: [String: Any] = ["index": 0,
                                   "name": "纯色",
                                   "subType": EffectModelSubType.color]
        
        let dic2: [String: Any] = ["index": 1,
                                   "name": "图片",
                                   "subType": EffectModelSubType.image]
        
        return [dic1, dic2]
    }
}
