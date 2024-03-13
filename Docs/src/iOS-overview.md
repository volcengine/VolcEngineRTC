# 方法
## 引擎管理

| 方法 | 描述 |
| --- | --- |
| [createRTCVideo:delegate:parameters:](iOS-api.md#ByteRTCVideo-creatertcvideo-delegate-parameters) | 创建引擎对象。<br/>如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。 <br/>如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。 |
| [destroyRTCVideo](iOS-api.md#ByteRTCVideo-destroyrtcvideo) | 销毁由 [createRTCVideo:delegate:parameters:](iOS-api.md#ByteRTCVideo-creatertcvideo-delegate-parameters) 所创建的引擎实例，并释放所有相关资源。<br> |
| [getSDKVersion](iOS-api.md#ByteRTCVideo-getsdkversion) | 获取 SDK 当前的版本号。 |
| [feedback:info:](iOS-api.md#ByteRTCVideo-feedback-info) | 通话结束，将用户反馈的问题上报到 RTC。 <br> |
| [getErrorDescription:](iOS-api.md#ByteRTCVideo-geterrordescription) | 获取 SDK 内各种错误码、警告码的描述文字。 |
| [setBusinessId:](iOS-api.md#ByteRTCVideo-setbusinessid) | 设置业务标识参数  <br><br/>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
| [setRuntimeParameters:](iOS-api.md#ByteRTCVideo-setruntimeparameters) | 设置运行时的参数 |
| [setLogConfig:](iOS-api.md#ByteRTCVideo-setlogconfig) | 配置 SDK 本地日志参数，包括日志级别、存储路径、日志文件最大占用的总空间、日志文件名前缀。 |

## 房间管理

| 方法 | 描述 |
| --- | --- |
| [createRTCRoom:](iOS-api.md#ByteRTCVideo-creatertcroom) | 创建房间实例。<br><br/>调用此方法仅返回一个房间实例，你仍需调用 [joinRoom:userInfo:roomConfig:](iOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) 才能真正地创建/加入房间。<br><br/>多次调用此方法以创建多个 [ByteRTCRoom](iOS-api.md#bytertcroom) 实例。分别调用各 ByteRTCRoom 实例中的 [joinRoom:userInfo:roomConfig:](iOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) 方法，同时加入多个房间。<br><br/>多房间模式下，用户可以同时订阅各房间的音视频流。 |
| [destroy](iOS-api.md#ByteRTCRoom-destroy) | 退出并销毁调用 [createRTCRoom:](iOS-api.md#ByteRTCVideo-creatertcroom) 所创建的房间实例。 |
| [setRTCRoomDelegate:](iOS-api.md#ByteRTCRoom-setrtcroomdelegate) | 通过设置 [ByteRTCRoom](iOS-api.md#bytertcroom) 对象的事件句柄，监听此对象对应的回调事件。 |
| [joinRoom:userInfo:roomConfig:](iOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) | 加入房间。<br><br/>调用 [createRTCRoom:](iOS-api.md#ByteRTCVideo-creatertcroom) 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br> |
| [setRoomExtraInfo:value:](iOS-api.md#ByteRTCRoom-setroomextrainfo-value) | 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。 |
| [leaveRoom](iOS-api.md#ByteRTCRoom-leaveroom) | 离开房间。  <br><br/>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。 |
| [setUserVisibility:](iOS-api.md#ByteRTCRoom-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br/>默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，最多 30 人可同时上麦。更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。 |
| [updateToken:](iOS-api#ByteRTCRoom-updatetoken) | 更新 Token。<br/>收到 [onTokenWillExpire:](iOS-callback.md#ByteRTCRoomDelegate-ontokenwillexpire)，[onPublishPrivilegeTokenWillExpire:](iOS-callback.md#ByteRTCRoomDelegate-onpublishprivilegetokenwillexpire)，或 [onSubscribePrivilegeTokenWillExpire:](iOS-callback.md#ByteRTCRoomDelegate-onsubscribeprivilegetokenwillexpire) 时，你必须重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。 |

## 音频管理

| 方法 | 描述 |
| --- | --- |
| [setDefaultAudioRoute:](iOS-api.md#ByteRTCVideo-setdefaultaudioroute) | 将默认的音频播放设备设置为听筒或扬声器。 |
| [getAudioRoute](iOS-api.md#ByteRTCVideo-getaudioroute) | 获取当前使用的音频播放路由。  <br> |
| [setBluetoothMode:](iOS-api.md#ByteRTCVideo-setbluetoothmode) | 在纯媒体音频场景下,切换 iOS 设备与耳机之间的蓝牙传输协议。 |
| [setCaptureVolume:volume:](iOS-api.md#ByteRTCVideo-setcapturevolume-volume) | 调节音频采集音量 |
| [setPlaybackVolume:](iOS-api.md#ByteRTCVideo-setplaybackvolume) | 调节本地播放的所有远端用户音频混音后的音量，混音内容包括远端人声、音乐、音效等。<br><br/>播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume:remoteUid:playVolume:](iOS-api.md#ByteRTCVideo-setremoteaudioplaybackvolume-remoteuid-playvolume) | 调节来自指定远端用户的音频播放音量。 |
| [setRemoteRoomAudioPlaybackVolume:](iOS-api.md#ByteRTCRoom-setremoteroomaudioplaybackvolume) | 调节某个房间内所有远端用户的音频播放音量。 |
| [enableAudioPropertiesReport:](iOS-api#ByteRTCVideo-enableaudiopropertiesreport) | 启用音频信息提示。启用后，你可以收到 [rtcEngine:onLocalAudioPropertiesReport:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport)，[rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume)，和 [rtcEngine:onActiveSpeaker:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid)。 |
| [startAudioCapture](iOS-api#ByteRTCVideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法开启后，本地用户会收到 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStartAudioCapture:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid) 的回调。 |
| [stopAudioCapture](iOS-api#ByteRTCVideo-stopaudiocapture) | 关闭内部音频采集。默认为关闭状态。  <br><br/>内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br/>调用该方法，本地用户会收到 [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStopAudioCapture:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid) 的回调。 |
| [setAudioScenario:](iOS-api.md#ByteRTCVideo-setaudioscenario) | 设置音频场景类型。<br/>你可以根据你的应用所在场景，选择合适的音频场景类型。<br/>选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量，并同步变更对应音频相关的算法配置和采集配置。 |
| [setAudioProfile:](iOS-api#ByteRTCVideo-setaudioprofile) | 设置音质档位。<br><br/>当所选的 [ByteRTCRoomProfile](iOS-keytype.md#bytertcroomprofile) 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。 |
| [enableExternalSoundCard:](iOS-api.md#ByteRTCVideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |
| [startHardwareEchoDetection:](iOS-api.md#ByteRTCVideo-starthardwareechodetection) | 开启通话前回声检测 |
| [stopHardwareEchoDetection](iOS-api.md#ByteRTCVideo-stophardwareechodetection) | 停止通话前回声检测 |

## 视频管理

| 方法 | 描述 |
| --- | --- |
| [startVideoCapture](iOS-api#ByteRTCVideo-startvideocapture) | 立即开启内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStartVideoCapture:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid) 的回调。 |
| [stopVideoCapture](iOS-api#ByteRTCVideo-stopvideocapture) | 立即关闭内部视频采集。默认为关闭状态。  <br><br/>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br><br/>调用该方法后，本地用户会收到 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 的回调。  <br><br/>可见用户进房后调用该方法，房间中的其他用户会收到 [rtcEngine:onUserStopVideoCapture:uid:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid) 的回调。 |
| [setVideoCaptureConfig:](iOS-api.md#ByteRTCVideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。<br><br/>如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。 |
| [setVideoRotationMode:](iOS-api.md#ByteRTCVideo-setvideorotationmode) | 设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br><br/>接收端渲染视频时，将按照和发送端相同的方式进行旋转。<br> |
| [setLocalVideoCanvas:withCanvas:](iOS-api.md#ByteRTCVideo-setlocalvideocanvas-withcanvas) | 设置本地视频渲染时使用的视图，并设置渲染模式。 |
| [updateLocalVideoCanvas:withRenderMode:withBackgroundColor:](iOS-api.md#ByteRTCVideo-updatelocalvideocanvas-withrendermode-withbackgroundcolor) | 修改本地视频渲染模式和背景色。 |
| [setRemoteVideoCanvas:withCanvas:](iOS-api.md#ByteRTCVideo-setremotevideocanvas-withcanvas) | 渲染来自指定远端用户 uid 的视频流时，设置使用的视图和渲染模式。  <br><br/>如果需要解除视频的绑定视图，把 `canvas.view` 设置为空。(`canvas` 中其他参数不能为空。) |
| [updateRemoteStreamVideoCanvas:withRemoteVideoRenderConfig:](iOS-api.md#ByteRTCVideo-updateremotestreamvideocanvas-withremotevideorenderconfig) | 使用 SDK 内部渲染时，修改远端视频帧的渲染设置，包括渲染模式、背景颜色和旋转角度。 |
| [switchCamera:](iOS-api#ByteRTCVideo-switchcamera) | 切换视频内部采集时使用的前置/后置摄像头 <br><br/>调用此接口后，在本地会触发 [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) 回调。 |
| [isCameraZoomSupported](iOS-api.md#ByteRTCVideo-iscamerazoomsupported) | 检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。 |
| [getCameraZoomMaxRatio](iOS-api.md#ByteRTCVideo-getcamerazoommaxratio) | 获取当前使用的摄像头（前置/后置）的最大变焦倍数 |
| [setCameraZoomRatio:](iOS-api.md#ByteRTCVideo-setcamerazoomratio) | 设置当前使用的摄像头（前置/后置）的变焦倍数 |
| [isCameraTorchSupported](iOS-api.md#ByteRTCVideo-iscameratorchsupported) | 检测当前使用的摄像头（前置/后置），是否支持闪光灯。 |
| [setCameraTorch:](iOS-api.md#ByteRTCVideo-setcameratorch) | 打开/关闭当前使用的摄像头（前置/后置）的闪光灯 |
| [isCameraFocusPositionSupported](iOS-api.md#ByteRTCVideo-iscamerafocuspositionsupported) | 检查当前使用的摄像头是否支持手动对焦。 |
| [setCameraFocusPosition:](iOS-api.md#ByteRTCVideo-setcamerafocusposition) | 设置当前使用的摄像头的对焦点。 |
| [isCameraExposurePositionSupported](iOS-api.md#ByteRTCVideo-iscameraexposurepositionsupported) | 检查当前使用的摄像头是否支持手动设置曝光点。 |
| [setCameraExposurePosition:](iOS-api.md#ByteRTCVideo-setcameraexposureposition) | 设置当前使用的摄像头的曝光点。 |
| [setCameraExposureCompensation:](iOS-api.md#ByteRTCVideo-setcameraexposurecompensation) | 设置当前使用的摄像头的曝光补偿。 |
| [setVideoEncoderConfig:](iOS-api.md#ByteRTCVideo-setvideoencoderconfig) | 视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [setMaxVideoEncoderConfig:](iOS-api.md#ByteRTCVideo-setmaxvideoencoderconfig) | 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br><br/>该接口支持设置一路视频流参数，设置多路参数请使用 [setVideoEncoderConfig:](iOS-api.md#ByteRTCVideo-setvideoencoderconfig)。 |

## 音视频传输

| 方法 | 描述 |
| --- | --- |
| [publishStream:](iOS-api.md#ByteRTCRoom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream:](iOS-api.md#ByteRTCRoom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [setDummyCaptureImagePath:](iOS-api.md#ByteRTCVideo-setdummycaptureimagepath) | 摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。<br/>调用 `stopVideoCapture` 接口时，会开始推静态图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。<br/>可重复调用该接口来更新图片。 |
| [subscribeStream:mediaStreamType:](iOS-api.md#ByteRTCRoom-subscribestream-mediastreamtype) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream:mediaStreamType:](iOS-api.md#ByteRTCRoom-unsubscribestream-mediastreamtype) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreamsWithMediaStreamType:](iOS-api.md#ByteRTCRoom-subscribeallstreamswithmediastreamtype) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreamsWithMediaStreamType:](iOS-api.md#ByteRTCRoom-unsubscribeallstreamswithmediastreamtype) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br><br/>自动订阅和手动订阅的流都可以通过本方法取消订阅。 |
| [pauseAllSubscribedStream:](iOS-api.md#ByteRTCRoom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流 |
| [resumeAllSubscribedStream:](iOS-api.md#ByteRTCRoom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [requestRemoteVideoKeyFrame:](iOS-api.md#ByteRTCVideo-requestremotevideokeyframe) | 在订阅远端视频流之后，向远端请求关键帧 |
| [startForwardStreamToRooms:](iOS-api.md#ByteRTCRoom-startforwardstreamtorooms) | 开始跨房间转发媒体流。<br/>在调用 [joinRoom:userInfo:roomConfig:](iOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br> |
| [updateForwardStreamToRooms:](iOS-api#ByteRTCRoom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。<br><br/>通过 [startForwardStreamToRooms:](iOS-api#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br/>调用本方法增加或删减房间后，将在本端触发 [rtcRoom:onForwardStreamStateChanged:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) 回调，包含发生了变动的目标房间中媒体流转发状态。 |
| [stopForwardStreamToRooms](iOS-api.md#ByteRTCRoom-stopforwardstreamtorooms) | 停止跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms:](iOS-api.md#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。 |
| [pauseForwardStreamToAllRooms](iOS-api.md#ByteRTCRoom-pauseforwardstreamtoallrooms) | 暂停跨房间媒体流转发。<br/>通过 [startForwardStreamToRooms:](iOS-api.md#ByteRTCRoom-startforwardstreamtorooms) 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br/>调用本方法暂停向所有目标房间转发后，你可以随时调用 [resumeForwardStreamToAllRooms](iOS-api.md#ByteRTCRoom-resumeforwardstreamtoallrooms) 快速恢复转发。 |
| [resumeForwardStreamToAllRooms](iOS-api.md#ByteRTCRoom-resumeforwardstreamtoallrooms) | 恢复跨房间媒体流转发。<br/>调用 [pauseForwardStreamToAllRooms](iOS-api.md#ByteRTCRoom-pauseforwardstreamtoallrooms) 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。 |
| [setMultiDeviceAVSync:](iOS-api.md#ByteRTCRoom-setmultideviceavsync) | 设置发流端音画同步。  <br><br/>当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。 |
| [startPushPublicStream:withLayout:](iOS-api.md#ByteRTCVideo-startpushpublicstream-withlayout) | 发布一路公共流<br><br/>用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream) 获取和播放指定的公共流。 |
| [stopPushPublicStream:](iOS-api.md#ByteRTCVideo-stoppushpublicstream) | 停止发布当前用户发布的公共流<br><br/>关于发布公共流，查看 [startPushPublicStream:withLayout:](iOS-api.md#ByteRTCVideo-startpushpublicstream-withlayout)。 |
| [updatePublicStreamParam:withLayout:](iOS-api#ByteRTCVideo-updatepublicstreamparam-withlayout) | 更新公共流参数<br><br/>关于发布公共流，查看 [startPushPublicStream:withLayout:](iOS-api#ByteRTCVideo-startpushpublicstream-withlayout)。<br/>建议调用更新公共流前判断公共流是否已经成功启动，相关回调详见 [rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode)。 |
| [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream) | 订阅指定公共流<br><br/>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream:](iOS-api.md#ByteRTCVideo-stopplaypublicstream) | 取消订阅指定公共流<br><br/>关于订阅公共流，查看 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream)。 |
| [setPublicStreamVideoCanvas:withCanvas:](iOS-api.md#ByteRTCVideo-setpublicstreamvideocanvas-withcanvas) | 为指定公共流绑定内部渲染视图。 |
| [setPublicStreamVideoSink:withSink:withPixelFormat:](iOS-api.md#ByteRTCVideo-setpublicstreamvideosink-withsink-withpixelformat) | 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。 |
| [setPublicStreamAudioPlaybackVolume:volume:](iOS-api.md#ByteRTCVideo-setpublicstreamaudioplaybackvolume-volume) | 调节公共流的音频播放音量。 |

## 视频处理

| 方法 | 描述 |
| --- | --- |
| [setVideoDenoiser:](iOS-api.md#ByteRTCVideo-setvideodenoiser) | 设置视频降噪模式。 |
| [setRemoteVideoSuperResolution:withMode:](iOS-api.md#ByteRTCVideo-setremotevideosuperresolution-withmode) | 设置远端视频超分模式。 |
| [setLocalVideoMirrorType:](iOS-api.md#ByteRTCVideo-setlocalvideomirrortype) | 为采集到的视频流开启镜像 |
| [setRemoteVideoMirrorType:withMirrorType:](iOS-api.md#ByteRTCVideo-setremotevideomirrortype-withmirrortype) | 使用内部渲染时，为远端流开启镜像。 |
| [setVideoOrientation:](iOS-api.md#ByteRTCVideo-setvideoorientation) | 在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。<br/>移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。 |
| [setVideoWatermark:withImagePath:withRtcWatermarkConfig:](iOS-api.md#ByteRTCVideo-setvideowatermark-withimagepath-withrtcwatermarkconfig) | 在指定视频流上添加水印。 |
| [clearVideoWatermark:](iOS-api.md#ByteRTCVideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [enableEffectBeauty:](iOS-api.md#ByteRTCVideo-enableeffectbeauty) | 开启/关闭基础美颜。 |
| [setBeautyIntensity:withIntensity:](iOS-api.md#ByteRTCVideo-setbeautyintensity-withintensity) | 调整基础美颜强度。 |
| [getVideoEffectInterface](iOS-api.md#ByteRTCVideo-getvideoeffectinterface) | 获取视频特效接口。 |
| [initCVResource:withAlgoModelDir:](iOS-api.md#ByteRTCVideoEffect-initcvresource-withalgomodeldir) | 检查视频特效证书，设置算法模型路径，并初始化特效模块。 |
| [enableVideoEffect](iOS-api.md#ByteRTCVideoEffect-enablevideoeffect) | 开启高级美颜、滤镜等视频特效。 |
| [disableVideoEffect](iOS-api.md#ByteRTCVideoEffect-disablevideoeffect) | 关闭视频特效。 |
| [setEffectNodes:](iOS-api.md#ByteRTCVideoEffect-seteffectnodes) | 设置视频特效素材包。 |
| [updateEffectNode:key:value:](iOS-api.md#ByteRTCVideoEffect-updateeffectnode-key-value) | 设置特效强度。 |
| [setColorFilter:](iOS-api.md#ByteRTCVideoEffect-setcolorfilter) | 设置颜色滤镜。 |
| [setColorFilterIntensity:](iOS-api.md#ByteRTCVideoEffect-setcolorfilterintensity) | 设置已启用颜色滤镜的强度。 |
| [enableVirtualBackground:withSource:](iOS-api.md#ByteRTCVideoEffect-enablevirtualbackground-withsource) | 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。 |
| [disableVirtualBackground](iOS-api.md#ByteRTCVideoEffect-disablevirtualbackground) | 关闭虚拟背景。 |
| [enableFaceDetection:withInterval:withModelPath:](iOS-api#ByteRTCVideoEffect-enablefacedetection-withinterval-withmodelpath) | 开启人脸识别功能，并设置人脸检测结果回调观察者。<br/>此观察者后，你会周期性收到 [onFaceDetectResult:](iOS-callback.md#ByteRTCFaceDetectionObserver-onfacedetectresult) 回调。 |
| [disableFaceDetection](iOS-api.md#ByteRTCVideoEffect-disablefacedetection) | 关闭人脸识别功能。 |
| [setVideoDigitalZoomConfig:size:](iOS-api.md#ByteRTCVideo-setvideodigitalzoomconfig-size) | 设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。 |
| [setVideoDigitalZoomControl:](iOS-api.md#ByteRTCVideo-setvideodigitalzoomcontrol) | 控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。 |
| [startVideoDigitalZoomControl:](iOS-api.md#ByteRTCVideo-startvideodigitalzoomcontrol) | 开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。 |
| [stopVideoDigitalZoomControl](iOS-api.md#ByteRTCVideo-stopvideodigitalzoomcontrol) | 停止本地摄像头持续数码变焦。 |

## 音频处理

| 方法 | 描述 |
| --- | --- |
| [setVoiceChangerType:](iOS-api.md#ByteRTCVideo-setvoicechangertype) | 设置变声特效类型 |
| [setVoiceReverbType:](iOS-api.md#ByteRTCVideo-setvoicereverbtype) | 设置混响特效类型 |
| [setLocalVoicePitch:](iOS-api.md#ByteRTCVideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。  <br><br/>使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |
| [setLocalVoiceEqualization:](iOS-api.md#ByteRTCVideo-setlocalvoiceequalization) | 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [setLocalVoiceReverbParam:](iOS-api.md#ByteRTCVideo-setlocalvoicereverbparam) | 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [enableLocalVoiceReverb:](iOS-api.md#ByteRTCVideo-enablelocalvoicereverb) | 开启本地音效混响效果 |

## 自定义流处理

| 方法 | 描述 |
| --- | --- |
| [setVideoSourceType:WithStreamIndex:](iOS-api.md#ByteRTCVideo-setvideosourcetype-withstreamindex) | 设置向 SDK 输入的视频源，包括屏幕流<br/>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br> |
| [pushExternalVideoFrame:](iOS-api.md#ByteRTCVideo-pushexternalvideoframe) | 推送外部视频帧。 |
| [setLocalVideoRender:withSink:withLocalRenderConfig:](iOS-api.md#ByteRTCVideo-setlocalvideorender-withsink-withlocalrenderconfig) | 将本地视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。 |
| [setRemoteVideoRender:withSink:withRemoteRenderConfig:](iOS-api.md#ByteRTCVideo-setremotevideorender-withsink-withremoterenderconfig) | 将远端视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。 |
| [registerRemoteEncodedVideoFrameObserver:](iOS-api#ByteRTCVideo-registerremoteencodedvideoframeobserver) | 注册远端编码后视频数据回调。  <br><br/>完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 [onRemoteEncodedVideoFrame:withEncodedVideoFrame:](iOS-callback.md#ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe) 回调 |
| [setVideoDecoderConfig:withVideoDecoderConfig:](iOS-api.md#ByteRTCVideo-setvideodecoderconfig-withvideodecoderconfig) | 在订阅远端视频流之前，设置远端视频数据解码方式 |
| [setAudioSourceType:](iOS-api.md#ByteRTCVideo-setaudiosourcetype) | 切换音频采集方式 |
| [setAudioRenderType:](iOS-api.md#ByteRTCVideo-setaudiorendertype) | 切换音频渲染方式 |
| [pushExternalAudioFrame:](iOS-api.md#ByteRTCVideo-pushexternalaudioframe) | 推送自定义采集的音频数据到 RTC SDK。 |
| [pullExternalAudioFrame:](iOS-api.md#ByteRTCVideo-pullexternalaudioframe) | 拉取下行音频数据用于自定义音频渲染。<br/>调用该方法后，SDK 会主动拉取待播放的音频数据，包括远端已解码和混音后的音频数据，用于外部播放。 |
| [registerLocalVideoProcessor:withConfig:](iOS-api#ByteRTCVideo-registerlocalvideoprocessor-withconfig) | 设置自定义视频前处理器。<br><br/>使用这个视频前处理器，你能够调用 [processVideoFrame:](iOS-callback.md#ByteRTCVideoProcessorDelegate-processvideoframe) 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。 |
| [registerAudioProcessor:](iOS-api.md#ByteRTCVideo-registeraudioprocessor) | 注册自定义音频处理器。<br><br/>注册完成后，你可以调用 [enableAudioProcessor:audioFormat:](iOS-api.md#ByteRTCVideo-enableaudioprocessor-audioformat)，对本地采集到的音频进行处理，RTC SDK 将对处理后的音频进行编码和发送。也可以对接收到的远端音频进行自定义处理，RTC SDK 将对处理后的音频进行渲染。 |
| [enableAudioProcessor:audioFormat:](iOS-api.md#ByteRTCVideo-enableaudioprocessor-audioformat) | 设置并开启指定的音频帧回调，进行自定义处理。 |
| [disableAudioProcessor:](iOS-api.md#ByteRTCVideo-disableaudioprocessor) | 关闭自定义音频处理。 |
| [registerAudioFrameObserver:](iOS-api.md#ByteRTCVideo-registeraudioframeobserver) | 注册音频数据回调观察者。  <br> |
| [enableAudioFrameCallback:format:](iOS-api.md#ByteRTCVideo-enableaudioframecallback-format) | 设置并开启指定的音频数据帧回调 |
| [disableAudioFrameCallback:](iOS-api.md#ByteRTCVideo-disableaudioframecallback) | 关闭音频回调 |
| [registerLocalEncodedVideoFrameObserver:](iOS-api#ByteRTCVideo-registerlocalencodedvideoframeobserver) | 注册本地视频帧监测器。  <br><br/>无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 [onLocalEncodedVideoFrame:Frame:](iOS-callback.md#ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame) 回调给用户 |
| [setExternalVideoEncoderEventHandler:](iOS-api.md#ByteRTCVideo-setexternalvideoencodereventhandler) | 注册自定义编码帧推送事件回调 |
| [pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:](iOS-api.md#ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe) | 推送自定义编码后的视频流 |

## 网络管理

| 方法 | 描述 |
| --- | --- |
| [enableSimulcastMode:](iOS-api.md#ByteRTCVideo-enablesimulcastmode) | 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。 |
| [setRemoteVideoConfig:remoteVideoConfig:](iOS-api.md#ByteRTCRoom-setremotevideoconfig-remotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [setPublishFallbackOption:](iOS-api.md#ByteRTCVideo-setpublishfallbackoption) | 设置发布的音视频流的回退选项。  <br><br/>你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。 |
| [setSubscribeFallbackOption:](iOS-api.md#ByteRTCVideo-setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。 <br><br/>你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
| [setRemoteUserPriority:InRoomId:uid:](iOS-api.md#ByteRTCVideo-setremoteuserpriority-inroomid-uid) | 设置用户优先级。 |
| [startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:](iOS-api.md#ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth) | 开始通话前网络探测 |
| [stopNetworkDetection](iOS-api.md#ByteRTCVideo-stopnetworkdetection) | 停止通话前网络探测 |
| [startEchoTest:playDelay:](iOS-api.md#ByteRTCVideo-startechotest-playdelay) | 开启音视频回路测试。  <br><br/>在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br><br/>开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。 |
| [stopEchoTest](iOS-api.md#ByteRTCVideo-stopechotest) | 停止音视频回路测试。  <br><br/>调用 [startEchoTest:playDelay:](iOS-api.md#ByteRTCVideo-startechotest-playdelay) 开启音视频回路检测后，你必须调用该方法停止检测。 |
| [getNetworkTimeInfo](iOS-api.md#ByteRTCVideo-getnetworktimeinfo) | 通过 NTP 协议，获取网络时间。 |

## 消息

| 方法 | 描述 |
| --- | --- |
| [sendRoomMessage:](iOS-api.md#ByteRTCRoom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [sendRoomBinaryMessage:](iOS-api.md#ByteRTCRoom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [sendUserMessage:message:config:](iOS-api.md#ByteRTCRoom-sendusermessage-message-config) | 给房间内指定的用户发送点对点文本消息（P2P）。 |
| [sendUserBinaryMessage:message:config:](iOS-api.md#ByteRTCRoom-senduserbinarymessage-message-config) | 给房间内指定的用户发送点对点二进制消息（P2P）。 |
| [login:uid:](iOS-api.md#ByteRTCVideo-login-uid) | 登录 RTS 服务器。<br>必须先登录，才能调用 [sendUserMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) 和 [sendServerMessage:](iOS-api.md#ByteRTCVideo-sendservermessage) 发送房间外点对点消息和向应用服务器发送消息 <br><br/>在调用本接口登录后，如果想要登出，需要调用 [logout](iOS-api.md#ByteRTCVideo-logout) |
| [logout](iOS-api.md#ByteRTCVideo-logout) | 登出 RTS 服务器。<br>调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [updateLoginToken:](iOS-api#ByteRTCVideo-updatelogintoken) | 更新用户用于登录的 Token  <br><br/>Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br><br/>调用 [login:uid:](iOS-api#ByteRTCVideo-login-uid) 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 [rtcEngine:onLoginResult:errorCode:elapsed:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed) 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。 |
| [setServerParams:url:](iOS-api.md#ByteRTCVideo-setserverparams-url) | 设置应用服务器参数  <br><br/>客户端调用 [sendServerMessage:](iOS-api.md#ByteRTCVideo-sendservermessage) 或 [sendServerBinaryMessage:](iOS-api.md#ByteRTCVideo-sendserverbinarymessage) 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。 |
| [getPeerOnlineStatus:](iOS-api.md#ByteRTCVideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [sendUserMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) | 给房间外指定的用户发送文本消息（P2P） |
| [sendUserBinaryMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) | 给房间外指定的用户发送二进制消息（P2P） |
| [sendServerMessage:](iOS-api.md#ByteRTCVideo-sendservermessage) | 客户端给应用服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage:](iOS-api.md#ByteRTCVideo-sendserverbinarymessage) | 客户端给应用服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo:config:](iOS-api#ByteRTCVideo-sendstreamsyncinfo-config) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 [rtcEngine:onStreamSyncInfoReceived:streamType:data:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data) 回调。 |
| [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](iOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) | 通过视频帧发送 SEI 数据。<br/>在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。 |

## CDN 推流

| 方法 | 描述 |
| --- | --- |
| [startPushMixedStreamToCDN:mixedConfig:observer:](iOS-api.md#ByteRTCVideo-startpushmixedstreamtocdn-mixedconfig-observer) | 新增合流转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br><br/>同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。 |
| [updatePushMixedStreamToCDN:mixedConfig:](iOS-api#ByteRTCVideo-updatepushmixedstreamtocdn-mixedconfig) | 更新合流转推直播参数，会收到 [onMixingEvent:taskId:error:mixType:](iOS-callback.md#ByteRTCMixedStreamObserver-onmixingevent-taskid-error-mixtype) 回调。  <br><br/>开启转推直播功能后，你可以使用此方法更新合流转推功能配置参数。 |
| [startPushSingleStreamToCDN:singleStream:observer:](iOS-api.md#ByteRTCVideo-startpushsinglestreamtocdn-singlestream-observer) | 新增单流转推直播任务。 |
| [stopPushStreamToCDN:](iOS-api.md#ByteRTCVideo-stoppushstreamtocdn) | 停止转推直播。<br><br/>该方法可用于停止单流转推直播或停止合流转推直播，通过 taskId 区分需要停止的任务。 |

## 混音

| 方法 | 描述 |
| --- | --- |
| [getAudioEffectPlayer](iOS-api.md#ByteRTCVideo-getaudioeffectplayer) | 创建音效播放器实例。 |
| [start:filePath:config:](iOS-api.md#ByteRTCAudioEffectPlayer-start-filepath-config) | 开始播放音效文件。<br><br/>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个音效文件，实现音效叠加。 |
| [preload:filePath:](iOS-api.md#ByteRTCAudioEffectPlayer-preload-filepath) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [setPosition:position:](iOS-api.md#ByteRTCAudioEffectPlayer-setposition-position) | 设置音效文件的起始播放位置。 |
| [setVolume:volume:](iOS-api.md#ByteRTCAudioEffectPlayer-setvolume-volume) | 调节指定音效的音量大小，包括音效文件和 PCM 音频。 |
| [open:config:](iOS-api.md#ByteRTCMediaPlayer-open-config) | 打开音乐文件。<br/>一个播放器实例仅能够同时打开一个音乐文件。如果需要同时打开多个音乐文件，请创建多个音乐播放器实例。<br/>要播放 PCM 格式的音频数据，参看 [openWithCustomSource:config:](iOS-api.md#ByteRTCMediaPlayer-openwithcustomsource-config)。`openWithCustomSource` 和此 API 互斥。 |
| [openWithCustomSource:config:](iOS-api.md#ByteRTCMediaPlayer-openwithcustomsource-config) | 启动音频裸数据混音。<br/>要播放音乐文件，参看 [open:config:](iOS-api.md#ByteRTCMediaPlayer-open-config)。`open` 与此 API 互斥。 |
| [setVolume:type:](iOS-api.md#ByteRTCMediaPlayer-setvolume-type) | 调节指定混音的音量大小，包括音乐文件混音和 PCM 混音。 |

## 屏幕分享

| 方法 | 描述 |
| --- | --- |
| [setExtensionConfig:](iOS-api.md#ByteRTCVideo-setextensionconfig) | 设置 Extension 配置项。你必须在使用屏幕内部采集功能前，设置使用的 Extension。 |
| [startScreenCapture:bundleId:](iOS-api.md#ByteRTCVideo-startscreencapture-bundleid) | 使用 RTC SDK 内部采集模块开始采集屏幕音频流和（或）视频流。 |
| [updateScreenCapture:](iOS-api.md#ByteRTCVideo-updatescreencapture) | 更新内部屏幕采集时采集的媒体类型。 |
| [stopScreenCapture](iOS-api.md#ByteRTCVideo-stopscreencapture) | 在屏幕共享时，停止使用 RTC SDK 内部采集方式采集屏幕音视频。 |
| [publishScreen:](iOS-api.md#ByteRTCRoom-publishscreen) | 在当前所在房间内发布本地屏幕共享音视频流 |
| [unpublishScreen:](iOS-api.md#ByteRTCRoom-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [setScreenAudioSourceType:](iOS-api.md#ByteRTCVideo-setscreenaudiosourcetype) | 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集） |
| [setScreenAudioStreamIndex:](iOS-api.md#ByteRTCVideo-setscreenaudiostreamindex) | 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式 |
| [setScreenVideoEncoderConfig:](iOS-api.md#ByteRTCVideo-setscreenvideoencoderconfig) | 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [pushScreenAudioFrame:](iOS-api.md#ByteRTCVideo-pushscreenaudioframe) | 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。 |
| [pushScreenVideoFrame:time:rotation:](iOS-api.md#ByteRTCVideo-pushscreenvideoframe-time-rotation) | 推送外部屏幕采集帧 |
| [subscribeScreen:mediaStreamType:](iOS-api.md#ByteRTCRoom-subscribescreen-mediastreamtype) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen:mediaStreamType:](iOS-api.md#ByteRTCRoom-unsubscribescreen-mediastreamtype) | 取消订阅房间内指定的远端屏幕共享音视频流。  <br><br/>该方法对自动订阅和手动订阅模式均适用。 |
| [sendScreenCaptureExtensionMessage:](iOS-api.md#ByteRTCVideo-sendscreencaptureextensionmessage) | 向屏幕共享 Extension 发送自定义消息 |

## 安全与加密

| 方法 | 描述 |
| --- | --- |
| [startCloudProxy:](iOS-api.md#ByteRTCVideo-startcloudproxy) | 开启云代理 |
| [setCustomizeEncryptHandler:](iOS-api.md#ByteRTCVideo-setcustomizeencrypthandler) | 设置自定义加密和解密方式。 |
| [setEncryptInfo:key:](iOS-api.md#ByteRTCVideo-setencryptinfo-key) | 设置传输时使用内置加密的方式。 |
| [setLocalProxy:](iOS-api.md#ByteRTCVideo-setlocalproxy) | 设置本地代理。 |

## 高级功能

| 方法 | 描述 |
| --- | --- |
| [startFileRecording:withRecordingConfig:type:](iOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) | 该方法将通话过程中的音视频数据录制到本地的文件中。 |
| [stopFileRecording:](iOS-api.md#ByteRTCVideo-stopfilerecording) | 停止本地录制 |
| [startAudioRecording:](iOS-api.md#ByteRTCVideo-startaudiorecording) | 开启录制语音通话，生成本地文件。<br><br/>在进房前后开启录制，如果未打开麦克风采集，录制任务正常进行，只是不会将数据写入生成的本地文件；只有调用 [startAudioCapture](iOS-api.md#ByteRTCVideo-startaudiocapture) 接口打开麦克风采集后，才会将录制数据写入本地文件。 |
| [stopAudioRecording](iOS-api.md#ByteRTCVideo-stopaudiorecording) | 停止音频文件录制 |
| [setEarMonitorMode:](iOS-api.md#ByteRTCVideo-setearmonitormode) | 开启/关闭耳返功能。 |
| [setEarMonitorVolume:](iOS-api.md#ByteRTCVideo-setearmonitorvolume) | 设置耳返的音量。 |
| [getSpatialAudio](iOS-api.md#ByteRTCRoom-getspatialaudio) | 获取空间音频接口实例。 |
| [disableRemoteOrientation](iOS-api.md#ByteRTCSpatialAudio-disableremoteorientation) | 关闭本地用户朝向对本地用户发声效果的影响。<br><br/>调用此接口后，房间内的其他用户收听本地发声时，声源都在收听者正面。 |
| [getRangeAudio](iOS-api.md#ByteRTCRoom-getrangeaudio) | 获取范围语音接口实例。 |
| [startASR:handler:](iOS-api#ByteRTCVideo-startasr-handler) | 开启自动语音识别服务。<br><br/>该方法将识别后的用户语音转化成文字，并通过 [onMessage:](iOS-callback.md#ByteRTCASREngineEventHandler-onmessage) 事件回调给用户。 |
| [stopASR](iOS-api.md#ByteRTCVideo-stopasr) | 关闭语音识别服务 |
| [takeLocalSnapshot:callback:](iOS-api.md#ByteRTCVideo-takelocalsnapshot-callback) | 截取本地视频画面 |
| [takeRemoteSnapshot:callback:](iOS-api.md#ByteRTCVideo-takeremotesnapshot-callback) | 截取远端视频画面 |
| [setAnsMode:](iOS-api.md#ByteRTCVideo-setansmode) | 支持根据业务场景，设置通话中的音频降噪模式。 |
| [updateSelfPosition:](iOS-api.md#ByteRTCSpatialAudio-updateselfposition) | 设置本地用户在自建空间直角坐标系中的收听坐标和收听朝向，以实现本地用户预期的空间音频收听效果。 |
| [updateRemotePosition:positionInfo:](iOS-api.md#ByteRTCSpatialAudio-updateremoteposition-positioninfo) | 设置房间内某一远端用户在本地用户自建的空间音频坐标系中的发声位置和发声朝向，以实现本地用户预期的空间音频收听效果。 |
| [removeRemotePosition:](iOS-api.md#ByteRTCSpatialAudio-removeremoteposition) | 移除调用 [updateRemotePosition:positionInfo:](iOS-api.md#ByteRTCSpatialAudio-updateremoteposition-positioninfo) 为某一远端用户设置的空间音频效果。 |
| [removeAllRemotePosition](iOS-api.md#ByteRTCSpatialAudio-removeallremoteposition) | 移除调用 [updateRemotePosition:positionInfo:](iOS-api.md#ByteRTCSpatialAudio-updateremoteposition-positioninfo) 为所有远端用户设置的空间音频效果。 |

## 字幕翻译服务

| 方法 | 描述 |
| --- | --- |
| [startSubtitle:](iOS-api#ByteRTCRoom-startsubtitle) | 识别或翻译房间内所有用户的语音，形成字幕。<br><br/>调用该方法时，可以在 [ByteRTCSubtitleMode](iOS-keytype#bytertcsubtitlemode) 中选择语音识别或翻译模式。如果选择识别模式，语音识别文本会通过 [rtcRoom:onSubtitleMessageReceived:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived) 事件回调给你；<br><br/>如果选择翻译模式，你会同时收到两个 [rtcRoom:onSubtitleMessageReceived:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived) 回调，分别包含字幕原文及字幕译文。<br><br/>调用该方法后，用户会收到 [rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage) 回调，通知字幕是否开启。 |
| [stopSubtitle](iOS-api#ByteRTCRoom-stopsubtitle) | 关闭字幕。 <br><br/>调用该方法后，用户会收到 [rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage)  回调，通知字幕是否关闭。 |

## 在线 KTV

| 方法 | 描述 |
| --- | --- |
| [getKTVManager](iOS-api.md#ByteRTCVideo-getktvmanager) | 创建 KTV 管理接口。 |
| [getMusicList:pageSize:filterType:](iOS-api.md#ByteRTCKTVManager-getmusiclist-pagesize-filtertype) | 获取歌曲列表。 |
| [searchMusic:pageNumber:pageSize:filterType:](iOS-api.md#ByteRTCKTVManager-searchmusic-pagenumber-pagesize-filtertype) | 根据关键词搜索歌曲。 |
| [getHotMusic:filterType:](iOS-api.md#ByteRTCKTVManager-gethotmusic-filtertype) | 根据热榜获取每个榜单的歌曲列表。 |
| [getMusicDetail:](iOS-api.md#ByteRTCKTVManager-getmusicdetail) | 获取音乐详细信息。 |
| [downloadMusic:](iOS-api.md#ByteRTCKTVManager-downloadmusic) | 下载音乐。 |
| [downloadLyric:lyricType:](iOS-api.md#ByteRTCKTVManager-downloadlyric-lyrictype) | 下载歌词。 |
| [downloadMidi:](iOS-api.md#ByteRTCKTVManager-downloadmidi) | 下载 MIDI 文件。 |
| [cancelDownload:](iOS-api.md#ByteRTCKTVManager-canceldownload) | 取消下载任务。 |
| [clearCache](iOS-api.md#ByteRTCKTVManager-clearcache) | 清除当前音乐缓存文件，包括音乐音频和歌词。 |
| [setMaxCacheSize:](iOS-api.md#ByteRTCKTVManager-setmaxcachesize) | 设置歌曲文件最大占用的本地缓存。 |
| [getKTVPlayer](iOS-api.md#ByteRTCKTVManager-getktvplayer) | 获取 KTV 播放器。 |
| [playMusic:audioTrackType:audioPlayType:](iOS-api.md#ByteRTCKTVPlayer-playmusic-audiotracktype-audioplaytype) | 播放歌曲。 |
| [pauseMusic:](iOS-api.md#ByteRTCKTVPlayer-pausemusic) | 暂停播放歌曲。 |
| [resumeMusic:](iOS-api.md#ByteRTCKTVPlayer-resumemusic) | 继续播放歌曲。 |
| [stopMusic:](iOS-api.md#ByteRTCKTVPlayer-stopmusic) | 停止播放歌曲。 |
| [seekMusic:position:](iOS-api.md#ByteRTCKTVPlayer-seekmusic-position) | 设置音乐文件的起始播放位置。 |
| [setMusicVolume:volume:](iOS-api.md#ByteRTCKTVPlayer-setmusicvolume-volume) | 设置歌曲播放音量，只能在开始播放后进行设置。 |
| [switchAudioTrackType:](iOS-api.md#ByteRTCKTVPlayer-switchaudiotracktype) | 切换歌曲原唱伴唱。 |
| [setMusicPitch:pitch:](iOS-api.md#ByteRTCKTVPlayer-setmusicpitch-pitch) | 对播放中的音乐设置升降调信息。 |
| [getSingScoringManager](iOS-api.md#ByteRTCVideo-getsingscoringmanager) | 创建 K 歌评分管理接口。 |
| [initSingScoring:singScoringToken:delegate:](iOS-api.md#ByteRTCSingScoringManager-initsingscoring-singscoringtoken-delegate) | 初始化 K 歌评分。 |
| [setSingScoringConfig:](iOS-api.md#ByteRTCSingScoringManager-setsingscoringconfig) | 设置 K 歌评分参数。 |
| [getStandardPitchInfo:](iOS-api.md#ByteRTCSingScoringManager-getstandardpitchinfo) | 获取标准音高数据。 |
| [startSingScoring:scoringInfoInterval:](iOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) | 开始 K 歌评分。 |
| [stopSingScoring](iOS-api.md#ByteRTCSingScoringManager-stopsingscoring) | 停止 K 歌评分。 |
| [getLastSentenceScore](iOS-api.md#ByteRTCSingScoringManager-getlastsentencescore) | 获取上一句的演唱评分。调用 [startSingScoring:scoringInfoInterval:](iOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 开始评分后可以调用该接口。 |
| [getTotalScore](iOS-api.md#ByteRTCSingScoringManager-gettotalscore) | 获取当前演唱总分。调用 [startSingScoring:scoringInfoInterval:](iOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 开始评分后可以调用该接口。 |
| [getAverageScore](iOS-api.md#ByteRTCSingScoringManager-getaveragescore) | 获取当前演唱歌曲的平均分。 |
| [setAudioAlignmentProperty:withMode:](iOS-api.md#ByteRTCVideo-setaudioalignmentproperty-withmode) | 在听众端，设置订阅的所有远端音频流精准对齐后播放。 |

# 回调
## 引擎管理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onWarning:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onwarning) | 发生警告回调。  <br><br/>SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。 |
| [rtcEngine:onError:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onerror) | 发生错误回调。<br><br/>SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。<br><br/>你可能需要干预. |
| [onTokenWillExpire:](iOS-callback#ByteRTCRoomDelegate-ontokenwillexpire) | Token 进房权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken:](iOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 进房权限。 |
| [onPublishPrivilegeTokenWillExpire:](iOS-callback#ByteRTCRoomDelegate-onpublishprivilegetokenwillexpire) | Token 发布权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken:](iOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 发布权限。 |
| [onSubscribePrivilegeTokenWillExpire:](iOS-callback#ByteRTCRoomDelegate-onsubscribeprivilegetokenwillexpire) | Token 订阅权限过期前 30 秒将触发该回调。<br><br/>收到该回调后，你需调用 [updateToken:](iOS-api.md#ByteRTCRoom-updatetoken) 更新 Token 订阅权限有效期。 |

## 房间管理

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) | 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。 |
| [rtcEngine:onCreateRoomStateChanged:errorCode:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode) | 创建房间失败回调。 |
| [rtcRoom:onLeaveRoom:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onleaveroom) | 离开房间成功回调。  <br><br/>用户调用 [leaveRoom](iOS-api.md#ByteRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br> |
| [rtcRoom:onUserJoined:elapsed:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) | 远端可见用户加入房间，或房内不可见用户切换为可见的回调。<br><br/>1. 远端用户调用 [setUserVisibility:](iOS-api.md#ByteRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br><br/>2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br><br/>3. 房间内隐身远端用户调用 [setUserVisibility:](iOS-api.md#ByteRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。  <br><br/>4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br> |
| [rtcRoom:onUserLeave:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) | 远端用户离开房间，或切至不可见时，本地用户会收到此事件 |
| [rtcRoom:onUserVisibilityChanged:errorCode:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onuservisibilitychanged-errorcode) | 用户调用 [setUserVisibility:](iOS-api.md#ByteRTCRoom-setuservisibility) 设置用户可见性的回调。 |
| [rtcRoom:onRoomStats:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstats) | 房间内通话统计信息回调。   <br><br/>用户进房开始通话后，每 2s 收到一次本回调。 |
| [rtcRoom:onSetRoomExtraInfoResult:error:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onsetroomextrainforesult-error) | 调用 [setRoomExtraInfo:value:](iOS-api.md#ByteRTCRoom-setroomextrainfo-value) 结果回调。 |
| [rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onroomextrainfoupdate-value-lastupdateuserid-lastupdatetimems) | 接收到房间附加信息的回调。<br><br/>房间内其他用户调用 [setRoomExtraInfo:value:](iOS-api.md#ByteRTCRoom-setroomextrainfo-value) 设置房间附加信息，收到此回调。<br><br/>另外用户加入房间成功后会收到这个房间全量附加信息 |

## 音频管理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning) | 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。 |
| [rtcEngine:onAudioRouteChanged:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudioroutechanged) | 音频播放路由变化时，收到该回调。 |
| [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) | 音频设备状态回调。提示音频采集、音频播放等设备的状态。 |
| [rtcEngine:onLocalAudioPropertiesReport:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport:](iOS-api.md#ByteRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br><br/>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。 |
| [rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume) | 远端用户进房后，本地调用 [enableAudioPropertiesReport:](iOS-api.md#ByteRTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br><br/>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [rtcEngine:onActiveSpeaker:uid:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid) | 调用 [enableAudioPropertiesReport:](iOS-api.md#ByteRTCVideo-enableaudiopropertiesreport)  后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [rtcEngine:onUserStartAudioCapture:uid:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid) | 房间内的可见用户调用 [startAudioCapture](iOS-api.md#ByteRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。 |
| [rtcEngine:onUserStopAudioCapture:uid:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid) | 房间内的可见用户调用 [stopAudioCapture](iOS-api.md#ByteRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。 |
| [rtcEngine:onStreamSyncInfoReceived:streamType:data:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data) | 音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo:config:](iOS-api.md#ByteRTCVideo-sendstreamsyncinfo-config) 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br> |
| [rtcRoom:onAudioStreamBanned:isBanned:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onaudiostreambanned-isbanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [rtcEngine:onHardwareEchoDetectionResult:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onhardwareechodetectionresult) | 通话前回声检测结果回调。 |
| [rtcEngine:onLocalAudioStateChanged:error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalaudiostatechanged-error) | 本地音频流的状态发生改变时，收到此回调。 |

## 视频管理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onUserStartVideoCapture:uid:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid) | 房间内的可见用户调用 [startVideoCapture](iOS-api.md#ByteRTCVideo-startvideocapture) 开启内部视频采集时，房间中其他用户会收到此回调。 |
| [rtcEngine:onUserStopVideoCapture:uid:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid) | 房间内的可见用户调用 [stopVideoCapture](iOS-api.md#ByteRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。<br><br/>若发布视频数据前未开启采集，房间内所有可见用户会收到此回调。 |
| [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) | 视频设备状态发生改变回调。当设备的视频状态发生改变时，SDK 会触发该回调，提示摄像头视频采集、屏幕视频采集等设备的状态。 |
| [rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodevicewarning-devicetype-devicewarning) | 视频设备警告回调。视频设备包括视频采集设备。 |
| [onFaceDetectResult:](iOS-callback.md#ByteRTCFaceDetectionObserver-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。 <br><br/>调用 [enableFaceDetection:withInterval:withModelPath:](iOS-api#ByteRTCVideoEffect-enablefacedetection-withinterval-withmodelpath) 注册了 [ByteRTCFaceDetectionObserver](iOS-callback.md#bytertcfacedetectionobserver) ，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |
| [rtcEngine:onLocalVideoStateChanged:withStreamState:withStreamError:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalvideostatechanged-withstreamstate-withstreamerror) | 本地视频流的状态发生改变时，收到该事件。 |

## 音视频传输

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [rtcRoom:onAVSyncStateChange:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onavsyncstatechange) | 发布端调用 [setMultiDeviceAVSync:](iOS-api.md#ByteRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。 |
| [rtcEngine:onAudioFrameSendStateChanged:rtcUser:state:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudioframesendstatechanged-rtcuser-state) | 本地音频首帧发送状态发生改变时，收到此回调。 |
| [rtcEngine:onVideoFrameSendStateChanged:rtcUser:state:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideoframesendstatechanged-rtcuser-state) | 本地视频首帧发送状态发生改变时，收到此回调。 |
| [rtcEngine:onAudioFramePlayStateChanged:rtcUser:state:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onaudioframeplaystatechanged-rtcuser-state) | 音频首帧播放状态发生改变时，收到此回调。 |
| [rtcEngine:onVideoFramePlayStateChanged:rtcUser:state:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideoframeplaystatechanged-rtcuser-state) | 视频首帧播放状态发生改变时，收到此回调。 |
| [rtcRoom:onUserPublishStream:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) | 房间内新增远端摄像头/麦克风采集的媒体流的回调。 |
| [rtcRoom:onUserUnpublishStream:type:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [rtcRoom:onForwardStreamStateChanged:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [rtcRoom:onForwardStreamEvent:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [rtcEngine:onSysStats:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onsysstats) | 报告当前设备 cpu 与 memory 使用率，每 2s 触发一次。 |
| [rtcRoom:onLocalStreamStats:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onlocalstreamstats) | 本地流数据统计以及网络质量回调。  <br><br/>本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br><br/>统计信息通过 [ByteRTCLocalStreamStats](iOS-keytype.md#bytertclocalstreamstats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [rtcRoom:onRemoteStreamStats:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onremotestreamstats) | 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br><br/>本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。 |
| [rtcRoom:onNetworkQuality:remoteQualities:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onnetworkquality-remotequalities) | 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。 |
| [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) | 关于订阅媒体流状态改变的回调 |
| [rtcEngine:onRemoteAudioStateChanged:state:reason:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremoteaudiostatechanged-state-reason) | 订阅的远端音频流状态发生改变时，收到此回调。 |
| [rtcEngine:onFirstLocalAudioFrame:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstlocalaudioframe) | 发布音频流时，采集到第一帧音频帧，收到该回调。 |
| [rtcEngine:onFirstRemoteAudioFrame:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe) | 当收到远端流的第一帧音频的时候上报该事件 |
| [rtcEngine:onRemoteVideoStateChanged:withVideoState:withVideoStateReason:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremotevideostatechanged-withvideostate-withvideostatereason) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstlocalvideoframecaptured-withframeinfo) | 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。 |
| [rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframerendered-withframeinfo) | SDK 内部渲染成功远端视频流首帧后，收到此回调。 |
| [rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo) | 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [rtcEngine:onLocalVideoSizeChanged:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlocalvideosizechanged-withframeinfo) | 本地视频大小或旋转信息发生改变时，收到此回调。 |
| [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [rtcRoom:onVideoStreamBanned:isBanned:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onvideostreambanned-isbanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode) | 公共流发布结果回调。<br><br/>调用 [startPushPublicStream:withLayout:](iOS-api.md#ByteRTCVideo-startpushpublicstream-withlayout) <br><br/>接口或直接在服务端启动推公共流功能后，你会通过此回调收到启动结果和推流过程中的错误。 |
| [rtcEngine:onPlayPublicStreamResult:errorCode:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode) | 订阅公共流的结果回调  <br><br/>调用 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream) 接口拉公共流后，你会通过此回调收到启动结果和拉流过程中的错误。 |
| [rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage-andsourcetype) | 回调公共流中包含的 SEI 信息。<br/>调用 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo) | 公共流的首帧视频解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream)。 |
| [rtcEngine:onFirstPublicStreamAudioFrame:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功<br><br/>关于订阅公共流，详见 [startPlayPublicStream:](iOS-api.md#ByteRTCVideo-startplaypublicstream)。 |

## 视频处理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onVideoDenoiseModeChanged:withReason:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onvideodenoisemodechanged-withreason) | 降噪模式状态变更回调。当降噪模式的运行状态发生改变，SDK 会触发该回调，提示用户降噪模式改变后的运行状态及状态发生改变的原因。 |
| [rtcEngine:onRemoteVideoSuperResolutionModeChanged:withMode:withReason:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onremotevideosuperresolutionmodechanged-withmode-withreason) | 远端视频流的超分状态发生改变时，房间内订阅此流的用户会收到该回调。 |

## 自定义流处理

| 回调 | 描述 |
| --- | --- |
| [onStart:](iOS-callback#ByteRTCExternalVideoEncoderEventHandler-onstart) | 提示自定义编码帧可以开始推送的回调。  <br><br/>收到该回调后，你即可调用 [pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:](iOS-api.md#ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe) 向 SDK 推送自定义编码视频帧 |
| [onStop:](iOS-callback.md#ByteRTCExternalVideoEncoderEventHandler-onstop) | 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧 |
| [onRateUpdate:withVideoIndex:withFps:withBitRate:](iOS-callback.md#ByteRTCExternalVideoEncoderEventHandler-onrateupdate-withvideoindex-withfps-withbitrate) | 当自定义编码流的帧率或码率发生变化时，触发该回调 |
| [onRequestKeyFrame:withVideoIndex:](iOS-callback.md#ByteRTCExternalVideoEncoderEventHandler-onrequestkeyframe-withvideoindex) | 提示流发布端需重新生成关键帧的回调 |
| [onActiveVideoLayer:withVideoIndex:withActive:](iOS-callback.md#ByteRTCExternalVideoEncoderEventHandler-onactivevideolayer-withvideoindex-withactive) | 作为自定义编码视频流的发送端，你会在视频流可发送状态发生变化时，收到此回调。<br/>你可以根据此回调的提示，仅对可发送的视频流进行编码，以降低本端视频编码性能消耗。此回调会根据多个因素综合判断触发，包括：本端设备性能和本端网络性能，以及按需订阅场景下，远端用户是否订阅。 |
| [onLocalEncodedVideoFrame:Frame:](iOS-callback#ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame) | 调用 [registerLocalEncodedVideoFrameObserver:](iOS-api.md#ByteRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。 |
| [onRemoteEncodedVideoFrame:withEncodedVideoFrame:](iOS-callback#ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe) | 调用 [registerRemoteEncodedVideoFrameObserver:](iOS-api.md#ByteRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调 |
| [onProcessEarMonitorAudioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessearmonitoraudioframe) | 软件耳返音频数据的回调。你可根据此回调自定义处理音频。<br/>软件耳返音频中包含通过调用 `setVoiceReverbType:` 和 `setVoiceChangerType:` 设置的音频特效。 |
| [onProcessPlayBackAudioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe) | 回调远端音频混音的音频帧地址，供自定义音频处理。 |
| [onProcessRecordAudioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessrecordaudioframe) | 回调本地采集的音频帧地址，供自定义音频处理。 |
| [onProcessRemoteUserAudioFrame:audioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe) | 回调单个远端用户的音频帧地址，供自定义音频处理。 |
| [onProcessScreenAudioFrame:](iOS-callback.md#ByteRTCAudioFrameProcessor-onprocessscreenaudioframe) | 回调屏幕共享的音频帧地址，供自定义音频处理。 |
| [onRecordAudioFrame:](iOS-callback.md#ByteRTCAudioFrameObserver-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame:](iOS-callback.md#ByteRTCAudioFrameObserver-onplaybackaudioframe) | 返回订阅的所有远端用户混音后的音频数据。 |
| [onRemoteUserAudioFrame:audioFrame:](iOS-callback.md#ByteRTCAudioFrameObserver-onremoteuseraudioframe-audioframe) | 返回远端单个用户的音频数据 |
| [onMixedAudioFrame:](iOS-callback.md#ByteRTCAudioFrameObserver-onmixedaudioframe) | 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据 |
| [processVideoFrame:](iOS-callback#ByteRTCVideoProcessorDelegate-processvideoframe) | 获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor:withConfig:](iOS-api.md#ByteRTCVideo-registerlocalvideoprocessor-withconfig) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。 |

## 网络管理

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onperformancealarms-roomid-reason-sourcewanteddata) | 本地未通过 [setPublishFallbackOption:](iOS-api.md#ByteRTCVideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。  <br><br/>本地通过 [setPublishFallbackOption:](iOS-api.md#ByteRTCVideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。  <br> |
| [rtcEngine:onSimulcastSubscribeFallback:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback) | 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。 |
| [rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionresult-quality-rtt-lostrate-bitrate-jitter) | 通话前网络探测结果的回调。  <br><br/>成功调用 [startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:](iOS-api.md#ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [rtcEngine:onNetworkDetectionStopped:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionstopped) | 通话前网络探测结束  <br><br/>以下情况将停止探测并收到一次本回调：<br><br/>1. 当调用 [stopNetworkDetection](iOS-api.md#ByteRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；<br/>2. 当收到远端/本端音频首帧后，停止探测；<br/>3. 当探测超过3分钟后，停止探测；<br/>4. 当探测链路断开一定时间之后，停止探测。 |
| [rtcEngine:onConnectionStateChanged:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onconnectionstatechanged) | SDK 与信令服务器连接状态改变回调。连接状态改变时触发。 |
| [rtcEngine:onNetworkTypeChanged:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onnetworktypechanged) | SDK 当前网络连接类型改变回调。 |
| [rtcEngine:onSEIMessageReceived:andMessage:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage) | 收到通过调用 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](iOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 发送带有 SEI 消息的视频帧时，收到此回调。 |
| [rtcEngine:onEchoTestResult:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onechotestresult) | 关于音视频回路测试结果的回调。 |
| [rtcEngineOnNetworkTimeSynchronized:](iOS-callback#ByteRTCVideoDelegate-rtcengineonnetworktimesynchronized) | 首次调用 [getNetworkTimeInfo](iOS-api.md#ByteRTCVideo-getnetworktimeinfo) 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。 |

## 消息

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onRoomMessageReceived:message:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onroommessagereceived-message) | 收到房间中调用 [sendRoomMessage:](iOS-api.md#ByteRTCRoom-sendroommessage) 发送的广播文本消息时，收到此回调。 |
| [rtcRoom:onRoomBinaryMessageReceived:message:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onroombinarymessagereceived-message) | 收到房间内广播二进制消息的回调。<br><br/>房间内其他用户调用 [sendRoomBinaryMessage:](iOS-api.md#ByteRTCRoom-sendroombinarymessage) 发送的广播二进制消息时，收到此回调。 |
| [rtcRoom:onUserMessageReceived:message:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onusermessagereceived-message) | 收到来自房间中其他用户通过 [sendUserMessage:message:config:](iOS-api.md#ByteRTCRoom-sendusermessage-message-config) 发来的点对点文本消息时，会收到此回调。 |
| [rtcRoom:onUserBinaryMessageReceived:message:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onuserbinarymessagereceived-message) | 收到来自房间中其他用户通过 [sendUserBinaryMessage:message:config:](iOS-api.md#ByteRTCRoom-senduserbinarymessage-message-config) 发来的点对点二进制消息时，会收到此回调。 |
| [rtcRoom:onUserMessageSendResult:error:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error) | 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。 |
| [rtcRoom:onRoomMessageSendResult:error:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error) | 调用 [sendRoomMessage:](iOS-api.md#ByteRTCRoom-sendroommessage) 或 [sendRoomBinaryMessage:](iOS-api.md#ByteRTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [rtcEngine:onLoginResult:errorCode:elapsed:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed) | 登录结果回调 |
| [rtcEngine:onLogout:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onlogout) | 登出结果回调 |
| [rtcEngine:onServerParamsSetResult:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onserverparamssetresult) | 设置应用服务器参数的返回结果 |
| [rtcEngine:onGetPeerOnlineStatus:status:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-ongetpeeronlinestatus-status) | 查询对端或本端用户登录状态的返回结果 |
| [rtcEngine:onUserMessageReceivedOutsideRoom:message:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onusermessagereceivedoutsideroom-message) | 收到房间外用户调用 [sendUserMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-sendusermessageoutsideroom-message-config) 发来的文本消息时，会收到此回调 |
| [rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onuserbinarymessagereceivedoutsideroom-message) | 收到房间外用户调用 [sendUserBinaryMessageOutsideRoom:message:config:](iOS-api.md#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) 发来的二进制消息时，会收到此回调。 |
| [rtcEngine:onUserMessageSendResultOutsideRoom:error:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error) | 给房间外指定的用户发送消息的回调 |
| [rtcEngine:onServerMessageSendResult:error:message:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onservermessagesendresult-error-message) | 给应用服务器发送消息的回调。 |
| [rtcEngine:onSEIStreamUpdate:eventType:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onseistreamupdate-eventtype) | 黑帧视频流发布状态回调。  <br><br/>在语音通话场景下，本地用户调用 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](iOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br><br/>你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。 |

## CDN 推流

| 回调 | 描述 |
| --- | --- |
| [onStreamPushEvent:taskId:error:](iOS-callback.md#ByteRTCPushSingleStreamToCDNObserver-onstreampushevent-taskid-error) | 单流转推直播状态回调 |

## 混音

| 回调 | 描述 |
| --- | --- |
| [onFrame:audioFrame:](iOS-callback.md#ByteRTCMediaPlayerAudioFrameObserver-onframe-audioframe) | 当本地音频文件混音时，回调播放的音频帧。 |
| [onMediaPlayerStateChanged:state:error:](iOS-callback.md#ByteRTCMediaPlayerEventHandler-onmediaplayerstatechanged-state-error) | 播放状态改变时回调。 |
| [onMediaPlayerPlayingProgress:progress:](iOS-callback#ByteRTCMediaPlayerEventHandler-onmediaplayerplayingprogress-progress) | 播放进度周期性回调。回调周期通过 [setProgressInterval:](iOS-api.md#ByteRTCMediaPlayer-setprogressinterval) 设置。 |
| [onReadData:bufferSize:](iOS-callback#ByteRTCMediaPlayerCustomSourceProvider-onreaddata-buffersize) | 调用 [openWithCustomSource:config:](iOS-api.md#ByteRTCMediaPlayer-openwithcustomsource-config) 接口播放用户传入的内存音频数据时，会触发此回调，用户需要写入音频数据。 |
| [onSeek:whence:](iOS-callback#ByteRTCMediaPlayerCustomSourceProvider-onseek-whence) | 根据设置好的内存音频数据的读取位置和读取偏移量对音频数据进行偏移，以便 SDK 读取和分析音频数据。 <br><br/>在调用 [openWithCustomSource:config:](iOS-api.md#ByteRTCMediaPlayer-openwithcustomsource-config) 接口传入内存音频数据，或者调用 [setPosition:position:](iOS-api.md#ByteRTCAudioEffectPlayer-setposition-position) 设置了音频数据的起始播放位置后，SDK 会对音频数据进行读取和分析，此时会触发该回调，你需要根据参数中设置的起始读取位置和偏移量进行操作。 |

## 屏幕分享

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onUserPublishScreen:type:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) | 房间内新增远端屏幕共享音视频流的回调。 |
| [rtcRoom:onUserUnpublishScreen:type:reason:](iOS-callback.md#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) | 房间内远端屏幕共享音视频流移除的回调。 |
| [rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onscreenvideoframesendstatechanged-rtcuser-state) | 屏幕共享流的视频首帧发送状态发生改变时，收到此回调。 |
| [rtcEngine:onScreenVideoFramePlayStateChanged:rtcUser:state:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onscreenvideoframeplaystatechanged-rtcuser-state) | 屏幕共享流视频首帧播放状态发生改变时，收到此回调。 |

## 安全与加密

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onCloudProxyConnected:](iOS-callback#ByteRTCVideoDelegate-rtcengine-oncloudproxyconnected) | 调用 [startCloudProxy:](iOS-api.md#ByteRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onEncryptData:](iOS-callback.md#ByteRTCEncryptHandler-onencryptdata) | 自定义加密。  <br><br/>使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br><br/>暂不支持对原始音视频帧进行加密。 |
| [onDecryptData:](iOS-callback.md#ByteRTCEncryptHandler-ondecryptdata) | 自定义解密。  <br><br/>对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData:](iOS-callback.md#ByteRTCEncryptHandler-onencryptdata)。 |

## 高级功能

| 回调 | 描述 |
| --- | --- |
| [rtcEngine:onExtensionAccessError:msg:](iOS-callback.md#ByteRTCVideoDelegate-rtcengine-onextensionaccesserror-msg) | 当访问插件失败时，收到此回调。<br/>RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。 |
| [rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info) | 获取本地录制状态回调。  <br><br/>该回调由 [startFileRecording:withRecordingConfig:type:](iOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 或 [stopFileRecording:](iOS-api.md#ByteRTCVideo-stopfilerecording) 触发。 |
| [rtcEngine:onRecordingProgressUpdate:process:recording_info:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info) | 本地录制进度回调。  <br><br/>该回调由 [startFileRecording:withRecordingConfig:type:](iOS-api.md#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。 |
| [rtcEngine:onAudioRecordingStateUpdate:error_code:](iOS-callback#ByteRTCVideoDelegate-rtcengine-onaudiorecordingstateupdate-error_code) | 调用 [startAudioRecording:](iOS-api.md#ByteRTCVideo-startaudiorecording) 或者 [stopAudioRecording](iOS-api.md#ByteRTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。 |
| [onTakeLocalSnapshotResult:streamIndex:image:errorCode:](iOS-callback#ByteRTCVideoSnapshotCallbackDelegate-ontakelocalsnapshotresult-streamindex-image-errorcode) | 调用 [takeLocalSnapshot:callback:](iOS-api.md#ByteRTCVideo-takelocalsnapshot-callback) 截取视频画面时，收到此回调。 |
| [onTakeRemoteSnapshotResult:streamKey:image:errorCode:](iOS-callback#ByteRTCVideoSnapshotCallbackDelegate-ontakeremotesnapshotresult-streamkey-image-errorcode) | 调用 [takeRemoteSnapshot:callback:](iOS-api.md#ByteRTCVideo-takeremotesnapshot-callback) 截取视频画面时，收到此回调。 |

## 字幕翻译服务

| 回调 | 描述 |
| --- | --- |
| [rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage) | 字幕状态发生改变回调。 <br><br/>当用户调用 [startSubtitle:](iOS-api.md#ByteRTCRoom-startsubtitle) 和 [stopSubtitle](iOS-api.md#ByteRTCRoom-stopsubtitle) 使字幕状态发生改变或出现错误时，触发该回调。 |
| [rtcRoom:onSubtitleMessageReceived:](iOS-callback#ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived) | 字幕相关内容回调。 <br><br/>当用户调用 [startSubtitle:](iOS-api.md#ByteRTCRoom-startsubtitle) 后会收到此回调，通知字幕的相关信息。 |

## 在线 KTV

| 回调 | 描述 |
| --- | --- |
| [ktvManager:onDownloadSuccess:downloadResult:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadsuccess-downloadresult) | 下载成功回调。 |
| [ktvManager:onDownloadMusicProgress:progress:](iOS-callback.md#ByteRTCKTVManagerDelegate-ktvmanager-ondownloadmusicprogress-progress) | 歌曲文件下载进度回调。 |
| [ktvPlayer:onPlayProgress:progress:](iOS-callback.md#ByteRTCKTVPlayerDelegate-ktvplayer-onplayprogress-progress) | 音乐播放进度回调。 |
| [onCurrentScoringInfo:](iOS-callback#ByteRTCSingScoringDelegate-oncurrentscoringinfo) | 实时评分信息回调。调用 [startSingScoring:scoringInfoInterval:](iOS-api.md#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 后，会收到该回调。 |