
#ifndef EFFECT_SDK_BEF_EFFECT_AI_PUBLIC_DEFINE_H
#define EFFECT_SDK_BEF_EFFECT_AI_PUBLIC_DEFINE_H


#define BEF_INTENSITY_TYPE_NONE                 0
#define BEF_INTENSITY_TYPE_BEAUTY_WHITEN        1   // 美白
#define BEF_INTENSITY_TYPE_BEAUTY_SMOOTH        2   // 磨平
#define BEF_INTENSITY_TYPE_FACE_SHAPE           3   // 大眼/瘦脸
#define BEF_INTENSITY_TYPE_BEAUTY_SHARP         9   // 锐化
#define BEF_INTENSITY_TYPE_GLOBAL_FILTER_V2     12  // 滤镜
#define BEF_INTENSITY_TYPE_BUILDIN_LIP          17  // 唇色
#define BEF_INTENSITY_TYPE_BUILDIN_BLUSHER      18  // 腮红
#ifdef BEF_SDK_API
#undef BEF_SDK_API
#endif

//bef_framework_public_base_define
#    ifdef __cplusplus
#        ifdef _EFFECT_SDK_EXPORTS_
#            define BEF_SDK_API extern "C" __attribute__((visibility ("default")))
#        else
#            define BEF_SDK_API extern "C"
#        endif
#    else
#        ifdef _EFFECT_SDK_EXPORTS_
#            define BEF_SDK_API __attribute__((visibility ("default")))
#        else
#            define BEF_SDK_API
#        endif
#    endif


typedef    short           int16_t;
typedef    int             int32_t;

typedef unsigned long long UINT64;
// def  effect handle
typedef void *bef_effect_handle_t;

// def  effect result
typedef int bef_effect_result_t;

typedef int effect_result;

// define bef_intensity_type
typedef int bef_intensity_type;

// start error code
#define BEF_RESULT_SUC                       0  //  {zh} 成功返回  {en} Successful return
#define BEF_RESULT_SUC_EMPTY_DRAW            1  //  {zh} 成功返回  {en} Successful return
#define BEF_RESULT_FAIL                     -1  //  {zh} 内部错误，检查是否初始化，初始化是否成功  {en} Internal error, check whether initialization is successful
#define BEF_RESULT_FILE_NOT_FIND            -2  //  {zh} 文件没找到，检查代码中的文件路径与实际路径是否匹配  {en} File not found, check whether the file path in the code matches the actual path

#define BEF_RESULT_INVALID_INTERFACE        -3  //  {zh} 接口未实现，检查SDK是否具备该功能  {en} The interface is not implemented, check whether the SDK has this function
#define BEF_RESULT_FILE_OPEN_FAILED         -4  //  {zh} 文件打开失败，检查文件是否存在，检查对目标文件是否有读写权限  {en} File opening failed, check whether the file exists, check whether there are read and write permissions on the target file

