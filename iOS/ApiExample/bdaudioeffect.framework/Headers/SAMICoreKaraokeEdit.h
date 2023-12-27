//
// Created by zhangkg on 2022/8/31.
//

#ifndef SAMI_CORE_KARAOKE_EDIT_H
#define SAMI_CORE_KARAOKE_EDIT_H

#import <Foundation/Foundation.h>
#include "SAMICoreCode.h"
#include "SAMICoreDataType.h"
#include "SAMICoreKaraokeDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

@interface SAMICore_KaraokeEditSettingParam : NSObject
@property (nonatomic, assign) const char* _Nonnull vocal_path;
@property (nonatomic, assign) const char* _Nonnull bgm_path;
@property (nonatomic, assign) const char* _Nonnull record_result_path;
@property (nonatomic, assign) int sample_rate;
@property (nonatomic, assign) int max_block_samples;
@property (nonatomic, assign) SAMICore_KaraokeMessageCallBackPtr _Nullable message_callback;
@end

@interface SAMICore_LoudnormProperty : NSObject
@property (nonatomic, assign) float source_lufs;
@property (nonatomic, assign) float source_peak;
@property (nonatomic, assign) float target_lufs;
@end

@interface SAMICore_ByteTunerContextCreateParameter : NSObject
@property (nonatomic, assign) const char* _Nonnull url;
@property (nonatomic, assign) const char* _Nonnull appKey;
@property (nonatomic, assign) SAMICore_TokenType tokenType;
@property (nonatomic, assign) const char* _Nonnull token;

@property (nonatomic, assign) const char* _Nonnull format;
@property (nonatomic, assign) int sampleRate;
@property (nonatomic, assign) int channel;
@property (nonatomic, assign) float shiftSecond;
@property (nonatomic, assign) int shiftSemitone;
@property (nonatomic, assign) float lag;
@property (nonatomic, assign) long timestamp;
@property (nonatomic, assign) const char* _Nonnull midiPath;
@property (nonatomic, assign) const char* _Nonnull vocalPath;
@property (nonatomic, assign) const char* _Nonnull tunedPath;
@end

@interface SAMICoreKaraokeEdit: NSObject

- (int)initEditGraphWithSettingParam:(SAMICore_KaraokeEditSettingParam* _Nonnull)param;
- (int)pullAudioData:(float* _Nonnull* _Nonnull)out_data
         num_samples:(int)num_samples;

- (int)prepare;
- (int)play;
- (int)pause;
- (int)stop;
- (int)seek:(float)time_ms;

// export audio file
-(int)exportAudioDataToAudioFile:(const char* _Nonnull)result_file_path
                   WithStartTime:(float)start_time_ms
                         EndTime:(float)end_time_ms;

// get duration, should be called after init
-(float)getTotalDurationMs;
// get play progress, should be called after init
-(float)getCurrentPositionMs;

// denoise
- (int)setDenoiseModelPath:(const char* _Nonnull)denoise_model_path;
- (int)setUseDenoise:(bool)use_denoise;

// loudness
- (int)setBGMLoudnormInfo:(SAMICore_LoudnormProperty* _Nonnull)bgm_loudness;
- (int)setVocalLoudnormInfo:(SAMICore_LoudnormProperty* _Nonnull)vocal_loudness;

// set/update effect
- (int)updateEffectFilePath:(const char* _Nonnull)effect_path;
- (int)setUseEffect:(bool)use_effect;

// byteTuner
- (int)setByteTunerParam:(SAMICore_ByteTunerContextCreateParameter* _Nonnull)parameter;
- (int)getByteTunerStatus; // Status: ErrorOccurred = -1, unInitialize = 0, Processing = 1, Succeed = 2
- (int)setUseByteTuner:(bool)use_byteTuner;

// volume
- (int)updateVocalVolume:(float)value_db;
- (int)updateBGMVolume:(float)value_db;

// vocal and bgm offset
- (int)setVocalOffsetMs:(float)vocal_offset_ms;
@end

#ifdef __cplusplus
}   // extern "C"
#endif
#endif  //SAMI_CORE_KARAOKE_EDIT_H