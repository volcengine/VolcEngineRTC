//
// Created by xiangning zhu on 2021/1/11.
//

#ifndef SAMI_CORE_DEF_H
#define SAMI_CORE_DEF_H

#ifdef __cplusplus
#define SAMI_CORE_EXTERN_C_BEGIN extern "C" {
#define SAMI_CORE_EXTERN_C_END   }
#else
#define SAMI_CORE_EXTERN_C_BEGIN
#define SAMI_CORE_EXTERN_C_END
#endif

#ifdef _WIN32
#ifdef SAMI_CORE_WIN_EXPORT
#define SAMI_CORE_DLL_EXPORT __declspec(dllexport)
#else
#define SAMI_CORE_DLL_EXPORT __declspec(dllimport)
#endif
#else
#define SAMI_CORE_DLL_EXPORT __attribute__((visibility("default")))
#endif
SAMI_CORE_EXTERN_C_BEGIN

#if __cplusplus >= 201103L
#define SAMI_CORE_NON_EXCEPTION noexcept
#else
#define SAMI_CORE_NON_EXCEPTION
#endif  // __cplusplus >= 201103L

#include "sami_core_asr_def.h"
#include "sami_core_auth_check.h"
#include "sami_core_base_def.h"
#include "sami_core_device_register.h"
#include "sami_core_effect_param.h"
#include "sami_core_error_code.h"
#include "sami_core_mdss_def.h"
#include "sami_core_voice_filter_def.h"
#include "sami_core_yggdrasil_def.h"

/*************Base****************/
typedef enum SAMI_CORE_DLL_EXPORT logLevel {
    Debug = 4,
    Error = 16,
    Warning = 32,
    Info = 128,
} SAMICoreLogLevel;

typedef enum SAMI_CORE_DLL_EXPORT binaryType { binaryTypeFile, binaryTypeData } SAMICoreBinaryType;

/**
 * @brief struct for get set params, or call some method
 * @param type      dataType of the property, @see SAMICoreDataType
 * @param id        propertyId ,used to identify what function is called, @see SAMICorePropertyId
 * @param writable  whether the data could be modified, 0 : can't modify 1: can modified
 * @param data      Can be any data address, determined by type
 * @param dataLen   byte Size of that type of data
 * @param extraInfo Additional configuration information to indicate what kind of information
 *                   you want to get when getting information
 */
typedef struct SAMI_CORE_DLL_EXPORT property {
    SAMICoreDataType type;
    SAMICorePropertyId id;
    int writable;
    void* data;
    unsigned int dataLen;
    const char* extraInfo;
} SAMICoreProperty;

typedef struct SAMI_CORE_DLL_EXPORT properties {
    SAMICoreProperty* data;
    unsigned int dataLen;
} SAMICorePropertySet;

typedef struct audioBuffer SAMICoreAudioBuffer;

typedef struct SAMICoreExtendAudioBuffer {
    SAMICoreAudioBuffer samiCoreAudioBuffer;
    bool isLastFrame;
} SAMICoreExtendAudioBuffer;

/*****************************/

/***********Extractor*************/
// use for creating extractor
typedef struct SAMI_CORE_DLL_EXPORT extractorCreateParameter {
    unsigned int sampleRate;
    unsigned int numChannel;
} SAMICoreExtractorCreateParam;


typedef struct SAMI_CORE_DLL_EXPORT aedS2sExtractorCreateParameter {
    const char* fileDir;
    const char* modelDir;
    const char* configDir;
    const char* businessType;
    float threshold;
} SAMICoreAedS2sExtractorCreateParameter;

typedef struct SAMI_CORE_DLL_EXPORT vadS2sExtractorCreateParameter {
    const char* fileDir;
    float threshold;
} SAMICoreVadS2sExtractorCreateParameter;

//
typedef struct SAMI_CORE_DLL_EXPORT extractorParameter {
    char* name;
    char* strValue;
    float floatValue;
} SAMICoreExtractorParam;
/*****************************/