#define BEF_RESULT_INVALID_EFFECT_HANDLE    -5  //  {zh} 无效的Effect句柄，检查是否初始化，初始化是否成功  {en} Invalid Effect handle to check whether initialization is successful
#define BEF_RESULT_INVALID_EFFECT_MANAGER   -6  //  {zh} 无效的EffectManager，检查是否初始化，初始化是否成功  {en} Invalid EffectManager, check whether initialization is successful
#define BEF_RESULT_INVALID_FEATURE_HANDLE   -7  //  {zh} 无效的Feature句柄，检查是否初始化，初始化是否成功  {en} Invalid Feature handle to check whether initialization is successful
#define BEF_RESULT_INVALID_FEATURE          -8  //  {zh} 无效的Feature，检查是否初始化，初始化是否成功  {en} Invalid Feature, check whether initialization is successful
#define BEF_RESULT_INVALID_RENDER_MANAGER   -9  //  {zh} 无效的RenderManager，检查是否初始化，初始化是否成功  {en} Invalid RenderManager, check whether initialization is successful
#define BEF_RESULT_INVALID_ALG_RES          -11 //  {zh} 无效的算法结果，没有设置美颜等特效可能会有这个报错，大部分情况下可忽略  {en} Invalid algorithm results, no special effects such as beauty setting may have this error, which can be ignored in most cases
#define BEF_RESULT_INVALID_ALG_FACE_RES     -12 //  {zh} 无效的人脸检测结果  {en} Invalid face detection results
#define BEF_RESULT_INVALID_ALG_CAT_FACE_RES -13 //  {zh} 无效的猫脸检测结果  {en} Invalid cat face test results
#define BEF_RESULT_INVALID_ALG_HAND_RES     -14 //  {zh} 无效的手势检测结果  {en} Invalid gesture detection result
#define BEF_RESULT_INVALID_ALG_BODY_RES     -15 //  {zh} 无效的人体检测结果  {en} Invalid human test results
#define BEF_RESULT_ALG_INIT_FAIL            -17 //  {zh} 算法初始化失败  {en} Algorithm initialization failed
#define BEF_RESULT_ALG_FACE_INIT_FAIL       -21 //  {zh} 人脸检测初始化失败  {en} Face detection initialization failed
#define BEF_RESULT_ALG_FACE_106_CREATE_FAIL -22 //  {zh} 人脸检测106算法创建失败，检查 license 是否有效，检查模型是否有效  {en} Face detection 106 algorithm creation failed, check whether the license is valid, check whether the model is valid
#define BEF_RESULT_ALG_FACE_280_CREATE_FAIL -23 //  {zh} 人脸检测280算法创建失败，检查 license 是否有效，检查模型是否有效  {en} Face detection 280 algorithm creation failed, check whether the license is valid, check whether the model is valid
#define BEF_RESULT_ALG_FACE_PREDICT_FAIL    -24 //  {zh} 人脸检测预测失败，检查传入图像是否正确  {en} Face detection prediction failed, check whether the incoming image is correct
#define BEF_RESULT_ALG_EXP_CREATE_FAIL      -25 //  {zh} 表情检测初始化失败，检查 license 是否有效，检查模型是否有效  {en} Expression detection initialization failed, check whether the license is valid, check whether the model is valid
#define BEF_RESULT_ALG_HAND_CREATE_FAIL     -26 //  {zh} 创建手势算法失败，检查 license 是否有效，检查模型是否有效  {en} Failed to create gesture algorithm, check whether the license is valid, check whether the model is valid
#define BEF_RESULT_ALG_HAND_PREDICT_FAIL    -27 //  {zh} 手势算法预测失败，检查传入图像是否正确  {en} Gesture algorithm failed to predict, check whether the incoming image is correct


#define BEF_RESULT_INVALID_TEXTURE          -36 //  {zh} 无效的texture，检查传入 texture 是否正确  {en} Invalid texture, check whether the incoming texture is correct
#define BEF_RESULT_INVALID_IMAGE_DATA       -37 //  {zh} 无效的图像数据，检查传入 buffer 是否正确  {en} Invalid image data, check whether the incoming buffer is correct
#define BEF_RESULT_INVALID_IMAGE_FORMAT     -38 //  {zh} 无效的图片格式，检查传入的图像格式是否符合要求  {en} Invalid image format, check whether the incoming image format meets the requirements
#define BEF_RESULT_INVALID_PARAM_TYPE       -39 //  {zh} 无效的参数类型，检查传入的参数是否符合要求  {en} Invalid parameter type, check whether the passed parameter meets the requirements
#define BEF_RESULT_INVALID_RESOURCE_VERSION -40 //  {zh} 资源文件指定sdk版本过高，检查资源文件是否正确  {en} The resource file specifies that the sdk version is too high, check whether the resource file is correct
#define BEF_RESULT_INVALID_PARAM_VALUE      -47 //  {zh} 无效的参数值，检查传入的参数是否符合要求  {en} Invalid parameter value, check whether the passed parameter meets the requirements

