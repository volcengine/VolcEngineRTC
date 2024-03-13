//
// Created by LIJING on 2021/12/3.
//

#ifndef SAMI_CORE_OC_SAMICORECALLBACKEVENTTYPE_H
#define SAMI_CORE_OC_SAMICORECALLBACKEVENTTYPE_H

typedef NS_ENUM(NSInteger, SAMICore_CallBackEventType) {
    // tts
    TTS_Started = 0,
    TTS_GetResulted = 1,
    TTS_Finished = 2,
    TTS_Failed = 3,
    TTS_WebSocketStateChanged = 4,
    // vc
    VC_Started = 5,
    VC_GetResulted = 6,
    VC_Finished = 7,
    VC_Failed = 8,
    VC_WebSocketStateChanged = 9,
    VC_Player_Finished = 10,

    // asr
    ASR_Started = 100,
    ASR_GetResulted = 101,
    ASR_Finished = 102,
    ASR_Failed = 103,
    ASR_WebSocketStateChanged = 104
};

#endif  //SAMI_CORE_OC_SAMICORECALLBACKEVENTTYPE_H
