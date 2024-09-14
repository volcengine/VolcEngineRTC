---
is_dir: False    # True for dir; False for doc
status: 1    # 1 for online; 0 for offline
keywords: 实时音视频    # use ',' as separator
---
<span id="ByteRTCMediaPlayerAudioFrameObserver"></span>
# ByteRTCMediaPlayerAudioFrameObserver
```objectivec
@protocol ByteRTCMediaPlayerAudioFrameObserver <NSObject>
```
本地音频文件混音的音频帧观察者。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onFrame:audioFrame:](#ByteRTCMediaPlayerAudioFrameObserver-onframe-audioframe) |

## 函数说明
<span id="ByteRTCMediaPlayerAudioFrameObserver-onframe-audioframe"></span>
### onFrame:audioFrame:
```objectivec
- (void)onFrame:(int)playerId audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
当本地音频文件混音时，回调播放的音频帧。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| playerId | int | 播放器 ID |
| audioFrame | ByteRTCAudioFrame * | 参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame)。 |


<span id="ByteRTCFaceDetectionObserver"></span>
# ByteRTCFaceDetectionObserver
```objectivec
@protocol ByteRTCFaceDetectionObserver <NSObject>
```
人脸检测结果回调观察者

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onFaceDetectResult:](#ByteRTCFaceDetectionObserver-onfacedetectresult) |

## 函数说明
<span id="ByteRTCFaceDetectionObserver-onfacedetectresult"></span>
### onFaceDetectResult:
```objectivec
- (void)onFaceDetectResult:(ByteRTCFaceDetectionResult * _Nonnull)result;
```
特效 SDK 进行人脸检测结果的回调。

调用 [enableFaceDetection:withInterval:withModelPath:](macOS-api#ByteRTCVideoEffect-enablefacedetection-withinterval-withmodelpath) 注册了 [ByteRTCFaceDetectionObserver](#ByteRTCFaceDetectionObserver) ，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| result | ByteRTCFaceDetectionResult * | 人脸检测结果, 参看 [ByteRTCFaceDetectionResult](macOS-keytype#ByteRTCFaceDetectionResult)。 |


<span id="ByteRTCEncryptHandler"></span>
# ByteRTCEncryptHandler
```objectivec
@protocol ByteRTCEncryptHandler <NSObject>
```
自定义加密接口

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| NSData *  | [onEncryptData:](#ByteRTCEncryptHandler-onencryptdata) |
| NSData *  | [onDecryptData:](#ByteRTCEncryptHandler-ondecryptdata) |

## 函数说明
<span id="ByteRTCEncryptHandler-onencryptdata"></span>
### onEncryptData:
```objectivec
- (NSData * _Nonnull) onEncryptData:(NSData * _Nonnull)rawData;
```
自定义加密。

使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。

暂不支持对原始音视频帧进行加密。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rawData | NSData * | 原始音视频帧数据 |


**返回值**

加密后的数据
- 非空，表示加密后的数据
- 为空，表示数据被丢弃


**注意**

- 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 `setCustomizeEncryptHandler:`。
- 使用 [onDecryptData:](#ByteRTCEncryptHandler-ondecryptdata) 对已加密的音视频帧数据进行解密。
- 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。

<span id="ByteRTCEncryptHandler-ondecryptdata"></span>
### onDecryptData:
```objectivec
- (NSData * _Nonnull) onDecryptData:(NSData * _Nonnull)rawData;
```
自定义解密。

对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 [onEncryptData:](#ByteRTCEncryptHandler-onencryptdata)。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rawData | NSData * | 收到的已加密的音视频帧数据 |


**返回值**

解密后的数据
- 非空，表示解密后的数据
- 为空，表示丢弃该帧


**注意**

- 使用此接口进行解密前，你必须先设定解密方式，参看 `setCustomizeEncryptHandler:`。
- 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。

<span id="ByteRTCPushSingleStreamToCDNObserver"></span>
# ByteRTCPushSingleStreamToCDNObserver
```objectivec
@protocol ByteRTCPushSingleStreamToCDNObserver <NSObject>
```
单流转推直播观察者。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onStreamPushEvent:taskId:error:](#ByteRTCPushSingleStreamToCDNObserver-onstreampushevent-taskid-error) |

## 函数说明
<span id="ByteRTCPushSingleStreamToCDNObserver-onstreampushevent-taskid-error"></span>
### onStreamPushEvent:taskId:error:
```objectivec
- (void)onStreamPushEvent:(ByteRTCSingleStreamPushEvent)event
                   taskId:(NSString *_Nonnull)taskID
                    error:(NSInteger)errorCode;
```
单流转推直播状态回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | ByteRTCSingleStreamPushEvent | 任务状态, 参看 [ByteRTCSingleStreamPushEvent](macOS-errorcode#ByteRTCSingleStreamPushEvent). |
| taskID | NSString * | 任务 ID |
| errorCode | NSInteger | 错误码，参看 [ByteRtcTranscoderErrorCode](macOS-errorcode#ByteRtcTranscoderErrorCode)。 |


<span id="ByteRTCVideoSnapshotCallbackDelegate"></span>
# ByteRTCVideoSnapshotCallbackDelegate
```objectivec
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSnapshotCallbackDelegate <NSObject>
```
截取视频画面回调类

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onTakeLocalSnapshotResult:streamIndex:image:errorCode:](#ByteRTCVideoSnapshotCallbackDelegate-ontakelocalsnapshotresult-streamindex-image-errorcode) |
| void | [onTakeRemoteSnapshotResult:streamKey:image:errorCode:](#ByteRTCVideoSnapshotCallbackDelegate-ontakeremotesnapshotresult-streamkey-image-errorcode) |

## 函数说明
<span id="ByteRTCVideoSnapshotCallbackDelegate-ontakelocalsnapshotresult-streamindex-image-errorcode"></span>
### onTakeLocalSnapshotResult:streamIndex:image:errorCode:
```objectivec
- (void)onTakeLocalSnapshotResult:(NSInteger) taskId
                      streamIndex:(ByteRTCStreamIndex)streamIndex
                            image:(ByteRTCImage * _Nullable)image
                        errorCode:(NSInteger)errorCode;
```
调用 [takeLocalSnapshot:callback:](macOS-api#ByteRTCVideo-takelocalsnapshot-callback) 截取视频画面时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | NSInteger | 本地截图任务的编号。和 [takeLocalSnapshot:callback:](macOS-api#ByteRTCVideo-takelocalsnapshot-callback) 的返回值一致。 |
| streamIndex | ByteRTCStreamIndex | 截图的视频流的属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex)。 |
| image | ByteRTCImage *_Nullable | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | NSInteger | 截图错误码：<br><ul><li>0: 成功</li><li>-1: 截图错误。生成图片数据失败或 RGBA 编码失败</li><li>-2: 截图错误。流无效。</li><li>-3: 截图错误。截图超时,超时时间 1 秒。</li></ul> |


<span id="ByteRTCVideoSnapshotCallbackDelegate-ontakeremotesnapshotresult-streamkey-image-errorcode"></span>
### onTakeRemoteSnapshotResult:streamKey:image:errorCode:
```objectivec
- (void)onTakeRemoteSnapshotResult:(NSInteger)taskId
                         streamKey:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                             image:(ByteRTCImage * _Nullable)image
                         errorCode:(NSInteger)errorCode;
```
调用 [takeRemoteSnapshot:callback:](macOS-api#ByteRTCVideo-takeremotesnapshot-callback) 截取视频画面时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| taskId | NSInteger | 远端截图任务的编号。和 [takeRemoteSnapshot:callback:](macOS-api#ByteRTCVideo-takeremotesnapshot-callback) 的返回值一致。 |
| streamKey | ByteRTCRemoteStreamKey * | 截图的视频流，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey)。 |
| image | ByteRTCImage *_Nullable | 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。 |
| errorCode | NSInteger | 截图错误码：<br><ul><li>0: 成功</li><li>-1: 截图错误。生成图片数据失败或 RGBA 编码失败</li><li>-2: 截图错误。流无效。</li><li>-3: 截图错误。截图超时,超时时间 1 秒。</li></ul> |


<span id="ByteRTCSingScoringDelegate"></span>
# ByteRTCSingScoringDelegate
```objectivec
BYTERTC_APPLE_EXPORT @protocol ByteRTCSingScoringDelegate<NSObject>
```
K 歌评分事件回调类。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onCurrentScoringInfo:](#ByteRTCSingScoringDelegate-oncurrentscoringinfo) |

## 函数说明
<span id="ByteRTCSingScoringDelegate-oncurrentscoringinfo"></span>
### onCurrentScoringInfo:
```objectivec
- (void)onCurrentScoringInfo:(ByteRTCSingScoringRealtimeInfo * _Nullable)info;
```
实时评分信息回调。调用 [startSingScoring:scoringInfoInterval:](macOS-api#ByteRTCSingScoringManager-startsingscoring-scoringinfointerval) 后，会收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| info | ByteRTCSingScoringRealtimeInfo *_Nullable | 实时评分信息。详见 [ByteRTCSingScoringRealtimeInfo](macOS-keytype#ByteRTCSingScoringRealtimeInfo)。 |


<span id="ByteRTCMixedStreamObserver"></span>
# ByteRTCMixedStreamObserver
```objectivec
@protocol ByteRTCMixedStreamObserver <NSObject>
```
转推直播观察者。(Valid from 352.1)

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| BOOL | [isSupportClientPushStream](#ByteRTCMixedStreamObserver-issupportclientpushstream) |
| void | [onMixingEvent:taskId:error:mixType:](#ByteRTCMixedStreamObserver-onmixingevent-taskid-error-mixtype) |
| void | [onMixingAudioFrame:timestamp:taskId:](#ByteRTCMixedStreamObserver-onmixingaudioframe-timestamp-taskid) |
| void | [onMixingVideoFrame:taskId:](#ByteRTCMixedStreamObserver-onmixingvideoframe-taskid) |
| void | [onMixingDataFrame:taskId:](#ByteRTCMixedStreamObserver-onmixingdataframe-taskid) |

## 函数说明
<span id="ByteRTCMixedStreamObserver-issupportclientpushstream"></span>
### isSupportClientPushStream
```objectivec
_- (BOOL)isSupportClientPushStream;
```
是否具有推流能力。
- false：不具备推流能力（默认值）
- true：具备推流能力


**注意**

- 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。

<span id="ByteRTCMixedStreamObserver-onmixingevent-taskid-error-mixtype"></span>
### onMixingEvent:taskId:error:mixType:
```objectivec
- (void)onMixingEvent:(ByteRTCStreamMixingEvent)event
               taskId:(NSString *_Nonnull)taskId
                error:(ByteRTCStreamMixingErrorCode)errorCode
              mixType:(ByteRTCMixedStreamType)mixType;
```
转推直播状态回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | ByteRTCStreamMixingEvent | 转推直播任务状态，参看 [ByteRTCStreamMixingEvent](macOS-keytype#ByteRTCStreamMixingEvent)。 |
| taskId | NSString * | 转推直播任务 ID。 |
| errorCode | ByteRTCStreamMixingErrorCode | 转推直播错误码，参看 [ByteRTCStreamMixingErrorCode](macOS-errorcode#ByteRTCStreamMixingErrorCode)。 |
| mixType | ByteRTCMixedStreamType | 转推直播类型，参看 [ByteRTCMixedStreamType](macOS-keytype#ByteRTCMixedStreamType)。 |


<span id="ByteRTCMixedStreamObserver-onmixingaudioframe-timestamp-taskid"></span>
### onMixingAudioFrame:timestamp:taskId:
```objectivec
- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame timestamp:(int64_t)timeStamp taskId:(NSString *_Nonnull)taskId;
```
端云一体合流音频 PCM 回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | ByteRTCAudioFrame * | PCM 编码的合流音频数据帧，参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame)。 |
| timeStamp | int64_t | 时间戳，单位毫秒。 |
| taskId | NSString * | 转推直播任务 ID。 |


**注意**

收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

<span id="ByteRTCMixedStreamObserver-onmixingvideoframe-taskid"></span>
### onMixingVideoFrame:taskId:
```objectivec
- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流视频 YUV 回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoFrame | ByteRTCVideoFrame * | YUV 合流视频数据帧，参看 [ByteRTCVideoFrame](macOS-keytype#ByteRTCVideoFrame)。 |
| taskId | NSString * | 转推直播任务 ID。 |


**注意**

收到该回调的周期取决于视频的帧率。

<span id="ByteRTCMixedStreamObserver-onmixingdataframe-taskid"></span>
### onMixingDataFrame:taskId:
```objectivec
- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流视频 SEI 数据


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| dataFrame | ByteRTCFrameExtendedData * | SEI 数据，详见 [ByteRTCFrameExtendedData](macOS-keytype#ByteRTCFrameExtendedData)。 |
| taskId | NSString * | 转推直播任务 ID。 |


<span id="ByteRTCAudioFrameObserver"></span>
# ByteRTCAudioFrameObserver
```objectivec
@protocol ByteRTCAudioFrameObserver <NSObject>
```
音频数据回调观察者

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。

本接口类中的单个回调的数据量为 20 ms 的数据量。回调周期在 20 ms 上下浮动。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onRecordAudioFrame:](#ByteRTCAudioFrameObserver-onrecordaudioframe) |
| void | [onPlaybackAudioFrame:](#ByteRTCAudioFrameObserver-onplaybackaudioframe) |
| void | [onRemoteUserAudioFrame:audioFrame:](#ByteRTCAudioFrameObserver-onremoteuseraudioframe-audioframe) |
| void | [onMixedAudioFrame:](#ByteRTCAudioFrameObserver-onmixedaudioframe) |

## 函数说明
<span id="ByteRTCAudioFrameObserver-onrecordaudioframe"></span>
### onRecordAudioFrame:
```objectivec
- (void)onRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回麦克风录制的音频数据


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | ByteRTCAudioFrame * | 音频数据, 详见： [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame) |


<span id="ByteRTCAudioFrameObserver-onplaybackaudioframe"></span>
### onPlaybackAudioFrame:
```objectivec
- (void)onPlaybackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回订阅的所有远端用户混音后的音频数据。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | ByteRTCAudioFrame * | 音频数据, 详见： [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame) |


<span id="ByteRTCAudioFrameObserver-onremoteuseraudioframe-audioframe"></span>
### onRemoteUserAudioFrame:audioFrame:
```objectivec
- (void)onRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                    audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回远端单个用户的音频数据


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | ByteRTCRemoteStreamKey * | 远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey)。 |
| audioFrame | ByteRTCAudioFrame * | 音频数据，参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame)。 |


**注意**

此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。

