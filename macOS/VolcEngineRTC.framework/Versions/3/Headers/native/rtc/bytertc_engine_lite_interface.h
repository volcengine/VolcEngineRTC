/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Interface Lite
 */

#pragma once

#ifndef BYTE_RTC_LITE_INTERFACE_H__
#define BYTE_RTC_LITE_INTERFACE_H__

#include "bytertc_room_interface.h"
#include "bytertc_device_manager.h"
#include "bytertc_audio_frame.h"
#include "byte_rtc_asr_engine_event_handler.h"
#include "bytertc_audio_mixing_manager.h"
#include "bytertc_video_processor_interface.h"
#include "bytertc_position_audio_render_interface.h"

namespace bytertc {

/**
 * @type callback
 * @brief 自定义编码帧回调类
 */
class IExternalVideoEncoderEventHandler {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IExternalVideoEncoderEventHandler(){}
    /**
     * @type callback
     * @region 视频管理
     * @brief 提示自定义编码帧可以开始推送的回调。  <br>
     *        收到该回调后，你即可调用 PushExternalEncodedVideoFrame{@link #IRtcEngineLite#PushExternalEncodedVideoFrame} 向 SDK 推送自定义编码视频帧
     * @param [in] index 可以推送的编码流的属性，参看 StreamIndex{@link #StreamIndex}
     */
    virtual void OnStart(StreamIndex index) = 0;
    /**
     * @type callback
     * @region 视频管理
     * @brief 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧
     * @param [in] index 需停止推送的编码流的属性，参看 StreamIndex{@link #StreamIndex}
     */
    virtual void OnStop(StreamIndex index) = 0;
    /**
     * @type callback
     * @region 视频管理
     * @brief 当自定义编码流的帧率或码率发生变化时，触发该回调
     * @param [in] index 发生变化的编码流的属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] video_index 对应编码流的下标
     * @param [in] info 变化后的编码流信息，参看 VideoRateInfo{@link #VideoRateInfo}
     */
    virtual void OnRateUpdate(StreamIndex index, int32_t video_index, VideoRateInfo info) = 0;
    /**
     * @type callback
     * @region 视频管理
     * @brief 调用 RequestRemoteVideoKeyFrame{@link #IRtcEngineLite#RequestRemoteVideoKeyFrame} 请求远端关键帧时，会触发该回调
     * @param [in] index 远端编码流的属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] video_index 对应编码流的下标
     */
    virtual void OnRequestKeyFrame(StreamIndex index, int32_t video_index) = 0;
};

/**
 * @type callback
 * @region 视频数据回调
 * @brief 本地视频帧监测器
 */
class ILocalEncodedVideoFrameObserver {
public:
    /**
     * @brief 析构函数
     */
    virtual ~ILocalEncodedVideoFrameObserver() {
    }
    /**
     * @type callback
     * @region 视频数据回调
     * @brief 调用 RegisterLocalEncodedVideoFrameObserver{@link #RegisterLocalEncodedVideoFrameObserver} 后，SDK 收到本地视频帧信息时，回调该事件
     * @param [in] type 本地视频帧类型，参看 StreamIndex{@link #StreamIndex}
     * @param [in] video_stream 本地视频帧信息，参看 IEncodedVideoFrame{@link #IEncodedVideoFrame}
     */
    virtual void OnLocalEncodedVideoFrame(StreamIndex type, const IEncodedVideoFrame& video_stream) = 0;
};

/**
 * @type callback
 * @region 视频管理
 * @brief 远端编码后视频数据监测器
 */
class IRemoteEncodedVideoFrameObserver {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRemoteEncodedVideoFrameObserver() {
    }
    /**
     * @type callback
     * @region 视频数据回调
     * @brief 调用 RegisterRemoteEncodedVideoFrameObserver{@link #IRtcEngineLite#RegisterRemoteEncodedVideoFrameObserver} 后，SDK 监测到远端编码后视频数据时，触发该回调
     * @param [in] stream_info 收到的远端流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] video_stream 收到的远端视频帧信息，参看 IEncodedVideoFrame{@link #IEncodedVideoFrame}
     */
    virtual void OnRemoteEncodedVideoFrame(const RemoteStreamKey& stream_info, const IEncodedVideoFrame& video_stream) = 0;
};

/**
 * @type keytype
 * @brief 视频帧中包含的 metadata 信息
 */
struct VideoMetadataBuffer {
    /**
     * @brief 接收或者发送的 metadata
     */
    char* data;
    /**
     * @brief 接收或者发送的 metadata 数据大小，不能超过 1024
     */
    int size;
    /**
     * @brief 包含 metadata 视频帧的时间戳，单位微秒
     */
    int64_t timestamp_us;
};

/**
 * @hidden
 * @deprecated
 * @type callback
 * @region 视频数据回调
 * @brief metadata 观察者，可以接收媒体流中的 metadata， 或者向媒体流中添加 metadata
 */
class IMetadataObserver {
public:
    /**
     * @hidden
     */
    virtual ~IMetadataObserver() {
    }

    /**
     * @type callback
     * @region 视频数据回调
     * @brief 当 SDK 准备发送一个视频帧时，会回调该事件，以确定是否需要在该视频帧中添加 metadata。
     * @param [in/out] metadata 待发送的数据，把数据拷贝到 data 字段中，并将 size 设置为真实的大小。
     * @return  <br>
     *        + true：需要向视频帧中添加 metadata  <br>
     *        + false：不需要向视频帧中添加 metadata  <br>
     * @notes  <br>
     *        + metadata 的大小不能超过1024字节  <br>
     *        + metadata 中的 timestamp_us 是输入字段，代表视频帧的时间戳，做同步使用，不需要修改。  <br>
     *        + 回调中不能有耗时操作，以免影响视频卡顿  <br>
     */
    virtual bool OnReadyToSendMetadata(VideoMetadataBuffer* metadata) = 0;

    /**
     * @type callback
     * @region 视频数据回调
     * @brief 当 SDK 收到一个视频帧时，并且其中包含 medatada 时，会回调该事件。
     * @param [in] roomid 当前帧所属的房间 ID。
     * @param [in] uid 当前帧所属的用户 ID。
     * @param [in] metadata 视频帧中包含的 metadata 信息。参看 VideoMetadataBuffer{@link #VideoMetadataBuffer}。
     * @notes 回调中不能有耗时操作，以免影响视频卡顿。
     */
    virtual void OnMetadataReceived(const char* roomid, const char* uid, const VideoMetadataBuffer& metadata) = 0;
};

/**
 * @type callback
 * @region 音频数据回调
 * @brief 音频数据回调观察者
 */
class IAudioFrameObserver {
public:
    /**
     * @type keytype
     * @region 音频数据回调
     * @brief 音频帧类型
     */
    enum AUDIO_FRAME_TYPE {
        /**
         * @brief PCM 16bit
         */
        FRAME_TYPE_PCM16 = 0,
    };

    /**
     * @type keytype
     * @region 音频数据回调
     * @brief 音频帧
     */
    struct AudioFrame {
        /**
         * @brief 音频帧类型
         */
        AUDIO_FRAME_TYPE type;
        /**
         * @brief 音频采样点数量
         */
        int samples;

        /**
         * @brief 音频通道数
         */
        int channels;

        /**
         * @brief 音频采样率
         */
        int samples_per_sec;

        /**
         * @brief 音频数据内存地址
         */
        void* buffer;

        /**
         * @brief 渲染时间
         */
        int64_t render_time_ms;
    };

public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioFrameObserver() {
    }

    /**
     * @type callback
     * @region 音频数据回调
     * @brief 返回麦克风录制的音频数据
     * @param [in] audio_frame 麦克风录制的音频数据, 详见：AudioFrame{@link #AudioFrame}
     */
    virtual void OnRecordAudioFrame(const AudioFrame& audio_frame) = 0;

    /**
     * @type callback
     * @region 音频数据回调
     * @brief 返回远端所有用户混音后的音频数据
     * @param [in] audio_frame 远端所有用户混音后的音频数据, 详见：AudioFrame{@link #AudioFrame}
     */
    virtual void OnPlaybackAudioFrame(const AudioFrame& audio_frame) = 0;

    /**
     * @hidden
     * @region 音频数据回调
     * @notes 该接口未实现
     */
    virtual void OnPlaybackAudioFrameBeforeMixing(const char* uid, const AudioFrame& audio_frame) = 0;

    /**
     * @type callback
     * @region 音频数据回调
     * @brief 返回本地麦克风录制和远端所有用户混音后的音频数据
     * @param [in] audio_frame 本地麦克风录制和远端所有用户混音后的音频数据, 详见：AudioFrame{@link #AudioFrame}
     */
    virtual void OnMixedAudioFrame(const AudioFrame& audio_frame) = 0;

    /**
     * @hidden
     * @type callback
     * @region 屏幕音频数据回调
     * @brief 返回本地播放的音频数据
     * @param [in] audio_frame 麦克风录制的音频数据, 详见：{@link #AudioFrame}
     */
    virtual void OnRecordScreenAudioFrame(const AudioFrame& audio_frame) {
    }
};

/**
 * @type keytype
 * @region 音频处理
 * @brief 自定义音频处理器
 */
class IAudioProcessor{
public:
    /**
     * @type callback
     * @region 音频处理
     * @brief 获取 RTC SDK 采集得到的音频帧，并进行自定义处理，最终将处理后的音频帧给到 RTC SDK 用于编码传输。
     * @param [in] audioFrame RTC SDK 采集到的音频帧，自定义处理可直接对音频 data 中的数据进行修改。参看 IAudioFrame{@link #IAudioFrame}。
     * @return  <br>
     *        0: 未处理  <br>
     *        >0: 处理成功  <br>
     *        <0: 处理失败
     * @notes 在进行音频自定义处理前，你需要调用 RegisterLocalAudioProcessor{@link #IRtcEngineLite#RegisterLocalAudioProcessor} 设置音频自定义处理器。
     */
    virtual int ProcessAudioFrame(const IAudioFrame& audioFrame) = 0;
};

/**
 * @type callback
 * @region 视频管理
 * @brief 视频数据回调对象
 */
class IVideoFrameObserver {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IVideoFrameObserver() = default;

    /**
     * @type callback
     * @region 视频管理
     * @brief 本地屏幕视频流采集成功后，会收到此回调。
     * @param [in] videoFrame 视频数据，参看 IVideoFrame{@link #IVideoFrame}。  <br>
     * @return  <br>
     *        + true: SDK 不处理返回值
     *        + false: SDK 不处理返回值
     * @notes 对于回调的视频数据，你可以进行自定义渲染。
     */
    virtual bool OnLocalScreenFrame(IVideoFrame* videoFrame) = 0;

    /**
     * @type callback
     * @region 视频管理
     * @brief 本地视频流数据回调
     * @param [in] videoFrame 视频数据，参看 IVideoFrame{@link #IVideoFrame}。  <br>
     * @return  <br>
     *        + true: SDK 不处理返回值
     *        + false: SDK 不处理返回值
     */
    virtual bool OnLocalVideoFrame(IVideoFrame* videoFrame) = 0;

    /**
     * @type callback
     * @region 视频管理
     * @brief 远端屏幕共享流数据回调
     * @param [in] roomid 房间 ID。
     * @param [in] uid 远端用户 ID。
     * @param [in] videoFrame 视频数据，参看 IVideoFrame{@link #IVideoFrame}。  <br>
     * @return  <br>
     *        + true: SDK 不处理返回值
     *        + false: SDK 不处理返回值
     */
    virtual bool OnRemoteScreenFrame(const char* roomid, const char* uid, IVideoFrame* videoFrame) = 0;

    /**
     * @type callback
     * @region 视频管理
     * @brief 远端视频数据回调
     * @param [in] roomid 房间 ID。
     * @param [in] uid 远端用户 ID。
     * @param [in] videoFrame 视频数据，参看 IVideoFrame{@link #IVideoFrame}}。  <br>
     * @return  <br>
     *        + true: SDK 不处理返回值
     *        + false: SDK 不处理返回值
     */
    virtual bool OnRemoteVideoFrame(const char* roomid, const char* uid, IVideoFrame* videoFrame) = 0;

    /**
     * @hidden
     * @type callback
     * @region 视频管理
     * @brief 拼接视频数据回调
     * @param [in] roomid
     *        房间 id
     * @param [in] uid
     *        远端用户ID
     * @param [in] videoFrame
     *        视频数据，详见 IVideoFrame{@link #IVideoFrame}}
     * @return
     *        true: SDK 不处理返回值
     *       false: SDK 不处理返回值
     */
    virtual bool OnMergeFrame(const char* roomid, const char* uid, IVideoFrame* videoFrame) {
        return false;
    }
};

/**
 * @hidden
 * @type callback
 * @region 音频数据回调
 * @brief 音频数据回调观察者
 */
class IRemoteAudioFrameObserver {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRemoteAudioFrameObserver() {
    }

    /**
     * @hidden
     * @type callback
     * @region 音频数据回调
     * @brief 获得单个流的音频数据，此回调通过调用 RegisterRemoteAudioFrameObserver{@link
     * #RegisterRemoteAudioFrameObserver} 触发。
     * @param [in] audio_frame 音频数据, 详见： IAudioFrame{@link #IAudioFrame}
     * @param [in] stream_info 该音频流的业务信息, 详见： RemoteStreamKey{@link #RemoteStreamKey}
     */
    virtual void OnRemoteAudioFrame(const IAudioFrame& audio_frame, const RemoteStreamKey& stream_info) = 0;
};

/**
 * @type keytype
 * @brief 屏幕采集对象的类型
 */
enum ScreenCaptureSourceType {
    /**
     * @brief 类型未知
     */
    kScreenCaptureSourceTypeUnknown,

