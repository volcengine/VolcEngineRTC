# IRTCASREngineEventHandler
```cpp
class bytertc::IRTCASREngineEventHandler
```

语音识别服务使用状态回调


`Defined in : byte_rtc_asr_engine_event_handler.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual void** | [onSuccess](#IRTCASREngineEventHandler-onsuccess) |
| **virtual void** | [onMessage](#IRTCASREngineEventHandler-onmessage) |
| **virtual void** | [onError](#IRTCASREngineEventHandler-onerror) |


## 函数说明
<span id="IRTCASREngineEventHandler-onsuccess"></span>
### onSuccess
```cpp
virtual void bytertc::IRTCASREngineEventHandler::onSuccess()
```
语音识别服务开启成功回调


<span id="IRTCASREngineEventHandler-onmessage"></span>
### onMessage
```cpp
virtual void bytertc::IRTCASREngineEventHandler::onMessage(
    const char* message)
```
语音转文字成功回调，该回调返回识别后的全量消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **const char*** | 识别完成后得到的文字消息 |


**注意**
若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。

<span id="IRTCASREngineEventHandler-onerror"></span>
### onError
```cpp
virtual void bytertc::IRTCASREngineEventHandler::onError(
    int error_code,
    const char* error_message)
```
当语音识别服务内部发生错误事件时触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| error_code | **int** | 错误码  <br/>• < 0: 参数错误或 API 调用顺序错误，参看 [RTCASRErrorCode](#rtcasrerrorcode)；  <br/>• >0: 参看 [语音识别服务错误码](https://www.volcengine.com/docs/6561/80818#_3-3-%E9%94%99%E8%AF%AF%E7%A0%81) |
| error_message | **const char*** | 错误原因说明 |


# AudioSampleRate
```cpp
enum bytertc::AudioSampleRate
```

音频采样率，单位为 Hz。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioSampleRateAuto | -1 | 默认设置。 |
| kAudioSampleRate8000 | 8000 | 8000 Hz |
| kAudioSampleRate16000 | 16000 | 16000 Hz |
| kAudioSampleRate32000 | 32000 | 32000 Hz |
| kAudioSampleRate44100 | 44100 | 44100 Hz |
| kAudioSampleRate48000 | 48000 | 48000 Hz |


# AudioChannel
```cpp
enum bytertc::AudioChannel
```

音频声道。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioChannelAuto | -1 | 默认设置。 |
| kAudioChannelMono | 1 | 单声道 |
| kAudioChannelStereo | 2 | 双声道 |


# AudioFormat
```cpp
struct bytertc::AudioFormat
```

音频格式


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **AudioSampleRate** | [sample_rate](#AudioFormat-sample_rate) |
| **AudioChannel** | [channel](#AudioFormat-channel) |


## 变量说明
<span id="AudioFormat-sample_rate"></span>
### sample_rate
```cpp
AudioSampleRate bytertc::AudioFormat::sample_rate;
```
音频采样率，详见 [AudioSampleRate](#audiosamplerate)


<span id="AudioFormat-channel"></span>
### channel
```cpp
AudioChannel bytertc::AudioFormat::channel;
```
音频声道，详见 [AudioChannel](#audiochannel)



# AudioProcessorMethod
```cpp
enum bytertc::AudioProcessorMethod
```

返回给音频处理器的音频类型。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioFrameProcessorRecord | 0 | 本地采集的音频。 |
| kAudioFrameProcessorPlayback | 1 | 远端音频流的混音音频。 |
| kAudioFrameProcessorRemoteUser | 2 | 各个远端音频流。 |
| kAudioFrameProcessorScreen | 4 | 屏幕共享音频。 |


# RTCAudioDeviceType
```cpp
enum bytertc::RTCAudioDeviceType
```

音频设备类型


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRTCAudioDeviceTypeUnknown | -1 | 未知设备类型 |
| kRTCAudioDeviceTypeRenderDevice | 0 | 音频渲染设备 |
| kRTCAudioDeviceTypeCaptureDevice | 1 | 音频采集设备 |
| kRTCAudioDeviceTypeScreenCaptureDevice | 2 | 屏幕流音频设备 |


# AudioRoute
```cpp
enum bytertc::AudioRoute
```

音频播放设备


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioRouteUnknown | -1 | 未知设备 |
| kAudioRouteHeadset | 1 | 有线耳机 |
| kAudioRouteEarpiece | 2 | 听筒 |
| kAudioRouteSpeakerphone | 3 | 扬声器 |
| kAudioRouteHeadsetBluetooth | 4 | 蓝牙耳机 |
| kAudioRouteHeadsetUSB | 5 | USB设备 |


# AudioPlaybackDevice
```cpp
enum bytertc::AudioPlaybackDevice
```

音频播放设备


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioPlaybackDeviceHeadset | 1 | 有线耳机 |
| kAudioPlaybackDeviceEarpiece | 2 | 听筒 |
| kAudioPlaybackDeviceSpeakerphone | 3 | 扬声器 |
| kAudioPlaybackDeviceHeadsetBluetooth | 4 | 蓝牙耳机 |
| kAudioPlaybackDeviceHeadsetUSB | 5 | USB设备 |


# VoiceChangerType
```cpp
enum bytertc::VoiceChangerType
```

Private method. 变声特效类型


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVoiceChangerTypeOriginal | 0 | 原声，不含特效 |
| kVoiceChangerTypeGiant | 1 | 巨人 |
| kVoiceChangerTypeChipmunk | 2 | 花栗鼠 |
| kVoiceChangerTypeMinionst | 3 | 小黄人 |
| kVoiceChangerTypeVibrato | 4 | 颤音 |
| kVoiceChangerTypeRobot | 5 | 机器人 |


# VoiceReverbType
```cpp
enum bytertc::VoiceReverbType
```

Private method. 混响特效类型


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVoiceReverbTypeOriginal | 0 | 原声，不含特效 |
| kVoiceReverbTypeEcho | 1 | 回声 |
| kVoiceReverbTypeConcert | 2 | 演唱会 |
| kVoiceReverbTypeEthereal | 3 | 空灵 |
| kVoiceReverbTypeKTV | 4 | KTV |
| kVoiceReverbTypeStudio | 5 | 录音棚 |


# AudioVolumeInfo
```cpp
struct bytertc::AudioVolumeInfo
```

音频流来源的用户 ID 及对应的音量。


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [linear_volume](#AudioVolumeInfo-linear_volume) |
| **int** | [nonlinear_volume](#AudioVolumeInfo-nonlinear_volume) |
| **const char*** | [uid](#AudioVolumeInfo-uid) |


## 变量说明
<span id="AudioVolumeInfo-linear_volume"></span>
### linear_volume
```cpp
int bytertc::AudioVolumeInfo::linear_volume;
```
线性音量，取值范围是：[0, 255]，与原始音量呈线性关系，数值越大，音量越大。
无声为 25 以下（绝对无声为 0，25 以下可视为无声），低音量为 25～76，中音量为 76～204，高音量为 204 以上。


<span id="AudioVolumeInfo-nonlinear_volume"></span>
### nonlinear_volume
```cpp
int bytertc::AudioVolumeInfo::nonlinear_volume;
```
非线性音量，取值范围是：[–127, 0]，单位 dB。此音量范围是将原始音量进行对数转化，在中低音量时分辨更为灵敏，适用于 Active Speaker（房间内最活跃用户）的识别。
高音量为 0～–20 dB，中音量为 –20～–40dB，低音量为 –40～–60dB，若低于 –60 dB，则为无声。


<span id="AudioVolumeInfo-uid"></span>
### uid
```cpp
const char* bytertc::AudioVolumeInfo::uid;
```
音频流来源的用户 ID



# AudioMixingState
```cpp
enum bytertc::AudioMixingState
```

音频混音文件播放状态。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioMixingStatePreloaded | 0 | 混音已加载 |
| kAudioMixingStatePlaying | 1 | 混音正在播放 |
| kAudioMixingStatePaused | 2 | 混音暂停 |
| kAudioMixingStateStopped | 3 | 混音停止 |
| kAudioMixingStateFailed | 4 | 混音播放失败 |
| kAudioMixingStateFinished | 5 | 混音播放结束 |
| kAudioMixingStatePCMEnabled | 6 | 准备PCM混音 |
| kAudioMixingStatePCMDisabled | 7 | PCM混音播放结束 |


# AudioMixingError
```cpp
enum bytertc::AudioMixingError
```

混音错误码。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioMixingErrorOk | 0 | 正常 |
| kAudioMixingErrorPreloadFailed | 1 | 预加载失败。找不到混音文件或者文件长度超出 20s |
| kAudioMixingErrorStartFailed | 2 | 混音开启失败。找不到混音文件或者混音文件打开失败 |
| kAudioMixingErrorIdNotFound | 3 | 混音 ID 异常 |
| kAudioMixingErrorSetPositionFailed | 4 | 设置混音文件的播放位置出错 |
| kAudioMixingErrorInValidVolume | 5 | 音量参数不合法，仅支持设置的音量值为[0, 400] |
| kAudioMixingErrorLoadConflict | 6 | 播放的文件与预加载的文件不一致。请先使用 [unloadAudioMixing](Windows-api.md#IAudioMixingManager-unloadaudiomixing) 卸载此前的文件。 |
| kAudioMixingErrorIdTypeNotMatch | 7 | 不支持此混音类型。 |
| kAudioMixingErrorInValidPitch | 8 | 设置混音文件的音调不合法 |
| kAudioMixingErrorInValidAudioTrack | 9 | 设置混音文件的音轨不合法 |
| kAudioMixingErrorIsStarting | 10 | 混音文件正在启动中 |
| kAudioMixingErrorInValidPlaybackSpeed | 11 | 设置混音文件的播放速度不合法 |


# AudioSourceType
```cpp
enum bytertc::AudioSourceType
```

音频输入源类型


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioSourceTypeExternal | 0 |  |
| kAudioSourceTypeInternal | 1 |  |


# AudioRenderType
```cpp
enum bytertc::AudioRenderType
```

音频输出类型


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioRenderTypeExternal | 0 |  |
| kAudioRenderTypeInternal | 1 |  |


# ASRAuthorizationType
```cpp
enum bytertc::ASRAuthorizationType
```

语音识别服务鉴权方式，详情请咨询语音识别服务相关人员


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kASRAuthorizationTypeToken | 0 | Token 鉴权 |
| kASRAuthorizationTypeSignature | 1 | Signature 鉴权 |


# RTCASRConfig
```cpp
struct bytertc::RTCASRConfig
```

使用自动语音识别服务所需校验信息


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [app_id](#RTCASRConfig-app_id) |
| **const char*** | [user_id](#RTCASRConfig-user_id) |
| **ASRAuthorizationType** | [authorization_type](#RTCASRConfig-authorization_type) |
| **const char*** | [access_token](#RTCASRConfig-access_token) |
| **const char*** | [secret_key](#RTCASRConfig-secret_key) |
| **const char*** | [cluster](#RTCASRConfig-cluster) |


## 变量说明
<span id="RTCASRConfig-app_id"></span>
### app_id
```cpp
const char* bytertc::RTCASRConfig::app_id;
```
应用 ID


<span id="RTCASRConfig-user_id"></span>
### user_id
```cpp
const char* bytertc::RTCASRConfig::user_id;
```
用户 ID


<span id="RTCASRConfig-authorization_type"></span>
### authorization_type
```cpp
ASRAuthorizationType bytertc::RTCASRConfig::authorization_type;
```
鉴权方式，参看 [ASRAuthorizationType](#asrauthorizationtype)


<span id="RTCASRConfig-access_token"></span>
### access_token
```cpp
const char* bytertc::RTCASRConfig::access_token;
```
访问令牌


<span id="RTCASRConfig-secret_key"></span>
### secret_key
```cpp
const char* bytertc::RTCASRConfig::secret_key;
```
私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://www.volcengine.com/docs/6561/107789)


<span id="RTCASRConfig-cluster"></span>
### cluster
```cpp
const char* bytertc::RTCASRConfig::cluster;
```
场景信息，参看[业务集群](https://www.volcengine.com/docs/6561/80818#_3-2-2-%E5%8F%91%E9%80%81-full-client-request)



# RTCASRErrorCode
```cpp
enum bytertc::RTCASRErrorCode
```

语音识别服务错误码。  <br>
除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 `startASR` 重启语音识别功能。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRTCASRErrorNetworkInterrupted | -1 | 网络连接中断，服务不可用，内部会进行重连 |
| kRTCASRErrorAlreadyStarted | -2 | 重复调用 `startASR`。开启语音识别服务后，你需要先调用 `stopASR` 停止语音识别服务，才能二次调用 `startASR` 再次开启服务。 |
| kRTCASRErrorTokenEmpty | -3 | 语音识别服务所需 token 为空 |
| kRTCErrorSignatureKeyEmpty | -4 | Signature 鉴权模式下 secret_key 为空 |
| kRTCASRErrorUserIdNull | -5 | 用户 ID 为空 |
| kRTCASRErrorAPPIDNull | -6 | 应用 ID 为空 |
| kRTCASRErrorClusterNull | -7 | 语音识别服务 cluster 为空 |
| kRTCASRErrorOperationDenied | -8 | 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。 |


# AudioMixingType
```cpp
enum bytertc::AudioMixingType
```

混音播放类型


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioMixingTypePlayout | 0 | 仅本地播放 |
| kAudioMixingTypePublish | 1 | 仅远端播放 |
| kAudioMixingTypePlayoutAndPublish | 2 | 本地和远端同时播放 |


# AudioMixingConfig
```cpp
struct bytertc::AudioMixingConfig
```

混音配置


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **AudioMixingType** | [type](#AudioMixingConfig-type) |
| **int** | [play_count](#AudioMixingConfig-play_count) |
| **int** | [position](#AudioMixingConfig-position) |
| **int64_t** | [callback_on_progress_interval](#AudioMixingConfig-callback_on_progress_interval) |


## 变量说明
<span id="AudioMixingConfig-type"></span>
### type
```cpp
AudioMixingType bytertc::AudioMixingConfig::type;
```
混音播放类型，详见 [AudioMixingType](#audiomixingtype)


<span id="AudioMixingConfig-play_count"></span>
### play_count
```cpp
int bytertc::AudioMixingConfig::play_count;
```
混音播放次数，

+ play_count <= 0: 无限循环  <br>
+ play_count == 1: 播放一次（默认）  <br>
+ play_count > 1: 播放 play_count 次


<span id="AudioMixingConfig-position"></span>
### position
```cpp
int bytertc::AudioMixingConfig::position;
```
混音时音频文件播放进度条位置，参数为整数，单位为毫秒


<span id="AudioMixingConfig-callback_on_progress_interval"></span>
### callback_on_progress_interval
```cpp
int64_t bytertc::AudioMixingConfig::callback_on_progress_interval = 0;
```
设置音频文件播放进度回调的时间间隔，参数为大于 0 的 10 的倍数，单位为毫秒，设置后 SDK 将按照设置的值触发 `onAudioMixingPlayingProgress` 回调，默认不回调。  <br>

+ 当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。  <br>
+ 当传入的值小于等于 0 时，不会触发进度回调。  <br>



# AudioMixingDualMonoMode
```cpp
enum bytertc::AudioMixingDualMonoMode
```

混音播放声道类型


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioMixingDualMonoModeAuto | 0 | 和音频文件一致 |
| kAudioMixingDualMonoModeL | 1 | 只能听到音频文件中左声道的音频 |
| kAudioMixingDualMonoModeR | 2 | 只能听到音频文件中右声道的音频 |
| kAudioMixingDualMonoModeMix | 3 | 能同时听到音频文件中左右声道的音频 |


# AudioReportMode
```cpp
enum bytertc::AudioReportMode
```

音量回调模式。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioReportModeNormal | 0 | 默认始终开启音量回调。 |
| kAudioReportModeDisconnect | 1 | 可见用户进房并停止推流后，关闭音量回调。 |
| kAudioReportModeReset | 2 | 可见用户进房并停止推流后，开启音量回调，回调值重置为0。 |


# AudioPropertiesMode
```cpp
enum bytertc::AudioPropertiesMode
```

音频信息提示中是否包含本地混音音频数据。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioPropertiesModeMicrophone | 0 | 音频信息提示中，仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。 |
| kAudioPropertiesModeAudioMixing | 1 | 音频信息提示中，除本地麦克风采集的音频数据和本地屏幕音频采集数据外，还包含本地混音的音频数据。 |


# AudioPropertiesConfig
```cpp
struct bytertc::AudioPropertiesConfig
```

音频属性信息提示的相关配置。


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [interval](#AudioPropertiesConfig-interval) |
| **bool** | [enable_spectrum](#AudioPropertiesConfig-enable_spectrum) |
| **bool** | [enable_vad](#AudioPropertiesConfig-enable_vad) |
| **AudioReportMode** | [local_main_report_mode](#AudioPropertiesConfig-local_main_report_mode) |
| **AudioPropertiesMode** | [audio_report_mode](#AudioPropertiesConfig-audio_report_mode) |


## 变量说明
<span id="AudioPropertiesConfig-interval"></span>
### interval
```cpp
int bytertc::AudioPropertiesConfig::interval;
```
信息提示间隔，单位：ms <br>

+ `<= 0`: 关闭信息提示  <br>
+ `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
+ `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>


<span id="AudioPropertiesConfig-enable_spectrum"></span>
### enable_spectrum
```cpp
bool bytertc::AudioPropertiesConfig::enable_spectrum = false;
```
是否开启音频频谱检测。


<span id="AudioPropertiesConfig-enable_vad"></span>
### enable_vad
```cpp
bool bytertc::AudioPropertiesConfig::enable_vad = false;
```
是否开启人声检测 (VAD)。


<span id="AudioPropertiesConfig-local_main_report_mode"></span>
### local_main_report_mode
```cpp
AudioReportMode bytertc::AudioPropertiesConfig::local_main_report_mode = kAudioReportModeNormal;
```
音量回调配置模式。详见 [AudioReportMode](#audioreportmode)。


<span id="AudioPropertiesConfig-audio_report_mode"></span>
### audio_report_mode
```cpp
AudioPropertiesMode bytertc::AudioPropertiesConfig::audio_report_mode = kAudioPropertiesModeMicrophone;
```
设置 `onLocalAudioPropertiesReport` 回调中是否包含本地混音音频数据。参看 [AudioPropertiesMode](#audiopropertiesmode)。<br>
默认仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。



# AudioPropertiesInfo
```cpp
struct bytertc::AudioPropertiesInfo
```

音频属性信息  <br>


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [linear_volume](#AudioPropertiesInfo-linear_volume) |
| **int** | [nonlinear_volume](#AudioPropertiesInfo-nonlinear_volume) |
| **float** | [spectrum](#AudioPropertiesInfo-spectrum) |
| **int** | [vad](#AudioPropertiesInfo-vad) |


## 变量说明
<span id="AudioPropertiesInfo-linear_volume"></span>
### linear_volume
```cpp
int bytertc::AudioPropertiesInfo::linear_volume;
```
线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。<br>

- [0, 25]: 无声 <br>
- [26, 75]: 低音量 <br>
- [76, 204]: 中音量 <br>
- [205, 255]: 高音量 <br>


<span id="AudioPropertiesInfo-nonlinear_volume"></span>
### nonlinear_volume
```cpp
int bytertc::AudioPropertiesInfo::nonlinear_volume;
```
非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。 <br>

- [-127, -60]: 无声 <br>
- [-59, -40]: 低音量 <br>
- [-39, -20]: 中音量 <br>
- [-19, 0]: 高音量 <br>


<span id="AudioPropertiesInfo-spectrum"></span>
### spectrum
```cpp
float bytertc::AudioPropertiesInfo::spectrum[SPECTRUM_SIZE] = {0};
```
频谱数组。默认长度为 257。


<span id="AudioPropertiesInfo-vad"></span>
### vad
```cpp
int bytertc::AudioPropertiesInfo::vad = -1;
```
人声检测（VAD）结果

+ 1: 检测到人声。<br>
+ 0: 未检测到人声。<br>
+ -1: 未开启 VAD。<br>



# RemoteAudioPropertiesInfo
```cpp
struct bytertc::RemoteAudioPropertiesInfo
```

远端音频属性信息


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **RemoteStreamKey** | [stream_key](#RemoteAudioPropertiesInfo-stream_key) |
| **AudioPropertiesInfo** | [audio_properties_info](#RemoteAudioPropertiesInfo-audio_properties_info) |


## 变量说明
<span id="RemoteAudioPropertiesInfo-stream_key"></span>
### stream_key
```cpp
RemoteStreamKey bytertc::RemoteAudioPropertiesInfo::stream_key;
```
远端流信息，详见 [RemoteStreamKey](#remotestreamkey)


<span id="RemoteAudioPropertiesInfo-audio_properties_info"></span>
### audio_properties_info
```cpp
AudioPropertiesInfo bytertc::RemoteAudioPropertiesInfo::audio_properties_info;
```
音频属性信息，详见 [AudioPropertiesInfo](#audiopropertiesinfo)



# LocalAudioPropertiesInfo
```cpp
struct bytertc::LocalAudioPropertiesInfo
```

本地音频属性信息


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **StreamIndex** | [stream_index](#LocalAudioPropertiesInfo-stream_index) |
| **AudioPropertiesInfo** | [audio_properties_info](#LocalAudioPropertiesInfo-audio_properties_info) |


## 变量说明
<span id="LocalAudioPropertiesInfo-stream_index"></span>
### stream_index
```cpp
StreamIndex bytertc::LocalAudioPropertiesInfo::stream_index;
```
流属性，主流或屏幕流。参看 [StreamIndex](#streamindex)


<span id="LocalAudioPropertiesInfo-audio_properties_info"></span>
### audio_properties_info
```cpp
AudioPropertiesInfo bytertc::LocalAudioPropertiesInfo::audio_properties_info;
```
音频属性信息，详见 [AudioPropertiesInfo](#audiopropertiesinfo)



# AudioProfileType
```cpp
enum bytertc::AudioProfileType
```

音质档位


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioProfileTypeDefault | 0 | 默认音质<br><br/>服务器下发或客户端已设置的 [RoomProfileType](#roomprofiletype) 的音质配置 |
| kAudioProfileTypeFluent | 1 | 流畅  <br><br/>单声道，采样率为 16 kHz，编码码率为 32 Kbps。 <br><br/>流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。 |
| kAudioProfileTypeStandard | 2 | 单声道标准音质。  <br><br/>采样率为 24 kHz，编码码率为 48 Kbps。 <br><br/>适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和狼人杀等游戏。 |
| kAudioProfileTypeHD | 3 | 双声道音乐音质  <br><br/>采样率为 48 kHz，编码码率为 128 kbps。 <br><br/>超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。 <br><br/>游戏场景不建议使用。 |
| kAudioProfileTypeStandardStereo | 4 | 双声道标准音质。采样率为 48 KHz，编码码率最大值为 80 Kbps |
| kAudioProfileTypeHDMono | 5 | 单声道音乐音质。采样率为 48 kHz，编码码率最大值为 64 Kbps |


# Position
```cpp
struct bytertc::Position
```

本地用户在房间内的位置坐标，需自行建立空间直角坐标系


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [x](#Position-x) |
| **int** | [y](#Position-y) |
| **int** | [z](#Position-z) |


## 变量说明
<span id="Position-x"></span>
### x
```cpp
int bytertc::Position::x;
```
x 坐标


<span id="Position-y"></span>
### y
```cpp
int bytertc::Position::y;
```
y 坐标


<span id="Position-z"></span>
### z
```cpp
int bytertc::Position::z;
```
z 坐标



# AudioAbilityType
```cpp
enum bytertc::AudioAbilityType
```

音频音量是否可设置


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioAbilityTypeUnknown | -1 | 未知 |
| kAudioAbilityAble | 0 | 音量可设置 |
| kAudioAbilityUnable | 1 | 音量不可设置 |


# AudioDeviceInfo
```cpp
struct bytertc::AudioDeviceInfo
```

音频设备信息


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **char** | [device_id](#AudioDeviceInfo-device_id) |
| **char** | [device_name](#AudioDeviceInfo-device_name) |
| **char** | [device_container_id](#AudioDeviceInfo-device_container_id) |
| **int64_t** | [device_vid](#AudioDeviceInfo-device_vid) |
| **int64_t** | [device_pid](#AudioDeviceInfo-device_pid) |
| **DeviceTransportType** | [transport_type](#AudioDeviceInfo-transport_type) |
| **AudioAbilityType** | [volume_settable](#AudioDeviceInfo-volume_settable) |
| **bool** | [is_system_default](#AudioDeviceInfo-is_system_default) |


## 变量说明
<span id="AudioDeviceInfo-device_id"></span>
### device_id
```cpp
char bytertc::AudioDeviceInfo::device_id[MAX_DEVICE_ID_LENGTH];
```
设备 ID


<span id="AudioDeviceInfo-device_name"></span>
### device_name
```cpp
char bytertc::AudioDeviceInfo::device_name[MAX_DEVICE_ID_LENGTH];
```
设备名称


<span id="AudioDeviceInfo-device_container_id"></span>
### device_container_id
```cpp
char bytertc::AudioDeviceInfo::device_container_id[MAX_DEVICE_ID_LENGTH];
```
设备所连接的声卡 ID，便于选择使用同一声卡的扬声器和麦克风。


<span id="AudioDeviceInfo-device_vid"></span>
### device_vid
```cpp
int64_t bytertc::AudioDeviceInfo::device_vid;
```
设备的厂商 ID


<span id="AudioDeviceInfo-device_pid"></span>
### device_pid
```cpp
int64_t bytertc::AudioDeviceInfo::device_pid;
```
设备的产品编码


<span id="AudioDeviceInfo-transport_type"></span>
### transport_type
```cpp
DeviceTransportType bytertc::AudioDeviceInfo::transport_type;
```
设备的传输方式


<span id="AudioDeviceInfo-volume_settable"></span>
### volume_settable
```cpp
AudioAbilityType bytertc::AudioDeviceInfo::volume_settable;
```
是否支持设置音量


<span id="AudioDeviceInfo-is_system_default"></span>
### is_system_default
```cpp
bool bytertc::AudioDeviceInfo::is_system_default;
```
是否系统默认设备



# StandardPitchInfo
```cpp
struct bytertc::StandardPitchInfo
```

标准音高数据


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [start_time](#StandardPitchInfo-start_time) |
| **int** | [duration](#StandardPitchInfo-duration) |
| **int** | [pitch](#StandardPitchInfo-pitch) |


## 变量说明
<span id="StandardPitchInfo-start_time"></span>
### start_time
```cpp
int bytertc::StandardPitchInfo::start_time;
```
开始时间，单位 ms。


<span id="StandardPitchInfo-duration"></span>
### duration
```cpp
int bytertc::StandardPitchInfo::duration;
```
持续时间，单位 ms。


<span id="StandardPitchInfo-pitch"></span>
### pitch
```cpp
int bytertc::StandardPitchInfo::pitch;
```
音高。



# MulDimSingScoringMode
```cpp
enum bytertc::MulDimSingScoringMode
```

K 歌打分维度。


`Defined in : bytertc_audio_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMulDimSingScoringModeNote | 0 | 按照音高进行评分。 |


# SingScoringConfig
```cpp
struct bytertc::SingScoringConfig
```