<span id="ByteRTCAudioFrameObserver-onmixedaudioframe"></span>
### onMixedAudioFrame:
```objectivec
- (void)onMixedAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
返回本地麦克风录制和订阅的所有远端用户混音后的音频数据


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | ByteRTCAudioFrame * | 音频数据, 详见： [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame) |


<span id="ByteRtcScreenCapturerExtDelegate"></span>
# ByteRtcScreenCapturerExtDelegate
```objectivec
BYTE_RTC_EXPORT @protocol ByteRtcScreenCapturerExtDelegate <NSObject>
```
屏幕采集相关扩展协议，仅适用于 SDK 内部采集。

用户创建 extension 后生成的 SampleHandler 需继承此协议以实现屏幕共享相关能力。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onQuitFromApp](#ByteRtcScreenCapturerExtDelegate-onquitfromapp) |
| void | [onReceiveMessageFromApp:](#ByteRtcScreenCapturerExtDelegate-onreceivemessagefromapp) |
| void | [onSocketDisconnect](#ByteRtcScreenCapturerExtDelegate-onsocketdisconnect) |
| void | [onSocketConnect](#ByteRtcScreenCapturerExtDelegate-onsocketconnect) |
| void | [onNotifyAppRunning](#ByteRtcScreenCapturerExtDelegate-onnotifyapprunning) |

## 函数说明
<span id="ByteRtcScreenCapturerExtDelegate-onquitfromapp"></span>
### onQuitFromApp
```objectivec
- (void)onQuitFromApp;
```
通知 Broadcast Upload Extension 停止采集屏幕并退出。


**注意**

iOS 端调用 [stopScreenCapture](iOS-api#ByteRTCVideo-stopscreencapture)，或 macOS 端调用 [stopScreenVideoCapture](macOS-api#ByteRTCVideo-stopscreenvideocapture)，会触发该方法通知 extension 端的 SDK 停止屏幕采集。

<span id="ByteRtcScreenCapturerExtDelegate-onreceivemessagefromapp"></span>
### onReceiveMessageFromApp:
```objectivec
- (void)onReceiveMessageFromApp:(NSData *)message;
```
Socket 收到 App 侧发来的信息时，触发该回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | NSData * | App 侧发送的消息 |


<span id="ByteRtcScreenCapturerExtDelegate-onsocketdisconnect"></span>
### onSocketDisconnect
```objectivec
- (void)onSocketDisconnect;
```
Socket 连接断开时触发此回调


<span id="ByteRtcScreenCapturerExtDelegate-onsocketconnect"></span>
### onSocketConnect
```objectivec
- (void)onSocketConnect;
```
Socket 连接成功时触发此回调


<span id="ByteRtcScreenCapturerExtDelegate-onnotifyapprunning"></span>
### onNotifyAppRunning
```objectivec
- (void)onNotifyAppRunning;
```
检测到 App 正在进行音视频通话时触发此回调。


<span id="ByteRTCAudioEffectPlayerEventHandler"></span>
# ByteRTCAudioEffectPlayerEventHandler
```objectivec
@protocol ByteRTCAudioEffectPlayerEventHandler <NSObject>
```
[ByteRTCAudioEffectPlayer](macOS-api#ByteRTCAudioEffectPlayer) 对应的回调句柄。你必须调用 [setEventHandler:](macOS-api#ByteRTCAudioEffectPlayer-seteventhandler) 完成设置后，才能收到对应回调。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onAudioEffectPlayerStateChanged:state:error:](#ByteRTCAudioEffectPlayerEventHandler-onaudioeffectplayerstatechanged-state-error) |

## 函数说明
<span id="ByteRTCAudioEffectPlayerEventHandler-onaudioeffectplayerstatechanged-state-error"></span>
### onAudioEffectPlayerStateChanged:state:error:
```objectivec
-(void)onAudioEffectPlayerStateChanged:(int)effectId state:(ByteRTCPlayerState)state error:(ByteRTCPlayerError)error;
```
播放状态改变时回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| effectId | int | [ByteRTCAudioEffectPlayer](macOS-api#ByteRTCAudioEffectPlayer) 的 ID。通过 [getAudioEffectPlayer](macOS-api#ByteRTCVideo-getaudioeffectplayer) 设置。 |
| state | ByteRTCPlayerState | 混音状态。参考 [ByteRTCPlayerState](macOS-keytype#ByteRTCPlayerState)。 |
| error | ByteRTCPlayerError | 错误码。参考 [ByteRTCPlayerError](macOS-keytype#ByteRTCPlayerError)。 |


<span id="ByteRTCAudioFrameProcessor"></span>
# ByteRTCAudioFrameProcessor
```objectivec
@protocol ByteRTCAudioFrameProcessor <NSObject>
```
自定义音频处理器

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| int | [onProcessRecordAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessrecordaudioframe) |
| int | [onProcessPlayBackAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe) |
| int | [onProcessRemoteUserAudioFrame:audioFrame:](#ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe) |
| int | [onProcessScreenAudioFrame:](#ByteRTCAudioFrameProcessor-onprocessscreenaudioframe) |

## 函数说明
<span id="ByteRTCAudioFrameProcessor-onprocessrecordaudioframe"></span>
### onProcessRecordAudioFrame:
```objectivec
- (int)onProcessRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调本地采集的音频帧地址，供自定义音频处理。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | ByteRTCAudioFrame * | 音频帧地址，参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame)。 |


**返回值**

- 0： 成功。
- < 0： 失败。


**注意**

- 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。此音频处理不会影响软件耳返音频数据。
- 要启用此回调，必须调用 `enableAudioProcessor`，并在参数中选择本地采集的音频，每 10 ms 收到此回调。

<span id="ByteRTCAudioFrameProcessor-onprocessplaybackaudioframe"></span>
### onProcessPlayBackAudioFrame:
```objectivec
- (int)onProcessPlayBackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调远端音频混音的音频帧地址，供自定义音频处理。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | ByteRTCAudioFrame * | 音频帧地址，参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame) |


**注意**

调用 `enableAudioProcessor`,并在参数中选择远端音频流的的混音音频时，每 10 ms 收到此回调。

<span id="ByteRTCAudioFrameProcessor-onprocessremoteuseraudioframe-audioframe"></span>
### onProcessRemoteUserAudioFrame:audioFrame:
```objectivec
- (int)onProcessRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey  audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调单个远端用户的音频帧地址，供自定义音频处理。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | ByteRTCRemoteStreamKey * | 音频流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |
| audioFrame | ByteRTCAudioFrame * | 音频帧地址，参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame) |


**注意**

调用 `enableAudioProcessor`,并在参数中选择各个远端音频流时，每 10 ms 收到此回调。

<span id="ByteRTCAudioFrameProcessor-onprocessscreenaudioframe"></span>
### onProcessScreenAudioFrame:
```objectivec
- (int)onProcessScreenAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
```
回调屏幕共享的音频帧地址，供自定义音频处理。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | ByteRTCAudioFrame * | 音频帧地址，参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame)。 |


**注意**

调用 `enableAudioProcessor:`，把返回给音频处理器的音频类型设置为屏幕共享音频后，每 10 ms 收到此回调。

