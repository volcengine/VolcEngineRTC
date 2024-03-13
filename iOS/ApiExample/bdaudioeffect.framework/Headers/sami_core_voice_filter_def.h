//
// Created by xiangning zhu on 2021/12/29.
//

#ifndef SAMI_CORE_SAMI_CORE_VOICE_FILTER_DEF_H
#define SAMI_CORE_SAMI_CORE_VOICE_FILTER_DEF_H
typedef struct voiceFilterContextCreateParameter {
    const char* url;
    const char* appKey;
    const char* nameSpace;
    const char* token;
} SAMICoreVoiceFilterContextCreateParameter;

typedef struct voiceFilterDateType{
    const char* model_type;
    const char* wav_chunk;
    int wav_chunk_len;
    const char* embedding;
    int embedding_len;
    const char* hidden_state;
    int hidden_state_len;
    const char* cell_state;
    int cell_state_len;
} SAMICoreVoiceFilterParam;

#endif  //SAMI_CORE_SAMI_CORE_VOICE_FILTER_DEF_H
