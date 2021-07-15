//
//  VoiceControlAckModel.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/17.
//

#import "VoiceControlAckModel.h"

@implementation VoiceControlAckModel

- (BOOL)result {
    if (self.code == 200) {
        return YES;
    } else {
        return NO;
    }
}

@end
