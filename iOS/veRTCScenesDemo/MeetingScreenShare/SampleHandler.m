//
//  SampleHandler.m
//  MeetingScreenShare
//
//  Created by  on 2021/4/6.
//  Copyright © 2021 bytedance. All rights reserved.
//


#import "SampleHandler.h"
#import <ByteRtcEngineKit/ByteRtcScreenCapturerExt.h>

@interface SampleHandler () <ByteRtcScreenCapturerExtDelegate>

@property (nonatomic, strong) ByteRtcScreenCapturerExt *capturer;

@end

@implementation SampleHandler

- (instancetype)init {
    self = [super init];
    if (self) {
        self.capturer = ByteRtcScreenCapturerExt.shared;
    }
    return self;
}

- (void)broadcastStartedWithSetupInfo:(NSDictionary<NSString *,NSObject *> *)setupInfo {
    // User has requested to start the broadcast. Setup info from the UI extension can be supplied but optional.
#ifdef DEBUG
    NSString *groupId = @"group.com.veRTC.screen.rtc";
#else
    NSString *groupId = @"group.rtc.veRTCDemo.ios.meetingScreenShare";
#endif
    [self.capturer startWithDelegate:self groupId:groupId];
}

- (void)broadcastPaused {
    // User has requested to pause the broadcast. Samples will stop being delivered.
}

- (void)broadcastResumed {
    // User has requested to resume the broadcast. Samples delivery will resume.
}

- (void)broadcastFinished {
    // User has requested to finish the broadcast.
    [self.capturer stop];
}

- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType {
    
    switch (sampleBufferType) {
        case RPSampleBufferTypeVideo:
            [self.capturer processSampleBuffer:sampleBuffer withType:sampleBufferType];
            break;
        case RPSampleBufferTypeAudioApp:
            // Handle audio sample buffer for app audio
            break;
        case RPSampleBufferTypeAudioMic:
            // Handle audio sample buffer for mic audio
            break;
            
        default:
            break;
    }
}

#pragma mark - ByteRtcScreenCapturerExtDelegate

- (void)quit {
    [self finishBroadcastWithError:[NSError errorWithDomain:RPRecordingErrorDomain
                                                       code:RPRecordingErrorUserDeclined
                                                   userInfo:@{
                                                       NSLocalizedFailureReasonErrorKey : @"您停止了屏幕共享",
                                                   }]];
}

@end
