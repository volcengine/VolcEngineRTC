/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Advance API
*/

#pragma once

#ifndef BYTE_RTC_ADVANCE_H__
#define BYTE_RTC_ADVANCE_H__

#include "bytertc_engine_interface.h"

#include <stdint.h>
#ifdef __ANDROID__
#include "jni.h"
#endif


#ifdef __GNUC__
#    define attribute_deprecated __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#else
#    define attribute_deprecated
#endif

namespace bytertc {

/**
 * @hidden
 * @type
 * @brief RTC Audio Dump 节点配置。
 * 要与bae_audio_sample_interface中
 * 的AudioSampleType枚举和AudioSampleConfigure保持一致。
 */
struct RTCAudioSampleConfigure {
    /**
     * @hidden
     */
    bool aec_near_in_enable = false;
    /**
     * @hidden
     */
    bool aec_far_in_enable = false;
    /**
     * @hidden
     */
    bool aec_far_in_ref_enable = false;
    /**
     * @hidden
     */
    bool aec_out_enable = false;
    /**
     * @hidden
     */
    bool agc_out_enable = false;
    /**
     * @hidden
     */
    bool ns_out_enable = false;
    /**
     * @hidden
     */
    bool ainr_out_enable = false;
    /**
     * @hidden
     */
    bool mix_out_enable = false;
    /**
     * @hidden
     */
    bool send2encoder_enable = false;
    /**
     * @hidden
     */
    bool audio_share_in_enable = false;
    /**
     * @hidden
     */
    bool audio_share_win_ref_enable = false;
    /**
     * @hidden
     */
    bool audio_share_out_enable = false;
    /**
     * @hidden
     */
    bool external_audio_in_enable = false;
    /**
     * @hidden
     */
    bool pitchfilter_out_enable = false;
    /**
     * @hidden
     */
    bool decoder_out_enable = false;
    /**
     * @hidden
     */
    void reset() {
        aec_near_in_enable = false;
        aec_far_in_enable = false;
        aec_far_in_ref_enable = false;
        aec_out_enable = false;
        agc_out_enable = false;
        ns_out_enable = false;
        ainr_out_enable = false;
        mix_out_enable = false;
        send2encoder_enable = false;
        audio_share_in_enable = false;
        audio_share_win_ref_enable = false;
        audio_share_out_enable = false;
        external_audio_in_enable = false;
        pitchfilter_out_enable = false;
        decoder_out_enable = false;
    }
    /**
     * @hidden
     */
    void NormalMode() {
        aec_near_in_enable = true;
        aec_far_in_ref_enable = true;
        mix_out_enable = true;
    }
    /**
     * @hidden
     */
    void AllMode() {
        aec_near_in_enable = true;
        aec_far_in_enable = true;
        aec_far_in_ref_enable = true;
        aec_out_enable = true;
        agc_out_enable = true;
        ns_out_enable = true;
        ainr_out_enable = true;
        mix_out_enable = true;
        send2encoder_enable = true;
        audio_share_in_enable = true;
        audio_share_win_ref_enable = true;
        audio_share_out_enable = true;
        external_audio_in_enable = true;
        pitchfilter_out_enable = true;
        decoder_out_enable = true;
    }
};

/**
 * @hidden
 * @type keytype
 * @brief SDK 的服务器环境。
 */
enum Env {
    /**
     * @hidden
     * @brief 线上环境。
     */
    kEnvProduct = 0,
    /**
     * @hidden
     * @brief BOE 环境。
     */
    kEnvBOE,
    /**
     * @hidden
     * @brief 测试环境。
     */
    kEnvTest
};

attribute_deprecated
/**
 * @hidden
 * @deprecated
 * @type api
 * @region 引擎管理
 * @brief 设置 SDK 当前使用的环境。
 * @param [in] env SDK 使用的环境参数，详见：Env{@link #Env} 。
 * @return
 *        0： 设置成功
 *        -1：设置失败
 * @notes
 *        1.本函数是可选函数，默认使用正式环境；
 *        2.本函数必须在创建 RtcEngine 实例 CreateRtcEngine{@link #CreateRtcEngine} 前调用。
 */
BYTERTC_API int SetEnv(Env env);

attribute_deprecated
/**
 * @hidden
 * @deprecated
 * @brief 设置设备ID
 * @param [in] device_id app根据当前软硬件环境生成的唯一设备id
 */
BYTERTC_API void SetDeviceId(const char* device_id);
/**
 * @hidden
 * @brief 设置应用的状态
 * @param [in] engine
 *       要通知的引擎
 * @param [in] appState 应用状态字符串
 */
BYTERTC_API void SetAppState(IRtcEngine* engine, const char* appState);

attribute_deprecated
/**
 * @hidden
 * @deprecated
 * @type api
 * @region 房间管理
 * @brief 私有接口
 * @param [in] parameters JSON字符串
 */
BYTERTC_API int SetParameters(const char* parameters);

#ifdef __ANDROID__
/**
 * @type api
 * @region 视频管理
 * @brief 用于给编码器设置共享的EGLContext，该接口需要传入一个 android.opengl.EGLContext 类型的EGLContext
 * 如果只有C++的EGLContext，则需要在绑定了EGLContext的线程环境下执行 SetHardWareEncodeContext() 方法设置。
 * 设置后，RTC的编码器即可和当前的EGLContext共享资源。
 * 如果Android使用纯C++接口，则该方法必须在引擎创建前设置，用于初始化EGLContext，如果没有共享的EGLContext，参数传递nullptr即可
 * 引擎销毁后，应该调用 ClearHardWareEncodeContext() 来进行资源释放
 * @param [in] j_egl_context
 *      传入Java的 android.opengl.EGLContext 类型的EGLContext
 * @return
 *      true: 设置成功
 *      false：设置失败
 */
BYTERTC_API bool SetHardWareEncodeContext(jobject j_egl_context);

/**
 * @type api
 * @region 视频管理
 * @brief 用于给编码器设置共享的EGLContext，该接口需要在绑定了EGLContext的接口下执行方法设置。
 * 设置后，RTC的编码器即可和当前的EGLContext共享资源。
 * 如果Android使用纯C++接口，则该方法必须在引擎创建前设置，如果没有绑定了EGLContext的线程环境，可以使用参数为jobject的接口替代
 * 引擎销毁后，应该调用 ClearHardWareEncodeContext() 来进行资源释放
 * @return
 *      true: 设置成功
 *      false：设置失败
 */
BYTERTC_API bool SetHardWareEncodeContext();

/**
 * @type api
 * @region 视频管理
 * @brief 用于清除共享的EGLContext，在引擎销毁后，如果确定之后不会再使用 则应该调用本接口在进行EGLContext的资源释放
 */
BYTERTC_API void ClearHardWareEncodeContext();

/**
 * @type api
 * @region 引擎管理
 * @brief 用于设置Android的ApplicationContext给Engine使用，
 * 如果Android使用纯C++接口，则该方法必须在引擎创建前设置
 * @param [in] j_egl_context
 *      传入Java的 android.content.Context 类型的EGLContext
 */
BYTERTC_API void SetApplicationContext(jobject j_application_context);
#endif

/**
 * @hidden
 * @type api
 * @region 视频管理
 * @type keytype
 * @brief 硬件加速设备类型
 */
enum HWDeviceType {
    /**
     * @brief 未知的设备类型
     */
    kHWDeviceTypeNone,

