//
//  ByteRtcEngineKitInternal.h
//  ByteRtcEngineKit
//
//  Created by yanchangqing on 2018/7/26.
//  Copyright © 2018年 bytedance. All rights reserved.
//


#ifndef ByteRtcEngineKitInternal_h
#define ByteRtcEngineKitInternal_h

#import "byte_rtc_engine_kit.h"

/**
 * @type api
 * @region 视频设备管理
 * @brief 获取视频设备相关的信息
 */
BYTE_RTC_EXPORT @interface ByteRtcVideoDeviceCollection : NSObject

/**
 * @type api
 * @region 视频设备管理
 * @brief 获取当前系统内视频采集设备数量
 * @return 视频采集设备数量
 */
- (int)getCount;

/**
 * @type api
 * @region 视频设备管理
 * @brief 根据索引号，获取设备信息
 * @param index
 *       视频设备索引号，从0开始， 注意小于getCount{@link #ByteRtcVideoDeviceCollection#getCount}返回值
 * @param deviceName
 *       设备名称
 * @param deviceID
 *       视频设备ID
 * @return
 *      0：方法调用成功
 *      !0：方法调用失败
 */
- (int)getDevice:(int)index DeviceName:(NSString *_Nonnull*_Nonnull)deviceName DeviceID:(NSString *_Nonnull*_Nonnull) deviceID;
@end

/**
 * @type api
 * @region 视频设备管理
 * @brief 主要用于枚举、设置视频采集设备
 */
BYTE_RTC_EXPORT @interface ByteRtcVideoDeviceManager : NSObject

/**
 * @type api
 * @region 视频设备管理
 * @brief 获取当前系统视频设备列表
 * @return 一个包含系统中所有视频设备列表的对象，详见 ByteRtcVideoDeviceCollection{@link #ByteRtcVideoDeviceCollection}
 * @notes 该方法返回一个ByteRtcVideoDeviceCollection{@link #ByteRtcVideoDeviceCollection}对象，可以通过该对象枚举系统中视频设备
 */
- (ByteRtcVideoDeviceCollection * _Nonnull)enumerateVideoDevices;

/**
 * @type api
 * @region 视频设备管理
 * @brief 获取当前SDK正在使用的设备信息
 * @param deviceID
 *       视频设备ID
 * @return
 *      0：方法调用成功
 *      !0：方法调用失败
 */
- (int)getDevice:(NSString * _Nonnull * _Nonnull) deviceID;

/**
 * @type api
 * @region 视频设备管理
 * @brief 设置当前视频采集设备
 * @param  deviceID
 *       视频设备ID，从getDevice{@link #ByteRtcVideoDeviceCollection#getDevice}获得的有效ID
 * @return
 *      0：成功
 *      !0：失败
 * @notes 必须保证调用该函数前该视频摄像头没有被其他应以程序占用或者损坏
 */
- (int)setDevice:(NSString* _Nonnull)deviceID;
@end

/**
 * @type api
 * @brief 音频设备集合类
 *      主要用于系统音频设备播放与采集设备管理
 */
BYTE_RTC_EXPORT @interface ByteRtcAudioDeviceCollection : NSObject
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频设备的数量
 * @return 返回当前系统的设备数量
 * @notes 当本集合是播放设备集合时返回播放设备数量，当是音频采集设备集合时返回音频采集设备数量
 */
- (int)getCount;
/**
 * @type api
 * @region 音频设备管理
 * @brief 返回当前系统音频设备信息
 * @param index
 *       系统设备索引
 * @param deviceName
 *       音频设备名称
 * @param deviceID
 *       音频设备 id
 * @return
 *      0：成功
 *      <0：失败
 * @notes  当本集合是播放设备集合时返回播放设备信息，当是音频采集设备集合时返回音频采集设备信息
 */
- (int)getDevice:(int)index DeviceName:(NSString * _Nonnull * _Nonnull)deviceName DeviceID:(NSString * _Nonnull * _Nonnull) deviceID;
@end

/**
 * @hidden
 * @type callback
 */
BYTE_RTC_EXPORT @protocol ByteAudioDeviceEventHandler<NSObject>
/**
 * @hidden
 * @type callback
 */
- (void)onRecordingAudioVolumeIndication:(int)volume;
/**
 * @hidden
 * @type callback
 */
- (void)onLoopbackAudioVolumeIndication:(int)volume;
@end

