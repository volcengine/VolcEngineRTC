//
// Created by LIJING on 2021/11/22.
//

#ifndef SAMI_CORE_SAMICOREDATATYPEENUM_H
#define SAMI_CORE_SAMICOREDATATYPEENUM_H

#import <Foundation/Foundation.h>
#import "SAMICorePropertyId.h"
#import "SAMICoreIdentify.h"
#import "SAMICoreCallBackEventType.h"

typedef NS_ENUM(NSInteger, SAMICore_LogLevel) {
    LogLevel_Debug = 4,
    LogLevel_Error = 16,
    LogLevel_Warning = 32,
    LogLevel_Info = 128,
};

typedef NS_ENUM(NSInteger, SAMICore_DataType) {
    // base
    SAMICore_DataType_Float = 0,
    SAMICore_DataType_Int,
    SAMICore_DataType_String,
    SAMICore_DataType_Double,
    SAMICore_DataType_Long,
    SAMICore_DataType_Null,

    // custom base
    SAMICore_DataType_AudioBuffer = 50,
    SAMICore_DataType_Data_Uri_Parameter = 52,

    // context
    SAMICore_DataType_ContextPrepareParameter = 100,
    SAMICore_DataType_ResourceParameter,
    SAMICore_DataType_ParameterEvent,

    // processor
    SAMICore_DataType_ProcessorParameter = 150,

    // Extractor
    SAMICore_DataType_FeatureSet = 250,
    SAMICore_DataType_ExtractorParameter,

    // model binary
    SAMICore_DataType_ModelBin = 300,

    // aec
    SAMICore_DataType_AecInput = 350,

    // sami engine tts
    SAMICore_DataType_TTSCallBack = 400,
    SAMICore_DataType_EngineCreateParameter,
    SAMICore_DataType_ExecutorCreateParameter,

    // time align
    SAMICore_DataType_TimeAlign = 450,

    //loud norm
    SAMICore_DataType_LoudNorm = 451,
    SAMICore_DataType_LoudNorm2 = 452,

    // server
    SAMICore_DataType_TTS_Result = 500,
    SAMICore_DataType_ASR_Result = 503,
    SAMICore_DataType_AudioBin = 504,
    SAMICore_DataType_BeatTracking_Result = 505,
    SAMICore_DataType_MusicSourceSeparate_Result = 506,
    SAMICore_DataType_MusicTagging_Result = 507,
    SAMICore_DataType_Chorus_Result = 508,
    SAMICore_DataType_MusicRetarget_Result = 509,
    SAMICore_DataType_Midi_Result = 510,
    SAMICore_DataType_Token_Result = 511,
    SAMICore_DataType_SpeechDisfluency_Result = 512,

    // websocket
    SAMICore_DataType_WebSocket_Server_Event = 600,
    SAMICore_DataType_WebSocket_Connection_Event = 601,
    SAMICore_DataType_WebSocket_Tts = 603,
    SAMICore_DataType_WebSocket_Vc = 604,
    SAMICore_DataType_WebSocket_Vc_Speaker = 605,

    // TimeStretcher
    SAMICore_DataType_TimeStretcher_ScaleInfo = 800,

};

@interface SAMICore_Property : NSObject
    @property (nonatomic, assign) SAMICore_DataType type;
    @property (nonatomic, assign) SAMICore_PropertyId id;
    @property (nonatomic, assign) int writable;
    @property (nonatomic, strong) id _Nullable data;
    @property (nonatomic, assign) const char* _Nullable extraInfo;
@end

typedef NS_ENUM(NSInteger, SAMICore_BinaryType) {
    SAMICore_BinaryTypeFile,
    SAMICore_BinaryTypeData
};

@interface SAMICore_ResourceParameter : NSObject
    @property (nonatomic, assign) int sampleRate;
    @property (nonatomic, assign) int maxBlockSize;
    @property (nonatomic, assign) int numChannel;
    /**
     * input json file path or json string, depends on which identity used
     *  1. SAMICore_Identify_Processor_ContextWithStringWithResourcePaths, 'input' must be json string
     *  2. SAMICore_Identify_Processor_ContextWithFileNameWithResourcePaths, 'input' must be json file path
     */
    @property (nonatomic, strong) NSString * _Nullable input;
    /**
     * resource search paths, is a string array.
     * the context use these paths to find resources it needed
     */
    @property (nonatomic, strong) NSArray * _Nullable resourcePaths;
