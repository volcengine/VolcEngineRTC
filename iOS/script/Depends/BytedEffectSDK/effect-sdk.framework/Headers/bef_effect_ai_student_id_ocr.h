#ifndef BEF_EFFECT_AI_STUDENT_ID_OCR_H
#define BEF_EFFECT_AI_STUDENT_ID_OCR_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

typedef unsigned long long bef_ai_student_id_handle;

/**
 * @brief 模型枚举，有些模块可能有多个模型
 *
 */
typedef enum bef_ai_student_id_ocr_model_type {
  BEF_STUDENT_ID_OCR_MODEL = 1,        
} bef_ai_student_id_ocr_model_type;


/**
 * @brief 模型参数类型
 *
 */
typedef enum bef_ai_student_id_orc_param_type
{
  BEF_STUDENT_ID_OCR_EDGE_TYPE = 1,
}bef_ai_student_id_orc_param_type;

/**
 * @brief 封装预测接口的返回值
 *
 * @note 返回识别框的位置和大小
 */
typedef struct bef_student_id_ocr_result {
  int width;                   ///< 识别框的宽度
  int height;                  ///< 识别框的的高度
  int x;                       ///< 识别框的横坐标
  int y;                       ///< 识别框的纵坐标
  int length;                   ///< 识别出来的id的长度
  char* result;                ///< 识别出的id的结果，这个部分的内存算法内部分配，用户在使用后，需要free，以免造成内存泄漏
} bef_student_id_ocr_result;

BEF_SDK_API bef_effect_result_t
bef_effect_ai_student_id_ocr_create_handle(bef_ai_student_id_handle* handle);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_student_id_ocr_init_model(bef_ai_student_id_handle handle,
                                        bef_ai_student_id_ocr_model_type type,
                                        const char* model_path);

// BEF_SDK_API bef_effect_result_t
// bef_effect_ai_student_id_ocr_set_paramf(bef_ai_student_id_handle handle,
//                                         bef_ai_student_id_orc_param_type type,
//                                         float value);
                                    
BEF_SDK_API bef_effect_result_t
bef_effect_ai_student_id_ocr_detect(bef_ai_student_id_handle handle,
                                    const unsigned char* image,
                                    bef_ai_pixel_format pixel_format,
                                    int image_width,
                                    int image_height,
                                    int image_stride,
                                    bef_ai_rotate_type orientation,
                                    bef_student_id_ocr_result *id_info);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_student_id_ocr_destroy(bef_ai_student_id_handle handle);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_student_id_ocr_check_license(bef_ai_student_id_handle handle, const char* licensePath);

#endif