/***********Processor*************/
typedef struct SAMI_CORE_DLL_EXPORT audioProcessorParameter {
    int index;
    char name[128];
    float plainValue;
    float minPlainValue;
    float maxPlainValue;
    float scalingPower;
    int type;
    int scalingMode;
} SAMICoreProcessorParameter;
/*****************************/

/***********Processor*************/
typedef struct SAMI_CORE_DLL_EXPORT audioProcessorPrepareParameter {
    unsigned int sampleRate;
    unsigned int blockSize;
} SAMICoreProcessorPrepareParameter;
/*****************************/

typedef struct feature {
    float time;
    float duration;
    float* values;
    unsigned int numValues;
} SAMICoreFeature;

typedef struct featureArray {
    SAMICoreFeature* array;
    unsigned int numFeatures;
    unsigned int featureID;
} SAMICoreFeatureArray;

typedef struct featureSet {
    int numFeatureTypes;
    SAMICoreFeatureArray* set;
} SAMICoreFeatureSet;

/***********3A&Audio processor*************/
typedef struct SAMI_CORE_DLL_EXPORT audio3ACreateParameter {
    unsigned int sampleRate;
    unsigned int channels;
} SAMICore3ACreateParameter;

typedef struct audio3ACreateParameter SAMICoreAudioCommonParameter;

typedef struct SAMI_CORE_DLL_EXPORT audio3ASeekParameter {
    unsigned int pos;
    unsigned int mod;
} SAMICore3ASeekParameter;

typedef struct aecInput {
    SAMICoreAudioBuffer* ref;
    SAMICoreAudioBuffer* mic;
} SAMICoreAecInput;

typedef struct loudnormProperty {
    float source_lufs;
    float source_peak;
    float target_lufs;
} SAMICoreLoudnormProperty;

typedef struct loudnorm2Property {
    float target_lufs;
} SAMICoreLoudnorm2Property;

typedef struct cherEffectProperty {
    float major;
    float seek_position;
} SAMICoreCherEffectProperty;

typedef struct AudioEffectCompressorProperty {
    float pre_gain;
    float threshold;
    float knee;
    float ratio;
    float attack;
    float release;
    float pre_delay;
    float release_zone_1;
    float release_zone_2;
    float release_zone_3;
    float release_zone_4;
    float post_gain;
    float wet;
    float attenuation_dB_thd;
    float detector_avg_thd;
} SAMICoreAudioEffectCompressorProperty;

/**
 * gate: range:[0.0, 1.0] default:0.9999
 * pregain_dB: range:[-100, 100] default:0
 */
typedef struct climiterProperty {
    float gate;
    float pregain_dB;
    bool isUpdateGate;
    bool isUpdatePregaindB;
} SAMICoreClimiterProperty;

/**
 * clip_mode: range:[ENHANCE_NO_CLIP, REDUCE_SCALE_NO_CLIP, SOFT_CLIP, SOFT_CLIP_WITH_LIMITER, HARD_CLIP] default:ENHANCE_NO_CLIP
 * adjust_gain: range:[0.0, 1.0] default:0.0
 * contrast: range:[0.0, 0.1], dafault:0.0
 * peak: range:[0.0, 1.0] default:1.0
 * RMSMax: range:[-20, 10] default:-5.0
 * attack_time: range:[0.0, 1.0] default:0.0401642
 * release_time: range:[0.0, 1.0] default:0.743039
 */
typedef struct loudnessProperty {
    float clip_mode;
    float adjust_gain;
    float contrast;
    float peak;
    float RMSMax;
    float attack_time;
    float release_time;
    bool isUpdateClipMode;
    bool isUpdateAdjustGain;
    bool isUpdateContrast;
    bool isUpdatePeak;
    bool isUpdateRMSMax;
    bool isUpdateAttackTime;
    bool isUpdateReleaseTime;
} SAMICoreLoudnessProperty;

typedef struct audioFadingProperty {
    float content_duration;
    float fade_in_duration;
    float fade_out_duration;
    float curve_fadein;
    float curve_fadeout;
} SAMICoreAudioFadingProperty;