/**
 * @type api
 * @brief 音频设备管理类
 */
BYTE_RTC_EXPORT @interface ByteRtcAudioDeviceManager : NSObject
/**
 * @type api
 * @region 音频设备管理
 * @brief 创建播放设备集合
 * @return 返回音频播放集合，详见，{@link #ByteRtcAudioDeviceCollection}
 */
- (ByteRtcAudioDeviceCollection * _Nonnull)enumeratePlaybackDevices;
/**
 * @type api
 * @region 音频设备管理
 * @brief 创建音频采集设备集合
 * @return 返回音频采集集合，详见，{@link #ByteRtcAudioDeviceCollection}
 * @notes 如果没有音频采集设备操作权限，设备集合列表中仍然会有所有音频采集设备
 */
- (ByteRtcAudioDeviceCollection * _Nonnull)enumerateRecordingDevices;

/**
 * @type api
 * @region 音频设备管理
 * @brief 设置音频播放设备
 * @param deviceID
 *       音频播放设备 id, 可通过 {@link #EnumeratePlaybackDevices} 获取。插拔设备不会影响 deviceID
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)setPlaybackDevice:(NSString * _Nonnull)deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频播放设备 id
 * @param deviceID
 *       音频设备 id
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)getPlaybackDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频播放设备信息
 * @param deviceName
 *       音频设备名称
 * @param deviceID
 *       音频设备 id
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)getPlaybackDeviceInfo:(NSString * _Nonnull * _Nonnull)deviceName DeviceID:(NSString * _Nonnull * _Nonnull) deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @brief 设置音频采集设备
 * @param deviceID
 *       音频采集设备 id, 可通过 {@link #EnumeratePlaybackDevices} 获取。插拔设备不会影响 deviceID
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)setRecordingDevice:(NSString * _Nonnull)deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频采集设备 id
 * @param deviceID
 *       音频设备 id,
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)getRecordingDevice:(NSString *_Nonnull * _Nonnull) deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频采集设备信息
 * @param deviceName
 *       音频设备名称
 * @param deviceID
 *       音频设备 id
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)getRecordingDeviceInfo:(NSString *_Nonnull * _Nonnull)deviceName DeviceID:(NSString * _Nonnull * _Nonnull) deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @brief 设置音频播放设备静音信息
 * @param mute
 *       true：设备静音
 *      false：取消设备静音
 * @return
 *      0：成功
 *      <0：失败
 */
- (int) setPlaybackDeviceMute:(bool)mute;
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取音频播放设备静音信息
 * @param mute
 *       true：设备静音
 *      false：设备非静音
 * @return
 *      0：成功
 *      <0：失败
 */
- (int) getPlaybackDeviceMute:(bool * _Nonnull)mute;
/**
 * @type api
 * @region 音频设备管理
 * @brief 设置音频采集设备静音信息
 * @param mute
 *       true：设备静音
 *      false：取消设备静音
 * @return
 *      0：成功
 *      <0：失败
 */
- (int) setRecordingDeviceMute:(bool)mute;
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取音频采集设备静音信息
 * @param mute
 *       true：设备静音
 *      false：设备非静音
 * @return
 *      0：成功
 *      <0：失败
 */
- (int) getRecordingDeviceMute:(bool * _Nonnull)mute;
/**
 * @type api
 * @region 音频设备管理
 * @brief 设置音频播放设备音量
 * @param volume
 *       音频播放设备音量, 取值范围 [0,255], 超出此范围返回错误 -2
 * @return
 *      0：成功
 *      <0：失败
 */
- (int) setPlaybackDeviceVolume:(unsigned int)volume;
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取音频播放设备音量
 * @param volume
 *       音频播放设备音量, 取值范围 [0,255]
 * @return
 *      0：成功
 *      <0：失败
 */
- (int) getPlaybackDeviceVolume:(unsigned int * _Nonnull)volume;
/**
 * @type api
 * @region 音频设备管理
 * @brief 设置音频采集设备音量
 * @param volume
 *       音频采集设备音量, 取值范围 [0,255], 超出此范围返回错误 -2
 * @return
 *      0：成功
 *      <0：失败
 */
- (int) setRecordingDeviceVolume:(unsigned int)volume;
/**
 * @type api
 * @region 音频设备管理
 * @brief 获取音频采集设备音量
 * @param volume
 *       音频采集设备音量, 取值范围 [0,255]
 * @return
 *      0：成功
 *      <0：失败
 */
