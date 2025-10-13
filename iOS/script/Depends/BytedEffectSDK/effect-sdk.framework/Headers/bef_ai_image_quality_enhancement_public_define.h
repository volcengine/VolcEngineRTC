#ifndef BEF_AI_IMAGE_QUALITY_ENHANCEMENT_PUBLICE_DEFINE_H
#define BEF_AI_IMAGE_QUALITY_ENHANCEMENT_PUBLICE_DEFINE_H

#include <stddef.h>
#include "bef_effect_ai_public_define.h"
#include <stdint.h>

//**************  common begin *****************************
#define bef_effect_result_t int

typedef union bef_ai_lens_data{
    int texture[2]; // 如果是纹理，这里纹理的index, ios 的纹理目前只支持metal的纹理, android 需要oes 纹理，且纹理放在0 位置
    void* buffer;   // 如果是数据输入，iOS 传入pixelBuffer的指针
}bef_ai_lens_data;

//#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
typedef enum bef_ai_lens_power_level{
    BEF_AI_LENS_POWER_LEVEL_DEFAULT = 0,
    BEF_AI_LENS_POWER_LEVEL_LOW,
    BEF_AI_LENS_POWER_LEVEL_NORMAL,
    BEF_AI_LENS_POWER_LEVEL_HIGH,
    BEF_AI_LENS_POWER_LEVEL_AUTO,
} bef_ai_lens_power_level;

//#endif

typedef enum bef_ai_lens_data_type{
    BEF_AI_LENS_ANDROID_TEXTURE_RGBA,
    BEF_AI_LENS_ANDROID_TEXTURE_OES,
    BEF_AI_LENS_METAL_TEXTURE_RGBA,
    BEF_AI_LENS_PXIELBUFFER_NV12,
    BEF_AI_LENS_PXIELBUFFER_RGBA,
    BEF_AI_LENS_PXIELBUFFER_BGRA,
    BEF_AI_LENS_METAL_TEXTURE_NV12,
    BEF_AI_LENS_DATA_GRAY,
    BEF_AI_LENS_DATA_BGR,
    BEF_AI_LENS_DATA_BGRA,
}bef_ai_lens_data_type;

typedef enum bef_ai_lens_yuv_type {
    BEF_AI_LENS_NV21 = 0,
    BEF_AI_LENS_NV12,
}bef_ai_lens_yuv_type;


//**************  common end *****************************
typedef struct bef_ai_video_sr_input{
    int width;   // 输入数据的宽度
    int height;  // 输入数据的高度
    bef_ai_lens_data data;   // 输入数据的数据
    bef_ai_lens_data_type type; // 输入数据的类型，iOS 支持pixelbuffer 输出，Android 支持oes 纹理
}bef_ai_video_sr_input;

typedef struct bef_ai_video_sr_output{
    bef_ai_lens_data data;   // 输出类型数据，会根据输入，填充对应的输出部分
    int width;   // 输出数据的宽度
    int height;  // 输入数据的高度
}bef_ai_video_sr_output;

typedef struct bef_ai_night_scene_data{
    int width;   // 输入数据的宽度
    int height;  // 输入数据的高度
    bef_ai_lens_data data;   // 输入数据的数据
    bef_ai_lens_data_type type; // 输入数据的类型 iOS暂时不支持 Android 支持oes 纹理
}bef_ai_night_scene_data;

typedef enum bef_ai_lens_backend_type
{
    BEF_AI_LENS_BACKEND_CPU = 0,
    BEF_AI_LENS_BACKEND_GPU,
    BEF_AI_LENS_BACKEND_DSP,
    BEF_AI_LENS_BACKEND_HETEROGENE,
    BEF_AI_LENS_BACKEND_DYNAMIC_TUNING,
    BEF_AI_LenGrammaBlurReal,  //虚化实时处理算法
    BEF_AI_LenGrammaBlurShoot,  //虚化拍摄算法
    BEF_AI_LENS_BACKEND_CoreML,//apple CoreML
}bef_ai_lens_backend_type;


//**************  video  super resolution begin *****************************
 # if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
