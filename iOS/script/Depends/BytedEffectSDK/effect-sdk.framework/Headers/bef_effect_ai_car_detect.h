
#ifndef ANDROIDDEMO_BEF_EFFECT_AI_CAR_DETECT_H
#define ANDROIDDEMO_BEF_EFFECT_AI_CAR_DETECT_H

#include "bef_effect_ai_public_define.h"

#define BEF_AI_MAX_CAR_NUM 16
#define BEF_AI_MAX_BRAND_NUM 10
#define BEF_AI_BRAND_LEN 10

typedef unsigned long long bef_ai_car_handle;

typedef enum {
    BEF_AI_CarDetct = 1,
    BEF_AI_BrandRec = 2,
} bef_ai_car_param_type;


typedef enum {
    BEF_AI_CarDetectModel = 1,   // 车辆检测/方向
    BEF_AI_BrandDetectModel = 2,   // 车牌检测/关键点
    BEF_AI_BrandOcrModel = 3,   // 车牌 ocr
    BEF_AI_CarTrackModel = 4,
} bef_ai_car_model_type;

typedef struct {
    bef_ai_fpoint points_array[4];      //车牌关键点数组
    int brand_id;                       //车牌id
    int brand_vi[BEF_AI_BRAND_LEN];     //车牌ocr
    int brand_vi_len;
} bef_ai_car_brand_info;


typedef struct {
    int x0;
    int y0;
    int x1;
    int y1;
    int orient;  // 方向
} bef_ai_car_bounding_box;

typedef struct {
    int car_count;                                          // 检到的车辆数
    int brand_count;                                        //检测到的车牌数量
    bef_ai_car_bounding_box car_boxes[BEF_AI_MAX_CAR_NUM];   // 车辆 bbox 数组
    bef_ai_car_brand_info base_infos[BEF_AI_MAX_BRAND_NUM];  //检测到的车牌信息，包括关键点、id
    double gray_score;
    double blur_score;
} bef_ai_car_ret;

BEF_SDK_API
bef_effect_result_t
bef_effect_ai_car_detect_create_handle(bef_ai_car_handle* handle);

BEF_SDK_API
bef_effect_result_t
bef_effect_ai_car_detect_init_model(bef_ai_car_handle handle,
                                           bef_ai_car_model_type modelType,
                                           const char* modelPath);

BEF_SDK_API
bef_effect_result_t
bef_effect_ai_car_detect_set_paramf(bef_ai_car_handle handle,
                                           bef_ai_car_param_type type,
                                           float value);

BEF_SDK_API
bef_effect_result_t
bef_effect_ai_car_detect_detect(bef_ai_car_handle handle,
                                       const unsigned char* image,
                                       bef_ai_pixel_format pixel_format,
                                       int image_width,
                                       int image_height,
                                       int image_stride,
                                       bef_ai_rotate_type orientation,
                                       bef_ai_car_ret* car_info);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_car_detect_destroy(bef_ai_car_handle handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_car_detect_check_license(bef_ai_car_handle handle, const char* licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_car_detect_check_online_license(bef_ai_car_handle handle, const char* licensePath);

#endif //ANDROIDDEMO_BEF_EFFECT_AI_CAR_DETECT_H
