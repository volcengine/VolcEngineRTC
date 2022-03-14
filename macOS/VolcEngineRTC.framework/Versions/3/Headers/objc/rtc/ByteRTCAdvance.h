/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Advance API
*/

#import "ByteRTCEngineKit.h"

/**
 * @type api
 * @author wangjunzheng
 * @brief 设备集合类
 *      主要用于系统设备播放与采集设备管理
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCDeviceCollection : NSObject
/**
 * @type api
 * @region 引擎管理
 * @author wangjunzheng
 * @brief 获取当前设备的数量
 * @return 返回当前系统的设备数量
 */
- (int)getCount;
/**
 * @type api
 * @region 引擎管理
 * @author wangjunzheng
 * @brief 返回当前系统设备信息
 * @param index
 *       系统设备索引
 * @param deviceName
 *       设备名称
 * @param deviceID
 *       设备 id
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int)getDevice:(int)index DeviceName:(NSString * _Nonnull * _Nonnull)deviceName DeviceID:(NSString * _Nonnull * _Nonnull) deviceID;
@end

/**
 * @type api
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 主要用于枚举、设置视频采集设备
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoDeviceManager : NSObject

/**
 * @type api
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 获取当前系统视频设备列表
 * @return 一个包含系统中所有视频设备列表的对象，详见 ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}
 * @notes 该方法返回一个 ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}对象，可以通过该对象枚举系统中视频设备
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateVideoCaptureDevices;

/**
 * @type api
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 获取当前SDK正在使用的设备信息
 * @param deviceID
 *       视频设备ID
 * @return
 *      0：方法调用成功
 *      !0：方法调用失败
 */
- (int)GetVideoCaptureDevice:(NSString * _Nonnull * _Nonnull) deviceID;

/**
 * @type api
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 设置当前视频采集设备
 * @param  deviceID
 *       视频设备ID，从GetVideoCaptureDevice{@link #ByteRTCDeviceCollection#GetVideoCaptureDevice}获得的有效ID
 * @return
 *      0：成功
 *      !0：失败
 * @notes 必须保证调用该函数前该视频摄像头没有被其他应以程序占用或者损坏
 */
- (int)setVideoCaptureDevice:(NSString* _Nonnull)deviceID;
@end

/**
 * @hidden
 * @type callback
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCAudioDeviceEventHandler<NSObject>
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
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioDeviceManager : NSObject
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 创建播放设备集合
 * @return 返回音频播放集合，详见，{@link #ByteRTCDeviceCollection}
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateAudioPlaybackDevices;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 创建音频采集设备集合
 * @return 返回音频采集集合，详见，{@link #ByteRTCDeviceCollection}
 * @notes 如果没有音频采集设备操作权限，设备集合列表中仍然会有所有音频采集设备
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateAudioCaptureDevices;

/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 设置音频播放设备
 * @param deviceID
 *       音频播放设备 id, 可通过 {@link #enumerateAudioPlaybackDevices} 获取。插拔设备不会影响 deviceID
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int)setAudioPlaybackDevice:(NSString * _Nonnull)deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 获取当前音频播放设备 id
 * @param deviceID
 *       音频设备 id
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int)getAudioPlaybackDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 设置音频采集设备
 * @param deviceID
 *       音频采集设备 id, 可通过 {@link #enumerateAudioCaptureDevices} 获取。插拔设备不会影响 deviceID
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int)setAudioCaptureDevice:(NSString * _Nonnull)deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 获取当前音频采集设备 id
 * @param deviceID
 *       音频设备 id,
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int)getAudioCaptureDevice:(NSString *_Nonnull * _Nonnull) deviceID;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 设置音频播放设备静音信息
 * @param mute
 *       true：设备静音
 *      false：取消设备静音
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int) setAudioPlaybackDeviceMute:(bool)mute;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 获取音频播放设备静音信息
 * @param mute
 *       true：设备静音
 *      false：设备非静音
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int) getAudioPlaybackDeviceMute:(bool * _Nonnull)mute;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 设置音频采集设备静音信息
 * @param mute
 *       true：设备静音
 *      false：取消设备静音
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int) setAudioCaptureDeviceMute:(bool)mute;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 获取音频采集设备静音信息
 * @param mute
 *       true：设备静音
 *      false：设备非静音
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int) getAudioCaptureDeviceMute:(bool * _Nonnull)mute;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 设置音频播放设备音量
 * @param volume
 *       音频播放设备音量, 取值范围 [0,255], 超出此范围返回错误 -2
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int) setAudioPlaybackDeviceVolume:(unsigned int)volume;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 获取音频播放设备音量
 * @param volume
 *       音频播放设备音量, 取值范围 [0,255]
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int) getAudioPlaybackDeviceVolume:(unsigned int * _Nonnull)volume;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 设置音频采集设备音量
 * @param volume
 *       音频采集设备音量, 取值范围 [0,255], 超出此范围返回错误 -2
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int) setAudioCaptureDeviceVolume:(unsigned int)volume;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 获取音频采集设备音量
 * @param volume
 *       音频采集设备音量, 取值范围 [0,255]
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int) getAudioCaptureDeviceVolume:(unsigned int * _Nonnull)volume;

/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 启动播放设备测试
 *       该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作
 * @param testAudioFilePath
 *       指定音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav
 * @return
 *      0：成功
 *      < 0：失败
 * @notes: 测试功能必须在 {@link #ByteRTCEngineKit#joinChannelByKey} 前应用。且不可与其它音频设备测试功能同时应用。
 */