- (int) getRecordingDeviceVolume:(unsigned int * _Nonnull)volume;

/**
 * @type api
 * @region 音频设备管理
 * @brief 启动播放设备测试
 *       该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作
 * @param testAudioFilePath
 *       指定音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav
 * @return
 *      0：成功
 *      <0：失败
 * @notes: 测试功能必须在 {@link #ByteRtcEngineKit#joinChannelByKey} 前应用。且不可与其它音频设备测试功能同时应用。
 */
- (int)startPlaybackDeviceTest:(NSString *_Nonnull)testAudioFilePath;
/**
 * @type api
 * @region 音频设备管理
 * @brief 停止播放设备测试。
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)stopPlaybackDeviceTest;
/**
 * @type api
 * @region 音频设备管理
 * @brief 启动录音设备测试。
 *       该方法测试录音设备是否能正常工作。启动测试后，SDK 通过 {@link #ByteRtcEngineDelegate#reportAudioVolumeIndicationOfSpeakers} 回调方法向应用上报音量信息
 * @param indicationInterval
 *       回调的周期（毫秒）
 * @return
 *      0:成功
 *      <0：失败
 * @notes: 测试功能必须在 {@link #ByteRtcEngineKit#joinChannelByKey} 前应用。且不可与其它音频设备测试功能同时应用。
 */
- (int)startAudioRecordingDeviceTest:(unsigned int)indicationInterval;
/**
 * @type api
 * @region 音频设备管理
 * @brief 停止录音设备测试。
 *       该方法停止录音设备测试。调用 {@link #startAudioRecordingDeviceTest} 后，必须调用该方法停止测试。
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)stopAudioRecordingDeviceTest;
/**
 * @type api
 * @region 音频设备管理
 * @brief 开始音频设备回路测试。
 *       该方法测试麦克风和播放设备是否能正常工作。一旦测试开始，麦克风会采集本地讲话声音
 *       然后使用扬声器播放出来，同时 SDK 会通过 {@link #ByteRtcEngineDelegate#reportAudioVolumeIndicationOfSpeakers} 回调向应用程序上报音量信息。
 * @param indicationInterval
 *       SDK 返回 {@link #ByteRtcEngineDelegate#reportAudioVolumeIndicationOfSpeakers} 回调的时间间隔，单位为毫秒
 *       建议设置到大于 200 毫秒。最小不得少于 10 毫秒。
 * @return
 *      0：成功
 *      <0：失败
 * @notes:
 *      1.测试功能必须在 {@link #ByteRtcEngineKit#joinChannelByKey} 前应用。且不可与其它音频设备测试功能同时应用。
 *      2.该方法仅在本地进行音频设备测试，不涉及网络连接。
 */
- (int)startAudioDeviceLoopbackTest:(unsigned int)indicationInterval;
/**
 * @type api
 * @region 音频设备管理
 * @brief 停止音频设备回路测试。
 *       该方法停止录音设备测试。调用 {@link #startAudioDeviceLoopbackTest} 后，必须调用该方法停止测试。
 * @return
 *      0：成功
 *      <0：失败
 */
- (int)stopAudioDeviceLoopbackTest;
@end

/**
 *  @hidden
 *  @type api
 *  @brief 视频帧回调函数
*/
BYTE_RTC_EXPORT @protocol ByteRtcVideoFrameObserver<NSObject>
@optional
//When uid == "" means it is local frame
/**
 *  @type callback
 *  @region 视频管理
 *  @brief 视频帧回调。
 *  @param frame 视频数据帧，详见类型ByteRtcVideoFrameData{@link #ByteRtcVideoFrameData}
 *  @param uid 用户id
 *  @return YES：方法调用成功；
            NO： 方法调用失败
*/
- (bool)OnVideoFrame:(ByteRtcVideoFrameData * _Null_unspecified) frame Uid:(NSString * _Nonnull)uid;
/**
 *  @type callback
 *  @region 视频管理
 *  @brief 屏幕共享帧回调。
 *  @param frame 视频数据帧，详见类型 ByteRtcVideoFrameData{@link #ByteRtcVideoFrameData}
 *  @param uid 用户 id，当该参数是空字符串时表示是本地屏幕共享数据
 *  @return YES：方法调用成功；
 *           NO：方法调用失败；
 */
