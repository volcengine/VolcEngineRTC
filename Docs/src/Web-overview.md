---
is_dir: False    # True for dir; False for doc
status: 1    # 1 for online; 0 for offline
keywords: 实时音视频    # use ',' as separator
---

## 引擎管理

| 方法 | 描述 |
| :-- | :-- |
| [createEngine](Web-api#vertc-createengine) | 创建引擎对象。你必须先使用此方法，以使用 RTC 提供的各种音视频能力。<br>再次调用此方法时，会创建另一个独立的引擎实例。 |
| [destroyEngine](Web-api#vertc-destroyengine) | 手动销毁通过 [createEngine](Web-api#createengine) 所创建的引擎对象。 |
| [setBusinessId](Web-api#rtcengine-setbusinessid) | 设置业务标识参数<br>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [getSdkVersion](Web-api#vertc-getsdkversion) | 获取 SDK 当前的版本号。 |
| [isSupported](Web-api#vertc-issupported) | 浏览器是否支持 |
| [getSupportedCodecs](Web-api#vertc-getsupportedcodecs) | 获取当前浏览器支持的编解码类型。<br>若你已开通 vp8 业务，可以在进房前调用该接口查看当前浏览器是否支持 vp8 编码类型 |
| [setLogConfig](Web-api#vertc-setlogconfig) | 配置本地缓存的日志级别, 以及可使用的最大缓存空间。 |
| [downloadLog](Web-api#vertc-downloadlog) | 下载本地缓存生成文件。 |


## 设备管理

| 方法 | 描述 |
| :-- | :-- |
| [enumerateDevices](Web-api#vertc-enumeratedevices) | 枚举可用的媒体输入和输出设备，比如麦克风、摄像头、耳机等。<br>可以通过该方法获取设备的 deviceId, 用于在 [setAudioPlaybackDevice](Web-api#setaudioplaybackdevice)、[startVideoCapture](Web-api#startvideocapture)、[startAudioCapture](Web-api#startaudiocapture) 方法中指定采集/播放设备。 |
| [enableDevices](Web-api#vertc-enabledevices) | 向用户获取设备权限 |
| [enumerateAudioCaptureDevices](Web-api#vertc-enumerateaudiocapturedevices) | 该方法枚举可用的麦克风。<br>可以通过该方法获取设备的 `deviceId`, 用于在 [startAudioCapture](Web-api#startaudiocapture)、[setAudioCaptureDevice](Web-api#setaudiocapturedevice) 方法中指定使用的麦克风设备。 |
| [enumerateVideoCaptureDevices](Web-api#vertc-enumeratevideocapturedevices) | 该方法枚举可用的摄像头等。<br>可以通过该方法获取设备的 deviceId, 用于在 [startVideoCapture](Web-api#startvideocapture)、[setVideoCaptureDevice](Web-api#setvideocapturedevice) 方法中指定使用的摄像头设备。 |
| [enumerateAudioPlaybackDevices](Web-api#vertc-enumerateaudioplaybackdevices) | 该方法枚举可用的音频播放设备，例如耳机、音箱等。<br>可以通过该方法获取设备的 deviceId, 可用于 [setAudioPlaybackDevice](Web-api#setaudioplaybackdevice) 方法中指定音频播放设备。 |
| [startAudioPlaybackDeviceTest](Web-api#rtcengine-startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 [onAudioPlaybackDeviceTestVolume](Web-event#onaudioplaybackdevicetestvolume) 回调播放时的音量信息。 |
| [stopAudioPlaybackDeviceTest](Web-api#rtcengine-stopaudioplaybackdevicetest) | 停止音频播放设备测试。 |
| [startAudioDeviceRecordTest](Web-api#rtcengine-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br>建议提前调用 [enableAudioPropertiesReport](Web-api#enableaudiopropertiesreport) 注册音量提示回调，测试开始后，音频设备开始采集本地声音，可以通过 [onLocalAudioPropertiesReport](Web-event#onlocalaudiopropertiesreport) 获取采集音量。 |
| [stopAudioDeviceRecordAndPlayTest](Web-api#rtcengine-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>调用 [startAudioDeviceRecordTest](Web-api#startaudiodevicerecordtest) 30s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
| [stopAudioDevicePlayTest](Web-api#rtcengine-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Web-api#startaudiodevicerecordtest) 开始的音频播放设备测试。<br>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |
| [onAudioPlaybackDeviceTestVolume](Web-event#engineevents-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |


## 房间管理

| 方法 | 描述 |
| :-- | :-- |
| [joinRoom](Web-api#rtcengine-joinroom) | 加入房间。<br>调用此方法加入房间，同房间内其他用户进行音视频通话。 |
| [leaveRoom](Web-api#rtcengine-leaveroom) | 离开房间。<br>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。 |
| [updateToken](Web-api#rtcengine-updatetoken) | 更新 Token。<br>用于加入房间的 Token 有一定的有效期。Token 过期前 30 秒将收到 [onTokenWillExpire](Web-event#ontokenwillexpire) 回调，需要调用此方法更新房间的 Token 信息。 |
| [setUserVisibility](Web-api#rtcengine-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br>默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，最多 30 人可同时上麦。更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。 |
| [setAudioSelectionConfig](Web-api#rtcengine-setaudioselectionconfig) | 设置本端发布流在音频选路中的优先级。 |
| [onUserJoined](Web-event#engineevents-onuserjoined) | 远端可见用户加入房间，或房内不可见用户切换为可见的回调 |
| [onUserLeave](Web-event#engineevents-onuserleave) | 远端可见用户离开房间，或房内可见用户切换为隐身的回调 |
| [onConnectionStateChanged](Web-event#engineevents-onconnectionstatechanged) | 连接状态发生变化 |
| [onError](Web-event#engineevents-onerror) | 当 SDK 内部发生不可逆转错误时触发该回调。 |
| [onTokenWillExpire](Web-event#engineevents-ontokenwillexpire) | Token 过期前 30 秒将触发该回调。<br>调用 [updateToken](Web-api#updatetoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。 |
| [onTokenPublishPrivilegeWillExpire](Web-event#engineevents-ontokenpublishprivilegewillexpire) | Token 发布权限过期前 30 秒将触发该回调。<br>收到该回调后，调用 [updateToken](Web-api#updatetoken) 更新 Token。 |
| [onTokenPublishPrivilegeDidExpired](Web-event#engineevents-ontokenpublishprivilegedidexpired) | Token 发布权限过期时触发该回调，调用 [updateToken](Web-api#updatetoken) 更新 Token。 |
| [onTokenSubscribePrivilegeWillExpire](Web-event#engineevents-ontokensubscribeprivilegewillexpire) | Token 订阅权限过期前 30 秒将触发该回调。<br>收到该回调后，调用 [updateToken](Web-api#updatetoken) 更新 Token。 |
| [onTokenSubscribePrivilegeDidExpired](Web-event#engineevents-ontokensubscribeprivilegedidexpired) | Token 订阅权限过期时触发该回调，调用 [updateToken](Web-api#updatetoken) 更新 Token。 |


## 音频管理

| 方法 | 描述 |
| :-- | :-- |
| [setAudioCaptureDevice](Web-api#rtcengine-setaudiocapturedevice) | 设置内部采集时使用的麦克风。 |
| [setAudioPlaybackDevice](Web-api#rtcengine-setaudioplaybackdevice) | 设置音频播放设备，例如扬声器或者耳机，默认使用扬声器。 |
| [startAudioCapture](Web-api#rtcengine-startaudiocapture) | 开启内部音频采集。默认为关闭状态。<br>内部采集是指：使用 RTC SDK 内置采集机制进行音频采集。<br>可见用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Web-event#onuserstartaudiocapture) 的回调。 |
| [startAudioAndVideoCapture](Web-api#rtcengine-startaudioandvideocapture) | 使用内部采集模块同时开启音视频采集。调用该方法，浏览器会同时请求麦克风和摄像头授权，用户只需授权一次。<br>可见用户进房后调用该方法，房间中的其他用户会收到 [onUserStartVideoCapture](Web-event#onuserstartvideocapture) 和 [onUserStartAudioCapture](Web-event#onuserstartaudiocapture) 的回调。 |
| [stopAudioCapture](Web-api#rtcengine-stopaudiocapture) | 立即关闭内部音频采集。<br>发布流后调用该方法，房间内的其他用户会收到 [onUserStopAudioCapture](Web-event#onuserstopaudiocapture) 的回调。 |
| [setAudioProfile](Web-api#rtcengine-setaudioprofile) | 设置音质档位 |
| [setCaptureVolume](Web-api#rtcengine-setcapturevolume) | 调节音频采集音量。 |
| [setPlaybackVolume](Web-api#rtcengine-setplaybackvolume) | 调节本地播放的单个远端用户的音量。 |
| [getAudioVolume](Web-api#rtcengine-getaudiovolume) | 获取音量大小。包括内部采集、外部采集的本地流以及远端流。 |
| [setAudioCaptureConfig](Web-api#rtcengine-setaudiocaptureconfig) | 设置 RTC SDK 内部采集时的音频采集参数。默认参数由浏览器决定。 |
| [enableAudioPropertiesReport](Web-api#rtcengine-enableaudiopropertiesreport) | 启用音频信息提示。 |
| [onAudioDeviceStateChanged](Web-event#engineevents-onaudiodevicestatechanged) | 音频媒体设备状态改变。 |
| [onLocalAudioPropertiesReport](Web-event#engineevents-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Web-api#enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。<br>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。 |
| [onRemoteAudioPropertiesReport](Web-event#engineevents-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Web-api#enableaudiopropertiesreport)，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。<br>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onActiveSpeaker](Web-event#engineevents-onactivespeaker) | 成功调用 [enableAudioPropertiesReport](Web-api#enableaudiopropertiesreport) 后，当房间内用户数量大于或等于 2 且有活跃用户时，你会周期性收到此回调，获取房间内音量最大用户的信息。 |
| [onAudioPlaybackDeviceChanged](Web-event#engineevents-onaudioplaybackdevicechanged) | 当调用 [setAudioPlaybackDevice](Web-api#setaudioplaybackdevice) 设置音频播放设备时，会收到此事件。 |
| [onUserStartAudioCapture](Web-event#engineevents-onuserstartaudiocapture) | 房间内的可见用户调用 [startAudioCapture](Web-api#startaudiocapture) 开启音频采集时，房间内其他用户会收到此事件。 |
| [onUserStopAudioCapture](Web-event#engineevents-onuserstopaudiocapture) | 房间内的可见用户调用 [stopAudioCapture](Web-api#stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此事件。 |


## 视频管理

| 方法 | 描述 |
| :-- | :-- |
| [setVideoCaptureDevice](Web-api#rtcengine-setvideocapturedevice) | 设置内部采集时使用的摄像头。 |
| [startVideoCapture](Web-api#rtcengine-startvideocapture) | 开启内部视频采集。默认为关闭状态。<br>内部视频采集是指：使用 RTC SDK 内置的视频采集机制进行视频采集。<br>可见用户进房后调用该方法，房间中的其他用户会收到 [onUserStartVideoCapture](Web-event#onuserstartvideocapture) 的回调。 |
| [stopVideoCapture](Web-api#rtcengine-stopvideocapture) | 关闭内部视频采集。<br>发布流后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Web-event#onuserstopvideocapture) 的回调。 |
| [setLocalVideoPlayer](Web-api#rtcengine-setlocalvideoplayer) | 设置本地视频渲染时，使用的视图，并设置渲染模式。<br>调用本方法绑定视图以后，你可以通过 `onPlayerEvent` 来监听播放状态。<br>你可以通过再次调用本方法，并绑定空视图来解除绑定。如果已创建了多个播放器，且存在默认播放器，不指定 playerId，将解绑默认播放器。 |
| [setRemoteVideoPlayer](Web-api#rtcengine-setremotevideoplayer) | 设置远端视频渲染时使用的视图，并设置渲染模式。<br>建议在收到 [onUserPublishStream](Web-event#onuserpublishstream)/[onUserPublishScreen](Web-event#onuserpublishscreen) 事件后，调用本方法对远端视频视图进行设置。<br>你可以通过再次调用本方法，并绑定空视图来解除绑定。如果已创建了多个播放器，且存在默认播放器，不指定 playerId，将解绑默认播放器。 |
| [play](Web-api#rtcengine-play) | 手动开启音视频流播放。 |
| [stop](Web-api#rtcengine-stop) | 暂停音视频流播放。 |
| [setLocalVideoMirrorType](Web-api#rtcengine-setlocalvideomirrortype) | 是否开启本地视频流镜像模式。 |
| [setRemoteVideoMirrorType](Web-api#rtcengine-setremotevideomirrortype) | 开关远端视频流镜像模式。 |
| [setVideoEncoderConfig](Web-api#rtcengine-setvideoencoderconfig) | 在视频发布端设置发布的视频流参数。 |
| [setDummyCaptureImagePath](Web-api#rtcengine-setdummycaptureimagepath) | 停止内部摄像头采集时，使用静态图片填充本地推送的视频流。 |
| [onVideoDeviceStateChanged](Web-event#engineevents-onvideodevicestatechanged) | 视频媒体设备状态改变。 |
| [onUserStartVideoCapture](Web-event#engineevents-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Web-api#startvideocapture) 开启内部视频采集时，房间内其他用户会收到此事件。 |
| [onUserStopVideoCapture](Web-event#engineevents-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Web-api#stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此事件。 |
| [onLocalVideoSizeChanged](Web-event#engineevents-onlocalvideosizechanged) | 当实际采集的参数与设置的编码参数不一致时，SDK 会触发该回调返回实际采集视频的参数。 |
| [onPlayerEvent](Web-event#engineevents-onplayerevent) | 播放器事件 |
| [onAutoplayFailed](Web-event#engineevents-onautoplayfailed) | 自动播放失败 |
| [onTrackEnded](Web-event#engineevents-ontrackended) | 断流事件，建议在回调里重新采集。 |


## 音视频传输

| 方法 | 描述 |
| :-- | :-- |
| [publishStream](Web-api#rtcengine-publishstream) | 在当前所在房间内发布本地摄像头/麦克风采集的媒体流 |
| [unpublishStream](Web-api#rtcengine-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [subscribeStream](Web-api#rtcengine-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流。<br>该方法对自动订阅和手动订阅模式均适用。 |
| [unsubscribeStream](Web-api#rtcengine-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。<br>该方法对自动订阅和手动订阅模式均适用。 |
| [pauseAllSubscribedStream](Web-api#rtcengine-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Web-api#rtcengine-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [setRemoteVideoConfig](Web-api#rtcengine-setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [enableSimulcastMode](Web-api#rtcengine-enablesimulcastmode) | 在视频发布端设置摄像头视频流的大小流模式。 |
| [setSubscribeFallbackOption](Web-api#rtcengine-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。<br>回退指在网络不佳时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority](Web-api#rtcengine-setremoteuserpriority) | 设置用户优先级。<br>该方法与 [setSubscribeFallbackOption](Web-api#setsubscribefallbackoption) 搭配使用。<br>开启回退后，会优先保证收到的高优先级用户的流的质量。 |
| [startForwardStreamToRooms](Web-api#rtcengine-startforwardstreamtorooms) | 开始跨房间转发媒体流，示例代码可参看[跨房间转发媒体流功能文档](https://www.volcengine.com/docs/6348/104398)。<br>在调用 [joinRoom](Web-api#rtcengine-joinroom) 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。 |
| [updateForwardStreamToRooms](Web-api#rtcengine-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br>通过 [startForwardStreamToRooms](Web-api#rtcengine-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。 |
| [stopForwardStreamToRooms](Web-api#rtcengine-stopforwardstreamtorooms) | 停止向所有目标房间转发媒体流。 |
| [pauseForwardStreamToAllRooms](Web-api#rtcengine-pauseforwardstreamtoallrooms) | 暂停向所有目标房间转发媒体流。<br>调用本方法暂停向所有目标房间转发后，你可以调用 [resumeForwardStreamToAllRooms](Web-api#rtcengine-resumeforwardstreamtoallrooms) 恢复转发。 |
| [resumeForwardStreamToAllRooms](Web-api#rtcengine-resumeforwardstreamtoallrooms) | 恢复向所有目标房间转发媒体流。 |
| [onUserPublishStream](Web-event#engineevents-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集音视频流的回调。 |
| [onUserUnpublishStream](Web-event#engineevents-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onRemoteVideoFirstFrame](Web-event#engineevents-onremotevideofirstframe) | 视频首帧渲染 |
| [getRemoteVideoStats](Web-api#rtcengine-getremotevideostats) | 获取用户订阅的远端视频流统计信息以及网络状况。 |
| [onRemoteAudioFirstFrame](Web-event#engineevents-onremoteaudiofirstframe) | 远端音频首帧播放事件 |
| [getRemoteAudioStats](Web-api#rtcengine-getremoteaudiostats) | 获取用户订阅的远端音频流统计信息以及网络状况。 |
| [getLocalVideoStats](Web-api#rtcengine-getlocalvideostats) | 获取本地视频流统计信息以及网络状况。 |
| [getLocalAudioStats](Web-api#rtcengine-getlocalaudiostats) | 本地音频流统计信息以及网络状况。 |
| [onRemoteStreamStats](Web-event#engineevents-onremotestreamstats) | 用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s |
| [onLocalStreamStats](Web-event#engineevents-onlocalstreamstats) | 本地音/视频流统计信息以及网络状况，统计周期为 2s |
| [onAutoSubscribeResult](Web-event#engineevents-onautosubscriberesult) | 如果开启了自动订阅，订阅成功或者失败后可以收到此事件 |
| [onAutoPublishResult](Web-event#engineevents-onautopublishresult) | 如果开启了自动发布，发布成功或者失败后可以收到此事件 |
| [onNetworkQuality](Web-event#engineevents-onnetworkquality) | 加入房间后，会以每2秒一次的频率，收到本端上行及下行的网络质量信息。 |
| [onSimulcastSubscribeFallback](Web-event#engineevents-onsimulcastsubscribefallback) | 订阅的视频流发生回退，或从回退中恢复时，收到此回调。 |
| [onRemoteVideoSizeChanged](Web-event#engineevents-onremotevideosizechanged) | 远端视频分辨率发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onVideoStreamBanned](Web-event#engineevents-onvideostreambanned) | 调用服务端接口 BanUserStream/UnbanUserStream 封禁/解禁指定用户的视频流发布时，触发该回调。 |
| [onAudioStreamBanned](Web-event#engineevents-onaudiostreambanned) | 调用服务端接口 BanUserStream/UnbanUserStream 封禁/解禁指定用户的音频流发布时，触发该回调。 |
| [onForwardStreamError](Web-event#engineevents-onforwardstreamerror) | 设置跨房间转发媒体流失败时收到本事件。 |


## 公共流

| 方法 | 描述 |
| :-- | :-- |
| [startPushPublicStream](Web-api#rtcengine-startpushpublicstream) | 发布一路公共流。 |
| [updatePublicStreamParam](Web-api#rtcengine-updatepublicstreamparam) | 更新公共流参数。<br>调用 [startPushPublicStream](Web-api#startpushpublicstream) 发布一路公共流。 |
| [stopPushPublicStream](Web-api#rtcengine-stoppushpublicstream) | 停止发布公共流。<br>调用 [startPushPublicStream](Web-api#startpushpublicstream) 发布一路公共流。 |
| [startPlayPublicStream](Web-api#rtcengine-startplaypublicstream) | 订阅指定公共流。<br>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream](Web-api#rtcengine-stopplaypublicstream) | 取消订阅指定公共流。<br>关于订阅公共流，查看 [startPlayPublicStream](Web-api#startplaypublicstream)。 |
| [setPublicStreamVideoPlayer](Web-api#rtcengine-setpublicstreamvideoplayer) | 为指定公共流设置使用的视图和渲染模式。 |
| [setPublicStreamVolume](Web-api#rtcengine-setpublicstreamvolume) | 调节本地播放的公共流播放音量。 |
| [onPublicStreamStats](Web-event#engineevents-onpublicstreamstats) | 调用 [startPlayPublicStream](Web-api#startplaypublicstream) 订阅公共流，后将触发此回调，周期为 2s，包含各项统计信息。 |
| [onPushPublicStreamResult](Web-event#engineevents-onpushpublicstreamresult) | 公共流发布结果回调。<br>调用 [startPushPublicStream](Web-api#startpushpublicstream) 发布公共流后，结果通过此回调通知用户。 |
| [onPublicStreamSEIMessageReceived](Web-event#engineevents-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br>调用 [startPlayPublicStream](Web-api#startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [onFirstPublicStreamAudioFrameDecoded](Web-event#engineevents-onfirstpublicstreamaudioframedecoded) | 公共流的音频首帧解码成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api#startplaypublicstream)。 |
| [onFirstPublicStreamVideoFrameDecoded](Web-event#engineevents-onfirstpublicstreamvideoframedecoded) | 公共流的视频首帧解码成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api#startplaypublicstream)。 |
| [onFirstPublicStreamVideoFrameRendered](Web-event#engineevents-onfirstpublicstreamvideoframerendered) | 公共流的首帧视频渲染成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api#startplaypublicstream)。 |


## 屏幕分享

| 方法 | 描述 |
| :-- | :-- |
| [startScreenCapture](Web-api#rtcengine-startscreencapture) | 使用内部采集模块，采集当前屏幕视频流，用于共享。 |
| [stopScreenCapture](Web-api#rtcengine-stopscreencapture) | 停止屏幕共享流内部采集。 |
| [setScreenEncoderConfig](Web-api#rtcengine-setscreenencoderconfig) | 设置共享屏幕的视频编码参数，同时对视频采集生效。<br>若设置的参数浏览器不支持，RTC SDK 按照浏览器支持的参数范围进行采集和编码，并通过回调 [onLocalVideoSizeChanged](Web-event#onlocalvideosizechanged) 通知采集的实际参数。 |
| [publishScreen](Web-api#rtcengine-publishscreen) | 在当前所在房间内发布本地屏幕共享音视频流 |
| [unpublishScreen](Web-api#rtcengine-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [subscribeScreen](Web-api#rtcengine-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流。<br>该方法对自动订阅和手动订阅模式均适用。 |
| [unsubscribeScreen](Web-api#rtcengine-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。<br>该方法对自动订阅和手动订阅模式均适用。 |
| [onUserPublishScreen](Web-event#engineevents-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](Web-event#engineevents-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |


## 混音

| 方法 | 描述 |
| :-- | :-- |
| [getAudioMixingManager](Web-api#rtcengine-getaudiomixingmanager) | 混音管理接口创建 |
| [startAudioMixing](Web-api#audiomixingmanager-startaudiomixing) | 开启混音 |
| [stopAudioMixing](Web-api#audiomixingmanager-stopaudiomixing) | 停止播放音频文件 |
| [pauseAudioMixing](Web-api#audiomixingmanager-pauseaudiomixing) | 暂停播放音频文件 |
| [resumeAudioMixing](Web-api#audiomixingmanager-resumeaudiomixing) | 恢复播放音频文件 |
| [preloadAudioMixing](Web-api#audiomixingmanager-preloadaudiomixing) | 预加载指定音频文件到内存中 |
| [unloadAudioMixing](Web-api#audiomixingmanager-unloadaudiomixing) | 卸载指定音频文件 |
| [getAudioMixingVolume](Web-api#audiomixingmanager-getaudiomixingvolume) | 获取音频文件的音量 |
| [setAudioMixingVolume](Web-api#audiomixingmanager-setaudiomixingvolume) | 调节音频文件混音的音量大小。 |
| [getAudioMixingDuration](Web-api#audiomixingmanager-getaudiomixingduration) | 获取音频文件时长 |
| [getAudioMixingCurrentPosition](Web-api#audiomixingmanager-getaudiomixingcurrentposition) | 获取音频文件播放进度 |
| [setAudioMixingPosition](Web-api#audiomixingmanager-setaudiomixingposition) | 设置音频文件的起始播放位置 |
| [enableAudioMixingBuffer](Web-api#audiomixingmanager-enableaudiomixingbuffer) | 启动 PCM 音频数据混音 |
| [disableAudioMixingBuffer](Web-api#audiomixingmanager-disableaudiomixingbuffer) | 关闭 PCM 混音 |
| [pushAudioMixingBuffer](Web-api#audiomixingmanager-pushaudiomixingbuffer) | 推送 PCM 音频数据用于混音 |
| [onAudioMixingStateChanged](Web-event#engineevents-onaudiomixingstatechanged) | 音频混音文件播放状态改变事件 |
| [setAudioFrameCallback](Web-api#audiomixingmanager-setaudioframecallback) | 开关混音音频帧 PCM 数据回调。 |


## CDN 推流

| 方法 | 描述 |
| :-- | :-- |
| [defaultTranscoding](Web-api#rtcengine-defaulttranscoding) | 获取合流转推默认参数。 |
| [startLiveTranscoding](Web-api#rtcengine-startlivetranscoding) | 开启转推直播，并设置合流的视频视图布局和音频属性。 |
| [updateLiveTranscoding](Web-api#rtcengine-updatelivetranscoding) | 更新转推直播参数。<br>使用 [startLiveTranscoding](Web-api#startlivetranscoding) 启用转推直播功能后，使用此方法更新功能配置参数。 |
| [stopLiveTranscoding](Web-api#rtcengine-stoplivetranscoding) | 停止转推直播。<br>关于启动转推直播，参看 [startLiveTranscoding](Web-api#startlivetranscoding)。 |
| [onStreamMixingEvent](Web-event#engineevents-onstreammixingevent) | 转推直播相关事件 |


## 自定义流处理

| 方法 | 描述 |
| :-- | :-- |
| [setVideoSourceType](Web-api#rtcengine-setvideosourcetype) | 设置向 SDK 输入的视频源<br>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。<br>该方法进房前后均可调用。<br>当你已调用 [startVideoCapture](Web-api#startvideocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。<br>当你调用此方法开启自定义采集，再调用此方法切换至内部采集时，必须再调用 [startVideoCapture](Web-api#startvideocapture) 手动开启内部采集。 |
| [setExternalVideoTrack](Web-api#rtcengine-setexternalvideotrack) | 使用用户自定义的 videoTrack。<br>调用本方法前必须先调用 [setVideoSourceType](Web-api#setvideosourcetype) 设置为自定义视频采集。 |
| [setAudioSourceType](Web-api#rtcengine-setaudiosourcetype) | 设置向 SDK 输入的音频源<br>默认使用内部采集。内部采集指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br>该方法进房前后均可调用。<br>当你已调用 [startAudioCapture](Web-api#startaudiocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。<br>当你调用此方法开启自定义采集，再调用此方法切换至内部采集时，必须再调用 [startAudioCapture](Web-api#startaudiocapture) 手动开启内部采集。 |
| [setExternalAudioTrack](Web-api#rtcengine-setexternalaudiotrack) | 使用用户自定义的 audioTrack。<br>调用本方法前必须先调用 [setAudioSourceType](Web-api#setaudiosourcetype) 设置为自定义音频采集。 |
| [getLocalStreamTrack](Web-api#rtcengine-getlocalstreamtrack) | 获取本地用户的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
| [getRemoteStreamTrack](Web-api#rtcengine-getremotestreamtrack) | 获取已订阅的远端用户的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
| [getPublicStreamTrack](Web-api#rtcengine-getpublicstreamtrack) | 获取已订阅的公共流的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
| [setRemoteStreamRenderSync](Web-api#rtcengine-setremotestreamrendersync) | 设置远端音视频流是否同步渲染。<br>你可以通过关闭音视频同步，达到超低端到端延时的效果。 |
| [setAudioFrameCallback](Web-api#rtcengine-setaudioframecallback) | 开关音频帧 PCM 数据回调。 |


## 消息

| 方法 | 描述 |
| :-- | :-- |
| [sendUserMessage](Web-api#rtcengine-sendusermessage) | 给房间内指定的用户发送点对点文本消息。<br>若消息发送成功，则 userId 所指定的用户会收到 [onUserMessageReceived](Web-event#onusermessagereceived) 回调。 |
| [sendUserBinaryMessage](Web-api#rtcengine-senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息。<br>若消息发送成功，则 userId 所指定的用户会收到 [onUserBinaryMessageReceived](Web-event#onuserbinarymessagereceived) 回调。 |
| [sendRoomMessage](Web-api#rtcengine-sendroommessage) | 给房间内的所有其他用户群发文本消息。<br>若消息发送成功，同一房间内的其他用户会收到 [onRoomMessageReceived](Web-event#onroommessagereceived) 回调。 |
| [sendRoomBinaryMessage](Web-api#rtcengine-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。<br>若消息发送成功，同一房间内的其他用户会收到通过 [onRoomBinaryMessageReceived](Web-event#onroombinarymessagereceived) 回调发送的消息 |
| [sendSEIMessage](Web-api#rtcengine-sendseimessage) | 通过视频帧发送 SEI 数据。<br>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |
| [login](Web-api#rtcengine-login) | 登录即时消息服务器。<br>调用此方法登录后，可以向同 `appID` 下其他已登录用户发送文本或二进制消息。 |
| [logout](Web-api#rtcengine-logout) | 登出 RTS 服务器。调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken](Web-api#rtcengine-updatelogintoken) | 更新用户用于登录的 Token。Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。 |
| [getPeerOnlineStatus](Web-api#rtcengine-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态。在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。 |
| [sendUserMessageOutsideRoom](Web-api#rtcengine-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom](Web-api#rtcengine-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [setServerParams](Web-api#rtcengine-setserverparams) | 设置业务服务器参数。调用 [sendServerMessage](Web-api#sendservermessage) 或 [sendServerBinaryMessage](Web-api#sendserverbinarymessage) 发送消息给业务服务器之前，必须需要设置有效签名和业务服务器地址。 |
| [sendServerMessage](Web-api#rtcengine-sendservermessage) | 客户端给业务服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Web-api#rtcengine-sendserverbinarymessage) | 客户端给业务服务器发送二进制消息（P2Server） |
| [onUserMessageReceived](Web-event#engineevents-onusermessagereceived) | 收到来自房间中其他用户通过 [sendUserMessage](Web-api#sendusermessage) 发来的点对点文本消息时，会收到此事件 |
| [onUserBinaryMessageReceived](Web-event#engineevents-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 sendUserBinaryMessage 发来的点对点二进制消息时，会收到此事件 |
| [onRoomMessageReceived](Web-event#engineevents-onroommessagereceived) | 接收到房间内广播消息的事件。 |
| [onRoomBinaryMessageReceived](Web-event#engineevents-onroombinarymessagereceived) | 接收到房间内二进制广播消息的事件。 |
| [onSEIMessageReceived](Web-event#engineevents-onseimessagereceived) | 接收到包含 SEI 数据的视频帧事件 |
| [onSEIStreamUpdate](Web-event#engineevents-onseistreamupdate) | 包含 SEI 信息的流更新事件。<br>在语音通话场景下，远端用户调用 [sendSEIMessage](Web-api#sendseimessage) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过此事件回调本地用户。<br>你可以通过此事件判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。 |
| [onUserMessageReceivedOutsideRoom](Web-event#engineevents-onusermessagereceivedoutsideroom) | 接收到房间外消息的事件。 |
| [onUserBinaryMessageReceivedOutsideRoom](Web-event#engineevents-onuserbinarymessagereceivedoutsideroom) | 接收到房间外二进制消息的事件。 |
| [onServerParamsSetResult](Web-event#engineevents-onserverparamssetresult) | 设置接收客户端即时消息的服务器成功或失败时收到本事件。 |


## 字幕翻译服务

| 方法 | 描述 |
| :-- | :-- |
| [startSubtitle](Web-api#rtcengine-startsubtitle) | 识别或翻译房间内所有用户的语音，形成字幕。语音识别或翻译的结果会通过 [onSubtitleMessageReceived](Web-event#onsubtitlemessagereceived) 事件回调给你。<br>调用该方法后，你会收到 [onSubtitleStateChanged](Web-event#onsubtitlestatechanged) 回调，通知字幕是否开启。 |
| [stopSubtitle](Web-api#rtcengine-stopsubtitle) | 关闭字幕。<br>调用该方法后，你会收到 [onSubtitleStateChanged](Web-event#onsubtitlestatechanged) 回调，通知字幕是否关闭。 |
| [updateSubtitleConfig](Web-api#rtcengine-updatesubtitleconfig) | 开启字幕翻译后切换源语种。 |
| [onSubtitleStateChanged](Web-event#engineevents-onsubtitlestatechanged) | 字幕状态发生改变回调。<br>当你调用 [startSubtitle](Web-api#startsubtitle) 和 [stopSubtitle](Web-api#stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。 |
| [onSubtitleMessageReceived](Web-event#engineevents-onsubtitlemessagereceived) | 字幕相关信息回调。<br>当你成功调用 [startSubtitle](Web-api#startsubtitle) 后会收到此回调，通知字幕的相关信息。 |


## 视频截图

| 方法 | 描述 |
| :-- | :-- |
| [takeLocalSnapshot](Web-api#rtcengine-takelocalsnapshot) | 截取本地视频画面 |
| [takeRemoteSnapshot](Web-api#rtcengine-takeremotesnapshot) | 截取远端视频画面 |


## 插件功能

| 方法 | 描述 |
| :-- | :-- |
| [registerExtension](Web-api#rtcengine-registerextension) | 注册插件。<br>你可以通过插件实现[基础美颜功能](https://www.volcengine.com/docs/6348/148646)、[虚拟背景功能](https://www.volcengine.com/docs/6348/697417)、[AI 降噪功能](https://www.volcengine.com/docs/6348/148647)。 |

