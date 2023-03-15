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
     * @brief 自动布局
     */
    kLayoutAutoMode = 0,
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
 * @brief 公共流视频编码参数
 */
typedef struct PublicStreamVideoParam {
    /** 
     * @brief 公共流视频宽度，必填。单位为 px，范围为 [2, 1920]，必须是偶数。
     */
    int32_t width;
    /** 
     * @brief 公共流视频高度，必填。单位为 px，范围为 [16, 1280]，必须是偶数。
     */
    int32_t height;
    /** 
     * @brief 公共流视频帧率。必填<br>
     *        范围：[1, 60] 
     */
    int32_t fps;
    /** 
     * @brief 视频码率，必填<br>
     *        范围：[1,10000000]<br>
     *        单位为 bps
     */
    int32_t bitrate_kpbs;
} PublicStreamVideoParam;
/** 
 * @hidden currently not available
 * @type keytype
 * @brief 公共流音频编码参数
 */
typedef struct PublicStreamAudioParam {
    /** 
     * @brief 音频采样率，必填。单位为 Hz。可选取值：16000, 32000, 44100 和 48000
     */
    int32_t sample_rate;
    /** 
     * @brief 音频声道数，必填。
     * + 1: 单声道<br>
     * + 2: 双声道
     */
    int32_t channel_num;
    /** 
     * @brief 音频码率，必填。单位为 kbps。<br>
     * 正整数，可选取值：16, 32, 64。
     */
    int32_t bitrate_kbps;
} PublicStreamAudioParam;
/** 
 * @type keytype
 * @brief 单个视频流在公共流中的布局信息。  <br>
 *        在多路视频流公共流时，你需要设置每一路视频流在公共流中的布局信息。
 */
typedef struct PublicStreamLayoutRegion {
    /** 
     * @brief 目标公共流用户的 ID。必填。  <br>
     *        服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。
     */
    const char* user_id = "";
    /** 
     * @brief 跨房间订阅流时，目标流所在的房间 ID。 必填。  <br>
     *        服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。
     */
    const char* room_id = "";
    /** 
     * @brief 背景图片地址
     */
    const char* alternate_image_uri = "";
    /** 
     * @brief 用户视频布局相对画布左侧的偏移量，取值的范围为 [0.0, 1.0)。必填。  
     */
    float x;
    /** 
     * @brief 用户视频布局相对画布顶端的偏移量，取值的范围为 [0.0, 1.0)。必填。
     */
    float y;
    /** 
     * @brief 用户视频宽度相对画布宽度的比例，取值的范围为 (0.0, 1.0]。必填。
     */
    float width;
    /** 
     * @brief 用户视频高度相对画布高度的比例，取值的范围为 (0.0, 1.0]。必填。
     */
    float height;
    /** 
     * @brief 透明度，取值范围 [0，255], 0 为全透明，255 为不透明
     */
    float alpha;
    /** 
     * @brief 用户视频布局在画布中的层级，取值范围 [0，100]，0(默认）为底层，100 为顶层。
     */
    int32_t z_order;
    /** 
     * @brief 必填。媒体流类型：  <br>
     *        + 0: 普通流（默认设置）  <br>
     *        + 1: 屏幕流
     */
    int stream_type = 0;
    /** 
     * @brief 公共流输出类型，参看 TranscoderContentControlType{@link #TranscoderContentControlType}
     */
    TranscoderContentControlType media_type;
    /** 
     * @brief 渲染时，视频内容缩放模式，必填。参看 RenderMode{@link #RenderMode}
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
     * @brief 布局模式。必填。<br>
     *        + `0`: 自动模式。默认值。 <br>
     *        + `2`: 自定义模式。
     */
    int layoutMode;
    /** 
     * @brief 插帧模式<br>
     *         + `0`: 补最后一帧<br>
     *         + `1`: 补背景图片，如果没有设置背景图片则补黑帧
     */
    int interMode;
    /** 
     * @brief 背景图片
     */
    const char* background_image = nullptr;
    /** 
     * @brief 公共流视频的背景颜色，格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色
     */
    const char* background_color = nullptr;
    /** 
     * @brief 各路流的布局信息列表。每一个该类型对象为一路单独的视频流的布局信息。详见 PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion}
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
     * @brief 公共流视频编码参数配置，必填。详见 PublicStreamVideoParam{@link #PublicStreamVideoParam}
     */
    PublicStreamVideoParam video_config;
    /** 
     * @brief 公共流音频编码参数配置，必填。详见 PublicStreamAudioParam{@link #PublicStreamAudioParam}
     */
    PublicStreamAudioParam audio_config;
    /** 
     * @brief 公共流流布局设置，必填。详见 PublicStreamLayout{@link #PublicStreamLayout}
     */
    PublicStreamLayout layout;
};
/** 
 * @type keytype
 * @brief 公共流参数
 *        本类型继承了 ITranscoderParamBase{@link #ITranscoderParamBase} 中的所有接口。
 */