@end

@interface SAMICore_BinaryContextCreateParameter : NSObject
    @property (nonatomic, assign) int sampleRate;
    @property (nonatomic, assign) int maxBlockSize;
    @property (nonatomic, assign) int numChannel;
    @property (nonatomic, assign) SAMICore_BinaryType type;
    @property (nonatomic, assign) void* _Nullable data;
    @property (nonatomic, assign) int dataLen;
@end

@interface SAMICore_BinaryContextUpdateParameter : NSObject
    @property (nonatomic, assign) SAMICore_BinaryType type;
    @property (nonatomic, assign) void* _Nullable data;
    @property (nonatomic, assign) int dataLen;
@end

@interface SAMICore_CreateParameter : NSObject
    @property (nonatomic, assign) int sampleRate;  // sample rate
    @property (nonatomic, assign) int maxBlockSize;  // the maximum number of samples per processing
    @property (nonatomic, assign) char* _Nullable modelBuffer;  // model buffer
    @property (nonatomic, assign) int modelLen;  // the length of model buffer
    @property (nonatomic, assign) int numChannel; // number of channels
    @property (nonatomic, assign) int numAudioBuffer; //number of in buffers
    @property (nonatomic, assign) char* _Nullable jsonConfig; // the extra config
    @property (nonatomic, assign) const char* _Nullable bussinessInfo; // the bussinessInfo
    @property (nonatomic, assign) const char* _Nullable configInfo;    // the configInfo
@end

@interface SAMICore_AudioBuffer : NSObject
    @property (nonatomic, assign) unsigned int numberChannels;
    @property (nonatomic, assign) unsigned int numberSamples;
    @property (nonatomic, assign) int isInterleave;
    @property (nonatomic, assign) void* _Nullable data; // float **

    - (_Nullable instancetype)initWithNumberSamples:(int)samples
                                     numberChannels:(int)cahnnels
                                       isInterleave:(bool)interleave;

    - (void)destroy;
@end

@interface SAMICore_AudioBlock : NSObject
    @property (nonatomic, assign) SAMICore_DataType dataType;
    @property (nonatomic, assign) unsigned int numberAudioData;
    @property (nonatomic, strong) id _Nullable audioData;
@end

@interface SAMICore_AecInput : NSObject
    @property (nonatomic, strong) SAMICore_AudioBuffer* _Nullable ref;
    @property (nonatomic, strong) SAMICore_AudioBuffer* _Nullable mic;

    - (_Nullable instancetype)initWithNumberSamples:(int)samples
                                     numberChannels:(int)channels;

    - (void)destroy;
@end

@protocol SAMICoreCallbackListener <NSObject>
@required
- (void)onMessageReceived:(SAMICore_CallBackEventType)type withBlock:(SAMICore_AudioBlock * _Nullable)block;
@end

typedef NS_ENUM(NSInteger, SAMICore_TokenType) {
    SAMICore_TOKEN_TO_B,
    SAMICore_TOKEN_TO_C_D,
    SAMICore_TOKEN_TO_B_MIXED
};

typedef NS_ENUM(NSInteger, SAMICore_DataUriType) {
    SAMICore_OC_AUDIO_BINARY_DATA = 0,
    SAMICore_OC_AUDIO_BINARY_FILE = 1,
    SAMICore_OC_AUDIO_VCLOUD_VID = 2,
    SAMICore_OC_AUDIO_VCLOUD_URL_PUBLIC = 3,
    SAMICore_OC_AUDIO_VCLOUD_URL_PRIVATE = 4,
    SAMICore_OC_AUDIO_VCLOUD_VID_AND_PUBLIC_URL = 5,   // just for output
    SAMICore_OC_AUDIO_VCLOUD_VID_AND_PRIVATE_URL = 6  // just for output
};