#define BEF_RESULT_SMASH_E_INTERNAL         -101 //  {zh} 未定义内部错误，请联系技术支持  {en} No internal error defined, please contact technical support
#define BEF_RESULT_SMASH_E_NOT_INITED       -102 //  {zh} 未初始化相关资源，请联系技术支持  {en} Not initializing related resources, please contact technical support
#define BEF_RESULT_SMASH_E_MALLOC           -103 //  {zh} 申请内存失败，请联系技术支持  {en} Failed to request memory, please contact technical support
#define BEF_RESULT_SMASH_E_INVALID_PARAM    -104 //  {zh} 无效的参数，检查传入的参数是否符合要求  {en} Invalid parameter, check whether the passed parameter meets the requirements
#define BEF_RESULT_SMASH_E_ESPRESSO         -105 //  {zh} ESPRESSO错误，请联系技术支持  {en} ESPRESSO error, please contact technical support
#define BEF_RESULT_SMASH_E_MOBILECV         -106 //  {zh} MOBILECV错误，请联系技术支持  {en} MOBILECV error, please contact technical support
#define BEF_RESULT_SMASH_E_INVALID_CONFIG   -107 //  {zh} 无效的配置，请检查传入授权文件路径是否正确，授权文件是否受损  {en} Invalid configuration, please check whether the path of the incoming authorization file is correct and whether the authorization file is damaged
#define BEF_RESULT_SMASH_E_INVALID_HANDLE   -108 //  {zh} 无效的句柄，请检查传入授权文件路径是否正确，授权文件是否受损  {en} Invalid handle, please check whether the path of the incoming authorization file is correct and whether the authorization file is damaged
#define BEF_RESULT_SMASH_E_INVALID_MODEL    -109 //  {zh} 无效的模型，请检查传入授权文件路径是否正确，授权文件是否受损  {en} Invalid model, please check whether the path of the incoming authorization file is correct and whether the authorization file is damaged
#define BEF_RESULT_SMASH_E_INVALID_PIXEL_FORMAT        -110 //  {zh} 无效的图像格式，请检查传入图像格式是否在SDK支持的范围内  {en} Invalid image format, please check whether the incoming image format is within the scope supported by the SDK
#define BEF_RESULT_SMASH_E_INVALID_POINT               -111 //  {zh} 无效的点，请检查传入接口的输入或输出变量是否为null  {en} Invalid point, please check whether the input or output variable of the incoming interface is null
#define BEF_RESULT_SMASH_E_REQUIRE_FEATURE_NOT_INIT    -112 //  {zh} 依赖模块没有初始化，请联系技术支持  {en} The dependency module is not initialized, please contact technical support
#define BEF_RESULT_SMASH_E_NOT_IMPL                    -113 //  {zh} 未实现的接口，请检查调用函数名和参数是否正确  {en} Unimplemented interface, please check whether the calling function name and parameters are correct

#define BEF_RESULT_INVALID_LICENSE                     -114 //  {zh} 无效的license，请检查授权文件路径是否正确，模型文件是否受损  {en} Invalid license, please check whether the authorization file path is correct and whether the model file is damaged
#define BEF_RESULT_NULL_BUNDLEID                       -115 //  {zh} Application/Bundle ID 为空，请检查传入bundle Id或ApplicationId是否为空  {en} Application/Bundle ID is empty, please check whether the incoming bundle Id or ApplicationId is empty
#define BEF_RESULT_LICENSE_STATUS_INVALID              -116 //  {zh} 非法授权文件，请检查授权文件是否正确  {en} Illegal authorization file, please check whether the authorization file is correct
#define BEF_RESULT_LICENSE_STATUS_EXPIRED              -117 //  {zh} 授权文件过期，请检查授权文件是否正确，是否需要更新  {en} The authorization file has expired, please check whether the authorization file is correct and whether it needs to be updated
#define BEF_RESULT_LICENSE_STATUS_NO_FUNC              -118 //  {zh} 请求功能不匹配，请检查是否购买对应功能  {en} The request function does not match, please check whether to purchase the corresponding function
#define BEF_RESULT_LICENSE_STATUS_ID_NOT_MATCH         -119 //  {zh} Application/Bundle ID 不匹配，请检查申请授权文件和应用的Application/BundleId是否一致  {en} Application/Bundle IDs do not match, please check whether the application authorization file is consistent with the application/BundleId of the application