typedef struct bef_ai_video_sr_init_config
{
    const char* bin_path;   // 传入的路径必须是存在并且有读写权限，超分算法会读写文件，这个路径需要外部传递进来
    bool ext_oes_texture;   // 是否是oes 纹理
    int max_height;         // 算法输入图片的分辨率 (max_height, max_width), 创建的时候设定，避免频繁申请释放内存
    int max_width;
    void* filter_ptr;       // 目前传null
    int filter_size;        // 目前传0
    float thresh;           // 暂时不用设置
    bef_ai_lens_data_type  input_type;       // 输入类型
    bef_ai_lens_power_level power_level;    // 传入频率设置等级，默认为auto等级（default是指随系统调节，low是使用低频率，normal是使用中频率，high是使用高频率，auto是sdk内部根据机型自动调节）
    // bef_ai_lens_backend_type backend_type;  // 目前仅支持GPU平台
    bool isMaliSync;       // true 与原来方式一致，false，可提升Mail GPU设备性能。{lens 3.9.0 add @see 
    int srType = 0;             // @see LensVideoAlgType
}bef_ai_video_sr_init_config;

#elif  defined(__APPLE__)
typedef struct bef_ai_video_sr_init_config
{
    const char* model_path;     // 模型文件的路径  目前不需要传入
    int model_data_length;      // 目前不需要传入
    const char* metal_path;     // 目前不需要传入
    bool enable_mem_pool;       // 是否使用内存池，短视频场景下使用
    bef_ai_lens_data_type input_type;   // 输入目前只有pixelbuffer格式
    bef_ai_lens_data_type output_type;  // 输出为pixelbuffer和 metal texture两种
    float float_thresh;         // 暂时不用设置
    int srType;            // 1.5x 用15表示，2.0x 用 20表示
}bef_ai_video_sr_init_config;
#endif


//**************  video  super resolution end *****************************

//**************  adaptive sharpen begin *****************************
//自适应锐化支持的场景
typedef enum bef_ai_asf_scene_mode
{
    BEF_AI_LENS_ASF_SCENE_MODE_LIVE_GAME = 0,   //游戏
    BEF_AI_LENS_ASF_SCENE_MODE_LIVE_PEOPLE,     // 秀场
    BEF_AI_LENS_ASF_SCENE_MODE_EDIT,            // 视频编辑
    BEF_AI_LENS_ASF_SCENE_MODE_RECORED_MAIN,    // 主摄录制
    BEF_AI_LENS_ASF_SCENE_MODE_RECORED_FRONT    // 前摄录制
}bef_ai_asf_scene_mode;


typedef struct bef_ai_asf_init_config{
    bef_ai_asf_scene_mode scene_mode;   //场景模式
    void* context; //iOS端可以传入外部metal device，如果为nullptr，则在lens内部新建device
#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
    bef_ai_lens_power_level level; //iOS端无需设置
#endif
    bef_ai_lens_data_type input_type; // 输入数据的类型
    bef_ai_lens_data_type output_type; // 输出数据的类型
    
    int frame_width;//视频宽度
    int frame_height;//视频高度
    float amount;//锐化强度增益，默认-1（无效值），即不调整。 有效值为>0：当设置>1时，会增大锐化强度，设置<1时，减弱锐化强度。
    float over_ratio;//黑白边的容忍度增益，默认-1（无效值），即不调整。有效值为>0：当amount>1时，如果发现增大amount清晰度没有明显增加，可能需要稍微增大over_ratio，经验公式为：over_ratio= 1+ a * (amount -1)，其中比例系数a可调整，属于0～1范围。
    float edge_weight_gamma;//对中低频边缘的锐化强度进行调整， 默认-1（无效值），即 不调整。有效值为>0
    int diff_img_smooth_enable;//开启后减少锐化带来的边缘artifacts，但锐化强度会比关闭时弱一些， 默认-1（无效值），即保持内部设置，目前设置为开启。 有效值为0或1，0--关闭，1--开启

}bef_ai_asf_init_config;

typedef struct bef_ai_asf_input{
    bef_ai_lens_data data;   // 输入数据的数据
    bef_ai_lens_data_type type;// 输入数据格式
}bef_ai_asf_input;

