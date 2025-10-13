#ifndef _BEF_EFFECT_AI_SLAM_H
#define _BEF_EFFECT_AI_SLAM_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

typedef unsigned long long bef_ai_slam_handle;

typedef enum bef_ai_slam_image_color
{
    BEF_AI_SLAM_RGB = 0,
    BEF_AI_SLAM_BGR,
    BEF_AI_SLAM_GRAY,
}bef_ai_slam_image_color;

typedef enum bef_ai_slam_device_orientation
{
    BEF_AI_SLAM_Portrait = 0, // android: protrait
    BEF_AI_SLAM_LandscapeLeft,
    BEF_AI_SLAM_UpsideDown,
    BEF_AI_SLAM_LandscapeRight,  // android: landscape
}bef_ai_slam_device_orientation;

typedef struct bef_ai_slam_camera_intrinsic{
    float fx;  // focal length x
    float fy;  // focal length y
    float cx;  // optical center x
    float cy;  // optical center y
}bef_ai_slam_camera_intrinsic;

typedef enum {
    BEF_AI_SLAM_480P = 0,
    BEF_AI_SLAM_720P,
    BEF_AI_SLAM_360P,
    BEF_AI_SLAM_180P
}bef_ai_slam_resolution;

typedef enum {
    BEF_AI_SLAM_High_Accuracy = 0,
    BEF_AI_SLAM_Medium_Accuracy,
    BEF_AI_SLAM_Low_Accuracy
}bef_ai_slam_accuracy_level;

typedef enum {
    BEF_AI_SLAM_Tracking_ERROR = -1,    // Unknown error
    BEF_AI_SLAM_Tracking_INIT = 0,      // Initialization state
    BEF_AI_SLAM_Tracking_TRACKING,      // Tracking
    BEF_AI_SLAM_Tracking_LOST,          // Tracking lost
    
}bef_ai_slam_tracking_state;

typedef struct bef_ai_slam_camera_info
{
    bef_ai_slam_image_color color;
    int is_front;
    bef_ai_slam_device_orientation oriention;
    bef_ai_slam_camera_intrinsic camera_intrinsic;
    int  disable_internal_time_delay; // disable the internal correction of time delay
    float horizontal_fov;             // not used
    bef_ai_slam_resolution resolution;
    bool low_texture_enhanced;  // disable it to speed up but worse results on low-texture regions
    bef_ai_slam_accuracy_level level;// default value is Medium, use Low for faster version
    int is_video;                           // use video mode
    int run_gba;                            // use gba
    int easy_init;
                          // use fast initialization
    int width;
    int height;
    int enable_fusion;
    int enable_multi_planes;
    int enable_normal_model;
}bef_ai_slam_camera_info;

typedef struct bef_ai_slam_imu_info
{
    int has_accelerometer;  // TYPE_ACCELEROMETER
    int has_gyroscope;      // TYPE_GYROSCOPE
    int has_gravity;        // TYPE_GRAVITY
    int has_orientation;    // TYPE_GAME_ROTATION_VECTOR or TYPE_ROTATION_VECTOR
}bef_ai_slam_imu_info;

typedef struct bef_ai_slam_imu_data
{
    double acc[3];      // userAcceleration + gravity
    double gyro[3];     // gyro
    double gra[3];      // deprecated
    double wRb[9];      // attitude
    double time_stamp;  // unit: second
}bef_ai_slam_imu_data;


typedef enum bef_ai_slam_imu_data_type{
    BEF_AI_SLAM_IMU_ACCELEROMETER = 0,
    BEF_AI_SLAM_IMU_GYROSCOPE,
    BEF_AI_SLAM_IMU_GRAVITY
}bef_ai_slam_imu_data_type;


typedef struct bef_ai_slam_click_flag {
    int is_clicked;
    float x;  // normalized [0, 1] with screen width, which is the size of getIntrinsic
    float y;  // normalized [0, 1] with screen height, which is the size of getIntrinsic
}bef_ai_slam_click_flag;

typedef struct bef_ai_slam_pose{
    float R[9];  // row major 3x3 rotation matrix
    float T[3];  // 3x1 translation matrix
    bef_ai_slam_tracking_state state;
    int plane_detected;  // planeDetected 1,  otherwise 0
    double time_stamp;   // time for pose (unit is second), 0 for no time
}bef_ai_slam_pose;

typedef struct bef_ai_slam_plane {
    int has_plane;          // 1 for detected plane, 0 for none
    float normal[3];        // plane normal in world frame
    float offset;           // signed distance from world origin to plane in world frame.
    float origin_world[3];  // plane origin in world frame
    float origin[2];        // plane origin on image
    float* boundary;  // plane boundary polygon on image [x1, y1, x2, y2, ...] (NULL if no boundary or
                      // out of frame)
    int boundary_size;  // plane boundary vertex size (not array size)
    int* plane_points_ids;
    int plane_points_size;
}bef_ai_slam_plane;

