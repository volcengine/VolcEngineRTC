/*
 * Copyright 2021 @bytedance
 *  Created on: june 20, 2021
 */

#pragma once
#include "bytertc_video_frame.h"
#include "bytertc_audio_frame.h"

#define TRANSCODE_ERR_OK 0
#define TRANSCODE_ERR_BASE 1090
#define TRANSCODE_ERR_INVALID_PARAM 1091
#define TRANSCODE_ERR_INVALID_STATE 1092
#define TRANSCODE_ERR_INVALID_OPERATOR 1093
#define TRANSCODE_ERR_TIMEOUT 1094

namespace bytertc {

/**
 * @hidden
 * @type keytype
 * @brief 合流房间状态
 */
enum TranscoderRoomStatus {
    /**
     * @brief join room status
     */
    kRoomStatusJoinRoom,
    /**
     * @brief leave room status
     */
    kRoomStatusLeaveRoom,
    /**
     * @brief room status was offline
     */
    kRoomStatusOffline,
    /**
     * @brief room status was online
     */
    kRoomStatusOnline,
};

/**
 * @type keytype
 * @brief 合流事件类型
 */
enum StreamMixingEvent {
    /**
     * @hidden
     */ 
    kStreamMixingBase = 0,
    /**
     * @brief 合流开始
     */
    kStreamMixingStart = 1,
    /**
     * @brief 合流启动成功
     */
    kStreamMixingStartSuccess = 2,
    /**
     * @brief 合流启动失败
     */
    kStreamMixingStartFailed = 3,
    /**
     * @brief 更新合流
     */
    kStreamMixingUpdate = 4,
    /**
     * @brief 合流结束
     */
    kStreamMixingStop = 5,
    /**
     * @brief 合流类型发生改变
     */
    kStreamMixingChangeMixType = 6,
    /**
     * @brief 收到客户端合流音频首帧
     */
    kStreamMixingFirstAudioFrameByClientMix = 7,
    /**
     * @brief 收到客户端合流视频首帧
     */
    kStreamMixingFirstVideoFrameByClientMix = 8,
    /**
     * @brief 更新合流超时
     */
    kStreamMixingUpdateTimeout = 9,
    /**
     * @brief 开始合流超时
     */
    kStreamMixingStartTimeout = 10,
    /*
    * @brief 合流布局参数错误
    */
    kStreamMixingRequestParamError = 11,
    /**
     * @hidden
     */
    kStreamMixingMax = 15,
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
     * @brief 客户端合流
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
    * @brief 编码等级 AAC-MAIN
    */
    kByteAACProfileMain = 1,
    /**
     * @brief 编码等级 HE-AAC v1
     */
    kByteAACProfileHEv1 = 2,
    /**
     * @brief 编码等级 HE-AAC v2
     */
    kByteAACProfileHEv2 = 3,
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
 * @brief 合流输出内容类型
 */
enum TranscoderContentControlType {
    /**
     * @brief 输出的混流包含音频和视频
     */
    kHasAudioAndVideo = 0,
    /**
     * @brief 输出的混流只包含音频
     */
    kHasAudioOnly = 1,
    /**
     * @brief 输出的混流只包含视频
     */
    kHasVideoOnly = 2,
};

/**
 * @type keytype
 * @brief 渲染时，视频内容的缩放模式
 */
enum TranscoderRenderMode {
    /**
     * @hidden
     * @brief to be removed
     */
    kRenderUnknown = 0,
    /**
     * @brief 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    kRenderHidden = 1,
    /**
     * @brief 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。
     */
    kRenderFit = 2,
    /**
     * @brief 视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。
     */
    kRenderAdaptive = 3,
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
 * @brief 单个视频流在合流中的布局信息。  <br>
 *        开启转推直播功能后，在多路视频流合流时，你可以设置其中一路视频流在合流中的预设布局信息。
 */
typedef struct TranscoderLayoutRegion {
    /**
     * @brief 目标合流用户的 ID
     */
    const char* region_id;
    /**
     * @brief 跨房间订阅流时，目标流所在的房间 ID
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
     *        + false: 否（默认设置）
     */
    bool screen_stream = false;
    /**
     * @brief 合流输出内容，参看 TranscoderContentControlType{@link #TranscoderContentControlType}
     */
    TranscoderContentControlType content_control;
    /**
     * @brief 渲染时，视频内容缩放模式，参看 TranscoderRenderMode{@link #TranscoderRenderMode}
     */
    TranscoderRenderMode render_mode;
} TranscoderLayoutRegion;

/**
 * @type keytype
 * @brief 合流音频参数
 */
typedef struct TranscoderAudioParam {
    /**
     * @brief 音频采样率，包括 16k, 32k, 44.1k, 48k
     */
    int32_t i32_sample_rate;
    /**
     * @brief 声道数
     */
    int32_t i32_channel_num;
    /**
     * @brief 音频码率，单位：kbps，包括 16kbsp, 32kbps, 64kbps
     */
    int32_t i32_bitrate_kbps;
    /**
     *  @brief AAC 等级，参看 TranscoderAudioCodecProfile{@link #TranscoderAudioCodecProfile}
     */
    TranscoderAudioCodecProfile audio_codec_profile;
} TranscoderAudioParam;

/**
 * @type keytype
 * @brief 合流视频参数
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
     * @brief 合流视频帧率，单位：fps
     */
    int32_t i32_fps;
    /**
     * @brief 视频 I 帧间隔，单位：ms
     */
    int32_t i32_gop;
    /**
     * @brief 合流视频码率，单位：kbps
     */
    int32_t i32_bitrate_kpbs;
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
 * @type api
 */
class ITranscoderParam {
public:
    /**
     * @type api
     * @region 转推直播
     * @brief 获取合流房间 ID
     * @return 合流房间 ID
     */
    virtual const char* RoomID() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取合流用户 ID
     * @return 合流用户 ID
     */
    virtual const char* UserID() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取合流类型
     * @return 合流类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    virtual StreamMixingType ExpectedMixingType() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取推流地址
     * @return 推流地址
     */
    virtual const char* Uri() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取通过 Flatten{@link #Flatten} 方法转换得到的 json 格式内容
     * @return json 格式数据
     */
    virtual const char* JsonContent() = 0;
    /**
     * @hidden
     * @type api
     * @region 转推直播
     * @brief 获取 Other 数据
     * @return Other数据
     */
    virtual const char* Other() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取合流音频参数
     * @return 合流音频参数内容，参看 TranscoderAudioParam{@link #TranscoderAudioParam}
     */
    virtual TranscoderAudioParam AudioParam() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取合流视频参数
     * @return 合流视频参数内容，参看 TranscoderVideoParam{@link #TranscoderVideoParam}
     */
    virtual TranscoderVideoParam VideoParam() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取合流参数中视窗的数量
     * @return 合流参数中视窗的数量
     */
    virtual int32_t LayoutRegionsSize() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取合流视窗布局信息
     * @param [in] index 视窗对应下标
     * @return 合流视窗布局信息，参看 TranscoderLayoutRegion{@link #TranscoderLayoutRegion}
     */
    virtual TranscoderLayoutRegion LayoutRegionByIndex(int32_t index) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取背景颜色
     * @return 背景颜色
     */
    virtual const char* BackgroundColor() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 获取 SEI 信息
     * @return SEI 信息
     */
    virtual const char* AppData() = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 设置合流房间 ID
     * @param [in] room_id 发起合流的用户所在的房间 ID
     */
    virtual void SetRoomID(const char* room_id) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 设置合流用户 ID
     * @param [in] user_id 发起合流的用户的 ID
     */
    virtual void SetUserID(const char* user_id) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 设置合流类型
     * @param [in] expected_mix_type 合流类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    virtual void SetExpectedMixingType(StreamMixingType expected_mix_type) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 设置推流地址
     * @param [in] uri 推流地址
     */
    virtual void SetUri(const char* uri) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 设置 jsonContent  <br>
     *        传入通过 Flatten{@link #Flatten} 方法转换得到的 json 格式内容
     * @param [in] json_content json 格式内容
     */
    virtual void SetJsonContent(const char* json_content) = 0;
    /**
     * @hidden
     * @type api
     * @region 转推直播
     * @brief 设置 Other 数据
     * @param [in] other Other 数据
     */
    virtual void SetOther(const char* other) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 设置音频参数
     * @param [in] TranscoderAudioParam 音频参数，参看 TranscoderAudioParam{@link #TranscoderAudioParam}
     */
    virtual void SetAudioParam(const TranscoderAudioParam&) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 设置视频参数
     * @param [in] TranscoderVideoParam 音频参数，参看 TranscoderVideoParam{@link #TranscoderVideoParam}
     */
    virtual void SetVideoParam(const TranscoderVideoParam&) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 设置合流布局参数
     * @param [in] regions[] 合流布局参数，参看 TranscoderLayoutRegion{@link #TranscoderLayoutRegion}
     * @param [in] regions_size 合流视窗数量
     * @param [in] bg_color 合流背景颜色
     * @param [in] app_data 用户额外需要传入的数据
     */
    virtual void SetLayoutParam(
            TranscoderLayoutRegion regions[], int32_t regions_size, const char* bg_color, const char* app_data) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 将合流参数转成 json 字符串
     * @param [in] contentType 内容属性，表明是合流信令
     * @param [in] action 合流状态，可选取值如下：  <br>
     *               + started: 开启合流  <br>
     *               + layoutChanged: 更新合流布局  <br>
     *               + stopped: 停止合流
     * @return 转换后的 json 字符串
     */
    virtual const char* Flatten(const char* contentType, const char* action) = 0;
    /**
     * @type api
     * @region 转推直播
     * @brief 将输入的 json 格式的字符串转成 ITranscoderParam 结构体
     * @param [in] json_str json 格式字符串
     * @return 转换后的 ITranscoderParam 结构体
     */
    virtual ITranscoderParam* Inflatten(const char* json_str) = 0;
    /**
     * @hidden
     */
    virtual ~ITranscoderParam() = default;
};

}  // namespace bytertc
