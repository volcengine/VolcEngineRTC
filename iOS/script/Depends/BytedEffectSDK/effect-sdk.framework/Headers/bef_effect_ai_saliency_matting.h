//
//

#ifndef bef_effect_ai_saliency_matting_h
#define bef_effect_ai_saliency_matting_h

#include "bef_effect_ai_public_define.h"

typedef unsigned long long bef_ai_saliency_matting_handle;

typedef enum{
    BEF_SALIENCY_MATTING_SMALL_MODEL = 0,
    BEF_SALIENCY_MATTING_MEDIUM_MODEL = 1,
    BEF_SALIENCY_MATTING_LARGE_MODEL = 2,
}bef_ai_saliency_matting_model_type;

/**
 * @brief result of algorithm
 */
typedef struct {
    unsigned char* mask; /**< alpha[x][y] indicate value of element in mask*/
    int maskWidth; /**< width of mask */
    int maskHeight; /**< height mask */
}bef_ai_saliency_matting_ret;

/**
 * @brief Create handle
 * @param [out] handle Created handle
 * @return If succeed, return @a BEF_RESULT_SUC. other value please see @a bef_effect_ai_public_define.h
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_saliency_matting_create(bef_ai_saliency_matting_handle *handle);

/**
 * @brief Check license
 * @return If succeed, return @a BEF_RESULT_SUC. other value please see @a bef_effect_ai_public_define.h
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_saliency_matting_check_online_license(bef_ai_saliency_matting_handle handle, const char* licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_saliency_matting_check_offline_license(bef_ai_saliency_matting_handle handle, const char* licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_saliency_matting_set_model(bef_ai_saliency_matting_handle handle, bef_ai_saliency_matting_model_type type, const char *modelPath);

/**
 * @brief Execute algorithm 
 * 
 * @param [in] handle algorithm handle
 * @param [in] image binary data of image, should be row first
 * @param [in] pixelFormat format of input image, see @a bef_effect_ai_public_define.h
 * @param [in] width width of input image
 * @param [in] height height of input image
 * @param [in] stride the number of bytes of each row
 * @param [in] rotation the rotation type of input image
 * @param [out] result output of algorithm, the "mask" member of result points to a memory space of size: @p width * @p height *sizeof(unsigned char)
 *              If the "mask" member in @a bef_ai_saliency_matting_ret is NULL, the algorithm will allocate memory space of
 *              an appropriate size and write the result into it. The user will be responsible for releasing this space.
 *              If the 'mask' member of the structure is not NULL, the algorithm assumes that the user has already allocated
 *              appropriate memory space and writes the result directly into the memory space pointed to by the 'mask' member.
 * @return If succeed, return @a BEF_RESULT_SUC
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_saliency_matting_detect(bef_ai_saliency_matting_handle handle,
                                            const unsigned char *image,
                                            bef_ai_pixel_format pixelFormat,
                                            int width,
                                            int height,
                                            int stride,
                                            bef_ai_rotate_type rotation,
                                            bef_ai_saliency_matting_ret *result);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_saliency_matting_release(bef_ai_saliency_matting_handle handle);

#endif /* bef_effect_ai_saliency_matting_h */
