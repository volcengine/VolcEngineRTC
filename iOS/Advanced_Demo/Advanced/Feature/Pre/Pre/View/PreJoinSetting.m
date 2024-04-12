//
//  PreJoinSetting.m
//  Advanced
//
//

#import "PreJoinSetting.h"

@implementation PreJoinSetting

- (instancetype)init {
    if (self = [super init]) {
        self.useCustomCapture = NO;
        self.useCustomRender = NO;
        self.localRenderMode = RenderMode_Hidden;
        self.remoteRenderMode = RenderMode_Hidden;
    }
    return self;
}

@end