- (int)startAudioPlaybackDeviceTest:(NSString *_Nonnull)testAudioFilePath;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 停止播放设备测试。
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int)stopAudioPlaybackDeviceTest;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 启动录音设备测试。
 *       该方法测试录音设备是否能正常工作。启动测试后，SDK 通过 {@link #ByteRTCEngineDelegate#reportAudioVolumeIndicationOfSpeakers} 回调方法向应用上报音量信息
 * @param indicationInterval
 *       回调的周期（毫秒）
 * @return
 *      0:成功
 *      < 0：失败
 * @notes: 测试功能必须在 {@link #ByteRTCEngineKit#joinChannelByKey} 前应用。且不可与其它音频设备测试功能同时应用。
 */
- (int)startAudioCaptureDeviceTest:(unsigned int)indicationInterval;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 停止录音设备测试。
 *       该方法停止录音设备测试。调用 {@link #startAudioCaptureDeviceTest} 后，必须调用该方法停止测试。
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int)stopAudioCaptureDeviceTest;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 开始音频设备回路测试。
 *       该方法测试麦克风和播放设备是否能正常工作。一旦测试开始，麦克风会采集本地讲话声音
 *       然后使用扬声器播放出来，同时 SDK 会通过 {@link #ByteRTCEngineDelegate#reportAudioVolumeIndicationOfSpeakers} 回调向应用程序上报音量信息。
 * @param indicationInterval
 *       SDK 返回 {@link #ByteRTCEngineDelegate#reportAudioVolumeIndicationOfSpeakers} 回调的时间间隔，单位为毫秒
 *       建议设置到大于 200 毫秒。最小不得少于 10 毫秒。
 * @return
 *      0：成功
 *      < 0：失败
 * @notes:
 *      1.测试功能必须在 {@link #ByteRTCEngineKit#joinChannelByKey} 前应用。且不可与其它音频设备测试功能同时应用。
 *      2.该方法仅在本地进行音频设备测试，不涉及网络连接。
 */
- (int)startAudioDeviceLoopbackTest:(unsigned int)indicationInterval;
/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 停止音频设备回路测试。
 *       该方法停止录音设备测试。调用 {@link #startAudioDeviceLoopbackTest} 后，必须调用该方法停止测试。
 * @return
 *      0：成功
 *      < 0：失败
 */
- (int)stopAudioDeviceLoopbackTest;
@end

/**
 * @hidden
 * @type api
 * @brief 视频帧回调函数
*/
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoFrameObserver<NSObject>
@optional
//When uid == "" means it is local frame
/**
 * @type callback
 * @region 视频管理
 * @brief 视频帧回调。
 * @param frame 视频数据帧，详见类型 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid 用户id
 * @return YES：方法调用成功；
            NO： 方法调用失败
*/
- (bool)OnVideoFrame:(ByteRTCVideoFrame * _Null_unspecified) frame Uid:(NSString * _Nonnull)uid;
/**
 * @type callback
 * @region 视频管理
 * @brief 屏幕共享帧回调。
 * @param frame 视频数据帧，详见类型 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid 用户 id，当该参数是空字符串时表示是本地屏幕共享数据
 * @return YES：方法调用成功；
 *           NO：方法调用失败；
 */
- (bool)OnScreenFrame:(ByteRTCVideoFrame * _Null_unspecified) frame Uid:(NSString * _Nonnull)uid;

- (bool)OnMergeFrame:(ByteRTCVideoFrame * _Null_unspecified) frame Uid:(NSString * _Nonnull)uid;
@end

/**
 * @hidden
 * @type api
 * @brief 压缩视频帧回调函数
*/
BYTERTC_APPLE_EXPORT @protocol ByteRTCLocalEncodedVideoFrameObserver<NSObject>
@optional
/**
 * @type callback
 * @region 视频管理
 * @brief 压缩视频帧回调。
 * @param streamIndex 流类型
 * @param frame 压缩视频数据帧，详见类型 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 * @return YES：方法调用成功；
            NO： 方法调用失败
*/
- (bool)OnLocalEncodedVideoFrame:(ByteRTCStreamIndex) streamIndex Frame:(ByteRTCEncodedVideoFrame * _Null_unspecified)frame;
@end

/**
 * @hidden
 * @type api
 * @brief 音频帧回调函数
*/
BYTERTC_APPLE_EXPORT @protocol ByteRTCAudioFrameObserver<NSObject>

/**
 * @hidden
 * @type callback
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 返回麦克风录制的音频数据
 * @param frame，麦克风录制的音频数据, 详见： ByteRTCAudioFrameData{@link #ByteRTCAudioFrameData}
 * @return YES：方法调用成功；
           NO： 方法调用失败
 */
- (bool)OnMixPlaybackAudioFrame:(ByteRTCAudioFrameData * _Null_unspecified) frame;

/**
 * @hidden
 * @type callback
 * @region 音频管理
 * @author wangjunzheng
 * @brief 用户uid音频帧回调。
 * @param frame 音频数据帧，详见类型 ByteRTCAudioFrameData{@link #ByteRTCAudioFrameData}
 * @param uid 用户id
 * @return YES：方法调用成功；
           NO： 方法调用失败
*/
- (bool)OnAudioFrame:(ByteRTCAudioFrameData * _Null_unspecified) frame Uid:(NSString * _Nonnull)uid;
@end

/**
 * @type api
 */
@interface ByteRTCEngineKit()
/**
 * @hidden
 * @deprecated
 * @type api
 * @region 网络连接
 * @brief 设置 SDK 当前使用的环境。
 * @param env SDK使用的环境参数，详见：Env{@link #Env}。
 * @return
 *        0： 设置成功
 *        -1：设置失败
 * @notes
 *        1.本函数是可选函数，默认使用正式环境；
 *        2.本函数必须在创建 RtcEngine 实例 sharedEngineWithAppId{@link #sharedEngineWithAppId} 前调用。
 */

+ (int)setEnv:(ByteRTCEnv)env __attribute((deprecated("Will be removed in new version")));

/**
 * @hidden
 * @type api
 * @deprecated
 * @region 频道管理
 * @brief 设置Json格式的字符串参数，配置RTC引擎参数。
 * @param parameters Json格式的字符串参数
 * @return 0：方法调用成功；
            < 0： 方法调用失败
 * @notes 需要在引擎初始化之前调用
 */
+ (int)setParameters:(NSString* _Nullable)parameters __attribute((deprecated("Will be removed in new version")));

/**
 * @type api
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 设备视频管理接口创建
 * @return 视频设备管理接口，详见：{@link #ByteRTCVideoDeviceManager}
 */
- (ByteRTCVideoDeviceManager * _Null_unspecified)getVideoDeviceManager;

/**
 * @type api
 * @region 音频设备管理
 * @author wangjunzheng
 * @brief 设备音频管理接口创建
 * @return 音频设备管理接口，详见：{@link #ByteRTCAudioDeviceManager}
 */
- (ByteRTCAudioDeviceManager * _Null_unspecified)getAudioDeviceManager;

/**
 * @type api
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 注册音频数据回调观察者
 * @param observer 音频数据观察者，详见： ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}
 */
- (void)registerAudioFrameObserver:(id<ByteRTCAudioFrameObserver> _Nonnull)observer;

/**
 * @type api
 * @region 视频管理
 * @brief 注册回调视频数据
 * @param observer 数据回调函数，详见：{@link #ByteRTCVideoFrameObserver}
 * @notes 设置引擎服务地址，必须在joinChannel前调用
 */
- (void)registerVideoFrameObserver:(id<ByteRTCVideoFrameObserver> _Nonnull)observer;

/**
 * @type api
 * @region 视频管理
 * @brief 注册回调压缩视频数据
 * @param observer 数据回调函数，详见：{@link #ByteRTCLocalEncodedVideoFrameObserver}
 */
- (void)registerLocalEncodedVideoFrameObserver:(id<ByteRTCLocalEncodedVideoFrameObserver> _Nonnull)observer;

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
 * @type api
 * @region 视频管理
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待自研SDK编码的视频数据
 * @return YES 设置成功
 *           NO 设置失败
 * @note 调用 pushExternalVideoFrame 推送视频帧前，需要使用 setExternalVideoSource 开启视频外部源功能。
 *        详见 setExternalVideoSource@link #setExternalVideoSource}
 */
- (bool)pushExternalVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

/**
 * @hidden
 * @type api
 * @region 视频管理
 * @brief 推送外部视频帧。
 * @param buffer 视频数据
 * @param type 视频帧类型
 * @param width 视频帧宽度
 * @param height 视频帧高度
 * @param rotation 视频帧旋转角度
 * @param timestampMs 视频帧时间戳，单位是毫秒
 * @return YES 成功
 *           NO 失败
 * @note 调用 pushExternalVideoFrame 推送视频帧前，需要使用 setExternalVideoSource 开启视频外部源功能。
 *        详见 setExternalVideoSource@link #setExternalVideoSource}
 */
- (bool)pushExternalVideoFrame:(UInt8 * _Nonnull)buffer type:(ByteRTCVideoFrameType)type width:(int)width height:(int)height rotation:(int)rotation timestampMs:(SInt64)timestampMs;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @author dixing
 * @brief 启用外部音频采集渲染。
 * @param recordingFormat 外部音频采集数据格式，详见 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}
 * @param playoutChannelNum 外部音频渲染数据格式，详见 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}
 * @notes  <br>
 *      + 该方法应该在 joinChannelByKey{@link #ByteRTCEngineKit#joinChannelByKey} 前使用。  <br>
 *      + 启用自定义音频采集渲染后，使用 pushExternalAudioFrame:{@link #pushExternalAudioFrame:} 推送音频数据。  <br>
 *      + 启用自定义音频采集渲染后，使用 pullExternalAudioFrame:{@link #pullExternalAudioFrame:} 拉取音频数据。  <br>
 */

- (void)enableExternalAudioDevice:(ByteRTCAudioFormat * _Nonnull) recordingFormat playbackFormat:(ByteRTCAudioFormat * _Nonnull) playbackFormat;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @author dixing
 * @brief 禁用外部音频采集渲染。
 * @notes  <br>
 *      + 该方法应该在 joinChannelByKey{@link #ByteRTCEngineKit#joinChannelByKey} 前使用。  <br>
 *      + 启用自定义音频采集请使用 enableExternalAudioDevice:{@link #enableExternalAudioDevice:}。  <br>
 */
- (void)disableExternalAudioDevice;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @author dixing
 * @brief 推送外部音频数据。使用
 *        enableExternalAudioDevice:playbackFormat:{@link #enableExternalAudioDevice:playbackFormat:}
 *        启用自定义音频采集渲染后，可以使用本方法推送外部音频数据。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + < 0: 调用失败  <br>
 * @notes  <br>
 *       + audioFrame 的 buffer 必须是pcm数据，内存大小应该为 recordFormat.samples * recordFormat.channel * 2， 推送间隔是10ms，音频采样格式为s16。  <br>
 *       + audioFrame 的 samples 表示采样点数量，应该为 enableExternalAudioDevice:playbackFormat:{@link #enableExternalAudioDevice:playbackFormat:} 中设置的 recordFormat.sampleRate / 100。
 *        当设置采样率为48000时， 每次应该推送480个采样点
 *       + 该函数运行在用户调用线程内
 */
- (int)pushExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @author dixing
 * @brief 拉取远端音频数据。使用
 *        enableExternalAudioDevice:playbackFormat:{@link #enableExternalAudioDevice:playbackFormat:}
 *        启用自定义音频采集渲染后，可以使用本方法拉取外部音频数据。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + < 0: 调用失败  <br>
 * @notes  <br>
 *       + audioFrame 的 buffer 是pcm数据，内存大小为 playbackFormat.samples * playbackFormat.channel * 2， 拉取间隔是10ms，音频采样格式为s16。  <br>
 *       + audioFrame 的 samples 表示采样点数量，应该为 enableExternalAudioDevice:playbackFormat:{@link #enableExternalAudioDevice:playbackFormat:} 中设置的 playbackFormat.sampleRate / 100。
 *        当设置采样率为48000时， 每次应该推送480个采样点
 *       + 该函数运行在用户调用线程内
 */
- (int)pullExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;

/**
 * @hidden
 * @type api
 */
- (ByteRTCAudioDeviceManager *_Null_unspecified)createAudioDeviceManager:(id<ByteRTCAudioDeviceEventHandler> _Nonnull)handler;
@end