#define BEF_RESULT_LICENSE_BAG_NULL_PATH               -120 //  {zh} 授权包路径为空，请检查授权文件路径是否正确  {en} The path of the authorization package is empty, please check whether the path of the authorization file is correct
#define BEF_RESULT_LICENSE_BAG_INVALID_PATH            -121 //  {zh} 错误的授权包路径，请检查传入sdk的路径是否正确  {en} Wrong authorization package path, please check whether the path passed into sdk is correct
#define BEF_RESULT_LICENSE_BAG_TYPE_NOT_MATCH          -122 //  {zh} 授权包类型不匹配，请检查授权文件是否正确，是否损坏  {en} Authorization package type does not match, please check whether the authorization file is correct and damaged
#define BEF_RESULT_LICENSE_BAG_INVALID_VERSION         -123 //  {zh} 无效的版本，请检查是否用了旧版本的授权文件  {en} Invalid version, please check whether the old version of the authorization file is used
#define BEF_RESULT_LICENSE_BAG_INVALID_BLOCK_COUNT     -124 //  {zh} 无效的数据块，请检查授权文件是否正确，是否损坏  {en} Invalid data block, please check whether the authorization file is correct and damaged
#define BEF_RESULT_LICENSE_BAG_INVALID_BLOCK_LEN       -125 //  {zh} 无效的数据块长度，请检查授权文件是否正确，是否损坏  {en} Invalid data block length, please check whether the authorization file is correct and damaged
#define BEF_RESULT_LICENSE_BAG_INCOMPLETE_BLOCK        -126 //  {zh} 数据块不完整，请检查授权文件是否正确，是否损坏  {en} The data block is incomplete, please check whether the authorization file is correct and damaged
#define BEF_RESULT_LICENSE_BAG_UNAUTHORIZED_FUNC       -127 //  {zh} license未授权的功能，请检查是否购买对应功能  {en} License unauthorized functions, please check whether to purchase corresponding functions

#define BEF_RESULT_SDK_FUNC_NOT_INCLUDE                -128 //  {zh} SDK 未包含功能  {en} SDK does not include features
#define BEF_RESULT_LICENSE_BAG_INVALID_SUB_FUNC        -129 //  {zh} 无效的subFunction，证书存在问题，请联系技术支持  {en} Invalid subFunction, there is a problem with the certificate, please contact technical support
#define BEF_RESULT_GL_ERROR_OCCUR                      -150 //  {zh} opengl发生错误，请检查是否在opengl线程调用接口  {en} An error occurred in opengl, please check whether the interface is called in the opengl thread
#define BEF_RESULT_GL_CONTECT                          -151 //  {zh} 无效的glcontext，请检查gl上下文是否正确  {en} Invalid glcontext, please check if the gl context is correct
#define BEF_RESULT_GL_TEXTURE                          -152 //  {zh} 无效的gltexture，请检查纹理号是否有效  {en} Invalid gltexture, please check whether the texture number is valid

// Be Used in bach algorithm module
#define BEF_RESULT_BACH_E_INVALID_RES_FINDER -153 // {zh} Bach算法模块错误，无效的ResourceFinder，请检查资源文件名或者路径是否正确  {en} Bach algorithm module error, invalid ResourceFinder, please check whether resource path or name is correct
#define BEF_RESULT_BACH_E_NOT_INIT           -154 // {zh} Bach算法模块错误，检查是否初始化，初始化是否成功  {en} Bach algorithm module error, check whether initialization is successful
#define BEF_RESULT_BACH_E_INVALID_CONFIG     -155 // {zh} Bach算法模块错误，无效的算法配置或参数，请检查配置文件或参数是否正确  {en} Bach algorithm module error, invalid algorithm config or param, please check whether input config or param is correct
#define BEF_RESULT_BACH_E_INVALID_GRAPH      -156 // {zh} Bach算法模块错误，无效的Graph定义，请检查初始化输入的Graph是否正确  {en} Bach algorithm module error, invalid Graph define, please check whether input Graph is correct
#define BEF_RESULT_BACH_E_INVALID_MODEL      -157 // {zh} Bach算法模块错误，无效的算法模型，请检查给定的模型或路径是否正确  {en} Bach algorithm module error, invalid algorith model, please check whether input model or path is correct
#define BEF_RESULT_BACH_E_INVALID_TYPE       -158 // {zh} Bach算法模块错误，无效的参数类型，请检查给定的参数类型是否正确  {en} Bach algorithm module error, invalid parameter type, please check whether input parameter type is correct
#define BEF_RESULT_BACH_E_INVALID_NODE       -159 // {zh} Bach算法模块错误，无效的算法结点，请检查算法的配置是否正确  {en} Bach algorithm module error, invalid algorithm node, please check whether algorithm config is correct
#define BEF_RESULT_BACH_E_INVALID_FORMAT     -160 // {zh} Bach算法模块错误，无效的图像格式，请检查输入图像格式是否正确  {en} Bach algorithm module error, invalid input picture format, please check whether input picture format is correct
#define BEF_RESULT_BACH_E_INTERNAL_ERROR     -161 // {zh} Bach算法模块错误，内部错误  {en} Bach algorithm module error, internal error

