#pragma once

#ifdef WIN32
#define BYTEAUDIO_API __declspec(dllexport)
#else
#define BYTEAUDIO_API __attribute__((__visibility__("default")))
#endif

/**
 * Private header file, defines some private stream option key.
 */
namespace bae {
/**
 * @brief Private option key of byteaudio engine.
 * scope: [0 ~ 1000)
 */
enum ByteAudioEnginePrivateOptionKey {
    /**
     * @brief Adjust capture vocal volume in KTV (for engine).
     */
    kEngineOptVocalVolume = 0,

    /**
     * @brief enable local audio with higher priority.
     */
    kEngineOptEnableLocalAudio = 1,

    /**
     * @brief used to get the current audio route (only for ios & android).
     */
    kEngineOptCurrentAudioRoute = 2,

    /**
     * @brief enable/disable hands-free ear monitor. This option does't control headset ear monitor.
     */
    kEngineOptEnableHandsFreeEarMonitor = 3,

    /**
     * @brief whether enable audiosession deactive to avoid the low voice problem in ios14 device, default false.
     *        enable this option will interrupt the audio playback of other processes, such as game audio.
     */
    kEngineOptEnableAudioSessionDeactive = 4,
};

/**
 * @brief Private option key of input/output/aux stream.
 * scope: [1000 ~ 10000)
 */
enum ByteAudioStreamPrivateOptionKey {
    /**
     * @brief Force enable AEC for this stream(for input stream).
     * value_type: bool, default false
     */
    kInputOptEnableAec = 1000,

    /**
     * @brief Force enable AGC for this stream(for input stream).
     * value_type: bool, default false
     */
    kInputOptEnableAgc = 1001,

    /**
     * @brief Force enable ANS for this stream(for input stream).
     * value_type: bool, default false
     */
    kInputOptEnableAns = 1002,

    /**
     * @brief Enable opus dtx encode, used for RealX (for input stream).
     * value_type: bool, default false
     */
    kInputOptOpusUseDTX = 1003,

    /**
     * @brief Enable opus in-band fec, used for RealX (for input stream).
     * value_type: bool, default false
     */
    kInputOptOpusUseInBandFEC = 1004,

    /**
     * @brief Set encode loss rate, used for RealX (for input stream).
     * value_type: int32_t, default 0
     */
    kInputOptEncLossRate = 1005,

    /**
     * @brief get capture audio level, used for RealX (for input stream).
     * value_type: int32_t, [0~32767]
     */
    kInputOptRecordLevel = 1006,

    /**
     * @brief get encode audio level, used for RealX (for input stream).
     * value_type: int32_t, [0~32767]
     */
    kInputOptEncodeLevel = 1007,

    /**
     * @brief Whether lead to a start of audio device (for input stream).
     * value_type: bool, default true
     */
    kInputOptImpactDevice = 1008,

    /**
     * @brief aux stream is effct audio
     * value_type: bool, default false
     */
    kAuxOptEffect = 2000,
    /**
     * @brief stream id
     * value_type: int32_t
     */
    kAuxOptSoundId = 2001,

    /**
     * @brief get plaback audio level, used for RealX (for input stream).
     * value_type: int32_t, [0~32767]
     */
    kOutputOptPlaybackLevel = 3000,

    /**
     * @brief get decode audio level, used for RealX (for input stream).
     * value_type: int32_t, [0~32767]
     */
    kOutputOptDecodeLevel = 3001,
};

BYTEAUDIO_API void set_engine_context(void* env, void* context);
}  // namespace bae
