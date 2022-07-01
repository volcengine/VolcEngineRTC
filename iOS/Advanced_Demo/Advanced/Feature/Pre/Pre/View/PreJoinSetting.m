//
//  PreJoinSetting.m
//  Advanced
//
//  Created by bytedance on 2021/12/6.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "PreJoinSetting.h"

@implementation PreJoinSetting

- (instancetype)init {
    if (self = [super init]) {
        self.useCustomCapture = NO;
        self.useCustomRender = NO;
        self.localRenderMode = RenderMode_Hidden;
        self.remoteRenderMode = RenderMode_Hidden;
        self.effectsMode = EffectsMode_Volc;
    }
    return self;
}

@end
