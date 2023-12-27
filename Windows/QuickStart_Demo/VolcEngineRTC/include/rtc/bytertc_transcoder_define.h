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
    kStreamMixingEventBase = 0,
    /** 
     * @brief 请求发起转推直播任务
     */
    kStreamMixingEventStart = 1,
    /** 
     * @brief 发起转推直播任务成功
     */
    kStreamMixingEventStartSuccess = 2,
    /** 
     * @brief 发起转推直播任务失败
     */
    kStreamMixingEventStartFailed = 3,
    /** 
     * @brief 请求更新转推直播任务配置
     */
    kStreamMixingEventUpdate = 4,
    /** 
     * @brief 成功更新转推直播任务配置
     */
    kStreamMixingEventUpdateSuccess = 5,
    /** 
     * @brief 更新转推直播任务配置失败
     */
    kStreamMixingEventUpdateFailed = 6,
    /** 
     * @brief 请求结束转推直播任务
     */
    kStreamMixingEventStop = 7,
    /** 
     * @brief 结束转推直播任务成功
     */
    kStreamMixingEventStopSuccess = 8,
    /** 
     * @brief 结束转推直播任务失败
     */
    kStreamMixingEventStopFailed = 9,
    /** 
     * @brief 更新转推直播任务配置的请求超时
     */
    kStreamMixingEventChangeMixType = 10,
    /** 
     * @brief 得到客户端合流音频首帧
     */
    kStreamMixingEventFirstAudioFrameByClientMix = 11,
    /** 
     * @brief 收到客户端合流视频首帧
     */
    kStreamMixingEventFirstVideoFrameByClientMix = 12,
    /** 
     * @brief 更新转推直播任务配置超时
     */
    kStreamMixingEventUpdateTimeout = 13,
    /** 
     * @brief 发起转推直播任务配置超时
     */
    kStreamMixingEventStartTimeout = 14,
    /** 
     * @brief 合流布局参数错误
     */
    kStreamMixingEventRequestParamError = 15,
    /** 
    * @brief 合流加图片
    */
    kStreamMixingEventMixImageEvent = 16,
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @brief 单通合唱事件
     */
    kStreamMixingEventMixSingleWayChorusEvent = 17,
};


/** 
 * @type errorcode
 * @brief 单流转推直播错误码
 */
enum SingleStreamPushEvent {
    /**
     * @hidden for internal use only
     */
    kSingleStreamPushEventBase = 0,
    /** 
    * @brief 开始推流。
    */
   kSingleStreamPushEventStart = 1,
    /** 
    * @brief 推流成功。
    */
   kSingleStreamPushEventSuccess = 2,
    /** 
    * @brief 推流失败。
    */
   kSingleStreamPushEventFailed = 3,
    /** 
     * @brief 停止推流。
     */
    kSingleStreamPushEventStop = 4,
    /** 
    * @brief 单流转推直播任务处理超时，请检查网络状态并重试。
    */
   kSingleStreamPushEventTimeout = 5,
    /** 
     * @brief 参数错误。
     */
    kSingleStreamPushEventParamError = 6,
};

/** 
 * @type errorcode
 * @brief 转推直播错误码
 */
enum StreamMixingErrorCode {
    /** 
     * @brief 推流成功。
     */
    kStreamMixingErrorCodeOK = 0,
    /** 
     * @brief 未定义的合流错误
     */
    kStreamMixingErrorCodeBase= 1090,
    /** 
     * @brief 客户端 SDK 检测到无效推流参数。
     */
    kStreamMixingErrorCodeInvalidParam = 1091,
    /** 
     * @brief 状态错误，需要在状态机正常状态下发起操作
     */
    kStreamMixingErrorCodeInvalidState = 1092,
    /** 
     * @brief 无效操作
     */
    kStreamMixingErrorCodeInvalidOperator = 1093,
    /** 
     * @brief 转推直播任务处理超时，请检查网络状态并重试
     */
    kStreamMixingErrorCodeTimeout = 1094,
    /** 
     * @brief 服务端检测到错误的推流参数
     */
    kStreamMixingErrorCodeInvalidParamByServer = 1095,
    /** 
     * @brief 对流的订阅超时
     */
    kStreamMixingErrorCodeSubTimeoutByServer = 1096,
    /** 
     * @brief 合流服务端内部错误。
     */
    kStreamMixingErrorCodeInvalidStateByServer = 1097,
    /** 
     * @brief 合流服务端推 CDN 失败。
     */
    kStreamMixingErrorCodeAuthenticationByCDN  = 1098,
    /** 
     * @brief 服务端接收信令超时，请检查网络状态并重试。
     */
    kStreamMixingErrorCodeTimeoutBySignaling = 1099,
    /** 
     * @brief 图片合流失败。
     */
    kStreamMixingErrorCodeMixImageFail = 1100,
    /** 
     * @brief 服务端未知错误。
     */
    kStreamMixingErrorCodeUnKnownByServer = 1101,
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @brief 缓存未同步。
     */
    kStreamMixingErrorCodeStreamSyncWorse = 1102,
    /** 
     * @hidden 只供内部使用
     * @brief 合流消息中的用户布局信息发生了变化。
     */
    kStreamMixingErrorCodeUpdateRegionChanged = 1103,
    /**
     * @hidden for internal use only
     */
    kStreamMixingErrorCodeMax = 1199,
};

