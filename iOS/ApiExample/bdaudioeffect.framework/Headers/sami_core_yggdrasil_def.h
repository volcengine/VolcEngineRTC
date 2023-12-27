//
// Created by xiangning zhu on 2021/12/16.
//

#ifndef SAMI_CORE_SAMI_CORE_YGGDRASIL_DEF_H
#define SAMI_CORE_SAMI_CORE_YGGDRASIL_DEF_H
#include "sami_core_base_def.h"

typedef enum {
    SAMICore_YGG_BINAURAL_OUT,
    SAMICore_YGG_LOUDSPEAKERS_OUT,
} SAMICoreYggdrasilPlaybackMode;

typedef enum {
    SAMICoreYGG_REALTIME_LATE_REVERB = 0,
    SAMICoreYGG_BAKED_LATE_REVERB = 1,
    SAMICoreYGG_SHARED_SPECTRAL_LATE_REVERB = 2,
} SAMICoreYggdrasilLateReverbUpdatingMode;

typedef enum {
    SAMICoreYGG_IR_LATE_REVERB = 0,
    SAMICoreYGG_SPECTRAL_LATE_REVERB = 1,
} SAMICoreYggdrasilLateReverbRenderingMode;

typedef enum {
    SAMICoreYGG_LOW_QUALITY = 0,
    SAMICoreYGG_MEDIUM_QUALITY = 1,
    SAMICoreYGG_HIGH_QUALITY = 2,
    SAMICoreYGG_AMBISONIC_FIRST_ORDER,
    SAMICoreYGG_AMBISONIC_SECOND_ORDER,
    SAMICoreYGG_AMBISONIC_THIRD_ORDER,
    SAMICoreYGG_AMBISONIC_FOURTH_ORDER,
    SAMICoreYGG_AMBISONIC_FIFTH_ORDER,
    SAMICoreYGG_AMBISONIC_SIXTH_ORDER,
    SAMICoreYGG_AMBISONIC_SEVENTH_ORDER,
} SAMICoreYggdrasilRenderingMode;

typedef enum {
    SAMICoreYGG_SOURCE_SPATIALIZE = 0,
    SAMICoreYGG_SOURCE_BYPASS = 1,
} SAMICoreYggdrasilSourceMode;

typedef enum {
    SAMICorePER_PARTITION_SWAPPING = 0,
    SAMICoreINTER_PARTITION_LINEAR_CROSS_FADE = 1,
    SAMICoreINTER_PARTITION_POWER_COMPLEMENTARY_CROSS_FADE = 2
} SAMICoreYggdrasilIrUpdateMethod;

typedef enum {
    SAMICoreYGG_MATERIAL_AcousticTile,
    SAMICoreYGG_MATERIAL_Brick,
    SAMICoreYGG_MATERIAL_BrickPainted,
    SAMICoreYGG_MATERIAL_Carpet,
    SAMICoreYGG_MATERIAL_CarpetHeavy,
    SAMICoreYGG_MATERIAL_CarpetHeavyPadded,
    SAMICoreYGG_MATERIAL_CeramicTile,
    SAMICoreYGG_MATERIAL_Concrete,
    SAMICoreYGG_MATERIAL_ConcreteRough,
    SAMICoreYGG_MATERIAL_ConcreteBlock,
    SAMICoreYGG_MATERIAL_ConcreteBlockPainted,
    SAMICoreYGG_MATERIAL_Curtain,
    SAMICoreYGG_MATERIAL_Foliage,
    SAMICoreYGG_MATERIAL_Glass,
    SAMICoreYGG_MATERIAL_GlassHeavy,
    SAMICoreYGG_MATERIAL_Grass,
    SAMICoreYGG_MATERIAL_Gravel,
    SAMICoreYGG_MATERIAL_GypsumBoard,
    SAMICoreYGG_MATERIAL_PlasterOnBrick,
    SAMICoreYGG_MATERIAL_PlasterOnConcreteBlock,
    SAMICoreYGG_MATERIAL_Soil,
    SAMICoreYGG_MATERIAL_SoundProof,
    SAMICoreYGG_MATERIAL_Snow,
    SAMICoreYGG_MATERIAL_Steel,
    SAMICoreYGG_MATERIAL_Water,
    SAMICoreYGG_MATERIAL_WoodThin,
    SAMICoreYGG_MATERIAL_WoodThick,
    SAMICoreYGG_MATERIAL_WoodFloor,
    SAMICoreYGG_MATERIAL_WoodOnConcrete,
    SAMICoreYGG_MATERIAL_COUNT,
} SAMICoreYggdrasilAcousticsMaterial;

