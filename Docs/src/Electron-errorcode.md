---
is_dir: False    # True for dir; False for doc
status: 1    # 0 for offline; 1 for online; 2 for whitelist; 4 for online but hidden in TOC
keywords: 实时音视频    # use ',' as separator
---

## UserVisibilityChangeError <span id="uservisibilitychangeerror"></span>

类型: `enum`

用户可见性状态改变错误码。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kUserVisibilityChangeErrorOk | `0` | 成功。 |
  | kUserVisibilityChangeErrorUnknown | `1` | 未知错误。 |
  | kUserVisibilityChangeErrorTooManyVisibleUser | `2` | 房间内可见用户达到上限。 |


## ForwardStreamError <span id="forwardstreamerror"></span>

类型: `enum`

媒体流跨房间转发过程中抛出的错误码

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kForwardStreamErrorOK | `0` | 正常 |
  | kForwardStreamErrorInvalidArgument | `1201` | 参数异常 |
  | kForwardStreamErrorInvalidToken | `1202` | token 错误 |
  | kForwardStreamErrorResponse | `1203` | 服务端异常 |
  | kForwardStreamErrorRemoteKicked | `1204` | 目标房间有相同 user id 的用户加入，转发中断 |
  | kForwardStreamErrorNotSupport | `1205` | 服务端不支持转发功能 |


## SubtitleErrorCode <span id="subtitleerrorcode"></span>

类型: `enum`

字幕任务错误码。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kSubtitleErrorCodeUnknow | `-1` | 客户端无法识别云端媒体处理发送的错误码。请联系技术支持。 |
  | kSubtitleErrorCodeSuccess | `0` | 字幕已开启。 |
  | kSubtitleErrorCodePostProcessError | `1` | 云端媒体处理内部出现错误，请联系技术支持。 |
  | kSubtitleErrorCodeASRConnectionError | `2` | 第三方服务连接失败，请联系技术支持。 |
  | kSubtitleErrorCodeASRServiceError | `3` | 第三方服务内部出现错误，请联系技术支持。 |
  | kSubtitleErrorCodeBeforeJoinRoom | `4` | 未进房导致调用`startSubtitle`失败。请加入房间后再调用此方法。 |
  | kSubtitleErrorCodeAlreadyOn | `5` | 重复调用 `startSubtitle`。 |
  | kSubtitleErrorCodeUnsupportedLanguage | `6` | 用户选择的目标语言目前暂不支持。 |
  | kSubtitleErrorCodePostProcessTimeout | `7` | 云端媒体处理超时未响应，请联系技术支持。 |


## KTVErrorCode <span id="ktverrorcode"></span>

类型: `enum`

KTV 错误码。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kKTVErrorCodeOK | `0` | 成功。 |
  | kKTVErrorCodeAppidInValid | `-3000` | AppID 异常。 |
  | kKTVErrorCodeParasInValid | `-3001` | 非法参数，传入的参数不正确。 |
  | kKTVErrorCodeGetMusicFailed | `-3002` | 获取歌曲资源失败。 |
  | kKTVErrorCodeGetLyricFailed | `-3003` | 获取歌词失败。 |
  | kKTVErrorCodeMusicTakedown | `-3004` | 歌曲下架。 |
  | kKTVErrorCodeMusicDownload | `-3005` | 歌曲文件下载失败。 |
  | kKTVErrorCodeMidiDownloadFailed | `-3006` | MIDI 文件下载失败。 |
  | kKTVErrorCodeSystemBusy | `-3007` | 系统繁忙。 |
  | kKTVErrorCodeNetwork | `-3008` | 网络异常。 |
  | kKTVErrorCodeNotJoinRoom | `-3009` | KTV 功能未加入房间。 |
  | kKTVErrorCodeParseData | `-3010` | 解析数据失败。 |
  | kKTVErrorCodeDownload | `-3011` | 下载失败。 |
  | kKTVErrorCodeDownloading | `-3012` | 已在下载中。 |
  | kKTVErrorCodeInternalDomain | `-3013` | 内部错误，联系技术支持人员。 |
  | kKTVErrorCodeInsufficientDiskSpace | `-3014` | 下载失败，磁盘空间不足。清除缓存后重试。 |
  | kKTVErrorCodeMusicDecryptionFailed | `-3015` | 下载失败，音乐文件解密失败，联系技术支持人员。 |
  | kKTVErrorCodeFileRenameFailed | `-3016` | 下载失败，音乐文件重命名失败，请重试。 |
  | kKTVErrorCodeDownloadTimeOut | `-3017` | 下载失败，下载超时，请重试。 |
  | kKTVErrorCodeClearCacheFailed | `-3018` | 清除缓存失败，可能原因是文件被占用或者系统异常，请重试。 |
  | kKTVErrorCodeDownloadCanceled | `-3019` | 取消下载。 |