typedef struct bef_ai_asf_output{
    bef_ai_lens_data data;   // 输出类型数据，会根据输入，填充对应的输出部分
    bef_ai_lens_data_type type;// 输入数据格式
}bef_ai_asf_output;

typedef struct bef_ai_asf_property{
    bef_ai_asf_scene_mode scene_mode;   //场景模式
    int frame_width;//视频宽度
    int frame_height;//视频高度
    float amount;//锐化强度增益，默认-1（无效值），即不调整。 有效值为>0：当设置>1时，会增大锐化强度，设置<1时，减弱锐化强度。
    float over_ratio;//黑白边的容忍度增益，默认-1（无效值），即不调整。有效值为>0：当amount>1时，如果发现增大amount清晰度没有明显增加，可能需要稍微增大over_ratio，经验公式为：over_ratio= 1+ a * (amount -1)，其中比例系数a可调整，属于0～1范围。
    float edge_weight_gamma;//对中低频边缘的锐化强度进行调整， 默认-1（无效值），即 不调整。有效值为>0
    int diff_img_smooth_enable;//开启后减少锐化带来的边缘artifacts，但锐化强度会比关闭时弱一些， 默认-1（无效值），即保持内部设置，目前设置为开启。 有效值为0或1，0--关闭，1--开启
}bef_ai_asf_property;

//**************  adaptive sharpen end *****************************

//**************  vfi  begin *****************************
// VFI_UM_为补帧， VFI_COVER_TYPE为帧融合
typedef enum {
    bef_ai_lens_vfi_um = 0,
    bef_ai_lens_vfi_cover = 1
}bef_ai_lens_vfi_type;

typedef enum {
    bef_ai_lens_vfi_rgba8888_buffer  = 0,
    bef_ai_lens_vfi_rgba8888_texture = 1
}bef_ai_lens_vfi_data_type;

typedef struct bef_ai_vfi_init_config {
    const char* kernelBinPath; // 可读写的路径
    bef_ai_lens_vfi_type type; // 插帧的类型
    bef_ai_lens_power_level level; //iOS端无需设置
    bef_ai_lens_vfi_data_type dataType; // 插帧输的的输入输出类型
}bef_ai_vfi_init_config;

typedef union bef_ai_lens_vfi_data{
    int texture; // 如果是纹理，这里纹理的index, ios 的纹理目前只支持metal的纹理, android 需要oes 纹理，且纹理放在0 位置
    void* buffer;   // 如果是数据输入，iOS 传入pixelBuffer的指针
}bef_ai_lens_vfi_data;

typedef struct bef_ai_vfi_process_config {
    int textureIdP;
    int textureIdN;
    void* buffer;
    void* backBuffer;
    int width;
    int height;
    int strideW;
    int strideH;
    int flag;
    int open;
    float timeStamp;
    float scaleX;
    float scaleY;
}bef_ai_vfi_process_config;

//**************  vfi  end *****************************


//**************  onekey enhance begin *****************************

 typedef enum {
     BEF_SCENE_MODE_MOBILE_EDITOR = 0,
     BEF_SCENE_MODE_MOBILE_RECORDE,
     BEF_SCENE_MODE_MOBILE_LIVE,
     BEF_SCENE_MODE_MOBILE_RTC,
     BEF_SCENE_MODE_PC_EDITOR,
     BEF_SCENE_MODE_PC_LIVE,
     BEF_SCENE_MODE_PC_RTC,
     BEF_SCENE_MODE_TRANSCODING
 }bef_one_key_scene_strategy_mode;

typedef struct bef_ai_onekey_enhancement_algParamStream {
    int luminance_target_int0;
    int luminance_target_int1;
    float contrast_factor_float;
    float saturation_factor_float;
    float amount_float;
    float ratio_float;
    float noise_factor_float;
    float current_pixel_weight_float;
    int hdr_version_int;
    float luma_trigger_float;
    float over_trigger_float;
    float under_trigger_float;
    int asf_scene_mode_int;
}bef_ai_onekey_enhancement_algParamStream;