    /**
     * @brief direct3d 11 视频加速设备
     */
    kHWDeviceTypeD3D11,

    /**
     * @brief cuda 硬件加速设备
     * @notes cuda 是 nvidia 平台下硬件加速设备
     */
    kHWDeviceTypeCuda,

    /**
     * @brief intel 平台下 qsv 加速设备
     */
    kHWDeviceTypeQsv,

    /**
     * @brief windows 平台 dx 硬件加速设备
     */
    kHWDeviceTypeDxva2,

    /**
     * @brief Android 平台下硬件加速设备 mediacodec
     */
    kHWDeviceTypeMediaCodec,

    /**
     * @brief IOS、MACOS 平台下硬件加速设备 VideoToolbox
     */
    kHWDeviceTypeVideoToolbox,
     /**
     * @hidden
     * @brief android、linux 平台下硬件加速设备 egl context
     */
    kHWDeviceTypeEglContext,

    /**
     * @hidden
     * @brief linux、windows 平台下硬件加速设备 va context
     */
    kHWDeviceTypeVaapi,
};

/**
 * @hidden
 * @type keytype
 * @brief 硬编码设备 context
 */
enum HWDeviceContextKey {
    /**
     * @hidden
     * @brief cuda context
     */
    kHWDeviceContextKeyCudaContext,
    /**
     * @hidden
     * @brief derict3D11 设备
     */
    kHWDeviceContextKeyD3D11Device,
    /**
     * @hidden
     * @brief derict3D11 设备 context
     */
    kHWDeviceContextKeyD3D11DeviceContext,
    /**
     * @hidden
     * @brief egl 设备 context
     */
    kHWDeviceContextKeyEglContext,
    /**
     * @hidden
     * @brief vadisplay 设备 context
     */
    kHWDeviceContextKeyVADisplay,
};

/**
 * @hidden
 * @type keytype
 * @brief 硬件加速设备 context
 */
class IHWDeviceContext {
public:
    /**
     * @brief 获取硬件加速设备 context 类型
     * @return 硬件加速设备类型，详见 HWDeviceType{@link #HWDeviceType}
     */
    virtual HWDeviceType device_type() const = 0;
    /**
     * @brief 设置属性
     * @param [in] key
     *        硬件加速设备 context 类型，详见 ByteRTCHWDeviceContextKey:{@link #ByteRTCHWDeviceContextKey}
     * @param [in] value
     *        指向硬件加速设备 context 地址的指针
     */
    virtual void set_property(HWDeviceContextKey key, void* value) = 0;
    /**
     * @brief 获取属性
     * @param [in] key
     *        硬件加速设备 context 类型，详见 ByteRTCHWDeviceContextKey:{@link #ByteRTCHWDeviceContextKey}
     * @return 返回硬件加速设备 context 地址的指针
     */
    virtual void* get_property(HWDeviceContextKey key) = 0;
    /**
     * @brief 内部 context 是否由该实例拥有
     * @return  <br>
     *        + true: 硬件设备 context 被实例对象拥有  <br>
     *        + false: 硬件设备上 context 文不被实例对象拥有  <br>
     */
    virtual bool own_context() const = 0;
    /**
     * @brief 设置 context 是否被实例对象拥有
     * @param  [in] own_context  <br>
     *       + true: context 被实例对象拥有  <br>
     *       + false: context 不被实例对象拥有  <br>
     */
    virtual void set_own_context(bool own_context) = 0;
    /**
     * @brief 转移硬件设备 context，
     * @return 指向硬件设备 context 的指针
     */
    virtual IHWDeviceContext* move_context() = 0;
    /**
     * @brief 释放实例对象
     */
    virtual void release() = 0;
};

/**
 * @hidden
 * @brief create a hardware device context with specified device_type
 */
BYTERTC_API IHWDeviceContext* CreateHwDeviceContext(HWDeviceType device_type);

/**
 * @hidden
 * @brief 设置视频源的设备上下文信息
 * @param [in] engine
 *       要设置的引擎，详见：{@link #IRtcEngine}
 * @param [in] hw_context
 *        设置视频帧，详见：{@link #IHWDeviceContext}
 * @notes 用于硬件编码传入 GPU 内存时使用
 */
BYTERTC_API void SetVideoSourceHWDeviceContext(IRtcEngine* engine, IHWDeviceContext* hw_context);

/**
 * @type api
 * @region 视频管理
 * @brief 创建 IVideoFrame
 * @param [in] builder 视频帧构建实例，参看 VideoFrameBuilder{@link #VideoFrameBuilder}
 */
BYTERTC_API IVideoFrame* BuildVideoFrame(const VideoFrameBuilder& builder);

/**
 * @type api
 * @region 视频管理
 * @brief 发送外部源视频数据
 * @param [in] engine
 *       要设置的引擎，详见 IRtcEngine{@link #IRtcEngine}
 * @param [in] frame
 *        输入视频帧，详见 IVideoFrame{@link #IVideoFrame}
 * @notes
 *      1.支持 YUV420P，NV12，D3D texture，Cuda 内存，OpenGL texture等格式的视频帧。
 *      2.该函数运行在用户调用线程内
 */
BYTERTC_API bool PushExternalVideoFrame(IRtcEngine* engine, const IVideoFrame* frame);

/**
 * @hidden
 * @type keytype
 * @region 音频管理
 * @brief 音频编码类型
 */
enum AudioCodecType {
    /**
     * @brief 未知编码类型
     */
    kAudioCodecTypeNone = 0,
    /**
     * @brief Opus 编码类型
     */
    kAudioCodecTypeOpus,
    /**
     * @brief AAC 编码类型
     */
    kAudioCodecTypeAac,
};

/**
 * @hidden
 */
BYTERTC_API IAudioFrame* BuildAudioFrame(const AudioFrameBuilder& builder);

/**
 * @hidden
 * @type keytype
 * @brief 音频帧信息
 */
class IEncodedAudioFrame {
public:
    /**
     * @hidden
     */
    virtual ~IEncodedAudioFrame() {
    }
    /**
     * @hidden
     */
    virtual AudioCodecType codec_type() const = 0;
    /**
     * @hidden
     */
    virtual void set_codec_type(AudioCodecType codec_type) = 0;
    /**
     * @hidden
     */
    virtual int sample_rate() const = 0;
    /**
     * @hidden
     */
    virtual void set_sample_rate(int sample_rate) = 0;
    /**
     * @hidden
     */
    virtual int channels_num() const = 0;
    /**
     * @hidden
     */
    virtual void set_channels_num(int channels_num) = 0;
    /**
     * @hidden
     */
    virtual int64_t timestamp_us() const = 0;
    /**
     * @hidden
     */
    virtual void set_timestamp_us(int64_t timestamp_us) = 0;
    /**
     * @hidden
     */
    virtual int64_t timestamp_pts() const = 0;
    /**
     * @hidden
     */
    virtual void set_timestamp_pts(int64_t timestamp_pts) = 0;
    /**
     * @hidden
     */
    virtual int timebase_num() const = 0;
    /**
     * @hidden
     */
    virtual void set_timestamp_num(int timebase_num) = 0;
    /**
     * @hidden
     */
    virtual int timebase_den() const = 0;
    /**
     * @hidden
     */
    virtual void set_timestamp_den(int timebase_den) = 0;