typedef struct bef_ai_slam_feature_points
{
    int point_size;  // number of points
    float* points;   // points: [x1, y1, x2, y2, ...] (NULL if no points)
    float* depths;   // depths: [d1, d2, ...] (NULL if no points or depths)
    int* ids;        // ids: [i1, i2, ...] (NULL if no points of ids)
}bef_ai_slam_feature_points;


typedef enum {
    BEF_AI_SLAM_HorizontalPlaneTracking = 2,
    BEF_AI_SLAM_RegionTracking,
}bef_ai_slam_version;


/// Init camera info
/// @param info camera info result
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_init_camera_info(bef_ai_slam_camera_info* info);

/// create slam handle
/// @param handle ret handle
/// @param modelPath slam model path
/// @param deviceName device name
/// @param camera camera info
/// @param imu imu info data
/// @param version different slam version
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_create(bef_ai_slam_handle *handle, const char* modelPath, const char* deviceName, bef_ai_slam_camera_info* camera, bef_ai_slam_imu_info imu, bef_ai_slam_version version);

/// change slam version
/// @param version slam version
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_set_version(bef_ai_slam_handle handle, bef_ai_slam_version version);

/// set imu info, only ios use
/// @param handle created slam handle
/// @param imuData imudata
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_set_imuinfo(bef_ai_slam_handle handle, const bef_ai_slam_imu_data* imuData);

/// set detail imu info, android only
/// @param handle created slam handle
/// @param type device sensor type
/// @param x x
/// @param y y
/// @param z z
/// @param timeStamp timeStamp
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_set_detail_imuinfo(bef_ai_slam_handle handle, bef_ai_slam_imu_data_type type, double x, double y, double z, double timeStamp);

/// set rotation vector, android only
/// @param handle created slam handle
/// @param rb[9] rotation vectiron
/// @param timeStamp timeStamp
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_set_rotation_vector(bef_ai_slam_handle handle, const double rb[9], double timeStamp);

/// slam detect plane and calc hitpoint when needed
/// @param created slam handle
/// @param image image buffer data
/// @param width image buffer width
/// @param height image buffer height
/// @param channels image channels
/// @param imageStride image stride
/// @param timeStamp timeStamp
/// @param flag click flag
/// @param pose camera pose
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_detect(bef_ai_slam_handle handle, const unsigned char* image, int width, int height, int channels,
                          int imageStride, double timeStamp , bef_ai_slam_click_flag flag, bef_ai_slam_pose* pose);

/// get slam pose, call this function when camera pose is available
/// @param handle slam handle
/// @param cameraPose camera pose from uppder function
/// @param forceFacing 1
/// @param flag click flog
/// @param retPose plane pose
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_get_plane_pose(bef_ai_slam_handle handle, bef_ai_slam_pose cameraPose, int forceFacing, bef_ai_slam_click_flag flag,
                                  bef_ai_slam_pose* retPose);

/// get plane info, current no use
/// @param handle slam handle
/// @param cameraPose camera pose
/// @param returnBoundary returnBoundary
/// @param plane plane info
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_get_plane(bef_ai_slam_handle handle, bef_ai_slam_pose cameraPose, int returnBoundary, bef_ai_slam_plane* plane);

/// release plane info
/// @param plane release plane addr
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_release_plane(bef_ai_slam_handle, bef_ai_slam_plane* plane);

/// get feature points
/// @param handle slam handle
/// @param points feature points
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_get_feature_points(bef_ai_slam_handle handle, bef_ai_slam_feature_points* points);

/// release feature points
/// @param points feature points
BEF_SDK_API void
bef_effect_ai_slam_release_feature_points(bef_ai_slam_handle, bef_ai_slam_feature_points* points);

/// get camera intrincis
/// @param device_name device name
/// @param param_file device camera intrinsic file
/// @param width image buffer width
/// @param height image buffer height
/// @param intrinsic camera instrinsic
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_get_intrinsic(bef_ai_slam_handle, const char* device_name, const char* param_file, int width, int height, bef_ai_slam_camera_intrinsic* intrinsic);

/// reset slam handle
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_reset(bef_ai_slam_handle);

/// destroy slam handle
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_destroy(bef_ai_slam_handle);

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
/// check license offline
/// @param env JNIEnv
/// @param context jobject
/// @param handle slam handle
/// @param licensePath license path
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_check_license(JNIEnv *env, jobject context, bef_ai_slam_handle handle, const char* licensePath);
#elif TARGET_OS_IPHONE
/// check license offline
/// @param handle slam handle
/// @param licensePath license path
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_check_license(bef_ai_slam_handle handle, const char* licensePath);
#endif

/// check license online
/// @param handle slam handle
/// @param licensePath license path
BEF_SDK_API bef_effect_result_t
bef_effect_ai_slam_check_online_license(bef_ai_slam_handle handle, const char *licensePath);
#endif