/*****************************/

/*********time scaler**********/
typedef struct SAMI_CORE_DLL_EXPORT audioTimeScalerCreateParameter {
    unsigned int sampleRate;
    unsigned int channels;
} SAMICoreTimeScalerCreateParameter;
/*****************************/

/*********pitch shifter**********/
typedef struct SAMI_CORE_DLL_EXPORT audioPitchShifterCreateParameter {
    unsigned int sampleRate;
    unsigned int channels;
} SAMICorePitchShifterCreateParameter;
/*****************************/

/*********audio scratcher**********/
typedef struct SAMI_CORE_DLL_EXPORT audioScratcherCreateParameter {
    unsigned int sampleRate;
    unsigned int channels;
} SAMICoreAudioScratcherCreateParameter;
/*****************************/

/*********time stretcher**********/
typedef struct SAMI_CORE_DLL_EXPORT timeStretcherCreateParameter {
    unsigned int sampleRate;
    unsigned int channels;
    float scale;
    bool reservingPitch;
} SAMICoreTimeStretcherCreateParameter;

typedef struct SAMI_CORE_DLL_EXPORT timeStretcherProperty {
    float scale;
    bool reservingPitch;
} SAMICoreTimeStretcherProperty;
/*****************************/

/*********audio retarget**********/
/**
 * this struct use to set retarget inout params
 * @param in_audio_path       input audio file path;
 * @param out_audio_path      output audio file path;
 * @param loop_info_path      input file beatinfo json file path;
 * @param target_sec          target total time_sec when process finished
 * @param range_start_sec     start time in input audiofile
 * @param range_end_sec       end time in input audiofile
 * @param process_mode        run mode;@see AudioRetargetProcessMode
 * @param splice_info_jsonstr splice info
 * @param loop_num_limit      the maximum repeat times for one loop
 * @param bussinessInfo       bussiness info
 * @param original_beginning  generate output with the beginning of original audio or not
 */
typedef enum SAMI_CORE_DLL_EXPORT audioRetargetProcessMode {
    audioRetaretModeAudioInOut = 0,    /*< input audiofile ,output retargeted audiofile*/
    audioRetaretModeGetSplice = 1,     /*< input audiofile ,output retargted splice json strings*/
    audioRetaretModeSpliceAudioOut = 2 /* input audiofile and splice json str ,output audio file*/
} AudioRetargetProcessMode;
typedef struct SAMI_CORE_DLL_EXPORT audioRetargetInOutInfoParameter {
    const char* in_audio_path;
    const char* out_audio_path;
    const char* loop_info_path;
    float target_sec;
    float range_start_sec;
    float range_end_sec;
    AudioRetargetProcessMode process_mode;
    const char* splice_info_jsonstr;
    int loop_num_limit;
    int sampleRate;
    int numChannel;
    const char* bussinessInfo;
    bool original_beginning;
} SAMICoreAudioRetargetInOutInfoParameter;

typedef void (*SAMICoreCallbackMethod_AudioRetargetOnProgress)(float progress, void* pUser);
typedef void (*SAMICoreCallbackMethod_AudioRetargetOnFinish)(bool success, void* pUser);
typedef void (*SAMICoreCallbackMethod_AudioRetargetOnCancelled)(void* pUser);
/**
 * this struct use to set retarget process callbacks
 */
typedef struct SAMI_CORE_DLL_EXPORT audioRetargetCallBackParameter {
    SAMICoreCallbackMethod_AudioRetargetOnProgress onProgress;
    SAMICoreCallbackMethod_AudioRetargetOnFinish onFinish;
    SAMICoreCallbackMethod_AudioRetargetOnCancelled onCancelled;
    void* userParam;
} SAMICoreAudioRetargetCallBackParameter;

/*****************************/

/*********time align**********/
typedef SAMICoreAecInput SAMICoreTimeAlignParameter;
/**
 * Used for MulTimeAlign and TimeDomainReAlign
 * @param offsetMS The offset from the reference audio
 * @param alignState Whether it can be aligned，
 * @param refSeekPosMS  The Seek POS for reference audio for TimeDomain ReAlign
 * @param curSeekPosMS  The Seek POS for current audio for TimeDomain ReAlign
 * */