- (bool)OnScreenFrame:(ByteRtcVideoFrameData * _Null_unspecified) frame Uid:(NSString * _Nonnull)uid;
@end

/**
 * @hidden
 * @type api
 * @brief 音频帧回调函数
*/
BYTE_RTC_EXPORT @protocol ByteRtcAudioFrameObserver<NSObject>

/**
 * @hidden
 * @type callback
 * @region 音频数据回调
 * @brief 返回麦克风录制的音频数据
 * @param frame，麦克风录制的音频数据, 详见：ByteRtcAudioFrameData{@link #ByteRtcAudioFrameData}
 * @return YES：方法调用成功；
           NO： 方法调用失败
 */
- (bool)OnMixPlaybackAudioFrame:(ByteRtcAudioFrameData * _Null_unspecified) frame;

/**
 * @hidden
 * @type callback
 * @region 音频管理
 * @brief 用户uid音频帧回调。
 * @param frame 音频数据帧，详见类型ByteRtcAudioFrameData{@link #ByteRtcAudioFrameData}
 * @param uid 用户id
 * @return YES：方法调用成功；
           NO： 方法调用失败
*/
- (bool)OnAudioFrame:(ByteRtcAudioFrameData * _Null_unspecified) frame Uid:(NSString * _Nonnull)uid;
@end

/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 音频外部设备事件监听，只用于自定义音频采集渲染的情况
 *      SDK内部需要控制外部设备时，通过这个事件监听类通知上层应用
 */
BYTE_RTC_EXPORT @protocol AudioDeviceObserver<NSObject>
@optional
/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 通知上层应用开启音频采集设备
 */
- (void)OnAudioDeviceRecordStart;
/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 通知上层应用关闭音频采集设备
 */
- (void)OnAudioDeviceRecordStop;
/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 通知上层应用开启音频播放设备
 */
- (void)OnAudioDevicePalyoutStart;
/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 通知上层应用关闭音频播放设备
 */
- (void)OnAudioDevicePlayoutStop;
@end

/**
 *  @type api
 */
@interface ByteRtcEngineKit()
/**
 *  @hidden
 *  @type api
 *  @region 网络连接
 *  @brief 设置 SDK 当前使用的环境。
 *  @param env SDK使用的环境参数，详见：ByteRtcEnv{@link #ByteRtcEnv}。
 *  @return
 *        0： 设置成功
 *        -1：设置失败
 *  @notes
 *        1.本函数是可选函数，默认使用正式环境；
 *        2.本函数必须在创建 RtcEngine 实例 sharedEngineWithAppId{@link #sharedEngineWithAppId} 前调用。
 */

+ (int)setEnv:(ByteRtcEnv)env;

/**
 *  @type api
 *  @region 频道管理
 *  @brief 设置Json格式的字符串参数，配置RTC引擎参数。
 *  @param parameters Json格式的字符串参数
 *  @return 0：方法调用成功；
            <0： 方法调用失败
 *  @notes 需要在引擎初始化之前调用
 */
+ (int)setParameters:(NSString* _Nullable)parameters;

/**
 * @type api
 * @region 视频管理
 * @brief 设备视频管理接口创建
 * @return 视频设备管理接口，详见：{@link #ByteRtcVideoDeviceManager}
 */
- (ByteRtcVideoDeviceManager * _Null_unspecified)getVideoDeviceManager;

/**
 * @type api
 * @region 音频管理
 * @brief 设备音频管理接口创建
 * @return 音频设备管理接口，详见：{@link #ByteRtcAudioDeviceManager}
 */
- (ByteRtcAudioDeviceManager * _Null_unspecified)getAudioDeviceManager;

/**
 * @type api
 * @region 音频数据回调
 * @brief 注册音频数据回调观察者
 * @param observer 音频数据观察者，详见：ByteRtcAudioFrameObserver{@link #ByteRtcAudioFrameObserver}
 */
- (void)registerAudioFrameObserver:(id<ByteRtcAudioFrameObserver> _Nonnull)observer;

/**
 * @type api
 * @region 视频管理
 * @brief 注册回调视频数据
 * @param [in] observer 数据回调函数，详见：{@link #ByteRtcVideoFrameObserver}
 * @notes 设置引擎服务地址，必须在joinChannel前调用
 */
- (void)registerVideoFrameObserver:(id<ByteRtcVideoFrameObserver> _Nonnull)observer;