    /**
     * @hidden
     */
    virtual void set_stream_memory(const ManagedMemory& memory) = 0;
    /**
     * @hidden
     */
    virtual uint8_t* data() const = 0;
    /**
     * @hidden
     */
    virtual int data_size() const = 0;
};

/**
 * @hidden
 */
BYTERTC_API IEncodedAudioFrame* CreateEncodedAudioFrame();

/**
 * @hidden
 */
BYTERTC_API IEncodedVideoFrame* BuildEncodedVideoFrame(const EncodedVideoFrameBuilder& builder);

/**
 * @hidden
 * @type callback
 * @region 音频数据回调
 * @brief 本地音频帧监测器
 */
class ILocalEncodedAudioFrameObserver  {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~ILocalEncodedAudioFrameObserver() {
    }

    /**
     * @hidden
     * @type callback
     * @region 音频数据回调
     * @brief 调用 RegisterLocalEncodedAudioFrameObserver{@link #RegisterLocalEncodedAudioFrameObserver} 后，SDK 收到本地音频帧信息时，回调该事件
     * @param [in] type 本地音频帧类型，参看 StreamIndex{@link #StreamIndex}
     * @param [in] audio_stream 本地音频帧信息，参看 IEncodedAudioFrame{@link #IEncodedAudioFrame}
     */
    virtual void OnLocalEncodedAudioFrame(StreamIndex type, const IEncodedAudioFrame& audio_stream) = 0;
};

/**
 * @hidden
 * @type callback
 * @region 音频数据回调
 * @brief 远端音频帧监测器
 */
class IRemoteEncodedAudioFrameObserver  {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRemoteEncodedAudioFrameObserver () {
    }