typedef struct multiTimeAlignResult {
    float offsetMS;
    int alignState;
    float refSeekPosMS;
    float curSeekPosMS;
} SAMICoreMultiTimeAlignResult;

typedef SAMICoreAecInput SAMICoreTimeDomainReAlignParameter;

typedef struct loudnessStrategyParameter {
    // from Vcould
    const char* metaData;
    // from libra (will be removed after adding sdk ab testing)
    const char* libraData;
    // from business
    float durarion;
    int channels;
    // from client UI
    int device_playback_ability;
    bool panorama_switch;
} SAMICoreLoudnessStrategyParameter;

/*****************************/
/**
 * this struct used for creating context handle, @see SAMICoreIdentify_Processor_ContextWithString @see
 SAMICoreIdentify_Processor_ContextWithFileName
 * here is a small example:
 *
 * @code
 * const char* json_path = "/path/to/json/a.json";
 * SAMICoreContextCreateParameter create_param;
 * create_param.input = json;
 * create_param.resource_paths = NULL;
 * create_param.num_paths = 0;
 *
 * int ret = SAMICoreCreateHandleByIdentify(
 *              &handle, SAMICoreIdentify::SAMICoreIdentify_Processor_ContextWithFileName,
 *              &create_param);
 *
 * @endcode
 *
 * if there are resource paths that needs oto set, then you can write link this:
 * @code
 * SAMICoreContextCreateParameter create_param;
 * const char* json_path = "/path/to/json/a.json";
 * const char* path0 = {"./"};
 * const char* path1 = {"../"};
 * vector<const char*> paths{path0, path1};
 *
 * create_param.resource_paths = paths.data();
 * create_param.num_paths = 2;
 *
 * int ret = SAMICoreCreateHandleByIdentify(
                &handle, SAMICoreIdentify::SAMICoreIdentify_Processor_ContextWithFileName,
                (void *)(&create_param));
 *
 * @endcode
 */
typedef struct SAMI_CORE_DLL_EXPORT resourceParameter {
    /**
     * input json file path or json string, depends on which identity used
     *  1. SAMICoreIdentify_Processor_ContextWithStringWithResourcePaths, 'input' must be json string
     *  2. SAMICoreIdentify_Processor_ContextWithFileNameWithResourcePaths, 'input' must be json file path
     */
    const char* input;

    /**
     * number of resource search paths, can be 0 if there is no resource search paths
     */
    int numPaths;

    /**
     * resource search paths, is a string array.
     * the context use these paths to find resources it needed
     */
    const char** resourcePaths;

    /**
    * duration of input audio(sec).
    * used in automation
    */
    float duration;
    /*
     * custom param
     */
    void* settingParams;
} SAMICoreResourceParameter;

/*********engine**********/
typedef struct SAMI_CORE_DLL_EXPORT engineCreateParameter {
    const char* resourcePath;
    int sampleRate;
} SAMICoreEngineCreateParameter;

typedef enum SAMI_CORE_DLL_EXPORT executorTaskType {
    TIME_ALIGN_MODEL = 0,
} SAMICoreExecutorTaskType;

typedef struct SAMI_CORE_DLL_EXPORT executorCreateParameter {
    void* engineHandle;
    int sampleRate;
    SAMICoreExecutorTaskType taskType;
    int outputNum;
} SAMICoreExecutorCreateParameter;

typedef struct SAMI_CORE_DLL_EXPORT executorContextCreateParameter {
    int sampleRate;
    int maxBlockSize;
    const char* modelBuffer;
    int modelLen;
    int numChannel;
    const char* bussinessInfo;
    const char* configInfo;
    int numAudioBuffer;
} SAMICoreExecutorContextCreateParameter;

