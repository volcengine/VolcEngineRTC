
#ifndef _BEF_EFFECT_HEADSEG_AI_H
#define _BEF_EFFECT_HEADSEG_AI_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"
#define HS_FACE_KEY_POINT_NUM 106
typedef long long bef_ai_headseg_handle;

typedef struct
{
    int net_input_width; //网络输入的大小
    int net_input_height;
} bef_ai_headseg_config;

typedef struct
{
    int face_id;
    bef_ai_fpoint points[HS_FACE_KEY_POINT_NUM];
} bef_ai_headseg_faceinfo;

typedef struct
{
    int face_id;
    unsigned char* alpha;
    unsigned char* crop;
    int width;
    int height;
    int channel;
    double matrix[6];
} bef_ai_headseg_face_result;

typedef struct
{
    unsigned char* image;
    int image_width;
    int image_height;
    int image_stride;
    bef_ai_pixel_format pixel_format; // kPixelFormat_BGRA8888 或者 kPixelFormat_RGBA8888
    bef_ai_rotate_type orient;
    bef_ai_headseg_faceinfo* face_info;
    int face_count;
} bef_ai_headseg_input;

typedef struct
{
    bef_ai_headseg_face_result* face_result;
    int face_count;
} bef_ai_headseg_output;

typedef enum
{
    BEF_AI_HS_ENABLE_TRACKING = 1, // default set to 1 传递true 用于 防抖
    BEF_AI_HS_MAX_FACE = 2,
} bef_ai_headseg_paramtype;

BEF_SDK_API
int BEF_AI_HSeg_CreateHandler(bef_ai_headseg_handle* out);

BEF_SDK_API
int BEF_AI_HSeg_CheckLicense(bef_ai_headseg_handle handle, const char* licensePath);

BEF_SDK_API
int BEF_AI_HSeg_CheckOnlineLicense(bef_ai_headseg_handle handle, const char* licensePath);

//设置网络输入参数
BEF_SDK_API
int BEF_AI_HSeg_SetConfig(bef_ai_headseg_handle handle, bef_ai_headseg_config* config);

//设置模型参数
BEF_SDK_API
int BEF_AI_HSeg_SetModelFromBuff(bef_ai_headseg_handle handle,
                          const unsigned char* param,
                          unsigned int param_len);

//设置模块参数
BEF_SDK_API
int BEF_AI_HSeg_SetParam(bef_ai_headseg_handle handle, bef_ai_headseg_paramtype type, float value);

BEF_SDK_API
// int HS_InitModel(HeadSegHandle handle, const char* param);
int BEF_AI_HSeg_InitModel(bef_ai_headseg_handle handle, const char* param_path);

BEF_SDK_API
int BEF_AI_HSeg_DoHeadSeg(bef_ai_headseg_handle handle,
                   bef_ai_headseg_input* input,
                   bef_ai_headseg_output* output);

BEF_SDK_API
int BEF_AI_HSeg_ReleaseHandle(bef_ai_headseg_handle handle);

#endif // _BEF_EFFECT_HEADSEG_AI_H
