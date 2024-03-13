//
// Created by xiangning zhu on 2022/1/4.
//

#ifndef SAMI_CORE_SAMI_CORE_ASR_DEF_H
#define SAMI_CORE_SAMI_CORE_ASR_DEF_H

#include "sami_core_auth_check.h"
#include "sami_core_base_def.h"
// server callback
typedef void (*SAMICoreServerCallbackMethod)(SAMICoreBlock*, void*);

typedef struct serverCallbackParameter {
    SAMICoreServerCallbackMethod onTaskStarted;
    SAMICoreServerCallbackMethod onTaskFailed;
    SAMICoreServerCallbackMethod onTaskFinished;
    SAMICoreServerCallbackMethod onTaskGetResulted;
    SAMICoreServerCallbackMethod onWebSocketStateChanged;
    SAMICoreServerCallbackMethod onPlayerFinished;
    void* userParam;
} SAMICoreServerCallbackParameter;

typedef struct serverCommonParameter {
    const char* url;
    const char* appKey;
    SAMICoreTokenType tokenType;
    const char* token;
    const char* format;
    int sampleRate;
    int channel;
    int connect_timeout;
} SAMICoreServerCommonParameter;

typedef struct asrContextCreateParameter {
    SAMICoreServerCommonParameter commonParameter;
    const char* language;
    const char* extra;
    int sos_silence_timeout;
    int eos_silence_timeout;
    int sentence_max_time; // the unit is milli-seconds, different from server protocol
    int enable_punctuation;
    int enable_speaker_diarization;
    const char* model;
    long timestamp;
    int enable_audio_cache;
    int audio_cache_size;
    SAMICoreServerCallbackParameter* callbackParameter;
} SAMICoreAsrContextCreateParameter;

typedef struct asrResult {
    char* result;
} SAMICoreAsrResult;

typedef struct asrAudio {
    char* asrData;
    int asrDataLen;
    char* embeddingData;
    int embeddingDataLen;
} SAMICoreAsrAudio;

#endif  //SAMI_CORE_SAMI_CORE_ASR_DEF_H
