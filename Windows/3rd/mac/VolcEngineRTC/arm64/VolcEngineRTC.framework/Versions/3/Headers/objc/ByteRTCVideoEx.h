#import "ByteRTCVideo.h"
#import "rtc/ByteRTCVideoDefinesEx.h"

@class ByteRTCVideoEx;
@class ByteRTCRoomEx;

/**
 * @locale zh
 * @type callback
 * @brief ByteRTCVideoDelegateEx Class<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
@protocol ByteRTCVideoDelegateEx <NSObject>
@optional
/**
 * @locale zh
 * @type callback
 * @brief 本地音频首帧发送状态发生改变时，收到此回调。
 * @param streamKey 参看 ByteRTCStreamKey{@link #ByteRTCStreamKey}。
 * @param metaData 发送 ID
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onAudioFrameSendStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                            metaData:(NSString* _Nonnull)metaData
                               state:(ByteRTCFirstFrameSendState)state;
/**
 * @locale zh
 * @type callback
 * @brief 本地视频首帧发送状态发生改变时，收到此回调。
 * @param streamKey 参看 ByteRTCStreamKey{@link #ByteRTCStreamKey}。
 * @param metaData 发送 ID
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onVideoFrameSendStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                            metaData:(NSString* _Nonnull)metaData
                               state:(ByteRTCFirstFrameSendState)state;
/**
 * @locale zh
 * @type callback
 * @brief 音频首帧播放状态发生改变时，收到此回调。
 * @param streamKey 参看 ByteRTCStreamKey{@link #ByteRTCStreamKey}。
 * @param metaData 发送 ID
 * @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onAudioFramePlayStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                            metaData:(NSString* _Nonnull)metaData
                               state:(ByteRTCFirstFramePlayState)state;
/**
 * @locale zh
 * @type callback
 * @brief 视频首帧播放状态发生改变时，收到此回调。
 * @param streamKey 参看 ByteRTCStreamKey{@link #ByteRTCStreamKey}。
 * @param metaData 发送 ID
 * @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onVideoFramePlayStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                            metaData:(NSString* _Nonnull)metaData
                               state:(ByteRTCFirstFramePlayState)state;
/**
 * @locale zh
 * @type callback
 * @region 数据统计
 * @brief 反映通话中本地设备发送音/视频流的统计信息以及网络状况的回调，每 2s 触发一次。
 * @param streamIndex 流索引，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param stats 详见 ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onLocalStreamStats:(ByteRTCStreamIndex)streamIndex
                     stats:(ByteRTCLocalStreamStats* _Nonnull)stats;
/**
 * @locale zh
 * @type callback
 * @region 数据统计
 * @brief 通话中本地设备接收订阅的远端音/视频流的统计信息以及网络状况，每 2s 触发一次。
 * @param streamKey 参看 ByteRTCStreamKey{@link #ByteRTCStreamKey}。
 * @param stats 当前 RtcEngine 统计数据，详见 ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onRemoteStreamStats:(ByteRTCStreamKey* _Nonnull)streamKey
                      stats:(ByteRTCRemoteStreamStats* _Nonnull)stats;
/**
 * @locale zh
 * @type callback
 * @region 音视频回退
 * @brief 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。
 * @param streamKey 参看 ByteRTCStreamKey{@link #ByteRTCStreamKey}。
 * @param event 音视频流发生变化的信息。参看 ByteRTCRemoteStreamSwitchEvent{@link #ByteRTCRemoteStreamSwitchEvent}。
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onSimulcastSubscribeFallback:(ByteRTCStreamKey* _Nonnull)streamKey
                               event:(ByteRTCRemoteStreamSwitchEvent* _Nonnull)event;
/**
 * @locale zh
 * @type callback
 * @region 音视频回退
 * @brief 本地未通过 setPublishFallbackOption:{@link #ByteRTCVideo#setPublishFallbackOption:} 开启发布性能回退，检测到设备性能不足时，收到此回调。<br>
 *        本地通过 setPublishFallbackOption:{@link #ByteRTCVideo#setPublishFallbackOption:} 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。
 * @param streamIndex 流索引，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param mode 指示本地是否开启发布回退功能。参看 ByteRTCPerformanceAlarmMode{@link #ByteRTCPerformanceAlarmMode}  <br>
 *                  + 当发布端未开启发布性能回退时，mode 值为 kPerformanceAlarmModeNormal。  <br>
 *                  + 当发布端开启发布性能回退时，mode 值为 kPerformanceAlarmModeSimulcast。
 * @param reason 告警原因，参看 ByteRTCPerformanceAlarmReason{@link #ByteRTCPerformanceAlarmReason}
 * @param data 性能回退相关数据，详见 ByteRTCSourceWantedData{@link #ByteRTCSourceWantedData}。
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onPerformanceAlarms:(ByteRTCStreamIndex)streamIndex
                       mode:(ByteRTCPerformanceAlarmMode)mode
                     reason:(ByteRTCPerformanceAlarmReason)reason
           sourceWantedData:(ByteRTCSourceWantedData* _Nonnull)data;
@end

/**
 * @locale zh
 * @type api
 * @brief ByteRTCVideoEx class
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoEx : ByteRTCVideo
/**
* @locale zh
* @type api
* @brief 创建 ByteRTCVideoEx 实例。  <br>
*        如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
*        如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。
* @param appId 每个应用的唯一标识符。只有使用相同的 app_id 生成的实例，才能够进行音视频通信。
* @param delegate SDK 回调给应用层的 Callback 对象，详见 ByteRTCVideoDelegate{@link #ByteRTCVideoDelegate} 。
* @param delegateEx SDK 回调给应用层的 Callback 对象，详见 ByteRTCVideoDelegateEx{@link #ByteRTCVideoDelegateEx} 。
* @param parameters 私有参数。如需使用请联系技术支持人员。
* @return ByteRTCVideoEx：创建成功。返回一个可用的 ByteRTCVideoEx{@link #ByteRTCVideoEx} 实例  
*/
+ (ByteRTCVideoEx* _Nullable)createRTCVideoEx:(NSString* _Nonnull)appId
                                     delegate:(id<ByteRTCVideoDelegate> _Nullable)delegate
                                   delegateEx:(id<ByteRTCVideoDelegateEx> _Nullable)delegateEx
                                   parameters:(NSDictionary* _Nonnull)parameters;