    /**
     * @hidden
     * @type callback
     * @region 音频数据回调
     * @brief 调用 RegisterRemoteEncodedAudioFrameObserver{@link #RegisterRemoteEncodedAudioFrameObserver} 后，SDK 收到远端音频帧信息时，回调该事件
     * @param [in] stream_id 收到的远端音频流的 ID
     * @param [in] audio_stream 远端音频帧信息，参看 IEncodedAudioFrame{@link #IEncodedAudioFrame}
     * @param [in] stream_info 收到的远端音频流的信息，参看 RemoteStreamKey{@link #RemoteStreamKey}
     */
    virtual void OnRemoteEncodedAudioFrame(
            const char* stream_id, const IEncodedAudioFrame& audio_stream, const RemoteStreamKey& stream_info) = 0;
};


/**
 * @hidden
 * @type api
 * @region 音频数据回调
 * @brief 注册远端音频帧监测器。  <br>
 *        调用该方法后，SDK 每监测到一帧远端音频帧时，都会将音频帧信息通过 OnRemoteEncodedAudioFrame{@link #OnRemoteEncodedAudioFrame} 回调给用户
 * @param [in] engine 需设置的引擎，参看 IRtcEngine{@link #IRtcEngine}
 * @param [in] observer 远端音频帧监测器，参看 IRemoteEncodedAudioFrameObserver{@link #IRemoteEncodedAudioFrameObserver}
 * @notes  <br>
 *       + 该方法建议在进房前调用。 <br>
 *       + 将参数设置为 nullptr 则取消注册。
 */
BYTERTC_API void RegisterRemoteEncodedAudioFrameObserver(IRtcEngine* engine, IRemoteEncodedAudioFrameObserver* observer);

/**
 * @hidden
 * @type api
 * @region 音频数据回调
 * @brief 注册本地音频帧监测器。  <br>
 *        调用该方法后，SDK 每监测到一帧本地音频帧时，都会将音频帧信息通过 OnLocalEncodedAudioFrame{@link #OnLocalEncodedAudioFrame} 回调给用户
 * @param [in] engine 需设置的引擎，参看 IRtcEngine{@link #IRtcEngine}
 * @param [in] observer 本地音频帧监测器，参看 ILocalEncodedAudioFrameObserver{@link #ILocalEncodedAudioFrameObserver}
 * @notes  <br>
 *       + 该方法建议在进房前调用。 <br>
 *       + 将参数设置为 nullptr 则取消注册。
 */
BYTERTC_API void RegisterLocalEncodedAudioFrameObserver(IRtcEngine* engine, ILocalEncodedAudioFrameObserver* observer);


/**
 * @hidden
 */
BYTERTC_API bool PushExternalEncodedAudioFrame(IRtcEngine* engine, const IEncodedAudioFrame* audio_stream);

/**
 * @hidden
 * @type api
 */
struct MediaIoOption {
    /**
     * @hidden
     */
    bool enable_audio_encoding = true;
    /**
     * @hidden
     */
    bool enable_video_encoding = true;
    /**
     * @hidden
     */
    bool enable_audio_decoding = true;
    /**
     * @hidden
     */
    bool enable_video_decoding = true;
};

/**
 * @hidden
 * @type api
 */
BYTERTC_API void SetupEngineMediaIo(IRtcEngine* engine, const MediaIoOption& option);

/**
 * @type keytype
 * @region 视频数据回调
 * @brief metadata 数据大小最大值
 */
const int MAX_METADATA_LENGTH = 1024;


/**
 * @hidden
 * @type callback
 * @brief 音频设备事件回调
 */
class IAudioDeviceEventHandler {
public:
    /**
     * @hidden
     * @type callback
     * @brief 获得麦克风音量
     * @param [in] volume
     *       音量大小
     */
    virtual void OnRecordingAudioVolumeIndication(int volume) = 0;