@interface SAMICore_TtsContextCreateParameter : NSObject
    @property (nonatomic, assign) const char* _Nullable url;
    @property (nonatomic, assign) const char* _Nullable appKey;
    @property (nonatomic, assign) SAMICore_TokenType tokenType;
    @property (nonatomic, assign) const char* _Nullable token;
    @property (nonatomic, assign) const char* _Nullable speaker;
    @property (nonatomic, assign) const char* _Nullable format;
    @property (nonatomic, assign) const char* _Nullable textType;
    @property (nonatomic, assign) const char* _Nullable text;
    @property (nonatomic, assign) bool enableConcurrency;
    @property (nonatomic, assign) bool enableSentenceSeg;
    @property (nonatomic, assign) long timestamp;
    @property (nonatomic, assign) int sampleRate;
    @property (nonatomic, assign) int speechRate;
    @property (nonatomic, assign) int pitchRate;
    @property (nonatomic, assign) bool enableTimestamp;
    @property (nonatomic, assign) int silenceDuration;
    @property (nonatomic, assign) bool enableNetTransportCompress;
    @property (nonatomic, assign) int bitRate;
    @property (nonatomic, assign) bool enableSaveAudioToFile;
    @property (nonatomic, assign) const char* _Nullable saveFileDir;
    @property (nonatomic, assign) bool enable_split;
    @property (nonatomic, strong) id<SAMICoreCallbackListener> _Nullable listener;
@end

@interface SAMICore_TtsProcessParameter : NSObject
    @property (nonatomic, assign) const char* _Nullable speaker;
    @property (nonatomic, assign) const char* _Nullable textType;
    @property (nonatomic, assign) const char* _Nullable text;
    @property (nonatomic, assign) bool enableConcurrency;
    @property (nonatomic, assign) bool enableSentenceSeg;
    @property (nonatomic, assign) int sampleRate;
    @property (nonatomic, assign) long timestamp;
    @property (nonatomic, assign) bool enablePlaying;
    @property (nonatomic, assign) bool enableSaveAudioToFile;
@end

@interface SAMICore_AsrContextCreateParameter : NSObject
    @property (nonatomic, assign) const char* _Nullable url;
    @property (nonatomic, assign) const char* _Nullable appKey;
    @property (nonatomic, assign) SAMICore_TokenType tokenType;
    @property (nonatomic, assign) const char* _Nullable token;
    @property (nonatomic, assign) const char* _Nullable format;
    @property (nonatomic, assign) int sampleRate;
    @property (nonatomic, assign) int maxBlockSize;
    @property (nonatomic, assign) int channel;
    @property (nonatomic, assign) const char* _Nullable language;
    @property (nonatomic, assign) const char* _Nullable extra;
    @property (nonatomic, assign) int sos_silence_timeout;
    @property (nonatomic, assign) int eos_silence_timeout;
    @property (nonatomic, assign) int sentence_max_time;
    @property (nonatomic, assign) int enable_punctuation;
    @property (nonatomic, assign) int enable_speaker_diarization;
    @property (nonatomic, assign) long timestamp;
    @property (nonatomic, assign) int connect_timeout;
    @property (nonatomic, assign) int enable_audio_cache;
    @property (nonatomic, assign) int audio_cache_size;
    @property (nonatomic, strong) id<SAMICoreCallbackListener> _Nullable listener;
@end

@interface SAMICore_ServerEvent : NSObject
    @property (nonatomic, strong) NSString* _Nullable event;
    @property (nonatomic, assign) int statusCode;
    @property (nonatomic, strong) NSString* _Nullable statusText;
    @property (nonatomic, strong) NSString* _Nullable taskId;
    @property (nonatomic, strong) NSString* _Nullable messageId;
    @property (nonatomic, strong) NSString* _Nullable textMsg;
    @property (nonatomic, strong) NSData* _Nullable binaryData;
    @property (nonatomic, assign) int binaryDateLen;
@end

typedef NS_ENUM(NSInteger, SAMICore_WebSocketConnectionState) {
    SAMICore_ConnectionState_ConnectUnknown = -1,
    SAMICore_ConnectionState_Connecting,    // 0
    SAMICore_ConnectionState_Disconnecting, // 1
    SAMICore_ConnectionState_ConnectFailed, // 2
    SAMICore_ConnectionState_ConnectClosed, // 3
    SAMICore_ConnectionState_Connected,     // 4
};

@interface SAMICore_WebSocketConnectionEvent : NSObject
    @property (nonatomic, assign) SAMICore_WebSocketConnectionState state;
    @property (nonatomic, strong) NSString* _Nullable url;
    @property (nonatomic, strong) NSString* _Nullable textMsg;
@end