/* {zh} 
 ** 画质增强的错误码都放在这里
 */
/* {en} 
 ** The enhanced image error codes are all here
 */
#define BEF_RESULT_IMAGE_QUALITY_CREATE_ENGINE_FAILED           -64     //  {zh} 画质增强引擎创建失败  {en} Image quality enhancement engine creation failed
#define BEF_RESULT_IMAGE_QUALITY_CREATE_VIDEO_SR_FAILED         -65     //  {zh} 视频超分算法创建失败  {en} Video super-segmentation algorithm creation failed
#define BEF_RESULT_IMAGE_QUALITY_CREATE_NIGHT_SCENE_FAILED      -66     //  {zh} 画质算法失败  {en} Image quality algorithm failed
#define BEF_RESULT_INVALID_HANDLE                               -67     //  {zh} 无效的画质算法handle  {en} Invalid image quality algorithm handling
#define BEF_RESULT_IMAGE_QUALITY_CREATE_ADAPTIVE_SHARPEN_FAILED      -68     //  {zh} 画质算法失败  {en} Image quality algorithm failed
#define BEF_RESULT_IMAGE_QUALITY_ASP_UNDER_INIT                 -69     //  {zh} 画质自适应锐化异步处理，设置完成会继续处理  {en} Image quality adaptive sharpening asynchronous processing, processing will continue after setting
#define BEF_RESULT_IMAGE_QUALITY_VFI_NO_EXECUTION                -70    //  {zh} 插帧算法判断不需要插帧  {en} video frame insertion algorithm thinks no need to do execute
#define BEF_RESULT_IMAGE_QUALITY_CREATE_ONEKEY_ENHANCE_FAILED       -71    //  {zh} 创建一键画质增强算法失败  {en} Image quality algorithm failed
#define BEF_RESULT_IMAGE_QUALITY_ONEKEY_ENHANCE_NO_EXECUTION        -72    //  {zh} 画质增强算法判断不需要执行  {en} Image enhancement algorithm thinks as no need to execute
#define BEF_RESULT_IMAGE_QUALITY_CREATE_VIDA_FAILED      -73     //  {zh} vida画质算法失败  {en} Image quality algorithm failed

/*
 ** END
 */
// end error code

#define BEF_EFFECT_FEATURE_LEN                          128 //feature name 默认长度

typedef enum
{
    BEF_AI_LOG_LEVEL_NONE = 0,
    BEF_AI_LOG_LEVEL_DEFAULT = 1,
    BEF_AI_LOG_LEVEL_VERBOSE = 2,
    BEF_AI_LOG_LEVEL_DEBUG = 3,
    BEF_AI_LOG_LEVEL_INFO = 4,
    BEF_AI_LOG_LEVEL_WARN = 5,
    BEF_AI_LOG_LEVEL_ERROR = 6,
    BEF_AI_LOG_LEVEL_FATAL = 7,
    BEF_AI_LOG_LEVEL_SILENT = 8,
} bef_ai_log_level;

typedef enum {
    BEF_AI_PREVIEW_MODE = 0, // 预览模式集成SDK
    BEF_AI_PICTURE_MODE = 1  //拍照模式下集成SDK
} bef_ai_process_type;


