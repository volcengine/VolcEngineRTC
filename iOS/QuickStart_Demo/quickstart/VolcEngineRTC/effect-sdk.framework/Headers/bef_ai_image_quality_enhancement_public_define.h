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

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
typedef enum bef_ai_lens_power_level{
    BEF_AI_LENS_POWER_LEVEL_DEFAULT = 0,
    BEF_AI_LENS_POWER_LEVEL_LOW,
    BEF_AI_LENS_POWER_LEVEL_NORMAL,
    BEF_AI_LENS_POWER_LEVEL_HIGH,
    BEF_AI_LENS_POWER_LEVEL_AUTO,
} bef_ai_lens_power_level;

#endif

typedef enum bef_ai_lens_data_type{
    BEF_AI_LENS_ANDROID_TEXTURE_RGBA,
    BEF_AI_LENS_ANDROID_TEXTURE_OES,
    BEF_AI_LENS_METAL_TEXTURE_RGBA,
    BEF_AI_LENS_PXIELBUFFER_NV12,
    BEF_AI_LENS_METAL_TEXTURE_NV12,
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
    BEF_AI_LENS_BACKEND_GPU = 0,
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

typedef uint64_t bef_image_quality_enhancement_handle;
#endif 
