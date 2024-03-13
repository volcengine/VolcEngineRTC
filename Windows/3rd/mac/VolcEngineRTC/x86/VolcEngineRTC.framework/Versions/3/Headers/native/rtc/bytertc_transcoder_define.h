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
 * @locale zh
 * @type keytype
 * @brief 转推直播事件
 */
/**
 * @locale en
 * @type keytype
 * @brief Events during pushing streams to CDN
 */
enum StreamMixingEvent {
    /**
     * @hidden for internal use only
     */
    kStreamMixingEventBase = 0,
    /**
     * @locale zh
     * @brief 请求发起转推直播任务
     */
    /**
     * @locale en
     * @brief Request to start pushing streams to CDN
     */
    kStreamMixingEventStart = 1,
    /**
     * @locale zh
     * @brief 发起转推直播任务成功
     */
    /**
     * @locale en
     * @brief ask to push streams to CDN started
     */
    kStreamMixingEventStartSuccess = 2,
    /**
     * @locale zh
     * @brief 发起转推直播任务失败
     */
    /**
     * @locale en
     * @brief Failed to start the task to push streams to CDN
     */
    kStreamMixingEventStartFailed = 3,
    /**
     * @locale zh
     * @brief 请求更新转推直播任务配置
     */
    /**
     * @locale en
     * @brief Request to update the configuration for the task to push streams to CDN
     */
    kStreamMixingEventUpdate = 4,
    /**
     * @locale zh
     * @brief 成功更新转推直播任务配置
     */
    /**
     * @locale en
     * @brief Successfully update the configuration for the task to push streams to CDN
     */
    kStreamMixingEventUpdateSuccess = 5,
    /**
     * @locale zh
     * @brief 更新转推直播任务配置失败
     */
    /**
     * @locale en
     * @brief Failed to update the configuration for the task to push streams to CDN
     */
    kStreamMixingEventUpdateFailed = 6,
    /**
     * @locale zh
     * @brief 请求结束转推直播任务
     */
    /**
     * @locale en
     * @brief Request to stop the task to push streams to CDN
     */
    kStreamMixingEventStop = 7,
    /**
     * @locale zh
     * @brief 结束转推直播任务成功
     */
    /**
     * @locale en
     * @brief The task to push streams to CDN stopped
     */
    kStreamMixingEventStopSuccess = 8,
    /**
     * @locale zh
     * @brief 结束转推直播任务失败
     */
    /**
     * @locale en
     * @brief Failed to stop the task to push streams to CDN
     */
    kStreamMixingEventStopFailed = 9,
    /**
     * @locale zh
     * @brief 更新转推直播任务配置的请求超时
     */
    /**
     * @locale en
     * @brief Timeout for the request to update the configuration for the task to push streams to CDN.
     */
    kStreamMixingEventChangeMixType = 10,
    /**
     * @locale zh
     * @brief 得到客户端合流音频首帧
     */
    /**
     * @locale en
     * @brief Got the first frame of the mixed audio stream by client.
     */
    kStreamMixingEventFirstAudioFrameByClientMix = 11,
    /**
     * @locale zh
     * @brief 收到客户端合流视频首帧
     */
    /**
     * @locale en
     * @brief Got the first frame of the mixed video stream by client.
     */
    kStreamMixingEventFirstVideoFrameByClientMix = 12,
    /**
     * @locale zh
     * @brief 更新转推直播任务配置超时
     */
    /**
     * @locale en
     * @brief Timeout for the request to update the configuration for the task to push streams to CDN
     */
    kStreamMixingEventUpdateTimeout = 13,
    /**
     * @locale zh
     * @brief 发起转推直播任务配置超时
     */
    /**
     * @locale en
     * @brief Timeout for the request to start the task to push streams to CDN
     */
    kStreamMixingEventStartTimeout = 14,
    /**
     * @locale zh
     * @brief 合流布局参数错误
     */
    /**
     * @locale en
     * @brief Error in the parameters of the request for the task to push streams to CDN
     */
    kStreamMixingEventRequestParamError = 15,
    /**
    * @locale zh
    * @brief 合流加图片
    */
    /**
     * @locale en
     * @brief Mixing image.
     */
    kStreamMixingEventMixImageEvent = 16,
    /**
     * @locale zh
     * @hidden internal use only
     * @valid since 3.50
     * @brief 单通合唱事件
     */
    /**
     * @locale en
     * @hidden internal use only
     * @hidden currently not available
     * @brief Simplex chorus event
     */
    kStreamMixingEventMixSingleWayChorusEvent = 17,
};


/**
 * @locale zh
 * @type errorcode
 * @brief 单流转推直播错误码
 */
/**
 * @locale en
 * @type errorcode
 * @brief Errors occurring during pushing a single stream to CDN
 */
