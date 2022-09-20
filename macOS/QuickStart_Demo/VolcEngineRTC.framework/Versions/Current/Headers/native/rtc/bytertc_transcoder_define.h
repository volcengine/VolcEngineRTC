/*
 * Copyright 2021 @bytedance
 *  Created on: june 20, 2021
 */

#pragma once
#include "bytertc_video_frame.h"
#include "bytertc_audio_frame.h"
#include "bytertc_transcoder_base_interface.h"

#define TRANSCODE_ERR_OK 0
#define TRANSCODE_ERR_BASE 1090
#define TRANSCODE_ERR_INVALID_PARAM 1091
#define TRANSCODE_ERR_INVALID_STATE 1092
#define TRANSCODE_ERR_INVALID_OPERATOR 1093
#define TRANSCODE_ERR_TIMEOUT 1094
#define TRANSCODE_ERR_INVALID_PARAM_BY_SERVER 1095
#define TRANSCODE_ERR_SUB_TIMEOUT_BY_SERVER 1096
#define TRANSCODE_ERR_INVALID_STATE_BY_SERVER 1097
#define TRANSCODE_ERR_AUTHENTICATION_BY_CDN 1098
#define TRANSCODE_ERR_TIMEOUT_BY_SIGNALING 1099
#define TRANSCODE_ERR_PUSH_PUBLIC_STREAM_FAIL 1100
#define TRANSCODE_ERR_MIX_IMAGE_FAIL 1101
#define TRANSCODE_ERR_UNKNOW_ERROR_BY_SERVER 1102
#define TRANSCODE_ERR_MAX 1199

