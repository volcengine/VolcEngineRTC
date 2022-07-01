/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Video Defines
 */

#pragma once

#include "bytertc_common_defines.h"
#include "bytertc_video_frame.h"

namespace bytertc {
/** 
 * @type keytype
 * @brief 渲染模式
 */
enum RenderMode {
    /** 
     * @brief 视窗填满优先。<br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    kRenderModeHidden = 1,
    /** 
     * @brief 视频帧内容全部显示优先。<br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
     */
    kRenderModeFit = 2,
    /** 
     *  @brief 视频帧自适应画布 <br>
     *         视频帧非等比缩放，直至画布被填满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
   kRenderModeFill = 3,
};

/** 
 * @type keytype
 * @brief 订阅媒体的类型
 */
enum SubscribeMediaType {
    /** 
     * @brief 既不订阅音频，也不订阅视频
     */
    kRTCSubscribeMediaTypeNone = 0,
    /** 
     * @brief 只订阅音频，不订阅视频
     */
    kRTCSubscribeMediaTypeAudioOnly,
    /** 
     * @brief 只订阅视频，不订阅音频
     */
    kRTCSubscribeMediaTypeVideoOnly,
    /** 
     * @brief 同时订阅音频和视频
     */
    kRTCSubscribeMediaTypeVideoAndAudio
};

/** 
 * @type keytype
 * @brief 暂停/恢复接收远端的媒体流类型。
 */
enum PauseResumeControlMediaType {
    /** 
     * @brief 只控制音频，不影响视频
     */
    kRTCPauseResumeControlMediaTypeAudio = 0,
    /** 
     * @brief 只控制视频，不影响音频
     */
    kRTCPauseResumeControlMediaTypeVideo = 1,
    /** 
     * @brief 同时控制音频和视频
     */
    kRTCPauseResumeControlMediaTypeVideoAndAudio = 2
};

/** 
 * @type keytype
 * @brief 时域分层定义
 */
enum SVCLayer {
    /** 
    * @brief 不指定分层(默认值）
    */
   kSVCLayerDefault = 0,
    /** 
     * @brief T0层
     */
    kSVCLayerBase = 1,
    /** 
     * @brief T0+T1层
     */
    kSVCLayerMain = 2,
    /** 
     * @brief T0+T1+T2层
     */
    kSVCLayerHigh = 3,
};

/** 
 * @type keytype
 * @brief 流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。
 */
struct RemoteStreamSwitch {
    /** 
     * @brief 订阅的音视频流的发布者的用户 ID。
     */
    const char* uid;
    /** 
     * @brief 是否是屏幕流。
     */
    bool is_screen;
    /** 
     * @brief 流切换前本地用户订阅的视频流的分辨率对应的索引。
     */
    int before_video_index;
    /** 
     * @brief 流切换后本地用户订阅的视频流的分辨率对应的索引。
     */
    int after_video_index;
    /** 
     * @brief 流切换前是否有视频流。
     */
    bool before_enable;
    /** 
     * @brief 流切换后是否有视频流。
     */
    bool after_enable;
    /** 
     * @brief 触发流回退的原因，详见类型 FallbackOrRecoverReason{@link #FallbackOrRecoverReason} 。
     */
    FallbackOrRecoverReason reason;
};

/** 
 * @type keytype
 * @brief 直播推流转码功能错误码。
 */
enum TransCodingError {
    /** 
     * @brief 推流成功。
     */
    kTransCodingErrorOK = 0,
    /** 
     * @brief 推流参数错误。
     */
    kTransCodingErrorInvalidArgument = 1,
    /** 
     * @brief 和 RTC 服务端建立连接失败。会自动重连
     */
    kTransCodingErrorSubscribe = 2,
    /** 
     * @brief 合流服务中间过程存在错误，建议重试。
     */
    kTransCodingErrorProcessing = 3,
    /** 
     * @brief 推流失败，可以等待服务端重新推流。
     */
    kTransCodingErrorPublish = 4,
};

/** 
 * @hidden
 * @type keytype
 * @brief 转推直播包含内容。
 */
enum LiveTranscodingContentControl {
    /** 
     * @brief 输出的混流包含音频和视频
     */
    kVideoAndAudio = 0,
    /** 
     * @brief 输出的混流只包含音频
     */
    kAudioOnly,
    /** 
     * @brief 输出的混流只包含视频
     */
    kVideoOnly,
};

/** 
 * @hidden
 * @type keytype
 * @brief 转推直播视频编码器格式。
 */
enum LiveTranscodingVideoCodec {
    /** 
     * @brief 使用 H264 编码格式
     */
    kLiveTranscondingH264,
    /** 
     * @brief 自定义编码器
     */
    kLiveTranscodingByteVC1,
};

/** 
 * @hidden
 * @type keytype
 * @brief 转推直播音频编码格式。
 */
enum LiveTranscodingAudioCodec {
    /** 
     * @brief 使用 AAC 编码格式
     */
    kLiveTranscodingAAC,
};

/** 
 * @hidden
 * @type keytype
 * @brief AAC 编码等级。
 */
enum LiveTranscodingAudioProfile {
    /** 
     * @brief 编码等级 AAC-LC （默认）
     */
    kLiveTranscodingAACLC,
    /** 
     * @brief 编码等级 AAC-MAIN
     */
    kLiveTranscodingAACMAIN,
    /** 
     * @brief 编码等级 HE-AAC v1
     */
    kLiveTranscodingHEV1,
    /** 
     * @brief 编码等级 HE-AAC v2
     */
    KLiveTranscodingHEV2,
};

/** 
 * @hidden
 * @type keytype
 * @brief 转推视频配置。
 */
struct LiveTranscodingVideoConfig {
    /** 
     * @brief 转推直播视频编码器格式。详见 LiveTranscodingVideoCodec{@link #LiveTranscodingVideoCodec}
     */
    LiveTranscodingVideoCodec codec;
    /** 
     * @brief 合流视频帧率信息
     */
    int fps;
    /** 
     * @brief 视频 I 帧间隔。
     */
    int gop;
    /** 
     * @brief 是否使用低延时特性。取值含义如下:  <br>
     *        + true: 使用低延时特性  <br>
     *        + false: 不使用低延时特性
     */
    bool low_latency;
    /** 
     *  @brief 合流视频码率，单位为 bps 。
     */
    int bitrate;
    /** 
     * @brief 宽（像素）
     */
    int width;
    /** 
     * @brief 高（像素）
     */
    int height;
};

/** 
 * @hidden
 * @type keytype
 * @brief 转推音频配置。
 */
struct LiveTranscodingAudioConfig {
    /** 
     * @brief 转推直播音频编码器格式。详见 LiveTranscodingAudioCodec{@link #LiveTranscodingAudioCodec}
     */
    LiveTranscodingAudioCodec codec = kLiveTranscodingAAC;
    /** 
     * @brief 合流音频码率，单位为 bps 。
     */
    int bitrate;
    /** 
     * @brief 音频帧采样率，单位 HZ。目前支持的采样率有：8000HZ， 16000HZ， 32000HZ， 44100HZ，48000HZ。
     */
    int sample_rate;
    /** 
     * @brief 音频声道数，可取 1 或 2。
     */
    int channels;
    /** 
     * @brief AAC 编码等级。详见 LiveTranscodingAudioProfile{@link #LiveTranscodingAudioProfile}
     */
    LiveTranscodingAudioProfile aac_profile = kLiveTranscodingAACLC;
};

/** 
 * @hidden
 * @type keytype
 * @brief 单个视频流在合流中的布局信息。
 */
struct LiveTranscodingRegion {
    /** 
     * @brief 视频流发布用户的用户 ID 。必填。
     */
    const char* uid = nullptr;
    /** 
     * @brief 视频流发布用户的房间 ID 。必填。
     */
    const char* roomId = nullptr;
    /** 
     * @brief 用户视频布局相对画布左侧的偏移量。相对值，范围为[0.0, 1.0]。
     */
    double x;
    /** 
     * @brief 用户视频布局相对画布顶端的偏移量。相对值，范围为[0.0, 1.0]。
     */
    double y;
    /** 
     * @brief 用户视频宽度相对用户原始视频宽度的比例。相对值，范围为[0.0, 1.0]。
     */
    double w;
    /** 
     * @brief 用户视频高度相对用户原始视频高度的比例。相对值，范围为[0.0, 1.0]。
     */
    double h;
    /** 
     * @brief 用户视频布局在画布中的层级。0为底层，值越大越上层，范围为[0, 100]。
     */
    int zorder;
    /** 
     * @brief 透明度。范围为 [0.0, 1.0]。
     */
    double alpha;
    /** 
     * @brief 转推直播包含内容。详见 LiveTranscodingContentControl{@link #LiveTranscodingContentControl}
     */
    LiveTranscodingContentControl content_control = kVideoAndAudio;
    /** 
     * @brief 渲染模式
     */
    RenderMode render_mode = kRenderModeHidden;
};

/** 
 * @hidden
 * @type keytype
 * @brief 转推流布局设置。
 */
struct LiveTranscodingLayout {
    /** 
     * @brief SEI 信息，长度不得超 4096 bytes
     */
    const char* app_data = nullptr;
    /** 
     * @brief 视频的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色
     */
    const char* background_color = nullptr;
    /** 
     * @brief 转推直播布局信息。详见 LiveTranscodingRegion{@link #LiveTranscodingRegion}
     */
    LiveTranscodingRegion* regions = nullptr;
    /** 
     * @brief 合流的数量
     */
    int regions_num = 0;
};

/** 
 * @hidden
 * @type keytype
 * @brief 转推直播配置信息。
 */
struct LiveTranscodingConfig {
    /** 
     * @brief 设置推流地址。
     */
    const char* url = nullptr;
    /** 
     * @brief 转推视频配置。详见 LiveTranscodingVideoConfig{@link #LiveTranscodingVideoConfig}
     */
    LiveTranscodingVideoConfig video_config;
    /** 
     * @brief 转推音频配置。详见 LiveTranscodingAudioConfig{@link #LiveTranscodingAudioConfig}
     */
    LiveTranscodingAudioConfig audio_config;
    /** 
     * @brief 转推流布局设置。详见 LiveTranscodingLayout{@link #LiveTranscodingLayout}
     */
    LiveTranscodingLayout layout;
    /** 
     * @hidden
     * @brief 设置动态扩展自定义参数。
     */
    const char* advanced_config = nullptr;
};

/** 
 * @hidden
 * @deprecated since 332.1, use VirtualBackgroundSourceType instead
 * @type keytype
 * @brief 背景模式
 */
enum BackgroundMode {
    /** 
     *@brief 无
     */
    kBackgroundModeNone = 0,
    /** 
     *@brief 虚化
     */
    kBackgroundModeBlur = 1,
    /** 
     *@brief 背景 1
     */
    kBackgroundModeA = 2,
    /** 
     *@brief 背景 2
     */
    kBackgroundModeB = 3,
};

/** 
 * @hidden
 * @deprecated since 332.1, use EnableVirtualBackground instead
 * @type keytype
 * @brief 分割模型
 */
enum DivideMode {
    /** 
     *@brief 自研
     */
    kDivideModeNone = 0,
    /**
     *@brief effect
     */
    kDivideModeEffect = 1,
};

/** 
 * @type keytype
 * @brief 流属性。  <br>
 */
struct MediaStreamInfo {
    /** 
     * @brief 发布此流的用户 ID 。
     */
    const char* user_id;
    /** 
     * @brief 此流是否为共享屏幕流。
     */
    bool is_screen;
    /** 
     * @brief 此流是否包括视频流。
     */
    bool has_video;
    /** 
     * @brief 流是否包括音频流。
     */
    bool has_audio;
    /** 
     * @brief 视频流的属性。  <br>
     *        当远端用户调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 方法发布多个配置的视频流时，此处会包含该用户发布的所有视频流的属性信息。
     *        参看 VideoSolutionDescription{@link #VideoSolutionDescription}。
     */
    VideoSolutionDescription* profiles;
    /** 
     * @brief 不同配置流的个数。  <br>
     *        当远端用户调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 方法发布多个配置的视频流时，此处会包含该用户发布的视频流的数目。
     */
    int profile_count;