/**
 * @type api
 * @region 视频管理
 * @brief 设置外部视频输入源
 * @param enable 是否使用外部视频输入源
 *        true: 采用外部输入源
 *        false: 不采用外部输入源
 * @notes 该方法应该在startpreview和joinChannel之前调用
 */
- (void)setExternalVideoSource:(bool)enable;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 推送外部视频帧。
 *  @param frame 该视频帧包含待自研SDK编码的视频数据
 *  @return YES 设置成功
 *           NO 设置失败
 *  @note 调用 pushExternalVideoFrame 推送视频帧前，需要使用 setExternalVideoSource 开启视频外部源功能。
 *        详见 setExternalVideoSource@link #setExternalVideoSource}
 */
- (bool)pushExternalVideoFrame:(ByteRtcVideoFrameData * _Nonnull)frame;

/**
 *  @hidden
 *  @type api
 *  @region 视频管理
 *  @brief 推送外部视频帧。
 *  @param buffer 视频数据
 *  @param type 视频帧类型
 *  @param width 视频帧宽度
 *  @param height 视频帧高度
 *  @param rotation 视频帧旋转角度
 *  @param timestampMs 视频帧时间戳，单位是毫秒
 *  @return YES 成功
 *           NO 失败
 *  @note 调用 pushExternalVideoFrame 推送视频帧前，需要使用 setExternalVideoSource 开启视频外部源功能。
 *        详见 setExternalVideoSource@link #setExternalVideoSource}
 */
- (bool)pushExternalVideoFrame:(UInt8 * _Nonnull)buffer type:(ByteRtcVideoFrameType)type width:(int)width height:(int)height rotation:(int)rotation timestampMs:(SInt64)timestampMs;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @brief 设置是否启用外部音频采集渲染
 * @param enable
 *        YES: 启用自定义音频采集渲染
 *        NO: 不启用自定义音频采集渲染
 * @param SampleRate
 *        音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
 * @param RecordChannels，外部音频采集通道数，支持单声道和双声道
 *        1：单声道
 *        2：双声道
 * @param PlayoutChannels，外部音频渲染通道数，支持单通道和双通道
 *        1：单声道
 *        2：双声道
 * @note 该方法应该在 joinChannelByKey{@link #ByteRtcEngineKit#joinChannelByKey} 前使用
 */
- (void)setExternalAudioSource:(bool)enable SampleRate:(int)rate RecordChannels:(unsigned int)recordChannels PlayoutChannels:(unsigned int)playoutChannels;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @brief 启动音频外部源采集渲染时，添加音频外部设备事件监控
 * @param observer
 *        音频设备事件监控，详见：AudioDeviceObserver{@link #AudioDeviceObserver}
 */
- (void)setAudioDeviceObserver:(id<AudioDeviceObserver> _Nonnull) observer;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @brief 推送外部音频数据
 * @param buffer
 *        pcm 数据
 * @param samples
 *        采样点数量，应该为 setExternalAudioSource{@link #setExternalAudioSource} 中设置的 SampleRate / 100。
 *        当设置采样率为48000时， 每次应该推送480个采样点
 * @return YES: 推送成功
 *         NO: 推送失败
 * @notes
 *  1.必须是pcm数据，推送间隔是10ms
 *  2.该函数运行在用户调用线程内
 */
- (bool)pushExternalAudioFrame:(SInt8 * _Nonnull) buffer Samples:(int) samples;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @brief 拉取远端音频数据
 * @param buffer
 *        pcm 数据
 * @param samples
 *        采样点数量，应该为 setExternalAudioSource{@link #setExternalAudioSource} 中设置的 SampleRate / 100。
 *        当设置采样率为48000时， 每次应该推送480个采样点
 * @return YES: 拉取成功
 *         NO: 拉取失败
 * @notes
 *  1.必须是pcm数据，拉取间隔是10ms
 *  2.该函数运行在用户调用线程内
 */
- (bool)pullExternalAudioFrame:(SInt8 * _Nonnull) buffer Samples:(int) samples;

/**
 * @hidden
 * @type api
 */
+ (ByteRtcAudioDeviceManager *_Null_unspecified)createAudioDeviceManager:(id<ByteAudioDeviceEventHandler> _Nonnull)handler;
@end
#endif /* ByteRtcEngineKitInternal_h */
