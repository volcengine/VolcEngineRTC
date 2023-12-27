//
// Created by xiangning zhu on 2021/12/20.
//

#ifndef SAMI_CORE_SAMI_CORE_BASE_DEF_H
#define SAMI_CORE_SAMI_CORE_BASE_DEF_H

typedef enum dataType {
    // base
    SAMICoreDataType_Float = 0,
    SAMICoreDataType_Int,
    SAMICoreDataType_String,
    SAMICoreDataType_Double,
    SAMICoreDataType_Long,
    SAMICoreDataType_Null,  //when no data ptr need set ,use this type

    // custom base
    SAMICoreDataType_AudioBuffer = 50,
    SAMICoreDataType_ExtendAudioBuffer = 51,
    SAMICoreDataType_Data_Uri_Parameter = 52,

    // context
    SAMICoreDataType_ContextPrepareParameter = 100,
    SAMICoreDataType_ResourceParameter,
    SAMICoreDataType_ParameterEvent,

    // processor
    SAMICoreDataType_ProcessorParameter = 150,

    // Extractor
    SAMICoreDataType_FeatureSet = 250,
    SAMICoreDataType_ExtractorParameter,

    // model binary
    SAMICoreDataType_ModelBin = 300,

    // aec
    SAMICoreDataType_AecInput = 350,

    // sami engine tts
    SAMICoreDataType_TTSCallBack = 400,
    SAMICoreDataType_EngineCreateParameter,
    SAMICoreDataType_ExecutorCreateParameter,

    // sami engine wakeup
    SAMICoreDataType_Engine_WakeupWord_Result = 410,

    // time align
    SAMICoreDataType_TimeAlign = 450,

    //loud norm
    SAMICoreDataType_LoudNorm = 451,

    //loud norm
    SAMICoreDataType_LoudNorm2 = 452,

    // audio fading
    SAMICoreDataType_AudioFading = 453,

    // cher effect
    SAMICoreDataType_CherEffect = 454,

    // kws
    SAMICoreDataType_KWS = 455,

    // AudioEffect Compressor
    SAMICoreDataType_AudioEffect_Compressor = 456,
    // Audio Retarget
    SAMICoreDataType_AudioRetargetInOutInfo = 457,
    SAMICoreDataType_AudioRetargetCallBack = 458,
    SAMICoreDataType_MultiTimeAlignResult = 459,


    // server
    SAMICoreDataType_TTS_Result = 500,
    SAMICoreDataType_ASR_Result = 503,
    SAMICoreDataType_AudioBin = 504,
    SAMICoreDataType_BeatTracking_Result = 505,
    SAMICoreDataType_MusicSourceSeparate_Result = 506,
    SAMICoreDataType_MusicTagging_Result = 507,
    SAMICoreDataType_Chorus_Result = 508,
    SAMICoreDataType_MusicRetarget_Result = 509,
    SAMICoreDataType_Midi_Result = 510,
    SAMICoreDataType_Token_Result = 511,
    SAMICoreDataType_SpeechDisfluency_Result = 512,
    SAMICoreDataType_VoiceFilterParam = 513,
    SAMICoreDataType_ServerHttpResponse = 514,
    SAMICoreDataType_LyricsAlignment_Result = 515,
    SAMICoreDataType_VC_Result = 516,

    // websocket
    SAMICoreDataType_WebSocket_Server_Event = 600,
    SAMICoreDataType_WebSocket_Connection_Event = 601,
    SAMICoreDataType_WebSocket_Asr = 602,
    SAMICoreDataType_WebSocket_Tts = 603,
    SAMICoreDataType_WebSocket_Vc = 604,
    SAMICoreDataType_WebSocket_Vc_Speaker = 605,

    // yggdrasil
    SAMICoreDataType_Yggdrasil_Mesh = 700,
    SAMICoreDataType_Yggdrasil_Mesh_And_Material_Factor,
    SAMICoreDataType_Yggdrasil_Factor,
    SAMICoreDataType_Yggdrasil_Source,
    SAMICoreDataType_Yggdrasil_Source_With_Orientation,
    SAMICoreDataType_Yggdrasil_Source_With_Config,
    SAMICoreDataType_Yggdrasil_Source_Buffer,
    SAMICoreDataType_Yggdrasil_Ambisonic_Channel_Buffer,
    SAMICoreDataType_Yggdrasil_Matrix_Input_Buffer,
    SAMICoreDataType_Yggdrasil_Binaural_Buffer,
    SAMICoreDataType_Yggdrasil_Loudspeaker_Buffer,
    SAMICoreDataType_Yggdrasil_Doppler_Effect,
    SAMICoreDataType_Yggdrasil_Loudspeaker_Array,
    SAMICoreDataType_Yggdrasil_Mapping_Matrix,
    SAMICoreDataType_Yggdrasil_Ambisonic_Orientation,
    SAMICoreDataType_Yggdrasil_Listener,
    SAMICoreDataType_Yggdrasil_Planar_Preset_Input_Buffer,
    SAMICoreDataType_Yggdrasil_Listener_Pose_From_Unity_Scene,

    // MDSS
    SAMICoreDataType_MDSS_RealtimeInfo,
    SAMICoreDataType_MDSS_OverallInfo,

    // TimeStretcher
    SAMICoreDataType_TimeStretcher_ScaleInfo = 800,
} SAMICoreDataType;

