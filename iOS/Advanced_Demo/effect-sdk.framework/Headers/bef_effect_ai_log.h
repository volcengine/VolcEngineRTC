#ifndef _LIC_UTILS_TT_LOG_H_
#define _LIC_UTILS_TT_LOG_H_

#ifdef __ANDROID__
    #include <android/log.h>
#else
    #include <stdio.h>
#endif


#define  BEF_EFFECT_AI_LOG_TAG  "bef_effect_ai "
#ifdef __ANDROID__
    #ifdef DEBUG
        #define LOGCV_I(...)  __android_log_print(ANDROID_LOG_INFO, BEF_EFFECT_AI_LOG_TAG, __VA_ARGS__);
        #define LOGCV_W(...)  __android_log_print(ANDROID_LOG_WARNING, BEF_EFFECT_AI_LOG_TAG, __VA_ARGS__);
        #define LOGCV_D(...)  __android_log_print(ANDROID_LOG_DEBUG, BEF_EFFECT_AI_LOG_TAG, __VA_ARGS__);
        #define LOGCV_E(...)  __android_log_print(ANDROID_LOG_ERROR, BEF_EFFECT_AI_LOG_TAG, __VA_ARGS__);
    #else
        #define LOGCV_I(...)
        #define LOGCV_W(...)
        #define LOGCV_D(...)
        #define LOGCV_E(...)  __android_log_print(ANDROID_LOG_ERROR, BEF_EFFECT_AI_LOG_TAG, __VA_ARGS__);
    #endif
#else
    #ifdef DEBUG
        #define LOGCV_I(...)  printf(BEF_EFFECT_AI_LOG_TAG); printf(__VA_ARGS__)
        #define LOGCV_W(...)  printf(BEF_EFFECT_AI_LOG_TAG); printf(__VA_ARGS__)
        #define LOGCV_D(...)  printf(BEF_EFFECT_AI_LOG_TAG); printf(__VA_ARGS__)
        #define LOGCV_E(...)  fprintf(stderr, BEF_EFFECT_AI_LOG_TAG); fprintf(stderr, __VA_ARGS__)
    #else
        #define LOGCV_I(...)
        #define LOGCV_W(...)
        #define LOGCV_D(...)
        #define LOGCV_E(...)  fprintf(stderr, BEF_EFFECT_AI_LOG_TAG); fprintf(stderr, __VA_ARGS__)
    #endif
#endif

#endif  // _LIC_UTILS_TT_LOG_H_
