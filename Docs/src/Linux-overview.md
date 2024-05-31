# 方法
## 引擎管理

| 方法 | 描述 |
| --- | --- |
| [createRTCVideo](Linux-api.md#creatertcvideo) | 创建 IRTCVideo 实例。  <br><br/>如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br><br/>如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。 |
| [destroyRTCVideo](Linux-api.md#destroyrtcvideo) | 销毁由 [createRTCVideo](Linux-api.md#creatertcvideo) 创建的 IRTCVideo 实例，并释放所有相关资源。 |
| [getSDKVersion](Linux-api.md#getsdkversion) | 获取当前 SDK 版本信息。 |
| [feedback](Linux-api.md#IRTCVideo-feedback) | 将用户反馈的问题上报到 RTC |
| [getErrorDescription](Linux-api.md#geterrordescription) | 获取错误码的描述 |
| [setBusinessId](Linux-api.md#IRTCVideo-setbusinessid) | 设置业务标识参数  <br><br/>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setRuntimeParameters](Linux-api.md#IRTCVideo-setruntimeparameters) | 设置运行时的参数 |

## 房间管理

| 方法 | 描述 |
| --- | --- |
| [createRTCRoom](Linux-api.md#IRTCVideo-creatertcroom) | 创建房间实例。<br/>调用此方法仅返回一个房间实例，你仍需调用 [joinRoom](Linux-api.md#IRTCRoom-joinroom) 才能真正地创建/加入房间。<br/>多次调用此方法以创建多个 [IRTCRoom](Linux-api.md#irtcroom) 实例。分别调用各 IRTCRoom 实例中的 [joinRoom](Linux-api.md#IRTCRoom-joinroom) 方法，同时加入多个房间。<br/>多房间模式下，用户可以同时订阅各房间的音视频流。 |
| [destroy](Linux-api.md#IRTCRoom-destroy) | 退出并销毁调用 [createRTCRoom](Linux-api.md#IRTCVideo-creatertcroom) 所创建的房间实例。 |
| [setRTCRoomEventHandler](Linux-api.md#IRTCRoom-setrtcroomeventhandler) | 通过设置 [IRTCRoom](Linux-api.md#irtcroom) 对象的事件句柄，监听此对象对应的回调事件。 |
| [joinRoom](Linux-api.md#IRTCRoom-joinroom) | 创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br><br/>同一房间内的用户间可以相互通话。  <br> |
| [leaveRoom](Linux-api.md#IRTCRoom-leaveroom) | 离开房间。  <br><br/>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br><br/>加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br><br/>此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 [onLeaveRoom](Linux-callback.md#IRTCRoomEventHandler-onleaveroom) 回调通知。  <br> |
| [setUserVisibility](Linux-api.md#IRTCRoom-setuservisibility) | 设置用户可见性。默认可见。  <br> |
| [updateToken](Linux-api.md#IRTCRoom-updatetoken) | 更新 Token。<br>在 Token 进房权限过期前 30 秒，会收到 [onTokenWillExpire](Linux-callback.md#IRTCRoomEventHandler-ontokenwillexpire) 回调，此时需要重新获取 Token，并调用此方法更新 Token，否则用户将因为 Token 过期被移出房间。 |

## 音频管理

| 方法 | 描述 |
| --- | --- |
| [buildAudioFrame](Linux-api.md#buildaudioframe) | 创建 IAudioFrame |
| [enumerateAudioPlaybackDevices](Linux-api.md#IAudioDeviceManager-enumerateaudioplaybackdevices) | 获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 `onAudioMediaDeviceStateChanged` 回调通知，然后需要重新调用本接口以获得新的设备列表。 |
| [enumerateAudioCaptureDevices](Linux-api.md#IAudioDeviceManager-enumerateaudiocapturedevices) | 获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。 |
| [setAudioPlaybackDevice](Linux-api.md#IAudioDeviceManager-setaudioplaybackdevice) | 设置音频播放设备。 |
| [setAudioCaptureDevice](Linux-api.md#IAudioDeviceManager-setaudiocapturedevice) | 设置音频采集设备。 |
| [getAudioPlaybackDevice](Linux-api.md#IAudioDeviceManager-getaudioplaybackdevice) | 获取当前音频播放设备 ID。 |
| [getAudioCaptureDevice](Linux-api.md#IAudioDeviceManager-getaudiocapturedevice) | 获取当前音频采集设备 ID。 |
| [followSystemPlaybackDevice](Linux-api.md#IAudioDeviceManager-followsystemplaybackdevice) | 设置音频播放路由是否跟随系统。 |
| [followSystemCaptureDevice](Linux-api.md#IAudioDeviceManager-followsystemcapturedevice) | 设置音频采集路由是否跟随系统。 |
| [setAudioPlaybackDeviceVolume](Linux-api.md#IAudioDeviceManager-setaudioplaybackdevicevolume) | 设置当前音频播放设备音量 |
| [getAudioPlaybackDeviceVolume](Linux-api.md#IAudioDeviceManager-getaudioplaybackdevicevolume) | 获取当前音频播放设备音量 |
| [setAudioCaptureDeviceVolume](Linux-api.md#IAudioDeviceManager-setaudiocapturedevicevolume) | 设置当前音频采集设备音量 |
| [getAudioCaptureDeviceVolume](Linux-api.md#IAudioDeviceManager-getaudiocapturedevicevolume) | 获取当前音频采集设备音量 |
| [setAudioPlaybackDeviceMute](Linux-api.md#IAudioDeviceManager-setaudioplaybackdevicemute) | 设置当前音频播放设备静音状态，默认为非静音。 |
| [getAudioPlaybackDeviceMute](Linux-api.md#IAudioDeviceManager-getaudioplaybackdevicemute) | 获取当前音频播放设备是否静音的信息。 |
| [setAudioCaptureDeviceMute](Linux-api.md#IAudioDeviceManager-setaudiocapturedevicemute) | 设置当前音频采集设备静音状态，默认为非静音。 |
| [getAudioCaptureDeviceMute](Linux-api.md#IAudioDeviceManager-getaudiocapturedevicemute) | 获取当前音频采集设备是否静音的信息。 |
| [setCaptureVolume](Linux-api.md#IRTCVideo-setcapturevolume) | 调节音频采集音量 |
| [setPlaybackVolume](Linux-api.md#IRTCVideo-setplaybackvolume) | 调节本地播放的所有远端用户混音后的音量。播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume](Linux-api.md#IRTCVideo-setremoteaudioplaybackvolume) | 调节来自远端用户的音频播放音量 |
| [startAudioCapture](Linux-api.md#IRTCVideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。<br/>调用该方法开启后，本地用户会收到 [onAudioDeviceStateChanged](Linux-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。 <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Linux-callback.md#IRTCVideoEventHandler-onuserstartaudiocapture) 的回调。 |
| [stopAudioCapture](Linux-api.md#IRTCVideo-stopaudiocapture) | 立即关闭内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。<br/>调用该方法，本地用户会收到 [onAudioDeviceStateChanged](Linux-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法后，房间中的其他用户会收到 [onUserStopAudioCapture](Linux-callback.md#IRTCVideoEventHandler-onuserstopaudiocapture) 的回调。 |
| [enableAudioPropertiesReport](Linux-api.md#IRTCVideo-enableaudiopropertiesreport) | 启用音频信息提示。  <br> |
| [setAudioProfile](Linux-api.md#IRTCVideo-setaudioprofile) | 设置音质档位。当所选的 [RoomProfileType](Linux-keytype.md#roomprofiletype) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。 |
| [getAudioDeviceManager](Linux-api.md#IRTCVideo-getaudiodevicemanager) | 设备音频管理接口创建 |
| [startAudioDeviceRecordTest](Linux-api.md#IAudioDeviceManager-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br><br/>建议提前调用 `enableAudioPropertiesReport` 启用音频信息提示，测试开始后，音频设备开始采集本地声音，可以通过 `onLocalAudioPropertiesReport` 获取采集音量。<br> |
| [stopAudioDeviceRecordAndPlayTest](Linux-api.md#IAudioDeviceManager-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br><br/>调用 [startAudioDeviceRecordTest](Linux-api.md#IAudioDeviceManager-startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
| [stopAudioDevicePlayTest](Linux-api.md#IAudioDeviceManager-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Linux-api.md#IAudioDeviceManager-startaudiodevicerecordtest) 开始的音频播放设备测试。<br><br/>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |
| [enableExternalSoundCard](Linux-api.md#IRTCVideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |

## 视频管理

| 方法 | 描述 |
| --- | --- |
| [startVideoCapture](Linux-api.md#IRTCVideo-startvideocapture) | 立即开启内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Linux-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 [onUserStartVideoCapture](Linux-callback.md#IRTCVideoEventHandler-onuserstartvideocapture) 的回调。 |
| [stopVideoCapture](Linux-api.md#IRTCVideo-stopvideocapture) | 立即关闭内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Linux-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Linux-callback.md#IRTCVideoEventHandler-onuserstopvideocapture) 的回调。 |
| [setVideoCaptureConfig](Linux-api.md#IRTCVideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。<br><br/>如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数，包括模式、分辨率、帧率。 |
| [setLocalVideoCanvas](Linux-api.md#IRTCVideo-setlocalvideocanvas) | 设置本地视频渲染时，使用的视图，并设置渲染模式。 |
| [updateLocalVideoCanvas](Linux-api.md#IRTCVideo-updatelocalvideocanvas) | 修改本地视频渲染模式和背景色。 |
| [setRemoteStreamVideoCanvas](Linux-api.md#IRTCVideo-setremotestreamvideocanvas) | 设置渲染指定视频流 `stream_key` 时，使用的视图和渲染模式。 <br><br/>如果需要解除某个用户的绑定视图，你可以把 `canvas` 设置为空。 |
| [updateRemoteStreamVideoCanvas](Linux-api.md#IRTCVideo-updateremotestreamvideocanvas) | 修改远端视频渲染模式和背景色。 |
| [registerFaceDetectionObserver](Linux-api.md#IVideoEffect-registerfacedetectionobserver) | 注册人脸检测结果回调观察者 <br><br/>注册此观察者后，你会周期性收到 [onFaceDetectResult](Linux-callback.md#IFaceDetectionObserver-onfacedetectresult) 回调。 |
| [enumerateVideoCaptureDevices](Linux-api.md#IVideoDeviceManager-enumeratevideocapturedevices) | 获取当前系统内视频采集设备列表。 |
| [setVideoCaptureDevice](Linux-api.md#IVideoDeviceManager-setvideocapturedevice) | 设置当前视频采集设备 |
| [getVideoCaptureDevice](Linux-api.md#IVideoDeviceManager-getvideocapturedevice) | 获取当前 SDK 正在使用的视频采集设备信息 |
| [getVideoDeviceManager](Linux-api.md#IRTCVideo-getvideodevicemanager) | 创建视频设备管理实例 |
| [buildVideoFrame](Linux-api.md#buildvideoframe) | 创建 IVideoFrame |
| [setVideoEncoderConfig](Linux-api.md#IRTCVideo-setvideoencoderconfig) | <span id="IRTCVideo-setvideoencoderconfig-1"></span><br/>视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br><br/>该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2)。 |
| [setVideoEncoderConfig](Linux-api.md#IRTCVideo-setvideoencoderconfig) | <span id="IRTCVideo-setvideoencoderconfig-2"></span><br/>视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |

## 音视频传输

| 方法 | 描述 |
| --- | --- |
| [publishStream](Linux-api.md#IRTCRoom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream](Linux-api.md#IRTCRoom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [subscribeStream](Linux-api.md#IRTCRoom-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream](Linux-api.md#IRTCRoom-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreams](Linux-api.md#IRTCRoom-subscribeallstreams) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreams](Linux-api.md#IRTCRoom-unsubscribeallstreams) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br><br/>自动订阅和手动订阅的流都可以通过本方法取消订阅。 |
| [requestRemoteVideoKeyFrame](Linux-api.md#IRTCVideo-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [startForwardStreamToRooms](Linux-api.md#IRTCRoom-startforwardstreamtorooms) | 开始跨房间转发媒体流。<br/>在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br> |
| [stopForwardStreamToRooms](Linux-api.md#IRTCRoom-stopforwardstreamtorooms) | 停止跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Linux-api.md#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。 |
| [updateForwardStreamToRooms](Linux-api.md#IRTCRoom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br><br/>通过 [startForwardStreamToRooms](Linux-api.md#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br/>调用本方法增加或删减房间后，将在本端触发 [onForwardStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。 |
| [pauseForwardStreamToAllRooms](Linux-api.md#IRTCRoom-pauseforwardstreamtoallrooms) | 暂停跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Linux-api.md#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br/>调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](Linux-api.md#IRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。 |
| [resumeForwardStreamToAllRooms](Linux-api.md#IRTCRoom-resumeforwardstreamtoallrooms) | 恢复跨房间媒体流转发。<br/>调用 [pauseForwardStreamToAllRooms](Linux-api.md#IRTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。 |
| [pauseAllSubscribedStream](Linux-api.md#IRTCRoom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Linux-api.md#IRTCRoom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [setMultiDeviceAVSync](Linux-api.md#IRTCRoom-setmultideviceavsync) | 设置发流端音画同步。  <br><br/>当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。 |
| [startPushPublicStream](Linux-api.md#IRTCVideo-startpushpublicstream) | 发布一路公共流<br><br/>用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream](Linux-api.md#IRTCVideo-startplaypublicstream) 获取和播放指定的公共流。 |
| [stopPushPublicStream](Linux-api.md#IRTCVideo-stoppushpublicstream) | 停止发布当前用户发布的公共流<br><br/>关于发布公共流，查看 [startPushPublicStream](Linux-api.md#IRTCVideo-startpushpublicstream)。 |
| [updatePublicStreamParam](Linux-api.md#IRTCVideo-updatepublicstreamparam) | 更新公共流参数<br><br/>关于发布公共流，查看 [startPushPublicStream](Linux-api.md#IRTCVideo-startpushpublicstream)。 |
| [startPlayPublicStream](Linux-api.md#IRTCVideo-startplaypublicstream) | 订阅指定公共流<br><br/>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream](Linux-api.md#IRTCVideo-stopplaypublicstream) | 取消订阅指定公共流<br><br/>关于订阅公共流，查看 [startPlayPublicStream](Linux-api.md#IRTCVideo-startplaypublicstream)。 |
| [setPublicStreamVideoCanvas](Linux-api.md#IRTCVideo-setpublicstreamvideocanvas) | 为指定公共流绑定内部渲染视图 |
| [setPublicStreamVideoSink](Linux-api.md#IRTCVideo-setpublicstreamvideosink) | 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。 |

## 音视频处理

| 方法 | 描述 |
| --- | --- |
| [getVideoEffectInterface](Linux-api.md#IRTCVideo-getvideoeffectinterface) | 获取视频特效接口 |
| [setVideoWatermark](Linux-api.md#IRTCVideo-setvideowatermark) | 在指定视频流上添加水印。 |
| [clearVideoWatermark](Linux-api.md#IRTCVideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [checkLicense](Linux-api.md#IVideoEffect-checklicense) | 视频特效许可证检查 |
| [getAuthMessage](Linux-api.md#IVideoEffect-getauthmessage) | 从特效 SDK 获取授权消息，用于获取在线许可证。 |
| [freeAuthMessage](Linux-api.md#IVideoEffect-freeauthmessage) | 使用完授权消息字符串后，释放内存。 |
| [setAlgoModelPath](Linux-api.md#IVideoEffect-setalgomodelpath) | 设置视频特效算法模型路径 |
| [enableEffect](Linux-api.md#IVideoEffect-enableeffect) | 开启关闭视频特效 |
| [setEffectNodes](Linux-api.md#IVideoEffect-seteffectnodes) | 设置视频特效素材包 |
| [updateNode](Linux-api.md#IVideoEffect-updatenode) | 设置特效强度 |
| [setColorFilter](Linux-api.md#IVideoEffect-setcolorfilter) | 设置颜色滤镜 |
| [setColorFilterIntensity](Linux-api.md#IVideoEffect-setcolorfilterintensity) | 设置已启用颜色滤镜的强度 |
| [setLocalVoicePitch](Linux-api.md#IRTCVideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |

## 自定义流处理

| 方法 | 描述 |
| --- | --- |
| [setVideoSourceType](Linux-api.md#IRTCVideo-setvideosourcetype) | 设置向 SDK 输入的视频源，包括屏幕流<br/>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br> |
| [pushExternalVideoFrame](Linux-api.md#IRTCVideo-pushexternalvideoframe) | 发送外部源视频数据 |
| [setLocalVideoSink](Linux-api.md#IRTCVideo-setlocalvideosink) | 将本地视频流与自定义渲染器绑定。 |
| [setRemoteVideoSink](Linux-api.md#IRTCVideo-setremotevideosink) | 将远端视频流与自定义渲染器绑定。 |
| [registerRemoteEncodedVideoFrameObserver](Linux-api.md#IRTCVideo-registerremoteencodedvideoframeobserver) | 注册远端编码后视频数据回調。  <br><br/>完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame](Linux-callback.md#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调 |
| [setVideoDecoderConfig](Linux-api.md#IRTCVideo-setvideodecoderconfig) | 在订阅远端视频流之前，设置远端视频数据解码方式 |
| [setAudioSourceType](Linux-api.md#IRTCVideo-setaudiosourcetype) | 切换音频采集方式 |
| [setAudioRenderType](Linux-api.md#IRTCVideo-setaudiorendertype) | 切换音频渲染方式 |
| [pushExternalAudioFrame](Linux-api.md#IRTCVideo-pushexternalaudioframe) | 推送自定义音频数据。 |
| [pullExternalAudioFrame](Linux-api.md#IRTCVideo-pullexternalaudioframe) | 拉取远端音频数据。可用于自定义音频渲染。 |
| [registerLocalVideoProcessor](Linux-api.md#IRTCVideo-registerlocalvideoprocessor) | 设置自定义视频前处理器。<br><br/>使用这个视频前处理器，你可以调用 [processVideoFrame](Linux-api.md#IVideoProcessor-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。 |
| [processVideoFrame](Linux-api.md#IVideoProcessor-processvideoframe) | 获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor](Linux-api.md#IRTCVideo-registerlocalvideoprocessor) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。 |
| [registerAudioProcessor](Linux-api.md#IRTCVideo-registeraudioprocessor) | 注册自定义音频处理器。<br><br/>注册完成后，你可以调用 [enableAudioProcessor](Linux-api.md#IRTCVideo-enableaudioprocessor)，对本地采集或接收到的远端音频进行处理。 |
| [enableAudioProcessor](Linux-api.md#IRTCVideo-enableaudioprocessor) | 设置并开启指定的音频帧回调，进行自定义处理。 |
| [disableAudioProcessor](Linux-api.md#IRTCVideo-disableaudioprocessor) | 关闭自定义音频处理。 |
| [registerAudioFrameObserver](Linux-api.md#IRTCVideo-registeraudioframeobserver) | 注册音频数据回调观察者。  <br> |
| [enableAudioFrameCallback](Linux-api.md#IRTCVideo-enableaudioframecallback) | 设置并开启指定的音频数据帧回调 |
| [disableAudioFrameCallback](Linux-api.md#IRTCVideo-disableaudioframecallback) | 关闭音频回调 |
| [registerLocalEncodedVideoFrameObserver](Linux-api.md#IRTCVideo-registerlocalencodedvideoframeobserver) | 注册本地视频帧监测器。  <br><br/>无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame](Linux-callback.md#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) 回调给用户 |
| [setExternalVideoEncoderEventHandler](Linux-api.md#IRTCVideo-setexternalvideoencodereventhandler) | 注册自定义编码帧推送事件回调 |
| [pushExternalEncodedVideoFrame](Linux-api.md#IRTCVideo-pushexternalencodedvideoframe) | 推送自定义编码后的视频流 |

## 网络管理

| 方法 | 描述 |
| --- | --- |
| [enableSimulcastMode](Linux-api.md#IRTCVideo-enablesimulcastmode) | 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。 |
| [setRemoteVideoConfig](Linux-api.md#IRTCRoom-setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [setPublishFallbackOption](Linux-api.md#IRTCVideo-setpublishfallbackoption) | 设置发布的音视频流的回退选项。  <br><br/>你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。 |
| [setSubscribeFallbackOption](Linux-api.md#IRTCVideo-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。 <br><br/>你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority](Linux-api.md#IRTCVideo-setremoteuserpriority) | 设置用户优先级 |
| [startAudioPlaybackDeviceTest](Linux-api.md#IAudioDeviceManager-startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。 |
| [stopAudioPlaybackDeviceTest](Linux-api.md#IAudioDeviceManager-stopaudioplaybackdevicetest) | 停止音频播放测试。  <br> |
| [initAudioPlaybackDeviceForTest](Linux-api.md#IAudioDeviceManager-initaudioplaybackdevicefortest) | 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。 |
| [initAudioCaptureDeviceForTest](Linux-api.md#IAudioDeviceManager-initaudiocapturedevicefortest) | 尝试初始化音频采集设备，可检测设备不存在、权限被拒绝/禁用等异常问题。 |
| [startNetworkDetection](Linux-api.md#IRTCVideo-startnetworkdetection) | 开启通话前网络探测 |
| [stopNetworkDetection](Linux-api.md#IRTCVideo-stopnetworkdetection) | 停止通话前网络探测 |

## 消息

| 方法 | 描述 |
| --- | --- |
| [sendRoomMessage](Linux-api.md#IRTCRoom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [sendRoomBinaryMessage](Linux-api.md#IRTCRoom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [login](Linux-api.md#IRTCVideo-login) | 必须先登录，才能发送房间外点对点消息和向应用服务器发送消息<br><br/>在调用本接口登录后，如果想要登出，需要调用 [logout](Linux-api.md#IRTCVideo-logout)。 |
| [logout](Linux-api.md#IRTCVideo-logout) | 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken](Linux-api.md#IRTCVideo-updatelogintoken) | 更新用户用于登录的 Token  <br><br/>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br><br/>调用 [login](Linux-api.md#IRTCVideo-login) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [onLoginResult](Linux-callback.md#IRTCVideoEventHandler-onloginresult) 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。 |
| [setServerParams](Linux-api.md#IRTCVideo-setserverparams) | 设置应用服务器参数  <br><br/>客户端调用 [sendServerMessage](Linux-api.md#IRTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Linux-api.md#IRTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须设置有效签名和应用服务器地址。 |
| [getPeerOnlineStatus](Linux-api.md#IRTCVideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [sendUserMessage](Linux-api.md#IRTCRoom-sendusermessage) | 给房间内指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessage](Linux-api.md#IRTCRoom-senduserbinarymessage) | 给房间内指定的用户发送二进制消息（P2P） |
| [sendUserMessageOutsideRoom](Linux-api.md#IRTCVideo-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom](Linux-api.md#IRTCVideo-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [sendServerMessage](Linux-api.md#IRTCVideo-sendservermessage) | 客户端给应用服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Linux-api.md#IRTCVideo-sendserverbinarymessage) | 客户端给应用服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo](Linux-api.md#IRTCVideo-sendstreamsyncinfo) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [onStreamSyncInfoReceived](Linux-callback.md#IRTCVideoEventHandler-onstreamsyncinforeceived) 回调。 |
| [sendSEIMessage](Linux-api.md#IRTCVideo-sendseimessage) | 通过视频帧发送 SEI 数据。  <br><br/>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |

## 混音

| 方法 | 描述 |
| --- | --- |
| [getAudioMixingManager](Linux-api.md#IRTCVideo-getaudiomixingmanager) | 混音管理接口创建 |
| [startAudioMixing](Linux-api.md#IAudioMixingManager-startaudiomixing) | 开始播放音频文件。<br/>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。 |
| [stopAudioMixing](Linux-api.md#IAudioMixingManager-stopaudiomixing) | 停止播放音乐文件及混音 |
| [pauseAudioMixing](Linux-api.md#IAudioMixingManager-pauseaudiomixing) | 暂停播放音乐文件及混音 |
| [resumeAudioMixing](Linux-api.md#IAudioMixingManager-resumeaudiomixing) | 恢复播放音乐文件及混音 |
| [enableVocalInstrumentBalance](Linux-api.md#IRTCVideo-enablevocalinstrumentbalance) | 开启/关闭音量均衡功能。  <br><br/>开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 [setAudioMixingLoudness](#setaudiomixingloudness) 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。（Linux 不支持） |
| [getAudioMixingCurrentPosition](Linux-api.md#IAudioMixingManager-getaudiomixingcurrentposition) | 获取音乐文件播放进度 |
| [setAudioMixingPlaybackSpeed](Linux-api.md#IAudioMixingManager-setaudiomixingplaybackspeed) | 设置混音时音频文件的播放速度 |
| [preloadAudioMixing](Linux-api.md#IAudioMixingManager-preloadaudiomixing) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [unloadAudioMixing](Linux-api.md#IAudioMixingManager-unloadaudiomixing) | 卸载指定音乐文件 |
| [enablePlaybackDucking](Linux-api.md#IRTCVideo-enableplaybackducking) | 打开/关闭音量闪避功能，适用于“一起看”等场景。  <br><br/>开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。 |

## 屏幕分享

| 方法 | 描述 |
| --- | --- |
| [subscribeScreen](Linux-api.md#IRTCRoom-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen](Linux-api.md#IRTCRoom-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |

## 安全与加密

| 方法 | 描述 |
| --- | --- |
| [startCloudProxy](Linux-api.md#IRTCVideo-startcloudproxy) | 开启云代理 |
| [stopCloudProxy](Linux-api.md#IRTCVideo-stopcloudproxy) | 关闭云代理 |
| [setCustomizeEncryptHandler](Linux-api.md#IRTCVideo-setcustomizeencrypthandler) | 设置自定义加密  <br><br/>需要实现对应的加密/解密方法，详情参考 [EncryptType](Linux-keytype.md#encrypttype) 。 <br> |
| [setEncryptInfo](Linux-api.md#IRTCVideo-setencryptinfo) | 设置传输时使用内置加密的方式 <br> |

# 回调
## 引擎管理

| 回调 | 描述 |
| --- | --- |
| [onLogReport](Linux-callback.md#IRTCVideoEventHandler-onlogreport) | 端监控日志回调。当产生一个端监控事件时触发该回调。 |
| [onSysStats](Linux-callback.md#IRTCVideoEventHandler-onsysstats) | 周期性（2s）地发出回调，报告当前cpu与memory使用率 |
| [onWarning](Linux-callback.md#IRTCVideoEventHandler-onwarning) | 当内部发生警告事件时触发该回调 |
| [onError](Linux-callback.md#IRTCVideoEventHandler-onerror) | 当 SDK 内部发生不可逆转错误时触发该回调。 |
| [onHttpProxyState](Linux-callback.md#IRTCVideoEventHandler-onhttpproxystate) | HTTP 代理连接状态改变时，收到该回调。 |
| [onHttpsProxyState](Linux-callback.md#IRTCVideoEventHandler-onhttpsproxystate) | HTTPS 代理连接状态改变时，收到该回调。 |
| [onSocks5ProxyState](Linux-callback.md#IRTCVideoEventHandler-onsocks5proxystate) | Socks5 代理状态改变时，收到该回调。 |
| [onTokenWillExpire](Linux-callback#IRTCRoomEventHandler-ontokenwillexpire) | Token 过期前 30 秒将触发该回调。<br><br/>调用 [updateToken](Linux-api.md#IRTCRoom-updatetoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。 |

## 房间管理

| 回调 | 描述 |
| --- | --- |
| [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) | 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。 |
| [onCreateRoomStateChanged](Linux-callback.md#IRTCVideoEventHandler-oncreateroomstatechanged) | 创建房间失败回调。 |
| [onLeaveRoom](Linux-callback#IRTCRoomEventHandler-onleaveroom) | 离开房间回调。  <br><br/>用户调用 [leaveRoom](Linux-api.md#IRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br> |
| [onUserJoined](Linux-callback#IRTCRoomEventHandler-onuserjoined) | 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br><br/>1. 远端用户调用 [setUserVisibility](Linux-api.md#IRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br><br/>2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br><br/>3. 房间内隐身远端用户调用 [setUserVisibility](Linux-api.md#IRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br><br/>4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br> |
| [onUserLeave](Linux-callback.md#IRTCRoomEventHandler-onuserleave) | 远端用户离开房间，或切至不可见时，本地用户会收到此事件 |
| [onRoomStats](Linux-callback.md#IRTCRoomEventHandler-onroomstats) | 房间内通话统计信息回调。   <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |

## 音频管理

| 回调 | 描述 |
| --- | --- |
| [onAudioDeviceWarning](Linux-callback.md#IRTCVideoEventHandler-onaudiodevicewarning) | 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。 |
| [onAudioDeviceStateChanged](Linux-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) | 音频设备状态回调。提示音频采集、音频播放等设备设备的状态。 |
| [onLocalAudioPropertiesReport](Linux-callback#IRTCVideoEventHandler-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Linux-api.md#IRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br><br/>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。 |
| [onRemoteAudioPropertiesReport](Linux-callback#IRTCVideoEventHandler-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Linux-api.md#IRTCVideo-enableaudiopropertiesreport)，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br><br/>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onUserStartAudioCapture](Linux-callback#IRTCVideoEventHandler-onuserstartaudiocapture) | 房间内的用户调用 [startAudioCapture](Linux-api.md#IRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。 |
| [onUserStopAudioCapture](Linux-callback#IRTCVideoEventHandler-onuserstopaudiocapture) | 房间内的用户调用 [stopAudioCapture](Linux-api.md#IRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。 |
| [onActiveSpeaker](Linux-callback#IRTCVideoEventHandler-onactivespeaker) | 调用 [enableAudioPropertiesReport](Linux-api.md#IRTCVideo-enableaudiopropertiesreport) 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [onStreamSyncInfoReceived](Linux-callback#IRTCVideoEventHandler-onstreamsyncinforeceived) | 音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Linux-api.md#IRTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br> |
| [onAudioStreamBanned](Linux-callback.md#IRTCRoomEventHandler-onaudiostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [onAudioPlaybackDeviceTestVolume](Linux-callback.md#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onAudioDeviceVolumeChanged](Linux-callback.md#IRTCVideoEventHandler-onaudiodevicevolumechanged) | 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。 |

## 视频管理

| 回调 | 描述 |
| --- | --- |
| [onUserStartVideoCapture](Linux-callback#IRTCVideoEventHandler-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Linux-api.md#IRTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。 |
| [onUserStopVideoCapture](Linux-callback#IRTCVideoEventHandler-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Linux-api.md#IRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。 |
| [onVideoDeviceStateChanged](Linux-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) | 视频频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。 |
| [onVideoDeviceWarning](Linux-callback.md#IRTCVideoEventHandler-onvideodevicewarning) | 视频设备警告回调，包括视频采集设备等。 |
| [onFaceDetectResult](Linux-callback.md#IFaceDetectionObserver-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。 <br><br/>调用 [registerFaceDetectionObserver](Linux-api.md#IVideoEffect-registerfacedetectionobserver) 注册了 [IFaceDetectionObserver](Linux-callback.md#ifacedetectionobserver)，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |

## 音视频传输

| 回调 | 描述 |
| --- | --- |
| [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [onAVSyncStateChange](Linux-callback#IRTCRoomEventHandler-onavsyncstatechange) | 发布端调用 [setMultiDeviceAVSync](Linux-api.md#IRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。 |
| [onUserPublishStream](Linux-callback.md#IRTCRoomEventHandler-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集的媒体流的回调。 |
| [onUserUnpublishStream](Linux-callback.md#IRTCRoomEventHandler-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onStreamSubscribed](Linux-callback.md#IRTCRoomEventHandler-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onAudioFrameSendStateChanged](Linux-callback.md#IRTCVideoEventHandler-onaudioframesendstatechanged) | 音频首帧发送状态改变回调 |
| [onVideoFrameSendStateChanged](Linux-callback.md#IRTCVideoEventHandler-onvideoframesendstatechanged) | 视频首帧发送状态改变回调 |
| [onAudioFramePlayStateChanged](Linux-callback.md#IRTCVideoEventHandler-onaudioframeplaystatechanged) | 音频首帧播放状态改变回调 |
| [onVideoFramePlayStateChanged](Linux-callback.md#IRTCVideoEventHandler-onvideoframeplaystatechanged) | 视频首帧播放状态改变回调 |
| [onRemoteStreamStats](Linux-callback.md#IRTCRoomEventHandler-onremotestreamstats) | 每隔 2s 收到此回调，了解订阅的远端用户发布的流在此周期内的网络质量信息。 |
| [onNetworkQuality](Linux-callback.md#IRTCRoomEventHandler-onnetworkquality) | 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。 |
| [onForwardStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [onForwardStreamEvent](Linux-callback.md#IRTCRoomEventHandler-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [onLocalAudioStateChanged](Linux-callback.md#IRTCVideoEventHandler-onlocalaudiostatechanged) | 本地音频的状态发生改变时，该回调通知当前的本地音频状态。 |
| [onRemoteAudioStateChanged](Linux-callback.md#IRTCVideoEventHandler-onremoteaudiostatechanged) | 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。 |
| [onFirstLocalAudioFrame](Linux-callback.md#IRTCVideoEventHandler-onfirstlocalaudioframe) | 发布音频流时，采集到第一帧音频帧，收到该回调。 |
| [onFirstRemoteAudioFrame](Linux-callback.md#IRTCVideoEventHandler-onfirstremoteaudioframe) | 接收到来自远端某音频流的第一帧时，收到该回调。 |
| [onFirstLocalVideoFrameCaptured](Linux-callback.md#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) | RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。 |
| [onLocalVideoSizeChanged](Linux-callback.md#IRTCVideoEventHandler-onlocalvideosizechanged) | 本地视频大小或旋转配置发生改变时，收到此回调。 |
| [onRemoteVideoSizeChanged](Linux-callback.md#IRTCVideoEventHandler-onremotevideosizechanged) | 远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onFirstRemoteVideoFrameRendered](Linux-callback.md#IRTCVideoEventHandler-onfirstremotevideoframerendered) | SDK 内部渲染成功远端视频流首帧后，收到此回调。 |
| [onLocalVideoStateChanged](Linux-callback.md#IRTCVideoEventHandler-onlocalvideostatechanged) | 本地视频流的状态发生改变时，收到该事件。 |
| [onRemoteVideoStateChanged](Linux-callback.md#IRTCVideoEventHandler-onremotevideostatechanged) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [onVideoStreamBanned](Linux-callback.md#IRTCRoomEventHandler-onvideostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [onFirstRemoteVideoFrameDecoded](Linux-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [onPushPublicStreamResult](Linux-callback#IRTCVideoEventHandler-onpushpublicstreamresult) | 公共流发布结果回调。<br><br/>调用 [startPushPublicStream](Linux-api.md#IRTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。 |
| [onPlayPublicStreamResult](Linux-callback#IRTCVideoEventHandler-onplaypublicstreamresult) | 订阅公共流的结果回调<br><br/>通过 [startPlayPublicStream](Linux-api.md#IRTCVideo-startplaypublicstream) 订阅公共流后，可以通过本回调获取订阅结果。 |
| [onPublicStreamSEIMessageReceived](Linux-callback#IRTCVideoEventHandler-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息<br><br/>通过 [startPlayPublicStream](Linux-api.md#IRTCVideo-startplaypublicstream) 开始播放公共流后，可以通过本回调获取公共流中包含的 SEI 信息。 |
| [onFirstPublicStreamVideoFrameDecoded](Linux-callback#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) | 公共流的首帧视频解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Linux-api.md#IRTCVideo-startplaypublicstream)。 |
| [onFirstPublicStreamAudioFrame](Linux-callback#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Linux-api.md#IRTCVideo-startplaypublicstream)。 |

## 自定义流处理

| 回调 | 描述 |
| --- | --- |
| [onStart](Linux-callback#IExternalVideoEncoderEventHandler-onstart) | 提示自定义编码帧可以开始推送的回调。  <br><br/>收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Linux-api.md#IRTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧 |
| [onStop](Linux-callback.md#IExternalVideoEncoderEventHandler-onstop) | 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧 |
| [onRateUpdate](Linux-callback.md#IExternalVideoEncoderEventHandler-onrateupdate) | 当自定义编码流的帧率或码率发生变化时，触发该回调 |
| [onRequestKeyFrame](Linux-callback.md#IExternalVideoEncoderEventHandler-onrequestkeyframe) | 提示流发布端需重新生成关键帧的回调 |
| [onLocalEncodedVideoFrame](Linux-callback#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) | 调用 [registerLocalEncodedVideoFrameObserver](Linux-api.md#IRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。 |
| [onRemoteEncodedVideoFrame](Linux-callback#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) | 调用 [registerRemoteEncodedVideoFrameObserver](Linux-api.md#IRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调 |
| [onLocalVideoFrame](Linux-callback.md#IVideoFrameObserver-onlocalvideoframe) | 获取采集成功的本地摄像头流视频帧，用于自定义处理或渲染。 |
| [onLocalScreenFrame](Linux-callback.md#IVideoFrameObserver-onlocalscreenframe) | 获取采集成功的本地屏幕视频帧，用于自定义处理或渲染。 |
| [onRemoteVideoFrame](Linux-callback.md#IVideoFrameObserver-onremotevideoframe) | 获取采集成功的远端摄像头流视频帧，用于自定义处理或渲染。 |
| [onRemoteScreenFrame](Linux-callback.md#IVideoFrameObserver-onremotescreenframe) | 获取采集成功的远端屏幕视频帧，用于自定义处理或渲染。 |
| [onRecordAudioFrame](Linux-callback.md#IAudioFrameObserver-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame](Linux-callback.md#IAudioFrameObserver-onplaybackaudioframe) | 返回订阅的所有远端用户混音后的音频数据 |
| [onRemoteUserAudioFrame](Linux-callback.md#IAudioFrameObserver-onremoteuseraudioframe) | 返回远端单个用户的音频数据 |
| [onMixedAudioFrame](Linux-callback.md#IAudioFrameObserver-onmixedaudioframe) | 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据 |
| [onRecordScreenAudioFrame](Linux-callback.md#IAudioFrameObserver-onrecordscreenaudioframe) | 返回本地屏幕录制的音频数据 |

## 网络管理

| 回调 | 描述 |
| --- | --- |
| [onPerformanceAlarms](Linux-callback.md#IRTCVideoEventHandler-onperformancealarms) | 本地未开启发布性能回退，检测到设备性能不足时，收到此回调。<br><br/>本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。 |
| [onSimulcastSubscribeFallback](Linux-callback.md#IRTCVideoEventHandler-onsimulcastsubscribefallback) | 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。 |
| [onNetworkDetectionResult](Linux-callback#IRTCVideoEventHandler-onnetworkdetectionresult) | 通话前网络探测结果。  <br><br/>成功调用 [startNetworkDetection](Linux-api.md#IRTCVideo-startnetworkdetection) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [onNetworkDetectionStopped](Linux-callback#IRTCVideoEventHandler-onnetworkdetectionstopped) | 通话前网络探测结束<br/>以下情况将停止探测并收到本一次本回调：<br><br/>1. 当调用 [stopNetworkDetection](Linux-api.md#IRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；<br/>2. 当收到远端/本端音频首帧后，停止探测；<br/>3. 当探测超过3分钟后，停止探测；<br/>4. 当探测链路断开一定时间之后，停止探测。 |
| [onConnectionStateChanged](Linux-callback.md#IRTCVideoEventHandler-onconnectionstatechanged) | SDK 与信令服务器连接状态改变回调。连接状态改变时触发。 |
| [onSEIMessageReceived](Linux-callback#IRTCVideoEventHandler-onseimessagereceived) | 收到通过 [sendSEIMessage](Linux-api.md#IRTCVideo-sendseimessage) 发送的带有 SEI 消息的视频帧时，收到此回调 |

## 消息

| 回调 | 描述 |
| --- | --- |
| [onLoginResult](Linux-callback.md#IRTCVideoEventHandler-onloginresult) | 登录结果回调 |
| [onLogout](Linux-callback.md#IRTCVideoEventHandler-onlogout) | 登出结果回调 |
| [onServerParamsSetResult](Linux-callback.md#IRTCVideoEventHandler-onserverparamssetresult) | 设置应用服务器参数的返回结果 |
| [onGetPeerOnlineStatus](Linux-callback.md#IRTCVideoEventHandler-ongetpeeronlinestatus) | 查询对端或本端用户登录状态的返回结果 |
| [onUserMessageReceivedOutsideRoom](Linux-callback#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserMessageOutsideRoom](Linux-api.md#IRTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调 |
| [onUserBinaryMessageReceivedOutsideRoom](Linux-callback#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Linux-api.md#IRTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调 |
| [onUserMessageSendResultOutsideRoom](Linux-callback.md#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) | 给房间外指定的用户发送消息的回调 |
| [onServerMessageSendResult](Linux-callback.md#IRTCVideoEventHandler-onservermessagesendresult) | 给应用服务器发送消息的回调。 |
| [onRoomMessageReceived](Linux-callback.md#IRTCRoomEventHandler-onroommessagereceived) | 接收到房间内广播消息的回调。 |
| [onRoomBinaryMessageReceived](Linux-callback.md#IRTCRoomEventHandler-onroombinarymessagereceived) | 接收到房间内二进制广播消息的回调。 |
| [onUserMessageReceived](Linux-callback.md#IRTCRoomEventHandler-onusermessagereceived) | 收到来自房间中其他用户发来的文本消息时（P2P），会收到此回调。 |
| [onUserBinaryMessageReceived](Linux-callback.md#IRTCRoomEventHandler-onuserbinarymessagereceived) | 单个用户接收到同一房间内其他 uid 所属用户发来二进制消息的回调（P2P）。 |
| [onUserMessageSendResult](Linux-callback.md#IRTCRoomEventHandler-onusermessagesendresult) | 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。 |
| [onRoomMessageSendResult](Linux-callback#IRTCRoomEventHandler-onroommessagesendresult) | 当调用 [sendRoomMessage](Linux-api.md#IRTCRoom-sendroommessage) 函数发送消息后，回调此条消息的发送结果（反馈）。 |

## CDN 推流

| 回调 | 描述 |
| --- | --- |
| [onStreamMixingEvent](Linux-callback.md#ITranscoderObserver-onstreammixingevent) | 转推直播状态回调 |
| [onStreamMixingAudioFrame](Linux-callback.md#ITranscoderObserver-onstreammixingaudioframe) | 合流音频回调，运行在音频回调线程 |
| [onStreamMixingVideoFrame](Linux-callback.md#ITranscoderObserver-onstreammixingvideoframe) | 合流视频回调，运行在视频回调线程 |
| [onStreamMixingDataFrame](Linux-callback.md#ITranscoderObserver-onstreammixingdataframe) | 视频 SEI 帧回调，运行在视频回调线程 |

## 混音

| 回调 | 描述 |
| --- | --- |
| [onAudioMixingStateChanged](Linux-callback.md#IRTCVideoEventHandler-onaudiomixingstatechanged) | 音频混音文件播放状态改变时回调 |
| [onAudioMixingPlayingProgress](Linux-callback.md#IRTCVideoEventHandler-onaudiomixingplayingprogress) | 混音音频文件播放进度回调 |

## 屏幕分享

| 回调 | 描述 |
| --- | --- |
| [onUserPublishScreen](Linux-callback.md#IRTCRoomEventHandler-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](Linux-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onScreenVideoFrameSendStateChanged](Linux-callback.md#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) | 屏幕共享流视频首帧发送状态改变回调 |
| [onScreenVideoFramePlayStateChanged](Linux-callback.md#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) | 屏幕共享流视频首帧播放状态改变回调 |

## 安全与加密

| 回调 | 描述 |
| --- | --- |
| [onCloudProxyConnected](Linux-callback#IRTCVideoEventHandler-oncloudproxyconnected) | 调用 [startCloudProxy](Linux-api.md#IRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onEncryptData](Linux-callback.md#IEncryptHandler-onencryptdata) | 自定义加密。  <br><br/>使用设定的自定义加密方式，对传输前的音视频帧数据进行加密。 |
| [onDecryptData](Linux-callback.md#IEncryptHandler-ondecryptdata) | 自定义解密。  <br><br/>对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData](Linux-callback.md#IEncryptHandler-onencryptdata)。 |