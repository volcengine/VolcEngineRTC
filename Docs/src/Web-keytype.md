## MixOption <span id="mixoption"></span>

类型: `interface`

混音配置

<p style="font-size: 16px;font-weight: bolder;"> playCount <span id="mixoption-playcount"></span></p> 

类型: <code>number</code>

混音播放次数

+ play_count <= 0: 无限循环
+ play_count == 1: 播放一次（默认）
+ play_count > 1: 播放 play_count 次

<p style="font-size: 16px;font-weight: bolder;"> type <span id="mixoption-type"></span></p> 

类型: <code>[AudioMixingType](#audiomixingtype) | undefined</code>

混音播放类型


## AudioMixingType <span id="audiomixingtype"></span>

类型: `enum`

混音播放类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | PLAYOUT | `0` | 仅本地播放 |
  | PUBLISH | `1` | 仅发送到远端 |
  | PLAYOUT_AND_PUBLISH | `2` | 在本地播放并发送到远端 |



## PlayerEvent <span id="playerevent"></span>

类型: `interface`

播放器事件

<p style="font-size: 16px;font-weight: bolder;"> type <span id="playerevent-type"></span></p> 

类型: <code>"video" | "audio"</code>

类型

<p style="font-size: 16px;font-weight: bolder;"> eventName <span id="playerevent-eventname"></span></p> 

类型: <code>string</code>

事件名称

<p style="font-size: 16px;font-weight: bolder;"> rawEvent <span id="playerevent-rawevent"></span></p> 

类型: <code>Event</code>

播放事件。详见[官方文档](https://developer.mozilla.org/en-US/docs/Web/API/HTMLMediaElement/play_event)

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="playerevent-userid"></span></p> 

类型: <code>string</code>

进房用户的 userId

<p style="font-size: 16px;font-weight: bolder;"> publicStreamId <span id="playerevent-publicstreamid"></span></p> 

类型: <code>string | undefined</code>

公共流 ID。

<p style="font-size: 16px;font-weight: bolder;"> readyState <span id="playerevent-readystate"></span></p> 

类型: <code>number</code>

媒体就绪状态，详见[官方文档](https://developer.mozilla.org/en-US/docs/Web/API/HTMLMediaElement/readyState)

<p style="font-size: 16px;font-weight: bolder;"> currentTime <span id="playerevent-currenttime"></span></p> 

类型: <code>number</code>

当前时间

<p style="font-size: 16px;font-weight: bolder;"> isScreen <span id="playerevent-isscreen"></span></p> 

类型: <code>boolean | undefined</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## onUserJoinedEvent <span id="onuserjoinedevent"></span>

类型: `interface`

远端用户进房事件

<p style="font-size: 16px;font-weight: bolder;"> userInfo <span id="onuserjoinedevent-userinfo"></span></p> 

类型: <code>[UserInfo](#userinfo)</code>

进房用户的 userId


## UserInfo <span id="userinfo"></span>

类型: `interface`

用户信息。

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="userinfo-userid"></span></p> 

类型: <code>string</code>

用户 ID，长度在 128 字节以内的非空字符串。

<p style="font-size: 16px;font-weight: bolder;"> extraInfo <span id="userinfo-extrainfo"></span></p> 

类型: <code>string | undefined</code>

用户传递的额外信息，最大长度为 200 字节。会在 [onUserJoined](Web-event.md#onuserjoined) 中回调给远端用户。

- **注意**

  支持以下字符集范围:

  + 26 个大写字母: A ~ Z
  + 26 个小写字母: a ~ z
  + 10 个数字: 0 ~ 9
  + 特殊字符: 下划线 "_"，at 符 "@"，减号 "-"


## onUserLeaveEvent <span id="onuserleaveevent"></span>

类型: `interface`

远端用户退房事件

<p style="font-size: 16px;font-weight: bolder;"> userInfo <span id="onuserleaveevent-userinfo"></span></p> 

类型: <code>[UserInfo](#userinfo)</code>

用户信息

<p style="font-size: 16px;font-weight: bolder;"> reason <span id="onuserleaveevent-reason"></span></p> 

类型: <code>[UserOfflineReason](#userofflinereason)</code>

远端用户离开房间的原因


## UserOfflineReason <span id="userofflinereason"></span>

类型: `enum`

远端用户离开房间的原因

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | QUIT | `0` | 远端用户调用 `leaveRoom` 主动退出房间。 |
  | DROPPED | `1` | 远端用户因 Token 过期或网络原因等掉线。 |
  | SWITCH_TO_INVISIBLE | `2` | 远端用户调用 `setUserVisibility` 切换至不可见状态。 |
  | KICKED_BY_ADMIN | `3` | 服务端调用 OpenAPI 将远端用户踢出房间。 |



## ConnectionStateChangeEvent <span id="connectionstatechangeevent"></span>

类型: `interface`

连接状态改变

<p style="font-size: 16px;font-weight: bolder;"> state <span id="connectionstatechangeevent-state"></span></p> 

类型: <code>[ConnectionState](#connectionstate)</code>

内部连接状态


## ConnectionState <span id="connectionstate"></span>

类型: `enum`

SDK 与信令服务器连接状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | CONNECTION_START | `0` | 进行连接前准备，锁定相关资源。 |
  | CONNECTION_STATE_DISCONNECTED | `1` | 连接断开。 |
  | CONNECTION_STATE_CONNECTING | `2` | 首次连接，正在连接中。 |
  | CONNECTION_STATE_CONNECTED | `3` | 首次连接成功。 |
  | CONNECTION_STATE_RECONNECTING | `4` | 连接断开后重新连接中。 |
  | CONNECTION_STATE_RECONNECTED | `5` | 连接断开后重连成功。 |
  | CONNECTION_STATE_LOST | `6` | 处于 `CONNECTION_STATE_DISCONNECTED` 状态超过 10 秒，且期间重连未成功。SDK将继续尝试重连。 |



## MediaType <span id="mediatype"></span>

类型: `enum`

媒体流类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | AUDIO | `1` | 只控制音频 |
  | VIDEO | `2` | 只控制视频 |
  | AUDIO_AND_VIDEO | `3` | 同时控制音频和视频 |



## StreamRemoveReason <span id="streamremovereason"></span>

类型: `enum`

房间内远端流移除原因。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | STREAM_REMOVE_REASON_UNPUBLISH | `0` | 远端用户停止发布流。 |
  | STREAM_REMOVE_REASON_PUBLISH_FAILED | `1` | 远端用户发布流失败。 |
  | STREAM_REMOVE_REASON_KEEP_LIVE_FAILED | `2` | 保活失败。 |
  | STREAM_REMOVE_REASON_CLIENT_DISCONNECTED | `3` | 远端用户断网。 |
  | STREAM_REMOVE_REASON_REPUBLISH | `4` | 远端用户重新发布流。 |
  | STREAM_REMOVE_REASON_OTHER | `5` | 其他原因。 |



## onVideoFirstFrameRenderedEvent <span id="onvideofirstframerenderedevent"></span>

类型: `interface`

第一帧远端视频显示在视图上

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="onvideofirstframerenderedevent-userid"></span></p> 

类型: <code>string</code>

发布视频用户的 userId

<p style="font-size: 16px;font-weight: bolder;"> height <span id="onvideofirstframerenderedevent-height"></span></p> 

类型: <code>number</code>

高度

<p style="font-size: 16px;font-weight: bolder;"> width <span id="onvideofirstframerenderedevent-width"></span></p> 

类型: <code>number</code>

宽度

<p style="font-size: 16px;font-weight: bolder;"> isScreen <span id="onvideofirstframerenderedevent-isscreen"></span></p> 

类型: <code>boolean</code>

是否为屏幕流


## onAudioFirstFrameDecodedEvent <span id="onaudiofirstframedecodedevent"></span>

类型: `interface`

第一帧远端音频解码事件

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="onaudiofirstframedecodedevent-userid"></span></p> 

类型: <code>string</code>

发布视频用户的 userId

<p style="font-size: 16px;font-weight: bolder;"> isScreen <span id="onaudiofirstframedecodedevent-isscreen"></span></p> 

类型: <code>boolean</code>

是否为屏幕共享流


## DeviceInfo <span id="deviceinfo"></span>

类型: `interface`

媒体设备信息及状态。

<p style="font-size: 16px;font-weight: bolder;"> mediaDeviceInfo <span id="deviceinfo-mediadeviceinfo"></span></p> 

类型: <code>MediaDeviceInfo</code>

媒体设备信息，参看 [MediaDeviceInfo](https://developer.mozilla.org/en-US/docs/Web/API/MediaDeviceInfo)。

<p style="font-size: 16px;font-weight: bolder;"> deviceState <span id="deviceinfo-devicestate"></span></p> 

类型: <code>"active" | "inactive"</code>

设备状态。
active：设备已连接。
inactive：设备已断开连接。


## UserMessageEvent <span id="usermessageevent"></span>

类型: `interface`

点对点文本消息

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="usermessageevent-userid"></span></p> 

类型: <code>string</code>

发送消息的用户

<p style="font-size: 16px;font-weight: bolder;"> message <span id="usermessageevent-message"></span></p> 

类型: <code>string</code>

点对点文本消息


## UserBinaryMessageEvent <span id="userbinarymessageevent"></span>

类型: `interface`

点对点二进制消息

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="userbinarymessageevent-userid"></span></p> 

类型: <code>string</code>

发送消息的用户

<p style="font-size: 16px;font-weight: bolder;"> message <span id="userbinarymessageevent-message"></span></p> 

类型: <code>ArrayBuffer</code>

点对点二进制消息


## RemoteStreamStats <span id="remotestreamstats"></span>

类型: `interface`

远端媒体流统计信息，统计周期为 2s 。
本地用户订阅媒体流成功后，SDK 会周期性地通知远端的媒体流在此次统计周期内的接收状况。此数据结构为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="remotestreamstats-userid"></span></p> 

类型: <code>string</code>

进房用户的 userId

<p style="font-size: 16px;font-weight: bolder;"> audioStats <span id="remotestreamstats-audiostats"></span></p> 

类型: <code>[RemoteAudioStats](#remoteaudiostats)</code>

远端音频流信息

<p style="font-size: 16px;font-weight: bolder;"> videoStats <span id="remotestreamstats-videostats"></span></p> 

类型: <code>[RemoteVideoStats](#remotevideostats)</code>

远端视频流信息

<p style="font-size: 16px;font-weight: bolder;"> isScreen <span id="remotestreamstats-isscreen"></span></p> 

类型: <code>boolean</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## RemoteAudioStats <span id="remoteaudiostats"></span>

类型: `interface`

远端音频流统计信息，统计周期为 2s 。
本地用户订阅音频流成功后，SDK 会周期性地通知远端的音频流在此次统计周期内的接收状况。此数据结构为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> audioLossRate <span id="remoteaudiostats-audiolossrate"></span></p> 

类型: <code>number</code>

音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。

<p style="font-size: 16px;font-weight: bolder;"> receivedKBitrate <span id="remoteaudiostats-receivedkbitrate"></span></p> 

类型: <code>number</code>

接收码率。统计周期内的音频接收码率，单位为 kbps 。

<p style="font-size: 16px;font-weight: bolder;"> stallCount <span id="remoteaudiostats-stallcount"></span></p> 

类型: <code>number | undefined</code>

统计周期内的卡顿次数

<p style="font-size: 16px;font-weight: bolder;"> stallDuration <span id="remoteaudiostats-stallduration"></span></p> 

类型: <code>number | undefined</code>

统计周期内的卡顿时长，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> totalRtt <span id="remoteaudiostats-totalrtt"></span></p> 

类型: <code>number</code>

全链路往返传输时延。单位 ms。

- **注意**

  对于 FireFox 浏览器，此值不准确。

<p style="font-size: 16px;font-weight: bolder;"> statsInterval <span id="remoteaudiostats-statsinterval"></span></p> 

类型: <code>number</code>

统计间隔。此次统计周期的间隔，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="remoteaudiostats-rtt"></span></p> 

类型: <code>number</code>

往返时延，单位：ms

<p style="font-size: 16px;font-weight: bolder;"> jitterBufferDelay <span id="remoteaudiostats-jitterbufferdelay"></span></p> 

类型: <code>number</code>

抖动延迟，单位：ms

<p style="font-size: 16px;font-weight: bolder;"> numChannels <span id="remoteaudiostats-numchannels"></span></p> 

类型: <code>number</code>

声道数

<p style="font-size: 16px;font-weight: bolder;"> receivedSampleRate <span id="remoteaudiostats-receivedsamplerate"></span></p> 

类型: <code>number</code>

接收侧采样率

<p style="font-size: 16px;font-weight: bolder;"> concealedSamples <span id="remoteaudiostats-concealedsamples"></span></p> 

类型: <code>number</code>

音频丢包补偿(PLC) 样点总个数

<p style="font-size: 16px;font-weight: bolder;"> concealmentEvent <span id="remoteaudiostats-concealmentevent"></span></p> 

类型: <code>number</code>

音频丢包补偿(PLC) 累计次数


## RemoteVideoStats <span id="remotevideostats"></span>

类型: `interface`

远端视频流统计信息，统计周期为 2s 。
本地用户订阅视频流成功后，SDK 会周期性地通知远端的视频流在此次统计周期内的接收状况。此数据结构为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="remotevideostats-width"></span></p> 

类型: <code>number</code>

宽度，单位：px

<p style="font-size: 16px;font-weight: bolder;"> height <span id="remotevideostats-height"></span></p> 

类型: <code>number</code>

高度，单位：px

<p style="font-size: 16px;font-weight: bolder;"> videoLossRate <span id="remotevideostats-videolossrate"></span></p> 

类型: <code>number</code>

视频丢包率。统计周期内的视频下行丢包率，取值范围为 [0, 1] 。

<p style="font-size: 16px;font-weight: bolder;"> receivedKBitrate <span id="remotevideostats-receivedkbitrate"></span></p> 

类型: <code>number</code>

接收码率。统计周期内的视频接收码率，单位为 kbps 。

<p style="font-size: 16px;font-weight: bolder;"> decoderOutputFrameRate <span id="remotevideostats-decoderoutputframerate"></span></p> 

类型: <code>number</code>

解码器输出帧率。统计周期内的视频解码器输出帧率，单位 fps 。

<p style="font-size: 16px;font-weight: bolder;"> stallCount <span id="remotevideostats-stallcount"></span></p> 

类型: <code>number | undefined</code>

统计周期内的卡顿次数

<p style="font-size: 16px;font-weight: bolder;"> stallDuration <span id="remotevideostats-stallduration"></span></p> 

类型: <code>number | undefined</code>

统计周期内的卡顿时长，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> totalRtt <span id="remotevideostats-totalrtt"></span></p> 

类型: <code>number</code>

全链路往返传输时延。单位 ms。

- **注意**

  对于 FireFox 浏览器，此值不准确。

<p style="font-size: 16px;font-weight: bolder;"> isScreen <span id="remotevideostats-isscreen"></span></p> 

类型: <code>boolean</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。

<p style="font-size: 16px;font-weight: bolder;"> statsInterval <span id="remotevideostats-statsinterval"></span></p> 

类型: <code>number</code>

统计间隔。此次统计周期的间隔，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="remotevideostats-rtt"></span></p> 

类型: <code>number</code>

客户端到服务端数据传输的往返时延，单位：ms


## LocalStreamStats <span id="localstreamstats"></span>

类型: `interface`

本地媒体流统计信息以及网络状况，统计周期为 2s 。
本地用户发布媒体流成功后，SDK 会周期性地通知本地用户发布的媒体流在此次统计周期内的发送状况。此数据结构为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> audioStats <span id="localstreamstats-audiostats"></span></p> 

类型: <code>[LocalAudioStats](#localaudiostats)</code>

本地发送音频流的统计信息。

<p style="font-size: 16px;font-weight: bolder;"> videoStats <span id="localstreamstats-videostats"></span></p> 

类型: <code>[LocalVideoStats](#localvideostats)</code>

本地发送视频流的统计信息。

<p style="font-size: 16px;font-weight: bolder;"> isScreen <span id="localstreamstats-isscreen"></span></p> 

类型: <code>boolean</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## LocalAudioStats <span id="localaudiostats"></span>

类型: `interface`

本地音频流统计信息以及网络状况，统计周期为 2s 。
本地用户发布音频流成功后，SDK 会周期性地通知本地用户发布的音频流在此次统计周期内的发送状况。此数据结构为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> audioLossRate <span id="localaudiostats-audiolossrate"></span></p> 

类型: <code>number</code>

音频丢包率。统计周期内的音频上行丢包率，取值范围为 [0, 1] 。

<p style="font-size: 16px;font-weight: bolder;"> sendKBitrate <span id="localaudiostats-sendkbitrate"></span></p> 

类型: <code>number</code>

发送码率。统计周期内的音频接收码率，单位为 kbps 。

<p style="font-size: 16px;font-weight: bolder;"> recordSampleRate <span id="localaudiostats-recordsamplerate"></span></p> 

类型: <code>number</code>

采集采样率。统计周期内的音频采集采样率信息，单位为 Hz 。

<p style="font-size: 16px;font-weight: bolder;"> statsInterval <span id="localaudiostats-statsinterval"></span></p> 

类型: <code>number</code>

统计间隔。此次统计周期的间隔，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="localaudiostats-rtt"></span></p> 

类型: <code>number</code>

客户端到服务端数据传输的往返时延，单位：ms

<p style="font-size: 16px;font-weight: bolder;"> numChannels <span id="localaudiostats-numchannels"></span></p> 

类型: <code>number</code>

声道数


## LocalVideoStats <span id="localvideostats"></span>

类型: `interface`

本地视频流统计信息以及网络状况，统计周期为 2s 。
本地用户发布视频流成功后，SDK 会周期性地通知本地用户发布的视频流在此次统计周期内的发送状况。此数据结构为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> sentKBitrate <span id="localvideostats-sentkbitrate"></span></p> 

类型: <code>number</code>

发送码率，单位：kbps。统计周期内的视频发送码率

<p style="font-size: 16px;font-weight: bolder;"> sentFrameRate <span id="localvideostats-sentframerate"></span></p> 

类型: <code>number</code>

发送帧率。统计周期内的视频发送帧率，单位为 fps 。

<p style="font-size: 16px;font-weight: bolder;"> encoderOutputFrameRate <span id="localvideostats-encoderoutputframerate"></span></p> 

类型: <code>number</code>

编码器输出帧率。当前编码器在此次统计周期内的输出帧率，单位为 fps 。

<p style="font-size: 16px;font-weight: bolder;"> rendererOutputFrameRate <span id="localvideostats-rendereroutputframerate"></span></p> 

类型: <code>number | undefined</code>

本地渲染帧率。统计周期内的本地视频渲染帧率，单位为 fps 。

<p style="font-size: 16px;font-weight: bolder;"> statsInterval <span id="localvideostats-statsinterval"></span></p> 

类型: <code>number</code>

统计间隔。此次统计周期的间隔，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> videoLossRate <span id="localvideostats-videolossrate"></span></p> 

类型: <code>number</code>

视频丢包率。统计周期内的视频上行丢包率，取值范围为 [0, 1] 。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="localvideostats-rtt"></span></p> 

类型: <code>number</code>

客户端到服务端数据传输的往返时延，单位：ms

<p style="font-size: 16px;font-weight: bolder;"> encodedFrameWidth <span id="localvideostats-encodedframewidth"></span></p> 

类型: <code>number</code>

视频编码宽度，单位为 px。

<p style="font-size: 16px;font-weight: bolder;"> encodedFrameHeight <span id="localvideostats-encodedframeheight"></span></p> 

类型: <code>number</code>

视频编码高度，单位为 px。

<p style="font-size: 16px;font-weight: bolder;"> encodedFrameCount <span id="localvideostats-encodedframecount"></span></p> 

类型: <code>number</code>

统计周期内发送的视频帧总数

<p style="font-size: 16px;font-weight: bolder;"> codecType <span id="localvideostats-codectype"></span></p> 

类型: <code>string</code>

视频编码格式。
"H264": H.264 格式。
"VP8": VP8 格式。

<p style="font-size: 16px;font-weight: bolder;"> isScreen <span id="localvideostats-isscreen"></span></p> 

类型: <code>boolean</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## PublicStreamStats <span id="publicstreamstats"></span>

用户订阅的公共流统计信息以及网络状况，统计周期为 2s。

- **类型**

  ```ts
  Omit<
    RemoteStreamStats,
    'userId' | 'isScreen'
  > & {
    publicStreamId: string;
  }
  ```

- **成员**

  | 名称 | 类型 | 描述 |
  | :-- | :-- | :-- |
  | publicStreamId | <code>string</code> | 公共流 ID。 |
  | RemoteStreamStats | <code>[RemoteStreamStats](#remotestreamstats)</code> | 远端媒体流统计信息 |



## LocalAudioPropertiesInfo <span id="localaudiopropertiesinfo"></span>

类型: `interface`

本地音频信息

<p style="font-size: 16px;font-weight: bolder;"> streamIndex <span id="localaudiopropertiesinfo-streamindex"></span></p> 

类型: <code>[StreamIndex](#streamindex)</code>

流属性，标记该流为麦克风采集音频流或屏幕音频流。

<p style="font-size: 16px;font-weight: bolder;"> audioPropertiesInfo <span id="localaudiopropertiesinfo-audiopropertiesinfo"></span></p> 

类型: <code>[AudioPropertiesInfo](#audiopropertiesinfo)</code>

音频属性信息。


## StreamIndex <span id="streamindex"></span>

类型: `enum`

流属性

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | STREAM_INDEX_MAIN | `0` | 主流。包括：通过默认摄像头/麦克风采集到的视频/音频; |
  | STREAM_INDEX_SCREEN | `1` | 屏幕流。共享的视频流，或来自声卡的本地播放音频流。 |



## AudioPropertiesInfo <span id="audiopropertiesinfo"></span>

类型: `interface`

音频属性信息

<p style="font-size: 16px;font-weight: bolder;"> linearVolume <span id="audiopropertiesinfo-linearvolume"></span></p> 

类型: <code>number</code>

线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。<br>

- [0, 25]: 无声 <br>
- [26, 75]: 低音量 <br>
- [76, 204]: 中音量 <br>
- [205, 255]: 高音量 <br>

<p style="font-size: 16px;font-weight: bolder;"> nonlinearVolume <span id="audiopropertiesinfo-nonlinearvolume"></span></p> 

类型: <code>number</code>

非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。 <br>

- [-127, -60]: 无声 <br>
- [-59, -40]: 低音量 <br>
- [-39, -20]: 中音量 <br>
- [-19, 0]: 高音量 <br>


## RemoteAudioPropertiesInfo <span id="remoteaudiopropertiesinfo"></span>

类型: `interface`

远端音频信息

<p style="font-size: 16px;font-weight: bolder;"> streamKey <span id="remoteaudiopropertiesinfo-streamkey"></span></p> 

类型: <code>[StreamKey](#streamkey)</code>

远端流信息

<p style="font-size: 16px;font-weight: bolder;"> audioPropertiesInfo <span id="remoteaudiopropertiesinfo-audiopropertiesinfo"></span></p> 

类型: <code>[AudioPropertiesInfo](#audiopropertiesinfo)</code>

远端音频属性信息


## StreamKey <span id="streamkey"></span>

类型: `interface`

远端流信息

<p style="font-size: 16px;font-weight: bolder;"> roomId <span id="streamkey-roomid"></span></p> 

类型: <code>string</code>

房间 ID

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="streamkey-userid"></span></p> 

类型: <code>string</code>

用户 ID

<p style="font-size: 16px;font-weight: bolder;"> streamIndex <span id="streamkey-streamindex"></span></p> 

类型: <code>[StreamIndex](#streamindex)</code>

流属性，标记该流为麦克风采集音频流或屏幕音频流。


## onSEIMessageEvent <span id="onseimessageevent"></span>

类型: `interface`

收到带有 SEI 消息的视频帧时，收到此回调

<p style="font-size: 16px;font-weight: bolder;"> remoteStreamKey <span id="onseimessageevent-remotestreamkey"></span></p> 

类型: <code>[RemoteStreamKey](#remotestreamkey)</code>

包含 SEI 发送者的用户名，所在的房间名和媒体流

<p style="font-size: 16px;font-weight: bolder;"> sei <span id="onseimessageevent-sei"></span></p> 

类型: <code>Uint8Array</code>

收到的 SEI 消息内容


## RemoteStreamKey <span id="remotestreamkey"></span>

类型: `interface`

远端流信息

<p style="font-size: 16px;font-weight: bolder;"> roomId <span id="remotestreamkey-roomid"></span></p> 

类型: <code>string</code>

房间 ID

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="remotestreamkey-userid"></span></p> 

类型: <code>string</code>

用户 ID

<p style="font-size: 16px;font-weight: bolder;"> streamIndex <span id="remotestreamkey-streamindex"></span></p> 

类型: <code>[StreamIndex](#streamindex)</code>

流属性，包括主流、屏幕流。


## SubscribeState <span id="subscribestate"></span>

类型: `enum`

音视频流订阅结果

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | SUBSCRIBE_SUCC | `0` | 更新订阅状态成功 |
  | SUBSCRIBE_FAIL | `1` | 更新订阅状态失败 |



## PublishState <span id="publishstate"></span>

类型: `enum`

音视频流发布结果

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | PUBLISH_SUCC | `0` | 发布成功 |
  | PUBLISH_FAIL | `1` | 发布失败 |



## AutoPlayFailedEvent <span id="autoplayfailedevent"></span>

类型: `interface`

自动播放失败事件

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="autoplayfailedevent-userid"></span></p> 

类型: <code>string</code>

自动播放失败的流所属的用户 ID。不带此参数时表示本地流播放失败。

<p style="font-size: 16px;font-weight: bolder;"> kind <span id="autoplayfailedevent-kind"></span></p> 

类型: <code>"video" | "audio"</code>

自动播放失败的媒体类型
例如，当同一用户的视频流和音频流自动播放都失败时，将触发两次 `onAutoPlayFailed` 回调，分别包含 `audio` 和 `video` 参数。

<p style="font-size: 16px;font-weight: bolder;"> streamIndex <span id="autoplayfailedevent-streamindex"></span></p> 

类型: <code>[StreamIndex](#streamindex)</code>

视频流属性。

<p style="font-size: 16px;font-weight: bolder;"> mediaType <span id="autoplayfailedevent-mediatype"></span></p> 

类型: <code>MediaType.AUDIO | MediaType.VIDEO</code>

远端媒体流的类型


## AudioMixingStateChangedEvent <span id="audiomixingstatechangedevent"></span>

类型: `interface`

音频混音文件播放状态改变事件

<p style="font-size: 16px;font-weight: bolder;"> mixId <span id="audiomixingstatechangedevent-mixid"></span></p> 

类型: <code>number</code>

混音 ID

<p style="font-size: 16px;font-weight: bolder;"> state <span id="audiomixingstatechangedevent-state"></span></p> 

类型: <code>[AudioMixingState](#audiomixingstate)</code>

混音状态

<p style="font-size: 16px;font-weight: bolder;"> error <span id="audiomixingstatechangedevent-error"></span></p> 

类型: <code>[AudioMixingError](Web-errorcode.md#audiomixingerror)</code>

混音错误


## AudioMixingState <span id="audiomixingstate"></span>

类型: `enum`

音频混音文件播放状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | AUDIO_MIXING_STATE_PRELOADED | `0` | 混音已加载 |
  | AUDIO_MIXING_STATE_PLAYING | `1` | 混音正在播放 |
  | AUDIO_MIXING_STATE_PAUSED | `2` | 混音暂停 |
  | AUDIO_MIXING_STATE_STOPPED | `3` | 混音停止 |
  | AUDIO_MIXING_STATE_FAILED | `4` | 混音播放失败 |
  | AUDIO_MIXING_STATE_FINISHED | `5` | 混音播放结束 |
  | AUDIO_MIXING_STATE_PCM_ENABLED | `6` | 准备 PCM 混音 |
  | AUDIO_MIXING_STATE_PCM_DISABLED | `7` | PCM 混音播放结束 |



## CloudProxyConnectedEvent <span id="cloudproxyconnectedevent"></span>

类型: `interface`

SDK 成功连接云代理服务器事件。

<p style="font-size: 16px;font-weight: bolder;"> interval <span id="cloudproxyconnectedevent-interval"></span></p> 

类型: <code>number</code>

SDK 开启云代理后，加入频道的耗时。


## PublicStreamResultEvent <span id="publicstreamresultevent"></span>

类型: `interface`

公共流发布结果

<p style="font-size: 16px;font-weight: bolder;"> code <span id="publicstreamresultevent-code"></span></p> 

类型: <code>number</code>

公共流发布事件编号

<p style="font-size: 16px;font-weight: bolder;"> message <span id="publicstreamresultevent-message"></span></p> 

类型: <code>string</code>

公共流发布事件详情

+ `200`: 发布或订阅成功
+ `1191`: 公共流的参数异常，请修改参数后重试
+ `1192`: 服务端状态异常，将自动重试
+ `1193`: 内部错误，不可恢复，请重试
+ `1195`: 推流失败，将自动重试，用户不需要处理
+ `1196`: 推流失败，10 s 后会重试，重试 3 次后停止重试


## PublicStreamSEIMessageEvent <span id="publicstreamseimessageevent"></span>

类型: `interface`

公共流中包含的 SEI 信息。

<p style="font-size: 16px;font-weight: bolder;"> publicStreamId <span id="publicstreamseimessageevent-publicstreamid"></span></p> 

类型: <code>string</code>

公共流 ID

<p style="font-size: 16px;font-weight: bolder;"> sei <span id="publicstreamseimessageevent-sei"></span></p> 

类型: <code>Uint8Array</code>

收到的 SEI 消息内容


## PublicStreamVideoFirstFrameDecodedEvent <span id="publicstreamvideofirstframedecodedevent"></span>

公共流首帧视频解码事件。

- **类型**

  ```ts
  Omit<
    onVideoFirstFrameDecodedEvent,
    'userId'
  > & {
    publicStreamId: string;
  }
  ```

- **成员**

  | 名称 | 类型 | 描述 |
  | :-- | :-- | :-- |
  | publicStreamId | <code>string</code> | 公共流 ID。 |
  | onVideoFirstFrameDecodedEvent | <code>[onVideoFirstFrameDecodedEvent](#onvideofirstframedecodedevent)</code> | 视频首帧解码事件。 |



## onVideoFirstFrameDecodedEvent <span id="onvideofirstframedecodedevent"></span>

类型: `interface`

第一帧远端视频解码事件

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="onvideofirstframedecodedevent-userid"></span></p> 

类型: <code>string</code>

发布视频用户的 userId

<p style="font-size: 16px;font-weight: bolder;"> height <span id="onvideofirstframedecodedevent-height"></span></p> 

类型: <code>number</code>

高度

<p style="font-size: 16px;font-weight: bolder;"> width <span id="onvideofirstframedecodedevent-width"></span></p> 

类型: <code>number</code>

宽度


## PublicStreamAudioFirstFrameDecodedEvent <span id="publicstreamaudiofirstframedecodedevent"></span>

类型: `interface`

公共流首帧解码/渲染事件。

<p style="font-size: 16px;font-weight: bolder;"> publicStreamId <span id="publicstreamaudiofirstframedecodedevent-publicstreamid"></span></p> 

类型: <code>string</code>

公共流 ID。


## NetworkQuality <span id="networkquality"></span>

类型: `enum`

网络质量

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | UNKNOWN | `0` | 网络质量未知 |
  | EXCELLENT | `1` | 网络质量极好 |
  | GOOD | `2` | 主观感觉和 Excellent 差不多，但码率可能略低 |
  | POOR | `3` | 主观感受有瑕疵但不影响沟通 |
  | BAD | `4` | 勉强能沟通但不顺畅。建议降低采样率、码率或通过 UI 提示用户是否切换为纯语音通话。 |
  | VBAD | `5` | 网络质量非常差，基本不能沟通。建议通过 UI 给出弱网提示。 |
  | DOWN | `6` | 网络连接断开，无法通话。 |



## RemoteStreamSwitch <span id="remotestreamswitch"></span>

类型: `interface`

流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="remotestreamswitch-userid"></span></p> 

类型: <code>string</code>

订阅的音视频流的发布者的用户 ID

<p style="font-size: 16px;font-weight: bolder;"> isScreen <span id="remotestreamswitch-isscreen"></span></p> 

类型: <code>boolean</code>

是否是屏幕共享流

<p style="font-size: 16px;font-weight: bolder;"> beforeVideoIndex <span id="remotestreamswitch-beforevideoindex"></span></p> 

类型: <code>number</code>

原分辨率视频流的下标

<p style="font-size: 16px;font-weight: bolder;"> afterVideoIndex <span id="remotestreamswitch-aftervideoindex"></span></p> 

类型: <code>number</code>

现分辨率视频流的下标

<p style="font-size: 16px;font-weight: bolder;"> beforeEnable <span id="remotestreamswitch-beforeenable"></span></p> 

类型: <code>boolean</code>

原媒体流是否是视频流

<p style="font-size: 16px;font-weight: bolder;"> afterEnable <span id="remotestreamswitch-afterenable"></span></p> 

类型: <code>boolean</code>

现媒体流是否是视频流

<p style="font-size: 16px;font-weight: bolder;"> reason <span id="remotestreamswitch-reason"></span></p> 

类型: <code>[FallbackOrRecoverReason](#fallbackorrecoverreason)</code>

触发流回退或恢复的原因


## FallbackOrRecoverReason <span id="fallbackorrecoverreason"></span>

类型: `enum`

触发流回退或恢复的原因

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | Unknown | `-1` | 其他原因，非带宽原因引起的回退或恢复。默认值 |
  | SubscribeFallbackByBandwidth | `0` | 由带宽不足导致的流回退。 |
  | SubscribeRecoverByBandwidth | `2` | 由带宽恢复导致的流恢复。 |



## StreamMixingEvent <span id="streammixingevent"></span>

类型: `interface`

转推直播相关事件。

<p style="font-size: 16px;font-weight: bolder;"> event <span id="streammixingevent-event"></span></p> 

类型: <code>[StreamMixingEventType](#streammixingeventtype)</code>

转推直播事件类型。

<p style="font-size: 16px;font-weight: bolder;"> error <span id="streammixingevent-error"></span></p> 

类型: <code>[StreamMixingEventErrorCode](Web-errorcode.md#streammixingeventerrorcode)</code>

转推直播事件错误码。

<p style="font-size: 16px;font-weight: bolder;"> message <span id="streammixingevent-message"></span></p> 

类型: <code>string</code>

转推直播事件错误详情。


## StreamMixingEventType <span id="streammixingeventtype"></span>

类型: `enum`

转推直播事件类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | START | `1` | 已发起开始转推请求。 |
  | START_SUCCESS | `2` | 转推至 CDN 成功。 |
  | START_FAILED | `3` | 推流 CDN 失败。 |
  | UPDATE | `4` | 已发起更新转推请求。 |
  | UPDATE_SUCCESS | `5` | 成功应用新配置进行推流。 |
  | UPDATE_FAILED | `6` | 更新合流失败，新配置参数校验失败或配置未生效。 |
  | STOP | `7` | 已发起停止转推请求。 |
  | STOP_SUCCESS | `8` | 成功停止推流至CDN。 |
  | STOP_FAILED | `9` | 停止推流失败。 |



## VideoStreamBannedEvent <span id="videostreambannedevent"></span>

类型: `interface`

视频流发布封禁/解禁事件

<p style="font-size: 16px;font-weight: bolder;"> uid <span id="videostreambannedevent-uid"></span></p> 

类型: <code>string</code>

被禁用/解禁的视频流用户 ID

<p style="font-size: 16px;font-weight: bolder;"> banned <span id="videostreambannedevent-banned"></span></p> 

类型: <code>boolean</code>

视频流发布状态
true：视频流发布被禁止
false: 视频流发布被解禁


## AudioStreamBannedEvent <span id="audiostreambannedevent"></span>

类型: `interface`

音频流发布封禁/解禁事件

<p style="font-size: 16px;font-weight: bolder;"> uid <span id="audiostreambannedevent-uid"></span></p> 

类型: <code>string</code>

被禁用/解禁的音频流用户 ID

<p style="font-size: 16px;font-weight: bolder;"> banned <span id="audiostreambannedevent-banned"></span></p> 

类型: <code>boolean</code>

音频流发布状态
true：音频流发布被禁止
false: 音频流发布被解禁


## SubtitleEvent <span id="subtitleevent"></span>

类型: `interface`

字幕任务状态。

<p style="font-size: 16px;font-weight: bolder;"> event <span id="subtitleevent-event"></span></p> 

类型: <code>[SubtitleEventType](#subtitleeventtype)</code>

字幕任务状态类型。

<p style="font-size: 16px;font-weight: bolder;"> errorCode <span id="subtitleevent-errorcode"></span></p> 

类型: <code>[ErrorCode](Web-errorcode.md#errorcode) | undefined</code>

字幕任务错误码。

+ `SUBTITLE_ERR_POSTPROCESS`: 云端媒体处理内部出现错误。
+ `SUBTITLE_ERR_CONNECTION_ERROR`: 第三方服务连接失败。
+ `SUBTITLE_ERR_PROCESS_ERROR`: 云端媒体处理超时未响应。
+ `SUBTITLE_ERR_UNKNOWN`: 客户端无法识别云端媒体处理发送的错误码。

<p style="font-size: 16px;font-weight: bolder;"> errorMessage <span id="subtitleevent-errormessage"></span></p> 

类型: <code>string | undefined</code>

字幕相关信息。


## SubtitleEventType <span id="subtitleeventtype"></span>

类型: `enum`

字幕任务状态类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | STARTED | `0` | 字幕已开启。 |
  | STOPPED | `1` | 字幕已关闭。 |
  | ERROR | `2` | 字幕任务出现错误。 |



## SubtitleMessage <span id="subtitlemessage"></span>

类型: `interface`

字幕具体内容。

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="subtitlemessage-userid"></span></p> 

类型: <code>string</code>

说话者的用户ID。

<p style="font-size: 16px;font-weight: bolder;"> text <span id="subtitlemessage-text"></span></p> 

类型: <code>string</code>

语音识别或翻译后的文本, 采用 UTF-8 编码。

<p style="font-size: 16px;font-weight: bolder;"> definite <span id="subtitlemessage-definite"></span></p> 

类型: <code>boolean</code>

语音识别出的文本是否为一段完整的一句话。 True 代表是, False 代表不是。

<p style="font-size: 16px;font-weight: bolder;"> sequence <span id="subtitlemessage-sequence"></span></p> 

类型: <code>number</code>

语音识别或翻译后形成的文本的序列号。同一发言人的完整发言和不完整发言会按递增顺序单独分别编号。

<p style="font-size: 16px;font-weight: bolder;"> language <span id="subtitlemessage-language"></span></p> 

类型: <code>string</code>

字幕语种代号。

<p style="font-size: 16px;font-weight: bolder;"> mode <span id="subtitlemessage-mode"></span></p> 

类型: <code>[SUBTITLE_MODE](#subtitle_mode)</code>

字幕模式。


## SUBTITLE_MODE <span id="subtitle_mode"></span>

类型: `enum`

字幕模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | ASR_ONLY | `0` | 识别模式。在此模式下，房间内用户语音会被转为文字。 |
  | ASR_AND_TRANSLATION | `1` | 翻译模式。在此模式下，房间内用户语音会先被转为文字，再被翻译为目标语言。 |



## ForwardStreamStateInfo <span id="forwardstreamstateinfo"></span>

类型: `interface`

跨房间转发媒体流状态信息。

<p style="font-size: 16px;font-weight: bolder;"> roomId <span id="forwardstreamstateinfo-roomid"></span></p> 

类型: <code>string</code>

跨房间转发媒体流的目标房间 ID。

<p style="font-size: 16px;font-weight: bolder;"> state <span id="forwardstreamstateinfo-state"></span></p> 

类型: <code>[ForwardStreamState](#forwardstreamstate)</code>

跨房间转发媒体流状态。

<p style="font-size: 16px;font-weight: bolder;"> error <span id="forwardstreamstateinfo-error"></span></p> 

类型: <code>[ForwardStreamError](Web-errorcode.md#forwardstreamerror)</code>

跨房间转发媒体流错误码。


## ForwardStreamState <span id="forwardstreamstate"></span>

类型: `enum`

跨房间转发媒体流状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | FORWARD_STREAM_STATE_SUCCESS | `0` | 成功。 |
  | FORWARD_STREAM_STATE_FAILURE | `1` | 失败。 |



## RoomConfig <span id="roomconfig"></span>

类型: `interface`

房间参数配置。

<p style="font-size: 16px;font-weight: bolder;"> isAutoPublish <span id="roomconfig-isautopublish"></span></p> 

类型: <code>boolean | undefined</code>

是否自动发布音视频流，默认为自动发布。
取消自动发布后，通过调用 [publishStream](Web-api.md#publishstream) 进行音视频流发布。

<p style="font-size: 16px;font-weight: bolder;"> isAutoSubscribeAudio <span id="roomconfig-isautosubscribeaudio"></span></p> 

类型: <code>boolean | undefined</code>

是否自动订阅音频流，默认为自动订阅。
不包含屏幕流。
进房后，你可以调用 [subscribeStream](Web-api.md#subscribestream)、[unsubscribeStream](Web-api.md#unsubscribestream) 修改订阅设置。

<p style="font-size: 16px;font-weight: bolder;"> isAutoSubscribeVideo <span id="roomconfig-isautosubscribevideo"></span></p> 

类型: <code>boolean | undefined</code>

是否自动订阅视频流，默认为自动订阅。
不包含屏幕流。
进房后，你可以调用 [subscribeStream](Web-api.md#subscribestream)、[unsubscribeStream](Web-api.md#unsubscribestream) 修改订阅设置。

<p style="font-size: 16px;font-weight: bolder;"> remoteVideoConfig <span id="roomconfig-remotevideoconfig"></span></p> 

类型: <code>[RemoteVideoConfig](#remotevideoconfig) | undefined</code>

远端视频流参数


## RemoteVideoConfig <span id="remotevideoconfig"></span>

类型: `interface`

远端视频流参数

<p style="font-size: 16px;font-weight: bolder;"> width <span id="remotevideoconfig-width"></span></p> 

类型: <code>number</code>

视频宽度，单位：px

<p style="font-size: 16px;font-weight: bolder;"> height <span id="remotevideoconfig-height"></span></p> 

类型: <code>number</code>

视频宽度，单位：px


## ScreenConfig <span id="screenconfig"></span>

类型: `interface`

屏幕共享流设置

<p style="font-size: 16px;font-weight: bolder;"> enableAudio <span id="screenconfig-enableaudio"></span></p> 

类型: <code>boolean | undefined</code>

在共享屏幕时是否显示共享音频选项:
• Windows 支持在共享整个屏幕时共享系统音频；在共享 Chrome 标签页时共享 Tab 标签页面音频。
• macOS 仅支持在共享 Chrome 标签页时共享 Tab 标签页面音频。


## VideoPlayerOption <span id="videoplayeroption"></span>

类型: `interface`

播放器信息和渲染模式

<p style="font-size: 16px;font-weight: bolder;"> renderDom <span id="videoplayeroption-renderdom"></span></p> 

类型: <code>string | HTMLElement | undefined</code>

DOM

<p style="font-size: 16px;font-weight: bolder;"> renderMode <span id="videoplayeroption-rendermode"></span></p> 

类型: <code>[VideoRenderMode](#videorendermode) | undefined</code>

渲染模式。

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="videoplayeroption-userid"></span></p> 

类型: <code>string</code>

用户 ID，支持以下字符集范围

+ 26 个大写字母 A ~ Z
+ 26 个小写字母 a ~ z
+ 10 个数字 0 ~ 9
+ 下划线 "_"，at 符 "@"，减 号 "-"

<p style="font-size: 16px;font-weight: bolder;"> rotation <span id="videoplayeroption-rotation"></span></p> 

类型: <code>number | undefined</code>

视频帧顺时针的旋转角度。可选值为 0，90，180，270。默认值是 0，即不做旋转处理。<br>
该设置仅对远端视频有效，调用 [setLocalVideoPlayer](Web-api.md#setlocalvideoplayer) 设置本参数不生效。


## VideoRenderMode <span id="videorendermode"></span>

类型: `enum`

渲染模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | RENDER_MODE_HIDDEN | `0` | （主流默认值）视窗填满优先。<br>视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。 |
  | RENDER_MODE_FIT | `1` | （屏幕流默认值）视频帧内容全部显示优先。<br>视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上会出现未被填满的透明区域。 |
  | RENDER_MODE_FILL | `2` | 视窗填满并显示视频全部内容。<br>视频帧非等比缩放，拉伸至填满视窗区域。 |



## MirrorType <span id="mirrortype"></span>

类型: `enum`

本地渲染镜像类型。因浏览器限制，不支持编码传输镜像。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | MIRROR_TYPE_NONE | `0` | 本地渲染和编码传输时均无镜像效果 |
  | MIRROR_TYPE_RENDER | `1` | 本地渲染时有镜像效果，编码传输时无镜像效果 |



## VideoEncoderConfig <span id="videoencoderconfig"></span>

类型: `interface`

视频编码参数。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="videoencoderconfig-width"></span></p> 

类型: <code>ConstrainULong</code>

视频宽度，单位为像素。默认值为 640 px。
支持传入 `number` 或一个整形约束对象，参看 [ConstrainULong](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constrainulong)。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="videoencoderconfig-height"></span></p> 

类型: <code>ConstrainULong</code>

视频高度，单位为像素。默认值为 480 px。
支持传入 `number` 或一个整形约束对象，参看 [ConstrainULong](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constrainulong)。

<p style="font-size: 16px;font-weight: bolder;"> frameRate <span id="videoencoderconfig-framerate"></span></p> 

类型: <code>ConstrainDouble</code>

视频帧率，单位为 FPS。默认值为 15 FPS。
支持传入 `number` 或一个浮点形约束对象，参看 [ConstrainDouble](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constraindouble)。

<p style="font-size: 16px;font-weight: bolder;"> maxKbps <span id="videoencoderconfig-maxkbps"></span></p> 

类型: <code>number</code>

最大编码码率，RTC SDK 内部采集和自定义采集均需设定 > 0 的数值，单位为 Kbps。默认值为 600 Kbps。

<p style="font-size: 16px;font-weight: bolder;"> contentHint <span id="videoencoderconfig-contenthint"></span></p> 

类型: <code>"text" | "motion" | "detail" | undefined</code>

视频内容类型。
`'text'`：清晰度优先，适用于视频内容只包含大量文本的情况。
`'motion'`：流畅度优先，适用于视频内容为摄像头采集、电影、视频、游戏的情况。
`'detail'`：清晰度优先，适用于视频内容包含图片、文本混排的情况。

- **注意**

  Firefox 浏览器不支持设置此参数，参看 [contentHint 浏览器兼容信息](https://caniuse.com/?search=contentHint)。


## ScreenEncoderConfig <span id="screenencoderconfig"></span>

类型: `interface`

屏幕共享的视频编码参数。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="screenencoderconfig-width"></span></p> 

类型: <code>ConstrainULong</code>

视频宽度，单位为像素。默认值为 1920 px。
支持传入 `number` 或一个整形约束对象，参看 [ConstrainULong](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constrainulong)。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="screenencoderconfig-height"></span></p> 

类型: <code>ConstrainULong</code>

视频高度，单位为像素。默认值为 1080 px。
支持传入 `number` 或一个整形约束对象，参看 [ConstrainULong](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constrainulong)。

<p style="font-size: 16px;font-weight: bolder;"> frameRate <span id="screenencoderconfig-framerate"></span></p> 

类型: <code>ConstrainDouble</code>

视频帧率，默认值为 15 FPS。
支持传入 `number` 或一个浮点形约束对象，参看 [ConstrainDouble](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constraindouble)。

<p style="font-size: 16px;font-weight: bolder;"> maxKbps <span id="screenencoderconfig-maxkbps"></span></p> 

类型: <code>number</code>

最大编码码率，RTC SDK 内部采集和自定义采集均需设定 > 0 的数值，单位为 Kbps。默认值为 3000 Kbps。

<p style="font-size: 16px;font-weight: bolder;"> contentHint <span id="screenencoderconfig-contenthint"></span></p> 

类型: <code>"text" | "motion" | "detail" | undefined</code>

视频内容类型。
`'text'`：清晰度优先，适用于视频内容只包含大量文本的情况。
`'motion'`：流畅度优先，适用于视频内容为摄像头采集、电影、视频、游戏的情况。
`'detail'`：清晰度优先，适用于视频内容包含图片、文本混排的情况。

- **注意**

  Firefox 浏览器不支持设置此参数，参看 [contentHint 浏览器兼容信息](https://caniuse.com/?search=contentHint)。


## AudioPropertiesConfig <span id="audiopropertiesconfig"></span>

类型: `interface`

音频信息提示的相关配置

<p style="font-size: 16px;font-weight: bolder;"> interval <span id="audiopropertiesconfig-interval"></span></p> 

类型: <code>number | undefined</code>

信息提示间隔，单位：ms，默认为 100ms </br>

   + `≤0`: 关闭信息提示
   + `(0,100)`: 不合法的interval 值，SDK 自动设置为 100ms
   + `≥100`: 开启信息提示，并将信息提示间隔设置为此值

<p style="font-size: 16px;font-weight: bolder;"> enableInBackground <span id="audiopropertiesconfig-enableinbackground"></span></p> 

类型: <code>boolean | undefined</code>

是否在页面隐藏时保持开启获取音量回调，默认保持开启。

+ true: 保持开启
+ false：关闭

<p style="font-size: 16px;font-weight: bolder;"> localMainReportMode <span id="audiopropertiesconfig-localmainreportmode"></span></p> 

类型: <code>[LocalMainReportMode](#localmainreportmode) | undefined</code>

本地主流音量回调模式。

<p style="font-size: 16px;font-weight: bolder;"> audioReportMode <span id="audiopropertiesconfig-audioreportmode"></span></p> 

类型: <code>[AudioReportMode](#audioreportmode) | undefined</code>

本地主流音量回调的数据范围，控制回调中是否包含混音。


## LocalMainReportMode <span id="localmainreportmode"></span>

类型: `enum`

本地主流音量回调模式。
该功能影响 [onActiveSpeaker](Web-event.md#onactivespeaker) 回调。例如，进入房间但未发布主流音频，[LocalMainReportMode](#localmainreportmode) 为 `RESET`，则该回调永远不会包含本端用户主流音频。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | NORMAL | `0` | （默认值）本地主流存在时，始终开启音量回调。 |
  | DISCONNECT | `1` | 未发布时，不回调对应音量。发布时回调真实音量。 |
  | RESET | `2` | 未发布时，始终回调 0。发布时正常回调真实音量。 |



## AudioReportMode <span id="audioreportmode"></span>

类型: `enum`

本地主流音量回调的数据范围，控制回调中是否包含混音。
该功能影响 [onActiveSpeaker](Web-event.md#onactivespeaker) 回调。例如，[AudioReportMode](#audioreportmode) 为 `AUDIOMIXING`，即使麦克风音量为 0，该回调中也可能回调本端用户主流音频。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | MICROPHONE | `0` | （默认值）麦克风音量，即混音前的音量。 |
  | AUDIOMIXING | `1` | 混音后的音量。 |



## LiveTranscodeConfig <span id="livetranscodeconfig"></span>

类型: `interface`

转码推流配置参数。

<p style="font-size: 16px;font-weight: bolder;"> url <span id="livetranscodeconfig-url"></span></p> 

类型: <code>string</code>

推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。
本参数不支持过程中更新。

<p style="font-size: 16px;font-weight: bolder;"> audio <span id="livetranscodeconfig-audio"></span></p> 

类型: <code>Partial<[LiveTranscodeAudioConfig](#livetranscodeaudioconfig)\> | undefined</code>

音频转码配置参数。
本参数不支持过程中更新。

<p style="font-size: 16px;font-weight: bolder;"> video <span id="livetranscodeconfig-video"></span></p> 

类型: <code>Partial<[LiveTranscodeVideoConfig](#livetranscodevideoconfig)\> | undefined</code>

视频转码配置参数。

<p style="font-size: 16px;font-weight: bolder;"> layout <span id="livetranscodeconfig-layout"></span></p> 

类型: <code>Partial<[LiveTranscodeLayoutConfig](#livetranscodelayoutconfig)\> | undefined</code>

用户布局信息。


## LiveTranscodeAudioConfig <span id="livetranscodeaudioconfig"></span>

类型: `interface`

音频转码配置参数。值不合法或未设置时，自动使用默认值。

<p style="font-size: 16px;font-weight: bolder;"> codec <span id="livetranscodeaudioconfig-codec"></span></p> 

类型: <code>"AAC" | undefined</code>

音频编码格式，选填，默认为 `AAC`。

<p style="font-size: 16px;font-weight: bolder;"> kBitRate <span id="livetranscodeaudioconfig-kbitrate"></span></p> 

类型: <code>number</code>

音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。

<p style="font-size: 16px;font-weight: bolder;"> sampleRate <span id="livetranscodeaudioconfig-samplerate"></span></p> 

类型: <code>number</code>

音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。

<p style="font-size: 16px;font-weight: bolder;"> channels <span id="livetranscodeaudioconfig-channels"></span></p> 

类型: <code>number</code>

音频声道数。可取 1（单声道）、2（双声道），默认值为 2。

<p style="font-size: 16px;font-weight: bolder;"> AACProfile <span id="livetranscodeaudioconfig-aacprofile"></span></p> 

类型: <code>[AAC_PROFILE](#aac_profile)</code>

<span id="aac_profile"></span>
AAC 编码规格。默认值为 `LC`。


## AAC_PROFILE <span id="aac_profile"></span>

类型: `enum`

AAC 编码规格。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | LC | `'LC'` | AAC-LC 规格，默认值。 |
  | HEv1 | `'HEv1'` | HE-AAC v1 规格。 |
  | HEv2 | `'HEv2'` | HE-AAC v2 规格。 |



## LiveTranscodeVideoConfig <span id="livetranscodevideoconfig"></span>

类型: `interface`

视频转码配置参数。值不合法或未设置时，自动使用默认值。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="livetranscodevideoconfig-width"></span></p> 

类型: <code>number</code>

合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。
设置值为非偶数时，自动向上取偶数。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="livetranscodevideoconfig-height"></span></p> 

类型: <code>number</code>

合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。
设置值为非偶数时，自动向上取偶数。

<p style="font-size: 16px;font-weight: bolder;"> codec <span id="livetranscodevideoconfig-codec"></span></p> 

类型: <code>[TRANSCODING_VIDEO_CODEC](#transcoding_video_codec)</code>

视频编码格式。默认值为 `H264`。
本参数不支持过程中更新。

<p style="font-size: 16px;font-weight: bolder;"> fps <span id="livetranscodevideoconfig-fps"></span></p> 

类型: <code>number</code>

合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。

<p style="font-size: 16px;font-weight: bolder;"> gop <span id="livetranscodevideoconfig-gop"></span></p> 

类型: <code>number</code>

视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。
本参数不支持过程中更新。


## TRANSCODING_VIDEO_CODEC <span id="transcoding_video_codec"></span>

类型: `enum`

<span id="transcoding_video_codec"></span>
视频编码格式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | H264 | `'H264'` | H.264 格式，默认值。 |
  | H265 | `'H265'` | ByteVC1 格式。 |



## LiveTranscodeLayoutConfig <span id="livetranscodelayoutconfig"></span>

类型: `interface`

视频流合流整体布局信息。
开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。

<p style="font-size: 16px;font-weight: bolder;"> regions <span id="livetranscodelayoutconfig-regions"></span></p> 

类型: <code>[LiveTranscodeLayoutRegion](#livetranscodelayoutregion)[]</code>

用户布局信息列表。值不合法或未设置时，自动使用默认值。

<p style="font-size: 16px;font-weight: bolder;"> appData <span id="livetranscodelayoutconfig-appdata"></span></p> 

类型: <code>string</code>

透传的 App 数据，长度不超过 4 KB。

<p style="font-size: 16px;font-weight: bolder;"> backgroundColor <span id="livetranscodelayoutconfig-backgroundcolor"></span></p> 

类型: <code>string</code>

合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。
值不合法或未设置时，自动使用默认值。


## LiveTranscodeLayoutRegion <span id="livetranscodelayoutregion"></span>

类型: `interface`

单个视频流在合流中的布局信息。

<p style="font-size: 16px;font-weight: bolder;"> alpha <span id="livetranscodelayoutregion-alpha"></span></p> 

类型: <code>number | undefined</code>

透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。

<p style="font-size: 16px;font-weight: bolder;"> userId <span id="livetranscodelayoutregion-userid"></span></p> 

类型: <code>string</code>

视频流发布用户的用户 ID

<p style="font-size: 16px;font-weight: bolder;"> x <span id="livetranscodelayoutregion-x"></span></p> 

类型: <code>number | undefined</code>

视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。

<p style="font-size: 16px;font-weight: bolder;"> y <span id="livetranscodelayoutregion-y"></span></p> 

类型: <code>number | undefined</code>

视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。

<p style="font-size: 16px;font-weight: bolder;"> zorder <span id="livetranscodelayoutregion-zorder"></span></p> 

类型: <code>number | undefined</code>

用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。

<p style="font-size: 16px;font-weight: bolder;"> w <span id="livetranscodelayoutregion-w"></span></p> 

类型: <code>number | undefined</code>

视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。默认值为 1.0。

<p style="font-size: 16px;font-weight: bolder;"> h <span id="livetranscodelayoutregion-h"></span></p> 

类型: <code>number | undefined</code>

视频流对应区域高度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。默认值为 1.0。

<p style="font-size: 16px;font-weight: bolder;"> renderMode <span id="livetranscodelayoutregion-rendermode"></span></p> 

类型: <code>number | undefined</code>

图片或视频流的缩放模式，默认值为 1。可选取值如下：
• 1: 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
• 2: 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。
• 3: 视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。

<p style="font-size: 16px;font-weight: bolder;"> contentControl <span id="livetranscodelayoutregion-contentcontrol"></span></p> 

类型: <code>number | undefined</code>

合流内容控制。默认值为 0，可选取值如下：
• 0: 输出的混流包含音视频。
• 1: 只包含音频。
• 2: 只包含视频。

<p style="font-size: 16px;font-weight: bolder;"> isScreenStream <span id="livetranscodelayoutregion-isscreenstream"></span></p> 

类型: <code>boolean</code>

是否是屏幕流


## VideoSourceType <span id="videosourcetype"></span>

类型: `enum`

视频采集方式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | VIDEO_SOURCE_TYPE_EXTERNAL | `0` | 自定义采集 |
  | VIDEO_SOURCE_TYPE_INTERNAL | `1` | 内部采集，使用由 SDK 提供的视频采集模块（默认） |



## AudioSourceType <span id="audiosourcetype"></span>

类型: `enum`

音频采集方式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | AUDIO_SOURCE_TYPE_EXTERNAL | `0` | 自定义采集模块 |
  | AUDIO_SOURCE_TYPE_INTERNAL | `1` | 内部采集，使用由 SDK 提供的音频采集模块 |



## TrackCaptureConfig <span id="trackcaptureconfig"></span>

内部采集的媒体属性，详见[浏览器文档](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints)

- **类型**

  ```ts
  Omit<MediaTrackConstraints, 'deviceId'>
  ```


## USER_ONLINE_STATUS <span id="user_online_status"></span>

类型: `enum`

<span id="user_online_status"></span>
登录状态

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | OFFLINE | `0` | 离线。无法收发点对点消息。 |
  | ONLINE | `1` | 在线 |
  | UNREACHABLE | `2` | 未知。无法收发点对点消息。 |



## CloudProxyInfo <span id="cloudproxyinfo"></span>

类型: `interface`

云代理服务器信息

<p style="font-size: 16px;font-weight: bolder;"> logProxy <span id="cloudproxyinfo-logproxy"></span></p> 

类型: <code>string</code>

埋点日志上报的的代理地址

<p style="font-size: 16px;font-weight: bolder;"> accessProxy <span id="cloudproxyinfo-accessproxy"></span></p> 

类型: <code>string</code>

统一接入的代理地址

<p style="font-size: 16px;font-weight: bolder;"> configProxy <span id="cloudproxyinfo-configproxy"></span></p> 

类型: <code>string</code>

RTC 配置下发的代理地址


## PublicStreamConfig <span id="publicstreamconfig"></span>

类型: `interface`

公共流配置信息

<p style="font-size: 16px;font-weight: bolder;"> video <span id="publicstreamconfig-video"></span></p> 

类型: <code>{ width?: number | undefined; height?: number | undefined; fps?: number | undefined; kBitRate: number; } | undefined</code>

视频参数

 - **成员**

    | 名称 | 类型 | 描述 |
    | :-- | :-- | :-- |
    | width | `number | undefined` | 宽度，单位：px。<br>仅支持设为偶数，如果设为奇数，将导致公共流发布失败。 |
    | height | `number | undefined` | 高度，单位：px。<br>仅支持设为偶数，如果设为奇数，云端媒体处理会直接拒绝，导致公共流失败。 |
    | fps | `number | undefined` | 帧率，单位：fps |
    | kBitRate | `number` | 码率，单位：kbps |


<p style="font-size: 16px;font-weight: bolder;"> layout <span id="publicstreamconfig-layout"></span></p> 

类型: <code>{ interpolationMode?: [PublicInterpolationMode](#publicinterpolationmode) | undefined; backgroundColor?: string | undefined; backgroundImage?: string | undefined; regions?: [PublicStreamLayoutRegion](#publicstreamlayoutregion)[] | undefined; } | undefined</code>

公共流的布局模式

 - **成员**

    | 名称 | 类型 | 描述 |
    | :-- | :-- | :-- |
    | interpolationMode | `PublicInterpolationMode | undefined` | 补帧模式 |
    | backgroundColor | `string | undefined` | 背景颜色，用 Hex 色值表示。 |
    | backgroundImage | `string | undefined` | 背景图片的 URL。长度最大为 1024 byte。可以传入的图片的格式包括：JPG, JPEG, PNG。 |
    | regions | `PublicStreamLayoutRegion[] | undefined` | 多路媒体流布局设置。 |



## PublicInterpolationMode <span id="publicinterpolationmode"></span>

类型: `enum`

补帧模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | PREV_FRAME | `0` | 补最后一帧。 |
  | OTHER_FRAME | `1` | 补背景图片或者黑帧。 |



## PublicStreamLayoutRegion <span id="publicstreamlayoutregion"></span>

多路媒体流中一路流的布局设置。

- **类型**

  ```ts
  Omit<LiveTranscodeLayoutRegion, 'isLocalUser' | 'contentControl'> & {
    roomId: string;
    mediaType?: PublicStreamType;
    sourceCrop?: {
      x: number;
      y: number;
      w: number;
      h: number;
    };
  }
  ```

- **成员**

  | 名称 | 类型 | 描述 |
  | :-- | :-- | :-- |
  | roomId | <code>string</code> | 媒体流发布用户的房间 ID |
  | mediaType | <code>[PublicStreamType](#publicstreamtype) \| undefined</code> | 公共流输出内容类型 |
  | sourceCrop | <code>{ x: number; y: number; w: number; h: number; } \| undefined</code> | 公共流视频裁剪配置 |
  | x | <code>number</code> | 裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)。 |
  | y | <code>number</code> | 裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)。 |
  | w | <code>number</code> | 裁剪后得到的视频帧宽度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]。 |
  | h | <code>number</code> | 裁剪后得到的视频帧高度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]。 |



## PublicStreamType <span id="publicstreamtype"></span>

类型: `enum`

公共流输出内容类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | AUDIO_AND_VIDEO | `0` | 包含音视频 |
  | AUDIO_ONLY | `1` | 仅包含音频 |
  | VIDEO_ONLY | `2` | 仅包含视频 |



## SubscribeFallbackOption <span id="subscribefallbackoption"></span>

类型: `enum`

订阅端音视频流回退选项。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | DISABLE | `0` | 不开启回退功能。默认设置。 |
  | VIDEO_STREAM_LOW | `1` | 下行网络不佳时，对视频流做降级处理。具体降级规则参看[音视频流回退](https://www.volcengine.com/docs/6348/70137)文档。<br>该设置仅对发布端调用 [EnableSimulcastMode](Web-api.md#enablesimulcastmode) 开启发送多路流功能的情况生效。 |
  | AUDIO_ONLY | `2` | 下行网络不佳时，取消接收视频，仅接收音频。<br>当发布端开启发送多路流功能时，设置此选项不利于提升用户体验，因此不建议设置此选项。 |



## RemoteUserPriority <span id="remoteuserpriority"></span>

类型: `enum`

远端用户优先级

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | LOW | `0` | 用户优先级为低（默认值） |
  | MEDIUM | `100` | 用户优先级为正常 |
  | HIGH | `200` | 用户优先级为高 |



## AudioProfileType <span id="audioprofiletype"></span>

类型: `enum`

音质档位
调用 [setAudioProfile](Web-api.md#setaudioprofile) 设置的音质档位

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | default | `0` | 默认音质<br>服务器下发的音质配置 |
  | fluent | `1` | 流畅音质。<br>单声道，采样率为 16kHz，编码码率为 24kbps。<br>流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。 |
  | standard | `2` | 单声道标准音质。<br>采样率为 48kHz，编码码率为 48kbps。<br>适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和狼人杀等游戏。 |
  | hd | `3` | 双声道音乐音质<br>采样率为 48kHz，编码码率为 128kbps。<br>超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。<br>游戏场景不建议使用。 |
  | standardStereo | `4` | 双声道标准音质。采样率为 48 KHz，编码码率最大值为 80 Kbps |
  | hdMono | `5` | 单声道音乐音质。采样率为 48 kHz，编码码率最大值为 128 Kbps |



## RTCSubtitleConfig <span id="rtcsubtitleconfig"></span>

类型: `interface`

字幕配置信息。

<p style="font-size: 16px;font-weight: bolder;"> targetLanguage <span id="rtcsubtitleconfig-targetlanguage"></span></p> 

类型: <code>string | undefined</code>

目标语言语种代号，参看[语言支持信息](https://www.volcengine.com/docs/4640/35107)。

<p style="font-size: 16px;font-weight: bolder;"> mode <span id="rtcsubtitleconfig-mode"></span></p> 

类型: <code>[SUBTITLE_MODE](#subtitle_mode)</code>

字幕模式。


## ForwardStreamInfo <span id="forwardstreaminfo"></span>

类型: `interface`

跨房间转发媒体流信息。

<p style="font-size: 16px;font-weight: bolder;"> roomId <span id="forwardstreaminfo-roomid"></span></p> 

类型: <code>string</code>

跨房间转发媒体流的目标房间 ID。

<p style="font-size: 16px;font-weight: bolder;"> token <span id="forwardstreaminfo-token"></span></p> 

类型: <code>string</code>

使用目标房间 roomId 和 userId 生成的 Token。
测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成的临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。


## EngineConfig <span id="engineconfig"></span>

类型: `interface`

引擎级别配置项

<p style="font-size: 16px;font-weight: bolder;"> autoPlayPolicy <span id="engineconfig-autoplaypolicy"></span></p> 

类型: <code>[RTCAutoPlayPolicy](#rtcautoplaypolicy) | undefined</code>

自动播放策略


## RTCAutoPlayPolicy <span id="rtcautoplaypolicy"></span>

类型: `enum`

自动播放策略。参考[自动播放策略](https://www.volcengine.com/docs/6348/130302)，获取更多相关信息。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | AUTO_PLAY | `0` | 默认值，自动播放音频和视频 |
  | VIDEO_ONLY | `1` | 自动播放视频，不自动播放音频 |
  | PLAY_MANUALLY | `2` | 不自动播放，引导用户通过交互，手动播放 |