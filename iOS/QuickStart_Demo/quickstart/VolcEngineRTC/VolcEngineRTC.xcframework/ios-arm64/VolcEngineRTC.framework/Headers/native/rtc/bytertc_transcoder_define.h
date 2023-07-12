/*
 * Copyright 2021 @bytedance
 *  Created on: june 20, 2021
 */

#pragma once
#include "bytertc_video_frame.h"
#include "bytertc_audio_frame.h"
#include "bytertc_transcoder_base_interface.h"

namespace bytertc {
/** 
 * @type keytype
 * @brief 转推直播事件
 */
enum StreamMixingEvent {
    /**
     * @hidden for internal use only
     */
    kStreamMixingBase = 0,
    /** 
     * @brief 请求发起转推直播任务
     */
    kStreamMixingStart = 1,
    /** 
     * @brief 发起转推直播任务成功
     */
    kStreamMixingStartSuccess = 2,
    /** 
     * @brief 发起转推直播任务失败
     */
    kStreamMixingStartFailed = 3,
    /** 
     * @brief 请求更新转推直播任务配置
     */
    kStreamMixingUpdate = 4,
    /** 
     * @brief 成功更新转推直播任务配置
     */
    kStreamMixingUpdateSuccess = 5,
    /** 
     * @brief 更新转推直播任务配置失败
     */
    kStreamMixingUpdateFailed = 6,
    /** 
     * @brief 请求结束转推直播任务
     */
    kStreamMixingStop = 7,
    /** 
     * @brief 结束转推直播任务成功
     */
    kStreamMixingStopSuccess = 8,
    /** 
     * @brief 结束转推直播任务失败
     */
    kStreamMixingStopFailed = 9,
    /** 
     * @brief 更新转推直播任务配置的请求超时
     */
    kStreamMixingChangeMixType = 10,
    /** 
     * @brief 得到客户端合流音频首帧
     */
    kStreamMixingFirstAudioFrameByClientMix = 11,
    /** 
     * @brief 收到客户端合流视频首帧
     */
    kStreamMixingFirstVideoFrameByClientMix = 12,
    /** 
     * @brief 更新转推直播任务配置超时
     */
    kStreamMixingUpdateTimeout = 13,
    /** 
     * @brief 发起转推直播任务配置超时
     */
    kStreamMixingStartTimeout = 14,
    /** 
     * @brief 合流布局参数错误
     */
    kStreamMixingRequestParamError = 15,
    /** 
    * @brief 合流加图片
    */
    kStreamMixingMixImageEvent = 16,
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @brief 单通合唱事件
     */
    kStreamMixingMixSingleWayChorusEvent = 17,
};


/** 
 * @type errorcode
 * @brief 单流转推直播错误码
 */
enum SingleStreamPushEvent {
    /**
     * @hidden for internal use only
     */
    kSingleStreamPushBase = 0,
    /** 
    * @brief 开始推流。
    */
   kSingleStreamPushStart = 1,
    /** 
    * @brief 推流成功。
    */
   kSingleStreamPushSuccess = 2,
    /** 
    * @brief 推流失败。
    */
   kSingleStreamPushFailed = 3,
    /** 
     * @brief 停止推流。
     */
    kSingleStreamPushStop = 4,
    /** 
    * @brief 单流转推直播任务处理超时，请检查网络状态并重试。
    */
   kSingleStreamPushTimeout = 5,
    /** 
     * @brief 参数错误。
     */
    kSingleStreamPushParamError = 6,
};

/** 
 * @type errorcode
 * @brief 转推直播错误码
 */
enum StreamMixingErrorCode {
    /** 
     * @brief 推流成功。
     */
    kStreamMixingErrorOK = 0,
    /** 
     * @brief 未定义的合流错误
     */
    kStreamMixingErrorBase= 1090,
    /** 
     * @brief 客户端 SDK 检测到无效推流参数。
     */
    kStreamMixingErrorInvalidParam = 1091,
    /** 
     * @brief 状态错误，需要在状态机正常状态下发起操作
     */
    kStreamMixingErrorInvalidState = 1092,
    /** 
     * @brief 无效操作
     */
    kStreamMixingErrorInvalidOperator = 1093,
    /** 
     * @brief 转推直播任务处理超时，请检查网络状态并重试
     */
    kStreamMixingErrorTimeout = 1094,
    /** 
     * @brief 服务端检测到错误的推流参数
     */
    kStreamMixingErrorInvalidParamByServer = 1095,
    /** 
     * @brief 对流的订阅超时
     */
    kStreamMixingErrorSubTimeoutByServer = 1096,
    /** 
     * @brief 合流服务端内部错误。
     */
    kStreamMixingErrorInvalidStateByServer = 1097,
    /** 
     * @brief 合流服务端推 CDN 失败。
     */
    kStreamMixingErrorAuthenticationByCDN  = 1098,
    /** 
     * @brief 服务端接收信令超时，请检查网络状态并重试。
     */
    kStreamMixingErrorTimeoutBySignaling = 1099,
    /** 
     * @brief 图片合流失败。
     */
    kStreamMixingErrorMixImageFail = 1100,
    /** 
     * @brief 服务端未知错误。
     */
    kStreamMixingErrorUnKnownByServer = 1101,
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @brief 缓存未同步。
     */
    kStreamMixingErrorStreamSyncWorse = 1102,
    /** 
     * @hidden 只供内部使用
     * @brief 合流消息中的用户布局信息发生了变化。
     */
    kStreamMixingErrorUpdateRegionChanged = 1103,
    /**
     * @hidden for internal use only
     */
    kStreamMixingErrorMax = 1199,
};

/** 
 * @type keytype
 * @brief 合流类型(新)
 */
enum MixedStreamType {
    /** 
     * @brief 服务端合流
     */
    kMixedStreamTypeByServer = 0,
    /** 
     * @brief 端云一体合流
     */
    kMixedStreamTypeByClient = 1,
};


/** 
 * @type keytype
 * @brief AAC 编码规格(新)。
 */
enum MixedStreamAudioProfile {
    /** 
     * @brief AAC-LC 规格，默认值。
     */
    kMixedStreamAudioProfileLC = 0,
    /** 
     * @brief HE-AAC v1 规格。
     */
    kMixedStreamAudioProfileHEv1 = 1,
    /** 
     * @brief HE-AAC v2 规格。
     */
    kMixedStreamAudioProfileHEv2 = 2,
};

/** 
 * @type keytype
 * @brief 音频编码格式(新)。
 */
enum MixedStreamAudioCodecType {
    /** 
     * @brief AAC 格式。
     */
    kMixedStreamAudioCodecTypeAAC = 0,
};

/** 
 * @type keytype
 * @brief 视频编码格式(新)。
 */
enum MixedStreamVideoCodecType {
    /** 
     * @brief H.264 格式，默认值。
     */
    kMixedStreamVideoCodecTypeH264 = 0,
    /** 
     * @brief ByteVC1 格式。
     */
    kMixedStreamVideoCodecTypeByteVC1 = 1,
};

/** 
 * @type keytype
 * @brief 图片或视频流的缩放模式(新)。
 */
enum MixedStreamRenderMode {
    /** 
     * @brief 视窗填满优先，默认值。
     *        视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    kMixedStreamRenderModeHidden = 1,
    /** 
     * @brief 视频帧内容全部显示优先。
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。
     */
    kMixedStreamRenderModeFit = 2,
    /** 
     * @brief 视频帧自适应画布。
     *        视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
    kMixedStreamRenderModeAdaptive = 3,
};

/** 
 * @type keytype
 * @brief 合流输出内容类型(新)。
 */
enum MixedStreamMediaType {
    /** 
     * @brief 输出的混流包含音频和视频
     */
    kMixedStreamMediaTypeAudioAndVideo = 0,
    /** 
     * @brief 输出的混流只包含音频
     */
    kMixedStreamMediaTypeAudioOnly = 1,
    /** 
     * @brief 输出的混流只包含视频
     */
    kMixedStreamMediaTypeVideoOnly = 2,
};

/** 
 * @type keytype
 * @brief 合流布局区域类型(新)。
 */
enum MixedStreamLayoutRegionType {
    /** 
     * @brief 合流布局区域类型为视频。
     */
    kMixedStreamLayoutRegionTypeVideoStream = 0,
    /** 
     * @brief 合流布局区域类型为图片。
     */
    kMixedStreamLayoutRegionTypeImage = 1,
};

/** 
 * @type keytype
 * @brief 客户端合流回调视频格式(新)。设置为系统不支持的格式时，自动回调系统默认格式。
 */
enum MixedStreamClientMixVideoFormat {
    /** 
     * @brief YUV I420。Android、Windows 默认回调格式。支持系统：Android、Windows。
     */
    kMixedStreamClientMixVideoFormatI420 = 0,
    /** 
     * @brief OpenGL GL_TEXTURE_2D 格式纹理。支持系统：安卓。
     */
    kMixedStreamClientMixVideoFormatTexture2D = 1,
    /** 
     * @brief CVPixelBuffer BGRA。iOS 默认回调格式。支持系统: iOS。
     */
    kMixedStreamClientMixVideoFormatCVPixelBufferBGRA = 2,
    /** 
     * @brief YUV NV12。macOS 默认回调格式。支持系统: macOS。
     */
    /**
     * {en}
     * @brief YUV NV12 format. The default format for macOS. Supported system: macOS.
     */
    kMixedStreamClientMixVideoFormatNV12 = 3,
};
/** 
 * @type keytype
 * @brief region 中流的类型属性
 */
enum MixedStreamVideoType {
    /** 
     * @brief 主流。包括：<br>
     *        + 由摄像头/麦克风通过内部采集机制，采集到的流<br>
     *        + 通过自定义采集，采集到的流。
     */
    kMixedStreamVideoTypeMain = 0,
    /** 
     * @brief 屏幕流。
     */
    kMixedStreamVideoTypeScreen = 1,
};


/** 
 *  @type keytype
 *  @brief 音频合流配置参数(新)。值不合法或未设置时，自动使用默认值。
 */
typedef struct MixedStreamAudioConfig {
    /** 
     * @brief 音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。
     */
    int32_t sample_rate = 48000;
    /** 
     * @brief 音频声道数。可取 1（单声道）、2（双声道），默认值为 2。
     */
    int32_t channels = 2;
    /** 
     * @brief 音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。
     */
    int32_t bitrate = 64;
    /** 
     * @brief AAC 编码规格，参看 MixedStreamAudioCodecProfile{@link #MixedStreamAudioCodecProfile}。默认值为 `0`。
     */
    MixedStreamAudioProfile audio_profile = MixedStreamAudioProfile::kMixedStreamAudioProfileLC;
    /** 
     * @brief 音频编码格式，参看 MixedStreamAudioCodecType{@link #MixedStreamAudioCodecType}。默认值为 `0`。
     */
    MixedStreamAudioCodecType audio_codec = MixedStreamAudioCodecType::kMixedStreamAudioCodecTypeAAC;
} MixedStreamAudioConfig;

/** 
 * @type keytype
 * @brief 视频合流配置参数(新)。值不合法或未设置时，自动使用默认值。
 */
typedef struct MixedStreamVideoConfig {
    /** 
     * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。
     *        设置值为非偶数时，自动向上取偶数。
     */
    int32_t width = 360;
    /** 
     * @brief 合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。
     *        设置值为非偶数时，自动向上取偶数。
     */
    int32_t height = 640;
    /** 
     * @brief 合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。
     */
    int32_t fps = 15;
    /** 
     * @brief 视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。
     *        本参数不支持过程中更新。
     */
    int32_t gop = 2;
    /** 
     * @brief 合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。
     */
    int32_t bitrate = 500;
    /** 
     * @brief 视频编码格式，参看 MixedStreamVideoCodecType{@link #MixedStreamVideoCodecType}。默认值为 `0`。
     *        本参数不支持过程中更新。
     */
    MixedStreamVideoCodecType video_codec = MixedStreamVideoCodecType::kMixedStreamVideoCodecTypeH264;
    /** 
      * @brief 是否在合流中开启B帧，仅服务端合流支持：  <br>
      *        + true: 是  <br>
      *        + false: 否
      */
     bool enable_Bframe = false;
} MixedStreamVideoConfig;

/** 
 * @type keytype
 * @brief 客户端合流参数(新)。
 */
typedef struct MixedStreamClientMixConfig {
    /** 
     * @brief 客户端合流是否使用混音，默认为 true。
     */
    bool use_audio_mixer = true;
    /** 
     * @brief 客户端合流回调视频格式，参看 MixedStreamClientMixVideoFormat{@link #MixedStreamClientMixVideoFormat}。
     */
    MixedStreamClientMixVideoFormat video_format;
} MixedStreamClientMixConfig;

/** 
 * @type keytype
 * @brief 合流转推直播同步参数(新)。
 */
typedef struct MixedStreamSyncControlConfig {
    /** 
     * @brief 是否转推同步，默认为 false。
     */
    bool enable_sync = false;
    /** 
     * @brief 转推同步基准用户 ID，即以该用户的流同步时间戳为准。默认为空。
     */
    const char* base_user_id = nullptr;
    /** 
     * @brief 缓存队列的长度，单位为毫秒。默认值为 0。
     */
    int32_t max_cache_time_ms = 0;
    /** 
     * @brief 视频是否需要在 RTC 进行合流。
     */
    bool video_need_sdk_mix = true;
    /** 
     * @brief 是否只开启时间戳发送而不做对齐和数据回调。
     */
    bool is_only_send_pts = false;
} MixedStreamSyncControlConfig;

/** 
 * @type keytype
 * @brief 图片合流相关参数(新)。
 */
typedef struct MixedStreamLayoutRegionImageWaterMarkConfig {
    /** 
     * @brief 原始图片的宽度，单位为 px。
     */
    int image_width = 0;
    /** 
     * @brief 原始图片的高度，单位为 px。
     */
    int image_height = 0;
} MixedStreamLayoutRegionImageWaterMarkConfig;

/** 
 * @type keytype
 * @brief 推流 CDN 的空间音频参数(新)。
 */
typedef struct MixedStreamSpatialAudioConfig {
    /** 
     * @brief 是否开启推流 CDN 时的空间音频效果。
     * @notes 当你启用此效果时，你需要设定推流中各个 MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} 的 `spatial_position` 值，实现空间音频效果。
     */
    bool enable_spatial_render;
    /** 
     * @brief 听众的空间位置。参看 Position{@link #Position}。<br>
     *        听众指收听来自 CDN 的音频流的用户。
     */
    Position audience_spatial_position;
    /** 
     * @brief 听众的空间朝向。参看 HumanOrientation{@link #HumanOrientation}。<br>
     *        听众指收听来自 CDN 的音频流的用户。
     */
    HumanOrientation audience_spatial_orientation;
} MixedStreamSpatialAudioConfig;

/** 
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息(新)。
 *        开启合流功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 */
typedef struct MixedStreamLayoutRegionConfig {
    /** 
     * @brief 合流用户的 ID。必填。
     */
    const char* region_id = nullptr;
   /** 
     * @brief 图片或视频流所在房间的房间 ID。必填。<br>
     *        如果此图片或视频流是通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
     */
    const char* room_id = nullptr;
    /** 
     * @brief 视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
     */
    float location_x = 0.0f;
    /** 
     * @brief 视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
     */
    float location_y = 0.0f;
    /** 
     * @brief 视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
     */
    float width_proportion = 1.0f;
    /** 
     * @brief 视频流对应区域高度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
     */
    float height_proportion = 1.0f;
    /** 
     * @brief 透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。
     */
    float alpha = 1.0f;
    /** 
     * @brief 圆角半径相对画布宽度的比例。默认值为 `0.0`。
     * @notes 做范围判定时，首先根据画布的宽高，将 `width`，`height`，和 `corner_radius` 分别转换为像素值：`width_px`，`height_px`，和 `corner_radius_px`。然后判定是否满足 `corner_radius_px < min(width_px/2, height_px/2)`：若满足，则设置成功；若不满足，则将 `corner_radius_px` 设定为 `min(width_px/2, height_px/2)`，然后将 `corner_radius` 设定为 `corner_radius_px` 相对画布宽度的比例值。
     */
    float corner_radius = 0;

    /** 
     * @brief 用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。
     */
    int32_t z_order = 0;
    /** 
     * @brief 是否为本地用户：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    bool is_local_user = false;
    /** 
     * @brief 是否为屏幕流：  <br>
     */
    MixedStreamVideoType stream_type = MixedStreamVideoType::kMixedStreamVideoTypeMain;
    /** 
     * @brief 合流内容控制。默认值为 `kMediaTypeAudioAndVideo`，参看 MixedStreamMediaType{@link #MixedStreamMediaType}。
     */
    MixedStreamMediaType media_type = MixedStreamMediaType::kMixedStreamMediaTypeAudioAndVideo;
    /** 
     * @brief 图片或视频流的缩放模式，参看 MixedStreamRenderMode{@link #MixedStreamRenderMode}。默认值为 1。
     */
    MixedStreamRenderMode render_mode = MixedStreamRenderMode::kMixedStreamRenderModeHidden;
    /** 
     * @type keytype
     * @brief 合流布局区域类型，参看 MixedStreamLayoutRegionType{@link #MixedStreamLayoutRegionType}。
     */
    MixedStreamLayoutRegionType region_content_type = MixedStreamLayoutRegionType::  kMixedStreamLayoutRegionTypeVideoStream;
    /** 
     * @type keytype
     * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
     */
    uint8_t* image_water_mark = nullptr;
    /** 
     * @type keytype
     * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 MixedStreamLayoutRegionImageWaterMarkConfig{@link #MixedStreamLayoutRegionImageWaterMarkConfig}。
     */
    MixedStreamLayoutRegionImageWaterMarkConfig image_water_mark_param;
    /** 
     * @type keytype
     * @brief 空间位置。参看 Position{@link #Position}。
     */
    Position spatial_position;
    
    bool apply_spatial_audio = true;
    
} MixedStreamLayoutRegionConfig;

/** 
 * @deprecated since 3.52, use MixedStreamType instead.
 * @type keytype
 * @brief 合流类型
 */
enum StreamMixingType {
    /** 
     * @brief 服务端合流
     */
    kStreamMixingTypeByServer = 0,
    /** 
     * @brief 端云一体合流
     */
    kStreamMixingTypeByClient = 1,
};


/** 
 * @deprecated since 3.52, use MixedStreamAudioProfile instead.
 * @type keytype
 * @brief AAC 编码规格。
 */
enum TranscoderAudioCodecProfile {
    /** 
     * @brief AAC-LC 规格，默认值。
     */
    kByteAACProfileLC = 0,
    /** 
     * @brief HE-AAC v1 规格。
     */
    kByteAACProfileHEv1 = 1,
    /** 
     * @brief HE-AAC v2 规格。
     */
    kByteAACProfileHEv2 = 2,
};

/** 
 * @deprecated since 3.52, use MixedStreamAudioCodecType instead.
 * @type keytype
 * @brief 音频编码格式。
 */
enum TranscoderAudioCodecType {
    /** 
     * @brief AAC 格式。
     */
    kTranscodeAudioCodecAAC = 0,
};

/** 
 * @deprecated since 3.52, use MixedStreamVideoCodecType instead.
 * @type keytype
 * @brief 视频编码格式。
 */
enum TranscoderVideoCodecType {
    /** 
     * @brief H.264 格式，默认值。
     */
    kTranscodeVideoCodecH264 = 0,
    /** 
     * @brief ByteVC1 格式。
     */
    kTranscodeVideoCodecH265 = 1,
};

/** 
 * @deprecated since 3.52, use MixedStreamRenderMode instead.
 * @type keytype
 * @brief 图片或视频流的缩放模式。
 */
enum TranscoderRenderMode {
    /** 
     * @deprecated since 3.45 and will be deleted in 3.51.
     */
    kRenderUnknown = 0,
    /** 
     * @brief 视窗填满优先，默认值。
     *        视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    kRenderHidden = 1,
    /** 
     * @brief 视频帧内容全部显示优先。
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。
     */
    kRenderFit = 2,
    /** 
     * @brief 视频帧自适应画布。
     *        视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
    kRenderAdaptive = 3,
};

/** 
 * @deprecated since 3.52, use MixedStreamLayoutRegionType instead.
 * @type keytype
 * @brief 合流布局区域类型
 */
enum TranscoderLayoutRegionType {
    /** 
     * @brief 合流布局区域类型为视频。
     */
    kLayoutRegionTypeVideoStream = 0,
    /** 
     * @brief 合流布局区域类型为图片。
     */
    kLayoutRegionTypeImage = 1,
};

/** 
 * @deprecated since 3.52, use MixedStreamLayoutRegionImageWaterMarkConfig instead.
 * @type keytype
 * @brief 图片合流相关参数
 */
typedef struct TranscoderLayoutRegionDataParam {
    /** 
     * @brief 原始图片的宽度，单位为 px。
     */
    int image_width = 0;
    /** 
     * @brief 原始图片的高度，单位为 px。
     */
    int image_height = 0;
}TranscoderLayoutRegionDataParam;

/** 
 * @deprecated since 3.52, use MixedStreamClientMixVideoFormat instead.
 * @type keytype
 * @brief 客户端合流回调视频格式。设置为系统不支持的格式时，自动回调系统默认格式。
 */
enum TranscoderClientMixVideoFormat {
    /** 
     * @brief YUV I420。Android、Windows 默认回调格式。支持系统：Android、Windows。
     */
    kClientMixVideoFormatI420 = 0,
    /** 
     * @brief OpenGL GL_TEXTURE_2D 格式纹理。支持系统：安卓。
     */
    kClientMixVideoFormatTexture2D = 1,
    /** 
     * @brief CVPixelBuffer BGRA。iOS 默认回调格式。支持系统: iOS。
     */
    kClientMixVideoFormatCVPixelBufferBGRA = 2,
    /** 
     * @brief YUV NV12。macOS 默认回调格式。支持系统: macOS。
     */
    kClientMixVideoFormatNV12 = 3,
};
/** 
 * @type keytype
 * @brief 数据帧类型
 */
enum DataFrameType {
    /** 
     * @brief SEI 视频帧
     */
    kDataFrameTypeSei = 0,
};

/**
 * @hidden for internal use only
 */
typedef size_t status_t;
/**
 * @hidden for internal use only
 */
class IVideoFrame;
/**
 * @hidden for internal use only
 */
class IAudioFrame;

/** 
 * @type keytype
 * @brief 数据帧
 */
typedef struct IDataFrame {
    /** 
     * @brief 数据帧类型，参看 DataFrameType{@link #DataFrameType}
     */
    DataFrameType frame_type = kDataFrameTypeSei;
    /** 
     * @brief 数据帧数据
     */
    uint8_t* u8_data = nullptr;
    /** 
     * @brief 数据帧数据大小
     */
    uint32_t u32_data_size = 0;
    /** 
     * @brief 数据帧时间戳，单位：微秒
     */
    uint64_t u64_ts_us = 0;
} IDataFrame;

/** 
 * @deprecated since 3.52, use MixedStreamLayoutRegionConfig instead.
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息。
 *        开启转推直播功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 */
typedef struct TranscoderLayoutRegion {
    /** 
     * @brief 合流用户的 ID。必填。
     */
    const char* region_id = nullptr;
   /** 
     * @brief 图片或视频流所在房间的房间 ID。必填。<br>
     *        如果此图片或视频流是通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
     */
    const char* room_id = nullptr;
    /** 
     * @brief 视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
     */
    float x = 0.0f;
    /** 
     * @brief 视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
     */
    float y = 0.0f;
    /** 
     * @brief 视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
     */
    float width = 1.0f;
    /** 
     * @brief 视频流对应区域高度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
     */
    float height = 1.0f;
    /** 
     * @brief （仅服务端合流支持设置）透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。
     */
    float alpha = 1.0f;
    /** 
     * @brief （仅服务端合流支持设置）圆角半径相对画布宽度的比例。默认值为 `0.0`。
     * @notes 做范围判定时，首先根据画布的宽高，将 `width`，`height`，和 `corner_radius` 分别转换为像素值：`width_px`，`height_px`，和 `corner_radius_px`。然后判定是否满足 `corner_radius_px < min(width_px/2, height_px/2)`：若满足，则设置成功；若不满足，则将 `corner_radius_px` 设定为 `min(width_px/2, height_px/2)`，然后将 `corner_radius` 设定为 `corner_radius_px` 相对画布宽度的比例值。
     */
    float corner_radius = 0;

    /** 
     * @brief 用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。
     */
    int32_t i32_z_order = 0;
    /** 
     * @brief 是否为本地用户：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    bool local_user = false;
    /** 
     * @brief （仅服务端合流支持合屏幕流）是否为屏幕流：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    bool screen_stream = false;
    /** 
     * @brief （仅服务端合流支持设置）合流内容控制。默认值为 `kHasAudioAndVideo`，参看 TranscoderContentControlType{@link #TranscoderContentControlType}。
     */
    TranscoderContentControlType content_control = kHasAudioAndVideo;
    /** 
     * @brief 图片或视频流的缩放模式，参看 TranscoderRenderMode{@link #TranscoderRenderMode}。默认值为 1。
     */
    TranscoderRenderMode render_mode = kRenderHidden;
    /** 
     * @type keytype
     * @brief 合流布局区域类型，参看 TranscoderLayoutRegionType{@link #TranscoderLayoutRegionType}。
     */
    TranscoderLayoutRegionType type = kLayoutRegionTypeVideoStream;
    /** 
     * @type keytype
     * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
     */
    uint8_t* data = nullptr;
    /** 
     * @type keytype
     * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 TranscoderLayoutRegionDataParam{@link #TranscoderLayoutRegionDataParam}。
     */
    TranscoderLayoutRegionDataParam data_param;
    /** 
     * @type keytype
     * @brief 空间位置。参看 Position{@link #Position}。
     */
    Position spatial_position;

    bool apply_spatial_audio = true;

} TranscoderLayoutRegion;

/** 
 * @deprecated since 3.52, use MixedStreamAudioConfig instead.
 *  @type keytype
 *  @brief 音频转码配置参数。值不合法或未设置时，自动使用默认值。
 */
typedef struct TranscoderAudioParam {
    /** 
     * @brief 音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。
     */
    int32_t i32_sample_rate = 48000;
    /** 
     * @brief 音频声道数。可取 1（单声道）、2（双声道），默认值为 2。
     */
    int32_t i32_channel_num = 2;
    /** 
     * @brief 音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。
     */
    int32_t i32_bitrate_kbps = 64;
    /** 
     * @brief AAC 编码规格，参看 TranscoderAudioCodecProfile{@link #TranscoderAudioCodecProfile}。默认值为 `0`。
     */
    TranscoderAudioCodecProfile audio_codec_profile = kByteAACProfileLC;
    /** 
     * @brief 音频编码格式，参看 TranscoderAudioCodecType{@link #TranscoderAudioCodecType}。默认值为 `0`。
     */
    TranscoderAudioCodecType audio_codec_type = kTranscodeAudioCodecAAC;
} TranscoderAudioParam;

/** 
 * @deprecated since 3.52, use MixedStreamVideoConfig instead.
 * @type keytype
 * @brief 视频转码配置参数。值不合法或未设置时，自动使用默认值。
 */
typedef struct TranscoderVideoParam {
    /** 
     * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。
     *        设置值为非偶数时，自动向上取偶数。
     */
    int32_t i32_width = 360;
    /** 
     * @brief 合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。
     *        设置值为非偶数时，自动向上取偶数。
     */
    int32_t i32_height = 640;
    /** 
     * @brief 合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。
     */
    int32_t i32_fps = 15;
    /** 
     * @brief 视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。
     *        本参数不支持过程中更新。
     */
    int32_t i32_gop = 2;
    /** 
     * @brief 合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。
     */
    int32_t i32_bitrate_kbps = 500;
    /** 
     * @brief 视频编码格式，参看 TranscoderVideoCodecType{@link #TranscoderVideoCodecType}。默认值为 `0`。
     *        本参数不支持过程中更新。
     */
    TranscoderVideoCodecType video_codec_type = kTranscodeVideoCodecH264;
    /** 
      * @brief 是否在合流中开启B帧，仅服务端合流支持：  <br>
      *        + true: 是  <br>
      *        + false: 否
      */
     bool bFrame = false;
} TranscoderVideoParam;
/** 
 * @deprecated since 3.52, use MixedStreamSyncControlConfig instead.
 * @hidden internal use only
 * @valid since 3.50
 * @type keytype
 * @brief 转推直播单通同步参数。
 */
typedef struct TranscoderSyncControlParam {
    /** 
     * @brief 是否在转推直播时，启用单通模式。默认为 false，不启用。
     *        启用单通模式时，RTC SDK 会对指定的多个用户的媒体流进行同步处理，再合流后推送到 CDN，但基准流所属用户不会播放来自其他用户的媒体流。你需要设定以下参数。
     *        非单通模式时，RTC SDK 不会对媒体流进行同步处理，只是简单合流后推送到 CDN。以下参数设定无效。
     */
    bool sync_stream = false;
    /** 
     * @brief 在进行同步处理时，基准流所属用户的 ID。默认为空。
     */
    const char* sync_base_user = nullptr;
    /** 
     * @brief 在进行同步处理时，缓存音视频流的最大长度。单位为毫秒。默认值为 0。
     * @notes 参与转推直播的这些媒体流延迟越高，应该将此值设置的越大。但此值越大，因缓存媒体流造成的内存占用也会更大。推荐值为 `2000`。
     */
    int32_t sync_queue_length_ms = 0;
    /** 
     * @brief 是否通过 RTC SDK 进行转推直播。默认为 True。
     *        如果选择 `False`，你会通过 onCacheSyncVideoFrames{@link #ITranscoderObserver#onCacheSyncVideoFrames} 收到同步的帧，你可以使用此视频帧，自行实现合流转推。
     */
    bool sync_client_video_need_mix = true;
    /** 
     * @brief 是否只开启时间戳发送而不做对齐和媒体数据回调。默认为 False。
     *        在单通合唱双人场景下，主唱应设置为 False，副唱应设置为 True。
     *        在单通合唱多人场景下，主唱和所有副唱都应设置为 False。
     */
    bool sync_only_send_pts = false;
} TranscoderSyncControlParam;
/** 
 * @deprecated since 3.52, use MixedStreamClientMixConfig instead.
 * @type keytype
 * @brief 客户端合流参数。
 */
typedef struct TranscoderClientMixParam {
    /** 
     * @brief 是否使用原始视频帧。默认为 False。
     */
    bool client_mix_use_original_frame = false;
    /** 
     * @brief 客户端合流是否使用音频混音，默认为 true。
     */
    bool client_mix_use_audio_mixer = true;
    /** 
     * @brief 客户端合流回调视频格式，参看 TranscoderClientMixVideoFormat{@link #TranscoderClientMixVideoFormat}。
     */
    TranscoderClientMixVideoFormat client_mix_video_format_;
} TranscoderClientMixParam;

/** 
 * @deprecated since 3.52, use MixedStreamSpatialAudioConfig instead.
 * @type keytype
 * @brief 推流 CDN 的空间音频参数。
 */
typedef struct TranscoderSpatialConfig {
    /** 
     * @brief 是否开启推流 CDN 时的空间音频效果。
     * @notes 当你启用此效果时，你需要设定推流中各个 TranscoderLayoutRegion{@link #TranscoderLayoutRegion} 的 `spatial_position` 值，实现空间音频效果。
     */
    bool enable_spatial_render;
    /** 
     * @brief 听众的空间位置。参看 Position{@link #Position}。<br>
     *        听众指收听来自 CDN 的音频流的用户。
     */
    Position audience_spatial_position;
    /** 
     * @brief 听众的空间朝向。参看 HumanOrientation{@link #HumanOrientation}。<br>
     *        听众指收听来自 CDN 的音频流的用户。
     */
    HumanOrientation audience_spatial_orientation;
} TranscoderSpatialConfig;

/** 
 * @deprecated since 3.52, use IMixedStreamParam instead.
 * @type keytype
 * @brief 转推直播配置参数。
 */
class ITranscoderParam : public ITranscoderParamBase {
public:

    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流类型。
     * @return 合流类型，参看 StreamMixingType{@link #StreamMixingType}
     * @notes 本参数不支持过程中更新。
     */
    virtual StreamMixingType expectedMixingType() = 0;
    /** 
     * @type api
     * @brief 获取推流用户 ID。
     * @return 推流用户 ID。
     */
    virtual const char* userID() = 0;
    /** 
     * @type api
     * @brief 获取推流 CDN 地址。
     * @return 推流地址。
     */
    virtual const char* uri() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取 SEI 信息。
     * @return SEI 信息。
     */
    virtual const char* appData() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流音频参数。
     * @return 合流音频参数内容，参看 TranscoderAudioParam{@link #TranscoderAudioParam}。
     */
    virtual TranscoderAudioParam audioParam() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流视频转码参数。
     * @return 合流视频转码参数内容，参看 TranscoderVideoParam{@link #TranscoderVideoParam}。
     */
    virtual TranscoderVideoParam videoParam() = 0;
    /** 
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 获取转推 CDN 时的空间音频参数。
     * @return 参看 TranscoderSpatialConfig{@link #TranscoderSpatialConfig}。
     */
    virtual TranscoderSpatialConfig spatialConfig() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流视窗布局信息。
     * @param [in] index 视窗对应下标。
     * @return 合流视窗布局信息，参看 TranscoderLayoutRegion{@link #TranscoderLayoutRegion}。
     */
    virtual TranscoderLayoutRegion layoutRegionByIndex(int32_t index) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 获取动态扩展自定义参数
     * @return 动态扩展自定义参数
     */
    virtual const char* advancedConfig() = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 获取业务透传鉴权信息
     * @return 业务透传鉴权信息
     */
    virtual const char* authInfo() = 0;
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @type api
     * @brief 获取客户端合流信息。
     * @return 客户端合流信息，参看 TranscoderClientMixParam{@link #TranscoderClientMixParam}。
     */
    virtual TranscoderClientMixParam clientMixParam()  = 0;
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @type api
     * @brief 获取转推直播单通同步参数。
     * @return 参看 TranscoderSyncControlParam{@link #TranscoderSyncControlParam}。
     */
    virtual TranscoderSyncControlParam syncControlparam() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置合流类型。
     * @param [in] expected_mix_type 合流类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    virtual void setExpectedMixingType(StreamMixingType expected_mix_type) = 0;
    /** 
     * @type api
     * @brief 设置推流用户 ID。`room_id` 和 `user_id` 长度相加不得超过 126 字节。
     *        本参数不支持过程中更新。
     * @param [in] user_id 推流用户 ID。
     */
    virtual void setUserID(const char* user_id) = 0;
    /** 
     * @type api
     * @brief 设置推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。
     *        本参数不支持过程中更新。
     * @param [in] uri 推流地址。
     */
    virtual void setUri(const char* uri) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置音频参数。
     *        本参数不支持过程中更新。
     * @param [in] TranscoderAudioParam 音频参数，参看 TranscoderAudioParam{@link #TranscoderAudioParam}。
     */
    virtual void setAudioParam(const TranscoderAudioParam&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置视频参数。
     * @param [in] TranscoderVideoParam 视频参数，参看 TranscoderVideoParam{@link #TranscoderVideoParam}
     */
    virtual void setVideoParam(const TranscoderVideoParam&) = 0;
    /** 
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 设定转推 CDN 时的空间音频效果。
     * @param [in] TranscoderSpatialConfig 参看 TranscoderSpatialConfig{@link #TranscoderSpatialConfig}。
     */
    virtual void setSpatialConfig(const TranscoderSpatialConfig&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置视频流合流整体布局信息。
     * @param [in] regions[] 用户布局信息列表。为 TranscoderLayoutRegion{@link #TranscoderLayoutRegion} 数据类型的数组。每一个该类型对象为一路单独的视频流的布局信息。
     *                       值不合法或未设置时，自动使用默认值。
     * @param [in] regions_size 合流视窗数量。
     * @param [in] bg_color 合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。
     *                      值不合法或未设置时，自动使用默认值。
     * @param [in] app_data 透传的 App 数据，长度不超过 4 KB。
     */
    virtual void setLayoutParam(
            TranscoderLayoutRegion regions[], int32_t regions_size, const char* bg_color, const char* app_data) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置动态扩展自定义参数
     * @param [in] advancedConfig 动态扩展自定义参数
     */
    virtual void setAdvancedConfig(const char* advancedConfig) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置业务透传鉴权信息
     * @param [in] authInfo 业务透传鉴权信息
     */
    virtual void setAuthInfo(const char* authInfo) = 0;
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @type api
     * @brief 设置客户端合流信息。
     * @param [in] param 参看 TranscoderClientMixParam{@link #TranscoderClientMixParam}。
     * @return 参看 TranscoderClientMixParam{@link #TranscoderClientMixParam}。
     */
    virtual void setClientMixParam(TranscoderClientMixParam param) = 0;
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @type api
     * @brief 设置转推直播单通同步参数。
     * @param [in] param 参看 TranscoderSyncControlParam{@link #TranscoderSyncControlParam}。
     * @return 参看 TranscoderSyncControlParam{@link #TranscoderSyncControlParam}。
     */
    virtual void setSyncControlparam(TranscoderSyncControlParam param) = 0;

    /** 
     * @type api
     * @region 转推直播
     * @brief 将输入的 json 格式的字符串转成 ITranscoderParam 结构体
     * @param [in] json_str json 格式字符串
     * @return 转换后的 ITranscoderParam 结构体
     */
    virtual ITranscoderParam* inflatten(const char* json_str) = 0;

    /** 
     * @type api
     * @region 转推直播
     * @brief 获取默认的合流转推参数
     * @return 生成的 ITranscoderParam 结构体
     */
    virtual ITranscoderParam* defaultTranscoding() = 0;
    /**
     * @hidden constructor/destructor
     */
    virtual ~ITranscoderParam() = default;
};

/** 
 * @type keytype
 * @brief 转推直播配置参数(新)。
 */
class IMixedStreamConfig : public ITranscoderParamBase {
public:

    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流类型。
     * @return 合流类型，参看 MixedStreamType{@link #MixedStreamType}
     */
    virtual MixedStreamType getExpectedMixingType() = 0;
    /** 
     * @type api
     * @brief 获取推流用户 ID。
     * @return 推流用户 ID。
     */
    virtual const char* getUserID() = 0;
    /** 
     * @type api
     * @brief 获取推流 CDN 地址。
     * @return 推流地址。
     */
    virtual const char* getPushURL() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取用户配置的额外信息。
     * @return UserConfigExtraInfo 信息。
     */
    virtual const char* getUserConfigExtraInfo() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流音频参数。
     * @return 合流音频参数内容，参看 MixedStreamAudioConfig{@link #MixedStreamAudioConfig}。
     */
    virtual MixedStreamAudioConfig getAudioConfig() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流视频转码参数。
     * @return 合流视频转码参数内容，参看 MixedStreamVideoConfig{@link #MixedStreamVideoConfig}。
     */
    virtual MixedStreamVideoConfig getVideoConfig() = 0;
    /** 
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 获取转推 CDN 时的空间音频参数。
     * @return 参看 MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig}。
     */
    virtual MixedStreamSpatialAudioConfig getSpatialAudioConfig() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流视窗布局信息。
     * @param [in] index 视窗对应下标。
     * @return 合流视窗布局信息，参看 MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig}。
     */
    virtual MixedStreamLayoutRegionConfig getLayoutByIndex(int32_t index) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 获取动态扩展自定义参数
     * @return 动态扩展自定义参数
     */
    virtual const char* getAdvancedConfig() = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 获取业务透传鉴权信息
     * @return 业务透传鉴权信息
     */
    virtual const char* getAuthInfo() = 0;
    /** 
     * @type api
     * @brief 获取客户端合流信息。
     * @return 客户端合流信息，参看 MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig}。
     */
    virtual MixedStreamClientMixConfig getClientMixConfig()  = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @brief 获取转推直播同步参数。
     * @return 转推直播同步参数，参看 MixedStreamSyncControlConfig{@link #MixedStreamSyncControlConfig}。
     */
    virtual MixedStreamSyncControlConfig getSyncControlConfig() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置合流类型。
     * @param [in] expected_mix_type 合流类型，参看 MixedStreamType{@link #MixedStreamType}
     */
    virtual void setExpectedMixingType(MixedStreamType expected_mix_type) = 0;
    /** 
     * @type api
     * @brief 设置推流用户 ID。`room_id` 和 `user_id` 长度相加不得超过 126 字节。
     *        本参数不支持过程中更新。
     * @param [in] user_id 推流用户 ID。
     */
    virtual void setUserID(const char* user_id) = 0;
    /** 
     * @type api
     * @brief 设置推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。
     *        本参数不支持过程中更新。
     * @param [in] url 推流地址。
     */
    virtual void setPushURL(const char* push_url) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置音频参数。
     *        本参数不支持过程中更新。
     * @param [in] MixedStreamAudioConfig 音频参数，参看 MixedStreamAudioConfig{@link #MixedStreamAudioConfig}。
     */
    virtual void setAudioConfig(const MixedStreamAudioConfig&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置视频参数。
     * @param [in] MixedStreamVideoConfig 视频参数，参看 MixedStreamVideoConfig{@link #MixedStreamVideoConfig}
     */
    virtual void setVideoConfig(const MixedStreamVideoConfig&) = 0;
    /** 
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 设定转推 CDN 时的空间音频效果。
     * @param [in] TranscoderSpatialConfig 参看 MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig}。
     */
    virtual void setSpatialAudioConfig(const MixedStreamSpatialAudioConfig&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置视频流合流整体布局信息。
     * @param [in] regions[] 用户布局信息列表。为 MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} 数据类型的数组。每一个该类型对象为一路单独的视频流的布局信息。
     *                       值不合法或未设置时，自动使用默认值。
     * @param [in] regions_size 合流视窗数量。
     * @param [in] background_color 合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。
     *                      值不合法或未设置时，自动使用默认值。
     * @param [in] user_extra_info 透传的 App 数据。
     */
    virtual void setLayoutConfig(MixedStreamLayoutRegionConfig regions[],
                                int32_t regions_size,
                                const char* background_color,
                                const char* user_extra_info) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置动态扩展自定义参数
     * @param [in] advancedConfig 动态扩展自定义参数
     */
    virtual void setAdvancedConfig(const char* advancedConfig) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置业务透传鉴权信息
     * @param [in] authInfo 业务透传鉴权信息
     */
    virtual void setAuthInfo(const char* authInfo) = 0;
    /** 
     * @type api
     * @brief 设置客户端合流信息
     * @param [in] param 客户端合流信息，参看 MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig}。
     */
    virtual void setClientMixConfig(MixedStreamClientMixConfig&) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @brief 设置转推直播同步参数。
     * @param [in] param 转推直播同步参数，参看 MixedStreamSyncControlConfig{@link #MixedStreamSyncControlConfig}。
     */
    virtual void setSyncControlConfig(MixedStreamSyncControlConfig&) = 0;

    /** 
     * @type api
     * @region 转推直播
     * @brief 获取默认的合流转推参数
     * @return 生成的 IMixedStreamConfig 结构体
     */
    virtual IMixedStreamConfig* defaultMixedStreamConfig() = 0;
    /**
     * @hidden convertToTranscoderParam
     */
    virtual ITranscoderParam* convertToTranscoderParam() = 0;
    /**
     * @hidden constructor/destructor
     */
    virtual ~IMixedStreamConfig() = default;
};

/** 
 * @type keytype
 * @brief 单流转推直播配置参数。
 */
typedef struct PushSingleStreamParam {
    /** 
     * @brief 媒体流所在的房间 ID
     */
    const char* room_id;
    /** 
     * @brief 媒体流所属的用户 ID
     */
    const char* user_id;
    /** 
     * @brief 推流地址
     */
    const char* uri;
    /** 
     * @brief 媒体流是否为屏幕流。
     */
    const bool is_screen_stream;
}PushSingleStreamParam;
}  // namespace bytertc
