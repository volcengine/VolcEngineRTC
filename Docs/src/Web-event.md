## EngineEvents <span id="engineevents"></span>

类型: `interface`

- **API**

| 方法 | 描述 |
| :-- | :-- |
| [onPlayerEvent](#engineevents-onplayerevent) | 播放器事件 |
| [onUserJoined](#engineevents-onuserjoined) | 远端可见用户加入房间，或房内隐身用户切换为可见的回调 |
| [onUserLeave](#engineevents-onuserleave) | 远端可见用户离开房间，或房内可见用户切换为隐身的回调 |
| [onConnectionStateChanged](#engineevents-onconnectionstatechanged) | 连接状态发生变化 |
| [onUserPublishStream](#engineevents-onuserpublishstream) | 房间内新增远端摄像头/麦克风采集音视频流的回调。 |
| [onUserUnpublishStream](#engineevents-onuserunpublishstream) | 房间内远端摄像头/麦克风采集的媒体流移除的回调。 |
| [onUserPublishScreen](#engineevents-onuserpublishscreen) | 房间内新增远端屏幕共享音视频流的回调。 |
| [onUserUnpublishScreen](#engineevents-onuserunpublishscreen) | 房间内远端屏幕共享音视频流移除的回调。 |
| [onRemoteVideoFirstFrame](#engineevents-onremotevideofirstframe) | 视频首帧解码 |
| [onRemoteAudioFirstFrame](#engineevents-onremoteaudiofirstframe) | 远端音频首帧播放事件 |
| [onVideoDeviceStateChanged](#engineevents-onvideodevicestatechanged) | 视频媒体设备状态改变。 |
| [onAudioDeviceStateChanged](#engineevents-onaudiodevicestatechanged) | 音频媒体设备状态改变。 |
| [onTrackEnded](#engineevents-ontrackended) | 断流事件 |
| [onRoomMessageReceived](#engineevents-onroommessagereceived) | 接收到房间内广播消息的事件。 |
| [onRoomBinaryMessageReceived](#engineevents-onroombinarymessagereceived) | 接收到房间内二进制广播消息的事件。 |
| [onUserMessageReceived](#engineevents-onusermessagereceived) | 收到来自房间中其他用户通过 [sendUserMessage](Web-api.md#sendusermessage) 发来的点对点文本消息时，会收到此事件 |
| [onUserBinaryMessageReceived](#engineevents-onuserbinarymessagereceived) | 收到来自房间中其他用户通过 sendUserBinaryMessage 发来的点对点二进制消息时，会收到此事件 |
| [onRemoteStreamStats](#engineevents-onremotestreamstats) | 用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s |
| [onLocalStreamStats](#engineevents-onlocalstreamstats) | 本地音/视频流统计信息以及网络状况，统计周期为 2s |
| [onPublicStreamStats](#engineevents-onpublicstreamstats) | 调用 [startPlayPublicStream](Web-api.md#startplaypublicstream) 订阅公共流，后将触发此回调，周期为 2s，包含各项统计信息。 |
| [onLocalAudioPropertiesReport](#engineevents-onlocalaudiopropertiesreport) | 调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。<br>本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。 |
| [onRemoteAudioPropertiesReport](#engineevents-onremoteaudiopropertiesreport) | 远端用户进房后，本地调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport)，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。 |
| [onActiveSpeaker](#engineevents-onactivespeaker) | 成功调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport) 后，当房间内用户数量大于或等于 2 且有活跃用户时，你会周期性收到此回调，获取房间内音量最大用户的信息。 |
| [onAudioPlaybackDeviceChanged](#engineevents-onaudioplaybackdevicechanged) | 当调用 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice) 设置音频播放设备时，会收到此事件。 |
| [onUserStartAudioCapture](#engineevents-onuserstartaudiocapture) | 房间内的可见用户调用 [startAudioCapture](Web-api.md#startaudiocapture) 开启音频采集时，房间内其他用户会收到此事件。 |
| [onUserStopAudioCapture](#engineevents-onuserstopaudiocapture) | 房间内的可见用户调用 [stopAudioCapture](Web-api.md#stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此事件。 |
| [onUserStartVideoCapture](#engineevents-onuserstartvideocapture) | 房间内的可见用户调用 [startVideoCapture](Web-api.md#startvideocapture) 开启内部视频采集时，房间内其他用户会收到此事件。 |
| [onUserStopVideoCapture](#engineevents-onuserstopvideocapture) | 房间内的可见用户调用 [stopVideoCapture](Web-api.md#stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此事件。 |
| [onSEIMessageReceived](#engineevents-onseimessagereceived) | 接收到包含 SEI 数据的视频帧事件 |
| [onAutoSubscribeResult](#engineevents-onautosubscriberesult) | 如果开启了自动订阅，订阅成功或者失败后可以收到此事件 |
| [onAutoPublishResult](#engineevents-onautopublishresult) | 如果开启了自动发布，发布成功或者失败后可以收到此事件 |
| [onAutoplayFailed](#engineevents-onautoplayfailed) | 自动播放失败 |
| [onError](#engineevents-onerror) | 当 SDK 内部发生不可逆转错误时触发该回调 |
| [onAudioMixingStateChanged](#engineevents-onaudiomixingstatechanged) | 音频混音文件播放状态改变事件 |
| [onUserMessageReceivedOutsideRoom](#engineevents-onusermessagereceivedoutsideroom) | 接收到房间外消息的事件。 |
| [onUserBinaryMessageReceivedOutsideRoom](#engineevents-onuserbinarymessagereceivedoutsideroom) | 接收到房间外二进制消息的事件。 |
| [onTokenWillExpire](#engineevents-ontokenwillexpire) | Token 过期前 30 秒将触发该回调。<br>调用 [updateToken](Web-api.md#updatetoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。 |
| [onCloudProxyConnected](#engineevents-oncloudproxyconnected) | 调用 [startCloudProxy](Web-api.md#startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。 |
| [onPushPublicStreamResult](#engineevents-onpushpublicstreamresult) | 公共流发布结果回调。<br>调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布公共流后，结果通过此回调通知用户。 |
| [onPublicStreamSEIMessageReceived](#engineevents-onpublicstreamseimessagereceived) | 回调公共流中包含的 SEI 信息。<br>调用 [startPlayPublicStream](Web-api.md#startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。 |
| [onFirstPublicStreamVideoFrameDecoded](#engineevents-onfirstpublicstreamvideoframedecoded) | 公共流的视频首帧解码成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。 |
| [onFirstPublicStreamAudioFrameDecoded](#engineevents-onfirstpublicstreamaudioframedecoded) | 公共流的音频首帧解码成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。 |
| [onFirstPublicStreamVideoFrameRendered](#engineevents-onfirstpublicstreamvideoframerendered) | 公共流的首帧视频渲染成功。<br>关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。 |
| [onAudioPlaybackDeviceTestVolume](#engineevents-onaudioplaybackdevicetestvolume) | 回调音频设备测试时的播放音量 |
| [onNetworkQuality](#engineevents-onnetworkquality) | 加入房间后，会以每2秒一次的频率，收到本端上行及下行的网络质量信息。 |
| [onSimulcastSubscribeFallback](#engineevents-onsimulcastsubscribefallback) | 订阅的视频流发生回退，或从回退中恢复时，收到此回调。 |
| [onRemoteVideoSizeChanged](#engineevents-onremotevideosizechanged) | 远端视频分辨率发生改变时，房间内订阅此视频流的用户会收到此回调。 |
| [onStreamMixingEvent](#engineevents-onstreammixingevent) | 转推直播相关事件 |
| [onVideoStreamBanned](#engineevents-onvideostreambanned) | 调用服务端接口 BanUserStream/UnbanUserStream 封禁/解禁指定用户的视频流发布时，触发该回调。 |
| [onAudioStreamBanned](#engineevents-onaudiostreambanned) | 调用服务端接口 BanUserStream/UnbanUserStream 封禁/解禁指定用户的音频流发布时，触发该回调。 |
| [onLocalVideoSizeChanged](#engineevents-onlocalvideosizechanged) | 当实际采集的参数与设置的编码参数不一致时，SDK 会触发该回调返回实际采集视频的参数。 |
| [onSubtitleStateChanged](#engineevents-onsubtitlestatechanged) | 字幕状态发生改变回调。<br>当你调用 [startSubtitle](Web-api.md#startsubtitle) 和 [stopSubtitle](Web-api.md#stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。 |
| [onSubtitleMessageReceived](#engineevents-onsubtitlemessagereceived) | 字幕相关信息回调。<br>当你成功调用 [startSubtitle](Web-api.md#startsubtitle) 后会收到此回调，通知字幕的相关信息。 |
| [onServerParamsSetResult](#engineevents-onserverparamssetresult) | 设置接收客户端即时消息的服务器成功或失败时收到本事件。 |
| [onForwardStreamError](#engineevents-onforwardstreamerror) | 设置跨房间转发媒体流失败时收到本事件。 |


### onPlayerEvent <span id="engineevents-onplayerevent"></span> 

播放器事件

- **类型**

  ```ts
  (event: PlayerEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[PlayerEvent](Web-keytype.md#playerevent)</code>

### onUserJoined <span id="engineevents-onuserjoined"></span> 

远端可见用户加入房间，或房内隐身用户切换为可见的回调

- **类型**

  ```ts
  (event: onUserJoinedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[onUserJoinedEvent](Web-keytype.md#onuserjoinedevent)</code>

### onUserLeave <span id="engineevents-onuserleave"></span> 

远端可见用户离开房间，或房内可见用户切换为隐身的回调

- **类型**

  ```ts
  (event: onUserLeaveEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[onUserLeaveEvent](Web-keytype.md#onuserleaveevent)</code>

### onConnectionStateChanged <span id="engineevents-onconnectionstatechanged"></span> 

连接状态发生变化

- **类型**

  ```ts
  (event: ConnectionStateChangeEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[ConnectionStateChangeEvent](Web-keytype.md#connectionstatechangeevent)</code>

### onUserPublishStream <span id="engineevents-onuserpublishstream"></span> 

房间内新增远端摄像头/麦克风采集音视频流的回调。

- **类型**

  ```ts
  (event: { userId: string; mediaType: MediaType;}) => void
  ```

- **注意**

  当房间内的远端用户调用 [publishStream](Web-api.md#publishstream) 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeStream](Web-api.md#subscribestream) 订阅此流。

- **参数**

  - **event**

    类型: <code>{ userId: string; mediaType: [MediaType](Web-keytype.md#mediatype); }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 远端流发布用户的用户 ID |
      | mediaType | `MediaType` | 远端媒体流的类型 |


### onUserUnpublishStream <span id="engineevents-onuserunpublishstream"></span> 

房间内远端摄像头/麦克风采集的媒体流移除的回调。

- **类型**

  ```ts
  (event: { userId: string; mediaType: MediaType; reason: StreamRemoveReason;}) => void
  ```

- **注意**

  当房间内的远端用户调用 [unpublishStream](Web-api.md#unpublishstream) 成功取消发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [unsubscribeStream](Web-api.md#unsubscribestream) 取消订阅此流。

- **参数**

  - **event**

    类型: <code>{ userId: string; mediaType: [MediaType](Web-keytype.md#mediatype); reason: [StreamRemoveReason](Web-keytype.md#streamremovereason); }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 移除的远端流发布用户的用户 ID |
      | mediaType | `MediaType` | 远端媒体流的类型 |
      | reason | `StreamRemoveReason` | 远端流移除的原因 |


### onUserPublishScreen <span id="engineevents-onuserpublishscreen"></span> 

房间内新增远端屏幕共享音视频流的回调。

- **类型**

  ```ts
  (event: { userId: string; mediaType: MediaType;}) => void
  ```

- **注意**

  当房间内的远端用户调用 [publishScreen](Web-api.md#publishscreen) 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeScreen](Web-api.md#subscribescreen) 订阅此流。

- **参数**

  - **event**

    类型: <code>{ userId: string; mediaType: [MediaType](Web-keytype.md#mediatype); }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 远端流发布用户的用户 ID |
      | mediaType | `MediaType` | 远端媒体流的类型 |


### onUserUnpublishScreen <span id="engineevents-onuserunpublishscreen"></span> 

房间内远端屏幕共享音视频流移除的回调。

- **类型**

  ```ts
  (event: { userId: string; mediaType: MediaType; reason: StreamRemoveReason;}) => void
  ```

- **注意**

  当房间内的远端用户调用 [unpublishScreen](Web-api.md#unpublishscreen) 成功取消发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [unsubscribeScreen](Web-api.md#unsubscribescreen) 取消订阅此流。

- **参数**

  - **event**

    类型: <code>{ userId: string; mediaType: [MediaType](Web-keytype.md#mediatype); reason: [StreamRemoveReason](Web-keytype.md#streamremovereason); }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 移除的远端流发布用户的用户 ID |
      | mediaType | `MediaType` | 远端媒体流的类型 |
      | reason | `StreamRemoveReason` | 远端流移除的原因 |


### onRemoteVideoFirstFrame <span id="engineevents-onremotevideofirstframe"></span> 

视频首帧解码

- **类型**

  ```ts
  (event: onVideoFirstFrameRenderedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[onVideoFirstFrameRenderedEvent](Web-keytype.md#onvideofirstframerenderedevent)</code>

### onRemoteAudioFirstFrame <span id="engineevents-onremoteaudiofirstframe"></span> 

远端音频首帧播放事件

- **类型**

  ```ts
  (event: onAudioFirstFrameDecodedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[onAudioFirstFrameDecodedEvent](Web-keytype.md#onaudiofirstframedecodedevent)</code>

### onVideoDeviceStateChanged <span id="engineevents-onvideodevicestatechanged"></span> 

视频媒体设备状态改变。

- **类型**

  ```ts
  (event: DeviceInfo) => void
  ```

- **参数**

  - **event**

    类型: <code>[DeviceInfo](Web-keytype.md#deviceinfo)</code>

    媒体设备信息及状态。

### onAudioDeviceStateChanged <span id="engineevents-onaudiodevicestatechanged"></span> 

音频媒体设备状态改变。

- **类型**

  ```ts
  (event: DeviceInfo) => void
  ```

- **参数**

  - **event**

    类型: <code>[DeviceInfo](Web-keytype.md#deviceinfo)</code>

    媒体设备信息及状态。

### onTrackEnded <span id="engineevents-ontrackended"></span> 

断流事件。
建议在回调里重新采集。

- **类型**

  ```ts
  (event: { kind: string; isScreen: boolean;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ kind: string; isScreen: boolean; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | kind | `string` | 类型 |
      | isScreen | `boolean` | 是否屏幕流 |


### onRoomMessageReceived <span id="engineevents-onroommessagereceived"></span> 

接收到房间内广播消息的事件。

- **类型**

  ```ts
  (event: { userId: string; message: any;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ userId: string; message: any; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 发送消息用户的 userId |
      | message | `any` | 消息内容 |


### onRoomBinaryMessageReceived <span id="engineevents-onroombinarymessagereceived"></span> 

接收到房间内二进制广播消息的事件。

- **类型**

  ```ts
  (event: { userId: string; message: ArrayBuffer;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ userId: string; message: ArrayBuffer; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 发送消息用户的 userId |
      | message | `ArrayBuffer` | 消息内容 |


### onUserMessageReceived <span id="engineevents-onusermessagereceived"></span> 

收到来自房间中其他用户通过 [sendUserMessage](Web-api.md#sendusermessage) 发来的点对点文本消息时，会收到此事件

- **类型**

  ```ts
  (event: UserMessageEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[UserMessageEvent](Web-keytype.md#usermessageevent)</code>

### onUserBinaryMessageReceived <span id="engineevents-onuserbinarymessagereceived"></span> 

收到来自房间中其他用户通过 sendUserBinaryMessage 发来的点对点二进制消息时，会收到此事件

- **类型**

  ```ts
  (event: UserBinaryMessageEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[UserBinaryMessageEvent](Web-keytype.md#userbinarymessageevent)</code>

### onRemoteStreamStats <span id="engineevents-onremotestreamstats"></span> 

用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s

- **类型**

  ```ts
  (stats: RemoteStreamStats) => void
  ```

- **参数**

  - **stats**

    类型: <code>[RemoteStreamStats](Web-keytype.md#remotestreamstats)</code>

### onLocalStreamStats <span id="engineevents-onlocalstreamstats"></span> 

本地音/视频流统计信息以及网络状况，统计周期为 2s

- **类型**

  ```ts
  (stats: LocalStreamStats) => void
  ```

- **参数**

  - **stats**

    类型: <code>[LocalStreamStats](Web-keytype.md#localstreamstats)</code>

### onPublicStreamStats <span id="engineevents-onpublicstreamstats"></span> 

调用 [startPlayPublicStream](Web-api.md#startplaypublicstream) 订阅公共流，后将触发此回调，周期为 2s，包含各项统计信息。

- **类型**

  ```ts
  (stats: PublicStreamStats) => void
  ```

- **参数**

  - **stats**

    类型: <code>[PublicStreamStats](Web-keytype.md#publicstreamstats)</code>

### onLocalAudioPropertiesReport <span id="engineevents-onlocalaudiopropertiesreport"></span> 

调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。
本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。

- **类型**

  ```ts
  (event: LocalAudioPropertiesInfo[]) => void
  ```

- **参数**

  - **event**

    类型: <code>[LocalAudioPropertiesInfo](Web-keytype.md#localaudiopropertiesinfo)[]</code>

    本地音频信息。

### onRemoteAudioPropertiesReport <span id="engineevents-onremoteaudiopropertiesreport"></span> 

远端用户进房后，本地调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport)，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。
远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。

- **类型**

  ```ts
  (event: RemoteAudioPropertiesInfo[]) => void
  ```

- **参数**

  - **event**

    类型: <code>[RemoteAudioPropertiesInfo](Web-keytype.md#remoteaudiopropertiesinfo)[]</code>

    远端音频信息，其中包含音频流属性、房间 ID、用户 ID。

### onActiveSpeaker <span id="engineevents-onactivespeaker"></span> 

成功调用 [enableAudioPropertiesReport](Web-api.md#enableaudiopropertiesreport) 后，当房间内用户数量大于或等于 2 且有活跃用户时，你会周期性收到此回调，获取房间内音量最大用户的信息。

- **类型**

  ```ts
  (userInfo: UserInfo) => void
  ```

- **参数**

  - **event**

    类型: <code>[UserInfo](Web-keytype.md#userinfo)</code>

    音量最大用户的信息。

### onAudioPlaybackDeviceChanged <span id="engineevents-onaudioplaybackdevicechanged"></span> 

当调用 [setAudioPlaybackDevice](Web-api.md#setaudioplaybackdevice) 设置音频播放设备时，会收到此事件。

- **类型**

  ```ts
  (event: MediaDeviceInfo) => void
  ```

- **参数**

  - **event**

    类型: <code>MediaDeviceInfo</code>

    媒体设备信息，参看 [MediaDeviceInfo](https://developer.mozilla.org/en-US/docs/Web/API/MediaDeviceInfo)。

### onUserStartAudioCapture <span id="engineevents-onuserstartaudiocapture"></span> 

房间内的可见用户调用 [startAudioCapture](Web-api.md#startaudiocapture) 开启音频采集时，房间内其他用户会收到此事件。

- **类型**

  ```ts
  (event: { userId: string;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ userId: string; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 开启音频采集的远端用户 ID |


### onUserStopAudioCapture <span id="engineevents-onuserstopaudiocapture"></span> 

房间内的可见用户调用 [stopAudioCapture](Web-api.md#stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此事件。

- **类型**

  ```ts
  (event: { userId: string;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ userId: string; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 关闭音频采集的远端用户 ID |


### onUserStartVideoCapture <span id="engineevents-onuserstartvideocapture"></span> 

房间内的可见用户调用 [startVideoCapture](Web-api.md#startvideocapture) 开启内部视频采集时，房间内其他用户会收到此事件。

- **类型**

  ```ts
  (event: { userId: string;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ userId: string; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 开启视频采集的用户 ID |


### onUserStopVideoCapture <span id="engineevents-onuserstopvideocapture"></span> 

房间内的可见用户调用 [stopVideoCapture](Web-api.md#stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此事件。

- **类型**

  ```ts
  (event: { userId: string;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ userId: string; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 停止视频采集的用户的 ID |


### onSEIMessageReceived <span id="engineevents-onseimessagereceived"></span> 

接收到包含 SEI 数据的视频帧事件

- **类型**

  ```ts
  (event: onSEIMessageEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[onSEIMessageEvent](Web-keytype.md#onseimessageevent)</code>

    SEI 数据事件

### onAutoSubscribeResult <span id="engineevents-onautosubscriberesult"></span> 

如果开启了自动订阅，订阅成功或者失败后可以收到此事件

- **类型**

  ```ts
  (event: { userId: string; isScreen: boolean; state: SubscribeState;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ userId: string; isScreen: boolean; state: [SubscribeState](Web-keytype.md#subscribestate); }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | userId | `string` | 订阅用户的 userId |
      | isScreen | `boolean` | 是否为屏幕流 |
      | state | `SubscribeState` | 订阅状态 |


### onAutoPublishResult <span id="engineevents-onautopublishresult"></span> 

如果开启了自动发布，发布成功或者失败后可以收到此事件

- **类型**

  ```ts
  (event: { isScreen: boolean; state: PublishState;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ isScreen: boolean; state: [PublishState](Web-keytype.md#publishstate); }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | isScreen | `boolean` | 是否为屏幕流 |
      | state | `PublishState` | 发布状态 |


### onAutoplayFailed <span id="engineevents-onautoplayfailed"></span> 

自动播放失败

- **类型**

  ```ts
  (event: AutoPlayFailedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[AutoPlayFailedEvent](Web-keytype.md#autoplayfailedevent)</code>

    播放器事件

### onError <span id="engineevents-onerror"></span> 

当 SDK 内部发生不可逆转错误时触发该回调

- **类型**

  ```ts
  (event: { errorCode: ErrorCode.DUPLICATE_LOGIN | ErrorCode.RTM_DUPLICATE_LOGIN | ErrorCode.RTM_TOKEN_ERROR | ErrorCode.EXPIRED_TOKEN | ErrorCode.RECONNECT_FAILED;}) => void
  ```

- **参数**

  - **event**

    类型: <code>{ errorCode: ErrorCode.DUPLICATE_LOGIN | ErrorCode.RTM_DUPLICATE_LOGIN | ErrorCode.RTM_TOKEN_ERROR | ErrorCode.EXPIRED_TOKEN | ErrorCode.RECONNECT_FAILED; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | errorCode | `ErrorCode.EXPIRED_TOKEN | ErrorCode.DUPLICATE_LOGIN | ErrorCode.RTM_DUPLICATE_LOGIN | ErrorCode.RTM_TOKEN_ERROR | ErrorCode.RECONNECT_FAILED` | 查看错误码和发生错误的原因 |


### onAudioMixingStateChanged <span id="engineevents-onaudiomixingstatechanged"></span> 

音频混音文件播放状态改变事件

- **类型**

  ```ts
  (event: AudioMixingStateChangedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[AudioMixingStateChangedEvent](Web-keytype.md#audiomixingstatechangedevent)</code>

### onUserMessageReceivedOutsideRoom <span id="engineevents-onusermessagereceivedoutsideroom"></span> 

接收到房间外消息的事件。

- **类型**

  ```ts
  (event: UserMessageEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[UserMessageEvent](Web-keytype.md#usermessageevent)</code>

### onUserBinaryMessageReceivedOutsideRoom <span id="engineevents-onuserbinarymessagereceivedoutsideroom"></span> 

接收到房间外二进制消息的事件。

- **类型**

  ```ts
  (event: UserBinaryMessageEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[UserBinaryMessageEvent](Web-keytype.md#userbinarymessageevent)</code>

### onTokenWillExpire <span id="engineevents-ontokenwillexpire"></span> 

Token 过期前 30 秒将触发该回调。
调用 [updateToken](Web-api.md#updatetoken) 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。

- **类型**

  ```ts
  () => void
  ```

### onCloudProxyConnected <span id="engineevents-oncloudproxyconnected"></span> 

调用 [startCloudProxy](Web-api.md#startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。

- **类型**

  ```ts
  (event: CloudProxyConnectedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[CloudProxyConnectedEvent](Web-keytype.md#cloudproxyconnectedevent)</code>

### onPushPublicStreamResult <span id="engineevents-onpushpublicstreamresult"></span> 

公共流发布结果回调。
调用 [startPushPublicStream](Web-api.md#startpushpublicstream) 发布公共流后，结果通过此回调通知用户。

- **类型**

  ```ts
  (event: PublicStreamResultEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[PublicStreamResultEvent](Web-keytype.md#publicstreamresultevent)</code>

### onPublicStreamSEIMessageReceived <span id="engineevents-onpublicstreamseimessagereceived"></span> 

回调公共流中包含的 SEI 信息。
调用 [startPlayPublicStream](Web-api.md#startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。

- **类型**

  ```ts
  (event: PublicStreamSEIMessageEvent) => void
  ```

- **注意**

  当公共流中的多路视频流均包含有 SEI 信息时：

  + SEI 不互相冲突时，将通过多次回调分别发送；
  + SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。

- **参数**

  - **event**

    类型: <code>[PublicStreamSEIMessageEvent](Web-keytype.md#publicstreamseimessageevent)</code>

### onFirstPublicStreamVideoFrameDecoded <span id="engineevents-onfirstpublicstreamvideoframedecoded"></span> 

公共流的视频首帧解码成功。
关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。

- **类型**

  ```ts
  (event: PublicStreamVideoFirstFrameDecodedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[PublicStreamVideoFirstFrameDecodedEvent](Web-keytype.md#publicstreamvideofirstframedecodedevent)</code>

### onFirstPublicStreamAudioFrameDecoded <span id="engineevents-onfirstpublicstreamaudioframedecoded"></span> 

公共流的音频首帧解码成功。
关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。

- **类型**

  ```ts
  (event: PublicStreamAudioFirstFrameDecodedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[PublicStreamAudioFirstFrameDecodedEvent](Web-keytype.md#publicstreamaudiofirstframedecodedevent)</code>

### onFirstPublicStreamVideoFrameRendered <span id="engineevents-onfirstpublicstreamvideoframerendered"></span> 

公共流的首帧视频渲染成功。
关于订阅公共流，参看 [startPlayPublicStream](Web-api.md#startplaypublicstream)。

- **类型**

  ```ts
  (event: PublicStreamAudioFirstFrameDecodedEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[PublicStreamAudioFirstFrameDecodedEvent](Web-keytype.md#publicstreamaudiofirstframedecodedevent)</code>

### onAudioPlaybackDeviceTestVolume <span id="engineevents-onaudioplaybackdevicetestvolume"></span> 

回调音频设备测试时的播放音量

- **类型**

  ```ts
  (volume: number) => void
  ```

- **注意**

  调用 [startAudioPlaybackDeviceTest](Web-api.md#startaudioplaybackdevicetest) 或 [startAudioDeviceRecordTest](Web-api.md#startaudiodevicerecordtest)，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。

- **参数**

  - **volume**

    类型: <code>number</code>

    音频设备测试播放音量。单位：毫秒。推荐设置为 200 ms。范围：[0,255]

### onNetworkQuality <span id="engineevents-onnetworkquality"></span> 

加入房间后，会以每2秒一次的频率，收到本端上行及下行的网络质量信息。

- **类型**

  ```ts
  (uplinkNetworkQuality: NetworkQuality, downlinkNetworkQuality: NetworkQuality) => void
  ```

- **参数**

  - **uplinkNetworkQuality**

    类型: <code>[NetworkQuality](Web-keytype.md#networkquality)</code>

    上行网络质量。

  - **downlinkNetworkQuality**

    类型: <code>[NetworkQuality](Web-keytype.md#networkquality)</code>

    下行网络质量。

### onSimulcastSubscribeFallback <span id="engineevents-onsimulcastsubscribefallback"></span> 

订阅的视频流发生回退，或从回退中恢复时，收到此回调。

- **类型**

  ```ts
  (event: RemoteStreamSwitch) => void
  ```

- **参数**

  - **event**

    类型: <code>[RemoteStreamSwitch](Web-keytype.md#remotestreamswitch)</code>

    流切换信息

### onRemoteVideoSizeChanged <span id="engineevents-onremotevideosizechanged"></span> 

远端视频分辨率发生改变时，房间内订阅此视频流的用户会收到此回调。

- **类型**

  ```ts
  (key: RemoteStreamKey, info: { width: number; height: number;}) => void
  ```

- **参数**

  - **key**

    类型: <code>[RemoteStreamKey](Web-keytype.md#remotestreamkey)</code>

  - **info**

    类型: <code>{ width: number; height: number; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | width | `number` | 宽度，单位：px |
      | height | `number` | 高度，单位：px |


### onStreamMixingEvent <span id="engineevents-onstreammixingevent"></span> 

转推直播相关事件

- **类型**

  ```ts
  (event: StreamMixingEvent) => void
  ```

- **参数**

  - **event**

    类型: <code>[StreamMixingEvent](Web-keytype.md#streammixingevent)</code>

### onVideoStreamBanned <span id="engineevents-onvideostreambanned"></span> 

调用服务端接口 BanUserStream/UnbanUserStream 封禁/解禁指定用户的视频流发布时，触发该回调。

- **类型**

  ```ts
  (event: VideoStreamBannedEvent) => void
  ```

- **注意**

  + 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。
  + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。
  + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。
  + 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。
  + 同一房间解散后再次创建，房间内状态清空。

- **参数**

  - **event**

    类型: <code>[VideoStreamBannedEvent](Web-keytype.md#videostreambannedevent)</code>

### onAudioStreamBanned <span id="engineevents-onaudiostreambanned"></span> 

调用服务端接口 BanUserStream/UnbanUserStream 封禁/解禁指定用户的音频流发布时，触发该回调。

- **类型**

  ```ts
  (event: AudioStreamBannedEvent) => void
  ```

- **注意**

  + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。
  + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。
  + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。
  + 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。
  + 同一房间解散后再次创建，房间内状态清空。

- **参数**

  - **event**

    类型: <code>[AudioStreamBannedEvent](Web-keytype.md#audiostreambannedevent)</code>

### onLocalVideoSizeChanged <span id="engineevents-onlocalvideosizechanged"></span> 

当实际采集的参数与设置的编码参数不一致时，SDK 会触发该回调返回实际采集视频的参数。

- **类型**

  ```ts
  (e: { streamIndex: StreamIndex; info: { width: number; height: number; };}) => void
  ```

- **参数**

  - **e**

    类型: <code>{ streamIndex: [StreamIndex](Web-keytype.md#streamindex); info: { width: number; height: number;}; }</code>

    - **成员**

      | 名称 | 类型 | 描述 |
      | :-- | :-- | :-- |
      | streamIndex | `StreamIndex` | 视频流属性。 |
      | info | `{ width: number; height: number; }` | 视频实际采集参数。 |
      | info.width | `number` | 视频宽度，单位：px。 |
      | info.height | `number` | 视频高度，单位：px。 |


### onSubtitleStateChanged <span id="engineevents-onsubtitlestatechanged"></span> 

字幕状态发生改变回调。
当你调用 [startSubtitle](Web-api.md#startsubtitle) 和 [stopSubtitle](Web-api.md#stopsubtitle) 使字幕状态发生改变或字幕任务出现错误时，触发该回调。

- **类型**

  ```ts
  (e: SubtitleEvent) => void
  ```

- **参数**

  - **e**

    类型: <code>[SubtitleEvent](Web-keytype.md#subtitleevent)</code>

    字幕任务状态。

### onSubtitleMessageReceived <span id="engineevents-onsubtitlemessagereceived"></span> 

字幕相关信息回调。
当你成功调用 [startSubtitle](Web-api.md#startsubtitle) 后会收到此回调，通知字幕的相关信息。

- **类型**

  ```ts
  (e: SubtitleMessage[]) => void
  ```

- **参数**

  - **e**

    类型: <code>[SubtitleMessage](Web-keytype.md#subtitlemessage)[]</code>

    字幕具体内容。

### onServerParamsSetResult <span id="engineevents-onserverparamssetresult"></span> 

设置接收客户端即时消息的服务器成功或失败时收到本事件。

- **类型**

  ```ts
  (error?: ErrorCode) => void
  ```

- **注意**

  + 调用 [setServerParams](Web-api.md#setserverparams) 时触发。
  + 当调用 [setServerParams](Web-api.md#setserverparams) 设置服务器参数后断网，会在重连成功后收到本事件。

- **参数**

  - **error**

    类型: <code>[ErrorCode](Web-errorcode.md#errorcode) | undefined</code>

    错误码

### onForwardStreamError <span id="engineevents-onforwardstreamerror"></span> 

设置跨房间转发媒体流失败时收到本事件。

- **类型**

  ```ts
  (e: ForwardStreamStateInfo) => void
  ```

- **参数**

  - **e**

    类型: <code>[ForwardStreamStateInfo](Web-keytype.md#forwardstreamstateinfo)</code>

    跨房间转发媒体流状态信息。