typedef struct bef_ai_onekey_enhancement_config {
    int width;
    int height;
    const char* kernelBinPath; // 可读写的路径
    bool disableDenoise; //打开降噪
    bool disableHdr; //打开HDR
    bool oneKeyRecordHdrV2; //选择hdr v1,v2算法
    bool asnycProcess; //算法异步执行开关
    bool disableNightScene; //算法白天隔离夜晚
    bool disableDayScene; //算法夜晚隔离白天
    bool disableAsf; //打开锐化
    bef_ai_lens_power_level level; //iOS端无需设置
    bef_one_key_scene_strategy_mode sceneMode;
    bef_ai_onekey_enhancement_algParamStream algParamStream;
}bef_ai_onekey_enhancement_config;

typedef struct bef_ai_onekey_detect_config {
    int iso;
    int iso_max; //默认是50
    int iso_min; //默认3500
    int cvdetectFrames;  //默认是3
}bef_ai_onekey_detect_config;

typedef struct bef_ai_onekey_process_config {
    bef_ai_onekey_detect_config detectConfig;
    int width;
    int height;
    bool isFirstFrame;
    int initDecayFrames; //动态场景切换用淡入淡出效果来过度（默认值30）
    bool isProtectFace;
    int faceNum;
    bef_ai_rect* faceList;
    bef_ai_onekey_enhancement_algParamStream algParamStream;
}bef_ai_onekey_process_config;
//**************  onekey enhance end *****************************


//**************  vida enhance begin *****************************
typedef enum{
    bef_ai_vida_Face,        // 人脸打分
    bef_ai_vida_AES,         // 美学打分
    bef_ai_vida_Similar,
    bef_ai_vida_Coherence,
    bef_ai_vida_Clarity    //清晰度检测模型
} bef_ai_vida_type;

typedef struct bef_ai_vida_init_config {
    const char* modelPath; // 模型路径
    const char* kernelBinPath;
    bef_ai_vida_type vidaType; // 模型类型
    bef_ai_lens_backend_type backendType; // 运行的bachend
    int numThread; //only make sense when backendType is CPU, default set 2
    float alpha;    // 1.0
    float beta;     // 0.0
    const char* tempDirPath;  // iOS 存放临时文件的目录，仅 coreml 模型生效
}bef_ai_vida_init_config;
//**************  vida enhance end *****************************

//**************  taint detect begin *****************************
typedef struct bef_ai_taint_scene_detect_param {
    int detectFrequency;
    const char* modelPath;
    const char* kernelBinPath;
    bef_ai_lens_backend_type backendType;
    int numThread; // only make sense when backendType is CPU, default set 2
}bef_ai_taint_scene_detect_param;

typedef struct bef_ai_taint_scene_detect_buffer {
    void *inBuffer;
    bool switchScene;
}bef_ai_taint_scene_detect_buffer;

//**************  taint detect end *****************************

//**************  cine move begin *****************************

typedef enum bef_cine_move_alg_type {
    BEF_CINE_MOVE_ALG_START = 0,
    BEF_CINE_MOVE_ALG_V1,   // 等间隔推拉运镜
    BEF_CINE_MOVE_ALG_V2,   // 等间隔水平运镜
    BEF_CINE_MOVE_ALG_V3,   // 等间隔推拉水平运镜
    BEF_CINE_MOVE_ALG_RHYTHMIC_V4,  // 律动运镜
    BEF_CINE_MOVE_ALG_CENTER_FOCUS, // 人像居中
    BEF_CINE_MOVE_ALG_Y_COOR_V6,    // 等间隔垂直运镜
    BEF_CINE_MOVE_ALG_ROT_V7,       // 摇动运镜
    BEF_CINE_MOVE_ALG_SNAKE_V8,     // 波动运镜
    BEF_CINE_MOVE_ALG_HEART_BEAT_V9,// 心跳运镜
    BEF_CINE_MOVE_ALG_BREATH_V10,   // 呼吸运镜
    BEF_CINE_MOVE_ALG_ROT360_V11,       // 全域 POV
    BEF_CINE_MOVE_ALG_END
} bef_cine_move_alg_type;