typedef enum {
    SAMICoreYGG_SN3D,
    SAMICoreYGG_N3D
} SAMICoreYggdrasilAmbisonicNormalizationType;

typedef struct yggdrasilCreateParameter{
    SAMICoreYggdrasilRenderingMode mode;
    unsigned int frames_per_buffer;
    unsigned int sample_rate;
} SAMICoreYggdrasilCreateParameter;

typedef struct yggdrasilMesh{
    const float* vertices;
    int vertices_count;
    const int *indices;
    int indices_count;
    SAMICoreYggdrasilAcousticsMaterial material;
    int geometry_id;
} SAMICoreYggdrasilMesh;


typedef struct yggdrasilMeshAndMaterialFactor{
    const float* vertices;
    int vertices_count;
    const int *indices;
    int indices_count;
    const float *absorption_factor;
    float scattering_factor;
    float transmission_factor;
    int geometry_id;
} SAMICoreYggdrasilMeshAndMaterialFactor;

typedef struct yggdrasilFactor{
    SAMICoreYggdrasilAcousticsMaterial material;
    float * factor;
    int len;
} SAMICoreYggdrasilFactor;

typedef struct yggdrasilSource{
    int source_id;
    SAMICoreYggdrasilSourceMode* mode;
    const float* position;
    const float* gain;
    const float* volumetric_size;
    bool is_async;
} SAMICoreYggdrasilSource;

/**
 * this struct use to set SourceRemove params
 * @param source_id  source id;
 * @param is_async whether use async mode;
 */
typedef struct yggdrasilSourceRemove{
    int source_id;
    bool is_async;
} SAMICoreYggdrasilSourceRemove;

typedef struct yggdrasilSourceOrientation{
    SAMICoreYggdrasilSourceMode mode;
    const float *position;
    const float *front;
    const float *up;
    float radius;
    int source_id;
    bool is_async;
} SAMICoreYggdrasilSourceOrientation;

/**
 * this struct use to set SourceConfig params
 * @param position indicating source position, which corresponds to {X, Y, Z} (meters);
 * @param front indicating source front direction, which defaults to Z axis positive direction;
 * @param up indicating source up direction, which defaults to Y axis positive direction;
 * @param radius Radius of ray tracing detection sphere (meter);
 * @param directivity_alpha Weighting balance between figure of eight pattern and circular pattern for source emission in range [0, 1];
 * @param directivity_order order applied to computed directivity. Higher values will result in narrower and sharper directivity patterns. Range [1, inf);
 * @param use_direct_path_spread alternatively, we could use spread param directly, this is useful when audio middleware specifies spread value by itself;
 * @param direct_path_spread Master gain of sound source;
 * @param source_gain Reflection gain relative to default (master gain);
 * @param reflection_gain whether use async mode;
 * @param enable_doppler Turn on/off doppler effect for this source;
 */
typedef struct yggdrasilAudioSourceConfig {
    SAMICoreYggdrasilSourceMode mode;
    float *position;
    float *front;
    float *up;
    float radius;
    float directivity_alpha;
    float directivity_order;
    bool use_direct_path_spread;
    float direct_path_spread;
    float source_gain;
    float reflection_gain;
    bool enable_doppler;
} SAMICoreYggdrasilAudioSourceConfig;

