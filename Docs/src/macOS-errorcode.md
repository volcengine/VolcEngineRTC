# ByteRTCNetworkDetectionStartReturn
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCNetworkDetectionStartReturn)
```

开始探测的返回值
`startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:` 返回对象类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCNetworkDetectionStartReturnSuccess | 0 | 成功开始探测。 |
| ByteRTCNetworkDetectionStartReturnParamErr | 1 | 开始探测失败。参数错误，上下行探测均为 `false`，或期望带宽超过了范围 [100,10000] |
| ByteRTCNetworkDetectionStartReturnStreaming | 2 | 开始探测失败。失败原因为，本地已经开始推拉流 |
| ByteRTCNetworkDetectionStartReturnStarted | 3 | 已经开始探测，无需重复开启 |
| ByteRTCNNetworkDetectionStartReturnNotSupport | 4 | 不支持该功能 |


# ByteRTCErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCErrorCode)
```

回调错误码。
SDK 内部遇到不可恢复的错误时，会通过 `rtcEngine:onError:` 回调通知用户。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCErrorCodeInvalidToken | -1000 | Token 无效。<br/>进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用<br/>`updateToken:` 方法更新 Token。 |
| ByteRTCErrorCodeJoinRoom | -1001 | 加入房间错误。<br/>进房时发生未知错误导致加入房间失败。需要用户重新加入房间。 |
| ByteRTCErrorCodeNoPublishPermission | -1002 | 没有发布音视频流权限。<br/>用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。 |
| ByteRTCErrorCodeNoSubscribePermission | -1003 | 没有订阅音视频流权限。<br/>用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。 |
| ByteRTCErrorCodeDuplicateLogin | -1004 | 相同用户 ID 的用户加入本房间，当前用户被踢出房间 |
| ByteRTCErrorCodeKickedOut | -1006 | 服务端调用 OpenAPI 将当前用户踢出房间 |
| ByteRTCErrorCodeRoomIdIllegal | -1007 | 当调用 `createRtcRoom:` ，如果 roomId 非法，会返回 null，并抛出该错误 |
| ByteRTCErrorCodeTokenExpired | -1009 | Token 过期。调用 `joinRoomByKey:roomId:userInfo:rtcRoomConfig:` 使用新的 Token 重新加入房间。 |
| ByteRTCErrorCodeUpdateTokenWithInvalidToken | -1010 | 调用 `updateToken:` 传入的 Token 无效 |
| ByteRTCErrorCodeRoomDismiss | -1011 | 服务端调用 OpenAPI 解散房间，所有用户被移出房间。 |
| ByteRTCJoinRoomWithoutLicenseAuthenticateSDK | -1012 | 加入房间错误。  <br><br/>调用 `joinRoomByToken:userInfo:roomConfig:` 方法时, LICENSE 计费账号未使用 LICENSE_AUTHENTICATE SDK，加入房间错误。 |
| ByteRTCRoomAlreadyExist | -1013 | 通话回路检测已经存在同样 roomId 的房间了 |
| ByteRTCErrorCodeOverStreamSubscribeLimit | -1070 | 订阅音视频流失败，订阅音视频流总数超过上限。<br/>游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。 |
| ByteRTCErrorCodeOverStreamPublishLimit | -1080 | 发布流失败，发布流总数超过上限。<br/>RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。 |
| ByteRTCErrorCodeOverScreenPublishLimit | -1081 | 发布屏幕流失败，发布流总数超过上限。<br/>RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。 |
| ByteRTCErrorCodeOverVideoPublishLimit | -1082 | 发布视频流总数超过上限。<br/>RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。 |
| ByteRTCErrorCodInvalidAudioSyncUidRepeated | -1083 | 音视频同步失败。  <br><br/>当前音频源已与其他视频源关联同步关系。  <br><br/>单个音频源不支持与多个视频源同时同步。 |
| ByteRTCErrorCodeAbnormalServerStatus | -1084 | 服务端异常状态导致退出房间。  <br><br/>SDK与信令服务器断开，并不再自动重连，可联系技术支持。  <br> |


# ByteRTCWarningCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCWarningCode)
```

回调警告码。
警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCWarningCodeJoinRoomFailed | -2001 | 进房失败。  <br><br/>初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。 |
| ByteRTCWarningCodePublishStreamFailed | -2002 | 发布音视频流失败。<br/>当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。 |
| ByteRTCWarningCodeSubscribeStreamFailed404 | -2003 | 订阅音视频流失败。<br/>当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。 |
| ByteRTCWarningCodeSubscribeStreamFailed5xx | -2004 | 订阅音视频流失败。<br/>当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。 |
| ByteRTCWarningCodePublishStreamForbiden | -2009 | 当调用 `setUserVisibility:` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  <br> |
| ByteRTCWarningCodeSendCustomMessage | -2011 | 发送自定义广播消息失败，当前你未在房间中。 |
| ByteRTCWarningCodeCodeUserNotifyStop | -2013 | 当房间内人数超过 500 人时，停止向房间内已有用户发送 `rtcEngine:onUserJoined:elapsed:` 和 `rtcEngine:onUserLeave:reason:` 回调，并通过广播提示房间内所有用户。 |
| ByteRTCWarningCodeUserInPublish | -2014 | 用户已经在其他房间发布过流，或者用户正在发布公共流。 |
| ByteRTCWarningCodeOldRoomBeenReplaced | -2016 | 已存在相同 roomId 的房间，新创建的房间实例已替换旧房间实例。 |
| ByteRTCWarningCodeInEchoTestMode | -2017 | 当前正在进行回路测试，该接口调用无效 |
| ByteRTCWarningCodeNoCameraPermission | -5001 | 摄像头权限异常，当前应用没有获取摄像头权限 |
| ByteRTCWarningSetScreenAudioSourceTypeFailed | -5009 | 不支持在 `publishScreen` 之后，通过 `setScreenAudioSourceType` 设置屏幕音频采集类型 |
| ByteRTCWarningSetScreenAudioStreamIndexFailed | -5010 | 不支持在 `publishScreen` 之后，通过 `setScreenAudioStreamIndex` 设置屏幕音频混流类型 |
| ByteRTCWarningInvalidVoicePitch | -5011 | 设置语音音高不合法 |
| ByteRTCWarningInvalidCallForExtAudio | -5013 | 外部音频源新旧接口混用 |
| ByteRTCWarningCodeInvalidCanvasHandle | -6001 | 指定的内部渲染画布句柄无效。  <br><br/>当你调用 [setLocalVideoCanvas:withCanvas:](macOS-api.md#ByteRTCVideo-setlocalvideocanvas-withcanvas) 或 [setRemoteVideoCanvas:withIndex:withCanvas:](macOS-api.md#ByteRTCVideo-setremotevideocanvas-withindex-withcanvas) 时指定了无效的画布句柄，触发此回调。 |


# ByteRTCLoginErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCLoginErrorCode)
```

登录结果  <br>
调用 `login:uid:` 登录的结果，会通过 `rtcEngine:onLoginResult:errorCode:elapsed:` 回调通知用户。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCLoginErrorCodeSuccess | 0 | 调用 `login:uid:` 方法登录成功。 |
| ByteRTCLoginErrorCodeInvalidToken | -1000 | 调用 `login:uid:` 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token。 |
| ByteRTCLoginErrorCodeLoginFailed | -1001 | 登录错误  <br><br/>调用 `login:uid:` 方法时发生未知错误导致登录失败。需要用户重新登录。 |
| ByteRTCLoginErrorCodeInvalidUserId | -1002 | 调用 `login:uid:` 方法时传入的用户 ID 有问题。 |
| ByteRTCLoginErrorCodeServerError | -1003 | 调用 `login:uid:` 登录时服务器错误。 |


# ByteRTCTranscodingError
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCTranscodingError)
```

转推直播功能错误码。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCTranscodingErrorOK | 0 | 推流成功。 |
| ByteRTCTranscodingErrorInvalidArgument | 1 | 推流参数错误。你必须更新合流参数并重试。 |
| ByteRTCTranscodingErrorSubscribe | 2 | 和 RTC 服务端建立连接失败。会自动重连 |
| ByteRTCTranscodingErrorProcessing | 3 | 合流服务中间过程存在错误，建议重试。 |
| ByteRTCTranscodingErrorPublish | 4 | 推流失败，可以等待服务端重新推流。 |


# ByteRTCSingleStreamPushEvent
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCSingleStreamPushEvent)
```

单流转推直播错误码


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCSingleStreamPushEventStart | 1 | 开始推流。 |
| ByteRTCSingleStreamPushEventStartSuccess | 2 | 推流成功。 |
| ByteRTCSingleStreamPushEventStartFailed | 3 | 推流失败。 |
| ByteRTCSingleStreamPushEventStop | 4 | 停止推流。 |
| ByteRTCSingleStreamPushEventTimeout | 5 | 单流转推直播任务处理超时，请检查网络状态并重试。 |
| ByteRTCSingleStreamPushEventParamError | 6 | 参数错误。 |


# ByteRtcTranscoderErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRtcTranscoderErrorCode)
```

转推直播错误码


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRtcTranscoderErrorCodeOK | 0 | 推流成功。 |
| ByteRtcTranscoderErrorCodeBase | 1090 | 未定义的合流错误 |
| ByteRtcTranscoderErrorCodeInvalidParam | 1091 | 客户端 SDK 检测到无效推流参数。 |
| ByteRtcTranscoderErrorCodeInvalidState | 1092 | 状态错误，需要在状态机正常状态下发起操作 |
| ByteRtcTranscoderErrorCodeInvalidOperator | 1093 | 无效操作 |
| ByteRtcTranscoderErrorCodeTimeOut | 1094 | 转推直播任务处理超时，请检查网络状态并重试 |
| ByteRtcTranscoderErrorCodeInvalidParamByServer | 1095 | 服务端检测到错误的推流参数 |
| ByteRtcTranscoderErrorCodeSubTimeoutByServer | 1096 | 对流的订阅超时 |
| ByteRtcTranscoderErrorCodeInvalidStateByServer | 1097 | 合流服务端内部错误。 |
| ByteRtcTranscoderErrorCodeAuthenticationByCDN | 1098 | 合流服务端推 CDN 失败。 |
| ByteRtcTranscoderErrorCodeTimeoutBySignaling | 1099 | 服务端接收信令超时，请检查网络状态并重试。 |
| ByteRtcTranscoderErrorCodeMixImageFail | 1100 | 图片合流失败。 |
| ByteRtcTranscoderErrorCodeUnKnownErrorByServer | 1101 | 服务端未知错误。 |