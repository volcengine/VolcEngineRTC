# ByteRTCAudioScenarioType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioScenarioType)
```

音频场景类型。
选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。
如果以下音频场景类型无法满足你的业务需要，请联系技术支持人员。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioScenarioMusic | 0 | （默认）音乐场景。<br/>此场景适用于对音乐表现力有要求的场景，如音乐直播等。<br/>音频采集播放设备和采集播放状态，到音量类型的映射如下：<br/><table><br/><tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr><br/><tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr><br/><tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr><br/><tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr><br/></table> |
| ByteRTCAudioScenarioHighqualityCommunication | 1 | 高质量通话场景。<br/>此场景适用于对音乐表现力有要求，但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。<br/>此场景下，更倾向于使用媒体音量。由此，可能引起开关麦时音量突变。如不希望有此突变，请使用 `ByteRTCAudioScenarioHighqualityChat`。<br/>此场景可以兼顾外放/使用蓝牙耳机时的音频体验，并避免使用蓝牙耳机时音量类型切换导致的听感突变。<br/>音频采集播放设备和采集播放状态，到音量类型的映射如下：<br/><table><br/><tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr><br/><tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr><br/><tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr><br/><tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr><br/></table> |
| ByteRTCAudioScenarioCommunication | 2 | 纯通话音量场景。<br/>此场景下，无论客户端音频路由情况和发布订阅状态，全程使用通话音量。<br/>适用于需要频繁上下麦的通话或会议场景。<br/>此场景可以保持统一的音频模式，不会有音量突变的听感；<br/>最大程度地消除回声，使通话清晰度达到最优；<br/>使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。<br/>但是，会压低使用媒体音量进行播放的其他音频的音量，且音质会变差。 |
| ByteRTCAudioScenarioMedia | 3 | 纯媒体场景。一般不建议使用。<br/>此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。<br/>外放通话时，可能出现回声和啸叫，请联系技术支持人员。 |
| ByteRTCAudioScenarioGameStreaming | 4 | 游戏媒体场景。<br/>此场景下，蓝牙耳机时使用通话音量，其它设备使用媒体音量。<br/>若外放通话且无游戏音效消除优化时音质不理想，请联系技术支持人员。 |
| ByteRTCAudioScenarioHighqualityChat | 5 | 高质量畅聊场景。  <br><br/>此场景和 `ByteRTCAudioScenarioHighqualityCommunication` 高度类似，唯一的差异在于：此场景下，在使用设备自带的麦克风和扬声器/听筒进行通话时，开关麦始终采用通话音量，不会引起音量类型突变。 <br><br/>音频采集播放设备和采集播放状态，到音量类型的映射如下：<br><br/><table><br/><tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr><br/><tr><td>设备自带麦克风和扬声器/听筒</td><td>通话音量</td><td>通话音量</td><td>/</td></tr><br/><tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr><br/><tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr><br/></table> |


# ByteRTCVoiceChangerType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVoiceChangerType)
```

变声特效类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVoiceChangerOriginal | 0 | 原声，不含特效 |
| ByteRTCVoiceChangerGiant | 1 | 巨人 |
| ByteRTCVoiceChangerChipmunk | 2 | 花栗鼠 |
| ByteRTCVoiceChangerMinionst | 3 | 小黄人 |
| ByteRTCVoiceChangerVibrato | 4 | 颤音 |
| ByteRTCVoiceChangerRobot | 5 | 机器人 |


# ByteRTCVoiceReverbType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVoiceReverbType)
```

混响特效类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVoiceReverbOriginal | 0 | 原声，不含特效 |
| ByteRTCVoiceReverbEcho | 1 | 回声 |
| ByteRTCVoiceReverbConcert | 2 | 演唱会 |
| ByteRTCVoiceReverbEthereal | 3 | 空灵 |
| ByteRTCVoiceReverbKTV | 4 | KTV |
| ByteRTCVoiceReverbStudio | 5 | 录音棚 |


# ByteRTCAudioProfileType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioProfileType)
```

音质档位


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioProfileDefault | 0 | 默认音质<br><br/>服务器下发或客户端已设置的 [ByteRTCRoomProfile](#bytertcroomprofile) 的音质配置 |
| ByteRTCAudioProfileFluent | 1 | 流畅  <br><br/>单声道，采样率为 16 kHz，编码码率为 32 Kbps。 <br><br/>流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。 |
| ByteRTCAudioProfileStandard | 2 | 单声道标准音质。  <br><br/>采样率为 24 kHz，编码码率为 48 Kbps。 <br><br/>适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和狼人杀等游戏。 |
| ByteRTCAudioProfileHD | 3 | 双声道音乐音质  <br><br/>采样率为 48 kHz，编码码率为 128 kbps。 <br><br/>超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。 <br><br/>游戏场景不建议使用。 |
| ByteRTCAudioProfileStandardStereo | 4 | 双声道标准音质。采样率为 48 KHz，编码码率最大值为 80 Kbps |
| ByteRTCAudioProfileHDMono | 5 | 单声道音乐音质。采样率为 48 kHz，编码码率最大值为 64 Kbps |


# ByteRTCAudioDeviceType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioDeviceType)
```

当前音频设备类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioDeviceTypeUnknown | -1 | 未知音频设备 |
| ByteRTCAudioDeviceTypeRenderDevice | 0 | 音频渲染设备 |
| ByteRTCAudioDeviceTypeCaptureDevice | 1 | 音频采集设备 |
| ByteRTCAudioDeviceTypeScreenCaptureDevice | 2 | 屏幕流音频设备 |


# ByteRTCAudioSampleRate
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioSampleRate)
```

音频采样率，单位为 Hz。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioSampleRateAuto | -1 | 默认设置。 |
| ByteRTCAudioSampleRate8000 | 8000 | 8000 Hz |
| ByteRTCAudioSampleRate16000 | 16000 | 16000 Hz |
| ByteRTCAudioSampleRate32000 | 32000 | 32000 Hz |
| ByteRTCAudioSampleRate44100 | 44100 | 44100 Hz |
| ByteRTCAudioSampleRate48000 | 48000 | 48000 Hz |


# ByteRTCAudioChannel
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioChannel)
```

音频声道。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioChannelAuto | -1 | 默认设置。 |
| ByteRTCAudioChannelMono | 1 | 单声道 |
| ByteRTCAudioChannelStereo | 2 | 双声道 |


# ByteRTCAACProfile
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAACProfile)
```

AAC 编码类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAACProfileLC | 0 | LC（默认） |
| ByteRTCAACProfileHEv1 | 1 | HEv1 |
| ByteRTCAACProfileHEv2 | 2 | HEv2 |


# ByteRTCAudioRoute
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioRoute)
```

音频播放路由


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioRouteUnknown | -1 | 未知设备 |
| ByteRTCAudioRouteHeadset | 1 | 有线耳机 |
| ByteRTCAudioRouteEarpiece | 2 | 听筒。设备自带的，一般用于通话的播放硬件。 |
| ByteRTCAudioRouteSpeakerphone | 3 | 扬声器。设备自带的，一般用于免提播放的硬件。 |
| ByteRTCAudioRouteHeadsetBluetooth | 4 | 蓝牙耳机 |
| ByteRTCAudioRouteHeadsetUSB | 5 | USB设备 |


# ByteRTCAudioPlaybackDevice
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioPlaybackDevice)
```

音频播放设备 <br>
音频设备变化时 SDK 通过 `rtcEngine:onAudioPlaybackDeviceChanged:` 回调当前音频播放设备。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioPlaybackDeviceHeadset | 1 | 有线耳机 |
| ByteRTCAudioPlaybackDeviceEarpiece | 2 | 听筒 |
| ByteRTCAudioPlaybackDeviceSpeakerphone | 3 | 扬声器 |
| ByteRTCAudioPlaybackDeviceHeadsetBluetooth | 4 | 蓝牙耳机 |
| ByteRTCAudioPlaybackDeviceHeadsetUSB | 5 | USB设备 |


# ByteRTCASRAuthorizationType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCASRAuthorizationType)
```

语音识别服务鉴权方式，详情请咨询语音识别服务相关人员


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCASRAuthorizationTypeToken | 0 | 使用 token 不设置加密形式。  <br> |
| ByteRTCASRAuthorizationTypeSignature | 1 | 带有 token 额外使用 signature 加密，此种加密形式需要额外传递 secret token 。  <br> |


# ByteRTCASRErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCASRErrorCode)
```

语音识别服务错误码。  <br>
除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 `startASR:handler:` 重启语音识别功能。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCASRErrorNetworkInterrupted | -1 | 网络连接中断，服务不可用，内部会进行重连 |
| ByteRTCASRErrorAlreadyStarted | -2 | 用户已经调用过 `startASR:handler:`。  <br><br/>开启语音识别服务后，你需要先调用 `stopASR` 停止语音识别服务，才能二次调用 `startASR:handler:` 再次开启服务。 |
| ByteRTCASRErrorTokenEmpty | -3 | 语音识别服务所需 token 为空 |
| ByteRTCErrorSignatureKeyEmpty | -4 | Signature 鉴权模式下 secretKey 为空 |
| ByteRTCASRErrorUserIdNull | -5 | 用户 ID 为空 |
| ByteRTCASRErrorAPPIDNull | -6 | 应用 ID 为空 |
| ByteRTCASRErrorClusterNull | -7 | 语音识别服务 cluster 为空 |
| ByteRTCASRErrorOperationDenied | -8 | 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。 |


# ByteRTCAudioMixingType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingType)
```

混音播放类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioMixingTypePlayout | 0 | 仅本地播放 |
| ByteRTCAudioMixingTypePublish | 1 | 仅远端播放 |
| ByteRTCAudioMixingTypePlayoutAndPublish | 2 | 本地和远端同时播放 |


# ByteRTCAudioMixingDualMonoMode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingDualMonoMode)
```

混音播放声道类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioMixingDualMonoModeAuto | 0 | 和音频文件一致 |
| ByteRTCAudioMixingDualMonoModeL | 1 | 只能听到音频文件中左声道的音频 |
| ByteRTCAudioMixingDualMonoModeR | 2 | 只能听到音频文件中右声道的音频 |
| ByteRTCAudioMixingDualMonoModeMix | 3 | 能同时听到音频文件中左右声道的音频 |


# ByteRTCAudioMixingState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingState)
```

音频混音文件播放状态。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioMixingStatePreloaded | 0 | 混音已加载 |
| ByteRTCAudioMixingStatePlaying | 1 | 混音正在播放 |
| ByteRTCAudioMixingStatePaused | 2 | 混音暂停 |
| ByteRTCAudioMixingStateStopped | 3 | 混音停止 |
| ByteRTCAudioMixingStateFailed | 4 | 混音播放失败 |
| ByteRTCAudioMixingStateFinished | 5 | 混音播放结束 |
| ByteRTCAudioMixingStatePCMEnabled | 6 | 准备PCM混音 |
| ByteRTCAudioMixingStatePCMDisabled | 7 | PCM混音播放结束 |


# ByteRTCAudioMixingError
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingError)
```

混音错误码。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioMixingErrorOk | 0 | 正常 |
| ByteRTCAudioMixingErrorPreloadFailed | 1 | 预加载失败，找不到混音文件或者文件长度超出 20s |
| ByteRTCAudioMixingErrorStartFailed | 2 | 混音开启失败，找不到混音文件或者混音文件打开失败 |
| ByteRTCAudioMixingErrorIdNotFound | 3 | 混音 ID 异常 |
| ByteRTCAudioMixingErrorSetPositionFailed | 4 | 设置混音文件的播放位置出错 |
| ByteRTCAudioMixingErrorInValidVolume | 5 | 音量参数不合法，仅支持设置的音量值为[0, 400] |
| ByteRTCAudioMixingErrorLoadConflict | 6 | 播放的文件与预加载的文件不一致。请先使用 [unloadAudioMixing:](iOS-api.md#ByteRTCAudioMixingManager-unloadaudiomixing) 卸载此前的文件。 |
| ByteRTCAudioMixingErrorIdTypeNotMatch | 7 | 不支持此混音类型。 |
| ByteRTCAudioMixingErrorInValidPitch | 8 | 设置混音文件的音调不合法 |
| ByteRTCAudioMixingErrorInValidAudioTrack | 9 | 设置混音文件的音轨不合法 |
| ByteRTCAudioMixingErrorIsStarting | 10 | 混音文件正在启动中 |
| ByteRTCAudioMixingErrorInValidPlaybackSpeed | 11 | 设置混音文件的播放速度不合法 |


# ByteRTCAudioSourceType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioSourceType)
```

音频输入源类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioSourceTypeExternal | 0 | 自定义采集音频源 |
| ByteRTCAudioSourceTypeInternal | 1 | RTC SDK 内部采集音频源 |


# ByteRTCAudioRenderType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioRenderType)
```

音频输出源类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioRenderTypeExternal | 0 | 自定义渲染音频 |
| ByteRTCAudioRenderTypeInternal | 1 | RTC SDK 内部渲染音频 |


# ByteRTCEarMonitorMode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCEarMonitorMode)
```

开启/关闭耳返功能。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCEarMonitorModeOff | 0 | 关闭耳返功能。 |
| ByteRTCEarMonitorModeOn | 1 | 开启耳返功能。 |


# ByteRTCAudioFrameCallbackMethod
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameCallbackMethod)
```

音频回调方法


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioFrameCallbackRecord | 0 | 本地麦克风录制的音频数据回调 |
| ByteRTCAudioFrameCallbackPlayback | 1 | 订阅的远端所有用户混音后的音频数据回调 |
| ByteRTCAudioFrameCallbackMixed | 2 | 本地麦克风录制和订阅的远端所有用户混音后的音频数据回调 |
| ByteRTCAudioFrameCallbackRemoteUser | 3 | 订阅的远端每个用户混音前的音频数据回调 |


# ByteRTCAudioFrameMethod
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameMethod)
```

返回给音频处理器的音频类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioFrameProcessorRecord | 0 | 本地采集的音频。 |
| ByteRTCAudioFrameProcessorPlayback | 1 | 远端音频流的混音音频。 |
| ByteRTCAudioFrameProcessorRemoteUser | 2 | 各个远端音频流。 |
| ByteRTCAudioFrameProcessorEarMonitor | 3 | 软件耳返音频。 |
| ByteRTCAudioFrameProcessorScreen | 4 | 屏幕共享音频。 |


# ByteRTCAudioReportMode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioReportMode)
```

音量回调配置模式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioReportModeNormal | 0 | 默认始终开启音量回调。 |
| ByteRTCAudioReportModeDisconnect | 1 | 可见用户进房并停止推流后，关闭音量回调。 |
| ByteRTCAudioReportModeReset | 2 | 可见用户进房并停止推流后，开启音量回调，回调值重置为0。 |


# ByteRTCAudioPropertiesMode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAudioPropertiesMode)
```

音频信息提示中是否包含本地混音音频数据。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCAudioPropertiesModeMicrohone | 0 | 音频信息提示中，仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。 |
| ByteRTCAudioPropertiesModeAudioMixing | 1 | 音频信息提示中，除本地麦克风采集的音频数据和本地屏幕音频采集数据外，还包含本地混音的音频数据。 |


# ByteRTCAudioVolumeInfo
```objectivec
@interface ByteRTCAudioVolumeInfo : NSObject
```

音频流来源的用户 ID, 及对应的音量。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [uid](#ByteRTCAudioVolumeInfo-uid) |
| **NSUInteger** | [linearVolume](#ByteRTCAudioVolumeInfo-linearvolume) |
| **NSUInteger** | [nonlinearVolume](#ByteRTCAudioVolumeInfo-nonlinearvolume) |


## 变量说明
<span id="ByteRTCAudioVolumeInfo-uid"></span>
### uid
```objectivec
@property(copy, nonatomic) NSString * _Nonnull uid;
```
音频流来源的用户 ID


<span id="ByteRTCAudioVolumeInfo-linearvolume"></span>
### linearVolume
```objectivec
@property(assign, nonatomic) NSUInteger linearVolume;
```
线性音量，取值范围为：[0,255]


<span id="ByteRTCAudioVolumeInfo-nonlinearvolume"></span>
### nonlinearVolume
```objectivec
@property(assign, nonatomic) NSUInteger nonlinearVolume;
```
非线性音量，取值范围为：[-127,0]



# ByteRTCAudioFormat
```objectivec
@interface ByteRTCAudioFormat : NSObject
```

音频参数格式


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCAudioSampleRate** | [sampleRate](#ByteRTCAudioFormat-samplerate) |
| **ByteRTCAudioChannel** | [channel](#ByteRTCAudioFormat-channel) |


## 变量说明
<span id="ByteRTCAudioFormat-samplerate"></span>
### sampleRate
```objectivec
@property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
```
音频采样率，详见 [ByteRTCAudioSampleRate](#bytertcaudiosamplerate)


<span id="ByteRTCAudioFormat-channel"></span>
### channel
```objectivec
@property(nonatomic, assign) ByteRTCAudioChannel channel;
```
音频声道，详见 [ByteRTCAudioChannel](#bytertcaudiochannel)



# ByteRTCAudioFrame
```objectivec
@interface ByteRTCAudioFrame : NSObject
```

PCM 音频帧


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSData*** | [buffer](#ByteRTCAudioFrame-buffer) |
| **int** | [samples](#ByteRTCAudioFrame-samples) |
| **ByteRTCAudioChannel** | [channel](#ByteRTCAudioFrame-channel) |
| **ByteRTCAudioSampleRate** | [sampleRate](#ByteRTCAudioFrame-samplerate) |


## 变量说明
<span id="ByteRTCAudioFrame-buffer"></span>
### buffer
```objectivec
@property(strong, nonatomic) NSData * _Nonnull buffer;
```
PCM 数据


<span id="ByteRTCAudioFrame-samples"></span>
### samples
```objectivec
@property(assign, nonatomic) int samples;
```
采样点个数


<span id="ByteRTCAudioFrame-channel"></span>
### channel
```objectivec
@property(assign, nonatomic) ByteRTCAudioChannel channel;
```
音频声道，参看 [ByteRTCAudioChannel](#bytertcaudiochannel)。
双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。


<span id="ByteRTCAudioFrame-samplerate"></span>
### sampleRate
```objectivec
@property(assign, nonatomic) ByteRTCAudioSampleRate sampleRate;
```
采样率，参看 [ByteRTCAudioSampleRate](#bytertcaudiosamplerate)。



# ByteRTCASRConfig
```objectivec
@interface ByteRTCASRConfig : NSObject
```

使用自动语音识别服务所需校验信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [appId](#ByteRTCASRConfig-appid) |
| **NSString*** | [userId](#ByteRTCASRConfig-userid) |
| **NSString*** | [accessToken](#ByteRTCASRConfig-accesstoken) |
| **NSString*** | [secretKey](#ByteRTCASRConfig-secretkey) |
| **NSString*** | [cluster](#ByteRTCASRConfig-cluster) |
| **ByteRTCASRAuthorizationType** | [authorizationType](#ByteRTCASRConfig-authorizationtype) |


## 变量说明
<span id="ByteRTCASRConfig-appid"></span>
### appId
```objectivec
@property(copy, nonatomic) NSString *_Nonnull appId;
```
应用 ID


<span id="ByteRTCASRConfig-userid"></span>
### userId
```objectivec
@property(copy, nonatomic) NSString *_Nonnull userId;
```
用户 ID


<span id="ByteRTCASRConfig-accesstoken"></span>
### accessToken
```objectivec
@property(copy, nonatomic) NSString *_Nonnull accessToken;
```
访问令牌


<span id="ByteRTCASRConfig-secretkey"></span>
### secretKey
```objectivec
@property(copy, nonatomic) NSString *_Nonnull secretKey;
```
私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://www.volcengine.com/docs/6561/107789)


<span id="ByteRTCASRConfig-cluster"></span>
### cluster
```objectivec
@property(copy, nonatomic) NSString *_Nonnull cluster;
```
场景信息，参看[业务集群](https://www.volcengine.com/docs/6561/80818#_3-2-2-%E5%8F%91%E9%80%81-full-client-request)


<span id="ByteRTCASRConfig-authorizationtype"></span>
### authorizationType
```objectivec
@property(assign, nonatomic) ByteRTCASRAuthorizationType authorizationType;
```
鉴权模式，参看 [ByteRTCASRAuthorizationType](#bytertcasrauthorizationtype)



# ByteRTCASREngineEventHandler
```objectivec
@protocol ByteRTCASREngineEventHandler<NSObject>
```

语音识别服务使用状态回调


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onSuccess](#ByteRTCASREngineEventHandler-onsuccess) |
| **void** | [onMessage:](#ByteRTCASREngineEventHandler-onmessage) |
| **void** | [onError:withErrorMessage:](#ByteRTCASREngineEventHandler-onerror-witherrormessage) |


## 函数说明
<span id="ByteRTCASREngineEventHandler-onsuccess"></span>
### onSuccess
```objectivec

- (void)onSuccess;
```
语音识别服务开启成功回调


<span id="ByteRTCASREngineEventHandler-onmessage"></span>
### onMessage:
```objectivec

- (void)onMessage:(NSString *_Nonnull)message;
```
语音转文字成功回调，该回调返回识别后的全量消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **NSString*** | 识别完成后得到的文字消息 |


**注意**
若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。

<span id="ByteRTCASREngineEventHandler-onerror-witherrormessage"></span>
### onError:withErrorMessage:
```objectivec