// bef_framework_public_geometry_define
// @brief image rotate type definition
typedef enum {
    BEF_AI_CLOCKWISE_ROTATE_0 = 0, // 图像不需要旋转，图像中的人脸为正脸
    BEF_AI_CLOCKWISE_ROTATE_90 = 1, // 图像需要顺时针旋转90度，使图像中的人脸为正
    BEF_AI_CLOCKWISE_ROTATE_180 = 2, // 图像需要顺时针旋转180度，使图像中的人脸为正
    BEF_AI_CLOCKWISE_ROTATE_270 = 3  // 图像需要顺时针旋转270度，使图像中的人脸为正
} bef_ai_rotate_type;

// ORDER!!!
typedef enum {
    BEF_AI_PIX_FMT_RGBA8888, // RGBA 8:8:8:8 32bpp ( 4通道32bit RGBA 像素 )
    BEF_AI_PIX_FMT_BGRA8888, // BGRA 8:8:8:8 32bpp ( 4通道32bit RGBA 像素 )
    BEF_AI_PIX_FMT_BGR888,   // BGR 8:8:8 24bpp ( 3通道32bit RGB 像素 )
    BEF_AI_PIX_FMT_RGB888,   // RGB 8:8:8 24bpp ( 3通道32bit RGB 像素 )
    BEF_AI_PIX_FMT_GRAY8,    // GRAY 8bpp ( 1通道8bit 灰度像素 ). 目前还不支持
    BEF_AI_PIX_FMT_YUV420P,  // YUV  4:2:0   12bpp ( 3通道, 一个亮度通道, 另两个为U分量和V分量通道, 所有通道都是连续的 ). 目前还不支持
    BEF_AI_PIX_FMT_NV12,     // YUV  4:2:0   12bpp ( 3通道, 一个亮度通道, 另一道为UV分量交错 ). 目前还不支持
    BEF_AI_PIX_FMT_NV21      // YUV  4:2:0   12bpp ( 3通道, 一个亮度通道, 另一道为VU分量交错 ). 目前还不支持
} bef_ai_pixel_format;


typedef struct bef_ai_fpoint_t {
    float x;
    float y;
} bef_ai_fpoint;

typedef struct bef_ai_fpoint3d_t {
    float x;
    float y;
    float z;
} bef_ai_fpoint3d;

typedef struct bef_ai_rect_t {
    int left;   // Left most coordinate in rectangle. 矩形最左边的坐标
    int top;    // Top coordinate in rectangle.  矩形最上边的坐标
    int right;  // Right most coordinate in rectangle.  矩形最右边的坐标
    int bottom; // Bottom coordinate in rectangle. 矩形最下边的坐标
} bef_ai_rect;

// Same definiation as bef_rect, but in float type
// 和bef_rect一样的定义，类型为单精度浮点
typedef struct bef_ai_rectf_t {
    float left;
    float top;
    float right;
    float bottom;
} bef_ai_rectf;


typedef enum bef_ai_camera_position_t {
    bef_ai_camera_position_front,
    bef_ai_camera_position_back
} bef_ai_camera_position;



typedef struct bef_ai_frect_st {
    float left;   ///< 矩形最左边的坐标
    float top;    ///< 矩形最上边的坐标
    float right;  ///< 矩形最右边的坐标
    float bottom; ///< 矩形最下边的坐标
} bef_ai_frect;


typedef struct bef_ai_image_t {
    const unsigned char *data;
    int width;
    int height;
    int stride;
    int format;
    bef_ai_rotate_type rotate;
} bef_ai_image;

typedef struct bef_ai_tt_key_point_st {
    float x; // 对应 cols, 范围在 [0, width] 之间
    float y; // 对应 rows, 范围在 [0, height] 之间
    bool is_detect; // 如果该值为 false, 则 x,y 无意义
} bef_ai_tt_key_point;

typedef struct {
    const unsigned char* image;          ///< 图像帧数据地址
    bef_ai_pixel_format pixel_fmt;       ///< 图像格式
    int image_width;                     ///< 图像的宽度
    int image_height;                    ///< 图像的高度
    int image_stride;                    ///< 图像的步长(每行的字节数，可能存在padding)
    bef_ai_rotate_type orient;           ///< 图像的方向
} bef_ai_base_args;