## KTVPlayerErrorCode <span id="ktvplayererrorcode"></span>

类型: `enum`

KTV 播放器错误码。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kKTVPlayerErrorCodeOK | `0` | 成功。 |
  | kKTVPlayerErrorCodeFileNotExist | `-3020` | 播放错误，请下载后播放。 |
  | kKTVPlayerErrorCodeFileError | `-3021` | 播放错误，请确认文件播放格式。 |
  | kKTVPlayerErrorCodeNotJoinRoom | `-3022` | 播放错误，未进入房间。 |
  | kKTVPlayerErrorCodeParam | `-3023` | 参数错误。 |
  | kKTVPlayerErrorCodeStartError | `-3024` | 播放失败，找不到文件或文件打开失败。 |
  | kKTVPlayerErrorCodeMixIdError | `-3025` | 混音 ID 异常。 |
  | kKTVPlayerErrorCodePositionError | `-3026` | 设置播放位置出错。 |
  | kKTVPlayerErrorCodeAudioVolumeError | `-3027` | 音量参数不合法，可设置的取值范围为 [0,400]。 |
  | kKTVPlayerErrorCodeTypeError | `-3028` | 不支持此混音类型。 |
  | kKTVPlayerErrorCodePitchError | `-3029` | 音调文件不合法。 |
  | kKTVPlayerErrorCodeAudioTrackError | `-3030` | 音轨不合法。 |
  | kKTVPlayerErrorCodeStartingError | `-3031` | 混音启动中。 |


## AudioRecordingErrorCode <span id="audiorecordingerrorcode"></span>

类型: `enum`

音频文件录制的错误码

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioRecordingErrorCodeOk | `0` | 录制正常 |
  | kAudioRecordingErrorCodeNoPermission | `-1` | 没有文件写权限 |
  | kAudioRecordingErrorCodeNotInRoom | `-2` | 没有进入房间 |
  | kAudioRecordingErrorCodeAlreadyStarted | `-3` | 录制已经开始 |
  | kAudioRecordingErrorCodeNotStarted | `-4` | 录制还未开始 |
  | kAudioRecordingErrorCodeNotSupport | `-5` | 录制失败。文件格式不支持。 |
  | kAudioRecordingErrorCodeOther | `-6` | 其他异常 |


## LocalProxyError <span id="localproxyerror"></span>

类型: `enum`

本地代理错误信息。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLocalProxyErrorOK | `0` | 代理无错误 |
  | kLocalProxyErrorSocks5VersionError | `1` | 代理服务器回复的版本号错误，导致 socks5 连接失败。 |
  | kLocalProxyErrorSocks5FormatError | `2` | 代理服务器回复的格式错误，导致 socks5 连接失败。 |
  | kLocalProxyErrorSocks5InvalidValue | `3` | 代理服务器回复的字段值错误，导致 socks5 连接失败。 |
  | kLocalProxyErrorSocks5UserPassNotGiven | `4` | 未提供本地代理的用户名及密码，导致 socks5 连接失败。 |
  | kLocalProxyErrorSocks5TcpClosed | `5` | TCP 关闭，导致 socks5 连接失败。 |
  | kLocalProxyErrorHttpTunnelFailed | `6` | http隧道代理错误。 |


## StreamMixingErrorCode <span id="streammixingerrorcode"></span>

类型: `enum`

转推直播错误码

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kStreamMixingErrorCodeOK | `0` | 推流成功。 |
  | kStreamMixingErrorCodeBase | `1090` | 未定义的合流错误 |
  | kStreamMixingErrorCodeInvalidParam | `1091` | 客户端 SDK 检测到无效推流参数。 |
  | kStreamMixingErrorCodeInvalidState | `1092` | 状态错误，需要在状态机正常状态下发起操作 |
  | kStreamMixingErrorCodeInvalidOperator | `1093` | 无效操作 |
  | kStreamMixingErrorCodeTimeout | `1094` | 转推直播任务处理超时，请检查网络状态并重试 |
  | kStreamMixingErrorCodeInvalidParamByServer | `1095` | 服务端检测到错误的推流参数 |
  | kStreamMixingErrorCodeSubTimeoutByServer | `1096` | 对流的订阅超时 |
  | kStreamMixingErrorCodeInvalidStateByServer | `1097` | 合流服务端内部错误。 |
  | kStreamMixingErrorCodeAuthenticationByCDN | `1098` | 合流服务端推 CDN 失败。 |
  | kStreamMixingErrorCodeTimeoutBySignaling | `1099` | 服务端接收信令超时，请检查网络状态并重试。 |
  | kStreamMixingErrorCodeMixImageFail | `1100` | 图片合流失败。 |
  | kStreamMixingErrorCodeUnKnownByServer | `1101` | 服务端未知错误。 |