    /** 
     * @brief 最大视频流的属性。  <br>
     *        since 336版本
     *        当远端用户开启带通道划分的大小流时，回调最大视频流属性信息。用户可以使用新的订阅方式，订阅任意不超过该分辨率的流。
     *        最终接收到的流，会受房间内其他用户的订阅行为的影响，综合确定一个最接近用户请求的分辨率的流。
     */
    VideoSolutionDescription max_profile;
};

/** 
 * @type keytype
 * @brief 视频订阅配置信息
 */
struct SubscribeVideoConfig {
    /** 
     * @brief 订阅的视频流分辨率下标。  <br>
     *        当远端用户通过调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
     *        默认值为 0，即订阅第一路流。  <br>
     *        如果不想更改之前的设置，可以输入 -1。  <br>
     */
    int video_index = 0;
    /** 
     * @brief 远端用户优先级，参看 RemoteUserPriority{@link #RemoteUserPriority}，默认值为 0。
     */
    int priority = 0;
    /** 
     * @hidden
     * @brief 构造函数
     */
    SubscribeVideoConfig() : video_index(0), priority(0) {
    }
    /**
     * @hidden
     */
    bool operator==(const SubscribeVideoConfig& config) const {
        bool result = video_index == config.video_index && priority == config.priority;
        return result;
    }
    /**
     * @hidden
     */
    bool operator!=(const SubscribeVideoConfig& config) const {
        bool result = (*this == config);
        return !result;
    }
};

/** 
 * @type keytype
 * @brief 手动订阅流的配置信息。  <br>
 */
struct SubscribeConfig {
    /** 
     * @brief 是否是屏幕流（默认为否）。  <br>
     */
    bool is_screen = false;
    /** 
     * @brief 是否订阅视频。  <br>
     */
    bool sub_video;
    /** 
     * @brief 是否订阅音频。  <br>
     */
    bool sub_audio;
    /** 
     * @brief 订阅的视频流分辨率下标。  <br>
     *        用户可以通过调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 方法在一路流中发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>
     */
    int video_index;
    /** 
     * @brief 远端用户的需求优先级，参看 RemoteUserPriority{@link #RemoteUserPriority}，默认值为 0 。  <br>
     *        当开启了订阅流回退选项功能（详见 SetSubscribeFallbackOption{@link #IRtcEngineLite#SetSubscribeFallbackOption} 方法），弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
     */
    int priority = 0;
    /** 
     * @brief 远端用户的时域分层，参看 SVCLayer{@link #SVCLayer}，默认值为 0 。  <br>
     *        仅码流支持SVC特性时可以生效。  <br>
     */
    int svc_layer = 0;
    /** 
     * @brief 期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。  <br>
     *        当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
     *        仅码流支持 SVC 分级编码特性时方可生效。
     */
    int framerate = 0;
    /** 
     * @brief 用户通过指定UI对应的最合适的流的宽度，单位：px
     */
    int sub_width = 0;
    /** 
     * @brief 用户通过指定UI对应的最合适的流的高度，单位：px
     */
    int sub_height = 0;
    /**
     * @hidden
     */
    int sub_video_index = -1;

public:
    /** 
     * @hidden
     * @brief 构造函数
     */
    SubscribeConfig() : is_screen(false), sub_video(true), sub_audio(true), video_index(0), priority(0) {
    }