namespace bytertc {
/** 
 * @type keytype
 * @brief 转推直播事件
 */
enum StreamMixingEvent {
    /**
     * @hidden
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
};


/** 
 * @hidden
 * @brief 343 需求，缺注释，需补齐
 */
enum SingleStreamPushEvent {
    kSingleStreamPushBase = 0,
    kSingleStreamPushStart = 1,
    kSingleStreamPushSuccess = 2,
    kSingleStreamPushFailed = 3,
    kSingleStreamPushStop = 4,
    kSingleStreamPushTimeout = 5,
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
     * @hidden
     */
    kStreamMixingErrorMax = 1199,
};

/** 
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
 * @type keytype
 * @brief AAC 编码等级
 */
enum TranscoderAudioCodecProfile {
    /** 
     * @brief 编码等级 AAC-LC
     */
    kByteAACProfileLC = 0,
    /** 
     * @brief 编码等级 HE-AAC v1
     */
    kByteAACProfileHEv1 = 1,
    /** 
     * @brief 编码等级 HE-AAC v2
     */
    kByteAACProfileHEv2 = 2,
};

/** 
 * @type keytype
 * @brief 视频编码规格
 */
enum TranscoderVideoCodecProfile {
    /** 
     * @brief H264 格式基本规格编码
     */
    kByteH264ProfileBaseline = 0,
    /** 
     * @brief H264 格式主流规格编码
     */
    kByteH264ProfileMain = 1,
    /** 
     * @brief H264 格式高规格编码
     */
    kByteH264ProfileHigh = 2,
    /** 
     * @brief ByteVC1 格式基本规格编码
     */
    kByteVC1ProfileBaseline = 3,
    /** 
     * @brief ByteVC1 格式主流规格编码
     */
    kByteVC1ProfileMain = 4,
    /** 
     * @brief ByteVC1 格式高规格编码
     */
    kByteVC1ProfileHigh = 5,
};

/** 
 * @type keytype
 * @brief 视频渲染的缩放模式
 */
enum TranscoderRenderMode {
    /**
     * @hidden
     * @brief to be removed
     */
    kRenderUnknown = 0,
    /** 
     * @brief 视窗填满优先。  <br>
     *        视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    kRenderHidden = 1,
    /** 
     * @brief 视频帧内容全部显示优先。  <br>
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。
     */
    kRenderFit = 2,
    /** 
     * @brief 视频帧自适应画布。 <br>
     *        视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
    kRenderAdaptive = 3,
};

/** 
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
 * @type keytype
 * @brief 图片合流相关参数
 */
typedef struct TranscoderLayoutRegionDataParam{
    /** 
     * @brief 原始图片的宽度，单位为 px。
     */
    int image_width;
    /** 
     * @brief 原始图片的高度，单位为 px。
     */
    int image_height;
}TranscoderLayoutRegionDataParam;

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
 * @hidden
 */
typedef size_t status_t;
/**
 * @hidden
 */
class IVideoFrame;
/**
 * @hidden
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
    DataFrameType frame_type;
    /** 
     * @brief 数据帧数据
     */
    uint8_t* u8_data;
    /** 
     * @brief 数据帧数据大小
     */
    uint32_t u32_data_size;
    /** 
     * @brief 数据帧时间戳，单位：微秒
     */
    uint64_t u64_ts_us;
} IDataFrame;

/** 
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息。  <br>
 *        开启转推直播功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 */
typedef struct TranscoderLayoutRegion {
    /** 
     * @brief 合流用户的 ID。必填。
     */
    const char* region_id;
   /** 
     * @brief 图片或视频流所在房间的房间 ID。<br>
     *        如果此图片或视频流是通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
     */
    const char* room_id;
    /** 
     * @brief 用户视频布局相对画布左侧的偏移量，取值的范围为 [0.0, 1.0)
     */
    float x;
    /** 
     * @brief 用户视频布局相对画布顶端的偏移量，取值的范围为 [0.0, 1.0)
     */
    float y;
    /** 
     * @brief 用户视频宽度相对画布宽度的比例，取值的范围为 (0.0, 1.0]
     */
    float width;
    /** 
     * @brief 用户视频高度相对画布高度的比例，取值的范围为 (0.0, 1.0]
     */
    float height;
    /** 
     * @brief 透明度，取值范围 [0，255]
     */
    float alpha;
    /** 
     * @brief 用户视频布局在画布中的层级，取值范围 [0，100]，0 为底层，值越大层级越高
     */
    int32_t i32_z_order;
    /** 
     * @brief 是否为本地用户：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    bool local_user;
    /** 
     * @brief 是否为屏幕流：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    bool screen_stream = false;
    /** 
     * @brief 合流内容控制。默认值为 `kHasAudioAndVideo`，参看 TranscoderContentControlType{@link #TranscoderContentControlType}。
     */
    TranscoderContentControlType content_control;
    /** 
     * @brief 渲染时，视频内容缩放模式，参看 TranscoderRenderMode{@link #TranscoderRenderMode}
     */
    TranscoderRenderMode render_mode;
    /** 
     * @type keytype
     * @brief 合流布局区域类型，参看 TranscoderLayoutRegionType{@link #TranscoderLayoutRegionType}。
     */
    TranscoderLayoutRegionType type;
    /** 
     * @type keytype
     * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
     */
    uint8_t* data;
    /** 
     * @type keytype
     * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 TranscoderLayoutRegionDataParam{@link #TranscoderLayoutRegionDataParam}。
     */
    TranscoderLayoutRegionDataParam data_param;
} TranscoderLayoutRegion;

/** 
 *  @type keytype
 *  @brief 音频转码配置参数。
 */
typedef struct TranscoderAudioParam {
    /** 
     * @brief 音频采样率，单位 kHz。可取 32Khz、44.1Khz、48Khz，默认值为 48Khz。
     */
    int32_t i32_sample_rate;
    /** 
     * @brief 音频声道数。可取 1、2，默认值为 2。
     */
    int32_t i32_channel_num;
    /** 
     * @brief 音频码率，单位 Kbps。可取范围 [32Kbps, 192Kbps]，默认值为 64Kbps。
     */
    int32_t i32_bitrate_kbps;
    /** 
     *  @brief AAC 等级，参看 TranscoderAudioCodecProfile{@link #TranscoderAudioCodecProfile}。默认值为 `0`。
     */
    TranscoderAudioCodecProfile audio_codec_profile;
} TranscoderAudioParam;

/** 
 * @type keytype
 * @brief 合流视频转码参数
 */
typedef struct TranscoderVideoParam {
    /** 
     * @brief 合流视频宽度，单位：px。  <br>
     *        仅支持设为偶数，如果设为奇数，后处理会直接拒绝，导致合流失败。
     */
    int32_t i32_width;
    /** 
     * @brief 合流视频高度，单位：px。  <br>
     *        仅支持设为偶数，如果设为奇数，后处理会直接拒绝，导致合流失败。
     */
    int32_t i32_height;
    /** 
     * @brief 合流的视频帧率。默认值为 `15`，取值范围是 `[1, 60]`。值不合法时，自动调整为默认值。
     */
    int32_t i32_fps;
    /** 
     * @brief I 帧间隔。默认值为 `4`，取值范围为 `[1, 5]`，单位为秒。值不合法时，自动调整为默认值。
     */
    int32_t i32_gop;
    /** 
     * @brief 合流视频码率。单位为 kbps，取值范围为 `[1,10000]`，默认值为自适应。值不合法时，自动调整为默认值。
     */
    int32_t i32_bitrate_kbps;
    /** 
     * @brief 视频编码规格，参看 TranscoderVideoCodecProfile{@link #TranscoderVideoCodecProfile}
     */
    TranscoderVideoCodecProfile video_codec_profile;
    /** 
     * @brief 是否使用低延时特性：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    bool lowLatency;
} TranscoderVideoParam;

/** 
 * @type keytype
 * @brief 转推直播配置参数
 */
class ITranscoderParam : public ITranscoderParamBase {
public:

    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流类型
     * @return 合流类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    virtual StreamMixingType expectedMixingType() = 0;
    /** 
     * @type api
     * @region 转码
     * @brief 获取合流用户 ID
     * @return 合流用户 ID
     */
    virtual const char* userID() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取推流地址
     * @return 推流地址
     */
    virtual const char* uri() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取 SEI 信息
     * @return SEI 信息
     */
    virtual const char* appData() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流音频参数
     * @return 合流音频参数内容，参看 TranscoderAudioParam{@link #TranscoderAudioParam}
     */
    virtual TranscoderAudioParam audioParam() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流视频转码参数
     * @return 合流视频转码参数内容，参看 TranscoderVideoParam{@link #TranscoderVideoParam}
     */
    virtual TranscoderVideoParam videoParam() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流视窗布局信息
     * @param [in] index 视窗对应下标
     * @return 合流视窗布局信息，参看 TranscoderLayoutRegion{@link #TranscoderLayoutRegion}
     */
    virtual TranscoderLayoutRegion layoutRegionByIndex(int32_t index) = 0;

    /** 
     * @hidden
     * @type api
     * @region 转推直播
     * @brief 获取动态扩展自定义参数
     * @return 动态扩展自定义参数
     */
    virtual const char* advancedConfig() = 0;
    /** 
     * @hidden
     * @type api
     * @region 转推直播
     * @brief  获取业务透传鉴权信息
     * @return 业务透传鉴权信息
     */
    virtual const char* authInfo() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置合流类型
     * @param [in] expected_mix_type 合流类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    virtual void setExpectedMixingType(StreamMixingType expected_mix_type) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置合流用户 ID
     * @param [in] user_id 发起合流的用户的 ID
     */
    virtual void setUserID(const char* user_id) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置推流地址
     * @param [in] uri 推流地址
     */
    virtual void setUri(const char* uri) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置音频参数
     * @param [in] TranscoderAudioParam 音频参数，参看 TranscoderAudioParam{@link #TranscoderAudioParam}
     */
    virtual void setAudioParam(const TranscoderAudioParam&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置视频参数
     * @param [in] TranscoderVideoParam 视频参数，参看 TranscoderVideoParam{@link #TranscoderVideoParam}
     */
    virtual void setVideoParam(const TranscoderVideoParam&) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置合流布局参数
     * @param [in] regions[] 合流布局参数，参看 TranscoderLayoutRegion{@link #TranscoderLayoutRegion}
     * @param [in] regions_size 合流视窗数量
     * @param [in] bg_color 合流背景颜色
     * @param [in] app_data 用户额外需要传入的数据
     */
    virtual void setLayoutParam(
            TranscoderLayoutRegion regions[], int32_t regions_size, const char* bg_color, const char* app_data) = 0;
    /** 
     * @hidden
     * @type api
     * @region 转推直播
     * @brief 设置动态扩展自定义参数
     * @param [in] advancedConfig 动态扩展自定义参数
     */
    virtual void setAdvancedConfig(const char* advancedConfig) = 0;
    /** 
     * @hidden
     * @type api
     * @region 转推直播
     * @brief  设置业务透传鉴权信息
     * @param [in] authInfo 业务透传鉴权信息
     */
    virtual void setAuthInfo(const char* authInfo) = 0;

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
     * @hidden
     */
    virtual ~ITranscoderParam() = default;
};
/** 
 * @hidden not available in 343
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
