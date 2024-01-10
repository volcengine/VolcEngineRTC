# AudioRecordingErrorCode
```cpp
enum bytertc::AudioRecordingErrorCode
```

音频文件录制的错误码


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kAudioRecordingErrorCodeOk** | 录制正常 |
| **kAudioRecordingErrorCodeNoPermission** | 没有文件写权限 |
| **kAudioRecordingErrorNotInRoom** | 没有进入房间 |
| **kAudioRecordingAlreadyStarted** | 录制已经开始 |
| **kAudioRecordingNotStarted** | 录制还未开始 |
| **kAudioRecordingErrorCodeNotSupport** | 录制失败。文件格式不支持。 |
| **kAudioRecordingErrorCodeOther** | 其他异常 |


# ErrorCode
```cpp
enum bytertc::ErrorCode
```

回调错误码。  <br>
SDK 内部遇到不可恢复的错误时，会通过 `onError` 回调通知用户。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kErrorCodeInvalidToken** | Token 无效。通过 [onRoomStateChanged](Linux-callback#IRTCRoomEventHandler-onroomstatechanged) 回调。<br/>调用 [joinRoom](Linux-api.md#IRTCRoom-joinroom) 进房时使用的 Token 参数有误或过期失效。需要重新获取 Token，并调用 [updateToken](Linux-api.md#IRTCRoom-updatetoken) 方法更新 Token。 |
| **kErrorCodeJoinRoom** | 加入房间错误。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。<br/>进房时发生未知错误导致加入房间失败。需要用户重新加入房间。 |
| **kErrorCodeNoPublishPermission** | 没有发布音视频流权限。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。<br/>用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。 |
| **kErrorCodeNoSubscribePermission** | 没有订阅音视频流权限。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。<br/>用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。 |
| **kErrorCodeDuplicateLogin** | 相同用户 ID 的用户加入本房间，当前用户被踢出房间。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kErrorCodeKickedOut** | 服务端调用 OpenAPI 将当前用户踢出房间。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kRoomErrorCodeRoomIdIllegal** | 当调用 `createRTCRoom` ，如果roomid 非法，会返回null，并抛出该error。通过 [onCreateRoomStateChanged](Linux-callback.md#IRTCVideoEventHandler-oncreateroomstatechanged) 回调。 |
| **kRoomErrorTokenExpired** | Token 过期。加入房间后 Token 过期时，返回此错误码。需使用新的 Token 重新加入房间。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kRoomErrorUpdateTokenWithInvalidToken** | 调用 `updateToken` 传入的 Token 无效。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kErrorCodeRoomDismiss** | 服务端调用 OpenAPI 解散房间，所有用户被移出房间。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kErrorCodeRoomAlreadyExist** | 通话回路检测已经存在同样 roomId 的房间了。通过 [onCreateRoomStateChanged](Linux-callback.md#IRTCVideoEventHandler-oncreateroomstatechanged) 回调。 |
| **kErrorCodeUserIDDifferent** | 加入多个房间时使用了不同的 uid。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。<br/>同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。 |
| **kErrorCodeJoinRoomRoomForbidden** | 房间被封禁。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kErrorCodeJoinRoomUserForbidden** | 用户被封禁。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kErrorCodeOverStreamSubscribeLimit** | 订阅音视频流失败，订阅音视频流总数超过上限。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。<br/>游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。 |
| **kErrorCodeOverStreamPublishLimit** | 发布流失败，发布流总数超过上限。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。<br/>RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。 |
| **kErrorCodeInvalidAudioSyncUidRepeated** | 音视频同步失败。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。<br/>当前音频源已与其他视频源关联同步关系。  <br><br/>单个音频源不支持与多个视频源同时同步。 |
| **kErrorCodeAbnormalServerStatus** | 服务端异常状态导致退出房间。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。<br/>SDK与信令服务器断开，并不再自动重连，可联系技术支持。  <br> |
| **[deprecated] kErrorCodeOverScreenPublishLimit** | 发布屏幕流失败，发布流总数超过上限。<br/>RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。 |
| **[deprecated] kErrorCodeOverVideoPublishLimit** | 发布视频流总数超过上限。<br/>RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。 |


# WarningCode
```cpp
enum bytertc::WarningCode
```

回调警告码。
警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kWarningCodeJoinRoomFailed** | 进房失败。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。<br/>当你调用初次加入房间或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。 |
| **kWarningCodePublishStreamFailed** | 发布音视频流失败。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。<br/>当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。 |
| **kWarningCodeSubscribeStreamFailed404** | 订阅音视频流失败。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。<br/>当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。 |
| **kWarningCodeSubscribeStreamFailed5xx** | 订阅音视频流失败。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。<br/>当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。 |
| **kWarningCodePublishStreamForbiden** | 当调用 `setUserVisibility` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。 |
| **kWarningCodeSendCustomMessage** | 发送自定义广播消息失败，当前你未在房间中。 |
| **kWarningCodeUserNotifyStop** | 当房间内人数超过 500 人时，停止向房间内已有用户发送 `onUserJoined` 和 `onUserLeave` 回调，并通过广播提示房间内所有用户。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kWarningCodeUserInPublish** | 用户已经在其他房间发布过流，或者用户正在发布公共流。通过 [onStreamStateChanged](Linux-callback.md#IRTCRoomEventHandler-onstreamstatechanged) 回调。 |
| **kWarningCodeOldRoomBeenReplaced** | 已存在相同 roomId 的房间，新创建的房间实例已替换旧房间实例。通过 [onRoomStateChanged](Linux-callback.md#IRTCRoomEventHandler-onroomstatechanged) 回调。 |
| **kWarningCodeInEchoTestMode** | 当前正在进行回路测试，该接口调用无效 |
| **kWarningCodeNoCameraPermission** | 摄像头权限异常，当前应用没有获取摄像头权限。 |
| **kWarningCodeNoMicrophonePermission** | 已在 3.33 版本中废弃，使用 [MediaDeviceError](Linux-keytype.md#mediadeviceerror).kMediaDeviceErrorDeviceNoPermission 代替。<br><br/>麦克风权限异常，当前应用没有获取麦克风权限。 |
| **kWarningCodeRecodingDeviceStartFailed** | 已在 3.33 版本中废弃，使用 [MediaDeviceError](Linux-keytype.md#mediadeviceerror).kMediaDeviceErrorDeviceFailure 代替。<br><br/>音频采集设备启动失败，当前设备可能被其他应用占用。 |
| **kWarningCodePlayoutDeviceStartFailed** | 已在 3.33 版本中废弃，使用 use [MediaDeviceError](Linux-keytype.md#mediadeviceerror).kMediaDeviceErrorDeviceFailure 代替。<br><br/>音频播放设备启动失败警告，可能由于系统资源不足，或参数错误。 |
| **kWarningCodeNoRecordingDevice** | 已在 3.33 版本中废弃，使用 [MediaDeviceError](Linux-keytype.md#mediadeviceerror).kMediaDeviceErrorDeviceNotFound 代替。<br><br/>无可用音频采集设备，请插入可用的音频采集设备。 |
| **kWarningCodeNoPlayoutDevice** | 已在 3.33 版本中废弃，使用 [MediaDeviceError](Linux-keytype.md#mediadeviceerror).kMediaDeviceErrorDeviceNotFound 代替。<br><br/>无可用音频播放设备，请插入可用的音频播放设备。 |
| **kWarningCodeRecordingSilence** | 已在 3.33 版本中废弃，使用 [MediaDeviceWarning](Linux-keytype.md#mediadevicewarning).kMediaDeviceWarningCaptureSilence 代替。<br><br/>当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。 |
| **kWarningCodeMediaDeviceOperationDenied** | 已在 3.33 版本中废弃，使用 [MediaDeviceWarning](Linux-keytype.md#mediadevicewarning).kMediaDeviceWarningOperationDenied 代替。<br><br/>媒体设备误操作警告。  <br><br/>使用自定义采集时，不可调用内部采集开关，调用时将触发此警告。 |
| **kWarningCodeSetScreenAudioSourceTypeFailed** | 不支持在 `publishScreen` 之后调用 `setScreenAudioSourceType` 设置屏幕音频采集类型，请在 publishScreen 之前设置 |
| **kWarningCodeSetScreenAudioStreamIndexFailed** | 不支持在 `publishScreen` 之后， 通过 `setScreenAudioStreamIndex` 设置屏幕共享时的音频采集方式。 |
| **kWarningCodeInvalidVoicePitch** | 设置语音音高不合法 |
| **kWarningCodeInvalidAudioFormat** | 设置音频格式不合法 |
| **kWarningCodeInvalidCallForExtAudio** | 外部音频源新旧接口混用 |
| **kWarningCodeInvalidRemoteStreamKey** | 非法的远端流索引 |
| **kWarningCodeInvalidCanvasHandle** | 指定的内部渲染画布句柄无效。  <br><br/>当你调用 [setLocalVideoCanvas](Linux-api.md#IRTCVideo-setlocalvideocanvas) 时指定了无效的画布句柄，触发此回调。 |
| **kWarningInvaildSamiAppkeyORToken** | [音频技术](https://www.volcengine.com/docs/6489/71986) SDK 鉴权失效。联系技术支持人员。 |
| **kWarningInvaildSamiResourcePath** | [音频技术](https://www.volcengine.com/docs/6489/71986) 资源加载失败。传入正确的 DAT 路径，或联系技术支持人员。 |
| **kWarningLoadSamiLibraryFailed** | [音频技术](https://www.volcengine.com/docs/6489/71986) 库加载失败。使用正确的库，或联系技术支持人员。 |
| **kWarningInvaildSamiEffectType** | [音频技术](https://www.volcengine.com/docs/6489/71986) 不支持此音效。联系技术支持人员。 |
| **[deprecated] kWarningCodeGetRoomFailed** |  |
| **[deprecated] kWarningCodeSubscribeStreamForbiden** | 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br><br/>你需在进房前关闭自动订阅模式，再调用 [subscribeStream](Linux-api.md#IRTCRoom-subscribestream) 方法手动订阅音视频流。 |


# LocalVideoStreamError
```cpp
enum bytertc::LocalVideoStreamError
```

本地视频状态改变时的错误码


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kLocalVideoStreamErrorOk** | 状态正常 |
| **kLocalVideoStreamErrorFailure** | 本地视频流发布失败 |
| **kLocalVideoStreamErrorDeviceNoPermission** | 没有权限启动本地视频采集设备 |
| **kLocalVideoStreamErrorDeviceBusy** | 本地视频采集设备已被占用 |
| **kLocalVideoStreamErrorDeviceNotFound** | 本地视频采集设备不存在 |
| **kLocalVideoStreamErrorCaptureFailure** | 本地视频采集失败，建议检查采集设备是否正常工作 |
| **kLocalVideoStreamErrorEncodeFailure** | 本地视频编码失败 |
| **kLocalVideoStreamErrorDeviceDisconnected** | 通话过程中本地视频采集设备被其他程序抢占，导致设备连接中断 |


# NetworkDetectionStartReturn
```cpp
enum bytertc::NetworkDetectionStartReturn
```

开始探测的返回值
`startNetworkDetection` 返回对象类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kNetworkDetectionStartReturnSuccess** | 成功开启网络探测。 |
| **kNetworkDetectionStartReturnParamErr** | 开始探测失败。参数错误，上下行探测均为 `false`，或期望带宽超过了范围 [100,10000] |
| **kNetworkDetectionStartReturnStreaming** | 开始探测失败。失败原因为，本地已经开始推拉流 |
| **kNetworkDetectionStartReturnStarted** | 已经开始探测，无需重复开启 |
| **kNetworkDetectionStartReturnNotSupport** | 不支持该功能 |


# SubtitleErrorCode
```cpp
enum bytertc::SubtitleErrorCode
```

字幕任务错误码。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kSubtitleErrorCodeUnknow** | 客户端无法识别云端媒体处理发送的错误码。请联系技术支持。 |
| **kSubtitleErrorCodeSuccess** | 字幕已开启。 |
| **kSubtitleErrorCodePostProcessError** | 云端媒体处理内部出现错误，请联系技术支持。 |
| **kSubtitleErrorCodeASRConnectionError** | 第三方服务连接失败，请联系技术支持。 |
| **kSubtitleErrorCodeASRServiceError** | 第三方服务内部出现错误，请联系技术支持。 |
| **kSubtitleErrorCodeBeforeJoinRoom** | 未进房导致调用`startSubtitle`失败。请加入房间后再调用此方法。 |
| **kSubtitleErrorCodeAlreadyOn** | 重复调用 `startSubtitle`。 |
| **kSubtitleErrorCodeUnsupportedLanguage** | 用户选择的目标语言目前暂不支持。 |
| **kSubtitleErrorCodePostProcessTimeout** | 云端媒体处理超时未响应，请联系技术支持。 |


# LoginErrorCode
```cpp
enum bytertc::LoginErrorCode
```

登录结果  <br>
调用 `login` 登录的结果，会通过 `onLoginResult` 回调通知用户。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kLoginErrorCodeSuccess** | 调用 `login` 方法登录成功 |
| **kLoginErrorCodeInvalidToken** | 调用 `login` 方法时使用的 Token 无效或过期失效，需要用户重新获取 Token。 |
| **kLoginErrorCodeLoginFailed** | 登录错误  <br><br/>调用 `login` 方法时发生未知错误导致登录失败，需要重新登录。 |
| **kLoginErrorCodeInvalidUserId** | 调用 `login` 方法时传入的用户 ID 有问题。 |
| **kLoginErrorCodeServerError** | 调用 `login` 登录时服务端出错。 |


# RtsErrorCode
```cpp
enum bytertc::RtsErrorCode
```

回调错误码。  <br>
SDK 内部遇到不可恢复的错误时，会通过 `onError` 回调通知用户。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kRtsErrorCodeInvalidToken** | Token 无效。<br/>进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用 `updateToken` 方法更新 Token。 |
| **kRtsErrorCodeJoinRoom** | 加入房间错误。<br/>进房时发生未知错误导致加入房间失败。需要用户重新加入房间。 |
| **kRtsErrorCodeDuplicateLogin** | 相同用户 ID 的用户加入本房间，当前用户被踢出房间 |
| **kRtsErrorCodeKickedOut** | 服务端调用 OpenAPI 将当前用户踢出房间 |
| **kRtsRoomErrorCodeRoomIdIllegal** | 当调用 `createRTCRoom` ，如果roomid 非法，会返回null，并抛出该error |
| **kRtsRoomErrorTokenExpired** | Token 过期。调用 `joinRoom` 使用新的 Token 重新加入房间。 |
| **kRtsRoomErrorUpdateTokenWithInvalidToken** | 调用 `updateToken` 传入的 Token 无效 |
| **kRtsErrorCodeRoomDismiss** | 服务端调用 OpenAPI 解散房间，所有用户被移出房间。 |
| **kRtsErrorCodeRoomAlreadyExist** | 通话回路检测已经存在同样 roomId 的房间了 |
| **kRtsErrorCodeUserIDDifferent** | 同一个引擎实例在进入多个房间时设置的用户名必须相同 |
| **kRtsErrorCodeAbnormalServerStatus** | 服务端异常状态导致退出房间。  <br><br/>SDK与信令服务器断开，并不再自动重连，可联系技术支持。  <br> |


# RtsWarningCode
```cpp
enum bytertc::RtsWarningCode
```

回调警告码。
警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kRtsWarningCodeJoinRoomFailed** | 进房失败。  <br><br/>当你调用初次加入房间或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。 |
| **kRtsWarningCodePublishStreamFailed** | 发布音视频流失败。  <br><br/>当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。 |
| **kRtsWarningCodeSendCustomMessage** | 发送自定义广播消息失败，当前你未在房间中。 |
| **kRtsWarningCodeUserNotifyStop** | 当房间内人数超过 500 人时，停止向房间内已有用户发送 `onUserJoined` 和 `onUserLeave` 回调，并通过广播提示房间内所有用户。 |
| **kRtsWarningCodeOldRoomBeenReplaced** | 新生成的房间已经替换了同样roomId的旧房间 |
| **[deprecated] kRtsWarningCodeGetRoomFailed** |  |


# SingleStreamPushEvent
```cpp
enum bytertc::SingleStreamPushEvent
```

单流转推直播错误码


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kSingleStreamPushStart** | 开始推流。 |
| **kSingleStreamPushSuccess** | 推流成功。 |
| **kSingleStreamPushFailed** | 推流失败。 |
| **kSingleStreamPushStop** | 停止推流。 |
| **kSingleStreamPushTimeout** | 单流转推直播任务处理超时，请检查网络状态并重试。 |
| **kSingleStreamPushParamError** | 参数错误。 |


# StreamMixingErrorCode
```cpp
enum bytertc::StreamMixingErrorCode
```

转推直播错误码


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kStreamMixingErrorOK** | 推流成功。 |
| **kStreamMixingErrorBase** | 未定义的合流错误 |
| **kStreamMixingErrorInvalidParam** | 客户端 SDK 检测到无效推流参数。 |
| **kStreamMixingErrorInvalidState** | 状态错误，需要在状态机正常状态下发起操作 |
| **kStreamMixingErrorInvalidOperator** | 无效操作 |
| **kStreamMixingErrorTimeout** | 转推直播任务处理超时，请检查网络状态并重试 |
| **kStreamMixingErrorInvalidParamByServer** | 服务端检测到错误的推流参数 |
| **kStreamMixingErrorSubTimeoutByServer** | 对流的订阅超时 |
| **kStreamMixingErrorInvalidStateByServer** | 合流服务端内部错误。 |
| **kStreamMixingErrorAuthenticationByCDN** | 合流服务端推 CDN 失败。 |
| **kStreamMixingErrorTimeoutBySignaling** | 服务端接收信令超时，请检查网络状态并重试。 |
| **kStreamMixingErrorMixImageFail** | 图片合流失败。 |
| **kStreamMixingErrorUnKnownByServer** | 服务端未知错误。 |


# PublicStreamErrorCode
```cpp
enum bytertc::PublicStreamErrorCode
```

公共流状态码


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kPublicStreamErrorCodeOK** | 发布或订阅成功。 |
| **kPublicStreamErrorCodePushInvalidParam** | 公共流的参数异常，请修改参数后重试。 |
| **kPublicStreamErrorCodePushInvalidStatus** | 服务端状态异常，将自动重试。 |
| **kPublicStreamErrorCodePushInternalError** | 内部错误，不可恢复，请重试。 |
| **kPublicStreamErrorCodePushFailed** | 发布失败，将自动重试，请关注重试结果。 |
| **kPublicStreamErrorCodePushTimeout** | 发布失败，10 s 后会重试，重试 3 次后自动停止。 |
| **kPublicStreamErrorCodePullNoPushStream** | 订阅失败，发布端未开始发布流。 |