# 方法
## 引擎管理

| 方法 | 描述 |
| --- | --- |
| [createRTCVideo:delegate:parameters:](macOS-api.md#ByteRTCVideo-creatertcvideo-delegate-parameters) | 创建引擎对象。<br/>如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。 <br/>如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。 |
| [destroyRTCVideo](macOS-api.md#ByteRTCVideo-destroyrtcvideo) | 销毁由 [createRTCVideo:delegate:parameters:](macOS-api.md#ByteRTCVideo-creatertcvideo-delegate-parameters) 所创建的引擎实例，并释放所有相关资源。<br> |
| [getSDKVersion](macOS-api.md#ByteRTCVideo-getsdkversion) | 获取 SDK 当前的版本号。 |
| [feedback:info:](macOS-api.md#ByteRTCVideo-feedback-info) | 通话结束，将用户反馈的问题上报到 RTC。 <br> |
| [getErrorDescription:](macOS-api.md#ByteRTCVideo-geterrordescription) | 获取 SDK 内各种错误码、警告码的描述文字。 |
| [setBusinessId:](macOS-api.md#ByteRTCVideo-setbusinessid) | 设置业务标识参数  <br><br/>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setRuntimeParameters:](macOS-api.md#ByteRTCVideo-setruntimeparameters) | 设置运行时的参数 |
| [setLogConfig:](macOS-api.md#ByteRTCVideo-setlogconfig) | 配置 SDK 本地日志参数，包括日志级别、存储路径、日志文件最大占用的总空间、日志文件名前缀。 |

## 房间管理

| 方法 | 描述 |
| --- | --- |
| [createRTCRoom:](macOS-api.md#ByteRTCVideo-creatertcroom) | 创建房间实例。<br><br/>调用此方法仅返回一个房间实例，你仍需调用 [joinRoom:userInfo:roomConfig:](macOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) 才能真正地创建/加入房间。<br><br/>多次调用此方法以创建多个 [ByteRTCRoom](macOS-api.md#bytertcroom) 实例。分别调用各 ByteRTCRoom 实例中的 [joinRoom:userInfo:roomConfig:](macOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) 方法，同时加入多个房间。<br><br/>多房间模式下，用户可以同时订阅各房间的音视频流。 |
| [destroy](macOS-api.md#ByteRTCRoom-destroy) | 退出并销毁调用 [createRTCRoom:](macOS-api.md#ByteRTCVideo-creatertcroom) 所创建的房间实例。 |
| [setRTCRoomDelegate:](macOS-api.md#ByteRTCRoom-setrtcroomdelegate) | 通过设置 [ByteRTCRoom](macOS-api.md#bytertcroom) 对象的事件句柄，监听此对象对应的回调事件。 |
| [joinRoom:userInfo:roomConfig:](macOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) | 加入房间。<br><br/>调用 [createRTCRoom:](macOS-api.md#ByteRTCVideo-creatertcroom) 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br> |
| [setRoomExtraInfo:value:](macOS-api.md#ByteRTCRoom-setroomextrainfo-value) | 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。 |
| [leaveRoom](macOS-api.md#ByteRTCRoom-leaveroom) | 离开房间。  <br><br/>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。 |
| [setUserVisibility:](macOS-api.md#ByteRTCRoom-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br/>默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，最多 30 人可同时上麦。更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。 |
| [updateToken:](macOS-api#ByteRTCRoom-updatetoken) | 更新 Token。<br/>收到 [onTokenWillExpire:](macOS-callback.md#ByteRTCRoomDelegate-ontokenwillexpire)，[onPublishPrivilegeTokenWillExpire:](macOS-callback.md#ByteRTCRoomDelegate-onpublishprivilegetokenwillexpire)，或 [onSubscribePrivilegeTokenWillExpire:](macOS-callback.md#ByteRTCRoomDelegate-onsubscribeprivilegetokenwillexpire) 时，你必须重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。 |

## 音频管理

| 方法 | 描述 |
| --- | --- |
| [setCaptureVolume:volume:](macOS-api.md#ByteRTCVideo-setcapturevolume-volume) | 调节音频采集音量 |
| [setPlaybackVolume:](macOS-api.md#ByteRTCVideo-setplaybackvolume) | 调节本地播放的所有远端用户音频混音后的音量，混音内容包括远端人声、音乐、音效等。<br><br/>播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume:remoteUid:playVolume:](macOS-api.md#ByteRTCVideo-setremoteaudioplaybackvolume-remoteuid-playvolume) | 调节来自指定远端用户的音频播放音量。 |
| [setRemoteRoomAudioPlaybackVolume:](macOS-api.md#ByteRTCRoom-setremoteroomaudioplaybackvolume) | 调节某个房间内所有远端用户的音频播放音量。 |
| [enableAudioPropertiesReport:](macOS-api#ByteRTCVideo-enableaudiopropertiesreport) | 启用音频信息提示。启用后，你可以收到 [rtcEngine:onLocalAudioPropertiesReport:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport)，[rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume)，和 [rtcEngine:onActiveSpeaker:uid:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid)。 |
| [startAudioCapture](macOS-api#ByteRTCVideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法开启后，本地用户会收到 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStartAudioCapture:uid:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid) 的回调。 |
| [stopAudioCapture](macOS-api#ByteRTCVideo-stopaudiocapture) | 关闭内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法，本地用户会收到 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStopAudioCapture:uid:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid) 的回调。 |
| [setAudioProfile:](macOS-api#ByteRTCVideo-setaudioprofile) | 设置音质档位。<br><br/>当所选的 [ByteRTCRoomProfile](macOS-keytype.md#bytertcroomprofile) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。 |
| [enableExternalSoundCard:](macOS-api.md#ByteRTCVideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |
| [enumerateAudioCaptureDevices](macOS-api.md#ByteRTCAudioDeviceManager-enumerateaudiocapturedevices) | 获取音频采集设备列表。 |
| [enumerateAudioPlaybackDevices](macOS-api.md#ByteRTCAudioDeviceManager-enumerateaudioplaybackdevices) | 获取当前系统内音频播放设备列表。 |
| [followSystemCaptureDevice:](macOS-api.md#ByteRTCAudioDeviceManager-followsystemcapturedevice) | 设置音频采集路由是否跟随系统。 |
| [followSystemPlaybackDevice:](macOS-api.md#ByteRTCAudioDeviceManager-followsystemplaybackdevice) | 设置音频播放路由是否跟随系统。 |
| [getAudioCaptureDevice:](macOS-api.md#ByteRTCAudioDeviceManager-getaudiocapturedevice) | 获取当前音频采集设备。 |
| [getAudioCaptureDeviceMute:](macOS-api.md#ByteRTCAudioDeviceManager-getaudiocapturedevicemute) | 获取当前音频采集设备是否静音的信息。 |
| [getAudioCaptureDeviceVolume:](macOS-api.md#ByteRTCAudioDeviceManager-getaudiocapturedevicevolume) | 获取当前音频采集设备音量 |
| [getAudioPlaybackDevice:](macOS-api.md#ByteRTCAudioDeviceManager-getaudioplaybackdevice) | 获取当前音频播放设备。 |
| [getAudioPlaybackDeviceMute:](macOS-api.md#ByteRTCAudioDeviceManager-getaudioplaybackdevicemute) | 获取当前音频播放设备是否静音的信息。 |
| [getAudioPlaybackDeviceVolume:](macOS-api.md#ByteRTCAudioDeviceManager-getaudioplaybackdevicevolume) | 获取当前音频播放设备音量 |
| [initAudioCaptureDeviceForTest:](macOS-api.md#ByteRTCAudioDeviceManager-initaudiocapturedevicefortest) | 尝试初始化音频采集设备，以检测设备不存在、权限被拒绝/禁用等异常问题。 |
| [initAudioPlaybackDeviceForTest:](macOS-api.md#ByteRTCAudioDeviceManager-initaudioplaybackdevicefortest) | 尝试初始化音频播放设备，以检测设备不存在、权限被拒绝/禁用等异常问题。 |
| [setAudioCaptureDevice:](macOS-api.md#ByteRTCAudioDeviceManager-setaudiocapturedevice) | 设置音频采集设备。 |
| [setAudioCaptureDeviceMute:](macOS-api.md#ByteRTCAudioDeviceManager-setaudiocapturedevicemute) | 设置当前音频采集设备静音状态，默认为非静音。 |
| [setAudioCaptureDeviceVolume:](macOS-api.md#ByteRTCAudioDeviceManager-setaudiocapturedevicevolume) | 设置当前音频采集设备音量 |
| [setAudioPlaybackDevice:](macOS-api.md#ByteRTCAudioDeviceManager-setaudioplaybackdevice) | 设置音频播放设备。 |
| [setAudioPlaybackDeviceMute:](macOS-api.md#ByteRTCAudioDeviceManager-setaudioplaybackdevicemute) | 设置当前音频播放设备静音状态，默认为非静音。 |
| [setAudioPlaybackDeviceVolume:](macOS-api.md#ByteRTCAudioDeviceManager-setaudioplaybackdevicevolume) | 设置当前音频播放设备音量 |
| [startAudioDeviceLoopbackTest:](macOS-api#ByteRTCAudioDeviceManager-startaudiodeviceloopbacktest) | 开始音频设备回路测试。  <br><br/>该方法测试音频采集设备和音频播放设备是否能正常工作。一旦测试开始，音频采集设备会采集本地声音并通过音频播放设备播放出来，同时会收到 [rtcEngine:onLocalAudioPropertiesReport:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport)。 |
| [startAudioDeviceRecordTest:](macOS-api.md#ByteRTCAudioDeviceManager-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br> |
| [startAudioRecordingDeviceTest:](macOS-api#ByteRTCAudioDeviceManager-startaudiorecordingdevicetest) | 启动音频采集设备测试。  <br><br/>该方法测试音频采集设备是否能正常工作。启动测试后，会收到 [rtcEngine:onLocalAudioPropertiesReport:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport) 回调上报的音量信息。 |
| [startAudioPlaybackDeviceTest:interval:](macOS-api.md#ByteRTCAudioDeviceManager-startaudioplaybackdevicetest-interval) | 启动音频播放设备测试。  <br><br/>该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。 |
| [stopAudioDeviceLoopbackTest](macOS-api.md#ByteRTCAudioDeviceManager-stopaudiodeviceloopbacktest) | 停止音频设备回路测试。 |
| [stopAudioDevicePlayTest](macOS-api.md#ByteRTCAudioDeviceManager-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest:](macOS-api.md#ByteRTCAudioDeviceManager-startaudiodevicerecordtest) 开始的音频播放设备测试。<br><br/>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |
| [stopAudioDeviceRecordAndPlayTest](macOS-api.md#ByteRTCAudioDeviceManager-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br><br/>调用 [startAudioDeviceRecordTest:](macOS-api.md#ByteRTCAudioDeviceManager-startaudiodevicerecordtest) 30s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
| [stopAudioRecordingDeviceTest](macOS-api.md#ByteRTCAudioDeviceManager-stopaudiorecordingdevicetest) | 停止音频采集设备测试。 |
| [stopAudioPlaybackDeviceTest](macOS-api.md#ByteRTCAudioDeviceManager-stopaudioplaybackdevicetest) | 停止音频播放设备测试。 |
| [getAudioDeviceManager](macOS-api.md#ByteRTCVideo-getaudiodevicemanager) | 创建音频设备管理实例 |
| [startScreenAudioCapture:](macOS-api.md#ByteRTCVideo-startscreenaudiocapture) | 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频 |
| [stopScreenAudioCapture](macOS-api.md#ByteRTCVideo-stopscreenaudiocapture) | 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。 |
| [enableAGC:](macOS-api.md#ByteRTCVideo-enableagc) | 打开/关闭 AGC 功能<br/>打开/关闭 AGC(Analog Automatic Gain Control)模拟自动增益控制功能。<br><br/>开启该功能后，SDK 会自动调节麦克风的采集音量，确保音量稳定。 |
| [startHardwareEchoDetection:](macOS-api.md#ByteRTCVideo-starthardwareechodetection) | 开启通话前回声检测 |
| [stopHardwareEchoDetection](macOS-api.md#ByteRTCVideo-stophardwareechodetection) | 停止通话前回声检测 |

## 视频管理

| 方法 | 描述 |
| --- | --- |
| [startVideoCapture](macOS-api#ByteRTCVideo-startvideocapture) | 立即开启内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStartVideoCapture:uid:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid) 的回调。 |
| [stopVideoCapture](macOS-api#ByteRTCVideo-stopvideocapture) | 立即关闭内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStopVideoCapture:uid:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid) 的回调。 |
| [setVideoCaptureConfig:](macOS-api.md#ByteRTCVideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。<br><br/>如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。 |
| [setLocalVideoCanvas:withCanvas:](macOS-api.md#ByteRTCVideo-setlocalvideocanvas-withcanvas) | 设置本地视频渲染时使用的视图，并设置渲染模式。 |
| [updateLocalVideoCanvas:withRenderMode:withBackgroundColor:](macOS-api.md#ByteRTCVideo-updatelocalvideocanvas-withrendermode-withbackgroundcolor) | 修改本地视频渲染模式和背景色。 |
| [setRemoteVideoCanvas:withCanvas:](macOS-api.md#ByteRTCVideo-setremotevideocanvas-withcanvas) | 渲染来自指定远端用户 uid 的视频流时，设置使用的视图和渲染模式。  <br><br/>如果需要解除视频的绑定视图，把 `canvas.view` 设置为空。(`canvas` 中其他参数不能为空。) |
| [enumerateVideoCaptureDevices](macOS-api.md#ByteRTCVideoDeviceManager-enumeratevideocapturedevices) | 获取视频采集设备列表。 |
| [getVideoCaptureDevice:](macOS-api.md#ByteRTCVideoDeviceManager-getvideocapturedevice) | 获取当前 SDK 正在使用的视频采集设备信息 |
| [setVideoCaptureDevice:](macOS-api.md#ByteRTCVideoDeviceManager-setvideocapturedevice) | 设置当前视频采集设备 |
| [setVideoEncoderConfig:](macOS-api.md#ByteRTCVideo-setvideoencoderconfig) | 视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [setMaxVideoEncoderConfig:](macOS-api.md#ByteRTCVideo-setmaxvideoencoderconfig) | 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br><br/>该接口支持设置一路视频流参数，设置多路参数请使用 [setVideoEncoderConfig:](macOS-api.md#ByteRTCVideo-setvideoencoderconfig)。 |
| [getVideoDeviceManager](macOS-api.md#ByteRTCVideo-getvideodevicemanager) | 创建视频设备管理实例 |

## 音视频传输

| 方法 | 描述 |
| --- | --- |
| [publishStream:](macOS-api.md#ByteRTCRoom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream:](macOS-api.md#ByteRTCRoom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [subscribeStream:mediaStreamType:](macOS-api.md#ByteRTCRoom-subscribestream-mediastreamtype) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream:mediaStreamType:](macOS-api.md#ByteRTCRoom-unsubscribestream-mediastreamtype) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreamsWithMediaStreamType:](macOS-api.md#ByteRTCRoom-subscribeallstreamswithmediastreamtype) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreamsWithMediaStreamType:](macOS-api.md#ByteRTCRoom-unsubscribeallstreamswithmediastreamtype) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br><br/>自动订阅和手动订阅的流都可以通过本方法取消订阅。 |
| [pauseAllSubscribedStream:](macOS-api.md#ByteRTCRoom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流 |
| [resumeAllSubscribedStream:](macOS-api.md#ByteRTCRoom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [requestRemoteVideoKeyFrame:](macOS-api.md#ByteRTCVideo-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [startForwardStreamToRooms:](macOS-api.md#ByteRTCRoom-startforwardstreamtorooms) | 开始跨房间转发媒体流。<br/>在调用 [joinRoom:userInfo:roomConfig:](macOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br> |
| [updateForwardStreamToRooms:](macOS-api#ByteRTCRoom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br><br/>通过 [startForwardStreamToRooms:](macOS-api#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br/>调用本方法增加或删减房间后，将在本端触发 [rtcRoom:onForwardStreamStateChanged:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。 |
| [stopForwardStreamToRooms](macOS-api.md#ByteRTCRoom-stopforwardstreamtorooms) | 停止跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms:](macOS-api.md#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。 |
| [pauseForwardStreamToAllRooms](macOS-api.md#ByteRTCRoom-pauseforwardstreamtoallrooms) | 暂停跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms:](macOS-api.md#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br/>调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](macOS-api.md#ByteRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。 |
| [resumeForwardStreamToAllRooms](macOS-api.md#ByteRTCRoom-resumeforwardstreamtoallrooms) | 恢复跨房间媒体流转发。<br/>调用 [pauseForwardStreamToAllRooms](macOS-api.md#ByteRTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。 |
| [setMultiDeviceAVSync:](macOS-api.md#ByteRTCRoom-setmultideviceavsync) | 设置发流端音画同步。  <br><br/>当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。 |
| [startPushPublicStream:withLayout:](macOS-api.md#ByteRTCVideo-startpushpublicstream-withlayout) | 发布一路公共流<br><br/>用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream) 获取和播放指定的公共流。 |
| [stopPushPublicStream:](macOS-api.md#ByteRTCVideo-stoppushpublicstream) | 停止发布当前用户发布的公共流<br><br/>关于发布公共流，查看 [startPushPublicStream:withLayout:](macOS-api.md#ByteRTCVideo-startpushpublicstream-withlayout)。 |
| [updatePublicStreamParam:withLayout:](macOS-api#ByteRTCVideo-updatepublicstreamparam-withlayout) | 更新公共流参数<br><br/>关于发布公共流，查看 [startPushPublicStream:withLayout:](macOS-api#ByteRTCVideo-startpushpublicstream-withlayout)。<br/>建议调用更新公共流前判断公共流是否已经成功启动，相关回调详见 [rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode)。 |
| [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream) | 订阅指定公共流<br><br/>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream:](macOS-api.md#ByteRTCVideo-stopplaypublicstream) | 取消订阅指定公共流<br><br/>关于订阅公共流，查看 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream)。 |
| [setPublicStreamVideoCanvas:withCanvas:](macOS-api.md#ByteRTCVideo-setpublicstreamvideocanvas-withcanvas) | 为指定公共流绑定内部渲染视图。 |
| [setPublicStreamVideoSink:withSink:withPixelFormat:](macOS-api.md#ByteRTCVideo-setpublicstreamvideosink-withsink-withpixelformat) | 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。 |
| [setPublicStreamAudioPlaybackVolume:volume:](macOS-api.md#ByteRTCVideo-setpublicstreamaudioplaybackvolume-volume) | 调节公共流的音频播放音量。 |

## 视频处理

| 方法 | 描述 |
| --- | --- |
| [setLowLightAdjusted:](macOS-api.md#ByteRTCVideo-setlowlightadjusted) | 设置视频暗光增强模式。<br/>对于光线不足、照明不均匀或背光等场景下推荐开启，可有效改善画面质量。 |
| [setLocalVideoMirrorType:](macOS-api.md#ByteRTCVideo-setlocalvideomirrortype) | 为采集到的视频流开启镜像 |
| [setRemoteVideoMirrorType:withMirrorType:](macOS-api.md#ByteRTCVideo-setremotevideomirrortype-withmirrortype) | 使用内部渲染时，为远端流开启镜像。 |
| [setVideoCaptureRotation:](macOS-api.md#ByteRTCVideo-setvideocapturerotation) | 设置本端采集的视频帧的旋转角度。<br/>当摄像头倒置或者倾斜安装时，可调用本接口进行调整。对于手机等普通设备，可调用 `setVideoRotationMode:` 实现旋转。 |
| [setVideoWatermark:withImagePath:withRtcWatermarkConfig:](macOS-api.md#ByteRTCVideo-setvideowatermark-withimagepath-withrtcwatermarkconfig) | 在指定视频流上添加水印。 |
| [clearVideoWatermark:](macOS-api.md#ByteRTCVideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [enableEffectBeauty:](macOS-api.md#ByteRTCVideo-enableeffectbeauty) | 开启/关闭基础美颜。 |
| [setBeautyIntensity:withIntensity:](macOS-api.md#ByteRTCVideo-setbeautyintensity-withintensity) | 调整基础美颜强度。 |
| [getVideoEffectInterface](macOS-api.md#ByteRTCVideo-getvideoeffectinterface) | 获取视频特效接口。 |
| [getAuthMessage:](macOS-api.md#ByteRTCVideoEffect-getauthmessage) | 从特效 SDK 获取授权消息，用于获取在线许可证。 |
| [initCVResource:withAlgoModelDir:](macOS-api.md#ByteRTCVideoEffect-initcvresource-withalgomodeldir) | 检查视频特效证书，设置算法模型路径，并初始化特效模块。 |
| [enableVideoEffect](macOS-api.md#ByteRTCVideoEffect-enablevideoeffect) | 开启高级美颜、滤镜等视频特效。 |
| [disableVideoEffect](macOS-api.md#ByteRTCVideoEffect-disablevideoeffect) | 关闭视频特效。 |
| [setEffectNodes:](macOS-api.md#ByteRTCVideoEffect-seteffectnodes) | 设置视频特效素材包。 |
| [updateEffectNode:key:value:](macOS-api.md#ByteRTCVideoEffect-updateeffectnode-key-value) | 设置特效强度。 |
| [setColorFilter:](macOS-api.md#ByteRTCVideoEffect-setcolorfilter) | 设置颜色滤镜。 |
| [setColorFilterIntensity:](macOS-api.md#ByteRTCVideoEffect-setcolorfilterintensity) | 设置已启用颜色滤镜的强度。 |
| [enableVirtualBackground:withSource:](macOS-api.md#ByteRTCVideoEffect-enablevirtualbackground-withsource) | 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。 |
| [disableVirtualBackground](macOS-api.md#ByteRTCVideoEffect-disablevirtualbackground) | 关闭虚拟背景。 |
| [enableFaceDetection:withInterval:withModelPath:](macOS-api#ByteRTCVideoEffect-enablefacedetection-withinterval-withmodelpath) | 开启人脸识别功能，并设置人脸检测结果回调观察者。<br/>此观察者后，你会周期性收到 [onFaceDetectResult:](macOS-callback.md#ByteRTCFaceDetectionObserver-onfacedetectresult) 回调。 |
| [disableFaceDetection](macOS-api.md#ByteRTCVideoEffect-disablefacedetection) | 关闭人脸识别功能。 |
| [setVideoDigitalZoomConfig:size:](macOS-api.md#ByteRTCVideo-setvideodigitalzoomconfig-size) | 设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。 |
| [setVideoDigitalZoomControl:](macOS-api.md#ByteRTCVideo-setvideodigitalzoomcontrol) | 控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。 |
| [startVideoDigitalZoomControl:](macOS-api.md#ByteRTCVideo-startvideodigitalzoomcontrol) | 开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。 |
| [stopVideoDigitalZoomControl](macOS-api.md#ByteRTCVideo-stopvideodigitalzoomcontrol) | 停止本地摄像头持续数码变焦。 |

## 音频处理

| 方法 | 描述 |
| --- | --- |
| [setVoiceChangerType:](macOS-api.md#ByteRTCVideo-setvoicechangertype) | 设置变声特效类型 |
| [setVoiceReverbType:](macOS-api.md#ByteRTCVideo-setvoicereverbtype) | 设置混响特效类型 |
| [setLocalVoicePitch:](macOS-api.md#ByteRTCVideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |
| [setLocalVoiceEqualization:](macOS-api.md#ByteRTCVideo-setlocalvoiceequalization) | 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [setLocalVoiceReverbParam:](macOS-api.md#ByteRTCVideo-setlocalvoicereverbparam) | 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [enableLocalVoiceReverb:](macOS-api.md#ByteRTCVideo-enablelocalvoicereverb) | 开启本地音效混响效果 |

## 自定义流处理

| 方法 | 描述 |
| --- | --- |
| [setVideoSourceType:WithStreamIndex:](macOS-api.md#ByteRTCVideo-setvideosourcetype-withstreamindex) | 设置向 SDK 输入的视频源，包括屏幕流<br/>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br> |
| [pushExternalVideoFrame:](macOS-api.md#ByteRTCVideo-pushexternalvideoframe) | 推送外部视频帧。 |
| [setLocalVideoRender:withSink:withLocalRenderConfig:](macOS-api.md#ByteRTCVideo-setlocalvideorender-withsink-withlocalrenderconfig) | 将本地视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。 |
| [setRemoteVideoRender:withSink:withRemoteRenderConfig:](macOS-api.md#ByteRTCVideo-setremotevideorender-withsink-withremoterenderconfig) | 将远端视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。 |
| [registerRemoteEncodedVideoFrameObserver:](macOS-api#ByteRTCVideo-registerremoteencodedvideoframeobserver) | 注册远端编码后视频数据回调。  <br><br/>完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame:withEncodedVideoFrame:](macOS-callback.md#ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe) 回调 |
| [setVideoDecoderConfig:withVideoDecoderConfig:](macOS-api.md#ByteRTCVideo-setvideodecoderconfig-withvideodecoderconfig) | 在订阅远端视频流之前，设置远端视频数据解码方式 |
| [setAudioSourceType:](macOS-api.md#ByteRTCVideo-setaudiosourcetype) | 切换音频采集方式 |
| [setAudioRenderType:](macOS-api.md#ByteRTCVideo-setaudiorendertype) | 切换音频渲染方式 |
| [pushExternalAudioFrame:](macOS-api.md#ByteRTCVideo-pushexternalaudioframe) | 推送自定义采集的音频数据到 RTC SDK。 |
| [pullExternalAudioFrame:](macOS-api.md#ByteRTCVideo-pullexternalaudioframe) | 拉取下行音频数据用于自定义音频渲染。<br/>调用该方法后，SDK 会主动拉取待播放的音频数据，包括远端已解码和混音后的音频数据，用于外部播放。 |
| [registerLocalVideoProcessor:withConfig:](macOS-api#ByteRTCVideo-registerlocalvideoprocessor-withconfig) | 设置自定义视频前处理器。<br><br/>使用这个视频前处理器，你能够调用 [processVideoFrame:](macOS-callback.md#ByteRTCVideoProcessorDelegate-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。 |
| [registerAudioProcessor:](macOS-api.md#ByteRTCVideo-registeraudioprocessor) | 注册自定义音频处理器。<br><br/>注册完成后，你可以调用 [enableAudioProcessor:audioFormat:](macOS-api.md#ByteRTCVideo-enableaudioprocessor-audioformat)，对本地采集到的音频进行处理，RTC SDK 将对处理后的音频进行编码和发送。也可以对接收到的远端音频进行自定义处理，RTC SDK 将对处理后的音频进行渲染。 |
| [enableAudioProcessor:audioFormat:](macOS-api.md#ByteRTCVideo-enableaudioprocessor-audioformat) | 设置并开启指定的音频帧回调，进行自定义处理。 |
| [disableAudioProcessor:](macOS-api.md#ByteRTCVideo-disableaudioprocessor) | 关闭自定义音频处理。 |
| [registerAudioFrameObserver:](macOS-api.md#ByteRTCVideo-registeraudioframeobserver) | 注册音频数据回调观察者。  <br> |
| [enableAudioFrameCallback:format:](macOS-api.md#ByteRTCVideo-enableaudioframecallback-format) | 设置并开启指定的音频数据帧回调 |
| [disableAudioFrameCallback:](macOS-api.md#ByteRTCVideo-disableaudioframecallback) | 关闭音频回调 |
| [registerLocalEncodedVideoFrameObserver:](macOS-api#ByteRTCVideo-registerlocalencodedvideoframeobserver) | 注册本地视频帧监测器。  <br><br/>无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame:Frame:](macOS-callback.md#ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame) 回调给用户 |
| [setExternalVideoEncoderEventHandler:](macOS-api.md#ByteRTCVideo-setexternalvideoencodereventhandler) | 注册自定义编码帧推送事件回调 |
| [pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:](macOS-api.md#ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe) | 推送自定义编码后的视频流 |

## 网络管理

| 方法 | 描述 |
| --- | --- |
| [enableSimulcastMode:](macOS-api.md#ByteRTCVideo-enablesimulcastmode) | 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。 |
| [setRemoteVideoConfig:remoteVideoConfig:](macOS-api.md#ByteRTCRoom-setremotevideoconfig-remotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [setPublishFallbackOption:](macOS-api.md#ByteRTCVideo-setpublishfallbackoption) | 设置发布的音视频流的回退选项。  <br><br/>你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。 |
| [setSubscribeFallbackOption:](macOS-api.md#ByteRTCVideo-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。 <br><br/>你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority:InRoomId:uid:](macOS-api.md#ByteRTCVideo-setremoteuserpriority-inroomid-uid) | 设置用户优先级。 |
| [startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:](macOS-api.md#ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth) | 开始通话前网络探测 |
| [stopNetworkDetection](macOS-api.md#ByteRTCVideo-stopnetworkdetection) | 停止通话前网络探测 |
| [startEchoTest:playDelay:](macOS-api.md#ByteRTCVideo-startechotest-playdelay) | 开启音视频回路测试。  <br><br/>在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br><br/>开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。 |
| [stopEchoTest](macOS-api.md#ByteRTCVideo-stopechotest) | 停止音视频回路测试。  <br><br/>调用 [startEchoTest:playDelay:](macOS-api.md#ByteRTCVideo-startechotest-playdelay) 开启音视频回路检测后，你必须调用该方法停止检测。 |
| [getNetworkTimeInfo](macOS-api.md#ByteRTCVideo-getnetworktimeinfo) | 通过 NTP 协议，获取网络时间。 |

## 消息

| 方法 | 描述 |
| --- | --- |
| [sendRoomMessage:](macOS-api.md#ByteRTCRoom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [sendRoomBinaryMessage:](macOS-api.md#ByteRTCRoom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [sendUserMessage:message:config:](macOS-api.md#ByteRTCRoom-sendusermessage-message-config) | 给房间内指定的用户发送点对点文本消息（P2P）。 |
| [sendUserBinaryMessage:message:config:](macOS-api.md#ByteRTCRoom-senduserbinarymessage-message-config) | 给房间内指定的用户发送点对点二进制消息（P2P）。 |
| [login:uid:](macOS-api.md#ByteRTCVideo-login-uid) | 登录 RTS 服务器。<br>必须先登录，才能调用 [sendUserMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) 和 [sendServerMessage:](macOS-api.md#ByteRTCVideo-sendservermessage) 发送房间外点对点消息和向应用服务器发送消息 <br><br/>在调用本接口登录后，如果想要登出，需要调用 [logout](macOS-api.md#ByteRTCVideo-logout) |
| [logout](macOS-api.md#ByteRTCVideo-logout) | 登出 RTS 服务器。<br>调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken:](macOS-api#ByteRTCVideo-updatelogintoken) | 更新用户用于登录的 Token  <br><br/>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br><br/>调用 [login:uid:](macOS-api#ByteRTCVideo-login-uid) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [rtcEngine:onLoginResult:errorCode:elapsed:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed) 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。 |
| [setServerParams:url:](macOS-api.md#ByteRTCVideo-setserverparams-url) | 设置应用服务器参数  <br><br/>客户端调用 [sendServerMessage:](macOS-api.md#ByteRTCVideo-sendservermessage) 或 [sendServerBinaryMessage:](macOS-api.md#ByteRTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。 |
| [getPeerOnlineStatus:](macOS-api.md#ByteRTCVideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [sendUserMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) | 给房间外指定的用户发送二进制消息（P2P） |
| [sendServerMessage:](macOS-api.md#ByteRTCVideo-sendservermessage) | 客户端给应用服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage:](macOS-api.md#ByteRTCVideo-sendserverbinarymessage) | 客户端给应用服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo:config:](macOS-api#ByteRTCVideo-sendstreamsyncinfo-config) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [rtcEngine:onStreamSyncInfoReceived:streamType:data:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data) 回调。 |
| [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](macOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) | 通过视频帧发送 SEI 数据。<br/>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |

## CDN 推流

| 方法 | 描述 |
| --- | --- |
| [startPushMixedStreamToCDN:mixedConfig:observer:](macOS-api.md#ByteRTCVideo-startpushmixedstreamtocdn-mixedconfig-observer) | 新增合流转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br><br/>同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。 |
| [updatePushMixedStreamToCDN:mixedConfig:](macOS-api#ByteRTCVideo-updatepushmixedstreamtocdn-mixedconfig) | 更新合流转推直播参数，会收到 [onMixingEvent:taskId:error:mixType:](macOS-callback.md#ByteRTCMixedStreamObserver-onmixingevent-taskid-error-mixtype) 回调。  <br><br/>开启转推直播功能后，你可以使用此方法更新合流转推功能配置参数。 |
| [startPushSingleStreamToCDN:singleStream:observer:](macOS-api.md#ByteRTCVideo-startpushsinglestreamtocdn-singlestream-observer) | 新增单流转推直播任务。 |
| [stopPushStreamToCDN:](macOS-api.md#ByteRTCVideo-stoppushstreamtocdn) | 停止转推直播。<br><br/>该方法可用于停止单流转推直播或停止合流转推直播，通过 taskId 区分需要停止的任务。 |

## 混音

| 方法 | 描述 |
| --- | --- |
| [getAudioEffectPlayer](macOS-api.md#ByteRTCVideo-getaudioeffectplayer) | 创建音效播放器实例。 |
| [start:filePath:config:](macOS-api.md#ByteRTCAudioEffectPlayer-start-filepath-config) | 开始播放音效文件。<br><br/>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个音效文件，实现音效叠加。 |
| [preload:filePath:](macOS-api.md#ByteRTCAudioEffectPlayer-preload-filepath) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [setPosition:position:](macOS-api.md#ByteRTCAudioEffectPlayer-setposition-position) | 设置音效文件的起始播放位置。 |
| [setVolume:volume:](macOS-api.md#ByteRTCAudioEffectPlayer-setvolume-volume) | 调节指定音效的音量大小，包括音效文件和 PCM 音频。 |
| [open:config:](macOS-api.md#ByteRTCMediaPlayer-open-config) | 打开音乐文件。<br/>一个播放器实例仅能够同时打开一个音乐文件。如果需要同时打开多个音乐文件，请创建多个音乐播放器实例。<br/>要播放 PCM 格式的音频数据，参看 [openWithCustomSource:config:](macOS-api.md#ByteRTCMediaPlayer-openwithcustomsource-config)。`openWithCustomSource` 和此 API 互斥。 |
| [openWithCustomSource:config:](macOS-api.md#ByteRTCMediaPlayer-openwithcustomsource-config) | 启动音频裸数据混音。<br/>要播放音乐文件，参看 [open:config:](macOS-api.md#ByteRTCMediaPlayer-open-config)。`open` 与此 API 互斥。 |
| [setVolume:type:](macOS-api.md#ByteRTCMediaPlayer-setvolume-type) | 调节指定混音的音量大小，包括音乐文件混音和 PCM 混音。 |

## 屏幕分享

| 方法 | 描述 |
| --- | --- |
| [publishScreen:](macOS-api.md#ByteRTCRoom-publishscreen) | 在当前所在房间内发布本地屏幕共享音视频流 |
| [unpublishScreen:](macOS-api.md#ByteRTCRoom-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [setScreenAudioSourceType:](macOS-api.md#ByteRTCVideo-setscreenaudiosourcetype) | 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集） |
| [setScreenAudioStreamIndex:](macOS-api.md#ByteRTCVideo-setscreenaudiostreamindex) | 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式 |
| [setScreenVideoEncoderConfig:](macOS-api.md#ByteRTCVideo-setscreenvideoencoderconfig) | 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [setScreenAudioChannel:](macOS-api.md#ByteRTCVideo-setscreenaudiochannel) | 在屏幕共享时，设置屏幕音频流的声道数 |
| [pushScreenAudioFrame:](macOS-api.md#ByteRTCVideo-pushscreenaudioframe) | 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。 |
| [setOriginalScreenVideoInfo:withOriginalCaptureHeight:](macOS-api.md#ByteRTCVideo-setoriginalscreenvideoinfo-withoriginalcaptureheight) | 外部采集时，当屏幕或待采集窗口大小发生改变，为了使 RTC 更好地决策合适的帧率和分辨率积，调用此接口设置改变前的分辨率。 |
| [pushScreenVideoFrame:time:rotation:](macOS-api.md#ByteRTCVideo-pushscreenvideoframe-time-rotation) | 推送外部屏幕采集帧 |
| [subscribeScreen:mediaStreamType:](macOS-api.md#ByteRTCRoom-subscribescreen-mediastreamtype) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen:mediaStreamType:](macOS-api.md#ByteRTCRoom-unsubscribescreen-mediastreamtype) | 取消订阅房间内指定的远端屏幕共享音视频流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |

## 安全与加密

| 方法 | 描述 |
| --- | --- |
| [startCloudProxy:](macOS-api.md#ByteRTCVideo-startcloudproxy) | 开启云代理 |
| [setCustomizeEncryptHandler:](macOS-api.md#ByteRTCVideo-setcustomizeencrypthandler) | 设置自定义加密和解密方式。 |
| [setEncryptInfo:key:](macOS-api.md#ByteRTCVideo-setencryptinfo-key) | 设置传输时使用内置加密的方式。 |
| [setLocalProxy:](macOS-api.md#ByteRTCVideo-setlocalproxy) | 设置本地代理。 |

## 高级功能

| 方法 | 描述 |
| --- | --- |
| [startFileRecording:withRecordingConfig:type:](macOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) | 该方法将通话过程中的音视频数据录制到本地的文件中。 |
| [stopFileRecording:](macOS-api.md#ByteRTCVideo-stopfilerecording) | 停止本地录制 |
| [startAudioRecording:](macOS-api.md#ByteRTCVideo-startaudiorecording) | 开启录制语音通话，生成本地文件。<br><br/>在进房前后开启录制，如果未打开麦克风采集，录制任务正常进行，只是不会将数据写入生成的本地文件；只有调用 [startAudioCapture](macOS-api.md#ByteRTCVideo-startaudiocapture) 接口打开麦克风采集后，才会将录制数据写入本地文件。 |
| [stopAudioRecording](macOS-api.md#ByteRTCVideo-stopaudiorecording) | 停止音频文件录制 |
| [setEarMonitorMode:](macOS-api.md#ByteRTCVideo-setearmonitormode) | 开启/关闭耳返功能。 |
| [setEarMonitorVolume:](macOS-api.md#ByteRTCVideo-setearmonitorvolume) | 设置耳返的音量。 |
| [getSpatialAudio](macOS-api.md#ByteRTCRoom-getspatialaudio) | 获取空间音频接口实例。 |
| [disableRemoteOrientation](macOS-api.md#ByteRTCSpatialAudio-disableremoteorientation) | 关闭本地用户朝向对本地用户发声效果的影响。<br><br/>调用此接口后，房间内的其他用户收听本地发声时，声源都在收听者正面。 |
| [getRangeAudio](macOS-api.md#ByteRTCRoom-getrangeaudio) | 获取范围语音接口实例。 |
| [getScreenCaptureSourceList](macOS-api.md#ByteRTCVideo-getscreencapturesourcelist) | 获取共享对象(应用窗口和桌面)列表。 |
| [getThumbnail:sourceId:maxWidth:maxHeight:](macOS-api.md#ByteRTCVideo-getthumbnail-sourceid-maxwidth-maxheight) | 获取屏幕采集对象缩略图 |
| [getWindowAppIcon:width:height:](macOS-api.md#ByteRTCVideo-getwindowappicon-width-height) | 获取应用窗体所属应用的图标。 |
| [startScreenVideoCapture:captureParameters:](macOS-api.md#ByteRTCVideo-startscreenvideocapture-captureparameters) | 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，或应用窗口中显示的内容。<br> |
| [stopScreenVideoCapture](macOS-api.md#ByteRTCVideo-stopscreenvideocapture) | 停止屏幕视频流采集。 |
| [updateScreenCaptureFilterConfig:](macOS-api.md#ByteRTCVideo-updatescreencapturefilterconfig) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。 |
| [updateScreenCaptureHighlightConfig:](macOS-api.md#ByteRTCVideo-updatescreencapturehighlightconfig) | 内部屏幕流采集时，更新边框高亮设置。默认展示边框。 |
| [updateScreenCaptureMouseCursor:](macOS-api.md#ByteRTCVideo-updatescreencapturemousecursor) | 内部屏幕流采集时，更新对鼠标的处理设置。默认采集鼠标。 |
| [updateScreenCaptureRegion:](macOS-api.md#ByteRTCVideo-updatescreencaptureregion) | 内部屏幕流采集时，更新采集区域。 |
| [takeLocalSnapshot:callback:](macOS-api.md#ByteRTCVideo-takelocalsnapshot-callback) | 截取本地视频画面 |
| [takeRemoteSnapshot:callback:](macOS-api.md#ByteRTCVideo-takeremotesnapshot-callback) | 截取远端视频画面 |
| [setAnsMode:](macOS-api.md#ByteRTCVideo-setansmode) | 支持根据业务场景，设置通话中的音频降噪模式。 |
| [updateSelfPosition:](macOS-api.md#ByteRTCSpatialAudio-updateselfposition) | 设置本地用户在自建空间直角坐标系中的收听坐标和收听朝向，以实现本地用户预期的空间音频收听效果。 |
| [updateRemotePosition:positionInfo:](macOS-api.md#ByteRTCSpatialAudio-updateremoteposition-positioninfo) | 设置房间内某一远端用户在本地用户自建的空间音频坐标系中的发声位置和发声朝向，以实现本地用户预期的空间音频收听效果。 |
| [removeRemotePosition:](macOS-api.md#ByteRTCSpatialAudio-removeremoteposition) | 移除调用 [updateRemotePosition:positionInfo:](macOS-api.md#ByteRTCSpatialAudio-updateremoteposition-positioninfo) 为某一远端用户设置的空间音频效果。 |
| [removeAllRemotePosition](macOS-api.md#ByteRTCSpatialAudio-removeallremoteposition) | 移除调用 [updateRemotePosition:positionInfo:](macOS-api.md#ByteRTCSpatialAudio-updateremoteposition-positioninfo) 为所有远端用户设置的空间音频效果。 |

## 字幕翻译服务

| 方法 | 描述 |
| --- | --- |
| [startSubtitle:](macOS-api#ByteRTCRoom-startsubtitle) | 识别或翻译房间内所有用户的语音，形成字幕。<br><br/>调用该方法时，可以在 [ByteRTCSubtitleMode](macOS-keytype#bytertcsubtitlemode) 中选择语音识别或翻译模式。如果选择识别模式，语音识别文本会通过 [rtcRoom:onSubtitleMessageReceived:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived) 事件回调给你；<br><br/>如果选择翻译模式，你会同时收到两个 [rtcRoom:onSubtitleMessageReceived:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived) 回调，分别包含字幕原文及字幕译文。<br><br/>调用该方法后，用户会收到 [rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage) 回调，通知字幕是否开启。 |
| [stopSubtitle](macOS-api#ByteRTCRoom-stopsubtitle) | 关闭字幕。 <br><br/>调用该方法后，用户会收到 [rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage)  回调，通知字幕是否关闭。 |

## 在线 KTV

| 方法 | 描述 |
| --- | --- |
| [getSingScoringManager](macOS-api.md#ByteRTCVideo-getsingscoringmanager) | 创建 K 歌评分管理接口。 |
| [initSingScoring:singScoringToken:delegate:](macOS-api.md#ByteRTCSingScoringManager-initsingscoring-singscoringtoken-delegate) | 初始化 K 歌评分。 |
| [setSingScoringConfig:](macOS-api.md#ByteRTCSingScoringManager-setsingscoringconfig) | 设置 K 歌评分参数。 |
| [getStandardPitchInfo:](macOS-api.md#ByteRTCSingScoringManager-getstandardpitchinfo) | 获取标准音高数据。 |
| [startSingScoring:scoringInfoInterval:](macOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) | 开始 K 歌评分。 |
| [stopSingScoring](macOS-api.md#ByteRTCSingScoringManager-stopsingscoring) | 停止 K 歌评分。 |
| [getLastSentenceScore](macOS-api.md#ByteRTCSingScoringManager-getlastsentencescore) | 获取上一句的演唱评分。调用 [startSingScoring:scoringInfoInterval:](macOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 开始评分后可以调用该接口。 |
| [getTotalScore](macOS-api.md#ByteRTCSingScoringManager-gettotalscore) | 获取当前演唱总分。调用 [startSingScoring:scoringInfoInterval:](macOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 开始评分后可以调用该接口。 |
| [getAverageScore](macOS-api.md#ByteRTCSingScoringManager-getaveragescore) | 获取当前演唱歌曲的平均分。 |
| [setAudioAlignmentProperty:withMode:](macOS-api.md#ByteRTCVideo-setaudioalignmentproperty-withmode) | 在听众端，设置订阅的所有远端音频流精准对齐后播放。 |

# 回调
## 引擎管理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onWarning:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onwarning) | 发生警告回调。  <br><br/>SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。 |
| [rtcEngine:onError:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onerror) | 发生错误回调。<br><br/>SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。<br><br/>你可能需要干预. |
| [onTokenWillExpire:](macOS-callback#ByteRTCRoomDelegate-ontokenwillexpire) | 当 SDK 检测到 Token 的进房权限将在 30 秒内过期时，触发该回调。<br><br/>收到该回调后，你需调用 [updateToken:](macOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 进房权限。 |
| [onPublishPrivilegeTokenWillExpire:](macOS-callback#ByteRTCRoomDelegate-onpublishprivilegetokenwillexpire) | Token 发布权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken:](macOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 发布权限。 |
| [onSubscribePrivilegeTokenWillExpire:](macOS-callback#ByteRTCRoomDelegate-onsubscribeprivilegetokenwillexpire) | Token 订阅权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken:](macOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 订阅权限有效期。 |

## 房间管理

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) | 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。 |
| [rtcEngine:onCreateRoomStateChanged:errorCode:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode) | 创建房间失败回调。 |
| [rtcRoom:onLeaveRoom:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onleaveroom) | 离开房间成功回调。  <br><br/>用户调用 [leaveRoom](macOS-api.md#ByteRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br> |
| [rtcRoom:onUserJoined:elapsed:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) | 远端可见用户加入房间，或房内不可见用户切换为可见的回调。<br><br/>1. 远端用户调用 [setUserVisibility:](macOS-api.md#ByteRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br><br/>2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br><br/>3. 房间内隐身远端用户调用 [setUserVisibility:](macOS-api.md#ByteRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br><br/>4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br> |
| [rtcRoom:onUserLeave:reason:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) | 远端用户离开房间，或切至不可见时，本地用户会收到此事件 |
| [rtcRoom:onUserVisibilityChanged:errorCode:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onuservisibilitychanged-errorcode) | 用户调用 [setUserVisibility:](macOS-api.md#ByteRTCRoom-setuservisibility) 设置用户可见性的回调。 |
| [rtcRoom:onRoomStats:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstats) | 房间内通话统计信息回调。   <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |
| [rtcRoom:onRoomStats:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstats) | 房间内通话统计信息回调。   <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |
| [rtcRoom:onSetRoomExtraInfoResult:error:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onsetroomextrainforesult-error) | 调用 [setRoomExtraInfo:value:](macOS-api.md#ByteRTCRoom-setroomextrainfo-value) 结果回调。 |
| [rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onroomextrainfoupdate-value-lastupdateuserid-lastupdatetimems) | 接收到房间附加信息的回调。<br><br/>房间内其他用户调用 [setRoomExtraInfo:value:](macOS-api.md#ByteRTCRoom-setroomextrainfo-value) 设置房间附加信息，收到此回调。<br><br/>另外用户加入房间成功后会收到这个房间全量附加信息 |

## 音频管理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning) | 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。 |
| [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) | 音频设备状态回调。提示音频采集、音频播放等设备的状态。 |
| [rtcEngine:onLocalAudioPropertiesReport:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport:](macOS-api.md#ByteRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br><br/>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。 |
| [rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume) | 远端用户进房后，本地调用 [enableAudioPropertiesReport:](macOS-api.md#ByteRTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。<br><br/>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [rtcEngine:onActiveSpeaker:uid:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid) | 调用 [enableAudioPropertiesReport:](macOS-api.md#ByteRTCVideo-enableaudiopropertiesreport)  后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [rtcEngine:onUserStartAudioCapture:uid:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid) | 房间内的可见用户调用 [startAudioCapture](macOS-api.md#ByteRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。 |
| [rtcEngine:onUserStopAudioCapture:uid:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid) | 房间内的可见用户调用 [stopAudioCapture](macOS-api.md#ByteRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。 |
| [rtcEngine:onStreamSyncInfoReceived:streamType:data:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data) | 音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo:config:](macOS-api.md#ByteRTCVideo-sendstreamsyncinfo-config) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br> |
| [rtcRoom:onAudioStreamBanned:isBanned:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onaudiostreambanned-isbanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [rtcEngine:onAudioPlaybackDeviceTestVolume:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [rtcEngine:onAudioDeviceVolumeChanged:volume:muted:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicevolumechanged-volume-muted) | 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。 |
| [rtcEngine:onHardwareEchoDetectionResult:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onhardwareechodetectionresult) | 通话前回声检测结果回调。 |
| [rtcEngine:onLocalAudioStateChanged:error:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalaudiostatechanged-error) | 本地音频流的状态发生改变时，收到此回调。 |

## 视频管理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onUserStartVideoCapture:uid:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid) | 房间内的可见用户调用 [startVideoCapture](macOS-api.md#ByteRTCVideo-startvideocapture) 开启内部视频采集时，房间中其他用户会收到此回调。 |
| [rtcEngine:onUserStopVideoCapture:uid:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid) | 房间内的可见用户调用 [stopVideoCapture](macOS-api.md#ByteRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。<br><br/>若发布视频数据前未开启采集，房间内所有可见用户会收到此回调。 |
| [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) | 视频设备状态发生改变回调。当设备的视频状态发生改变时，SDK 会触发该回调，提示摄像头视频采集、屏幕视频采集等设备的状态。 |
| [rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicewarning-devicetype-devicewarning) | 视频设备警告回调。视频设备包括视频采集设备。 |
| [onFaceDetectResult:](macOS-callback.md#ByteRTCFaceDetectionObserver-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。 <br><br/>调用 [enableFaceDetection:withInterval:withModelPath:](macOS-api#ByteRTCVideoEffect-enablefacedetection-withinterval-withmodelpath) 注册了 [ByteRTCFaceDetectionObserver](macOS-callback.md#bytertcfacedetectionobserver) ，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |
| [rtcEngine:onLocalVideoStateChanged:withStreamState:withStreamError:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalvideostatechanged-withstreamstate-withstreamerror) | 本地视频流的状态发生改变时，收到该事件。 |

## 音视频传输

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [rtcRoom:onAVSyncStateChange:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onavsyncstatechange) | 发布端调用 [setMultiDeviceAVSync:](macOS-api.md#ByteRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。 |
| [rtcEngine:onAudioFrameSendStateChanged:rtcUser:state:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudioframesendstatechanged-rtcuser-state) | 本地音频首帧发送状态发生改变时，收到此回调。 |
| [rtcEngine:onVideoFrameSendStateChanged:rtcUser:state:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideoframesendstatechanged-rtcuser-state) | 本地视频首帧发送状态发生改变时，收到此回调。 |
| [rtcEngine:onAudioFramePlayStateChanged:rtcUser:state:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudioframeplaystatechanged-rtcuser-state) | 音频首帧播放状态发生改变时，收到此回调。 |
| [rtcEngine:onVideoFramePlayStateChanged:rtcUser:state:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideoframeplaystatechanged-rtcuser-state) | 视频首帧播放状态发生改变时，收到此回调。 |
| [rtcRoom:onUserPublishStream:type:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) | 房间内新增远端摄像头/麦克风采集的媒体流的回调。 |
| [rtcRoom:onUserUnpublishStream:type:reason:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [rtcRoom:onForwardStreamStateChanged:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [rtcRoom:onForwardStreamEvent:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [rtcEngine:onSysStats:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onsysstats) | 报告当前设备 cpu 与 memory 使用率，每 2s 触发一次。 |
| [rtcRoom:onLocalStreamStats:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onlocalstreamstats) | 本地流数据统计以及网络质量回调。  <br><br/>本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br><br/>统计信息通过 [ByteRTCLocalStreamStats](macOS-keytype.md#bytertclocalstreamstats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [rtcRoom:onRemoteStreamStats:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onremotestreamstats) | 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br><br/>本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [rtcRoom:onNetworkQuality:remoteQualities:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onnetworkquality-remotequalities) | 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。 |
| [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) | 关于订阅媒体流状态改变的回调 |
| [rtcEngine:onRemoteAudioStateChanged:state:reason:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremoteaudiostatechanged-state-reason) | 订阅的远端音频流状态发生改变时，收到此回调。 |
| [rtcEngine:onFirstLocalAudioFrame:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstlocalaudioframe) | 发布音频流时，采集到第一帧音频帧，收到该回调。 |
| [rtcEngine:onFirstRemoteAudioFrame:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe) | 当收到远端流的第一帧音频的时候上报该事件 |
| [rtcEngine:onRemoteVideoStateChanged:withVideoState:withVideoStateReason:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremotevideostatechanged-withvideostate-withvideostatereason) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstlocalvideoframecaptured-withframeinfo) | 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。 |
| [rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframerendered-withframeinfo) | SDK 内部渲染成功远端视频流首帧后，收到此回调。 |
| [rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo) | 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [rtcEngine:onLocalVideoSizeChanged:withFrameInfo:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalvideosizechanged-withframeinfo) | 本地视频大小或旋转信息发生改变时，收到此回调。 |
| [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [rtcRoom:onVideoStreamBanned:isBanned:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onvideostreambanned-isbanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode) | 公共流发布结果回调。<br><br/>调用 [startPushPublicStream:withLayout:](macOS-api.md#ByteRTCVideo-startpushpublicstream-withlayout) <br><br/>接口或直接在服务端启动推公共流功能后，你会通过此回调收到启动结果和推流过程中的错误。 |
| [rtcEngine:onPlayPublicStreamResult:errorCode:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode) | 订阅公共流的结果回调  <br><br/>调用 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream) 接口拉公共流后，你会通过此回调收到启动结果和拉流过程中的错误。 |
| [rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage-andsourcetype) | 回调公共流中包含的 SEI 信息。<br/>调用 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo) | 公共流的首帧视频解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream)。 |
| [rtcEngine:onFirstPublicStreamAudioFrame:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream:](macOS-api.md#ByteRTCVideo-startplaypublicstream)。 |

## 自定义流处理

| 回调 | 描述 |
| --- | --- |
| [onStart:](macOS-callback#ByteRTCExternalVideoEncoderEventHandler-onstart) | 提示自定义编码帧可以开始推送的回调。  <br><br/>收到该回调后，你即可调用 [pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:](macOS-api.md#ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe) 向 SDK 推送自定义编码视频帧 |
| [onStop:](macOS-callback.md#ByteRTCExternalVideoEncoderEventHandler-onstop) | 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧 |
| [onRateUpdate:withVideoIndex:withFps:withBitRate:](macOS-callback.md#ByteRTCExternalVideoEncoderEventHandler-onrateupdate-withvideoindex-withfps-withbitrate) | 当自定义编码流的帧率或码率发生变化时，触发该回调 |
| [onRequestKeyFrame:withVideoIndex:](macOS-callback.md#ByteRTCExternalVideoEncoderEventHandler-onrequestkeyframe-withvideoindex) | 提示流发布端需重新生成关键帧的回调 |
| [onActiveVideoLayer:withVideoIndex:withActive:](macOS-callback.md#ByteRTCExternalVideoEncoderEventHandler-onactivevideolayer-withvideoindex-withactive) | 作为自定义编码视频流的发送端，你会在视频流可发送状态发生变化时，收到此回调。<br/>你可以根据此回调的提示，仅对可发送的视频流进行编码，以降低本端视频编码性能消耗。此回调会根据多个因素综合判断触发，包括：本端设备性能和本端网络性能，以及按需订阅场景下，远端用户是否订阅。 |
| [onLocalEncodedVideoFrame:Frame:](macOS-callback#ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame) | 调用 [registerLocalEncodedVideoFrameObserver:](macOS-api.md#ByteRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。 |
| [onRemoteEncodedVideoFrame:withEncodedVideoFrame:](macOS-callback#ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe) | 调用 [registerRemoteEncodedVideoFrameObserver:](macOS-api.md#ByteRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调 |
| [onProcessPlayBackAudioFrame:](macOS-callback.md#ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe) | 回调远端音频混音的音频帧地址，供自定义音频处理。 |
| [onProcessRecordAudioFrame:](macOS-callback.md#ByteRTCAudioFrameProcessor-onprocessrecordaudioframe) | 回调本地采集的音频帧地址，供自定义音频处理。 |
| [onProcessRemoteUserAudioFrame:audioFrame:](macOS-callback.md#ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe) | 回调单个远端用户的音频帧地址，供自定义音频处理。 |
| [onProcessScreenAudioFrame:](macOS-callback.md#ByteRTCAudioFrameProcessor-onprocessscreenaudioframe) | 回调屏幕共享的音频帧地址，供自定义音频处理。 |
| [onRecordAudioFrame:](macOS-callback.md#ByteRTCAudioFrameObserver-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame:](macOS-callback.md#ByteRTCAudioFrameObserver-onplaybackaudioframe) | 返回订阅的所有远端用户混音后的音频数据。 |
| [onRemoteUserAudioFrame:audioFrame:](macOS-callback.md#ByteRTCAudioFrameObserver-onremoteuseraudioframe-audioframe) | 返回远端单个用户的音频数据 |
| [onMixedAudioFrame:](macOS-callback.md#ByteRTCAudioFrameObserver-onmixedaudioframe) | 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据 |
| [processVideoFrame:](macOS-callback#ByteRTCVideoProcessorDelegate-processvideoframe) | 获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor:withConfig:](macOS-api.md#ByteRTCVideo-registerlocalvideoprocessor-withconfig) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。 |

## 网络管理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onperformancealarms-roomid-reason-sourcewanteddata) | 本地未通过 [setPublishFallbackOption:](macOS-api.md#ByteRTCVideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。  <br><br/>本地通过 [setPublishFallbackOption:](macOS-api.md#ByteRTCVideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。  <br> |
| [rtcEngine:onSimulcastSubscribeFallback:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback) | 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。 |
| [rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionresult-quality-rtt-lostrate-bitrate-jitter) | 通话前网络探测结果的回调。  <br><br/>成功调用 [startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:](macOS-api.md#ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [rtcEngine:onNetworkDetectionStopped:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionstopped) | 通话前网络探测结束  <br><br/>以下情况将停止探测并收到一次本回调：<br><br/>1. 当调用 [stopNetworkDetection](macOS-api.md#ByteRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；<br/>2. 当收到远端/本端音频首帧后，停止探测；<br/>3. 当探测超过3分钟后，停止探测；<br/>4. 当探测链路断开一定时间之后，停止探测。 |
| [rtcEngine:onConnectionStateChanged:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onconnectionstatechanged) | SDK 与信令服务器连接状态改变回调。连接状态改变时触发。 |
| [rtcEngine:onNetworkTypeChanged:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onnetworktypechanged) | SDK 当前网络连接类型改变回调。 |
| [rtcEngine:onSEIMessageReceived:andMessage:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage) | 收到通过调用 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](macOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 发送带有 SEI 消息的视频帧时，收到此回调。 |
| [rtcEngine:onEchoTestResult:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onechotestresult) | 关于音视频回路测试结果的回调。 |
| [rtcEngineOnNetworkTimeSynchronized:](macOS-callback#ByteRTCVideoDelegate-rtcengineonnetworktimesynchronized) | 首次调用 [getNetworkTimeInfo](macOS-api.md#ByteRTCVideo-getnetworktimeinfo) 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。 |

## 消息

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onRoomMessageReceived:message:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onroommessagereceived-message) | 收到房间中调用 [sendRoomMessage:](macOS-api.md#ByteRTCRoom-sendroommessage) 发送的广播文本消息时，收到此回调。 |
| [rtcRoom:onRoomBinaryMessageReceived:message:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onroombinarymessagereceived-message) | 收到房间内广播二进制消息的回调。<br><br/>房间内其他用户调用 [sendRoomBinaryMessage:](macOS-api.md#ByteRTCRoom-sendroombinarymessage) 发送的广播二进制消息时，收到此回调。 |
| [rtcRoom:onUserMessageReceived:message:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onusermessagereceived-message) | 收到来自房间中其他用户通过 [sendUserMessage:message:config:](macOS-api.md#ByteRTCRoom-sendusermessage-message-config) 发来的点对点文本消息时，会收到此回调。 |
| [rtcRoom:onUserBinaryMessageReceived:message:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onuserbinarymessagereceived-message) | 收到来自房间中其他用户通过 [sendUserBinaryMessage:message:config:](macOS-api.md#ByteRTCRoom-senduserbinarymessage-message-config) 发来的点对点二进制消息时，会收到此回调。 |
| [rtcRoom:onUserMessageSendResult:error:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error) | 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。 |
| [rtcRoom:onRoomMessageSendResult:error:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error) | 调用 [sendRoomMessage:](macOS-api.md#ByteRTCRoom-sendroommessage) 或 [sendRoomBinaryMessage:](macOS-api.md#ByteRTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [rtcEngine:onLoginResult:errorCode:elapsed:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed) | 登录结果回调 |
| [rtcEngine:onLogout:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlogout) | 登出结果回调 |
| [rtcEngine:onServerParamsSetResult:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onserverparamssetresult) | 设置应用服务器参数的返回结果 |
| [rtcEngine:onGetPeerOnlineStatus:status:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-ongetpeeronlinestatus-status) | 查询对端或本端用户登录状态的返回结果 |
| [rtcEngine:onUserMessageReceivedOutsideRoom:message:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onusermessagereceivedoutsideroom-message) | 收到房间外用户调用 [sendUserMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) 发来的文本消息时，会收到此回调 |
| [rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onuserbinarymessagereceivedoutsideroom-message) | 收到房间外用户调用 [sendUserBinaryMessageOutsideRoom:message:config:](macOS-api.md#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) 发来的二进制消息时，会收到此回调。 |
| [rtcEngine:onUserMessageSendResultOutsideRoom:error:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error) | 给房间外指定的用户发送消息的回调 |
| [rtcEngine:onServerMessageSendResult:error:message:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onservermessagesendresult-error-message) | 给应用服务器发送消息的回调。 |
| [rtcEngine:onSEIStreamUpdate:eventType:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onseistreamupdate-eventtype) | 黑帧视频流发布状态回调。  <br><br/>在语音通话场景下，本地用户调用 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](macOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br><br/>你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。 |

## CDN 推流

| 回调 | 描述 |
| --- | --- |
| [onStreamPushEvent:taskId:error:](macOS-callback.md#ByteRTCPushSingleStreamToCDNObserver-onstreampushevent-taskid-error) | 单流转推直播状态回调 |

## 混音

| 回调 | 描述 |
| --- | --- |
| [onFrame:audioFrame:](macOS-callback.md#ByteRTCMediaPlayerAudioFrameObserver-onframe-audioframe) | 当本地音频文件混音时，回调播放的音频帧。 |
| [onMediaPlayerStateChanged:state:error:](macOS-callback.md#ByteRTCMediaPlayerEventHandler-onmediaplayerstatechanged-state-error) | 播放状态改变时回调。 |
| [onMediaPlayerPlayingProgress:progress:](macOS-callback#ByteRTCMediaPlayerEventHandler-onmediaplayerplayingprogress-progress) | 播放进度周期性回调。回调周期通过 [setProgressInterval:](macOS-api.md#ByteRTCMediaPlayer-setprogressinterval) 设置。 |
| [onReadData:bufferSize:](macOS-callback#ByteRTCMediaPlayerCustomSourceProvider-onreaddata-buffersize) | 调用 [openWithCustomSource:config:](macOS-api.md#ByteRTCMediaPlayer-openwithcustomsource-config) 接口播放用户传入的内存音频数据时，会触发此回调，用户需要写入音频数据。 |
| [onSeek:whence:](macOS-callback#ByteRTCMediaPlayerCustomSourceProvider-onseek-whence) | 根据设置好的内存音频数据的读取位置和读取偏移量对音频数据进行偏移，以便 SDK 读取和分析音频数据。 <br><br/>在调用 [openWithCustomSource:config:](macOS-api.md#ByteRTCMediaPlayer-openwithcustomsource-config) 接口传入内存音频数据，或者调用 [setPosition:position:](macOS-api.md#ByteRTCAudioEffectPlayer-setposition-position) 设置了音频数据的起始播放位置后，SDK 会对音频数据进行读取和分析，此时会触发该回调，你需要根据参数中设置的起始读取位置和偏移量进行操作。 |

## 屏幕分享

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onUserPublishScreen:type:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) | 房间内新增远端屏幕共享音视频流的回调。 |
| [rtcRoom:onUserUnpublishScreen:type:reason:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) | 房间内远端屏幕共享音视频流移除的回调。 |
| [rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onscreenvideoframesendstatechanged-rtcuser-state) | 屏幕共享流的视频首帧发送状态发生改变时，收到此回调。 |
| [rtcEngine:onScreenVideoFramePlayStateChanged:rtcUser:state:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onscreenvideoframeplaystatechanged-rtcuser-state) | 屏幕共享流视频首帧播放状态发生改变时，收到此回调。 |
| [rtcEngine:onExternalScreenFrameUpdate:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onexternalscreenframeupdate) | 外部采集时，调用 [setOriginalScreenVideoInfo:withOriginalCaptureHeight:](macOS-api.md#ByteRTCVideo-setoriginalscreenvideoinfo-withoriginalcaptureheight) 设置屏幕或窗口大小改变前的分辨率后，若屏幕采集模式为智能模式，你将收到此回调，根据 RTC 智能决策合适的帧率和分辨率积（宽*高）重新采集。 |

## 安全与加密

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onCloudProxyConnected:](macOS-callback#ByteRTCVideoDelegate-rtcengine-oncloudproxyconnected) | 调用 [startCloudProxy:](macOS-api.md#ByteRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onEncryptData:](macOS-callback.md#ByteRTCEncryptHandler-onencryptdata) | 自定义加密。  <br><br/>使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br><br/>暂不支持对原始音视频帧进行加密。 |
| [onDecryptData:](macOS-callback.md#ByteRTCEncryptHandler-ondecryptdata) | 自定义解密。  <br><br/>对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData:](macOS-callback.md#ByteRTCEncryptHandler-onencryptdata)。 |

## 高级功能

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onExtensionAccessError:msg:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-onextensionaccesserror-msg) | 当访问插件失败时，收到此回调。<br/>RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。 |
| [rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info) | 获取本地录制状态回调。  <br><br/>该回调由 [startFileRecording:withRecordingConfig:type:](macOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 或 [stopFileRecording:](macOS-api.md#ByteRTCVideo-stopfilerecording) 触发。 |
| [rtcEngine:onRecordingProgressUpdate:process:recording_info:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info) | 本地录制进度回调。  <br><br/>该回调由 [startFileRecording:withRecordingConfig:type:](macOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。 |
| [rtcEngine:onAudioRecordingStateUpdate:error_code:](macOS-callback#ByteRTCVideoDelegate-rtcengine-onaudiorecordingstateupdate-error_code) | 调用 [startAudioRecording:](macOS-api.md#ByteRTCVideo-startaudiorecording) 或者 [stopAudioRecording](macOS-api.md#ByteRTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。 |
| [onTakeLocalSnapshotResult:streamIndex:image:errorCode:](macOS-callback#ByteRTCVideoSnapshotCallbackDelegate-ontakelocalsnapshotresult-streamindex-image-errorcode) | 调用 [takeLocalSnapshot:callback:](macOS-api.md#ByteRTCVideo-takelocalsnapshot-callback) 截取视频画面时，收到此回调。 |
| [onTakeRemoteSnapshotResult:streamKey:image:errorCode:](macOS-callback#ByteRTCVideoSnapshotCallbackDelegate-ontakeremotesnapshotresult-streamkey-image-errorcode) | 调用 [takeRemoteSnapshot:callback:](macOS-api.md#ByteRTCVideo-takeremotesnapshot-callback) 截取视频画面时，收到此回调。 |

## 字幕翻译服务

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage) | 字幕状态发生改变回调。 <br><br/>当用户调用 [startSubtitle:](macOS-api.md#ByteRTCRoom-startsubtitle) 和 [stopSubtitle](macOS-api.md#ByteRTCRoom-stopsubtitle) 使字幕状态发生改变或出现错误时，触发该回调。 |
| [rtcRoom:onSubtitleMessageReceived:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived) | 字幕相关内容回调。 <br><br/>当用户调用 [startSubtitle:](macOS-api.md#ByteRTCRoom-startsubtitle) 后会收到此回调，通知字幕的相关信息。 |

## 在线 KTV

| 回调 | 描述 |
| --- | --- |
| [onCurrentScoringInfo:](macOS-callback#ByteRTCSingScoringDelegate-oncurrentscoringinfo) | 实时评分信息回调。调用 [startSingScoring:scoringInfoInterval:](macOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 后，会收到该回调。 |