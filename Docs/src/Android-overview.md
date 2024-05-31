# 方法
## 引擎管理

| 方法 | 描述 |
| --- | --- |
| [createRTCVideo](Android-api.md#RTCVideo-creatertcvideo) | 创建引擎对象  <br><br/>如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br><br/>如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。 |
| [destroyRTCVideo](Android-api.md#RTCVideo-destroyrtcvideo) | 销毁由 [createRTCVideo](Android-api.md#RTCVideo-creatertcvideo) 所创建引擎实例，并释放所有相关资源  <br> |
| [getSdkVersion](Android-api.md#RTCVideo-getsdkversion) | 获取 SDK 当前的版本号。 |
| [feedback](Android-api.md#RTCVideo-feedback) | 将用户反馈的问题上报到 RTC |
| [getErrorDescription](Android-api.md#RTCVideo-geterrordescription) | 获取 SDK 内各种错误码、警告码的描述文字 |
| [setRtcVideoEventHandler](Android-api.md#RTCVideo-setrtcvideoeventhandler) | 设置引擎事件回调的接收类，必须继承自 [IRTCVideoEventHandler](Android-callback.md#irtcvideoeventhandler) 。 |
| [setBusinessId](Android-api.md#RTCVideo-setbusinessid) | 设置业务标识参数  <br><br/>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setRuntimeParameters](Android-api.md#RTCVideo-setruntimeparameters) | 设置运行时的参数 |

## 房间管理

| 方法 | 描述 |
| --- | --- |
| [createRTCRoom](Android-api.md#RTCVideo-creatertcroom) | 创建房间实例。<br/>调用此方法仅返回一个房间实例，你仍需调用 [joinRoom](Android-api.md#RTCRoom-joinroom) 才能真正地创建/加入房间。<br/>多次调用此方法以创建多个 [RTCRoom](Android-api.md#rtcroom) 实例。分别调用各 RTCRoom 实例中的 [joinRoom](Android-api.md#RTCRoom-joinroom) 方法，同时加入多个房间。<br/>多房间模式下，用户可以同时订阅各房间的音视频流。 |
| [destroy](Android-api.md#RTCRoom-destroy) | 退出并销毁调用 [createRTCRoom](Android-api.md#RTCVideo-creatertcroom) 所创建的房间实例。 |
| [setRTCRoomEventHandler](Android-api.md#RTCRoom-setrtcroomeventhandler) | 通过设置房间事件 handler，监听此对象对应的回调事件。 |
| [joinRoom](Android-api.md#RTCRoom-joinroom) | 加入房间。<br><br/>多房间场景下，调用 [createRTCRoom](Android-api.md#RTCVideo-creatertcroom) 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br> |
| [leaveRoom](Android-api.md#RTCRoom-leaveroom) | 离开房间。  <br><br/>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br><br/>此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 [onLeaveRoom](Android-callback.md#IRTCRoomEventHandler-onleaveroom) 回调通知。  <br> |
| [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) | 设置用户可见性。默认可见。  <br> |
| [updateToken](Android-api.md#RTCRoom-updatetoken) | 更新 Token。<br>在 Token 进房权限过期前 30 秒，会收到 [onTokenWillExpire](Android-callback.md#IRTCRoomEventHandler-ontokenwillexpire) 回调，此时需要重新获取 Token，并调用此方法更新 Token，否则用户将因为 Token 过期被移出房间。 |

## 音频管理

| 方法 | 描述 |
| --- | --- |
| [setDefaultAudioRoute](Android-api.md#RTCVideo-setdefaultaudioroute) | 将默认的音频播放设备设置为听筒或扬声器。  <br> |
| [setAudioRoute](Android-api.md#RTCVideo-setaudioroute) | 设置当前音频播放路由。默认使用 [setDefaultAudioRoute](Android-api.md#RTCVideo-setdefaultaudioroute) 中设置的音频路由。<br/>音频播放路由发生变化时，会收到 [onAudioRouteChanged](Android-callback.md#IRTCVideoEventHandler-onaudioroutechanged) 回调。 |
| [getAudioRoute](Android-api.md#RTCVideo-getaudioroute) | 获取当前使用的音频播放路由。  <br> |
| [setCaptureVolume](Android-api.md#RTCVideo-setcapturevolume) | 调节音频采集音量 |
| [setPlaybackVolume](Android-api.md#RTCVideo-setplaybackvolume) | 调节本地播放的所有远端用户混音后的音量。播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume](Android-api.md#RTCVideo-setremoteaudioplaybackvolume) | 调节来自指定远端用户的音频播放音量，默认为 100。 |
| [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) | 启用音频信息提示。  <br> |
| [startAudioCapture](Android-api.md#RTCVideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法开启后，本地用户会收到 [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Android-callback.md#IRTCVideoEventHandler-onuserstartaudiocapture) 的回调。 |
| [stopAudioCapture](Android-api.md#RTCVideo-stopaudiocapture) | 立即关闭内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法，本地用户会收到 [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopAudioCapture](Android-callback.md#IRTCVideoEventHandler-onuserstopaudiocapture) 的回调。 |
| [setAudioScenario](Android-api.md#RTCVideo-setaudioscenario) | 设置音频场景类型 |
| [setAudioProfile](Android-api.md#RTCVideo-setaudioprofile) | 设置音质档位。当所选的 [ChannelProfile](Android-keytype.md#channelprofile) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。 |
| [enableExternalSoundCard](Android-api.md#RTCVideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |
| [getAudioDeviceManager](Android-api.md#RTCVideo-getaudiodevicemanager) |  |
| [startAudioPlaybackDeviceTest](Android-api.md#IRTCAudioDeviceManager-startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。 |
| [stopAudioPlaybackDeviceTest](Android-api.md#IRTCAudioDeviceManager-stopaudioplaybackdevicetest) | 停止音频播放测试。 |
| [startAudioDeviceRecordTest](Android-api.md#IRTCAudioDeviceManager-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br><br/>建议提前调用 `enableAudioPropertiesReport` 注册音量提示回调，测试开始后，音频设备开始采集本地声音，可以通过 `onLocalAudioPropertiesReport` 获取采集音量。<br> |
| [stopAudioDeviceRecordAndPlayTest](Android-api.md#IRTCAudioDeviceManager-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br><br/>调用 [startAudioDeviceRecordTest](Android-api.md#IRTCAudioDeviceManager-startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
| [stopAudioDevicePlayTest](Android-api.md#IRTCAudioDeviceManager-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Android-api.md#IRTCAudioDeviceManager-startaudiodevicerecordtest) 开始的音频播放设备测试。<br/>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |

## 视频管理

| 方法 | 描述 |
| --- | --- |
| [startVideoCapture](Android-api.md#RTCVideo-startvideocapture) | 立即开启内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 [onUserStartVideoCapture](Android-callback.md#IRTCVideoEventHandler-onuserstartvideocapture) 的回调。 |
| [stopVideoCapture](Android-api.md#RTCVideo-stopvideocapture) | 立即关闭内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br/>调用该方法，本地用户会收到 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Android-callback.md#IRTCVideoEventHandler-onuserstopvideocapture) 的回调。 |
| [setVideoCaptureConfig](Android-api.md#RTCVideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。<br><br/>如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。 |
| [setVideoRotationMode](Android-api.md#RTCVideo-setvideorotationmode) | 设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br><br/>接收端渲染视频时，将按照和发送端相同的方式进行旋转。<br> |
| [setLocalVideoCanvas](Android-api.md#RTCVideo-setlocalvideocanvas) | 设置本地视频渲染时使用的视图，并设置渲染模式。 |
| [updateLocalVideoCanvas](Android-api.md#RTCVideo-updatelocalvideocanvas) | 修改本地视频渲染模式和背景色。 |
| [setRemoteVideoCanvas](Android-api.md#RTCVideo-setremotevideocanvas) | 渲染来自指定远端用户的视频流时，设置使用的视图和渲染模式。<br><br/>要解除绑定，将 `videoCanvas` 设置为空。 |
| [updateRemoteStreamVideoCanvas](Android-api.md#RTCVideo-updateremotestreamvideocanvas) | 修改远端视频渲染模式和背景色。 |
| [switchCamera](Android-api.md#RTCVideo-switchcamera) | 切换视频内部采集时使用的前置/后置摄像头 <br><br/>调用此接口后，在本地会触发 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 回调。 |
| [isCameraZoomSupported](Android-api.md#RTCVideo-iscamerazoomsupported) | 检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。 |
| [getCameraZoomMaxRatio](Android-api.md#RTCVideo-getcamerazoommaxratio) | 获取当前使用的摄像头（前置/后置）的最大变焦倍数 |
| [setCameraZoomRatio](Android-api.md#RTCVideo-setcamerazoomratio) | 设置当前使用的摄像头（前置/后置）的变焦倍数 |
| [isCameraTorchSupported](Android-api.md#RTCVideo-iscameratorchsupported) | 检测当前使用的摄像头（前置/后置），是否支持闪光灯。 |
| [setCameraTorch](Android-api.md#RTCVideo-setcameratorch) | 打开/关闭当前使用的摄像头（前置/后置）的闪光灯 |
| [isCameraFocusPositionSupported](Android-api.md#RTCVideo-iscamerafocuspositionsupported) | 检查当前使用的摄像头是否支持手动对焦。 |
| [setCameraFocusPosition](Android-api.md#RTCVideo-setcamerafocusposition) | 设置当前使用的摄像头的对焦点。 |
| [isCameraExposurePositionSupported](Android-api.md#RTCVideo-iscameraexposurepositionsupported) | 检查当前使用的摄像头是否支持手动设置曝光点。 |
| [setCameraExposurePosition](Android-api.md#RTCVideo-setcameraexposureposition) | 设置当前使用的摄像头的曝光点 |
| [setCameraExposureCompensation](Android-api.md#RTCVideo-setcameraexposurecompensation) | 设置当前使用的摄像头的曝光补偿。 |
| [registerFaceDetectionObserver](Android-api.md#RTCVideo-registerfacedetectionobserver) | 注册人脸检测结果回调观察者 <br><br/>注册此观察者后，你会周期性收到 [onFaceDetectResult](Android-callback.md#IFaceDetectionObserver-onfacedetectresult) 回调。 |
| [setVideoEncoderConfig](Android-api.md#RTCVideo-setvideoencoderconfig) | <span id="RTCVideo-setvideoencoderconfig-1"></span><br/>视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br><br/>该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig-2) |
| [setVideoEncoderConfig](Android-api.md#RTCVideo-setvideoencoderconfig) | <span id="RTCVideo-setvideoencoderconfig-2"></span><br/>视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |

## 音视频传输

| 方法 | 描述 |
| --- | --- |
| [pauseAllSubscribedStream](Android-api.md#RTCRoom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Android-api.md#RTCRoom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [publishStream](Android-api.md#RTCRoom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream](Android-api.md#RTCRoom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [subscribeStream](Android-api.md#RTCRoom-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream](Android-api.md#RTCRoom-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreams](Android-api.md#RTCRoom-subscribeallstreams) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreams](Android-api.md#RTCRoom-unsubscribeallstreams) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br><br/>自动订阅和手动订阅的流都可以通过本方法取消订阅。 |
| [requestRemoteVideoKeyFrame](Android-api.md#RTCVideo-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) | 开始跨房间转发媒体流。<br/>在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br> |
| [updateForwardStreamToRooms](Android-api.md#RTCRoom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br><br/>通过 [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br/>调用本方法增加或删减房间后，将在本端触发 [onForwardStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。 |
| [stopForwardStreamToRooms](Android-api.md#RTCRoom-stopforwardstreamtorooms) | 停止跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。 |
| [pauseForwardStreamToAllRooms](Android-api.md#RTCRoom-pauseforwardstreamtoallrooms) | 暂停跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br/>调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](Android-api.md#RTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。 |
| [resumeForwardStreamToAllRooms](Android-api.md#RTCRoom-resumeforwardstreamtoallrooms) | 恢复跨房间媒体流转发。<br/>调用 [pauseForwardStreamToAllRooms](Android-api.md#RTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。 |
| [setMultiDeviceAVSync](Android-api.md#RTCRoom-setmultideviceavsync) | 设置发流端音画同步。  <br><br/>当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。 |
| [startPushPublicStream](Android-api.md#RTCVideo-startpushpublicstream) | 发布一路公共流<br><br/>用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 获取和播放指定的公共流。 |
| [stopPushPublicStream](Android-api.md#RTCVideo-stoppushpublicstream) | 停止发布当前用户发布的公共流<br><br/>关于发布公共流，查看 [startPushPublicStream](Android-api.md#RTCVideo-startpushpublicstream) |
| [updatePublicStreamParam](Android-api.md#RTCVideo-updatepublicstreamparam) | 更新公共流参数<br><br/>关于发布公共流，查看 [startPushPublicStream](Android-api.md#RTCVideo-startpushpublicstream)。 |
| [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) | 订阅指定公共流<br><br/>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream](Android-api.md#RTCVideo-stopplaypublicstream) | 取消订阅指定公共流<br><br/>关于订阅公共流，查看 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。 |
| [setPublicStreamVideoCanvas](Android-api.md#RTCVideo-setpublicstreamvideocanvas) | 为指定公共流绑定内部渲染视图。  <br> |
| [setPublicStreamVideoSink](Android-api.md#RTCVideo-setpublicstreamvideosink) | 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。 |

## 音视频处理

| 方法 | 描述 |
| --- | --- |
| [setLocalVideoMirrorType](Android-api.md#RTCVideo-setlocalvideomirrortype) | 为采集到的视频流开启镜像 |
| [setVideoOrientation](Android-api.md#RTCVideo-setvideoorientation) | 在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。<br/>移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。 |
| [setVideoWatermark](Android-api.md#RTCVideo-setvideowatermark) | 在指定视频流上添加水印。 |
| [clearVideoWatermark](Android-api.md#RTCVideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [checkVideoEffectLicense](Android-api.md#RTCVideo-checkvideoeffectlicense) | 视频特效许可证检查 |
| [setVideoEffectAlgoModelPath](Android-api.md#RTCVideo-setvideoeffectalgomodelpath) | 设置视频特效算法模型路径 |
| [enableVideoEffect](Android-api.md#RTCVideo-enablevideoeffect) | 创建/销毁视频特效引擎 |
| [setVideoEffectNodes](Android-api.md#RTCVideo-setvideoeffectnodes) | 设置视频特效素材包 |
| [updateVideoEffectNode](Android-api.md#RTCVideo-updatevideoeffectnode) | 设置特效强度 |
| [setVideoEffectColorFilter](Android-api.md#RTCVideo-setvideoeffectcolorfilter) | 设置颜色滤镜 |
| [setVideoEffectColorFilterIntensity](Android-api.md#RTCVideo-setvideoeffectcolorfilterintensity) | 设置已启用的颜色滤镜强度 |
| [enableEffectBeauty](Android-api.md#RTCVideo-enableeffectbeauty) | 开启/关闭基础美颜 |
| [setBeautyIntensity](Android-api.md#RTCVideo-setbeautyintensity) | 调整基础美颜强度 |
| [setBackgroundSticker](Android-api.md#RTCVideo-setbackgroundsticker) | 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。<br/>若要取消背景特效，将背景贴纸特效素材路径设置为null。 |
| [setVoiceChangerType](Android-api.md#RTCVideo-setvoicechangertype) | 设置变声特效类型 |
| [setVoiceReverbType](Android-api.md#RTCVideo-setvoicereverbtype) | 设置混响特效类型 |
| [setLocalVoicePitch](Android-api.md#RTCVideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |

## 自定义流处理

| 方法 | 描述 |
| --- | --- |
| [setVideoSourceType](Android-api.md#RTCVideo-setvideosourcetype) | 设置向 SDK 输入的视频源，包括屏幕流<br/>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br> |
| [pushExternalVideoFrame](Android-api.md#RTCVideo-pushexternalvideoframe) | 推送外部视频帧。 |
| [setLocalVideoSink](Android-api.md#RTCVideo-setlocalvideosink) | 将本地视频流与自定义渲染器绑定。 |
| [setRemoteVideoSink](Android-api.md#RTCVideo-setremotevideosink) | 将远端视频流与自定义渲染器绑定。 |
| [registerRemoteEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerremoteencodedvideoframeobserver) | 注册远端编码后视频数据回調。  <br><br/>完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [OnRemoteEncodedVideoFrame](Android-callback.md#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调 |
| [setVideoDecoderConfig](Android-api.md#RTCVideo-setvideodecoderconfig) | 在订阅远端视频流之前，设置远端视频数据解码方式 |
| [setAudioSourceType](Android-api.md#RTCVideo-setaudiosourcetype) | 切换音频采集方式 |
| [setAudioRenderType](Android-api.md#RTCVideo-setaudiorendertype) | 切换音频渲染方式 |
| [pushExternalAudioFrame](Android-api.md#RTCVideo-pushexternalaudioframe) | 推送自定义采集的音频数据到 RTC SDK。 |
| [pullExternalAudioFrame](Android-api.md#RTCVideo-pullexternalaudioframe) | 拉取音频数据，用于外部播放。 |
| [registerLocalVideoProcessor](Android-api.md#RTCVideo-registerlocalvideoprocessor) | 设置自定义视频前处理器。<br><br/>使用这个视频前处理器，你能够调用 [processVideoFrame](Android-api.md#IVideoProcessor-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。 |
| [processVideoFrame](Android-api.md#IVideoProcessor-processvideoframe) | 获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor](Android-api.md#RTCVideo-registerlocalvideoprocessor) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。 |
| [registerAudioProcessor](Android-api.md#RTCVideo-registeraudioprocessor) | 注册自定义音频处理器。<br><br/>注册完成后，你可以调用 [enableAudioProcessor](Android-api.md#RTCVideo-enableaudioprocessor)，对本地采集或接收到的远端音频进行处理。 |
| [enableAudioProcessor](Android-api.md#RTCVideo-enableaudioprocessor) | 设置并开启指定的音频帧回调，进行自定义处理。 |
| [disableAudioProcessor](Android-api.md#RTCVideo-disableaudioprocessor) | 关闭自定义音频处理。 |
| [registerAudioFrameObserver](Android-api.md#RTCVideo-registeraudioframeobserver) | 注册音频数据回调观察者。  <br> |
| [enableAudioFrameCallback](Android-api.md#RTCVideo-enableaudioframecallback) | 设置并开启指定的音频数据帧回调 |
| [disableAudioFrameCallback](Android-api.md#RTCVideo-disableaudioframecallback) | 关闭音频回调 |
| [registerLocalEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerlocalencodedvideoframeobserver) | 注册本地视频帧监测器。  <br><br/>无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame](Android-callback.md#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) 回调给用户。 |
| [setExternalVideoEncoderEventHandler](Android-api.md#RTCVideo-setexternalvideoencodereventhandler) | 注册自定义编码帧推送事件回调 |
| [pushExternalEncodedVideoFrame](Android-api.md#RTCVideo-pushexternalencodedvideoframe) | 推送自定义编码后的视频流 |

## 网络管理

| 方法 | 描述 |
| --- | --- |
| [enableSimulcastMode](Android-api.md#RTCVideo-enablesimulcastmode) | 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。 |
| [setRemoteVideoConfig](Android-api.md#RTCRoom-setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [setPublishFallbackOption](Android-api.md#RTCVideo-setpublishfallbackoption) | 设置发布的音视频流的回退选项。  <br><br/>你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。 |
| [setSubscribeFallbackOption](Android-api.md#RTCVideo-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。 <br><br/>你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority](Android-api.md#RTCVideo-setremoteuserpriority) | 设置用户优先级。 |
| [startNetworkDetection](Android-api.md#RTCVideo-startnetworkdetection) | 开启通话前网络探测 |
| [stopNetworkDetection](Android-api.md#RTCVideo-stopnetworkdetection) | 停止通话前网络探测 |
| [startEchoTest](Android-api.md#RTCVideo-startechotest) | 开启音视频回路测试。  <br><br/>在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br><br/>开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。 |
| [stopEchoTest](Android-api.md#RTCVideo-stopechotest) | 停止音视频回路测试。  <br><br/>调用 [startEchoTest](Android-api.md#RTCVideo-startechotest) 开启音视频回路检测后，你必须调用该方法停止检测。 |

## 消息

| 方法 | 描述 |
| --- | --- |
| [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [sendUserMessage](Android-api.md#RTCRoom-sendusermessage) | 给房间内指定的用户发送点对点文本消息 |
| [sendUserBinaryMessage](Android-api.md#RTCRoom-senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息。 |
| [login](Android-api.md#RTCVideo-login) | 必须先登录，才能发送房间外点对点消息和向应用服务器发送消息<br><br/>在调用本接口登录后，如果想要登出，需要调用 [logout](Android-api.md#RTCVideo-logout)。  <br> |
| [logout](Android-api.md#RTCVideo-logout) | 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken](Android-api.md#RTCVideo-updatelogintoken) | 更新用户用于登录的 Token  <br><br/>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br><br/>调用 [login](Android-api.md#RTCVideo-login) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [onLoginResult](Android-callback.md#IRTCVideoEventHandler-onloginresult) 回调通知，错误码为 `LOGIN_ERROR_CODE_INVALID_TOKEN`。此时需要重新获取 Token，并调用此方法更新 Token。 |
| [setServerParams](Android-api.md#RTCVideo-setserverparams) | 设置应用服务器参数  <br><br/>客户端调用 [sendServerMessage](Android-api.md#RTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Android-api.md#RTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。 |
| [getPeerOnlineStatus](Android-api.md#RTCVideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom](Android-api.md#RTCVideo-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [sendServerMessage](Android-api.md#RTCVideo-sendservermessage) | 客户端给应用服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Android-api.md#RTCVideo-sendserverbinarymessage) | 客户端给应用服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo](Android-api.md#RTCVideo-sendstreamsyncinfo) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [onStreamSyncInfoReceived](Android-callback.md#IRTCVideoEventHandler-onstreamsyncinforeceived) 回调。 |
| [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) | 通过视频帧发送 SEI 数据。  <br><br/>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |

## CDN 推流

| 方法 | 描述 |
| --- | --- |
| [startLiveTranscoding](Android-api.md#RTCVideo-startlivetranscoding) | 新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br><br/>同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。 |
| [stopLiveTranscoding](Android-api.md#RTCVideo-stoplivetranscoding) | 停止转推直播，会收到 [onStreamMixingEvent](Android-callback#ILiveTranscodingObserver-onstreammixingevent) 回调。<br><br/>关于启动转推直播，参看 [startLiveTranscoding](Android-api.md#RTCVideo-startlivetranscoding)。 |
| [updateLiveTranscoding](Android-api.md#RTCVideo-updatelivetranscoding) | 更新转推直播参数，会收到 [onStreamMixingEvent](Android-callback#ILiveTranscodingObserver-onstreammixingevent) 回调。  <br><br/>使用 [startLiveTranscoding](Android-api.md#RTCVideo-startlivetranscoding) 启用转推直播功能后，使用此方法更新功能配置参数。 |
| [startPushSingleStreamToCDN](Android-api.md#RTCVideo-startpushsinglestreamtocdn) | 新增单流转推直播任务。 |
| [stopPushStreamToCDN](Android-api.md#RTCVideo-stoppushstreamtocdn) | 停止转推直播。<br><br/>关于启动转推直播，参看 [startPushSingleStreamToCDN](Android-api.md#RTCVideo-startpushsinglestreamtocdn)。 |

## 混音

| 方法 | 描述 |
| --- | --- |
| [enableAudioMixingFrame](Android-api.md#IAudioMixingManager-enableaudiomixingframe) | 启动 PCM 音频数据混音 |
| [disableAudioMixingFrame](Android-api.md#IAudioMixingManager-disableaudiomixingframe) | 关闭 PCM 混音 |
| [pushAudioMixingFrame](Android-api.md#IAudioMixingManager-pushaudiomixingframe) | 推送 PCM 音频帧数据用于混音 |
| [getAudioMixingManager](Android-api.md#RTCVideo-getaudiomixingmanager) | 混音管理接口创建 |
| [startAudioMixing](Android-api.md#IAudioMixingManager-startaudiomixing) | 开始播放音频文件。<br><br/>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。 |
| [stopAudioMixing](Android-api.md#IAudioMixingManager-stopaudiomixing) | 停止播放音频文件 |
| [pauseAudioMixing](Android-api.md#IAudioMixingManager-pauseaudiomixing) | 暂停播放音频文件 |
| [resumeAudioMixing](Android-api.md#IAudioMixingManager-resumeaudiomixing) | 恢复播放音频文件 |
| [setAudioMixingVolume](Android-api.md#IAudioMixingManager-setaudiomixingvolume) | 调节指定混音的音量大小，包括音频文件混音和 PCM 混音。 |
| [setAllAudioMixingVolume](Android-api.md#IAudioMixingManager-setallaudiomixingvolume) | 设置默认的混音音量大小，包括音频文件混音和 PCM 混音。 |
| [enableVocalInstrumentBalance](Android-api.md#RTCVideo-enablevocalinstrumentbalance) | 开启/关闭音量均衡功能。  <br><br/>开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 [setAudioMixingLoudness](Android-api.md#IAudioMixingManager-setaudiomixingloudness) 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。 |
| [setAudioMixingLoudness](Android-api.md#IAudioMixingManager-setaudiomixingloudness) | 如果你需要使用 `enableVocalInstrumentBalance` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。 |
| [enablePlaybackDucking](Android-api.md#RTCVideo-enableplaybackducking) | 打开/关闭音量闪避功能，适用于“一起看”等场景。  <br><br/>开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。 |
| [setAudioMixingPitch](Android-api.md#IAudioMixingManager-setaudiomixingpitch) | 开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。 |
| [getAudioMixingCurrentPosition](Android-api.md#IAudioMixingManager-getaudiomixingcurrentposition) | 获取音频文件播放进度 |
| [setAudioMixingPosition](Android-api.md#IAudioMixingManager-setaudiomixingposition) | 设置音频文件的起始播放位置。 |
| [getAudioTrackCount](Android-api.md#IAudioMixingManager-getaudiotrackcount) | 获取当前音频文件的音轨索引 |
| [getSpatialAudio](Android-api.md#RTCRoom-getspatialaudio) | 获取空间音频接口实例。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。   <br> |
| [selectAudioTrack](Android-api.md#IAudioMixingManager-selectaudiotrack) | 指定当前音频文件的播放音轨 |
| [setAudioMixingPlaybackSpeed](Android-api.md#IAudioMixingManager-setaudiomixingplaybackspeed) | 设置混音时音频文件的播放速度 |
| [setAudioMixingDualMonoMode](Android-api.md#IAudioMixingManager-setaudiomixingdualmonomode) | 设置当前音频文件的声道模式 |
| [setAudioMixingProgressInterval](Android-api.md#IAudioMixingManager-setaudiomixingprogressinterval) | 设置混音时音频文件播放进度回调的间隔 |
| [preloadAudioMixing](Android-api.md#IAudioMixingManager-preloadaudiomixing) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [unloadAudioMixing](Android-api.md#IAudioMixingManager-unloadaudiomixing) | 卸载指定音频文件 |
| [getAudioMixingDuration](Android-api.md#IAudioMixingManager-getaudiomixingduration) | 获取音频文件时长 |
| [getAudioMixingPlaybackDuration](Android-api.md#IAudioMixingManager-getaudiomixingplaybackduration) | 获取混音音频文件的实际播放时长（单位：毫秒）。 |

## 屏幕分享

| 方法 | 描述 |
| --- | --- |
| [startScreenCapture](Android-api.md#RTCVideo-startscreencapture) | 使用 RTC SDK 内部采集模块开始采集屏幕音频流和（或）视频流。 |
| [updateScreenCapture](Android-api.md#RTCVideo-updatescreencapture) | 使用 RTC SDK 内部屏幕采集后，更新采集的媒体类型。 |
| [stopScreenCapture](Android-api.md#RTCVideo-stopscreencapture) | 在屏幕共享时，停止使用 RTC SDK 内部采集方式采集屏幕音视频。 |
| [publishScreen](Android-api.md#RTCRoom-publishscreen) | 在当前所在房间内发布本地屏幕共享音视频流 |
| [unpublishScreen](Android-api.md#RTCRoom-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [setScreenAudioSourceType](Android-api.md#RTCVideo-setscreenaudiosourcetype) | 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集） |
| [setScreenAudioStreamIndex](Android-api.md#RTCVideo-setscreenaudiostreamindex) | 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式 |
| [setScreenVideoEncoderConfig](Android-api.md#RTCVideo-setscreenvideoencoderconfig) | 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [pushScreenAudioFrame](Android-api.md#RTCVideo-pushscreenaudioframe) | 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。 |
| [pushScreenFrame](Android-api.md#RTCVideo-pushscreenframe) | 推送屏幕视频帧 |
| [subscribeScreen](Android-api.md#RTCRoom-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen](Android-api.md#RTCRoom-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |

## 安全与加密

| 方法 | 描述 |
| --- | --- |
| [startCloudProxy](Android-api.md#RTCVideo-startcloudproxy) | 开启云代理 |
| [stopCloudProxy](Android-api.md#RTCVideo-stopcloudproxy) | 关闭云代理 |
| [setCustomizeEncryptHandler](Android-api.md#RTCVideo-setcustomizeencrypthandler) | 设置自定义加密方法<br/>自定义加密方法需要实现对应的加密/解密方法  <br> |
| [setEncryptInfo](Android-api.md#RTCVideo-setencryptinfo) | 设置AES加密算法和加密密钥  <br><br/>有四种内置的加密算法，为 AES-128-CBC，AES-256-CBC，AES-128-ECB，AES-256-ECB |

## 高级功能

| 方法 | 描述 |
| --- | --- |
| [startFileRecording](Android-api.md#RTCVideo-startfilerecording) | 该方法将通话过程中的音视频数据录制到本地的文件中。 |
| [stopFileRecording](Android-api.md#RTCVideo-stopfilerecording) | 停止本地录制 |
| [setEarMonitorMode](Android-api.md#RTCVideo-setearmonitormode) | 打开/关闭耳返功能。 |
| [setEarMonitorVolume](Android-api.md#RTCVideo-setearmonitorvolume) | 设置耳返音量。 |
| [getRangeAudio](Android-api.md#RTCRoom-getrangeaudio) | 获取范围语音接口实例。 |
| [startASR](Android-api.md#RTCVideo-startasr) | 开启自动语音识别服务。该方法将识别后的用户语音转化成文字，并通过 [onMessage](Android-keytype.md#IRTCASREngineEventHandler-onmessage) 事件回调给用户。 |
| [stopASR](Android-api.md#RTCVideo-stopasr) | 关闭语音识别服务 |
| [takeLocalSnapshot](Android-api.md#RTCVideo-takelocalsnapshot) | 截取本地视频画面 |
| [takeRemoteSnapshot](Android-api.md#RTCVideo-takeremotesnapshot) | 截取远端视频画面 |

## 音乐及打分

| 方法 | 描述 |
| --- | --- |
| [getKTVManager](Android-api.md#RTCVideo-getktvmanager) | 创建 KTV 管理接口。 |
| [setKTVEventHandler](Android-api.md#KTVManager-setktveventhandler) | 设置 KTV 回调接口。 |
| [setMaxCacheSize](Android-api.md#KTVManager-setmaxcachesize) | 设置歌曲文件最大占用的本地缓存。 |
| [getMusicList](Android-api.md#KTVManager-getmusiclist) | 获取歌曲列表。 |
| [searchMusic](Android-api.md#KTVManager-searchmusic) | 根据关键词搜索歌曲。 |
| [getHotMusic](Android-api.md#KTVManager-gethotmusic) | 根据热榜类别获取每个榜单的歌曲列表。 |
| [getMusicDetail](Android-api.md#KTVManager-getmusicdetail) | 获取音乐详细信息。 |
| [downloadMusic](Android-api.md#KTVManager-downloadmusic) | 下载音乐。 |
| [downloadLyric](Android-api.md#KTVManager-downloadlyric) | 下载歌词。 |
| [downloadMidi](Android-api.md#KTVManager-downloadmidi) | 下载 MIDI 文件。 |
| [cancelDownload](Android-api.md#KTVManager-canceldownload) | 取消下载任务。 |
| [clearCache](Android-api.md#KTVManager-clearcache) | 清除当前音乐缓存文件，包括音乐音频和歌词。 |
| [getKTVPlayer](Android-api.md#KTVManager-getktvplayer) | 获取 KTV 播放器。 |
| [setPlayerEventHandler](Android-api.md#KTVPlayer-setplayereventhandler) | 设置 KTV 播放器进度及状态回调接口。 |
| [playMusic](Android-api.md#KTVPlayer-playmusic) | 播放歌曲。 |
| [pauseMusic](Android-api.md#KTVPlayer-pausemusic) | 暂停播放歌曲。 |
| [resumeMusic](Android-api.md#KTVPlayer-resumemusic) | 继续播放歌曲。 |
| [stopMusic](Android-api.md#KTVPlayer-stopmusic) | 停止播放歌曲。 |
| [seekMusic](Android-api.md#KTVPlayer-seekmusic) | 设置音乐文件的起始播放位置。 |
| [setMusicVolume](Android-api.md#KTVPlayer-setmusicvolume) | 设置歌曲播放音量，只能在开始播放后进行设置。 |
| [switchAudioTrackType](Android-api.md#KTVPlayer-switchaudiotracktype) | 切换歌曲原唱伴唱。 |
| [setMusicPitch](Android-api.md#KTVPlayer-setmusicpitch) | 对播放中的音乐设置升降调信息。 |
| [getSingScoringManager](Android-api.md#RTCVideo-getsingscoringmanager) | 创建 K 歌评分管理接口。 |
| [initSingScoring](Android-api.md#ISingScoringManager-initsingscoring) | 初始化 K 歌评分。 |
| [setSingScoringConfig](Android-api.md#ISingScoringManager-setsingscoringconfig) | 设置 K 歌评分参数。 |
| [getStandardPitchInfo](Android-api.md#ISingScoringManager-getstandardpitchinfo) | 获取标准音高数据。 |
| [startSingScoring](Android-api.md#ISingScoringManager-startsingscoring) | 开始 K 歌评分。 |
| [stopSingScoring](Android-api.md#ISingScoringManager-stopsingscoring) | 停止 K 歌评分。 |
| [getLastSentenceScore](Android-api.md#ISingScoringManager-getlastsentencescore) | 获取上一句的演唱评分。调用 [startSingScoring](Android-api.md#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。 |
| [getTotalScore](Android-api.md#ISingScoringManager-gettotalscore) | 获取当前演唱总分。调用 [startSingScoring](Android-api.md#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。 |
| [getAverageScore](Android-api.md#ISingScoringManager-getaveragescore) | 获取当前演唱歌曲的平均分。 |

# 回调
## 引擎管理

| 回调 | 描述 |
| --- | --- |
| [onLogReport](Android-callback.md#IRTCVideoEventHandler-onlogreport) | 上报日志时回调该事件。 |
| [onHttpsProxyState](Android-callback.md#IRTCVideoEventHandler-onhttpsproxystate) | HTTPS 代理连接状态改变时，收到该回调。 |
| [onSocks5ProxyState](Android-callback.md#IRTCVideoEventHandler-onsocks5proxystate) | SOCKS5 代理状态改变时，收到该回调。 |
| [onSysStats](Android-callback.md#IRTCVideoEventHandler-onsysstats) | 每2秒发生回调，通知当前cpu，内存使用的信息。  <br> |
| [onWarning](Android-callback.md#IRTCVideoEventHandler-onwarning) | 发生警告回调。 |
| [onError](Android-callback.md#IRTCVideoEventHandler-onerror) | 发生错误回调。 |
| [onTokenWillExpire](Android-callback#IRTCRoomEventHandler-ontokenwillexpire) | Token 过期前 30 秒将触发该回调。<br><br/>调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。 |
| [onHttpProxyState](Android-callback.md#IRTCVideoEventHandler-onhttpproxystate) | HTTP 代理连接状态改变时，收到该回调。 |

## 房间管理

| 回调 | 描述 |
| --- | --- |
| [onRoomStateChanged](Android-callback.md#IRTCRoomEventHandler-onroomstatechanged) | 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。 |
| [onCreateRoomStateChanged](Android-callback.md#IRTCVideoEventHandler-oncreateroomstatechanged) | 创建房间失败回调。 |
| [onLeaveRoom](Android-callback#IRTCRoomEventHandler-onleaveroom) | 离开房间成功回调。  <br><br/>用户调用 [leaveRoom](Android-api.md#RTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br> |
| [onUserJoined](Android-callback#IRTCRoomEventHandler-onuserjoined) | 可见用户加入房间，或房内隐身用户切换为可见的回调。  <br><br/>1.远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br><br/>2.远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br><br/>3.房间内隐身远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br><br/>4.新进房用户也会收到进房前已在房内的主播角色用户的进房回调通知。  <br> |
| [onUserLeave](Android-callback.md#IRTCRoomEventHandler-onuserleave) | 远端用户离开房间，或切至不可见时，房间内其他用户会收到此事件 |
| [onRoomStats](Android-callback.md#IRTCRoomEventHandler-onroomstats) | 房间通话统计信息回调。  <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |

## 音频管理

| 回调 | 描述 |
| --- | --- |
| [onAudioDeviceWarning](Android-callback.md#IRTCVideoEventHandler-onaudiodevicewarning) | 音频设备警告回调。音频设备包括音频采集设备、音频渲染设备等。 |
| [onAudioRouteChanged](Android-callback.md#IRTCVideoEventHandler-onaudioroutechanged) | 音频播放路由变化时，收到该回调。 |
| [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) | 音频设备状态回调。提示音频采集、音频播放等媒体设备的状态。 |
| [onLocalAudioPropertiesReport](Android-callback#IRTCVideoEventHandler-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br><br/>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。 |
| [onRemoteAudioPropertiesReport](Android-callback#IRTCVideoEventHandler-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br><br/>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onActiveSpeaker](Android-callback#IRTCVideoEventHandler-onactivespeaker) | 调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) 后，根据设置的 `AudioPropertiesConfig.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [onUserStartAudioCapture](Android-callback#IRTCVideoEventHandler-onuserstartaudiocapture) | 房间内的用户调用 [startAudioCapture](Android-api.md#RTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。 |
| [onUserStopAudioCapture](Android-callback#IRTCVideoEventHandler-onuserstopaudiocapture) | 房间内的用户调用 [stopAudioCapture](Android-api.md#RTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。 |
| [onStreamSyncInfoReceived](Android-callback#IRTCVideoEventHandler-onstreamsyncinforeceived) | 音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Android-api.md#RTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br> |
| [onAudioStreamBanned](Android-callback.md#IRTCRoomEventHandler-onaudiostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [onAudioPlaybackDeviceTestVolume](Android-callback.md#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |

## 视频管理

| 回调 | 描述 |
| --- | --- |
| [onUserStartVideoCapture](Android-callback#IRTCVideoEventHandler-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Android-api.md#RTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。 |
| [onUserStopVideoCapture](Android-callback#IRTCVideoEventHandler-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Android-api.md#RTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。 |
| [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) | 视频设备状态回调。提示摄像头视频采集、屏幕视频采集等媒体设备的状态。 |
| [onVideoDeviceWarning](Android-callback.md#IRTCVideoEventHandler-onvideodevicewarning) | 视频设备警告回调，包括视频采集等设备。 |
| [onFaceDetectResult](Android-callback.md#IFaceDetectionObserver-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。 <br><br/>调用 [registerFaceDetectionObserver](Android-api.md#RTCVideo-registerfacedetectionobserver) 注册了 [IFaceDetectionObserver](Android-callback.md#ifacedetectionobserver)，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |

## 音视频传输

| 回调 | 描述 |
| --- | --- |
| [onStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onstreamstatechanged) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [onAVSyncStateChange](Android-callback#IRTCRoomEventHandler-onavsyncstatechange) | 发布端调用 [setMultiDeviceAVSync](Android-api.md#RTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。 |
| [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集音视频流的回调。 |
| [onUserUnpublishStream](Android-callback.md#IRTCRoomEventHandler-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onAudioFrameSendStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudioframesendstatechanged) | 本地音频首帧发送状态发生改变时，收到此回调 |
| [onVideoFrameSendStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideoframesendstatechanged) | 本地视频首帧发送状态发生改变时，收到此回调 |
| [onAudioFramePlayStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudioframeplaystatechanged) | 音频首帧播放状态发生改变时，收到此回调 |
| [onVideoFramePlayStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideoframeplaystatechanged) | 视频首帧播放状态发生改变时，收到此回调 |
| [onForwardStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [onForwardStreamEvent](Android-callback.md#IRTCRoomEventHandler-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [onLocalStreamStats](Android-callback.md#IRTCRoomEventHandler-onlocalstreamstats) | 反映通话中本地设备发送音/视频流的统计信息以及网络状况的回调。<br><br/>本地用户发布音视频流成功后，每隔 2s 收到此回调。 |
| [onRemoteStreamStats](Android-callback.md#IRTCRoomEventHandler-onremotestreamstats) | 反映通话中本地设备接收订阅的远端音/视频流的统计信息以及网络状况的回调。每隔 2s 收到此回调。 |
| [onNetworkQuality](Android-callback.md#IRTCRoomEventHandler-onnetworkquality) | 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。 |
| [onStreamSubscribed](Android-callback.md#IRTCRoomEventHandler-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onLocalAudioStateChanged](Android-callback.md#IRTCVideoEventHandler-onlocalaudiostatechanged) | 本地音频流的状态发生改变时，该回调通知当前的本地音频流状态。 |
| [onRemoteAudioStateChanged](Android-callback.md#IRTCVideoEventHandler-onremoteaudiostatechanged) | 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。 |
| [onFirstLocalAudioFrame](Android-callback.md#IRTCVideoEventHandler-onfirstlocalaudioframe) | 发布音频流时，采集到第一帧音频帧，收到该回调。 |
| [onFirstRemoteAudioFrame](Android-callback.md#IRTCVideoEventHandler-onfirstremoteaudioframe) | 接收到来自远端某音频流的第一帧时，收到该回调。 |
| [onLocalVideoStateChanged](Android-callback.md#IRTCVideoEventHandler-onlocalvideostatechanged) | 本地视频流的状态发生改变时，收到该事件。 |
| [onRemoteVideoStateChanged](Android-callback.md#IRTCVideoEventHandler-onremotevideostatechanged) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [onFirstRemoteVideoFrameRendered](Android-callback.md#IRTCVideoEventHandler-onfirstremotevideoframerendered) | SDK 内部渲染成功远端视频流首帧后，收到此回调。 |
| [onFirstLocalVideoFrameCaptured](Android-callback.md#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) | RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。 |
| [onLocalVideoSizeChanged](Android-callback.md#IRTCVideoEventHandler-onlocalvideosizechanged) | 本地预览视频大小或旋转信息发生改变时，收到此回调。 |
| [onRemoteVideoSizeChanged](Android-callback.md#IRTCVideoEventHandler-onremotevideosizechanged) | 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onFirstRemoteVideoFrameDecoded](Android-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [onVideoStreamBanned](Android-callback.md#IRTCRoomEventHandler-onvideostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [onPushPublicStreamResult](Android-callback#IRTCVideoEventHandler-onpushpublicstreamresult) | 公共流发布结果回调。<br><br/>调用 [startPushPublicStream](Android-api.md#RTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。 |
| [onPlayPublicStreamResult](Android-callback#IRTCVideoEventHandler-onplaypublicstreamresult) | 订阅公共流的结果回调  <br><br/>调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到启动结果和拉流过程中的错误。 |
| [onPublicStreamSEIMessageReceived](Android-callback#IRTCVideoEventHandler-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息<br><br/>调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的SEI消息。 |
| [onFirstPublicStreamVideoFrameDecoded](Android-callback#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) | 公共流的首帧视频解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。 |
| [onFirstPublicStreamAudioFrame](Android-callback#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。 |

## 自定义流处理

| 回调 | 描述 |
| --- | --- |
| [OnStart](Android-callback#IExternalVideoEncoderEventHandler-onstart) | 提示自定义编码帧可以开始推送的回调。  <br><br/>收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Android-api.md#RTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧 |
| [OnStop](Android-callback.md#IExternalVideoEncoderEventHandler-onstop) | 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧 |
| [OnRateUpdate](Android-callback.md#IExternalVideoEncoderEventHandler-onrateupdate) | 当自定义编码流的帧率或码率发生变化时，触发该回调 |
| [OnRequestKeyFrame](Android-callback.md#IExternalVideoEncoderEventHandler-onrequestkeyframe) | 提示流发布端需重新生成关键帧的回调 |
| [onLocalEncodedVideoFrame](Android-callback#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) | 调用 [registerLocalEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。 |
| [OnRemoteEncodedVideoFrame](Android-callback#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) | 调用 [registerRemoteEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调 |
| [onRecordAudioFrame](Android-callback.md#IAudioFrameObserver-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame](Android-callback.md#IAudioFrameObserver-onplaybackaudioframe) | 返回订阅的远端所有用户混音后的音频数据 |
| [onRemoteUserAudioFrame](Android-callback.md#IAudioFrameObserver-onremoteuseraudioframe) | 返回远端单个用户的音频数据 |
| [onMixedAudioFrame](Android-callback.md#IAudioFrameObserver-onmixedaudioframe) | 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据 |

## 网络管理

| 回调 | 描述 |
| --- | --- |
| [onPerformanceAlarms](Android-callback.md#IRTCVideoEventHandler-onperformancealarms) | 本地未开启发布性能回退，检测到设备性能不足时，收到此回调。  <br><br/>本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。 |
| [onSimulcastSubscribeFallback](Android-callback.md#IRTCVideoEventHandler-onsimulcastsubscribefallback) | 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。 |
| [onNetworkDetectionResult](Android-callback#IRTCVideoEventHandler-onnetworkdetectionresult) | 通话前网络探测结果。  <br><br/>成功调用 [startNetworkDetection](Android-api.md#RTCVideo-startnetworkdetection) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [onNetworkDetectionStopped](Android-callback#IRTCVideoEventHandler-onnetworkdetectionstopped) | 通话前网络探测结束<br/>以下情况将停止探测并收到本一次本回调：<br><br/>1. 当调用 [stopNetworkDetection](Android-api.md#RTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；<br/>2. 当收到远端/本端音频首帧后，停止探测；<br/>3. 当探测超过3分钟后，停止探测；<br/>4. 当探测链路断开一定时间之后，停止探测。 |
| [onConnectionStateChanged](Android-callback.md#IRTCVideoEventHandler-onconnectionstatechanged) | 回调 SDK 与信令服务器连接状态相关事件。当 SDK 与信令服务器的网络连接状态改变时回调该事件。 |
| [onNetworkTypeChanged](Android-callback.md#IRTCVideoEventHandler-onnetworktypechanged) | SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。 |
| [onSEIMessageReceived](Android-callback#IRTCVideoEventHandler-onseimessagereceived) | 收到通过调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 发送带有 SEI 消息的视频帧时，收到此回调 |
| [onEchoTestResult](Android-callback.md#IRTCVideoEventHandler-onechotestresult) | 关于音视频回路测试结果的回调。 |

## 消息

| 回调 | 描述 |
| --- | --- |
| [onRoomMessageReceived](Android-callback#IRTCRoomEventHandler-onroommessagereceived) | 接收到房间内广播消息的回调。<br><br/>房间内其他用户调用 [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) 发送广播消息时，收到此回调。 |
| [onRoomBinaryMessageReceived](Android-callback#IRTCRoomEventHandler-onroombinarymessagereceived) | 接收到房间内广播二进制消息的回调。<br><br/>房间内其他用户调用 [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) 发送广播二进制消息时，收到此回调。 |
| [onUserMessageReceived](Android-callback#IRTCRoomEventHandler-onusermessagereceived) | 收到来自房间中其他用户通过 [sendUserMessage](Android-api.md#RTCRoom-sendusermessage) 发来的点对点文本消息时，会收到此回调。 |
| [onUserBinaryMessageReceived](Android-callback#IRTCRoomEventHandler-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 [sendUserBinaryMessage](Android-api.md#RTCRoom-senduserbinarymessage) 发来的点对点二进制消息时，会收到此回调。 |
| [onUserMessageSendResult](Android-callback.md#IRTCRoomEventHandler-onusermessagesendresult) | 向房间内单个用户发送点对点文本或点对点二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onRoomMessageSendResult](Android-callback#IRTCRoomEventHandler-onroommessagesendresult) | 调用 [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) 或 [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onLoginResult](Android-callback.md#IRTCVideoEventHandler-onloginresult) | 登录结果回调 |
| [onLogout](Android-callback.md#IRTCVideoEventHandler-onlogout) | 登出结果回调 |
| [onServerParamsSetResult](Android-callback.md#IRTCVideoEventHandler-onserverparamssetresult) | 设置应用服务器参数的返回结果 |
| [onGetPeerOnlineStatus](Android-callback.md#IRTCVideoEventHandler-ongetpeeronlinestatus) | 查询对端或本端用户登录状态的返回结果 |
| [onUserMessageReceivedOutsideRoom](Android-callback#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调 |
| [onUserBinaryMessageReceivedOutsideRoom](Android-callback#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Android-api.md#RTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调 |
| [onUserMessageSendResultOutsideRoom](Android-callback.md#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) | 给房间外指定的用户发送消息的回调 |
| [onServerMessageSendResult](Android-callback.md#IRTCVideoEventHandler-onservermessagesendresult) | 给应用服务器发送消息的回调。 |

## CDN 推流

| 回调 | 描述 |
| --- | --- |
| [onStreamMixingEvent](Android-callback.md#ILiveTranscodingObserver-onstreammixingevent) | 转推直播状态回调 |
| [isSupportClientPushStream](Android-callback.md#ILiveTranscodingObserver-issupportclientpushstream) | 是否具有推流能力。  <br><br/>+ false：不具备推流能力（默认值）  <br><br/>+ true：具备推流能力 |
| [onMixingAudioFrame](Android-callback.md#ILiveTranscodingObserver-onmixingaudioframe) | 端云一体合流音频 PCM 回调 |
| [onMixingVideoFrame](Android-callback.md#ILiveTranscodingObserver-onmixingvideoframe) | 端云一体合流视频 YUV 回调 |
| [onDataFrame](Android-callback.md#ILiveTranscodingObserver-ondataframe) | 端云一体合流视频 SEI 数据回调 |

## 混音

| 回调 | 描述 |
| --- | --- |
| [onAudioMixingStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiomixingstatechanged) | 音频混音文件播放状态改变时回调 |
| [onAudioMixingPlayingProgress](Android-callback.md#IRTCVideoEventHandler-onaudiomixingplayingprogress) | 混音音频文件播放进度回调 |

## 屏幕分享

| 回调 | 描述 |
| --- | --- |
| [onUserPublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onScreenVideoFrameSendStateChanged](Android-callback.md#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) | 屏幕共享流的视频首帧发送状态发生改变时，收到此回调 |
| [onScreenVideoFramePlayStateChanged](Android-callback.md#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) | 屏幕共享流视频首帧播放状态发生改变时，收到此回调 |

## 安全与加密

| 回调 | 描述 |
| --- | --- |
| [onCloudProxyConnected](Android-callback#IRTCVideoEventHandler-oncloudproxyconnected) | 调用 [startCloudProxy](Android-api.md#RTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onEncryptData](Android-callback.md#IRTCEncryptionHandler-onencryptdata) | 自定义加密 |
| [onDecryptData](Android-callback.md#IRTCEncryptionHandler-ondecryptdata) | 自定义解密 |

## 高级功能

| 回调 | 描述 |
| --- | --- |
| [onRecordingStateUpdate](Android-callback#IRTCVideoEventHandler-onrecordingstateupdate) | 获取本地录制状态回调。  <br><br/>该回调由 [startFileRecording](Android-api.md#RTCVideo-startfilerecording) 或 [stopFileRecording](Android-api.md#RTCVideo-stopfilerecording) 触发。 |
| [onRecordingProgressUpdate](Android-callback#IRTCVideoEventHandler-onrecordingprogressupdate) | 本地录制进度回调。  <br><br/>该回调由 [startFileRecording](Android-api.md#RTCVideo-startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。 |
| [onRangeAudioInfo](Android-callback#IRangeAudioObserver-onrangeaudioinfo) | 关于当前范围语音衰减系数的回调。  <br><br/>手动订阅的场景下，房间内任一用户调用 [updatePosition](Android-api.md#IRangeAudio-updateposition) 更新自身位置或调用 [updateReceiveRange](Android-api.md#IRangeAudio-updatereceiverange) 更新语音接收范围时，该用户与房间内其他用户的相对距离都会发生改变，据此计算的衰减系数也会发生改变，并通过该回调通知用户。 <br><br/>你可以通过关注该回调中包含的远端用户的衰减系数决定是否订阅该远端用户的流。 |
| [onTakeLocalSnapshotResult](Android-callback#ISnapshotResultCallback-ontakelocalsnapshotresult) | 调用 [takeLocalSnapshot](Android-api.md#RTCVideo-takelocalsnapshot) 截取视频画面时，收到此回调。 |
| [onTakeRemoteSnapshotResult](Android-callback#ISnapshotResultCallback-ontakeremotesnapshotresult) | 调用 [takeRemoteSnapshot](Android-api.md#RTCVideo-takeremotesnapshot) 截取视频画面时，收到此回调。 |

## 音乐及打分

| 回调 | 描述 |
| --- | --- |
| [onMusicListResult](Android-callback.md#IKTVEventHandler-onmusiclistresult) | 歌曲列表回调。 |
| [onSearchMusicResult](Android-callback.md#IKTVEventHandler-onsearchmusicresult) | 搜索歌曲结果回调。 |
| [onHotMusicResult](Android-callback.md#IKTVEventHandler-onhotmusicresult) | 热榜歌曲结果回调。 |
| [onMusicDetailResult](Android-callback.md#IKTVEventHandler-onmusicdetailresult) | 歌曲详细信息回调。 |
| [onDownloadSuccess](Android-callback.md#IKTVEventHandler-ondownloadsuccess) | 下载成功回调。 |
| [onDownloadFail](Android-callback.md#IKTVEventHandler-ondownloadfail) | 下载失败回调。 |
| [onDownloadMusicProgress](Android-callback.md#IKTVEventHandler-ondownloadmusicprogress) | 歌曲文件下载进度回调。 |
| [onPlayProgress](Android-callback.md#IKTVPlayerEventHandler-onplayprogress) | 音乐播放进度回调。 |
| [onPlayStateChange](Android-callback.md#IKTVPlayerEventHandler-onplaystatechange) | 音乐播放状态改变回调。 |
| [onCurrentScoringInfo](Android-callback#ISingScoringEventHandler-oncurrentscoringinfo) | 实时评分信息回调。调用 [startSingScoring](Android-api.md#ISingScoringManager-startsingscoring) 后，会收到该回调。 |