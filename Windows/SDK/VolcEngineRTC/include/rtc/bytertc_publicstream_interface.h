//
//  bytertc_publicstream_interface.h
//  VolcEngineRTC

#pragma once

#include "bytertc_defines.h"
#include "bytertc_transcoder_base_interface.h"

#define PUBLICSTREAM_OK 0
#define PUBLICSTREAM_BASE 1190
#define PUBLICSTREAM_INVALID_PARAM 1191
#define PUBLICSTREAM_INVALID_STATE 1192
#define PUBLICSTREAM_INTERNAL_ERROR 1193
#define PUBLICSTREAM_PUSH_FAILED 1195
#define PUBLICSTREAM_TIMEOUT 1196

namespace bytertc {
/** 
 * @type keytype
 * @brief 公共流的布局模式
 */
enum StreamLayoutMode {
    /** 
     * @brief 自定义
     */
    kLayoutCustomerMode = 2
};

/** 
 * @type keytype
 * @brief 公共流错误码。
 */
enum PublicStreamErrorCode {
    /** 
     * @brief 推流成功。
     */
    kPublicStreamOK = 200,
    /** 
     * @brief 推流参数错误。
     */
    kPushPublicStreamInvalidParam = 1191,
    /** 
     * @brief 推流状态异常。
     */
    kPushPublicStreamInvalidStatus = 1192,
    /** 
     * @brief 推流内部错误。
     */
    kPushPublicStreamInternalError = 1193,
    /** 
     * @brief 推流失败。
     */
    kPushPublicStreamPushFailed = 1195,
    /** 
     * @brief 推流消息发送超时。
     */
    kPushPublicStreamTimeout = 1196,
};

/** 
 * @type keytype
 * @brief 公共流视频裁剪配置
 */
typedef struct SourceCrop {
    /** 
     * @brief 裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)
     */
    float LocationX = 0.0;
    /** 
     * @brief 裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)
     */
    float LocationY = 0.0;
    /** 
     * @brief 裁剪后得到的视频帧宽度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]
     */
    float WidthProportion = 0.0;
    /** 
     * @brief 裁剪后得到的视频帧高度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]
     */
    float HeightProportion = 0.0;
} SourceCrop;
/** 
 * @type keytype
 * @brief 公共流视频参数
 */
typedef struct PublicStreamVideoParam {
    /** 
     * @brief 宽度，单位：px。  <br>
     *        仅支持设为偶数，如果设为奇数，将导致公共流发布失败。
     */
    int32_t width;
    /** 
     * @brief 高度，单位：px。  <br>
     *        仅支持设为偶数，如果设为奇数，后处理会直接拒绝，导致公共流失败。
     */
    int32_t height;
    /** 
     * @brief 帧率，单位：fps
     */
    int32_t fps;
    /** 
     * @brief 码率，单位：kbps
     */
    int32_t bitrate_kpbs;
} PublicStreamVideoParam;
/** 
 * @type keytype
 * @brief 公共流音频参数
 */
typedef struct PublicStreamAudioParam {
    /** 
     * @brief 音频采样率，包括 16k, 32k, 44.1k, 48k
     */
    int32_t sample_rate;
    /** 
     * @brief 声道数
     */
    int32_t channel_num;
    /** 
     * @brief 音频码率，单位：kbps，包括 16kbps, 32kbps, 64kbps
     */
    int32_t bitrate_kbps;
} PublicStreamAudioParam;
/** 
 * @type keytype
 * @brief 单个视频流在公共流中的布局信息。  <br>
 *        在多路视频流公共流时，你可以设置其中一路视频流在公共流中的预设布局信息。
 */
typedef struct PublicStreamLayoutRegion {
    /** 
     * @brief 目标公共流用户的 ID
     */
    const char* user_id = "";
    /** 
     * @brief 跨房间订阅流时，目标流所在的房间 ID
     */
    const char* room_id = "";
    /** 
     * @brief 背景图片地址
     */
    const char* alternate_image_uri = "";
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
    int32_t z_order;
    /** 
     * @brief 媒体流类型：  <br>
     *        + 0: 普通流（默认设置）  <br>
     *        + 1: 屏幕流
     */
    int stream_type = 0;
    /** 
     * @brief 公共流输出类型，参看 TranscoderContentControlType{@link #TranscoderContentControlType}
     */
    TranscoderContentControlType media_type;
    /** 
     * @brief 渲染时，视频内容缩放模式，参看 RenderMode{@link #RenderMode}
     */
    RenderMode render_mode;
    /** 
     * @brief 支持对每一路参与公共流的视频进行裁剪，参看 SourceCrop{@link #SourceCrop}
     */
    SourceCrop source_crop;
} PublicStreamLayoutRegion;
/** 
 * @type keytype
 * @brief 公共流布局设置。
 */
struct PublicStreamLayout {
    /** 
     * @brief 布局模式
     */
    int layoutMode;
    /** 
     * @brief 插帧模式
     */
    int interMode;
    /** 
     * @brief 背景图片
     */
    const char* background_image = nullptr;
    /** 
     * @brief 公共流视频的背景颜色，默认值 #000000，表示为黑色。
     */
    const char* background_color = nullptr;
    /** 
     * @brief 公共流布局信息。详见 PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion}
     */
    PublicStreamLayoutRegion* regions = nullptr;
    /** 
     * @brief 参与合流的数量
     */
    int regions_num = 0;
};
/** 
 * @type keytype
 * @brief 公共流配置信息
 */
struct PublicStreamConfig {
    /** 
     * @brief 公共流 ID
     */
    const char* stream_id = nullptr;
    /** 
     * @brief 公共流视频配置。详见 PublicStreamVideoParam{@link #PublicStreamVideoParam}
     */
    PublicStreamVideoParam video_config;
    /** 
     * @brief 公共流音频配置。详见 PublicStreamAudioParam{@link #PublicStreamAudioParam}
     */
    PublicStreamAudioParam audio_config;
    /** 
     * @brief 公共流流布局设置。详见 PublicStreamLayout{@link #PublicStreamLayout}
     */
    PublicStreamLayout layout;
};
/** 
 * @type keytype
 * @brief 公共流参数
 */
class IPublicStreamParam : public ITranscoderParamBase {
public:
    /** 
     * @type api
     * @brief 设置公共流的布局模式，目前只支持 `kLayoutCustomerMode` 模式
     * @return 公共流的布局模式，参看 StreamLayoutMode{@link #StreamLayoutMode}
     */
    virtual StreamLayoutMode LayoutMode() = 0;
    /** 
     * @type api
     * @brief 获取补帧模式
     * @return 补帧模式<br>
     *         `0`: 补最后一帧<br>
     *         `1`: 补背景图片或者黑帧
     */
    virtual int InterpolationMode() = 0;
    /** 
     * @type api
     * @brief 获取背景图片地址
     * @return 背景图片的地址
     */
    virtual const char* BackgroundImageUri() = 0;
    /** 
     * @type api
     * @brief 获取公共流音频参数
     * @return 公共流音频参数内容，参看 PublicStreamAudioParam{@link #PublicStreamAudioParam}
     */
    virtual PublicStreamAudioParam AudioParam() = 0;
    /** 
     * @type api
     * @brief 获取公共流视频参数
     * @return 公共流视频参数内容，参看 PublicStreamVideoParam{@link #PublicStreamVideoParam}
     */
    virtual PublicStreamVideoParam VideoParam() = 0;
    /** 
     * @type api
     * @brief 获取公共流视窗布局信息
     * @param [in] index 视窗对应下标
     * @return 公共流视窗布局信息，参看 PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion}
     */
    virtual PublicStreamLayoutRegion LayoutRegionByIndex(int32_t index) = 0;
    /** 
     * @type api
     * @brief 设置补帧模式
     * @param [in] mode 补帧模式<br>
     *         `0`: 补最后一帧<br>
     *         `1`: 补背景图片或者黑帧
     */
    virtual void SetInterpolationMode(int mode) = 0;
    /** 
     * @type api
     * @brief 设置背景图片的地址
     * @param [in] uri 公共流的背景图片的地址
     */
    virtual void SetBackgroundImageUri(const char* uri) = 0;
    /** 
     * @type api
     * @brief 设置音频参数
     * @param [in] PublicStreamAudioParam 音频参数，参看 PublicStreamAudioParam{@link #PublicStreamAudioParam}
     */
    virtual void SetAudioParam(const PublicStreamAudioParam&) = 0;
    /** 
     * @type api
     * @brief 设置视频参数
     * @param [in] PublicStreamVideoParam 音频参数，参看 PublicStreamVideoParam{@link #PublicStreamVideoParam}
     */
    virtual void SetVideoParam(const PublicStreamVideoParam&) = 0;
    /** 
     * @type api
     * @brief 设置公共流布局参数
     * @param [in] regions[] 公共流布局参数，参看 PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion}
     * @param [in] regions_size 公共流视窗数量
     * @param [in] bg_color 公共流背景颜色
     * @param [in] mode 布局参数，参看 StreamLayoutMode{@link #StreamLayoutMode}
     */
    virtual void SetLayoutParam(
                PublicStreamLayoutRegion regions[], int32_t regions_size, const char* bg_color,
                StreamLayoutMode mode) = 0;
    /** 
     * @type api
     * @brief 将输入的 json 格式的字符串转成 ITranscoderParam 结构体
     * @param [in] json_str json 格式字符串
     * @return 转换后的 ITranscoderParam 结构体
     */
    virtual IPublicStreamParam* Inflatten(const char* json_str) = 0;
    /** 
     * @type api
     * @brief 参数校验
     * @param [in] json_str 传入参数，json 格式字符串
     * @return 检查结果<br>
     *        `true`: 所有参数都合法<br>
     *        `false`: 存在不合法参数
     */
    virtual bool CheckParameter(const char* json_str) = 0;
    /**
     * @hidden
     */
    virtual ~IPublicStreamParam() = default;
};

/** 
 * @hidden
 * @type api
 * @brief 创建公共流参数实例
 */
 BYTERTC_API IPublicStreamParam* CreatePublicStreamParam();
} /* namespace bytertc */