/** 
 * @type keytype
 * @brief 合流类型。(新)
 */
enum MixedStreamType {
    /** 
     * @brief 服务端合流
     */
    kMixedStreamTypeByServer = 0,
    /** 
     * @brief 端云一体合流。SDK 智能决策在客户端或服务端完成合流。
     *        使用前，请联系技术支持同学开通，否则不生效。
     */
    kMixedStreamTypeByClient = 1,
};


/** 
 * @type keytype
 * @brief AAC 编码规格。(新)
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
 * @hidden
 * @brief notes missing
 */
enum MixedStreamSyncStrategy {
    /** 
     * @brief 不使用同步策略
     */
    kMixedStreamSyncStrategyNoSync = 0,
    /** 
     * @brief 使用音频精准同步策略
     */
    kMixedStreamSyncStrategyAudioPreciseSync = 1,
    /** 
     * @brief 使用单通模式同步策略
     */
    kMixedStreamSyncStrategySimplexModeSync = 2,
};

/** 
 * @type keytype
 * @brief 音频编码格式。(新)
 */
enum MixedStreamAudioCodecType {
    /** 
     * @brief AAC 格式。
     */
    kMixedStreamAudioCodecTypeAAC = 0,
};

/** 
 * @type keytype
 * @brief 服务端合流转推 SEI 内容。
 */
enum MixedStreamSEIContentMode {
    /** 
     * @brief 视频流中包含全部的 SEI 信息。默认设置。
     */
    kMixedStreamSEIContentModeDefault = 0,
    /** 
     * @brief 随非关键帧传输的 SEI 数据中仅包含音量信息。<br>
     *        当设置 `MixedStreamServerControlConfig.enable_volume_indication` 为 True 时，此参数设置生效。
     */
    kMixedStreamSEIContentModeEnableVolumeIndication = 1,
};

/** 
 * @type keytype
 * @brief 视频编码格式。(新)
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
 * @brief 图片或视频流的缩放模式。(新)
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
 * @brief 合流输出内容类型。(新)
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
 * @brief 合流布局区域类型。(新)
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
 * @brief 客户端合流回调视频格式。(新)<br>
 *        设置为系统不支持的格式时，自动回调系统默认格式。
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
 * @brief 服务端合流转推发起模式。
 */
enum MixedStreamPushMode {
    /** 
     * @brief 无用户发布媒体流时，发起合流任务无效。默认设置。<br>
     *        当有用户发布媒体流时，才能发起合流任务。
     */
    kMixedStreamPushModeOnStream = 0,
    /** 
     * @brief 无用户发布媒体流时，可以使用占位图发起合流任务。<br>
     *        占位图设置参看 alternate_image_url{@link #MixedStreamLayoutRegionConfig#alternate_image_url} 和 alternate_image_fill_mode{@link #MixedStreamLayoutRegionConfig#alternate_image_fill_mode}
     */
    kMixedStreamPushModeOnStartRequest = 1,
};
/** 
 * @type keytype
 * @brief 服务端合流占位图填充模式。
 */
