## RTCEngine
<span id="irtcengine"></span>

类型: `interface`

- **API**

  | 名称 | 描述 |
  | -- | -- |
  | [joinRoom()](#joinroom) | 加入房间。<br>调用此方法加入房间，同房间内其他用户进行音视频通话。 |
  | [leaveRoom()](#leaveroom) | 离开房间。<br>用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。 |
  | [publishStream()](#publishstream) | 在当前所在房间内发布本地摄像头/麦克风采集的媒体流 |
  | [unpublishStream()](#unpublishstream) | 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中 |
  | [publishScreen()](#publishscreen) | 在当前所在房间内发布本地屏幕共享音视频流 |
  | [unpublishScreen()](#unpublishscreen) | 停止将本地屏幕共享音视频流发布到当前所在房间中 |
  | [subscribeStream()](#subscribestream) | 订阅房间内指定的通过摄像头/麦克风采集的媒体流。<br>该方法对自动订阅和手动订阅模式均适用。 |
  | [unsubscribeStream()](#unsubscribestream) | 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。<br>该方法对自动订阅和手动订阅模式均适用。 |
  | [subscribeScreen()](#subscribescreen) | 订阅房间内指定的远端屏幕共享音视频流。<br>该方法对自动订阅和手动订阅模式均适用。 |
  | [unsubscribeScreen()](#unsubscribescreen) | 取消订阅房间内指定的远端屏幕共享音视频流。<br>该方法对自动订阅和手动订阅模式均适用。 |
  | [updateToken()](#updatetoken) | 更新 Token。<br>用于加入房间的 Token 有一定的有效期。Token 过期前 30 秒将收到 [onTokenWillExpire](Web-event.md#ontokenwillexpire) 回调，需要调用此方法更新房间的 Token 信息。 |
  | [setAudioCaptureDevice()](#setaudiocapturedevice) | 设置内部采集时使用的麦克风。 |
  | [setVideoCaptureDevice()](#setvideocapturedevice) | 设置内部采集时使用的摄像头。 |
  | [startVideoCapture()](#startvideocapture) | 开启内部视频采集。默认为关闭状态。<br>内部视频采集是指：使用 RTC SDK 内置的视频采集机制进行视频采集。<br>发布流后调用该方法，房间中的其他用户会收到 [onUserStartVideoCapture](Web-event.md#onuserstartvideocapture) 的回调。 |
  | [stopVideoCapture()](#stopvideocapture) | 关闭内部视频采集。默认为关闭状态。<br>内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>发布流后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Web-event.md#onuserstopvideocapture) 的回调。 |
  | [startAudioCapture()](#startaudiocapture) | 立即开启内部音频采集。默认为关闭状态。<br>内部采集是指：使用 RTC SDK 内置采集机制进行音频采集。<br>发布流后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Web-event.md#onuserstartaudiocapture) 的回调。 |
  | [stopAudioCapture()](#stopaudiocapture) | 立即关闭内部音频采集。默认为关闭状态。<br>内部采集是指：使用 RTC SDK 内置采集机制进行音频采集。<br>调用该方法，房间内的其他用户会收到 [onUserStopAudioCapture](Web-event.md#onuserstopaudiocapture) 的回调。 |
  | [startScreenCapture()](#startscreencapture) | 使用内部采集模块，采集当前屏幕视频流，用于共享。 |
  | [stopScreenCapture()](#stopscreencapture) | 停止屏幕共享流内部采集。 |
  | [setLocalVideoPlayer()](#setlocalvideoplayer) | 设置本地视频渲染时，使用的视图，并设置渲染模式。<br>调用本方法绑定视图以后，你可以通过 `onPlayerEvent` 来监听播放状态。<br>你可以通过再次调用本方法，并绑定空视图来解除绑定。 |
  | [setRemoteVideoPlayer()](#setremotevideoplayer) | 设置远端视频渲染时使用的视图，并设置渲染模式。<br>建议在收到 [onUserPublishStream](Web-event.md#onuserpublishstream)/[onUserPublishScreen](Web-event.md#onuserpublishscreen) 事件后，调用本方法对远端视频视图进行设置。<br>你可以通过再次调用本方法，并绑定空视图来解除绑定。 |
  | [setLocalVideoMirrorType()](#setlocalvideomirrortype) | 是否开启本地视频流镜像模式。 |
  | [setAudioPlaybackDevice()](#setaudioplaybackdevice) | 设置音频播放设备，例如扬声器或者耳机，默认使用扬声器。 |
  | [play()](#play) | 手动开启音视频流播放 |
  | [pauseAllSubscribedStream()](#pauseallsubscribedstream) | 暂停接收来自远端的媒体流。 |
  | [resumeAllSubscribedStream()](#resumeallsubscribedstream) | 恢复接收来自远端的媒体流 |
  | [sendUserMessage()](#sendusermessage) | 给房间内指定的用户发送点对点文本消息。<br>若消息发送成功，则 userId 所指定的用户会收到 [onUserMessageReceived](Web-event.md#onusermessagereceived) 回调。 |
  | [sendUserBinaryMessage()](#senduserbinarymessage) | 给房间内指定的用户发送点对点二进制消息。<br>若消息发送成功，则 userId 所指定的用户会收到 [onUserBinaryMessageReceived](Web-event.md#onuserbinarymessagereceived) 回调。 |
  | [sendRoomMessage()](#sendroommessage) | 给房间内的所有其他用户群发文本消息。<br>若消息发送成功，同一房间内的其他用户会收到 [onRoomMessageReceived](Web-event.md#onroommessagereceived) 回调。 |
  | [sendRoomBinaryMessage()](#sendroombinarymessage) | 给房间内的所有其他用户群发二进制消息。<br>若消息发送成功，同一房间内的其他用户会收到通过 [onRoomBinaryMessageReceived](Web-event.md#onroombinarymessagereceived) 回调发送的消息 |
  | [sendSEIMessage()](#sendseimessage) | 在视频通信时，通过视频帧发送 SEI 数据。 |
  | [setVideoEncoderConfig()](#setvideoencoderconfig) | 在视频发布端设置发布的视频流参数。 |
  | [setScreenEncoderConfig()](#setscreenencoderconfig) | 设置共享屏幕的视频编码参数，同时对视频采集生效。<br>若设置的参数浏览器不支持，RTC SDK 按照浏览器支持的参数范围进行采集和编码，并通过回调 [onLocalVideoSizeChanged](Web-event.md#onlocalvideosizechanged) 通知采集的实际参数。 |
  | [setRemoteVideoConfig()](#setremotevideoconfig) | 设置期望订阅的远端视频流的参数。 |
  | [enableSimulcastMode()](#enablesimulcastmode) | 在视频发布端设置摄像头视频流的大小流模式 |
  | [enableAudioPropertiesReport()](#enableaudiopropertiesreport) | 启用音频信息提示。 |
  | [startLiveTranscoding()](#startlivetranscoding) | 开启转推直播，并设置合流的视频视图布局和音频属性。 |
  | [updateLiveTranscoding()](#updatelivetranscoding) | 更新转推直播参数。<br>使用 [startLiveTranscoding](Web-api.md#startlivetranscoding) 启用转推直播功能后，使用此方法更新功能配置参数。 |
  | [stopLiveTranscoding()](#stoplivetranscoding) | 停止转推直播。<br>关于启动转推直播，参看 [startLiveTranscoding](Web-api.md#startlivetranscoding)。 |
  | [setBusinessId()](#setbusinessid) | 设置业务标识参数<br>可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。 |
  | [setUserVisibility()](#setuservisibility) | 设置用户可见性。未调用该接口前，本地用户默认对他人可见。 |
  | [setExternalVideoTrack()](#setexternalvideotrack) | 使用用户自定义的 videoTrack。<br>调用本方法前必须先调用 [setVideoSourceType](Web-api.md#setvideosourcetype) 设置为自定义视频采集。 |
  | [setExternalAudioTrack()](#setexternalaudiotrack) | 使用用户自定义的 audioTrack。<br>调用本方法前必须先调用 [setAudioSourceType](Web-api.md#setaudiosourcetype) 设置为自定义音频采集。 |
  | [setVideoSourceType()](#setvideosourcetype) | 设置向 SDK 输入的视频源<br>默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。<br>该方法进房前后均可调用。<br>当你已调用 [startVideoCapture](Web-api.md#startvideocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。<br>当你调用此方法开启自定义采集，再调用此方法切换至内部采集时，必须再调用 [startVideoCapture](Web-api.md#startvideocapture) 手动开启内部采集。 |
  | [setAudioSourceType()](#setaudiosourcetype) | 设置向 SDK 输入的音频源<br>默认使用内部采集。内部采集指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br>该方法进房前后均可调用。<br>当你已调用 [startAudioCapture](Web-api.md#startaudiocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。<br>当你调用此方法开启自定义采集，再调用此方法切换至内部采集时，必须再调用 [startAudioCapture](Web-api.md#startaudiocapture) 手动开启内部采集。 |
  | [getAudioMixingManager()](#getaudiomixingmanager) | 混音管理接口创建 |
  | [setAudioCaptureConfig()](#setaudiocaptureconfig) | 设置 RTC SDK 内部采集时的音频采集参数。默认参数由浏览器决定。 |
  | [login()](#login) | 登录即时消息服务器<br>调用此方法登录后，可以向同 `appID` 下其他已登陆用户发送文本或二进制消息。 |
  | [logout()](#logout) | 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。 |
  | [updateLoginToken()](#updatelogintoken) | 更新用户用于登录的 Token。Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。 |
  | [getPeerOnlineStatus()](#getpeeronlinestatus) | 查询对端用户或本端用户的登录状态。在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。 |
  | [sendUserMessageOutsideRoom()](#sendusermessageoutsideroom) | 给房间外指定的用户发送文本消息（P2P） |
  | [sendUserBinaryMessageOutsideRoom()](#senduserbinarymessageoutsideroom) | 给房间外指定的用户发送二进制消息（P2P） |
  | [setServerParams()](#setserverparams) | 设置业务服务器参数。调用 [sendServerMessage](Web-api.md#sendservermessage) 或 [sendServerBinaryMessage](Web-api.md#sendserverbinarymessage) 发送消息给业务服务器之前，必须需要设置有效签名和业务服务器地址。 |
  | [sendServerMessage()](#sendservermessage) | 客户端给业务服务器发送文本消息（P2Server） |
  | [sendServerBinaryMessage()](#sendserverbinarymessage) | 客户端给业务服务器发送二进制消息（P2Server） |
  | [startCloudProxy()](#startcloudproxy) | 开启云代理 |
  | [stopCloudProxy()](#stopcloudproxy) | 关闭云代理 |
  | [startPushPublicStream()](#startpushpublicstream) | 发布一路公共流。 |
  | [updatePublicStreamParam()](#updatepublicstreamparam) | 更新公共流参数。<br>调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布一路公共流。 |
  | [stopPushPublicStream()](#stoppushpublicstream) | 停止发布公共流。<br>调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布一路公共流。 |
  | [startPlayPublicStream()](#startplaypublicstream) | 订阅指定公共流。<br>无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。 |
  | [stopPlayPublicStream()](#stopplaypublicstream) | 取消订阅指定公共流。<br>关于订阅公共流，查看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。 |
  | [setPublicStreamVideoPlayer()](#setpublicstreamvideoplayer) | 为指定公共流设置使用的视图和渲染模式。 |
  | [setDummyCaptureImagePath()](#setdummycaptureimagepath) | 停止内部摄像头采集时，使用静态图片填充本地推送的视频流。 |
  | [defaultTranscoding()](#defaulttranscoding) | 获取合流转推默认参数。 |
  | [setSubscribeFallbackOption()](#setsubscribefallbackoption) | 设置订阅的音视频流的回退选项。<br>回退指：设置网络不佳时允许订阅流进行降级或只订阅音频流，以保证通话流畅。 |
  | [setRemoteUserPriority()](#setremoteuserpriority) | 设置用户优先级。<br>该方法与 [setSubscribeFallbackOption](Web-api.md#setsubscribefallbackoption) 搭配使用。<br>开启回退后，会优先保证收到的高优先级用户的流的质量。 |
  | [startAudioPlaybackDeviceTest()](#startaudioplaybackdevicetest) | 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 [onAudioPlaybackDeviceTestVolume](Web-event.md#onaudioplaybackdevicetestvolume) 回调播放时的音量信息。 |
  | [stopAudioPlaybackDeviceTest()](#stopaudioplaybackdevicetest) | 停止音频播放设备测试。 |
  | [startAudioDeviceRecordTest()](#startaudiodevicerecordtest) | 开始音频采集设备和音频播放设备测试。<br>建议提前调用 [enableAudioPropertiesReport](Web-api#enableaudiopropertiesreport) 注册音量提示回调，测试开始后，音频设备开始采集本地声音，可以通过 [onLocalAudioPropertiesReport](Web-event.md#onlocalaudiopropertiesreport) 获取采集音量。 |
  | [stopAudioDeviceRecordAndPlayTest()](#stopaudiodevicerecordandplaytest) | 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>调用 [startAudioDeviceRecordTest](Web-api.md#startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。 |
  | [stopAudioDevicePlayTest()](#stopaudiodeviceplaytest) | 停止由调用 [startAudioDeviceRecordTest](Web-api.md#startaudiodevicerecordtest) 开始的音频播放设备测试。<br>在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。 |
  | [setAudioProfile()](#setaudioprofile) | 设置音质档位 |
  | [getLocalStreamTrack()](#getlocalstreamtrack) | 获取本地用户的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
  | [getRemoteStreamTrack()](#getremotestreamtrack) | 获取已订阅的远端用户的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
  | [getPublicStreamTrack()](#getpublicstreamtrack) | 获取已订阅的公共流的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。 |
  | [takeLocalSnapshot()](#takelocalsnapshot) | 截取本地视频画面 |
  | [takeRemoteSnapshot()](#takeremotesnapshot) | 截取远端视频画面 |
  | [registerExtension()](#registerextension) | 注册插件。 |
  | [startSubtitle()](#startsubtitle) | 开启字幕。<br>调用该方法后，你可以根据需要选择识别和翻译两种模式。开启识别模式，会将识别后的用户语音转化成文字；开启翻译模式，会在语音识别后进行翻译。语音识别或翻译的结果会通过 [onSubtitleMessageReceived](Web-event.md#onsubtitlemessagereceived) 事件回调给你。<br>调用该方法后，你会收到 [onSubtitleStateChanged](Web-event.md#onsubtitlestatechanged) 回调，通知字幕是否开启。 |
  | [stopSubtitle()](#stopsubtitle) | 关闭字幕。<br>调用该方法后，你会收到 [onSubtitleStateChanged](Web-event.md#onsubtitlestatechanged) 回调，通知字幕是否关闭。 |
  | [setRemoteStreamRenderSync()](#setremotestreamrendersync) | 设置远端音视频流是否同步渲染。<br>你可以通过关闭音视频同步，达到超低端到端延时的效果。 |


### joinRoom()

加入房间。
调用此方法加入房间，同房间内其他用户进行音视频通话。

- **类型**

  ```ts
  (token: string | null, roomId: string, userInfo: UserInfo, roomConfig?: RoomConfig | undefined) => Promise<void>
  ```

- **注意**

  + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则先进房的用户将自动退房并收到 `DUPLICATE_LOGIN` 错误。
  + 本地用户调用 [setUserVisibility](#setuservisibility) 将自身设为可见后加入房间，远端用户会收到 [onUserJoined](Web-event.md#onuserjoined) 回调通知。
  + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 [onConnectionStateChanged](Web-event.md#onConnectionStateChanged) 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，如果加入房间的为可见用户，远端用户会收到 [onUserJoined](Web-event.md#onuserjoined)  回调通知。

- **参数**

  - **token**

    类型: <code>string | null</code>

    动态密钥，用于对进房用户进行鉴权验证。
进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。
使用不同 AppID 的 App 是不能互通的。
请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。

  - **roomId**

    类型: <code>string</code>

    加入的房间 ID。
房间 ID 为长度在 128 字节以内的非空字符串，支持以下字符集范围:
1. 26 个大写字母 A ~ Z 。
2. 26 个小写字母 a ~ z 。
3. 10 个数字 0 ~ 9 。
4. 下划线 "_"，at 符 "@"，减号 "-"。

  - **userInfo**

    类型: <code>[UserInfo](Web-keytype.md#userinfo)</code>

    用户信息。

  - **roomConfig**

    类型: <code>[RoomConfig](Web-keytype.md#roomconfig) | undefined</code>

    房间参数配置，设置房间模式以及是否自动发布或订阅流。

- **返回值**

  类型: <code>Promise<void\></code>

### leaveRoom()

离开房间。
用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。

- **类型**

  ```ts
  (waitAck?: boolean | undefined) => Promise<void>
  ```

- **注意**

  + 可见的用户离开房间后，房间内其他用户会收到 [onUserLeave](Web-event.md#onuserleave) 回调通知。
  + 调用 [joinRoom](#joinroom) 方法加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。重复调用此方法没有负面影响。

- **参数**

  - **waitAck**

    类型: <code>boolean | undefined</code>

- **返回值**

  类型: <code>Promise<void\></code>

### publishStream()

在当前所在房间内发布本地摄像头/麦克风采集的媒体流

- **类型**

  ```ts
  (mediaType: MediaType) => Promise<void>
  ```

- **注意**

  + 调用 [setUserVisibility](#setuservisibility) 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。
  + 如果你需要发布屏幕共享流，调用 [publishScreen](#publishscreen)。
  + 调用此方法后，房间中的所有远端用户会收到 [onUserPublishStream](Web-event.md#onuserpublishstream) 回调通知。
  + 调用 [unpublishStream](#unpublishstream) 取消发布。

- **参数**

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，用于指定发布音频/视频。

- **返回值**

  类型: <code>Promise<void\></code>

### unpublishStream()

停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中

- **类型**

  ```ts
  (mediaType: MediaType) => Promise<void>
  ```

- **注意**

  + 调用 [publishStream](#publishstream) 手动发布摄像头/麦克风采集的音视频流后，你需调用此接口停止发布。
  + 调用此方法停止发布音视频流后，房间中的其他用户将会收到 [onUserUnpublishStream](Web-event.md#onuserunpublishstream) 回调通知。

- **参数**

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，用于指定停止发布音频/视频。

- **返回值**

  类型: <code>Promise<void\></code>

### publishScreen()

在当前所在房间内发布本地屏幕共享音视频流

- **类型**

  ```ts
  (mediaType: MediaType) => Promise<void>
  ```

- **注意**

  + 调用 [setUserVisibility](#setuservisibility) 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。
  + 调用该方法后，房间中的所有远端用户会收到 [onUserPublishScreen](Web-event.md#onuserpublishscreen) 回调。
  + 调用 [unpublishScreen](#unpublishscreen) 取消发布。

- **参数**

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，用于指定发布屏幕音频/视频。

- **返回值**

  类型: <code>Promise<void\></code>

### unpublishScreen()

停止将本地屏幕共享音视频流发布到当前所在房间中

- **类型**

  ```ts
  (mediaType: MediaType) => Promise<void>
  ```

- **注意**

  + 调用 [publishScreen](#publishscreen) 发布屏幕流后，你需调用此接口停止发布。
  + 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 [onUserUnpublishScreen](Web-event.md#onuserunpublishscreen) 回调。

- **参数**

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，用于指定停止发布屏幕音频/视频

- **返回值**

  类型: <code>Promise<void\></code>

### subscribeStream()

订阅房间内指定的通过摄像头/麦克风采集的媒体流。
该方法对自动订阅和手动订阅模式均适用。

- **类型**

  ```ts
  (userId: string, mediaType: MediaType) => Promise<void>
  ```

- **注意**

  你必须先通过 [onUserPublishStream](Web-event.md#onuserpublishstream) 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。

- **参数**

  - **userId**

    类型: <code>string</code>

    指定订阅的远端发布音视频流的用户 ID。

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，用于指定订阅音频/视频。

- **返回值**

  类型: <code>Promise<void\></code>

### unsubscribeStream()

取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。
该方法对自动订阅和手动订阅模式均适用。

- **类型**

  ```ts
  (userId: string, mediaType: MediaType) => Promise<void>
  ```

- **参数**

  - **userId**

    类型: <code>string</code>

    指定取消订阅的远端发布音视频流的用户 ID。

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，用于指定取消订阅音频/视频。

- **返回值**

  类型: <code>Promise<void\></code>

### subscribeScreen()

订阅房间内指定的远端屏幕共享音视频流。
该方法对自动订阅和手动订阅模式均适用。

- **类型**

  ```ts
  (userId: string, mediaType: MediaType) => Promise<void>
  ```

- **注意**

  你必须先通过 [onUserPublishScreen](Web-event.md#onuserpublishscreen) 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。

- **参数**

  - **userId**

    类型: <code>string</code>

    指定订阅的远端发布屏幕流的用户 ID。

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，用于指定订阅音频/视频。

- **返回值**

  类型: <code>Promise<void\></code>

### unsubscribeScreen()

取消订阅房间内指定的远端屏幕共享音视频流。
该方法对自动订阅和手动订阅模式均适用。

- **类型**

  ```ts
  (userId: string, mediaType: MediaType) => Promise<void>
  ```

- **参数**

  - **uid**

    类型: <code>string</code>

    指定取消订阅的远端发布屏幕流的用户 ID。

  - **type**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，用于指定取消订阅音频/视频。

- **返回值**

  类型: <code>Promise<void\></code>

### updateToken()

更新 Token。
用于加入房间的 Token 有一定的有效期。Token 过期前 30 秒将收到 [onTokenWillExpire](Web-event.md#ontokenwillexpire) 回调，需要调用此方法更新房间的 Token 信息。

- **类型**

  ```ts
  (token: string) => void
  ```

- **注意**

  + 调用 [joinRoom](#joinroom) 方法加入房间或断网重连进入房间时，如果 Token 过期，将导致加入房间失败，回调错误码为 `INVALID_TOKEN`。此时需要重新获取 Token，并调用此方法更新 Token。
  + 如果因 Token 过期导致加入房间失败，则调用此方法更新 Token 后，SDK 会自动重新加入房间，不需要再次调用 [joinRoom](#joinroom) 方法。
  + Token 过期后，用户将被移出房间无法继续进行音视频通话。

- **参数**

  - **token**

    类型: <code>string</code>

    获取的新的有效 Token。

### setAudioCaptureDevice()

设置内部采集时使用的麦克风。

- **类型**

  ```ts
  (deviceId: string) => Promise<void>
  ```

- **注意**

  如果设置时正在使用麦克风进行音频采集，切换操作当即生效；如果设置时未开启采集，则会在开启内部采集时打开设置的麦克风。

- **参数**

  - **deviceId**

    类型: <code>string</code>

    设备 ID，可以通过调用 [enumerateAudioCaptureDevices](#enumerateaudiocapturedevices) 获取设备列表。

- **返回值**

  类型: <code>Promise<void\></code>

### setVideoCaptureDevice()

设置内部采集时使用的摄像头。

- **类型**

  ```ts
  (deviceId: string) => Promise<void>
  ```

- **注意**

  + 如果设置时正在使用摄像头进行视频采集，切换操作当即生效；如果设置时未开启采集，则会在开启采集时打开设置的摄像头。
  + 在移动端场景下，可以通过设置 deviceId 为 `"user"` 来指定前置摄像头，可以通过设置 deviceId 为 `"environment"` 来指定后置摄像头。
  + 默认摄像头由浏览器指定。

- **参数**

  - **deviceId**

    类型: <code>string</code>

    设备 ID，可以通过调用 [enumerateVideoCaptureDevices](#enumeratevideocapturedevices) 获取设备列表。

- **返回值**

  类型: <code>Promise<void\></code>

### startVideoCapture()

开启内部视频采集。默认为关闭状态。
内部视频采集是指：使用 RTC SDK 内置的视频采集机制进行视频采集。
发布流后调用该方法，房间中的其他用户会收到 [onUserStartVideoCapture](Web-event.md#onuserstartvideocapture) 的回调。

- **类型**

  ```ts
  (deviceId?: string | undefined) => Promise<MediaTrackSettings>
  ```

- **注意**

  + 调用 [stopVideoCapture](#stopvideocapture) 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。
  + 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。
  + 内部视频采集使用的摄像头由 [setVideoCaptureDevice](#setvideocapturedevice) 接口指定。

- **参数**

  - **deviceId**

    类型: <code>string | undefined</code>

    设备 ID，你需在此传入采集视频的设备 ID，以免出现无画面或显示非所需画面等异常。你可以通过调用 [enumerateDevices](#enumeratedevices) 获取设备列表。

- **返回值**

  类型: <code>Promise<MediaTrackSettings\></code>

  实际生效的视频采集参数。参看 [MediaTrackSettings](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints)。请关注其中的 `frameRate`, `height`, `width` 等值。

### stopVideoCapture()

关闭内部视频采集。默认为关闭状态。
内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。
发布流后调用该方法，房间中的其他用户会收到 [onUserStopVideoCapture](Web-event.md#onuserstopvideocapture) 的回调。

- **类型**

  ```ts
  () => Promise<void>
  ```

- **注意**

  + 调用 [startVideoCapture](#startvideocapture) 可以开启内部视频采集。
  + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。

- **返回值**

  类型: <code>Promise<void\></code>

### startAudioCapture()

立即开启内部音频采集。默认为关闭状态。
内部采集是指：使用 RTC SDK 内置采集机制进行音频采集。
发布流后调用该方法，房间中的其他用户会收到 [onUserStartAudioCapture](Web-event.md#onuserstartaudiocapture) 的回调。

- **类型**

  ```ts
  (deviceId?: string | undefined) => Promise<void>
  ```

- **注意**

  + 调用 [stopAudioCapture](#stopaudiocapture) 可以停止内部音频采集。否则，只有当销毁引擎实例时，内部音频采集才会停止。
  + 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，只有当（内部或外部）音频采集开始以后音频流才会发布。

- **参数**

  - **deviceId**

    类型: <code>string | undefined</code>

    设备 ID，你需在此传入采集音频的设备 ID，以免出现无声等异常。你可以通过调用 [enumerateDevices](#enumeratedevices) 获取设备列表。

- **返回值**

  类型: <code>Promise<void\></code>

### stopAudioCapture()

立即关闭内部音频采集。默认为关闭状态。
内部采集是指：使用 RTC SDK 内置采集机制进行音频采集。
调用该方法，房间内的其他用户会收到 [onUserStopAudioCapture](Web-event.md#onuserstopaudiocapture) 的回调。

- **类型**

  ```ts
  () => Promise<void>
  ```

- **注意**

  + 调用 [startAudioCapture](#startaudiocapture) 可以开启内部音频采集。
  + 如果不调用本方法停止内部音频采集，则只有当销毁引擎实例时，内部音频采集才会停止。

- **返回值**

  类型: <code>Promise<void\></code>

### startScreenCapture()

使用内部采集模块，采集当前屏幕视频流，用于共享。

- **类型**

  ```ts
  (screenConfig?: ScreenConfig | undefined) => Promise<void>
  ```

- **注意**

  + 调用此方法仅开启屏幕流视频采集，不会发布采集到的视频。发布屏幕流视频需要调用 [publishScreen](#publishscreen)。
  + 要关闭屏幕视频源采集，调用 [stopScreenCapture](#stopscreencapture)。
  + 调用此接口前，你可以调用 [setVideoEncoderConfig](#setvideoencoderconfig) 设置屏幕视频流的采集帧率和编码分辨率。

- **参数**

  - **screenConfig**

    类型: <code>[ScreenConfig](Web-keytype.md#screenconfig) | undefined</code>

    共享屏幕属性

- **返回值**

  类型: <code>Promise<void\></code>

### stopScreenCapture()

停止屏幕共享流内部采集。

- **类型**

  ```ts
  () => Promise<void>
  ```

- **返回值**

  类型: <code>Promise<void\></code>

### setLocalVideoPlayer()

设置本地视频渲染时，使用的视图，并设置渲染模式。
调用本方法绑定视图以后，你可以通过 `onPlayerEvent` 来监听播放状态。
你可以通过再次调用本方法，并绑定空视图来解除绑定。

- **类型**

  ```ts
  (streamIndex: StreamIndex, videoPlayerOption?: Partial<VideoPlayerOption> | undefined) => HTMLVideoElement | undefined
  ```

- **注意**

  你应在加入房间后，绑定视图。退出房间后，此设置仍然有效。

- **参数**

  - **streamIndex**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    视频流属性

  - **videoPlayerOption**

    类型: <code>Partial<[VideoPlayerOption](Web-keytype.md#videoplayeroption)\> | undefined</code>

    视图信息和渲染模式

- **返回值**

  类型: <code>HTMLVideoElement | undefined</code>

### setRemoteVideoPlayer()

设置远端视频渲染时使用的视图，并设置渲染模式。
建议在收到 [onUserPublishStream](Web-event.md#onuserpublishstream)/[onUserPublishScreen](Web-event.md#onuserpublishscreen) 事件后，调用本方法对远端视频视图进行设置。
你可以通过再次调用本方法，并绑定空视图来解除绑定。

- **类型**

  ```ts
  (streamIndex: StreamIndex, videoPlayerOption: VideoPlayerOption) => HTMLVideoElement | undefined
  ```

- **注意**

  你应在加入房间后，绑定视图。退出房间后，此设置仍然有效。

- **参数**

  - **streamIndex**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    视频流属性

  - **videoPlayer**

    类型: <code>[VideoPlayerOption](Web-keytype.md#videoplayeroption)</code>

    视图信息和渲染模式

- **返回值**

  类型: <code>HTMLVideoElement | undefined</code>

### setLocalVideoMirrorType()

是否开启本地视频流镜像模式。

- **类型**

  ```ts
  (mirrorType: MirrorType) => void
  ```

- **参数**

  - **mirrorType**

    类型: <code>[MirrorType](Web-keytype.md#mirrortype)</code>

    是否开启镜像模式

### setAudioPlaybackDevice()

设置音频播放设备，例如扬声器或者耳机，默认使用扬声器。

- **类型**

  ```ts
  (deviceId: string) => Promise<void>
  ```

- **注意**

  进房前和进房后，均可调用此方法设置音频播放设备。

- **参数**

  - **deviceId**

    类型: <code>string</code>

    音频播放设备（扬声器或者耳机），你可以通过调用 [enumerateDevices](#enumeratedevices)

- **返回值**

  类型: <code>Promise<void\></code>

### play()

手动开启音视频流播放

- **类型**

  ```ts
  (userId?: string | undefined, mediaType?: MediaType | undefined, streamIndex?: StreamIndex | undefined) => Promise<void>
  ```

- **参数**

  - **userId**

    类型: <code>string | undefined</code>

    指定播放的流所属的用户 ID
不传参数代表指定为本地媒体流

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype) | undefined</code>

    媒体流类型，用于指定发布音频/视频。

  - **streamIndex**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex) | undefined</code>

    视频流属性

- **返回值**

  类型: <code>Promise<void\></code>

  当音视频正常播放时调用本接口也将返回 Promise 对象

### pauseAllSubscribedStream()

暂停接收来自远端的媒体流。

- **类型**

  ```ts
  (mediaType: MediaType) => Promise<void>
  ```

- **注意**

  + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送。
  + 该方法不改变用户的订阅状态以及订阅流的属性。
  + 若想恢复接收远端流，需调用 [resumeAllSubscribedStream](#resumeallsubscribedstream)。

- **参数**

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，指定需要暂停接收音频还是视频流

- **返回值**

  类型: <code>Promise<void\></code>

### resumeAllSubscribedStream()

恢复接收来自远端的媒体流

- **类型**

  ```ts
  (mediaType: MediaType) => Promise<void>
  ```

- **注意**

  + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；
  + 该方法不改变用户的订阅状态以及订阅流的属性。

- **参数**

  - **mediaType**

    类型: <code>[MediaType](Web-keytype.md#mediatype)</code>

    媒体流类型，指定需要暂停接收音频还是视频流

- **返回值**

  类型: <code>Promise<void\></code>

### sendUserMessage()

给房间内指定的用户发送点对点文本消息。
若消息发送成功，则 userId 所指定的用户会收到 [onUserMessageReceived](Web-event.md#onusermessagereceived) 回调。

- **类型**

  ```ts
  (userId: string, message: string) => Promise<unknown> | undefined
  ```

- **注意**

  在发送房间内文本消息前，必须先调用 [joinRoom](#joinroom) 加入房间。

- **参数**

  - **userId**

    类型: <code>string</code>

    消息接收用户的 ID

  - **message**

    类型: <code>string</code>

    发送的文本消息内容
消息不超过 64 KB。

- **返回值**

  类型: <code>Promise<unknown\> | undefined</code>

### sendUserBinaryMessage()

给房间内指定的用户发送点对点二进制消息。
若消息发送成功，则 userId 所指定的用户会收到 [onUserBinaryMessageReceived](Web-event.md#onuserbinarymessagereceived) 回调。

- **类型**

  ```ts
  (userId: string, message: ArrayBuffer) => Promise<unknown>
  ```

- **注意**

  在发送房间内二进制消息前，必须先调用 [joinRoom](#joinroom) 加入房间。

- **参数**

  - **userId**

    类型: <code>string</code>

    消息接收用户的 ID

  - **message**

    类型: <code>ArrayBuffer</code>

    发送的二进制消息内容
消息不超过 64 KB。

- **返回值**

  类型: <code>Promise<unknown\></code>

### sendRoomMessage()

给房间内的所有其他用户群发文本消息。
若消息发送成功，同一房间内的其他用户会收到 [onRoomMessageReceived](Web-event.md#onroommessagereceived) 回调。

- **类型**

  ```ts
  (message: string) => Promise<any> | undefined
  ```

- **参数**

  - **message**

    类型: <code>string</code>

    发送的文本消息内容
消息不超过 64 KB。

- **返回值**

  类型: <code>Promise<any\> | undefined</code>

### sendRoomBinaryMessage()

给房间内的所有其他用户群发二进制消息。
若消息发送成功，同一房间内的其他用户会收到通过 [onRoomBinaryMessageReceived](Web-event.md#onroombinarymessagereceived) 回调发送的消息

- **类型**

  ```ts
  (message: ArrayBuffer) => Promise<any> | undefined
  ```

- **参数**

  - **message**

    类型: <code>ArrayBuffer</code>

    发送的文本消息，不超过 64 KB。

- **返回值**

  类型: <code>Promise<any\> | undefined</code>

### sendSEIMessage()

在视频通信时，通过视频帧发送 SEI 数据。

- **类型**

  ```ts
  (streamIndex: StreamIndex, message: Uint8Array | string, repeatCount: number) => void
  ```

- **注意**

  + 你可以通过此接口对 RTC SDK 内部采集的视频帧添加 SEI。
  + 如果调用此接口之后的 2s 内，没有可带 SEI 的视频帧（比如没有开启视频采集和传输），那么，SEI 数据不会被加进视频帧中。
  + 消息发送成功后，远端会收到 [onSEIMessageReceived](Web-event.md#onseimessagereceived) 事件。

- **参数**

  - **streamIndex**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    指定携带 SEI 信息的媒体流类型

  - **message**

    类型: <code>string | Uint8Array</code>

    SEI 消息，不大于 4 kb。当消息为空或大小超限，终止发送，并收到相应的错误提示。

  - **repeatCount**

    类型: <code>number</code>

    消息发送重复次数。取值范围是 [0, max{29, %{视频帧率}-1}]。推荐范围 [2,4]。调用此接口后，SEI 数据会添加到当前视频帧开始的连续 `repeatCount` 个视频帧中。

### setVideoEncoderConfig()

在视频发布端设置发布的视频流参数。

- **类型**

  ```ts
  (descriptions: VideoEncoderConfig | VideoEncoderConfig[]) => Promise<void>
  ```

- **注意**

  + 默认分辨率 640 × 480 px，帧率 15 FPS，最大编码码率 600 Kbps。
  + 视频流发布前后均可调用本方法。视频流发布后，不支持从单流切换到多路流，不支持修改发布的多路流层数。
  + 当使用移动端在竖持状态下发布视频流时，设置的分辨率宽高与实际发流参数相反。例如，当设置发送分辨率为 640 × 480 px 时，实际发流参数为 480 × 640 px。
  + 发布多路流时，建议取消自动发布，通过调用 [publishStream](#publishstream) 手动发布音视频流，否则多路流不生效。
  + 若设置的参数浏览器不支持，RTC SDK 按照浏览器支持的参数范围进行采集和编码，并通过回调 [onLocalVideoSizeChanged](Web-event.md#onlocalvideosizechanged) 通知采集的实际参数。
  + 是否发布多路流取决于是否同时调用了 [enableSimulcastMode](#enablesimulcastmode) 开启发布多路流。若未开启发布多路流，但调用本方法设置了多个分辨率，SDK 默认发布分辨率最大的一条流，多个分辨率的设置会在开启发布多路流之后生效。若开启了发布多路流，但仅调用本方法设置了一路流的参数，SDK 会自动填充 1～2 组小流参数。
  + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 [setScreenEncoderConfig](#setscreenencoderconfig)。

- **参数**

  - **descriptions**

    类型: <code>[VideoEncoderConfig](Web-keytype.md#videoencoderconfig) | [VideoEncoderConfig](Web-keytype.md#videoencoderconfig)[]</code>

    要推送的多路视频流的参数，所设置的分辨率是各路流的最大分辨率。
最多支持设置 3 路参数，超过 3 路时默认取前 3 路的值。
当设置了多路参数时，分辨率和帧率必须是从大到小排列。
参数最大的一路流的分辨率大于等于 540P 时，支持发布 3 路流；在 270P（含）和 450P（含）之间时，支持发布 2 路流；在 180P 及以下时，开启发布多路流不生效。

- **返回值**

  类型: <code>Promise<void\></code>

### setScreenEncoderConfig()

设置共享屏幕的视频编码参数，同时对视频采集生效。
若设置的参数浏览器不支持，RTC SDK 按照浏览器支持的参数范围进行采集和编码，并通过回调 [onLocalVideoSizeChanged](Web-event.md#onlocalvideosizechanged) 通知采集的实际参数。

- **类型**

  ```ts
  (description: ScreenEncoderConfig) => Promise<void>
  ```

- **注意**

  + 默认分辨率 1920 × 1080 px，帧率 15 FPS，最大编码码率 3000 Kbps。
  + 建议在采集视频前设置编码参数。若采集前未设置编码参数，则使用默认编码参数。

- **参数**

  - **description**

    类型: <code>[ScreenEncoderConfig](Web-keytype.md#screenencoderconfig)</code>

    共享屏幕的视频编码参数。

- **返回值**

  类型: <code>Promise<void\></code>

### setRemoteVideoConfig()

设置期望订阅的远端视频流的参数。

- **类型**

  ```ts
  (userId: string, remoteVideoConfig: RemoteVideoConfig) => Promise<void>
  ```

- **注意**

  + 该方法仅在发布端调用 [enableSimulcastMode](#enablesimulcastmode) 开启了发送多路视频流的情况下生效，此时订阅端将收到与设置的期望参数最相近的一路流。
  + 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。
  + 该方法需在进房后调用，若想进房前设置，你需调用 [joinRoom](#joinroom)，并对 `roomConfig` 中的 `remoteVideoConfig` 进行设置。

- **参数**

  - **userId**

    类型: <code>string</code>

    期望配置订阅参数的远端视频流发布用户的 ID。

  - **remoteVideoConfig**

    类型: <code>[RemoteVideoConfig](Web-keytype.md#remotevideoconfig)</code>

    期望配置的远端视频流参数。

- **返回值**

  类型: <code>Promise<void\></code>

### enableSimulcastMode()

在视频发布端设置摄像头视频流的大小流模式

- **类型**

  ```ts
  (enabled: boolean) => boolean
  ```

- **注意**

  + 仅可以在发布之前进行大小流模式的设置。
  + 开启大小流模式后，SDK 会自动设置各路视频的编码参数。如果你需要手动设置，可以调用 [setVideoEncoderConfig](#setvideoencoderconfig)。

- **参数**

  - **enabled**

    类型: <code>boolean</code>

- **返回值**

  类型: <code>boolean</code>

### enableAudioPropertiesReport()

启用音频信息提示。

- **类型**

  ```ts
  (config?: AudioPropertiesConfig | undefined) => void
  ```

- **注意**

  开启提示后，你可以：

  + 通过 [onLocalAudioPropertiesReport](Web-event.md#onlocalaudiopropertiesreport) 回调获取本地麦克风和屏幕音频流采集的音频信息；
  + 通过 [onRemoteAudioPropertiesReport](Web-event.md#onremoteaudiopropertiesreport) 回调获取订阅的远端用户的音频信息。

- **参数**

  - **config**

    类型: <code>[AudioPropertiesConfig](Web-keytype.md#audiopropertiesconfig) | undefined</code>

    音频信息提示相关设置

### startLiveTranscoding()

开启转推直播，并设置合流的视频视图布局和音频属性。

- **类型**

  ```ts
  (transcode: LiveTranscodeConfig) => Promise<void>
  ```

- **注意**

  + 调用该方法后，关于启动结果和推流过程中的错误，会收到 [onStreamMixingEvent](Web-event.md#onstreammixingevent) 回调。
  + 调用 [stopLiveTranscoding](#stoplivetranscoding) 停止转推直播。

- **参数**

  - **transcode**

    类型: <code>[LiveTranscodeConfig](Web-keytype.md#livetranscodeconfig)</code>

    转推直播配置参数。

- **返回值**

  类型: <code>Promise<void\></code>

### updateLiveTranscoding()

更新转推直播参数。
使用 [startLiveTranscoding](Web-api.md#startlivetranscoding) 启用转推直播功能后，使用此方法更新功能配置参数。

- **类型**

  ```ts
  (transcode: Partial<LiveTranscodeConfig>) => Promise<void>
  ```

- **参数**

  - **transcode**

    类型: <code>Partial<[LiveTranscodeConfig](Web-keytype.md#livetranscodeconfig)\></code>

    转推直播配置参数。除特殊说明外，均支持过程中更新。

- **返回值**

  类型: <code>Promise<void\></code>

### stopLiveTranscoding()

停止转推直播。
关于启动转推直播，参看 [startLiveTranscoding](Web-api.md#startlivetranscoding)。

- **类型**

  ```ts
  () => Promise<void>
  ```

- **返回值**

  类型: <code>Promise<void\></code>

### setBusinessId()

设置业务标识参数
可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。

- **类型**

  ```ts
  (businessId: string) => boolean
  ```

- **注意**

  需要在调用 [joinRoom](#joinroom) 之前调用，[joinRoom](#joinroom) 之后调用该方法无效。

- **参数**

  - **businessId**

    类型: <code>string</code>

    businessId 只是一个标签，颗粒度需要用户自定义。

- **返回值**

  类型: <code>boolean</code>

### setUserVisibility()

设置用户可见性。未调用该接口前，本地用户默认对他人可见。

- **类型**

  ```ts
  (enable: boolean) => Promise<void>
  ```

- **注意**

  + 该方法在加入房间前后均可调用。
  + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：
      - 从 `false` 切换至 `true` 时，房间内其他用户会收到 [onUserJoined](Web-event.md#onuserjoined) 回调通知；
      - 从 `true` 切换至 `false` 时，房间内其他用户会收到 [onUserLeave](Web-event.md#onuserleave) 回调通知。

- **参数**

  - **enable**

    类型: <code>boolean</code>

    用户是否对房间内其他用户可见：

+ `true`: 可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。
+ `false`: 不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。

- **返回值**

  类型: <code>Promise<void\></code>

### setExternalVideoTrack()

使用用户自定义的 videoTrack。
调用本方法前必须先调用 [setVideoSourceType](Web-api.md#setvideosourcetype) 设置为自定义视频采集。

- **类型**

  ```ts
  (index: StreamIndex, track: MediaStreamTrack) => Promise<void>
  ```

- **参数**

  - **index**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    视频指针。

  - **track**

    类型: <code>MediaStreamTrack</code>

    自定义的 videoTrack，参看 [MediaStreamTrack](https://developer.mozilla.org/zh-CN/docs/Web/API/MediaStreamTrack)。

- **返回值**

  类型: <code>Promise<void\></code>

### setExternalAudioTrack()

使用用户自定义的 audioTrack。
调用本方法前必须先调用 [setAudioSourceType](Web-api.md#setaudiosourcetype) 设置为自定义音频采集。

- **类型**

  ```ts
  (index: StreamIndex, track: MediaStreamTrack) => Promise<void>
  ```

- **参数**

  - **index**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    音频流指针

  - **track**

    类型: <code>MediaStreamTrack</code>

    自定义的 audioTrack，参看 [MediaStreamTrack](https://developer.mozilla.org/zh-CN/docs/Web/API/MediaStreamTrack)。

- **返回值**

  类型: <code>Promise<void\></code>

### setVideoSourceType()

设置向 SDK 输入的视频源
默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。
该方法进房前后均可调用。
当你已调用 [startVideoCapture](Web-api.md#startvideocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。
当你调用此方法开启自定义采集，再调用此方法切换至内部采集时，必须再调用 [startVideoCapture](Web-api.md#startvideocapture) 手动开启内部采集。

- **类型**

  ```ts
  (index: StreamIndex, videoSourceType: VideoSourceType) => Promise<void>
  ```

- **参数**

  - **index**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    视频流指针

  - **videoSourceType**

    类型: <code>[VideoSourceType](Web-keytype.md#videosourcetype)</code>

    视频采集模块

- **返回值**

  类型: <code>Promise<void\></code>

### setAudioSourceType()

设置向 SDK 输入的音频源
默认使用内部采集。内部采集指：使用 RTC SDK 内置的音频采集机制进行音频采集。
该方法进房前后均可调用。
当你已调用 [startAudioCapture](Web-api.md#startaudiocapture) 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。
当你调用此方法开启自定义采集，再调用此方法切换至内部采集时，必须再调用 [startAudioCapture](Web-api.md#startaudiocapture) 手动开启内部采集。

- **类型**

  ```ts
  (index: StreamIndex, audioSourceType: AudioSourceType) => Promise<void>
  ```

- **参数**

  - **index**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    音频流指针

  - **audioSourceType**

    类型: <code>[AudioSourceType](Web-keytype.md#audiosourcetype)</code>

    音频采集模块

- **返回值**

  类型: <code>Promise<void\></code>

### getAudioMixingManager()

混音管理接口创建

- **类型**

  ```ts
  () => IAudioMixingManager
  ```

- **返回值**

  类型: <code>IAudioMixingManager</code>

  混音管理对象

### setAudioCaptureConfig()

设置 RTC SDK 内部采集时的音频采集参数。默认参数由浏览器决定。

- **类型**

  ```ts
  (config: TrackCaptureConfig) => Promise<void>
  ```

- **注意**

  你需要在开始音频采集和首次发布之前调用本接口。

- **参数**

  - **config**

    类型: <code>TrackCaptureConfig</code>

    音频采集参数。例如，关闭浏览器音频 3A。支持传入设置的参数见 [MediaTrackConstraints](https://developer.mozilla.org/zh-CN/docs/Web/API/MediaTrackConstraints)

- **返回值**

  类型: <code>Promise<void\></code>

### login()

登录即时消息服务器
调用此方法登录后，可以向同 `appID` 下其他已登陆用户发送文本或二进制消息。

- **类型**

  ```ts
  (token: string | null, userId: string) => Promise<void>
  ```

- **注意**

  + 在调用本接口登录后，如果想要登出，需要调用 [logout](#logout)。
     + 同一个 App ID 的每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则先登录的用户将自动登出，并收到 `RTM_DUPLICATE_LOGIN` 错误。

- **参数**

  - **token**

    类型: <code>string | null</code>

    用户登录必须携带的 Token，用于鉴权验证。<br/>测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成临时 Token，`roomId` 填任意值。<br/>正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token，`roomId` 置空，Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。

  - **userInfo**

    类型: <code>string</code>

    用户信息。

- **返回值**

  类型: <code>Promise<void\></code>

### logout()

调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。

- **类型**

  ```ts
  () => Promise<void>
  ```

- **返回值**

  类型: <code>Promise<void\></code>

### updateLoginToken()

更新用户用于登录的 Token。Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。

- **类型**

  ```ts
  (token: string | null) => Promise<void>
  ```

- **注意**

  + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，你无需再次调用 login 方法。
  + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知。

- **参数**

  - **token**

    类型: <code>string | null</code>

    更新的动态密钥

- **返回值**

  类型: <code>Promise<void\></code>

### getPeerOnlineStatus()

查询对端用户或本端用户的登录状态。在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。

- **类型**

  ```ts
  (userId: string) => Promise<USER_ONLINE_STATUS>
  ```

- **注意**

  必须调用 [login](#login) 登录后，才能调用本接口。

- **参数**

  - **userId**

    类型: <code>string</code>

    需要查询的用户 ID

- **返回值**

  类型: <code>Promise<[USER_ONLINE_STATUS](Web-keytype.md#user_online_status)\></code>

### sendUserMessageOutsideRoom()

给房间外指定的用户发送文本消息（P2P）

- **类型**

  ```ts
  (userId: string, message: string) => Promise<any>
  ```

- **注意**

  + 必须调用 [login](#login) 登录后，才能调用本接口。
  + 若文本消息发送成功，指定的用户会通过 [onUserMessageReceivedOutsideRoom](Web-event.md#onusermessagereceivedoutsideroom) 回调收到该消息。

- **参数**

  - **userId**

    类型: <code>string</code>

    消息接收用户的 ID

  - **message**

    类型: <code>string</code>

    发送的文本消息内容。消息不超过 64 KB。

- **返回值**

  类型: <code>Promise<any\></code>

### sendUserBinaryMessageOutsideRoom()

给房间外指定的用户发送二进制消息（P2P）

- **类型**

  ```ts
  (userId: string, message: ArrayBuffer) => Promise<any>
  ```

- **注意**

  + 必须调用 [login](#login) 登录后，才能调用本接口。
  + 若文本消息发送成功，则 uid 所指定的用户会通过 [EngineEventsTypes.onUserBinaryMessageReceivedOutsideRoom](Web-event.md#onuserbinarymessagereceivedoutsideroom) 回调收到该消息。

- **参数**

  - **userId**

    类型: <code>string</code>

    消息接收用户的 ID

  - **message**

    类型: <code>ArrayBuffer</code>

    发送的二进制消息内容。消息不超过 64 KB。

- **返回值**

  类型: <code>Promise<any\></code>

### setServerParams()

设置业务服务器参数。调用 [sendServerMessage](Web-api.md#sendservermessage) 或 [sendServerBinaryMessage](Web-api.md#sendserverbinarymessage) 发送消息给业务服务器之前，必须需要设置有效签名和业务服务器地址。

- **类型**

  ```ts
  (signature: string, url: string) => Promise<any>
  ```

- **注意**

  + 用户必须调用 [login](#login) 登录后，才能调用本接口。
  + 调用本接口后将触发 [onServerParamsSetResult](Web-event.md#onserverparamssetresult) 回调。

- **参数**

  - **signature**

    类型: <code>string</code>

    动态签名。业务服务器会使用该签名对请求进行鉴权验证。

  - **url**

    类型: <code>string</code>

    业务服务器的地址

- **返回值**

  类型: <code>Promise<any\></code>

### sendServerMessage()

客户端给业务服务器发送文本消息（P2Server）

- **类型**

  ```ts
  (message: string) => Promise<any>
  ```

- **注意**

  在向业务服务器发送文本消息前，必须先调用 [login](#login) 完成登录，随后调用 [setServerParams](#setserverparams) 设置业务服务器。

- **参数**

  - **message**

    类型: <code>string</code>

    发送的文本消息内容。消息不超过 64 KB。

- **返回值**

  类型: <code>Promise<any\></code>

### sendServerBinaryMessage()

客户端给业务服务器发送二进制消息（P2Server）

- **类型**

  ```ts
  (message: ArrayBuffer) => Promise<any>
  ```

- **注意**

  在向业务服务器发送文本消息前，必须先调用 [login](#login) 完成登录，随后调用 [setServerParams](#setserverparams) 设置业务服务器。

- **参数**

  - **message**

    类型: <code>ArrayBuffer</code>

    发送的二进制消息内容。消息不超过 64 KB。

- **返回值**

  类型: <code>Promise<any\></code>

### startCloudProxy()

开启云代理

- **类型**

  ```ts
  (cloudProxyInfo: CloudProxyInfo) => void
  ```

- **注意**

  + 在加入房间前调用此接口
  + 在开启云代理后，进行通话前网络探测
  + 开启云代理后，并成功链接云代理服务器后，会收到 [onCloudProxyConnected](Web-event.md#oncloudproxyconnected)。
  + 要关闭云代理，调用 [stopCloudProxy](#stopcloudproxy)。

- **参数**

  - **cloudProxyInfo**

    类型: <code>[CloudProxyInfo](Web-keytype.md#cloudproxyinfo)</code>

    云代理服务器信息列表。

### stopCloudProxy()

关闭云代理

- **类型**

  ```ts
  () => void
  ```

- **注意**

  要开启云代理，调用 [startCloudProxy](#startcloudproxy)。

### startPushPublicStream()

发布一路公共流。

- **类型**

  ```ts
  (publicStreamId: string, publicStreamParam: PublicStreamConfig) => Promise<void>
  ```

- **注意**

  + 使用同一 `appID` 的用户，无论是否进房，可以调用 [startPlayPublicStream](#startplaypublicstream) 获取和播放指定的公共流。
  + 同一用户使用同一公共流 ID 多次调用本接口无效。调用 [updatePublicStreamParam](#updatepublicstreamparam) 更新公共流参数。
  + 不同用户使用同一公共流 ID 多次调用本接口时，RTC SDK 将使用最后一次调用时传入的参数更新公共流。
  + 使用不同的公共流 ID 多次调用本接口可以发布多路公共流。
  + 调用 [stopPushPublicStream](#stoppushpublicstream) 停止推公共流。

- **参数**

  - **publicStreamId**

    类型: <code>string</code>

    公共流 ID。

  - **publicStreamParam**

    类型: <code>[PublicStreamConfig](Web-keytype.md#publicstreamconfig)</code>

    公共流参数。
一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。
如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。

- **返回值**

  类型: <code>Promise<void\></code>

### updatePublicStreamParam()

更新公共流参数。
调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布一路公共流。

- **类型**

  ```ts
  (publicStreamId: string, publicStreamParam: Partial<PublicStreamConfig>) => Promise<void>
  ```

- **参数**

  - **publicStreamId**

    类型: <code>string</code>

    公共流 ID。
指定的流必须为当前用户所发布。

  - **publicStreamParam**

    类型: <code>Partial<[PublicStreamConfig](Web-keytype.md#publicstreamconfig)\></code>

    公共流参数。

- **返回值**

  类型: <code>Promise<void\></code>

### stopPushPublicStream()

停止发布公共流。
调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布一路公共流。

- **类型**

  ```ts
  (publicStreamId: string) => Promise<void>
  ```

- **参数**

  - **publicStreamId**

    类型: <code>string</code>

    公共流 ID。
指定的流必须为当前用户所发布。

- **返回值**

  类型: <code>Promise<void\></code>

### startPlayPublicStream()

订阅指定公共流。
无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。

- **类型**

  ```ts
  (publicStreamId: string) => Promise<void>
  ```

- **注意**

  + 建议在调用本接口前，先调用 [setPublicStreamVideoPlayer](#setpublicstreamvideoplayer) 设置使用的视图和渲染模式。
  + 调用本接口后，可以通过 [onFirstPublicStreamVideoFrameDecoded](Web-event.md#onfirstpublicstreamvideoframedecoded) 和 [onFirstPublicStreamAudioFrameDecoded](Web-event.md#onfirstpublicstreamaudioframedecoded) 回调公共流的视频和音频首帧解码情况。
  + 调用本接口后，可以通过 [onPublicStreamSEIMessageReceived](Web-event.md#onpublicstreamseimessagereceived) 回调公共流中包含的 SEI 信息。
  + 调用 [stopPlayPublicStream](#stopplaypublicstream) 取消订阅公共流。

- **参数**

  - **publicStreamId**

    类型: <code>string</code>

    公共流 ID。
如果指定流暂未发布，则本地客户端将在其开始发布后接收到流数据。

- **返回值**

  类型: <code>Promise<void\></code>

### stopPlayPublicStream()

取消订阅指定公共流。
关于订阅公共流，查看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。

- **类型**

  ```ts
  (publicStreamId: string) => Promise<void>
  ```

- **参数**

  - **publicStreamId**

    类型: <code>string</code>

    公共流 ID。

- **返回值**

  类型: <code>Promise<void\></code>

### setPublicStreamVideoPlayer()

为指定公共流设置使用的视图和渲染模式。

- **类型**

  ```ts
  (publicStreamId: string, videoPlayerOption: Omit<VideoPlayerOption, 'userId'>) => void
  ```

- **参数**

  - **publicStreamId**

    类型: <code>string</code>

    公共流 ID。

  - **videoPlayerOption**

    类型: <code>Omit<[VideoPlayerOption](Web-keytype.md#videoplayeroption), "userId"\></code>

    视图信息和渲染模式。

### setDummyCaptureImagePath()

停止内部摄像头采集时，使用静态图片填充本地推送的视频流。

- **类型**

  ```ts
  (index: StreamIndex, filePath: string) => Promise<void>
  ```

- **注意**

  + Mac 端的 Chrome 浏览器上支持此功能
  + 建议你在结束采集前，就进行静态图片填充设置，避免视频录制时，出现黑帧。
  + 本地预览时，无法看到此图片。

- **参数**

  - **index**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

  - **filePath**

    类型: <code>string</code>

    以 Http 协议表示的图片地址，或 Blob 对象。
图片类型支持：JPG、PNG、BMP。
图片长宽比和视频编码参数不一致时，图片会被等比缩放，直至其两边长小于等于视频编码参数中的宽高。

- **返回值**

  类型: <code>Promise<void\></code>

### defaultTranscoding()

获取合流转推默认参数。

- **类型**

  ```ts
  () => Required<LiveTranscodeConfig>
  ```

- **返回值**

  类型: <code>Required<[LiveTranscodeConfig](Web-keytype.md#livetranscodeconfig)\></code>

  转推直播默认音视频参数

### setSubscribeFallbackOption()

设置订阅的音视频流的回退选项。
回退指：设置网络不佳时允许订阅流进行降级或只订阅音频流，以保证通话流畅。

- **类型**

  ```ts
  (option: SubscribeFallbackOption) => boolean
  ```

- **注意**

  + 必须在进房前设置，进房后设置或更改设置无效。
  + 设置回退选项后，订阅的音视频流发生回退或从回退中恢复时，会收到 [onRemoteVideoSizeChanged](Web-event.md#onremotevideosizechanged) 回调通知。
  + 可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。

- **参数**

  - **option**

    类型: <code>[SubscribeFallbackOption](Web-keytype.md#subscribefallbackoption)</code>

    订阅的音视频流回退选项

- **返回值**

  类型: <code>boolean</code>

  + `true` 设置成功；
  + `false` 设置失败。

### setRemoteUserPriority()

设置用户优先级。
该方法与 [setSubscribeFallbackOption](Web-api.md#setsubscribefallbackoption) 搭配使用。
开启回退后，会优先保证收到的高优先级用户的流的质量。

- **类型**

  ```ts
  (userId: string, priority: RemoteUserPriority) => boolean
  ```

- **参数**

  - **userId**

    类型: <code>string</code>

    远端用户的 ID

  - **priority**

    类型: <code>[RemoteUserPriority](Web-keytype.md#remoteuserpriority)</code>

    远端用户优先级

- **返回值**

  类型: <code>boolean</code>

  + `true` 设置成功；
  + `false` 设置失败。

### startAudioPlaybackDeviceTest()

启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 [onAudioPlaybackDeviceTestVolume](Web-event.md#onaudioplaybackdevicetestvolume) 回调播放时的音量信息。

- **类型**

  ```ts
  (filePath: string, indicationInterval: number) => Promise<void>
  ```

- **注意**

  + 该方法在用户进房前后均可调用。但不可与其它音频设备测试功能同时应用。
  + 调用 [stopAudioPlaybackDeviceTest](#stopaudioplaybackdevicetest) 可以停止测试。

- **参数**

  - **filePath**

    类型: <code>string</code>

    指定播放设备检测的音频文件网络地址。包括格式 wav 和 mp3。

  - **indicationInterval**

    类型: <code>number</code>

    [onAudioPlaybackDeviceTestVolume](Web-event.md#onaudioplaybackdevicetestvolume) 音量回调的时间间隔，推荐设置为 200 毫秒或以上。单位为毫秒。最小值为 100 毫秒。

- **返回值**

  类型: <code>Promise<void\></code>

  当测试流程结束时 Resolve

### stopAudioPlaybackDeviceTest()

停止音频播放设备测试。

- **类型**

  ```ts
  () => void
  ```

- **注意**

  调用 [startAudioPlaybackDeviceTest](#startaudioplaybackdevicetest) 后，调用本方法停止测试。

### startAudioDeviceRecordTest()

开始音频采集设备和音频播放设备测试。
建议提前调用 [enableAudioPropertiesReport](Web-api#enableaudiopropertiesreport) 注册音量提示回调，测试开始后，音频设备开始采集本地声音，可以通过 [onLocalAudioPropertiesReport](Web-event.md#onlocalaudiopropertiesreport) 获取采集音量。

- **类型**

  ```ts
  (indicationInterval: number, onAutoplayFailed?: ((resume: () => Promise<any>) => any) | undefined) => Promise<void>
  ```

- **注意**

  + 该方法在 joinRoom 前后均可调用。但不可与其它音频设备测试功能同时应用。
  + 调用本接口 30 s 后，采集自动停止，并开始播放采集到的声音。录音播放完毕后，设备测试流程自动结束。你也可以在 30 s 内调用 [stopAudioDeviceRecordAndPlayTest](#stopaudiodevicerecordandplaytest) 来停止采集并开始播放此前采集到的声音。
  + 调用 [stopAudioDevicePlayTest](#stopaudiodeviceplaytest) 可以停止音频设备采集和播放测试。
  + 该方法仅在本地进行音频设备测试，不涉及网络连接。

- **参数**

  - **indicationInterval**

    类型: <code>number</code>

    测试录音播放时触发 [onAudioPlaybackDeviceTestVolume](Web-event.md#onaudioplaybackdevicetestvolume) 播放音量回调，本参数指定了该周期回调的时间间隔。推荐设置为 200 毫秒或以上。单位为毫秒。最小值为 100 毫秒。

  - **onAutoplayFailed**

    类型: <code>((resume: () =\> Promise<any\>) =\> any) | undefined</code>

    由于浏览器自动播放策略影响，导致录制音频播放失败时回调。`resume` 为恢复播放方法，建议在用户点击后同步执行。

- **返回值**

  类型: <code>Promise<void\></code>

  当测试流程结束时 Resolve

### stopAudioDeviceRecordAndPlayTest()

停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。
调用 [startAudioDeviceRecordTest](Web-api.md#startaudiodevicerecordtest) 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。

- **类型**

  ```ts
  () => void
  ```

- **注意**

  调用本接口开始播放录音后，可以在播放过程中调用 [stopAudioDevicePlayTest](#stopaudiodeviceplaytest) 停止播放。

### stopAudioDevicePlayTest()

停止由调用 [startAudioDeviceRecordTest](Web-api.md#startaudiodevicerecordtest) 开始的音频播放设备测试。
在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。

- **类型**

  ```ts
  () => void
  ```

### setAudioProfile()

设置音质档位

- **类型**

  ```ts
  (profile: AudioProfileType) => Promise<void>
  ```

- **注意**

  你需要在开始音频采集和首次发布之前调用本接口。

- **参数**

  - **profile**

    类型: <code>[AudioProfileType](Web-keytype.md#audioprofiletype)</code>

    音质档位。不同的音质档位有着不同的音频参数，带来不同的听觉体验，你应根据业务场景选择适合的音质档位。

- **返回值**

  类型: <code>Promise<void\></code>

### getLocalStreamTrack()

获取本地用户的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。

- **类型**

  ```ts
  (streamIndex: StreamIndex, type: 'video' | 'audio') => MediaStreamTrack | undefined
  ```

- **注意**

  + 调用时机，本地采集开启后或已指定外部 MediaStreamTrack 后。
  + 当调用接口或拔出设备关闭本地采集时，将触发该 MediaStreamTrack 回调的 `ended` 事件，MediaStreamTrack 随即被关闭。
  + 通过 MediaStreamTrack 可以获取实际分辨率、设备 ID 参数、实时音量信息，对轨道进行 muted 和 stop 操作，调整音量等。
  + 我们推荐使用 RTC 提供的对外接口实现以下功能：
  1. 获取本地流分辨率和音量：[onLocalStreamStats](Web-event.md#onlocalstreamstats)
  2. 获取设备 ID： [enumerateDevices](#enumeratedevices)
  3. stop：[stopAudioCapture](#stopaudiocapture)，[stopVideoCapture](#stopvideocapture)

- **参数**

  - **streamIndex**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    流属性，包括主流、屏幕流。

  - **type**

    类型: <code>"video" | "audio"</code>

    媒体流类型，视频或音频。
音频：可分别获取本地麦克风、本地音频外部源、播放本地音频文件、本地屏幕流音频的音轨。
视频：可分别获取本地摄像头、本地视频外部源、本地屏幕视频的视频轨道。

- **返回值**

  类型: <code>MediaStreamTrack | undefined</code>

  当 MediaStreamTrack 不存在时，比如没有开启采集，返回 `undefined`。

### getRemoteStreamTrack()

获取已订阅的远端用户的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。

- **类型**

  ```ts
  (userId: string, streamIndex: StreamIndex, type: 'video' | 'audio') => MediaStreamTrack | undefined
  ```

- **注意**

  + 调用时机，订阅该远端流之后。
  + 本地用户取消订阅该流时，将触发该 MediaStreamTrack 回调的 `ended` 事件， MediaStreamTrack 随即被关闭。
  + 通过 MediaStreamTrack 可以获取实际分辨率、实时音量信息，对轨道进行 muted 和 stop 操作，调整音量等。
  + 我们推荐使用 RTC 提供的对外接口实现以下功能。
  1. 获取远端流分辨率和音量：[onRemoteStreamStats](Android-callback.md#onremotestreamstats)
  2. stop：[unsubscribeStream](#unsubscribestream)，[unsubscribeScreen](#unsubscribescreen)

- **参数**

  - **userId**

    类型: <code>string</code>

    远端用户 ID。

  - **streamIndex**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    流属性，包括主流、屏幕流。

  - **type**

    类型: <code>"video" | "audio"</code>

    媒体流类型，视频或音频。
可分别单独获取远端麦克风、远端屏幕音频的音轨。
可分别获取远端摄像头、远端屏幕视频的视频轨道。

- **返回值**

  类型: <code>MediaStreamTrack | undefined</code>

  当 MediaStreamTrack 不存在时，比如没有订阅该流，返回 `undefined`。

### getPublicStreamTrack()

获取已订阅的公共流的音频或者视频的 [MediaStreamTrack](https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamTrack)。

- **类型**

  ```ts
  (id: string, type: 'video' | 'audio') => MediaStreamTrack | undefined
  ```

- **注意**

  + 调用时机，调用 [`stopPlayPublicStream`](#stopplaypublicstream) 订阅公共流后。
  + 调用 [`stopPlayPublicStream`](#stopplaypublicstream) 停止订阅公共流时，将触发该 MediaStreamTrack 回调的 `ended` 事件， MediaStreamTrack 随即被关闭。

- **参数**

  - **id**

    类型: <code>string</code>

    公共流 ID。

  - **type**

    类型: <code>"video" | "audio"</code>

    媒体流类型，视频或音频。

- **返回值**

  类型: <code>MediaStreamTrack | undefined</code>

  当 MediaStreamTrack 不存在时，比如没有订阅该公共流，返回 `undefined`。

### takeLocalSnapshot()

截取本地视频画面

- **类型**

  ```ts
  (streamIndex: StreamIndex) => Promise<ImageData>
  ```

- **注意**

  + 对截取的画面，包含本地视频处理的全部效果，包含旋转，镜像，美颜等。
  + 不管采用 SDK 内部采集，还是自定义采集，都可以进行截图。

- **参数**

  - **streamIndex**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    截图的视频流。

- **返回值**

  类型: <code>Promise<ImageData\></code>

### takeRemoteSnapshot()

截取远端视频画面

- **类型**

  ```ts
  (id: string, streamIndex: StreamIndex) => Promise<ImageData>
  ```

- **参数**

  - **id**

    类型: <code>string</code>

    用户 ID/公共流 ID

  - **streamIndex**

    类型: <code>[StreamIndex](Web-keytype.md#streamindex)</code>

    截图的视频流。

- **返回值**

  类型: <code>Promise<ImageData\></code>

### registerExtension()

注册插件。

- **类型**

  ```ts
  (extension: RTCExtension) => Promise<void>
  ```

- **注意**

  你可以通过插件实现：
  • [基础美颜功能](https://www.volcengine.com/docs/6348/148646)；
  • [AI 降噪功能](https://www.volcengine.com/docs/6348/148647)。

- **参数**

  - **extension**

    类型: <code>RTCExtension</code>

    插件实例。

- **返回值**

  类型: <code>Promise<void\></code>

### startSubtitle()

开启字幕。
调用该方法后，你可以根据需要选择识别和翻译两种模式。开启识别模式，会将识别后的用户语音转化成文字；开启翻译模式，会在语音识别后进行翻译。语音识别或翻译的结果会通过 [onSubtitleMessageReceived](Web-event.md#onsubtitlemessagereceived) 事件回调给你。
调用该方法后，你会收到 [onSubtitleStateChanged](Web-event.md#onsubtitlestatechanged) 回调，通知字幕是否开启。

- **类型**

  ```ts
  (config: RTCSubtitleConfig) => Promise<void>
  ```

- **注意**

  此方法需要在进房后调用。
          如果想要指定源语言，你需要在进房前调用 `joinRoom` 接口，通过 extraInfo 参数传入 `"source_language": "zh"` JSON 字符串来指定自己的源语言，目前仅支持指定中文、英文和日文。
          如果你未指定源语言，SDK 会将浏览器的语种设定为源语言。

- **参数**

  - **config**

    类型: <code>[RTCSubtitleConfig](Web-keytype.md#rtcsubtitleconfig)</code>

    字幕配置信息。

- **返回值**

  类型: <code>Promise<void\></code>

### stopSubtitle()

关闭字幕。
调用该方法后，你会收到 [onSubtitleStateChanged](Web-event.md#onsubtitlestatechanged) 回调，通知字幕是否关闭。

- **类型**

  ```ts
  () => void
  ```

### setRemoteStreamRenderSync()

设置远端音视频流是否同步渲染。
你可以通过关闭音视频同步，达到超低端到端延时的效果。

- **类型**

  ```ts
  (sync: boolean) => boolean
  ```

- **注意**

  必须在进房前设置，进房后设置或更改设置无效。

- **参数**

  - **sync**

    类型: <code>boolean</code>

    `true`：（默认值）开启同步。
`false`：关闭同步。

- **返回值**

  类型: <code>boolean</code>

  + `true`：设置成功。
  + `false`：设置失败。


## VERTC

类型: `interface`

- **API**

  | 名称 | 描述 |
  | -- | -- |
  | [createEngine()](#createengine) | 创建引擎对象。<br>你必须先使用此方法，以使用 RTC 提供的各种音视频能力。<br>再次调用此方法时，会创建另一个独立的引擎实例。 |
  | [destroyEngine()](#destroyengine) | 手动销毁通过 [createEngine](Web-api.md#createengine) 所创建的引擎对象。 |
  | [getSdkVersion()](#getsdkversion) | 获取 SDK 当前的版本号。 |
  | [enumerateDevices()](#enumeratedevices) | 枚举可用的媒体输入和输出设备，比如麦克风、摄像头、耳机等。<br>可以通过该方法获取设备的 deviceId, 用于在 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice)、[startVideoCapture](Web-api.md#startvideocapture)、[startAudioCapture](Web-api.md#startaudiocapture) 方法中指定采集/播放设备。 |
  | [enableDevices()](#enabledevices) | 向用户获取设备权限 |
  | [enumerateAudioCaptureDevices()](#enumerateaudiocapturedevices) | 该方法枚举可用的麦克风。<br>可以通过该方法获取设备的 `deviceId`, 用于在 [startAudioCapture](Web-api.md#startaudiocapture)、[setAudioCaptureDevice](Web-api.md#setaudiocapturedevice) 方法中指定使用的麦克风设备。 |
  | [enumerateVideoCaptureDevices()](#enumeratevideocapturedevices) | 该方法枚举可用的摄像头等。<br>可以通过该方法获取设备的 deviceId, 用于在 [startVideoCapture](Web-api.md#startvideocapture)、[setVideoCaptureDevice](Web-api.md#setvideocapturedevice) 方法中指定使用的摄像头设备。 |
  | [enumerateAudioPlaybackDevices()](#enumerateaudioplaybackdevices) | 该方法枚举可用的音频播放设备，例如耳机、音箱等。<br>可以通过该方法获取设备的 deviceId, 可用于 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice) 方法中指定音频播放设备。 |
  | [isSupported()](#issupported) | 浏览器是否支持 |
  | [getSupportedCodecs()](#getsupportedcodecs) | 获取当前浏览器支持的编解码类型。<br>若你已开通 vp8 业务，可以在进房前调用该接口查看当前浏览器是否支持 vp8 编码类型 |
  | [setLogConfig()](#setlogconfig) | 配置本地缓存的日志级别, 以及可使用的最大缓存空间。 |
  | [downloadLog()](#downloadlog) | 下载本地缓存生成文件。 |


### createEngine()

创建引擎对象。
你必须先使用此方法，以使用 RTC 提供的各种音视频能力。
再次调用此方法时，会创建另一个独立的引擎实例。

- **类型**

  ```ts
  (appId: string, config?: EngineConfig | undefined) => IRTCEngine
  ```

- **注意**

  + 通过分别调用 [destroyEngine](#destroyengine) 销毁已经创建的多个引擎实例。
  + 每个引擎都将消耗一定系统资源，通常不建议同时创建多于 2 个引擎实例。

- **参数**

  - **appId**

    类型: <code>string</code>

    每个应用的唯一标识符，由 RTC 控制台随机生成的。不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。

  - **config**

    类型: <code>[EngineConfig](Web-keytype.md#engineconfig) | undefined</code>

    引擎级的设置项。例如，是否开启自动播放。

- **返回值**

  类型: <code>IRTCEngine</code>

  创建成功后返回一个可用的 `IRTCEngine` 实例

### destroyEngine()

手动销毁通过 [createEngine](Web-api.md#createengine) 所创建的引擎对象。

- **类型**

  ```ts
  (engine: IRTCEngine) => void
  ```

- **注意**

  + 请确保与需要销毁的相关的业务场景全部结束后，才调用此方法。
  + 本方法为阻塞调用，会阻塞当前线程直到 SDK 彻底完成退出逻辑，因而需要注意不要在回调线程中直接调用本方法，也需要注意不要在回调方法中等待主线程的执行，而同时在主线程调用本方法，从而造成死锁

- **参数**

  - **engine**

    类型: <code>[IRTCEngine](#irtcengine)</code>

    销毁所有和此 `IRTCEngine` 实例相关的内存，并且停止与媒体服务器的任何交互。

### getSdkVersion()

获取 SDK 当前的版本号。

- **类型**

  ```ts
  () => string
  ```

- **返回值**

  类型: <code>string</code>

  SDK 当前的版本号

### enumerateDevices()

枚举可用的媒体输入和输出设备，比如麦克风、摄像头、耳机等。
可以通过该方法获取设备的 deviceId, 用于在 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice)、[startVideoCapture](Web-api.md#startvideocapture)、[startAudioCapture](Web-api.md#startaudiocapture) 方法中指定采集/播放设备。

- **类型**

  ```ts
  () => Promise<MediaDeviceInfo[]>
  ```

- **注意**

  浏览器只有在已经获得设备权限时，才能准确获取设备信息。建议授权访问后调用本接口。

- **返回值**

  类型: <code>Promise<MediaDeviceInfo[]\></code>

  媒体设备列表。

### enableDevices()

向用户获取设备权限

- **类型**

  ```ts
  (options?: { video: boolean; audio: boolean; } | undefined) => Promise<{ video: boolean; audio: boolean;}>
  ```

- **参数**

  - **options**

    类型: <code>{ video: boolean; audio: boolean; } | undefined</code>

    需要获取权限的设备类型

    - **成员**

      | 名称 | 类型 | 描述 |
      | -- | -- | -- |
      | video | `boolean` | 视频设备 |
      | audio | `boolean` | 音频设备 |


- **返回值**

  类型: <code>Promise<{ video: boolean; audio: boolean; }\></code>

  + `video: boolean` 视频设备
  + `audio:boolean` 音频设备

### enumerateAudioCaptureDevices()

该方法枚举可用的麦克风。
可以通过该方法获取设备的 `deviceId`, 用于在 [startAudioCapture](Web-api.md#startaudiocapture)、[setAudioCaptureDevice](Web-api.md#setaudiocapturedevice) 方法中指定使用的麦克风设备。

- **类型**

  ```ts
  () => Promise<MediaDeviceInfo[]>
  ```

- **注意**

  浏览器只有在已经获得设备权限时，才能准确获取设备信息。建议授权访问后调用本接口。

- **返回值**

  类型: <code>Promise<MediaDeviceInfo[]\></code>

  所有的麦克风设备列表。

### enumerateVideoCaptureDevices()

该方法枚举可用的摄像头等。
可以通过该方法获取设备的 deviceId, 用于在 [startVideoCapture](Web-api.md#startvideocapture)、[setVideoCaptureDevice](Web-api.md#setvideocapturedevice) 方法中指定使用的摄像头设备。

- **类型**

  ```ts
  () => Promise<MediaDeviceInfo[]>
  ```

- **注意**

  浏览器只有在已经获得设备权限时，才能准确获取设备信息。建议授权访问后调用本接口。

- **返回值**

  类型: <code>Promise<MediaDeviceInfo[]\></code>

  所有的摄像头设备列表。

### enumerateAudioPlaybackDevices()

该方法枚举可用的音频播放设备，例如耳机、音箱等。
可以通过该方法获取设备的 deviceId, 可用于 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice) 方法中指定音频播放设备。

- **类型**

  ```ts
  () => Promise<MediaDeviceInfo[]>
  ```

- **注意**

  浏览器只有在已经获得设备权限时，才能准确获取设备信息。建议授权访问后调用本接口。

- **返回值**

  类型: <code>Promise<MediaDeviceInfo[]\></code>

  所有的音频播放设备列表。

### isSupported()

浏览器是否支持

- **类型**

  ```ts
  () => Promise<boolean>
  ```

- **返回值**

  类型: <code>Promise<boolean\></code>

  + `True`: 支持
  + `False`：不支持

### getSupportedCodecs()

获取当前浏览器支持的编解码类型。
若你已开通 vp8 业务，可以在进房前调用该接口查看当前浏览器是否支持 vp8 编码类型

- **类型**

  ```ts
  () => Promise<string[]>
  ```

- **返回值**

  类型: <code>Promise<string[]\></code>

  当前浏览器支持的编解码类型

### setLogConfig()

配置本地缓存的日志级别, 以及可使用的最大缓存空间。

- **类型**

  ```ts
  ({ logLevel, LogfileSize }: { logLevel?: 'none' | 'error' | 'warning' | 'info' | 'trace'; LogfileSize?: number;}) => void
  ```

- **注意**

  本方法必须在调用 [createEngine](#createengine) 之前调用。若在 [createEngine](#createengine) 之后调用，则在 [destroyEngine](#destroyengine) 后的下一次 [createEngine](#createengine) 后生效。

- **参数**

  - **{ logLevel, LogfileSize }**

    类型: <code>{ logLevel?: "none" | "error" | "warning" | "info" | "trace" | undefined; LogfileSize?: number | undefined; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | -- | -- | -- |
      | logLevel | `"none" | "error" | "warning" | "info" | "trace" | undefined` | 本地缓存的日志级别。<br>• `none`: 关闭日志。（默认值）<br>• `error`: 错误。<br>• `warning`: 警告。<br>• `info`: 信息。<br>• `trace`: 跟踪。 |
      | LogfileSize | `number | undefined` | 日志可使用的最大缓存空间，单位为 MB。取值范围为 1～100 MB，默认值为 10 MB。 |


### downloadLog()

下载本地缓存生成文件。

- **类型**

  ```ts
  (key?: string | undefined) => void
  ```

- **参数**

  - **key**

    类型: <code>string | undefined</code>

    本地缓存的 key。若为空则下载当前缓存中的日志。


## AudioMixingManager

类型: `interface`

- **API**

  | 名称 | 描述 |
  | -- | -- |
  | [startAudioMixing()](#startaudiomixing) | 开启混音 |
  | [stopAudioMixing()](#stopaudiomixing) | 停止播放音频文件 |
  | [pauseAudioMixing()](#pauseaudiomixing) | 暂停播放音频文件 |
  | [resumeAudioMixing()](#resumeaudiomixing) | 恢复播放音频文件 |
  | [preloadAudioMixing()](#preloadaudiomixing) | 预加载指定音频文件到内存中 |
  | [unloadAudioMixing()](#unloadaudiomixing) | 卸载指定音频文件 |
  | [setAudioMixingVolume()](#setaudiomixingvolume) | 调节混音的音量大小，包括音频文件混音和 PCM 混音。 |
  | [getAudioMixingVolume()](#getaudiomixingvolume) | 获取音频文件的音量 |
  | [getAudioMixingDuration()](#getaudiomixingduration) | 获取音频文件时长 |
  | [getAudioMixingCurrentPosition()](#getaudiomixingcurrentposition) | 获取音频文件播放进度 |
  | [setAudioMixingPosition()](#setaudiomixingposition) | 设置音频文件的起始播放位置 |
  | [enableAudioMixingBuffer()](#enableaudiomixingbuffer) | 启动 PCM 音频数据混音 |
  | [disableAudioMixingBuffer()](#disableaudiomixingbuffer) | 关闭 PCM 混音 |
  | [pushAudioMixingBuffer()](#pushaudiomixingbuffer) | 推送 PCM 音频数据用于混音 |


### startAudioMixing()

开启混音

- **类型**

  ```ts
  (id: number, filePath: string, options: MixOption) => Promise<void>
  ```

- **注意**

  + 如果已经通过 [preloadAudioMixing](#preloadaudiomixing) 加载音效，确保此处的 `ID` 与上次调用 [preloadAudioMixing](#preloadaudiomixing) 设置的 `ID` 相同。
  + 如果使用相同的 `ID` 重复调用本方法，前一次混音会停止，后一次混音开始
  + 开始播放音频文件后，可以调用 [stopAudioMixing](#stopaudiomixing) 方法停止播放音频文件。
  + 本方法的混音数据来源于外部文件，而 [enableAudioMixingBuffer](#enableaudiomixingbuffer) 的混音数据来源于外部缓存且音频格式为 PCM，这两种混音方式可以共存。

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID。
混音 ID 用于标识混音，请保证混音 ID 唯一性。

  - **filePath**

    类型: <code>string</code>

    指定需要混音的音频文件的绝对路径，支持音频文件格式有: mp3，aac等

  - **options**

    类型: <code>[MixOption](Web-keytype.md#mixoption)</code>

    混音配置
可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端

- **返回值**

  类型: <code>Promise<void\></code>

### stopAudioMixing()

停止播放音频文件

- **类型**

  ```ts
  (id: number) => void
  ```

- **注意**

  + 调用 [startAudioMixing](#startaudiomixing) 方法开始播放音频文件后，可以调用本方法停止播放音频文件。
  + 调用本方法停止播放音频文件后，该音频文件会被自动卸载。

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

### pauseAudioMixing()

暂停播放音频文件

- **类型**

  ```ts
  (id: number) => void
  ```

- **注意**

  + 调用 [startAudioMixing](#startaudiomixing) 方法开始播放音频文件后，可以通过调用本方法暂停播放音频文件。
  + 调用本方法暂停播放音频文件后，可调用 [resumeAudioMixing](#resumeaudiomixing) 方法恢复播放及混音。

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

### resumeAudioMixing()

恢复播放音频文件

- **类型**

  ```ts
  (id: number) => void
  ```

- **注意**

  调用 [pauseAudioMixing](#pauseaudiomixing) 方法暂停播放音频文件后，可以通过调用本方法恢复播放及混音。

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

### preloadAudioMixing()

预加载指定音频文件到内存中

- **类型**

  ```ts
  (id: number, filePath: string) => Promise<void>
  ```

- **注意**

  + 需要频繁播放某个音频文件的时候，调用本方法预加载该文件，在播放的时候可以只加载一次该文件，减少 CPU 占用。
  + 本方法只是预加载指定音频文件，只有调用 [startAudioMixing](#startaudiomixing) 方法才开始播放指定音频文件。
  + 调用本方法预加载的指定音频文件可以通过 [unloadAudioMixing](#unloadaudiomixing) 卸载。

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID。用于标识混音，请保证混音 ID 唯一性。
如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。
如果先调用 [startAudioMixing](#startaudiomixing)，再使用相同的 ID 调用本方法 ，会上一个混音停止，然后加载后一个混音。
使用一个 ID 调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 [startAudioMixing](#startaudiomixing) 播放 B.mp3，请先调用 [unloadAudioMixing](#unloadaudiomixing) 卸载 A.mp3 ，否则会报错 AUDIO_MIXING_ERROR_LOAD_CONFLICT。

  - **filePath**

    类型: <code>string</code>

    用于混音文件路径。可以是本地文件的绝对路径，支持音频文件格式有: mp3，aac等

- **返回值**

  类型: <code>Promise<void\></code>

### unloadAudioMixing()

卸载指定音频文件

- **类型**

  ```ts
  (id: number) => void
  ```

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

### setAudioMixingVolume()

调节混音的音量大小，包括音频文件混音和 PCM 混音。

- **类型**

  ```ts
  (id: number, volume: number) => void
  ```

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

  - **volume**

    类型: <code>number</code>

    混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。

+ 0：静音
+ 100：原始音量（默认值）
+ 400: 最大可调音量 (自带溢出保护)

### getAudioMixingVolume()

获取音频文件的音量

- **类型**

  ```ts
  (id: number) => number
  ```

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

- **返回值**

  类型: <code>number</code>

  + `0`: 获取失败
  + `>0`: 成功，音量值

### getAudioMixingDuration()

获取音频文件时长

- **类型**

  ```ts
  (id: number) => number
  ```

- **注意**

  调用本方法获取音频文件时长前，需要先调用 [preloadAudioMixing](#preloadaudiomixing) 或 [startAudioMixing](#startaudiomixing)。

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

- **返回值**

  类型: <code>number</code>

  + `> 0`: 成功, 音频文件时长，单位为毫秒。
  + `< 0`: 失败

### getAudioMixingCurrentPosition()

获取音频文件播放进度

- **类型**

  ```ts
  (id: number) => number
  ```

- **注意**

  调用本方法获取音频文件播放进度前，需要先调用 [startAudioMixing](#startaudiomixing) 开始播放音频文件。

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

- **返回值**

  类型: <code>number</code>

  + `> 0`: 成功, 音频文件播放进度，单位为毫秒。
  + `< 0`: 失败

### setAudioMixingPosition()

设置音频文件的起始播放位置

- **类型**

  ```ts
  (id: number, position: number) => void
  ```

- **注意**

  + 调用本方法你可以根据实际情况从指定的位置播放音频文件，无需从头到尾完整播放一个音频文件。
  + 调用本方法设置音频文件起始播放位置前，需要先调用 [startAudioMixing](#startaudiomixing) 开始播放音频文件。

- **参数**

  - **id**

    类型: <code>number</code>

    混音 ID

  - **position**

    类型: <code>number</code>

    音频文件起始播放位置，单位为毫秒。
你可以通过 [getAudioMixingDuration](#getaudiomixingduration) 获取音频文件总时长，position 的值不得大于音频文件总时长。

### enableAudioMixingBuffer()

启动 PCM 音频数据混音

- **类型**

  ```ts
  (type: AudioMixingType) => void
  ```

- **注意**

  + 必须先调用本方法启动 PCM 音频数据混音，随后调用 [pushAudioMixingBuffer](#pushaudiomixingbuffer) 方法，才会开始混音。
  + 如要结束 PCM 音频数据混音，使用 [disableAudioMixingBuffer](#disableaudiomixingbuffer)。

- **参数**

  - **type**

    类型: <code>[AudioMixingType](Web-keytype.md#audiomixingtype)</code>

    混音类型。是否本地播放、以及是否发送到远端

### disableAudioMixingBuffer()

关闭 PCM 混音

- **类型**

  ```ts
  () => void
  ```

### pushAudioMixingBuffer()

推送 PCM 音频数据用于混音

- **类型**

  ```ts
  (buffer: AudioBuffer) => void
  ```

- **注意**

  调用该方法前，须通过 [enableAudioMixingBuffer](#enableaudiomixingbuffer) 启动外部音频流混音。

- **参数**

  - **buffer**

    类型: <code>AudioBuffer</code>

    音频缓冲池，详见[浏览器文档](https://developer.mozilla.org/en-US/docs/Web/API/AudioBuffer)