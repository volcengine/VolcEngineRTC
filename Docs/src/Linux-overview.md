---
is_dir: False    # True for dir; False for doc
status: 1    # 1 for online; 0 for offline
keywords: 实时音视频    # use ',' as separator
---

# 方法
## 引擎管理
| 方法 | 描述 |
| --- | --- |
| [createRTCVideo](Linux-api#creatertcvideo) | 创建 IRTCVideo 实例。  <br><br/>如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。 <br/>如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。 |
| [destroyRTCVideo](Linux-api#destroyrtcvideo) | 销毁由 [createRTCVideo](Linux-api#creatertcvideo) 所创建的引擎实例，并释放所有相关资源。<br> |
| [getSDKVersion](Linux-api#getsdkversion) | 获取当前 SDK 版本信息。 |
| [feedback](Linux-api#IRTCVideo-feedback) | 将用户反馈的问题上报到 RTC。 |
| [getErrorDescription](Linux-api#geterrordescription) | 获取 SDK 内各种错误码、警告码的描述文字。 |
| [setBusinessId](Linux-api#IRTCVideo-setbusinessid) | 设置业务标识参数  <br><br/>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setRuntimeParameters](Linux-api#IRTCVideo-setruntimeparameters) | 设置运行时的参数 |
| [setLogConfig](Windows-api#setlogconfig) | 配置 SDK 本地日志参数，包括日志级别、存储路径、日志文件最大占用的总空间、日志文件名前缀。 |
## 房间管理
| 方法 | 描述 |
| --- | --- |
| [createRTCRoom](Linux-api#IRTCVideo-creatertcroom) | 创建房间实例。<br><br/>调用此方法仅返回一个房间实例，你仍需调用 [joinRoom](Linux-api#IRTCRoom-joinroom) 才能真正地创建/加入房间。<br><br/>多次调用此方法以创建多个 [IRTCRoom](Linux-api#irtcroom) 实例。分别调用各 IRTCRoom 实例中的 [joinRoom](Linux-api#IRTCRoom-joinroom) 方法，同时加入多个房间。<br><br/>多房间模式下，用户可以同时订阅各房间的音视频流。 |
| [destroy](Linux-api#IRTCRoom-destroy) | 退出并销毁调用 [createRTCRoom](Linux-api#IRTCVideo-creatertcroom) 所创建的房间实例。 |
| [setRTCRoomEventHandler](Linux-api#IRTCRoom-setrtcroomeventhandler) | 通过设置 [IRTCRoom](Linux-api#irtcroom) 对象的事件句柄，监听此对象对应的回调事件。 |
| [joinRoom](Linux-api#IRTCRoom-joinroom) | 加入房间。<br><br/>调用 [createRTCRoom](Linux-api#IRTCVideo-creatertcroom) 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br> |
| [setRoomExtraInfo](Linux-api#IRTCRoom-setroomextrainfo) | 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。 |
| [leaveRoom](Linux-api#IRTCRoom-leaveroom) | 离开房间。  <br><br/>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br><br/>加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br><br/>此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 [onLeaveRoom](Linux-callback#IRTCRoomEventHandler-onleaveroom) 回调通知。  <br> |
| [setUserVisibility](Linux-api#IRTCRoom-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br/>默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，最多 30 人可同时上麦。更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。 |
| [updateToken](Linux-api#IRTCRoom-updatetoken) | 更新 Token。<br/>收到 [onTokenWillExpire](Linux-callback#IRTCRoomEventHandler-ontokenwillexpire)，[onPublishPrivilegeTokenWillExpire](Linux-callback#IRTCRoomEventHandler-onpublishprivilegetokenwillexpire)， 或 [onSubscribePrivilegeTokenWillExpire](Linux-callback#IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire) 时，你必须重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。 |
## 音频管理
| 方法 | 描述 |
| --- | --- |
| [buildAudioFrame](Linux-api#buildaudioframe) | 创建 IAudioFrame |
| [enumerateAudioPlaybackDevices](Linux-api#IAudioDeviceManager-enumerateaudioplaybackdevices) | 获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 `onAudioMediaDeviceStateChanged` 回调通知，然后需要重新调用本接口以获得新的设备列表。 |
| [enumerateAudioCaptureDevices](Linux-api#IAudioDeviceManager-enumerateaudiocapturedevices) | 获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。 |
| [setAudioPlaybackDevice](Linux-api#IAudioDeviceManager-setaudioplaybackdevice) | 设置音频播放设备。 |
| [setAudioCaptureDevice](Linux-api#IAudioDeviceManager-setaudiocapturedevice) | 设置音频采集设备。 |
| [getAudioPlaybackDevice](Linux-api#IAudioDeviceManager-getaudioplaybackdevice) | 获取当前音频播放设备 ID。 |
| [getAudioCaptureDevice](Linux-api#IAudioDeviceManager-getaudiocapturedevice) | 获取当前音频采集设备 ID。 |
| [followSystemPlaybackDevice](Linux-api#IAudioDeviceManager-followsystemplaybackdevice) | 设置音频播放路由是否跟随系统。 |
| [followSystemCaptureDevice](Linux-api#IAudioDeviceManager-followsystemcapturedevice) | 设置音频采集路由是否跟随系统。 |
| [setAudioPlaybackDeviceVolume](Linux-api#IAudioDeviceManager-setaudioplaybackdevicevolume) | 设置当前音频播放设备音量 |
| [getAudioPlaybackDeviceVolume](Linux-api#IAudioDeviceManager-getaudioplaybackdevicevolume) | 获取当前音频播放设备音量 |
| [setAudioCaptureDeviceVolume](Linux-api#IAudioDeviceManager-setaudiocapturedevicevolume) | 设置当前音频采集设备音量 |
| [getAudioCaptureDeviceVolume](Linux-api#IAudioDeviceManager-getaudiocapturedevicevolume) | 获取当前音频采集设备音量 |
| [setAudioPlaybackDeviceMute](Linux-api#IAudioDeviceManager-setaudioplaybackdevicemute) | 设置当前音频播放设备静音状态，默认为非静音。 |
| [getAudioPlaybackDeviceMute](Linux-api#IAudioDeviceManager-getaudioplaybackdevicemute) | 获取当前音频播放设备是否静音的信息。 |
| [setAudioCaptureDeviceMute](Linux-api#IAudioDeviceManager-setaudiocapturedevicemute) | 设置当前音频采集设备静音状态，默认为非静音。 |
| [getAudioCaptureDeviceMute](Linux-api#IAudioDeviceManager-getaudiocapturedevicemute) | 获取当前音频采集设备是否静音的信息。 |
| [startAudioPlaybackDeviceTest](Linux-api#IAudioDeviceManager-startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。 |
| [stopAudioPlaybackDeviceTest](Linux-api#IAudioDeviceManager-stopaudioplaybackdevicetest) | 停止音频播放测试。  <br> |
| [initAudioPlaybackDeviceForTest](Linux-api#IAudioDeviceManager-initaudioplaybackdevicefortest) | 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。 |
| [initAudioCaptureDeviceForTest](Linux-api#IAudioDeviceManager-initaudiocapturedevicefortest) | 尝试初始化音频采集设备，可检测设备不存在、权限被拒绝/禁用等异常问题。 |
| [setCaptureVolume](Linux-api#IRTCVideo-setcapturevolume) | 调节音频采集音量 |
| [setPlaybackVolume](Linux-api#IRTCVideo-setplaybackvolume) | 调节本地播放的所有远端用户音频混音后的音量，混音内容包括远端人声、音乐、音效等。<br><br/>播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume](Linux-api#IRTCVideo-setremoteaudioplaybackvolume) | 调节来自指定远端用户的音频播放音量。 |
| [setRemoteRoomAudioPlaybackVolume](Linux-api#IRTCRoom-setremoteroomaudioplaybackvolume) | 调节某个房间内所有远端用户的音频播放音量。 |
| [startAudioCapture](Linux-api#IRTCVideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法开启后，本地用户会收到 [onAudioDeviceStateChanged](Linux-callback#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。 <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Linux-callback#IRTCVideoEventHandler-onuserstartaudiocapture) 的回调。 |
| [stopAudioCapture](Linux-api#IRTCVideo-stopaudiocapture) | 立即关闭内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法，本地用户会收到 [onAudioDeviceStateChanged](Linux-callback#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>可见用户进房后调用该方法后，房间中的其他用户会收到 [onUserStopAudioCapture](Linux-callback#IRTCVideoEventHandler-onuserstopaudiocapture) 的回调。 |
| [enableAudioPropertiesReport](Linux-api#IRTCVideo-enableaudiopropertiesreport) | 启用音频信息提示。开启提示后，你会收到 [onLocalAudioPropertiesReport](Linux-callback#IRTCVideoEventHandler-onlocalaudiopropertiesreport)，[onRemoteAudioPropertiesReport](Linux-callback#IRTCVideoEventHandler-onremoteaudiopropertiesreport) 和 [onActiveSpeaker](Linux-callback#IRTCVideoEventHandler-onactivespeaker)。 |
| [startScreenAudioCapture](Linux-api#IRTCVideo-startscreenaudiocapture) | 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频 |
| [stopScreenAudioCapture](Linux-api#IRTCVideo-stopscreenaudiocapture) | 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。 |
| [setAudioProfile](Linux-api#IRTCVideo-setaudioprofile) | 设置音质档位。<br><br/>当所选的 [RoomProfileType](Linux-keytype#roomprofiletype) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。 |
| [getAudioDeviceManager](Linux-api#IRTCVideo-getaudiodevicemanager) | 设备音频管理接口创建 |
| [enableExternalSoundCard](Linux-api#IRTCVideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |
| [enableAGC](Linux-api#IRTCVideo-enableagc) | 打开/关闭 AGC(Automatic Gain Control) 自动增益控制功能。<br><br/>开启该功能后，SDK 会自动调节麦克风的采集音量，确保音量稳定。 |
## 视频管理
| 方法 | 描述 |
| --- | --- |
| [startVideoCapture](Linux-api#IRTCVideo-startvideocapture) | 立即开启内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Linux-callback#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 [onUserStartVideoCapture](Linux-callback#IRTCVideoEventHandler-onuserstartvideocapture) 的回调。 |
| [stopVideoCapture](Linux-api#IRTCVideo-stopvideocapture) | 立即关闭内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Linux-callback#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Linux-callback#IRTCVideoEventHandler-onuserstopvideocapture) 的回调。 |
| [setVideoCaptureConfig](Linux-api#IRTCVideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。<br><br/>如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数，包括模式、分辨率、帧率。 |
| [setLocalVideoCanvas](Linux-api#IRTCVideo-setlocalvideocanvas) | 设置本地视频渲染时使用的视图，并设置渲染模式。 |
| [updateLocalVideoCanvas](Linux-api#IRTCVideo-updatelocalvideocanvas) | 修改本地视频渲染模式和背景色。 |
| [setRemoteVideoCanvas](Linux-api#IRTCVideo-setremotevideocanvas) | 设置渲染指定视频流 `stream_key` 时，使用的视图和渲染模式。 <br><br/>如果需要解除某个用户的绑定视图，你可以把 `canvas` 设置为空。 |
| [enumerateVideoCaptureDevices](Linux-api#IVideoDeviceManager-enumeratevideocapturedevices) | 获取当前系统内视频采集设备列表。 |
| [getVideoCaptureDevice](Linux-api#IVideoDeviceManager-getvideocapturedevice) | 获取当前 SDK 正在使用的视频采集设备信息 |
| [setVideoCaptureDevice](Linux-api#IVideoDeviceManager-setvideocapturedevice) | 设置当前视频采集设备 |
| [getVideoDeviceManager](Linux-api#IRTCVideo-getvideodevicemanager) | 创建视频设备管理实例 |
| [buildVideoFrame](Linux-api#buildvideoframe) | 创建 IVideoFrame |
| [setVideoEncoderConfig](Linux-api#IRTCVideo-setvideoencoderconfig) | <span id="IRTCVideo-setvideoencoderconfig-1"></span> 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br><br/>该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2)。 |
| [setVideoEncoderConfig](Linux-api#IRTCVideo-setvideoencoderconfig-2) | <span id="IRTCVideo-setvideoencoderconfig-2"></span> 视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [buildEncodedVideoFrame](Linux-api#buildencodedvideoframe) | 创建 IEncodedVideoFrame |
## 音视频传输
| 方法 | 描述 |
| --- | --- |
| [publishStream](Linux-api#IRTCRoom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream](Linux-api#IRTCRoom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [setDummyCaptureImagePath](Linux-api#IRTCVideo-setdummycaptureimagepath) | 摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。<br/>调用 `stopVideoCapture` 接口时，会开始推静态图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。<br/>可重复调用该接口来更新图片。 |
| [subscribeStream](Linux-api#IRTCRoom-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream](Linux-api#IRTCRoom-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreams](Linux-api#IRTCRoom-subscribeallstreams) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreams](Linux-api#IRTCRoom-unsubscribeallstreams) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br><br/>自动订阅和手动订阅的流都可以通过本方法取消订阅。 |
| [requestRemoteVideoKeyFrame](Linux-api#IRTCVideo-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [startForwardStreamToRooms](Linux-api#IRTCRoom-startforwardstreamtorooms) | 开始跨房间转发媒体流。<br/>在调用 [joinRoom](Linux-api#IRTCRoom-joinroom) 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br> |
| [stopForwardStreamToRooms](Linux-api#IRTCRoom-stopforwardstreamtorooms) | 停止跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Linux-api#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。 |
| [updateForwardStreamToRooms](Linux-api#IRTCRoom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br><br/>通过 [startForwardStreamToRooms](Linux-api#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br/>调用本方法增加或删减房间后，将在本端触发 [onForwardStreamStateChanged](Linux-callback#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。 |
| [pauseForwardStreamToAllRooms](Linux-api#IRTCRoom-pauseforwardstreamtoallrooms) | 暂停跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Linux-api#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br/>调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](Linux-api#IRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。 |
| [resumeForwardStreamToAllRooms](Linux-api#IRTCRoom-resumeforwardstreamtoallrooms) | 恢复跨房间媒体流转发。<br/>调用 [pauseForwardStreamToAllRooms](Linux-api#IRTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。 |
| [pauseAllSubscribedStream](Linux-api#IRTCRoom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Linux-api#IRTCRoom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [setMultiDeviceAVSync](Linux-api#IRTCRoom-setmultideviceavsync) | 设置发流端音画同步。  <br><br/>当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。 |
| [startPushPublicStream](Linux-api#IRTCVideo-startpushpublicstream) | 发布一路公共流<br><br/>用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream](Linux-api#IRTCVideo-startplaypublicstream) 获取和播放指定的公共流。 |
| [stopPushPublicStream](Linux-api#IRTCVideo-stoppushpublicstream) | 停止发布当前用户发布的公共流<br><br/>关于发布公共流，查看 [startPushPublicStream](Linux-api#IRTCVideo-startpushpublicstream)。 |
| [updatePublicStreamParam](Linux-api#IRTCVideo-updatepublicstreamparam) | 更新公共流参数<br><br/>关于发布公共流，查看 [startPushPublicStream](Linux-api#IRTCVideo-startpushpublicstream)。 |
| [startPlayPublicStream](Linux-api#IRTCVideo-startplaypublicstream) | 订阅指定公共流<br><br/>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream](Linux-api#IRTCVideo-stopplaypublicstream) | 取消订阅指定公共流<br><br/>关于订阅公共流，查看 [startPlayPublicStream](Linux-api#IRTCVideo-startplaypublicstream)。 |
| [setPublicStreamVideoCanvas](Linux-api#IRTCVideo-setpublicstreamvideocanvas) | 为指定公共流绑定内部渲染视图。 |
| [setPublicStreamVideoSink](Linux-api#IRTCVideo-setpublicstreamvideosink) | 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。 |
| [setPublicStreamAudioPlaybackVolume](Linux-api#IRTCVideo-setpublicstreamaudioplaybackvolume) | 调节公共流的音频播放音量。 |
## 视频处理
| 方法 | 描述 |
| --- | --- |
| [setLowLightAdjusted](Linux-api#IRTCVideo-setlowlightadjusted) | 设置视频暗光增强模式。<br/>对于光线不足、照明不均匀或背光等场景下推荐开启，可有效改善画面质量。 |
| [setRemoteVideoMirrorType](Linux-api#IRTCVideo-setremotevideomirrortype) | 使用内部渲染时，为远端流开启镜像。 |
| [setVideoCaptureRotation](Linux-api#IRTCVideo-setvideocapturerotation) | 设置本端采集的视频帧的旋转角度。<br/>当摄像头倒置或者倾斜安装时，可调用本接口进行调整。 |
| [setVideoWatermark](Linux-api#IRTCVideo-setvideowatermark) | 在指定视频流上添加水印。 |
| [clearVideoWatermark](Linux-api#IRTCVideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [setVideoDigitalZoomConfig](Linux-api#IRTCVideo-setvideodigitalzoomconfig) | 设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。 |
| [setVideoDigitalZoomControl](Linux-api#IRTCVideo-setvideodigitalzoomcontrol) | 控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。 |
| [startVideoDigitalZoomControl](Linux-api#IRTCVideo-startvideodigitalzoomcontrol) | 开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。 |
| [stopVideoDigitalZoomControl](Linux-api#IRTCVideo-stopvideodigitalzoomcontrol) | 停止本地摄像头持续数码变焦。 |
## 音频处理
| 方法 | 描述 |
| --- | --- |
| [setLocalVoicePitch](Linux-api#IRTCVideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |
## 自定义流处理
| 方法 | 描述 |
| --- | --- |
| [setVideoSourceType](Linux-api#IRTCVideo-setvideosourcetype) | 设置向 SDK 输入的视频源，包括屏幕流<br/>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br> |
| [pushExternalVideoFrame](Linux-api#IRTCVideo-pushexternalvideoframe) | 推送外部视频帧。 |
| [setLocalVideoRender](Linux-api#IRTCVideo-setlocalvideorender) | 将本地视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。 |
| [setRemoteVideoRender](Linux-api#IRTCVideo-setremotevideorender) | 将远端视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。 |
| [registerRemoteEncodedVideoFrameObserver](Linux-api#IRTCVideo-registerremoteencodedvideoframeobserver) | 注册远端编码后视频数据回调。  <br><br/>完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame](Linux-callback#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调 |
| [setVideoDecoderConfig](Linux-api#IRTCVideo-setvideodecoderconfig) | 在订阅远端视频流之前，设置远端视频数据解码方式 |
| [registerLocalVideoProcessor](Linux-api#IRTCVideo-registerlocalvideoprocessor) | 设置自定义视频前处理器。<br><br/>使用这个视频前处理器，你可以调用 [processVideoFrame](Linux-api#IVideoProcessor-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。 |
| [processVideoFrame](Linux-api#IVideoProcessor-processvideoframe) | 获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor](Linux-api#IRTCVideo-registerlocalvideoprocessor) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。 |
| [registerAudioProcessor](Linux-api#IRTCVideo-registeraudioprocessor) | 注册自定义音频处理器。<br><br/>注册完成后，你可以调用 [enableAudioProcessor](Linux-api#IRTCVideo-enableaudioprocessor)，对本地采集到的音频进行处理，RTC SDK 将对处理后的音频进行编码和发送。也可以对接收到的远端音频进行自定义处理，RTC SDK 将对处理后的音频进行渲染。 |
| [enableAudioProcessor](Linux-api#IRTCVideo-enableaudioprocessor) | 设置并开启指定的音频帧回调，进行自定义处理。 |
| [disableAudioProcessor](Linux-api#IRTCVideo-disableaudioprocessor) | 关闭自定义音频处理。 |
| [registerAudioFrameObserver](Linux-api#IRTCVideo-registeraudioframeobserver) | 注册音频数据回调观察者。  <br> |
| [enableAudioFrameCallback](Linux-api#IRTCVideo-enableaudioframecallback) | 设置并开启指定的音频数据帧回调 |
| [disableAudioFrameCallback](Linux-api#IRTCVideo-disableaudioframecallback) | 关闭音频回调 |
| [registerLocalEncodedVideoFrameObserver](Linux-api#IRTCVideo-registerlocalencodedvideoframeobserver) | 注册本地视频帧监测器。  <br><br/>无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame](Linux-callback#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) 回调给用户 |
| [setExternalVideoEncoderEventHandler](Linux-api#IRTCVideo-setexternalvideoencodereventhandler) | 注册自定义编码帧推送事件回调 |
| [pushExternalEncodedVideoFrame](Linux-api#IRTCVideo-pushexternalencodedvideoframe) | 推送自定义编码后的视频流 |
## 网络管理
| 方法 | 描述 |
| --- | --- |
| [enableSimulcastMode](Linux-api#IRTCVideo-enablesimulcastmode) | 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。 |
| [setRemoteVideoConfig](Linux-api#IRTCRoom-setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [setPublishFallbackOption](Linux-api#IRTCVideo-setpublishfallbackoption) | 设置发布的音视频流的回退选项。  <br><br/>你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。 |
| [setSubscribeFallbackOption](Linux-api#IRTCVideo-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。 <br><br/>你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority](Linux-api#IRTCVideo-setremoteuserpriority) | 设置用户优先级。 |
| [startNetworkDetection](Linux-api#IRTCVideo-startnetworkdetection) | 开启通话前网络探测 |
| [stopNetworkDetection](Linux-api#IRTCVideo-stopnetworkdetection) | 停止通话前网络探测 |
## 消息
| 方法 | 描述 |
| --- | --- |
| [sendRoomMessage](Linux-api#IRTCRoom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [sendRoomBinaryMessage](Linux-api#IRTCRoom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [login](Linux-api#IRTCVideo-login) | 登录 RTS 服务器。<br>必须先登录，才能调用 [sendUserMessageOutsideRoom](Linux-api#IRTCVideo-sendusermessageoutsideroom) 和 [sendServerMessage](Linux-api#IRTCVideo-sendservermessage) 发送房间外点对点消息和向应用服务器发送消息 <br><br/>在调用本接口登录后，如果想要登出，需要调用 [logout](Linux-api#IRTCVideo-logout)。 |
| [logout](Linux-api#IRTCVideo-logout) | 登出 RTS 服务器。<br>调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken](Linux-api#IRTCVideo-updatelogintoken) | 更新用户用于登录的 Token  <br><br/>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br><br/>调用 [login](Linux-api#IRTCVideo-login) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [onLoginResult](Linux-callback#IRTCVideoEventHandler-onloginresult) 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。 |
| [setServerParams](Linux-api#IRTCVideo-setserverparams) | 设置应用服务器参数  <br><br/>客户端调用 [sendServerMessage](Linux-api#IRTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Linux-api#IRTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须设置有效签名和应用服务器地址。 |
| [getPeerOnlineStatus](Linux-api#IRTCVideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [sendUserMessage](Linux-api#IRTCRoom-sendusermessage) | 给房间内指定的用户发送点对点文本消息（P2P）。 |
| [sendUserBinaryMessage](Linux-api#IRTCRoom-senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息（P2P）。 |
| [sendUserMessageOutsideRoom](Linux-api#IRTCVideo-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom](Linux-api#IRTCVideo-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [sendServerMessage](Linux-api#IRTCVideo-sendservermessage) | 客户端给应用服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Linux-api#IRTCVideo-sendserverbinarymessage) | 客户端给应用服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo](Linux-api#IRTCVideo-sendstreamsyncinfo) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [onStreamSyncInfoReceived](Linux-callback#IRTCVideoEventHandler-onstreamsyncinforeceived) 回调。 |
| [sendSEIMessage](Linux-api#IRTCVideo-sendseimessage) | <span id="IRTCVideo-sendseimessage-2"></span> 通过视频帧发送 SEI 数据。<br/>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |
## 混音
| 方法 | 描述 |
| --- | --- |
| [getAudioEffectPlayer](Linux-api#IRTCVideo-getaudioeffectplayer) | 创建音效播放器实例。 |
| [start](Linux-api#IAudioEffectPlayer-start) | 开始播放音效文件。<br><br/>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个音效文件，实现音效叠加。 |
| [stop](Linux-api#IAudioEffectPlayer-stop) | 停止播放音效文件。 |
| [preload](Linux-api#IAudioEffectPlayer-preload) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [unload](Linux-api#IAudioEffectPlayer-unload) | 卸载指定音效文件。 |
| [unloadAll](Linux-api#IAudioEffectPlayer-unloadall) | 卸载所有音效文件。 |
| [pause](Linux-api#IAudioEffectPlayer-pause) | 暂停播放音效文件。 |
| [resume](Linux-api#IAudioEffectPlayer-resume) | 恢复播放音效文件。 |
| [setPosition](Linux-api#IAudioEffectPlayer-setposition) | 设置音效文件的起始播放位置。 |
| [getPosition](Linux-api#IAudioEffectPlayer-getposition) | 获取音效文件播放进度。 |
| [getVolume](Linux-api#IAudioEffectPlayer-getvolume) | 获取当前音量。 |
| [getDuration](Linux-api#IAudioEffectPlayer-getduration) | 获取音效文件时长。 |
| [setEventHandler](Linux-api#IAudioEffectPlayer-seteventhandler) | 设置回调句柄。 |
| [getMediaPlayer](Linux-api#IRTCVideo-getmediaplayer) | 创建音乐播放器实例。 |
| [open](Linux-api#IMediaPlayer-open) | 打开音乐文件。<br/>一个播放器实例仅能够同时打开一个音乐文件。如果需要同时打开多个音乐文件，请创建多个音乐播放器实例。<br/>要播放 PCM 格式的音频数据，参看 [openWithCustomSource](Linux-api#IMediaPlayer-openwithcustomsource)。`openWithCustomSource` 和此 API 互斥。 |
| [start](Linux-api#IMediaPlayer-start) | 播放音乐。你仅需要在调用 [open](Linux-api#IMediaPlayer-open)，且未开启自动播放时，调用此方法。 |
| [openWithCustomSource](Linux-api#IMediaPlayer-openwithcustomsource) | 启动音频裸数据混音。<br/>要播放音乐文件，参看 [open](Linux-api#IMediaPlayer-open)。`open` 与此 API 互斥。 |
| [stop](Linux-api#IMediaPlayer-stop) | 调用 [open](Linux-api#IMediaPlayer-open), [start](Linux-api#IMediaPlayer-start), 或 [openWithCustomSource](Linux-api#IMediaPlayer-openwithcustomsource) 开始播放后，可以调用本方法停止。 |
| [pause](Linux-api#IMediaPlayer-pause) | 调用 [open](Linux-api#IMediaPlayer-open)，或 [start](Linux-api#IMediaPlayer-start) 开始播放音频文件后，调用本方法暂停播放。 |
| [resume](Linux-api#IMediaPlayer-resume) | 调用 [pause](Linux-api#IMediaPlayer-pause) 暂停音频播放后，调用本方法恢复播放。 |
| [getVolume](Linux-api#IMediaPlayer-getvolume) | 获取当前音量 |
| [getTotalDuration](Linux-api#IMediaPlayer-gettotalduration) | 获取音乐文件时长。 |
| [getPosition](Linux-api#IMediaPlayer-getposition) | 获取音乐文件播放进度。 |
| [setAudioPitch](Linux-api#IMediaPlayer-setaudiopitch) | 开启变调功能，多用于 K 歌场景。 |
| [setPosition](Linux-api#IMediaPlayer-setposition) | 设置音乐文件的起始播放位置。 |
| [setAudioDualMonoMode](Linux-api#IMediaPlayer-setaudiodualmonomode) | 设置当前音乐文件的声道模式 |
| [getAudioTrackCount](Linux-api#IMediaPlayer-getaudiotrackcount) | 获取当前音乐文件的音轨数 |
| [selectAudioTrack](Linux-api#IMediaPlayer-selectaudiotrack) | 指定当前音乐文件的播放音轨 |
| [setPlaybackSpeed](Linux-api#IMediaPlayer-setplaybackspeed) | 设置播放速度 |
| [setProgressInterval](Linux-api#IMediaPlayer-setprogressinterval) | 设置音频文件混音时，收到 [onMediaPlayerPlayingProgress](Linux-callback#IMediaPlayerEventHandler-onmediaplayerplayingprogress) 的间隔。 |
| [setLoudness](Linux-api#IMediaPlayer-setloudness) | 如果你需要使用 [enableVocalInstrumentBalance](Linux-api#IRTCVideo-enablevocalinstrumentbalance) 对音频文件/PCM 音频数据设置音量均衡，你必须通过此接口传入其原始响度。 |
| [pushExternalAudioFrame](Linux-api#IMediaPlayer-pushexternalaudioframe) | 推送用于混音的 PCM 音频帧数据 |
| [setEventHandler](Linux-api#IMediaPlayer-seteventhandler) | 设置回调句柄。 |
## 屏幕分享
| 方法 | 描述 |
| --- | --- |
| [getScreenCaptureSourceList](Linux-api#IRTCVideo-getscreencapturesourcelist) | 获取共享对象列表。 |
| [startScreenVideoCapture](Linux-api#IRTCVideo-startscreenvideocapture) | 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，应用窗口中显示的内容，或虚拟屏幕中显示的内容。<br><br/>其中，虚拟屏幕中显示的内容仅在 Windows 平台上支持。 |
| [updateScreenCaptureHighlightConfig](Linux-api#IRTCVideo-updatescreencapturehighlightconfig) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新边框高亮设置。默认展示表框。 |
| [updateScreenCaptureMouseCursor](Linux-api#IRTCVideo-updatescreencapturemousecursor) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新对鼠标的处理设置。默认采集鼠标。 |
| [updateScreenCaptureRegion](Linux-api#IRTCVideo-updatescreencaptureregion) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新采集区域。仅用于采集源为显示器屏幕时。 |
| [stopScreenVideoCapture](Linux-api#IRTCVideo-stopscreenvideocapture) | 停止屏幕视频流采集。 |
| [publishScreen](Linux-api#IRTCRoom-publishscreen) | 在当前所在房间内手动发布本地屏幕共享音视频流。<br><br/>如果你需要手动向多个房间发布屏幕共享流，可以使用同样的 uid 加入多个房间，并在每个房间调用该方法。同时，你可以在不同的房间发布不同的屏幕共享流类型。 |
| [unpublishScreen](Linux-api#IRTCRoom-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [getThumbnail](Linux-api#IRTCVideo-getthumbnail) | 获取共享对象缩略图 |
| [getWindowAppIcon](Linux-api#IRTCVideo-getwindowappicon) | 获取应用窗体所属应用的图标。 |
| [pushScreenVideoFrame](Linux-api#IRTCVideo-pushscreenvideoframe) | 推送屏幕视频帧 |
| [setScreenVideoEncoderConfig](Linux-api#IRTCVideo-setscreenvideoencoderconfig) | 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [subscribeScreen](Linux-api#IRTCRoom-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen](Linux-api#IRTCRoom-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
## 安全与加密
| 方法 | 描述 |
| --- | --- |
| [startCloudProxy](Linux-api#IRTCVideo-startcloudproxy) | 开启云代理 |
| [stopCloudProxy](Linux-api#IRTCVideo-stopcloudproxy) | 关闭云代理 |
| [setCustomizeEncryptHandler](Linux-api#IRTCVideo-setcustomizeencrypthandler) | 设置自定义加密和解密方式。 |
| [setEncryptInfo](Linux-api#IRTCVideo-setencryptinfo) | 设置传输时使用内置加密的方式。 |
| [setLocalProxy](Linux-api#IRTCVideo-setlocalproxy) | 设置本地代理。 |
## 高级功能
| 方法 | 描述 |
| --- | --- |
| [startFileRecording](Linux-api#IRTCVideo-startfilerecording) | 录制通话过程中的音视频数据到本地的文件中。 |
| [stopFileRecording](Linux-api#IRTCVideo-stopfilerecording) | 停止本地录制 |
| [startAudioRecording](Linux-api#IRTCVideo-startaudiorecording) | 开启录制语音通话，生成本地文件。<br><br/>在进房前后开启录制，如果未打开麦克风采集，录制任务正常进行，只是不会将数据写入生成的本地文件；只有调用 [startAudioCapture](Linux-api#IRTCVideo-startaudiocapture) 接口打开麦克风采集后，才会将录制数据写入本地文件。 |
| [stopAudioRecording](Linux-api#IRTCVideo-stopaudiorecording) | 停止音频文件录制 |
| [setAnsMode](Linux-api#IRTCVideo-setansmode) | 支持根据业务场景，设置通话中的音频降噪模式。 |
## 字幕翻译服务
| 方法 | 描述 |
| --- | --- |
| [startSubtitle](Linux-api#IRTCRoom-startsubtitle) | 识别或翻译房间内所有用户的语音，形成字幕。<br><br/>调用该方法时，可以在 [SubtitleMode](Linux-keytype#subtitlemode) 中选择语音识别或翻译模式。如果选择识别模式，语音识别文本会通过 [onSubtitleMessageReceived](Linux-callback#IRTCRoomEventHandler-onsubtitlemessagereceived) 事件回调给你；<br><br/>如果选择翻译模式，你会同时收到两个 [onSubtitleMessageReceived](Linux-callback#IRTCRoomEventHandler-onsubtitlemessagereceived) 回调，分别包含字幕原文及字幕译文。<br><br/>调用该方法后，用户会收到 [onSubtitleStateChanged](Linux-callback#IRTCRoomEventHandler-onsubtitlestatechanged) 回调，通知字幕是否开启。 |
| [stopSubtitle](Linux-api#IRTCRoom-stopsubtitle) | 关闭字幕。 <br><br/>调用该方法后，用户会收到 [onSubtitleStateChanged](Linux-callback#IRTCRoomEventHandler-onsubtitlestatechanged) 回调，通知字幕是否关闭。 |
## 在线 KTV
| 方法 | 描述 |
| --- | --- |
| [setAudioAlignmentProperty](Linux-api#IRTCVideo-setaudioalignmentproperty) | 在听众端，设置订阅的所有远端音频流精准对齐后播放。 |
# 回调
## 引擎管理
| 回调 | 描述 |
| --- | --- |
| [onLogReport](Linux-callback#IRTCVideoEventHandler-onlogreport) | 上报日志时回调该事件。 |
| [onSysStats](Linux-callback#IRTCVideoEventHandler-onsysstats) | 周期性（2s）发出回调，报告当前 CPU 与内存的相关信息。 |
| [onWarning](Linux-callback#IRTCVideoEventHandler-onwarning) | 发生警告回调。  <br><br/>SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。<br><br/>你可能需要干预. |
| [onError](Linux-callback#IRTCVideoEventHandler-onerror) | 发生错误回调。<br><br/>SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。 |
| [onTokenWillExpire](Linux-callback#IRTCRoomEventHandler-ontokenwillexpire) | 当 SDK 检测到 Token 的进房权限将在 30 秒内过期时，触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Linux-api#IRTCRoom-updatetoken) 更新 Token 进房权限。 |
| [onPublishPrivilegeTokenWillExpire](Linux-callback#IRTCRoomEventHandler-onpublishprivilegetokenwillexpire) | Token 发布权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Linux-api#IRTCRoom-updatetoken) 更新 Token 发布权限。 |
| [onSubscribePrivilegeTokenWillExpire](Linux-callback#IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire) | Token 订阅权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Linux-api#IRTCRoom-updatetoken) 更新 Token 订阅权限有效期。 |
## 房间管理
| 回调 | 描述 |
| --- | --- |
| [onRoomStateChanged](Linux-callback#IRTCRoomEventHandler-onroomstatechanged) | 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。 |
| [onCreateRoomStateChanged](Linux-callback#IRTCVideoEventHandler-oncreateroomstatechanged) | 创建房间失败回调。 |
| [onLeaveRoom](Linux-callback#IRTCRoomEventHandler-onleaveroom) | 离开房间成功回调。  <br><br/>用户调用 [leaveRoom](Linux-api#IRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br> |
| [onUserJoined](Linux-callback#IRTCRoomEventHandler-onuserjoined) | 远端可见用户加入房间，或房内不可见用户切换为可见的回调。<br><br/>1. 远端用户调用 [setUserVisibility](Linux-api#IRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br><br/>2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br><br/>3. 房间内隐身远端用户调用 [setUserVisibility](Linux-api#IRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br><br/>4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br> |
| [onUserLeave](Linux-callback#IRTCRoomEventHandler-onuserleave) | 远端用户离开房间，或切至不可见时，本地用户会收到此事件 |
| [onUserVisibilityChanged](Linux-callback#IRTCRoomEventHandler-onuservisibilitychanged) | 用户调用 [setUserVisibility](Linux-api#IRTCRoom-setuservisibility) 设置用户可见性的回调。 |
| [onRoomStats](Linux-callback#IRTCRoomEventHandler-onroomstats) | 房间内通话统计信息回调。  <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |
| [onSetRoomExtraInfoResult](Linux-callback#IRTCRoomEventHandler-onsetroomextrainforesult) | 调用 [setRoomExtraInfo](Linux-api#IRTCRoom-setroomextrainfo) 设置房间附加信息结果的回调。 |
| [onRoomExtraInfoUpdate](Linux-callback#IRTCRoomEventHandler-onroomextrainfoupdate) | 接收同一房间内，其他用户调用 [setRoomExtraInfo](Linux-api#IRTCRoom-setroomextrainfo) 设置的房间附加信息的回调。 |
## 音频管理
| 回调 | 描述 |
| --- | --- |
| [onAudioDeviceWarning](Linux-callback#IRTCVideoEventHandler-onaudiodevicewarning) | 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。 |
| [onAudioDeviceStateChanged](Linux-callback#IRTCVideoEventHandler-onaudiodevicestatechanged) | 音频设备状态回调。提示音频采集、音频播放等设备设备的状态。 |
| [onLocalAudioPropertiesReport](Linux-callback#IRTCVideoEventHandler-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Linux-api#IRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br><br/>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。 |
| [onRemoteAudioPropertiesReport](Linux-callback#IRTCVideoEventHandler-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Linux-api#IRTCVideo-enableaudiopropertiesreport)，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。<br><br/>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onUserStartAudioCapture](Linux-callback#IRTCVideoEventHandler-onuserstartaudiocapture) | 房间内的用户调用 [startAudioCapture](Linux-api#IRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。 |
| [onUserStopAudioCapture](Linux-callback#IRTCVideoEventHandler-onuserstopaudiocapture) | 房间内的用户调用 [stopAudioCapture](Linux-api#IRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。 |
| [onActiveSpeaker](Linux-callback#IRTCVideoEventHandler-onactivespeaker) | 调用 [enableAudioPropertiesReport](Linux-api#IRTCVideo-enableaudiopropertiesreport) 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [onStreamSyncInfoReceived](Linux-callback#IRTCVideoEventHandler-onstreamsyncinforeceived) | 音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Linux-api#IRTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br> |
| [onAudioStreamBanned](Linux-callback#IRTCRoomEventHandler-onaudiostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [onAudioPlaybackDeviceTestVolume](Linux-callback#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onAudioDeviceVolumeChanged](Linux-callback#IRTCVideoEventHandler-onaudiodevicevolumechanged) | 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。 |
| [onLocalAudioStateChanged](Linux-callback#IRTCVideoEventHandler-onlocalaudiostatechanged) | 本地音频流的状态发生改变时，收到此回调。 |
## 视频管理
| 回调 | 描述 |
| --- | --- |
| [onUserStartVideoCapture](Linux-callback#IRTCVideoEventHandler-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Linux-api#IRTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。 |
| [onUserStopVideoCapture](Linux-callback#IRTCVideoEventHandler-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Linux-api#IRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。<br/>若发布视频数据前未开启采集，房间内所有可见用户会收到此回调。 |
| [onVideoDeviceStateChanged](Linux-callback#IRTCVideoEventHandler-onvideodevicestatechanged) | 视频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。 |
| [onVideoDeviceWarning](Linux-callback#IRTCVideoEventHandler-onvideodevicewarning) | 视频设备警告回调，包括视频采集设备等。 |
| [onLocalVideoStateChanged](Linux-callback#IRTCVideoEventHandler-onlocalvideostatechanged) | 本地视频流的状态发生改变时，收到该事件。 |
## 音视频传输
| 回调 | 描述 |
| --- | --- |
| [onStreamStateChanged](Linux-callback#IRTCRoomEventHandler-onstreamstatechanged) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [onAVSyncStateChange](Linux-callback#IRTCRoomEventHandler-onavsyncstatechange) | 发布端调用 [setMultiDeviceAVSync](Linux-api#IRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。 |
| [onUserPublishStream](Linux-callback#IRTCRoomEventHandler-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集的媒体流的回调。 |
| [onUserUnpublishStream](Linux-callback#IRTCRoomEventHandler-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onStreamSubscribed](Linux-callback#IRTCRoomEventHandler-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onAudioFrameSendStateChanged](Linux-callback#IRTCVideoEventHandler-onaudioframesendstatechanged) | 本地音频首帧发送状态发生改变时，收到此回调。 |
| [onVideoFrameSendStateChanged](Linux-callback#IRTCVideoEventHandler-onvideoframesendstatechanged) | 本地视频首帧发送状态发生改变时，收到此回调。 |
| [onAudioFramePlayStateChanged](Linux-callback#IRTCVideoEventHandler-onaudioframeplaystatechanged) | 音频首帧播放状态发生改变时，收到此回调。 |
| [onVideoFramePlayStateChanged](Linux-callback#IRTCVideoEventHandler-onvideoframeplaystatechanged) | 视频首帧播放状态改变回调 |
| [onRemoteStreamStats](Linux-callback#IRTCRoomEventHandler-onremotestreamstats) | 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br><br/>本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [onNetworkQuality](Linux-callback#IRTCRoomEventHandler-onnetworkquality) | 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。 |
| [onForwardStreamStateChanged](Linux-callback#IRTCRoomEventHandler-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [onForwardStreamEvent](Linux-callback#IRTCRoomEventHandler-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [onRemoteAudioStateChanged](Linux-callback#IRTCVideoEventHandler-onremoteaudiostatechanged) | 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。 |
| [onFirstLocalAudioFrame](Linux-callback#IRTCVideoEventHandler-onfirstlocalaudioframe) | 发布音频流时，采集到第一帧音频帧，收到该回调。 |
| [onFirstRemoteAudioFrame](Linux-callback#IRTCVideoEventHandler-onfirstremoteaudioframe) | 接收到来自远端某音频流的第一帧时，收到该回调。 |
| [onFirstLocalVideoFrameCaptured](Linux-callback#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) | RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。 |
| [onLocalVideoSizeChanged](Linux-callback#IRTCVideoEventHandler-onlocalvideosizechanged) | 本地视频大小或旋转信息发生改变时，收到此回调。 |
| [onRemoteVideoSizeChanged](Linux-callback#IRTCVideoEventHandler-onremotevideosizechanged) | 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onRemoteVideoStateChanged](Linux-callback#IRTCVideoEventHandler-onremotevideostatechanged) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [onFirstRemoteVideoFrameRendered](Linux-callback#IRTCVideoEventHandler-onfirstremotevideoframerendered) | SDK 内部渲染成功远端视频流首帧后，收到此回调。 |
| [onVideoStreamBanned](Linux-callback#IRTCRoomEventHandler-onvideostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [onFirstRemoteVideoFrameDecoded](Linux-callback#IRTCVideoEventHandler-onfirstremotevideoframedecoded) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [onPushPublicStreamResult](Linux-callback#IRTCVideoEventHandler-onpushpublicstreamresult) | 公共流发布结果回调。<br><br/>调用 [startPushPublicStream](Linux-api#IRTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。 |
| [onPlayPublicStreamResult](Linux-callback#IRTCVideoEventHandler-onplaypublicstreamresult) | 订阅公共流的结果回调<br><br/>通过 [startPlayPublicStream](Linux-api#IRTCVideo-startplaypublicstream) 订阅公共流后，可以通过本回调获取订阅结果。 |
| [onPublicStreamSEIMessageReceived](Linux-callback#IRTCVideoEventHandler-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br/>调用 [startPlayPublicStream](Linux-api#IRTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [onFirstPublicStreamVideoFrameDecoded](Linux-callback#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) | 公共流的首帧视频解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Linux-api#IRTCVideo-startplaypublicstream)。 |
| [onFirstPublicStreamAudioFrame](Linux-callback#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Linux-api#IRTCVideo-startplaypublicstream)。 |
## 自定义流处理
| 回调 | 描述 |
| --- | --- |
| [onStart](Linux-callback#IExternalVideoEncoderEventHandler-onstart) | 提示自定义编码帧可以开始推送的回调。  <br><br/>收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Linux-api#IRTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧 |
| [onStop](Linux-callback#IExternalVideoEncoderEventHandler-onstop) | 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧 |
| [onRateUpdate](Linux-callback#IExternalVideoEncoderEventHandler-onrateupdate) | 当自定义编码流的帧率或码率发生变化时，触发该回调 |
| [onRequestKeyFrame](Linux-callback#IExternalVideoEncoderEventHandler-onrequestkeyframe) | 提示流发布端需重新生成关键帧的回调 |
| [onActiveVideoLayer](Linux-callback#IExternalVideoEncoderEventHandler-onactivevideolayer) | 作为自定义编码视频流的发送端，你会在视频流可发送状态发生变化时，收到此回调。<br/>你可以根据此回调的提示，仅对可发送的视频流进行编码，以降低本端视频编码性能消耗。此回调会根据多个因素综合判断触发，包括：本端设备性能和本端网络性能，以及按需订阅场景下，远端用户是否订阅。 |
| [onLocalEncodedVideoFrame](Linux-callback#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) | 调用 [registerLocalEncodedVideoFrameObserver](Linux-api#IRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。 |
| [onRemoteEncodedVideoFrame](Linux-callback#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) | 调用 [registerRemoteEncodedVideoFrameObserver](Linux-api#IRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调 |
| [onProcessPlayBackAudioFrame](Linux-callback#IAudioFrameProcessor-onprocessplaybackaudioframe) | 回调远端音频混音的音频帧地址，供自定义音频处理。 |
| [onProcessRecordAudioFrame](Linux-callback#IAudioFrameProcessor-onprocessrecordaudioframe) | 回调本地采集的音频帧地址，供自定义音频处理。 |
| [onProcessRemoteUserAudioFrame](Linux-callback#IAudioFrameProcessor-onprocessremoteuseraudioframe) | 回调单个远端用户的音频帧地址，供自定义音频处理。 |
| [onProcessScreenAudioFrame](Linux-callback#IAudioFrameProcessor-onprocessscreenaudioframe) | 屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。 |
| [onRecordAudioFrame](Linux-callback#IAudioFrameObserver-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame](Linux-callback#IAudioFrameObserver-onplaybackaudioframe) | 返回订阅的所有远端用户混音后的音频数据。 |
| [onRemoteUserAudioFrame](Linux-callback#IAudioFrameObserver-onremoteuseraudioframe) | 返回远端单个用户的音频数据 |
| [onMixedAudioFrame](Linux-callback#IAudioFrameObserver-onmixedaudioframe) | 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据 |
| [onRecordScreenAudioFrame](Linux-callback#IAudioFrameObserver-onrecordscreenaudioframe) | 返回本地屏幕录制的音频数据 |
## 网络管理
| 回调 | 描述 |
| --- | --- |
| [onPerformanceAlarms](Linux-callback#IRTCVideoEventHandler-onperformancealarms) | 本地未通过 [setPublishFallbackOption](Linux-api#IRTCVideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。<br><br/>本地通过 [setPublishFallbackOption](Linux-api#IRTCVideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。 |
| [onSimulcastSubscribeFallback](Linux-callback#IRTCVideoEventHandler-onsimulcastsubscribefallback) | 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。 |
| [onNetworkDetectionResult](Linux-callback#IRTCVideoEventHandler-onnetworkdetectionresult) | 通话前网络探测结果。  <br><br/>成功调用 [startNetworkDetection](Linux-api#IRTCVideo-startnetworkdetection) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [onNetworkDetectionStopped](Linux-callback#IRTCVideoEventHandler-onnetworkdetectionstopped) | 通话前网络探测结束<br/>以下情况将停止探测并收到本一次本回调：<br><br/>1. 当调用 [stopNetworkDetection](Linux-api#IRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；<br/>2. 当收到远端/本端音频首帧后，停止探测；<br/>3. 当探测超过3分钟后，停止探测；<br/>4. 当探测链路断开一定时间之后，停止探测。 |
| [onConnectionStateChanged](Linux-callback#IRTCVideoEventHandler-onconnectionstatechanged) | SDK 与信令服务器连接状态改变回调。连接状态改变时触发。 |
| [onNetworkTypeChanged](Linux-callback#IRTCVideoEventHandler-onnetworktypechanged) | SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。 |
| [onSEIMessageReceived](Linux-callback#IRTCVideoEventHandler-onseimessagereceived) | 收到通过调用 [sendSEIMessage](Linux-api#IRTCVideo-sendseimessage) 发送带有 SEI 消息的视频帧时，收到此回调。 |
## 消息
| 回调 | 描述 |
| --- | --- |
| [onLoginResult](Linux-callback#IRTCVideoEventHandler-onloginresult) | 登录结果回调 |
| [onLogout](Linux-callback#IRTCVideoEventHandler-onlogout) | 登出结果回调 |
| [onServerParamsSetResult](Linux-callback#IRTCVideoEventHandler-onserverparamssetresult) | 设置应用服务器参数的返回结果 |
| [onGetPeerOnlineStatus](Linux-callback#IRTCVideoEventHandler-ongetpeeronlinestatus) | 查询对端或本端用户登录状态的返回结果 |
| [onUserMessageReceivedOutsideRoom](Linux-callback#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserMessageOutsideRoom](Linux-api#IRTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调 |
| [onUserBinaryMessageReceivedOutsideRoom](Linux-callback#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Linux-api#IRTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调 |
| [onUserMessageSendResultOutsideRoom](Linux-callback#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) | 给房间外指定的用户发送消息的回调 |
| [onServerMessageSendResult](Linux-callback#IRTCVideoEventHandler-onservermessagesendresult) | 给应用服务器发送消息的回调。 |
| [onRoomMessageReceived](Linux-callback#IRTCRoomEventHandler-onroommessagereceived) | 接收到房间内广播消息的回调。 |
| [onRoomBinaryMessageReceived](Linux-callback#IRTCRoomEventHandler-onroombinarymessagereceived) | 收到房间内广播二进制消息的回调。<br><br/>房间内其他用户调用 [sendRoomBinaryMessage](Linux-api#IRTCRoom-sendroombinarymessage) 发送广播二进制消息时，收到此回调。 |
| [onUserMessageReceived](Linux-callback#IRTCRoomEventHandler-onusermessagereceived) | 收到来自房间中其他用户通过 [sendUserMessage](Linux-api#IRTCRoom-sendusermessage) 发来的点对点文本消息时，会收到此回调。 |
| [onUserBinaryMessageReceived](Linux-callback#IRTCRoomEventHandler-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 [sendUserBinaryMessage](Linux-api#IRTCRoom-senduserbinarymessage) 发来的点对点二进制消息时，会收到此回调。 |
| [onUserMessageSendResult](Linux-callback#IRTCRoomEventHandler-onusermessagesendresult) | 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。 |
| [onRoomMessageSendResult](Linux-callback#IRTCRoomEventHandler-onroommessagesendresult) | 调用 [sendRoomMessage](Linux-api#IRTCRoom-sendroommessage) 或 [sendRoomBinaryMessage](Linux-api#IRTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onSEIStreamUpdate](Linux-callback#IRTCVideoEventHandler-onseistreamupdate) | 黑帧视频流发布状态回调。  <br><br/>在语音通话场景下，本地用户调用 [sendSEIMessage](Linux-api#IRTCVideo-sendseimessage) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br><br/>你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。 |
## 混音
| 回调 | 描述 |
| --- | --- |
| [onAudioEffectPlayerStateChanged](Linux-callback#IAudioEffectPlayerEventHandler-onaudioeffectplayerstatechanged) | 播放状态改变时回调。 |
| [onMediaPlayerStateChanged](Linux-callback#IMediaPlayerEventHandler-onmediaplayerstatechanged) | 播放状态改变时回调。 |
| [onMediaPlayerPlayingProgress](Linux-callback#IMediaPlayerEventHandler-onmediaplayerplayingprogress) | 播放进度周期性回调。回调周期通过 [setProgressInterval](Linux-api#IMediaPlayer-setprogressinterval) 设置。 |
| [onReadData](Linux-callback#IMediaPlayerCustomSourceProvider-onreaddata) | 调用 [openWithCustomSource](Linux-api#IMediaPlayer-openwithcustomsource) 接口播放用户传入的内存音频数据时，会触发此回调，用户需要写入音频数据。 |
| [onSeek](Linux-callback#IMediaPlayerCustomSourceProvider-onseek) | 根据设置好的内存音频数据的读取位置和读取偏移量对音频数据进行偏移，以便 SDK 读取和分析音频数据。 <br><br/>在调用 [openWithCustomSource](Linux-api#IMediaPlayer-openwithcustomsource) 接口传入内存音频数据，或者调用 [setPosition](Linux-api#IMediaPlayer-setposition) 设置了音频数据的起始播放位置后，SDK 会对音频数据进行读取和分析，此时会触发该回调，你需要根据参数中设置的起始读取位置和偏移量进行操作。 |
## 屏幕分享
| 回调 | 描述 |
| --- | --- |
| [onUserPublishScreen](Linux-callback#IRTCRoomEventHandler-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](Linux-callback#IRTCRoomEventHandler-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onScreenVideoFrameSendStateChanged](Linux-callback#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) | 屏幕共享流的视频首帧发送状态发生改变时，收到此回调。 |
| [onScreenVideoFramePlayStateChanged](Linux-callback#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) | 屏幕共享流视频首帧播放状态发生改变时，收到此回调。 |
| [onScreenAudioFrameSendStateChanged](Linux-callback#IRTCVideoEventHandler-onscreenaudioframesendstatechanged) | 屏幕音频首帧发送状态改变回调 |
| [onScreenAudioFramePlayStateChanged](Linux-callback#IRTCVideoEventHandler-onscreenaudioframeplaystatechanged) | 屏幕音频首帧播放状态改变回调 |
## 安全与加密
| 回调 | 描述 |
| --- | --- |
| [onCloudProxyConnected](Linux-callback#IRTCVideoEventHandler-oncloudproxyconnected) | 调用 [startCloudProxy](Linux-api#IRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onEncryptData](Linux-callback#IEncryptHandler-onencryptdata) | 自定义加密。  <br><br/>使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br><br/>暂不支持对原始音视频帧进行加密。 |
| [onDecryptData](Linux-callback#IEncryptHandler-ondecryptdata) | 自定义解密。  <br><br/>对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData](Linux-callback#IEncryptHandler-onencryptdata)。 |
| [onLocalProxyStateChanged](Linux-callback#IRTCVideoEventHandler-onlocalproxystatechanged) | 本地代理状态发生改变回调。调用 [setLocalProxy](Linux-api#IRTCVideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。 |
## 高级功能
| 回调 | 描述 |
| --- | --- |
| [onRecordingStateUpdate](Linux-callback#IRTCVideoEventHandler-onrecordingstateupdate) | 获取本地录制状态回调。  <br><br/>该回调由 [startFileRecording](Linux-api#IRTCVideo-startfilerecording) 或 [stopFileRecording](Linux-api#IRTCVideo-stopfilerecording) 触发。 |
| [onRecordingProgressUpdate](Linux-callback#IRTCVideoEventHandler-onrecordingprogressupdate) | 本地录制进度回调。  <br><br/>该回调由 [startFileRecording](Linux-api#IRTCVideo-startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。 |
| [onAudioRecordingStateUpdate](Linux-callback#IRTCVideoEventHandler-onaudiorecordingstateupdate) | 调用 [startAudioRecording](Linux-api#IRTCVideo-startaudiorecording) 或 [stopAudioRecording](Linux-api#IRTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。 |
## 字幕翻译服务
| 回调 | 描述 |
| --- | --- |
| [onSubtitleStateChanged](Linux-callback#IRTCRoomEventHandler-onsubtitlestatechanged) | 字幕状态发生改变回调。 <br><br/>当用户调用 [startSubtitle](Linux-api#IRTCRoom-startsubtitle) 和 [stopSubtitle](Linux-api#IRTCRoom-stopsubtitle) 使字幕状态发生改变或出现错误时，触发该回调。 |
| [onSubtitleMessageReceived](Linux-callback#IRTCRoomEventHandler-onsubtitlemessagereceived) | 字幕相关内容回调。 <br><br/>当用户调用 [startSubtitle](Linux-api#IRTCRoom-startsubtitle) 后会收到此回调，通知字幕的相关信息。 |
