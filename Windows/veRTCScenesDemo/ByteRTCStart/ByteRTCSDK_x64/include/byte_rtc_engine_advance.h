#ifndef BYTE_RTC_ENGINE_ADVANCE_H
#define BYTE_RTC_ENGINE_ADVANCE_H

#include "byte_rtc_engine_interface.h"

#include <stdint.h>
#if defined(BYTERTC_ANDROID)
#include "jni.h"
#endif

namespace bytertc {

/**
 * @hidden
 * @type keytype
 * @brief SDK 的服务器环境。
 */
enum ByteRtcEnv {
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

/**
 * @hidden
 * @type api
 * @region 网络连接
 * @brief 设置 SDK 当前使用的环境。
 * @param [in] env SDK 使用的环境参数，详见：ByteRtcEnv{@link #ByteRtcEnv} 。
 * @return
 *        0： 设置成功
 *        -1：设置失败
 * @notes
 *        1.本函数是可选函数，默认使用正式环境；
 *        2.本函数必须在创建 RtcEngine 实例 CreateByteRtcEngine{@link #CreateByteRtcEngine} 前调用。
 */
BYTE_API int SetEnv(ByteRtcEnv env);

/**
 * @hidden
 * @brief 设置端监控上报上下文
 * @param [in] project_key 调用app的project_key，每个app有自己特有的值
 * @param [in] device_id app根据当前软硬件环境生成的唯一设备id
 */
BYTE_API void SetLogReportContext(const char* project_key, const char* device_id);

/**
 * @hidden
 * @brief 设置应用的状态
 * @param [in] engine
 *       要通知的引擎
 * @param [in] appState 应用状态字符串
 */
BYTE_API void SetAppState(IRtcEngine* engine, const char* appState);

/**
 * @hidden
 * @type api
 * @region 频道管理
 * @brief 私有接口
 * @param [in] parameters JSON字符串
 */
BYTE_API int SetParameters(const char* parameters);

#if defined(BYTERTC_ANDROID)
/**
 * @type api
 * @region 视频管理
 * @brief 用于给编码器设置opengl context
 * @param [in] hardware_encoder
 *      java的Opengl Context对象
 * @return 
 *      true: 设置成功
 *      false：设置失败
 */
BYTE_API bool SetHardWareEncodeContext(jobject j_hardware_encoder);
#endif

/**
 * @hidden
 * @type api
 * @region 其他
 * @type keytype
 * @brief 硬件加速设备类型
 */
enum ByteHWDeviceType {
    /**
     * @brief 未知的设备类型
     */
    kByteHWDeviceTypeNone,

    /**
     * @brief direct3d 11 视频加速设备
     */
    kByteHWDeviceTypeD3D11,

    /**
     * @brief cuda 硬件加速设备
     * @notes cuda 是 nvidia 平台下硬件加速设备
     */
    kByteHWDeviceTypeCuda,

    /**
     * @brief intel 平台下 qsv 加速设备
     */
    kByteHWDeviceTypeQsv,

    /**
     * @brief windows 平台 dx 硬件加速设备
     */
    kByteHWDeviceTypeDxva2,

    /**
     * @brief Android 平台下硬件加速设备 mediacodec
     */
    kByteHWDeviceTypeMediaCodec,

    /**
     * @brief IOS、MACOS 平台下硬件加速设备 VideoToolbox
     */
    kByteHWDeviceTypeVideoToolbox,
     /**
     * @hidden
     * @brief android、linux 平台下硬件加速设备 egl context
     */
    kByteHWDeviceTypeEglContext,

