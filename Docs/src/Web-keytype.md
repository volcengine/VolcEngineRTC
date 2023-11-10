## MixOption

类型: `interface`

混音配置

### playCount

类型: <code>number</code>

混音播放次数

- **注意**

  + play_count <= 0: 无限循环
  + play_count == 1: 播放一次（默认）
  + play_count > 1: 播放 play_count 次

### type

类型: <code>[AudioMixingType](#audiomixingtype) | undefined</code>

混音播放类型


## AudioMixingType

类型: `enum`

混音播放类型

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | PLAYOUT | `0` | 仅本地播放 |
  | PUBLISH | `1` | 仅发送到远端 |
  | PLAYOUT_AND_PUBLISH | `2` | 在本地播放并发送到远端 |



## PlayerEvent

类型: `interface`

播放器事件

### type

类型: <code>"video" | "audio"</code>

类型

### eventName

类型: <code>string</code>

事件名称

### rawEvent

类型: <code>Event</code>

播放事件。详见[官方文档](https://developer.mozilla.org/en-US/docs/Web/API/HTMLMediaElement/play_event)

### userId

类型: <code>string</code>

进房用户的 userId

### publicStreamId

类型: <code>string | undefined</code>

公共流 ID。

### readyState

类型: <code>number</code>

媒体就绪状态，详见[官方文档](https://developer.mozilla.org/en-US/docs/Web/API/HTMLMediaElement/readyState)

### currentTime

类型: <code>number</code>

当前时间

### isScreen

类型: <code>boolean | undefined</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## onUserJoinedEvent

类型: `interface`

远端用户进房事件

### userInfo

类型: <code>[UserInfo](#userinfo)</code>

进房用户的 userId


## UserInfo

类型: `interface`

用户信息。

### userId

类型: <code>string</code>

用户 ID，长度在 128 字节以内的非空字符串。

### extraInfo

类型: <code>string | undefined</code>

用户传递的额外信息，最大长度为 200 字节。会在 [onUserJoined](Web-event.md#onuserjoined) 中回调给远端用户。

- **注意**

  支持以下字符集范围:

  + 26 个大写字母: A ~ Z
  + 26 个小写字母: a ~ z
  + 10 个数字: 0 ~ 9
  + 特殊字符: 下划线 "_"，at 符 "@"，减号 "-"


## onUserLeaveEvent

类型: `interface`

远端用户退房事件

### userInfo

类型: <code>[UserInfo](#userinfo)</code>

用户信息

### reason

类型: <code>[UserOfflineReason](#userofflinereason)</code>

远端用户离开房间的原因


## UserOfflineReason

类型: `enum`

远端用户离开房间的原因

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | QUIT | `0` | 远端用户调用 `leaveRoom` 主动退出房间。 |
  | DROPPED | `1` | 远端用户因 Token 过期或网络原因等掉线。 |
  | SWITCH_TO_INVISIBLE | `2` | 远端用户调用 `setUserVisibility` 切换至不可见状态。 |
  | KICKED_BY_ADMIN | `3` | 服务端调用 OpenAPI 将远端用户踢出房间。 |



## ConnectionStateChangeEvent

类型: `interface`

连接状态改变

### state

类型: <code>[ConnectionState](#connectionstate)</code>

内部连接状态


## ConnectionState

类型: `enum`

SDK 与信令服务器连接状态。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | CONNECTION_START | `0` | 进行连接前准备，锁定相关资源。 |
  | CONNECTION_STATE_DISCONNECTED | `1` | 连接断开。 |
  | CONNECTION_STATE_CONNECTING | `2` | 首次连接，正在连接中。 |
  | CONNECTION_STATE_CONNECTED | `3` | 首次连接成功。 |
  | CONNECTION_STATE_RECONNECTING | `4` | 连接断开后重新连接中。 |
  | CONNECTION_STATE_RECONNECTED | `5` | 连接断开后重连成功。 |
  | CONNECTION_STATE_LOST | `6` | 处于 `CONNECTION_STATE_DISCONNECTED` 状态超过 10 秒，且期间重连未成功。SDK将继续尝试重连。 |



## MediaType

类型: `enum`

媒体流类型

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | AUDIO | `1` | 只控制音频 |
  | VIDEO | `2` | 只控制视频 |
  | AUDIO_AND_VIDEO | `3` | 同时控制音频和视频 |



## StreamRemoveReason

类型: `enum`

房间内远端流移除原因。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | STREAM_REMOVE_REASON_UNPUBLISH | `0` | 远端用户停止发布流。 |
  | STREAM_REMOVE_REASON_PUBLISH_FAILED | `1` | 远端用户发布流失败。 |
  | STREAM_REMOVE_REASON_KEEP_LIVE_FAILED | `2` | 保活失败。 |
  | STREAM_REMOVE_REASON_CLIENT_DISCONNECTED | `3` | 远端用户断网。 |
  | STREAM_REMOVE_REASON_REPUBLISH | `4` | 远端用户重新发布流。 |
  | STREAM_REMOVE_REASON_OTHER | `5` | 其他原因。 |



## onVideoFirstFrameRenderedEvent

类型: `interface`

第一帧远端视频显示在视图上

### userId

类型: <code>string</code>

发布视频用户的 userId

### height

类型: <code>number</code>

高度

### width

类型: <code>number</code>

宽度

### isScreen

类型: <code>boolean</code>

是否为屏幕流


## onAudioFirstFrameDecodedEvent

类型: `interface`

第一帧远端音频解码事件

### userId

类型: <code>string</code>

发布视频用户的 userId

### isScreen

类型: <code>boolean</code>

是否为屏幕共享流


## DeviceInfo

类型: `interface`

媒体设备信息及状态。

### mediaDeviceInfo

类型: <code>MediaDeviceInfo</code>

媒体设备信息，参看 [MediaDeviceInfo](https://developer.mozilla.org/en-US/docs/Web/API/MediaDeviceInfo)。

### deviceState

类型: <code>"active" | "inactive"</code>

设备状态。
active：设备已连接。
inactive：设备已断开连接。


## AutoPlayFailedEvent

类型: `interface`

自动播放失败事件

### userId

类型: <code>string</code>

自动播放失败的流所属的用户 ID。不带此参数时表示本地流播放失败。

### kind

类型: <code>"video" | "audio"</code>

自动播放失败的媒体类型
例如，当同一用户的视频流和音频流自动播放都失败时，将触发两次 `onAutoPlayFailed` 回调，分别包含 `audio` 和 `video` 参数。

### streamIndex

类型: <code>[StreamIndex](#streamindex)</code>

视频流属性。

### mediaType

类型: <code>MediaType.AUDIO | MediaType.VIDEO</code>

远端媒体流的类型


## StreamIndex

类型: `enum`

流属性

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | STREAM_INDEX_MAIN | `0` | 主流。包括：通过默认摄像头/麦克风采集到的视频/音频; |
  | STREAM_INDEX_SCREEN | `1` | 屏幕流。共享的视频流，或来自声卡的本地播放音频流。 |



## UserMessageEvent

类型: `interface`

点对点文本消息

### userId

类型: <code>string</code>

发送消息的用户

### message

类型: <code>string</code>

点对点文本消息


## UserBinaryMessageEvent

类型: `interface`

点对点二进制消息

### userId

类型: <code>string</code>

发送消息的用户

### message

类型: <code>ArrayBuffer</code>

点对点二进制消息


## RemoteStreamStats

类型: `interface`

远端媒体流统计信息，统计周期为 2s 。
本地用户订阅媒体流成功后，SDK 会周期性地通知远端的媒体流在此次统计周期内的接收状况。此数据结构为回调给用户的参数类型。

### userId

类型: <code>string</code>

进房用户的 userId

### audioStats

类型: <code>[RemoteAudioStats](#remoteaudiostats)</code>

远端音频流信息

### videoStats

类型: <code>[RemoteVideoStats](#remotevideostats)</code>

远端视频流信息

### isScreen

类型: <code>boolean</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## RemoteAudioStats

类型: `interface`

远端音频流统计信息，统计周期为 2s 。
本地用户订阅音频流成功后，SDK 会周期性地通知远端的音频流在此次统计周期内的接收状况。此数据结构为回调给用户的参数类型。

### audioLossRate

类型: <code>number</code>

音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。

### receivedKBitrate

类型: <code>number</code>

接收码率。统计周期内的音频接收码率，单位为 kbps 。

### stallCount

类型: <code>number | undefined</code>

统计周期内的卡顿次数

### stallDuration

类型: <code>number | undefined</code>

统计周期内的卡顿时长，单位为 ms 。

### statsInterval

类型: <code>number</code>

统计间隔。此次统计周期的间隔，单位为 ms 。

### rtt

类型: <code>number</code>

往返时延，单位：ms

### jitterBufferDelay

类型: <code>number</code>

抖动延迟，单位：ms

### numChannels

类型: <code>number</code>

声道数

### receivedSampleRate

类型: <code>number</code>

接收侧采样率

### concealedSamples

类型: <code>number</code>

音频丢包补偿(PLC) 样点总个数

### concealmentEvent

类型: <code>number</code>

音频丢包补偿(PLC) 累计次数


## RemoteVideoStats

类型: `interface`

远端视频流统计信息，统计周期为 2s 。
本地用户订阅视频流成功后，SDK 会周期性地通知远端的视频流在此次统计周期内的接收状况。此数据结构为回调给用户的参数类型。

### width

类型: <code>number</code>

宽度，单位：px

### height

类型: <code>number</code>

高度，单位：px

### videoLossRate

类型: <code>number</code>

视频丢包率。统计周期内的视频下行丢包率，取值范围为 [0, 1] 。

### receivedKBitrate

类型: <code>number</code>

接收码率。统计周期内的音频接收码率，单位为 kbps 。

### decoderOutputFrameRate

类型: <code>number</code>

解码器输出帧率。统计周期内的视频解码器输出帧率，单位 fps 。

### stallCount

类型: <code>number | undefined</code>

统计周期内的卡顿次数

### stallDuration

类型: <code>number | undefined</code>

统计周期内的卡顿时长，单位为 ms 。

### isScreen

类型: <code>boolean</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。

### statsInterval

类型: <code>number</code>

统计间隔。此次统计周期的间隔，单位为 ms 。

### rtt

类型: <code>number</code>

客户端到服务端数据传输的往返时延，单位：ms


## LocalStreamStats

类型: `interface`

本地媒体流统计信息以及网络状况，统计周期为 2s 。
本地用户发布媒体流成功后，SDK 会周期性地通知本地用户发布的媒体流在此次统计周期内的发送状况。此数据结构为回调给用户的参数类型。

### audioStats

类型: <code>[LocalAudioStats](#localaudiostats)</code>

本地发送音频流的统计信息。

### videoStats

类型: <code>[LocalVideoStats](#localvideostats)</code>

本地发送视频流的统计信息。

### isScreen

类型: <code>boolean</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## LocalAudioStats

类型: `interface`

本地音频流统计信息以及网络状况，统计周期为 2s 。
本地用户发布音频流成功后，SDK 会周期性地通知本地用户发布的音频流在此次统计周期内的发送状况。此数据结构为回调给用户的参数类型。

### audioLossRate

类型: <code>number</code>

音频丢包率。统计周期内的音频上行丢包率，取值范围为 [0, 1] 。

### sendKBitrate

类型: <code>number</code>

发送码率。统计周期内的音频接收码率，单位为 kbps 。

### recordSampleRate

类型: <code>number</code>

采集采样率。统计周期内的音频采集采样率信息，单位为 Hz 。

### statsInterval

类型: <code>number</code>

统计间隔。此次统计周期的间隔，单位为 ms 。

### rtt

类型: <code>number</code>

客户端到服务端数据传输的往返时延，单位：ms

### numChannels

类型: <code>number</code>

声道数


## LocalVideoStats

类型: `interface`

本地视频流统计信息以及网络状况，统计周期为 2s 。
本地用户发布视频流成功后，SDK 会周期性地通知本地用户发布的视频流在此次统计周期内的发送状况。此数据结构为回调给用户的参数类型。

### sentKBitrate

类型: <code>number</code>

发送码率，单位：kbps。统计周期内的视频发送码率

### sentFrameRate

类型: <code>number</code>

发送帧率。统计周期内的视频发送帧率，单位为 fps 。

### encoderOutputFrameRate

类型: <code>number</code>

编码器输出帧率。当前编码器在此次统计周期内的输出帧率，单位为 fps 。

### rendererOutputFrameRate

类型: <code>number | undefined</code>

本地渲染帧率。统计周期内的本地视频渲染帧率，单位为 fps 。

### statsInterval

类型: <code>number</code>

统计间隔。此次统计周期的间隔，单位为 ms 。

### videoLossRate

类型: <code>number</code>

视频丢包率。统计周期内的视频上行丢包率，取值范围为 [0, 1] 。

### rtt

类型: <code>number</code>

客户端到服务端数据传输的往返时延，单位：ms

### encodedFrameWidth

类型: <code>number</code>

视频编码宽度，单位为 px。

### encodedFrameHeight

类型: <code>number</code>

视频编码高度，单位为 px。

### encodedFrameCount

类型: <code>number</code>

统计周期内发送的视频帧总数

### codecType

类型: <code>string</code>

视频编码格式。
"H264": H.264 格式。
"VP8": VP8 格式。

### isScreen

类型: <code>boolean</code>

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## PublicStreamStats

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
  | -- | -- | -- |
  | publicStreamId | <code>string</code> | 公共流 ID。 |
  | RemoteStreamStats | <code>[RemoteStreamStats](#remotestreamstats)</code> | 远端媒体流统计信息 |



## LocalAudioPropertiesInfo

类型: `interface`

本地音频信息

### streamIndex

类型: <code>[StreamIndex](#streamindex)</code>

流属性，标记该流为麦克风采集音频流或屏幕音频流。

### audioPropertiesInfo

类型: <code>[AudioPropertiesInfo](#audiopropertiesinfo)</code>

音频属性信息。


## AudioPropertiesInfo

类型: `interface`

音频属性信息

### linearVolume

类型: <code>number</code>

线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。<br>

- [0, 25]: 无声 <br>
- [26, 75]: 低音量 <br>
- [76, 204]: 中音量 <br>
- [205, 255]: 高音量 <br>

### nonlinearVolume

类型: <code>number</code>

非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。 <br>

- [-127, -60]: 无声 <br>
- [-59, -40]: 低音量 <br>
- [-39, -20]: 中音量 <br>
- [-19, 0]: 高音量 <br>


## RemoteAudioPropertiesInfo

类型: `interface`

远端音频信息

### streamKey

类型: <code>[StreamKey](#streamkey)</code>

远端流信息

### audioPropertiesInfo

类型: <code>[AudioPropertiesInfo](#audiopropertiesinfo)</code>

远端音频属性信息


## StreamKey

类型: `interface`

远端流信息

### roomId

类型: <code>string</code>

房间 ID

### userId

类型: <code>string</code>

用户 ID

### streamIndex

类型: <code>[StreamIndex](#streamindex)</code>

流属性，标记该流为麦克风采集音频流或屏幕音频流。


## onSEIMessageEvent

类型: `interface`

收到带有 SEI 消息的视频帧时，收到此回调

### remoteStreamKey

类型: <code>[RemoteStreamKey](#remotestreamkey)</code>

包含 SEI 发送者的用户名，所在的房间名和媒体流

### sei

类型: <code>Uint8Array</code>

收到的 SEI 消息内容


## RemoteStreamKey

类型: `interface`

远端流信息

### roomId

类型: <code>string</code>

房间 ID

### userId

类型: <code>string</code>

用户 ID

### streamIndex

类型: <code>[StreamIndex](#streamindex)</code>

流属性，包括主流、屏幕流。


## SubscribeState

类型: `enum`

音视频流订阅结果

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | SUBSCRIBE_SUCC | `0` | 更新订阅状态成功 |
  | SUBSCRIBE_FAIL | `1` | 更新订阅状态失败 |



## PublishState

类型: `enum`

音视频流发布结果

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | PUBLISH_SUCC | `0` | 发布成功 |
  | PUBLISH_FAIL | `1` | 发布失败 |



## AudioMixingStateChangedEvent

类型: `interface`

音频混音文件播放状态改变事件

### mixId

类型: <code>number</code>

混音 ID

### state

类型: <code>[AudioMixingState](#audiomixingstate)</code>

混音状态

### error

类型: <code>[AudioMixingError](Web-errorcode.md#audiomixingerror)</code>

混音错误


## AudioMixingState

类型: `enum`

音频混音文件播放状态。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | AUDIO_MIXING_STATE_PRELOADED | `0` | 混音已加载 |
  | AUDIO_MIXING_STATE_PLAYING | `1` | 混音正在播放 |
  | AUDIO_MIXING_STATE_PAUSED | `2` | 混音暂停 |
  | AUDIO_MIXING_STATE_STOPPED | `3` | 混音停止 |
  | AUDIO_MIXING_STATE_FAILED | `4` | 混音播放失败 |
  | AUDIO_MIXING_STATE_FINISHED | `5` | 混音播放结束 |
  | AUDIO_MIXING_STATE_PCM_ENABLED | `6` | 准备 PCM 混音 |
  | AUDIO_MIXING_STATE_PCM_DISABLED | `7` | PCM 混音播放结束 |



## CloudProxyConnectedEvent

类型: `interface`

SDK 成功连接云代理服务器事件。

### interval

类型: <code>number</code>

SDK 开启云代理后，加入频道的耗时。


## PublicStreamResultEvent

类型: `interface`

公共流发布结果

### code

类型: <code>number</code>

公共流发布事件编号

### message

类型: <code>string</code>

公共流发布事件详情

+ `200`: 发布或订阅成功
+ `1191`: 公共流的参数异常，请修改参数后重试
+ `1192`: 服务端状态异常，将自动重试
+ `1193`: 内部错误，不可恢复，请重试
+ `1195`: 推流失败，将自动重试，用户不需要处理
+ `1196`: 推流失败，10 s 后会重试，重试 3 次后停止重试


## PublicStreamSEIMessageEvent

类型: `interface`

公共流中包含的 SEI 信息。

### publicStreamId

类型: <code>string</code>

公共流 ID

### sei

类型: <code>Uint8Array</code>

收到的 SEI 消息内容


## PublicStreamVideoFirstFrameDecodedEvent

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
  | -- | -- | -- |
  | publicStreamId | <code>string</code> | 公共流 ID。 |
  | onVideoFirstFrameDecodedEvent | <code>[onVideoFirstFrameDecodedEvent](#onvideofirstframedecodedevent)</code> | 视频首帧解码事件。 |



## onVideoFirstFrameDecodedEvent

类型: `interface`

第一帧远端视频解码事件

### userId

类型: <code>string</code>

发布视频用户的 userId

### height

类型: <code>number</code>

高度

### width

类型: <code>number</code>

宽度


## PublicStreamAudioFirstFrameDecodedEvent

类型: `interface`

公共流首帧解码/渲染事件。

### publicStreamId

类型: <code>string</code>

公共流 ID。


## NetworkQuality

类型: `enum`

网络质量

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | UNKNOWN | `0` | 网络质量未知 |
  | EXCELLENT | `1` | 网络质量极好 |
  | GOOD | `2` | 主观感觉和 Excellent 差不多，但码率可能略低 |
  | POOR | `3` | 主观感受有瑕疵但不影响沟通 |
  | BAD | `4` | 勉强能沟通但不顺畅。建议降低采样率、码率或通过 UI 提示用户是否切换为纯语音通话。 |
  | VBAD | `5` | 网络质量非常差，基本不能沟通。建议通过 UI 给出弱网提示。 |



## RemoteStreamSwitch

类型: `interface`

流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。

### userId

类型: <code>string</code>

订阅的音视频流的发布者的用户 ID

### isScreen

类型: <code>boolean</code>

是否是屏幕共享流

### beforeVideoIndex

类型: <code>number</code>

原分辨率视频流的下标

### afterVideoIndex

类型: <code>number</code>

现分辨率视频流的下标

### beforeEnable

类型: <code>boolean</code>

原媒体流是否是视频流

### afterEnable

类型: <code>boolean</code>

现媒体流是否是视频流

### reason

类型: <code>[FallbackOrRecoverReason](#fallbackorrecoverreason)</code>

触发流回退或恢复的原因


## FallbackOrRecoverReason

类型: `enum`

触发流回退或恢复的原因

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | Unknown | `-1` | 其他原因，非带宽原因引起的回退或恢复。默认值 |
  | SubscribeFallbackByBandwidth | `0` | 由带宽不足导致的流回退。 |
  | SubscribeRecoverByBandwidth | `2` | 由带宽恢复导致的流恢复。 |



## StreamMixingEvent

类型: `interface`

转推直播相关事件。

### event

类型: <code>[StreamMixingEventType](#streammixingeventtype)</code>

转推直播事件类型。

### error

类型: <code>[StreamMixingEventErrorCode](#streammixingeventerrorcode)</code>

转推直播事件错误码。

### message

类型: <code>string</code>

转推直播事件错误详情。


## StreamMixingEventType

类型: `enum`

转推直播事件类型

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | START | `1` | 已发起开始转推请求。 |
  | START_SUCCESS | `2` | 转推至 CDN 成功。 |
  | START_FAILED | `3` | 推流 CDN 失败。 |
  | UPDATE | `4` | 已发起更新转推请求。 |
  | UPDATE_SUCCESS | `5` | 成功应用新配置进行推流。 |
  | UPDATE_FAILED | `6` | 更新合流失败，新配置参数校验失败或配置未生效。 |
  | STOP | `7` | 已发起停止转推请求。 |
  | STOP_SUCCESS | `8` | 成功停止推流至CDN。 |
  | STOP_FAILED | `9` | 停止推流失败。 |



## StreamMixingEventErrorCode

类型: `enum`

转推直播错误码

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | ERR_OK | `0` | 推流成功 |
  | ERR_PARAM_INVALID | `1` | 推流参数错误。 |
  | ERR_FRAME_TIMEOUT | `2` | 和 RTC 服务端建立连接失败，会自动重连。 |
  | ERR_POSTPROCESS | `3` | 合流服务中间过程存在错误，建议重试。 |
  | ERR_PUSH_CDN | `4` | 推流失败，等待服务端重推。 |
  | ERR_UNKNOWN | `9999` | 其他异常。 |



## VideoStreamBannedEvent

类型: `interface`

视频流发布封禁/解禁事件

### uid

类型: <code>string</code>

被禁用/解禁的视频流用户 ID

### banned

类型: <code>boolean</code>

视频流发布状态
true：视频流发布被禁止
false: 视频流发布被解禁


## AudioStreamBannedEvent

类型: `interface`

音频流发布封禁/解禁事件

### uid

类型: <code>string</code>

被禁用/解禁的音频流用户 ID

### banned

类型: <code>boolean</code>

音频流发布状态
true：音频流发布被禁止
false: 音频流发布被解禁


## SubtitleEvent

类型: `interface`

字幕任务状态。

### event

类型: <code>[SubtitleEventType](#subtitleeventtype)</code>

字幕任务状态类型。

### errorCode

类型: <code>[ErrorCode](Web-errorcode.md#errorcode) | undefined</code>

字幕任务错误码。

### errorMessage

类型: <code>string | undefined</code>

字幕相关信息。


## SubtitleEventType

类型: `enum`

字幕任务状态类型。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | STARTED | `0` | 字幕已开启。 |
  | STOPPED | `1` | 字幕已关闭。 |
  | ERROR | `2` | 字幕任务出现错误。 |



## SubtitleMessage

类型: `interface`

字幕具体内容。

### userId

类型: <code>string</code>

说话者的用户ID。

### text

类型: <code>string</code>

语音识别或翻译后的文本, 采用 UTF-8 编码。

### definite

类型: <code>boolean</code>

语音识别出的文本是否为一段完整的一句话。 True 代表是, False 代表不是。

### sequence

类型: <code>number</code>

语音识别或翻译后形成的文本的序列号。同一发言人的完整发言和不完整发言会按递增顺序单独分别编号。


## RoomConfig

类型: `interface`

房间参数配置。

### isAutoPublish

类型: <code>boolean | undefined</code>

是否自动发布音频流，默认为自动发布。
取消自动发布后，通过调用 [publishStream](Web-api.md#publishstream) 进行音视频流发布。

### isAutoSubscribeAudio

类型: <code>boolean | undefined</code>

是否自动订阅音频流，默认为自动订阅。
不包含屏幕流。
进房后，你可以调用 [subscribeStream](Web-api.md#subscribestream)、[unsubscribeStream](Web-api.md#unsubscribestream) 修改订阅设置。

### isAutoSubscribeVideo

类型: <code>boolean | undefined</code>

是否自动订阅视频流，默认为自动订阅。
不包含屏幕流。
进房后，你可以调用 [subscribeStream](Web-api.md#subscribestream)、[unsubscribeStream](Web-api.md#unsubscribestream) 修改订阅设置。

### remoteVideoConfig

类型: <code>[RemoteVideoConfig](#remotevideoconfig) | undefined</code>

远端视频流参数


## RemoteVideoConfig

类型: `interface`

远端视频流参数

### width

类型: <code>number</code>

视频宽度，单位：px

### height

类型: <code>number</code>

视频宽度，单位：px


## ScreenConfig

类型: `interface`

屏幕共享流设置

### enableAudio

类型: <code>boolean | undefined</code>

在共享屏幕时是否显示共享音频选项:
• Window 端选择共享整个屏幕时支持共享系统音频；在共享 Chrome 标签页时支持共享 Tab 标签页面音频。
• macOS 仅支持在共享 Chrome 标签页时共享 Tab 标签页面音频。


## VideoPlayerOption

类型: `interface`

播放器信息和渲染模式

### renderDom

类型: <code>string | HTMLElement | undefined</code>

DOM

### renderMode

类型: <code>[VideoRenderMode](#videorendermode) | undefined</code>

渲染模式：可选 `RENDER_MODE_HIDDEN` 和 `RENDER_MODE_FIT` 。

### userId

类型: <code>string</code>

用户 ID，支持以下字符集范围

+ 26 个大写字母 A ~ Z
+ 26 个小写字母 a ~ z
+ 10 个数字 0 ~ 9
+ 下划线 "_"，at 符 "@"，减 号 "-"


## VideoRenderMode

类型: `enum`

渲染模式

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | RENDER_MODE_HIDDEN | `0` | 视窗填满优先。<br>视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。 |
  | RENDER_MODE_FIT | `1` | 视频帧内容全部显示优先。<br>视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。 |



## MirrorType

类型: `enum`

镜像类型

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | MIRROR_TYPE_NONE | `0` | 本地渲染和编码传输时均无镜像效果 |
  | MIRROR_TYPE_RENDER | `1` | 本地渲染时有镜像效果，编码传输时无镜像效果 |



## VideoEncoderConfig

类型: `interface`

视频编码参数。

### width

类型: <code>ConstrainULong</code>

视频宽度，单位为像素。默认值为 640 px。
支持传入 `number` 或一个整形约束对象，参看 [ConstrainULong](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constrainulong)。

### height

类型: <code>ConstrainULong</code>

视频高度，单位为像素。默认值为 480 px。
支持传入 `number` 或一个整形约束对象，参看 [ConstrainULong](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constrainulong)。

### frameRate

类型: <code>ConstrainDouble</code>

视频帧率，单位为 FPS。默认值为 15 FPS。
支持传入 `number` 或一个浮点形约束对象，参看 [ConstrainDouble](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constraindouble)。

### maxKbps

类型: <code>number</code>

最大编码码率，RTC SDK 内部采集和自定义采集均需设定 > 0 的数值，单位为 Kbps。默认值为 600 Kbps。


## ScreenEncoderConfig

类型: `interface`

屏幕共享的视频编码参数。

### width

类型: <code>ConstrainULong</code>

视频宽度，单位为像素。默认值为 1920 px。
支持传入 `number` 或一个整形约束对象，参看 [ConstrainULong](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constrainulong)。

### height

类型: <code>ConstrainULong</code>

视频高度，单位为像素。默认值为 1080 px。
支持传入 `number` 或一个整形约束对象，参看 [ConstrainULong](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constrainulong)。

### frameRate

类型: <code>ConstrainDouble</code>

视频帧率，默认值为 15 FPS。
支持传入 `number` 或一个浮点形约束对象，参看 [ConstrainDouble](https://developer.mozilla.org/en-US/docs/Web/API/MediaTrackConstraints#constraindouble)。

### maxKbps

类型: <code>number</code>

最大编码码率，RTC SDK 内部采集和自定义采集均需设定 > 0 的数值，单位为 Kbps。默认值为 3000 Kbps。

### contentHint

类型: <code>"text" | "motion" | "detail" | undefined</code>

屏幕共享的视频内容类型。

- 'detail'【默认值】：清晰度优先，适用于视频内容包含图片、文本混排的情况。
- 'text'：清晰度优先，适用于视频内容只包含大量文本的情况。
- 'motion'：流畅度优先，适用于视频内容为摄像头采集、电影、视频、游戏的情况。

- **注意**

  仅支持Chrome浏览器设置此参数。


## AudioPropertiesConfig

类型: `interface`

音频信息提示的相关配置

### interval

类型: <code>number | undefined</code>

信息提示间隔，单位：ms，默认为 100ms

+ `<= 0`: 关闭信息提示；
+ `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms；
+ `> 100`: 开启信息提示，并将信息提示间隔设置为此值。

### enableInBackground

类型: <code>boolean | undefined</code>

是否在页面隐藏时保持开启获取音量回调，默认保持开启。

+ true: 保持开启
+ false：关闭


## LiveTranscodeConfig

类型: `interface`

转码推流配置参数。

### url

类型: <code>string</code>

推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。
本参数不支持过程中更新。

### audio

类型: <code>Partial<[LiveTranscodeAudioConfig](#livetranscodeaudioconfig)\> | undefined</code>

音频转码配置参数。
本参数不支持过程中更新。

### video

类型: <code>Partial<[LiveTranscodeVideoConfig](#livetranscodevideoconfig)\> | undefined</code>

视频转码配置参数。

### layout

类型: <code>Partial<[LiveTranscodeLayoutConfig](#livetranscodelayoutconfig)\> | undefined</code>

用户布局信息。


## LiveTranscodeAudioConfig

类型: `interface`

音频转码配置参数。值不合法或未设置时，自动使用默认值。

### codec

类型: <code>"AAC" | undefined</code>

音频编码格式，选填，默认为 `AAC`。

### kBitRate

类型: <code>number</code>

音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。

### sampleRate

类型: <code>number</code>

音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。

### channels

类型: <code>number</code>

音频声道数。可取 1（单声道）、2（双声道），默认值为 2。

### AACProfile

类型: <code>[AAC_PROFILE](#aac_profile)</code>

<span id="aac_profile"></span>
AAC 编码规格。默认值为 `LC`。


## AAC_PROFILE

类型: `enum`

AAC 编码规格。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | LC | `'LC'` | AAC-LC 规格，默认值。 |
  | HEv1 | `'HEv1'` | HE-AAC v1 规格。 |
  | HEv2 | `'HEv2'` | HE-AAC v2 规格。 |



## LiveTranscodeVideoConfig

类型: `interface`

视频转码配置参数。值不合法或未设置时，自动使用默认值。

### width

类型: <code>number</code>

合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。
设置值为非偶数时，自动向上取偶数。

### height

类型: <code>number</code>

合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。
设置值为非偶数时，自动向上取偶数。

### codec

类型: <code>[TRANSCODING_VIDEO_CODEC](#transcoding_video_codec)</code>

视频编码格式。默认值为 `H264`。
本参数不支持过程中更新。

### fps

类型: <code>number</code>

合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。

### gop

类型: <code>number</code>

视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。
本参数不支持过程中更新。


## TRANSCODING_VIDEO_CODEC

类型: `enum`

<span id="transcoding_video_codec"></span>
视频编码格式。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | H264 | `'H264'` | H.264 格式，默认值。 |
  | H265 | `'H265'` | ByteVC1 格式。 |



## LiveTranscodeLayoutConfig

类型: `interface`

视频流合流整体布局信息。
开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。

### regions

类型: <code>[LiveTranscodeLayoutRegion](#livetranscodelayoutregion)[]</code>

用户布局信息列表。值不合法或未设置时，自动使用默认值。

### appData

类型: <code>string</code>

透传的 App 数据，长度不超过 4 KB。

### backgroundColor

类型: <code>string</code>

合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。
值不合法或未设置时，自动使用默认值。


## LiveTranscodeLayoutRegion

类型: `interface`

单个视频流在合流中的布局信息。

### alpha

类型: <code>number | undefined</code>

透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。

### userId

类型: <code>string</code>

视频流发布用户的用户 ID

### x

类型: <code>number | undefined</code>

视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。

### y

类型: <code>number | undefined</code>

视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。

### zorder

类型: <code>number | undefined</code>

用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。

### w

类型: <code>number | undefined</code>

视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。默认值为 1.0。

### h

类型: <code>number | undefined</code>

视频流对应区域高度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。默认值为 1.0。

### renderMode

类型: <code>number | undefined</code>

图片或视频流的缩放模式，默认值为 1。可选取值如下：
• 1: 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
• 2: 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。
• 3: 视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。

### contentControl

类型: <code>number | undefined</code>

合流内容控制。默认值为0，可选取值如下：
• 0: 输出的混流包含音视频。
• 1: 只包含音频。
• 2: 只包含视频。

### isScreenStream

类型: <code>boolean</code>

是否是屏幕流


## VideoSourceType

类型: `enum`

视频采集方式

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | VIDEO_SOURCE_TYPE_EXTERNAL | `0` | 自定义采集 |
  | VIDEO_SOURCE_TYPE_INTERNAL | `1` | 内部采集，使用由 SDK 提供的视频采集模块（默认） |



## AudioSourceType

类型: `enum`

音频采集方式

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | AUDIO_SOURCE_TYPE_EXTERNAL | `0` | 自定义采集模块 |
  | AUDIO_SOURCE_TYPE_INTERNAL | `1` | 内部采集，使用由 SDK 提供的音频采集模块 |



## USER_ONLINE_STATUS

类型: `enum`

<span id="user_online_status"></span>
登录状态

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | OFFLINE | `0` | 离线。无法收发点对点消息。 |
  | ONLINE | `1` | 在线 |
  | UNREACHABLE | `2` | 未知。无法收发点对点消息。 |



## CloudProxyInfo

类型: `interface`

### logProxy

类型: <code>string</code>

埋点日志上报的的代理地址

### accessProxy

类型: <code>string</code>

统一接入的代理地址

### configProxy

类型: <code>string</code>

RTC 配置下发的代理地址


## PublicStreamConfig

类型: `interface`

公共流配置信息

### video

类型: <code>{ width?: number | undefined; height?: number | undefined; fps?: number | undefined; kBitRate: number; } | undefined</code>

视频参数

 - **成员**

    | 名称 | 类型 | 描述 |
    | -- | -- | -- |
    | width | `number | undefined` | 宽度，单位：px。<br>仅支持设为偶数，如果设为奇数，将导致公共流发布失败。 |
    | height | `number | undefined` | 高度，单位：px。<br>仅支持设为偶数，如果设为奇数，云端媒体处理会直接拒绝，导致公共流失败。 |
    | fps | `number | undefined` | 帧率，单位：fps |
    | kBitRate | `number` | 码率，单位：kbps |


### layout

类型: <code>{ interpolationMode?: [PublicInterpolationMode](#publicinterpolationmode) | undefined; backgroundColor?: string | undefined; backgroundImage?: string | undefined; regions?: [PublicStreamLayoutRegion](#publicstreamlayoutregion)[] | undefined; } | undefined</code>

公共流的布局模式

 - **成员**

    | 名称 | 类型 | 描述 |
    | -- | -- | -- |
    | interpolationMode | `PublicInterpolationMode | undefined` | 补帧模式 |
    | backgroundColor | `string | undefined` | 背景颜色，用 Hex 色值表示。 |
    | backgroundImage | `string | undefined` | 背景图片的 URL。长度最大为 1024 byte。可以传入的图片的格式包括：JPG, JPEG, PNG。 |
    | regions | `PublicStreamLayoutRegion[] | undefined` | 多路媒体流布局设置。 |



## PublicInterpolationMode

类型: `enum`

补帧模式

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | PREV_FRAME | `0` | 补最后一帧。 |
  | OTHER_FRAME | `1` | 补背景图片或者黑帧。 |



## PublicStreamLayoutRegion

多路媒体流中一路流的布局设置。

- **类型**

  ```ts
  Omit<
    LiveTranscodeLayoutRegion,
    'isLocalUser' | 'contentControl'
  > & {
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
  | -- | -- | -- |
  | roomId | <code>string</code> | 媒体流发布用户的房间 ID |
  | mediaType | <code>[PublicStreamType](#publicstreamtype) \| undefined</code> | 公共流输出内容类型 |
  | sourceCrop | <code>{ x: number; y: number; w: number; h: number; } \| undefined</code> | 公共流视频裁剪配置 |
  | x | <code>number</code> | 裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)。 |
  | y | <code>number</code> | 裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)。 |
  | w | <code>number</code> | 裁剪后得到的视频帧宽度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]。 |
  | h | <code>number</code> | 裁剪后得到的视频帧高度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]。 |



## PublicStreamType

类型: `enum`

公共流输出内容类型

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | AUDIO_AND_VIDEO | `0` | 包含音视频 |
  | AUDIO_ONLY | `1` | 仅包含音频 |
  | VIDEO_ONLY | `2` | 仅包含视频 |



## SubscribeFallbackOption

类型: `enum`

订阅端音视频流回退选项。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | DISABLE | `0` | 不开启回退功能。默认设置。 |
  | VIDEO_STREAM_LOW | `1` | 下行网络不佳时，对视频流做降级处理。具体降级规则参看[音视频流回退](https://www.volcengine.com/docs/6348/70137)文档。<br>该设置仅对发布端调用 [EnableSimulcastMode](Web-api.md#enablesimulcastmode) 开启发送多路流功能的情况生效。 |
  | AUDIO_ONLY | `2` | 下行网络不佳时，取消接收视频，仅接收音频。<br>当发布端开启发送多路流功能时，设置此选项不利于提升用户体验，因此不建议设置此选项。 |



## RemoteUserPriority

类型: `enum`

远端用户优先级

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | LOW | `0` | 用户优先级为低（默认值） |
  | MEDIUM | `100` | 用户优先级为正常 |
  | HIGH | `200` | 用户优先级为高 |



## AudioProfileType

类型: `enum`

音质档位
调用 [setAudioProfile](Web-api.md#setaudioprofile) 设置的音质档位

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | default | `0` | 默认音质<br>服务器下发的音质配置 |
  | fluent | `1` | 流畅音质。<br>单声道，采样率为 16kHz，编码码率为 24kbps。<br>流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。 |
  | standard | `2` | 单声道标准音质。<br>采样率为 48kHz，编码码率为 48kbps。<br>适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和狼人杀等游戏。 |
  | hd | `3` | 双声道音乐音质<br>采样率为 48kHz，编码码率为 128kbps。<br>超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。<br>游戏场景不建议使用。 |
  | standardStereo | `4` | 双声道标准音质。采样率为 48 KHz，编码码率最大值为 80 Kbps |
  | hdMono | `5` | 单声道音乐音质。采样率为 48 kHz，编码码率最大值为 128 Kbps |



## RTCSubtitleConfig

类型: `interface`

字幕配置信息。

### targetLanguage

类型: <code>string | undefined</code>

目标翻译语言。可点击 [语言支持](https://www.volcengine.com/docs/4640/35107#%E7%9B%AE%E6%A0%87%E8%AF%AD%E8%A8%80-2) 查看翻译服务最新支持的语种信息。

### mode

类型: <code>[SUBTITLE_MODE](#subtitle_mode)</code>

字幕模式。


## SUBTITLE_MODE

类型: `enum`

字幕模式。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | ASR_ONLY | `0` | 识别模式。在此模式下，房间内用户语音会被转为文字。 |
  | ASR_AND_TRANSLATION | `1` | 翻译模式。在此模式下，房间内用户语音会先被转为文字，再被翻译为目标语言。 |



## EngineConfig

类型: `interface`

引擎级别配置项

### autoPlayPolicy

类型: <code>[RTCAutoPlayPolicy](#rtcautoplaypolicy)</code>

自动播放策略


## RTCAutoPlayPolicy

类型: `enum`

自动播放策略。参考[自动播放策略](https://www.volcengine.com/docs/6348/130302)，获取更多相关信息。

- **成员**

  | 属性 | 值 | 描述 |
  | -- | -- | -- |
  | AUTO_PLAY | `0` | 默认值，自动播放音频和视频 |
  | VIDEO_ONLY | `1` | 自动播放视频，不自动播放音频 |
  | PLAY_MANUALLY | `2` | 不自动播放，引导用户通过交互，手动播放 |