typedef struct bef_ai_cine_move_input{
    int width;   // 输入数据的宽度
    int height;  // 输入数据的高度
    int stride;
    bef_ai_lens_data data;   // 输入数据的数据
    bef_ai_lens_data_type type; // 输入数据的类型，iOS 支持pixelbuffer 输出，Android 支持oes 纹理
}bef_ai_cine_move_input;

typedef struct bef_ai_cine_move_output{
    bef_ai_lens_data data;   // 输出类型数据，会根据输入，填充对应的输出部分
    int width;   // 输出数据的宽度
    int height;  // 输入数据的高度
}bef_ai_cine_move_output;

//**************  cine move end *****************************

//**************  video lite hdr start *****************************
typedef enum {
    BEF_HDR_TYPE_LITE_V5 = 0,       // HDR：性能效果平衡
    BEF_HDR_TYPE_LITE_V6 = 1,       // HDR：性能最好
    BEF_HDR_TYPE_LITE_V7 = 2,       // HDR：效果最好
    BEF_HDR_TYPE_LITE_V8 = 3,       // 色彩增强
    BEF_HDR_TYPE_UNKNOW,
} bef_ai_hdr_lite_alg_type;

typedef struct bef_ai_hdr_lite_init_config
{
    void* context;                          // 可以设置为NULL，iOS和mac可以传入MTLDevice，Windows可以传入D3D11Device
    const char* binPath;                    // Android和Windows传入可读写目录路径；iOS和mac传入vhdr.metallib文件路径
    bool  isExtOESTexture;                  // 是否为oes纹理，目前只支持非oes纹理
    int maxHeight;                          // 可支持最大输入帧的高
    int maxWidth;                           // 可支持最大输入帧的宽
    int perNum;                             // 每多少帧做一次曲线计算
    bef_ai_hdr_lite_alg_type algType;            // 子算法类型，默认使用 BEF_HDR_TYPE_LITE_V8
    bef_ai_pixel_format pixelFmt;                // 输入输出数据格式
    bef_ai_lens_power_level powerLevel;              // 性能模式 只有Android 高通手机有用
    bef_ai_lens_backend_type backendType;            // backend设置, 该算法统一为gpu
    const char* imgLutPath;                 // 原图lut映射表文件路径，只对BEF_HDR_TYPE_LITE_V8有效, 目前传空
    const char* skinLutPath;                // 肤色lut映射表文件路径，只对BEF_HDR_TYPE_LITE_V8有效，目前传空
    bool isNeedSkinSeg;                     // 是否需要做肤色分割，目前穿传false
    bool isCover;                           // 是否使用兜底版本，只对BEF_HDR_TYPE_LITE_V8有效
}bef_ai_hdr_init_config;


typedef struct bef_ai_hdr_lite_frame_info{
    bool        isFirstFrame;               // 是否为视频第一帧标志
    bool        isDay;                      // 是否为白天场景  true
    bool        isProtectFace;              // 是否需要做人脸保护 true
    bool        isAFS;                      // 是否需要做自适应锐化 true
    int         luminanceTarget;            // 亮度阈值 -1;
    float       luminanceFactor;            // 亮度系数 -1.0f
    float       contrast;                   // 对比度参数 -1.0f
    float       saturation;                 // 饱和度参数 -1.0f
    int         faceNum;                    // 人脸数 0
    bef_ai_rect*   faceList;                   // 人脸数据，传null
    int         faceLuminanceTarget;        // 人脸亮度阈值， -1
    float       faceLuminanceFactor;        // 人脸亮度阈值 -1
    float       sharpenStrength;            // 锐化参数 -1
    float       enhanceStrength;            // 增强系数 1.0
} bef_ai_hdr_lite_frame_info;

typedef struct bef_ai_hdr_lite_param{
    int  width;                             // 帧的宽
    int  height;                            // 帧的高
    bool open;                              // 动态开启/关闭算法
    int  textureId;                         // 输入纹理id
    float* stMatrix;                        // 如果是oes纹理,传入SurfaceTexture获取的纹理矩阵
    bef_ai_hdr_lite_frame_info* info;        // 帧信息
    void* skinSegPtr;                       // 传入肤色分割结果，cpu buffer地址，只对HDR_TYPE_LITE_V8有效
} bef_ai_hdr_lite_param;