    /**
     * @hidden
     * @brief linux、windows 平台下硬件加速设备 va context
     */
    kByteHWDeviceTypeVaapi,
};

/**
 * @hidden
 * @type keytype
 * @brief 硬编码设备 context
 */
enum ByteHWDeviceContextKey {
    /**
     * @hidden
     * @brief cuda context
     */
    kByteHWDeviceContextKeyCudaContext,
    /**
     * @hidden
     * @brief derict3D11 设备
     */
    kByteHWDeviceContextKeyD3D11Device,
    /**
     * @hidden
     * @brief derict3D11 设备 context
     */
    kByteHWDeviceContextKeyD3D11DeviceContext,
    /**
     * @hidden
     * @brief egl 设备 context
     */
    kByteHWDeviceContextKeyEglContext,
    /**
     * @hidden
     * @brief vadisplay 设备 context
     */
    kByteHWDeviceContextKeyVADisplay,
};

/**
 * @type keytype
 * @brief 硬件加速设备 context
 */
class IHWDeviceContext {
public:
    /**
     * @brief 获取硬件加速设备 context 类型
     * @return 硬件加速设备类型，详见 ByteHWDeviceType{@link #ByteHWDeviceType}
     */
    virtual ByteHWDeviceType device_type() const = 0;
    /**
     * @brief 设置属性
     * @param [in] key
     *        硬件加速设备 context 类型，详见ByteHWDeviceContextKey:{@link #ByteHWDeviceContextKey}
     * @param [in] value
     *        指向硬件加速设备 context 地址的指针
     */
    virtual void set_property(ByteHWDeviceContextKey key, void* value) = 0;
    /**
     * @brief 获取属性
     * @param [in] key
     *        硬件加速设备 context 类型，详见ByteHWDeviceContextKey:{@link #ByteHWDeviceContextKey}
     * @return 返回硬件加速设备 context 地址的指针
     */
    virtual void* get_property(ByteHWDeviceContextKey key) = 0;
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
BYTE_API IHWDeviceContext* CreateByteHwDeviceContext(ByteHWDeviceType device_type);

/**
 * @hidden
 * @brief 设置视频源的设备上下文信息
 * @param [in] engine
 *       要设置的引擎，详见：{@link #IRtcEngine}
 * @param [in] hw_context
 *        设置视频帧，详见：{@link #IHWDeviceContext}
 * @notes 用于硬件编码传入 GPU 内存时使用
 */
BYTE_API void SetVideoSourceHWDeviceContext(IRtcEngine* engine, IHWDeviceContext* hw_context);

/**
 * @type api
 * @region 视频管理
 * @brief 创建IByteVideoFrame
 * @param [in] builder
 *        视频帧构建实例，详见ByteVideoFrameBuilder{@link #ByteVideoFrameBuilder}
 */
BYTE_API IByteVideoFrame* BuildByteVideoFrame(const ByteVideoFrameBuilder& builder);

/**
 * @type api
 * @region 视频管理
 * @brief 发送外部源视频数据
 * @param [in] engine
 *       要设置的引擎，详见 IRtcEngine{@link #IRtcEngine}
 * @param [in] frame
 *        输入视频帧，详见 IByteVideoFrame{@link #IByteVideoFrame}
 * @notes
 *      1.支持 YUV420P，NV12，D3D texture，Cuda 内存，OpenGL texture等格式的视频帧。
 *      2.该函数运行在用户调用线程内
 */
BYTE_API bool PushExternalVideoFrame(IRtcEngine* engine, const IByteVideoFrame* frame);

/**
 * @hidden
 * @type keytype
 * @region 音频管理
 * @brief 音频编码类型
 */
enum ByteAudioCodecType {
    /**
     * @brief 未知编码类型
     */
    kByteAudioCodecTypeNone = 0,
    /**
     * @brief Opus 编码类型
     */
    kByteAudioCodecTypeOpus,
    /**
     * @brief AAC 编码类型
     */
    kByteAudioCodecTypeAac,
};

/**
 * @hidden
 * @type keytype
 * @region 视频管理
 * @brief 编码帧类型
 */
enum ByteVideoPictureType {
    /**
     * @brief 未知类型
     */
    kByteVideoPictureTypeUnknown = 0,
    /**
     * @brief I帧，视频关键帧，编解码不需要参考其他视频帧
     */
    kByteVideoPictureTypeI,
    /**
     * @brief P帧，视频参考帧，编解码需要参考前一帧视频帧
     */
    kByteVideoPictureTypeP,
    /**
     * @brief B帧，视频参考帧，编解码需要参考两个视频帧
     */
    kByteVideoPictureTypeB
};

/**
 * @hidden
 */
BYTE_API IByteAudioFrame* CreateByteAudioFrame();

/**
 * @hidden
 */
class IByteAudioStream {
public:
    /**
     * @hidden
     */
    virtual ~IByteAudioStream() {
    }
    /**
     * @hidden
     */
    virtual ByteAudioCodecType codec_type() const = 0;
    /**
     * @hidden
     */
    virtual void set_codec_type(ByteAudioCodecType codec_type) = 0;
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
    virtual void set_stream_memory(const ByteManagedMemory& memory) = 0;
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
BYTE_API IByteAudioStream* CreateByteAudioStream();

/**
 * @type api
 * @region 视频管理
 * @brief 视频流信息
 */
class IByteVideoStream {
public:
    /**
     * @brief 析构函数
     */
    virtual ~IByteVideoStream() {
    }
    /**
     * @brief 获取视频编码类型
     * @return [out] VideoCodecType
     *         视频编码类型 VideoCodecType:{@link #VideoCodecType}
     */
    virtual VideoCodecType codec_type() const = 0;
    /**
     * @brief 设置视频编码类型
     * @param [in] VideoCodecType
     *        视频编码类型 VideoCodecType:{@link #VideoCodecType}
     */
    virtual void set_codec_type(VideoCodecType codec_type) = 0;
    /**
     * @brief 获取视频采集时间戳
     * @return 视频采集时间戳，单位：微秒
     */
    virtual int64_t timestamp_us() const = 0;
    /**
     * @brief 设置视频帧采集时间戳
     * @param [in] timestamp_us
     *        视频采集时间戳，单位：微秒
     */
    virtual void set_timestamp_us(int64_t timestamp_us) = 0;
    /**
     * @brief 获取视频显示时间戳
     * @return 视频显示时间戳，单位：微秒
     */
    virtual int64_t timestamp_pts() const = 0;
    /**
     * @brief 设置视频显示时间戳
     * @param [in] timestamp_pts
     *        视频显示时间戳，单位：微秒
     */
    virtual void set_timestamp_pts(int64_t timestamp_pts) = 0;
    /**
     * @brief 获取视频解码时间戳
     * @return 视频解码时间戳，单位：微秒
     */
    virtual int64_t timestamp_dts() const = 0;
    /**
     * @brief 设置视频解码时间戳
     * @param timestamp_dts 视频解码时间戳，单位：微秒
     */
    virtual void set_timestamp_dts(int64_t timestamp_dts) = 0;
    /**
     * @brief 获取时间基分子
     * @return 时间基分子
     */
    virtual int timebase_num() const = 0;
    /**
     * @brief 设置时间基分子
     * @param [in] timebase_num
     *        时间基分子
     */
    virtual void set_timestamp_num(int timebase_num) = 0;
    /**
     * @brief 获取时间基分母
     * @return 时间基分母
     */
    virtual int timebase_den() const = 0;
    /**
     * @brief 设置时间基分母
     * @param [in] timebase_den
     *        时间基分母
     */
    virtual void set_timestamp_den(int timebase_den) = 0;
    /**
     * @brief 获取视频分辨率的宽度
     * @return 视频分辨率宽度
     */
    virtual int width() const = 0;
    /**
     * @brief 设置视频分辨率的宽
     * @param [in] width
     *        视频宽度
     */
    virtual void set_width(int width) = 0;
    /**
     * @brief 获取视频高度
     * @return 视频分辨率高度
     */
    virtual int height() const = 0;
    /**
     * @brief 设置视频高度
     * @param [in] height
     *        视频分辨率高度
     */
    virtual void set_height(int height) = 0;
    /**
     * @brief 获取视频编码格式
     * @return 视频编码格式，详见 ByteVideoPictureType：{@link #ByteVideoPictureType}
     */
    virtual ByteVideoPictureType picture_type() const = 0;
    /**
     * @brief 设置视频编码格式
     * @param [in] ByteVideoPictureType
     *        视频编码格式，详见 ByteVideoPictureType：{@link #ByteVideoPictureType}
     */
    virtual void set_picture_type(ByteVideoPictureType type) = 0;
    /**
     * @brief 获取视频帧旋转角度
     * @return 视频旋转角度，详见 VideoRotation{@link #VideoRotation}
     */
    virtual VideoRotation rotation() const = 0;
    /**
     * @brief 设置视频帧旋转角度
     * @param [in] VideoRotation
     *         视频旋转角度，详见 VideoRotation{@link #VideoRotation}
     */
    virtual void set_rotation(VideoRotation rotation) = 0;
    /**
     * @brief 设置视频帧内存管理方式
     * @param [in] ByteManagedMemory
     *         视频帧内存管理信息，详见 ByteManagedMemory{@link #ByteManagedMemory}
     */
    virtual void set_stream_memory(const ByteManagedMemory& memory) = 0;
    /**
     * @brief 获取视频数据指针地址
     * @return  视频数据指针地址
     */
    virtual uint8_t* data() const = 0;
    /**
     * @brief 获取视频数据大小
     * @return  视频数据大小
     */
    virtual int data_size() const = 0;
};

/**
 * @hidden
 */
BYTE_API IByteVideoStream* CreateByteVideoStream();

/**
 * @hidden
 * @type callback
 * @region 音频数据回调
 * @brief 音频数据回调观察者
 */
class IAudioStreamObserver {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioStreamObserver() {
    }

