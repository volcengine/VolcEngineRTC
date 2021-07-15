//
//  MeetingMockDataCompoments.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/15.
//

#import "MeetingMockDataCompoments.h"

@implementation MeetingMockDataCompoments
@synthesize resolutionData = _resolutionData;
@synthesize framerateData = _framerateData;
@synthesize micInputDeviceData = _micInputDeviceData;
@synthesize micOutputDeviceData = _micOutputDeviceData;
@synthesize cameraDeviceData = _cameraDeviceData;
@synthesize screenResolutionData = _screenResolutionData;
@synthesize screenFramerateData = _screenFramerateData;


+ (MeetingMockDataCompoments *)sharedInstance {
    static dispatch_once_t onceToken ;
    static MeetingMockDataCompoments *instance = nil;
    dispatch_once(&onceToken, ^{
        instance = [[self alloc] init];
    });
    return instance;
}

- (NSArray *)resolutionData {
    if (!_resolutionData) {
        _resolutionData = [NSMutableArray new];
        _resolutionData = @[
            @{@"w": @(160), @"h" : @(160), @"minBitRate" : @(40), @"maxBitRate" : @(150)},
            @{@"w": @(320), @"h" : @(180), @"minBitRate" : @(80), @"maxBitRate" : @(350)},
            @{@"w": @(320), @"h" : @(240), @"minBitRate" : @(100), @"maxBitRate" : @(400)},
            @{@"w": @(640), @"h" : @(360), @"minBitRate" : @(200), @"maxBitRate" : @(1000)},
            @{@"w": @(480), @"h" : @(480), @"minBitRate" : @(200), @"maxBitRate" : @(1000)},
            @{@"w": @(640), @"h" : @(480), @"minBitRate" : @(250), @"maxBitRate" : @(1000)},
            @{@"w": @(960), @"h" : @(540), @"minBitRate" : @(400), @"maxBitRate" : @(1600)},
            @{@"w": @(1280), @"h" : @(720), @"minBitRate" : @(500), @"maxBitRate" : @(2000)},
            @{@"w": @(1920), @"h" : @(1080), @"minBitRate" : @(800), @"maxBitRate" : @(3000)},
        ];
    }
    return _resolutionData;
}

- (NSArray *)framerateData {
    if (!_framerateData) {
         _framerateData = [NSMutableArray new];
         _framerateData = @[
             @"15 fps",
             @"20 fps",
             @"24 fps",
         ];
     }
    return _framerateData;
}

- (NSArray *)screenResolutionData {
    if (!_screenResolutionData) {
        _screenResolutionData = [NSMutableArray new];
        _screenResolutionData = @[
            @{@"w": @(160), @"h" : @(160), @"minBitRate" : @(40), @"maxBitRate" : @(150)},
            @{@"w": @(320), @"h" : @(180), @"minBitRate" : @(80), @"maxBitRate" : @(350)},
            @{@"w": @(320), @"h" : @(240), @"minBitRate" : @(100), @"maxBitRate" : @(400)},
            @{@"w": @(640), @"h" : @(360), @"minBitRate" : @(200), @"maxBitRate" : @(1000)},
            @{@"w": @(480), @"h" : @(480), @"minBitRate" : @(200), @"maxBitRate" : @(1000)},
            @{@"w": @(640), @"h" : @(480), @"minBitRate" : @(250), @"maxBitRate" : @(1000)},
            @{@"w": @(960), @"h" : @(540), @"minBitRate" : @(400), @"maxBitRate" : @(1600)},
            @{@"w": @(1280), @"h" : @(720), @"minBitRate" : @(500), @"maxBitRate" : @(2000)},
            @{@"w": @(1920), @"h" : @(1080), @"minBitRate" : @(800), @"maxBitRate" : @(3000)},
        ];
    }
    return _screenResolutionData;
}

- (NSArray *)screenFramerateData {
    if (!_screenFramerateData) {
        _screenFramerateData = [NSMutableArray new];
        _screenFramerateData = @[
             @"15 fps",
             @"20 fps",
             @"24 fps",
         ];
     }
    return _screenFramerateData;
}

- (NSArray *)micInputDeviceData {
    if (!_micInputDeviceData) {
        _micInputDeviceData = [NSMutableArray new];
    }
    return _micInputDeviceData;
}

- (NSArray *)micOutputDeviceData {
    if (!_micOutputDeviceData) {
        _micOutputDeviceData = [NSMutableArray new];
    }
    return _micOutputDeviceData;
}

- (NSArray *)cameraDeviceData {
    if (!_cameraDeviceData) {
        _cameraDeviceData = [NSMutableArray new];
    }
    return _cameraDeviceData;
}

@end