typedef enum identify {
    /**
     * SAMICoreIdentify_Processor_ContextWithString, used to create vocal preset from json string.
     * create handle with SAMICoreContextCreateParameter
     *
     * @see SAMICoreContextCreateParameter
     */
    SAMICoreIdentify_Processor_ContextWithString = 0,

    /**
     * SAMICoreIdentify_Processor_ContextWithFileName, used to create vocal preset from json file path.
     * create handle with SAMICoreContextCreateParameter
     *
     * @see SAMICoreContextCreateParameter
     */
    SAMICoreIdentify_Processor_ContextWithFileName,
    SAMICoreIdentify_Processor_ContextWithAutomation,

    /**
     * SAMICoreIdentify_Processor, used to create processor by name,here is an example:
     * @code
     *  SAMICoreHandle handle;
     *  const char* name = "Gain";
     *  int ret = SAMICoreCreateHandleByIdentify(&handle, SAMICoreIdentify_Processor, name);
     *  assert(ret == SAMI_OK);
     * @endcode
     *
     * or, you can create processor by enum id, like this:
     * @code
     * int ret = SAMICoreCreateHandleByIdentify(&handle, SAMICoreIdentify_Processor_Compressor, NULL);
     * @endcode
     *
     * the currently supported processors' name are match to processor id,
     * here is a table shows the mapping between IDs and names
     *
     * +---------------------------------------+--------------+
     * | Id                                    | Name         |
     * +---------------------------------------+--------------+
     * | SAMICoreIdentify_Processor_Gain       | "Gain"       |
     * +---------------------------------------+--------------+
     * | SAMICoreIdentify_Processor_Compressor | "Compressor" |
     * +---------------------------------------+--------------+
     *
     *
     */
    SAMICoreIdentify_Processor = 100,

    SAMICoreIdentify_Processor_Gain,
    SAMICoreIdentify_Processor_Compressor,
    SAMICoreIdentify_Processor_Chorus,
    SAMICoreIdentify_Processor_Distortion,
    SAMICoreIdentify_Processor_Echo,
    SAMICoreIdentify_Processor_Filter,
    SAMICoreIdentify_Processor_GainAndPan,
    SAMICoreIdentify_Processor_Limiter,
    SAMICoreIdentify_Processor_Reverb,
    SAMICoreIdentify_Processor_Vibrato,
    SAMICoreIdentify_Processor_TimeDomainPitchShifter,

    /**
     * Name: "SpatialAudio"
     * Parameters:
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | index   | name                   | type       | range                                                                        | default        |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     * | 0       | "preset_id"            | "Int"      | [0, 1]                                                                       | 1              |
     * +---------+------------------------+------------+------------------------------------------------------------------------------+----------------+
     */
    SAMICoreIdentify_Processor_SpatialAudio,

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
    SAMICoreIdentify_Processor_AECompressor,

    // graph used sami core api
    SAMICoreIdentify_Graph_TTPLAYER,
    SAMICoreIdentify_Graph_TTPLAYER_FromString,

    // extractor
    SAMICoreIdentify_Extractor_F0Detection = 200,
    SAMICoreIdentify_Extractor_OnsetDetection,
    SAMICoreIdentify_Extractor_SpectrumDisplay,
    SAMICoreIdentify_Extractor_VolumeDetection,
    SAMICoreIdentify_Extractor_EventDetection,
    SAMICoreIdentify_Extractor_VoiceActivityDetection,
    SAMICoreIdentify_Extractor_BeatTracking,
    SAMICoreIdentify_Extractor_BeatTrackingOffline,
    SAMICoreIdentify_Extractor_Music2VibesVideoModel,
    SAMICoreIdentify_Extractor_Music2VibesMatchModel,
    SAMICoreIdentify_Extractor_NNVAD,
    SAMICoreIdentify_Extractor_Loudness,
    SAMICoreIdentify_Extractor_AedS2s,
    SAMICoreIdentify_Extractor_VoiceActivityDetection_S2S,

    // 3a
    SAMICoreIdentify_AEC = 300,
    SAMICoreIdentify_RNNAEC,
    SAMICoreIdentify_AGC,
    SAMICoreIdentify_RNNOSIE16K,
    SAMICoreIdentify_RNNOSIE,
    SAMICoreIdentify_RNNOSIE48K,
    SAMICoreIdentify_TCNDENOISE44K,
    SAMICoreIdentify_TCNDENOISE16K,
    SAMICoreIdentify_DENOISE_V2_MUSIC44k,
    SAMICoreIdentify_DENOISE_V2_SPEECH44k,
    SAMICoreIdentify_DENOISE_V2_MUSIC16k,
    SAMICoreIdentify_DENOISE_V2_SPEECH16k,
    SAMICoreIdentify_DENOISE_V2_DEREVERB44k,
    SAMICoreIdentify_BEAM_FORMING,
    SAMICoreIdentify_NNAEC_MIC_SELECTION,
    SAMICoreIdentify_DENOISE_V2,
    SAMICoreIdentify_Loudnorm,
    SAMICoreIdentify_Loudnorm2,
    SAMICoreIdentify_AudioFading,
    SAMICoreIdentify_CherEffect,
    SAMICoreIdentify_AudioEffect_Compressor,
    SAMICoreIdentify_RNNAEC_V3,
    SAMICoreIdentify_DENOISE_V3,
    SAMICoreIdentify_Climiter,
    SAMICoreIdentify_Loudness,
    SAMICoreIdentify_VOICE_CONVERTER,

    // non realtime effect
    SAMICoreIdentify_TimeScaler = 400,
    SAMICoreIdentify_PitchShifter = 401,
    SAMICoreIdentify_ReTarget = 402,
    // sami engine
    SAMICoreIdentify_Engine = 500,
    SAMICoreIdentify_EngineExecutor,
    SAMICoreIdentify_EngineExecutor_TimeAlign,
    SAMICoreIdentify_EngineExecutor_AED,
    SAMICoreIdentify_EngineExecutor_Denoise,
    SAMICoreIdentify_EngineExecutor_WakeupWord,
    SAMICoreIdentify_EngineExecutor_MSS,
    SAMICoreIdentify_EngineExecutor_KWS,
    SAMICoreIdentify_EngineExecutor_AudioMetrics,
    SAMICoreIdentify_EngineExecutor_AudioMetricsV2 = 509,
    SAMICoreIdentify_EngineExecutor_MultiTimeAlign = 510,
    SAMICoreIdentify_EngineExecutor_TimeDomainReAlign = 511,
    SAMICoreIdentify_EngineExecutor_Common = 512,
    SAMICoreIdentify_EngineExecutor_SNR = 513,
    SAMICoreIdentify_EngineExecutor_Flow_SNR = 514,
    // common executor
    SAMICoreIdentify_EngineExecutor_CE_DENOISE = 550,
    SAMICoreIdentify_EngineExecutor_CE_DEREVERB = 551,
    SAMICoreIdentify_EngineExecutor_CE_HOWLING = 552,
    SAMICoreIdentify_EngineExecutor_CE_AEC = 553,
    SAMICoreIdentify_EngineExecutor_CE_Loudnorm3 = 554,

    // server
    SAMICoreIdentify_Create_Token = 600,
    SAMICoreIdentify_TTS_Online = 601,
    SAMICoreIdentify_ASR_Online = 602,
    SAMICoreIdentify_BeatTracking_Online = 603,
    SAMICoreIdentify_MusicSourceSeparate_Online = 604,
    SAMICoreIdentify_MusicTagging_Online = 605,
    SAMICoreIdentify_Chorus_Online = 606,
    SAMICoreIdentify_MusicRetarget_Online = 607,
    SAMICoreIdentify_Midi_Online = 608,
    SAMICoreIdentify_SpeechDisfluency_Online = 609,
    SAMICoreIdentify_VoiceFilter_Online = 610,
    SAMICoreIdentify_GET_MixedEncryptedFOnlineToken = 611,
    SAMICoreIdentify_LyricsAlignment_Online = 612,
    SAMICoreIdentify_SpeechToSong_Online = 613,

    SAMICoreIdentify_Streaming_ASR_Online = 650,
    SAMICoreIdentify_Streaming_TTS_Online = 651,
    SAMICoreIdentify_Streaming_Playing_TTS_Online = 652,
    SAMICoreIdentify_Streaming_ASR_Async_Online = 653,
    SAMICoreIdentify_Streaming_VC_Online = 654,

    // asr
    SAMICoreIdentify_SPEECH_RECOGNITION = 700,
    SAMICoreIdentify_ASR_Offline = 701,
    SAMICoreIdentify_Speech_Tracking = 702,

    // audio encode
    SAMICoreIdentify_Audio_Encode = 800,
    SAMICoreIdentify_Audio_Decode = 801,

    // non-effect
    SAMICoreIdentify_AudioScratcher = 900,

    //tob
    SAMICoreIdentify_Processor_ContextWithBinaryRes = 2000,

    SAMICoreIdentify_TuneToTarget = 3000,  //deprecated
    SAMICoreIdentify_ByteTuner = 3001,

    // yggdrasil
    SAMICoreIdentify_Yggdrasil = 4000,

    // audio_norm
    SAMICoreIdentify_AudioNorm = 5000,

    // MDSS
    SAMICoreIdentify_MulDimSingScoring = 6000,

    SAMICoreIdentify_Get_DevicePlaybackAbility = 7000,

    // SAMI Karaoke
    SAMICoreIdentify_SAMIKaraoke = 8000,

    // Audio ab testing
    SAMICoreIdentify_AbConfig = 9000,

} SAMICoreIdentify;