- (void)onError:(NSInteger)errorCode withErrorMessage:(NSString *_Nonnull)errorMessage;
```
当语音识别服务内部发生错误事件时触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **NSInteger** | 错误码  <br/>• < 0: 参数错误或 API 调用顺序错误，参看 [ByteRTCASRErrorCode](#bytertcasrerrorcode)；  <br/>• >0: 参看 [语音识别服务错误码](https://www.volcengine.com/docs/6561/80818#_3-3-%E9%94%99%E8%AF%AF%E7%A0%81) |
| errorMessage | **NSString*** | 错误原因说明 |


# ByteRTCAudioMixingConfig
```objectivec
@interface ByteRTCAudioMixingConfig : NSObject
```

混音配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCAudioMixingType** | [type](#ByteRTCAudioMixingConfig-type) |
| **NSInteger** | [playCount](#ByteRTCAudioMixingConfig-playcount) |
| **NSInteger** | [position](#ByteRTCAudioMixingConfig-position) |
| **NSInteger** | [callbackOnProgressInterval](#ByteRTCAudioMixingConfig-callbackonprogressinterval) |


## 变量说明
<span id="ByteRTCAudioMixingConfig-type"></span>
### type
```objectivec
@property(assign, nonatomic) ByteRTCAudioMixingType type;
```
混音播放类型，详见 [ByteRTCAudioMixingType](#bytertcaudiomixingtype)


<span id="ByteRTCAudioMixingConfig-playcount"></span>
### playCount
```objectivec
@property(assign, nonatomic) NSInteger playCount;
```
混音播放次数

+ play_count <= 0: 无限循环  <br>
+ play_count == 1: 播放一次（默认）  <br>
+ play_count > 1: 播放 play_count 次


<span id="ByteRTCAudioMixingConfig-position"></span>
### position
```objectivec
@property(assign, nonatomic) NSInteger position;
```
混音时音频文件播放进度条位置，参数为整数，单位为毫秒


<span id="ByteRTCAudioMixingConfig-callbackonprogressinterval"></span>
### callbackOnProgressInterval
```objectivec
@property(assign, nonatomic) NSInteger callbackOnProgressInterval;
```
设置音频文件播放进度回调的时间间隔，参数为为大于 0 的 10 的倍数，单位为毫秒，设置后 SDK 将按照设置的值触发 `rtcEngine:onAudioMixingPlayingProgress:progress:` 回调，默认不回调。  <br>

+ 当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。  <br>
+ 当传入的值小于等于 0 时，不会触发进度回调。  <br>



# ByteRTCAudioPropertiesConfig
```objectivec
@interface ByteRTCAudioPropertiesConfig : NSObject
```

音频属性信息提示的相关配置。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [interval](#ByteRTCAudioPropertiesConfig-interval) |
| **BOOL** | [enable_spectrum](#ByteRTCAudioPropertiesConfig-enable_spectrum) |
| **BOOL** | [enable_vad](#ByteRTCAudioPropertiesConfig-enable_vad) |
| **ByteRTCAudioReportMode** | [local_main_report_mode](#ByteRTCAudioPropertiesConfig-local_main_report_mode) |
| **ByteRTCAudioPropertiesMode** | [audio_report_mode](#ByteRTCAudioPropertiesConfig-audio_report_mode) |


## 变量说明
<span id="ByteRTCAudioPropertiesConfig-interval"></span>
### interval
```objectivec
@property(assign, nonatomic) NSInteger interval;
```
信息提示间隔，单位：ms <br>

+ `<= 0`: 关闭信息提示  <br>
+ `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
+ `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>


<span id="ByteRTCAudioPropertiesConfig-enable_spectrum"></span>
### enable_spectrum
```objectivec
@property(assign, nonatomic) BOOL enable_spectrum;
```
是否开启音频频谱检测。


<span id="ByteRTCAudioPropertiesConfig-enable_vad"></span>
### enable_vad
```objectivec
@property(assign, nonatomic) BOOL enable_vad;
```
是否开启人声检测 (VAD)。


<span id="ByteRTCAudioPropertiesConfig-local_main_report_mode"></span>
### local_main_report_mode
```objectivec
@property(assign, nonatomic) ByteRTCAudioReportMode local_main_report_mode;
```
音量回调模式。详见 [ByteRTCAudioReportMode](#bytertcaudioreportmode)。


<span id="ByteRTCAudioPropertiesConfig-audio_report_mode"></span>
### audio_report_mode
```objectivec
@property(assign, nonatomic) ByteRTCAudioPropertiesMode audio_report_mode;
```
设置 `rtcEngine:onLocalAudioPropertiesReport:` 回调中是否包含本地混音音频数据。参看 [ByteRTCAudioPropertiesMode](#bytertcaudiopropertiesmode)。<br>
默认仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。



# ByteRTCAudioPropertiesInfo
```objectivec
@interface ByteRTCAudioPropertiesInfo : NSObject
```

音频属性信息  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [linearVolume](#ByteRTCAudioPropertiesInfo-linearvolume) |
| **NSInteger** | [nonlinearVolume](#ByteRTCAudioPropertiesInfo-nonlinearvolume) |
| **NSInteger** | [vad](#ByteRTCAudioPropertiesInfo-vad) |
| **NSArray<NSNumber*>*** | [spectrum](#ByteRTCAudioPropertiesInfo-spectrum) |


## 变量说明
<span id="ByteRTCAudioPropertiesInfo-linearvolume"></span>
### linearVolume
```objectivec
@property(assign, nonatomic) NSInteger linearVolume;
```
线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。<br>

- [0, 25]: 无声 <br>
- [26, 75]: 低音量 <br>
- [76, 204]: 中音量 <br>
- [205, 255]: 高音量 <br>


<span id="ByteRTCAudioPropertiesInfo-nonlinearvolume"></span>
### nonlinearVolume
```objectivec
@property(assign, nonatomic) NSInteger nonlinearVolume;
```
非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。 <br>

- [-127, -60]: 无声 <br>
- [-59, -40]: 低音量 <br>
- [-39, -20]: 中音量 <br>
- [-19, 0]: 高音量 <br>


<span id="ByteRTCAudioPropertiesInfo-vad"></span>
### vad
```objectivec
@property(assign, nonatomic) NSInteger vad;
```
人声检测（VAD）结果

+ 1: 检测到人声。<br>
+ 0: 未检测到人声。<br>
+ -1: 未开启 VAD。<br>


<span id="ByteRTCAudioPropertiesInfo-spectrum"></span>
### spectrum
```objectivec
@property(copy, nonatomic) NSArray<NSNumber*> * _Nonnull spectrum;
```
频谱数组。默认长度为 257。



# ByteRTCLocalAudioPropertiesInfo
```objectivec
@interface ByteRTCLocalAudioPropertiesInfo : NSObject
```

本地音频属性信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCStreamIndex** | [streamIndex](#ByteRTCLocalAudioPropertiesInfo-streamindex) |
| **ByteRTCAudioPropertiesInfo*** | [audioPropertiesInfo](#ByteRTCLocalAudioPropertiesInfo-audiopropertiesinfo) |


## 变量说明
<span id="ByteRTCLocalAudioPropertiesInfo-streamindex"></span>
### streamIndex
```objectivec
@property(assign, nonatomic) ByteRTCStreamIndex streamIndex;
```
流属性，包括主流、屏幕流。参看 [ByteRTCStreamIndex](#bytertcstreamindex)


<span id="ByteRTCLocalAudioPropertiesInfo-audiopropertiesinfo"></span>
### audioPropertiesInfo
```objectivec
@property(strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;
```
音频属性信息，详见 [ByteRTCAudioPropertiesInfo](#bytertcaudiopropertiesinfo)



# ByteRTCRemoteAudioPropertiesInfo
```objectivec
@interface ByteRTCRemoteAudioPropertiesInfo : NSObject
```

远端音频属性信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCRemoteStreamKey*** | [streamKey](#ByteRTCRemoteAudioPropertiesInfo-streamkey) |
| **ByteRTCAudioPropertiesInfo*** | [audioPropertiesInfo](#ByteRTCRemoteAudioPropertiesInfo-audiopropertiesinfo) |


## 变量说明
<span id="ByteRTCRemoteAudioPropertiesInfo-streamkey"></span>
### streamKey
```objectivec
@property(strong, nonatomic) ByteRTCRemoteStreamKey *_Nonnull streamKey;
```
远端流信息，详见 [ByteRTCRemoteStreamKey](#bytertcremotestreamkey)


<span id="ByteRTCRemoteAudioPropertiesInfo-audiopropertiesinfo"></span>
### audioPropertiesInfo
```objectivec
@property(strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;
```
音频属性信息，详见 [ByteRTCAudioPropertiesInfo](#bytertcaudiopropertiesinfo)



# Position
```objectivec
@interface Position : NSObject
```

本地用户在房间内的位置坐标，需自行建立空间直角坐标系


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [x](#Position-x) |
| **int** | [y](#Position-y) |
| **int** | [z](#Position-z) |


## 变量说明
<span id="Position-x"></span>
### x
```objectivec
@property(nonatomic, assign) int x;
```
x 坐标


<span id="Position-y"></span>
### y
```objectivec
@property(nonatomic, assign) int y;
```
y 坐标


<span id="Position-z"></span>
### z
```objectivec
@property(nonatomic, assign) int z;
```
z 坐标



# ByteRTCMulDimSingScoringMode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCMulDimSingScoringMode)
```

K 歌打分维度。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMulDimSingScoringModeNote | 0 | 按照音高进行评分。 |


# ByteRTCSingScoringRealtimeInfo
```objectivec
@interface ByteRTCSingScoringRealtimeInfo : NSObject
```

实时评分信息。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [currentPosition](#ByteRTCSingScoringRealtimeInfo-currentposition) |
| **int** | [userPitch](#ByteRTCSingScoringRealtimeInfo-userpitch) |
| **int** | [standardPitch](#ByteRTCSingScoringRealtimeInfo-standardpitch) |
| **int** | [sentenceIndex](#ByteRTCSingScoringRealtimeInfo-sentenceindex) |
| **int** | [sentenceScore](#ByteRTCSingScoringRealtimeInfo-sentencescore) |
| **int** | [totalScore](#ByteRTCSingScoringRealtimeInfo-totalscore) |
| **int** | [averageScore](#ByteRTCSingScoringRealtimeInfo-averagescore) |


## 变量说明
<span id="ByteRTCSingScoringRealtimeInfo-currentposition"></span>
### currentPosition
```objectivec
@property(nonatomic, assign) int currentPosition;
```
当前的播放进度。


<span id="ByteRTCSingScoringRealtimeInfo-userpitch"></span>
### userPitch
```objectivec
@property(nonatomic, assign) int userPitch;
```
演唱者的音高。


<span id="ByteRTCSingScoringRealtimeInfo-standardpitch"></span>
### standardPitch
```objectivec
@property(nonatomic, assign) int standardPitch;
```
标准音高。


<span id="ByteRTCSingScoringRealtimeInfo-sentenceindex"></span>
### sentenceIndex
```objectivec
@property(nonatomic, assign) int sentenceIndex;
```
歌词分句索引。


<span id="ByteRTCSingScoringRealtimeInfo-sentencescore"></span>
### sentenceScore
```objectivec
@property(nonatomic, assign) int sentenceScore;
```
上一句歌词的评分。


<span id="ByteRTCSingScoringRealtimeInfo-totalscore"></span>
### totalScore
```objectivec
@property(nonatomic, assign) int totalScore;
```
当前演唱的累计分数。


<span id="ByteRTCSingScoringRealtimeInfo-averagescore"></span>
### averageScore
```objectivec
@property(nonatomic, assign) int averageScore;
```
当前演唱的平均分数。



# ByteRTCStandardPitchInfo
```objectivec
@interface ByteRTCStandardPitchInfo : NSObject
```

标准音高数据组。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [startTime](#ByteRTCStandardPitchInfo-starttime) |
| **int** | [duration](#ByteRTCStandardPitchInfo-duration) |
| **int** | [pitch](#ByteRTCStandardPitchInfo-pitch) |


## 变量说明
<span id="ByteRTCStandardPitchInfo-starttime"></span>
### startTime
```objectivec
@property(nonatomic, assign) int startTime;
```
开始时间，单位 ms。


<span id="ByteRTCStandardPitchInfo-duration"></span>
### duration
```objectivec
@property(nonatomic, assign) int duration;
```
持续时间，单位 ms。


<span id="ByteRTCStandardPitchInfo-pitch"></span>
### pitch
```objectivec
@property(nonatomic, assign) int pitch;
```
音高。



# ByteRTCSingScoringConfig
```objectivec
@interface ByteRTCSingScoringConfig : NSObject
```

K 歌评分配置。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCMulDimSingScoringMode** | [mode](#ByteRTCSingScoringConfig-mode) |
| **ByteRTCAudioSampleRate** | [sampleRate](#ByteRTCSingScoringConfig-samplerate) |
| **NSString*** | [lyricsFilepath](#ByteRTCSingScoringConfig-lyricsfilepath) |
| **NSString*** | [midiFilepath](#ByteRTCSingScoringConfig-midifilepath) |


## 变量说明
<span id="ByteRTCSingScoringConfig-mode"></span>
### mode
```objectivec
@property(nonatomic, assign) ByteRTCMulDimSingScoringMode mode;
```
打分维度，详见 [ByteRTCMulDimSingScoringMode](#bytertcmuldimsingscoringmode)。


<span id="ByteRTCSingScoringConfig-samplerate"></span>
### sampleRate
```objectivec
@property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
```
音频采样率。仅支持 44100 Hz、48000 Hz。


<span id="ByteRTCSingScoringConfig-lyricsfilepath"></span>
### lyricsFilepath
```objectivec
@property(nonatomic, copy) NSString *_Nonnull lyricsFilepath;
```
歌词文件路径。打分功能仅支持 KRC 歌词文件。


<span id="ByteRTCSingScoringConfig-midifilepath"></span>
### midiFilepath
```objectivec
@property(nonatomic, copy) NSString *_Nonnull midiFilepath;
```
歌曲 midi 文件路径。



# ByteRTCUserOfflineReason
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCUserOfflineReason)
```

远端用户离开房间的原因。  <br>


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCUserOfflineReasonQuit | 0 | 远端用户调用 `leaveRoom` 方法主动退出房间。  <br> |
| ByteRTCUserOfflineReasonDropped | 1 | 远端用户因网络等原因掉线。  <br> |
| ByteRTCUserOfflineReasonSwitchToInvisible | 2 | 远端用户切换至隐身状态。  <br> |
| ByteRTCUserOfflineReasonKickedByAdmin | 3 | 远端用户被踢出出房间。<br/>因调用踢出用户的 OpenAPI，远端用户被踢出房间。 |


# ByteRTCStreamRemoveReason
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCStreamRemoveReason)
```

房间内远端流移除原因。  <br>


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCStreamRemoveReasonUnpublish | 0 | 远端用户停止发布流。  <br> |
| ByteRTCStreamRemoveReasonPublishFailed | 1 | 远端用户发布流失败。  <br> |
| ByteRTCStreamRemoveReasonKeepLiveFailed | 2 | 保活失败。  <br> |
| ByteRTCStreamRemoveReasonClientDisconnected | 3 | 远端用户断网。  <br> |
| ByteRTCStreamRemoveReasonRepublish | 4 | 远端用户重新发布流。  <br> |
| ByteRTCStreamRemoveReasonOther | 5 | 其他原因。  <br> |


# ByteRTCRoomProfile
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRoomProfile)
```

房间模式<br>
根据所需场景，选择合适的房间模式，应用不同的音视频算法、视频参数和网络配置 <br>
调用 `setAudioProfile` 改变音频参数配置


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRoomProfileCommunication | 0 | 默认场景，通用模式 |
| ByteRTCRoomProfileGame | 2 | 游戏语音模式，低功耗、低流量消耗。<br><br/>低端机在此模式下运行时，进行了额外的性能优化：<br><br/>+ 部分低端机型配置编码帧长 40/60 <br><br/>+ 部分低端机型关闭软件 3A 音频处理 <br><br/>增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。 |
| ByteRTCRoomProfileCloudGame | 3 | 云游戏模式。<br><br/>如果你的游戏场景需要低延迟的配置，使用此设置。<br><br/>此设置下，弱网抗性较差。 |
| ByteRTCRoomProfileLowLatency | 4 | 云渲染模式。超低延时配置。  <br><br/>如果你的应用并非游戏但又对延时要求较高时，选用此模式 <br><br/>该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br> |
| ByteRTCRoomProfileChat | 5 | 适用于 1 vs 1 音视频通话 |
| ByteRTCRoomProfileChatRoom | 6 | 适用于 3 人及以上纯语音通话。<br><br/>通话中，闭麦时为是媒体模式，上麦后切换为通话模式。 |
| ByteRTCRoomProfileLwTogether | 7 | 实现多端同步播放音视频，适用于 “一起看” 或 “一起听” 场景。<br><br/>该场景中，使用 RTC 信令同步播放进度，共享的音频内容不通过 RTC 进行传输。 |
| ByteRTCRoomProfileGameHD | 8 | 适用于对音质要求较高的游戏场景，优化音频 3A 策略，只通过媒体模式播放音频 |
| ByteRTCRoomProfileCoHost | 9 | 适用于直播中主播之间连麦的业务场景。<br><br/>该场景中，直播时通过 CDN，发起连麦 PK 时使用 RTC。 |
| ByteRTCRoomProfileInteractivePodcast | 10 | 适用于单主播和观众进行音视频互动的直播。通话模式，上下麦不会有模式切换，避免音量突变现象 |
| ByteRTCRoomProfileKTV | 11 | 线上 KTV 场景，音乐音质，低延迟<br><br/>使用 RTC 传输伴奏音乐，混音后的歌声，适合独唱或单通合唱 |
| ByteRTCRoomProfileChorus | 12 | 适合在线实时合唱场景，高音质，超低延迟。使用本配置前请联系技术支持进行协助完成其他配置。 |
| ByteRTCRoomProfileGameStreaming | 14 | 适用于 1 vs 1 游戏串流，支持公网或局域网。 |
| ByteRTCRoomProfileLanLiveStreaming | 15 | 适用于局域网的 1 对多视频直播，最高支持 8K， 60 帧/秒， 100 Mbps 码率<br><br/>需要在局域网配置私有化部署媒体服务器。 |
| ByteRTCRoomProfileMeeting | 16 | 适用于云端会议中的个人设备 |
| ByteRTCRoomProfileMeetingRoom | 17 | 适用于云端会议中的会议室终端设备，例如 Rooms，投屏盒子等。 |
| ByteRTCRoomProfileClassroom | 18 | 适用于课堂互动，房间内所有成员都可以进行音视频互动<br><br/>当你的场景中需要同时互动的成员超过 10人时使用此模式 |


# ByteRTCConnectionState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCConnectionState)
```

SDK 与信令服务器连接状态。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCConnectionStateDisconnected | 1 | 连接断开超过 12s，此时 SDK 会尝试自动重连。 |
| ByteRTCConnectionStateConnecting | 2 | 首次请求建立连接，正在连接中。 |
| ByteRTCConnectionStateConnected | 3 | 首次连接成功。 |
| ByteRTCConnectionStateReconnecting | 4 | 涵盖了以下情况：<br><br/>+ 首次连接时，10秒连接不成功; <br><br/>+ 连接成功后，断连 10 秒。自动重连中。 |
| ByteRTCConnectionStateReconnected | 5 | 连接断开后，重连成功。 |
| ByteRTCConnectionStateLost | 6 | 处于 `ByteRTCConnectionStateDisconnected` 状态超过 10 秒，且期间重连未成功。SDK 仍将继续尝试重连。 |
| ByteRTCConnectionStateFailed | 7 | 连接失败，服务端状态异常。SDK 不会自动重连，请重新进房，或联系技术支持。 |


# ByteRTCNetworkType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCNetworkType)
```

SDK 网络连接类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCNetworkTypeUnknown | -1 | 网络连接类型未知。 |
| ByteRTCNetworkTypeDisconnected | 0 | 网络连接已断开。 |
| ByteRTCNetworkTypeLAN | 1 | 网络连接类型为 LAN 。 |
| ByteRTCNetworkTypeWIFI | 2 | 网络连接类型为 Wi-Fi（包含热点）。 |
| ByteRTCNetworkTypeMobile2G | 3 | 网络连接类型为 2G 移动网络。 |
| ByteRTCNetworkTypeMobile3G | 4 | 网络连接类型为 3G 移动网络。 |
| ByteRTCNetworkTypeMobile4G | 5 | 网络连接类型为 4G 移动网络。 |
| ByteRTCNetworkTypeMobile5G | 6 | 网络连接类型为 5G 移动网络。 |


# ByteRTCNetworkDetectionStopReason
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCNetworkDetectionStopReason)
```

通话前探测的停止原因
`rtcEngine:onNetworkDetectionStopped:` 回调的参数类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCNetworkDetectionStopReasonUser | 0 | 用户主动停止。 |
| ByteRTCNetworkDetectionStopReasonTimeout | 1 | 探测超过三分钟。 |
| ByteRTCNetworkDetectionStopReasonConnectionLost | 2 | 探测网络连接断开。<br><br/>当超过 12s 没有收到回复，SDK 将断开网络连接，并且不再尝试重连。 |
| ByteRTCNetworkDetectionStopReasonStreaming | 3 | 本地开始推拉流，停止探测。 |
| ByteRTCNetworkDetectionStopReasonInnerErr | 4 | 网络探测失败，内部异常 |


# ByteRTCNetworkDetectionLinkType
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCNetworkDetectionLinkType)
```

通话前探测链接的类型
`rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:` 回调的参数类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCNetworkDetectionLinkTypeUp | 0 | 上行网络探测。 |
| ByteRTCNetworkDetectionLinkTypeDown | 1 | 下行网络探测。 |


# ByteRTCNetworkQuality
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCNetworkQuality)
```

媒体流网络质量。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCNetworkQualityUnknown | 0 | 网络质量未知。 |
| ByteRTCNetworkQualityExcellent | 1 | 网络质量极好。 |
| ByteRTCNetworkQualityGood | 2 | 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。 |
| ByteRTCNetworkQualityPoor | 3 | 主观感受有瑕疵但不影响沟通。 |
| ByteRTCNetworkQualityBad | 4 | 勉强能沟通但不顺畅。 |
| ByteRTCNetworkQualityVeryBad | 5 | 网络质量非常差，基本不能沟通。 |
| ByteRTCNetworkQualityDisconnected | 6 | 12 s 内无应答，代表网络断开，将返回本枚举值。<br/>你也可以通过 rtcEngine:onConnectionStateChanged: 监听 ByteRTCConnectionStateDisconnected = 1 感知网络断开。<br/>更多网络状态信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。 |


# ByteRTCSubscribeState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCSubscribeState)
```

订阅媒体流状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCSubscribeStateSuccess | 0 | 订阅/取消订阅流成功 |
| ByteRTCSubscribeStateFailedNotInRoom | 1 | 订阅/取消订阅流失败，本地用户未在房间中 |
| ByteRTCSubscribeStateFailedStreamNotFound | 2 | 订阅/取消订阅流失败，房间内未找到指定的音视频流 |
| ByteRTCSubscribeStateFailedOverLimit | 3 | 超过订阅流数上限 |


# ByteRTCPerformanceAlarmReason
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmReason)
```

性能相关告警的原因


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCPerformanceAlarmReasonBandwidthFallback | 0 | 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。 |
| ByteRTCPerformanceAlarmReasonBandwidthResumed | 1 | 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。 |
| ByteRTCPerformanceAlarmReasonFallback | 2 | 如果未开启发送性能回退，收到此告警时，意味着性能不足；<br><br/>如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。 |
| ByteRTCPerformanceAlarmReasonResumed | 3 | 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复；<br><br/>如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。 |


# ByteRTCPerformanceAlarmMode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmMode)
```

性能回退的模式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCPerformanceAlarmModeNormal | 0 | 未开启发布性能回退 |
| ByteRTCPerformanceAlarmModeSimulcast | 1 | 已开启发布性能回退 |


# ByteRTCMessageConfig
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCMessageConfig)
```

发送消息的可靠有序类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMessageConfigReliableOrdered | 0 | 低延时可靠有序消息 |
| ByteRTCMessageConfigUnreliableOrdered | 1 | 超低延时有序消息 |
| ByteRTCMessageConfigUnreliableUnordered | 2 | 超低延时无序消息 |


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
| ByteRTCUserMessageSendResultBroken | 2 | 通道断开，没有发送 |
| ByteRTCUserMessageSendResultNoReceiver | 3 | 找不到接收方 |
| ByteRTCUserMessageSendResultNoRelayPath | 4 | 远端用户未登录或未进房 |
| ByteRTCUserMessageSendResultNotJoin | 100 | 消息发送方没有加入房间 |
| ByteRTCUserMessageSendResultInit | 101 | 连接未完成初始化 |
| ByteRTCUserMessageSendResultNoConnection | 102 | 没有可用的数据传输通道连接 |
| ByteRTCUserMessageSendResultExceedMaxLength | 103 | 消息超过最大长度，当前为64KB |
| ByteRTCUserMessageSendResultEmptyUser | 104 | 接收消息的单个用户 id 为空 |
| ByteRTCUserMessageSendResultServerParamsNotSet | 106 | 发送消息给业务方服务器之前没有设置参数 |
| ByteRTCUserMessageSendResultUnknown | 1000 | 失败，未知错误。 |


# ByteRTCUserOnlineStatus
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCUserOnlineStatus)
```

用户在线状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCUserOnlineStatusOffline | 0 | 对端用户离线<br/>对端用户已经调用 `logout`，或者没有调用 `login:uid:` 进行登录 |
| ByteRTCUserOnlineStatusOnline | 1 | 对端用户在线<br/>对端用户调用 `login:uid:` 登录，并且连接状态正常 |
| ByteRTCUserOnlineStatusUnreachable | 2 | 无法获取对端用户在线状态<br/>发生级联错误、对端用户在线状态异常时返回 |


# ByteRTCRoomMessageSendResult
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRoomMessageSendResult)
```

房间内广播消息发送结果


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRoomMessageSendResultSuccess | 200 | 消息发送成功 |
| ByteRTCRoomMessageSendResultNotJoin | 100 | 失败，发送方未加入房间 |
| ByteRTCRoomMessageSendResultInit | 101 | 失败，连接未完成初始化。 |
| ByteRTCRoomMessageSendResultNoConnection | 102 | 失败，没有可用的连接。 |
| ByteRTCRoomMessageSendResultExceedMaxLength | 103 | 消息超过最大长度，当前为 64KB |
| ByteRTCRoomMessageSendResultUnknown | 1000 | 失败，未知错误。 |


# ByteRTCPublishFallbackOption
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCPublishFallbackOption)
```

发布端音视频流回退选项


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCPublishFallbackOptionDisabled | 0 | 上行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。 |
| ByteRTCPublishFallbackOptionSimulcast | 1 | 上行网络不佳或设备性能不足时，发布的视频流会从大流到小流依次降级，直到与当前网络性能匹配，具体降级规则参看[性能回退](https://www.volcengine.com/docs/6348/70137)文档。 |


# ByteRTCSubscribeFallbackOption
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeFallbackOption)
```

订阅端音视频流回退选项。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCSubscribeFallbackOptionDisabled | 0 | 下行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。 |
| ByteRTCSubscribeFallbackOptionVideoStreamLow | 1 | 下行网络不佳或设备性能不足时，对视频流做降级处理，具体降级规则参看[音视频流回退](70137)。 <br>该设置仅对发布端调用 `enableSimulcastMode:` 开启发送多路流功能的情况生效。 |
| ByteRTCSubscribeFallbackOptionAudioOnly | 2 | 下行网络不佳或设备性能不足时，先对视频流做回退处理。当网络状况不满足接收弱流时，则自动取消接收视频，仅接收音频。<br>该设置仅对发布端调用 `enableSimulcastMode:` 开启发送多路流功能的情况生效。|


# ByteRTCRemoteUserPriority
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCRemoteUserPriority)
```

远端用户优先级。在性能不足需要回退时，会先回退优先级低的用户的音视频流


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRemoteUserPriorityLow | 0 | 用户优先级为低，默认值 |
| ByteRTCRemoteUserPriorityMedium | 100 | 用户优先级为正常 |
| ByteRTCRemoteUserPriorityHigh | 200 | 用户优先级为高 |


# ByteRTCFallbackOrRecoverReason
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCFallbackOrRecoverReason)
```

本地用户订阅的远端流触发回退策略的原因。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCFallbackOrRecoverReasonUnknown | -1 | 其他原因，非带宽和性能原因引起的回退或恢复。默认值 |
| ByteRTCFallbackOrRecoverReasonSubscribeFallbackByBandwidth | 0 | 由带宽不足导致的订阅端音视频流回退。 |
| ByteRTCFallbackOrRecoverReasonSubscribeFallbackByPerformance | 1 | 由性能不足导致的订阅端音视频流回退。 |
| ByteRTCFallbackOrRecoverReasonSubscribeRecoverByBandwidth | 2 | 由带宽恢复导致的订阅端音视频流恢复。 |
| ByteRTCFallbackOrRecoverReasonSubscribeRecoverByPerformance | 3 | 由性能恢复导致的订阅端音视频流恢复。 |
| ByteRTCFallbackOrRecoverReasonPublishFallbackByBandwidth | 4 | 由带宽不足导致的发布端音视频流回退。 |
| ByteRTCFallbackOrRecoverReasonPublishFallbackByPerformance | 5 | 由性能不足导致的发布端音视频流回退。 |
| ByteRTCFallbackOrRecoverReasonPublishRecoverByBandwidth | 6 | 由带宽恢复导致的发布端音视频流恢复。 |
| ByteRTCFallbackOrRecoverReasonPublishRecoverByPerformance | 7 | 由性能恢复导致的发布端音视频流恢复。 |


# ByteRTCLocalAudioStreamState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamState)
```

本地音频流状态。  <br>
SDK 通过 `onLocalAudioStateChanged` 回调该状态。  <br>


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCLocalAudioStreamStateStopped | 0 | 本地音频默认初始状态。<br/>麦克风停止工作时回调该状态，对应错误码 [ByteRTCLocalAudioStreamError](#bytertclocalaudiostreamerror) 中的 ByteRTCLocalAudioStreamErrorOk |
| ByteRTCLocalAudioStreamStateRecording | 1 | 本地音频录制设备启动成功。<br/>采集到音频首帧时回调该状态，对应错误码 [ByteRTCLocalAudioStreamError](#bytertclocalaudiostreamerror) 中的 ByteRTCLocalAudioStreamErrorOk |
| ByteRTCLocalAudioStreamStateEncoding | 2 | 本地音频首帧编码成功。<br/>音频首帧编码成功时回调该状态，对应错误码 [ByteRTCLocalAudioStreamError](#bytertclocalaudiostreamerror) 中的 ByteRTCLocalAudioStreamErrorOk |
| ByteRTCLocalAudioStreamStateFailed | 3 | 本地音频启动失败，在以下时机回调该状态：  <br><br/>+ 本地录音设备启动失败，对应错误码 [ByteRTCLocalAudioStreamError](#bytertclocalaudiostreamerror) 中的 ByteRTCLocalAudioStreamErrorRecordFailure  <br><br/>+ 检测到没有录音设备权限，对应错误码 [ByteRTCLocalAudioStreamError](#bytertclocalaudiostreamerror) 中的 ByteRTCLocalAudioStreamErrorDeviceNoPermission <br><br/>+ 音频编码失败，对应错误码 [ByteRTCLocalAudioStreamError](#bytertclocalaudiostreamerror) 中的 ByteRTCLocalAudioStreamError <br> |


# ByteRTCLocalAudioStreamError
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamError)
```

本地音频流状态改变时的错误码。
SDK 通过 `onLocalAudioStateChanged` 回调该错误码。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCLocalAudioStreamErrorOk | 0 | 本地音频状态正常 |
| ByteRTCLocalAudioStreamErrorFailure | 1 | 本地音频出错原因未知 |
| ByteRTCLocalAudioStreamErrorDeviceNoPermission | 2 | 没有权限启动本地音频录制设备 |
| ByteRTCLocalAudioStreamErrorRecordFailure | 4 | 本地音频录制失败，建议你检查录制设备是否正常工作 |
| ByteRTCLocalAudioStreamErrorEncodeFailure | 5 | 本地音频编码失败 |
| ByteRTCLocalAudioStreamErrorNoRecordingDevice | 6 | 没有可用的音频录制设备 |


# ByteRTCLocalVideoStreamState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoStreamState)
```

本地视频流状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCLocalVideoStreamStateStopped | 0 | 本地视频默认初始状态<br/>摄像头停止工作时回调该状态，对应错误码 [ByteRTCLocalVideoStreamError](#bytertclocalvideostreamerror) 中的 ByteRTCLocalVideoStreamErrorOk |
| ByteRTCLocalVideoStreamStateRecording | 1 | 本地视频录制设备启动成功<br/>采集到视频首帧时回调该状态，对应错误码 [ByteRTCLocalVideoStreamError](#bytertclocalvideostreamerror) 中的 ByteRTCLocalVideoStreamErrorOk |
| ByteRTCLocalVideoStreamStateEncoding | 2 | 本地视频首帧编码成功<br/>本地视频首帧编码成功时回调该状态，对应错误码 [ByteRTCLocalVideoStreamError](#bytertclocalvideostreamerror) 中的 ByteRTCLocalVideoStreamErrorOk |
| ByteRTCLocalVideoStreamStateFailed | 3 | 本地视频启动失败, 在以下时机回调该状态：  <br><br/>+ 本地采集设备启动失败，对应错误码 [ByteRTCLocalVideoStreamError](#bytertclocalvideostreamerror) 中的 ByteRTCLocalVideoStreamErrorCaptureFailure  <br><br/>+ 检测到没有摄像头权限，对应错误码 [ByteRTCLocalVideoStreamError](#bytertclocalvideostreamerror) 中的 ByteRTCLocalVideoStreamErrorDeviceNoPermission <br><br/>+ 视频编码失败，对应错误码 [ByteRTCLocalVideoStreamError](#bytertclocalvideostreamerror) 中的 ByteRTCLocalVideoStreamErrorEncodeFailure  <br> |


# ByteRTCLocalVideoStreamError
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoStreamError)
```

本地视频状态改变时的错误码


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCLocalVideoStreamErrorOk | 0 | 本地视频状态正常（本地视频状态改变正常时默认返回值） |
| ByteRTCLocalVideoStreamErrorFailure | 1 | 本地视频流发布失败 |
| ByteRTCLocalVideoStreamErrorDeviceNoPermission | 2 | 没有权限启动本地视频采集设备 |
| ByteRTCLocalVideoStreamErrorDeviceBusy | 3 | 本地视频采集设备已被占用 |
| ByteRTCLocalVideoStreamErrorDeviceNotFound | 4 | 本地视频采集设备不存在或已移除 |
| ByteRTCLocalVideoStreamErrorCaptureFailure | 5 | 本地视频采集失败，建议检查采集设备是否正常工作 |
| ByteRTCLocalVideoStreamErrorEncodeFailure | 6 | 本地视频编码失败 |
| ByteRTCLocalVideoStreamErrorDeviceDisconnected | 7 | 通话过程中本地视频采集设备被其他程序抢占，导致设备连接中断 |


# ByteRTCRemoteAudioState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioState)
```

用户订阅的远端音频流状态。  <br>
SDK 通过 `onRemoteAudioStateChanged` 回调该状态。  <br>


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRemoteAudioStateStopped | 0 | 远端音频流默认初始状态，在以下时机回调该状态：  <br><br/>+ 本地用户停止接收远端音频流，对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonLocalMuted`  <br><br/>+ 远端用户停止发送音频流，对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteMuted` <br><br/>+ 远端用户离开房间，对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteOffline` <br> |
| ByteRTCRemoteAudioStateStarting | 1 | 开始接收远端音频流首包。  <br><br/>刚收到远端音频流首包时，会触发回调 `onRemoteAudioStateChanged`，<br/>对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonLocalUnmuted` |
| ByteRTCRemoteAudioStateDecoding | 2 | 远端音频流正在解码，正常播放，在以下时机回调该状态：  <br><br/>+ 成功解码远端音频首帧，对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonLocalUnmuted` <br><br/>+ 网络由阻塞恢复正常，对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonNetworkRecovery` <br><br/>+ 本地用户恢复接收远端音频流，对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonLocalUnmuted` <br><br/>+ 远端用户恢复发送音频流，对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteUnmuted`<br> |
| ByteRTCRemoteAudioStateFrozen | 3 | 远端音频流卡顿。<br><br/>网络阻塞导致丢包率大于 40% 时，会触发回调 `onRemoteAudioStateChanged`，<br/>对应原因是 [ByteRTCRemoteAudioStateChangeReason](#bytertcremoteaudiostatechangereason) 中的 `ByteRTCRemoteAudioStateChangeReasonNetworkCongestion` |


# ByteRTCRemoteAudioStateChangeReason
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioStateChangeReason)
```

接收远端音频流状态改变的原因。<br>
用户可以通过 `onRemoteAudioStateChanged` 了解该状态。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRemoteAudioStateChangeReasonInternal | 0 | 内部原因 |
| ByteRTCRemoteAudioStateChangeReasonNetworkCongestion | 1 | 网络阻塞 |
| ByteRTCRemoteAudioStateChangeReasonNetworkRecovery | 2 | 网络恢复正常 |
| ByteRTCRemoteAudioStateChangeReasonLocalMuted | 3 | 本地用户停止接收远端音频流 |
| ByteRTCRemoteAudioStateChangeReasonLocalUnmuted | 4 | 本地用户恢复接收远端音频流 |
| ByteRTCRemoteAudioStateChangeReasonRemoteMuted | 5 | 远端用户停止发送音频流 |
| ByteRTCRemoteAudioStateChangeReasonRemoteUnmuted | 6 | 远端用户恢复发送音频流 |
| ByteRTCRemoteAudioStateChangeReasonRemoteOffline | 7 | 远端用户离开房间 |


# ByteRTCRemoteVideoState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoState)
```

远端视频流状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRemoteVideoStateStopped | 0 | 远端视频流默认初始状态, 在以下时机回调该状态：  <br><br/>+ 本地用户停止接收远端视频流，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonLocalMuted  <br><br/>+ 远端用户停止发送视频流，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonRemoteMuted <br><br/>+ 远端用户离开房间，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonRemoteOffline  <br> |
| ByteRTCRemoteVideoStateStarting | 1 | 本地用户已接收远端视频首包 <br><br/>收到远端视频首包时回调该状态，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted |
| ByteRTCRemoteVideoStateDecoding | 2 | 远端视频流正在解码，正常播放, 在以下时机回调该状态：  <br><br/>+ 成功解码远端视频首帧，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted  <br><br/>+ 网络由阻塞恢复正常，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonNetworkRecovery <br><br/>+ 本地用户恢复接收远端视频流，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted <br><br/>+ 远端用户恢复发送视频流，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonRemoteUnmuted  <br> |
| ByteRTCRemoteVideoStateFrozen | 3 | 远端视频流卡顿 <br><br/>网络阻塞、丢包率等原因造成视频卡顿流时会回报该状态，对应错误码 [ByteRTCRemoteVideoStateChangeReason](#bytertcremotevideostatechangereason) 中的 ByteRTCRemoteVideoStateChangeReasonNetworkCongestion |
| ByteRTCRemoteVideoStateFailed | 4 | 远端音频流播放失败 <br> |


# ByteRTCRemoteVideoStateChangeReason
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoStateChangeReason)
```

远端视频流状态改变的原因


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRemoteVideoStateChangeReasonInternal | 0 | 内部原因 |
| ByteRTCRemoteVideoStateChangeReasonNetworkCongestion | 1 | 网络阻塞 |
| ByteRTCRemoteVideoStateChangeReasonNetworkRecovery | 2 | 网络恢复正常 |
| ByteRTCRemoteVideoStateChangeReasonLocalMuted | 3 | 本地用户停止接收远端视频流或本地用户禁用视频模块 |
| ByteRTCRemoteVideoStateChangeReasonLocalUnmuted | 4 | 本地用户恢复接收远端视频流或本地用户启用视频模块 |
| ByteRTCRemoteVideoStateChangeReasonRemoteMuted | 5 | 远端用户停止发送视频流或远端用户禁用视频模块 |
| ByteRTCRemoteVideoStateChangeReasonRemoteUnmuted | 6 | 远端用户恢复发送视频流或远端用户启用视频模块 |
| ByteRTCRemoteVideoStateChangeReasonRemoteOffline | 7 | 远端用户离开房间 |


# ByteRTCMediaDeviceState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceState)
```

媒体设备状态<br>
通过 `rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:` 或 `rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:` 回调设备状态。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMediaDeviceStateStarted | 1 | 设备已开启 |
| ByteRTCMediaDeviceStateStopped | 2 | 设备已停止 |
| ByteRTCMediaDeviceStateRuntimeError | 3 | 设备运行时错误<br><br/>例如，当媒体设备的预期行为是正常采集，但没有收到采集数据时，将回调该状态。 |
| ByteRTCMediaDeviceStateAdded | 10 | 设备已插入 |
| ByteRTCMediaDeviceStateRemoved | 11 | 设备被移除 |
| ByteRTCMediaDeviceStateInterruptionBegan | 12 | 系统通话，锁屏或第三方应用打断了音视频通话。将在通话结束或第三方应用结束占用后自动恢复。 |
| ByteRTCMediaDeviceStateInterruptionEnded | 13 | 音视频通话已从系统电话或第三方应用打断中恢复 |


# ByteRTCMediaDeviceError
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceError)
```

媒体设备错误类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMediaDeviceErrorOK | 0 | 媒体设备正常 |
| ByteRTCMediaDeviceErrorDeviceNoPermission | 1 | 没有权限启动媒体设备 |
| ByteRTCMediaDeviceErrorDeviceBusy | 2 | 媒体设备已经在使用中 |
| ByteRTCMediaDeviceErrorDeviceFailure | 3 | 媒体设备错误 |
| ByteRTCMediaDeviceErrorDeviceNotFound | 4 | 未找到指定的媒体设备 |
| ByteRTCMediaDeviceErrorDeviceDisconnected | 5 | 媒体设备被移除 |
| ByteRTCMediaDeviceErrorDeviceNoCallback | 6 | 无采集数据。当媒体设备的预期行为是正常采集，但没有收到采集数据时，将收到该错误。 |
| ByteRTCMediaDeviceErrorUNSupportFormat | 7 | 设备采样率不支持 |
| ByteRTCMediaDeviceErrorNotFindGroupId | 8 | iOS 屏幕采集没有 group Id 参数 |


# ByteRTCMediaDeviceWarning
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceWarning)
```

媒体设备警告


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMediaDeviceWarningOK | 0 | 无警告 |
| ByteRTCMediaDeviceWarningOperationDenied | 1 | 非法设备操作。在使用外部设备时，调用了 SDK 内部设备 API。 |
| ByteRTCMediaDeviceWarningCaptureSilence | 2 | 采集到的数据为静音帧。 |
| ByteRTCMediaDeviceWarningSetAudioRouteInvalidScenario | 20 | 当前 AudioScenario 不支持更改音频路由，设置音频路由失败 |
| ByteRTCMediaDeviceWarningSetAudioRouteFailedByPriority | 22 | 音频路由被系统或其他应用占用，设置音频路由失败 |
| ByteRTCMediaDeviceWarningSetAudioRouteDeviceNotStart | 24 | 音频设备未启动，设置音频路由失败 |


# ByteRTCProblemFeedbackOption
```objectivec
typedef NS_OPTIONS(NSUInteger, ByteRTCProblemFeedbackOption)
```

音视频质量反馈问题类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCProblemFeedbackOptionNone | 0 | 没有问题 |
| ByteRTCProblemFeedbackOptionOtherMessage | (1 << 0) | 其他问题 |
| ByteRTCProblemFeedbackOptionAudioNotClear | (1 << 1) | 声音不清晰 |
| ByteRTCProblemFeedbackOptionVideoNotClear | (1 << 2) | 视频不清晰 |
| ByteRTCProblemFeedbackOptionNotSync | (1 << 3) | 音视频不同步 |
| ByteRTCProblemFeedbackOptionAudioLagging | (1 << 4) | 音频卡顿 |
| ByteRTCProblemFeedbackOptionVideoLagging | (1 << 5) | 视频卡顿 |
| ByteRTCProblemFeedbackOptionDisconnected | (1 << 6) | 连接断开 |
| ByteRTCProblemFeedbackOptionNoAudio | (1 << 7) | 无声音 |
| ByteRTCProblemFeedbackOptionNoVideo | (1 << 8) | 无画面 |
| ByteRTCProblemFeedbackOptionAudioStrength | (1 << 9) | 声音过小 |
| ByteRTCProblemFeedbackOptionEcho | (1 << 10) | 回声噪音 |
| ByteRTCFeedBackProblemTypeEarBackDelay | (1 << 11) | 耳返延迟大 |


# ByteRTCProblemOption
```objectivec
@interface ByteRTCProblemOption: NSObject
```

通话质量反馈预设问题列表


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCProblemFeedbackOption** | [option](#ByteRTCProblemOption-option) |
| **NSString*** | [desc](#ByteRTCProblemOption-desc) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **instancetype** | [initWithOption:](#ByteRTCProblemOption-initwithoption) |


## 变量说明
<span id="ByteRTCProblemOption-option"></span>
### option
```objectivec
@property(nonatomic, assign, readonly) ByteRTCProblemFeedbackOption option;
```
读取音视频质量反馈问题类型，参看 [ByteRTCProblemFeedbackOption](#bytertcproblemfeedbackoption)。


<span id="ByteRTCProblemOption-desc"></span>
### desc
```objectivec
@property(nonatomic, copy, readonly) NSString * _Nonnull desc;
```
读取 ByteRTCProblemOption 类对应的文字描述



## 函数说明
<span id="ByteRTCProblemOption-initwithoption"></span>
### initWithOption:
```objectivec

- (instancetype _Nonnull)initWithOption:(ByteRTCProblemFeedbackOption)option;
```
初始化 ByteRTCProblemOption


# ByteRTCFirstFrameSendState
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCFirstFrameSendState)
```

首帧发送状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCFirstFrameSendStateSending | 0 | 发送中 |
| ByteRTCFirstFrameSendStateSent | 1 | 发送成功 |
| ByteRTCFirstFrameSendStateEnd | 2 | 发送失败 |


# ByteRTCFirstFramePlayState
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCFirstFramePlayState)
```

首帧播放状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCFirstFramePlayStatePlaying | 0 | 播放中 |
| ByteRTCFirstFramePlayStatePlay | 1 | 播放成功 |
| ByteRTCFirstFramePlayStateEnd | 2 | 播放失败 |


# ByteRTCEncryptType
```objectivec
typedef NS_OPTIONS(NSUInteger, ByteRTCEncryptType)
```

自定义加密类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCEncryptTypeCustomize | 0 | 不使用内置加密。默认值。 |
| ByteRTCEncryptTypeAES128CBC | 1 | AES-128-CBC 加密算法 |
| ByteRTCEncryptTypeAES256CBC | 2 | AES-256-CBC 加密算法 |
| ByteRTCEncryptTypeAES128ECB | 3 | AES-128-ECB 加密算法 |
| ByteRTCEncryptTypeAES256ECB | 4 | AES-256-ECB 加密算法 |


# ByteRTCVideoCodecType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecType)
```

视频编码类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoCodecTypeUnknown | 0 | 未知类型 |
| ByteRTCVideoCodecTypeH264 | 1 | 标准 H264 编码格式 |
| ByteRTCVideoCodecTypeByteVC1 | 2 | ByteVC1 编码器 |


# ByteRTCMuteState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCMuteState)
```

音视频流的发送/播放状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMuteStateOff | 0 | 发送 |
| ByteRTCMuteStateOn | 1 | 停止发送 |


# ByteSEIStreamEventType
```objectivec
typedef NS_ENUM(NSInteger, ByteSEIStreamEventType)
```

黑帧视频流状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteSEIStreamEventTypeStreamAdd | 0 | 远端用户发布黑帧视频流。  <br><br/>纯语音通话场景下，远端用户调用 [sendSEIMessage:andMessage:andRepeatCount:](iOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount) 发送 SEI 数据时，SDK 会自动发布一路黑帧视频流，并触发该回调。 |
| ByteSEIStreamEventTypeStreamRemove | 1 | 远端黑帧视频流移除。该回调的触发时机包括：  <br><br/>+ 远端用户开启摄像头采集，由语音通话切换至视频通话，黑帧视频流停止发布；  <br><br/>+ 远端用户调用 [sendSEIMessage:andMessage:andRepeatCount:](iOS-api.md#ByteRTCVideo-sendseimessage-andmessage-andrepeatcount) 后 1min 内未有 SEI 数据发送，黑帧视频流停止发布；  <br><br/>+ 远端用户调用 [setVideoSourceType:WithStreamIndex:](iOS-api.md#ByteRTCVideo-setvideosourcetype-withstreamindex) 切换至自定义视频采集时，黑帧视频流停止发布。 |


# ByteRTCStreamIndex
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCStreamIndex)
```

流属性


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCStreamIndexMain | 0 | 主流。包括：<br><br/>+ 由摄像头/麦克风通过内部采集机制，采集到的视频/音频; <br><br/>+ 通过自定义采集，采集到的视频/音频。 |
| ByteRTCStreamIndexScreen | 1 | 屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。 |


# ByteRTCSyncInfoStreamType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCSyncInfoStreamType)
```

媒体流信息同步的流类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCSyncInfoStreamTypeAudio | 0 | 音频流 |


# ByteRTCForwardStreamState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamState)
```

媒体流跨房间转发状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCForwardStreamStateIdle | 0 | 空闲状态<br/>+ 成功调用 `stopForwardStreamToRooms` 后，所有目标房间为空闲状态。<br/>+ 成功调用 `updateForwardStreamToRooms` 减少目标房间后，本次减少的目标房间为空闲状态。 |
| ByteRTCForwardStreamStateSuccess | 1 | 开始转发<br/>+ 调用 `startForwardStreamToRooms` 成功向所有房间开始转发媒体流后，返回此状态。<br/>+ 调用 `updateForwardStreamToRooms` 后，成功向新增目标房间开始转发媒体流后，返回此状态。 |
| ByteRTCForwardStreamStateFailure | 2 | 转发失败，失败详情参考 [ByteRTCForwardStreamError](#bytertcforwardstreamerror)<br/>调用 `startForwardStreamToRooms` 或 `updateForwardStreamToRooms` 后，如遇转发失败，返回此状态。 |


# ByteRTCForwardStreamError
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamError)
```

媒体流跨房间转发过程中抛出的错误码


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCForwardStreamErrorOK | 0 | 正常 |
| ByteRTCForwardStreamErrorInvalidArgument | 1201 | 参数异常 |
| ByteRTCForwardStreamErrorInvalidToken | 1202 | Token 错误 |
| ByteRTCForwardStreamErrorResponse | 1203 | 服务端异常 |
| ByteRTCForwardStreamErrorRemoteKicked | 1204 | 目标房间有相同 user id 的用户加入，转发中断 |
| ByteRTCForwardStreamErrorNotSupport | 1205 | 服务端不支持转发功能 |


# ByteRTCForwardStreamEvent
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamEvent)
```

媒体流跨房间转发事件


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCForwardStreamEventDisconnected | 0 | 本端与服务器网络连接断开，暂停转发。 |
| ByteRTCForwardStreamEventConnected | 1 | 本端与服务器网络连接恢复，转发服务连接成功。 |
| ByteRTCForwardStreamEventInterrupt | 2 | 转发中断。转发过程中，如果相同 user_id 的用户进入目标房间，转发中断。 |
| ByteRTCForwardStreamEventDstRoomUpdated | 3 | 目标房间已更新，由 `updateForwardStreamToRooms` 触发。 |
| ByteRTCForwardStreamEventUnExpectAPICall | 4 | API 调用时序错误。例如，在调用 `startForwardStreamToRooms` 之前调用 `updateForwardStreamToRooms` 。 |


# ByteRTCRecordingState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRecordingState)
```

本地录制的状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| RecordingStateError | 0 | 录制异常 |
| RecordingStateProcessing | 1 | 录制进行中 |
| RecordingStateSuccess | 2 | 录制文件保存成功，调用 `stopFileRecording:` 结束录制之后才会收到该状态码。 |


# ByteRTCRecordingErrorCode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRecordingErrorCode)
```

本地录制错误码


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| RecordingErrorCodeOk | 0 | 录制正常 |
| RecordingErrorCodeNoPermission | -1 | 没有文件写权限 |
| RecordingErrorCodeNotSupport | -2 | 当前版本 SDK 不支持本地录制功能，请联系技术支持人员 |
| RecordingErrorCodeOther | -3 | 其他异常 |


# ByteRTCRecordingFileType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRecordingFileType)
```

本地录制文件的存储格式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| RecordingFileTypeAAC | 0 | aac 格式文件 |
| RecordingFileTypeMP4 | 1 | mp4 格式文件 |


# ByteRTCAVSyncState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCAVSyncState)
```

音视频同步状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| AVSyncStateAVStreamSyncBegin | 0 | 音视频开始同步 |
| AVSyncStateAudioStreamRemove | 1 | 音视频同步过程中音频移除，但不影响当前的同步关系 |
| AVSyncStateVdieoStreamRemove | 2 | 音视频同步过程中视频移除，但不影响当前的同步关系 |


# ByteRTCEchoTestResult
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCEchoTestResult)
```

音视频回路测试结果


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| EchoTestSuccess | 0 | 接收到采集的音视频的回放，通话回路检测成功 |
| EchoTestTimeout | 1 | 测试超过 60s 仍未完成，已自动停止 |
| EchoTestIntervalShort | 2 | 上一次测试结束和下一次测试开始之间的时间间隔少于 5s |
| EchoTestAudioDeviceError | 3 | 音频采集异常 |
| EchoTestVideoDeviceError | 4 | 视频采集异常 |
| EchoTestAudioReceiveError | 5 | 音频接收异常 |
| EchoTestVideoReceiveError | 6 | 视频接收异常 |
| EchoTestInternalError | 7 | 内部错误，不可恢复 |


# ByteRTCEchoTestConfig
```objectivec
@interface ByteRTCEchoTestConfig : NSObject
```

音视频回路测试参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCView*** | [view](#ByteRTCEchoTestConfig-view) |
| **NSString*** | [roomId](#ByteRTCEchoTestConfig-roomid) |
| **NSString*** | [userId](#ByteRTCEchoTestConfig-userid) |
| **NSString*** | [token](#ByteRTCEchoTestConfig-token) |
| **BOOL** | [enableAudio](#ByteRTCEchoTestConfig-enableaudio) |
| **BOOL** | [enableVideo](#ByteRTCEchoTestConfig-enablevideo) |
| **NSInteger** | [audioReportInterval](#ByteRTCEchoTestConfig-audioreportinterval) |


## 变量说明
<span id="ByteRTCEchoTestConfig-view"></span>
### view
```objectivec
@property(strong, nonatomic) ByteRTCView* _Nullable view;
```
用于渲染接收到的视频的视图


<span id="ByteRTCEchoTestConfig-roomid"></span>
### roomId
```objectivec
@property(copy, nonatomic) NSString *_Nonnull roomId;
```
测试用户加入的房间 ID。  <br>


<span id="ByteRTCEchoTestConfig-userid"></span>
### userId
```objectivec
@property(copy, nonatomic) NSString *_Nonnull userId;
```
进行音视频通话回路测试的用户 ID


<span id="ByteRTCEchoTestConfig-token"></span>
### token
```objectivec
@property(copy, nonatomic) NSString *_Nonnull token;
```
对用户进房时进行鉴权验证的动态密钥，用于保证音视频通话回路测试的安全性。


<span id="ByteRTCEchoTestConfig-enableaudio"></span>
### enableAudio
```objectivec
@property(assign, nonatomic) BOOL enableAudio;
```
是否检测音频。检测设备为系统默认音频设备。  <br>

+ true：是  <br>
- 若使用 SDK 内部采集，此时设备麦克风会自动开启，并在 audioReportInterval 值大于 0 时触发 `onLocalAudioPropertiesReport` 回调，你可以根据该回调判断麦克风的工作状态  <br>
- 若使用自定义采集，此时你需调用 [pushExternalAudioFrame:](iOS-api.md#ByteRTCVideo-pushexternalaudioframe) 将采集到的音频推送给 SDK  <br>
+ flase：否  <br>


<span id="ByteRTCEchoTestConfig-enablevideo"></span>
### enableVideo
```objectivec
@property(assign, nonatomic) BOOL enableVideo;
```
是否检测视频。PC 端默认检测列表中第一个视频设备。  <br>

+ true：是  <br>
- 若使用 SDK 内部采集，此时设备摄像头会自动开启  <br>
- If you choose custom capture, you also need to call [pushExternalVideoFrame:time:](iOS-api.md#ByteRTCVideo-pushexternalvideoframe-time) to push the captured video to the SDK.  <br>
+ false: No  <br>

**注意:**
The video is published with fixed parameters: resolution 640px × 360px, frame rate 15fps.
The video is published with fixed parameters: resolution 640px × 360px, frame rate 15fps.

<span id="ByteRTCEchoTestConfig-audioreportinterval"></span>
### audioReportInterval
```objectivec
@property(assign, nonatomic) NSInteger audioReportInterval;
```
音量信息提示间隔，单位：ms，默认为 100ms <br>

+ `<= 0`: 关闭信息提示  <br>
+ `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
+ `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>



# ByteRTCUserInfo
```objectivec
@interface ByteRTCUserInfo : NSObject
```

用户信息。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [userId](#ByteRTCUserInfo-userid) |
| **NSString*** | [extraInfo](#ByteRTCUserInfo-extrainfo) |


## 变量说明
<span id="ByteRTCUserInfo-userid"></span>
### userId
```objectivec
@property(copy, nonatomic) NSString *_Nonnull userId;
```
用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-]{1,128}`。


<span id="ByteRTCUserInfo-extrainfo"></span>
### extraInfo
```objectivec
@property(copy, nonatomic) NSString *_Nonnull extraInfo;
```
用户需要透传的额外的信息，字符长度限制为 200 字节。会在 `rtcEngine:onUserJoined:elapsed:` 中回调给远端用户。



# ByteRTCRoomStats
```objectivec
@interface ByteRTCRoomStats : NSObject
```

房间通话统计数据，统计周期为 2s 。  <br>
用户进房成功后，SDK 会周期性地通过 `onRoomStats` 回调通知用户当前房间内的汇总统计信息。此数据结构即为回调给用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [duration](#ByteRTCRoomStats-duration) |
| **NSInteger** | [txBytes](#ByteRTCRoomStats-txbytes) |
| **NSInteger** | [rxBytes](#ByteRTCRoomStats-rxbytes) |
| **NSInteger** | [txKbitrate](#ByteRTCRoomStats-txkbitrate) |
| **NSInteger** | [rxKbitrate](#ByteRTCRoomStats-rxkbitrate) |
| **NSInteger** | [txAudioKBitrate](#ByteRTCRoomStats-txaudiokbitrate) |
| **NSInteger** | [rxAudioKBitrate](#ByteRTCRoomStats-rxaudiokbitrate) |
| **NSInteger** | [txVideoKBitrate](#ByteRTCRoomStats-txvideokbitrate) |
| **NSInteger** | [rxVideoKBitrate](#ByteRTCRoomStats-rxvideokbitrate) |
| **NSInteger** | [txScreenKBitrate](#ByteRTCRoomStats-txscreenkbitrate) |
| **NSInteger** | [rxScreenKBitrate](#ByteRTCRoomStats-rxscreenkbitrate) |
| **NSInteger** | [userCount](#ByteRTCRoomStats-usercount) |
| **float** | [rxLostrate](#ByteRTCRoomStats-rxlostrate) |
| **float** | [txLostrate](#ByteRTCRoomStats-txlostrate) |
| **NSInteger** | [rtt](#ByteRTCRoomStats-rtt) |
| **NSInteger** | [txJitter](#ByteRTCRoomStats-txjitter) |
| **NSInteger** | [rxJitter](#ByteRTCRoomStats-rxjitter) |
| **NSInteger** | [tx_cellular_kbitrate](#ByteRTCRoomStats-tx_cellular_kbitrate) |
| **NSInteger** | [rx_cellular_kbitrate](#ByteRTCRoomStats-rx_cellular_kbitrate) |


## 变量说明
<span id="ByteRTCRoomStats-duration"></span>
### duration
```objectivec
@property(assign, nonatomic) NSInteger duration;
```
用户进房开始通话后的总时长，单位为 s ，累计值


<span id="ByteRTCRoomStats-txbytes"></span>
### txBytes
```objectivec
@property(assign, nonatomic) NSInteger txBytes;
```
本地用户的总发送字节数 (bytes)，累计值


<span id="ByteRTCRoomStats-rxbytes"></span>
### rxBytes
```objectivec
@property(assign, nonatomic) NSInteger rxBytes;
```
本地用户的总接收字节数 (bytes)，累计值


<span id="ByteRTCRoomStats-txkbitrate"></span>
### txKbitrate
```objectivec
@property(assign, nonatomic) NSInteger txKbitrate;
```
发送码率（kbps），获取该数据时的瞬时值


<span id="ByteRTCRoomStats-rxkbitrate"></span>
### rxKbitrate
```objectivec
@property(assign, nonatomic) NSInteger rxKbitrate;
```
接收码率（kbps），获取该数据时的瞬时值


<span id="ByteRTCRoomStats-txaudiokbitrate"></span>
### txAudioKBitrate
```objectivec
@property(assign, nonatomic) NSInteger txAudioKBitrate;
```
本地用户的音频发送码率 (kbps)，瞬时值


<span id="ByteRTCRoomStats-rxaudiokbitrate"></span>
### rxAudioKBitrate
```objectivec
@property(assign, nonatomic) NSInteger rxAudioKBitrate;
```
本地用户的音频接收码率 (kbps)，瞬时值


<span id="ByteRTCRoomStats-txvideokbitrate"></span>
### txVideoKBitrate
```objectivec
@property(assign, nonatomic) NSInteger txVideoKBitrate;
```
本地用户的视频发送码率 (kbps)，瞬时值


<span id="ByteRTCRoomStats-rxvideokbitrate"></span>
### rxVideoKBitrate
```objectivec
@property(assign, nonatomic) NSInteger rxVideoKBitrate;
```
本地用户的视频接收码率 (kbps)，瞬时值


<span id="ByteRTCRoomStats-txscreenkbitrate"></span>
### txScreenKBitrate
```objectivec
@property(assign, nonatomic) NSInteger txScreenKBitrate;
```
屏幕接收码率，获取该数据时的瞬时值，单位为 Kbps


<span id="ByteRTCRoomStats-rxscreenkbitrate"></span>
### rxScreenKBitrate
```objectivec
@property(assign, nonatomic) NSInteger rxScreenKBitrate;
```
屏幕发送码率，获取该数据时的瞬时值，单位为 Kbps


<span id="ByteRTCRoomStats-usercount"></span>
### userCount
```objectivec
@property(assign, nonatomic) NSInteger userCount;
```
当前房间内的可见用户人数，包括本地用户自身


<span id="ByteRTCRoomStats-rxlostrate"></span>
### rxLostrate
```objectivec
@property(assign, nonatomic) float rxLostrate;
```
App 现在的下行丢包率


<span id="ByteRTCRoomStats-txlostrate"></span>
### txLostrate
```objectivec
@property(assign, nonatomic) float txLostrate;
```
App 现在的上行丢包率


<span id="ByteRTCRoomStats-rtt"></span>
### rtt
```objectivec
@property(assign, nonatomic) NSInteger rtt;
```
客户端到服务端的往返时延


<span id="ByteRTCRoomStats-txjitter"></span>
### txJitter
```objectivec
@property(assign, nonatomic) NSInteger txJitter;
```
系统上行网络抖动（ms）


<span id="ByteRTCRoomStats-rxjitter"></span>
### rxJitter
```objectivec
@property(assign, nonatomic) NSInteger rxJitter;
```
系统下行网络抖动（ms）


<span id="ByteRTCRoomStats-tx_cellular_kbitrate"></span>
### tx_cellular_kbitrate
```objectivec
@property(assign, nonatomic) NSInteger tx_cellular_kbitrate;
```
蜂窝路径发送的码率 (kbps)，为获取该数据时的瞬时值


<span id="ByteRTCRoomStats-rx_cellular_kbitrate"></span>
### rx_cellular_kbitrate
```objectivec
@property(assign, nonatomic) NSInteger rx_cellular_kbitrate;
```
蜂窝路径接收码率 (kbps)，为获取该数据时的瞬时值



# ByteRTCSysStats
```objectivec
@interface ByteRTCSysStats : NSObject
```

App 使用的 cpu 和 memory 信息  <br>
信息由 SDK 周期性（2s）地通过 `reportSysStats` 回调事件通知给用户。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **unsigned** | [cpu_cores](#ByteRTCSysStats-cpu_cores) |
| **double** | [cpu_app_usage](#ByteRTCSysStats-cpu_app_usage) |
| **double** | [cpu_total_usage](#ByteRTCSysStats-cpu_total_usage) |
| **double** | [memory_usage](#ByteRTCSysStats-memory_usage) |
| **unsigned** | [full_memory](#ByteRTCSysStats-full_memory) |
| **unsigned** | [total_memory_usage](#ByteRTCSysStats-total_memory_usage) |
| **unsigned** | [free_memory](#ByteRTCSysStats-free_memory) |
| **double** | [memory_ratio](#ByteRTCSysStats-memory_ratio) |
| **double** | [total_memory_ratio](#ByteRTCSysStats-total_memory_ratio) |


## 变量说明
<span id="ByteRTCSysStats-cpu_cores"></span>
### cpu_cores
```objectivec
@property(assign, nonatomic) unsigned int cpu_cores;
```
当前系统 cpu 核数


<span id="ByteRTCSysStats-cpu_app_usage"></span>
### cpu_app_usage
```objectivec
@property(assign, nonatomic) double cpu_app_usage;
```
当前应用的 CPU 使用率，取值范围为 [0, 1]。


<span id="ByteRTCSysStats-cpu_total_usage"></span>
### cpu_total_usage
```objectivec
@property(assign, nonatomic) double cpu_total_usage;
```
当前系统的 CPU 使用率，取值范围为 [0, 1]。


<span id="ByteRTCSysStats-memory_usage"></span>
### memory_usage
```objectivec
@property(assign, nonatomic) double memory_usage;
```
当前App的内存使用（单位 MB）


<span id="ByteRTCSysStats-full_memory"></span>
### full_memory
```objectivec
@property(assign, nonatomic) unsigned long long full_memory;
```
全量内存（单位MB）


<span id="ByteRTCSysStats-total_memory_usage"></span>
### total_memory_usage
```objectivec
@property(assign, nonatomic) unsigned long long total_memory_usage;
```
系统已使用内存（单位MB）


<span id="ByteRTCSysStats-free_memory"></span>
### free_memory
```objectivec
@property(assign, nonatomic) unsigned long long free_memory;
```
空闲可分配内存（单位MB）


<span id="ByteRTCSysStats-memory_ratio"></span>
### memory_ratio
```objectivec
@property(assign, nonatomic) double memory_ratio;
```
当前应用的内存使用率（单位 %）


<span id="ByteRTCSysStats-total_memory_ratio"></span>
### total_memory_ratio
```objectivec
@property(assign, nonatomic) double total_memory_ratio;
```
系统内存使用率（单位 %）



# ByteRTCLocalVideoStats
```objectivec
@interface ByteRTCLocalVideoStats : NSObject
```

本地视频流统计信息，统计周期为 2s 。  <br>
本地用户发布视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
通知本地用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [sentKBitrate](#ByteRTCLocalVideoStats-sentkbitrate) |
| **NSInteger** | [inputFrameRate](#ByteRTCLocalVideoStats-inputframerate) |
| **NSInteger** | [sentFrameRate](#ByteRTCLocalVideoStats-sentframerate) |
| **NSInteger** | [encoderOutputFrameRate](#ByteRTCLocalVideoStats-encoderoutputframerate) |
| **NSInteger** | [rendererOutputFrameRate](#ByteRTCLocalVideoStats-rendereroutputframerate) |
| **NSInteger** | [statsInterval](#ByteRTCLocalVideoStats-statsinterval) |
| **float** | [videoLossRate](#ByteRTCLocalVideoStats-videolossrate) |
| **NSInteger** | [rtt](#ByteRTCLocalVideoStats-rtt) |
| **NSInteger** | [encodedBitrate](#ByteRTCLocalVideoStats-encodedbitrate) |
| **NSInteger** | [encodedFrameWidth](#ByteRTCLocalVideoStats-encodedframewidth) |
| **NSInteger** | [encodedFrameHeight](#ByteRTCLocalVideoStats-encodedframeheight) |
| **NSInteger** | [encodedFrameCount](#ByteRTCLocalVideoStats-encodedframecount) |
| **ByteRTCVideoCodecType** | [codecType](#ByteRTCLocalVideoStats-codectype-2) |
| **BOOL** | [isScreen](#ByteRTCLocalVideoStats-isscreen) |
| **NSInteger** | [jitter](#ByteRTCLocalVideoStats-jitter) |


## 变量说明
<span id="ByteRTCLocalVideoStats-sentkbitrate"></span>
### sentKBitrate
```objectivec
@property(assign, nonatomic) float sentKBitrate;
```
发送码率。此次统计周期内实际发送的分辨率最大的视频流的发送码率，单位为 Kbps


<span id="ByteRTCLocalVideoStats-inputframerate"></span>
### inputFrameRate
```objectivec
@property(assign, nonatomic) NSInteger inputFrameRate;
```
采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。


<span id="ByteRTCLocalVideoStats-sentframerate"></span>
### sentFrameRate
```objectivec
@property(assign, nonatomic) NSInteger sentFrameRate;
```
发送帧率。此次统计周期内实际发送的分辨率最大的视频流的视频发送帧率，单位为 fps 。


<span id="ByteRTCLocalVideoStats-encoderoutputframerate"></span>
### encoderOutputFrameRate
```objectivec
@property(assign, nonatomic) NSInteger encoderOutputFrameRate;
```
编码器输出帧率。当前编码器在此次统计周期内实际发送的分辨率最大的视频流的输出帧率，单位为 fps 。


<span id="ByteRTCLocalVideoStats-rendereroutputframerate"></span>
### rendererOutputFrameRate
```objectivec
@property(assign, nonatomic) NSInteger rendererOutputFrameRate;
```
本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。


<span id="ByteRTCLocalVideoStats-statsinterval"></span>
### statsInterval
```objectivec
@property(assign, nonatomic) NSInteger statsInterval;
```
统计间隔，单位为 ms 。
此字段用于设置回调的统计周期，默认设置为 2s 。


<span id="ByteRTCLocalVideoStats-videolossrate"></span>
### videoLossRate
```objectivec
@property(assign, nonatomic) float videoLossRate;
```
视频丢包率。统计周期内的视频上行丢包率，取值范围为 [0, 1] 。  <br>


<span id="ByteRTCLocalVideoStats-rtt"></span>
### rtt
```objectivec
@property(assign, nonatomic) NSInteger rtt;
```
往返时延。单位为 ms 。  <br>


<span id="ByteRTCLocalVideoStats-encodedbitrate"></span>
### encodedBitrate
```objectivec
@property(assign, nonatomic) NSInteger encodedBitrate;
```
视频编码码率。此次统计周期内的实际发送的分辨率最大的视频流视频编码码率，单位为 Kbps 。


<span id="ByteRTCLocalVideoStats-encodedframewidth"></span>
### encodedFrameWidth
```objectivec
@property(assign, nonatomic) NSInteger encodedFrameWidth;
```
实际发送的分辨率最大的视频流的视频编码宽度，单位为 px 。


<span id="ByteRTCLocalVideoStats-encodedframeheight"></span>
### encodedFrameHeight
```objectivec
@property(assign, nonatomic) NSInteger encodedFrameHeight;
```
实际发送的分辨率最大的视频流的视频编码高度，单位为 px 。


<span id="ByteRTCLocalVideoStats-encodedframecount"></span>
### encodedFrameCount
```objectivec
@property(assign, nonatomic) NSInteger encodedFrameCount;
```
此次统计周期内实际发送的分辨率最大的视频流的发送的视频帧总数。


<span id="ByteRTCLocalVideoStats-codectype"></span>
### codecType
```objectivec
@property(nonatomic) ByteRTCVideoCodecType codecType;
```
编码类型。参看 [ByteRTCVideoCodecType](#bytertcvideocodectype) 类型。  <br>


<span id="ByteRTCLocalVideoStats-isscreen"></span>
### isScreen
```objectivec
@property(assign, nonatomic) BOOL isScreen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


<span id="ByteRTCLocalVideoStats-jitter"></span>
### jitter
```objectivec
@property(assign, nonatomic) NSInteger jitter;
```
视频上行网络抖动，单位为 ms。  <br>



# ByteRTCRemoteVideoStats
```objectivec
@interface ByteRTCRemoteVideoStats : NSObject
```

远端视频流统计信息，统计周期为 2s 。  <br>
本地用户订阅远端视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [width](#ByteRTCRemoteVideoStats-width) |
| **NSInteger** | [height](#ByteRTCRemoteVideoStats-height) |
| **float** | [videoLossRate](#ByteRTCRemoteVideoStats-videolossrate) |
| **float** | [receivedKBitrate](#ByteRTCRemoteVideoStats-receivedkbitrate) |
| **NSInteger** | [receivedFrameRate](#ByteRTCRemoteVideoStats-receivedframerate) |
| **NSInteger** | [decoderOutputFrameRate](#ByteRTCRemoteVideoStats-decoderoutputframerate) |
| **NSInteger** | [renderOutputFrameRate](#ByteRTCRemoteVideoStats-renderoutputframerate) |
| **NSInteger** | [stallCount](#ByteRTCRemoteVideoStats-stallcount) |
| **NSInteger** | [stallDuration](#ByteRTCRemoteVideoStats-stallduration) |
| **NSInteger** | [e2eDelay](#ByteRTCRemoteVideoStats-e2edelay) |
| **BOOL** | [isScreen](#ByteRTCRemoteVideoStats-isscreen) |
| **NSInteger** | [statsInterval](#ByteRTCRemoteVideoStats-statsinterval) |
| **NSInteger** | [rtt](#ByteRTCRemoteVideoStats-rtt) |
| **NSInteger** | [frozenRate](#ByteRTCRemoteVideoStats-frozenrate) |
| **ByteRTCVideoCodecType** | [codecType](#ByteRTCRemoteVideoStats-codectype) |
| **NSInteger** | [videoIndex](#ByteRTCRemoteVideoStats-videoindex) |
| **NSInteger** | [jitter](#ByteRTCRemoteVideoStats-jitter) |


## 变量说明
<span id="ByteRTCRemoteVideoStats-width"></span>
### width
```objectivec
@property(assign, nonatomic) NSInteger width;
```
远端视频宽度。  <br>


<span id="ByteRTCRemoteVideoStats-height"></span>
### height
```objectivec
@property(assign, nonatomic) NSInteger height;
```
远端视频高度。  <br>


<span id="ByteRTCRemoteVideoStats-videolossrate"></span>
### videoLossRate
```objectivec
@property(assign, nonatomic) float videoLossRate;
```
远端视频丢包率。统计周期内的视频下行丢包率，取值范围为 [0, 1] 。  <br>


<span id="ByteRTCRemoteVideoStats-receivedkbitrate"></span>
### receivedKBitrate
```objectivec
@property(assign, nonatomic) float receivedKBitrate;
```
接收码率。统计周期内的视频接收码率，单位为 kbps 。  <br>


<span id="ByteRTCRemoteVideoStats-receivedframerate"></span>
### receivedFrameRate
```objectivec
@property(assign, nonatomic) NSInteger receivedFrameRate;
```
远端视频接收帧率。  <br>


<span id="ByteRTCRemoteVideoStats-decoderoutputframerate"></span>
### decoderOutputFrameRate
```objectivec
@property(assign, nonatomic) NSInteger decoderOutputFrameRate;
```
远端视频解码输出帧率。  <br>


<span id="ByteRTCRemoteVideoStats-renderoutputframerate"></span>
### renderOutputFrameRate
```objectivec
@property(assign, nonatomic) NSInteger renderOutputFrameRate;
```
远端视频渲染输出帧率。  <br>


<span id="ByteRTCRemoteVideoStats-stallcount"></span>
### stallCount
```objectivec
@property(assign, nonatomic) NSInteger stallCount;
```
远端视频卡顿次数。  <br>


<span id="ByteRTCRemoteVideoStats-stallduration"></span>
### stallDuration
```objectivec
@property(assign, nonatomic) NSInteger stallDuration;
```
远端视频卡顿时长，单位为 ms 。  <br>


<span id="ByteRTCRemoteVideoStats-e2edelay"></span>
### e2eDelay
```objectivec
@property(assign, nonatomic) NSInteger e2eDelay;
```
用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>


<span id="ByteRTCRemoteVideoStats-isscreen"></span>
### isScreen
```objectivec
@property(assign, nonatomic) BOOL isScreen;
```
远端视频流是否是屏幕共享流。你可以知道当前数据来自主流还是屏幕流。


<span id="ByteRTCRemoteVideoStats-statsinterval"></span>
### statsInterval
```objectivec
@property(assign, nonatomic) NSInteger statsInterval;
```
统计间隔，此次统计周期的间隔，单位为 ms 。  <br>
此字段用于设置回调的统计周期，目前设置为 2s 。


<span id="ByteRTCRemoteVideoStats-rtt"></span>
### rtt
```objectivec
@property(assign, nonatomic) NSInteger rtt;
```
往返时延。单位为 ms 。  <br>


<span id="ByteRTCRemoteVideoStats-frozenrate"></span>
### frozenRate
```objectivec
@property(assign, nonatomic) NSInteger frozenRate;
```
远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。


<span id="ByteRTCRemoteVideoStats-codectype"></span>
### codecType
```objectivec
@property(nonatomic) ByteRTCVideoCodecType codecType;
```
编码类型。参看 [ByteRTCVideoCodecType](#bytertcvideocodectype) 类型。


<span id="ByteRTCRemoteVideoStats-videoindex"></span>
### videoIndex
```objectivec
@property(assign, nonatomic) NSInteger videoIndex;
```
SDK 订阅的远端视频流的分辨率下标。  <br>


<span id="ByteRTCRemoteVideoStats-jitter"></span>
### jitter
```objectivec
@property(assign, nonatomic) NSInteger jitter;
```
视频下行网络抖动，单位为 ms。  <br>



# ByteRTCLocalAudioStats
```objectivec
@interface ByteRTCLocalAudioStats : NSObject
```

本地音频流统计信息，统计周期为 2s 。  <br>
本地用户发布音频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
通知本地用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [audioLossRate](#ByteRTCLocalAudioStats-audiolossrate) |
| **float** | [sentKBitrate](#ByteRTCLocalAudioStats-sentkbitrate) |
| **NSInteger** | [recordSampleRate](#ByteRTCLocalAudioStats-recordsamplerate) |
| **NSInteger** | [statsInterval](#ByteRTCLocalAudioStats-statsinterval) |
| **NSInteger** | [rtt](#ByteRTCLocalAudioStats-rtt) |
| **NSInteger** | [numChannels](#ByteRTCLocalAudioStats-numchannels) |
| **NSInteger** | [sentSampleRate](#ByteRTCLocalAudioStats-sentsamplerate) |
| **NSInteger** | [jitter](#ByteRTCLocalAudioStats-jitter) |


## 变量说明
<span id="ByteRTCLocalAudioStats-audiolossrate"></span>
### audioLossRate
```objectivec
@property(assign, nonatomic) float audioLossRate;
```
音频丢包率。此次统计周期内的音频上行丢包率，取值范围为 [0, 1] 。  <br>


<span id="ByteRTCLocalAudioStats-sentkbitrate"></span>
### sentKBitrate
```objectivec
@property(assign, nonatomic) float sentKBitrate;
```
发送的码率。此次统计周期内的音频发送码率，单位为 kbps 。  <br>


<span id="ByteRTCLocalAudioStats-recordsamplerate"></span>
### recordSampleRate
```objectivec
@property(assign, nonatomic) NSInteger recordSampleRate;
```
采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  <br>


<span id="ByteRTCLocalAudioStats-statsinterval"></span>
### statsInterval
```objectivec
@property(assign, nonatomic) NSInteger statsInterval;
```
统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
此字段用于设置回调的统计周期，默认设置为 2s 。


<span id="ByteRTCLocalAudioStats-rtt"></span>
### rtt
```objectivec
@property(assign, nonatomic) NSInteger rtt;
```
往返时延。单位为 ms 。  <br>


<span id="ByteRTCLocalAudioStats-numchannels"></span>
### numChannels
```objectivec
@property(assign, nonatomic) NSInteger numChannels;
```
音频声道数。  <br>


<span id="ByteRTCLocalAudioStats-sentsamplerate"></span>
### sentSampleRate
```objectivec
@property(assign, nonatomic) NSInteger sentSampleRate;
```
音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。  <br>


<span id="ByteRTCLocalAudioStats-jitter"></span>
### jitter
```objectivec
@property(assign, nonatomic) NSInteger jitter;
```
音频上行网络抖动，单位为 ms。  <br>



# ByteRTCRemoteAudioStats
```objectivec
@interface ByteRTCRemoteAudioStats : NSObject
```

远端音频流统计信息，统计周期为 2s 。  <br>
本地用户订阅远端音频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [audioLossRate](#ByteRTCRemoteAudioStats-audiolossrate) |
| **float** | [receivedKBitrate](#ByteRTCRemoteAudioStats-receivedkbitrate) |
| **NSInteger** | [stallCount](#ByteRTCRemoteAudioStats-stallcount) |
| **NSInteger** | [stallDuration](#ByteRTCRemoteAudioStats-stallduration) |
| **NSInteger** | [playoutSampleRate](#ByteRTCRemoteAudioStats-playoutsamplerate) |
| **NSInteger** | [e2eDelay](#ByteRTCRemoteAudioStats-e2edelay) |
| **NSInteger** | [statsInterval](#ByteRTCRemoteAudioStats-statsinterval) |
| **NSInteger** | [rtt](#ByteRTCRemoteAudioStats-rtt) |
| **NSInteger** | [total_rtt](#ByteRTCRemoteAudioStats-total_rtt) |
| **NSInteger** | [quality](#ByteRTCRemoteAudioStats-quality) |
| **NSInteger** | [jitterBufferDelay](#ByteRTCRemoteAudioStats-jitterbufferdelay) |
| **NSInteger** | [numChannels](#ByteRTCRemoteAudioStats-numchannels) |
| **NSInteger** | [receivedSampleRate](#ByteRTCRemoteAudioStats-receivedsamplerate) |
| **NSInteger** | [frozenRate](#ByteRTCRemoteAudioStats-frozenrate) |
| **NSInteger** | [concealedSamples](#ByteRTCRemoteAudioStats-concealedsamples) |
| **NSInteger** | [concealmentEvent](#ByteRTCRemoteAudioStats-concealmentevent) |
| **NSInteger** | [decSampleRate](#ByteRTCRemoteAudioStats-decsamplerate) |
| **NSInteger** | [decDuration](#ByteRTCRemoteAudioStats-decduration) |
| **NSInteger** | [jitter](#ByteRTCRemoteAudioStats-jitter) |


## 变量说明
<span id="ByteRTCRemoteAudioStats-audiolossrate"></span>
### audioLossRate
```objectivec
@property(assign, nonatomic) float audioLossRate;
```
音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  <br>


<span id="ByteRTCRemoteAudioStats-receivedkbitrate"></span>
### receivedKBitrate
```objectivec
@property(assign, nonatomic) float receivedKBitrate;
```
接收码率。统计周期内的音频接收码率，单位为 kbps 。  <br>


<span id="ByteRTCRemoteAudioStats-stallcount"></span>
### stallCount
```objectivec
@property(assign, nonatomic) NSInteger stallCount;
```
音频卡顿次数。统计周期内的卡顿次数。  <br>


<span id="ByteRTCRemoteAudioStats-stallduration"></span>
### stallDuration
```objectivec
@property(assign, nonatomic) NSInteger stallDuration;
```
音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  <br>


<span id="ByteRTCRemoteAudioStats-playoutsamplerate"></span>
### playoutSampleRate
```objectivec
@property(assign, nonatomic) NSInteger playoutSampleRate;
```
播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  <br>


<span id="ByteRTCRemoteAudioStats-e2edelay"></span>
### e2eDelay
```objectivec
@property(assign, nonatomic) NSInteger e2eDelay;
```
用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>


<span id="ByteRTCRemoteAudioStats-statsinterval"></span>
### statsInterval
```objectivec
@property(assign, nonatomic) NSInteger statsInterval;
```
统计间隔。此次统计周期的间隔，单位为 ms 。  <br>


<span id="ByteRTCRemoteAudioStats-rtt"></span>
### rtt
```objectivec
@property(assign, nonatomic) NSInteger rtt;
```
客户端到服务端数据传输的往返时延，单位为 ms。  <br>


<span id="ByteRTCRemoteAudioStats-total_rtt"></span>
### total_rtt
```objectivec
@property(assign, nonatomic) NSInteger total_rtt;
```
发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  <br>


<span id="ByteRTCRemoteAudioStats-quality"></span>
### quality
```objectivec
@property(assign, nonatomic) NSInteger quality;
```
远端用户发送的音频流质量。值含义参考 [ByteRTCNetworkQuality](#bytertcnetworkquality) 。  <br>


<span id="ByteRTCRemoteAudioStats-jitterbufferdelay"></span>
### jitterBufferDelay
```objectivec
@property(assign, nonatomic) NSInteger jitterBufferDelay;
```
因引入 jitter buffer 机制导致的延时。单位为 ms 。  <br>


<span id="ByteRTCRemoteAudioStats-numchannels"></span>
### numChannels
```objectivec
@property(assign, nonatomic) NSInteger numChannels;
```
音频声道数。  <br>


<span id="ByteRTCRemoteAudioStats-receivedsamplerate"></span>
### receivedSampleRate
```objectivec
@property(assign, nonatomic) NSInteger receivedSampleRate;
```
音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  <br>


<span id="ByteRTCRemoteAudioStats-frozenrate"></span>
### frozenRate
```objectivec
@property(assign, nonatomic) NSInteger frozenRate;
```
远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。


<span id="ByteRTCRemoteAudioStats-concealedsamples"></span>
### concealedSamples
```objectivec
@property(assign, nonatomic) NSInteger concealedSamples;
```
音频 PLC 样点总个数。  <br>


<span id="ByteRTCRemoteAudioStats-concealmentevent"></span>
### concealmentEvent
```objectivec
@property(assign, nonatomic) NSInteger concealmentEvent;
```
音频丢包补偿(PLC) 累计次数。  <br>


<span id="ByteRTCRemoteAudioStats-decsamplerate"></span>
### decSampleRate
```objectivec
@property(assign, nonatomic) NSInteger decSampleRate;
```
音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  <br>


<span id="ByteRTCRemoteAudioStats-decduration"></span>
### decDuration
```objectivec
@property(assign, nonatomic) NSInteger decDuration;
```
此次订阅中，对远端音频流进行解码的累计耗时。单位为 s。


<span id="ByteRTCRemoteAudioStats-jitter"></span>
### jitter
```objectivec
@property(assign, nonatomic) NSInteger jitter;
```
视频下行网络抖动，单位为 ms。  <br>



# ByteRTCLocalStreamStats
```objectivec
@interface ByteRTCLocalStreamStats : NSObject
```

本地音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
本地用户发布音/视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
通知本地用户发布的音/视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCLocalAudioStats*** | [audio_stats](#ByteRTCLocalStreamStats-audio_stats) |
| **ByteRTCLocalVideoStats*** | [video_stats](#ByteRTCLocalStreamStats-video_stats) |
| **BOOL** | [is_screen](#ByteRTCLocalStreamStats-is_screen) |


## 变量说明
<span id="ByteRTCLocalStreamStats-audio_stats"></span>
### audio_stats
```objectivec
@property(strong, nonatomic) ByteRTCLocalAudioStats *_Nonnull audio_stats;
```
本地设备发送音频流的统计信息，详见 [ByteRTCLocalAudioStats](#bytertclocalaudiostats)


<span id="ByteRTCLocalStreamStats-video_stats"></span>
### video_stats
```objectivec
@property(strong, nonatomic) ByteRTCLocalVideoStats *_Nonnull video_stats;
```
本地设备发送视频流的统计信息，详见 [ByteRTCLocalVideoStats](#bytertclocalvideostats)


<span id="ByteRTCLocalStreamStats-is_screen"></span>
### is_screen
```objectivec
@property(nonatomic, assign) BOOL is_screen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。



# ByteRTCRemoteStreamStats
```objectivec
@interface ByteRTCRemoteStreamStats : NSObject
```

用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [uid](#ByteRTCRemoteStreamStats-uid) |
| **ByteRTCRemoteAudioStats*** | [audio_stats](#ByteRTCRemoteStreamStats-audio_stats) |
| **ByteRTCRemoteVideoStats*** | [video_stats](#ByteRTCRemoteStreamStats-video_stats) |
| **BOOL** | [is_screen](#ByteRTCRemoteStreamStats-is_screen) |


## 变量说明
<span id="ByteRTCRemoteStreamStats-uid"></span>
### uid
```objectivec
@property(copy, nonatomic) NSString *_Nonnull uid;
```
用户 ID 。音频来源的用户 ID 。  <br>


<span id="ByteRTCRemoteStreamStats-audio_stats"></span>
### audio_stats
```objectivec
@property(strong, nonatomic) ByteRTCRemoteAudioStats *_Nonnull audio_stats;
```
远端音频流的统计信息，详见 [ByteRTCRemoteAudioStats](#bytertcremoteaudiostats)


<span id="ByteRTCRemoteStreamStats-video_stats"></span>
### video_stats
```objectivec
@property(strong, nonatomic) ByteRTCRemoteVideoStats *_Nonnull video_stats;
```
远端视频流的统计信息，详见 [ByteRTCRemoteVideoStats](#bytertcremotevideostats)


<span id="ByteRTCRemoteStreamStats-is_screen"></span>
### is_screen
```objectivec
@property(nonatomic, assign) BOOL is_screen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。



# ByteRTCUser
```objectivec
@interface ByteRTCUser : NSObject
```

用户信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [userId](#ByteRTCUser-userid) |
| **NSString*** | [metaData](#ByteRTCUser-metadata) |


## 变量说明
<span id="ByteRTCUser-userid"></span>
### userId
```objectivec
@property(nonatomic, copy, nullable) NSString *userId;
```
用户 ID


<span id="ByteRTCUser-metadata"></span>
### metaData
```objectivec
@property(nonatomic, copy, nullable) NSString *metaData;
```
元信息



# ByteRTCRemoteStreamKey
```objectivec
@interface ByteRTCRemoteStreamKey : NSObject
```

用户信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [userId](#ByteRTCRemoteStreamKey-userid) |
| **NSString*** | [roomId](#ByteRTCRemoteStreamKey-roomid) |
| **ByteRTCStreamIndex** | [streamIndex](#ByteRTCRemoteStreamKey-streamindex) |


## 变量说明
<span id="ByteRTCRemoteStreamKey-userid"></span>
### userId
```objectivec
@property(nonatomic, copy, nullable) NSString *userId;
```
用户 ID


<span id="ByteRTCRemoteStreamKey-roomid"></span>
### roomId
```objectivec
@property(nonatomic, copy, nullable) NSString *roomId;
```
房间 ID


<span id="ByteRTCRemoteStreamKey-streamindex"></span>
### streamIndex
```objectivec
@property(nonatomic, assign) ByteRTCStreamIndex streamIndex;
```
流属性，包括主流、屏幕流。参看 [ByteRTCStreamIndex](#bytertcstreamindex)



# ByteRTCRecordingConfig
```objectivec
@interface ByteRTCRecordingConfig : NSObject
```

本地录制参数配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [dirPath](#ByteRTCRecordingConfig-dirpath) |
| **ByteRTCRecordingFileType** | [recordingFileType](#ByteRTCRecordingConfig-recordingfiletype) |


## 变量说明
<span id="ByteRTCRecordingConfig-dirpath"></span>
### dirPath
```objectivec
@property(strong, nonatomic) NSString* _Nullable dirPath;
```
录制文件保存的绝对路径，需精确到文件夹，文件名由 RTC 自动生成。你需要确保对该路径具有读写权限。


<span id="ByteRTCRecordingConfig-recordingfiletype"></span>
### recordingFileType
```objectivec
@property(assign, nonatomic) ByteRTCRecordingFileType recordingFileType;
```
录制存储文件格式，参看 [ByteRTCRecordingFileType](#bytertcrecordingfiletype)



# ByteRTCRecordingProgress
```objectivec
@interface ByteRTCRecordingProgress : NSObject
```

本地录制进度


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **unsigned** | [duration](#ByteRTCRecordingProgress-duration) |
| **unsigned** | [fileSize](#ByteRTCRecordingProgress-filesize) |


## 变量说明
<span id="ByteRTCRecordingProgress-duration"></span>
### duration
```objectivec
@property(assign, nonatomic) unsigned long long duration;
```
当前文件的累计录制时长，单位：毫秒


<span id="ByteRTCRecordingProgress-filesize"></span>
### fileSize
```objectivec
@property(assign, nonatomic) unsigned long long fileSize;
```
当前录制文件的大小，单位：byte



# ByteRTCRecordingInfo
```objectivec
@interface ByteRTCRecordingInfo : NSObject
```

本地录制的详细信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [filePath](#ByteRTCRecordingInfo-filepath) |
| **ByteRTCVideoCodecType** | [codecType](#ByteRTCRecordingInfo-codectype) |
| **NSInteger** | [width](#ByteRTCRecordingInfo-width) |
| **NSInteger** | [height](#ByteRTCRecordingInfo-height) |


## 变量说明
<span id="ByteRTCRecordingInfo-filepath"></span>
### filePath
```objectivec
@property(strong, nonatomic) NSString* _Nullable filePath;
```
录制文件的绝对路径，包含文件名和文件后缀


<span id="ByteRTCRecordingInfo-codectype"></span>
### codecType
```objectivec
@property(assign, nonatomic) ByteRTCVideoCodecType codecType;
```
录制文件的视频编码类型，参看 [ByteRTCVideoCodecType](#bytertcvideocodectype)


<span id="ByteRTCRecordingInfo-width"></span>
### width
```objectivec
@property(nonatomic, assign) NSInteger width;
```
录制视频的宽，单位：像素。纯音频录制请忽略该字段


<span id="ByteRTCRecordingInfo-height"></span>
### height
```objectivec
@property(nonatomic, assign) NSInteger height;
```
录制视频的高，单位：像素。纯音频录制请忽略该字段



# ByteRTCStreamSycnInfoConfig
```objectivec
@interface ByteRTCStreamSycnInfoConfig : NSObject
```

媒体流信息同步的相关配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCStreamIndex** | [streamIndex](#ByteRTCStreamSycnInfoConfig-streamindex) |
| **int** | [repeatCount](#ByteRTCStreamSycnInfoConfig-repeatcount) |
| **ByteRTCSyncInfoStreamType** | [streamType](#ByteRTCStreamSycnInfoConfig-streamtype) |


## 变量说明
<span id="ByteRTCStreamSycnInfoConfig-streamindex"></span>
### streamIndex
```objectivec
@property(assign, nonatomic) ByteRTCStreamIndex streamIndex;
```
流属性，主流或屏幕流。见 [ByteRTCStreamIndex](#bytertcstreamindex) 。


<span id="ByteRTCStreamSycnInfoConfig-repeatcount"></span>
### repeatCount
```objectivec
@property(assign, nonatomic) int repeatCount;
```
消息发送的重复次数，取值范围是 [0,25]，建议设置为 [3,5]。


<span id="ByteRTCStreamSycnInfoConfig-streamtype"></span>
### streamType
```objectivec
@property(assign, nonatomic) ByteRTCSyncInfoStreamType streamType;
```
媒体流信息同步的流类型，见 [ByteRTCSyncInfoStreamType](#bytertcsyncinfostreamtype) 。



# ForwardStreamConfiguration
```objectivec
@interface ForwardStreamConfiguration: NSObject
```

媒体流跨房间转发的目标房间的相关信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [roomId](#ForwardStreamConfiguration-roomid) |
| **NSString*** | [token](#ForwardStreamConfiguration-token) |


## 变量说明
<span id="ForwardStreamConfiguration-roomid"></span>
### roomId
```objectivec
@property(strong, nonatomic) NSString* _Nullable roomId;
```
跨房间转发媒体流过程中目标房间 ID<br>


<span id="ForwardStreamConfiguration-token"></span>
### token
```objectivec
@property(strong, nonatomic) NSString* _Nullable token;
```
使用转发目标房间 RoomID 和 UserID 生成 Token。<br>
测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。<br>
如果 Token 无效，转发失败。



# ForwardStreamStateInfo
```objectivec
@interface ForwardStreamStateInfo: NSObject
```

跨房间转发媒体流过程中的不同目标房间的状态和错误信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [roomId](#ForwardStreamStateInfo-roomid) |
| **ByteRTCForwardStreamState** | [state](#ForwardStreamStateInfo-state) |
| **ByteRTCForwardStreamError** | [error](#ForwardStreamStateInfo-error) |


## 变量说明
<span id="ForwardStreamStateInfo-roomid"></span>
### roomId
```objectivec
@property(strong, nonatomic) NSString* _Nullable roomId;
```
跨房间转发媒体流过程中目标房间 ID<br>
空字符串代表所有目标房间


<span id="ForwardStreamStateInfo-state"></span>
### state
```objectivec
@property(assign, nonatomic) ByteRTCForwardStreamState state;
```
跨房间转发媒体流过程中该目标房间的状态，参看 [ByteRTCForwardStreamState](#bytertcforwardstreamstate)


<span id="ForwardStreamStateInfo-error"></span>
### error
```objectivec
@property(assign, nonatomic) ByteRTCForwardStreamError error;
```
跨房间转发媒体流过程中该目标房间抛出的错误码，参看 [ByteRTCForwardStreamError](#bytertcforwardstreamerror)



# ForwardStreamEventInfo
```objectivec
@interface ForwardStreamEventInfo: NSObject
```

跨房间转发媒体流过程中的不同目标房间发生的事件


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [roomId](#ForwardStreamEventInfo-roomid) |
| **ByteRTCForwardStreamEvent** | [event](#ForwardStreamEventInfo-event) |


## 变量说明
<span id="ForwardStreamEventInfo-roomid"></span>
### roomId
```objectivec
@property(strong, nonatomic) NSString* _Nullable roomId;
```
跨房间转发媒体流过程中的发生该事件的目标房间 ID<br>
空字符串代表所有目标房间


<span id="ForwardStreamEventInfo-event"></span>
### event
```objectivec
@property(assign, nonatomic) ByteRTCForwardStreamEvent event;
```
跨房间转发媒体流过程中该目标房间发生的事件，参看 [ByteRTCForwardStreamEvent](#bytertcforwardstreamevent)



# ByteRTCNetworkQualityStats
```objectivec
@interface ByteRTCNetworkQualityStats: NSObject
```

上行/下行网络质量


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [uid](#ByteRTCNetworkQualityStats-uid) |
| **double** | [lossRatio](#ByteRTCNetworkQualityStats-lossratio) |
| **int** | [rtt](#ByteRTCNetworkQualityStats-rtt) |
| **int** | [totalBandwidth](#ByteRTCNetworkQualityStats-totalbandwidth) |
| **ByteRTCNetworkQuality** | [txQuality](#ByteRTCNetworkQualityStats-txquality) |
| **ByteRTCNetworkQuality** | [rxQuality](#ByteRTCNetworkQualityStats-rxquality) |


## 变量说明
<span id="ByteRTCNetworkQualityStats-uid"></span>
### uid
```objectivec
@property(strong, nonatomic) NSString* _Nonnull uid;
```
用户 ID


<span id="ByteRTCNetworkQualityStats-lossratio"></span>
### lossRatio
```objectivec
@property(assign, nonatomic) double lossRatio;
```
本端的上行/下行的丢包率，范围 [0.0,1.0]
当 `uid` 为本地用户时，代表发布流的上行丢包率。
当 `uid` 为远端用户时，代表接收所有订阅流的下行丢包率。


<span id="ByteRTCNetworkQualityStats-rtt"></span>
### rtt
```objectivec
@property(assign, nonatomic) int rtt;
```
当 `uid` 为本地用户时有效，客户端到服务端的往返延时（RTT），单位：ms


<span id="ByteRTCNetworkQualityStats-totalbandwidth"></span>
### totalBandwidth
```objectivec
@property(assign, nonatomic) int totalBandwidth;
```
本端的音视频 RTP 包 2 秒内的平均传输速率，单位：bps
当 `uid` 为本地用户时，代表发送速率。
当 `uid` 为远端用户时，代表所有订阅流的接收速率。


<span id="ByteRTCNetworkQualityStats-txquality"></span>
### txQuality
```objectivec
@property(assign, nonatomic) ByteRTCNetworkQuality txQuality;
```
上行网络质量评分，详见 [ByteRTCNetworkQuality](#bytertcnetworkquality)。


<span id="ByteRTCNetworkQualityStats-rxquality"></span>
### rxQuality
```objectivec
@property(assign, nonatomic) ByteRTCNetworkQuality rxQuality;
```
下行网络质量评分，详见 [ByteRTCNetworkQuality](#bytertcnetworkquality)。



# ByteRTCCloudProxyInfo
```objectivec
@interface ByteRTCCloudProxyInfo: NSObject
```

云代理信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [cloudProxyIp](#ByteRTCCloudProxyInfo-cloudproxyip) |
| **int** | [cloudProxyPort](#ByteRTCCloudProxyInfo-cloudproxyport) |


## 变量说明
<span id="ByteRTCCloudProxyInfo-cloudproxyip"></span>
### cloudProxyIp
```objectivec
@property(strong, nonatomic) NSString* _Nonnull cloudProxyIp;
```
云代理服务器 IP


<span id="ByteRTCCloudProxyInfo-cloudproxyport"></span>
### cloudProxyPort
```objectivec
@property(assign, nonatomic) int cloudProxyPort;
```
云代理服务器端口



# ByteRTCKTVMusicFilterType
```objectivec
typedef NS_OPTIONS(NSUInteger, ByteRTCKTVMusicFilterType)
```

歌曲过滤方式。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVMusicFilterTypeNone | 0 | 不过滤。 |
| ByteRTCKTVMusicFilterTypeWithoutLyric | 1 << 0 | 过滤没有歌词的歌曲。 |
| ByteRTCKTVMusicFilterTypeUnsupportedScore | 1 << 1 | 过滤不支持打分的歌曲。 |
| ByteRTCKTVMusicFilterTypeUnsupportedAccopmay | 1 << 2 | 过滤不支持伴唱切换的歌曲。 |
| ByteRTCKTVMusicFilterTypeUnsupportedClimx | 1 << 3 | 过滤没有高潮片段的歌曲。 |


# ByteRTCKTVMusicHotType
```objectivec
typedef NS_OPTIONS(NSUInteger, ByteRTCKTVMusicHotType)
```

热榜类别。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVMusicHotTypeContentCenter | 1 << 0 | 火山内容中心热歌榜。 |
| ByteRTCKTVMusicHotTypeProject | 1 << 1 | 项目热歌榜。 |


# ByteRTCKTVPlayState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCKTVPlayState)
```

音乐播放状态。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVPlayStatePlaying | 1 | 播放中。 |
| ByteRTCKTVPlayStatePaused | 2 | 暂停中。 |
| ByteRTCKTVPlayStateStoped | 3 | 已停止。 |
| ByteRTCKTVPlayStateFailed | 4 | 播放失败。 |
| ByteRTCKTVPlayStateFinished | 5 | 播放结束。 |


# ByteRTCKTVAudioTrackType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCKTVAudioTrackType)
```

原唱伴唱类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVAudioTrackTypeOriginal | 1 | 播放原唱。 |
| ByteRTCKTVAudioTrackTypeAccompy | 2 | 播放伴唱。 |


# ByteRTCKTVAudioPlayType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCKTVAudioPlayType)
```

音乐播放类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVAudioPlayTypeLocal | 0 | 仅本地播放。 |
| ByteRTCKTVAudioPlayTypeRemote | 1 | 仅远端播放。 |
| ByteRTCKTVAudioPlayTypeLocalAndRemote | 2 | 本地、远端同时播放。 |


# ByteRTCKTVLyricStatus
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCKTVLyricStatus)
```

歌词格式类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVLyricStatusNone | 0 | 无歌词。 |
| ByteRTCKTVLyricStatusKRC | 1 | KRC 歌词。 |
| ByteRTCKTVLyricStatusLRC | 2 | LRC 歌词。 |
| ByteRTCKTVLyricStatusKRCAndLRC | 3 | KRC 歌词和 LRC 歌词均有。 |


# ByteRTCKTVDownloadFileType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCKTVDownloadFileType)
```

下载文件类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVDownloadFileTypeMusic | 1 | 音频文件。 |
| ByteRTCKTVDownloadFileTypeKRC | 2 | KRC 歌词文件。 |
| ByteRTCKTVDownloadFileTypeLRC | 3 | LRC 歌词文件。 |
| ByteRTCKTVDownloadFileTypeMIDI | 4 | MIDI 文件。 |


# ByteRTCKTVDownloadLyricType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCKTVDownloadLyricType)
```

歌词文件类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVDownloadLyricTypeKRC | 0 | KRC 歌词文件。 |
| ByteRTCKTVDownloadLyricTypeLRC | 1 | LRC 歌词文件。 |


# ByteRTCKTVError
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCKTVError)
```

KTV 错误码。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVErrorOK | 0 | 成功。 |
| ByteRTCKTVErrorAppidInValid | -3000 | AppID 异常。 |
| ByteRTCKTVErrorParasInValid | -3001 | 非法参数，传入的参数不正确。 |
| ByteRTCKTVErrorGetMusicFailed | -3002 | 获取歌曲资源失败。 |
| ByteRTCKTVErrorGetLyricFailed | -3003 | 获取歌词失败。 |
| ByteRTCKTVErrorMusicTakedown | -3004 | 歌曲下架。 |
| ByteRTCKTVErrorMusicDownload | -3005 | 歌曲文件下载失败。 |
| ByteRTCKTVErrorMidiDownloadFailed | -3006 | MIDI 文件下载失败。 |
| ByteRTCKTVErrorSystemBusy | -3007 | 系统繁忙。 |
| ByteRTCKTVErrorNetwork | -3008 | 网络异常。 |
| ByteRTCKTVErrorNotJoinRoom | -3009 | KTV 功能未加入房间。 |
| ByteRTCKTVErrorParseData | -3010 | 解析数据失败。 |
| ByteRTCKTVErrorDownload | -3011 | 下载失败。 |
| ByteRTCKTVErrorDownloading | -3012 | 已在下载中。 |
| ByteRTCKTVErrorInternal | -3013 | 内部错误，联系技术支持人员。 |


# ByteRTCKTVPlayerError
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCKTVPlayerError)
```

KTV 播放器错误码。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCKTVPlayerErrorOK | 0 | 成功。 |
| ByteRTCKTVPlayerErrorFileNotExist | -3020 | 播放错误，请下载后播放。 |
| ByteRTCKTVPlayerErrorFileError | -3021 | 播放错误，请确认文件播放格式。 |
| ByteRTCKTVPlayerErrorNotJoinRoom | -3022 | 播放错误，未进入房间。 |
| ByteRTCKTVPlayerErrorParam | -3023 | 参数错误。 |
| ByteRTCKTVPlayerErrorStartError | -3024 | 播放失败，找不到文件或文件打开失败。 |
| ByteRTCKTVPlayerErrorMixIdError | -3025 | 混音 ID 异常。 |
| ByteRTCKTVPlayerErrorPositionError | -3026 | 设置播放位置出错。 |
| ByteRTCKTVPlayerErrorAudioVolumeError | -3027 | 音量参数不合法，可设置的取值范围为 [0,400]。 |
| ByteRTCKTVPlayerErrorTypeError | -3028 | 不支持此混音类型。 |
| ByteRTCKTVPlayerErrorPitchError | -3029 | 音调文件不合法。 |
| ByteRTCKTVPlayerErrorAudioTrackError | -3030 | 音轨不合法。 |
| ByteRTCKTVPlayerErrorStartingError | -3031 | 混音启动中。 |


# ByteRTCKTVMusic
```objectivec
@interface ByteRTCKTVMusic : NSObject
```

歌曲数据。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [musicId](#ByteRTCKTVMusic-musicid) |
| **NSString*** | [musicName](#ByteRTCKTVMusic-musicname) |
| **NSString*** | [singer](#ByteRTCKTVMusic-singer) |
| **NSString*** | [vendorId](#ByteRTCKTVMusic-vendorid) |
| **NSString*** | [vendorName](#ByteRTCKTVMusic-vendorname) |
| **int64_t** | [updateTimestamp](#ByteRTCKTVMusic-updatetimestamp) |
| **NSString*** | [posterUrl](#ByteRTCKTVMusic-posterurl) |
| **ByteRTCKTVLyricStatus** | [lyricStatus](#ByteRTCKTVMusic-lyricstatus) |
| **int** | [duration](#ByteRTCKTVMusic-duration) |
| **BOOL** | [enableScore](#ByteRTCKTVMusic-enablescore) |
| **int** | [climaxStartTime](#ByteRTCKTVMusic-climaxstarttime) |
| **int** | [climaxEndTime](#ByteRTCKTVMusic-climaxendtime) |


## 变量说明
<span id="ByteRTCKTVMusic-musicid"></span>
### musicId
```objectivec
@property (nonatomic, copy) NSString * _Nonnull musicId;
```
音乐 ID。


<span id="ByteRTCKTVMusic-musicname"></span>
### musicName
```objectivec
@property (nonatomic, copy) NSString * _Nonnull musicName;
```
音乐名称。


<span id="ByteRTCKTVMusic-singer"></span>
### singer
```objectivec
@property (nonatomic, copy) NSString * _Nonnull singer;
```
歌手。


<span id="ByteRTCKTVMusic-vendorid"></span>
### vendorId
```objectivec
@property (nonatomic, copy) NSString * _Nonnull vendorId;
```
版权商 ID。


<span id="ByteRTCKTVMusic-vendorname"></span>
### vendorName
```objectivec
@property (nonatomic, copy) NSString * _Nonnull vendorName;
```
版权商名称。


<span id="ByteRTCKTVMusic-updatetimestamp"></span>
### updateTimestamp
```objectivec
@property (nonatomic, assign) int64_t updateTimestamp;
```
最新更新时间戳，单位为毫秒。


<span id="ByteRTCKTVMusic-posterurl"></span>
### posterUrl
```objectivec
@property (nonatomic, copy) NSString * _Nonnull posterUrl;
```
封面地址。


<span id="ByteRTCKTVMusic-lyricstatus"></span>
### lyricStatus
```objectivec
@property (nonatomic, assign) ByteRTCKTVLyricStatus lyricStatus;
```
歌词格式类型，参看 [ByteRTCKTVLyricStatus](#bytertcktvlyricstatus)。


<span id="ByteRTCKTVMusic-duration"></span>
### duration
```objectivec
@property (nonatomic, assign) int duration;
```
歌曲长度，单位为毫秒。


<span id="ByteRTCKTVMusic-enablescore"></span>
### enableScore
```objectivec
@property (nonatomic, assign) BOOL enableScore;
```
歌曲是否支持打分。


<span id="ByteRTCKTVMusic-climaxstarttime"></span>
### climaxStartTime
```objectivec
@property (nonatomic, assign) int climaxStartTime;
```
歌曲高潮片段开始时间，单位为毫秒。


<span id="ByteRTCKTVMusic-climaxendtime"></span>
### climaxEndTime
```objectivec
@property (nonatomic, assign) int climaxEndTime;
```
歌曲高潮片段停止时间，单位为毫秒。



# ByteRTCKTVHotMusicInfo
```objectivec
@interface ByteRTCKTVHotMusicInfo : NSObject
```

热榜歌曲数据。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCKTVMusicHotType** | [hotType](#ByteRTCKTVHotMusicInfo-hottype) |
| **NSString*** | [hotName](#ByteRTCKTVHotMusicInfo-hotname) |
| **NSArray<ByteRTCKTVMusic*>*** | [musics](#ByteRTCKTVHotMusicInfo-musics) |


## 变量说明
<span id="ByteRTCKTVHotMusicInfo-hottype"></span>
### hotType
```objectivec
@property (nonatomic, assign) ByteRTCKTVMusicHotType hotType;
```
热榜类别，参看 [ByteRTCKTVMusicHotType](#bytertcktvmusichottype)。多个热榜类别可以按位或组合。


<span id="ByteRTCKTVHotMusicInfo-hotname"></span>
### hotName
```objectivec
@property (nonatomic, copy) NSString * _Nullable hotName;
```
热榜名称。


<span id="ByteRTCKTVHotMusicInfo-musics"></span>
### musics
```objectivec
@property (nonatomic, copy) NSArray<ByteRTCKTVMusic *> * _Nullable musics;
```
歌曲数据，参看 [ByteRTCKTVMusic](#bytertcktvmusic)。



# ByteRTCKTVDownloadResult
```objectivec
@interface ByteRTCKTVDownloadResult : NSObject
```

歌曲下载信息。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [musicId](#ByteRTCKTVDownloadResult-musicid) |
| **ByteRTCKTVDownloadFileType** | [fileType](#ByteRTCKTVDownloadResult-filetype) |
| **NSString*** | [filePath](#ByteRTCKTVDownloadResult-filepath) |


## 变量说明
<span id="ByteRTCKTVDownloadResult-musicid"></span>
### musicId
```objectivec
@property (nonatomic, copy) NSString * _Nonnull musicId;
```
音乐 ID。


<span id="ByteRTCKTVDownloadResult-filetype"></span>
### fileType
```objectivec
@property (nonatomic, assign) ByteRTCKTVDownloadFileType fileType;
```
下载文件类型，参看 [ByteRTCKTVDownloadFileType](#bytertcktvdownloadfiletype)。


<span id="ByteRTCKTVDownloadResult-filepath"></span>
### filePath
```objectivec
@property (nonatomic, copy) NSString * _Nullable filePath;
```
文件存放路径。



# AttenuationType
```objectivec
typedef NS_ENUM(NSInteger, AttenuationType)
```

空间音频音量随距离衰减模式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| AttenuationTypeNone | 0 | 不随距离衰减 |
| AttenuationTypeLinear | 1 | 线性衰减，音量随距离增大而线性减小 |
| AttenuationTypeExponential | 2 | 指数型衰减，音量随距离增大进行指数衰减 |


# ReceiveRange
```objectivec
@interface ReceiveRange : NSObject
```

本地用户能收听到、且具有衰减效果的音频接收范围


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [min](#ReceiveRange-min) |
| **int** | [max](#ReceiveRange-max) |


## 变量说明
<span id="ReceiveRange-min"></span>
### min
```objectivec
@property(nonatomic, assign) int min;
```
能够接收语音、并且具有衰减效果的最小距离值，该值须 ≥ 0，但 ≤ max。  <br>
小于该值的范围内没有范围语音效果，即收听到的音频音量相同。


<span id="ReceiveRange-max"></span>
### max
```objectivec
@property(nonatomic, assign) int max;
```
能够收听语音的最大距离值，该值须 > 0 且 ≥ min。  <br>
当收听者和声源距离处于 [min, max) 之间时，收听到的音量根据距离呈衰减效果。  <br>
超出该值范围的音频将无法收听到。



# ByteRTCRangeAudioInfo
```objectivec
@interface ByteRTCRangeAudioInfo : NSObject
```

范围语音流信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [userId](#ByteRTCRangeAudioInfo-userid) |
| **int** | [factor](#ByteRTCRangeAudioInfo-factor) |


## 变量说明
<span id="ByteRTCRangeAudioInfo-userid"></span>
### userId
```objectivec
@property(copy, nonatomic) NSString * _Nonnull userId;
```
远端音频发布用户 ID


<span id="ByteRTCRangeAudioInfo-factor"></span>
### factor
```objectivec
@property(nonatomic, assign) int factor;
```
本地用户听到该远端音频发布用户的衰减系数，范围 [0,100]，数值为 0 时表示远端用户音频音量为 0。



# ByteRtcScreenCapturerExtDelegate
```objectivec
@protocol ByteRtcScreenCapturerExtDelegate <NSObject>
```

屏幕采集相关扩展协议，仅适用于 SDK 内部采集。  <br>
用户创建 extesion 后生成的 SampleHandler 需继承此协议以实现屏幕共享相关能力。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onQuitFromApp](#ByteRtcScreenCapturerExtDelegate-onquitfromapp) |
| **void** | [onReceiveMessageFromApp:](#ByteRtcScreenCapturerExtDelegate-onreceivemessagefromapp) |
| **void** | [onSocketDisconnect](#ByteRtcScreenCapturerExtDelegate-onsocketdisconnect) |
| **void** | [onSocketConnect](#ByteRtcScreenCapturerExtDelegate-onsocketconnect) |
| **void** | [onNotifyAppRunning](#ByteRtcScreenCapturerExtDelegate-onnotifyapprunning) |


## 函数说明
<span id="ByteRtcScreenCapturerExtDelegate-onquitfromapp"></span>
### onQuitFromApp
```objectivec

- (void)onQuitFromApp;
```
通知 Broadcast Upload Extension 停止采集屏幕并退出。


**注意**
用户调用 [stopScreenCapture](iOS-api.md#ByteRTCVideo-stopscreencapture) 后，会触发该方法通知 extension 端的 SDK 停止屏幕采集。

<span id="ByteRtcScreenCapturerExtDelegate-onreceivemessagefromapp"></span>
### onReceiveMessageFromApp:
```objectivec

- (void)onReceiveMessageFromApp:(NSData *)message;
```
Socket 收到 App 侧发来的信息时，触发该回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **NSData*** | App 侧发送的消息 |


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


# ByteRtcScreenCapturerExt
```objectivec
@interface ByteRtcScreenCapturerExt : NSObject
```

屏幕采集相关扩展实例，仅适用于 SDK 内部采集。  <br>
用户创建 extesion 后生成的 SampleHandler 需通过此实例实现屏幕共享相关能力。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [startWithDelegate:groupId:](#ByteRtcScreenCapturerExt-startwithdelegate-groupid) |
| **void** | [stop](#ByteRtcScreenCapturerExt-stop) |
| **void** | [processSampleBuffer:withType:](#ByteRtcScreenCapturerExt-processsamplebuffer-withtype) |


## 函数说明
<span id="ByteRtcScreenCapturerExt-startwithdelegate-groupid"></span>
### startWithDelegate:groupId:
```objectivec

- (void)startWithDelegate:(NSObject<ByteRtcScreenCapturerExtDelegate> *)delegate groupId:(NSString *)groupId;
```
开始屏幕采集  <br>
Extension 启动后，系统将自动调用该方法开启屏幕采集。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| delegate | **NSObject<ByteRtcScreenCapturerExtDelegate>*** | 回调代理，参看 [ByteRtcScreenCapturerExtDelegate](#bytertcscreencapturerextdelegate) |
| groupId | **NSString*** | App groups 中配置的 group ID |


<span id="ByteRtcScreenCapturerExt-stop"></span>
### stop
```objectivec

- (void)stop;
```
结束屏幕采集  <br>
Extension 关闭后，系统将自动调用该方法停止屏幕采集。


<span id="ByteRtcScreenCapturerExt-processsamplebuffer-withtype"></span>
### processSampleBuffer:withType:
```objectivec

- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType API_AVAILABLE(ios(10));
```
推送 Extension 采集的数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| sampleBuffer | **CMSampleBufferRef** | 采集到的数据 |
| sampleBufferType | **RPSampleBufferType** | 数据类型 |


# Orientation
```objectivec
@interface Orientation : NSObject
```

方向朝向信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [x](#Orientation-x) |
| **float** | [y](#Orientation-y) |
| **float** | [z](#Orientation-z) |


## 变量说明
<span id="Orientation-x"></span>
### x
```objectivec
@property(nonatomic, assign) float x;
```
x 坐标


<span id="Orientation-y"></span>
### y
```objectivec
@property(nonatomic, assign) float y;
```
y 坐标


<span id="Orientation-z"></span>
### z
```objectivec
@property(nonatomic, assign) float z;
```
z 坐标



# HumanOrientation
```objectivec
@interface HumanOrientation : NSObject
```

三维朝向信息，三个向量需要两两垂直。参看 [Orientation](#orientation)。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **Orientation*** | [forward](#HumanOrientation-forward) |
| **Orientation*** | [right](#HumanOrientation-right) |
| **Orientation*** | [up](#HumanOrientation-up) |


## 变量说明
<span id="HumanOrientation-forward"></span>
### forward
```objectivec
@property(nonatomic, strong) Orientation* _Nonnull forward;
```
正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向


<span id="HumanOrientation-right"></span>
### right
```objectivec
@property(nonatomic, strong) Orientation* _Nonnull right;
```
正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向


<span id="HumanOrientation-up"></span>
### up
```objectivec
@property(nonatomic, strong) Orientation* _Nonnull up;
```
正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向



# ByteRTCRenderMode
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCRenderMode)
```

视频帧渲染设置


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCRenderModeHidden | 1 | 视窗填满优先，默认值。  <br><br/>视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br><br/>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。 |
| ByteRTCRenderModeFit | 2 | 视频帧内容全部显示优先。  <br><br/>视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。<br><br/>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。 |
| ByteRTCRenderModeFill | 3 | 视频帧自适应画布 <br><br/>视频帧非等比缩放，直至画布被填满。在此过程中，视频帧的长宽比例可能会发生变化。 |


# ByteRTCTranscoderContentControlType
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCTranscoderContentControlType)
```

合流输出内容类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCTranscoderContentControlTypeHasAudioAndVideo | 0 | 输出的混流包含音频和视频 |
| ByteRTCTranscoderContentControlTypeHasAudioOnly | 1 | 输出的混流只包含音频 |
| ByteRTCTranscoderContentControlTypeHasVideoOnly | 2 | 输出的混流只包含视频 |


# ByteRTCTranscoderLayoutRegionType
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCTranscoderLayoutRegionType)
```

合流布局区域类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCTranscoderLayoutRegionTypeVideoStream | 0 | 合流布局区域类型为视频。 |
| ByteRTCTranscoderLayoutRegionTypeImage | 1 | 合流布局区域类型为图片。 |


# ByteRTCVideoStreamType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamType)
```

视频流类型
目前C++ SDK 只支持 ByteRTCVideoStreamTypeHigh 类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoStreamTypeHigh | 0 | 高分辨率视频流 |
| ByteRTCVideoStreamTypeLow | 1 | 低分辨率视频 |


# ByteRTCVideoStreamState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamState)
```

设置本地视频属性的返回状态。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoStreamStateSuccess | 0 | 设置本地视频属性成功 |
| ByteRTCVideoStreamStateInvalid | -2 | 本地视频属性参数不合法 |


# ByteRTCVideoOutputOrientationMode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoOutputOrientationMode)
```

视频输出方向模式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoOutputOrientationModeAdaptative | 0 | 自适应布局 |
| ByteRTCVideoOutputOrientationModeFixedLandscape | 1 | 横屏布局 |
| ByteRTCVideoOutputOrientationModeFixedPortrait | 2 | 竖屏布局 |


# ByteRTCVideoOrientation
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCVideoOrientation)
```

视频帧朝向


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoOrientationAdaptive | 0 | （默认）使用相机输出的原始视频帧的角度，不对视频帧进行额外旋转。 |
| ByteRTCVideoOrientationPortrait | 1 | 固定为竖屏，将相机采集到的视频帧转换为竖屏，在整个 RTC 链路中传递竖屏帧。 |
| ByteRTCVideoOrientationLandscape | 2 | 固定为横屏，将相机采集到的视频帧转换为横屏，在整个 RTC 链路中传递横屏帧。 |


# ByteRTCMirrorType
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCMirrorType)
```

镜像类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMirrorTypeNone | 0 | 本地预览和编码传输时均无镜像效果 |
| ByteRTCMirrorTypeRender | 1 | 本地预览时有镜像效果，编码传输时无镜像效果 |
| ByteRTCMirrorTypeRenderAndEncoder | 3 | 本地预览和编码传输时均有镜像效果 |


# ByteRTCEffectBeautyMode
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCEffectBeautyMode)
```

基础美颜模式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCEffectWhiteMode | 0 | 美白 |
| ByteRTCEffectSmoothMode | 1 | 磨皮 |
| ByteRTCEffectSharpenMode | 2 | 锐化 |


# ByteRTCVideoRotation
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoRotation)
```

视频旋转信息，枚举类型，定义了以 90 度为间隔的四种旋转模式。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoRotation0 | 0 | 视频不做旋转 |
| ByteRTCVideoRotation90 | 90 | 视频顺时针旋转 90 度 |
| ByteRTCVideoRotation180 | 180 | 视频顺时针旋转 180 度 |
| ByteRTCVideoRotation270 | 270 | 视频顺时针旋转 270 度 |


# ByteRTCVideoContentType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoContentType)
```

视频内容类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoContentTypeNormalFrame | 0 | 普通视频 |
| ByteRTCVideoContentTypeBlackFrame | 1 | 黑帧视频 |


# ByteRTCVideoStreamScaleMode
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamScaleMode)
```

视频帧缩放模式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoStreamScaleModeAuto | 0 | 自动缩放模式，默认设置为 ByteRTCVideoStreamScaleModeFitWithCropping。 |
| ByteRTCVideoStreamScaleModeStretch | 1 | 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。 |
| ByteRTCVideoStreamScaleModeFitWithCropping | 2 | 视窗填满优先，默认值。  <br><br/>视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br><br/>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。 |
| ByteRTCVideoStreamScaleModeFitWithFilling | 3 | 视频帧内容全部显示优先。  <br><br/>视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br><br/>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。保持纵横比来缩放图像，填充短边 |


# ByteRTCVideoPictureType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoPictureType)
```

编码帧类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoPictureTypeUnknown | 0 | 未知类型 |
| ByteRTCVideoPictureTypeI | 1 | I帧，关键帧，编解码不需要参考其他视频帧 |
| ByteRTCVideoPictureTypeP | 2 | P帧，向前参考帧，编解码需要参考前一帧视频帧 |
| ByteRTCVideoPictureTypeB | 3 | B帧，前后参考帧，编解码需要参考前后两帧视频帧 |


# ByteRTCVideoEncoderPreference
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoEncoderPreference)
```

编码策略偏好。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoEncoderPreferenceDisabled | 0 | 无偏好。不降低帧率和分辨率。 |
| ByteRTCVideoEncoderPreferenceMaintainFramerate | 1 | （默认值）帧率优先。 |
| ByteRTCVideoEncoderPreferenceMaintainQuality | 2 | 分辨率优先。 |
| ByteRTCVideoEncoderPreferenceBalance | 3 | 平衡帧率与分辨率。 |


# ByteRTCDataFrameType
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCDataFrameType)
```

数据类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCDataFrameTypeSei | 0 | SEI 数据 |
| ByteRTCDataFrameTypeRoi | 1 | 人脸识别数据 |
| ByteRTCDataFrameTypeOther | 2 | 其他数据帧类型 |


# ByteRTCVideoCapturePreference
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoCapturePreference)
```

视频采集模式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoCapturePreferenceAuto | 0 | （默认）自动设置采集参数。<br/>SDK在开启采集时根据服务端下发的采集配置结合编码参数设置最佳采集参数。 |
| ByteRTCVideoCapturePreferenceMannal | 1 | 手动设置采集参数，包括采集分辨率、帧率。 |
| ByteRTCVideoCapturePreferenceAutoPerformance | 2 | 采集参数与编码参数一致 |


# ByteRTCVideoFrameType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoFrameType)
```

视频帧类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoFrameTypeRawMemory | 0 | 视频帧类型：内存数据 |
| ByteRTCVideoFrameTypePixelBuffer | 1 | 视频帧类型：CVPixelBuffer |


# ByteRTCVideoPixelFormat
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoPixelFormat)
```

视频帧格式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoPixelFormatUnknown | 0 | 未知格式 |
| ByteRTCVideoPixelFormatI420 | 1 | I420 |
| ByteRTCVideoPixelFormatBGRA | 2 | BGRA |
| ByteRTCVideoPixelFormatNV21 | 3 | NV21 |
| ByteRTCVideoPixelFormatRGBA | 4 | RGBA |
| ByteRTCVideoPixelFormatIMC2 | 5 | IMC2 |
| ByteRTCVideoPixelFormatARGB | 7 | ARGB |
| ByteRTCVideoPixelFormatNV12 | 8 | NV12 |
| ByteRTCVideoPixelFormatGLTexture2D | 10 | Opengl Texture2D纹理 |
| ByteRTCVideoPixelFormatGLTextureOES | 11 | Opengl OES纹理 |
| ByteRTCVideoPixelFormatCVPixelBuffer | 12 | CVPixelBuffer |


# ByteRTCVideoSinkPixelFormat
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoSinkPixelFormat)
```

视频帧编码格式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoSinkPixelFormatOriginal | 0 | 原始视频帧格式 |
| ByteRTCVideoSinkPixelFormatI420 | 1 | YUV I420 格式 |
| ByteRTCVideoSinkPixelFormatBGRA | 2 | BGRA 格式 |
| ByteRTCVideoSinkPixelFormatNV12 | 8 | YUV NV21 格式 |


# ByteRTCStreamMixingType
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingType)
```

合流方式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCStreamMixingTypeByServer | 0 | 通过服务端转推 |
| ByteRTCStreamMixingTypeByClient | 1 | 端云一体转推 |


# ByteRTCStreamMixingEvent
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingEvent)
```

转推直播事件


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCStreamMixingEventStart | 1 | 请求发起转推直播任务 |
| ByteRTCStreamMixingEventStartSuccess | 2 | 发起转推直播任务成功 |
| ByteRTCStreamMixingEventStartFailed | 3 | 发起转推直播任务失败 |
| ByteRTCStreamMixingEventUpdate | 4 | 请求更新转推直播任务配置 |
| ByteRTCStreamMixingEventUpdateSuccess | 5 | 成功更新转推直播任务配置 |
| ByteRTCStreamMixingEventUpdateFailed | 6 | 更新转推直播任务配置失败 |
| ByteRTCStreamMixingEventStop | 7 | 请求结束转推直播任务 |
| ByteRTCStreamMixingEventStopSuccess | 8 | 结束转推直播任务成功 |
| ByteRTCStreamMixingEventStopFailed | 9 | 结束转推直播任务失败 |
| ByteRTCStreamMixingEventChangeMixType | 10 | 更新转推直播任务配置的请求超时 |
| ByteRTCStreamMixingEventFirstAudioFrameByClientMixer | 11 | 得到客户端合流音频首帧 |
| ByteRTCStreamMixingEventFirstVideoFrameByClientMixer | 12 | 收到客户端合流视频首帧 |
| ByteRTCStreamMixingEventUpdateTimeout | 13 | 更新转推直播任务配置超时 |
| ByteRTCStreamMixingEventStartTimeout | 14 | 发起转推直播任务配置超时 |
| ByteRTCStreamMixingEventRequestParamError | 15 | 合流布局参数错误 |
| ByteRTCStreamMixingEventMixImage | 16 | 合流加图片 |


# ByteRTCSubscribeMediaType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCSubscribeMediaType)
```

订阅媒体的类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCSubscribeMediaTypeNone | 0 | 既不订阅音频，也不订阅视频 |
| ByteRTCSubscribeMediaTypeAudioOnly | 1 | 只订阅音频，不订阅视频 |
| ByteRTCSubscribeMediaTypeVideoOnly | 2 | 只订阅视频，不订阅音频 |
| ByteRTCSubscribeMediaTypeAudioAndVideo | 3 | 同时订阅音频和视频 |


# ByteRTCPauseResumControlMediaType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCPauseResumControlMediaType)
```

暂停/恢复接收远端的媒体流类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCControlMediaTypeAudio | 0 | 只控制音频，不影响视频 |
| ByteRtcControlMediaTypeVideo | 1 | 只控制视频，不影响音频 |
| ByteRtcControlMediaTypeAudioAndVideo | 2 | 同时控制音频和视频 |


# ByteRTCVideoSourceType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoSourceType)
```

视频输入源类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoSourceTypeExternal | 0 | 自定义采集视频源 |
| ByteRTCVideoSourceTypeInternal | 1 | 内部采集视频源 |
| ByteRTCVideoSourceTypeEncodedManualSimulcast | 2 | 自定义编码视频源。  <br><br/>SDK 不会自动生成多路流，你需要自行生成并推送多路流 |
| ByteRTCVideoSourceTypeEncodedAutoSimulcast | 3 | 自定义编码视频源。  <br><br/>你仅需推送分辨率最大的一路编码后视频流，SDK 将自动转码生成多路小流 |


# ByteRTCVideoDecoderConfig
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoDecoderConfig)
```

视频解码方式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoDecoderConfigRaw | 0 | 开启 SDK 内部解码，只回调解码后的数据。回调为[onRemoteVideoFrame:user:room: ](iOS-callback.md#onremotevideoframe-user-room)。 |
| ByteRTCVideoDecoderConfigEncode | 1 | 开启自定义解码，只回调解码前数据。回调为[onRemoteEncodedVideoFrame:withEncodedVideoFrame:](iOS-callback.md#onremoteencodedvideoframe-withencodedvideoframe)。|
| ByteRTCVideoDecoderConfigBoth | 2 | 开启 SDK 内部解码，同时回调解码前和解码后的数据。回调为回调为[onRemoteVideoFrame:user:room: ](iOS-callback.md#onremotevideoframe-user-room)和[onRemoteEncodedVideoFrame:withEncodedVideoFrame:](iOS-callback.md#onremoteencodedvideoframe-withencodedvideoframe)。 |


# ByteRTCVirtualBackgroundSourceType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVirtualBackgroundSourceType)
```

虚拟背景类型。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVirtualBackgroundSourceTypeColor | 0 | 使用纯色背景替换视频原有背景。 |
| ByteRTCVirtualBackgroundSourceTypeImage | 1 | 使用自定义图片替换视频原有背景。 |


# ByteRTCCameraID
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCCameraID)
```

摄像头类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCCameraIDFront | 0 | 前置摄像头 |
| ByteRTCCameraIDBack | 1 | 后置摄像头 |
| ByteRTCCameraIDExternal | 2 | 外接摄像头 |
| ByteRTCCameraIDInvalid | 3 | 无效值 |


# ByteRTCRecordingType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCRecordingType)
```

本地录制的媒体类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| RecordAudioOnly | 0 | 只录制音频 |
| RecordVideoOnly | 1 | 只录制视频 |
| RecordVideoAndAudio | 2 | 同时录制音频和视频 |


# ByteRTCScreenMediaType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCScreenMediaType)
```

屏幕采集媒体类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCScreenMediaTypeVideoOnly | 0 | 只采集视频数据 |
| ByteRTCScreenMediaTypeAudioOnly | 1 | 只采集音频数据 |
| ByteRTCScreenMediaTypeVideoAndAudio | 2 | 音视频数据都采集 |


# ByteRTCScreenCaptureSourceType
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCScreenCaptureSourceType)
```

屏幕采集对象的类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCScreenCaptureSourceTypeUnknown | 0 | 类型未知 |
| ByteRTCScreenCaptureSourceTypeWindow | 1 | 应用程序的窗口 |
| ByteRTCScreenCaptureSourceTypeScreen | 2 | 桌面 |


# ByteRTCMouseCursorCaptureState
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCMouseCursorCaptureState)
```

内部采集屏幕视频流时，是否采集鼠标信息。


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMouseCursorCaptureStateOn | 0 | 采集鼠标信息。 |
| ByteRTCMouseCursorCaptureStateOff | 1 | 不采集鼠标信息。 |


# ByteRTCHighlightConfig
```objectivec
@interface ByteRTCHighlightConfig: NSObject
```

屏幕共享时的边框高亮设置。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **BOOL** | [enableHighlight](#ByteRTCHighlightConfig-enablehighlight) |
| **uint32_t** | [borderColor](#ByteRTCHighlightConfig-bordercolor) |
| **int** | [borderWidth](#ByteRTCHighlightConfig-borderwidth) |


## 变量说明
<span id="ByteRTCHighlightConfig-enablehighlight"></span>
### enableHighlight
```objectivec
@property (assign, nonatomic) BOOL enableHighlight;
```
是否显示高亮边框，默认显示。


<span id="ByteRTCHighlightConfig-bordercolor"></span>
### borderColor
```objectivec
@property (assign, nonatomic) uint32_t borderColor;
```
边框的颜色, 颜色格式为十六进制 ARGB: 0xAARRGGB。


<span id="ByteRTCHighlightConfig-borderwidth"></span>
### borderWidth
```objectivec
@property (assign, nonatomic) int borderWidth;
```
边框的宽度，单位：像素。



# ByteRTCTorchState
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCTorchState)
```

相机补光灯状态


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCTorchStateOff | 0 | 相机补光灯关闭 |
| ByteRTCTorchStateOn | 1 | 相机补光灯打开 |


# ByteRTCVideoDeviceType
```objectivec
typedef NS_ENUM(NSInteger, ByteRTCVideoDeviceType)
```

当前视频设备类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoDeviceTypeUnknown | -1 | 未知视频设备 |
| ByteRTCVideoDeviceTypeRenderDevice | 0 | 视频渲染设备类型 |
| ByteRTCVideoDeviceTypeCaptureDevice | 1 | 视频采集设备类型 |
| ByteRTCVideoDeviceTypeScreenCaptureDevice | 2 | 屏幕流视频设备 |


# ByteRTCMediaStreamType
```objectivec
typedef NS_OPTIONS(NSUInteger, ByteRTCMediaStreamType)
```

媒体流类型


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCMediaStreamTypeAudio | (1 << 0) | 只控制音频 |
| ByteRTCMediaStreamTypeVideo | (1 << 1) | 只控制视频 |
| ByteRTCMediaStreamTypeBoth | ByteRTCMediaStreamTypeAudio \| ByteRTCMediaStreamTypeVideo | 同时控制音频和视频 |


# ByteRTCFrameRateRatio
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCFrameRateRatio)
```

占发布端原始帧率的比例


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCFrameRateRatioOrigin | 0 | 100% |
| ByteRTCFrameRateRatioHalf | 1 | 50% |
| ByteRTCFrameRateRatioQuater | 2 | 25% |


# ByteRTCVideoRotationMode
```objectivec
typedef NS_ENUM(NSUInteger, ByteRTCVideoRotationMode)
```

视频旋转模式


### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ByteRTCVideoRotationModeFollowApp | 0 | App 方向 |
| ByteRTCVideoRotationModeFollowGSensor | 1 | 重力方向 |


# ByteRTCRectangle
```objectivec
@interface ByteRTCRectangle : NSObject
```

矩形区域，用于指定屏幕区域。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [x](#ByteRTCRectangle-x) |
| **int** | [y](#ByteRTCRectangle-y) |
| **int** | [width](#ByteRTCRectangle-width) |
| **int** | [height](#ByteRTCRectangle-height) |


## 变量说明
<span id="ByteRTCRectangle-x"></span>
### x
```objectivec
@property(assign, nonatomic) int x;
```
矩形区域左上角的 x 坐标。


<span id="ByteRTCRectangle-y"></span>
### y
```objectivec
@property(assign, nonatomic) int y;
```
矩形区域左上角的 y 坐标。


<span id="ByteRTCRectangle-width"></span>
### width
```objectivec
@property(assign, nonatomic) int width;
```
矩形宽度，单位：px。


<span id="ByteRTCRectangle-height"></span>
### height
```objectivec
@property(assign, nonatomic) int height;
```
矩形高度，单位：px。



# ByteRTCFaceDetectionResult
```objectivec
@interface ByteRTCFaceDetectionResult : NSObject
```

人脸检测结果


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [detectResult](#ByteRTCFaceDetectionResult-detectresult) |
| **int** | [imageWidth](#ByteRTCFaceDetectionResult-imagewidth) |
| **int** | [imageHeight](#ByteRTCFaceDetectionResult-imageheight) |
| **NSArray<ByteRTCRectangle*>*** | [faces](#ByteRTCFaceDetectionResult-faces) |


## 变量说明
<span id="ByteRTCFaceDetectionResult-detectresult"></span>
### detectResult
```objectivec
@property(assign, nonatomic) int detectResult;
```
人脸检测结果 <br>

+ 0：检测成功 <br>
+ !0：检测失败。详见[CV 错误码](https://www.volcengine.com/docs/6705/102042)。


<span id="ByteRTCFaceDetectionResult-imagewidth"></span>
### imageWidth
```objectivec
@property(assign, nonatomic) int imageWidth;
```
原始图片宽度(px)


<span id="ByteRTCFaceDetectionResult-imageheight"></span>
### imageHeight
```objectivec
@property(assign, nonatomic) int imageHeight;
```
原始图片高度(px)


<span id="ByteRTCFaceDetectionResult-faces"></span>
### faces
```objectivec
@property(nonatomic, copy) NSArray<ByteRTCRectangle *> * _Nullable faces;
```
识别到人脸的矩形框。数组的长度和检测到的人脸数量一致。参看 [ByteRTCRectangle](#bytertcrectangle)。



# ByteRTCVideoCanvas
```objectivec
@interface ByteRTCVideoCanvas : NSObject
```

视频帧渲染设置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCView*** | [view](#ByteRTCVideoCanvas-view) |
| **ByteRTCRenderMode** | [renderMode](#ByteRTCVideoCanvas-rendermode) |
| **NSString*** | [roomId](#ByteRTCVideoCanvas-roomid) |
| **NSString*** | [uid](#ByteRTCVideoCanvas-uid) |
| **NSInteger** | [backgroundColor](#ByteRTCVideoCanvas-backgroundcolor) |


## 变量说明
<span id="ByteRTCVideoCanvas-view"></span>
### view
```objectivec
@property(strong, nonatomic) ByteRTCView* _Nullable view;
```
本地视图句柄


<span id="ByteRTCVideoCanvas-rendermode"></span>
### renderMode
```objectivec
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
```
渲染模式，参看 [ByteRTCRenderMode](#bytertcrendermode)


<span id="ByteRTCVideoCanvas-roomid"></span>
### roomId
```objectivec
@property(strong, nonatomic) NSString* _Nullable roomId;
```
房间 ID


<span id="ByteRTCVideoCanvas-uid"></span>
### uid
```objectivec
@property(strong, nonatomic) NSString* _Nullable uid;
```
用户 ID，必填。


<span id="ByteRTCVideoCanvas-backgroundcolor"></span>
### backgroundColor
```objectivec
@property(assign, nonatomic) NSInteger backgroundColor;
```
用于填充画布空白部分的背景颜色。取值范围是 `[0x00000000, 0xFFFFFFFF]`,格式为 BGR。默认值是 `0x00000000`。其中，透明度设置无效。



# ByteRTCFrameExtendedData
```objectivec
@interface ByteRTCFrameExtendedData : NSObject
```

视频帧附加的数据,视频解码后获得的附加数据


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCDataFrameType** | [frameType](#ByteRTCFrameExtendedData-frametype) |
| **NSData*** | [extendedData](#ByteRTCFrameExtendedData-extendeddata) |
| **NSInteger** | [extendedDataLen](#ByteRTCFrameExtendedData-extendeddatalen) |


## 变量说明
<span id="ByteRTCFrameExtendedData-frametype"></span>
### frameType
```objectivec
@property(assign, nonatomic) ByteRTCDataFrameType frameType;
```
数据类型，详见 [ByteRTCDataFrameType](#bytertcdataframetype)。


<span id="ByteRTCFrameExtendedData-extendeddata"></span>
### extendedData
```objectivec
@property(strong, nonatomic) NSData * _Nullable extendedData;
```
附加数据


<span id="ByteRTCFrameExtendedData-extendeddatalen"></span>
### extendedDataLen
```objectivec
@property(assign, nonatomic) NSInteger extendedDataLen;
```
附加数据长度



# ByteRTCVideoCaptureConfig
```objectivec
@interface ByteRTCVideoCaptureConfig: NSObject
```

视频采集参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCVideoCapturePreference** | [preference](#ByteRTCVideoCaptureConfig-preference) |
| **CGSize** | [videoSize](#ByteRTCVideoCaptureConfig-videosize) |
| **NSInteger** | [frameRate](#ByteRTCVideoCaptureConfig-framerate) |


## 变量说明
<span id="ByteRTCVideoCaptureConfig-preference"></span>
### preference
```objectivec
@property(nonatomic, assign) ByteRTCVideoCapturePreference preference;
```
视频采集模式，参看 [ByteRTCVideoCapturePreference](#bytertcvideocapturepreference)


<span id="ByteRTCVideoCaptureConfig-videosize"></span>
### videoSize
```objectivec
@property(nonatomic, assign) CGSize videoSize;
```
视频采集分辨率


<span id="ByteRTCVideoCaptureConfig-framerate"></span>
### frameRate
```objectivec
@property(nonatomic, assign) NSInteger frameRate;
```
视频采集帧率，单位：fps。



# ByteRTCSubscribeConfig
```objectivec
@interface ByteRTCSubscribeConfig: NSObject
```

订阅流的参数配置。用户手动订阅一路音视频流所使用的订阅配置参数。  <br>
用户关闭自动订阅功能，使用手动订阅模式时，通过调用 `subscribeStream` 方法订阅音视频流，调用时传入的参数即为此数据类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **BOOL** | [isScreen](#ByteRTCSubscribeConfig-isscreen) |
| **BOOL** | [subscribeVideo](#ByteRTCSubscribeConfig-subscribevideo) |
| **BOOL** | [subscribeAudio](#ByteRTCSubscribeConfig-subscribeaudio) |
| **NSInteger** | [videoIndex](#ByteRTCSubscribeConfig-videoindex) |
| **NSInteger** | [svcLayer](#ByteRTCSubscribeConfig-svclayer) |
| **NSInteger** | [width](#ByteRTCSubscribeConfig-width) |
| **NSInteger** | [height](#ByteRTCSubscribeConfig-height) |
| **NSInteger** | [framerate](#ByteRTCSubscribeConfig-framerate) |


## 变量说明
<span id="ByteRTCSubscribeConfig-isscreen"></span>
### isScreen
```objectivec
@property(nonatomic, assign) BOOL isScreen;
```
是否是屏幕流。  <br>
用户通过设置此参数，订阅该远端用户发布的屏幕共享流或非屏幕共享流。 YES 为订阅屏幕共享流，NO 为订阅非屏幕共享流，默认值为 YES 。  <br>


<span id="ByteRTCSubscribeConfig-subscribevideo"></span>
### subscribeVideo
```objectivec
@property(nonatomic, assign) BOOL subscribeVideo;
```
是否订阅视频。  <br>
用户通过设置此参数，选择是否订阅远端流中的视频。 YES 为订阅视频，NO 为不订阅视频，默认值为 YES 。  <br>


<span id="ByteRTCSubscribeConfig-subscribeaudio"></span>
### subscribeAudio
```objectivec
@property(nonatomic, assign) BOOL subscribeAudio;
```
是否订阅音频。  <br>
用户通过设置此参数，选择是否订阅远端流中的音频。YES 为订阅音频，NO 为不订阅音频，默认值为 YES 。  <br>


<span id="ByteRTCSubscribeConfig-videoindex"></span>
### videoIndex
```objectivec
@property(nonatomic, assign) NSInteger videoIndex;
```
订阅的视频流分辨率下标。  <br>
用户可以通过调用 [SetVideoEncoderConfig:](iOS-api.md#ByteRTCVideo-setvideoencoderconfig) 方法发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>


<span id="ByteRTCSubscribeConfig-svclayer"></span>
### svcLayer
```objectivec
@property(nonatomic, assign) NSInteger svcLayer;
```
订阅的视频流时域分层，默认值为 0。  <br>


<span id="ByteRTCSubscribeConfig-width"></span>
### width
```objectivec
@property(nonatomic, assign) NSInteger width;
```
订阅的宽度信息，单位：px，默认值为 0。 <br>


<span id="ByteRTCSubscribeConfig-height"></span>
### height
```objectivec
@property(nonatomic, assign) NSInteger height;
```
订阅的高度信息，单位：px， 默认值为0。


<span id="ByteRTCSubscribeConfig-framerate"></span>
### framerate
```objectivec
@property (nonatomic, assign) NSInteger framerate;
```
期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。  <br>
当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
仅码流支持 SVC 分级编码特性时方可生效。



# ByteRTCVideoFrame
```objectivec
@interface ByteRTCVideoFrame : NSObject
```

待 SDK 编码的视频数据


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [format](#ByteRTCVideoFrame-format) |
| **ByteRTCVideoContentType** | [contentType](#ByteRTCVideoFrame-contenttype) |
| **CMTime** | [time](#ByteRTCVideoFrame-time) |
| **int** | [strideInPixels](#ByteRTCVideoFrame-strideinpixels) |
| **int** | [width](#ByteRTCVideoFrame-width) |
| **int** | [height](#ByteRTCVideoFrame-height) |
| **CVPixelBufferRef** | [textureBuf](#ByteRTCVideoFrame-texturebuf) |
| **NSData*** | [dataBuf](#ByteRTCVideoFrame-databuf) |
| **int** | [cropLeft](#ByteRTCVideoFrame-cropleft) |
| **int** | [cropTop](#ByteRTCVideoFrame-croptop) |
| **int** | [cropRight](#ByteRTCVideoFrame-cropright) |
| **int** | [cropBottom](#ByteRTCVideoFrame-cropbottom) |
| **ByteRTCVideoRotation** | [rotation](#ByteRTCVideoFrame-rotation) |
| **ByteRTCCameraID** | [cameraId](#ByteRTCVideoFrame-cameraid) |
| **ByteRTCFrameExtendedData*** | [extendedData](#ByteRTCVideoFrame-extendeddata) |


## 变量说明
<span id="ByteRTCVideoFrame-format"></span>
### format
```objectivec
@property(assign, nonatomic) int format;
```
视频帧格式，参考 [ByteRTCVideoPixelFormat](#bytertcvideopixelformat)


<span id="ByteRTCVideoFrame-contenttype"></span>
### contentType
```objectivec
@property(assign, nonatomic) ByteRTCVideoContentType contentType;
```
获取视频内容类型，参看 [ByteRTCVideoContentType](#bytertcvideocontenttype)


<span id="ByteRTCVideoFrame-time"></span>
### time
```objectivec
@property(assign, nonatomic) CMTime time;
```
当前帧的时间戳信息


<span id="ByteRTCVideoFrame-strideinpixels"></span>
### strideInPixels
```objectivec
@property(assign, nonatomic) int strideInPixels;
```
每一行像素占用的字节数


<span id="ByteRTCVideoFrame-width"></span>
### width
```objectivec
@property(assign, nonatomic) int width;
```
视频帧宽度


<span id="ByteRTCVideoFrame-height"></span>
### height
```objectivec
@property(assign, nonatomic) int height;
```
视频帧高度


<span id="ByteRTCVideoFrame-texturebuf"></span>
### textureBuf
```objectivec
@property(assign, nonatomic) CVPixelBufferRef _Nullable textureBuf;
```
CVPixelBufferRef 类型的数据，当 format 为 kPixelFormatCVPixelBuffer 时有效


<span id="ByteRTCVideoFrame-databuf"></span>
### dataBuf
```objectivec
@property(strong, nonatomic) NSData * _Nullable dataBuf;
```
视频帧内存块首地址


<span id="ByteRTCVideoFrame-cropleft"></span>
### cropLeft
```objectivec
@property(assign, nonatomic) int cropLeft;
```
视频帧左侧被裁剪的尺寸（像素）


<span id="ByteRTCVideoFrame-croptop"></span>
### cropTop
```objectivec
@property(assign, nonatomic) int cropTop;
```
视频帧上部被裁剪的尺寸（像素）


<span id="ByteRTCVideoFrame-cropright"></span>
### cropRight
```objectivec
@property(assign, nonatomic) int cropRight;
```
视频帧右侧被裁剪的尺寸（像素）


<span id="ByteRTCVideoFrame-cropbottom"></span>
### cropBottom
```objectivec
@property(assign, nonatomic) int cropBottom;
```
视频帧底部被裁剪的尺寸（像素）


<span id="ByteRTCVideoFrame-rotation"></span>
### rotation
```objectivec
@property(assign, nonatomic) ByteRTCVideoRotation rotation;
```
视频帧旋转角度：0, 90, 180, 270


<span id="ByteRTCVideoFrame-cameraid"></span>
### cameraId
```objectivec
@property(assign, nonatomic) ByteRTCCameraID cameraId;
```
视频帧的摄像头信息，参考 [ByteRTCCameraID](#bytertccameraid)


<span id="ByteRTCVideoFrame-extendeddata"></span>
### extendedData
```objectivec
@property(strong, nonatomic) ByteRTCFrameExtendedData * _Nullable extendedData;
```
视频帧附加的数据



# ByteRTCEncodedVideoFrame
```objectivec
@interface ByteRTCEncodedVideoFrame : NSObject
```

视频帧信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCVideoCodecType** | [codecType](#ByteRTCEncodedVideoFrame-codectype) |
| **ByteRTCVideoPictureType** | [pictureType](#ByteRTCEncodedVideoFrame-picturetype) |
| **SInt64** | [timestampUs](#ByteRTCEncodedVideoFrame-timestampus) |
| **SInt64** | [timestampDtsUs](#ByteRTCEncodedVideoFrame-timestampdtsus) |
| **int** | [width](#ByteRTCEncodedVideoFrame-width) |
| **int** | [height](#ByteRTCEncodedVideoFrame-height) |
| **ByteRTCVideoRotation** | [rotation](#ByteRTCEncodedVideoFrame-rotation) |
| **NSData*** | [data](#ByteRTCEncodedVideoFrame-data) |


## 变量说明
<span id="ByteRTCEncodedVideoFrame-codectype"></span>
### codecType
```objectivec
@property(assign, nonatomic) ByteRTCVideoCodecType codecType;
```
视频编码类型。参看 [ByteRTCVideoCodecType](#bytertcvideocodectype)


<span id="ByteRTCEncodedVideoFrame-picturetype"></span>
### pictureType
```objectivec
@property(assign, nonatomic) ByteRTCVideoPictureType pictureType;
```
视频帧类型。参看 [ByteRTCVideoPictureType](#bytertcvideopicturetype)


<span id="ByteRTCEncodedVideoFrame-timestampus"></span>
### timestampUs
```objectivec
@property(assign, nonatomic) SInt64 timestampUs;
```
视频采集时间戳，单位：微秒


<span id="ByteRTCEncodedVideoFrame-timestampdtsus"></span>
### timestampDtsUs
```objectivec
@property(assign, nonatomic) SInt64 timestampDtsUs;
```
视频编码时间戳，单位：微秒


<span id="ByteRTCEncodedVideoFrame-width"></span>
### width
```objectivec
@property(assign, nonatomic) int width;
```
视频帧宽，单位：px


<span id="ByteRTCEncodedVideoFrame-height"></span>
### height
```objectivec
@property(assign, nonatomic) int height;
```
视频帧高，单位：px


<span id="ByteRTCEncodedVideoFrame-rotation"></span>
### rotation
```objectivec
@property(nonatomic, assign) ByteRTCVideoRotation rotation;
```
视频帧旋转角度。参看 [ByteRTCVideoRotation](#bytertcvideorotation)


<span id="ByteRTCEncodedVideoFrame-data"></span>
### data
```objectivec
@property(strong, nonatomic) NSData * _Nonnull data;
```
视频帧数据指针地址



# ByteRTCTranscoderLayoutRegionDataParam
```objectivec
@interface ByteRTCTranscoderLayoutRegionDataParam : NSObject
```

图片合流相关参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [imageWidth](#ByteRTCTranscoderLayoutRegionDataParam-imagewidth) |
| **NSInteger** | [imageHeight](#ByteRTCTranscoderLayoutRegionDataParam-imageheight) |


## 变量说明
<span id="ByteRTCTranscoderLayoutRegionDataParam-imagewidth"></span>
### imageWidth
```objectivec
@property (assign, nonatomic) NSInteger imageWidth;
```
原始图片的宽度，单位为 px。


<span id="ByteRTCTranscoderLayoutRegionDataParam-imageheight"></span>
### imageHeight
```objectivec
@property (assign, nonatomic) NSInteger imageHeight;
```
原始图片的高度，单位为 px。



# ByteRTCVideoCompositingRegion
```objectivec
@interface ByteRTCVideoCompositingRegion : NSObject
```

单个图片或视频流在合流中的布局信息。  <br>
开启转推直播功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [uid](#ByteRTCVideoCompositingRegion-uid) |
| **NSString*** | [roomId](#ByteRTCVideoCompositingRegion-roomid) |
| **CGFloat** | [x](#ByteRTCVideoCompositingRegion-x) |
| **CGFloat** | [y](#ByteRTCVideoCompositingRegion-y) |
| **CGFloat** | [width](#ByteRTCVideoCompositingRegion-width) |
| **CGFloat** | [height](#ByteRTCVideoCompositingRegion-height) |
| **NSInteger** | [zOrder](#ByteRTCVideoCompositingRegion-zorder) |
| **BOOL** | [localUser](#ByteRTCVideoCompositingRegion-localuser) |
| **BOOL** | [screenStream](#ByteRTCVideoCompositingRegion-screenstream) |
| **CGFloat** | [alpha](#ByteRTCVideoCompositingRegion-alpha) |
| **ByteRTCTranscoderContentControlType** | [contentControl](#ByteRTCVideoCompositingRegion-contentcontrol) |
| **ByteRTCRenderMode** | [renderMode](#ByteRTCVideoCompositingRegion-rendermode) |
| **ByteRTCTranscoderLayoutRegionType** | [type](#ByteRTCVideoCompositingRegion-type) |
| **NSData*** | [data](#ByteRTCVideoCompositingRegion-data) |
| **ByteRTCTranscoderLayoutRegionDataParam*** | [dataParam](#ByteRTCVideoCompositingRegion-dataparam) |


## 变量说明
<span id="ByteRTCVideoCompositingRegion-uid"></span>
### uid
```objectivec
@property(copy, nonatomic) NSString * _Nonnull uid;
```
视频流发布用户的用户 ID 。必填。


<span id="ByteRTCVideoCompositingRegion-roomid"></span>
### roomId
```objectivec
@property(copy, nonatomic) NSString * _Nonnull roomId;
```
图片或视频流所在房间的房间 ID。必填。<br>
如果此图片或视频流是通过 [startForwardStreamToRooms:](iOS-api.md#ByteRTCRoom-startforwardstreamtorooms) 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。


<span id="ByteRTCVideoCompositingRegion-x"></span>
### x
```objectivec
@property(assign, nonatomic) CGFloat x;
```
视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。


<span id="ByteRTCVideoCompositingRegion-y"></span>
### y
```objectivec
@property(assign, nonatomic) CGFloat y;
```
视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。


<span id="ByteRTCVideoCompositingRegion-width"></span>
### width
```objectivec
@property(assign, nonatomic) CGFloat width;
```
视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。


<span id="ByteRTCVideoCompositingRegion-height"></span>
### height
```objectivec
@property(assign, nonatomic) CGFloat height;
```
视频流对应区域高度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。


<span id="ByteRTCVideoCompositingRegion-zorder"></span>
### zOrder
```objectivec
@property(assign, nonatomic) NSInteger zOrder;
```
用户视频布局在画布中的层级。0为底层，值越大越上层，范围为[0 - 100]。


<span id="ByteRTCVideoCompositingRegion-localuser"></span>
### localUser
```objectivec
@property(assign, nonatomic) BOOL localUser;
```
是否为本地用户


<span id="ByteRTCVideoCompositingRegion-screenstream"></span>
### screenStream
```objectivec
@property(assign, nonatomic) BOOL screenStream;
```
是否为屏幕流，默认为NO


<span id="ByteRTCVideoCompositingRegion-alpha"></span>
### alpha
```objectivec
@property(assign, nonatomic) CGFloat alpha;
```
透明度，可选范围为 [0.0, 1.0]，0.0 为全透明。


<span id="ByteRTCVideoCompositingRegion-contentcontrol"></span>
### contentControl
```objectivec
@property (assign, nonatomic) ByteRTCTranscoderContentControlType contentControl;
```
合流内容控制。默认值为 `ByteRTCTranscoderContentControlTypeHasAudioAndVideo`，参看 [ByteRTCTranscoderContentControlType](#bytertctranscodercontentcontroltype) 。


<span id="ByteRTCVideoCompositingRegion-rendermode"></span>
### renderMode
```objectivec
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
```
视频显示模式。详见 [ByteRTCRenderMode](#bytertcrendermode) 数据类型。  <br>


<span id="ByteRTCVideoCompositingRegion-type"></span>
### type
```objectivec
@property (assign, nonatomic) ByteRTCTranscoderLayoutRegionType type;
```
合流布局区域类型。参看 [ByteRTCTranscoderLayoutRegionType](#bytertctranscoderlayoutregiontype)。


<span id="ByteRTCVideoCompositingRegion-data"></span>
### data
```objectivec
@property (strong, nonatomic) NSData * _Nullable data;
```
图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。


<span id="ByteRTCVideoCompositingRegion-dataparam"></span>
### dataParam
```objectivec
@property (strong, nonatomic) ByteRTCTranscoderLayoutRegionDataParam * _Nullable dataParam;
```
合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 [ByteRTCTranscoderLayoutRegionDataParam](#bytertctranscoderlayoutregiondataparam)。



# ByteRTCVideoCompositingLayout
```objectivec
@interface ByteRTCVideoCompositingLayout : NSObject
```

视频流合流整体布局信息。  <br>
开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [backgroundColor](#ByteRTCVideoCompositingLayout-backgroundcolor) |
| **NSArray<ByteRTCVideoCompositingRegion*>*** | [regions](#ByteRTCVideoCompositingLayout-regions) |
| **NSString*** | [appData](#ByteRTCVideoCompositingLayout-appdata) |


## 变量说明
<span id="ByteRTCVideoCompositingLayout-backgroundcolor"></span>
### backgroundColor
```objectivec
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
```
画布的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色


<span id="ByteRTCVideoCompositingLayout-regions"></span>
### regions
```objectivec
@property(copy, nonatomic) NSArray<ByteRTCVideoCompositingRegion *> * _Nonnull regions;
```
用户布局信息列表。每条流的具体布局详见 [ByteRTCVideoCompositingRegion](#bytertcvideocompositingregion) 数据类型。


<span id="ByteRTCVideoCompositingLayout-appdata"></span>
### appData
```objectivec
@property(copy, nonatomic) NSString *_Nonnull appData;
```
透传的 App 数据。长度不超过 4KB。



# ByteRTCTranscodingVideoConfig
```objectivec
@interface ByteRTCTranscodingVideoConfig : NSObject
```

视频转码配置参数。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [codec](#ByteRTCTranscodingVideoConfig-codec) |
| **NSInteger** | [width](#ByteRTCTranscodingVideoConfig-width) |
| **NSInteger** | [height](#ByteRTCTranscodingVideoConfig-height) |
| **NSInteger** | [fps](#ByteRTCTranscodingVideoConfig-fps) |
| **NSInteger** | [gop](#ByteRTCTranscodingVideoConfig-gop) |
| **NSInteger** | [kBitRate](#ByteRTCTranscodingVideoConfig-kbitrate) |
| **BOOL** | [lowLatency](#ByteRTCTranscodingVideoConfig-lowlatency) |


## 变量说明
<span id="ByteRTCTranscodingVideoConfig-codec"></span>
### codec
```objectivec
@property(copy, nonatomic) NSString * _Nonnull codec;
```
codec 编码器。本参数不支持过程中更新。默认值为 `0`。 <br>

+ 值为 `0` 时，使用 H.264； <br>
+ 值为 `1` 时，使用 byteVC1。此时，你必须指明 [ByteRTCTranscodingVideoConfig](#bytertctranscodingvideoconfig) 的视频码率。


<span id="ByteRTCTranscodingVideoConfig-width"></span>
### width
```objectivec
@property(assign, nonatomic) NSInteger width;
```
合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640。


<span id="ByteRTCTranscodingVideoConfig-height"></span>
### height
```objectivec
@property(assign, nonatomic) NSInteger height;
```
合流视频高度。单位为 px，范围为 [2, 1080]，必须是偶数。默认值为 480。


<span id="ByteRTCTranscodingVideoConfig-fps"></span>
### fps
```objectivec
@property(assign, nonatomic) NSInteger fps;
```
合流的视频帧率。默认值为 `15`，取值范围是 `[1, 60]`。值不合法时，自动调整为默认值。


<span id="ByteRTCTranscodingVideoConfig-gop"></span>
### gop
```objectivec
@property(assign, nonatomic) NSInteger gop;
```
I 帧间隔。默认值为 `4`，取值范围为 `[1, 5]`，单位为秒。值不合法时，自动调整为默认值。


<span id="ByteRTCTranscodingVideoConfig-kbitrate"></span>
### kBitRate
```objectivec
@property(assign, nonatomic) NSInteger kBitRate;
```
合流视频码率。单位为 kbps，取值范围为 `[1,10000]`，默认值为自适应。值不合法时，自动调整为默认值。


<span id="ByteRTCTranscodingVideoConfig-lowlatency"></span>
### lowLatency
```objectivec
@property(assign, nonatomic) BOOL lowLatency;
```
是否使用低延时特性。



# ByteRTCTranscodingAudioConfig
```objectivec
@interface ByteRTCTranscodingAudioConfig : NSObject
```

音频转码配置参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [codec](#ByteRTCTranscodingAudioConfig-codec) |
| **NSInteger** | [sampleRate](#ByteRTCTranscodingAudioConfig-samplerate) |
| **NSInteger** | [channels](#ByteRTCTranscodingAudioConfig-channels) |
| **NSInteger** | [kBitRate](#ByteRTCTranscodingAudioConfig-kbitrate) |
| **ByteRTCAACProfile** | [profile](#ByteRTCTranscodingAudioConfig-profile) |


## 变量说明
<span id="ByteRTCTranscodingAudioConfig-codec"></span>
### codec
```objectivec
@property(copy, nonatomic) NSString * _Nonnull codec;
```
音频编码格式，仅支持`AAC`编码格式。


<span id="ByteRTCTranscodingAudioConfig-samplerate"></span>
### sampleRate
```objectivec
@property(assign, nonatomic) NSInteger sampleRate;
```
音频采样率，单位 Hz。可取 32000Hz、44100Hz、48000Hz，默认值为 48000Hz。


<span id="ByteRTCTranscodingAudioConfig-channels"></span>
### channels
```objectivec
@property(assign, nonatomic) NSInteger channels;
```
音频声道数。可取 1、2，默认值为 2。


<span id="ByteRTCTranscodingAudioConfig-kbitrate"></span>
### kBitRate
```objectivec
@property(assign, nonatomic) NSInteger kBitRate;
```
音频码率，单位 Kbps。可取范围 [32Kbps, 192Kbps]，默认值为 64Kbps。


<span id="ByteRTCTranscodingAudioConfig-profile"></span>
### profile
```objectivec
@property(assign, nonatomic) ByteRTCAACProfile profile;
```
AAC 等级，参看 [ByteRTCAACProfile](#bytertcaacprofile)。默认值为 `0`。



# ByteRTCLiveTranscoding
```objectivec
@interface ByteRTCLiveTranscoding : NSObject
```

转推直播配置参数。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCStreamMixingType** | [expectedMixingType](#ByteRTCLiveTranscoding-expectedmixingtype) |
| **ByteRTCVideoCompositingLayout*** | [layout](#ByteRTCLiveTranscoding-layout) |
| **ByteRTCTranscodingVideoConfig*** | [video](#ByteRTCLiveTranscoding-video) |
| **ByteRTCTranscodingAudioConfig*** | [audio](#ByteRTCLiveTranscoding-audio) |
| **NSMutableDictionary*** | [authInfo](#ByteRTCLiveTranscoding-authinfo) |
| **NSString*** | [url](#ByteRTCLiveTranscoding-url) |
| **NSString*** | [roomId](#ByteRTCLiveTranscoding-roomid) |
| **NSString*** | [userId](#ByteRTCLiveTranscoding-userid) |


## 静态函数

| 返回 | 名称 |
| --- | --- |
| **instancetype** | [defaultTranscoding](#ByteRTCLiveTranscoding-defaulttranscoding) |


## 变量说明
<span id="ByteRTCLiveTranscoding-expectedmixingtype"></span>
### expectedMixingType
```objectivec
@property(assign, nonatomic) ByteRTCStreamMixingType expectedMixingType;
```
合流类型。本参数不支持过程中更新。详见 [ByteRTCStreamMixingType](#bytertcstreammixingtype) 数据类型。


<span id="ByteRTCLiveTranscoding-layout"></span>
### layout
```objectivec
@property(strong, nonatomic) ByteRTCVideoCompositingLayout * _Nonnull layout;
```
视频流合流整体布局信息。  <br>
开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。详见 [ByteRTCVideoCompositingLayout](#bytertcvideocompositinglayout) 数据类型。


<span id="ByteRTCLiveTranscoding-video"></span>
### video
```objectivec
@property(strong, nonatomic) ByteRTCTranscodingVideoConfig * _Nonnull video;
```
视频转码配置参数。详见 [ByteRTCTranscodingVideoConfig](#bytertctranscodingvideoconfig) 数据类型。


<span id="ByteRTCLiveTranscoding-audio"></span>
### audio
```objectivec
@property(strong, nonatomic) ByteRTCTranscodingAudioConfig * _Nonnull audio;
```
音频转码配置参数。本参数不支持过程中更新。详见 [ByteRTCTranscodingAudioConfig](#bytertctranscodingaudioconfig) 数据类型。


<span id="ByteRTCLiveTranscoding-authinfo"></span>
### authInfo
```objectivec
@property(strong, nonatomic) NSMutableDictionary *  _Nullable authInfo;
```
业务透传鉴权信息


<span id="ByteRTCLiveTranscoding-url"></span>
### url
```objectivec
@property(copy, nonatomic) NSString * _Nullable url;
```
推流 CDN 地址。本参数不支持过程中更新。


<span id="ByteRTCLiveTranscoding-roomid"></span>
### roomId
```objectivec
@property(copy, nonatomic) NSString * _Nonnull roomId;
```
推流房间 ID，必填。本参数不支持过程中更新。


<span id="ByteRTCLiveTranscoding-userid"></span>
### userId
```objectivec
@property(copy, nonatomic) NSString * _Nonnull userId;
```
推流用户 ID。本参数不支持过程中更新。



## 函数说明
<span id="ByteRTCLiveTranscoding-defaulttranscoding"></span>
### defaultTranscoding
```objectivec

+ (instancetype _Nonnull)defaultTranscoding;
```
获取默认转推直播配置参数。

**返回值**
转推直播配置参数，参看 [ByteRTCLiveTranscoding](#bytertclivetranscoding)。


# ByteRTCPushSingleStreamParam
```objectivec
@interface ByteRTCPushSingleStreamParam : NSObject
```

单流转推直播配置参数。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [url](#ByteRTCPushSingleStreamParam-url) |
| **NSString*** | [roomId](#ByteRTCPushSingleStreamParam-roomid) |
| **NSString*** | [userId](#ByteRTCPushSingleStreamParam-userid) |
| **BOOL** | [isScreen](#ByteRTCPushSingleStreamParam-isscreen) |


## 变量说明
<span id="ByteRTCPushSingleStreamParam-url"></span>
### url
```objectivec
@property(copy, nonatomic) NSString * _Nullable url;
```
推流地址


<span id="ByteRTCPushSingleStreamParam-roomid"></span>
### roomId
```objectivec
@property(copy, nonatomic) NSString * _Nonnull roomId;
```
媒体流所在的房间 ID


<span id="ByteRTCPushSingleStreamParam-userid"></span>
### userId
```objectivec
@property(copy, nonatomic) NSString * _Nullable userId;
```
媒体流所属的用户 ID


<span id="ByteRTCPushSingleStreamParam-isscreen"></span>
### isScreen
```objectivec
@property(nonatomic, assign) BOOL isScreen;
```
媒体流是否为屏幕流。



# ByteRTCSubscribeVideoConfig
```objectivec
@interface ByteRTCSubscribeVideoConfig : NSObject
```

视频订阅配置信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [videoIndex](#ByteRTCSubscribeVideoConfig-videoindex) |
| **NSInteger** | [priority](#ByteRTCSubscribeVideoConfig-priority) |


## 变量说明
<span id="ByteRTCSubscribeVideoConfig-videoindex"></span>
### videoIndex
```objectivec
@property(assign, nonatomic) NSInteger videoIndex;
```
订阅的视频流分辨率下标。  <br>
当远端用户通过调用 [enableSimulcastMode:](iOS-api.md#ByteRTCVideo-enablesimulcastmode) 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
默认值为 0，即订阅第一路流。  <br>
如果不想更改之前的设置，可以输入 -1。  <br>


<span id="ByteRTCSubscribeVideoConfig-priority"></span>
### priority
```objectivec
@property(assign, nonatomic) NSInteger priority;
```
远端用户优先级，参看 [ByteRTCRemoteUserPriority](#bytertcremoteuserpriority)，默认值为 0。



# ByteRTCSourceWantedData
```objectivec
@interface ByteRTCSourceWantedData : NSObject
```

性能回退相关数据


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [width](#ByteRTCSourceWantedData-width) |
| **NSInteger** | [height](#ByteRTCSourceWantedData-height) |
| **NSInteger** | [frameRate](#ByteRTCSourceWantedData-framerate) |


## 变量说明
<span id="ByteRTCSourceWantedData-width"></span>
### width
```objectivec
@property(nonatomic, assign) NSInteger width;
```
推荐视频输入宽


<span id="ByteRTCSourceWantedData-height"></span>
### height
```objectivec
@property(nonatomic, assign) NSInteger height;
```
推荐视频输入高


<span id="ByteRTCSourceWantedData-framerate"></span>
### frameRate
```objectivec
@property(nonatomic, assign) NSInteger frameRate;
```
推荐视频输入帧率



# ByteRTCRemoteStreamSwitchEvent
```objectivec
@interface ByteRTCRemoteStreamSwitchEvent : NSObject
```

流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [uid](#ByteRTCRemoteStreamSwitchEvent-uid) |
| **BOOL** | [isScreen](#ByteRTCRemoteStreamSwitchEvent-isscreen) |
| **NSInteger** | [beforeVideoIndex](#ByteRTCRemoteStreamSwitchEvent-beforevideoindex) |
| **NSInteger** | [afterVideoIndex](#ByteRTCRemoteStreamSwitchEvent-aftervideoindex) |
| **BOOL** | [beforeVideoEnabled](#ByteRTCRemoteStreamSwitchEvent-beforevideoenabled) |
| **BOOL** | [afterVideoEnabled](#ByteRTCRemoteStreamSwitchEvent-aftervideoenabled) |
| **ByteRTCFallbackOrRecoverReason** | [reason](#ByteRTCRemoteStreamSwitchEvent-reason) |


## 变量说明
<span id="ByteRTCRemoteStreamSwitchEvent-uid"></span>
### uid
```objectivec
@property(nonatomic, copy) NSString * _Nonnull uid;
```
订阅的音视频流的发布者的用户 ID。


<span id="ByteRTCRemoteStreamSwitchEvent-isscreen"></span>
### isScreen
```objectivec
@property(nonatomic, assign) BOOL isScreen;
```
流是否是屏幕流


<span id="ByteRTCRemoteStreamSwitchEvent-beforevideoindex"></span>
### beforeVideoIndex
```objectivec
@property(nonatomic, assign) NSInteger beforeVideoIndex;
```
流切换前订阅视频流的分辨率对应的索引


<span id="ByteRTCRemoteStreamSwitchEvent-aftervideoindex"></span>
### afterVideoIndex
```objectivec
@property(nonatomic, assign) NSInteger afterVideoIndex;
```
流切换后订阅视频流的分辨率对应的索引


<span id="ByteRTCRemoteStreamSwitchEvent-beforevideoenabled"></span>
### beforeVideoEnabled
```objectivec
@property(nonatomic, assign) BOOL beforeVideoEnabled;
```
流切换前是否有视频流


<span id="ByteRTCRemoteStreamSwitchEvent-aftervideoenabled"></span>
### afterVideoEnabled
```objectivec
@property(nonatomic, assign) BOOL afterVideoEnabled;
```
流切换后是否有视频流


<span id="ByteRTCRemoteStreamSwitchEvent-reason"></span>
### reason
```objectivec
@property(nonatomic, assign) ByteRTCFallbackOrRecoverReason reason;
```
流切换原因，详见 [ByteRTCFallbackOrRecoverReason](#bytertcfallbackorrecoverreason)。



# ByteRTCVideoSinkDelegate
```objectivec
@protocol ByteRTCVideoSinkDelegate <NSObject>
```

自定义视频渲染器


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [renderPixelBuffer:rotation:contentType:extendedData:](#ByteRTCVideoSinkDelegate-renderpixelbuffer-rotation-contenttype-extendeddata) |


## 函数说明
<span id="ByteRTCVideoSinkDelegate-renderpixelbuffer-rotation-contenttype-extendeddata"></span>
### renderPixelBuffer:rotation:contentType:extendedData:
```objectivec

- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer rotation:(ByteRTCVideoRotation)rotation contentType:(ByteRTCVideoContentType)contentType extendedData:(NSData * _Nullable)extendedData;
```
输出视频的 PixelBuffer

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| pixelBuffer | **CVPixelBufferRef** | 视频的 PixelBuffer |
| rotation | **ByteRTCVideoRotation** | 视频旋转角度，参看 [ByteRTCVideoRotation](#bytertcvideorotation) |
| contentType | **ByteRTCVideoContentType** | 视频内部类型 参看 [ByteRTCVideoContentType](#bytertcvideocontenttype) |
| extendedData | **NSData*** | 视频解码后获得的附加数据 |


# ByteRTCVideoPreprocessorConfig
```objectivec
@interface ByteRTCVideoPreprocessorConfig : NSObject
```

视频处理配置参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCVideoPixelFormat** | [required_pixel_format](#ByteRTCVideoPreprocessorConfig-required_pixel_format) |


## 变量说明
<span id="ByteRTCVideoPreprocessorConfig-required_pixel_format"></span>
### required_pixel_format
```objectivec
@property(nonatomic, assign) ByteRTCVideoPixelFormat required_pixel_format;
```
视频帧的像素格式，参看 [ByteRTCVideoPixelFormat](#bytertcvideopixelformat)。



# ByteRTCScreenCaptureParam
```objectivec
@interface ByteRTCScreenCaptureParam : NSObject
```

屏幕采集设置参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [width](#ByteRTCScreenCaptureParam-width) |
| **NSInteger** | [height](#ByteRTCScreenCaptureParam-height) |
| **NSInteger** | [frameRate](#ByteRTCScreenCaptureParam-framerate) |
| **NSInteger** | [bitrate](#ByteRTCScreenCaptureParam-bitrate) |
| **CGRect** | [regionRect](#ByteRTCScreenCaptureParam-regionrect) |
| **ByteRTCMouseCursorCaptureState** | [mouseCursorCaptureState](#ByteRTCScreenCaptureParam-mousecursorcapturestate) |
| **NSArray<NSNumber*>*** | [excludedWindowList](#ByteRTCScreenCaptureParam-excludedwindowlist) |
| **ByteRTCHighlightConfig*** | [highlightConfig](#ByteRTCScreenCaptureParam-highlightconfig) |


## 变量说明
<span id="ByteRTCScreenCaptureParam-width"></span>
### width
```objectivec
@property(nonatomic, assign) NSInteger width;
```
屏幕采集宽度


<span id="ByteRTCScreenCaptureParam-height"></span>
### height
```objectivec
@property(nonatomic, assign) NSInteger height;
```
屏幕采集高度


<span id="ByteRTCScreenCaptureParam-framerate"></span>
### frameRate
```objectivec
@property(nonatomic, assign) NSInteger frameRate;
```
屏幕采集帧率，单位 fps


<span id="ByteRTCScreenCaptureParam-bitrate"></span>
### bitrate
```objectivec
@property(nonatomic, assign) NSInteger bitrate;
```
发送屏幕采集码率，单位 kbps


<span id="ByteRTCScreenCaptureParam-regionrect"></span>
### regionRect
```objectivec
@property(nonatomic, assign) CGRect regionRect;
```
采集区域


<span id="ByteRTCScreenCaptureParam-mousecursorcapturestate"></span>
### mouseCursorCaptureState
```objectivec
@property(nonatomic, assign) ByteRTCMouseCursorCaptureState mouseCursorCaptureState;
```
是否采集鼠标


<span id="ByteRTCScreenCaptureParam-excludedwindowlist"></span>
### excludedWindowList
```objectivec
@property (strong, nonatomic) NSArray<NSNumber *> * _Nullable excludedWindowList;
```
屏幕过滤设置


<span id="ByteRTCScreenCaptureParam-highlightconfig"></span>
### highlightConfig
```objectivec
@property (strong, nonatomic) ByteRTCHighlightConfig * _Nonnull highlightConfig;
```
采集区域的边框高亮设置，参看 [ByteRTCHighlightConfig](#bytertchighlightconfig)。



# ByteRTCScreenCaptureSourceInfo
```objectivec
@interface ByteRTCScreenCaptureSourceInfo : NSObject
```

屏幕采集对象的具体信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCScreenCaptureSourceType** | [sourceType](#ByteRTCScreenCaptureSourceInfo-sourcetype) |
| **intptr_t** | [sourceId](#ByteRTCScreenCaptureSourceInfo-sourceid) |
| **NSString*** | [sourceName](#ByteRTCScreenCaptureSourceInfo-sourcename) |


## 变量说明
<span id="ByteRTCScreenCaptureSourceInfo-sourcetype"></span>
### sourceType
```objectivec
@property (assign, nonatomic) ByteRTCScreenCaptureSourceType sourceType;
```
屏幕分享时，共享对象的类型，参看 [ByteRTCScreenCaptureSourceType](#bytertcscreencapturesourcetype)


<span id="ByteRTCScreenCaptureSourceInfo-sourceid"></span>
### sourceId
```objectivec
@property (assign, nonatomic) intptr_t sourceId;
```
屏幕分享时，共享对象的 ID。


<span id="ByteRTCScreenCaptureSourceInfo-sourcename"></span>
### sourceName
```objectivec
@property (copy, nonatomic) NSString * _Nullable sourceName;
```
屏幕分享时共享对象的名称。<br>



# ByteRTCScreenParam
```objectivec
@interface ByteRTCScreenParam : NSObject
```

屏幕采集设置参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [frameRate](#ByteRTCScreenParam-framerate) |
| **NSInteger** | [bitrate](#ByteRTCScreenParam-bitrate) |


## 变量说明
<span id="ByteRTCScreenParam-framerate"></span>
### frameRate
```objectivec
@property(nonatomic, assign) NSInteger frameRate;
```
编码帧率,单位为 fps


<span id="ByteRTCScreenParam-bitrate"></span>
### bitrate
```objectivec
@property(nonatomic, assign) NSInteger bitrate;
```
编码码率，小于 0 时 SDK 会根据高宽自适应码率, 单位 kbps



# ByteRTCVirtualBackgroundSource
```objectivec
@interface ByteRTCVirtualBackgroundSource: NSObject
```

虚拟背景对象。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCVirtualBackgroundSourceType** | [sourceType](#ByteRTCVirtualBackgroundSource-sourcetype) |
| **int** | [sourceColor](#ByteRTCVirtualBackgroundSource-sourcecolor) |
| **NSString*** | [sourcePath](#ByteRTCVirtualBackgroundSource-sourcepath) |


## 变量说明
<span id="ByteRTCVirtualBackgroundSource-sourcetype"></span>
### sourceType
```objectivec
@property(nonatomic, assign) ByteRTCVirtualBackgroundSourceType sourceType;
```
虚拟背景类型，详见 [ByteRTCVirtualBackgroundSourceType](#bytertcvirtualbackgroundsourcetype) 。


<span id="ByteRTCVirtualBackgroundSource-sourcecolor"></span>
### sourceColor
```objectivec
@property int sourceColor;
```
纯色背景使用的颜色。<br>
格式为 0xAARRGGBB 。


<span id="ByteRTCVirtualBackgroundSource-sourcepath"></span>
### sourcePath
```objectivec
@property(nonatomic) NSString* _Nullable sourcePath;
```
自定义背景图片的绝对路径。

+ 支持的格式为 jpg、jpeg、png。  <br>
+ 图片分辨率超过 1080P 时，图片会被等比缩放至和视频一致。  <br>
+ 图片和视频宽高比一致时，图片会被直接缩放至和视频一致。  <br>
+ 图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。  <br>
+ 自定义图片带有局部透明效果时，透明部分由黑色代替。



# ByteRTCVideoFrameInfo
```objectivec
@interface ByteRTCVideoFrameInfo : NSObject
```

视频帧基础信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [width](#ByteRTCVideoFrameInfo-width) |
| **NSInteger** | [height](#ByteRTCVideoFrameInfo-height) |
| **ByteRTCVideoRotation** | [rotation](#ByteRTCVideoFrameInfo-rotation) |


## 变量说明
<span id="ByteRTCVideoFrameInfo-width"></span>
### width
```objectivec
@property(nonatomic, assign) NSInteger width;
```
视频帧的宽度（像素）


<span id="ByteRTCVideoFrameInfo-height"></span>
### height
```objectivec
@property(nonatomic, assign) NSInteger height;
```
视频帧的高度（像素）


<span id="ByteRTCVideoFrameInfo-rotation"></span>
### rotation
```objectivec
@property(nonatomic, assign) ByteRTCVideoRotation rotation;
```
视频帧顺时针旋转角度。参看 [ByteRTCVideoRotation](#bytertcvideorotation)。



# ByteRTCVideoEncoderConfig
```objectivec
@interface ByteRTCVideoEncoderConfig: NSObject
```

视频编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [width](#ByteRTCVideoEncoderConfig-width) |
| **NSInteger** | [height](#ByteRTCVideoEncoderConfig-height) |
| **NSInteger** | [frameRate](#ByteRTCVideoEncoderConfig-framerate) |
| **NSInteger** | [maxBitrate](#ByteRTCVideoEncoderConfig-maxbitrate) |
| **ByteRTCVideoEncoderPreference** | [encoderPreference](#ByteRTCVideoEncoderConfig-encoderpreference) |


## 变量说明
<span id="ByteRTCVideoEncoderConfig-width"></span>
### width
```objectivec
@property(nonatomic, assign) NSInteger width;
```
视频宽度，单位：px


<span id="ByteRTCVideoEncoderConfig-height"></span>
### height
```objectivec
@property(nonatomic, assign) NSInteger height;
```
视频高度，单位：px


<span id="ByteRTCVideoEncoderConfig-framerate"></span>
### frameRate
```objectivec
@property(nonatomic, assign) NSInteger frameRate;
```
视频帧率，单位：fps


<span id="ByteRTCVideoEncoderConfig-maxbitrate"></span>
### maxBitrate
```objectivec
@property(nonatomic, assign) NSInteger maxBitrate;
```
最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。  <br>
设为 -1 即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。 <br>
设为 0 则不对视频流进行编码发送。<br>
344 及以上版本，内部采集时默认值为 -1，344 以前版本无默认值，需手动设置。


<span id="ByteRTCVideoEncoderConfig-encoderpreference"></span>
### encoderPreference
```objectivec
@property(nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
```
编码策略偏好，默认为帧率优先。参看 [ByteRTCVideoEncoderPreference](#bytertcvideoencoderpreference)。



# ByteRTCRemoteVideoConfig
```objectivec
@interface ByteRTCRemoteVideoConfig : NSObject
```

远端视频帧信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [framerate](#ByteRTCRemoteVideoConfig-framerate) |
| **int** | [width](#ByteRTCRemoteVideoConfig-width) |
| **int** | [height](#ByteRTCRemoteVideoConfig-height) |


## 变量说明
<span id="ByteRTCRemoteVideoConfig-framerate"></span>
### framerate
```objectivec
@property (nonatomic, assign) int framerate;
```
期望订阅的最高帧率，单位：fps，默认值为 0 即满帧订阅，设为大于 0 的值时开始生效。  <br>
当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
仅码流支持 SVC 分级编码特性时方可生效。


<span id="ByteRTCRemoteVideoConfig-width"></span>
### width
```objectivec
@property(nonatomic, assign) int  width;
```
视频宽度，单位：px


<span id="ByteRTCRemoteVideoConfig-height"></span>
### height
```objectivec
@property(nonatomic, assign) int   height;
```
视频高度，单位：px



# ByteRTCRoomConfig
```objectivec
@interface ByteRTCRoomConfig : NSObject
```

房间参数配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCRoomProfile** | [profile](#ByteRTCRoomConfig-profile) |
| **BOOL** | [isAutoPublish](#ByteRTCRoomConfig-isautopublish) |
| **BOOL** | [isAutoSubscribeAudio](#ByteRTCRoomConfig-isautosubscribeaudio) |
| **BOOL** | [isAutoSubscribeVideo](#ByteRTCRoomConfig-isautosubscribevideo) |
| **ByteRTCRemoteVideoConfig*** | [remoteVideoConfig](#ByteRTCRoomConfig-remotevideoconfig) |


## 变量说明
<span id="ByteRTCRoomConfig-profile"></span>
### profile
```objectivec
@property(nonatomic) ByteRTCRoomProfile profile;
```
房间模式，参看 [ByteRTCRoomProfile](#bytertcroomprofile)，默认为普通音视频通话模式，进房后不可更改。


<span id="ByteRTCRoomConfig-isautopublish"></span>
### isAutoPublish
```objectivec
@property(assign, nonatomic) BOOL isAutoPublish;
```
是否自动发布音视频流，默认为自动发布。 <br>
创建和加入多房间时，只能将其中一个房间设置为自动发布。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。<br>
若调用 [setUserVisibility:](iOS-api.md#ByteRTCRoom-setuservisibility) 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。


<span id="ByteRTCRoomConfig-isautosubscribeaudio"></span>
### isAutoSubscribeAudio
```objectivec
@property(assign, nonatomic) BOOL isAutoSubscribeAudio;
```
是否自动订阅音频流，默认为自动订阅。<br>
包含主流和屏幕流。


<span id="ByteRTCRoomConfig-isautosubscribevideo"></span>
### isAutoSubscribeVideo
```objectivec
@property(assign, nonatomic) BOOL isAutoSubscribeVideo;
```
是否自动订阅视频流，默认为自动订阅。<br>
包含主流和屏幕流。


<span id="ByteRTCRoomConfig-remotevideoconfig"></span>
### remoteVideoConfig
```objectivec
@property(nonatomic, strong) ByteRTCRemoteVideoConfig * _Nonnull remoteVideoConfig;
```
远端视频流参数，参看 [ByteRTCRemoteVideoConfig](#bytertcremotevideoconfig)



# ByteRTCSourceCropInfo
```objectivec
@interface ByteRTCSourceCropInfo : NSObject
```

公共流裁剪信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **CGFloat** | [LocationX](#ByteRTCSourceCropInfo-locationx) |
| **CGFloat** | [LocationY](#ByteRTCSourceCropInfo-locationy) |
| **CGFloat** | [WidthProportion](#ByteRTCSourceCropInfo-widthproportion) |
| **CGFloat** | [HeightProportion](#ByteRTCSourceCropInfo-heightproportion) |


## 变量说明
<span id="ByteRTCSourceCropInfo-locationx"></span>
### LocationX
```objectivec
@property(assign, nonatomic) CGFloat LocationX;
```
裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的比例，取值范围[0.0, 1.0)


<span id="ByteRTCSourceCropInfo-locationy"></span>
### LocationY
```objectivec
@property(assign, nonatomic) CGFloat LocationY;
```
裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的比例，取值范围[0.0, 1.0)


<span id="ByteRTCSourceCropInfo-widthproportion"></span>
### WidthProportion
```objectivec
@property(assign, nonatomic) CGFloat WidthProportion;
```
裁剪后得到的视频帧宽度相对于裁剪前整体画面的比例，取值范围(0.0, 1.0]


<span id="ByteRTCSourceCropInfo-heightproportion"></span>
### HeightProportion
```objectivec
@property(assign, nonatomic) CGFloat HeightProportion;
```
裁剪后得到的视频帧高度相对于裁剪前整体画面的比例，取值范围(0.0, 1.0]



# ByteRTCPublicStreamRegion
```objectivec
@interface ByteRTCPublicStreamRegion : NSObject
```

合成公共流的每条流的布局信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSString*** | [userId](#ByteRTCPublicStreamRegion-userid) |
| **NSString*** | [roomId](#ByteRTCPublicStreamRegion-roomid) |
| **NSString*** | [alternateImage](#ByteRTCPublicStreamRegion-alternateimage) |
| **CGFloat** | [x](#ByteRTCPublicStreamRegion-x) |
| **CGFloat** | [y](#ByteRTCPublicStreamRegion-y) |
| **CGFloat** | [width](#ByteRTCPublicStreamRegion-width) |
| **CGFloat** | [height](#ByteRTCPublicStreamRegion-height) |
| **NSInteger** | [zOrder](#ByteRTCPublicStreamRegion-zorder) |
| **CGFloat** | [alpha](#ByteRTCPublicStreamRegion-alpha) |
| **NSInteger** | [mediaType](#ByteRTCPublicStreamRegion-mediatype) |
| **NSInteger** | [streamType](#ByteRTCPublicStreamRegion-streamtype) |
| **ByteRTCRenderMode** | [renderMode](#ByteRTCPublicStreamRegion-rendermode) |
| **ByteRTCSourceCropInfo*** | [sourceCrop](#ByteRTCPublicStreamRegion-sourcecrop) |


## 变量说明
<span id="ByteRTCPublicStreamRegion-userid"></span>
### userId
```objectivec
@property(copy, nonatomic) NSString * _Nonnull userId;
```
用户 ID。必填。  <br>
服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。


<span id="ByteRTCPublicStreamRegion-roomid"></span>
### roomId
```objectivec
@property(copy, nonatomic) NSString * _Nonnull roomId;
```
房间 ID必填。  <br>
服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。


<span id="ByteRTCPublicStreamRegion-alternateimage"></span>
### alternateImage
```objectivec
@property(copy, nonatomic) NSString * _Nonnull alternateImage;
```
背景图片地址


<span id="ByteRTCPublicStreamRegion-x"></span>
### x
```objectivec
@property(assign, nonatomic) CGFloat x;
```
用户视频布局相对画布左侧的偏移量， 相对值。范围[0.0 - 1.0]


<span id="ByteRTCPublicStreamRegion-y"></span>
### y
```objectivec
@property(assign, nonatomic) CGFloat y;
```
用户视频布局相对画布顶端的偏移量， 相对值。范围[0.0 - 1.0]


<span id="ByteRTCPublicStreamRegion-width"></span>
### width
```objectivec
@property(assign, nonatomic) CGFloat width;
```
用户视频宽度相对用户原始视频宽度的比例，相对值。范围[0.0 - 1.0]


<span id="ByteRTCPublicStreamRegion-height"></span>
### height
```objectivec
@property(assign, nonatomic) CGFloat height;
```
用户视频高度相对用户原始视频高度的比例，相对值。范围[0.0 - 1.0]


<span id="ByteRTCPublicStreamRegion-zorder"></span>
### zOrder
```objectivec
@property(assign, nonatomic) NSInteger zOrder;
```
用户视频布局在画布中的层级，0为底层，值越大越上层。范围[0 - 100]


<span id="ByteRTCPublicStreamRegion-alpha"></span>
### alpha
```objectivec
@property(assign, nonatomic) CGFloat alpha;
```
透明度，必填。可选范围为 [0.0, 1.0]。


<span id="ByteRTCPublicStreamRegion-mediatype"></span>
### mediaType
```objectivec
@property(assign, nonatomic) NSInteger mediaType;
```
推流内容控制。默认为0。<br>
0: 输出的混流包含音视频<br>
1: 只包含音频<br>
2: 表示只包含视频


<span id="ByteRTCPublicStreamRegion-streamtype"></span>
### streamType
```objectivec
@property(assign, nonatomic) NSInteger streamType;
```
推流媒体类型<br>
0：普通音视频流<br>
1: 屏幕流


<span id="ByteRTCPublicStreamRegion-rendermode"></span>
### renderMode
```objectivec
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
```
视频显示模式。详见 [ByteRTCRenderMode](#bytertcrendermode) 数据类型。  <br>


<span id="ByteRTCPublicStreamRegion-sourcecrop"></span>
### sourceCrop
```objectivec
@property(strong, nonatomic) ByteRTCSourceCropInfo * _Nonnull sourceCrop;
```
视频裁剪信息。 详见 [ByteRTCSourceCropInfo](#bytertcsourcecropinfo)。



# ByteRTCPublicStreamLayout
```objectivec
@interface ByteRTCPublicStreamLayout : NSObject
```

公共流的合流布局。必填


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [layoutMode](#ByteRTCPublicStreamLayout-layoutmode) |
| **NSInteger** | [interpolationMode](#ByteRTCPublicStreamLayout-interpolationmode) |
| **NSString*** | [backgroundColor](#ByteRTCPublicStreamLayout-backgroundcolor) |
| **NSString*** | [backgroundImage](#ByteRTCPublicStreamLayout-backgroundimage) |
| **NSArray<ByteRTCPublicStreamRegion*>*** | [regions](#ByteRTCPublicStreamLayout-regions) |


## 变量说明
<span id="ByteRTCPublicStreamLayout-layoutmode"></span>
### layoutMode
```objectivec
@property(assign, nonatomic) NSInteger layoutMode;
```
布局模式，必填。<br>

+ `0`: 自动模式。默认值。 <br>
+ `2`: 自定义模式。


<span id="ByteRTCPublicStreamLayout-interpolationmode"></span>
### interpolationMode
```objectivec
@property(assign, nonatomic) NSInteger interpolationMode;
```
插帧模式。<br>

+ `0`: 补最后一帧<br>
+ `1`: 补背景图片，如果没有设置背景图片则补黑帧


<span id="ByteRTCPublicStreamLayout-backgroundcolor"></span>
### backgroundColor
```objectivec
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
```
画布的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色


<span id="ByteRTCPublicStreamLayout-backgroundimage"></span>
### backgroundImage
```objectivec
@property(copy, nonatomic) NSString *_Nonnull backgroundImage;
```
背景图片地址


<span id="ByteRTCPublicStreamLayout-regions"></span>
### regions
```objectivec
@property(copy, nonatomic) NSArray<ByteRTCPublicStreamRegion *> * _Nonnull regions;
```
用户布局信息列表。每一个该类型对象为一路单独的视频流的布局信息。



# ByteRTCPublicStreamVideoConfig
```objectivec
@interface ByteRTCPublicStreamVideoConfig : NSObject
```

公共流的视频编码参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **NSInteger** | [width](#ByteRTCPublicStreamVideoConfig-width) |
| **NSInteger** | [height](#ByteRTCPublicStreamVideoConfig-height) |
| **NSInteger** | [fps](#ByteRTCPublicStreamVideoConfig-fps) |
| **NSInteger** | [bitrate](#ByteRTCPublicStreamVideoConfig-bitrate) |


## 变量说明
<span id="ByteRTCPublicStreamVideoConfig-width"></span>
### width
```objectivec
@property(assign, nonatomic) NSInteger width;
```
公共流视频宽度，必填。单位为 px，范围为 [2, 1920]，必须是偶数。


<span id="ByteRTCPublicStreamVideoConfig-height"></span>
### height
```objectivec
@property(assign, nonatomic) NSInteger height;
```
公共流视频高度，必填。单位为 px，范围为 [16, 1280]，必须是偶数。


<span id="ByteRTCPublicStreamVideoConfig-fps"></span>
### fps
```objectivec
@property(assign, nonatomic) NSInteger fps;
```
公共流视频帧率。必填<br>
范围：[1, 60] <br>


<span id="ByteRTCPublicStreamVideoConfig-bitrate"></span>
### bitrate
```objectivec
@property(assign, nonatomic) NSInteger bitrate;
```
视频码率，必填<br>
范围：[1,10000000]
单位为 bps



# ByteRTCVideoByteWatermark
```objectivec
@interface ByteRTCVideoByteWatermark: NSObject
```

水印图片相对视频流的位置和大小。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [x](#ByteRTCVideoByteWatermark-x) |
| **float** | [y](#ByteRTCVideoByteWatermark-y) |
| **float** | [width](#ByteRTCVideoByteWatermark-width) |
| **float** | [height](#ByteRTCVideoByteWatermark-height) |


## 变量说明
<span id="ByteRTCVideoByteWatermark-x"></span>
### x
```objectivec
@property(assign, nonatomic) float x;
```
水印图片相对视频流左上角的横向偏移与视频流宽度的比值，取值范围为 [0,1)。


<span id="ByteRTCVideoByteWatermark-y"></span>
### y
```objectivec
@property(assign, nonatomic) float y;
```
水印图片相对视频流左上角的纵向偏移与视频流高度的比值，取值范围为 [0,1)。


<span id="ByteRTCVideoByteWatermark-width"></span>
### width
```objectivec
@property(assign, nonatomic) float width;
```
水印图片宽度与视频流宽度的比值，取值范围 [0,1)。


<span id="ByteRTCVideoByteWatermark-height"></span>
### height
```objectivec
@property(assign, nonatomic) float height;
```
水印图片高度与视频流高度的比值，取值范围为 [0,1)。



# ByteRTCVideoWatermarkConfig
```objectivec
@interface ByteRTCVideoWatermarkConfig: NSObject
```

水印参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **BOOL** | [visibleInPreview](#ByteRTCVideoWatermarkConfig-visibleinpreview) |
| **ByteRTCVideoByteWatermark*** | [positionInLandscapeMode](#ByteRTCVideoWatermarkConfig-positioninlandscapemode) |
| **ByteRTCVideoByteWatermark*** | [positionInPortraitMode](#ByteRTCVideoWatermarkConfig-positioninportraitmode) |


## 变量说明
<span id="ByteRTCVideoWatermarkConfig-visibleinpreview"></span>
### visibleInPreview
```objectivec
@property(nonatomic, assign) BOOL visibleInPreview;
```
水印是否在视频预览中可见，默认可见。


<span id="ByteRTCVideoWatermarkConfig-positioninlandscapemode"></span>
### positionInLandscapeMode
```objectivec
@property(strong, nonatomic) ByteRTCVideoByteWatermark * _Nonnull positionInLandscapeMode;
```
横屏时的水印位置和大小，参看 [ByteRTCVideoByteWatermark](#bytertcvideobytewatermark)。


<span id="ByteRTCVideoWatermarkConfig-positioninportraitmode"></span>
### positionInPortraitMode
```objectivec
@property(strong, nonatomic) ByteRTCVideoByteWatermark * _Nonnull positionInPortraitMode;
```
竖屏时的水印位置和大小，参看 [ByteRTCVideoByteWatermark](#bytertcvideobytewatermark)。



# ByteRTCPublicStreaming
```objectivec
@interface ByteRTCPublicStreaming : NSObject
```

公共流参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteRTCPublicStreamLayout*** | [layout](#ByteRTCPublicStreaming-layout) |
| **ByteRTCPublicStreamVideoConfig*** | [video](#ByteRTCPublicStreaming-video) |


## 静态函数

| 返回 | 名称 |
| --- | --- |
| **instancetype** | [defaultPublicStreaming](#ByteRTCPublicStreaming-defaultpublicstreaming) |


## 变量说明
<span id="ByteRTCPublicStreaming-layout"></span>
### layout
```objectivec
@property(strong, nonatomic) ByteRTCPublicStreamLayout * _Nonnull layout;
```
视频流公共流整体布局参数，必填。详见 [ByteRTCPublicStreamLayout](#bytertcpublicstreamlayout)


<span id="ByteRTCPublicStreaming-video"></span>
### video
```objectivec
@property(strong, nonatomic) ByteRTCPublicStreamVideoConfig * _Nonnull video;
```
公共流视频编码参数。详见 [ByteRTCPublicStreamVideoConfig](#bytertcpublicstreamvideoconfig)。



## 函数说明
<span id="ByteRTCPublicStreaming-defaultpublicstreaming"></span>
### defaultPublicStreaming
```objectivec

+ (instancetype _Nonnull)defaultPublicStreaming;
```
获取默认的公共流转码配置属性。

**返回值**
包含默认配置的 [ByteRTCPublicStreaming](#bytertcpublicstreaming) 结构体