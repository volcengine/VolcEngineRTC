---
is_dir: False    # True for dir; False for doc
status: 1    # 1 for online; 0 for offline
keywords: 实时音视频    # use ',' as separator
---

## RTCVIDEOCALLBACK <span id="rtcvideocallback"></span>

类型: `interface`

- **API**

| 方法 | 描述 |
| :-- | :-- |
| [onLogReport](#rtcvideocallback-onlogreport) | 端监控日志回调。当产生一个端监控事件时触发该回调。 |
| [onMusicListResult](#rtcvideocallback-onmusiclistresult) | 歌曲列表回调。 |
| [onSearchMusicResult](#rtcvideocallback-onsearchmusicresult) | 搜索歌曲结果回调。 |
| [onHotMusicResult](#rtcvideocallback-onhotmusicresult) | 热榜歌曲结果回调。 |
| [onMusicDetailResult](#rtcvideocallback-onmusicdetailresult) | 歌曲详细信息回调。 |
| [onDownloadSuccess](#rtcvideocallback-ondownloadsuccess) | 下载成功回调。 |
| [onDownloadFailed](#rtcvideocallback-ondownloadfailed) | 下载失败回调。 |
| [onDownloadMusicProgress](#rtcvideocallback-ondownloadmusicprogress) | 歌曲文件下载进度回调。 |
| [onPlayProgress](#rtcvideocallback-onplayprogress) | 音乐播放进度回调。 |
| [onPlayStateChanged](#rtcvideocallback-onplaystatechanged) | 音乐播放状态改变回调。 |
| [onTakeLocalSnapshotResult](#rtcvideocallback-ontakelocalsnapshotresult) | 调用 `takeLocalSnapshot` 截取视频画面时，收到此回调。 |
| [onTakeRemoteSnapshotResult](#rtcvideocallback-ontakeremotesnapshotresult) | 调用 `takeRemoteSnapshot` 截取视频画面时，收到此回调。 |
| [onCreateRoomStateChanged](#rtcvideocallback-oncreateroomstatechanged) | 创建房间失败回调。 |
| [onHttpProxyState](#rtcvideocallback-onhttpproxystate) | HTTP 代理连接状态改变时，收到该回调。 |
| [onHttpsProxyState](#rtcvideocallback-onhttpsproxystate) | HTTPS 代理连接状态改变时，收到该回调。 |
| [onSocks5ProxyState](#rtcvideocallback-onsocks5proxystate) | SOCKS5 代理状态改变时，收到该回调。 |
| [onStreamSyncInfoReceived](#rtcvideocallback-onstreamsyncinforeceived) | 音频流同步信息回调。可以通过此回调，在远端用户调用 `sendStreamSyncInfo` 发送音频流同步消息后，收到远端发送的音频流同步信息。 |
| [onScreenAudioFrameSendStateChanged](#rtcvideocallback-onscreenaudioframesendstatechanged) | 屏幕音频首帧发送状态改变回调 |
| [onScreenAudioFramePlayStateChanged](#rtcvideocallback-onscreenaudioframeplaystatechanged) | 屏幕音频首帧播放状态改变回调 |
| [onCloudProxyConnected](#rtcvideocallback-oncloudproxyconnected) | 调用 `startCloudProxy` 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onNetworkTimeSynchronized](#rtcvideocallback-onnetworktimesynchronized) | 首次调用 `getNetworkTimeInfo` 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。 |
| [onLicenseWillExpire](#rtcvideocallback-onlicensewillexpire) | license过期时间提醒 |
| [onFaceDetectResult](#rtcvideocallback-onfacedetectresult) | 特效 SDK 进行人脸检测结果的回调。<br>调用 `enableFaceDetection` 注册了回调，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。 |
| [onAudioDeviceVolumeChanged](#rtcvideocallback-onaudiodevicevolumechanged) | 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。 |
| [onCurrentScoringInfo](#rtcvideocallback-oncurrentscoringinfo) | 实时评分信息回调。 |
| [onAudioRecordingStateUpdate](#rtcvideocallback-onaudiorecordingstateupdate) | 调用 [startAudioRecording](Electron-api#startaudiorecording) 或 [stopAudioRecording](Electron-api#stopaudiorecording) 改变音频文件录制状态时，收到此回调。 |
| [onExtensionAccessError](#rtcvideocallback-onextensionaccesserror) | 当访问插件失败时，收到此回调。<br>RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。 |
| [onPublicStreamDataMessageReceived](#rtcvideocallback-onpublicstreamdatamessagereceived) | 回调公共流中包含的数据信息。<br>通过 [`startPlayPublicStream`](Electron-api#rtcvideo-startplaypublicstream)  订阅公共流后，通过监听本回调获取公共流中的数据消息，包括调用 Open API 发送的 SEI 消息和音量回调。 |
| [onHardwareEchoDetectionResult](#rtcvideocallback-onhardwareechodetectionresult) | 通话前回声检测结果回调。 |
| [onLocalProxyStateChanged](#rtcvideocallback-onlocalproxystatechanged) | 本地代理状态发生改变回调。调用 [setLocalProxy](Electron-api#rtcvideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。 |
| [onMixingEvent](#rtcvideocallback-onmixingevent) | 转推直播状态回调 |
| [onMixingVideoFrame](#rtcvideocallback-onmixingvideoframe) | 合流视频回调，运行在视频回调线程 |
| [onMixingAudioFrame](#rtcvideocallback-onmixingaudioframe) | 合流音频回调，运行在音频回调线程 |
| [onMixingDataFrame](#rtcvideocallback-onmixingdataframe) | 视频 SEI 帧回调，运行在视频回调线程 |
| [onClearCacheResult](#rtcvideocallback-onclearcacheresult) | 清理文件缓存结果回调。 |
| [onFirstPublicStreamAudioFrame](#rtcvideocallback-onfirstpublicstreamaudioframe) | 公共流的音频首帧解码成功 |
| [onPushPublicStreamResult](#rtcvideocallback-onpushpublicstreamresult) | 公共流发布结果回调。<br>调用 `startPushPublicStream` 接口发布公共流后，启动结果通过此回调方法通知用户。 |
| [onFirstPublicStreamVideoFrameDecoded](#rtcvideocallback-onfirstpublicstreamvideoframedecoded) | 公共流的首帧视频解码成功 |
| [onPublicStreamSEIMessageReceived](#rtcvideocallback-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br>调用 [`startPlayPublicStream`](Electron-api#startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [onPlayPublicStreamResult](#rtcvideocallback-onplaypublicstreamresult) | 订阅公共流的结果回调<br>通过 [`startPlayPublicStream`](Electron-api#rtcvideo-startplaypublicstream)  订阅公共流后，可以通过本回调获取订阅结果。 |
| [onLocalScreenFrame](#rtcvideocallback-onlocalscreenframe) | 获取采集成功的本地屏幕视频帧，用于自定义处理或渲染。 |
| [onLocalVideoFrame](#rtcvideocallback-onlocalvideoframe) | 获取采集成功的本地摄像头流视频帧，用于自定义处理或渲染。 |
| [onRemoteScreenFrame](#rtcvideocallback-onremotescreenframe) | 视频管理获取采集成功的远端屏幕视频帧，用于自定义处理或渲染。 |
| [onRemoteVideoFrame](#rtcvideocallback-onremotevideoframe) | 获取采集成功的远端摄像头流视频帧，用于自定义处理或渲染。 |
| [onPublicStreamVideoFrame](#rtcvideocallback-onpublicstreamvideoframe) | 公共流视频数据回调，绑定公共流到自定义渲染器后，通过该回调获取公共流视频数据。 |
| [onWarning](#rtcvideocallback-onwarning) | 当内部发生警告事件时触发该回调 |
| [onError](#rtcvideocallback-onerror) | 当内部发生不可逆转错误时触发该回调 |
| [onAudioMixingFinished](#rtcvideocallback-onaudiomixingfinished) | 本地音乐文件播放已结束回调。 |
| [onAudioMixingStateChanged](#rtcvideocallback-onaudiomixingstatechanged) | 音频混音文件播放状态改变时回调 |
| [onAudioMixingPlayingProgress](#rtcvideocallback-onaudiomixingplayingprogress) | 混音音频文件播放进度回调 |
| [onConnectionStateChanged](#rtcvideocallback-onconnectionstatechanged) | SDK 与信令服务器连接状态改变回调。连接状态改变时触发。 |
| [onNetworkTypeChanged](#rtcvideocallback-onnetworktypechanged) | SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。 |
| [onPerformanceAlarms](#rtcvideocallback-onperformancealarms) | 本地未通过 [`setPublishFallbackOption`](Electron-api#rtcvideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。本地通过 [`setPublishFallbackOption`](Electron-api#rtcvideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。 |
| [onSysStats](#rtcvideocallback-onsysstats) | 周期性地发出回调，报告当前cpu与memory使用率 |
| [onUserStartAudioCapture](#rtcvideocallback-onuserstartaudiocapture) | 房间内的用户调用 `startAudioCapture` 开启音频采集时，房间内其他用户会收到此回调。 |
| [onUserStopAudioCapture](#rtcvideocallback-onuserstopaudiocapture) | 房间内的用户调用 `stopAudioCapture` 关闭音频采集时，房间内其他用户会收到此回调。 |
| [onFirstLocalAudioFrame](#rtcvideocallback-onfirstlocalaudioframe) | 本地采集到第一帧音频帧时，收到该回调 |
| [onFirstRemoteAudioFrame](#rtcvideocallback-onfirstremoteaudioframe) | 收到房间内每一路音频流的第一帧时，收到该回调。 |
| [onSimulcastSubscribeFallback](#rtcvideocallback-onsimulcastsubscribefallback) | 因发布/订阅性能回退或退出回退状态，订阅的音视频流，发生流的切换时，收到该回调。 |
| [onFirstLocalVideoFrameCaptured](#rtcvideocallback-onfirstlocalvideoframecaptured) | 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。 |
| [onLocalVideoSizeChanged](#rtcvideocallback-onlocalvideosizechanged) | 本地视频大小或旋转配置发生改变时，收到此回调。 |
| [onRemoteVideoSizeChanged](#rtcvideocallback-onremotevideosizechanged) | 远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onFirstRemoteVideoFrameRendered](#rtcvideocallback-onfirstremotevideoframerendered) | 第一帧远端视频流在视图上渲染成功后，收到此回调。 |
| [onFirstRemoteVideoFrameDecoded](#rtcvideocallback-onfirstremotevideoframedecoded) | SDK 接收并解码远端视频流首帧后，收到此回调。 |
| [onUserStartVideoCapture](#rtcvideocallback-onuserstartvideocapture) | 房间内的用户调用 `startVideoCapture` 开启视频采集时，房间内其他用户会收到此回调。 |
| [onUserStopVideoCapture](#rtcvideocallback-onuserstopvideocapture) | 房间内的用户调用 `stopVideoCapture` 关闭视频采集时，房间内其他用户会收到此回调。 |
| [onLocalAudioStateChanged](#rtcvideocallback-onlocalaudiostatechanged) | 本地音频的状态发生改变时，该回调通知当前的本地音频状态。 |
| [onRemoteAudioStateChanged](#rtcvideocallback-onremoteaudiostatechanged) | 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。 |
| [onActiveSpeaker](#rtcvideocallback-onactivespeaker) | 调用 `enableAudioPropertiesReport` 后，根据设置的 config.interval，你会周期性地收到此回调，获取房间内的最活跃用户信息。 |
| [onLocalVideoStateChanged](#rtcvideocallback-onlocalvideostatechanged) | 本地视频流的状态发生改变时，收到该事件。 |
| [onRemoteVideoStateChanged](#rtcvideocallback-onremotevideostatechanged) | 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。 |
| [onAudioFrameSendStateChanged](#rtcvideocallback-onaudioframesendstatechanged) | 音频首帧发送状态改变回调 |
| [onVideoFrameSendStateChanged](#rtcvideocallback-onvideoframesendstatechanged) | 视频首帧发送状态改变回调 |
| [onScreenVideoFrameSendStateChanged](#rtcvideocallback-onscreenvideoframesendstatechanged) | 屏幕共享流视频首帧发送状态改变回调 |
| [onAudioFramePlayStateChanged](#rtcvideocallback-onaudioframeplaystatechanged) | 音频首帧播放状态改变回调 |
| [onVideoFramePlayStateChanged](#rtcvideocallback-onvideoframeplaystatechanged) | 视频首帧播放状态改变回调 |
| [onScreenVideoFramePlayStateChanged](#rtcvideocallback-onscreenvideoframeplaystatechanged) | 屏幕共享流视频首帧播放状态改变回调 |
| [onUserMessageSendResult](#rtcvideocallback-onusermessagesendresult) | 当调用 sendMessageToUser 函数发送消息后，回调此条消息的发送结果（反馈）。 |
| [onUserBinaryMessageReceived](#rtcvideocallback-onuserbinarymessagereceived) | 单个用户接收到同一房间内其他 uid 所属用户发来二进制消息的回调（P2P）。 |
| [onStreamSubscribed](#rtcvideocallback-onstreamsubscribed) | 当订阅一个流成功的时候回调该事件 |
| [onSEIMessageReceived](#rtcvideocallback-onseimessagereceived) | 收到通过 `sendSEIMessage` 发送的带有 SEI 消息的视频帧时，收到此回调 |
| [onStreamPushEvent](#rtcvideocallback-onstreampushevent) | 单流转推直播状态回调 |
| [onRecordingStateUpdate](#rtcvideocallback-onrecordingstateupdate) | 获取本地录制状态回调。 |
| [onRecordingProgressUpdate](#rtcvideocallback-onrecordingprogressupdate) | 本地录制进度回调。 |
| [onLoginResult](#rtcvideocallback-onloginresult) | 调用 `login` 后，会收到此回调。 |
| [onLogout](#rtcvideocallback-onlogout) | 登出结果回调 |
| [onServerParamsSetResult](#rtcvideocallback-onserverparamssetresult) | 设置业务服务器参数的返回结果 |
| [onGetPeerOnlineStatus](#rtcvideocallback-ongetpeeronlinestatus) | 查询对端或本端用户登录状态的返回结果 |
| [onUserMessageReceivedOutsideRoom](#rtcvideocallback-onusermessagereceivedoutsideroom) | 收到房间外用户调用 `sendUserMessageOutsideRoom` 发来的文本消息时，会收到此回调 |
| [onUserBinaryMessageReceivedOutsideRoom](#rtcvideocallback-onuserbinarymessagereceivedoutsideroom) | 收到房间外用户调用 `sendUserBinaryMessageOutsideRoom` 发来的二进制消息时，会收到此回调 |
| [onUserMessageSendResultOutsideRoom](#rtcvideocallback-onusermessagesendresultoutsideroom) | 给房间外指定的用户发送消息的回调 |
| [onServerMessageSendResult](#rtcvideocallback-onservermessagesendresult) | 给业务服务器发送消息的回调 |
| [onRecordAudioFrame](#rtcvideocallback-onrecordaudioframe) | 返回麦克风录制的音频数据 |
| [onPlaybackAudioFrame](#rtcvideocallback-onplaybackaudioframe) | 返回远端所有用户混音后的音频数据 |
| [onMixedAudioFrame](#rtcvideocallback-onmixedaudioframe) | 返回本地麦克风录制和远端所有用户混音后的音频数据 |
| [onASRSuccess](#rtcvideocallback-onasrsuccess) | 语音识别服务开启成功回调 |
| [onMessage](#rtcvideocallback-onmessage) | 语音转文字成功回调，该回调返回识别后的全量消息。 |
| [onASRError](#rtcvideocallback-onasrerror) | 当语音识别服务内部发生错误事件时触发该回调。 |
| [onNetworkDetectionResult](#rtcvideocallback-onnetworkdetectionresult) | 成功调用 `startNetworkDetection` 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。 |
| [onNetworkDetectionStopped](#rtcvideocallback-onnetworkdetectionstopped) | 通话前网络探测结束 |
| [onLocalAudioPropertiesReport](#rtcvideocallback-onlocalaudiopropertiesreport) | 调用 `enableAudioPropertiesReport` 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。 |
| [onRemoteAudioPropertiesReport](#rtcvideocallback-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 `enableAudioPropertiesReport`，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。 |
| [onEchoTestResult](#rtcvideocallback-onechotestresult) | 通话前网络探测结束 |
| [onVideoDeviceStateChanged](#rtcvideocallback-onvideodevicestatechanged) | 视频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。 |
| [onAudioDeviceStateChanged](#rtcvideocallback-onaudiodevicestatechanged) | 音频设备状态回调。提示音频采集、音频播放等设备设备的状态。 |
| [onAudioPlaybackDeviceTestVolume](#rtcvideocallback-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onRemoteUserAudioFrame](#rtcvideocallback-onremoteuseraudioframe) | 返回远端单个用户的音频数据 |
| [onRecordScreenAudioFrame](#rtcvideocallback-onrecordscreenaudioframe) | 返回本地屏幕录制的音频数据 |
| [onAudioDeviceWarning](#rtcvideocallback-onaudiodevicewarning) | 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。 |
| [onVideoDeviceWarning](#rtcvideocallback-onvideodevicewarning) | 视频设备警告回调，包括视频采集设备等。 |
| [onSEIStreamUpdate](#rtcvideocallback-onseistreamupdate) | 黑帧视频流发布状态回调。 |

### onLogReport <span id="rtcvideocallback-onlogreport"></span> 

端监控日志回调。当产生一个端监控事件时触发该回调。

- **类型**

  ```ts
  (log_type: string, log_content: string) => void
  ```

- **参数**

  - **log_type**

    类型: string

    事件类型。目前类型固定为 "live_webrtc_monitor_log"。

  - **log_content**

    类型: string

    端监控日志内容。

### onMusicListResult <span id="rtcvideocallback-onmusiclistresult"></span> 

歌曲列表回调。

- **类型**

  ```ts
  (music_infos: MusicInfo[], total_musics_size: number, error_code: KTVErrorCode) => void
  ```

- **参数**

  - **error_code**

    类型: [MusicInfo](Electron-keytype#musicinfo)[]

    错误码，成功时返回 0。

  - **total_musics_size**

    类型: number

    数据条目总数。

  - **music_infos**

    类型: [KTVErrorCode](Electron-errorcode#ktverrorcode)

    歌曲数据数组。

### onSearchMusicResult <span id="rtcvideocallback-onsearchmusicresult"></span> 

搜索歌曲结果回调。

- **类型**

  ```ts
  (music_infos: MusicInfo[], total_musics_size: number, error_code: KTVErrorCode) => void
  ```

- **参数**

  - **error_code**

    类型: [MusicInfo](Electron-keytype#musicinfo)[]

    错误码，成功时返回 0。

  - **total_musics_size**

    类型: number

    数据条目总数。

  - **music_infos**

    类型: [KTVErrorCode](Electron-errorcode#ktverrorcode)

    歌曲数据数组。

### onHotMusicResult <span id="rtcvideocallback-onhotmusicresult"></span> 

热榜歌曲结果回调。

- **类型**

  ```ts
  (hot_infos: HotMusicInfo[], error_code: KTVErrorCode) => void
  ```

- **参数**

  - **error_code**

    类型: [HotMusicInfo](Electron-keytype#hotmusicinfo)[]

    错误码，成功时返回 0。

  - **hot_infos**

    类型: [KTVErrorCode](Electron-errorcode#ktverrorcode)

    热榜歌曲数据数组。

### onMusicDetailResult <span id="rtcvideocallback-onmusicdetailresult"></span> 

歌曲详细信息回调。

- **类型**

  ```ts
  (music_info: MusicInfo, error_code: KTVErrorCode) => void
  ```

- **参数**

  - **error_code**

    类型: [MusicInfo](Electron-keytype#musicinfo)

    错误码，成功时返回 0。

  - **music_info**

    类型: [KTVErrorCode](Electron-errorcode#ktverrorcode)

    歌曲数据。

### onDownloadSuccess <span id="rtcvideocallback-ondownloadsuccess"></span> 

下载成功回调。

- **类型**

  ```ts
  (download_id: number, download_info: DownloadResult) => void
  ```

- **参数**

  - **download_id**

    类型: number

    下载任务 ID。

  - **download_info**

    类型: [DownloadResult](Electron-keytype#downloadresult)

    下载信息。

### onDownloadFailed <span id="rtcvideocallback-ondownloadfailed"></span> 

下载失败回调。

- **类型**

  ```ts
  (download_id: number, error_code: KTVErrorCode) => void
  ```

- **参数**

  - **error_code**

    类型: number

    错误码。

  - **download_id**

    类型: [KTVErrorCode](Electron-errorcode#ktverrorcode)

    下载任务 ID。

### onDownloadMusicProgress <span id="rtcvideocallback-ondownloadmusicprogress"></span> 

歌曲文件下载进度回调。

- **类型**

  ```ts
  (download_id: number, download_percentage: number) => void
  ```

- **参数**

  - **download_id**

    类型: number

    下载任务 ID。

  - **download_percentage**

    类型: number

    下载进度百分比，取值范围 [0,100]。

### onPlayProgress <span id="rtcvideocallback-onplayprogress"></span> 

音乐播放进度回调。

- **类型**

  ```ts
  (music_id: string, progress: number) => void
  ```

- **参数**

  - **music_id**

    类型: string

    音乐 ID。

  - **progress**

    类型: number

    音乐播放进度，单位为毫秒。

### onPlayStateChanged <span id="rtcvideocallback-onplaystatechanged"></span> 

音乐播放状态改变回调。

- **类型**

  ```ts
  (music_id: string, play_state: PlayState, error_code: KTVPlayerErrorCode) => void
  ```

- **注意**

  此回调被触发的时机汇总如下：
  + 调用 [playMusic](Electron-api#playmusic) 成功后，会触发 playState 值为 PlayStatePlaying 的回调；否则会触发 playState 值为 PlayStateFailed 的回调。
  + 使用相同的音乐 ID 重复调用 [playMusic](Electron-api#playmusic) 后，后一次播放会覆盖前一次，且会触发 playState 值为 PlayStatePlaying 的回调，表示后一次音乐播放已开始。
  + 调用 pauseMusic(Electron-api#pausemusic) 方法暂停播放成功后，会触发 playState 值为 PlayStatePaused 的回调；否则触发 playState 值为 PlayStateFailed 的回调。
  + 调用 resumeMusic(Electron-api#resumeMusic) 方法恢复播放成功后，会触发 playState 值为 PlayStatePlaying 的回调；否则触发 playState 值为 PlayStateFailed 的回调。
  + 调用 [stopMusic](Electron-api#stopmusic) 方法停止播放成功后，会触发 playState 值为 PlayStateStoped 的回调；否则触发 playState 值为 PlayStateFailed 的回调。
  + 音乐播放结束会触发 playState 值为 PlayStateFinished 的回调。

- **参数**

  - **music_id**

    类型: string

    音乐 ID。

  - **play_state**

    类型: [PlayState](Electron-keytype#playstate)

    音乐播放状态。

  - **error_code**

    类型: [KTVPlayerErrorCode](Electron-errorcode#ktvplayererrorcode)

    错误码。

### onTakeLocalSnapshotResult <span id="rtcvideocallback-ontakelocalsnapshotresult"></span> 

调用 `takeLocalSnapshot` 截取视频画面时，收到此回调。

- **类型**

  ```ts
  (task_id: number, stream_index: number, image: string, error_code: number) => void
  ```

- **参数**

  - **taskId**

    类型: number

    本地截图任务的编号。和 [takeLocalSnapshot](Electron-api#takelocalsnapshot) 的返回值一致。

  - **streamIndex**

    类型: number

    流属性，主流或屏幕流。

  - **image**

    类型: string

    截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。

  - **errorCode**

    类型: number

    截图错误码：
+ `0`: 成功
+ `-1`: 截图错误。生成图片数据失败或 RGBA 编码失败
+ `-2`: 截图错误。流无效。

### onTakeRemoteSnapshotResult <span id="rtcvideocallback-ontakeremotesnapshotresult"></span> 

调用 `takeRemoteSnapshot` 截取视频画面时，收到此回调。

- **类型**

  ```ts
  (task_id: number, stream_key: RemoteStreamKey, image: string, error_code: number) => void
  ```

- **参数**

  - **taskId**

    类型: number

    远端截图任务的编号。和 [takeRemoteSnapshot](Electron-api#takeremotesnapshot) 的返回值一致。

  - **streamKey**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    截图的视频流。

  - **image**

    类型: string

    截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。

  - **errorCode**

    类型: number

    截图错误码：
+ `0`: 成功
+ `-1`: 截图错误。生成图片数据失败或 RGBA 编码失败
+ `-2`: 截图错误。流无效。

### onCreateRoomStateChanged <span id="rtcvideocallback-oncreateroomstatechanged"></span> 

创建房间失败回调。

- **类型**

  ```ts
  (room_id: string, error_code: number) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID。

  - **error_code**

    类型: number

    创建房间错误码。

### onHttpProxyState <span id="rtcvideocallback-onhttpproxystate"></span> 

HTTP 代理连接状态改变时，收到该回调。

- **类型**

  ```ts
  (state: number) => void
  ```

- **参数**

  - **state**

    类型: number

    当前 HTTP 代理连接状态

### onHttpsProxyState <span id="rtcvideocallback-onhttpsproxystate"></span> 

HTTPS 代理连接状态改变时，收到该回调。

- **类型**

  ```ts
  (state: number) => void
  ```

- **参数**

  - **state**

    类型: number

    当前 HTTPS 代理连接状态

### onSocks5ProxyState <span id="rtcvideocallback-onsocks5proxystate"></span> 

SOCKS5 代理状态改变时，收到该回调。

- **类型**

  ```ts
  (state: number, cmd: string, proxy_address: string, local_address: string, remote_address: string) => void
  ```

- **参数**

  - **state**

    类型: number

    SOCKS5 代理连接状态

  - **cmd**

    类型: string

    代理连接的每一步操作命令

  - **proxy_address**

    类型: string

    代理地址信息

  - **local_address**

    类型: string

    当前连接使用的本地地址

  - **remote_address**

    类型: string

    远端的连接地址

### onStreamSyncInfoReceived <span id="rtcvideocallback-onstreamsyncinforeceived"></span> 

音频流同步信息回调。可以通过此回调，在远端用户调用 `sendStreamSyncInfo` 发送音频流同步消息后，收到远端发送的音频流同步信息。

- **类型**

  ```ts
  (stream_key: RemoteStreamKey, stream_type: SyncInfoStreamType, data: string) => void
  ```

- **参数**

  - **stream_key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端流信息

  - **stream_type**

    类型: SyncInfoStreamType

    媒体流类型

  - **data**

    类型: string

    消息内容。

### onScreenAudioFrameSendStateChanged <span id="rtcvideocallback-onscreenaudioframesendstatechanged"></span> 

屏幕音频首帧发送状态改变回调

- **类型**

  ```ts
  (room_id: string, user: RtcUser, state: FirstFrameSendState) => void
  ```

- **参数**

  - **room_id**

    类型: string

    音频发布用户所在的房间 ID

  - **user**

    类型: [RtcUser](Electron-keytype#rtcuser)

    本地用户信息

  - **state**

    类型: [FirstFrameSendState](Electron-keytype#firstframesendstate)

    首帧发送状态

### onScreenAudioFramePlayStateChanged <span id="rtcvideocallback-onscreenaudioframeplaystatechanged"></span> 

屏幕音频首帧播放状态改变回调

- **类型**

  ```ts
  (room_id: string, user: RtcUser, state: FirstFramePlayState) => void
  ```

- **参数**

  - **room_id**

    类型: string

    首帧播放状态发生改变的流所在的房间 ID

  - **user**

    类型: [RtcUser](Electron-keytype#rtcuser)

    远端用户信息

  - **state**

    类型: [FirstFramePlayState](Electron-keytype#firstframeplaystate)

    首帧播放状态

### onCloudProxyConnected <span id="rtcvideocallback-oncloudproxyconnected"></span> 

调用 `startCloudProxy` 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。

- **类型**

  ```ts
  (interval: number) => void
  ```

- **参数**

  - **interval**

    类型: number

    从开启云代理到连接成功经过的时间，单位为 ms

### onNetworkTimeSynchronized <span id="rtcvideocallback-onnetworktimesynchronized"></span> 

首次调用 `getNetworkTimeInfo` 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。

- **类型**

  ```ts
  () => void
  ```

### onLicenseWillExpire <span id="rtcvideocallback-onlicensewillexpire"></span> 

license过期时间提醒

- **类型**

  ```ts
  (days: number) => void
  ```

- **参数**

  - **days**

    类型: number

    过期时间天数

### onFaceDetectResult <span id="rtcvideocallback-onfacedetectresult"></span> 

特效 SDK 进行人脸检测结果的回调。
调用 `enableFaceDetection` 注册了回调，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。

- **类型**

  ```ts
  (result: FaceDetectResult) => this
  ```

- **参数**

  - **result**

    类型: [FaceDetectResult](Electron-keytype#facedetectresult)

    人脸检测结果

- **返回值**

  类型: this

### onAudioDeviceVolumeChanged <span id="rtcvideocallback-onaudiodevicevolumechanged"></span> 

音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。

- **类型**

  ```ts
  (device_type: RTCAudioDeviceType, volume: number, muted: boolean) => void
  ```

- **参数**

  - **device_type**

    类型: [RTCAudioDeviceType](Electron-keytype#rtcaudiodevicetype)

    设备类型，包括麦克风和扬声器。

  - **volume**

    类型: number

    音量值，[0, 255]。当 volume 变为 0 时，muted 会变为 true。注意：在 Windows 端，当麦克风 volume 变为 0 时，muted 值不变。

  - **muted**

    类型: boolean

    是否禁音状态。扬声器被设置为禁音时，muted 为 true，但 volume 保持不变。

### onCurrentScoringInfo <span id="rtcvideocallback-oncurrentscoringinfo"></span> 

实时评分信息回调。

- **类型**

  ```ts
  (info: SingScoringRealtimeInfo) => void
  ```

- **注意**

  调用 [startSingScoring](Electron-api#startsingscoring) 后，会收到该回调。

- **参数**

  - **info**

    类型: [SingScoringRealtimeInfo](Electron-keytype#singscoringrealtimeinfo)

    实时评分信息。

### onAudioRecordingStateUpdate <span id="rtcvideocallback-onaudiorecordingstateupdate"></span> 

调用 [startAudioRecording](Electron-api#startaudiorecording) 或 [stopAudioRecording](Electron-api#stopaudiorecording) 改变音频文件录制状态时，收到此回调。

- **类型**

  ```ts
  (state: AudioRecordingState, error_code: AudioRecordingErrorCode) => void
  ```

- **参数**

  - **state**

    类型: [AudioRecordingState](Electron-keytype#audiorecordingstate)

    录制状态

  - **errorCode**

    类型: [AudioRecordingErrorCode](Electron-errorcode#audiorecordingerrorcode)

    录制错误码

### onExtensionAccessError <span id="rtcvideocallback-onextensionaccesserror"></span> 

当访问插件失败时，收到此回调。
RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。

- **类型**

  ```ts
  (extensionName: string, msg: string) => void
  ```

- **参数**

  - **extensionName**

    类型: string

    插件名字

  - **msg**

    类型: string

    失败说明

### onPublicStreamDataMessageReceived <span id="rtcvideocallback-onpublicstreamdatamessagereceived"></span> 

回调公共流中包含的数据信息。
通过 [`startPlayPublicStream`](Electron-api#rtcvideo-startplaypublicstream)  订阅公共流后，通过监听本回调获取公共流中的数据消息，包括调用 Open API 发送的 SEI 消息和音量回调。

- **类型**

  ```ts
  (public_stream_id: string, message: Uint8Array, source_type: DataMessageSourceType) => void
  ```

- **注意**

  通过调用客户端 API 插入的 SEI 信息，应通过回调 [`onPublicStreamSEIMessageReceived`](Electron-event#rtcvideocallback-onpublicstreamseimessagereceived) 获取。

- **参数**

  - **public_stream_id**

    类型: string

    公共流 ID

  - **message**

    类型: Uint8Array

    收到的数据消息内容，如下：
+ 调用公共流 OpenAPI 发送的自定义消息。
+ 媒体流音量变化，需要通过公共流 OpenAPI 开启回调。JSON 格式说明如下：
```
{
    "Type" : "VolumeIndication", //具体业务类型
    "VolumeInfos"[                 // 业务类型对应信息
        {
            "RoomId":"1000001", // 房间ID
            "UserId":"1000001", // 用户ID
            "StreamType":0, // 0:摄像头流；1:屏幕流
            "LinearVolume":1 // 线性音量大小
        }
    ]
}
```

  - **message_length**

    类型: [DataMessageSourceType](Electron-keytype#datamessagesourcetype)

    消息的长度

### onHardwareEchoDetectionResult <span id="rtcvideocallback-onhardwareechodetectionresult"></span> 

通话前回声检测结果回调。

- **类型**

  ```ts
  (hardware_echo_detection_result: HardwareEchoDetectionResult) => void
  ```

- **注意**

  * + 通话前调用 [startHardwareEchoDetection](Electron-api#rtcvideo-starthardwareechodetection) 后，将触发本回调返回检测结果。
  + 建议在收到检测结果后，调用 [stopHardwareEchoDetection](Electron-api#rtcvideo-stophardwareechodetection) 停止检测，释放对音频设备的占用。
  + 如果 SDK 在通话中检测到回声，将通过 [onAudioDeviceWarning](Electron-event#rtcvideocallback-onaudiodevicewarning) 回调 `kMediaDeviceWarningLeakEchoDetected`。

- **参数**

  - **hardwareEchoDetectionResult**

    类型: [HardwareEchoDetectionResult](Electron-keytype#hardwareechodetectionresult)

    通话前回声检测结果

### onLocalProxyStateChanged <span id="rtcvideocallback-onlocalproxystatechanged"></span> 

本地代理状态发生改变回调。调用 [setLocalProxy](Electron-api#rtcvideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。

- **类型**

  ```ts
  (local_proxy_type: LocalProxyType, local_proxy_state: LocalProxyState, local_proxy_error: LocalProxyError) => void
  ```

- **参数**

  - **localProxyType**

    类型: [LocalProxyType](Electron-keytype#localproxytype)

    本地代理类型。

  - **localProxyState**

    类型: [LocalProxyState](Electron-keytype#localproxystate)

    本地代理状态。

  - **localProxyError**

    类型: [LocalProxyError](Electron-errorcode#localproxyerror)

    本地代理错误。

### onMixingEvent <span id="rtcvideocallback-onmixingevent"></span> 

转推直播状态回调

- **类型**

  ```ts
  (event: StreamMixingEvent, task_id: string, error: StreamMixingErrorCode, mix_type: MixedStreamType) => void
  ```

- **参数**

  - **event**

    类型: [StreamMixingEvent](Electron-keytype#streammixingevent)

    转推直播任务状态

  - **task_id**

    类型: string

    转推直播任务 ID

  - **error**

    类型: [StreamMixingErrorCode](Electron-errorcode#streammixingerrorcode)

    转推直播错误码

  - **mix_type**

    类型: [MixedStreamType](Electron-keytype#mixedstreamtype)

    转推直播类型

### onMixingVideoFrame <span id="rtcvideocallback-onmixingvideoframe"></span> 

合流视频回调，运行在视频回调线程

- **类型**

  ```ts
  (video_frame: IVideoFrame) => void
  ```

- **注意**

  收到该回调的周期与视频的帧间隔一致。

- **参数**

  - **video_frame**

    类型: [IVideoFrame](Electron-keytype#ivideoframe)

    视频帧

### onMixingAudioFrame <span id="rtcvideocallback-onmixingaudioframe"></span> 

合流音频回调，运行在音频回调线程

- **类型**

  ```ts
  (task_id: string, audio_frame: IAudioFrame) => void
  ```

- **注意**

  收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

- **参数**

  - **task_id**

    类型: string

    转推直播任务 ID

  - **audio_frame**

    类型: [IAudioFrame](Electron-keytype#iaudioframe)

    音频帧

### onMixingDataFrame <span id="rtcvideocallback-onmixingdataframe"></span> 

视频 SEI 帧回调，运行在视频回调线程

- **类型**

  ```ts
  (task_id: string, data_frame: IDataFrame) => void
  ```

- **参数**

  - **task_id**

    类型: string

    转推直播任务 ID

  - **data_frame**

    类型: [IDataFrame](Electron-keytype#idataframe)

    SEI 数据

### onClearCacheResult <span id="rtcvideocallback-onclearcacheresult"></span> 

清理文件缓存结果回调。

- **类型**

  ```ts
  (error_code: KTVErrorCode) => void
  ```

- **参数**

  - **error_code**

    类型: [KTVErrorCode](Electron-errorcode#ktverrorcode)

    错误码，非0为失败

### onFirstPublicStreamAudioFrame <span id="rtcvideocallback-onfirstpublicstreamaudioframe"></span> 

公共流的音频首帧解码成功

- **类型**

  ```ts
  (public_stream_id: string) => void
  ```

- **注意**

  关于订阅公共流，详见 [`startPlayPublicStream`](Electron-api#startplaypublicstream)。

- **参数**

  - **public_stream_id**

    类型: string

    公共流 ID

### onPushPublicStreamResult <span id="rtcvideocallback-onpushpublicstreamresult"></span> 

公共流发布结果回调。
调用 `startPushPublicStream` 接口发布公共流后，启动结果通过此回调方法通知用户。

- **类型**

  ```ts
  (room_id: string, public_stream_id: string, error_code: PublicStreamErrorCode) => void
  ```

- **注意**

  关于订阅公共流，详见 [`startPlayPublicStream`](Electron-api#startplaypublicstream)。

- **参数**

  - **room_id**

    类型: string

    房间 ID

  - **public_stream_id**

    类型: string

    公共流 ID

  - **error_code**

    类型: [PublicStreamErrorCode](Electron-errorcode#publicstreamerrorcode)

    公共流发布结果状态码。
+ `200`: 发布成功
+ `1191`: 推流参数存在异常
+ `1192`: 当前状态异常，通常为无法发起任务
+ `1193`: 服务端错误，不可恢复
+ `1195`: 服务端调用发布接口返回失败
+ `1196`: 超时无响应。推流请求发送后 10s 没有收到服务端的结果回调。客户端将每隔 10s 重试，3 次重试失败后停止。

### onFirstPublicStreamVideoFrameDecoded <span id="rtcvideocallback-onfirstpublicstreamvideoframedecoded"></span> 

公共流的首帧视频解码成功

- **类型**

  ```ts
  (public_stream_id: string, info: VideoFrameInfo) => void
  ```

- **注意**

  关于订阅公共流，详见 [`startPlayPublicStream`](Electron-api#startplaypublicstream)。

- **参数**

  - **public_stream_id**

    类型: string

    公共流 ID

  - **info**

    类型: [VideoFrameInfo](Electron-keytype#videoframeinfo)

    视频帧信息。

### onPublicStreamSEIMessageReceived <span id="rtcvideocallback-onpublicstreamseimessagereceived"></span> 

回调公共流中包含的 SEI 信息。
调用 [`startPlayPublicStream`](Electron-api#startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。

- **类型**

  ```ts
  (public_stream_id: string, message: string, source_type: DataMessageSourceType) => void
  ```

- **注意**

  通过 Open API 插入的自定义信息，应通过回调 [`onPublicStreamDataMessageReceived`](Electron-event#rtcvideocallback-onpublicstreamdatamessagereceived) 获取。

- **参数**

  - **public_stream_id**

    类型: string

    公共流 ID。

  - **message**

    类型: string

    收到的 SEI 消息内容。
通过调用客户端 `sendSEIMessage` 插入的 SEI 信息。
当公共流中的多路视频流均包含有 SEI 信息：SEI 不互相冲突时，将通过多次回调分别发送；SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。

  - **source_type**

    类型: [DataMessageSourceType](Electron-keytype#datamessagesourcetype)

    SEI 消息类型，自 3.52.1 版本后固定为 `0`，自定义消息。

### onPlayPublicStreamResult <span id="rtcvideocallback-onplaypublicstreamresult"></span> 

订阅公共流的结果回调
通过 [`startPlayPublicStream`](Electron-api#rtcvideo-startplaypublicstream)  订阅公共流后，可以通过本回调获取订阅结果。

- **类型**

  ```ts
  (public_stream_id: string, error_code: PublicStreamErrorCode) => void
  ```

- **参数**

  - **public_stream_id**

    类型: string

    公共流的 ID

  - **error_code**

    类型: [PublicStreamErrorCode](Electron-errorcode#publicstreamerrorcode)

    公共流订阅结果状态码。

### onLocalScreenFrame <span id="rtcvideocallback-onlocalscreenframe"></span> 

获取采集成功的本地屏幕视频帧，用于自定义处理或渲染。

- **类型**

  ```ts
  (frame: IVideoFrame) => void
  ```

- **参数**

  - **frame**

    类型: [IVideoFrame](Electron-keytype#ivideoframe)

    视频数据

### onLocalVideoFrame <span id="rtcvideocallback-onlocalvideoframe"></span> 

获取采集成功的本地摄像头流视频帧，用于自定义处理或渲染。

- **类型**

  ```ts
  (frame: IVideoFrame) => void
  ```

- **参数**

  - **frame**

    类型: [IVideoFrame](Electron-keytype#ivideoframe)

    视频数据

### onRemoteScreenFrame <span id="rtcvideocallback-onremotescreenframe"></span> 

视频管理获取采集成功的远端屏幕视频帧，用于自定义处理或渲染。

- **类型**

  ```ts
  (frame: IVideoFrame) => void
  ```

- **参数**

  - **frame**

    类型: [IVideoFrame](Electron-keytype#ivideoframe)

    视频数据

### onRemoteVideoFrame <span id="rtcvideocallback-onremotevideoframe"></span> 

获取采集成功的远端摄像头流视频帧，用于自定义处理或渲染。

- **类型**

  ```ts
  (frame: IVideoFrame) => void
  ```

- **注意**

  不同的平台上（macOS, Windows）上获取的视频帧的 pixelFormat 可能不同。

- **参数**

  - **frame**

    类型: [IVideoFrame](Electron-keytype#ivideoframe)

    视频数据

### onPublicStreamVideoFrame <span id="rtcvideocallback-onpublicstreamvideoframe"></span> 

公共流视频数据回调，绑定公共流到自定义渲染器后，通过该回调获取公共流视频数据。

- **类型**

  ```ts
  (frame: IVideoFrame) => void
  ```

- **参数**

  - **frame**

    类型: [IVideoFrame](Electron-keytype#ivideoframe)

    视频数据

### onWarning <span id="rtcvideocallback-onwarning"></span> 

当内部发生警告事件时触发该回调

- **类型**

  ```ts
  (warn: WarningCode) => void
  ```

- **参数**

  - **warn**

    类型: [WarningCode](Electron-errorcode#warningcode)

    警告标识码

### onError <span id="rtcvideocallback-onerror"></span> 

当内部发生不可逆转错误时触发该回调

- **类型**

  ```ts
  (err: ErrorCode) => void
  ```

- **参数**

  - **err**

    类型: [ErrorCode](Electron-errorcode#errorcode)

    错误标识码

### onAudioMixingFinished <span id="rtcvideocallback-onaudiomixingfinished"></span> 

本地音乐文件播放已结束回调。

- **类型**

  ```ts
  () => void
  ```

- **注意**

  当调用 [startAudioMixing](Electron-api#startaudiomixing) 启动的混音文件播放结束后，会触发该回调。

### onAudioMixingStateChanged <span id="rtcvideocallback-onaudiomixingstatechanged"></span> 

音频混音文件播放状态改变时回调

- **类型**

  ```ts
  (id: number, state: AudioMixingState, error: AudioMixingError) => void
  ```

- **注意**

  + 当调用 [startAudioMixing](Electron-api#startaudiomixing) 方法成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。
  + 当使用相同的 ID 重复调用 [startAudioMixing](Electron-api#startaudiomixing) 后，后一次会覆盖前一次，且本回调会以 kAudioMixingStateStopped 通知前一次混音已停止。
  + 当调用 [pauseAudioMixing](Electron-api#pauseaudiomixing) 方法暂停播放成功后，会触发 state 值为 kAudioMixingStatePaused 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。
  + 当调用 [resumeAudioMixing](Electron-api#resumeaudiomixing) 方法恢复播放成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。
  + 当调用 [stopAudioMixing](Electron-api#stopaudiomixing) 方法暂停止播放成功后，会触发 state 值为 kAudioMixingStateStopped 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。
  + 播放结束会触发 state 值为 kAudioMixingStateFinished 回调。

- **参数**

  - **id**

    类型: number

    混音 ID

  - **state**

    类型: [AudioMixingState](Electron-keytype#audiomixingstate)

    混音状态

  - **error**

    类型: [AudioMixingError](Electron-errorcode#audiomixingerror)

    错误码

### onAudioMixingPlayingProgress <span id="rtcvideocallback-onaudiomixingplayingprogress"></span> 

混音音频文件播放进度回调

- **类型**

  ```ts
  (mix_id: number, progress: number) => void
  ```

- **注意**

  调用 [setAudioMixingProgressInterval](Electron-api#setaudiomixingprogressinterval) 将时间间隔设为大于 0 的值后，或调用 [startAudioMixing](Electron-api#startaudiomixing) 将 AudioMixingConfig 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。

- **参数**

  - **mix_id**

    类型: number

    混音 ID

  - **progress**

    类型: number

    当前混音音频文件播放进度，单位毫秒

### onConnectionStateChanged <span id="rtcvideocallback-onconnectionstatechanged"></span> 

SDK 与信令服务器连接状态改变回调。连接状态改变时触发。

- **类型**

  ```ts
  (state: ConnectionState) => void
  ```

- **参数**

  - **state**

    类型: [ConnectionState](Electron-keytype#connectionstate)

    当前 SDK 与信令服务器的连接状态

### onNetworkTypeChanged <span id="rtcvideocallback-onnetworktypechanged"></span> 

SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。

- **类型**

  ```ts
  (type: NetworkType) => void
  ```

- **注意**

  更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。

- **参数**

  - **type**

    类型: [NetworkType](Electron-keytype#networktype)

    SDK 当前的网络连接类型

### onPerformanceAlarms <span id="rtcvideocallback-onperformancealarms"></span> 

本地未通过 [`setPublishFallbackOption`](Electron-api#rtcvideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。本地通过 [`setPublishFallbackOption`](Electron-api#rtcvideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。

- **类型**

  ```ts
  (mode: PerformanceAlarmMode, room_id: string, reason: PerformanceAlarmReason, data: SourceWantedData) => void
  ```

- **参数**

  - **mode**

    类型: [PerformanceAlarmMode](Electron-keytype#performancealarmmode)

    指示本地是否开启发布回退功能 <li> 当发布端未开启发布性能回退时，`mode` 值为 `kPerformanceAlarmModeNormal`。  </li><li>当发布端开启发布性能回退时，`mode` 值为 `kPerformanceAlarmModeSimulcast`。</li>

  - **room_id**

    类型: string

    <li>未开启发布性能回退时，`room_id` 为空 </li><li>开启发布性能回退时，`room_id` 是告警影响的房间 ID。</li>

  - **reason**

    类型: [PerformanceAlarmReason](Electron-keytype#performancealarmreason)

    告警原因

  - **data**

    类型: [SourceWantedData](Electron-keytype#sourcewanteddata)

    性能回退相关数据

### onSysStats <span id="rtcvideocallback-onsysstats"></span> 

周期性地发出回调，报告当前cpu与memory使用率

- **类型**

  ```ts
  (stats: SysStats) => void
  ```

- **参数**

  - **stats**

    类型: [SysStats](Electron-keytype#sysstats)

    返回包含当前系统状态信息的结构体

### onUserStartAudioCapture <span id="rtcvideocallback-onuserstartaudiocapture"></span> 

房间内的用户调用 `startAudioCapture` 开启音频采集时，房间内其他用户会收到此回调。

- **类型**

  ```ts
  (room_id: string, user_id: string) => void
  ```

- **参数**

  - **room_id**

    类型: string

    开启音频采集的远端用户所在的房间 ID

  - **user_id**

    类型: string

    开启音频采集的远端用户 ID

### onUserStopAudioCapture <span id="rtcvideocallback-onuserstopaudiocapture"></span> 

房间内的用户调用 `stopAudioCapture` 关闭音频采集时，房间内其他用户会收到此回调。

- **类型**

  ```ts
  (room_id: string, user_id: string) => void
  ```

- **参数**

  - **room_id**

    类型: string

    关闭音频采集的远端用户所在的房间 ID

  - **user_id**

    类型: string

    关闭音频采集的远端用户 ID

### onFirstLocalAudioFrame <span id="rtcvideocallback-onfirstlocalaudioframe"></span> 

本地采集到第一帧音频帧时，收到该回调

- **类型**

  ```ts
  (index: StreamIndex) => void
  ```

- **参数**

  - **index**

    类型: [StreamIndex](Electron-keytype#streamindex)

    音频流属性

### onFirstRemoteAudioFrame <span id="rtcvideocallback-onfirstremoteaudioframe"></span> 

收到房间内每一路音频流的第一帧时，收到该回调。

- **类型**

  ```ts
  (key: RemoteStreamKey) => void
  ```

- **参数**

  - **key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端音频流信息

### onSimulcastSubscribeFallback <span id="rtcvideocallback-onsimulcastsubscribefallback"></span> 

因发布/订阅性能回退或退出回退状态，订阅的音视频流，发生流的切换时，收到该回调。

- **类型**

  ```ts
  (event: RemoteStreamSwitch) => void
  ```

- **注意**

  你必须先通过 API 或控制台设置音视频流订阅回退功能时，你才能收到此回调。

- **参数**

  - **event**

    类型: [RemoteStreamSwitch](Electron-keytype#remotestreamswitch)

    流切换信息

### onFirstLocalVideoFrameCaptured <span id="rtcvideocallback-onfirstlocalvideoframecaptured"></span> 

第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。

- **类型**

  ```ts
  (index: StreamIndex, info: VideoFrameInfo) => void
  ```

- **参数**

  - **index**

    类型: [StreamIndex](Electron-keytype#streamindex)

    流属性

  - **info**

    类型: [VideoFrameInfo](Electron-keytype#videoframeinfo)

    视频信息

### onLocalVideoSizeChanged <span id="rtcvideocallback-onlocalvideosizechanged"></span> 

本地视频大小或旋转配置发生改变时，收到此回调。

- **类型**

  ```ts
  (index: StreamIndex, info: VideoFrameInfo) => void
  ```

- **参数**

  - **index**

    类型: [StreamIndex](Electron-keytype#streamindex)

    流属性

  - **info**

    类型: [VideoFrameInfo](Electron-keytype#videoframeinfo)

    视频帧信息

### onRemoteVideoSizeChanged <span id="rtcvideocallback-onremotevideosizechanged"></span> 

远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。

- **类型**

  ```ts
  (key: RemoteStreamKey, stream: VideoFrameInfo) => void
  ```

- **参数**

  - **key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端流信息

  - **stream**

    类型: [VideoFrameInfo](Electron-keytype#videoframeinfo)

    视频帧信息

### onFirstRemoteVideoFrameRendered <span id="rtcvideocallback-onfirstremotevideoframerendered"></span> 

第一帧远端视频流在视图上渲染成功后，收到此回调。

- **类型**

  ```ts
  (key: RemoteStreamKey, info: VideoFrameInfo) => void
  ```

- **参数**

  - **key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端流信息

  - **info**

    类型: [VideoFrameInfo](Electron-keytype#videoframeinfo)

    视频帧信息

### onFirstRemoteVideoFrameDecoded <span id="rtcvideocallback-onfirstremotevideoframedecoded"></span> 

SDK 接收并解码远端视频流首帧后，收到此回调。

- **类型**

  ```ts
  (key: RemoteStreamKey, info: VideoFrameInfo) => void
  ```

- **参数**

  - **key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端流信息。

  - **info**

    类型: [VideoFrameInfo](Electron-keytype#videoframeinfo)

    视频帧信息。

### onUserStartVideoCapture <span id="rtcvideocallback-onuserstartvideocapture"></span> 

房间内的用户调用 `startVideoCapture` 开启视频采集时，房间内其他用户会收到此回调。

- **类型**

  ```ts
  (room_id: string, user_id: string) => void
  ```

- **参数**

  - **room_id**

    类型: string

    开启视频采集的远端用户所在的房间 ID

  - **user_id**

    类型: string

    开启视频采集的远端用户 ID

### onUserStopVideoCapture <span id="rtcvideocallback-onuserstopvideocapture"></span> 

房间内的用户调用 `stopVideoCapture` 关闭视频采集时，房间内其他用户会收到此回调。

- **类型**

  ```ts
  (room_id: string, user_id: string) => void
  ```

- **参数**

  - **room_id**

    类型: string

    关闭视频采集的远端用户所在的房间 ID

  - **user_id**

    类型: string

    关闭视频采集的远端用户 ID

### onLocalAudioStateChanged <span id="rtcvideocallback-onlocalaudiostatechanged"></span> 

本地音频的状态发生改变时，该回调通知当前的本地音频状态。

- **已弃用**

  since 3.50. Use `onAudioDeviceStateChanged` instead.

- **类型**

  ```ts
  (state: LocalAudioStreamState, error: LocalAudioStreamError) => void
  ```

- **参数**

  - **state**

    类型: [LocalAudioStreamState](Electron-keytype#localaudiostreamstate)

    本地音频设备的状态

  - **error**

    类型: [LocalAudioStreamError](Electron-errorcode#localaudiostreamerror)

    本地音频状态改变时的错误码

### onRemoteAudioStateChanged <span id="rtcvideocallback-onremoteaudiostatechanged"></span> 

用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。

- **类型**

  ```ts
  (key: RemoteStreamKey, state: RemoteAudioState, reason: RemoteAudioStateChangeReason) => void
  ```

- **参数**

  - **key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端流信息

  - **state**

    类型: [RemoteAudioState](Electron-keytype#remoteaudiostate)

    远端音频流状态

  - **reason**

    类型: [RemoteAudioStateChangeReason](Electron-keytype#remoteaudiostatechangereason)

    远端音频流状态改变的原因

### onActiveSpeaker <span id="rtcvideocallback-onactivespeaker"></span> 

调用 `enableAudioPropertiesReport` 后，根据设置的 config.interval，你会周期性地收到此回调，获取房间内的最活跃用户信息。

- **类型**

  ```ts
  (room_id: string, uid: string) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID

  - **uid**

    类型: string

    最活跃用户（ActiveSpeaker）的用户 ID

### onLocalVideoStateChanged <span id="rtcvideocallback-onlocalvideostatechanged"></span> 

本地视频流的状态发生改变时，收到该事件。

- **已弃用**

  since 3.50. Use `onVideoDeviceStateChanged` instead.

- **类型**

  ```ts
  (index: StreamIndex, state: LocalVideoStreamState, error: LocalVideoStreamError) => void
  ```

- **参数**

  - **index**

    类型: [StreamIndex](Electron-keytype#streamindex)

    音/视频属性

  - **state**

    类型: [LocalVideoStreamState](Electron-keytype#localvideostreamstate)

    本地视频流状态

  - **error**

    类型: [LocalVideoStreamError](Electron-errorcode#localvideostreamerror)

    本地视频状态改变时的错误码

### onRemoteVideoStateChanged <span id="rtcvideocallback-onremotevideostatechanged"></span> 

远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。

- **类型**

  ```ts
  (key: RemoteStreamKey, state: RemoteVideoState, reason: RemoteVideoStateChangeReason) => void
  ```

- **注意**

  本回调仅适用于主流，不适用于屏幕流。

- **参数**

  - **key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端视频流的信息，房间、用户 ID、流属性等。

  - **state**

    类型: [RemoteVideoState](Electron-keytype#remotevideostate)

    远端视频流状态

  - **reason**

    类型: [RemoteVideoStateChangeReason](Electron-keytype#remotevideostatechangereason)

    远端视频流状态改变的原因

### onAudioFrameSendStateChanged <span id="rtcvideocallback-onaudioframesendstatechanged"></span> 

音频首帧发送状态改变回调

- **类型**

  ```ts
  (room_id: string, user: RtcUser, state: FirstFrameSendState) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID

  - **user**

    类型: [RtcUser](Electron-keytype#rtcuser)

    本地用户信息

  - **state**

    类型: [FirstFrameSendState](Electron-keytype#firstframesendstate)

    首帧发送状态

### onVideoFrameSendStateChanged <span id="rtcvideocallback-onvideoframesendstatechanged"></span> 

视频首帧发送状态改变回调

- **类型**

  ```ts
  (room_id: string, user: RtcUser, state: FirstFrameSendState) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID

  - **user**

    类型: [RtcUser](Electron-keytype#rtcuser)

    本地用户信息

  - **state**

    类型: [FirstFrameSendState](Electron-keytype#firstframesendstate)

    首帧发送状态

### onScreenVideoFrameSendStateChanged <span id="rtcvideocallback-onscreenvideoframesendstatechanged"></span> 

屏幕共享流视频首帧发送状态改变回调

- **类型**

  ```ts
  (room_id: string, user: RtcUser, state: FirstFrameSendState) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID

  - **user**

    类型: [RtcUser](Electron-keytype#rtcuser)

    本地用户信息

  - **state**

    类型: [FirstFrameSendState](Electron-keytype#firstframesendstate)

    首帧发送状态

### onAudioFramePlayStateChanged <span id="rtcvideocallback-onaudioframeplaystatechanged"></span> 

音频首帧播放状态改变回调

- **类型**

  ```ts
  (room_id: string, user: RtcUser, state: FirstFramePlayState) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID

  - **user**

    类型: [RtcUser](Electron-keytype#rtcuser)

    远端用户信息

  - **state**

    类型: [FirstFramePlayState](Electron-keytype#firstframeplaystate)

    首帧播放状态

### onVideoFramePlayStateChanged <span id="rtcvideocallback-onvideoframeplaystatechanged"></span> 

视频首帧播放状态改变回调

- **类型**

  ```ts
  (room_id: string, user: RtcUser, state: FirstFramePlayState) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID

  - **user**

    类型: [RtcUser](Electron-keytype#rtcuser)

    远端用户信息

  - **state**

    类型: [FirstFramePlayState](Electron-keytype#firstframeplaystate)

    首帧播放状态

### onScreenVideoFramePlayStateChanged <span id="rtcvideocallback-onscreenvideoframeplaystatechanged"></span> 

屏幕共享流视频首帧播放状态改变回调

- **类型**

  ```ts
  (room_id: string, user: RtcUser, state: FirstFramePlayState) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间id

  - **user**

    类型: [RtcUser](Electron-keytype#rtcuser)

    远端用户信息

  - **state**

    类型: [FirstFramePlayState](Electron-keytype#firstframeplaystate)

    首帧播放状态

### onUserMessageSendResult <span id="rtcvideocallback-onusermessagesendresult"></span> 

当调用 sendMessageToUser 函数发送消息后，回调此条消息的发送结果（反馈）。

- **类型**

  ```ts
  (msgid: number, error: MessageSendResultCode) => void
  ```

- **参数**

  - **msgid**

    类型: number

    本条消息的 ID

  - **error**

    类型: [MessageSendResultCode](Electron-errorcode#messagesendresultcode)

    消息发送结果

### onUserBinaryMessageReceived <span id="rtcvideocallback-onuserbinarymessagereceived"></span> 

单个用户接收到同一房间内其他 uid 所属用户发来二进制消息的回调（P2P）。

- **类型**

  ```ts
  (uid: string, message: string) => void
  ```

- **注意**

  同一房间内其他用户调用 [sendUserBinaryMessage](Electron-api#senduserbinarymessage) 发送二进制消息给本地用户时，本地用户会收到该回调。

- **参数**

  - **uid**

    类型: string

    消息发送者 ID 。

  - **message**

    类型: string

    收到的二进制消息内容。

### onStreamSubscribed <span id="rtcvideocallback-onstreamsubscribed"></span> 

当订阅一个流成功的时候回调该事件

- **类型**

  ```ts
  (state_code: SubscribeState, user_id: string, info: SubscribeConfig) => void
  ```

- **注意**

  当更新流的内容时比如增加或者减少音视频流成功更新时也会回调该事件

- **参数**

  - **state_code**

    类型: [SubscribeState](Electron-keytype#subscribestate)

    订阅流的结果

  - **user_id**

    类型: string

    用户的标识

  - **info**

    类型: [SubscribeConfig](Electron-keytype#subscribeconfig)

    流的属性

### onSEIMessageReceived <span id="rtcvideocallback-onseimessagereceived"></span> 

收到通过 `sendSEIMessage` 发送的带有 SEI 消息的视频帧时，收到此回调

- **类型**

  ```ts
  (stream_key: RemoteStreamKey, message: string) => void
  ```

- **参数**

  - **stream_key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    包含 SEI 发送者的用户名，所在的房间名和媒体流

  - **message**

    类型: string

    收到的 SEI 消息内容

### onStreamPushEvent <span id="rtcvideocallback-onstreampushevent"></span> 

单流转推直播状态回调

- **类型**

  ```ts
  (event: SingleStreamPushEvent, task_id: string, error: number) => void
  ```

- **参数**

  - **event**

    类型: [SingleStreamPushEvent](Electron-keytype#singlestreampushevent)

    事件类型

  - **task_id**

    类型: string

    任务 ID

  - **error**

    类型: number

    错误类型
+ `0`: 推流成功。
+ `1090`: 未定义的合流错误。
+ `1091`: 客户端 SDK 检测到无效推流参数。
+ `1092`: 状态错误，需要在状态机正常状态下发起操作。
+ `1093`: 无效操作。
+ `1094`: 转推直播任务处理超时，请检查网络状态并重试。
+ `1095`: 服务端检测到错误的推流参数。
+ `1096`: 对流的订阅超时。
+ `1097`: 合流服务端内部错误。
+ `1098`: 合流服务端推 CDN 失败。
+ `1099`: 服务端接收信令超时，请检查网络状态并重试。
+ `1100`: 图片合流失败。
+ `1101`: 服务端未知错误。

### onRecordingStateUpdate <span id="rtcvideocallback-onrecordingstateupdate"></span> 

获取本地录制状态回调。

- **类型**

  ```ts
  (type: StreamIndex, state: number, error_code: number, info: RecordingInfo) => void
  ```

- **注意**

  该回调由 [`startFileRecording`](Electron-api#startfilerecording) 或 [`stopFileRecording`](Electron-api#stopfilerecording) 触发。

- **参数**

  - **type**

    类型: [StreamIndex](Electron-keytype#streamindex)

    录制流的流属性

  - **state**

    类型: number

    录制状态

  - **error_code**

    类型: number

    录制错误码

  - **info**

    类型: [RecordingInfo](Electron-keytype#recordinginfo)

    录制文件的详细信息

### onRecordingProgressUpdate <span id="rtcvideocallback-onrecordingprogressupdate"></span> 

本地录制进度回调。

- **类型**

  ```ts
  (type: StreamIndex, process: RecordingProgress, info: RecordingInfo) => void
  ```

- **注意**

  该回调由 [`startFileRecording`](Electron-api#startfilerecording) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。

- **参数**

  - **type**

    类型: [StreamIndex](Electron-keytype#streamindex)

    录制流的流属性

  - **process**

    类型: [RecordingProgress](Electron-keytype#recordingprogress)

    录制进度

  - **info**

    类型: [RecordingInfo](Electron-keytype#recordinginfo)

    录制文件的详细信息

### onLoginResult <span id="rtcvideocallback-onloginresult"></span> 

调用 `login` 后，会收到此回调。

- **类型**

  ```ts
  (uid: string, error_code: number, elapsed: number) => void
  ```

- **参数**

  - **uid**

    类型: string

    登录用户 ID

  - **error_code**

    类型: number

    登录结果

  - **elapsed**

    类型: number

    从调用 [login](Electron-api#rtcvideo-login) 接口开始到返回结果所用时长，单位为 ms。

### onLogout <span id="rtcvideocallback-onlogout"></span> 

登出结果回调

- **类型**

  ```ts
  (reason: LogoutReason) => void
  ```

- **注意**

  调用 [logout](Electron-api#rtcvideo-logout) 后，会收到此回调。

- **参数**

  - **reason**

    类型: [LogoutReason](Electron-keytype#logoutreason)

    用户登出的原因

### onServerParamsSetResult <span id="rtcvideocallback-onserverparamssetresult"></span> 

设置业务服务器参数的返回结果

- **类型**

  ```ts
  (error: number) => void
  ```

- **注意**

  调用 [setServerParams](Electron-api#setserverparams) 后，会收到此回调。

- **参数**

  - **error**

    类型: number

    设置结果  <li>返回 200，设置成功 </li><li>返回其他，设置失败</li>

### onGetPeerOnlineStatus <span id="rtcvideocallback-ongetpeeronlinestatus"></span> 

查询对端或本端用户登录状态的返回结果

- **类型**

  ```ts
  (peer_user_id: string, status: number) => void
  ```

- **注意**

  必须先调用 [getPeeronlineStatus](Electron-api#getpeeronlinestatus)，才能收到此回调。

- **参数**

  - **peer_user_id**

    类型: string

    需要查询的用户 ID

  - **status**

    类型: number

    查询的用户登录状态

### onUserMessageReceivedOutsideRoom <span id="rtcvideocallback-onusermessagereceivedoutsideroom"></span> 

收到房间外用户调用 `sendUserMessageOutsideRoom` 发来的文本消息时，会收到此回调

- **类型**

  ```ts
  (uid: string, message: string) => void
  ```

- **参数**

  - **uid**

    类型: string

    消息发送者 ID

  - **message**

    类型: string

    收到的文本消息内容

### onUserBinaryMessageReceivedOutsideRoom <span id="rtcvideocallback-onuserbinarymessagereceivedoutsideroom"></span> 

收到房间外用户调用 `sendUserBinaryMessageOutsideRoom` 发来的二进制消息时，会收到此回调

- **类型**

  ```ts
  (uid: string, message: string) => void
  ```

- **参数**

  - **uid**

    类型: string

    消息发送者 ID

  - **message**

    类型: string

    收到的二进制消息内容

### onUserMessageSendResultOutsideRoom <span id="rtcvideocallback-onusermessagesendresultoutsideroom"></span> 

给房间外指定的用户发送消息的回调

- **类型**

  ```ts
  (msgid: number, error: number) => void
  ```

- **注意**

  当调用 [sendUserMessageOutsideRoom](Electron-api#sendusermessageoutsideroom) 或 [sendUserBinaryMessageOutsideRoom](Electron-api#senduserbinarymessageoutsideroom) 发送消息后，会收到此回调。

- **参数**

  - **msgid**

    类型: number

    本条消息的 ID。所有的 P2P 和 P2Server 消息共用一个 ID 序列。

  - **error**

    类型: number

    消息发送结果

### onServerMessageSendResult <span id="rtcvideocallback-onservermessagesendresult"></span> 

给业务服务器发送消息的回调

- **类型**

  ```ts
  (msgid: number, error: number, msg: string) => void
  ```

- **注意**

  当调用 [sendServerMessage](Electron-api#sendservermessage) 或 [sendServerBinaryMessage](Electron-api#sendserverbinarymessage) 接口发送消息后，会收到此回调。

- **参数**

  - **msgid**

    类型: number

    本条消息的 ID。所有的 P2P 和 P2Server 消息共用一个 ID 序列。

  - **error**

    类型: number

    消息发送结果

  - **msg**

    类型: string

    应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。

### onRecordAudioFrame <span id="rtcvideocallback-onrecordaudioframe"></span> 

返回麦克风录制的音频数据

- **类型**

  ```ts
  (audio_frame: IAudioFrame) => void
  ```

- **参数**

  - **audio_frame**

    类型: [IAudioFrame](Electron-keytype#iaudioframe)

    麦克风录制的音频数据

### onPlaybackAudioFrame <span id="rtcvideocallback-onplaybackaudioframe"></span> 

返回远端所有用户混音后的音频数据

- **类型**

  ```ts
  (audio_frame: IAudioFrame) => void
  ```

- **参数**

  - **audio_frame**

    类型: [IAudioFrame](Electron-keytype#iaudioframe)

    远端所有用户混音后的音频数据

### onMixedAudioFrame <span id="rtcvideocallback-onmixedaudioframe"></span> 

返回本地麦克风录制和远端所有用户混音后的音频数据

- **类型**

  ```ts
  (audio_frame: IAudioFrame) => void
  ```

- **参数**

  - **audio_frame**

    类型: [IAudioFrame](Electron-keytype#iaudioframe)

    本地麦克风录制和远端所有用户混音后的音频数据

### onASRSuccess <span id="rtcvideocallback-onasrsuccess"></span> 

语音识别服务开启成功回调

- **类型**

  ```ts
  () => void
  ```

### onMessage <span id="rtcvideocallback-onmessage"></span> 

语音转文字成功回调，该回调返回识别后的全量消息。

- **类型**

  ```ts
  (message: string) => void
  ```

- **注意**

  若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。

- **参数**

  - **message**

    类型: string

    识别完成后得到的文字消息

### onASRError <span id="rtcvideocallback-onasrerror"></span> 

当语音识别服务内部发生错误事件时触发该回调。

- **类型**

  ```ts
  (error_code: number, error_message: string) => void
  ```

- **参数**

  - **error_code**

    类型: number

    错误码  <0: 参数错误或 API 调用顺序错误
+ `-1`: 网络连接中断，服务不可用，内部会进行重连
+ `-2`: 重复调用 startASR。开启语音识别服务后，你需要先调用 stopASR 停止语音识别服务，才能二次调用 startASR 再次开启服务。
+ `-3`: 语音识别服务所需 token 为空
+ `-4`: Signature 鉴权模式下 secret_key 为空
+ `-5`: 用户 ID 为空
+ `-6`: 应用 ID 为空
+ `-7`: 语音识别服务 cluster 为空
+ `-8`: 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。

  - **error_message**

    类型: string

    错误原因说明

### onNetworkDetectionResult <span id="rtcvideocallback-onnetworkdetectionresult"></span> 

成功调用 `startNetworkDetection` 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。

- **类型**

  ```ts
  (type: number, quality: number, rtt: number, lost_rate: number, bit_rate: number, jitter: number) => void
  ```

- **参数**

  - **type**

    类型: number

    探测网络类型为上行/下行

  - **quality**

    类型: number

    探测网络的质量
+ `0`: 网络质量未知。
+ `1`: 网络质量极好。
+ `2`: 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
+ `3`: 主观感受有瑕疵但不影响沟通。
+ `4`: 勉强能沟通但不顺畅。
+ `5`: 网络质量非常差，基本不能沟通。

  - **rtt**

    类型: number

    探测网络的 RTT，单位：ms

  - **lost_rate**

    类型: number

    探测网络的丢包率

  - **bit_rate**

    类型: number

    探测网络的带宽，单位：kbps

  - **jitter**

    类型: number

    探测网络的抖动,单位：ms

### onNetworkDetectionStopped <span id="rtcvideocallback-onnetworkdetectionstopped"></span> 

通话前网络探测结束

- **类型**

  ```ts
  (reason: number) => void
  ```

- **注意**

  以下情况将停止探测并收到本一次本回调：
  + 当调用 [`stopNetworkDetection`](Electron-api#stopnetworkdetection) 接口停止探测后，会收到一次该回调；
  + 当收到远端/本端音频首帧后，停止探测；
  + 当探测超过3分钟后，停止探测；
  + 当探测链路断开一定时间之后，停止探测。

- **参数**

  - **reason**

    类型: number

    停止探测的原因类型
+ `0`: 用户主动停止
+ `1`: 探测超过三分钟
+ `2`: 探测网络连接断开。当超过 12s 没有收到回复，SDK 将断开网络连接，并且不再尝试重连。
+ `3`: 本地开始推拉流，停止探测
+ `4`: 网络探测失败，内部异常

### onLocalAudioPropertiesReport <span id="rtcvideocallback-onlocalaudiopropertiesreport"></span> 

调用 `enableAudioPropertiesReport` 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。

- **类型**

  ```ts
  (audio_properties_infos: LocalAudioPropertiesInfo[], audio_properties_info_number: number) => void
  ```

- **参数**

  - **audio_properties_infos**

    类型: [LocalAudioPropertiesInfo](Electron-keytype#localaudiopropertiesinfo)[]

    本地音频信息。本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。

  - **audio_properties_info_number**

    类型: number

    数组长度，无需关注

### onRemoteAudioPropertiesReport <span id="rtcvideocallback-onremoteaudiopropertiesreport"></span> 

远端用户进房后，本地调用 `enableAudioPropertiesReport`，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。

- **类型**

  ```ts
  (audio_properties_infos: RemoteAudioPropertiesInfo[], audio_properties_info_number: number, total_remote_volume: number) => void
  ```

- **参数**

  - **audio_properties_infos**

    类型: [RemoteAudioPropertiesInfo](Electron-keytype#remoteaudiopropertiesinfo)[]

    远端音频信息，其中包含音频流属性、房间 ID、用户 ID。远端用户的音频包括使用 RTC SDK 采集的麦克风音频和屏幕音频。

  - **audio_properties_info_number**

    类型: number

    数组长度，无需关注

  - **total_remote_volume**

    类型: number

    订阅的所有远端流混音后的总音量，范围是 [0,255]。<br><ul><li>[0,25] 接近无声；</li><li>[25,75] 为低音量；</li><li>[76,204] 为中音量；</li><li>[205,255] 为高音量。</li></ul>

### onEchoTestResult <span id="rtcvideocallback-onechotestresult"></span> 

通话前网络探测结束

- **类型**

  ```ts
  (result: EchoTestResult) => void
  ```

- **注意**

  该回调触发的时机包括：
  + 检测过程中采集设备发生错误时；
  + 检测成功后；
  + 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。

- **参数**

  - **result**

    类型: [EchoTestResult](Electron-keytype#echotestresult)

    + kTestSuccess	0:	接收到采集的音视频的回放，通话回路检测成功
+ kTestTimeout 1:	测试超过 60s 仍未完成，已自动停止
+ kTestIntervalShort 2:	上一次测试结束和下一次测试开始之间的时间间隔少于 5s
+ kAudioDeviceError	3:	音频采集异常
+ kVideoDeviceError	4:	视频采集异常
+ kAudioReceiveError	5:	音频接收异常
+ kVideoReceiveError	6:	视频接收异常
+ kInternalError	7:	内部错误，不可恢复

### onVideoDeviceStateChanged <span id="rtcvideocallback-onvideodevicestatechanged"></span> 

视频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。

- **类型**

  ```ts
  (device_id: string, device_type: number, device_state: number, device_error: number) => void
  ```

- **参数**

  - **device_id**

    类型: string

    设备 ID。采集屏幕共享流时，设备 ID 为固定字符串 screen_capture_video

  - **device_type**

    类型: number

    设备类型
+ `-1`: 未知设备类型
+ `0`: 视频渲染设备类型
+ `1`: 视频采集设备类型
+ `2`: 屏幕流视频设备

  - **device_state**

    类型: number

    设备状态
+ `1`: 设备已开启
+ `2`: 设备已停止
+ `3`: 设备运行时错误。例如，当媒体设备的预期行为是正常采集，但没有收到采集数据时，将回调该状态。
+ `4`: 设备已暂停。包括：
+ 采集过程中，目标应用窗体最小化到任务栏。
+ 开启采集或采集过程中，目标应用窗体被隐藏。
+ 采集过程中，目标应用窗体正在被拉伸。
+ 采集过程中，目标应用窗体正在被拖动。
+ `5`: 设备已恢复
+ `10`: 设备已插入
+ `11`: 设备被移除
+ `12`: 用户合盖打断了视频通话。如果系统未休眠或关机，将在开盖后自动恢复视频通话。
+ `13`: 视频通话已从合盖打断中恢复
+ `14`: 设备成为系统默认
+ `15`: 设备不再是系统默认
+ `16`:  获取设备列表超时后，收到设备列表通知。再次调用获取设备接口更新设备列表。

  - **device_error**

    类型: number

    设备错误类型
+ `0`: 媒体设备正常
+ `1`: 没有权限启动媒体设备
+ `2`: 媒体设备已经在使用中
+ `3`: 媒体设备错误
+ `4`: 未找到指定的媒体设备
+ `5`: 媒体设备被移除，对象为采集屏幕流时，表明窗体被关闭或显示器被移除。
+ `6`: 设备没有数据回调
+ `7`: 设备采样率不支持

### onAudioDeviceStateChanged <span id="rtcvideocallback-onaudiodevicestatechanged"></span> 

音频设备状态回调。提示音频采集、音频播放等设备设备的状态。

- **类型**

  ```ts
  (device_id: string, device_type: number, device_state: number, device_error: number) => void
  ```

- **参数**

  - **device_id**

    类型: string

    设备 ID

  - **device_type**

    类型: number

    设备类型
+ `-1`: 未知设备类型
+ `0`: 音频渲染设备类型
+ `1`: 音频采集设备类型
+ `2`: 屏幕流音频设备

  - **device_state**

    类型: number

    设备状态
+ `1`: 设备已开启
+ `2`: 设备已停止
+ `3`: 设备运行时错误。例如，当媒体设备的预期行为是正常采集，但没有收到采集数据时，将回调该状态。
+ `4`: 设备已暂停。包括：
+ 采集过程中，目标应用窗体最小化到任务栏。
+ 开启采集或采集过程中，目标应用窗体被隐藏。
+ 采集过程中，目标应用窗体正在被拉伸。
+ 采集过程中，目标应用窗体正在被拖动。
+ `5`: 设备已恢复
+ `10`: 设备已插入
+ `11`: 设备被移除
+ `12`: 用户合盖打断了视频通话。如果系统未休眠或关机，将在开盖后自动恢复视频通话。
+ `13`: 通话已从合盖打断中恢复
+ `14`: 设备成为系统默认
+ `15`: 设备不再是系统默认

  - **device_error**

    类型: number

    设备错误类型
+ `0`: 媒体设备正常
+ `1`: 没有权限启动媒体设备
+ `2`: 媒体设备已经在使用中
+ `3`: 媒体设备错误
+ `4`: 未找到指定的媒体设备
+ `5`: 媒体设备被移除，对象为采集屏幕流时，表明窗体被关闭或显示器被移除。
+ `6`: 设备没有数据回调
+ `7`: 设备采样率不支持

### onAudioPlaybackDeviceTestVolume <span id="rtcvideocallback-onaudioplaybackdevicetestvolume"></span> 

回调音频设备测试时的播放音量

- **类型**

  ```ts
  (volume: number) => void
  ```

- **注意**

  调用 [`startAudioPlaybackDeviceTest`](Electron-api#startaudioplaybackdevicetest) 开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。

- **参数**

  - **volume**

    类型: number

    音频设备测试播放音量。单位：毫秒。推荐设置为 200 ms。范围：[0,255]

### onRemoteUserAudioFrame <span id="rtcvideocallback-onremoteuseraudioframe"></span> 

返回远端单个用户的音频数据

- **类型**

  ```ts
  (stream_info: RemoteStreamKey, audio_frame: IAudioFrame) => void
  ```

- **注意**

  此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。

- **参数**

  - **stream_info**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端流信息

  - **audio_frame**

    类型: [IAudioFrame](Electron-keytype#iaudioframe)

    音频数据

### onRecordScreenAudioFrame <span id="rtcvideocallback-onrecordscreenaudioframe"></span> 

返回本地屏幕录制的音频数据

- **类型**

  ```ts
  (audio_frame: IAudioFrame) => void
  ```

- **参数**

  - **audio_frame**

    类型: [IAudioFrame](Electron-keytype#iaudioframe)

    音频数据

### onAudioDeviceWarning <span id="rtcvideocallback-onaudiodevicewarning"></span> 

音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。

- **类型**

  ```ts
  (device_id: string, device_type: RTCAudioDeviceType, device_warning: MediaDeviceWarning) => void
  ```

- **参数**

  - **device_id**

    类型: string

    设备 ID

  - **device_type**

    类型: [RTCAudioDeviceType](Electron-keytype#rtcaudiodevicetype)

    设备类型

  - **device_warning**

    类型: [MediaDeviceWarning](Electron-keytype#mediadevicewarning)

    告警信息

### onVideoDeviceWarning <span id="rtcvideocallback-onvideodevicewarning"></span> 

视频设备警告回调，包括视频采集设备等。

- **类型**

  ```ts
  (device_id: string, device_type: RTCAudioDeviceType, device_warning: MediaDeviceWarning) => void
  ```

- **参数**

  - **device_id**

    类型: string

    设备 ID

  - **device_type**

    类型: [RTCAudioDeviceType](Electron-keytype#rtcaudiodevicetype)

    设备类型

  - **device_warning**

    类型: [MediaDeviceWarning](Electron-keytype#mediadevicewarning)

    告警信息

### onSEIStreamUpdate <span id="rtcvideocallback-onseistreamupdate"></span> 

黑帧视频流发布状态回调。

- **类型**

  ```ts
  (key: RemoteStreamKey, type: SEIStreamEventType) => void
  ```

- **注意**

  + 在语音通话场景下，本地用户调用 [`sendSEIMessage`](Electron-api#rtcvideo-sendseimessage) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。
  + 你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。

- **参数**

  - **key**

    类型: [RemoteStreamKey](Electron-keytype#remotestreamkey)

    远端流信息

  - **type**

    类型: [SEIStreamEventType](Electron-keytype#seistreameventtype)

    黑帧视频流状态


## RTCROOMCALLBACK <span id="rtcroomcallback"></span>

类型: `interface`

- **API**

| 方法 | 描述 |
| :-- | :-- |
| [onUserVisibilityChanged](#rtcroomcallback-onuservisibilitychanged) | 用户调用 [setUserVisibility](Electron-api#rtcroom-setuservisibility) 设置用户可见性的回调。 |
| [onRoomStateChanged](#rtcroomcallback-onroomstatechanged) | 房间状态改变回调，加入房间、离开房间、发生房间相关的警告或错误时会收到此回调。 |
| [onStreamStateChanged](#rtcroomcallback-onstreamstatechanged) | 流状态改变回调，发生流相关的警告或错误时会收到此回调。 |
| [onLeaveRoom](#rtcroomcallback-onleaveroom) | 离开房间成功回调。 |
| [onUserJoined](#rtcroomcallback-onuserjoined) | 可见用户加入房间，或房内不可见用户切换为可见的回调。<br>1.远端可见用户调用 `setUserVisibility` 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。<br>2.远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。<br>3.房间内不可见远端用户调用 `setUserVisibility` 方法切换至可见时，房间内其他用户将收到该事件。<br>4.新进房用户也会收到进房前已在房内的可见角色用户的进房回调通知。 |
| [onUserLeave](#rtcroomcallback-onuserleave) | 远端用户离开房间，或切至不可见时，本地用户会收到此事件 |
| [onTokenWillExpire](#rtcroomcallback-ontokenwillexpire) | 当 SDK 检测到 Token 的进房权限将在 30 秒内过期时，触发该回调。 |
| [onAVSyncStateChange](#rtcroomcallback-onavsyncstatechange) | 发布端调用 `setMultiDeviceAVSync` 后音视频同步状态发生改变时，会收到此回调。 |
| [onRoomStats](#rtcroomcallback-onroomstats) | 房间通话统计信息回调。<br>用户进房开始通话后，每 2s 收到一次本回调。 |
| [onLocalStreamStats](#rtcroomcallback-onlocalstreamstats) | 反映通话中本地设备发送音/视频流的统计信息以及网络状况的回调。<br>本地用户发布音视频流成功后，每隔 2s 收到此回调。 |
| [onRemoteStreamStats](#rtcroomcallback-onremotestreamstats) | 反映通话中本地设备接收订阅的远端音/视频流的统计信息以及网络状况的回调。每隔 2s 收到此回调。 |
| [onUserPublishStream](#rtcroomcallback-onuserpublishstream) | 房间内新增远端麦克风采集的音频流的回调。 |
| [onUserUnpublishStream](#rtcroomcallback-onuserunpublishstream) | 房间内远端麦克风采集的音频流移除的回调。 |
| [onUserPublishScreen](#rtcroomcallback-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](#rtcroomcallback-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onStreamSubscribed](#rtcroomcallback-onstreamsubscribed) | 关于订阅媒体流状态改变的回调 |
| [onVideoStreamBanned](#rtcroomcallback-onvideostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。 |
| [onAudioStreamBanned](#rtcroomcallback-onaudiostreambanned) | 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。 |
| [onRoomMessageReceived](#rtcroomcallback-onroommessagereceived) | 接收到房间内广播消息的回调。 |
| [onRoomBinaryMessageReceived](#rtcroomcallback-onroombinarymessagereceived) | 接收到房间内广播二进制消息的回调。 |
| [onUserMessageReceived](#rtcroomcallback-onusermessagereceived) | 收到来自房间中其他用户通过 `sendUserMessage` 发来的点对点文本消息时，会收到此回调。 |
| [onUserBinaryMessageReceived](#rtcroomcallback-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 `sendUserBinaryMessage` 发来的点对点二进制消息时，会收到此回调。 |
| [onUserMessageSendResult](#rtcroomcallback-onusermessagesendresult) | 向房间内单个用户发送点对点文本或点对点二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onRoomMessageSendResult](#rtcroomcallback-onroommessagesendresult) | 调用 `sendRoomMessage` 或 `sendRoomBinaryMessage` 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。 |
| [onForwardStreamStateChanged](#rtcroomcallback-onforwardstreamstatechanged) | 跨房间媒体流转发状态和错误回调 |
| [onForwardStreamEvent](#rtcroomcallback-onforwardstreamevent) | 跨房间媒体流转发事件回调 |
| [onNetworkQuality](#rtcroomcallback-onnetworkquality) | 加入房间后， 以 2 秒 1 次的频率，报告用户的网络质量信息 |
| [onPublishPrivilegeTokenWillExpire](#rtcroomcallback-onpublishprivilegetokenwillexpire) | Token 发布权限过期前 30 秒将触发该回调。 |
| [onSubscribePrivilegeTokenWillExpire](#rtcroomcallback-onsubscribeprivilegetokenwillexpire) | Token 订阅权限过期前 30 秒将触发该回调。 |
| [onSetRoomExtraInfoResult](#rtcroomcallback-onsetroomextrainforesult) | 调用 [setRoomExtraInfo](Electron-api#rtcroom-setroomextrainfo) 设置房间附加信息结果的回调。 |
| [onRoomExtraInfoUpdate](#rtcroomcallback-onroomextrainfoupdate) | 接收同一房间内，其他用户调用 [setRoomExtraInfo](Electron-api#rtcroom-setroomextrainfo) 设置的房间附加信息的回调。 |
| [onSubtitleStateChanged](#rtcroomcallback-onsubtitlestatechanged) | 字幕状态发生改变回调。<br>当用户调用 [startSubtitle](Electron-api#startsubtitle) 和 [stopSubtitle](Electron-api#stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。 |
| [onSubtitleMessageReceived](#rtcroomcallback-onsubtitlemessagereceived) | 字幕相关内容回调。<br>当用户成功调用 [startSubtitle](Electron-api#startsubtitle) 后会收到此回调，通知字幕的相关信息。 |

### onUserVisibilityChanged <span id="rtcroomcallback-onuservisibilitychanged"></span> 

用户调用 [setUserVisibility](Electron-api#rtcroom-setuservisibility) 设置用户可见性的回调。

- **类型**

  ```ts
  (current_user_visibility: boolean, error_code: UserVisibilityChangeError) => void
  ```

- **参数**

  - **current_user_visibility**

    类型: boolean

    当前用户的可见性。
+ true: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。
+ false: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。

  - **error_code**

    类型: [UserVisibilityChangeError](Electron-errorcode#uservisibilitychangeerror)

    设置用户可见性错误码

### onRoomStateChanged <span id="rtcroomcallback-onroomstatechanged"></span> 

房间状态改变回调，加入房间、离开房间、发生房间相关的警告或错误时会收到此回调。

- **类型**

  ```ts
  (room_id: string, uid: string, state: number, extra_info: string) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID。

  - **uid**

    类型: string

    用户 ID。

  - **state**

    类型: number

    房间状态码。
+ 0: 成功。
+ !0: 失败，参看 [ErrorCode](Electron-errorcode#errorcode) 及 [WarningCode](Electron-errorcode#warningcode)。

  - **extra_info**

    类型: string

    额外信息。
`joinType`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
`elapsed`表示加入房间耗时，即本地用户从调用 [joinRoom](Electron-api#joinroom) 到加入房间成功所经历的时间间隔，单位为 ms。

### onStreamStateChanged <span id="rtcroomcallback-onstreamstatechanged"></span> 

流状态改变回调，发生流相关的警告或错误时会收到此回调。

- **类型**

  ```ts
  (room_id: string, uid: string, state: number, extra_info: string) => void
  ```

- **参数**

  - **room_id**

    类型: string

    房间 ID。

  - **uid**

    类型: string

    用户 ID。

  - **state**

    类型: number

    流状态码，参看 [ErrorCode](Electron-errorcode#errorcode) 及 [WarningCode](Electron-errorcode#warningcode)。

  - **extra_info**

    类型: string

    附加信息，目前为空。

### onLeaveRoom <span id="rtcroomcallback-onleaveroom"></span> 

离开房间成功回调。

- **类型**

  ```ts
  (stats: RtcRoomStats) => void
  ```

- **注意**

  + 用户调用 [`leaveRoom`](Electron-api#leaveroom) 方法后，SDK 会停止所有的发布订阅流，并在释放所有通话相关的音视频资源后，通过此回调通知用户离开房间成功。
  + 用户调用 [`leaveRoom`](Electron-api#leaveroom) 方法离开房间后，如果立即调用 [destroy](Electron-api#destroy) 方法销毁 RTC 引擎，则将无法收到此回调事件。
  + 离开房间后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用音视频设备导致初始化失败。

- **参数**

  - **stats**

    类型: [RtcRoomStats](Electron-keytype#rtcroomstats)

    本次通话的统计数据。

### onUserJoined <span id="rtcroomcallback-onuserjoined"></span> 

可见用户加入房间，或房内不可见用户切换为可见的回调。
1.远端可见用户调用 `setUserVisibility` 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。
2.远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。
3.房间内不可见远端用户调用 `setUserVisibility` 方法切换至可见时，房间内其他用户将收到该事件。
4.新进房用户也会收到进房前已在房内的可见角色用户的进房回调通知。

- **类型**

  ```ts
  (user_info: UserInfo, elapsed: number) => void
  ```

- **参数**

  - **user_info**

    类型: [UserInfo](Electron-keytype#userinfo)

    用户信息。

  - **elapsed**

    类型: number

    可见角色用户调用 [joinRoom](Electron-api#joinroom) 加入房间到房间内其他用户收到该事件经历的时间，单位为 ms。

### onUserLeave <span id="rtcroomcallback-onuserleave"></span> 

远端用户离开房间，或切至不可见时，本地用户会收到此事件

- **类型**

  ```ts
  (uid: string, reason: UserOfflineReasonType) => void
  ```

- **参数**

  - **uid**

    类型: string

    离开房间，或切至不可见的的远端用户 ID。

  - **reason**

    类型: [UserOfflineReasonType](Electron-keytype#userofflinereasontype)

    用户离开房间的原因

### onTokenWillExpire <span id="rtcroomcallback-ontokenwillexpire"></span> 

当 SDK 检测到 Token 的进房权限将在 30 秒内过期时，触发该回调。

- **类型**

  ```ts
  () => void
  ```

- **注意**

  调用 [updateToken](Electron-api#updatetoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。

### onAVSyncStateChange <span id="rtcroomcallback-onavsyncstatechange"></span> 

发布端调用 `setMultiDeviceAVSync` 后音视频同步状态发生改变时，会收到此回调。

- **类型**

  ```ts
  (state: AVSyncState) => void
  ```

- **参数**

  - **state**

    类型: [AVSyncState](Electron-keytype#avsyncstate)

    音视频同步状态

### onRoomStats <span id="rtcroomcallback-onroomstats"></span> 

房间通话统计信息回调。
用户进房开始通话后，每 2s 收到一次本回调。

- **类型**

  ```ts
  (stats: RtcRoomStats) => void
  ```

- **参数**

  - **stats**

    类型: [RtcRoomStats](Electron-keytype#rtcroomstats)

    房间内的汇总统计数据。

### onLocalStreamStats <span id="rtcroomcallback-onlocalstreamstats"></span> 

反映通话中本地设备发送音/视频流的统计信息以及网络状况的回调。
本地用户发布音视频流成功后，每隔 2s 收到此回调。

- **类型**

  ```ts
  (stats: LocalStreamStats) => void
  ```

- **参数**

  - **stats**

    类型: [LocalStreamStats](Electron-keytype#localstreamstats)

    音视频流以及网络状况统计信息。

### onRemoteStreamStats <span id="rtcroomcallback-onremotestreamstats"></span> 

反映通话中本地设备接收订阅的远端音/视频流的统计信息以及网络状况的回调。每隔 2s 收到此回调。

- **类型**

  ```ts
  (stats: RemoteStreamStats) => void
  ```

- **参数**

  - **stats**

    类型: [RemoteStreamStats](Electron-keytype#remotestreamstats)

    音视频流以及网络状况统计信息。

### onUserPublishStream <span id="rtcroomcallback-onuserpublishstream"></span> 

房间内新增远端麦克风采集的音频流的回调。

- **类型**

  ```ts
  (uid: string, type: MediaStreamType) => void
  ```

- **注意**

  当房间内的远端用户调用 [publishStream](Electron-api#publishstream) 成功发布由麦克风采集的音频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeStream](Electron-api#subscribestream) 订阅此流。

- **参数**

  - **uid**

    类型: string

    远端流发布用户的用户 ID。

  - **type**

    类型: [MediaStreamType](Electron-keytype#mediastreamtype)

    远端媒体流的类型。

### onUserUnpublishStream <span id="rtcroomcallback-onuserunpublishstream"></span> 

房间内远端麦克风采集的音频流移除的回调。

- **类型**

  ```ts
  (uid: string, type: MediaStreamType, reason: StreamRemoveReason) => void
  ```

- **注意**

  收到该回调通知后，你可以自行选择是否调用 [unsubscribeStream](Electron-api#unsubscribestream) 取消订阅此流。

- **参数**

  - **uid**

    类型: string

    移除的远端流发布用户的用户 ID。

  - **type**

    类型: [MediaStreamType](Electron-keytype#mediastreamtype)

    远端媒体流的类型。

  - **reason**

    类型: [StreamRemoveReason](Electron-keytype#streamremovereason)

    远端流移除的原因

### onUserPublishScreen <span id="rtcroomcallback-onuserpublishscreen"></span> 

房间内新增远端屏幕共享音视频流的回调。

- **类型**

  ```ts
  (uid: string, type: MediaStreamType) => void
  ```

- **注意**

  当房间内的远端用户调用 [publishScreen](Electron-api#publishscreen) 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeScreen](Electron-api#subscribescreen) 订阅此流。

- **参数**

  - **uid**

    类型: string

    远端流发布用户的用户 ID。

  - **type**

    类型: [MediaStreamType](Electron-keytype#mediastreamtype)

    远端媒体流的类型

### onUserUnpublishScreen <span id="rtcroomcallback-onuserunpublishscreen"></span> 

房间内远端屏幕共享音视频流移除的回调。

- **类型**

  ```ts
  (uid: string, type: MediaStreamType, reason: StreamRemoveReason) => void
  ```

- **注意**

  收到该回调通知后，你可以自行选择是否调用 [unsubscribeScreen](Electron-api#unsubscribescreen) 取消订阅此流。

- **参数**

  - **uid**

    类型: string

    移除的远端流发布用户的用户 ID。

  - **type**

    类型: [MediaStreamType](Electron-keytype#mediastreamtype)

    移除的远端流类型

  - **reason**

    类型: [StreamRemoveReason](Electron-keytype#streamremovereason)

    远端流移除的原因

### onStreamSubscribed <span id="rtcroomcallback-onstreamsubscribed"></span> 

关于订阅媒体流状态改变的回调

- **类型**

  ```ts
  (state_code: SubscribeState, user_id: string, info: SubscribeConfig) => void
  ```

- **注意**

  本地用户收到该回调的时机包括：
  + 调用 [subscribeStream](Electron-api#subscribestream) 或 [unsubscribeStream](Electron-api#unsubscribestream) 订阅/取消订阅指定远端摄像头音视频流后；
  + 调用 [subscribeScreen](Electron-api#subscribescreen) 或 [unsubscribeScreen](Electron-api#unsubscribescreen) 订阅/取消订阅指定远端屏幕共享流后。

- **参数**

  - **state_code**

    类型: [SubscribeState](Electron-keytype#subscribestate)

    订阅媒体流状态

  - **user_id**

    类型: string

    流发布用户的用户 ID

  - **info**

    类型: [SubscribeConfig](Electron-keytype#subscribeconfig)

    流的属性

### onVideoStreamBanned <span id="rtcroomcallback-onvideostreambanned"></span> 

通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。

- **类型**

  ```ts
  (uid: string, banned: boolean) => void
  ```

- **注意**

  + 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。
  + 若被封禁用户退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。
  + 若被封禁用户断网后重连进房，则依然是封禁状态，且只有本人会再次收到该回调。
  + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。
  + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。

- **参数**

  - **uid**

    类型: string

    被禁用/解禁的视频流用户 ID

  - **banned**

    类型: boolean

    视频流发送状态
+ true: 视频流发送被禁用
+ false: 视频流发送被解禁

### onAudioStreamBanned <span id="rtcroomcallback-onaudiostreambanned"></span> 

通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。

- **类型**

  ```ts
  (uid: string, banned: boolean) => void
  ```

- **注意**

  + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。
  + 若被封禁用户退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。
  + 若被封禁用户断网后重连进房，则依然是封禁状态，且只有本人会再次收到该回调。
  + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。
  + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。

- **参数**

  - **uid**

    类型: string

    被禁用/解禁的音频流用户 ID

  - **banned**

    类型: boolean

    音频流发送状态
+ true: 音频流发送被禁用
+ false: 音频流发送被解禁

### onRoomMessageReceived <span id="rtcroomcallback-onroommessagereceived"></span> 

接收到房间内广播消息的回调。

- **类型**

  ```ts
  (uid: string, message: string) => void
  ```

- **注意**

  房间内其他用户调用 [`sendRoomMessage`](Electron-api#sendroommessage) 发送广播消息时，收到此回调。

- **参数**

  - **uid**

    类型: string

    消息发送者 ID

  - **message**

    类型: string

    收到的消息内容

### onRoomBinaryMessageReceived <span id="rtcroomcallback-onroombinarymessagereceived"></span> 

接收到房间内广播二进制消息的回调。

- **类型**

  ```ts
  (uid: string, message: string) => void
  ```

- **注意**

  房间内其他用户调用 [`sendRoomBinaryMessage`](Electron-api#sendroombinarymessage) 发送广播二进制消息时，收到此回调。

- **参数**

  - **uid**

    类型: string

    消息发送者 ID

  - **message**

    类型: string

    收到的二进制消息内容

### onUserMessageReceived <span id="rtcroomcallback-onusermessagereceived"></span> 

收到来自房间中其他用户通过 `sendUserMessage` 发来的点对点文本消息时，会收到此回调。

- **类型**

  ```ts
  (uid: string, message: string) => void
  ```

- **参数**

  - **uid**

    类型: string

    消息发送者的用户 ID 。

  - **message**

    类型: string

    收到的文本消息内容。

### onUserBinaryMessageReceived <span id="rtcroomcallback-onuserbinarymessagereceived"></span> 

收到来自房间中其他用户通过 `sendUserBinaryMessage` 发来的点对点二进制消息时，会收到此回调。

- **类型**

  ```ts
  (uid: string, message: string) => void
  ```

- **参数**

  - **uid**

    类型: string

    消息发送者的用户 ID 。

  - **message**

    类型: string

    收到的二进制消息内容。

### onUserMessageSendResult <span id="rtcroomcallback-onusermessagesendresult"></span> 

向房间内单个用户发送点对点文本或点对点二进制消息后，消息发送方会收到该消息发送结果回调。

- **类型**

  ```ts
  (msgid: number, error: number) => void
  ```

- **注意**

  调用 [sendUserMessage](Electron-api#sendusermessage) 或 [sendUserBinaryMessage](Electron-api#senduserbinarymessage) 接口，才能收到此回调。

- **参数**

  - **msgid**

    类型: number

    本条消息的 ID。

  - **error**

    类型: number

    文本或二进制消息发送结果
+ `200`: 消息发送成功
+ `100`: 失败，发送方未加入房间
+ `102`: 失败，没有可用的数据传输通道连接
+ `103`: 失败，消息超过最大长度，当前为 64 KB
+ `1000`: 失败，未知错误

### onRoomMessageSendResult <span id="rtcroomcallback-onroommessagesendresult"></span> 

调用 `sendRoomMessage` 或 `sendRoomBinaryMessage` 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。

- **类型**

  ```ts
  (msgid: number, error: number) => void
  ```

- **参数**

  - **msgid**

    类型: number

    本条消息的 ID。

  - **error**

    类型: number

    消息发送结果
+ `200`: 消息发送成功
+ `100`: 失败，发送方未加入房间
+ `102`: 失败，没有可用的数据传输通道连接
+ `103`: 失败，消息超过最大长度，当前为 64 KB
+ `1000`: 失败，未知错误

### onForwardStreamStateChanged <span id="rtcroomcallback-onforwardstreamstatechanged"></span> 

跨房间媒体流转发状态和错误回调

- **类型**

  ```ts
  (infos: ForwardStreamStateInfo[], info_count: number) => void
  ```

- **参数**

  - **infos**

    类型: [ForwardStreamStateInfo](Electron-keytype#forwardstreamstateinfo)[]

    跨房间媒体流转发目标房间信息数组

  - **info_count**

    类型: number

    数量

### onForwardStreamEvent <span id="rtcroomcallback-onforwardstreamevent"></span> 

跨房间媒体流转发事件回调

- **类型**

  ```ts
  (infos: ForwardStreamEventInfo[], info_count: number) => void
  ```

- **参数**

  - **infos**

    类型: [ForwardStreamEventInfo](Electron-keytype#forwardstreameventinfo)[]

    跨房间媒体流转发目标房间事件数组

  - **info_count**

    类型: number

    数量

### onNetworkQuality <span id="rtcroomcallback-onnetworkquality"></span> 

加入房间后， 以 2 秒 1 次的频率，报告用户的网络质量信息

- **类型**

  ```ts
  (localQuality: NetworkQualityStats, remoteQualities: NetworkQualityStats[]) => void
  ```

- **注意**

  更多通话中的监测接口，详见[通话中质量监测](106866)

- **参数**

  - **localQuality**

    类型: [NetworkQualityStats](Electron-keytype#networkqualitystats)

    本地网络质量。

  - **remoteQualities**

    类型: [NetworkQualityStats](Electron-keytype#networkqualitystats)[]

    已订阅用户的网络质量。

### onPublishPrivilegeTokenWillExpire <span id="rtcroomcallback-onpublishprivilegetokenwillexpire"></span> 

Token 发布权限过期前 30 秒将触发该回调。

- **类型**

  ```ts
  () => void
  ```

- **注意**

  收到该回调后，你需调用 [updateToken](Electron-api#updatetoken) 更新 Token 发布权限。若收到该回调后未及时更新 Token，Token 发布权限过期后：
  + 此时尝试发布流会收到 [onStreamStateChanged](#onstreamstatechanged) 回调，提示错误码为 `-1002` 没有发布权限；
  + 已在发布中的流会停止发布，发布端会收到 [onStreamStateChanged](#onstreamstatechanged) 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 [onUserUnPublishStream](#onuserunpublishstream) 回调，提示原因为 `6` 发流端发布权限过期。

### onSubscribePrivilegeTokenWillExpire <span id="rtcroomcallback-onsubscribeprivilegetokenwillexpire"></span> 

Token 订阅权限过期前 30 秒将触发该回调。

- **类型**

  ```ts
  () => void
  ```

- **注意**

  收到该回调后，你需调用 [updateToken](Electron-api#updatetoken) 更新 Token 订阅权限有效期。若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 [onStreamStateChanged](#onstreamstatechanged) 回调，提示错误码为 `-1003` 没有订阅权限。

### onSetRoomExtraInfoResult <span id="rtcroomcallback-onsetroomextrainforesult"></span> 

调用 [setRoomExtraInfo](Electron-api#rtcroom-setroomextrainfo) 设置房间附加信息结果的回调。

- **类型**

  ```ts
  (task_id: number, error_code: SetRoomExtraInfoResult) => void
  ```

- **参数**

  - **task_id**

    类型: number

    调用 setRoomExtraInfo 的任务编号。

  - **error_code**

    类型: [SetRoomExtraInfoResult](Electron-keytype#setroomextrainforesult)

    error_code 设置房间附加信息的结果。

### onRoomExtraInfoUpdate <span id="rtcroomcallback-onroomextrainfoupdate"></span> 

接收同一房间内，其他用户调用 [setRoomExtraInfo](Electron-api#rtcroom-setroomextrainfo) 设置的房间附加信息的回调。

- **类型**

  ```ts
  (key: string, value: string, last_update_user_id: string, last_update_time_ms: number) => void
  ```

- **注意**

  新进房的用户会收到进房前房间内已有的全部附加信息通知。

- **参数**

  - **key**

    类型: string

    房间附加信息的键值

  - **value**

    类型: string

    房间附加信息的内容

  - **last_update_user_id**

    类型: string

    最后更新本条信息的用户 ID。

  - **last_update_time_ms**

    类型: number

    最后更新本条信息的 Unix 时间，单位：毫秒。

### onSubtitleStateChanged <span id="rtcroomcallback-onsubtitlestatechanged"></span> 

字幕状态发生改变回调。
当用户调用 [startSubtitle](Electron-api#startsubtitle) 和 [stopSubtitle](Electron-api#stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。

- **类型**

  ```ts
  (state: SubtitleState, error_code: SubtitleErrorCode, error_message: string) => void
  ```

- **参数**

  - **state**

    类型: [SubtitleState](Electron-keytype#subtitlestate)

    字幕状态。

  - **error_code**

    类型: [SubtitleErrorCode](Electron-errorcode#subtitleerrorcode)

    字幕任务错误码。

  - **error_message**

    类型: string

    与第三方服务有关的错误信息。

### onSubtitleMessageReceived <span id="rtcroomcallback-onsubtitlemessagereceived"></span> 

字幕相关内容回调。
当用户成功调用 [startSubtitle](Electron-api#startsubtitle) 后会收到此回调，通知字幕的相关信息。

- **类型**

  ```ts
  (subtitles: SubtitleMessage[]) => void
  ```

- **参数**

  - **subtitles**

    类型: [SubtitleMessage](Electron-keytype#subtitlemessage)[]

    字幕消息内容。


## RTCAUDIOEFFECTPLAYERCALLBACK <span id="rtcaudioeffectplayercallback"></span>

类型: `interface`

- **API**

| 方法 | 描述 |
| :-- | :-- |
| [onAudioEffectPlayerStateChanged](#rtcaudioeffectplayercallback-onaudioeffectplayerstatechanged) | 播放状态改变时回调。 |

### onAudioEffectPlayerStateChanged <span id="rtcaudioeffectplayercallback-onaudioeffectplayerstatechanged"></span> 

播放状态改变时回调。

- **类型**

  ```ts
  (effect_id: number, state: PlayerState, error: PlayerError) => void
  ```

- **参数**

  - **effect_id**

    类型: number

    veRTCAudioEffectPlayer 的 ID。通过 [getAudioEffectPlayer](Electron-api#rtcvideo-getaudioeffectplayer) 设置。

  - **state**

    类型: [PlayerState](Electron-keytype#playerstate)

    混音状态。

  - **error**

    类型: [PlayerError](Electron-errorcode#playererror)

    错误码。


## RTCMediaPlayerCALLBACK <span id="rtcmediaplayercallback"></span>

类型: `interface`

- **API**

| 方法 | 描述 |
| :-- | :-- |
| [onMediaPlayerStateChanged](#rtcmediaplayercallback-onmediaplayerstatechanged) | 播放状态改变时回调。 |
| [onMediaPlayerPlayingProgress](#rtcmediaplayercallback-onmediaplayerplayingprogress) | 播放进度周期性回调。回调周期通过 [setAudioMixingProgressInterval] 设置。 |

### onMediaPlayerStateChanged <span id="rtcmediaplayercallback-onmediaplayerstatechanged"></span> 

播放状态改变时回调。

- **类型**

  ```ts
  (player_id: number, state: PlayerState, error: PlayerError) => void
  ```

- **参数**

  - **player_id**

    类型: number

    veRTCMediaPlayer 的 ID。通过 [getMediaPlayer](Electron-api#rtcvideo-getmediaplayer) 设置。

  - **state**

    类型: [PlayerState](Electron-keytype#playerstate)

    混音状态。

  - **error**

    类型: [PlayerError](Electron-errorcode#playererror)

    错误码。

### onMediaPlayerPlayingProgress <span id="rtcmediaplayercallback-onmediaplayerplayingprogress"></span> 

播放进度周期性回调。回调周期通过 [setAudioMixingProgressInterval] 设置。

- **类型**

  ```ts
  (player_id: number, progress: string) => void
  ```

- **参数**

  - **player_id**

    类型: number

    veRTCMediaPlayer 的 ID。通过 [getMediaPlayer](Electron-api#rtcvideo-getmediaplayer) 设置。

  - **progress**

    类型: string

    进度。单位 ms。