@interface SAMICore_TtsResult : NSObject
    @property (nonatomic, assign) float duration;
    @property (nonatomic, strong) NSString* _Nullable phonemeAlignment;
    @property (nonatomic, strong) NSString* _Nullable wordAlignment;
    @property (nonatomic, strong) NSData* _Nullable data;
    @property (nonatomic, assign) int dataLength;
@end

@interface SAMICore_Feature : NSObject
    @property (nonatomic, assign) float time;
    @property (nonatomic, assign) float duration;
    @property (nonatomic, assign) float* _Nullable values;
    @property (nonatomic, assign) unsigned int numValues;
@end

@interface SAMICore_FeatureArray : NSObject
    @property (nonatomic, strong) NSArray * _Nullable array; // SAMICore_Feature
    @property (nonatomic, assign) unsigned int numFeatures;
    @property (nonatomic, assign) unsigned int featureID;
@end

@interface SAMICore_FeatureSet : NSObject
    @property (nonatomic, assign) int numFeatureTypes;
    @property (nonatomic, strong) NSArray * _Nullable set; // SAMICore_FeatureArray
@end

typedef NS_ENUM(NSInteger, SAMICore_ContextType) {
    SAMICore_ContextType_Lic_Auth = 0,
    SAMICore_TokenVerifyOnlineContext,
    SAMICore_TokenVerifyOfflineContext,
    SAMICore_TokenVerifyMixedContext,
    SAMICore_ContextType_AbConfig
};

@interface SAMICore_TokenVerifyOfflineParameter : NSObject
    @property (nonatomic, strong) NSString* _Nullable appKey;
    @property (nonatomic, strong) NSString* _Nullable token;
    @property (nonatomic, strong) NSString* _Nullable extra;
@end

@interface SAMICore_ContextParameterEvent : NSObject
    @property (nonatomic, assign) int portIndex;
    @property (nonatomic, assign) int parameterIndex;
    @property (nonatomic, assign) float normalizedValue;
    @property (nonatomic, assign) float plainValue;
    @property (nonatomic, strong) NSString* _Nullable processorName;
@end

@interface SAMICore_LoudNormProperty : NSObject
    @property (nonatomic, assign) float source_lufs;
    @property (nonatomic, assign) float source_peak;
    @property (nonatomic, assign) float target_lufs;
@end

@interface SAMICore_LoudNorm2Property : NSObject
    @property (nonatomic, assign) float target_lufs;
@end

@interface SAMICore_TokenResult : NSObject
    @property (nonatomic, strong) NSString* _Nullable token;
    @property (nonatomic, assign) int expiration;
@end

@interface SAMICore_DebugConfig : NSObject
    @property (nonatomic, strong) NSString* _Nullable dumpPath;
    @property (nonatomic, strong) NSString* _Nullable fileNamePrefix;
    @property (nonatomic, assign) unsigned int sampleRate;
    @property (nonatomic, assign) unsigned int numberChannels;
@end

@interface SAMICore_AudioConfig : NSObject
    @property (nonatomic, assign) const char* _Nullable format;
    @property (nonatomic, assign) int sampleRate;
    @property (nonatomic, assign) int channel;
@end

@interface SAMICore_VcContextCreateParameter : NSObject
    @property (nonatomic, assign) const char* _Nullable url;
    @property (nonatomic, assign) const char* _Nullable header;
    @property (nonatomic, assign) const char* _Nullable appKey;
    @property (nonatomic, assign) int connectTimeout;
    @property (nonatomic, assign) SAMICore_TokenType tokenType;
    @property (nonatomic, assign) const char* _Nullable token;
//    @property (nonatomic, assign) const char* _Nullable speaker;
    @property (nonatomic, assign) long timestamp;
    @property (nonatomic, assign) int maxBlockSize;
    @property (nonatomic, assign) bool enableAudioCache;
    @property (nonatomic, assign) int audioCacheSize;
    @property (nonatomic, assign) const char* _Nullable saveFileDir;
//    @property (nonatomic, strong) SAMICore_AudioConfig* _Nullable inputAudioConfig;
//    @property (nonatomic, strong) SAMICore_AudioConfig* _Nullable outputAudioConfig;
    @property (nonatomic, strong) id<SAMICoreCallbackListener> _Nullable listener;
@end

