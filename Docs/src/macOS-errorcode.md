# ByteRTCAudioRecordingErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioRecordingErrorCode)
```

音频文件录制的错误码


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioRecordingErrorCodeOk | 0 | 录制正常 |
| ByteRTCAudioRecordingErrorCodeNoPermission | -1 | 没有文件写权限 |
| ByteRTCAudioRecordingErrorNotInRoom | -2 | 没有进入房间 |
| ByteRTCAudioRecordingAlreadyStarted | -3 | 录制已经开始 |
| ByteRTCAudioRecordingNotStarted | -4 | 录制还未开始 |
| ByteRTCAudioRecordingErrorCodeNotSupport | -5 | 录制失败。文件格式不支持。 |
| ByteRTCAudioRecordingErrorCodeOther | -6 | 其他异常 |


# ByteRTCErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCErrorCode)
```

回调错误码。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCErrorCodeInvalidToken | -1000 | Token 无效。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。<br/>调用 [joinRoom:userInfo:roomConfig:](macOS-api.md#ByteRTCRoom-joinroom-userinfo-roomconfig) 进房时使用的 Token 参数有误或过期失效。需要重新获取 Token，并调用 [updateToken:](macOS-api.md#ByteRTCRoom-updatetoken) 方法更新 Token。 |
| ByteRTCErrorCodeJoinRoom | -1001 | 加入房间错误。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。<br/>进房时发生未知错误导致加入房间失败。需要用户重新加入房间。 |
| ByteRTCErrorCodeNoPublishPermission | -1002 | 没有发布音视频流权限。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。<br/>用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。 |
| ByteRTCErrorCodeNoSubscribePermission | -1003 | 没有订阅音视频流权限。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。<br/>用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。 |
| ByteRTCErrorCodeDuplicateLogin | -1004 | 相同用户 ID 的用户加入本房间，当前用户被踢出房间。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCErrorCodeKickedOut | -1006 | 服务端调用 OpenAPI 将当前用户踢出房间。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCErrorCodeRoomIdIllegal | -1007 | 当调用 `createRtcRoom:` ，如果 roomId 非法，会返回 null，并抛出该错误。通过 [rtcEngine:onCreateRoomStateChanged:errorCode:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode) 回调。 |
| ByteRTCErrorCodeTokenExpired | -1009 | Token 过期。加入房间后 Token 过期时，返回此错误码。需使用新的 Token 重新加入房间。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCErrorCodeUpdateTokenWithInvalidToken | -1010 | 调用 `updateToken:` 传入的 Token 无效。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCErrorCodeRoomDismiss | -1011 | 服务端调用 OpenAPI 解散房间，所有用户被移出房间。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCRoomAlreadyExist | -1013 | 通话回路检测已经存在同样 roomId 的房间了。通过 onCreatrtcEngine:onCreateRoomStateChanged:errorCode:eRoomStateChanged[rtcEngine:onCreateRoomStateChanged:errorCode:](macOS-callback.md#ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode) 回调。 |
| ByteRTCUserIDDifferent | -1014 | 加入多个房间时使用了不同的 uid。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。<br/>同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。 |
| ByteRTCErrorCodeJoinRoomRoomForbidden | -1025 | 房间被封禁。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCErrorCodeJoinRoomUserForbidden | -1026 | 用户被封禁。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCErrorCodeOverStreamSubscribeLimit | -1070 | 订阅音视频流失败，订阅音视频流总数超过上限。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。<br/>游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。 |
| ByteRTCErrorCodeOverStreamPublishLimit | -1080 | 发布流失败，发布流总数超过上限。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。<br/>RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。 |
| ByteRTCErrorCodInvalidAudioSyncUidRepeated | -1083 | 音视频同步失败。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。<br/>当前音频源已与其他视频源关联同步关系。  <br><br/>单个音频源不支持与多个视频源同时同步。 |
| ByteRTCErrorCodeAbnormalServerStatus | -1084 | 服务端异常状态导致退出房间。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。<br/>SDK与信令服务器断开，并不再自动重连，可联系技术支持。  <br> |
| [deprecated] ByteRTCErrorCodeOverScreenPublishLimit | -1081 | 发布屏幕流失败，发布流总数超过上限。<br/>RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。 |
| [deprecated] ByteRTCErrorCodeOverVideoPublishLimit | -1082 | 发布视频流总数超过上限。<br/>RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。 |


# ByteRTCWarningCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCWarningCode)
```

回调警告码。
警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCWarningCodeJoinRoomFailed | -2001 | 进房失败。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。<br/>初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。 |
| ByteRTCWarningCodePublishStreamFailed | -2002 | 发布音视频流失败。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。<br/>当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。 |
| ByteRTCWarningCodeSubscribeStreamFailed404 | -2003 | 订阅音视频流失败。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。<br/>当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。 |
| ByteRTCWarningCodeSubscribeStreamFailed5xx | -2004 | 订阅音视频流失败。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。<br/>当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。 |
| ByteRTCWarningCodePublishStreamForbiden | -2009 | 当调用 `setUserVisibility:` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCWarningCodeSendCustomMessage | -2011 | 发送自定义广播消息失败，当前你未在房间中。 |
| ByteRTCWarningCodeCodeUserNotifyStop | -2013 | 当房间内人数超过 500 人时，停止向房间内已有用户发送 `rtcEngine:onUserJoined:elapsed:` 和 `rtcEngine:onUserLeave:reason:` 回调，并通过广播提示房间内所有用户。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCWarningCodeUserInPublish | -2014 | 用户已经在其他房间发布过流，或者用户正在发布公共流。通过 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCWarningCodeOldRoomBeenReplaced | -2016 | 已存在相同 roomId 的房间，新创建的房间实例已替换旧房间实例。通过 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](macOS-callback.md#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调。 |
| ByteRTCWarningCodeInEchoTestMode | -2017 | 当前正在进行回路测试，该接口调用无效 |
| ByteRTCWarningCodeNoCameraPermission | -5001 | 摄像头权限异常，当前应用没有获取摄像头权限 |
| ByteRTCWarningSetScreenAudioSourceTypeFailed | -5009 | 不支持在 `publishScreen` 之后，通过 `setScreenAudioSourceType` 设置屏幕音频采集类型 |
| ByteRTCWarningSetScreenAudioStreamIndexFailed | -5010 | 不支持在 `publishScreen` 之后，通过 `setScreenAudioStreamIndex` 设置屏幕音频混流类型 |
| ByteRTCWarningInvalidVoicePitch | -5011 | 设置语音音高不合法 |
| ByteRTCWarningInvalidCallForExtAudio | -5013 | 外部音频源新旧接口混用 |
| ByteRTCWarningCodeInvalidCanvasHandle | -6001 | 指定的内部渲染画布句柄无效。  <br><br/>当你调用 [setLocalVideoCanvas:withCanvas:](macOS-api.md#ByteRTCVideo-setlocalvideocanvas-withcanvas) 或 [setRemoteVideoCanvas:withCanvas:](macOS-api.md#ByteRTCVideo-setremotevideocanvas-withcanvas) 时指定了无效的画布句柄，触发此回调。 |
| ByteRTCWarningCodeInvaildSamiAppkeyORToken | -7002 | [音频技术](https://www.volcengine.com/docs/6489/71986) SDK 鉴权失效。联系技术支持人员。 |
| ByteRTCWarningCodeInvaildSamiResourcePath | -7003 | [音频技术](https://www.volcengine.com/docs/6489/71986) 资源加载失败。传入正确的 DAT 路径，或联系技术支持人员。 |
| ByteRTCWarningCodeLoadSamiLibraryFailed | -7004 | [音频技术](https://www.volcengine.com/docs/6489/71986) 库加载失败。使用正确的库，或联系技术支持人员。 |
| ByteRTCWarningCodeInvaildSamiEffectType | -7005 | [音频技术](https://www.volcengine.com/docs/6489/71986) 不支持此音效。联系技术支持人员。 |
| [deprecated] ByteRTCWarningCodeGetRoomFailed | -2000 |  |
| [deprecated] ByteRTCWarningCodeSubscribeStreamForbiden | -2010 | 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br><br/>你需在进房前关闭自动订阅模式，再调用 [subscribeStream:mediaStreamType:](macOS-api.md#ByteRTCRoom-subscribestream-mediastreamtype) 方法手动订阅音视频流。 |
| [deprecated] ByteRTCWarningCodeRoomAlreadyExist | -2015 | 同样roomid的房间已经存在了 |
| [deprecated] ByteRTCWarningCodeNoMicrophonePermission | -5002 | 已在 3.33 版本中废弃，使用 [ByteRTCMediaDeviceError](macOS-keytype.md#bytertcmediadeviceerror).ByteRTCMediaDeviceErrorDeviceNoPermission 代替。<br><br/>麦克风权限异常，当前应用没有获取麦克风权限。 |
| [deprecated] ByteRTCWarningCodeAudioDeviceManagerRecordingStartFail | -5003 | 已在 3.33 版本中废弃，使用 [ByteRTCMediaDeviceError](macOS-keytype.md#bytertcmediadeviceerror).ByteRTCMediaDeviceErrorDeviceFailure 代替。<br><br/>音频采集设备启动失败。  <br><br/>启动音频采集设备失败，当前设备可能被其他应用占用。 |
| [deprecated] ByteRTCWarningCodeAudioDeviceManagerPlayoutStartFail | -5004 | 已在 3.33 版本中废弃，使用 [ByteRTCMediaDeviceError](macOS-keytype.md#bytertcmediadeviceerror).ByteRTCMediaDeviceErrorDeviceFailure 代替.<br><br/>音频播放设备启动失败警告。  <br><br/>可能由于系统资源不足，或参数错误。 |
| [deprecated] ByteRTCWarningCodeNoRecordingDevice | -5005 | 已在 3.33 版本中废弃，使用 [ByteRTCMediaDeviceError](macOS-keytype.md#bytertcmediadeviceerror).ByteRTCMediaDeviceErrorDeviceNotFound 代替。<br><br/>无可用音频采集设备。  <br><br/>启动音频采集设备失败，请插入可用的音频采集设备。 |
| [deprecated] ByteRTCWarningCodeNoPlayoutDevice | -5006 | 已在 3.33 版本中废弃，使用 [ByteRTCMediaDeviceError](macOS-keytype.md#bytertcmediadeviceerror).ByteRTCMediaDeviceErrorDeviceNotFound 代替。<br><br/>无可用音频播放设备。  <br><br/>启动音频播放设备失败，请插入可用的音频播放设备。 |
| [deprecated] ByteRTCWarningCodeRecordingSilence | -5007 | 已在 3.33 版本中废弃，使用 [ByteRTCMediaDeviceWarning](macOS-keytype.md#bytertcmediadevicewarning).ByteRTCMediaDeviceWarningCaptureSilence 代替。<br><br/>当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。 |
| [deprecated] ByteRTCWarningCodeMediaDeviceOperationDennied | -5008 | 已在 3.33 版本中废弃，使用 [ByteRTCMediaDeviceWarning](macOS-keytype.md#bytertcmediadevicewarning).ByteRTCMediaDeviceWarningOperationDenied 代替。<br><br/>媒体设备误操作警告。  <br><br/>使用自定义采集时，不可调用内部采集开关，调用时触发此警告。 |


# ByteRTCPublicStreamErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCPublicStreamErrorCode)
```

公共流状态码


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCPublicStreamErrorCodeSuccess | 0 | 发布或订阅成功。 |
| ByteRTCPublicStreamErrorCodePushParamError | 1191 | 公共流的参数异常，请修改参数后重试。 |
| ByteRTCPublicStreamErrorCodePushStatusError | 1192 | 服务端状态异常，将自动重试。 |
| ByteRTCPublicStreamErrorCodePushInternalError | 1193 | 内部错误，不可恢复，请重试。 |
| ByteRTCPublicStreamErrorCodePushError | 1195 | 发布失败，将自动重试，请关注重试结果。 |
| ByteRTCPublicStreamErrorCodePushTimeOut | 1196 | 发布失败，10 s 后会重试，重试 3 次后自动停止。 |
| ByteRTCPublicStreamErrorCodePullNoPushStream | 1300 | 订阅失败，发布端未开始发布流。 |


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


# ByteRTCSubtitleErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCSubtitleErrorCode)
```

字幕任务错误码。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCSubtitleErrorCodeUnknow | -1 | 客户端无法识别云端媒体处理发送的错误码。 |
| ByteRTCSubtitleErrorCodeSuccess | 0 | 字幕已开启。 |
| ByteRTCSubtitleErrorCodePostProcessError | 1 | 云端媒体处理内部出现错误，请联系技术支持。 |
| ByteRTCSubtitleErrorCodeASRConnectionError | 2 | 第三方服务连接失败，请联系技术支持。 |
| ByteRTCSubtitleErrorCodeASRServiceError | 3 | 第三方服务内部出现错误，请联系技术支持。 |
| ByteRTCSubtitleErrorCodeBeforeJoinRoom | 4 | 未进房导致调用`startSubtitle`失败。请加入房间后再调用此方法。 |
| ByteRTCSubtitleErrorCodeAlreadyOn | 5 | 字幕已开启，无需重复调用 `startSubtitle`。 |
| ByteRTCSubtitleErrorCodeUnsupportedLanguage | 6 | 用户选择的目标语言目前暂不支持。 |
| ByteRTCSubtitleErrorCodePostProcessTimeout | 7 | 云端媒体处理超时未响应，请联系技术支持。 |


# ByteRTSErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTSErrorCode)
```

回调错误码。
SDK 内部遇到不可恢复的错误时，会通过 `rtcEngine:onError:` 回调通知用户。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTSErrorCodeInvalidToken | -1000 | Token 无效。<br/>进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用<br/>`updateToken:` 方法更新 Token。 |
| ByteRTSErrorCodeJoinRoom | -1001 | 加入房间错误。<br/>进房时发生未知错误导致加入房间失败。需要用户重新加入房间。 |
| ByteRTSErrorCodeDuplicateLogin | -1004 | 相同用户 ID 的用户加入本房间，当前用户被踢出房间 |
| ByteRTSErrorCodeKickedOut | -1006 | 服务端调用 OpenAPI 将当前用户踢出房间 |
| ByteRTSErrorCodeRoomIdIllegal | -1007 | 当调用 `createRtcRoom:` ，如果 roomId 非法，会返回 null，并抛出该错误 |
| ByteRTSErrorCodeTokenExpired | -1009 | Token 过期。调用 `joinRoomByKey:roomId:userInfo:rtcRoomConfig:` 使用新的 Token 重新加入房间。 |
| ByteRTSErrorCodeUpdateTokenWithInvalidToken | -1010 | 调用 `updateToken:` 传入的 Token 无效 |
| ByteRTSErrorCodeRoomDismiss | -1011 | 服务端调用 OpenAPI 解散房间，所有用户被移出房间。 |
| ByteRTSRoomAlreadyExist | -1013 | 通话回路检测已经存在同样 roomId 的房间了 |
| ByteRTSUserIDDifferent | -1014 | 加入多个房间时使用了不同的 uid。<br><br/>同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。 |
| ByteRTSErrorCodeAbnormalServerStatus | -1084 | 服务端异常状态导致退出房间。  <br><br/>SDK与信令服务器断开，并不再自动重连，可联系技术支持。  <br> |


# ByteRTSWarningCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTSWarningCode)
```

回调警告码。
警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTSWarningCodeJoinRoomFailed | -2001 | 进房失败。  <br><br/>初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。 |
| ByteRTSWarningCodePublishStreamFailed | -2002 | 发布音视频流失败。<br/>当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。 |
| ByteRTSWarningCodeSendCustomMessage | -2011 | 发送自定义广播消息失败，当前你未在房间中。 |
| ByteRTSWarningCodeOldRoomBeenReplaced | -2016 | 新生成的房间已经替换了同样roomId的旧房间 |
| [deprecated] ByteRTSWarningCodeGetRoomFailed | -2000 |  |
| [deprecated] ByteRTSWarningCodeRoomAlreadyExist | -2015 | 同样roomid的房间已经存在了 |


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


# ByteRTCUserMessageSendResult
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCUserMessageSendResult)
```

发送消息结果，成功或失败，及失败原因


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCUserMessageSendResultSuccess | 0 | 发送消息成功 |
| ByteRTCUserMessageSendResultTimeout | 1 | 发送超时，没有发送。 |
| ByteRTCUserMessageSendResultNetworkDisconnected | 2 | 通道断开，没有发送 |
| ByteRTCUserMessageSendResultNoReceiver | 3 | 找不到接收方 |
| ByteRTCUserMessageSendResultNoRelayPath | 4 | 远端用户没有登录或进房 |
| ByteRTCUserMessageSendResultExceedQPS | 5 | 超过 QPS 限制 |
| ByteRTCUserMessageSendResultNotJoin | 100 | 消息发送方没有加入房间 |
| ByteRTCUserMessageSendResultInit | 101 | 连接未完成初始化 |
| ByteRTCUserMessageSendResultNoConnection | 102 | 没有可用的数据传输通道连接 |
| ByteRTCUserMessageSendResultExceedMaxLength | 103 | 消息超过最大长度，当前为64KB |
| ByteRTCUserMessageSendResultEmptyUser | 104 | 接收消息的单个用户 id 为空 |
| ByteRTCUserMessageSendResultNotLogin | 105 | 房间外或应用服务器消息发送方没有登录 |
| ByteRTCUserMessageSendResultServerParamsNotSet | 106 | 发送消息给业务方服务器之前没有设置参数 |
| ByteRTCUserMessageSendResultUnknown | 1000 | 失败，未知错误。 |


# ByteRTCRoomMessageSendResult
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRoomMessageSendResult)
```

房间内广播消息发送结果


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRoomMessageSendResultSuccess | 200 | 消息发送成功 |
| ByteRTCRoomMessageSendResultTimeout | 1 | 发送超时，没有发送 |
| ByteRTCRoomMessageSendResultNetworkDisconnected | 2 | 通道断开，没有发送 |
| ByteRTCRoomMessageSendResultExceedQPS | 5 | 超过 QPS 限制 |
| ByteRTCRoomMessageSendResultNotJoin | 100 | 失败，发送方未加入房间 |
| ByteRTCRoomMessageSendResultInit | 101 | 失败，连接未完成初始化。 |
| ByteRTCRoomMessageSendResultNoConnection | 102 | 失败，没有可用的连接。 |
| ByteRTCRoomMessageSendResultExceedMaxLength | 103 | 消息超过最大长度，当前为 64KB |
| ByteRTCRoomMessageSendResultUnknown | 1000 | 失败，未知错误。 |


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


# ByteRTCStreamMixingErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCStreamMixingErrorCode)
```

转推直播错误码。(新)


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCStreamMixingErrorCodeOK | 0 | 推流成功。 |
| ByteRTCStreamMixingErrorCodeBase | 1090 | 未定义的合流错误 |
| ByteRTCStreamMixingErrorCodeInvalidParam | 1091 | 客户端 SDK 检测到无效推流参数。 |
| ByteRTCStreamMixingrrorCodeInvalidState | 1092 | 状态错误，需要在状态机正常状态下发起操作 |
| ByteRTCStreamMixingErrorCodeInvalidOperator | 1093 | 无效操作 |
| ByteRTCStreamMixingErrorCodeTimeOut | 1094 | 转推直播任务处理超时，请检查网络状态并重试 |
| ByteRTCStreamMixingErrorCodeInvalidParamByServer | 1095 | 服务端检测到错误的推流参数 |
| ByteRTCStreamMixingErrorCodeSubTimeoutByServer | 1096 | 对流的订阅超时 |
| ByteRTCStreamMixingErrorCodeInvalidStateByServer | 1097 | 合流服务端内部错误。 |
| ByteRTCStreamMixingErrorCodeAuthenticationByCDN | 1098 | 合流服务端推 CDN 失败。 |
| ByteRTCStreamMixingErrorCodeTimeoutBySignaling | 1099 | 服务端接收信令超时，请检查网络状态并重试。 |
| ByteRTCStreamMixingErrorCodeMixImageFail | 1100 | 图片合流失败。 |
| ByteRTCStreamMixingErrorCodeUnKnownErrorByServer | 1101 | 服务端未知错误。 |