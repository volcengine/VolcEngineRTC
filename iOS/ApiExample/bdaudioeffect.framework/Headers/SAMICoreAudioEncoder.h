//
// Created by CHENZEMIN on 2022/7/8.
//

#ifndef SAMI_CORE_OC_MEAUDIOENCODER_H
#define SAMI_CORE_OC_MEAUDIOENCODER_H

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Audio encoder format
 *
 * You can pass different build option to select implementations.
 *
 * - USE_FFMPEG, ffmpeg implementation
 * - USE_TTFFMPEG, ttffmpeg implementation(only available on Android)
 * - USE_CORE_AUDIO, CoreAudio implementation(only available on macos/iOS)
 * - USE_3RDPARTY, lame implementation for mp3, fkd-aac for aac, dr_wav for wav
 *
 * By default, cmake/mammon_audio_io_options.cmake will selects the most appropriate implementation on different
 * platform:
 *
 * +----------------------------------------------------------------------+
 * |             Default Implementation on Different Platforms            |
 * +---------------+----------------+-------------------------------------+
 * |               |                |              Platforms              |
 * |               |                +---------+---------+-------+---------+
 * |               |                | Mac/iOS | Android | Linux | Windows |
 * +---------------+----------------+---------+---------+-------+---------+
 * |               | USE_FFMPEG     |         |         | ▲     |         |
 * |               +----------------+---------+---------+-------+---------+
 * |               | USE_TTFFMPEG   |         | ▲       |       |         |
 * | Build Options +----------------+---------+---------+-------+---------+
 * |               | USE_CORE_AUDIO | ▲       |         |       |         |
 * |               +----------------+---------+---------+-------+---------+
 * |               | USE_3RDPARTY   |         |         |       | ▲       |
 * +---------------+----------------+---------+---------+-------+---------+
 *
 *
 * Different implementation supports different encoding format, the following tables summarizes the available
 * implementation:
 *
 * +------------------------------+------------------------------------------------------------------------------------+
 * |                              |                                   Encoder Formats                                  |
 * |                              +-----+----------+----------+---------+---------+---------+--------+--------+--------+
 * |                              | mp3 | aiff_s16 | aiff_s24 | wav_s16 | wav_s24 | wav_f32 | aac_lc | aac_ld | aac_he |
 * +-----------------+------------+-----+----------+----------+---------+---------+---------+--------+--------+--------+
 * |                 | core audio | ✖   | √        | √        | √       | √       | √       | √      | √      | √      |
 * |                 +------------+-----+----------+----------+---------+---------+---------+--------+--------+--------+
 * |                 | ffmpeg     | √   | √        | √        | √       | √       | √       | √      | √      | √      |
 * | Implementations +------------+-----+----------+----------+---------+---------+---------+--------+--------+--------+
 * |                 | ttffmpeg   | √   | ✖        | ✖        | √       | √       | √       | √      | ✖      | ✖      |
 * |                 +------------+-----+----------+----------+---------+---------+---------+--------+--------+--------+
 * |                 | 3rd party  | √   | ✖        | ✖        | √       | √       | √       | √      | ✖      | ✖      |
 * +-----------------+------------+-----+----------+----------+---------+---------+---------+--------+--------+--------+
 *
 *
 */
typedef NS_ENUM(NSInteger, SAMICore_AudioEncoderFormat) {
    kNone = 0,
    kMp3,       // not supported in ttffmpeg(D android)
    kAiff_S16,  // not supported in ttffmpeg(D android)
    kAiff_S24,  // not supported in ttffmpeg(D android)
    kWav_S16,
    kWav_S24,  // not supported in ttffmpeg(D android)
    kWav_F32,  // not supported in ttffmpeg(D android)
    kFLAC_F32,
    kAAC_LC,
    kAAC_LD,
    kAAC_HE
};

/**
 * Encoder acceleration option.
 *
 * kHardware_Acceleration, hardware encoding acceleration is currently only available on Android
 *
 */
typedef NS_ENUM(NSInteger, SAMICore_AudioEncoderAcceleration) {
    kSoftware,
    kHardware_Acceleration
};

