#ifndef  _BEF_EFFECT_AI_OBJECT_TRACKING_H
#define  _BEF_EFFECT_AI_OBJECT_TRACKING_H
#include "bef_effect_ai_public_define.h"

typedef unsigned long long bef_ai_object_tracking_handle;

typedef enum {
    /// Original speed, slowest, but the accuracy is the highest
    bef_ai_object_tracking_speed_orig = 0,
    /// First level speed-up, faster compared with original speed, at the cost
    /// of some accucacy
    bef_ai_object_tracking_speed_up1 = 1,
    /// Second level speed-up, even faster than SpeedUp1, at the cost of more
    /// accuracy
    bef_ai_object_tracking_speed_up2 = 2,
} bef_ai_object_tracking_speed;


typedef struct bef_ai_object_tracking_param{
/// Whether redetection is needed when tracking is lost.
    /// Default to true.
    bool needRedetection;
    /// Whether we need to reset tracking state. Reseting tracking states is
    /// used for tracking in recorded videos (e.g. pinning stickers), but for
    /// realtime videos (e.g. camera capture session) it is not needed and
    /// should be set to false.\n Default to true.
    bool needReset;
    /// Whether we perform texture evaluation for user-inputed bounding box.
    /// This is to help filtering out some bounding boxes that are certained
    /// to be hard to track, such as bounding boxes with no textures inside
    /// and at its surroundings.\n
    /// Default to true.\n
    bool needInitialBboxEvaluation;

    /// Padding for bounding box search area. Larger number
    /// leads to more robust tracking due to looking at larger areas, but
    /// at the cost of longer computation time per frame.\n
    /// Default value is 1.2, generally range from 1.0 to 2.0.
    float padding;

    /// @name Tracking related parameters
    /// Model potential scaling/rotating changes.\n
    /// track***Step: step size of each level of scale/angle change.\n
    /// trackNum***: number of levels for scale/angle change.\n
    /// More explanation: scale/level change works in both directions. For
    /// example, when the trackNumAngle is 3 and trackAngleStep is 15.f, this
    /// means the tracking algorithm will model 3 different scenarios: -15
    /// degrees, 0 degree and +15 degrees. Similar for scaling, when
    /// trackScaleStep is 2.0 and trackNumScale is 3, the algorithm will
    /// model original size, original size * 2, and original size / 2.\n
    /// trackNumScale and trackNumAngle should be odd numbers. When even numbers
    /// are used, the algorithm will add 1 to trackNumScale/trackNumAngle to
    /// make them odd numbers.\n Default values:\n trackAngleStep: 15.f (15
    /// degree)\n trackScaleStep: 1.1f\n trackNumScale: 3\n trackNumAngle: 3\n
    ///@{
    float trackAngleStep;
    float trackScaleStep;
    int trackNumScale;
    int trackNumAngle;
    ///@}

    /// @name Detection related parameters.
    ///  detect***Step and detectNum*** behaves
    /// similar to tracking related parameters.\n
    /// detect***GridNum: number of segments per horizontal/vertical direction
    /// of the image. In each frame, we look into one position in each segment
    /// in horizontal/vertical direction. Thus, if detectHorizontalGridNum is 3
    /// and detectVerticalGridNum is 2, we will look into 2*3 = 6 positions
    /// each frame.\n
    /// default values:\n
    /// detectAngleStep: 15.f (15 degree)\n
    /// detectScaleStep: 2.f\n
    /// detectNumScale: 3\n
    /// detectNumAngle: 3\n
    /// detectHorizontalGridNum: 2\n
    /// detectVerticalGridNum: 2\n
    ///@{
    float detectAngleStep;
    float detectScaleStep;
    int detectNumScale;
    int detectNumAngle;
    int detectHorizontalGridNum;
    int detectVerticalGridNum;
    ///@}

    /// @name Feature score thresholds for detection/tracking
    /// Tracking has only one threshold, while detection has two: a
    /// candidate proposal threshold and a candidate confirmation threshold.
    /// Generally the candidate proposal threshold could be smaller than
    /// tracking threshold, and the condidate confirmation threshold is
    /// larger than tracking threshold.\n
    /// default values:\n
    /// trackThresh: 0.15f\n
    /// detectProposeCandidateThresh: 0.8f * trackThresh;\n
    /// detectConfirmCandidateThresh: 2.f * trackThresh;\n
    ///@{
    float trackThresh;
    float detectProposeCandidateThresh;
    float detectConfirmCandidateThresh;
    ///@}

    /// Control general tracking speed. See Bingo_ObjectTracking_Speed for
    /// details
    bef_ai_object_tracking_speed speed;

}bef_ai_object_tracking_param;

