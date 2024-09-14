## AudioEffectPlayerConfig <span id="audioeffectplayerconfig"></span>

类型: `interface`

混音配置

<p style="font-size: 16px;font-weight: bolder;"> type <span id="audioeffectplayerconfig-type"></span></p> 

类型: [AudioMixingType](#audiomixingtype)

混音播放类型

<p style="font-size: 16px;font-weight: bolder;"> play_count <span id="audioeffectplayerconfig-play_count"></span></p> 

类型: number

混音播放次数

+ play_count <= 0: 无限循环
+ play_count == 1: 播放一次（默认）
+ play_count > 1: 播放 play_count 次

<p style="font-size: 16px;font-weight: bolder;"> pitch <span id="audioeffectplayerconfig-pitch"></span></p> 

类型: number

与音乐文件原始音调相比的升高/降低值，取值范围为 `[-12，12]`，默认值为 0。每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调。

<p style="font-size: 16px;font-weight: bolder;"> start_pos <span id="audioeffectplayerconfig-start_pos"></span></p> 

类型: number

混音起始位置。默认值为 0，单位为毫秒。


## AudioMixingType <span id="audiomixingtype"></span>

类型: `enum`

混音播放类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioMixingTypePlayout | `0` | 仅本地播放 |
  | kAudioMixingTypePublish | `1` | 仅远端播放 |
  | kAudioMixingTypePlayoutAndPublish | `2` | 本地和远端同时播放 |



## MediaPlayerConfig <span id="mediaplayerconfig"></span>

类型: `interface`

混音配置

<p style="font-size: 16px;font-weight: bolder;"> play_count <span id="mediaplayerconfig-play_count"></span></p> 

类型: number

混音播放次数

+ play_count <= 0: 无限循环
+ play_count == 1: 播放一次（默认）
+ play_count > 1: 播放 play_count 次

<p style="font-size: 16px;font-weight: bolder;"> start_pos <span id="mediaplayerconfig-start_pos"></span></p> 

类型: number

混音起始位置。默认值为 0，单位为毫秒。

<p style="font-size: 16px;font-weight: bolder;"> callback_on_progress_interval <span id="mediaplayerconfig-callback_on_progress_interval"></span></p> 

类型: string

设置音频文件混音时，收到 [`onMediaPlayerPlayingProgress`](Electron-event.md#rtcmediaplayercallback-onmediaplayerplayingprogress) 的间隔。单位毫秒。

+ interval > 0 时，触发回调。实际间隔为 10 的倍数。如果输入数值不能被 10 整除，将自动向上取整。例如传入 `52`，实际间隔为 60 ms。
+ interval <= 0 时，不会触发回调。

<p style="font-size: 16px;font-weight: bolder;"> sync_progress_to_record_frame <span id="mediaplayerconfig-sync_progress_to_record_frame"></span></p> 

类型: boolean

在采集音频数据时，附带本地混音文件播放进度的时间戳。启用此功能会提升远端人声和音频文件混音播放时的同步效果。

- **注意**

  + 仅在单个音频文件混音时使用有效。
  + `true` 时开启此功能，`false` 时关闭此功能，默认为关闭。

<p style="font-size: 16px;font-weight: bolder;"> auto_play <span id="mediaplayerconfig-auto_play"></span></p> 

类型: boolean

是否自动播放。如果不自动播放，调用 [`startAudioMixing`](Electron-api.md#rtcvideo-startaudiomixing) 播放音乐文件。

<p style="font-size: 16px;font-weight: bolder;"> type <span id="mediaplayerconfig-type"></span></p> 

类型: [AudioMixingType](#audiomixingtype)

混音播放类型


## AudioMixingDualMonoMode <span id="audiomixingdualmonomode"></span>

类型: `enum`

混音播放声道类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioMixingDualMonoModeAuto | `0` | 和音频文件一致 |
  | kAudioMixingDualMonoModeL | `1` | 只能听到音频文件中左声道的音频 |
  | kAudioMixingDualMonoModeR | `2` | 只能听到音频文件中右声道的音频 |
  | kAudioMixingDualMonoModeMix | `3` | 能同时听到音频文件中左右声道的音频 |



## MediaPlayerCustomSource <span id="mediaplayercustomsource"></span>

类型: `interface`

自定义音频源模式

<p style="font-size: 16px;font-weight: bolder;"> mode <span id="mediaplayercustomsource-mode"></span></p> 

类型: [MediaPlayerCustomSourceMode](#mediaplayercustomsourcemode)

数据源模式

<p style="font-size: 16px;font-weight: bolder;"> type <span id="mediaplayercustomsource-type"></span></p> 

类型: [MediaPlayerCustomSourceStreamType](#mediaplayercustomsourcestreamtype)

数据源类型


## MediaPlayerCustomSourceMode <span id="mediaplayercustomsourcemode"></span>

类型: `enum`

自定义音频源模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMediaPlayerCustomSourceModePush | `0` | 当播放来自本地的 PCM 数据时，使用此选项。 |
  | kMediaPlayerCustomSourceModePull | `1` | 当播放来自内存的音频数据时，使用此选项。 |



## MediaPlayerCustomSourceStreamType <span id="mediaplayercustomsourcestreamtype"></span>

类型: `enum`

自定义音频流类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMediaPlayerCustomSourceStreamTypeRaw | `0` | 当播放来自本地的 PCM 数据时，使用此选项。 |
  | kMediaPlayerCustomSourceStreamTypeEncoded | `1` | 当播放来自内存的音频数据时，使用此选项。 |



## ExternalAudioFrame <span id="externalaudioframe"></span>

类型: `interface`

外部音频帧

<p style="font-size: 16px;font-weight: bolder;"> frame_type <span id="externalaudioframe-frame_type"></span></p> 

类型: AudioFrameType

值: `0`

音频帧类型。目前只支持 PCM

<p style="font-size: 16px;font-weight: bolder;"> sample_rate <span id="externalaudioframe-sample_rate"></span></p> 

类型: [AudioSampleRate](#audiosamplerate)

音频采样率，单位：Hz

<p style="font-size: 16px;font-weight: bolder;"> channel <span id="externalaudioframe-channel"></span></p> 

类型: [AudioChannel](#audiochannel)

音频通道数。双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。

<p style="font-size: 16px;font-weight: bolder;"> timestamp_ms <span id="externalaudioframe-timestamp_ms"></span></p> 

类型: number | undefined

音频帧时间戳，单位：毫秒

<p style="font-size: 16px;font-weight: bolder;"> data <span id="externalaudioframe-data"></span></p> 

类型: Uint8Array

音频帧数据: 音频帧数据只支持 PCM 格式, 只支持 10ms 帧长
帧长度计算: 48000采样率、单声道的帧长度: 48000 × 0.01s × 1 × 16bit = 7680bit = 960字节


## AudioSampleRate <span id="audiosamplerate"></span>

类型: `enum`

音频采样率，单位为 HZ。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioSampleRateAuto | `-1` | 默认设置。48000Hz。 |
  | kAudioSampleRate8000 | `8000` | 8000 Hz 采样率 |
  | kAudioSampleRate16000 | `16000` | 16000 Hz 采样率 |
  | kAudioSampleRate32000 | `32000` | 32000 Hz 采样率 |
  | kAudioSampleRate44100 | `44100` | 44100 Hz 采样率 |
  | kAudioSampleRate48000 | `48000` | 48000 Hz 采样率 |



## AudioChannel <span id="audiochannel"></span>

类型: `enum`

音频声道。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioChannelAuto | `-1` | 默认设置。 |
  | kAudioChannelMono | `1` | 单声道 |
  | kAudioChannelStereo | `2` | 双声道 |



## ProblemFeedbackOption <span id="problemfeedbackoption"></span>

类型: `enum`

反馈信息类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kProblemFeedbackOptionNone | `0` | 没有问题 |
  | kProblemFeedbackOptionOtherMessage | `1` | 其他问题 |
  | kProblemFeedbackOptionDisconnected | `2` | 连接失败 |
  | kProblemFeedbackOptionEarBackDelay | `3` | 耳返延迟大 |
  | kProblemFeedbackOptionLocalNoise | `11` | 本端有杂音 |
  | kProblemFeedbackOptionLocalAudioLagging | `12` | 本端声音卡顿 |
  | kProblemFeedbackOptionLocalNoAudio | `13` | 本端无声音 |
  | kProblemFeedbackOptionLocalAudioStrength | `14` | 本端声音大/小 |
  | kProblemFeedbackOptionLocalEcho | `15` | 本端有回声 |
  | kProblemFeedbackOptionLocalVideoFuzzy | `25` | 本端视频模糊 |
  | kProblemFeedbackOptionLocalNotSync | `26` | 本端音视频不同步 |
  | kProblemFeedbackOptionLocalVideoLagging | `27` | 本端视频卡顿 |
  | kProblemFeedbackOptionLocalNoVideo | `28` | 本端无画面 |
  | kProblemFeedbackOptionRemoteNoise | `38` | 远端有杂音 |
  | kProblemFeedbackOptionRemoteAudioLagging | `39` | 远端声音卡顿 |
  | kProblemFeedbackOptionRemoteNoAudio | `40` | 远端无声音 |
  | kProblemFeedbackOptionRemoteAudioStrength | `41` | 远端声音大/小 |
  | kProblemFeedbackOptionRemoteEcho | `42` | 远端有回声 |
  | kProblemFeedbackOptionRemoteVideoFuzzy | `52` | 远端视频模糊 |
  | kProblemFeedbackOptionRemoteNotSync | `53` | 远端音视频不同步 |
  | kProblemFeedbackOptionRemoteVideoLagging | `54` | 远端视频卡顿 |
  | kProblemFeedbackOptionRemoteNoVideo | `55` | 远端无画面 |



## ProblemFeedbackInfo <span id="problemfeedbackinfo"></span>

类型: `interface`

音视频质量反馈的信息

<p style="font-size: 16px;font-weight: bolder;"> problem_desc <span id="problemfeedbackinfo-problem_desc"></span></p> 

类型: string

预设问题以外的其他问题的具体描述。

<p style="font-size: 16px;font-weight: bolder;"> room_info <span id="problemfeedbackinfo-room_info"></span></p> 

类型: [ProblemFeedbackRoomInfo](#problemfeedbackroominfo)[]

音视频质量反馈的房间信息。


## ProblemFeedbackRoomInfo <span id="problemfeedbackroominfo"></span>

类型: `interface`

音视频质量反馈的房间信息

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="problemfeedbackroominfo-room_id"></span></p> 

类型: string

房间 ID。

<p style="font-size: 16px;font-weight: bolder;"> user_id <span id="problemfeedbackroominfo-user_id"></span></p> 

类型: string

本地用户 ID。


## RTCPluginInfo <span id="rtcplugininfo"></span>

类型: `interface`

插件信息

<p style="font-size: 16px;font-weight: bolder;"> id <span id="rtcplugininfo-id"></span></p> 

类型: string

插件 ID，插件唯一标识

<p style="font-size: 16px;font-weight: bolder;"> path <span id="rtcplugininfo-path"></span></p> 

类型: string

插件库路径


## RTCPlugin <span id="rtcplugin"></span>

类型: `interface`

插件定义

<p style="font-size: 16px;font-weight: bolder;"> id <span id="rtcplugin-id"></span></p> 

类型: string

插件 ID，插件唯一标识

<p style="font-size: 16px;font-weight: bolder;"> setEnabled <span id="rtcplugin-setenabled"></span></p> 

启用插件

- **类型**

  ```ts
  (enabled: boolean) => number
  ```

- **参数**

  - **enabled**

    类型: boolean

    是否启用插件

- **返回值**

  类型: number

  + `0`: 成功
  + `-1`: 失败

<p style="font-size: 16px;font-weight: bolder;"> setParameter <span id="rtcplugin-setparameter"></span></p> 

设置参数

- **类型**

  ```ts
  (json_string: string) => number
  ```

- **参数**

  - **json_string**

    类型: string

    json 字符串

- **返回值**

  类型: number

  + `0`: 成功
  + `-1`: 失败


## EchoTestConfig <span id="echotestconfig"></span>

类型: `interface`

音视频回路测试参数

<p style="font-size: 16px;font-weight: bolder;"> audio_properties_report_interval <span id="echotestconfig-audio_properties_report_interval"></span></p> 

类型: number

音量信息提示间隔，单位：ms，默认为 100ms
+`<= 0`: 关闭信息提示
+`(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms
+`> 100`: 开启信息提示，并将信息提示间隔设置为此值

<p style="font-size: 16px;font-weight: bolder;"> uid <span id="echotestconfig-uid"></span></p> 

类型: string

进行音视频通话回路测试的用户 ID

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="echotestconfig-room_id"></span></p> 

类型: string

测试用户加入的房间 ID。

<p style="font-size: 16px;font-weight: bolder;"> token <span id="echotestconfig-token"></span></p> 

类型: string

对用户进房时进行鉴权验证的动态密钥，用于保证音视频通话回路测试的安全性。

<p style="font-size: 16px;font-weight: bolder;"> enable_audio <span id="echotestconfig-enable_audio"></span></p> 

类型: boolean

是否检测音频。检测设备为系统默认音频设备。  

+ true：是  
    - 若使用 SDK 内部采集，此时设备麦克风会自动开启，并在 audioPropertiesReportInterval 值大于 0 时触发 onLocalAudioPropertiesReport 回调，你可以根据该回调判断麦克风的工作状态  
    - 若使用自定义采集，此时你需调用 [`pushExternalAudioFrame`](Electron-api.md#rtcvideo-pushexternalaudioframe) 将采集到的音频推送给 SDK  
+ false：否

<p style="font-size: 16px;font-weight: bolder;"> enable_video <span id="echotestconfig-enable_video"></span></p> 

类型: boolean

是否检测视频。PC 端默认检测列表中第一个视频设备。  

+ true：是  
    - 若使用 SDK 内部采集，此时设备摄像头会自动开启  
    - 若使用自定义采集，此时你需调用 [`pushExternalVideoFrame`](Electron-api.md#rtcvideo-pushexternalvideoframe) 将采集到的视频推送给 SDK  
+ false：否  
视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。


## AudioPropertiesConfig <span id="audiopropertiesconfig"></span>

类型: `interface`

音频属性信息提示的相关配置。

<p style="font-size: 16px;font-weight: bolder;"> interval <span id="audiopropertiesconfig-interval"></span></p> 

类型: number

信息提示间隔，单位：ms

+ `<= 0`: 关闭信息提示
+ `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms
+ `> 100`: 开启信息提示，并将信息提示间隔设置为此值

<p style="font-size: 16px;font-weight: bolder;"> enable_spectrum <span id="audiopropertiesconfig-enable_spectrum"></span></p> 

类型: boolean | undefined

是否开启音频频谱检测。

<p style="font-size: 16px;font-weight: bolder;"> enable_vad <span id="audiopropertiesconfig-enable_vad"></span></p> 

类型: boolean | undefined

是否开启人声检测 (VAD)。

<p style="font-size: 16px;font-weight: bolder;"> local_main_report_mode <span id="audiopropertiesconfig-local_main_report_mode"></span></p> 

类型: [AudioReportMode](#audioreportmode) | undefined

音量回调配置模式。

<p style="font-size: 16px;font-weight: bolder;"> audio_report_mode <span id="audiopropertiesconfig-audio_report_mode"></span></p> 

类型: [AudioPropertiesMode](#audiopropertiesmode) | undefined

设置 [`onLocalAudioPropertiesReport`](Electron-event.md#onlocalaudiopropertiesreport) 回调中是否包含本地混音音频数据。
默认仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。

<p style="font-size: 16px;font-weight: bolder;"> smooth <span id="audiopropertiesconfig-smooth"></span></p> 

类型: number | undefined

适用于音频属性信息提示的平滑系数。取值范围是 `(0.0, 1.0]`。
默认值为 `1.0`，不开启平滑效果；值越小，提示音量平滑效果越明显。如果要开启平滑效果，可以设置为 `0.3`。

<p style="font-size: 16px;font-weight: bolder;"> enable_voice_pitch <span id="audiopropertiesconfig-enable_voice_pitch"></span></p> 

类型: boolean | undefined

是否回调本地用户的人声基频。


## AudioReportMode <span id="audioreportmode"></span>

类型: `enum`

音量回调模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioReportModeNormal | `0` | 默认始终开启音量回调。 |
  | kAudioReportModeDisconnect | `1` | 可见用户进房并停止推流后，关闭音量回调。 |
  | kAudioReportModeReset | `2` | 可见用户进房并停止推流后，开启音量回调，回调值重置为0。 |



## AudioPropertiesMode <span id="audiopropertiesmode"></span>

类型: `enum`

音频信息提示中是否包含本地混音音频数据。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioPropertiesModeMicrophone | `0` | 音频信息提示中，仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。 |
  | kAudioPropertiesModeAudioMixing | `1` | 音频信息提示中，除本地麦克风采集的音频数据和本地屏幕音频采集数据外，还包含本地混音的音频数据。 |



## VideoEncoderConfig <span id="videoencoderconfig"></span>

类型: `interface`

视频流参数

<p style="font-size: 16px;font-weight: bolder;"> width <span id="videoencoderconfig-width"></span></p> 

类型: number

视频宽度，单位：像素

<p style="font-size: 16px;font-weight: bolder;"> height <span id="videoencoderconfig-height"></span></p> 

类型: number

视频高度，单位：像素

<p style="font-size: 16px;font-weight: bolder;"> frame_rate <span id="videoencoderconfig-frame_rate"></span></p> 

类型: number

视频帧率，单位：fps

<p style="font-size: 16px;font-weight: bolder;"> max_bitrate <span id="videoencoderconfig-max_bitrate"></span></p> 

类型: number | undefined

最大发送编码码率（kbps），建议使用默认的自动码率。<li>-1: 自动码率</li><li>0: 不开启上限</li><li>>0: 填写预估码率<li>
设为 0 则不对视频流进行编码发送。

<p style="font-size: 16px;font-weight: bolder;"> min_bitrate <span id="videoencoderconfig-min_bitrate"></span></p> 

类型: number | undefined

视频最小编码码率, 单位 kbps。编码码率不会低于 `minBitrate`。
默认值为 `0`。
范围：[0, maxBitrate)，当 `maxBitrate` < `minBitrate` 时，为适配码率模式。
以下情况，设置本参数无效：

+ 当 `maxBitrate` 为 `0` 时，不对视频流进行编码发送。
+ 当 `maxBitrate` < `0` 时，适配码率模式。

<p style="font-size: 16px;font-weight: bolder;"> encoder_preference <span id="videoencoderconfig-encoder_preference"></span></p> 

类型: [VideoEncodePreference](#videoencodepreference) | undefined

视频编码质量策略


## VideoEncodePreference <span id="videoencodepreference"></span>

类型: `enum`

编码策略偏好

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kVideoEncodePreferenceDisabled | `0` | 无偏好。不降低帧率和分辨率。 |
  | kVideoEncodePreferenceFramerate | `1` | （默认值）帧率优先。分辨率不变。 |
  | kVideoEncodePreferenceQuality | `2` | 分辨率优先。 |
  | kVideoEncodePreferenceBalance | `3` | 平衡帧率与分辨率。 |



## StreamIndex <span id="streamindex"></span>

类型: `enum`

流属性

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kStreamIndexMain | `0` | 主流。包括：通过默认摄像头/麦克风采集到的视频/音频; |
  | kStreamIndexScreen | `1` | 屏幕流。<br>屏幕共享时共享的视频流，或来自声卡的本地播放音频流。 |



## AlphaLayout <span id="alphalayout"></span>

类型: `enum`

编码 Alpha 通道视频帧的布局

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAlphaLayoutTop | `0` | Alpha 数据布局到上方 |



## MirrorType <span id="mirrortype"></span>

类型: `enum`

镜像类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMirrorTypeNone | `0` | 本地预览和编码传输时均无镜像效果 |
  | kMirrorTypeRender | `1` | 本地预览时有镜像效果，编码传输时无镜像效果 |
  | kMirrorTypeRenderAndEncoder | `3` | 本地预览和编码传输时均有镜像效果 |



## EffectBeautyMode <span id="effectbeautymode"></span>

类型: `enum`

基础美颜模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kEffectBeautyWhite | `0` | 美白 |
  | kEffectBeautySmooth | `1` | 磨皮 |
  | kEffectBeautySharpen | `2` | 锐化 |
  | kEffectBeautyModeClear | `3` | 清晰，需集成 v4.4.2+ 版本的特效 SDK。 |



## VideoSourceType <span id="videosourcetype"></span>

类型: `enum`

视频输入源类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kVideoSourceTypeExternal | `0` | 自定义采集视频源 |
  | kVideoSourceTypeInternal | `1` | 内部采集视频源 |



## ExternalVideoFrame <span id="externalvideoframe"></span>

类型: `interface`

外部视频帧

<p style="font-size: 16px;font-weight: bolder;"> pixel_fmt <span id="externalvideoframe-pixel_fmt"></span></p> 

类型: [VideoPixelFormat](#videopixelformat)

视频帧像素格式

<p style="font-size: 16px;font-weight: bolder;"> color_space <span id="externalvideoframe-color_space"></span></p> 

类型: [ColorSpace](#colorspace) | undefined

视频帧颜色空间

<p style="font-size: 16px;font-weight: bolder;"> data <span id="externalvideoframe-data"></span></p> 

类型: [(Uint8Array | undefined)?, (Uint8Array | undefined)?, (Uint8Array | undefined)?]

视频帧数据平面指针数组
I420数据：data[0]: y; data[1]: u; data[2]: v;
NV12数据：data[0]: y; data[1]: uv;
RGBA、ARGB、BGRA数据: data[0]: rgba/argb/bgra;

<p style="font-size: 16px;font-weight: bolder;"> linesize <span id="externalvideoframe-linesize"></span></p> 

类型: [(number | undefined)?, (number | undefined)?, (number | undefined)?]

视频帧数据平面行长度
I420数据：linesize[0]: width; linesize[1]: width/2; linesize[2]: width/2;
NV12数据：linesize[0]: width; linesize[1]: width;
RGBA、ARGB、BGRA数据：linesize[0]: width*4;

<p style="font-size: 16px;font-weight: bolder;"> extra_data <span id="externalvideoframe-extra_data"></span></p> 

类型: Uint8Array | undefined

SEI 数据地址

<p style="font-size: 16px;font-weight: bolder;"> supplementary_info <span id="externalvideoframe-supplementary_info"></span></p> 

类型: Uint8Array | undefined

补充数据地址

<p style="font-size: 16px;font-weight: bolder;"> width <span id="externalvideoframe-width"></span></p> 

类型: number

视频帧宽度

<p style="font-size: 16px;font-weight: bolder;"> height <span id="externalvideoframe-height"></span></p> 

类型: number

视频帧高度

<p style="font-size: 16px;font-weight: bolder;"> rotation <span id="externalvideoframe-rotation"></span></p> 

类型: [VideoRotation](#videorotation) | undefined

视频旋转角度。
当视频接收端使用 RTC SDK 内部渲染时，引擎会根据设定的 rotation 处理旋转角度后再行渲染；
当视频接收端使用自定义渲染时，此处设置的 rotation 无效。

<p style="font-size: 16px;font-weight: bolder;"> timestamp_ms <span id="externalvideoframe-timestamp_ms"></span></p> 

类型: number | undefined

视频帧时间戳, 单位毫秒


## VideoPixelFormat <span id="videopixelformat"></span>

类型: `enum`

视频帧颜色编码格式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kVideoPixelFormatUnknown | `0` | 未知的颜色编码格式 |
  | kVideoPixelFormatI420 | `1` | YUV I420 格式 |
  | kVideoPixelFormatNV12 | `2` | YUV NV12 格式 |
  | kVideoPixelFormatNV21 | `3` | YUV NV21 格式 |
  | kVideoPixelFormatRGB24 | `4` | RGB 24bit格式， |
  | kVideoPixelFormatRGBA | `5` | RGBA 编码格式 |
  | kVideoPixelFormatARGB | `6` | ARGB 编码格式 |
  | kVideoPixelFormatBGRA | `7` | BGRA 编码格式 |



## ColorSpace <span id="colorspace"></span>

类型: `enum`

视频 YUV 格式颜色空间

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kColorSpaceUnknown | `0` | 未知的颜色空间，默认使用 kColorSpaceYCbCrBT601LimitedRange 颜色空间 |
  | kColorSpaceYCbCrBT601LimitedRange | `1` | BT.601 数字编码标准，颜色空间 [16-235] |
  | kColorSpaceYCbCrBT601FullRange | `2` | BT.601 数字编码标准，颜色空间 [0-255] |
  | kColorSpaceYCbCrBT709LimitedRange | `3` | BT.7091 数字编码标准，颜色空间 [16-235] |
  | kColorSpaceYCbCrBT709FullRange | `4` | BT.7091 数字编码标准，颜色空间 [0-255] |



## VideoRotation <span id="videorotation"></span>

类型: `enum`

视频旋转信息，枚举类型，定义了以 90 度为间隔的四种旋转模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kVideoRotation0 | `0` | 顺时针旋转 0 度 |
  | kVideoRotation90 | `90` | 顺时针旋转 90 度 |
  | kVideoRotation180 | `180` | 顺时针旋转 180 度 |
  | kVideoRotation270 | `270` | 顺时针旋转 270 度 |



## AudioSourceType <span id="audiosourcetype"></span>

类型: `enum`

音频输入源类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioSourceTypeExternal | `0` | 自定义采集音频源 |
  | kAudioSourceTypeInternal | `1` | RTC SDK 内部采集音频源 |



## PushSingleStreamParam <span id="pushsinglestreamparam"></span>

类型: `interface`

单流转推直播配置参数。

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="pushsinglestreamparam-room_id"></span></p> 

类型: string

媒体流所在的房间 ID。必填。

<p style="font-size: 16px;font-weight: bolder;"> user_id <span id="pushsinglestreamparam-user_id"></span></p> 

类型: string

媒体流所属的用户 ID

<p style="font-size: 16px;font-weight: bolder;"> uri <span id="pushsinglestreamparam-uri"></span></p> 

类型: string

推流地址

<p style="font-size: 16px;font-weight: bolder;"> is_screen_stream <span id="pushsinglestreamparam-is_screen_stream"></span></p> 

类型: boolean

媒体流是否为屏幕流。


## AnsMode <span id="ansmode"></span>

类型: `enum`

降噪模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAnsModeDisable | `0` | 禁用音频降噪。 |
  | kAnsModeLow | `1` | 适用于微弱降噪。 |
  | kAnsModeMedium | `2` | 适用于抑制中度平稳噪音，如空调声、风扇声。 |
  | kAnsModeHigh | `3` | 适用于抑制嘈杂非平稳噪音，如键盘声、敲击声、碰撞声、动物叫声。 |
  | kAnsModeAutomatic | `4` | 启用音频降噪能力。具体的降噪算法由 RTC 决定。 |



## RemoteStreamKey <span id="remotestreamkey"></span>

类型: `interface`

远端流信息

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="remotestreamkey-room_id"></span></p> 

类型: string

媒体流所在房间的房间 ID。
如果此媒体流是通过 `startForwardStreamToRooms` 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。

<p style="font-size: 16px;font-weight: bolder;"> user_id <span id="remotestreamkey-user_id"></span></p> 

类型: string

用户 ID

<p style="font-size: 16px;font-weight: bolder;"> stream_index <span id="remotestreamkey-stream_index"></span></p> 

类型: [StreamIndex](#streamindex)

流属性，主流或屏幕流。


## StreamSycnInfoConfig <span id="streamsycninfoconfig"></span>

类型: `interface`

媒体流信息同步的相关配置

<p style="font-size: 16px;font-weight: bolder;"> stream_index <span id="streamsycninfoconfig-stream_index"></span></p> 

类型: [StreamIndex](#streamindex)

流属性，主流或屏幕流。

<p style="font-size: 16px;font-weight: bolder;"> repeat_count <span id="streamsycninfoconfig-repeat_count"></span></p> 

类型: number

消息发送的重复次数，取值范围是 [0,25]，建议设置为 [3,5]。

<p style="font-size: 16px;font-weight: bolder;"> stream_type <span id="streamsycninfoconfig-stream_type"></span></p> 

类型: SyncInfoStreamType

值: `0`

媒体流信息同步的流类型，


## CloudProxyInfo <span id="cloudproxyinfo"></span>

类型: `interface`

云代理信息

<p style="font-size: 16px;font-weight: bolder;"> cloud_proxy_ip <span id="cloudproxyinfo-cloud_proxy_ip"></span></p> 

类型: string

云代理服务器 IP

<p style="font-size: 16px;font-weight: bolder;"> cloud_proxy_port <span id="cloudproxyinfo-cloud_proxy_port"></span></p> 

类型: number

云代理服务器端口


## IPublicStreamParam <span id="ipublicstreamparam"></span>

类型: `interface`

公共流参数

<p style="font-size: 16px;font-weight: bolder;"> interpolation_mode <span id="ipublicstreamparam-interpolation_mode"></span></p> 

类型: number

补帧模式

+ `0`: 补最后一帧
+ `1`: 补背景图片，如果没有设置背景图片则补黑帧

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="ipublicstreamparam-room_id"></span></p> 

类型: string

合流房间 ID，必填

<p style="font-size: 16px;font-weight: bolder;"> background_image_uri <span id="ipublicstreamparam-background_image_uri"></span></p> 

类型: string

背景图片链接

<p style="font-size: 16px;font-weight: bolder;"> video_param <span id="ipublicstreamparam-video_param"></span></p> 

类型: [PublicStreamVideoParam](#publicstreamvideoparam)

公共流视频参数。

<p style="font-size: 16px;font-weight: bolder;"> layout_regions <span id="ipublicstreamparam-layout_regions"></span></p> 

类型: [PublicStreamLayoutRegion](#publicstreamlayoutregion)[]

公共流视窗布局信息。

<p style="font-size: 16px;font-weight: bolder;"> layout_mode <span id="ipublicstreamparam-layout_mode"></span></p> 

类型: [StreamLayoutMode](#streamlayoutmode)

公共流的布局模式

<p style="font-size: 16px;font-weight: bolder;"> bg_color <span id="ipublicstreamparam-bg_color"></span></p> 

类型: string

背景颜色


## PublicStreamVideoParam <span id="publicstreamvideoparam"></span>

类型: `interface`

公共流视频编码参数

<p style="font-size: 16px;font-weight: bolder;"> width <span id="publicstreamvideoparam-width"></span></p> 

类型: number

公共流视频宽度，必填。单位为 px，范围为 [2, 1920]，必须是偶数。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="publicstreamvideoparam-height"></span></p> 

类型: number

公共流视频高度，必填。单位为 px，范围为 [16, 1280]，必须是偶数。

<p style="font-size: 16px;font-weight: bolder;"> fps <span id="publicstreamvideoparam-fps"></span></p> 

类型: number

公共流视频帧率。必填
范围：[1, 60]

<p style="font-size: 16px;font-weight: bolder;"> bitrate_kpbs <span id="publicstreamvideoparam-bitrate_kpbs"></span></p> 

类型: number

视频码率，必填
范围：[1,10000000]
单位为 bps


## PublicStreamLayoutRegion <span id="publicstreamlayoutregion"></span>

类型: `interface`

单个视频流在公共流中的布局信息。
在多路视频流公共流时，你需要设置每一路视频流在公共流中的布局信息。

<p style="font-size: 16px;font-weight: bolder;"> user_id <span id="publicstreamlayoutregion-user_id"></span></p> 

类型: string

目标公共流用户的 ID, 不能为空

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="publicstreamlayoutregion-room_id"></span></p> 

类型: string

跨房间订阅流时，目标流所在的房间 ID, 不能为空

<p style="font-size: 16px;font-weight: bolder;"> alternate_image_uri <span id="publicstreamlayoutregion-alternate_image_uri"></span></p> 

类型: string

背景图片地址

<p style="font-size: 16px;font-weight: bolder;"> x <span id="publicstreamlayoutregion-x"></span></p> 

类型: number

用户视频布局相对画布左侧的偏移量，取值的范围为 [0.0, 1.0)。必填。

<p style="font-size: 16px;font-weight: bolder;"> y <span id="publicstreamlayoutregion-y"></span></p> 

类型: number

用户视频布局相对画布顶端的偏移量，取值的范围为 [0.0, 1.0)。必填。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="publicstreamlayoutregion-width"></span></p> 

类型: number

用户视频宽度相对画布宽度的比例，取值的范围为 (0.0, 1.0]。必填。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="publicstreamlayoutregion-height"></span></p> 

类型: number

用户视频高度相对画布高度的比例，取值的范围为 (0.0, 1.0]。必填。

<p style="font-size: 16px;font-weight: bolder;"> alpha <span id="publicstreamlayoutregion-alpha"></span></p> 

类型: number

透明度，取值范围 [0，255], 0 为全透明，255 为不透明

<p style="font-size: 16px;font-weight: bolder;"> z_order <span id="publicstreamlayoutregion-z_order"></span></p> 

类型: number

用户视频布局在画布中的层级，取值范围 [0，100]，0(默认）为底层，100 为顶层。

<p style="font-size: 16px;font-weight: bolder;"> stream_type <span id="publicstreamlayoutregion-stream_type"></span></p> 

类型: number

必填。媒体流类型：

+ 0: 普通流（默认设置）
+ 1: 屏幕流

<p style="font-size: 16px;font-weight: bolder;"> media_type <span id="publicstreamlayoutregion-media_type"></span></p> 

类型: [TranscoderContentControlType](#transcodercontentcontroltype)

公共流输出类型。

<p style="font-size: 16px;font-weight: bolder;"> render_mode <span id="publicstreamlayoutregion-render_mode"></span></p> 

类型: [PublicStreamRenderMode](#publicstreamrendermode)

渲染时，视频内容缩放模式，必填。

<p style="font-size: 16px;font-weight: bolder;"> source_crop <span id="publicstreamlayoutregion-source_crop"></span></p> 

类型: [SourceCrop](#sourcecrop)

支持对每一路参与公共流的视频进行裁剪。


## TranscoderContentControlType <span id="transcodercontentcontroltype"></span>

类型: `enum`

合流输出内容类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kHasAudioAndVideo | `0` | 音视频 |
  | kHasAudioOnly | `1` | 音频 |
  | kHasVideoOnly | `2` | 视频 |



## PublicStreamRenderMode <span id="publicstreamrendermode"></span>

类型: `enum`

渲染模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRenderModeHidden | `1` | 视窗填满优先，默认值。<br>视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。 |
  | kRenderModeFit | `2` | 视频帧内容全部显示优先。<br>视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。 |
  | kRenderModeFill | `3` | 视频帧自适应画布<br>视频帧非等比缩放，直至画布被填满。在此过程中，视频帧的长宽比例可能会发生变化。 |



## SourceCrop <span id="sourcecrop"></span>

类型: `interface`

公共流视频裁剪配置

<p style="font-size: 16px;font-weight: bolder;"> location_x <span id="sourcecrop-location_x"></span></p> 

类型: number

裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)

<p style="font-size: 16px;font-weight: bolder;"> location_y <span id="sourcecrop-location_y"></span></p> 

类型: number

裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)

<p style="font-size: 16px;font-weight: bolder;"> width_proportion <span id="sourcecrop-width_proportion"></span></p> 

类型: number

裁剪后得到的视频帧宽度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]

<p style="font-size: 16px;font-weight: bolder;"> height_proportion <span id="sourcecrop-height_proportion"></span></p> 

类型: number

裁剪后得到的视频帧高度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]


## StreamLayoutMode <span id="streamlayoutmode"></span>

类型: `enum`

公共流的布局模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kStreamLayoutModeAuto | `0` | （默认）自动布局 |
  | kStreamLayoutModeCustom | `2` | 自定义 |



## RenderOptions <span id="renderoptions"></span>

类型: `interface`

本地渲染选项

<p style="font-size: 16px;font-weight: bolder;"> render_mode <span id="renderoptions-render_mode"></span></p> 

类型: [RenderMode](#rendermode)

渲染时，视频内容缩放模式

<p style="font-size: 16px;font-weight: bolder;"> mirror <span id="renderoptions-mirror"></span></p> 

类型: boolean

是否镜像渲染


## RenderMode <span id="rendermode"></span>

类型: `enum`

渲染时，视频内容缩放模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | FIT | `1` | 视频帧内容全部显示优先。<br>视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。 |
  | HIDDEN | `2` | 视窗填满优先。<br>视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。 |



## PixelFormat <span id="pixelformat"></span>

类型: `enum`

视频帧编码格式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kI420 |  | YUV I420 格式 |
  | kRGBA |  | RGBA 格式, 字节序为 R8 G8 B8 A8 |



## ScreenCaptureSourceInfo <span id="screencapturesourceinfo"></span>

类型: `interface`

屏幕共享对象信息
[`startScreenVideoCapture`](Electron-api.md#rtcvideo-startscreenvideocapture) 接口的中的参数类型

<p style="font-size: 16px;font-weight: bolder;"> type <span id="screencapturesourceinfo-type"></span></p> 

类型: [ScreenCaptureSourceType](#screencapturesourcetype)

共享对象类型，屏幕或应用窗体

<p style="font-size: 16px;font-weight: bolder;"> source_id <span id="screencapturesourceinfo-source_id"></span></p> 

类型: number

共享对象 ID

<p style="font-size: 16px;font-weight: bolder;"> source_name <span id="screencapturesourceinfo-source_name"></span></p> 

类型: string

屏幕共享对象的名称

<p style="font-size: 16px;font-weight: bolder;"> application <span id="screencapturesourceinfo-application"></span></p> 

类型: string

共享的应用窗体所属应用的名称
当共享对象为应用窗体时有效

<p style="font-size: 16px;font-weight: bolder;"> primary_monitor <span id="screencapturesourceinfo-primary_monitor"></span></p> 

类型: boolean

共享的屏幕是否为主屏。
当共享对象为屏幕时有效

<p style="font-size: 16px;font-weight: bolder;"> pid <span id="screencapturesourceinfo-pid"></span></p> 

类型: number

共享的应用窗体所属应用进程的 pid
当共享对象为应用窗体时有效

<p style="font-size: 16px;font-weight: bolder;"> region_rect <span id="screencapturesourceinfo-region_rect"></span></p> 

类型: [Rectangle](#rectangle)

屏幕共享对象的坐标。多显示器的场景下，屏幕坐标系统以主屏左上角为原点 (0, 0)，向右向下扩展。


## ScreenCaptureSourceType <span id="screencapturesourcetype"></span>

类型: `enum`

屏幕采集对象的类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kScreenCaptureSourceTypeUnknown | `0` | 类型未知 |
  | kScreenCaptureSourceTypeWindow | `1` | 应用程序的窗口 |
  | kScreenCaptureSourceTypeScreen | `2` | 桌面 |



## Rectangle <span id="rectangle"></span>

类型: `interface`

矩形区域，用于指定屏幕区域

+ 对于多屏幕的场景，不同平台的坐标系原点不同：
  - 对于 Windows 平台，屏幕坐标以主屏左上角为原点 (0, 0)，向右向下扩展。
  — 对于 Linux 平台，屏幕坐标以 **恰好包住所有显示器的矩形区域的左上角** 为原点 (0, 0)，向右向下扩展。

+ 对于不同平台，窗口区域不同：
  - 对于 Windows 和 macOS 平台，窗口区域包含系统标题栏。
  - 对于 Linux 平台，窗口区域不包含系统标题栏。

<p style="font-size: 16px;font-weight: bolder;"> x <span id="rectangle-x"></span></p> 

类型: number | undefined

矩形区域左上角的 x 坐标

<p style="font-size: 16px;font-weight: bolder;"> y <span id="rectangle-y"></span></p> 

类型: number | undefined

矩形区域左上角的 y 坐标

<p style="font-size: 16px;font-weight: bolder;"> width <span id="rectangle-width"></span></p> 

类型: number | undefined

矩形宽度

<p style="font-size: 16px;font-weight: bolder;"> height <span id="rectangle-height"></span></p> 

类型: number | undefined

矩形高度


## ScreenCaptureParameters <span id="screencaptureparameters"></span>

类型: `interface`

屏幕共享时，内部采集参数配置

<p style="font-size: 16px;font-weight: bolder;"> region_rect <span id="screencaptureparameters-region_rect"></span></p> 

类型: [Rectangle](#rectangle)

采集区域

<p style="font-size: 16px;font-weight: bolder;"> capture_mouse_cursor <span id="screencaptureparameters-capture_mouse_cursor"></span></p> 

类型: [MouseCursorCaptureState](#mousecursorcapturestate) | undefined

是否采集鼠标状态

<p style="font-size: 16px;font-weight: bolder;"> filter_config <span id="screencaptureparameters-filter_config"></span></p> 

类型: number[]

屏幕过滤设置，填写不需要采集的窗口 ID

<p style="font-size: 16px;font-weight: bolder;"> highlight_config <span id="screencaptureparameters-highlight_config"></span></p> 

类型: [HighlightConfig](#highlightconfig)

采集区域的边框高亮设置


## MouseCursorCaptureState <span id="mousecursorcapturestate"></span>

类型: `enum`

内部采集屏幕视频流时，是否采集鼠标信息

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMouseCursorCaptureStateOn | `0` | 采集鼠标信息 |
  | kMouseCursorCaptureStateOff | `1` | 不采集鼠标信息 |



## HighlightConfig <span id="highlightconfig"></span>

类型: `interface`

屏幕共享时的边框高亮设置

<p style="font-size: 16px;font-weight: bolder;"> enable_highlight <span id="highlightconfig-enable_highlight"></span></p> 

类型: boolean | undefined

是否显示高亮边框，默认显示。

<p style="font-size: 16px;font-weight: bolder;"> border_color <span id="highlightconfig-border_color"></span></p> 

类型: number | undefined

边框的颜色, 颜色格式为十六进制 ARGB:  0xAARRGGBB, 默认为 0xFF29CCA3

<p style="font-size: 16px;font-weight: bolder;"> border_width <span id="highlightconfig-border_width"></span></p> 

类型: number | undefined

边框的宽度, 单位：像素，默认为: 4


## ThumbnailInfo <span id="thumbnailinfo"></span>

类型: `interface`

屏幕共享对象缩略图
调用 [getThumbnail](Electron-api.md#rtcvideo-getthumbnail) 后返回本对象

<p style="font-size: 16px;font-weight: bolder;"> width <span id="thumbnailinfo-width"></span></p> 

类型: number

宽度，单位：像素

<p style="font-size: 16px;font-weight: bolder;"> height <span id="thumbnailinfo-height"></span></p> 

类型: number

高度，单位：像素

<p style="font-size: 16px;font-weight: bolder;"> data <span id="thumbnailinfo-data"></span></p> 

类型: string

数据，采用 base64 编码的 png 字符串


## AppIconInfo <span id="appiconinfo"></span>

类型: `interface`

共享窗体的图标信息
调用 [getWindowAppIcon](Electron-api.md#rtcvideo-getwindowappicon) 后返回本对象

<p style="font-size: 16px;font-weight: bolder;"> width <span id="appiconinfo-width"></span></p> 

类型: number

宽度，单位：像素

<p style="font-size: 16px;font-weight: bolder;"> height <span id="appiconinfo-height"></span></p> 

类型: number

高度，单位：像素

<p style="font-size: 16px;font-weight: bolder;"> data <span id="appiconinfo-data"></span></p> 

类型: string

数据，采用 base64 编码的 png 字符串


## ScreenVideoEncoderConfig <span id="screenvideoencoderconfig"></span>

类型: `interface`

屏幕编码配置。参考[屏幕共享](https://www.volcengine.com/docs/6348/129464)。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="screenvideoencoderconfig-width"></span></p> 

类型: number

屏幕流最大宽度，单位：px。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="screenvideoencoderconfig-height"></span></p> 

类型: number

屏幕流最大高度，单位：px。

<p style="font-size: 16px;font-weight: bolder;"> frame_rate <span id="screenvideoencoderconfig-frame_rate"></span></p> 

类型: number

屏幕流编码帧率，单位：fps。建议和采集帧率保持一致。

<p style="font-size: 16px;font-weight: bolder;"> max_bitrate <span id="screenvideoencoderconfig-max_bitrate"></span></p> 

类型: number | undefined

最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。
设为 -1 即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。
设为 0 则不对视频流进行编码发送。
3.44 及以上版本，内部采集时默认值为 -1，3.44 以前版本无默认值，需手动设置。

<p style="font-size: 16px;font-weight: bolder;"> min_bitrate <span id="screenvideoencoderconfig-min_bitrate"></span></p> 

类型: number | undefined

最小编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。
最小编码码率必须小于或等于最大编码，否则不对视频流进行编码发送。

<p style="font-size: 16px;font-weight: bolder;"> encoder_preference <span id="screenvideoencoderconfig-encoder_preference"></span></p> 

类型: [ScreenVideoEncodePreference](#screenvideoencodepreference) | undefined

屏幕流编码模式。


## ScreenVideoEncodePreference <span id="screenvideoencodepreference"></span>

类型: `enum`

屏幕流编码模式。默认采用清晰模式。若在采集时设置 [filter_config](#screencaptureparameters-filter_config) 排除指定窗口，共享视频时帧率无法达到 30fps。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kScreenVideoEncodePreferenceAuto | `0` | 智能模式。根据屏幕内容智能决策选择流畅模式或清晰模式。 |
  | kScreenVideoEncodePreferenceFramerate | `1` | 流畅模式，优先保障帧率。适用于共享游戏、视频等动态画面。 |
  | kScreenVideoEncodePreferenceQuality | `2` | 清晰模式，优先保障分辨率。适用于共享PPT、文档、图片等静态画面。 |



## MessageConfig <span id="messageconfig"></span>

类型: `enum`

发送消息的可靠有序性

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMessageConfigReliableOrdered | `0` | 低延时可靠有序消息 |
  | kMessageConfigUnreliableOrdered | `1` | 超低延时有序消息 |
  | kMessageConfigUnreliableUnordered | `2` | 超低延时无序消息 |



## SEICountPerFrame <span id="seicountperframe"></span>

类型: `enum`

SEI 发送模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kSEICountPerFrameSingle | `0` | 单发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 按队列逐帧发送。 |
  | kSEICountPerFrameMulti | `1` | 多发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 随下个视频帧同时发送。 |



## VideoCaptureConfig <span id="videocaptureconfig"></span>

视频采集配置

- **类型**

  ```ts
  {
    capture_preference: CapturePreference;
    width?: number;
    height?: number;
    frame_rate?: number;
  }
  ```

- **成员**

  | 名称 | 类型 | 描述 |
  | :-- | :-- | :-- |
  | capture_preference | [CapturePreference](#capturepreference) | 视频采集模式 |
  | width | number \| undefined | 视频采集分辨率的宽度，单位：px。 |
  | height | number \| undefined | 视频采集分辨率的高度，单位：px。 |
  | frame_rate | number \| undefined | 视频采集帧率，单位：fps。 |



## CapturePreference <span id="capturepreference"></span>

类型: `enum`

视频采集配置

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAuto | `0` | （默认）自动设置采集参数。<br>SDK在开启采集时根据服务端下发的采集配置结合编码参数设置最佳采集参数。 |
  | kManual | `1` | 手动设置采集参数，包括采集分辨率、帧率。 |
  | kAutoPerformance | `2` | 采集参数与编码参数一致，即在 [setVideoEncoderConfig](Electron-api.md#setvideoencoderconfig) 中设置的参数。 |



## AudioMixingConfig <span id="audiomixingconfig"></span>

类型: `interface`

混音配置

<p style="font-size: 16px;font-weight: bolder;"> type <span id="audiomixingconfig-type"></span></p> 

类型: [AudioMixingType](#audiomixingtype)

混音播放类型

<p style="font-size: 16px;font-weight: bolder;"> play_count <span id="audiomixingconfig-play_count"></span></p> 

类型: number

混音播放次数，

+ play_count <= 0: 无限循环
+ play_count == 1: 播放一次（默认）
+ play_count > 1: 播放 play_count 次

<p style="font-size: 16px;font-weight: bolder;"> position <span id="audiomixingconfig-position"></span></p> 

类型: number

混音时音频文件播放的起始位置。参数为整数，单位为毫秒。

<p style="font-size: 16px;font-weight: bolder;"> callback_on_progress_interval <span id="audiomixingconfig-callback_on_progress_interval"></span></p> 

类型: number | undefined

设置音频文件播放进度回调的时间间隔，单位毫秒，并按照设置的值触发 onAudioMixingPlayingProgress 回调，默认不回调。
该值应为大于 0 的 10 的倍数，当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。
传入的值小于等于 0 时，不会触发进度回调。

<p style="font-size: 16px;font-weight: bolder;"> sync_progress_to_record_frame <span id="audiomixingconfig-sync_progress_to_record_frame"></span></p> 

类型: boolean | undefined

在采集音频数据时，附带本地混音文件播放进度的时间戳。启用此功能会提升远端人声和音频文件混音播放时的同步效果。

- **注意**

  + 仅在单个音频文件混音时使用有效。
  + `true` 时开启此功能，`false` 时关闭此功能，默认为关闭。


## RecordingConfig <span id="recordingconfig"></span>

类型: `interface`

本地录制参数配置

<p style="font-size: 16px;font-weight: bolder;"> dir_path <span id="recordingconfig-dir_path"></span></p> 

类型: string

录制文件保存的绝对路径。你需要指定一个有读写权限的合法路径。

<p style="font-size: 16px;font-weight: bolder;"> file_type <span id="recordingconfig-file_type"></span></p> 

类型: number

录制存储文件格式

+ aac : 0
+ mp4 : 1


## RecordingType <span id="recordingtype"></span>

类型: `enum`

本地录制的媒体类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRecordingTypeAudioOnly | `0` | 只录制音频 |
  | kRecordingTypeVideoOnly | `1` | 只录制视频 |
  | kRecordingTypeVideoAndAudio | `2` | 同时录制音频和视频 |



## RemoteUserPriority <span id="remoteuserpriority"></span>

类型: `enum`

远端用户优先级，在性能不足需要回退时，会优先回退优先级低的用户的音视频流

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRemoteUserPriorityLow | `0` | 用户优先级为低（默认值） |
  | kRemoteUserPriorityMedium | `100` | 用户优先级为正常 |
  | kRemoteUserPriorityHigh | `200` | 用户优先级为高 |



## VirtualBackgroundSource <span id="virtualbackgroundsource"></span>

类型: `interface`

虚拟背景对象。

<p style="font-size: 16px;font-weight: bolder;"> source_type <span id="virtualbackgroundsource-source_type"></span></p> 

类型: [VirtualBackgroundSourceType](#virtualbackgroundsourcetype) | undefined

虚拟背景类型

<p style="font-size: 16px;font-weight: bolder;"> source_path <span id="virtualbackgroundsource-source_path"></span></p> 

类型: string

自定义背景图片的绝对路径。
 支持的格式为 jpg、jpeg、png。
图片分辨率超过 1080P 时，图片会被等比缩放至和视频一致。
图片和视频宽高比一致时，图片会被直接缩放至和视频一致。
图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。
自定义图片带有局部透明效果时，透明部分由黑色代替。

<p style="font-size: 16px;font-weight: bolder;"> source_color <span id="virtualbackgroundsource-source_color"></span></p> 

类型: number | undefined

纯色背景使用的颜色。


## VirtualBackgroundSourceType <span id="virtualbackgroundsourcetype"></span>

类型: `enum`

虚拟背景类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kVirtualBackgroundSourceTypeColor | `0` | 使用纯色背景替换视频原有背景。 |
  | kVirtualBackgroundSourceTypeImage | `1` | 使用自定义图片替换视频原有背景。 |



## RTCWatermarkConfig <span id="rtcwatermarkconfig"></span>

类型: `interface`

水印参数

<p style="font-size: 16px;font-weight: bolder;"> visible_in_preview <span id="rtcwatermarkconfig-visible_in_preview"></span></p> 

类型: boolean | undefined

水印是否在视频预览中可见，默认可见。

<p style="font-size: 16px;font-weight: bolder;"> position_in_landscape_mode <span id="rtcwatermarkconfig-position_in_landscape_mode"></span></p> 

类型: [ByteWatermark](#bytewatermark)

横屏时的水印位置和大小

<p style="font-size: 16px;font-weight: bolder;"> position_in_portrait_mode <span id="rtcwatermarkconfig-position_in_portrait_mode"></span></p> 

类型: [ByteWatermark](#bytewatermark)

视频编码的方向模式为竖屏时的水印位置和大小


## ByteWatermark <span id="bytewatermark"></span>

类型: `interface`

水印图片相对视频流的位置和大小。

<p style="font-size: 16px;font-weight: bolder;"> x <span id="bytewatermark-x"></span></p> 

类型: number

水印图片相对视频流左上角的横向偏移与视频流宽度的比值，取值范围为 [0,1)。

<p style="font-size: 16px;font-weight: bolder;"> y <span id="bytewatermark-y"></span></p> 

类型: number

水印图片相对视频流左上角的纵向偏移与视频流高度的比值，取值范围为 [0,1)。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="bytewatermark-width"></span></p> 

类型: number

水印图片宽度与视频流宽度的比值，取值范围 [0,1)。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="bytewatermark-height"></span></p> 

类型: number

水印图片高度与视频流高度的比值，取值范围为 [0,1)。


## AudioTrackType <span id="audiotracktype"></span>

类型: `enum`

原唱伴唱类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kOriginal | `1` | 播放原唱。 |
  | kAccompy | `2` | 播放伴唱。 |



## AudioPlayType <span id="audioplaytype"></span>

类型: `enum`

音乐播放类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLocal | `0` | 仅本地播放。 |
  | kRemote | `1` | 仅远端播放。 |
  | kLocalAndRemote | `2` | 本地、远端同时播放。 |



## DownloadLyricType <span id="downloadlyrictype"></span>

类型: `enum`

歌词文件类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kKRC | `0` | KRC 歌词文件。 |
  | kLRC | `1` | LRC 歌词文件。 |



## SingScoringConfig <span id="singscoringconfig"></span>

类型: `interface`

K 歌评分配置。

<p style="font-size: 16px;font-weight: bolder;"> sample_rate <span id="singscoringconfig-sample_rate"></span></p> 

类型: [AudioSampleRate](#audiosamplerate)

音频采样率。仅支持 44100 Hz、48000 Hz。

<p style="font-size: 16px;font-weight: bolder;"> mode <span id="singscoringconfig-mode"></span></p> 

类型: MulDimSingScoringMode

值: `0`

打分维度

<p style="font-size: 16px;font-weight: bolder;"> lyrics_filepath <span id="singscoringconfig-lyrics_filepath"></span></p> 

类型: string

歌词文件路径。打分功能仅支持 KRC 歌词文件。

<p style="font-size: 16px;font-weight: bolder;"> midi_filepath <span id="singscoringconfig-midi_filepath"></span></p> 

类型: string

歌曲 midi 文件路径。


## StandardPitchInfo <span id="standardpitchinfo"></span>

类型: `interface`

标准音高数据

<p style="font-size: 16px;font-weight: bolder;"> start_time <span id="standardpitchinfo-start_time"></span></p> 

类型: number

开始时间，单位 ms。

<p style="font-size: 16px;font-weight: bolder;"> duration <span id="standardpitchinfo-duration"></span></p> 

类型: number

持续时间，单位 ms。

<p style="font-size: 16px;font-weight: bolder;"> pitch <span id="standardpitchinfo-pitch"></span></p> 

类型: number

音高。


## VoiceEqualizationConfig <span id="voiceequalizationconfig"></span>

类型: `interface`

语音均衡效果。

<p style="font-size: 16px;font-weight: bolder;"> frequency <span id="voiceequalizationconfig-frequency"></span></p> 

类型: [VoiceEqualizationBandFrequency](#voiceequalizationbandfrequency)

频带。

<p style="font-size: 16px;font-weight: bolder;"> gain <span id="voiceequalizationconfig-gain"></span></p> 

类型: number

频带增益（dB）。取值范围是 `[-15, 15]`。


## VoiceEqualizationBandFrequency <span id="voiceequalizationbandfrequency"></span>

类型: `enum`

音频均衡效果。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kVoiceEqualizationBandFrequency31 | `0` | 中心频率为 31Hz 的频带。 |
  | kVoiceEqualizationBandFrequency62 | `1` | 中心频率为 62Hz 的频带。 |
  | kVoiceEqualizationBandFrequency125 | `2` | 中心频率为 125Hz 的频带。 |
  | kVoiceEqualizationBandFrequency250 | `3` | 中心频率为 250Hz 的频带。 |
  | kVoiceEqualizationBandFrequency500 | `4` | 中心频率为 500Hz 的频带。 |
  | kVoiceEqualizationBandFrequency1k | `5` | 中心频率为 1kHz 的频带。 |
  | kVoiceEqualizationBandFrequency2k | `6` | 中心频率为 2kHz 的频带。 |
  | kVoiceEqualizationBandFrequency4k | `7` | 中心频率为 4kHz 的频带。 |
  | kVoiceEqualizationBandFrequency8k | `8` | 中心频率为 8kHz 的频带。 |
  | kVoiceEqualizationBandFrequency16k | `9` | 中心频率为 16kHz 的频带。 |



## VoiceReverbConfig <span id="voicereverbconfig"></span>

类型: `interface`

音频混响效果。

<p style="font-size: 16px;font-weight: bolder;"> room_size <span id="voicereverbconfig-room_size"></span></p> 

类型: number

混响模拟的房间大小，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。房间越大，混响越强。

<p style="font-size: 16px;font-weight: bolder;"> decay_time <span id="voicereverbconfig-decay_time"></span></p> 

类型: number

混响的拖尾长度，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。

<p style="font-size: 16px;font-weight: bolder;"> damping <span id="voicereverbconfig-damping"></span></p> 

类型: number

混响的衰减阻尼大小，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。

<p style="font-size: 16px;font-weight: bolder;"> wet_gain <span id="voicereverbconfig-wet_gain"></span></p> 

类型: number

早期反射信号强度。取值范围 `[-20.0, 10.0]`，单位为 dB。默认值为 `0.0f`。

<p style="font-size: 16px;font-weight: bolder;"> dry_gain <span id="voicereverbconfig-dry_gain"></span></p> 

类型: number

原始信号强度。取值范围 `[-20.0, 10.0]`，单位为 dB。默认值为 `0.0f`。

<p style="font-size: 16px;font-weight: bolder;"> pre_delay <span id="voicereverbconfig-pre_delay"></span></p> 

类型: number

早期反射信号的延迟。取值范围 `[0.0, 200.0]`，单位为 ms。默认值为 `0.0f`。


## AudioRecordingConfig <span id="audiorecordingconfig"></span>

类型: `interface`

录音配置

<p style="font-size: 16px;font-weight: bolder;"> absolute_file_name <span id="audiorecordingconfig-absolute_file_name"></span></p> 

类型: string

录制文件路径。一个有读写权限的绝对路径，包含文件名和文件后缀。

- **注意**

  录制文件的格式仅支持 .aac 和 .wav。

<p style="font-size: 16px;font-weight: bolder;"> frame_source <span id="audiorecordingconfig-frame_source"></span></p> 

类型: [AudioFrameSource](#audioframesource)

录音内容来源
默认为 kAudioFrameSourceMixed = 2。

<p style="font-size: 16px;font-weight: bolder;"> sample_rate <span id="audiorecordingconfig-sample_rate"></span></p> 

类型: [AudioSampleRate](#audiosamplerate)

录音采样率

<p style="font-size: 16px;font-weight: bolder;"> channel <span id="audiorecordingconfig-channel"></span></p> 

类型: [AudioChannel](#audiochannel)

录音音频声道。

- **注意**

  如果录制时设置的的音频声道数与采集时的音频声道数不同：

  + 如果采集的声道数为 1，录制的声道数为 2，那么，录制的音频为经过单声道数据拷贝后的双声道数据，而不是立体声。
  + 如果采集的声道数为 2，录制的声道数为 1，那么，录制的音频为经过双声道数据混合后的单声道数据。

<p style="font-size: 16px;font-weight: bolder;"> quality <span id="audiorecordingconfig-quality"></span></p> 

类型: [AudioQuality](#audioquality)

录音音质。仅在录制文件格式为 .aac 时可以设置。

- **注意**

  采样率为 32kHz 时，不同音质录制文件（时长为 10min）的大小分别是：

  + 低音质：1.2MB；
  + 【默认】中音质：2MB；
  + 高音质：3.75MB；
  + 超高音质：7.5MB。


## AudioFrameSource <span id="audioframesource"></span>

类型: `enum`

音频文件录制内容来源。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioFrameSourceMic | `0` | 本地麦克风采集的音频数据。 |
  | kAudioFrameSourcePlayback | `1` | 远端所有用户混音后的数据 |
  | kAudioFrameSourceMixed | `2` | 本地麦克风和所有远端用户音频流的混音后的数据 |



## AudioQuality <span id="audioquality"></span>

类型: `enum`

音频质量。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioQualityLow | `0` | 低音质 |
  | kAudioQualityMedium | `1` | 中音质 |
  | kAudioQualityHigh | `2` | 高音质 |
  | kAudioQualityUltraHigh | `3` | 超高音质 |



## ZoomConfigType <span id="zoomconfigtype"></span>

类型: `enum`

数码变焦参数类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kZoomConfigTypeFocusOffset | `0` | 设置缩放系数 |
  | kZoomConfigTypeMoveOffset | `1` | 设置移动步长 |



## ZoomDirectionType <span id="zoomdirectiontype"></span>

类型: `enum`

数码变焦操作类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kZoomDirectionTypeMoveLeft | `0` | 相机向左移动 |
  | kZoomDirectionTypeMoveRight | `1` | 相机向右移动 |
  | kZoomDirectionTypeMoveUp | `2` | 相机向上移动 |
  | kZoomDirectionTypeMoveDown | `3` | 相机向下移动 |
  | kZoomDirectionTypeZoomOut | `4` | 相机缩小焦距 |
  | kZoomDirectionTypeZoomIn | `5` | 相机放大焦距 |
  | kZoomDirectionTypeReset | `6` | 恢复到原始画面 |



## IMixedStreamConfig <span id="imixedstreamconfig"></span>

类型: `interface`

转推直播配置参数(新)

<p style="font-size: 16px;font-weight: bolder;"> is_support_client_push_stream <span id="imixedstreamconfig-is_support_client_push_stream"></span></p> 

类型: boolean

本端是否具有推流能力。如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true
默认为 false。

<p style="font-size: 16px;font-weight: bolder;"> expected_mix_type <span id="imixedstreamconfig-expected_mix_type"></span></p> 

类型: [MixedStreamType](#mixedstreamtype)

设置合流类型。本参数不支持过程中更新。

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="imixedstreamconfig-room_id"></span></p> 

类型: string

媒体流所在的房间 ID。必填。

<p style="font-size: 16px;font-weight: bolder;"> user_id <span id="imixedstreamconfig-user_id"></span></p> 

类型: string

媒体流所属的用户 ID

<p style="font-size: 16px;font-weight: bolder;"> push_url <span id="imixedstreamconfig-push_url"></span></p> 

类型: string

设置推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`

<p style="font-size: 16px;font-weight: bolder;"> audio_config <span id="imixedstreamconfig-audio_config"></span></p> 

类型: [MixedStreamAudioConfig](#mixedstreamaudioconfig)

音频参数

<p style="font-size: 16px;font-weight: bolder;"> video_config <span id="imixedstreamconfig-video_config"></span></p> 

类型: [MixedStreamVideoConfig](#mixedstreamvideoconfig)

视频参数

<p style="font-size: 16px;font-weight: bolder;"> client_mix_config <span id="imixedstreamconfig-client_mix_config"></span></p> 

类型: [MixedStreamClientMixConfig](#mixedstreamclientmixconfig)

设置客户端合流信息

<p style="font-size: 16px;font-weight: bolder;"> layout_regions <span id="imixedstreamconfig-layout_regions"></span></p> 

类型: [MixedStreamLayoutRegionConfig](#mixedstreamlayoutregionconfig)[]

设置视频流合流整体布局信息。必填。

<p style="font-size: 16px;font-weight: bolder;"> background_color <span id="imixedstreamconfig-background_color"></span></p> 

类型: string

背景颜色

<p style="font-size: 16px;font-weight: bolder;"> user_config_extra_info <span id="imixedstreamconfig-user_config_extra_info"></span></p> 

类型: string

设置透传的 App 数据

<p style="font-size: 16px;font-weight: bolder;"> server_control_config <span id="imixedstreamconfig-server_control_config"></span></p> 

类型: [MixedStreamServerControlConfig](#mixedstreamservercontrolconfig) | undefined

服务端合流控制参数

<p style="font-size: 16px;font-weight: bolder;"> background_image_url <span id="imixedstreamconfig-background_image_url"></span></p> 

类型: string | undefined

设置合流后整体画布的背景图片 URL，长度最大为 1024 bytes。
支持的图片格式包括：JPG, JPEG, PNG。如果背景图片的宽高和整体屏幕的宽高不一致，背景图片会缩放到铺满屏幕。


## MixedStreamType <span id="mixedstreamtype"></span>

类型: `enum`

合流类型(新)

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamTypeByServer | `0` | 服务端合流 |
  | kMixedStreamTypeByClient | `1` | 端云一体合流。SDK 智能决策在客户端或服务端完成合流。<br>使用前，请联系技术支持同学开通，否则不生效。 |



## MixedStreamAudioConfig <span id="mixedstreamaudioconfig"></span>

类型: `interface`

音频合流配置参数(新)。值不合法或未设置时，自动使用默认值。

<p style="font-size: 16px;font-weight: bolder;"> sample_rate <span id="mixedstreamaudioconfig-sample_rate"></span></p> 

类型: 32000 | 44100 | 48000

音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。

<p style="font-size: 16px;font-weight: bolder;"> channels <span id="mixedstreamaudioconfig-channels"></span></p> 

类型: 1 | 2

音频声道数。可取 1（单声道）、2（双声道），默认值为 2。

<p style="font-size: 16px;font-weight: bolder;"> bitrate <span id="mixedstreamaudioconfig-bitrate"></span></p> 

类型: number

音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。

<p style="font-size: 16px;font-weight: bolder;"> audio_profile <span id="mixedstreamaudioconfig-audio_profile"></span></p> 

类型: [MixedStreamAudioProfile](#mixedstreamaudioprofile)

AAC 编码规格。默认值为 `0`。

<p style="font-size: 16px;font-weight: bolder;"> audio_codec <span id="mixedstreamaudioconfig-audio_codec"></span></p> 

类型: MixedStreamAudioCodecType

值: `0`

音频编码格式。默认值为 `0`。


## MixedStreamAudioProfile <span id="mixedstreamaudioprofile"></span>

类型: `enum`

AAC 编码规格(新)。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamAudioProfileLC | `0` | AAC-LC 规格，默认值。 |
  | kMixedStreamAudioProfileHEv1 | `1` | HE-AAC v1 规格。 |
  | kMixedStreamAudioProfileHEv2 | `2` | HE-AAC v2 规格。 |



## MixedStreamVideoConfig <span id="mixedstreamvideoconfig"></span>

类型: `interface`

视频合流配置参数(新)。值不合法或未设置时，自动使用默认值。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="mixedstreamvideoconfig-width"></span></p> 

类型: number

合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。
设置值为非偶数时，自动向上取偶数。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="mixedstreamvideoconfig-height"></span></p> 

类型: number

合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。
设置值为非偶数时，自动向上取偶数。

<p style="font-size: 16px;font-weight: bolder;"> fps <span id="mixedstreamvideoconfig-fps"></span></p> 

类型: number

合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。

<p style="font-size: 16px;font-weight: bolder;"> gop <span id="mixedstreamvideoconfig-gop"></span></p> 

类型: number

视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。
本参数不支持过程中更新。

<p style="font-size: 16px;font-weight: bolder;"> bitrate <span id="mixedstreamvideoconfig-bitrate"></span></p> 

类型: number

合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。

<p style="font-size: 16px;font-weight: bolder;"> video_codec <span id="mixedstreamvideoconfig-video_codec"></span></p> 

类型: [MixedStreamVideoCodecType](#mixedstreamvideocodectype)

视频编码格式。默认值为 `0`。
本参数不支持过程中更新。

<p style="font-size: 16px;font-weight: bolder;"> enable_bframe <span id="mixedstreamvideoconfig-enable_bframe"></span></p> 

类型: boolean

是否在合流中开启 B 帧，仅服务端合流支持：

+ true: 是
+ false: 否


## MixedStreamVideoCodecType <span id="mixedstreamvideocodectype"></span>

类型: `enum`

视频编码格式(新)。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamVideoCodecTypeH264 | `0` | H.264 格式，默认值。 |
  | kMixedStreamVideoCodecTypeByteVC1 | `1` | ByteVC1 格式。 |



## MixedStreamClientMixConfig <span id="mixedstreamclientmixconfig"></span>

类型: `interface`

客户端合流参数(新)。

<p style="font-size: 16px;font-weight: bolder;"> use_audio_mixer <span id="mixedstreamclientmixconfig-use_audio_mixer"></span></p> 

类型: boolean

客户端合流是否使用混音，默认为 true。

<p style="font-size: 16px;font-weight: bolder;"> video_format <span id="mixedstreamclientmixconfig-video_format"></span></p> 

类型: [MixedStreamClientMixVideoFormat](#mixedstreamclientmixvideoformat)

客户端合流回调视频格式。


## MixedStreamClientMixVideoFormat <span id="mixedstreamclientmixvideoformat"></span>

类型: `enum`

客户端合流回调视频格式(新)。设置为系统不支持的格式时，自动回调系统默认格式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamClientMixVideoFormatI420 | `0` | YUV I420。Android、Windows 默认回调格式。支持系统：Android、Windows。 |
  | kMixedStreamClientMixVideoFormatTexture2D | `1` | OpenGL GL_TEXTURE_2D 格式纹理。支持系统：安卓。 |
  | kMixedStreamClientMixVideoFormatCVPixelBufferBGRA | `2` | CVPixelBuffer BGRA。iOS 默认回调格式。支持系统: iOS。 |
  | kMixedStreamClientMixVideoFormatNV12 | `3` | YUV NV12。macOS 默认回调格式。支持系统: macOS。 |



## MixedStreamLayoutRegionConfig <span id="mixedstreamlayoutregionconfig"></span>

类型: `interface`

单个图片或视频流在合流中的布局信息(新)。
开启合流功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。

<p style="font-size: 16px;font-weight: bolder;"> region_id <span id="mixedstreamlayoutregionconfig-region_id"></span></p> 

类型: string

合流用户的 ID。必填。

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="mixedstreamlayoutregionconfig-room_id"></span></p> 

类型: string

图片或视频流所在房间的房间 ID。必填。
如果此图片或视频流是通过 [startForwardStreamToRooms](Electron-api.md#rtcroom-startforwardstreamtorooms) 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。

<p style="font-size: 16px;font-weight: bolder;"> location_x <span id="mixedstreamlayoutregionconfig-location_x"></span></p> 

类型: number

视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。

<p style="font-size: 16px;font-weight: bolder;"> location_y <span id="mixedstreamlayoutregionconfig-location_y"></span></p> 

类型: number

视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="mixedstreamlayoutregionconfig-width"></span></p> 

类型: number

视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。

<p style="font-size: 16px;font-weight: bolder;"> height <span id="mixedstreamlayoutregionconfig-height"></span></p> 

类型: number

视频流对应区域高度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。

<p style="font-size: 16px;font-weight: bolder;"> alpha <span id="mixedstreamlayoutregionconfig-alpha"></span></p> 

类型: number

透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。

<p style="font-size: 16px;font-weight: bolder;"> corner_radius <span id="mixedstreamlayoutregionconfig-corner_radius"></span></p> 

类型: number

圆角半径相对画布宽度的比例。默认值为 `0.0`。

- **注意**

  做范围判定时，首先根据画布的宽高，将 `width`，`height`，和 `corner_radius` 分别转换为像素值：`width_px`，`height_px`，和 `corner_radius_px`。然后判定是否满足 `corner_radius_px < min(width_px/2, height_px/2)`：若满足，则设置成功；若不满足，则将 `corner_radius_px` 设定为 `min(width_px/2, height_px/2)`，然后将 `corner_radius` 设定为 `corner_radius_px` 相对画布宽度的比例值。

<p style="font-size: 16px;font-weight: bolder;"> z_order <span id="mixedstreamlayoutregionconfig-z_order"></span></p> 

类型: number

用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。

<p style="font-size: 16px;font-weight: bolder;"> is_local_user <span id="mixedstreamlayoutregionconfig-is_local_user"></span></p> 

类型: boolean

是否为本地用户：

+ true: 是
+ false: 否

<p style="font-size: 16px;font-weight: bolder;"> stream_type <span id="mixedstreamlayoutregionconfig-stream_type"></span></p> 

类型: [MixedStreamVideoType](#mixedstreamvideotype)

是否为屏幕流：

<p style="font-size: 16px;font-weight: bolder;"> media_type <span id="mixedstreamlayoutregionconfig-media_type"></span></p> 

类型: [MixedStreamMediaType](#mixedstreammediatype)

合流内容控制。默认值为 `kMediaTypeAudioAndVideo`。

<p style="font-size: 16px;font-weight: bolder;"> render_mode <span id="mixedstreamlayoutregionconfig-render_mode"></span></p> 

类型: [MixedStreamRenderMode](#mixedstreamrendermode)

图片或视频流的缩放模式。默认值为 1。

<p style="font-size: 16px;font-weight: bolder;"> region_content_type <span id="mixedstreamlayoutregionconfig-region_content_type"></span></p> 

类型: [MixedStreamLayoutRegionType](#mixedstreamlayoutregiontype)

合流布局区域类型。

<p style="font-size: 16px;font-weight: bolder;"> image_water_mark <span id="mixedstreamlayoutregionconfig-image_water_mark"></span></p> 

类型: Uint8Array

图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。

<p style="font-size: 16px;font-weight: bolder;"> image_water_mark_param <span id="mixedstreamlayoutregionconfig-image_water_mark_param"></span></p> 

类型: [MixedStreamLayoutRegionImageWaterMarkConfig](#mixedstreamlayoutregionimagewatermarkconfig)

合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数。

<p style="font-size: 16px;font-weight: bolder;"> spatial_position <span id="mixedstreamlayoutregionconfig-spatial_position"></span></p> 

类型: [Position](#position)

空间位置。

<p style="font-size: 16px;font-weight: bolder;"> apply_spatial_audio <span id="mixedstreamlayoutregionconfig-apply_spatial_audio"></span></p> 

类型: boolean

是否开启空间音频

<p style="font-size: 16px;font-weight: bolder;"> alternate_image_fill_mode <span id="mixedstreamlayoutregionconfig-alternate_image_fill_mode"></span></p> 

类型: [MixedStreamAlternateImageFillMode](#mixedstreamalternateimagefillmode)

占位图的填充模式。
该参数用来控制当用户停止发布视频流，画面恢复为占位图后，此时占位图的填充模式。

<p style="font-size: 16px;font-weight: bolder;"> alternate_image_url <span id="mixedstreamlayoutregionconfig-alternate_image_url"></span></p> 

类型: string

设置占位图的 URL，长度小于 1024 字符。


## MixedStreamVideoType <span id="mixedstreamvideotype"></span>

类型: `enum`

region中流的类型属性

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamVideoTypeMain | `0` | 主流。包括：<br>+ 由摄像头/麦克风通过内部采集机制，采集到的流<br>+ 通过自定义采集，采集到的流。 |
  | kMixedStreamVideoTypeScreen | `1` | 屏幕流。 |



## MixedStreamMediaType <span id="mixedstreammediatype"></span>

类型: `enum`

合流输出内容类型(新)。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamMediaTypeAudioAndVideo | `0` | 输出的混流包含音频和视频 |
  | kMixedStreamMediaTypeAudioOnly | `1` | 输出的混流只包含音频 |
  | kMixedStreamMediaTypeVideoOnly | `2` | 输出的混流只包含视频 |



## MixedStreamRenderMode <span id="mixedstreamrendermode"></span>

类型: `enum`

图片或视频流的缩放模式(新)。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamRenderModeHidden | `1` | 视窗填满优先，默认值。<br>视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。 |
  | kMixedStreamRenderModeFit | `2` | 视频帧内容全部显示优先。<br>视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。 |
  | kMixedStreamRenderModeAdaptive | `3` | 视频帧自适应画布。<br>视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。 |



## MixedStreamLayoutRegionType <span id="mixedstreamlayoutregiontype"></span>

类型: `enum`

合流布局区域类型(新)。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamLayoutRegionTypeVideoStream | `0` | 合流布局区域类型为视频。 |
  | kMixedStreamLayoutRegionTypeImage | `1` | 合流布局区域类型为图片。 |



## MixedStreamLayoutRegionImageWaterMarkConfig <span id="mixedstreamlayoutregionimagewatermarkconfig"></span>

类型: `interface`

图片合流相关参数(新)。

<p style="font-size: 16px;font-weight: bolder;"> image_width <span id="mixedstreamlayoutregionimagewatermarkconfig-image_width"></span></p> 

类型: number

原始图片的宽度，单位为 px。

<p style="font-size: 16px;font-weight: bolder;"> image_height <span id="mixedstreamlayoutregionimagewatermarkconfig-image_height"></span></p> 

类型: number

原始图片的高度，单位为 px。


## Position <span id="position"></span>

本地用户在房间内的位置坐标，需自行建立空间直角坐标系

- **类型**

  ```ts
  {
    x: number;
    y: number;
    z: number;
  }
  ```

- **成员**

  | 名称 | 类型 | 描述 |
  | :-- | :-- | :-- |
  | x | number | x 坐标 |
  | y | number | y 坐标 |
  | z | number | z 坐标 |



## MixedStreamAlternateImageFillMode <span id="mixedstreamalternateimagefillmode"></span>

类型: `enum`

服务端合流占位图渲染模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamAlternateImageFillModeFit | `0` | 占位图跟随用户原始视频帧相同的比例缩放，默认。 |
  | kMixedStreamAlternateImageFillModeFill | `1` | 占位图不跟随用户原始视频帧相同的比例缩放，保持图片原有比例。 |



## MixedStreamServerControlConfig <span id="mixedstreamservercontrolconfig"></span>

类型: `interface`

服务端合流控制参数

<p style="font-size: 16px;font-weight: bolder;"> enable_volume_indication <span id="mixedstreamservercontrolconfig-enable_volume_indication"></span></p> 

类型: boolean

是否开启单独发送声音提示 SEI 的功能：

+ True：开启；
+ False：关闭。（默认值）
开启后，你可以通过 MixedStreamServerControlConfig.sei_content_mode 控制 SEI 的内容是否只携带声音信息。

<p style="font-size: 16px;font-weight: bolder;"> volume_indication_interval <span id="mixedstreamservercontrolconfig-volume_indication_interval"></span></p> 

类型: number

声音提示间隔，单位为秒，取值范围为 [0.3,+∞)，默认值为 2。
此值仅取整百毫秒。若传入两位及以上小数，则四舍五入取第一位小数的值。例如，若传入 0.36，则取 0.4。

<p style="font-size: 16px;font-weight: bolder;"> talk_volume <span id="mixedstreamservercontrolconfig-talk_volume"></span></p> 

类型: number

有效音量大小，取值范围为 [0, 255]，默认值为 0。
超出取值范围则自动调整为默认值，即 0。

<p style="font-size: 16px;font-weight: bolder;"> is_add_volume_value <span id="mixedstreamservercontrolconfig-is_add_volume_value"></span></p> 

类型: boolean

声音信息 SEI 是否包含音量值：

+ True：是；
+ False：否，默认值。

<p style="font-size: 16px;font-weight: bolder;"> sei_content_mode <span id="mixedstreamservercontrolconfig-sei_content_mode"></span></p> 

类型: [MixedStreamSEIContentMode](#mixedstreamseicontentmode)

设置 SEI 内容。

<p style="font-size: 16px;font-weight: bolder;"> sei_payload_type <span id="mixedstreamservercontrolconfig-sei_payload_type"></span></p> 

类型: number

SEI 信息的 payload type。

- **注意**

  默认值为 100，只支持设置 5 和 100。
  在转推直播的过程中，该参数不支持变更。

<p style="font-size: 16px;font-weight: bolder;"> sei_payload_uuid <span id="mixedstreamservercontrolconfig-sei_payload_uuid"></span></p> 

类型: string | undefined

SEI 信息的 payload UUID。

- **注意**

  PayloadType 为 5 时，必须填写 PayloadUUID，否则会收到错误回调。  
   PayloadType 不是 5 时，不需要填写 PayloadUUID，如果填写会被后端忽略。
   该参数长度需为32位，否则会收到错误回调。  
   该参数每个字符的范围需为 [0, 9] [a, f] [A, F] 
   该参数不应带有-字符，如系统自动生成的 UUID 中带有-，则应删去。
   在转推直播的过程中，该参数不支持变更。

<p style="font-size: 16px;font-weight: bolder;"> media_type <span id="mixedstreamservercontrolconfig-media_type"></span></p> 

类型: [MixedStreamMediaType](#mixedstreammediatype)

控制合流后推到CDN的输出内容。

- **注意**

  默认值为音视频，可以支持纯音频，暂不支持纯视频，MixedStreamMediaType枚举中有纯视频的定义，但是不会对该字段生效。

<p style="font-size: 16px;font-weight: bolder;"> push_stream_mode <span id="mixedstreamservercontrolconfig-push_stream_mode"></span></p> 

类型: [MixedStreamPushMode](#mixedstreampushmode)

控制合流的推流模式。

- **注意**

  默认值为有音频/视频发布的时候，可以发起合流任务；在没有用户推流的情况下，支持用占位图发起合流任务。


## MixedStreamSEIContentMode <span id="mixedstreamseicontentmode"></span>

类型: `enum`

服务端合流转推 SEI 内容。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamSEIContentModeDefault | `0` | 视频流中包含全部的 SEI 信息。默认设置。 |
  | kMixedStreamSEIContentModeEnableVolumeIndication | `1` | 随非关键帧传输的 SEI 数据中仅包含音量信息。<br>当设置 MixedStreamServerControlConfig.enable_volume_indication 为 True 时，此参数设置生效。 |



## MixedStreamPushMode <span id="mixedstreampushmode"></span>

类型: `enum`

服务端合流推流模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMixedStreamPushModeOnStream | `0` | 有用户推流的情况下，才能发起合流任务 |
  | kMixedStreamPushModeOnStartRequest | `1` | 无用户推流的情况下，调用合流开启可以用占位图发起合流任务 |



## LocalProxyConfiguration <span id="localproxyconfiguration"></span>

类型: `interface`

本地代理配置详细信息。

<p style="font-size: 16px;font-weight: bolder;"> local_proxy_type <span id="localproxyconfiguration-local_proxy_type"></span></p> 

类型: [LocalProxyType](#localproxytype)

本地代理类型

<p style="font-size: 16px;font-weight: bolder;"> local_proxy_ip <span id="localproxyconfiguration-local_proxy_ip"></span></p> 

类型: string

本地代理服务器 IP。

<p style="font-size: 16px;font-weight: bolder;"> local_proxy_port <span id="localproxyconfiguration-local_proxy_port"></span></p> 

类型: number

本地代理服务器端口。

<p style="font-size: 16px;font-weight: bolder;"> local_proxy_username <span id="localproxyconfiguration-local_proxy_username"></span></p> 

类型: string

本地代理用户名。

<p style="font-size: 16px;font-weight: bolder;"> local_proxy_password <span id="localproxyconfiguration-local_proxy_password"></span></p> 

类型: string

本地代理密码。


## LocalProxyType <span id="localproxytype"></span>

类型: `enum`

本地代理的类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLocalProxyTypeSocks5 | `1` | Socks5 代理。选用此代理服务器，需满足 Socks5 协议标准文档的要求。 |
  | kLocalProxyTypeHttpTunnel | `2` | Http 隧道代理。 |



## EarMonitorMode <span id="earmonitormode"></span>

类型: `enum`

是否开启耳返功能

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kEarMonitorModeOff | `0` | 不开启 |
  | kEarMonitorModeOn | `1` | 开启 |



## AudioFrameCallbackMethod <span id="audioframecallbackmethod"></span>

类型: `enum`

音频回调方法

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRecord | `0` | 本地麦克风录制的音频数据回调 [`onRecordAudioFrame`](Electron-event.md#rtcvideocallback-onrecordaudioframe) |
  | kPlayback | `1` | 订阅的远端所有用户混音后的音频数据回调  [`onPlaybackAudioFrame`](Electron-event.md#rtcvideocallback-onplaybackaudioframe) |
  | kMixed | `2` | 本地麦克风录制和订阅的远端所有用户混音后的音频数据回调 [`onMixedAudioFrame`](Electron-event.md#rtcvideocallback-onmixedaudioframe) |
  | kRemoteUser | `3` | 订阅的远端每个用户混音前的音频数据回调 [`onRemoteUserAudioFrame`](Electron-event.md#rtcvideocallback-onremoteuseraudioframe) |
  | kRecordScreen | `4` | 本地屏幕录制的音频数据回调 [`onRecordScreenAudioFrame`](Electron-event.md#rtcvideocallback-onrecordscreenaudioframe) |



## AudioFormat <span id="audioformat"></span>

类型: `interface`

音频格式

<p style="font-size: 16px;font-weight: bolder;"> sample_rate <span id="audioformat-sample_rate"></span></p> 

类型: [AudioSampleRate](#audiosamplerate)

音频采样率

<p style="font-size: 16px;font-weight: bolder;"> channel <span id="audioformat-channel"></span></p> 

类型: [AudioChannel](#audiochannel)

音频声道

<p style="font-size: 16px;font-weight: bolder;"> samples_per_call <span id="audioformat-samples_per_call"></span></p> 

类型: number

单次回调的音频帧中包含的采样点数。你可以通过设置 `samples_per_call`，`sample_rate` 和 `channel`，设置音频帧长。
默认值为 `0`，此时，采样点数取最小值。最小值为帧长间隔是 0.01s 时的值，即 `sample_rate * channel * 0.01s`。
最大值是 `2048`。超出取值范围时，采样点数取默认值。


## AudioAlignmentMode <span id="audioalignmentmode"></span>

类型: `enum`

远端音频流精准对齐模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioAlignmentModeOff | `0` | 不对齐 |
  | kAudioAlignmentModeAudioMixing | `1` | 远端音频流都对齐伴奏进度同步播放 |



## VideoEnhancementMode <span id="videoenhancementmode"></span>

类型: `enum`

弱光适应类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kVideoEnhancementModeDisabled | `0` | 关闭弱光适应 |
  | kVideoEnhancementModeAuto | `1` | - @brief 开启弱光适应 |



## LogConfig <span id="logconfig"></span>

类型: `interface`

本地日志参数。

<p style="font-size: 16px;font-weight: bolder;"> log_path <span id="logconfig-log_path"></span></p> 

类型: string

日志存储路径。

<p style="font-size: 16px;font-weight: bolder;"> log_level <span id="logconfig-log_level"></span></p> 

类型: [LocalLogLevel](#localloglevel)

日志等级，默认为警告级别。

<p style="font-size: 16px;font-weight: bolder;"> log_filename_prefix <span id="logconfig-log_filename_prefix"></span></p> 

类型: string | undefined

日志文件名前缀，选填。该字符串必须符合正则表达式：[a-zA-Z0-9_@\-\.]{1,128}。
最终的日志文件名为前缀 + "_" + 文件创建时间 + "_rtclog".log，如 logPrefix_2023-05-25_172324_rtclog.log。


## LocalLogLevel <span id="localloglevel"></span>

类型: `enum`

本地日志输出等级。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kInfo | `0` | 信息级别。 |
  | kWarning | `1` | （默认值）警告级别。 |
  | kError | `2` | 错误级别。 |
  | kNone | `3` | 关闭日志。 |



## RenderType <span id="rendertype"></span>

类型: `enum`

渲染类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRenderTypeWebGL | `1` | WebGL渲染。 |
  | kRenderTypeSoftware | `2` | Software渲染。 |



## UserInfo <span id="userinfo"></span>

用户信息

- **类型**

  ```ts
  {
    uid: string;
    extra_info?: string;
  }
  ```

- **成员**

  | 名称 | 类型 | 描述 |
  | :-- | :-- | :-- |
  | uid | string | 用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。  你需要自行设置或管理 uid，并保证同一房间内每个 uid 的唯一性。 |
  | extra_info | string \| undefined | 用户的额外信息，最大长度为 200 字节。会在 [`onUserJoined`](Electron-event.md#rtcroomcallback-onuserjoined) 中回调给远端用户。 |



## RTCRoomConfig <span id="rtcroomconfig"></span>

类型: `interface`

房间参数配置。房间是 RTC 通话的抽象概念。在同一个房间中的用户可以进行音视频通话。

<p style="font-size: 16px;font-weight: bolder;"> room_profile_type <span id="rtcroomconfig-room_profile_type"></span></p> 

类型: [RoomProfileType](#roomprofiletype) | undefined

房间模式，默认为普通音视频通话模式，进房后不可更改。

<p style="font-size: 16px;font-weight: bolder;"> is_auto_publish <span id="rtcroomconfig-is_auto_publish"></span></p> 

类型: boolean | undefined

是否自动发布音视频流，默认为自动发布。
创建和加入多房间时，只能将其中一个房间设置为自动发布。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。
若调用 [`setUserVisibility`](Electron-api.md#rtcroom-setuservisibility) 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。

<p style="font-size: 16px;font-weight: bolder;"> is_auto_subscribe_audio <span id="rtcroomconfig-is_auto_subscribe_audio"></span></p> 

类型: boolean | undefined

是否自动订阅音频流，默认为自动订阅。包含主流和屏幕流。
进房后，你可以调用 [`subscribeStream`](Electron-api.md#rtcroom-subscribestream) 修改订阅设置。

<p style="font-size: 16px;font-weight: bolder;"> is_auto_subscribe_video <span id="rtcroomconfig-is_auto_subscribe_video"></span></p> 

类型: boolean | undefined

是否自动订阅主视频流，默认为自动订阅。包含主流和屏幕流。
进房后，你可以调用 [`subscribeStream`](Electron-api.md#rtcroom-subscribestream) 修改订阅设置。

<p style="font-size: 16px;font-weight: bolder;"> remote_video_config <span id="rtcroomconfig-remote_video_config"></span></p> 

类型: [RemoteVideoConfig](#remotevideoconfig) | undefined

远端视频流参数


## RoomProfileType <span id="roomprofiletype"></span>

类型: `enum`

房间模式
根据所需场景，选择合适的房间模式，应用不同的音视频算法、视频参数和网络配置
调用 `setAudioProfile` 改变音频参数配置

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRoomProfileTypeCommunication | `0` | 默认场景，通用模式<br>与 `kRoomProfileTypeMeeting = 16` 配置相同。<br>你可以联系技术支持更换默认配置参数。 |
  | kRoomProfileTypeGame | `2` | 游戏语音模式，低功耗、低流量消耗。<br>低端机在此模式下运行时，进行了额外的性能优化：<br>+ 部分低端机型配置编码帧长 40/60<br>+ 部分低端机型关闭软件 3A 音频处理<br>增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。 |
  | kRoomProfileTypeCloudGame | `3` | 云游戏模式。<br>如果你的游戏场景需要低延迟的配置，使用此设置。<br>此设置下，弱网抗性较差。 |
  | kRoomProfileTypeLowLatency | `4` | 低时延模式。SDK 会使用低延时设置。<br>当你的场景非游戏或云游戏场景，又需要极低延时的体验时，可以使用该模式。<br>该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。<br>在使用此模式前，强烈建议咨询技术支持同学。 |
  | kRoomProfileTypeChat | `5` | 适用于 1 vs 1 音视频通话 |
  | kRoomProfileTypeChatRoom | `6` | 适用于 3 人及以上纯语音通话<br>音视频通话为媒体模式，上麦时切换为通话模式 |
  | kRoomProfileTypeLwTogether | `7` | 实现多端同步播放音视频，适用于 “一起看” 或 “一起听” 场景。<br>该场景中，使用 RTC 信令同步播放进度，共享的音频内容不通过 RTC 进行传输。 |
  | kRoomProfileTypeGameHD | `8` | 适用于对音质要求较高的游戏场景，优化音频 3A 策略，只通过媒体模式播放音频 |
  | kRoomProfileTypeCoHost | `9` | 适用于直播中主播之间连麦的业务场景。<br>直播时通过 CDN，发起连麦 PK 时使用 RTC。 |
  | kRoomProfileTypeInteractivePodcast | `10` | 适用于单主播和观众进行音视频互动的直播。通话模式，上下麦不会有模式切换，避免音量突变现象 |
  | kRoomProfileTypeKTV | `11` | 线上 KTV 场景，音乐音质，低延迟<br>使用 RTC 传输伴奏音乐，混音后的歌声，适合独唱或单通合唱 |
  | kRoomProfileTypeChorus | `12` | 适合在线实时合唱场景，高音质，超低延迟。使用本配置前请联系技术支持进行协助完成其他配置。 |
  | kRoomProfileTypeVRChat | `13` | 适用于 VR 场景。支持最高 192 KHz 音频采样率，可开启球形立体声。自 V3.45 及之后版本支持。 |
  | kRoomProfileTypeGameStreaming | `14` | 适用于 1 vs 1 游戏串流，支持公网或局域网。 |
  | kRoomProfileTypeLanLiveStreaming | `15` | 适用于局域网的 1 对多视频直播，最高支持 8K， 60 帧/秒， 100 Mbps 码率<br>需要在局域网配置私有化部署媒体服务器。 |
  | kRoomProfileTypeMeeting | `16` | 适用于云端会议中的个人设备 |
  | kRoomProfileTypeMeetingRoom | `17` | 适用于云端会议中的会议室终端设备，例如 Rooms，投屏盒子等。 |
  | kRoomProfileTypeClassroom | `18` | 适用于课堂互动，房间内所有成员都可以进行音视频互动<br>当你的场景中需要同时互动的成员超过 10 人时使用此模式 |



## RemoteVideoConfig <span id="remotevideoconfig"></span>

类型: `interface`

远端视频帧信息

<p style="font-size: 16px;font-weight: bolder;"> framerate <span id="remotevideoconfig-framerate"></span></p> 

类型: number | undefined

期望订阅的最高帧率，单位：fps，默认值为 0 即满帧订阅，设为大于 0 的值时开始生效。
如果发布端发布帧率 > 订阅端订阅的帧率，下行媒体服务器 SVC 丢帧，订阅端收到通过此接口设置的帧率；如果发布端发布帧率 < 订阅端订阅的帧率，则订阅端只能收到发布的帧率
仅码流支持 SVC 分级编码特性时方可生效。

<p style="font-size: 16px;font-weight: bolder;"> resolution_width <span id="remotevideoconfig-resolution_width"></span></p> 

类型: number | undefined

视频宽度，单位：px

<p style="font-size: 16px;font-weight: bolder;"> resolution_height <span id="remotevideoconfig-resolution_height"></span></p> 

类型: number | undefined

视频高度，单位：px


## MediaStreamType <span id="mediastreamtype"></span>

类型: `enum`

媒体流类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMediaStreamTypeAudio | `1` | 只控制音频 |
  | kMediaStreamTypeVideo | `2` | 只控制视频 |
  | kMediaStreamTypeBoth | `3` | 同时控制音频和视频 |



## PauseResumeControlMediaType <span id="pauseresumecontrolmediatype"></span>

类型: `enum`

暂停/恢复接收远端的媒体流类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRTCPauseResumeControlMediaTypeAudio | `0` | 只控制音频，不影响视频 |
  | kRTCPauseResumeControlMediaTypeVideo | `1` | 只控制视频，不影响音频 |
  | kRTCPauseResumeControlMediaTypeVideoAndAudio | `2` | 同时控制音频和视频 |



## ForwardStreamConfiguration <span id="forwardstreamconfiguration"></span>

类型: `interface`

媒体流跨房间转发的目标房间的相关信息

<p style="font-size: 16px;font-weight: bolder;"> forward_stream_dests <span id="forwardstreamconfiguration-forward_stream_dests"></span></p> 

类型: [ForwardStreamInfo](#forwardstreaminfo)[]

目标房间信息，数组中的每个元素包含一个房间的信息。


## ForwardStreamInfo <span id="forwardstreaminfo"></span>

类型: `interface`

媒体流跨房间转发的目标房间的相关信息

<p style="font-size: 16px;font-weight: bolder;"> token <span id="forwardstreaminfo-token"></span></p> 

类型: string

使用转发目标房间 RoomID 和 UserID 生成 Token。
测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。
如果 Token 无效，转发失败。

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="forwardstreaminfo-room_id"></span></p> 

类型: string

跨房间转发媒体流过程中目标房间 ID


## ReceiveRange <span id="receiverange"></span>

本地用户能收听到、且具有衰减效果的音频接收范围

- **类型**

  ```ts
  {
    max: number;
    min: number;
  }
  ```

- **成员**

  | 名称 | 类型 | 描述 |
  | :-- | :-- | :-- |

  | max | number | 能够收听语音的最大距离值，该值须 > 0 且 ≥ min。
当收听者和声源距离处于 [min, max) 之间时，收听到的音量根据距离呈衰减效果。
超出该值范围的音频将无法收听到。 |
  | min | number | 能够接收语音、并且具有衰减效果的最小距离值，该值须 ≥ 0，但 ≤ max。
小于该值的范围内没有范围语音效果，即收听到的音频音量相同。 |


## AttenuationType <span id="attenuationtype"></span>

类型: `enum`

空间音频音量随距离衰减模式

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAttenuationTypeNone | `0` | 不随距离衰减 |
  | kAttenuationTypeLinear | `1` | 线性衰减，音量随距离增大而线性减小 |
  | kAttenuationTypeExponential | `2` | 指数型衰减，音量随距离增大进行指数衰减 |



## HumanOrientation <span id="humanorientation"></span>

类型: `interface`

三维朝向信息，三个向量需要两两垂直。

<p style="font-size: 16px;font-weight: bolder;"> forward <span id="humanorientation-forward"></span></p> 

类型: [Orientation](#orientation)

正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向

<p style="font-size: 16px;font-weight: bolder;"> right <span id="humanorientation-right"></span></p> 

类型: [Orientation](#orientation)

正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向

<p style="font-size: 16px;font-weight: bolder;"> up <span id="humanorientation-up"></span></p> 

类型: [Orientation](#orientation)

正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向


## Orientation <span id="orientation"></span>

类型: `interface`

方向朝向信息

<p style="font-size: 16px;font-weight: bolder;"> x <span id="orientation-x"></span></p> 

类型: number

x 方向向量

<p style="font-size: 16px;font-weight: bolder;"> y <span id="orientation-y"></span></p> 

类型: number

y 方向向量

<p style="font-size: 16px;font-weight: bolder;"> z <span id="orientation-z"></span></p> 

类型: number

z 方向向量


## AudioSelectionPriority <span id="audioselectionpriority"></span>

类型: `enum`

音频选路优先级设置

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioSelectionPriorityNormal | `0` | 正常，参加音频选路 |
  | kAudioSelectionPriorityHigh | `1` | 高优先级，跳过音频选路 |



## SubtitleConfig <span id="subtitleconfig"></span>

类型: `interface`

字幕配置信息。

<p style="font-size: 16px;font-weight: bolder;"> mode <span id="subtitleconfig-mode"></span></p> 

类型: [SubtitleMode](#subtitlemode)

字幕模式。

<p style="font-size: 16px;font-weight: bolder;"> target_language <span id="subtitleconfig-target_language"></span></p> 

类型: string

目标翻译语言。可点击 [语言支持](https://www.volcengine.com/docs/4640/35107) 查看翻译服务最新支持的语种信息。


## SubtitleMode <span id="subtitlemode"></span>

类型: `enum`

字幕模式。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kSubtitleModeRecognition | `0` | 识别模式。在此模式下，房间内用户语音会被转为文字。 |
  | kSubtitleModeTranslation | `1` | 翻译模式。在此模式下，房间内用户语音会先被转为文字，再被翻译为目标语言。 |



## PositionInfo <span id="positioninfo"></span>

类型: `interface`

用户在空间音频坐标系里的位置信息。

<p style="font-size: 16px;font-weight: bolder;"> position <span id="positioninfo-position"></span></p> 

类型: [Position](#position)

用户在空间音频坐标系里的位置，需自行建立空间直角坐标系。

<p style="font-size: 16px;font-weight: bolder;"> orientation <span id="positioninfo-orientation"></span></p> 

类型: [HumanOrientation](#humanorientation)

用户在空间音频坐标系里的三维朝向信息。三个向量需要两两垂直。


## RtcRoomStats <span id="rtcroomstats"></span>

类型: `interface`

通话相关的统计信息

<p style="font-size: 16px;font-weight: bolder;"> tx_lostrate <span id="rtcroomstats-tx_lostrate"></span></p> 

类型: number

当前应用的上行丢包率，取值范围为 [0, 1]。

<p style="font-size: 16px;font-weight: bolder;"> rx_lostrate <span id="rtcroomstats-rx_lostrate"></span></p> 

类型: number

当前应用的下行丢包率，取值范围为 [0, 1]。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="rtcroomstats-rtt"></span></p> 

类型: number

客户端到服务端数据传输的往返时延（单位 ms）

<p style="font-size: 16px;font-weight: bolder;"> duration <span id="rtcroomstats-duration"></span></p> 

类型: number

本地用户在本次通话中的参与时长，单位为 s

<p style="font-size: 16px;font-weight: bolder;"> tx_bytes <span id="rtcroomstats-tx_bytes"></span></p> 

类型: number

本地用户的总发送字节数 (bytes)，累计值

<p style="font-size: 16px;font-weight: bolder;"> rx_bytes <span id="rtcroomstats-rx_bytes"></span></p> 

类型: number

本地用户的总接收字节数 (bytes)，累计值

<p style="font-size: 16px;font-weight: bolder;"> tx_kbitrate <span id="rtcroomstats-tx_kbitrate"></span></p> 

类型: number

发送码率 (kbps)，获取该数据时的瞬时值

<p style="font-size: 16px;font-weight: bolder;"> rx_kbitrate <span id="rtcroomstats-rx_kbitrate"></span></p> 

类型: number

接收码率 (kbps)，获取该数据时的瞬时值

<p style="font-size: 16px;font-weight: bolder;"> rx_audio_kbitrate <span id="rtcroomstats-rx_audio_kbitrate"></span></p> 

类型: number

音频接收码率 (kbps)，获取该数据时的瞬时值

<p style="font-size: 16px;font-weight: bolder;"> tx_audio_kbitrate <span id="rtcroomstats-tx_audio_kbitrate"></span></p> 

类型: number

音频发送码率 (kbps)，获取该数据时的瞬时值

<p style="font-size: 16px;font-weight: bolder;"> rx_video_kbitrate <span id="rtcroomstats-rx_video_kbitrate"></span></p> 

类型: number

视频接收码率 (kbps)，获取该数据时的瞬时值

<p style="font-size: 16px;font-weight: bolder;"> tx_video_kbitrate <span id="rtcroomstats-tx_video_kbitrate"></span></p> 

类型: number

视频发送码率 (kbps)，获取该数据时的瞬时值

<p style="font-size: 16px;font-weight: bolder;"> rx_screen_kbitrate <span id="rtcroomstats-rx_screen_kbitrate"></span></p> 

类型: number

屏幕接收码率，获取该数据时的瞬时值，单位为 Kbps

<p style="font-size: 16px;font-weight: bolder;"> tx_screen_kbitrate <span id="rtcroomstats-tx_screen_kbitrate"></span></p> 

类型: number

屏幕发送码率，获取该数据时的瞬时值，单位为 Kbps

<p style="font-size: 16px;font-weight: bolder;"> user_count <span id="rtcroomstats-user_count"></span></p> 

类型: number

当前房间内的用户人数

<p style="font-size: 16px;font-weight: bolder;"> tx_cellular_kbitrate <span id="rtcroomstats-tx_cellular_kbitrate"></span></p> 

类型: number

蜂窝路径发送的码率 (kbps)，获取该数据时的瞬时值

<p style="font-size: 16px;font-weight: bolder;"> rx_cellular_kbitrate <span id="rtcroomstats-rx_cellular_kbitrate"></span></p> 

类型: number

蜂窝路径接收码率 (kbps)，获取该数据时的瞬时值


## UserOfflineReasonType <span id="userofflinereasontype"></span>

类型: `enum`

用户离线原因。
房间内的远端用户离开房间时，本端用户会收到 [`onUserLeave`](Electron-event.md#rtcroomcallback-onuserleave) 回调通知，此枚举类型为回调的用户离线原因。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kUserOfflineReasonQuit | `0` | 远端用户调用 [`leaveRoom`](Electron-api.md#rtcroom-leaveroom) 方法退出房间。 |
  | kUserOfflineReasonDropped | `1` | 远端用户因网络等原因掉线。 |
  | kUserOfflineReasonSwitchToInvisible | `2` | 远端用户切换至不可见状态。 |
  | kUserOfflineReasonKickedByAdmin | `3` | 远端用户被踢出出房间。<br>因调用踢出用户的 OpenAPI，远端用户被踢出房间。 |



## AVSyncState <span id="avsyncstate"></span>

类型: `enum`

音视频同步状态

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAVSyncStateAVStreamSyncBegin | `0` | 音视频开始同步 |
  | kAVSyncStateAudioStreamRemove | `1` | 音视频同步过程中音频移除，但不影响当前的同步关系 |
  | kAVSyncStateVdieoStreamRemove | `2` | 音视频同步过程中视频移除，但不影响当前的同步关系 |



## LocalStreamStats <span id="localstreamstats"></span>

类型: `interface`

本地音/视频流统计信息，统计周期为 2s 。
本地用户发布音/视频流成功后，SDK 会周期性地通过 `onLocalStreamStats` 通知本地用户发布的音/视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> audio_stats <span id="localstreamstats-audio_stats"></span></p> 

类型: [LocalAudioStats](#localaudiostats)

本地设备发送音频流的统计信息

<p style="font-size: 16px;font-weight: bolder;"> video_stats <span id="localstreamstats-video_stats"></span></p> 

类型: [LocalVideoStats](#localvideostats)

本地设备发送视频流的统计信息

<p style="font-size: 16px;font-weight: bolder;"> is_screen <span id="localstreamstats-is_screen"></span></p> 

类型: boolean

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## LocalAudioStats <span id="localaudiostats"></span>

类型: `interface`

本地音频流统计信息，统计周期为 2s 。  本地用户发布音频流成功后，SDK 会周期性地通过 [`onLocalStreamStats`](Electron-event.md#rtcroomcallback-onlocalstreamstats) 通知用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> audio_loss_rate <span id="localaudiostats-audio_loss_rate"></span></p> 

类型: number

音频丢包率。此次统计周期内的音频上行丢包率，单位为 % ，取值范围为 [0, 1]。

<p style="font-size: 16px;font-weight: bolder;"> send_kbitrate <span id="localaudiostats-send_kbitrate"></span></p> 

类型: number

发送码率。此次统计周期内的音频发送码率，单位为 kbps 。

<p style="font-size: 16px;font-weight: bolder;"> record_sample_rate <span id="localaudiostats-record_sample_rate"></span></p> 

类型: number

采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。

<p style="font-size: 16px;font-weight: bolder;"> stats_interval <span id="localaudiostats-stats_interval"></span></p> 

类型: number

统计间隔。此次统计周期的间隔，单位为 ms 。
此字段用于设置回调的统计周期，默认设置为 2s 。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="localaudiostats-rtt"></span></p> 

类型: number

往返时延。单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> num_channels <span id="localaudiostats-num_channels"></span></p> 

类型: number

音频声道数。

<p style="font-size: 16px;font-weight: bolder;"> sent_sample_rate <span id="localaudiostats-sent_sample_rate"></span></p> 

类型: number

音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。

<p style="font-size: 16px;font-weight: bolder;"> jitter <span id="localaudiostats-jitter"></span></p> 

类型: number

音频上行网络抖动，单位为 ms 。


## LocalVideoStats <span id="localvideostats"></span>

类型: `interface`

本地视频流统计信息，统计周期为 2s 。
本地用户发布视频流成功后，SDK 会周期性地通过 [`onLocalStreamStats`](Electron-event.md#rtcroomcallback-onlocalstreamstats)  通知用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> sent_kbitrate <span id="localvideostats-sent_kbitrate"></span></p> 

类型: number

发送码率。此次统计周期内的视频发送码率，单位为 kbps 。

<p style="font-size: 16px;font-weight: bolder;"> input_frame_rate <span id="localvideostats-input_frame_rate"></span></p> 

类型: number

采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。

<p style="font-size: 16px;font-weight: bolder;"> sent_frame_rate <span id="localvideostats-sent_frame_rate"></span></p> 

类型: number

发送帧率。此次统计周期内的视频发送帧率，单位为 fps 。

<p style="font-size: 16px;font-weight: bolder;"> encoder_output_frame_rate <span id="localvideostats-encoder_output_frame_rate"></span></p> 

类型: number

编码器输出帧率。当前编码器在此次统计周期内的输出帧率，单位为 fps 。

<p style="font-size: 16px;font-weight: bolder;"> renderer_output_frame_rate <span id="localvideostats-renderer_output_frame_rate"></span></p> 

类型: number

本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。

<p style="font-size: 16px;font-weight: bolder;"> stats_interval <span id="localvideostats-stats_interval"></span></p> 

类型: number

统计间隔。此次统计周期的间隔，单位为 ms 。
此字段用于设置回调的统计周期，默认设置为 2s 。

<p style="font-size: 16px;font-weight: bolder;"> video_loss_rate <span id="localvideostats-video_loss_rate"></span></p> 

类型: number

视频丢包率。此次统计周期内的视频上行丢包率，取值范围为 [0，1] 。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="localvideostats-rtt"></span></p> 

类型: number

往返时延，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> encoded_bitrate <span id="localvideostats-encoded_bitrate"></span></p> 

类型: number

视频编码码率。此次统计周期内的视频编码码率，单位为 kbps 。

<p style="font-size: 16px;font-weight: bolder;"> encoded_frame_width <span id="localvideostats-encoded_frame_width"></span></p> 

类型: number

实际发送的分辨率最大的视频流的视频编码宽度，单位为 px 。

<p style="font-size: 16px;font-weight: bolder;"> encoded_frame_height <span id="localvideostats-encoded_frame_height"></span></p> 

类型: number

实际发送的分辨率最大的视频流的视频编码高度，单位为 px 。

<p style="font-size: 16px;font-weight: bolder;"> encoded_frame_count <span id="localvideostats-encoded_frame_count"></span></p> 

类型: number

此次统计周期内实际发送的分辨率最大的视频流的发送的视频帧总数。

<p style="font-size: 16px;font-weight: bolder;"> codec_type <span id="localvideostats-codec_type"></span></p> 

类型: [VideoCodecType](#videocodectype)

视频的编码类型

<p style="font-size: 16px;font-weight: bolder;"> is_screen <span id="localvideostats-is_screen"></span></p> 

类型: boolean

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。

<p style="font-size: 16px;font-weight: bolder;"> jitter <span id="localvideostats-jitter"></span></p> 

类型: number

视频上行网络抖动，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> codec_elapse_per_frame <span id="localvideostats-codec_elapse_per_frame"></span></p> 

类型: number

视频编码平均耗时，单位ms。


## VideoCodecType <span id="videocodectype"></span>

类型: `enum`

视频的编码类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kVideoCodecUnknown | `0` | 未知类型 |
  | kVideoCodecH264 | `1` | 标准H264 |



## RemoteStreamStats <span id="remotestreamstats"></span>

类型: `interface`

用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。
订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 [onRemoteStreamStats](Electron-event.md#rtcroomcallback-onremotestreamstats)
通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> uid <span id="remotestreamstats-uid"></span></p> 

类型: string

用户 ID 。音频来源的远端用户 ID 。

<p style="font-size: 16px;font-weight: bolder;"> audio_stats <span id="remotestreamstats-audio_stats"></span></p> 

类型: [RemoteAudioStats](#remoteaudiostats)

远端音频流的统计信息

<p style="font-size: 16px;font-weight: bolder;"> video_stats <span id="remotestreamstats-video_stats"></span></p> 

类型: [RemoteVideoStats](#remotevideostats)

远端视频流的统计信息

<p style="font-size: 16px;font-weight: bolder;"> is_screen <span id="remotestreamstats-is_screen"></span></p> 

类型: boolean

所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。


## RemoteAudioStats <span id="remoteaudiostats"></span>

类型: `interface`

远端音频流统计信息，统计周期为 2s。
本地用户订阅远端音频流成功后，SDK 会周期性地通过 [`onRemoteStreamStats`](Electron-event.md#rtcroomcallback-onremotestreamstats) 通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> audio_loss_rate <span id="remoteaudiostats-audio_loss_rate"></span></p> 

类型: number

音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。

<p style="font-size: 16px;font-weight: bolder;"> received_kbitrate <span id="remoteaudiostats-received_kbitrate"></span></p> 

类型: number

接收码率。统计周期内的音频接收码率，单位为 kbps 。

<p style="font-size: 16px;font-weight: bolder;"> stall_count <span id="remoteaudiostats-stall_count"></span></p> 

类型: number

音频卡顿次数。统计周期内的卡顿次数。

<p style="font-size: 16px;font-weight: bolder;"> stall_duration <span id="remoteaudiostats-stall_duration"></span></p> 

类型: number

音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> e2e_delay <span id="remoteaudiostats-e2e_delay"></span></p> 

类型: number

用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> playout_sample_rate <span id="remoteaudiostats-playout_sample_rate"></span></p> 

类型: number

播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。

<p style="font-size: 16px;font-weight: bolder;"> stats_interval <span id="remoteaudiostats-stats_interval"></span></p> 

类型: number

统计间隔。此次统计周期的间隔，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="remoteaudiostats-rtt"></span></p> 

类型: number

客户端到服务端数据传输的往返时延，单位为 ms。

<p style="font-size: 16px;font-weight: bolder;"> total_rtt <span id="remoteaudiostats-total_rtt"></span></p> 

类型: number

发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> quality <span id="remoteaudiostats-quality"></span></p> 

类型: number

远端用户发送的音频流质量。

+ `0`: 网络质量未知。
+ `1`: 网络质量极好。
+ `2`: 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
+ `3`: 主观感受有瑕疵但不影响沟通。
+ `4`: 勉强能沟通但不顺畅。
+ `5`: 网络质量非常差，基本不能沟通。

<p style="font-size: 16px;font-weight: bolder;"> jitter_buffer_delay <span id="remoteaudiostats-jitter_buffer_delay"></span></p> 

类型: number

因引入 jitter buffer 机制导致的延时。单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> num_channels <span id="remoteaudiostats-num_channels"></span></p> 

类型: number

音频声道数。

<p style="font-size: 16px;font-weight: bolder;"> received_sample_rate <span id="remoteaudiostats-received_sample_rate"></span></p> 

类型: number

音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。

<p style="font-size: 16px;font-weight: bolder;"> frozen_rate <span id="remoteaudiostats-frozen_rate"></span></p> 

类型: number

远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。

<p style="font-size: 16px;font-weight: bolder;"> concealed_samples <span id="remoteaudiostats-concealed_samples"></span></p> 

类型: number

音频 PLC 样点总个数。

<p style="font-size: 16px;font-weight: bolder;"> concealment_event <span id="remoteaudiostats-concealment_event"></span></p> 

类型: number

PLC 累计次数。

<p style="font-size: 16px;font-weight: bolder;"> dec_sample_rate <span id="remoteaudiostats-dec_sample_rate"></span></p> 

类型: number

音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。

<p style="font-size: 16px;font-weight: bolder;"> dec_duration <span id="remoteaudiostats-dec_duration"></span></p> 

类型: number

解码时长。对此次统计周期内接收的远端音频流进行解码的总耗时，单位为 s 。

<p style="font-size: 16px;font-weight: bolder;"> jitter <span id="remoteaudiostats-jitter"></span></p> 

类型: number

音频下行网络抖动，单位为 ms 。


## RemoteVideoStats <span id="remotevideostats"></span>

类型: `interface`

远端音频流统计信息，统计周期为 2s 。
本地用户订阅远端音频流成功后，SDK 会周期性地通过 [onRemoteStreamStats](Electron-event.md#rtcroomcallback-onremotestreamstats)
通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。

<p style="font-size: 16px;font-weight: bolder;"> width <span id="remotevideostats-width"></span></p> 

类型: number

视频宽度

<p style="font-size: 16px;font-weight: bolder;"> height <span id="remotevideostats-height"></span></p> 

类型: number

视频高度

<p style="font-size: 16px;font-weight: bolder;"> video_loss_rate <span id="remotevideostats-video_loss_rate"></span></p> 

类型: number

视频丢包率。统计周期内的视频下行丢包率，单位为 % ，取值范围：[0，1] 。

<p style="font-size: 16px;font-weight: bolder;"> received_kbitrate <span id="remotevideostats-received_kbitrate"></span></p> 

类型: number

接收码率。统计周期内的视频接收码率，单位为 kbps 。

<p style="font-size: 16px;font-weight: bolder;"> decoder_output_frame_rate <span id="remotevideostats-decoder_output_frame_rate"></span></p> 

类型: number

解码器输出帧率。统计周期内的视频解码器输出帧率，单位 fps 。

<p style="font-size: 16px;font-weight: bolder;"> renderer_output_frame_rate <span id="remotevideostats-renderer_output_frame_rate"></span></p> 

类型: number

渲染帧率。统计周期内的视频渲染帧率，单位 fps 。

<p style="font-size: 16px;font-weight: bolder;"> stall_count <span id="remotevideostats-stall_count"></span></p> 

类型: number

卡顿次数。统计周期内的卡顿次数。

<p style="font-size: 16px;font-weight: bolder;"> stall_duration <span id="remotevideostats-stall_duration"></span></p> 

类型: number

卡顿时长。统计周期内的视频卡顿总时长。单位 ms 。

<p style="font-size: 16px;font-weight: bolder;"> e2eDelay <span id="remotevideostats-e2edelay"></span></p> 

类型: number

用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> is_screen <span id="remotevideostats-is_screen"></span></p> 

类型: number

所属用户的媒体流是否为屏幕流。你可以知道当前数据来自主流还是屏幕流。

<p style="font-size: 16px;font-weight: bolder;"> stats_interval <span id="remotevideostats-stats_interval"></span></p> 

类型: number

统计间隔，此次统计周期的间隔，单位为 ms 。

- **注意**

  此字段用于设置回调的统计周期，目前设置为 2s 。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="remotevideostats-rtt"></span></p> 

类型: number

往返时延，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> frozen_rate <span id="remotevideostats-frozen_rate"></span></p> 

类型: number

远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。

<p style="font-size: 16px;font-weight: bolder;"> codec_type <span id="remotevideostats-codec_type"></span></p> 

类型: [VideoCodecType](#videocodectype)

视频的编码类型

<p style="font-size: 16px;font-weight: bolder;"> video_index <span id="remotevideostats-video_index"></span></p> 

类型: number

对应多种分辨率的流的下标

<p style="font-size: 16px;font-weight: bolder;"> jitter <span id="remotevideostats-jitter"></span></p> 

类型: number

视频下行网络抖动，单位为 ms 。

<p style="font-size: 16px;font-weight: bolder;"> codec_elapse_per_frame <span id="remotevideostats-codec_elapse_per_frame"></span></p> 

类型: number

视频解码平均耗时，单位 ms。


## StreamRemoveReason <span id="streamremovereason"></span>

类型: `enum`

房间内远端流被移除的原因。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kStreamRemoveReasonUnpublish | `0` | 远端用户停止发布流。 |
  | kStreamRemoveReasonPublishFailed | `1` | 远端用户发布流失败。 |
  | kStreamRemoveReasonKeepLiveFailed | `2` | 保活失败。 |
  | kStreamRemoveReasonClientDisconnected | `3` | 远端用户断网。 |
  | kStreamRemoveReasonRepublish | `4` | 远端用户重新发布流。 |
  | kStreamRemoveReasonOther | `5` | 其他原因。 |



## SubscribeState <span id="subscribestate"></span>

类型: `enum`

订阅媒体流状态

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kSubscribeStateSuccess | `0` | 订阅/取消订阅流成功 |
  | kSubscribeStateFailedNotInRoom | `1` | 订阅/取消订阅流失败，本地用户未在房间中 |
  | kSubscribeStateFailedStreamNotFound | `2` | 订阅/取消订阅流失败，房间内未找到指定的音视频流 |
  | kSubscribeStateFailedOverLimit | `3` | 超过订阅流数上限 |



## SubscribeConfig <span id="subscribeconfig"></span>

类型: `interface`

手动订阅流的配置信息。

<p style="font-size: 16px;font-weight: bolder;"> is_screen <span id="subscribeconfig-is_screen"></span></p> 

类型: boolean

是否是屏幕流，默认为否。

<p style="font-size: 16px;font-weight: bolder;"> sub_video <span id="subscribeconfig-sub_video"></span></p> 

类型: boolean

是否订阅视频。

<p style="font-size: 16px;font-weight: bolder;"> sub_audio <span id="subscribeconfig-sub_audio"></span></p> 

类型: boolean

是否订阅音频。

<p style="font-size: 16px;font-weight: bolder;"> video_index <span id="subscribeconfig-video_index"></span></p> 

类型: number

订阅的视频流分辨率下标。
用户可以通过调用 [setVideoEncoderConfig](Electron-api.md#setvideoencoderconfig) 方法在一路流中发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。

<p style="font-size: 16px;font-weight: bolder;"> priority <span id="subscribeconfig-priority"></span></p> 

类型: number

远端用户的需求优先级，0 为默认值。

+ `0`: 默认，用户优先级为低
+ `100`: 用户优先级为正常
+ `200`: 用户优先级为高
当开启了订阅流回退选项功能（详见 [setSubscribeFallbackOption](Electron-api.md#setsubscribefallbackoption) 方法），弱网或性能不足时会优先保证收到的高优先级用户的流的质量。

<p style="font-size: 16px;font-weight: bolder;"> svc_layer <span id="subscribeconfig-svc_layer"></span></p> 

类型: number

远端用户的时域分层，0 为默认值。
仅码流支持 SVC 特性时可以生效。

<p style="font-size: 16px;font-weight: bolder;"> framerate <span id="subscribeconfig-framerate"></span></p> 

类型: number

期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。
如果发布端发布帧率 > 订阅端订阅的帧率，下行媒体服务器 SVC 丢帧，订阅端收到通过此接口设置的帧率；如果发布端发布帧率 < 订阅端订阅的帧率，则订阅端只能收到发布的帧率
仅码流支持 SVC 分级编码特性时方可生效。

<p style="font-size: 16px;font-weight: bolder;"> sub_width <span id="subscribeconfig-sub_width"></span></p> 

类型: number

用户通过指定 UI 对应的最合适的流的宽度，单位：px

<p style="font-size: 16px;font-weight: bolder;"> sub_height <span id="subscribeconfig-sub_height"></span></p> 

类型: number

用户通过指定 UI 对应的最合适的流的高度，单位：px


## ForwardStreamStateInfo <span id="forwardstreamstateinfo"></span>

类型: `interface`

跨房间转发媒体流过程中的不同目标房间的状态和错误信息

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="forwardstreamstateinfo-room_id"></span></p> 

类型: string

跨房间转发媒体流过程中目标房间 ID
空字符串代表所有目标房间

<p style="font-size: 16px;font-weight: bolder;"> state <span id="forwardstreamstateinfo-state"></span></p> 

类型: [ForwardStreamState](#forwardstreamstate)

跨房间转发媒体流过程中该目标房间的状态、

<p style="font-size: 16px;font-weight: bolder;"> error <span id="forwardstreamstateinfo-error"></span></p> 

类型: [ForwardStreamError](Electron-errorcode.md#forwardstreamerror)

跨房间转发媒体流过程中该目标房间抛出的错误码


## ForwardStreamState <span id="forwardstreamstate"></span>

类型: `enum`

跨房间转发媒体流过程中的不同目标房间的状态和错误信息

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kForwardStreamStateIdle | `0` | 空闲状态<br>+ 成功调用 `stopForwardStreamToRooms` 后，所有目标房间为空闲状态。<br>+ 成功调用 `updateForwardStreamToRooms` 减少目标房间后，本次减少的目标房间为空闲状态。 |
  | kForwardStreamStateSuccess | `1` | 开始转发<br>+ 调用 `startForwardStreamToRooms` 成功向所有房间开始转发媒体流后，返回此状态。<br>+ 调用 `updateForwardStreamToRooms` 后，成功向新增目标房间开始转发媒体流后，返回此状态。 |
  | kForwardStreamStateFailure | `2` | 转发失败，失败详情参考 [ForwardStreamError](Electron-errorcode.md#forwardstreamerror)<br>调用 `startForwardStreamToRooms` 或 `updateForwardStreamToRooms` 后，如遇转发失败，返回此状态。 |



## ForwardStreamEventInfo <span id="forwardstreameventinfo"></span>

类型: `interface`

跨房间转发媒体流过程中的不同目标房间发生的事件

<p style="font-size: 16px;font-weight: bolder;"> room_id <span id="forwardstreameventinfo-room_id"></span></p> 

类型: string

跨房间转发媒体流过程中的发生该事件的目标房间 ID
空字符串代表所有目标房间

<p style="font-size: 16px;font-weight: bolder;"> event <span id="forwardstreameventinfo-event"></span></p> 

类型: [ForwardStreamEvent](#forwardstreamevent)

跨房间转发媒体流过程中该目标房间发生的事件


## ForwardStreamEvent <span id="forwardstreamevent"></span>

类型: `enum`

媒体流跨房间转发事件

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kForwardStreamEventDisconnected | `0` | 本端与服务器网络连接断开，暂停转发。 |
  | kForwardStreamEventConnected | `1` | 本端与服务器网络连接恢复，转发服务连接成功。 |
  | kForwardStreamEventInterrupt | `2` | 转发中断。转发过程中，如果相同 user_id 的用户进入目标房间，转发中断。 |
  | kForwardStreamEventDstRoomUpdated | `3` | 目标房间已更新，由 `updateForwardStreamToRooms` 触发。 |
  | kForwardStreamEventUnExpectAPICall | `4` | API 调用时序错误。例如，在调用 `startForwardStreamToRooms` 之前调用 `updateForwardStreamToRooms` 。 |



## NetworkQualityStats <span id="networkqualitystats"></span>

类型: `interface`

上行/下行网络质量

<p style="font-size: 16px;font-weight: bolder;"> uid <span id="networkqualitystats-uid"></span></p> 

类型: string

用户 id

<p style="font-size: 16px;font-weight: bolder;"> fraction_lost <span id="networkqualitystats-fraction_lost"></span></p> 

类型: number

本端的上行/下行的丢包率，范围 [0.0,1.0]
当 `uid` 为本地用户时，代表发布流的上行丢包率。
当 `uid` 为远端用户时，代表接收所有订阅流的下行丢包率。

<p style="font-size: 16px;font-weight: bolder;"> rtt <span id="networkqualitystats-rtt"></span></p> 

类型: number

当 `uid` 为本地用户时有效，客户端到服务端的往返延时（RTT），单位：ms

<p style="font-size: 16px;font-weight: bolder;"> rx_quality <span id="networkqualitystats-rx_quality"></span></p> 

类型: [NetworkQuality](#networkquality)

下行网络质量分。范围 [0,5]，分数越高网络质量越差。

<p style="font-size: 16px;font-weight: bolder;"> total_bandwidth <span id="networkqualitystats-total_bandwidth"></span></p> 

类型: number

本端的音视频 RTP 包 2 秒内的平均传输速率，单位：bps
当 `uid` 为本地用户时，代表发送速率。
当 `uid` 为远端用户时，代表所有订阅流的接收速率。

<p style="font-size: 16px;font-weight: bolder;"> tx_quality <span id="networkqualitystats-tx_quality"></span></p> 

类型: [NetworkQuality](#networkquality)

上行网络质量分。范围 [0,5]，分数越高网络质量越差。


## NetworkQuality <span id="networkquality"></span>

类型: `enum`

媒体流网络质量。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kNetworkQualityUnknown | `0` | 网络质量未知。 |
  | kNetworkQualityExcellent | `1` | 网络质量极好。 |
  | kNetworkQualityGood | `2` | 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。 |
  | kNetworkQualityPoor | `3` | 主观感受有瑕疵但不影响沟通。 |
  | kNetworkQualityBad | `4` | 勉强能沟通但不顺畅。 |
  | kNetworkQualityVbad | `5` | 网络质量非常差，基本不能沟通。 |



## SetRoomExtraInfoResult <span id="setroomextrainforesult"></span>

类型: `enum`

设置房间附加消息结果。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kSetRoomExtraInfoResultSuccess | `0` | 设置房间附加信息成功 |
  | kSetRoomExtraInfoResultErrorNotJoinRoom | `-1` | 设置失败，尚未加入房间 |
  | kSetRoomExtraInfoResultErrorKeyIsNull | `-2` | 设置失败，key 指针为空 |
  | kSetRoomExtraInfoResultErrorValueIsNull | `-3` | 设置失败，value 指针为空 |
  | kSetRoomExtraInfoResultResultUnknow | `-99` | 设置失败，未知错误 |
  | kSetRoomExtraInfoResultErrorKeyIsEmpty | `-400` | 设置失败，key 长度为 0 |
  | kSetRoomExtraInfoResultErrorTooOften | `-406` | 调用 `setRoomExtraInfo` 过于频繁，建议不超过 10 次/秒。 |
  | kSetRoomExtraInfoResultErrorSilentUser | `-412` | 设置失败，用户已调用 `setUserVisibility` 将自身设为不可见状态。 |
  | kSetRoomExtraInfoResultErrorKeyTooLong | `-413` | 设置失败，Key 长度超过 10 字节 |
  | kSetRoomExtraInfoResultErrorValueTooLong | `-414` | 设置失败，value 长度超过 128 字节 |
  | kSetRoomExtraInfoResultErrorServer | `-500` | 设置失败，服务器错误 |



## SubtitleState <span id="subtitlestate"></span>

类型: `enum`

字幕任务状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kSubtitleStateStarted | `0` | 开启字幕。 |
  | kSubtitleStateStoped | `1` | 关闭字幕。 |
  | kSubtitleStateError | `2` | 字幕任务出现错误。 |



## SubtitleMessage <span id="subtitlemessage"></span>

类型: `interface`

字幕具体内容。

<p style="font-size: 16px;font-weight: bolder;"> user_id <span id="subtitlemessage-user_id"></span></p> 

类型: string

说话者的用户ID。

<p style="font-size: 16px;font-weight: bolder;"> text <span id="subtitlemessage-text"></span></p> 

类型: string

语音识别或翻译后的文本, 采用 UTF-8 编码。

<p style="font-size: 16px;font-weight: bolder;"> sequence <span id="subtitlemessage-sequence"></span></p> 

类型: number

语音识别或翻译后形成的文本的序列号，同一发言人的完整发言和不完整发言会按递增顺序单独分别编号。

<p style="font-size: 16px;font-weight: bolder;"> definite <span id="subtitlemessage-definite"></span></p> 

类型: boolean

语音识别出的文本是否为一段完整的一句话。 true 代表是, false 代表不是。

<p style="font-size: 16px;font-weight: bolder;"> language <span id="subtitlemessage-language"></span></p> 

类型: string

字幕语种，根据字幕模式为原文或译文对应的语种。

<p style="font-size: 16px;font-weight: bolder;"> mode <span id="subtitlemessage-mode"></span></p> 

类型: [SubtitleMode](#subtitlemode)

字幕模式


## MusicInfo <span id="musicinfo"></span>

类型: `interface`

歌曲数据。

<p style="font-size: 16px;font-weight: bolder;"> music_id <span id="musicinfo-music_id"></span></p> 

类型: string

音乐 ID。

<p style="font-size: 16px;font-weight: bolder;"> music_name <span id="musicinfo-music_name"></span></p> 

类型: string

音乐名称。

<p style="font-size: 16px;font-weight: bolder;"> singer <span id="musicinfo-singer"></span></p> 

类型: string

歌手。

<p style="font-size: 16px;font-weight: bolder;"> vendor_id <span id="musicinfo-vendor_id"></span></p> 

类型: string

版权商 ID。

<p style="font-size: 16px;font-weight: bolder;"> vendor_name <span id="musicinfo-vendor_name"></span></p> 

类型: string

版权商名称。

<p style="font-size: 16px;font-weight: bolder;"> update_timestamp <span id="musicinfo-update_timestamp"></span></p> 

类型: number

最新更新时间戳，单位为毫秒。

<p style="font-size: 16px;font-weight: bolder;"> poster_url <span id="musicinfo-poster_url"></span></p> 

类型: string

封面地址。

<p style="font-size: 16px;font-weight: bolder;"> lyric_status <span id="musicinfo-lyric_status"></span></p> 

类型: [LyricStatus](#lyricstatus)

歌词格式类型。

<p style="font-size: 16px;font-weight: bolder;"> duration <span id="musicinfo-duration"></span></p> 

类型: number

歌曲长度，单位为毫秒。

<p style="font-size: 16px;font-weight: bolder;"> enable_score <span id="musicinfo-enable_score"></span></p> 

类型: boolean

歌曲是否支持打分。

<p style="font-size: 16px;font-weight: bolder;"> climax_start_time <span id="musicinfo-climax_start_time"></span></p> 

类型: number

歌曲高潮片段开始时间，单位为毫秒。

<p style="font-size: 16px;font-weight: bolder;"> climax_stop_time <span id="musicinfo-climax_stop_time"></span></p> 

类型: number

歌曲高潮片段停止时间，单位为毫秒。


## LyricStatus <span id="lyricstatus"></span>

类型: `enum`

歌词格式类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kNone | `0` | 无歌词。 |
  | kKRC | `1` | KRC 歌词。 |
  | kLRC | `2` | LRC 歌词。 |
  | kKRCAndLRC | `3` | KRC 歌词和 LRC 歌词均有。 |



## HotMusicInfo <span id="hotmusicinfo"></span>

类型: `interface`

热榜歌曲数据。

<p style="font-size: 16px;font-weight: bolder;"> hot_type <span id="hotmusicinfo-hot_type"></span></p> 

类型: [MusicHotType](#musichottype)

热榜类别。多个热榜类别可以按位或组合。

<p style="font-size: 16px;font-weight: bolder;"> hot_name <span id="hotmusicinfo-hot_name"></span></p> 

类型: string

热榜名称。

<p style="font-size: 16px;font-weight: bolder;"> musics <span id="hotmusicinfo-musics"></span></p> 

类型: [MusicInfo](#musicinfo)[]

歌曲数据。


## MusicHotType <span id="musichottype"></span>

类型: `enum`

热榜类别。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMusicHotTypeContentCenter |  | 火山内容中心热歌榜。 |
  | kMusicHotTypeProject |  | 项目热歌榜。 |



## DownloadResult <span id="downloadresult"></span>

类型: `interface`

歌曲下载信息。

<p style="font-size: 16px;font-weight: bolder;"> local_file_path <span id="downloadresult-local_file_path"></span></p> 

类型: string

文件存放路径。

<p style="font-size: 16px;font-weight: bolder;"> music_id <span id="downloadresult-music_id"></span></p> 

类型: string

音乐 ID。

<p style="font-size: 16px;font-weight: bolder;"> type <span id="downloadresult-type"></span></p> 

类型: [DownloadFileType](#downloadfiletype)

下载文件类型。


## DownloadFileType <span id="downloadfiletype"></span>

类型: `enum`

下载文件类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kDownloadFileTypeMusic | `1` | 音频文件。 |
  | kDownloadFileTypeKRC | `2` | KRC 歌词文件。 |
  | kDownloadFileTypeLRC | `3` | LRC 歌词文件。 |
  | kDownloadFileTypeMIDI | `4` | MIDI 文件。 |



## PlayState <span id="playstate"></span>

类型: `enum`

音乐播放状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kPlaying | `1` | 播放中。 |
  | kPaused | `2` | 暂停中。 |
  | kStoped | `3` | 已停止。 |
  | kFailed | `4` | 播放失败。 |
  | kFinished | `5` | 播放结束。 |



## RtcUser <span id="rtcuser"></span>

类型: `interface`

用户信息

<p style="font-size: 16px;font-weight: bolder;"> user_id <span id="rtcuser-user_id"></span></p> 

类型: string

用户 id

<p style="font-size: 16px;font-weight: bolder;"> meta_data <span id="rtcuser-meta_data"></span></p> 

类型: string

元数据


## FirstFrameSendState <span id="firstframesendstate"></span>

类型: `enum`

首帧发送状态

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kFirstFrameSendStateSending | `0` | 发送中 |
  | kFirstFrameSendStateSent | `1` | 发送成功 |
  | kFirstFrameSendStateEnd | `2` | 发送失败 |



## FirstFramePlayState <span id="firstframeplaystate"></span>

类型: `enum`

首帧播放状态

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kFirstFramePlayStatePlaying | `0` | 播放中 |
  | kFirstFramePlayStatePlayed | `1` | 播放成功 |
  | kFirstFramePlayStateEnd | `2` | 播放失败 |



## FaceDetectResult <span id="facedetectresult"></span>

类型: `interface`

人脸检测结果

<p style="font-size: 16px;font-weight: bolder;"> detect_result <span id="facedetectresult-detect_result"></span></p> 

类型: number

人脸检测结果

+ 0：检测成功
+ !0：检测失败。详见[错误码表](https://www.volcengine.com/docs/6705/102042)。

<p style="font-size: 16px;font-weight: bolder;"> face_count <span id="facedetectresult-face_count"></span></p> 

类型: number

检测到的人脸的数量

<p style="font-size: 16px;font-weight: bolder;"> rect <span id="facedetectresult-rect"></span></p> 

类型: [Rectangle](#rectangle)[]

识别到人脸的矩形框。数组的长度和检测到的人脸数量一致。

<p style="font-size: 16px;font-weight: bolder;"> image_width <span id="facedetectresult-image_width"></span></p> 

类型: number

原始图片宽度(px)

<p style="font-size: 16px;font-weight: bolder;"> image_height <span id="facedetectresult-image_height"></span></p> 

类型: number

原始图片高度(px)

<p style="font-size: 16px;font-weight: bolder;"> frame_timestamp_us <span id="facedetectresult-frame_timestamp_us"></span></p> 

类型: number

进行人脸识别的视频帧的时间戳。


## RTCAudioDeviceType <span id="rtcaudiodevicetype"></span>

类型: `enum`

音频设备类型

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRTCAudioDeviceTypeUnknown | `-1` | 未知设备类型 |
  | kRTCAudioDeviceTypeRenderDevice | `0` | 音频渲染设备 |
  | kRTCAudioDeviceTypeCaptureDevice | `1` | 音频采集设备 |
  | kRTCAudioDeviceTypeScreenCaptureDevice | `2` | 屏幕流音频设备 |



## SingScoringRealtimeInfo <span id="singscoringrealtimeinfo"></span>

类型: `interface`

实时评分信息。

<p style="font-size: 16px;font-weight: bolder;"> current_position <span id="singscoringrealtimeinfo-current_position"></span></p> 

类型: number

当前播放进度。

<p style="font-size: 16px;font-weight: bolder;"> user_pitch <span id="singscoringrealtimeinfo-user_pitch"></span></p> 

类型: number

演唱者的音高。

<p style="font-size: 16px;font-weight: bolder;"> standard_pitch <span id="singscoringrealtimeinfo-standard_pitch"></span></p> 

类型: number

标准音高。

<p style="font-size: 16px;font-weight: bolder;"> sentence_index <span id="singscoringrealtimeinfo-sentence_index"></span></p> 

类型: number

歌词分句索引。

<p style="font-size: 16px;font-weight: bolder;"> sentence_score <span id="singscoringrealtimeinfo-sentence_score"></span></p> 

类型: number

上一句歌词的评分。

<p style="font-size: 16px;font-weight: bolder;"> total_score <span id="singscoringrealtimeinfo-total_score"></span></p> 

类型: number

当前演唱的累计分数。

<p style="font-size: 16px;font-weight: bolder;"> average_score <span id="singscoringrealtimeinfo-average_score"></span></p> 

类型: number

当前演唱的平均分数。


## AudioRecordingState <span id="audiorecordingstate"></span>

类型: `enum`

录音配置

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioRecordingStateError | `0` | 录制异常 |
  | kAudioRecordingStateProcessing | `1` | 录制进行中 |
  | kAudioRecordingStateSuccess | `2` | 已结束录制，并且录制文件保存成功。 |



## DataMessageSourceType <span id="datamessagesourcetype"></span>

类型: `enum`

SEI 信息来源。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kDataMessageSourceTypeDefault | `0` | 通过客户端或服务端的插入的自定义消息。 |
  | kDataMessageSourceTypeSystem | `1` | 系统数据，包含音量指示信息。 |



## HardwareEchoDetectionResult <span id="hardwareechodetectionresult"></span>

类型: `enum`

通话前回声检测结果

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kHardwareEchoDetectionResultCanceled | `0` | 主动调用 `stopHardwareEchoDetection` 结束流程时，未有回声检测结果。 |
  | kHardwareEchoDetectionResultUnknown | `1` | 未检测出结果。建议重试，如果仍然失败请联系技术支持协助排查。 |
  | kHardwareEchoDetectionResultNormal | `2` | 无回声 |
  | kHardwareEchoDetectionResultPoor | `3` | 有回声。可通过 UI 建议用户使用耳机设备入会。 |



## LocalProxyState <span id="localproxystate"></span>

类型: `enum`

本地代理连接状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLocalProxyStateInited | `0` | TCP 代理服务器连接成功。 |
  | kLocalProxyStateConnected | `1` | 本地代理连接成功。 |
  | kLocalProxyStateError | `2` | 本地代理连接出现错误。 |



## StreamMixingEvent <span id="streammixingevent"></span>

类型: `enum`

转推直播事件

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kStreamMixingEventStart | `1` | 请求发起转推直播任务 |
  | kStreamMixingEventStartSuccess | `2` | 发起转推直播任务成功 |
  | kStreamMixingEventStartFailed | `3` | 发起转推直播任务失败 |
  | kStreamMixingEventUpdate | `4` | 请求更新转推直播任务配置 |
  | kStreamMixingEventUpdateSuccess | `5` | 成功更新转推直播任务配置 |
  | kStreamMixingEventUpdateFailed | `6` | 更新转推直播任务配置失败 |
  | kStreamMixingEventStop | `7` | 请求结束转推直播任务 |
  | kStreamMixingEventStopSuccess | `8` | 结束转推直播任务成功 |
  | kStreamMixingEventStopFailed | `9` | 结束转推直播任务失败 |
  | kStreamMixingEventChangeMixType | `10` | 更新转推直播任务配置的请求超时 |
  | kStreamMixingEventFirstAudioFrameByClientMix | `11` | 得到客户端合流音频首帧 |
  | kStreamMixingEventFirstVideoFrameByClientMix | `12` | 收到客户端合流视频首帧 |
  | kStreamMixingEventUpdateTimeout | `13` | 更新转推直播任务配置超时 |
  | kStreamMixingEventStartTimeout | `14` | 发起转推直播任务配置超时 |
  | kStreamMixingEventRequestParamError | `15` | 合流布局参数错误 |
  | kStreamMixingEventMixImageEvent | `16` | 合流加图片 |



## IVideoFrame <span id="ivideoframe"></span>

类型: `interface`

设置视频帧

<p style="font-size: 16px;font-weight: bolder;"> channel_id <span id="ivideoframe-channel_id"></span></p> 

类型: string

房间 ID

<p style="font-size: 16px;font-weight: bolder;"> user_id <span id="ivideoframe-user_id"></span></p> 

类型: string

用户 ID

<p style="font-size: 16px;font-weight: bolder;"> plane_y <span id="ivideoframe-plane_y"></span></p> 

类型: Uint8Array

视频数据缓冲区 Y

<p style="font-size: 16px;font-weight: bolder;"> plane_u <span id="ivideoframe-plane_u"></span></p> 

类型: Uint8Array

视频数据缓冲区 U

<p style="font-size: 16px;font-weight: bolder;"> plane_v <span id="ivideoframe-plane_v"></span></p> 

类型: Uint8Array

视频数据缓冲区 V

<p style="font-size: 16px;font-weight: bolder;"> width <span id="ivideoframe-width"></span></p> 

类型: number

视频分辨率宽度，单位：像素

<p style="font-size: 16px;font-weight: bolder;"> height <span id="ivideoframe-height"></span></p> 

类型: number

视频分辨率高度，单位：像素

<p style="font-size: 16px;font-weight: bolder;"> plane_size_y <span id="ivideoframe-plane_size_y"></span></p> 

类型: number

视频数据缓冲区 Y 大小

<p style="font-size: 16px;font-weight: bolder;"> plane_size_u <span id="ivideoframe-plane_size_u"></span></p> 

类型: number

视频数据缓冲区 U 大小

<p style="font-size: 16px;font-weight: bolder;"> plane_size_v <span id="ivideoframe-plane_size_v"></span></p> 

类型: number

视频数据缓冲区 V 大小

<p style="font-size: 16px;font-weight: bolder;"> format <span id="ivideoframe-format"></span></p> 

类型: [VideoPixelFormat](#videopixelformat)

视频帧数据格式

<p style="font-size: 16px;font-weight: bolder;"> rotation <span id="ivideoframe-rotation"></span></p> 

类型: number

视频帧旋转角度

<p style="font-size: 16px;font-weight: bolder;"> rgba <span id="ivideoframe-rgba"></span></p> 

类型: Uint8Array

视频数据缓冲区 RGBA

<p style="font-size: 16px;font-weight: bolder;"> rgba_size <span id="ivideoframe-rgba_size"></span></p> 

类型: number

视频数据缓冲区 RGBA 大小

<p style="font-size: 16px;font-weight: bolder;"> public_stream_id <span id="ivideoframe-public_stream_id"></span></p> 

类型: number

公共流 ID

<p style="font-size: 16px;font-weight: bolder;"> task_id <span id="ivideoframe-task_id"></span></p> 

类型: string

合流任务 ID


## IAudioFrame <span id="iaudioframe"></span>

类型: `interface`

设置音频帧

<p style="font-size: 16px;font-weight: bolder;"> frame_type <span id="iaudioframe-frame_type"></span></p> 

类型: AudioFrameType

值: `0`

音频帧类型。目前只支持 PCM

<p style="font-size: 16px;font-weight: bolder;"> channels <span id="iaudioframe-channels"></span></p> 

类型: number

音频通道数
双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。

<p style="font-size: 16px;font-weight: bolder;"> sample_rate <span id="iaudioframe-sample_rate"></span></p> 

类型: number

音频采样率，单位：Hz

<p style="font-size: 16px;font-weight: bolder;"> buffer <span id="iaudioframe-buffer"></span></p> 

类型: Uint8Array

音频数据内存地址

<p style="font-size: 16px;font-weight: bolder;"> render_time_ms <span id="iaudioframe-render_time_ms"></span></p> 

类型: number

音频帧时间戳，单位：毫秒

<p style="font-size: 16px;font-weight: bolder;"> mute <span id="iaudioframe-mute"></span></p> 

类型: boolean

获取音频静音标志


## IDataFrame <span id="idataframe"></span>

类型: `interface`

数据帧

<p style="font-size: 16px;font-weight: bolder;"> frame_type <span id="idataframe-frame_type"></span></p> 

类型: DataFrameType

值: `0`

数据帧类型

<p style="font-size: 16px;font-weight: bolder;"> u8_data <span id="idataframe-u8_data"></span></p> 

类型: Uint8Array

数据帧数据

<p style="font-size: 16px;font-weight: bolder;"> u64_ts_us <span id="idataframe-u64_ts_us"></span></p> 

类型: number

数据帧时间戳，单位：微秒


## VideoFrameInfo <span id="videoframeinfo"></span>

类型: `interface`

视频帧信息

<p style="font-size: 16px;font-weight: bolder;"> width <span id="videoframeinfo-width"></span></p> 

类型: number

视频帧的宽度（像素）

<p style="font-size: 16px;font-weight: bolder;"> height <span id="videoframeinfo-height"></span></p> 

类型: number

视频帧的高度（像素）

<p style="font-size: 16px;font-weight: bolder;"> rotation <span id="videoframeinfo-rotation"></span></p> 

类型: [VideoRotation](#videorotation)

视频帧顺时针旋转角度。


## AudioMixingState <span id="audiomixingstate"></span>

类型: `enum`

音频混音文件播放状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kAudioMixingStatePreloaded | `0` | 混音已加载 |
  | kAudioMixingStatePlaying | `1` | 混音正在播放 |
  | kAudioMixingStatePaused | `2` | 混音暂停 |
  | kAudioMixingStateStopped | `3` | 混音停止 |
  | kAudioMixingStateFailed | `4` | 混音播放失败 |
  | kAudioMixingStateFinished | `5` | 混音播放结束 |



## ConnectionState <span id="connectionstate"></span>

类型: `enum`

SDK 与信令服务器连接状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kConnectionStateDisconnected | `1` | 连接断开。 |
  | kConnectionStateConnecting | `2` | 首次连接，正在连接中。 |
  | kConnectionStateConnected | `3` | 涵盖了以下情况：<br>+ 首次连接时，10秒连接不成功;<br>+ 连接成功后，断连 10 秒。自动重连中。 |
  | kConnectionStateReconnecting | `4` | 涵盖了以下情况：<br>+ 首次连接时，10秒连接不成功;<br>+ 连接成功后，断连 10 秒。自动重连中。 |
  | kConnectionStateReconnected | `5` | 连接断开后重连成功。 |
  | kConnectionStateLost | `6` | 处于 `kConnectionStateDisconnected` 状态超过 10 秒，且期间重连未成功。SDK 仍将继续尝试重连。 |



## NetworkType <span id="networktype"></span>

类型: `enum`

SDK 网络连接类型。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kNetworkTypeUnknown | `-1` | 网络连接类型未知。 |
  | kNetworkTypeDisconnected | `0` | 网络连接已断开。 |
  | kNetworkTypeLAN | `1` | 网络连接类型为 LAN 。 |
  | kNetworkTypeWIFI | `2` | 网络连接类型为 Wi-Fi（包含热点）。 |
  | kNetworkTypeMobile2G | `3` | 网络连接类型为 2G 移动网络。 |
  | kNetworkTypeMobile3G | `4` | 网络连接类型为 3G 移动网络。 |
  | kNetworkTypeMobile4G | `5` | 网络连接类型为 4G 移动网络。 |
  | kNetworkTypeMobile5G | `6` | 网络连接类型为 5G 移动网络。 |



## PerformanceAlarmMode <span id="performancealarmmode"></span>

类型: `enum`

是否开启发布性能回退

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kPerformanceAlarmModeNormal | `0` | 未开启发布性能回退 |
  | kPerformanceAlarmModeSimulcast | `1` | 已开启发布性能回退 |



## PerformanceAlarmReason <span id="performancealarmreason"></span>

类型: `enum`

[`onPerformanceAlarms`](Electron-event.md#rtcvideocallback-onperformancealarms) 告警的原因

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kPerformanceAlarmReasonBandwidthFallbacked | `0` | 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。 |
  | kPerformanceAlarmReasonBandwidthResumed | `1` | 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。 |
  | kPerformanceAlarmReasonPerformanceFallbacked | `2` | 如果未开启发送性能回退，收到此告警时，意味着性能不足；如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。 |
  | kPerformanceAlarmReasonPerformanceResumed | `3` | 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复； 如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。 |



## SourceWantedData <span id="sourcewanteddata"></span>

类型: `interface`

性能回退相关数据

<p style="font-size: 16px;font-weight: bolder;"> width <span id="sourcewanteddata-width"></span></p> 

类型: number

未开启发布回退时，此值表示推荐的视频输入宽度，当回退模式为大小流模式时，表示当前推流的最大宽度
如果未开启发送性能回退，此值表示推荐的视频输入宽度；
如果开启了发送性能回退，此值表示当前推流的最大宽度。

<p style="font-size: 16px;font-weight: bolder;"> heigth <span id="sourcewanteddata-heigth"></span></p> 

类型: number

如果未开启发送性能回退，此值表示推荐的视频输入高度；
如果开启了发送性能回退，此值表示当前推流的最大高度。

<p style="font-size: 16px;font-weight: bolder;"> frame_rate <span id="sourcewanteddata-frame_rate"></span></p> 

类型: number

如果未开启发送性能回退，此值表示推荐的视频输入帧率，单位 fps；
如果开启了发送性能回退，此值表示当前推流的最大帧率，单位 fps。


## SysStats <span id="sysstats"></span>

类型: `interface`

App 使用的 cpu 和内存信息。
信息由 SDK 周期性（2s）地通过 [onSysStats](Electron-event.md#onsysstats) 回调通知给用户。

<p style="font-size: 16px;font-weight: bolder;"> cpu_cores <span id="sysstats-cpu_cores"></span></p> 

类型: number

当前系统 CPU 核数

<p style="font-size: 16px;font-weight: bolder;"> cpu_app_usage <span id="sysstats-cpu_app_usage"></span></p> 

类型: number

当前应用的 cpu 使用率，取值范围为 [0, 1]。

<p style="font-size: 16px;font-weight: bolder;"> cpu_total_usage <span id="sysstats-cpu_total_usage"></span></p> 

类型: number

当前系统的 cpu 使用率，取值范围为 [0, 1]。

<p style="font-size: 16px;font-weight: bolder;"> memory_usage <span id="sysstats-memory_usage"></span></p> 

类型: number

当前应用的内存使用量（单位 MB）

<p style="font-size: 16px;font-weight: bolder;"> full_memory <span id="sysstats-full_memory"></span></p> 

类型: number

全量内存（单位字节）

<p style="font-size: 16px;font-weight: bolder;"> total_memory_usage <span id="sysstats-total_memory_usage"></span></p> 

类型: number

系统已使用内存（单位字节）

<p style="font-size: 16px;font-weight: bolder;"> free_memory <span id="sysstats-free_memory"></span></p> 

类型: number

空闲可分配内存（单位字节）

<p style="font-size: 16px;font-weight: bolder;"> memory_ratio <span id="sysstats-memory_ratio"></span></p> 

类型: number

当前应用的内存使用率（单位 %）

<p style="font-size: 16px;font-weight: bolder;"> total_memory_ratio <span id="sysstats-total_memory_ratio"></span></p> 

类型: number

系统内存使用率（单位 %）


## RemoteStreamSwitch <span id="remotestreamswitch"></span>

类型: `interface`

流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。

<p style="font-size: 16px;font-weight: bolder;"> uid <span id="remotestreamswitch-uid"></span></p> 

类型: string

订阅的音视频流的发布者的用户 ID。

<p style="font-size: 16px;font-weight: bolder;"> is_screen <span id="remotestreamswitch-is_screen"></span></p> 

类型: boolean

是否是屏幕流。

<p style="font-size: 16px;font-weight: bolder;"> before_video_index <span id="remotestreamswitch-before_video_index"></span></p> 

类型: number

流切换前本地用户订阅的视频流的分辨率对应的索引。

<p style="font-size: 16px;font-weight: bolder;"> after_video_index <span id="remotestreamswitch-after_video_index"></span></p> 

类型: number

流切换后本地用户订阅的视频流的分辨率对应的索引。

<p style="font-size: 16px;font-weight: bolder;"> before_enable <span id="remotestreamswitch-before_enable"></span></p> 

类型: boolean

流切换前是否有视频流。

<p style="font-size: 16px;font-weight: bolder;"> after_enable <span id="remotestreamswitch-after_enable"></span></p> 

类型: boolean

流切换后是否有视频流。

<p style="font-size: 16px;font-weight: bolder;"> reason <span id="remotestreamswitch-reason"></span></p> 

类型: [FallbackOrRecoverReason](#fallbackorrecoverreason)

触发流回退的原因


## FallbackOrRecoverReason <span id="fallbackorrecoverreason"></span>

类型: `enum`

远端订阅流发生回退或恢复的原因

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kFallbackOrRecoverReasonUnknown | `-1` | 其他原因，非带宽和性能原因引起的回退或恢复。默认值 |
  | kFallbackOrRecoverReasonSubscribeFallbackByBandwidth | `0` | 由带宽不足导致的订阅端音视频流回退。 |
  | kFallbackOrRecoverReasonSubscribeFallbackByPerformance | `1` | 由性能不足导致的订阅端音视频流回退。 |
  | kFallbackOrRecoverReasonSubscribeRecoverByBandwidth | `2` | 由带宽恢复导致的订阅端音视频流恢复。 |
  | kFallbackOrRecoverReasonSubscribeRecoverByPerformance | `3` | 由性能恢复导致的订阅端音视频流恢复。 |
  | kFallbackOrRecoverReasonPublishFallbackByBandwidth | `4` | 由带宽不足导致的发布端音视频流回退。 |
  | kFallbackOrRecoverReasonPublishFallbackByPerformance | `5` | 由性能不足导致的发布端音视频流回退。 |
  | kFallbackOrRecoverReasonPublishRecoverByBandwidth | `6` | 由带宽恢复导致的发布端音视频流恢复。 |
  | kFallbackOrRecoverReasonPublishRecoverByPerformance | `7` | 由性能恢复导致的发布端音视频流恢复。 |



## LocalAudioStreamState <span id="localaudiostreamstate"></span>

类型: `enum`

本地音频流状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLocalAudioStreamStateStopped | `0` | 本地音频默认初始状态。<br>麦克风停止工作时回调该状态，对应错误码 kLocalAudioStreamErrorOk |
  | kLocalAudioStreamStateRecording | `1` | 本地音频录制设备启动成功。<br>采集到音频首帧时回调该状态，对应错误码 kLocalAudioStreamErrorOk |
  | kLocalAudioStreamStateEncoding | `2` | 本地音频首帧编码成功。<br>音频首帧编码成功时回调该状态，对应错误码 kLocalAudioStreamErrorOk |
  | kLocalAudioStreamStateFailed | `3` | 本地音频启动失败，在以下时机回调该状态：<br>+本地录音设备启动失败，对应错误码 kLocalAudioStreamErrorRecordFailure<br>+检测到没有录音设备权限，对应错误码 kLocalAudioStreamErrorDeviceNoPermission<br>+音频编码失败，对应错误码 kLocalAudioStreamErrorEncodeFailure |
  | kLocalAudioStreamStateMute | `4` | 本地音频静音成功后回调该状态。<br>调用 [`setAudioCaptureDeviceMute`](Electron-api#rtcvideo-setaudiocapturedevicemute) 成功后回调，对应错误码 [`LocalAudioStreamError`](Electron-errorcode.md#localaudiostreamerror) 中的 kLocalAudioStreamErrorOk 。 |
  | kLocalAudioStreamStateUnmute | `5` | 本地音频解除静音成功后回调该状态。<br>调用 [`setAudioCaptureDeviceMute`](Electron-api#rtcvideo-setaudiocapturedevicemute) 成功后回调，对应错误码 [`LocalAudioStreamError`](Electron-errorcode.md#localaudiostreamerror) 中的 kLocalAudioStreamErrorOk 。 |



## RemoteAudioState <span id="remoteaudiostate"></span>

类型: `enum`

远端音频流状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRemoteAudioStateStopped | `0` | 不接收远端音频流。 |
  | kRemoteAudioStateStarting | `1` |  |
  | kRemoteAudioStateDecoding | `2` |  |
  | kRemoteAudioStateFrozen | `3` | 远端音频流卡顿。 |



## RemoteAudioStateChangeReason <span id="remoteaudiostatechangereason"></span>

类型: `enum`

接收远端音频流状态改变的原因。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRemoteAudioStateChangeReasonInternal | `0` | 内部原因 |
  | kRemoteAudioStateChangeReasonNetworkCongestion | `1` | 网络阻塞 |
  | kRemoteAudioStateChangeReasonNetworkRecovery | `2` | 网络恢复正常 |
  | kRemoteAudioStateChangeReasonLocalMuted | `3` | 本地用户停止接收远端音频流 |
  | kRemoteAudioStateChangeReasonLocalUnmuted | `4` | 本地用户恢复接收远端音频流 |
  | kRemoteAudioStateChangeReasonRemoteMuted | `5` | 远端用户停止发送音频流 |
  | kRemoteAudioStateChangeReasonRemoteUnmuted | `6` | 远端用户恢复发送音频流 |
  | kRemoteAudioStateChangeReasonRemoteOffline | `7` | 远端用户离开房间 |



## LocalVideoStreamState <span id="localvideostreamstate"></span>

类型: `enum`

本地视频流状态

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLocalVideoStreamStateStopped | `0` | 本地视频采集停止状态 |
  | kLocalVideoStreamStateRecording | `1` | 本地视频采集设备启动成功 |
  | kLocalVideoStreamStateEncoding | `2` | 本地视频采集后，首帧编码成功 |
  | kLocalVideoStreamStateFailed | `3` | 本地视频采集设备启动失败 |



## RemoteVideoState <span id="remotevideostate"></span>

类型: `enum`

远端视频流状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRemoteVideoStateStopped | `0` | 远端视频流默认初始状态，视频尚未开始播放。 |
  | kRemoteVideoStateStarting | `1` | 本地用户已接收远端视频流首包。 |
  | kRemoteVideoStateDecoding | `2` | 远端视频流正在解码，正常播放。 |
  | kRemoteVideoStateFrozen | `3` | 远端视频流卡顿，可能有网络等原因。 |
  | kRemoteVideoStateFailed | `4` | 远端视频流播放失败。 |



## RemoteVideoStateChangeReason <span id="remotevideostatechangereason"></span>

类型: `enum`

远端视频流状态改变的原因

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kRemoteVideoStateChangeReasonInternal | `0` | 内部原因 |
  | kRemoteVideoStateChangeReasonNetworkCongestion | `1` | 网络阻塞 |
  | kRemoteVideoStateChangeReasonNetworkRecovery | `2` | 网络恢复正常 |
  | kRemoteVideoStateChangeReasonLocalMuted | `3` | 本地用户停止接收远端视频流或本地用户禁用视频模块 |
  | kRemoteVideoStateChangeReasonLocalUnmuted | `4` | 本地用户恢复接收远端视频流或本地用户启用视频模块 |
  | kRemoteVideoStateChangeReasonRemoteMuted | `5` | 远端用户停止发送视频流或远端用户禁用视频模块 |
  | kRemoteVideoStateChangeReasonRemoteUnmuted | `6` | 远端用户恢复发送视频流或远端用户启用视频模块 |
  | kRemoteVideoStateChangeReasonRemoteOffline | `7` | 远端用户离开频道。<br>状态转换参考 onStreamRemove(Electron-event#onstreamremove) |



## SingleStreamPushEvent <span id="singlestreampushevent"></span>

类型: `enum`

转推直播事件

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kSingleStreamPushEventStart | `1` | 开始推流。 |
  | kSingleStreamPushEventSuccess | `2` | 推流成功。 |
  | kSingleStreamPushEventFailed | `3` | 推流失败。 |
  | kSingleStreamPushEventStop | `4` | 停止推流。 |
  | kSingleStreamPushEventTimeout | `5` | 单流转推直播任务处理超时，请检查网络状态并重试。 |
  | kSingleStreamPushEventParamError | `6` | 参数错误。 |



## RecordingInfo <span id="recordinginfo"></span>

类型: `interface`

本地录制的详细信息

<p style="font-size: 16px;font-weight: bolder;"> file_path <span id="recordinginfo-file_path"></span></p> 

类型: string

录制文件的绝对路径，包含文件名和文件后缀

<p style="font-size: 16px;font-weight: bolder;"> video_codec_type <span id="recordinginfo-video_codec_type"></span></p> 

类型: [VideoCodecType](#videocodectype)

录制文件的视频编码类型

<p style="font-size: 16px;font-weight: bolder;"> width <span id="recordinginfo-width"></span></p> 

类型: number

录制视频的宽，单位：像素。纯音频录制请忽略该字段

<p style="font-size: 16px;font-weight: bolder;"> height <span id="recordinginfo-height"></span></p> 

类型: number

录制视频的高，单位：像素。纯音频录制请忽略该字段


## RecordingProgress <span id="recordingprogress"></span>

类型: `interface`

本地录制进度

<p style="font-size: 16px;font-weight: bolder;"> duration <span id="recordingprogress-duration"></span></p> 

类型: number

当前文件的累计录制时长，单位：毫秒

<p style="font-size: 16px;font-weight: bolder;"> file_size <span id="recordingprogress-file_size"></span></p> 

类型: number

当前录制文件的大小，单位：byte


## LogoutReason <span id="logoutreason"></span>

类型: `enum`

用户登出的原因

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kLogoutReasonLogout | `0` | 用户主动退出<br>用户调用 logout 接口登出，或者销毁引擎登出。 |
  | kLogoutReasonDuplicateLogin | `1` | 用户被动退出<br>另一个用户以相同 UserId 进行了 login，导致本端用户被踢出。 |



## LocalAudioPropertiesInfo <span id="localaudiopropertiesinfo"></span>

类型: `interface`

本地音频属性信息

<p style="font-size: 16px;font-weight: bolder;"> stream_index <span id="localaudiopropertiesinfo-stream_index"></span></p> 

类型: [StreamIndex](#streamindex)

流属性，主流或屏幕流。

<p style="font-size: 16px;font-weight: bolder;"> audio_properties_info <span id="localaudiopropertiesinfo-audio_properties_info"></span></p> 

类型: [AudioPropertiesInfo](#audiopropertiesinfo)

音频属性信息，


## AudioPropertiesInfo <span id="audiopropertiesinfo"></span>

类型: `interface`

音频属性信息

<p style="font-size: 16px;font-weight: bolder;"> linear_volume <span id="audiopropertiesinfo-linear_volume"></span></p> 

类型: number

线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。

- [0, 25]: 无声
- [26, 75]: 低音量
- [76, 204]: 中音量
- [205, 255]: 高音量

<p style="font-size: 16px;font-weight: bolder;"> nonlinear_volume <span id="audiopropertiesinfo-nonlinear_volume"></span></p> 

类型: number

非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。

- [-127, -60]: 无声
- [-59, -40]: 低音量
- [-39, -20]: 中音量
- [-19, 0]: 高音量

<p style="font-size: 16px;font-weight: bolder;"> vad <span id="audiopropertiesinfo-vad"></span></p> 

类型: number

人声检测（VAD）结果

- 1: 检测到人声。
- 0: 未检测到人声。
- -1: 未开启 VAD。

<p style="font-size: 16px;font-weight: bolder;"> spectrum <span id="audiopropertiesinfo-spectrum"></span></p> 

类型: number[]

频谱数组。默认长度为 257。

<p style="font-size: 16px;font-weight: bolder;"> voice_pitch <span id="audiopropertiesinfo-voice_pitch"></span></p> 

类型: number

本地用户的人声基频，单位为赫兹。 
同时满足以下两个条件时，返回的值为本地用户的人声基频：

+ 调用 [`enableAudioPropertiesReport`](Electron-api.md#rtcvideo-enableaudiopropertiesreport)，并设置参数 `enable_voice_pitch` 的值为 `true`。 
+ 本地采集的音频中包含本地用户的人声。 
其他情况下返回 0。


## RemoteAudioPropertiesInfo <span id="remoteaudiopropertiesinfo"></span>

类型: `interface`

远端音频属性信息

<p style="font-size: 16px;font-weight: bolder;"> stream_key <span id="remoteaudiopropertiesinfo-stream_key"></span></p> 

类型: [RemoteStreamKey](#remotestreamkey)

流属性，主流或屏幕流。

<p style="font-size: 16px;font-weight: bolder;"> audio_properties_info <span id="remoteaudiopropertiesinfo-audio_properties_info"></span></p> 

类型: [AudioPropertiesInfo](#audiopropertiesinfo)

音频属性信息


## EchoTestResult <span id="echotestresult"></span>

类型: `enum`

音视频回路测试结果

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kTestSuccess | `0` | 接收到采集的音视频的回放，通话回路检测成功 |
  | kTestTimeout | `1` | 测试超过 60s 仍未完成，已自动停止 |
  | kTestIntervalShort | `2` | 上一次测试结束和下一次测试开始之间的时间间隔少于 5s |
  | kAudioDeviceError | `3` | 音频采集异常 |
  | kVideoDeviceError | `4` | 视频采集异常 |
  | kAudioReceiveError | `5` | 音频接收异常 |
  | kVideoReceiveError | `6` | 视频接收异常 |
  | kInternalError | `7` | 内部错误，不可恢复 |



## MediaDeviceWarning <span id="mediadevicewarning"></span>

类型: `enum`

媒体设备警告

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kMediaDeviceWarningOK | `0` | 无警告 |
  | kMediaDeviceWarningOperationDenied | `1` | 非法设备操作。在使用外部设备时，调用了 SDK 内部设备 API。 |
  | kMediaDeviceWarningCaptureSilence | `2` | 采集静音。 |
  | kMediaDeviceWarningDetectLeakEcho | `11` | 通话中出现回声现象。<br>当 [`RoomProfileType`](Electron-keytype.md#roomprofiletype) 为 `kRoomProfileTypeMeeting` 和<br>`kRoomProfileTypeMeetingRoom`，且 AEC 关闭时，SDK 自动启动回声检测，如果检测到回声问题，将通过<br>`onAudioDeviceWarning` 返回本枚举值。 |
  | kMediaDeviceWarningCaptureDetectHowling | `16` | 啸叫。触发该回调的情况如下：1）不支持啸叫抑制的房间模式下，检测到啸叫；2）支持啸叫抑制的房间模式下，检测到未被抑制的啸叫。<br>仅 `kRoomProfileTypeCommunication`、`kRoomProfileTypeMeeting`、`kRoomProfileTypeMeetingRoom`<br>三种房间模式支持啸叫抑制。 建议提醒用户检查客户端的距离或将麦克风和扬声器调至静音。 |



## SEIStreamEventType <span id="seistreameventtype"></span>

类型: `enum`

黑帧视频流状态

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kSEIStreamEventTypeStreamAdd | `0` | 远端用户发布黑帧视频流。<br>纯语音通话场景下，远端用户调用 [`sendSEIMessage`](Electron-api.md#rtcvideo-sendseimessage) 发送 SEI 数据时，SDK 会自动发布一路黑帧视频流，并触发该回调。 |
  | kSEIStreamEventTypeStreamRemove | `1` | 远端黑帧视频流移除。该回调的触发时机包括：<br>+ 远端用户开启摄像头采集，由语音通话切换至视频通话，黑帧视频流停止发布；<br>+ 远端用户调用 [`sendSEIMessage`](Electron-api.md#rtcvideo-sendseimessage) 后 1min 内未有 SEI 数据发送，黑帧视频流停止发布；<br>+ 远端用户切换至自定义视频采集时，黑帧视频流停止发布。 |



## PlayerState <span id="playerstate"></span>

类型: `enum`

播放状态。

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kPlayerStateIdle | `0` | 播放未启动 |
  | kPlayerStatePreloaded | `1` | 已加载 |
  | kPlayerStateOpened | `2` | 播放文件已打开 |
  | kPlayerStatePlaying | `3` | 正在播放 |
  | kPlayerStatePaused | `4` | 播放已暂停 |
  | kPlayerStateStopped | `5` | 播放已停止 |
  | kPlayerStateFailed | `6` | 播放失败 |
  | kPlayerStateFinished | `7` | 播放结束 |


## ReturnStatus <span id="returnstatus"></span>

类型: `enum`

- **成员**

  | 属性 | 值 | 描述 |
  | :-- | :-- | :-- |
  | kReturnStatusSuccess | `0` | 成功。 |
  | kReturnStatusFailure | `-1` | 失败。 |
  | kReturnStatusParameterErr | `-2` | 参数错误。 |
  | kReturnStatusWrongState | `-3` | 接口状态错误。 |
  | kReturnStatusHasInRoom | `-4` | 失败，用户已在房间内。 |
  | kReturnStatusHasInLogin | `-5` | 失败，用户已登录。 |
  | kReturnStatusHasInEchoTest | `-6` | 失败，用户已经在进行通话回路测试中。 |
  | kReturnStatusNeitherVideoNorAudio | `-7` | 失败，音视频均未采集。 |
  | kReturnStatusRoomIdInUse | `-8` | 失败，该 roomId 已被使用。 |
  | kReturnStatusScreenNotSupport | `-9` | 失败，屏幕流不支持。 |
  | kReturnStatusNotSupport | `-10` | 失败，不支持该操作。 |
  | kReturnStatusResourceOverflow | `-11` | 失败，资源已占用。 |
  | kReturnStatusVideoNotSupport | `-12` | 失败，不支持视频接口调用。 |
  | kReturnStatusAudioNoFrame | `-101` | 失败，没有音频帧。 |
  | kReturnStatusAudioNotImplemented | `-102` | 失败，未实现。 |
  | kReturnStatusAudioNoPermission | `-103` | 失败，采集设备无麦克风权限，尝试初始化设备失败。 |
  | kReturnStatusAudioDeviceNotExists | `-104` | 失败，设备不存在。当前没有设备或设备被移除时返回该值。 |
  | kReturnStatusAudioDeviceFormatNotSupport | `-105` | 失败，设备音频格式不支持。 |
  | kReturnStatusAudioDeviceNoDevice | `-106` | 失败，系统无可用设备。 |
  | kReturnStatusAudioDeviceCannotUse | `-107` | 失败，当前设备不可用，需更换设备。 |
  | kReturnStatusAudioDeviceInitFailed | `-108` | 系统错误，设备初始化失败。 |
  | kReturnStatusAudioDeviceStartFailed | `-109` | 系统错误，设备开启失败。 |
  | kReturnStatusNativeInvalid | `-201` | 失败，无效对象。 |
  | kReturnStatusVideoTimeStampWarning | `-202` | 警告。推送视频帧到 RTC SDK 时，相邻视频帧的时间戳差异应当和推帧操作的间隔相同。如果不同，会收到此警告。 |