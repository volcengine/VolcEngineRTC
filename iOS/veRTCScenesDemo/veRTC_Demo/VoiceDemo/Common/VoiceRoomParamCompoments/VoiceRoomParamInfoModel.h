//
//  VoiceRoomParamInfoModel.h
//  veRTC_Demo
//
//  Created by  on 2021/6/2.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VoiceRoomParamInfoModel : NSObject

@property (nonatomic, strong) NSString *numChannels;
@property (nonatomic, strong) NSString *sentSampleRate;
@property (nonatomic, strong) NSString *sentKBitrate;
@property (nonatomic, strong) NSString *audioLossRate;

@property (nonatomic, strong) NSString *recordKBitrate;
@property (nonatomic, strong) NSString *recordLossRate;
@property (nonatomic, strong) NSString *rtt;

@end

NS_ASSUME_NONNULL_END
