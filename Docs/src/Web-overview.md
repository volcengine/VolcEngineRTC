## RTCEngine

| 方法 | 描述 |
| :-- | :-- |
| [joinRoom](Web-api.md#rtcengine-joinroom) | 加入房间。<br>调用此方法加入房间，同房间内其他用户进行音视频通话。 |
| [leaveRoom](Web-api.md#rtcengine-leaveroom) | 离开房间。<br>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。 |
| [publishStream](Web-api.md#rtcengine-publishstream) | 在当前所在房间内发布本地摄像头/麦克风采集的媒体流 |
| [unpublishStream](Web-api.md#rtcengine-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [publishScreen](Web-api.md#rtcengine-publishscreen) | 在当前所在房间内发布本地屏幕共享音视频流 |
| [unpublishScreen](Web-api.md#rtcengine-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [subscribeStream](Web-api.md#rtcengine-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流。<br>该方法对自动订阅和手动订阅模式均适用。 |
| [unsubscribeStream](Web-api.md#rtcengine-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。<br>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeScreen](Web-api.md#rtcengine-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流。<br>该方法对自动订阅和手动订阅模式均适用。 |
| [unsubscribeScreen](Web-api.md#rtcengine-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。<br>该方法对自动订阅和手动订阅模式均适用。 |
| [updateToken](Web-api#rtcengine-updatetoken) | 更新 Token。<br>用于加入房间的 Token 有一定的有效期。Token 过期前 30 秒将收到 [onTokenWillExpire](Web-event.md#ontokenwillexpire) 回调，需要调用此方法更新房间的 Token 信息。 |
| [setAudioCaptureDevice](Web-api.md#rtcengine-setaudiocapturedevice) | 设置内部采集时使用的麦克风。 |
| [setVideoCaptureDevice](Web-api.md#rtcengine-setvideocapturedevice) | 设置内部采集时使用的摄像头。 |
| [startVideoCapture](Web-api#rtcengine-startvideocapture) | 开启内部视频采集。默认为关闭状态。<br>内部视频采集是指：使用 RTC SDK 内置的视频采集机制进行视频采集。<br>发布流后调用该方法，房间中的其他用户会收到 [onUserStartVideoCapture](Web-event.md#onuserstartvideocapture) 的回调。 |
| [stopVideoCapture](Web-api#rtcengine-stopvideocapture) | 关闭内部视频采集。默认为关闭状态。<br>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>发布流后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Web-event.md#onuserstopvideocapture) 的回调。 |
| [startAudioCapture](Web-api#rtcengine-startaudiocapture) | 立即开启内部音频采集。默认为关闭状态。<br>内部采集是指：使用 RTC SDK 内置采集机制进行音频采集。<br>发布流后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Web-event.md#onuserstartaudiocapture) 的回调。 |
| [stopAudioCapture](Web-api#rtcengine-stopaudiocapture) | 立即关闭内部音频采集。默认为关闭状态。<br>内部采集是指：使用 RTC SDK 内置采集机制进行音频采集。<br>调用该方法，房间内的其他用户会收到 [onUserStopAudioCapture](Web-event.md#onuserstopaudiocapture) 的回调。 |
| [startScreenCapture](Web-api.md#rtcengine-startscreencapture) | 使用内部采集模块，采集当前屏幕视频流，用于共享。 |
| [stopScreenCapture](Web-api.md#rtcengine-stopscreencapture) | 停止屏幕共享流内部采集。 |
| [setLocalVideoPlayer](Web-api.md#rtcengine-setlocalvideoplayer) | 设置本地视频渲染时，使用的视图，并设置渲染模式。<br>调用本方法绑定视图以后，你可以通过 `onPlayerEvent` 来监听播放状态。<br>你可以通过再次调用本方法，并绑定空视图来解除绑定。 |
| [setRemoteVideoPlayer](Web-api#rtcengine-setremotevideoplayer) | 设置远端视频渲染时使用的视图，并设置渲染模式。<br>建议在收到 [onUserPublishStream](Web-event.md#onuserpublishstream)/[onUserPublishScreen](Web-event.md#onuserpublishscreen) 事件后，调用本方法对远端视频视图进行设置。<br>你可以通过再次调用本方法，并绑定空视图来解除绑定。 |
| [setLocalVideoMirrorType](Web-api.md#rtcengine-setlocalvideomirrortype) | 是否开启本地视频流镜像模式。 |
| [setAudioPlaybackDevice](Web-api.md#rtcengine-setaudioplaybackdevice) | 设置音频播放设备，例如扬声器或者耳机，默认使用扬声器。 |
| [play](Web-api.md#rtcengine-play) | 手动开启音视频流播放 |
| [pauseAllSubscribedStream](Web-api.md#rtcengine-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Web-api.md#rtcengine-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [sendUserMessage](Web-api#rtcengine-sendusermessage) | 给房间内指定的用户发送点对点文本消息。<br>若消息发送成功，则 userId 所指定的用户会收到 [onUserMessageReceived](Web-event.md#onusermessagereceived) 回调。 |
| [sendUserBinaryMessage](Web-api#rtcengine-senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息。<br>若消息发送成功，则 userId 所指定的用户会收到 [onUserBinaryMessageReceived](Web-event.md#onuserbinarymessagereceived) 回调。 |
| [sendRoomMessage](Web-api#rtcengine-sendroommessage) | 给房间内的所有其他用户群发文本消息。<br>若消息发送成功，同一房间内的其他用户会收到 [onRoomMessageReceived](Web-event.md#onroommessagereceived) 回调。 |
| [sendRoomBinaryMessage](Web-api#rtcengine-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。<br>若消息发送成功，同一房间内的其他用户会收到通过 [onRoomBinaryMessageReceived](Web-event.md#onroombinarymessagereceived) 回调发送的消息 |
| [sendSEIMessage](Web-api.md#rtcengine-sendseimessage) | 在视频通信时，通过视频帧发送 SEI 数据。 |
| [setVideoEncoderConfig](Web-api.md#rtcengine-setvideoencoderconfig) | 在视频发布端设置发布的视频流参数。 |
| [setScreenEncoderConfig](Web-api#rtcengine-setscreenencoderconfig) | 设置共享屏幕的视频编码参数，同时对视频采集生效。<br>若设置的参数浏览器不支持，RTC SDK 按照浏览器支持的参数范围进行采集和编码，并通过回调 [onLocalVideoSizeChanged](Web-event.md#onlocalvideosizechanged) 通知采集的实际参数。 |
| [setRemoteVideoConfig](Web-api.md#rtcengine-setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [enableSimulcastMode](Web-api.md#rtcengine-enablesimulcastmode) | 在视频发布端设置摄像头视频流的大小流模式 |
| [enableAudioPropertiesReport](Web-api.md#rtcengine-enableaudiopropertiesreport) | 启用音频信息提示。 |
| [startLiveTranscoding](Web-api.md#rtcengine-startlivetranscoding) | 开启转推直播，并设置合流的视频视图布局和音频属性。 |
| [updateLiveTranscoding](Web-api.md#rtcengine-updatelivetranscoding) | 更新转推直播参数。<br>使用 [startLiveTranscoding](Web-api.md#startlivetranscoding) 启用转推直播功能后，使用此方法更新功能配置参数。 |
| [stopLiveTranscoding](Web-api.md#rtcengine-stoplivetranscoding) | 停止转推直播。<br>关于启动转推直播，参看 [startLiveTranscoding](Web-api.md#startlivetranscoding)。 |
| [setBusinessId](Web-api.md#rtcengine-setbusinessid) | 设置业务标识参数<br>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setUserVisibility](Web-api.md#rtcengine-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。 |
| [setExternalVideoTrack](Web-api.md#rtcengine-setexternalvideotrack) | 使用用户自定义的 videoTrack。<br>调用本方法前必须先调用 [setVideoSourceType](Web-api.md#setvideosourcetype) 设置为自定义视频采集。 |
| [setExternalAudioTrack](Web-api.md#rtcengine-setexternalaudiotrack) | 使用用户自定义的 audioTrack。<br>调用本方法前必须先调用 [setAudioSourceType](Web-api.md#setaudiosourcetype) 设置为自定义音频采集。 |
| [setVideoSourceType](Web-api.md#rtcengine-setvideosourcetype) | 设置向 SDK 输入的视频源<br>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。<br>该方法进房前后均可调用。<br>当你已调用 [startVideoCapture](Web-api.md#startvideocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。<br>当你调用此方法开启自定义采集，再调用此方法切换至内部采集时，必须再调用 [startVideoCapture](Web-api.md#startvideocapture) 手动开启内部采集。 |
| [setAudioSourceType](Web-api.md#rtcengine-setaudiosourcetype) | 设置向 SDK 输入的音频源<br>默认使用内部采集。内部采集指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br>该方法进房前后均可调用。<br>当你已调用 [startAudioCapture](Web-api.md#startaudiocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。<br>当你调用此方法开启自定义采集，再调用此方法切换至内部采集时，必须再调用 [startAudioCapture](Web-api.md#startaudiocapture) 手动开启内部采集。 |
| [getAudioMixingManager](Web-api.md#rtcengine-getaudiomixingmanager) | 混音管理接口创建 |
| [setAudioCaptureConfig](Web-api.md#rtcengine-setaudiocaptureconfig) | 设置 RTC SDK 内部采集时的音频采集参数。默认参数由浏览器决定。 |
| [login](Web-api.md#rtcengine-login) | 登录即时消息服务器。<br>调用此方法登录后，可以向同 `appID` 下其他已登陆用户发送文本或二进制消息。 |
| [logout](Web-api.md#rtcengine-logout) | 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken](Web-api.md#rtcengine-updatelogintoken) | 更新用户用于登录的 Token。Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。 |
| [getPeerOnlineStatus](Web-api.md#rtcengine-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态。在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。 |
| [sendUserMessageOutsideRoom](Web-api.md#rtcengine-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom](Web-api.md#rtcengine-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [setServerParams](Web-api.md#rtcengine-setserverparams) | 设置业务服务器参数。调用 [sendServerMessage](Web-api.md#sendservermessage) 或 [sendServerBinaryMessage](Web-api.md#sendserverbinarymessage) 发送消息给业务服务器之前，必须需要设置有效签名和业务服务器地址。 |
| [sendServerMessage](Web-api.md#rtcengine-sendservermessage) | 客户端给业务服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Web-api.md#rtcengine-sendserverbinarymessage) | 客户端给业务服务器发送二进制消息（P2Server） |
| [startCloudProxy](Web-api.md#rtcengine-startcloudproxy) | 开启云代理 |
| [stopCloudProxy](Web-api.md#rtcengine-stopcloudproxy) | 关闭云代理 |
| [startPushPublicStream](Web-api.md#rtcengine-startpushpublicstream) | 发布一路公共流。 |
| [updatePublicStreamParam](Web-api.md#rtcengine-updatepublicstreamparam) | 更新公共流参数。<br>调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布一路公共流。 |
| [stopPushPublicStream](Web-api.md#rtcengine-stoppushpublicstream) | 停止发布公共流。<br>调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布一路公共流。 |
| [startPlayPublicStream](Web-api.md#rtcengine-startplaypublicstream) | 订阅指定公共流。<br>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream](Web-api.md#rtcengine-stopplaypublicstream) | 取消订阅指定公共流。<br>关于订阅公共流，查看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。 |
| [setPublicStreamVideoPlayer](Web-api.md#rtcengine-setpublicstreamvideoplayer) | 为指定公共流设置使用的视图和渲染模式。 |
| [setDummyCaptureImagePath](Web-api.md#rtcengine-setdummycaptureimagepath) | 停止内部摄像头采集时，使用静态图片填充本地推送的视频流。 |
| [defaultTranscoding](Web-api.md#rtcengine-defaulttranscoding) | 获取合流转推默认参数。 |
| [setSubscribeFallbackOption](Web-api.md#rtcengine-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。<br>回退指：设置网络不佳时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority](Web-api.md#rtcengine-setremoteuserpriority) | 设置用户优先级。<br>该方法与 [setSubscribeFallbackOption](Web-api.md#setsubscribefallbackoption) 搭配使用。<br>开启回退后，会优先保证收到的高优先级用户的流的质量。 |
| [startAudioPlaybackDeviceTest](Web-api#rtcengine-startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 [onAudioPlaybackDeviceTestVolume](Web-event.md#onaudioplaybackdevicetestvolume) 回调播放时的音量信息。 |
| [stopAudioPlaybackDeviceTest](Web-api.md#rtcengine-stopaudioplaybackdevicetest) | 停止音频播放设备测试。 |
| [startAudioDeviceRecordTest](Web-api#rtcengine-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br>建议提前调用 [enableAudioPropertiesReport](Web-api#enableaudiopropertiesreport) 注册音量提示回调，测试开始后，音频设备开始采集本地声音，可以通过 [onLocalAudioPropertiesReport](Web-event.md#onlocalaudiopropertiesreport) 获取采集音量。 |
| [stopAudioDeviceRecordAndPlayTest](Web-api.md#rtcengine-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>调用 [startAudioDeviceRecordTest](Web-api.md#startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
| [stopAudioDevicePlayTest](Web-api.md#rtcengine-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Web-api.md#startaudiodevicerecordtest) 开始的音频播放设备测试。<br>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |
| [setAudioProfile](Web-api.md#rtcengine-setaudioprofile) | 设置音质档位 |
| [getLocalStreamTrack](Web-api.md#rtcengine-getlocalstreamtrack) | 获取本地用户的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
| [getRemoteStreamTrack](Web-api.md#rtcengine-getremotestreamtrack) | 获取已订阅的远端用户的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
| [getPublicStreamTrack](Web-api.md#rtcengine-getpublicstreamtrack) | 获取已订阅的公共流的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
| [takeLocalSnapshot](Web-api.md#rtcengine-takelocalsnapshot) | 截取本地视频画面 |
| [takeRemoteSnapshot](Web-api.md#rtcengine-takeremotesnapshot) | 截取远端视频画面 |
| [registerExtension](Web-api.md#rtcengine-registerextension) | 注册插件。 |
| [startSubtitle](Web-api#rtcengine-startsubtitle) | 开启字幕。<br>调用该方法后，你可以根据需要选择识别和翻译两种模式。开启识别模式，会将识别后的用户语音转化成文字；开启翻译模式，会在语音识别后进行翻译。语音识别或翻译的结果会通过 [onSubtitleMessageReceived](Web-event.md#onsubtitlemessagereceived) 事件回调给你。<br>调用该方法后，你会收到 [onSubtitleStateChanged](Web-event.md#onsubtitlestatechanged) 回调，通知字幕是否开启。 |
| [stopSubtitle](Web-api#rtcengine-stopsubtitle) | 关闭字幕。<br>调用该方法后，你会收到 [onSubtitleStateChanged](Web-event.md#onsubtitlestatechanged) 回调，通知字幕是否关闭。 |
| [setRemoteStreamRenderSync](Web-api.md#rtcengine-setremotestreamrendersync) | 设置远端音视频流是否同步渲染。<br>你可以通过关闭音视频同步，达到超低端到端延时的效果。 |
| [setCaptureVolume](Web-api.md#rtcengine-setcapturevolume) | 调节音频采集音量。 |
| [setPlaybackVolume](Web-api.md#rtcengine-setplaybackvolume) | 调节本地播放的单个远端用户的音量。 |
| [setPublicStreamVolume](Web-api.md#rtcengine-setpublicstreamvolume) | 调节本地播放的公共流播放音量。 |



## VERTC

| 方法 | 描述 |
| :-- | :-- |
| [createEngine](Web-api.md#vertc-createengine) | 创建引擎对象。<br>你必须先使用此方法，以使用 RTC 提供的各种音视频能力。<br>再次调用此方法时，会创建另一个独立的引擎实例。 |
| [destroyEngine](Web-api.md#vertc-destroyengine) | 手动销毁通过 [createEngine](Web-api.md#createengine) 所创建的引擎对象。 |
| [getSdkVersion](Web-api.md#vertc-getsdkversion) | 获取 SDK 当前的版本号。 |
| [enumerateDevices](Web-api.md#vertc-enumeratedevices) | 枚举可用的媒体输入和输出设备，比如麦克风、摄像头、耳机等。<br>可以通过该方法获取设备的 deviceId, 用于在 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice)、[startVideoCapture](Web-api.md#startvideocapture)、[startAudioCapture](Web-api.md#startaudiocapture) 方法中指定采集/播放设备。 |
| [enableDevices](Web-api.md#vertc-enabledevices) | 向用户获取设备权限 |
| [enumerateAudioCaptureDevices](Web-api.md#vertc-enumerateaudiocapturedevices) | 该方法枚举可用的麦克风。<br>可以通过该方法获取设备的 `deviceId`, 用于在 [startAudioCapture](Web-api.md#startaudiocapture)、[setAudioCaptureDevice](Web-api.md#setaudiocapturedevice) 方法中指定使用的麦克风设备。 |
| [enumerateVideoCaptureDevices](Web-api.md#vertc-enumeratevideocapturedevices) | 该方法枚举可用的摄像头等。<br>可以通过该方法获取设备的 deviceId, 用于在 [startVideoCapture](Web-api.md#startvideocapture)、[setVideoCaptureDevice](Web-api.md#setvideocapturedevice) 方法中指定使用的摄像头设备。 |
| [enumerateAudioPlaybackDevices](Web-api.md#vertc-enumerateaudioplaybackdevices) | 该方法枚举可用的音频播放设备，例如耳机、音箱等。<br>可以通过该方法获取设备的 deviceId, 可用于 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice) 方法中指定音频播放设备。 |
| [isSupported](Web-api.md#vertc-issupported) | 浏览器是否支持 |
| [getSupportedCodecs](Web-api.md#vertc-getsupportedcodecs) | 获取当前浏览器支持的编解码类型。<br>若你已开通 vp8 业务，可以在进房前调用该接口查看当前浏览器是否支持 vp8 编码类型 |
| [setLogConfig](Web-api.md#vertc-setlogconfig) | 配置本地缓存的日志级别, 以及可使用的最大缓存空间。 |
| [downloadLog](Web-api.md#vertc-downloadlog) | 下载本地缓存生成文件。 |



## AudioMixingManager

| 方法 | 描述 |
| :-- | :-- |
| [startAudioMixing](Web-api.md#audiomixingmanager-startaudiomixing) | 开启混音 |
| [stopAudioMixing](Web-api.md#audiomixingmanager-stopaudiomixing) | 停止播放音频文件 |
| [pauseAudioMixing](Web-api.md#audiomixingmanager-pauseaudiomixing) | 暂停播放音频文件 |
| [resumeAudioMixing](Web-api.md#audiomixingmanager-resumeaudiomixing) | 恢复播放音频文件 |
| [preloadAudioMixing](Web-api.md#audiomixingmanager-preloadaudiomixing) | 预加载指定音频文件到内存中 |
| [unloadAudioMixing](Web-api.md#audiomixingmanager-unloadaudiomixing) | 卸载指定音频文件 |
| [setAudioMixingVolume](Web-api.md#audiomixingmanager-setaudiomixingvolume) | 调节混音的音量大小，包括音频文件混音和 PCM 混音。 |
| [getAudioMixingVolume](Web-api.md#audiomixingmanager-getaudiomixingvolume) | 获取音频文件的音量 |
| [getAudioMixingDuration](Web-api.md#audiomixingmanager-getaudiomixingduration) | 获取音频文件时长 |
| [getAudioMixingCurrentPosition](Web-api.md#audiomixingmanager-getaudiomixingcurrentposition) | 获取音频文件播放进度 |
| [setAudioMixingPosition](Web-api.md#audiomixingmanager-setaudiomixingposition) | 设置音频文件的起始播放位置 |
| [enableAudioMixingBuffer](Web-api.md#audiomixingmanager-enableaudiomixingbuffer) | 启动 PCM 音频数据混音 |
| [disableAudioMixingBuffer](Web-api.md#audiomixingmanager-disableaudiomixingbuffer) | 关闭 PCM 混音 |
| [pushAudioMixingBuffer](Web-api.md#audiomixingmanager-pushaudiomixingbuffer) | 推送 PCM 音频数据用于混音 |



## EngineEvents

| 方法 | 描述 |
| :-- | :-- |
| [onPlayerEvent](Web-event.md#engineevents-onplayerevent) | 播放器事件 |
| [onUserJoined](Web-event.md#engineevents-onuserjoined) | 远端可见用户加入房间，或房内隐身用户切换为可见的回调 |
| [onUserLeave](Web-event.md#engineevents-onuserleave) | 远端可见用户离开房间，或房内可见用户切换为隐身的回调 |
| [onConnectionStateChanged](Web-event.md#engineevents-onconnectionstatechanged) | 连接状态发生变化 |
| [onUserPublishStream](Web-event.md#engineevents-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集音视频流的回调。 |
| [onUserUnpublishStream](Web-event.md#engineevents-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onUserPublishScreen](Web-event.md#engineevents-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](Web-event.md#engineevents-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onRemoteVideoFirstFrame](Web-event.md#engineevents-onremotevideofirstframe) | 视频首帧解码 |
| [onRemoteAudioFirstFrame](Web-event.md#engineevents-onremoteaudiofirstframe) | 远端音频首帧播放事件 |
| [onVideoDeviceStateChanged](Web-event.md#engineevents-onvideodevicestatechanged) | 视频媒体设备状态改变。 |
| [onAudioDeviceStateChanged](Web-event.md#engineevents-onaudiodevicestatechanged) | 音频媒体设备状态改变。 |
| [onAutoplayFailed](Web-event.md#engineevents-onautoplayfailed) | 自动播放失败 |
| [onTrackEnded](Web-event.md#engineevents-ontrackended) | 断流事件 |
| [onRoomMessageReceived](Web-event.md#engineevents-onroommessagereceived) | 接收到房间内广播消息的事件。 |
| [onRoomBinaryMessageReceived](Web-event.md#engineevents-onroombinarymessagereceived) | 接收到房间内二进制广播消息的事件。 |
| [onUserMessageReceived](Web-event#engineevents-onusermessagereceived) | 收到来自房间中其他用户通过 [sendUserMessage](Web-api.md#sendusermessage) 发来的点对点文本消息时，会收到此事件 |
| [onUserBinaryMessageReceived](Web-event.md#engineevents-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 sendUserBinaryMessage 发来的点对点二进制消息时，会收到此事件 |
| [onRemoteStreamStats](Web-event.md#engineevents-onremotestreamstats) | 用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s |
| [onLocalStreamStats](Web-event.md#engineevents-onlocalstreamstats) | 本地音/视频流统计信息以及网络状况，统计周期为 2s |
| [onPublicStreamStats](Web-event#engineevents-onpublicstreamstats) | 调用 [startPlayPublicStream](Web-api.md#startplaypublicstream) 订阅公共流，后将触发此回调，周期为 2s，包含各项统计信息。 |
| [onLocalAudioPropertiesReport](Web-event#engineevents-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。<br>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。 |
| [onRemoteAudioPropertiesReport](Web-event#engineevents-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport)，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onActiveSpeaker](Web-event#engineevents-onactivespeaker) | 成功调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport) 后，当房间内用户数量大于或等于 2 且有活跃用户时，你会周期性收到此回调，获取房间内音量最大用户的信息。 |
| [onAudioPlaybackDeviceChanged](Web-event#engineevents-onaudioplaybackdevicechanged) | 当调用 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice) 设置音频播放设备时，会收到此事件。 |
| [onUserStartAudioCapture](Web-event#engineevents-onuserstartaudiocapture) | 房间内的可见用户调用 [startAudioCapture](Web-api.md#startaudiocapture) 开启音频采集时，房间内其他用户会收到此事件。 |
| [onUserStopAudioCapture](Web-event#engineevents-onuserstopaudiocapture) | 房间内的可见用户调用 [stopAudioCapture](Web-api.md#stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此事件。 |
| [onUserStartVideoCapture](Web-event#engineevents-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Web-api.md#startvideocapture) 开启内部视频采集时，房间内其他用户会收到此事件。 |
| [onUserStopVideoCapture](Web-event#engineevents-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Web-api.md#stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此事件。 |
| [onSEIMessageReceived](Web-event.md#engineevents-onseimessagereceived) | 接收到包含 SEI 数据的视频帧事件 |
| [onAutoSubscribeResult](Web-event.md#engineevents-onautosubscriberesult) | 如果开启了自动订阅，订阅成功或者失败后可以收到此事件 |
| [onAutoPublishResult](Web-event.md#engineevents-onautopublishresult) | 如果开启了自动发布，发布成功或者失败后可以收到此事件 |
| [onAutoplayFailed](Web-event.md#engineevents-onautoplayfailed) | 自动播放失败 |
| [onError](Web-event.md#engineevents-onerror) | 当 SDK 内部发生不可逆转错误时触发该回调 |
| [onAudioMixingStateChanged](Web-event.md#engineevents-onaudiomixingstatechanged) | 音频混音文件播放状态改变事件 |
| [onUserMessageReceivedOutsideRoom](Web-event.md#engineevents-onusermessagereceivedoutsideroom) | 接收到房间外消息的事件。 |
| [onUserBinaryMessageReceivedOutsideRoom](Web-event.md#engineevents-onuserbinarymessagereceivedoutsideroom) | 接收到房间外二进制消息的事件。 |
| [onTokenWillExpire](Web-event#engineevents-ontokenwillexpire) | Token 过期前 30 秒将触发该回调。<br>调用 [updateToken](Web-api.md#updatetoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。 |
| [onCloudProxyConnected](Web-event#engineevents-oncloudproxyconnected) | 调用 [startCloudProxy](Web-api.md#startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onPushPublicStreamResult](Web-event#engineevents-onpushpublicstreamresult) | 公共流发布结果回调。<br>调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布公共流后，结果通过此回调通知用户。 |
| [onPublicStreamSEIMessageReceived](Web-event#engineevents-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br>调用 [startPlayPublicStream](Web-api.md#startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [onFirstPublicStreamVideoFrameDecoded](Web-event#engineevents-onfirstpublicstreamvideoframedecoded) | 公共流的视频首帧解码成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。 |
| [onFirstPublicStreamAudioFrameDecoded](Web-event#engineevents-onfirstpublicstreamaudioframedecoded) | 公共流的音频首帧解码成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。 |
| [onFirstPublicStreamVideoFrameRendered](Web-event#engineevents-onfirstpublicstreamvideoframerendered) | 公共流的首帧视频渲染成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。 |
| [onAudioPlaybackDeviceTestVolume](Web-event.md#engineevents-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onNetworkQuality](Web-event.md#engineevents-onnetworkquality) | 加入房间后，会以每2秒一次的频率，收到本端上行及下行的网络质量信息。 |
| [onSimulcastSubscribeFallback](Web-event.md#engineevents-onsimulcastsubscribefallback) | 订阅的视频流发生回退，或从回退中恢复时，收到此回调。 |
| [onRemoteVideoSizeChanged](Web-event.md#engineevents-onremotevideosizechanged) | 远端视频分辨率发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onStreamMixingEvent](Web-event.md#engineevents-onstreammixingevent) | 转推直播相关事件 |
| [onVideoStreamBanned](Web-event.md#engineevents-onvideostreambanned) | 调用服务端接口 BanUserStream/UnbanUserStream 封禁/解禁指定用户的视频流发布时，触发该回调。 |
| [onAudioStreamBanned](Web-event.md#engineevents-onaudiostreambanned) | 调用服务端接口 BanUserStream/UnbanUserStream 封禁/解禁指定用户的音频流发布时，触发该回调。 |
| [onLocalVideoSizeChanged](Web-event.md#engineevents-onlocalvideosizechanged) | 当实际采集的参数与设置的编码参数不一致时，SDK 会触发该回调返回实际采集视频的参数。 |
| [onSubtitleStateChanged](Web-event#engineevents-onsubtitlestatechanged) | 字幕状态发生改变回调。<br>当你调用 [startSubtitle](Web-api.md#startsubtitle) 和 [stopSubtitle](Web-api.md#stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。 |
| [onSubtitleMessageReceived](Web-event#engineevents-onsubtitlemessagereceived) | 字幕相关信息回调。<br>当你成功调用 [startSubtitle](Web-api.md#startsubtitle) 后会收到此回调，通知字幕的相关信息。 |
| [onServerParamsSetResult](Web-event.md#engineevents-onserverparamssetresult) | 设置接收客户端即时消息的服务器成功或失败时收到本事件。 |