/**
 * Encoder thread option.
 *
 * kMultiThreaded is currently only available on aac format
 *
 * +-----------------+------------------------------------------------------------------------------------+
 * |                 |                                   Encoder Formats                                  |
 * |                 +-----+----------+----------+---------+---------+---------+--------+--------+--------+
 * |                 | mp3 | aiff_s16 | aiff_s24 | wav_s16 | wav_s24 | wav_f32 | aac_lc | aac_ld | aac_he |
 * +-----------------+-----+----------+----------+---------+---------+---------+--------+--------+--------+
 * | kSingleThreaded | √   | √        | √        | √       | √       | √       | √      | √      | √      |
 * +-----------------+-----+----------+----------+---------+---------+---------+--------+--------+--------+
 * | kMultiThreaded  |     |          |          |         |         |         | √      | √      | √      |
 * +-----------------+-----+----------+----------+---------+---------+---------+--------+--------+--------+
 *
 *
 */
typedef NS_ENUM(NSInteger, SAMICore_AudioEncoderThreading) {
    kSingleThreaded,
    kMultiThreaded
};

/**
 * Settings for creating audio encoder
 * @see AudioEncoderFormat
 * @see AudioEncoderAcceleration
 * @see AudioEncoderThreading
 *
 * if num_threads <= 0, it will use std::hardware_concurrency() as default.
 *
 */
@interface SAMICore_AudioEncoderSettings: NSObject
@property (nonatomic, assign) SAMICore_AudioEncoderFormat format;
@property (nonatomic, assign) SAMICore_AudioEncoderAcceleration acc;
@property (nonatomic, assign) SAMICore_AudioEncoderThreading threading;
@property (nonatomic, assign) int num_threads;

- (_Nullable id) init;
- (_Nullable id) initWithAudioEncoderFormat:(SAMICore_AudioEncoderFormat)format_
                  AudioEncoderAcceleration:(SAMICore_AudioEncoderAcceleration)acc_
                     AudioEncoderThreading:(SAMICore_AudioEncoderThreading)threading_
                                NumThreads:(int)num_threads_;
@end

@interface SAMICore_AudioEncoder: NSObject

/**
     * create audio encoder according to the setting
     *
     * returns nullptr if unsupported
     *
     * @see AudioEncoderSettings
     */
- (_Nullable id)createWithAudioEncoderSettings:(SAMICore_AudioEncoderSettings* _Nonnull)settings;

/**
     * open file to write
     * @param output_path, the save path
     * @param sample_rate, sample rate of the output file
     * @param num_channels, number of channels of the output file
     * @param bit_rate, bit rate of the output file
     * @return 0 if successfully, -1 if failed
     */
- (int)openWithOutputPath:(NSString* _Nonnull)output_path
               SampleRate:(int)sample_rate
               NumChannels:(int)num_channels
                   BitRate:(int)bit_rate;


/**
     * write planar audio data to file
     * @return 1. number of frames actually written if you use kSingleThreaded
     *         2. number of bytes written to output if you use kMultiThreaded,
     *            maybe 0 because the worker which in other thread not finished encoding.
     */
- (int64_t) writePlanarData:(void* _Nonnull) planar_data
                  NumChannels:(int)num_channels
          NumSamplePerChannel:(int64_t)num_sample_per_channel;

/**
     * write interleave audio data to file
     * @return 1. number of frames actually written if use kSingleThreaded
     *         2. number of bytes written to output if use kMultiThreaded,
     *            maybe 0 because the worker which in other thread not finished encoding.
     */
- (int64_t) writeInterleaveData:(void* _Nonnull)interleave_data
                      NumChannels:(int)num_channels
             NumSamplePerChannel:(int64_t)num_sample_per_channel;

/**
     * close file to end the write process.
     *
     * flush will be called in this function.
     */
- (void)close;

/**
     * flush the remaining data to file
     */
- (void)flush;

/**
     * returns sample rate of output file, if open failed will return 0
     */
- (int)getSampleRate;

/**
     * returns number of channels of output file, if open failed will return 0
     */
- (int)getNumChannels;

/**
     * returns true if opened, others returns false
     */
- (bool)isOpen;


@end

#ifdef __cplusplus
}   // extern "C"
#endif

#endif  //SAMI_CORE_OC_MEAUDIOENCODER_H