/**
 * @locale zh
 * @type api
 * @brief 销毁由 ByteRTCVideoEx 实例，并释放所有相关资源。
 * @note  
 *        + 请确保和需要销毁的 ByteRTCVideoEx 实例相关的业务场景全部结束后，才调用此方法。如果在多线程场景下，调用此接口后，又调用了其他 ByteRTCVideoEx 相关接口，可能导致 SDK 崩溃。该方法在调用之后，会销毁所有和此 ByteRTCVideoEx 实例相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，会导致死锁。同时此方法是耗时操作，不建议在主线程调用本方法，避免主线程阻塞。
 */
+ (void)destroyRTCVideoEx NS_SWIFT_NAME(destroyRTCVideoEx());
/**
 * @locale zh
 * @type api
 * @brief 设置回调句柄。
 * @param delegateEx 参看 ByteRTCVideoDelegateEx{@link #ByteRTCVideoDelegateEx}。
 */
- (void)setDelegateEx:(id<ByteRTCVideoDelegateEx> _Nullable)delegateEx;
/**
 * @locale zh
 * @type api
 * @brief 创建 ByteRTCRoomEx{@link #ByteRTCRoomEx} 实例。<br>
 *        调用此方法仅返回一个房间实例，你仍需调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 才能真正地创建/加入房间。
 * @param roomId 标识通话房间的房间 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
 * @return 创建的 ByteRTCRoomEx{@link #ByteRTCRoomEx} 房间实例。
 * @note 请勿使用同样的 roomId 创建多个房间，否则后创建的房间实例会替换先创建的房间实例。
 */
- (ByteRTCRoomEx* _Nullable)createRTCRoomEx:(NSString* _Nonnull)roomId;
/**
 * @locale zh
 * @type api
 * @brief 设置视频源的相关配置。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param config 参看 ByteRTCVideoSourceConfig{@link #ByteRTCVideoSourceConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
- (int)setVideoSource:(ByteRTCStreamIndex)streamIndex videoSourceConfig:(ByteRTCVideoSourceConfig* _Nonnull)config;
/**
 * @locale zh
 * @type api
 * @region 自定义视频采集渲染
 * @brief 推送外部视频帧。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param frame 该视频帧包含待 SDK 编码的视频数据，参考 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note 推送外部视频帧前，必须调用 setVideoSource:videoSourceConfig:{@link #ByteRTCVideoEx#setVideoSource:videoSourceConfig:} 开启外部视频源采集。
 */
- (int)pushExternalVideoFrame:(ByteRTCStreamIndex)streamIndex videoFrame:(ByteRTCVideoFrame* _Nonnull)frame;
/**
 * @locale zh
 * @type api
 * @brief 设置流的优先级。<br>
 *        在网络条件有限的情况下，优先保障高优先级视频流的清晰度和流畅度，优先保障高优先级流的音频流畅度和音质。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param priority 参看 ByteRTCStreamPriority{@link #ByteRTCStreamPriority}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 */
