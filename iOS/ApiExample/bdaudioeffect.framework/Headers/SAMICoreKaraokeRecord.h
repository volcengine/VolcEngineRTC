//
// Created by zhangkg on 2022/7/20.
//

#ifndef SAMI_CORE_KARAOKE_RECORD_H
#define SAMI_CORE_KARAOKE_RECORD_H

#import <Foundation/Foundation.h>
#include "SAMICoreCode.h"
#include "SAMICoreKaraokeDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

@interface SAMICore_KaraokeRecordSettingParam : NSObject
    @property (nonatomic, assign) const char* _Nonnull accompany_path;
    @property (nonatomic, assign) const char* _Nonnull original_path;
    @property (nonatomic, assign) int sample_rate;
    @property (nonatomic, assign) int max_block_samples;
    @property (nonatomic, assign) SAMICore_KaraokeMessageCallBackPtr _Nullable message_callback;
@end

@interface SAMICore_MulDimSingScoringRealtimeInfo : NSObject
    @property (nonatomic, assign) double timeMilliseconds;  // Timestamp (-1, 0~T)
    @property (nonatomic, assign) double songScore;  // Score till the current song position (0~100)
    @property (nonatomic, assign) int sentenceCount; // Sentences' number count

    @property (nonatomic, assign) int sentenceIndex;     // 0-Based Sentence-Index to identify the sentenceScore referring to. (-1, 0~N-1)
    @property (nonatomic, assign) double sentenceScore;  // Score of the last sentence (0~100)

    @property (nonatomic, assign) double userPitch;      // MIDI pitch value of the detected Vocal (-1, 0.0~127.0)
    @property (nonatomic, assign) int userNote;          // MIDI Note value of the detected Vocal (-1, 0~127)
    @property (nonatomic, assign) int userCent;          // MIDI Note Cent of the detected Vocal (-50~+50)
    @property (nonatomic, assign) int userOctave;        // Octave offset of the detected Vocal (-9, +9)

    @property (nonatomic, assign) double refPitch;      // MIDI pitch value of the Reference MIDI (-1, 0.0~127.0)
    @property (nonatomic, assign) int refNote;          // MIDI Note value of the Reference MIDI (-1, 0~127)
    @property (nonatomic, assign) int refCent;          // MIDI Note Cent of the Reference MIDI (-50~+50)
@end

@interface SAMICore_MulDimSingScoringOverallInfo : NSObject
    @property (nonatomic, assign) float rhythm_score;
    @property (nonatomic, assign) float emotion_score;
    @property (nonatomic, assign) float note_score;
@end

typedef NS_ENUM(NSInteger, SAMICore_KaraokeBGMMode) {
    SAMICore_KaraokeBGMMode_Accompany = 0,
    SAMICore_KaraokeBGMMode_Original
};


@interface SAMICoreKaraokeRecord: NSObject

- (int)initRecordingGraphWithSettingParam:(SAMICore_KaraokeRecordSettingParam* _Nonnull)param;
- (int)pushMicAudioData:(float* _Nonnull* _Nonnull)in_data
           num_channels:(int)num_channels
            num_samples:(int)num_samples
            interleaved:(bool)interleaved;
- (int)pullAudioData:(float* _Nonnull* _Nonnull)out_data
         num_samples:(int)num_samples;

- (int)prepare;
- (int)play;
- (int)pause;
- (int)stop;
- (int)seek:(float)seek_to_ms count_down_ms:(float)count_down_ms;
- (int)writeRecordInfoToFile:(const char* _Nonnull)record_result_path;
- (float)getTotalDurationMs;
- (float)getCurrentPositionMs;

- (int)setAECParam:(const char* _Nonnull)aec_model_path;
- (int)setTimeAlignParam:(const char* _Nonnull)time_align_mode_path;
- (int)setOutVocalFileParam:(const char* _Nonnull)vocal_path;
- (int)setSingScoreParam:(int)score_mode
              lyric_path:(const char* _Nonnull)lyric_path
               midi_path:(const char* _Nonnull)midi_path;
- (int)openVocalLoudnessExtractor;

- (int)updateMonitorVocalVolume:(float)value_db;
- (int)updateMonitorBGMVolume:(float)value_db;
- (int)switchBGMMode:(SAMICore_KaraokeBGMMode)mode;
- (int)setUseAEC:(bool)use;

- (int)getLoudnessOverallFeatures:(float* _Nonnull)global_loudness global_peak:(float* _Nonnull)global_peak;
- (int)getTimeAlignResultMs:(float* _Nonnull)delay_ms;
- (int)getRealTimeScoreInfo:(SAMICore_MulDimSingScoringRealtimeInfo* _Nonnull)info;
- (int)getOverallScoreInfo:(SAMICore_MulDimSingScoringOverallInfo* _Nonnull) info;
@end

#ifdef __cplusplus
}   // extern "C"
#endif

#endif  //SAMI_CORE_KARAOKE_RECORD_H