typedef struct SAMI_CORE_DLL_EXPORT ExecutorContextCreateVCParameter {
    int sampleRate;
    int numChannel;
    int maxBlockSize;
    const char* encoderModelBuffer;
    long long encoderModelLen;
    const char* timbreModelBuffer;
    long long timbreModelLen;
    const char* vadModelBuffer;
    long long vadModelLen;
} SAMICoreExecutorContextCreateVCParameter;

typedef struct SAMI_CORE_DLL_EXPORT executorContextCreateKWSParameter {
    int sampleRate;
    int maxBlockSize;
    const char* language;
    const char* modelBuffer;
    int modelLen;
    int numChannel;
} SAMICoreExecutorContextCreateKWSParameter;

typedef struct SAMI_CORE_DLL_EXPORT binaryContextCreateParameter {
    SAMICoreBinaryType type;
    void* data;
    int dataLen;
} SAMICoreBinaryContextCreateParameter;

typedef SAMICoreBinaryContextCreateParameter SAMICoreBinaryContextUpdateParameter;

typedef struct SAMI_CORE_DLL_EXPORT parameterEvent {
    int portIndex;
    int parameterIndex;
    float normalizedValue;
    float plainValue;
    const char* processorName;
} SAMICoreContextParameterEvent;

typedef struct SAMI_CORE_DLL_EXPORT jsonContextCreateParameter {
    int sampleRate;
    int maxBlockSize;
    const char* modelBuffer;
    int modelLen;
    int numChannel;
    const char* json_string;
} SAMICoreJSONContextCreateParameter;

typedef struct SAMI_CORE_DLL_EXPORT tuneToTargetCreateParameter {
    int sampleRate;
    const char* midiPath;
    float shift;
    float lag;
} SAMICoreTuneToTargetCreateParameter;

typedef struct wakeupWordResult {
    char* wakeupWorld;
    float score;
    int startTime;
    int stopTime;
} SAMICoreWakeupWordResult;

/***************** Server API ******************************/
typedef struct audioConfig {
    int sampleRate;
    const char* format;
    int channel;
} SAMICoreAudioConfig;

typedef struct speechToSongContextCreateParameter {
    const char* url;
    const char* appKey;
    SAMICoreTokenType tokenType;
    const char* token;
    const char* audioUrl;
    const char* audioUrlType;
    const char* authPolicyHeader;  // json string {key:value}
    int responseType;
    int videoStatus;
    // const char* audio_info;
    const char* extra;
    //    const char* format;
    //    int sampleRate;
    //    int channel;
    int connect_timeout;
    long timeStamp;
    const char* envType; // prod by default
    const char* env;
} SAMICoreSpeechToSongContextCreateParameter;

typedef struct vcContextCreateParameter {
    const char* url;
    const char* header;
    const char* appKey;
    int connectTimeout;
    SAMICoreTokenType tokenType;
    const char* token;
    long timestamp;
    //    const char* speaker;
    //    SAMICoreAudioConfig* inputAudioConfig;
    //    SAMICoreAudioConfig* outputAudioConfig;
    bool enableAudioCache;
    int audioCacheSize;
    const char* saveFileDir;
    SAMICoreServerCallbackParameter* callbackParameter;
} SAMICoreVcContextCreateParameter;

typedef struct vcSpeakerParameter {
    const char* speaker;
    SAMICoreAudioConfig* inputAudioConfig;
    SAMICoreAudioConfig* outputAudioConfig;
    bool enableSaveInputAudioData;
    bool enableSaveOutputAudioData;
    bool enableBackground;
    bool enablePlaying;
    int playerCacheTime;
} SAMICoreVcSpeakerParameter;

typedef enum SAMI_CORE_DLL_EXPORT dataUriType {
    SAMICore_AUDIO_BINARY_DATA = 0,
    SAMICore_AUDIO_BINARY_FILE = 1,
    SAMICore_AUDIO_VCLOUD_VID = 2,
    SAMICore_AUDIO_VCLOUD_URL_PUBLIC = 3,
    SAMICore_AUDIO_VCLOUD_URL_PRIVATE = 4,
    SAMICore_AUDIO_VCLOUD_VID_AND_PUBLIC_URL = 5,   // just for output
    SAMICore_AUDIO_VCLOUD_VID_AND_PRIVATE_URL = 6,  // just for output
} SAMICoreDataUriType;

