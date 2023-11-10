# 方法
## 引擎管理

| 方法 | 描述 |
| --- | --- |
| [createRTCVideo](Windows-api.md#creatertcvideo) | 创建 IRTCVideo 实例。  <br><br/>如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br><br/>如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。 |
| [destroyRTCVideo](Windows-api.md#destroyrtcvideo) | 销毁由 [createRTCVideo](Windows-api.md#creatertcvideo) 所创建的引擎实例，并释放所有相关资源。<br> |
| [getSDKVersion](Windows-api.md#getsdkversion) | 获取当前 SDK 版本信息。 |
| [feedback](Windows-api.md#IRTCVideo-feedback) | 将用户反馈的问题上报到 RTC |
| [getErrorDescription](Windows-api.md#geterrordescription) | 获取 SDK 内各种错误码、警告码的描述文字。 |
| [setBusinessId](Windows-api.md#IRTCVideo-setbusinessid) | 设置业务标识参数  <br><br/>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setRuntimeParameters](Windows-api.md#IRTCVideo-setruntimeparameters) | 设置运行时的参数 |

## 房间管理

| 方法 | 描述 |
| --- | --- |
| [createRTCRoom](Windows-api.md#IRTCVideo-creatertcroom) | 创建房间实例。<br><br/>调用此方法仅返回一个房间实例，你仍需调用 [joinRoom](Windows-api.md#IRTCRoom-joinroom) 才能真正地创建/加入房间。<br><br/>多次调用此方法以创建多个 [IRTCRoom](Windows-api.md#irtcroom) 实例。分别调用各 IRTCRoom 实例中的 [joinRoom](Windows-api.md#IRTCRoom-joinroom) 方法，同时加入多个房间。<br><br/>多房间模式下，用户可以同时订阅各房间的音视频流。 |
| [destroy](Windows-api.md#IRTCRoom-destroy) | 退出并销毁调用 [createRTCRoom](Windows-api.md#IRTCVideo-creatertcroom) 所创建的房间实例。 |
| [setRTCRoomEventHandler](Windows-api.md#IRTCRoom-setrtcroomeventhandler) | 通过设置 [IRTCRoom](Windows-api.md#irtcroom) 对象的事件句柄，监听此对象对应的回调事件。 |
| [joinRoom](Windows-api.md#IRTCRoom-joinroom) | 创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br><br/>同一房间内的用户间可以相互通话。  <br> |
| [leaveRoom](Windows-api#IRTCRoom-leaveroom) | 离开房间。  <br><br/>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br><br/>加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br><br/>此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 [onLeaveRoom](Windows-callback.md#IRTCRoomEventHandler-onleaveroom) 回调通知。  <br> |
| [setUserVisibility](Windows-api.md#IRTCRoom-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。 <br> |
| [updateToken](Windows-api.md#IRTCRoom-updatetoken) | 更新 Token。<br/>Token 中同时包含进房、发布和订阅权限，各权限有一定的有效期，并且到期前 30 秒会触发回调，提示用户更新 Token 相关权限。此时需要重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。 |

## 音频管理

| 方法 | 描述 |
| --- | --- |
| [buildAudioFrame](Windows-api.md#buildaudioframe) | 创建 IAudioFrame |
| [enumerateAudioPlaybackDevices](Windows-api.md#IAudioDeviceManager-enumerateaudioplaybackdevices) | 获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 `onAudioMediaDeviceStateChanged` 回调通知，然后需要重新调用本接口以获得新的设备列表。 |
| [enumerateAudioCaptureDevices](Windows-api.md#IAudioDeviceManager-enumerateaudiocapturedevices) | 获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。 |
| [setAudioPlaybackDevice](Windows-api.md#IAudioDeviceManager-setaudioplaybackdevice) | 设置音频播放设备。 |
| [setAudioCaptureDevice](Windows-api.md#IAudioDeviceManager-setaudiocapturedevice) | 设置音频采集设备。 |
| [getAudioPlaybackDevice](Windows-api.md#IAudioDeviceManager-getaudioplaybackdevice) | 获取当前音频播放设备 ID。 |
| [getAudioCaptureDevice](Windows-api.md#IAudioDeviceManager-getaudiocapturedevice) | 获取当前音频采集设备 ID。 |
| [followSystemPlaybackDevice](Windows-api.md#IAudioDeviceManager-followsystemplaybackdevice) | 设置音频播放路由是否跟随系统。 |
| [followSystemCaptureDevice](Windows-api.md#IAudioDeviceManager-followsystemcapturedevice) | 设置音频采集路由是否跟随系统。 |
| [setAudioPlaybackDeviceVolume](Windows-api.md#IAudioDeviceManager-setaudioplaybackdevicevolume) | 设置当前音频播放设备音量 |
| [getAudioPlaybackDeviceVolume](Windows-api.md#IAudioDeviceManager-getaudioplaybackdevicevolume) | 获取当前音频播放设备音量 |
| [setAudioCaptureDeviceVolume](Windows-api.md#IAudioDeviceManager-setaudiocapturedevicevolume) | 设置当前音频采集设备音量 |
| [getAudioCaptureDeviceVolume](Windows-api.md#IAudioDeviceManager-getaudiocapturedevicevolume) | 获取当前音频采集设备音量 |
| [setAudioPlaybackDeviceMute](Windows-api.md#IAudioDeviceManager-setaudioplaybackdevicemute) | 设置当前音频播放设备静音状态，默认为非静音。 |
| [getAudioPlaybackDeviceMute](Windows-api.md#IAudioDeviceManager-getaudioplaybackdevicemute) | 获取当前音频播放设备是否静音的信息。 |
| [setAudioCaptureDeviceMute](Windows-api.md#IAudioDeviceManager-setaudiocapturedevicemute) | 设置当前音频采集设备静音状态，默认为非静音。 |
| [getAudioCaptureDeviceMute](Windows-api.md#IAudioDeviceManager-getaudiocapturedevicemute) | 获取当前音频采集设备是否静音的信息。 |
| [startAudioPlaybackDeviceTest](Windows-api.md#IAudioDeviceManager-startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。 |
| [stopAudioPlaybackDeviceTest](Windows-api.md#IAudioDeviceManager-stopaudioplaybackdevicetest) | 停止音频播放测试。  <br> |
| [initAudioPlaybackDeviceForTest](Windows-api.md#IAudioDeviceManager-initaudioplaybackdevicefortest) | 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。 |
| [initAudioCaptureDeviceForTest](Windows-api.md#IAudioDeviceManager-initaudiocapturedevicefortest) | 尝试初始化音频采集设备，可检测设备不存在、权限被拒绝/禁用等异常问题。 |
| [setCaptureVolume](Windows-api.md#IRTCVideo-setcapturevolume) | 调节音频采集音量 |
| [setPlaybackVolume](Windows-api.md#IRTCVideo-setplaybackvolume) | 调节本地播放的所有远端用户混音后的音量。<br><br/>播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume](Windows-api.md#IRTCVideo-setremoteaudioplaybackvolume) | 调节来自指定远端用户的音频播放音量。 |
| [setRemoteRoomAudioPlaybackVolume](Windows-api.md#IRTCRoom-setremoteroomaudioplaybackvolume) | 调节某个房间内所有远端用户的音频播放音量。 |
| [enableAudioPropertiesReport](Windows-api#IRTCVideo-enableaudiopropertiesreport) | 启用音频信息提示。开启提示后，你会收到 [onLocalAudioPropertiesReport](Windows-callback.md#IRTCVideoEventHandler-onlocalaudiopropertiesreport)，[onRemoteAudioPropertiesReport](Windows-callback.md#IRTCVideoEventHandler-onremoteaudiopropertiesreport) 和 [onActiveSpeaker](Windows-callback.md#IRTCVideoEventHandler-onactivespeaker)。 |
| [startAudioCapture](Windows-api#IRTCVideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。<br/>调用该方法开启后，本地用户会收到 [onAudioDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。 <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Windows-callback.md#IRTCVideoEventHandler-onuserstartaudiocapture) 的回调。 |
| [stopAudioCapture](Windows-api#IRTCVideo-stopaudiocapture) | 立即关闭内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。<br/>调用该方法，本地用户会收到 [onAudioDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法后，房间中的其他用户会收到 [onUserStopAudioCapture](Windows-callback.md#IRTCVideoEventHandler-onuserstopaudiocapture) 的回调。 |
| [startScreenAudioCapture](Windows-api.md#IRTCVideo-startscreenaudiocapture) | 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频 |
| [stopScreenAudioCapture](Windows-api.md#IRTCVideo-stopscreenaudiocapture) | 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。 |
| [setAudioProfile](Windows-api#IRTCVideo-setaudioprofile) | 设置音质档位。<br><br/>当所选的 [RoomProfileType](Windows-keytype.md#roomprofiletype) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。 |
| [getAudioDeviceManager](Windows-api.md#IRTCVideo-getaudiodevicemanager) | 设备音频管理接口创建 |
| [startAudioDeviceRecordTest](Windows-api.md#IAudioDeviceManager-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br> |
| [stopAudioDeviceRecordAndPlayTest](Windows-api.md#IAudioDeviceManager-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br><br/>调用 [startAudioDeviceRecordTest](Windows-api.md#IAudioDeviceManager-startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
| [stopAudioDevicePlayTest](Windows-api.md#IAudioDeviceManager-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Windows-api.md#IAudioDeviceManager-startaudiodevicerecordtest) 开始的音频播放设备测试。<br><br/>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |
| [enableExternalSoundCard](Windows-api.md#IRTCVideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |

## 视频管理

| 方法 | 描述 |
| --- | --- |
| [startVideoCapture](Windows-api#IRTCVideo-startvideocapture) | 立即开启内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 [onUserStartVideoCapture](Windows-callback.md#IRTCVideoEventHandler-onuserstartvideocapture) 的回调。 |
| [stopVideoCapture](Windows-api#IRTCVideo-stopvideocapture) | 立即关闭内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [onVideoDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) 的回调。  <br><br/>非隐身用户进房后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Windows-callback.md#IRTCVideoEventHandler-onuserstopvideocapture) 的回调。 |
| [setVideoCaptureConfig](Windows-api.md#IRTCVideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。<br><br/>如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数，包括模式、分辨率、帧率。 |
| [setLocalVideoCanvas](Windows-api.md#IRTCVideo-setlocalvideocanvas) | 设置本地视频渲染时使用的视图，并设置渲染模式。 |
| [updateLocalVideoCanvas](Windows-api.md#IRTCVideo-updatelocalvideocanvas) | 修改本地视频渲染模式和背景色。 |
| [setRemoteVideoCanvas](Windows-api.md#IRTCVideo-setremotevideocanvas) | 设置渲染指定视频流 `stream_key` 时，使用的视图和渲染模式。 <br><br/>如果需要解除某个用户的绑定视图，你可以把 `canvas` 设置为空。 |
| [updateRemoteStreamVideoCanvas](Windows-api.md#IRTCVideo-updateremotestreamvideocanvas) | 修改远端视频渲染模式和背景色。 |
| [enumerateVideoCaptureDevices](Windows-api.md#IVideoDeviceManager-enumeratevideocapturedevices) | 获取当前系统内视频采集设备列表。 |
| [setVideoCaptureDevice](Windows-api.md#IVideoDeviceManager-setvideocapturedevice) | 设置当前视频采集设备 |
| [getVideoDeviceManager](Windows-api.md#IRTCVideo-getvideodevicemanager) | 创建视频设备管理实例 |
| [getVideoCaptureDevice](Windows-api.md#IVideoDeviceManager-getvideocapturedevice) | 获取当前 SDK 正在使用的视频采集设备信息 |
| [buildVideoFrame](Windows-api.md#buildvideoframe) | 创建 IVideoFrame |
| [setVideoEncoderConfig](Windows-api.md#IRTCVideo-setvideoencoderconfig) | <span id="IRTCVideo-setvideoencoderconfig-1"></span> 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br><br/>该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2)。 |
| [setVideoEncoderConfig](Windows-api.md#IRTCVideo-setvideoencoderconfig) | <span id="IRTCVideo-setvideoencoderconfig-2"></span> 视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [buildEncodedVideoFrame](Windows-api.md#buildencodedvideoframe) | 创建 IEncodedVideoFrame |

## 音视频传输

| 方法 | 描述 |
| --- | --- |
| [publishStream](Windows-api.md#IRTCRoom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream](Windows-api.md#IRTCRoom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [setDummyCaptureImagePath](Windows-api.md#IRTCVideo-setdummycaptureimagepath) | 摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。<br/>可重复调用该接口来更新图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。 |
| [subscribeStream](Windows-api.md#IRTCRoom-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream](Windows-api.md#IRTCRoom-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreams](Windows-api.md#IRTCRoom-subscribeallstreams) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreams](Windows-api.md#IRTCRoom-unsubscribeallstreams) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br><br/>自动订阅和手动订阅的流都可以通过本方法取消订阅。 |
| [requestRemoteVideoKeyFrame](Windows-api.md#IRTCVideo-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [startForwardStreamToRooms](Windows-api.md#IRTCRoom-startforwardstreamtorooms) | 开始跨房间转发媒体流。<br/>在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br> |
| [stopForwardStreamToRooms](Windows-api.md#IRTCRoom-stopforwardstreamtorooms) | 停止跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Windows-api.md#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。 |
| [updateForwardStreamToRooms](Windows-api#IRTCRoom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br><br/>通过 [startForwardStreamToRooms](Windows-api#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br/>调用本方法增加或删减房间后，将在本端触发 [onForwardStreamStateChanged](Windows-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。 |
| [pauseForwardStreamToAllRooms](Windows-api.md#IRTCRoom-pauseforwardstreamtoallrooms) | 暂停跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms](Windows-api.md#IRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br/>调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](Windows-api.md#IRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。 |
| [resumeForwardStreamToAllRooms](Windows-api.md#IRTCRoom-resumeforwardstreamtoallrooms) | 恢复跨房间媒体流转发。<br/>调用 [pauseForwardStreamToAllRooms](Windows-api.md#IRTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。 |
| [pauseAllSubscribedStream](Windows-api.md#IRTCRoom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Windows-api.md#IRTCRoom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [setMultiDeviceAVSync](Windows-api.md#IRTCRoom-setmultideviceavsync) | 设置发流端音画同步。  <br><br/>当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。 |
| [startPushPublicStream](Windows-api.md#IRTCVideo-startpushpublicstream) | 发布一路公共流<br><br/>用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream) 获取和播放指定的公共流。 |
| [stopPushPublicStream](Windows-api.md#IRTCVideo-stoppushpublicstream) | 停止发布当前用户发布的公共流<br><br/>关于发布公共流，查看 [startPushPublicStream](Windows-api.md#IRTCVideo-startpushpublicstream)。 |
| [updatePublicStreamParam](Windows-api.md#IRTCVideo-updatepublicstreamparam) | 更新公共流参数<br><br/>关于发布公共流，查看 [startPushPublicStream](Windows-api.md#IRTCVideo-startpushpublicstream)。 |
| [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream) | 订阅指定公共流<br><br/>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream](Windows-api.md#IRTCVideo-stopplaypublicstream) | 取消订阅指定公共流<br><br/>关于订阅公共流，查看 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream)。 |
| [setPublicStreamVideoCanvas](Windows-api.md#IRTCVideo-setpublicstreamvideocanvas) | 为指定公共流绑定内部渲染视图。 |
| [setPublicStreamVideoSink](Windows-api.md#IRTCVideo-setpublicstreamvideosink) | 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。 |

## 视频处理

| 方法 | 描述 |
| --- | --- |
| [setLocalVideoMirrorType](Windows-api.md#IRTCVideo-setlocalvideomirrortype) | 为采集到的视频流开启镜像 |
| [setVideoWatermark](Windows-api.md#IRTCVideo-setvideowatermark) | 在指定视频流上添加水印。 |
| [clearVideoWatermark](Windows-api.md#IRTCVideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [enableEffectBeauty](Windows-api.md#IRTCVideo-enableeffectbeauty) | 开启/关闭基础美颜。 |
| [setBeautyIntensity](Windows-api.md#IRTCVideo-setbeautyintensity) | 调整基础美颜强度。 |
| [getVideoEffectInterface](Windows-api.md#IRTCVideo-getvideoeffectinterface) | 获取视频特效接口。 |
| [getAuthMessage](Windows-api.md#IVideoEffect-getauthmessage) | 从特效 SDK 获取授权消息，用于获取在线许可证。 |
| [freeAuthMessage](Windows-api.md#IVideoEffect-freeauthmessage) | 使用完授权消息字符串后，释放内存。 |
| [initCVResource](Windows-api.md#IVideoEffect-initcvresource) | 检查视频特效证书，设置算法模型路径，并初始化特效模块。 |
| [enableVideoEffect](Windows-api.md#IVideoEffect-enablevideoeffect) | 开启高级美颜、滤镜等视频特效。 |
| [disableVideoEffect](Windows-api.md#IVideoEffect-disablevideoeffect) | 关闭视频特效。 |
| [setEffectNodes](Windows-api.md#IVideoEffect-seteffectnodes) | 设置视频特效素材包。 |
| [updateEffectNode](Windows-api.md#IVideoEffect-updateeffectnode) | 设置特效强度。 |
| [setColorFilter](Windows-api.md#IVideoEffect-setcolorfilter) | 设置颜色滤镜。 |
| [setColorFilterIntensity](Windows-api.md#IVideoEffect-setcolorfilterintensity) | 设置已启用颜色滤镜的强度。 |
| [enableVirtualBackground](Windows-api.md#IVideoEffect-enablevirtualbackground) | 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。 |
| [disableVirtualBackground](Windows-api.md#IVideoEffect-disablevirtualbackground) | 关闭虚拟背景。 |
| [enableFaceDetection](Windows-api#IVideoEffect-enablefacedetection) | 开启人脸识别功能，并设置人脸检测结果回调观察者。<br/>此观察者后，你会周期性收到 [onFaceDetectResult](Windows-callback.md#IFaceDetectionObserver-onfacedetectresult) 回调。 |
| [disableFaceDetection](Windows-api.md#IVideoEffect-disablefacedetection) | 关闭人脸识别功能。 |

## 音频处理

| 方法 | 描述 |
| --- | --- |
| [setVoiceChangerType](Windows-api.md#IRTCVideo-setvoicechangertype) | 设置变声特效类型 |
| [setVoiceReverbType](Windows-api.md#IRTCVideo-setvoicereverbtype) | 设置混响特效类型 |
| [setLocalVoicePitch](Windows-api.md#IRTCVideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |
| [setLocalVoiceEqualization](Windows-api.md#IRTCVideo-setlocalvoiceequalization) | 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [setLocalVoiceReverbParam](Windows-api.md#IRTCVideo-setlocalvoicereverbparam) | 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [enableLocalVoiceReverb](Windows-api.md#IRTCVideo-enablelocalvoicereverb) | 开启本地音效混响效果 |

## 自定义流处理

| 方法 | 描述 |
| --- | --- |
| [setVideoSourceType](Windows-api.md#IRTCVideo-setvideosourcetype) | 设置向 SDK 输入的视频源，包括屏幕流<br/>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br> |
| [pushExternalVideoFrame](Windows-api.md#IRTCVideo-pushexternalvideoframe) | 推送外部视频帧。 |
| [setLocalVideoSink](Windows-api.md#IRTCVideo-setlocalvideosink) | 将本地视频流与自定义渲染器绑定。 |
| [setRemoteVideoSink](Windows-api.md#IRTCVideo-setremotevideosink) | 将远端视频流与自定义渲染器绑定。 |
| [registerRemoteEncodedVideoFrameObserver](Windows-api#IRTCVideo-registerremoteencodedvideoframeobserver) | 注册远端编码后视频数据回調。  <br><br/>完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame](Windows-callback.md#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) 回调 |
| [setVideoDecoderConfig](Windows-api.md#IRTCVideo-setvideodecoderconfig) | 在订阅远端视频流之前，设置远端视频数据解码方式 |
| [setAudioSourceType](Windows-api.md#IRTCVideo-setaudiosourcetype) | 切换音频采集方式 |
| [setAudioRenderType](Windows-api.md#IRTCVideo-setaudiorendertype) | 切换音频渲染方式 |
| [pushExternalAudioFrame](Windows-api.md#IRTCVideo-pushexternalaudioframe) | 推送自定义采集的音频数据到 RTC SDK。 |
| [pullExternalAudioFrame](Windows-api.md#IRTCVideo-pullexternalaudioframe) | 拉取远端音频数据。<br><br/>可用于自定义音频渲染。 |
| [registerLocalVideoProcessor](Windows-api.md#IRTCVideo-registerlocalvideoprocessor) | 设置自定义视频前处理器。<br><br/>使用这个视频前处理器，你可以调用 [processVideoFrame](Windows-api.md#IVideoProcessor-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。 |
| [processVideoFrame](Windows-api.md#IVideoProcessor-processvideoframe) | 获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor](Windows-api.md#IRTCVideo-registerlocalvideoprocessor) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。 |
| [registerAudioProcessor](Windows-api.md#IRTCVideo-registeraudioprocessor) | 注册自定义音频处理器。<br><br/>注册完成后，你可以调用 [enableAudioProcessor](Windows-api.md#IRTCVideo-enableaudioprocessor)，对本地采集或接收到的远端音频进行处理。 |
| [enableAudioProcessor](Windows-api.md#IRTCVideo-enableaudioprocessor) | 设置并开启指定的音频帧回调，进行自定义处理。 |
| [disableAudioProcessor](Windows-api.md#IRTCVideo-disableaudioprocessor) | 关闭自定义音频处理。 |
| [registerAudioFrameObserver](Windows-api.md#IRTCVideo-registeraudioframeobserver) | 注册音频数据回调观察者。  <br> |
| [enableAudioFrameCallback](Windows-api.md#IRTCVideo-enableaudioframecallback) | 设置并开启指定的音频数据帧回调 |
| [disableAudioFrameCallback](Windows-api.md#IRTCVideo-disableaudioframecallback) | 关闭音频回调 |
| [registerLocalEncodedVideoFrameObserver](Windows-api#IRTCVideo-registerlocalencodedvideoframeobserver) | 注册本地视频帧监测器。  <br><br/>无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame](Windows-callback.md#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) 回调给用户 |
| [setExternalVideoEncoderEventHandler](Windows-api.md#IRTCVideo-setexternalvideoencodereventhandler) | 注册自定义编码帧推送事件回调 |
| [pushExternalEncodedVideoFrame](Windows-api.md#IRTCVideo-pushexternalencodedvideoframe) | 推送自定义编码后的视频流 |

## 网络管理

| 方法 | 描述 |
| --- | --- |
| [enableSimulcastMode](Windows-api.md#IRTCVideo-enablesimulcastmode) | 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。 |
| [setRemoteVideoConfig](Windows-api.md#IRTCRoom-setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [setPublishFallbackOption](Windows-api.md#IRTCVideo-setpublishfallbackoption) | 设置发布的音视频流的回退选项。  <br><br/>你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。 |
| [setSubscribeFallbackOption](Windows-api.md#IRTCVideo-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。 <br><br/>你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority](Windows-api.md#IRTCVideo-setremoteuserpriority) | 设置用户优先级。 |
| [startNetworkDetection](Windows-api.md#IRTCVideo-startnetworkdetection) | 开启通话前网络探测 |
| [stopNetworkDetection](Windows-api.md#IRTCVideo-stopnetworkdetection) | 停止通话前网络探测 |
| [startEchoTest](Windows-api.md#IRTCVideo-startechotest) | 开启音视频回路测试。  <br><br/>在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br><br/>开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。 |
| [stopEchoTest](Windows-api.md#IRTCVideo-stopechotest) | 停止音视频回路测试。  <br><br/>调用 [startEchoTest](Windows-api.md#IRTCVideo-startechotest) 开启音视频回路检测后，你必须调用该方法停止检测。 |
| [getNetworkTimeInfo](Windows-api.md#IRTCVideo-getnetworktimeinfo) | 通过 NTP 协议，获取网络时间。 |

## 消息

| 方法 | 描述 |
| --- | --- |
| [sendRoomMessage](Windows-api.md#IRTCRoom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [sendRoomBinaryMessage](Windows-api.md#IRTCRoom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [login](Windows-api.md#IRTCVideo-login) | 必须先登录，才能调用 [sendUserMessageOutsideRoom](Windows-api.md#IRTCVideo-sendusermessageoutsideroom) 和 [sendServerMessage](Windows-api.md#IRTCVideo-sendservermessage) 发送房间外点对点消息和向应用服务器发送消息 <br><br/>在调用本接口登录后，如果想要登出，需要调用 [logout](Windows-api.md#IRTCVideo-logout)。 |
| [logout](Windows-api.md#IRTCVideo-logout) | 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken](Windows-api#IRTCVideo-updatelogintoken) | 更新用户用于登录的 Token  <br><br/>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br><br/>调用 [login](Windows-api#IRTCVideo-login) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [onLoginResult](Windows-callback.md#IRTCVideoEventHandler-onloginresult) 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。 |
| [setServerParams](Windows-api.md#IRTCVideo-setserverparams) | 设置应用服务器参数  <br><br/>客户端调用 [sendServerMessage](Windows-api.md#IRTCVideo-sendservermessage) 或 [sendServerBinaryMessage](Windows-api.md#IRTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须设置有效签名和应用服务器地址。 |
| [getPeerOnlineStatus](Windows-api.md#IRTCVideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [sendUserMessage](Windows-api.md#IRTCRoom-sendusermessage) | 给房间内指定的用户发送点对点文本消息（P2P）。 |
| [sendUserBinaryMessage](Windows-api.md#IRTCRoom-senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息（P2P）。 |
| [sendUserMessageOutsideRoom](Windows-api.md#IRTCVideo-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom](Windows-api.md#IRTCVideo-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [sendServerMessage](Windows-api.md#IRTCVideo-sendservermessage) | 客户端给应用服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Windows-api.md#IRTCVideo-sendserverbinarymessage) | 客户端给应用服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo](Windows-api#IRTCVideo-sendstreamsyncinfo) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [onStreamSyncInfoReceived](Windows-callback.md#IRTCVideoEventHandler-onstreamsyncinforeceived) 回调。 |
| [sendSEIMessage](Windows-api.md#IRTCVideo-sendseimessage) | <span id="IRTCVideo-sendseimessage-2"></span> 通过视频帧发送 SEI 数据。<br/>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |

## CDN 推流

| 方法 | 描述 |
| --- | --- |
| [startLiveTranscoding](Windows-api.md#IRTCVideo-startlivetranscoding) | 新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br><br/>同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。 |
| [stopLiveTranscoding](Windows-api.md#IRTCVideo-stoplivetranscoding) | 停止转推直播，会收到 [onStreamMixingEvent](Windows-callback#ITranscoderObserver-onstreammixingevent) 回调。  <br><br/>关于启动转推直播，参看 [startLiveTranscoding](Windows-api.md#IRTCVideo-startlivetranscoding)。 |
| [updateLiveTranscoding](Windows-api.md#IRTCVideo-updatelivetranscoding) | 更新转推直播参数，会收到 [onStreamMixingEvent](Windows-callback#ITranscoderObserver-onstreammixingevent) 回调。  <br><br/>使用 [startLiveTranscoding](Windows-api.md#IRTCVideo-startlivetranscoding) 启用转推直播功能后，使用此方法更新功能配置参数。 |
| [setAudioAlignmentProperty](Windows-api.md#IRTCVideo-setaudioalignmentproperty) | 在听众端，设置订阅的所有远端音频流精准对齐后播放。 |
| [startPushSingleStreamToCDN](Windows-api.md#IRTCVideo-startpushsinglestreamtocdn) | 新增单流转推直播任务。 |
| [stopPushStreamToCDN](Windows-api.md#IRTCVideo-stoppushstreamtocdn) | 停止转推直播。<br><br/>关于启动转推直播，参看 [startPushSingleStreamToCDN](Windows-api.md#IRTCVideo-startpushsinglestreamtocdn)。 |

## 混音

| 方法 | 描述 |
| --- | --- |
| [getAudioMixingManager](Windows-api.md#IRTCVideo-getaudiomixingmanager) | 混音管理接口创建 |
| [enableAudioMixingFrame](Windows-api.md#IAudioMixingManager-enableaudiomixingframe) | 启动 PCM 音频数据混音。<br><br/>要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 id。<br/>启动 PCM 音频数据混音。<br><br/>要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 mix_id。 |
| [disableAudioMixingFrame](Windows-api.md#IAudioMixingManager-disableaudiomixingframe) | 关闭 PCM 混音 |
| [pushAudioMixingFrame](Windows-api.md#IAudioMixingManager-pushaudiomixingframe) | 推送 PCM 音频帧数据用于混音 |
| [startAudioMixing](Windows-api.md#IAudioMixingManager-startaudiomixing) | 开始播放音频文件。<br/>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。 |
| [stopAudioMixing](Windows-api.md#IAudioMixingManager-stopaudiomixing) | 停止播放音频文件及混音。 |
| [pauseAudioMixing](Windows-api.md#IAudioMixingManager-pauseaudiomixing) | 暂停播放音频文件及混音。 |
| [resumeAudioMixing](Windows-api.md#IAudioMixingManager-resumeaudiomixing) | 恢复播放音频文件及混音。 |
| [setAudioMixingVolume](Windows-api.md#IAudioMixingManager-setaudiomixingvolume) | 调节指定混音的音量大小，包括音频文件混音和 PCM 混音。 |
| [enableVocalInstrumentBalance](Windows-api.md#IRTCVideo-enablevocalinstrumentbalance) | 开启/关闭音量均衡功能。  <br><br/>开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 [setAudioMixingLoudness](Windows-api.md#IAudioMixingManager-setaudiomixingloudness) 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。（Linux 不支持） |
| [setAudioMixingLoudness](Windows-api.md#IAudioMixingManager-setaudiomixingloudness) | 如果你需要使用 `enableVocalInstrumentBalance` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。 |
| [enablePlaybackDucking](Windows-api.md#IRTCVideo-enableplaybackducking) | 打开/关闭音量闪避功能，适用于在 RTC 通话过程中会同时播放短视频或音乐的场景，如“一起看”、“在线 KTV”等。  <br><br/>开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。 |
| [setAudioMixingPitch](Windows-api.md#IAudioMixingManager-setaudiomixingpitch) | 开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。 |
| [getAudioMixingCurrentPosition](Windows-api.md#IAudioMixingManager-getaudiomixingcurrentposition) | 获取音频文件播放进度。 |
| [setAudioMixingPosition](Windows-api.md#IAudioMixingManager-setaudiomixingposition) | 设置音频文件的起始播放位置 |
| [getAudioTrackCount](Windows-api.md#IAudioMixingManager-getaudiotrackcount) | 获取当前音频文件的音轨索引 |
| [selectAudioTrack](Windows-api.md#IAudioMixingManager-selectaudiotrack) | 指定当前音频文件的播放音轨 |
| [setAudioMixingPlaybackSpeed](Windows-api.md#IAudioMixingManager-setaudiomixingplaybackspeed) | 设置混音时音频文件的播放速度 |
| [setAudioMixingDualMonoMode](Windows-api.md#IAudioMixingManager-setaudiomixingdualmonomode) | 设置当前音频文件的声道模式 |
| [setAudioMixingProgressInterval](Windows-api.md#IAudioMixingManager-setaudiomixingprogressinterval) | 设置混音时音频文件播放进度回调的间隔 |
| [preloadAudioMixing](Windows-api.md#IAudioMixingManager-preloadaudiomixing) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [unloadAudioMixing](Windows-api.md#IAudioMixingManager-unloadaudiomixing) | 卸载指定音乐文件。 |
| [getAudioMixingDuration](Windows-api.md#IAudioMixingManager-getaudiomixingduration) | 获取音频文件时长。 |
| [getAudioMixingPlaybackDuration](Windows-api.md#IAudioMixingManager-getaudiomixingplaybackduration) | 获取混音音频文件的实际播放时长（单位：毫秒）。 |
| [stopAllAudioMixing](Windows-api.md#IAudioMixingManager-stopallaudiomixing) | 停止播放所有音频文件。 |
| [pauseAllAudioMixing](Windows-api.md#IAudioMixingManager-pauseallaudiomixing) | 暂停播放所有音频文件。 |
| [resumeAllAudioMixing](Windows-api.md#IAudioMixingManager-resumeallaudiomixing) | 恢复播放所有音频文件。 |
| [registerAudioFileFrameObserver](Windows-api.md#IAudioMixingManager-registeraudiofileframeobserver) | 注册本地音频文件混音的音频帧观察者。<br/>当本地音频文件混音时，会收到相关回调。 |

## 屏幕分享

| 方法 | 描述 |
| --- | --- |
| [getScreenCaptureSourceList](Windows-api.md#IRTCVideo-getscreencapturesourcelist) | 获取共享对象列表。 |
| [startScreenVideoCapture](Windows-api.md#IRTCVideo-startscreenvideocapture) | 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，应用窗口中显示的内容，或虚拟屏幕中显示的内容。<br><br/>其中，虚拟屏幕中显示的内容仅在 Windows 平台上支持。 |
| [updateScreenCaptureHighlightConfig](Windows-api.md#IRTCVideo-updatescreencapturehighlightconfig) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新边框高亮设置。默认展示表框。 |
| [updateScreenCaptureMouseCursor](Windows-api.md#IRTCVideo-updatescreencapturemousecursor) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新对鼠标的处理设置。默认采集鼠标。 |
| [updateScreenCaptureFilterConfig](Windows-api.md#IRTCVideo-updatescreencapturefilterconfig) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。 |
| [updateScreenCaptureRegion](Windows-api.md#IRTCVideo-updatescreencaptureregion) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新采集区域。仅用于采集源为显示器屏幕时。 |
| [stopScreenVideoCapture](Windows-api.md#IRTCVideo-stopscreenvideocapture) | 停止屏幕视频流采集。 |
| [publishScreen](Windows-api.md#IRTCRoom-publishscreen) | 在当前所在房间内手动发布本地屏幕共享音视频流。<br><br/>如果你需要手动向多个房间发布屏幕共享流，可以使用同样的 uid 加入多个房间，并在每个房间调用该方法。同时，你可以在不同的房间发布不同的屏幕共享流类型。 |
| [unpublishScreen](Windows-api.md#IRTCRoom-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [getThumbnail](Windows-api.md#IRTCVideo-getthumbnail) | 获取共享对象缩略图 |
| [getWindowAppIcon](Windows-api.md#IRTCVideo-getwindowappicon) | 获取应用窗体所属应用的图标。 |
| [setScreenAudioSourceType](Windows-api.md#IRTCVideo-setscreenaudiosourcetype) | 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集） |
| [setScreenAudioStreamIndex](Windows-api.md#IRTCVideo-setscreenaudiostreamindex) | 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式 |
| [setScreenAudioChannel](Windows-api.md#IRTCVideo-setscreenaudiochannel) | 在屏幕共享时，设置屏幕音频流的声道数 |
| [pushScreenAudioFrame](Windows-api.md#IRTCVideo-pushscreenaudioframe) | 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。 |
| [pushScreenVideoFrame](Windows-api.md#IRTCVideo-pushscreenvideoframe) | 推送屏幕视频帧 |
| [setOriginalScreenVideoInfo](Windows-api.md#IRTCVideo-setoriginalscreenvideoinfo) | 外部采集时，当屏幕或待采集窗口大小发生改变，为了使 RTC 更好地决策合适的帧率和分辨率积，调用此接口设置改变前的分辨率。 |
| [setScreenVideoEncoderConfig](Windows-api.md#IRTCVideo-setscreenvideoencoderconfig) | 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [subscribeScreen](Windows-api.md#IRTCRoom-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen](Windows-api.md#IRTCRoom-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |

## 安全与加密

| 方法 | 描述 |
| --- | --- |
| [startCloudProxy](Windows-api.md#IRTCVideo-startcloudproxy) | 开启云代理 |
| [stopCloudProxy](Windows-api.md#IRTCVideo-stopcloudproxy) | 关闭云代理 |
| [setCustomizeEncryptHandler](Windows-api.md#IRTCVideo-setcustomizeencrypthandler) | 设置自定义加密和解密方式。 |
| [setEncryptInfo](Windows-api.md#IRTCVideo-setencryptinfo) | 设置传输时使用内置加密的方式。 |

## 高级功能

| 方法 | 描述 |
| --- | --- |
| [startFileRecording](Windows-api.md#IRTCVideo-startfilerecording) | 录制通话过程中的音视频数据到本地的文件中。 |
| [stopFileRecording](Windows-api.md#IRTCVideo-stopfilerecording) | 停止本地录制 |
| [startAudioRecording](Windows-api.md#IRTCVideo-startaudiorecording) | 开启录制语音通话，生成本地文件。 |
| [stopAudioRecording](Windows-api.md#IRTCVideo-stopaudiorecording) | 停止音频文件录制 |
| [getSpatialAudio](Windows-api.md#IRTCRoom-getspatialaudio) | 获取空间音频接口实例。 |
| [disableRemoteOrientation](Windows-api.md#ISpatialAudio-disableremoteorientation) | 关闭本地用户朝向对本地用户发声效果的影响。<br><br/>调用此接口后，房间内的其他用户收听本地发声时，声源都在收听者正面。 |
| [enableSpatialAudio](Windows-api.md#ISpatialAudio-enablespatialaudio) | 开启/关闭空间音频功能。  <br> |
| [updateListenerOrientation](Windows-api.md#ISpatialAudio-updatelistenerorientation) | 更新在房间内收听音频时的朝向。<br><br/>通过此接口，你可以设定本地用户的发声朝向和收听朝向不同。 |
| [updateListenerPosition](Windows-api.md#ISpatialAudio-updatelistenerposition) | 更新在房间内收听音频时的位置。<br><br/>通过此接口，你可以设定本地发声位置和收听位置不同。 |
| [updatePosition](Windows-api.md#ISpatialAudio-updateposition) | 更新本地用户发声时，在房间内空间直角坐标系中的位置坐标。  <br><br/>如果未调用 [updateListenerPosition](Windows-api.md#ISpatialAudio-updatelistenerposition) 设定收听位置，默认的收听位置和发声位置一致。 |
| [updateSelfOrientation](Windows-api.md#ISpatialAudio-updateselforientation) | 更新本地用户发声时，在空间音频坐标系下的朝向。  <br><br/>如果未调用 [updateListenerOrientation](Windows-api.md#ISpatialAudio-updatelistenerorientation) 设定收听朝向，默认的收听位朝向和发声朝向一致。 |
| [getRangeAudio](Windows-api.md#IRTCRoom-getrangeaudio) | 获取范围语音接口实例。 |
| [enableRangeAudio](Windows-api.md#IRangeAudio-enablerangeaudio) | 开启/关闭范围语音功能。  <br><br/>范围语音是指，在同一 RTC 房间中设定的音频接收距离范围内，本地用户收听到的远端用户音频音量会随着远端用户的靠近/远离而放大/衰减；若远端用户在房间内的位置超出设定范围，则本地用户无法接收其音频。音频接收范围设置参看 [updateReceiveRange](Windows-api.md#IRangeAudio-updatereceiverange)。 |
| [setAttenuationModel](Windows-api.md#IRangeAudio-setattenuationmodel) | 设置范围语音的音量衰减模式。<br> |
| [setNoAttenuationFlags](Windows-api.md#IRangeAudio-setnoattenuationflags) | 添加标签组，用于标记相互之间通话不衰减的用户组。<br><br/>在同一个 RTC 房间中，如果多个用户的标签组之间有交集，那么，他们之间互相通话时，通话不衰减。<br><br/>比如，用户身处多个队伍，队伍成员间通话不衰减。那么，可以为每个队伍绑定专属标签，每个用户的标签组包含用户所属各个队伍的标签。 |
| [updatePosition](Windows-api.md#IRangeAudio-updateposition) | 更新本地用户在房间内空间直角坐标系中的位置坐标。 |
| [updateReceiveRange](Windows-api.md#IRangeAudio-updatereceiverange) | 更新本地用户的音频收听范围。 |
| [CreateStreamingRTCEngine](Windows-api.md#createstreamingrtcengine) | 创建 IStreamingRTCEngine 实例。  <br><br/>如果当前线程中未创建引擎实例，那么你必须先使用此方法，以使用 IStreamingRTCEngine 提供的各种音视频能力。  <br><br/>如果当前线程中已创建了引擎实例，再次调用此方法时，会创建另一个独立的引擎实例。 |
| [DestroyStreamingRTCEngine](Windows-api.md#destroystreamingrtcengine) | 销毁由 [CreateStreamingRTCEngine](Windows-api.md#createstreamingrtcengine) 创建的 IStreamingRTCEngine 实例，并释放所有相关资源。 |
| [SetVideoEncoderConfig](Windows-api.md#IStreamingRTCEngine-setvideoencoderconfig) | 设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。 |
| [Startup](Windows-api#IStreamingRTCEngine-startup) | 启动串流引擎 <br><br/>通过 [EngineConfig](Windows-keytype.md#engineconfig) 设置引擎类型服务端或客户端和端口号范围 <br> |
| [Shutdown](Windows-api.md#IStreamingRTCEngine-shutdown) | 关闭串流引擎 |
| [SendP2PMessage](Windows-api.md#IStreamingRTCEngine-sendp2pmessage) | 发送点对点文本消息 |
| [SendP2PBinaryMessage](Windows-api.md#IStreamingRTCEngine-sendp2pbinarymessage) | 发送点对点二进制消息 |
| [PullAudioFrame](Windows-api.md#IStreamingRTCEngine-pullaudioframe) | 拉取音频数据 |
| [PushAudioFrame](Windows-api.md#IStreamingRTCEngine-pushaudioframe) | 推送自定义音频数据 |
| [SetVideoDecoderConfig](Windows-api.md#IStreamingRTCEngine-setvideodecoderconfig) | 设置远端视频数据解码方式。<br><br/>需要在 [Startup](Windows-api.md#IStreamingRTCEngine-startup) 之前调用本接口。  <br> |
| [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) | 设置输入到串流引擎的视频源<br><br/>默认使用内部采集。内部采集指：使用 SDK 内置的视频采集机制进行视频采集。 <br> |
| [PushVideoFrame](Windows-api.md#IStreamingRTCEngine-pushvideoframe) | 发送外部源视频数据 |
| [PushEncodedVideoFrame](Windows-api.md#IStreamingRTCEngine-pushencodedvideoframe) | 推送自定义编码后的视频流 |
| [RequestRemoteVideoKeyFrame](Windows-api.md#IStreamingRTCEngine-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [SetReportExtraInfo](Windows-api.md#IStreamingRTCEngine-setreportextrainfo) | 设置上报的 trace 的 extra_info |
| [takeLocalSnapshot](Windows-api.md#IRTCVideo-takelocalsnapshot) | 截取本地视频画面 |
| [takeRemoteSnapshot](Windows-api.md#IRTCVideo-takeremotesnapshot) | 截取远端视频画面 |
| [setAnsMode](Windows-api.md#IRTCVideo-setansmode) | 支持根据业务场景，设置通话中的音频降噪模式。 |

## 音乐及打分

| 方法 | 描述 |
| --- | --- |
| [getKTVManager](Windows-api.md#IRTCVideo-getktvmanager) | 创建 KTV 管理接口。 |
| [setMaxCacheSize](Windows-api.md#IKTVManager-setmaxcachesize) | 设置歌曲文件最大占用的本地缓存。 |
| [setKTVEventHandler](Windows-api.md#IKTVManager-setktveventhandler) | 设置 KTV 回调接口。 |
| [getMusicList](Windows-api.md#IKTVManager-getmusiclist) | 获取歌曲列表。 |
| [searchMusic](Windows-api.md#IKTVManager-searchmusic) | 根据关键词搜索歌曲。 |
| [getHotMusic](Windows-api.md#IKTVManager-gethotmusic) | 根据榜单类别获取每个榜单的歌曲列表。 |
| [getMusicDetail](Windows-api.md#IKTVManager-getmusicdetail) | 获取音乐详细信息。 |
| [downloadMusic](Windows-api.md#IKTVManager-downloadmusic) | 下载音乐。 |
| [downloadLyric](Windows-api.md#IKTVManager-downloadlyric) | 下载歌词。 |
| [downloadMidi](Windows-api.md#IKTVManager-downloadmidi) | 下载 MIDI 文件。 |
| [cancelDownload](Windows-api.md#IKTVManager-canceldownload) | 取消下载任务。 |
| [clearCache](Windows-api.md#IKTVManager-clearcache) | 清除当前音乐缓存文件，包括音乐音频和歌词。 |
| [getPlayer](Windows-api.md#IKTVManager-getplayer) | 获取 KTV 播放器。 |
| [setPlayerEventHandler](Windows-api.md#IKTVPlayer-setplayereventhandler) | 设置 KTV 播放器进度及状态回调接口。 |
| [playMusic](Windows-api.md#IKTVPlayer-playmusic) | 播放歌曲。 |
| [pauseMusic](Windows-api.md#IKTVPlayer-pausemusic) | 暂停播放歌曲。 |
| [resumeMusic](Windows-api.md#IKTVPlayer-resumemusic) | 继续播放歌曲。 |
| [stopMusic](Windows-api.md#IKTVPlayer-stopmusic) | 停止播放歌曲。 |
| [seekMusic](Windows-api.md#IKTVPlayer-seekmusic) | 设置音乐文件的起始播放位置。 |
| [setMusicVolume](Windows-api.md#IKTVPlayer-setmusicvolume) | 设置歌曲播放音量，只能在开始播放后进行设置。 |
| [switchAudioTrackType](Windows-api.md#IKTVPlayer-switchaudiotracktype) | 切换歌曲原唱伴唱。 |
| [setMusicPitch](Windows-api.md#IKTVPlayer-setmusicpitch) | 对播放中的音乐设置升降调信息。 |
| [getSingScoringManager](Windows-api.md#IRTCVideo-getsingscoringmanager) | 创建 K 歌评分管理接口。 |
| [getCount](Windows-api.md#IStandardPitchCollection-getcount) | 获取歌词句子总数 |
| [getStandardPitchInfo](Windows-api.md#IStandardPitchCollection-getstandardpitchinfo) | 获取每句歌词的标准音高信息 |
| [release](Windows-api.md#IStandardPitchCollection-release) | 销毁 IStandardPitchCollection 类，释放资源 |
| [initSingScoring](Windows-api.md#ISingScoringManager-initsingscoring) | 初始化 K 歌评分。 |
| [setSingScoringConfig](Windows-api.md#ISingScoringManager-setsingscoringconfig) | 设置 K 歌评分参数。 |
| [getStandardPitchInfoCollection](Windows-api.md#ISingScoringManager-getstandardpitchinfocollection) | 获取标准音高数据。 |
| [startSingScoring](Windows-api.md#ISingScoringManager-startsingscoring) | 开始 K 歌评分。 |
| [stopSingScoring](Windows-api.md#ISingScoringManager-stopsingscoring) | 停止 K 歌评分。 |
| [getLastSentenceScore](Windows-api.md#ISingScoringManager-getlastsentencescore) | 获取上一句的演唱评分。调用 [startSingScoring](Windows-api.md#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。 |
| [getTotalScore](Windows-api.md#ISingScoringManager-gettotalscore) | 获取当前演唱总分。调用 [startSingScoring](Windows-api.md#ISingScoringManager-startsingscoring) 开始评分后可以调用该接口。 |
| [getAverageScore](Windows-api.md#ISingScoringManager-getaveragescore) | 获取当前演唱歌曲的平均分。 |

# 回调
## 引擎管理

| 回调 | 描述 |
| --- | --- |
| [onLogReport](Windows-callback.md#IRTCVideoEventHandler-onlogreport) | 上报日志时回调该事件。 |
| [onSysStats](Windows-callback.md#IRTCVideoEventHandler-onsysstats) | 周期性（2s）发出回调，报告当前 CPU 与内存的相关信息。 |
| [onWarning](Windows-callback.md#IRTCVideoEventHandler-onwarning) | 发生警告回调。  <br><br/>SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。<br><br/>你可能需要干预. |
| [onError](Windows-callback.md#IRTCVideoEventHandler-onerror) | 发生错误回调。<br><br/>SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。 |
| [onHttpProxyState](Windows-callback.md#IRTCVideoEventHandler-onhttpproxystate) | HTTP 代理连接状态改变时，收到该回调。 |
| [onHttpsProxyState](Windows-callback.md#IRTCVideoEventHandler-onhttpsproxystate) | HTTPS 代理连接状态改变时，收到该回调。 |
| [onSocks5ProxyState](Windows-callback.md#IRTCVideoEventHandler-onsocks5proxystate) | SOCKS5 代理状态改变时，收到该回调。 |
| [onTokenWillExpire](Windows-callback#IRTCRoomEventHandler-ontokenwillexpire) | Token 进房权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Windows-api.md#IRTCRoom-updatetoken) 更新 Token 进房权限。 |
| [onPublishPrivilegeTokenWillExpire](Windows-callback#IRTCRoomEventHandler-onpublishprivilegetokenwillexpire) | Token 发布权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Windows-api.md#IRTCRoom-updatetoken) 更新 Token 发布权限。 |
| [onSubscribePrivilegeTokenWillExpire](Windows-callback#IRTCRoomEventHandler-onsubscribeprivilegetokenwillexpire) | Token 订阅权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken](Windows-api.md#IRTCRoom-updatetoken) 更新 Token 订阅权限有效期。 |
| [onLicenseWillExpire](Windows-callback.md#IRTCVideoEventHandler-onlicensewillexpire) | license过期时间提醒 |

## 房间管理

| 回调 | 描述 |
| --- | --- |
| [onRoomStateChanged](Windows-callback.md#IRTCRoomEventHandler-onroomstatechanged) | 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。 |
| [onCreateRoomStateChanged](Windows-callback.md#IRTCVideoEventHandler-oncreateroomstatechanged) | 创建房间失败回调。 |
| [onLeaveRoom](Windows-callback#IRTCRoomEventHandler-onleaveroom) | 离开房间成功回调。  <br><br/>用户调用 [leaveRoom](Windows-api.md#IRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br> |
| [onUserJoined](Windows-callback#IRTCRoomEventHandler-onuserjoined) | 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br><br/>1. 远端用户调用 [setUserVisibility](Windows-api.md#IRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br><br/>2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br><br/>3. 房间内隐身远端用户调用 [setUserVisibility](Windows-api.md#IRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br><br/>4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br> |
| [onUserLeave](Windows-callback.md#IRTCRoomEventHandler-onuserleave) | 远端用户离开房间，或切至不可见时，本地用户会收到此事件 |
| [onRoomStats](Windows-callback.md#IRTCRoomEventHandler-onroomstats) | 房间内通话统计信息回调。  <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |

## 音频管理

| 回调 | 描述 |
| --- | --- |
| [onAudioDeviceWarning](Windows-callback.md#IRTCVideoEventHandler-onaudiodevicewarning) | 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。 |
| [onAudioDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudiodevicestatechanged) | 音频设备状态回调。提示音频采集、音频播放等设备设备的状态。 |
| [onLocalAudioPropertiesReport](Windows-callback#IRTCVideoEventHandler-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Windows-api.md#IRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br><br/>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。 |
| [onRemoteAudioPropertiesReport](Windows-callback#IRTCVideoEventHandler-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Windows-api.md#IRTCVideo-enableaudiopropertiesreport)，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br><br/>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onUserStartAudioCapture](Windows-callback#IRTCVideoEventHandler-onuserstartaudiocapture) | 房间内的用户调用 [startAudioCapture](Windows-api.md#IRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。 |
| [onUserStopAudioCapture](Windows-callback#IRTCVideoEventHandler-onuserstopaudiocapture) | 房间内的用户调用 [stopAudioCapture](Windows-api.md#IRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。 |
| [onActiveSpeaker](Windows-callback#IRTCVideoEventHandler-onactivespeaker) | 调用 [enableAudioPropertiesReport](Windows-api.md#IRTCVideo-enableaudiopropertiesreport) 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [onStreamSyncInfoReceived](Windows-callback#IRTCVideoEventHandler-onstreamsyncinforeceived) | 音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo](Windows-api.md#IRTCVideo-sendstreamsyncinfo) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br> |
| [onAudioStreamBanned](Windows-callback.md#IRTCRoomEventHandler-onaudiostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [onAudioPlaybackDeviceTestVolume](Windows-callback.md#IRTCVideoEventHandler-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onAudioDeviceVolumeChanged](Windows-callback.md#IRTCVideoEventHandler-onaudiodevicevolumechanged) | 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。 |

## 视频管理

| 回调 | 描述 |
| --- | --- |
| [onUserStartVideoCapture](Windows-callback#IRTCVideoEventHandler-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Windows-api.md#IRTCVideo-startvideocapture) 开启内部视频采集时，房间内其他用户会收到此回调。 |
| [onUserStopVideoCapture](Windows-callback#IRTCVideoEventHandler-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Windows-api.md#IRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。 |
| [onVideoDeviceStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideodevicestatechanged) | 视频频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。 |
| [onVideoDeviceWarning](Windows-callback.md#IRTCVideoEventHandler-onvideodevicewarning) | 视频设备警告回调，包括视频采集设备等。 |
| [onFaceDetectResult](Windows-callback.md#IFaceDetectionObserver-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。 <br><br/>调用 [enableFaceDetection](Windows-api#IVideoEffect-enablefacedetection) 注册了 [IFaceDetectionObserver](Windows-callback.md#ifacedetectionobserver)，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |

## 音视频传输

| 回调 | 描述 |
| --- | --- |
| [onStreamStateChanged](Windows-callback.md#IRTCRoomEventHandler-onstreamstatechanged) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [onAVSyncStateChange](Windows-callback#IRTCRoomEventHandler-onavsyncstatechange) | 发布端调用 [setMultiDeviceAVSync](Windows-api.md#IRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。 |
| [onUserPublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集的媒体流的回调。 |
| [onUserUnpublishStream](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onStreamSubscribed](Windows-callback.md#IRTCRoomEventHandler-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onAudioFrameSendStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudioframesendstatechanged) | 本地音频首帧发送状态发生改变时，收到此回调。 |
| [onVideoFrameSendStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideoframesendstatechanged) | 本地视频首帧发送状态发生改变时，收到此回调。 |
| [onAudioFramePlayStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudioframeplaystatechanged) | 音频首帧播放状态发生改变时，收到此回调。 |
| [onVideoFramePlayStateChanged](Windows-callback.md#IRTCVideoEventHandler-onvideoframeplaystatechanged) | 视频首帧播放状态改变回调 |
| [onLocalStreamStats](Windows-callback#IRTCRoomEventHandler-onlocalstreamstats) | 本地流数据统计以及网络质量回调。  <br><br/>本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br><br/>统计信息通过 [LocalStreamStats](Windows-keytype.md#localstreamstats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [onRemoteStreamStats](Windows-callback.md#IRTCRoomEventHandler-onremotestreamstats) | 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br><br/>本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [onNetworkQuality](Windows-callback.md#IRTCRoomEventHandler-onnetworkquality) | 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。 |
| [onForwardStreamStateChanged](Windows-callback.md#IRTCRoomEventHandler-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [onForwardStreamEvent](Windows-callback.md#IRTCRoomEventHandler-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [onFirstLocalAudioFrame](Windows-callback.md#IRTCVideoEventHandler-onfirstlocalaudioframe) | 发布音频流时，采集到第一帧音频帧，收到该回调。 |
| [onFirstRemoteAudioFrame](Windows-callback.md#IRTCVideoEventHandler-onfirstremoteaudioframe) | 接收到来自远端某音频流的第一帧时，收到该回调。 |
| [onFirstLocalVideoFrameCaptured](Windows-callback.md#IRTCVideoEventHandler-onfirstlocalvideoframecaptured) | RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。 |
| [onLocalVideoSizeChanged](Windows-callback.md#IRTCVideoEventHandler-onlocalvideosizechanged) | 本地视频大小或旋转信息发生改变时，收到此回调。 |
| [onRemoteVideoSizeChanged](Windows-callback.md#IRTCVideoEventHandler-onremotevideosizechanged) | 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onFirstRemoteVideoFrameRendered](Windows-callback.md#IRTCVideoEventHandler-onfirstremotevideoframerendered) | SDK 内部渲染成功远端视频流首帧后，收到此回调。 |
| [onVideoStreamBanned](Windows-callback.md#IRTCRoomEventHandler-onvideostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [onFirstRemoteVideoFrameDecoded](Windows-callback.md#IRTCVideoEventHandler-onfirstremotevideoframedecoded) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [onPushPublicStreamResult](Windows-callback#IRTCVideoEventHandler-onpushpublicstreamresult) | 公共流发布结果回调。<br><br/>调用 [startPushPublicStream](Windows-api.md#IRTCVideo-startpushpublicstream) 接口发布公共流后，启动结果通过此回调方法通知用户。 |
| [onPlayPublicStreamResult](Windows-callback#IRTCVideoEventHandler-onplaypublicstreamresult) | 订阅公共流的结果回调<br><br/>通过 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream) 订阅公共流后，可以通过本回调获取订阅结果。 |
| [onPublicStreamSEIMessageReceived](Windows-callback#IRTCVideoEventHandler-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br/>调用 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [onFirstPublicStreamVideoFrameDecoded](Windows-callback#IRTCVideoEventHandler-onfirstpublicstreamvideoframedecoded) | 公共流的首帧视频解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream)。 |
| [onFirstPublicStreamAudioFrame](Windows-callback#IRTCVideoEventHandler-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream](Windows-api.md#IRTCVideo-startplaypublicstream)。 |

## 自定义流处理

| 回调 | 描述 |
| --- | --- |
| [onStart](Windows-callback#IExternalVideoEncoderEventHandler-onstart) | 提示自定义编码帧可以开始推送的回调。  <br><br/>收到该回调后，你即可调用 [pushExternalEncodedVideoFrame](Windows-api.md#IRTCVideo-pushexternalencodedvideoframe) 向 SDK 推送自定义编码视频帧 |
| [onStop](Windows-callback.md#IExternalVideoEncoderEventHandler-onstop) | 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧 |
| [onRateUpdate](Windows-callback.md#IExternalVideoEncoderEventHandler-onrateupdate) | 当自定义编码流的帧率或码率发生变化时，触发该回调 |
| [onRequestKeyFrame](Windows-callback.md#IExternalVideoEncoderEventHandler-onrequestkeyframe) | 提示流发布端需重新生成关键帧的回调 |
| [onLocalEncodedVideoFrame](Windows-callback#ILocalEncodedVideoFrameObserver-onlocalencodedvideoframe) | 调用 [registerLocalEncodedVideoFrameObserver](Windows-api.md#IRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。 |
| [onRemoteEncodedVideoFrame](Windows-callback#IRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe) | 调用 [registerRemoteEncodedVideoFrameObserver](Windows-api.md#IRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调 |
| [onProcessPlayBackAudioFrame](Windows-callback.md#IAudioFrameProcessor-onprocessplaybackaudioframe) | 回调远端音频混音的音频帧地址，供自定义音频处理。 |
| [onProcessRecordAudioFrame](Windows-callback.md#IAudioFrameProcessor-onprocessrecordaudioframe) | 回调本地采集的音频帧地址，供自定义音频处理。 |
| [onProcessRemoteUserAudioFrame](Windows-callback.md#IAudioFrameProcessor-onprocessremoteuseraudioframe) | 回调单个远端用户的音频帧地址，供自定义音频处理。 |
| [onProcessScreenAudioFrame](Windows-callback.md#IAudioFrameProcessor-onprocessscreenaudioframe) | 屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。 |
| [onRecordAudioFrame](Windows-callback.md#IAudioFrameObserver-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame](Windows-callback.md#IAudioFrameObserver-onplaybackaudioframe) | 返回订阅的所有远端用户混音后的音频数据。 |
| [onRemoteUserAudioFrame](Windows-callback.md#IAudioFrameObserver-onremoteuseraudioframe) | 返回远端单个用户的音频数据 |
| [onMixedAudioFrame](Windows-callback.md#IAudioFrameObserver-onmixedaudioframe) | 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据 |
| [onRecordScreenAudioFrame](Windows-callback.md#IAudioFrameObserver-onrecordscreenaudioframe) | 返回本地屏幕录制的音频数据 |

## 网络管理

| 回调 | 描述 |
| --- | --- |
| [onPerformanceAlarms](Windows-callback.md#IRTCVideoEventHandler-onperformancealarms) | 本地未开启发布性能回退，检测到设备性能不足时，收到此回调。<br><br/>本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。 |
| [onSimulcastSubscribeFallback](Windows-callback.md#IRTCVideoEventHandler-onsimulcastsubscribefallback) | 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。 |
| [onNetworkDetectionResult](Windows-callback#IRTCVideoEventHandler-onnetworkdetectionresult) | 通话前网络探测结果。  <br><br/>成功调用 [startNetworkDetection](Windows-api.md#IRTCVideo-startnetworkdetection) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [onNetworkDetectionStopped](Windows-callback#IRTCVideoEventHandler-onnetworkdetectionstopped) | 通话前网络探测结束<br/>以下情况将停止探测并收到本一次本回调：<br><br/>1. 当调用 [stopNetworkDetection](Windows-api.md#IRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；<br/>2. 当收到远端/本端音频首帧后，停止探测；<br/>3. 当探测超过3分钟后，停止探测；<br/>4. 当探测链路断开一定时间之后，停止探测。 |
| [onConnectionStateChanged](Windows-callback.md#IRTCVideoEventHandler-onconnectionstatechanged) | SDK 与信令服务器连接状态改变回调。连接状态改变时触发。 |
| [onNetworkTypeChanged](Windows-callback.md#IRTCVideoEventHandler-onnetworktypechanged) | SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。 |
| [onSEIMessageReceived](Windows-callback#IRTCVideoEventHandler-onseimessagereceived) | 收到通过调用 [sendSEIMessage](Windows-api.md#IRTCVideo-sendseimessage) 发送带有 SEI 消息的视频帧时，收到此回调。 |
| [onEchoTestResult](Windows-callback.md#IRTCVideoEventHandler-onechotestresult) | 关于音视频回路测试结果的回调。 |
| [onNetworkTimeSynchronized](Windows-callback#IRTCVideoEventHandler-onnetworktimesynchronized) | 首次调用 [getNetworkTimeInfo](Windows-api.md#IRTCVideo-getnetworktimeinfo) 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。 |

## 消息

| 回调 | 描述 |
| --- | --- |
| [onLoginResult](Windows-callback.md#IRTCVideoEventHandler-onloginresult) | 登录结果回调 |
| [onLogout](Windows-callback.md#IRTCVideoEventHandler-onlogout) | 登出结果回调 |
| [onServerParamsSetResult](Windows-callback.md#IRTCVideoEventHandler-onserverparamssetresult) | 设置应用服务器参数的返回结果 |
| [onGetPeerOnlineStatus](Windows-callback.md#IRTCVideoEventHandler-ongetpeeronlinestatus) | 查询对端或本端用户登录状态的返回结果 |
| [onUserMessageReceivedOutsideRoom](Windows-callback#IRTCVideoEventHandler-onusermessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserMessageOutsideRoom](Windows-api.md#IRTCVideo-sendusermessageoutsideroom) 发来的文本消息时，会收到此回调 |
| [onUserBinaryMessageReceivedOutsideRoom](Windows-callback#IRTCVideoEventHandler-onuserbinarymessagereceivedoutsideroom) | 收到房间外用户调用 [sendUserBinaryMessageOutsideRoom](Windows-api.md#IRTCVideo-senduserbinarymessageoutsideroom) 发来的二进制消息时，会收到此回调 |
| [onUserMessageSendResultOutsideRoom](Windows-callback.md#IRTCVideoEventHandler-onusermessagesendresultoutsideroom) | 给房间外指定的用户发送消息的回调 |
| [onServerMessageSendResult](Windows-callback.md#IRTCVideoEventHandler-onservermessagesendresult) | 给应用服务器发送消息的回调。 |
| [onRoomMessageReceived](Windows-callback.md#IRTCRoomEventHandler-onroommessagereceived) | 接收到房间内广播消息的回调。 |
| [onRoomBinaryMessageReceived](Windows-callback#IRTCRoomEventHandler-onroombinarymessagereceived) | 收到房间内广播二进制消息的回调。<br><br/>房间内其他用户调用 [sendRoomBinaryMessage](Windows-api.md#IRTCRoom-sendroombinarymessage) 发送广播二进制消息时，收到此回调。 |
| [onUserMessageReceived](Windows-callback#IRTCRoomEventHandler-onusermessagereceived) | 收到来自房间中其他用户通过 [sendUserMessage](Windows-api.md#IRTCRoom-sendusermessage) 发来的点对点文本消息时，会收到此回调。 |
| [onUserBinaryMessageReceived](Windows-callback#IRTCRoomEventHandler-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 [sendUserBinaryMessage](Windows-api.md#IRTCRoom-senduserbinarymessage) 发来的点对点二进制消息时，会收到此回调。 |
| [onUserMessageSendResult](Windows-callback.md#IRTCRoomEventHandler-onusermessagesendresult) | 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。 |
| [onRoomMessageSendResult](Windows-callback#IRTCRoomEventHandler-onroommessagesendresult) | 调用 [sendRoomMessage](Windows-api.md#IRTCRoom-sendroommessage) 或 [sendRoomBinaryMessage](Windows-api.md#IRTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onSEIStreamUpdate](Windows-callback#IRTCVideoEventHandler-onseistreamupdate) | 黑帧视频流发布状态回调。  <br><br/>在语音通话场景下，本地用户调用 [sendSEIMessage](Windows-api.md#IRTCVideo-sendseimessage) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br><br/>你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。 |

## CDN 推流

| 回调 | 描述 |
| --- | --- |
| [onStreamMixingEvent](Windows-callback.md#ITranscoderObserver-onstreammixingevent) | 转推直播状态回调 |
| [isSupportClientPushStream](Windows-callback.md#ITranscoderObserver-issupportclientpushstream) | 是否具有推流能力。  <br><br/>+ false：不具备推流能力（默认值）  <br><br/>+ true：具备推流能力 |
| [onMixingAudioFrame](Windows-callback.md#ITranscoderObserver-onmixingaudioframe) | 合流音频回调，运行在音频回调线程 |
| [onMixingVideoFrame](Windows-callback.md#ITranscoderObserver-onmixingvideoframe) | 合流视频回调，运行在视频回调线程 |
| [onMixingDataFrame](Windows-callback.md#ITranscoderObserver-onmixingdataframe) | 视频 SEI 帧回调，运行在视频回调线程 |
| [onStreamPushEvent](Windows-callback.md#IPushSingleStreamToCDNObserver-onstreampushevent) | 单流转推直播状态回调 |

## 混音

| 回调 | 描述 |
| --- | --- |
| [onAudioMixingStateChanged](Windows-callback.md#IRTCVideoEventHandler-onaudiomixingstatechanged) | 音频混音文件播放状态改变时回调 |
| [onAudioMixingPlayingProgress](Windows-callback.md#IRTCVideoEventHandler-onaudiomixingplayingprogress) | 混音音频文件播放进度回调 |
| [onAudioFileFrame](Windows-callback.md#IAudioFileFrameObserver-onaudiofileframe) | 当本地音频文件混音时，回调播放的音频帧。 |

## 屏幕分享

| 回调 | 描述 |
| --- | --- |
| [onUserPublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](Windows-callback.md#IRTCRoomEventHandler-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onScreenVideoFrameSendStateChanged](Windows-callback.md#IRTCVideoEventHandler-onscreenvideoframesendstatechanged) | 屏幕共享流的视频首帧发送状态发生改变时，收到此回调。 |
| [onScreenVideoFramePlayStateChanged](Windows-callback.md#IRTCVideoEventHandler-onscreenvideoframeplaystatechanged) | 屏幕共享流视频首帧播放状态发生改变时，收到此回调。 |
| [onExternalScreenFrameUpdate](Windows-callback#IRTCVideoEventHandler-onexternalscreenframeupdate) | 外部采集时，调用 [setOriginalScreenVideoInfo](Windows-api.md#IRTCVideo-setoriginalscreenvideoinfo)设置屏幕或窗口大小改变前的分辨率后，若屏幕采集模式为智能模式，你将收到此回调，根据 RTC 智能决策合适的帧率和分辨率积（宽*高）重新采集。 |
| [onScreenAudioFrameSendStateChanged](Windows-callback.md#IRTCVideoEventHandler-onscreenaudioframesendstatechanged) | 屏幕音频首帧发送状态改变回调 |
| [onScreenAudioFramePlayStateChanged](Windows-callback.md#IRTCVideoEventHandler-onscreenaudioframeplaystatechanged) | 屏幕音频首帧播放状态改变回调 |

## 安全与加密

| 回调 | 描述 |
| --- | --- |
| [onCloudProxyConnected](Windows-callback#IRTCVideoEventHandler-oncloudproxyconnected) | 调用 [startCloudProxy](Windows-api.md#IRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onEncryptData](Windows-callback.md#IEncryptHandler-onencryptdata) | 自定义加密。  <br><br/>使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br><br/>暂不支持对原始音视频帧进行加密。 |
| [onDecryptData](Windows-callback.md#IEncryptHandler-ondecryptdata) | 自定义解密。  <br><br/>对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData](Windows-callback.md#IEncryptHandler-onencryptdata)。 |

## 高级功能

| 回调 | 描述 |
| --- | --- |
| [onRecordingStateUpdate](Windows-callback#IRTCVideoEventHandler-onrecordingstateupdate) | 获取本地录制状态回调。  <br><br/>该回调由 [startFileRecording](Windows-api.md#IRTCVideo-startfilerecording) 或 [stopFileRecording](Windows-api.md#IRTCVideo-stopfilerecording) 触发。 |
| [onRecordingProgressUpdate](Windows-callback#IRTCVideoEventHandler-onrecordingprogressupdate) | 本地录制进度回调。  <br><br/>该回调由 [startFileRecording](Windows-api.md#IRTCVideo-startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。 |
| [onAudioRecordingStateUpdate](Windows-callback#IRTCVideoEventHandler-onaudiorecordingstateupdate) | 调用 [startAudioRecording](Windows-api.md#IRTCVideo-startaudiorecording) 或 [stopAudioRecording](Windows-api.md#IRTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。 |
| [OnLogReport](Windows-callback.md#IStreamingRTCEventHandler-onlogreport) | 端监控日志回调。当产生一个端监控事件时触发该回调。 |
| [OnWarning](Windows-callback.md#IStreamingRTCEventHandler-onwarning) | 当内部发生警告事件时触发该回调 |
| [OnError](Windows-callback.md#IStreamingRTCEventHandler-onerror) | 当 SDK 内部发生不可逆转错误时触发该回调。 |
| [OnP2PConnectionStateChanged](Windows-callback.md#IStreamingRTCEventHandler-onp2pconnectionstatechanged) | 串流引擎连接状态改变回调。连接状态改变时触发。 |
| [OnP2PConnectionStats](Windows-callback.md#IStreamingRTCEventHandler-onp2pconnectionstats) | P2P 通话统计信息回调。   <br><br/>串流引擎启动后，每 2s 收到一次本回调。 |
| [OnP2PLocalStreamStats](Windows-callback.md#IStreamingRTCEventHandler-onp2plocalstreamstats) | 串流引擎启动后，每隔 2s 收到此回调，了解本端发布的流在此周期内的网络质量信息。 |
| [OnP2PRemoteStreamStats](Windows-callback.md#IStreamingRTCEventHandler-onp2premotestreamstats) | 每隔 2s 收到此回调，了解远端用户发布的流在此周期内的网络质量信息。 |
| [OnP2PMessageSendResult](Windows-callback#IStreamingRTCEventHandler-onp2pmessagesendresult) | 调用 [SendP2PMessage](Windows-api.md#IStreamingRTCEngine-sendp2pmessage) 或 [SendP2PBinaryMessage](Windows-api.md#IStreamingRTCEngine-sendp2pbinarymessage) ，向远端用户发送文本或二进制消息后，消息发送方会收到本次发送的结果回调。 |
| [OnP2PMessageReceived](Windows-callback.md#IStreamingRTCEventHandler-onp2pmessagereceived) | 收到远端用户发来的文本消息时，会收到此回调。 |
| [OnP2PBinaryMessageReceived](Windows-callback.md#IStreamingRTCEventHandler-onp2pbinarymessagereceived) | 收到远端用户发来的二进制消息时，会收到此回调。 |
| [OnP2PRemoteVideoFrame](Windows-callback#IStreamingRTCEventHandler-onp2premotevideoframe) | 获取远端用户发送的视频帧。 <br><br/>关于推送视频帧，参看 [PushVideoFrame](Windows-api.md#IStreamingRTCEngine-pushvideoframe) <br><br/>关于推送已编码的视频流，参看 [PushEncodedVideoFrame](Windows-api.md#IStreamingRTCEngine-pushencodedvideoframe) <br><br/>关于编码设置，参看 [SetVideoDecoderConfig](Windows-api.md#IStreamingRTCEngine-setvideodecoderconfig) <br> |
| [OnP2PRemoteEncodedVideoFrame](Windows-callback#IStreamingRTCEventHandler-onp2premoteencodedvideoframe) | 获取远端用户解码前的视频数据。获取数据后传入自定义解码器进行解码。 <br><br/>关于推送视频帧，参看 [PushVideoFrame](Windows-api.md#IStreamingRTCEngine-pushvideoframe) <br><br/>关于推送已编码的视频流，参看 [PushEncodedVideoFrame](Windows-api.md#IStreamingRTCEngine-pushencodedvideoframe) <br><br/>关于编码设置，参看 [SetVideoDecoderConfig](Windows-api.md#IStreamingRTCEngine-setvideodecoderconfig) <br> |
| [OnP2PLocalExternalEncoderStart](Windows-callback#IStreamingRTCEventHandler-onp2plocalexternalencoderstart) | 提醒外部视频编码器开始工作。 <br><br/>关于编码设置，参看 [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) <br> |
| [OnP2PLocalExternalEncoderStop](Windows-callback#IStreamingRTCEventHandler-onp2plocalexternalencoderstop) | 提醒外部视频编码器停止工作。 <br><br/>关于编码设置，参看 [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) <br> |
| [OnP2PSuggestLocalExternalEncoderRateUpdate](Windows-callback#IStreamingRTCEventHandler-onp2psuggestlocalexternalencoderrateupdate) | 提醒外部视频编码器调整编码码率。 <br><br/>关于编码设置，参看 [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) <br> |
| [OnP2PRequestLocalExternalEncoderKeyFrame](Windows-callback#IStreamingRTCEventHandler-onp2prequestlocalexternalencoderkeyframe) | 提醒外部视频编码器发送关键帧。 <br><br/>关于编码设置，参看 [SetVideoSourceType](Windows-api.md#IStreamingRTCEngine-setvideosourcetype) <br> |
| [onTakeLocalSnapshotResult](Windows-callback#ISnapshotResultCallback-ontakelocalsnapshotresult) | 调用 [takeLocalSnapshot](Windows-api.md#IRTCVideo-takelocalsnapshot) 截取视频画面时，收到此回调。 |
| [onTakeRemoteSnapshotResult](Windows-callback#ISnapshotResultCallback-ontakeremotesnapshotresult) | 调用 [takeRemoteSnapshot](Windows-api.md#IRTCVideo-takeremotesnapshot) 截取视频画面时，收到此回调。 |

## 音乐及打分

| 回调 | 描述 |
| --- | --- |
| [onMusicListResult](Windows-callback.md#IKTVEventHandler-onmusiclistresult) | 歌曲列表回调。 |
| [onSearchMusicResult](Windows-callback.md#IKTVEventHandler-onsearchmusicresult) | 搜索歌曲结果回调。 |
| [onHotMusicResult](Windows-callback.md#IKTVEventHandler-onhotmusicresult) | 热榜歌曲结果回调。 |
| [onMusicDetailResult](Windows-callback.md#IKTVEventHandler-onmusicdetailresult) | 歌曲详细信息回调。 |
| [onDownloadSuccess](Windows-callback.md#IKTVEventHandler-ondownloadsuccess) | 下载成功回调。 |
| [onDownloadFailed](Windows-callback.md#IKTVEventHandler-ondownloadfailed) | 下载失败回调。 |
| [onDownloadMusicProgress](Windows-callback.md#IKTVEventHandler-ondownloadmusicprogress) | 歌曲文件下载进度回调。 |
| [onPlayProgress](Windows-callback.md#IKTVPlayerEventHandler-onplayprogress) | 音乐播放进度回调。 |
| [onPlayStateChange](Windows-callback.md#IKTVPlayerEventHandler-onplaystatechange) | 音乐播放状态改变回调。 |
| [onCurrentScoringInfo](Windows-callback#ISingScoringEventHandler-oncurrentscoringinfo) | 实时评分信息回调。调用 [startSingScoring](Windows-api.md#ISingScoringManager-startsingscoring) 后，会收到该回调。 |