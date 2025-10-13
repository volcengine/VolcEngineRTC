#ifndef _LIC_UTILS_TT_LOG_H_
#define _LIC_UTILS_TT_LOG_H_

#ifdef __ANDROID__
    #include <android/log.h>
#else
    #include <stdio.h>
#endif

#include "bef_effect_ai_public_define.h"

BEF_SDK_API void bef_effect_ai_tob_print(int level, const char* logTag, const char *fmt, ...);

#define  BEF_EFFECT_AI_LOG_TAG  "bef_effect_ai "
#ifdef __ANDROID__
    #ifdef DEBUG
        #define LOGCV_I(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_INFO, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
        #define LOGCV_W(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_WARN, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
        #define LOGCV_D(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_DEBUG, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
        #define LOGCV_E(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_ERROR, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
    #else
        #define LOGCV_I(fmt, ...)
        #define LOGCV_W(fmt, ...)
        #define LOGCV_D(fmt, ...)
        #define LOGCV_E(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_ERROR, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
    #endif
#else
    #ifdef DEBUG
        #define LOGCV_I(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_INFO, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
        #define LOGCV_W(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_WARN, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
        #define LOGCV_D(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_DEBUG, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
        #define LOGCV_E(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_ERROR, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
    #else
        #define LOGCV_I(fmt, ...)
        #define LOGCV_W(fmt, ...)
        #define LOGCV_D(fmt, ...)
        #define LOGCV_E(fmt, ...)  bef_effect_ai_tob_print(BEF_AI_LOG_LEVEL_ERROR, BEF_EFFECT_AI_LOG_TAG, fmt, ##__VA_ARGS__);
    #endif
#endif

#endif  // _LIC_UTILS_TT_LOG_H_
