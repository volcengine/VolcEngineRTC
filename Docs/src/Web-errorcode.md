## ErrorCode <span id="errorcode"></span>

类型: `enum`

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | INVALID_ENGINE | `'INVALID_ENGINE'` | 调用 destroyEngine 时，传入的参数不是合法的 engine 对象 |
  | INVALID_PARAMS | `'INVALID_PARAMS'` | 调用方法时，传入的参数不合法 |
  | INVOKED_BEFORE_JOIN_ROOM | `'INVOKED_BEFORE_JOIN_ROOM'` | 尝试发布/取消发布或订阅/取消订阅流时不在房间内 |
  | INVALID_TOKEN | `'INVALID_TOKEN'` | Token 无效 |
  | EXPIRED_TOKEN | `'EXPIRED_TOKEN'` | Token 过期失效 |
  | JOIN_ROOM_FAILED | `'JOIN_ROOM_FAILED'` | 加入房间失败 |
  | UPDATE_TOKEN_WITH_INVALID_TOKEN | `'UPDATE_TOKEN_WITH_INVALID_TOKEN'` | 更新时使用的 Token 无效 |
  | UPDATE_TOKEN_BEFORE_JOIN | `'UPDATE_TOKEN_BEFORE_JOIN'` | 调用 updateToken 时不在房间内 |
  | REPEAT_JOIN | `'REPEAT_JOIN'` | 重复加入房间 |
  | REPEAT_PUBLISH | `'REPEAT_PUBLISH'` | 重复发布流 |
  | REPEAT_PUSH | `'REPEAT_PUSH'` | 重复发布公共流 |
  | REPEAT_PLAY | `'REPEAT_PLAY'` | 重复订阅公共流 |
  | PUBLISH_BEFORE_JOIN | `'PUBLISH_BEFORE_JOIN'` | 在加入房间之前就执行发布操作 |
  | UNPUBLISH_BEFORE_JOIN | `'UNPUBLISH_BEFORE_JOIN'` | 在加入房间之前就执行取消发布操作 |
  | SUBSCRIBE_BEFORE_JOIN | `'SUBSCRIBE_BEFORE_JOIN'` | 在加入房间之前就执行订阅操作 |
  | UNSUBSCRIBE_BEFORE_JOIN | `'UNSUBSCRIBE_BEFORE_JOIN'` | 在加入房间之前就执行取消订阅操作 |
  | NO_PUBLISH_PERMISSION | `'NO_PUBLISH_PERMISSION'` | 隐身状态下发布流 |
  | STREAM_NOT_EXIST | `'STREAM_NOT_EXIST'` | 订阅或者取消订阅不存在一路流 |
  | EMPTY_STREAM | `'EMPTY_STREAM'` | 发布时，没有采集任何音视频流 |
  | NOT_CONNECTED_YET | `'NOT_CONNECTED_YET'` | SDK 尚未与服务器连接，一般是进行发布/订阅相关操作时，没有加入房间，或处在断网状态 |
  | IM_BEFORE_JOIN | `'IM_BEFORE_JOIN'` | 在加入房间之前就发布 IM 消息 |
  | USER_NOT_EXIST | `'USER_NOT_EXIST'` | 用户不存在 |
  | ALREADY_IN_ROOM | `'ALREADY_IN_ROOM'` | 用户已经在房间中 |
  | KICKED_OUT | `'KICKED_OUT'` | 服务端调用 OpenAPI 将当前用户踢出房间 |
  | ROOM_DISMISS | `'ROOM_DISMISS'` | 服务端调用 OpenAPI 解散房间，所有用户被移出房间。 |
  | TOKEN_EXPIRED | `'TOKEN_EXPIRED'` | Token 过期。调用 `joinRoom` 使用新的 Token 重新加入房间。 |
  | DUPLICATE_LOGIN | `'DUPLICATE_LOGIN'` | 相同用户 ID 的用户加入本房间，当前用户被踢出房间 |
  | INVOKED_BEFORE_CAPTURE | `'INVOKED_BEFORE_CAPTURE'` | 截图指定的视频流不存在。 |
  | REPEAT_CAPTURE | `'REPEAT_CAPTURE'` | 重复采集 |
  | GET_VIDEO_TRACK_FAILED | `'GET_VIDEO_TRACK_FAILED'` | 采集视频失败 |
  | GET_AUDIO_TRACK_FAILED | `'GET_AUDIO_TRACK_FAILED'` | 采集音频失败 |
  | GET_SCREEN_TRACK_FAILED | `'GET_SCREEN_TRACK_FAILED'` | 采集屏幕共享失败 |
  | STREAM_TYPE_NOT_MATCH | `'STREAM_TYPE_NOT_MATCH'` | 流类型不匹配，出现于设置了自定义视频流后，打开本地音视频设备 |
  | CANT_FIND_DOM | `'CANT_FIND_DOM'` | 播放视频时，找不到设置的播放窗口 |
  | INVALID_DEVICE_ID | `'INVALID_DEVICE_ID'` | 无效的设备ID |
  | NO_PERMISSION | `'NO_PERMISSION'` | 没有采集权限 |
  | NOT_SUPPORTED | `'NOT_SUPPORTED'` | 浏览器不支持采集 |
  | INTERRUPT | `'INTERRUPT'` |  |
  | ICE_SERVER_WRONG | `'ICE_SERVER_WRONG'` | 请求分配 ICE 节点时失败 |
  | ESTABLISH_DATACHANNEL_FAILED | `'ESTABLISH_DATACHANNEL_FAILED'` | 跟服务器建立 datachannel 连接失败 |
  | LOAD_RESOURCES_FAILED | `'LOAD_RESOURCES_FAILED'` | 加载网络资源失败 |
  | SIGNALING_CHANNEL_NOT_OPEN | `'SIGNALING_CHANNEL_NOT_OPEN'` | 信令通道没有建立 |
  | TIME_OUT | `'TIME_OUT'` | 请求超时 |
  | REFUSE_OPERATION_IN_DISCONNECT | `'REFUSE_OPERATION_IN_DISCONNECT'` | 网络未连接拒绝操作 |
  | ADD_TRANSCEIVER_FAILED | `'ADD_TRANSCEIVER_FAILED'` | 创建 TRANSCEIVER 失败 |
  | UPDATE_TRACK_FAILED | `'UPDATE_TRACK_FAILED'` | 更新发送流失败 |
  | PUBLISH_FAILED | `'PUBLISH_FAILED'` | 发布流失败 |
  | UNPUBLISH_FAILED | `'UNPUBLISH_FAILED'` | 取消发布流失败 |
  | SUBSCRIBE_FAILED | `'SUBSCRIBE_FAILED'` | 订阅失败 |
  | UNSUBSCRIBE_FAILED | `'UNSUBSCRIBE_FAILED'` | 取消订阅失败 |
  | OPERATION_CANCEL | `'OPERATION_CANCEL'` | 发布/订阅等操作执行到一半时离开房间，会触发改错误回调，表示操作被打断，无需处理。 |
  | START_CLOUD_PROXY_AFTER_JOIN | `'START_CLOUD_PROXY_AFTER_JOIN'` | 开启云代理功能需要在加入频道之前调用 |
  | STOP_CLOUD_PROXY_BEFORE_LEAVE | `'STOP_CLOUD_PROXY_BEFORE_LEAVE'` | 关闭云代理功能需要在离开频道之前调用 |
  | UNEXPECTED_ERROR | `'UNEXPECTED_ERROR'` | 未知错误 |
  | REPEAT_DEVICE_TEST | `'REPEAT_DEVICE_TEST'` | 重复调用设备测试 |
  | AUDIO_DEVICE_TEST_FAILED | `'AUDIO_DEVICE_RECORD_FAILED'` | 音频设备测试失败 |
  | ALREADY_LOGIN | `'ALREADY_LOGIN'` | 同名用户已经登录 |
  | LOGIN_FAILED | `'LOGIN_FAILED'` | 登录失败 |
  | NOT_LOGIN | `'NOT_LOGIN'` | 未登录 |
  | RTM_DUPLICATE_LOGIN | `'RTM_DUPLICATE_LOGIN'` | 重复登录 |
  | RTM_TOKEN_ERROR | `'RTM_TOKEN_ERROR'` | 重连 RTM 服务器时使用的 Token 异常 |
  | USER_MESSAGE_TIMEOUT | `'USER_MESSAGE_TIMEOUT'` | 发送超时 |
  | USER_MESSAGE_BROKEN | `'USER_MESSAGE_BROKEN'` | 通道断开，发送失败 |
  | USER_MESSAGE_NO_RECEIVER | `'USER_MESSAGE_NO_RECEIVER'` | 找不到接收者 |
  | USER_MESSAGE_EXCEED_QPS | `'USER_MESSAGE_EXCEED_QPS'` | 超过 QPS 限制 |
  | USER_MESSAGE_SEND_TO_SERVER_ERROR | `'USER_MESSAGE_SEND_TO_SERVER_ERROR'` | 发送到信息到业务服务器无应答，可能是 Http 不通 |
  | USER_MESSAGE_SERVER_RESPONSE_ERROR | `'USER_MESSAGE_SERVER_RESPONSE_ERROR'` | 发送到信息到业务服务器失败，业务服务器 Http 响应状态码不是 `200` |
  | USER_MESSAGE_NOT_JOIN | `'USER_MESSAGE_NOT_JOIN'` | 消息发送方没有加入房间 |
  | USER_MESSAGE_NOT_LOGIN | `'USER_MESSAGE_NOT_LOGIN'` | 房间外或业务服务器消息发送方没有登录 |
  | USER_MESSAGE_SERVER_PARAMS_NOTSET | `'USER_MESSAGE_SERVER_PARAMS_NOTSET'` | 发送消息给业务方服务器之前没有设置参数 |
  | USER_MESSAGE_UNKNOWN | `'USER_MESSAGE_UNKNOWN'` | 即时未知消息错误 |
  | START_PUBLIC_STREAM_BEFORE_JOIN | `'START_PUBLIC_STREAM_BEFORE_JOIN'` | 推流用户没有进入房间。 |
  | RECONNECT_FAILED | `'RECONNECT_FAILED'` | SDK 与服务端重连失败，并不再自动重试，你需退房后重新进房，或联系技术支持。 |
  | SUBTITLE_ALREADY_ON | `'SUBTITLE_ALREADY_ON'` | 字幕已开启，无需重复调用 [startSubtitle](Web-api.md#startsubtitle)。 |
  | SUBTITLE_ERR_POSTPROCESS | `'SUBTITLE_ERR_POSTPROCESS'` | 云端媒体处理内部出现错误，请联系技术支持。 |
  | SUBTITLE_ERR_CONNECTION_ERROR | `'SUBTITLE_ERR_CONNECTION_ERROR'` | 第三方服务连接失败，请联系技术支持。 |
  | SUBTITLE_ERR_PROCESS_ERROR | `'SUBTITLE_ERR_PROCESS_ERROR'` | 云端媒体处理超时未响应，请联系技术支持。 |
  | SUBTITLE_ERR_UNKNOWN | `'SUBTITLE_ERR_UNKNOWN'` | 客户端无法识别云端媒体处理发送的错误码。请联系技术支持。 |
  | UNEXPECTED_INVOKE_FORWARD_STREAM | `'UNEXPECTED_INVOKE_FORWARD_STREAM'` | 跨房间转发媒体流接口调用不符合预期，例如在停止转发状态下再次调用 `stopForwardStreamToRooms`。 |



## AudioMixingError <span id="audiomixingerror"></span>

类型: `enum`

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | AUDIO_MIXING_ERROR_OK | `0` | 混音正常 |
  | AUDIO_MIXING_ERROR_PRELOAD_FAILED | `1` | 预加载失败，找不到混音文件或者文件长度超出 20s |
  | AUDIO_MIXING_ERROR_START_FAILED | `2` | 混音开启失败，找不到混音文件或者混音文件打开失败 |
  | AUDIO_MIXING_ERROR_ID_NOT_FOUND | `3` | 混音 ID 异常 |
  | AUDIO_MIXING_ERROR_SET_POSITION_FAILED | `4` | 设置混音文件的播放位置出错 |
  | AUDIO_MIXING_ERROR_INVALID_VOLUME | `5` | 音量参数不合法，音量值区间应为[0, 400] |
  | AUDIO_MIXING_ERROR_LOAD_CONFLICT | `6` | 播放的文件与预加载的文件不一致，请先使用 `unloadAudioMixing` 卸载文件 |
  | AUDIO_MIXING_ERROR_ID_TYPE_NOT_MATCH | `7` | 混音 ID 类型不匹配，当前操作接口不支持该 ID 代表的音频流类型 |
  | AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH | `8` | 设置混音文件的音调不合法 |
  | AUDIO_MIXING_ERROR_INVALID_AUDIO_TRACK | `9` | 设置混音文件的音轨不合法 |