## PublicStreamErrorCode <span id="publicstreamerrorcode"></span>

类型: `enum`

公共流状态码

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kPublicStreamErrorCodeOK | `0` | 发布或订阅成功。 |
  | kPublicStreamErrorCodePushInvalidParam | `1191` | 公共流的参数异常，请修改参数后重试。 |
  | kPublicStreamErrorCodePushInvalidStatus | `1192` | 服务端状态异常，将自动重试。 |
  | kPublicStreamErrorCodePushInternalError | `1193` | 内部错误，不可恢复，请重试。 |
  | kPublicStreamErrorCodePushFailed | `1195` | 发布失败，将自动重试，请关注重试结果。 |
  | kPublicStreamErrorCodePushTimeout | `1196` | 发布失败，10 s 后会重试，重试 3 次后自动停止。 |
  | kPublicStreamErrorCodePullNoPushStream | `1300` | 订阅失败，发布端未开始发布流。 |


## WarningCode <span id="warningcode"></span>

类型: `enum`

回调警告码。警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kWarningCodeJoinRoomFailed | `-2001` | 进房失败。<br>当你调用初次加入房间或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。 |
  | kWarningCodePublishStreamFailed | `-2002` | 发布音视频流失败。<br>当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。 |
  | kWarningCodeSubscribeStreamFailed404 | `-2003` | 订阅音视频流失败。<br>当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。 |
  | kWarningCodeSubscribeStreamFailed5xx | `-2004` | 订阅音视频流失败。<br>当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。 |
  | kWarningCodePublishStreamForbiden | `-2009` | 当调用 [`setUserVisibility`](Electron-api#rtcroom-setuservisibility) 将自身可见性设置为 false 后，再尝试发布流会触发此警告。 |
  | kWarningCodeSendCustomMessage | `-2011` | 发送自定义广播消息失败，当前你未在房间中。 |
  | kWarningCodeUserNotifyStop | `-2013` | 当房间内人数超过 500 人时，停止向房间内已有用户发送 [onUserJoined](Electron-event#onuserjoined) 和 [onUserLeave](Electron-event#onuserleave) 回调，并通过广播提示房间内所有用户。 |
  | kWarningCodeUserInPublish | `-2014` | 用户已经在其他房间发布过流，或者用户正在发布公共流。 |
  | kWarningCodeOldRoomBeenReplaced | `-2016` | 新生成的房间已经替换了同样roomId的旧房间 |
  | kWarningCodeInEchoTestMode | `-2017` | 当前正在进行回路测试，该接口调用无效 |
  | kWarningCodeNoCameraPermission | `-5001` | 摄像头权限异常，当前应用没有获取摄像头权限。 |
  | kWarningCodeSetScreenAudioStreamIndexFailed | `-5010` | 不支持在 [publishScreen](Electron-api#publishscreen) 之后，<br>通过 [setScreenAudioStreamIndex](Electron-api#setscreenaudiostreamindex) 设置屏幕共享时的音频采集方式。 |
  | kWarningCodeInvalidVoicePitch | `-5011` | 设置语音音高不合法 |
  | kWarningCodeInvalidAudioFormat | `-5012` | 设置音频格式不合法 |
  | kWarningCodeInvalidCallForExtAudio | `-5013` | 外部音频源新旧接口混用 |
  | kWarningCodeInvalidCanvasHandle | `-6001` | 指定的内部渲染画布句柄无效。   当你调用 [setupLocalVideo(Electron-api#setuplocalvideo) 或 [setupRemoteVideo](Electron-api#setupremotevideo) 时指定了无效的画布句柄，触发此回调。 |
  | kWarningLicenseFileExpired | `-7001` | 鉴权文件失效，当检查鉴权文件状态时，本地文件与远端文件不一致会触发次警告。 |
  | kWarningInvaildSamiAppkeyORToken | `-7002` | [音频技术](https://www.volcengine.com/docs/6489/71986) SDK 鉴权失效。联系技术支持人员。 |
  | kWarningInvaildSamiResourcePath | `-7003` | [音频技术](https://www.volcengine.com/docs/6489/71986) 资源加载失败。传入正确的 DAT 路径，或联系技术支持人员。 |
  | kWarningLoadSamiLibraryFailed | `-7004` | [音频技术](https://www.volcengine.com/docs/6489/71986) 库加载失败。使用正确的库，或联系技术支持人员。 |
  | kWarningInvaildSamiEffectType | `-7005` | [音频技术](https://www.volcengine.com/docs/6489/71986) 不支持此音效。联系技术支持人员。 |


## ErrorCode <span id="errorcode"></span>

类型: `enum`

回调错误码。  SDK 内部遇到不可恢复的错误时，会通过 [onError](Electron-event#rtcvideocallback-onerror) 回调通知用户。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kErrorCodeInvalidToken | `-1000` | Token 无效。调用 [joinRoom](Electron-api#joinroom) 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用 [updateToken](Electron-api#updatetoken) 方法更新 Token。 |
  | kErrorCodeJoinRoom | `-1001` | 加入房间错误。调用 [joinRoom](Electron-api#joinroom) 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。 |
  | kErrorCodeNoPublishPermission | `-1002` | 没有发布音视频流权限。用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。 |
  | kErrorCodeNoSubscribePermission | `-1003` | 没有订阅音视频流权限。用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。 |
  | kErrorCodeDuplicateLogin | `-1004` | 用户重复登录。本地用户所在房间中有相同用户 ID 的用户加入房间，导致本地用户被踢出房间。 |
  | kErrorCodeKickedOut | `-1006` | 服务端调用 OpenAPI 将当前用户踢出房间 |
  | kRoomErrorCodeRoomIdIllegal | `-1007` | 当调用 createRTCRoom ，如果roomid 非法，会返回null，并抛出该error |
  | kRoomErrorTokenExpired | `-1009` | Token 过期。调用 joinRoom 使用新的 Token 重新加入房间。 |
  | kRoomErrorUpdateTokenWithInvalidToken | `-1010` | 调用 updateToken 传入的 Token 无效 |
  | kErrorCodeRoomDismiss | `-1011` | 服务端调用 OpenAPI 解散房间，所有用户被移出房间。 |
  | kErrorCodeJoinRoomWithoutLicenseAuthenticateSDK | `-1012` | 加入房间错误。进房时, LICENSE 计费账号未使用 LICENSE_AUTHENTICATE SDK，加入房间错误。 |
  | kErrorCodeRoomAlreadyExist | `-1013` | 通话回路检测已经存在同样 roomId 的房间了 |
  | kErrorCodeOverStreamSubscribeLimit | `-1070` | 订阅音视频流失败，订阅音视频流总数超过上限。游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。 |
  | kErrorCodeOverStreamPublishLimit | `-1080` | 发布流失败，发布流总数超过上限。 RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。 |
  | kErrorCodeInvalidAudioSyncUidRepeated | `-1083` | 音视频同步失败。当前音频源已与其他视频源关联同步关系。单个音频源不支持与多个视频源同时同步。 |
  | kErrorCodeAbnormalServerStatus | `-1084` | 服务端异常状态导致退出房间。SDK与信令服务器断开，并不再自动重连，可联系技术支持。 |
  | kErrorCodeJoinRoomRoomForbidden | `-1025` | 房间被封禁。 |
  | kErrorCodeJoinRoomUserForbidden | `-1026` | 用户被封禁。 |
  | kErrorCodeJoinRoomLicenseFunctionNotFound | `-1027` | license 计费方法没有加载成功。可能是因为 license 相关插件未正确集成。 |


## AudioMixingError <span id="audiomixingerror"></span>

类型: `enum`

音频混音文件播放错误码。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioMixingErrorOk | `0` | 正常 |
  | kAudioMixingErrorPreloadFailed | `1` | 预加载失败，找不到混音文件或者文件长度超出 20s |
  | kAudioMixingErrorStartFailed | `2` | 混音开启失败，找不到混音文件或者混音文件打开失败 |
  | kAudioMixingErrorIdNotFound | `3` | 混音 ID 异常 |
  | kAudioMixingErrorSetPositionFailed | `4` | 设置混音文件的播放位置出错 |
  | kAudioMixingErrorInValidVolume | `5` | 音量参数不合法，仅支持设置的音量值为[0, 400] |
  | kAudioMixingErrorLoadConflict | `6` | 播放的文件与预加载的文件不一致，请先使用 [unloadAudioMixing](Electron-api#unloadaudiomixing) 卸载文件 |
  | kAudioMixingErrorIdTypeNotMatch | `7` | 不支持此混音类型。 |
  | kAudioMixingErrorInValidPitch | `8` | 设置混音文件的音调不合法 |
  | kAudioMixingErrorInValidAudioTrack | `9` | 设置混音文件的音轨不合法 |
  | kAudioMixingErrorIsStarting | `10` | 混音文件正在启动中 |
  | kAudioMixingErrorInValidPlaybackSpeed | `11` | 设置混音文件的播放速度不合法 |


## LocalAudioStreamError <span id="localaudiostreamerror"></span>

类型: `enum`

本地音频流状态改变时的错误码。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLocalAudioStreamErrorOk | `0` | 本地音频状态正常 |
  | kLocalAudioStreamErrorFailure | `1` | 本地音频出错原因未知 |
  | kLocalAudioStreamErrorDeviceNoPermission | `2` | 没有权限启动本地音频录制设备 |
  | kLocalAudioStreamErrorRecordFailure | `4` | 本地音频录制失败，建议你检查录制设备是否正常工作 |
  | kLocalAudioStreamErrorEncodeFailure | `5` | 本地音频编码失败 |
  | kLocalAudioStreamErrorNoRecordingDevice | `6` | 没有可用的音频录制设备 |


## LocalVideoStreamError <span id="localvideostreamerror"></span>

类型: `enum`

本地视频状态改变时的错误码

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLocalVideoStreamErrorOk | `0` | 状态正常 |
  | kLocalVideoStreamErrorFailure | `1` | 本地视频流发布失败 |
  | kLocalVideoStreamErrorDeviceNoPermission | `2` | 没有权限启动本地视频采集设备 |
  | kLocalVideoStreamErrorDeviceBusy | `3` | 本地视频采集设备被占用 |
  | kLocalVideoStreamErrorDeviceNotFound | `4` | 本地视频采集设备不存在 |
  | kLocalVideoStreamErrorCaptureFailure | `5` | 本地视频采集失败，建议检查采集设备是否正常工作 |
  | kLocalVideoStreamErrorEncodeFailure | `6` | 本地视频编码失败 |
  | kLocalVideoStreamErrorDeviceDisconnected | `7` | 通话过程中本地视频采集设备被其他程序抢占，导致设备连接中断 |


## MessageSendResultCode <span id="messagesendresultcode"></span>

类型: `enum`

发送用户消息或者房间消息的结果

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | MESSAGE_CODE_SUCCESS | `0` | 用户 P2P 消息发送成功 |
  | MESSAGE_CODE_ROOM_SUCCESS | `200` | 房间 Broadcast 消息发送成功 |
  | MESSAGE_CODE_ERROR_TIMEOUT | `1` | 发送超时，没有发送 |
  | MESSAGE_CODE_ERROR_BROKEN | `2` | 通道断开，没有发送 |
  | MESSAGE_CODE_ERROR_NOT_RECEIVER | `3` | 找不到接收方 |
  | MESSAGE_CODE_ERROR_NOT_JOIN | `100` | 消息发送方没有加入房间 |
  | MESSAGE_CODE_ERROR_NO_CONNECTION | `102` | 没有可用的数据传输通道连接 |
  | MESSAGE_CODE_ERROR_EXCEED_MAX_LENGTH | `103` | 消息超过最大长度，当前为64KB |
  | MESSAGE_CODE_ERROR_EMPTY_USER | `104` | 接收消息的单个用户 id 为空 |
  | MESSAGE_CODE_ERROR_UNKNOWN | `1000` | 未知错误 |


## PlayerError <span id="playererror"></span>

类型: `enum`

播放错误码。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kPlayerErrorOK | `0` | 正常 |
  | kPlayerErrorFormatNotSupport | `1` | 不支持此类型 |
  | kPlayerErrorInvalidPath | `2` | 无效的播放路径 |
  | kPlayerErrorInvalidState | `3` | 未满足前序接口调用的要求。请查看具体接口文档。 |
  | kPlayerErrorInvalidPosition | `4` | 设置播放位置出错。 |
  | kPlayerErrorInvalidVolume | `5` | 音量参数不合法。 |
  | kPlayerErrorInvalidPitch | `6` | 音调参数设置不合法。 |
  | kPlayerErrorInvalidAudioTrackIndex | `7` | 音轨参数设置不合法。 |
  | kPlayerErrorInvalidPlaybackSpeed | `8` | 播放速度参数设置不合法 |
  | kPlayerErrorInvalidEffectId | `9` | 音效 ID 异常。还未加载或播放文件，就调用其他 API。 |