@interface SAMICore_VcSpeakerParameter : NSObject
    @property (nonatomic, assign) const char* _Nullable speaker;
    @property (nonatomic, strong) SAMICore_AudioConfig* _Nullable inputAudioConfig;
    @property (nonatomic, strong) SAMICore_AudioConfig* _Nullable outputAudioConfig;
    @property (nonatomic, assign) bool enableSaveInputAudioData;
    @property (nonatomic, assign) bool enableSaveOutputAudioData;
    @property (nonatomic, assign) bool enableBackground;
    @property (nonatomic, assign) bool enablePlaying;
    @property (nonatomic, assign) int playerCacheTime;
@end

@interface SAMICore_DataUriParameter : NSObject
    @property (nonatomic, assign) SAMICore_DataUriType uriType;
    /**
     * uris is a string array, vid or url list
     */
    @property (nonatomic, strong) NSArray* _Nullable uris;
    @property (nonatomic, strong) NSString* _Nullable authPolicy;
    @property (nonatomic, strong) NSString* _Nullable authPolicyHeader;
@end

@interface SAMICore_TimeStretcherProperty : NSObject
    @property (nonatomic, assign) float scale;
    @property (nonatomic, assign) bool reservingPitch;
@end

@interface SAMICore_AedS2sExtractorCreateParameter : NSObject
    @property (nonatomic, assign) const char* _Nullable fileDir;
    @property (nonatomic, assign) const char* _Nullable modelDir;
    @property (nonatomic, assign) const char* _Nullable configDir;
    @property (nonatomic, assign) const char* _Nullable businessType;
    @property (nonatomic, assign) float threshold;
@end

@interface SAMICore_VadS2sExtractorCreateParameter : NSObject
    @property (nonatomic, assign) const char* _Nullable fileDir;
    @property (nonatomic, assign) float threshold;
@end

@interface SAMICore_ServerContextCreateParameter : NSObject
    @property (nonatomic, assign) const char* _Nullable url;
    @property (nonatomic, assign) const char* _Nullable appKey;
    @property (nonatomic, assign) SAMICore_TokenType tokenType;
    @property (nonatomic, assign) const char* _Nullable token;
    @property (nonatomic, assign) int connectTimeout;
    @property (nonatomic, assign) long timeStamp;
    @property (nonatomic, assign) const char* _Nullable envType;
    @property (nonatomic, assign) const char* _Nullable env;
@end

@interface SAMICore_SpeechToSongContextCreateParameter : SAMICore_ServerContextCreateParameter
    @property (nonatomic, assign) const char* _Nullable audioUrl;
    @property (nonatomic, assign) const char* _Nullable audioUrlType;
    @property (nonatomic, assign) const char* _Nullable authPolicyHeader;
    @property (nonatomic, assign) int responseType;
    @property (nonatomic, assign) int videoStatus;
    @property (nonatomic, assign) const char* _Nullable extra;
@end

typedef bool (*SAMICore_CallbackMethod_AbGetStringValue) (const char* _Nonnull, char* _Nonnull, int* _Nonnull, int, void* _Nullable);
typedef bool (*SAMICore_CallbackMethod_AbGetIntValue) (const char* _Nonnull const, int* _Nonnull, void* _Nullable);
typedef bool (*SAMICore_CallbackMethod_AbGetBoolValue) (const char* _Nonnull, bool* _Nonnull, void* _Nullable);
typedef bool (*SAMICore_CallbackMethod_AbGetFloatValue) (const char* _Nonnull, float* _Nonnull, void* _Nullable);
typedef bool (*SAMICore_CallbackMethod_AbGetConfig) (const char* _Nonnull, void* _Nonnull, void* _Nullable, int dataType);

@interface SAMICore_AbContextCreateParameter : NSObject
    @property (nonatomic, assign) SAMICore_CallbackMethod_AbGetStringValue _Nonnull getString;
    @property (nonatomic, assign) SAMICore_CallbackMethod_AbGetIntValue _Nonnull getInt;
    @property (nonatomic, assign) SAMICore_CallbackMethod_AbGetBoolValue _Nonnull getBool;
    @property (nonatomic, assign) SAMICore_CallbackMethod_AbGetFloatValue _Nonnull getFloat;
    @property (nonatomic, assign) SAMICore_CallbackMethod_AbGetConfig _Nullable getAbConfig;
    // userParam not used in OC.
@end

#endif  //SAMI_CORE_SAMICOREDATATYPEENUM_H