    /**
     * @brief 应用程序的窗口
     */
    kScreenCaptureSourceTypeWindow,

    /**
     * @brief 桌面
     */
    kScreenCaptureSourceTypeScreen
};

/**
 * @type keytype
 * @brief 屏幕采集对象的具体信息
 */
struct ScreenCaptureSourceInfo {
    /**
     * @brief 屏幕分享时，共享对象的类型，参看 ScreenCaptureSourceType{@link #ScreenCaptureSourceType}
     */
    ScreenCaptureSourceType type = kScreenCaptureSourceTypeUnknown;

    /**
     * @brief 屏幕分享时，共享对象的 ID。
     */
    view_t source_id = nullptr;

    /**
     * @brief 屏幕分享时共享对象的名称。
     * @notes 内存在 IScreenCaptureSourceList{@link #IScreenCaptureSourceList}释放的时候一起释放，
     * 请及时转为string对象保存
     */
    const char* source_name = nullptr;
};

/**
 * @hidden(Android,iOS)
 * @type keytype
 * @region 屏幕共享
 * @brief 屏幕源类型信息列表
 */
class IScreenCaptureSourceList {
public:
  /**
   * @hidden
   */
    virtual ~IScreenCaptureSourceList() {
    }
    /**
     * @region 屏幕共享
     * @brief 获取列表大小
     * @return 获取列表大小
     */
    virtual int32_t GetCount() = 0;

    /**
     * @region 屏幕共享
     * @brief 根据索引，获取屏幕共享列表中的元素
     * @param 列表索引号
     * @return 屏幕源类型信息
     * @notes 返回类型中有char*类型的字符串，该字符串在本对象Release后释放，请注意内存管理。
     */
    virtual ScreenCaptureSourceInfo GetSourceInfo(int32_t index) = 0;

    /**
     * @region 屏幕共享
     * @brief 析构当前对象，释放内存
     * @notes 严禁调用 delete 该结构体，该结构不需要的时候应该调用本函数释放资源
     */
    virtual void Release() = 0;
};

/**
 * @type api
 * @brief 引擎 API
 */
class IRtcEngineLite {
public:
    /**
     * @hidden
     * @deprecated from 327.1, use SetCaptureVolume instead
     * @type api
     * @region 音频管理
     * @brief 调节音频采集音量
     * @param [in] volume 音频采集音量，取值范围： [0,400]  <br>
     *       + 0: 静音  <br>
     *       + 100: 原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100], 该接口已废弃，请使用 SetCaptureVolume{@link #SetCaptureVolume}。
     */
    virtual void SetRecordingVolume(const int volume) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 音量管理
     * @brief 调节音频采集音量
     * @param [in] index 流索引，指定调节主流还是调节屏幕流的音量，参看 StreamIndex{@link #StreamIndex}
     * @param [in] volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。
     * @notes <br>
     *        + 无论是采集来自麦克风的音频流，还是屏幕音频流；无论是 RTC SDK 内部采集，还是自定义采集，都可以使用此接口进行音量调节。
     *        + 在开启音频采集前后，你都可以使用此接口设定采集音量。
     */
    virtual void SetCaptureVolume(StreamIndex index, int volume) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 调节本地播放的所有远端用户混音后的音量
     * @param [in] volume 音频播放音量，取值范围： [0,400] <br>
     *       + 0: 静音  <br>
     *       + 100: 原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100]。
     */
    virtual void SetPlaybackVolume(const int volume) = 0;


    /**
     * @hidden(Windows)
     * @type api
     * @region 音频管理
     * @brief 开启/关闭耳返功能
     * @param [in] mode 是否开启耳返功能，参看 EarMonitorMode{@link #EarMonitorMode}
     */
    virtual void SetEarMonitorMode(EarMonitorMode mode) = 0;

    /**
     * @hidden(Windows)
     * @type api
     * @region 音频管理
     * @brief 设置耳返的音量
     * @param [in] volume 耳返的音量，取值范围：[0,100]，单位：%
     * @notes <br>
     *        + 设置耳返音量前，你必须先调用 SetEarMonitorMode{@link #SetEarMonitorMode} 打开耳返功能。<br>
     *        + 耳返功能仅在使用 RTC SDK 提供的内部音频采集功能，并连接了有线耳机时有效。<br>
     */
    virtual void SetEarMonitorVolume(const int volume) = 0;

    /**
     * @hidden
     * @deprecated from 327.1, use SetScreenAudioStreamIndex instead
     * @type api
     * @region 屏幕共享
     * @brief 开启声卡采集，将声卡播放的音频流合到本地采集的音频流中。<br>
     *         如果你希望将声卡播放的声音传输到远端（比如屏幕共享等场景），你必须开启声卡采集。如此，声卡播放的声音会合到本地采集的音频流在中，一起发送到远端。
     * @notes  <br>
     *       + 开启声卡采集后，你可以设置对应音量，参看 SetScreenAudioVolumeBeforeMixing{@link
     * #SetScreenAudioVolumeBeforeMixing} <br>
     *       + 如果需要关闭声卡采集，参看 StopMixScreenAudioToMainStream{@link #StopMixScreenAudioToMainStream}
     */
    virtual void StartMixScreenAudioToMainStream() = 0;

    /**
     * @hidden
     * @deprecated from 327.1, use SetScreenAudioStreamIndex instead
     * @type api
     * @region 屏幕共享
     * @brief 关闭声卡采集，声卡播放的音频流不再合到本地采集的音频流中。
     * @notes 如果需要开启声卡采集，请参看 StartMixScreenAudioToMainStream{@link #StartMixScreenAudioToMainStream}
     */
    virtual void StopMixScreenAudioToMainStream() = 0;

