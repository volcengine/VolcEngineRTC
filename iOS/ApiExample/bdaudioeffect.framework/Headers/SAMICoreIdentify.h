//
// Created by LIJING on 2021/11/22.
//

#ifndef SAMI_CORE_SAMICOREIDENTIFYENUM_H
#define SAMI_CORE_SAMICOREIDENTIFYENUM_H

typedef NS_ENUM(NSInteger, SAMICore_Identify) {
    /**
     * SAMICore_Identify_Processor_ContextWithString, used to create vocal preset from json string.
     * create handle with SAMICoreContextCreateParameter
     *
     * @see SAMICoreContextCreateParameter
     */
    SAMICore_Identify_Processor_ContextWithString = 0,

    /**
     * SAMICore_Identify_Processor_ContextWithFileName, used to create vocal preset from json file path.
     * create handle with SAMICoreContextCreateParameter
     *
     * @see SAMICoreContextCreateParameter
     */
    SAMICore_Identify_Processor_ContextWithFileName,

    /**
     * SAMICore_Identify_Processor, used to create processor by name,here is an example:
     * @code
     *  SAMICoreHandle handle;
     *  const char* name = "Gain";
     *  int ret = SAMICoreCreateHandleByIdentify(&handle, SAMICore_Identify_Processor, name);
     *  assert(ret == SAMI_OK);
     * @endcode
     *
     * or, you can create processor by enum id, like this:
     * @code
     * int ret = SAMICoreCreateHandleByIdentify(&handle, SAMICore_Identify_Processor_Compressor, NULL);
     * @endcode
     *
     * the currently supported processors' name are match to processor id,
     * here is a table shows the mapping between IDs and names
     *
     * +---------------------------------------+--------------+
     * | Id                                    | Name         |
     * +---------------------------------------+--------------+
     * | SAMICore_Identify_Processor_Gain       | "Gain"       |
     * +---------------------------------------+--------------+
     * | SAMICore_Identify_Processor_Compressor | "Compressor" |
     * +---------------------------------------+--------------+
     *
     *
     */
    SAMICore_Identify_Processor = 100,

    /**
     * Name: "Gain"
     * Parameters:
     * +---------+-------------+-----------+-------------+------------+
     * | index   | name        | type      | range       | default    |
     * +---------+-------------+-----------+-------------+------------+
     * | 0       | "Gain dB"   | "Float"   | [-70, 35]   | 0          |
     * +---------+-------------+-----------+-------------+------------+
     */
    SAMICore_Identify_Processor_Gain,

    /**
     * Name: "Compressor"
     * Parameters:
     * +---------+----------------------+-----------+-----------------+------------+
     *  | index   | name                 | type      | range           | default    |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 0       | "Bypass"             | "Bool"    | [false, true]   | false      |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 1       | "Ratio"              | "Float"   | [1, 40]         | 1          |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 2       | "Threshold dB"       | "Float"   | [-70, 0]        | 0          |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 3       | "Knee dB"            | "Float"   | [0, 18]         | 6          |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 4       | "Attack"             | "Float"   | [0.005, 250]    | 0.25       |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 5       | "Release"            | "Float"   | [1, 2500]       | 100        |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 6       | "Auto Makeup Gain"   | "Bool"    | [false, true]   | true       |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 7       | "Output Gain dB"     | "Float"   | [-35, 35]       | 0          |
     *  +---------+----------------------+-----------+-----------------+------------+
     *  | 8       | "Lookahead"          | "Float"   | [0, 10]         | 0          |
     *  +---------+----------------------+-----------+-----------------+------------+
     */
    SAMICore_Identify_Processor_Compressor,

    /**
     * Name: "Chorus"
     * Parameters:
     * +---------+-------------------------+-----------+-----------------+------------+
     * | index   | name                    | type      | range           | default    |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 0       | "Bypass"                | "Bool"    | [false, true]   | false      |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 1       | "Delay"                 | "Float"   | [0.5, 20]       | 4          |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 2       | "Rate"                  | "Float"   | [0, 4]          | 1          |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 3       | "Depth"                 | "Float"   | [0, 5]          | 2          |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 4       | "Stereo Phase Offset"   | "Float"   | [0, 1]          | 1          |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 5       | "Feedback"              | "Float"   | [0, 0.96]       | 0          |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 6       | "Wetness"               | "Float"   | [0, 1]          | 1          |
     * +---------+-------------------------+-----------+-----------------+------------+
     */
    SAMICore_Identify_Processor_Chorus,

    /**
     * Name: "Distortion"
     * Parameters:
     * +---------+--------------------------+------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+------------+
     * | index   | name                     | type       | range | default    |
     * +---------+--------------------------+------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+------------+
     * | 0       | "Bypass"                 | "Bool"     | [false, true] | false      |
     * +---------+--------------------------+------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+------------+
     * | 1       | "Distortion Mode"        | "Choice"   | ["Cubic", "Tanh", "Arctan", "ArctanTanh", "L1", "L2",
     * "HardClip", "DeadZone", "FoldBackTriangle", "FoldBackSine", "FoldBackSinArctan", "BitCrush", "Decimate"]   |
     * "Cubic"    |
     * +---------+--------------------------+------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+------------+
     * | 2       | "Distortion Amount"      | "Float"    | [0, 1] | 0          |
     * +---------+--------------------------+------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+------------+
     * | 3       | "Apply Upsampling"       | "Choice"   | ["None", "X8", "X16", "X32"] | "None"     |
     * +---------+--------------------------+------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+------------+
     * | 4       | "Wetness"                | "Float"    | [0, 1] | 1          |
     * +---------+--------------------------+------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+------------+
     * | 5       | "Post Distortion Gain"   | "Float"    | [-40, 0] | 0          |
     * +---------+--------------------------+------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------+------------+
     */
    SAMICore_Identify_Processor_Distortion,

    /**
     * Name: "Echo"
     * Parameters:
     * +---------+----------------------+-----------+-----------------+------------+
     * | index   | name                 | type      | range           | default    |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 0       | "Dry Bypass"         | "Bool"    | [false, true]   | false      |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 1       | "Dry Gain dB"        | "Float"   | [-35, 6]        | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 2       | "Dry Pan"            | "Float"   | [-1, 1]         | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 3       | "Tap 1 Bypass"       | "Bool"    | [false, true]   | true       |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 4       | "Tap 1 Delay Time"   | "Float"   | [0.001, 1]      | 0.001      |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 5       | "Tap 1 Feedback"     | "Float"   | [0, 1]          | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 6       | "Tap 1 Gain dB"      | "Float"   | [-35, 6]        | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 7       | "Tap 1 Pan"          | "Float"   | [-1, 1]         | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 8       | "Tap 1 Sync"         | "Bool"    | [false, true]   | true       |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 9       | "Tap 2 Bypass"       | "Bool"    | [false, true]   | true       |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 10      | "Tap 2 Delay Time"   | "Float"   | [0.001, 1]      | 0.001      |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 11      | "Tap 2 Feedback"     | "Float"   | [0, 1]          | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 12      | "Tap 2 Gain dB"      | "Float"   | [-35, 6]        | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 13      | "Tap 2 Pan"          | "Float"   | [-1, 1]         | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 14      | "Tap 2 Sync"         | "Bool"    | [false, true]   | true       |
     * +---------+----------------------+-----------+-----------------+------------+
     */
    SAMICore_Identify_Processor_Echo,

    /**
     * Name: "Filter"
     * Parameters:
     * +---------+-----------------+------------+---------------------------------------------------------------------------------------------------------------------------+--------------+
     * | index   | name            | type       | range | default      |
     * +---------+-----------------+------------+---------------------------------------------------------------------------------------------------------------------------+--------------+
     * | 0       | "Filter Mode"   | "Choice"   | ["LowPass", "HighPass", "BandPass", "NormalisedBandPass", "Bell",
     * "HighShelf", "LowShelf", "AllPass", "Notch", "Morph"]   | "LowPass"    |
     * +---------+-----------------+------------+---------------------------------------------------------------------------------------------------------------------------+--------------+
     * | 1       | "Cutoff Freq"   | "Float"    | [20, 20000] | 1000         |
     * +---------+-----------------+------------+---------------------------------------------------------------------------------------------------------------------------+--------------+
     * | 2       | "Resonance"     | "Float"    | [0.1, 20] | 1            |
     * +---------+-----------------+------------+---------------------------------------------------------------------------------------------------------------------------+--------------+
     * | 3       | "Gain dB"       | "Float"    | [-20, 20] | 0            |
     * +---------+-----------------+------------+---------------------------------------------------------------------------------------------------------------------------+--------------+
     * | 4       | "Morph"         | "Float"    | [-1, 1] | 0            |
     * +---------+-----------------+------------+---------------------------------------------------------------------------------------------------------------------------+--------------+
     */
    SAMICore_Identify_Processor_Filter,

    /**
     * Name: "GainAndPan"
     * Parameters:
     * +---------+-------------+-----------+-------------+------------+
     * | index   | name        | type      | range       | default    |
     * +---------+-------------+-----------+-------------+------------+
     * | 0       | "Gain dB"   | "Float"   | [-70, 35]   | 0          |
     * +---------+-------------+-----------+-------------+------------+
     * | 1       | "Pan"       | "Float"   | [-1, 1]     | 0          |
     * +---------+-------------+-----------+-------------+------------+
     */
    SAMICore_Identify_Processor_GainAndPan,

    /**
     * Name: "Limiter"
     * Parameters:
     * +---------+-------------------------+-----------+-----------------+------------+
     * | index   | name                    | type      | range           | default    |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 0       | "Bypass"                | "Bool"    | [false, true]   | false      |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 1       | "Input Gain dB"         | "Float"   | [0, 24]         | 0          |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 2       | "Ceiling dB"            | "Float"   | [-24, 0]        | -0.3       |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 3       | "Release"               | "Float"   | [1, 3000]       | 500        |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 4       | "Lookahead"             | "Float"   | [0, 10]         | 0          |
     * +---------+-------------------------+-----------+-----------------+------------+
     * | 5       | "Audition Unity Gain"   | "Bool"    | [false, true]   | false      |
     * +---------+-------------------------+-----------+-----------------+------------+
     */
    SAMICore_Identify_Processor_Limiter,

    /**
     * Name: "Reverb"
     * Parameters:
     * +---------+----------------------+-----------+-----------------+------------+
     * | index   | name                 | type      | range           | default    |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 0       | "Bypass"             | "Bool"    | [false, true]   | false      |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 1       | "Decay Time"         | "Float"   | [0.5, 16]       | 3          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 2       | "Damp"               | "Float"   | [0, 1]          | 0.5        |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 3       | "Mod Depth"          | "Float"   | [0, 1]          | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 4       | "Mod Rate"           | "Float"   | [0.01, 7.5]     | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 5       | "Wet Gain"           | "Float"   | [-36, 12]       | 0          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 6       | "Wet Stereo Width"   | "Float"   | [0, 2]          | 1          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 7       | "Wet Mix"            | "Float"   | [0, 1]          | 0.5        |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 8       | "Wet LP Bypass"      | "Bool"    | [false, true]   | true       |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 9       | "Wet HP Bypass"      | "Bool"    | [false, true]   | true       |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 10      | "Wet LP Freq"        | "Float"   | [20, 20000]     | 20000      |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 11      | "Wet HP Freq"        | "Float"   | [20, 20000]     | 20         |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 12      | "Wet LP Res"         | "Float"   | [0.1, 20]       | 1          |
     * +---------+----------------------+-----------+-----------------+------------+
     * | 13      | "Wet HP Res"         | "Float"   | [0.1, 20]       | 1          |
     * +---------+----------------------+-----------+-----------------+------------+
     */
    SAMICore_Identify_Processor_Reverb,

    /**
     * Name: "Vibrato"
     * Parameters:
     * +---------+--------------------+-----------+-----------------+------------+
     * | index   | name               | type      | range           | default    |
     * +---------+--------------------+-----------+-----------------+------------+
     * | 0       | "Bypass"           | "Bool"    | [false, true]   | false      |
     * +---------+--------------------+-----------+-----------------+------------+
     * | 1       | "Rate Hz"          | "Float"   | [1, 8]          | 4          |
     * +---------+--------------------+-----------+-----------------+------------+
     * | 2       | "Depth Semitone"   | "Float"   | [0, 2]          | 0.5        |
     * +---------+--------------------+-----------+-----------------+------------+
     * | 3       | "Wetness"          | "Float"   | [0, 1]          | 1          |
     * +---------+--------------------+-----------+-----------------+------------+
     */
    SAMICore_Identify_Processor_Vibrato,

    /**
     * Name: "TimeDomainPitchShifter"
     * Parameters:
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | index   | name                   | type       | range                                                                        | default        |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | 0       | "Bypass"               | "Bool"     | [false, true]                                                                | false          |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | 1       | "Pitch Ratio"          | "Float"    | [0.25, 4]                                                                    | 1              |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | 2       | "Interpolation Mode"   | "Choice"   | ["Linear", "Lagrange4", "Lagrange16", "Lagrange24", "Sinc32", "Lanczos32"]   | "Lagrange4"    |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | 3       | "Mono Input"           | "Bool"     | [false, true]                                                                | true           |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | 4       | "Mode"                 | "Choice"   | ["Fastest", "Moderate", "HighQuality", "UltraHighQuality"]                   | "Moderate"     |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     */
    SAMICore_Identify_Processor_TimeDomainPitchShifter,

    /**
     * Name: "SpatialAudio"
     * Parameters:
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | index   | name                   | type       | range                                                                        | default        |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | 0       | "preset_id"            | "Int"      | [0, 1]                                                                       | 1              |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     */
    SAMICore_Identify_Processor_SpatialAudio,

    /**
     * Name: "AECompressor"
     * Parameters:
     * +-------+--------------------------+---------+---------------+---------+
       | index | name                     | type    | range         | default |
       +-------+--------------------------+---------+---------------+---------+
       | 0     | Bypass                   | "Bool"  | [false, true] | false   |
       +-------+--------------------------+---------+---------------+---------+
       | 1     | Pre Gain dB              | "Float" | [0.0, 100]    | 0       |
       +-------+--------------------------+---------+---------------+---------+
       | 2     | Threshold                | "Float" | [-100, 0]     | -24     |
       +-------+--------------------------+---------+---------------+---------+
       | 3     | Knee                     | "Float" | [0.0, 40]     | 30      |
       +-------+--------------------------+---------+---------------+---------+
       | 4     | Ratio                    | "Float" | [0.0, 20]     | 12      |
       +-------+--------------------------+---------+---------------+---------+
       | 5     | Attack                   | "Float" | [0.0, 1]      | 0.003   |
       +-------+--------------------------+---------+---------------+---------+
       | 6     | Release                  | "Float" | [0.0, 1]      | 0.25    |
       +-------+--------------------------+---------+---------------+---------+
       | 7     | Pre Delay                | "Float" | [0.0, 1]      | 0.006   |
       +-------+--------------------------+---------+---------------+---------+
       | 8     | Release Zone 1           | "Float" | [0.0, 1]      | 0.09    |
       +-------+--------------------------+---------+---------------+---------+
       | 9     | Release Zone 2           | "Float" | [0.0, 1]      | 0.16    |
       +-------+--------------------------+---------+---------------+---------+
       | 10    | Release Zone 3           | "Float" | [0.0, 1]      | 0.42    |
       +-------+--------------------------+---------+---------------+---------+
       | 11    | Release Zone 4           | "Float" | [0.0, 1]      | 0.98    |
       +-------+--------------------------+---------+---------------+---------+
       | 12    | Post Gain dB             | "Float" | [0.0, 100]    | 0.0     |
       +-------+--------------------------+---------+---------------+---------+
       | 13    | Wet                      | "Float" | [0.0, 1]      | 1.0     |
       +-------+--------------------------+---------+---------------+---------+
       | 14    | Attenuation dB Threshold | "Float" | [0.0, 2]      | 2.0     |
       +-------+--------------------------+---------+---------------+---------+
       | 15    | Detector Avg Threshold   | "Float" | [0.0, 1]      | 1.0     |
       +-------+--------------------------+---------+---------------+---------+
     */
    SAMICore_Identify_Processor_AECompressor,

    // extractor
    SAMICore_Identify_Extractor_F0Detection = 200,
    SAMICore_Identify_Extractor_OnsetDetection,
    SAMICore_Identify_Extractor_SpectrumDisplay,
    SAMICore_Identify_Extractor_VolumeDetection,
    SAMICore_Identify_Extractor_EventDetection,
    SAMICore_Identify_Extractor_VoiceActivityDetection,
    SAMICore_Identify_Extractor_BeatTracking,
    SAMICore_Identify_Extractor_BeatTrackingOffline,
    SAMICore_Identify_Extractor_Music2VibesVideoModel,
    SAMICore_Identify_Extractor_Music2VibesMatchModel,
    SAMICore_Identify_Extractor_NNVAD,
    SAMICore_Identify_Extractor_Loudness,
    SAMICore_Identify_Extractor_AedS2s,
    SAMICore_Identify_Extractor_VoiceActivityDetection_S2S,

    // 3a
    SAMICore_Identify_AEC = 300,
    SAMICore_Identify_RNNAEC,
    SAMICore_Identify_AGC,
    SAMICore_Identify_RNNOSIE16K,
    SAMICore_Identify_RNNOSIE,
    SAMICore_Identify_RNNOSIE48K,
    SAMICore_Identify_TCNDENOISE44K,
    SAMICore_Identify_TCNDENOISE16K,
    SAMICore_Identify_DENOISE_V2_MUSIC44k,
    SAMICore_Identify_DENOISE_V2_SPEECH44k,
    SAMICore_Identify_DENOISE_V2_MUSIC16k,
    SAMICore_Identify_DENOISE_V2_SPEECH16k,
    SAMICore_Identify_DENOISE_V2_DEREVERB44k,
    SAMICore_Identify_BEAM_FORMING,
    SAMICore_Identify_NNAEC_MIC_SELECTION,
    SAMICore_Identify_DENOISE_V2,
    SAMICore_Identify_LoudNorm,
    SAMICore_Identify_LoudNorm2,

    // non realtime effect
    SAMICore_Identify_TimeScaler = 400,

    // sami engine
    SAMICore_Identify_Engine = 500,
    SAMICore_Identify_EngineExecutor,
    SAMICore_Identify_EngineExecutor_TimeAlign,
    SAMICore_Identify_EngineExecutor_AED,
    SAMICore_Identify_EngineExecutor_Denoise,
    SAMICore_Identify_EngineExecutor_Common = 512,

    // common executor
    SAMICore_Identify_EngineExecutor_CE_DENOISE = 550,
    SAMICore_Identify_EngineExecutor_CE_DEREVERB = 551,
    SAMICore_Identify_EngineExecutor_CE_HOWLING = 552,
    SAMICore_Identify_EngineExecutor_CE_AEC = 553,
    SAMICore_Identify_EngineExecutor_CE_Loudnorm3 = 554,

    // server
    SAMICore_Identify_Create_Token = 600,
    SAMICore_Identify_TTS_Online = 601,
    SAMICore_Identify_ASR_Online = 602,
    SAMICore_Identify_BeatTracking_Online = 603,
    SAMICore_Identify_MusicSourceSeparate_Online = 604,
    SAMICore_Identify_MusicTagging_Online = 605,
    SAMICore_Identify_Chorus_Online = 606,
    SAMICore_Identify_MusicRetarget_Online = 607,
    SAMICore_Identify_Midi_Online = 608,
    SAMICore_Identify_SpeechDisfluency_Online = 609,
    SAMICore_Identify_VoiceFilter_Online = 610,
    SAMICore_Identify_GET_MixedEncryptedFOnlineToken = 611,
    SAMICore_Identify_LyricsAlignment_Online = 612,
    SAMICore_Identify_SpeechToSong_Online = 613,

    SAMICore_Identify_Streaming_ASR_Online = 650,
    SAMICore_Identify_Streaming_TTS_Online = 651,
    SAMICore_Identify_Streaming_Playing_TTS_Online = 652,
    SAMICore_Identify_Streaming_ASR_Async_Online = 653,
    SAMICore_Identify_Streaming_VC_Online = 654,

    // asr
    SAMICore_Identify_SPEECH_RECOGNITION = 700,
    SAMICore_Identify_ASR_Offline = 701,

    //tob
    SAMICore_Identify_Processor_ContextWithBinaryRes = 2000,

    SAMICore_Identify_TuneToTarget = 3000,

    SAMICore_Identify_Get_DevicePlaybackAbility = 7000,

    // karaoke
    SAMICore_Identify_SAMIKaraoke = 8000,
};

#endif  //SAMI_CORE_SAMICOREIDENTIFYENUM_H
