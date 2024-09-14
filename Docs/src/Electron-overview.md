## 引擎管理

| 方法 | 描述 |
| :-- | :-- |
| [createRTCVideo](Electron-api.md#rtcvideo-creatertcvideo) | 创建引擎对象 |
| [destroyRTCVideo](Electron-api.md#rtcvideo-destroyrtcvideo) | 销毁引擎实例对象 |
| [feedback](Electron-api.md#rtcvideo-feedback) | 将用户反馈的问题上报到 RTC |
| [setBusinessId](Electron-api.md#rtcvideo-setbusinessid) | 设置业务标识参数 |
| [onLogReport](Electron-event.md#rtcvideocallback-onlogreport) | 端监控日志回调。当产生一个端监控事件时触发该回调。 |
| [onWarning](Electron-event.md#rtcvideocallback-onwarning) | 当内部发生警告事件时触发该回调 |
| [onError](Electron-event.md#rtcvideocallback-onerror) | 当内部发生不可逆转错误时触发该回调 |
| [onLicenseWillExpire](Electron-event.md#rtcvideocallback-onlicensewillexpire) | license过期时间提醒 |
| [onSysStats](Electron-event.md#rtcvideocallback-onsysstats) | 周期性地发出回调，报告当前cpu与memory使用率 |
| `static` [getSDKVersion](Electron-api.md#static-rtcvideo-getsdkversion) | 获取当前 SDK 版本信息 |
| `static` [setLogConfig](Electron-api.md#static-rtcvideo-setlogconfig) | 设置日志文件 |
| `static` [getErrorDescription](Electron-api.md#static-rtcvideo-geterrordescription) | 获取错误码的描述 |
| `static` [getCurrentProcessId](Electron-api.md#static-rtcvideo-getcurrentprocessid) | 获取加载引擎进程的 ID 方便调试 |
| `static` [setRenderType](Electron-api.md#static-rtcvideo-setrendertype) | 设置渲染类型 |
| `static` [getTimestampMs](Electron-api.md#static-rtcvideo-gettimestampms) | 获取时间戳, 单位毫秒 |
| `static` [getTimestampUs](Electron-api.md#static-rtcvideo-gettimestampus) | 获取时间戳, 单位微秒 |



## 房间管理

| 方法 | 描述 |
| :-- | :-- |
| [createRTCRoom](Electron-api.md#rtcvideo-creatertcroom) | 创建房间 |
| [onCreateRoomStateChanged](Electron-event.md#rtcvideocallback-oncreateroomstatechanged) | 创建房间失败回调。 |
| [onRoomStats](Electron-event.md#rtcroomcallback-onroomstats) | 房间通话统计信息回调。<br>用户进房开始通话后，每 2s 收到一次本回调。 |
| [destroy](Electron-api.md#rtcroom-destroy) | 退出并销毁房间。 |
| [getRoomId](Electron-api.md#rtcroom-getroomid) | 获取房间 ID |
| [onRoomStateChanged](Electron-event.md#rtcroomcallback-onroomstatechanged) | 房间状态改变回调，加入房间、离开房间、发生房间相关的警告或错误时会收到此回调。 |
| [joinRoom](Electron-api.md#rtcroom-joinroom) | 加入房间。 |
| [onUserJoined](Electron-event.md#rtcroomcallback-onuserjoined) | 可见用户加入房间，或房内不可见用户切换为可见的回调。<br>1.远端可见用户调用 `setUserVisibility` 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。<br>2.远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。<br>3.房间内不可见远端用户调用 `setUserVisibility` 方法切换至可见时，房间内其他用户将收到该事件。<br>4.新进房用户也会收到进房前已在房内的可见角色用户的进房回调通知。 |
| [leaveRoom](Electron-api.md#rtcroom-leaveroom) | 离开房间。 |
| [onLeaveRoom](Electron-event.md#rtcroomcallback-onleaveroom) | 离开房间成功回调。 |
| [onUserLeave](Electron-event.md#rtcroomcallback-onuserleave) | 远端用户离开房间，或切至不可见时，本地用户会收到此事件 |
| [setRoomExtraInfo](Electron-api.md#rtcroom-setroomextrainfo) | 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。 |
| [onSetRoomExtraInfoResult](Electron-event#rtcroomcallback-onsetroomextrainforesult) | 调用 [setRoomExtraInfo](Electron-api.md#rtcroom-setroomextrainfo) 设置房间附加信息结果的回调。 |
| [onRoomExtraInfoUpdate](Electron-event#rtcroomcallback-onroomextrainfoupdate) | 接收同一房间内，其他用户调用 [setRoomExtraInfo](Electron-api.md#rtcroom-setroomextrainfo) 设置的房间附加信息的回调。 |
| [setUserVisibility](Electron-api.md#rtcroom-setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。 |
| [onUserVisibilityChanged](Electron-event#rtcroomcallback-onuservisibilitychanged) | 用户调用 [setUserVisibility](Electron-api.md#rtcroom-setuservisibility) 设置用户可见性的回调。 |
| [updateToken](Electron-api.md#rtcroom-updatetoken) | 更新 Token。Token 中同时包含进房、发布和订阅权限，各权限有一定的有效期，并且到期前 30 秒会触发回调，提示用户更新 Token 相关权限。此时需要重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。 |
| [onTokenWillExpire](Electron-event.md#rtcroomcallback-ontokenwillexpire) | 当 SDK 检测到 Token 的进房权限将在 30 秒内过期时，触发该回调。 |
| [onPublishPrivilegeTokenWillExpire](Electron-event.md#rtcroomcallback-onpublishprivilegetokenwillexpire) | Token 发布权限过期前 30 秒将触发该回调。 |
| [onSubscribePrivilegeTokenWillExpire](Electron-event.md#rtcroomcallback-onsubscribeprivilegetokenwillexpire) | Token 订阅权限过期前 30 秒将触发该回调。 |



## 音频管理

| 方法 | 描述 |
| :-- | :-- |
| [enumerateAudioPlaybackDevices](Electron-api#rtcvideo-enumerateaudioplaybackdevices) | 获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 [`onAudioDeviceStateChanged`](Electron-event.md#rtcvideocallback-onaudiodevicestatechanged) 回调通知，然后需要重新调用本接口以获得新的设备列表。 |
| [enumerateAudioCaptureDevices](Electron-api.md#rtcvideo-enumerateaudiocapturedevices) | 获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。 |
| [setAudioPlaybackDevice](Electron-api.md#rtcvideo-setaudioplaybackdevice) | 设置音频播放设备。 |
| [setAudioCaptureDevice](Electron-api.md#rtcvideo-setaudiocapturedevice) | 设置音频采集设备。 |
| [getAudioPlaybackDevice](Electron-api.md#rtcvideo-getaudioplaybackdevice) | 获取当前音频播放设备 ID。 |
| [getAudioCaptureDevice](Electron-api.md#rtcvideo-getaudiocapturedevice) | 获取当前音频采集设备 ID。 |
| [enableFilterSilentDevice](Electron-api.md#rtcvideo-enablefiltersilentdevice) | 开启/关闭过滤无声设备功能。 |
| [followSystemPlaybackDevice](Electron-api.md#rtcvideo-followsystemplaybackdevice) | 设置音频播放路由是否跟随系统。 |
| [followSystemCaptureDevice](Electron-api.md#rtcvideo-followsystemcapturedevice) | 设置音频采集路由是否跟随系统。 |
| [onAudioDeviceWarning](Electron-event.md#rtcvideocallback-onaudiodevicewarning) | 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。 |
| [onAudioDeviceStateChanged](Electron-event.md#rtcvideocallback-onaudiodevicestatechanged) | 音频设备状态回调。提示音频采集、音频播放等设备设备的状态。 |
| [setAudioPlaybackDeviceVolume](Electron-api.md#rtcvideo-setaudioplaybackdevicevolume) | 设置当前音频播放设备音量 |
| [getAudioPlaybackDeviceVolume](Electron-api.md#rtcvideo-getaudioplaybackdevicevolume) | 获取当前音频播放设备音量 |
| [onAudioStreamBanned](Electron-event.md#rtcroomcallback-onaudiostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [muteAudioCapture](Electron-api.md#rtcvideo-muteaudiocapture) | 设置是否将录音信号静音（不改变本端硬件）。 |
| [setAudioCaptureDeviceVolume](Electron-api.md#rtcvideo-setaudiocapturedevicevolume) | 设置当前音频采集设备音量 |
| [getAudioCaptureDeviceVolume](Electron-api.md#rtcvideo-getaudiocapturedevicevolume) | 获取当前音频采集设备音量 |
| [setAudioPlaybackDeviceMute](Electron-api.md#rtcvideo-setaudioplaybackdevicemute) | 设置当前音频播放设备静音状态，默认为非静音。 |
| [getAudioPlaybackDeviceMute](Electron-api.md#rtcvideo-getaudioplaybackdevicemute) | 获取当前音频播放设备是否静音的信息。 |
| [setAudioCaptureDeviceMute](Electron-api.md#rtcvideo-setaudiocapturedevicemute) | 设置当前音频采集设备静音状态，默认为非静音。 |
| [getAudioCaptureDeviceMute](Electron-api.md#rtcvideo-getaudiocapturedevicemute) | 获取当前音频采集设备是否静音的信息。 |
| [onAudioDeviceVolumeChanged](Electron-event.md#rtcvideocallback-onaudiodevicevolumechanged) | 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。 |
| [startAudioPlaybackDeviceTest](Electron-api.md#rtcvideo-startaudioplaybackdevicetest) | 启动音频播放设备测试。  该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。 |
| [stopAudioPlaybackDeviceTest](Electron-api.md#rtcvideo-stopaudioplaybackdevicetest) | 停止音频播放设备测试。 |
| [initAudioPlaybackDeviceForTest](Electron-api.md#rtcvideo-initaudioplaybackdevicefortest) | 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。 |
| [enableVocalInstrumentBalance](Electron-api.md#rtcvideo-enablevocalinstrumentbalance) | 开启/关闭音量均衡功能。 |
| [initAudioCaptureDeviceForTest](Electron-api.md#rtcvideo-initaudiocapturedevicefortest) | 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。 |
| [setCaptureVolume](Electron-api.md#rtcvideo-setcapturevolume) | 调节音频采集音量 |
| [setPlaybackVolume](Electron-api.md#rtcvideo-setplaybackvolume) | 调节本地播放的所有远端用户音频混音后的音量，混音内容包括远端人声、音乐、音效等。播放音频前或播放音频时，你都可以使用此接口设定播放音量。 |
| [setRemoteAudioPlaybackVolume](Electron-api.md#rtcvideo-setremoteaudioplaybackvolume) | 调节来自远端用户的音频播放音量 |
| [onStreamSyncInfoReceived](Electron-event.md#rtcvideocallback-onstreamsyncinforeceived) | 音频流同步信息回调。可以通过此回调，在远端用户调用 `sendStreamSyncInfo` 发送音频流同步消息后，收到远端发送的音频流同步信息。 |
| [setRemoteRoomAudioPlaybackVolume](Electron-api.md#rtcroom-setremoteroomaudioplaybackvolume) | 调节某个房间内所有远端用户的音频播放音量。 |
| [enableAudioPropertiesReport](Electron-api.md#rtcvideo-enableaudiopropertiesreport) | 启用音频信息提示。 |
| [onLocalAudioPropertiesReport](Electron-event.md#rtcvideocallback-onlocalaudiopropertiesreport) | 调用 `enableAudioPropertiesReport` 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。 |
| [onRemoteAudioPropertiesReport](Electron-event.md#rtcvideocallback-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 `enableAudioPropertiesReport`，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。 |
| [onActiveSpeaker](Electron-event.md#rtcvideocallback-onactivespeaker) | 调用 `enableAudioPropertiesReport` 后，根据设置的 config.interval，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [onUserStartAudioCapture](Electron-event.md#rtcvideocallback-onuserstartaudiocapture) | 房间内的用户调用 `startAudioCapture` 开启音频采集时，房间内其他用户会收到此回调。 |
| [startAudioCapture](Electron-api.md#rtcvideo-startaudiocapture) | 开启内部音频采集。默认为关闭状态。 |
| [onUserStopAudioCapture](Electron-event.md#rtcvideocallback-onuserstopaudiocapture) | 房间内的用户调用 `stopAudioCapture` 关闭音频采集时，房间内其他用户会收到此回调。 |
| [stopAudioCapture](Electron-api.md#rtcvideo-stopaudiocapture) | 关闭内部音频采集。默认为关闭状态。 |
| [setAudioProfile](Electron-api.md#rtcvideo-setaudioprofile) | 设置音质档位。 |
| [startAudioDeviceRecordTest](Electron-api.md#rtcvideo-startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。 |
| [stopAudioDeviceRecordAndPlayTest](Electron-api.md#rtcvideo-stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。 |
| [stopAudioDevicePlayTest](Electron-api.md#rtcvideo-stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Electron-api.md#rtcvideo-startaudiodevicerecordtest) 开始的音频播放设备测试。 |
| [enableExternalSoundCard](Electron-api.md#rtcvideo-enableexternalsoundcard) | 启用匹配外置声卡的音频处理模式 |
| [enableAGC](Electron-api.md#rtcvideo-enableagc) | 打开/关闭 AGC(Automatic Gain Control) 自动增益控制功能。开启该功能后，SDK 会自动调节麦克风的采集音量，确保音量稳定。 |
| [startHardwareEchoDetection](Electron-api.md#rtcvideo-starthardwareechodetection) | 开启通话前回声检测 |
| [stopHardwareEchoDetection](Electron-api.md#rtcvideo-stophardwareechodetection) | 停止通话前回声检测 |
| [onAudioPlaybackDeviceTestVolume](Electron-event.md#rtcvideocallback-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onHardwareEchoDetectionResult](Electron-event.md#rtcvideocallback-onhardwareechodetectionresult) | 通话前回声检测结果回调。 |
| [setAudioSelectionConfig](Electron-api.md#rtcroom-setaudioselectionconfig) | 设置本端发布流在音频选路中的优先级。 |



## 视频管理

| 方法 | 描述 |
| :-- | :-- |
| [startVideoCapture](Electron-api.md#rtcvideo-startvideocapture) | 开启内部视频采集。默认为关闭状态。 |
| [stopVideoCapture](Electron-api.md#rtcvideo-stopvideocapture) | 关闭内部视频采集。默认为关闭状态。 |
| [onUserStartVideoCapture](Electron-event.md#rtcvideocallback-onuserstartvideocapture) | 房间内的用户调用 `startVideoCapture` 开启视频采集时，房间内其他用户会收到此回调。 |
| [onUserStopVideoCapture](Electron-event.md#rtcvideocallback-onuserstopvideocapture) | 房间内的用户调用 `stopVideoCapture` 关闭视频采集时，房间内其他用户会收到此回调。 |
| [setVideoCaptureConfig](Electron-api.md#rtcvideo-setvideocaptureconfig) | 设置 RTC SDK 内部采集时的视频采集参数。指定视频采集参数包括模式、分辨率、帧率。 |
| [setupLocalScreen](Electron-api.md#rtcvideo-setuplocalscreen) | 为本地屏幕共享流绑定视图，实现预览 |
| [removeLocalScreen](Electron-api.md#rtcvideo-removelocalscreen) | 解绑屏幕共享流已绑定的视图 |
| [setVideoEncoderConfig](Electron-api.md#rtcvideo-setvideoencoderconfig) | 视频发布端设置推送多路流时各路流的参数，包括最大分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [setupRemoteScreen](Electron-api.md#rtcvideo-setupremotescreen) | 为远端屏幕共享流绑定本地视图 |
| [removeRemoteScreen](Electron-api.md#rtcvideo-removeremotescreen) | 解绑远端屏幕共享流已绑定的本地视图 |
| [enumerateVideoCaptureDevices](Electron-api.md#rtcvideo-enumeratevideocapturedevices) | 获取当前系统内视频采集设备列表。 |
| [setVideoCaptureDevice](Electron-api.md#rtcvideo-setvideocapturedevice) | 设置当前视频采集设备 |
| [getVideoCaptureDevice](Electron-api.md#rtcvideo-getvideocapturedevice) | 获取当前 SDK 正在使用的视频采集设备 ID |
| [onVideoDeviceStateChanged](Electron-event.md#rtcvideocallback-onvideodevicestatechanged) | 视频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。 |
| [onVideoDeviceWarning](Electron-event.md#rtcvideocallback-onvideodevicewarning) | 视频设备警告回调，包括视频采集设备等。 |
| [setupLocalVideo](Electron-api.md#rtcvideo-setuplocalvideo) | 设置本地视频渲染时使用的视图，并设置渲染模式。 |
| [setMaxVideoEncoderConfig](Electron-api.md#rtcvideo-setmaxvideoencoderconfig) | 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。 |
| [removeLocalVideo](Electron-api.md#rtcvideo-removelocalvideo) | 解绑本地视频流已绑定的渲染视图 |
| [setupRemoteVideo](Electron-api.md#rtcvideo-setupremotevideo) | 为远端视频流绑定本地渲染视图，并设置渲染模式。 |
| [onFirstLocalVideoFrameCaptured](Electron-event.md#rtcvideocallback-onfirstlocalvideoframecaptured) | 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。 |
| [removeRemoteVideo](Electron-api.md#rtcvideo-removeremotevideo) | 解绑指定远端视频流已绑定的本地视图 |
| [removeAllRemoteVideo](Electron-api.md#rtcvideo-removeallremotevideo) | 解绑所有已绑定本地视图的指定远端视频流 |
| [onLocalVideoStateChanged](Electron-event.md#rtcvideocallback-onlocalvideostatechanged) | 本地视频流的状态发生改变时，收到该事件。 |



## 音视频传输

| 方法 | 描述 |
| :-- | :-- |
| [publishStream](Electron-api.md#rtcroom-publishstream) | 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流 |
| [unpublishStream](Electron-api.md#rtcroom-unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
| [setDummyCaptureImagePath](Electron-api.md#rtcvideo-setdummycaptureimagepath) | 摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。可重复调用该接口来更新图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。 |
| [subscribeStream](Electron-api.md#rtcroom-subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项 |
| [unsubscribeStream](Electron-api.md#rtcroom-unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。该方法对自动订阅和手动订阅模式均适用。 |
| [subscribeAllStreams](Electron-api.md#rtcroom-subscribeallstreams) | 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。 |
| [unsubscribeAllStreams](Electron-api.md#rtcroom-unsubscribeallstreams) | 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。 |
| [onStreamStateChanged](Electron-event.md#rtcroomcallback-onstreamstatechanged) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [onRemoteAudioStateChanged](Electron-event.md#rtcvideocallback-onremoteaudiostatechanged) | 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。 |
| [onUserPublishStream](Electron-event.md#rtcroomcallback-onuserpublishstream) | 房间内新增远端麦克风采集的音频流的回调。 |
| [onUserUnpublishStream](Electron-event.md#rtcroomcallback-onuserunpublishstream) | 房间内远端麦克风采集的音频流移除的回调。 |
| [onStreamSubscribed](Electron-event.md#rtcroomcallback-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onFirstLocalAudioFrame](Electron-event.md#rtcvideocallback-onfirstlocalaudioframe) | 本地采集到第一帧音频帧时，收到该回调 |
| [onFirstRemoteAudioFrame](Electron-event.md#rtcvideocallback-onfirstremoteaudioframe) | 收到房间内每一路音频流的第一帧时，收到该回调。 |
| [onAudioFrameSendStateChanged](Electron-event.md#rtcvideocallback-onaudioframesendstatechanged) | 音频首帧发送状态改变回调 |
| [onVideoFrameSendStateChanged](Electron-event.md#rtcvideocallback-onvideoframesendstatechanged) | 视频首帧发送状态改变回调 |
| [onAudioFramePlayStateChanged](Electron-event.md#rtcvideocallback-onaudioframeplaystatechanged) | 音频首帧播放状态改变回调 |
| [onVideoFramePlayStateChanged](Electron-event.md#rtcvideocallback-onvideoframeplaystatechanged) | 视频首帧播放状态改变回调 |
| [onLocalStreamStats](Electron-event.md#rtcroomcallback-onlocalstreamstats) | 反映通话中本地设备发送音/视频流的统计信息以及网络状况的回调。<br>本地用户发布音视频流成功后，每隔 2s 收到此回调。 |
| [onRemoteStreamStats](Electron-event.md#rtcroomcallback-onremotestreamstats) | 反映通话中本地设备接收订阅的远端音/视频流的统计信息以及网络状况的回调。每隔 2s 收到此回调。 |
| [onStreamSubscribed](Electron-event.md#rtcvideocallback-onstreamsubscribed) | 当订阅一个流成功的时候回调该事件 |
| [onNetworkQuality](Electron-event.md#rtcroomcallback-onnetworkquality) | 加入房间后， 以 2 秒 1 次的频率，报告用户的网络质量信息 |
| [onLocalVideoSizeChanged](Electron-event.md#rtcvideocallback-onlocalvideosizechanged) | 本地视频大小或旋转配置发生改变时，收到此回调。 |
| [onRemoteVideoSizeChanged](Electron-event.md#rtcvideocallback-onremotevideosizechanged) | 远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onRemoteVideoStateChanged](Electron-event.md#rtcvideocallback-onremotevideostatechanged) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [onFirstRemoteVideoFrameRendered](Electron-event.md#rtcvideocallback-onfirstremotevideoframerendered) | 第一帧远端视频流在视图上渲染成功后，收到此回调。 |
| [onVideoStreamBanned](Electron-event.md#rtcroomcallback-onvideostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [onFirstRemoteVideoFrameDecoded](Electron-event.md#rtcvideocallback-onfirstremotevideoframedecoded) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [startForwardStreamToRooms](Electron-api.md#rtcroom-startforwardstreamtorooms) | 开始跨房间转发媒体流。 |
| [stopForwardStreamToRooms](Electron-api.md#rtcroom-stopforwardstreamtorooms) | 停止跨房间媒体流转发。 |
| [updateForwardStreamToRooms](Electron-api.md#rtcroom-updateforwardstreamtorooms) | 更新跨房间媒体流转发信息。 |
| [pauseForwardStreamToAllRooms](Electron-api.md#rtcroom-pauseforwardstreamtoallrooms) | 暂停跨房间媒体流转发。 |
| [resumeForwardStreamToAllRooms](Electron-api.md#rtcroom-resumeforwardstreamtoallrooms) | 恢复跨房间媒体流转发。 |
| [pauseAllSubscribedStream](Electron-api.md#rtcroom-pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
| [resumeAllSubscribedStream](Electron-api.md#rtcroom-resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
| [onForwardStreamStateChanged](Electron-event.md#rtcroomcallback-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [onForwardStreamEvent](Electron-event.md#rtcroomcallback-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [setMultiDeviceAVSync](Electron-api.md#rtcroom-setmultideviceavsync) | 设置发流端音画同步。 |
| [onAVSyncStateChange](Electron-event.md#rtcroomcallback-onavsyncstatechange) | 发布端调用 `setMultiDeviceAVSync` 后音视频同步状态发生改变时，会收到此回调。 |



## 视频处理

| 方法 | 描述 |
| :-- | :-- |
| [setLocalVideoMirrorType](Electron-api.md#rtcvideo-setlocalvideomirrortype) | 为采集到的视频流开启镜像 |
| [setVideoWatermark](Electron-api.md#rtcvideo-setvideowatermark) | 在指定视频流上添加水印。 |
| [clearVideoWatermark](Electron-api.md#rtcvideo-clearvideowatermark) | 移除指定视频流的水印。 |
| [enableEffectBeauty](Electron-api.md#rtcvideo-enableeffectbeauty) | 开启/关闭基础美颜 |
| [setBeautyIntensity](Electron-api.md#rtcvideo-setbeautyintensity) | 调整基础美颜强度 |
| [initCVResource](Electron-api.md#rtcvideo-initcvresource) | 视频特效许可证检查 |
| [enableVideoEffect](Electron-api.md#rtcvideo-enablevideoeffect) | 开启高级美颜、滤镜等视频特效。 |
| [disableVideoEffect](Electron-api.md#rtcvideo-disablevideoeffect) | 关闭视频特效。 |
| [getAuthMessage](Electron-api.md#rtcvideo-getauthmessage) | 从 CV SDK 获取授权消息，用于获取在线许可证。 |
| [setEffectNodes](Electron-api.md#rtcvideo-seteffectnodes) | 设置视频特效素材包，支持同时设置多个素材包 |
| [updateEffectNode](Electron-api.md#rtcvideo-updateeffectnode) | 设置特效强度 |
| [setColorFilter](Electron-api.md#rtcvideo-setcolorfilter) | 设置颜色滤镜 |
| [setColorFilterIntensity](Electron-api.md#rtcvideo-setcolorfilterintensity) | 设置已启用颜色滤镜的强度 |
| [enableVirtualBackground](Electron-api.md#rtcvideo-enablevirtualbackground) | 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。 |
| [disableVirtualBackground](Electron-api.md#rtcvideo-disablevirtualbackground) | 关闭虚拟背景。 |
| [setVideoCaptureRotation](Electron-api.md#rtcvideo-setvideocapturerotation) | 设置本端采集的视频帧的旋转角度。当外接摄像头倒置或者倾斜安装时，调用本接口进行调整。 |
| [setVideoDigitalZoomConfig](Electron-api.md#rtcvideo-setvideodigitalzoomconfig) | 设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。 |
| [setVideoDigitalZoomControl](Electron-api.md#rtcvideo-setvideodigitalzoomcontrol) | 控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。 |
| [startVideoDigitalZoomControl](Electron-api.md#rtcvideo-startvideodigitalzoomcontrol) | 开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。 |
| [setLowLightAdjusted](Electron-api.md#rtcvideo-setlowlightadjusted) | 设置视频暗光增强模式。对于光线不足、照明不均匀或背光等场景下推荐开启，可有效改善画面质量。 |
| [enableFaceDetection](Electron-api.md#rtcvideo-enablefacedetection) | 开启人脸识别功能，并设置人脸检测结果回调观察者。 |
| [disableFaceDetection](Electron-api.md#rtcvideo-disablefacedetection) | 关闭人脸识别功能。 |
| [onFaceDetectResult](Electron-event.md#rtcvideocallback-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。<br>调用 `enableFaceDetection` 注册了回调，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |
| [stopVideoDigitalZoomControl](Electron-api.md#rtcvideo-stopvideodigitalzoomcontrol) | 停止本地摄像头持续数码变焦。 |



## 音频处理

| 方法 | 描述 |
| :-- | :-- |
| [setVoiceChangerType](Electron-api.md#rtcvideo-setvoicechangertype) | 设置变声特效类型 |
| [setVoiceReverbType](Electron-api.md#rtcvideo-setvoicereverbtype) | 设置混响特效类型 |
| [setLocalVoicePitch](Electron-api.md#rtcvideo-setlocalvoicepitch) | 开启本地语音变调功能，多用于 K 歌场景。使用该方法，你可以对本地语音的音调进行升调或降调等调整。 |
| [setLocalVoiceReverbParam](Electron-api.md#rtcvideo-setlocalvoicereverbparam) | 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [enableLocalVoiceReverb](Electron-api.md#rtcvideo-enablelocalvoicereverb) | 开启本地音效混响效果 |
| [setLocalVoiceEqualization](Electron-api.md#rtcvideo-setlocalvoiceequalization) | 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。 |
| [enablePlaybackDucking](Electron-api.md#rtcvideo-enableplaybackducking) | 打开/关闭音量闪避功能，适用于在 RTC 通话过程中会同时播放短视频或音乐的场景，如“一起看”、“在线 KTV”等。开启该功能后，当检测到远端人声时，RTC 的本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，RTC 的本地媒体音量会恢复到闪避前的音量水平。 |



## 自定义流处理

| 方法 | 描述 |
| :-- | :-- |
| [setVideoSourceType](Electron-api.md#rtcvideo-setvideosourcetype) | 设置向 SDK 输入的视频源，包括屏幕流。默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 |
| [pushExternalVideoFrame](Electron-api.md#rtcvideo-pushexternalvideoframe) | 推送外部视频帧。 |
| [enableAlphaChannelVideoEncode](Electron-api.md#rtcvideo-enablealphachannelvideoencode) | 开启带有Alpha通道的视频帧编码支持。 |
| [disableAlphaChannelVideoEncode](Electron-api.md#rtcvideo-disablealphachannelvideoencode) | 关闭带有Alpha通道的视频帧编码支持。 |
| [setAudioSourceType](Electron-api.md#rtcvideo-setaudiosourcetype) | 切换音频采集方式 |
| [pushExternalAudioFrame](Electron-api.md#rtcvideo-pushexternalaudioframe) | 推送自定义采集的音频数据到 RTC SDK。 |
| [setLocalVideoSink](Electron-api.md#rtcvideo-setlocalvideosink) | 获取本地视频流。 |
| [unsetLocalVideoSink](Electron-api.md#rtcvideo-unsetlocalvideosink) | 停止获取本地视频流。 |
| [setRemoteVideoSink](Electron-api.md#rtcvideo-setremotevideosink) | 获取远端视频流。 |
| [unsetRemoteVideoSink](Electron-api.md#rtcvideo-unsetremotevideosink) | 停止获取远端视频流。 |
| [onLocalVideoFrame](Electron-event.md#rtcvideocallback-onlocalvideoframe) | 获取采集成功的本地摄像头流视频帧，用于自定义处理或渲染。 |
| [onRemoteVideoFrame](Electron-event.md#rtcvideocallback-onremotevideoframe) | 获取采集成功的远端摄像头流视频帧，用于自定义处理或渲染。 |
| [enableAudioFrameCallback](Electron-api.md#rtcvideo-enableaudioframecallback) | 设置并开启指定的音频数据帧回调。 |
| [disableAudioFrameCallback](Electron-api.md#rtcvideo-disableaudioframecallback) | 关闭音频回调 |
| [onRecordAudioFrame](Electron-event.md#rtcvideocallback-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame](Electron-event.md#rtcvideocallback-onplaybackaudioframe) | 返回远端所有用户混音后的音频数据 |
| [onRemoteUserAudioFrame](Electron-event.md#rtcvideocallback-onremoteuseraudioframe) | 返回远端单个用户的音频数据 |
| [onMixedAudioFrame](Electron-event.md#rtcvideocallback-onmixedaudioframe) | 返回本地麦克风录制和远端所有用户混音后的音频数据 |
| [onRecordScreenAudioFrame](Electron-event.md#rtcvideocallback-onrecordscreenaudioframe) | 返回本地屏幕录制的音频数据 |



## 网络管理

| 方法 | 描述 |
| :-- | :-- |
| [enableSimulcastMode](Electron-api.md#rtcvideo-enablesimulcastmode) | 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。 |
| [onSimulcastSubscribeFallback](Electron-event.md#rtcvideocallback-onsimulcastsubscribefallback) | 因发布/订阅性能回退或退出回退状态，订阅的音视频流，发生流的切换时，收到该回调。 |
| [setRemoteVideoConfig](Electron-api.md#rtcroom-setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
| [setPublishFallbackOption](Electron-api.md#rtcvideo-setpublishfallbackoption) | 设置发布的音视频流回退选项 。你可以调用这个接口来设置网络情况不佳或设备性能不足时只发送小流，以保证通话质量。 |
| [setSubscribeFallbackOption](Electron-api.md#rtcvideo-setsubscribefallbackoption) | 设置订阅的音视频流回退选项。 你可以通过调用该接口来设置网络情况不佳或性能不足时只订阅小流或音频流，以保证通话质量。 |
| [setRemoteUserPriority](Electron-api.md#rtcvideo-setremoteuserpriority) | 设置用户优先级 |
| [onPerformanceAlarms](Electron-event#rtcvideocallback-onperformancealarms) | 本地未通过 [`setPublishFallbackOption`](Electron-api.md#rtcvideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。本地通过 [`setPublishFallbackOption`](Electron-api.md#rtcvideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。 |
| [startNetworkDetection](Electron-api.md#rtcvideo-startnetworkdetection) | 开启通话前网络探测 |
| [stopNetworkDetection](Electron-api.md#rtcvideo-stopnetworkdetection) | 停止通话前网络探测 |
| [onConnectionStateChanged](Electron-event.md#rtcvideocallback-onconnectionstatechanged) | SDK 与信令服务器连接状态改变回调。连接状态改变时触发。 |
| [onNetworkTypeChanged](Electron-event.md#rtcvideocallback-onnetworktypechanged) | SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。 |
| [onNetworkDetectionResult](Electron-event.md#rtcvideocallback-onnetworkdetectionresult) | 成功调用 `startNetworkDetection` 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [onNetworkDetectionStopped](Electron-event.md#rtcvideocallback-onnetworkdetectionstopped) | 通话前网络探测结束 |
| [startEchoTest](Electron-api.md#rtcvideo-startechotest) | 开始音频设备回路测试。 |
| [stopEchoTest](Electron-api.md#rtcvideo-stopechotest) | 停止音频设备回路测试。 |
| [onEchoTestResult](Electron-event.md#rtcvideocallback-onechotestresult) | 通话前网络探测结束 |
| [getNetworkTimeInfo](Electron-api.md#rtcvideo-getnetworktimeinfo) | 通过 NTP 协议，获取网络时间。 |
| [onNetworkTimeSynchronized](Electron-event.md#rtcvideocallback-onnetworktimesynchronized) | 首次调用 `getNetworkTimeInfo` 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。 |



## 消息

| 方法 | 描述 |
| :-- | :-- |
| [login](Electron-api.md#rtcvideo-login) | 登录 RTS 服务器。必须先登录，才能发送房间外点对点消息和向应用服务器发送消息 |
| [logout](Electron-api.md#rtcvideo-logout) | 登出 RTS 服务器。调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
| [onLoginResult](Electron-event.md#rtcvideocallback-onloginresult) | 调用 `login` 后，会收到此回调。 |
| [onLogout](Electron-event.md#rtcvideocallback-onlogout) | 登出结果回调 |
| [updateLoginToken](Electron-api.md#rtcvideo-updatelogintoken) | 更新用户用于登录的 Token。 |
| [sendRoomMessage](Electron-api.md#rtcroom-sendroommessage) | 给房间内的所有其他用户群发文本消息。 |
| [onRoomMessageSendResult](Electron-event.md#rtcroomcallback-onroommessagesendresult) | 调用 `sendRoomMessage` 或 `sendRoomBinaryMessage` 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onRoomMessageReceived](Electron-event.md#rtcroomcallback-onroommessagereceived) | 接收到房间内广播消息的回调。 |
| [sendRoomBinaryMessage](Electron-api.md#rtcroom-sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。 |
| [onRoomBinaryMessageReceived](Electron-event.md#rtcroomcallback-onroombinarymessagereceived) | 接收到房间内广播二进制消息的回调。 |
| [getPeerOnlineStatus](Electron-api.md#rtcvideo-getpeeronlinestatus) | 查询对端用户或本端用户的登录状态 |
| [onGetPeerOnlineStatus](Electron-event.md#rtcvideocallback-ongetpeeronlinestatus) | 查询对端或本端用户登录状态的返回结果 |
| [sendUserMessage](Electron-api.md#rtcroom-sendusermessage) | 给房间内指定的用户发送点对点文本消息 |
| [onUserMessageReceived](Electron-event.md#rtcroomcallback-onusermessagereceived) | 收到来自房间中其他用户通过 `sendUserMessage` 发来的点对点文本消息时，会收到此回调。 |
| [onUserMessageSendResult](Electron-event.md#rtcvideocallback-onusermessagesendresult) | 当调用 sendMessageToUser 函数发送消息后，回调此条消息的发送结果（反馈）。 |
| [onUserMessageSendResult](Electron-event.md#rtcroomcallback-onusermessagesendresult) | 向房间内单个用户发送点对点文本或点对点二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [sendUserBinaryMessage](Electron-api.md#rtcroom-senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息。 |
| [onServerMessageSendResult](Electron-event.md#rtcvideocallback-onservermessagesendresult) | 给业务服务器发送消息的回调 |
| [onServerParamsSetResult](Electron-event.md#rtcvideocallback-onserverparamssetresult) | 设置业务服务器参数的返回结果 |
| [onUserBinaryMessageReceived](Electron-event.md#rtcvideocallback-onuserbinarymessagereceived) | 单个用户接收到同一房间内其他 uid 所属用户发来二进制消息的回调（P2P）。 |
| [onUserBinaryMessageReceived](Electron-event.md#rtcroomcallback-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 `sendUserBinaryMessage` 发来的点对点二进制消息时，会收到此回调。 |
| [sendUserMessageOutsideRoom](Electron-api.md#rtcvideo-sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
| [onUserMessageSendResultOutsideRoom](Electron-event.md#rtcvideocallback-onusermessagesendresultoutsideroom) | 给房间外指定的用户发送消息的回调 |
| [sendUserBinaryMessageOutsideRoom](Electron-api.md#rtcvideo-senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
| [onUserMessageReceivedOutsideRoom](Electron-event.md#rtcvideocallback-onusermessagereceivedoutsideroom) | 收到房间外用户调用 `sendUserMessageOutsideRoom` 发来的文本消息时，会收到此回调 |
| [onUserBinaryMessageReceivedOutsideRoom](Electron-event.md#rtcvideocallback-onuserbinarymessagereceivedoutsideroom) | 收到房间外用户调用 `sendUserBinaryMessageOutsideRoom` 发来的二进制消息时，会收到此回调 |
| [setServerParams](Electron-api.md#rtcvideo-setserverparams) | 设置业务服务器参数。 |
| [sendServerMessage](Electron-api.md#rtcvideo-sendservermessage) | 客户端给业务服务器发送文本消息（P2Server） |
| [sendServerBinaryMessage](Electron-api.md#rtcvideo-sendserverbinarymessage) | 客户端给业务服务器发送二进制消息（P2Server） |
| [sendStreamSyncInfo](Electron-api.md#rtcvideo-sendstreamsyncinfo) | 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步。 |
| [sendSEIMessage](Electron-api.md#rtcvideo-sendseimessage) | 通过视频帧发送 SEI 数据。 |
| [onSEIStreamUpdate](Electron-event.md#rtcvideocallback-onseistreamupdate) | 黑帧视频流发布状态回调。 |
| [onSEIMessageReceived](Electron-event.md#rtcvideocallback-onseimessagereceived) | 收到通过 `sendSEIMessage` 发送的带有 SEI 消息的视频帧时，收到此回调 |



## CDN 推流

| 方法 | 描述 |
| :-- | :-- |
| [startPushMixedStreamToCDN](Electron-api.md#rtcvideo-startpushmixedstreamtocdn) | 新增转推直播任务(新)，并设置合流的图片、视频视图布局和音频属性。 |
| [updatePushMixedStreamToCDN](Electron-api.md#rtcvideo-updatepushmixedstreamtocdn) | 更新转推直播参数。 |
| [setupMixingVideo](Electron-api.md#rtcvideo-setupmixingvideo) | 为客户端合流绑定本地视图 |
| [removeMixingVideo](Electron-api.md#rtcvideo-removemixingvideo) | 为合流转推解绑本地视图 |
| [setAudioAlignmentProperty](Electron-api.md#rtcvideo-setaudioalignmentproperty) | 在听众端，设置订阅的所有远端音频流精准对齐后播放。 |
| [startPushSingleStreamToCDN](Electron-api.md#rtcvideo-startpushsinglestreamtocdn) | 新增单流转推直播任务。 |
| [onStreamPushEvent](Electron-event.md#rtcvideocallback-onstreampushevent) | 单流转推直播状态回调 |
| [onMixingEvent](Electron-event.md#rtcvideocallback-onmixingevent) | 转推直播状态回调 |
| [onMixingVideoFrame](Electron-event.md#rtcvideocallback-onmixingvideoframe) | 合流视频回调，运行在视频回调线程 |
| [stopPushStreamToCDN](Electron-api.md#rtcvideo-stoppushstreamtocdn) | 停止转推直播。 |
| [onMixingAudioFrame](Electron-event.md#rtcvideocallback-onmixingaudioframe) | 合流音频回调，运行在音频回调线程 |
| [onMixingDataFrame](Electron-event.md#rtcvideocallback-onmixingdataframe) | 视频 SEI 帧回调，运行在视频回调线程 |



## 音效播放

| 方法 | 描述 |
| :-- | :-- |
| [getAudioEffectPlayer](Electron-api.md#rtcvideo-getaudioeffectplayer) | 创建音效播放器实例。 |
| [start](Electron-api.md#rtcaudioeffectplayer-start) | 开始播放音效文件。<br>可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个音效文件，实现音效叠加。 |
| [stop](Electron-api.md#rtcaudioeffectplayer-stop) | 停止播放音效文件。 |
| [stopAll](Electron-api.md#rtcaudioeffectplayer-stopall) | 停止播放所有音效文件。 |
| [preload](Electron-api.md#rtcaudioeffectplayer-preload) | 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。 |
| [unload](Electron-api.md#rtcaudioeffectplayer-unload) | 卸载指定音效文件。 |
| [unloadAll](Electron-api.md#rtcaudioeffectplayer-unloadall) | 卸载所有音效文件。 |
| [pause](Electron-api.md#rtcaudioeffectplayer-pause) | 暂停播放音效文件。 |
| [pauseAll](Electron-api.md#rtcaudioeffectplayer-pauseall) | 暂停播放所有音效文件。 |
| [resume](Electron-api.md#rtcaudioeffectplayer-resume) | 恢复播放音效文件。 |
| [resumeAll](Electron-api.md#rtcaudioeffectplayer-resumeall) | 恢复播放所有音效文件。 |
| [setPosition](Electron-api.md#rtcaudioeffectplayer-setposition) | 设置音效文件的起始播放位置。 |
| [getPosition](Electron-api.md#rtcaudioeffectplayer-getposition) | 获取音效文件播放进度。 |
| [setVolume](Electron-api.md#rtcaudioeffectplayer-setvolume) | 调节指定音效的音量大小，包括音效文件和 PCM 音频。 |
| [setVolumeAll](Electron-api.md#rtcaudioeffectplayer-setvolumeall) | 设置所有音效的音量大小，包括音效文件和 PCM 音效。 |
| [getVolume](Electron-api.md#rtcaudioeffectplayer-getvolume) | 获取当前音量。 |
| [getDuration](Electron-api.md#rtcaudioeffectplayer-getduration) | 获取音效文件时长。 |
| [setEventHandler](Electron-api.md#rtcaudioeffectplayer-seteventhandler) | 设置回调句柄。 |
| [onAudioEffectPlayerStateChanged](Electron-event.md#rtcaudioeffectplayercallback-onaudioeffectplayerstatechanged) | 播放状态改变时回调。 |



## 音乐播放

| 方法 | 描述 |
| :-- | :-- |
| [getMediaPlayer](Electron-api.md#rtcvideo-getmediaplayer) | 创建音乐播放器实例。 |
| [open](Electron-api.md#rtcmediaplayer-open) | 打开音乐文件。<br>一个播放器实例仅能够同时打开一个音乐文件。如果需要同时打开多个音乐文件，请创建多个音乐播放器实例。 |
| [start](Electron-api.md#rtcmediaplayer-start) | 播放音乐。你仅需要在调用 [open](Electron-api.md#rtcmediaplayer-open)，且未开启自动播放时，调用此方法。 |
| [stop](Electron-api.md#rtcmediaplayer-stop) | 调用 [open](Electron-api.md#rtcmediaplayer-open) 或 [start](Electron-api.md#rtcmediaplayer-start) 开始播放后，可以调用本方法停止。 |
| [pause](Electron-api.md#rtcmediaplayer-pause) | 调用 [open](Electron-api.md#rtcmediaplayer-open)，或 [start](Electron-api.md#rtcmediaplayer-start) 开始播放音频文件后，调用本方法暂停播放。 |
| [resume](Electron-api.md#rtcmediaplayer-resume) | 调用 [pause](Electron-api.md#rtcmediaplayer-pause) 暂停音频播放后，调用本方法恢复播放。 |
| [setVolume](Electron-api.md#rtcmediaplayer-setvolume) | 调节指定混音的音量大小，包括音乐文件混音和 PCM 混音。 |
| [getVolume](Electron-api.md#rtcmediaplayer-getvolume) | 获取当前音量 |
| [getTotalDuration](Electron-api.md#rtcmediaplayer-gettotalduration) | 获取音乐文件时长。 |
| [getPlaybackDuration](Electron-api.md#rtcmediaplayer-getplaybackduration) | 获取混音音乐文件的实际播放时长，单位为毫秒。 |
| [getPosition](Electron-api.md#rtcmediaplayer-getposition) | 获取音乐文件播放进度。 |
| [setPosition](Electron-api.md#rtcmediaplayer-setposition) | 设置音乐文件的起始播放位置。 |
| [setAudioPitch](Electron-api.md#rtcmediaplayer-setaudiopitch) | 开启变调功能，多用于 K 歌场景。 |
| [setAudioDualMonoMode](Electron-api.md#rtcmediaplayer-setaudiodualmonomode) | 设置当前音乐文件的声道模式 |
| [getAudioTrackCount](Electron-api.md#rtcmediaplayer-getaudiotrackcount) | 获取当前音乐文件的音轨数 |
| [selectAudioTrack](Electron-api.md#rtcmediaplayer-selectaudiotrack) | 指定当前音乐文件的播放音轨 |
| [setPlaybackSpeed](Electron-api.md#rtcmediaplayer-setplaybackspeed) | 设置播放速度 |
| [setProgressInterval](Electron-api#rtcmediaplayer-setprogressinterval) | 设置音频文件混音时，收到 [onMediaPlayerPlayingProgress](Electron-event.md#rtcmediaplayercallback-onmediaplayerplayingprogress) 的间隔。 |
| [setLoudness](Electron-api.md#rtcmediaplayer-setloudness) | 如果你需要使用 [`enableVocalInstrumentBalance`](Electron-api.md#rtcvideo-enablevocalinstrumentbalance) 对音频文件/PCM 音频数据设置音量均衡，你必须通过此接口传入其原始响度。 |
| [setEventHandler](Electron-api.md#rtcmediaplayer-seteventhandler) | 注册回调句柄以在本地音乐文件混音时，收到相关回调。 |
| [onMediaPlayerStateChanged](Electron-event.md#rtcmediaplayercallback-onmediaplayerstatechanged) | 播放状态改变时回调。 |
| [onMediaPlayerPlayingProgress](Electron-event.md#rtcmediaplayercallback-onmediaplayerplayingprogress) | 播放进度周期性回调。回调周期通过 [setAudioMixingProgressInterval] 设置。 |
| [openWithCustomSource](Electron-api.md#rtcmediaplayer-openwithcustomsource) | 启动音频裸数据混音。 |
| [pushExternalAudioFrame](Electron-api.md#rtcmediaplayer-pushexternalaudioframe) | 推送用于混音的 PCM 音频帧数据 |



## 屏幕分享

| 方法 | 描述 |
| :-- | :-- |
| [startScreenVideoCapture](Electron-api.md#rtcvideo-startscreenvideocapture) | 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，应用窗口中显示的内容，或虚拟屏幕中显示的内容。其中，虚拟屏幕中显示的内容仅在 Windows 平台上支持。 |
| [stopScreenVideoCapture](Electron-api.md#rtcvideo-stopscreenvideocapture) | 停止屏幕视频流采集。 |
| [updateScreenCaptureMouseCursor](Electron-api.md#rtcvideo-updatescreencapturemousecursor) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新对鼠标的处理设置。默认采集鼠标。 |
| [setScreenVideoEncoderConfig](Electron-api.md#rtcvideo-setscreenvideoencoderconfig) | 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。 |
| [publishScreen](Electron-api.md#rtcroom-publishscreen) | 在当前所在房间内发布本地屏幕共享音视频流 |
| [updateScreenCaptureRegion](Electron-api.md#rtcvideo-updatescreencaptureregion) | 更新屏幕共享区域。 |
| [unpublishScreen](Electron-api.md#rtcroom-unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
| [updateScreenCaptureHighlightConfig](Electron-api.md#rtcvideo-updatescreencapturehighlightconfig) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新边框高亮设置。默认展示表框。 |
| [updateScreenCaptureFilterConfig](Electron-api.md#rtcvideo-updatescreencapturefilterconfig) | 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。 |
| [getScreenCaptureSourceList](Electron-api.md#rtcvideo-getscreencapturesourcelist) | 获取屏幕采集对象列表。 |
| [getThumbnail](Electron-api.md#rtcvideo-getthumbnail) | 获取共享对象缩略图 |
| [getWindowAppIcon](Electron-api.md#rtcvideo-getwindowappicon) | 获取应用窗体所属应用的图标。 |
| [subscribeScreen](Electron-api.md#rtcroom-subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项 |
| [unsubscribeScreen](Electron-api.md#rtcroom-unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。 |
| [startScreenAudioCapture](Electron-api.md#rtcvideo-startscreenaudiocapture) | 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频 |
| [onUserPublishScreen](Electron-event.md#rtcroomcallback-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [stopScreenAudioCapture](Electron-api.md#rtcvideo-stopscreenaudiocapture) | 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。 |
| [onUserUnpublishScreen](Electron-event.md#rtcroomcallback-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onScreenVideoFrameSendStateChanged](Electron-event.md#rtcvideocallback-onscreenvideoframesendstatechanged) | 屏幕共享流视频首帧发送状态改变回调 |
| [onScreenVideoFramePlayStateChanged](Electron-event.md#rtcvideocallback-onscreenvideoframeplaystatechanged) | 屏幕共享流视频首帧播放状态改变回调 |
| [onScreenAudioFrameSendStateChanged](Electron-event.md#rtcvideocallback-onscreenaudioframesendstatechanged) | 屏幕音频首帧发送状态改变回调 |
| [onScreenAudioFramePlayStateChanged](Electron-event.md#rtcvideocallback-onscreenaudioframeplaystatechanged) | 屏幕音频首帧播放状态改变回调 |
| [onLocalScreenFrame](Electron-event.md#rtcvideocallback-onlocalscreenframe) | 获取采集成功的本地屏幕视频帧，用于自定义处理或渲染。 |
| [onRemoteScreenFrame](Electron-event.md#rtcvideocallback-onremotescreenframe) | 视频管理获取采集成功的远端屏幕视频帧，用于自定义处理或渲染。 |
| [setScreenAudioChannel](Electron-api.md#rtcvideo-setscreenaudiochannel) | 在屏幕共享时，设置屏幕音频流的声道数 |
| [setScreenAudioStreamIndex](Electron-api.md#rtcvideo-setscreenaudiostreamindex) | 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式 |



## 安全与加密

| 方法 | 描述 |
| :-- | :-- |
| [startCloudProxy](Electron-api.md#rtcvideo-startcloudproxy) | 开启云代理 |
| [stopCloudProxy](Electron-api.md#rtcvideo-stopcloudproxy) | 关闭云代理 |
| [onCloudProxyConnected](Electron-event.md#rtcvideocallback-oncloudproxyconnected) | 调用 `startCloudProxy` 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [setEncryptInfo](Electron-api.md#rtcvideo-setencryptinfo) | 设置传输时使用内置加密的方式 |
| [setLocalProxy](Electron-api.md#rtcvideo-setlocalproxy) | 设置本地代理。 |
| [onLocalProxyStateChanged](Electron-event#rtcvideocallback-onlocalproxystatechanged) | 本地代理状态发生改变回调。调用 [setLocalProxy](Electron-api.md#rtcvideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。 |
| [onHttpsProxyState](Electron-event.md#rtcvideocallback-onhttpsproxystate) | HTTPS 代理连接状态改变时，收到该回调。 |
| [onHttpProxyState](Electron-event.md#rtcvideocallback-onhttpproxystate) | HTTP 代理连接状态改变时，收到该回调。 |
| [onSocks5ProxyState](Electron-event.md#rtcvideocallback-onsocks5proxystate) | SOCKS5 代理状态改变时，收到该回调。 |



## 录制

| 方法 | 描述 |
| :-- | :-- |
| [startFileRecording](Electron-api.md#rtcvideo-startfilerecording) | 该方法将通话过程中的音视频数据录制到本地的文件中。 |
| [stopFileRecording](Electron-api.md#rtcvideo-stopfilerecording) | 停止本地录制 |
| [startAudioRecording](Electron-api.md#rtcvideo-startaudiorecording) | 开启录制语音通话，生成本地文件。 |
| [stopAudioRecording](Electron-api.md#rtcvideo-stopaudiorecording) | 停止音频文件录制 |
| [onRecordingStateUpdate](Electron-event.md#rtcvideocallback-onrecordingstateupdate) | 获取本地录制状态回调。 |
| [onRecordingProgressUpdate](Electron-event.md#rtcvideocallback-onrecordingprogressupdate) | 本地录制进度回调。 |
| [onAudioRecordingStateUpdate](Electron-event#rtcvideocallback-onaudiorecordingstateupdate) | 调用 [startAudioRecording](Electron-api.md#startaudiorecording) 或 [stopAudioRecording](Electron-api.md#stopaudiorecording) 改变音频文件录制状态时，收到此回调。 |



## 空间音频

| 方法 | 描述 |
| :-- | :-- |
| [enableSpatialAudio](Electron-api.md#rtcroom-enablespatialaudio) | 开启/关闭空间音频功能。 |
| [disableRemoteOrientation](Electron-api.md#rtcroom-disableremoteorientation) | 参与通话的各端调用本接口后，将忽略远端用户的朝向，认为所有远端用户都面向本地用户。 |
| [updateListenerOrientation](Electron-api.md#rtcroom-updatelistenerorientation) | 更新在房间内收听音频时的朝向。<br>通过此接口，你可以设定本地用户的发声朝向和收听朝向不同。 |
| [updateListenerPosition](Electron-api.md#rtcroom-updatelistenerposition) | 更新在房间内收听音频时的位置。<br>通过此接口，你可以设定本地发声位置和收听位置不同。 |
| [updateSpatialPosition](Electron-api.md#rtcroom-updatespatialposition) | 更新本地用户在房间内空间直角坐标系中的位置坐标。 |
| [updateSelfPosition](Electron-api.md#rtcroom-updateselfposition) | 设置本地用户在自建空间直角坐标系中的收听坐标和收听朝向，以实现本地用户预期的空间音频收听效果。 |
| [updateSelfOrientation](Electron-api.md#rtcroom-updateselforientation) | 更新本地用户在空间音频坐标系下的朝向。 |
| [updateRemotePosition](Electron-api.md#rtcroom-updateremoteposition) | 设置房间内某一远端用户在本地用户自建的空间音频坐标系中的发声位置和发声朝向，以实现本地用户预期的空间音频收听效果。 |
| [removeRemotePosition](Electron-api.md#rtcroom-removeremoteposition) | 移除调用 [updateRemotePosition](Electron-api.md#updateremoteposition) 为某一远端用户设置的空间音频效果。 |
| [removeAllRemotePosition](Electron-api.md#rtcroom-removeallremoteposition) | 移除调用 [updateRemotePosition](Electron-api.md#updateremoteposition) 为所有远端用户设置的空间音频效果。 |



## 范围语音

| 方法 | 描述 |
| :-- | :-- |
| [enableRangeAudio](Electron-api.md#rtcroom-enablerangeaudio) | 开启/关闭范围语音功能。 |
| [setAttenuationModel](Electron-api.md#rtcroom-setattenuationmodel) | 设置范围语音的音量衰减模式。 |
| [setNoAttenuationFlags](Electron-api.md#rtcroom-setnoattenuationflags) | 添加标签组，用于标记相互之间通话不衰减的用户组。<br>在同一个 RTC 房间中，如果多个用户的标签组之间有交集，那么，他们之间互相通话时，通话不衰减。<br>比如，用户身处多个队伍，队伍成员间通话不衰减。那么，可以为每个队伍绑定专属标签，每个用户的标签组包含用户所属各个队伍的标签。 |
| [updateRangePosition](Electron-api.md#rtcroom-updaterangeposition) | 更新本地用户在房间内空间直角坐标系中的位置坐标。 |
| [updateReceiveRange](Electron-api.md#rtcroom-updatereceiverange) | 更新本地用户的音频收听范围。 |



## 音乐和打分

| 方法 | 描述 |
| :-- | :-- |
| [getMusicDetail](Electron-api.md#rtcvideo-getmusicdetail) | 获取音乐详细信息。 |
| [getMusicList](Electron-api.md#rtcvideo-getmusiclist) | 获取歌曲列表。 |
| [searchMusic](Electron-api.md#rtcvideo-searchmusic) | 根据关键词搜索歌曲。 |
| [getHotMusic](Electron-api.md#rtcvideo-gethotmusic) | 根据热榜类别获取每个榜单的歌曲列表。 |
| [downloadMusic](Electron-api.md#rtcvideo-downloadmusic) | 下载音乐。 |
| [downloadLyric](Electron-api.md#rtcvideo-downloadlyric) | 下载歌词。 |
| [downloadMidi](Electron-api.md#rtcvideo-downloadmidi) | 下载 MIDI 文件。 |
| [cancelDownload](Electron-api.md#rtcvideo-canceldownload) | 取消下载任务。 |
| [setMaxCacheSize](Electron-api.md#rtcvideo-setmaxcachesize) | 设置歌曲文件最大占用的本地缓存。 |
| [clearCache](Electron-api.md#rtcvideo-clearcache) | 清除当前音乐缓存文件，包括音乐音频和歌词。 |
| [playMusic](Electron-api.md#rtcvideo-playmusic) | 播放歌曲。 |
| [pauseMusic](Electron-api.md#rtcvideo-pausemusic) | 暂停播放歌曲。 |
| [resumeMusic](Electron-api.md#rtcvideo-resumemusic) | 继续播放歌曲。 |
| [stopMusic](Electron-api.md#rtcvideo-stopmusic) | 停止播放歌曲。 |
| [seekMusic](Electron-api.md#rtcvideo-seekmusic) | 设置音乐文件的起始播放位置。 |
| [setMusicVolume](Electron-api.md#rtcvideo-setmusicvolume) | 设置歌曲播放音量，只能在开始播放后进行设置。 |
| [switchAudioTrackType](Electron-api.md#rtcvideo-switchaudiotracktype) | 切换歌曲原唱伴唱。 |
| [setMusicPitch](Electron-api.md#rtcvideo-setmusicpitch) | 对播放中的音乐设置升降调信息。 |
| [onMusicListResult](Electron-event.md#rtcvideocallback-onmusiclistresult) | 歌曲列表回调。 |
| [onSearchMusicResult](Electron-event.md#rtcvideocallback-onsearchmusicresult) | 搜索歌曲结果回调。 |
| [onHotMusicResult](Electron-event.md#rtcvideocallback-onhotmusicresult) | 热榜歌曲结果回调。 |
| [onMusicDetailResult](Electron-event.md#rtcvideocallback-onmusicdetailresult) | 歌曲详细信息回调。 |
| [onDownloadSuccess](Electron-event.md#rtcvideocallback-ondownloadsuccess) | 下载成功回调。 |
| [onDownloadFailed](Electron-event.md#rtcvideocallback-ondownloadfailed) | 下载失败回调。 |
| [onDownloadMusicProgress](Electron-event.md#rtcvideocallback-ondownloadmusicprogress) | 歌曲文件下载进度回调。 |
| [onPlayProgress](Electron-event.md#rtcvideocallback-onplayprogress) | 音乐播放进度回调。 |
| [onPlayStateChanged](Electron-event.md#rtcvideocallback-onplaystatechanged) | 音乐播放状态改变回调。 |
| [onCurrentScoringInfo](Electron-event.md#rtcvideocallback-oncurrentscoringinfo) | 实时评分信息回调。 |
| [onClearCacheResult](Electron-event.md#rtcvideocallback-onclearcacheresult) | 清理文件缓存结果回调。 |
| [initSingScoring](Electron-api.md#rtcvideo-initsingscoring) | 初始化 K 歌评分。 |
| [setSingScoringConfig](Electron-api.md#rtcvideo-setsingscoringconfig) | 设置 K 歌评分参数。 |
| [getStandardPitchCount](Electron-api.md#rtcvideo-getstandardpitchcount) | 获取当前系统内音视频设备数量 |
| [getStandardPitchInfo](Electron-api.md#rtcvideo-getstandardpitchinfo) | 获取每句歌词的标准音高信息 |
| [startSingScoring](Electron-api.md#rtcvideo-startsingscoring) | 开始 K 歌评分。 |
| [getLastSentenceScore](Electron-api.md#rtcvideo-getlastsentencescore) | 获取上一句的演唱评分。 |
| [getTotalScore](Electron-api.md#rtcvideo-gettotalscore) | 获取当前演唱总分。 |
| [getAverageScore](Electron-api.md#rtcvideo-getaveragescore) | 获取当前演唱歌曲的平均分。 |
| [stopSingScoring](Electron-api.md#rtcvideo-stopsingscoring) | 停止 K 歌评分。 |



## 公共流

| 方法 | 描述 |
| :-- | :-- |
| [startPushPublicStream](Electron-api.md#rtcvideo-startpushpublicstream) | 发布一路公共流。 |
| [stopPushPublicStream](Electron-api.md#rtcvideo-stoppushpublicstream) | 停止发布当前用户发布的公共流 |
| [updatePublicStreamParam](Electron-api.md#rtcvideo-updatepublicstreamparam) | 更新公共流参数 |
| [startPlayPublicStream](Electron-api.md#rtcvideo-startplaypublicstream) | 订阅指定公共流。无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
| [stopPlayPublicStream](Electron-api.md#rtcvideo-stopplaypublicstream) | 取消订阅指定公共流 |
| [setupPublicStreamVideo](Electron-api.md#rtcvideo-setuppublicstreamvideo) | 为公共流绑定本地视图 |
| [removePublicStreamVideo](Electron-api.md#rtcvideo-removepublicstreamvideo) | 为公共流解绑本地视图 |
| [setPublicStreamVideoSink](Electron-api.md#rtcvideo-setpublicstreamvideosink) | 为指定公共流绑定自定义渲染器。 |
| [unsetPublicStreamVideoSink](Electron-api.md#rtcvideo-unsetpublicstreamvideosink) | 为指定公共解绑自定义渲染器。 |
| [setPublicStreamAudioPlaybackVolume](Electron-api.md#rtcvideo-setpublicstreamaudioplaybackvolume) | 调节公共流的音频播放音量。 |
| [onPushPublicStreamResult](Electron-event.md#rtcvideocallback-onpushpublicstreamresult) | 公共流发布结果回调。<br>调用 `startPushPublicStream` 接口发布公共流后，启动结果通过此回调方法通知用户。 |
| [onFirstPublicStreamVideoFrameDecoded](Electron-event.md#rtcvideocallback-onfirstpublicstreamvideoframedecoded) | 公共流的首帧视频解码成功 |
| [onPlayPublicStreamResult](Electron-event#rtcvideocallback-onplaypublicstreamresult) | 订阅公共流的结果回调<br>通过 [`startPlayPublicStream`](Electron-api.md#rtcvideo-startplaypublicstream)  订阅公共流后，可以通过本回调获取订阅结果。 |
| [onFirstPublicStreamAudioFrame](Electron-event.md#rtcvideocallback-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功 |
| [onPublicStreamVideoFrame](Electron-event.md#rtcvideocallback-onpublicstreamvideoframe) | 公共流视频数据回调，绑定公共流到自定义渲染器后，通过该回调获取公共流视频数据。 |
| [onPublicStreamDataMessageReceived](Electron-event#rtcvideocallback-onpublicstreamdatamessagereceived) | 回调公共流中包含的数据信息。<br>通过 [`startPlayPublicStream`](Electron-api.md#rtcvideo-startplaypublicstream)  订阅公共流后，通过监听本回调获取公共流中的数据消息，包括调用 Open API 发送的 SEI 消息和音量回调。 |
| [onPublicStreamSEIMessageReceived](Electron-event#rtcvideocallback-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br>调用 [`startPlayPublicStream`](Electron-api.md#startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |



## 字幕翻译服务

| 方法 | 描述 |
| :-- | :-- |
| [startSubtitle](Electron-api.md#rtcroom-startsubtitle) | 识别或翻译房间内所有用户的语音，形成字幕。 |
| [stopSubtitle](Electron-api#rtcroom-stopsubtitle) | 关闭字幕。<br>调用该方法后，用户会收到 [onSubtitleStateChanged](Electron-event.md#onsubtitlestatechanged) 回调，通知字幕是否关闭。 |
| [onSubtitleStateChanged](Electron-event#rtcroomcallback-onsubtitlestatechanged) | 字幕状态发生改变回调。<br>当用户调用 [startSubtitle](Electron-api.md#startsubtitle) 和 [stopSubtitle](Electron-api.md#stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。 |
| [onSubtitleMessageReceived](Electron-event#rtcroomcallback-onsubtitlemessagereceived) | 字幕相关内容回调。<br>当用户成功调用 [startSubtitle](Electron-api.md#startsubtitle) 后会收到此回调，通知字幕的相关信息。 |



## 视频截图

| 方法 | 描述 |
| :-- | :-- |
| [takeLocalSnapshot](Electron-api.md#rtcvideo-takelocalsnapshot) | 截取本地视频画面 |
| [takeRemoteSnapshot](Electron-api.md#rtcvideo-takeremotesnapshot) | 截取远端视频画面 |
| [onTakeLocalSnapshotResult](Electron-event.md#rtcvideocallback-ontakelocalsnapshotresult) | 调用 `takeLocalSnapshot` 截取视频画面时，收到此回调。 |
| [onTakeRemoteSnapshotResult](Electron-event.md#rtcvideocallback-ontakeremotesnapshotresult) | 调用 `takeRemoteSnapshot` 截取视频画面时，收到此回调。 |



## 插件管理器

| 方法 | 描述 |
| :-- | :-- |
| [initializePluginManager](Electron-api.md#rtcvideo-initializepluginmanager) | 初始化插件管理器 |
| [registerPlugin](Electron-api.md#rtcvideo-registerplugin) | 注册插件 |
| [getPlugin](Electron-api.md#rtcvideo-getplugin) | 获取插件实例 |
| [unregisterPlugin](Electron-api.md#rtcvideo-unregisterplugin) | 卸载插件 |
| [releasePluginManager](Electron-api.md#rtcvideo-releasepluginmanager) | 释放插件管理器 |



## 高级功能

| 方法 | 描述 |
| :-- | :-- |
| [setEarMonitorMode](Electron-api.md#rtcvideo-setearmonitormode) | 开启/关闭耳返功能 |
| [setEarMonitorVolume](Electron-api.md#rtcvideo-setearmonitorvolume) | 设置耳返的音量 |
| [setAnsMode](Electron-api.md#rtcvideo-setansmode) | 支持根据业务场景，设置通话中的音频降噪模式。 |
| [onExtensionAccessError](Electron-event.md#rtcvideocallback-onextensionaccesserror) | 当访问插件失败时，收到此回调。<br>RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。 |