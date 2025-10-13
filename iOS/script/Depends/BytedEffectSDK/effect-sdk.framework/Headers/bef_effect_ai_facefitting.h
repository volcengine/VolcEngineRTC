#ifndef BEF_EFFECT_AI_FACEFITTING
#define BEF_EFFECT_AI_FACEFITTING

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

#define BEF_FITTING_MAX_FACE 6 //最大支持的人脸数
typedef unsigned long long bef_ai_facefitting_handle;

typedef enum {
    BEF_AI_FACEFITTING_Camera_Orthographic = 0,
    BEF_AI_FACEFITTING_Camera_Perspective = 1
} bef_ai_facefitting_camera_type;

typedef enum {
    BEF_AI_FACEFITTING_Solver_Lambda = 1,      // Solver parameter
    BEF_AI_FACEFITTING_Solver_MaxIter = 2,
    BEF_AI_FACEFITTING_Solver_Eps = 3,
    BEF_AI_FACEFITTING_Solver_Ratio = 4,
    BEF_AI_FACEFITTING_Solver_Smooth = 5,
    BEF_AI_FACEFITTING_Solver_Camera_Type = 6,
    BEF_AI_FACEFITTING_Config_Cal_TB = 7,
    BEF_AI_FACEFITTING_Eyelash_Flag = 8,
    BEF_AI_FACEFITTING_Use_Semantic_Lmk = 9,
    BEF_AI_FACEFITTING_Mouth_BS_Limit = 10
} bef_ai_facefitting_param_type;

//manager memory by sdk， count与num的解释：count表示数组的长度，num表示数组具有多少元素， 例如 一个2d坐标点(x,y)数组  [x,y,x,y,x,y,x,y]  ===> count = 8, num = 4
typedef struct {
    int id;                     // 人脸sdk返回的id，用来表示这个mesh属于哪一个人脸
    float* vertex;        // 3d模型的顶点,  由sdk管理内存分配与释放
    int vertex_count;           // vertex数组的长度
    float* landmark;      // 3d模型投影会图像坐标的landmark坐标值数组. 由sdk管理内存分配与释放
    int landmark_count;         // landmark数组的长度
    float* param;         // 解优化的参数，[scale，rotatex, rotatey, rotatez, tx, ty, alpha0, alpha1 ......], manager memory by sdk
    int param_count;            // param数组的长度
    float mvp[16];              // 将vertex变为ndc坐标的矩阵
    float model[16];            // 包括了对原始模型的旋转平移缩放的模型矩阵         正交投影下使用
    float * normal;       // 模型空间下的法线， 长度和vertex_count是一样的,   由sdk管理内存分配与释放
    float * tangent;      // 模型空间下的切线， 长度和vertex_count是一样的,   由sdk管理内存分配与释放
    float * bitangent;    // 模型空间下的副切线， 长度和vertex_count是一样的,  由sdk管理内存分配与释放
    float rvec[3];              // opencv solvepnp输出的旋转向量
    float tvec[3];              // opencv solvepnp输出的平移向量
} bef_ai_facefitting_mesh_info;

// pack landmark
typedef struct {
    int id;                     // 人脸的id
    bef_ai_fpoint * landmark106;         // 106点数组               required
    bool eye_lv2;              // true 使用二级网络的眼睛             optional
    bool eyebrow_lv2;          // true 使用二级网络的眉毛             optional
    bool lips_lv2;             // true 使用二级网络的嘴巴             optional
    bool iris_lv2;             // true 使用二级网络的iris             optional
    bef_ai_fpoint * eye_left;       // 左眼关键点                  optional
    bef_ai_fpoint * eye_right;      // 右眼关键点                  optional
    bef_ai_fpoint * eyebrow_left;   // 左眉毛关键点                 optional
    bef_ai_fpoint * eyebrow_right;  // 右眉毛关键点                 optional
    bef_ai_fpoint * lips;           // 嘴唇关键点                  optional
    bef_ai_fpoint * left_iris;      // 左虹膜关键点             optional
    bef_ai_fpoint * right_iris;     // 右虹膜关键点             optional
} bef_ai_facefitting_landmark_info;