<span id="ByteRTCRoomDelegate"></span>
# ByteRTCRoomDelegate
```objectivec
@protocol ByteRTCRoomDelegate <NSObject>
```
房间事件回调接口

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) |
| void | [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) |
| void | [rtcRoom:onLeaveRoom:](#ByteRTCRoomDelegate-rtcroom-onleaveroom) |
| void | [rtcRoom:onAVSyncStateChange:](#ByteRTCRoomDelegate-rtcroom-onavsyncstatechange) |
| void | [rtcRoom:onRoomStats:](#ByteRTCRoomDelegate-rtcroom-onroomstats) |
| void | [rtcRoom:onLocalStreamStats:](#ByteRTCRoomDelegate-rtcroom-onlocalstreamstats) |
| void | [rtcRoom:onRemoteStreamStats:](#ByteRTCRoomDelegate-rtcroom-onremotestreamstats) |
| void | [rtcRoom:onUserJoined:elapsed:](#ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed) |
| void | [rtcRoom:onUserLeave:reason:](#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) |
| void | [onTokenWillExpire:](#ByteRTCRoomDelegate-ontokenwillexpire) |
| void | [onPublishPrivilegeTokenWillExpire:](#ByteRTCRoomDelegate-onpublishprivilegetokenwillexpire) |
| void | [onSubscribePrivilegeTokenWillExpire:](#ByteRTCRoomDelegate-onsubscribeprivilegetokenwillexpire) |
| void | [rtcRoom:onUserPublishStream:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) |
| void | [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) |
| void | [rtcRoom:onUserPublishScreen:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) |
| void | [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) |
| void | [rtcRoom:onStreamSubscribed:userId:subscribeConfig:](#ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig) |
| void | [rtcRoom:onRoomMessageReceived:message:](#ByteRTCRoomDelegate-rtcroom-onroommessagereceived-message) |
| void | [rtcRoom:onRoomBinaryMessageReceived:message:](#ByteRTCRoomDelegate-rtcroom-onroombinarymessagereceived-message) |
| void | [rtcRoom:onUserMessageReceived:message:](#ByteRTCRoomDelegate-rtcroom-onusermessagereceived-message) |
| void | [rtcRoom:onUserBinaryMessageReceived:message:](#ByteRTCRoomDelegate-rtcroom-onuserbinarymessagereceived-message) |
| void | [rtcRoom:onUserMessageSendResult:error:](#ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error) |
| void | [rtcRoom:onRoomMessageSendResult:error:](#ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error) |
| void | [rtcRoom:onSetRoomExtraInfoResult:error:](#ByteRTCRoomDelegate-rtcroom-onsetroomextrainforesult-error) |
| void | [rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:](#ByteRTCRoomDelegate-rtcroom-onroomextrainfoupdate-value-lastupdateuserid-lastupdatetimems) |
| void | [rtcRoom:onUserVisibilityChanged:errorCode:](#ByteRTCRoomDelegate-rtcroom-onuservisibilitychanged-errorcode) |
| void | [rtcRoom:onVideoStreamBanned:isBanned:](#ByteRTCRoomDelegate-rtcroom-onvideostreambanned-isbanned) |
| void | [rtcRoom:onAudioStreamBanned:isBanned:](#ByteRTCRoomDelegate-rtcroom-onaudiostreambanned-isbanned) |
| void | [rtcRoom:onForwardStreamStateChanged:](#ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged) |
| void | [rtcRoom:onForwardStreamEvent:](#ByteRTCRoomDelegate-rtcroom-onforwardstreamevent) |
| void | [rtcRoom:onNetworkQuality:remoteQualities:](#ByteRTCRoomDelegate-rtcroom-onnetworkquality-remotequalities) |
| void | [rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:](#ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage) |
| void | [rtcRoom:onSubtitleMessageReceived:](#ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived) |
| void | [deprecated] [rtcRoom:onRoomWarning:](#ByteRTCRoomDelegate-rtcroom-onroomwarning) |
| void | [deprecated] [rtcRoom:onRoomError:](#ByteRTCRoomDelegate-rtcroom-onroomerror) |
| void | [deprecated] [rtcRoom:onStreamAdd:](#ByteRTCRoomDelegate-rtcroom-onstreamadd) |
| void | [deprecated] [rtcRoom:onStreamRemove:stream:reason:](#ByteRTCRoomDelegate-rtcroom-onstreamremove-stream-reason) |

## 函数说明
<span id="ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo"></span>
### rtcRoom:onRoomStateChanged:withUid:state:extraInfo:
```objectivec
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomStateChanged:(NSString *_Nonnull)roomId
        withUid:(nonnull NSString *)uid
          state:(NSInteger)state
      extraInfo:(NSString *_Nonnull)extraInfo;
```
房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCAudioRoom 实例 |
| roomId | NSString * | 房间 ID。 |
| uid | NSString * | 用户 ID。 |
| state | NSInteger | 房间状态码。<br><ul><li>0: 加入房间成功。</li><li>!0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 [ByteRTCErrorCode](macOS-errorcode#ByteRTCErrorCode) 及 [ByteRTCWarningCode](macOS-errorcode#ByteRTCWarningCode)。</li></ul> |
| extraInfo | NSString * | 额外信息，如 `{"elapsed":1187,"join_type":0}`。<br>`join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。<br>`elapsed`表示加入房间耗时，即本地用户从调用 [joinRoom:userInfo:roomConfig:](macOS-api#ByteRTCRoom-joinroom-userinfo-roomconfig) 到加入房间成功所经历的时间间隔，单位为 ms。 |


<span id="ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo"></span>
### rtcRoom:onStreamStateChanged:withUid:state:extraInfo:
```objectivec
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamStateChanged:(NSString *_Nonnull)roomId
        withUid:(nonnull NSString *)uid
          state:(NSInteger)state
      extraInfo:(NSString *_Nonnull)extraInfo;
```
流状态改变回调，发生流相关的警告或错误时会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | `ByteRTCRoom` 实例 |
| roomId | NSString * | 房间 ID。 |
| uid | NSString * | 用户 ID。 |
| state | NSInteger | 流状态码，参看 [ByteRTCErrorCode](macOS-errorcode#ByteRTCErrorCode) 及 [ByteRTCWarningCode](macOS-errorcode#ByteRTCWarningCode)。 |
| extraInfo | NSString * | 附加信息，目前为空。 |


<span id="ByteRTCRoomDelegate-rtcroom-onleaveroom"></span>
### rtcRoom:onLeaveRoom:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLeaveRoom:(ByteRTCRoomStats *_Nonnull)stats;
```
离开房间成功回调。

用户调用 [leaveRoom](macOS-api#ByteRTCRoom-leaveroom) 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| stats | ByteRTCRoomStats * | 保留参数，目前为空。 |


**注意**

- 用户调用 [leaveRoom](macOS-api#ByteRTCRoom-leaveroom) 方法离开房间后，如果立即调用 [destroy](macOS-api#ByteRTCRoom-destroy) 销毁房间实例或 destroyRTCVideo 方法销毁 RTC 引擎，则将无法收到此回调事件。
- 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。

<span id="ByteRTCRoomDelegate-rtcroom-onavsyncstatechange"></span>
### rtcRoom:onAVSyncStateChange:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAVSyncStateChange:(ByteRTCAVSyncState)state;
```
发布端调用 [setMultiDeviceAVSync:](macOS-api#ByteRTCRoom-setmultideviceavsync) 后音视频同步状态发生改变时，会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 实例 |
| state | ByteRTCAVSyncState | 音视频同步状态，参看 [ByteRTCAVSyncState](macOS-keytype#ByteRTCAVSyncState)。 |


<span id="ByteRTCRoomDelegate-rtcroom-onroomstats"></span>
### rtcRoom:onRoomStats:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onRoomStats:));
```
房间内通话统计信息回调。

用户进房开始通话后，每 2s 收到一次本回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| stats | ByteRTCRoomStats * | 当前 ByteRTCRoom 统计数据，详见： [ByteRTCRoomStats](macOS-keytype#ByteRTCRoomStats) |


<span id="ByteRTCRoomDelegate-rtcroom-onlocalstreamstats"></span>
### rtcRoom:onLocalStreamStats:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onLocalStreamStats:));
```
本地流数据统计以及网络质量回调。

本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。

统计信息通过 [ByteRTCLocalStreamStats](macOS-keytype#ByteRTCLocalStreamStats) 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| stats | ByteRTCLocalStreamStats * | 当前房间本地流数据统计。详见： [ByteRTCLocalStreamStats](macOS-keytype#ByteRTCLocalStreamStats) |


<span id="ByteRTCRoomDelegate-rtcroom-onremotestreamstats"></span>
### rtcRoom:onRemoteStreamStats:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onRemoteStreamStats:));
```
本地订阅的远端音/视频流数据统计以及网络质量回调。

本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| stats | ByteRTCRemoteStreamStats * | 当前房间本地流数据统计。 详见： [ByteRTCRemoteStreamStats](macOS-keytype#ByteRTCRemoteStreamStats) |


<span id="ByteRTCRoomDelegate-rtcroom-onuserjoined-elapsed"></span>
### rtcRoom:onUserJoined:elapsed:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;
```
远端可见用户加入房间，或房内不可见用户切换为可见的回调。

1. 远端用户调用 [setUserVisibility:](macOS-api#ByteRTCRoom-setuservisibility) 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。

2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。

3. 房间内隐身远端用户调用 [setUserVisibility:](macOS-api#ByteRTCRoom-setuservisibility) 方法切换至可见时，房间内其他用户将收到该事件。

4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| userInfo | ByteRTCUserInfo * | 用户信息，参看 [ByteRTCUserInfo](macOS-keytype#ByteRTCUserInfo)。 |
| elapsed | NSInteger | 保留字段，无意义 |


<span id="ByteRTCRoomDelegate-rtcroom-onuserleave-reason"></span>
### rtcRoom:onUserLeave:reason:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;
```
远端用户离开房间，或切至不可见时，本地用户会收到此事件


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | `ByteRTCRoom` 实例 |
| uid | NSString * | 离开房间，或切至不可见的的远端用户 ID。 |
| reason | ByteRTCUserOfflineReason | 用户离开房间的原因：<br><ul><li>0: 远端用户调用 [leaveRoom](macOS-api#ByteRTCRoom-leaveroom) 主动退出房间。</li><li>1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376)</li><li>2: 远端用户调用 [setUserVisibility:](macOS-api#ByteRTCRoom-setuservisibility) 切换至不可见状态。</li><li>3: 服务端调用 OpenAPI 将远端用户踢出房间。</li></ul> |


<span id="ByteRTCRoomDelegate-ontokenwillexpire"></span>
### onTokenWillExpire:
```objectivec
- (void)onTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
```
当 SDK 检测到 Token 的进房权限将在 30 秒内过期时，触发该回调。

收到该回调后，你需调用 [updateToken:](macOS-api#ByteRTCRoom-updatetoken) 更新 Token 进房权限。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | `ByteRTCRoom` 实例 |


**注意**

若 Token 进房权限过期且未及时更新：
- 用户此时尝试进房会收到 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1000` Token 无效；
- 用户已在房间内则会被移出房间，本地用户会收到 [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1009` Token 过期，同时远端用户会收到 [rtcRoom:onUserLeave:reason:](#ByteRTCRoomDelegate-rtcroom-onuserleave-reason) 回调，提示原因为 `1` Token 进房权限过期。

<span id="ByteRTCRoomDelegate-onpublishprivilegetokenwillexpire"></span>
### onPublishPrivilegeTokenWillExpire:
```objectivec
- (void)onPublishPrivilegeTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
```
Token 发布权限过期前 30 秒将触发该回调。

收到该回调后，你需调用 [updateToken:](macOS-api#ByteRTCRoom-updatetoken) 更新 Token 发布权限。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | `ByteRTCRoom` 实例 |


**注意**

若收到该回调后未及时更新 Token，Token 发布权限过期后：
- 此时尝试发布流会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1002` 没有发布权限；
- 已在发布中的流会停止发布，发布端会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason)/ [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) 回调，提示原因为 `6` 发流端发布权限过期。

<span id="ByteRTCRoomDelegate-onsubscribeprivilegetokenwillexpire"></span>
### onSubscribePrivilegeTokenWillExpire:
```objectivec
- (void)onSubscribePrivilegeTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
```
Token 订阅权限过期前 30 秒将触发该回调。

收到该回调后，你需调用 [updateToken:](macOS-api#ByteRTCRoom-updatetoken) 更新 Token 订阅权限有效期。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | `ByteRTCRoom` 实例 |


**注意**

若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) 回调，提示错误码为 `-1003` 没有订阅权限。

<span id="ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type"></span>
### rtcRoom:onUserPublishStream:type:
```objectivec
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
```
房间内新增远端摄像头/麦克风采集的媒体流的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 实例 |
| userId | NSString * | 远端流发布用户的用户 ID。 |
| type | ByteRTCMediaStreamType | 远端媒体流的类型，参看 [ByteRTCMediaStreamType](macOS-keytype#ByteRTCMediaStreamType)。 |


**注意**

当房间内的远端用户调用 [publishStream:](macOS-api#ByteRTCRoom-publishstream) 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeStream:mediaStreamType:](macOS-api#ByteRTCRoom-subscribestream-mediastreamtype) 订阅此流。

<span id="ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason"></span>
### rtcRoom:onUserUnpublishStream:type:reason:
```objectivec
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserUnpublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
         reason:(ByteRTCStreamRemoveReason)reason;
```
房间内远端摄像头/麦克风采集的媒体流移除的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 实例 |
| userId | NSString * | 移除的远端流发布用户的用户 ID。 |
| type | ByteRTCMediaStreamType | 移除的远端流类型，参看 [ByteRTCMediaStreamType](macOS-keytype#ByteRTCMediaStreamType)。 |
| reason | ByteRTCStreamRemoveReason | 远端流移除的原因，参看 [ByteRTCStreamRemoveReason](macOS-keytype#ByteRTCStreamRemoveReason)。 |


**注意**

收到该回调通知后，你可以自行选择是否调用 [unsubscribeStream:mediaStreamType:](macOS-api#ByteRTCRoom-unsubscribestream-mediastreamtype) 取消订阅此流。

<span id="ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type"></span>
### rtcRoom:onUserPublishScreen:type:
```objectivec
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
```
房间内新增远端屏幕共享音视频流的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 实例 |
| userId | NSString * | 远端流发布用户的用户 ID。 |
| type | ByteRTCMediaStreamType | 远端媒体流的类型，参看 [ByteRTCMediaStreamType](macOS-keytype#ByteRTCMediaStreamType)。 |


**注意**

当房间内的远端用户调用 [publishScreen:](macOS-api#ByteRTCRoom-publishscreen) 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 [subscribeScreen:mediaStreamType:](macOS-api#ByteRTCRoom-subscribescreen-mediastreamtype) 订阅此流。

<span id="ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason"></span>
### rtcRoom:onUserUnpublishScreen:type:reason:
```objectivec
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserUnpublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
         reason:(ByteRTCStreamRemoveReason)reason;
```
房间内远端屏幕共享音视频流移除的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 实例 |
| userId | NSString * | 移除的远端流发布用户的用户 ID。 |
| type | ByteRTCMediaStreamType | 移除的远端流类型，参看 [ByteRTCMediaStreamType](macOS-keytype#ByteRTCMediaStreamType)。 |
| reason | ByteRTCStreamRemoveReason | 远端流移除的原因，参看 [ByteRTCStreamRemoveReason](macOS-keytype#ByteRTCStreamRemoveReason)。 |


**注意**

收到该回调通知后，你可以自行选择是否调用 [unsubscribeScreen:mediaStreamType:](macOS-api#ByteRTCRoom-unsubscribescreen-mediastreamtype) 取消订阅此流。

<span id="ByteRTCRoomDelegate-rtcroom-onstreamsubscribed-userid-subscribeconfig"></span>
### rtcRoom:onStreamSubscribed:userId:subscribeConfig:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamSubscribed:(ByteRTCSubscribeState)state
         userId:(NSString *_Nonnull)userId
subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;
```
关于订阅媒体流状态改变的回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| state | ByteRTCSubscribeState | 订阅媒体流状态，参看 [ByteRTCSubscribeState](macOS-keytype#ByteRTCSubscribeState) |
| userId | NSString * | 流发布用户的用户 ID |
| info | ByteRTCSubscribeConfig * | 流的属性，参看 [ByteRTCSubscribeConfig](macOS-keytype#ByteRTCSubscribeConfig) |


**注意**

本地用户收到该回调的时机包括：
- 调用 [subscribeStream:mediaStreamType:](macOS-api#ByteRTCRoom-subscribestream-mediastreamtype) 或 [unsubscribeStream:mediaStreamType:](macOS-api#ByteRTCRoom-unsubscribestream-mediastreamtype) 订阅/取消订阅指定远端摄像头音视频流后；
- 调用 [subscribeScreen:mediaStreamType:](macOS-api#ByteRTCRoom-subscribescreen-mediastreamtype) 或 [unsubscribeScreen:mediaStreamType:](macOS-api#ByteRTCRoom-unsubscribescreen-mediastreamtype) 订阅/取消订阅指定远端屏幕共享流后。

<span id="ByteRTCRoomDelegate-rtcroom-onroommessagereceived-message"></span>
### rtcRoom:onRoomMessageReceived:message:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;
```
收到房间中调用 [sendRoomMessage:](macOS-api#ByteRTCRoom-sendroommessage) 发送的广播文本消息时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| uid | NSString * | 消息发送者 ID 。 |
| message | NSString * | 收到的文本消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onroombinarymessagereceived-message"></span>
### rtcRoom:onRoomBinaryMessageReceived:message:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;
```
收到房间内广播二进制消息的回调。

房间内其他用户调用 [sendRoomBinaryMessage:](macOS-api#ByteRTCRoom-sendroombinarymessage) 发送的广播二进制消息时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| uid | NSString * | 消息发送者 ID 。 |
| message | NSData * | 收到的二进制消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onusermessagereceived-message"></span>
### rtcRoom:onUserMessageReceived:message:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;
```
收到来自房间中其他用户通过 [sendUserMessage:message:config:](macOS-api#ByteRTCRoom-sendusermessage-message-config) 发来的点对点文本消息时，会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| uid | NSString * | 消息发送者的用户 ID 。 |
| message | NSString * | 收到的文本消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onuserbinarymessagereceived-message"></span>
### rtcRoom:onUserBinaryMessageReceived:message:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;
```
收到来自房间中其他用户通过 [sendUserBinaryMessage:message:config:](macOS-api#ByteRTCRoom-senduserbinarymessage-message-config) 发来的点对点二进制消息时，会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| uid | NSString * | 消息发送者的用户 ID 。 |
| message | NSData * | 收到的二进制消息内容。 |


<span id="ByteRTCRoomDelegate-rtcroom-onusermessagesendresult-error"></span>
### rtcRoom:onUserMessageSendResult:error:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(NSInteger)msgid error:(ByteRTCUserMessageSendResult)error;
```
向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| msgid | NSInteger | 本条消息的 ID。 |
| error | ByteRTCUserMessageSendResult | 消息发送结果，详见 [ByteRTCUserMessageSendResult](macOS-errorcode#ByteRTCUserMessageSendResult) |


**注意**

- 你应调用 [sendUserMessage:message:config:](macOS-api#ByteRTCRoom-sendusermessage-message-config) 向房间内单个用户发送文本消息
- 你应调用 [sendUserBinaryMessage:message:config:](macOS-api#ByteRTCRoom-senduserbinarymessage-message-config) 向房间内单个用户发送二进制消息

<span id="ByteRTCRoomDelegate-rtcroom-onroommessagesendresult-error"></span>
### rtcRoom:onRoomMessageSendResult:error:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(NSInteger)msgid error:(ByteRTCRoomMessageSendResult)error;
```
调用 [sendRoomMessage:](macOS-api#ByteRTCRoom-sendroommessage) 或 [sendRoomBinaryMessage:](macOS-api#ByteRTCRoom-sendroombinarymessage) 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| msgid | NSInteger | 本条消息的 ID。 |
| error | ByteRTCRoomMessageSendResult | 消息发送结果，详见 [ByteRTCRoomMessageSendResult](macOS-errorcode#ByteRTCRoomMessageSendResult) |


<span id="ByteRTCRoomDelegate-rtcroom-onsetroomextrainforesult-error"></span>
### rtcRoom:onSetRoomExtraInfoResult:error:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSetRoomExtraInfoResult:(NSInteger)taskId error:(ByteRTCSetRoomExtraInfoResult)error;
```
> Available since 3.52.

调用 [setRoomExtraInfo:value:](macOS-api#ByteRTCRoom-setroomextrainfo-value) 结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| taskId | NSInteger | 本次调用的任务编号。 |
| error | ByteRTCSetRoomExtraInfoResult | 设置房间附加信息结果，详见 [ByteRTCSetRoomExtraInfoResult](macOS-keytype#ByteRTCSetRoomExtraInfoResult) |


<span id="ByteRTCRoomDelegate-rtcroom-onroomextrainfoupdate-value-lastupdateuserid-lastupdatetimems"></span>
### rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomExtraInfoUpdate:(NSString *_Nonnull)key value:(NSString *_Nonnull)value lastUpdateUserId:(NSString *_Nonnull)lastUpdateUserId
lastUpdateTimeMs:(NSInteger)lastUpdateTimeMs;
```
> Available since 3.52.

接收到房间附加信息的回调。

房间内其他用户调用 [setRoomExtraInfo:value:](macOS-api#ByteRTCRoom-setroomextrainfo-value) 设置房间附加信息，收到此回调。

另外用户加入房间成功后会收到这个房间全量附加信息


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| key | NSString * | 附加信息的键值 |
| value | NSString * | 附加信息的内容 |
| lastUpdateUserId | NSString * | 最后更新这条附加信息的用户编号 |
| lastUpdateTimeMs | NSInteger | 最后更新这条附加信息的 Unix 时间，时间精度是毫秒 |


<span id="ByteRTCRoomDelegate-rtcroom-onuservisibilitychanged-errorcode"></span>
### rtcRoom:onUserVisibilityChanged:errorCode:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserVisibilityChanged:(BOOL)currentUserVisibility errorCode:(ByteRTCUserVisibilityChangeError)errorCode;
```
> Available since 3.54

用户调用 [setUserVisibility:](macOS-api#ByteRTCRoom-setuservisibility) 设置用户可见性的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | `ByteRTCRoom` 实例 |
| currentUserVisibility | BOOL | 当前用户的可见性。<br><ul><li>YES: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。</li><li>NO: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。</li></ul> |
| errorCode | ByteRTCUserVisibilityChangeError | 设置用户可见性错误码，参看 [ByteRTCUserVisibilityChangeError](macOS-keytype#ByteRTCUserVisibilityChangeError)。 |


<span id="ByteRTCRoomDelegate-rtcroom-onvideostreambanned-isbanned"></span>
### rtcRoom:onVideoStreamBanned:isBanned:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onVideoStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | `ByteRTCRoom` 实例 |
| uid | NSString * | 被禁用/解禁的视频流用户 ID |
| banned | BOOL | 视频流发送状态<br><ul><li>true: 视频流发送被禁用</li><li>false: 视频流发送被解禁</li></ul> |


**注意**

- 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。
- 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。
- 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。
- 同一房间解散后再次创建，房间内状态清空。

<span id="ByteRTCRoomDelegate-rtcroom-onaudiostreambanned-isbanned"></span>
### rtcRoom:onAudioStreamBanned:isBanned:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAudioStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;
```
通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | 参看 [ByteRTCRoom](macOS-api#ByteRTCRoom)。 |
| uid | NSString * | 被禁用/解禁的音频流用户 ID |
| banned | BOOL | 音频流发送状态<br><ul><li>true: 音频流发送被禁用</li><li>false: 音频流发送被解禁</li></ul> |


**注意**

- 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。
- 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。
- 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。
- 在控制台开启音频选路后，只有被封禁/解禁用户会收到该回调。
- 同一房间解散后再次创建，房间内状态清空。

<span id="ByteRTCRoomDelegate-rtcroom-onforwardstreamstatechanged"></span>
### rtcRoom:onForwardStreamStateChanged:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onForwardStreamStateChanged:(NSArray<ByteRTCForwardStreamStateInfo *> * _Nonnull)infos;
```
跨房间媒体流转发状态和错误回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| infos | NSArray<ByteRTCForwardStreamStateInfo *\> * | 跨房间媒体流转发目标房间信息数组，详见 [ByteRTCForwardStreamStateInfo](macOS-keytype#ByteRTCForwardStreamStateInfo) |


<span id="ByteRTCRoomDelegate-rtcroom-onforwardstreamevent"></span>
### rtcRoom:onForwardStreamEvent:
```objectivec
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onForwardStreamEvent:(NSArray<ByteRTCForwardStreamEventInfo *> * _Nonnull)infos;
```
跨房间媒体流转发事件回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| infos | NSArray<ByteRTCForwardStreamEventInfo *\> * | 跨房间媒体流转发目标房间事件数组，详见 [ByteRTCForwardStreamEventInfo](macOS-keytype#ByteRTCForwardStreamEventInfo) |


<span id="ByteRTCRoomDelegate-rtcroom-onnetworkquality-remotequalities"></span>
### rtcRoom:onNetworkQuality:remoteQualities:
```objectivec
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onNetworkQuality:(ByteRTCNetworkQualityStats *_Nonnull)localQuality remoteQualities:(NSArray<ByteRTCNetworkQualityStats*> *_Nonnull)remoteQualities;
```
加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| localQuality | ByteRTCNetworkQualityStats * | 本端网络质量，详见 [ByteRTCNetworkQualityStats](macOS-keytype#ByteRTCNetworkQualityStats)。 |
| remoteQualities | NSArray<ByteRTCNetworkQualityStats *\> * | 已订阅用户的网络质量，详见 [ByteRTCNetworkQualityStats](macOS-keytype#ByteRTCNetworkQualityStats)。 |


**注意**

更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。

<span id="ByteRTCRoomDelegate-rtcroom-onsubtitlestatechanged-errorcode-errormessage"></span>
### rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSubtitleStateChanged:(ByteRTCSubtitleState)state
      errorCode:(ByteRTCSubtitleErrorCode)errorCode
   errorMessage:(NSString *_Nonnull)errorMessage;
```
字幕状态发生改变回调。

当用户调用 [startSubtitle:](macOS-api#ByteRTCRoom-startsubtitle) 和 [stopSubtitle](macOS-api#ByteRTCRoom-stopsubtitle) 使字幕状态发生改变或出现错误时，触发该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 实例。 |
| state | ByteRTCSubtitleState | 字幕状态。参看 [ByteRTCSubtitleState](macOS-keytype#ByteRTCSubtitleState)。 |
| errorCode | ByteRTCSubtitleErrorCode | 字幕任务错误码。参看 [ByteRTCSubtitleErrorCode](macOS-errorcode#ByteRTCSubtitleErrorCode)。 |
| errorMessage | NSString * | 第三方服务出现的错误。当因第三方服务出现错误，导致字幕状态改变时，用户可通过此参数获取具体的错误信息。如果不是因为第三方服务导致字幕状态改变，该字段为空。 |


<span id="ByteRTCRoomDelegate-rtcroom-onsubtitlemessagereceived"></span>
### rtcRoom:onSubtitleMessageReceived:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSubtitleMessageReceived:(NSArray<ByteRTCSubtitleMessage*> * _Nonnull)subtitles;
```
字幕相关内容回调。

当用户调用 [startSubtitle:](macOS-api#ByteRTCRoom-startsubtitle) 后会收到此回调，通知字幕的相关信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 实例。 |
| subtitles | NSArray<ByteRTCSubtitleMessage *\> * | 字幕消息内容。参看 [ByteRTCSubtitleMessage](macOS-keytype#ByteRTCSubtitleMessage)。 |


<span id="ByteRTCRoomDelegate-rtcroom-onroomwarning"></span>
### rtcRoom:onRoomWarning:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode __deprecated_msg("Will be removed in new version");
```
> Deprecated since 3.41 and will be deleted in 3.51, use [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) and [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) instead.

发生警告回调。

SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| warningCode | ByteRTCWarningCode | 警告码，详见枚举类型 [ByteRTCWarningCode](macOS-errorcode#ByteRTCWarningCode)。 |


<span id="ByteRTCRoomDelegate-rtcroom-onroomerror"></span>
### rtcRoom:onRoomError:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode __deprecated_msg("Will be removed in new version");
```
> Deprecated since 3.41 and will be deleted in 3.51, use [rtcRoom:onRoomStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onroomstatechanged-withuid-state-extrainfo) and [rtcRoom:onStreamStateChanged:withUid:state:extraInfo:](#ByteRTCRoomDelegate-rtcroom-onstreamstatechanged-withuid-state-extrainfo) instead.

发生错误回调。

SDK 运行时出现了错误。SDK 通常无法自动恢复，应用需要采取行动。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| errorCode | ByteRTCErrorCode | 错误码，详见枚举类型 [ByteRTCErrorCode](macOS-errorcode#ByteRTCErrorCode)。 |


<span id="ByteRTCRoomDelegate-rtcroom-onstreamadd"></span>
### rtcRoom:onStreamAdd:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream __deprecated_msg("Will be removed in new version");
```
> Deprecated since 3.36 and will be deleted in 3.51, use [rtcRoom:onUserPublishStream:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type) and [rtcRoom:onUserPublishScreen:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type) instead.

以下情况会触发此回调：
- 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调通知。
- 房间内的用户原音视频流被移出后，又重新发布音视频流时，房间内的其他用户会收到此回调通知。
- 用户刚加入房间时，会收到此回调，包含房间中所有已发布的流。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象。 |
| stream | id<ByteRTCStream\> | 流属性，参看 [ByteRTCStream](macOS-keytype#ByteRTCStream) 。 |


<span id="ByteRTCRoomDelegate-rtcroom-onstreamremove-stream-reason"></span>
### rtcRoom:onStreamRemove:stream:reason:
```objectivec
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamRemove:(NSString *_Nonnull)uid
         stream:(id<ByteRTCStream> _Nonnull)stream
         reason:(ByteRTCStreamRemoveReason)reason
__deprecated_msg("Will be removed in new version");
```
> Deprecated since 3.36 and will be deleted in 3.51, use [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) and [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) instead.

房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rtcRoom | ByteRTCRoom * | ByteRTCRoom 对象 |
| uid | NSString * | 远端流来源的用户 ID 。 |
| stream | id<ByteRTCStream\> | 流的属性，参看 [ByteRTCStream](macOS-keytype#ByteRTCStream)。 |
| reason | ByteRTCStreamRemoveReason | 远端流移除的原因，参看 [ByteRTCStreamRemoveReason](macOS-keytype#ByteRTCStreamRemoveReason)。 |


<span id="ByteRTCExternalVideoEncoderEventHandler"></span>
# ByteRTCExternalVideoEncoderEventHandler
```objectivec
BYTERTC_APPLE_EXPORT @protocol ByteRTCExternalVideoEncoderEventHandler<NSObject>
```
自定义编码帧回调类


**注意**

回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。

## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onStart:](#ByteRTCExternalVideoEncoderEventHandler-onstart) |
| void | [onStop:](#ByteRTCExternalVideoEncoderEventHandler-onstop) |
| void | [onRateUpdate:withVideoIndex:withFps:withBitRate:](#ByteRTCExternalVideoEncoderEventHandler-onrateupdate-withvideoindex-withfps-withbitrate) |
| void | [onRequestKeyFrame:withVideoIndex:](#ByteRTCExternalVideoEncoderEventHandler-onrequestkeyframe-withvideoindex) |
| void | [onActiveVideoLayer:withVideoIndex:withActive:](#ByteRTCExternalVideoEncoderEventHandler-onactivevideolayer-withvideoindex-withactive) |

## 函数说明
<span id="ByteRTCExternalVideoEncoderEventHandler-onstart"></span>
### onStart:
```objectivec
- (void)onStart:(ByteRTCStreamIndex)streamIndex;
```
提示自定义编码帧可以开始推送的回调。

收到该回调后，你即可调用 [pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:](macOS-api#ByteRTCVideo-pushexternalencodedvideoframe-withvideoindex-withencodedvideoframe) 向 SDK 推送自定义编码视频帧


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | ByteRTCStreamIndex | 可以推送的编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |


<span id="ByteRTCExternalVideoEncoderEventHandler-onstop"></span>
### onStop:
```objectivec
- (void)onStop:(ByteRTCStreamIndex)streamIndex;
```
当收到该回调时，你需停止向 SDK 推送自定义编码视频帧


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | ByteRTCStreamIndex | 需停止推送的编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |


<span id="ByteRTCExternalVideoEncoderEventHandler-onrateupdate-withvideoindex-withfps-withbitrate"></span>
### onRateUpdate:withVideoIndex:withFps:withBitRate:
```objectivec
- (void)onRateUpdate:(ByteRTCStreamIndex)streamIndex
      withVideoIndex:(NSInteger)videoIndex
             withFps:(NSInteger)fps
         withBitRate:(NSInteger)bitRateKps;
```
当自定义编码流的帧率或码率发生变化时，触发该回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | ByteRTCStreamIndex | 发生变化的编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |
| videoIndex | NSInteger | 对应编码流的下标 |
| fps | NSInteger | 变化后的帧率，单位：fps |
| bitRateKps | NSInteger | 变化后的码率，单位：kbps |


<span id="ByteRTCExternalVideoEncoderEventHandler-onrequestkeyframe-withvideoindex"></span>
### onRequestKeyFrame:withVideoIndex:
```objectivec
- (void)onRequestKeyFrame:(ByteRTCStreamIndex)streamIndex
           withVideoIndex:(NSInteger)videoIndex;
```
提示流发布端需重新生成关键帧的回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | ByteRTCStreamIndex | 远端编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |
| videoIndex | NSInteger | 对应编码流的下标 |


<span id="ByteRTCExternalVideoEncoderEventHandler-onactivevideolayer-withvideoindex-withactive"></span>
### onActiveVideoLayer:withVideoIndex:withActive:
```objectivec
- (void)onActiveVideoLayer:(ByteRTCStreamIndex)streamIndex
            withVideoIndex:(NSInteger)videoIndex
                withActive:(BOOL)active;
```
> Available since 3.56

作为自定义编码视频流的发送端，你会在视频流可发送状态发生变化时，收到此回调。

你可以根据此回调的提示，仅对可发送的视频流进行编码，以降低本端视频编码性能消耗。此回调会根据多个因素综合判断触发，包括：本端设备性能和本端网络性能，以及按需订阅场景下，远端用户是否订阅。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | ByteRTCStreamIndex | 远端编码流的属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex)。 |
| videoIndex | NSInteger | 对应编码流的下标 |
| active | BOOL | 该路流可发送状态 |


**注意**

要收到此回调，必须调用 [setVideoSourceType:WithStreamIndex:](macOS-api#ByteRTCVideo-setvideosourcetype-withstreamindex) 设置视频源是自定义编码，且通过 [setExternalVideoEncoderEventHandler:](macOS-api#ByteRTCVideo-setexternalvideoencodereventhandler) 设置了回调句柄。

<span id="ByteRTCAudioFileFrameObserver"></span>
# ByteRTCAudioFileFrameObserver
```objectivec
@protocol ByteRTCAudioFileFrameObserver <NSObject>
```
本地音频文件混音的音频帧观察者。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [deprecated] [onAudioFileFrame:audioFrame:](#ByteRTCAudioFileFrameObserver-onaudiofileframe-audioframe) |

## 函数说明
<span id="ByteRTCAudioFileFrameObserver-onaudiofileframe-audioframe"></span>
### onAudioFileFrame:audioFrame:
```objectivec
- (void)onAudioFileFrame:(int)mixID audioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");
```
> Deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead 

当本地音频文件混音时，回调播放的音频帧。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixID | int | 混音 ID。 |
| audioFrame | ByteRTCAudioFrame * | 参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame)。 |


<span id="ByteRTCVideoProcessorDelegate"></span>
# ByteRTCVideoProcessorDelegate
```objectivec
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoProcessorDelegate <NSObject>
```
视频处理回调接口类

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| ByteRTCVideoFrame | [processVideoFrame:](#ByteRTCVideoProcessorDelegate-processvideoframe) |

## 函数说明
<span id="ByteRTCVideoProcessorDelegate-processvideoframe"></span>
### processVideoFrame:
```objectivec
- (ByteRTCVideoFrame* _Nullable)processVideoFrame:(ByteRTCVideoFrame* _Nonnull)srcFrame;
```
获取 RTC SDK 采集得到的视频帧，根据 [registerLocalVideoProcessor:withConfig:](macOS-api#ByteRTCVideo-registerlocalvideoprocessor-withconfig) 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| srcFrame | ByteRTCVideoFrame * | RTC SDK 采集得到的视频帧，参考: [ByteRTCVideoFrame](macOS-keytype#ByteRTCVideoFrame) |


**返回值**

经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参考: [ByteRTCVideoFrame](macOS-keytype#ByteRTCVideoFrame)


**注意**

如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。

<span id="ByteRTCMediaPlayerEventHandler"></span>
# ByteRTCMediaPlayerEventHandler
```objectivec
@protocol ByteRTCMediaPlayerEventHandler <NSObject>
```
[ByteRTCMediaPlayer](macOS-api#ByteRTCMediaPlayer) 对应的回调句柄。你必须调用 [setEventHandler:](macOS-api#ByteRTCMediaPlayer-seteventhandler) 完成设置后，才能收到对应回调。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onMediaPlayerStateChanged:state:error:](#ByteRTCMediaPlayerEventHandler-onmediaplayerstatechanged-state-error) |
| void | [onMediaPlayerPlayingProgress:progress:](#ByteRTCMediaPlayerEventHandler-onmediaplayerplayingprogress-progress) |

## 函数说明
<span id="ByteRTCMediaPlayerEventHandler-onmediaplayerstatechanged-state-error"></span>
### onMediaPlayerStateChanged:state:error:
```objectivec
-(void)onMediaPlayerStateChanged:(int)playerId state:(ByteRTCPlayerState)state error:(ByteRTCPlayerError)error;
```
播放状态改变时回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| playerId | int | [ByteRTCMediaPlayer](macOS-api#ByteRTCMediaPlayer) 的 ID。通过 [getMediaPlayer:](macOS-api#ByteRTCVideo-getmediaplayer) 设置。 |
| state | ByteRTCPlayerState | 混音状态。参考 [ByteRTCPlayerState](macOS-keytype#ByteRTCPlayerState)。 |
| error | ByteRTCPlayerError | 错误码。参考 [ByteRTCPlayerError](macOS-keytype#ByteRTCPlayerError)。 |


<span id="ByteRTCMediaPlayerEventHandler-onmediaplayerplayingprogress-progress"></span>
### onMediaPlayerPlayingProgress:progress:
```objectivec
-(void)onMediaPlayerPlayingProgress:(int)playerId progress:(int64_t)progress;
```
播放进度周期性回调。回调周期通过 [setProgressInterval:](macOS-api#ByteRTCMediaPlayer-setprogressinterval) 设置。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| playerId | int | [ByteRTCMediaPlayer](macOS-api#ByteRTCMediaPlayer) 的 ID。通过 [getMediaPlayer:](macOS-api#ByteRTCVideo-getmediaplayer) 设置。 |
| progress | int64_t | 进度。单位 ms。 |


<span id="ByteRTCVideoDelegate"></span>
# ByteRTCVideoDelegate
```objectivec
@protocol ByteRTCVideoDelegate <NSObject>
```
ByteRTCVideoDelegate 协议包含了 SDK 提供的回调方法，SDK 通过代理向应用程序上报一些运行时事件

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [rtcEngine:onWarning:](#ByteRTCVideoDelegate-rtcengine-onwarning) |
| void | [rtcEngine:onError:](#ByteRTCVideoDelegate-rtcengine-onerror) |
| void | [rtcEngine:onDeadLockError:](#ByteRTCVideoDelegate-rtcengine-ondeadlockerror) |
| void | [rtcEngine:onExtensionAccessError:msg:](#ByteRTCVideoDelegate-rtcengine-onextensionaccesserror-msg) |
| void | [rtcEngine:onCreateRoomStateChanged:errorCode:](#ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode) |
| void | [rtcEngine:onConnectionStateChanged:](#ByteRTCVideoDelegate-rtcengine-onconnectionstatechanged) |
| void | [rtcEngine:onNetworkTypeChanged:](#ByteRTCVideoDelegate-rtcengine-onnetworktypechanged) |
| void | [rtcEngine:onUserStartAudioCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid) |
| void | [rtcEngine:onUserStopAudioCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid) |
| void | [rtcEngine:onFirstRemoteAudioFrame:](#ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe) |
| void | [rtcEngine:onLocalAudioPropertiesReport:](#ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport) |
| void | [rtcEngine:onAudioPlaybackDeviceTestVolume:](#ByteRTCVideoDelegate-rtcengine-onaudioplaybackdevicetestvolume) |
| void | [rtcEngine:onAudioDeviceVolumeChanged:volume:muted:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicevolumechanged-volume-muted) |
| void | [rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:](#ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume) |
| void | [rtcEngine:onActiveSpeaker:uid:](#ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid) |
| void | [rtcEngine:onUserStartVideoCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid) |
| void | [rtcEngine:onUserStopVideoCapture:uid:](#ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid) |
| void | [rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstlocalvideoframecaptured-withframeinfo) |
| void | [rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframerendered-withframeinfo) |
| void | [rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo) |
| void | [rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo) |
| void | [rtcEngine:onLocalVideoSizeChanged:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onlocalvideosizechanged-withframeinfo) |
| void | [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) |
| void | [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) |
| void | [rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning) |
| void | [rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onvideodevicewarning-devicetype-devicewarning) |
| void | [rtcEngine:onAudioFrameSendStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onaudioframesendstatechanged-rtcuser-state) |
| void | [rtcEngine:onVideoFrameSendStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onvideoframesendstatechanged-rtcuser-state) |
| void | [rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onscreenvideoframesendstatechanged-rtcuser-state) |
| void | [rtcEngine:onAudioFramePlayStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onaudioframeplaystatechanged-rtcuser-state) |
| void | [rtcEngine:onVideoFramePlayStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onvideoframeplaystatechanged-rtcuser-state) |
| void | [rtcEngine:onScreenVideoFramePlayStateChanged:rtcUser:state:](#ByteRTCVideoDelegate-rtcengine-onscreenvideoframeplaystatechanged-rtcuser-state) |
| void | [rtcEngine:onFirstLocalAudioFrame:](#ByteRTCVideoDelegate-rtcengine-onfirstlocalaudioframe) |
| void | [rtcEngine:onSEIMessageReceived:andMessage:](#ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage) |
| void | [rtcEngine:onSEIStreamUpdate:eventType:](#ByteRTCVideoDelegate-rtcengine-onseistreamupdate-eventtype) |
| void | [rtcEngine:onStreamSyncInfoReceived:streamType:data:](#ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data) |
| void | [rtcEngine:onSysStats:](#ByteRTCVideoDelegate-rtcengine-onsysstats) |
| void | [rtcEngine:onLocalAudioStateChanged:error:](#ByteRTCVideoDelegate-rtcengine-onlocalaudiostatechanged-error) |
| void | [rtcEngine:onRemoteAudioStateChanged:state:reason:](#ByteRTCVideoDelegate-rtcengine-onremoteaudiostatechanged-state-reason) |
| void | [rtcEngine:onLocalVideoStateChanged:withStreamState:withStreamError:](#ByteRTCVideoDelegate-rtcengine-onlocalvideostatechanged-withstreamstate-withstreamerror) |
| void | [rtcEngine:onRemoteVideoStateChanged:withVideoState:withVideoStateReason:](#ByteRTCVideoDelegate-rtcengine-onremotevideostatechanged-withvideostate-withvideostatereason) |
| void | [rtcEngine:onLoginResult:errorCode:elapsed:](#ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed) |
| void | [rtcEngine:onLogout:](#ByteRTCVideoDelegate-rtcengine-onlogout) |
| void | [rtcEngine:onServerParamsSetResult:](#ByteRTCVideoDelegate-rtcengine-onserverparamssetresult) |
| void | [rtcEngine:onGetPeerOnlineStatus:status:](#ByteRTCVideoDelegate-rtcengine-ongetpeeronlinestatus-status) |
| void | [rtcEngine:onUserMessageReceivedOutsideRoom:message:](#ByteRTCVideoDelegate-rtcengine-onusermessagereceivedoutsideroom-message) |
| void | [rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:](#ByteRTCVideoDelegate-rtcengine-onuserbinarymessagereceivedoutsideroom-message) |
| void | [rtcEngine:onUserMessageSendResultOutsideRoom:error:](#ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error) |
| void | [rtcEngine:onServerMessageSendResult:error:message:](#ByteRTCVideoDelegate-rtcengine-onservermessagesendresult-error-message) |
| void | [rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:](#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionresult-quality-rtt-lostrate-bitrate-jitter) |
| void | [rtcEngine:onNetworkDetectionStopped:](#ByteRTCVideoDelegate-rtcengine-onnetworkdetectionstopped) |
| void | [rtcEngine:onAudioMixingPlayingProgress:progress:](#ByteRTCVideoDelegate-rtcengine-onaudiomixingplayingprogress-progress) |
| void | [rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:](#ByteRTCVideoDelegate-rtcengine-onperformancealarms-roomid-reason-sourcewanteddata) |
| void | [rtcEngine:onSimulcastSubscribeFallback:](#ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback) |
| void | [rtcEngine:onExternalScreenFrameUpdate:](#ByteRTCVideoDelegate-rtcengine-onexternalscreenframeupdate) |
| void | [rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:](#ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info) |
| void | [rtcEngine:onRecordingProgressUpdate:process:recording_info:](#ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info) |
| void | [rtcEngine:onAudioRecordingStateUpdate:error_code:](#ByteRTCVideoDelegate-rtcengine-onaudiorecordingstateupdate-error_code) |
| void | [rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:](#ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode) |
| void | [rtcEngine:onPlayPublicStreamResult:errorCode:](#ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode) |
| void | [rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage-andsourcetype) |
| void | [rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamdatamessagereceived-andmessage-andsourcetype) |
| void | [rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:](#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo) |
| void | [rtcEngine:onFirstPublicStreamAudioFrame:](#ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe) |
| void | [rtcEngine:onCloudProxyConnected:](#ByteRTCVideoDelegate-rtcengine-oncloudproxyconnected) |
| void | [rtcEngine:onEchoTestResult:](#ByteRTCVideoDelegate-rtcengine-onechotestresult) |
| void | [rtcEngineOnNetworkTimeSynchronized:](#ByteRTCVideoDelegate-rtcengineonnetworktimesynchronized) |
| void | [rtcEngine:onHardwareEchoDetectionResult:](#ByteRTCVideoDelegate-rtcengine-onhardwareechodetectionresult) |
| void | [rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:](#ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror) |
| void | [deprecated] [rtcEngine:onUserMuteAudio:uid:muteState:](#ByteRTCVideoDelegate-rtcengine-onusermuteaudio-uid-mutestate) |
| void | [deprecated] [rtcEngine:onUserMuteVideo:uid:withMuteState:](#ByteRTCVideoDelegate-rtcengine-onusermutevideo-uid-withmutestate) |
| void | [deprecated] [rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onmediadevicestatechanged-device_type-device_state-device_error) |
| void | [deprecated] [rtcEngine:onMediaDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onmediadevicewarning-devicetype-devicewarning) |
| void | [deprecated] [rtcEngine:log:](#ByteRTCVideoDelegate-rtcengine-log) |
| void | [deprecated] [rtcEngine:onAudioMixingStateChanged:state:error:](#ByteRTCVideoDelegate-rtcengine-onaudiomixingstatechanged-state-error) |
| void | [deprecated] [rtcEngine:onHttpProxyState:](#ByteRTCVideoDelegate-rtcengine-onhttpproxystate) |
| void | [deprecated] [rtcEngine:onHttpsProxyState:](#ByteRTCVideoDelegate-rtcengine-onhttpsproxystate) |
| void | [deprecated] [rtcEngine:onSocks5ProxyState:cmd:proxy_address:local_address:remote_address:](#ByteRTCVideoDelegate-rtcengine-onsocks5proxystate-cmd-proxy_address-local_address-remote_address) |

## 函数说明
<span id="ByteRTCVideoDelegate-rtcengine-onwarning"></span>
### rtcEngine:onWarning:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onWarning:(ByteRTCWarningCode)code;
```
发生警告回调。

SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象。 |
| code | ByteRTCWarningCode | 警告代码，参看 [ByteRTCWarningCode](macOS-errorcode#ByteRTCWarningCode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onerror"></span>
### rtcEngine:onError:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onError:(ByteRTCErrorCode)errorCode;
```
发生错误回调。

SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。

你可能需要干预.


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象。 |
| errorCode | ByteRTCErrorCode | 错误代码，参看 [ByteRTCErrorCode](macOS-errorcode#ByteRTCErrorCode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-ondeadlockerror"></span>
### rtcEngine:onDeadLockError:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onDeadLockError:(ByteRTCDeadLockMsg *_Nonnull)deadlockMsg;
```
内部线程发生 block 时触发，回调线程名和 block 次数


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| deadlockMsg | ByteRTCDeadLockMsg * | 错误消息 |


<span id="ByteRTCVideoDelegate-rtcengine-onextensionaccesserror-msg"></span>
### rtcEngine:onExtensionAccessError:msg:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onExtensionAccessError:(NSString * _Nonnull)extensionName msg:(NSString * _Nonnull)msg;
```
> Available since 3.52

当访问插件失败时，收到此回调。

RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| extensionName | NSString * | 插件名字 |
| msg | NSString * | 失败说明 |


<span id="ByteRTCVideoDelegate-rtcengine-oncreateroomstatechanged-errorcode"></span>
### rtcEngine:onCreateRoomStateChanged:errorCode:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onCreateRoomStateChanged:(NSString * _Nonnull)roomId errorCode:(NSInteger)errorCode;
```
创建房间失败回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| roomId | NSString * | 房间 ID。 |
| errorCode | NSInteger | 创建房间错误码，具体原因参看 [ByteRTCErrorCode](macOS-errorcode#ByteRTCErrorCode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onconnectionstatechanged"></span>
### rtcEngine:onConnectionStateChanged:
```objectivec
- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine onConnectionStateChanged:(ByteRTCConnectionState) state;
```
SDK 与信令服务器连接状态改变回调。连接状态改变时触发。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| state | ByteRTCConnectionState | 当前 SDK 与信令服务器的连接状态，详见 [ByteRTCConnectionState](macOS-keytype#ByteRTCConnectionState)。 |


**注意**

更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。

<span id="ByteRTCVideoDelegate-rtcengine-onnetworktypechanged"></span>
### rtcEngine:onNetworkTypeChanged:
```objectivec
- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkTypeChanged:(ByteRTCNetworkType) type;
```
SDK 当前网络连接类型改变回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| type | ByteRTCNetworkType | SDK 当前的网络连接类型，详见 [ByteRTCNetworkType](macOS-keytype#ByteRTCNetworkType) |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstartaudiocapture-uid"></span>
### rtcEngine:onUserStartAudioCapture:uid:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartAudioCapture:(NSString* _Nonnull)roomId
              uid:(NSString *_Nonnull)userId;
```
房间内的可见用户调用 [startAudioCapture](macOS-api#ByteRTCVideo-startaudiocapture) 开启音频采集时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例 |
| roomId | NSString * | 开启音频采集的用户所在的房间 ID |
| userId | NSString * | 开启音频采集的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstopaudiocapture-uid"></span>
### rtcEngine:onUserStopAudioCapture:uid:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopAudioCapture:(NSString* _Nonnull)roomId
              uid:(NSString *_Nonnull)userId;
```
房间内的可见用户调用 [stopAudioCapture](macOS-api#ByteRTCVideo-stopaudiocapture) 关闭音频采集时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例 |
| roomId | NSString * | 关闭音频采集的用户所在的房间 ID |
| userId | NSString * | 关闭音频采集的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstremoteaudioframe"></span>
### rtcEngine:onFirstRemoteAudioFrame:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;
```
当收到远端流的第一帧音频的时候上报该事件


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| key | ByteRTCRemoteStreamKey * | 远端流信息, 详见 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |


**注意**

用户刚收到房间内每一路音频流时，都会收到该回调。

<span id="ByteRTCVideoDelegate-rtcengine-onlocalaudiopropertiesreport"></span>
### rtcEngine:onLocalAudioPropertiesReport:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLocalAudioPropertiesReport:(NSArray<ByteRTCLocalAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos;
```
调用 [enableAudioPropertiesReport:](macOS-api#ByteRTCVideo-enableaudiopropertiesreport) 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。

本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| audioPropertiesInfos | NSArray<ByteRTCLocalAudioPropertiesInfo *\> * | 本地音频信息，详见 [ByteRTCLocalAudioPropertiesInfo](macOS-keytype#ByteRTCLocalAudioPropertiesInfo) 。 |


<span id="ByteRTCVideoDelegate-rtcengine-onaudioplaybackdevicetestvolume"></span>
### rtcEngine:onAudioPlaybackDeviceTestVolume:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioPlaybackDeviceTestVolume:(int)volume;
```
回调音频设备测试时的播放音量


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 参看 [ByteRTCVideo](macOS-api#ByteRTCVideo)。 |
| volume | int | 音频设备测试播放音量。取值范围：[0,255] |


**注意**

调用 [startAudioPlaybackDeviceTest:interval:](macOS-api#ByteRTCAudioDeviceManager-startaudioplaybackdevicetest-interval) 或 [startAudioDeviceRecordTest:](macOS-api#ByteRTCAudioDeviceManager-startaudiodevicerecordtest)，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。

<span id="ByteRTCVideoDelegate-rtcengine-onaudiodevicevolumechanged-volume-muted"></span>
### rtcEngine:onAudioDeviceVolumeChanged:volume:muted:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceVolumeChanged:(ByteRTCAudioDeviceType)deviceType volume:(int)volume muted:(bool)muted;
```
音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 参看 [ByteRTCVideo](macOS-api#ByteRTCVideo) |
| deviceType | ByteRTCAudioDeviceType | 设备类型，包括麦克风和扬声器，参阅 [ByteRTCAudioDeviceType](macOS-keytype#ByteRTCAudioDeviceType)。 |
| volume | int | 音量值，[0, 255]。当 volume 变为 0 时，muted 会转为 True。 |
| muted | bool | 是否禁音状态。扬声器被设置为禁音时，muted 为 True，但 volume 保持不变。 |


<span id="ByteRTCVideoDelegate-rtcengine-onremoteaudiopropertiesreport-totalremotevolume"></span>
### rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos totalRemoteVolume:(NSInteger)totalRemoteVolume;
```
远端用户进房后，本地调用 [enableAudioPropertiesReport:](macOS-api#ByteRTCVideo-enableaudiopropertiesreport) ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的瞬时音频信息。

远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| audioPropertiesInfos | NSArray<ByteRTCRemoteAudioPropertiesInfo *\> * | 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 [ByteRTCRemoteAudioPropertiesInfo](macOS-keytype#ByteRTCRemoteAudioPropertiesInfo)。 |
| totalRemoteVolume | NSInteger | 订阅的所有远端流混音后的总音量，范围是 [0,255]。<br><ul><li>[0,25] 接近无声；</li><li>[25,75] 为低音量；</li><li>[76,204] 为中音量；</li><li>[205,255] 为高音量。</li></ul> |


<span id="ByteRTCVideoDelegate-rtcengine-onactivespeaker-uid"></span>
### rtcEngine:onActiveSpeaker:uid:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onActiveSpeaker:(NSString * _Nonnull)roomId uid:(NSString *_Nonnull)uid;
```
调用 [enableAudioPropertiesReport:](macOS-api#ByteRTCVideo-enableaudiopropertiesreport) 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| roomId | NSString * | 房间 ID |
| uid | NSString * | 最活跃用户（ActiveSpeaker）的用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstartvideocapture-uid"></span>
### rtcEngine:onUserStartVideoCapture:uid:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartVideoCapture:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid;
```
房间内的可见用户调用 [startVideoCapture](macOS-api#ByteRTCVideo-startvideocapture) 开启内部视频采集时，房间中其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例 |
| roomId | NSString * | 开启视频采集的用户所在的房间 ID |
| uid | NSString * | 调用 [startVideoCapture](macOS-api#ByteRTCVideo-startvideocapture) 接口的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onuserstopvideocapture-uid"></span>
### rtcEngine:onUserStopVideoCapture:uid:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopVideoCapture:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid;
```
房间内的可见用户调用 [stopVideoCapture](macOS-api#ByteRTCVideo-stopvideocapture) 关闭内部视频采集时，房间内其他用户会收到此回调。

若发布视频数据前未开启采集，房间内所有可见用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例 |
| roomId | NSString * | 关闭视频采集的用户所在的房间 ID |
| uid | NSString * | 关闭视频采集的远端用户 ID |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstlocalvideoframecaptured-withframeinfo"></span>
### rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onFirstLocalVideoFrameCaptured:withFrameInfo:));
```
第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| streamIndex | ByteRTCStreamIndex | 流属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |
| frameInfo | ByteRTCVideoFrameInfo * | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype#ByteRTCVideoFrameInfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframerendered-withframeinfo"></span>
### rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onFirstRemoteVideoFrameRendered:withFrameInfo:));
```
SDK 内部渲染成功远端视频流首帧后，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| streamKey | ByteRTCRemoteStreamKey * | 远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |
| frameInfo | ByteRTCVideoFrameInfo * | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype#ByteRTCVideoFrameInfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstremotevideoframedecoded-withframeinfo"></span>
### rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteVideoFrameDecoded:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onFirstRemoteVideoFrameDecoded:withFrameInfo:));
```
SDK 接收并解码远端视频流首帧后，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| streamKey | ByteRTCRemoteStreamKey * | 远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |
| frameInfo | ByteRTCVideoFrameInfo * | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype#ByteRTCVideoFrameInfo) |


**注意**

- 对于主流，进入房间后，仅在发布端第一次发布的时候，订阅端会收到该回调，此后不受重新发布的影响，只要不重新加入房间，就不会再收到该回调。
- 对于屏幕流，用户每次重新发布屏幕视频流在订阅端都会重新触发一次该回调。

<span id="ByteRTCVideoDelegate-rtcengine-onremotevideosizechanged-withframeinfo"></span>
### rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onRemoteVideoSizeChanged:withFrameInfo:));
```
远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| streamKey | ByteRTCRemoteStreamKey * | 流属性，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |
| frameInfo | ByteRTCVideoFrameInfo * | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype#ByteRTCVideoFrameInfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalvideosizechanged-withframeinfo"></span>
### rtcEngine:onLocalVideoSizeChanged:withFrameInfo:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onLocalVideoSizeChanged:withFrameInfo:));
```
本地视频大小或旋转信息发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| streamIndex | ByteRTCStreamIndex | 流属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |
| frameInfo | ByteRTCVideoFrameInfo * | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype#ByteRTCVideoFrameInfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error"></span>
### rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceStateChanged:(NSString*_Nonnull)deviceID
      device_type:(ByteRTCAudioDeviceType)deviceType
     device_state:(ByteRTCMediaDeviceState)deviceState
     device_error:(ByteRTCMediaDeviceError)deviceError;
```
音频设备状态回调。提示音频采集、音频播放等设备的状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例 |
| deviceID | NSString * | 设备 ID |
| deviceType | ByteRTCAudioDeviceType | 设备类型，参看 [ByteRTCAudioDeviceType](macOS-keytype#ByteRTCAudioDeviceType)。 |
| deviceState | ByteRTCMediaDeviceState | 设备状态，参看 [ByteRTCMediaDeviceState](macOS-keytype#ByteRTCMediaDeviceState)。 |
| deviceError | ByteRTCMediaDeviceError | 设备错误类型，参看 [ByteRTCMediaDeviceError](macOS-keytype#ByteRTCMediaDeviceError)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error"></span>
### rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceStateChanged:(NSString*_Nonnull)deviceID
      device_type:(ByteRTCVideoDeviceType)deviceType
     device_state:(ByteRTCMediaDeviceState)deviceState
     device_error:(ByteRTCMediaDeviceError)deviceError;
```
视频设备状态发生改变回调。当设备的视频状态发生改变时，SDK 会触发该回调，提示摄像头视频采集、屏幕视频采集等设备的状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 参看 [ByteRTCVideo](macOS-api#ByteRTCVideo)。 |
| deviceID | NSString * | 设备 ID |
| deviceType | ByteRTCVideoDeviceType | 设备类型，参看 [ByteRTCVideoDeviceType](macOS-keytype#ByteRTCVideoDeviceType)。 |
| deviceState | ByteRTCMediaDeviceState | 设备状态，参看 [ByteRTCMediaDeviceState](macOS-keytype#ByteRTCMediaDeviceState)。 |
| deviceError | ByteRTCMediaDeviceError | 设备错误类型，参看 [ByteRTCMediaDeviceError](macOS-keytype#ByteRTCMediaDeviceError)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning"></span>
### rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceWarning:(NSString*_Nonnull)deviceId
       deviceType:(ByteRTCAudioDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;
```
音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| deviceId | NSString * | 设备 ID |
| deviceType | ByteRTCAudioDeviceType | 参看 [ByteRTCAudioDeviceType](macOS-keytype#ByteRTCAudioDeviceType) |
| deviceWarning | ByteRTCMediaDeviceWarning | 参看 [ByteRTCMediaDeviceWarning](macOS-keytype#ByteRTCMediaDeviceWarning) |


<span id="ByteRTCVideoDelegate-rtcengine-onvideodevicewarning-devicetype-devicewarning"></span>
### rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceWarning:(NSString*_Nonnull)deviceId
       deviceType:(ByteRTCVideoDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;
```
视频设备警告回调。视频设备包括视频采集设备。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| deviceId | NSString * | 设备 ID |
| deviceType | ByteRTCVideoDeviceType | 参看 [ByteRTCVideoDeviceType](macOS-keytype#ByteRTCVideoDeviceType) |
| deviceWarning | ByteRTCMediaDeviceWarning | 参看 [ByteRTCMediaDeviceWarning](macOS-keytype#ByteRTCMediaDeviceWarning) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudioframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onAudioFrameSendStateChanged:rtcUser:state:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFrameSendStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
本地音频首帧发送状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| roomId | NSString * | 音频流发布用户所在的房间 ID |
| user | ByteRTCUser * | 本地用户信息，详见 [ByteRTCUser](macOS-keytype#ByteRTCUser) |
| state | ByteRTCFirstFrameSendState | 首帧发送状态，详见 [ByteRTCFirstFrameSendState](macOS-keytype#ByteRTCFirstFrameSendState) |


<span id="ByteRTCVideoDelegate-rtcengine-onvideoframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onVideoFrameSendStateChanged:rtcUser:state:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFrameSendStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
本地视频首帧发送状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| roomId | NSString * | 视频流发布用户所在的房间 ID |
| user | ByteRTCUser * | 本地用户信息，详见 [ByteRTCUser](macOS-keytype#ByteRTCUser) |
| state | ByteRTCFirstFrameSendState | 首帧发送状态，详见 [ByteRTCFirstFrameSendState](macOS-keytype#ByteRTCFirstFrameSendState) |


<span id="ByteRTCVideoDelegate-rtcengine-onscreenvideoframesendstatechanged-rtcuser-state"></span>
### rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFrameSendStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
```
屏幕共享流的视频首帧发送状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象。 |
| roomId | NSString * | 屏幕流发布用户所在的房间 ID |
| user | ByteRTCUser * | 本地用户信息，参看 [ByteRTCUser](macOS-keytype#ByteRTCUser) |
| state | ByteRTCFirstFrameSendState | 首帧发送状态，参看 [ByteRTCFirstFrameSendState](macOS-keytype#ByteRTCFirstFrameSendState) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudioframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onAudioFramePlayStateChanged:rtcUser:state:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFramePlayStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
音频首帧播放状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象。 |
| roomId | NSString * | 音频流发布用户所在的房间 ID |
| user | ByteRTCUser * | 音频流来源的用户信息，参看 [ByteRTCUser](macOS-keytype#ByteRTCUser) |
| state | ByteRTCFirstFramePlayState | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](macOS-keytype#ByteRTCFirstFramePlayState) |


<span id="ByteRTCVideoDelegate-rtcengine-onvideoframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onVideoFramePlayStateChanged:rtcUser:state:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFramePlayStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
视频首帧播放状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象。 |
| roomId | NSString * | 视频流发布用户所在的房间 ID |
| user | ByteRTCUser * | 视频流来源的用户信息，参看 [ByteRTCUser](macOS-keytype#ByteRTCUser) |
| state | ByteRTCFirstFramePlayState | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](macOS-keytype#ByteRTCFirstFramePlayState) |


<span id="ByteRTCVideoDelegate-rtcengine-onscreenvideoframeplaystatechanged-rtcuser-state"></span>
### rtcEngine:onScreenVideoFramePlayStateChanged:rtcUser:state:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
```
屏幕共享流视频首帧播放状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象。 |
| roomId | NSString * | 屏幕流发布用户所在的房间 ID |
| user | ByteRTCUser * | 屏幕共享流来源的用户信息，参看 [ByteRTCUser](macOS-keytype#ByteRTCUser) |
| state | ByteRTCFirstFramePlayState | 首帧播放状态，参看 [ByteRTCFirstFramePlayState](macOS-keytype#ByteRTCFirstFramePlayState) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstlocalaudioframe"></span>
### rtcEngine:onFirstLocalAudioFrame:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;
```
发布音频流时，采集到第一帧音频帧，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| streamIndex | ByteRTCStreamIndex | 音频流属性, 详见 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |


**注意**

如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onseimessagereceived-andmessage"></span>
### rtcEngine:onSEIMessageReceived:andMessage:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIMessageReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey andMessage:(NSData* _Nonnull)message;
```
收到通过调用 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](macOS-api#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 发送带有 SEI 消息的视频帧时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 当前 ByteRTCVideo 实例。 |
| remoteStreamKey | ByteRTCRemoteStreamKey * | 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |
| message | NSData * | 收到的 SEI 消息内容 |


<span id="ByteRTCVideoDelegate-rtcengine-onseistreamupdate-eventtype"></span>
### rtcEngine:onSEIStreamUpdate:eventType:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIStreamUpdate:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey eventType:(ByteRTCSEIStreamEventType)eventType;
```
黑帧视频流发布状态回调。

在语音通话场景下，本地用户调用 [sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:](macOS-api#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount-andcountperframe) 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。

你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 当前 ByteRTCVideo 实例。 |
| remoteStreamKey | ByteRTCRemoteStreamKey * | 远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey)。 |
| eventType | ByteRTCSEIStreamEventType | 黑帧视频流状态，参看 [ByteRTCSEIStreamEventType](macOS-keytype#ByteRTCSEIStreamEventType) |


<span id="ByteRTCVideoDelegate-rtcengine-onstreamsyncinforeceived-streamtype-data"></span>
### rtcEngine:onStreamSyncInfoReceived:streamType:data:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onStreamSyncInfoReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey streamType:(ByteRTCSyncInfoStreamType)streamType data:(NSData* _Nonnull)data;
```
音频流同步信息回调。可以通过此回调，在远端用户调用 [sendStreamSyncInfo:config:](macOS-api#ByteRTCVideo-sendstreamsyncinfo-config) 发送音频流同步消息后，收到远端发送的音频流同步信息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 当前 ByteRTCVideo 实例。 |
| remoteStreamKey | ByteRTCRemoteStreamKey * | 远端流信息，详见 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) 。 |
| streamType | ByteRTCSyncInfoStreamType | 媒体流类型，详见 [ByteRTCSyncInfoStreamType](macOS-keytype#ByteRTCSyncInfoStreamType)。 |
| data | NSData * | 消息内容。 |


<span id="ByteRTCVideoDelegate-rtcengine-onsysstats"></span>
### rtcEngine:onSysStats:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSysStats:(const ByteRTCSysStats * _Nonnull)stats NS_SWIFT_NAME(rtcEngine(_:onSysStats:));
```
报告当前设备 cpu 与 memory 使用率，每 2s 触发一次。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| stats | const ByteRTCSysStats * | cpu 和 memory 使用率信息，详见 [ByteRTCSysStats](macOS-keytype#ByteRTCSysStats) 数据类型 |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalaudiostatechanged-error"></span>
### rtcEngine:onLocalAudioStateChanged:error:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
            error:(ByteRTCLocalAudioStreamError)error;
```
本地音频流的状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| state | ByteRTCLocalAudioStreamState | 本地音频设备的当前状态，详见 [ByteRTCLocalAudioStreamState](macOS-keytype#ByteRTCLocalAudioStreamState) |
| error | ByteRTCLocalAudioStreamError | 本地音频流状态改变时的错误码，详见 [ByteRTCLocalAudioStreamError](macOS-keytype#ByteRTCLocalAudioStreamError) |


<span id="ByteRTCVideoDelegate-rtcengine-onremoteaudiostatechanged-state-reason"></span>
### rtcEngine:onRemoteAudioStateChanged:state:reason:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key
            state:(ByteRTCRemoteAudioState)state
           reason:(ByteRTCRemoteAudioStateChangeReason)reason;
```
订阅的远端音频流状态发生改变时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| key | ByteRTCRemoteStreamKey * | 远端流信息, 详见 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |
| state | ByteRTCRemoteAudioState | 远端音频流的当前状态，详见 [ByteRTCRemoteAudioState](macOS-keytype#ByteRTCRemoteAudioState) |
| reason | ByteRTCRemoteAudioStateChangeReason | 远端音频流状态改变的原因，详见 [ByteRTCRemoteAudioStateChangeReason](macOS-keytype#ByteRTCRemoteAudioStateChangeReason) |


<span id="ByteRTCVideoDelegate-rtcengine-onlocalvideostatechanged-withstreamstate-withstreamerror"></span>
### rtcEngine:onLocalVideoStateChanged:withStreamState:withStreamError:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex
  withStreamState:(ByteRTCLocalVideoStreamState)state
  withStreamError:(ByteRTCLocalVideoStreamError)error NS_SWIFT_NAME(rtcEngine(_:onLocalVideoStateChanged:withStreamState:withStreamError:));
```
本地视频流的状态发生改变时，收到该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| streamIndex | ByteRTCStreamIndex | 流属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |
| state | ByteRTCLocalVideoStreamState | 本地视频流的当前状态，参看 [ByteRTCLocalVideoStreamState](macOS-keytype#ByteRTCLocalVideoStreamState) |
| error | ByteRTCLocalVideoStreamError | 本地视频状态改变时的错误码，参看 [ByteRTCLocalVideoStreamError](macOS-keytype#ByteRTCLocalVideoStreamError) |


<span id="ByteRTCVideoDelegate-rtcengine-onremotevideostatechanged-withvideostate-withvideostatereason"></span>
### rtcEngine:onRemoteVideoStateChanged:withVideoState:withVideoStateReason:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoStateChanged:(ByteRTCRemoteStreamKey*_Nonnull)streamKey
   withVideoState:(ByteRTCRemoteVideoState)state
withVideoStateReason:(ByteRTCRemoteVideoStateChangeReason)reason NS_SWIFT_NAME(rtcEngine(_:onRemoteVideoStateChanged:withVideoState:withVideoStateReason:));
```
远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| streamKey | ByteRTCRemoteStreamKey * | 远端视频流信息，房间、用户 ID、流属性等，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |
| state | ByteRTCRemoteVideoState | 远端视频流的当前状态，参看 [ByteRTCRemoteVideoState](macOS-keytype#ByteRTCRemoteVideoState) |
| reason | ByteRTCRemoteVideoStateChangeReason | 远端视频流状态改变的原因，参看 [ByteRTCRemoteVideoStateChangeReason](macOS-keytype#ByteRTCRemoteVideoStateChangeReason) |


**注意**

本回调仅适用于主流，不适用于屏幕流。

<span id="ByteRTCVideoDelegate-rtcengine-onloginresult-errorcode-elapsed"></span>
### rtcEngine:onLoginResult:errorCode:elapsed:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
```
登录结果回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| uid | NSString * | <br>登录用户 ID |
| errorCode | ByteRTCLoginErrorCode | <br>登录结果<br>详见 [ByteRTCLoginErrorCode](macOS-errorcode#ByteRTCLoginErrorCode)。 |
| elapsed | NSInteger | <br>从调用 [login:uid:](macOS-api#ByteRTCVideo-login-uid) 接口开始到返回结果所用时长。<br>单位为 ms。 |


**注意**

调用 [login:uid:](macOS-api#ByteRTCVideo-login-uid) 后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onlogout"></span>
### rtcEngine:onLogout:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLogout:(ByteRTCLogoutReason)reason;
```
登出结果回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| reason | ByteRTCLogoutReason | 用户登出的原因，参看 [ByteRTCLogoutReason](macOS-keytype#ByteRTCLogoutReason) |


**注意**

在以下两种情况下会收到此回调：调用 [logout](macOS-api#ByteRTCVideo-logout) 接口主动退出；或其他用户以相同 UserId 进行 `login` 导致本地用户被动登出。

<span id="ByteRTCVideoDelegate-rtcengine-onserverparamssetresult"></span>
### rtcEngine:onServerParamsSetResult:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
```
设置应用服务器参数的返回结果


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| errorCode | NSInteger | <br>设置结果<br><ul><li>返回 200，设置成功</li><li>返回其他，设置失败，详见 [ByteRTCUserMessageSendResult](macOS-errorcode#ByteRTCUserMessageSendResult) </li></ul> |


**注意**

调用 [setServerParams:url:](macOS-api#ByteRTCVideo-setserverparams-url) 后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-ongetpeeronlinestatus-status"></span>
### rtcEngine:onGetPeerOnlineStatus:status:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId status:(ByteRTCUserOnlineStatus)status;
```
查询对端或本端用户登录状态的返回结果


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| peerUserId | NSString * | <br>需要查询的用户 ID |
| status | ByteRTCUserOnlineStatus | <br>查询的用户登录状态<br>详见 [ByteRTCUserOnlineStatus](macOS-keytype#ByteRTCUserOnlineStatus). |


**注意**

必须先调用 [getPeerOnlineStatus:](macOS-api#ByteRTCVideo-getpeeronlinestatus)，才能收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onusermessagereceivedoutsideroom-message"></span>
### rtcEngine:onUserMessageReceivedOutsideRoom:message:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;
```
收到房间外用户调用 [sendUserMessageOutsideRoom:message:config:](macOS-api#ByteRTCVideo-sendusermessageoutsideroom-message-config) 发来的文本消息时，会收到此回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| uid | NSString * | <br>消息发送者 ID |
| message | NSString * | <br>收到的文本消息内容 |


<span id="ByteRTCVideoDelegate-rtcengine-onuserbinarymessagereceivedoutsideroom-message"></span>
### rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserBinaryMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;
```
收到房间外用户调用 [sendUserBinaryMessageOutsideRoom:message:config:](macOS-api#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) 发来的二进制消息时，会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| uid | NSString * | <br>消息发送者 ID |
| message | NSData * | <br>收到的二进制消息内容 |


<span id="ByteRTCVideoDelegate-rtcengine-onusermessagesendresultoutsideroom-error"></span>
### rtcEngine:onUserMessageSendResultOutsideRoom:error:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageSendResultOutsideRoom:(NSInteger)msgid error:(ByteRTCUserMessageSendResult)error;
```
给房间外指定的用户发送消息的回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| msgid | NSInteger | <br>本条消息的 ID<br>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | ByteRTCUserMessageSendResult | <br>消息发送结果<br>详见 [ByteRTCUserMessageSendResult](macOS-errorcode#ByteRTCUserMessageSendResult)。 |


**注意**

当调用 [sendUserMessageOutsideRoom:message:config:](macOS-api#ByteRTCVideo-sendusermessageoutsideroom-message-config) 或 [sendUserBinaryMessageOutsideRoom:message:config:](macOS-api#ByteRTCVideo-senduserbinarymessageoutsideroom-message-config) 发送消息后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onservermessagesendresult-error-message"></span>
### rtcEngine:onServerMessageSendResult:error:message:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error message:(NSData * _Nonnull)message;
```
给应用服务器发送消息的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象。 |
| msgid | int64_t | 本条消息的 ID。<br>所有的 P2P 和 P2Server 消息共用一个 ID 序列。 |
| error | ByteRTCUserMessageSendResult | 消息发送结果。详见 [ByteRTCUserMessageSendResult](macOS-errorcode#ByteRTCUserMessageSendResult)。 |
| message | NSData * | 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。 |


**注意**

本回调为异步回调。当调用 [sendServerMessage:](macOS-api#ByteRTCVideo-sendservermessage) 或 [sendServerBinaryMessage:](macOS-api#ByteRTCVideo-sendserverbinarymessage) 接口发送消息后，会收到此回调。

<span id="ByteRTCVideoDelegate-rtcengine-onnetworkdetectionresult-quality-rtt-lostrate-bitrate-jitter"></span>
### rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionResult:(ByteRTCNetworkDetectionLinkType)type quality:(ByteRTCNetworkQuality)quality rtt:(int)rtt lostRate:(double)lostRate bitrate:(int)bitrate jitter:(int)jitter;
```
通话前网络探测结果的回调。

成功调用 [startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:](macOS-api#ByteRTCVideo-startnetworkdetection-uplinkbandwidth-downlink-downlinkbandwidth) 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| type | ByteRTCNetworkDetectionLinkType | 探测网络类型为上行/下行 |
| quality | ByteRTCNetworkQuality | 探测网络的质量，参看 [ByteRTCNetworkQuality](macOS-keytype#ByteRTCNetworkQuality)。 |
| rtt | int | 探测网络的 RTT，单位：ms |
| lostRate | double | 探测网络的丢包率 |
| bitrate | int | 探测网络的带宽，单位：kbps |
| jitter | int | 探测网络的抖动,单位：ms |


<span id="ByteRTCVideoDelegate-rtcengine-onnetworkdetectionstopped"></span>
### rtcEngine:onNetworkDetectionStopped:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionStopped:(ByteRTCNetworkDetectionStopReason)errorCode;
```
通话前网络探测结束

以下情况将停止探测并收到一次本回调：

1. 当调用 [stopNetworkDetection](macOS-api#ByteRTCVideo-stopnetworkdetection) 接口停止探测后，会收到一次该回调；

2. 当收到远端/本端音频首帧后，停止探测；

3. 当探测超过 3 分钟后，停止探测；

4. 当探测链路断开一定时间之后，停止探测。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| errorCode | ByteRTCNetworkDetectionStopReason | <br>停止探测的原因类型,参考 [ByteRTCNetworkDetectionStopReason](macOS-keytype#ByteRTCNetworkDetectionStopReason) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiomixingplayingprogress-progress"></span>
### rtcEngine:onAudioMixingPlayingProgress:progress:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioMixingPlayingProgress:(NSInteger)mixId progress:(int64_t) progress;
```
混音音频文件播放进度回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 当前 RTC SDK 对象 |
| mixId | NSInteger | 混音 ID |
| progress | int64_t | 当前混音音频文件播放进度，单位毫秒 |


**注意**

调用 [setAudioMixingProgressInterval:interval:](macOS-api#ByteRTCAudioMixingManager-setaudiomixingprogressinterval-interval) 将时间间隔设为大于 0 的值后，或调用 [startAudioMixing:filePath:config:](macOS-api#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 将 [ByteRTCAudioMixingConfig](macOS-keytype#ByteRTCAudioMixingConfig) 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。

<span id="ByteRTCVideoDelegate-rtcengine-onperformancealarms-roomid-reason-sourcewanteddata"></span>
### rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPerformanceAlarms:(ByteRTCPerformanceAlarmMode)mode
           roomId:(NSString *_Nonnull)roomId
           reason:(ByteRTCPerformanceAlarmReason)reason
 sourceWantedData:(ByteRTCSourceWantedData *_Nonnull)data;
```
本地未通过 [setPublishFallbackOption:](macOS-api#ByteRTCVideo-setpublishfallbackoption) 开启发布性能回退，检测到设备性能不足时，收到此回调。

本地通过 [setPublishFallbackOption:](macOS-api#ByteRTCVideo-setpublishfallbackoption) 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| mode | ByteRTCPerformanceAlarmMode | 指示本地是否开启发布回退功能。参看 [ByteRTCPerformanceAlarmMode](macOS-keytype#ByteRTCPerformanceAlarmMode)<br><ul><li>当发布端未开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeNormal。</li><li>当发布端开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeSimulcast。</li></ul> |
| roomId | NSString * | <ul><li>未开启发布性能回退时，roomId 为空</li><li>开启发布性能回退时，roomId 是告警影响的房间 ID。</li></ul> |
| reason | ByteRTCPerformanceAlarmReason | 告警原因，参看 [ByteRTCPerformanceAlarmReason](macOS-keytype#ByteRTCPerformanceAlarmReason) |
| data | ByteRTCSourceWantedData * | 性能回退相关数据，详见 [ByteRTCSourceWantedData](macOS-keytype#ByteRTCSourceWantedData)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onsimulcastsubscribefallback"></span>
### rtcEngine:onSimulcastSubscribeFallback:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onSimulcastSubscribeFallback:(ByteRTCRemoteStreamSwitchEvent *_Nonnull)event;
```
音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 当前 ByteRTCVideo 实例 |
| event | ByteRTCRemoteStreamSwitchEvent * | 流切换信息。详见 [ByteRTCRemoteStreamSwitchEvent](macOS-keytype#ByteRTCRemoteStreamSwitchEvent)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onexternalscreenframeupdate"></span>
### rtcEngine:onExternalScreenFrameUpdate:
```objectivec
- (void)rtcEngine: (ByteRTCVideo* _Nonnull)engine onExternalScreenFrameUpdate: (ByteRTCFrameUpdateInfo* _Nullable)frameUpdateInfo;
#endif
```
外部采集时，调用 [setOriginalScreenVideoInfo:withOriginalCaptureHeight:](macOS-api#ByteRTCVideo-setoriginalscreenvideoinfo-withoriginalcaptureheight) 设置屏幕或窗口大小改变前的分辨率后，若屏幕采集模式为智能模式，你将收到此回调，根据 RTC 智能决策合适的帧率和分辨率积（宽*高）重新采集。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 参看 [ByteRTCVideo](macOS-api#ByteRTCVideo) |
| frameUpdateInfo | ByteRTCFrameUpdateInfo *_Nullable | RTC 智能决策后合适的帧率和分辨率积（宽*高）。参看 [ByteRTCFrameUpdateInfo](macOS-keytype#ByteRTCFrameUpdateInfo)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onrecordingstateupdate-state-error_code-recording_info"></span>
### rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:
```objectivec
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine onRecordingStateUpdate:(ByteRTCStreamIndex)type
            state:(ByteRTCRecordingState)state
       error_code:(ByteRTCRecordingErrorCode)errorCode
   recording_info:(ByteRTCRecordingInfo* _Nonnull)recordingInfo;
```
获取本地录制状态回调。

该回调由 [startFileRecording:withRecordingConfig:type:](macOS-api#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 或 [stopFileRecording:](macOS-api#ByteRTCVideo-stopfilerecording) 触发。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| type | ByteRTCStreamIndex | 录制流的流属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |
| state | ByteRTCRecordingState | 录制状态，参看 [ByteRTCRecordingState](macOS-keytype#ByteRTCRecordingState) |
| errorCode | ByteRTCRecordingErrorCode | 录制错误码，参看 [ByteRTCRecordingErrorCode](macOS-keytype#ByteRTCRecordingErrorCode) |
| recordingInfo | ByteRTCRecordingInfo * | 录制文件的详细信息，参看 [ByteRTCRecordingInfo](macOS-keytype#ByteRTCRecordingInfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onrecordingprogressupdate-process-recording_info"></span>
### rtcEngine:onRecordingProgressUpdate:process:recording_info:
```objectivec
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine onRecordingProgressUpdate:(ByteRTCStreamIndex)type
          process:(ByteRTCRecordingProgress* _Nonnull)process
   recording_info:(ByteRTCRecordingInfo* _Nonnull)recordingInfo;
```
本地录制进度回调。

该回调由 [startFileRecording:withRecordingConfig:type:](macOS-api#ByteRTCVideo-startfilerecording-withrecordingconfig-type) 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| type | ByteRTCStreamIndex | 录制流的流属性，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |
| process | ByteRTCRecordingProgress * | 录制进度，参看 [ByteRTCRecordingProgress](macOS-keytype#ByteRTCRecordingProgress) |
| recordingInfo | ByteRTCRecordingInfo * | 录制文件的详细信息，参看 [ByteRTCRecordingInfo](macOS-keytype#ByteRTCRecordingInfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiorecordingstateupdate-error_code"></span>
### rtcEngine:onAudioRecordingStateUpdate:error_code:
```objectivec
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
onAudioRecordingStateUpdate:(ByteRTCAudioRecordingState)state
                 error_code:(ByteRTCAudioRecordingErrorCode)errorCode;
```
调用 [startAudioRecording:](macOS-api#ByteRTCVideo-startaudiorecording) 或者 [stopAudioRecording](macOS-api#ByteRTCVideo-stopaudiorecording) 改变音频文件录制状态时，收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| state | ByteRTCAudioRecordingState | 录制状态，参看 [ByteRTCAudioRecordingState](macOS-keytype#ByteRTCAudioRecordingState) |
| errorCode | ByteRTCAudioRecordingErrorCode | 录制错误码，参看 [ByteRTCAudioRecordingErrorCode](macOS-errorcode#ByteRTCAudioRecordingErrorCode) |


<span id="ByteRTCVideoDelegate-rtcengine-onpushpublicstreamresult-publicstreamid-errorcode"></span>
### rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPushPublicStreamResult:(NSString *_Nonnull)roomId
   publicStreamId:(NSString *_Nonnull)streamId
        errorCode:(ByteRTCPublicStreamErrorCode)errorCode;
```
公共流发布结果回调。

调用 [startPushPublicStream:withLayout:](macOS-api#ByteRTCVideo-startpushpublicstream-withlayout)

接口或直接在服务端启动推公共流功能后，你会通过此回调收到启动结果和推流过程中的错误。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | engine 实例 |
| roomId | NSString * | 发布公共流的房间 ID |
| streamId | NSString * | 公共流 ID。 |
| errorCode | ByteRTCPublicStreamErrorCode | 公共流发布结果状态码。 详见 [ByteRTCPublicStreamErrorCode](macOS-errorcode#ByteRTCPublicStreamErrorCode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onplaypublicstreamresult-errorcode"></span>
### rtcEngine:onPlayPublicStreamResult:errorCode:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPlayPublicStreamResult:(NSString *_Nonnull)publicStreamId
        errorCode:(ByteRTCPublicStreamErrorCode)errorCode;
```
订阅公共流的结果回调

调用 [startPlayPublicStream:](macOS-api#ByteRTCVideo-startplaypublicstream) 接口拉公共流后，你会通过此回调收到启动结果和拉流过程中的错误。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | engine 实例 |
| publicStreamId | NSString * | 公共流 ID。 |
| errorCode | ByteRTCPublicStreamErrorCode | 公共流订阅结果状态码。 详见 [ByteRTCPublicStreamErrorCode](macOS-errorcode#ByteRTCPublicStreamErrorCode)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage-andsourcetype"></span>
### rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamSEIMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message andSourceType:(ByteRTCDataMessageSourceType)sourceType;
```
回调公共流中包含的 SEI 信息。

调用 [startPlayPublicStream:](macOS-api#ByteRTCVideo-startplaypublicstream) 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例。 |
| publicStreamId | NSString * | 公共流 ID。 |
| message | NSData * | 收到的 SEI 消息内容。<br>本回调可以获取通过调用客户端 `sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:` 插入的 SEI 信息。<br>当公共流中的多路视频流均包含有 SEI 信息：SEI 不互相冲突时，将通过多次回调分别发送；SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。 |
| sourceType | ByteRTCDataMessageSourceType | SEI 消息类型，自 3.52.1 版本后固定为 `0`，自定义消息。参看 [ByteRTCDataMessageSourceType](macOS-keytype#ByteRTCDataMessageSourceType)。 |


**注意**

通过 Open API 插入的自定义信息，应通过回调 [rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamdatamessagereceived-andmessage-andsourcetype) 获取。

<span id="ByteRTCVideoDelegate-rtcengine-onpublicstreamdatamessagereceived-andmessage-andsourcetype"></span>
### rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamDataMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message andSourceType:(ByteRTCDataMessageSourceType)sourceType;
```
> Available since 3.52

回调公共流中包含的数据信息。

通过 [startPlayPublicStream:](macOS-api#ByteRTCVideo-startplaypublicstream) 开始播放公共流后，可以通过本回调获取公共流中的数据消息，包括调用 Open API 发送的 SEI 消息和音量回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例。 |
| publicStreamId | NSString * | 公共流 ID |
| message | NSData * | 收到的数据消息内容，如下：<br><ul><li>调用公共流 OpenAPI 发送的自定义消息。</li><li>媒体流音量变化，需要通过公共流 OpenAPI 开启回调。JSON 格式说明如下： {<br>"Type":"VolumeIndication", //具体业务类型<br>"VolumeInfos"[// 业务类型对应信息<br>{<br>"RoomId":"1000001", // 房间 ID<br>"UserId":"1000001", // 用户 ID<br>"StreamType":0, // 0:摄像头流；1:屏幕流<br>"LinearVolume":1 // 线性音量大小<br>}<br>]<br>}</li></ul> |
| sourceType | ByteRTCDataMessageSourceType | 数据消息来源，参看 [ByteRTCDataMessageSourceType](macOS-keytype#ByteRTCDataMessageSourceType)。通过调用客户端 API 插入的 SEI 信息，应通过回调 [rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:](#ByteRTCVideoDelegate-rtcengine-onpublicstreamseimessagereceived-andmessage-andsourcetype) 获取。 |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamvideoframedecoded-withframeinfo"></span>
### rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamVideoFrameDecoded:(NSString * _Nonnull)publicStreamId withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:));
```
公共流的首帧视频解码成功

关于订阅公共流，详见 [startPlayPublicStream:](macOS-api#ByteRTCVideo-startplaypublicstream)。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| publicStreamId | NSString * | 公共流 ID |
| frameInfo | ByteRTCVideoFrameInfo * | 视频帧信息，参看 [ByteRTCVideoFrameInfo](macOS-keytype#ByteRTCVideoFrameInfo) |


<span id="ByteRTCVideoDelegate-rtcengine-onfirstpublicstreamaudioframe"></span>
### rtcEngine:onFirstPublicStreamAudioFrame:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamAudioFrame:(NSString * _Nonnull)publicStreamId;
```
公共流的音频首帧解码成功

关于订阅公共流，详见 [startPlayPublicStream:](macOS-api#ByteRTCVideo-startplaypublicstream)。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| publicStreamId | NSString * | 公共流 ID |


<span id="ByteRTCVideoDelegate-rtcengine-oncloudproxyconnected"></span>
### rtcEngine:onCloudProxyConnected:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *  _Nonnull)engine onCloudProxyConnected:(NSInteger)interval;
```
调用 [startCloudProxy:](macOS-api#ByteRTCVideo-startcloudproxy) 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| interval | NSInteger | 从开启云代理到连接成功经过的时间，单位为 ms |


<span id="ByteRTCVideoDelegate-rtcengine-onechotestresult"></span>
### rtcEngine:onEchoTestResult:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onEchoTestResult:(ByteRTCEchoTestResult)result NS_SWIFT_NAME(rtcEngine(_:onEchoTestResult:));
```
关于音视频回路测试结果的回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| result | ByteRTCEchoTestResult | 测试结果，参看 [ByteRTCEchoTestResult](macOS-keytype#ByteRTCEchoTestResult)。 |


**注意**

该回调触发的时机包括：
- 检测过程中采集设备发生错误时；
- 检测成功后；
- 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。

<span id="ByteRTCVideoDelegate-rtcengineonnetworktimesynchronized"></span>
### rtcEngineOnNetworkTimeSynchronized:
```objectivec
- (void)rtcEngineOnNetworkTimeSynchronized:(ByteRTCVideo *_Nonnull)engine;
```
首次调用 [getNetworkTimeInfo](macOS-api#ByteRTCVideo-getnetworktimeinfo) 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | [ByteRTCVideo](macOS-api#ByteRTCVideo) 对象 |


<span id="ByteRTCVideoDelegate-rtcengine-onhardwareechodetectionresult"></span>
### rtcEngine:onHardwareEchoDetectionResult:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHardwareEchoDetectionResult:(ByteRTCHardwareEchoDetectionResult)result NS_SWIFT_NAME(rtcEngine(_:onHardwareEchoDetectionResult:));
```
通话前回声检测结果回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| result | ByteRTCHardwareEchoDetectionResult | 参见 [ByteRTCHardwareEchoDetectionResult](macOS-keytype#ByteRTCHardwareEchoDetectionResult)。 |


**注意**

- 通话前调用 [startHardwareEchoDetection:](macOS-api#ByteRTCVideo-starthardwareechodetection) 后，将触发本回调返回检测结果。
- 建议在收到检测结果后，调用 [stopHardwareEchoDetection](macOS-api#ByteRTCVideo-stophardwareechodetection) 停止检测，释放对音频设备的占用。
- 如果 SDK 在通话中检测到回声，将通过 [rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning) 回调 `ByteRTCMediaDeviceWarningDetectLeakEcho`。

<span id="ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror"></span>
### rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLocalProxyStateChanged:(ByteRTCLocalProxyType)type withProxyState:(ByteRTCLocalProxyState)state withProxyError:(ByteRTCLocalProxyError)error;
```
本地代理状态发生改变回调。调用 [setLocalProxy:](macOS-api#ByteRTCVideo-setlocalproxy) 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | `ByteRTCVideo` 实例 |
| type | ByteRTCLocalProxyType | 本地代理类型。参看 [ByteRTCLocalProxyType](macOS-keytype#ByteRTCLocalProxyType)。 |
| state | ByteRTCLocalProxyState | 本地代理状态。参看 [ByteRTCLocalProxyState](macOS-keytype#ByteRTCLocalProxyState)。 |
| error | ByteRTCLocalProxyError | 本地代理错误。参看 [ByteRTCLocalProxyError](macOS-keytype#ByteRTCLocalProxyError)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onusermuteaudio-uid-mutestate"></span>
### rtcEngine:onUserMuteAudio:uid:muteState:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMuteAudio:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState __deprecated_msg("Will be removed in new version");
```
> Deprecated since 3.36 and will be deleted in 3.51, use [rtcRoom:onUserPublishStream:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type), [rtcRoom:onUserPublishScreen:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type), [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) and [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) instead.

房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例 |
| roomId | NSString * | 房间 ID |
| uid | NSString * | 改变本地音频发送状态的用户 ID |
| muteState | ByteRTCMuteState | 发送状态，参看 [ByteRTCMuteState](macOS-keytype#ByteRTCMuteState) |


<span id="ByteRTCVideoDelegate-rtcengine-onusermutevideo-uid-withmutestate"></span>
### rtcEngine:onUserMuteVideo:uid:withMuteState:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMuteVideo:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState
NS_SWIFT_NAME(rtcEngine(_:onUserMuteVideo:uid:withMuteState:)) __deprecated_msg("Will be removed in new version");
```
> Deprecated since 3.36 and will be deleted in 3.51, use [rtcRoom:onUserPublishStream:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishstream-type), [rtcRoom:onUserPublishScreen:type:](#ByteRTCRoomDelegate-rtcroom-onuserpublishscreen-type), [rtcRoom:onUserUnpublishStream:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishstream-type-reason) and [rtcRoom:onUserUnpublishScreen:type:reason:](#ByteRTCRoomDelegate-rtcroom-onuserunpublishscreen-type-reason) instead.

房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例 |
| roomId | NSString * | 房间 ID |
| uid | NSString * | 暂停/恢复发送视频流的用户 ID。 |
| muteState | ByteRTCMuteState | 视频流的发送状态。参看 [ByteRTCMuteState](macOS-keytype#ByteRTCMuteState)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onmediadevicestatechanged-device_type-device_state-device_error"></span>
### rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onMediaDeviceStateChanged:(NSString*_Nonnull)deviceID
      device_type:(ByteRTCMediaDeviceType)deviceType
     device_state:(ByteRTCMediaDeviceState)deviceState
     device_error:(ByteRTCMediaDeviceError)deviceError
__attribute((deprecated("Will be removed in new version")));
```
> Deprecated since 3.37 and will be deleted in 3.51, use [rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicestatechanged-device_type-device_state-device_error) and [rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:](#ByteRTCVideoDelegate-rtcengine-onvideodevicestatechanged-device_type-device_state-device_error) instead.

媒体设备状态回调。提示音频采集、音频播放、摄像头视频采集、屏幕视频采集四种媒体设备的状态。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 实例 |
| deviceID | NSString * | 设备 ID |
| deviceType | ByteRTCMediaDeviceType | 设备类型，参看 [ByteRTCMediaDeviceType](macOS-keytype#ByteRTCMediaDeviceType)。 |
| deviceState | ByteRTCMediaDeviceState | 设备状态，参看 [ByteRTCMediaDeviceState](macOS-keytype#ByteRTCMediaDeviceState)。 |
| deviceError | ByteRTCMediaDeviceError | 设备错误类型，参看 [ByteRTCMediaDeviceError](macOS-keytype#ByteRTCMediaDeviceError)。 |


<span id="ByteRTCVideoDelegate-rtcengine-onmediadevicewarning-devicetype-devicewarning"></span>
### rtcEngine:onMediaDeviceWarning:deviceType:deviceWarning:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onMediaDeviceWarning:(NSString*_Nonnull)deviceId
       deviceType:(ByteRTCMediaDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning
__deprecated_msg("Will be removed in new version");
```
> Deprecated since 3.37 and will be deleted in 3.51, use [rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onaudiodevicewarning-devicetype-devicewarning) and [rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:](#ByteRTCVideoDelegate-rtcengine-onvideodevicewarning-devicetype-devicewarning) instead.

媒体设备警告回调。媒体设备包括：音频采集设备、音频渲染设备、和视频采集设备。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| deviceId | NSString * | 设备 ID |
| deviceType | ByteRTCMediaDeviceType | 参看 [ByteRTCMediaDeviceType](macOS-keytype#ByteRTCMediaDeviceType) |
| deviceWarning | ByteRTCMediaDeviceWarning | 参看 [ByteRTCMediaDeviceWarning](macOS-keytype#ByteRTCMediaDeviceWarning) |


<span id="ByteRTCVideoDelegate-rtcengine-log"></span>
### rtcEngine:log:
```objectivec
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine log:(NSDictionary* _Nonnull)dict;
```
> Deprecated since 3.45 and will be deleted in 3.51.

SDK 内部日志回调。

SDK 内部运行时，会把日志回调给业务方，方便排查问题。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象。 |
| dict | NSDictionary * | 日志内容。 |


<span id="ByteRTCVideoDelegate-rtcengine-onaudiomixingstatechanged-state-error"></span>
### rtcEngine:onAudioMixingStateChanged:state:error:
```objectivec
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioMixingStateChanged:(NSInteger)mixId state:(ByteRTCAudioMixingState)state error:(ByteRTCAudioMixingError)error;
```
> Deprecated since 353. Use [ByteRTCAudioEffectPlayerEventHandler](#ByteRTCAudioEffectPlayerEventHandler) and [ByteRTCMediaPlayerEventHandler](#ByteRTCMediaPlayerEventHandler) instead. 

音频混音文件播放状态改变时回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | 当前 RTC SDK 对象 |
| mixId | NSInteger | 混音 ID <br>使用 [ByteRTCAudioMixingManager](macOS-api#ByteRTCAudioMixingManager) 相关接口时传入的唯一 ID。 |
| state | ByteRTCAudioMixingState | <br>混音状态<br>其混音状态可参考： [ByteRTCAudioMixingState](macOS-keytype#ByteRTCAudioMixingState)。 |
| error | ByteRTCAudioMixingError | <br>错误码<br>详见 [ByteRTCAudioMixingError](macOS-keytype#ByteRTCAudioMixingError)。 |


**注意**

此回调会被触发的时机汇总如下：
- 当调用 [startAudioMixing:filePath:config:](macOS-api#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 方法成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。
- 当使用相同的 ID 重复调用 [startAudioMixing:filePath:config:](macOS-api#ByteRTCAudioMixingManager-startaudiomixing-filepath-config) 后，后一次会覆盖前一次，且本回调会以 ByteRTCAudioMixingStateStopped 通知前一次混音已停止。
- 当调用 [pauseAudioMixing:](macOS-api#ByteRTCAudioMixingManager-pauseaudiomixing) 方法暂停播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePaused 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。
- 当调用 [resumeAudioMixing:](macOS-api#ByteRTCAudioMixingManager-resumeaudiomixing) 方法恢复播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。
- 当调用 [stopAudioMixing:](macOS-api#ByteRTCAudioMixingManager-stopaudiomixing) 方法停止播放成功后，会触发 state 值为 ByteRTCAudioMixingStateStopped 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。
- 播放结束会触发 state 值为 ByteRTCAudioMixingStateFinished 回调。

<span id="ByteRTCVideoDelegate-rtcengine-onhttpproxystate"></span>
### rtcEngine:onHttpProxyState:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpProxyState:(NSInteger)state;
```
> Deprecated 在 3.52 及之后废弃，将在 3.57 删除，使用 [rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:](#ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror) 替换

HTTP 代理连接状态改变时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| state | NSInteger | 当前 HTTP 代理连接状态 |


<span id="ByteRTCVideoDelegate-rtcengine-onhttpsproxystate"></span>
### rtcEngine:onHttpsProxyState:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpsProxyState:(NSInteger)state;
```
> Deprecated 在 3.52 及之后废弃，将在 3.57 删除，使用 [rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:](#ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror) 替换

HTTPS 代理连接状态改变时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| state | NSInteger | 当前 HTTPS 代理连接状态 |


<span id="ByteRTCVideoDelegate-rtcengine-onsocks5proxystate-cmd-proxy_address-local_address-remote_address"></span>
### rtcEngine:onSocks5ProxyState:cmd:proxy_address:local_address:remote_address:
```objectivec
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onSocks5ProxyState:(NSInteger)state
              cmd:(NSString *_Nonnull)cmd
    proxy_address:(NSString *_Nonnull)proxyAddress
    local_address:(NSString *_Nonnull)localAddress
   remote_address:(NSString *_Nonnull)remoteAddress;
```
> Deprecated 在 3.52 及之后废弃，将在 3.57 删除，使用 [rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:](#ByteRTCVideoDelegate-rtcengine-onlocalproxystatechanged-withproxystate-withproxyerror) 替换

SOCKS5 代理状态改变时，收到该回调。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| engine | ByteRTCVideo * | ByteRTCVideo 对象 |
| state | NSInteger | SOCKS5 代理连接状态 |
| cmd | NSString * | 代理连接的每一步操作命令 |
| proxyAddress | NSString * | 代理地址信息 |
| localAddress | NSString * | 当前连接使用的本地地址 |
| remoteAddress | NSString * | 远端的连接地址 |


<span id="LiveTranscodingDelegate"></span>
# LiveTranscodingDelegate
```objectivec
@protocol LiveTranscodingDelegate <NSObject>
```
> Deprecated since 3.52, use [ByteRTCMixedStreamObserver](#ByteRTCMixedStreamObserver) instead. 

转推直播观察者。

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| BOOL | [isSupportClientPushStream](#LiveTranscodingDelegate-issupportclientpushstream) |
| void | [onStreamMixingEvent:taskId:error:mixType:](#LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype) |
| void | [onMixingAudioFrame:timestamp:taskId:](#LiveTranscodingDelegate-onmixingaudioframe-timestamp-taskid) |
| void | [onMixingVideoFrame:taskId:](#LiveTranscodingDelegate-onmixingvideoframe-taskid) |
| void | [onMixingDataFrame:taskId:](#LiveTranscodingDelegate-onmixingdataframe-taskid) |

## 函数说明
<span id="LiveTranscodingDelegate-issupportclientpushstream"></span>
### isSupportClientPushStream
```objectivec
_- (BOOL)isSupportClientPushStream;
```
是否具有推流能力。
- false：不具备推流能力（默认值）
- true：具备推流能力


**注意**

如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。

<span id="LiveTranscodingDelegate-onstreammixingevent-taskid-error-mixtype"></span>
### onStreamMixingEvent:taskId:error:mixType:
```objectivec
- (void)onStreamMixingEvent:(ByteRTCStreamMixingEvent)event
                     taskId:(NSString *_Nonnull)taskId
                      error:(ByteRtcTranscoderErrorCode)Code
                    mixType:(ByteRTCStreamMixingType)mixType;
```
转推直播状态回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| event | ByteRTCStreamMixingEvent | 转推直播任务状态，参看 [ByteRTCStreamMixingEvent](macOS-keytype#ByteRTCStreamMixingEvent)。 |
| taskId | NSString * | 转推直播任务 ID。 |
| Code | ByteRtcTranscoderErrorCode | 转推直播错误码，参看 [ByteRtcTranscoderErrorCode](macOS-errorcode#ByteRtcTranscoderErrorCode)。 |
| mixType | ByteRTCStreamMixingType | 转推直播类型，参看 [ByteRTCStreamMixingType](macOS-keytype#ByteRTCStreamMixingType)。 |


<span id="LiveTranscodingDelegate-onmixingaudioframe-timestamp-taskid"></span>
### onMixingAudioFrame:timestamp:taskId:
```objectivec
- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame timestamp:(int64_t)timeStamp taskId:(NSString *_Nonnull)taskId;
```
端云一体合流音频 PCM 回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audioFrame | ByteRTCAudioFrame * | PCM 编码的合流音频数据帧，参看 [ByteRTCAudioFrame](macOS-keytype#ByteRTCAudioFrame)。 |
| timeStamp | int64_t | 时间戳，单位毫秒。 |
| taskId | NSString * | 转推直播任务 ID。 |


**注意**

收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。

<span id="LiveTranscodingDelegate-onmixingvideoframe-taskid"></span>
### onMixingVideoFrame:taskId:
```objectivec
- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流视频 YUV 回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoFrame | ByteRTCVideoFrame * | YUV 合流视频数据帧，参看 [ByteRTCVideoFrame](macOS-keytype#ByteRTCVideoFrame)。 |
| taskId | NSString * | 转推直播任务 ID。 |


**注意**

收到该回调的周期取决于视频的帧率。

<span id="LiveTranscodingDelegate-onmixingdataframe-taskid"></span>
### onMixingDataFrame:taskId:
```objectivec
- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame taskId:(NSString *_Nonnull)taskId;
```
端云一体合流视频 SEI 数据


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| dataFrame | ByteRTCFrameExtendedData * | SEI 数据，详见 [ByteRTCFrameExtendedData](macOS-keytype#ByteRTCFrameExtendedData)。 |
| taskId | NSString * | 转推直播任务 ID。 |


<span id="ByteRTCLocalEncodedVideoFrameObserver"></span>
# ByteRTCLocalEncodedVideoFrameObserver
```objectivec
BYTERTC_APPLE_EXPORT @protocol ByteRTCLocalEncodedVideoFrameObserver<NSObject>
```
本地视频帧监测器

注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。


## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onLocalEncodedVideoFrame:Frame:](#ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame) |

## 函数说明
<span id="ByteRTCLocalEncodedVideoFrameObserver-onlocalencodedvideoframe-frame"></span>
### onLocalEncodedVideoFrame:Frame:
```objectivec
- (void)onLocalEncodedVideoFrame:(ByteRTCStreamIndex) streamIndex
                           Frame:(ByteRTCEncodedVideoFrame * _Null_unspecified)frame;
```
调用 [registerLocalEncodedVideoFrameObserver:](macOS-api#ByteRTCVideo-registerlocalencodedvideoframeobserver) 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamIndex | ByteRTCStreamIndex | 本地视频帧类型，参看 [ByteRTCStreamIndex](macOS-keytype#ByteRTCStreamIndex) |
| frame | ByteRTCEncodedVideoFrame *_Null_unspecified | 本地视频帧信息，参看 [ByteRTCEncodedVideoFrame](macOS-keytype#ByteRTCEncodedVideoFrame) |


<span id="ByteRTCRemoteEncodedVideoFrameObserver"></span>
# ByteRTCRemoteEncodedVideoFrameObserver
```objectivec
BYTERTC_APPLE_EXPORT @protocol ByteRTCRemoteEncodedVideoFrameObserver<NSObject>
```
远端编码后视频数据监测器


**注意**

回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。

## 成员函数
| 返回 | 名称 |
| --- | --- |
| void | [onRemoteEncodedVideoFrame:withEncodedVideoFrame:](#ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe) |

## 函数说明
<span id="ByteRTCRemoteEncodedVideoFrameObserver-onremoteencodedvideoframe-withencodedvideoframe"></span>
### onRemoteEncodedVideoFrame:withEncodedVideoFrame:
```objectivec
- (void)onRemoteEncodedVideoFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
            withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;
```
调用 [registerRemoteEncodedVideoFrameObserver:](macOS-api#ByteRTCVideo-registerremoteencodedvideoframeobserver) 后，SDK 监测到远端编码后视频数据时，触发该回调


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamKey | ByteRTCRemoteStreamKey * | 收到的远端流信息，参看 [ByteRTCRemoteStreamKey](macOS-keytype#ByteRTCRemoteStreamKey) |
| videoFrame | ByteRTCEncodedVideoFrame * | 收到的远端视频帧信息，参看 [ByteRTCEncodedVideoFrame](macOS-keytype#ByteRTCEncodedVideoFrame) |


<span id="ByteRTCMediaPlayerCustomSourceProvider"></span>
# ByteRTCMediaPlayerCustomSourceProvider
```objectivec
BYTERTC_APPLE_EXPORT @protocol ByteRTCMediaPlayerCustomSourceProvider <NSObject>
```
内存播放数据源回调


## 成员函数
| 返回 | 名称 |
| --- | --- |
| int | [onReadData:bufferSize:](#ByteRTCMediaPlayerCustomSourceProvider-onreaddata-buffersize) |
| int64_t | [onSeek:whence:](#ByteRTCMediaPlayerCustomSourceProvider-onseek-whence) |

## 函数说明
<span id="ByteRTCMediaPlayerCustomSourceProvider-onreaddata-buffersize"></span>
### onReadData:bufferSize:
```objectivec
-(int)onReadData:(uint8_t*_Nonnull) buffer bufferSize:(int)bufferSize;
```
> Available since 3.53

调用 [openWithCustomSource:config:](macOS-api#ByteRTCMediaPlayer-openwithcustomsource-config) 接口播放用户传入的内存音频数据时，会触发此回调，用户需要写入音频数据。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| buffer | uint8_t * | 内存地址。在该地址中写入音频数据，写入音频数据的大小不超过 bufferSize 中填入的数值。支持的音频数据格式有: mp3，aac，m4a，3gp，wav。 |
| bufferSize | int | 音频数据大小，单位为字节。如果你想停止播放内存音频数据，可在 bufferSize 中填入小于或等于 0 的数，此时 SDK 会停止调用此接口。 |


**返回值**

返回实际读取的音频数据大小。


**注意**

若 [openWithCustomSource:config:](macOS-api#ByteRTCMediaPlayer-openwithcustomsource-config) 接口调用失败，请在 buffer 和 bufferSize 两个参数中填入 0。 此时 SDK 会停止调用此接口。

<span id="ByteRTCMediaPlayerCustomSourceProvider-onseek-whence"></span>
### onSeek:whence:
```objectivec
-(int64_t)onSeek:(int64_t)offset whence:(ByteRTCMediaPlayerCustomSourceSeekWhence)whence;
```
> Available since 3.53

根据设置好的内存音频数据的读取位置和读取偏移量对音频数据进行偏移，以便 SDK 读取和分析音频数据。

在调用 [openWithCustomSource:config:](macOS-api#ByteRTCMediaPlayer-openwithcustomsource-config) 接口传入内存音频数据，或者调用 [setPosition:position:](macOS-api#ByteRTCAudioEffectPlayer-setposition-position) 设置了音频数据的起始播放位置后，SDK 会对音频数据进行读取和分析，此时会触发该回调，你需要根据参数中设置的起始读取位置和偏移量进行操作。


**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| offset | int64_t | 音频数据读取偏移量，单位为字节，取值可正可负。 |
| whence | ByteRTCMediaPlayerCustomSourceSeekWhence | 音频数据的起始读取位置。参看 [ByteRTCMediaPlayerCustomSourceSeekWhence](macOS-keytype#ByteRTCMediaPlayerCustomSourceSeekWhence) |


**返回值**

定位成功，返回偏移后的位置信息，或返回音频数据的大小。

定位失败，返回 -1。
