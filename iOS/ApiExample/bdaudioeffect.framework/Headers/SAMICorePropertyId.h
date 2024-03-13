//
// Created by LIJING on 2021/11/22.
//

#ifndef SAMI_CORE_SAMICOREPROPERTYIDENUM_H
#define SAMI_CORE_SAMICOREPROPERTYIDENUM_H

typedef NS_ENUM(int, SAMICore_PropertyId) {
    // base parameter
    SAMICore_PropertyId_Base_NAME = 0,
    SAMICore_PropertyId_Base_UNKNOWN,

    // token
    SAMICore_PropertyID_Token_Timestamp = 50,

    // context
    SAMICore_PropertyId_Processor_ContextPrepare = 100,
    SAMICore_PropertyId_JSON_Context,

    // vad parameters
    SAMICore_PropertyId_VAD_Aggressiveness_Mode_Name = 200,
    SAMICore_PropertyId_VAD_Silence_Robust_Length_name,
    SAMICore_PropertyId_VAD_Frame_Time_Length_Name,
    SAMICore_PropertyId_VAD_Smoothing_Searching_Width_Name,
    SAMICore_PropertyId_VAD_Smoothing_Searching_Threshold_Ratio_Name,
    SAMICore_PropertyId_VAD_Overall_Moving_Average_Width_Name,
    SAMICore_PropertyId_VAD_Overall_Searching_Threshold_Ratio_Name,
    SAMICore_PropertyId_VAD_Overall_Silence_Length_Name,

    // compressor
    SAMICore_PropertyId_Compressor_Bypass = 300,
    SAMICore_PropertyId_Compressor_Ratio,
    SAMICore_PropertyId_Compressor_Threshold,
    SAMICore_PropertyId_Compressor_Knee_dB,
    SAMICore_PropertyId_Compressor_Attack,
    SAMICore_PropertyId_Compressor_Release,
    SAMICore_PropertyId_Compressor_Auto_Makeup_Gain,
    SAMICore_PropertyId_Compressor_Output_Gain_dB,
    SAMICore_PropertyId_Compressor_Look_Head,

    // extractor frame feature
    SAMICore_PropertyId_FrameFeatures = 400,
    SAMICore_PropertyId_FrameFeature_SPECTRUM,
    SAMICore_PropertyId_FrameFeature_ONSET,
    SAMICore_PropertyId_FrameFeature_F0,
    SAMICore_PropertyId_FrameFeature_BEAT_TRACKING,
    SAMICore_PropertyId_FrameFeature_VOLUME,
    SAMICore_PropertyId_FrameFeature_NNVAD,
    SAMICore_PropertyId_FrameFeature_Voice_Activity,

    // extractor overall feature
    SAMICore_PropertyId_OverallFeatures = 500,
    SAMICore_PropertyId_OverallFeature_GLOBAL_LOUDNESS,
    SAMICore_PropertyId_OverallFeature_GLOBAL_PEAK,
    SAMICore_PropertyId_OverallFeature_TRACKING_OFFLINE_OVERALL,
    SAMICore_PropertyId_OverallFeature_NNVAD_OVERALL,
    SAMICore_PropertyId_OverallFeature_ONSET_OVERALL,
    SAMICore_PropertyId_OverallFeature_Voice_Activity_OVERALL,

    // extractor
    SAMICore_PropertyId_SetExtractorFloatParameter = 600,
    SAMICore_PropertyId_SetExtractorStringParameter,

    // model path
    SAMICore_PropertyId_LoadModelBinary = 700,

    // seek
    SAMICore_PropertyId_Seek = 800,

    // time scaler
    SAMICore_PropertyId_TimeScaler_ScaleRate = 900,

    // processor
    SAMICore_PropertyId_Processor_Prepare = 1000,
    SAMICore_PropertyId_Processor_SetParametersOffline,
    SAMICore_PropertyId_Processor_ContextUpdateFromFile,
    SAMICore_PropertyId_Processor_ContextUpdateFromString,
    SAMICore_PropertyId_Processor_ContextEmplaceParameterEventNow,
    SAMICore_PropertyId_Processor_ContextEmplaceParameterEventNowWithPlainValue,

    SAMICore_PropertyId_Processor_Loudnorm = 1007,
    SAMICore_PropertyId_Processor_Loudnorm2,

    SAMICore_PropertyId_AGC = 1050,
    SAMICore_PropertyId_AGC_SetTargetLevel,
    SAMICore_PropertyId_AGC_SetGain,
    SAMICore_PropertyId_AGC_SetEnableLimiter,

    // sami engine
    SAMICore_PropertyId_EngineExecutorOutPut = 1100,
    //通用engine utility模块相关
    SAMICore_PropertyID_Common_Flush = 1103,
    SAMICore_PropertyID_Common_Reset = 1104,
    SAMICore_PropertyID_Common_SetParam = 1105,
    SAMICore_PropertyID_Common_SetInputEnd = 1106,
    SAMICore_PropertyID_Common_GetParam = 1107,
    SAMICore_PropertyID_Common_GetResult = 1108,
    // denoise
    SAMICore_PropertyId_TCNDenoise = 1200,
    SAMICore_PropertyId_TCNDenoise_Rate,
    SAMICore_PropertyId_TCNDenoise_Mode,

    SAMICore_PropertyId_Processor_ContextChunkBinaryRes = 1300,
    SAMICore_PropertyId_Processor_ContextUpdateFromBinaryFile,
    SAMICore_PropertyId_Processor_ContextUpdateFromBinaryRes,

    // denoise
    SAMICore_PropertyId_Denoise_V2 = 1400,
    SAMICore_PropertyId_Denoise_V2_Rate,
    SAMICore_PropertyId_Denoise_V2_Mode,

    // speech recognition
    SAMICore_PropertyId_SpeechRecognition = 1500,
    SAMICore_PropertyId_SpeechRecognition_Reset,
    SAMICore_PropertyId_SpeechRecognition_Finish,
    SAMICore_PropertyId_SpeechRecognition_UseWordInfo,
    SAMICore_PropertyId_SpeechRecognition_Resume,
    SAMICore_PropertyId_SpeechRecognition_UpdateRange,

    //ASR
    SAMICore_PropertyID_ASR_Offline,
    SAMICore_PropertyID_ASR_Offline_Set_Parameters,
    SAMICore_PropertyID_ASR_Offline_Rest_Executor,
    SAMICore_PropertyID_ASR_Offline_Finish,
    SAMICore_PropertyID_ASR_Offline_Finish_Result,

    SAMICore_PropertyId_ASR_Online_Reset_Recognition = 1700,
    SAMICore_PropertyID_Stream_TTS_Online_Force_Finish = 1701,
    SAMICore_PropertyID_Stream_TTS_Online_Wait_Stop = 1702,
    SAMICore_PropertyID_Stream_Play_TTS_Online_Force_Finish = 1703,
    SAMICore_PropertyId_ASR_Online_Force_Finish = 1704,
    SAMICore_PropertyId_ASR_Online_Start_Connect = 1705,
    SAMICore_PropertyID_Stream_Play_TTS_Online_Set_TimeStrecher = 1706,

    SAMICore_PropertyId_VC_Online = 1710,
    SAMICore_PropertyId_VC_Online_Open_Loudspeaker,
    SAMICore_PropertyId_VC_Online_Close_Loudspeaker,
    SAMICore_PropertyId_VC_Online_Audio_Start_Play,
    SAMICore_PropertyId_VC_Online_Audio_Stop_Play,
    SAMICore_PropertyId_VC_Online_Audio_Pause_Play,
    SAMICore_PropertyId_VC_Online_Audio_Resume_Play,
    SAMICore_PropertyId_VC_Online_Start_Server,
    SAMICore_PropertyId_VC_Online_Stop_Server,
    SAMICore_PropertyId_VC_Online_Stop_Server_Async,
    SAMICore_PropertyId_VC_Online_Force_Finish_Server,
    SAMICore_PropertyId_VC_Online_Set_Speaker,
    SAMICore_PropertyId_VC_Online_Get_Performance_Event_Tracking,
    SAMICore_PropertyId_VC_Online_Get_Input_Data_Save_File,
    SAMICore_PropertyId_VC_Online_Set_Input_Data_Uri,
    SAMICore_PropertyId_VC_Online_Set_Output_Data_Uri

};

#endif  //SAMI_CORE_SAMICOREPROPERTYIDENUM_H
