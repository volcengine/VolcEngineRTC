# 方法
## 引擎管理

| 方法 | 描述 |
| --- | --- |
| [createRTCVideo](Android-api.md#RTCVideo-creatertcvideo) | 创建引擎对象  <br><br/>如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br><br/>如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。 |
| [destroyRTCVideo](Android-api.md#RTCVideo-destroyrtcvideo) | 销毁由 [createRTCVideo](Android-api.md#RTCVideo-creatertcvideo) 所创建的引擎实例，并释放所有相关资源。<br> |
| [getSDKVersion](Android-api.md#RTCVideo-getsdkversion) | 获取 SDK 当前的版本号。 |
| [feedback](Android-api.md#RTCVideo-feedback) | 将用户反馈的问题上报到 RTC |
| [getErrorDescription](Android-api.md#RTCVideo-geterrordescription) | 获取 SDK 内各种错误码、警告码的描述文字。 |
| [setRtcVideoEventHandler](Android-api#RTCVideo-setrtcvideoeventhandler) | 设置引擎事件回调的接收类，必须继承自 [IRTCVideoEventHandler](Android-callback.md#irtcvideoeventhandler) 。 |
| [setBusinessId](Android-api.md#RTCVideo-setbusinessid) | 设置业务标识参数  <br><br/>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setRuntimeParameters](Android-api.md#RTCVideo-setruntimeparameters) | 设置运行时的参数 |

## 房间管理

| 方法 | 描述 |
| --- | --- |
| [createRTCRoom](Android-api.md#RTCVideo-creatertcroom) | 创建房间实例。<br/>调用此方法仅返回一个房间实例，你仍需调用 [joinRoom](Android-api.md#RTCRoom-joinroom) 才能真正地创建/加入房间。<br/>多次调用此方法以创建多个 [RTCRoom](Android-api.md#rtcroom) 实例。分别调用各 RTCRoom 实例中的 [joinRoom](Android-api.md#RTCRoom-joinroom) 方法，同时加入多个房间。<br/>多房间模式下，用户可以同时订阅各房间的音视频流。 |
| [destroy](Android-api.md#RTCRoom-destroy) | 退出并销毁调用 [createRTCRoom](Android-api.md#RTCVideo-creatertcroom) 所创建的房间实例。 |
| [setRTCRoomEventHandler](Android-api.md#RTCRoom-setrtcroomeventhandler) | 通过设置 [RTCRoom](Android-api.md#rtcroom) 对象的事件句柄，监听此对象对应的回调事件。 |
| [joinRoom](Android-api.md#RTCRoom-joinroom) | 加入房间。<br><br/>多房间场景下，调用 [createRTCRoom](Android-api.md#RTCVideo-creatertcroom) 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br> |
| [setRoomExtraInfo](Android-api.md#RTCRoom-setroomextrainfo) | 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。 |
| [leaveRoom](Android-api#RTCRoom-leaveroom) | 离开房间。  <br><br/>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br><br/>此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 [onLeaveRoom](Android-callback.md#IRTCRoomEventHandler-onleaveroom) 回调通知。  <br> |
| [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br> |
| [updateToken](Android-api.md#RTCRoom-updatetoken) | 更新 Token。<br/>Token 中同时包含进房、发布和订阅权限，各权限有一定的有效期，并且到期前 30 秒会触发回调，提示用户更新 Token 相关权限。此时需要重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。 |

## 音频管理

| 方法 | 描述 |
| --- | --- |
| [setDefaultAudioRoute](Android-api.md#RTCVideo-setdefaultaudioroute) | 将默认的音频播放设备设置为听筒或扬声器。 |
| [getAudioRoute](Android-api.md#RTCVideo-getaudioroute) | 获取当前使用的音频播放路由。  <br> |
| [setCaptureVolume](Android-api.md#RTCVideo-setcapturevolume) | 调节音频采集音量 |
| [setPlaybackVolume](Android-api.md#RTCVideo-setplaybackvolume) | 调节本地播放的所有远端用户混音后的音量。<br><br/>播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume](Android-api.md#RTCVideo-setremoteaudioplaybackvolume) | 调节来自指定远端用户的音频播放音量。 |
| [setRemoteRoomAudioPlaybackVolume](Android-api.md#RTCRoom-setremoteroomaudioplaybackvolume) | 调节某个房间内所有远端用户的音频播放音量。 |
| [enableAudioPropertiesReport](Android-api#RTCVideo-enableaudiopropertiesreport) | 启用音频信息提示。开启提示后，你可以收到 [onLocalAudioPropertiesReport](Android-callback.md#IRTCVideoEventHandler-onlocalaudiopropertiesreport)，[onRemoteAudioPropertiesReport](Android-callback.md#IRTCVideoEventHandler-onremoteaudiopropertiesreport) 和 [onActiveSpeaker](Android-callback.md#IRTCVideoEventHandler-onactivespeaker)。 |
| [startAudioCapture](Android-api#RTCVideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法开启后，本地用户会收到 [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Android-callback.md#IRTCVideoEventHandler-onuserstartaudiocapture) 的回调。 |
| [stopAudioCapture](Android-api#RTCVideo-stopaudiocapture) | 立即关闭内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法，本地用户会收到 [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopAudioCapture](Android-callback.md#IRTCVideoEventHandler-onuserstopaudiocapture) 的回调。 |
| [setAudioScenario](Android-api.md#RTCVideo-setaudioscenario) | 设置音频场景类型。<br/>你可以根据你的应用所在场景，选择合适的音频场景类型。<br/>选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。 |
| [setAudioProfile](Android-api#RTCVideo-setaudioprofile) | 设置音质档位。<br><br/>当所选的 [ChannelProfile](Android-keytype.md#channelprofile) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。 |
| [enableExternalSoundCard](Android-api.md#RTCVideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |
| [getAudioDeviceManager](Android-api.md#RTCVideo-getaudiodevicemanager) | 获取音频设备管理接口 |
| [startAudioPlaybackDeviceTest](Android-api.md#IRTCAudioDeviceManager-startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。 |
| [stopAudioPlaybackDeviceTest](Android-api.md#IRTCAudioDeviceManager-stopaudioplaybackdevicetest) | 停止音频播放测试。 |
| [startAudioDeviceRecordTest](Android-api.md#IRTCAudioDeviceManager-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br> |
| [stopAudioDeviceRecordAndPlayTest](Android-api.md#IRTCAudioDeviceManager-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br><br/>调用 [startAudioDeviceRecordTest](Android-api.md#IRTCAudioDeviceManager-startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
| [stopAudioDevicePlayTest](Android-api.md#IRTCAudioDeviceManager-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Android-api.md#IRTCAudioDeviceManager-startaudiodevicerecordtest) 开始的音频播放设备测试。<br/>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |
| [startHardwareEchoDetection](Android-api.md#RTCVideo-starthardwareechodetection) | 开启通话前回声检测 |
| [stopHardwareEchoDetection](Android-api.md#RTCVideo-stophardwareechodetection) | 停止通话前回声检测 |

## 视频管理

| 方法 | 描述 |
| --- | --- |
| [startVideoCapture](Android-api#RTCVideo-startvideocapture) | 立即开启内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 [onUserStartVideoCapture](Android-callback.md#IRTCVideoEventHandler-onuserstartvideocapture) 的回调。 |
| [stopVideoCapture](Android-api#RTCVideo-stopvideocapture) | 立即关闭内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br/>调用该方法，本地用户会收到 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Android-callback.md#IRTCVideoEventHandler-onuserstopvideocapture) 的回调。 |
| [setVideoCaptureConfig](Android-api.md#RTCVideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。<br><br/>如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。 |
| [setVideoRotationMode](Android-api.md#RTCVideo-setvideorotationmode) | 设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br><br/>接收端渲染视频时，将按照和发送端相同的方式进行旋转。<br> |
| [setLocalVideoCanvas](Android-api.md#RTCVideo-setlocalvideocanvas) | 设置本地视频渲染时使用的视图，并设置渲染模式。 |
| [updateLocalVideoCanvas](Android-api.md#RTCVideo-updatelocalvideocanvas) | 修改本地视频渲染模式和背景色。 |
| [setRemoteVideoCanvas](Android-api.md#RTCVideo-setremotevideocanvas) | 渲染来自指定远端用户的视频流时，设置使用的视图和渲染模式。<br><br/>要解除绑定，将 `videoCanvas` 设置为空。 |
| [updateRemoteStreamVideoCanvas](Android-api.md#RTCVideo-updateremotestreamvideocanvas) | 修改远端视频渲染模式和背景色。 |
| [switchCamera](Android-api#RTCVideo-switchcamera) | 切换视频内部采集时使用的前置/后置摄像头 <br><br/>调用此接口后，在本地会触发 [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 回调。 |
| [isCameraZoomSupported](Android-api.md#RTCVideo-iscamerazoomsupported) | 检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。 |
| [getCameraZoomMaxRatio](Android-api.md#RTCVideo-getcamerazoommaxratio) | 获取当前使用的摄像头（前置/后置）的最大变焦倍数 |
| [setCameraZoomRatio](Android-api.md#RTCVideo-setcamerazoomratio) | 设置当前使用的摄像头（前置/后置）的光学变焦倍数 |
| [isCameraTorchSupported](Android-api.md#RTCVideo-iscameratorchsupported) | 检测当前使用的摄像头（前置/后置），是否支持闪光灯。 |
| [setCameraTorch](Android-api.md#RTCVideo-setcameratorch) | 打开/关闭当前使用的摄像头（前置/后置）的闪光灯 |
| [isCameraFocusPositionSupported](Android-api.md#RTCVideo-iscamerafocuspositionsupported) | 检查当前使用的摄像头是否支持手动对焦。 |
| [setCameraFocusPosition](Android-api.md#RTCVideo-setcamerafocusposition) | 设置当前使用的摄像头的对焦点。 |
| [isCameraExposurePositionSupported](Android-api.md#RTCVideo-iscameraexposurepositionsupported) | 检查当前使用的摄像头是否支持手动设置曝光点。 |
| [setCameraExposurePosition](Android-api.md#RTCVideo-setcameraexposureposition) | 设置当前使用的摄像头的曝光点 |
| [setCameraExposureCompensation](Android-api.md#RTCVideo-setcameraexposurecompensation) | 设置当前使用的摄像头的曝光补偿。 |
| [setVideoEncoderConfig](Android-api.md#RTCVideo-setvideoencoderconfig) | <span id="RTCVideo-setvideoencoderconfig-1"></span>视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br><br/>该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#RTCVideo-setvideoencoderconfig-2) |
| [setVideoEncoderConfig](Android-api.md#RTCVideo-setvideoencoderconfig) | <span id="RTCVideo-setvideoencoderconfig-2"></span>视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |

## 音视频传输

| 方法 | 描述 |
| --- | --- |
| [publishStream](Android-api.md#RTCRoom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream](Android-api.md#RTCRoom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [setDummyCaptureImagePath](Android-api.md#RTCVideo-setdummycaptureimagepath) | 摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。<br/>可重复调用该接口来更新图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。 |
| [subscribeStream](Android-api.md#RTCRoom-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream](Android-api.md#RTCRoom-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreams](Android-api.md#RTCRoom-subscribeallstreams) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreams](Android-api.md#RTCRoom-unsubscribeallstreams) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br><br/>自动订阅和手动订阅的流都可以通过本方法取消订阅。 |
| [pauseAllSubscribedStream](Android-api.md#RTCRoom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Android-api.md#RTCRoom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [requestRemoteVideoKeyFrame](Android-api.md#RTCVideo-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) | 开始跨房间转发媒体流。<br/>在调用 [joinRoom](Android-api.md#RTCRoom-joinroom) 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br> |
| [updateForwardStreamToRooms](Android-api#RTCRoom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br><br/>通过 [startForwardStreamToRooms](Android-api#RTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br/>调用本方法增加或删减房间后，将在本端触发 [onForwardStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。 |
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
| [setPublicStreamAudioPlaybackVolume](Android-api.md#RTCVideo-setpublicstreamaudioplaybackvolume) | 调节公共流的音频播放音量。 |

## 视频处理

| 方法 | 描述 |
| --- | --- |
| [setLocalVideoMirrorType](Android-api.md#RTCVideo-setlocalvideomirrortype) | 为采集到的视频流开启镜像 |
| [setVideoOrientation](Android-api.md#RTCVideo-setvideoorientation) | 在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。<br/>移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。 |
| [setVideoWatermark](Android-api.md#RTCVideo-setvideowatermark) | 在指定视频流上添加水印。 |
| [clearVideoWatermark](Android-api.md#RTCVideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [enableEffectBeauty](Android-api.md#RTCVideo-enableeffectbeauty) | 开启/关闭基础美颜 |
| [setBeautyIntensity](Android-api.md#RTCVideo-setbeautyintensity) | 调整基础美颜强度 |
| [getVideoEffectInterface](Android-api.md#RTCVideo-getvideoeffectinterface) | 获取视频特效接口。 |
| [initCVResource](Android-api.md#IVideoEffect-initcvresource) | 检查视频特效证书，设置算法模型路径，并初始化特效模块。 |
| [enableVideoEffect](Android-api.md#IVideoEffect-enablevideoeffect) | 开启高级美颜、滤镜等视频特效。 |
| [disableVideoEffect](Android-api.md#IVideoEffect-disablevideoeffect) | 关闭视频特效。 |
| [setEffectNodes](Android-api.md#IVideoEffect-seteffectnodes) | 设置视频特效素材包。 |
| [updateEffectNode](Android-api.md#IVideoEffect-updateeffectnode) | 设置特效强度。 |
| [setColorFilter](Android-api.md#IVideoEffect-setcolorfilter) | 设置颜色滤镜。 |
| [setColorFilterIntensity](Android-api.md#IVideoEffect-setcolorfilterintensity) | 设置已启用颜色滤镜的强度。 |
| [enableVirtualBackground](Android-api.md#IVideoEffect-enablevirtualbackground) | 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。 |
| [disableVirtualBackground](Android-api.md#IVideoEffect-disablevirtualbackground) | 关闭虚拟背景。 |
| [enableFaceDetection](Android-api#IVideoEffect-enablefacedetection) | 开启人脸识别功能，并设置人脸检测结果回调观察者。<br/>此观察者后，你会周期性收到 [onFaceDetectResult](Android-callback.md#IFaceDetectionObserver-onfacedetectresult) 回调。 |
| [disableFaceDetection](Android-api.md#IVideoEffect-disablefacedetection) | 关闭人脸识别功能。 |
| [setVideoDigitalZoomConfig](Android-api.md#RTCVideo-setvideodigitalzoomconfig) | 设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。 |
| [setVideoDigitalZoomControl](Android-api.md#RTCVideo-setvideodigitalzoomcontrol) | 控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。 |
| [startVideoDigitalZoomControl](Android-api.md#RTCVideo-startvideodigitalzoomcontrol) | 开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。 |
| [stopVideoDigitalZoomControl](Android-api.md#RTCVideo-stopvideodigitalzoomcontrol) | 停止本地摄像头持续数码变焦。 |

## 音频处理

| 方法 | 描述 |
| --- | --- |
| [setVoiceChangerType](Android-api.md#RTCVideo-setvoicechangertype) | 设置变声特效类型 |
| [setVoiceReverbType](Android-api.md#RTCVideo-setvoicereverbtype) | 设置混响特效类型 |
| [setLocalVoicePitch](Android-api.md#RTCVideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |
| [setLocalVoiceEqualization](Android-api.md#RTCVideo-setlocalvoiceequalization) | 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [setLocalVoiceReverbParam](Android-api.md#RTCVideo-setlocalvoicereverbparam) | 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [enableLocalVoiceReverb](Android-api.md#RTCVideo-enablelocalvoicereverb) | 开启本地音效混响效果 |

## 自定义流处理

| 方法 | 描述 |
| --- | --- |
| [setVideoSourceType](Android-api.md#RTCVideo-setvideosourcetype) | 设置向 SDK 输入的视频源，包括屏幕流<br/>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br> |
| [pushExternalVideoFrame](Android-api.md#RTCVideo-pushexternalvideoframe) | 推送外部视频帧。 |
| [setLocalVideoSink](Android-api.md#RTCVideo-setlocalvideosink) | 将本地视频流与自定义渲染器绑定。 |
| [setRemoteVideoSink](Android-api.md#RTCVideo-setremotevideosink) | 将远端视频流与自定义渲染器绑定。 |
| [registerRemoteEncodedVideoFrameObserver](Android-api#RTCVideo-registerremoteencodedvideoframeobserver) | 注册远端编码后视频数据回調。  <br><br/>完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame](Android-callback.md#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调 |
| [setVideoDecoderConfig](Android-api.md#RTCVideo-setvideodecoderconfig) | 在订阅远端视频流之前，设置远端视频数据解码方式 |
| [setAudioSourceType](Android-api.md#RTCVideo-setaudiosourcetype) | 切换音频采集方式 |
| [setAudioRenderType](Android-api.md#RTCVideo-setaudiorendertype) | 切换音频渲染方式 |
| [pushExternalAudioFrame](Android-api.md#RTCVideo-pushexternalaudioframe) | 推送自定义采集的音频数据到 RTC SDK。 |
| [pullExternalAudioFrame](Android-api.md#RTCVideo-pullexternalaudioframe) | 拉取远端音频数据。<br><br/>可用于自定义音频渲染。 |
| [registerLocalVideoProcessor](Android-api.md#RTCVideo-registerlocalvideoprocessor) | 设置自定义视频前处理器。<br><br/>使用这个视频前处理器，你能够调用 [processVideoFrame](Android-api.md#IVideoProcessor-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。 |
| [processVideoFrame](Android-api.md#IVideoProcessor-processvideoframe) | 获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor](Android-api.md#RTCVideo-registerlocalvideoprocessor) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。 |
| [onGLEnvInitiated](Android-api.md#IVideoProcessor-onglenvinitiated) | OpenGL 环境创建完成时，收到此回调。 |
| [onGLEnvRelease](Android-api.md#IVideoProcessor-onglenvrelease) | OpenGL 环境即将销毁时，收到此回调。此时，你可以释放纹理等资源。 |
| [registerAudioProcessor](Android-api.md#RTCVideo-registeraudioprocessor) | 注册自定义音频处理器。<br><br/>注册完成后，你可以调用 [enableAudioProcessor](Android-api.md#RTCVideo-enableaudioprocessor)，对本地采集或接收到的远端音频进行处理。 |
| [enableAudioProcessor](Android-api.md#RTCVideo-enableaudioprocessor) | 设置并开启指定的音频帧回调，进行自定义处理。 |
| [disableAudioProcessor](Android-api.md#RTCVideo-disableaudioprocessor) | 关闭自定义音频处理。 |
| [registerAudioFrameObserver](Android-api.md#RTCVideo-registeraudioframeobserver) | 注册音频数据回调观察者。  <br> |
| [enableAudioFrameCallback](Android-api.md#RTCVideo-enableaudioframecallback) | 设置并开启指定的音频数据帧回调 |
| [disableAudioFrameCallback](Android-api.md#RTCVideo-disableaudioframecallback) | 关闭音频回调 |
| [registerLocalEncodedVideoFrameObserver](Android-api#RTCVideo-registerlocalencodedvideoframeobserver) | 注册本地视频帧监测器。  <br><br/>无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame](Android-callback.md#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) 回调给用户。 |
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
| [getNetworkTimeInfo](Android-api.md#RTCVideo-getnetworktimeinfo) | 通过 NTP 协议，获取网络时间。 |
| [setCellularEnhancement](Android-api.md#RTCVideo-setcellularenhancement) | 启用蜂窝网络辅助增强，改善通话质量。 |

## 消息

| 方法 | 描述 |
| --- | --- |
| [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [sendUserMessage](Android-api.md#RTCRoom-sendusermessage) | 给房间内指定的用户发送点对点文本消息（P2P）。 |
| [sendUserBinaryMessage](Android-api.md#RTCRoom-senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息（P2P）。 |
| [login](Android-api.md#RTCVideo-login) | 必须先登录，才能调用 [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) 和 [sendServerMessage](Android-api.md#RTCVideo-sendservermessage) 发送房间外点对点消息和向应用服务器发送消息 <br><br/>在调用本接口登录后，如果想要登出，需要调用 [logout](Android-api.md#RTCVideo-logout)。  <br> |
| [logout](Android-api.md#RTCVideo-logout) | 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken](Android-api#RTCVideo-updatelogintoken) | 更新用户用于登录的 Token  <br><br/>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br><br/>调用 [login](Android-api#RTCVideo-login) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [onLoginResult](Android-callback.md#IRTCVideoEventHandler-onloginresult) 回调通知，错误码为 `LOGIN_ERROR_CODE_INVALID_TOKEN`。此时需要重新获取 Token，并调用此方法更新 Token。 |
| [setServerParams](Android-api.md#RTCVideo-setserverparams) | 设置应用服务器参数  <br><br/>客户端调用 [sendServerMessage](Android-api.md#RTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Android-api.md#RTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。 |
| [getPeerOnlineStatus](Android-api.md#RTCVideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom](Android-api.md#RTCVideo-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [sendServerMessage](Android-api.md#RTCVideo-sendservermessage) | 客户端给应用服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Android-api.md#RTCVideo-sendserverbinarymessage) | 客户端给应用服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo](Android-api#RTCVideo-sendstreamsyncinfo) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [onStreamSyncInfoReceived](Android-callback.md#IRTCVideoEventHandler-onstreamsyncinforeceived) 回调。 |
| [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) | <span id="RTCVideo-sendseimessage-2"></span>通过视频帧发送 SEI 数据。<br/>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |

## CDN 推流

| 方法 | 描述 |
| --- | --- |
| [startPushMixedStreamToCDN](Android-api.md#RTCVideo-startpushmixedstreamtocdn) | 新增合流转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br><br/>同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。 |
| [updatePushMixedStreamToCDN](Android-api.md#RTCVideo-updatepushmixedstreamtocdn) | 更新合流转推直播参数，会收到 [onMixingEvent](Android-callback#IMixedStreamObserver-onmixingevent) 回调。  <br><br/>使用 [startPushMixedStreamToCDN](Android-api.md#RTCVideo-startpushmixedstreamtocdn) 启用转推直播功能后，使用此方法更新功能配置参数。 |
| [setAudioAlignmentProperty](Android-api.md#RTCVideo-setaudioalignmentproperty) | 在听众端，设置订阅的所有远端音频流精准对齐后播放。 |
| [startPushSingleStreamToCDN](Android-api.md#RTCVideo-startpushsinglestreamtocdn) | 新增单流转推直播任务。 |
| [stopPushStreamToCDN](Android-api.md#RTCVideo-stoppushstreamtocdn) | 停止转推直播。<br><br/>该方法可用于停止单流转推直播或停止合流转推直播，通过 taskId 区分需要停止的任务。 |

## 混音

| 方法 | 描述 |
| --- | --- |
| [getAudioMixingManager](Android-api.md#RTCVideo-getaudiomixingmanager) | 混音管理接口创建 |
| [enableAudioMixingFrame](Android-api.md#IAudioMixingManager-enableaudiomixingframe) | 启动 PCM 音频数据混音。<br><br/>要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 id。 |
| [disableAudioMixingFrame](Android-api.md#IAudioMixingManager-disableaudiomixingframe) | 关闭 PCM 混音 |
| [pushAudioMixingFrame](Android-api.md#IAudioMixingManager-pushaudiomixingframe) | 推送 PCM 音频帧数据用于混音 |
| [startAudioMixing](Android-api.md#IAudioMixingManager-startaudiomixing) | 开始播放音频文件。<br><br/>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。 |
| [stopAudioMixing](Android-api.md#IAudioMixingManager-stopaudiomixing) | 停止播放音频文件及混音。 |
| [pauseAudioMixing](Android-api.md#IAudioMixingManager-pauseaudiomixing) | 暂停播放音频文件及混音。 |
| [resumeAudioMixing](Android-api.md#IAudioMixingManager-resumeaudiomixing) | 恢复播放音频文件及混音。 |
| [setAudioMixingVolume](Android-api.md#IAudioMixingManager-setaudiomixingvolume) | 调节指定混音的音量大小，包括音频文件混音和 PCM 混音。 |
| [setAllAudioMixingVolume](Android-api.md#IAudioMixingManager-setallaudiomixingvolume) | 设置默认的混音音量大小，包括音频文件混音和 PCM 混音。 |
| [enableVocalInstrumentBalance](Android-api.md#RTCVideo-enablevocalinstrumentbalance) | 开启/关闭音量均衡功能。  <br><br/>开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 [setAudioMixingLoudness](Android-api.md#IAudioMixingManager-setaudiomixingloudness) 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。 |
| [setAudioMixingLoudness](Android-api.md#IAudioMixingManager-setaudiomixingloudness) | 如果你需要使用 `enableVocalInstrumentBalance` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。 |
| [enablePlaybackDucking](Android-api.md#RTCVideo-enableplaybackducking) | 打开/关闭音量闪避功能，适用于在 RTC 通话过程中会同时播放短视频或音乐的场景，如“一起看”、“在线 KTV”等。  <br><br/>开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。 |
| [setAudioMixingPitch](Android-api.md#IAudioMixingManager-setaudiomixingpitch) | 开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。 |
| [getAudioMixingCurrentPosition](Android-api.md#IAudioMixingManager-getaudiomixingcurrentposition) | 获取音频文件播放进度。 |
| [setAudioMixingPosition](Android-api.md#IAudioMixingManager-setaudiomixingposition) | 设置音频文件的起始播放位置。 |
| [getAudioTrackCount](Android-api.md#IAudioMixingManager-getaudiotrackcount) | 获取当前音频文件的音轨索引 |
| [selectAudioTrack](Android-api.md#IAudioMixingManager-selectaudiotrack) | 指定当前音频文件的播放音轨 |
| [setAudioMixingPlaybackSpeed](Android-api.md#IAudioMixingManager-setaudiomixingplaybackspeed) | 设置混音时音频文件的播放速度 |
| [setAudioMixingDualMonoMode](Android-api.md#IAudioMixingManager-setaudiomixingdualmonomode) | 设置当前音频文件的声道模式 |
| [setAudioMixingProgressInterval](Android-api.md#IAudioMixingManager-setaudiomixingprogressinterval) | 设置混音时音频文件播放进度回调的间隔 |
| [preloadAudioMixing](Android-api.md#IAudioMixingManager-preloadaudiomixing) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [unloadAudioMixing](Android-api.md#IAudioMixingManager-unloadaudiomixing) | 卸载指定音乐文件。 |
| [getAudioMixingDuration](Android-api.md#IAudioMixingManager-getaudiomixingduration) | 获取音频文件时长。 |
| [getAudioMixingPlaybackDuration](Android-api.md#IAudioMixingManager-getaudiomixingplaybackduration) | 获取混音音频文件的实际播放时长（单位：毫秒）。 |
| [stopAllAudioMixing](Android-api.md#IAudioMixingManager-stopallaudiomixing) | 停止播放所有音频文件及混音。 |
| [pauseAllAudioMixing](Android-api.md#IAudioMixingManager-pauseallaudiomixing) | 暂停播放所有音频文件及混音。 |
| [resumeAllAudioMixing](Android-api.md#IAudioMixingManager-resumeallaudiomixing) | 恢复播放所有音频文件及混音。 |
| [registerAudioFileFrameObserver](Android-api.md#IAudioMixingManager-registeraudiofileframeobserver) | 注册本地音频文件混音的音频帧观察者。<br/>当本地音频文件混音时，会收到相关回调。 |

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
| [pushScreenVideoFrame](Android-api.md#RTCVideo-pushscreenvideoframe) | 推送屏幕视频帧 |
| [subscribeScreen](Android-api.md#RTCRoom-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen](Android-api.md#RTCRoom-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |

## 安全与加密

| 方法 | 描述 |
| --- | --- |
| [startCloudProxy](Android-api.md#RTCVideo-startcloudproxy) | 开启云代理 |
| [stopCloudProxy](Android-api.md#RTCVideo-stopcloudproxy) | 关闭云代理 |
| [setCustomizeEncryptHandler](Android-api.md#RTCVideo-setcustomizeencrypthandler) | 设置自定义加密和解密方式。 |
| [setEncryptInfo](Android-api.md#RTCVideo-setencryptinfo) | 设置传输时使用内置加密的方式。 |
| [setLocalProxy](Android-api.md#RTCVideo-setlocalproxy) | 设置本地代理。 |

## 高级功能

| 方法 | 描述 |
| --- | --- |
| [startFileRecording](Android-api.md#RTCVideo-startfilerecording) | 该方法将通话过程中的音视频数据录制到本地的文件中。 |
| [stopFileRecording](Android-api.md#RTCVideo-stopfilerecording) | 停止本地录制 |
| [startAudioRecording](Android-api.md#RTCVideo-startaudiorecording) | 开启录制语音通话，生成本地文件。 <br><br/>在进房前后开启录制，如果未打开麦克风采集，录制任务正常进行，只是不会将数据写入生成的本地文件；只有调用 [startAudioCapture](Android-api.md#RTCVideo-startaudiocapture) 接口打开麦克风采集后，才会将录制数据写入本地文件。 |
| [stopAudioRecording](Android-api.md#RTCVideo-stopaudiorecording) | 停止音频文件录制 |
| [setEarMonitorMode](Android-api.md#RTCVideo-setearmonitormode) | 打开/关闭耳返功能。 |
| [setEarMonitorVolume](Android-api.md#RTCVideo-setearmonitorvolume) | 设置耳返音量。 |
| [getSpatialAudio](Android-api.md#RTCRoom-getspatialaudio) | 获取空间音频接口实例。 |
| [disableRemoteOrientation](Android-api.md#ISpatialAudio-disableremoteorientation) | 关闭本地用户朝向对本地用户发声效果的影响。<br><br/>调用此接口后，房间内的其他用户收听本地发声时，声源都在收听者正面。 |
| [enableSpatialAudio](Android-api.md#ISpatialAudio-enablespatialaudio) | 开启/关闭空间音频功能。  <br> |
| [getRangeAudio](Android-api.md#RTCRoom-getrangeaudio) | 获取范围语音接口实例。 |
| [enableRangeAudio](Android-api.md#IRangeAudio-enablerangeaudio) | 开启/关闭范围语音功能。  <br><br/>范围语音是指，在同一 RTC 房间中设定的音频接收距离范围内，本地用户收听到的远端用户音频音量会随着远端用户的靠近/远离而放大/衰减；若远端用户在房间内的位置超出设定范围，则本地用户无法接收其音频。音频接收范围设置参看 [updateReceiveRange](Android-api.md#IRangeAudio-updatereceiverange)。 |
| [setAttenuationModel](Android-api.md#IRangeAudio-setattenuationmodel) | 设置范围语音的音量衰减模式。<br> |
| [setNoAttenuationFlags](Android-api.md#IRangeAudio-setnoattenuationflags) | 添加标签组，用于标记相互之间通话不衰减的用户组。<br><br/>在同一个 RTC 房间中，如果多个用户的标签组之间有交集，那么，他们之间互相通话时，通话不衰减。<br><br/>比如，用户身处多个队伍，队伍成员间通话不衰减。那么，可以为每个队伍绑定专属标签，每个用户的标签组包含用户所属各个队伍的标签。 |
| [updatePosition](Android-api.md#IRangeAudio-updateposition) | 更新本地用户在房间内空间直角坐标系中的位置坐标。 |
| [updateReceiveRange](Android-api.md#IRangeAudio-updatereceiverange) | 更新本地用户的音频收听范围。 |
| [startASR](Android-api#RTCVideo-startasr) | 开启自动语音识别服务。<br><br/>该方法将识别后的用户语音转化成文字，并通过 [onMessage](Android-callback.md#IRTCASREngineEventHandler-onmessage) 事件回调给用户。 |
| [stopASR](Android-api.md#RTCVideo-stopasr) | 关闭语音识别服务 |
| [takeLocalSnapshot](Android-api.md#RTCVideo-takelocalsnapshot) | 截取本地视频画面 |
| [takeRemoteSnapshot](Android-api.md#RTCVideo-takeremotesnapshot) | 截取远端视频画面 |
| [setAnsMode](Android-api.md#RTCVideo-setansmode) | 支持根据业务场景，设置通话中的音频降噪模式。 |
| [updateSelfPosition](Android-api.md#ISpatialAudio-updateselfposition) | 设置本地用户在自建空间直角坐标系中的收听坐标和收听朝向，以实现本地用户预期的空间音频收听效果。 |
| [updateRemotePosition](Android-api.md#ISpatialAudio-updateremoteposition) | 设置房间内某一远端用户在本地用户自建的空间音频坐标系中的发声位置和发声朝向，以实现本地用户预期的空间音频收听效果。 |
| [removeRemotePosition](Android-api.md#ISpatialAudio-removeremoteposition) | 移除调用 [updateRemotePosition](Android-api.md#ISpatialAudio-updateremoteposition) 为某一远端用户设置的空间音频效果。 |
| [removeAllRemotePosition](Android-api.md#ISpatialAudio-removeallremoteposition) | 移除调用 [updateRemotePosition](Android-api.md#ISpatialAudio-updateremoteposition) 为所有远端用户设置的空间音频效果。 |

## 字幕翻译服务

| 方法 | 描述 |
| --- | --- |
| [startSubtitle](Android-api#RTCRoom-startsubtitle) | 识别或翻译房间内所有用户的语音，形成字幕。<br><br/>语音识别或翻译的结果会通过 [onSubtitleMessageReceived](Android-callback.md#IRTCRoomEventHandler-onsubtitlemessagereceived) 事件回调给你。<br><br/>调用该方法后，你会收到 [onSubtitleStateChanged](Android-callback.md#IRTCRoomEventHandler-onsubtitlestatechanged) 回调，通知字幕是否开启。 |
| [stopSubtitle](Android-api#RTCRoom-stopsubtitle) | 关闭字幕。 <br><br/>调用该方法后，用户会收到 [onSubtitleStateChanged](Android-callback.md#IRTCRoomEventHandler-onsubtitlestatechanged) 回调，通知字幕是否关闭。 |

## 音乐及打分

| 方法 | 描述 |
| --- | --- |
| [getKTVManager](Android-api.md#RTCVideo-getktvmanager) | 创建 KTV 管理接口。 |
| [setMaxCacheSize](Android-api.md#KTVManager-setmaxcachesize) | 设置歌曲文件最大占用的本地缓存。 |
| [getMusicList](Android-api.md#KTVManager-getmusiclist) | 获取歌曲列表。|
| [searchMusic](Android-api.md#KTVManager-searchmusic) | 根据关键词搜索歌曲。|
| [getHotMusic](Android-api.md#KTVManager-gethotmusic) | 根据热榜类别获取每个榜单的歌曲列表。|
| [getMusicDetail](Android-api.md#KTVManager-getmusicdetail) | 获取音乐详细信息。|
| [downloadMusic](Android-api.md#KTVManager-downloadmusic) | 下载音乐。|
| [downloadLyric](Android-api.md#KTVManager-downloadlyric) | 下载歌词。|
| [downloadMidi](Android-api.md#KTVManager-downloadmidi) | 下载 MIDI 文件。|
| [cancelDownload](Android-api.md#KTVManager-canceldownload) | 取消下载任务。|
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
| [onSysStats](Android-callback.md#IRTCVideoEventHandler-onsysstats) | 每2秒发生回调，通知当前cpu，内存使用的信息。  <br> |
| [onWarning](Android-callback.md#IRTCVideoEventHandler-onwarning) | 发生警告回调。  <br><br/>SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。 |
| [onError](Android-callback.md#IRTCVideoEventHandler-onerror) | 发生错误回调。<br><br/>SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。<br><br/>你可能需要干预. |
| [onTokenWillExpire](Android-callback#IRTCRoomEventHandler-ontokenwillexpire) | Token 进房权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 进房权限。 |
| [onPublishPrivilegeTokenWillExpire](Android-callback#IRTCRoomEventHandler-onpublishprivilegetokenwillexpire) | Token 发布权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 发布权限。 |
| [onSubscribePrivilegeTokenWillExpire](Android-callback#IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire) | Token 订阅权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Android-api.md#RTCRoom-updatetoken) 更新 Token 订阅权限有效期。 |
| [onLicenseWillExpire](Android-callback.md#IRTCVideoEventHandler-onlicensewillexpire) | license 过期时间提醒 |

## 房间管理

| 回调 | 描述 |
| --- | --- |
| [onRoomStateChanged](Android-callback.md#IRTCRoomEventHandler-onroomstatechanged) | 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。 |
| [onCreateRoomStateChanged](Android-callback.md#IRTCVideoEventHandler-oncreateroomstatechanged) | 创建房间失败回调。 |
| [onLeaveRoom](Android-callback#IRTCRoomEventHandler-onleaveroom) | 离开房间成功回调。  <br><br/>用户调用 [leaveRoom](Android-api.md#RTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br> |
| [onUserJoined](Android-callback#IRTCRoomEventHandler-onuserjoined) | 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br><br/>1.远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br><br/>2.远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br><br/>3.房间内隐身远端用户调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br><br/>4.新进房用户也会收到进房前已在房内的可见用户的进房回调通知。  <br> |
| [onUserLeave](Android-callback.md#IRTCRoomEventHandler-onuserleave) | 远端用户离开房间，或切至不可见时，房间内其他用户会收到此事件 |
| [onRoomStats](Android-callback.md#IRTCRoomEventHandler-onroomstats) | 房间内通话统计信息回调。  <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |
| [onSetRoomExtraInfoResult](Android-callback#IRTCRoomEventHandler-onsetroomextrainforesult) | 调用 [setRoomExtraInfo](Android-api.md#RTCRoom-setroomextrainfo) 设置房间附加信息结果的回调。 |
| [onRoomExtraInfoUpdate](Android-callback#IRTCRoomEventHandler-onroomextrainfoupdate) | 接收同一房间内，其他用户调用 [setRoomExtraInfo](Android-api.md#RTCRoom-setroomextrainfo) 设置的房间附加信息的回调。 |

## 音频管理

| 回调 | 描述 |
| --- | --- |
| [onAudioDeviceWarning](Android-callback.md#IRTCVideoEventHandler-onaudiodevicewarning) | 音频设备警告回调。音频设备包括音频采集设备、音频渲染设备等。 |
| [onAudioRouteChanged](Android-callback.md#IRTCVideoEventHandler-onaudioroutechanged) | 音频播放路由变化时，收到该回调。 |
| [onAudioDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) | 音频设备状态回调。提示音频采集、音频播放等媒体设备的状态。 |
| [onLocalAudioPropertiesReport](Android-callback#IRTCVideoEventHandler-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) 后，你会周期性地收到此回调，了解本地音频的相关信息。  <br><br/>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。 |
| [onRemoteAudioPropertiesReport](Android-callback#IRTCVideoEventHandler-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br><br/>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onActiveSpeaker](Android-callback#IRTCVideoEventHandler-onactivespeaker) | 调用 [enableAudioPropertiesReport](Android-api.md#RTCVideo-enableaudiopropertiesreport) 后，根据设置的 `AudioPropertiesConfig.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [onUserStartAudioCapture](Android-callback#IRTCVideoEventHandler-onuserstartaudiocapture) | 房间内的用户调用 [startAudioCapture](Android-api.md#RTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。 |
| [onUserStopAudioCapture](Android-callback#IRTCVideoEventHandler-onuserstopaudiocapture) | 房间内的用户调用 [stopAudioCapture](Android-api.md#RTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。 |
| [onStreamSyncInfoReceived](Android-callback#IRTCVideoEventHandler-onstreamsyncinforeceived) | 音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Android-api.md#RTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br> |
| [onAudioStreamBanned](Android-callback.md#IRTCRoomEventHandler-onaudiostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [onAudioPlaybackDeviceTestVolume](Android-callback.md#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onHardwareEchoDetectionResult](Android-callback.md#IRTCVideoEventHandler-onhardwareechodetectionresult) | 通话前回声检测结果回调。 |

## 视频管理

| 回调 | 描述 |
| --- | --- |
| [onUserStartVideoCapture](Android-callback#IRTCVideoEventHandler-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Android-api.md#RTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。 |
| [onUserStopVideoCapture](Android-callback#IRTCVideoEventHandler-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Android-api.md#RTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。 |
| [onVideoDeviceStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) | 视频设备状态回调。提示摄像头视频采集、屏幕视频采集等媒体设备的状态。 |
| [onVideoDeviceWarning](Android-callback.md#IRTCVideoEventHandler-onvideodevicewarning) | 视频设备警告回调，包括视频采集等设备。 |
| [onFaceDetectResult](Android-callback.md#IFaceDetectionObserver-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。 <br><br/>调用 [enableFaceDetection](Android-api#IVideoEffect-enablefacedetection) 注册了 [IFaceDetectionObserver](Android-callback.md#ifacedetectionobserver)，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |

## 音视频传输

| 回调 | 描述 |
| --- | --- |
| [onStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onstreamstatechanged) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [onAVSyncStateChange](Android-callback#IRTCRoomEventHandler-onavsyncstatechange) | 发布端调用 [setMultiDeviceAVSync](Android-api.md#RTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。 |
| [onUserPublishStream](Android-callback.md#IRTCRoomEventHandler-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集的媒体流的回调。 |
| [onUserUnpublishStream](Android-callback.md#IRTCRoomEventHandler-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onAudioFrameSendStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudioframesendstatechanged) | 本地音频首帧发送状态发生改变时，收到此回调。 |
| [onVideoFrameSendStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideoframesendstatechanged) | 本地视频首帧发送状态发生改变时，收到此回调。 |
| [onAudioFramePlayStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudioframeplaystatechanged) | 音频首帧播放状态发生改变时，收到此回调。 |
| [onVideoFramePlayStateChanged](Android-callback.md#IRTCVideoEventHandler-onvideoframeplaystatechanged) | 视频首帧播放状态发生改变时，收到此回调。 |
| [onForwardStreamStateChanged](Android-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [onForwardStreamEvent](Android-callback.md#IRTCRoomEventHandler-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [onLocalStreamStats](Android-callback#IRTCRoomEventHandler-onlocalstreamstats) | 本地流数据统计以及网络质量回调。  <br><br/>本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br><br/>统计信息通过 [LocalStreamStats](Android-keytype.md#localstreamstats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [onRemoteStreamStats](Android-callback.md#IRTCRoomEventHandler-onremotestreamstats) | 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br><br/>本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [onNetworkQuality](Android-callback.md#IRTCRoomEventHandler-onnetworkquality) | 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。 |
| [onStreamSubscribed](Android-callback.md#IRTCRoomEventHandler-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onRemoteAudioStateChanged](Android-callback.md#IRTCVideoEventHandler-onremoteaudiostatechanged) | 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。 |
| [onFirstLocalAudioFrame](Android-callback.md#IRTCVideoEventHandler-onfirstlocalaudioframe) | 发布音频流时，采集到第一帧音频帧，收到该回调。 |
| [onFirstRemoteAudioFrame](Android-callback.md#IRTCVideoEventHandler-onfirstremoteaudioframe) | 接收到来自远端某音频流的第一帧时，收到该回调。 |
| [onRemoteVideoStateChanged](Android-callback.md#IRTCVideoEventHandler-onremotevideostatechanged) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [onFirstRemoteVideoFrameRendered](Android-callback.md#IRTCVideoEventHandler-onfirstremotevideoframerendered) | SDK 内部渲染成功远端视频流首帧后，收到此回调。 |
| [onFirstLocalVideoFrameCaptured](Android-callback.md#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) | RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。 |
| [onLocalVideoSizeChanged](Android-callback.md#IRTCVideoEventHandler-onlocalvideosizechanged) | 本地预览视频大小或旋转信息发生改变时，收到此回调。 |
| [onRemoteVideoSizeChanged](Android-callback.md#IRTCVideoEventHandler-onremotevideosizechanged) | 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onFirstRemoteVideoFrameDecoded](Android-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [onVideoStreamBanned](Android-callback.md#IRTCRoomEventHandler-onvideostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [onPushPublicStreamResult](Android-callback#IRTCVideoEventHandler-onpushpublicstreamresult) | 公共流发布结果回调。<br><br/>调用 [startPushPublicStream](Android-api.md#RTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。 |
| [onPlayPublicStreamResult](Android-callback#IRTCVideoEventHandler-onplaypublicstreamresult) | 订阅公共流的结果回调  <br><br/>调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到启动结果和拉流过程中的错误。 |
| [onPublicStreamSEIMessageReceived](Android-callback#IRTCVideoEventHandler-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br/>调用 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [onFirstPublicStreamVideoFrameDecoded](Android-callback#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) | 公共流的首帧视频解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。 |
| [onFirstPublicStreamAudioFrame](Android-callback#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Android-api.md#RTCVideo-startplaypublicstream)。 |

## 自定义流处理

| 回调 | 描述 |
| --- | --- |
| [onStart](Android-callback#IExternalVideoEncoderEventHandler-onstart) | 提示自定义编码帧可以开始推送的回调。  <br><br/>收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Android-api.md#RTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧 |
| [onStop](Android-callback.md#IExternalVideoEncoderEventHandler-onstop) | 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧 |
| [onRateUpdate](Android-callback.md#IExternalVideoEncoderEventHandler-onrateupdate) | 当自定义编码流的帧率或码率发生变化时，触发该回调 |
| [onRequestKeyFrame](Android-callback.md#IExternalVideoEncoderEventHandler-onrequestkeyframe) | 提示流发布端需重新生成关键帧的回调 |
| [onLocalEncodedVideoFrame](Android-callback#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) | 调用 [registerLocalEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。 |
| [onRemoteEncodedVideoFrame](Android-callback#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) | 调用 [registerRemoteEncodedVideoFrameObserver](Android-api.md#RTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调 |
| [onProcessEarMonitorAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessearmonitoraudioframe) | 软件耳返音频数据的回调。你可根据此回调自定义处理音频。<br/>软件耳返音频中包含通过调用 `setVoiceReverbType` 和 `setVoiceChangerType` 设置的音频特效。 |
| [onProcessPlayBackAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessplaybackaudioframe) | 回调远端音频混音的音频帧地址，供自定义音频处理。 |
| [onProcessRecordAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessrecordaudioframe) | 回调本地采集的音频帧地址，供自定义音频处理。 |
| [onProcessRemoteUserAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessremoteuseraudioframe) | 回调单个远端用户的音频帧地址，供自定义音频处理。 |
| [onProcessScreenAudioFrame](Android-callback.md#IAudioFrameProcessor-onprocessscreenaudioframe) | 屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。 |
| [onRecordAudioFrame](Android-callback.md#IAudioFrameObserver-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame](Android-callback.md#IAudioFrameObserver-onplaybackaudioframe) | 返回订阅的所有远端用户混音后的音频数据。 |
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
| [onSEIMessageReceived](Android-callback#IRTCVideoEventHandler-onseimessagereceived) | 收到通过调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 发送带有 SEI 消息的视频帧时，收到此回调。 |
| [onEchoTestResult](Android-callback.md#IRTCVideoEventHandler-onechotestresult) | 关于音视频回路测试结果的回调。 |
| [onNetworkTimeSynchronized](Android-callback#IRTCVideoEventHandler-onnetworktimesynchronized) | 首次调用 [getNetworkTimeInfo](Android-api.md#RTCVideo-getnetworktimeinfo) 后，SDK内部启动网络时间同步，同步完成时会触发此回调。 |

## 消息

| 回调 | 描述 |
| --- | --- |
| [onRoomMessageReceived](Android-callback#IRTCRoomEventHandler-onroommessagereceived) | 接收到房间内广播消息的回调。<br><br/>房间内其他用户调用 [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) 发送广播消息时，收到此回调。 |
| [onRoomBinaryMessageReceived](Android-callback#IRTCRoomEventHandler-onroombinarymessagereceived) | 收到房间内广播二进制消息的回调。<br><br/>房间内其他用户调用 [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) 发送广播二进制消息时，收到此回调。 |
| [onUserMessageReceived](Android-callback#IRTCRoomEventHandler-onusermessagereceived) | 收到来自房间中其他用户通过 [sendUserMessage](Android-api.md#RTCRoom-sendusermessage) 发来的点对点文本消息时，会收到此回调。 |
| [onUserBinaryMessageReceived](Android-callback#IRTCRoomEventHandler-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 [sendUserBinaryMessage](Android-api.md#RTCRoom-senduserbinarymessage) 发来的点对点二进制消息时，会收到此回调。 |
| [onUserMessageSendResult](Android-callback.md#IRTCRoomEventHandler-onusermessagesendresult) | 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。 |
| [onRoomMessageSendResult](Android-callback#IRTCRoomEventHandler-onroommessagesendresult) | 调用 [sendRoomMessage](Android-api.md#RTCRoom-sendroommessage) 或 [sendRoomBinaryMessage](Android-api.md#RTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onLoginResult](Android-callback.md#IRTCVideoEventHandler-onloginresult) | 登录结果回调 |
| [onLogout](Android-callback.md#IRTCVideoEventHandler-onlogout) | 登出结果回调 |
| [onServerParamsSetResult](Android-callback.md#IRTCVideoEventHandler-onserverparamssetresult) | 设置应用服务器参数的返回结果 |
| [onGetPeerOnlineStatus](Android-callback.md#IRTCVideoEventHandler-ongetpeeronlinestatus) | 查询对端或本端用户登录状态的返回结果 |
| [onUserMessageReceivedOutsideRoom](Android-callback#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserMessageOutsideRoom](Android-api.md#RTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调 |
| [onUserBinaryMessageReceivedOutsideRoom](Android-callback#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Android-api.md#RTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调 |
| [onUserMessageSendResultOutsideRoom](Android-callback.md#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) | 给房间外指定的用户发送消息的回调 |
| [onServerMessageSendResult](Android-callback.md#IRTCVideoEventHandler-onservermessagesendresult) | 给应用服务器发送消息的回调。 |
| [onSEIStreamUpdate](Android-callback#IRTCVideoEventHandler-onseistreamupdate) | 黑帧视频流发布状态回调。  <br><br/>在语音通话场景下，本地用户调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br><br/>你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。 |

## CDN 推流

| 回调 | 描述 |
| --- | --- |
| [onStreamMixingEvent](Android-callback.md#ILiveTranscodingObserver-onstreammixingevent) | 转推直播状态回调 |
| [isSupportClientPushStream](Android-callback.md#ILiveTranscodingObserver-issupportclientpushstream) | 是否具有推流能力。  <br><br/>+ false：不具备推流能力（默认值）  <br><br/>+ true：具备推流能力 |
| [onMixingAudioFrame](Android-callback.md#ILiveTranscodingObserver-onmixingaudioframe) | 端云一体合流音频 PCM 回调 |
| [onMixingVideoFrame](Android-callback.md#ILiveTranscodingObserver-onmixingvideoframe) | 端云一体合流视频 YUV 回调 |
| [onMixingDataFrame](Android-callback.md#ILiveTranscodingObserver-onmixingdataframe) | 端云一体合流视频 SEI 数据回调 |
| [onStreamPushEvent](Android-callback.md#IPushSingleStreamToCDNObserver-onstreampushevent) | 单流转推直播状态回调 |

## 混音

| 回调 | 描述 |
| --- | --- |
| [onAudioMixingStateChanged](Android-callback.md#IRTCVideoEventHandler-onaudiomixingstatechanged) | 音频混音文件播放状态改变时回调 |
| [onAudioMixingPlayingProgress](Android-callback.md#IRTCVideoEventHandler-onaudiomixingplayingprogress) | 混音音频文件播放进度回调 |
| [onAudioFileFrame](Android-callback.md#IAudioFileFrameObserver-onaudiofileframe) | 当本地音频文件混音时，回调播放的音频帧。 |

## 屏幕分享

| 回调 | 描述 |
| --- | --- |
| [onUserPublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onScreenVideoFrameSendStateChanged](Android-callback.md#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) | 屏幕共享流的视频首帧发送状态发生改变时，收到此回调。 |
| [onScreenVideoFramePlayStateChanged](Android-callback.md#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) | 屏幕共享流视频首帧播放状态发生改变时，收到此回调。 |

## 安全与加密

| 回调 | 描述 |
| --- | --- |
| [onCloudProxyConnected](Android-callback#IRTCVideoEventHandler-oncloudproxyconnected) | 调用 [startCloudProxy](Android-api.md#RTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onEncryptData](Android-callback.md#IRTCEncryptionHandler-onencryptdata) | 自定义加密。  <br><br/>使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br><br/>暂不支持对原始音视频帧进行加密。 |
| [onDecryptData](Android-callback.md#IRTCEncryptionHandler-ondecryptdata) | 自定义解密。  <br><br/>对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData](Android-callback.md#IRTCEncryptionHandler-onencryptdata)。 |
| [onLocalProxyStateChanged](Android-callback#IRTCVideoEventHandler-onlocalproxystatechanged) | 本地代理状态发生改变回调。调用 [setLocalProxy](Android-api.md#RTCVideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，通知代理连接的状态。  <br> |

## 高级功能

| 回调 | 描述 |
| --- | --- |
| [onRecordingStateUpdate](Android-callback#IRTCVideoEventHandler-onrecordingstateupdate) | 获取本地录制状态回调。  <br><br/>该回调由 [startFileRecording](Android-api.md#RTCVideo-startfilerecording) 或 [stopFileRecording](Android-api.md#RTCVideo-stopfilerecording) 触发。 |
| [onRecordingProgressUpdate](Android-callback#IRTCVideoEventHandler-onrecordingprogressupdate) | 本地录制进度回调。  <br><br/>该回调由 [startFileRecording](Android-api.md#RTCVideo-startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。 |
| [onAudioRecordingStateUpdate](Android-callback#IRTCVideoEventHandler-onaudiorecordingstateupdate) | 调用 [startAudioRecording](Android-api.md#RTCVideo-startaudiorecording) 或 [stopAudioRecording](Android-api.md#RTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。 |
| [onTakeLocalSnapshotResult](Android-callback#ISnapshotResultCallback-ontakelocalsnapshotresult) | 调用 [takeLocalSnapshot](Android-api.md#RTCVideo-takelocalsnapshot) 截取视频画面时，收到此回调。 |
| [onTakeRemoteSnapshotResult](Android-callback#ISnapshotResultCallback-ontakeremotesnapshotresult) | 调用 [takeRemoteSnapshot](Android-api.md#RTCVideo-takeremotesnapshot) 截取视频画面时，收到此回调。 |

## 字幕翻译服务

| 回调 | 描述 |
| --- | --- |
| [onSubtitleStateChanged](Android-callback#IRTCRoomEventHandler-onsubtitlestatechanged) | 字幕状态发生改变回调。 <br><br/>当用户调用 [startSubtitle](Android-api.md#RTCRoom-startsubtitle) 和 [stopSubtitle](Android-api.md#RTCRoom-stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。 |
| [onSubtitleMessageReceived](Android-callback#IRTCRoomEventHandler-onsubtitlemessagereceived) | 字幕相关内容回调。 <br><br/>当用户成功调用 [startSubtitle](Android-api.md#RTCRoom-startsubtitle) 后会收到此回调，通知字幕的相关信息。 |

## 音乐及打分

| 回调 | 描述 |
| --- | --- |
| [onMusicListResult](Android-callback.md#IKTVManagerEventHandler-onmusiclistresult) | 歌曲列表回调。 |
| [onSearchMusicResult](Android-callback.md#IKTVManagerEventHandler-onsearchmusicresult) | 搜索歌曲结果回调。 |
| [onHotMusicResult](Android-callback.md#IKTVManagerEventHandler-onhotmusicresult) | 热榜歌曲结果回调。 |
| [onMusicDetailResult](Android-callback.md#IKTVManagerEventHandler-onmusicdetailresult) | 歌曲详细信息回调。 |
| [onDownloadSuccess](Android-callback.md#IKTVManagerEventHandler-ondownloadsuccess) | 下载成功回调。 |
| [onDownloadMusicProgress](Android-callback.md#IKTVManagerEventHandler-ondownloadmusicprogress) | 歌曲文件下载进度回调。 |
| [onPlayProgress](Android-callback.md#IKTVPlayerEventHandler-onplayprogress) | 音乐播放进度回调。 |
| [onCurrentScoringInfo](Android-callback#ISingScoringEventHandler-oncurrentscoringinfo) | 实时评分信息回调。调用 [startSingScoring](Android-api.md#ISingScoringManager-startsingscoring) 后，会收到该回调。 |