enum MixedStreamAlternateImageFillMode {
    /** 
     * @brief 占位图跟随用户原始视频帧相同的比例缩放。默认设置。
     */
    /**
     * {en}
     * @brief The placeholder image is scaled with the same aspect ratio as the user's original video frame. Default setting.
     */
    kMixedStreamAlternateImageFillModeFit = 0,
    /** 
     * @brief 占位图不跟随用户原始视频帧相同的比例缩放，保持图片原有比例。
     */
    /**
     * {en}
     * @brief The placeholder image is not scaled with the same aspect ratio as the user's original video frame. It maintains the original aspect ratio.
     */
    kMixedStreamAlternateImageFillModeFill = 1,
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
 *  @brief 音频合流配置参数。(新)<br>
 *         值不合法或未设置时，自动使用默认值。
 */
typedef struct MixedStreamAudioConfig {
    /** 
     * @brief 音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。建议设置。
     */
    int32_t sample_rate = 48000;
    /** 
     * @brief 音频声道数。可取 1（单声道）、2（双声道），默认值为 2。建议设置。
     */
    int32_t channels = 2;
    /** 
     * @brief 音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。建议设置。
     */
    int32_t bitrate = 64;
    /** 
     * @brief AAC 编码规格，参看 MixedStreamAudioProfile{@link #MixedStreamAudioProfile}。默认值为 `0`。建议设置。
     */
    MixedStreamAudioProfile audio_profile = MixedStreamAudioProfile::kMixedStreamAudioProfileLC;
    /** 
     * @brief 音频编码格式，参看 MixedStreamAudioCodecType{@link #MixedStreamAudioCodecType}。默认值为 `0`。建议设置。
     */
    MixedStreamAudioCodecType audio_codec = MixedStreamAudioCodecType::kMixedStreamAudioCodecTypeAAC;
} MixedStreamAudioConfig;

#define MIXED_STREAM_VIDEO_DEFAULT_WIDTH 360
#define MIXED_STREAM_DEFAULT_VIDEO_HEIGHT 640
/** 
 * @type keytype
 * @brief 视频合流配置参数。(新)<br>
 *        值不合法或未设置时，自动使用默认值。
 */
typedef struct MixedStreamVideoConfig {
    /** 
     * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。建议设置。
     *        设置值为非偶数时，自动向上取偶数。
     */
    int32_t width = MIXED_STREAM_VIDEO_DEFAULT_WIDTH;
    /** 
     * @brief 合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。建议设置。
     *        设置值为非偶数时，自动向上取偶数。
     */
    int32_t height = MIXED_STREAM_DEFAULT_VIDEO_HEIGHT;
    /** 
     * @brief 合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。建议设置。
     */
    int32_t fps = 15;
    /** 
     * @brief 视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。建议设置。
     *        本参数不支持过程中更新。
     */
    int32_t gop = 2;
    /** 
     * @brief 合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。建议设置。
     */
    int32_t bitrate = 500;
    /** 
     * @brief 视频编码格式，参看 MixedStreamVideoCodecType{@link #MixedStreamVideoCodecType}。默认值为 `0`。建议设置。
     *        本参数不支持过程中更新。
     */
    MixedStreamVideoCodecType video_codec = MixedStreamVideoCodecType::kMixedStreamVideoCodecTypeH264;
    /** 
      * @brief 是否在合流中开启B帧，仅服务端合流支持：  <br>
      *        + true: 是  <br>
      *        + false: 否
      */
     bool enable_bframe = false;
} MixedStreamVideoConfig;

/** 
 * @type keytype
 * @brief 客户端合流参数。(新)
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
 * @hidden for internal use only
 * @type keytype
 * @brief 转推直播单通同步参数。(新)
 */
typedef struct MixedStreamSyncControlConfig {
    /** 
     * @brief 在进行同步处理时，缓存音视频流的最大长度。单位为毫秒。默认值为 2000。
     * @notes 参与转推直播的这些媒体流延迟越高，应该将此值设置的越大。但此值越大，因缓存媒体流造成的内存占用也会更大。推荐值为 `2000`。
     */
    int32_t max_cache_time_ms = 2000;
    /** 
     * @brief 是否在转推直播时，启用单通模式。默认为 false，不启用。
     *        启用单通模式时，RTC SDK 会对指定的多个用户的媒体流进行同步处理，再合流后推送到 CDN，但基准流所属用户不会播放来自其他用户的媒体流。你需要设定以下参数。
     *        非单通模式时，RTC SDK 不会对媒体流进行同步处理，只是简单合流后推送到 CDN。以下参数设定无效。
     */
    /** 
     * @brief 同步策略
     */
    MixedStreamSyncStrategy sync_strategy = MixedStreamSyncStrategy::kMixedStreamSyncStrategyNoSync;
    /** 
     * @brief 在进行同步处理时，基准流所属用户的 ID。默认为空。
     */
    const char* base_user_id = nullptr;
    /** 
     * @brief 是否通过 RTC SDK 进行转推直播。默认为 True。
     *        如果选择 `False`，你会通过 onCacheSyncVideoFrames{@link #ITranscoderObserver#onCacheSyncVideoFrames} 收到同步的帧，你可以使用此视频帧，自行实现合流转推。
     */
    bool video_need_sdk_mix = true;
} MixedStreamSyncControlConfig;

/** 
 * @type keytype
 * @brief 图片合流相关参数。(新)
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
 * @brief 推流 CDN 的空间音频参数。(新)
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
 * @brief 服务端合流控制参数
 */
typedef struct MixedStreamServerControlConfig {
    /** 
     * @valid since 3.56
     * @brief 是否开启单独发送声音提示 SEI 的功能：<br>
     *        + True：开启；
     *        + False：关闭。（默认值）
     *        开启后，你可以通过 `MixedStreamServerControlConfig.sei_content_mode` 控制 SEI 的内容是否只携带声音信息。
     */
    bool enable_volume_indication = false;
    /** 
     * @valid since 3.56
     * @brief 声音提示间隔，单位为秒，取值范围为 [0.3,+∞)，默认值为 2。<br>
     *        此值仅取整百毫秒。若传入两位及以上小数，则四舍五入取第一位小数的值。例如，若传入 0.36，则取 0.4。
     */
    float volume_indication_interval = 2.0f;
    /** 
     * @valid since 3.56
     * @brief 有效音量大小，取值范围为 [0, 255]，默认值为 0。<br>
     *        超出取值范围则自动调整为默认值，即 0。
     */
    int talk_volume = 0;
    /** 
     * @valid since 3.56
     * @brief 声音信息 SEI 是否包含音量值：
     *        + True：是；
     *        + False：否，默认值。
     */
    bool is_add_volume_value = false;
    /** 
     * @valid since 3.56
     * @brief 设置 SEI 内容。参看 MixedStreamSEIContentMode{@link #MixedStreamSEIContentMode}。
     */
    MixedStreamSEIContentMode sei_content_mode = kMixedStreamSEIContentModeDefault;
    /** 
     * @valid since 3.56
     * @brief SEI 信息的 payload type。<br>
     *        默认值为 `100`，只支持设置 `5` 和 `100`。<br>
     *        在转推直播的过程中，该参数不支持变更。
     */
    int sei_payload_type = 100;
    /** 
     * @valid since 3.56
     * @brief SEI 信息的 payload UUID。
     * @notes PayloadType 为 `5` 时，必须填写 PayloadUUID，否则会收到错误回调，错误码为1091。  <br>
     *         PayloadType 不是 `5` 时，不需要填写 PayloadUUID，如果填写会被后端忽略。   <br>
     *         该参数长度需为32位，否则会收到错误码为1091的回调。  <br>
     *         该参数每个字符的范围需为 [0, 9] [a, f] [A, F] <br>
     *         该参数不应带有`-`字符，如系统自动生成的 UUID 中带有`-`，则应删去。<br>
     *         在转推直播的过程中，该参数不支持变更。
     */
     const char* sei_payload_uuid = nullptr;
     /** 
      * @valid since 3.57
      * @brief 设置合流推到 CDN 时输出的媒体流类型。参看 MixedStreamMediaType{@link #MixedStreamMediaType}。<br>
      *        默认输出音视频流。支持输出纯音频流，但暂不支持输出纯视频流。
      */
     MixedStreamMediaType media_type = MixedStreamMediaType::kMixedStreamMediaTypeAudioAndVideo;
     /** 
      * @valid since 3.57
      * @brief 设置是否在没有用户发布流的情况下发起转推直播。具体参看 MixedStreamPushMode{@link #MixedStreamPushMode}。<br>
      *        该参数在发起合流任务后的转推直播过程中不支持动态变更。
      */
     MixedStreamPushMode push_stream_mode = MixedStreamPushMode::kMixedStreamPushModeOnStream;
} MixedStreamServerControlConfig;

/** 
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息。(新)
 *        开启合流功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 */
typedef struct MixedStreamLayoutRegionConfig {
    /** 
     * @brief 合流用户的 ID。建议设置。
     */
    const char* region_id = nullptr;
   /** 
     * @brief 图片或视频流所在房间的房间 ID。建议设置。<br>
     *        如果此图片或视频流是通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
     */
    const char* room_id = nullptr;
    /** 
     * @brief 单个用户画面左上角在整个画布坐标系中的 X 坐标（pixel），即以画布左上角为原点，用户画面左上角相对于原点的横向位移。<br>
     *        取值范围为 [0, 整体画布宽度)。默认值为 0。
     */
    int location_x = 0;
    /** 
     * @brief 单个用户画面左上角在整个画布坐标系中的 Y 坐标（pixel），即以画布左上角为原点，用户画面左上角相对于原点的纵向位移。<br>
     *        取值范围为 [0, 整体画布高度)。默认值为 0。
     */
    int location_y = 0;
    /** 
     * @brief 单个用户画面的宽度。取值范围为 [0, 整体画布宽度]，默认值为 360。
     */
    int width = MIXED_STREAM_VIDEO_DEFAULT_WIDTH;
    /** 
     * @brief 单个用户画面的高度。取值范围为 [0, 整体画布高度]，默认值为 640。
     */
    int height = MIXED_STREAM_DEFAULT_VIDEO_HEIGHT;
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
     * @brief 图片或视频流的缩放模式，参看 MixedStreamRenderMode{@link #MixedStreamRenderMode}。默认值为 1。建议设置。
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
     * @valid since 3.57
     * @brief 设置占位图的填充模式。<br>
     *        该参数用来控制当用户停止发布视频流，画面恢复为占位图后，此时占位图的填充模式。参看 MixedStreamAlternateImageFillMode{@link #MixedStreamAlternateImageFillMode}。
     */
    MixedStreamAlternateImageFillMode alternate_image_fill_mode = kMixedStreamAlternateImageFillModeFit;
    /** 
     * @valid since 3.57
     * @brief 设置占位图的 URL，长度小于 1024 字符.
     */
    const char* alternate_image_url = nullptr;
    /** 
     * @type keytype
     * @brief 空间位置。参看 Position{@link #Position}。
     */
    Position spatial_position;
    
    bool apply_spatial_audio = true;
    
} MixedStreamLayoutRegionConfig;

/** 
 * @deprecated since 3.52, use MixedStreamType{@link #MixedStreamType} instead.
 * @type keytype
 * @brief 合流类型
 */
enum StreamMixingType {
    /** 
     * @brief 服务端合流。
     */
    kStreamMixingTypeByServer = 0,
    /** 
     * @brief 端云一体合流。SDK 智能决策在客户端或服务端完成合流。
     */
    kStreamMixingTypeByClient = 1,
};


/** 
 * @deprecated since 3.52, use MixedStreamAudioProfile{@link #MixedStreamAudioProfile} instead.
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
 * @deprecated since 3.52, use MixedStreamAudioCodecType{@link #MixedStreamAudioCodecType} instead.
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
 * @deprecated since 3.52, use MixedStreamVideoCodecType{@link #MixedStreamVideoCodecType} instead.
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
 * @deprecated since 3.52, use MixedStreamRenderMode{@link #MixedStreamRenderMode} instead.
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
 * @deprecated since 3.52, use MixedStreamLayoutRegionType{@link #MixedStreamLayoutRegionType} instead.
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
 * @deprecated since 3.52, use MixedStreamLayoutRegionImageWaterMarkConfig{@link #MixedStreamLayoutRegionImageWaterMarkConfig} instead.
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
 * @deprecated since 3.52, use MixedStreamClientMixVideoFormat{@link #MixedStreamClientMixVideoFormat} instead.
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
 * @deprecated since 3.52, use MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} instead.
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
    TranscoderContentControlType content_control = TranscoderContentControlType::kHasAudioAndVideo;
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
 * @deprecated since 3.52, use MixedStreamAudioConfig{@link #MixedStreamAudioConfig} instead.
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
 * @deprecated since 3.52, use MixedStreamVideoConfig{@link #MixedStreamVideoConfig} instead.
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
    * @hidden
    */
    MixedStreamSyncStrategy sync_strategy = MixedStreamSyncStrategy::kMixedStreamSyncStrategyNoSync;
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
 * @deprecated since 3.52, use MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig} instead.
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
 * @deprecated since 3.52, use MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig} instead.
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
 * @deprecated since 3.52, use IMixedStreamConfig{@link #IMixedStreamConfig} instead.
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
     * @brief 设置音频参数。参看 TranscoderAudioParam{@link #TranscoderAudioParam}。<br>
     *        本参数不支持过程中更新。
     */
    virtual void setAudioParam(const TranscoderAudioParam&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置视频参数。参看 TranscoderVideoParam{@link #TranscoderVideoParam}。
     */
    virtual void setVideoParam(const TranscoderVideoParam&) = 0;
    /** 
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 设定转推 CDN 时的空间音频效果。参看 TranscoderSpatialConfig{@link #TranscoderSpatialConfig}。
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
     * @param [in] advanced_config 动态扩展自定义参数
     */
    virtual void setAdvancedConfig(const char* advanced_config) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置业务透传鉴权信息
     * @param [in] auth_info 业务透传鉴权信息
     */
    virtual void setAuthInfo(const char* auth_info) = 0;
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
     * @hidden only provide for IMixedStreamConfig
     */
    virtual MixedStreamServerControlConfig getServerControlConfig() = 0;
    /**
     * @hidden only provide for IMixedStreamConfig
     */
    virtual void setServerControlConfig(MixedStreamServerControlConfig& config) = 0;
    /**
     * @hidden constructor/destructor
     */
    virtual ~ITranscoderParam() = default;
};

/** 
 * @type keytype
 * @brief 转推直播配置参数。(新)
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
     * @brief 设置合流类型。建议设置。
     * @param [in] expected_mix_type 合流类型，参看 MixedStreamType{@link #MixedStreamType}
     */
    virtual void setExpectedMixingType(MixedStreamType expected_mix_type) = 0;
    /** 
     * @type api
     * @brief 设置推流用户 ID。`room_id` 和 `user_id` 长度相加不得超过 126 字节。建议设置。
     *        本参数不支持过程中更新。
     * @param [in] user_id 推流用户 ID。
     */
    virtual void setUserID(const char* user_id) = 0;
    /** 
     * @type api
     * @brief 设置推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。建议设置。
     *        本参数不支持过程中更新。
     * @param [in] url 推流地址。
     */
    virtual void setPushURL(const char* push_url) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置音频参数。参看 MixedStreamAudioConfig{@link #MixedStreamAudioConfig}。建议设置。
     *        本参数不支持过程中更新。
     */
    virtual void setAudioConfig(const MixedStreamAudioConfig&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置视频参数。参看 MixedStreamVideoConfig{@link #MixedStreamVideoConfig}。建议设置。
     */
    virtual void setVideoConfig(const MixedStreamVideoConfig&) = 0;
    /** 
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 设定转推 CDN 时的空间音频效果。参看 MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig}。
     */
    virtual void setSpatialAudioConfig(const MixedStreamSpatialAudioConfig&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置视频流合流整体布局信息。
     * @param [in] regions[] 用户布局信息列表。为 MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} 数据类型的数组。每一个该类型对象为一路单独的视频流的布局信息。
     *                       值不合法或未设置时，自动使用默认值。建议设置。
     * @param [in] regions_size 合流视窗数量。建议设置。
     * @param [in] background_color 合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。建议设置。
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
     * @param [in] advanced_config 动态扩展自定义参数
     */
    virtual void setAdvancedConfig(const char* advanced_config) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置业务透传鉴权信息
     * @param [in] auth_info 业务透传鉴权信息
     */
    virtual void setAuthInfo(const char* auth_info) = 0;
    /** 
     * @type api
     * @brief 设置客户端合流信息，参看 MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig}。
     */
    virtual void setClientMixConfig(MixedStreamClientMixConfig&) = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @brief 设置转推直播同步参数。参看 MixedStreamSyncControlConfig{@link #MixedStreamSyncControlConfig}。
     */
    virtual void setSyncControlConfig(MixedStreamSyncControlConfig&) = 0;
    /** 
     * @type api
     * @brief 获取服务端合流控制参数。参看 MixedStreamServerControlConfig{@link #MixedStreamServerControlConfig}。
     */
    virtual MixedStreamServerControlConfig getServerControlConfig() = 0;
    /** 
     * @type api
     * @brief 设置服务端合流控制参数。参看 MixedStreamServerControlConfig{@link #MixedStreamServerControlConfig}。
     */
    virtual void setServerControlConfig(MixedStreamServerControlConfig& config) = 0;
    /** 
     * @valid since 3.57
     * @type api
     * @brief 设置合流后整体画布的背景图片 URL，长度最大为 1024 bytes。<br>
     *        支持的图片格式包括：JPG, JPEG, PNG。如果背景图片的宽高和整体屏幕的宽高不一致，背景图片会缩放到铺满屏幕。
     */
    virtual void setBackgroundImageURL(const char* background_image_url) = 0;
    /** 
     * @valid since 3.57
     * @type api
     * @brief 获取背景图片的地址。
     */
    virtual const char* getBackgroundImageURL() = 0;
    /** 
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 将输入的 json 格式的字符串转成 ITranscoderParam 结构体
     * @param [in] json_str json 格式字符串
     * @return 转换后的 ITranscoderParam 结构体
     */
    virtual IMixedStreamConfig* inflatten(const char* json_str) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取默认的合流转推参数
     * @return 生成的 IMixedStreamConfig 结构体
     */
    virtual IMixedStreamConfig* defaultMixedStreamConfig() = 0;
    /**
     * @hidden constructor/destructor
     */
    virtual ~IMixedStreamConfig() = default;
    /**
     * @hidden for internal use only
     * @type api
     */
    virtual void setConvertFromOldTranscodeParam(bool is_from_old_param) = 0;
    /**
     * @hidden for internal use only
     * @type api
     */
    virtual bool getIsConvertFromOldTranscodeParam() = 0;
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
     * @brief 推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。
     *        本参数不支持过程中更新。
     */
    const char* uri;
    /** 
     * @brief 媒体流是否为屏幕流。
     */
    bool is_screen_stream;
}PushSingleStreamParam;

/** 
* @hidden internal use only
* @type keytype
* @brief 缓存同步模式。
*/
enum ChorusCacheSyncMode {
    /** 
     * @brief 合唱场景下，主唱应采用此模式，以发送带时间戳信息的媒体数据。
     */
    kChorusCacheSyncModeProducer= 0,
    /** 
     * @brief 合唱场景下，副唱应采用此模式。
     *        此模式下，副唱收到来自主唱的带时间戳的媒体数据。副唱发送的媒体数据中带有来自主唱的时间戳。
     */
    kChorusCacheSyncModeRetransmitter= 1,
    /** 
     * @brief 合唱场景下，听众应采用此模式。
     *        此模式下，听众收到来自主唱的时间戳，并据此对齐来自主唱和副唱的媒体数据，以获得良好的合唱播放效果。
     */
    kChorusCacheSyncModeConsumer = 2
};
/** 
* @hidden internal use only
* @type keytype
* @brief 缓存同步事件。
*/
enum ChorusCacheSyncEvent {
     /** 
     * @brief 成功
     */
    kChorusCacheSyncEventStartSuccess = 0,
     /** 
     * @brief 失败。
     */
    kChorusCacheSyncEventStartFailed = 1,
};
/** 
* @hidden internal use only
* @type errorcode
* @brief 缓存同步错误码。
*/
enum ChorusCacheSyncError {
    /** 
     * @brief 成功。
     */
    kChorusCacheSyncErrorOK = 0,
   /** 
    * @brief 失败。推送至 CDN 时，应进行以下设置：
    *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.enable_sync = true`；
    *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.base_user_id = {uid of producer}`。
    */
    kChorusCacheSyncErrorWrongState = 1,
    /** 
    * @brief 缓存同步功能已启动，不需要重复开启。
    */
    kChorusCacheSyncErrorAlreadyRunning = 2
};
/** 
* @hidden internal use only
* @type keytype
* @brief 缓存同步配置。
*/
struct ChorusCacheSyncConfig {
     /** 
      * @brief 最大媒体缓存时长（ms）。
      *        取值范围是 `[500, 2500]`，默认值是 `2000`。
      *        值越大，同步效果越好，但会造成占用内存较大。如果参与缓存同步的各路媒体流之间的时间差超过此值，会造成丢帧。
      */
     int32_t max_cache_time_ms = 2000;
    /** 
      * @brief 收到 onSyncedVideoFrames{@link #IChorusCacheSyncObserver#onSyncedVideoFrames} 的频率。
      *        默认值是 `15`。此值通常应小于等于原始视频帧率；如果大于原始视频帧率，可能会收到重复帧。
      */
     int32_t video_fps = 15;
    /** 
      * @brief 模式。参看 ChorusCacheSyncMode{@link #ChorusCacheSyncMode}. 默认值是 `retransmitter`。  
      */
     ChorusCacheSyncMode mode = kChorusCacheSyncModeRetransmitter;
};
}  // namespace bytertc