// pack input
typedef struct {
    bef_ai_facefitting_landmark_info face_landmark_info[BEF_FITTING_MAX_FACE];
    int face_landmark_info_count;                   //输入的人脸的个数
    int view_width;
    int view_height;
    float cameraParams[3];          // focal_length, centerx, centery
} bef_ai_facefitting_args;

//与模型文件一一对应, 内容不会改变的， 由sdk管理内存分配与释放
typedef struct {
    int version_code;                           // 模型的版本号
    float* uv;                            // 标准展开图像的 uv坐标, 由sdk管理内存分配与释放
    int uv_count;                               // uv数组的长度
    unsigned short* flist;                // 3d模型顶点 的索引数组(face),  由sdk管理内存分配与释放
    int flist_count;                            // flist数组的长度
    unsigned short* landmark_triangle;    // landmark做三角剖分后的三角形数组,    由sdk管理内存分配与释放
    int landmark_triangle_count;                // landmark数组的长度

    int num_vertex;                             // = uv_count/2 = vertex_count/3    表示顶点元素的个数，      uv是标准3d模型的展开后的2d坐标
    int num_flist;                              // = flist_count / 3                面的个数
    int num_landmark_triangle;                  // = landmark_triangle_count / 2    三角形的个数
    int mum_landmark;                           // = landmark_count / 3             landmrk的个数
    int num_param;                              // = param_count                    求解参数的个数
} bef_ai_facefitting_mesh_config;

//pack output
typedef struct {
    bef_ai_facefitting_mesh_info face_mesh_info[BEF_FITTING_MAX_FACE];
    int face_mesh_info_count;               //返回mesh的个数, 请使用face_mesh_info_count来取face_mesh_info的前几个的内容，不要越界！！
    bef_ai_facefitting_mesh_config face_mesh_config;
} bef_ai_facefitting_result;

/**
 * @param handle
 * @return
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_facefitting_create(bef_ai_facefitting_handle *handle);

/**
 * @param handle
 * @param model_path    模型文件的绝对路径
 * @return 
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_facefitting_init(bef_ai_facefitting_handle handle, const char *model_path);


/**
 * @param handle            bef_ai_facefitting_handle
 * @param type              bef_ai_facefitting_param_type
 * @param value             value
 * @return
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_facefitting_set_param(bef_ai_facefitting_handle handle, bef_ai_facefitting_param_type type, float value);

/**
 * 输入人脸id和106点关键点，返回mesh信息
 * @param handle
 * @param args  输入
 * @param ret   输出，该部分内存空间生命周期由sdk管理，会在内部分配空间
 * @return
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_do_fitting_3dmesh(bef_ai_facefitting_handle handle, bef_ai_facefitting_args* args, bef_ai_facefitting_result* ret);

/**
 * 释放内部资源，不使用的时候一定要调用
 * @param handle    调用后handle会重置为0
 * @return
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_facefitting_release(bef_ai_facefitting_handle handle);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_facefitting_malloc_result(bef_ai_facefitting_handle handle, bef_ai_facefitting_result ** result);


BEF_SDK_API bef_effect_result_t
bef_effect_ai_facefitting_free_result(bef_ai_facefitting_handle handle, bef_ai_facefitting_result * result);

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
/**
 * 离线鉴权
 * @param env JNIEnv
 * @param context jobject
 * @param handle handle
 * @param licensePath license path
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_facefitting_check_license(JNIEnv *env, jobject context, bef_ai_facefitting_handle handle, const char* licensePath);
#elif TARGET_OS_IPHONE
/**
 * 离线鉴权
 * @param handle handle
 * @param licensePath license path
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_facefitting_check_license(bef_ai_facefitting_handle handle, const char* licensePath);
#endif

BEF_SDK_API
bef_effect_result_t bef_effect_ai_facefitting_check_onine_license(bef_ai_facefitting_handle handle, const char *licensePath);


#endif // BEF_EFFECT_AI_FACEFITTING
