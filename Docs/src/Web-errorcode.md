## ErrorCode <span id="errorcode"></span>

类型: `enum`

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | INVALID_ENGINE | `'INVALID_ENGINE'` | 调用 `destroyEngine` 时，传入的参数不是合法的 engine 对象。 |
  | INVALID_PARAMS | `'INVALID_PARAMS'` | 通用错误码。调用方法时，传入的参数不合法。请根据各方法说明传入正确的参数。 |
  | INVALID_TOKEN | `'INVALID_TOKEN'` | 调用 `joinRoom` 进房时使用了已过期的 Token 或使用的 Token 无效。请重新获取 Token 后再次调用 `joinRoom` 进房。 |
  | JOIN_ROOM_FAILED | `'JOIN_ROOM_FAILED'` | 调用 `joinRoom` 进房失败，具体错误原因查看 message。 |
  | UPDATE_TOKEN_WITH_INVALID_TOKEN | `'UPDATE_TOKEN_WITH_INVALID_TOKEN'` | 调用 `updateToken` 时传入的 Token 无效。请使用有效的 Token。 |
  | UPDATE_TOKEN_BEFORE_JOIN | `'UPDATE_TOKEN_BEFORE_JOIN'` | 调用 `updateToken` 时不在房间内，请先调用 `joinRoom` 加入房间。 |
  | REPEAT_JOIN | `'REPEAT_JOIN'` | 重复进房。已加入房间后，又再次调用 `joinRoom` 时触发。 |
  | REPEAT_PUSH | `'REPEAT_PUSH'` | 重复发布公共流。已发布公共流后，又再次调用 `startPushPublicStream` 时触发。 |
  | REPEAT_PLAY | `'REPEAT_PLAY'` | 调用 `startPlayPublicStream` 重复订阅同一条公共流。 |
  | NO_PUBLISH_PERMISSION | `'NO_PUBLISH_PERMISSION'` | 无发布权限。调用 `setUserVisibility` 将自身设置为对当前房间内其他用户不可见后，调用 `publishStream` 或 `publishScreen` 发布流。请先将自身切换至可见后再发布流。 |
  | STREAM_NOT_EXIST | `'STREAM_NOT_EXIST'` | 目标流不存在。触发时机包括：调用 `subscribeStream`/`unsubscribeStream` 订阅/取消订阅一路不存在的流；调用 `takeRemoteSnapshot` 截取远端画面时指定的流不存在。请输入正确的 ID，或确认目标流在房间内。 |
  | NOT_CONNECTED_YET | `'NOT_CONNECTED_YET'` | 非法操作。SDK 尚未与服务器建连，在此状态下不能进行该操作。请确认调用方法时是否已加入房间，或网络状态是否正常。 |
  | KICKED_OUT | `'KICKED_OUT'` | 服务端调用 OpenAPI 将当前用户踢出房间。通过 `onError` 回调。 |
  | ROOM_DISMISS | `'ROOM_DISMISS'` | 服务端调用 OpenAPI 解散房间，所有用户被移出房间。通过 `onError` 回调。 |
  | TOKEN_EXPIRED | `'TOKEN_EXPIRED'` | 加入房间后，Token 过期。通过 `onError` 回调。请获取新的 Token 后，调用 `joinRoom` 重新加入房间。 |
  | TOKEN_NO_PUBLISH_PERMISSION | `'TOKEN_NO_PUBLISH_PERMISSION'` | Token 发布权限过期，通过 `onTokenPublishPrivilegeDidExpired` 回调。调用 `updateToken` 更新 Token 发布权限。 |
  | TOKEN_NO_SUBSCRIBE_PERMISSION | `'TOKEN_NO_SUBSCRIBE_PERMISSION'` | Token 订阅权限过期，通过 `onTokenSubscribePrivilegeDidExpired` 回调。调用 `updateToken` 更新 Token 订阅权限。 |
  | DUPLICATE_LOGIN | `'DUPLICATE_LOGIN'` | 有相同用户 ID 的用户加入本房间，当前用户被踢出房间。通过 `onError` 回调。 |
  | INVOKED_BEFORE_CAPTURE | `'INVOKED_BEFORE_CAPTURE'` | 调用 `takeLocalSnapshot` 截取本地画面时指定的视频流不存在。请确保指定的流已发布。 |
  | REPEAT_CAPTURE | `'REPEAT_CAPTURE'` | 重复采集。调用 `startAudioCapture`、`startVideoCapture` 或 `startAudioAndVideoCapture` 重复采集同一条音频/视频流时触发。 |
  | GET_VIDEO_TRACK_FAILED | `'GET_VIDEO_TRACK_FAILED'` | 调用 `startVideoCapture` 或 `startAudioAndVideoCapture` 开启视频采集失败。请确认是否有可用的采集设备，或是否被其他 App 占用。 |
  | GET_AUDIO_TRACK_FAILED | `'GET_AUDIO_TRACK_FAILED'` | 调用 `startAudioCapture` 或 `startAudioAndVideoCapture` 开启音频采集失败。请确认是否有可用的采集设备，或是否被其他 App 占用。 |
  | GET_SCREEN_TRACK_FAILED | `'GET_SCREEN_TRACK_FAILED'` | 调用 `startScreenCapture` 开启屏幕采集共享失败。 |
  | STREAM_TYPE_NOT_MATCH | `'STREAM_TYPE_NOT_MATCH'` | 流类型不匹配。调用 `setVideoSourceType` 设置了自定义视频源后，又调用 `startAudioCapture`、`stopAudioCapture`、`startVideoCapture`、`stopVideoCapture` 或 `startAudioAndVideoCapture` 等内部采集相关的接口。 |
  | CANT_FIND_DOM | `'CANT_FIND_DOM'` | 调用 `setLocalVideoPlayer`/`setRemoteVideoPlayer` 传入的播放容器不存在。 |
  | INVALID_DEVICE_ID | `'INVALID_DEVICE_ID'` | 调用 `setAudioPlaybackDevice` 设置音频播放设备时，输入的设备 ID 无效。 |
  | NOT_SUPPORTED | `'NOT_SUPPORTED'` | 调用 `startAudioDeviceRecordTest`/`setAudioPlaybackDevice` 失败，浏览器不支持设置音频播放设备或测试音频采集/播放设备。 |
  | ICE_SERVER_WRONG | `'ICE_SERVER_WRONG'` | 调用 `joinRoom` 时请求分配 ICE 节点时失败。 |
  | LOAD_RESOURCES_FAILED | `'LOAD_RESOURCES_FAILED'` | 调用 `startAudioMixing` 或 `preloadAudioMixing` 时资源加载失败。请传入正确的资源路径。 |
  | TIME_OUT | `'TIME_OUT'` | 通用错误码，60s 内没有收到信令回复。 |
  | ADD_TRANSCEIVER_FAILED | `'ADD_TRANSCEIVER_FAILED'` | 创建 TRANSCEIVER 失败 |
  | PUBLISH_FAILED | `'PUBLISH_FAILED'` | 调用 `publishStream` 或 `publishScreen` 发布流失败，具体原因查看 message。 |
  | OPERATION_CANCEL | `'OPERATION_CANCEL'` | 通用错误码。发布/订阅等操作执行到一半时离开房间，会触发该错误回调，表示操作中断，无需处理。 |
  | START_CLOUD_PROXY_AFTER_JOIN | `'START_CLOUD_PROXY_AFTER_JOIN'` | 调用 `startCloudProxy` 开启云代理功能失败，原因为进房后调用。你需要在进房前调用该方法。 |
  | STOP_CLOUD_PROXY_BEFORE_LEAVE | `'STOP_CLOUD_PROXY_BEFORE_LEAVE'` | 调用 `stopCloudProxy` 关闭云代理功能失败，原因为离开房间前调用。你需要在退房后调用该方法。 |
  | UNEXPECTED_ERROR | `'UNEXPECTED_ERROR'` | 通用错误码。具体错误原因查看 message。 |
  | REPEAT_DEVICE_TEST | `'REPEAT_DEVICE_TEST'` | 检测已开启。已经开启音频设备检测后，重复调用 `startAudioPlaybackDeviceTest` 或 `startAudioDeviceRecordTest` 时触发。 |
  | AUDIO_DEVICE_TEST_FAILED | `'AUDIO_DEVICE_RECORD_FAILED'` | 调用 `startAudioDeviceRecordTest` 开启音频设备测试失败，请重试。 |
  | ALREADY_LOGIN | `'ALREADY_LOGIN'` | 调用 `login` 失败，已有相同 userId 的用户登录了实时信令服务器，请勿重复登录或使用不同的 userId 登录。 |
  | LOGIN_FAILED | `'LOGIN_FAILED'` | 调用 `login` 登录实时信令服务器失败，具体原因查看 message。 |
  | NOT_LOGIN | `'NOT_LOGIN'` | 消息功能通用错误码。尚未调用 `login` 成功登录实时信令服务器前调用消息相关 API 时触发。请先登录。 |
  | RTM_DUPLICATE_LOGIN | `'RTM_DUPLICATE_LOGIN'` | 相同用户 ID 的用户登录，导致本地已登录用户被顶出。通过 `onError` 回调。 |
  | RTM_TOKEN_ERROR | `'RTM_TOKEN_ERROR'` | 重连实时信令服务器时使用的 Token 异常。通过 `onError` 回调。请使用新的 Token 重新登录。 |
  | USER_MESSAGE_TIMEOUT | `'USER_MESSAGE_TIMEOUT'` | 调用 `sendUserMessage`、`sendUserBinaryMessage`、`sendUserMessageOutsideRoom`、`sendUserBinaryMessageOutsideRoom`、`sendServerMessage` 或 `sendServerBinaryMessage` 发送点对点消息超时。 |
  | USER_MESSAGE_BROKEN | `'USER_MESSAGE_BROKEN'` | 调用 `sendUserMessage`、`sendUserBinaryMessage`、`sendUserMessageOutsideRoom`、`sendUserBinaryMessageOutsideRoom`、`sendServerMessage` 或 `sendServerBinaryMessage` 发送点对点消息时，通道断开，发送失败。 |
  | USER_MESSAGE_NO_RECEIVER | `'USER_MESSAGE_NO_RECEIVER'` | 调用 `sendUserMessage`、`sendUserBinaryMessage`、`sendUserMessageOutsideRoom`、`sendUserBinaryMessageOutsideRoom`、`sendServerMessage` 或 `sendServerBinaryMessage` 发送点对点消息时找不到接收者，请检查传入的 userId 是否正确。 |
  | USER_MESSAGE_SEND_TO_SERVER_ERROR | `'USER_MESSAGE_SEND_TO_SERVER_ERROR'` | 调用 `sendServerMessage` 或 `sendServerBinaryMessage` 发送点对点消息到业务服务器无应答，可能是 Http 不通。 |
  | USER_MESSAGE_SERVER_RESPONSE_ERROR | `'USER_MESSAGE_SERVER_RESPONSE_ERROR'` | 调用 `sendServerMessage` 或 `sendServerBinaryMessage` 发送点对点消息到业务服务器失败，业务服务器 Http 响应状态码不是 200。 |
  | USER_MESSAGE_NOT_JOIN | `'USER_MESSAGE_NOT_JOIN'` | 调用 `sendUserMessage` 或 `sendUserBinaryMessage` 发送点对点消息失败，原因是尚未进房。请加入房间后调用。 |
  | USER_MESSAGE_NOT_LOGIN | `'USER_MESSAGE_NOT_LOGIN'` | 调用 `sendUserMessageOutsideRoom`/`sendUserBinaryMessageOutsideRoom` 发送房间外点对点消息，或调用 `sendServerMessage`/`sendServerBinaryMessage` 向业务服务器发送消息时尚未登录实时信令服务器，请先调用 `login` 登录。 |
  | USER_MESSAGE_SERVER_PARAMS_NOTSET | `'USER_MESSAGE_SERVER_PARAMS_NOTSET'` | 调用 `sendServerMessage`/`sendServerBinaryMessage` 向业务服务器发送消息之前，尚未设置参数，请先调用 `setServerParam` 设置业务服务器参数。 |
  | USER_MESSAGE_UNKNOWN | `'USER_MESSAGE_UNKNOWN'` | 调用 `sendUserMessage`、`sendUserBinaryMessage`、`sendUserMessageOutsideRoom`、`sendUserBinaryMessageOutsideRoom`、`sendServerMessage` 或 `sendServerBinaryMessage` 发送点对点消息时发生未知错误。 |
  | RECONNECT_FAILED | `'RECONNECT_FAILED'` | SDK 与服务端重连失败，并不再自动重试。通过 `onError` 回调。你需退房后重新进房，或联系技术支持。 |
  | SUBTITLE_ALREADY_ON | `'SUBTITLE_ALREADY_ON'` | 字幕已开启。已开启字幕功能后，再次调用 `startSubtitle` 时触发。请勿重复开启字幕功能。 |
  | SUBTITLE_ERR_POSTPROCESS | `'SUBTITLE_ERR_POSTPROCESS'` | 云端媒体处理内部出现错误。通过 `onSubtitleStateChanged` 回调。请联系技术支持。 |
  | SUBTITLE_ERR_CONNECTION_ERROR | `'SUBTITLE_ERR_CONNECTION_ERROR'` | 第三方服务连接失败。通过 `onSubtitleStateChanged` 回调。请联系技术支持。 |
  | SUBTITLE_ERR_PROCESS_ERROR | `'SUBTITLE_ERR_PROCESS_ERROR'` | 云端媒体处理超时未响应。通过 `onSubtitleStateChanged` 回调。请联系技术支持。 |
  | SUBTITLE_ERR_UNKNOWN | `'SUBTITLE_ERR_UNKNOWN'` | 客户端无法识别云端媒体处理发送的错误码。通过 `onSubtitleStateChanged` 回调。请联系技术支持。 |
  | UNEXPECTED_INVOKE_FORWARD_STREAM | `'UNEXPECTED_INVOKE_FORWARD_STREAM'` | 跨房间转发媒体流相关 API 的调用时机不正确，请参考各接口说明确认调用的先后顺序。 |
  | ROOM_FORBIDDEN | `'ROOM_FORBIDDEN'` | 调用 `joinRoom` 进房失败，原因是房间被封禁。 |
  | USER_FORBIDDEN | `'USER_FORBIDDEN'` | 调用 `joinRoom` 进房失败，原因是本地用户被封禁。 |
  | ERR_ELECTRON_IS_NULL | `'ERR_ELECTRON_IS_NULL'` | 获取 Electron 实例失败。确认当前满足 Electron 开发环境要求，参考 [Electron 架构下通过 Web SDK 实现屏幕共享](https://www.volcengine.com/docs/6348/1340581)。 |
  | ELECTRON_DESKTOP_CAPTURER_GET_SOURCES_ERROR | `'ELECTRON_DESKTOP_CAPTURER_GET_SOURCES_ERROR'` | 在 Electron 环境中获取桌面共享源失败。 |
  | SET_SIMULCAST_FAILED | `'SET_SIMULCAST_FAILED'` | Simulcast 功能设置失败。确认调用时机是否满足 [`setLocalSimulcastMode`](Web-api.md#rtcengine-setlocalsimulcastmode) 要求。<br>开始发布后可以更改分辨率，但不能更改路数。 |
  | MIXING_OLD_AND_NEW_APIS | `'MIXING_OLD_AND_NEW_APIS'` | 混用了 Simulcast 功能的废弃接口和当前接口。后续版本将不再维护废弃接口，并预计在多个版本后删除，建议尽快替换为当前接口。<br>+ `setRemoteVideoConfig` 已废弃，请使用 [`setRemoteSimulcastStreamType`](Web-api.md#rtcengine-setremotesimulcaststreamtype)。<br>+ `enableSimulcastMode` 已废弃，请使用 [`setLocalSimulcastMode`](Web-api.md#rtcengine-setlocalsimulcastmode)。 |



## AudioMixingError <span id="audiomixingerror"></span>

类型: `enum`

混音错误码，通过 [onAudioMixingStateChanged](Web-event.md#onaudiomixingstatechanged) 回调。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | AUDIO_MIXING_ERROR_OK | `0` | 混音正常。 |
  | AUDIO_MIXING_ERROR_PRELOAD_FAILED | `1` | 预加载失败，找不到混音文件或者文件长度超出 20s。 |
  | AUDIO_MIXING_ERROR_START_FAILED | `2` | 混音开启失败，找不到混音文件或者混音文件打开失败。 |
  | AUDIO_MIXING_ERROR_ID_NOT_FOUND | `3` | 混音 ID 异常。 |
  | AUDIO_MIXING_ERROR_SET_POSITION_FAILED | `4` | 设置混音文件的播放位置出错。 |
  | AUDIO_MIXING_ERROR_INVALID_VOLUME | `5` | 音量参数不合法，音量值区间应为[0, 400]。 |
  | AUDIO_MIXING_ERROR_LOAD_CONFLICT | `6` | 播放的文件与预加载的文件不一致，请先使用 `unloadAudioMixing` 卸载文件。 |
  | AUDIO_MIXING_ERROR_ID_TYPE_NOT_MATCH | `7` | 混音 ID 类型不匹配，当前操作接口不支持该 ID 代表的音频流类型。 |
  | AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH | `8` | 设置混音文件的音调不合法。 |
  | AUDIO_MIXING_ERROR_INVALID_AUDIO_TRACK | `9` | 设置混音文件的音轨不合法。 |



## StreamMixingEventErrorCode <span id="streammixingeventerrorcode"></span>

类型: `enum`

转推直播错误码，通过 [onStreamMixingEvent](Web-event.md#onstreammixingevent) 回调。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | ERR_OK | `0` | 推流成功 |
  | ERR_PARAM_INVALID | `1` | 推流参数错误。 |
  | ERR_FRAME_TIMEOUT | `2` | 和 RTC 服务端建立连接失败，会自动重连。 |
  | ERR_POSTPROCESS | `3` | 合流服务中间过程存在错误，建议重试。 |
  | ERR_PUSH_CDN | `4` | 推流失败，等待服务端重推。 |
  | ERR_UNKNOWN | `9999` | 其他异常。 |



## ForwardStreamError <span id="forwardstreamerror"></span>

类型: `enum`

跨房间转发媒体流错误码，通过 [onForwardStreamError](Web-event.md#onforwardstreamerror) 回调。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | FORWARD_STREAM_ERROR_OK | `0` | 成功。 |
  | FORWARD_STREAM_ERROR_INVALID_TOKEN | `1202` | 目标房间 Token 错误。 |
  | FORWARD_STREAM_ERROR_RESPONSE | `1203` | 服务端未知错误。 |
  | FORWARD_STREAM_ERROR_REMOTE_KICKED | `1204` | 将源房间设置为目标房间时返回该错误。 |