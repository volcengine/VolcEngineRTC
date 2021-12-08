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
 *@brief 合流事件事件类型
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
     * @brief 服务端合流/端云一体合流
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
     * @brief 停止服务端合流超时
     */
    kStreamMixingStopTimeoutByServer = 9,
    /**
     * @brief 更新合流超时
     */
    kStreamMixingUpdateTimeout = 10,
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
 *@brief 合流类型
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
 *@brief 合流类型
 */
enum TranscoderAudioCodecProfile {
    kByteAACProfileLC = 0,
    kByteAACProfileMain = 1,
    kByteAACProfileHEv1 = 2,
    kByteAACProfileHEv2 = 3,
};

enum TranscoderVideoCodecProfile {
    kByteH264ProfileBaseline = 0,
    kByteH264ProfileMain = 1,
    kByteH264ProfileHigh = 2,
    kByteVC1ProfileBaseline = 3,
    kByteVC1ProfileMain = 4,
    kByteVC1ProfileHigh = 5,
};

enum TranscoderContentControlType {
    kHasAudioAndVideo = 0,
    kHasAudioOnly = 1,
    kHasVideoOnly = 2,
};

enum TranscoderRenderMode {
    kRenderUnknown = 0,  // TODO(LIYL): remove
    /**
     *  @brief 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    kRenderHidden = 1,
    /**
     *  @brief
     * 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。
     */
    kRenderFit = 2,
    /**
     *  @brief 视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。
     */
    kRenderAdaptive = 3,
};

enum DataFrameType {
    /**
     *  @brief sei 视频帧
     */
    kDataFrameTypeSei = 0,
};

typedef size_t status_t;
class IVideoFrame;
class IAudioFrame;

typedef struct IDataFrame {
    DataFrameType frame_type;
    uint8_t* u8_data;
    uint32_t u32_data_size;
    uint64_t u64_ts_us;
} IDataFrame;

typedef struct TranscoderLayoutRegion {
    const char* region_id;
    const char* room_id;
    float x;
    float y;
    float width;
    float height;
    float alpha;
    int32_t i32_z_order;
    bool local_user;
    bool screen_stream = false;
    TranscoderContentControlType content_control;
    TranscoderRenderMode render_mode;

} TranscoderLayoutRegion;

typedef struct TranscoderAudioParam {
    int32_t i32_sample_rate;
    int32_t i32_channel_num;
    int32_t i32_bitrate_kbps;
    TranscoderAudioCodecProfile audio_codec_profile;
} TranscoderAudioParam;

typedef struct TranscoderVideoParam {
    int32_t i32_width;
    int32_t i32_height;
    int32_t i32_fps;
    int32_t i32_gop;
    int32_t i32_bitrate_kpbs;
    TranscoderVideoCodecProfile video_codec_profile;
    bool lowLatency;
} TranscoderVideoParam;

/**
 * @type api
 * @region 转推直播
 * @brief 合流参数
 */
class ITranscoderParam {
public:
    /**
     * @type api
     * @region 转推直播
     * @brief 转推直播房间ID
     * @return 房间ID
     */
    virtual const char* RoomID() = 0;

    virtual const char* UserID() = 0;

    virtual StreamMixingType ExpectedMixingType() = 0;

    virtual const char* Uri() = 0;

    virtual const char* JsonContent() = 0;

    virtual const char* Other() = 0;

    virtual TranscoderAudioParam AudioParam() = 0;

    virtual TranscoderVideoParam VideoParam() = 0;

    virtual int32_t LayoutRegionsSize() = 0;

    virtual TranscoderLayoutRegion LayoutRegionByIndex(int32_t index) = 0;
    
    virtual const char* BackgroundColor() = 0;
    
    virtual const char* AppData() = 0;

    virtual void SetRoomID(const char* room_id) = 0;

    virtual void SetUserID(const char* user_id) = 0;

    virtual void SetExpectedMixingType(StreamMixingType expected_mix_type) = 0;

    virtual void SetUri(const char* uri) = 0;

    virtual void SetJsonContent(const char* json_content) = 0;

    virtual void SetOther(const char* other) = 0;

    virtual void SetAudioParam(const TranscoderAudioParam&) = 0;

    virtual void SetVideoParam(const TranscoderVideoParam&) = 0;

    virtual void SetLayoutParam(
            TranscoderLayoutRegion regions[], int32_t regions_size, const char* bg_color, const char* app_data) = 0;

    virtual const char* Flatten(const char* contentType, const char* action) = 0;

    virtual ITranscoderParam* Inflatten(const char* json_str) = 0;

    virtual ~ITranscoderParam() = default;
};

}  // namespace bytertc
