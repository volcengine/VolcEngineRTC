# AudioFormat
```java
public class com.ss.bytertc.engine.data.AudioFormat
```

音频参数格式


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **AudioSampleRate** | [sampleRate](#AudioFormat-samplerate) |
| **AudioChannel** | [channel](#AudioFormat-channel) |


## 变量说明
<span id="AudioFormat-samplerate"></span>
### sampleRate
```java
public AudioSampleRate com.ss.bytertc.engine.data.AudioFormat.sampleRate;
```
音频采样率，参看 [AudioSampleRate](#audiosamplerate)。


<span id="AudioFormat-channel"></span>
### channel
```java
public AudioChannel com.ss.bytertc.engine.data.AudioFormat.channel;
```
音频声道，参看 [AudioChannel](#audiochannel)。



# AudioMixingConfig
```java
public class com.ss.bytertc.engine.data.AudioMixingConfig
```

混音配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **AudioMixingType** | [type](#AudioMixingConfig-type) |
| **int** | [playCount](#AudioMixingConfig-playcount) |
| **int** | [position](#AudioMixingConfig-position) |
| **long** | [callbackOnProgressInterval](#AudioMixingConfig-callbackonprogressinterval) |


## 变量说明
<span id="AudioMixingConfig-type"></span>
### type
```java
public AudioMixingType com.ss.bytertc.engine.data.AudioMixingConfig.type;
```
混音播放类型，详见 [AudioMixingType](#audiomixingtype)


<span id="AudioMixingConfig-playcount"></span>
### playCount
```java
public int com.ss.bytertc.engine.data.AudioMixingConfig.playCount;
```
混音播放次数

+ play_count <= 0: 无限循环  <br>
+ play_count == 1: 播放一次（默认）  <br>
+ play_count > 1: 播放 play_count 次


<span id="AudioMixingConfig-position"></span>
### position
```java
public int com.ss.bytertc.engine.data.AudioMixingConfig.position;
```
混音时音频文件播放进度条位置，参数为整数，单位为毫秒


<span id="AudioMixingConfig-callbackonprogressinterval"></span>
### callbackOnProgressInterval
```java
public long com.ss.bytertc.engine.data.AudioMixingConfig.callbackOnProgressInterval;
```
设置音频文件播放进度回调的时间间隔，参数为大于 0 的 10 的倍数，单位为毫秒，设置后 SDK 将按照设置的值触发 `onAudioMixingPlayingProgress` 回调，默认不回调。  <br>

+ 当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。  <br>
+ 当传入的值小于等于 0 时，不会触发进度回调。  <br>



# AudioMixingDualMonoMode
```java
public enum com.ss.bytertc.engine.data.AudioMixingDualMonoMode
```

混音播放声道类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_MIXING_DUAL_MONO_MODE_AUTO(0)** | 和音频文件一致 |
| **AUDIO_MIXING_DUAL_MONO_MODE_L(1)** | 只能听到音频文件中左声道的音频 |
| **AUDIO_MIXING_DUAL_MONO_MODE_R(2)** | 只能听到音频文件中右声道的音频 |
| **AUDIO_MIXING_DUAL_MONO_MODE_MIX(3)** | 能同时听到音频文件中左右声道的音频 |


# AudioMixingError
```java
public enum com.ss.bytertc.engine.data.AudioMixingError
```

混音错误码。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_MIXING_ERROR_OK(0)** | 正常 |
| **AUDIO_MIXING_ERROR_PRELOAD_FAILED(1)** | 预加载失败。找不到混音文件或者文件长度超出 20s |
| **AUDIO_MIXING_ERROR_START_FAILED(2)** | 混音开启失败。找不到混音文件或者混音文件打开失败 |
| **AUDIO_MIXING_ERROR_ID_NOT_FOUND(3)** | 混音 ID 异常 |
| **AUDIO_MIXING_ERROR_SET_POSITION_FAILED(4)** | 设置混音文件的播放位置出错 |
| **AUDIO_MIXING_ERROR_INVALID_VOLUME(5)** | 音量参数不合法，仅支持设置的音量值为[0, 400] |
| **AUDIO_MIXING_ERROR_LOAD_CONFLICT(6)** | 播放的文件与预加载的文件不一致。请先使用 [unloadAudioMixing](Android-api.md#IAudioMixingManager-unloadaudiomixing) 卸载此前的文件。 |
| **AUDIO_MIXING_ERROR_ID_TYPE_NOT_MATCH(7)** | 不支持此混音类型。 |
| **AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH(8)** | 设置混音文件的音调不合法 |
| **AUDIO_MIXING_ERROR_INVALID_AUDIO_TRACK(9)** | 设置混音文件的音轨不合法 |
| **AUDIO_MIXING_ERROR_IS_STARTING(10)** | 混音文件正在启动中 |
| **AUDIO_MIXING_ERROR_INVALID_PLAYBACK_SPEED(11)** | 设置混音文件的播放速度不合法 |


# AudioMixingState
```java
public enum com.ss.bytertc.engine.data.AudioMixingState
```

音频混音文件播放状态。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_MIXING_STATE_PRELOADED(0)** | 混音已加载 |
| **AUDIO_MIXING_STATE_PLAYING(1)** | 混音正在播放 |
| **AUDIO_MIXING_STATE_PAUSED(2)** | 混音暂停 |
| **AUDIO_MIXING_STATE_STOPPED(3)** | 混音停止 |
| **AUDIO_MIXING_STATE_FAILED(4)** | 混音播放失败 |
| **AUDIO_MIXING_STATE_FINISHED(5)** | 混音播放结束 |
| **AUDIO_MIXING_STATE_PCM_ENABLED(6)** | 准备PCM混音 |
| **AUDIO_MIXING_STATE_PCM_DISABLED(7)** | PCM混音播放结束 |


# AudioMixingType
```java
public enum com.ss.bytertc.engine.data.AudioMixingType
```

混音播放类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_MIXING_TYPE_PLAYOUT(0)** | 仅本地播放 |
| **AUDIO_MIXING_TYPE_PUBLISH(1)** | 仅远端播放 |
| **AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH(2)** | 本地和远端同时播放 |


# AudioPlaybackDevice
```java
public enum com.ss.bytertc.engine.data.AudioPlaybackDevice
```

音频播放设备  <br>
音频设备变化时 SDK 通过 `onAudioPlaybackDeviceChanged` 回调当前音频播放设备。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_PLAYBACK_DEVICE_HEADSET(1)** | 有线耳机 |
| **AUDIO_PLAYBACK_DEVICE_EARPIECE(2)** | 听筒 |
| **AUDIO_PLAYBACK_DEVICE_SPEAKERPHONE(3)** | 扬声器 |
| **AUDIO_PLAYBACK_DEVICE_HEADSET_BLUETOOTH(4)** | 蓝牙耳机 |
| **AUDIO_PLAYBACK_DEVICE_HEADSET_USB(5)** | USB设备 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [value](#AudioPlaybackDevice-value) |


## 函数说明
<span id="AudioPlaybackDevice-value"></span>
### value
```java
public int com.ss.bytertc.engine.data.AudioPlaybackDevice.value()
```
获取当前值

**返回值**
当前值


# AudioProcessorMethod
```java
public enum com.ss.bytertc.engine.data.AudioProcessorMethod
```

返回给音频处理器的音频类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_FRAME_PROCESSOR_RECORD(0)** | 本地采集的音频。 |
| **AUDIO_FRAME_PROCESSOR_PLAYBACK(1)** | 远端音频流的混音音频。 |
| **AUDIO_FRAME_PROCESSOR_REMOTE_USER(2)** | 各个远端音频流。 |
| **AUDIO_FRAME_PROCESSOR_EAR_MONITOR(3)** | 软件耳返音频。 |
| **AUDIO_FRAME_PROCESSOR_SCREEN(4)** | 屏幕共享音频。 |


# AudioPropertiesConfig
```java
public class com.ss.bytertc.engine.data.AudioPropertiesConfig
```

音频属性信息提示的相关配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [interval](#AudioPropertiesConfig-interval) |
| **boolean** | [enable_spectrum](#AudioPropertiesConfig-enable_spectrum) |
| **boolean** | [enable_vad](#AudioPropertiesConfig-enable_vad) |
| **AudioReportMode** | [local_main_report_mode](#AudioPropertiesConfig-local_main_report_mode) |
| **AudioPropertiesMode** | [audio_report_mode](#AudioPropertiesConfig-audio_report_mode) |


## 变量说明
<span id="AudioPropertiesConfig-interval"></span>
### interval
```java
public int com.ss.bytertc.engine.data.AudioPropertiesConfig.interval;
```
信息提示间隔，单位：ms <br>

+ `<= 0`: 关闭信息提示  <br>
+ `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
+ `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>


<span id="AudioPropertiesConfig-enable_spectrum"></span>
### enable_spectrum
```java
public boolean com.ss.bytertc.engine.data.AudioPropertiesConfig.enable_spectrum = false;
```
是否开启音频频谱检测


<span id="AudioPropertiesConfig-enable_vad"></span>
### enable_vad
```java
public boolean com.ss.bytertc.engine.data.AudioPropertiesConfig.enable_vad = false;
```
是否开启人声检测 (VAD)


<span id="AudioPropertiesConfig-local_main_report_mode"></span>
### local_main_report_mode
```java
public AudioReportMode com.ss.bytertc.engine.data.AudioPropertiesConfig.local_main_report_mode = AudioReportMode.AUDIO_REPORT_MODE_NORMAL;
```
音量回调模式。详见 [AudioReportMode](#audioreportmode)。


<span id="AudioPropertiesConfig-audio_report_mode"></span>
### audio_report_mode
```java
public AudioPropertiesMode com.ss.bytertc.engine.data.AudioPropertiesConfig.audio_report_mode = AudioPropertiesMode.AUDIO_PROPERTIES_MODE_MIC/;"
```
设置 `onLocalAudioPropertiesReport` 回调是否包含本地混音音频数据。参看 [AudioPropertiesMode](#audiopropertiesmode)。<br>
默认仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。



# AudioPropertiesInfo
```java
public class com.ss.bytertc.engine.data.AudioPropertiesInfo
```

音频属性信息  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [linearVolume](#AudioPropertiesInfo-linearvolume) |
| **int** | [nonlinearVolume](#AudioPropertiesInfo-nonlinearvolume) |
| **float[]** | [spectrum](#AudioPropertiesInfo-spectrum) |
| **int** | [vad](#AudioPropertiesInfo-vad) |


## 变量说明
<span id="AudioPropertiesInfo-linearvolume"></span>
### linearVolume
```java
public int com.ss.bytertc.engine.data.AudioPropertiesInfo.linearVolume;
```
线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。<br>

- [0, 25]: 无声 <br>
- [26, 75]: 低音量 <br>
- [76, 204]: 中音量 <br>
- [205, 255]: 高音量 <br>


<span id="AudioPropertiesInfo-nonlinearvolume"></span>
### nonlinearVolume
```java
public int com.ss.bytertc.engine.data.AudioPropertiesInfo.nonlinearVolume;
```
非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。 <br>

- [-127, -60]: 无声 <br>
- [-59, -40]: 低音量 <br>
- [-39, -20]: 中音量 <br>
- [-19, 0]: 高音量 <br>


<span id="AudioPropertiesInfo-spectrum"></span>
### spectrum
```java
public float[] com.ss.bytertc.engine.data.AudioPropertiesInfo.spectrum = new float[SPECTRUM_SIZE];
```
频谱数组


<span id="AudioPropertiesInfo-vad"></span>
### vad
```java
public int com.ss.bytertc.engine.data.AudioPropertiesInfo.vad;
```
人声检测（VAD）结果

- 1: 检测到人声。<br>
- 0: 未检测到人声。<br>
- -1: 未开启 VAD。



# AudioPropertiesMode
```java
public enum com.ss.bytertc.engine.data.AudioPropertiesMode
```

音频信息提示中是否包含本地混音音频数据。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_PROPERTIES_MODE_MICROPHONE(0)** | 音频信息提示中，仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。 |
| **AUDIO_PROPERTIES_MODE_AUDIOMIXING(1)** | 音频信息提示中，除本地麦克风采集的音频数据和本地屏幕音频采集数据外，还包含本地混音的音频数据。 |


# AudioRenderType
```java
public enum com.ss.bytertc.engine.data.AudioRenderType
```

音频输出源类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_RENDER_TYPE_EXTERNAL(0)** | 自定义渲染 |
| **AUDIO_RENDER_TYPE_INTERNAL(1)** | 内部渲染 |


# AudioReportMode
```java
public enum com.ss.bytertc.engine.data.AudioReportMode
```

音量回调模式。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_REPORT_MODE_NORMAL(0)** | 默认始终开启音量回调。 |
| **AUDIO_REPORT_MODE_DISCONNECT(1)** | 可见用户进房并停止推流后，关闭音量回调。 |
| **AUDIO_REPORT_MODE_RESET(2)** | 可见用户进房并停止推流后，开启音量回调，回调值重置为0。 |


# AudioRoute
```java
public enum com.ss.bytertc.engine.data.AudioRoute
```

音频播放路由


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_ROUTE_UNKNOWN(-1)** | 未知设备 |
| **AUDIO_ROUTE_HEADSET(1)** | 有线耳机 |
| **AUDIO_ROUTE_EARPIECE(2)** | 听筒。设备自带的，一般用于通话的播放硬件。 |
| **AUDIO_ROUTE_SPEAKERPHONE(3)** | 扬声器。设备自带的，一般用于免提播放的硬件。 |
| **AUDIO_ROUTE_HEADSET_BLUETOOTH(4)** | 蓝牙耳机 |
| **AUDIO_ROUTE_HEADSET_USB(5)** | USB 设备 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [value](#AudioRoute-value) |


## 函数说明
<span id="AudioRoute-value"></span>
### value
```java
public int com.ss.bytertc.engine.data.AudioRoute.value()
```
获取当前值

**返回值**
当前值


# AudioSourceType
```java
public enum com.ss.bytertc.engine.data.AudioSourceType
```

音频输入源类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_SOURCE_TYPE_EXTERNAL(0)** | 自定义采集音频源 |
| **AUDIO_SOURCE_TYPE_INTERNAL(1)** | RTC SDK 内部采集音频源 |


# AVSyncState
```java
public enum com.ss.bytertc.engine.data.AVSyncState
```

音视频同步状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AV_SYNC_STATE_STREAM_SYNC_BEGIN(0)** | 音视频开始同步 |
| **AV_SYNC_STATE_AUDIO_STREAM_REMOVE(1)** | 音视频同步过程中音频移除，但不影响当前的同步关系 |
| **AV_SYNC_STATE_VIDEO_STREAM_REMOVE(2)** | 音视频同步过程中视频移除，但不影响当前的同步关系 |


# CameraId
```java
public enum com.ss.bytertc.engine.data.CameraId
```

摄像头类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **CAMERA_ID_FRONT (0)** | 前置摄像头 |
| **CAMERA_ID_BACK (1)** | 后置摄像头（默认设置） |
| **CAMERA_ID_EXTERNAL (2)** | 外接摄像头 |
| **CAMERA_ID_INVALID (3)** | 无效值 |


# CloudProxyInfo
```java
public class com.ss.bytertc.engine.data.CloudProxyInfo
```

云代理信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [cloudProxyIp](#CloudProxyInfo-cloudproxyip) |
| **int** | [cloudProxyPort](#CloudProxyInfo-cloudproxyport) |


## 变量说明
<span id="CloudProxyInfo-cloudproxyip"></span>
### cloudProxyIp
```java
public String com.ss.bytertc.engine.data.CloudProxyInfo.cloudProxyIp;
```
云代理服务器 IP


<span id="CloudProxyInfo-cloudproxyport"></span>
### cloudProxyPort
```java
public int com.ss.bytertc.engine.data.CloudProxyInfo.cloudProxyPort;
```
云代理服务器端口



# ColorSpace
```java
public enum com.ss.bytertc.engine.data.ColorSpace
```

视频帧色彩空间


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kColorSpaceUnknown(0)** | 色彩空间未知 |
| **kColorSpaceYCbCrBT601LimitedRange(1)** | BT.601数字编码标准，色彩空间[16-235] |
| **kColorSpaceYCbCrBT601FullRange(2)** | BT.601数字编码标准，颜色空间[0-255] |
| **kColorSpaceYCbCrBT709LimitedRange(3)** | BT.7091数字编码标准，颜色空间[16-235] |
| **kColorSpaceYCbCrBT709FullRange(4)** | BT.7091数字编码标准，颜色空间[0-255] |


# EarMonitorMode
```java
public enum com.ss.bytertc.engine.data.EarMonitorMode
```

是否开启耳返功能。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **EAR_MONITOR_MODE_OFF(0)** | 关闭（默认设置） |
| **EAR_MONITOR_MODE_ON(1)** | 开启 |


# EffectBeautyMode
```java
public enum com.ss.bytertc.engine.data.EffectBeautyMode
```

基础美颜模式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **EFFECT_WHITE_MODE(0)** | 美白 |
| **EFFECT_SMOOTH_MODE(1)** | 磨皮 |
| **EFFECT_SHARPEN_MODE(2)** | 锐化 |


# ForwardStreamEventInfo
```java
public class com.ss.bytertc.engine.data.ForwardStreamEventInfo
```

跨房间转发媒体流过程中的不同目标房间发生的事件


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [roomId](#ForwardStreamEventInfo-roomid) |
| **ForwardStreamEvent** | [event](#ForwardStreamEventInfo-event) |


## 变量说明
<span id="ForwardStreamEventInfo-roomid"></span>
### roomId
```java
public String com.ss.bytertc.engine.data.ForwardStreamEventInfo.roomId;
```
跨房间转发媒体流过程中的发生该事件的目标房间 ID<br>
空字符串代表所有目标房间


<span id="ForwardStreamEventInfo-event"></span>
### event
```java
public ForwardStreamEvent com.ss.bytertc.engine.data.ForwardStreamEventInfo.event;
```
跨房间转发媒体流过程中该目标房间发生的事件，参看 [ForwardStreamEvent](#forwardstreamevent)。



# ForwardStreamEvent
```java
public enum com.ss.bytertc.engine.data.ForwardStreamEventInfo.ForwardStreamEvent
```

跨房间转发媒体流过程中该目标房间发生的事件


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **FORWARD_STREAM_EVENT_DISCONNECTED(0)** | 本端与服务器网络连接断开，暂停转发。 |
| **FORWARD_STREAM_EVENT_CONNECTED(1)** | 本端与服务器网络连接恢复，转发服务连接成功。 |
| **FORWARD_STREAM_EVENT_INTERRUPT(2)** | 转发中断。转发过程中，如果相同 user_id 的用户进入目标房间，转发中断。 |
| **FORWARD_STREAM_EVENT_DST_ROOM_UPDATED(3)** | 目标房间已更新，由 [updateForwardStreamToRooms](Android-api.md#RTCRoom-updateforwardstreamtorooms) 触发。 |
| **FORWARD_STREAM_EVENT_UN_EXPECT_API_CALL(4)** | API 调用时序错误。例如，在调用 [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) 之前调用 [updateForwardStreamToRooms](Android-api.md#RTCRoom-updateforwardstreamtorooms) 。 |


# ForwardStreamInfo
```java
public class com.ss.bytertc.engine.data.ForwardStreamInfo
```

媒体流跨房间转发的目标房间的相关信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [roomId](#ForwardStreamInfo-roomid) |
| **String** | [token](#ForwardStreamInfo-token) |


## 变量说明
<span id="ForwardStreamInfo-roomid"></span>
### roomId
```java
public String com.ss.bytertc.engine.data.ForwardStreamInfo.roomId;
```
跨房间转发媒体流过程中目标房间 ID<br>


<span id="ForwardStreamInfo-token"></span>
### token
```java
public String com.ss.bytertc.engine.data.ForwardStreamInfo.token;
```
使用转发目标房间 RoomID 和 UserID 生成的 Token。<br>
测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。<br>
如果 Token 无效，转发失败。



# ForwardStreamStateInfo
```java
public class com.ss.bytertc.engine.data.ForwardStreamStateInfo
```

跨房间转发媒体流过程中的不同目标房间的状态和错误信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [roomId](#ForwardStreamStateInfo-roomid) |
| **ForwardStreamState** | [state](#ForwardStreamStateInfo-state) |
| **ForwardStreamError** | [error](#ForwardStreamStateInfo-error) |


## 变量说明
<span id="ForwardStreamStateInfo-roomid"></span>
### roomId
```java
public String com.ss.bytertc.engine.data.ForwardStreamStateInfo.roomId;
```
跨房间转发媒体流过程中目标房间 ID<br>
空字符串代表所有目标房间


<span id="ForwardStreamStateInfo-state"></span>
### state
```java
public ForwardStreamState com.ss.bytertc.engine.data.ForwardStreamStateInfo.state;
```
跨房间转发媒体流过程中该目标房间的状态，参看 [ForwardStreamState](#forwardstreamstate)


<span id="ForwardStreamStateInfo-error"></span>
### error
```java
public ForwardStreamError com.ss.bytertc.engine.data.ForwardStreamStateInfo.error;
```
跨房间转发媒体流过程中该目标房间抛出的错误码，参看 [ForwardStreamError](#forwardstreamerror)



# ForwardStreamState
```java
public enum com.ss.bytertc.engine.data.ForwardStreamStateInfo.ForwardStreamState
```

媒体流跨房间转发状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **FORWARD_STREAM_STATE_IDLE(0)** | 空闲状态<br/>+ 成功调用 [stopForwardStreamToRooms](Android-api.md#RTCRoom-stopforwardstreamtorooms) 后，所有目标房间为空闲状态。<br/>+ 成功调用 [updateForwardStreamToRooms](Android-api.md#RTCRoom-updateforwardstreamtorooms) 减少目标房间后，本次减少的目标房间为空闲状态。 |
| **FORWARD_STREAM_STATE_SUCCESS(1)** | 开始转发<br/>+ 调用 [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) 成功向所有房间开始转发媒体流后，返回此状态。<br/>+ 调用 [updateForwardStreamToRooms](Android-api.md#RTCRoom-updateforwardstreamtorooms) 后，成功向新增目标房间开始转发媒体流后，返回此状态。 |
| **FORWARD_STREAM_STATE_FAILURE(2)** | 转发失败，失败详情参考 ForwardStreamError[forwardStreamError](#forwardstreamerror)<br/>调用 [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) 或 [updateForwardStreamToRooms](Android-api.md#RTCRoom-updateforwardstreamtorooms) 后，如遇转发失败，返回此状态。 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [value](#ForwardStreamState-value) |


## 函数说明
<span id="ForwardStreamState-value"></span>
### value
```java
public int com.ss.bytertc.engine.data.ForwardStreamStateInfo.ForwardStreamState.value()
```
获取当前值


# ForwardStreamError
```java
public enum com.ss.bytertc.engine.data.ForwardStreamStateInfo.ForwardStreamError
```

媒体流跨房间转发过程中抛出的错误码


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **FORWARD_STREAM_ERROR_OK(0)** | 正常 |
| **FORWARD_STREAM_ERROR_INVALID_ARGUMENT(1201)** | 参数异常 |
| **FORWARD_STREAM_ERROR_INVALID_TOKEN(1202)** | token 错误 |
| **FORWARD_STREAM_ERROR_RESPONSE(1203)** | 服务端异常 |
| **FORWARD_STREAM_ERROR_REMOTE_KICKED(1204)** | 目标房间有相同 user id 的用户加入，转发中断 |
| **FORWARD_STREAM_ERROR_NOT_SUPPORT(1205)** | 服务端不支持转发功能 |


# HumanOrientation
```java
public class com.ss.bytertc.engine.data.HumanOrientation
```

三维朝向信息，三个向量需要两两垂直。参看 [Orientation](#orientation)。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **Orientation** | [forward](#HumanOrientation-forward) |
| **Orientation** | [right](#HumanOrientation-right) |
| **Orientation** | [up](#HumanOrientation-up) |


## 变量说明
<span id="HumanOrientation-forward"></span>
### forward
```java
public Orientation com.ss.bytertc.engine.data.HumanOrientation.forward;
```
正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向


<span id="HumanOrientation-right"></span>
### right
```java
public Orientation com.ss.bytertc.engine.data.HumanOrientation.right;
```
正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向


<span id="HumanOrientation-up"></span>
### up
```java
public Orientation com.ss.bytertc.engine.data.HumanOrientation.up;
```
正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向



# LocalAudioPropertiesInfo
```java
public class com.ss.bytertc.engine.data.LocalAudioPropertiesInfo
```

本地音频属性信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **StreamIndex** | [streamIndex](#LocalAudioPropertiesInfo-streamindex) |
| **AudioPropertiesInfo** | [audioPropertiesInfo](#LocalAudioPropertiesInfo-audiopropertiesinfo) |


## 变量说明
<span id="LocalAudioPropertiesInfo-streamindex"></span>
### streamIndex
```java
public StreamIndex com.ss.bytertc.engine.data.LocalAudioPropertiesInfo.streamIndex;
```
流属性，主流或屏幕流。参看 [StreamIndex](#streamindex-2)


<span id="LocalAudioPropertiesInfo-audiopropertiesinfo"></span>
### audioPropertiesInfo
```java
public AudioPropertiesInfo com.ss.bytertc.engine.data.LocalAudioPropertiesInfo.audioPropertiesInfo;
```
音频属性信息，详见 [AudioPropertiesInfo](#audiopropertiesinfo)。



# MediaInputType
```java
public enum com.ss.bytertc.engine.data.MediaInputType
```

视频输入类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **MEDIA_INPUT_TYPE_EXTERNAL(0)** | 自定义采集。  <br><br/>设置完成后方可直接向 SDK 推送视频帧。 |
| **MEDIA_INPUT_TYPE_INTERNAL(1)** | 内部 SDK 采集。  <br><br/>此设置仅切换至内部采集，你需继续调用 [startVideoCapture](Android-api.md#RTCVideo-startvideocapture) 开启内部采集。 |


# MirrorType
```java
public enum com.ss.bytertc.engine.data.MirrorType
```

镜像类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **MIRROR_TYPE_NONE(0)** | 本地预览和编码传输时均无镜像效果 |
| **MIRROR_TYPE_RENDER(1)** | 本地预览时有镜像效果，编码传输时无镜像效果 |
| **MIRROR_TYPE_RENDER_AND_ENCODER(3)** | 本地预览和编码传输时均有镜像效果 |


# MulDimSingScoringMode
```java
public enum com.ss.bytertc.engine.data.MulDimSingScoringMode
```

K 歌打分维度。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **MUL_DIM_SING_SCORING_MODE_NOTE(0)** | 按照音高进行评分。 |


# MuteState
```java
public enum com.ss.bytertc.engine.data.MuteState
```

音视频流的发送/播放状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **MUTE_STATE_OFF(0)** | 发送 |
| **MUTE_STATE_ON(1)** | 停止发送 |


# Orientation
```java
public class com.ss.bytertc.engine.data.Orientation
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
```java
public float com.ss.bytertc.engine.data.Orientation.x;
```
x 坐标


<span id="Orientation-y"></span>
### y
```java
public float com.ss.bytertc.engine.data.Orientation.y;
```
y 坐标


<span id="Orientation-z"></span>
### z
```java
public float com.ss.bytertc.engine.data.Orientation.z;
```
z 坐标



# Position
```java
public class com.ss.bytertc.engine.data.Position
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
```java
public int com.ss.bytertc.engine.data.Position.x;
```
x 坐标


<span id="Position-y"></span>
### y
```java
public int com.ss.bytertc.engine.data.Position.y;
```
y 坐标


<span id="Position-z"></span>
### z
```java
public int com.ss.bytertc.engine.data.Position.z;
```
z 坐标



# ReceiveRange
```java
public class com.ss.bytertc.engine.data.ReceiveRange
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
```java
public int com.ss.bytertc.engine.data.ReceiveRange.min;
```
能够接收语音、并且具有衰减效果的最小距离值，该值须 ≥ 0，但 ≤ max。  <br>
小于该值的范围内没有范围语音效果，即收听到的音频音量相同。


<span id="ReceiveRange-max"></span>
### max
```java
public int com.ss.bytertc.engine.data.ReceiveRange.max;
```
能够收听语音的最大距离值，该值须 > 0 且 ≥ min。  <br>
当收听者和声源距离处于 [min, max) 之间时，收听到的音量根据距离呈衰减效果。  <br>
超出该值范围的音频将无法收听到。



# RemoteAudioPropertiesInfo
```java
public class com.ss.bytertc.engine.data.RemoteAudioPropertiesInfo
```

远端音频属性信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **RemoteStreamKey** | [streamKey](#RemoteAudioPropertiesInfo-streamkey) |
| **AudioPropertiesInfo** | [audioPropertiesInfo](#RemoteAudioPropertiesInfo-audiopropertiesinfo) |


## 变量说明
<span id="RemoteAudioPropertiesInfo-streamkey"></span>
### streamKey
```java
public RemoteStreamKey com.ss.bytertc.engine.data.RemoteAudioPropertiesInfo.streamKey;
```
远端流信息，详见 [RemoteStreamKey](#remotestreamkey)


<span id="RemoteAudioPropertiesInfo-audiopropertiesinfo"></span>
### audioPropertiesInfo
```java
public AudioPropertiesInfo com.ss.bytertc.engine.data.RemoteAudioPropertiesInfo.audioPropertiesInfo;
```
音频属性信息，详见 [AudioPropertiesInfo](#audiopropertiesinfo)



# ScreenMediaType
```java
public enum com.ss.bytertc.engine.data.ScreenMediaType
```

屏幕采集媒体类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **SCREEN_MEDIA_TYPE_VIDEO_ONLY(0)** | 仅采集视频 |
| **SCREEN_MEDIA_TYPE_AUDIO_ONLY(1)** | 仅采集音频 |
| **SCREEN_MEDIA_TYPE_VIDEO_AND_AUDIO(2)** | 采集音频和视频 |


# SingScoringConfig
```java
public class com.ss.bytertc.engine.data.SingScoringConfig
```

K 歌评分配置。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **AudioSampleRate** | [sampleRate](#SingScoringConfig-samplerate) |
| **MulDimSingScoringMode** | [mode](#SingScoringConfig-mode) |
| **String** | [lyricsFilepath](#SingScoringConfig-lyricsfilepath) |
| **String** | [midiFilepath](#SingScoringConfig-midifilepath) |


## 变量说明
<span id="SingScoringConfig-samplerate"></span>
### sampleRate
```java
public AudioSampleRate com.ss.bytertc.engine.data.SingScoringConfig.sampleRate;
```
音频采样率。仅支持 44100 Hz、48000 Hz。


<span id="SingScoringConfig-mode"></span>
### mode
```java
public MulDimSingScoringMode com.ss.bytertc.engine.data.SingScoringConfig.mode;
```
打分维度，详见 [MulDimSingScoringMode](#muldimsingscoringmode)。


<span id="SingScoringConfig-lyricsfilepath"></span>
### lyricsFilepath
```java
public String com.ss.bytertc.engine.data.SingScoringConfig.lyricsFilepath;
```
歌词文件路径。打分功能仅支持 KRC 歌词文件。


<span id="SingScoringConfig-midifilepath"></span>
### midiFilepath
```java
public String com.ss.bytertc.engine.data.SingScoringConfig.midiFilepath;
```
歌曲 midi 文件路径。



# SingScoringRealtimeInfo
```java
public class com.ss.bytertc.engine.data.SingScoringRealtimeInfo
```

实时评分信息。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [currentPosition](#SingScoringRealtimeInfo-currentposition) |
| **int** | [userPitch](#SingScoringRealtimeInfo-userpitch) |
| **int** | [standardPitch](#SingScoringRealtimeInfo-standardpitch) |
| **int** | [sentenceIndex](#SingScoringRealtimeInfo-sentenceindex) |
| **int** | [sentenceScore](#SingScoringRealtimeInfo-sentencescore) |
| **int** | [totalScore](#SingScoringRealtimeInfo-totalscore) |
| **int** | [averageScore](#SingScoringRealtimeInfo-averagescore) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **String** | [toString](#SingScoringRealtimeInfo-tostring) |


## 变量说明
<span id="SingScoringRealtimeInfo-currentposition"></span>
### currentPosition
```java
public int com.ss.bytertc.engine.data.SingScoringRealtimeInfo.currentPosition;
```
当前播放进度。


<span id="SingScoringRealtimeInfo-userpitch"></span>
### userPitch
```java
public int com.ss.bytertc.engine.data.SingScoringRealtimeInfo.userPitch;
```
演唱者的音高。


<span id="SingScoringRealtimeInfo-standardpitch"></span>
### standardPitch
```java
public int com.ss.bytertc.engine.data.SingScoringRealtimeInfo.standardPitch;
```
标准音高。


<span id="SingScoringRealtimeInfo-sentenceindex"></span>
### sentenceIndex
```java
public int com.ss.bytertc.engine.data.SingScoringRealtimeInfo.sentenceIndex;
```
歌词分句索引。


<span id="SingScoringRealtimeInfo-sentencescore"></span>
### sentenceScore
```java
public int com.ss.bytertc.engine.data.SingScoringRealtimeInfo.sentenceScore;
```
上一句歌词的评分。


<span id="SingScoringRealtimeInfo-totalscore"></span>
### totalScore
```java
public int com.ss.bytertc.engine.data.SingScoringRealtimeInfo.totalScore;
```
当前演唱的累计分数。


<span id="SingScoringRealtimeInfo-averagescore"></span>
### averageScore
```java
public int com.ss.bytertc.engine.data.SingScoringRealtimeInfo.averageScore;
```
当前演唱的平均分数。



## 函数说明
<span id="SingScoringRealtimeInfo-tostring"></span>
### toString
```java
public String com.ss.bytertc.engine.data.SingScoringRealtimeInfo.toString()
```

# StandardPitchInfo
```java
public class com.ss.bytertc.engine.data.StandardPitchInfo
```

标准音高数据数组。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [startTime](#StandardPitchInfo-starttime) |
| **int** | [duration](#StandardPitchInfo-duration) |
| **int** | [pitch](#StandardPitchInfo-pitch) |


## 变量说明
<span id="StandardPitchInfo-starttime"></span>
### startTime
```java
public int com.ss.bytertc.engine.data.StandardPitchInfo.startTime;
```
开始时间，单位 ms。


<span id="StandardPitchInfo-duration"></span>
### duration
```java
public int com.ss.bytertc.engine.data.StandardPitchInfo.duration;
```
持续时间，单位 ms。


<span id="StandardPitchInfo-pitch"></span>
### pitch
```java
public int com.ss.bytertc.engine.data.StandardPitchInfo.pitch;
```
音高。



# StreamIndex
```java
public enum com.ss.bytertc.engine.data.StreamIndex
```

流属性


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **STREAM_INDEX_MAIN(0)** | <br><br/>主流。包括：<br><br/>+ 由摄像头/麦克风通过内部采集机制，采集到的视频/音频; <br><br/>+ 通过自定义采集，采集到的视频/音频。 |
| **STREAM_INDEX_SCREEN(1)** | 屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。 |


# StreamSycnInfoConfig
```java
public class com.ss.bytertc.engine.data.StreamSycnInfoConfig
```

媒体流信息同步的相关配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **StreamIndex** | [streamIndex](#StreamSycnInfoConfig-streamindex) |
| **int** | [repeatCount](#StreamSycnInfoConfig-repeatcount) |
| **SyncInfoStreamType** | [streamType](#StreamSycnInfoConfig-streamtype) |


## 变量说明
<span id="StreamSycnInfoConfig-streamindex"></span>
### streamIndex
```java
public StreamIndex com.ss.bytertc.engine.data.StreamSycnInfoConfig.streamIndex;
```
流属性，主流或屏幕流。见枚举类 [StreamIndex](#streamindex-2)<br>

+ `STREAM_INDEX_MAIN(0)`: 主流
+ `STREAM_INDEX_SCREEN(1)`: 屏幕流


<span id="StreamSycnInfoConfig-repeatcount"></span>
### repeatCount
```java
public int com.ss.bytertc.engine.data.StreamSycnInfoConfig.repeatCount;
```
信息发送的重复次数。取值范围是 [0,25]，建议设置为 [3,5]


<span id="StreamSycnInfoConfig-streamtype"></span>
### streamType
```java
public SyncInfoStreamType com.ss.bytertc.engine.data.StreamSycnInfoConfig.streamType;
```
媒体流信息同步的流类型，见 [SyncInfoStreamType](#syncinfostreamtype)



# SyncInfoStreamType
```java
public enum com.ss.bytertc.engine.data.StreamSycnInfoConfig.SyncInfoStreamType
```

媒体流信息同步的流类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **SYNC_INFO_STREAM_TYPE_AUDIO** | 音频流 |


# VideoContentType
```java
public enum com.ss.bytertc.engine.data.VideoContentType
```

视频内容类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kVideoContentTypeNormalFrame(0)** | 普通视频 |
| **kVideoContentTypeBlackFrame(1)** | 黑帧视频 |


# VideoFrameType
```java
public enum com.ss.bytertc.engine.data.VideoFrameType
```

视频帧的类型，用于标识视频帧是 CPUBuffer 还是 TextureBuffer


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kVideoFrameTypeRawMemory(0)** | CPU Buffer |
| **kVideoFrameTypeGLTexture(2)** | GL Texture |


# VideoOrientation
```java
public enum com.ss.bytertc.engine.data.VideoOrientation
```

视频帧朝向


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **Adaptive(0)** | （默认）使用相机输出的原始视频帧的角度，不对视频帧进行额外旋转。 |
| **Portrait(1)** | 固定为竖屏，将相机采集到的视频帧转换为竖屏，在整个 RTC 链路中传递竖屏帧。 |
| **Landscape(2)** | 固定为横屏，将相机采集到的视频帧转换为横屏，在整个 RTC 链路中传递横屏帧。 |


# VideoPixelFormat
```java
public enum com.ss.bytertc.engine.data.VideoPixelFormat
```

视频帧的数据格式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kVideoPixelFormatUnknown(0)** | 未知格式 |
| **kVideoPixelFormatI420(1)** | I420格式 |
| **kVideoPixelFormatNV12(2)** | NV12格式 |
| **kVideoPixelFormatNV21(3)** | NV21格式 |
| **kVideoPixelFormatRGBA(5)** | RGBA格式 |
| **kVideoPixelFormatTexture2D(GLES10.GL_TEXTURE_2D)** | Texture2D格式 |
| **kVideoPixelFormatTextureOES(GLES11Ext.GL_TEXTURE_EXTERNAL_OES)** | TextureOES格式 |


# VideoRotationMode
```java
public enum com.ss.bytertc.engine.data.VideoRotationMode
```

视频旋转模式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **FollowApp(0)** | App 方向 |
| **FollowGSensor(1)** | 重力方向 |


# VirtualBackgroundSource
```java
public class com.ss.bytertc.engine.data.VirtualBackgroundSource
```

背景贴纸对象。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **VirtualBackgroundSourceType** | [sourceType](#VirtualBackgroundSource-sourcetype) |
| **int** | [sourceColor](#VirtualBackgroundSource-sourcecolor) |
| **String** | [sourcePath](#VirtualBackgroundSource-sourcepath) |


## 变量说明
<span id="VirtualBackgroundSource-sourcetype"></span>
### sourceType
```java
public VirtualBackgroundSourceType com.ss.bytertc.engine.data.VirtualBackgroundSource.sourceType;
```
虚拟背景类型，详见 [VirtualBackgroundSourceType](#virtualbackgroundsourcetype) 。


<span id="VirtualBackgroundSource-sourcecolor"></span>
### sourceColor
```java
public int com.ss.bytertc.engine.data.VirtualBackgroundSource.sourceColor;
```
纯色背景使用的颜色。<br>
格式为 0xAARRGGBB 。


<span id="VirtualBackgroundSource-sourcepath"></span>
### sourcePath
```java
public String com.ss.bytertc.engine.data.VirtualBackgroundSource.sourcePath;
```
自定义背景图片的绝对路径。

+ 支持本地文件绝对路径 (file://xxx) 和 Asset 资源路径 (asset://xxx)。  <br>
+ 支持的格式为 jpg、jpeg、png。  <br>
+ 图片分辨率超过 1080P 时，图片会被等比缩放至和视频一致。  <br>
+ 图片和视频宽高比一致时，图片会被直接缩放至和视频一致。  <br>
+ 图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。  <br>
+ 自定义图片带有局部透明效果时，透明部分由黑色代替。



# VirtualBackgroundSourceType
```java
public enum com.ss.bytertc.engine.data.VirtualBackgroundSourceType
```

虚拟背景类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **SourceTypeColor** | 使用纯色背景替换视频原有背景。 |
| **SourceTypeImage** | 使用自定义图片背景替换视频原有背景。 |


# IRTCASREngineEventHandler
```java
public interface com.ss.bytertc.engine.handler.IRTCASREngineEventHandler
```

语音识别服务使用状态回调


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onSuccess](#IRTCASREngineEventHandler-onsuccess) |
| **void** | [onMessage](#IRTCASREngineEventHandler-onmessage) |
| **void** | [onError](#IRTCASREngineEventHandler-onerror) |


## 函数说明
<span id="IRTCASREngineEventHandler-onsuccess"></span>
### onSuccess
```java
public void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onSuccess()
```
语音识别服务开启成功回调


<span id="IRTCASREngineEventHandler-onmessage"></span>
### onMessage
```java
public void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onMessage(
    String message)
```
语音转文字成功后回调，该回调返回识别后的全量消息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| message | **String** | 识别完成后得到的文字消息 |


**注意**
若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。

<span id="IRTCASREngineEventHandler-onerror"></span>
### onError
```java
public void com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.onError(
    int errorCode,
    String errorMessage)
```
当语音识别服务内部发生错误事件时触发该回调。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| errorCode | **int** | 错误码  <br/>• < 0: 参数错误或 API 调用顺序错误，参看 [RTCASRErrorCode](#rtcasrerrorcode)；  <br/>• >0: 参看 [语音识别服务错误码](https://www.volcengine.com/docs/6561/80818#_3-3-%E9%94%99%E8%AF%AF%E7%A0%81) |
| errorMessage | **String** | 错误原因说明。 |


# RTCASRErrorCode
```java
public enum com.ss.bytertc.engine.handler.IRTCASREngineEventHandler.RTCASRErrorCode
```

语音识别服务错误码。  <br>
除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 `startASR` 重启语音识别功能。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RTCASRErrorNetworkInterrupted(-1)** | 网络连接中断，服务不可用，内部会进行重连 |
| **RTCASRErrorAlreadyStarted(-2)** | 重复调用 `startASR`。开启语音识别服务后，你需要先调用 `stopASR` 停止语音识别服务，才能二次调用 `startASR` 再次开启服务。 |
| **RTCASRErrorTokenEmpty(-3)** | 语音识别服务所需 token 为空 |
| **RTCErrorSignatureKeyEmpty(-4)** | Signature 鉴权模式下 secretKey 为空 |
| **RTCASRErrorUserIdNull(-5)** | 用户 ID 为空 |
| **RTCASRErrorAPPIDNull(-6)** | 应用 ID 为空 |
| **RTCASRErrorClusterNull(-7)** | 语音识别服务 cluster 为空 |
| **RTCASRErrorOperationDenied(-8)** | 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。 |


# ByteRTCStreamMixingEvent
```java
public enum com.ss.bytertc.engine.live.ByteRTCStreamMixingEvent
```

转推直播任务状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **STREAM_MIXING_START(1)** | 请求发起转推直播任务 |
| **STREAM_MIXING_START_SUCCESS(2)** | 发起转推直播任务成功 |
| **STREAM_MIXING_START_FAILED(3)** | 发起转推直播任务失败 |
| **STREAM_MIXING_UPDATE(4)** | 请求更新转推直播任务配置 |
| **STREAM_MIXING_UPDATE_SUCCESS(5)** | 成功更新转推直播任务配置 |
| **STREAM_MIXING_UPDATE_FAILED(6)** | 更新转推直播任务配置失败 |
| **STREAM_MIXING_STOP(7)** | 请求结束转推直播任务 |
| **STREAM_MIXING_STOP_SUCCESS(8)** | 结束转推直播任务成功 |
| **STREAM_MIXING_STOP_FAILED(9)** | 结束转推直播任务失败 |
| **STREAM_MIXING_CHANGE_MIX_TYPE(10)** | 更新转推直播任务配置的请求超时 |
| **STREAM_MIXING_FIRST_AUDIO_FRAME_BY_CLIENT_MIX(11)** | 得到客户端合流音频首帧 |
| **STREAM_MIXING_FIRST_VIDEO_FRAME_BY_CLIENT_MIX(12)** | 收到客户端合流视频首帧 |
| **STREAM_MIXING_UPDATE_TIMEOUT(13)** | 更新转推直播任务配置超时 |
| **STREAM_MIXING_START_TIMEOUT(14)** | 发起转推直播任务配置超时 |
| **STREAM_MIXING_REQUEST_PARAM_ERROR(15)** | 合流布局参数错误 |
| **STREAM_MIXING_MIX_IMAGE_EVENT(16)** | 合流加图片 |


# ByteRTCStreamMixingType
```java
public enum com.ss.bytertc.engine.live.ByteRTCStreamMixingType
```

合流类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **STREAM_MIXING_BY_SERVER(0)** | 服务端合流 |
| **STREAM_MIXING_BY_CLIENT(1)** | 端云一体合流 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **ByteRTCStreamMixingType** | [ByteRTCStreamMixingType](#ByteRTCStreamMixingType-bytertcstreammixingtype) |


## 函数说明
<span id="ByteRTCStreamMixingType-bytertcstreammixingtype"></span>
### ByteRTCStreamMixingType
```java
com.ss.bytertc.engine.live.ByteRTCStreamMixingType.ByteRTCStreamMixingType(
    int value)
```

# LiveTranscoding
```java
public class com.ss.bytertc.engine.live.LiveTranscoding
```

转推直播配置参数。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [ACTION_START](#LiveTranscoding-action_start) |
| **String** | [ACTION_CHANGED](#LiveTranscoding-action_changed) |
| **String** | [ACTION_STOPPED](#LiveTranscoding-action_stopped) |


## 静态函数

| 返回 | 名称 |
| --- | --- |
| **static LiveTranscoding** | [getDefualtLiveTranscode](#LiveTranscoding-getdefualtlivetranscode) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [setUrl](#LiveTranscoding-seturl) |
| **void** | [setRoomId](#LiveTranscoding-setroomid) |
| **void** | [setUserId](#LiveTranscoding-setuserid) |
| **void** | [setAction](#LiveTranscoding-setaction) |
| **void** | [setVideo](#LiveTranscoding-setvideo) |
| **void** | [setAudio](#LiveTranscoding-setaudio) |
| **void** | [setLayout](#LiveTranscoding-setlayout) |
| **ByteRTCStreamMixingType** | [getMixType](#LiveTranscoding-getmixtype) |
| **void** | [setMixType](#LiveTranscoding-setmixtype) |
| **String** | [getUrl](#LiveTranscoding-geturl) |
| **VideoConfig** | [getVideo](#LiveTranscoding-getvideo) |
| **AudioConfig** | [getAudio](#LiveTranscoding-getaudio) |
| **Layout** | [getLayout](#LiveTranscoding-getlayout) |


## 变量说明
<span id="LiveTranscoding-action_start"></span>
### ACTION_START
```java
public static final String com.ss.bytertc.engine.live.LiveTranscoding.ACTION_START = "started";
```
开启转推直播。


<span id="LiveTranscoding-action_changed"></span>
### ACTION_CHANGED
```java
public static final String com.ss.bytertc.engine.live.LiveTranscoding.ACTION_CHANGED = "layoutChanged";
```
更新合流视频布局。


<span id="LiveTranscoding-action_stopped"></span>
### ACTION_STOPPED
```java
public static final String com.ss.bytertc.engine.live.LiveTranscoding.ACTION_STOPPED = "stopped";
```
停止直播推流功能。



## 函数说明
<span id="LiveTranscoding-getdefualtlivetranscode"></span>
### getDefualtLiveTranscode
```java
public static LiveTranscoding com.ss.bytertc.engine.live.LiveTranscoding.getDefualtLiveTranscode()
```
获取默认的转推直播配置参数。

**返回值**
默认的转推直播配置参数。参看 [LiveTranscoding](#livetranscoding)。


<span id="LiveTranscoding-seturl"></span>
### setUrl
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.setUrl(
    String url)
```
设置推流 CDN 地址。


<span id="LiveTranscoding-setroomid"></span>
### setRoomId
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.setRoomId(
    String roomId)
```
设置roomId。


<span id="LiveTranscoding-setuserid"></span>
### setUserId
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.setUserId(
    String userId)
```
设置userId。


<span id="LiveTranscoding-setaction"></span>
### setAction
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.setAction(
    String action)
```
设置转推直播动作参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| action | **String** | 转推直播动作。可选取值如下：  <br/>• ACTION_START: 开启转推直播功能  <br/>• ACTION_CHANGED: 更新转推直播视频合流布局  <br/>• ACTION_STOPPED: 停止转推直播功能 |


<span id="LiveTranscoding-setvideo"></span>
### setVideo
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.setVideo(
    VideoConfig video)
```
设置视频转码配置参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| video | **VideoConfig** | 视频转码配置参数。详见 [VideoConfig](#videoconfig) 数据类型。 |


<span id="LiveTranscoding-setaudio"></span>
### setAudio
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.setAudio(
    AudioConfig audio)
```
设置音频转码配置参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| audio | **AudioConfig** | 音频转码配置参数。详见 [AudioConfig](#audioconfig) 数据类型。 |


<span id="LiveTranscoding-setlayout"></span>
### setLayout
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.setLayout(
    Layout layout)
```
设置视频流合流整体布局信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| layout | **Layout** | 视频流合流整体布局参数。详见 [Layout](#layout) 数据类型。 |


<span id="LiveTranscoding-getmixtype"></span>
### getMixType
```java
public ByteRTCStreamMixingType com.ss.bytertc.engine.live.LiveTranscoding.getMixType()
```
获取合流类型。

**返回值**
合流类型，参看 [ByteRTCStreamMixingType](#bytertcstreammixingtype)。


<span id="LiveTranscoding-setmixtype"></span>
### setMixType
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.setMixType(
    ByteRTCStreamMixingType mixType)
```
设置合流类型。本参数不支持过程中更新。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mixType | **ByteRTCStreamMixingType** | 合流类型，参看 [ByteRTCStreamMixingType](#bytertcstreammixingtype)。 |


<span id="LiveTranscoding-geturl"></span>
### getUrl
```java
public String com.ss.bytertc.engine.live.LiveTranscoding.getUrl()
```
获取推流的 CDN 地址。

**返回值**
CDN 的 URL 地址。


<span id="LiveTranscoding-getvideo"></span>
### getVideo
```java
public VideoConfig com.ss.bytertc.engine.live.LiveTranscoding.getVideo()
```
获取视频转码配置参数。

**返回值**
当前视频转码配置参数。详见 [VideoConfig](#videoconfig) 数据类型。


<span id="LiveTranscoding-getaudio"></span>
### getAudio
```java
public AudioConfig com.ss.bytertc.engine.live.LiveTranscoding.getAudio()
```
获取音频转码配置参数。

**返回值**
当前音频转码配置参数。详见 [AudioConfig](#audioconfig) 数据类型。


<span id="LiveTranscoding-getlayout"></span>
### getLayout
```java
public Layout com.ss.bytertc.engine.live.LiveTranscoding.getLayout()
```
获取视频流合流整体布局信息。

**返回值**
当前视频流合流整体布局。详见 [Layout](#layout) 数据类型。


# TranscoderContentControlType
```java
public enum com.ss.bytertc.engine.live.LiveTranscoding.TranscoderContentControlType
```

合流输出内容类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **HAS_AUDIO_AND_VIDEO(0)** | 输出的混流包含音频和视频 |
| **HAS_AUDIO_ONLY(1)** | 输出的混流只包含音频 |
| **HAS_VIDEO_ONLY(2)** | 输出的混流只包含视频 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [getValue](#TranscoderContentControlType-getvalue) |


## 函数说明
<span id="TranscoderContentControlType-getvalue"></span>
### getValue
```java
public int com.ss.bytertc.engine.live.LiveTranscoding.TranscoderContentControlType.getValue()
```
获取合流输出内容类型。

**返回值**
合流输出内容类型


# TranscoderRenderMode
```java
public enum com.ss.bytertc.engine.live.LiveTranscoding.TranscoderRenderMode
```

视频渲染的缩放模式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RENDER_HIDDEN(1)** | 视窗填满优先，默认值。  <br><br/>视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。 |
| **RENDER_FIT(2)** | 视频帧内容全部显示优先。  <br><br/>视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。 |
| **RENDER_ADAPTIVE(3)** | 视频帧自适应画布。 <br><br/>视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [getValue](#TranscoderRenderMode-getvalue) |


## 函数说明
<span id="TranscoderRenderMode-getvalue"></span>
### getValue
```java
public int com.ss.bytertc.engine.live.LiveTranscoding.TranscoderRenderMode.getValue()
```
获取视频内容的缩放模式。

**返回值**
视频内容的缩放模式。


# TranscoderLayoutRegionType
```java
public enum com.ss.bytertc.engine.live.LiveTranscoding.TranscoderLayoutRegionType
```

合流布局区域类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **LAYOUT_REGION_TYPE_VIDEO_STREAM(0)** | 合流布局区域类型为视频。 |
| **LAYOUT_REGION_TYPE_IMAGE(1)** | 合流布局区域类型为图片。 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [getValue](#TranscoderLayoutRegionType-getvalue) |


## 函数说明
<span id="TranscoderLayoutRegionType-getvalue"></span>
### getValue
```java
public int com.ss.bytertc.engine.live.LiveTranscoding.TranscoderLayoutRegionType.getValue()
```
获取合流布局区域类型。

**返回值**
合流布局区域类型。


# AACProfile
```java
public enum com.ss.bytertc.engine.live.LiveTranscoding.AACProfile
```

AAC 编码类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AAC_PROFILE_LC("LC")** | 编码等级 AAC-LC |
| **AAC_PROFILE_HEV1("HEv1")** | 编码等级 HE-AAC v1 |
| **AAC_PROFILE_HEV2("HEv2")** | 编码等级 HE-AAC v2 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **String** | [getValue](#AACProfile-getvalue) |


## 函数说明
<span id="AACProfile-getvalue"></span>
### getValue
```java
public String com.ss.bytertc.engine.live.LiveTranscoding.AACProfile.getValue()
```
获取 AAC 编码类型。

**返回值**
AAC 编码类型。


# VideoConfig
```java
public static class com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig
```

视频转码配置参数。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **VideoConfig** | [setCodec](#VideoConfig-setcodec) |
| **VideoConfig** | [setFps](#VideoConfig-setfps) |
| **VideoConfig** | [setGop](#VideoConfig-setgop) |
| **VideoConfig** | [setLowLatency](#VideoConfig-setlowlatency) |
| **VideoConfig** | [setKBitRate](#VideoConfig-setkbitrate) |
| **VideoConfig** | [setWidth](#VideoConfig-setwidth) |
| **VideoConfig** | [setHeight](#VideoConfig-setheight) |


## 函数说明
<span id="VideoConfig-setcodec"></span>
### setCodec
```java
public VideoConfig com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.setCodec(
    String codec)
```
设置视频编码器。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| codec | **String** | 编码器。默认值为 `0`。 <br/>• 值为 `0` 时，使用 H.264； <br/>• 值为 `1` 时，使用 byteVC1。此时，你必须调用 [setKBitRate](#VideoConfig-setkbitrate) 设置视频码率。 |


<span id="VideoConfig-setfps"></span>
### setFps
```java
public VideoConfig com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.setFps(
    int fps)
```
设置合流视频帧率信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| fps | **int** | 合流的视频帧率。默认值为 `15`，取值范围是 `[1, 60]`。值不合法时，自动调整为默认值。 |


<span id="VideoConfig-setgop"></span>
### setGop
```java
public VideoConfig com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.setGop(
    int gop)
```
设置视频 I 帧间隔。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| gop | **int** | I 帧间隔。默认值为 `4`，取值范围为 `[1, 5]`，单位为秒。值不合法时，自动调整为默认值。 |


<span id="VideoConfig-setlowlatency"></span>
### setLowLatency
```java
public VideoConfig com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.setLowLatency(
    boolean lowLatency)
```
设置是否使用低延时特性。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| lowLatency | **boolean** | 是否使用低延时特性。取值含义如下:  <br/>•  true: 使用低延时特性  <br/>• false: 不使用低延时特性 |


<span id="VideoConfig-setkbitrate"></span>
### setKBitRate
```java
public VideoConfig com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.setKBitRate(
    int kBitRate)
```
设置合流视频码率

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| kBitRate | **int** | 合流视频码率。单位为 kbps，取值范围为 `[1,10000]`，默认值为自适应。值不合法时，自动调整为默认值。 |


<span id="VideoConfig-setwidth"></span>
### setWidth
```java
public VideoConfig com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.setWidth(
    int width)
```
设置合流视频宽度。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| width | **int** | 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640。 |


<span id="VideoConfig-setheight"></span>
### setHeight
```java
public VideoConfig com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.setHeight(
    int height)
```
设置合流视频高度。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| height | **int** | 合流视频高度。单位为 px，范围为 [2, 1080]，必须是偶数。默认值为 480。 |


# VideoCodecType
```java
public enum com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.VideoCodecType
```

转推直播视频编码器格式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **VIDEO_CODEC_TYPE_H264("H264")** | 标准 H264 编码格式 |
| **VIDEO_CODEC_TYPE_BYTEVC1("ByteVC1")** | ByteVC1 编码格式 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **String** | [getValue](#VideoCodecType-getvalue) |


## 函数说明
<span id="VideoCodecType-getvalue"></span>
### getValue
```java
public String com.ss.bytertc.engine.live.LiveTranscoding.VideoConfig.VideoCodecType.getValue()
```
获取转推直播视频编码器格式。

**返回值**
转推直播视频编码器格式。


# AudioConfig
```java
public static class com.ss.bytertc.engine.live.LiveTranscoding.AudioConfig
```

音频转码配置参数。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **AudioConfig** | [setCodec](#AudioConfig-setcodec) |
| **AudioConfig** | [setKBitRate](#AudioConfig-setkbitrate) |
| **AudioConfig** | [setSampleRate](#AudioConfig-setsamplerate) |
| **AudioConfig** | [setChannels](#AudioConfig-setchannels) |
| **AudioConfig** | [setAacProfile](#AudioConfig-setaacprofile) |


## 函数说明
<span id="AudioConfig-setcodec"></span>
### setCodec
```java
public AudioConfig com.ss.bytertc.engine.live.LiveTranscoding.AudioConfig.setCodec(
    String codec)
```
设置音频编码格式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| codec | **String** | 音频编码格式，仅支持`AAC`编码格式。 |


<span id="AudioConfig-setkbitrate"></span>
### setKBitRate
```java
public AudioConfig com.ss.bytertc.engine.live.LiveTranscoding.AudioConfig.setKBitRate(
    int kBitRate)
```
设置音频码率。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| kBitRate | **int** | 音频码率，单位 Kbps。可取范围 [32Kbps, 192Kbps]，默认值为 64Kbps。 |


<span id="AudioConfig-setsamplerate"></span>
### setSampleRate
```java
public AudioConfig com.ss.bytertc.engine.live.LiveTranscoding.AudioConfig.setSampleRate(
    int sampleRate)
```
设置音频采样率。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| sampleRate | **int** | 音频采样率，单位 Hz。可取 32000Hz、44100Hz、48000Hz，默认值为 48000Hz。 |


<span id="AudioConfig-setchannels"></span>
### setChannels
```java
public AudioConfig com.ss.bytertc.engine.live.LiveTranscoding.AudioConfig.setChannels(
    int channels)
```
设置声道数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| channels | **int** | 音频声道数。可取 1、2，默认值为 2。 |


<span id="AudioConfig-setaacprofile"></span>
### setAacProfile
```java
public AudioConfig com.ss.bytertc.engine.live.LiveTranscoding.AudioConfig.setAacProfile(
    AACProfile aacProfile)
```
设置 AAC 等级。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| AACProfile | **** | AAC 等级，参看 [AACProfile](#aacprofile)。默认值为 `AAC_PROFILE_LC("LC")`。 |


# Region
```java
public static class com.ss.bytertc.engine.live.LiveTranscoding.Region
```

单个图片或视频流在合流中的布局信息。  <br>
开启转推直播功能后，在多路视频流合流时，你可以设置其中一路视频流在合流中的预设布局信息。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **Region** | [uid](#Region-uid) |
| **Region** | [roomId](#Region-roomid) |
| **Region** | [zorder](#Region-zorder) |
| **Region** | [alpha](#Region-alpha) |
| **Region** | [contentControl](#Region-contentcontrol) |
| **Region** | [renderMode](#Region-rendermode) |
| **Region** | [position](#Region-position) |
| **Region** | [size](#Region-size) |
| **boolean** | [isScreenStream](#Region-isscreenstream) |
| **Region** | [setScreenStream](#Region-setscreenstream) |
| **boolean** | [isLocalUser](#Region-islocaluser) |
| **Region** | [setLocalUser](#Region-setlocaluser) |
| **Region** | [type](#Region-type) |
| **Region** | [data](#Region-data) |
| **Region** | [dataParam](#Region-dataparam) |


## 函数说明
<span id="Region-uid"></span>
### uid
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.uid(
    String)
```
设置视频流发布用户的用户 ID。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 用户 ID。 |


<span id="Region-roomid"></span>
### roomId
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.roomId(
    String)
```
设置视频流发布用户的房间 ID。必填。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 房间 ID。 |


<span id="Region-zorder"></span>
### zorder
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.zorder(
    int)
```
设置用户视频布局在画布中的层级。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| zorder | **int** | 用户视频布局在画布中的层级。取值范围为[0 - 100]。0为底层，值越大越上层。 |


<span id="Region-alpha"></span>
### alpha
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.alpha(
    double)
```
设置透明度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| alpha | **double** | 透明度，可选范围为 [0.0, 1.0]，0.0 为全透明。 |


<span id="Region-contentcontrol"></span>
### contentControl
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.contentControl(
    TranscoderContentControlType)
```
设置合流内容类型。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| contentControl | **TranscoderContentControlType** | 合流内容控制。默认值为 `TranscoderContentControlType.HAS_AUDIO_AND_VIDEO`，参看 [TranscoderContentControlType](#transcodercontentcontroltype)。 |


<span id="Region-rendermode"></span>
### renderMode
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.renderMode(
    TranscoderRenderMode)
```
设置图片或视频流渲染的缩放模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| renderMode | **TranscoderRenderMode** | 图片或视频流的缩放模式，参看 [TranscoderRenderMode](#transcoderrendermode)。 |


<span id="Region-position"></span>
### position
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.position(
    double x,
    double y)
```
设置用户视频布局的相对位置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| x | **double** | 视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。 |
| y | **double** | 视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。 |


<span id="Region-size"></span>
### size
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.size(
    double width,
    double height)
```
设置用户视频相对大小。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| width | **double** | 视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。 |
| height | **double** | 视频流对应区域高度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。 |


<span id="Region-isscreenstream"></span>
### isScreenStream
```java
public boolean com.ss.bytertc.engine.live.LiveTranscoding.Region.isScreenStream()
```
是否是屏幕流。

**返回值**

+ True： 是屏幕流。  
+ False：不是屏幕流。


<span id="Region-setscreenstream"></span>
### setScreenStream
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.setScreenStream(
    boolean screenStream)
```
设置是否是屏幕流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| screenStream | **boolean** | 标识是否是屏幕流 |


<span id="Region-islocaluser"></span>
### isLocalUser
```java
public boolean com.ss.bytertc.engine.live.LiveTranscoding.Region.isLocalUser()
```
是否本地用户。

**返回值**

+ True： 是本地用户。  
+ False：不是本地用户。


<span id="Region-setlocaluser"></span>
### setLocalUser
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.setLocalUser(
    boolean localUser)
```
设置是否是本地用户。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| localUser | **boolean** | 标识是否是本地用户 |


<span id="Region-type"></span>
### type
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.type(
    TranscoderLayoutRegionType)
```
设置合流布局区域类型。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| type | **TranscoderLayoutRegionType** | 合流布局区域类型，详见 [TranscoderLayoutRegionType](#transcoderlayoutregiontype)。 |


<span id="Region-data"></span>
### data
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.data(
    byte[])
```
设置图片合流区域类型对应的数据。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| data | **byte[]** | 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。 |


<span id="Region-dataparam"></span>
### dataParam
```java
public Region com.ss.bytertc.engine.live.LiveTranscoding.Region.dataParam(
    Region.DataParam)
```
设置合流布局区域数据的对应参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| dataParam | **Region.DataParam** | 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 [DataParam](#dataparam)。 |


# DataParam
```java
public static class com.ss.bytertc.engine.live.LiveTranscoding.Region.DataParam
```

图片合流相关参数


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **Region.DataParam** | [setImageWidth](#DataParam-setimagewidth) |
| **Region.DataParam** | [setImageHeight](#DataParam-setimageheight) |


## 函数说明
<span id="DataParam-setimagewidth"></span>
### setImageWidth
```java
public Region.DataParam com.ss.bytertc.engine.live.LiveTranscoding.Region.DataParam.setImageWidth(
    int imageWidth)
```
原始图片的宽度，单位为 px。


<span id="DataParam-setimageheight"></span>
### setImageHeight
```java
public Region.DataParam com.ss.bytertc.engine.live.LiveTranscoding.Region.DataParam.setImageHeight(
    int imageHeight)
```
原始图片的高度，单位为 px。


# Layout
```java
public static class com.ss.bytertc.engine.live.LiveTranscoding.Layout
```

视频流合流整体布局信息。  <br>
开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **Region[]** | [getRegions](#Layout-getregions) |
| **void** | [setRegions](#Layout-setregions) |
| **String** | [getAppData](#Layout-getappdata) |
| **void** | [setAppData](#Layout-setappdata) |
| **String** | [getBackgroundColor](#Layout-getbackgroundcolor) |
| **void** | [setBackgroundColor](#Layout-setbackgroundcolor) |


## 函数说明
<span id="Layout-getregions"></span>
### getRegions
```java
public Region[] com.ss.bytertc.engine.live.LiveTranscoding.Layout.getRegions()
```
获取用户布局信息列表。

**返回值**
当前合流的用户布局信息列表。


<span id="Layout-setregions"></span>
### setRegions
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.Layout.setRegions(
    Region[] regions)
```
设置用户布局信息列表。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| regions | **Region[]** | 用户布局信息列表。为 [Region](#region) 数据类型的数组。每一个该类型对象为一路单独的视频流的布局信息。 |


<span id="Layout-getappdata"></span>
### getAppData
```java
public String com.ss.bytertc.engine.live.LiveTranscoding.Layout.getAppData()
```
获取透传的 App 数据。

**返回值**
当前透传的 App 数据。


<span id="Layout-setappdata"></span>
### setAppData
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.Layout.setAppData(
    String appData)
```
设置透传的 App 数据。长度不超过 4KB。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| appData | **String** | 透传的 App 数据。 |


<span id="Layout-getbackgroundcolor"></span>
### getBackgroundColor
```java
public String com.ss.bytertc.engine.live.LiveTranscoding.Layout.getBackgroundColor()
```
获取画布的背景颜色。

**返回值**
当前画布的背景颜色。


<span id="Layout-setbackgroundcolor"></span>
### setBackgroundColor
```java
public void com.ss.bytertc.engine.live.LiveTranscoding.Layout.setBackgroundColor(
    String backgroundColor)
```
设置画布的背景颜色。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| backgroundColor | **String** | 画布的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色 |


# Builder
```java
public static class com.ss.bytertc.engine.live.LiveTranscoding.Layout.Builder
```

构建参数组合


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **Builder** | [appData](#Builder-appdata) |
| **Builder** | [backgroundColor](#Builder-backgroundcolor) |


## 函数说明
<span id="Builder-appdata"></span>
### appData
```java
public Builder com.ss.bytertc.engine.live.LiveTranscoding.Layout.Builder.appData(
    String)
```
透传的 app 数据


<span id="Builder-backgroundcolor"></span>
### backgroundColor
```java
public Builder com.ss.bytertc.engine.live.LiveTranscoding.Layout.Builder.backgroundColor(
    String)
```
画布的背景颜色


# PushSingleStreamParam
```java
public class com.ss.bytertc.engine.live.PushSingleStreamParam
```

单流转推直播配置参数。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [roomId](#PushSingleStreamParam-roomid) |
| **String** | [userId](#PushSingleStreamParam-userid) |
| **String** | [url](#PushSingleStreamParam-url) |
| **boolean** | [isScreen](#PushSingleStreamParam-isscreen) |


## 变量说明
<span id="PushSingleStreamParam-roomid"></span>
### roomId
```java
public String com.ss.bytertc.engine.live.PushSingleStreamParam.roomId;
```
媒体流所在的房间 ID


<span id="PushSingleStreamParam-userid"></span>
### userId
```java
public String com.ss.bytertc.engine.live.PushSingleStreamParam.userId;
```
媒体流所属的用户 ID


<span id="PushSingleStreamParam-url"></span>
### url
```java
public String com.ss.bytertc.engine.live.PushSingleStreamParam.url;
```
推流地址


<span id="PushSingleStreamParam-isscreen"></span>
### isScreen
```java
public boolean com.ss.bytertc.engine.live.PushSingleStreamParam.isScreen = false;
```
媒体流是否为屏幕流。



# RTCNativeLibraryLoader
```java
public interface com.ss.bytertc.engine.loader.RTCNativeLibraryLoader
```

用户自定义动态库加载器实现


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **boolean** | [load](#RTCNativeLibraryLoader-load) |


## 函数说明
<span id="RTCNativeLibraryLoader-load"></span>
### load
```java
boolean com.ss.bytertc.engine.loader.RTCNativeLibraryLoader.load(
    String libraryName)
```
SDK在需要加载动态库时通过该方法回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| libraryName | **String** | 要加载的动态库名称 |


# PublicStreaming
```java
public class com.ss.bytertc.engine.publicstream.PublicStreaming
```

公共流参数。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [ACTION_START](#PublicStreaming-action_start) |
| **String** | [ACTION_CHANGED](#PublicStreaming-action_changed) |
| **String** | [ACTION_STOPPED](#PublicStreaming-action_stopped) |


## 静态函数

| 返回 | 名称 |
| --- | --- |
| **static PublicStreaming** | [getDefualtPublicStreaming](#PublicStreaming-getdefualtpublicstreaming) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [setRoomId](#PublicStreaming-setroomid) |
| **void** | [setAction](#PublicStreaming-setaction) |
| **void** | [setVideo](#PublicStreaming-setvideo) |
| **void** | [setLayout](#PublicStreaming-setlayout) |
| **VideoConfig** | [getVideo](#PublicStreaming-getvideo) |
| **Layout** | [getLayout](#PublicStreaming-getlayout) |


## 变量说明
<span id="PublicStreaming-action_start"></span>
### ACTION_START
```java
public static final String com.ss.bytertc.engine.publicstream.PublicStreaming.ACTION_START = "started";
```
设置公共流发布动作参数：开启公共流推流功能。


<span id="PublicStreaming-action_changed"></span>
### ACTION_CHANGED
```java
public static final String com.ss.bytertc.engine.publicstream.PublicStreaming.ACTION_CHANGED = "layoutChanged";
```
设置公共流发布动作参数：更新视频公共流布局。


<span id="PublicStreaming-action_stopped"></span>
### ACTION_STOPPED
```java
public static final String com.ss.bytertc.engine.publicstream.PublicStreaming.ACTION_STOPPED = "stopped";
```
设置公共流发布动作参数：停止公共流推流功能。



## 函数说明
<span id="PublicStreaming-getdefualtpublicstreaming"></span>
### getDefualtPublicStreaming
```java
public static PublicStreaming com.ss.bytertc.engine.publicstream.PublicStreaming.getDefualtPublicStreaming()
```
获取默认的公共流配置属性。

**返回值**
默认的推公共流转码配置属性。详见 [PublicStreaming](#publicstreaming) 数据类型。


<span id="PublicStreaming-setroomid"></span>
### setRoomId
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.setRoomId(
    String roomId)
```
设置 roomId。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** |  |


<span id="PublicStreaming-setaction"></span>
### setAction
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.setAction(
    String action)
```
设置公共流发布动作参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| action | **String** | 公共流发布动作。可选取值如下：  <br/>• ACTION_START: 开启发布  <br/>• ACTION_CHANGED: 更新公共流布局  <br/>• ACTION_STOPPED: 停止发布 |


<span id="PublicStreaming-setvideo"></span>
### setVideo
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.setVideo(
    VideoConfig video)
```
设置公共流视频参数。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| video | **VideoConfig** | 公共流视频参数，必填。详见 [VideoConfig](#videoconfig-2) 数据类型。 |


**注意**
建议先调用 [getDefualtPublicStreaming](#PublicStreaming-getdefualtpublicstreaming) 获取包含默认参数的数据结构体。

<span id="PublicStreaming-setlayout"></span>
### setLayout
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.setLayout(
    Layout layout)
```
设置公共流整体布局信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| layout | **Layout** | 公共流整体布局参数，必填。详见 [Layout](#layout-2) 数据类型。 |


<span id="PublicStreaming-getvideo"></span>
### getVideo
```java
public VideoConfig com.ss.bytertc.engine.publicstream.PublicStreaming.getVideo()
```
获取公共流视频编码参数。

**返回值**
公共流视频参数。详见 [VideoConfig](#videoconfig-2) 数据类型。


<span id="PublicStreaming-getlayout"></span>
### getLayout
```java
public Layout com.ss.bytertc.engine.publicstream.PublicStreaming.getLayout()
```
获取公共流整体布局信息。

**返回值**
当前公共流整体布局。详见 [Layout](#layout-2) 数据类型。


# VideoConfig
```java
public static class com.ss.bytertc.engine.publicstream.PublicStreaming.VideoConfig
```

公共流的视频编码参数


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **VideoConfig** | [setFps](#VideoConfig-setfps) |
| **VideoConfig** | [setKBitRate](#VideoConfig-setkbitrate) |
| **VideoConfig** | [setWidth](#VideoConfig-setwidth) |
| **VideoConfig** | [setHeight](#VideoConfig-setheight) |


## 函数说明
<span id="VideoConfig-setfps"></span>
### setFps
```java
public VideoConfig com.ss.bytertc.engine.publicstream.PublicStreaming.VideoConfig.setFps(
    int fps)
```
设置公共流视频帧率。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| fps | **int** | 公共流视频帧率。必填<br/>范围：[1, 60] <br/>默认值：30 fps |

**返回值**
公共流视频参数。详见 [VideoConfig](#videoconfig-2) 数据类型。


<span id="VideoConfig-setkbitrate"></span>
### setKBitRate
```java
public VideoConfig com.ss.bytertc.engine.publicstream.PublicStreaming.VideoConfig.setKBitRate(
    int kBitRate)
```
设置公共流视频码率  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| kBitRate | **int** | 视频码率，必填<br/>范围：[1,10000000]<br/>单位为 bps，默认值为 500 。 |

**返回值**
公共流视频参数。详见 [VideoConfig](#videoconfig-2) 数据类型。


<span id="VideoConfig-setwidth"></span>
### setWidth
```java
public VideoConfig com.ss.bytertc.engine.publicstream.PublicStreaming.VideoConfig.setWidth(
    int width)
```
设置公共流视频宽度。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| width | **int** | 公共流视频宽度，必填。单位为 px，范围为 [16, 1920]，必须是偶数。默认值为 360 px。 |

**返回值**
公共流视频参数。详见 [VideoConfig](#videoconfig-2) 数据类型。


<span id="VideoConfig-setheight"></span>
### setHeight
```java
public VideoConfig com.ss.bytertc.engine.publicstream.PublicStreaming.VideoConfig.setHeight(
    int height)
```
设置公共流视频高度。  <br>

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| height | **int** | 公共流视频高度，必填。单位为 px，范围为 [16, 1280]，必须是偶数。默认值为 640。 |

**返回值**
公共流视频参数。详见 [VideoConfig](#videoconfig-2) 数据类型。


# SourceCrop
```java
public static class com.ss.bytertc.engine.publicstream.PublicStreaming.SourceCrop
```

公共流布局中的视频裁剪参数。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **SourceCrop** | [setLocationX](#SourceCrop-setlocationx) |
| **SourceCrop** | [setLocationY](#SourceCrop-setlocationy) |
| **SourceCrop** | [setWidthProportion](#SourceCrop-setwidthproportion) |
| **SourceCrop** | [setHeightProportion](#SourceCrop-setheightproportion) |


## 函数说明
<span id="SourceCrop-setlocationx"></span>
### setLocationX
```java
public SourceCrop com.ss.bytertc.engine.publicstream.PublicStreaming.SourceCrop.setLocationX(
    double x)
```
设置左上角横坐标。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| x | **double** | 裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)。 |

**返回值**
裁剪配置。详见 [SourceCrop](#sourcecrop) 数据类型。


<span id="SourceCrop-setlocationy"></span>
### setLocationY
```java
public SourceCrop com.ss.bytertc.engine.publicstream.PublicStreaming.SourceCrop.setLocationY(
    double y)
```
设置左上角纵坐标。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| y | **double** | 裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)。 |

**返回值**
裁剪配置。详见 [SourceCrop](#sourcecrop) 数据类型。


<span id="SourceCrop-setwidthproportion"></span>
### setWidthProportion
```java
public SourceCrop com.ss.bytertc.engine.publicstream.PublicStreaming.SourceCrop.setWidthProportion(
    double w)
```
设置视频宽度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| w | **double** | 裁剪后得到的视频帧宽度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0] |

**返回值**
裁剪配置。详见 [SourceCrop](#sourcecrop) 数据类型。


<span id="SourceCrop-setheightproportion"></span>
### setHeightProportion
```java
public SourceCrop com.ss.bytertc.engine.publicstream.PublicStreaming.SourceCrop.setHeightProportion(
    double h)
```
设置视频高度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| h | **double** | 裁剪后得到的视频帧高度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]。 |

**返回值**
裁剪配置。详见 [SourceCrop](#sourcecrop) 数据类型。


# Layout
```java
public static class com.ss.bytertc.engine.publicstream.PublicStreaming.Layout
```

公共流的合流布局


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **Region[]** | [getRegions](#Layout-getregions) |
| **void** | [setRegions](#Layout-setregions) |
| **int** | [getInterpolationMode](#Layout-getinterpolationmode) |
| **void** | [setInterpolationMode](#Layout-setinterpolationmode) |
| **int** | [getLayoutMode](#Layout-getlayoutmode) |
| **void** | [setLayoutMode](#Layout-setlayoutmode) |
| **String** | [getBackgroundImage](#Layout-getbackgroundimage) |
| **void** | [setBackgroundImage](#Layout-setbackgroundimage) |
| **String** | [getBackgroundColor](#Layout-getbackgroundcolor) |
| **void** | [setBackgroundColor](#Layout-setbackgroundcolor) |


## 函数说明
<span id="Layout-getregions"></span>
### getRegions
```java
public Region[] com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.getRegions()
```
获取当前公共流的用户布局信息列表。

**返回值**
当前公共流的用户布局信息列表。


<span id="Layout-setregions"></span>
### setRegions
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.setRegions(
    Region[] regions)
```
设置合成公共流的各路流的布局信息。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| regions | **Region[]** | 各路流的布局信息列表。为 [Region](#region-2) 数据类型的数组。每一个该类型对象为一路单独的视频流的布局信息。 |


<span id="Layout-getinterpolationmode"></span>
### getInterpolationMode
```java
public int com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.getInterpolationMode()
```
获取插帧模式。

**返回值**
插帧模式。

+ `0`: 补最后一帧
+ `1`: 补背景图片，如果没有设置背景图片则补黑帧


<span id="Layout-setinterpolationmode"></span>
### setInterpolationMode
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.setInterpolationMode(
    int interMode)
```
设置插帧模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| interMode | **int** | 插帧模式。<br/>• `0`: 补最后一帧<br/>• `1`: 补背景图片或者黑帧 |


<span id="Layout-getlayoutmode"></span>
### getLayoutMode
```java
public int com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.getLayoutMode()
```
获取当前公共流的布局模式。

**返回值**
当前使用的布局模式。

+ `0`: 自动模式。默认值。 
+ `2`: 自定义模式。


<span id="Layout-setlayoutmode"></span>
### setLayoutMode
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.setLayoutMode(
    int layoutMode)
```
设置公共流的布局模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| layoutMode | **int** | 公共流的目标布局模式：<br/>• `0`: 自动模式。默认值。 <br/>• `2`: 自定义模式。 |


<span id="Layout-getbackgroundimage"></span>
### getBackgroundImage
```java
public String com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.getBackgroundImage()
```
获取视频的背景图片链接。

**返回值**
当前背景图片链接


<span id="Layout-setbackgroundimage"></span>
### setBackgroundImage
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.setBackgroundImage(
    String bgImage)
```
设置背景图片链接。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| bgImage | **String** | 背景图片链接。 |


<span id="Layout-getbackgroundcolor"></span>
### getBackgroundColor
```java
public String com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.getBackgroundColor()
```
获取画布的背景颜色。

**返回值**
当前画布的背景颜色。


<span id="Layout-setbackgroundcolor"></span>
### setBackgroundColor
```java
public void com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.setBackgroundColor(
    String backgroundColor)
```
设置画布的背景颜色。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| backgroundColor | **String** | 画布的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色 |


# Region
```java
public static class com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region
```

合成公共流的每条流的布局信息


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **Region** | [userId](#Region-userid) |
| **Region** | [roomId](#Region-roomid) |
| **Region** | [zorder](#Region-zorder) |
| **Region** | [alpha](#Region-alpha) |
| **Region** | [mediaType](#Region-mediatype) |
| **Region** | [streamType](#Region-streamtype) |
| **Region** | [renderMode](#Region-rendermode) |
| **Region** | [position](#Region-position) |
| **Region** | [size](#Region-size) |
| **Region** | [sourceCropPosition](#Region-sourcecropposition) |
| **Region** | [sourceCropSize](#Region-sourcecropsize) |


## 函数说明
<span id="Region-userid"></span>
### userId
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.userId(
    String uid)
```
指定视频流所属用户的 ID。服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 用户 ID。必填。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-roomid"></span>
### roomId
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.roomId(
    String)
```
设置媒体流所在房间的房间 ID。服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| roomId | **String** | 必填。如果此媒体流是通过 [startForwardStreamToRooms](Android-api.md#RTCRoom-startforwardstreamtorooms) 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-zorder"></span>
### zorder
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.zorder(
    int)
```
设置用户视频布局在画布中的层级。当前 Region 的位置与其他 Region 重合时，将按照此处设置的层级属性进行渲染。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| zorder | **int** | 用户视频布局在画布中的层级。取值范围为[0, 100]。0(默认）为底层，100 为顶层。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-alpha"></span>
### alpha
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.alpha(
    double)
```
设置透明度。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| alpha | **double** | 透明度。必填。可选范围为 [0.0, 1.0]。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-mediatype"></span>
### mediaType
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.mediaType(
    int)
```
设置公共流内容类型。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| mediaType | **int** | 公共流内容类型。默认值为0，可选取值如下：  <br/>• 0: 输出的混流包含音视频  <br/>• 1: 只包含音频  <br/>• 2: 只包含视频 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-streamtype"></span>
### streamType
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.streamType(
    int)
```
设置公共流媒体类型。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| streamType | **int** | 公共流媒体类型。默认值为 0，可选取值如下：  <br/>• 0: 普通音视频流  <br/>• 1: 屏幕流 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-rendermode"></span>
### renderMode
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.renderMode(
    int)
```
设置视频显示模式。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| renderMode | **int** | 视频显示模式。可选取值如下：  <br/>• 1: 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。  <br/>• 2: 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。  <br/>• 3: 视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-position"></span>
### position
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.position(
    double x,
    double y)
```
设置用户视频布局的相对位置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| x | **double** | 视频流对应区域左上角的横坐标相对整体画面的比例，取值的范围为 [0.0, 1.0)。必填。 |
| y | **double** | 视频流对应区域左上角的纵坐标相对整体画面的比例，取值的范围为 [0.0, 1.0)。必填。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-size"></span>
### size
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.size(
    double width,
    double height)
```
设置用户视频相对大小。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| width | **double** | 视频流对应区域宽度相对整体画面的比例，取值的范围为 (0.0, 1.0]。必填。 |
| height | **double** | 视频流对应区域高度相对整体画面的比例，取值的范围为 (0.0, 1.0]。必填。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-sourcecropposition"></span>
### sourceCropPosition
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.sourceCropPosition(
    double x,
    double y)
```
设置用户视频布局的相对位置。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| x | **double** | 裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的比例，取值的范围为 [0.0, 1.0)。 |
| y | **double** | 裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的比例，取值的范围为 [0.0, 1.0)。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


<span id="Region-sourcecropsize"></span>
### sourceCropSize
```java
public Region com.ss.bytertc.engine.publicstream.PublicStreaming.Layout.Region.sourceCropSize(
    double width,
    double height)
```
设置裁剪视频相对大小。

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| width | **double** | 裁剪后得到的视频帧宽度相对于裁剪前整体画面的比例，取值的范围为 (0.0, 1.0]。 |
| height | **double** | 裁剪后得到的视频帧高度相对于裁剪前整体画面的比例，取值的范围为 (0.0, 1.0]。 |

**返回值**
当前流在公共流中的布局信息。详见 [Region](#region-2)。


# AudioFrame
```java
public class com.ss.bytertc.engine.utils.AudioFrame
```

PCM 音频帧


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **byte[]** | [buffer](#AudioFrame-buffer) |
| **int** | [samples](#AudioFrame-samples) |
| **AudioSampleRate** | [sampleRate](#AudioFrame-samplerate) |
| **AudioChannel** | [channel](#AudioFrame-channel) |


## 变量说明
<span id="AudioFrame-buffer"></span>
### buffer
```java
public byte[] com.ss.bytertc.engine.utils.AudioFrame.buffer;
```
PCM 数据


<span id="AudioFrame-samples"></span>
### samples
```java
public int com.ss.bytertc.engine.utils.AudioFrame.samples;
```
采样点个数


<span id="AudioFrame-samplerate"></span>
### sampleRate
```java
public AudioSampleRate com.ss.bytertc.engine.utils.AudioFrame.sampleRate;
```
采样率，参看 [AudioSampleRate](#audiosamplerate)。


<span id="AudioFrame-channel"></span>
### channel
```java
public AudioChannel com.ss.bytertc.engine.utils.AudioFrame.channel;
```
音频声道，参看 [AudioChannel](#audiochannel)。



# IAudioFrame
```java
public interface com.ss.bytertc.engine.utils.IAudioFrame
```

音频数据


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **long** | [timestamp_us](#IAudioFrame-timestamp_us) |
| **AudioSampleRate** | [sample_rate](#IAudioFrame-sample_rate) |
| **AudioChannel** | [channel](#IAudioFrame-channel) |
| **ByteBuffer** | [getDataBuffer](#IAudioFrame-getdatabuffer) |
| **int** | [data_size](#IAudioFrame-data_size) |
| **AudioFrameType** | [frame_type](#IAudioFrame-frame_type) |
| **void** | [release](#IAudioFrame-release) |


## 函数说明
<span id="IAudioFrame-timestamp_us"></span>
### timestamp_us
```java
long com.ss.bytertc.engine.utils.IAudioFrame.timestamp_us()
```
获取音频帧时间戳。

**返回值**
音频帧时间戳，单位：微秒。


<span id="IAudioFrame-sample_rate"></span>
### sample_rate
```java
AudioSampleRate com.ss.bytertc.engine.utils.IAudioFrame.sample_rate()
```
获取音频采样率，参看 [AudioSampleRate](#audiosamplerate)。

**返回值**
音频采样率


<span id="IAudioFrame-channel"></span>
### channel
```java
AudioChannel com.ss.bytertc.engine.utils.IAudioFrame.channel()
```
获取音频声道，参看 [AudioChannel](#audiochannel)。

**返回值**
音频声道


**注意**
双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。

<span id="IAudioFrame-getdatabuffer"></span>
### getDataBuffer
```java
ByteBuffer com.ss.bytertc.engine.utils.IAudioFrame.getDataBuffer()
```
获取音频帧内存块地址

**返回值**
音频帧的 ByteBuffer


<span id="IAudioFrame-data_size"></span>
### data_size
```java
int com.ss.bytertc.engine.utils.IAudioFrame.data_size()
```
获取音频帧数据大小。

**返回值**
音频帧数据大小，单位：字节。


<span id="IAudioFrame-frame_type"></span>
### frame_type
```java
AudioFrameType com.ss.bytertc.engine.utils.IAudioFrame.frame_type()
```
获取音频帧类型，目前只支持 PCM，参看 [AudioFrameType](#audioframetype)。

**返回值**
音频帧类型


<span id="IAudioFrame-release"></span>
### release
```java
void com.ss.bytertc.engine.utils.IAudioFrame.release()
```
释放音频帧。


# AttenuationType
```java
public enum com.ss.bytertc.engine.type.AttenuationType
```

空间音频音量随距离衰减模式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **ATTENUATION_TYPE_NONE(0)** | 不随距离衰减 |
| **ATTENUATION_TYPE_LINEAR(1)** | 线性衰减，音量随距离增大而线性减小 |
| **ATTENUATION_TYPE_EXPONENTIAL(2)** | 指数型衰减，音量随距离增大进行指数衰减 |


# AudioDeviceType
```java
public enum com.ss.bytertc.engine.type.AudioDeviceType
```

音频设备类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_DEVICE_TYPE_UNKNOWN(-1)** | 未知设备 |
| **AUDIO_DEVICE_TYPE_RENDER_DEVICE(0)** | 音频渲染设备 |
| **AUDIO_DEVICE_TYPE_CAPTURE_DEVICE(1)** | 音频采集设备类型 |
| **AUDIO_DEVICE_TYPE_SCREEN_CAPTURE_DEVICE(2)** | 屏幕流音频设备 |


# AudioProfileType
```java
public enum com.ss.bytertc.engine.type.AudioProfileType
```

音质档位


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_PROFILE_DEFAULT(0)** | 默认音质  <br><br/>服务器下发或客户端已设置的 [ChannelProfile](#channelprofile) 的音质配置 |
| **AUDIO_PROFILE_FLUENT(1)** | 流畅。  <br><br/>单声道，采样率为 16 kHz，编码码率为 32 Kbps。 <br><br/>流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。 |
| **AUDIO_PROFILE_STANDARD(2)** | 单声道标准音质。  <br><br/>采样率为 24 kHz，编码码率为 48 Kbps。 <br><br/>适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和狼人杀等游戏。 |
| **AUDIO_PROFILE_HD(3)** | 双声道音乐音质  <br><br/>采样率为 48 kHz，编码码率为 128 kbps。 <br><br/>超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。 <br><br/>游戏场景不建议使用。 |
| **AUDIO_PROFILE_STANDARD_STEREO(4)** | 双声道标准音质。采样率为 48 KHz，编码码率最大值为 80 Kbps |
| **AUDIO_PROFILE_HD_MONO(5)** | 单声道音乐音质。采样率为 48 kHz，编码码率最大值为 64 Kbps |


# AudioScenarioType
```java
public enum com.ss.bytertc.engine.type.AudioScenarioType
```

音频场景类型。
选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。
你可以调用 `setAudioScenario` 设置音频场景。
如果以下音频场景类型无法满足你的业务需要，请联系技术支持人员。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_SCENARIO_MUSIC(0)** | （默认）音乐场景。<br/>此场景适用于对音乐表现力有要求的场景，如音乐直播等。<br/>音频采集播放设备和采集播放状态，到音量类型的映射如下：<br/><table><br/><tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr><br/><tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr><br/><tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr><br/><tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr><br/></table> |
| **AUDIO_SCENARIO_HIGHQUALITY_COMMUNICATION(1)** | 高质量通话场景。<br/>此场景适用于对音乐表现力有要求，但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。<br/>此场景下，更倾向于使用媒体音量。由此，可能引起开关麦时音量突变。如不希望有此突变，请使用 `AUDIO_SCENARIO_HIGHQUALITY_CHAT`。<br/>此场景可以兼顾外放/使用蓝牙耳机时的音频体验，并避免使用蓝牙耳机时音量类型切换导致的听感突变。<br/>音频采集播放设备和采集播放状态，到音量类型的映射如下：<br/><table><br/><tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr><br/><tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr><br/><tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr><br/><tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr><br/></table> |
| **AUDIO_SCENARIO_COMMUNICATION(2)** | 纯通话音量场景。<br/>此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用通话音量。<br/>适用于需要频繁上下麦的通话或会议场景。<br/>此场景可以保持统一的音频模式，不会有音量突变的听感。<br/>此场景可以最大程度地消除回声，使通话清晰度达到最优。<br/>使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。<br/>但是，此场景会压低使用媒体音量进行播放的其他音频的音量，且音质会变差。 |
| **AUDIO_SCENARIO_MEDIA(3)** | 纯媒体场景。一般不建议使用。<br/>此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。<br/>外放通话时，可能出现回声和啸叫，请联系技术支持人员。 |
| **AUDIO_SCENARIO_GAME_STREAMING(4)** | 游戏媒体场景。<br/>此场景下，蓝牙耳机使用通话音量，其它设备使用媒体音量。<br/>若外放通话且无游戏音效消除优化时音质不理想，请联系技术支持人员。 |
| **AUDIO_SCENARIO_HIGHQUALITY_CHAT(5)** | 高质量畅聊场景。  <br><br/>此场景和 `AUDIO_SCENARIO_HIGHQUALITY_COMMUNICATION` 高度类似，唯一的差异在于：此场景下，在使用设备自带的麦克风和扬声器/听筒进行通话时，开关麦始终采用通话音量，不会引起音量类型突变。 <br><br/>音频采集播放设备和采集播放状态，到音量类型的映射如下：<br><br/><table><br/><tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr><br/><tr><td>设备自带麦克风和扬声器/听筒</td><td>通话音量</td><td>通话音量</td><td>/</td></tr><br/><tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr><br/><tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr><br/></table> |


# ChannelProfile
```java
public enum com.ss.bytertc.engine.type.ChannelProfile
```

房间模式<br>
根据所需场景，选择合适的房间模式，应用不同的音视频算法、视频参数和网络配置 <br>
调用 `setAudioProfile` 改变音频参数配置


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **CHANNEL_PROFILE_COMMUNICATION(0)** | 默认场景，通用模式 |
| **CHANNEL_PROFILE_GAME(2)** | 游戏语音模式，低功耗、低流量消耗。<br><br/>低端机在此模式下运行时，进行了额外的性能优化：<br><br/>+ 部分低端机型配置编码帧长 40/60 <br><br/>+ 部分低端机型关闭软件 3A 音频处理 <br><br/>增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。 |
| **CHANNEL_PROFILE_CLOUD_GAME(3)** | 云游戏模式。<br><br/>如果你的游戏场景需要低延迟的配置，使用此设置。<br><br/>此设置下，弱网抗性较差。 |
| **CHANNEL_PROFILE_LOW_LATENCY(4)** | 云渲染模式。超低延时配置。  <br><br/>如果你的应用并非游戏但又对延时要求较高时，选用此模式 <br><br/>该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br> |
| **CHANNEL_PROFILE_CHAT(5)** | 适用于 1 vs 1 音视频通话 |
| **CHANNEL_PROFILE_CHAT_ROOM(6)** | 适用于 3 人及以上纯语音通话。<br><br/>通话中，闭麦时为是媒体模式，上麦后切换为通话模式。 |
| **CHANNEL_PROFILE_LW_TOGETHER(7)** | 实现多端同步播放音视频，适用于 “一起看” 或 “一起听” 场景。<br><br/>该场景中，使用 RTC 信令同步播放进度，共享的音频内容不通过 RTC 进行传输。 |
| **CHANNEL_PROFILE_GAME_HD(8)** | 适用于对音质要求较高的游戏场景，优化音频 3A 策略，只通过媒体模式播放音频 |
| **CHANNEL_PROFILE_CO_HOST(9)** | 适用于直播中主播之间连麦的业务场景。<br><br/>该场景中，直播时通过 CDN，发起连麦 PK 时使用 RTC。 |
| **CHANNEL_PROFILE_INTERACTIVE_PODCAST(10)** | 适用于单主播和观众进行音视频互动的直播。通话模式，上下麦不会有模式切换，避免音量突变现象 |
| **CHANNEL_PROFILE_KTV(11)** | 线上 KTV 场景，音乐音质，低延迟<br><br/>使用 RTC 传输伴奏音乐，混音后的歌声，适合独唱或单通合唱 |
| **CHANNEL_PROFILE_CHORUS(12)** | 适合在线实时合唱场景，高音质，超低延迟。使用本配置前请联系技术支持进行协助完成其他配置。 |
| **CHANNEL_PROFILE_GAME_STREAMING(14)** | 适用于 1 vs 1 游戏串流，支持公网或局域网。 |
| **CHANNEL_PROFILE_LAN_LIVE_STREAMING(15)** | 适用于局域网的 1 对多视频直播，最高支持 8K， 60 帧/秒， 100 Mbps 码率<br><br/>需要在局域网配置私有化部署媒体服务器。 |
| **CHANNEL_PROFIEL_MEETING(16)** | 适用于云端会议中的个人设备。 |
| **CHANNEL_PROFILE_MEETING_ROOM(17)** | 适用于云端会议中的会议室终端设备，例如 Rooms，投屏盒子等。 |
| **CHANNEL_PROFILE_CLASSROOM(18)** | 适用于课堂互动，房间内所有成员都可以进行音视频互动<br><br/>当你的场景中需要同时互动的成员超过 10人时使用此模式 |


# ConnectionState
```java
public enum com.ss.bytertc.engine.type.ConnectionState
```

SDK 与 RTC 服务器连接状态。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **CONNECTION_STATE_DISCONNECTED(1)** | 连接断开超过 12s，此时 SDK 会尝试自动重连。 |
| **CONNECTION_STATE_CONNECTING(2)** | 首次请求建立连接，正在连接中。 |
| **CONNECTION_STATE_CONNECTED(3)** | 首次连接成功。 |
| **CONNECTION_STATE_RECONNECTING(4)** | 涵盖了以下情况：<br><br/>+ 首次连接时，10 秒内未连接成功; <br><br/>+ 连接成功后，断连 10 秒。自动重连中。 |
| **CONNECTION_STATE_RECONNECTED(5)** | 连接断开后，重连成功。 |
| **CONNECTION_STATE_LOST(6)** | 处于 `CONNECTION_STATE_DISCONNECTED` 状态超过 10 秒，且期间重连未成功。SDK 仍将继续尝试重连。 |
| **CONNECTION_STATE_FAILED(7)** | 连接失败，服务端状态异常。SDK 不会自动重连，请重新进房，或联系技术支持。 |


# EchoTestResult
```java
public enum com.ss.bytertc.engine.type.EchoTestResult
```

音视频回路测试结果


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **ECHO_TEST_SUCCESS(0)** | 接收到采集的音视频的回放，通话回路检测成功 |
| **ECHO_TEST_TIMEOUT(1)** | 测试超过 60s 仍未完成，已自动停止 |
| **ECHO_TEST_INTERVAL_SHORT(2)** | 上一次测试结束和下一次测试开始之间的时间间隔少于 5s |
| **ECHO_TEST_AUDIO_DEVICE_ERROR(3)** | 音频采集异常 |
| **ECHO_TEST_VIDEO_DEVICE_ERROR(4)** | 视频采集异常 |
| **ECHO_TEST_AUDIO_RECEIVE_ERROR(5)** | 音频接收异常 |
| **ECHO_TEST_VIDEO_RECEIVE_ERROR(6)** | 视频接收异常 |
| **ECHO_TEST_INTERNAL_ERROR(7)** | 内部错误，不可恢复 |


# FallbackOrRecoverReason
```java
public enum com.ss.bytertc.engine.type.FallbackOrRecoverReason
```

远端订阅流发生回退或恢复的原因


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **FALLBACK_OR_RECOVER_REASON_UNKNOWN(-1)** | 其他原因，非带宽和性能原因引起的回退或恢复。默认值 |
| **FALLBACK_OR_RECOVER_REASON_SUBSCRIBE_FALLBACK_BY_BANDWIDTH(0)** | 由带宽不足导致的订阅端音视频流回退。 |
| **FALLBACK_OR_RECOVER_REASON_SUBSCRIBE_FALLBACK_BY_PERFORMANCE(1)** | 由性能不足导致的订阅端音视频流回退。 |
| **FALLBACK_OR_RECOVER_REASON_SUBSCRIBE_RECOVER_BY_BANDWIDTH(2)** | 由带宽恢复导致的订阅端音视频流恢复。 |
| **FALLBACK_OR_RECOVER_REASON_SUBSCRIBE_RECOVER_BY_PERFORMANCE(3)** | 由性能恢复导致的订阅端音视频流恢复。 |
| **FALLBACK_OR_RECOVER_REASON_PUBLISH_FALLBACK_BY_BANDWIDTH(4)** | 由带宽不足导致的发布端音视频流回退。 |
| **FALLBACK_OR_RECOVER_REASON_PUBLISH_FALLBACK_BY_PERFORMANCE(5)** | 由性能不足导致的发布端音视频流回退。 |
| **FALLBACK_OR_RECOVER_REASON_PUBLISH_RECOVER_BY_BANDWIDTH(6)** | 由带宽恢复导致的发布端音视频流恢复。 |
| **FALLBACK_OR_RECOVER_REASON_PUBLISH_RECOVER_BY_PERFORMANCE(7)** | 由性能恢复导致的发布端音视频流恢复。 |


# FirstFramePlayState
```java
public enum com.ss.bytertc.engine.type.FirstFramePlayState
```

首帧播放状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **FIRST_FRAME_PLAY_STATE_PLAYING(0)** | 播放中 |
| **FIRST_FRAME_PLAY_STATE_PLAYED(1)** | 播放成功 |
| **FIRST_FRAME_PLAY_STATE_END(2)** | 播放失败 |


# FirstFrameSendState
```java
public enum com.ss.bytertc.engine.type.FirstFrameSendState
```

首帧发送状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **FIRST_FRAME_SEND_STATE_SENDING(0)** | 发送中 |
| **FIRST_FRAME_SEND_STATE_SENT(1)** | 发送成功 |
| **FIRST_FRAME_SEND_STAT_END(2)** | 发送失败 |


# LocalAudioStats
```java
public class com.ss.bytertc.engine.type.LocalAudioStats
```

本地音频流统计信息，统计周期为 2s 。  <br>
本地用户发布音频流成功后，SDK 会周期性地通过 `onLocalStreamStats` 通知用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [audioLossRate](#LocalAudioStats-audiolossrate) |
| **float** | [sendKBitrate](#LocalAudioStats-sendkbitrate) |
| **int** | [recordSampleRate](#LocalAudioStats-recordsamplerate) |
| **int** | [statsInterval](#LocalAudioStats-statsinterval) |
| **int** | [rtt](#LocalAudioStats-rtt) |
| **int** | [numChannels](#LocalAudioStats-numchannels) |
| **int** | [sentSampleRate](#LocalAudioStats-sentsamplerate) |


## 变量说明
<span id="LocalAudioStats-audiolossrate"></span>
### audioLossRate
```java
public float com.ss.bytertc.engine.type.LocalAudioStats.audioLossRate;
```
音频丢包率。此次统计周期内的音频上行丢包率，单位为 % ，取值范围为 [0, 1] 。  <br>


<span id="LocalAudioStats-sendkbitrate"></span>
### sendKBitrate
```java
public float com.ss.bytertc.engine.type.LocalAudioStats.sendKBitrate;
```
发送码率。此次统计周期内的音频发送码率，单位为 kbps 。  <br>


<span id="LocalAudioStats-recordsamplerate"></span>
### recordSampleRate
```java
public int com.ss.bytertc.engine.type.LocalAudioStats.recordSampleRate;
```
采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  <br>


<span id="LocalAudioStats-statsinterval"></span>
### statsInterval
```java
public int com.ss.bytertc.engine.type.LocalAudioStats.statsInterval;
```
统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
此字段用于设置回调的统计周期，默认设置为 2s 。


<span id="LocalAudioStats-rtt"></span>
### rtt
```java
public int com.ss.bytertc.engine.type.LocalAudioStats.rtt;
```
往返时延。单位为 ms 。  <br>


<span id="LocalAudioStats-numchannels"></span>
### numChannels
```java
public int com.ss.bytertc.engine.type.LocalAudioStats.numChannels;
```
音频声道数。  <br>


<span id="LocalAudioStats-sentsamplerate"></span>
### sentSampleRate
```java
public int com.ss.bytertc.engine.type.LocalAudioStats.sentSampleRate;
```
音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。  <br>



# LocalStreamStats
```java
public class com.ss.bytertc.engine.type.LocalStreamStats
```

本地音/视频流统计信息，统计周期为 2s 。  <br>
本地用户发布音/视频流成功后，SDK 会周期性地通过 `onLocalStreamStats` 通知本地用户发布的音/视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **LocalAudioStats** | [audioStats](#LocalStreamStats-audiostats) |
| **LocalVideoStats** | [videoStats](#LocalStreamStats-videostats) |
| **boolean** | [isScreen](#LocalStreamStats-isscreen) |


## 变量说明
<span id="LocalStreamStats-audiostats"></span>
### audioStats
```java
public LocalAudioStats com.ss.bytertc.engine.type.LocalStreamStats.audioStats;
```
本地设备发送音频流的统计信息，详见 [LocalAudioStats](#localaudiostats) 。


<span id="LocalStreamStats-videostats"></span>
### videoStats
```java
public LocalVideoStats com.ss.bytertc.engine.type.LocalStreamStats.videoStats;
```
本地设备发送视频流的统计信息，详见 [LocalVideoStats](#localvideostats) 。


<span id="LocalStreamStats-isscreen"></span>
### isScreen
```java
public boolean com.ss.bytertc.engine.type.LocalStreamStats.isScreen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。



# LocalVideoStats
```java
public class com.ss.bytertc.engine.type.LocalVideoStats
```

本地视频流统计信息，统计周期为 2s 。  <br>
本地用户发布视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
通知用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [sentKBitrate](#LocalVideoStats-sentkbitrate) |
| **int** | [inputFrameRate](#LocalVideoStats-inputframerate) |
| **int** | [sentFrameRate](#LocalVideoStats-sentframerate) |
| **int** | [encoderOutputFrameRate](#LocalVideoStats-encoderoutputframerate) |
| **int** | [rendererOutputFrameRate](#LocalVideoStats-rendereroutputframerate) |
| **int** | [statsInterval](#LocalVideoStats-statsinterval) |
| **float** | [videoLossRate](#LocalVideoStats-videolossrate) |
| **int** | [rtt](#LocalVideoStats-rtt) |
| **int** | [encodedBitrate](#LocalVideoStats-encodedbitrate) |
| **int** | [encodedFrameWidth](#LocalVideoStats-encodedframewidth) |
| **int** | [encodedFrameHeight](#LocalVideoStats-encodedframeheight) |
| **int** | [encodedFrameCount](#LocalVideoStats-encodedframecount) |
| **int** | [codecType](#LocalVideoStats-codectype) |
| **boolean** | [isScreen](#LocalVideoStats-isscreen) |


## 变量说明
<span id="LocalVideoStats-sentkbitrate"></span>
### sentKBitrate
```java
public float com.ss.bytertc.engine.type.LocalVideoStats.sentKBitrate;
```
发送码率。此次统计周期内实际发送的分辨率最大的视频流的发送码率，单位为 Kbps


<span id="LocalVideoStats-inputframerate"></span>
### inputFrameRate
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.inputFrameRate;
```
采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。


<span id="LocalVideoStats-sentframerate"></span>
### sentFrameRate
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.sentFrameRate;
```
发送帧率。此次统计周期内实际发送的分辨率最大的视频流的视频发送帧率，单位为 fps 。


<span id="LocalVideoStats-encoderoutputframerate"></span>
### encoderOutputFrameRate
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.encoderOutputFrameRate;
```
编码器输出帧率。当前编码器在此次统计周期内实际发送的分辨率最大的视频流的输出帧率，单位为 fps 。


<span id="LocalVideoStats-rendereroutputframerate"></span>
### rendererOutputFrameRate
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.rendererOutputFrameRate;
```
本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。


<span id="LocalVideoStats-statsinterval"></span>
### statsInterval
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.statsInterval;
```
统计间隔，单位为 ms 。
此字段用于设置回调的统计周期，默认设置为 2s 。


<span id="LocalVideoStats-videolossrate"></span>
### videoLossRate
```java
public float com.ss.bytertc.engine.type.LocalVideoStats.videoLossRate;
```
视频丢包率。此次统计周期内的视频上行丢包率，取值范围： [0，1] 。


<span id="LocalVideoStats-rtt"></span>
### rtt
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.rtt;
```
往返时延，单位为 ms 。


<span id="LocalVideoStats-encodedbitrate"></span>
### encodedBitrate
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.encodedBitrate;
```
视频编码码率。此次统计周期内的实际发送的分辨率最大的视频流视频编码码率，单位为 Kbps 。


<span id="LocalVideoStats-encodedframewidth"></span>
### encodedFrameWidth
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.encodedFrameWidth;
```
实际发送的分辨率最大的视频流的视频编码宽度，单位为 px 。


<span id="LocalVideoStats-encodedframeheight"></span>
### encodedFrameHeight
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.encodedFrameHeight;
```
实际发送的分辨率最大的视频流的视频编码高度，单位为 px 。


<span id="LocalVideoStats-encodedframecount"></span>
### encodedFrameCount
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.encodedFrameCount;
```
此次统计周期内实际发送的分辨率最大的视频流的发送的视频帧总数。


<span id="LocalVideoStats-codectype"></span>
### codecType
```java
public int com.ss.bytertc.engine.type.LocalVideoStats.codecType;
```
视频的编码类型，具体参考 [VideoCodecType](#videocodectype) 。


<span id="LocalVideoStats-isscreen"></span>
### isScreen
```java
public boolean com.ss.bytertc.engine.type.LocalVideoStats.isScreen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。



# LocalVideoStreamError
```java
public enum com.ss.bytertc.engine.type.LocalVideoStreamError
```

本地视频状态改变时的错误码


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **LOCAL_VIDEO_STREAM_ERROR_OK(0)** | 状态正常（本地视频状态改变正常时默认返回值） |
| **LOCAL_VIDEO_STREAM_ERROR_FAILURE(1)** | 本地视频流发布失败 |
| **LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION(2)** | 没有权限启动本地视频采集设备 |
| **LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY(3)** | 本地视频采集设备已被占用 |
| **LOCAL_VIDEO_STREAM_ERROR_DEVICE_NOT_FOUND(4)** | 本地视频采集设备不存在或已移除 |
| **LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE(5)** | 本地视频采集失败，建议检查采集设备是否正常工作 |
| **LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE(6)** | 本地视频编码失败 |
| **LOCAL_VIDEO_STREAM_ERROR_DEVICE_DISCONNECTED(7)** | 通话过程中本地视频采集设备被其他程序抢占，导致设备连接中断 |


# LocalVideoStreamState
```java
public enum com.ss.bytertc.engine.type.LocalVideoStreamState
```

本地视频流状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **LOCAL_VIDEO_STREAM_STATE_STOPPED(0)** | 本地视频采集停止状态（默认初始状态）<br/>本地视频采集关闭时回调该状态，对应错误码 [LocalVideoStreamError](#localvideostreamerror) 中的 `LOCAL_VIDEO_STREAM_ERROR_OK` |
| **LOCAL_VIDEO_STREAM_STATE_RECORDING(1)** | 本地视频采集设备启动成功<br/>本地视频采集开启时回调该状态，对应错误码 [LocalVideoStreamError](#localvideostreamerror) 中的 `LOCAL_VIDEO_STREAM_ERROR_OK` |
| **LOCAL_VIDEO_STREAM_STATE_ENCODING(2)** | 本地视频采集后，首帧编码成功<br/>本地视频首帧编码成功时回调该状态，对应错误码 [LocalVideoStreamError](#localvideostreamerror) 中的 `LOCAL_VIDEO_STREAM_ERROR_OK` |
| **LOCAL_VIDEO_STREAM_STATE_FAILED(3)** | 本地视频启动失败<br/>+ 本地视频采集设备启动失败，对应错误码 [LocalVideoStreamError](#localvideostreamerror) 中的 `LOCAL_VIDEO_STREAM_ERROR_FAILURE` <br><br/>+ 检测到没有视频采集设备权限，对应错误码 [LocalVideoStreamError](#localvideostreamerror) 中的 `LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION`  <br><br/>+ 视频编码失败，对应错误码 [LocalVideoStreamError](#localvideostreamerror) 中的 `LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE` |


# MediaDeviceError
```java
public class  com.ss.bytertc.engine.type.MediaDeviceError
```

媒体设备错误类型


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [MEDIA_DEVICE_ERROR_OK](#MediaDeviceError-media_device_error_ok) |
| **int** | [MEDIA_DEVICE_ERROR_NOPERMISSION](#MediaDeviceError-media_device_error_nopermission) |
| **int** | [MEDIA_DEVICE_ERROR_DEVICEBUSY](#MediaDeviceError-media_device_error_devicebusy) |
| **int** | [MEDIA_DEVICE_ERROR_DEVICEFAILURE](#MediaDeviceError-media_device_error_devicefailure) |
| **int** | [MEDIA_DEVICE_ERROR_DEVICENOTFOUND](#MediaDeviceError-media_device_error_devicenotfound) |
| **int** | [MEDIA_DEVICE_ERROR_DEVICEDISCONNECTED](#MediaDeviceError-media_device_error_devicedisconnected) |
| **int** | [MEDIA_DEVICE_ERROR_DEVICENOCALLBACK](#MediaDeviceError-media_device_error_devicenocallback) |
| **int** | [MEDIA_DEVICE_ERROR_UNSUPPORTFORMAT](#MediaDeviceError-media_device_error_unsupportformat) |


## 变量说明
<span id="MediaDeviceError-media_device_error_ok"></span>
### MEDIA_DEVICE_ERROR_OK
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceError.MEDIA_DEVICE_ERROR_OK = 0;
```
媒体设备正常


<span id="MediaDeviceError-media_device_error_nopermission"></span>
### MEDIA_DEVICE_ERROR_NOPERMISSION
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceError.MEDIA_DEVICE_ERROR_NOPERMISSION = 1;
```
没有权限启动媒体设备


<span id="MediaDeviceError-media_device_error_devicebusy"></span>
### MEDIA_DEVICE_ERROR_DEVICEBUSY
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceError.MEDIA_DEVICE_ERROR_DEVICEBUSY = 2;
```
媒体设备已经在使用中


<span id="MediaDeviceError-media_device_error_devicefailure"></span>
### MEDIA_DEVICE_ERROR_DEVICEFAILURE
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceError.MEDIA_DEVICE_ERROR_DEVICEFAILURE = 3;
```
媒体设备错误


<span id="MediaDeviceError-media_device_error_devicenotfound"></span>
### MEDIA_DEVICE_ERROR_DEVICENOTFOUND
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceError.MEDIA_DEVICE_ERROR_DEVICENOTFOUND = 4;
```
未找到指定的媒体设备


<span id="MediaDeviceError-media_device_error_devicedisconnected"></span>
### MEDIA_DEVICE_ERROR_DEVICEDISCONNECTED
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceError.MEDIA_DEVICE_ERROR_DEVICEDISCONNECTED = 5;
```
媒体设备被移除


<span id="MediaDeviceError-media_device_error_devicenocallback"></span>
### MEDIA_DEVICE_ERROR_DEVICENOCALLBACK
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceError.MEDIA_DEVICE_ERROR_DEVICENOCALLBACK = 6;
```
无采集数据。当媒体设备的预期行为是正常采集，但没有收到采集数据时，将收到该错误。


<span id="MediaDeviceError-media_device_error_unsupportformat"></span>
### MEDIA_DEVICE_ERROR_UNSUPPORTFORMAT
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceError.MEDIA_DEVICE_ERROR_UNSUPPORTFORMAT = 7;
```
设备采样率不支持



# MediaDeviceState
```java
public class  com.ss.bytertc.engine.type.MediaDeviceState
```

媒体设备状态<br>
通过 `onAudioDeviceStateChanged` 或 `onVideoDeviceStateChanged` 回调设备状态。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [MEDIA_DEVICE_STATE_STARTED](#MediaDeviceState-media_device_state_started) |
| **int** | [MEDIA_DEVICE_STATE_STOPPED](#MediaDeviceState-media_device_state_stopped) |
| **int** | [MEDIA_DEVICE_STATE_RUNTIMEERROR](#MediaDeviceState-media_device_state_runtimeerror) |
| **int** | [MEDIA_DEVICE_STATE_ADDED](#MediaDeviceState-media_device_state_added) |
| **int** | [MEDIA_DEVICE_STATE_REMOVED](#MediaDeviceState-media_device_state_removed) |
| **int** | [MEDIA_DEVICE_STATE_INTERRUPTION_BEGAN](#MediaDeviceState-media_device_state_interruption_began) |
| **int** | [MEDIA_DEVICE_STATE_INTERRUPTION_ENDED](#MediaDeviceState-media_device_state_interruption_ended) |


## 变量说明
<span id="MediaDeviceState-media_device_state_started"></span>
### MEDIA_DEVICE_STATE_STARTED
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceState.MEDIA_DEVICE_STATE_STARTED = 1;
```
设备开启采集


<span id="MediaDeviceState-media_device_state_stopped"></span>
### MEDIA_DEVICE_STATE_STOPPED
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceState.MEDIA_DEVICE_STATE_STOPPED = 2;
```
设备停止采集


<span id="MediaDeviceState-media_device_state_runtimeerror"></span>
### MEDIA_DEVICE_STATE_RUNTIMEERROR
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceState.MEDIA_DEVICE_STATE_RUNTIMEERROR = 3;
```
设备运行时错误<br>
例如，当媒体设备的预期行为是正常采集，但没有收到采集数据时，将回调该状态。


<span id="MediaDeviceState-media_device_state_added"></span>
### MEDIA_DEVICE_STATE_ADDED
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceState.MEDIA_DEVICE_STATE_ADDED = 10;
```
设备已插入


<span id="MediaDeviceState-media_device_state_removed"></span>
### MEDIA_DEVICE_STATE_REMOVED
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceState.MEDIA_DEVICE_STATE_REMOVED = 11;
```
设备被移除


<span id="MediaDeviceState-media_device_state_interruption_began"></span>
### MEDIA_DEVICE_STATE_INTERRUPTION_BEGAN
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceState.MEDIA_DEVICE_STATE_INTERRUPTION_BEGAN= 12;
```
系统通话打断了音视频通话。将在通话结束后自动恢复。


<span id="MediaDeviceState-media_device_state_interruption_ended"></span>
### MEDIA_DEVICE_STATE_INTERRUPTION_ENDED
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceState.MEDIA_DEVICE_STATE_INTERRUPTION_ENDED= 13;
```
音视频通话已从系统电话中恢复



# MediaDeviceWarning
```java
public class com.ss.bytertc.engine.type.MediaDeviceWarning
```

媒体设备警告


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [MEDIA_DEVICE_WARNING_OK](#MediaDeviceWarning-media_device_warning_ok) |
| **int** | [MEDIA_DEVICE_WARNING_OPERATION_DENIED](#MediaDeviceWarning-media_device_warning_operation_denied) |
| **int** | [MEDIA_DEVICE_WARNING_CAPTURE_SILENCE](#MediaDeviceWarning-media_device_warning_capture_silence) |
| **int** | [MEDIA_DEVICE_WARNING_ANDROID_SYS_SILENCE](#MediaDeviceWarning-media_device_warning_android_sys_silence) |
| **int** | [MEDIA_DEVICE_WARNING_ANDROID_SYS_SILENCE_DISAPPEAR](#MediaDeviceWarning-media_device_warning_android_sys_silence_disappear) |
| **int** | [MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_INVALID_SCENARIO](#MediaDeviceWarning-media_device_warning_set_audio_route_invalid_scenario) |
| **int** | [MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_NOT_EXISTS](#MediaDeviceWarning-media_device_warning_set_audio_route_not_exists) |
| **int** | [MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_FAILED_BY_PRIORITY](#MediaDeviceWarning-media_device_warning_set_audio_route_failed_by_priority) |
| **int** | [MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_NOT_VOIP_MODE](#MediaDeviceWarning-media_device_warning_set_audio_route_not_voip_mode) |
| **int** | [MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_DEVICE_NOT_START](#MediaDeviceWarning-media_device_warning_set_audio_route_device_not_start) |


## 变量说明
<span id="MediaDeviceWarning-media_device_warning_ok"></span>
### MEDIA_DEVICE_WARNING_OK
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_OK = 0;
```
无警告


<span id="MediaDeviceWarning-media_device_warning_operation_denied"></span>
### MEDIA_DEVICE_WARNING_OPERATION_DENIED
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_OPERATION_DENIED = 1;
```
非法设备操作。在使用外部设备时，调用了 SDK 内部设备 API。


<span id="MediaDeviceWarning-media_device_warning_capture_silence"></span>
### MEDIA_DEVICE_WARNING_CAPTURE_SILENCE
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_CAPTURE_SILENCE = 2;
```
采集到的数据为静音帧。


<span id="MediaDeviceWarning-media_device_warning_android_sys_silence"></span>
### MEDIA_DEVICE_WARNING_ANDROID_SYS_SILENCE
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_ANDROID_SYS_SILENCE = 3;
```
Android 特有的静音，系统层面的静音上报


<span id="MediaDeviceWarning-media_device_warning_android_sys_silence_disappear"></span>
### MEDIA_DEVICE_WARNING_ANDROID_SYS_SILENCE_DISAPPEAR
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_ANDROID_SYS_SILENCE_DISAPPEAR = 4;
```
Android 特有的静音消失


<span id="MediaDeviceWarning-media_device_warning_set_audio_route_invalid_scenario"></span>
### MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_INVALID_SCENARIO
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_INVALID_SCENARIO = 20;
```
当前 AudioScenario 不支持更改音频路由，设置音频路由失败


<span id="MediaDeviceWarning-media_device_warning_set_audio_route_not_exists"></span>
### MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_NOT_EXISTS
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_NOT_EXISTS = 21;
```
音频设备不存在，设置音频路由失败


<span id="MediaDeviceWarning-media_device_warning_set_audio_route_failed_by_priority"></span>
### MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_FAILED_BY_PRIORITY
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_FAILED_BY_PRIORITY = 22;
```
音频路由被系统或其他应用占用，设置音频路由失败


<span id="MediaDeviceWarning-media_device_warning_set_audio_route_not_voip_mode"></span>
### MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_NOT_VOIP_MODE
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_NOT_VOIP_MODE = 23;
```
当前非通话模式，不支持设置音频路由


<span id="MediaDeviceWarning-media_device_warning_set_audio_route_device_not_start"></span>
### MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_DEVICE_NOT_START
```java
public static final int com.ss.bytertc.engine.type.MediaDeviceWarning.MEDIA_DEVICE_WARNING_SET_AUDIO_ROUTE_DEVICE_NOT_START = 24;
```
音频设备未启动，设置音频路由失败



# MediaStreamType
```java
public enum com.ss.bytertc.engine.type.MediaStreamType
```

媒体流类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RTC_MEDIA_STREAM_TYPE_AUDIO(1)** | 只控制音频 |
| **RTC_MEDIA_STREAM_TYPE_VIDEO(2)** | 只控制视频 |
| **RTC_MEDIA_STREAM_TYPE_BOTH(3)** | 同时控制音频和视频 |


# MessageConfig
```java
public enum com.ss.bytertc.engine.type.MessageConfig
```

发送消息的可靠有序性


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **MessageConfigReliableOrdered (0)** | 低延时可靠有序消息 |
| **MessageConfigUnreliableOrdered (1)** | 超低延时有序消息 |
| **MessageConfigUnreliableUnordered (2)** | 超低延时无序消息 |


# NetworkDetectionLinkType
```java
public enum com.ss.bytertc.engine.type.NetworkDetectionLinkType
```

通话前探测链接的类型。  <br>
`onNetworkDetectionResult` 回调的参数类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **NetworkDetectionLinkTypeUp (0)** | 上行网络探测 |
| **NetworkDetectionLinkTypeDown (1)** | 下行网络探测 |


# NetworkDetectionStopReason
```java
public enum com.ss.bytertc.engine.type.NetworkDetectionStopReason
```

通话前探测的停止原因。  <br>
`onNetworkDetectionStopped` 回调的参数类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **NetworkDetectionStopReasonUser (0)** | 用户主动停止 |
| **NetworkDetectionStopReasonTimeout (1)** | 探测超过三分钟 |
| **NetworkDetectionStopReasonConnectionLost (2)** | 探测网络连接断开。<br><br/>当超过 12s 没有收到回复，SDK 将断开网络连接，并且不再尝试重连。 |
| **NetworkDetectionStopReasonStreaming (3)** | 本地开始推拉流，停止探测 |
| **NetworkDetectionStopReasonInnerErr (4)** | 网络探测失败，内部异常 |


# NetworkQuality
```java
public class com.ss.bytertc.engine.type.NetworkQuality
```

所属用户的媒体流网络质量。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [NETWORK_QUALITY_UNKNOWN](#NetworkQuality-network_quality_unknown) |
| **int** | [NETWORK_QUALITY_EXCELLENT](#NetworkQuality-network_quality_excellent) |
| **int** | [NETWORK_QUALITY_GOOD](#NetworkQuality-network_quality_good) |
| **int** | [NETWORK_QUALITY_POOR](#NetworkQuality-network_quality_poor) |
| **int** | [NETWORK_QUALITY_BAD](#NetworkQuality-network_quality_bad) |
| **int** | [NETWORK_QUALITY_VERY_BAD](#NetworkQuality-network_quality_very_bad) |
| **int** | [NETWORK_QUALITY_DISCONNECTED](#NetworkQuality-network_quality_disconnected) |


## 变量说明
<span id="NetworkQuality-network_quality_unknown"></span>
### NETWORK_QUALITY_UNKNOWN
```java
public static final int com.ss.bytertc.engine.type.NetworkQuality.NETWORK_QUALITY_UNKNOWN = 0;
```
媒体流网络质量未知。


<span id="NetworkQuality-network_quality_excellent"></span>
### NETWORK_QUALITY_EXCELLENT
```java
public static final int com.ss.bytertc.engine.type.NetworkQuality.NETWORK_QUALITY_EXCELLENT = 1;
```
媒体流网络质量极好。


<span id="NetworkQuality-network_quality_good"></span>
### NETWORK_QUALITY_GOOD
```java
public static final int com.ss.bytertc.engine.type.NetworkQuality.NETWORK_QUALITY_GOOD = 2;
```
媒体流网络质量好。


<span id="NetworkQuality-network_quality_poor"></span>
### NETWORK_QUALITY_POOR
```java
public static final int com.ss.bytertc.engine.type.NetworkQuality.NETWORK_QUALITY_POOR = 3;
```
媒体流网络质量较差但不影响沟通。


<span id="NetworkQuality-network_quality_bad"></span>
### NETWORK_QUALITY_BAD
```java
public static final int com.ss.bytertc.engine.type.NetworkQuality.NETWORK_QUALITY_BAD = 4;
```
媒体流网络质量差沟通不顺畅。


<span id="NetworkQuality-network_quality_very_bad"></span>
### NETWORK_QUALITY_VERY_BAD
```java
public static final int com.ss.bytertc.engine.type.NetworkQuality.NETWORK_QUALITY_VERY_BAD = 5;
```
媒体流网络质量非常差。


<span id="NetworkQuality-network_quality_disconnected"></span>
### NETWORK_QUALITY_DISCONNECTED
```java
public static final int com.ss.bytertc.engine.type.NetworkQuality.NETWORK_QUALITY_DISCONNECTED = 6;
```
12 s 内无应答，代表网络断开，将返回本枚举值。
你也可以通过 onConnectionStateChanged 监听 CONNECTION_STATE_DISCONNECTED(1) 感知网络断开。
更多网络状态信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。



# NetworkQualityStats
```java
public class com.ss.bytertc.engine.type.NetworkQualityStats
```

上行/下行网络质量


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [uid](#NetworkQualityStats-uid) |
| **double** | [fractionLost](#NetworkQualityStats-fractionlost) |
| **int** | [rtt](#NetworkQualityStats-rtt) |
| **int** | [totalBandwidth](#NetworkQualityStats-totalbandwidth) |
| **int** | [txQuality](#NetworkQualityStats-txquality) |
| **int** | [rxQuality](#NetworkQualityStats-rxquality) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **String** | [toString](#NetworkQualityStats-tostring) |


## 变量说明
<span id="NetworkQualityStats-uid"></span>
### uid
```java
public String com.ss.bytertc.engine.type.NetworkQualityStats.uid;
```
用户 id


<span id="NetworkQualityStats-fractionlost"></span>
### fractionLost
```java
public double com.ss.bytertc.engine.type.NetworkQualityStats.fractionLost;
```
本端的上行/下行的丢包率，范围 [0.0,1.0]
当 `uid` 为本地用户时，代表发布流的上行丢包率。
当 `uid` 为远端用户时，代表接收所有订阅流的下行丢包率。


<span id="NetworkQualityStats-rtt"></span>
### rtt
```java
public int com.ss.bytertc.engine.type.NetworkQualityStats.rtt;
```
当 `uid` 为本地用户时有效，客户端到服务端的往返延时（RTT），单位：ms


<span id="NetworkQualityStats-totalbandwidth"></span>
### totalBandwidth
```java
public int com.ss.bytertc.engine.type.NetworkQualityStats.totalBandwidth;
```
本端的音视频 RTP 包 2 秒内的平均传输速率，单位：bps
当 `uid` 为本地用户时，代表发送速率。
当 `uid` 为远端用户时，代表所有订阅流的接收速率。


<span id="NetworkQualityStats-txquality"></span>
### txQuality
```java
public int com.ss.bytertc.engine.type.NetworkQualityStats.txQuality;
```
上行网络质量分。范围 [0,5]，分数越高网络质量越差。


<span id="NetworkQualityStats-rxquality"></span>
### rxQuality
```java
public int com.ss.bytertc.engine.type.NetworkQualityStats.rxQuality;
```
下行网络质量分。范围 [0,5]，分数越高网络质量越差。



## 函数说明
<span id="NetworkQualityStats-tostring"></span>
### toString
```java
public String com.ss.bytertc.engine.type.NetworkQualityStats.toString()
```

# PauseResumeControlMediaType
```java
public enum com.ss.bytertc.engine.type.PauseResumeControlMediaType
```

暂停/恢复接收远端的媒体流类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RTC_PAUSE_RESUME_CONTROL_AUDIO** | 只控制音频，不影响视频 |
| **RTC_PAUSE_RESUME_CONTROL_VIDEO** | 只控制视频，不影响音频 |
| **RTC_PAUSE_RESUME_CONTROL_AUDIO_AND_VIDEO** | 同时控制音频和视频 |


# PerformanceAlarmMode
```java
public enum com.ss.bytertc.engine.type.PerformanceAlarmMode
```

性能回退的模式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **PERFORMANCE_ALARM_MODE_NORMAL** | 未开启发布性能回退 |
| **PERFORMANCE_ALARM_MODE_SIMULCAST** | 已开启发布性能回退 |


# PerformanceAlarmReason
```java
public enum com.ss.bytertc.engine.type.PerformanceAlarmReason
```

性能相关告警的原因


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **PERFORMANCE_ALARM_REASON_BANDWIDTH_FALLBACKED** | 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。 |
| **PERFORMANCE_ALARM_REASON_BANDWIDTH_RESUMED** | 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。 |
| **PERFORMANCE_ALARM_REASON_PERFORMANCE_FALLBACKED** | 如果未开启发送性能回退，收到此告警时，意味着性能不足；<br><br/>如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。 |
| **PERFORMANCE_ALARM_REASON_PERFORMANCE_RESUMED** | 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复；<br><br/>如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。 |


# ProblemFeedback
```java
public enum com.ss.bytertc.engine.type.ProblemFeedback
```

音视频质量反馈问题类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **PROBLEM_NONE(0, "No problem")** | 没有问题 |
| **PROBLEM_OTHER_MSG (1,"Other Issues")** | 其他问题 |
| **PROBLEM_AUDIO_NOT_CLEAR (1 << 1, "Sound is not clear")** | 有杂音 |
| **PROBLEM_VIDEO_NOT_CLEAR (1 << 2, "Video is not clear")** | 视频模糊 |
| **PROBLEM_SYNC (1 << 3, "Audio and video is not synchronized")** | 音视频不同步 |
| **PROBLEM_AUDIO_LAGGING (1 << 4, "Audio lagging")** | 音频卡顿 |
| **PROBLEM_VIDEO_DELAY (1 << 5, "Video Delay")** | 视频延迟 |
| **PROBLEM_DISCONNECT (1 << 6, "Disconnect")** | 连接失败 |
| **PROBLEM_NO_AUDIO (1 << 7, "No audio")** | 无声音 |
| **PROBLEM_NO_VIDEO (1 << 8, "No video")** | 无画面 |
| **PROBLEM_AUDIO_STRENGTH (1 << 9, "Too quiet")** | 声音过小 |
| **PROBLEM_ECHO (1 << 10, "Echo Noise")** | 有回声 |
| **PROBLEM_EAR_BACK_DELAY(1 << 11,"Ear back delay")** | 耳返延迟大 |


# PublishFallbackOption
```java
public enum com.ss.bytertc.engine.type.PublishFallbackOption
```

发布端音视频流回退选项


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **kPublishFallbackDisable(0)** | 上行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。 |
| **kPublishFallbackSimulcastSmallVideoOnly(1)** | 上行网络不佳或设备性能不足时，发布的视频流会从大流到小流依次降级，直到与当前网络性能匹配，具体降级规则参看[性能回退](https://www.volcengine.com/docs/6348/70137)文档。 |


# RangeAudioInfo
```java
public class com.ss.bytertc.engine.type.RangeAudioInfo
```

范围语音流信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [userId](#RangeAudioInfo-userid) |
| **int** | [factor](#RangeAudioInfo-factor) |


## 变量说明
<span id="RangeAudioInfo-userid"></span>
### userId
```java
public String com.ss.bytertc.engine.type.RangeAudioInfo.userId;
```
远端音频发布用户 ID


<span id="RangeAudioInfo-factor"></span>
### factor
```java
public int com.ss.bytertc.engine.type.RangeAudioInfo.factor;
```
本地用户听到该远端音频发布用户的衰减系数，范围 [0,100]，数值为 0 时表示远端用户音频音量为 0。



# RecordingErrorCode
```java
public enum com.ss.bytertc.engine.type.RecordingErrorCode
```

本地录制的错误码


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RECORDING_ERROR_CODE_OK(0)** | 录制正常 |
| **RECORDING_ERROR_CODE_NO_PERMISSION(-1)** | 没有文件写权限 |
| **RECORDING_ERROR_CODE_NOT_SUPPORT(-2)** | 当前版本 SDK 不支持本地录制功能，请联系技术支持人员 |
| **RECORDING_ERROR_CODE_NO_OTHER(-3)** | 其他异常 |


# RecordingFileType
```java
public enum com.ss.bytertc.engine.type.RecordingFileType
```

本地录制文件的存储格式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RECORDING_FILE_TYPE_AAC(0)** | aac 格式文件 |
| **RECORDING_FILE_TYPE_MP4(1)** | mp4 格式文件 |


# RecordingState
```java
public enum com.ss.bytertc.engine.type.RecordingState
```

本地录制的状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RECORDING_STATE_ERROE(0)** | 录制异常 |
| **RECORDING_STATE_PROCESSING(1)** | 录制进行中 |
| **RECORDING_STATE_SUCCESS(2)** | 录制文件保存成功，调用 `stopFileRecording` 结束录制之后才会收到该状态码。 |


# RecordingType
```java
public enum com.ss.bytertc.engine.type.RecordingType
```

本地录制的媒体类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RECORD_AUDIO_ONLY(0)** | 只录制音频 |
| **RECORD_VIDEO_ONLY(1)** | 只录制视频 |
| **RECORD_VIDEO_AND_AUDIO(2)** | 同时录制音频和视频 |


# RemoteAudioStats
```java
public class com.ss.bytertc.engine.type.RemoteAudioStats
```

远端音频流统计信息，统计周期为 2s。  <br>
本地用户订阅远端音频流成功后，SDK 会周期性地通过 `onRemoteStreamStats` 通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **float** | [audioLossRate](#RemoteAudioStats-audiolossrate) |
| **float** | [receivedKBitrate](#RemoteAudioStats-receivedkbitrate) |
| **int** | [stallCount](#RemoteAudioStats-stallcount) |
| **int** | [stallDuration](#RemoteAudioStats-stallduration) |
| **long** | [e2eDelay](#RemoteAudioStats-e2edelay) |
| **int** | [playoutSampleRate](#RemoteAudioStats-playoutsamplerate) |
| **int** | [statsInterval](#RemoteAudioStats-statsinterval) |
| **int** | [rtt](#RemoteAudioStats-rtt) |
| **int** | [total_rtt](#RemoteAudioStats-total_rtt) |
| **int** | [quality](#RemoteAudioStats-quality) |
| **int** | [jitterBufferDelay](#RemoteAudioStats-jitterbufferdelay) |
| **int** | [numChannels](#RemoteAudioStats-numchannels) |
| **int** | [receivedSampleRate](#RemoteAudioStats-receivedsamplerate) |
| **int** | [frozenRate](#RemoteAudioStats-frozenrate) |
| **int** | [concealedSamples](#RemoteAudioStats-concealedsamples) |
| **int** | [concealmentEvent](#RemoteAudioStats-concealmentevent) |
| **int** | [decSampleRate](#RemoteAudioStats-decsamplerate) |
| **int** | [decDuration](#RemoteAudioStats-decduration) |


## 变量说明
<span id="RemoteAudioStats-audiolossrate"></span>
### audioLossRate
```java
public float com.ss.bytertc.engine.type.RemoteAudioStats.audioLossRate;
```
音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  <br>


<span id="RemoteAudioStats-receivedkbitrate"></span>
### receivedKBitrate
```java
public float com.ss.bytertc.engine.type.RemoteAudioStats.receivedKBitrate;
```
接收码率。统计周期内的音频接收码率，单位为 kbps 。  <br>


<span id="RemoteAudioStats-stallcount"></span>
### stallCount
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.stallCount;
```
音频卡顿次数。统计周期内的卡顿次数。  <br>


<span id="RemoteAudioStats-stallduration"></span>
### stallDuration
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.stallDuration;
```
音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  <br>


<span id="RemoteAudioStats-e2edelay"></span>
### e2eDelay
```java
public long com.ss.bytertc.engine.type.RemoteAudioStats.e2eDelay;
```
用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>


<span id="RemoteAudioStats-playoutsamplerate"></span>
### playoutSampleRate
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.playoutSampleRate;
```
播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  <br>


<span id="RemoteAudioStats-statsinterval"></span>
### statsInterval
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.statsInterval;
```
统计间隔。此次统计周期的间隔，单位为 ms 。  <br>


<span id="RemoteAudioStats-rtt"></span>
### rtt
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.rtt;
```
客户端到服务端数据传输的往返时延，单位为 ms 。  <br>


<span id="RemoteAudioStats-total_rtt"></span>
### total_rtt
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.total_rtt;
```
发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  <br>


<span id="RemoteAudioStats-quality"></span>
### quality
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.quality;
```
远端用户发送的音频流质量。值含义参考 [NetworkQuality](#networkquality) 。  <br>


<span id="RemoteAudioStats-jitterbufferdelay"></span>
### jitterBufferDelay
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.jitterBufferDelay;
```
因引入 jitter buffer 机制导致的延时。单位为 ms 。  <br>


<span id="RemoteAudioStats-numchannels"></span>
### numChannels
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.numChannels;
```
音频声道数。  <br>


<span id="RemoteAudioStats-receivedsamplerate"></span>
### receivedSampleRate
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.receivedSampleRate;
```
音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  <br>


<span id="RemoteAudioStats-frozenrate"></span>
### frozenRate
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.frozenRate;
```
远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。


<span id="RemoteAudioStats-concealedsamples"></span>
### concealedSamples
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.concealedSamples;
```
音频丢包补偿(PLC) 样点总个数。  <br>


<span id="RemoteAudioStats-concealmentevent"></span>
### concealmentEvent
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.concealmentEvent;
```
音频丢包补偿(PLC) 累计次数。  <br>


<span id="RemoteAudioStats-decsamplerate"></span>
### decSampleRate
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.decSampleRate;
```
音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  <br>


<span id="RemoteAudioStats-decduration"></span>
### decDuration
```java
public int com.ss.bytertc.engine.type.RemoteAudioStats.decDuration;
```
此次订阅中，对远端音频流进行解码的累计耗时。单位为 s。



# RemoteStreamStats
```java
public class com.ss.bytertc.engine.type.RemoteStreamStats
```

用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats` 通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [uid](#RemoteStreamStats-uid) |
| **RemoteAudioStats** | [audioStats](#RemoteStreamStats-audiostats) |
| **RemoteVideoStats** | [videoStats](#RemoteStreamStats-videostats) |
| **boolean** | [isScreen](#RemoteStreamStats-isscreen) |


## 变量说明
<span id="RemoteStreamStats-uid"></span>
### uid
```java
public String com.ss.bytertc.engine.type.RemoteStreamStats.uid;
```
用户 ID 。音/视频来源的远端用户 ID 。  <br>


<span id="RemoteStreamStats-audiostats"></span>
### audioStats
```java
public RemoteAudioStats com.ss.bytertc.engine.type.RemoteStreamStats.audioStats;
```
远端音频流的统计信息，详见 [RemoteAudioStats](#remoteaudiostats)


<span id="RemoteStreamStats-videostats"></span>
### videoStats
```java
public RemoteVideoStats com.ss.bytertc.engine.type.RemoteStreamStats.videoStats;
```
远端视频流的统计信息，详见 [RemoteVideoStats](#remotevideostats)


<span id="RemoteStreamStats-isscreen"></span>
### isScreen
```java
public boolean com.ss.bytertc.engine.type.RemoteStreamStats.isScreen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。



# RemoteStreamSwitch
```java
public class com.ss.bytertc.engine.type.RemoteStreamSwitch
```

流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [uid](#RemoteStreamSwitch-uid) |
| **boolean** | [isScreen](#RemoteStreamSwitch-isscreen) |
| **int** | [before_video_index](#RemoteStreamSwitch-before_video_index) |
| **int** | [after_video_index](#RemoteStreamSwitch-after_video_index) |
| **boolean** | [before_enable](#RemoteStreamSwitch-before_enable) |
| **boolean** | [after_enable](#RemoteStreamSwitch-after_enable) |
| **FallbackOrRecoverReason** | [reason](#RemoteStreamSwitch-reason) |


## 变量说明
<span id="RemoteStreamSwitch-uid"></span>
### uid
```java
public String com.ss.bytertc.engine.type.RemoteStreamSwitch.uid;
```
订阅的音视频流的发布者的用户 ID


<span id="RemoteStreamSwitch-isscreen"></span>
### isScreen
```java
public boolean com.ss.bytertc.engine.type.RemoteStreamSwitch.isScreen;
```
是否是屏幕共享流


<span id="RemoteStreamSwitch-before_video_index"></span>
### before_video_index
```java
public int com.ss.bytertc.engine.type.RemoteStreamSwitch.before_video_index;
```
流切换前订阅视频流的分辨率对应的索引


<span id="RemoteStreamSwitch-after_video_index"></span>
### after_video_index
```java
public int com.ss.bytertc.engine.type.RemoteStreamSwitch.after_video_index;
```
流切换后订阅视频流的分辨率对应的索引


<span id="RemoteStreamSwitch-before_enable"></span>
### before_enable
```java
public boolean com.ss.bytertc.engine.type.RemoteStreamSwitch.before_enable;
```
流切换前是否有视频流


<span id="RemoteStreamSwitch-after_enable"></span>
### after_enable
```java
public boolean com.ss.bytertc.engine.type.RemoteStreamSwitch.after_enable;
```
流切换后是否有视频流


<span id="RemoteStreamSwitch-reason"></span>
### reason
```java
public FallbackOrRecoverReason com.ss.bytertc.engine.type.RemoteStreamSwitch.reason;
```
流切换原因，详见类型 [FallbackOrRecoverReason](#fallbackorrecoverreason) 。



# RemoteUserPriority
```java
public enum com.ss.bytertc.engine.type.RemoteUserPriority
```

远端用户优先级，在性能不足需要回退时，会优先回退优先级低的用户的音视频流。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **REMOTE_USER_PRIORITY_LOW(0)** | 用户优先级为低，默认值。 |
| **REMOTE_USER_PRIORITY_MEDIUM(100)** | 用户优先级为正常。 |
| **REMOTE_USER_PRIORITY_HIGH(200)** | 用户优先级为高。 |


# RemoteVideoState
```java
public enum com.ss.bytertc.engine.type.RemoteVideoState
```

远端视频流状态。状态改变时，会收到回调：[onRemoteVideoStateChanged](Android-callback.md#IRTCVideoEventHandler-onremotevideostatechanged)


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **REMOTE_VIDEO_STATE_STOPPED(0)** | 远端视频流默认初始状态<br/>在以下时机回调该状态：  <br><br/>+ 本地用户停止接收远端视频流，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_STATE_CHANGE_REASON_LOCAL_MUTED。  <br><br/>+ 远端用户停止发送视频流，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_STATE_CHANGE_REASON_REMOTE_MUTED。  <br><br/>+ 远端用户离开房间，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_STATE_CHANGE_REASON_REMOTE_OFFLINE。 |
| **REMOTE_VIDEO_STATE_STARTING(1)** | 本地用户已接收远端视频首包<br/>收到远端视频首包时回调该状态，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_STATE_CHANGE_REASON_LOCAL_UNMUTED。 |
| **REMOTE_VIDEO_STATE_DECODING(2)** | 远端视频流正在解码，正常播放<br/>在以下时机回调该状态： <br><br/>+ 成功解码远端视频首帧，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_STATE_CHANGE_REASON_LOCAL_UNMUTED。  <br><br/>+ 网络由阻塞恢复正常，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_STATE_CHANGE_REASON_NETWORK_RECOVERY。  <br><br/>+ 本地用户恢复接收远端视频流，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_STATE_CHANGE_REASON_LOCAL_UNMUTED。  <br><br/>+ 远端用户恢复发送视频流，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_STATE_CHANGE_REASON_NETWORK_CONGESTION。  <br> |
| **REMOTE_VIDEO_STATE_FROZEN(3)** | 远端视频流卡顿<br/>网络阻塞、丢包率大于40%时回调该状态，对应错误码 [RemoteVideoStateChangeReason](#remotevideostatechangereason) 中的 REMOTE_VIDEO_REASON_NETWORK_CONGESTION 。  <br> |
| **REMOTE_VIDEO_STATE_FAILED(4)** | 远端视频流播放失败 |


# RemoteVideoStateChangeReason
```java
public enum com.ss.bytertc.engine.type.RemoteVideoStateChangeReason
```

远端视频流状态改变的原因


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **REMOTE_VIDEO_STATE_CHANGE_REASON_INTERNAL(0)** | 内部原因 |
| **REMOTE_VIDEO_STATE_CHANGE_REASON_NETWORK_CONGESTION(1)** | 网络阻塞 |
| **REMOTE_VIDEO_STATE_CHANGE_REASON_NETWORK_RECOVERY(2)** | 网络恢复正常 |
| **REMOTE_VIDEO_STATE_CHANGE_REASON_LOCAL_MUTED(3)** | 本地用户停止接收远端视频流或本地用户禁用视频模块 |
| **REMOTE_VIDEO_STATE_CHANGE_REASON_LOCAL_UNMUTED(4)** | 本地用户恢复接收远端视频流或本地用户启用视频模块 |
| **REMOTE_VIDEO_STATE_CHANGE_REASON_REMOTE_MUTED(5)** | 远端用户停止发送视频流或远端用户禁用视频模块 |
| **REMOTE_VIDEO_STATE_CHANGE_REASON_REMOTE_UNMUTED(6)** | 远端用户恢复发送视频流或远端用户启用视频模块 |
| **REMOTE_VIDEO_STATE_CHANGE_REASON_REMOTE_OFFLINE(7)** | 远端用户离开房间<br/>状态转换参看 [onUserUnpublishStream](Android-callback.md#IRTCRoomEventHandler-onuserunpublishstream)/[onUserUnpublishScreen](Android-callback.md#IRTCRoomEventHandler-onuserunpublishscreen)。 |


# RemoteVideoStats
```java
public class com.ss.bytertc.engine.type.RemoteVideoStats
```

远端视频流统计信息，统计周期为 2s 。  <br>
本地用户订阅远端视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#RemoteVideoStats-width) |
| **int** | [height](#RemoteVideoStats-height) |
| **float** | [videoLossRate](#RemoteVideoStats-videolossrate) |
| **float** | [receivedKBitrate](#RemoteVideoStats-receivedkbitrate) |
| **int** | [decoderOutputFrameRate](#RemoteVideoStats-decoderoutputframerate) |
| **int** | [rendererOutputFrameRate](#RemoteVideoStats-rendereroutputframerate) |
| **int** | [stallCount](#RemoteVideoStats-stallcount) |
| **int** | [stallDuration](#RemoteVideoStats-stallduration) |
| **long** | [e2eDelay](#RemoteVideoStats-e2edelay) |
| **boolean** | [isScreen](#RemoteVideoStats-isscreen) |
| **int** | [statsInterval](#RemoteVideoStats-statsinterval) |
| **int** | [rtt](#RemoteVideoStats-rtt) |
| **int** | [frozenRate](#RemoteVideoStats-frozenrate) |
| **int** | [codecType](#RemoteVideoStats-codectype) |
| **int** | [videoIndex](#RemoteVideoStats-videoindex) |


## 变量说明
<span id="RemoteVideoStats-width"></span>
### width
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.width;
```
远端视频流宽度


<span id="RemoteVideoStats-height"></span>
### height
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.height;
```
远端视频流高度


<span id="RemoteVideoStats-videolossrate"></span>
### videoLossRate
```java
public float com.ss.bytertc.engine.type.RemoteVideoStats.videoLossRate;
```
视频丢包率。统计周期内的视频下行丢包率，单位为 % ，取值范围为 [0，1] 。


<span id="RemoteVideoStats-receivedkbitrate"></span>
### receivedKBitrate
```java
public float com.ss.bytertc.engine.type.RemoteVideoStats.receivedKBitrate;
```
接收码率。统计周期内的视频接收码率，单位为 kbps 。


<span id="RemoteVideoStats-decoderoutputframerate"></span>
### decoderOutputFrameRate
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.decoderOutputFrameRate;
```
解码器输出帧率。统计周期内的视频解码器输出帧率，单位 fps 。


<span id="RemoteVideoStats-rendereroutputframerate"></span>
### rendererOutputFrameRate
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.rendererOutputFrameRate;
```
渲染帧率。统计周期内的视频渲染帧率，单位 fps 。


<span id="RemoteVideoStats-stallcount"></span>
### stallCount
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.stallCount;
```
卡顿次数。统计周期内的卡顿次数。


<span id="RemoteVideoStats-stallduration"></span>
### stallDuration
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.stallDuration;
```
卡顿时长。统计周期内的视频卡顿总时长。单位 ms 。


<span id="RemoteVideoStats-e2edelay"></span>
### e2eDelay
```java
public long com.ss.bytertc.engine.type.RemoteVideoStats.e2eDelay;
```
用户体验级别的端到端延时，从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为毫秒


<span id="RemoteVideoStats-isscreen"></span>
### isScreen
```java
public boolean com.ss.bytertc.engine.type.RemoteVideoStats.isScreen;
```
所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


<span id="RemoteVideoStats-statsinterval"></span>
### statsInterval
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.statsInterval;
```
统计间隔，此次统计周期的间隔，单位为 ms 。  <br>
此字段用于设置回调的统计周期，目前设置为 2s 。


<span id="RemoteVideoStats-rtt"></span>
### rtt
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.rtt;
```
往返时延，单位为 ms 。


<span id="RemoteVideoStats-frozenrate"></span>
### frozenRate
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.frozenRate;
```
远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。


<span id="RemoteVideoStats-codectype"></span>
### codecType
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.codecType;
```
视频的编码类型，具体参考 [VideoCodecType](#videocodectype) 。


<span id="RemoteVideoStats-videoindex"></span>
### videoIndex
```java
public int com.ss.bytertc.engine.type.RemoteVideoStats.videoIndex;
```
对应多种分辨率的流的下标。



# RTCRoomStats
```java
public class com.ss.bytertc.engine.type.RTCRoomStats
```

通话相关的统计信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [totalDuration](#RTCRoomStats-totalduration) |
| **long** | [txBytes](#RTCRoomStats-txbytes) |
| **long** | [rxBytes](#RTCRoomStats-rxbytes) |
| **int** | [txKBitRate](#RTCRoomStats-txkbitrate) |
| **int** | [rxKBitRate](#RTCRoomStats-rxkbitrate) |
| **int** | [txAudioKBitRate](#RTCRoomStats-txaudiokbitrate) |
| **int** | [rxAudioKBitRate](#RTCRoomStats-rxaudiokbitrate) |
| **int** | [txVideoKBitRate](#RTCRoomStats-txvideokbitrate) |
| **int** | [rxVideoKBitRate](#RTCRoomStats-rxvideokbitrate) |
| **int** | [txScreenKBitRate](#RTCRoomStats-txscreenkbitrate) |
| **int** | [rxScreenKBitRate](#RTCRoomStats-rxscreenkbitrate) |
| **int** | [users](#RTCRoomStats-users) |
| **double** | [cpuTotalUsage](#RTCRoomStats-cputotalusage) |
| **double** | [cpuAppUsage](#RTCRoomStats-cpuappusage) |
| **double** | [txLostrate](#RTCRoomStats-txlostrate) |
| **double** | [rxLostrate](#RTCRoomStats-rxlostrate) |
| **int** | [rtt](#RTCRoomStats-rtt) |
| **int** | [txJitter](#RTCRoomStats-txjitter) |
| **int** | [rxJitter](#RTCRoomStats-rxjitter) |
| **int** | [txCellularKBitrate](#RTCRoomStats-txcellularkbitrate) |
| **int** | [rxCellularKBitrate](#RTCRoomStats-rxcellularkbitrate) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [reset](#RTCRoomStats-reset) |


## 变量说明
<span id="RTCRoomStats-totalduration"></span>
### totalDuration
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.totalDuration;
```
进房到退房之间累计时长，单位为 s


<span id="RTCRoomStats-txbytes"></span>
### txBytes
```java
public long com.ss.bytertc.engine.type.RTCRoomStats.txBytes;
```
本地用户的总发送字节数 (bytes)，累计值


<span id="RTCRoomStats-rxbytes"></span>
### rxBytes
```java
public long com.ss.bytertc.engine.type.RTCRoomStats.rxBytes;
```
本地用户的总接收字节数 (bytes)，累计值


<span id="RTCRoomStats-txkbitrate"></span>
### txKBitRate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.txKBitRate;
```
发送码率（kbps），获取该数据时的瞬时值


<span id="RTCRoomStats-rxkbitrate"></span>
### rxKBitRate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.rxKBitRate;
```
接收码率（kbps），获取该数据时的瞬时值


<span id="RTCRoomStats-txaudiokbitrate"></span>
### txAudioKBitRate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.txAudioKBitRate;
```
音频包的发送码率（kbps），获取该数据时的瞬时值


<span id="RTCRoomStats-rxaudiokbitrate"></span>
### rxAudioKBitRate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.rxAudioKBitRate;
```
音频接收码率（kbps），获取该数据时的瞬时值


<span id="RTCRoomStats-txvideokbitrate"></span>
### txVideoKBitRate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.txVideoKBitRate;
```
视频发送码率（kbps），获取该数据时的瞬时值


<span id="RTCRoomStats-rxvideokbitrate"></span>
### rxVideoKBitRate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.rxVideoKBitRate;
```
视频接收码率（kbps），获取该数据时的瞬时值


<span id="RTCRoomStats-txscreenkbitrate"></span>
### txScreenKBitRate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.txScreenKBitRate;
```
屏幕发送码率（kbps），获取该数据时的瞬时值


<span id="RTCRoomStats-rxscreenkbitrate"></span>
### rxScreenKBitRate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.rxScreenKBitRate;
```
屏幕接收码率（kbps），获取该数据时的瞬时值


<span id="RTCRoomStats-users"></span>
### users
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.users;
```
当前房间内的可见用户人数。


<span id="RTCRoomStats-cputotalusage"></span>
### cpuTotalUsage
```java
public double com.ss.bytertc.engine.type.RTCRoomStats.cpuTotalUsage;
```
当前系统的 CPU 使用率 (%)


<span id="RTCRoomStats-cpuappusage"></span>
### cpuAppUsage
```java
public double com.ss.bytertc.engine.type.RTCRoomStats.cpuAppUsage;
```
当前应用的 CPU 使用率 (%)


<span id="RTCRoomStats-txlostrate"></span>
### txLostrate
```java
public double com.ss.bytertc.engine.type.RTCRoomStats.txLostrate;
```
当前应用的上行丢包率，取值范围为 [0, 1]


<span id="RTCRoomStats-rxlostrate"></span>
### rxLostrate
```java
public double com.ss.bytertc.engine.type.RTCRoomStats.rxLostrate;
```
当前应用的下行丢包率，取值范围为 [0, 1]


<span id="RTCRoomStats-rtt"></span>
### rtt
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.rtt;
```
客户端到服务端数据传输的往返时延（单位 ms）


<span id="RTCRoomStats-txjitter"></span>
### txJitter
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.txJitter;
```
系统上行网络抖动（ms）


<span id="RTCRoomStats-rxjitter"></span>
### rxJitter
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.rxJitter;
```
系统下行网络抖动（ms）


<span id="RTCRoomStats-txcellularkbitrate"></span>
### txCellularKBitrate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.txCellularKBitrate;
```
蜂窝路径发送的码率 (kbps)，为获取该数据时的瞬时值


<span id="RTCRoomStats-rxcellularkbitrate"></span>
### rxCellularKBitrate
```java
public int com.ss.bytertc.engine.type.RTCRoomStats.rxCellularKBitrate;
```
蜂窝路径接收码率 (kbps)，为获取该数据时的瞬时值



## 函数说明
<span id="RTCRoomStats-reset"></span>
### reset
```java
public void com.ss.bytertc.engine.type.RTCRoomStats.reset()
```
重置所有的 [RTCRoomStats](#rtcroomstats) 成员变量的值，重新开始统计。


# RtcUser
```java
public class com.ss.bytertc.engine.type.RtcUser
```

用户信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [userId](#RtcUser-userid) |
| **String** | [metaData](#RtcUser-metadata) |


## 变量说明
<span id="RtcUser-userid"></span>
### userId
```java
public String com.ss.bytertc.engine.type.RtcUser.userId;
```
用户 id


<span id="RtcUser-metadata"></span>
### metaData
```java
public String com.ss.bytertc.engine.type.RtcUser.metaData;
```
元数据



# SEIStreamUpdateEvent
```java
public enum com.ss.bytertc.engine.type.SEIStreamUpdateEvent
```

黑帧视频流状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **SEIStreamUpdateEventStreamAdd (0)** | 远端用户发布黑帧视频流。  <br><br/>纯语音通话场景下，远端用户调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 发送 SEI 数据时，SDK 会自动发布一路黑帧视频流，并触发该回调。 |
| **SEIStreamUpdateEventStreamRemove (1)** | 远端黑帧视频流移除。该回调的触发时机包括：  <br><br/>+ 远端用户开启摄像头采集，由语音通话切换至视频通话，黑帧视频流停止发布；  <br><br/>+ 远端用户调用 [sendSEIMessage](Android-api.md#RTCVideo-sendseimessage) 后 1min 内未有 SEI 数据发送，黑帧视频流停止发布；  <br><br/>+ 远端用户调用 [setVideoSourceType](Android-api.md#RTCVideo-setvideosourcetype) 切换至自定义视频采集时，黑帧视频流停止发布。 |


# SourceWantedData
```java
public class com.ss.bytertc.engine.type.SourceWantedData
```

性能回退相关数据


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#SourceWantedData-width) |
| **int** | [height](#SourceWantedData-height) |
| **int** | [frameRate](#SourceWantedData-framerate) |


## 变量说明
<span id="SourceWantedData-width"></span>
### width
```java
public int com.ss.bytertc.engine.type.SourceWantedData.width;
```
如果未开启发送性能回退，此值表示推荐的视频输入宽度；<br>
如果开启了发送性能回退，此值表示当前推流的最大宽度。


<span id="SourceWantedData-height"></span>
### height
```java
public int com.ss.bytertc.engine.type.SourceWantedData.height;
```
如果未开启发送性能回退，此值表示推荐的视频输入高度；<br>
如果开启了发送性能回退，此值表示当前推流的最大高度。


<span id="SourceWantedData-framerate"></span>
### frameRate
```java
public int com.ss.bytertc.engine.type.SourceWantedData.frameRate;
```
如果未开启发送性能回退，此值表示推荐的视频输入帧率，单位 fps；<br>
如果开启了发送性能回退，此值表示当前推流的最大帧率，单位 fps。



# StreamRemoveReason
```java
public enum com.ss.bytertc.engine.type.StreamRemoveReason
```

房间内远端流移除原因。  <br>



## 枚举值

| 类型 | 说明 |
| --- | --- |
| **STREAM_REMOVE_REASON_UNPUBLISH(0)** | 远端用户停止发布流。  <br> |
| **STREAM_REMOVE_REASON_PUBLISH_FAILED(1)** | 远端用户发布流失败。  <br> |
| **STREAM_REMOVE_REASON_KEEP_LIVE_FAILED(2)** | 保活失败。  <br> |
| **STREAM_REMOVE_REASON_CLIENT_DISCONNECTED(3)** | 远端用户断网。  <br> |
| **STREAM_REMOVE_REASON_REPUBLISH(4)** | 远端用户重新发布流。  <br> |
| **STREAM_REMOVE_REASON_OTHER(5)** | 其他原因。  <br> |


# SubscribeFallbackOptions
```java
public enum com.ss.bytertc.engine.type.SubscribeFallbackOptions
```

订阅端音视频流回退选项。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **SUBSCRIBE_FALLBACK_OPTIONS_DISABLED(0)** | 下行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。 |
| **SUBSCRIBE_FALLBACK_OPTIONS_STREAM_LOW(1)** | 下行网络不佳或设备性能不足时，对视频流做回退处理，具体降级规则参看[音视频流回退](70137)。 <br>该设置仅对发布端调用 [enableSimulcastMode](Android-api.md#RTCVideo-enablesimulcastmode) 开启发送多路流功能的情况生效。 |
| **SUBSCRIBE_FALLBACK_OPTIONS_AUDIO_ONLY(2)** | 下行网络不佳或设备性能不足时，先对视频流做回退处理。当网络状况不满足接收弱流时，则自动取消接收视频，仅接收音频。<br>该设置仅对发布端调用 [enableSimulcastMode](Android-api.md#RTCVideo-enablesimulcastmode) 开启发送多路流功能的情况生效。 |


# SubscribeMediaType
```java
public enum com.ss.bytertc.engine.type.SubscribeMediaType
```

订阅的媒体类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **RTC_SUBSCRIBE_MEDIA_TYPE_NONE** | 既不订阅音频，也不订阅视频 |
| **RTC_SUBSCRIBE_MEDIA_TYPE_AUDIO_ONLY** | 只订阅音频，不订阅视频 |
| **RTC_SUBSCRIBE_MEDIA_TYPE_VIDEO_ONLY** | 只订阅视频，不订阅音频 |
| **RTC_SUBSCRIBE_MEDIA_TYPE_AUDIO_AND_VIDEO** | 同时订阅音频和视频 |


# TorchState
```java
public enum com.ss.bytertc.engine.type.TorchState
```

相机闪光灯状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **TORCH_STATE_OFF(0)** | 关闭 |
| **TORCH_STATE_ON(1)** | 打开 |


# UserOnlineStatus
```java
public class com.ss.bytertc.engine.type.UserOnlineStatus
```

用户在线状态


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [USER_ONLINE_STATUS_OFFLINE](#UserOnlineStatus-user_online_status_offline) |
| **int** | [USER_ONLINE_STATUS_ONLINE](#UserOnlineStatus-user_online_status_online) |
| **int** | [USER_ONLINE_STATUS_UNREACHABLE](#UserOnlineStatus-user_online_status_unreachable) |


## 变量说明
<span id="UserOnlineStatus-user_online_status_offline"></span>
### USER_ONLINE_STATUS_OFFLINE
```java
public static final int com.ss.bytertc.engine.type.UserOnlineStatus.USER_ONLINE_STATUS_OFFLINE = 0;
```
对端用户离线  <br>
对端用户已经调用 `logout`，或者没有调用 `login` 进行登录


<span id="UserOnlineStatus-user_online_status_online"></span>
### USER_ONLINE_STATUS_ONLINE
```java
public static final int com.ss.bytertc.engine.type.UserOnlineStatus.USER_ONLINE_STATUS_ONLINE = 1;
```
对端用户在线  <br>
对端用户调用 `login` 登录，并且连接状态正常。


<span id="UserOnlineStatus-user_online_status_unreachable"></span>
### USER_ONLINE_STATUS_UNREACHABLE
```java
public static final int com.ss.bytertc.engine.type.UserOnlineStatus.USER_ONLINE_STATUS_UNREACHABLE = 2;
```
无法获取对端用户在线状态  <br>
发生级联错误、对端用户在线状态异常时返回



# VideoDeviceType
```java
public enum com.ss.bytertc.engine.type.VideoDeviceType
```

当前视频设备类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **VIDEO_DEVICE_TYPE_UNKNOWN(-1)** | 未知设备类型 |
| **VIDEO_DEVICE_TYPE_RENDER_DEVICE(0)** | 视频渲染设备类型 |
| **VIDEO_DEVICE_TYPE_CAPTURE_DEVICE(1)** | 视频采集设备类型 |
| **VIDEO_DEVICE_TYPE_SCREEN_CAPTURE_DEVICE(2)** | 屏幕流视频设备 |


# VoiceChangerType
```java
public enum com.ss.bytertc.engine.type.VoiceChangerType
```

变声特效类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **VOICE_CHANGER_ORIGINAL(0)** | 原声，不含特效 |
| **VOICE_CHANGER_GIANT(1)** | 巨人 |
| **VOICE_CHANGER_CHIPMUNK(2)** | 花栗鼠 |
| **VOICE_CHANGER_MINIONST(3)** | 小黄人 |
| **VOICE_CHANGER_VIBRATO(4)** | 颤音 |
| **VOICE_CHANGER_ROBOT(5)** | 机器人 |


# VoiceReverbType
```java
public enum com.ss.bytertc.engine.type.VoiceReverbType
```

混响特效类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **VOICE_REVERB_ORIGINAL(0)** | 原声，不含特效 |
| **VOICE_REVERB_ECHO(1)** | 回声 |
| **VOICE_REVERB_CONCERT(2)** | 演唱会 |
| **VOICE_REVERB_ETHEREAL(3)** | 空灵 |
| **VOICE_REVERB_KTV(4)** | KTV |
| **VOICE_REVERB_STUDIO(5)** | 录音棚 |


# ByteWatermark
```java
public class com.ss.bytertc.engine.video.ByteWatermark
```

水印图片相对视频流的位置和大小。


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
```java
public float com.ss.bytertc.engine.video.ByteWatermark.x;
```
水印图片相对视频流左上角的横向偏移与视频流宽度的比值，取值范围为 [0,1)。


<span id="ByteWatermark-y"></span>
### y
```java
public float com.ss.bytertc.engine.video.ByteWatermark.y;
```
水印图片相对视频流左上角的纵向偏移与视频流高度的比值，取值范围为 [0,1)。


<span id="ByteWatermark-width"></span>
### width
```java
public  float com.ss.bytertc.engine.video.ByteWatermark.width;
```
水印图片宽度与视频流宽度的比值，取值范围 [0,1)。


<span id="ByteWatermark-height"></span>
### height
```java
public float com.ss.bytertc.engine.video.ByteWatermark.height;
```
水印图片高度与视频流高度的比值，取值范围为 [0,1)。



# FaceDetectionResult
```java
public class com.ss.bytertc.engine.video.FaceDetectionResult
```

人脸检测结果


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [detectResult](#FaceDetectionResult-detectresult) |
| **int** | [imageWidth](#FaceDetectionResult-imagewidth) |
| **int** | [imageHeight](#FaceDetectionResult-imageheight) |
| **Rectangle[]** | [faces](#FaceDetectionResult-faces) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **String** | [toString](#FaceDetectionResult-tostring) |


## 变量说明
<span id="FaceDetectionResult-detectresult"></span>
### detectResult
```java
public int com.ss.bytertc.engine.video.FaceDetectionResult.detectResult;
```
人脸检测结果 <br>

+ 0：检测成功 <br>
+ !0：检测失败。详见[CV 错误码](https://www.volcengine.com/docs/6705/102042)。


<span id="FaceDetectionResult-imagewidth"></span>
### imageWidth
```java
public int com.ss.bytertc.engine.video.FaceDetectionResult.imageWidth;
```
原始图片宽度(px)


<span id="FaceDetectionResult-imageheight"></span>
### imageHeight
```java
public int com.ss.bytertc.engine.video.FaceDetectionResult.imageHeight;
```
原始图片高度(px)


<span id="FaceDetectionResult-faces"></span>
### faces
```java
public Rectangle[] com.ss.bytertc.engine.video.FaceDetectionResult.faces;
```
识别到人脸的矩形框。数组的长度和检测到的人脸数量一致。参看 [Rectangle](#rectangle)。



## 函数说明
<span id="FaceDetectionResult-tostring"></span>
### toString
```java
public String com.ss.bytertc.engine.video.FaceDetectionResult.toString()
```

# IVideoSink
```java
public interface com.ss.bytertc.engine.video.IVideoSink
```

自定义视频渲染器。


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **void** | [onFrame](#IVideoSink-onframe) |


## 函数说明
<span id="IVideoSink-onframe"></span>
### onFrame
```java
void com.ss.bytertc.engine.video.IVideoSink.onFrame(
    VideoFrame frame)
```
视频帧回调

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| frame | **VideoFrame** | 视频帧结构类，参看 [VideoFrame](#videoframe) |


# PixelFormat
```java
public @interface com.ss.bytertc.engine.video.IVideoSink.PixelFormat
```

视频帧数据格式


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [Original](#PixelFormat-original) |
| **int** | [I420](#PixelFormat-i420) |


## 变量说明
<span id="PixelFormat-original"></span>
### Original
```java
int com.ss.bytertc.engine.video.IVideoSink.PixelFormat.Original = 0;
```
原始视频帧格式


<span id="PixelFormat-i420"></span>
### I420
```java
int com.ss.bytertc.engine.video.IVideoSink.PixelFormat.I420 = 1;
```
I420数据格式



# Rectangle
```java
public class com.ss.bytertc.engine.video.Rectangle
```

矩形区域


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [x](#Rectangle-x) |
| **int** | [y](#Rectangle-y) |
| **int** | [width](#Rectangle-width) |
| **int** | [height](#Rectangle-height) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **Rectangle** | [Rectangle](#Rectangle-rectangle) |
| **String** | [toString](#Rectangle-tostring) |


## 变量说明
<span id="Rectangle-x"></span>
### x
```java
public int com.ss.bytertc.engine.video.Rectangle.x = 0;
```
矩形区域左上角的 x 坐标


<span id="Rectangle-y"></span>
### y
```java
public int com.ss.bytertc.engine.video.Rectangle.y = 0;
```
矩形区域左上角的 y 坐标


<span id="Rectangle-width"></span>
### width
```java
public int com.ss.bytertc.engine.video.Rectangle.width = 0;
```
矩形宽度(px)


<span id="Rectangle-height"></span>
### height
```java
public int com.ss.bytertc.engine.video.Rectangle.height = 0;
```
矩形高度(px)



## 函数说明
<span id="Rectangle-rectangle"></span>
### Rectangle
```java
public com.ss.bytertc.engine.video.Rectangle.Rectangle(
    int x,
    int y,
    int w,
    int h)
```

<span id="Rectangle-tostring"></span>
### toString
```java
public String com.ss.bytertc.engine.video.Rectangle.toString()
```

# RTCWatermarkConfig
```java
public class com.ss.bytertc.engine.video.RTCWatermarkConfig
```

水印参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **boolean** | [visibleInPreview](#RTCWatermarkConfig-visibleinpreview) |
| **ByteWatermark** | [positionInLandscapeMode](#RTCWatermarkConfig-positioninlandscapemode) |
| **ByteWatermark** | [positionInPortraitMode](#RTCWatermarkConfig-positioninportraitmode) |


## 变量说明
<span id="RTCWatermarkConfig-visibleinpreview"></span>
### visibleInPreview
```java
public boolean com.ss.bytertc.engine.video.RTCWatermarkConfig.visibleInPreview = true;
```
水印是否在视频预览中可见，默认可见。


<span id="RTCWatermarkConfig-positioninlandscapemode"></span>
### positionInLandscapeMode
```java
public ByteWatermark com.ss.bytertc.engine.video.RTCWatermarkConfig.positionInLandscapeMode;
```
横屏时的水印位置和大小，参看 [ByteWatermark](#bytewatermark)。


<span id="RTCWatermarkConfig-positioninportraitmode"></span>
### positionInPortraitMode
```java
public ByteWatermark com.ss.bytertc.engine.video.RTCWatermarkConfig.positionInPortraitMode;
```
竖屏时的水印位置和大小，参看 [ByteWatermark](#bytewatermark)。



# ScreenSharingParameters
```java
public class com.ss.bytertc.engine.video.ScreenSharingParameters
```

屏幕共享的编码参数配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [maxWidth](#ScreenSharingParameters-maxwidth) |
| **int** | [maxHeight](#ScreenSharingParameters-maxheight) |
| **int** | [frameRate](#ScreenSharingParameters-framerate) |
| **int** | [bitrate](#ScreenSharingParameters-bitrate) |


## 变量说明
<span id="ScreenSharingParameters-maxwidth"></span>
### maxWidth
```java
public int com.ss.bytertc.engine.video.ScreenSharingParameters.maxWidth = 0;
```
屏幕采集编码最大宽度,


<span id="ScreenSharingParameters-maxheight"></span>
### maxHeight
```java
public int com.ss.bytertc.engine.video.ScreenSharingParameters.maxHeight = 0;
```
屏幕采集编码最大高度


<span id="ScreenSharingParameters-framerate"></span>
### frameRate
```java
public int com.ss.bytertc.engine.video.ScreenSharingParameters.frameRate = 15;
```
屏幕采集编码帧率, 单位 fps


<span id="ScreenSharingParameters-bitrate"></span>
### bitrate
```java
public int com.ss.bytertc.engine.video.ScreenSharingParameters.bitrate = -1;
```
屏幕采集编码码率, `-1` 为自动码率, SDK 会根据宽高信息选择合适的码率，单位 kbps



# VideoCaptureConfig
```java
public class com.ss.bytertc.engine.video.VideoCaptureConfig
```

视频采集配置


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
```java
public CapturePreference com.ss.bytertc.engine.video.VideoCaptureConfig.capturePreference = CapturePreference.AUTO;
```
视频采集模式，参看 [CapturePreference](#capturepreference-2)。


<span id="VideoCaptureConfig-width"></span>
### width
```java
public int com.ss.bytertc.engine.video.VideoCaptureConfig.width;
```
视频采集分辨率的宽度，单位：px。


<span id="VideoCaptureConfig-height"></span>
### height
```java
public int com.ss.bytertc.engine.video.VideoCaptureConfig.height;
```
视频采集分辨率的高度，单位：px。


<span id="VideoCaptureConfig-framerate"></span>
### frameRate
```java
public int com.ss.bytertc.engine.video.VideoCaptureConfig.frameRate;
```
视频采集帧率，单位：fps。



# CapturePreference
```java
public enum com.ss.bytertc.engine.video.VideoCaptureConfig.CapturePreference
```

视频采集模式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUTO(0)** | （默认）自动设置采集参数。<br/>SDK在开启采集时根据服务端下发的采集配置结合编码参数设置最佳采集参数。 |
| **MANUAL(1)** | 手动设置采集参数，包括采集分辨率、帧率。 |
| **AUTO_PERFORMANCE(2)** | 采集参数与编码参数一致，即在 [setVideoEncoderConfig](Android-api.md#RTCVideo-setvideoencoderconfig) 中设置的参数。 |


# VideoEncoderConfiguration
```java
public class com.ss.bytertc.engine.video.VideoEncoderConfiguration
```

视频编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **VideoDimensions** | [dimensions](#VideoEncoderConfiguration-dimensions) |
| **FrameRate** | [frameRate](#VideoEncoderConfiguration-framerate) |
| **int** | [kBitrate](#VideoEncoderConfiguration-kbitrate) |
| **OrientationMode** | [orientationMode](#VideoEncoderConfiguration-orientationmode) |


## 变量说明
<span id="VideoEncoderConfiguration-dimensions"></span>
### dimensions
```java
public VideoDimensions com.ss.bytertc.engine.video.VideoEncoderConfiguration.dimensions;
```
视频编码像素


<span id="VideoEncoderConfiguration-framerate"></span>
### frameRate
```java
public FrameRate com.ss.bytertc.engine.video.VideoEncoderConfiguration.frameRate;
```
视频编码帧率


<span id="VideoEncoderConfiguration-kbitrate"></span>
### kBitrate
```java
public int com.ss.bytertc.engine.video.VideoEncoderConfiguration.kBitrate;
```
视频编码码率


<span id="VideoEncoderConfiguration-orientationmode"></span>
### orientationMode
```java
public OrientationMode com.ss.bytertc.engine.video.VideoEncoderConfiguration.orientationMode;
```
视频编码方向模式



# OrientationMode
```java
public static enum com.ss.bytertc.engine.video.VideoEncoderConfiguration.OrientationMode
```

视频编码的方向模式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **ORIENTATION_MODE_ADAPTIVE(0)** | 视频输出方向与采集方向一致。 |
| **ORIENTATION_MODE_FIXED_LANDSCAPE(1)** | 固定横屏输出视频。若采集到的视频是竖屏模式，则视频编码器会对其进行裁剪。 |
| **ORIENTATION_MODE_FIXED_PORTRAIT(2)** | 固定竖屏输出视频。若采集到的视频是横屏模式，则视频编码器会对其进行裁剪。 |


# VideoFrame
```java
public abstract class com.ss.bytertc.engine.video.VideoFrame
```

视频帧


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **synchronized void** | [setReleaseCallback](#VideoFrame-setreleasecallback) |
| **synchronized boolean** | [hasReleaseCallback](#VideoFrame-hasreleasecallback) |
| **abstract VideoFrameType** | [getFrameType](#VideoFrame-getframetype) |
| **abstract VideoPixelFormat** | [getPixelFormat](#VideoFrame-getpixelformat) |
| **abstract VideoContentType** | [getContentType](#VideoFrame-getcontenttype) |
| **abstract long** | [getTimeStampUs](#VideoFrame-gettimestampus) |
| **abstract int** | [getWidth](#VideoFrame-getwidth) |
| **abstract int** | [getHeight](#VideoFrame-getheight) |
| **abstract VideoRotation** | [getRotation](#VideoFrame-getrotation) |
| **abstract ColorSpace** | [getColorSpace](#VideoFrame-getcolorspace) |
| **abstract CameraId** | [getCameraId](#VideoFrame-getcameraid) |
| **abstract int** | [getNumberOfPlanes](#VideoFrame-getnumberofplanes) |
| **abstract ByteBuffer** | [getPlaneData](#VideoFrame-getplanedata) |
| **abstract int** | [getPlaneStride](#VideoFrame-getplanestride) |
| **abstract ByteBuffer** | [getExternalDataInfo](#VideoFrame-getexternaldatainfo) |
| **abstract ByteBuffer** | [getSupplementaryInfo](#VideoFrame-getsupplementaryinfo) |
| **abstract int** | [getTextureID](#VideoFrame-gettextureid) |
| **abstract float[]** | [getTextureMatrix](#VideoFrame-gettexturematrix) |
| **abstract EGLContext** | [getEGLContext](#VideoFrame-geteglcontext) |
| **synchronized void** | [retain](#VideoFrame-retain) |
| **synchronized void** | [release](#VideoFrame-release) |


## 函数说明
<span id="VideoFrame-setreleasecallback"></span>
### setReleaseCallback
```java
public synchronized void com.ss.bytertc.engine.video.VideoFrame.setReleaseCallback(
    Runnable releaseCallback)
```
设置视频帧释放回调，当视频帧的引用计数归 0 时，会执行 releaseCallback

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| releaseCallback | **Runnable** | 视频帧释放回调 |


<span id="VideoFrame-hasreleasecallback"></span>
### hasReleaseCallback
```java
public synchronized boolean com.ss.bytertc.engine.video.VideoFrame.hasReleaseCallback()
```
用于检查当前的视频帧是否已设置 releaseCallback

**返回值**

+ true：是  
+ false：否


<span id="VideoFrame-getframetype"></span>
### getFrameType
```java
public abstract VideoFrameType com.ss.bytertc.engine.video.VideoFrame.getFrameType()
```
获取视频帧类型，参看 [VideoFrameType](#videoframetype)


<span id="VideoFrame-getpixelformat"></span>
### getPixelFormat
```java
public abstract VideoPixelFormat com.ss.bytertc.engine.video.VideoFrame.getPixelFormat()
```
获取视频帧格式，参看 [VideoPixelFormat](#videopixelformat)


<span id="VideoFrame-getcontenttype"></span>
### getContentType
```java
public abstract VideoContentType com.ss.bytertc.engine.video.VideoFrame.getContentType()
```
获取视频内容类型

**返回值**
视频内容类型，参看 [VideoContentType](#videocontenttype)。


<span id="VideoFrame-gettimestampus"></span>
### getTimeStampUs
```java
public abstract long com.ss.bytertc.engine.video.VideoFrame.getTimeStampUs()
```
获取视频帧时间戳，单位：微秒


<span id="VideoFrame-getwidth"></span>
### getWidth
```java
public abstract int com.ss.bytertc.engine.video.VideoFrame.getWidth()
```
获取视频帧宽度，单位：px


<span id="VideoFrame-getheight"></span>
### getHeight
```java
public abstract int com.ss.bytertc.engine.video.VideoFrame.getHeight()
```
获取视频帧高度，单位：px


<span id="VideoFrame-getrotation"></span>
### getRotation
```java
public abstract VideoRotation com.ss.bytertc.engine.video.VideoFrame.getRotation()
```
获取视频帧旋转角度


<span id="VideoFrame-getcolorspace"></span>
### getColorSpace
```java
public abstract ColorSpace com.ss.bytertc.engine.video.VideoFrame.getColorSpace()
```
获取视频帧色彩空间，参看 [ColorSpace](#colorspace)


<span id="VideoFrame-getcameraid"></span>
### getCameraId
```java
public abstract CameraId com.ss.bytertc.engine.video.VideoFrame.getCameraId()
```
获取视频帧的摄像头信息，参看 [CameraId](#cameraid)


<span id="VideoFrame-getnumberofplanes"></span>
### getNumberOfPlanes
```java
public abstract int com.ss.bytertc.engine.video.VideoFrame.getNumberOfPlanes()
```
获取视频帧像素平面数量


**注意**
yuv 数据存储格式分为打包（packed）存储格式和平面（planar）存储格式，planar 格式中 Y、U、V 分平面存储，packed 格式中 Y、U、V 交叉存储

<span id="VideoFrame-getplanedata"></span>
### getPlaneData
```java
public abstract ByteBuffer com.ss.bytertc.engine.video.VideoFrame.getPlaneData(
    int planeIndex)
```
获取 plane 数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| planeIndex | **int** | plane 数据索引 |


<span id="VideoFrame-getplanestride"></span>
### getPlaneStride
```java
public abstract int com.ss.bytertc.engine.video.VideoFrame.getPlaneStride(
    int planeIndex)
```
获取指定 plane 中数据行的长度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| planeIndex | **int** | plane 数据索引 |


<span id="VideoFrame-getexternaldatainfo"></span>
### getExternalDataInfo
```java
public abstract ByteBuffer com.ss.bytertc.engine.video.VideoFrame.getExternalDataInfo()
```
获取 SEI 数据


<span id="VideoFrame-getsupplementaryinfo"></span>
### getSupplementaryInfo
```java
public abstract ByteBuffer com.ss.bytertc.engine.video.VideoFrame.getSupplementaryInfo()
```
获取补充数据指针


<span id="VideoFrame-gettextureid"></span>
### getTextureID
```java
public abstract int com.ss.bytertc.engine.video.VideoFrame.getTextureID()
```
获取纹理ID


<span id="VideoFrame-gettexturematrix"></span>
### getTextureMatrix
```java
public abstract float[] com.ss.bytertc.engine.video.VideoFrame.getTextureMatrix()
```
获取纹理矩阵


<span id="VideoFrame-geteglcontext"></span>
### getEGLContext
```java
public abstract EGLContext com.ss.bytertc.engine.video.VideoFrame.getEGLContext()
```
获取纹理使用的 EGLContext


<span id="VideoFrame-retain"></span>
### retain
```java
public synchronized void com.ss.bytertc.engine.video.VideoFrame.retain()
```
对当前的视频帧进行一次引用计数


<span id="VideoFrame-release"></span>
### release
```java
public synchronized void com.ss.bytertc.engine.video.VideoFrame.release()
```
对当前的视频帧减少一次引用计数


# VideoDecoderConfig
```java
public enum com.ss.bytertc.engine.video.VideoDecoderConfig
```

视频解码方式


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **VIDEO_DECODER_CONFIG_RAW(0)** | 开启 SDK 内部解码，只回调解码后的数据。回调为[onFrame](Android-keytype.md#onframe)。 |
| **VIDEO_DECODER_CONFIG_ENCODE(1)** | 开启自定义解码，只回调解码前数据。回调为[OnRemoteEncodedVideoFrame](Android-callback.md#onremoteencodedvideoframe)。 |
| **VIDEO_DECODER_CONFIG_BOTH(2)** | 开启 SDK 内部解码，同时回调解码前和解码后的数据。回调为[onFrame](Android-keytype#onframe)和[OnRemoteEncodedVideoFrame](Android-callback.md#onremoteencodedvideoframe)。|


# VideoPreprocessorConfig
```java
public class com.ss.bytertc.engine.video.VideoPreprocessorConfig
```

视频处理配置参数。<br>


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **VideoPixelFormat** | [required_pixel_format](#VideoPreprocessorConfig-required_pixel_format) |


## 变量说明
<span id="VideoPreprocessorConfig-required_pixel_format"></span>
### required_pixel_format
```java
public VideoPixelFormat com.ss.bytertc.engine.video.VideoPreprocessorConfig.required_pixel_format = VideoPixelFormat.kVideoPixelFormatUnknown;
```
设置请求的像素格式，参看 [VideoPixelFormat](#videopixelformat)。



# VideoEncoderConfig
```java
public class com.ss.bytertc.engine.VideoEncoderConfig
```

视频流参数描述


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#VideoEncoderConfig-width) |
| **int** | [height](#VideoEncoderConfig-height) |
| **int** | [frameRate](#VideoEncoderConfig-framerate) |
| **int** | [maxBitrate](#VideoEncoderConfig-maxbitrate) |
| **EncoderPreference** | [encodePreference](#VideoEncoderConfig-encodepreference) |


## 变量说明
<span id="VideoEncoderConfig-width"></span>
### width
```java
public int com.ss.bytertc.engine.VideoEncoderConfig.width;
```
视频宽度，单位：px


<span id="VideoEncoderConfig-height"></span>
### height
```java
public int com.ss.bytertc.engine.VideoEncoderConfig.height;
```
视频高度，单位：px


<span id="VideoEncoderConfig-framerate"></span>
### frameRate
```java
public int com.ss.bytertc.engine.VideoEncoderConfig.frameRate;
```
视频帧率，单位：fps


<span id="VideoEncoderConfig-maxbitrate"></span>
### maxBitrate
```java
public int com.ss.bytertc.engine.VideoEncoderConfig.maxBitrate = -1;
```
最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。  <br>
设为 `-1` 即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。 <br>
设为 `0` 则不对视频流进行编码发送。<br>
3.44.1 及以上版本，内部采集时默认值为 `-1`，3.44.1 以前版本无默认值，需手动设置。


<span id="VideoEncoderConfig-encodepreference"></span>
### encodePreference
```java
public EncoderPreference com.ss.bytertc.engine.VideoEncoderConfig.encodePreference =
```
编码策略偏好，默认为帧率优先。参看 [EncoderPreference](#encoderpreference)。



# CodecMode
```java
public enum com.ss.bytertc.engine.VideoEncoderConfig.CodecMode
```

编码器Mode(使用软编码或者硬编码)


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **CODEC_MODE_AUTO(0)** | 自动模式 |
| **CODEC_MODE_HARDWARE(1)** | 硬编码模式 |
| **CODEC_MODE_SOFTWARE(2)** | 软编码模式 |


# VideoCodecType
```java
public enum com.ss.bytertc.engine.VideoEncoderConfig.VideoCodecType
```

编码模式(H264, ByteVC1)


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **CODEC_TYPE_AUTO(0)** | 自动选择编码模式 |
| **CODEC_TYPE_H264(1)** | H264 |
| **CODEC_TYPE_BYTEVC1(2)** | ByteVC1 |


# EncoderPreference
```java
public enum com.ss.bytertc.engine.VideoEncoderConfig.EncoderPreference
```

编码策略偏好。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **Disabled(0)** | 无偏好。不降低帧率和分辨率。 |
| **MaintainFramerate(1)** | （默认值）帧率优先。 |
| **MaintainQuality(2)** | 分辨率优先。 |
| **Balance(3)** | 平衡帧率与分辨率。 |


# AudioChannel
```java
public enum com.ss.bytertc.engine.data.AudioChannel
```

音频声道


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_CHANNEL_AUTO(-1)** | 自动声道，适用于从 SDK 获取音频数据，使用 SDK 内部处理的声道，不经过 resample。  <br><br/>当你需要从 SDK 获取音频数据时，建议设置成该值，避免 resample 带来的性能损失。 |
| **AUDIO_CHANNEL_MONO(1)** | 单声道 |
| **AUDIO_CHANNEL_STEREO(2)** | 双声道 |


# AudioFrameCallbackMethod
```java
public enum com.ss.bytertc.engine.data.AudioFrameCallbackMethod
```

音频回调方法


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_FRAME_CALLBACK_RECORD(0)** | 本地麦克风录制的音频数据回调 |
| **AUDIO_FRAME_CALLBACK_PLAYBACK(1)** | 订阅的远端所有用户混音后的音频数据回调 |
| **AUDIO_FRAME_CALLBACK_MIXED(2)** | 本地麦克风录制和订阅的远端所有用户混音后的音频数据回调 |
| **AUDIO_FRAME_CALLBACK_REMOTE_USER(3)** | 订阅的远端每个用户混音前的音频数据回调 |


# AudioFrameType
```java
public enum com.ss.bytertc.engine.data.AudioFrameType
```

音频帧类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **FRAME_TYPE_PCM16(0)** | PCM 16bit |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [value](#AudioFrameType-value) |


## 函数说明
<span id="AudioFrameType-value"></span>
### value
```java
public int com.ss.bytertc.engine.data.AudioFrameType.value()
```
获取当前值

**返回值**
当前值


# AudioSampleRate
```java
public enum com.ss.bytertc.engine.data.AudioSampleRate
```

音频采样率，单位为 Hz。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_SAMPLE_RATE_AUTO(-1)** | 自动采样率，适用于从 SDK 获取音频数据，使用 SDK 内部处理的采样率，不经过 resample。  <br><br/>当你需要从 SDK 获取音频数据时，建议设置成该值，避免 resample 带来的性能损失。 |
| **AUDIO_SAMPLE_RATE_8000(8000)** | 8000 采样率 |
| **AUDIO_SAMPLE_RATE_16000(16000)** | 16000 采样率 |
| **AUDIO_SAMPLE_RATE_32000(32000)** | 32000 采样率 |
| **AUDIO_SAMPLE_RATE_44100(44100)** | 44100 采样率 |
| **AUDIO_SAMPLE_RATE_48000(48000)** | 48000 采样率 |


# EchoTestConfig
```java
public class com.ss.bytertc.engine.data.EchoTestConfig
```

音视频回路测试参数


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **View** | [view](#EchoTestConfig-view) |
| **String** | [uid](#EchoTestConfig-uid) |
| **String** | [roomId](#EchoTestConfig-roomid) |
| **String** | [token](#EchoTestConfig-token) |
| **boolean** | [enableAudio](#EchoTestConfig-enableaudio) |
| **boolean** | [enableVideo](#EchoTestConfig-enablevideo) |
| **int** | [audioReportInterval](#EchoTestConfig-audioreportinterval) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **View** | [getEchoRenderView](#EchoTestConfig-getechorenderview) |
| **String** | [getEchoUid](#EchoTestConfig-getechouid) |
| **String** | [getEchoRoomId](#EchoTestConfig-getechoroomid) |
| **String** | [getEchoToken](#EchoTestConfig-getechotoken) |
| **boolean** | [getEchoEnabledAudio](#EchoTestConfig-getechoenabledaudio) |
| **boolean** | [getEchoEnabledVideo](#EchoTestConfig-getechoenabledvideo) |
| **int** | [getAudioReportInterval](#EchoTestConfig-getaudioreportinterval) |


## 变量说明
<span id="EchoTestConfig-view"></span>
### view
```java
public View   com.ss.bytertc.engine.data.EchoTestConfig.view;
```
用于渲染接收到的视频的视图


<span id="EchoTestConfig-uid"></span>
### uid
```java
public String com.ss.bytertc.engine.data.EchoTestConfig.uid;
```
进行音视频通话回路测试的用户 ID


<span id="EchoTestConfig-roomid"></span>
### roomId
```java
public String com.ss.bytertc.engine.data.EchoTestConfig.roomId;
```
测试用户加入的房间 ID


<span id="EchoTestConfig-token"></span>
### token
```java
public String com.ss.bytertc.engine.data.EchoTestConfig.token;
```
对用户进房时进行鉴权验证的动态密钥，用于保证音视频通话回路测试的安全性。


<span id="EchoTestConfig-enableaudio"></span>
### enableAudio
```java
public boolean com.ss.bytertc.engine.data.EchoTestConfig.enableAudio;
```
是否检测音频。检测设备为系统默认音频设备。  <br>

+ true：是  <br>
- 若使用 SDK 内部采集，此时设备麦克风会自动开启，并在 audioReportInterval 值大于 0 时触发 `onLocalAudioPropertiesReport` 回调，你可以根据该回调判断麦克风的工作状态  <br>
- 若使用自定义采集，此时你需调用 [pushExternalAudioFrame](Android-api.md#RTCVideo-pushexternalaudioframe) 将采集到的音频推送给 SDK  <br>
+ flase：否  <br>


<span id="EchoTestConfig-enablevideo"></span>
### enableVideo
```java
public boolean com.ss.bytertc.engine.data.EchoTestConfig.enableVideo;
```
是否检测视频。PC 端默认检测列表中第一个视频设备。  <br>

+ true：是  <br>
- 若使用 SDK 内部采集，此时设备摄像头会自动开启  <br>
- 若使用自定义采集，此时你需调用 [pushExternalVideoFrame](Android-api.md#RTCVideo-pushexternalvideoframe) 将采集到的视频推送给 SDK  <br>
+ flase：否  <br>

**注意:**
视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。
视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。

<span id="EchoTestConfig-audioreportinterval"></span>
### audioReportInterval
```java
public int com.ss.bytertc.engine.data.EchoTestConfig.audioReportInterval;
```
音量信息提示间隔，单位：ms，默认为 100ms <br>

+ `<= 0`: 关闭信息提示  <br>
+ `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
+ `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>



## 函数说明
<span id="EchoTestConfig-getechorenderview"></span>
### getEchoRenderView
```java
public View com.ss.bytertc.engine.data.EchoTestConfig.getEchoRenderView()
```

<span id="EchoTestConfig-getechouid"></span>
### getEchoUid
```java
public String com.ss.bytertc.engine.data.EchoTestConfig.getEchoUid()
```

<span id="EchoTestConfig-getechoroomid"></span>
### getEchoRoomId
```java
public String com.ss.bytertc.engine.data.EchoTestConfig.getEchoRoomId()
```

<span id="EchoTestConfig-getechotoken"></span>
### getEchoToken
```java
public String com.ss.bytertc.engine.data.EchoTestConfig.getEchoToken()
```

<span id="EchoTestConfig-getechoenabledaudio"></span>
### getEchoEnabledAudio
```java
public boolean com.ss.bytertc.engine.data.EchoTestConfig.getEchoEnabledAudio()
```

<span id="EchoTestConfig-getechoenabledvideo"></span>
### getEchoEnabledVideo
```java
public boolean com.ss.bytertc.engine.data.EchoTestConfig.getEchoEnabledVideo()
```

<span id="EchoTestConfig-getaudioreportinterval"></span>
### getAudioReportInterval
```java
public int com.ss.bytertc.engine.data.EchoTestConfig.getAudioReportInterval()
```

# LocalAudioStreamError
```java
public enum com.ss.bytertc.engine.data.LocalAudioStreamError
```

本地音频流状态改变时的错误码。  <br>
SDK 通过 onLocalAudioStateChanged 回调该错误码。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **LOCAL_AUDIO_STREAM_ERROR_OK(0)** | 本地音频状态正常 |
| **LOCAL_AUDIO_STREAM_ERROR_FAILURE(1)** | 本地音频出错原因未知 |
| **LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION(2)** | 没有权限启动本地音频录制设备 |
| **LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE(4)** | 本地音频录制失败，建议你检查录制设备是否正常工作 |
| **LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE(5)** | 本地音频编码失败 |
| **LOCAL_AUDIO_STREAM_ERROR_NO_RECORDING_DEVICE(6)** | 没有可用的音频录制设备 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [value](#LocalAudioStreamError-value) |


## 函数说明
<span id="LocalAudioStreamError-value"></span>
### value
```java
public int com.ss.bytertc.engine.data.LocalAudioStreamError.value()
```
获取当前值

**返回值**
当前值


# LocalAudioStreamState
```java
public enum com.ss.bytertc.engine.data.LocalAudioStreamState
```

本地音频流状态。  <br>
SDK 通过 onLocalAudioStateChanged 回调该状态。  <br>


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **LOCAL_AUDIO_STREAM_STATE_STOPPED(0)** | 本地音频默认初始状态。  <br><br/>麦克风停止工作时回调该状态，对应错误码 [LocalAudioStreamError](#localaudiostreamerror) 中的 kLocalAudioStreamErrorOk 。  <br> |
| **LOCAL_AUDIO_STREAM_STATE_RECORDING(1)** | 本地音频录制设备启动成功。  <br><br/>采集到音频首帧时回调该状态，对应错误码 [LocalAudioStreamError](#localaudiostreamerror) 中的 kLocalAudioStreamErrorOk 。  <br> |
| **LOCAL_AUDIO_STREAM_STATE_ENCODING(2)** | 本地音频首帧编码成功。  <br><br/>音频首帧编码成功时回调该状态，对应错误码 [LocalAudioStreamError](#localaudiostreamerror) 中的 kLocalAudioStreamErrorOk 。  <br> |
| **LOCAL_AUDIO_STREAM_STATE_FAILED(3)** | 本地音频启动失败，在以下时机回调该状态：  <br><br/>+ 本地录音设备启动失败，对应错误码 [LocalAudioStreamError](#localaudiostreamerror) 中的 kLocalAudioStreamErrorRecordFailure 。  <br><br/>+ 检测到没有录音设备权限，对应错误码 [LocalAudioStreamError](#localaudiostreamerror) 中的 kLocalAudioStreamErrorDeviceNoPermission。  <br><br/>+ 音频编码失败，对应错误码 [LocalAudioStreamError](#localaudiostreamerror) 中的 kLocalAudioStreamErrorEncodeFailure。  <br> |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [value](#LocalAudioStreamState-value) |


## 函数说明
<span id="LocalAudioStreamState-value"></span>
### value
```java
public int com.ss.bytertc.engine.data.LocalAudioStreamState.value()
```
获取当前值

**返回值**
当前值


# RecordingConfig
```java
public class com.ss.bytertc.engine.data.RecordingConfig
```

本地录制参数配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [dirPath](#RecordingConfig-dirpath) |
| **RecordingFileType** | [recordingFileType](#RecordingConfig-recordingfiletype) |


## 变量说明
<span id="RecordingConfig-dirpath"></span>
### dirPath
```java
public String com.ss.bytertc.engine.data.RecordingConfig.dirPath;
```
录制文件保存的绝对路径，需精确到文件夹，文件名由 RTC 自动生成。你需要确保对该路径具有读写权限。


<span id="RecordingConfig-recordingfiletype"></span>
### recordingFileType
```java
public RecordingFileType com.ss.bytertc.engine.data.RecordingConfig.recordingFileType = RecordingFileType.RECORDING_FILE_TYPE_MP4;
```
录制存储文件格式，参看 [RecordingFileType](#recordingfiletype)



# RecordingInfo
```java
public class com.ss.bytertc.engine.data.RecordingInfo
```

本地录制的详细信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [filePath](#RecordingInfo-filepath) |
| **VideoCodecType** | [videoCodecType](#RecordingInfo-videocodectype) |
| **int** | [width](#RecordingInfo-width) |
| **int** | [height](#RecordingInfo-height) |


## 变量说明
<span id="RecordingInfo-filepath"></span>
### filePath
```java
public String com.ss.bytertc.engine.data.RecordingInfo.filePath;
```
录制文件的绝对路径，包含文件名和文件后缀


<span id="RecordingInfo-videocodectype"></span>
### videoCodecType
```java
public VideoCodecType com.ss.bytertc.engine.data.RecordingInfo.videoCodecType;
```
录制文件的视频编码类型，参看 参看 [VideoCodecType](#videocodectype)


<span id="RecordingInfo-width"></span>
### width
```java
public int com.ss.bytertc.engine.data.RecordingInfo.width;
```
录制视频的宽，单位：像素。纯音频录制请忽略该字段


<span id="RecordingInfo-height"></span>
### height
```java
public int com.ss.bytertc.engine.data.RecordingInfo.height;
```
录制视频的高，单位：像素。纯音频录制请忽略该字段



# RecordingProgress
```java
public class com.ss.bytertc.engine.data.RecordingProgress
```

本地录制进度


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **long** | [duration](#RecordingProgress-duration) |
| **long** | [fileSize](#RecordingProgress-filesize) |


## 变量说明
<span id="RecordingProgress-duration"></span>
### duration
```java
public long com.ss.bytertc.engine.data.RecordingProgress.duration;
```
当前文件的累计录制时长，单位：毫秒


<span id="RecordingProgress-filesize"></span>
### fileSize
```java
public long com.ss.bytertc.engine.data.RecordingProgress.fileSize;
```
当前录制文件的大小，单位：byte



# RemoteAudioState
```java
public enum com.ss.bytertc.engine.data.RemoteAudioState
```

用户订阅的远端音频流状态。  <br>
SDK 通过 onRemoteAudioStateChanged 回调该状态。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **REMOTE_AUDIO_STATE_STOPPED(0)** | 远端音频流默认初始状态，在以下时机回调该状态：  <br><br/>+ 本地用户停止接收远端音频流，对应原因是 [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonLocalMuted`  <br><br/>+ 远端用户停止发送音频流，对应原因是 [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonRemoteMuted` <br><br/>+ 远端用户离开房间，对应原因是 [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonRemoteOffline`  <br> |
| **REMOTE_AUDIO_STATE_STARTING(1)** | 开始接收远端音频流首包。  <br><br/>刚收到远端音频流首包时，会触发回调 onRemoteAudioStateChanged，<br/>对应原因是 [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonLocalUnmuted` 。 |
| **REMOTE_AUDIO_STATE_DECODING(2)** | 远端音频流正在解码，正常播放，在以下时机回调该状态：  <br><br/>+ 成功解码远端音频首帧，对应原因是 [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonLocalUnmuted`  <br><br/>+ 网络由阻塞恢复正常，对应原因是 [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonNetworkRecovery`  <br><br/>+ 本地用户恢复接收远端音频流，对应原因是 [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonLocalUnmuted`  <br><br/>+ 远端用户恢复发送音频流，对应原因是 [RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonRemoteUnmuted` <br> |
| **REMOTE_AUDIO_STATE_FROZEN(3)** | 远端音频流卡顿。<br/>网络阻塞导致丢包率大于 40% 时回调该状态，对应原因是<br/>[RemoteAudioStateChangeReason](#remoteaudiostatechangereason) 中的 `kRemoteAudioReasonNetworkCongestion` |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [value](#RemoteAudioState-value) |


## 函数说明
<span id="RemoteAudioState-value"></span>
### value
```java
public int com.ss.bytertc.engine.data.RemoteAudioState.value()
```
获取当前值

**返回值**
当前值


# RemoteAudioStateChangeReason
```java
public enum com.ss.bytertc.engine.data.RemoteAudioStateChangeReason
```

远端音频流状态改变的原因。
SDK 通过 onRemoteAudioStateChanged 回调该错误码。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **REMOTE_AUDIO_STATE_CHANGE_REASON_INTERNAL(0)** | 内部原因 |
| **REMOTE_AUDIO_STATE_CHANGE_REASON_NETWORK_CONGESTION(1)** | 网络阻塞 |
| **REMOTE_AUDIO_STATE_CHANGE_REASON_NETWORK_RECOVERY(2)** | 网络恢复正常 |
| **REMOTE_AUDIO_STATE_CHANGE_REASON_LOCAL_MUTED(3)** | 本地用户停止接收远端音频流 |
| **REMOTE_AUDIO_STATE_CHANGE_REASON_LOCAL_UNMUTED(4)** | 本地用户恢复接收远端音频流 |
| **REMOTE_AUDIO_STATE_CHANGE_REASON_REMOTE_MUTED(5)** | 远端用户停止发送音频流 |
| **REMOTE_AUDIO_STATE_CHANGE_REASON_REMOTE_UNMUTED(6)** | 远端用户恢复发送音频流 |
| **REMOTE_AUDIO_STATE_CHANGE_REASON_REMOTE_OFFLINE(7)** | 远端用户离开房间 |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [value](#RemoteAudioStateChangeReason-value) |


## 函数说明
<span id="RemoteAudioStateChangeReason-value"></span>
### value
```java
public int com.ss.bytertc.engine.data.RemoteAudioStateChangeReason.value()
```
获取当前值

**返回值**
当前值


# RemoteStreamKey
```java
public class com.ss.bytertc.engine.data.RemoteStreamKey
```

远端流信息


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **String** | [getRoomId](#RemoteStreamKey-getroomid) |
| **String** | [getUserId](#RemoteStreamKey-getuserid) |
| **StreamIndex** | [getStreamIndex](#RemoteStreamKey-getstreamindex) |


## 函数说明
<span id="RemoteStreamKey-getroomid"></span>
### getRoomId
```java
public String com.ss.bytertc.engine.data.RemoteStreamKey.getRoomId()
```
获取房间 ID


<span id="RemoteStreamKey-getuserid"></span>
### getUserId
```java
public String com.ss.bytertc.engine.data.RemoteStreamKey.getUserId()
```
获取用户 ID


<span id="RemoteStreamKey-getstreamindex"></span>
### getStreamIndex
```java
public StreamIndex com.ss.bytertc.engine.data.RemoteStreamKey.getStreamIndex()
```
获取流属性，包括主流、屏幕流。参看 [StreamIndex](#streamindex-2)


# RemoteVideoConfig
```java
public class com.ss.bytertc.engine.data.RemoteVideoConfig
```

远端视频帧信息


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **RemoteVideoConfig** | [RemoteVideoConfig](#RemoteVideoConfig-remotevideoconfig) |


## 函数说明
<span id="RemoteVideoConfig-remotevideoconfig"></span>
### RemoteVideoConfig
```java
public com.ss.bytertc.engine.data.RemoteVideoConfig.RemoteVideoConfig(
    int width,
    int height,
    int framerate)
```
远端视频参数设置

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| width | **int** | 视频宽度，单位：px |
| height | **int** | 视频高度，单位：px |
| framerate | **int** | 期望订阅的最高帧率，单位：fps，默认值为 0 即满帧订阅，设为大于 0 的值时开始生效。  <br/>当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br/>仅码流支持 SVC 分级编码特性时方可生效。 |


# RTCASRConfig
```java
public class com.ss.bytertc.engine.data.RTCASRConfig
```

使用自动语音识别服务所需校验信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [userId](#RTCASRConfig-userid) |
| **String** | [accessToken](#RTCASRConfig-accesstoken) |
| **String** | [secretKey](#RTCASRConfig-secretkey) |
| **ASRAuthorizationType** | [authorizationType](#RTCASRConfig-authorizationtype) |
| **String** | [cluster](#RTCASRConfig-cluster) |
| **String** | [appId](#RTCASRConfig-appid) |


## 变量说明
<span id="RTCASRConfig-userid"></span>
### userId
```java
public String com.ss.bytertc.engine.data.RTCASRConfig.userId;
```
用户 ID


<span id="RTCASRConfig-accesstoken"></span>
### accessToken
```java
public String com.ss.bytertc.engine.data.RTCASRConfig.accessToken;
```
访问令牌


<span id="RTCASRConfig-secretkey"></span>
### secretKey
```java
public String com.ss.bytertc.engine.data.RTCASRConfig.secretKey;
```
私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://www.volcengine.com/docs/6561/107789)


<span id="RTCASRConfig-authorizationtype"></span>
### authorizationType
```java
public ASRAuthorizationType com.ss.bytertc.engine.data.RTCASRConfig.authorizationType;
```
鉴权方式


<span id="RTCASRConfig-cluster"></span>
### cluster
```java
public String com.ss.bytertc.engine.data.RTCASRConfig.cluster;
```
场景信息，参看[业务集群](https://www.volcengine.com/docs/6561/80818#_3-2-2-%E5%8F%91%E9%80%81-full-client-request)


<span id="RTCASRConfig-appid"></span>
### appId
```java
public String com.ss.bytertc.engine.data.RTCASRConfig.appId;
```
应用 ID



# ASRAuthorizationType
```java
public enum com.ss.bytertc.engine.data.RTCASRConfig.ASRAuthorizationType
```

语音识别服务鉴权方式，详情请咨询语音识别服务相关人员


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **ASR_AUTHORIZATION_TYPE_TOKEN(0)** | Token 鉴权 |
| **ASR_AUTHORIZATION_TYPE_SIGNATURE(1)** | Signature 鉴权 |


# VideoFrameInfo
```java
public class com.ss.bytertc.engine.data.VideoFrameInfo
```

视频帧信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **VideoRotation** | [rotation](#VideoFrameInfo-rotation) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **int** | [getWidth](#VideoFrameInfo-getwidth) |
| **int** | [getHeight](#VideoFrameInfo-getheight) |


## 变量说明
<span id="VideoFrameInfo-rotation"></span>
### rotation
```java
public VideoRotation com.ss.bytertc.engine.data.VideoFrameInfo.rotation = VideoRotation.VIDEO_ROTATION_0;
```
视频帧顺时针旋转角度。参看 [VideoRotation](#videorotation)。



## 函数说明
<span id="VideoFrameInfo-getwidth"></span>
### getWidth
```java
public int com.ss.bytertc.engine.data.VideoFrameInfo.getWidth()
```
获取宽度（像素）


<span id="VideoFrameInfo-getheight"></span>
### getHeight
```java
public int com.ss.bytertc.engine.data.VideoFrameInfo.getHeight()
```
获取高度（像素）


# VideoPictureType
```java
public enum com.ss.bytertc.engine.data.VideoPictureType
```

编码帧类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **VIDEO_PICTURE_TYPE_UNKNOWN(0)** | 未知类型 |
| **VIDEO_PICTURE_TYPE_I(1)** | I帧，关键帧，编解码不需要参考其他视频帧 |
| **VIDEO_PICTURE_TYPE_P(2)** | P帧，向前参考帧，编解码需要参考前一帧视频帧 |
| **VIDEO_PICTURE_TYPE_B(3)** | B帧，前后参考帧，编解码需要参考前后两帧视频帧 |


# VideoRotation
```java
public enum com.ss.bytertc.engine.data.VideoRotation
```

视频帧旋转角度


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **VIDEO_ROTATION_0(0)** | 顺时针旋转 0 度 |
| **VIDEO_ROTATION_90(90)** | 顺时针旋转 90 度 |
| **VIDEO_ROTATION_180(180)** | 顺时针旋转 180 度 |
| **VIDEO_ROTATION_270(270)** | 顺时针旋转 270 度 |


# VideoSourceType
```java
public enum com.ss.bytertc.engine.data.VideoSourceType
```

视频输入源类型


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **VIDEO_SOURCE_TYPE_EXTERNAL(0)** | 自定义采集视频源 |
| **VIDEO_SOURCE_TYPE_INTERNAL(1)** | 内部采集视频源 |
| **VIDEO_SOURCE_TYPE_ENCODED_WITH_SIMULCAST(2)** | 自定义编码视频源。  <br><br/>你仅需推送分辨率最大的一路编码后视频流，SDK 将自动转码生成多路小流 |
| **VIDEO_SOURCE_TYPE_ENCODED_WITHOUT_SIMULCAST(3)** | 自定义编码视频源。  <br><br/>SDK 不会自动生成多路流，你需要自行生成并推送多路流 |


# RTCEncodedVideoFrame
```java
public class com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame
```

视频帧信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ByteBuffer** | [buffer](#RTCEncodedVideoFrame-buffer) |
| **long** | [timestampUs](#RTCEncodedVideoFrame-timestampus) |
| **long** | [timestampDtsUs](#RTCEncodedVideoFrame-timestampdtsus) |
| **int** | [width](#RTCEncodedVideoFrame-width) |
| **int** | [height](#RTCEncodedVideoFrame-height) |
| **VideoCodecType** | [videoCodecType](#RTCEncodedVideoFrame-videocodectype) |
| **VideoPictureType** | [videoPictureType](#RTCEncodedVideoFrame-videopicturetype) |
| **VideoRotation** | [videoRotation](#RTCEncodedVideoFrame-videorotation) |


## 变量说明
<span id="RTCEncodedVideoFrame-buffer"></span>
### buffer
```java
public final ByteBuffer com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame.buffer;
```
视频帧数据指针地址


<span id="RTCEncodedVideoFrame-timestampus"></span>
### timestampUs
```java
public long com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame.timestampUs;
```
视频采集时间戳，单位：微秒


<span id="RTCEncodedVideoFrame-timestampdtsus"></span>
### timestampDtsUs
```java
public long com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame.timestampDtsUs;
```
视频编码时间戳，单位：微秒


<span id="RTCEncodedVideoFrame-width"></span>
### width
```java
public int com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame.width;
```
视频分辨率的宽度，单位：px


<span id="RTCEncodedVideoFrame-height"></span>
### height
```java
public int com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame.height;
```
视频分辨率的高度，单位：px


<span id="RTCEncodedVideoFrame-videocodectype"></span>
### videoCodecType
```java
public VideoCodecType com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame.videoCodecType;
```
视频编码类型。参看 [VideoCodecType](#videocodectype-2)


<span id="RTCEncodedVideoFrame-videopicturetype"></span>
### videoPictureType
```java
public VideoPictureType com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame.videoPictureType;
```
视频帧类型。参看 [VideoPictureType](#videopicturetype)


<span id="RTCEncodedVideoFrame-videorotation"></span>
### videoRotation
```java
public VideoRotation com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame.videoRotation;
```
视频帧旋转角度，默认旋转 0 度。参看 [VideoRotation](#videorotation)



# VideoDimensions
```java
public class com.ss.bytertc.engine.video.VideoDimensions
```

视频编码像素


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [width](#VideoDimensions-width) |
| **int** | [height](#VideoDimensions-height) |


## 变量说明
<span id="VideoDimensions-width"></span>
### width
```java
public int com.ss.bytertc.engine.video.VideoDimensions.width;
```
宽


<span id="VideoDimensions-height"></span>
### height
```java
public int com.ss.bytertc.engine.video.VideoDimensions.height;
```
高



# CpuBufferVideoFrameBuilder
```java
public class com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder
```

构建 CpuBuffer 的视频帧


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **CpuBufferVideoFrameBuilder** | [setTimeStampUs](#CpuBufferVideoFrameBuilder-settimestampus) |
| **CpuBufferVideoFrameBuilder** | [setWidth](#CpuBufferVideoFrameBuilder-setwidth) |
| **CpuBufferVideoFrameBuilder** | [setHeight](#CpuBufferVideoFrameBuilder-setheight) |
| **CpuBufferVideoFrameBuilder** | [setRotation](#CpuBufferVideoFrameBuilder-setrotation) |
| **CpuBufferVideoFrameBuilder** | [setColorSpace](#CpuBufferVideoFrameBuilder-setcolorspace) |
| **CpuBufferVideoFrameBuilder** | [setPlaneData](#CpuBufferVideoFrameBuilder-setplanedata) |
| **CpuBufferVideoFrameBuilder** | [setPlaneStride](#CpuBufferVideoFrameBuilder-setplanestride) |
| **CpuBufferVideoFrameBuilder** | [setExternalDataInfo](#CpuBufferVideoFrameBuilder-setexternaldatainfo) |
| **CpuBufferVideoFrameBuilder** | [setSupplementaryInfo](#CpuBufferVideoFrameBuilder-setsupplementaryinfo) |
| **CpuBufferVideoFrameBuilder** | [setReleaseCallback](#CpuBufferVideoFrameBuilder-setreleasecallback) |
| **VideoFrame** | [build](#CpuBufferVideoFrameBuilder-build) |


## 函数说明
<span id="CpuBufferVideoFrameBuilder-settimestampus"></span>
### setTimeStampUs
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setTimeStampUs(
    long timeStampUs)
```
设置视频帧的时间戳

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| timeStampUs | **long** | 视频帧时间戳 |


<span id="CpuBufferVideoFrameBuilder-setwidth"></span>
### setWidth
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setWidth(
    int width)
```
设置视频帧宽度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| width | **int** | 视频帧宽度，单位：像素 |


<span id="CpuBufferVideoFrameBuilder-setheight"></span>
### setHeight
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setHeight(
    int height)
```
设置视频帧高度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| height | **int** | 视频帧高度，单位：像素 |


<span id="CpuBufferVideoFrameBuilder-setrotation"></span>
### setRotation
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setRotation(
    VideoRotation rotation)
```
设置视频帧旋转角度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rotation | **VideoRotation** | 视频帧旋转角度，参看 [VideoRotation](#videorotation) |


<span id="CpuBufferVideoFrameBuilder-setcolorspace"></span>
### setColorSpace
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setColorSpace(
    ColorSpace colorSpace)
```
设置视频帧色彩空间

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| colorSpace | **ColorSpace** | 视频帧色彩空间，参看 [ColorSpace](#colorspace) |


<span id="CpuBufferVideoFrameBuilder-setplanedata"></span>
### setPlaneData
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setPlaneData(
    int planeIndex,
    ByteBuffer buffer)
```
设置像素平面数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| planeIndex | **int** | 像素平面数据索引 |
| buffer | **ByteBuffer** | plane 要设置的 ByteBuffer，如果设置的是一个 DirectBuffer，则不会发生拷贝，如果不是，则会发生一次拷贝 |


<span id="CpuBufferVideoFrameBuilder-setplanestride"></span>
### setPlaneStride
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setPlaneStride(
    int planeIndex,
    int stride)
```
设置指定像素平面的跨距

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| planeIndex | **int** | 像素平面数据索引 |
| stride | **int** | 当前像素平面的跨度 |


<span id="CpuBufferVideoFrameBuilder-setexternaldatainfo"></span>
### setExternalDataInfo
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setExternalDataInfo(
    ByteBuffer externalDataInfo)
```
设置 SEI 数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| externalDataInfo | **ByteBuffer** | SEI 数据，如果设置的是一个 DirectBuffer，则不会发生拷贝，如果不是，则会发生一次拷贝 |


<span id="CpuBufferVideoFrameBuilder-setsupplementaryinfo"></span>
### setSupplementaryInfo
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setSupplementaryInfo(
    ByteBuffer supplementaryInfo)
```
设置补充数据指针

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| supplementaryInfo | **ByteBuffer** | 补充数据指针，如果设置的是一个 DirectBuffer，则不会发生拷贝，如果不是，则会发生一次拷贝 |


<span id="CpuBufferVideoFrameBuilder-setreleasecallback"></span>
### setReleaseCallback
```java
public CpuBufferVideoFrameBuilder com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.setReleaseCallback(
    Runnable releaseCallback)
```
设置视频帧的释放回调，当视频帧的引用计数归 0 时，会执行 releaseCallback

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| releaseCallback | **Runnable** | 视频帧的释放回调 |


<span id="CpuBufferVideoFrameBuilder-build"></span>
### build
```java
public VideoFrame com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder.build()
```
获取到创建好的视频帧

**返回值**
创建好的视频帧，参看 [VideoFrame](#videoframe)


# GLTextureVideoFrameBuilder
```java
public class com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder
```

构建纹理格式视频数据返回帧


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **GLTextureVideoFrameBuilder** | [setTimeStampUs](#GLTextureVideoFrameBuilder-settimestampus) |
| **GLTextureVideoFrameBuilder** | [setWidth](#GLTextureVideoFrameBuilder-setwidth) |
| **GLTextureVideoFrameBuilder** | [setHeight](#GLTextureVideoFrameBuilder-setheight) |
| **GLTextureVideoFrameBuilder** | [setRotation](#GLTextureVideoFrameBuilder-setrotation) |
| **GLTextureVideoFrameBuilder** | [setColorSpace](#GLTextureVideoFrameBuilder-setcolorspace) |
| **GLTextureVideoFrameBuilder** | [setExternalDataInfo](#GLTextureVideoFrameBuilder-setexternaldatainfo) |
| **GLTextureVideoFrameBuilder** | [setSupplementaryInfo](#GLTextureVideoFrameBuilder-setsupplementaryinfo) |
| **GLTextureVideoFrameBuilder** | [setTextureID](#GLTextureVideoFrameBuilder-settextureid) |
| **GLTextureVideoFrameBuilder** | [setTextureMatrix](#GLTextureVideoFrameBuilder-settexturematrix) |
| **GLTextureVideoFrameBuilder** | [setEGLContext](#GLTextureVideoFrameBuilder-seteglcontext) |
| **GLTextureVideoFrameBuilder** | [setReleaseCallback](#GLTextureVideoFrameBuilder-setreleasecallback) |
| **VideoFrame** | [build](#GLTextureVideoFrameBuilder-build) |


## 函数说明
<span id="GLTextureVideoFrameBuilder-settimestampus"></span>
### setTimeStampUs
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setTimeStampUs(
    long timeStampUs)
```
设置视频帧的时间戳

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| timeStampUs | **long** | 视频帧时间戳 |


<span id="GLTextureVideoFrameBuilder-setwidth"></span>
### setWidth
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setWidth(
    int width)
```
设置视频帧宽度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| width | **int** | 视频帧宽度，单位：像素 |


<span id="GLTextureVideoFrameBuilder-setheight"></span>
### setHeight
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setHeight(
    int height)
```
设置视频帧高度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| height | **int** | 视频帧高度，单位：像素 |


<span id="GLTextureVideoFrameBuilder-setrotation"></span>
### setRotation
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setRotation(
    VideoRotation rotation)
```
设置视频帧旋转角度

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| rotation | **VideoRotation** | 视频帧旋转角度，参看 [VideoRotation](#videorotation) |


<span id="GLTextureVideoFrameBuilder-setcolorspace"></span>
### setColorSpace
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setColorSpace(
    ColorSpace colorSpace)
```
设置视频帧色彩空间

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| colorSpace | **ColorSpace** | 视频帧色彩空间，参看 [ColorSpace](#colorspace) |


<span id="GLTextureVideoFrameBuilder-setexternaldatainfo"></span>
### setExternalDataInfo
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setExternalDataInfo(
    ByteBuffer externalDataInfo)
```
设置 SEI 数据

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| externalDataInfo | **ByteBuffer** | SEI 数据，如果设置的是一个 DirectBuffer，则不会发生拷贝，如果不是，则会发生一次拷贝 |


<span id="GLTextureVideoFrameBuilder-setsupplementaryinfo"></span>
### setSupplementaryInfo
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setSupplementaryInfo(
    ByteBuffer supplementaryInfo)
```
设置补充数据指针

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| supplementaryInfo | **ByteBuffer** | 补充数据指针，如果设置的是一个 DirectBuffer，则不会发生拷贝，如果不是，则会发生一次拷贝 |


<span id="GLTextureVideoFrameBuilder-settextureid"></span>
### setTextureID
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setTextureID(
    int textureID)
```
设置视频帧的纹理 ID

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| textureID | **int** | 纹理 ID |


<span id="GLTextureVideoFrameBuilder-settexturematrix"></span>
### setTextureMatrix
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setTextureMatrix(
    float[] textureMatrix)
```
设置视频帧纹理矩阵

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| textureMatrix | **float[]** | 视频帧纹理矩阵 |


<span id="GLTextureVideoFrameBuilder-seteglcontext"></span>
### setEGLContext
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setEGLContext(
    EGLContext eglContext)
```
设置视频帧的 EGLContext

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| eglContext | **EGLContext** | 视频帧的 EGLContext |


<span id="GLTextureVideoFrameBuilder-setreleasecallback"></span>
### setReleaseCallback
```java
public GLTextureVideoFrameBuilder com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.setReleaseCallback(
    Runnable releaseCallback)
```
设置视频帧的释放回调，当视频帧的引用计数归 0 时，会执行 releaseCallback

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| releaseCallback | **Runnable** | 视频帧的释放回调 |


<span id="GLTextureVideoFrameBuilder-build"></span>
### build
```java
public VideoFrame com.ss.bytertc.engine.video.builder.GLTextureVideoFrameBuilder.build()
```
获取到创建好的视频帧

**返回值**
创建好的视频帧，参看 [VideoFrame](#videoframe)


# RTCRoomConfig
```java
public class com.ss.bytertc.engine.RTCRoomConfig
```

房间参数配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **ChannelProfile** | [profile](#RTCRoomConfig-profile) |
| **boolean** | [isAutoPublish](#RTCRoomConfig-isautopublish) |
| **boolean** | [isAutoSubscribeAudio](#RTCRoomConfig-isautosubscribeaudio) |
| **boolean** | [isAutoSubscribeVideo](#RTCRoomConfig-isautosubscribevideo) |
| **RemoteVideoConfig** | [remoteVideoConfig](#RTCRoomConfig-remotevideoconfig) |


## 变量说明
<span id="RTCRoomConfig-profile"></span>
### profile
```java
public ChannelProfile com.ss.bytertc.engine.RTCRoomConfig.profile;
```
房间模式，参看 [ChannelProfile](#channelprofile)，默认为 `CHANNEL_PROFILE_COMMUNICATION`，进房后不可更改。


<span id="RTCRoomConfig-isautopublish"></span>
### isAutoPublish
```java
public boolean com.ss.bytertc.engine.RTCRoomConfig.isAutoPublish;
```
是否自动发布音视频流，默认为自动发布。 <br>
创建和加入多房间时，只能将其中一个房间设置为自动发布。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。<br>
若调用 [setUserVisibility](Android-api.md#RTCRoom-setuservisibility) 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。


<span id="RTCRoomConfig-isautosubscribeaudio"></span>
### isAutoSubscribeAudio
```java
public boolean com.ss.bytertc.engine.RTCRoomConfig.isAutoSubscribeAudio;
```
是否自动订阅音频流，默认为自动订阅。<br>
包含主流和屏幕流。


<span id="RTCRoomConfig-isautosubscribevideo"></span>
### isAutoSubscribeVideo
```java
public boolean com.ss.bytertc.engine.RTCRoomConfig.isAutoSubscribeVideo;
```
是否自动订阅视频流，默认为自动订阅。 <br>
包含主流和屏幕流。


<span id="RTCRoomConfig-remotevideoconfig"></span>
### remoteVideoConfig
```java
public RemoteVideoConfig com.ss.bytertc.engine.RTCRoomConfig.remoteVideoConfig = null;
```
远端视频流参数，参看 [RemoteVideoConfig](#remotevideoconfig)



# SubscribeConfig
```java
public class com.ss.bytertc.engine.SubscribeConfig
```

选择订阅配置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **boolean** | [isScreen](#SubscribeConfig-isscreen) |
| **boolean** | [subVideo](#SubscribeConfig-subvideo) |
| **boolean** | [subAudio](#SubscribeConfig-subaudio) |
| **int** | [sub_width](#SubscribeConfig-sub_width) |
| **int** | [sub_height](#SubscribeConfig-sub_height) |
| **int** | [framerate](#SubscribeConfig-framerate) |


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **SubscribeConfig** | [SubscribeConfig](#SubscribeConfig-subscribeconfig) |


## 变量说明
<span id="SubscribeConfig-isscreen"></span>
### isScreen
```java
public boolean com.ss.bytertc.engine.SubscribeConfig.isScreen;
```
是否是屏幕流


<span id="SubscribeConfig-subvideo"></span>
### subVideo
```java
public boolean com.ss.bytertc.engine.SubscribeConfig.subVideo;
```
是否订阅视频


<span id="SubscribeConfig-subaudio"></span>
### subAudio
```java
public boolean com.ss.bytertc.engine.SubscribeConfig.subAudio;
```
是否订阅音频


<span id="SubscribeConfig-sub_width"></span>
### sub_width
```java
public int com.ss.bytertc.engine.SubscribeConfig.sub_width = 0;
```
视频宽度，单位：px


<span id="SubscribeConfig-sub_height"></span>
### sub_height
```java
public int com.ss.bytertc.engine.SubscribeConfig.sub_height = 0;
```
视频高度，单位：px


<span id="SubscribeConfig-framerate"></span>
### framerate
```java
public int com.ss.bytertc.engine.SubscribeConfig.framerate = 0;
```
期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。  <br>
当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
仅码流支持 SVC 分级编码特性时方可生效。



## 函数说明
<span id="SubscribeConfig-subscribeconfig"></span>
### SubscribeConfig
```java
public com.ss.bytertc.engine.SubscribeConfig.SubscribeConfig(
    boolean isScreen,
    boolean subVideo,
    boolean subAudio,
    int videoIndex,
    int svcLayer,
    int sub_width,
    int sub_height,
    int sub_video_index)
```

# SVCLayer
```java
public enum com.ss.bytertc.engine.SubscribeConfig.SVCLayer
```

时域分层订阅层级


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **SVCLayerDefault(0)** | 不指定分层(默认值） |
| **SVCLayerBase(1)** | T0层 |
| **SVCLayerMain(2)** | T0+T1层 |
| **SVCLayerHigh(3)** | T0+T1+T2层 |


# SubscribeState
```java
public enum com.ss.bytertc.engine.SubscribeState
```

订阅媒体流状态


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **SUBSCRIBE_STATE_SUCCESS** | 订阅/取消订阅流成功 |
| **SUBSCRIBE_STATE_FAILED_NOT_IN_ROOM** | 订阅/取消订阅流失败，本地用户未在房间中 |
| **SUBSCRIBE_STATE_FAILED_STREAM_NOT_FOUND** | 订阅/取消订阅流失败，房间内未找到指定的音视频流 |
| **SUBSCRIBE_STATE_FAILED_SIGNAL** | 订阅/取消订阅流失败，信令错误，请重试 |


# SubscribeVideoConfig
```java
public class com.ss.bytertc.engine.SubscribeVideoConfig
```

视频订阅配置信息


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **SubscribeVideoConfig** | [SubscribeVideoConfig](#SubscribeVideoConfig-subscribevideoconfig) |


## 函数说明
<span id="SubscribeVideoConfig-subscribevideoconfig"></span>
### SubscribeVideoConfig
```java
public com.ss.bytertc.engine.SubscribeVideoConfig.SubscribeVideoConfig(
    int videoIndex,
    int priority)
```
视频订阅配置信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| videoIndex | **int** | 订阅的视频流分辨率下标。  <br/>通过此参数指定希望订阅的流。在此之前，远端用户已经通过调用 [setVideoEncoderConfig](Android-api.md#RTCVideo-setvideoencoderconfig) 方法，启动发布多路不同分辨率的视频流。编号 `0` 至 `3`代表流质量从高至低。<br/>默认值为 0，即订阅第一路流。  <br/>如果不想更改之前的设置，可以输入 -1。 |
| priority | **int** | 远端用户优先级，参看 [RemoteUserPriority](#remoteuserpriority)，默认值为 0。 |


# SysStats
```java
public class com.ss.bytertc.engine.SysStats
```

CPU 和内存统计信息


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [cpu_cores](#SysStats-cpu_cores) |
| **double** | [cpu_app_usage](#SysStats-cpu_app_usage) |
| **double** | [cpu_total_usage](#SysStats-cpu_total_usage) |
| **double** | [memory_usage](#SysStats-memory_usage) |
| **long** | [full_memory](#SysStats-full_memory) |
| **long** | [total_memory_usage](#SysStats-total_memory_usage) |
| **long** | [free_memory](#SysStats-free_memory) |
| **double** | [memory_ratio](#SysStats-memory_ratio) |
| **double** | [total_memory_ratio](#SysStats-total_memory_ratio) |


## 变量说明
<span id="SysStats-cpu_cores"></span>
### cpu_cores
```java
public int com.ss.bytertc.engine.SysStats.cpu_cores;
```
设备的 CPU 核数


<span id="SysStats-cpu_app_usage"></span>
### cpu_app_usage
```java
public double com.ss.bytertc.engine.SysStats.cpu_app_usage;
```
应用的 CPU 使用率，取值范围为 [0, 1]。


<span id="SysStats-cpu_total_usage"></span>
### cpu_total_usage
```java
public double com.ss.bytertc.engine.SysStats.cpu_total_usage;
```
系统的 CPU 使用率，取值范围为 [0, 1]。


<span id="SysStats-memory_usage"></span>
### memory_usage
```java
public double com.ss.bytertc.engine.SysStats.memory_usage;
```
应用的内存占用大小（单位 MB）


<span id="SysStats-full_memory"></span>
### full_memory
```java
public long com.ss.bytertc.engine.SysStats.full_memory;
```
设备的内存大小 单位：MB


<span id="SysStats-total_memory_usage"></span>
### total_memory_usage
```java
public long com.ss.bytertc.engine.SysStats.total_memory_usage;
```
系统已使用内存 MB


<span id="SysStats-free_memory"></span>
### free_memory
```java
public long com.ss.bytertc.engine.SysStats.free_memory;
```
系统当前空闲内存（MB）


<span id="SysStats-memory_ratio"></span>
### memory_ratio
```java
public double com.ss.bytertc.engine.SysStats.memory_ratio;
```
当前应用的内存使用率（单位 %）


<span id="SysStats-total_memory_ratio"></span>
### total_memory_ratio
```java
public double com.ss.bytertc.engine.SysStats.total_memory_ratio;
```
系统内存使用率（单位 %）



# UserInfo
```java
public class com.ss.bytertc.engine.UserInfo
```

用户信息


## 成员函数

| 返回 | 名称 |
| --- | --- |
| **UserInfo** | [UserInfo](#UserInfo-userinfo) |


## 函数说明
<span id="UserInfo-userinfo"></span>
### UserInfo
```java
public com.ss.bytertc.engine.UserInfo.UserInfo(
    String uid,
    String extraInfo)
```
用户信息

**传入参数**

| 参数名 | 类型 | 说明 |
| --- | --- | --- |
| uid | **String** | 用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-]{1,128}`。 |
| extraInfo | **String** | 用户的额外信息，最大长度为 200 字节。会在 `onUserJoined` 中回调给远端用户。 |


# VideoCanvas
```java
public class com.ss.bytertc.engine.VideoCanvas
```

视频帧渲染设置


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **int** | [RENDER_MODE_HIDDEN](#VideoCanvas-render_mode_hidden) |
| **int** | [RENDER_MODE_FIT](#VideoCanvas-render_mode_fit) |
| **int** | [RENDER_MODE_Fill](#VideoCanvas-render_mode_fill) |
| **View** | [renderView](#VideoCanvas-renderview) |
| **int** | [renderMode](#VideoCanvas-rendermode) |
| **String** | [roomId](#VideoCanvas-roomid) |
| **String** | [uid](#VideoCanvas-uid) |
| **String** | [streamId](#VideoCanvas-streamid) |
| **boolean** | [isScreen](#VideoCanvas-isscreen) |
| **int** | [background_color](#VideoCanvas-background_color) |


## 变量说明
<span id="VideoCanvas-render_mode_hidden"></span>
### RENDER_MODE_HIDDEN
```java
public static final int com.ss.bytertc.engine.VideoCanvas.RENDER_MODE_HIDDEN = 1;
```
视窗填满优先，默认值。  <br>
视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。


<span id="VideoCanvas-render_mode_fit"></span>
### RENDER_MODE_FIT
```java
public static final int com.ss.bytertc.engine.VideoCanvas.RENDER_MODE_FIT = 2;
```
视频帧内容全部显示优先。  <br>
视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将填充 `background_color`。<br>
缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。


<span id="VideoCanvas-render_mode_fill"></span>
### RENDER_MODE_Fill
```java
public static final int com.ss.bytertc.engine.VideoCanvas.RENDER_MODE_Fill = 3;
```
视频帧自适应画布 <br>
视频帧非等比缩放，直至画布被填满。在此过程中，视频帧的长宽比例可能会发生变化。


<span id="VideoCanvas-renderview"></span>
### renderView
```java
public View com.ss.bytertc.engine.VideoCanvas.renderView;
```
本地视图句柄


<span id="VideoCanvas-rendermode"></span>
### renderMode
```java
public int com.ss.bytertc.engine.VideoCanvas.renderMode;
```
渲染模式：可选 `RENDER_MODE_HIDDEN`, `RENDER_MODE_FIT` 和 `RENDER_MODE_Fill`。


<span id="VideoCanvas-roomid"></span>
### roomId
```java
public String com.ss.bytertc.engine.VideoCanvas.roomId;
```
房间 ID，必填。


<span id="VideoCanvas-uid"></span>
### uid
```java
public String com.ss.bytertc.engine.VideoCanvas.uid;
```
用户 ID


<span id="VideoCanvas-streamid"></span>
### streamId
```java
public String com.ss.bytertc.engine.VideoCanvas.streamId;
```
视图对应的公共流ID


<span id="VideoCanvas-isscreen"></span>
### isScreen
```java
public boolean com.ss.bytertc.engine.VideoCanvas.isScreen;
```
是否是屏幕流


<span id="VideoCanvas-background_color"></span>
### background_color
```java
public int com.ss.bytertc.engine.VideoCanvas.background_color;
```
用于填充画布空白部分的背景颜色。取值范围是 `[0x00000000, 0xFFFFFFFF]`。默认值是 `0x000000000`。其中，透明度设置无效。



# AudioPlayType
```java
public enum com.ss.bytertc.ktv.data.AudioPlayType
```

音乐播放类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_PLAY_TYPE_LOCAL(0)** | 仅本地播放。 |
| **AUDIO_PLAY_TYPE_REMOTE(1)** | 仅远端播放。 |
| **AUDIO_PLAY_TYPE_LOCAL_AND_REMOTE(2)** | 本地、远端同时播放。 |


# AudioTrackType
```java
public enum com.ss.bytertc.ktv.data.AudioTrackType
```

原唱伴唱类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **AUDIO_TRACK_TYPE_ORIGINAL(1)** | 播放原唱。 |
| **AUDIO_TRACK_TYPE_ACCOMPANY(2)** | 播放伴唱。 |


# DownloadFileType
```java
public enum com.ss.bytertc.ktv.data.DownloadFileType
```

下载文件类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **DOWNLOAD_FILE_TYPE_MUSIC(1)** | 音频文件。 |
| **DOWNLOAD_FILE_TYPE_KRC(2)** | KRC 歌词文件。 |
| **DOWNLOAD_FILE_TYPE_LRC(3)** | LRC 歌词文件。 |
| **DOWNLOAD_FILE_TYPE_MIDI(4)** | MIDI 文件。 |


# DownloadLyricType
```java
public enum com.ss.bytertc.ktv.data.DownloadLyricType
```

歌词文件类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **DOWNLOAD_LYRIC_TYPE_KRC(0)** | KRC 歌词文件。 |
| **DOWNLOAD_LYRIC_TYPE_LRC(1)** | LRC 歌词文件。 |


# DownloadResult
```java
public class com.ss.bytertc.ktv.data.DownloadResult
```

歌曲下载信息。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [musicId](#DownloadResult-musicid) |
| **DownloadFileType** | [fileType](#DownloadResult-filetype) |
| **String** | [filePath](#DownloadResult-filepath) |


## 变量说明
<span id="DownloadResult-musicid"></span>
### musicId
```java
public String com.ss.bytertc.ktv.data.DownloadResult.musicId;
```
音乐 ID。


<span id="DownloadResult-filetype"></span>
### fileType
```java
public DownloadFileType com.ss.bytertc.ktv.data.DownloadResult.fileType;
```
下载文件类型，参看 [DownloadFileType](#downloadfiletype)。


<span id="DownloadResult-filepath"></span>
### filePath
```java
public String com.ss.bytertc.ktv.data.DownloadResult.filePath;
```
文件存放路径。



# HotMusicInfo
```java
public class com.ss.bytertc.ktv.data.HotMusicInfo
```

热榜歌曲数据。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **MusicHotType** | [hotType](#HotMusicInfo-hottype) |
| **String** | [hotName](#HotMusicInfo-hotname) |
| **Music[]** | [musics](#HotMusicInfo-musics) |


## 变量说明
<span id="HotMusicInfo-hottype"></span>
### hotType
```java
public MusicHotType com.ss.bytertc.ktv.data.HotMusicInfo.hotType;
```
热榜类别，参看 [MusicHotType](#musichottype)。多个热榜类别可以按位或组合。


<span id="HotMusicInfo-hotname"></span>
### hotName
```java
public String com.ss.bytertc.ktv.data.HotMusicInfo.hotName;
```
热榜名称。


<span id="HotMusicInfo-musics"></span>
### musics
```java
public Music[] com.ss.bytertc.ktv.data.HotMusicInfo.musics;
```
歌曲数据，参看 [Music](#music)。



# LyricStatus
```java
public enum com.ss.bytertc.ktv.data.LyricStatus
```

歌词格式类型。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **LYRIC_STATUS_NONE(0)** | 无歌词。 |
| **LYRIC_STATUS_KRC(1)** | KRC 歌词。 |
| **LYRIC_STATUS_LRC(2)** | LRC 歌词。 |
| **LYRIC_STATUS_KRC_AND_LRC(4)** | KRC 歌词和 LRC 歌词均有。 |


# Music
```java
public class com.ss.bytertc.ktv.data.Music
```

歌曲数据。


## 成员变量

| 类型 | 名称 |
| --- | --- |
| **String** | [musicId](#Music-musicid) |
| **String** | [musicName](#Music-musicname) |
| **String** | [singer](#Music-singer) |
| **String** | [vendorId](#Music-vendorid) |
| **String** | [vendorName](#Music-vendorname) |
| **long** | [updateTimestamp](#Music-updatetimestamp) |
| **String** | [posterUrl](#Music-posterurl) |
| **LyricStatus** | [lyricStatus](#Music-lyricstatus) |
| **int** | [duration](#Music-duration) |
| **boolean** | [enableScore](#Music-enablescore) |
| **int** | [climaxStartTime](#Music-climaxstarttime) |
| **int** | [climaxEndTime](#Music-climaxendtime) |


## 变量说明
<span id="Music-musicid"></span>
### musicId
```java
public String com.ss.bytertc.ktv.data.Music.musicId;
```
音乐 ID。


<span id="Music-musicname"></span>
### musicName
```java
public String com.ss.bytertc.ktv.data.Music.musicName;
```
音乐名称。


<span id="Music-singer"></span>
### singer
```java
public String com.ss.bytertc.ktv.data.Music.singer;
```
歌手。


<span id="Music-vendorid"></span>
### vendorId
```java
public String com.ss.bytertc.ktv.data.Music.vendorId;
```
版权商 ID。


<span id="Music-vendorname"></span>
### vendorName
```java
public String com.ss.bytertc.ktv.data.Music.vendorName;
```
版权商名称。


<span id="Music-updatetimestamp"></span>
### updateTimestamp
```java
public long com.ss.bytertc.ktv.data.Music.updateTimestamp;
```
最新更新时间戳，单位为毫秒。


<span id="Music-posterurl"></span>
### posterUrl
```java
public String com.ss.bytertc.ktv.data.Music.posterUrl;
```
封面地址。


<span id="Music-lyricstatus"></span>
### lyricStatus
```java
public LyricStatus com.ss.bytertc.ktv.data.Music.lyricStatus;
```
歌词格式类型，参看 [LyricStatus](#lyricstatus)。


<span id="Music-duration"></span>
### duration
```java
public int com.ss.bytertc.ktv.data.Music.duration;
```
歌曲长度，单位为毫秒。


<span id="Music-enablescore"></span>
### enableScore
```java
public boolean com.ss.bytertc.ktv.data.Music.enableScore;
```
歌曲是否支持打分。


<span id="Music-climaxstarttime"></span>
### climaxStartTime
```java
public int com.ss.bytertc.ktv.data.Music.climaxStartTime;
```
歌曲高潮片段开始时间，单位为毫秒。


<span id="Music-climaxendtime"></span>
### climaxEndTime
```java
public int com.ss.bytertc.ktv.data.Music.climaxEndTime;
```
歌曲高潮片段停止时间，单位为毫秒。



# MusicFilterType
```java
public enum com.ss.bytertc.ktv.data.MusicFilterType
```

歌曲过滤方式。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **MUSIC_FILTER_TYPE_NONE(0)** | 不过滤。 |
| **MUSIC_FILTER_TYPE_WITHOUT_LYRIC(1<<0)** | 过滤没有歌词的歌曲。 |
| **MUSIC_FILTER_TYPE_UNSUPPORTED_SCORE(1<<1)** | 过滤不支持打分的歌曲。 |
| **MUSIC_FILTER_TYPE_UNSUPPORTED_ACCOMPANY(1<<2)** | 过滤不支持伴唱切换的歌曲。 |
| **MUSIC_FILTER_TYPE_UNSUPPORTED_CLIMAX(1<<3)** | 过滤没有高潮片段的歌曲。 |


# MusicHotType
```java
public enum com.ss.bytertc.ktv.data.MusicHotType
```

热榜类别。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **MUSIC_HOT_TYPE_CONTENT_CENTER(1 << 0)** | 火山内容中心热歌榜。 |
| **MUSIC_HOT_TYPE_PROJECT(1 << 1)** | 项目热歌榜。 |


# PlayState
```java
public enum com.ss.bytertc.ktv.data.PlayState
```

音乐播放状态。


## 枚举值

| 类型 | 说明 |
| --- | --- |
| **PLAY_STATE_PLAYING(1)** | 播放中。 |
| **PLAY_STATE_PAUSED(2)** | 暂停中。 |
| **PLAY_STATE_STOPPED(3)** | 已停止。 |
| **PLAY_STATE_FAILED(4)** | 播放失败。 |
| **PLAY_STATE_FINISHED(5)** | 播放结束。 |