    /** 
     * @hidden
     * @brief 构造函数
     */
    SubscribeConfig(bool is_screen, bool subvideo, bool subaudio, int videoindex)
            : is_screen(is_screen), sub_video(subvideo), sub_audio(subaudio), video_index(videoindex) {
    }

    /** 
     * @hidden
     * @brief 构造函数
     */
    SubscribeConfig(bool is_screen, bool subvideo, bool subaudio, int videoindex, int priority)
            : is_screen(is_screen),
              sub_video(subvideo),
              sub_audio(subaudio),
              video_index(videoindex),
              priority(priority) {
    }

    /** 
     * @hidden
     * @brief 构造函数
     */
    SubscribeConfig(bool is_screen, bool subvideo, bool subaudio, int videoindex,
     int priority,int svc_layer,int width,int height)
            : is_screen(is_screen),
              sub_video(subvideo),
              sub_audio(subaudio),
              video_index(videoindex),
              priority(priority),
              svc_layer(svc_layer),
              sub_width(width),
              sub_height(height) {
    }
    /**
     * @hidden
     */
    bool operator==(const SubscribeConfig& config) const {
        // sub_width * sub_height valid
        bool common_result = is_screen == config.is_screen && sub_video == config.sub_video
                                          && sub_audio == config.sub_audio && priority == config.priority
                                          && svc_layer == config.svc_layer && framerate == config.framerate;
        bool result;
        if(sub_width * sub_height > 0 && config.sub_width * config.sub_height > 0) {
          result = common_result && sub_width == config.sub_width && sub_height == config.sub_height ;
        }  else if((sub_width * sub_height == 0) && (config.sub_width * config.sub_height == 0) ) {
          result = common_result && video_index == config.video_index;
        } else {
          result = false;
        }
        return result;
    }