typedef bef_ai_video_sr_input bef_ai_hdr_lite_input;
typedef bef_ai_video_sr_output bef_ai_hdr_lite_output;


//**************  video lite hdr end *****************************

//**************  video stab begin *****************************

// 算法防抖算法配置参数，用于控制防抖效果
typedef  struct {
    int videoStabSmoothRadius;  // [1, 100]
    float videoStabMaxCropRatio; //[0, 0.5]
    int videoStabMotionType; //{1, 2, 3}-> 1.:similarity 2:affine 3:homography
} bef_ai_video_stab_config;

// 输入帧的标识
typedef enum {
    BEF_STAB_FRAME_START = 0, // 输入算法首帧
    BEF_STAB_FRAME_EST = 1,   // 输入视频帧计算相机轨迹
    BEF_STAB_FRAME_WARP = 2  // 输入视频帧做形变
} bef_ai_stab_frame_type;

// 算法process 配置参数
typedef  struct {
    bef_ai_stab_frame_type frameType;  // 帧标识
    int width;
    int height;
    int step;
    bef_ai_lens_data_type fmt;  // 输入帧格式
    bool open;   // 是否打开算法
    int frameIdx;  // 默认值-1 只在帧标识为 STAB_FRAME_WARP 时有效，用来指定warp 的帧索引
} bef_ai_lens_video_stab_params;

// warp matrix 3x3
typedef struct {
    float M00, M01, M02;
    float M10, M11, M12;
    float M20, M21, M22;
} bef_ai_stab_matrix;

// 获取算法输出结果
typedef struct {
    bef_ai_stab_matrix* matrixList; // warp 矩阵列表，内存在算法内部分配
    int matrixNum;   // 矩阵数量，和视频帧总数对应
    int real_radius;  // 算法中实际使用的smooth radius, 通常和用户设定的相同，用户输入超出范围或特殊case下，算法内部会做调整
    float real_crop_ratio; // 算法中实际使用的crop ratio
} bef_ai_lens_video_stab_out;

//**************  video stab end *****************************
//**************  video deflickering begin *****************************
typedef enum {
    BEF_VIDEO_DEFLICKER_ALG_DELAY,
    BEF_VIDEO_DEFLICKER_ALG_FLASH,
}bef_ai_lens_video_deflicker_alg_type;

typedef struct bef_ai_video_deflicker_init_config{
    void* context;             // 可以设置为NULL，iOS可以传入MTLDevice
    const char* kernelBinPath; // 可读写的路径
    bool isExtOESTexture;
    int maxWidth;
    int maxHeight;
    bef_ai_lens_video_deflicker_alg_type algType;
    bef_ai_lens_data_type dataType;
    bef_ai_lens_power_level powerLevel;
    bef_ai_lens_backend_type backendType;
}bef_ai_video_deflicker_init_config;

typedef struct bef_ai_video_deflicker_process_config{
    int width;             // 帧的宽
    int height;            // 帧的高
    int strideWidth;       // 帧x方向的stride值
    int strideHeight;      // 帧y方向的stride值
    bool open;             // 动态开启/关闭算法
    int inputTextureId;    // 输入帧纹理id
    int isFirst;           // 是否为视频第一帧标志
    float blendRate;       // 算法参数1
    float kernelSize;      // 算法参数2
    float* stMatrix;       // 如果是oes纹理,传入SurfaceTexture获取的纹理矩阵
    bef_ai_lens_data data;
}bef_ai_video_deflicker_process_config;

typedef union bef_ai_lens_video_deflicker_data{
    int texture; // 如果是纹理，这里纹理的index
    void* buffer;   // 如果是数据输入，iOS 传入pixelBuffer的指针
}bef_ai_lens_video_deflicker_data;

//**************  video deflickering end *****************************

typedef uint64_t bef_image_quality_enhancement_handle;
#endif 