typedef enum {
    bef_ai_object_tracking_init_bbox_invalid_handle = -1,
    /// bounding box initialization success
    bef_ai_object_tracking_init_bbox_success = 0,
    /// Image in bbox has no texture.
    bef_ai_object_tracking_init_bbox_no_texture = 1,
    /// Image failes during initial bounding box tracking step
    bef_ai_object_tracking_init_bbox_image_feature_extract_fail = 2,
}  bef_ai_object_tracking_init_bbox_status;


// general definition of bounding box
typedef struct bef_ai_object_tracking_bounding_box
{
    float centerX;
    float centerY;  // center position of bounding box
    float width;
    float height;  // please refer to image above for width and height definition
    float rotateAngle;  // clockwise rotate angle, in range [0, 360)
} bef_ai_object_tracking_bounding_box;

typedef enum {
    bef_ai_object_tracking_status_unavailable = 0,
    bef_ai_object_tracking_status_tracked = 1,
    bef_ai_object_tracking_status_losing = 2,
    bef_ai_object_tracking_status_lost = 3,
} bef_ai_object_tracking_status;

typedef struct  bef_ai_object_tracking_bbox
{
    bef_ai_object_tracking_bounding_box bbox;
    float timestamp;

    /// StatusTracked or StatusLost
    bef_ai_object_tracking_status status;
} bef_ai_object_tracking_bbox;


BEF_SDK_API bef_effect_result_t
bef_ai_object_tracking_create(bef_ai_object_tracking_handle *handle);

BEF_SDK_API bef_effect_result_t
bef_ai_object_tracking_destroy(bef_ai_object_tracking_handle handle);


BEF_SDK_API bef_effect_result_t
bef_ai_object_tracking_init(bef_ai_object_tracking_handle handle, const char* modelPath, bef_ai_object_tracking_param *param);

BEF_SDK_API void
bef_ai_object_tracking_get_default_param(bef_ai_object_tracking_handle handle, bef_ai_object_tracking_param* param);

BEF_SDK_API bef_ai_object_tracking_init_bbox_status
bef_ai_object_tracking_set_initial_bbox(bef_ai_object_tracking_handle handle, const unsigned char* image, bef_ai_pixel_format format, int width, int height, int channels,
                                        int imageStride, bef_ai_object_tracking_bbox* initialBox);

BEF_SDK_API bef_effect_result_t
bef_ai_object_tracking_track_frame(bef_ai_object_tracking_handle handle, const unsigned char* image, bef_ai_pixel_format format, int width, int height, int channels,
                                   int imageStride, float timeStamp, bef_ai_object_tracking_bbox* result);



#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
/// check license offline
/// @param env JNIEnv
/// @param context jobject
/// @param handle bef_ai_object_tracking_handle
/// @param licensePath license path
BEF_SDK_API bef_effect_result_t
bef_ai_object_tracking_check_license(JNIEnv *env, jobject context, bef_ai_object_tracking_handle handle, const char* licensePath);
#elif TARGET_OS_IPHONE
/// check license offline
/// @param bef_ai_object_tracking_handle handle
/// @param licensePath license path
BEF_SDK_API bef_effect_result_t
bef_ai_object_tracking_check_license(bef_ai_object_tracking_handle handle, const char* licensePath);
#endif

/// check license online
/// @param bef_ai_object_tracking_handle handle
/// @param licensePath license path
BEF_SDK_API bef_effect_result_t
bef_ai_object_tracking_check_online_license(bef_ai_object_tracking_handle handle, const char *licensePath);

#endif