    /**
     * @hidden
     */
    bool operator!=(const SubscribeConfig& config) const {
        bool result = (*this == config);
        return !result;
    }
};

/** 
 * @type keytype
 * @brief 远端视频类型
 *      目前C++ sdk 只支持 kVideoStreamTypeHigh 类型
 */
enum VideoStreamType {
    /** 
     * @brief 高分辨率视频流
     */
    kVideoStreamTypeHigh = 0,
    /** 
     * @brief 低分辨率视频
     */
    kVideoStreamTypeLow = 1,
};
/** 
 * @type keytype
 * @brief 视频帧渲染设置。<br>
 *        调用 SetLocalVideoCanvas{@link #IRtcEngineLite#SetLocalVideoCanvas} 将视频流绑定到本地视图。
 */
struct VideoCanvas {
    /** 
     * @brief 本地视图句柄
     */
    void* view;
    /** 
     * @brief 视频渲染模式，参看 RenderMode{@link #RenderMode}
     */
    int render_mode;
    /** 
     * @brief 用于填充画布空白部分的背景颜色。取值范围是 `[0x0000000, 0xFFFFFFFF]`。默认值是 `0x00000000`。其中，透明度设置无效。
     */
    uint32_t background_color;
    /** 
     * @hidden
     * @brief 构造函数
     */
    VideoCanvas() : view(NULL), render_mode(kRenderModeHidden), background_color(0) {
    }
    /** 
     * @hidden
     * @brief 构造函数
     */
    VideoCanvas(void* v, int m, uint32_t c) : view(v), render_mode(m), background_color(c) {
    }
};

/** 
 * @type keytype
 * @brief Windows 窗口 id, Windows 平台下传 Windows 窗口句柄
 */
typedef void* view_t;

/** 
 * @type keytype
 * @brief 矩形，用于屏幕共享指定区域, 默认值表示抓取整个屏幕
 */
struct Rectangle {
    /** 
     * @brief 矩形区域左上角的 x 坐标
     */
    int x = 0;
    /** 
     * @brief 矩形区域左上角的 y 坐标
     */
    int y = 0;
    /** 
     * @brief 矩形宽度
     */
    int width = 0;
    /** 
     * @brief 矩形高度
     */
    int height = 0;
};

/** 
 * @type keytype
 * @brief 屏幕共享时的边框高亮设置
 */
struct HighlightConfig {
    /** 
     * @brief 是否显示高亮边框，默认显示。
     */
    bool enable_highlight = true;
    /** 
     * @brief 边框的颜色, 颜色格式为十六进制 ARGB:  0xAARRGGBB
     */
    uint32_t border_color = 0xFF29CCA3;
    /** 
     * @brief 边框的宽度，单位：像素
     */
    int border_width = 4;
};

/** 
 * @type keytype
 * @brief 抓取屏幕时排除指定窗口，默认不排除任何窗体
 */
struct ScreenFilterConfig {
    /** 
     * @brief 抓取屏幕时排除窗口列表。这个参数仅在抓取屏幕时生效。
     */
    view_t* excluded_window_list = nullptr;
    /** 
     * @brief 排除窗口的数量。
     */
    int excluded_window_num = 0;
};

/** 
 * @type keytype
 * @region 屏幕共享
 * @brief 内部采集屏幕视频流时，是否采集鼠标信息
 */
enum MouseCursorCaptureState {
    /** 
     * @brief 采集鼠标信息
     */
    kMouseCursorCaptureStateOn,
    /** 
     * @brief 不采集鼠标信息
     */
    kMouseCursorCaptureStateOff,
};

/** 
 * @hidden
 * @deprecated
 * @type keytype
 * @brief 屏幕共享参数
 */
struct ScreenParameters {
    /** 
     * @brief 编码帧率,单位为 fps
     */
    int frame_rate = 15;
    /** 
     * @brief 编码码率，小于 0 时 SDK 会根据高宽自适应码率, 单位 kbps
     */
    int kbitrate = -1;
};

/** 
 * @type keytype
 * @region 屏幕共享
 * @brief 内部采集屏幕视频流的内容类型。
 */
enum ContentHint {
    /** 
     * @brief 细节内容。当共享文档、图片时，建议使用该内容类型。
     */
    kContentHintDetails = 0,
    /** 
     * @brief 动画内容。当共享视频、游戏时，建议使用该内容类型。
     */
    kContentHintMotion,
};

/** 
 * @type keytype
 * @brief 屏幕共享内部采集参数
 */
struct ScreenCaptureParameters {
    /** 
     * @brief 内容类型，参看 ContentHint{@link #ContentHint}。
     */
    ContentHint content_hint = kContentHintDetails;
    /** 
     * @brief 采集区域，参看 Rectangle{@link #Rectangle}。
     */
    Rectangle region_rect;
    /** 
     * @brief 是否采集鼠标状态，参看 MouseCursorCaptureState{@link #MouseCursorCaptureState}。
     */
    MouseCursorCaptureState capture_mouse_cursor;
    /** 
     * @brief 屏幕过滤设置，参看 ScreenFilterConfig{@link #ScreenFilterConfig}。
     */
    ScreenFilterConfig filter_config;
    /** 
     * @brief 采集区域的边框高亮设置，参看 HighlightConfig{@link #HighlightConfig}。
     */
    HighlightConfig highlight_config;
};

/** 
 * @type keytype
 * @brief 屏幕共享的编码参数配置
 */
struct DesktopCaptureParameters {
    /** 
     * @brief 屏幕采集编码最大宽度
     */
    int max_width = 1920;
    /** 
     * @brief 屏幕采集编码最大高度
     */
    int max_height = 1080;
    /** 
     * @brief 屏幕采集编码帧率, 单位 fps
     */
    int frame_rate = 15;
    /** 
     * @brief 屏幕采集编码码率, -1 为自动码率, SDK 会根据宽高信息选择合适的码率，单位 kbps
     */
    int bitrate = -1;
    /** 
     * @brief 是否捕获鼠标光标
     */
    bool capture_mouse_cursor = true;
    /** 
     * @brief 抓取屏幕时排除窗口列表。这个参数仅在抓取屏幕时生效。
     */
    view_t* excluded_window_list = nullptr;
    /** 
     * @brief 抓取屏幕时排除的窗口数量。
     */
    int excluded_window_num = 0;
    /** 
     * @brief 高亮边框的配置
     */
    HighlightConfig highlight_config;
};

/** 
 * @type keytype
 * @brief 自定义视频渲染器
 */
class IVideoSink {
public:
/** 
 * @type keytype
 * @brief 视频帧编码格式
 */
enum PixelFormat {
    /** 
     * @brief YUV I420 格式
     */
    kI420 = VideoPixelFormat::kVideoPixelFormatI420,
    /** 
     * @brief 原始视频帧格式
     */
    kOriginal = VideoPixelFormat::kVideoPixelFormatUnknown,
};
    /** 
     * @type callback
     * @brief 视频帧回调
     * @param [out] videoFrame 视频帧结构类，参看 IVideoFrame{@link #IVideoFrame}
     * @return 返回值暂未使用
     */
    virtual bool OnFrame(IVideoFrame* videoFrame) = 0;
    /** 
     * @hidden
     * @type callback
     * @region 房间管理
     * @brief 获取外部渲染耗时。
     * @notes 获取外部渲染耗时进行上报。开发者需要自己计算平均渲染耗时。
     */
    virtual int GetRenderElapse() = 0;
    /** 
     * @type callback
     * @brief 释放渲染器。
     * @notes 通知开发者渲染器即将被废弃。收到该返回通知后即可释放资源。
     */
    virtual void Release() {
    }
    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IVideoSink() = default;
};

/** 
 * @hidden
 * @type keytype
 * @deprecated since 329.1, use MirrorType instead
 * @brief 是否开启镜像模式
 */
enum MirrorMode {
    /** 
     * @brief 不开启
     */
    kMirrorModeOff = 0,
    /** 
     * @brief 开启
     */
    kMirrorModeOn = 1,
};

/** 
 * @type keytype
 * @brief 镜像类型
 */
enum MirrorType {
    /** 
     * @brief 本地预览和编码传输时均无镜像效果
     */
    kMirrorTypeNone = 0,
    /** 
     * @brief 本地预览时有镜像效果，编码传输时无镜像效果
     */
    kMirrorTypeRender = 1,
    /** 
     * @brief 本地预览和编码传输时均有镜像效果
     */
    kMirrorTypeRenderAndEncoder = 3,
};

/** 
 * @type keytype
 * @brief 弱光适应类型
 */
enum AdjustedMode {
    /** 
     * @brief 关闭弱光适应
     */
    kAdjustedModeDisabled = 0,
    /** 
     * @brief 开启弱光适应
     */
    kAdjustedModeEnabled = 1,
};

/** 
 * @type keytype
 * @brief 视频输入源类型
 */
enum VideoSourceType {
    /** 
     * @brief 自定义采集视频源
     */
    VideoSourceTypeExternal = 0,
    /** 
     * @brief 内部采集视频源
     */
    VideoSourceTypeInternal = 1,
    /** 
     * @brief 自定义编码视频源。  <br>
     *        你仅需推送分辨率最大的一路编码后视频流，SDK 将自动转码生成多路小流
     */
    VideoSourceTypeEncodedWithAutoSimulcast = 2,
    /** 
     * @brief 自定义编码视频源。  <br>
     *        SDK 不会自动生成多路流，你需要自行生成并推送多路流
     */
    VideoSourceTypeEncodedWithoutAutoSimulcast = 3,
};

/** 
 * @type keytype
 * @brief 视频帧信息
 */
struct VideoFrameInfo {
    /** 
     * @brief 宽（像素）
     */
    int width = 0;
    /** 
     * @brief 高（像素）
     */
    int height = 0;
    /** 
     * @brief 视频帧顺时针旋转角度。参看 VideoRotation{@link #VideoRotation}。
     */
    VideoRotation rotation = VideoRotation::kVideoRotation0;
};

/** 
 * @type keytype
 * @brief 视频前处理配置参数。<br>
 */
struct VideoPreprocessorConfig {
    /** 
     * @brief 视频帧像素格式，参看 VideoPixelFormat{@link #VideoPixelFormat}
     */
    VideoPixelFormat required_pixel_format = kVideoPixelFormatUnknown;
};

/** 
 * @type keytype
 * @brief 自定义编码流信息
 */
struct VideoRateInfo {
    /** 
     * @brief 帧率，单位 fps
     */
    int fps;
    /** 
     * @brief 码率，单位 kbps
     */
    int bitrate_kbps;
};

/** 
 * @type keytype
 * @brief 视频解码方式
 */
enum VideoDecoderConfig {
    /** 
     * @brief 开启 SDK 内部解码，只回调解码后的数据
     */
    kVideoDecoderConfigRaw,
    /** 
     * @brief 开启自定义解码，只回调解码前数据
     */
    kVideoDecoderConfigEncode,
    /** 
     * @brief 开启 SDK 内部解码，同时回调解码前和解码后的数据
     */
    kVideoDecoderConfigBoth,
};

/** 
 * @hidden(Linux)
 * @type keytype
 * @brief 视频采集配置参数。<br>
 */
struct VideoCaptureConfig {
   /** 
    * @type keytype
    * @brief 视频采集模式
    */
   enum CapturePreference {
       /** 
        * @brief （默认）自动设置采集参数。
        *        SDK在开启采集时根据服务端下发的采集配置结合编码参数设置最佳采集参数。
        */
       KAuto = 0,
       /** 
        * @brief 手动设置采集参数，包括采集分辨率、帧率。
        */
       KManual = 1,
       /** 
        * @brief 采集参数与编码参数一致，即在 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 中设置的参数。
        */
       KAutoPerformance = 2,
    };
   /** 
    * @brief 视频采集模式，参看 CapturePreference{@link #CapturePreference}
    */
   CapturePreference capturePreference = CapturePreference::KAuto;