typedef struct SAMI_CORE_DLL_EXPORT dataUriParameter {
    SAMICoreDataUriType uriType;
    const char** uris;
    int uriSize;
    const char* authPolicy;         // return private url policy_session/policy_header
    const char* authPolicyHeader;   // json string {key:value}
} SAMICoreDataUriParameter;

typedef struct vcResult{
    char* data;
    int dataLength;
} SAMICoreVcResult;

typedef struct speechDisfluencyCreateParameter {
    SAMICoreServerCommonParameter commonParameter;
} SAMICoreSpeechDisfluencyContextCreateParameter;

typedef struct speechDisfluencyResult {
    char* result;
} SAMICoreSpeechDisfluencyResult;

typedef struct ttsContextCreateParameter {
    const char* url;
    int connectTimeout;
    const char* appKey;
    SAMICoreTokenType tokenType;
    const char* token;
    const char* speaker;
    const char* format;
    const char* textType;
    const char* text;
    bool enableConcurrency;
    bool enableSentenceSeg;
    long timestamp;
    int sampleRate;
    int speechRate;
    int pitchRate;
    bool enableTimestamp;
    int silenceDuration;
    bool enableNetTransportCompress;
    int bitRate;
    bool enableSaveAudioToFile;
    const char* saveFileDir;
    SAMICoreServerCallbackParameter* callbackParameter;
    bool enable_split;
} SAMICoreTtsContextCreateParameter;

typedef struct ttsProcessParameter {
    const char* speaker;
    const char* textType;
    const char* text;
    bool enableConcurrency;
    bool enableSentenceSeg;
    int sampleRate;
    long timestamp;
    bool enablePlaying;
    bool enableSaveAudioToFile;
} SAMICoreTtsProcessParameter;

typedef struct ttsResult {
    float duration;
    char* phonemeAlignment;
    char* wordAlignment;
    char* data;
    int dataLength;
} SAMICoreTtsResult;

typedef struct LyricsAlignmentContextCreateParameter {
    const char* url;
    const char* appKey;
    const char* token;
    const char* lrcLang;
} SAMICoreLyricsAlignmentContextCreateParameter;

typedef struct LyricsAlignmentResult {
    char* krc_result;
    int len;
} SAMICoreLyricsAlignmentResult;

typedef struct beatTrackingContextCreateParameter {
    SAMICoreServerCommonParameter commonParameter;
    bool groupResult;
} SAMICoreBTContextCreateParameter;

typedef struct beatTrackingResult {
    char* result;
} SAMICoreBeatTrackingResult;

typedef struct musicSourceSeparateContextParameter {
    SAMICoreServerCommonParameter commonParameter;
    const char* model;  // vocal/acc
    const char* outputFormat;
    int outputSampleRate;
    int outputChannel;
} SAMICoreMusicSourceSeparateContextParameter;

typedef struct musicSourceSeparateResult {
    char* data;
    int dataLength;
} SAMICoreMusicSourceSeparateResult;

typedef struct musicTaggingContextParameter {
    SAMICoreServerCommonParameter commonParameter;
    bool enableTag;
    int topNum;
} SAMICoreMusicTaggingContextParameter;

typedef struct musicTaggingResult {
    char* result;
} SAMICoreMusicTaggingResult;

typedef struct chorusContextParameter {
    SAMICoreServerCommonParameter commonParameter;
} SAMICoreChorusContextParameter;

typedef struct chorusResult {
    char* result;
} SAMICoreChorusResult;

typedef struct musicRetargetContextParameter {
    SAMICoreServerCommonParameter commonParameter;
    bool stamp;
    int targetSecs;
} SAMICoreMusicRetargetContextParameter;

typedef struct musicRetargetResult {
    char* result;
} SAMICoreMusicRetargetResult;