    /**
     * @hidden
     * @deprecated from 327.1, use SetCaptureVolume instead
     * @type api
     * @region 屏幕共享
     * @brief 调节本地声卡采集音量。<br>
     *        开启本地声卡采集后，你可以使用此接口调节采集音量。
     *        关于如何开启本地声卡采集，参考 StartMixScreenAudioToMainStream{@link #StartMixScreenAudioToMainStream}。
     * @param volume 声卡采集音量，取值范围： [0,400]  <br>
     *       + 0: 静音  <br>
     *       + 100: 原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     */
    virtual void SetScreenAudioVolumeBeforeMixing(int volume) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 开启内部音频采集。默认为关闭状态。  <br>
     *        进房前调用该方法，本地用户会收到 OnMediaDeviceStateChanged{@link #OnMediaDeviceStateChanged} 的回调。 <br>
     *        进房后调用该方法，房间中的其他用户会收到 OnUserStartAudioCapture{@link #OnUserStartAudioCapture} 的回调。
     * @notes  <br>
     *       + 若未取得当前设备的麦克风权限，调用该方法后会触发 OnWarning{@link #IRtcEngineLiteEventHandler#OnWarning} 回调。  <br>
     *       + 调用 StopAudioCapture{@link #StopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
     *       + 无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  <br>
     *       + 尚未进房并且已使用自定义采集时，关闭自定义采集后并不会自动开启内部采集。你需调用此方法手动开启内部采集。
     */
    virtual void StartAudioCapture() = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 关闭内部音频采集。默认为关闭状态。  <br>
     *        进房前调用该方法，本地用户会收到 OnMediaDeviceStateChanged{@link #OnMediaDeviceStateChanged} 的回调。  <br>
     *        进房后调用该方法后，房间中的其他用户会收到 OnUserStopAudioCapture{@link #OnUserStopAudioCapture} 的回调。
     * @notes  <br>
     *       + 调用 StartAudioCapture{@link #StartAudioCapture} 可以开启音频采集设备。  <br>
     *       + 设备开启后若一直未调用该方法关闭，则 SDK 会在销毁引擎的时候自动关闭音频采集设备。  <br>
     */
    virtual void StopAudioCapture() = 0;

    /**
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频管理
     * @brief 设置音频场景类型。  <br>
     *        你可以根据你的应用所在场景，选择合适的音频场景类型。
     *        选择音频场景后，RTC 会自动根据客户端音频路由和发布订阅状态，适用通话音量/媒体音量。  <br>
     *        在进房前和进房后设置均可生效。
     * @param [in] scenario 音频场景类型，
     *        参见 AudioScenarioType{@link #AudioScenarioType}
     * @notes  <br>
     *        +
     * 通话音量更适合通话，会议等对信息准确度要求更高的场景。通话音量会激活系统硬件信号处理，使通话声音会更清晰。此时，音量无法降低到
     * 0。<br>
     *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，音量最低可以降低到 0。
     */
    virtual void SetAudioScenario(AudioScenarioType scenario) = 0;

    /**
     * @type api
     * @region 音频管理
     * @brief 设置音质档位。你应根据业务场景需要选择适合的音质档位。  <br>
     * @param [in] audio_profile 音质档位，参看 AudioProfileType{@link #AudioProfileType}
     * @notes  <br>
     *        + 该方法在进房前后均可调用；  <br>
     *        + 支持通话过程中动态切换音质档位。
     */
    virtual void SetAudioProfile(AudioProfileType audio_profile) = 0;

    /**
     * @type api
     * @region 媒体流管理
     * @brief 控制本地音频流的发送状态：发送/不发送  <br>
     *        使用此方法后，房间中的其他用户会收到回调： OnUserMuteAudio{@link #OnUserMuteAudio}
     * @param [in] mute_state 发送状态，标识是否发送本地音频流，详见：MuteState{@link #MuteState}
     * @notes 本方法仅控制本地音频流的发送状态，并不影响本地音频采集状态。
     */
    virtual void MuteLocalAudio(MuteState mute_state) = 0;

    /**
     * @type api
     * @region 自定义音频采集渲染
     * @brief 启用自定义音频采集渲染
     * @param [in] recording_format 自定义音频数据采集格式，详见 AudioFormat{@link #AudioFormat}
     * @param [in] playback_format 自定义音频数据渲染格式，详见 AudioFormat{@link #AudioFormat}
     * @notes  <br>
     *      + 该方法需要在进房前调用。  <br>
     *      + 启用自定义音频采集渲染的状态在离开房间后仍然有效，会一直持续到调用 DisableExternalAudioDevice{@link #DisableExternalAudioDevice} 关闭自定义音频采集渲染为止。  <br>
     *      + 启用自定义音频采集渲染后，仍需要使用 PushExternalAudioFrame{@link #PushExternalAudioFrame}，推送外部音频数据，再使用 PullExternalAudioFrame{@link #PullExternalAudioFrame} 拉取外部音频数据。  <br>
     *      + 当你已调用 StartAudioCapture{@link #StartAudioCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
     *      + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用 DisableExternalAudioDevice{@link #DisableExternalAudioDevice} 关闭自定义采集，然后调用 StartAudioCapture{@link #StartAudioCapture} 手动开启内部采集。
     */
    virtual void EnableExternalAudioDevice(const AudioFormat &recording_format, const AudioFormat &playback_format) = 0;

    /**
     * @type api
     * @region 自定义音频采集渲染
     * @brief 禁用已开启的自定义音频采集渲染，将音频采集渲染由自定义模块切换至内部模块。
     * @notes  <br>
     *      + 如果你已开启自定义音频采集渲染，你可以在进房前，使用本接口将音频采集渲染由自定义模块切换至内部模块。  <br>
     *      + 使用该 API 禁用自定义音频采集渲染后， SDK 不会自动开启内部的音频采集，需要开启 SDK 内部采集请使用
     * StartAudioCapture{@link #StartAudioCapture}。  <br>
     *      + 启用自定义音频采集渲染请使用 EnableExternalAudioDevice{@link #EnableExternalAudioDevice}。  <br>
     */
    virtual void DisableExternalAudioDevice() = 0;

    /**
     * @type api
     * @region 自定义音频采集渲染
     * @brief 推送外部音频数据。使用 EnableExternalAudioDevice{@link #EnableExternalAudioDevice}
     * 启用自定义音频采集渲染后，可以使用本方法推送外部音频数据。
     * @param [in] data
     *        pcm 数据，内存大小应该为 samples * record_format.channel * 2。
     * @param [in] samples
     *        采样点数量，应该为 EnableExternalAudioDevice{@link #EnableExternalAudioDevice} 中设置的
     * record_format.sample_rate / 100。 当设置采样率为48000时， 每次应该推送480个采样点
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 必须是 pcm 数据，推送间隔是 10ms，音频采样格式为 s16。  <br>
     *       + 该函数运行在用户调用线程内，是一个同步函数  <br>
     */
    virtual bool PushExternalAudioFrame(int8_t* data, int samples) = 0;

    /**
     * @type api
     * @region 自定义音频采集渲染
     * @brief 拉取远端音频数据。使用 EnableExternalAudioDevice{@link #EnableExternalAudioDevice}
     * 启用自定义音频采集渲染后，可以使用本方法拉取远端音频数据。
     * @param [out] data
     *        pcm 数据，内存大小应该为 samples * playback_format.channel * 2。
     * @param [in] samples
     *        采样点数量，应该为 EnableExternalAudioDevice{@link #EnableExternalAudioDevice} 中设置的
     * playback_format.sample_rate / 100。 当设置采样率为 48000 时， 每次应该拉取 480 个采样点
     * @return  方法调用结果  <br>
     *        + true:方法调用成功  <br>
     *        + false：方法调用失败  <br>
     * @notes  <br>
     *       + 必须是 pcm 数据，拉取间隔是 10ms，音频采样格式为 s16。  <br>
     *       + 该函数运行在用户调用线程内，是一个同步函数  <br>
     */
    virtual bool PullExternalAudioFrame(int8_t* data, int samples) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 开始播放音乐文件及混音。
     * @param [in] file_path  <br>
     *        指定需要混音的本地文件的绝对路径。支持音频文件格式有: mp3，aac，m4a，3gp，wav。
     * @param [in] loopback  <br>
     *       + true: 只有本地可以听到混音或替换后的音频流。  <br>
     *       + false: 本地和对方都可以听到混音或替换后的音频流
     * @param [in] replace  <br>
     *       + true: 只推送设置的本地音频文件，不传输麦克风采集的音频。  <br>
     *       + false: 音频文件内容将会和麦克风采集的音频流进行混音
     * @param [in] cycle 指定音频文件循环播放的次数。  <br>
     *       + >0: 循环的次数。  <br>
     *       + -1: 无限循环
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *      + 该方法指定本地和麦克风采集的音频流进行混音或替换。替换是指用音频文件替换麦克风采集的音频流。  <br>
     *      + 该方法可以选择是否让对方听到本地播放的音频，并指定循环播放的次数。
     * 调用本方法播放音乐文件及混音结束后，应用会收到 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged} 回调。  <br>
     *      + 开始播放音乐文件及混音后，可以调用 StopAudioMixing{@link #StopAudioMixing} 方法停止播放音乐文件。  <br>
     *      + 该方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav；而SetAudioPlayoutMixStream{@link
     * #SetAudioPlayoutMixStream} 混音的数据来源外部缓存且音频格式为PCM；这两种混音方式可以共存。  <br>
     *      + 单个房间只支持一路音乐文件的播放，多次调用该函数后，只有最后一次调用会生效。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int StartAudioMixing(const char* file_path, bool loopback, bool replace, int cycle) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 停止播放音乐文件及混音
     * @notes  <br>
     *      + 调用 StartAudioMixing{@link #StartAudioMixing}
     * 方法开始播放音乐文件及混音后，调用该方法可以停止播放音乐文件及混音。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual void StopAudioMixing() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 暂停播放音乐文件
     * @return  <br>
     *        + 0: 成功  <br>
     *        + <0: 失败
     * @notes  <br>
     *      + 调用 StartAudioMixing{@link #StartAudioMixing}
     * 方法开始播放音乐文件及混音后，可以通过调用该方法暂停播放音乐文件。  <br>
     *      + 调用该方法暂停播放音乐文件后，可调用 ResumeAudioMixing{@link #ResumeAudioMixing} 方法恢复播放。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int PauseAudioMixing() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 恢复播放音乐文件
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *      + 调用 PauseAudioMixing{@link #PauseAudioMixing} 方法暂停播放音乐文件后，可以通过调用该方法恢复播放。  <br>
     *      + 请在房间内调用该方法
     */
    virtual int ResumeAudioMixing() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节音乐文件的文件音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
     * @param [in] volume 音乐文件播放音量范围为 0~400。  <br>
     *       + 0：静音  <br>
     *       + 100：原始音量  <br>
     *       + 400: 最大可调音量 (自带溢出保护)
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *      + 调用该方法可同时调节的是本地和远端播放音量。仅调节本端音量可使用 AdjustAudioMixingPlayoutVolume{@link
     * #AdjustAudioMixingPlayoutVolume} ， 仅调节远端音量可使用 AdjustAudioMixingPublishVolume{@link
     * #AdjustAudioMixingPublishVolume}。  <br>
     *      + 该方法对 AdjustAudioMixingPlayoutVolume{@link #AdjustAudioMixingPlayoutVolume} 和
     * AdjustAudioMixingPublishVolume{@link #AdjustAudioMixingPublishVolume} 的音量调节影响是乘积关系。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int AdjustAudioMixingVolume(int volume) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节音乐文件的本地播放音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
     * @param [in] volume 音乐文件播放音量范围为 0~400。  <br>
     *       + 0：静音  <br>
     *       + 100：原始音量  <br>
     *       + 400: 最大可调音量 (自带溢出保护)
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *      + 调用该方法可以调节混音的音乐文件在本地播放的音量大小。如果需要同时调节本地和远端播放音量可使用
     * AdjustAudioMixingVolume{@link #AdjustAudioMixingVolume} 方法。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int AdjustAudioMixingPlayoutVolume(int volume) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节音乐文件的远端播放音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
     * @param [in] volume 音乐文件播放音量范围为 0~400。  <br>
     *       + 0：静音  <br>
     *       + 100：原始音量  <br>
     *       + 400: 最大可调音量 (自带溢出保护)
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *      + 该方法调节混音的音乐文件在远端播放的音量大小。如果需要同时调节本地和远端播放音量可使用
     * AdjustAudioMixingVolume{@link #AdjustAudioMixingVolume} 方法。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int AdjustAudioMixingPublishVolume(int volume) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 获取音乐文件时长
     * @return  <br>
     *       + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
     *       + <0: 失败
     * @notes <br>
     *       请在房间内调用该方法。
     */
    virtual int GetAudioMixingDuration() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 获取音乐文件播放进度
     * @return  <br>
     *       + >0: 成功, 音乐文件播放进度，单位为毫秒。  <br>
     *       + <0: 失败
     * @notes <br>
     *       请在房间内调用该方法。
     */
    virtual int GetAudioMixingCurrentPosition() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 设置音频文件的播放位置
     * @param [in] pos
     *        整数。进度条位置，单位为毫秒。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *       该方法可以设置音频文件的播放位置，这样你可以根据实际情况从指定的位置播放音乐文件，无需从头到尾完整播放一个音乐文件。
     */
    virtual int SetAudioMixingPosition(int pos) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 获取指定音效文件的文件音量
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。确保此处的 sound_id 与  StartAudioMixing{@link #StartAudioMixing}
     * 设置的 sound_id 相同。
     * @return  <br>
     *       + >0: 成功，文件音量，音量范围为 0~400。  <br>
     *       + <0: 失败
     * @notes  <br>
     *       请在房间内调用该方法。
     */
    virtual int GetEffectVolume(int sound_id) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节指定音效文件的文件音量
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。确保此处的 sound_id 与  StartAudioMixing{@link #StartAudioMixing}
     * 设置的 sound_id 相同。
     * @param [in] volume  <br>
     *        音乐文件播放音量范围为 0~400。默认 100 为原始文件音量
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes
     *       + 该方法调节音效文件在本地和远端播放的音量大小。  <br>
     *       + 请在房间内调用该方法。
     */
    virtual int SetVolumeOfEffect(int sound_id, int volume) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 开始播放指定音效文件。你可以在该方法中设置音效文件的播放次数、音量大小，以及远端用户是否能听到该音效。
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。如果已经通过 PreloadEffect{@link #PreloadEffect}
     * 将音效加载至内存，确保此处的 sound_id 与 PreloadEffect{@link #PreloadEffect} 设置的 sound_id 相同。
     * @param [in] file_path  <br>
     *        指定需要混音的音频文件名和文件路径名。支持以下音频格式: mp3，aac，m4a，3gp，wav
     * @param [in] loopback  <br>
     *       + true: 只有本地可以听到该音效。  <br>
     *       + false: 本地和远端用户都可以听到该音效。
     * @param  cycle 指定音频文件循环播放的次数。  <br>
     *       + >0：循环的次数。  <br>
     *       + -1：无限循环，直至调用 StopEffect{@link #StopEffect} 或 StopAllEffects{@link #StopAllEffects} 后停止。
     * @param [in] volume  <br>
     *        音效文件播放音量范围为 0~400。默认 100 为原始文件音量。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *      + 调用该方法播放音效结束后，应用会收到 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged} 回调。  <br>
     *      + 可以多次调用该方法，通过传入不同的音效文件的 sound_id 和
     * file_path，以实现同时播放多个音效文件，实现音效叠加。  <br>
     *      + 可以调用 StopEffect{@link #StopEffect} 方法停止播放指定音效文件。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int PlayEffect(int sound_id, const char* file_path, bool loopback, int cycle, int volume) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 预加载指定音效文件。
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。
     * @param [in] file_path  <br>
     *        指定需要混音的音频文件名和文件路径名。支持以下音频格式: mp3，aac，m4a，3gp，wav。
     * @return  <br>
     *        + 0: 成功  <br>
     *        + <0: 失败
     * @notes  <br>
     *       +
     * 调用该方法预加载播放指定音效文件。预加载操作可以在进房间之前完成（所有混音相关接口，如果没有标注请在房间内调用都可在没有进入房间的时候调用）。如果音效文件很长，加载操作可能会耗时较长，建议应用开发者将预加载操作放在子线程进行。
     * <br>
     *       + 该方法只是预加载播放指定音效文件，只有调用 StartAudioMixing{@link #StartAudioMixing}
     * 方法才开始播放指定音效文件。 <br>
     *       + 该方法预加载指定音效文件可以通过 UnloadEffect{@link #UnloadEffect} 来卸载。
     */
    virtual int PreloadEffect(int sound_id, const char* file_path) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 卸载指定音效文件
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *       + 调用该方法卸载指定音效文件。  <br>
     *       + 如果调用 StopEffect{@link #StopEffect} 方法时，音效文件没有被卸载，SDK会自动调用该方法卸载音效文件。
     */
    virtual int UnloadEffect(int sound_id) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 停止播放指定音效文件
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。如果已经通过 PreloadEffect{@link #PreloadEffect}
     * 将音效加载至内存，确保此处的 sound_id 与  PreloadEffect{@link #PreloadEffect} 设置的 sound_id 相同。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *       + 调用该方法停止播放指定音效文件。  <br>
     *       + 该方法内部会主动调用 UnloadEffect{@link #UnloadEffect} 来卸载指定音效文。
     */
    virtual int StopEffect(int sound_id) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 暂停播放指定音效文件
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *       调用该方法暂停播放指定音效文件，可以调用 ResumeEffect{@link #ResumeEffect} 方法恢复播放。
     */
    virtual int PauseEffect(int sound_id) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 恢复播放指定音效文件
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + <0: 失败
     * @notes  <br>
     *      + 调用 PauseEffect{@link #PauseEffect} 方法暂停播放指定音效文件后， 可以通过该方法恢复播放。  <br>
     *      + 调用 PauseAllEffects{@link #PauseAllEffects}
     * 方法暂停所有音效文件的播放后，也可以通过该方法恢复单个音效文件播放。
     */
    virtual int ResumeEffect(int sound_id) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节所有音效文件的文件音量
     * @param [in] volume  <br>
     *        音乐文件播放音量范围为 0~400。默认 100 为原始文件音量。
     * @notes  <br>
     *      + 该方法调节混音的所有音效文件在本地和远端播放的音量大小。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual void SetEffectsVolume(int volume) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 停止所有音效文件的播放
     * @notes  <br>
     *      该方法停止所有音效文件的播放。
     */
    virtual void StopAllEffects() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 暂停所有音效文件的播放。
     * @notes  <br>
     *      调用该方法暂停所有音效文件的播放，可调用 ResumeAllEffects{@link #ResumeAllEffects} 方法恢复播放。
     */
    virtual void PauseAllEffects() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 恢复所有音效文件的播放
     * @notes  <br>
     *     + 调用该方法恢复所有音效文件的播放。在调用 PauseAllEffects{@link #PauseAllEffects}
     * 暂停所有音效文件的播放后，可以调用该方法可恢复所有音效文件的播放。  <br>
     *     + 调用 PauseEffect{@link #PauseEffect}
     * 方法暂停单个指定音效文件的播放后，也可以调用该方法恢复播放，但是效率太低，不推荐这么使用。
     */
    virtual void ResumeAllEffects() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 卸载所有音效文件
     * @notes  <br>
     *      + 调用该方法卸载所有音效文件。如果引擎被销毁时有音效文件没有被卸载，SDK会自动调用该方法卸载所有音效文件。
     * <br>
     *      + 调用 LeaveRoom{@link #LeaveRoom}
     * 离开房间后，不会自动调用该方法卸载所有音效文件。如果需要在离开房间后卸载所有音效文件，需要应用主动调用该方法。
     */
    virtual void UnloadAllEffects() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 启动/停止外部音频流混音， 并设置混音数据格式
     * @param [in] enable  <br>
     *       + true: 启用外部音频流混音。  <br>
     *       + false: 停止外部音频流混音。
     * @param [in] sample_rate  <br>
     *        音频采样率，单位HZ。目前支持的采样率有：8000HZ， 16000HZ， 32000HZ， 44100HZ，48000HZ。
     * @param [in] channel_num  <br>
     *        音频声道个数。目前支持单通道(1)，双通道(2)
     * @notes  <br>
     *      + 调用该方法设置外部音频混音的PCM格式，即 PushAudioMixingStreamData{@link #PushAudioMixingStreamData} 的
     * audio_frame 的音频数据格式。  <br>
     *      + 调用该方法混音的数据来源外部缓存，且音频格式为PCM； StartAudioMixing{@link #StartAudioMixing}
     * 方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav。这两种混音方式可以共存。  <br>
     *      + enable 为 false 时，停止外部音频流混音。 或者引擎释放时，SDK内部会停止混音。  <br>
     *      + 该方法启动的外部音频流混音不支持音量调节，暂停，暂停恢复操作。
     */
    virtual void SetAudioPlayoutMixStream(bool enable, int sample_rate, int channel_num) = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 获取SDK当前缓冲数据
     * @return  <br>
     *       + >0: 成功，缓冲的音频采样点个数。  <br>
     *       + 0: 失败
     * @notes
     *      调用该方法可以实时获取缓存数据量，并以此数据为基准调整数据推送节奏来避免内存溢出
     */
    virtual int GetAudioMixingStreamCachedFrameNum() = 0;

    /**
     * @hidden
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 向SDK推送混音的音频数据
     * @param [in] audio_frame  <br>
     *        PCM音频数据，其格式与 SetAudioPlayoutMixStream{@link #SetAudioPlayoutMixStream} 保持一致。
     * @param [in] frame_num  <br>
     *        采样点数量，应该为 SetAudioPlayoutMixStream{@link #SetAudioPlayoutMixStream} 中设置的 sample_rate / 100。
     *        当设置采样率为48000时， 每次应该推送480个采样点
     * @return
     *       + true: 成功  <br>
     *       + false: 失败
     * @notes
     *      + 调用该方法前，必须通过 SetAudioPlayoutMixStream{@link #SetAudioPlayoutMixStream} 方法设置 audio_frame
     * 的数据格式。  <br>
     *      + 调用该方法前，先通过 GetAudioMixingStreamCachedFrameNum
     * 获取缓存的数据量，并调整推送数据的节奏以避免内部缓存溢出导致推送失败。  <br>
     *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），
     * 然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     */
    virtual bool PushAudioMixingStreamData(int8_t* audio_frame, int frame_num) = 0;

#ifndef ByteRTC_AUDIO_ONLY

    /**
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 开启内部视频采集。默认为关闭状态。  <br>
     *        调用该方法后，本地用户会收到 OnMediaDeviceStateChanged{@link #OnMediaDeviceStateChanged} 的回调。  <br>
     *        进房后调用该方法后，房间中的其他用户会收到 OnUserStartVideoCapture{@link #OnUserStartVideoCapture} 的回调。
     * @notes  <br>
     *       + 内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。
     *       + 若未取得当前设备的摄像头权限，调用该方法会不成功，并触发 OnMediaDeviceStateChanged{@link #OnMediaDeviceStateChanged} 回调。  <br>
     *       + 调用 StopVideoCapture{@link #StopVideoCapture} 可以关闭视频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
     *       + 无论是否发布视频数据，你都可以调用该方法开启视频采集，并且调用后方可发布视频。  <br>
     *       + 如果需要从自定义视频采集切换为内部视频采集，你必须先关闭自定义采集，再调用此方法手动开启内部采集。
     */
    virtual void StartVideoCapture() = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 关闭内部视频采集。默认为关闭状态。  <br>
     *        调用该方法后，本地用户会收到 OnMediaDeviceStateChanged{@link #OnMediaDeviceStateChanged} 的回调。  <br>
     *        进房后调用该方法后，房间中的其他用户会收到 OnUserStopVideoCapture{@link #OnUserStopVideoCapture} 的回调。
     * @notes  <br>
     *       + 调用 StartVideoCapture{@link #StartVideoCapture} 可以开启视频采集设备。  <br>
     *       + 设备开启后若一直未调用此方法关闭本地视频采集，则 SDK 会在销毁引擎的时候自动关闭。  <br>
     */
    virtual void StopVideoCapture() = 0;

    /**
    * @type api
    * @region 视频管理
    * @brief 设置 RTC SDK 内部采集时的视频采集参数。<br>
    *        如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括分辨率、帧率。
    * @param videoCaptureConfig 视频采集参数。参看: VideoCaptureConfig{@link #VideoCaptureConfig}。
    * @return  <br>
    *        + 0: 成功；  <br>
    *        + <0: 失败；  <br>
    * @notes  <br>
    * + 本接口在引擎创建后可调用，调用后立即生效。建议在调用 StartVideoCapture{@link #StartVideoCapture} 前调用本接口。
    * + 建议同一设备上的不同 Engine 使用相同的视频采集参数。
    * + 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 中设置的参数。
    */
    virtual int SetVideoCaptureConfig(const VideoCaptureConfig& videoCaptureConfig) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 启动推送多路视频流，设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
     * @param [in] index 视频流属性，参看 StreamIndex{@link #StreamIndex}。
     * @param [in] solutions 视频参数数组首地址，参看 VideoSolution{@link #VideoSolution}。
     * @param [in] solution_num 视频参数数组长度。<br>
     *                          最多支持 4 路参数。当设置了多路参数时，分辨率必须是从大到小排列。 <br>
     *                          最大分辨率为 4096px * 4096px，超过或设置的分辨率无法编码时，会导致编码推流失败。
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *       + 当使用内部采集时，视频采集的分辨率、帧率会根据最大的编码分辨率、帧率进行适配<br>
     *       + 默认的视频编码参数为：分辨率 640px * 360px，帧率 15fps。<br>
     *       + 变更编码分辨率后马上生效，可能会引发相机重启。<br>
     *       + 屏幕流只取视频参数数组的第一组数据。
     */
    virtual int SetVideoEncoderConfig(StreamIndex index, const VideoSolution* solutions, int solution_num) = 0;

    /**
     * @hidden
     * @deprecated
     * @type api
     * @region 视频管理
     * @brief 启动推送多路视频流，设置推送多路流时的各路视频参数，
     *        包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。

     * @param [in] solutions 视频参数数组首地址。参看 VideoSolution{@link #VideoSolution}。
     * @param [in] solution_num 视频参数数组长度。 <br>
*                               最多支持 3 路参数。当设置了多路参数时，分辨率必须是依次减小，从大到小排列的。 <br>
*                               最大分辨率没有限制。但是如果设置的分辨率无法编码，就会导致编码推流失败。
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *        + 当使用内部采集时，视频采集的分辨率、帧率会根据编码参数进行适配。<br>
     *        + 默认的视频编码参数为：分辨率 640px * 360px，帧率 15fps。<br>
     *        + 变更编码分辨率后马上生效，可能会引发相机重启。
     */
    virtual int SetVideoEncoderConfig(const VideoSolution* solutions, int solution_num) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 设置本地视频渲染时，使用的视图，并设置渲染模式。 <br>
     *        你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。
     *        如果需要解除绑定，你可以调用本方法绑定空视图。
     * @param [in] index 视频流属性, 参看 StreamIndex{@link #StreamIndex}
     * @param [in] canvas 视图信息和渲染模式，参看：VideoCanvas{@link #VideoCanvas}
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     */
    virtual int SetLocalVideoCanvas(StreamIndex index, const VideoCanvas& canvas) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 自定义视频采集渲染
     * @brief 将本地视频流与自定义渲染器绑定。
     * @param [in] index 视频流属性。采集的视频流/屏幕视频流，参看 StreamIndex{@link #StreamIndex}
     * @param [in] video_sink 自定义视频渲染器，参看 IVideoSink{@link #IVideoSink}。
     * @param [in] required_format video_sink 适用的视频帧编码格式，参看 PixelFormat{@link #PixelFormat}
     * @notes  <br>
     *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
     *        + 如果需要解除绑定，必须将 video_sink 设置为 null。进退房操作不会影响绑定状态。
     *        + 一般在收到 OnFirstLocalVideoFrameCaptured{@link #IRTCRoomEventHandler#OnFirstLocalVideoFrameCaptured} 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。
     */
    virtual void SetLocalVideoSink(
            StreamIndex index, IVideoSink* video_sink, IVideoSink::PixelFormat required_format) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 自定义视频采集渲染
     * @brief 将远端视频流与自定义渲染器绑定。
     * @param [in] stream_key 远端流信息，用于指定需要渲染的视频流来源及属性，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] video_sink 自定义视频渲染器，参看 IVideoSink{@link #IVideoSink}。
     * @param [in] required_format video_sink 适用的视频帧编码格式，参看 PixelFormat{@link #PixelFormat}。
     * @notes  <br>
     *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
     *        + 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 OnStreamAdd{@link #IRTCRoomEventHandler#OnStreamAdd} 回调获取到远端流信息之后，再调用该方法。
     *        + 如果需要解除绑定，必须将 video_sink 设置为 null。进退房操作不会影响绑定状态。
     */
    virtual void SetRemoteVideoSink(RemoteStreamKey stream_key, IVideoSink* video_sink,
                                   IVideoSink::PixelFormat required_format) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 停止/启动发送本地视频流，默认不发送。<br>
     *        无论你使用内部视频采集，还是自定义视频采集，你都应使用此接口启动发送本地视频流。<br>
     *        调用该方法后，房间中的其他用户会收到 OnUserMuteVideo{@link #OnUserMuteVideo} 的回调。
     * @param  [in] muteState 发送状态，标识是否发送本地视频流，参看 MuteState{@link #MuteState}   <br>
     * @notes <br>
     *        + 本方法只是停止/启动本地视频流的发送，不影响视频采集状态。
     *        + 无论是否开启视频采集，你都可以启动发送本地视频流。这样，一旦开始采集视频，即可进行发送。
     */
    virtual void MuteLocalVideo(MuteState muteState) = 0;

    /**
     * @hidden(Linux)
     * @hidden
     * @type api
     * @region 音频管理
     * @brief 开启屏幕共享本地音频
     * @notes  <br>
     *       + 请优先调用 StartScreenCapture 开启屏幕共享能力，在开启屏幕音频共享  <br>
     */
    virtual void StartScreenAudioShare() = 0;

    /**
     * @hidden(Linux)
     * @hidden
     * @type api
     * @region 音频管理
     * @brief 关闭屏幕共享本地音频
     * @notes  <br>
     *       + 请在调用 StopScreenCapture 之前关闭屏幕音频共享  <br>
     */
    virtual void StopScreenAudioShare() = 0;

    /**
     * @hidden
     * @type api
     * @region 音频管理
     * @brief 发送屏幕共享本地音频数据
     * @param [in] pData
     *        音频数据
     * @param [in] nSample
     *        采样数
     * @param [in] nBytesPerSample
     *        单个采样数据长度
     * @param [in] nChannels
     *        音频通道数
     * @param [in] sampleRate
     *        采样率
     * @return  <br>
     *        + true  :成功；  <br>
     *        + false :失败；  <br>
     * @notes  <br>
     *       + 暂时只支持 YUV420P 格式的视频帧。  <br>
     *       + 该函数运行在用户调用线程内，即将销毁 RtcEngine 实例前，请停止调用该函数推送屏幕共享数据  <br>
     */
    virtual void PushScreenAudioFrame(const void* pData, const size_t nSamples, const size_t nBytesPerSample,
            const size_t nChannels, const uint32_t sampleRate) = 0;

    /**
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 视频管理
     * @brief 切换视频内部采集时使用的前置/后置摄像头 <br>
     *        调用此接口后，在本地会触发 onMediaDeviceStateChanged{@link #IRtcEngineLiteEventHandler#onMediaDeviceStateChanged} 回调。
     * @param  [in] Camera ID，移动端摄像头。参看 CameraID {@link #CameraID}。
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *       + 默认使用前置摄像头。
     *       + 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。
     *       + 如果本地有多个摄像头且想选择特定工作摄像头可通过 IVideoDeviceManager{@link #IVideoDeviceManager} 来控制。  <br>
     */
    virtual int SwitchCamera(CameraID camera_id) = 0;

    /**
     * @type api
     * @region 屏幕共享
     * @brief 发送屏幕共享外部视频数据
     * @param [in] frame 设置屏幕视频帧，详见：IVideoFrame{@link #IVideoFrame}。  <br>
     * @return  <br>
     *        + true: 成功；  <br>
     *        + false: 失败；  <br>
     * @notes  <br>
     *       + 暂时只支持 YUV420P 格式的视频帧。  <br>
     *       + 该函数运行在用户调用线程内，即将销毁 RtcEngine 实例前，请停止调用该函数推送屏幕共享数据  <br>
     */
    virtual bool PushScreenFrame(IVideoFrame* frame) = 0;

    /**
     * @hidden
     * @deprecated from 327.1, use StartScreenVideoCapture and PublishScreen instead
     * @type api
     * @region 屏幕共享
     * @brief 该方法共享一个窗口或该窗口的部分区域。用户需要在该方法中指定想要共享的窗口 id 。
     * @param [in] window_id
     *        指定待共享的窗口 id，详见：view_t{@link #view_t}
     * @param [in] region_rect
     *        指定共享区域相对于整个窗口的位置，当值都为0时共享整个窗口，详见：Rectangle{@link #Rectangle}
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes  <br>
     *       + 本函数和 PublishScreen{@link #IRtcRoom#PublishScreen} 互斥使用，当调用 StopScreenCapture{@link
     * #StopScreenCapture} 后方可再用 PublishScreen{@link #IRtcRoom#PublishScreen}。  <br>
     *       + 本函数和 StopScreenCapture{@link #StopScreenCapture} 是成对调用的。  <br>
     *       + 在收到 OnFirstRemoteVideoFrameRendered{@link #IRTCRoomEventHandler#OnFirstRemoteVideoFrameRendered}
     *         事件后通过调用 SetRemoteVideoCanvas{@link #SetRemoteVideoCanvas} 或 SetRemoteVideoSink{@link #SetRemoteVideoSink}
     *         函数来设置远端屏幕共享视图。  <br>
     *       + 本地可调用 SetLocalVideoCanvas{@link #IRtcEngineLite#SetLocalVideoCanvas} 或 SetLocalVideoSink{@link
     * #SetLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 RegisterVideoFrameObserver{@link #RegisterVideoFrameObserver} 视频回调对象，监听
     * OnLocalScreenFrame{@link #IVideoFrameObserver#OnLocalScreenFrame} 本地屏幕视频回调事件和
     * OnRemoteScreenFrame{@link #IVideoFrameObserver#OnRemoteScreenFrame} 远端屏幕共享视频回调事件来获取原始数据。 <br>
     */
    virtual int StartScreenCaptureByWindowId(
            view_t window_id, const Rectangle& region_rect, const DesktopCaptureParameters& capture_params) = 0;

    /**
     * @hidden
     * @deprecated from 327.1, use StartScreenVideoCapture and PublishScreen instead
     * @type api
     * @region 屏幕共享
     * @brief 通过指定区域共享屏幕，共享一个屏幕或该屏幕的部分区域。用户需要在该方法中指定想要共享的屏幕区域。
     * @param [in] screen_rect
     *        指定待共享的屏幕相对于虚拟屏的位置，虚拟屏指所有屏幕组成的图像区域，详见：Rectangle{@link #Rectangle}
     * @param [in] region_rect
     *        指定待共享区域相对于screen_rect的位置，详见：Rectangle{@link #Rectangle}
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes  <br>
     *       + 本函数和 PublishScreen{@link #IRtcRoom#PublishScreen} 互斥使用，当调用 StopScreenCapture{@link
     * #StopScreenCapture} 后方可再用 PublishScreen{@link #IRtcRoom#PublishScreen}。  <br>
     *       + 本函数和 StopScreenCapture{@link #StopScreenCapture} 是成对调用的  <br>
     *       + 在收到 OnFirstRemoteVideoFrameRendered{@link #IRTCRoomEventHandler#OnFirstRemoteVideoFrameRendered}
     *         事件后通过调用
     * SetRemoteVideoCanvas{@link #SetRemoteVideoCanvas} 或 SetRemoteVideoSink{@link #SetRemoteVideoSink}
     * 函数来设置远端屏幕共享视图。  <br>
     *       + 本地可调用 SetLocalVideoCanvas{@link #IRtcEngineLite#SetLocalVideoCanvas} 或 SetLocalVideoSink{@link
     * #SetLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 RegisterVideoFrameObserver{@link #RegisterVideoFrameObserver} 视频回调对象，监听
     * OnLocalScreenFrame{@link #IVideoFrameObserver#OnLocalScreenFrame} 本地屏幕视频回调事件和
     * OnRemoteScreenFrame{@link #IVideoFrameObserver#OnRemoteScreenFrame} 远端屏幕共享视频回调事件来获取原始数据。 <br>
     */
    virtual int StartScreenCaptureByScreenRect(const Rectangle& screen_rect, const Rectangle& region_rect,
            const DesktopCaptureParameters& capture_params) = 0;

    /**
     * @hidden(iOS,Android)
     * @deprecated from 327.1, use StartScreenVideoCapture and PublishScreen instead
     * @type api
     * @region 屏幕共享
     * @brief 通过屏幕 id 共享屏幕，共享一个屏幕或该屏幕的部分区域。用户需要在该方法中指定想要共享的屏幕 id 。
     * @param [in] display_id
     *        指定待共享的屏幕 id 。
     * @param [in] region_rect
     *        指定待共享区域相对于整个屏幕的位置，详见：Rectangle{@link #Rectangle}
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes 共享一个窗口或该窗口的部分区域。需要在该方法中指定想要共享的窗口 id 。
     */
    virtual int StartScreenCaptureByDisplayId(
            unsigned int display_id, const Rectangle& region_rect, const DesktopCaptureParameters& capture_params) = 0;

    /**
     * @hidden(macOS,Windows)
     * @deprecated from 327.1, use StartScreenVideoCapture and PublishScreen instead
     * @type api
     * @region 屏幕共享
     * @brief 通过传入的Context开启屏幕共享。
     * @param [in] context
     *        Android平台是MediaProjection对象，由业务方申请系统录屏权限后获得, iOS上暂未用到，传空即可。
     * @param [in] group_id
     *        iOS 平台需传入 App 和 Extension 共同使用的 group id，Android平台传空即可。
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes 开启屏幕共享，移动端专用接口。
     */
    virtual int StartScreenCapture(
            void* context, const char* group_id, const DesktopCaptureParameters& capture_params) = 0;

    /**
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新采集区域。
     * @param  [in] region_rect 采集区域。参见 Rectangle{@link #Rectangle}  <br>
     *                          此参数描述了调用此接口后的采集区域，和 StartScreenVideoCapture{@link #StartScreenVideoCapture} 中 `source_info` 设定区域的相对关系。
     * @notes 调用此接口前，必须已通过调用 StartScreenVideoCapture{@link #StartScreenVideoCapture} 开启了内部屏幕流采集。
     */
    virtual void UpdateScreenCaptureRegion(const Rectangle& region_rect) = 0;

    /**
     * @hidden
     * @deprecated from 327.1, use SetVideoEncoderConfig、UpdateScreenCaptureHighlightConfig、
     *                  UpdateScreenCaptureFilterConfig、UpdateScreenCaptureMouseCursor instead
     * @type api
     * @region 屏幕共享
     * @brief 更新屏幕共享的编码参数配置。
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     */
    virtual int UpdateScreenCaptureParameters(const DesktopCaptureParameters& capture_params) = 0;

    /**
     * @type api
     * @deprecated from 327.1, use StopScreenVideoCapture instead
     * @region 屏幕共享
     * @brief 停止屏幕或者窗口共享。
     * @notes  <br>
     *       + 本函数必须在 StartScreenVideoCapture{@link #StartScreenVideoCapture} 之后调用  <br>
     *       + 本函数不可和 PublishScreen{@link #IRtcRoom#PublishScreen} 、UnpublishScreen{@link #IRtcRoom#UnpublishScreen} 混用。  <br>
     */
    virtual void StopScreenCapture() = 0;

    /**
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，应用窗口中显示的内容，或虚拟屏幕中显示的内容。<br>
     *        其中，虚拟屏幕中显示的内容仅在 Windows 平台上支持。
     * @param [in] source_info 待共享的屏幕源，参看 ScreenCaptureSourceInfo{@link #ScreenCaptureSourceInfo}。<br>
     *                         你可以调用 GetScreenCaptureSourceList{@link #IRtcEngineLite#GetScreenCaptureSourceList} 获得所有可以共享的屏幕源。
     * @param [in] capture_params 共享参数。参看 ScreenCaptureParameters{@link #ScreenCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes  <br>
     *       + 调用此方法仅开启屏幕流视频采集，不会发布采集到的视频。发布屏幕流视频需要调用 PublishScreen{@link #IRtcRoom#PublishScreen} 。<br>
     *       + 要关闭屏幕视频源采集，调用 StopScreenVideoCapture{@link #IRtcEngineLite#StopScreenVideoCapture}。  <br>
     *       + 调用成功后，本端会收到 OnFirstLocalVideoFrameCaptured{@link #IRTCRoomEventHandler#OnFirstLocalVideoFrameCaptured} 回调。<br>
     *       + 调用此接口前，你可以调用 SetVideoEncoderConfig{@link #SetVideoEncoderConfig} 设置屏幕视频流的采集帧率和编码分辨率。<br>
     *       + 在收到 OnFirstLocalVideoFrameCaptured{@link #IRTCRoomEventHandler#OnFirstLocalVideoFrameCaptured}
     * 事件后通过调用 SetLocalVideoCanvas{@link #IRtcEngineLite#SetLocalVideoCanvas} 或 SetLocalVideoSink{@link
     * #SetLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 RegisterVideoFrameObserver{@link #RegisterVideoFrameObserver} 视频回调对象，监听
     * OnLocalScreenFrame{@link #IVideoFrameObserver#OnLocalScreenFrame} 本地屏幕视频回调事件 <br>
     */
    virtual int StartScreenVideoCapture(const ScreenCaptureSourceInfo& source_info, const ScreenCaptureParameters& capture_params) = 0;

    /**
     * @hidden(macOS,Windows,iOS,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过传入的Context开启屏幕共享。
     * @param [in] context
     *        Android平台传入MediaProjection对象，由业务方申请系统录屏权限后获得。
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes 开启屏幕共享，Android专用接口。
     */
    virtual int StartScreenVideoCapture(void* context) = 0;

    /**
     * @hidden(macOS,Windows,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过传入的groupid开启屏幕共享。
     * @param [in] group_id
     *        iOS 平台需传入 App 和 Extension 共同使用的 group id。
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes 开启屏幕共享，iOS专用接口。
     */
    virtual int StartScreenVideoCapture(const char* group_id) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 屏幕共享
     * @brief 停止屏幕视频流采集。
     * @notes  <br>
     *       + 要开启屏幕视频流采集，调用 StartScreenVideoCapture{@link #StartScreenVideoCapture}  <br>
     *       + 调用此接口不影响屏幕视频流发布。  <br>
     */
    virtual void StopScreenVideoCapture() = 0;

    /**
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新边框高亮设置。默认展示表框。
     * @param [in] highlight_config 边框高亮设置。参见 HighlightConfig{@link #HighlightConfig}
     * @notes 调用此接口前，必须已通过调用 StartScreenVideoCapture{@link #StartScreenVideoCapture} 开启了内部屏幕流采集。
     */
    virtual void UpdateScreenCaptureHighlightConfig(const HighlightConfig& highlight_config) = 0;

    /**
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新对鼠标的处理设置。默认采集鼠标。
     * @param [in] capture_mouse_cursor 参看 MouseCursorCaptureState{@link #MouseCursorCaptureState}
     * @notes 调用此接口前，必须已通过调用 StartScreenVideoCapture{@link #StartScreenVideoCapture} 开启了内部屏幕流采集。
     */
    virtual void UpdateScreenCaptureMouseCursor(MouseCursorCaptureState capture_mouse_cursor) = 0;

    /**
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。
     * @param [in] ScreenFilterConfig 窗口过滤设置，参看 ScreenFilterConfig{@link #ScreenFilterConfig}  <br>
     * @notes <br>
     *       + 调用此接口前，必须已通过调用 StartScreenVideoCapture{@link #StartScreenVideoCapture} 开启了内部屏幕流采集。<br>
     *       + 本函数在屏幕源类别是屏幕而非应用窗体时才起作用。详见：ScreenCaptureSourceType{@link #ScreenCaptureSourceType}
     */
    virtual void UpdateScreenCaptureFilterConfig(const ScreenFilterConfig& filter_config) = 0;

    /**
     * @hidden(Linux)
     * @brief 获取共享对象(应用窗口和桌面)列表, 使用完之后需要调用对应的release接口释放
     * @region 屏幕共享
     * @notes  <br>
     *       + 枚举的窗体可作为开启屏幕共享时的输入参数，详见：StartScreenVideoCapture{@link #IRtcEngineLite#StartScreenVideoCapture} <br>
     *       + 本函数仅供PC端使用
     */
    virtual IScreenCaptureSourceList* GetScreenCaptureSourceList() = 0;

    /**
     * @hidden(Linux)
     * @brief 获取共享对象缩略图
     * @region 屏幕共享
     * @notes  <br>
     *        + 本函数仅供PC端使用
     */
    virtual IVideoFrame* GetThumbnail(
            ScreenCaptureSourceType type, view_t source_id, int max_width, int max_height) = 0;

    /**
     * @hidden
     * @deprecated from 324.1, use SetVideoSourceType instead
     * @type api
     * @region 视频管理
     * @brief 设置是否启用自定义视频采集
     * @param  [in] enable  <br>
     *       + true: 开启  <br>
     *       + false: 关闭
     * @notes  <br>
     *       + 1. 该方法在进房前后均可以调用。  <br>
     *       + 2. 当你已调用 StartVideoCapture{@link #StartVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
     *       + 3. 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 StartVideoCapture{@link #StartVideoCapture} 手动开启内部采集。
     */
    virtual void SetExternalVideoSource(bool enable) = 0;

    /**
     * @hidden
     * @deprecated
     * @type api
     * @region 视频管理
     * @brief 切换视频采集方式（内部采集/自定义采集）
     * @param  [in] type 视频采集方式，参看 VideoSourceType{@link #VideoSourceType}
     * @notes  <br>
     *       + 默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>
     *       + 该方法进房前后均可调用。  <br>
     *       + 当你已调用 StartVideoCapture{@link #StartVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
     *       + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 StartVideoCapture{@link #StartVideoCapture} 手动开启内部采集。
     */
    virtual void SetVideoSourceType(VideoSourceType type) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置向 SDK 输入的视频源
     * @param [in] stream_index 视频流的属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] type 视频输入源类型，参看 VideoSourceType{@link #VideoSourceType}
     * @notes  <br>
     *        + 默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>
     *        + 该方法进房前后均可调用。  <br>
     *        + 当你已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
     *        + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 StartVideoCapture{@link #StartVideoCapture} 手动开启内部采集。  <br>
     *        + 当你需要向 SDK 推送自定义编码后的视频帧，你需调用该方法将视频源切换至自定义编码视频源。
     */
    virtual void SetVideoSourceType(StreamIndex stream_index, VideoSourceType type) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 发送外部源视频数据
     * @param [in] frame 设置视频帧，参看 IVideoFrame{@link #IVideoFrame}。  <br>
     * @notes  <br>
     *       + 暂时只支持 YUV420P 格式的视频帧。  <br>
     *       + 该函数运行在用户调用线程内  <br>
     * @notes 推送外部视频帧前，必须调用 SetVideoSourceType{@link #SetVideoSourceType} 开启外部视频源采集。
     */
    virtual bool PushExternalVideoFrame(IVideoFrame* frame) = 0;

    /**
     * @hidden
     */
    virtual void SetupDynamicLayoutRender(IVideoSink* render) = 0;
#endif

    /**
     * @hidden(macOS,Windows)
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备，默认使用扬声器。  <br>
     *        音频播放设备发生变化时，会收到 OnAudioPlaybackDeviceChanged{@link
     * #IRtcEngineLiteEventHandler#OnAudioPlaybackDeviceChanged} 回调。
     * @param [in] device 音频播放设备。参看 AudioPlaybackDevice{@link #AudioPlaybackDevice} <br>
     * @return 方法调用结果  <br>
     *        + 0: 方法调用成功  <br>
     *        + <0: 方法调用失败  <br>
     * @notes  <br>
     *       + 1. 该接口仅适用于移动设备。  <br>
     *       + 2. 该方法只支持将音视频播放设备设置为听筒或者扬声器。当 App 连接有线或蓝牙音频播放设备时，SDK
     * 会自动切换到有线或蓝牙音频播放设备。主动设置为有线或蓝牙音频播放设备，会返回调用失败。  <br>
     *       + 3.
     * 若连接有线或者蓝牙音频播放设备时，将音频播放设备设置为扬声器或听筒将调用成功，但不会立马切换到扬声器或听筒，会在有线或者蓝牙音频播放设备移除后，根据设置自动切换到听筒或者扬声器。
     * <br>
     *       + 4. 通话前和通话中都可以调用该方法。  <br>
     */
    virtual int SetAudioPlaybackDevice(AudioPlaybackDevice device) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 创建并获取一个 IRTCRoom{@link #IRtcRoom} 对象  <br>
     * @param [in] room_id 标识通话房间的房间 ID，最大长度为 128 字节的非空字符串。支持的字符集范围为:  <br>
     *       + 26个大写字母 A ~ Z  <br>
     *       + 26个小写字母 a ~ z  <br>
     *       + 10个数字 0 ~ 9  <br>
     *       + 下划线 "_", at 符 "@", 减号 "-"  <br>
     *        多房间模式下，调用创建房间接口后，请勿调用同样的 roomID 创建房间，否则会导致创建房间失败。  <br>
     * @notes  <br>
     *       + 用户可以多次调用此方法创建多个 IRtcRoom{@link #IRtcRoom} 对象，再分别调用各 IRTCRoom 对象的 JoinRoom{@link #IRtcRoom#JoinRoom} 方法，实现同时加入多个房间；  <br>
     *       + 加入多个房间后，用户可以同时订阅各房间的音视频流，但是目前仅支持同一时间在一个房间内发布一路音视频流。  <br>
     */
    virtual IRtcRoom* CreateRtcRoom(const char* room_id) = 0;

    /**
     * @type api
     * @region 音视频回退
     * @brief 设置发布的音视频流回退选项  <br>
     *       你可以调用这个接口来设置网络情况不佳或设备性能不足时只发送小流，以保证通话质量。
     * @param [in] option 本地发布的音视频流回退选项  <br>
     *       + 0：（默认）上行网络较弱或性能不佳时，不对音视频流作回退处理。  <br>
     *       + 1：上行网络较弱或性能不佳时，只发送视频小流。
     * @return  <br>
     *        + 0: 方法调用成功  <br>
     *        + <0: 方法调用失败
     * @notes  <br>
     *       + 这个方法只在设置了发送多个流的情况下有效。  <br>
     *       + 你必须在进房前设置，进房后设置或更改设置无效。  <br>
     *       + 设置回退选项后，本端发布的音视频流发生回退或从回退中恢复时，订阅该音视频流的客户端会收到
     * OnSimulcastSubscribeFallback{@link #OnSimulcastSubscribeFallback} 回调通知。  <br>
     *       + 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用
     * API 设定的配置。
     */
    virtual int SetPublishFallbackOption(PublishFallbackOption option) = 0;

    /**
     * @type api
     * @region 音视频回退
     * @brief 设置订阅的音视频流回退选项  <br>
     *        你可以通过调用该接口来设置网络情况不佳或性能不足时只订阅小流或音频流，以保证通话质量。
     * @param [in] option 远端订阅流回退处理选项，详见枚举类型 SubscribeFallbackOption{@link #SubscribeFallbackOption}
     * @return 0: 方法调用成功  <br>
     *        + <0: 方法调用失败
     *  @notes  <br>
     *        + 你必须在进房前设置，进房后设置或更改设置无效。  <br>
     *        + 设置回退选项后，本端订阅的音视频流发生回退或从回退中恢复时,会收到 OnSimulcastSubscribeFallback{@link
     * #OnSimulcastSubscribeFallback} 回调通知。  <br>
     *        + 设置回退选项后，本端订阅的视频流因为回退分辨率发生变化时,会收到 OnRemoteVideoSizeChanged{@link
     * #OnRemoteVideoSizeChanged} 回调通知。  <br>
     *        + 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用
     * API 设定的配置。
     */
    virtual int SetSubscribeFallbackOption(SubscribeFallbackOption option) = 0;

    /**
     * @type api
     * @region 音视频回退
     * @brief 设置用户优先级
     * @param [in] user_id 远端用户的 ID
     * @param [in] priority 远端用户的需求优先级，详见枚举类型RemoteUserPriority{@link #RemoteUserPriority}
     * @return 0: 方法调用成功  <br>
     *        + <0: 方法调用失败  <br>
     * @notes  <br>
     *        + 1. 该方法与 SetSubscribeFallbackOption{@link #SetSubscribeFallbackOption} 搭配使用。  <br>
     *        + 2. 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
     *        + 3. 该方法在进房前后都可以使用，可以修改远端用户的优先级。  <br>
     */
    virtual int SetRemoteUserPriority(const char* user_id, RemoteUserPriority priority) = 0;

    /**
     * @type api
     * @region 引擎管理
     * @brief 设置业务标识参数。  <br>
     *        可通过 business_id 区分不同的业务场景（角色/策略等）。business_id 由客户自定义，相当于一个“标签”，
     *        可以分担和细化现在 AppId 的逻辑划分的功能。
     * @param [in] business_id  <br>
     *        用户设置的自己的 business_id 值。business_id 相当于一个 sub AppId，可以分担和细化现在 AppId
     * 的逻辑划分的功能， 但不需要鉴权。business_id 只是一个标签，颗粒度需要用户自定义。
     * @return  <br>
     *        + 0： 成功。  <br>
     *        + <0： 失败，具体原因参照 BusinessCheckCode{@link #BusinessCheckCode} 。  <br>
     *        + -6001： 用户已经在房间中。  <br>
     *        + -6002：
     * 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @
     * 。
     * @notes  <br>
     *        + 需要在调用 JoinRoom{@link #JoinRoom} 之前调用，JoinRoom{@link #JoinRoom}之后调用该方法无效。
     */
    virtual int SetBusinessId(const char* business_id) = 0;

    /**
     * @hidden
     * @type api
     * @region 视频特效
     * @brief 开启背景并设置背景模式与分割模式
     * @param [in] mode 背景模式，参看 BackgroundMode{@link #BackgroundMode}。  <br>
     * @param [in] divide_model 分割模型，参看 DivideMode{@link #DivideMode}。  <br>
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     */
    virtual int ReplaceBackground(BackgroundMode mode, DivideMode divide_model) = 0;

    /**
     * @type api
     * @region 视频特效
     * @brief 关闭背景
     */
    virtual void DisableBackground() = 0;

    /**
     * @deprecated from 329.1, use SetLocalVideoMirrorType instead
     * @type api
     * @region 视频管理
     * @brief 设置采用前置摄像头采集时，是否开启镜像模式。 <br>
     * @param  [in] mirrorMode 是否开启镜像模式
     */
    virtual void SetLocalVideoMirrorMode(MirrorMode mirrorMode) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 为本地采集到的视频流开启镜像
     * @param [in] mirrorType 设置镜像类型，参看 MirrorType{@link #MirrorType}
     * @notes <br>
     *        + 该接口调用前，各视频源的初始状态如下：<br>
     *        <table>
     *           <tr><th></th><th>前置摄像头</th><th>后置摄像头</th><th>自定义采集视频源</th> <th>桌面端摄像头</th> </tr>
     *           <tr><td>移动端</td><td>本地渲染镜像，编码传输不镜像</td><td> 本地渲染不镜像，编码传输不镜像 </td><td> 本地渲染不镜像，编码传输不镜像 </td><td>/</td></tr>
     *           <tr><td>桌面端</td><td>/</td><td>/</td><td> 本地渲染不镜像，编码传输不镜像 </td><td> 本地渲染镜像，编码传输不镜像 </td></tr>
     *        </table>
     *        + 切换视频源不影响镜像设置。<br>
     *        + 屏幕视频流始终不受镜像设置影响。<br>
     */
    virtual void SetLocalVideoMirrorType(MirrorType mirrorType) = 0;

    /**
     * @hidden
     * @type api
     * @region 视频特效
     * @brief 获取视频特效接口
     * @return 视频特效接口指针
     */
    virtual IVideoEffect* GetVideoEffectInterface() = 0;

    /**
     * @type api
     * @region 加密
     * @brief 设置传输时使用内置加密的方式 <br>
     * @param encrypt_type 内置加密算法，详见 EncryptType{@link #EncryptType}
     * @param [in] encrypt_type 加密类型，详见 EncryptType{@link #EncryptType}
     * @param [in] key 加密密钥，长度限制为 36 位，超出部分将会被截断
     * @param [in] key_size 参数 key 的长度
     * @notes  <br>
     *       + 使用传输时内置加密时，使用此方法；如果需要使用传输时自定义加密，参看 OnEncryptData{@link
     * #OnEncryptData}。 内置加密和自定义加密互斥，根据最后一个调用的方法确定传输是加密的方案。  <br>
     *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
     */
    virtual void SetEncryptInfo(EncryptType encrypt_type, const char* key, int key_size) = 0;

    /**
     * @type api
     * @region 加密
     * @brief 设置自定义加密  <br>
     *        需要实现对应的加密/解密方法，详情参考 EncryptType{@link #EncryptType} 。 <br>
     * @param [in] handler 自定义加密 handler，需要实现 handler 的加密和解密方法  <br>
     * @notes  <br>
     *       + 该方法与 SetEncryptInfo{@link #SetEncryptInfo} 为互斥关系，
     *         只能选择自定义加密方式或者默认加密方式。最终生效的加密方式取决于最后一个调用的方法。  <br>
     *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
     *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在 90% ~ 120% 之间，即如果输入数据为 100
     * 字节，则处理完成后的数据必须在 90 至 120 字节之间，如果加密或解密结果超出该长度限制，则该音视频帧会被丢弃。  <br>
     *       +
     * 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率。是否使用该方法，需要由使用方谨慎评估。
     * <br>
     */
    virtual void SetCustomizeEncryptHandler(IEncryptHandler* handler) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 音频数据回调
     * @brief 设置本地麦克风录制的音频数据回调参数
     * @param [in] sample_rate 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
     * @param [in] channels 音频通道数，支持单声道（1）和双声道（2）
     * @notes 使用本方法设置参数，并使用RegisterAudioFrameObserver{@link #RegisterAudioFrameObserver}注册数据观察者，
     *        之后可以在IAudioFrameObserver{@link #IAudioFrameObserver}的
     *        OnRecordAudioFrame{@link #IAudioFrameObserver#OnRecordAudioFrame}收到数据
     */
    virtual void SetRecordingAudioFrameParameters(int sample_rate, int channels) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 音频数据回调
     * @brief 设置远端所有用户音频数据混音后的音频数据回调参数
     * @param [in] sample_rate 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
     * @param [in] channels 音频通道数，支持单声道（1）和双声道（2）
     * @notes 使用本方法设置参数，并使用RegisterAudioFrameObserver{@link #RegisterAudioFrameObserver}注册数据观察者，
     *        之后可以在IAudioFrameObserver{@link #IAudioFrameObserver}的
     *        OnPlaybackAudioFrame{@link #IAudioFrameObserver#OnPlaybackAudioFrame}收到数据
     */
    virtual void SetPlaybackAudioFrameParameters(int sample_rate, int channels) = 0;

    /**
     * @type api
     * @region 音频数据回调
     * @brief 设置本地麦克风录制音频数据和远端所有用户音频数据混音后的音频数据回调参数
     * @param [in] sample_rate 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
     * @param [in] channels 音频通道数，支持单声道（1）和双声道（2）
     * @notes 使用本方法设置参数，并使用RegisterAudioFrameObserver{@link #RegisterAudioFrameObserver}注册数据观察者，
     *        之后可以在IAudioFrameObserver{@link #IAudioFrameObserver}的
     *        OnMixedAudioFrame{@link #IAudioFrameObserver#OnMixedAudioFrame}收到数据
     */
    virtual void SetMixedAudioFrameParameters(int sample_rate, int channels) = 0;

    /**
     * @type api
     * @region 音频数据回调
     * @brief 注册音频数据回调观察者
     * @param [in] observer 音频数据观察者，详见：IAudioFrameObserver{@link #IAudioFrameObserver}
     * @notes 本方法需要与下面3个方法配合使用：
     *        SetRecordingAudioFrameParameters{@link #SetRecordingAudioFrameParameters}、
     *        SetPlaybackAudioFrameParameters{@link #SetPlaybackAudioFrameParameters}、
     *        SetMixedAudioFrameParameters{@link #SetMixedAudioFrameParameters}
     */
    virtual void RegisterAudioFrameObserver(IAudioFrameObserver* observer) = 0;


    /**
     * @type api
     * @region 音频处理
     * @brief 设置自定义音频处理器。  <br>
     *        使用该处理器，你可以调用 ProcessAudioFrame{@link #IAudioProcessor#ProcessAudioFrame} 对 RTC SDK 采集得到的音频帧进行自定义处理，并将处理后的音频帧用于 RTC 音视频通信。  <br>
     *        SDK 只持有 processor 的弱引用，你应保证其生命周期。
     * @param [in] processor 自定义音频处理器，参看 IAudioProcessor{@link #IAudioProcessor}。如果传入 null，则不对 RTC SDK 采集得到的音频帧进行自定义处理。
     * @param [in] audioFormat 自定义音频参数格式，参看 AudioFormat{@link #AudioFormat}，SDK 将按指定设置给出音频帧。
     * @notes 重复调用此接口时，仅最后一次调用生效。效果不会叠加。
     */
    virtual void RegisterLocalAudioProcessor(IAudioProcessor* processor, AudioFormat audioFormat) = 0;

    /**
     * @type api
     * @region 视频数据回调
     * @brief 注册视频数据回调观察者
     * @param [in] observer 数据回调函数，详见： IVideoFrameObserver{@link #IVideoFrameObserver} 。
     * @notes  <br>
     *       + 该方法可以在任意时间调用，建议在 JoinRoom{@link #JoinRoom} 前。  <br>
     *       + 本接口支持动态取消注册，将参数设置为 nullptr 取消注册。  <br>
     */
    virtual void RegisterVideoFrameObserver(IVideoFrameObserver* observer) = 0;

    /**
      * @type api
      * @region 视频处理
      * @brief 设置自定义视频前处理器。<br>
      *        使用这个视频前处理器，你可以调用 ProcessVideoFrame{@link #IVideoProcessor#ProcessVideoFrame} 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。
      * @param [in] processor 自定义视频处理器，详见 IVideoProcessor{@link #IVideoProcessor}。如果传入 null，则不对 RTC SDK 采集得到的视频帧进行前处理。<br>
      *        SDK 只持有 processor 的弱引用，你应保证其生命周期。
      * @param [in] config 自定义视频前处理器适用的设置，详见 VideoPreprocessorConfig{@link #VideoPreprocessorConfig}。<br>
      *               当前，`config` 中的 `required_pixel_format` 仅支持：`kVideoPixelFormatI420` 和 `kVideoPixelFormatUnknown`：<br>
      *               + 设置为 `kVideoPixelFormatUnknown` 时，RTC SDK 给出供 processor 处理的视频帧格式即采集的格式。
      *                 你可以通过 frame_type{@link #IVideoFrame#frame_type} 和 pixel_format{@link #IVideoFrame#pixel_format} 获取实际采集的视频帧格式和像素类型。<br>
      *               + 设置为 `kVideoPixelFormatI420` 时，RTC SDK 会将采集得到的视频帧转变为对应的格式，供前处理使用。<br>
      *               + 设置为其他值时，此方法调用失败。
      * @return <br>
      *         + 0：方法调用成功 <br>
      *         + !0：方法调用失败 <br>
      * @notes  <br>
      *        + 对于 Windows 平台，经前处理返回的视频帧格式仅支持 `kVideoPixelFormatI420` <br>
      *        + 对于 Windows 平台，将 `config` 中的 required_pixel_format 设置为 `kVideoPixelFormatI420`，可以通过避免格式转换带来一些性能优化。<br>
      *        + 重复调用此接口时，仅最后一次调用生效。效果不会叠加。
      */
    virtual int RegisterLocalVideoProcessor(IVideoProcessor* processor, VideoPreprocessorConfig config) = 0;

    /**
     * @hidden
     * @deprecated
     * @type api
     * @region 视频数据回调
     * @brief 注册 metadata 观察者，用于接收或发送 metadata，底层通过在视频帧中添加 SEI 数据实现该功能。  <br>
     *        注册观察者后，发送的视频帧里面没有 SEI 信息， 会触发 OnReadyToSendMetadata{@link
     * #IMetadataObserver#OnReadyToSendMetadata} 回调。  <br> 注册观察者后，接收的视频帧里面有 SEI 信息，会触发接收
     * OnMetadataReceived{@link #IMetadataObserver#OnMetadataReceived} 回调。  <br>
     * @param [in] observer metadata 观察者，详见：IMetadataObserver{@link #IMetadataObserver}
     * @notes  <br>
     *      + 使用视频自定义采集与渲染时，可以直接在视频帧中添加与获取 metadata，不建议使用本接口。
     *      + 本接口支持动态取消注册，将参数设置为 nullptr 取消注册。  <br>
     */
    virtual void RegisterMetadataObserver(IMetadataObserver* observer) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 在视频通信时，通过视频帧发送 SEI 数据。
     * @param [in] stream_index 媒体流类型，参看 StreamIndex{@link #StreamIndex}
     * @param [in] message SEI 消息。长度不超过 4 kB。<br>
     * @param [in] length SEI 消息长度。<br>
     * @param [in] 消息发送重复次数。取值范围是 [0, 30]。<br>
     *                    调用此接口后，SEI 数据会添加到当前视频帧开始的连续 `repeatCount` 个视频帧中。
     * @return <br>
     *        + >=0: 将被添加到视频帧中的 SEI 的数量  <br>
     *        + < 0: 发送失败
     * @notes <br>
     *        + 你可以通过此接口对 RTC SDK 内部采集的视频帧添加 SEI。对于采用自定义采集获得的视频帧：如果原视频帧中没有添加 SEI 数据，那么你可以调用此接口为其中添加 SEI 信息后，进行编码传输；如果原视频帧中已添加了 SEI 数据，那么，调用此接口不生效。<br>
     *        + 如果调用此接口之后的 2s 内，没有可带 SEI 的视频帧（比如没有开启视频采集和传输），那么，SEI 数据不会被加进视频帧中。
     *        + 消息发送成功后，远端会收到 OnSEIMessageReceived{@link #IRtcEngineLiteEventHandler#OnSEIMessageReceived} 回调。
     */
    virtual int SendSEIMessage(StreamIndex stream_index, const uint8_t* message, int length, int repeat_count) = 0;

    /**
     * @hidden
     * @deprecated
     * @type api
     * @region 房间管理
     * @brief 设置引擎自动发布属性
     * @param [in] engine
     *       要设置的引擎，详见：{@link #IRtcEngine}
     * @param [in] auto_publish
     *       是否自动发布流，默认是true自动发布，设置false时可通过engine->publish()、engine->unpublish()来发布和取消发布本地流
     * @notes
     * 设置引擎是否自动发布用户的本地流，必须在joinChannel前调用。engine引擎默认auto_publish为true。当auto_publish为true时engine->publish()、
     * engine->unpublish()接口不应当被调用。
     */
    virtual void EnableAutoPublish(bool auto_publish) = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 视频设备管理
     * @brief 创建视频设备管理实例
     * @return 视频设备管理实例，详见IVideoDeviceManager{@link #IVideoDeviceManager}
     * @notes 当不再使用IVideoDeviceManager实例时，调用该实例的 Release{@link #Release}
     * 接口，以免资源泄露
     */
    virtual IVideoDeviceManager* GetVideoDeviceManager() = 0;

    /**
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 设备音频管理接口创建
     * @return 音频设备管理接口
     */
    virtual IAudioDeviceManager* GetAudioDeviceManager() = 0;


    /**
     * @type api
     * @region 音频管理
     * @brief 获取位置音频接口实例，包括范围语音、空间语音等和位置相关的音频接口。  <br>
     * @return 位置音频管理接口实例。如果返回 NULL，则表示不支持空间音频，详见 IPositionAudioRenderInterface{@link #IPositionAudioRenderInterface} 。  <br>
     * @notes  <br>
     *       + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
     *       + 在网络状况不佳的情况下，即使开启了这一功能，也不会产生空间音频效果；  <br>
     *       + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
     *       + 空间音频效果在启用服务端选路功能时，不生效。  <br>
     */
    virtual IPositionAudioRenderInterface* GetPositionAudioRender() = 0;

    /**
     * @hidden
     * @type api
     * @region 音频数据回调
     * @brief 注册音频数据回调观察者。
     * @param [in] observer 音频数据回调观察者，详见 IRemoteAudioFrameObserver{@link #IRemoteAudioFrameObserver}
     * @notes  <br>
     *         注册该回调，可以收到单个远端用户的 PCM 数据。
     */
    virtual void RegisterRemoteAudioFrameObserver(IRemoteAudioFrameObserver* observer) = 0;

    /**
     * @type api
     * @region 本地录制
     * @brief 该方法将通话过程中的音视频数据录制到本地的文件中。
     * @param [in] type 流属性，指定录制主流还是屏幕流，参看 StreamIndex{@link #StreamIndex}
     * @param [in] config 本地录制参数配置，参看 RecordingConfig{@link #RecordingConfig}
     * @return  <br>
     *        + 0: 正常
     *        + -1: 参数设置异常
     *        + -2: 当前版本 SDK 不支持该特性，请联系技术支持人员
     * @notes  <br>
     *        + 调用该方法后，你会收到 OnRecordingStateUpdate{@link #OnRecordingStateUpdate} 回调。  <br>
     *        + 如果录制正常，系统每秒钟会通过 OnRecordingProgressUpdate{@link #OnRecordingProgressUpdate}
     * 回调通知录制进度。
     */
    virtual int StartFileRecording(StreamIndex type, RecordingConfig config) = 0;

    /**
     * @type api
     * @region 本地录制
     * @brief 停止本地录制
     * @param [in] type 流属性，指定停止主流或者屏幕流录制，参看 StreamIndex{@link #StreamIndex}
     * @notes  <br>
     *        + 调用 StartFileRecording{@link #StartFileRecording} 开启本地录制后，你必须调用该方法停止录制。  <br>
     *        + 调用该方法后，你会收到 OnRecordingStateUpdate{@link #OnRecordingStateUpdate} 回调提示录制结果。
     */
    virtual void StopFileRecording(StreamIndex type) = 0;

    /**
     * @type api
     * @region 引擎管理
     * @brief 设置运行时的参数
     * @param [in] json_string  json 序列化之后的字符串
     * @notes
     */
    virtual void SetRuntimeParameters(const char * json_string) = 0;

    /**
     * @type api
     * @region 语音识别服务
     * @brief 开启自动语音识别服务。该方法将识别后的用户语音转化成文字，并通过 OnMessage{@link #OnMessage}
     * 事件回调给用户。
     * @param [in] asr_config 校验信息，参看 RTCASRConfig{@link #RTCASRConfig}
     * @param [in] handler 语音识别服务使用状态回调，参看 IRTCASREngineEventHandler{@link #IRTCASREngineEventHandler}
     */
    virtual void StartASR(const RTCASRConfig& asr_config, IRTCASREngineEventHandler* handler) = 0;

    /**
     * @type api
     * @region 语音识别服务
     * @brief 关闭语音识别服务
     */
    virtual void StopASR() = 0;

    /**
     * @type api
     * @region 引擎管理
     * @brief 本次通话质量打分评价
     * @param [in] data 上报的数据。JSON 格式，必须包含以下 4 个字段: <br>
     *        + types: 预设的问题类型集合，可多选。具体的类型参考 ProblemFeedbackOption{@link #ProblemFeedbackOption}  <br>
     *        + problem_desc: 预设问题以外的其他问题的具体描述  <br>
     *        + os_version: 系统版本  <br>
     *        + network_type: 网络类型：包括 WiFi, 2g, 3g, 4g, 5g。如果是台式机，填写 pc 。<br>
     * @return <br>
     *        +  0: 上报成功  <br>
     *        + -1: 上报失败，还没加入过房间  <br>
     *        + -2: 上报失败，传入 JSON 解析失败  <br>
     *        + -3: 上报失败，传入 JSON 字段缺失  <br>
     * @notes 如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；
     *        如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。
     */
    virtual int Feedback(const char* data) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 混音管理接口创建
     * @return 混音管理实例，详见IAudioMixingManager{@link #IAudioMixingManager}
     */
    virtual IAudioMixingManager* GetAudioMixingManager() = 0;

    /**
     * @type api
     * @region 实时消息通信
     * @brief 必须先登录注册一个 uid，才能发送房间外消息和向业务服务器发送消息
     * @param [in] token  <br>
     *        动态密钥  <br>
     *        用户登录必须携带的 Token，用于鉴权验证。  <br>
     *        本 Token 与加入房间时必须携带的 Token 不同。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。
     * @param [in] uid  <br>
     *        用户 ID  <br>
     *        用户 ID 在 appid 的维度下是唯一的。
     * @notes  <br>
     *       + 在调用本接口登录后，如果想要登出，需要调用 Logout{@link #IRtcEngineLite#Logout}。  <br>
     *       + 本地用户调用此方法登录后，会收到 OnLoginResult{@link #IRtcEngineLiteEventHandler#OnLoginResult} 回调通知登录结果，远端用户不会收到通知。
     */
    virtual void Login(const char* token, const char* uid) = 0;
    /**
     * @type api
     * @region 实时消息通信
     * @brief 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
     * @notes  <br>
     *       + 调用本接口登出前，必须先调用 Login{@link #IRtcEngineLite#Login} 登录。  <br>
     *       + 本地用户调用此方法登出后，会收到 OnLogout{@link #IRtcEngineLiteEventHandler#OnLogout} 回调通知结果，远端用户不会收到通知。
     */
    virtual void Logout() = 0;
    /**
     * @type api
     * @region 实时消息通信
     * @brief 更新用户用于登录的 Token  <br>
     *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
     *        调用 Login{@link #IRtcEngineLite#Login} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 OnLoginResult{@link #IRtcEngineLiteEventHandler#OnLoginResult} 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
     * @param [in] token  <br>
     *        更新的动态密钥
     * @notes  <br>
     *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 Login{@link #IRtcEngineLite#Login} 方法。  <br>
     *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
     */
    virtual void UpdateLoginToken(const char* token) = 0;
    /**
     * @type api
     * @region 实时消息通信
     * @brief 设置业务服务器参数  <br>
     *        客户端调用 SendServerMessage{@link #IRtcEngineLite#SendServerMessage} 或 SendServerBinaryMessage{@link #IRtcEngineLite#SendServerBinaryMessage} 发送消息给业务服务器之前，必须设置有效签名和业务服务器地址。
     * @param [in] signature  <br>
     *        动态签名  <br>
     *        业务服务器会使用该签名对请求进行鉴权验证。
     * @param [in] url  <br>
     *        业务服务器的地址
     * @notes  <br>
     *       + 用户必须调用 Login{@link #IRtcEngineLite#Login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 OnServerParamsSetResult{@link #IRtcEngineLiteEventHandler#OnServerParamsSetResult} 返回相应结果。
     */
    virtual void SetServerParams(const char* signature, const char* url) = 0;
    /**
     * @type api
     * @region 实时消息通信
     * @brief 查询对端用户或本端用户的登录状态
     * @param [in] peer_user_id  <br>
     *        需要查询的用户 ID
     * @notes  <br>
     *       + 必须调用 Login{@link #IRtcEngineLite#Login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 OnGetPeerOnlineStatus{@link #IRtcEngineLiteEventHandler#OnGetPeerOnlineStatus} 回调通知查询结果。  <br>
     *       + 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
     */
    virtual void GetPeerOnlineStatus(const char* peer_user_id) = 0;
    /**
     * @type api
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送文本消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] message  <br>
     *        发送的文本消息内容  <br>
     *        消息不超过 62KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建  <br>
     *        + -2：发送失败，uid 为空
     * @notes  <br>
     *       + 在发送房间外文本消息前，必须先调用 Login{@link #IRtcEngineLite#Login} 完成登录。  <br>
     *       + 用户调用本接口发送文本信息后，会收到一次 OnUserMessageSendResultOutsideRoom{@link #IRtcEngineLiteEventHandler#OnUserMessageSendResultOutsideRoom} 回调，得知消息是否成功发送。  <br>
     *       + 若文本消息发送成功，则 uid 所指定的用户会通过 OnUserMessageReceivedOutsideRoom{@link #IRtcEngineLiteEventHandler#OnUserMessageReceivedOutsideRoom} 回调收到该消息。
     */
    virtual int64_t SendUserMessageOutsideRoom(const char* uid, const char* message) = 0;
    /**
     * @type api
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送二进制消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] length <br>
     *        二进制字符串的长度
     * @param [in] message  <br>
     *        发送的二进制消息内容  <br>
     *        消息不超过 46KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建  <br>
     *        + -2：发送失败，uid 为空
     * @notes  <br>
     *       + 在发送房间外二进制消息前，必须先调用 Login{@link #IRtcEngineLite#Login} 完成登录。  <br>
     *       + 用户调用本接口发送二进制消息后，会收到一次 OnUserMessageSendResultOutsideRoom{@link #IRtcEngineLiteEventHandler#OnUserMessageSendResultOutsideRoom} 回调，通知消息是否发送成功。  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会通过 OnUserBinaryMessageReceivedOutsideRoom{@link #IRtcEngineLiteEventHandler#OnUserBinaryMessageReceivedOutsideRoom} 回调收到该条消息。
     */
    virtual int64_t SendUserBinaryMessageOutsideRoom(const char* uid, int length, const uint8_t* message) = 0;
    /**
     * @type api
     * @region 实时消息通信
     * @brief 客户端给业务服务器发送文本消息（P2Server）
     * @param [in] message  <br>
     *        发送的文本消息内容  <br>
     *        消息不超过 62KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建
     * @notes  <br>
     *       + 在向业务服务器发送文本消息前，必须先调用 Login{@link #IRtcEngineLite#Login} 完成登录，随后调用 SetServerParams{@link #IRtcEngineLite#SetServerParams} 设置业务服务器。  <br>
     *       + 调用本接口后，会收到一次 OnServerMessageSendResult{@link #IRtcEngineLiteEventHandler#OnServerMessageSendResult} 回调，通知消息发送方是否发送成功。  <br>
     *       + 若文本消息发送成功，则之前调用 SetServerParams{@link #IRtcEngineLite#SetServerParams} 设置的业务服务器会收到该条消息。
     */
    virtual int64_t SendServerMessage(const char* message) = 0;
    /**
     * @type api
     * @region 实时消息通信
     * @brief 客户端给业务服务器发送二进制消息（P2Server）
     * @param [in] length <br>
     *        二进制字符串的长度
     * @param [in] message  <br>
     *        发送的二进制消息内容  <br>
     *        消息不超过 46KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建
     * @notes  <br>
     *       + 在向业务服务器发送二进制消息前，必须先调用 Login{@link #IRtcEngineLite#Login} 完成登录，随后调用 SetServerParams{@link #IRtcEngineLite#SetServerParams} 设置业务服务器。  <br>
     *       + 调用本接口后，会收到一次 OnServerMessageSendResult{@link #IRtcEngineLiteEventHandler#OnServerMessageSendResult} 回调，通知消息发送方发送成功或失败。  <br>
     *       + 若二进制消息发送成功，则之前调用 SetServerParams{@link #IRtcEngineLite#SetServerParams} 设置的业务服务器会收到该条消息。
     */
    virtual int64_t SendServerBinaryMessage(int length, const uint8_t* message) = 0;

    /**
     * @hidden(Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）
     * @param [in] source_type 屏幕音频输入源类型, 参看 AudioSourceType{@link #AudioSourceType}
     * @notes  <br>
     *      + 默认采集方式是 RTC SDK 内部采集。<br>
     *      + 你应该在 PublishScreen{@link #IRtcRoom#PublishScreen} 前，调用此方法。否则，你将收到 OnWarning{@link #IRtcEngineLiteEventHandler#OnWarning} 的报错：`kWarningCodeSetScreenAudioSourceTypeFailed` <br>
     *      + 如果设定为内部采集，你必须再调用 StartScreenAudioCapture{@link #IRtcEngineLite#StartScreenAudioCapture} 开始采集；<br>
     *      + 如果设定为自定义采集，你必须再调用 PushScreenAudioFrame{@link #IRtcEngineLite#PushScreenAudioFrame} 将自定义采集到的屏幕音频帧推送到 RTC SDK。<br>
     *      + 无论是内部采集还是自定义采集，你都必须调用 PublishScreen{@link #IRtcRoom#PublishScreen} 将采集到的屏幕音频推送到远端。
     */
    virtual void SetScreenAudioSourceType(AudioSourceType source_type) = 0;

    /**
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式
     * @param [in] index 混流方式，参看 StreamIndex{@link #StreamIndex} <br>
     *        + `kStreamIndexMain`: 将屏幕音频流和麦克风采集到的音频流混流 <br>
     *        + `kStreamIndexScreen`: 将屏幕音频流和麦克风采集到的音频流分为两路音频流
     * @notes 你应该在 PublishScreen{@link #IRtcRoom#PublishScreen} 之前，调用此方法。否则，你将收到 OnWarning{@link #IRtcEngineLiteEventHandler#OnWarning} `的报错：kWarningCodeSetScreenAudioStreamIndexFailed`
     */
    virtual void SetScreenAudioStreamIndex(StreamIndex index) = 0;

    /**
     * @hidden(Android,iOS,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
     * @notes <br>
     *        + 采集后，你还需要调用 PublishScreen{@link #IRtcRoom#PublishScreen} 将采集到的屏幕音频推送到远端。<br>
     *        + 要关闭屏幕音频内部采集，调用 StopScreenAudioCapture{@link #IRtcEngineLite#StopScreenAudioCapture}。
     */
    virtual void StartScreenAudioCapture() = 0;

   /**
    * @hidden(Android,iOS,Linux)
    * @type api
    * @region 屏幕共享
    * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。
    * @notes 要开始屏幕音频内部采集，调用 StartScreenAudioCapture{@link #IRtcEngineLite#StartScreenAudioCapture}。
    */
    virtual void StopScreenAudioCapture() = 0;

    /**
     * @type api
     * @region 屏幕共享
     * @brief 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。
     * @param [in] frame 音频数据帧，参见 IAudioFrame{@link #IAudioFrame}
     * @return 方法调用结果  <br>
     *        + 0: 设置成功  <br>
     *        + <0: 设置失败  <br>
     * @notes  <br>
     *        + 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 SetScreenAudioSourceType{@link #IRtcEngineLite#SetScreenAudioSourceType} 开启屏幕音频自定义采集。  <br>
     *        + 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  <br>
     *        + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples * frame.channel * 2。  <br>
     *        + 此函数运行在用户级线程内。若同时运行其他进程，将导致本进程中断。  <br>
     *        + 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 PublishScreen{@link #IRtcRoom#PublishScreen} 将采集到的屏幕音频推送到远端。在调用 PublishScreen{@link #IRtcRoom#PublishScreen} 前，推送到 RTC SDK 的音频帧信息会丢失。
     */
    virtual int PushScreenAudioFrame(IAudioFrame* frame) = 0;

    /**
     * @type api
     * @region 音频管理
     * @brief 启用音量提示。  <br>
     * @param config 音频信息提示的相关配置，详见 AudioPropertiesConfig{@link #AudioPropertiesConfig}  <br>
     * @notes 开启提示后，你可以：  <br>
     *       + 通过 OnLocalAudioPropertiesReport{@link #IRtcEngineLiteEventHandler#OnLocalAudioPropertiesReport} 回调获取本地麦克风和屏幕音频流采集的音量信息；  <br>
     *       + 通过 OnRemoteAudioPropertiesReport{@link #IRtcEngineLiteEventHandler#OnRemoteAudioPropertiesReport} 回调获取订阅的远端用户的音量信息。  <br>
     */
    virtual void EnableAudioPropertiesReport(const AudioPropertiesConfig& config) = 0;

    /**
     * @type api
     * @region 视频数据回调
     * @brief 注册本地视频帧监测器。  <br>
     *        无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 OnLocalEncodedVideoFrame{@link #OnLocalEncodedVideoFrame} 回调给用户
     * @param [in] engine 需设置的引擎，参看 IRtcEngine{@link #IRtcEngine}
     * @param [in] observer 本地视频帧监测器，参看 ILocalEncodedVideoFrameObserver{@link #ILocalEncodedVideoFrameObserver}。将参数设置为 nullptr 则取消注册。
     * @notes 该方法可在进房前后的任意时间调用，调用越早，对视频帧的监测越早
     */
    virtual void RegisterLocalEncodedVideoFrameObserver(ILocalEncodedVideoFrameObserver* observer) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 注册远端编码后视频数据回調。  <br>
     *        完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 OnRemoteEncodedVideoFrame{@link #OnRemoteEncodedVideoFrame} 回调
     * @param [in] observer 远端编码后视频数据监测器，参看 IRemoteEncodedVideoFrameObserver{@link #IRemoteEncodedVideoFrameObserver}
     * @notes  <br>
     *       + 该方法需在进房前调用。 <br>
     *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
     */
    virtual void RegisterRemoteEncodedVideoFrameObserver(IRemoteEncodedVideoFrameObserver* observer) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 注册自定义编码帧推送事件回调
     * @param [in] encoder_handler 自定义编码帧回调类，参看 IExternalVideoEncoderEventHandler{@link #IExternalVideoEncoderEventHandler}
     * @notes  <br>
     *       + 该方法需在进房前调用。 <br>
     *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
     */
    virtual void SetExternalVideoEncoderEventHandler(IExternalVideoEncoderEventHandler* encoder_handler) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 推送自定义编码后的视频流
     * @param [in] index 需要推送的编码流的属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] video_index 对应的编码流下标，从 0 开始，如果调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 设置了多路流，此处数量须与之保持一致
     * @param [in] video_stream 编码流视频帧信息，参看 IEncodedVideoFrame{@link #IEncodedVideoFrame}。  <br>
     * @notes  <br>
     *        + 目前仅支持推送 H264 和 ByteVC1 格式的视频帧。  <br>
     *        + 该函数运行在用户调用线程内  <br>
     *        + 推送自定义编码视频帧前，必须调用 SetVideoSourceType{@link #IRtcEngineLite#SetVideoSourceType} 将视频输入源切换至自定义编码视频源。
     */
    virtual bool PushExternalEncodedVideoFrame(StreamIndex index, int video_index, IEncodedVideoFrame* video_stream) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 在订阅远端视频流之前，设置远端视频数据解码方式
     * @param [in] key 远端流信息，即对哪一路视频流进行解码方式设置，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] config 视频解码方式，参看 VideoDecoderConfig{@link #VideoDecoderConfig}。
     * @notes  <br>
     *        + 该方法近适用于手动订阅模式，并且在订阅远端流之前使用。  <br>
     *        + 当你想要对远端流进行自定义解码时，你需要先调用 RegisterRemoteEncodedVideoFrameObserver{@link #IRtcEngineLite#RegisterRemoteEncodedVideoFrameObserver} 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 OnRemoteEncodedVideoFrame{@link #OnRemoteEncodedVideoFrame} 回调出来。
     */
    virtual void SetVideoDecoderConfig(RemoteStreamKey key, VideoDecoderConfig config) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 在订阅远端视频流之后，向远端请求关键帧
     * @param [in] stream_info 远端流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @notes  <br>
     *        + 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  <br>
     *        + 该方法适用于调用 SetVideoDecoderConfig{@link #IRtcEngineLite#SetVideoDecoderConfig} 开启自定义解码功能后，并且自定义解码失败的情况下使用
     */
    virtual void RequestRemoteVideoKeyFrame(const RemoteStreamKey& stream_info) = 0;

    /**
     * @type api
     * @region 音频管理
     * @brief 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 OnStreamSyncInfoReceived{@link #IRtcEngineLiteEventHandler#OnStreamSyncInfoReceived} 回调。
     * @param [in] data 消息内容。
     * @param [in] length 消息长度。消息长度必须是 [1,16] 字节。
     * @param [in] config 媒体流信息同步的相关配置，详见 StreamSycnInfoConfig{@link #StreamSycnInfoConfig} 。
     * @return  <br>
     *        + >=0: 消息发送成功。返回成功发送的次数。  <br>
     *        + -1: 消息发送失败。消息长度大于 16 字节。  <br>
     *        + -2: 消息发送失败。传入的消息内容为空。  <br>
     *        + -3: 消息发送失败。不支持通过屏幕流进行消息同步。  <br>
     *        + -4: 消息发送失败。通过用麦克风采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 ErrorCode{@link #ErrorCode}。  <br>
     */
    virtual int SendStreamSyncInfo(const uint8_t* data, int32_t length, const StreamSycnInfoConfig& config) = 0;
};

}  // namespace bytertc

#endif  // BYTE_RTC_LITE_INTERFACE_H__