    /** 
     * @brief 视频采集分辨率的宽度，单位：px。
     */
    int width = 0;
    /** 
     * @brief 视频采集分辨率的高度，单位：px。
     */
    int height = 0;
    /** 
     * @brief 视频采集帧率，单位：fps。
    */
   int frameRate = 0;
};

/** 
 * @type keytype
 * @brief 本地录制的媒体类型
 */
enum RecordingType {
    /** 
     * @brief 只录制音频
     */
    kRecordAudioOnly = 0,
    /** 
     * @brief 只录制视频
     */
    kRecordVideoOnly = 1,
    /** 
     * @brief 同时录制音频和视频
     */
    kRecordVideoAndAudio = 2,
};

/** 
 * @type keytype
 * @brief 当前视频设备类型
 */
enum RTCVideoDeviceType {
    /** 
     * @brief 未知设备类型
     */
    kRTCVideoDeviceTypeUnknown = -1,
    /** 
     * @brief 视频渲染设备类型
     */
    kRTCVideoDeviceTypeRenderDevice = 0,
    /** 
     * @brief 视频采集设备类型
     */
    kRTCVideoDeviceTypeCaptureDevice = 1,
    /** 
     * @brief 屏幕流视频设备
     */
    kRTCVideoDeviceTypeScreenCaptureDevice = 2,
};

/** 
 * @hidden(Windows, MacOS, Linux)
 * @type keytype
 * @brief 视频旋转模式
 */
enum VideoRotationMode {
    /** 
     * @brief 跟随App界面方向
     */
    kVideoRotationModeFollowApp = 0,
    /** 
     * @brief 跟随设备重力方向
     */
    kVideoRotationModeFollowGSensor = 1,
};

/** 
 * @type keytype
 * @brief 媒体流类型
 */
enum MediaStreamType {
    /** 
     * @brief 只控制音频
     */
    kMediaStreamTypeAudio = 1 << 0,
    /** 
     * @brief 只控制视频
     */
    kMediaStreamTypeVideo = 1 << 1,
    /** 
     * @brief 同时控制音频和视频
     */
    kMediaStreamTypeBoth = kMediaStreamTypeAudio | kMediaStreamTypeVideo
};
/** 
 * @type keytype
 * @brief 占发布端原始帧率的比例
 */
enum FrameRateRatio {
  /** 
   * @brief 100%
   */
  kFrameRateRatioOriginal = 0,
  /** 
   * @brief 50%
   */
  kFrameRateRatioHalf = 1,
  /** 
   * @brief 25%
   */
  kFrameRateRatioQuarter = 2,
};
/**  
 * @type keytype
 * @brief 远端视频帧信息
 */
struct RemoteVideoConfig {
    /** 
     * @brief 期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。  <br>
     *        当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
     *        仅码流支持 SVC 分级编码特性时方可生效。
     */
    int framerate = 0;
    /** 
     * @brief 视频宽度，单位：px
     */
    int resolution_width = 0;
    /** 
     * @brief 视频高度，单位：px
     */
    int resolution_height = 0;
};
/**  
 * @type keytype
 * @brief 房间参数配置
 */
struct RTCRoomConfig {
    /** 
     * @brief 房间模式，参看 RoomProfileType{@link #RoomProfileType}，默认为 `kRoomProfileTypeCommunication`，进房后不可更改。
     */
     RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /** 
     * @brief 是否自动发布音视频流，默认为自动发布。 <br>
     *        若调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。
     */
   bool is_auto_publish = true;
    /** 
     * @brief 是否自动订阅音频流，默认为自动订阅。
     */
     bool is_auto_subscribe_audio = true;
    /** 
     * @brief 是否自动订阅主视频流，默认为自动订阅。  <br>
     *        屏幕流始终自动订阅，不受该方法影响。
     */
    bool is_auto_subscribe_video = true;
    /** 
     * @brief 远端视频流参数，参看 RemoteVideoConfig{@link #RemoteVideoConfig}
     */
    RemoteVideoConfig remote_video_config;
};
/** 
 * @type keytype
 * @brief 多房间参数配置
 */
struct MultiRoomConfig {
    /** 
     * @brief 房间模式，参看 RoomProfileType{@link #RoomProfileType}，默认为普通音视频通话模式，进房后不可更改。
     */
    RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /** 
     * @brief 是否自动订阅音频流，默认为自动订阅
     */
    bool is_auto_subscribe_audio = true;
    /** 
     * @brief 是否自动订阅视频流，默认为自动订阅
     */
    bool is_auto_subscribe_video = true;
    /** 
     * @brief 远端视频流参数，参看 RemoteVideoConfig{@link #RemoteVideoConfig}
     */
    RemoteVideoConfig remote_video_config;
};

/** 
 * @type keytype
 * @brief 屏幕采集的媒体类型
 */
enum ScreenMediaType {
    /** 
     * @brief 仅采集视频
     */
    kScreenMediaTypeVideoOnly = 0,
    /** 
     * @brief 仅采集音频
     */
    kScreenMediaTypeAudioOnly = 1,
    /** 
     * @brief 同时采集音频和视频
     */
    kScreenMediaTypeVideoAndAudio = 2,
};

}  // namespace bytertc