    /**
     * @hidden
     * @type callback
     * @brief 获得Loopback音量
     * @param [in] volume
     *       音量大小
     */
    virtual void OnLoopbackAudioVolumeIndication(int volume) = 0;
};

/**
 * @hidden
 * @type callback
 */
class IAudioDeviceManagerEx : public IAudioDeviceManager {
public:
    /**
     * @hidden
     * @region 音频设备管理
     * @brief 构造函数
     */
    IAudioDeviceManagerEx() = default;

    /**
     * @hidden
     * @type api
     * @region 音频设备管理
     * @brief 析构当前对象，释放内存
     * @notes 该结构不需要的时候应该调用本函数释放音频操作相关的资源
     */
    virtual void Release() = 0;

    /**
     * @hidden
     * @type api
     * @region 音频设备管理
     * @brief 切换音频播放到扬声器或者听筒，默认播放设备是扬声器
     * @param [in] enable  <br>
     *       + true：切换至扬声器  <br>
     *       + false：切换至听筒  <br>
     * @notes 本方法只在移动设备上有效
     */
    virtual void SetEnableSpeakerphone(bool enable) = 0;

protected:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioDeviceManagerEx() = default;
};

/**
 * @hidden
 * @type api
 * @brief 音频设备管理接口创建，该接口不依赖引擎，主要用于无引擎下的音频设备管理
 * @param [in] handler
 *       音频设备的事件回调
 * @return 音频设备管理接口
 */
BYTERTC_API IAudioDeviceManagerEx* CreateAudioDeviceManager(IAudioDeviceEventHandler* handler);

}  // namespace bytertc

#endif  // BYTE_RTC_ADVANCE_H__
