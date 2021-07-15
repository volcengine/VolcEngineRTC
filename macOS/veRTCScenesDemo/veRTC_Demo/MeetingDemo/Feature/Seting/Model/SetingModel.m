//
//  SetingModel.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/15.
//

#import "SetingModel.h"

@implementation SetingModel

- (instancetype)init {
    self = [super init];
    if (self) {
        self.resolutionSize = NSMakeSize(640, 480);
        self.frameRate = 15;
        self.bitRate = 600;
        self.screenResolutionSize = NSMakeSize(1920, 1080);
        self.screenFrameRate = 15;
        self.screenBitRate = 2000;
        self.isOpenParam = NO;
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeObject:@(self.resolutionSize) forKey:@"resolutionSize"];
    [aCoder encodeFloat:self.frameRate forKey:@"frameRate"];
    [aCoder encodeFloat:self.bitRate forKey:@"bitRate"];
    
    [aCoder encodeObject:@(self.screenResolutionSize) forKey:@"screenResolutionSize"];
    [aCoder encodeFloat:self.screenFrameRate forKey:@"screenFrameRate"];
    [aCoder encodeFloat:self.screenBitRate forKey:@"screenBitRate"];
    
    [aCoder encodeBool:self.isOpenParam forKey:@"isOpenParam"];
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super init]) {
        NSNumber *num = [aDecoder decodeObjectForKey:@"resolutionSize"];
        self.resolutionSize = num.sizeValue;
        self.frameRate = [aDecoder decodeFloatForKey:@"frameRate"];
        self.bitRate = [aDecoder decodeFloatForKey:@"bitRate"];
        
        NSNumber *screenNum = [aDecoder decodeObjectForKey:@"screenResolutionSize"];
        self.screenResolutionSize = screenNum.sizeValue;
        self.screenFrameRate = [aDecoder decodeFloatForKey:@"screenFrameRate"];
        self.screenBitRate = [aDecoder decodeFloatForKey:@"screenBitRate"];
        
        self.isOpenParam = [aDecoder decodeBoolForKey:@"isOpenParam"];
    }
    return self;
}

@end