typedef enum {
    bef_ai_render_api_gles20 = 0,
    bef_ai_render_api_gles30,
} bef_ai_render_api_type;

typedef enum {
    BEF_AI_TOUCH_EVENT_BEGAN,         ///< 触摸开始事件
    BEF_AI_TOUCH_EVENT_MOVED,         ///< 触摸移动事件
    BEF_AI_TOUCH_EVENT_STATIONARY,    ///< 触摸驻停事件
    BEF_AI_TOUCH_EVENT_ENDED,         ///< 触摸结束事件
    BEF_AI_TOUCH_EVENT_CANCELLED,     ///< 触摸取消事件
} bef_ai_touch_event_code;

typedef enum {
    BEF_AI_GESTURE_TAP,                 ///< 单击手势
    BEF_AI_GESTURE_PAN,                 ///< 滑动手势
    BEF_AI_GESTURE_ROTATE,              ///< 旋转手势
    BEF_AI_GESTURE_SCALE,               ///< 缩放手势
    BEF_AI_GESTURE_LONG_PRESS,          ///< 长按手势
    BEF_AI_GESTURE_DOUBLE_CLICK         ///< 双击手势
} bef_ai_gesture_event_code;


typedef enum {
    BEF_EFFECT = 0,
    BEF_FACE,
    BEF_C1,
    BEF_C2,
    BEF_CAR_DETECT,
    BEF_FACE_ATTR,
    BEF_FACE_CLUSTERING,
    BEF_FACE_VERIFY,
    BEF_GAZE_ESTIMATION,
    BEF_HAIR_PARSE,
    BEF_HAND_DETECT,
    BEF_HEAD_SEG,
    BEF_LIGHT_CLS,
    BEF_SKENETON,
    BEF_AVATAR_DRIVE,
    BEF_ACTION_RECOGNETION,
    BEF_SKY_SEG,
    BEF_VIDEO_CLS,
    BEF_STUDENT_ID_OCR,
    BEF_HUMAN_DISTANCE,
    BEF_PET_FACE,
    BEF_PORTRAIT_MATTING,
    BEF_ADAPTIVE_SHARPEN,
    BEF_VFI,
    BEF_ONEKEY_ENHANCE,
    BEF_LENS_VIDA,
    BEF_TAINT_DETECT,
    BEF_SKELETON_3D,
    BEF_SALIENCY_MATTING,
    BEF_VIDEO_DEFLICKER,
    BEF_VIDEO_SR,
    BEF_NIGHT_SCENE,
    BEF_PHOTO_NIGHT_SCENE,
    BEF_DYNAMIC_GESTURE,
    BEF_LICENSE_CAKE,
    BEF_BACH_SKELETON,
    BEF_CHROMA_KEYING,
    BEF_SKIN_SEGMENTATION,
    BEF_SLAM,
    BEF_FACEFITTING,
    BEF_CINE_MOVE,
    BEF_AVABOOST,
    BEF_OBJECT_TRACKING,
    BEF_VIDEO_HDR_LITE,
    BEF_VIDEO_STAB
} bef_ai_license_function_type;

typedef char*(*bef_ai_resource_finder)(bef_effect_handle_t, const char *, const char *);
typedef int(*bef_ai_log_callback)(int logLevel, const char* msg);

#define EFFECT_HAND_DETECT_DELAY_FRAME_COUNT 4

///部分贴纸需要与客户端通过消息交互
#define BEF_EFFECT_MESSAGE_TRIGGER_CAPUTURE_IMAGE  2200   /// <触发贴纸截图  客户端发给sdk
#define BEF_EFFECT_MESSAGE_RECEIVE_CAPUTURE_IMAGE  0x45   /// <获取贴纸截图  sdk发给客户端
#define BEF_EFFECT_MESSAGE_OPERATE_CLIENT_UI  0x30   /// <客户端接收sdk消息来控制UI    sdk发给客户端

#define ALGORITHM_DETECT_MIN_SIZE     720
#define FORCE_ALGORITM_IMAGE_POSITIVE false

#endif