enum SingleStreamPushEvent {
    /**
     * @hidden for internal use only
     */
    kSingleStreamPushEventBase = 0,
    /**
    * @locale zh
    * @brief 开始推流。
    */
   /**
    * @locale en
    * @brief Starting pushing a single stream to CDN.
    */
    kSingleStreamPushEventStart = 1,
    /**
    * @locale zh
    * @brief 推流成功。
    */
   /**
    * @locale en
    * @brief Successfully pushed a single stream to CDN.
    */
    kSingleStreamPushEventSuccess = 2,
    /**
    * @locale zh
    * @brief 推流失败。
    */
   /**
    * @locale en
    * @brief Failed to push a single stream to CDN.
    */
    kSingleStreamPushEventFailed = 3,
    /**
     * @locale zh
     * @brief 停止推流。
     */
    /**
     * @locale en
     * @brief Stop pushing a single stream to CDN.
     */
    kSingleStreamPushEventStop = 4,
    /**
    * @locale zh
    * @brief 单流转推直播任务处理超时，请检查网络状态并重试。
    */
   /**
    * @locale en
    * @brief Request timed out. Please check network status and retry.
    */
    kSingleStreamPushEventTimeout = 5,
    /**
     * @locale zh
     * @brief 参数错误。
     */
    /**
     * @locale en
     * @brief Request failed due to invalid parameter.
     */
    kSingleStreamPushEventParamError = 6,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 转推直播错误码
 */
/**
 * @locale en
 * @type errorcode
 * @brief Errors occurring during pushing streams to CDN
 */
enum StreamMixingErrorCode {
    /**
     * @locale zh
     * @brief 推流成功。
     */
    /**
     * @locale en
     * @brief Successfully pushed streams to target CDN.
     */
    kStreamMixingErrorCodeOK = 0,
    /**
     * @locale zh
     * @brief 未定义的合流错误
     */
    /**
     * @locale en
     * @brief Undefined error
     */
    kStreamMixingErrorCodeBase= 1090,
    /**
     * @locale zh
     * @brief 客户端 SDK 检测到无效推流参数。
     */
    /**
     * @locale en
     * @brief Invalid parameters detected by Client SDK.
     */
    kStreamMixingErrorCodeInvalidParam = 1091,
    /**
     * @locale zh
     * @brief 状态错误，需要在状态机正常状态下发起操作
     */
    /**
     * @locale en
     * @brief Program runs with an error, the state machine is in abnormal condition.
     */
    kStreamMixingErrorCodeInvalidState = 1092,
    /**
     * @locale zh
     * @brief 无效操作
     */
    /**
     * @locale en
     * @brief Invalid operation
     */
    kStreamMixingErrorCodeInvalidOperator = 1093,
    /**
     * @locale zh
     * @brief 转推直播任务处理超时，请检查网络状态并重试
     */
    /**
     * @locale en
     * @brief Request timed out. Please check network status and retry.
     */
    kStreamMixingErrorCodeTimeout = 1094,
    /**
     * @locale zh
     * @brief 服务端检测到错误的推流参数
     */
    /**
     * @locale en
     * @brief Invalid parameters detected by the server
     */
    kStreamMixingErrorCodeInvalidParamByServer = 1095,
    /**
     * @locale zh
     * @brief 对流的订阅超时
     */
    /**
     * @locale en
     * @brief Subscription to the stream has expired.
     */
    kStreamMixingErrorCodeSubTimeoutByServer = 1096,
    /**
     * @locale zh
     * @brief 合流服务端内部错误。
     */
    /**
     * @locale en
     * @brief Internal server error.
     */
    kStreamMixingErrorCodeInvalidStateByServer = 1097,
    /**
     * @locale zh
     * @brief 合流服务端推 CDN 失败。
     */
    /**
     * @locale en
     * @brief The server failed to push streams to CDN.
     */
    kStreamMixingErrorCodeAuthenticationByCDN  = 1098,
    /**
     * @locale zh
     * @brief 服务端接收信令超时，请检查网络状态并重试。
     */
    /**
     * @locale en
     * @brief Signaling connection timeout error. Please check network status and retry.
     */
    kStreamMixingErrorCodeTimeoutBySignaling = 1099,
    /**
     * @locale zh
     * @brief 图片合流失败。
     */
    /**
     * @locale en
     * @brief Failed to mix image.
     */
    kStreamMixingErrorCodeMixImageFail = 1100,
    /**
     * @locale zh
     * @brief 服务端未知错误。
     */
    /**
     * @locale en
     * @brief Unknown error from server.
     */
    kStreamMixingErrorCodeUnKnownByServer = 1101,
    /**
     * @locale zh
     * @hidden internal use only
     * @valid since 3.50
     * @brief 缓存未同步。
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief The cache is not synchronized.
     */
    kStreamMixingErrorCodeStreamSyncWorse = 1102,
    /**
     * @locale zh
     * @hidden 只供内部使用
     * @brief 合流消息中的用户布局信息发生了变化。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief The ‘regions’ field in transcoding message is changed.
     */
    kStreamMixingErrorCodeUpdateRegionChanged = 1103,
    /**
     * @hidden for internal use only
     */
    kStreamMixingErrorCodeMax = 1199,
};

/**
 * @locale zh
 * @type keytype
 * @brief 合流类型。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream mixing type.(New)
 */
enum MixedStreamType {
    /**
     * @locale zh
     * @brief 服务端合流
     */
    /**
     * @locale en
     * @brief Mix media streams on the server side.
     */
    kMixedStreamTypeByServer = 0,
    /**
     * @locale zh
     * @brief 端云一体合流。SDK 智能决策在客户端或服务端完成合流。<br>
     *        使用前，请联系技术支持同学开通，否则不生效。
     */
    /**
     * @locale en
     * @brief Intelligent stream mixing. The SDK will intelligently decide that a stream mixing task would be done on the client or the server.<br>
     *        Before using the option, please contact the technical support. Otherwise, the option does not take effect.
     */
    kMixedStreamTypeByClient = 1,
};


/**
 * @locale zh
 * @type keytype
 * @brief AAC 编码规格。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Advanced Audio Coding (AAC) profile.(New)
 */
enum MixedStreamAudioProfile {
    /**
     * @locale zh
     * @brief AAC-LC 规格，默认值。
     */
    /**
     * @locale en
     * @brief (Default) AAC Low-Complexity profile (AAC-LC).
     */
    kMixedStreamAudioProfileLC = 0,
    /**
     * @locale zh
     * @brief HE-AAC v1 规格。
     */
    /**
     * @locale en
     * @brief HE-AAC v1 profile (AAC LC with SBR).
     */
    kMixedStreamAudioProfileHEv1 = 1,
    /**
     * @locale zh
     * @brief HE-AAC v2 规格。
     */
    /**
     * @locale en
     * @brief HE-AAC v2 profile (AAC LC with SBR and Parametric Stereo).
     */
    kMixedStreamAudioProfileHEv2 = 2,
};

/**
 * @hidden
 * @brief notes missing
 */
enum MixedStreamSyncStrategy {
    /**
     * @locale zh
     * @brief 不使用同步策略
     */
    kMixedStreamSyncStrategyNoSync = 0,
    /**
     * @locale zh
     * @brief 使用音频精准同步策略
     */
    kMixedStreamSyncStrategyAudioPreciseSync = 1,
    /**
     * @locale zh
     * @brief 使用单通模式同步策略
     */
    kMixedStreamSyncStrategySimplexModeSync = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频编码格式。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief The audio codec.(New)
 */
enum MixedStreamAudioCodecType {
    /**
     * @locale zh
     * @brief AAC 格式。
     */
    /**
     * @locale en
     * @brief AAC format.
     */
    kMixedStreamAudioCodecTypeAAC = 0,
};

/**
 * @locale zh
 * @type keytype
 * @brief 服务端合流转推 SEI 内容。
 */
/**
 * @locale en
 * @type keytype
 * @brief Content of SEI sent while pushing mixed stream to CDN.
 */
enum MixedStreamSEIContentMode {
    /**
     * @locale zh
     * @brief 视频流中包含全部的 SEI 信息。默认设置。
     */
    /**
     * @locale en
     * @brief The video stream contains all the SEI information. Default value.
     */
    kMixedStreamSEIContentModeDefault = 0,
    /**
     * @locale zh
     * @brief 随非关键帧传输的 SEI 数据中仅包含音量信息。<br>
     *        当设置 `MixedStreamServerControlConfig.enable_volume_indication` 为 True 时，此参数设置生效。
     */
    /**
     * @locale en
     * @brief The SEI data transmitted with non-key frames contains volume information only.<br>
     *        This parameter only takes effect after you set `MixedStreamServerControlConfig.enable_volume_indication` to "True".
     */
    kMixedStreamSEIContentModeEnableVolumeIndication = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频编码格式。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief The video codec.(New)
 */
enum MixedStreamVideoCodecType {
    /**
     * @locale zh
     * @brief H.264 格式，默认值。
     */
    /**
     * @locale en
     * @brief (Default) H.264 format.
     */
    kMixedStreamVideoCodecTypeH264 = 0,
    /**
     * @locale zh
     * @brief ByteVC1 格式。
     */
    /**
     * @locale en
     * @brief ByteVC1 format.
     */
    kMixedStreamVideoCodecTypeByteVC1 = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 图片或视频流的缩放模式。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief The render mode.(New)
 */
enum MixedStreamRenderMode {
    /**
     * @locale zh
     * @brief 视窗填满优先，默认值。<br>
     *        视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    /**
     * @locale en
     * @brief (Default) Fill and Crop.<br>
     *        The video frame is scaled with fixed aspect ratio, until it completely fills the canvas. The region of the video exceeding the canvas will be cropped.
     */
    kMixedStreamRenderModeHidden = 1,
    /**
     * @locale zh
     * @brief 视频帧内容全部显示优先。<br>
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。
     */
    /**
     * @locale en
     * @brief Fit.<br>
     *        The video frame is scaled with fixed aspect ratio, until it fits just within the canvas. Other part of the canvas is filled with the background color.
     */
    kMixedStreamRenderModeFit = 2,
    /**
     * @locale zh
     * @brief 视频帧自适应画布。<br>
     *        视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
    /**
     * @locale en
     * @brief Fill the canvas.<br>
     *        The video frame is scaled to fill the canvas. During the process, the aspect ratio may change.
     */
    kMixedStreamRenderModeAdaptive = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 合流输出内容类型。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Types of stream after being mixed.(New)
 */
enum MixedStreamMediaType {
    /**
     * @locale zh
     * @brief 输出的混流包含音频和视频
     */
    /**
     * @locale en
     * @brief Audio and video
     */
    kMixedStreamMediaTypeAudioAndVideo = 0,
    /**
     * @locale zh
     * @brief 输出的混流只包含音频
     */
    /**
     * @locale en
     * @brief Audio only
     */
    kMixedStreamMediaTypeAudioOnly = 1,
    /**
     * @locale zh
     * @brief 输出的混流只包含视频
     */
    /**
     * @locale en
     * @brief Video only
     */
    kMixedStreamMediaTypeVideoOnly = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 合流布局区域类型。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream mixing region type.(New)
 */
enum MixedStreamLayoutRegionType {
    /**
     * @locale zh
     * @brief 合流布局区域类型为视频。
     */
    /**
     * @locale en
     * @brief The region type is a video stream.
     */
    kMixedStreamLayoutRegionTypeVideoStream = 0,
    /**
     * @locale zh
     * @brief 合流布局区域类型为图片。
     */
    /**
     * @locale en
     * @brief The region type is an image.
     */
    kMixedStreamLayoutRegionTypeImage = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 客户端合流回调视频格式。(新)<br>
 *        设置为系统不支持的格式时，自动回调系统默认格式。
 */
/**
 * @locale en
 * @type keytype
 * @brief The video format for client stream mixing callback.(New)<br>
 *        If the format you set is not adaptable to the system, the format will be set as the default value.
 */
enum MixedStreamClientMixVideoFormat {
    /**
     * @locale zh
     * @brief YUV I420。Android、Windows 默认回调格式。支持系统：Android、Windows。
     */
    /**
     * @locale en
     * @brief YUV I420 format. The default format for Android and Windows. Supported system: Android, Windows.
     */
    kMixedStreamClientMixVideoFormatI420 = 0,
    /**
     * @locale zh
     * @brief OpenGL GL_TEXTURE_2D 格式纹理。支持系统：安卓。
     */
    /**
     * @locale en
     * @brief OpenGL GL_TEXTURE_2D format. Supported system: Android.
     */
    kMixedStreamClientMixVideoFormatTexture2D = 1,
    /**
     * @locale zh
     * @brief CVPixelBuffer BGRA。iOS 默认回调格式。支持系统: iOS。
     */
    /**
     * @locale en
     * @brief CVPixelBuffer BGRA format. The default format for iOS. support system: iOS.
     */
    kMixedStreamClientMixVideoFormatCVPixelBufferBGRA = 2,
    /**
     * @locale zh
     * @brief YUV NV12。macOS 默认回调格式。支持系统: macOS。
     */
    /**
     * {en}
     * @brief YUV NV12 format. The default format for macOS. Supported system: macOS.
     */
    kMixedStreamClientMixVideoFormatNV12 = 3,
};
/**
 * @locale zh
 * @type keytype
 * @brief 服务端合流转推发起模式。
 */
/**
 * @locale en
 * @type keytype
 * @brief The initiation mode for pushing the stream mixed on the server side to CDN.
 */
enum MixedStreamPushMode {
    /**
     * @locale zh
     * @brief 无用户发布媒体流时，发起合流任务无效。默认设置。<br>
     *        当有用户发布媒体流时，才能发起合流任务。
     */
    /**
     * @locale en
     * @brief The initiation of a stream mixing task is dependent on a user actively publishing media streams.
     */
    kMixedStreamPushModeOnStream = 0,
    /**
     * @locale zh
     * @brief 无用户发布媒体流时，可以使用占位图发起合流任务。<br>
     *        占位图设置参看 alternate_image_url{@link #MixedStreamLayoutRegionConfig#alternate_image_url} 和 alternate_image_fill_mode{@link #MixedStreamLayoutRegionConfig#alternate_image_fill_mode}
     */
    /**
     * @locale en
     * @brief Even if no user is actively publishing media streams, it is still possible to initiate a stream mixing task using a placeholder image.<br>
     *        See alternate_image_url{@link #MixedStreamLayoutRegionConfig#alternate_image_url} and alternate_image_fill_mode{@link #MixedStreamLayoutRegionConfig#alternate_image_fill_mode} for setting a placeholder image.
     */
    kMixedStreamPushModeOnStartRequest = 1,
};
/**
 * @locale zh
 * @type keytype
 * @brief 服务端合流占位图填充模式。
 */
/**
 * @locale en
 * @type keytype
 * @brief The fill mode of the placeholder image.
 */
enum MixedStreamAlternateImageFillMode {
    /**
     * @locale zh
     * @brief 占位图跟随用户原始视频帧相同的比例缩放。默认设置。
     */
    /**
     * {en}
     * @brief The placeholder image is scaled with the same aspect ratio as the user's original video frame. Default setting.
     */
    kMixedStreamAlternateImageFillModeFit = 0,
    /**
     * @locale zh
     * @brief 占位图不跟随用户原始视频帧相同的比例缩放，保持图片原有比例。
     */
    /**
     * {en}
     * @brief The placeholder image is not scaled with the same aspect ratio as the user's original video frame. It maintains the original aspect ratio.
     */
    kMixedStreamAlternateImageFillModeFill = 1,
};
/**
 * @locale zh
 * @type keytype
 * @brief region 中流的类型属性
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream type
 */
enum MixedStreamVideoType {
    /**
     * @locale zh
     * @brief 主流。包括：<br>
     *        + 由摄像头/麦克风通过内部采集机制，采集到的流<br>
     *        + 通过自定义采集，采集到的流。
     */
    /**
     * @locale en
     * @brief Mainstream, including: <br>
     *       + Video/audio captured by the the camera/microphone using internal capturing; <br>
     *       + Video/audio captured by custom method.
     */
    kMixedStreamVideoTypeMain = 0,
    /**
     * @locale zh
     * @brief 屏幕流。
     */
    /**
     * @locale en
     * @brief Screen-sharing stream.
     */
    kMixedStreamVideoTypeScreen = 1,
};


/**
 * @locale zh
 *  @type keytype
 *  @brief 音频合流配置参数。(新)<br>
 *         值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 *  @type keytype
 *  @brief Audio mix stream configurations.(New)<br>
 *         With invalid or empty input, the configurations will be set as the default values.
 */
typedef struct MixedStreamAudioConfig {
    /**
     * @locale zh
     * @brief 音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。建议设置。
     */
    /**
     * @locale en
     * @brief The sample rate (Hz). Supported sample rates: 32,00 Hz, 44,100 Hz, 48,000 Hz. Defaults to 48,000 Hz. It's recommended to be set.
     */
    int32_t sample_rate = 48000;
    /**
     * @locale zh
     * @brief 音频声道数。可取 1（单声道）、2（双声道），默认值为 2。建议设置。
     */
    /**
     * @locale en
     * @brief The number of channels. Supported channels: 1 (single channel), 2 (dual channel).  Defaults to 2. It's recommended to be set.
     */
    int32_t channels = 2;
    /**
     * @locale zh
     * @brief 音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。建议设置。
     */
    /**
     * @locale en
     * @brief The bitrate (Kbps) in range of [32, 192]. Defaults to 64 Kbps. It's recommended to be set.
     */
    int32_t bitrate = 64;
    /**
     * @locale zh
     * @brief AAC 编码规格，参看 MixedStreamAudioProfile{@link #MixedStreamAudioProfile}。默认值为 `0`。建议设置。
     */
    /**
     * @locale en
     * @brief AAC profile. See MixedStreamAudioProfile{@link #MixedStreamAudioProfile}. Defaults to `0`. It's recommended to be set.
     */
    MixedStreamAudioProfile audio_profile = MixedStreamAudioProfile::kMixedStreamAudioProfileLC;
    /**
     * @locale zh
     * @brief 音频编码格式，参看 MixedStreamAudioCodecType{@link #MixedStreamAudioCodecType}。默认值为 `0`。建议设置。
     */
    /**
     * @locale en
     * @brief AAC profile. See MixedStreamAudioCodecType{@link #MixedStreamAudioCodecType}. Defaults to `0`. It's recommended to be set.
     */
    MixedStreamAudioCodecType audio_codec = MixedStreamAudioCodecType::kMixedStreamAudioCodecTypeAAC;
} MixedStreamAudioConfig;

#define MIXED_STREAM_VIDEO_DEFAULT_WIDTH 360
#define MIXED_STREAM_DEFAULT_VIDEO_HEIGHT 640
/**
 * @locale zh
 * @type keytype
 * @brief 视频合流配置参数。(新)<br>
 *        值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @type keytype
 * @brief Video mix stream configurations.(New)<br>
 *        With invalid or empty input, the configurations will be set as the default values.
 */
typedef struct MixedStreamVideoConfig {
    /**
     * @locale zh
     * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。建议设置。<br>
     *        设置值为非偶数时，自动向上取偶数。
     */
    /**
     * @locale en
     * @brief The width (pixels) to be set. The range is [2, 1920], and must be an even number. The default value is 360 pixels. It's recommended to be set.<br>
     *        If an odd number is set, the width will be adjusted to the next larger even number.
     */
    int32_t width = MIXED_STREAM_VIDEO_DEFAULT_WIDTH;
    /**
     * @locale zh
     * @brief 合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。建议设置。<br>
     *        设置值为非偶数时，自动向上取偶数。
     */
    /**
     * @locale en
     * @brief The height (pixels) to be set. The range is [2, 1920], and must be an even number. The default value is 640 pixels. It's recommended to be set.<br>
     *        If an odd number is set, the height will be adjusted to the next larger even number.
     */
    int32_t height = MIXED_STREAM_DEFAULT_VIDEO_HEIGHT;
    /**
     * @locale zh
     * @brief 合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。建议设置。
     */
    /**
     * @locale en
     * @brief The frame rate (FPS) in range of [1, 60]. The default value is 15 FPS. It's recommended to be set.
     */
    int32_t fps = 15;
    /**
     * @locale zh
     * @brief 视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。建议设置。<br>
     *        本参数不支持过程中更新。
     */
    /**
     * @locale en
     * @brief The time interval between I-frames (second) in range of [1, 5]. The default value is 2 seconds. It's recommended to be set.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     */
    int32_t gop = 2;
    /**
     * @locale zh
     * @brief 合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。建议设置。
     */
    /**
     * @locale en
     * @brief The bitrate (Kbps) in range of [1, 10000]. The default value is self-adaptive. It's recommended to be set.
     */
    int32_t bitrate = 500;
    /**
     * @locale zh
     * @brief 视频编码格式，参看 MixedStreamVideoCodecType{@link #MixedStreamVideoCodecType}。默认值为 `0`。建议设置。<br>
     *        本参数不支持过程中更新。
     */
    /**
     * @locale en
     * @brief The video codec. See MixedStreamVideoCodecType{@link #MixedStreamVideoCodecType}. The default value is `0`. It's recommended to be set.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     */
    MixedStreamVideoCodecType video_codec = MixedStreamVideoCodecType::kMixedStreamVideoCodecTypeH264;
    /**
      * @locale zh
      * @brief 是否在合流中开启B帧，仅服务端合流支持：  <br>
      *        + true: 是  <br>
      *        + false: 否
      */
     /**
      * @locale en
      * @brief Whether to push streams with B frame, only support by server mix:   <br>
      *         + True: Yes <br>
      *         + False: No
      */
    bool enable_bframe = false;
} MixedStreamVideoConfig;

/**
 * @locale zh
 * @type keytype
 * @brief 客户端合流参数。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Client mixing parameters.(New)
 */
typedef struct MixedStreamClientMixConfig {
    /**
     * @locale zh
     * @brief 客户端合流是否使用混音，默认为 true。
     */
    /**
     * @locale en
     * @brief Whether to use audio mixing. Default is true.
     */
    bool use_audio_mixer = true;
    /**
     * @locale zh
     * @brief 客户端合流回调视频格式，参看 MixedStreamClientMixVideoFormat{@link #MixedStreamClientMixVideoFormat}。
     */
    /**
     * @locale en
     * @brief The video format to be set. See MixedStreamClientMixVideoFormat{@link #MixedStreamClientMixVideoFormat}.
     */
    MixedStreamClientMixVideoFormat video_format;
} MixedStreamClientMixConfig;

/**
 * @locale zh
 * @hidden for internal use only
 * @type keytype
 * @brief 转推直播单通同步参数。(新)
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type keytype
 * @brief Parameters of simplex mode and synchronization when pushing to CDN.(New)
 */
typedef struct MixedStreamSyncControlConfig {
    /**
     * @locale zh
     * @brief 在进行同步处理时，缓存音视频流的最大长度。单位为毫秒。默认值为 2000。
     * @note 参与转推直播的这些媒体流延迟越高，应该将此值设置的越大。但此值越大，因缓存媒体流造成的内存占用也会更大。推荐值为 `2000`。
     */
    /**
     * @locale en
     * @brief The max length of the cached stream in milliseconds. 2000 by default.
     * @note Set the value based on the stall of the media streams. Higher the value, bigger the memory usage. The recommended value is `2000`.
     */
    int32_t max_cache_time_ms = 2000;
    /**
     * @locale zh
     * @brief 是否在转推直播时，启用单通模式。默认为 false，不启用。<br>
     *        启用单通模式时，RTC SDK 会对指定的多个用户的媒体流进行同步处理，再合流后推送到 CDN，但基准流所属用户不会播放来自其他用户的媒体流。你需要设定以下参数。<br>
     *        非单通模式时，RTC SDK 不会对媒体流进行同步处理，只是简单合流后推送到 CDN。以下参数设定无效。
     */
    /**
     * @locale en
     * @brief Whether to enable simplex mode during pushing to CDN. False(duplex mode) by default.<br>
     *        When simplex mode is enabled, RTC SDK synchronizes and transcodes the media streams from the local user and several remote users, and pushing the mixed stream to CDN. `syncBaseUser` does not play the streams from the remote users. You must set the following parameters.<br>
     *        When duplex mode is enabled, RTC SDK transcodes the media streams from the local user and several remote users without synchronization, and pushing the mixed stream to CDN. The following parameters are not effective.
     */
    /**
     * @locale zh
     * @brief 同步策略
     */
    MixedStreamSyncStrategy sync_strategy = MixedStreamSyncStrategy::kMixedStreamSyncStrategyNoSync;
    /**
     * @locale zh
     * @brief 在进行同步处理时，基准流所属用户的 ID。默认为空。
     */
    /**
     * @locale en
     * @brief User ID of the base stream during syncing. Null by default.
     */
    const char* base_user_id = nullptr;
    /**
     * @locale zh
     * @brief 是否通过 RTC SDK 进行转推直播。默认为 True。<br>
     *        如果选择 `False`，你会通过 onCacheSyncVideoFrames{@link #ITranscoderObserver#onCacheSyncVideoFrames} 收到同步的帧，你可以使用此视频帧，自行实现合流转推。
     */
    /**
     * @locale en
     * @brief Whether to use RTC SDK to push to CDN. True by default.<br>
     *        If `False`, you can get the media frames by onCacheSyncVideoFrames{@link #ITranscoderObserver#onCacheSyncVideoFrames} and manually push them to CDN.
     */
    bool video_need_sdk_mix = true;
} MixedStreamSyncControlConfig;

/**
 * @locale zh
 * @type keytype
 * @brief 图片合流相关参数。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Image parameters for stream mixing.(New)
 */
typedef struct MixedStreamLayoutRegionImageWaterMarkConfig {
    /**
     * @locale zh
     * @brief 原始图片的宽度，单位为 px。
     */
    /**
     * @locale en
     * @brief Width of the original image in px.
     */
    int image_width = 0;
    /**
     * @locale zh
     * @brief 原始图片的高度，单位为 px。
     */
    /**
     * @locale en
     * @brief Height of the original image in px.
     */
    int image_height = 0;
} MixedStreamLayoutRegionImageWaterMarkConfig;

/**
 * @locale zh
 * @type keytype
 * @brief 推流 CDN 的空间音频参数。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Spatial audio config when pushing to CDN.(New)
 */
typedef struct MixedStreamSpatialAudioConfig {
    /**
     * @locale zh
     * @brief 是否开启推流 CDN 时的空间音频效果。
     * @note 当你启用此效果时，你需要设定推流中各个 MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} 的 `spatial_position` 值，实现空间音频效果。
     */
    /**
     * @locale en
     * @brief Whether to enable the spatial audio effect when pushing to CDN.
     * @note when you enable the feature, set the `spatial_position` of each MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} for spatial audio effect.
     */
    bool enable_spatial_render;
    /**
     * @locale zh
     * @brief 听众的空间位置。参看 Position{@link #Position}。<br>
     *        听众指收听来自 CDN 的音频流的用户。
     */
    /**
     * @locale en
     * @brief The spatial position of the audience. See Position{@link #Position}. <br>
     *        The audience is the users who receive the audio stream from CDN.
     */
    Position audience_spatial_position;
    /**
     * @locale zh
     * @brief 听众的空间朝向。参看 HumanOrientation{@link #HumanOrientation}。<br>
     *        听众指收听来自 CDN 的音频流的用户。
     */
    /**
     * @locale en
     * @brief The orientation of the audience. See HumanOrientation{@link #HumanOrientation}. <br>
     *        The audience is the users who receive the audio stream from CDN.
     */
    HumanOrientation audience_spatial_orientation;
} MixedStreamSpatialAudioConfig;

/**
 * @locale zh
 * @type keytype
 * @brief 服务端合流控制参数
 */
/**
 * @locale en
 * @type keytype
 * @brief Configurations to be set while mixing streams on the server side.
 */
typedef struct MixedStreamServerControlConfig {
    /**
     * @locale zh
     * @valid since 3.56
     * @brief 是否开启单独发送声音提示 SEI 的功能：<br>
     *        + True：开启；<br>
     *        + False：关闭。（默认值）<br>
     *        开启后，你可以通过 `MixedStreamServerControlConfig.sei_content_mode` 控制 SEI 的内容是否只携带声音信息。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @brief Sets whether to enable the function of separately sending sound indication SEI:<br>
     *        + True: Enable.<br>
     *        + False: Disable. Default setting.<br>
     *        After setting this parameter to "true", you can choose whether to send sound indication SEI only through `MixedStreamServerControlConfig.sei_content_mode`.
     */
    bool enable_volume_indication = false;
    /**
     * @locale zh
     * @valid since 3.56
     * @brief 声音提示间隔，单位为秒，取值范围为 [0.3,+∞)，默认值为 2。<br>
     *        此值仅取整百毫秒。若传入两位及以上小数，则四舍五入取第一位小数的值。例如，若传入 0.36，则取 0.4。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @brief Sound indication interval in s. The range is [0.3,+∞). The default value is 2.<br>
     *        If a decimal with two or more decimal places is passed in, it will be rounded to the value of the first decimal place. For example, if you pass in 0.36, it will be automatically adjusted to 0.4.
     */
    float volume_indication_interval = 2.0f;
    /**
     * @locale zh
     * @valid since 3.56
     * @brief 有效音量大小，取值范围为 [0, 255]，默认值为 0。<br>
     *        超出取值范围则自动调整为默认值，即 0。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @brief Effective volume within the range of [0, 255]. The default value is 0.<br>
     *        If the value is set beyond the range, it will be automatically adjusted to the default value 0.
     */
    int talk_volume = 0;
    /**
     * @locale zh
     * @valid since 3.56
     * @brief 声音信息 SEI 是否包含音量值：<br>
     *        + True：是；<br>
     *        + False：否，默认值。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @brief Sets whether volume value is contained in the sound indication SEI:<br>
     *        + True: Yes.<br>
     *        + False: No. Default setting.
     */
    bool is_add_volume_value = false;
    /**
     * @locale zh
     * @valid since 3.56
     * @brief 设置 SEI 内容。参看 MixedStreamSEIContentMode{@link #MixedStreamSEIContentMode}。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @brief Sets SEI content. See MixedStreamSEIContentMode{@link #MixedStreamSEIContentMode}.
     */
    MixedStreamSEIContentMode sei_content_mode = kMixedStreamSEIContentModeDefault;
    /**
     * @locale zh
     * @valid since 3.56
     * @brief SEI 信息的 payload type。<br>
     *        默认值为 `100`，只支持设置 `5` 和 `100`。<br>
     *        在转推直播的过程中，该参数不支持变更。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @brief SEI payload type.<br>
     *        The default value is `100`, and the value supported is `5` and `100`.<br>
     *        During the process of pushing streams to CDN, you cannot change the parameter.
     */
    int sei_payload_type = 100;
    /**
     * @locale zh
     * @valid since 3.56
     * @brief SEI 信息的 payload UUID。
     * @note PayloadType 为 `5` 时，必须填写 PayloadUUID，否则会收到错误回调，错误码为1091。  <br>
     *         PayloadType 不是 `5` 时，不需要填写 PayloadUUID，如果填写会被后端忽略。   <br>
     *         该参数长度需为32位，否则会收到错误码为1091的回调。  <br>
     *         该参数每个字符的范围需为 [0, 9] [a, f] [A, F] <br>
     *         该参数不应带有`-`字符，如系统自动生成的 UUID 中带有`-`，则应删去。<br>
     *         在转推直播的过程中，该参数不支持变更。
     */
     /**
     * @locale en
     * @valid since 3.56
     * @brief SEI payload UUID.
     * @note When PayloadType is `5`, you must set PayloadUUID, or you will receive a callback indicating parameter error. The error code is 1091. <br>
     *        When PayloadType is not `5`, it is not required to set PayloadUUID. If filled, it will be ignored by the backend. <br>
     *        The length of PayloadUUID should be 32 bits, or you will receive an error code of 1091.  <br>
     *        Each character of the parameter should be within the range of [0, 9] [a, f] [A, F].  <br>
     *        The PayloadUUID should not contain `-`. If the automatically generated UUID contains `-`, you should delete it. <br>
     *        During the process of pushing streams to CDN, you cannot change the parameter.
     */
     const char* sei_payload_uuid = nullptr;
     /**
      * @locale zh
      * @valid since 3.57
      * @brief 设置合流推到 CDN 时输出的媒体流类型。参看 MixedStreamMediaType{@link #MixedStreamMediaType}。<br>
      *        默认输出音视频流。支持输出纯音频流，但暂不支持输出纯视频流。
      */
     /**
      * @locale en
      * @brief Sets the type of media stream pushed to CDN after being mixed. MixedStreamMediaType{@link #MixedStreamMediaType}.<br>
      *        The default value is 0，which means pushing both audio and video.<br>
      *        Pushing video only is not supported currently.
      */
     MixedStreamMediaType media_type = MixedStreamMediaType::kMixedStreamMediaTypeAudioAndVideo;
     /**
      * @locale zh
      * @valid since 3.57
      * @brief 设置是否在没有用户发布流的情况下发起转推直播。具体参看 MixedStreamPushMode{@link #MixedStreamPushMode}。<br>
      *        该参数在发起合流任务后的转推直播过程中不支持动态变更。
      */
     /**
      * @locale en
      * @brief Sets whether to initiate a stream mixing task in the absence of any users publishing streams. See MixedStreamPushMode{@link #MixedStreamPushMode}.<br>
      *        Once the stream mixing task is initiated, this parameter can not be updated any more.
      */
     MixedStreamPushMode push_stream_mode = MixedStreamPushMode::kMixedStreamPushModeOnStream;
} MixedStreamServerControlConfig;

/**
 * @locale zh
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息。(新)<br>
 *        开启合流功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 */
/**
 * @locale en
 * @type keytype
 * @brief Layout information for one of the video streams to be mixed.(New)<br>
 *        After starting to push streams to CDN and mixing multiple video streams, you can set the layout information for each of them.
 */
typedef struct MixedStreamLayoutRegionConfig {
    /**
     * @locale zh
     * @brief 合流用户的 ID。建议设置。
     */
    /**
     * @locale en
     * @brief The user ID of the user who publishes the video stream. It's recommended to be set.
     */
    const char* region_id = nullptr;
   /**
     * @locale zh
     * @brief 图片或视频流所在房间的房间 ID。建议设置。<br>
     *        如果此图片或视频流是通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
     */
    /**
     * @locale en
     * @brief The room ID of the media stream. It's recommended to be set. <br>
     *        If the media stream is the stream forwarded by startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}, you must set the roomID to the room ID of the target room.
     */
    const char* room_id = nullptr;
    /**
     * @locale zh
     * @brief 单个用户画面左上角在整个画布坐标系中的 X 坐标（pixel），即以画布左上角为原点，用户画面左上角相对于原点的横向位移。<br>
     *        取值范围为 [0, 整体画布宽度)。默认值为 0。
     */
    /**
     * @locale en
     * @brief The X-coordinate in pixels of the upper-left corner of the user's frame in the entire canvas coordinate system, where the origin is at the upper-left corner of the canvas. It represents the horizontal displacement of the upper-left corner of the user's frame relative to the origin.<br>
     *        The value range is [0, the width of the canvas). The default value is 0.
     */
    int location_x = 0;
    /**
     * @locale zh
     * @brief 单个用户画面左上角在整个画布坐标系中的 Y 坐标（pixel），即以画布左上角为原点，用户画面左上角相对于原点的纵向位移。<br>
     *        取值范围为 [0, 整体画布高度)。默认值为 0。
     */
    /**
     * @locale en
     * @brief The Y-coordinate in pixels of the upper-left corner of the user's frame in the entire canvas coordinate system, where the origin is at the upper-left corner of the canvas. It represents the vertical displacement of the upper-left corner of the user's frame relative to the origin.<br>
     *        The value range is [0, the height of the canvas). The default value is 0.
     */
    int location_y = 0;
    /**
     * @locale zh
     * @brief 单个用户画面的宽度。取值范围为 [0, 整体画布宽度]，默认值为 360。
     */
    /**
     * @locale en
     * @brief The width of the user's frame in pixels. The value range is [0, the width of the canvas]. The default value is 360.
     */
    int width = MIXED_STREAM_VIDEO_DEFAULT_WIDTH;
    /**
     * @locale zh
     * @brief 单个用户画面的高度。取值范围为 [0, 整体画布高度]，默认值为 640。
     */
    /**
     * @locale en
     * @brief The heigh of the user's frame in pixels. The value range is [0, the height of the canvas]. The default value is 640.
     */
    int height = MIXED_STREAM_DEFAULT_VIDEO_HEIGHT;
    /**
     * @locale zh
     * @brief 透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。
     */
    /**
     * @locale en
     * @brief The opacity in range of (0.0, 1.0]. The lower value, the more transparent. The default value is 1.0.
     */
    float alpha = 1.0f;
    /**
     * @locale zh
     * @brief 圆角半径相对画布宽度的比例。默认值为 `0.0`。
     * @note 做范围判定时，首先根据画布的宽高，将 `width`，`height`，和 `corner_radius` 分别转换为像素值：`width_px`，`height_px`，和 `corner_radius_px`。然后判定是否满足 `corner_radius_px < min(width_px/2, height_px/2)`：若满足，则设置成功；若不满足，则将 `corner_radius_px` 设定为 `min(width_px/2, height_px/2)`，然后将 `corner_radius` 设定为 `corner_radius_px` 相对画布宽度的比例值。
     */
    /**
     * @locale en
     * @brief The proportion of the radius to the width of the canvas. `0.0` by default.
     * @note After you set the value, `width_px`, `height_px`, and `corner_radius_px` are calculated based on `width`, `height`, `corner_radius`, and the width of the canvas. If `corner_radius_px < min(width_px/2, height_px/2)` is met, the value of `corner_radius` is set valid; if not, `corner_radius_px` is set to `min(width_px/2, height_px/2)`, and `corner_radius` is set to the proportion of `corner_radius_px` to the width of the canvas.
     */
    float corner_radius = 0;

    /**
     * @locale zh
     * @brief 用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。
     */
    /**
     * @locale en
     * @brief The layer on which the video is rendered. The range is [0, 100]. 0 for the bottom layer, and 100 for the top layer. The default value is 0.
     */
    int32_t z_order = 0;
    /**
     * @locale zh
     * @brief 是否为本地用户：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    /**
     * @locale en
     * @brief Whether the source user of the stream is a local user:   <br>
     *         + True: Yes <br>
     *         + False: No
     */
    bool is_local_user = false;
    /**
     * @locale zh
     * @brief 是否为屏幕流：  
     */
    /**
     * @locale en
     * @brief Whether the stream comes from screen sharing:   
     */
    MixedStreamVideoType stream_type = MixedStreamVideoType::kMixedStreamVideoTypeMain;
    /**
     * @locale zh
     * @brief 合流内容控制。默认值为 `kMediaTypeAudioAndVideo`，参看 MixedStreamMediaType{@link #MixedStreamMediaType}。
     */
    /**
     * @locale en
     * @brief The stream mixing content type. The default value is `kMediaTypeAudioAndVideo`. See MixedStreamMediaType{@link #MixedStreamMediaType}.
     */
    MixedStreamMediaType media_type = MixedStreamMediaType::kMixedStreamMediaTypeAudioAndVideo;
    /**
     * @locale zh
     * @brief 图片或视频流的缩放模式，参看 MixedStreamRenderMode{@link #MixedStreamRenderMode}。默认值为 1。建议设置。
     */
    /**
     * @locale en
     * @brief The render mode. See MixedStreamRenderMode{@link #MixedStreamRenderMode}. The default value is 1. It's recommended to be set.
     */
    MixedStreamRenderMode render_mode = MixedStreamRenderMode::kMixedStreamRenderModeHidden;
    /**
     * @locale zh
     * @type keytype
     * @brief 合流布局区域类型，参看 MixedStreamLayoutRegionType{@link #MixedStreamLayoutRegionType}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief  Stream mixing region type. See MixedStreamLayoutRegionType{@link #MixedStreamLayoutRegionType}.
     */
    MixedStreamLayoutRegionType region_content_type = MixedStreamLayoutRegionType::  kMixedStreamLayoutRegionTypeVideoStream;
    /**
     * @locale zh
     * @type keytype
     * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
     */
    /**
     * @locale en
     * @type keytype
     * @brief The RGBA data of the mixing image. Put in null when mixing video streams.
     */
    uint8_t* image_water_mark = nullptr;
    /**
     * @locale zh
     * @type keytype
     * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 MixedStreamLayoutRegionImageWaterMarkConfig{@link #MixedStreamLayoutRegionImageWaterMarkConfig}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief  Image parameters for stream mixing. See MixedStreamLayoutRegionImageWaterMarkConfig{@link #MixedStreamLayoutRegionImageWaterMarkConfig}. Put in null when mixing video streams.
     */
    MixedStreamLayoutRegionImageWaterMarkConfig image_water_mark_param;
    /**
     * @locale zh
     * @valid since 3.57
     * @brief 设置占位图的填充模式。<br>
     *        该参数用来控制当用户停止发布视频流，画面恢复为占位图后，此时占位图的填充模式。参看 MixedStreamAlternateImageFillMode{@link #MixedStreamAlternateImageFillMode}。
     */
    /**
     * @locale en
     * @brief Sets the fill mode of the placeholder image.<br>
     *        This parameter is used to control the fill mode of the placeholder image after the user stops publishing video streams and the screen reverts to the placeholder image. See MixedStreamAlternateImageFillMode{@link #MixedStreamAlternateImageFillMode}.
     */
    MixedStreamAlternateImageFillMode alternate_image_fill_mode = kMixedStreamAlternateImageFillModeFit;
    /**
     * @locale zh
     * @valid since 3.57
     * @brief 设置占位图的 URL，长度小于 1024 字符.
     */
    /**
     * @locale en
     * @brief Sets the URL of the placeholder image, limited to a maximum of 1024 characters.
     */
    const char* alternate_image_url = nullptr;
    /**
     * @locale zh
     * @type keytype
     * @brief 空间位置。参看 Position{@link #Position}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief spatial position. See Position{@link #Position}.
     */
    Position spatial_position;
    
    bool apply_spatial_audio = true;
    
} MixedStreamLayoutRegionConfig;

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamType{@link #MixedStreamType} instead.
 * @type keytype
 * @brief 合流类型
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamType{@link #MixedStreamType} instead.
 * @type keytype
 * @brief Stream mixing type
 */
enum StreamMixingType {
    /**
     * @locale zh
     * @brief 服务端合流。
     */
    /**
     * @locale en
     * @brief Mix media streams on the server side.
     */
    kStreamMixingTypeByServer = 0,
    /**
     * @locale zh
     * @brief 端云一体合流。SDK 智能决策在客户端或服务端完成合流。
     */
    /**
     * @locale en
     * @brief Intelligent stream mixing. The SDK will intelligently decide that a stream mixing task would be done on the client or the server.
     */
    kStreamMixingTypeByClient = 1,
};


/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamAudioProfile{@link #MixedStreamAudioProfile} instead.
 * @type keytype
 * @brief AAC 编码规格。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamAudioProfile{@link #MixedStreamAudioProfile} instead.
 * @type keytype
 * @brief Advanced Audio Coding (AAC) profile.
 */
enum TranscoderAudioCodecProfile {
    /**
     * @locale zh
     * @brief AAC-LC 规格，默认值。
     */
    /**
     * @locale en
     * @brief (Default) AAC Low-Complexity profile (AAC-LC).
     */
    kByteAACProfileLC = 0,
    /**
     * @locale zh
     * @brief HE-AAC v1 规格。
     */
    /**
     * @locale en
     * @brief HE-AAC v1 profile (AAC LC with SBR).
     */
    kByteAACProfileHEv1 = 1,
    /**
     * @locale zh
     * @brief HE-AAC v2 规格。
     */
    /**
     * @locale en
     * @brief HE-AAC v2 profile (AAC LC with SBR and Parametric Stereo).
     */
    kByteAACProfileHEv2 = 2,
};

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamAudioCodecType{@link #MixedStreamAudioCodecType} instead.
 * @type keytype
 * @brief 音频编码格式。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamAudioCodecType{@link #MixedStreamAudioCodecType} instead.
 * @type keytype
 * @brief The audio codec.
 */
enum TranscoderAudioCodecType {
    /**
     * @locale zh
     * @brief AAC 格式。
     */
    /**
     * @locale en
     * @brief AAC format.
     */
    kTranscodeAudioCodecAAC = 0,
};

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamVideoCodecType{@link #MixedStreamVideoCodecType} instead.
 * @type keytype
 * @brief 视频编码格式。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamVideoCodecType{@link #MixedStreamVideoCodecType} instead.
 * @type keytype
 * @brief The video codec.
 */
enum TranscoderVideoCodecType {
    /**
     * @locale zh
     * @brief H.264 格式，默认值。
     */
    /**
     * @locale en
     * @brief (Default) H.264 format.
     */
    kTranscodeVideoCodecH264 = 0,
    /**
     * @locale zh
     * @brief ByteVC1 格式。
     */
    /**
     * @locale en
     * @brief ByteVC1 format.
     */
    kTranscodeVideoCodecH265 = 1,
};

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamRenderMode{@link #MixedStreamRenderMode} instead.
 * @type keytype
 * @brief 图片或视频流的缩放模式。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamRenderMode{@link #MixedStreamRenderMode} instead.
 * @type keytype
 * @brief The render mode.
 */
enum TranscoderRenderMode {
    /**
     * @locale zh
     * @deprecated since 3.45 and will be deleted in 3.51.
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51.
     */
    kRenderUnknown = 0,
    /**
     * @locale zh
     * @brief 视窗填满优先，默认值。<br>
     *        视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    /**
     * @locale en
     * @brief (Default) Fill and Crop.<br>
     *        The video frame is scaled with fixed aspect ratio, until it completely fills the canvas. The region of the video exceeding the canvas will be cropped.
     */
    kRenderHidden = 1,
    /**
     * @locale zh
     * @brief 视频帧内容全部显示优先。<br>
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。
     */
    /**
     * @locale en
     * @brief Fit.<br>
     *        The video frame is scaled with fixed aspect ratio, until it fits just within the canvas. Other part of the canvas is filled with the background color.
     */
    kRenderFit = 2,
    /**
     * @locale zh
     * @brief 视频帧自适应画布。<br>
     *        视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
    /**
     * @locale en
     * @brief Fill the canvas.<br>
     *        The video frame is scaled to fill the canvas. During the process, the aspect ratio may change.
     */
    kRenderAdaptive = 3,
};

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamLayoutRegionType{@link #MixedStreamLayoutRegionType} instead.
 * @type keytype
 * @brief 合流布局区域类型
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamLayoutRegionType{@link #MixedStreamLayoutRegionType} instead.
 * @type keytype
 * @brief Stream mixing region type
 */
enum TranscoderLayoutRegionType {
    /**
     * @locale zh
     * @brief 合流布局区域类型为视频。
     */
    /**
     * @locale en
     * @brief The region type is a video stream.
     */
    kLayoutRegionTypeVideoStream = 0,
    /**
     * @locale zh
     * @brief 合流布局区域类型为图片。
     */
    /**
     * @locale en
     * @brief The region type is an image.
     */
    kLayoutRegionTypeImage = 1,
};

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamLayoutRegionImageWaterMarkConfig{@link #MixedStreamLayoutRegionImageWaterMarkConfig} instead.
 * @type keytype
 * @brief 图片合流相关参数
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamLayoutRegionImageWaterMarkConfig{@link #MixedStreamLayoutRegionImageWaterMarkConfig} instead.
 * @type keytype
 * @brief  Image parameters for stream mixing
 */
typedef struct TranscoderLayoutRegionDataParam {
    /**
     * @locale zh
     * @brief 原始图片的宽度，单位为 px。
     */
    /**
     * @locale en
     * @brief Width of the original image in px.
     */
    int image_width = 0;
    /**
     * @locale zh
     * @brief 原始图片的高度，单位为 px。
     */
    /**
     * @locale en
     * @brief Height of the original image in px.
     */
    int image_height = 0;
}TranscoderLayoutRegionDataParam;

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamClientMixVideoFormat{@link #MixedStreamClientMixVideoFormat} instead.
 * @type keytype
 * @brief 客户端合流回调视频格式。设置为系统不支持的格式时，自动回调系统默认格式。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamClientMixVideoFormat{@link #MixedStreamClientMixVideoFormat} instead.
 * @type keytype
 * @brief The video format for client stream mixing callback. If the format you set is not adaptable to the system, the format will be set as the default value.
 */
enum TranscoderClientMixVideoFormat {
    /**
     * @locale zh
     * @brief YUV I420。Android、Windows 默认回调格式。支持系统：Android、Windows。
     */
    /**
     * @locale en
     * @brief YUV I420 format. The default format for Android and Windows. Supported system: Android, Windows.
     */
    kClientMixVideoFormatI420 = 0,
    /**
     * @locale zh
     * @brief OpenGL GL_TEXTURE_2D 格式纹理。支持系统：安卓。
     */
    /**
     * @locale en
     * @brief OpenGL GL_TEXTURE_2D format. Supported system: Android.
     */
    kClientMixVideoFormatTexture2D = 1,
    /**
     * @locale zh
     * @brief CVPixelBuffer BGRA。iOS 默认回调格式。支持系统: iOS。
     */
    /**
     * @locale en
     * @brief CVPixelBuffer BGRA format. The default format for iOS. support system: iOS.
     */
    kClientMixVideoFormatCVPixelBufferBGRA = 2,
    /**
     * @locale zh
     * @brief YUV NV12。macOS 默认回调格式。支持系统: macOS。
     */
    /**
     * @locale en
     * @brief YUV NV12 format. The default format for macOS. Supported system: macOS.
     */
    kClientMixVideoFormatNV12 = 3,
};
/**
 * @locale zh
 * @type keytype
 * @brief 数据帧类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Data frame type
 */
enum DataFrameType {
    /**
     * @locale zh
     * @brief SEI 视频帧
     */
    /**
     * @locale en
     * @brief SEI  video frame
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
 * @locale zh
 * @type keytype
 * @brief 数据帧
 */
/**
 * @locale en
 * @type keytype
 * @brief  Data frame
 */
typedef struct IDataFrame {
    /**
     * @locale zh
     * @brief 数据帧类型，参看 DataFrameType{@link #DataFrameType}
     */
    /**
     * @locale en
     * @brief Data frame type. See DataFrameType{@link #DataFrameType}
     */
    DataFrameType frame_type = kDataFrameTypeSei;
    /**
     * @locale zh
     * @brief 数据帧数据
     */
    /**
     * @locale en
     * @brief Data frame data
     */
    uint8_t* u8_data = nullptr;
    /**
     * @locale zh
     * @brief 数据帧数据大小
     */
    /**
     * @locale en
     * @brief Data frame data size
     */
    uint32_t u32_data_size = 0;
    /**
     * @locale zh
     * @brief 数据帧时间戳，单位：微秒
     */
    /**
     * @locale en
     * @brief Data frame timestamp in microseconds
     */
    uint64_t u64_ts_us = 0;
} IDataFrame;

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} instead.
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息。<br>
 *        开启转推直播功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} instead.
 * @type keytype
 * @brief Layout information for one of the video streams to be mixed.<br>
 *        After starting to push streams to CDN and mixing multiple video streams, you can set the layout information for each of them.
 */
typedef struct TranscoderLayoutRegion {
    /**
     * @locale zh
     * @brief 合流用户的 ID。必填。
     */
    /**
     * @locale en
     * @brief The user ID of the user who publishes the video stream. Required.
     */
    const char* region_id = nullptr;
   /**
     * @locale zh
     * @brief 图片或视频流所在房间的房间 ID。必填。<br>
     *        如果此图片或视频流是通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
     */
    /**
     * @locale en
     * @brief The room ID of the media stream. Required. <br>
     *        If the media stream is the stream forwarded by startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}, you must set the roomID to the room ID of the target room.
     */
    const char* room_id = nullptr;
    /**
     * @locale zh
     * @brief 视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
     */
    /**
     * @locale en
     * @brief The normalized horizontal coordinate value of the top left end vertex of the user's view, ranging within [0.0, 1.0). The default value is 0.0.
     */
    float x = 0.0f;
    /**
     * @locale zh
     * @brief 视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
     */
    /**
     * @locale en
     * @brief The normalized vertical coordinate value of the top left end vertex of the user's view, ranging within [0.0, 1.0). The default value is 0.0.
     */
    float y = 0.0f;
    /**
     * @locale zh
     * @brief 视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
     */
    /**
     * @locale en
     * @brief The normalized width of the user's view, ranging within [0.0, 1.0]. The default value is 1.0.
     */
    float width = 1.0f;
    /**
     * @locale zh
     * @brief 视频流对应区域高度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
     */
    /**
     * @locale en
     * @brief The normalized height of the user's view, ranging within [0.0, 1.0]. The default value is 1.0.
     */
    float height = 1.0f;
    /**
     * @locale zh
     * @brief （仅服务端合流支持设置）透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。
     */
    /**
     * @locale en
     * @brief (Only server-side stream mixing can set this parameter.) The opacity in range of (0.0, 1.0]. The lower value, the more transparent. The default value is 1.0.
     */
    float alpha = 1.0f;
    /**
     * @locale zh
     * @brief （仅服务端合流支持设置）圆角半径相对画布宽度的比例。默认值为 `0.0`。
     * @note 做范围判定时，首先根据画布的宽高，将 `width`，`height`，和 `corner_radius` 分别转换为像素值：`width_px`，`height_px`，和 `corner_radius_px`。然后判定是否满足 `corner_radius_px < min(width_px/2, height_px/2)`：若满足，则设置成功；若不满足，则将 `corner_radius_px` 设定为 `min(width_px/2, height_px/2)`，然后将 `corner_radius` 设定为 `corner_radius_px` 相对画布宽度的比例值。
     */
    /**
     * @locale en
     * @brief (Only server-side stream mixing can set this parameter.) The proportion of the radius to the width of the canvas. The default value is 0.0.
     * @note After you set the value, `width_px`, `height_px`, and `corner_radius_px` are calculated based on `width`, `height`, `corner_radius`, and the width of the canvas. If `corner_radius_px < min(width_px/2, height_px/2)` is met, the value of `corner_radius` is set valid; if not, `corner_radius_px` is set to `min(width_px/2, height_px/2)`, and `corner_radius` is set to the proportion of `corner_radius_px` to the width of the canvas.
     */
    float corner_radius = 0;

    /**
     * @locale zh
     * @brief 用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。
     */
    /**
     * @locale en
     * @brief The layer on which the video is rendered. The range is [0, 100]. 0 for the bottom layer, and 100 for the top layer. The default value is 0.
     */
    int32_t i32_z_order = 0;
    /**
     * @locale zh
     * @brief 是否为本地用户：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    /**
     * @locale en
     * @brief Whether the source user of the stream is a local user:   <br>
     *         + true: Yes <br>
     *         + false: No
     */
    bool local_user = false;
    /**
     * @locale zh
     * @brief （仅服务端合流支持合屏幕流）是否为屏幕流：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    /**
     * @locale en
     * @brief (Only server-side stream mixing can set this parameter to true.) Whether the stream comes from screen sharing:   <br>
     *         + true: Yes <br>
     *         + false: No
     */
    bool screen_stream = false;
    /**
     * @locale zh
     * @brief （仅服务端合流支持设置）合流内容控制。默认值为 `kHasAudioAndVideo`，参看 TranscoderContentControlType{@link #TranscoderContentControlType}。
     */
    /**
     * @locale en
     * @brief (Only server-side stream mixing can set this parameter.) The stream mixing content type. The default value is `kHasAudioAndVideo`. See TranscoderContentControlType{@link #TranscoderContentControlType}.
     */
    TranscoderContentControlType content_control = TranscoderContentControlType::kHasAudioAndVideo;
    /**
     * @locale zh
     * @brief 图片或视频流的缩放模式，参看 TranscoderRenderMode{@link #TranscoderRenderMode}。默认值为 1。
     */
    /**
     * @locale en
     * @brief The render mode. See TranscoderRenderMode{@link #TranscoderRenderMode}. The default value is 1.
     */
    TranscoderRenderMode render_mode = kRenderHidden;
    /**
     * @locale zh
     * @type keytype
     * @brief 合流布局区域类型，参看 TranscoderLayoutRegionType{@link #TranscoderLayoutRegionType}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief  Stream mixing region type. See TranscoderLayoutRegionType{@link #TranscoderLayoutRegionType}.
     */
    TranscoderLayoutRegionType type = kLayoutRegionTypeVideoStream;
    /**
     * @locale zh
     * @type keytype
     * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
     */
    /**
     * @locale en
     * @type keytype
     * @brief The RGBA data of the mixing image. Put in null when mixing video streams.
     */
    uint8_t* data = nullptr;
    /**
     * @locale zh
     * @type keytype
     * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 TranscoderLayoutRegionDataParam{@link #TranscoderLayoutRegionDataParam}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief  Image parameters for stream mixing. See TranscoderLayoutRegionDataParam{@link #TranscoderLayoutRegionDataParam}. Put in null when mixing video streams.
     */
    TranscoderLayoutRegionDataParam data_param;
    /**
     * @locale zh
     * @type keytype
     * @brief 空间位置。参看 Position{@link #Position}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief spatial position. See Position{@link #Position}.
     */
    Position spatial_position;

    bool apply_spatial_audio = true;

} TranscoderLayoutRegion;

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamAudioConfig{@link #MixedStreamAudioConfig} instead.
 *  @type keytype
 *  @brief 音频转码配置参数。值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamAudioConfig{@link #MixedStreamAudioConfig} instead.
 *  @type keytype
 *  @brief Audio transcoding configurations. With invalid or empty input, the configurations will be set as the default values.
 */
typedef struct TranscoderAudioParam {
    /**
     * @locale zh
     * @brief 音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。
     */
    /**
     * @locale en
     * @brief The sample rate (Hz). Supported sample rates: 32,00 Hz, 44,100 Hz, 48,000 Hz. Defaults to 48,000 Hz.
     */
    int32_t i32_sample_rate = 48000;
    /**
     * @locale zh
     * @brief 音频声道数。可取 1（单声道）、2（双声道），默认值为 2。
     */
    /**
     * @locale en
     * @brief The number of channels. Supported channels: 1 (single channel), 2 (dual channel).  Defaults to 2.
     */
    int32_t i32_channel_num = 2;
    /**
     * @locale zh
     * @brief 音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。
     */
    /**
     * @locale en
     * @brief The bitrate (Kbps) in range of [32, 192]. Defaults to 64 Kbps.
     */
    int32_t i32_bitrate_kbps = 64;
    /**
     * @locale zh
     * @brief AAC 编码规格，参看 TranscoderAudioCodecProfile{@link #TranscoderAudioCodecProfile}。默认值为 `0`。
     */
    /**
     * @locale en
     * @brief AAC profile. See TranscoderAudioCodecProfile{@link #TranscoderAudioCodecProfile}. Defaults to `0`.
     */
    TranscoderAudioCodecProfile audio_codec_profile = kByteAACProfileLC;
    /**
     * @locale zh
     * @brief 音频编码格式，参看 TranscoderAudioCodecType{@link #TranscoderAudioCodecType}。默认值为 `0`。
     */
    /**
     * @locale en
     * @brief AAC profile. See TranscoderAudioCodecType{@link #TranscoderAudioCodecType}. Defaults to `0`.
     */
    TranscoderAudioCodecType audio_codec_type = kTranscodeAudioCodecAAC;
} TranscoderAudioParam;

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamVideoConfig{@link #MixedStreamVideoConfig} instead.
 * @type keytype
 * @brief 视频转码配置参数。值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamVideoConfig{@link #MixedStreamVideoConfig} instead.
 * @type keytype
 * @brief Video transcoding configurations. With invalid or empty input, the configurations will be set as the default values.
 */
typedef struct TranscoderVideoParam {
    /**
     * @locale zh
     * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。<br>
     *        设置值为非偶数时，自动向上取偶数。
     */
    /**
     * @locale en
     * @brief The width (pixels) to be set. The range is [2, 1920], and must be an even number. The default value is 360 pixels.<br>
     *        If an odd number is set, the width will be adjusted to the next larger even number.
     */
    int32_t i32_width = 360;
    /**
     * @locale zh
     * @brief 合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。<br>
     *        设置值为非偶数时，自动向上取偶数。
     */
    /**
     * @locale en
     * @brief The height (pixels) to be set. The range is [2, 1920], and must be an even number. The default value is 640 pixels.<br>
     *        If an odd number is set, the height will be adjusted to the next larger even number.
     */
    int32_t i32_height = 640;
    /**
     * @locale zh
     * @brief 合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。
     */
    /**
     * @locale en
     * @brief The frame rate (FPS) in range of [1, 60]. The default value is 15 FPS.
     */
    int32_t i32_fps = 15;
    /**
     * @locale zh
     * @brief 视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。<br>
     *        本参数不支持过程中更新。
     */
    /**
     * @locale en
     * @brief The time interval between I-frames (second) in range of [1, 5]. The default value is 2 seconds.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     */
    int32_t i32_gop = 2;
    /**
     * @locale zh
     * @brief 合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。
     */
    /**
     * @locale en
     * @brief The bitrate (Kbps) in range of [1, 10000]. The default value is self-adaptive.
     */
    int32_t i32_bitrate_kbps = 500;
    /**
     * @locale zh
     * @brief 视频编码格式，参看 TranscoderVideoCodecType{@link #TranscoderVideoCodecType}。默认值为 `0`。<br>
     *        本参数不支持过程中更新。
     */
    /**
     * @locale en
     * @brief The video codec. See TranscoderVideoCodecType{@link #TranscoderVideoCodecType}. The default value is `0`.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     */
    TranscoderVideoCodecType video_codec_type = kTranscodeVideoCodecH264;
    /**
      * @locale zh
      * @brief 是否在合流中开启B帧，仅服务端合流支持：  <br>
      *        + true: 是  <br>
      *        + false: 否
      */
     /**
      * @locale en
      * @brief Whether to push streams with B frame, only support by server mix:   <br>
      *         + true: Yes <br>
      *         + false: No
      */
    bool bFrame = false;
} TranscoderVideoParam;

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamSyncControlConfig instead.
 * @hidden internal use only
 * @valid since 3.50
 * @type keytype
 * @brief 转推直播单通同步参数。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamSyncControlConfig instead.
 * @hidden internal use only
 * @valid since 3.50
 * @type keytype
 * @brief Parameters of simplex mode and synchronization when pushing to CDN.
 */
typedef struct TranscoderSyncControlParam {
    /**
     * @locale zh
     * @brief 是否在转推直播时，启用单通模式。默认为 false，不启用。<br>
     *        启用单通模式时，RTC SDK 会对指定的多个用户的媒体流进行同步处理，再合流后推送到 CDN，但基准流所属用户不会播放来自其他用户的媒体流。你需要设定以下参数。<br>
     *        非单通模式时，RTC SDK 不会对媒体流进行同步处理，只是简单合流后推送到 CDN。以下参数设定无效。
     */
    /**
     * @locale en
     * @brief Whether to enable simplex mode during pushing to CDN. False(duplex mode) by default.<br>
     *        When simplex mode is enabled, RTC SDK synchronizes and transcodes the media streams from the local user and several remote users, and pushing the mixed stream to CDN. `syncBaseUser` does not play the streams from the remote users. You must set the following parameters.<br>
     *        When duplex mode is enabled, RTC SDK transcodes the media streams from the local user and several remote users without synchronization, and pushing the mixed stream to CDN. The following parameters are not effective.
     */
     bool sync_stream = false;
    /**
    * @locale zh
    * @hidden
    */
    /**
     * @locale en
     * @hidden
     */
     MixedStreamSyncStrategy sync_strategy = MixedStreamSyncStrategy::kMixedStreamSyncStrategyNoSync;
    /**
     * @locale zh
     * @brief 在进行同步处理时，基准流所属用户的 ID。默认为空。
     */
    /**
     * @locale en
     * @brief User ID of the base stream during syncing. Null by default.
     */
    const char* sync_base_user = nullptr;
    /**
     * @locale zh
     * @brief 在进行同步处理时，缓存音视频流的最大长度。单位为毫秒。默认值为 0。
     * @note 参与转推直播的这些媒体流延迟越高，应该将此值设置的越大。但此值越大，因缓存媒体流造成的内存占用也会更大。推荐值为 `2000`。
     */
    /**
     * @locale en
     * @brief The max length of the cached stream in milliseconds. 0 by default.
     * @note Set the value based on the stall of the media streams. Higher the value, bigger the memory usage. The recommended value is `2000`.
     */
    int32_t sync_queue_length_ms = 0;
    /**
     * @locale zh
     * @brief 是否通过 RTC SDK 进行转推直播。默认为 True。<br>
     *        如果选择 `False`，你会通过 onCacheSyncVideoFrames{@link #ITranscoderObserver#onCacheSyncVideoFrames} 收到同步的帧，你可以使用此视频帧，自行实现合流转推。
     */
    /**
     * @locale en
     * @brief Whether to use RTC SDK to push to CDN. True by default.<br>
     *        If `False`, you can get the media frames by onCacheSyncVideoFrames{@link #ITranscoderObserver#onCacheSyncVideoFrames} and manually push them to CDN.
     */
    bool sync_client_video_need_mix = true;
    /**
     * @locale zh
     * @brief 是否只开启时间戳发送而不做对齐和媒体数据回调。默认为 False。<br>
     *        在单通合唱双人场景下，主唱应设置为 False，副唱应设置为 True。<br>
     *        在单通合唱多人场景下，主唱和所有副唱都应设置为 False。
     */
    /**
     * @locale en
     * @brief Whether only send cache sync pts and not start sync and callback data. False by default.<br>
     *        In the simplex chorus scene of two people, the lead singer should set to False, and the sub-singer should set to True.<br>
     *        In the duplex chorus scene of two people, all the singers should set to False.
     */
    bool sync_only_send_pts = false;
} TranscoderSyncControlParam;

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig} instead.
 * @type keytype
 * @brief 客户端合流参数。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig} instead.
 * @type keytype
 * @brief Configurations for mixing and pushing to CDN at client side.
 */
typedef struct TranscoderClientMixParam {
    /**
     * @locale zh
     * @brief 是否使用原始视频帧。默认为 False。
     */
    /**
     * @locale en
     * @brief Whether to use original video frames. False by default.
     */
    bool client_mix_use_original_frame = false;
    /**
     * @locale zh
     * @brief 客户端合流是否使用音频混音，默认为 true。
     */
    /**
     * @locale en
     * @brief Whether to use audio mixing. True by default.
     */
    bool client_mix_use_audio_mixer = true;
    /**
     * @locale zh
     * @brief 客户端合流回调视频格式，参看 TranscoderClientMixVideoFormat{@link #TranscoderClientMixVideoFormat}。
     */
    /**
     * @locale en
     * @brief The video format to be set. See TranscoderClientMixVideoFormat{@link #TranscoderClientMixVideoFormat}.
     */
    TranscoderClientMixVideoFormat client_mix_video_format_;
} TranscoderClientMixParam;

/**
 * @locale zh
 * @deprecated since 3.52, use MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig} instead.
 * @type keytype
 * @brief 推流 CDN 的空间音频参数。
 */
/**
 * @locale en
 * @deprecated since 3.52, use MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig} instead.
 * @type keytype
 * @brief Spatial audio config when pushing to CDN.
 */
typedef struct TranscoderSpatialConfig {
    /**
     * @locale zh
     * @brief 是否开启推流 CDN 时的空间音频效果。
     * @note 当你启用此效果时，你需要设定推流中各个 TranscoderLayoutRegion{@link #TranscoderLayoutRegion} 的 `spatial_position` 值，实现空间音频效果。
     */
    /**
     * @locale en
     * @brief Whether to enable the spatial audio effect when pushing to CDN.
     * @note when you enable the feature, set the `spatial_position` of each TranscoderLayoutRegion{@link #TranscoderLayoutRegion} for spatial audio effect.
     */
    bool enable_spatial_render;
    /**
     * @locale zh
     * @brief 听众的空间位置。参看 Position{@link #Position}。<br>
     *        听众指收听来自 CDN 的音频流的用户。
     */
    /**
     * @locale en
     * @brief The spatial position of the audience. See Position{@link #Position}. <br>
     *        The audience is the users who receive the audio stream from CDN.
     */
    Position audience_spatial_position;
    /**
     * @locale zh
     * @brief 听众的空间朝向。参看 HumanOrientation{@link #HumanOrientation}。<br>
     *        听众指收听来自 CDN 的音频流的用户。
     */
    /**
     * @locale en
     * @brief The orientation of the audience. See HumanOrientation{@link #HumanOrientation}. <br>
     *        The audience is the users who receive the audio stream from CDN.
     */
    HumanOrientation audience_spatial_orientation;
} TranscoderSpatialConfig;

/**
 * @locale zh
 * @deprecated since 3.52, use IMixedStreamConfig{@link #IMixedStreamConfig} instead.
 * @type keytype
 * @brief 转推直播配置参数。
 */
/**
 * @locale en
 * @deprecated since 3.52, use IMixedStreamConfig{@link #IMixedStreamConfig} instead.
 * @type keytype
 * @brief Configurations to be set when pushing media streams to CDN.
 */
class ITranscoderParam : public ITranscoderParamBase {
public:

    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取合流类型。
     * @return 合流类型，参看 StreamMixingType{@link #StreamMixingType}
     * @note 本参数不支持过程中更新。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Gets the stream mixing type.
     * @return Stream mixing type. See StreamMixingType{@link #StreamMixingType}
     * @note This parameter cannot be updated while pushing stream to the CDN.
     */
    virtual StreamMixingType expectedMixingType() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取推流用户 ID。
     * @return 推流用户 ID。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the user ID for live transcoding.
     * @return The user ID for live transcoding.
     */
    virtual const char* userID() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取推流 CDN 地址。
     * @return 推流地址。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the URL for live transcoding.
     * @return The CDN url.
     */
    virtual const char* uri() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取 SEI 信息。
     * @return SEI 信息。
     */
    /**
     * @locale en
     * @type api
     * @region Forward to live broadcast
     * @brief Get SEI information.
     * @return SEI Information.
     */
    virtual const char* appData() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取合流音频参数。
     * @return 合流音频参数内容，参看 TranscoderAudioParam{@link #TranscoderAudioParam}。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Gets the audio configurations.
     * @return Audio configurations. See TranscoderAudioParam{@link #TranscoderAudioParam}.
     */
    virtual TranscoderAudioParam audioParam() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取合流视频转码参数。
     * @return 合流视频转码参数内容，参看 TranscoderVideoParam{@link #TranscoderVideoParam}。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Gets the video configurations.
     * @return Video configurations. See TranscoderVideoParam{@link #TranscoderVideoParam}.
     */
    virtual TranscoderVideoParam videoParam() = 0;
    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 获取转推 CDN 时的空间音频参数。
     * @return 参看 TranscoderSpatialConfig{@link #TranscoderSpatialConfig}。
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief Get the spatial audio configurations of pushing to CDN.
     * @return See TranscoderSpatialConfig{@link #TranscoderSpatialConfig}.
     */
    virtual TranscoderSpatialConfig spatialConfig() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取合流视窗布局信息。
     * @param index 视窗对应下标。
     * @return 合流视窗布局信息，参看 TranscoderLayoutRegion{@link #TranscoderLayoutRegion}。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Gets the video layout information of the mixed stream.
     * @param index The number of the view of which you want to get information.
     * @return Layout information. See TranscoderLayoutRegion{@link #TranscoderLayoutRegion}.
     */
    virtual TranscoderLayoutRegion layoutRegionByIndex(int32_t index) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 获取动态扩展自定义参数
     * @return 动态扩展自定义参数
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region Forward to live broadcast
     * @brief Get dynamically extend customizable parameters
     * @return dynamically extend customizable parameters
     */
    virtual const char* advancedConfig() = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 获取业务透传鉴权信息
     * @return 业务透传鉴权信息
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region Forward to live broadcast
     * @brief Get Business Transparent Authentication Information
     * @return Business Transparent Authentication Information
     */
    virtual const char* authInfo() = 0;
    /**
     * @locale zh
     * @valid since 3.50
     * @type api
     * @brief 获取客户端合流信息。
     * @return 客户端合流信息，参看 TranscoderClientMixParam{@link #TranscoderClientMixParam}。
     */
    /**
     * @locale en
     * @valid since 3.50
     * @type api
     * @brief Get client mixing parameters.
     * @return Client mixing parameters. See TranscoderClientMixParam{@link #TranscoderClientMixParam}.
     */
    virtual TranscoderClientMixParam clientMixParam()  = 0;
    /**
     * @locale zh
     * @hidden internal use only
     * @valid since 3.50
     * @type api
     * @brief 获取转推直播单通同步参数。
     * @return 参看 TranscoderSyncControlParam{@link #TranscoderSyncControlParam}。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @valid since 3.50
     * @type api
     * @brief Get the parameters of simplex mode and synchronization when pushing to CDN.
     * @return See TranscoderSyncControlParam{@link #TranscoderSyncControlParam}.
     */
    virtual TranscoderSyncControlParam syncControlparam() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 设置合流类型。
     * @param expected_mix_type 合流类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Sets the expected stream mixing type
     * @param expected_mix_type Stream mixing type. See StreamMixingType{@link #StreamMixingType}
     */
    virtual void setExpectedMixingType(StreamMixingType expected_mix_type) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置推流用户 ID。`room_id` 和 `user_id` 长度相加不得超过 126 字节。<br>
     *        本参数不支持过程中更新。
     * @param user_id 推流用户 ID。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the user ID for live transcoding. The sum length of `room_id` and `user_id` should not exceed 126 bytes.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     * @param user_id The user ID for live transcoding.
     */
    virtual void setUserID(const char* user_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。<br>
     *        本参数不支持过程中更新。
     * @param uri 推流地址。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the URL for live transcoding. Only supports live transcoding via RTMP. The URL should match the regular expression `/^rtmps?:\/\//`.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     * @param uri The URL to be set.
     */
    virtual void setUri(const char* uri) = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 设置音频参数。参看 TranscoderAudioParam{@link #TranscoderAudioParam}。<br>
     *        本参数不支持过程中更新。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Sets audio configurations. See TranscoderAudioParam{@link #TranscoderAudioParam}.<br>
     *        This parameters cannot be updated while pushing stream to the CDN.
     */
    virtual void setAudioParam(const TranscoderAudioParam&) = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 设置视频参数。参看 TranscoderVideoParam{@link #TranscoderVideoParam}。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Sets video configurations. See TranscoderVideoParam{@link #TranscoderVideoParam}.
     */
    virtual void setVideoParam(const TranscoderVideoParam&) = 0;
    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 设定转推 CDN 时的空间音频效果。参看 TranscoderSpatialConfig{@link #TranscoderSpatialConfig}。
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief Sets spatial audio configurations. See TranscoderSpatialConfig{@link #TranscoderSpatialConfig}.
     */
    virtual void setSpatialConfig(const TranscoderSpatialConfig&) = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 设置视频流合流整体布局信息。
     * @param regions[] 用户布局信息列表。为 TranscoderLayoutRegion{@link #TranscoderLayoutRegion} 数据类型的数组。每一个该类型对象为一路单独的视频流的布局信息。<br>
     *                       值不合法或未设置时，自动使用默认值。
     * @param regions_size 合流视窗数量。
     * @param bg_color 合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。<br>
     *                      值不合法或未设置时，自动使用默认值。
     * @param app_data 透传的 App 数据，长度不超过 4 KB。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Sets the layout configurations.
     * @param regions[] User layout information list. It's a list of TranscoderLayoutRegion{@link #TranscoderLayoutRegion} that you construct for each stream.<br>
     *                       With invalid or empty input, the configurations will be set as the default values.
     * @param regions_size Amount of views.
     * @param bg_color Background-color of the mixed stream in hexadecimal values such as #FFFFFF and #000000. The default value is #000000.<br>
     *                      With invalid or empty input, the configurations will be set as the default values.
     * @param app_data Additional data that you want to import，up to 4KB in length.
     */
    virtual void setLayoutParam(
            TranscoderLayoutRegion regions[], int32_t regions_size, const char* bg_color, const char* app_data) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置动态扩展自定义参数
     * @param advanced_config 动态扩展自定义参数
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region  Forward to live broadcast
     * @brief Sets dynamically extend customizable parameters
     * @param advanced_config  dynamically extend customizable parameters
     */
    virtual void setAdvancedConfig(const char* advanced_config) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置业务透传鉴权信息
     * @param auth_info 业务透传鉴权信息
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region Forward to live broadcast
     * @brief Sets Business Transparent Authentication Information
     * @param auth_info  Business Transparent Authentication Information
     */
    virtual void setAuthInfo(const char* auth_info) = 0;
    /**
     * @locale zh
     * @hidden internal use only
     * @valid since 3.50
     * @type api
     * @brief 设置客户端合流信息。
     * @param param 参看 TranscoderClientMixParam{@link #TranscoderClientMixParam}。
     * @return 参看 TranscoderClientMixParam{@link #TranscoderClientMixParam}。
     */
    /**
     * @locale en
     * @hidden internal use only
     * @valid since 3.50
     * @type api
     * @brief Sets client mixing parameters.
     * @param param See TranscoderClientMixParam{@link #TranscoderClientMixParam}.
     * @return See TranscoderClientMixParam{@link #TranscoderClientMixParam}.
     */
    virtual void setClientMixParam(TranscoderClientMixParam param) = 0;
    /**
     * @locale zh
     * @hidden internal use only
     * @valid since 3.50
     * @type api
     * @brief 设置转推直播单通同步参数。
     * @param param 参看 TranscoderSyncControlParam{@link #TranscoderSyncControlParam}。
     * @return 参看 TranscoderSyncControlParam{@link #TranscoderSyncControlParam}。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @valid since 3.50
     * @type api
     * @brief Sets the parameters of simplex mode and synchronization when pushing to CDN.
     * @param param See TranscoderSyncControlParam{@link #TranscoderSyncControlParam}.
     * @return See TranscoderSyncControlParam{@link #TranscoderSyncControlParam}.
     */
    virtual void setSyncControlparam(TranscoderSyncControlParam param) = 0;

    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 将输入的 json 格式的字符串转成 ITranscoderParam 结构体
     * @param json_str json 格式字符串
     * @return 转换后的 ITranscoderParam 结构体
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Convert the json format string into the ITranscoderParam structure
     * @param json_str Json format string
     * @return Converted ITranscoderParam structure
     */
    virtual ITranscoderParam* inflatten(const char* json_str) = 0;

    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取默认的合流转推参数
     * @return 生成的 ITranscoderParam 结构体
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Get default transcoding param
     * @return Default ITranscoderParam structure
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
 * @locale zh
 * @type keytype
 * @brief 转推直播配置参数。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Configurations to be set while pushing media streams to CDN.(New)
 */
class IMixedStreamConfig : public ITranscoderParamBase {
public:

    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取合流类型。
     * @return 合流类型，参看 MixedStreamType{@link #MixedStreamType}
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Gets the stream mixing type.
     * @return Stream mixing type. See MixedStreamType{@link #MixedStreamType}
     */
    virtual MixedStreamType getExpectedMixingType() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取推流用户 ID。
     * @return 推流用户 ID。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the user ID for mixed stream.
     * @return The user ID for live mixed stream.
     */
    virtual const char* getUserID() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取推流 CDN 地址。
     * @return 推流地址。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the URL for live mixed stream.
     * @return The CDN url.
     */
    virtual const char* getPushURL() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取用户配置的额外信息。
     * @return UserConfigExtraInfo 信息。
     */
    /**
     * @locale en
     * @type api
     * @region Forward to live broadcast
     * @brief Get user config extra information.
     * @return extraI Information.
     */
    virtual const char* getUserConfigExtraInfo() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取合流音频参数。
     * @return 合流音频参数内容，参看 MixedStreamAudioConfig{@link #MixedStreamAudioConfig}。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Gets the audio configurations.
     * @return Audio configurations. See MixedStreamAudioConfig{@link #MixedStreamAudioConfig}.
     */
    virtual MixedStreamAudioConfig getAudioConfig() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取合流视频转码参数。
     * @return 合流视频转码参数内容，参看 MixedStreamVideoConfig{@link #MixedStreamVideoConfig}。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Gets the video configurations.
     * @return Video configurations. See MixedStreamVideoConfig{@link #MixedStreamVideoConfig}.
     */
    virtual MixedStreamVideoConfig getVideoConfig() = 0;
    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 获取转推 CDN 时的空间音频参数。
     * @return 参看 MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig}。
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief Get the spatial audio configurations of pushing to CDN.
     * @return See MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig}.
     */
    virtual MixedStreamSpatialAudioConfig getSpatialAudioConfig() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取合流视窗布局信息。
     * @param index 视窗对应下标。
     * @return 合流视窗布局信息，参看 MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig}。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Gets the video layout information of the mixed stream.
     * @param index The number of the view of which you want to get information.
     * @return Layout information. See MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig}.
     */
    virtual MixedStreamLayoutRegionConfig getLayoutByIndex(int32_t index) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 获取动态扩展自定义参数
     * @return 动态扩展自定义参数
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region Forward to live broadcast
     * @brief Get dynamically extend customizable parameters
     * @return dynamically extend customizable parameters
     */
    virtual const char* getAdvancedConfig() = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 获取业务透传鉴权信息
     * @return 业务透传鉴权信息
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region Forward to live broadcast
     * @brief Get Business Transparent Authentication Information
     * @return Business Transparent Authentication Information
     */
    virtual const char* getAuthInfo() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取客户端合流信息。
     * @return 客户端合流信息，参看 MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig}。
     */
    /**
     * @locale en
     * @type api
     * @brief Get client mixing parameters.
     * @return Client mixing parameters. See MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig}.
     */
    virtual MixedStreamClientMixConfig getClientMixConfig()  = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @brief 获取转推直播同步参数。
     * @return 转推直播同步参数，参看 MixedStreamSyncControlConfig{@link #MixedStreamSyncControlConfig}。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @brief Get transcoding sync control parameters.
     * @return Transcoding sync control parameters. See MixedStreamSyncControlConfig{@link #MixedStreamSyncControlConfig}.
     */
    virtual MixedStreamSyncControlConfig getSyncControlConfig() = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 设置合流类型。建议设置。
     * @param expected_mix_type 合流类型，参看 MixedStreamType{@link #MixedStreamType}
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Sets the expected stream mixing type. It's recommended to be set.
     * @param expected_mix_type Stream mixing type. See MixedStreamType{@link #MixedStreamType}
     */
    virtual void setExpectedMixingType(MixedStreamType expected_mix_type) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置推流用户 ID。`room_id` 和 `user_id` 长度相加不得超过 126 字节。建议设置。<br>
     *        本参数不支持过程中更新。
     * @param user_id 推流用户 ID。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the user ID for live transcoding. The sum length of `room_id` and `user_id` should not exceed 126 bytes. It's recommended to be set.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     * @param user_id The user ID for live transcoding.
     */
    virtual void setUserID(const char* user_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。建议设置。<br>
     *        本参数不支持过程中更新。
     * @param url 推流地址。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the URL for live transcoding. Only supports live transcoding via RTMP. The URL should match the regular expression `/^rtmps?:\/\//`. It's recommended to be set.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     * @param url The URL to be set.
     */
    virtual void setPushURL(const char* push_url) = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 设置音频参数。参看 MixedStreamAudioConfig{@link #MixedStreamAudioConfig}。建议设置。<br>
     *        本参数不支持过程中更新。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Sets audio configurations. See MixedStreamAudioConfig{@link #MixedStreamAudioConfig}. It's recommended to be set.<br>
     *        This parameters cannot be updated while pushing stream to the CDN.
     */
    virtual void setAudioConfig(const MixedStreamAudioConfig&) = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 设置视频参数。参看 MixedStreamVideoConfig{@link #MixedStreamVideoConfig}。建议设置。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Sets video configurations. See MixedStreamVideoConfig{@link #MixedStreamVideoConfig}. It's recommended to be set.
     */
    virtual void setVideoConfig(const MixedStreamVideoConfig&) = 0;
    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief 设定转推 CDN 时的空间音频效果。参看 MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig}。
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @type api
     * @brief Sets spatial audio configurations. See MixedStreamSpatialAudioConfig{@link #MixedStreamSpatialAudioConfig}.
     */
    virtual void setSpatialAudioConfig(const MixedStreamSpatialAudioConfig&) = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 设置视频流合流整体布局信息。
     * @param regions[] 用户布局信息列表。为 MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} 数据类型的数组。每一个该类型对象为一路单独的视频流的布局信息。<br>
     *                       值不合法或未设置时，自动使用默认值。建议设置。
     * @param regions_size 合流视窗数量。建议设置。
     * @param background_color 合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。建议设置。<br>
     *                      值不合法或未设置时，自动使用默认值。
     * @param user_extra_info 透传的 App 数据。
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Sets the layout configurations.
     * @param regions[] User layout information list. It's a list of MixedStreamLayoutRegionConfig{@link #MixedStreamLayoutRegionConfig} that you construct for each stream.<br>
     *                       With invalid or empty input, the configurations will be set as the default values. It's recommended to be set.
     * @param regions_size Amount of views. It's recommended to be set.
     * @param background_color Background-color of the mixed stream in hexadecimal values such as #FFFFFF and #000000. The default value is #000000. It's recommended to be set.<br>
     *                      With invalid or empty input, the configurations will be set as the default values.
     * @param user_extra_info Additional data that you want to import.
     */
    virtual void setLayoutConfig(MixedStreamLayoutRegionConfig regions[],
                                int32_t regions_size,
                                const char* background_color,
                                const char* user_extra_info) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置动态扩展自定义参数
     * @param advanced_config 动态扩展自定义参数
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region Forward to live broadcast
     * @brief Sets dynamically extend customizable parameters
     * @param advanced_config  dynamically extend customizable parameters
     */
    virtual void setAdvancedConfig(const char* advanced_config) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 设置业务透传鉴权信息
     * @param auth_info 业务透传鉴权信息
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region Forward to live broadcast
     * @brief Sets Business Transparent Authentication Information
     * @param auth_info  Business Transparent Authentication Information
     */
    virtual void setAuthInfo(const char* auth_info) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置客户端合流信息，参看 MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig}。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets client mixing parameters. See MixedStreamClientMixConfig{@link #MixedStreamClientMixConfig}.
     */
    virtual void setClientMixConfig(MixedStreamClientMixConfig&) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @brief 设置转推直播同步参数。参看 MixedStreamSyncControlConfig{@link #MixedStreamSyncControlConfig}。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @brief Sets transcoding sync control parameters. See MixedStreamSyncControlConfig{@link #MixedStreamSyncControlConfig}.
     */
    virtual void setSyncControlConfig(MixedStreamSyncControlConfig&) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取服务端合流控制参数。参看 MixedStreamServerControlConfig{@link #MixedStreamServerControlConfig}。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the configurations while mixing streams on the server side. See MixedStreamServerControlConfig{@link #MixedStreamServerControlConfig}.
     */
    virtual MixedStreamServerControlConfig getServerControlConfig() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置服务端合流控制参数。参看 MixedStreamServerControlConfig{@link #MixedStreamServerControlConfig}。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the configurations while mixing streams on the server side. See MixedStreamServerControlConfig{@link #MixedStreamServerControlConfig}.
     */
    virtual void setServerControlConfig(MixedStreamServerControlConfig& config) = 0;
    /**
     * @locale zh
     * @valid since 3.57
     * @type api
     * @brief 设置合流后整体画布的背景图片 URL，长度最大为 1024 bytes。<br>
     *        支持的图片格式包括：JPG, JPEG, PNG。如果背景图片的宽高和整体屏幕的宽高不一致，背景图片会缩放到铺满屏幕。
     */
    /**
     * @locale en
     * @valid since 3.57
     * @type api
     * @brief Sets the URL of the background image for the canvas that renders the mixed stream, with a maximum length of 1024 bytes.<br>
     *        You can input images in the following supported formats: JPG, JPEG, PNG.<br>
     *        If the width and height of the background image are different from the screen dimensions, the background image will be scaled to fill the screen.
     */
    virtual void setBackgroundImageURL(const char* background_image_url) = 0;
    /**
     * @locale zh
     * @valid since 3.57
     * @type api
     * @brief 获取背景图片的地址。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the background image URL.
     */
    virtual const char* getBackgroundImageURL() = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @region 转推直播
     * @brief 将输入的 json 格式的字符串转成 ITranscoderParam 结构体
     * @param json_str json 格式字符串
     * @return 转换后的 ITranscoderParam 结构体
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @region Push to CDN
     * @brief Convert the json format string into the ITranscoderParam structure
     * @param json_str Json format string
     * @return Converted ITranscoderParam structure
     */
    virtual IMixedStreamConfig* inflatten(const char* json_str) = 0;
    /**
     * @locale zh
     * @type api
     * @region 转推直播
     * @brief 获取默认的合流转推参数
     * @return 生成的 IMixedStreamConfig 结构体
     */
    /**
     * @locale en
     * @type api
     * @region Push to CDN
     * @brief Get default transcoding config
     * @return Default IMixedStreamConfig structure
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
 * @locale zh
 * @type keytype
 * @brief 单流转推直播配置参数。
 */
/**
 * @locale en
 * @type keytype
 * @brief Configurations for pushing a single media stream to CDN.
 */
typedef struct PushSingleStreamParam {
    /**
     * @locale zh
     * @brief 媒体流所在的房间 ID
     */
    /**
     * @locale en
     * @brief The room ID of the media stream
     */
    const char* room_id;
    /**
     * @locale zh
     * @brief 媒体流所属的用户 ID
     */
    /**
     * @locale en
     * @brief The user ID of the media stream
     */
    const char* user_id;
    /**
     * @locale zh
     * @brief 推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。<br>
     *        本参数不支持过程中更新。
     */
    /**
     * @locale en
     * @brief The URL for live transcoding. Only supports live transcoding via RTMP. The URL should match the regular expression `/^rtmps?:\/\//`.<br>
     *        This parameter cannot be updated while pushing stream to the CDN.
     */
    const char* uri;
    /**
     * @locale zh
     * @brief 媒体流是否为屏幕流。
     */
    /**
     * @locale en
     * @brief Whether the media stream is a screen-sharing stream.
     */
    bool is_screen_stream;
}PushSingleStreamParam;

/**
* @locale zh
* @hidden internal use only
* @type keytype
* @brief 缓存同步模式。
*/
/**
* @locale en
* @hidden internal use only
* @type keytype
*/
enum ChorusCacheSyncMode {
    /**
     * @locale zh
     * @brief 合唱场景下，主唱应采用此模式，以发送带时间戳信息的媒体数据。
     */
    /**
     * @locale en
     * @brief Under chorus scenarios, the lead singer uses the mode to send the media data with timestamp attached.
     */
    kChorusCacheSyncModeProducer= 0,
    /**
     * @locale zh
     * @brief 合唱场景下，副唱应采用此模式。<br>
     *        此模式下，副唱收到来自主唱的带时间戳的媒体数据。副唱发送的媒体数据中带有来自主唱的时间戳。
     */
    /**
     * @locale en
     * @brief Under chorus scenarios, the sub singer uses the mode.<br>
     *        In this mode, the sub singer receives the media data from the lead singer with timestamp attached. The sub singer sends the media data with the lead singer's timestamp attached.
     */
    kChorusCacheSyncModeRetransmitter= 1,
    /**
     * @locale zh
     * @brief 合唱场景下，听众应采用此模式。<br>
     *        此模式下，听众收到来自主唱的时间戳，并据此对齐来自主唱和副唱的媒体数据，以获得良好的合唱播放效果。
     */
    /**
     * @locale en
     * @brief Under chorus scenarios, the audience uses the mode.<br>
     *        In this mode, the audience receives the lead singer's timestamp. The audience aligns and renders the media data from lead and sub singers, and gets good chorus experience.
     */
    kChorusCacheSyncModeConsumer = 2
};
/**
* @locale zh
* @hidden internal use only
* @type keytype
* @brief 缓存同步事件。
*/
/**
* @locale en
* @hidden internal use only
* @type keytype
*/
enum ChorusCacheSyncEvent {
     /**
     * @locale zh
     * @brief 成功
     */
    /**
     * @locale en
     * @brief Success
     */
    kChorusCacheSyncEventStartSuccess = 0,
     /**
     * @locale zh
     * @brief 失败。
     */
    /**
     * @locale en
     * @brief Failed
     */
    kChorusCacheSyncEventStartFailed = 1,
};
/**
* @locale zh
* @hidden internal use only
* @type errorcode
* @brief 缓存同步错误码。
*/
/**
* @locale en
* @hidden internal use only
* @type errorcode
*/
enum ChorusCacheSyncError {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief OK
     */
    kChorusCacheSyncErrorOK = 0,
   /**
    * @locale zh
    * @brief 失败。推送至 CDN 时，应进行以下设置：<br>
    *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.enable_sync = true`；<br>
    *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.base_user_id = {uid of producer}`。
    */
    /**
    * @locale en
    * @type Failure. Check if the config of pushing mixed streams to CDN is as follows:<br>
    *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.enable_sync = true`；<br>
    *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.base_user_id = {uid of producer}`。
    */   
    kChorusCacheSyncErrorWrongState = 1,
    /**
    * @locale zh
    * @brief 缓存同步功能已启动，不需要重复开启。
    */
    /**
    * @locale en
    * @type Already running. Do not enable the feature repeatedly.
    */
    kChorusCacheSyncErrorAlreadyRunning = 2
};
/**
* @locale zh
* @hidden internal use only
* @type keytype
* @brief 缓存同步配置。
*/
/**
* @locale en
* @hidden internal use only
* @type keytype
*/
struct ChorusCacheSyncConfig {
     /**
      * @locale zh
      * @brief 最大媒体缓存时长（ms）。<br>
      *        取值范围是 `[500, 2500]`，默认值是 `2000`。<br>
      *        值越大，同步效果越好，但会造成占用内存较大。如果参与缓存同步的各路媒体流之间的时间差超过此值，会造成丢帧。
      */
     /**
      * @locale en
      * @brief Maximum duration of media data cached in ms.<br>
      *        `2000` by default. The range is `[500, 2500]`. <br>
      *        Use higher value for better syncing effect. If the time difference between media streams in cache synchronization exceeds this value, frame loss will occur.
      */
    int32_t max_cache_time_ms = 2000;
    /**
      * @locale zh
      * @brief 收到 onSyncedVideoFrames{@link #IChorusCacheSyncObserver#onSyncedVideoFrames} 的频率。<br>
      *        默认值是 `15`。此值通常应小于等于原始视频帧率；如果大于原始视频帧率，可能会收到重复帧。
      */
     /**
      * @locale en
      * @brief The frequency of receiving onSyncedVideoFrames{@link #IChorusCacheSyncObserver#onSyncedVideoFrames}.<br>
      *        `15` by default. The value is smaller than that of the original video fps usually; if the value is bagger than that, you may receive duplicated video frame.
      */
    int32_t video_fps = 15;
    /**
      * @locale zh
      * @brief 模式。参看 ChorusCacheSyncMode{@link #ChorusCacheSyncMode}. 默认值是 `retransmitter`。  
      */
     /**
      * @locale en
      * @brief Mode. See ChorusCacheSyncMode{@link #ChorusCacheSyncMode}. `retransmitter` by default.
      */
    ChorusCacheSyncMode mode = kChorusCacheSyncModeRetransmitter;
};
}  // namespace bytertc
