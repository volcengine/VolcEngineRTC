//
// Created by ByteDance on 2023/7/12.
//

#ifndef SAMI_CORE_SAMICOREVOPENGINE_H
#define SAMI_CORE_SAMICOREVOPENGINE_H
#import <Foundation/Foundation.h>
#include "SAMICoreVopDefine.h"
#include "SAMICoreDataType.h"
#ifdef __cplusplus
extern "C" {
#endif

@interface SAMICore_VopInitContext : NSObject
@property (nonatomic, assign) SAMICore_VopLanguage language;
@property (nonatomic, assign) const char* _Nonnull vopServerUrl;
@property (nonatomic, assign) const char* _Nonnull ttsServerUrl;
@property (nonatomic, assign) const char* _Nonnull appKey;
@property (nonatomic, assign) const char* _Nonnull token;
@property (nonatomic, assign) int connection_timeout;
@property (nonatomic, assign) SAMICore_TokenType tokenType;

@property (nonatomic, assign) const char* _Nonnull snrModelPath;
@property (nonatomic, assign) const char* _Nonnull saveFileDir;

@property (nonatomic, assign) float werThreshold;
@property (nonatomic, assign) float snrThreshold;
@property (nonatomic, assign) int werFailedMaxTimes;
@property (nonatomic, assign) float cutoffLength;
@property (nonatomic, assign) int resampleRate;
@property (nonatomic, assign) const char* _Nonnull sampleTextContent;

@property (nonatomic, assign) SAMICore_VopTextType textType;
@property (nonatomic, assign) SAMICore_VopRecordingType recordingType;


@property (nonatomic, assign) int sampleRate;
@property (nonatomic, assign) int channel;
@property (nonatomic, assign) int maxBlockSize;

@property (nonatomic, assign) const char* _Nonnull userId;

@end

@interface SAMICore_VopSpeakerInfo : NSObject
@property (nonatomic, assign) int isPrivate;
@property (nonatomic, assign) NSString* _Nullable speakerId;
@property (nonatomic, assign) unsigned long long finishedTime;
@property (nonatomic, assign) NSString* _Nullable updateTime;
@end

@interface SAMICore_VopTextInfo : NSObject
@property (nonatomic, assign) NSString* _Nullable textJson;
@property (nonatomic, assign) SAMICore_VopTextState textState;
@end

@interface SAMICore_VopRecordingStatus : NSObject
@property (nonatomic, assign) int requiredTextNum;
@property (nonatomic, assign) int successTextNum;
@property (nonatomic, assign) int usedTextNum;
@end


@interface SAMICoreOCVopEngine: NSObject

- (int)init:(SAMICore_VopInitContext* _Nonnull)param;
- (int)getCurrentState:(SAMICore_VopState* _Nonnull)vopState;
- (int)getSpeakerInfo:(SAMICore_VopSpeakerInfo* _Nonnull)speakerInfo;
- (int)getNextTextInfo:(SAMICore_VopTextInfo* _Nonnull)textInfo;
- (int)getRecordingStatus:(SAMICore_VopRecordingStatus* _Nonnull)recordingStatus;
- (int)manageSpeakerInfo:(SAMICore_VopSpeakerInfoCommand)command;
- (int)processRecordAudio:(char* _Nonnull) audioData
                audioLen: (int) audioLen
                  result:(SAMICore_VopProcessRecordAudioResult* _Nonnull)result;
- (int)preparePlayer;
- (void)play;
- (void)stop;
- (float)getTotalDurationMs;
- (float)getCurrentPositionMs;


@end


#ifdef __cplusplus
}   // extern "C"
#endif

#endif  //SAMI_CORE_SAMICOREVOPENGINE_H