typedef struct midiContextParameter {
    SAMICoreServerCommonParameter commonParameter;
    bool midi;
} SAMICoreMidiContextParameter;

typedef struct beamformingCreateParameter {
    char* mic_positions;
    int numMic;
    int sampleRate;
    int chunkSizeMs;
} SAMICoreBeamformingCreateParameter;

typedef struct midiResult {
    char* jsonResult;
    char* data;
    int dataLength;
} SAMICoreMidiResult;

struct SAMICoreServerEvent {
    char* event;
    int statusCode;
    char* statusText;
    char* taskId;
    char* messageId;
    char* textMsg;
    char* binaryData;
    int binaryDateLen;
};

typedef struct byteTunerContextCreateParameter {
    SAMICoreServerCommonParameter commonParameter;
    float shiftSecond;
    int shiftSemitone;
    float lag;
    long timestamp;
    const char* midiPath;
    const char* vocalPath;
    const char* tunedPath;
    SAMICoreServerCallbackParameter* callbackParameter;
} SAMICoreByteTunerContextCreateParameter;

enum SAMICoreWebSocketConnectionState {
    ConnectionState_ConnectUnknown = -1,
    ConnectionState_Connecting,     // 0
    ConnectionState_Disconnecting,  // 1
    ConnectionState_ConnectFailed,  // 2
    ConnectionState_ConnectClosed,  // 3
    ConnectionState_Connected,      // 4
};

struct SAMICoreWebSocketConnectionEvent {
    SAMICoreWebSocketConnectionState state;
    char* url;
    char* textMsg;
};

typedef struct VopRequestContextParameter{
    const char* url;
    const char* appKey;
    const char* token;
    SAMICoreTokenType tokenType;
    int connect_timeout;

    const char* accessKey;
    const char* userId;
    const char* taskId;
    const char* messageId;
    const char* modelId;
    const char* eventName;
    const char* meta_version;
} SAMICoreVopRequestContextParameter;


/*****************************/

/************** Audio Encode ****************/
typedef enum SAMI_CORE_DLL_EXPORT audioFormat {
    PCM = 0,
    WAV = 1,
    AAC = 2,
    OPUS = 3,
    OGG_OPUS = 4,
} SAMICoreAudioFormat;

struct SAMICoreAudioEncodeContextParameter {
    int sample_rate;
    int channel;
    SAMICoreAudioFormat input_format;
    SAMICoreAudioFormat output_format;
    const char* output_path;
    int bit_rate;
    int complex;
};

struct SAMICoreAudioDecodeContextParameter {
    int sample_rate;
    int channel;
    SAMICoreAudioFormat input_format;
    SAMICoreAudioFormat output_format;
    const char* output_path;
};

typedef struct DebugConfig {
    const char* dumpPath;
    const char* fileNamePrefix;
    int sample_rate;
    int channel;
} SAMICoreDebugConfig;

// ab context
typedef bool (*SAMICoreCallbackMethod_AbGetStringValue) (const char*, char*, int*, int, void* params);
typedef bool (*SAMICoreCallbackMethod_AbGetIntValue) (const char*, int*, void* params);
typedef bool (*SAMICoreCallbackMethod_AbGetBoolValue) (const char*, bool*, void* params);
typedef bool (*SAMICoreCallbackMethod_AbGetFloatValue) (const char*, float*, void* params);
typedef bool (*SAMICoreCallbackMethod_AbGetConfig) (const char*, void*, void* params, int dataType);

typedef struct abContextCreateParameter {
    SAMICoreCallbackMethod_AbGetIntValue getInt;
    SAMICoreCallbackMethod_AbGetFloatValue getFloat;
    SAMICoreCallbackMethod_AbGetStringValue getString;
    SAMICoreCallbackMethod_AbGetBoolValue getBool;
    SAMICoreCallbackMethod_AbGetConfig getAbConfig;
    void* userParam;
} SAMICoreAbContextCreateParameter;

SAMI_CORE_EXTERN_C_END
#endif  // SAMI_CORE_DEF_H
