//
//  bef_effect_ai_animoji.h
//  effect-sdk
//
//  Created by bytedance on 2020/11/13.
//

#ifndef bef_effect_ai_animoji_h
#define bef_effect_ai_animoji_h


#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"
#include "bef_effect_ai_face_detect.h"

#define BEF_AI_AM_E_DIM 52
#define BEF_AI_AM_U_DIM 75
#define BEF_AI_ANIMOJI_MAX_FACE_COUNT 10
typedef unsigned long bef_ai_animoji_handle;

/**
 @brief animoji 检测结果
 */
typedef struct bef_ai_animoji_info {
  float alpha[BEF_AI_AM_U_DIM];
  float beta[BEF_AI_AM_E_DIM];
  float landmarks[240*2];
  float rot[3];
  float mvp[16];
  float mv[16];
  float affine_mat[9];
  int succ;                         // 是否检测成功
  int face_id;                      // 人脸 id
} bef_ai_animoji_info;

BEF_SDK_API
bef_effect_result_t bef_effect_ai_animoji_create(bef_ai_animoji_handle *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_animoji_check_license(bef_ai_animoji_handle handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_animoji_check_online_license(bef_ai_animoji_handle handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_animoji_set_model(bef_ai_animoji_handle handle, const char *modelPath, int inputWidth, int inputHeight);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_animoji_detect(bef_ai_animoji_handle handle,
                                            const unsigned char *image,
                                            bef_ai_pixel_format pixelFormat,
                                            int imageWidth,
                                            int imageHeight,
                                            int imageStride,
                                            bef_ai_rotate_type rotation,
                                            bef_ai_animoji_info *result);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_animoji_detect_with_face(bef_ai_animoji_handle handle,
                                            const unsigned char *image,
                                            bef_ai_pixel_format pixelFormat,
                                            int imageWidth,
                                            int imageHeight,
                                            int imageStride,
                                            bef_ai_rotate_type rotation,
                                            int faceCount,
                                            int id[BEF_AI_ANIMOJI_MAX_FACE_COUNT],
                                            float landmark106[BEF_AI_ANIMOJI_MAX_FACE_COUNT][212],
                                            bef_ai_animoji_info *result);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_animoji_set_escale(bef_ai_animoji_handle handle, int escale);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_animoji_release(bef_ai_animoji_handle handle);

#endif /* bef_effect_ai_animoji_h */