typedef enum propertyId {
    // base parameter
    SAMICorePropertyID_Base_NAME = 0,
    SAMICorePropertyID_Base_UNKNOWN,

    // token
    SAMICorePropertyID_Token_Timestamp = 50,

    // context
    SAMICorePropertyID_Processor_ContextPrepare = 100,
    SAMICorePropertyID_JSON_Context,

    // vad parameters
    SAMICorePropertyID_VAD_Aggressiveness_Mode_Name = 200,
    SAMICorePropertyID_VAD_Silence_Robust_Length_name,
    SAMICorePropertyID_VAD_Frame_Time_Length_Name,
    SAMICorePropertyID_VAD_Smoothing_Searching_Width_Name,
    SAMICorePropertyID_VAD_Smoothing_Searching_Threshold_Ratio_Name,
    SAMICorePropertyID_VAD_Overall_Moving_Average_Width_Name,
    SAMICorePropertyID_VAD_Overall_Searching_Threshold_Ratio_Name,
    SAMICorePropertyID_VAD_Overall_Silence_Length_Name,

    // compressor
    SAMICorePropertyID_Compressor_Bypass = 300,
    SAMICorePropertyID_Compressor_Ratio,
    SAMICorePropertyID_Compressor_Threshold,
    SAMICorePropertyID_Compressor_Knee_dB,
    SAMICorePropertyID_Compressor_Attack,
    SAMICorePropertyID_Compressor_Release,
    SAMICorePropertyID_Compressor_Auto_Makeup_Gain,
    SAMICorePropertyID_Compressor_Output_Gain_dB,
    SAMICorePropertyID_Compressor_Look_Head,

    // extractor frame feature
    SAMICorePropertyID_FrameFeatures = 400,
    SAMICorePropertyID_FrameFeature_SPECTRUM,
    SAMICorePropertyID_FrameFeature_ONSET,
    SAMICorePropertyID_FrameFeature_F0,
    SAMICorePropertyID_FrameFeature_BEAT_TRACKING,
    SAMICorePropertyID_FrameFeature_VOLUME,
    SAMICorePropertyID_FrameFeature_NNVAD,
    SAMICorePropertyID_FrameFeature_Voice_Activity,
    SAMICorePropertyID_FrameFeature_KWS,
    SAMICorePropertyID_FrameFeature_AudioMetrics,
    SAMICorePropertyID_FrameFeature_SHORTTERM_LOUDNESS,
    SAMICorePropertyID_FrameFeature_MOMENTARY_LOUDNESS,
    SAMICorePropertyID_FrameFeature_AudioMetricsV2 = 412,
    SAMICorePropertyID_FrameFeature_SNR = 413,
    SAMICorePropertyID_FrameFeature_Aed_STATISTIC,
    SAMICorePropertyID_FrameFeature_VOICE_ACTIVITY_DETECTION_STATISTIC,

    // extractor overall feature
    SAMICorePropertyID_OverallFeatures = 500,
    SAMICorePropertyID_OverallFeature_GLOBAL_LOUDNESS,
    SAMICorePropertyID_OverallFeature_GLOBAL_PEAK,
    SAMICorePropertyID_OverallFeature_TRACKING_OFFLINE_OVERALL,
    SAMICorePropertyID_OverallFeature_NNVAD_OVERALL,
    SAMICorePropertyID_OverallFeature_ONSET_OVERALL,
    SAMICorePropertyID_OverallFeature_Voice_Activity_OVERALL,

    // extractor
    SAMICorePropertyID_SetExtractorFloatParameter = 600,
    SAMICorePropertyID_SetExtractorStringParameter,
    SAMICorePropertyID_SetExtractorIntParameter,
    SAMICorePropertyID_GetLatency,

    //Loudness extractor mode
    SAMICorePropertyID_SetExtractorLoudnessModeParameter,

    // model path
    SAMICorePropertyId_LoadModelBinary = 700,

    // seek
    SAMICorePropertyId_Seek = 800,

    // time scaler
    SAMICorePropertyId_TimeScaler_ScaleRate = 900,

    // pitch shifter
    SAMICorePropertyId_PitchShifter_Value = 901,

    // audio scratcher
    SAMICorePropertyId_AudioScratcher_Value = 902,

    SAMICorePropertyID_AudioRetarget_InOutInfo,
    SAMICorePropertyID_AudioRetarget_CallBack,       //set callback function
    SAMICorePropertyID_AudioRetarget_CancleProcess,  //manual cancellation in asynchronous mode
    SAMICorePropertyID_AudioRetarget_IsProcess,      //check whether it is being processed in asynchronous mode
    SAMICorePropertyID_AudioRetarget_Wait,        //waiting for the processing thread to complete in asynchronous mode
    SAMICorePropertyID_AudioRetarget_SpliceInfo,  //get audio arrangement json info
    // processor
    SAMICorePropertyID_Processor_Prepare = 1000,
    SAMICorePropertyID_Processor_SetParametersOffline,
    SAMICorePropertyID_Processor_ContextUpdateFromFile,
    SAMICorePropertyID_Processor_ContextUpdateFromString,
    SAMICorePropertyID_Processor_ContextEmplaceParameterEventNow,  // use normalization value
    SAMICorePropertyID_Processor_ContextEmplaceParameterEventNowWithPlainValue,  // use plain value. For string options you can use the index of option as plain value
    SAMICorePropertyID_Processor_Name,
    SAMICorePropertyID_Processor_Loudnorm,
    SAMICorePropertyID_Processor_Loudnorm2,
    SAMICorePropertyID_Processor_AudioFading,
    SAMICorePropertyID_Processor_AudioFading_Seek,
    SAMICorePropertyID_Processor_CherEffect,
    SAMICorePropertyID_Processor_AudioEffect_Compressor,
    SAMICorePropertyID_Processor_Climiter,
    SAMICorePropertyID_Processor_Loudness,

    // graph
    SAMICorePropertyID_Graph_LoudnessStrategyPanoramaSwitch,
    SAMICorePropertyID_Graph_LoudnessStrategyMaxBlockSize,

    SAMICorePropertyID_AGC = 1050,
    SAMICorePropertyID_AGC_SetTargetLevel,
    SAMICorePropertyID_AGC_SetGain,
    SAMICorePropertyID_AGC_SetEnableLimiter,

    // sami engine
    SAMICoreEngineExecutorOutPut = 1100,
    SAMICorePropertyID_KWS_KeyWords = 1101,
    SAMICorePropertyID_KWS_Language = 1102,
    //通用engine utility模块相关
    SAMICorePropertyID_Common_Flush = 1103,
    SAMICorePropertyID_Common_Reset = 1104,
    SAMICorePropertyID_Common_SetParam = 1105,
    SAMICorePropertyID_Common_SetInputEnd = 1106,
    SAMICorePropertyID_Common_GetParam = 1107,
    SAMICorePropertyID_Common_GetResult = 1108,

    // denoise
    SAMICorePropertyID_TCNDenoise = 1200,
    SAMICorePropertyID_TCNDenoise_Rate,
    SAMICorePropertyID_TCNDenoise_Mode,

    SAMICorePropertyID_Processor_ContextChunkBinaryRes = 1300,
    SAMICorePropertyID_Processor_ContextUpdateFromBinaryFile,
    SAMICorePropertyID_Processor_ContextUpdateFromBinaryRes,
    SAMICorePropertyID_Processor_ContextSeek,

    // denoise
    SAMICorePropertyID_Denoise_V2 = 1400,
    SAMICorePropertyID_Denoise_V2_Rate,
    SAMICorePropertyID_Denoise_V2_Mode,
    SAMICorePropertyID_Denoise_V3,
    SAMICorePropertyID_Denoise_V3_FlushData,
    SAMICorePropertyID_Denoise_V3_SpeechRatio,
    // speech recognition
    SAMICorePropertyID_SpeechRecognition = 1500,
    SAMICorePropertyID_SpeechRecognition_Reset,
    SAMICorePropertyID_SpeechRecognition_Finish,
    SAMICorePropertyID_SpeechRecognition_UseWordInfo,
    SAMICorePropertyID_SpeechRecognition_Resume,
    SAMICorePropertyID_SpeechRecognition_UpdateRange,

    SAMICorePropertyID_ASR_Offline,
    SAMICorePropertyID_ASR_Offline_Set_Parameters,
    SAMICorePropertyID_ASR_Offline_Rest_Executor,
    SAMICorePropertyID_ASR_Offline_Finish,
    SAMICorePropertyID_ASR_Offline_Finish_Result,
    SAMICorePropertyID_AudioMetrics_Rest_Executor,
    SAMICorePropertyID_General_Rest_Executor,
    SAMICorePropertyID_AudioMetricsV2_Rest_Executor = 1513,

    // Speech Tracking
    SAMICorePropertyID_SpeechTracking = 1550,
    SAMICorePropertyID_SpeechTracking_Reset,
    SAMICorePropertyID_SpeechTracking_Finish,
    SAMICorePropertyID_SpeechTracking_UseWordInfo,
    SAMICorePropertyID_SpeechTracking_Resume,
    SAMICorePropertyID_SpeechTracking_UpdateRange,
    SAMICorePropertyID_SpeechTracking_Output,

    // yggdrasil
    SAMICorePropertyId_Yggdrasil_Initialize_Context = 1600,
    SAMICorePropertyId_Yggdrasil_Mesh,
    SAMICorePropertyId_Yggdrasil_Mesh_And_Material_Factor,
    SAMICorePropertyId_Yggdrasil_Absorption_Factor,
    SAMICorePropertyId_Yggdrasil_Scattering_Factor,
    SAMICorePropertyId_Yggdrasil_Transmission_Factor,
    SAMICorePropertyId_Yggdrasil_Scene_Commit,
    SAMICorePropertyId_Yggdrasil_Scene_Update,
    SAMICorePropertyId_Yggdrasil_Source_Add,
    SAMICorePropertyId_Yggdrasil_Source_With_Orientation,
    SAMICorePropertyId_Yggdrasil_Source_With_Config,
    SAMICorePropertyId_Yggdrasil_Source_Remove,
    SAMICorePropertyId_Yggdrasil_Source_Buffer,
    SAMICorePropertyId_Yggdrasil_Ambisonic_Channel_Buffer,
    SAMICorePropertyId_Yggdrasil_Interleaved_Ambisonic_Buffer,
    SAMICorePropertyId_Yggdrasil_Matrix_Input_Buffer,
    SAMICorePropertyId_Yggdrasil_Interleaved_Binaural_Buffer,
    SAMICorePropertyId_Yggdrasil_Planar_Binaural_Buffer,
    SAMICorePropertyId_Yggdrasil_Interleaved_Loudspeaker_Buffer,
    SAMICorePropertyId_Yggdrasil_Planar_Loudspeaker_Buffer,
    SAMICorePropertyId_Yggdrasil_Doppler_Effect,
    SAMICorePropertyId_Yggdrasil_Playback_Mode,
    SAMICorePropertyId_Yggdrasil_Loudspeaker_Array,
    SAMICorePropertyId_Yggdrasil_Mapping_Matrix,
    SAMICorePropertyId_Yggdrasil_Ambisonic_Orientation,
    SAMICorePropertyId_Yggdrasil_Listener,
    SAMICorePropertyId_Yggdrasil_Source,
    SAMICorePropertyId_Yggdrasil_Source_Config,
    SAMICorePropertyId_Yggdrasil_Submit_Planar_Preset_Input_Buffer,
    SAMICorePropertyId_Yggdrasil_Listener_Pose_From_Unity_Scene,

    // MDSS
    SAMICorePropertyID_FrameFeature_MulDimSingScoring = 1650,
    SAMICorePropertyID_OverallFeature_MulDimSingScoring,
    SAMICorePropertyID_SentenceScores_MulDimSingScoring,
    SAMICorePropertyID_SeekTo_MulDimSingScoring,
    SAMICorePropertyID_SetTranspose_MulDimSingScoring,

    SAMICorePropertyID_LyricsAlignment_LyricsWords,
    SAMICorePropertyID_LyricsAlignment_AudioFileData,

    SAMICorePropertyId_ASR_Online_Reset_Recognition = 1700,
    SAMICorePropertyID_Stream_TTS_Online_Force_Finish = 1701,
    SAMICorePropertyID_Stream_TTS_Online_Wait_Stop = 1702,
    SAMICorePropertyID_Stream_Play_TTS_Online_Force_Finish = 1703,
    SAMICorePropertyId_ASR_Online_Force_Finish = 1704,
    SAMICorePropertyId_ASR_Online_Start_Connect = 1705,
    SAMICorePropertyID_Stream_Play_TTS_Online_Set_TimeStrecher = 1706,

    SAMICorePropertyId_VC_Online = 1710,
    SAMICorePropertyId_VC_Online_Open_Loudspeaker,
    SAMICorePropertyId_VC_Online_Close_Loudspeaker,
    SAMICorePropertyId_VC_Online_Audio_Start_Play,
    SAMICorePropertyId_VC_Online_Audio_Stop_Play,
    SAMICorePropertyId_VC_Online_Audio_Pause_Play,
    SAMICorePropertyId_VC_Online_Audio_Resume_Play,
    SAMICorePropertyId_VC_Online_Start_Server,
    SAMICorePropertyId_VC_Online_Stop_Server,
    SAMICorePropertyId_VC_Online_Stop_Server_Async,
    SAMICorePropertyId_VC_Online_Force_Finish_Server,
    SAMICorePropertyId_VC_Online_Set_Speaker,
    SAMICorePropertyId_VC_Online_Get_Performance_Event_Tracking,
    SAMICorePropertyId_VC_Online_Get_Input_Data_Save_File,
    SAMICorePropertyId_VC_Online_Set_Input_Data_Uri,
    SAMICorePropertyId_VC_Online_Set_Output_Data_Uri,

    SAMICorePropertyId_ByteTuner_Force_Stop = 1750,

    // audio metrics
    SAMICorePropertyID_AudioMetricsJson = 1800,
    SAMICorePropertyID_AudioMetrics_InputEnd,
    SAMICorePropertyID_AudioMetricsV2Json = 1802,
    SAMICorePropertyID_AudioMetricsV2ThresholdJson = 1803,
    SAMICorePropertyID_AudioMetricsV2_InputEnd = 1804,
    // nnaec v3
    SAMICorePropertyID_NNAEC_V3 = 1850,
    SAMICorePropertyID_NNAEC_V3_ExtraData,
    SAMICorePropertyID_VOICE_CONVERTER_ExtraData,

    SAMICorePropertyID_Processor_Reset = 2000,
    // add parameters of other algorithms
    SAMICorePropertyID_MultiTimeAlign_Result = 2001,
    SAMICorePropertyID_DomainTimeAlignOffsetJson = 2002,

    // snr
    SAMICorePropertyID_Flow_SNR_InputEnd = 2100,
} SAMICorePropertyId;

struct audioBuffer {
    unsigned int numberChannels;
    unsigned int numberSamples;
    int isInterleave;
    float** data;
};

typedef struct audioBlock {
    SAMICoreDataType dataType;
    unsigned int numberAudioData;
    // abstract, can convert to any object such as midi, etc
    void* audioData;
} SAMICoreBlock;

#endif  //SAMI_CORE_SAMI_CORE_BASE_DEF_H
