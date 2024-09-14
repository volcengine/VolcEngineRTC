---
is_dir: False    # True for dir; False for doc
status: 1    # 0 for offline; 1 for online; 2 for whitelist; 4 for online but hidden in TOC
keywords: 实时音视频    # use ',' as separator
---

# 方法
## 引擎管理
| 方法 | 描述 |
| --- | --- |
| [createRTCVideo](Android-api#RTCVideo-creatertcvideo) | 创建引擎对象。<br/>如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。 <br/>如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。 |
| [destroyRTCVideo](Android-api#RTCVideo-destroyrtcvideo) | 销毁由 [createRTCVideo](Android-api#RTCVideo-creatertcvideo) 所创建的引擎实例，并释放所有相关资源。<br> |
| [getSDKVersion](Android-api#RTCVideo-getsdkversion) | 获取 SDK 当前的版本号。 |
| [feedback](Android-api#RTCVideo-feedback) | 将用户反馈的问题上报到 RTC。 |
| [getErrorDescription](Android-api#RTCVideo-geterrordescription) | 获取 SDK 内各种错误码、警告码的描述文字。 |
| [setRtcVideoEventHandler](Android-api#RTCVideo-setrtcvideoeventhandler) | 设置引擎事件回调的接收类，必须继承自 [IRTCVideoEventHandler](Android-callback#irtcvideoeventhandler) 。 |
| [setBusinessId](Android-api#RTCVideo-setbusinessid) | 设置业务标识参数  <br><br/>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setRuntimeParameters](Android-api#RTCVideo-setruntimeparameters) | 设置运行时的参数 |
| [setLogConfig](Android-api#RTCVideo-setlogconfig) | 配置 SDK 本地日志参数，包括日志级别、存储路径、日志文件最大占用的总空间、日志文件名前缀。 |
## 房间管理
| 方法 | 描述 |
| --- | --- |
| [createRTCRoom](Android-api#RTCVideo-creatertcroom) | 创建房间实例。<br/>调用此方法仅返回一个房间实例，你仍需调用 [joinRoom](Android-api#RTCRoom-joinroom) 才能真正地创建/加入房间。<br/>多次调用此方法以创建多个 [RTCRoom](Android-api#rtcroom) 实例。分别调用各 RTCRoom 实例中的 [joinRoom](Android-api#RTCRoom-joinroom) 方法，同时加入多个房间。<br/>多房间模式下，用户可以同时订阅各房间的音视频流。 |
| [destroy](Android-api#RTCRoom-destroy) | 退出并销毁调用 [createRTCRoom](Android-api#RTCVideo-creatertcroom) 所创建的房间实例。 |
| [setRTCRoomEventHandler](Android-api#RTCRoom-setrtcroomeventhandler) | 通过设置 [RTCRoom](Android-api#rtcroom) 对象的事件句柄，监听此对象对应的回调事件。 |
| [joinRoom](Android-api#RTCRoom-joinroom) | 加入房间。<br><br/>调用 [createRTCRoom](Android-api#RTCVideo-creatertcroom) 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br> |
| [setRoomExtraInfo](Android-api#RTCRoom-setroomextrainfo) | 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。 |
| [leaveRoom](Android-api#RTCRoom-leaveroom) | 离开房间。  <br><br/>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br><br/>此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 [onLeaveRoom](Android-callback#IRTCRoomEventHandler-onleaveroom) 回调通知。  <br> |
| [setUserVisibility](Android-api#RTCRoom-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br/>默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，最多 30 人可同时上麦。更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。 |
| [updateToken](Android-api#RTCRoom-updatetoken) | 更新 Token。<br/>收到 [onTokenWillExpire](Android-callback#IRTCRoomEventHandler-ontokenwillexpire)，[onPublishPrivilegeTokenWillExpire](Android-callback#IRTCRoomEventHandler-onpublishprivilegetokenwillexpire)， 或 [onSubscribePrivilegeTokenWillExpire](Android-callback#IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire) 时，你必须重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。 |
## 音频管理
| 方法 | 描述 |
| --- | --- |
| [setDefaultAudioRoute](Android-api#RTCVideo-setdefaultaudioroute) | 将默认的音频播放设备设置为听筒或扬声器。 |
| [setAudioRoute](Android-api#RTCVideo-setaudioroute) | 强制切换当前的音频播放路由。默认使用 [setDefaultAudioRoute](Android-api#RTCVideo-setdefaultaudioroute) 中设置的音频路由。<br/>音频播放路由发生变化时，会收到 [onAudioRouteChanged](Android-callback#IRTCVideoEventHandler-onaudioroutechanged) 回调。 |
| [getAudioRoute](Android-api#RTCVideo-getaudioroute) | 获取当前使用的音频播放路由。  <br> |
| [setCaptureVolume](Android-api#RTCVideo-setcapturevolume) | 调节音频采集音量 |
| [setPlaybackVolume](Android-api#RTCVideo-setplaybackvolume) | 调节本地播放的所有远端用户音频混音后的音量，混音内容包括远端人声、音乐、音效等。<br><br/>播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume](Android-api#RTCVideo-setremoteaudioplaybackvolume) | 调节来自指定远端用户的音频播放音量。 |
| [setRemoteRoomAudioPlaybackVolume](Android-api#RTCRoom-setremoteroomaudioplaybackvolume) | 调节某个房间内所有远端用户的音频播放音量。 |
| [enableAudioPropertiesReport](Android-api#RTCVideo-enableaudiopropertiesreport) | 启用音频信息提示。开启提示后，你可以收到 [onLocalAudioPropertiesReport](Android-callback#IRTCVideoEventHandler-onlocalaudiopropertiesreport)，[onRemoteAudioPropertiesReport](Android-callback#IRTCVideoEventHandler-onremoteaudiopropertiesreport) 和 [onActiveSpeaker](Android-callback#IRTCVideoEventHandler-onactivespeaker)。 |
| [startAudioCapture](Android-api#RTCVideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法开启后，本地用户会收到 [onAudioDeviceStateChanged](Android-callback#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Android-callback#IRTCVideoEventHandler-onuserstartaudiocapture) 的回调。 |
| [stopAudioCapture](Android-api#RTCVideo-stopaudiocapture) | 立即关闭内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法，本地用户会收到 [onAudioDeviceStateChanged](Android-callback#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [onUserStopAudioCapture](Android-callback#IRTCVideoEventHandler-onuserstopaudiocapture) 的回调。 |
| [setAudioScenario](Android-api#RTCVideo-setaudioscenario) | 设置音频场景类型。<br/>你可以根据你的应用所在场景，选择合适的音频场景类型。<br/>选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量，并同步变更对应音频相关的算法配置和采集配置。 |
| [setAudioProfile](Android-api#RTCVideo-setaudioprofile) | 设置音质档位。<br><br/>当所选的 [ChannelProfile](Android-keytype#channelprofile) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。 |
| [enableExternalSoundCard](Android-api#RTCVideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |
| [getAudioDeviceManager](Android-api#RTCVideo-getaudiodevicemanager) | 获取音频设备管理接口 |
| [startAudioPlaybackDeviceTest](Android-api#IRTCAudioDeviceManager-startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。 |
| [stopAudioPlaybackDeviceTest](Android-api#IRTCAudioDeviceManager-stopaudioplaybackdevicetest) | 停止音频播放测试。 |
| [startAudioDeviceRecordTest](Android-api#IRTCAudioDeviceManager-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br> |
| [stopAudioDeviceRecordAndPlayTest](Android-api#IRTCAudioDeviceManager-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br><br/>调用 [startAudioDeviceRecordTest](Android-api#IRTCAudioDeviceManager-startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
| [stopAudioDevicePlayTest](Android-api#IRTCAudioDeviceManager-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Android-api#IRTCAudioDeviceManager-startaudiodevicerecordtest) 开始的音频播放设备测试。<br/>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |
| [startHardwareEchoDetection](Android-api#RTCVideo-starthardwareechodetection) | 开启通话前回声检测 |
| [stopHardwareEchoDetection](Android-api#RTCVideo-stophardwareechodetection) | 停止通话前回声检测 |
## 视频管理
| 方法 | 描述 |
| --- | --- |
| [getVideoDeviceManager](Android-api#RTCVideo-getvideodevicemanager) | 创建视频设备管理实例 |
| [enumerateVideoCaptureDevices](Android-api#IVideoDeviceManager-enumeratevideocapturedevices) | 获取当前系统内视频采集设备列表。 |
| [setVideoCaptureDevice](Android-api#IVideoDeviceManager-setvideocapturedevice) | 设置当前视频采集设备 |
| [startVideoCapture](Android-api#RTCVideo-startvideocapture) | 立即开启内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Android-callback#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 [onUserStartVideoCapture](Android-callback#IRTCVideoEventHandler-onuserstartvideocapture) 的回调。 |
| [stopVideoCapture](Android-api#RTCVideo-stopvideocapture) | 立即关闭内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br/>调用该方法，本地用户会收到 [onVideoDeviceStateChanged](Android-callback#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Android-callback#IRTCVideoEventHandler-onuserstopvideocapture) 的回调。 |
| [setVideoCaptureConfig](Android-api#RTCVideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。<br><br/>如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。 |
| [setVideoRotationMode](Android-api#RTCVideo-setvideorotationmode) | 设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br><br/>接收端渲染视频时，将按照和发送端相同的方式进行旋转。<br> |
| [setLocalVideoCanvas](Android-api#RTCVideo-setlocalvideocanvas) | 设置本地视频渲染时使用的视图，并设置渲染模式。 |
| [updateLocalVideoCanvas](Android-api#RTCVideo-updatelocalvideocanvas) | 修改本地视频渲染模式和背景色。 |
| [setRemoteVideoCanvas](Android-api#RTCVideo-setremotevideocanvas) | 渲染来自指定远端用户的视频流时，设置使用的视图和渲染模式。<br><br/>要解除绑定，将 `videoCanvas` 设置为空。 |
| [updateRemoteStreamVideoCanvas](Android-api#RTCVideo-updateremotestreamvideocanvas) | 使用 SDK 内部渲染时，修改远端视频帧的渲染设置，包括渲染模式、背景颜色和旋转角度。 |
| [switchCamera](Android-api#RTCVideo-switchcamera) | 切换视频内部采集时使用的前置/后置摄像头 <br><br/>调用此接口后，在本地会触发 [onVideoDeviceStateChanged](Android-callback#IRTCVideoEventHandler-onvideodevicestatechanged) 回调。 |
| [isCameraZoomSupported](Android-api#RTCVideo-iscamerazoomsupported) | 检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。 |
| [getCameraZoomMaxRatio](Android-api#RTCVideo-getcamerazoommaxratio) | 获取当前使用的摄像头（前置/后置）的最大变焦倍数 |
| [setCameraZoomRatio](Android-api#RTCVideo-setcamerazoomratio) | 设置当前使用的摄像头（前置/后置）的光学变焦倍数 |
| [isCameraTorchSupported](Android-api#RTCVideo-iscameratorchsupported) | 检测当前使用的摄像头（前置/后置），是否支持闪光灯。 |
| [setCameraTorch](Android-api#RTCVideo-setcameratorch) | 打开/关闭当前使用的摄像头（前置/后置）的闪光灯 |
| [isCameraFocusPositionSupported](Android-api#RTCVideo-iscamerafocuspositionsupported) | 检查当前使用的摄像头是否支持手动对焦。 |
| [setCameraFocusPosition](Android-api#RTCVideo-setcamerafocusposition) | 设置当前使用的摄像头的对焦点。 |
| [isCameraExposurePositionSupported](Android-api#RTCVideo-iscameraexposurepositionsupported) | 检查当前使用的摄像头是否支持手动设置曝光点。 |
| [setCameraExposurePosition](Android-api#RTCVideo-setcameraexposureposition) | 设置当前使用的摄像头的曝光点 |
| [setCameraExposureCompensation](Android-api#RTCVideo-setcameraexposurecompensation) | 设置当前使用的摄像头的曝光补偿。 |
| [setVideoEncoderConfig](Android-api#RTCVideo-setvideoencoderconfig-3) | 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig-5) |
| [setVideoEncoderConfig](Android-api#RTCVideo-setvideoencoderconfig-5) | 视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
## 音视频传输
| 方法 | 描述 |
| --- | --- |
| [publishStream](Android-api#RTCRoom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream](Android-api#RTCRoom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [setDummyCaptureImagePath](Android-api#RTCVideo-setdummycaptureimagepath) | 摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。<br/>调用 `stopVideoCapture` 接口时，会开始推静态图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。<br/>可重复调用该接口来更新图片。 |
| [subscribeStream](Android-api#RTCRoom-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream](Android-api#RTCRoom-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreams](Android-api#RTCRoom-subscribeallstreams) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreams](Android-api#RTCRoom-unsubscribeallstreams) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br><br/>自动订阅和手动订阅的流都可以通过本方法取消订阅。 |
| [pauseAllSubscribedStream](Android-api#RTCRoom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Android-api#RTCRoom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [requestRemoteVideoKeyFrame](Android-api#RTCVideo-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [startForwardStreamToRooms](Android-api#RTCRoom-startforwardstreamtorooms) | 开始跨房间转发媒体流。<br/>在调用 [joinRoom](Android-api#RTCRoom-joinroom) 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br> |
| [updateForwardStreamToRooms](Android-api#RTCRoom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br><br/>通过 [startForwardStreamToRooms](Android-api#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br/>调用本方法增加或删减房间后，将在本端触发 [onForwardStreamStateChanged](Android-callback#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。 |
| [stopForwardStreamToRooms](Android-api#RTCRoom-stopforwardstreamtorooms) | 停止跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Android-api#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。 |
| [pauseForwardStreamToAllRooms](Android-api#RTCRoom-pauseforwardstreamtoallrooms) | 暂停跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Android-api#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br/>调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](Android-api#RTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。 |
| [resumeForwardStreamToAllRooms](Android-api#RTCRoom-resumeforwardstreamtoallrooms) | 恢复跨房间媒体流转发。<br/>调用 [pauseForwardStreamToAllRooms](Android-api#RTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。 |
| [setMultiDeviceAVSync](Android-api#RTCRoom-setmultideviceavsync) | 设置发流端音画同步。  <br><br/>当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。 |
| [startPushPublicStream](Android-api#RTCVideo-startpushpublicstream) | 发布一路公共流<br><br/>用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream](Android-api#RTCVideo-startplaypublicstream) 获取和播放指定的公共流。 |
| [stopPushPublicStream](Android-api#RTCVideo-stoppushpublicstream) | 停止发布当前用户发布的公共流<br><br/>关于发布公共流，查看 [startPushPublicStream](Android-api#RTCVideo-startpushpublicstream) |
| [updatePublicStreamParam](Android-api#RTCVideo-updatepublicstreamparam) | 更新公共流参数<br><br/>关于发布公共流，查看 [startPushPublicStream](Android-api#RTCVideo-startpushpublicstream)。 |
| [startPlayPublicStream](Android-api#RTCVideo-startplaypublicstream) | 订阅指定公共流<br><br/>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream](Android-api#RTCVideo-stopplaypublicstream) | 取消订阅指定公共流<br><br/>关于订阅公共流，查看 [startPlayPublicStream](Android-api#RTCVideo-startplaypublicstream)。 |
| [setPublicStreamVideoCanvas](Android-api#RTCVideo-setpublicstreamvideocanvas) | 为指定公共流绑定内部渲染视图。  <br> |
| [setPublicStreamVideoSink](Android-api#RTCVideo-setpublicstreamvideosink) | 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。 |
| [setPublicStreamAudioPlaybackVolume](Android-api#RTCVideo-setpublicstreamaudioplaybackvolume) | 调节公共流的音频播放音量。 |
## 视频处理
| 方法 | 描述 |
| --- | --- |
| [setLocalVideoMirrorType](Android-api#RTCVideo-setlocalvideomirrortype) | 为采集到的视频流开启镜像 |
| [setRemoteVideoMirrorType](Android-api#RTCVideo-setremotevideomirrortype) | 使用内部渲染时，为远端流开启镜像。 |
| [setVideoOrientation](Android-api#RTCVideo-setvideoorientation) | 在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。<br/>移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。 |
| [setVideoWatermark](Android-api#RTCVideo-setvideowatermark) | 在指定视频流上添加水印。 |
| [clearVideoWatermark](Android-api#RTCVideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [enableEffectBeauty](Android-api#RTCVideo-enableeffectbeauty) | 开启/关闭基础美颜。 |
| [setBeautyIntensity](Android-api#RTCVideo-setbeautyintensity) | 调整基础美颜强度 |
| [getVideoEffectInterface](Android-api#RTCVideo-getvideoeffectinterface) | 获取视频特效接口。 |
| [initCVResource](Android-api#IVideoEffect-initcvresource) | 检查视频特效证书，设置算法模型路径，并初始化特效模块。 |
| [enableVideoEffect](Android-api#IVideoEffect-enablevideoeffect) | 开启高级美颜、滤镜等视频特效。 |
| [disableVideoEffect](Android-api#IVideoEffect-disablevideoeffect) | 关闭视频特效。 |
| [setEffectNodes](Android-api#IVideoEffect-seteffectnodes) | 设置视频特效素材包。 |
| [updateEffectNode](Android-api#IVideoEffect-updateeffectnode) | 设置特效强度。 |
| [setColorFilter](Android-api#IVideoEffect-setcolorfilter) | 设置颜色滤镜。 |
| [setColorFilterIntensity](Android-api#IVideoEffect-setcolorfilterintensity) | 设置已启用颜色滤镜的强度。 |
| [enableVirtualBackground](Android-api#IVideoEffect-enablevirtualbackground) | 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。 |
| [disableVirtualBackground](Android-api#IVideoEffect-disablevirtualbackground) | 关闭虚拟背景。 |
| [enableFaceDetection](Android-api#IVideoEffect-enablefacedetection) | 开启人脸识别功能，并设置人脸检测结果回调观察者。<br/>此观察者后，你会周期性收到 [onFaceDetectResult](Android-callback#IFaceDetectionObserver-onfacedetectresult) 回调。 |
| [disableFaceDetection](Android-api#IVideoEffect-disablefacedetection) | 关闭人脸识别功能。 |
| [setVideoDigitalZoomConfig](Android-api#RTCVideo-setvideodigitalzoomconfig) | 设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。 |
| [setVideoDigitalZoomControl](Android-api#RTCVideo-setvideodigitalzoomcontrol) | 控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。 |
| [startVideoDigitalZoomControl](Android-api#RTCVideo-startvideodigitalzoomcontrol) | 开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。 |
| [stopVideoDigitalZoomControl](Android-api#RTCVideo-stopvideodigitalzoomcontrol) | 停止本地摄像头持续数码变焦。 |
## 音频处理
| 方法 | 描述 |
| --- | --- |
| [setVoiceChangerType](Android-api#RTCVideo-setvoicechangertype) | 设置变声特效类型 |
| [setVoiceReverbType](Android-api#RTCVideo-setvoicereverbtype) | 设置混响特效类型 |
| [setLocalVoicePitch](Android-api#RTCVideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |
| [setLocalVoiceEqualization](Android-api#RTCVideo-setlocalvoiceequalization) | 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [setLocalVoiceReverbParam](Android-api#RTCVideo-setlocalvoicereverbparam) | 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [enableLocalVoiceReverb](Android-api#RTCVideo-enablelocalvoicereverb) | 开启本地音效混响效果 |
## 自定义流处理
| 方法 | 描述 |
| --- | --- |
| [setVideoSourceType](Android-api#RTCVideo-setvideosourcetype) | 设置向 SDK 输入的视频源，包括屏幕流<br/>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br> |
| [pushExternalVideoFrame](Android-api#RTCVideo-pushexternalvideoframe) | 推送外部视频帧。 |
| [setLocalVideoRender](Android-api#RTCVideo-setlocalvideorender) | 将本地视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。 |
| [setRemoteVideoRender](Android-api#RTCVideo-setremotevideorender) | 将远端视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。 |
| [registerRemoteEncodedVideoFrameObserver](Android-api#RTCVideo-registerremoteencodedvideoframeobserver) | 注册远端编码后视频数据回调。  <br><br/>完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame](Android-callback#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调 |
| [setVideoDecoderConfig](Android-api#RTCVideo-setvideodecoderconfig) | 在订阅远端视频流之前，设置远端视频数据解码方式 |
| [setAudioSourceType](Android-api#RTCVideo-setaudiosourcetype) | 切换音频采集方式 |
| [setAudioRenderType](Android-api#RTCVideo-setaudiorendertype) | 切换音频渲染方式 |
| [pushExternalAudioFrame](Android-api#RTCVideo-pushexternalaudioframe) | 推送自定义采集的音频数据到 RTC SDK。 |
| [pullExternalAudioFrame](Android-api#RTCVideo-pullexternalaudioframe) | 拉取下行音频数据用于自定义音频渲染。<br/>调用该方法后，SDK 会主动拉取待播放的音频数据，包括远端已解码和混音后的音频数据，用于外部播放。 |
| [registerLocalVideoProcessor](Android-api#RTCVideo-registerlocalvideoprocessor) | 设置自定义视频前处理器。<br><br/>使用这个视频前处理器，你能够调用 [processVideoFrame](Android-api#IVideoProcessor-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。 |
| [processVideoFrame](Android-api#IVideoProcessor-processvideoframe) | 获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor](Android-api#RTCVideo-registerlocalvideoprocessor) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。 |
| [onGLEnvInitiated](Android-api#IVideoProcessor-onglenvinitiated) | OpenGL 环境创建完成时，收到此回调。 |
| [onGLEnvRelease](Android-api#IVideoProcessor-onglenvrelease) | OpenGL 环境即将销毁时，收到此回调。此时，你可以释放纹理等资源。 |
| [registerAudioProcessor](Android-api#RTCVideo-registeraudioprocessor) | 注册自定义音频处理器。<br><br/>注册完成后，你可以调用 [enableAudioProcessor](Android-api#RTCVideo-enableaudioprocessor)，对本地采集到的音频进行处理，RTC SDK 将对处理后的音频进行编码和发送。也可以对接收到的远端音频进行自定义处理，RTC SDK 将对处理后的音频进行渲染。 |
| [enableAudioProcessor](Android-api#RTCVideo-enableaudioprocessor) | 设置并开启指定的音频帧回调，进行自定义处理。 |
| [disableAudioProcessor](Android-api#RTCVideo-disableaudioprocessor) | 关闭自定义音频处理。 |
| [registerAudioFrameObserver](Android-api#RTCVideo-registeraudioframeobserver) | 注册音频数据回调观察者。  <br> |
| [enableAudioFrameCallback](Android-api#RTCVideo-enableaudioframecallback) | 设置并开启指定的音频数据帧回调 |
| [disableAudioFrameCallback](Android-api#RTCVideo-disableaudioframecallback) | 关闭音频回调 |
| [registerLocalEncodedVideoFrameObserver](Android-api#RTCVideo-registerlocalencodedvideoframeobserver) | 注册本地视频帧监测器。  <br><br/>无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame](Android-callback#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) 回调给用户。 |
| [setExternalVideoEncoderEventHandler](Android-api#RTCVideo-setexternalvideoencodereventhandler) | 注册自定义编码帧推送事件回调 |
| [pushExternalEncodedVideoFrame](Android-api#RTCVideo-pushexternalencodedvideoframe) | 推送自定义编码后的视频流 |
## 网络管理
| 方法 | 描述 |
| --- | --- |
| [enableSimulcastMode](Android-api#RTCVideo-enablesimulcastmode) | 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。 |
| [setRemoteVideoConfig](Android-api#RTCRoom-setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [setPublishFallbackOption](Android-api#RTCVideo-setpublishfallbackoption) | 设置发布的音视频流的回退选项。  <br><br/>你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。 |
| [setSubscribeFallbackOption](Android-api#RTCVideo-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。 <br><br/>你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority](Android-api#RTCVideo-setremoteuserpriority) | 设置用户优先级。 |
| [startNetworkDetection](Android-api#RTCVideo-startnetworkdetection) | 开启通话前网络探测 |
| [stopNetworkDetection](Android-api#RTCVideo-stopnetworkdetection) | 停止通话前网络探测 |
| [startEchoTest](Android-api#RTCVideo-startechotest) | 开启音视频回路测试。  <br><br/>在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br><br/>开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。 |
| [stopEchoTest](Android-api#RTCVideo-stopechotest) | 停止音视频回路测试。  <br><br/>调用 [startEchoTest](Android-api#RTCVideo-startechotest) 开启音视频回路检测后，你必须调用该方法停止检测。 |
| [getNetworkTimeInfo](Android-api#RTCVideo-getnetworktimeinfo) | 通过 NTP 协议，获取网络时间。 |
| [setCellularEnhancement](Android-api#RTCVideo-setcellularenhancement) | 启用蜂窝网络辅助增强，改善通话质量。 |
## 消息
| 方法 | 描述 |
| --- | --- |
| [sendRoomMessage](Android-api#RTCRoom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [sendRoomBinaryMessage](Android-api#RTCRoom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [sendUserMessage](Android-api#RTCRoom-sendusermessage) | 给房间内指定的用户发送点对点文本消息（P2P）。 |
| [sendUserBinaryMessage](Android-api#RTCRoom-senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息（P2P）。 |
| [login](Android-api#RTCVideo-login) | 登录 RTS 服务器。<br> 必须先登录，才能调用 [sendUserMessageOutsideRoom](Android-api#RTCVideo-sendusermessageoutsideroom) 和 [sendServerMessage](Android-api#RTCVideo-sendservermessage) 发送房间外点对点消息和向应用服务器发送消息 <br><br/>在调用本接口登录后，如果想要登出，需要调用 [logout](Android-api#RTCVideo-logout)。  <br> |
| [logout](Android-api#RTCVideo-logout) | 登出 RTS 服务器。<br> 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken](Android-api#RTCVideo-updatelogintoken) | 更新用户用于登录的 Token  <br><br/>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br><br/>调用 [login](Android-api#RTCVideo-login) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [onLoginResult](Android-callback#IRTCVideoEventHandler-onloginresult) 回调通知，错误码为 `LOGIN_ERROR_CODE_INVALID_TOKEN`。此时需要重新获取 Token，并调用此方法更新 Token。 |
| [setServerParams](Android-api#RTCVideo-setserverparams) | 设置应用服务器参数  <br><br/>客户端调用 [sendServerMessage](Android-api#RTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Android-api#RTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。 |
| [getPeerOnlineStatus](Android-api#RTCVideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [sendUserMessageOutsideRoom](Android-api#RTCVideo-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom](Android-api#RTCVideo-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [sendServerMessage](Android-api#RTCVideo-sendservermessage) | 客户端给应用服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Android-api#RTCVideo-sendserverbinarymessage) | 客户端给应用服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo](Android-api#RTCVideo-sendstreamsyncinfo) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [onStreamSyncInfoReceived](Android-callback#IRTCVideoEventHandler-onstreamsyncinforeceived) 回调。 |
| [sendSEIMessage](Android-api#RTCVideo-sendseimessage) | <span id="RTCVideo-sendseimessage-2"></span>通过视频帧发送 SEI 数据。<br/>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |
## CDN 推流
| 方法 | 描述 |
| --- | --- |
| [startPushMixedStreamToCDN](Android-api#RTCVideo-startpushmixedstreamtocdn) | 新增合流转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br><br/>同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。 |
| [updatePushMixedStreamToCDN](Android-api#RTCVideo-updatepushmixedstreamtocdn) | 更新合流转推直播参数，会收到 [onMixingEvent](Android-callback#IMixedStreamObserver-onmixingevent) 回调。  <br><br/>使用 [startPushMixedStreamToCDN](Android-api#RTCVideo-startpushmixedstreamtocdn) 启用转推直播功能后，使用此方法更新功能配置参数。 |
| [startPushSingleStreamToCDN](Android-api#RTCVideo-startpushsinglestreamtocdn) | 新增单流转推直播任务。 |
| [stopPushStreamToCDN](Android-api#RTCVideo-stoppushstreamtocdn) | 停止转推直播。<br><br/>该方法可用于停止单流转推直播或停止合流转推直播，通过 taskId 区分需要停止的任务。 |
## 混音
| 方法 | 描述 |
| --- | --- |
| [getAudioEffectPlayer](Android-api#RTCVideo-getaudioeffectplayer) | 创建音效播放器实例。 |
| [start](Android-api#IAudioEffectPlayer-start) | 开始播放音效文件。<br><br/>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个音效文件，实现音效叠加。 |
| [stop](Android-api#IAudioEffectPlayer-stop) | 停止播放音效文件。 |
| [stopAll](Android-api#IAudioEffectPlayer-stopall) | 停止播放所有音效文件。 |
| [preload](Android-api#IAudioEffectPlayer-preload) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [unload](Android-api#IAudioEffectPlayer-unload) | 卸载指定音效文件。 |
| [unloadAll](Android-api#IAudioEffectPlayer-unloadall) | 卸载所有音效文件。 |
| [pause](Android-api#IAudioEffectPlayer-pause) | 暂停播放音效文件。 |
| [pauseAll](Android-api#IAudioEffectPlayer-pauseall) | 暂停播放所有音效文件。 |
| [resume](Android-api#IAudioEffectPlayer-resume) | 恢复播放音效文件。 |
| [resumeAll](Android-api#IAudioEffectPlayer-resumeall) | 恢复播放所有音效文件。 |
| [setPosition](Android-api#IAudioEffectPlayer-setposition) | 设置音效文件的起始播放位置。 |
| [getPosition](Android-api#IAudioEffectPlayer-getposition) | 获取音效文件播放进度。 |
| [setVolume](Android-api#IAudioEffectPlayer-setvolume) | 调节指定音效的音量大小，包括音效文件和 PCM 音频。 |
| [setVolumeAll](Android-api#IAudioEffectPlayer-setvolumeall) | 设置所有音效的音量大小，包括音效文件和 PCM 音效。 |
| [getVolume](Android-api#IAudioEffectPlayer-getvolume) | 获取当前音量。 |
| [getDuration](Android-api#IAudioEffectPlayer-getduration) | 获取音效文件时长。 |
| [setEventHandler](Android-api#IAudioEffectPlayer-seteventhandler) | 设置回调句柄。 |
| [getMediaPlayer](Android-api#RTCVideo-getmediaplayer) | 创建音乐播放器实例。 |
| [open](Android-api#IMediaPlayer-open) | 打开音乐文件。<br/>一个播放器实例仅能够同时打开一个音乐文件。如果需要同时打开多个音乐文件，请创建多个音乐播放器实例。<br/>要播放 PCM 格式的音频数据，参看 [openWithCustomSource](Android-api#IMediaPlayer-openwithcustomsource)。`openWithCustomSource` 和此 API 互斥。 |
| [start](Android-api#IMediaPlayer-start) | 播放音乐。你仅需要在调用 [open](Android-api#IMediaPlayer-open)，且未开启自动播放时，调用此方法。 |
| [openWithCustomSource](Android-api#IMediaPlayer-openwithcustomsource) | 启动音频裸数据混音。<br/>要播放音乐文件，参看 [open](Android-api#IMediaPlayer-open)。`open` 与此 API 互斥。 |
| [stop](Android-api#IMediaPlayer-stop) | 调用 [open](Android-api#IMediaPlayer-open), [start](Android-api#IMediaPlayer-start), 或 [openWithCustomSource](Android-api#IMediaPlayer-openwithcustomsource) 开始播放后，可以调用本方法停止。 |
| [pause](Android-api#IMediaPlayer-pause) | 调用 [open](Android-api#IMediaPlayer-open)，或 [start](Android-api#IMediaPlayer-start) 开始播放音频文件后，调用本方法暂停播放。 |
| [resume](Android-api#IMediaPlayer-resume) | 调用 [pause](Android-api#IMediaPlayer-pause) 暂停音频播放后，调用本方法恢复播放。 |
| [setVolume](Android-api#IMediaPlayer-setvolume) | 调节指定混音的音量大小，包括音乐文件混音和 PCM 混音。 |
| [getVolume](Android-api#IMediaPlayer-getvolume) | 获取当前音量 |
| [getTotalDuration](Android-api#IMediaPlayer-gettotalduration) | 获取音乐文件时长。 |
| [getPlaybackDuration](Android-api#IMediaPlayer-getplaybackduration) | 获取混音音乐文件的实际播放时长，单位为毫秒。 |
| [getPosition](Android-api#IMediaPlayer-getposition) | 获取音乐文件播放进度。 |
| [setAudioPitch](Android-api#IMediaPlayer-setaudiopitch) | 开启变调功能，多用于 K 歌场景。 |
| [setPosition](Android-api#IMediaPlayer-setposition) | 设置音乐文件的起始播放位置。 |
| [setAudioDualMonoMode](Android-api#IMediaPlayer-setaudiodualmonomode) | 设置当前音乐文件的声道模式 |
| [getAudioTrackCount](Android-api#IMediaPlayer-getaudiotrackcount) | 获取当前音乐文件的音轨数 |
| [selectAudioTrack](Android-api#IMediaPlayer-selectaudiotrack) | 指定当前音乐文件的播放音轨 |
| [setPlaybackSpeed](Android-api#IMediaPlayer-setplaybackspeed) | 设置播放速度 |
| [setProgressInterval](Android-api#IMediaPlayer-setprogressinterval) | 设置音频文件混音时，收到 [onMediaPlayerPlayingProgress](Android-callback#IMediaPlayerEventHandler-onmediaplayerplayingprogress) 的间隔。 |
| [setLoudness](Android-api#IMediaPlayer-setloudness) | 如果你需要使用 [enableVocalInstrumentBalance](Android-api#RTCVideo-enablevocalinstrumentbalance) 对音频文件/PCM 音频数据设置音量均衡，你必须通过此接口传入其原始响度。 |
| [registerAudioFrameObserver](Android-api#IMediaPlayer-registeraudioframeobserver) | 注册回调句柄以在本地音乐文件混音时，收到相关回调。 |
| [pushExternalAudioFrame](Android-api#IMediaPlayer-pushexternalaudioframe) | 推送用于混音的 PCM 音频帧数据 |
| [setEventHandler](Android-api#IMediaPlayer-seteventhandler) | 设置回调句柄。 |
## 屏幕分享
| 方法 | 描述 |
| --- | --- |
| [startScreenCapture](Android-api#RTCVideo-startscreencapture) | 使用 RTC SDK 内部采集模块开始采集屏幕音频流和（或）视频流。 |
| [updateScreenCapture](Android-api#RTCVideo-updatescreencapture) | 使用 RTC SDK 内部屏幕采集后，更新采集的媒体类型。 |
| [stopScreenCapture](Android-api#RTCVideo-stopscreencapture) | 在屏幕共享时，停止使用 RTC SDK 内部采集方式采集屏幕音视频。 |
| [publishScreen](Android-api#RTCRoom-publishscreen) | 在当前所在房间内发布本地屏幕共享音视频流 |
| [unpublishScreen](Android-api#RTCRoom-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [setScreenAudioSourceType](Android-api#RTCVideo-setscreenaudiosourcetype) | 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集） |
| [setScreenAudioStreamIndex](Android-api#RTCVideo-setscreenaudiostreamindex) | 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式 |
| [setScreenVideoEncoderConfig](Android-api#RTCVideo-setscreenvideoencoderconfig) | 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [pushScreenAudioFrame](Android-api#RTCVideo-pushscreenaudioframe) | 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。 |
| [pushScreenVideoFrame](Android-api#RTCVideo-pushscreenvideoframe) | 推送屏幕视频帧 |
| [subscribeScreen](Android-api#RTCRoom-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen](Android-api#RTCRoom-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
## 安全与加密
| 方法 | 描述 |
| --- | --- |
| [startCloudProxy](Android-api#RTCVideo-startcloudproxy) | 开启云代理 |
| [stopCloudProxy](Android-api#RTCVideo-stopcloudproxy) | 关闭云代理 |
| [setCustomizeEncryptHandler](Android-api#RTCVideo-setcustomizeencrypthandler) | 设置自定义加密和解密方式。 |
| [setEncryptInfo](Android-api#RTCVideo-setencryptinfo) | 设置传输时使用内置加密的方式。 |
| [setLocalProxy](Android-api#RTCVideo-setlocalproxy) | 设置本地代理。 |
## 高级功能
| 方法 | 描述 |
| --- | --- |
| [startFileRecording](Android-api#RTCVideo-startfilerecording) | 该方法将通话过程中的音视频数据录制到本地的文件中。 |
| [stopFileRecording](Android-api#RTCVideo-stopfilerecording) | 停止本地录制 |
| [startAudioRecording](Android-api#RTCVideo-startaudiorecording) | 开启录制语音通话，生成本地文件。 <br><br/>在进房前后开启录制，如果未打开麦克风采集，录制任务正常进行，只是不会将数据写入生成的本地文件；只有调用 [startAudioCapture](Android-api#RTCVideo-startaudiocapture) 接口打开麦克风采集后，才会将录制数据写入本地文件。 |
| [stopAudioRecording](Android-api#RTCVideo-stopaudiorecording) | 停止音频文件录制 |
| [setEarMonitorMode](Android-api#RTCVideo-setearmonitormode) | 打开/关闭耳返功能。 |
| [setEarMonitorVolume](Android-api#RTCVideo-setearmonitorvolume) | 设置耳返音量。 |
| [getSpatialAudio](Android-api#RTCRoom-getspatialaudio) | 获取空间音频接口实例。 |
| [disableRemoteOrientation](Android-api#ISpatialAudio-disableremoteorientation) | 关闭本地用户朝向对本地用户发声效果的影响。<br><br/>调用此接口后，房间内的其他用户收听本地发声时，声源都在收听者正面。 |
| [enableSpatialAudio](Android-api#ISpatialAudio-enablespatialaudio) | 开启/关闭空间音频功能。  <br> |
| [getRangeAudio](Android-api#RTCRoom-getrangeaudio) | 获取范围语音接口实例。 |
| [enableRangeAudio](Android-api#IRangeAudio-enablerangeaudio) | 开启/关闭范围语音功能。  <br><br/>范围语音是指，在同一 RTC 房间中设定的音频接收距离范围内，本地用户收听到的远端用户音频音量会随着远端用户的靠近/远离而放大/衰减；若远端用户在房间内的位置超出设定范围，则本地用户无法接收其音频。音频接收范围设置参看 [updateReceiveRange](Android-api#IRangeAudio-updatereceiverange)。 |
| [setAttenuationModel](Android-api#IRangeAudio-setattenuationmodel) | 设置范围语音的音量衰减模式。<br> |
| [setNoAttenuationFlags](Android-api#IRangeAudio-setnoattenuationflags) | 添加标签组，用于标记相互之间通话不衰减的用户组。<br><br/>在同一个 RTC 房间中，如果多个用户的标签组之间有交集，那么，他们之间互相通话时，通话不衰减。<br><br/>比如，用户身处多个队伍，队伍成员间通话不衰减。那么，可以为每个队伍绑定专属标签，每个用户的标签组包含用户所属各个队伍的标签。 |
| [updatePosition](Android-api#IRangeAudio-updateposition) | 更新本地用户在房间内空间直角坐标系中的位置坐标。 |
| [updateReceiveRange](Android-api#IRangeAudio-updatereceiverange) | 更新本地用户的音频收听范围。 |
| [startASR](Android-api#RTCVideo-startasr) | 开启自动语音识别服务。<br><br/>该方法将识别后的用户语音转化成文字，并通过 [onMessage](Android-callback#IRTCASREngineEventHandler-onmessage) 事件回调给用户。 |
| [stopASR](Android-api#RTCVideo-stopasr) | 关闭语音识别服务 |
| [takeLocalSnapshot](Android-api#RTCVideo-takelocalsnapshot) | 截取本地视频画面 |
| [takeRemoteSnapshot](Android-api#RTCVideo-takeremotesnapshot) | 截取远端视频画面 |
| [setAnsMode](Android-api#RTCVideo-setansmode) | 支持根据业务场景，设置通话中的音频降噪模式。 |
| [updateSelfPosition](Android-api#ISpatialAudio-updateselfposition) | 设置本地用户在自建空间直角坐标系中的收听坐标和收听朝向，以实现本地用户预期的空间音频收听效果。 |
| [updateRemotePosition](Android-api#ISpatialAudio-updateremoteposition) | 设置房间内某一远端用户在本地用户自建的空间音频坐标系中的发声位置和发声朝向，以实现本地用户预期的空间音频收听效果。 |
| [removeRemotePosition](Android-api#ISpatialAudio-removeremoteposition) | 移除调用 [updateRemotePosition](Android-api#ISpatialAudio-updateremoteposition) 为某一远端用户设置的空间音频效果。 |
| [removeAllRemotePosition](Android-api#ISpatialAudio-removeallremoteposition) | 移除调用 [updateRemotePosition](Android-api#ISpatialAudio-updateremoteposition) 为所有远端用户设置的空间音频效果。 |
## 字幕翻译服务
| 方法 | 描述 |
| --- | --- |
| [startSubtitle](Android-api#RTCRoom-startsubtitle) | 识别或翻译房间内所有用户的语音，形成字幕。<br><br/>调用该方法时，可以在 [SubtitleMode](Android-keytype#subtitlemode) 中选择语音识别或翻译模式。如果选择识别模式，语音识别文本会通过 [onSubtitleMessageReceived](Android-callback#IRTCRoomEventHandler-onsubtitlemessagereceived) 事件回调给你；<br><br/>如果选择翻译模式，你会同时收到两个 [onSubtitleMessageReceived](Android-callback#IRTCRoomEventHandler-onsubtitlemessagereceived) 回调，分别包含字幕原文及字幕译文。<br><br/>调用该方法后，你会收到 [onSubtitleStateChanged](Android-callback#IRTCRoomEventHandler-onsubtitlestatechanged) 回调，通知字幕是否开启。 |
| [stopSubtitle](Android-api#RTCRoom-stopsubtitle) | 关闭字幕。 <br><br/>调用该方法后，用户会收到 [onSubtitleStateChanged](Android-callback#IRTCRoomEventHandler-onsubtitlestatechanged) 回调，通知字幕是否关闭。 |
## 在线 KTV
| 方法 | 描述 |
| --- | --- |
| [getKTVManager](Android-api#RTCVideo-getktvmanager) | 创建 KTV 管理接口。 |
| [setMaxCacheSize](Android-api#IKTVManager-setmaxcachesize) | 设置歌曲文件最大占用的本地缓存。 |
| [getMusicList](Android-api#IKTVManager-getmusiclist) | 获取歌曲列表。 |
| [searchMusic](Android-api#IKTVManager-searchmusic) | 根据关键词搜索歌曲。 |
| [getHotMusic](Android-api#IKTVManager-gethotmusic) | 根据热榜类别获取每个榜单的歌曲列表。 |
| [getMusicDetail](Android-api#IKTVManager-getmusicdetail) | 获取音乐详细信息。 |
| [downloadMusic](Android-api#IKTVManager-downloadmusic) | 下载音乐。 |
| [downloadLyric](Android-api#IKTVManager-downloadlyric) | 下载歌词。 |
| [downloadMidi](Android-api#IKTVManager-downloadmidi) | 下载 MIDI 文件。 |
| [cancelDownload](Android-api#IKTVManager-canceldownload) | 取消下载任务。 |
| [clearCache](Android-api#IKTVManager-clearcache) | 清除当前音乐缓存文件，包括音乐音频和歌词。 |
| [getKTVPlayer](Android-api#IKTVManager-getktvplayer) | 获取 KTV 播放器。 |
| [setPlayerEventHandler](Android-api#IKTVPlayer-setplayereventhandler) | 设置 KTV 播放器进度及状态回调接口。 |
| [playMusic](Android-api#IKTVPlayer-playmusic) | 播放歌曲。 |
| [pauseMusic](Android-api#IKTVPlayer-pausemusic) | 暂停播放歌曲。 |
| [resumeMusic](Android-api#IKTVPlayer-resumemusic) | 继续播放歌曲。 |
| [stopMusic](Android-api#IKTVPlayer-stopmusic) | 停止播放歌曲。 |
| [seekMusic](Android-api#IKTVPlayer-seekmusic) | 设置音乐文件的起始播放位置。 |
| [setMusicVolume](Android-api#IKTVPlayer-setmusicvolume) | 设置歌曲播放音量，只能在开始播放后进行设置。 |
| [switchAudioTrackType](Android-api#IKTVPlayer-switchaudiotracktype) | 切换歌曲原唱伴唱。 |
| [setMusicPitch](Android-api#IKTVPlayer-setmusicpitch) | 对播放中的音乐设置升降调信息。 |
| [getSingScoringManager](Android-api#RTCVideo-getsingscoringmanager) | 创建 K 歌评分管理接口。 |
| [initSingScoring](Android-api#ISingScoringManager-initsingscoring) | 初始化 K 歌评分。 |
| [setSingScoringConfig](Android-api#ISingScoringManager-setsingscoringconfig) | 设置 K 歌评分参数。 |
| [getStandardPitchInfo](Android-api#ISingScoringManager-getstandardpitchinfo) | 获取标准音高数据。 |
| [startSingScoring](Android-api#ISingScoringManager-startsingscoring) | 开始 K 歌评分。 |
| [stopSingScoring](Android-api#ISingScoringManager-stopsingscoring) | 停止 K 歌评分。 |
| [getLastSentenceScore](Android-api#ISingScoringManager-getlastsentencescore) | 获取上一句的演唱评分。调用 [startSingScoring](Android-api#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。 |
| [getTotalScore](Android-api#ISingScoringManager-gettotalscore) | 获取当前演唱总分。调用 [startSingScoring](Android-api#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。 |
| [getAverageScore](Android-api#ISingScoringManager-getaveragescore) | 获取当前演唱歌曲的平均分。 |
| [setAudioAlignmentProperty](Android-api#RTCVideo-setaudioalignmentproperty) | 在听众端，设置订阅的所有远端音频流精准对齐后播放。 |
# 回调
## 引擎管理
| 回调 | 描述 |
| --- | --- |
| [onLogReport](Android-callback#IRTCVideoEventHandler-onlogreport) | 上报日志时回调该事件。 |
| [onSysStats](Android-callback#IRTCVideoEventHandler-onsysstats) | 每2秒发生回调，通知当前cpu，内存使用的信息。  <br> |
| [onWarning](Android-callback#IRTCVideoEventHandler-onwarning) | 发生警告回调。  <br><br/>SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。 |
| [onError](Android-callback#IRTCVideoEventHandler-onerror) | 发生错误回调。<br><br/>SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。<br><br/>你可能需要干预. |
| [onTokenWillExpire](Android-callback#IRTCRoomEventHandler-ontokenwillexpire) | 当 SDK 检测到 Token 的进房权限将在 30 秒内过期时，触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Android-api#RTCRoom-updatetoken) 更新 Token 进房权限。 |
| [onPublishPrivilegeTokenWillExpire](Android-callback#IRTCRoomEventHandler-onpublishprivilegetokenwillexpire) | Token 发布权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Android-api#RTCRoom-updatetoken) 更新 Token 发布权限。 |
| [onSubscribePrivilegeTokenWillExpire](Android-callback#IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire) | Token 订阅权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Android-api#RTCRoom-updatetoken) 更新 Token 订阅权限有效期。 |
## 房间管理
| 回调 | 描述 |
| --- | --- |
| [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) | 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。 |
| [onCreateRoomStateChanged](Android-callback#IRTCVideoEventHandler-oncreateroomstatechanged) | 创建房间失败回调。 |
| [onLeaveRoom](Android-callback#IRTCRoomEventHandler-onleaveroom) | 离开房间成功回调。  <br><br/>用户调用 [leaveRoom](Android-api#RTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br> |
| [onUserJoined](Android-callback#IRTCRoomEventHandler-onuserjoined) | 远端可见用户加入房间，或房内不可见用户切换为可见的回调。<br><br/>1.远端用户调用 [setUserVisibility](Android-api#RTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br><br/>2.远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br><br/>3.房间内隐身远端用户调用 [setUserVisibility](Android-api#RTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br><br/>4.新进房用户也会收到进房前已在房内的可见用户的进房回调通知。  <br> |
| [onUserLeave](Android-callback#IRTCRoomEventHandler-onuserleave) | 远端用户离开房间，或切至不可见时，房间内其他用户会收到此事件 |
| [onUserVisibilityChanged](Android-callback#IRTCRoomEventHandler-onuservisibilitychanged) | 用户调用 [setUserVisibility](Android-api#RTCRoom-setuservisibility) 设置用户可见性的回调。 |
| [onRoomStats](Android-callback#IRTCRoomEventHandler-onroomstats) | 房间内通话统计信息回调。  <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |
| [onSetRoomExtraInfoResult](Android-callback#IRTCRoomEventHandler-onsetroomextrainforesult) | 调用 [setRoomExtraInfo](Android-api#RTCRoom-setroomextrainfo) 设置房间附加信息结果的回调。 |
| [onRoomExtraInfoUpdate](Android-callback#IRTCRoomEventHandler-onroomextrainfoupdate) | 接收同一房间内，其他用户调用 [setRoomExtraInfo](Android-api#RTCRoom-setroomextrainfo) 设置的房间附加信息的回调。 |
## 音频管理
| 回调 | 描述 |
| --- | --- |
| [onAudioDeviceWarning](Android-callback#IRTCVideoEventHandler-onaudiodevicewarning) | 音频设备警告回调。音频设备包括音频采集设备、音频渲染设备等。 |
| [onAudioRouteChanged](Android-callback#IRTCVideoEventHandler-onaudioroutechanged) | 音频播放路由变化时，收到该回调。 |
| [onAudioDeviceStateChanged](Android-callback#IRTCVideoEventHandler-onaudiodevicestatechanged) | 音频设备状态回调。提示音频采集、音频播放等媒体设备的状态。 |
| [onLocalAudioPropertiesReport](Android-callback#IRTCVideoEventHandler-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Android-api#RTCVideo-enableaudiopropertiesreport) 后，你会周期性地收到此回调，了解本地音频的相关信息。  <br><br/>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。 |
| [onRemoteAudioPropertiesReport](Android-callback#IRTCVideoEventHandler-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Android-api#RTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。<br><br/>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onActiveSpeaker](Android-callback#IRTCVideoEventHandler-onactivespeaker) | 调用 [enableAudioPropertiesReport](Android-api#RTCVideo-enableaudiopropertiesreport) 后，根据设置的 `AudioPropertiesConfig.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [onUserStartAudioCapture](Android-callback#IRTCVideoEventHandler-onuserstartaudiocapture) | 房间内的用户调用 [startAudioCapture](Android-api#RTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。 |
| [onUserStopAudioCapture](Android-callback#IRTCVideoEventHandler-onuserstopaudiocapture) | 房间内的用户调用 [stopAudioCapture](Android-api#RTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。 |
| [onStreamSyncInfoReceived](Android-callback#IRTCVideoEventHandler-onstreamsyncinforeceived) | 音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Android-api#RTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br> |
| [onAudioStreamBanned](Android-callback#IRTCRoomEventHandler-onaudiostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [onAudioPlaybackDeviceTestVolume](Android-callback#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onHardwareEchoDetectionResult](Android-callback#IRTCVideoEventHandler-onhardwareechodetectionresult) | 通话前回声检测结果回调。 |
| [onLocalAudioStateChanged](Android-callback#IRTCVideoEventHandler-onlocalaudiostatechanged) | 本地音频流的状态发生改变时，收到此回调。 |
## 视频管理
| 回调 | 描述 |
| --- | --- |
| [onUserStartVideoCapture](Android-callback#IRTCVideoEventHandler-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Android-api#RTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。 |
| [onUserStopVideoCapture](Android-callback#IRTCVideoEventHandler-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Android-api#RTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。<br><br/>若发布视频数据前未开启采集，房间内所有可见用户会收到此回调。 |
| [onVideoDeviceStateChanged](Android-callback#IRTCVideoEventHandler-onvideodevicestatechanged) | 视频设备状态回调。提示摄像头视频采集、屏幕视频采集等媒体设备的状态。 |
| [onVideoDeviceWarning](Android-callback#IRTCVideoEventHandler-onvideodevicewarning) | 视频设备警告回调，包括视频采集等设备。 |
| [onFaceDetectResult](Android-callback#IFaceDetectionObserver-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。 <br><br/>调用 [enableFaceDetection](Android-api#IVideoEffect-enablefacedetection) 注册了 [IFaceDetectionObserver](Android-callback#ifacedetectionobserver)，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |
| [onLocalVideoStateChanged](Android-callback#IRTCVideoEventHandler-onlocalvideostatechanged) | 本地视频流的状态发生改变时，收到该事件。 |
## 音视频传输
| 回调 | 描述 |
| --- | --- |
| [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [onAVSyncStateChange](Android-callback#IRTCRoomEventHandler-onavsyncstatechange) | 发布端调用 [setMultiDeviceAVSync](Android-api#RTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。 |
| [onUserPublishStream](Android-callback#IRTCRoomEventHandler-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集的媒体流的回调。 |
| [onUserUnpublishStream](Android-callback#IRTCRoomEventHandler-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onAudioFrameSendStateChanged](Android-callback#IRTCVideoEventHandler-onaudioframesendstatechanged) | 本地音频首帧发送状态发生改变时，收到此回调。 |
| [onVideoFrameSendStateChanged](Android-callback#IRTCVideoEventHandler-onvideoframesendstatechanged) | 本地视频首帧发送状态发生改变时，收到此回调。 |
| [onAudioFramePlayStateChanged](Android-callback#IRTCVideoEventHandler-onaudioframeplaystatechanged) | 音频首帧播放状态发生改变时，收到此回调。 |
| [onVideoFramePlayStateChanged](Android-callback#IRTCVideoEventHandler-onvideoframeplaystatechanged) | 视频首帧播放状态发生改变时，收到此回调。 |
| [onForwardStreamStateChanged](Android-callback#IRTCRoomEventHandler-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [onForwardStreamEvent](Android-callback#IRTCRoomEventHandler-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [onLocalStreamStats](Android-callback#IRTCRoomEventHandler-onlocalstreamstats) | 本地流数据统计以及网络质量回调。  <br><br/>本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br><br/>统计信息通过 [LocalStreamStats](Android-keytype#localstreamstats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [onRemoteStreamStats](Android-callback#IRTCRoomEventHandler-onremotestreamstats) | 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br><br/>本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [onNetworkQuality](Android-callback#IRTCRoomEventHandler-onnetworkquality) | 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。 |
| [onStreamSubscribed](Android-callback#IRTCRoomEventHandler-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onStreamSubscribed](Android-callback#IRTCRoomEventHandler-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onRemoteAudioStateChanged](Android-callback#IRTCVideoEventHandler-onremoteaudiostatechanged) | 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。 |
| [onFirstLocalAudioFrame](Android-callback#IRTCVideoEventHandler-onfirstlocalaudioframe) | 发布音频流时，采集到第一帧音频帧，收到该回调。 |
| [onFirstRemoteAudioFrame](Android-callback#IRTCVideoEventHandler-onfirstremoteaudioframe) | 接收到来自远端某音频流的第一帧时，收到该回调。 |
| [onRemoteVideoStateChanged](Android-callback#IRTCVideoEventHandler-onremotevideostatechanged) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [onFirstRemoteVideoFrameRendered](Android-callback#IRTCVideoEventHandler-onfirstremotevideoframerendered) | SDK 内部渲染成功远端视频流首帧后，收到此回调。 |
| [onFirstLocalVideoFrameCaptured](Android-callback#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) | RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。 |
| [onLocalVideoSizeChanged](Android-callback#IRTCVideoEventHandler-onlocalvideosizechanged) | 本地预览视频大小或旋转信息发生改变时，收到此回调。 |
| [onRemoteVideoSizeChanged](Android-callback#IRTCVideoEventHandler-onremotevideosizechanged) | 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onFirstRemoteVideoFrameDecoded](Android-callback#IRTCVideoEventHandler-onfirstremotevideoframedecoded) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [onVideoStreamBanned](Android-callback#IRTCRoomEventHandler-onvideostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [onPushPublicStreamResult](Android-callback#IRTCVideoEventHandler-onpushpublicstreamresult) | 公共流发布结果回调。<br><br/>调用 [startPushPublicStream](Android-api#RTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。 |
| [onPlayPublicStreamResult](Android-callback#IRTCVideoEventHandler-onplaypublicstreamresult) | 订阅公共流的结果回调  <br><br/>调用 [startPlayPublicStream](Android-api#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到启动结果和拉流过程中的错误。 |
| [onPublicStreamSEIMessageReceived](Android-callback#IRTCVideoEventHandler-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br/>调用 [startPlayPublicStream](Android-api#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [onFirstPublicStreamVideoFrameDecoded](Android-callback#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) | 公共流的首帧视频解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Android-api#RTCVideo-startplaypublicstream)。 |
| [onFirstPublicStreamAudioFrame](Android-callback#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Android-api#RTCVideo-startplaypublicstream)。 |
## 自定义流处理
| 回调 | 描述 |
| --- | --- |
| [onStart](Android-callback#IExternalVideoEncoderEventHandler-onstart) | 提示自定义编码帧可以开始推送的回调。  <br><br/>收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Android-api#RTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧 |
| [onStop](Android-callback#IExternalVideoEncoderEventHandler-onstop) | 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧 |
| [onRateUpdate](Android-callback#IExternalVideoEncoderEventHandler-onrateupdate) | 当自定义编码流的帧率或码率发生变化时，触发该回调 |
| [onRequestKeyFrame](Android-callback#IExternalVideoEncoderEventHandler-onrequestkeyframe) | 提示流发布端需重新生成关键帧的回调 |
| [onActiveVideoLayer](Android-callback#IExternalVideoEncoderEventHandler-onactivevideolayer) | 作为自定义编码视频流的发送端，你会在视频流可发送状态发生变化时，收到此回调。<br/>你可以根据此回调的提示，仅对可发送的视频流进行编码，以降低本端视频编码性能消耗。此回调会根据多个因素综合判断触发，包括：本端设备性能和本端网络性能，以及按需订阅场景下，远端用户是否订阅。 |
| [onLocalEncodedVideoFrame](Android-callback#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) | 调用 [registerLocalEncodedVideoFrameObserver](Android-api#RTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。 |
| [onRemoteEncodedVideoFrame](Android-callback#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) | 调用 [registerRemoteEncodedVideoFrameObserver](Android-api#RTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调 |
| [onProcessEarMonitorAudioFrame](Android-callback#IAudioFrameProcessor-onprocessearmonitoraudioframe) | 软件耳返音频数据的回调。你可根据此回调自定义处理音频。<br/>软件耳返音频中包含通过调用 `setVoiceReverbType` 和 `setVoiceChangerType` 设置的音频特效。 |
| [onProcessPlayBackAudioFrame](Android-callback#IAudioFrameProcessor-onprocessplaybackaudioframe) | 回调远端音频混音的音频帧地址，供自定义音频处理。 |
| [onProcessRecordAudioFrame](Android-callback#IAudioFrameProcessor-onprocessrecordaudioframe) | 回调本地采集的音频帧地址，供自定义音频处理。 |
| [onProcessRemoteUserAudioFrame](Android-callback#IAudioFrameProcessor-onprocessremoteuseraudioframe) | 回调单个远端用户的音频帧地址，供自定义音频处理。 |
| [onProcessScreenAudioFrame](Android-callback#IAudioFrameProcessor-onprocessscreenaudioframe) | 屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。 |
| [onRecordAudioFrame](Android-callback#IAudioFrameObserver-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame](Android-callback#IAudioFrameObserver-onplaybackaudioframe) | 返回订阅的所有远端用户混音后的音频数据。 |
| [onRemoteUserAudioFrame](Android-callback#IAudioFrameObserver-onremoteuseraudioframe) | 返回远端单个用户的音频数据 |
| [onMixedAudioFrame](Android-callback#IAudioFrameObserver-onmixedaudioframe) | 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据 |
## 网络管理
| 回调 | 描述 |
| --- | --- |
| [onPerformanceAlarms](Android-callback#IRTCVideoEventHandler-onperformancealarms) | 本地未通过 [setPublishFallbackOption](Android-api#RTCVideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。  <br><br/>本地通过 [setPublishFallbackOption](Android-api#RTCVideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。 |
| [onSimulcastSubscribeFallback](Android-callback#IRTCVideoEventHandler-onsimulcastsubscribefallback) | 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。 |
| [onNetworkDetectionResult](Android-callback#IRTCVideoEventHandler-onnetworkdetectionresult) | 通话前网络探测结果。  <br><br/>成功调用 [startNetworkDetection](Android-api#RTCVideo-startnetworkdetection) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [onNetworkDetectionStopped](Android-callback#IRTCVideoEventHandler-onnetworkdetectionstopped) | 通话前网络探测结束<br/>以下情况将停止探测并收到本一次本回调：<br><br/>1. 当调用 [stopNetworkDetection](Android-api#RTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；<br/>2. 当收到远端/本端音频首帧后，停止探测；<br/>3. 当探测超过3分钟后，停止探测；<br/>4. 当探测链路断开一定时间之后，停止探测。 |
| [onConnectionStateChanged](Android-callback#IRTCVideoEventHandler-onconnectionstatechanged) | 回调 SDK 与信令服务器连接状态相关事件。当 SDK 与信令服务器的网络连接状态改变时回调该事件。 |
| [onNetworkTypeChanged](Android-callback#IRTCVideoEventHandler-onnetworktypechanged) | SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。 |
| [onSEIMessageReceived](Android-callback#IRTCVideoEventHandler-onseimessagereceived) | 收到通过调用 [sendSEIMessage](Android-api#RTCVideo-sendseimessage) 发送带有 SEI 消息的视频帧时，收到此回调。 |
| [onEchoTestResult](Android-callback#IRTCVideoEventHandler-onechotestresult) | 关于音视频回路测试结果的回调。 |
| [onNetworkTimeSynchronized](Android-callback#IRTCVideoEventHandler-onnetworktimesynchronized) | 首次调用 [getNetworkTimeInfo](Android-api#RTCVideo-getnetworktimeinfo) 后，SDK内部启动网络时间同步，同步完成时会触发此回调。 |
## 消息
| 回调 | 描述 |
| --- | --- |
| [onRoomMessageReceived](Android-callback#IRTCRoomEventHandler-onroommessagereceived) | 接收到房间内广播消息的回调。<br><br/>房间内其他用户调用 [sendRoomMessage](Android-api#RTCRoom-sendroommessage) 发送广播消息时，收到此回调。 |
| [onRoomBinaryMessageReceived](Android-callback#IRTCRoomEventHandler-onroombinarymessagereceived) | 收到房间内广播二进制消息的回调。<br><br/>房间内其他用户调用 [sendRoomBinaryMessage](Android-api#RTCRoom-sendroombinarymessage) 发送广播二进制消息时，收到此回调。 |
| [onUserMessageReceived](Android-callback#IRTCRoomEventHandler-onusermessagereceived) | 收到来自房间中其他用户通过 [sendUserMessage](Android-api#RTCRoom-sendusermessage) 发来的点对点文本消息时，会收到此回调。 |
| [onUserBinaryMessageReceived](Android-callback#IRTCRoomEventHandler-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 [sendUserBinaryMessage](Android-api#RTCRoom-senduserbinarymessage) 发来的点对点二进制消息时，会收到此回调。 |
| [onUserMessageSendResult](Android-callback#IRTCRoomEventHandler-onusermessagesendresult) | 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。 |
| [onRoomMessageSendResult](Android-callback#IRTCRoomEventHandler-onroommessagesendresult) | 调用 [sendRoomMessage](Android-api#RTCRoom-sendroommessage) 或 [sendRoomBinaryMessage](Android-api#RTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onLoginResult](Android-callback#IRTCVideoEventHandler-onloginresult) | 登录结果回调 |
| [onLogout](Android-callback#IRTCVideoEventHandler-onlogout) | 登出结果回调 |
| [onServerParamsSetResult](Android-callback#IRTCVideoEventHandler-onserverparamssetresult) | 设置应用服务器参数的返回结果 |
| [onGetPeerOnlineStatus](Android-callback#IRTCVideoEventHandler-ongetpeeronlinestatus) | 查询对端或本端用户登录状态的返回结果 |
| [onUserMessageReceivedOutsideRoom](Android-callback#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserMessageOutsideRoom](Android-api#RTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调 |
| [onUserBinaryMessageReceivedOutsideRoom](Android-callback#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Android-api#RTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调 |
| [onUserMessageSendResultOutsideRoom](Android-callback#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) | 给房间外指定的用户发送消息的回调 |
| [onServerMessageSendResult](Android-callback#IRTCVideoEventHandler-onservermessagesendresult) | 给应用服务器发送消息的回调。 |
| [onSEIStreamUpdate](Android-callback#IRTCVideoEventHandler-onseistreamupdate) | 黑帧视频流发布状态回调。  <br><br/>在语音通话场景下，本地用户调用 [sendSEIMessage](Android-api#RTCVideo-sendseimessage) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br><br/>你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。 |
## CDN 推流
| 回调 | 描述 |
| --- | --- |
| [onStreamMixingEvent](Android-callback#ILiveTranscodingObserver-onstreammixingevent) | 转推直播状态回调 |
| [isSupportClientPushStream](Android-callback#ILiveTranscodingObserver-issupportclientpushstream) | 是否具有推流能力。  <br><br/>+ false：不具备推流能力（默认值）  <br><br/>+ true：具备推流能力 |
| [onMixingAudioFrame](Android-callback#ILiveTranscodingObserver-onmixingaudioframe) | 端云一体合流音频 PCM 回调 |
| [onMixingVideoFrame](Android-callback#ILiveTranscodingObserver-onmixingvideoframe) | 端云一体合流视频 YUV 回调 |
| [onMixingDataFrame](Android-callback#ILiveTranscodingObserver-onmixingdataframe) | 端云一体合流视频 SEI 数据回调 |
| [onStreamPushEvent](Android-callback#IPushSingleStreamToCDNObserver-onstreampushevent) | 单流转推直播状态回调 |
## 混音
| 回调 | 描述 |
| --- | --- |
| [onAudioEffectPlayerStateChanged](Android-callback#IAudioEffectPlayerEventHandler-onaudioeffectplayerstatechanged) | 播放状态改变时回调。 |
| [onFrame](Android-callback#IMediaPlayerAudioFrameObserver-onframe) | 当本地音频文件混音时，回调播放的音频帧。 |
| [onMediaPlayerStateChanged](Android-callback#IMediaPlayerEventHandler-onmediaplayerstatechanged) | 播放状态改变时回调。 |
| [onMediaPlayerPlayingProgress](Android-callback#IMediaPlayerEventHandler-onmediaplayerplayingprogress) | 播放进度周期性回调。回调周期通过 [setProgressInterval](Android-api#IMediaPlayer-setprogressinterval) 设置。 |
| [onReadData](Android-callback#IMediaPlayerCustomSourceProvider-onreaddata) | 调用 [openWithCustomSource](Android-api#IMediaPlayer-openwithcustomsource) 接口播放用户传入的内存音频数据时，会触发此回调，用户需要写入音频数据。 |
| [onSeek](Android-callback#IMediaPlayerCustomSourceProvider-onseek) | 根据设置好的内存音频数据的读取位置和读取偏移量对音频数据进行偏移，以便 SDK 读取和分析音频数据。 <br><br/>在调用 [openWithCustomSource](Android-api#IMediaPlayer-openwithcustomsource) 接口传入内存音频数据，或者调用 [setPosition](Android-api#IMediaPlayer-setposition) 设置了音频数据的起始播放位置后，SDK 会对音频数据进行读取和分析，此时会触发该回调，你需要根据参数中设置的起始读取位置和偏移量进行操作。 |
## 屏幕分享
| 回调 | 描述 |
| --- | --- |
| [onUserPublishScreen](Android-callback#IRTCRoomEventHandler-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](Android-callback#IRTCRoomEventHandler-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onScreenVideoFrameSendStateChanged](Android-callback#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) | 屏幕共享流的视频首帧发送状态发生改变时，收到此回调。 |
| [onScreenVideoFramePlayStateChanged](Android-callback#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) | 屏幕共享流视频首帧播放状态发生改变时，收到此回调。 |
## 安全与加密
| 回调 | 描述 |
| --- | --- |
| [onCloudProxyConnected](Android-callback#IRTCVideoEventHandler-oncloudproxyconnected) | 调用 [startCloudProxy](Android-api#RTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onEncryptData](Android-callback#IRTCEncryptionHandler-onencryptdata) | 自定义加密。  <br><br/>使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br><br/>暂不支持对原始音视频帧进行加密。 |
| [onDecryptData](Android-callback#IRTCEncryptionHandler-ondecryptdata) | 自定义解密。  <br><br/>对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData](Android-callback#IRTCEncryptionHandler-onencryptdata)。 |
| [onLocalProxyStateChanged](Android-callback#IRTCVideoEventHandler-onlocalproxystatechanged) | 本地代理状态发生改变回调。调用 [setLocalProxy](Android-api#RTCVideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，通知代理连接的状态。  <br> |
## 高级功能
| 回调 | 描述 |
| --- | --- |
| [onExtensionAccessError](Android-callback#IRTCVideoEventHandler-onextensionaccesserror) | 当访问插件失败时，收到此回调。<br/>RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。 |
| [onRecordingStateUpdate](Android-callback#IRTCVideoEventHandler-onrecordingstateupdate) | 获取本地录制状态回调。  <br><br/>该回调由 [startFileRecording](Android-api#RTCVideo-startfilerecording) 或 [stopFileRecording](Android-api#RTCVideo-stopfilerecording) 触发。 |
| [onRecordingProgressUpdate](Android-callback#IRTCVideoEventHandler-onrecordingprogressupdate) | 本地录制进度回调。  <br><br/>该回调由 [startFileRecording](Android-api#RTCVideo-startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。 |
| [onAudioRecordingStateUpdate](Android-callback#IRTCVideoEventHandler-onaudiorecordingstateupdate) | 调用 [startAudioRecording](Android-api#RTCVideo-startaudiorecording) 或 [stopAudioRecording](Android-api#RTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。 |
| [onTakeLocalSnapshotResult](Android-callback#ISnapshotResultCallback-ontakelocalsnapshotresult) | 调用 [takeLocalSnapshot](Android-api#RTCVideo-takelocalsnapshot) 截取视频画面时，收到此回调。 |
| [onTakeRemoteSnapshotResult](Android-callback#ISnapshotResultCallback-ontakeremotesnapshotresult) | 调用 [takeRemoteSnapshot](Android-api#RTCVideo-takeremotesnapshot) 截取视频画面时，收到此回调。 |
## 字幕翻译服务
| 回调 | 描述 |
| --- | --- |
| [onSubtitleStateChanged](Android-callback#IRTCRoomEventHandler-onsubtitlestatechanged) | 字幕状态发生改变回调。 <br><br/>当用户调用 [startSubtitle](Android-api#RTCRoom-startsubtitle) 和 [stopSubtitle](Android-api#RTCRoom-stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。 |
| [onSubtitleMessageReceived](Android-callback#IRTCRoomEventHandler-onsubtitlemessagereceived) | 字幕相关内容回调。 <br><br/>当用户成功调用 [startSubtitle](Android-api#RTCRoom-startsubtitle) 后会收到此回调，通知字幕的相关信息。 |
## 在线 KTV
| 回调 | 描述 |
| --- | --- |
| [onMusicListResult](Android-callback#IKTVManagerEventHandler-onmusiclistresult) | 歌曲列表回调。 |
| [onSearchMusicResult](Android-callback#IKTVManagerEventHandler-onsearchmusicresult) | 搜索歌曲结果回调。 |
| [onHotMusicResult](Android-callback#IKTVManagerEventHandler-onhotmusicresult) | 热榜歌曲结果回调。 |
| [onMusicDetailResult](Android-callback#IKTVManagerEventHandler-onmusicdetailresult) | 歌曲详细信息回调。 |
| [onDownloadSuccess](Android-callback#IKTVManagerEventHandler-ondownloadsuccess) | 下载成功回调。 |
| [onDownloadMusicProgress](Android-callback#IKTVManagerEventHandler-ondownloadmusicprogress) | 歌曲文件下载进度回调。 |
| [onPlayProgress](Android-callback#IKTVPlayerEventHandler-onplayprogress) | 音乐播放进度回调。 |
| [onCurrentScoringInfo](Android-callback#ISingScoringEventHandler-oncurrentscoringinfo) | 实时评分信息回调。调用 [startSingScoring](Android-api#ISingScoringManager-startsingscoring) 后，会收到该回调。 |