    /**
     * @hidden
     * @type callback
     * @region 音频数据回调
     * @brief 获得单个用户的音频数据
     * @param [in] type，相机流或者屏幕流，详见ByteStreamType{@link #ByteStreamType}
     * @param [in] audio_stream 音频数据，详见：IByteAudioStream{@link #IByteAudioStream}
     * @notes 该回调收到编码后的音频数据， 如AAC、Opus等
     */
    virtual void OnLocalAudioStream(ByteStreamType type, const IByteAudioStream& audio_stream) = 0;

    /**
     * @hidden
     * @type callback
     * @region 音频数据回调
     * @brief 获得单个用户的音频数据
     * @param [in] stream_id, 流ID
     * @param [in] audio_stream 音频数据，详见：IByteAudioStream{@link #IByteAudioStream}
     * @param [in] stream_info, 该音频流的业务信息, 详见：ByteStreamInfo{@link #ByteStreamInfo}
     * @notes 该回调收到编码后的音频数据， 如AAC、Opus等
     */
    virtual void OnRemoteAudioStream(
            const char* stream_id, const IByteAudioStream& audio_stream, const ByteStreamInfo& stream_info) = 0;
};

/**
 * @hidden
 * @type api
 * @region 音频数据回调
 * @brief 注册音频数据回调观察者
 * @param [in] engine 要设置的引擎，详见：IRtcEngine{@link #IRtcEngine}
 * @param [in] observer 音频数据回调观察者，详见：IAudioStreamObserver{@link #IAudioStreamObserver}
 * @notes 注册该回调，可以收到编码后的音频数据， 如AAC、Opus等
 */
BYTE_API void RegisterAudioStreamObserver(IRtcEngine* engine, IAudioStreamObserver* observer);

/**
 * @hidden
 * @type callback
 * @region 视频管理
 */
class IVideoStreamObserver {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IVideoStreamObserver() {
    }
    /**
     * @hidden
     * @type callback
     * @region 视频管理
     * @brief 本地视频流回调
     * @param type
     *        视频流类型，详见 ByteStreamType{@link #ByteStreamType}
     * @param video_stream
     *        视频流数据帧，详见 IByteVideoStream{@link #IByteVideoStream}
     */
    virtual void OnLocalVideoStream(ByteStreamType type, const IByteVideoStream& video_stream) = 0;
    /**
     * @hidden
     * @type callback
     * @region 视频管理
     * @brief 远端视频流回调
     * @param stream_id
     *        视频流id，表示视频流
     * @param video_stream
     *        视频流数据帧，详见 IByteVideoStream{@link #IByteVideoStream}
     * @param stream_info
     *        视频流信息，详见 ByteStreamInfo{@link #ByteStreamInfo}
     */
    virtual void OnRemoteVideoStream(
            const char* stream_id, const IByteVideoStream& video_stream, const ByteStreamInfo& stream_info) = 0;
};

/**
 * @hidden
 * @type api
 * @region 视频管理
 * @brief 注册视频流观察者实例对象
 * @param engine
 *        视频引擎指针，详见 IRtcEngine{@link #IRtcEngine}
 * @param observer
 *        视频流观察者实例对象指针，详见 IVideoStreamObserver{@IVideoStreamObserver #IVideoStreamObserver}
 */
BYTE_API void RegisterVideoStreamObserver(IRtcEngine* engine, IVideoStreamObserver* observer);

/**
 * @hidden
 */
BYTE_API bool PushExternalAudioStream(IRtcEngine* engine, const IByteAudioStream* audio_stream);

/**
 * @hidden
 * @type api
 * @region 视频管理
 * @brief 推送视频流数据帧
 * @param engine
 *        引擎实例指针，详见 IRtcEngine{@link #IRtcEngine}
 * @param video_stream
 *        视频流数据帧，详见 IByteVideoStream{@link #IByteVideoStream}
 */
BYTE_API bool PushExternalVideoStream(IRtcEngine* engine, const IByteVideoStream* video_stream);

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
BYTE_API void SetupEngineMediaIo(IRtcEngine* engine, const MediaIoOption& option);

/**
 * @type keytype
 * @region 视频数据回调
 * @brief metadata 数据大小最大值
 */
const int BYTE_MAX_METADATA_LENGTH = 1024;



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
 * @type api
 * @brief 音频设备管理接口创建，该接口不依赖引擎，主要用于无引擎下的音频设备管理
 * @param [in] handler
 *       音频设备的事件回调
 * @return 音频设备管理接口
 */
BYTE_API IAudioDeviceManager* CreateAudioDeviceManager(IAudioDeviceEventHandler* handler);

}  // namespace bytertc
#endif  // I_BYTE_RTC_ENGINE
