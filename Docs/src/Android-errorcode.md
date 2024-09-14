---
is_dir: False    # True for dir; False for doc
status: 1    # 0 for offline; 1 for online; 2 for whitelist; 4 for online but hidden in TOC
keywords: 实时音视频    # use ',' as separator
---

<span id="UserMessageSendResult"></span>
# UserMessageSendResult
```java
public class com.ss.bytertc.engine.type.UserMessageSendResult
```
发送消息结果，成功或失败，及失败原因


## 成员变量
| 类型 | 默认值 | 名称 |
| --- | --- | --- |
| int | 0 | [USER_MESSAGE_SEND_RESULT_SUCCESS](#UserMessageSendResult-user_message_send_result_success) |
| int | 1 | [USER_MESSAGE_SEND_RESULT_TIMEOUT](#UserMessageSendResult-user_message_send_result_timeout) |
| int | 2 | [USER_MESSAGE_SEND_RESULT_BROKEN](#UserMessageSendResult-user_message_send_result_broken) |
| int | 3 | [USER_MESSAGE_SEND_RESULT_NO_RECEIVER](#UserMessageSendResult-user_message_send_result_no_receiver) |
| int | 4 | [USER_MESSAGE_SEND_RESULT_NO_RELAY_PATH](#UserMessageSendResult-user_message_send_result_no_relay_path) |
| int | 5 | [USER_MESSAGE_SEND_RESULT_EXCEED_QPS](#UserMessageSendResult-user_message_send_result_exceed_qps) |
| int | 100 | [USER_MESSAGE_SEND_RESULT_NOT_JOIN](#UserMessageSendResult-user_message_send_result_not_join) |
| int | 101 | [USER_MESSAGE_SEND_RESULT_INIT](#UserMessageSendResult-user_message_send_result_init) |
| int | 102 | [USER_MESSAGE_SEND_RESULT_NO_CONNECTION](#UserMessageSendResult-user_message_send_result_no_connection) |
| int | 103 | [USER_MESSAGE_SEND_RESULT_EXCEED_MAX_LENGTH](#UserMessageSendResult-user_message_send_result_exceed_max_length) |
| int | 104 | [USER_MESSAGE_SEND_RESULT_EMPTY_USER](#UserMessageSendResult-user_message_send_result_empty_user) |
| int | 105 | [USER_MESSAGE_SEND_RESULT_NOT_LOGIN](#UserMessageSendResult-user_message_send_result_not_login) |
| int | 106 | [USER_MESSAGE_SEND_RESULT_SERVER_PARAMS_NOT_SET](#UserMessageSendResult-user_message_send_result_server_params_not_set) |
| int | 1000 | [USER_MESSAGE_SEND_RESULT_UNKNOWN](#UserMessageSendResult-user_message_send_result_unknown) |

## 变量说明
<span id="UserMessageSendResult-user_message_send_result_success"></span>
### USER_MESSAGE_SEND_RESULT_SUCCESS
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_SUCCESS = 0
```
发送消息成功


<span id="UserMessageSendResult-user_message_send_result_timeout"></span>
### USER_MESSAGE_SEND_RESULT_TIMEOUT
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_TIMEOUT = 1
```
发送超时，没有发送


<span id="UserMessageSendResult-user_message_send_result_broken"></span>
### USER_MESSAGE_SEND_RESULT_BROKEN
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_BROKEN = 2
```
通道断开，没有发送


<span id="UserMessageSendResult-user_message_send_result_no_receiver"></span>
### USER_MESSAGE_SEND_RESULT_NO_RECEIVER
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_NO_RECEIVER = 3
```
找不到接收方


<span id="UserMessageSendResult-user_message_send_result_no_relay_path"></span>
### USER_MESSAGE_SEND_RESULT_NO_RELAY_PATH
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_NO_RELAY_PATH = 4
```
远端用户没有登录或进房


<span id="UserMessageSendResult-user_message_send_result_exceed_qps"></span>
### USER_MESSAGE_SEND_RESULT_EXCEED_QPS
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_EXCEED_QPS = 5
```
超过 QPS 限制


<span id="UserMessageSendResult-user_message_send_result_not_join"></span>
### USER_MESSAGE_SEND_RESULT_NOT_JOIN
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_NOT_JOIN = 100
```
消息发送方没有加入房间


<span id="UserMessageSendResult-user_message_send_result_init"></span>
### USER_MESSAGE_SEND_RESULT_INIT
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_INIT = 101
```
连接未完成初始化。


<span id="UserMessageSendResult-user_message_send_result_no_connection"></span>
### USER_MESSAGE_SEND_RESULT_NO_CONNECTION
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_NO_CONNECTION = 102
```
没有可用的数据传输通道连接


<span id="UserMessageSendResult-user_message_send_result_exceed_max_length"></span>
### USER_MESSAGE_SEND_RESULT_EXCEED_MAX_LENGTH
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_EXCEED_MAX_LENGTH = 103
```
消息超过最大长度，当前为 64KB。


<span id="UserMessageSendResult-user_message_send_result_empty_user"></span>
### USER_MESSAGE_SEND_RESULT_EMPTY_USER
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_EMPTY_USER = 104
```
接收消息的单个用户 id 为空


<span id="UserMessageSendResult-user_message_send_result_not_login"></span>
### USER_MESSAGE_SEND_RESULT_NOT_LOGIN
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_NOT_LOGIN = 105
```
房间外或应用服务器消息发送方没有登录


<span id="UserMessageSendResult-user_message_send_result_server_params_not_set"></span>
### USER_MESSAGE_SEND_RESULT_SERVER_PARAMS_NOT_SET
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_SERVER_PARAMS_NOT_SET = 106
```
发送消息给业务方服务器之前没有设置参数


<span id="UserMessageSendResult-user_message_send_result_unknown"></span>
### USER_MESSAGE_SEND_RESULT_UNKNOWN
```java
public static final int com.ss.bytertc.engine.type.UserMessageSendResult.USER_MESSAGE_SEND_RESULT_UNKNOWN = 1000
```
未知错误


<span id="ByteRTCStreamSinglePushEvent"></span>
# ByteRTCStreamSinglePushEvent
```java
public enum com.ss.bytertc.engine.live.ByteRTCStreamSinglePushEvent
```
单流转推直播错误码


## 枚举值
| 类型 | 值 | 说明 |
| --- | --- | --- |
| SINGLE_STREAM_PUSH_START | 1 | 开始推流。 |
| SINGLE_STREAM_PUSH_SUCCESS | 2 | 推流成功。 |
| SINGLE_STREAM_PUSH_FAILED | 3 | 推流失败。 |
| SINGLE_STREAM_PUSH_STOP | 4 | 停止推流。 |
| SINGLE_STREAM_PUSH_TIMEOUT | 5 | 单流转推直播任务处理超时，请检查网络状态并重试。 |
| SINGLE_STREAM_PUSH_PARAM_ERROR | 6 | 参数错误。 |

<span id="ByteRTCTranscoderErrorCode"></span>
# ByteRTCTranscoderErrorCode
```java
public enum com.ss.bytertc.engine.live.ByteRTCTranscoderErrorCode
```
转推直播错误码


## 枚举值
| 类型 | 值 | 说明 |
| --- | --- | --- |
| TRANSCODER_ERROR_OK | 0 | 推流成功。 |
| TRANSCODER_ERROR_BASE | 1090 | 未定义的合流错误 |
| TRANSCODER_ERROR_INVALID_PARAM | 1091 | 客户端 SDK 检测到无效推流参数。 |
| TRANSCODER_ERROR_INVALID_STATE | 1092 | 状态错误，需要在状态机正常状态下发起操作 |
| TRANSCODER_ERROR_INVALID_OPERATOR | 1093 | 无效操作 |
| TRANSCODER_ERROR_TIMEOUT | 1094 | 转推直播任务处理超时，请检查网络状态并重试 |
| TRANSCODER_ERROR_INVALID_PARAM_BY_SERVER | 1095 | 服务端检测到错误的推流参数 |
| TRANSCODER_ERROR_SUB_TIMEOUT_BY_SERVER | 1096 | 对流的订阅超时 |
| TRANSCODER_ERROR_INVALID_STATE_BY_SERVER | 1097 | 合流服务端内部错误。 |
| TRANSCODER_ERROR_AUTHENTICATION_BY_CDN | 1098 | 合流服务端推 CDN 失败。 |
| TRANSCODER_ERROR_TIMEOUT_BY_SIGNALING | 1099 | 服务端接收信令超时，请检查网络状态并重试。 |
| TRANSCODER_ERROR_MIX_IMAGE_FAIL | 1100 | 图片合流失败。 |
| TRANSCODER_ERROR_UNKNOW_ERROR_BY_SERVER | 1101 | 服务端未知错误。 |

## 成员函数
| 返回 | 名称 |
| --- | --- |
| ByteRTCTranscoderErrorCode | [ByteRTCTranscoderErrorCode](#ByteRTCTranscoderErrorCode-bytertctranscodererrorcode) |

## 函数说明
<span id="ByteRTCTranscoderErrorCode-bytertctranscodererrorcode"></span>
### ByteRTCTranscoderErrorCode
```java
com.ss.bytertc.engine.live.ByteRTCTranscoderErrorCode.ByteRTCTranscoderErrorCode(int value)
```

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| value | int | - |


<span id="AudioRecordingErrorCode"></span>
# AudioRecordingErrorCode
```java
public enum com.ss.bytertc.engine.type.AudioRecordingErrorCode
```
音频文件录制的错误码


## 枚举值
| 类型 | 值 | 说明 |
| --- | --- | --- |
| AUDIO_RECORDING_ERROR_CODE_OK | 0 | 录制正常 |
| AUDIO_RECORDING_ERROR_CODE_NO_PERMISSION | -1 | 没有文件写权限 |
| AUDIO_RECORDING_ERROR_CODE_NOT_IN_ROOM | -2 | 没有进入房间 |
| AUDIO_RECORDING_ERROR_CODE_ALREADY_STARTED | -3 | 录制已经开始 |
| AUDIO_RECORDING_ERROR_CODE_NOT_STARTED | -4 | 录制还未开始 |
| AUDIO_RECORDING_ERROR_CODE_NOT_SUPPORT | -5 | 录制失败。文件格式不支持。 |
| AUDIO_RECORDING_ERROR_CODE_OTHER | -6 | 其他异常 |

<span id="KTVErrorCode"></span>
# KTVErrorCode
```java
public enum com.ss.bytertc.ktv.data.KTVErrorCode
```
KTV 错误码。


## 枚举值
| 类型 | 值 | 说明 |
| --- | --- | --- |
| OK | 0 | 成功。 |
| APPID_INVALID | -3000 | AppID 异常。 |
| PARAS_INVALID | -3001 | 非法参数，传入的参数不正确。 |
| GET_MUSIC_FAILED | -3002 | 获取歌曲资源失败。 |
| GET_LYRIC_FAILED | -3003 | 获取歌词失败。 |
| MUSIC_TAKEDOWN | -3004 | 歌曲下架。 |
| MUSIC_DOWNLOAD | -3005 | 歌曲文件下载失败。 |
| MIDI_DOWNLOAD_FAILED | -3006 | MIDI 文件下载失败。 |
| SYSTEM_BUSY | -3007 | 系统繁忙。 |
| NETWORK | -3008 | 网络异常。 |
| NOT_JOIN_ROOM | -3009 | KTV 功能未加入房间。 |
| PARSE_DATA | -3010 | 解析数据失败。 |
| DOWNLOADING | -3012 | 已在下载中。 |
| INTERNAL_DOMAIN | -3013 | 内部错误，联系技术支持人员。 |
| INSUFFICIENT_DISK_SPACE | -3014 | 下载失败，磁盘空间不足。清除缓存后重试。 |
| MUSIC_DECRYPTION_FAILED | -3015 | 下载失败，音乐文件解密失败，联系技术支持人员。 |
| FILE_RENAME_FAILED | -3016 | 下载失败，音乐文件重命名失败，请重试。 |
| DOWNLOAD_TIMEOUT | -3017 | 下载失败，下载超时，请重试。 |
| CLEAR_CACHE_FAILED | -3018 | 清除缓存失败，可能原因是文件被占用或者系统异常，请重试。 |
| DOWNLOAD_CANCELED | -3019 | 取消下载。 |

<span id="PublicStreamErrorCode"></span>
# PublicStreamErrorCode
```java
public enum com.ss.bytertc.engine.type.PublicStreamErrorCode
```
公共流状态码


## 枚举值
| 类型 | 值 | 说明 |
| --- | --- | --- |
| ERROR_CODE_SUCCESS | 0 | 发布或订阅成功。 |
| ERROR_CODE_PUSH_PARAM_ERROR | 1191 | 公共流的参数异常，请修改参数后重试。 |
| ERROR_CODE_PUSH_STATE_ERROR | 1192 | 服务端状态异常，将自动重试。 |
| ERROR_CODE_PUSH_INTERNAL_ERROR | 1193 | 内部错误，不可恢复，请重试。 |
| ERROR_CODE_PUSH_ERROR | 1195 | 发布失败，将自动重试，请关注重试结果。 |
| ERROR_CODE_PUSH_TIMEOUT | 1196 | 发布失败，10 s 后会重试，重试 3 次后自动停止。 |
| ERROR_CODE_PULL_NO_PUSH_STREAM | 1300 | 订阅失败，发布端未开始发布流。 |

<span id="SubtitleErrorCode"></span>
# SubtitleErrorCode
```java
public enum com.ss.bytertc.engine.type.SubtitleErrorCode
```
字幕任务错误码。


## 枚举值
| 类型 | 值 | 说明 |
| --- | --- | --- |
| SUBTITLE_ERROR_CODE_UNKNOW | -1 | 客户端无法识别云端媒体处理发送的错误码。请联系技术支持。 |
| SUBTITLE_ERROR_CODE_SUCCESS | 0 | 字幕已开启。 |
| SUBTITLE_ERROR_CODE_POST_PROCESS_ERROR | 1 | 云端媒体处理内部出现错误，请联系技术支持。 |
| SUBTITLE_ERROR_CODE_ASR_CONNECTION_ERROR | 2 | 第三方服务连接失败，请联系技术支持。 |
| SUBTITLE_ERROR_CODE_ASR_SERVICE_ERROR | 3 | 第三方服务内部出现错误，请联系技术支持。 |
| SUBTITLE_ERROR_CODE_BEFORE_JOIN_ROOM | 4 | 未进房导致调用`startSubtitle`失败。请加入房间后再调用此方法。 |
| SUBTITLE_ERROR_CODE_ALREADY_ON | 5 | 字幕已开启，无需重复调用 `startSubtitle`。 |
| SUBTITLE_ERROR_CODE_UNSUPPORTED_LANGUAGE | 6 | 你选择的目标语言目前暂不支持。 |
| SUBTITLE_ERROR_CODE_POST_PROCESS_TIMEOUT | 7 | 云端媒体处理超时未响应，请联系技术支持。 |

<span id="ErrorCode"></span>
# ErrorCode
```java
public class com.ss.bytertc.engine.type.ErrorCode
```
回调错误码。

SDK 内部遇到不可恢复的错误时，会通过 `onError` 回调通知用户。


## 成员变量
| 类型 | 默认值 | 名称 |
| --- | --- | --- |
| int | -1000 | [ERROR_CODE_INVALID_TOKEN](#ErrorCode-error_code_invalid_token) |
| int | -1001 | [ERROR_CODE_JOIN_ROOM](#ErrorCode-error_code_join_room) |
| int | -1002 | [ERROR_CODE_NO_PUBLISH_PERMISSION](#ErrorCode-error_code_no_publish_permission) |
| int | -1003 | [ERROR_CODE_NO_SUBSCRIBE_PERMISSION](#ErrorCode-error_code_no_subscribe_permission) |
| int | -1004 | [ERROR_CODE_DUPLICATE_LOGIN](#ErrorCode-error_code_duplicate_login) |
| int | -1005 | [ERROR_CODE_APP_ID_NULL](#ErrorCode-error_code_app_id_null) |
| int | -1006 | [ERROR_CODE_KICKED_OUT](#ErrorCode-error_code_kicked_out) |
| int | -1007 | [ERROR_CODE_ROOM_ID_ILLEGAL](#ErrorCode-error_code_room_id_illegal) |
| int | -1009 | [ERROR_CODE_TOKEN_EXPIRED](#ErrorCode-error_code_token_expired) |
| int | -1010 | [ERROR_CODE_UPDATE_TOKEN_WITH_INVALID_TOKEN](#ErrorCode-error_code_update_token_with_invalid_token) |
| int | -1011 | [ERROR_CODE_ROOM_DISMISS](#ErrorCode-error_code_room_dismiss) |
| int | -1013 | [ERROR_CODE_ROOM_ALREADY_EXIST](#ErrorCode-error_code_room_already_exist) |
| int | -1014 | [ERROR_CODE_USER_ID_DIFFERENT](#ErrorCode-error_code_user_id_different) |
| int | -1025 | [ERROR_CODE_JOIN_ROOM_ROOM_FORBIDDEN](#ErrorCode-error_code_join_room_room_forbidden) |
| int | -1026 | [ERROR_CODE_JOIN_ROOM_USER_FORBIDDEN](#ErrorCode-error_code_join_room_user_forbidden) |
| int | -1070 | [ERROR_CODE_OVER_SUBSCRIBE_LIMIT](#ErrorCode-error_code_over_subscribe_limit) |
| int | -1080 | [ERROR_CODE_OVER_STREAM_PUBLISH_LIMIT](#ErrorCode-error_code_over_stream_publish_limit) |
| int | -1083 | [ERROR_CODE_INVALID_AUDIO_SYNC_USERID_REPEATED](#ErrorCode-error_code_invalid_audio_sync_userid_repeated) |
| int | -1084 | [ERROR_CODE_ABNORMAL_SERVER_STATUS](#ErrorCode-error_code_abnormal_server_status) |
| int | -1081 | [deprecated] [ERROR_CODE_OVER_SCREEN_PUBLISH_LIMIT](#ErrorCode-error_code_over_screen_publish_limit) |
| int | -1082 | [deprecated] [ERROR_CODE_OVER_VIDEO_PUBLISH_LIMIT](#ErrorCode-error_code_over_video_publish_limit) |

## 变量说明
<span id="ErrorCode-error_code_invalid_token"></span>
### ERROR_CODE_INVALID_TOKEN
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_INVALID_TOKEN = -1000
```
Token 无效。

进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用 `updateToken` 方法更新 Token。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_join_room"></span>
### ERROR_CODE_JOIN_ROOM
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_JOIN_ROOM = -1001
```
加入房间错误。

进房时发生未知错误导致加入房间失败。需要用户重新加入房间。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_no_publish_permission"></span>
### ERROR_CODE_NO_PUBLISH_PERMISSION
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_NO_PUBLISH_PERMISSION = -1002
```
没有发布音视频流权限。

用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="ErrorCode-error_code_no_subscribe_permission"></span>
### ERROR_CODE_NO_SUBSCRIBE_PERMISSION
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_NO_SUBSCRIBE_PERMISSION = -1003
```
没有订阅音视频流权限。

用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="ErrorCode-error_code_duplicate_login"></span>
### ERROR_CODE_DUPLICATE_LOGIN
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_DUPLICATE_LOGIN = -1004
```
相同用户 ID 的用户加入本房间，当前用户被踢出房间。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_app_id_null"></span>
### ERROR_CODE_APP_ID_NULL
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_APP_ID_NULL = -1005
```
App ID 参数异常。

创建引擎时传入的 App ID 参数为空。


<span id="ErrorCode-error_code_kicked_out"></span>
### ERROR_CODE_KICKED_OUT
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_KICKED_OUT = -1006
```
服务端调用 OpenAPI 将当前用户踢出房间。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_room_id_illegal"></span>
### ERROR_CODE_ROOM_ID_ILLEGAL
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_ROOM_ID_ILLEGAL = -1007
```
当调用 `createRoom` ，如果 roomId 非法，会返回 null，并抛出该错误。通过 [onCreateRoomStateChanged](Android-callback#IRTCVideoEventHandler-oncreateroomstatechanged) 回调。


<span id="ErrorCode-error_code_token_expired"></span>
### ERROR_CODE_TOKEN_EXPIRED
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_TOKEN_EXPIRED = -1009
```
Token 过期。调用 `joinRoom` 使用新的 Token 重新加入房间。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_update_token_with_invalid_token"></span>
### ERROR_CODE_UPDATE_TOKEN_WITH_INVALID_TOKEN
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_UPDATE_TOKEN_WITH_INVALID_TOKEN = -1010
```
调用 `updateToken` 传入的 Token 无效。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_room_dismiss"></span>
### ERROR_CODE_ROOM_DISMISS
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_ROOM_DISMISS = -1011
```
服务端调用 OpenAPI 解散房间，所有用户被移出房间。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_room_already_exist"></span>
### ERROR_CODE_ROOM_ALREADY_EXIST
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_ROOM_ALREADY_EXIST = -1013
```
通话回路检测已经存在同样 roomId 的房间了。通过 [onCreateRoomStateChanged](Android-callback#IRTCVideoEventHandler-oncreateroomstatechanged) 回调。


<span id="ErrorCode-error_code_user_id_different"></span>
### ERROR_CODE_USER_ID_DIFFERENT
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_USER_ID_DIFFERENT = -1014
```
加入多个房间时使用了不同的 uid。

同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_join_room_room_forbidden"></span>
### ERROR_CODE_JOIN_ROOM_ROOM_FORBIDDEN
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_JOIN_ROOM_ROOM_FORBIDDEN = -1025
```
房间被封禁。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_join_room_user_forbidden"></span>
### ERROR_CODE_JOIN_ROOM_USER_FORBIDDEN
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_JOIN_ROOM_USER_FORBIDDEN = -1026
```
用户被封禁。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_over_subscribe_limit"></span>
### ERROR_CODE_OVER_SUBSCRIBE_LIMIT
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_OVER_SUBSCRIBE_LIMIT = -1070
```
订阅音视频流失败，订阅音视频流总数超过上限。

游戏场景下为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流的总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="ErrorCode-error_code_over_stream_publish_limit"></span>
### ERROR_CODE_OVER_STREAM_PUBLISH_LIMIT
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_OVER_STREAM_PUBLISH_LIMIT = -1080
```
发布流失败，发布流总数超过上限。

RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="ErrorCode-error_code_invalid_audio_sync_userid_repeated"></span>
### ERROR_CODE_INVALID_AUDIO_SYNC_USERID_REPEATED
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_INVALID_AUDIO_SYNC_USERID_REPEATED = -1083
```
音视频同步失败。

当前音频源已与其他视频源关联同步关系。

单个音频源不支持与多个视频源同时同步。

通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="ErrorCode-error_code_abnormal_server_status"></span>
### ERROR_CODE_ABNORMAL_SERVER_STATUS
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_ABNORMAL_SERVER_STATUS = -1084
```
服务端异常状态导致退出房间。

SDK 与信令服务器断开，并不再自动重连，可联系技术支持。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="ErrorCode-error_code_over_screen_publish_limit"></span>
### ERROR_CODE_OVER_SCREEN_PUBLISH_LIMIT
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_OVER_SCREEN_PUBLISH_LIMIT = -1081
```
> Deprecated since 3.52, use ERROR_CODE_OVER_STREAM_PUBLISH_LIMIT(-1080) instead

发布屏幕流失败，发布流总数超过上限。

RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。


<span id="ErrorCode-error_code_over_video_publish_limit"></span>
### ERROR_CODE_OVER_VIDEO_PUBLISH_LIMIT
```java
public static final int com.ss.bytertc.engine.type.ErrorCode.ERROR_CODE_OVER_VIDEO_PUBLISH_LIMIT = -1082
```
> Deprecated since 3.52, use ERROR_CODE_OVER_STREAM_PUBLISH_LIMIT(-1080) instead

发布视频流总数超过上限。

RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。


<span id="WarningCode"></span>
# WarningCode
```java
public class com.ss.bytertc.engine.type.WarningCode
```
回调警告码。

警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。


## 成员变量
| 类型 | 默认值 | 名称 |
| --- | --- | --- |
| int | -2001 | [WARNING_CODE_JOIN_ROOM_FAILED](#WarningCode-warning_code_join_room_failed) |
| int | -2002 | [WARNING_CODE_PUBLISH_STREAM_FAILED](#WarningCode-warning_code_publish_stream_failed) |
| int | -2003 | [WARNING_CODE_SUBSCRIBE_STREAM_FAILED404](#WarningCode-warning_code_subscribe_stream_failed404) |
| int | -2004 | [WARNING_CODE_SUBSCRIBE_STREAM_FAILED5XX](#WarningCode-warning_code_subscribe_stream_failed5xx) |
| int | -2009 | [WARNING_CODE_PUBLISH_STREAM_FORBIDEN](#WarningCode-warning_code_publish_stream_forbiden) |
| int | -2011 | [WARNING_CODE_SEND_CUSTOM_MESSAGE](#WarningCode-warning_code_send_custom_message) |
| int | -2013 | [WARNING_CODE_RECEIVE_USER_NOTIFY_STOP](#WarningCode-warning_code_receive_user_notify_stop) |
| int | -2014 | [WARNING_CODE_USER_IN_PUBLISH](#WarningCode-warning_code_user_in_publish) |
| int | -2016 | [WARNING_CODE_OLD_ROOM_BEEN_REPLACED](#WarningCode-warning_code_old_room_been_replaced) |
| int | -2017 | [WARNING_CODE_IN_ECHO_TEST_MODE](#WarningCode-warning_code_in_echo_test_mode) |
| int | -5001 | [WARNING_CODE_NO_CAMERA_PERMISSION](#WarningCode-warning_code_no_camera_permission) |
| int | -5009 | [WARNING_CODE_SET_SCREEN_AUDIO_SOURCE_TYPE_FAILED](#WarningCode-warning_code_set_screen_audio_source_type_failed) |
| int | -5010 | [WARNING_CODE_SET_SCREEN_STREAM_INDEX_FAILED](#WarningCode-warning_code_set_screen_stream_index_failed) |
| int | -5011 | [WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH](#WarningCode-warning_code_set_screen_stream_invalid_voice_pitch) |
| int | -5013 | [WARNING_CODE_INVALID_CALL_FOR_EXT_AUDIO](#WarningCode-warning_code_invalid_call_for_ext_audio) |
| int | -7002 | [WARNING_CODE_INVALID_SAMI_APPKEY_OR_TOKEN](#WarningCode-warning_code_invalid_sami_appkey_or_token) |
| int | -7003 | [WARNING_CODE_INVALID_RESOURCE_PATH](#WarningCode-warning_code_invalid_resource_path) |
| int | -7004 | [WARNING_CODE_LOAD_SAMI_LIBRARY_FAILED](#WarningCode-warning_code_load_sami_library_failed) |
| int | -7005 | [WARNING_CODE_INVALID_SAMI_EFFECT_TYPE](#WarningCode-warning_code_invalid_sami_effect_type) |
| int | -2000 | [deprecated] [WARNING_CODE_GET_ROOM_FAILED](#WarningCode-warning_code_get_room_failed) |
| int | -2010 | [deprecated] [WARNING_CODE_SUBSCRIBE_STREAM_FORBIDEN](#WarningCode-warning_code_subscribe_stream_forbiden) |
| int | -2015 | [deprecated] [WARNING_CODE_ROOM_ID_ALREADY_EXIST](#WarningCode-warning_code_room_id_already_exist) |
| int | -5002 | [deprecated] [WARNING_CODE_NO_MICROPHONE_PERMISSION](#WarningCode-warning_code_no_microphone_permission) |
| int | -5003 | [deprecated] [WARNING_CODE_RECODING_DEVICE_START_FAILED](#WarningCode-warning_code_recoding_device_start_failed) |
| int | -5004 | [deprecated] [WARNING_CODE_PLAYOUT_DEVICE_START_FAILED](#WarningCode-warning_code_playout_device_start_failed) |
| int | -5005 | [deprecated] [WARNING_CODE_NO_RECORDING_DEVICE](#WarningCode-warning_code_no_recording_device) |
| int | -5006 | [deprecated] [WARNING_CODE_NO_PLAYOUT_DEVICE](#WarningCode-warning_code_no_playout_device) |
| int | -5007 | [deprecated] [WARNING_CODE_RECORDING_SILENCE](#WarningCode-warning_code_recording_silence) |
| int | -5008 | [deprecated] [WARNING_CODE_MEDIA_DEVICE_OPERATION_DENIED](#WarningCode-warning_code_media_device_operation_denied) |

## 变量说明
<span id="WarningCode-warning_code_join_room_failed"></span>
### WARNING_CODE_JOIN_ROOM_FAILED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_JOIN_ROOM_FAILED = -2001
```
进房失败。

初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="WarningCode-warning_code_publish_stream_failed"></span>
### WARNING_CODE_PUBLISH_STREAM_FAILED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_PUBLISH_STREAM_FAILED = -2002
```
发布音视频流失败。

当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="WarningCode-warning_code_subscribe_stream_failed404"></span>
### WARNING_CODE_SUBSCRIBE_STREAM_FAILED404
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_SUBSCRIBE_STREAM_FAILED404 = -2003
```
订阅音视频流失败。

当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="WarningCode-warning_code_subscribe_stream_failed5xx"></span>
### WARNING_CODE_SUBSCRIBE_STREAM_FAILED5XX
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_SUBSCRIBE_STREAM_FAILED5XX = -2004
```
订阅音视频流失败。

当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="WarningCode-warning_code_publish_stream_forbiden"></span>
### WARNING_CODE_PUBLISH_STREAM_FORBIDEN
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_PUBLISH_STREAM_FORBIDEN = -2009
```
当调用 `setUserVisibility` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="WarningCode-warning_code_send_custom_message"></span>
### WARNING_CODE_SEND_CUSTOM_MESSAGE
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_SEND_CUSTOM_MESSAGE = -2011
```
发送自定义广播消息失败, 当前你未在房间中。


<span id="WarningCode-warning_code_receive_user_notify_stop"></span>
### WARNING_CODE_RECEIVE_USER_NOTIFY_STOP
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_RECEIVE_USER_NOTIFY_STOP = -2013
```
当房间内人数超过 500 人时，停止向房间内已有用户发送 `onUserJoined` 和 `onUserLeave` 回调，并通过广播提示房间内所有用户。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="WarningCode-warning_code_user_in_publish"></span>
### WARNING_CODE_USER_IN_PUBLISH
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_USER_IN_PUBLISH = -2014
```
用户已经在其他房间发布过流，或者用户正在发布公共流。通过 [onStreamStateChanged](Android-callback#IRTCRoomEventHandler-onstreamstatechanged) 回调。


<span id="WarningCode-warning_code_old_room_been_replaced"></span>
### WARNING_CODE_OLD_ROOM_BEEN_REPLACED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_OLD_ROOM_BEEN_REPLACED = -2016
```
已存在相同 roomId 的房间，新创建的房间实例已替换旧房间实例。通过 [onRoomStateChanged](Android-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。


<span id="WarningCode-warning_code_in_echo_test_mode"></span>
### WARNING_CODE_IN_ECHO_TEST_MODE
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_IN_ECHO_TEST_MODE = -2017
```
当前正在进行回路测试，该接口调用无效


<span id="WarningCode-warning_code_no_camera_permission"></span>
### WARNING_CODE_NO_CAMERA_PERMISSION
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_NO_CAMERA_PERMISSION = -5001
```
摄像头权限异常，当前应用没有获取摄像头权限。


<span id="WarningCode-warning_code_set_screen_audio_source_type_failed"></span>
### WARNING_CODE_SET_SCREEN_AUDIO_SOURCE_TYPE_FAILED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_SET_SCREEN_AUDIO_SOURCE_TYPE_FAILED = -5009
```
不支持在 [publishScreen](Android-api#RTCRoom-publishscreen) 之后，调用 [setScreenAudioSourceType](Android-api#RTCVideo-setscreenaudiosourcetype) 设置屏幕音频采集类型


<span id="WarningCode-warning_code_set_screen_stream_index_failed"></span>
### WARNING_CODE_SET_SCREEN_STREAM_INDEX_FAILED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_SET_SCREEN_STREAM_INDEX_FAILED = -5010
```
不支持在 [publishScreen](Android-api#RTCRoom-publishscreen) 之后，调用 [setScreenAudioStreamIndex](Android-api#RTCVideo-setscreenaudiostreamindex) 设置屏幕音频共享发布类型


<span id="WarningCode-warning_code_set_screen_stream_invalid_voice_pitch"></span>
### WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH = -5011
```
设置语音音高不合法


<span id="WarningCode-warning_code_invalid_call_for_ext_audio"></span>
### WARNING_CODE_INVALID_CALL_FOR_EXT_AUDIO
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_INVALID_CALL_FOR_EXT_AUDIO = -5013
```
外部音频源新旧接口混用


<span id="WarningCode-warning_code_invalid_sami_appkey_or_token"></span>
### WARNING_CODE_INVALID_SAMI_APPKEY_OR_TOKEN
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_INVALID_SAMI_APPKEY_OR_TOKEN = -7002
```
[音频技术](https://www.volcengine.com/docs/6489/71986) SDK 鉴权失效。联系技术支持人员。


<span id="WarningCode-warning_code_invalid_resource_path"></span>
### WARNING_CODE_INVALID_RESOURCE_PATH
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_INVALID_RESOURCE_PATH = -7003
```
[音频技术](https://www.volcengine.com/docs/6489/71986) 资源加载失败。传入正确的 DAT 路径，或联系技术支持人员。


<span id="WarningCode-warning_code_load_sami_library_failed"></span>
### WARNING_CODE_LOAD_SAMI_LIBRARY_FAILED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_LOAD_SAMI_LIBRARY_FAILED = -7004
```
[音频技术](https://www.volcengine.com/docs/6489/71986) 库加载失败。使用正确的库，或联系技术支持人员。


<span id="WarningCode-warning_code_invalid_sami_effect_type"></span>
### WARNING_CODE_INVALID_SAMI_EFFECT_TYPE
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_INVALID_SAMI_EFFECT_TYPE = -7005
```
[音频技术](https://www.volcengine.com/docs/6489/71986) 不支持此音效。联系技术支持人员。


<span id="WarningCode-warning_code_get_room_failed"></span>
### WARNING_CODE_GET_ROOM_FAILED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_GET_ROOM_FAILED = -2000
```
> Deprecated since 3.45 and will be deleted in 3.51.

获取房间信息失败警告


**注意**

SDK 获取房间信息失败（包含超时，返回非 200 的错误码），每隔两秒重试一次。

连续失败 5 次后，报该 warning，并继续重试。

建议提示用户：进入房间失败，请稍后再试

<span id="WarningCode-warning_code_subscribe_stream_forbiden"></span>
### WARNING_CODE_SUBSCRIBE_STREAM_FORBIDEN
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_SUBSCRIBE_STREAM_FORBIDEN = -2010
```
> Deprecated since 3.45 and will be deleted in 3.51.

自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。

你需在进房前关闭自动订阅模式，再调用 [subscribeUserStream](Android-api#RTCRoom-subscribeuserstream) 方法手动订阅音视频流。


<span id="WarningCode-warning_code_room_id_already_exist"></span>
### WARNING_CODE_ROOM_ID_ALREADY_EXIST
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_ROOM_ID_ALREADY_EXIST = -2015
```
> Deprecated since 3.45 and will be deleted in 3.51.

已存在同样 roomId 的房间。


<span id="WarningCode-warning_code_no_microphone_permission"></span>
### WARNING_CODE_NO_MICROPHONE_PERMISSION
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_NO_MICROPHONE_PERMISSION = -5002
```
> Deprecated since 3.33 and will be deleted in 3.51, use [MediaDeviceError](Android-keytype#MediaDeviceError).MEDIA_DEVICE_ERROR_NOPERMISSION instead.

麦克风权限异常，当前应用没有获取麦克风权限。


<span id="WarningCode-warning_code_recoding_device_start_failed"></span>
### WARNING_CODE_RECODING_DEVICE_START_FAILED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_RECODING_DEVICE_START_FAILED = -5003
```
> Deprecated since 3.33 and will be deleted in 3.51, use [MediaDeviceError](Android-keytype#MediaDeviceError).MEDIA_DEVICE_ERROR_DEVICEFAILURE instead.

音频采集设备启动失败。

启动音频采集设备失败，当前设备可能被其他应用占用。


<span id="WarningCode-warning_code_playout_device_start_failed"></span>
### WARNING_CODE_PLAYOUT_DEVICE_START_FAILED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_PLAYOUT_DEVICE_START_FAILED = -5004
```
> Deprecated since 3.33 and will be deleted in 3.51, use [MediaDeviceError](Android-keytype#MediaDeviceError).MEDIA_DEVICE_ERROR_DEVICEFAILURE instead.

音频播放设备启动失败警告。

可能由于系统资源不足，或参数错误。


<span id="WarningCode-warning_code_no_recording_device"></span>
### WARNING_CODE_NO_RECORDING_DEVICE
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_NO_RECORDING_DEVICE = -5005
```
> Deprecated since 3.33 and will be deleted in 3.51, use [MediaDeviceError](Android-keytype#MediaDeviceError).MEDIA_DEVICE_ERROR_DEVICENOTFOUND instead.

无可用音频采集设备。

启动音频采集设备失败，请插入可用的音频采集设备。


<span id="WarningCode-warning_code_no_playout_device"></span>
### WARNING_CODE_NO_PLAYOUT_DEVICE
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_NO_PLAYOUT_DEVICE = -5006
```
> Deprecated since 3.33 and will be deleted in 3.51, use [MediaDeviceError](Android-keytype#MediaDeviceError).MEDIA_DEVICE_ERROR_DEVICENOTFOUND instead.

无可用音频播放设备。

启动音频播放设备失败，请插入可用的音频播放设备。


<span id="WarningCode-warning_code_recording_silence"></span>
### WARNING_CODE_RECORDING_SILENCE
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_RECORDING_SILENCE = -5007
```
> Deprecated since 3.33 and will be deleted in 3.51, use [MediaDeviceWarning](Android-keytype#MediaDeviceWarning).MEDIA_DEVICE_WARNING_CAPTURE_SILENCE instead.

当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。


<span id="WarningCode-warning_code_media_device_operation_denied"></span>
### WARNING_CODE_MEDIA_DEVICE_OPERATION_DENIED
```java
public static final int com.ss.bytertc.engine.type.WarningCode.WARNING_CODE_MEDIA_DEVICE_OPERATION_DENIED = -5008
```
> Deprecated since 3.33 and will be deleted in 3.51, use [MediaDeviceWarning](Android-keytype#MediaDeviceWarning).MEDIA_DEVICE_WARNING_OPERATION_DENIED instead.

媒体设备误操作警告。

使用自定义采集时，不可调用内部采集开关，调用时将触发此警告。


<span id="RoomMessageSendResult"></span>
# RoomMessageSendResult
```java
public class com.ss.bytertc.engine.type.RoomMessageSendResult
```
房间内群发消息结果


## 成员变量
| 类型 | 默认值 | 名称 |
| --- | --- | --- |
| int | 200 | [ROOM_MESSAGE_SEND_RESULT_SUCCESS](#RoomMessageSendResult-room_message_send_result_success) |
| int | 5 | [ROOM_MESSAGE_SEND_RESULT_EXCEED_QPS](#RoomMessageSendResult-room_message_send_result_exceed_qps) |
| int | 100 | [ROOM_MESSAGE_SEND_RESULT_NOT_JOIN](#RoomMessageSendResult-room_message_send_result_not_join) |
| int | 101 | [ROOM_MESSAGE_SEND_RESULT_INIT](#RoomMessageSendResult-room_message_send_result_init) |
| int | 102 | [ROOM_MESSAGE_SEND_RESULT_NO_CONNECTION](#RoomMessageSendResult-room_message_send_result_no_connection) |
| int | 103 | [ROOM_MESSAGE_SEND_RESULT_EXCEED_MAX_LENGTH](#RoomMessageSendResult-room_message_send_result_exceed_max_length) |
| int | 1000 | [ROOM_MESSAGE_SEND_RESULT_UNKNOWN](#RoomMessageSendResult-room_message_send_result_unknown) |

## 变量说明
<span id="RoomMessageSendResult-room_message_send_result_success"></span>
### ROOM_MESSAGE_SEND_RESULT_SUCCESS
```java
public static final int com.ss.bytertc.engine.type.RoomMessageSendResult.ROOM_MESSAGE_SEND_RESULT_SUCCESS = 200
```
发送成功


<span id="RoomMessageSendResult-room_message_send_result_exceed_qps"></span>
### ROOM_MESSAGE_SEND_RESULT_EXCEED_QPS
```java
public static final int com.ss.bytertc.engine.type.RoomMessageSendResult.ROOM_MESSAGE_SEND_RESULT_EXCEED_QPS = 5
```
超过 QPS 限制


<span id="RoomMessageSendResult-room_message_send_result_not_join"></span>
### ROOM_MESSAGE_SEND_RESULT_NOT_JOIN
```java
public static final int com.ss.bytertc.engine.type.RoomMessageSendResult.ROOM_MESSAGE_SEND_RESULT_NOT_JOIN = 100
```
发送失败。消息发送方没有加入房间。


<span id="RoomMessageSendResult-room_message_send_result_init"></span>
### ROOM_MESSAGE_SEND_RESULT_INIT
```java
public static final int com.ss.bytertc.engine.type.RoomMessageSendResult.ROOM_MESSAGE_SEND_RESULT_INIT = 101
```
发送失败。连接未完成初始化。


<span id="RoomMessageSendResult-room_message_send_result_no_connection"></span>
### ROOM_MESSAGE_SEND_RESULT_NO_CONNECTION
```java
public static final int com.ss.bytertc.engine.type.RoomMessageSendResult.ROOM_MESSAGE_SEND_RESULT_NO_CONNECTION = 102
```
发送失败。没有可用的数据传输通道连接


<span id="RoomMessageSendResult-room_message_send_result_exceed_max_length"></span>
### ROOM_MESSAGE_SEND_RESULT_EXCEED_MAX_LENGTH
```java
public static final int com.ss.bytertc.engine.type.RoomMessageSendResult.ROOM_MESSAGE_SEND_RESULT_EXCEED_MAX_LENGTH = 103
```
发送失败。消息超过最大长度 64KB。


<span id="RoomMessageSendResult-room_message_send_result_unknown"></span>
### ROOM_MESSAGE_SEND_RESULT_UNKNOWN
```java
public static final int com.ss.bytertc.engine.type.RoomMessageSendResult.ROOM_MESSAGE_SEND_RESULT_UNKNOWN = 1000
```
发送失败。未知错误


<span id="LoginErrorCode"></span>
# LoginErrorCode
```java
public class com.ss.bytertc.engine.type.LoginErrorCode
```
登录结果

调用 `login` 登录的结果，会通过 `onLoginResult` 回调通知用户。


## 成员变量
| 类型 | 默认值 | 名称 |
| --- | --- | --- |
| int | 0 | [LOGIN_ERROR_CODE_SUCCESS](#LoginErrorCode-login_error_code_success) |
| int | -1000 | [LOGIN_ERROR_CODE_INVALID_TOKEN](#LoginErrorCode-login_error_code_invalid_token) |
| int | -1001 | [LOGIN_ERROR_CODE_LOGIN_FAILED](#LoginErrorCode-login_error_code_login_failed) |
| int | -1002 | [LOGIN_ERROR_CODE_INVALID_USER_ID](#LoginErrorCode-login_error_code_invalid_user_id) |
| int | -1003 | [LOGIN_ERROR_CODE_SERVER_ERROR](#LoginErrorCode-login_error_code_server_error) |

## 变量说明
<span id="LoginErrorCode-login_error_code_success"></span>
### LOGIN_ERROR_CODE_SUCCESS
```java
public static final int com.ss.bytertc.engine.type.LoginErrorCode.LOGIN_ERROR_CODE_SUCCESS = 0
```
调用 `login` 方法登录成功。


<span id="LoginErrorCode-login_error_code_invalid_token"></span>
### LOGIN_ERROR_CODE_INVALID_TOKEN
```java
public static final int com.ss.bytertc.engine.type.LoginErrorCode.LOGIN_ERROR_CODE_INVALID_TOKEN = -1000
```
调用 `login` 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token。


<span id="LoginErrorCode-login_error_code_login_failed"></span>
### LOGIN_ERROR_CODE_LOGIN_FAILED
```java
public static final int com.ss.bytertc.engine.type.LoginErrorCode.LOGIN_ERROR_CODE_LOGIN_FAILED = -1001
```
登录错误。

调用 `login` 方法时发生未知错误导致登录失败，需要重新登录。


<span id="LoginErrorCode-login_error_code_invalid_user_id"></span>
### LOGIN_ERROR_CODE_INVALID_USER_ID
```java
public static final int com.ss.bytertc.engine.type.LoginErrorCode.LOGIN_ERROR_CODE_INVALID_USER_ID = -1002
```
调用 `login` 方法时传入的用户 ID 有问题。


<span id="LoginErrorCode-login_error_code_server_error"></span>
### LOGIN_ERROR_CODE_SERVER_ERROR
```java
public static final int com.ss.bytertc.engine.type.LoginErrorCode.LOGIN_ERROR_CODE_SERVER_ERROR = -1003
```
调用 `login` 登录时服务器错误。


<span id="TranscodingError"></span>
# TranscodingError
```java
public class com.ss.bytertc.engine.type.TranscodingError
```
转推直播功能错误码。


## 成员变量
| 类型 | 默认值 | 名称 |
| --- | --- | --- |
| int | 0 | [TRANSCODING_ERROR_OK](#TranscodingError-transcoding_error_ok) |
| int | 1 | [TRANSCODING_ERROR_INVALID_ARGUMENT](#TranscodingError-transcoding_error_invalid_argument) |
| int | 2 | [TRANSCODING_ERROR_SUBSCRIBE](#TranscodingError-transcoding_error_subscribe) |
| int | 3 | [TRANSCODING_ERROR_PROCESSING](#TranscodingError-transcoding_error_processing) |
| int | 4 | [TRANSCODING_ERROR_PUBLISH](#TranscodingError-transcoding_error_publish) |

## 变量说明
<span id="TranscodingError-transcoding_error_ok"></span>
### TRANSCODING_ERROR_OK
```java
public static final int com.ss.bytertc.engine.type.TranscodingError.TRANSCODING_ERROR_OK = 0
```
推流成功。


<span id="TranscodingError-transcoding_error_invalid_argument"></span>
### TRANSCODING_ERROR_INVALID_ARGUMENT
```java
public static final int com.ss.bytertc.engine.type.TranscodingError.TRANSCODING_ERROR_INVALID_ARGUMENT = 1
```
推流参数错误。你必须更新合流参数并重试。


<span id="TranscodingError-transcoding_error_subscribe"></span>
### TRANSCODING_ERROR_SUBSCRIBE
```java
public static final int com.ss.bytertc.engine.type.TranscodingError.TRANSCODING_ERROR_SUBSCRIBE = 2
```
和 RTC 服务端建立连接失败。会自动重连


<span id="TranscodingError-transcoding_error_processing"></span>
### TRANSCODING_ERROR_PROCESSING
```java
public static final int com.ss.bytertc.engine.type.TranscodingError.TRANSCODING_ERROR_PROCESSING = 3
```
合流服务中间过程存在错误，建议重试。


<span id="TranscodingError-transcoding_error_publish"></span>
### TRANSCODING_ERROR_PUBLISH
```java
public static final int com.ss.bytertc.engine.type.TranscodingError.TRANSCODING_ERROR_PUBLISH = 4
```
推流失败，可以等待服务端重新推流。