typedef struct yggdrasilSourceConfig{
    SAMICoreYggdrasilAudioSourceConfig *config;
    int source_id;
    bool is_async;
} SAMICoreYggdrasilSourceConfig;

typedef struct yggdrasilSourceBuffer{
    int source_id;
    const float *input_buffer_ptr;
    unsigned int num_frames;
}SAMICoreYggdrasilSourceBuffer;

typedef struct yggdrasilAmbisonicChannelBuffer{
    const float *ambisonic_channel_buffer;
    int order;
    int degree;
    SAMICoreYggdrasilAmbisonicNormalizationType norm_type;
    float gain;
} SAMICoreYggdrasilAmbisonicBuffer;

typedef struct yggdrasilMatrixInputBuffer{
    const float *input_buffer;
    int input_channel_index;
} SAMICoreYggdrasilMatrixInputBuffer;

typedef struct yggdrasilBinauralBuffer{
    float *const *output_buffer_ptr;
    unsigned int num_frames;
    unsigned int num_channels;
    int isInterleave;
    bool is_accumulative;
} SAMICoreYggdrasilBinauralBuffer;

typedef struct audioBuffer SAMICoreYggdrasilLoudSpeakers;

typedef enum {
    SAMICORE_YGGDRASIL_SURROUND = 0,
    SAMICORE_YGGDRASIL_AMBIX = 1,
    SAMICORE_YGGDRASIL_AMBIX_WITH_HEADLOCK = 2,
    SAMICORE_YGGDRASIL_FUMA = 3,
    SAMICORE_YGGDRASIL_TBE = 4,
} SAMICoreYggdrasilChannelConfig;

typedef unsigned int SAMICoreYggdrasilChannelMask;

typedef struct yggdrasilPlanarPresetInputBuffer{
    const float* const* input_buffer;
    unsigned int num_channel;
    unsigned int num_frames;
    SAMICoreYggdrasilChannelConfig channel_config;
    SAMICoreYggdrasilChannelMask channel_mask;
    bool discard_lfe;
} SAMICoreYggdrasilPlanarPresetInputBuffer;

typedef struct yggdrasilListenerPoseFromUnityScene{
    const float screen_position_x;
    const float screen_position_y;
    const float screen_position_z;
    const float screen_front_x;
    const float screen_front_y;
    const float screen_front_z;
    const float screen_up_x;
    const float screen_up_y;
    const float screen_up_z;
    const float listener_position_x;
    const float listener_position_y;
    const float listener_position_z;
    const float listener_front_x;
    const float listener_front_y;
    const float listener_front_z;
    const float listener_up_x;
    const float listener_up_y;
    const float listener_up_z;
    float* out_listener_position_x;
    float* out_listener_position_y;
    float* out_listener_position_z;
    float* out_listener_front_x;
    float* out_listener_front_y;
    float* out_listener_front_z;
    float* out_listener_up_x;
    float* out_listener_up_y;
    float* out_listener_up_z;
} SAMICoreYggdrasilListenerPoseFromUnityScene;

typedef struct yggdrasilDopplerEffect{
    int source_id;
    int on;
} SAMICoreYggdrasilDopplerEffect;

typedef struct yggdrasilLoudSpeakerArray{
    const float *positions;
    int num_loudspeakers;
} SAMICoreYggdrasilLoudSpeakerArray;

typedef struct yggdrasilMappingMatrix{
    const float *matrix;
    int num_input_channels;
    int num_output_channels;
} SAMICoreYggdrasilMappingMatrix;

typedef struct yggdrasilAmbisonicOrientation{
    const float *front;
    const float *up;
} SAMICoreYggdrasilAmbisonicOrientation;

typedef struct yggdrasilListener{
    const float *position;
    const float *front;
    const float *up;
} SAMICoreYggdrasilListener;

#endif  //SAMI_CORE_SAMI_CORE_YGGDRASIL_DEF_H