class IPublicStreamParam : public ITranscoderParamBase {
public:
    /** 
     * @type api
     * @brief 获取公共流的布局模式，多路媒体流将按照指定的布局模式，合成为一路公共流。目前只支持 `kLayoutCustomerMode` 模式
     * @return 公共流的布局模式，参看 StreamLayoutMode{@link #StreamLayoutMode}
     *          `2`：自定义
     */
    virtual StreamLayoutMode layoutMode() = 0;
    /** 
     * @type api
     * @brief 获取补帧模式
     * @return 补帧模式<br>
     *         + `0`: 补最后一帧<br>
     *         + `1`: 补背景图片，如果没有设置背景图片则补黑帧
     */
    virtual int interpolationMode() = 0;
    /** 
     * @type api
     * @brief 获取背景图片链接
     * @return 背景图片链接
     */
    virtual const char* backgroundImageUri() = 0;
    /** 
     * @type api
     * @brief 获取公共流音频编码参数
     * @return 公共流音频编码参数内容，参看 PublicStreamAudioParam{@link #PublicStreamAudioParam}
     */
    virtual PublicStreamAudioParam audioParam() = 0;
    /** 
     * @type api
     * @brief 获取公共流视频编码参数
     * @return 公共流视频参数内容，参看 PublicStreamVideoParam{@link #PublicStreamVideoParam}
     */
    virtual PublicStreamVideoParam videoParam() = 0;
    /** 
     * @type api
     * @brief 获取公共流视窗布局信息
     * @param [in] index 视窗对应下标
     * @return 公共流视窗布局信息，参看 PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion}
     */
    virtual PublicStreamLayoutRegion layoutRegionByIndex(int32_t index) = 0;
    /** 
     * @type api
     * @brief 设置补帧模式
     * @param [in] mode 补帧模式<br>
     *         + `0`: 补最后一帧<br>
     *         + `1`: 补背景图片，如果没有设置背景图片则补黑帧
     */
    virtual void setInterpolationMode(int mode) = 0;
    /** 
     * @type api
     * @brief 设置背景图片的地址
     * @param [in] uri 公共流的背景图片的地址
     */
    virtual void setBackgroundImageUri(const char* uri) = 0;
    /** 
     * @hidden currently not available
     * @type api
     * @brief 设置音频编码参数
     * @param [in] PublicStreamAudioParam 音频参数，参看 PublicStreamAudioParam{@link #PublicStreamAudioParam}
     */
    virtual void setAudioParam(const PublicStreamAudioParam&) = 0;
    /** 
     * @type api
     * @brief 设置视频编码参数
     * @param [in] PublicStreamVideoParam 视频编码参数，参看 PublicStreamVideoParam{@link #PublicStreamVideoParam}
     */
    virtual void setVideoParam(const PublicStreamVideoParam&) = 0;
    /** 
     * @type api
     * @brief 设置公共流布局参数
     * @param [in] regions[] 必填。公共流布局参数，参看 PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion}
     * @param [in] regions_size 必填。公共流视窗数量
     * @param [in] bg_color 公共流背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色
     * @param [in] mode 必填。布局参数，参看 StreamLayoutMode{@link #StreamLayoutMode}
     */
    virtual void setLayoutParam(
                PublicStreamLayoutRegion regions[], int32_t regions_size, const char* bg_color,
                StreamLayoutMode mode) = 0;
    /** 
     * @type api
     * @brief 将输入的 json 格式的字符串转成 ITranscoderParam 结构体
     * @param [in] json_str json 格式字符串
     * @return 转换后的 ITranscoderParam 结构体
     */
    virtual IPublicStreamParam* inflatten(const char* json_str) = 0;
    /** 
     * @type api
     * @brief 参数校验
     * @param [in] json_str 传入参数，json 格式字符串
     * @return 检查结果<br>
     *        `true`: 所有参数都合法<br>
     *        `false`: 存在不合法参数
     */
    virtual bool checkParameter(const char* json_str) = 0;
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
 BYTERTC_API IPublicStreamParam* createPublicStreamParam();
} /* namespace bytertc */
