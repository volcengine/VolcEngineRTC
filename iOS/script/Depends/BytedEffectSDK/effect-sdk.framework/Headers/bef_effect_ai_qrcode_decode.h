

#ifndef ANDROIDDEMO_BEF_EFFECT_QRCODE_H
#define ANDROIDDEMO_BEF_EFFECT_QRCODE_H

#include "bef_effect_ai_public_define.h"

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
#endif
// clang-format off
#define CODE_TYPE_QRCODE        0x00000001
#define CODE_TYPE_DOUYIN_CODE   0x00000002
#define CODE_TYPE_UPC_A_CODE    0x00000004
#define CODE_TYPE_UPC_E_CODE    0x00000008
#define CODE_TYPE_EAN_8_CODE    0x00000010
#define CODE_TYPE_EAN_13_CODE   0x00000020
#define CODE_TYPE_CODE39_CODE   0x00000040
#define CODE_TYPE_CODE128_CODE  0x00000080
// clang-format on

typedef struct EnigmaPoint {
    float x;
    float y;
} EnigmaPoint;

typedef struct EnigmaCode {
    int type;    // 二维码的类型，目前支持2种: CODE_TYPE_QRCODE 和
    // CODE_TYPE_DOUYIN_CODE
    char *text;  // 二维码的内容

    // 二维码的定位点坐标，QR二维码和抖音码都有3个定位点
    // 目前坐标是以输入原图为标准大小的绝对坐标
    EnigmaPoint *points;
    int points_len;
} EnigmaCode;

// 二维码识别结果，默认情况下 code_count 为 1，如果需要返回图片上的所有二维码，
// 需要打开 EnigmaParamType.DecodeMultiple 配置，但该功能目前还不支持
typedef struct EnigmaResult {
    EnigmaCode *code;
    int code_count;
    // 推进系数为 {0,[1.0, 2.0]} 之间的值，0
    // 表示不需要推进,[1.0, 2.0]表示相机在原有的放大系数上需要推进的倍数。
    float zoom_in_factor;
} EnigmaResult;

typedef enum {
    KeepROISize = 1,  // 设置是否改变ROI的大小 (目前暂不支持)
    // 指定二维码的类型，目前有2种 {CODE_TYPE_QRCODE, CODE_TYPE_DOUYIN_CODE}
            CodeType = 2,
    // 设置验证级别的高低, 目前有4个等级: {0, 1, 2, 3},
    // 数字越大，级别越高，级别越高，二维码的容错性更强，但可编码的字符数越小
            ECLevel = 3,
    // 设置版本的高低, 目前有6个版本: {1, 2, 3, 4, 5, 6},
    // 版本越高，能容纳的数据越多
            Version = 4,
    // 如果拍摄的图片上有多种码，那么把该值设置为1, 则会返回多种码的结果,
    // 默认只返回一种结果
            DecodeMultiple = 5,
    // 在二维码比较小的情况下，设置是否自动放缩
            AutoZoomIn = 6,
    //指定编码生成的图片是否带透明通道, 0表示无透明通道,生成三通道图片
    // 1表示码的环形区域和logo外都为透明，生成四通道图片
    // 2表示除了抖音码的所占的圆形区域，其余部分都为透明，生成四通道图片
            BackgroundMode = 7,
} EnigmaParamType;

typedef void *EnigmaHandle;


BEF_SDK_API bef_effect_result_t
        bef_effect_ai_qrcode_decode_create(EnigmaHandle *handle);

BEF_SDK_API bef_effect_result_t
        bef_effect_ai_set_decode_param(EnigmaHandle handle,
                                       EnigmaParamType type,
                                       float value);
BEF_SDK_API bef_effect_result_t
        bef_effect_ai_qrcode_decode(EnigmaHandle handle,
                                    const unsigned char *image,
                                    bef_ai_pixel_format pixel_format,
                                    int image_width,
                                    int image_height,
                                    int image_stride,
                                    int roi_left,
                                    int roi_top,
                                    int roi_width,
                                    int roi_height,
                                    bef_ai_rotate_type orientation,
                                    EnigmaResult **ret);


BEF_SDK_API bef_effect_result_t
        bef_effect_ai_qrcode_release(EnigmaHandle handle);





#endif //ANDROIDDEMO_BEF_EFFECT_QRCODE_H