- (int)setLocalStreamPriority:(ByteRTCStreamIndex)streamIndex priority:(ByteRTCStreamPriority)priority;
/**
 * @locale zh
 * @type api
 * @brief 设置 RTC SDK 内部采集时的视频采集参数。<br>
 *        如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数，包括模式、分辨率、帧率。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param captureConfig 视频采集参数。参看: ByteRTCVideoCaptureConfig{@link #ByteRTCVideoCaptureConfig}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  
 * + 本接口在引擎创建后可调用，调用后立即生效。建议在调用 startVideoCapture:deviceId:{@link #ByteRTCVideoEx#startVideoCapture:deviceId:} 前调用本接口。<br>
 * + 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 Auto 模式。
 */
- (int)setVideoCaptureConfig:(ByteRTCStreamIndex)streamIndex
               captureConfig:(ByteRTCVideoCaptureConfig* _Nullable)captureConfig;

#if BYTERTC_TARGET_MAC
/**
 * @locale zh
 * @type api
 * @brief 立即开启内部视频采集。默认为关闭状态。  <br>
 *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
 *        调用该方法后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
 *        本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 rtcEngine:onUserStartVideoCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStartVideoCapture:uid:} 的回调。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param deviceId 设备 ID
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  
 *       + 调用 stopVideoCapture:{@link #ByteRTCVideoEx#stopVideoCapture:} 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。  <br>
 *       + 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。  <br>
 *       + 如果需要从自定义视频采集切换为内部视频采集，你必须先关闭自定义采集，再调用此方法手动开启内部采集。
 */
- (int)startVideoCapture:(ByteRTCStreamIndex)streamIndex deviceId:(NSString* _Nonnull)deviceId;
#endif
/**
 * @locale zh
 * @type api
 * @brief 立即关闭内部视频采集。默认为关闭状态。  <br>
 *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
 *        调用该方法后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
 *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopVideoCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStopVideoCapture:uid:} 的回调。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  
 *       + 调用 startVideoCapture:deviceId{@link #ByteRTCVideoEx#startVideoCapture:deviceId:} 可以开启内部视频采集。  <br>
 *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。
 */
- (int)stopVideoCapture:(ByteRTCStreamIndex)streamIndex;
/**
 * @locale zh
 * @type api
 * @brief 调节远端流的音频播放音量。你必须在进房后进行设置。流的发布状态改变不影响设置生效。
 * @param streamKey 参看 ByteRTCStreamKey{@link #ByteRTCStreamKey}。
 * @param volume 音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。<br>
 *               为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note 假设某远端用户 A 始终在被调节的目标用户范围内：<br>
 *        + 当该方法与 setRemoteRoomAudioPlaybackVolume:{@link #ByteRTCRoom#setRemoteRoomAudioPlaybackVolume:} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
 *        + 当该方法与 setPlaybackVolume:{@link #ByteRTCVideo#setPlaybackVolume:} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
 */
- (int)setRemoteAudioPlaybackVolume:(ByteRTCStreamKey* _Nonnull)streamKey volume:(int)volume;
/**
 * @locale zh
 * @type api
 * @brief 调节麦克风音频采集音量。对于屏幕音频的采集音量，参看 setScreenCaptureVolume:{@link #ByteRTCVideoEx#setScreenCaptureVolume:}。
 * @param volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。<br>
 *               只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
 *               为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 * @return  
 *        + 0: 调用成功。<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note 在开启麦克风音频采集前后，你都可以使用此接口设定采集音量。
 */
- (int)setCaptureVolume:(int)volume;
/**
 * @locale zh
 * @type api
 * @brief 调节屏幕音频采集音量。对于麦克风音频的采集音量，参看 setCaptureVolume:{@link #ByteRTCVideoEx#setCaptureVolume:}。
 * @param volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。<br>
 *               只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
 *               为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 * @return  
 *        + 0: 调用成功。<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note 在开启屏幕音频采集前后，你都可以使用此接口设定采集音量。
 */
- (int)setScreenCaptureVolume:(int)volume;
/**
 * @locale zh
 * @type api
 * @brief 设置音频源的整体音量。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param volume 音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。<br>
 *               只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
 *               为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 * @return  
 *        + 0: 调用成功。<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 */
- (int)setAudioSourceVolume:(ByteRTCStreamIndex)streamIndex volume:(int)volume;
/**
 * @locale zh
 * @type api
 * @brief 设置音频源的内容。单个音频源的内容可以包含一个或多个原始音频来源。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param config 内容构成。参看 ByteRTCAudioContentTypeConfig{@link #ByteRTCAudioContentTypeConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 */
- (int)setAudioContentType:(ByteRTCStreamIndex)streamIndex config:(ByteRTCAudioContentTypeConfig* _Nonnull)config;
/**
 * @locale zh
 * @type api
 * @brief 设置音频流的编码配置。
 * @param streamIndex 源对应的流的索引。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param config 编码设置。参看 ByteRTCAudioEncodeConfig{@link #ByteRTCAudioEncodeConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 */
- (int)setAudioEncodeConfig:(ByteRTCStreamIndex)streamIndex config:(ByteRTCAudioEncodeConfig* _Nonnull)config;

@end