K 歌评分配置。


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **AudioSampleRate** | [sample_rate](#SingScoringConfig-sample_rate) |
| **MulDimSingScoringMode** | [mode](#SingScoringConfig-mode) |
| **const char*** | [lyrics_filepath](#SingScoringConfig-lyrics_filepath) |
| **const char*** | [midi_filepath](#SingScoringConfig-midi_filepath) |


## 变量说明
<span id="SingScoringConfig-sample_rate"></span>
### sample_rate
```cpp
AudioSampleRate bytertc::SingScoringConfig::sample_rate;
```
音频采样率。仅支持 44100 Hz、48000 Hz。


<span id="SingScoringConfig-mode"></span>
### mode
```cpp
MulDimSingScoringMode bytertc::SingScoringConfig::mode;
```
打分维度，详见 [MulDimSingScoringMode](#muldimsingscoringmode)。


<span id="SingScoringConfig-lyrics_filepath"></span>
### lyrics_filepath
```cpp
const char* bytertc::SingScoringConfig::lyrics_filepath;
```
歌词文件路径。打分功能仅支持 KRC 歌词文件。


<span id="SingScoringConfig-midi_filepath"></span>
### midi_filepath
```cpp
const char* bytertc::SingScoringConfig::midi_filepath;
```
歌曲 midi 文件路径。



# SingScoringRealtimeInfo
```cpp
struct bytertc::SingScoringRealtimeInfo
```

实时评分信息。


`Defined in : bytertc_audio_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [current_position](#SingScoringRealtimeInfo-current_position) |
| **int** | [user_pitch](#SingScoringRealtimeInfo-user_pitch) |
| **int** | [standard_pitch](#SingScoringRealtimeInfo-standard_pitch) |
| **int** | [sentence_index](#SingScoringRealtimeInfo-sentence_index) |
| **int** | [sentence_score](#SingScoringRealtimeInfo-sentence_score) |
| **int** | [total_score](#SingScoringRealtimeInfo-total_score) |
| **int** | [average_score](#SingScoringRealtimeInfo-average_score) |


## 变量说明
<span id="SingScoringRealtimeInfo-current_position"></span>
### current_position
```cpp
int bytertc::SingScoringRealtimeInfo::current_position;
```
当前播放进度。


<span id="SingScoringRealtimeInfo-user_pitch"></span>
### user_pitch
```cpp
int bytertc::SingScoringRealtimeInfo::user_pitch;
```
演唱者的音高。


<span id="SingScoringRealtimeInfo-standard_pitch"></span>
### standard_pitch
```cpp
int bytertc::SingScoringRealtimeInfo::standard_pitch;
```
标准音高。


<span id="SingScoringRealtimeInfo-sentence_index"></span>
### sentence_index
```cpp
int bytertc::SingScoringRealtimeInfo::sentence_index;
```
歌词分句索引。


<span id="SingScoringRealtimeInfo-sentence_score"></span>
### sentence_score
```cpp
int bytertc::SingScoringRealtimeInfo::sentence_score;
```
上一句歌词的评分。


<span id="SingScoringRealtimeInfo-total_score"></span>
### total_score
```cpp
int bytertc::SingScoringRealtimeInfo::total_score;
```
当前演唱的累计分数。


<span id="SingScoringRealtimeInfo-average_score"></span>
### average_score
```cpp
int bytertc::SingScoringRealtimeInfo::average_score;
```
当前演唱的平均分数。



# AudioFrameType
```cpp
enum bytertc::AudioFrameType
```

音频帧类型


`Defined in : bytertc_audio_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kFrameTypePCM16 | 0 | PCM 16bit |


# AudioFrameBuilder
```cpp
typedef struct bytertc::AudioFrameBuilder
```

音频帧构建类


`Defined in : bytertc_audio_frame.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **AudioSampleRate** | [sample_rate](#AudioFrameBuilder-sample_rate) |
| **AudioChannel** | [channel](#AudioFrameBuilder-channel) |
| **int64_t** | [timestamp_us](#AudioFrameBuilder-timestamp_us) |
| **uint8_t*** | [data](#AudioFrameBuilder-data) |
| **int64_t** | [data_size](#AudioFrameBuilder-data_size) |
| **bool** | [deep_copy](#AudioFrameBuilder-deep_copy) |


## 变量说明
<span id="AudioFrameBuilder-sample_rate"></span>
### sample_rate
```cpp
AudioSampleRate bytertc::AudioFrameBuilder::sample_rate;
```
音频采样率


<span id="AudioFrameBuilder-channel"></span>
### channel
```cpp
AudioChannel bytertc::AudioFrameBuilder::channel;
```
音频通道数


<span id="AudioFrameBuilder-timestamp_us"></span>
### timestamp_us
```cpp
int64_t bytertc::AudioFrameBuilder::timestamp_us = 0;
```
音频帧时间戳，单位：微秒


<span id="AudioFrameBuilder-data"></span>
### data
```cpp
uint8_t* bytertc::AudioFrameBuilder::data;
```
音频帧数据


<span id="AudioFrameBuilder-data_size"></span>
### data_size
```cpp
int64_t bytertc::AudioFrameBuilder::data_size = 0;
```
音频帧数据大小


<span id="AudioFrameBuilder-deep_copy"></span>
### deep_copy
```cpp
bool bytertc::AudioFrameBuilder::deep_copy = true;
```
是否深拷贝



# IAudioFrame
```cpp
class bytertc::IAudioFrame
```

音频帧


`Defined in : bytertc_audio_frame.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual int64_t** | [timestampUs](#IAudioFrame-timestampus) |
| **virtual AudioSampleRate** | [sampleRate](#IAudioFrame-samplerate) |
| **virtual AudioChannel** | [channel](#IAudioFrame-channel) |
| **virtual uint8_t*** | [data](#IAudioFrame-data) |
| **virtual int** | [dataSize](#IAudioFrame-datasize) |
| **virtual AudioFrameType** | [frameType](#IAudioFrame-frametype) |
| **virtual void** | [release](#IAudioFrame-release) |
| **virtual bool** | [isMutedData](#IAudioFrame-ismuteddata) |


## 函数说明
<span id="IAudioFrame-timestampus"></span>
### timestampUs
```cpp
virtual int64_t bytertc::IAudioFrame::timestampUs() const
```
获取音频帧时间戳。

**返回值**
音频帧时间戳，单位：微秒


<span id="IAudioFrame-samplerate"></span>
### sampleRate
```cpp
virtual AudioSampleRate bytertc::IAudioFrame::sampleRate() const
```
获取音频采样率。参看 [AudioSampleRate](#audiosamplerate)

**返回值**
音频采样率，单位：Hz


<span id="IAudioFrame-channel"></span>
### channel
```cpp
virtual AudioChannel bytertc::IAudioFrame::channel() const
```
获取音频通道数。参看 [AudioChannel](#audiochannel)

**返回值**
音频通道数


**注意**
双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。

<span id="IAudioFrame-data"></span>
### data
```cpp
virtual uint8_t* bytertc::IAudioFrame::data() const
```
获取音频帧内存块地址

**返回值**
音频帧内存块地址


<span id="IAudioFrame-datasize"></span>
### dataSize
```cpp
virtual int bytertc::IAudioFrame::dataSize() const
```
获取音频帧数据大小

**返回值**
音频帧数据大小，单位：字节。


<span id="IAudioFrame-frametype"></span>
### frameType
```cpp
virtual AudioFrameType bytertc::IAudioFrame::frameType() const
```
获取音频帧类型

**返回值**
音频帧类型，目前只支持 PCM，详见 [AudioFrameType](#audioframetype)


<span id="IAudioFrame-release"></span>
### release
```cpp
virtual void bytertc::IAudioFrame::release()
```
释放音频帧


<span id="IAudioFrame-ismuteddata"></span>
### isMutedData
```cpp
virtual bool bytertc::IAudioFrame::isMutedData() const
```
获取音频静音标志

**返回值**
是否静音数据  

+ true: 是  
+ false: 否


# AudioFrameCallbackMethod
```cpp
enum class bytertc::AudioFrameCallbackMethod
```

音频回调方法


`Defined in : bytertc_audio_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioFrameCallbackRecord | 0 | 本地麦克风录制的音频数据回调 |
| kAudioFrameCallbackPlayback | 1 | 订阅的远端所有用户混音后的音频数据回调 |
| kAudioFrameCallbackMixed | 2 | 本地麦克风录制和订阅的远端所有用户混音后的音频数据回调 |
| kAudioFrameCallbackRemoteUser | 3 | 订阅的远端每个用户混音前的音频数据回调 |
| kAudioFrameCallbackRecordScreen | 4 | 本地屏幕录制的音频数据回调 |


# UserOfflineReason
```cpp
enum bytertc::UserOfflineReason
```

用户离开房间的原因。  <br>


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kUserOfflineReasonQuit | 0 | 远端用户调用 `leaveRoom` 方法退出房间。  <br> |
| kUserOfflineReasonDropped | 1 | 远端用户因网络等原因掉线。  <br> |
| kUserOfflineReasonSwitchToInvisible | 2 | 远端用户切换至隐身状态。  <br> |
| kUserOfflineReasonKickedByAdmin | 3 | 远端用户被踢出出房间。<br/>因调用踢出用户的 OpenAPI，远端用户被踢出房间。 |


# StreamRemoveReason
```cpp
enum bytertc::StreamRemoveReason
```

房间内远端流被移除的原因。  <br>


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kStreamRemoveReasonUnpublish | 0 | 远端用户停止发布流。  <br> |
| kStreamRemoveReasonPublishFailed | 1 | 远端用户发布流失败。  <br> |
| kStreamRemoveReasonKeepLiveFailed | 2 | 保活失败。  <br> |
| kStreamRemoveReasonClientDisconnected | 3 | 远端用户断网。  <br> |
| kStreamRemoveReasonRepublish | 4 | 远端用户重新发布流。  <br> |
| kStreamRemoveReasonOther | 5 | 其他原因。  <br> |


# JoinRoomType
```cpp
enum bytertc::JoinRoomType
```

用户加入房间的类型。  <br>


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kJoinRoomTypeFirst | 0 | 首次加入房间。用户手动调用 `joinRoom` 加入房间。  <br> |
| kJoinRoomTypeReconnected | 1 | 重新加入房间。用户网络较差，失去与服务器的连接，进行重连时收到加入成功。  <br> |


# LoginType
```cpp
enum bytertc::LoginType
```

用户登录的类型


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kLoginTypeFirst | 0 | 首次登录。用户手动调用 `login`，收到登录成功。 |
| kLoginTypeReconnected | 1 | 重连。用户网络较差，失去与服务器的连接，SDK 自动重连登录成功。 |


# USER_ONLINE_STATUS
```cpp
enum bytertc::USER_ONLINE_STATUS
```

用户在线状态。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kUserOnlineStatusOffline | 0 | 对端用户离线  <br><br/>对端用户已调用 `logout`，或者没有调用 `login` 进行登录。 |
| kUserOnlineStatusOnline | 1 | 对端用户在线  <br><br/>对端用户调用 `login` 登录，并且连接状态正常。 |
| kUserOnlineStatusUnreachable | 2 | 无法获取对端用户在线状态  <br><br/>发生级联错误、对端用户在线状态异常时返回。 |


# ServerACKMsg
```cpp
struct bytertc::ServerACKMsg
```

服务端消息发送结果回调内容


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [length](#ServerACKMsg-length) |
| **char*** | [ACKMsg](#ServerACKMsg-ackmsg) |


## 变量说明
<span id="ServerACKMsg-length"></span>
### length
```cpp
int bytertc::ServerACKMsg::length;
```
回调消息长度


<span id="ServerACKMsg-ackmsg"></span>
### ACKMsg
```cpp
char* bytertc::ServerACKMsg::ACKMsg;
```
回调消息内容



# MessageConfig
```cpp
enum bytertc::MessageConfig
```

消息类型


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMessageConfigReliableOrdered | 0 | 低延时可靠有序消息 |
| kMessageConfigUnreliableOrdered | 1 | 超低延时有序消息 |
| kMessageConfigUnreliableUnordered | 2 | 超低延时无序消息 |


# UserMessageSendResult
```cpp
enum bytertc::UserMessageSendResult
```

发送消息结果，成功或失败，及失败原因


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kUserMessageSendResultSuccess | 0 | 发送消息成功 |
| kUserMessageSendResultTimeout | 1 | 发送超时，没有发送 |
| kUserMessageSendResultBroken | 2 | 通道断开，没有发送 |
| kUserMessageSendResultNoReceiver | 3 | 找不到接收方 |
| kUserMessageSendResultNoRelayPath | 4 | 远端用户未登录或未进房 |
| kUserMessageSendResultNotJoin | 100 | 消息发送方没有加入房间 |
| kUserMessageSendResultInit | 101 | 连接未完成初始化,没有可用的数据传输通道连接 |
| kUserMessageSendResultNoConnection | 102 | 没有可用的数据传输通道连接 |
| kUserMessageSendResultExceedMaxLength | 103 | 消息超过最大长度，当前为 64 KB |
| kUserMessageSendResultEmptyUser | 104 | 接收消息的单个用户 id 为空 |
| kUserMessageSendResultNotLogin | 105 | 房间外或应用服务器消息发送方没有登录 |
| kUserMessageSendResultServerParamsNotSet | 106 | 发送消息给业务方服务器之前没有设置参数 |
| kUserMessageSendResultUnknown | 1000 | 未知错误 |


# RoomMessageSendResult
```cpp
enum bytertc::RoomMessageSendResult
```

房间内广播消息发送结果


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRoomMessageSendResultSuccess | 200 | 消息发送成功 |
| kRoomMessageSendResultNotJoin | 100 | 失败，发送方未加入房间 |
| kRoomMessageSendResultNoConnection | 102 | 失败，没有可用的数据传输通道连接 |
| kRoomMessageSendResultExceedMaxLength | 103 | 失败，消息超过最大长度，当前为 64KB |
| kRoomMessageSendResultUnknown | 1000 | 失败，未知错误 |


# ConnectionState
```cpp
enum bytertc::ConnectionState
```

SDK 与信令服务器连接状态。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kConnectionStateDisconnected | 1 | 连接断开超过 12s，此时 SDK 会尝试自动重连。 |
| kConnectionStateConnecting | 2 | 首次请求建立连接，正在连接中。 |
| kConnectionStateConnected | 3 | 首次连接成功。 |
| kConnectionStateReconnecting | 4 | 涵盖了以下情况：<br><br/>+ 首次连接时，10秒连接不成功; <br><br/>+ 连接成功后，断连 10 秒。自动重连中。 |
| kConnectionStateReconnected | 5 | 连接断开后，重连成功。 |
| kConnectionStateLost | 6 | 处于 `kConnectionStateDisconnected` 状态超过 10 秒，且期间重连未成功。SDK 仍将继续尝试重连。 |
| kConnectionStateFailed | 7 | 连接失败，服务端状态异常。SDK 不会自动重连，请重新进房，或联系技术支持。 |


# NetworkDetectionStopReason
```cpp
enum bytertc::NetworkDetectionStopReason
```

通话前探测的停止原因
`onNetworkDetectionStopped` 回调的参数类型


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kNetworkDetectionStopReasonUser | 0 | 用户主动停止 |
| kNetworkDetectionStopReasonTimeout | 1 | 探测超过三分钟 |
| kNetworkDetectionStopReasonConnectionLost | 2 | 探测网络连接断开。<br>当超过 12s 没有收到回复，SDK 将断开网络连接，并且不再尝试重连。 |
| kNetworkDetectionStopReasonStreaming | 3 | 本地开始推拉流，停止探测 |
| kNetworkDetectionStopReasonInnerErr | 4 | 网络探测失败，内部异常 |


# NetworkDetectionLinkType
```cpp
enum bytertc::NetworkDetectionLinkType
```

通话前探测链接的类型。
`onNetworkDetectionResult` 回调的参数类型


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kNetworkDetectionLinkTypeUp | 0 | 上行网络探测 |
| kNetworkDetectionLinkTypeDown | 1 | 下行网络探测 |


# NetworkQuality
```cpp
enum bytertc::NetworkQuality
```

媒体流网络质量。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kNetworkQualityUnknown | 0 | 网络质量未知。 |
| kNetworkQualityExcellent | 1 | 网络质量极好。 |
| kNetworkQualityGood | 2 | 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。 |
| kNetworkQualityPoor | 3 | 主观感受有瑕疵但不影响沟通。 |
| kNetworkQualityBad | 4 | 勉强能沟通但不顺畅。 |
| kNetworkQualityVbad | 5 | 网络质量非常差，基本不能沟通。 |
| kNetworkQualityDisconnected | 6 | 12 s 内无应答，代表网络断开，将返回本枚举值。<br/>你也可以通过 onConnectionStateChanged 监听 kConnectionStateDisconnected = 1 感知网络断开。<br/>更多网络状态信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。 |


# NetworkQualityStats
```cpp
struct bytertc::NetworkQualityStats
```

上行/下行网络质量


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [uid](#NetworkQualityStats-uid) |
| **double** | [fraction_lost](#NetworkQualityStats-fraction_lost) |
| **int** | [rtt](#NetworkQualityStats-rtt) |
| **int** | [total_bandwidth](#NetworkQualityStats-total_bandwidth) |
| **NetworkQuality** | [tx_quality](#NetworkQualityStats-tx_quality) |
| **NetworkQuality** | [rx_quality](#NetworkQualityStats-rx_quality) |


## 变量说明
<span id="NetworkQualityStats-uid"></span>
### uid
```cpp
const char* bytertc::NetworkQualityStats::uid;
```
用户 ID


<span id="NetworkQualityStats-fraction_lost"></span>
### fraction_lost
```cpp
double bytertc::NetworkQualityStats::fraction_lost;
```
本端的上行/下行的丢包率，范围 [0.0,1.0]
当 `uid` 为本地用户时，代表发布流的上行丢包率。
当 `uid` 为远端用户时，代表接收所有订阅流的下行丢包率。


<span id="NetworkQualityStats-rtt"></span>
### rtt
```cpp
int bytertc::NetworkQualityStats::rtt;
```
当 `uid` 为本地用户时有效，客户端到服务端的往返延时（RTT），单位：ms


<span id="NetworkQualityStats-total_bandwidth"></span>
### total_bandwidth
```cpp
int bytertc::NetworkQualityStats::total_bandwidth;
```
本端的音视频 RTP 包 2 秒内的平均传输速率，单位：bps
当 `uid` 为本地用户时，代表发送速率。
当 `uid` 为远端用户时，代表所有订阅流的接收速率。


<span id="NetworkQualityStats-tx_quality"></span>
### tx_quality
```cpp
NetworkQuality bytertc::NetworkQualityStats::tx_quality;
```
上行网络质量评分，详见 [NetworkQuality](#networkquality)。


<span id="NetworkQualityStats-rx_quality"></span>
### rx_quality
```cpp
NetworkQuality bytertc::NetworkQualityStats::rx_quality;
```
下行网络质量评分，详见 [NetworkQuality](#networkquality)。



# NetworkType
```cpp
enum bytertc::NetworkType
```

SDK 网络连接类型。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kNetworkTypeUnknown | -1 | 网络连接类型未知。 |
| kNetworkTypeDisconnected | 0 | 网络连接已断开。 |
| kNetworkTypeLAN | 1 | 网络连接类型为 LAN 。 |
| kNetworkTypeWIFI | 2 | 网络连接类型为 Wi-Fi（包含热点）。 |
| kNetworkTypeMobile2G | 3 | 网络连接类型为 2G 移动网络。 |
| kNetworkTypeMobile3G | 4 | 网络连接类型为 3G 移动网络。 |
| kNetworkTypeMobile4G | 5 | 网络连接类型为 4G 移动网络。 |
| kNetworkTypeMobile5G | 6 | 网络连接类型为 5G 移动网络。 |


# RoomProfileType
```cpp
enum bytertc::RoomProfileType
```

房间模式<br>
根据所需场景，选择合适的房间模式，应用不同的音视频算法、视频参数和网络配置 <br>
调用 `setAudioProfile` 改变音频参数配置


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRoomProfileTypeCommunication | 0 | 默认场景，通用模式 |
| kRoomProfileTypeGame | 2 | 游戏语音模式，低功耗、低流量消耗。<br><br/>低端机在此模式下运行时，进行了额外的性能优化：<br><br/>+ 部分低端机型配置编码帧长 40/60 <br><br/>+ 部分低端机型关闭软件 3A 音频处理 <br><br/>增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。 |
| kRoomProfileTypeCloudGame | 3 | 云游戏模式。<br><br/>如果你的游戏场景需要低延迟的配置，使用此设置。<br><br/>此设置下，弱网抗性较差。 |
| kRoomProfileTypeLowLatency | 4 | 云渲染模式。超低延时配置。  <br><br/>如果你的应用并非游戏但又对延时要求较高时，选用此模式 <br><br/>该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br> |
| kRoomProfileTypeChat | 5 | 适用于 1 vs 1 音视频通话 |
| kRoomProfileTypeChatRoom | 6 | 适用于 3 人及以上纯语音通话。<br><br/>通话中，闭麦时为是媒体模式，上麦后切换为通话模式。 |
| kRoomProfileTypeLwTogether | 7 | 实现多端同步播放音视频，适用于 “一起看” 或 “一起听” 场景。<br><br/>该场景中，使用 RTC 信令同步播放进度，共享的音频内容不通过 RTC 进行传输。 |
| kRoomProfileTypeGameHD | 8 | 适用于对音质要求较高的游戏场景，优化音频 3A 策略，只通过媒体模式播放音频 |
| kRoomProfileTypeCoHost | 9 | 适用于直播中主播之间连麦的业务场景。<br><br/>直播时通过 CDN，发起连麦 PK 时使用 RTC。 |
| kRoomProfileTypeInteractivePodcast | 10 | 适用于单主播和观众进行音视频互动的直播。通话模式，上下麦不会有模式切换，避免音量突变现象 |
| kRoomProfileTypeKTV | 11 | 线上 KTV 场景，音乐音质，低延迟<br><br/>使用 RTC 传输伴奏音乐，混音后的歌声，适合独唱或单通合唱 |
| kRoomProfileTypeChorus | 12 | 适合在线实时合唱场景，高音质，超低延迟。使用本配置前请联系技术支持进行协助完成其他配置。 |
| kRoomProfileTypeGameStreaming | 14 | 适用于 1 vs 1 游戏串流，支持公网或局域网。 |
| kRoomProfileTypeLanLiveStreaming | 15 | 适用于局域网的 1 对多视频直播，最高支持 8K， 60 帧/秒， 100 Mbps 码率<br><br/>需要在局域网配置私有化部署媒体服务器。 |
| kRoomProfileTypeMeeting | 16 | 适用于云端会议中的个人设备 |
| kRoomProfileTypeMeetingRoom | 17 | 适用于云端会议中的会议室终端设备，例如 Rooms，投屏盒子等。 |
| kRoomProfileTypeClassroom | 18 | 适用于课堂互动，房间内所有成员都可以进行音视频互动<br><br/>当你的场景中需要同时互动的成员超过 10人时使用此模式 |


# AudioRoomConfig
```cpp
struct bytertc::AudioRoomConfig
```

多房间参数配置


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **RoomProfileType** | [room_profile_type](#AudioRoomConfig-room_profile_type) |
| **bool** | [is_auto_subscribe_audio](#AudioRoomConfig-is_auto_subscribe_audio) |
| **bool** | [is_auto_publish_audio](#AudioRoomConfig-is_auto_publish_audio) |


## 变量说明
<span id="AudioRoomConfig-room_profile_type"></span>
### room_profile_type
```cpp
RoomProfileType bytertc::AudioRoomConfig::room_profile_type = kRoomProfileTypeCommunication;
```
房间模式，参看 [RoomProfileType](#roomprofiletype)，默认为 `kRoomProfileTypeCommunication`，进房后不可更改。


<span id="AudioRoomConfig-is_auto_subscribe_audio"></span>
### is_auto_subscribe_audio
```cpp
bool bytertc::AudioRoomConfig::is_auto_subscribe_audio = true;
```
是否自动订阅音频流，默认为自动订阅。


<span id="AudioRoomConfig-is_auto_publish_audio"></span>
### is_auto_publish_audio
```cpp
bool bytertc::AudioRoomConfig::is_auto_publish_audio = false;
```
是否自动发布音视频流，默认为自动发布。 <br>
若调用 [setUserVisibility](Windows-api.md#IRTCRoom-setuservisibility) 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。  <br>
多房间场景下，若已在其中一个房间成功设置了自动发布，其他房间的自动发布设置均不会生效。



# MediaDeviceState
```cpp
enum bytertc::MediaDeviceState
```

媒体设备状态。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMediaDeviceStateStarted | 1 | 设备已开启 |
| kMediaDeviceStateStopped | 2 | 设备已停止 |
| kMediaDeviceStateRuntimeError | 3 | 设备运行时错误<br><br/>例如，当媒体设备的预期行为是正常采集，但没有收到采集数据时，将回调该状态。 |
| kMediaDeviceStatePaused | 4 | 设备已暂停。包括：<br/>+ 采集过程中，目标应用窗体最小化到任务栏。<br/>+ 开启采集或采集过程中，目标应用窗体被隐藏。<br/>+ 采集过程中，目标应用窗体正在被拉伸。<br/>+ 采集过程中，目标应用窗体正在被拖动。 |
| kMediaDeviceStateResumed | 5 | 设备已恢复 |
| kMediaDeviceStateAdded | 10 | 设备已插入 |
| kMediaDeviceStateRemoved | 11 | 设备被移除 |
| kMediaDeviceInterruptionBegan | 12 | 用户合盖打断了视频通话。如果系统未休眠或关机，将在开盖后自动恢复视频通话。 |
| kMediaDeviceInterruptionEnded | 13 | 视频通话已从合盖打断中恢复 |
| kMediaDeviceBecomeSystemDefault | 14 | 设备成为系统默认 |
| kMediaDeviceResignSystemDefault | 15 | 设备不再是系统默认 |


# MediaDeviceError
```cpp
enum bytertc::MediaDeviceError
```

媒体设备错误类型


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMediaDeviceErrorOK | 0 | 媒体设备正常 |
| kMediaDeviceErrorDeviceNoPermission | 1 | 没有权限启动媒体设备 |
| kMediaDeviceErrorDeviceBusy | 2 | 媒体设备已经在使用中 |
| kMediaDeviceErrorDeviceFailure | 3 | 媒体设备错误 |
| kMediaDeviceErrorDeviceNotFound | 4 | 未找到指定的媒体设备 |
| kMediaDeviceErrorDeviceDisconnected | 5 | 媒体设备被移除<br/>对象为采集屏幕流时，表明窗体被关闭或显示器被移除。 |
| kMediaDeviceErrorDeviceNoCallback | 6 | 设备没有数据回调 |
| kMediaDeviceErrorDeviceUNSupportFormat | 7 | 设备采样率不支持 |


# MediaDeviceWarning
```cpp
enum bytertc::MediaDeviceWarning
```

媒体设备警告


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMediaDeviceWarningOK | 0 | 无警告 |
| kMediaDeviceWarningOperationDenied | 1 | 非法设备操作。在使用外部设备时，调用了 SDK 内部设备 API。 |
| kMediaDeviceWarningCaptureSilence | 2 | 采集静音。 |
| kMediaDeviceWarningAndroidSysSilenceDisappear | 4 | Android 特有的静音消失 |
| kMediaDeviceWarningRecordingUseSilentDevice | 25 | 检测到用户正在使用设备过滤列表中的采集设备。 |
| kMediaDeviceWarningPlayoutUseSilentDevice | 26 | 检测到用户正在使用设备过滤列表中的播放设备。 |


# SubscribeState
```cpp
enum bytertc::SubscribeState
```

订阅媒体流状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kSubscribeStateSuccess | 0 | 订阅/取消订阅流成功 |
| kSubscribeStateFailedNotInRoom | 1 | 订阅/取消订阅流失败，本地用户未在房间中 |
| kSubscribeStateFailedStreamNotFound | 2 | 订阅/取消订阅流失败，房间内未找到指定的音视频流 |
| kSubscribeStateFailedOverLimit | 3 | 超过订阅流数上限 |


# RemoteUserPriority
```cpp
enum bytertc::RemoteUserPriority
```

远端用户优先级，在性能不足需要回退时，会优先回退优先级低的用户的音视频流


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRemoteUserPriorityLow | 0 | 用户优先级为低（默认值） |
| kRemoteUserPriorityMedium | 100 | 用户优先级为正常 |
| kRemoteUserPriorityHigh | 200 | 用户优先级为高 |


# PublishFallbackOption
```cpp
enum bytertc::PublishFallbackOption
```

发布端音视频流回退选项


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kPublishFallbackOptionDisabled | 0 | 上行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。 |
| kPublishFallbackOptionSimulcast | 1 | 上行网络不佳或设备性能不足时，发布的视频流会从大流到小流依次降级，直到与当前网络性能匹配，具体降级规则参看[性能回退](https://www.volcengine.com/docs/6348/70137)文档。 |


# SubscribeFallbackOption
```cpp
enum bytertc::SubscribeFallbackOption
```

订阅端音视频流回退选项。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kSubscribeFallbackOptionDisable | 0 | 下行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。 |
| kSubscribeFallbackOptionVideoStreamLow | 1 | 下行网络不佳或设备性能不足时，对视频流做降级处理，具体降级规则参看[音视频流回退](70137)。 <br>该设置仅对发布端调用 [enableSimulcastMode](Windows-api.md#IRTCVideo-enablesimulcastmode) 开启发送多路流功能的情况生效。 |
| kSubscribeFallbackOptionAudioOnly | 2 | 下行网络不佳或设备性能不足时，先对视频流做回退处理。当网络状况不满足接收弱流时，则自动取消接收视频，仅接收音频。<br>该设置仅对发布端调用 [enableSimulcastMode](Windows-api.md#IRTCVideo-enablesimulcastmode) 开启发送多路流功能的情况生效。 |


# FallbackOrRecoverReason
```cpp
enum bytertc::FallbackOrRecoverReason
```

远端订阅流发生回退或恢复的原因


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kFallbackOrRecoverReasonUnknown | -1 | 其他原因，非带宽和性能原因引起的回退或恢复。默认值 |
| kFallbackOrRecoverReasonSubscribeFallbackByBandwidth | 0 | 由带宽不足导致的订阅端音视频流回退。 |
| kFallbackOrRecoverReasonSubscribeFallbackByPerformance | 1 | 由性能不足导致的订阅端音视频流回退。 |
| kFallbackOrRecoverReasonSubscribeRecoverByBandwidth | 2 | 由带宽恢复导致的订阅端音视频流恢复。 |
| kFallbackOrRecoverReasonSubscribeRecoverByPerformance | 3 | 由性能恢复导致的订阅端音视频流恢复。 |
| kFallbackOrRecoverReasonPublishFallbackByBandwidth | 4 | 由带宽不足导致的发布端音视频流回退。 |
| kFallbackOrRecoverReasonPublishFallbackByPerformance | 5 | 由性能不足导致的发布端音视频流回退。 |
| kFallbackOrRecoverReasonPublishRecoverByBandwidth | 6 | 由带宽恢复导致的发布端音视频流恢复。 |
| kFallbackOrRecoverReasonPublishRecoverByPerformance | 7 | 由性能恢复导致的发布端音视频流恢复。 |


# PerformanceAlarmReason
```cpp
enum bytertc::PerformanceAlarmReason
```

性能相关告警的原因


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kPerformanceAlarmReasonBandwidthFallbacked | 0 | 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。 |
| kPerformanceAlarmReasonBandwidthResumed | 1 | 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。 |
| kPerformanceAlarmReasonPerformanceFallbacked | 2 | 如果未开启发送性能回退，收到此告警时，意味着性能不足；<br><br/>如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。 |
| kPerformanceAlarmReasonPerformanceResumed | 3 | 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复；<br><br/>如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。 |


# PerformanceAlarmMode
```cpp
enum bytertc::PerformanceAlarmMode
```

是否开启发布性能回退


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kPerformanceAlarmModeNormal | 0 | 未开启发布性能回退 |
| kPerformanceAlarmModeSimulcast | 1 | 已开启发布性能回退 |


# BusinessCheckCode
```cpp
enum bytertc::BusinessCheckCode
```

事务检查码  <br>
用户调用 `setBusinessId` 方法设置业务标识参数的返回错误码。  <br>


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| ERROR_ALREADY_IN_ROOM | -6001 | 用户已经在房间中。  <br><br/>业务标识需要在加入房间之前设置，加入后设置无效。  <br> |
| ERROR_INPUT_INVALIDATE | -6002 | 输入参数非法。  <br><br/>用户传入的业务标识参数非法，参数合法性参考 `setBusinessId` 方法的参数说明。  <br> |


# LocalAudioStreamState
```cpp
enum bytertc::LocalAudioStreamState
```

本地音频流状态。
SDK 通过 `onLocalAudioStateChanged` 回调本地音频流状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kLocalAudioStreamStateStopped | 0 | 本地音频默认初始状态。<br/>麦克风停止工作时回调该状态，对应错误码 kLocalAudioStreamErrorOk |
| kLocalAudioStreamStateRecording | 1 | 本地音频录制设备启动成功。<br/>采集到音频首帧时回调该状态，对应错误码 kLocalAudioStreamErrorOk |
| kLocalAudioStreamStateEncoding | 2 | 本地音频首帧编码成功。<br/>音频首帧编码成功时回调该状态，对应错误码 kLocalAudioStreamErrorOk |
| kLocalAudioStreamStateFailed | 3 | 本地音频启动失败，在以下时机回调该状态：  <br><br/>+ 本地录音设备启动失败，对应错误码 kLocalAudioStreamErrorRecordFailure <br><br/>+ 检测到没有录音设备权限，对应错误码 kLocalAudioStreamErrorDeviceNoPermission <br><br/>+ 音频编码失败，对应错误码 kLocalAudioStreamErrorEncodeFailure |
| kLocalAudioStreamMute | 4 | 本地音频静音成功后回调该状态。<br/>调用 [setAudioCaptureDeviceMute](Windows-api.md#IAudioDeviceManager-setaudiocapturedevicemute) 成功后回调，对应错误码 [LocalAudioStreamError](#localaudiostreamerror) 中的 kLocalAudioStreamErrorOk 。  <br> |
| kLocalAudioStreamUnmute | 5 | 本地音频解除静音成功后回调该状态。<br/>调用 [setAudioCaptureDeviceMute](Windows-api.md#IAudioDeviceManager-setaudiocapturedevicemute) 成功后回调，对应错误码 [LocalAudioStreamError](#localaudiostreamerror) 中的 kLocalAudioStreamErrorOk 。  <br> |


# LocalAudioStreamError
```cpp
enum bytertc::LocalAudioStreamError
```

本地音频流状态改变时的错误码。
SDK 通过 `onLocalAudioStateChanged` 回调该错误码。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kLocalAudioStreamErrorOk | 0 | 本地音频状态正常 |
| kLocalAudioStreamErrorFailure | 1 | 本地音频出错原因未知 |
| kLocalAudioStreamErrorDeviceNoPermission | 2 | 没有权限启动本地音频录制设备 |
| kLocalAudioStreamErrorRecordFailure | 4 | 本地音频录制失败，建议你检查录制设备是否正常工作 |
| kLocalAudioStreamErrorEncodeFailure | 5 | 本地音频编码失败 |
| kLocalAudioStreamErrorNoRecordingDevice | 6 | 没有可用的音频录制设备 |


# LocalVideoStreamState
```cpp
enum bytertc::LocalVideoStreamState
```

本地视频流状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kLocalVideoStreamStateStopped | 0 | 本地视频采集停止状态 |
| kLocalVideoStreamStateRecording | 1 | 本地视频采集设备启动成功 |
| kLocalVideoStreamStateEncoding | 2 | 本地视频采集后，首帧编码成功 |
| kLocalVideoStreamStateFailed | 3 | 本地视频采集设备启动失败 |


# RemoteAudioState
```cpp
enum bytertc::RemoteAudioState
```

远端音频流状态。<br>
用户可以通过 `onRemoteAudioStateChanged` 了解该状态。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRemoteAudioStateStopped | 0 | 不接收远端音频流。 <br><br/>以下情况下会触发回调 `onRemoteAudioStateChanged`：  <br><br/>+ 本地用户停止接收远端音频流，对应原因是：kRemoteAudioStateChangeReasonLocalMuted[RemoteAudioStateChangeReason](#remoteaudiostatechangereason)  <br><br/>+ 远端用户停止发送音频流，对应原因是：kRemoteAudioStateChangeReasonRemoteMuted[RemoteAudioStateChangeReason](#remoteaudiostatechangereason)  <br><br/>+ 远端用户离开房间，对应原因是：kRemoteAudioStateChangeReasonRemoteOffline[RemoteAudioStateChangeReason](#remoteaudiostatechangereason)  <br> |
| kRemoteAudioStateStarting | 1 | 开始接收远端音频流首包。<br><br/>刚收到远端音频流首包会触发回调 `onRemoteAudioStateChanged`，<br/>对应原因是： [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioStateChangeReasonLocalUnmuted` |
| kRemoteAudioStateDecoding | 2 | 远端音频流正在解码，正常播放。 <br><br/>以下情况下会触发回调 `onRemoteAudioStateChanged`：  <br><br/>+ 成功解码远端音频首帧，对应原因是： [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioStateChangeReasonLocalUnmuted` <br><br/>+ 网络由阻塞恢复正常，对应原因是： [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioStateChangeReasonNetworkRecovery` <br><br/>+ 本地用户恢复接收远端音频流，对应原因是：[RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioStateChangeReasonLocalUnmuted` <br><br/>+ 远端用户恢复发送音频流，对应原因是： [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioStateChangeReasonRemoteUnmuted` <br> |
| kRemoteAudioStateFrozen | 3 | 远端音频流卡顿。<br><br/>网络阻塞、丢包率大于 40% 时，会触发回调 `onRemoteAudioStateChanged`，<br/>对应原因是： [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioStateChangeReasonNetworkCongestion` |


# RemoteAudioStateChangeReason
```cpp
enum bytertc::RemoteAudioStateChangeReason
```

接收远端音频流状态改变的原因。  <br>
用户可以通过 `onRemoteAudioStateChanged` 了解该原因。


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRemoteAudioStateChangeReasonInternal | 0 | 内部原因 |
| kRemoteAudioStateChangeReasonNetworkCongestion | 1 | 网络阻塞 |
| kRemoteAudioStateChangeReasonNetworkRecovery | 2 | 网络恢复正常 |
| kRemoteAudioStateChangeReasonLocalMuted | 3 | 本地用户停止接收远端音频流 |
| kRemoteAudioStateChangeReasonLocalUnmuted | 4 | 本地用户恢复接收远端音频流 |
| kRemoteAudioStateChangeReasonRemoteMuted | 5 | 远端用户停止发送音频流 |
| kRemoteAudioStateChangeReasonRemoteUnmuted | 6 | 远端用户恢复发送音频流 |
| kRemoteAudioStateChangeReasonRemoteOffline | 7 | 远端用户离开房间 |


# RemoteVideoState
```cpp
enum bytertc::RemoteVideoState
```

远端视频流状态。状态改变时，会收到 `onRemoteVideoStateChanged` 回调


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRemoteVideoStateStopped | 0 | 远端视频流默认初始状态，视频尚未开始播放。 |
| kRemoteVideoStateStarting | 1 | 本地用户已接收远端视频流首包。 |
| kRemoteVideoStateDecoding | 2 | 远端视频流正在解码，正常播放。 |
| kRemoteVideoStateFrozen | 3 | 远端视频流卡顿，可能有网络等原因。 |
| kRemoteVideoStateFailed | 4 | 远端视频流播放失败。 |


# RemoteVideoStateChangeReason
```cpp
enum bytertc::RemoteVideoStateChangeReason
```

远端视频流状态改变的原因


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRemoteVideoStateChangeReasonInternal | 0 | 内部原因 |
| kRemoteVideoStateChangeReasonNetworkCongestion | 1 | 网络阻塞 |
| kRemoteVideoStateChangeReasonNetworkRecovery | 2 | 网络恢复正常 |
| kRemoteVideoStateChangeReasonLocalMuted | 3 | 本地用户停止接收远端视频流或本地用户禁用视频模块 |
| kRemoteVideoStateChangeReasonLocalUnmuted | 4 | 本地用户恢复接收远端视频流或本地用户启用视频模块 |
| kRemoteVideoStateChangeReasonRemoteMuted | 5 | 远端用户停止发送视频流或远端用户禁用视频模块 |
| kRemoteVideoStateChangeReasonRemoteUnmuted | 6 | 远端用户恢复发送视频流或远端用户启用视频模块 |
| kRemoteVideoStateChangeReasonRemoteOffline | 7 | 远端用户离开频道。状态转换参考 `onUserUnPublishStream`。 |


# SEIStreamEventType
```cpp
enum bytertc::SEIStreamEventType
```

黑帧视频流状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kSEIStreamEventTypeStreamAdd | 0 | 远端用户发布黑帧视频流。  <br><br/>纯语音通话场景下，远端用户调用 [sendSEIMessage](Windows-api.md#IRTCVideo-sendseimessage) 发送 SEI 数据时，SDK 会自动发布一路黑帧视频流，并触发该回调。 |
| kSEIStreamEventTypeStreamRemove | 1 | 远端黑帧视频流移除。该回调的触发时机包括：  <br><br/>+ 远端用户开启摄像头采集，由语音通话切换至视频通话，黑帧视频流停止发布；  <br><br/>+ 远端用户调用 [sendSEIMessage](Windows-api.md#IRTCVideo-sendseimessage) 后 1min 内未有 SEI 数据发送，黑帧视频流停止发布；  <br><br/>+ 远端用户调用 [setVideoSourceType](Windows-api.md#IRTCVideo-setvideosourcetype) 切换至自定义视频采集时，黑帧视频流停止发布。 |


# SourceWantedData
```cpp
struct bytertc::SourceWantedData
```

性能回退相关数据


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#SourceWantedData-width) |
| **int** | [height](#SourceWantedData-height) |
| **int** | [frame_rate](#SourceWantedData-frame_rate) |


## 变量说明
<span id="SourceWantedData-width"></span>
### width
```cpp
int bytertc::SourceWantedData::width;
```
<br>
未开启发布回退时，此值表示推荐的视频输入宽度，当回退模式为大小流模式时，表示当前推流的最大宽度
如果未开启发送性能回退，此值表示推荐的视频输入宽度；  <br>
如果开启了发送性能回退，此值表示当前推流的最大宽度。


<span id="SourceWantedData-height"></span>
### height
```cpp
int bytertc::SourceWantedData::height;
```
如果未开启发送性能回退，此值表示推荐的视频输入高度；<br>
如果开启了发送性能回退，此值表示当前推流的最大高度。


<span id="SourceWantedData-frame_rate"></span>
### frame_rate
```cpp
int bytertc::SourceWantedData::frame_rate;
```
如果未开启发送性能回退，此值表示推荐的视频输入帧率，单位 fps；<br>
如果开启了发送性能回退，此值表示当前推流的最大帧率，单位 fps。



# UserInfo
```cpp
struct bytertc::UserInfo
```

用户信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [uid](#UserInfo-uid) |
| **const char*** | [extra_info](#UserInfo-extra_info) |


## 变量说明
<span id="UserInfo-uid"></span>
### uid
```cpp
const char* bytertc::UserInfo::uid = nullptr;
```
用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-]{1,128}`。


<span id="UserInfo-extra_info"></span>
### extra_info
```cpp
const char* bytertc::UserInfo::extra_info = nullptr;
```
用户的额外信息，最大长度为 200 字节。会在 `onUserJoined` 中回调给远端用户。



# RtcRoomStats
```cpp
struct bytertc::RtcRoomStats
```

通话相关的统计信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [txLostrate](#RtcRoomStats-txlostrate) |
| **float** | [rxLostrate](#RtcRoomStats-rxlostrate) |
| **int** | [rtt](#RtcRoomStats-rtt) |
| **unsigned int** | [duration](#RtcRoomStats-duration) |
| **unsigned int** | [tx_bytes](#RtcRoomStats-tx_bytes) |
| **unsigned int** | [rx_bytes](#RtcRoomStats-rx_bytes) |
| **unsigned short** | [tx_kbitrate](#RtcRoomStats-tx_kbitrate) |
| **unsigned short** | [rx_kbitrate](#RtcRoomStats-rx_kbitrate) |
| **unsigned short** | [rx_audio_kbitrate](#RtcRoomStats-rx_audio_kbitrate) |
| **unsigned short** | [tx_audio_kbitrate](#RtcRoomStats-tx_audio_kbitrate) |
| **unsigned short** | [rx_video_kbitrate](#RtcRoomStats-rx_video_kbitrate) |
| **unsigned short** | [tx_video_kbitrate](#RtcRoomStats-tx_video_kbitrate) |
| **unsigned short** | [rx_screen_kbitrate](#RtcRoomStats-rx_screen_kbitrate) |
| **unsigned short** | [tx_screen_kbitrate](#RtcRoomStats-tx_screen_kbitrate) |
| **unsigned int** | [user_count](#RtcRoomStats-user_count) |
| **double** | [cpu_app_usage](#RtcRoomStats-cpu_app_usage) |
| **int** | [tx_jitter](#RtcRoomStats-tx_jitter) |
| **int** | [rx_jitter](#RtcRoomStats-rx_jitter) |
| **unsigned short** | [tx_cellular_kbitrate](#RtcRoomStats-tx_cellular_kbitrate) |
| **unsigned short** | [rx_cellular_kbitrate](#RtcRoomStats-rx_cellular_kbitrate) |


## 变量说明
<span id="RtcRoomStats-txlostrate"></span>
### txLostrate
```cpp
float bytertc::RtcRoomStats::txLostrate;
```
当前应用的上行丢包率，取值范围为 [0, 1]


<span id="RtcRoomStats-rxlostrate"></span>
### rxLostrate
```cpp
float bytertc::RtcRoomStats::rxLostrate;
```
当前应用的下行丢包率，取值范围为 [0, 1]


<span id="RtcRoomStats-rtt"></span>
### rtt
```cpp
int bytertc::RtcRoomStats::rtt;
```
客户端到服务端数据传输的往返时延（单位 ms）


<span id="RtcRoomStats-duration"></span>
### duration
```cpp
unsigned int bytertc::RtcRoomStats::duration;
```
进房到退房之间累计时长，单位为 s


<span id="RtcRoomStats-tx_bytes"></span>
### tx_bytes
```cpp
unsigned int bytertc::RtcRoomStats::tx_bytes;
```
本地用户的总发送字节数 (bytes)，累计值


<span id="RtcRoomStats-rx_bytes"></span>
### rx_bytes
```cpp
unsigned int bytertc::RtcRoomStats::rx_bytes;
```
本地用户的总接收字节数 (bytes)，累计值


<span id="RtcRoomStats-tx_kbitrate"></span>
### tx_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::tx_kbitrate;
```
发送码率（kbps），获取该数据时的瞬时值


<span id="RtcRoomStats-rx_kbitrate"></span>
### rx_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::rx_kbitrate;
```
接收码率（kbps），获取该数据时的瞬时值


<span id="RtcRoomStats-rx_audio_kbitrate"></span>
### rx_audio_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::rx_audio_kbitrate;
```
音频接收码率（kbps），获取该数据时的瞬时值


<span id="RtcRoomStats-tx_audio_kbitrate"></span>
### tx_audio_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::tx_audio_kbitrate;
```
音频包的发送码率（kbps），获取该数据时的瞬时值


<span id="RtcRoomStats-rx_video_kbitrate"></span>
### rx_video_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::rx_video_kbitrate;
```
视频接收码率（kbps），获取该数据时的瞬时值


<span id="RtcRoomStats-tx_video_kbitrate"></span>
### tx_video_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::tx_video_kbitrate;
```
视频发送码率（kbps），获取该数据时的瞬时值


<span id="RtcRoomStats-rx_screen_kbitrate"></span>
### rx_screen_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::rx_screen_kbitrate;
```
屏幕接收码率，获取该数据时的瞬时值，单位为 Kbps


<span id="RtcRoomStats-tx_screen_kbitrate"></span>
### tx_screen_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::tx_screen_kbitrate;
```
屏幕发送码率，获取该数据时的瞬时值，单位为 Kbps


<span id="RtcRoomStats-user_count"></span>
### user_count
```cpp
unsigned int bytertc::RtcRoomStats::user_count;
```
当前房间内的可见用户人数


<span id="RtcRoomStats-cpu_app_usage"></span>
### cpu_app_usage
```cpp
double bytertc::RtcRoomStats::cpu_app_usage;
```
当前应用的 CPU 使用率 (%)


<span id="RtcRoomStats-tx_jitter"></span>
### tx_jitter
```cpp
int bytertc::RtcRoomStats::tx_jitter;
```
系统上行网络抖动（ms）


<span id="RtcRoomStats-rx_jitter"></span>
### rx_jitter
```cpp
int bytertc::RtcRoomStats::rx_jitter;
```
系统下行网络抖动（ms）


<span id="RtcRoomStats-tx_cellular_kbitrate"></span>
### tx_cellular_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::tx_cellular_kbitrate;
```
蜂窝路径发送的码率 (kbps)，为获取该数据时的瞬时值


<span id="RtcRoomStats-rx_cellular_kbitrate"></span>
### rx_cellular_kbitrate
```cpp
unsigned short bytertc::RtcRoomStats::rx_cellular_kbitrate;
```
蜂窝路径接收码率 (kbps)，为获取该数据时的瞬时值



# VideoCodecType
```cpp
enum bytertc::VideoCodecType
```

视频的编码类型


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoCodecTypeUnknown | 0 | 未知类型 |
| kVideoCodecTypeH264 | 1 | 标准 H264 编码格式 |
| kVideoCodecTypeByteVC1 | 2 | ByteVC1 编码格式 |


# LocalAudioStats
```cpp
struct bytertc::LocalAudioStats
```

本地音频流统计信息，统计周期为 2s 。  <br>
本地用户发布音频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
通知用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [audio_loss_rate](#LocalAudioStats-audio_loss_rate) |
| **int** | [send_kbitrate](#LocalAudioStats-send_kbitrate) |
| **int** | [record_sample_rate](#LocalAudioStats-record_sample_rate) |
| **int** | [stats_interval](#LocalAudioStats-stats_interval) |
| **int** | [rtt](#LocalAudioStats-rtt) |
| **int** | [num_channels](#LocalAudioStats-num_channels) |
| **int** | [sent_sample_rate](#LocalAudioStats-sent_sample_rate) |
| **int** | [jitter](#LocalAudioStats-jitter) |


## 变量说明
<span id="LocalAudioStats-audio_loss_rate"></span>
### audio_loss_rate
```cpp
float bytertc::LocalAudioStats::audio_loss_rate;
```
音频丢包率。此次统计周期内的音频上行丢包率，单位为 % ，取值范围为 [0, 1]。  <br>


<span id="LocalAudioStats-send_kbitrate"></span>
### send_kbitrate
```cpp
int bytertc::LocalAudioStats::send_kbitrate;
```
发送码率。此次统计周期内的音频发送码率，单位为 kbps 。  <br>


<span id="LocalAudioStats-record_sample_rate"></span>
### record_sample_rate
```cpp
int bytertc::LocalAudioStats::record_sample_rate;
```
采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  <br>


<span id="LocalAudioStats-stats_interval"></span>
### stats_interval
```cpp
int bytertc::LocalAudioStats::stats_interval;
```
统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
此字段用于设置回调的统计周期，默认设置为 2s 。


<span id="LocalAudioStats-rtt"></span>
### rtt
```cpp
int bytertc::LocalAudioStats::rtt;
```
往返时延。单位为 ms 。  <br>


<span id="LocalAudioStats-num_channels"></span>
### num_channels
```cpp
int bytertc::LocalAudioStats::num_channels;
```
音频声道数。  <br>


<span id="LocalAudioStats-sent_sample_rate"></span>
### sent_sample_rate
```cpp
int bytertc::LocalAudioStats::sent_sample_rate;
```
音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。  <br>


<span id="LocalAudioStats-jitter"></span>
### jitter
```cpp
int bytertc::LocalAudioStats::jitter;
```
音频上行网络抖动，单位为 ms 。  <br>



# RemoteAudioStats
```cpp
struct bytertc::RemoteAudioStats
```

远端音频流统计信息，统计周期为 2s。  <br>
本地用户订阅远端音频流成功后，SDK 会周期性地通过 `onRemoteStreamStats` 通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [audio_loss_rate](#RemoteAudioStats-audio_loss_rate) |
| **int** | [received_kbitrate](#RemoteAudioStats-received_kbitrate) |
| **int** | [stall_count](#RemoteAudioStats-stall_count) |
| **int** | [stall_duration](#RemoteAudioStats-stall_duration) |
| **long** | [e2e_delay](#RemoteAudioStats-e2e_delay) |
| **int** | [playout_sample_rate](#RemoteAudioStats-playout_sample_rate) |
| **int** | [stats_interval](#RemoteAudioStats-stats_interval) |
| **int** | [rtt](#RemoteAudioStats-rtt) |
| **int** | [total_rtt](#RemoteAudioStats-total_rtt) |
| **int** | [quality](#RemoteAudioStats-quality) |
| **int** | [jitter_buffer_delay](#RemoteAudioStats-jitter_buffer_delay) |
| **int** | [num_channels](#RemoteAudioStats-num_channels) |
| **int** | [received_sample_rate](#RemoteAudioStats-received_sample_rate) |
| **int** | [frozen_rate](#RemoteAudioStats-frozen_rate) |
| **int** | [concealed_samples](#RemoteAudioStats-concealed_samples) |
| **int** | [concealment_event](#RemoteAudioStats-concealment_event) |
| **int** | [dec_sample_rate](#RemoteAudioStats-dec_sample_rate) |
| **int** | [dec_duration](#RemoteAudioStats-dec_duration) |
| **int** | [jitter](#RemoteAudioStats-jitter) |


## 变量说明
<span id="RemoteAudioStats-audio_loss_rate"></span>
### audio_loss_rate
```cpp
float bytertc::RemoteAudioStats::audio_loss_rate;
```
音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  <br>


<span id="RemoteAudioStats-received_kbitrate"></span>
### received_kbitrate
```cpp
int bytertc::RemoteAudioStats::received_kbitrate;
```
接收码率。统计周期内的音频接收码率，单位为 kbps 。  <br>


<span id="RemoteAudioStats-stall_count"></span>
### stall_count
```cpp
int bytertc::RemoteAudioStats::stall_count;
```
音频卡顿次数。统计周期内的卡顿次数。  <br>


<span id="RemoteAudioStats-stall_duration"></span>
### stall_duration
```cpp
int bytertc::RemoteAudioStats::stall_duration;
```
音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  <br>


<span id="RemoteAudioStats-e2e_delay"></span>
### e2e_delay
```cpp
long bytertc::RemoteAudioStats::e2e_delay;
```
用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>


<span id="RemoteAudioStats-playout_sample_rate"></span>
### playout_sample_rate
```cpp
int bytertc::RemoteAudioStats::playout_sample_rate;
```
播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  <br>


<span id="RemoteAudioStats-stats_interval"></span>
### stats_interval
```cpp
int bytertc::RemoteAudioStats::stats_interval;
```
统计间隔。此次统计周期的间隔，单位为 ms 。  <br>


<span id="RemoteAudioStats-rtt"></span>
### rtt
```cpp
int bytertc::RemoteAudioStats::rtt;
```
客户端到服务端数据传输的往返时延，单位为 ms。 <br>


<span id="RemoteAudioStats-total_rtt"></span>
### total_rtt
```cpp
int bytertc::RemoteAudioStats::total_rtt;
```
发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  <br>


<span id="RemoteAudioStats-quality"></span>
### quality
```cpp
int bytertc::RemoteAudioStats::quality;
```
远端用户发送的音频流质量。参看 [NetworkQuality](#networkquality)。


<span id="RemoteAudioStats-jitter_buffer_delay"></span>
### jitter_buffer_delay
```cpp
int bytertc::RemoteAudioStats::jitter_buffer_delay;
```
因引入 jitter buffer 机制导致的延时。单位为 ms 。  <br>


<span id="RemoteAudioStats-num_channels"></span>
### num_channels
```cpp
int bytertc::RemoteAudioStats::num_channels;
```
音频声道数。  <br>


<span id="RemoteAudioStats-received_sample_rate"></span>
### received_sample_rate
```cpp
int bytertc::RemoteAudioStats::received_sample_rate;
```
音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  <br>


<span id="RemoteAudioStats-frozen_rate"></span>
### frozen_rate
```cpp
int bytertc::RemoteAudioStats::frozen_rate;
```
远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。


<span id="RemoteAudioStats-concealed_samples"></span>
### concealed_samples
```cpp
int bytertc::RemoteAudioStats::concealed_samples;
```
音频丢包补偿(PLC) 样点总个数。  <br>


<span id="RemoteAudioStats-concealment_event"></span>
### concealment_event
```cpp
int bytertc::RemoteAudioStats::concealment_event;
```
音频丢包补偿(PLC) 累计次数。  <br>


<span id="RemoteAudioStats-dec_sample_rate"></span>
### dec_sample_rate
```cpp
int bytertc::RemoteAudioStats::dec_sample_rate;
```
音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  <br>


<span id="RemoteAudioStats-dec_duration"></span>
### dec_duration
```cpp
int bytertc::RemoteAudioStats::dec_duration;
```
此次订阅中，对远端音频流进行解码的累计耗时。单位为 s。


<span id="RemoteAudioStats-jitter"></span>
### jitter
```cpp
int bytertc::RemoteAudioStats::jitter;
```
音频下行网络抖动，单位为 ms 。  <br>



# LocalVideoStats
```cpp
struct bytertc::LocalVideoStats
```

本地视频流统计信息，统计周期为 2s 。  <br>
本地用户发布视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
通知用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [sent_kbitrate](#LocalVideoStats-sent_kbitrate) |
| **int** | [input_frame_rate](#LocalVideoStats-input_frame_rate) |
| **int** | [sent_frame_rate](#LocalVideoStats-sent_frame_rate) |
| **int** | [encoder_output_frame_rate](#LocalVideoStats-encoder_output_frame_rate) |
| **int** | [renderer_output_frame_rate](#LocalVideoStats-renderer_output_frame_rate) |
| **int** | [stats_interval](#LocalVideoStats-stats_interval) |
| **float** | [video_loss_rate](#LocalVideoStats-video_loss_rate) |
| **int** | [rtt](#LocalVideoStats-rtt) |
| **int** | [encoded_bitrate](#LocalVideoStats-encoded_bitrate) |
| **int** | [encoded_frame_width](#LocalVideoStats-encoded_frame_width) |
| **int** | [encoded_frame_height](#LocalVideoStats-encoded_frame_height) |
| **int** | [encoded_frame_count](#LocalVideoStats-encoded_frame_count) |
| **VideoCodecType** | [codec_type](#LocalVideoStats-codec_type) |
| **bool** | [is_screen](#LocalVideoStats-is_screen) |
| **int** | [jitter](#LocalVideoStats-jitter) |


## 变量说明
<span id="LocalVideoStats-sent_kbitrate"></span>
### sent_kbitrate
```cpp
int bytertc::LocalVideoStats::sent_kbitrate;
```
发送码率。此次统计周期内实际发送的分辨率最大的视频流的发送码率，单位为 Kbps


<span id="LocalVideoStats-input_frame_rate"></span>
### input_frame_rate
```cpp
int bytertc::LocalVideoStats::input_frame_rate;
```
采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。


<span id="LocalVideoStats-sent_frame_rate"></span>
### sent_frame_rate
```cpp
int bytertc::LocalVideoStats::sent_frame_rate;
```
发送帧率。此次统计周期内实际发送的分辨率最大的视频流的视频发送帧率，单位为 fps 。


<span id="LocalVideoStats-encoder_output_frame_rate"></span>
### encoder_output_frame_rate
```cpp
int bytertc::LocalVideoStats::encoder_output_frame_rate;
```
编码器输出帧率。当前编码器在此次统计周期内实际发送的分辨率最大的视频流的输出帧率，单位为 fps 。


<span id="LocalVideoStats-renderer_output_frame_rate"></span>
### renderer_output_frame_rate
```cpp
int bytertc::LocalVideoStats::renderer_output_frame_rate;
```
本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。


<span id="LocalVideoStats-stats_interval"></span>
### stats_interval
```cpp
int bytertc::LocalVideoStats::stats_interval;
```
统计间隔，单位为 ms 。
此字段用于设置回调的统计周期，默认设置为 2s 。


<span id="LocalVideoStats-video_loss_rate"></span>
### video_loss_rate
```cpp
float bytertc::LocalVideoStats::video_loss_rate;
```
视频丢包率。此次统计周期内的视频上行丢包率，取值范围为 [0，1] 。


<span id="LocalVideoStats-rtt"></span>
### rtt
```cpp
int bytertc::LocalVideoStats::rtt;
```
往返时延，单位为 ms 。


<span id="LocalVideoStats-encoded_bitrate"></span>
### encoded_bitrate
```cpp
int bytertc::LocalVideoStats::encoded_bitrate;
```
视频编码码率。此次统计周期内的实际发送的分辨率最大的视频流视频编码码率，单位为 Kbps 。


<span id="LocalVideoStats-encoded_frame_width"></span>
### encoded_frame_width
```cpp
int bytertc::LocalVideoStats::encoded_frame_width;
```
实际发送的分辨率最大的视频流的视频编码宽度，单位为 px 。


<span id="LocalVideoStats-encoded_frame_height"></span>
### encoded_frame_height
```cpp
int bytertc::LocalVideoStats::encoded_frame_height;
```
实际发送的分辨率最大的视频流的视频编码高度，单位为 px 。


<span id="LocalVideoStats-encoded_frame_count"></span>
### encoded_frame_count
```cpp
int bytertc::LocalVideoStats::encoded_frame_count;
```
此次统计周期内实际发送的分辨率最大的视频流的发送的视频帧总数。


<span id="LocalVideoStats-codec_type"></span>
### codec_type
```cpp
VideoCodecType bytertc::LocalVideoStats::codec_type;
```
视频的编码类型，具体参考 [VideoCodecType](#videocodectype) 。


<span id="LocalVideoStats-is_screen"></span>
### is_screen
```cpp
bool bytertc::LocalVideoStats::is_screen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


<span id="LocalVideoStats-jitter"></span>
### jitter
```cpp
int bytertc::LocalVideoStats::jitter;
```
视频上行网络抖动，单位为 ms 。  <br>



# RemoteVideoStats
```cpp
struct bytertc::RemoteVideoStats
```

远端视频流统计信息，统计周期为 2s 。  <br>
本地用户订阅远端视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#RemoteVideoStats-width) |
| **int** | [height](#RemoteVideoStats-height) |
| **float** | [video_loss_rate](#RemoteVideoStats-video_loss_rate) |
| **int** | [received_kbitrate](#RemoteVideoStats-received_kbitrate) |
| **int** | [decoder_output_frame_rate](#RemoteVideoStats-decoder_output_frame_rate) |
| **int** | [renderer_output_frame_rate](#RemoteVideoStats-renderer_output_frame_rate) |
| **int** | [stall_count](#RemoteVideoStats-stall_count) |
| **int** | [stall_duration](#RemoteVideoStats-stall_duration) |
| **long** | [e2e_delay](#RemoteVideoStats-e2e_delay) |
| **bool** | [is_screen](#RemoteVideoStats-is_screen) |
| **int** | [stats_interval](#RemoteVideoStats-stats_interval) |
| **int** | [rtt](#RemoteVideoStats-rtt) |
| **int** | [frozen_rate](#RemoteVideoStats-frozen_rate) |
| **VideoCodecType** | [codec_type](#RemoteVideoStats-codec_type) |
| **int** | [video_index](#RemoteVideoStats-video_index) |
| **int** | [jitter](#RemoteVideoStats-jitter) |


## 变量说明
<span id="RemoteVideoStats-width"></span>
### width
```cpp
int bytertc::RemoteVideoStats::width;
```
视频宽度


<span id="RemoteVideoStats-height"></span>
### height
```cpp
int bytertc::RemoteVideoStats::height;
```
视频高度


<span id="RemoteVideoStats-video_loss_rate"></span>
### video_loss_rate
```cpp
float bytertc::RemoteVideoStats::video_loss_rate;
```
视频丢包率。统计周期内的视频下行丢包率，单位为 % ，取值范围：[0，1] 。


<span id="RemoteVideoStats-received_kbitrate"></span>
### received_kbitrate
```cpp
int bytertc::RemoteVideoStats::received_kbitrate;
```
接收码率。统计周期内的视频接收码率，单位为 kbps 。


<span id="RemoteVideoStats-decoder_output_frame_rate"></span>
### decoder_output_frame_rate
```cpp
int bytertc::RemoteVideoStats::decoder_output_frame_rate;
```
解码器输出帧率。统计周期内的视频解码器输出帧率，单位 fps 。


<span id="RemoteVideoStats-renderer_output_frame_rate"></span>
### renderer_output_frame_rate
```cpp
int bytertc::RemoteVideoStats::renderer_output_frame_rate;
```
渲染帧率。统计周期内的视频渲染帧率，单位 fps 。


<span id="RemoteVideoStats-stall_count"></span>
### stall_count
```cpp
int bytertc::RemoteVideoStats::stall_count;
```
卡顿次数。统计周期内的卡顿次数。


<span id="RemoteVideoStats-stall_duration"></span>
### stall_duration
```cpp
int bytertc::RemoteVideoStats::stall_duration;
```
卡顿时长。统计周期内的视频卡顿总时长。单位 ms 。


<span id="RemoteVideoStats-e2e_delay"></span>
### e2e_delay
```cpp
long bytertc::RemoteVideoStats::e2e_delay;
```
用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。


<span id="RemoteVideoStats-is_screen"></span>
### is_screen
```cpp
bool bytertc::RemoteVideoStats::is_screen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前数据来自主流还是屏幕流。


<span id="RemoteVideoStats-stats_interval"></span>
### stats_interval
```cpp
int bytertc::RemoteVideoStats::stats_interval;
```
统计间隔，此次统计周期的间隔，单位为 ms 。  <br>
此字段用于设置回调的统计周期，目前设置为 2s 。


<span id="RemoteVideoStats-rtt"></span>
### rtt
```cpp
int bytertc::RemoteVideoStats::rtt;
```
往返时延，单位为 ms 。


<span id="RemoteVideoStats-frozen_rate"></span>
### frozen_rate
```cpp
int bytertc::RemoteVideoStats::frozen_rate;
```
远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。


<span id="RemoteVideoStats-codec_type"></span>
### codec_type
```cpp
VideoCodecType bytertc::RemoteVideoStats::codec_type;
```
视频的编码类型，具体参考 [VideoCodecType](#videocodectype) 。


<span id="RemoteVideoStats-video_index"></span>
### video_index
```cpp
int bytertc::RemoteVideoStats::video_index;
```
对应多种分辨率的流的下标。


<span id="RemoteVideoStats-jitter"></span>
### jitter
```cpp
int bytertc::RemoteVideoStats::jitter;
```
视频下行网络抖动，单位为 ms。  <br>



# LocalStreamStats
```cpp
struct bytertc::LocalStreamStats
```

本地音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
本地用户发布音/视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
通知本地用户发布的音/视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **LocalAudioStats** | [audio_stats](#LocalStreamStats-audio_stats) |
| **LocalVideoStats** | [video_stats](#LocalStreamStats-video_stats) |
| **bool** | [is_screen](#LocalStreamStats-is_screen) |


## 变量说明
<span id="LocalStreamStats-audio_stats"></span>
### audio_stats
```cpp
LocalAudioStats bytertc::LocalStreamStats::audio_stats;
```
本地设备发送音频流的统计信息，详见 [LocalAudioStats](#localaudiostats)


<span id="LocalStreamStats-video_stats"></span>
### video_stats
```cpp
LocalVideoStats bytertc::LocalStreamStats::video_stats;
```
本地设备发送视频流的统计信息，详见 [LocalVideoStats](#localvideostats)


<span id="LocalStreamStats-is_screen"></span>
### is_screen
```cpp
bool bytertc::LocalStreamStats::is_screen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。



# RemoteStreamStats
```cpp
struct bytertc::RemoteStreamStats
```

用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [uid](#RemoteStreamStats-uid) |
| **RemoteAudioStats** | [audio_stats](#RemoteStreamStats-audio_stats) |
| **RemoteVideoStats** | [video_stats](#RemoteStreamStats-video_stats) |
| **bool** | [is_screen](#RemoteStreamStats-is_screen) |


## 变量说明
<span id="RemoteStreamStats-uid"></span>
### uid
```cpp
const char* bytertc::RemoteStreamStats::uid;
```
用户 ID 。音/视频来源的远端用户 ID 。  <br>


<span id="RemoteStreamStats-audio_stats"></span>
### audio_stats
```cpp
RemoteAudioStats bytertc::RemoteStreamStats::audio_stats;
```
远端音频流的统计信息，详见 [RemoteAudioStats](#remoteaudiostats)


<span id="RemoteStreamStats-video_stats"></span>
### video_stats
```cpp
RemoteVideoStats bytertc::RemoteStreamStats::video_stats;
```
远端视频流的统计信息，详见 [RemoteVideoStats](#remotevideostats)


<span id="RemoteStreamStats-is_screen"></span>
### is_screen
```cpp
bool bytertc::RemoteStreamStats::is_screen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。



# ProblemFeedbackOption
```cpp
enum bytertc::ProblemFeedbackOption
```

音视频质量反馈问题类型


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kProblemFeedbackOptionNone | 0 | 没有问题 |
| kProblemFeedbackOptionOtherMessage | (1 << 0) | 其他问题 |
| kProblemFeedbackOptionAudioNotClear | (1 << 1) | 声音不清晰 |
| kProblemFeedbackOptionVideoNotClear | (1 << 2) | 视频不清晰 |
| kProblemFeedbackOptionNotSync | (1 << 3) | 音视频不同步 |
| kProblemFeedbackOptionAudioLagging | (1 << 4) | 音频卡顿 |
| kProblemFeedbackOptionVideoLagging | (1 << 5) | 视频卡顿 |
| kProblemFeedbackOptionDisconnected | (1 << 6) | 连接失败 |
| kProblemFeedbackOptionNoAudio | (1 << 7) | 无声音 |
| kProblemFeedbackOptionNoVideo | (1 << 8) | 无画面 |
| kProblemFeedbackOptionAudioStrength | (1 << 9) | 声音过小 |
| kProblemFeedbackOptionEcho | (1 << 10) | 回声噪音 |
| KFeedbackOptionEarBackDelay | (1 << 11) | 耳返延迟大 |


# SysStats
```cpp
struct bytertc::SysStats
```

App 使用的 cpu 和内存信息。  <br>
信息由 SDK 周期性（2s）地通过 `onSysStats` 回调通知给用户。


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **unsigned int** | [cpu_cores](#SysStats-cpu_cores) |
| **double** | [cpu_app_usage](#SysStats-cpu_app_usage) |
| **double** | [cpu_total_usage](#SysStats-cpu_total_usage) |
| **double** | [memory_usage](#SysStats-memory_usage) |
| **unsigned long long** | [full_memory](#SysStats-full_memory) |
| **unsigned long long** | [total_memory_usage](#SysStats-total_memory_usage) |
| **unsigned long long** | [free_memory](#SysStats-free_memory) |
| **double** | [memory_ratio](#SysStats-memory_ratio) |
| **double** | [total_memory_ratio](#SysStats-total_memory_ratio) |


## 变量说明
<span id="SysStats-cpu_cores"></span>
### cpu_cores
```cpp
unsigned int bytertc::SysStats::cpu_cores;
```
当前系统 CPU 核数


<span id="SysStats-cpu_app_usage"></span>
### cpu_app_usage
```cpp
double bytertc::SysStats::cpu_app_usage;
```
当前应用的 cpu 使用率，取值范围为 [0, 1]。


<span id="SysStats-cpu_total_usage"></span>
### cpu_total_usage
```cpp
double bytertc::SysStats::cpu_total_usage;
```
当前系统的 cpu 使用率，取值范围为 [0, 1]。


<span id="SysStats-memory_usage"></span>
### memory_usage
```cpp
double bytertc::SysStats::memory_usage;
```
当前应用的内存使用量（单位 MB）


<span id="SysStats-full_memory"></span>
### full_memory
```cpp
unsigned long long bytertc::SysStats::full_memory;
```
全量内存（单位MB）


<span id="SysStats-total_memory_usage"></span>
### total_memory_usage
```cpp
unsigned long long bytertc::SysStats::total_memory_usage;
```
系统已使用内存（单位MB）


<span id="SysStats-free_memory"></span>
### free_memory
```cpp
unsigned long long bytertc::SysStats::free_memory;
```
空闲可分配内存（单位MB）


<span id="SysStats-memory_ratio"></span>
### memory_ratio
```cpp
double bytertc::SysStats::memory_ratio;
```
当前应用的内存使用率（单位 %）


<span id="SysStats-total_memory_ratio"></span>
### total_memory_ratio
```cpp
double bytertc::SysStats::total_memory_ratio;
```
系统内存使用率（单位 %）



# EncryptType
```cpp
enum bytertc::EncryptType
```

自定义加密类型  <br>


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kEncryptTypeCustomize | 0 | 不使用内置加密。默认值。 |
| kEncryptTypeAES128CBC | 1 | AES-128-CBC 加密算法  <br> |
| kEncryptTypeAES256CBC | 2 | AES-256-CBC 加密算法  <br> |
| kEncryptTypeAES128ECB | 3 | AES-128-ECB 加密算法  <br> |
| kEncryptTypeAES256ECB | 4 | AES-256-ECB 加密算法  <br> |


# RtcUser
```cpp
struct bytertc::RtcUser
```

用户信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [user_id](#RtcUser-user_id) |
| **const char*** | [meta_data](#RtcUser-meta_data) |


## 变量说明
<span id="RtcUser-user_id"></span>
### user_id
```cpp
const char* bytertc::RtcUser::user_id;
```

<span id="RtcUser-meta_data"></span>
### meta_data
```cpp
const char* bytertc::RtcUser::meta_data;
```


# FirstFrameSendState
```cpp
enum bytertc::FirstFrameSendState
```

首帧发送状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kFirstFrameSendStateSending | 0 | 发送中 |
| kFirstFrameSendStateSent | 1 | 发送成功 |
| kFirstFrameSendStateEnd | 2 | 发送失败 |


# FirstFramePlayState
```cpp
enum bytertc::FirstFramePlayState
```

首帧播放状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kFirstFramePlayStatePlaying | 0 | 播放中 |
| kFirstFramePlayStatePlayed | 1 | 播放成功 |
| kFirstFramePlayStateEnd | 2 | 播放失败 |


# MuteState
```cpp
enum bytertc::MuteState
```

音视频流的发送/播放状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMuteStateOff | 0 | 发送 |
| kMuteStateOn | 1 | 停止发送 |


# StreamIndex
```cpp
enum bytertc::StreamIndex
```

流属性


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kStreamIndexMain | 0 | 主流。包括：<br><br/>+ 由摄像头/麦克风通过内部采集机制，采集到的视频/音频; <br><br/>+ 通过自定义采集，采集到的视频/音频。 |
| kStreamIndexScreen | 1 | 屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。 |


# RemoteStreamKey
```cpp
struct bytertc::RemoteStreamKey
```

远端流信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [room_id](#RemoteStreamKey-room_id) |
| **const char*** | [user_id](#RemoteStreamKey-user_id) |
| **StreamIndex** | [stream_index](#RemoteStreamKey-stream_index) |


## 变量说明
<span id="RemoteStreamKey-room_id"></span>
### room_id
```cpp
const char* bytertc::RemoteStreamKey::room_id;
```
媒体流所在房间的房间 ID。<br>
如果此媒体流是通过 `startForwardStreamToRooms` 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。


<span id="RemoteStreamKey-user_id"></span>
### user_id
```cpp
const char* bytertc::RemoteStreamKey::user_id;
```
用户 ID


<span id="RemoteStreamKey-stream_index"></span>
### stream_index
```cpp
StreamIndex bytertc::RemoteStreamKey::stream_index;
```
流属性，主流或屏幕流。参看 [StreamIndex](#streamindex)



# HttpProxyState
```cpp
enum bytertc::HttpProxyState
```

HTTP/HTTPS 代理状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kHttpInit | 0 | HTTP/HTTPS 初始化状态 |
| kHttpConnected | 1 | HTTP/HTTPS 连接成功 |
| kHttpError | 2 | HTTP/HTTPS 连接失败 |


# Socks5ProxyState
```cpp
enum bytertc::Socks5ProxyState
```

SOCKS5 代理连接状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kSocks5Init | 0 | SOCKS5 连接初始化 |
| kSocks5Connected | 1 | SOCKS5 连接成功 |
| kSocks5Error | 2 | SOCKS5 连接错误 |
| kSocks5TcpConnectFail | 3 | TCP 连接失败 |
| kSocks5TcpClose | 4 | TCP 连接关闭 |
| kSocks5ProtocolTcpFail | 5 | SOCKS 协议 TCP 协商阶段失败 |
| kSocks5ProtocolUdpFail | 6 | UDP 连接失败 |
| kSocks5AuthFail | 7 | 授权失败 |
| kSocks5Unknown | 8 | 未知状态 |


# RecordingFileType
```cpp
enum bytertc::RecordingFileType
```

本地录制文件的存储格式


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRecordingFileTypeAAC | 0 | aac 格式文件 |
| kRecordingFileTypeMP4 | 1 | mp4 格式文件 |


# RecordingState
```cpp
enum bytertc::RecordingState
```

本地录制的状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRecordingStateError | 0 | 录制异常 |
| kRecordingStateProcessing | 1 | 录制进行中 |
| kRecordingStateSuccess | 2 | 录制文件保存成功，调用 `stopFileRecording` 结束录制之后才会收到该状态码。 |


# RecordingErrorCode
```cpp
enum bytertc::RecordingErrorCode
```

本地录制的错误码


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRecordingErrorCodeOk | 0 | 录制正常 |
| kRecordingErrorCodeNoPermission | -1 | 没有文件写权限 |
| kRecordingErrorCodeNotSupport | -2 | 当前版本 SDK 不支持本地录制功能，请联系技术支持人员 |
| kRecordingErrorCodeOther | -3 | 其他异常 |


# RecordingProgress
```cpp
struct bytertc::RecordingProgress
```

本地录制进度


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **unsigned long long** | [duration](#RecordingProgress-duration) |
| **unsigned long long** | [file_size](#RecordingProgress-file_size) |


## 变量说明
<span id="RecordingProgress-duration"></span>
### duration
```cpp
unsigned long long bytertc::RecordingProgress::duration;
```
当前文件的累计录制时长，单位：毫秒


<span id="RecordingProgress-file_size"></span>
### file_size
```cpp
unsigned long long bytertc::RecordingProgress::file_size;
```
当前录制文件的大小，单位：byte



# RecordingInfo
```cpp
struct bytertc::RecordingInfo
```

本地录制的详细信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [file_path](#RecordingInfo-file_path) |
| **VideoCodecType** | [video_codec_type](#RecordingInfo-video_codec_type) |
| **int** | [width](#RecordingInfo-width) |
| **int** | [height](#RecordingInfo-height) |


## 变量说明
<span id="RecordingInfo-file_path"></span>
### file_path
```cpp
const char* bytertc::RecordingInfo::file_path;
```
录制文件的绝对路径，包含文件名和文件后缀


<span id="RecordingInfo-video_codec_type"></span>
### video_codec_type
```cpp
VideoCodecType bytertc::RecordingInfo::video_codec_type;
```
录制文件的视频编码类型，参看 [VideoCodecType](#videocodectype)


<span id="RecordingInfo-width"></span>
### width
```cpp
int bytertc::RecordingInfo::width;
```
录制视频的宽，单位：像素。纯音频录制请忽略该字段


<span id="RecordingInfo-height"></span>
### height
```cpp
int bytertc::RecordingInfo::height;
```
录制视频的高，单位：像素。纯音频录制请忽略该字段



# RecordingConfig
```cpp
struct bytertc::RecordingConfig
```

本地录制参数配置


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [dir_path](#RecordingConfig-dir_path) |
| **RecordingFileType** | [file_type](#RecordingConfig-file_type) |


## 变量说明
<span id="RecordingConfig-dir_path"></span>
### dir_path
```cpp
const char* bytertc::RecordingConfig::dir_path;
```
录制文件保存的绝对路径，需精确到文件夹，文件名由 RTC 自动生成。你需要确保对该路径具有读写权限。


<span id="RecordingConfig-file_type"></span>
### file_type
```cpp
RecordingFileType bytertc::RecordingConfig::file_type;
```
录制存储文件格式，参看 [RecordingFileType](#recordingfiletype)



# UserWorkerType
```cpp
enum bytertc::UserWorkerType
```

定义linux用户的用户功能  <br>


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| UserWorkerNormal | 0 | 正常用户，没有任何特殊属性  <br> |
| UserWorkerSupportSip | (1 << 0) | 用户支持SIP流，信令只下发SIP流  <br> |
| UserWorkerByteVc1Transcoder | (1 << 1) | 用户支持屏幕流的bytevc1到H264转码  <br> |
| UserWorkerNeedUserListAndCb | (1 << 2) | 用户需要信令服务器下发全量的用户列表和回调函数  <br> |
| UserWorkerNeedStreamCallBack | (1 << 3) | 用户需要在房间进入多人模式时获取房间内所有流的相关回调  <br> |


# AVSyncState
```cpp
enum bytertc::AVSyncState
```

音视频同步状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAVSyncStateAVStreamSyncBegin | 0 | 音视频开始同步 |
| kAVSyncStateAudioStreamRemove | 1 | 音视频同步过程中音频移除，但不影响当前的同步关系 |
| kAVSyncStateVdieoStreamRemove | 2 | 音视频同步过程中视频移除，但不影响当前的同步关系 |


# SyncInfoStreamType
```cpp
enum bytertc::SyncInfoStreamType
```

媒体流信息同步的流类型


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kSyncInfoStreamTypeAudio | 0 | 音频流 |


# StreamSycnInfoConfig
```cpp
struct bytertc::StreamSycnInfoConfig
```

媒体流信息同步的相关配置


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **StreamIndex** | [stream_index](#StreamSycnInfoConfig-stream_index) |
| **int** | [repeat_count](#StreamSycnInfoConfig-repeat_count) |
| **SyncInfoStreamType** | [stream_type](#StreamSycnInfoConfig-stream_type) |


## 变量说明
<span id="StreamSycnInfoConfig-stream_index"></span>
### stream_index
```cpp
StreamIndex bytertc::StreamSycnInfoConfig::stream_index;
```
流属性，主流或屏幕流。见 [StreamIndex](#streamindex)


<span id="StreamSycnInfoConfig-repeat_count"></span>
### repeat_count
```cpp
int bytertc::StreamSycnInfoConfig::repeat_count;
```
消息发送的重复次数，取值范围是 [0,25]，建议设置为 [3,5]。


<span id="StreamSycnInfoConfig-stream_type"></span>
### stream_type
```cpp
SyncInfoStreamType bytertc::StreamSycnInfoConfig::stream_type;
```
媒体流信息同步的流类型，见 [SyncInfoStreamType](#syncinfostreamtype)



# ForwardStreamInfo
```cpp
struct bytertc::ForwardStreamInfo
```

媒体流跨房间转发的目标房间的相关信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [token](#ForwardStreamInfo-token) |
| **const char*** | [room_id](#ForwardStreamInfo-room_id) |


## 变量说明
<span id="ForwardStreamInfo-token"></span>
### token
```cpp
const char* bytertc::ForwardStreamInfo::token;
```
使用转发目标房间 roomID 和 UserID 生成 Token。<br>
测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。<br>
如果 Token 无效，转发失败。


<span id="ForwardStreamInfo-room_id"></span>
### room_id
```cpp
const char* bytertc::ForwardStreamInfo::room_id;
```
跨间转发媒体流过程中目标房间 ID<br>



# ForwardStreamConfiguration
```cpp
struct bytertc::ForwardStreamConfiguration
```

媒体流跨房间转发的目标房间的相关信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ForwardStreamInfo*** | [forward_stream_dests](#ForwardStreamConfiguration-forward_stream_dests) |
| **int** | [dest_count](#ForwardStreamConfiguration-dest_count) |


## 变量说明
<span id="ForwardStreamConfiguration-forward_stream_dests"></span>
### forward_stream_dests
```cpp
ForwardStreamInfo* bytertc::ForwardStreamConfiguration::forward_stream_dests = nullptr;
```
目标房间信息，数组中的每个元素包含一个房间的信息。


<span id="ForwardStreamConfiguration-dest_count"></span>
### dest_count
```cpp
int bytertc::ForwardStreamConfiguration::dest_count = 0;
```
目标房间数量。媒体流同时转发的目标房间数量建议小于等于 4 个。



# ForwardStreamState
```cpp
enum bytertc::ForwardStreamState
```

媒体流跨房间转发状态


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kForwardStreamStateIdle | 0 | 空闲状态<br/>+ 成功调用 `stopForwardStreamToRooms` 后，所有目标房间为空闲状态。<br/>+ 成功调用 `updateForwardStreamToRooms` 减少目标房间后，本次减少的目标房间为空闲状态。 |
| kForwardStreamStateSuccess | 1 | 开始转发<br/>+ 调用 `startForwardStreamToRooms` 成功向所有房间开始转发媒体流后，返回此状态。<br/>+ 调用 `updateForwardStreamToRooms` 后，成功向新增目标房间开始转发媒体流后，返回此状态。 |
| kForwardStreamStateFailure | 2 | 转发失败，失败详情参考 [ForwardStreamError](#forwardstreamerror)<br/>调用 `startForwardStreamToRooms` 或 `updateForwardStreamToRooms` 后，如遇转发失败，返回此状态。 |


# ForwardStreamError
```cpp
enum bytertc::ForwardStreamError
```

媒体流跨房间转发过程中抛出的错误码


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kForwardStreamErrorOK | 0 | 正常 |
| kForwardStreamErrorInvalidArgument | 1201 | 参数异常 |
| kForwardStreamErrorInvalidToken | 1202 | token 错误 |
| kForwardStreamErrorResponse | 1203 | 服务端异常 |
| kForwardStreamErrorRemoteKicked | 1204 | 目标房间有相同 user id 的用户加入，转发中断 |
| kForwardStreamErrorNotSupport | 1205 | 服务端不支持转发功能 |


# ForwardStreamEvent
```cpp
enum bytertc::ForwardStreamEvent
```

媒体流跨房间转发事件


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kForwardStreamEventDisconnected | 0 | 本端与服务器网络连接断开，暂停转发。 |
| kForwardStreamEventConnected | 1 | 本端与服务器网络连接恢复，转发服务连接成功。 |
| kForwardStreamEventInterrupt | 2 | 转发中断。转发过程中，如果相同 user_id 的用户进入目标房间，转发中断。 |
| kForwardStreamEventDstRoomUpdated | 3 | 目标房间已更新，由 `updateForwardStreamToRooms` 触发。 |
| kForwardStreamEventUnExpectAPICall | 4 | API 调用时序错误。例如，在调用 `startForwardStreamToRooms` 之前调用 `updateForwardStreamToRooms` 。 |


# ForwardStreamStateInfo
```cpp
struct bytertc::ForwardStreamStateInfo
```

跨房间转发媒体流过程中的不同目标房间的状态和错误信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [room_id](#ForwardStreamStateInfo-room_id) |
| **ForwardStreamState** | [state](#ForwardStreamStateInfo-state) |
| **ForwardStreamError** | [error](#ForwardStreamStateInfo-error) |


## 变量说明
<span id="ForwardStreamStateInfo-room_id"></span>
### room_id
```cpp
const char* bytertc::ForwardStreamStateInfo::room_id;
```
跨间转发媒体流过程中目标房间 ID<br>


<span id="ForwardStreamStateInfo-state"></span>
### state
```cpp
ForwardStreamState bytertc::ForwardStreamStateInfo::state;
```
跨房间转发媒体流过程中该目标房间的状态，参看 [ForwardStreamState](#forwardstreamstate)


<span id="ForwardStreamStateInfo-error"></span>
### error
```cpp
ForwardStreamError bytertc::ForwardStreamStateInfo::error;
```
跨房间转发媒体流过程中该目标房间抛出的错误码，参看 [ForwardStreamError](#forwardstreamerror)



# ForwardStreamEventInfo
```cpp
struct bytertc::ForwardStreamEventInfo
```

跨房间转发媒体流过程中的不同目标房间发生的事件


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [room_id](#ForwardStreamEventInfo-room_id) |
| **ForwardStreamEvent** | [event](#ForwardStreamEventInfo-event) |


## 变量说明
<span id="ForwardStreamEventInfo-room_id"></span>
### room_id
```cpp
const char* bytertc::ForwardStreamEventInfo::room_id;
```
跨房间转发媒体流过程中的发生该事件的目标房间 ID<br>
空字符串代表所有目标房间


<span id="ForwardStreamEventInfo-event"></span>
### event
```cpp
ForwardStreamEvent bytertc::ForwardStreamEventInfo::event;
```
跨房间转发媒体流过程中该目标房间发生的事件，参看 [ForwardStreamEvent](#forwardstreamevent)



# ByteWatermark
```cpp
struct bytertc::ByteWatermark
```

水印图片相对视频流的位置和大小。


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [x](#ByteWatermark-x) |
| **float** | [y](#ByteWatermark-y) |
| **float** | [width](#ByteWatermark-width) |
| **float** | [height](#ByteWatermark-height) |


## 变量说明
<span id="ByteWatermark-x"></span>
### x
```cpp
float bytertc::ByteWatermark::x;
```
水印图片相对视频流左上角的横向偏移与视频流宽度的比值，取值范围为 [0,1)。


<span id="ByteWatermark-y"></span>
### y
```cpp
float bytertc::ByteWatermark::y;
```
水印图片相对视频流左上角的纵向偏移与视频流高度的比值，取值范围为 [0,1)。


<span id="ByteWatermark-width"></span>
### width
```cpp
float bytertc::ByteWatermark::width;
```
水印图片宽度与视频流宽度的比值，取值范围 [0,1)。


<span id="ByteWatermark-height"></span>
### height
```cpp
float bytertc::ByteWatermark::height;
```
水印图片高度与视频流高度的比值，取值范围为 [0,1)。



# RTCWatermarkConfig
```cpp
struct bytertc::RTCWatermarkConfig
```

水印参数


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **bool** | [visibleInPreview](#RTCWatermarkConfig-visibleinpreview) |
| **ByteWatermark** | [positionInLandscapeMode](#RTCWatermarkConfig-positioninlandscapemode) |
| **ByteWatermark** | [positionInPortraitMode](#RTCWatermarkConfig-positioninportraitmode) |


## 变量说明
<span id="RTCWatermarkConfig-visibleinpreview"></span>
### visibleInPreview
```cpp
bool bytertc::RTCWatermarkConfig::visibleInPreview = true;
```
水印是否在视频预览中可见，默认可见。


<span id="RTCWatermarkConfig-positioninlandscapemode"></span>
### positionInLandscapeMode
```cpp
ByteWatermark bytertc::RTCWatermarkConfig::positionInLandscapeMode;
```
横屏时的水印位置和大小，参看 [ByteWatermark](#bytewatermark)。


<span id="RTCWatermarkConfig-positioninportraitmode"></span>
### positionInPortraitMode
```cpp
ByteWatermark bytertc::RTCWatermarkConfig::positionInPortraitMode;
```
视频编码的方向模式为竖屏时的水印位置和大小，参看 [ByteWatermark](#bytewatermark)。



# CloudProxyInfo
```cpp
struct bytertc::CloudProxyInfo
```

云代理信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [cloud_proxy_ip](#CloudProxyInfo-cloud_proxy_ip) |
| **int** | [cloud_proxy_port](#CloudProxyInfo-cloud_proxy_port) |


## 变量说明
<span id="CloudProxyInfo-cloud_proxy_ip"></span>
### cloud_proxy_ip
```cpp
const char* bytertc::CloudProxyInfo::cloud_proxy_ip;
```
云代理服务器 IP


<span id="CloudProxyInfo-cloud_proxy_port"></span>
### cloud_proxy_port
```cpp
int bytertc::CloudProxyInfo::cloud_proxy_port;
```
云代理服务器端口



# CloudProxyConfiguration
```cpp
struct bytertc::CloudProxyConfiguration
```

云代理相关信息


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **CloudProxyInfo*** | [cloud_proxies](#CloudProxyConfiguration-cloud_proxies) |
| **int** | [cloud_proxy_count](#CloudProxyConfiguration-cloud_proxy_count) |


## 变量说明
<span id="CloudProxyConfiguration-cloud_proxies"></span>
### cloud_proxies
```cpp
CloudProxyInfo* bytertc::CloudProxyConfiguration::cloud_proxies = nullptr;
```
云代理信息。


<span id="CloudProxyConfiguration-cloud_proxy_count"></span>
### cloud_proxy_count
```cpp
int bytertc::CloudProxyConfiguration::cloud_proxy_count = 0;
```
云代理数量。



# DeviceTransportType
```cpp
enum bytertc::DeviceTransportType
```

设备的传输方式


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kDeviceTransportTypeUnknown | 0 | 未知类型 |
| kDeviceTransportTypeBuiltIn | 1 | 系统内置 |
| kDeviceTransportTypeBlueToothUnknownMode | 2 | 未知模式蓝牙 |
| kDeviceTransportTypeBlueToothHandsFreeMode | 3 | 免提模式蓝牙 |
| kDeviceTransportTypeBlueToothStereoMode | 4 | 立体声模式蓝牙 |
| kDeviceTransportTypeDisplayAudio | 5 | 显示器/电视机音频设备 |
| kDeviceTransportTypeVirtual | 6 | 虚拟设备 |
| kDeviceTransportTypeUSB | 7 | USB设备 |
| kDeviceTransportTypePCI | 8 | PCI设备 |
| kDeviceTransportTypeAirPlay | 9 | AirPlay设备 |


# EchoTestResult
```cpp
enum class bytertc::EchoTestResult
```

音视频回路测试结果


`Defined in : bytertc_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kTestSuccess | 0 | 接收到采集的音视频的回放，通话回路检测成功 |
| kTestTimeout | 1 | 测试超过 60s 仍未完成，已自动停止 |
| kTestIntervalShort | 2 | 上一次测试结束和下一次测试开始之间的时间间隔少于 5s |
| kAudioDeviceError | 3 | 音频采集异常 |
| kVideoDeviceError | 4 | 视频采集异常 |
| kAudioReceiveError | 5 | 音频接收异常 |
| kVideoReceiveError | 6 | 视频接收异常 |
| kInternalError | 7 | 内部错误，不可恢复 |


# EchoTestConfig
```cpp
struct bytertc::EchoTestConfig
```

音视频回路测试参数


`Defined in : bytertc_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **void*** | [view](#EchoTestConfig-view) |
| **bool** | [enableAudio](#EchoTestConfig-enableaudio) |
| **bool** | [enableVideo](#EchoTestConfig-enablevideo) |
| **int** | [audioPropertiesReportInterval](#EchoTestConfig-audiopropertiesreportinterval) |
| **const char*** | [uid](#EchoTestConfig-uid) |
| **const char*** | [roomId](#EchoTestConfig-roomid) |
| **const char*** | [token](#EchoTestConfig-token) |


## 变量说明
<span id="EchoTestConfig-view"></span>
### view
```cpp
void* bytertc::EchoTestConfig::view;
```
用于渲染接收到的视频的视图


<span id="EchoTestConfig-enableaudio"></span>
### enableAudio
```cpp
bool bytertc::EchoTestConfig::enableAudio;
```
是否检测音频。检测设备为系统默认音频设备。  <br>

+ true：是  <br>
- 若使用 SDK 内部采集，此时设备麦克风会自动开启，并在 audioPropertiesReportInterval 值大于 0 时触发 `onLocalAudioPropertiesReport` 回调，你可以根据该回调判断麦克风的工作状态  <br>
- 若使用自定义采集，此时你需调用 [pushExternalAudioFrame](Windows-api.md#IRTCVideo-pushexternalaudioframe) 将采集到的音频推送给 SDK  <br>
+ flase：否  <br>


<span id="EchoTestConfig-enablevideo"></span>
### enableVideo
```cpp
bool bytertc::EchoTestConfig::enableVideo;
```
是否检测视频。PC 端默认检测列表中第一个视频设备。  <br>

+ true：是  <br>
- 若使用 SDK 内部采集，此时设备摄像头会自动开启  <br>
- 若使用自定义采集，此时你需调用 [pushExternalVideoFrame](Windows-api.md#IRTCVideo-pushexternalvideoframe) 将采集到的视频推送给 SDK  <br>
+ flase：否  <br>

**注意:**
视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。
视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。

<span id="EchoTestConfig-audiopropertiesreportinterval"></span>
### audioPropertiesReportInterval
```cpp
int bytertc::EchoTestConfig::audioPropertiesReportInterval;
```
音量信息提示间隔，单位：ms，默认为 100ms <br>

+ `<= 0`: 关闭信息提示  <br>
+ `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
+ `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>


<span id="EchoTestConfig-uid"></span>
### uid
```cpp
const char* bytertc::EchoTestConfig::uid;
```
进行音视频通话回路测试的用户 ID


<span id="EchoTestConfig-roomid"></span>
### roomId
```cpp
const char* bytertc::EchoTestConfig::roomId;
```
测试用户加入的房间 ID。  <br>


<span id="EchoTestConfig-token"></span>
### token
```cpp
const char* bytertc::EchoTestConfig::token;
```
对用户进房时进行鉴权验证的动态密钥，用于保证音视频通话回路测试的安全性。



# MusicFilterType
```cpp
enum bytertc::MusicFilterType
```

歌曲过滤方式。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kFilterNone | 0 | 不过滤。 |
| kFilterWithoutLyric | 1 << 0 | 过滤没有歌词的歌曲。 |
| kFilterUnsupportedScore | 1 << 1 | 过滤不支持打分的歌曲。 |
| kFilterUnsupportedAccopmay | 1 << 2 | 过滤不支持伴唱切换的歌曲。 |
| kFilterUnsupportedClimx | 1 << 3 | 过滤没有高潮片段的歌曲。 |


# MusicHotType
```cpp
enum bytertc::MusicHotType
```

热榜类别。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kHotContentCenter | 1 << 0 | 火山内容中心热歌榜。 |
| kHotProject | 1 << 1 | 项目热歌榜。 |


# AudioTrackType
```cpp
enum class bytertc::AudioTrackType
```

原唱伴唱类型。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioTrackTypeOriginal | 1 | 播放原唱。 |
| kAudioTrackTypeAccompy | 2 | 播放伴唱。 |


# AudioPlayType
```cpp
enum class bytertc::AudioPlayType
```

音乐播放类型。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAudioPlayTypeLocal | 0 | 仅本地播放。 |
| kAudioPlayTypeRemote | 1 | 仅远端播放。 |
| kAudioPlayTypeLocalAndRemote | 2 | 本地、远端同时播放。 |


# PlayState
```cpp
enum class bytertc::PlayState
```

音乐播放状态。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kPlayStatePlaying | 1 | 播放中。 |
| kPlayStatePaused | 2 | 暂停中。 |
| kPlayStateStoped | 3 | 已停止。 |
| kPlayStateFailed | 4 | 播放失败。 |
| kPlayStateFinished | 5 | 播放结束。 |


# LyricStatus
```cpp
enum class bytertc::LyricStatus
```

歌词格式类型。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kLyricStatusNone | 0 | 无歌词。 |
| kLyricStatusKRC | 1 | KRC 歌词。 |
| kLyricStatusLRC | 2 | LRC 歌词。 |
| kLyricStatusKRCAndLRC | 3 | KRC 歌词和 LRC 歌词均有。 |


# DownloadLyricType
```cpp
enum class bytertc::DownloadLyricType
```

歌词文件类型。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kDownKrc | 0 | KRC 歌词文件。 |
| kDownLrc | 1 | LRC 歌词文件。 |


# MusicInfo
```cpp
struct bytertc::MusicInfo
```

歌曲数据。


`Defined in : bytertc_ktv_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [music_id](#MusicInfo-music_id) |
| **const char*** | [music_name](#MusicInfo-music_name) |
| **const char*** | [singer](#MusicInfo-singer) |
| **const char*** | [vendor_id](#MusicInfo-vendor_id) |
| **const char*** | [vendor_name](#MusicInfo-vendor_name) |
| **int64_t** | [update_timestamp](#MusicInfo-update_timestamp) |
| **const char*** | [poster_url](#MusicInfo-poster_url) |
| **LyricStatus** | [lyric_status](#MusicInfo-lyric_status) |
| **int** | [duration](#MusicInfo-duration) |
| **bool** | [enable_score](#MusicInfo-enable_score) |
| **int** | [climax_start_time](#MusicInfo-climax_start_time) |
| **int** | [climax_stop_time](#MusicInfo-climax_stop_time) |


## 变量说明
<span id="MusicInfo-music_id"></span>
### music_id
```cpp
const char*  bytertc::MusicInfo::music_id;
```
音乐 ID。


<span id="MusicInfo-music_name"></span>
### music_name
```cpp
const char*  bytertc::MusicInfo::music_name;
```
音乐名称。


<span id="MusicInfo-singer"></span>
### singer
```cpp
const char*  bytertc::MusicInfo::singer;
```
歌手。


<span id="MusicInfo-vendor_id"></span>
### vendor_id
```cpp
const char*  bytertc::MusicInfo::vendor_id;
```
版权商 ID。


<span id="MusicInfo-vendor_name"></span>
### vendor_name
```cpp
const char* bytertc::MusicInfo::vendor_name;
```
版权商名称。


<span id="MusicInfo-update_timestamp"></span>
### update_timestamp
```cpp
int64_t bytertc::MusicInfo::update_timestamp;
```
最新更新时间戳，单位为毫秒。


<span id="MusicInfo-poster_url"></span>
### poster_url
```cpp
const char*  bytertc::MusicInfo::poster_url;
```
封面地址。


<span id="MusicInfo-lyric_status"></span>
### lyric_status
```cpp
LyricStatus bytertc::MusicInfo::lyric_status;
```
歌词格式类型，参看 [LyricStatus](#lyricstatus)。


<span id="MusicInfo-duration"></span>
### duration
```cpp
int bytertc::MusicInfo::duration;
```
歌曲长度，单位为毫秒。


<span id="MusicInfo-enable_score"></span>
### enable_score
```cpp
bool bytertc::MusicInfo::enable_score;
```
歌曲是否支持打分。


<span id="MusicInfo-climax_start_time"></span>
### climax_start_time
```cpp
int bytertc::MusicInfo::climax_start_time;
```
歌曲高潮片段开始时间，单位为毫秒。


<span id="MusicInfo-climax_stop_time"></span>
### climax_stop_time
```cpp
int bytertc::MusicInfo::climax_stop_time;
```
歌曲高潮片段停止时间，单位为毫秒。



# HotMusicInfo
```cpp
struct bytertc::HotMusicInfo
```

热榜歌曲数据。


`Defined in : bytertc_ktv_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **MusicHotType** | [hot_type](#HotMusicInfo-hot_type) |
| **const char*** | [hot_name](#HotMusicInfo-hot_name) |
| **MusicInfo*** | [musics](#HotMusicInfo-musics) |
| **int** | [music_count](#HotMusicInfo-music_count) |


## 变量说明
<span id="HotMusicInfo-hot_type"></span>
### hot_type
```cpp
MusicHotType bytertc::HotMusicInfo::hot_type;
```
热榜类别，参看 [MusicHotType](#musichottype)。多个热榜类别可以按位或组合。


<span id="HotMusicInfo-hot_name"></span>
### hot_name
```cpp
const char* bytertc::HotMusicInfo::hot_name;
```
热榜名称。


<span id="HotMusicInfo-musics"></span>
### musics
```cpp
MusicInfo* bytertc::HotMusicInfo::musics;
```
歌曲数据，参看 [MusicInfo](#musicinfo)。


<span id="HotMusicInfo-music_count"></span>
### music_count
```cpp
int bytertc::HotMusicInfo::music_count;
```
歌曲列表的数量。



# DownloadFileType
```cpp
enum bytertc::DownloadFileType
```

下载文件类型。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kDownloadMusic | 1 | 音频文件。 |
| kDownloadKRC | 2 | KRC 歌词文件。 |
| kDownloadLRC | 3 | LRC 歌词文件。 |
| kDownloadMIDI | 4 | MIDI 文件。 |


# DownloadResult
```cpp
struct bytertc::DownloadResult
```

歌曲下载信息。


`Defined in : bytertc_ktv_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [local_file_path](#DownloadResult-local_file_path) |
| **const char*** | [music_id](#DownloadResult-music_id) |
| **DownloadFileType** | [type](#DownloadResult-type) |


## 变量说明
<span id="DownloadResult-local_file_path"></span>
### local_file_path
```cpp
const char* bytertc::DownloadResult::local_file_path;
```
文件存放路径。


<span id="DownloadResult-music_id"></span>
### music_id
```cpp
const char* bytertc::DownloadResult::music_id;
```
音乐 ID。


<span id="DownloadResult-type"></span>
### type
```cpp
DownloadFileType bytertc::DownloadResult::type;
```
下载文件类型，参看 [DownloadFileType](#downloadfiletype)。



# KTVErrorCode
```cpp
enum bytertc::KTVErrorCode
```

KTV 错误码。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kErrorCodeKTVOK | 0 | 成功。 |
| kErrorCodeKTVAppidInValid | -3000 | AppID 异常。 |
| kErrorCodeKTVParasInValid | -3001 | 非法参数，传入的参数不正确。 |
| kErrorCodeKTVGetMusicFailed | -3002 | 获取歌曲资源失败。 |
| kErrorCodeKTVGetLyricFailed | -3003 | 获取歌词失败。 |
| kErrorCodeKTVMusicTakedown | -3004 | 歌曲下架。 |
| kErrorCodeKTVMusicDownload | -3005 | 歌曲文件下载失败。 |
| kErrorCodeKTVMidiDownloadFailed | -3006 | MIDI 文件下载失败。 |
| kErrorCodeKTVSystemBusy | -3007 | 系统繁忙。 |
| kErrorCodeKTVNetwork | -3008 | 网络异常。 |
| kErrorCodeKTVNotJoinRoom | -3009 | KTV 功能未加入房间。 |
| kErrorCodeKTVParseData | -3010 | 解析数据失败。 |
| kErrorCodeKTVDownload | -3011 | 下载失败。 |
| kErrorCodeKTVDownloading | -3012 | 已在下载中。 |
| kErrorCodeKTVInternalDomain | -3013 | 内部错误，联系技术支持人员。 |


# KTVPlayerErrorCode
```cpp
enum bytertc::KTVPlayerErrorCode
```

KTV 播放器错误码。


`Defined in : bytertc_ktv_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kErrorCodeKTVPlayOK | 0 | 成功。 |
| kErrorCodeKTVPlayFileNotExist | -3020 | 播放错误，请下载后播放。 |
| kErrorCodeKTVPlayFileError | -3021 | 播放错误，请确认文件播放格式。 |
| kErrorCodeKTVPlayNotJoinRoom | -3022 | 播放错误，未进入房间。 |
| kErrorCodeKTVPlayParam | -3023 | 参数错误。 |
| kErrorCodeKTVPlayStartError | -3024 | 播放失败，找不到文件或文件打开失败。 |
| kErrorCodeKTVPlayMixIdError | -3025 | 混音 ID 异常。 |
| kErrorCodeKTVPlayPositionError | -3026 | 设置播放位置出错。 |
| kErrorCodeKTVPlayAudioVolumeError | -3027 | 音量参数不合法，可设置的取值范围为 [0,400]。 |
| kErrorCodeKTVPlayTypeError | -3028 | 不支持此混音类型。 |
| kErrorCodeKTVPlayPitchError | -3029 | 音调文件不合法。 |
| kErrorCodeKTVPlayAudioTrackError | -3030 | 音轨不合法。 |
| kErrorCodeKTVPlayStartingError | -3031 | 混音启动中。 |


# StreamLayoutMode
```cpp
enum bytertc::StreamLayoutMode
```

公共流的布局模式


`Defined in : bytertc_publicstream_interface.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kLayoutAutoMode | 0 | 自动布局 |
| kLayoutCustomerMode | 2 | 自定义 |


# PublicStreamErrorCode
```cpp
enum bytertc::PublicStreamErrorCode
```

公共流错误码。


`Defined in : bytertc_publicstream_interface.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kPublicStreamOK | 200 | 推流成功。 |
| kPushPublicStreamInvalidParam | 1191 | 推流参数错误。 |
| kPushPublicStreamInvalidStatus | 1192 | 推流状态异常。 |
| kPushPublicStreamInternalError | 1193 | 推流内部错误。 |
| kPushPublicStreamPushFailed | 1195 | 推流失败。 |
| kPushPublicStreamTimeout | 1196 | 推流消息发送超时。 |


# SourceCrop
```cpp
typedef struct bytertc::SourceCrop
```

公共流视频裁剪配置


`Defined in : bytertc_publicstream_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [LocationX](#SourceCrop-locationx) |
| **float** | [LocationY](#SourceCrop-locationy) |
| **float** | [WidthProportion](#SourceCrop-widthproportion) |
| **float** | [HeightProportion](#SourceCrop-heightproportion) |


## 变量说明
<span id="SourceCrop-locationx"></span>
### LocationX
```cpp
float bytertc::SourceCrop::LocationX = 0.0;
```
裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)


<span id="SourceCrop-locationy"></span>
### LocationY
```cpp
float bytertc::SourceCrop::LocationY = 0.0;
```
裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)


<span id="SourceCrop-widthproportion"></span>
### WidthProportion
```cpp
float bytertc::SourceCrop::WidthProportion = 0.0;
```
裁剪后得到的视频帧宽度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]


<span id="SourceCrop-heightproportion"></span>
### HeightProportion
```cpp
float bytertc::SourceCrop::HeightProportion = 0.0;
```
裁剪后得到的视频帧高度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]



# PublicStreamVideoParam
```cpp
typedef struct bytertc::PublicStreamVideoParam
```

公共流视频编码参数


`Defined in : bytertc_publicstream_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int32_t** | [width](#PublicStreamVideoParam-width) |
| **int32_t** | [height](#PublicStreamVideoParam-height) |
| **int32_t** | [fps](#PublicStreamVideoParam-fps) |
| **int32_t** | [bitrate_kpbs](#PublicStreamVideoParam-bitrate_kpbs) |


## 变量说明
<span id="PublicStreamVideoParam-width"></span>
### width
```cpp
int32_t bytertc::PublicStreamVideoParam::width;
```
公共流视频宽度，必填。单位为 px，范围为 [2, 1920]，必须是偶数。


<span id="PublicStreamVideoParam-height"></span>
### height
```cpp
int32_t bytertc::PublicStreamVideoParam::height;
```
公共流视频高度，必填。单位为 px，范围为 [16, 1280]，必须是偶数。


<span id="PublicStreamVideoParam-fps"></span>
### fps
```cpp
int32_t bytertc::PublicStreamVideoParam::fps;
```
公共流视频帧率。必填<br>
范围：[1, 60]


<span id="PublicStreamVideoParam-bitrate_kpbs"></span>
### bitrate_kpbs
```cpp
int32_t bytertc::PublicStreamVideoParam::bitrate_kpbs;
```
视频码率，必填<br>
范围：[1,10000000]<br>
单位为 bps



# PublicStreamLayoutRegion
```cpp
typedef struct bytertc::PublicStreamLayoutRegion
```

单个视频流在公共流中的布局信息。  <br>
在多路视频流公共流时，你需要设置每一路视频流在公共流中的布局信息。


`Defined in : bytertc_publicstream_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [user_id](#PublicStreamLayoutRegion-user_id) |
| **const char*** | [room_id](#PublicStreamLayoutRegion-room_id) |
| **const char*** | [alternate_image_uri](#PublicStreamLayoutRegion-alternate_image_uri) |
| **float** | [x](#PublicStreamLayoutRegion-x) |
| **float** | [y](#PublicStreamLayoutRegion-y) |
| **float** | [width](#PublicStreamLayoutRegion-width) |
| **float** | [height](#PublicStreamLayoutRegion-height) |
| **float** | [alpha](#PublicStreamLayoutRegion-alpha) |
| **int32_t** | [z_order](#PublicStreamLayoutRegion-z_order) |
| **int** | [stream_type](#PublicStreamLayoutRegion-stream_type) |
| **TranscoderContentControlType** | [media_type](#PublicStreamLayoutRegion-media_type) |
| **RenderMode** | [render_mode](#PublicStreamLayoutRegion-render_mode) |
| **SourceCrop** | [source_crop](#PublicStreamLayoutRegion-source_crop) |


## 变量说明
<span id="PublicStreamLayoutRegion-user_id"></span>
### user_id
```cpp
const char* bytertc::PublicStreamLayoutRegion::user_id = "";
```
目标公共流用户的 ID。必填。  <br>
服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。


<span id="PublicStreamLayoutRegion-room_id"></span>
### room_id
```cpp
const char* bytertc::PublicStreamLayoutRegion::room_id = "";
```
跨房间订阅流时，目标流所在的房间 ID。 必填。  <br>
服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。


<span id="PublicStreamLayoutRegion-alternate_image_uri"></span>
### alternate_image_uri
```cpp
const char* bytertc::PublicStreamLayoutRegion::alternate_image_uri = "";
```
背景图片地址


<span id="PublicStreamLayoutRegion-x"></span>
### x
```cpp
float bytertc::PublicStreamLayoutRegion::x;
```
用户视频布局相对画布左侧的偏移量，取值的范围为 [0.0, 1.0)。必填。


<span id="PublicStreamLayoutRegion-y"></span>
### y
```cpp
float bytertc::PublicStreamLayoutRegion::y;
```
用户视频布局相对画布顶端的偏移量，取值的范围为 [0.0, 1.0)。必填。


<span id="PublicStreamLayoutRegion-width"></span>
### width
```cpp
float bytertc::PublicStreamLayoutRegion::width;
```
用户视频宽度相对画布宽度的比例，取值的范围为 (0.0, 1.0]。必填。


<span id="PublicStreamLayoutRegion-height"></span>
### height
```cpp
float bytertc::PublicStreamLayoutRegion::height;
```
用户视频高度相对画布高度的比例，取值的范围为 (0.0, 1.0]。必填。


<span id="PublicStreamLayoutRegion-alpha"></span>
### alpha
```cpp
float bytertc::PublicStreamLayoutRegion::alpha;
```
透明度，取值范围 [0，255], 0 为全透明，255 为不透明


<span id="PublicStreamLayoutRegion-z_order"></span>
### z_order
```cpp
int32_t bytertc::PublicStreamLayoutRegion::z_order;
```
用户视频布局在画布中的层级，取值范围 [0，100]，0(默认）为底层，100 为顶层。


<span id="PublicStreamLayoutRegion-stream_type"></span>
### stream_type
```cpp
int bytertc::PublicStreamLayoutRegion::stream_type = 0;
```
必填。媒体流类型：  <br>

+ 0: 普通流（默认设置）  <br>
+ 1: 屏幕流


<span id="PublicStreamLayoutRegion-media_type"></span>
### media_type
```cpp
TranscoderContentControlType bytertc::PublicStreamLayoutRegion::media_type;
```
公共流输出类型，参看 [TranscoderContentControlType](#transcodercontentcontroltype)


<span id="PublicStreamLayoutRegion-render_mode"></span>
### render_mode
```cpp
RenderMode bytertc::PublicStreamLayoutRegion::render_mode;
```
渲染时，视频内容缩放模式，必填。参看 [RenderMode](#rendermode)


<span id="PublicStreamLayoutRegion-source_crop"></span>
### source_crop
```cpp
SourceCrop bytertc::PublicStreamLayoutRegion::source_crop;
```
支持对每一路参与公共流的视频进行裁剪，参看 [SourceCrop](#sourcecrop)



# PublicStreamLayout
```cpp
struct bytertc::PublicStreamLayout
```

公共流布局设置。


`Defined in : bytertc_publicstream_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [layoutMode](#PublicStreamLayout-layoutmode) |
| **int** | [interMode](#PublicStreamLayout-intermode) |
| **const char*** | [background_image](#PublicStreamLayout-background_image) |
| **const char*** | [background_color](#PublicStreamLayout-background_color) |
| **PublicStreamLayoutRegion*** | [regions](#PublicStreamLayout-regions) |
| **int** | [regions_num](#PublicStreamLayout-regions_num) |


## 变量说明
<span id="PublicStreamLayout-layoutmode"></span>
### layoutMode
```cpp
int bytertc::PublicStreamLayout::layoutMode;
```
布局模式。必填。<br>

+ `0`: 自动模式。默认值。 <br>
+ `2`: 自定义模式。


<span id="PublicStreamLayout-intermode"></span>
### interMode
```cpp
int bytertc::PublicStreamLayout::interMode;
```
插帧模式<br>

+ `0`: 补最后一帧<br>
+ `1`: 补背景图片，如果没有设置背景图片则补黑帧


<span id="PublicStreamLayout-background_image"></span>
### background_image
```cpp
const char* bytertc::PublicStreamLayout::background_image = nullptr;
```
背景图片


<span id="PublicStreamLayout-background_color"></span>
### background_color
```cpp
const char* bytertc::PublicStreamLayout::background_color = nullptr;
```
公共流视频的背景颜色，格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色


<span id="PublicStreamLayout-regions"></span>
### regions
```cpp
PublicStreamLayoutRegion* bytertc::PublicStreamLayout::regions = nullptr;
```
各路流的布局信息列表。每一个该类型对象为一路单独的视频流的布局信息。详见 [PublicStreamLayoutRegion](#publicstreamlayoutregion)


<span id="PublicStreamLayout-regions_num"></span>
### regions_num
```cpp
int bytertc::PublicStreamLayout::regions_num = 0;
```
参与合流的数量



# PublicStreamConfig
```cpp
struct bytertc::PublicStreamConfig
```

公共流配置信息


`Defined in : bytertc_publicstream_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [stream_id](#PublicStreamConfig-stream_id) |
| **PublicStreamVideoParam** | [video_config](#PublicStreamConfig-video_config) |
| **PublicStreamAudioParam** | [audio_config](#PublicStreamConfig-audio_config) |
| **PublicStreamLayout** | [layout](#PublicStreamConfig-layout) |


## 变量说明
<span id="PublicStreamConfig-stream_id"></span>
### stream_id
```cpp
const char* bytertc::PublicStreamConfig::stream_id = nullptr;
```
公共流 ID


<span id="PublicStreamConfig-video_config"></span>
### video_config
```cpp
PublicStreamVideoParam bytertc::PublicStreamConfig::video_config;
```
公共流视频编码参数配置，必填。详见 [PublicStreamVideoParam](#publicstreamvideoparam)


<span id="PublicStreamConfig-audio_config"></span>
### audio_config
```cpp
PublicStreamAudioParam bytertc::PublicStreamConfig::audio_config;
```
公共流音频编码参数配置，必填。详见 [PublicStreamAudioParam](#publicstreamaudioparam)


<span id="PublicStreamConfig-layout"></span>
### layout
```cpp
PublicStreamLayout bytertc::PublicStreamConfig::layout;
```
公共流流布局设置，必填。详见 [PublicStreamLayout](#publicstreamlayout)



# IPublicStreamParam
```cpp
class bytertc::IPublicStreamParam
```

公共流参数
本类型继承了 [ITranscoderParamBase](#itranscoderparambase) 中的所有接口。


`Defined in : bytertc_publicstream_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual StreamLayoutMode** | [layoutMode](#IPublicStreamParam-layoutmode) |
| **virtual int** | [interpolationMode](#IPublicStreamParam-interpolationmode) |
| **virtual const char*** | [backgroundImageUri](#IPublicStreamParam-backgroundimageuri) |
| **virtual PublicStreamAudioParam** | [audioParam](#IPublicStreamParam-audioparam) |
| **virtual PublicStreamVideoParam** | [videoParam](#IPublicStreamParam-videoparam) |
| **virtual PublicStreamLayoutRegion** | [layoutRegionByIndex](#IPublicStreamParam-layoutregionbyindex) |
| **virtual void** | [setInterpolationMode](#IPublicStreamParam-setinterpolationmode) |
| **virtual void** | [setBackgroundImageUri](#IPublicStreamParam-setbackgroundimageuri) |
| **virtual void** | [setVideoParam](#IPublicStreamParam-setvideoparam) |
| **virtual void** | [setLayoutParam](#IPublicStreamParam-setlayoutparam) |
| **virtual IPublicStreamParam*** | [inflatten](#IPublicStreamParam-inflatten) |
| **virtual bool** | [checkParameter](#IPublicStreamParam-checkparameter) |


## 函数说明
<span id="IPublicStreamParam-layoutmode"></span>
### layoutMode
```cpp
virtual StreamLayoutMode bytertc::IPublicStreamParam::layoutMode()
```
获取公共流的布局模式，多路媒体流将按照指定的布局模式，合成为一路公共流。目前只支持 `kLayoutCustomerMode` 模式

**返回值**
公共流的布局模式，参看 [StreamLayoutMode](#streamlayoutmode)
`2`：自定义


<span id="IPublicStreamParam-interpolationmode"></span>
### interpolationMode
```cpp
virtual int bytertc::IPublicStreamParam::interpolationMode()
```
获取补帧模式

**返回值**
补帧模式

+ `0`: 补最后一帧
+ `1`: 补背景图片，如果没有设置背景图片则补黑帧


<span id="IPublicStreamParam-backgroundimageuri"></span>
### backgroundImageUri
```cpp
virtual const char* bytertc::IPublicStreamParam::backgroundImageUri()
```
获取背景图片链接

**返回值**
背景图片链接


<span id="IPublicStreamParam-audioparam"></span>
### audioParam
```cpp
virtual PublicStreamAudioParam bytertc::IPublicStreamParam::audioParam()
```
获取公共流音频编码参数

**返回值**
公共流音频编码参数内容，参看 [PublicStreamAudioParam](#publicstreamaudioparam)


<span id="IPublicStreamParam-videoparam"></span>
### videoParam
```cpp
virtual PublicStreamVideoParam bytertc::IPublicStreamParam::videoParam()
```
获取公共流视频编码参数

**返回值**
公共流视频参数内容，参看 [PublicStreamVideoParam](#publicstreamvideoparam)


<span id="IPublicStreamParam-layoutregionbyindex"></span>
### layoutRegionByIndex
```cpp
virtual PublicStreamLayoutRegion bytertc::IPublicStreamParam::layoutRegionByIndex(
    int32_t index)
```
获取公共流视窗布局信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **int32_t** | 视窗对应下标 |

**返回值**
公共流视窗布局信息，参看 [PublicStreamLayoutRegion](#publicstreamlayoutregion)


<span id="IPublicStreamParam-setinterpolationmode"></span>
### setInterpolationMode
```cpp
virtual void bytertc::IPublicStreamParam::setInterpolationMode(
    int mode)
```
设置补帧模式

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mode | **int** | 补帧模式<br/>• `0`: 补最后一帧<br/>• `1`: 补背景图片，如果没有设置背景图片则补黑帧 |


<span id="IPublicStreamParam-setbackgroundimageuri"></span>
### setBackgroundImageUri
```cpp
virtual void bytertc::IPublicStreamParam::setBackgroundImageUri(
    const char* uri)
```
设置背景图片的地址

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uri | **const char*** | 公共流的背景图片的地址 |


<span id="IPublicStreamParam-setvideoparam"></span>
### setVideoParam
```cpp
virtual void bytertc::IPublicStreamParam::setVideoParam(
    const PublicStreamVideoParam&)
```
设置视频编码参数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| PublicStreamVideoParam | **const** | 视频编码参数，参看 [PublicStreamVideoParam](#publicstreamvideoparam) |


<span id="IPublicStreamParam-setlayoutparam"></span>
### setLayoutParam
```cpp
virtual void bytertc::IPublicStreamParam::setLayoutParam(
    PublicStreamLayoutRegion regions[],
    int32_t regions_size,
    const char* bg_color,
    StreamLayoutMode mode)
```
设置公共流布局参数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| regions[] | **PublicStreamLayoutRegion** | 必填。公共流布局参数，参看 [PublicStreamLayoutRegion](#publicstreamlayoutregion) |
| regions_size | **int32_t** | 必填。公共流视窗数量 |
| bg_color | **const char*** | 公共流背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色 |
| mode | **StreamLayoutMode** | 必填。布局参数，参看 [StreamLayoutMode](#streamlayoutmode) |


<span id="IPublicStreamParam-inflatten"></span>
### inflatten
```cpp
virtual IPublicStreamParam* bytertc::IPublicStreamParam::inflatten(
    const char* json_str)
```
将输入的 json 格式的字符串转成 ITranscoderParam 结构体

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| json_str | **const char*** | json 格式字符串 |

**返回值**
转换后的 ITranscoderParam 结构体


<span id="IPublicStreamParam-checkparameter"></span>
### checkParameter
```cpp
virtual bool bytertc::IPublicStreamParam::checkParameter(
    const char* json_str)
```
参数校验

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| json_str | **const char*** | 传入参数，json 格式字符串 |

**返回值**
检查结果
`true`: 所有参数都合法
`false`: 存在不合法参数


# ReceiveRange
```cpp
struct bytertc::ReceiveRange
```

本地用户能收听到、且具有衰减效果的音频接收范围


`Defined in : bytertc_range_audio_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [min](#ReceiveRange-min) |
| **int** | [max](#ReceiveRange-max) |


## 变量说明
<span id="ReceiveRange-min"></span>
### min
```cpp
int bytertc::ReceiveRange::min;
```
能够接收语音、并且具有衰减效果的最小距离值，该值须 ≥ 0，但 ≤ max。  <br>
小于该值的范围内没有范围语音效果，即收听到的音频音量相同。


<span id="ReceiveRange-max"></span>
### max
```cpp
int bytertc::ReceiveRange::max;
```
能够收听语音的最大距离值，该值须 > 0 且 ≥ min。  <br>
当收听者和声源距离处于 [min, max) 之间时，收听到的音量根据距离呈衰减效果。  <br>
超出该值范围的音频将无法收听到。



# RangeAudioInfo
```cpp
struct bytertc::RangeAudioInfo
```

范围语音流信息


`Defined in : bytertc_range_audio_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [user_id](#RangeAudioInfo-user_id) |
| **int** | [factor](#RangeAudioInfo-factor) |


## 变量说明
<span id="RangeAudioInfo-user_id"></span>
### user_id
```cpp
const char* bytertc::RangeAudioInfo::user_id;
```
远端音频发布用户 ID


<span id="RangeAudioInfo-factor"></span>
### factor
```cpp
int bytertc::RangeAudioInfo::factor = 0;
```
本地用户听到该远端音频发布用户的衰减系数，范围 [0,100]，数值为 0 时表示远端用户音频音量为 0。



# AttenuationType
```cpp
enum bytertc::AttenuationType
```

空间音频音量随距离衰减模式


`Defined in : bytertc_range_audio_interface.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAttenuationTypeNone | 0 | 不随距离衰减 |
| kAttenuationTypeLinear | 1 | 线性衰减，音量随距离增大而线性减小 |
| kAttenuationTypeExponential | 2 | 指数型衰减，音量随距离增大进行指数衰减 |


# Orientation
```cpp
struct bytertc::Orientation
```

方向朝向信息


`Defined in : bytertc_spatial_audio_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [x](#Orientation-x) |
| **float** | [y](#Orientation-y) |
| **float** | [z](#Orientation-z) |


## 变量说明
<span id="Orientation-x"></span>
### x
```cpp
float bytertc::Orientation::x;
```
x 坐标


<span id="Orientation-y"></span>
### y
```cpp
float bytertc::Orientation::y;
```
y 坐标


<span id="Orientation-z"></span>
### z
```cpp
float bytertc::Orientation::z;
```
z 坐标



# HumanOrientation
```cpp
struct bytertc::HumanOrientation
```

三维朝向信息，三个向量需要两两垂直。参看 [Orientation](#orientation)。


`Defined in : bytertc_spatial_audio_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **Orientation** | [forward](#HumanOrientation-forward) |
| **Orientation** | [right](#HumanOrientation-right) |
| **Orientation** | [up](#HumanOrientation-up) |


## 变量说明
<span id="HumanOrientation-forward"></span>
### forward
```cpp
Orientation bytertc::HumanOrientation::forward =  { 1, 0, 0 };
```
正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向


<span id="HumanOrientation-right"></span>
### right
```cpp
Orientation bytertc::HumanOrientation::right = { 0, 1, 0 };
```
正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向


<span id="HumanOrientation-up"></span>
### up
```cpp
Orientation bytertc::HumanOrientation::up = { 0, 0, 1 };
```
正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向



# TranscoderContentControlType
```cpp
enum bytertc::TranscoderContentControlType
```

合流输出内容类型


`Defined in : bytertc_transcoder_base_interface.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kHasAudioAndVideo | 0 | 输出的混流包含音频和视频 |
| kHasAudioOnly | 1 | 输出的混流只包含音频 |
| kHasVideoOnly | 2 | 输出的混流只包含视频 |


# ITranscoderParamBase
```cpp
class bytertc::ITranscoderParamBase
```

合流转码参数


`Defined in : bytertc_transcoder_base_interface.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual const char*** | [roomID](#ITranscoderParamBase-roomid) |
| **virtual const char*** | [jsonContent](#ITranscoderParamBase-jsoncontent) |
| **virtual int32_t** | [layoutRegionsSize](#ITranscoderParamBase-layoutregionssize) |
| **virtual const char*** | [backgroundColor](#ITranscoderParamBase-backgroundcolor) |
| **virtual void** | [setRoomID](#ITranscoderParamBase-setroomid) |
| **virtual void** | [setJsonContent](#ITranscoderParamBase-setjsoncontent) |
| **virtual const char*** | [flatten](#ITranscoderParamBase-flatten) |


## 函数说明
<span id="ITranscoderParamBase-roomid"></span>
### roomID
```cpp
virtual const char* bytertc::ITranscoderParamBase::roomID()
```
获取合流房间 ID

**返回值**
合流房间 ID


<span id="ITranscoderParamBase-jsoncontent"></span>
### jsonContent
```cpp
virtual const char* bytertc::ITranscoderParamBase::jsonContent()
```
获取通过 [flatten](#ITranscoderParamBase-flatten) 方法转换得到的 json 格式内容

**返回值**
json 格式数据


<span id="ITranscoderParamBase-layoutregionssize"></span>
### layoutRegionsSize
```cpp
virtual int32_t bytertc::ITranscoderParamBase::layoutRegionsSize()
```
获取合流参数中视窗的数量

**返回值**
合流参数中视窗的数量


<span id="ITranscoderParamBase-backgroundcolor"></span>
### backgroundColor
```cpp
virtual const char* bytertc::ITranscoderParamBase::backgroundColor()
```
获取背景颜色

**返回值**
背景颜色


<span id="ITranscoderParamBase-setroomid"></span>
### setRoomID
```cpp
virtual void bytertc::ITranscoderParamBase::setRoomID(
    const char* room_id)
```
设置合流房间 ID

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| room_id | **const char*** | 发起合流的用户所在的房间 ID |


<span id="ITranscoderParamBase-setjsoncontent"></span>
### setJsonContent
```cpp
virtual void bytertc::ITranscoderParamBase::setJsonContent(
    const char* json_content)
```
设置 jsonContent  <br>
传入通过 [flatten](#ITranscoderParamBase-flatten) 方法转换得到的 json 格式内容

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| json_content | **const char*** | json 格式内容 |


<span id="ITranscoderParamBase-flatten"></span>
### flatten
```cpp
virtual const char* bytertc::ITranscoderParamBase::flatten(
    const char* contentType,
    const char* action)
```
将合流参数转成 json 字符串

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| contentType | **const char*** | 内容属性，表明是合流信令 |
| action | **const char*** | 合流状态，可选取值如下：  <br/>• started: 开启合流  <br/>• layoutChanged: 更新合流布局  <br/>• stopped: 停止合流 |

**返回值**
转换后的 json 字符串


# StreamMixingEvent
```cpp
enum bytertc::StreamMixingEvent
```

转推直播事件


`Defined in : bytertc_transcoder_define.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kStreamMixingStart | 1 | 请求发起转推直播任务 |
| kStreamMixingStartSuccess | 2 | 发起转推直播任务成功 |
| kStreamMixingStartFailed | 3 | 发起转推直播任务失败 |
| kStreamMixingUpdate | 4 | 请求更新转推直播任务配置 |
| kStreamMixingUpdateSuccess | 5 | 成功更新转推直播任务配置 |
| kStreamMixingUpdateFailed | 6 | 更新转推直播任务配置失败 |
| kStreamMixingStop | 7 | 请求结束转推直播任务 |
| kStreamMixingStopSuccess | 8 | 结束转推直播任务成功 |
| kStreamMixingStopFailed | 9 | 结束转推直播任务失败 |
| kStreamMixingChangeMixType | 10 | 更新转推直播任务配置的请求超时 |
| kStreamMixingFirstAudioFrameByClientMix | 11 | 得到客户端合流音频首帧 |
| kStreamMixingFirstVideoFrameByClientMix | 12 | 收到客户端合流视频首帧 |
| kStreamMixingUpdateTimeout | 13 | 更新转推直播任务配置超时 |
| kStreamMixingStartTimeout | 14 | 发起转推直播任务配置超时 |
| kStreamMixingRequestParamError | 15 | 合流布局参数错误 |
| kStreamMixingMixImageEvent | 16 | 合流加图片 |


# StreamMixingType
```cpp
enum bytertc::StreamMixingType
```

合流类型


`Defined in : bytertc_transcoder_define.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kStreamMixingTypeByServer | 0 | 服务端合流 |
| kStreamMixingTypeByClient | 1 | 端云一体合流 |


# TranscoderAudioCodecProfile
```cpp
enum bytertc::TranscoderAudioCodecProfile
```

AAC 编码等级


`Defined in : bytertc_transcoder_define.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kByteAACProfileLC | 0 | 编码等级 AAC-LC |
| kByteAACProfileHEv1 | 1 | 编码等级 HE-AAC v1 |
| kByteAACProfileHEv2 | 2 | 编码等级 HE-AAC v2 |


# TranscoderVideoCodecProfile
```cpp
enum bytertc::TranscoderVideoCodecProfile
```

视频编码规格


`Defined in : bytertc_transcoder_define.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kByteH264ProfileBaseline | 0 | H264 格式基本规格编码 |
| kByteH264ProfileMain | 1 | H264 格式主流规格编码 |
| kByteH264ProfileHigh | 2 | H264 格式高规格编码 |
| kByteVC1ProfileBaseline | 3 | ByteVC1 格式基本规格编码 |
| kByteVC1ProfileMain | 4 | ByteVC1 格式主流规格编码 |
| kByteVC1ProfileHigh | 5 | ByteVC1 格式高规格编码 |


# TranscoderRenderMode
```cpp
enum bytertc::TranscoderRenderMode
```

视频渲染的缩放模式


`Defined in : bytertc_transcoder_define.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRenderHidden | 1 | 视窗填满优先，默认值。  <br><br/>视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。 |
| kRenderFit | 2 | 视频帧内容全部显示优先。  <br><br/>视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。 |
| kRenderAdaptive | 3 | 视频帧自适应画布。 <br><br/>视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。 |


# TranscoderLayoutRegionType
```cpp
enum bytertc::TranscoderLayoutRegionType
```

合流布局区域类型


`Defined in : bytertc_transcoder_define.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kLayoutRegionTypeVideoStream | 0 | 合流布局区域类型为视频。 |
| kLayoutRegionTypeImage | 1 | 合流布局区域类型为图片。 |


# TranscoderLayoutRegionDataParam
```cpp
typedef struct bytertc::TranscoderLayoutRegionDataParam
```

图片合流相关参数


`Defined in : bytertc_transcoder_define.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [image_width](#TranscoderLayoutRegionDataParam-image_width) |
| **int** | [image_height](#TranscoderLayoutRegionDataParam-image_height) |


## 变量说明
<span id="TranscoderLayoutRegionDataParam-image_width"></span>
### image_width
```cpp
int bytertc::TranscoderLayoutRegionDataParam::image_width;
```
原始图片的宽度，单位为 px。


<span id="TranscoderLayoutRegionDataParam-image_height"></span>
### image_height
```cpp
int bytertc::TranscoderLayoutRegionDataParam::image_height;
```
原始图片的高度，单位为 px。



# DataFrameType
```cpp
enum bytertc::DataFrameType
```

数据帧类型


`Defined in : bytertc_transcoder_define.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kDataFrameTypeSei | 0 | SEI 视频帧 |


# IDataFrame
```cpp
typedef struct bytertc::IDataFrame
```

数据帧


`Defined in : bytertc_transcoder_define.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **DataFrameType** | [frame_type](#IDataFrame-frame_type) |
| **uint8_t*** | [u8_data](#IDataFrame-u8_data) |
| **uint32_t** | [u32_data_size](#IDataFrame-u32_data_size) |
| **uint64_t** | [u64_ts_us](#IDataFrame-u64_ts_us) |


## 变量说明
<span id="IDataFrame-frame_type"></span>
### frame_type
```cpp
DataFrameType bytertc::IDataFrame::frame_type;
```
数据帧类型，参看 [DataFrameType](#dataframetype)


<span id="IDataFrame-u8_data"></span>
### u8_data
```cpp
uint8_t* bytertc::IDataFrame::u8_data;
```
数据帧数据


<span id="IDataFrame-u32_data_size"></span>
### u32_data_size
```cpp
uint32_t bytertc::IDataFrame::u32_data_size;
```
数据帧数据大小


<span id="IDataFrame-u64_ts_us"></span>
### u64_ts_us
```cpp
uint64_t bytertc::IDataFrame::u64_ts_us;
```
数据帧时间戳，单位：微秒



# TranscoderLayoutRegion
```cpp
typedef struct bytertc::TranscoderLayoutRegion
```

单个图片或视频流在合流中的布局信息。  <br>
开启转推直播功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。


`Defined in : bytertc_transcoder_define.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [region_id](#TranscoderLayoutRegion-region_id) |
| **const char*** | [room_id](#TranscoderLayoutRegion-room_id) |
| **float** | [x](#TranscoderLayoutRegion-x) |
| **float** | [y](#TranscoderLayoutRegion-y) |
| **float** | [width](#TranscoderLayoutRegion-width) |
| **float** | [height](#TranscoderLayoutRegion-height) |
| **float** | [alpha](#TranscoderLayoutRegion-alpha) |
| **int32_t** | [i32_z_order](#TranscoderLayoutRegion-i32_z_order) |
| **bool** | [local_user](#TranscoderLayoutRegion-local_user) |
| **bool** | [screen_stream](#TranscoderLayoutRegion-screen_stream) |
| **TranscoderContentControlType** | [content_control](#TranscoderLayoutRegion-content_control) |
| **TranscoderRenderMode** | [render_mode](#TranscoderLayoutRegion-render_mode) |
| **TranscoderLayoutRegionType** | [type](#TranscoderLayoutRegion-type) |
| **uint8_t*** | [data](#TranscoderLayoutRegion-data) |
| **TranscoderLayoutRegionDataParam** | [data_param](#TranscoderLayoutRegion-data_param) |


## 变量说明
<span id="TranscoderLayoutRegion-region_id"></span>
### region_id
```cpp
const char* bytertc::TranscoderLayoutRegion::region_id;
```
合流用户的 ID。必填。


<span id="TranscoderLayoutRegion-room_id"></span>
### room_id
```cpp
const char* bytertc::TranscoderLayoutRegion::room_id;
```
图片或视频流所在房间的房间 ID。必填。<br>
如果此图片或视频流是通过 [startForwardStreamToRooms](Windows-api.md#IRTCRoom-startforwardstreamtorooms) 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。


<span id="TranscoderLayoutRegion-x"></span>
### x
```cpp
float bytertc::TranscoderLayoutRegion::x;
```
用户视频布局相对画布左侧的偏移量，取值的范围为 [0.0, 1.0)


<span id="TranscoderLayoutRegion-y"></span>
### y
```cpp
float bytertc::TranscoderLayoutRegion::y;
```
用户视频布局相对画布顶端的偏移量，取值的范围为 [0.0, 1.0)


<span id="TranscoderLayoutRegion-width"></span>
### width
```cpp
float bytertc::TranscoderLayoutRegion::width;
```
用户视频宽度相对画布宽度的比例，取值的范围为 (0.0, 1.0]


<span id="TranscoderLayoutRegion-height"></span>
### height
```cpp
float bytertc::TranscoderLayoutRegion::height;
```
用户视频高度相对画布高度的比例，取值的范围为 (0.0, 1.0]


<span id="TranscoderLayoutRegion-alpha"></span>
### alpha
```cpp
float bytertc::TranscoderLayoutRegion::alpha;
```
透明度，取值范围 [0，255]


<span id="TranscoderLayoutRegion-i32_z_order"></span>
### i32_z_order
```cpp
int32_t bytertc::TranscoderLayoutRegion::i32_z_order;
```
用户视频布局在画布中的层级，取值范围 [0，100]，0 为底层，值越大层级越高


<span id="TranscoderLayoutRegion-local_user"></span>
### local_user
```cpp
bool bytertc::TranscoderLayoutRegion::local_user;
```
是否为本地用户：  <br>

+ true: 是  <br>
+ false: 否


<span id="TranscoderLayoutRegion-screen_stream"></span>
### screen_stream
```cpp
bool bytertc::TranscoderLayoutRegion::screen_stream = false;
```
是否为屏幕流：  <br>

+ true: 是  <br>
+ false: 否


<span id="TranscoderLayoutRegion-content_control"></span>
### content_control
```cpp
TranscoderContentControlType bytertc::TranscoderLayoutRegion::content_control;
```
合流内容控制。默认值为 `kHasAudioAndVideo`，参看 [TranscoderContentControlType](#transcodercontentcontroltype)。


<span id="TranscoderLayoutRegion-render_mode"></span>
### render_mode
```cpp
TranscoderRenderMode bytertc::TranscoderLayoutRegion::render_mode;
```
渲染时，视频内容缩放模式，参看 [TranscoderRenderMode](#transcoderrendermode)


<span id="TranscoderLayoutRegion-type"></span>
### type
```cpp
TranscoderLayoutRegionType bytertc::TranscoderLayoutRegion::type;
```
合流布局区域类型，参看 [TranscoderLayoutRegionType](#transcoderlayoutregiontype)。


<span id="TranscoderLayoutRegion-data"></span>
### data
```cpp
uint8_t* bytertc::TranscoderLayoutRegion::data;
```
图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。


<span id="TranscoderLayoutRegion-data_param"></span>
### data_param
```cpp
TranscoderLayoutRegionDataParam bytertc::TranscoderLayoutRegion::data_param;
```
合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 [TranscoderLayoutRegionDataParam](#transcoderlayoutregiondataparam)。



# TranscoderAudioParam
```cpp
typedef struct bytertc::TranscoderAudioParam
```

音频转码配置参数。


`Defined in : bytertc_transcoder_define.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int32_t** | [i32_sample_rate](#TranscoderAudioParam-i32_sample_rate) |
| **int32_t** | [i32_channel_num](#TranscoderAudioParam-i32_channel_num) |
| **int32_t** | [i32_bitrate_kbps](#TranscoderAudioParam-i32_bitrate_kbps) |
| **TranscoderAudioCodecProfile** | [audio_codec_profile](#TranscoderAudioParam-audio_codec_profile) |


## 变量说明
<span id="TranscoderAudioParam-i32_sample_rate"></span>
### i32_sample_rate
```cpp
int32_t bytertc::TranscoderAudioParam::i32_sample_rate;
```
音频采样率，单位 Hz。可取 32000Hz、44100Hz、48000Hz，默认值为 48000Hz。


<span id="TranscoderAudioParam-i32_channel_num"></span>
### i32_channel_num
```cpp
int32_t bytertc::TranscoderAudioParam::i32_channel_num;
```
音频声道数。可取 1、2，默认值为 2。


<span id="TranscoderAudioParam-i32_bitrate_kbps"></span>
### i32_bitrate_kbps
```cpp
int32_t bytertc::TranscoderAudioParam::i32_bitrate_kbps;
```
音频码率，单位 Kbps。可取范围 [32Kbps, 192Kbps]，默认值为 64Kbps。


<span id="TranscoderAudioParam-audio_codec_profile"></span>
### audio_codec_profile
```cpp
TranscoderAudioCodecProfile bytertc::TranscoderAudioParam::audio_codec_profile;
```
AAC 等级，参看 [TranscoderAudioCodecProfile](#transcoderaudiocodecprofile)。默认值为 `0`。



# TranscoderVideoParam
```cpp
typedef struct bytertc::TranscoderVideoParam
```

合流视频转码参数


`Defined in : bytertc_transcoder_define.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int32_t** | [i32_width](#TranscoderVideoParam-i32_width) |
| **int32_t** | [i32_height](#TranscoderVideoParam-i32_height) |
| **int32_t** | [i32_fps](#TranscoderVideoParam-i32_fps) |
| **int32_t** | [i32_gop](#TranscoderVideoParam-i32_gop) |
| **int32_t** | [i32_bitrate_kbps](#TranscoderVideoParam-i32_bitrate_kbps) |
| **TranscoderVideoCodecProfile** | [video_codec_profile](#TranscoderVideoParam-video_codec_profile) |
| **bool** | [lowLatency](#TranscoderVideoParam-lowlatency) |


## 变量说明
<span id="TranscoderVideoParam-i32_width"></span>
### i32_width
```cpp
int32_t bytertc::TranscoderVideoParam::i32_width;
```
合流视频宽度。不超过 1920，单位：px。  <br>
仅支持设为偶数，如果设为奇数，云端媒体处理会直接拒绝，导致合流失败。


<span id="TranscoderVideoParam-i32_height"></span>
### i32_height
```cpp
int32_t bytertc::TranscoderVideoParam::i32_height;
```
合流视频高度。不超过 1920，单位：px。  <br>
仅支持设为偶数，如果设为奇数，云端媒体处理会直接拒绝，导致合流失败。


<span id="TranscoderVideoParam-i32_fps"></span>
### i32_fps
```cpp
int32_t bytertc::TranscoderVideoParam::i32_fps;
```
合流的视频帧率。默认值为 `15`，取值范围是 `[1, 60]`。值不合法时，自动调整为默认值。


<span id="TranscoderVideoParam-i32_gop"></span>
### i32_gop
```cpp
int32_t bytertc::TranscoderVideoParam::i32_gop;
```
I 帧间隔。默认值为 `4`，取值范围为 `[1, 5]`，单位为秒。值不合法时，自动调整为默认值。


<span id="TranscoderVideoParam-i32_bitrate_kbps"></span>
### i32_bitrate_kbps
```cpp
int32_t bytertc::TranscoderVideoParam::i32_bitrate_kbps;
```
合流视频码率。单位为 kbps，取值范围为 `[1,10000]`，默认值为自适应。值不合法时，自动调整为默认值。


<span id="TranscoderVideoParam-video_codec_profile"></span>
### video_codec_profile
```cpp
TranscoderVideoCodecProfile bytertc::TranscoderVideoParam::video_codec_profile;
```
视频编码规格，参看 [TranscoderVideoCodecProfile](#transcodervideocodecprofile)
本参数不支持过程中更新。

<span id="TranscoderVideoParam-lowlatency"></span>
### lowLatency
```cpp
bool bytertc::TranscoderVideoParam::lowLatency;
```
是否使用低延时特性：  <br>

+ true: 是  <br>
+ false: 否



# ITranscoderParam
```cpp
class bytertc::ITranscoderParam
```

转推直播配置参数


`Defined in : bytertc_transcoder_define.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual StreamMixingType** | [expectedMixingType](#ITranscoderParam-expectedmixingtype) |
| **virtual const char*** | [userID](#ITranscoderParam-userid) |
| **virtual const char*** | [uri](#ITranscoderParam-uri) |
| **virtual const char*** | [appData](#ITranscoderParam-appdata) |
| **virtual TranscoderAudioParam** | [audioParam](#ITranscoderParam-audioparam) |
| **virtual TranscoderVideoParam** | [videoParam](#ITranscoderParam-videoparam) |
| **virtual TranscoderLayoutRegion** | [layoutRegionByIndex](#ITranscoderParam-layoutregionbyindex) |
| **virtual void** | [setExpectedMixingType](#ITranscoderParam-setexpectedmixingtype) |
| **virtual void** | [setUserID](#ITranscoderParam-setuserid) |
| **virtual void** | [setUri](#ITranscoderParam-seturi) |
| **virtual void** | [setAudioParam](#ITranscoderParam-setaudioparam) |
| **virtual void** | [setVideoParam](#ITranscoderParam-setvideoparam) |
| **virtual void** | [setLayoutParam](#ITranscoderParam-setlayoutparam) |
| **virtual ITranscoderParam*** | [inflatten](#ITranscoderParam-inflatten) |
| **virtual ITranscoderParam*** | [defaultTranscoding](#ITranscoderParam-defaulttranscoding) |


## 函数说明
<span id="ITranscoderParam-expectedmixingtype"></span>
### expectedMixingType
```cpp
virtual StreamMixingType bytertc::ITranscoderParam::expectedMixingType()
```
获取合流类型

**返回值**
合流类型，参看 [StreamMixingType](#streammixingtype)


<span id="ITranscoderParam-userid"></span>
### userID
```cpp
virtual const char* bytertc::ITranscoderParam::userID()
```
获取合流用户 ID

**返回值**
合流用户 ID


<span id="ITranscoderParam-uri"></span>
### uri
```cpp
virtual const char* bytertc::ITranscoderParam::uri()
```
获取推流地址

**返回值**
推流地址


<span id="ITranscoderParam-appdata"></span>
### appData
```cpp
virtual const char* bytertc::ITranscoderParam::appData()
```
获取 SEI 信息

**返回值**
SEI 信息


<span id="ITranscoderParam-audioparam"></span>
### audioParam
```cpp
virtual TranscoderAudioParam bytertc::ITranscoderParam::audioParam()
```
获取合流音频参数

**返回值**
合流音频参数内容，参看 [TranscoderAudioParam](#transcoderaudioparam)


<span id="ITranscoderParam-videoparam"></span>
### videoParam
```cpp
virtual TranscoderVideoParam bytertc::ITranscoderParam::videoParam()
```
获取合流视频转码参数

**返回值**
合流视频转码参数内容，参看 [TranscoderVideoParam](#transcodervideoparam)


<span id="ITranscoderParam-layoutregionbyindex"></span>
### layoutRegionByIndex
```cpp
virtual TranscoderLayoutRegion bytertc::ITranscoderParam::layoutRegionByIndex(
    int32_t index)
```
获取合流视窗布局信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| index | **int32_t** | 视窗对应下标 |

**返回值**
合流视窗布局信息，参看 [TranscoderLayoutRegion](#transcoderlayoutregion)


<span id="ITranscoderParam-setexpectedmixingtype"></span>
### setExpectedMixingType
```cpp
virtual void bytertc::ITranscoderParam::setExpectedMixingType(
    StreamMixingType expected_mix_type)
```
设置合流类型。本参数不支持过程中更新。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| expected_mix_type | **StreamMixingType** | 合流类型，参看 [StreamMixingType](#streammixingtype) |


<span id="ITranscoderParam-setuserid"></span>
### setUserID
```cpp
virtual void bytertc::ITranscoderParam::setUserID(
    const char* user_id)
```
设置合流用户 ID。本参数不支持过程中更新。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| user_id | **const char*** | 发起合流的用户的 ID |


<span id="ITranscoderParam-seturi"></span>
### setUri
```cpp
virtual void bytertc::ITranscoderParam::setUri(
    const char* uri)
```
设置推流地址。本参数不支持过程中更新。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uri | **const char*** | 推流地址 |


<span id="ITranscoderParam-setaudioparam"></span>
### setAudioParam
```cpp
virtual void bytertc::ITranscoderParam::setAudioParam(
    const TranscoderAudioParam&)
```
设置音频参数。本参数不支持过程中更新。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| TranscoderAudioParam | **const** | 音频参数，参看 [TranscoderAudioParam](#transcoderaudioparam) |


<span id="ITranscoderParam-setvideoparam"></span>
### setVideoParam
```cpp
virtual void bytertc::ITranscoderParam::setVideoParam(
    const TranscoderVideoParam&)
```
设置视频参数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| TranscoderVideoParam | **const** | 视频参数，参看 [TranscoderVideoParam](#transcodervideoparam) |


<span id="ITranscoderParam-setlayoutparam"></span>
### setLayoutParam
```cpp
virtual void bytertc::ITranscoderParam::setLayoutParam(
    TranscoderLayoutRegion regions[],
    int32_t regions_size,
    const char* bg_color,
    const char* app_data)
```
设置合流布局参数

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| regions[] | **TranscoderLayoutRegion** | 合流布局参数，参看 [TranscoderLayoutRegion](#transcoderlayoutregion) |
| regions_size | **int32_t** | 合流视窗数量 |
| bg_color | **const char*** | 合流背景颜色 |
| app_data | **const char*** | 用户额外需要传入的数据 |


<span id="ITranscoderParam-inflatten"></span>
### inflatten
```cpp
virtual ITranscoderParam* bytertc::ITranscoderParam::inflatten(
    const char* json_str)
```
将输入的 json 格式的字符串转成 ITranscoderParam 结构体

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| json_str | **const char*** | json 格式字符串 |

**返回值**
转换后的 ITranscoderParam 结构体


<span id="ITranscoderParam-defaulttranscoding"></span>
### defaultTranscoding
```cpp
virtual ITranscoderParam* bytertc::ITranscoderParam::defaultTranscoding()
```
获取默认的合流转推参数

**返回值**
生成的 ITranscoderParam 结构体


# PushSingleStreamParam
```cpp
typedef struct bytertc::PushSingleStreamParam
```

单流转推直播配置参数。


`Defined in : bytertc_transcoder_define.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [room_id](#PushSingleStreamParam-room_id) |
| **const char*** | [user_id](#PushSingleStreamParam-user_id) |
| **const char*** | [uri](#PushSingleStreamParam-uri) |
| **const bool** | [is_screen_stream](#PushSingleStreamParam-is_screen_stream) |


## 变量说明
<span id="PushSingleStreamParam-room_id"></span>
### room_id
```cpp
const char* bytertc::PushSingleStreamParam::room_id;
```
媒体流所在的房间 ID


<span id="PushSingleStreamParam-user_id"></span>
### user_id
```cpp
const char* bytertc::PushSingleStreamParam::user_id;
```
媒体流所属的用户 ID


<span id="PushSingleStreamParam-uri"></span>
### uri
```cpp
const char* bytertc::PushSingleStreamParam::uri;
```
推流地址


<span id="PushSingleStreamParam-is_screen_stream"></span>
### is_screen_stream
```cpp
const bool bytertc::PushSingleStreamParam::is_screen_stream;
```
媒体流是否为屏幕流。



# RenderMode
```cpp
enum bytertc::RenderMode
```

渲染模式


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRenderModeHidden | 1 | 视窗填满优先，默认值。<br><br/>视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br><br/>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。 |
| kRenderModeFit | 2 | 视频帧内容全部显示优先。<br><br/>视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br><br/>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。 |
| kRenderModeFill | 3 | 视频帧自适应画布 <br><br/>视频帧非等比缩放，直至画布被填满。在此过程中，视频帧的长宽比例可能会发生变化。 |


# SubscribeMediaType
```cpp
enum bytertc::SubscribeMediaType
```

订阅媒体的类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRTCSubscribeMediaTypeNone | 0 | 既不订阅音频，也不订阅视频 |
| kRTCSubscribeMediaTypeAudioOnly | 1 | 只订阅音频，不订阅视频 |
| kRTCSubscribeMediaTypeVideoOnly | 2 | 只订阅视频，不订阅音频 |
| kRTCSubscribeMediaTypeVideoAndAudio | 3 | 同时订阅音频和视频 |


# PauseResumeControlMediaType
```cpp
enum bytertc::PauseResumeControlMediaType
```

暂停/恢复接收远端的媒体流类型。


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRTCPauseResumeControlMediaTypeAudio | 0 | 只控制音频，不影响视频 |
| kRTCPauseResumeControlMediaTypeVideo | 1 | 只控制视频，不影响音频 |
| kRTCPauseResumeControlMediaTypeVideoAndAudio | 2 | 同时控制音频和视频 |


# SVCLayer
```cpp
enum bytertc::SVCLayer
```

时域分层定义


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kSVCLayerDefault | 0 | 不指定分层(默认值） |
| kSVCLayerBase | 1 | T0层 |
| kSVCLayerMain | 2 | T0+T1层 |
| kSVCLayerHigh | 3 | T0+T1+T2层 |


# RemoteStreamSwitch
```cpp
struct bytertc::RemoteStreamSwitch
```

流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [uid](#RemoteStreamSwitch-uid) |
| **bool** | [is_screen](#RemoteStreamSwitch-is_screen) |
| **int** | [before_video_index](#RemoteStreamSwitch-before_video_index) |
| **int** | [after_video_index](#RemoteStreamSwitch-after_video_index) |
| **bool** | [before_enable](#RemoteStreamSwitch-before_enable) |
| **bool** | [after_enable](#RemoteStreamSwitch-after_enable) |
| **FallbackOrRecoverReason** | [reason](#RemoteStreamSwitch-reason) |


## 变量说明
<span id="RemoteStreamSwitch-uid"></span>
### uid
```cpp
const char* bytertc::RemoteStreamSwitch::uid;
```
订阅的音视频流的发布者的用户 ID。


<span id="RemoteStreamSwitch-is_screen"></span>
### is_screen
```cpp
bool bytertc::RemoteStreamSwitch::is_screen;
```
是否是屏幕流。


<span id="RemoteStreamSwitch-before_video_index"></span>
### before_video_index
```cpp
int bytertc::RemoteStreamSwitch::before_video_index;
```
流切换前本地用户订阅的视频流的分辨率对应的索引。


<span id="RemoteStreamSwitch-after_video_index"></span>
### after_video_index
```cpp
int bytertc::RemoteStreamSwitch::after_video_index;
```
流切换后本地用户订阅的视频流的分辨率对应的索引。


<span id="RemoteStreamSwitch-before_enable"></span>
### before_enable
```cpp
bool bytertc::RemoteStreamSwitch::before_enable;
```
流切换前是否有视频流。


<span id="RemoteStreamSwitch-after_enable"></span>
### after_enable
```cpp
bool bytertc::RemoteStreamSwitch::after_enable;
```
流切换后是否有视频流。


<span id="RemoteStreamSwitch-reason"></span>
### reason
```cpp
FallbackOrRecoverReason bytertc::RemoteStreamSwitch::reason;
```
触发流回退的原因，详见类型 [FallbackOrRecoverReason](#fallbackorrecoverreason) 。



# TransCodingError
```cpp
enum bytertc::TransCodingError
```

直播推流转码功能错误码。


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kTransCodingErrorOK | 0 | 推流成功。 |
| kTransCodingErrorInvalidArgument | 1 | 推流参数错误。 |
| kTransCodingErrorSubscribe | 2 | 和 RTC 服务端建立连接失败。会自动重连 |
| kTransCodingErrorProcessing | 3 | 合流服务中间过程存在错误，建议重试。 |
| kTransCodingErrorPublish | 4 | 推流失败，可以等待服务端重新推流。 |


# SubscribeVideoConfig
```cpp
struct bytertc::SubscribeVideoConfig
```

视频订阅配置信息


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [video_index](#SubscribeVideoConfig-video_index) |
| **int** | [priority](#SubscribeVideoConfig-priority) |


## 变量说明
<span id="SubscribeVideoConfig-video_index"></span>
### video_index
```cpp
int bytertc::SubscribeVideoConfig::video_index = 0;
```
订阅的视频流分辨率下标。  <br>
当远端用户通过调用 [setVideoEncoderConfig](Windows-api.md#IRTCVideo-setvideoencoderconfig) 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
默认值为 0，即订阅第一路流。  <br>
如果不想更改之前的设置，可以输入 -1。  <br>


<span id="SubscribeVideoConfig-priority"></span>
### priority
```cpp
int bytertc::SubscribeVideoConfig::priority = 0;
```
远端用户优先级，参看 [RemoteUserPriority](#remoteuserpriority)，默认值为 0。



# SubscribeConfig
```cpp
struct bytertc::SubscribeConfig
```

手动订阅流的配置信息。


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **bool** | [is_screen](#SubscribeConfig-is_screen) |
| **bool** | [sub_video](#SubscribeConfig-sub_video) |
| **bool** | [sub_audio](#SubscribeConfig-sub_audio) |
| **int** | [video_index](#SubscribeConfig-video_index) |
| **int** | [priority](#SubscribeConfig-priority) |
| **int** | [svc_layer](#SubscribeConfig-svc_layer) |
| **int** | [framerate](#SubscribeConfig-framerate) |
| **int** | [sub_width](#SubscribeConfig-sub_width) |
| **int** | [sub_height](#SubscribeConfig-sub_height) |


## 变量说明
<span id="SubscribeConfig-is_screen"></span>
### is_screen
```cpp
bool bytertc::SubscribeConfig::is_screen = false;
```
是否是屏幕流（默认为否）。  <br>


<span id="SubscribeConfig-sub_video"></span>
### sub_video
```cpp
bool bytertc::SubscribeConfig::sub_video;
```
是否订阅视频。  <br>


<span id="SubscribeConfig-sub_audio"></span>
### sub_audio
```cpp
bool bytertc::SubscribeConfig::sub_audio;
```
是否订阅音频。  <br>


<span id="SubscribeConfig-video_index"></span>
### video_index
```cpp
int bytertc::SubscribeConfig::video_index;
```
订阅的视频流分辨率下标。  <br>
用户可以通过调用 [setVideoEncoderConfig](Windows-api.md#IRTCVideo-setvideoencoderconfig) 方法在一路流中发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>


<span id="SubscribeConfig-priority"></span>
### priority
```cpp
int bytertc::SubscribeConfig::priority = 0;
```
远端用户的需求优先级，参看 [RemoteUserPriority](#remoteuserpriority)，默认值为 0 。  <br>
当开启了订阅流回退选项功能（详见 [setSubscribeFallbackOption](Windows-api.md#IRTCVideo-setsubscribefallbackoption) 方法），弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>


<span id="SubscribeConfig-svc_layer"></span>
### svc_layer
```cpp
int bytertc::SubscribeConfig::svc_layer = 0;
```
远端用户的时域分层，参看 [SVCLayer](#svclayer)，默认值为 0 。  <br>
仅码流支持SVC特性时可以生效。  <br>


<span id="SubscribeConfig-framerate"></span>
### framerate
```cpp
int bytertc::SubscribeConfig::framerate = 0;
```
期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。  <br>
当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
仅码流支持 SVC 分级编码特性时方可生效。


<span id="SubscribeConfig-sub_width"></span>
### sub_width
```cpp
int bytertc::SubscribeConfig::sub_width = 0;
```
用户通过指定UI对应的最合适的流的宽度，单位：px


<span id="SubscribeConfig-sub_height"></span>
### sub_height
```cpp
int bytertc::SubscribeConfig::sub_height = 0;
```
用户通过指定UI对应的最合适的流的高度，单位：px



# VideoStreamType
```cpp
enum bytertc::VideoStreamType
```

远端视频类型
目前C++ sdk 只支持 kVideoStreamTypeHigh 类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoStreamTypeHigh | 0 | 高分辨率视频流 |
| kVideoStreamTypeLow | 1 | 低分辨率视频 |


# VideoCanvas
```cpp
struct bytertc::VideoCanvas
```

视频帧渲染设置。<br>
调用 [setLocalVideoCanvas](Windows-api.md#IRTCVideo-setlocalvideocanvas) 将视频流绑定到本地视图。


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **void*** | [view](#VideoCanvas-view) |
| **int** | [render_mode](#VideoCanvas-render_mode) |
| **uint32_t** | [background_color](#VideoCanvas-background_color) |


## 变量说明
<span id="VideoCanvas-view"></span>
### view
```cpp
void* bytertc::VideoCanvas::view;
```
本地视图句柄


<span id="VideoCanvas-render_mode"></span>
### render_mode
```cpp
int bytertc::VideoCanvas::render_mode;
```
视频渲染模式，参看 [RenderMode](#rendermode)


<span id="VideoCanvas-background_color"></span>
### background_color
```cpp
uint32_t bytertc::VideoCanvas::background_color;
```
用于填充画布空白部分的背景颜色。取值范围是 `[0x00000000, 0xFFFFFFFF]`。默认值是 `0x00000000`。其中，透明度设置无效。



# view_t
```cpp
typedef void* bytertc::view_t
```

Windows 窗口 id, Windows 平台下传 Windows 窗口句柄


`Defined in : bytertc_video_defines.h`

# Rectangle
```cpp
struct bytertc::Rectangle
```

矩形区域，用于指定屏幕区域。


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [x](#Rectangle-x) |
| **int** | [y](#Rectangle-y) |
| **int** | [width](#Rectangle-width) |
| **int** | [height](#Rectangle-height) |


## 变量说明
<span id="Rectangle-x"></span>
### x
```cpp
int bytertc::Rectangle::x = 0;
```
矩形区域左上角的 x 坐标。


<span id="Rectangle-y"></span>
### y
```cpp
int bytertc::Rectangle::y = 0;
```
矩形区域左上角的 y 坐标。


<span id="Rectangle-width"></span>
### width
```cpp
int bytertc::Rectangle::width = 0;
```
矩形宽度。


<span id="Rectangle-height"></span>
### height
```cpp
int bytertc::Rectangle::height = 0;
```
矩形高度。



# HighlightConfig
```cpp
struct bytertc::HighlightConfig
```

屏幕共享时的边框高亮设置。


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **bool** | [enable_highlight](#HighlightConfig-enable_highlight) |
| **uint32_t** | [border_color](#HighlightConfig-border_color) |
| **int** | [border_width](#HighlightConfig-border_width) |


## 变量说明
<span id="HighlightConfig-enable_highlight"></span>
### enable_highlight
```cpp
bool bytertc::HighlightConfig::enable_highlight = true;
```
是否显示高亮边框，默认显示。


<span id="HighlightConfig-border_color"></span>
### border_color
```cpp
uint32_t bytertc::HighlightConfig::border_color = 0xFF29CCA3;
```
边框的颜色, 颜色格式为十六进制 ARGB:  0xAARRGGB。


<span id="HighlightConfig-border_width"></span>
### border_width
```cpp
int bytertc::HighlightConfig::border_width = 4;
```
边框的宽度，单位：像素。



# ScreenFilterConfig
```cpp
struct bytertc::ScreenFilterConfig
```

抓取屏幕时排除指定窗口，默认不排除任何窗体。


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **view_t*** | [excluded_window_list](#ScreenFilterConfig-excluded_window_list) |
| **int** | [excluded_window_num](#ScreenFilterConfig-excluded_window_num) |


## 变量说明
<span id="ScreenFilterConfig-excluded_window_list"></span>
### excluded_window_list
```cpp
view_t* bytertc::ScreenFilterConfig::excluded_window_list = nullptr;
```
抓取屏幕时排除窗口列表。这个参数仅在抓取屏幕时生效。


<span id="ScreenFilterConfig-excluded_window_num"></span>
### excluded_window_num
```cpp
int bytertc::ScreenFilterConfig::excluded_window_num = 0;
```
排除窗口的数量。



# MouseCursorCaptureState
```cpp
enum bytertc::MouseCursorCaptureState
```

内部采集屏幕视频流时，是否采集鼠标信息。


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMouseCursorCaptureStateOn | 0 | 采集鼠标信息。 |
| kMouseCursorCaptureStateOff | 1 | 不采集鼠标信息。 |


# ContentHint
```cpp
enum bytertc::ContentHint
```

内部采集屏幕视频流的内容类型。


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kContentHintDetails | 0 | 细节内容。当共享文档、图片时，建议使用该内容类型。默认值。 |
| kContentHintMotion | 1 | 动画内容。当共享视频、游戏时，建议使用该内容类型。 |


# ScreenCaptureParameters
```cpp
struct bytertc::ScreenCaptureParameters
```

屏幕共享内部采集参数


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ContentHint** | [content_hint](#ScreenCaptureParameters-content_hint) |
| **Rectangle** | [region_rect](#ScreenCaptureParameters-region_rect) |
| **MouseCursorCaptureState** | [capture_mouse_cursor](#ScreenCaptureParameters-capture_mouse_cursor) |
| **ScreenFilterConfig** | [filter_config](#ScreenCaptureParameters-filter_config) |
| **HighlightConfig** | [highlight_config](#ScreenCaptureParameters-highlight_config) |


## 变量说明
<span id="ScreenCaptureParameters-content_hint"></span>
### content_hint
```cpp
ContentHint bytertc::ScreenCaptureParameters::content_hint = kContentHintDetails;
```
内容类型，参看 [ContentHint](#contenthint)。


<span id="ScreenCaptureParameters-region_rect"></span>
### region_rect
```cpp
Rectangle bytertc::ScreenCaptureParameters::region_rect;
```
采集区域，参看 [Rectangle](#rectangle)。


<span id="ScreenCaptureParameters-capture_mouse_cursor"></span>
### capture_mouse_cursor
```cpp
MouseCursorCaptureState bytertc::ScreenCaptureParameters::capture_mouse_cursor;
```
是否采集鼠标状态，参看 [MouseCursorCaptureState](#mousecursorcapturestate)。


<span id="ScreenCaptureParameters-filter_config"></span>
### filter_config
```cpp
ScreenFilterConfig bytertc::ScreenCaptureParameters::filter_config;
```
屏幕过滤设置，填写不需要采集的窗口 ID，参看 [ScreenFilterConfig](#screenfilterconfig)。


<span id="ScreenCaptureParameters-highlight_config"></span>
### highlight_config
```cpp
HighlightConfig bytertc::ScreenCaptureParameters::highlight_config;
```
采集区域的边框高亮设置，参看 [HighlightConfig](#highlightconfig)。



# DesktopCaptureParameters
```cpp
struct bytertc::DesktopCaptureParameters
```

屏幕共享的编码参数配置。


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [max_width](#DesktopCaptureParameters-max_width) |
| **int** | [max_height](#DesktopCaptureParameters-max_height) |
| **int** | [frame_rate](#DesktopCaptureParameters-frame_rate) |
| **int** | [bitrate](#DesktopCaptureParameters-bitrate) |
| **bool** | [capture_mouse_cursor](#DesktopCaptureParameters-capture_mouse_cursor) |
| **view_t*** | [excluded_window_list](#DesktopCaptureParameters-excluded_window_list) |
| **int** | [excluded_window_num](#DesktopCaptureParameters-excluded_window_num) |
| **HighlightConfig** | [highlight_config](#DesktopCaptureParameters-highlight_config) |


## 变量说明
<span id="DesktopCaptureParameters-max_width"></span>
### max_width
```cpp
int bytertc::DesktopCaptureParameters::max_width = 1920;
```
屏幕采集编码最大宽度，单位 px。


<span id="DesktopCaptureParameters-max_height"></span>
### max_height
```cpp
int bytertc::DesktopCaptureParameters::max_height = 1080;
```
屏幕采集编码最大高度，单位 px。


<span id="DesktopCaptureParameters-frame_rate"></span>
### frame_rate
```cpp
int bytertc::DesktopCaptureParameters::frame_rate = 15;
```
屏幕采集编码帧率, 单位 fps。


<span id="DesktopCaptureParameters-bitrate"></span>
### bitrate
```cpp
int bytertc::DesktopCaptureParameters::bitrate = -1;
```
屏幕采集编码码率, -1 为自动码率, SDK 会根据宽高信息选择合适的码率，单位 kbps


<span id="DesktopCaptureParameters-capture_mouse_cursor"></span>
### capture_mouse_cursor
```cpp
bool bytertc::DesktopCaptureParameters::capture_mouse_cursor = true;
```
是否捕获鼠标光标


<span id="DesktopCaptureParameters-excluded_window_list"></span>
### excluded_window_list
```cpp
view_t* bytertc::DesktopCaptureParameters::excluded_window_list = nullptr;
```
抓取屏幕时排除窗口列表。这个参数仅在抓取屏幕时生效。


<span id="DesktopCaptureParameters-excluded_window_num"></span>
### excluded_window_num
```cpp
int bytertc::DesktopCaptureParameters::excluded_window_num = 0;
```
抓取屏幕时排除的窗口数量。


<span id="DesktopCaptureParameters-highlight_config"></span>
### highlight_config
```cpp
HighlightConfig bytertc::DesktopCaptureParameters::highlight_config;
```
高亮边框的配置。



# IVideoSink
```cpp
class bytertc::IVideoSink
```

自定义视频渲染器


`Defined in : bytertc_video_defines.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual bool** | [onFrame](#IVideoSink-onframe) |
| **virtual void** | [release](#IVideoSink-release) |


## 函数说明
<span id="IVideoSink-onframe"></span>
### onFrame
```cpp
virtual bool bytertc::IVideoSink::onFrame(
    IVideoFrame* videoFrame)
```
视频帧回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoFrame | **IVideoFrame*** | 视频帧结构类，参看 [IVideoFrame](#ivideoframe) |

**返回值**
返回值暂未使用


<span id="IVideoSink-release"></span>
### release
```cpp
virtual void bytertc::IVideoSink::release()
```
释放渲染器。


**注意**
通知开发者渲染器即将被废弃。收到该返回通知后即可释放资源。

# PixelFormat
```cpp
enum bytertc::IVideoSink::PixelFormat
```

视频帧编码格式


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kI420 | VideoPixelFormat::kVideoPixelFormatI420 | YUV I420 格式 |
| kOriginal | VideoPixelFormat::kVideoPixelFormatUnknown | 原始视频帧格式 |


# MirrorType
```cpp
enum bytertc::MirrorType
```

镜像类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMirrorTypeNone | 0 | 本地预览和编码传输时均无镜像效果 |
| kMirrorTypeRender | 1 | 本地预览时有镜像效果，编码传输时无镜像效果 |
| kMirrorTypeRenderAndEncoder | 3 | 本地预览和编码传输时均有镜像效果 |


# AdjustedMode
```cpp
enum bytertc::AdjustedMode
```

弱光适应类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kAdjustedModeDisabled | 0 | 关闭弱光适应 |
| kAdjustedModeEnabled | 1 | 开启弱光适应 |


# VideoSourceType
```cpp
enum bytertc::VideoSourceType
```

视频输入源类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| VideoSourceTypeExternal | 0 | 自定义采集视频源 |
| VideoSourceTypeInternal | 1 | 内部采集视频源 |
| VideoSourceTypeEncodedWithAutoSimulcast | 2 | 自定义编码视频源。  <br><br/>你仅需推送分辨率最大的一路编码后视频流，SDK 将自动转码生成多路小流 |
| VideoSourceTypeEncodedWithoutAutoSimulcast | 3 | 自定义编码视频源。  <br><br/>SDK 不会自动生成多路流，你需要自行生成并推送多路流 |


# VideoFrameInfo
```cpp
struct bytertc::VideoFrameInfo
```

视频帧信息


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#VideoFrameInfo-width) |
| **int** | [height](#VideoFrameInfo-height) |
| **VideoRotation** | [rotation](#VideoFrameInfo-rotation) |


## 变量说明
<span id="VideoFrameInfo-width"></span>
### width
```cpp
int bytertc::VideoFrameInfo::width = 0;
```
宽（像素）


<span id="VideoFrameInfo-height"></span>
### height
```cpp
int bytertc::VideoFrameInfo::height = 0;
```
高（像素）


<span id="VideoFrameInfo-rotation"></span>
### rotation
```cpp
VideoRotation bytertc::VideoFrameInfo::rotation = VideoRotation::kVideoRotation0;
```
视频帧顺时针旋转角度。参看 [VideoRotation](#videorotation)。



# VideoPreprocessorConfig
```cpp
struct bytertc::VideoPreprocessorConfig
```

视频前处理配置参数。<br>


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **VideoPixelFormat** | [required_pixel_format](#VideoPreprocessorConfig-required_pixel_format) |


## 变量说明
<span id="VideoPreprocessorConfig-required_pixel_format"></span>
### required_pixel_format
```cpp
VideoPixelFormat bytertc::VideoPreprocessorConfig::required_pixel_format = kVideoPixelFormatUnknown;
```
视频帧像素格式，参看 [VideoPixelFormat](#videopixelformat)



# VideoRateInfo
```cpp
struct bytertc::VideoRateInfo
```

自定义编码流信息


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [fps](#VideoRateInfo-fps) |
| **int** | [bitrate_kbps](#VideoRateInfo-bitrate_kbps) |


## 变量说明
<span id="VideoRateInfo-fps"></span>
### fps
```cpp
int bytertc::VideoRateInfo::fps;
```
帧率，单位 fps


<span id="VideoRateInfo-bitrate_kbps"></span>
### bitrate_kbps
```cpp
int bytertc::VideoRateInfo::bitrate_kbps;
```
码率，单位 kbps



# VideoDecoderConfig
```cpp
enum bytertc::VideoDecoderConfig
```

视频解码方式


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoDecoderConfigRaw | 0 | 开启 SDK 内部解码，只回调解码后的数据。回调为[onRemoteVideoFrame](Windows-callback.md#onremotevideoframe)。 |
| kVideoDecoderConfigEncode | 1 | 开启自定义解码，只回调解码前数据。回调为[onRemoteEncodedVideoFrame](Windows-callback.md#onremoteencodedvideoframe)。|
| kVideoDecoderConfigBoth | 2 | 开启 SDK 内部解码，同时回调解码前和解码后的数据。回调为[onRemoteVideoFrame](Windows-callback.md#onremotevideoframe)和[onRemoteEncodedVideoFrame](Windows-callback.md#onremoteencodedvideoframe)。 |


# VideoCaptureConfig
```cpp
struct bytertc::VideoCaptureConfig
```

视频采集配置参数。<br>


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **CapturePreference** | [capturePreference](#VideoCaptureConfig-capturepreference) |
| **int** | [width](#VideoCaptureConfig-width) |
| **int** | [height](#VideoCaptureConfig-height) |
| **int** | [frameRate](#VideoCaptureConfig-framerate) |


## 变量说明
<span id="VideoCaptureConfig-capturepreference"></span>
### capturePreference
```cpp
CapturePreference bytertc::VideoCaptureConfig::capturePreference = CapturePreference::KAuto;
```
视频采集模式，参看 [CapturePreference](#capturepreference-2)


<span id="VideoCaptureConfig-width"></span>
### width
```cpp
int bytertc::VideoCaptureConfig::width = 0;
```
视频采集分辨率的宽度，单位：px。


<span id="VideoCaptureConfig-height"></span>
### height
```cpp
int bytertc::VideoCaptureConfig::height = 0;
```
视频采集分辨率的高度，单位：px。


<span id="VideoCaptureConfig-framerate"></span>
### frameRate
```cpp
int bytertc::VideoCaptureConfig::frameRate = 0;
```
视频采集帧率，单位：fps。



# CapturePreference
```cpp
enum bytertc::VideoCaptureConfig::CapturePreference
```

视频采集模式


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| KAuto | 0 | （默认）自动设置采集参数。<br/>SDK在开启采集时根据服务端下发的采集配置结合编码参数设置最佳采集参数。 |
| KManual | 1 | 手动设置采集参数，包括采集分辨率、帧率。 |
| KAutoPerformance | 2 | 采集参数与编码参数一致，即在 [setVideoEncoderConfig](Windows-api.md#IRTCVideo-setvideoencoderconfig) 中设置的参数。 |


# RecordingType
```cpp
enum bytertc::RecordingType
```

本地录制的媒体类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRecordAudioOnly | 0 | 只录制音频 |
| kRecordVideoOnly | 1 | 只录制视频 |
| kRecordVideoAndAudio | 2 | 同时录制音频和视频 |


# RTCVideoDeviceType
```cpp
enum bytertc::RTCVideoDeviceType
```

当前视频设备类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kRTCVideoDeviceTypeUnknown | -1 | 未知设备类型 |
| kRTCVideoDeviceTypeRenderDevice | 0 | 视频渲染设备类型 |
| kRTCVideoDeviceTypeCaptureDevice | 1 | 视频采集设备类型 |
| kRTCVideoDeviceTypeScreenCaptureDevice | 2 | 屏幕流视频设备 |


# MediaStreamType
```cpp
enum bytertc::MediaStreamType
```

媒体流类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kMediaStreamTypeAudio | 1 << 0 | 只控制音频 |
| kMediaStreamTypeVideo | 1 << 1 | 只控制视频 |
| kMediaStreamTypeBoth | kMediaStreamTypeAudio \| kMediaStreamTypeVideo | 同时控制音频和视频 |


# FrameRateRatio
```cpp
enum bytertc::FrameRateRatio
```

占发布端原始帧率的比例


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kFrameRateRatioOriginal | 0 | 100% |
| kFrameRateRatioHalf | 1 | 50% |
| kFrameRateRatioQuarter | 2 | 25% |


# RemoteVideoConfig
```cpp
struct bytertc::RemoteVideoConfig
```

远端视频帧信息


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [framerate](#RemoteVideoConfig-framerate) |
| **int** | [resolution_width](#RemoteVideoConfig-resolution_width) |
| **int** | [resolution_height](#RemoteVideoConfig-resolution_height) |


## 变量说明
<span id="RemoteVideoConfig-framerate"></span>
### framerate
```cpp
int bytertc::RemoteVideoConfig::framerate = 0;
```
期望订阅的最高帧率，单位：fps，默认值为 0 即满帧订阅，设为大于 0 的值时开始生效。  <br>
当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
仅码流支持 SVC 分级编码特性时方可生效。


<span id="RemoteVideoConfig-resolution_width"></span>
### resolution_width
```cpp
int bytertc::RemoteVideoConfig::resolution_width = 0;
```
视频宽度，单位：px


<span id="RemoteVideoConfig-resolution_height"></span>
### resolution_height
```cpp
int bytertc::RemoteVideoConfig::resolution_height = 0;
```
视频高度，单位：px



# RTCRoomConfig
```cpp
struct bytertc::RTCRoomConfig
```

房间参数配置。房间是 RTC 通话的抽象概念。在同一个房间中的用户可以进行音视频通话。


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **RoomProfileType** | [room_profile_type](#RTCRoomConfig-room_profile_type) |
| **bool** | [is_auto_publish](#RTCRoomConfig-is_auto_publish) |
| **bool** | [is_auto_subscribe_audio](#RTCRoomConfig-is_auto_subscribe_audio) |
| **bool** | [is_auto_subscribe_video](#RTCRoomConfig-is_auto_subscribe_video) |
| **RemoteVideoConfig** | [remote_video_config](#RTCRoomConfig-remote_video_config) |


## 变量说明
<span id="RTCRoomConfig-room_profile_type"></span>
### room_profile_type
```cpp
RoomProfileType bytertc::RTCRoomConfig::room_profile_type = kRoomProfileTypeCommunication;
```
房间模式，参看 [RoomProfileType](#roomprofiletype)，默认为 `kRoomProfileTypeCommunication`，进房后不可更改。


<span id="RTCRoomConfig-is_auto_publish"></span>
### is_auto_publish
```cpp
bool bytertc::RTCRoomConfig::is_auto_publish = true;
```
是否自动发布音视频流，默认为自动发布。 <br>
创建和加入多房间时，只能将其中一个房间设置为自动发布。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。<br>
若调用 [setUserVisibility](Windows-api.md#IRTCRoom-setuservisibility) 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。


<span id="RTCRoomConfig-is_auto_subscribe_audio"></span>
### is_auto_subscribe_audio
```cpp
bool bytertc::RTCRoomConfig::is_auto_subscribe_audio = true;
```
是否自动订阅音频流，默认为自动订阅。<br>
包含主流和屏幕流。


<span id="RTCRoomConfig-is_auto_subscribe_video"></span>
### is_auto_subscribe_video
```cpp
bool bytertc::RTCRoomConfig::is_auto_subscribe_video = true;
```
是否自动订阅视频流，默认为自动订阅。<br>
包含主流和屏幕流。


<span id="RTCRoomConfig-remote_video_config"></span>
### remote_video_config
```cpp
RemoteVideoConfig bytertc::RTCRoomConfig::remote_video_config;
```
远端视频流参数，参看 [RemoteVideoConfig](#remotevideoconfig)



# ScreenMediaType
```cpp
enum bytertc::ScreenMediaType
```

屏幕采集的媒体类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kScreenMediaTypeVideoOnly | 0 | 仅采集视频 |
| kScreenMediaTypeAudioOnly | 1 | 仅采集音频 |
| kScreenMediaTypeVideoAndAudio | 2 | 同时采集音频和视频 |


# EffectBeautyMode
```cpp
enum bytertc::EffectBeautyMode
```

基础美颜模式


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kEffectBeautyWhite | 0 | 美白 |
| kEffectBeautySmooth | 1 | 磨皮 |
| kEffectBeautySharpen | 2 | 锐化 |


# VideoDeviceInfo
```cpp
struct bytertc::VideoDeviceInfo
```

视频设备信息


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **char** | [device_id](#VideoDeviceInfo-device_id) |
| **char** | [device_name](#VideoDeviceInfo-device_name) |
| **int64_t** | [device_vid](#VideoDeviceInfo-device_vid) |
| **int64_t** | [device_pid](#VideoDeviceInfo-device_pid) |
| **DeviceTransportType** | [transport_type](#VideoDeviceInfo-transport_type) |


## 变量说明
<span id="VideoDeviceInfo-device_id"></span>
### device_id
```cpp
char bytertc::VideoDeviceInfo::device_id[MAX_DEVICE_ID_LENGTH];
```
设备 ID


<span id="VideoDeviceInfo-device_name"></span>
### device_name
```cpp
char bytertc::VideoDeviceInfo::device_name[MAX_DEVICE_ID_LENGTH];
```
设备名称


<span id="VideoDeviceInfo-device_vid"></span>
### device_vid
```cpp
int64_t bytertc::VideoDeviceInfo::device_vid;
```
设备的厂商 ID


<span id="VideoDeviceInfo-device_pid"></span>
### device_pid
```cpp
int64_t bytertc::VideoDeviceInfo::device_pid;
```
设备的产品编码


<span id="VideoDeviceInfo-transport_type"></span>
### transport_type
```cpp
DeviceTransportType bytertc::VideoDeviceInfo::transport_type;
```
设备的传输方式



# ScreenCaptureSourceType
```cpp
enum bytertc::ScreenCaptureSourceType
```

屏幕采集对象的类型


`Defined in : bytertc_video_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kScreenCaptureSourceTypeUnknown | 0 | 类型未知 |
| kScreenCaptureSourceTypeWindow | 1 | 应用程序的窗口 |
| kScreenCaptureSourceTypeScreen | 2 | 桌面 |


# ScreenCaptureSourceInfo
```cpp
struct bytertc::ScreenCaptureSourceInfo
```

屏幕共享对象的详细信息


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ScreenCaptureSourceType** | [type](#ScreenCaptureSourceInfo-type) |
| **view_t** | [source_id](#ScreenCaptureSourceInfo-source_id) |
| **const char*** | [source_name](#ScreenCaptureSourceInfo-source_name) |
| **const char*** | [application](#ScreenCaptureSourceInfo-application) |
| **int** | [pid](#ScreenCaptureSourceInfo-pid) |
| **bool** | [primaryMonitor](#ScreenCaptureSourceInfo-primarymonitor) |
| **Rectangle** | [region_rect](#ScreenCaptureSourceInfo-region_rect) |


## 变量说明
<span id="ScreenCaptureSourceInfo-type"></span>
### type
```cpp
ScreenCaptureSourceType bytertc::ScreenCaptureSourceInfo::type = kScreenCaptureSourceTypeUnknown;
```
屏幕共享对象的类型，参看 [ScreenCaptureSourceType](#screencapturesourcetype)


<span id="ScreenCaptureSourceInfo-source_id"></span>
### source_id
```cpp
view_t bytertc::ScreenCaptureSourceInfo::source_id = nullptr;
```
屏幕共享对象的 ID


<span id="ScreenCaptureSourceInfo-source_name"></span>
### source_name
```cpp
const char* bytertc::ScreenCaptureSourceInfo::source_name = nullptr;
```
屏幕共享对象的名称<br>
调用 [release](Windows-api.md#IScreenCaptureSourceList-release) 时将被释放，请及时转为 string 对象保存


<span id="ScreenCaptureSourceInfo-application"></span>
### application
```cpp
const char* bytertc::ScreenCaptureSourceInfo::application = nullptr;
```
共享的应用窗体所属应用的名称<br>
当共享对象为应用窗体时有效 <br>
调用 [release](Windows-api.md#IScreenCaptureSourceList-release) 时将被释放，请及时转为 string 对象保存<br>


<span id="ScreenCaptureSourceInfo-pid"></span>
### pid
```cpp
int bytertc::ScreenCaptureSourceInfo::pid;
```
共享的应用窗体所属应用进程的 pid<br>
当共享对象为应用窗体时有效 <br>


<span id="ScreenCaptureSourceInfo-primarymonitor"></span>
### primaryMonitor
```cpp
bool bytertc::ScreenCaptureSourceInfo::primaryMonitor = false;
```
共享的屏幕是否为主屏。<br>
当共享对象为屏幕时有效 <br>


<span id="ScreenCaptureSourceInfo-region_rect"></span>
### region_rect
```cpp
Rectangle bytertc::ScreenCaptureSourceInfo::region_rect;
```
屏幕共享对象的坐标，用于指定采集区域（默认为采集源的整个画面）。<br>
仅在采集源为显示器屏幕时有效。<br>
多显示器的场景下，屏幕坐标以主屏左上角为原点 (0, 0)，向右向下扩展。详见 [Rectangle](#rectangle)。



# VideoMetadataBuffer
```cpp
struct bytertc::VideoMetadataBuffer
```

视频帧中包含的 metadata 信息


`Defined in : bytertc_video_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **char*** | [data](#VideoMetadataBuffer-data) |
| **int** | [size](#VideoMetadataBuffer-size) |
| **int64_t** | [timestamp_us](#VideoMetadataBuffer-timestamp_us) |


## 变量说明
<span id="VideoMetadataBuffer-data"></span>
### data
```cpp
char* bytertc::VideoMetadataBuffer::data;
```
接收或者发送的 metadata


<span id="VideoMetadataBuffer-size"></span>
### size
```cpp
int bytertc::VideoMetadataBuffer::size;
```
接收或者发送的 metadata 数据大小，不能超过 1024


<span id="VideoMetadataBuffer-timestamp_us"></span>
### timestamp_us
```cpp
int64_t bytertc::VideoMetadataBuffer::timestamp_us;
```
包含 metadata 视频帧的时间戳，单位微秒



# VirtualBackgroundSourceType
```cpp
enum bytertc::VirtualBackgroundSourceType
```

虚拟背景类型。


`Defined in : bytertc_video_effect_interface.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVirtualBackgroundSourceColor | 0 | 使用纯色背景替换视频原有背景。 |
| kVirtualBackgroundSourceImage | 1 | 使用自定义图片替换视频原有背景。 |


# VirtualBackgroundSource
```cpp
struct bytertc::VirtualBackgroundSource
```

虚拟背景对象。


`Defined in : bytertc_video_effect_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **VirtualBackgroundSourceType** | [source_type](#VirtualBackgroundSource-source_type) |
| **uint32_t** | [source_color](#VirtualBackgroundSource-source_color) |
| **const char*** | [source_path](#VirtualBackgroundSource-source_path) |


## 变量说明
<span id="VirtualBackgroundSource-source_type"></span>
### source_type
```cpp
VirtualBackgroundSourceType bytertc::VirtualBackgroundSource::source_type;
```
虚拟背景类型，详见 [VirtualBackgroundSourceType](#virtualbackgroundsourcetype) 。


<span id="VirtualBackgroundSource-source_color"></span>
### source_color
```cpp
uint32_t bytertc::VirtualBackgroundSource::source_color = 0xFFFFFFFF;
```
纯色背景使用的颜色。<br>
格式为 0xAARRGGBB 。


<span id="VirtualBackgroundSource-source_path"></span>
### source_path
```cpp
const char* bytertc::VirtualBackgroundSource::source_path = nullptr;
```
自定义背景图片的绝对路径。

+ 支持的格式为 jpg、jpeg、png。  <br>
+ 图片分辨率超过 1080P 时，图片会被等比缩放至和视频一致。  <br>
+ 图片和视频宽高比一致时，图片会被直接缩放至和视频一致。  <br>
+ 图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。  <br>
+ 自定义图片带有局部透明效果时，透明部分由黑色代替。



# FaceDetectResult
```cpp
struct bytertc::FaceDetectResult
```

人脸检测结果


`Defined in : bytertc_video_effect_interface.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [detect_result](#FaceDetectResult-detect_result) |
| **int** | [face_count](#FaceDetectResult-face_count) |
| **Rectangle** | [rect](#FaceDetectResult-rect) |
| **int** | [image_width](#FaceDetectResult-image_width) |
| **int** | [image_height](#FaceDetectResult-image_height) |


## 变量说明
<span id="FaceDetectResult-detect_result"></span>
### detect_result
```cpp
int bytertc::FaceDetectResult::detect_result = 0;
```
人脸检测结果 <br>

+ 0：检测成功 <br>
+ !0：检测失败。详见[CV 错误码](https://www.volcengine.com/docs/6705/102042)。


<span id="FaceDetectResult-face_count"></span>
### face_count
```cpp
int bytertc::FaceDetectResult::face_count = 0;
```
检测到的人脸的数量


<span id="FaceDetectResult-rect"></span>
### rect
```cpp
Rectangle bytertc::FaceDetectResult::rect[max_face_num];
```
识别到人脸的矩形框。数组的长度和检测到的人脸数量一致。参看 [Rectangle](#rectangle)。


<span id="FaceDetectResult-image_width"></span>
### image_width
```cpp
int bytertc::FaceDetectResult::image_width = 0;
```
原始图片宽度(px)


<span id="FaceDetectResult-image_height"></span>
### image_height
```cpp
int bytertc::FaceDetectResult::image_height = 0;
```
原始图片高度(px)



# VideoPictureType
```cpp
enum bytertc::VideoPictureType
```

编码帧类型


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoPictureTypeUnknown | 0 | 未知类型 |
| kVideoPictureTypeI | 1 | I帧，关键帧，编解码不需要参考其他视频帧 |
| kVideoPictureTypeP | 2 | P帧，向前参考帧，编解码需要参考前一帧视频帧 |
| kVideoPictureTypeB | 3 | B帧，前后参考帧，编解码需要参考前后两帧视频帧 |


# VideoRotation
```cpp
enum bytertc::VideoRotation
```

视频帧旋转角度


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoRotation0 | 0 | 顺时针旋转 0 度 |
| kVideoRotation90 | 90 | 顺时针旋转 90 度 |
| kVideoRotation180 | 180 | 顺时针旋转 180 度 |
| kVideoRotation270 | 270 | 顺时针旋转 270 度 |


# VideoStreamScaleMode
```cpp
enum bytertc::VideoStreamScaleMode
```

视频帧缩放模式，默认值为 FitWithCropping。


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoStreamScaleModeAuto | 0 | 自动模式 |
| kVideoStreamScaleModeStretch | 1 | 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。 |
| kVideoStreamScaleModeFitWithCropping | 2 | 视窗填满优先，默认值。<br><br/>视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br><br/>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。 |
| kVideoStreamScaleModeFitWithFilling | 3 | 视频帧内容全部显示优先。<br><br/>视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br><br/>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。 |


# VideoCodecMode
```cpp
enum bytertc::VideoCodecMode
```

视频编码模式


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kCodecModeAuto | 0 | 自动选择 |
| kCodecModeHardware | 1 | 硬编码 |
| kCodecModeSoftware | 2 | 软编码 |


# VideoEncodePreference
```cpp
enum bytertc::VideoEncodePreference
```

编码策略偏好。


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoEncodePreferenceDisabled | 0 | 无偏好。不降低帧率和分辨率。 |
| kVideoEncodePreferenceFramerate | 1 | （默认值）帧率优先。 |
| kVideoEncodePreferenceQuality | 2 | 分辨率优先。 |
| kVideoEncodePreferenceBalance | 3 | 平衡帧率与分辨率。 |


# CameraID
```cpp
enum bytertc::CameraID
```

摄像头。


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kCameraIDFront | 0 | 移动端前置摄像头，PC端内置摄像头 |
| kCameraIDBack | 1 | 移动端后置摄像头，PC端无定义 |
| kCameraIDExternal | 2 | 外接摄像头 |
| kCameraIDInvalid | 3 | 无效值 |


# VideoSolution
```cpp
struct bytertc::VideoSolution
```

视频流参数


`Defined in : bytertc_video_frame.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#VideoSolution-width) |
| **int** | [height](#VideoSolution-height) |
| **int** | [fps](#VideoSolution-fps) |
| **int** | [max_send_kbps](#VideoSolution-max_send_kbps) |
| **VideoEncodePreference** | [encode_preference](#VideoSolution-encode_preference) |
| **VideoOrientation** | [orientation](#VideoSolution-orientation) |


## 变量说明
<span id="VideoSolution-width"></span>
### width
```cpp
int bytertc::VideoSolution::width;
```
视频宽度，单位：像素


<span id="VideoSolution-height"></span>
### height
```cpp
int bytertc::VideoSolution::height;
```
视频高度，单位：像素


<span id="VideoSolution-fps"></span>
### fps
```cpp
int bytertc::VideoSolution::fps;
```
视频帧率


<span id="VideoSolution-max_send_kbps"></span>
### max_send_kbps
```cpp
int bytertc::VideoSolution::max_send_kbps = SEND_KBPS_AUTO_CALCULATE;
```
最大发送编码码率（kbps），建议使用默认的自动码率。<li>-1: 自动码率</li><li>0: 不开启上限</li><li>>0: 填写预估码率<li>


<span id="VideoSolution-encode_preference"></span>
### encode_preference
```cpp
VideoEncodePreference bytertc::VideoSolution::encode_preference = VideoEncodePreference::kVideoEncodePreferenceFrame/;"
```
视频编码质量策略，参看 [VideoEncodePreference](#videoencodepreference)


<span id="VideoSolution-orientation"></span>
### orientation
```cpp
VideoOrientation bytertc::VideoSolution::orientation = VideoOrientation::kVideoOrientationAdaptive;
```
将视频编码为横屏帧（Landscape）或者竖屏帧（Portrait）,默认与发送端横竖屏保持一致（Adaptive）



# VideoEncoderConfig
```cpp
struct bytertc::VideoEncoderConfig
```

视频编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)


`Defined in : bytertc_video_frame.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#VideoEncoderConfig-width) |
| **int** | [height](#VideoEncoderConfig-height) |
| **int** | [frameRate](#VideoEncoderConfig-framerate) |
| **int** | [maxBitrate](#VideoEncoderConfig-maxbitrate) |
| **VideoEncodePreference** | [encoderPreference](#VideoEncoderConfig-encoderpreference) |


## 变量说明
<span id="VideoEncoderConfig-width"></span>
### width
```cpp
int bytertc::VideoEncoderConfig::width;
```
视频宽度，单位：像素


<span id="VideoEncoderConfig-height"></span>
### height
```cpp
int bytertc::VideoEncoderConfig::height;
```
视频高度，单位：像素


<span id="VideoEncoderConfig-framerate"></span>
### frameRate
```cpp
int bytertc::VideoEncoderConfig::frameRate;
```
视频帧率，单位：fps


<span id="VideoEncoderConfig-maxbitrate"></span>
### maxBitrate
```cpp
int bytertc::VideoEncoderConfig::maxBitrate = SEND_KBPS_AUTO_CALCULATE;
```
最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。  <br>
内部采集模式下默认值为 -1，即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。 <br>
设为 0 则不对视频流进行编码发送。


<span id="VideoEncoderConfig-encoderpreference"></span>
### encoderPreference
```cpp
VideoEncodePreference bytertc::VideoEncoderConfig::encoderPreference = VideoEncodePreference::kVideoEncodePreferenceFrame/;"
```
编码策略偏好，默认为帧率优先。参看 [VideoEncodePreference](#videoencodepreference)。



# VideoPixelFormat
```cpp
enum bytertc::VideoPixelFormat
```

视频帧颜色编码格式


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoPixelFormatUnknown | 0 | 未知的颜色编码格式 |
| kVideoPixelFormatI420 | 1 | YUV I420 格式 |
| kVideoPixelFormatNV12 | 2 | YUV NV12 格式 |
| kVideoPixelFormatNV21 | 3 | YUV NV21 格式 |
| kVideoPixelFormatRGB24 | 4 | RGB 24bit格式， |
| kVideoPixelFormatRGBA | 5 | RGBA 编码格式 |
| kVideoPixelFormatARGB | 6 | ARGB 编码格式 |
| kVideoPixelFormatBGRA | 7 | BGRA 编码格式 |
| kVideoPixelFormatTexture2D | 0x0DE1 | Texture2D格式 |
| kVideoPixelFormatTextureOES | 0x8D65 | TextureOES格式 |


# VideoContentType
```cpp
enum bytertc::VideoContentType
```

视频内容类型


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoContentTypeNormalFrame | 0 | 普通视频 |
| kVideoContentTypeBlackFrame | 1 | 黑帧视频 |


# ColorSpace
```cpp
enum bytertc::ColorSpace
```

视频YUV格式颜色空间


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kColorSpaceUnknown | 0 |  |
| kColorSpaceYCbCrBT601LimitedRange | 1 | BT.601数字编码标准，颜色空间[16-235] |
| kColorSpaceYCbCrBT601FullRange | 2 | BT.601数字编码标准，颜色空间[0-255] |
| kColorSpaceYCbCrBT709LimitedRange | 3 | BT.7091数字编码标准，颜色空间[16-235] |
| kColorSpaceYCbCrBT709FullRange | 4 | BT.7091数字编码标准，颜色空间[0-255] |


# VideoFrameType
```cpp
enum bytertc::VideoFrameType
```

视频帧格式


`Defined in : bytertc_video_frame.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kVideoFrameTypeRawMemory | 0 | 原始数据格式，按照内存存储 |
| kVideoFrameTypeCVPixelBuffer | 1 | CVPixelBufferRef类型，支持 iOS and macOS 平台 |
| kVideoFrameTypeGLTexture | 2 | open gl 纹理数据类型 |
| kVideoFrameTypeCuda | 3 | cuda 数据类型 |
| kVideoFrameTypeD3D11 | 4 | direct3d 11 数据格式 |
| kVideoFrameTypeD3D9 | 5 | direct3d 9 数据格式 |
| kVideoFrameTypeJavaFrame | 6 | Java的VideoFrame 数据格式 |
| kVideoFrameTypeVAAPI | 7 | vaapi 数据格式 |


# ManagedMemory
```cpp
struct bytertc::ManagedMemory
```

自定义内存释放器


`Defined in : bytertc_video_frame.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **uint8_t*** | [data](#ManagedMemory-data) |
| **int** | [size](#ManagedMemory-size) |
| **void*** | [user_opaque](#ManagedMemory-user_opaque) |
| **int (*)(uint8_t* data, int size, void* user_opaque)** | [memory_deleter](#ManagedMemory-memory_deleter) |


## 变量说明
<span id="ManagedMemory-data"></span>
### data
```cpp
uint8_t* bytertc::ManagedMemory::data = nullptr;
```
内存数据地址


<span id="ManagedMemory-size"></span>
### size
```cpp
int bytertc::ManagedMemory::size = 0;
```
内存空间的大小


<span id="ManagedMemory-user_opaque"></span>
### user_opaque
```cpp
void* bytertc::ManagedMemory::user_opaque = nullptr;
```
用户自定义数据


<span id="ManagedMemory-memory_deleter"></span>
### memory_deleter
```cpp
int (*bytertc::ManagedMemory::memory_deleter)(uint8_t* data, int size, void* user_opaque) = nullptr;
```
自定义内存释放方法指针，如果指针不为空，方法会被调用，用来释放内存空间。
函数传入的参数分别是本结构体内 data、size、user_opaque 3个字段。



# VideoFrameBuilder
```cpp
typedef struct bytertc::VideoFrameBuilder
```

视频帧构建类


`Defined in : bytertc_video_frame.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **uint8_t*** | [data](#VideoFrameBuilder-data) |
| **int** | [linesize](#VideoFrameBuilder-linesize) |
| **uint8_t*** | [extra_data](#VideoFrameBuilder-extra_data) |
| **int** | [extra_data_size](#VideoFrameBuilder-extra_data_size) |
| **uint8_t*** | [supplementary_info](#VideoFrameBuilder-supplementary_info) |
| **int** | [supplementary_info_size](#VideoFrameBuilder-supplementary_info_size) |
| **int** | [size](#VideoFrameBuilder-size) |
| **int** | [width](#VideoFrameBuilder-width) |
| **int** | [height](#VideoFrameBuilder-height) |
| **VideoRotation** | [rotation](#VideoFrameBuilder-rotation) |
| **void*** | [hwaccel_buffer](#VideoFrameBuilder-hwaccel_buffer) |
| **void*** | [user_opaque](#VideoFrameBuilder-user_opaque) |
| **int64_t** | [timestamp_us](#VideoFrameBuilder-timestamp_us) |
| **void*** | [hwaccel_context](#VideoFrameBuilder-hwaccel_context) |
| **jobject** | [android_hwaccel_context](#VideoFrameBuilder-android_hwaccel_context) |
| **float** | [tex_matrix](#VideoFrameBuilder-tex_matrix) |
| **uint32_t** | [texture_id](#VideoFrameBuilder-texture_id) |
| **int (*)(struct VideoFrameBuilder* builder)** | [memory_deleter](#VideoFrameBuilder-memory_deleter) |


## 变量说明
<span id="VideoFrameBuilder-data"></span>
### data
```cpp
uint8_t* bytertc::VideoFrameBuilder::data[ByteRTCNumDataPointers] = { 0 };
```
视频帧数据平面指针数组


<span id="VideoFrameBuilder-linesize"></span>
### linesize
```cpp
int bytertc::VideoFrameBuilder::linesize[ByteRTCNumDataPointers] = { 0 };
```
视频帧数据平面行长度


<span id="VideoFrameBuilder-extra_data"></span>
### extra_data
```cpp
uint8_t* bytertc::VideoFrameBuilder::extra_data = nullptr;
```
SEI 数据地址


<span id="VideoFrameBuilder-extra_data_size"></span>
### extra_data_size
```cpp
int bytertc::VideoFrameBuilder::extra_data_size = 0;
```
SEI 数据大小


<span id="VideoFrameBuilder-supplementary_info"></span>
### supplementary_info
```cpp
uint8_t* bytertc::VideoFrameBuilder::supplementary_info = nullptr;
```
补充数据地址


<span id="VideoFrameBuilder-supplementary_info_size"></span>
### supplementary_info_size
```cpp
int bytertc::VideoFrameBuilder::supplementary_info_size = 0;
```
补充数据大小


<span id="VideoFrameBuilder-size"></span>
### size
```cpp
int bytertc::VideoFrameBuilder::size = 0;
```
视频帧内存空间大小


<span id="VideoFrameBuilder-width"></span>
### width
```cpp
int bytertc::VideoFrameBuilder::width = 0;
```
视频帧宽度


<span id="VideoFrameBuilder-height"></span>
### height
```cpp
int bytertc::VideoFrameBuilder::height = 0;
```
视频帧高度


<span id="VideoFrameBuilder-rotation"></span>
### rotation
```cpp
VideoRotation bytertc::VideoFrameBuilder::rotation = kVideoRotation0;
```
视频旋转角度，参看 [VideoRotation](#videorotation)


<span id="VideoFrameBuilder-hwaccel_buffer"></span>
### hwaccel_buffer
```cpp
void* bytertc::VideoFrameBuilder::hwaccel_buffer = nullptr;
```
硬件加速缓冲区指针


<span id="VideoFrameBuilder-user_opaque"></span>
### user_opaque
```cpp
void* bytertc::VideoFrameBuilder::user_opaque = nullptr;
```
用户私有数据指针


<span id="VideoFrameBuilder-timestamp_us"></span>
### timestamp_us
```cpp
int64_t bytertc::VideoFrameBuilder::timestamp_us = 0;
```
视频帧时间戳


<span id="VideoFrameBuilder-hwaccel_context"></span>
### hwaccel_context
```cpp
void* bytertc::VideoFrameBuilder::hwaccel_context = nullptr;
```
硬件加速Context对象(AKA Opengl Context, Vulkan Context)


<span id="VideoFrameBuilder-android_hwaccel_context"></span>
### android_hwaccel_context
```cpp
jobject bytertc::VideoFrameBuilder::android_hwaccel_context = nullptr;
```
硬件加速Context的Java对象(Only for Android, AKA Opengl Context)


<span id="VideoFrameBuilder-tex_matrix"></span>
### tex_matrix
```cpp
float bytertc::VideoFrameBuilder::tex_matrix[16] = { };
```
纹理矩阵(仅针对纹理类型的frame生效)


<span id="VideoFrameBuilder-texture_id"></span>
### texture_id
```cpp
uint32_t bytertc::VideoFrameBuilder::texture_id = 0;
```
纹理ID(仅针对纹理类型的frame生效)


<span id="VideoFrameBuilder-memory_deleter"></span>
### memory_deleter
```cpp
int (*bytertc::VideoFrameBuilder::memory_deleter)(struct VideoFrameBuilder* builder) = nullptr;
```
用户定义的视频帧释放回调函数指针，如果指针不为空，方法会被调用用来释放内存空间



# IVideoFrame
```cpp
class bytertc::IVideoFrame
```

设置视频帧


`Defined in : bytertc_video_frame.h`

## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual VideoFrameType** | [frameType](#IVideoFrame-frametype) |
| **virtual VideoPixelFormat** | [pixelFormat](#IVideoFrame-pixelformat) |
| **virtual VideoContentType** | [videoContentType](#IVideoFrame-videocontenttype) |
| **virtual int64_t** | [timestampUs](#IVideoFrame-timestampus) |
| **virtual int** | [width](#IVideoFrame-width) |
| **virtual int** | [height](#IVideoFrame-height) |
| **virtual VideoRotation** | [rotation](#IVideoFrame-rotation) |
| **virtual ColorSpace** | [colorSpace](#IVideoFrame-colorspace) |
| **virtual int** | [numberOfPlanes](#IVideoFrame-numberofplanes) |
| **virtual uint8_t*** | [getPlaneData](#IVideoFrame-getplanedata) |
| **virtual int** | [getPlaneStride](#IVideoFrame-getplanestride) |
| **virtual uint8_t*** | [getExtraDataInfo](#IVideoFrame-getextradatainfo) |
| **virtual uint8_t*** | [getSupplementaryInfo](#IVideoFrame-getsupplementaryinfo) |
| **virtual void*** | [getHwaccelBuffer](#IVideoFrame-gethwaccelbuffer) |
| **virtual void*** | [getHwaccelContext](#IVideoFrame-gethwaccelcontext) |
| **virtual jobject** | [getAndroidHwaccelContext](#IVideoFrame-getandroidhwaccelcontext) |
| **virtual void** | [getTexMatrix](#IVideoFrame-gettexmatrix) |
| **virtual uint32_t** | [getTextureId](#IVideoFrame-gettextureid) |
| **virtual IVideoFrame*** | [shallowCopy](#IVideoFrame-shallowcopy) |
| **virtual void** | [release](#IVideoFrame-release) |
| **virtual void** | [toI420](#IVideoFrame-toi420) |
| **virtual CameraID** | [getCameraId](#IVideoFrame-getcameraid) |


## 函数说明
<span id="IVideoFrame-frametype"></span>
### frameType
```cpp
virtual VideoFrameType bytertc::IVideoFrame::frameType() const
```
获取视频帧类型，参看 [VideoFrameType](#videoframetype)


<span id="IVideoFrame-pixelformat"></span>
### pixelFormat
```cpp
virtual VideoPixelFormat bytertc::IVideoFrame::pixelFormat() const
```
获取视频帧格式，参看 [VideoPixelFormat](#videopixelformat)


<span id="IVideoFrame-videocontenttype"></span>
### videoContentType
```cpp
virtual VideoContentType bytertc::IVideoFrame::videoContentType() const
```
获取视频内容类型，参看 [VideoContentType](#videocontenttype)。


<span id="IVideoFrame-timestampus"></span>
### timestampUs
```cpp
virtual int64_t bytertc::IVideoFrame::timestampUs() const
```
获取视频帧时间戳，单位：微秒


<span id="IVideoFrame-width"></span>
### width
```cpp
virtual int bytertc::IVideoFrame::width() const
```
获取视频帧宽度，单位：px


<span id="IVideoFrame-height"></span>
### height
```cpp
virtual int bytertc::IVideoFrame::height() const
```
获取视频帧高度，单位：px


<span id="IVideoFrame-rotation"></span>
### rotation
```cpp
virtual VideoRotation bytertc::IVideoFrame::rotation() const
```
获取视频帧旋转角度，参看 [VideoRotation](#videorotation)


<span id="IVideoFrame-colorspace"></span>
### colorSpace
```cpp
virtual ColorSpace bytertc::IVideoFrame::colorSpace() const
```
获取视频帧颜色空间，参看 [ColorSpace](#colorspace)


<span id="IVideoFrame-numberofplanes"></span>
### numberOfPlanes
```cpp
virtual int bytertc::IVideoFrame::numberOfPlanes() const
```
视频帧颜色 plane 数量


**注意**
yuv 数据存储格式分为打包（packed）存储格式和平面（planar）存储格式，planar 格式中 Y、U、V 分平面存储，packed 格式中 Y、U、V 交叉存储

<span id="IVideoFrame-getplanedata"></span>
### getPlaneData
```cpp
virtual uint8_t* bytertc::IVideoFrame::getPlaneData(
    int plane_index)
```
获取 plane 数据指针

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| plane_index | **int** | plane 数据索引 |


<span id="IVideoFrame-getplanestride"></span>
### getPlaneStride
```cpp
virtual int bytertc::IVideoFrame::getPlaneStride(
    int plane_index)
```
获取 plane 中数据行的长度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| plane_index | **int** | plane 数据索引 |


<span id="IVideoFrame-getextradatainfo"></span>
### getExtraDataInfo
```cpp
virtual uint8_t* bytertc::IVideoFrame::getExtraDataInfo(
    int& size)
```
获取扩展数据指针

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| size | **int&** | 扩展数据字节数 |


<span id="IVideoFrame-getsupplementaryinfo"></span>
### getSupplementaryInfo
```cpp
virtual uint8_t* bytertc::IVideoFrame::getSupplementaryInfo(
    int& size)
```
获取补充数据指针

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| size | **int&** | 补充数据字节数 |


<span id="IVideoFrame-gethwaccelbuffer"></span>
### getHwaccelBuffer
```cpp
virtual void* bytertc::IVideoFrame::getHwaccelBuffer()
```
获取本地缓冲区指针


<span id="IVideoFrame-gethwaccelcontext"></span>
### getHwaccelContext
```cpp
virtual void* bytertc::IVideoFrame::getHwaccelContext()
```
获取硬件加速Context对象(AKA Opengl Context, Vulkan Context)


<span id="IVideoFrame-getandroidhwaccelcontext"></span>
### getAndroidHwaccelContext
```cpp
virtual jobject bytertc::IVideoFrame::getAndroidHwaccelContext()
```
获取硬件加速Context的Java对象(Only for Android, AKA Opengl Context)

**返回值**
返回JavaLocalRef, 当不再使用时，需要手动执行DeleteLocalRef(env, jobject)方法释放该对象


<span id="IVideoFrame-gettexmatrix"></span>
### getTexMatrix
```cpp
virtual void bytertc::IVideoFrame::getTexMatrix(
    float matrix[16])
```
获取纹理矩阵(仅针对纹理类型的frame生效)


<span id="IVideoFrame-gettextureid"></span>
### getTextureId
```cpp
virtual uint32_t bytertc::IVideoFrame::getTextureId()
```
获取纹理ID(仅针对纹理类型的frame生效)


<span id="IVideoFrame-shallowcopy"></span>
### shallowCopy
```cpp
virtual IVideoFrame* bytertc::IVideoFrame::shallowCopy()
```
浅拷贝视频帧并返回指针


<span id="IVideoFrame-release"></span>
### release
```cpp
virtual void bytertc::IVideoFrame::release()
```
释放视频帧

**注意**

调用 [pushExternalVideoFrame](Windows-api.md#IRTCVideo-pushexternalvideoframe) 推送视频帧后，你不需要再调用此方法释放资源。



<span id="IVideoFrame-toi420"></span>
### toI420
```cpp
virtual void bytertc::IVideoFrame::toI420()
```
转换为i420格式的视频帧


<span id="IVideoFrame-getcameraid"></span>
### getCameraId
```cpp
virtual CameraID bytertc::IVideoFrame::getCameraId() const
```
获取视频帧的摄像头信息，参看 [CameraID](#cameraid)


# EncodedVideoFrameBuilder
```cpp
typedef struct bytertc::EncodedVideoFrameBuilder
```

视频帧参数


`Defined in : bytertc_video_frame.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **VideoCodecType** | [codec_type](#EncodedVideoFrameBuilder-codec_type) |
| **VideoPictureType** | [picture_type](#EncodedVideoFrameBuilder-picture_type) |
| **VideoRotation** | [rotation](#EncodedVideoFrameBuilder-rotation) |
| **uint8_t*** | [data](#EncodedVideoFrameBuilder-data) |
| **int** | [size](#EncodedVideoFrameBuilder-size) |
| **int** | [width](#EncodedVideoFrameBuilder-width) |
| **int** | [height](#EncodedVideoFrameBuilder-height) |
| **int64_t** | [timestamp_us](#EncodedVideoFrameBuilder-timestamp_us) |
| **int64_t** | [timestamp_dts_us](#EncodedVideoFrameBuilder-timestamp_dts_us) |
| **int (*)(uint8_t* data, int size, void* user_opaque)** | [memory_deleter](#EncodedVideoFrameBuilder-memory_deleter) |


## 变量说明
<span id="EncodedVideoFrameBuilder-codec_type"></span>
### codec_type
```cpp
VideoCodecType bytertc::EncodedVideoFrameBuilder::codec_type = kVideoCodecTypeUnknown;
```
视频帧编码格式，参看 [VideoCodecType](#videocodectype)


<span id="EncodedVideoFrameBuilder-picture_type"></span>
### picture_type
```cpp
VideoPictureType bytertc::EncodedVideoFrameBuilder::picture_type = kVideoPictureTypeUnknown;
```
视频帧编码类型，参看 [VideoPictureType](#videopicturetype)


<span id="EncodedVideoFrameBuilder-rotation"></span>
### rotation
```cpp
VideoRotation bytertc::EncodedVideoFrameBuilder::rotation = kVideoRotation0;
```
视频帧旋转角度，参看 [VideoRotation](#videorotation)


<span id="EncodedVideoFrameBuilder-data"></span>
### data
```cpp
uint8_t* bytertc::EncodedVideoFrameBuilder::data = nullptr;
```
视频帧数据指针

**注意:**
IEncodedVideoFrame 会获取数据的所有权
IEncodedVideoFrame 会获取数据的所有权

<span id="EncodedVideoFrameBuilder-size"></span>
### size
```cpp
int bytertc::EncodedVideoFrameBuilder::size = 0;
```
视频帧数据大小


<span id="EncodedVideoFrameBuilder-width"></span>
### width
```cpp
int bytertc::EncodedVideoFrameBuilder::width = 0;
```
视频帧宽度，单位：px


<span id="EncodedVideoFrameBuilder-height"></span>
### height
```cpp
int bytertc::EncodedVideoFrameBuilder::height = 0;
```
视频帧高度，单位：px


<span id="EncodedVideoFrameBuilder-timestamp_us"></span>
### timestamp_us
```cpp
int64_t bytertc::EncodedVideoFrameBuilder::timestamp_us = 0;
```
视频采集时间戳，单位：微秒


<span id="EncodedVideoFrameBuilder-timestamp_dts_us"></span>
### timestamp_dts_us
```cpp
int64_t bytertc::EncodedVideoFrameBuilder::timestamp_dts_us = 0;
```
视频编码时间戳，单位：微秒


<span id="EncodedVideoFrameBuilder-memory_deleter"></span>
### memory_deleter
```cpp
int (*bytertc::EncodedVideoFrameBuilder::memory_deleter)(uint8_t* data, int size, void* user_opaque) = nullptr;
```
用户定义的视频帧释放回调函数指针，如果指针不为空，方法会被调用用来释放内存空间



# IEncodedVideoFrame
```cpp
class bytertc::IEncodedVideoFrame
```

视频帧信息


`Defined in : bytertc_video_frame.h`

## 静态函数

| 返回 | 名称 |
| --- | --- |
| **static IEncodedVideoFrame*** | [buildEncodedVideoFrame](#IEncodedVideoFrame-buildencodedvideoframe) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **virtual VideoCodecType** | [codecType](#IEncodedVideoFrame-codectype) |
| **virtual int64_t** | [timestampUs](#IEncodedVideoFrame-timestampus) |
| **virtual int64_t** | [timestampDtsUs](#IEncodedVideoFrame-timestampdtsus) |
| **virtual int** | [width](#IEncodedVideoFrame-width) |
| **virtual int** | [height](#IEncodedVideoFrame-height) |
| **virtual VideoPictureType** | [pictureType](#IEncodedVideoFrame-picturetype) |
| **virtual VideoRotation** | [rotation](#IEncodedVideoFrame-rotation) |
| **virtual uint8_t*** | [data](#IEncodedVideoFrame-data) |
| **virtual int** | [dataSize](#IEncodedVideoFrame-datasize) |
| **virtual IEncodedVideoFrame*** | [shallowCopy](#IEncodedVideoFrame-shallowcopy) |
| **virtual void** | [release](#IEncodedVideoFrame-release) |


## 函数说明
<span id="IEncodedVideoFrame-buildencodedvideoframe"></span>
### buildEncodedVideoFrame
```cpp
static IEncodedVideoFrame* bytertc::IEncodedVideoFrame::buildEncodedVideoFrame(
    const EncodedVideoFrameBuilder& builder)
```
根据视频帧参数创建视频帧并返回指针

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| builder | **const EncodedVideoFrameBuilder&** | 视频帧参数，参看 [EncodedVideoFrameBuilder](#encodedvideoframebuilder) |

**返回值**
IEncodedVideoFrame 创建的视频帧的指针


<span id="IEncodedVideoFrame-codectype"></span>
### codecType
```cpp
virtual VideoCodecType bytertc::IEncodedVideoFrame::codecType() const
```
获取视频编码类型

**返回值**
视频编码类型，参看 [VideoCodecType](#videocodectype)


<span id="IEncodedVideoFrame-timestampus"></span>
### timestampUs
```cpp
virtual int64_t bytertc::IEncodedVideoFrame::timestampUs() const
```
获取视频采集时间戳

**返回值**
视频采集时间戳，单位：微秒


<span id="IEncodedVideoFrame-timestampdtsus"></span>
### timestampDtsUs
```cpp
virtual int64_t bytertc::IEncodedVideoFrame::timestampDtsUs() const
```
获取视频编码时间戳

**返回值**
视频编码时间戳，单位：微秒


<span id="IEncodedVideoFrame-width"></span>
### width
```cpp
virtual int bytertc::IEncodedVideoFrame::width() const
```
获取视频帧宽度

**返回值**
视频帧宽度，单位：px


<span id="IEncodedVideoFrame-height"></span>
### height
```cpp
virtual int bytertc::IEncodedVideoFrame::height() const
```
获取视频帧高度

**返回值**
视频帧高度，单位：px


<span id="IEncodedVideoFrame-picturetype"></span>
### pictureType
```cpp
virtual VideoPictureType bytertc::IEncodedVideoFrame::pictureType() const
```
获取视频编码帧类型

**返回值**
视频编码帧类型，参看 [VideoPictureType](#videopicturetype)


<span id="IEncodedVideoFrame-rotation"></span>
### rotation
```cpp
virtual VideoRotation bytertc::IEncodedVideoFrame::rotation() const
```
获取视频帧旋转角度

**返回值**
视频帧旋转角度，参看 [VideoRotation](#videorotation)


<span id="IEncodedVideoFrame-data"></span>
### data
```cpp
virtual uint8_t* bytertc::IEncodedVideoFrame::data() const
```
获取视频帧数据指针地址

**返回值**
视频帧数据指针地址


<span id="IEncodedVideoFrame-datasize"></span>
### dataSize
```cpp
virtual int bytertc::IEncodedVideoFrame::dataSize() const
```
获取视频帧数据大小

**返回值**
视频帧数据大小


<span id="IEncodedVideoFrame-shallowcopy"></span>
### shallowCopy
```cpp
virtual IEncodedVideoFrame* bytertc::IEncodedVideoFrame::shallowCopy() const
```
浅拷贝视频帧并返回指针


<span id="IEncodedVideoFrame-release"></span>
### release
```cpp
virtual void bytertc::IEncodedVideoFrame::release()
```
释放视频帧


# P2PRole
```cpp
enum streamingrtc::P2PRole
```

串流引擎角色


`Defined in : streaming_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kP2PRoleClient | 0 | 客户端 |
| kP2PRoleServer | 1 | 服务端 |


# EngineConfig
```cpp
struct streamingrtc::EngineConfig
```

串流引擎配置 <br>
客户端和服务端的端口范围含义说明如下： <br>
服务端：引擎启动后开始监听端口 `server_port_min` 至 `server_port_max` 中的首个可用端口，等待客户端连接 <br>
客户端：引擎启动后开始不断尝试连接服务端，IP 地址为 `server_ip` ,端口号为 `server_port_min` 至 `server_port_max` <br>


`Defined in : streaming_common_defines.h`

## 成员变量

| 类型 | 名称 |
| --- | --- |
| **const char*** | [app_id](#EngineConfig-app_id) |
| **P2PRole** | [role](#EngineConfig-role) |
| **const char*** | [server_ip](#EngineConfig-server_ip) |
| **int** | [server_port_min](#EngineConfig-server_port_min) |
| **int** | [server_port_max](#EngineConfig-server_port_max) |


## 变量说明
<span id="EngineConfig-app_id"></span>
### app_id
```cpp
const char* streamingrtc::EngineConfig::app_id = nullptr;
```
每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。 <br>


<span id="EngineConfig-role"></span>
### role
```cpp
P2PRole streamingrtc::EngineConfig::role = kP2PRoleClient;
```
串流引擎角色, 参看 [P2PRole](#p2prole)


<span id="EngineConfig-server_ip"></span>
### server_ip
```cpp
const char* streamingrtc::EngineConfig::server_ip = nullptr;
```
服务端所在的 IP 地址，`role = kP2PRoleClient` 时需要设置


<span id="EngineConfig-server_port_min"></span>
### server_port_min
```cpp
int streamingrtc::EngineConfig::server_port_min = 50000;
```
最小端口号


<span id="EngineConfig-server_port_max"></span>
### server_port_max
```cpp
int streamingrtc::EngineConfig::server_port_max = 50004;
```
最大端口号



# StreamIndex
```cpp
enum streamingrtc::StreamIndex
```

流的序号，用于区分同一用户发出的多路流。例如 3D 视频流中的左/右眼。又如，屏幕流和摄像头采集流


`Defined in : streaming_common_defines.h`

### 枚举值

| 类型 | 值 | 说明 |
| --- | --- | --- |
| kStreamIndexIndex0 | 0 | 流序号 0 |
| kStreamIndexIndex1 | 1 | 流序号 1 |


# ConnectionStats
```cpp
typedef RtcRoomStats streamingrtc::ConnectionStats
```

参看 [RtcRoomStats](#rtcroomstats)。


`Defined in : streaming_rtc_engine_event_handler.h`