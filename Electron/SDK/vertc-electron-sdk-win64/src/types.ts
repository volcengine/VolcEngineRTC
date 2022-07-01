//
//  types.ts

//////////////////////////////////////////////////////////////////////////
// VRTCEngine here
export enum RenderMode {
  FIT = 1,
  HIDDEN = 2
}
/**
 * @brief 本地渲染选项
 */
export interface RenderOptions {
  /**
   * @brief 渲染模式
   */
  renderMode: RenderMode,
  /**
   * @brief 是否镜像渲染
   */
  mirror: boolean
}

/**
 * @type keytype
 * @brief 用户角色。
 *        房间模式为直播、游戏、云游戏模式时的用户角色。
 */
export enum ClientRoleType {
  /**
   * @brief 主播角色，用户既可以发布流到房间中，也可以从房间中订阅流。
   */
  CLIENT_ROLE_BROADCASTER = 1,
  /**
   * @brief 观众角色，用户只能从房间中订阅流，不能向房间中发布流，房间中的其他用户可以感知到该用户在房间中。
   */
  CLIENT_ROLE_AUDIENCE = 2,
  /**
   * @brief
   * 静默观众模式，除了满足观众角色的限制外，房间中的其他用户无法感知到该用户在房间中，即该用户加入退出房间和更新用户属性等行为不会通知给房间中的其他用户。
   */
  CLIENT_ROLE_SILENT_AUDIENCE = 3,
};

/**
 * @type keytype
 * @brief 房间模式
 *        房间使用的场景模式。
 */
export enum ChannelProfileType {
  /**
   * @brief 通信模式。该房间模式下，房间内所有用户都可以发布和订阅流。适用于 IM 场景。
   */
  CHANNEL_PROFILE_COMMUNICATION = 0,
  /**
   * @brief 直播模式。该房间模式下，用户有主播、观众、静默观众三种可选角色，可以通过调用方法 setClientRole{@link 85532#SetClientRole} 设置。主播可以发布和订阅流，观众和静默观众只能订阅流。适用于直播、教育大班课等场景。
   */
  CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
  /**
   * @brief 游戏模式。该房间模式下，用户角色同直播模式。适用于游戏场景。
   */
  CHANNEL_PROFILE_GAME = 2,
  /**
   * @brief 云游戏模式。该房间模式下，用户角色同直播模式。同时 SDK 会开启 DataChannel （详见方法 sendDataChannnelMessage{@link 85532#SendDataChannnelMessage} ）功能并使用低延时设置。适用于云游戏场景。
   */
  CHANNEL_PROFILE_CLOUD_GAME = 3,
};

/**
 * @hidden
 */
export enum SubscribeState {
  /**
   * @brief 订阅流成功
   */
  SUB_STATE_SUCCESS,
  /**
   * @hidden
   */
  SUB_STATE_FAILED_NOT_IN_ROOM,
  /**
   * @brief 没有找到流
   */
  SUB_STATE_FAILED_STREAM_NOT_FOUND,
};

/**
 * @type keytype
 * @brief 订阅流配置参数。
 *        用户调用 SubscribeUserStream{@link #SubscribeUserStream} 方法手动订阅音视频流或更新订阅参数时，传入订阅流配置参数。
 */
export interface SubscribeConfig {
  /**
   * @brief 是否是屏幕流。
   */
  isScreen: boolean,
  /**
   * @brief 是否订阅视频。
   */
  subVideo: boolean,
  /**
   * @brief 是否订阅音频。
   */
  subAudio: boolean,
  /**
   * @brief 订阅的视频流分辨率下标。
   *        视频流中含多个分辨率的情况下，标识订阅第几个的视频分辨率。如果视频流中仅含一个分辨率，则为 0。
   */
  videoIndex: number,
  /**
   * @brief 远端用户的需求优先级，0 为默认值。
   */
  priority: number
}


export interface Rectangle {
  /**
   * @brief 矩形左上角x坐标
   */
  x: number,
  /**
   * @brief 矩形左上角y坐标
   */
  y: number,
  /**
   * @brief 矩形宽度
   */
  width: number,
  /**
   * @brief 矩形高度
   */
  height: number
};

/**
 * @type keytype
 * @brief 高亮边框标识屏幕共享指定区域
 */
export interface HighlightConfig {
  /**
   * @brief 是否显示高亮边框，默认显示。
   */
  enableHighlight: boolean,
  /**
   * @brief 边框的颜色, 颜色格式为十六进制 ARGB:  0xAARRGGBB, 默认为 0xFF29CCA3
   */
  borderColor: number,
  /**
   * @brief 边框的宽度, 默认为: 4
   */
  borderWidth: number
};

/**
 * @type keytype
 * @brief 屏幕共享的编码参数配置
 */
export interface DesktopCaptureParameters {
  /**
   * @brief 屏幕采集编码最大宽度
   */
  maxWidth: number,
  /**
   * @brief 屏幕采集编码最大高度
   */
  maxHeight: number,
  /**
   * @brief 屏幕采集编码帧率, 单位 fps
   */
  frameRate: number,
  /**
   * @brief 屏幕采集编码码率, -1 为自动码率, SDK 会根据宽高信息选择合适的码率，单位 kbps
   */
  bitrate: number,
  /**
   * @brief 是否捕获鼠标光标
   */
  captureMouseCursor: boolean,

  // source id from 
  excludedWindowList: [],

  highlightConfig: HighlightConfig
};



export enum ScaleMode {
  /**
   * @brief 自由模式，默认使用FitWithCropping模式
   */
  Auto = 0,
  /**
   * @brief 视频尺寸进行缩放和拉伸以充满显示视窗
   */
  Stretch = 1,
  /**
   * @brief
   * 优先保证视窗被填满。视频尺寸等比缩放，直至整个视窗被视频填满。如果视频长宽与显示窗口不同，多出的视频将被截掉
   */
  FitWithCropping = 2,
  /**
   * @brief
   * 优先保证视频内容全部显示。视频尺寸等比缩放，直至视频窗口的一边与视窗边框对齐。如果视频长宽与显示窗口不同，视窗上未被填满的区域将被涂黑
   */
  FitWithFilling = 3,
}

/**
 * @type keytype
 * @brief 视频的编码类型
 */
export enum VideoCodecType {
  /**
   * @brief 未知类型
   */
  kVideoCodecUnknown = 0,
  /**
   * @brief 标准H264
   */
  kVideoCodecH264 = 1,
  /**
   * @brief 标准ByteVC1
   */
  kVideoCodecByteVC1 = 2,
};

/**
 * @type keytype
 * @brief 视频编码模式
 */
export enum CodecMode {
  /**
   * @brief 自动选择
   */
  AutoMode = 0,
  /**
   * @brief 硬编码
   */
  HardwareMode,
  /**
   * @brief 软编码
   */
  SoftwareMode,
};

/**
 * @type keytype
 * @brief 视频编码质量偏好
 *      网络不好时的编码策略
 */
export enum EncodePreference {
  /**
   * @brief 关闭
   */
  EncodePreferenceDisabled = 0,
  /**
   * @brief 保持帧率
   */
  EncodePreferenceFramerate,
  /**
   * @brief 保持画质
   */
  EncodePreferenceQuality,
  /**
   * @brief 平衡模式
   */
  EncodePreferenceBalance,
};

export const SEND_KBPS_AUTO_CALCULATE = -1;
export const SEND_KBPS_DISABLE_VIDEO_SEND = 0;

/**
 * @type keytype
 * @brief 视频属性
 */
export interface VideoSolution {
  /**
   * @brief 视频的宽
   */
  width: number,
  /**
   * @brief 视频的高
   */
  height: number,
  /**
   * @brief 画面每秒传输帧数
   */
  fps: number,
  /**
   * @brief 最大发送编码码率（kbps），建议使用自动码率。<li>-1: 自动码率</li><li>0: 不开启上限</li><li>>0: 填写预估码率<li>
   */
  maxSendKbps: number,
  /**
   * @brief 缩放模式，详见 ScaleMode{@link #ScaleMode}
   */
  scaleMode: ScaleMode,
  /**
   * @brief 视频编码质量偏好，详见 EncodePreference{@link #EncodePreference}
   */
  encodePreference: EncodePreference
};

/**
 * @type keytype
 * @brief 视频属性
 */
export interface VideoSolutionDescription {
  /**
   * @brief 视频的宽
   */
  width: number,
  /**
   * @brief 视频的高
   */
  height: number,
  /**
   * @brief 画面每秒传输帧数
   */
  fps: number,
  /**
   * @brief 最大发送速率（千比特每秒）
   * {@link #SEND_KBPS_AUTO_CALCULATE} means auto calculate
   * {@link #SEND_KBPS_DISABLE_VIDEO_SEND} means disable send video
   */
  maxSendKbps: number,
  /**
   * @brief 缩放模式，详见 ScaleMode{@link #ScaleMode}
   */
  scaleMode: ScaleMode,
  /**
   * @brief 编码类型，详见 VideoCodecType{@link #VideoCodecType}
   */
  codecName: VideoCodecType,
  /**
   * @brief 编码模式，详见 CodecMode{@link #CodecMode}
   */
  codecMode: CodecMode,
  /**
   * @brief 视频编码质量偏好，详见 EncodePreference{@link #EncodePreference}
   */
  encodePreference: EncodePreference
};

/**
 * @module
 */
export interface ByteStream {
  /**
   * @brief 用户 ID
   */
  userId: string,
  /**
   * @brief 是否屏幕共享流
   */
  isScreen: boolean,
  /**
   * @brief 是否包含视频
   */
  hasVideo: boolean,
  /**
   * @brief 是否包含音频
   */
  hasAudio: boolean,
  /**
   * @brief 视频分辨率描述
   */
  profiles: VideoSolutionDescription[]
};

export interface AudioVolumeInfo {
  userId: string,
  volume: number
}

/**
 * @type keytype
 * @brief 通话相关的统计信息
 */
 export interface RtcRoomStats {
  /**
   * @brief 当前应用的上行丢包率，取值范围为 [0, 1]。
   */
  txLostrate: number;
  /**
   * @brief 当前应用的下行丢包率，取值范围为 [0, 1]。
   */
  rxLostrate: number;
  /**
   * @brief 客户端到服务端数据传输的往返时延（单位 ms）
   */
  rtt: number;
  /**
   * @brief 通话时长，单位为秒，累计值
   */
  duration: number;
  /**
   * @brief 本地用户的总发送字节数 (bytes)，累计值
   */
  tx_bytes: number;
  /**
   * @brief 本地用户的总接收字节数 (bytes)，累计值
   */
  rx_bytes: number;
  /**
   * @brief 发送码率 (kbps)，获取该数据时的瞬时值
   */
  tx_kbitrate: number;
  /**
   * @brief 接收码率 (kbps)，获取该数据时的瞬时值
   */
  rx_kbitrate: number;
  /**
   * @brief 音频接收码率 (kbps)，获取该数据时的瞬时值
   */
  rx_audio_kbitrate: number;
  /**
   * @brief 音频发送码率 (kbps)，获取该数据时的瞬时值
   */
  tx_audio_kbitrate: number;
  /**
   * @brief 视频接收码率 (kbps)，获取该数据时的瞬时值
   */
  rx_video_kbitrate: number;
  /**
   * @brief 视频发送码率 (kbps)，获取该数据时的瞬时值
   */
  tx_video_kbitrate: number;
  /**
   * @brief 当前房间内的用户人数
   */
  user_count: number;
  /**
   * @hidden
   * @brief 当前应用程序的 CPU 使用率（%），暂未被使用
   */
  cpu_app_usage: number;
  /**
   * @hidden
   * @brief 当前系统的 CPU 使用率（%），暂未被使用
   */
  cpu_total_usage: number;
};

/**
 * @brief 视频数据
 */
export interface VideoFrame {
  /**
   * @brief 频道 ID
   */
  channelId: string,
  /**
   * @brief 用户 ID
   */
  userId: string,
  /**
   * @brief 视频数据缓冲区 Y
   */
  planeY: Uint8Array,
  /**
   * @brief 视频数据缓冲区 U
   */
  planeU: Uint8Array,
  /**
   * @brief 视频数据缓冲区 V
   */
  planeV: Uint8Array,
  /**
   * @brief 视频分辨率宽度，单位：像素
   */
  width: number,
  /**
   * @brief 视频分辨率高度，单位：像素
   */
  height: number,
  /**
   * @brief 视频数据缓冲区 Y 大小
   */
  planeSizeY: number,
  /**
   * @brief 视频数据缓冲区 U 大小
   */
  planeSizeU: number,
  /**
   * @brief 视频数据缓冲区 V 大小
   */
  planeSizeV: number,
  /**
   * @brief 视频帧数据格式
   */
  format: number,
  /**
   * @brief 视频帧旋转角度
   */
  rotation: number
}

export interface AudioFrame {
   /**
     * @brief 音频帧类型
     */
    type: AudioFrameType
    /**
     * @brief 音频采样点数量
     */
    samples: number;

    /**
     * @brief 音频通道数
     */
    channels: number;

    /**
     * @brief 音频采样率
     */
    samples_per_sec: number;

    /**
     * @brief 音频数据内存地址
     */
    buffer : Uint8Array;

    /**
     * @brief 渲染时间
     */
    render_time_ms: number;
}


/**
 * @type keytype
 * @region 音频管理
 * @brief 音频帧类型
 */
 export enum AudioFrameType {
  /**
   * @brief PCM 16bit
   */
  kFrameTypePCM16 = 0
};

/**
* @type keytype
* @brief 音频声道。
*/
export enum AudioChannel {
   /**
    * @brief 自动声道，适用于从 SDK 获取音频数据，使用 SDK 内部处理的声道，不经过 resample。  <br>
    *        当你需要从 SDK 获取音频数据时，若对声道没有强依赖，建议设置成该值，可以通过避免 resample 带来一些性能优化。
    */
   kAudioChannelAuto = -1,
   /**
    * @brief 单声道
    */
   kAudioChannelMono = 1,
   /**
    * @brief 双声道
    */
   kAudioChannelStereo = 2
};

/**
 * @type keytype
 * @brief 音频采样率，单位为 HZ。 <br>
 */
 export enum AudioSampleRate {
  /**
   * @brief 自动采样率，适用于从 SDK 获取音频数据，使用 SDK 内部处理的采样率，不经过 resample。  <br>
   *        当你需要从 SDK 获取音频数据时，若对采样率没有强依赖，建议设置成该值，可以通过避免 resample 带来一些性能优化。
   */
  kAudioSampleRateAuto = -1,
  /**
   * @brief 8000 采样率
   */
  kAudioSampleRate8000 = 8000,
  /**
   * @brief 16000 采样率
   */
  kAudioSampleRate16000 = 16000,
  /**
   * @brief 32000 采样率
   */
  kAudioSampleRate32000 = 32000,
  /**
   * @brief 44100 采样率
   */
  kAudioSampleRate44100 = 44100,
  /**
   * @brief 48000 采样率
   */
  kAudioSampleRate48000 = 48000
};

/**
 * @type keytype
 * @brief SDK 与信令服务器连接状态。
 */
 export enum ConnectionState {
  /**
   * @brief 连接断开。
   */
  kConnectionStateDisconnected = 1,
  /**
   * @brief 首次连接，正在连接中。
   */
  kConnectionStateConnecting = 2,
  /**
   * @brief 首次连接成功。
   */
  kConnectionStateConnected = 3,
  /**
   * @brief 连接断开后重新连接中。
   */
  kConnectionStateReconnecting = 4,
  /**
   * @brief 连接断开后重连成功。
   */
  kConnectionStateReconnected = 5,
  /**
   * @brief 网络连接断开超过 10 秒，仍然会继续重连。
   */
  kConnectionStateLost = 6,
};


/**
 * @hidden
 * @type keytype
 * @brief 用户离线原因。<br>
 *        房间内的远端用户离开房间时，本端用户会收到 OnUserOffline{@link #OnUserOffline} 回调通知，此枚举类型为回调的用户离线原因。
 */
export enum UserOfflineReasonType {
  /**
   * @brief 用户主动离开。
   */
  USER_OFFLINE_QUIT = 0,
  /**
   * @brief 用户掉线。
   */
  USER_OFFLINE_DROPPED = 1,
  /**
   * @hidden
   */
  USER_OFFLINE_BECOME_AUDIENCE = 2,
};

/**
 * @type keytype
 * @brief 当前媒体设备类型
 */
 export enum MediaDeviceType {
  /**
   * @brief 音频渲染设备类型
   */
  kMediaDeviceTypeAudioRenderDevice = 0,
  /**
   * @brief 音频采集设备类型
   */
  kMediaDeviceTypeAudioCaptureDevice = 1,
  /**
   *@hidden
   *@brief 视频渲染设备类型，该类型暂无使用
   */
  kMediaDeviceTypeVideoRenderDevice = 2,
  /**
   *@brief 视频采集设备类型
   */
  kMediaDeviceTypeVideoCaptureDevice = 3
};
/**
 * @type keytype
 * @brief 媒体设备事件类型
 */
export enum MediaDeviceNotification {
  /**
   *@brief 设备已就绪
   */
  kMediaDeviceNotificationActive = 1,
  /**
   *@brief 设备被禁用
   */
  kMediaDeviceNotificationDisabled = 2,
  /**
   *@brief 没有此设备
   */
  kMediaDeviceNotificationNotPresent = 4,
  /**
   *@brief 设备被拔出
   */
  kMediaDeviceNotificationUnplugged = 8
};


/**
 * @type keytype
 * @brief 媒体设备状态类型
 */
 export enum MediaDeviceState {
  /**
   *@brief 设备已开启
   */
  kMediaDeviceStateStarted = 1,
  /**
   *@brief 设备已停止
   */
  kMediaDeviceStateStopped = 2,
  /**
   *@brief 设备运行时错误
   */
  kMediaDeviceStateRuntimeError = 3,
  /**
   *@brief 设备已插入
   */
  kMediaDeviceStateAdded = 10,
  /**
   *@brief 设备被移除
   */
  kMediaDeviceStateRemoved = 11
};
/**
 * @type keytype
 * @brief 屏幕采集对象的类型
 */
export enum ScreenCaptureSourceType {
    /**
     * @brief 类型未知
     */
    kScreenCaptureSourceTypeUnknown,
    /**
     * @brief 应用程序的窗口
     */
    kScreenCaptureSourceTypeWindow,
    /**
     * @brief 桌面
     */
    kScreenCaptureSourceTypeScreen
};

export enum RemoteUserPriority {
  /**
     * @brief 用户优先级为低（默认值）
     */
   kRemoteUserPriorityLow = 0,
   /**
    * @brief 用户优先级为正常
    */
   kRemoteUserPriorityMedium = 100,
   /**
    * @brief 用户优先级为高
    */
   kRemoteUserPriorityHigh = 200,
}

/**
 * @brief 待共享的屏幕源信息
 *        [startScreenVideoCapture](../85532/#startscreenvideocapture) 接口的其中一个参数类型
 */
export interface ScreenCaptureSourceInfo {
    /**
     * @brief 屏幕源类型
     */
    type: ScreenCaptureSourceType,
    /**
     * @brief 屏幕源 ID
     */
    source_id: number,
    /**
     * @brief 屏幕源名称
     */
    source_name: string
};

/**
 * @brief 屏幕共享对象
 *        调用 [getThumbnail](../85532/#getthumbnail) 后返回本对象
 */
export interface ThumbnailInfo {
  /**
   * @brief 宽度，单位：像素
   */
  width: number,
  /**
   * @brief 高度，单位：像素
   */
  height: number,
  /**
   * @brief 数据，采用 base64 编码的 png 字符串
   */
  // base64 encode png string
  data: string
}

/** {zh}
 * @brief 转推直播参数
 */
export interface TranscoderParam {
  /**
   * @brief 当前房间 ID
   */
  roomID: string,
  /**
   * @brief 当前用户 ID
   */
  userID: string,
  /**
   * @brief 背景图片地址
   */
  uri: string,
  /**
   * @brief 音频参数
   */
  audioParam: TranscoderAudioParam,
  /**
   * @brief 视频参数
   */
  videoParam: TranscoderVideoParam,
  /**
   * @brief 布局设置
   */
  layoutRegions: TranscoderLayoutRegion[],
  /**
   * @brief 背景颜色
   */
  backgroundColor: string,
  /**
   * @brief 设置透传的 App 数据
   */
  appData: string,
}

/**
 * @brief 音频参数
 */
export interface TranscoderAudioParam {
  /**
   * @brief 采样率，单位 Hz，包括 16k, 32k, 44.1k, 48k
   */
  i32_sample_rate: number,
  /**
   * @brief 声道数
   */
  i32_channel_num: number,
  /**
   * @brief 编码码率，单位 Kbps，包括 16kbsp, 32kbps, 64kbps
   */
  i32_bitrate_kbps: number,
  /**
   * @brief 音频编码 AAC 等级
   */
  audio_codec_profile: TranscoderAudioCodecProfile
}

/**
 * @brief 视频参数
 */
export interface TranscoderVideoParam {
  /**
   * @brief 宽度
   */
  i32_width: number,
  /**
   * @brief 高度
   */
  i32_height: number,
  /**
   * @brief 帧率
   */
  i32_fps: number,
  /**
   * @brief gop
   */
  i32_gop: number,
  /**
   * @brief 编码码率，单位 Kbps
   */
  i32_bitrate_kpbs: number,
  /**
   * @brief 编码参数
   */
  video_codec_profile: TranscoderVideoCodecProfile,
  /**
   * @brief 是否开启低延迟
   */
  lowLatency: boolean
}

/**
 * @brief 布局设置
 */
export interface TranscoderLayoutRegion {
  /**
   * @brief 合流用户的 ID。必填。
   */
  region_id: string,
  /**
   * @brief 媒体流所在房间的房间 ID。
   */
  room_id: string,
  /**
   * @brief 用户视频布局相对画布左侧的偏移量，取值的范围为 [0.0, 1.0)
   */
  x: number,
  /**
   * @brief 用户视频布局相对画布顶端的偏移量，取值的范围为 [0.0, 1.0)
   */
  y: number,
  /**
   * @brief 用户视频宽度相对画布宽度的比例，取值的范围为 (0.0, 1.0]
   */
  width: number,
  /**
   * @brief 用户视频高度相对画布高度的比例，取值的范围为 (0.0, 1.0]
   */
  height: number,
  /**
   * @brief 透明度，取值范围 [0，255]
   */
  alpha: number
  /**
   * @brief 用户视频布局在画布中的层级，取值范围 [0，100]，0 为底层，值越大层级越高
   */
  i32_z_order: number
  /**
   * @brief 是否为本地用户
   */
  local_user: boolean,
  /**
   * @brief 是否为屏幕流
   */
  screen_stream: boolean,
  /**
   * @brief 合流输出内容
   */
  content_control: TranscoderContentControlType,
  /**
   * @brief 渲染时，视频内容缩放模式
   */
  render_mode: TranscoderRenderMode

}

/**
 * @brief 转推直播媒体类型
 */
export enum TranscoderContentControlType {
  /**
   * @brief 音视频
   */
  kHasAudioAndVideo = 0,
  /**
   * @brief 音频
   */
  kHasAudioOnly = 1,
  /**
   * @brief 视频
   */
  kHasVideoOnly = 2,
};

/**
 * @brief 转推直播视频编码参数
 */
export enum TranscoderVideoCodecProfile {
  /**
   * @brief H264 格式基本规格编码
   */
  kByteH264ProfileBaseline = 0,
  /**
   * @brief H264 格式主流规格编码
   */
  kByteH264ProfileMain = 1,
  /**
   * @brief H264 格式高规格编码
   */
  kByteH264ProfileHigh = 2,
  /**
   * @brief ByteVC1 格式基本规格编码
   */
  kByteVC1ProfileBaseline = 3,
  /**
   * @brief ByteVC1 格式主流规格编码
   */
  kByteVC1ProfileMain = 4,
  /**
   * @brief ByteVC1 格式高规格编码
   */
  kByteVC1ProfileHigh = 5
}

/**
 *@brief 转推直播音频编码 AAC 等级
 */
export enum TranscoderAudioCodecProfile {
  /**
   * @brief AAC-LC
   */
  kByteAACProfileLC = 0,
  /**
   * @brief AAC-MAIN
   */
  kByteAACProfileMain = 1,
  /**
   * @brief HE-AAC v1
   */
  kByteAACProfileHEv1 = 2,
  /**
   * @brief HE-AAC v2
   */
  kByteAACProfileHEv2 = 3
};
/**
 *@brief 转推直播视频渲染模式
 */
export enum TranscoderRenderMode {
  /**
   * @hidden 
   * TODO(LIYL): remove
   */
  kRenderUnknown = 0,  
  /**
   *  @brief 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
   */
  kRenderHidden = 1,
  /**
   *  @brief
   * 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。
   */
  kRenderFit = 2,
  /**
   *  @brief 视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。
   */
  kRenderAdaptive = 3,
};

/**
 * @type keytype
 * @brief 媒体流网络质量。
 */
export enum NetworkQuality {
    /**
     * @brief 网络质量未知。
     */
    kNetworkQualityUnknown = 0,
    /**
     * @brief 网络质量极好。
     */
    kNetworkQualityExcellent,
    /**
     * @brief 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
     */
    kNetworkQualityGood,
    /**
     * @brief 主观感受有瑕疵但不影响沟通。
     */
    kNetworkQualityPoor,
    /**
     * @brief 勉强能沟通但不顺畅。
     */
    kNetworkQualityBad,
    /**
     * @brief 网络质量非常差，基本不能沟通。
     */
    kNetworkQualityVbad,
};

/**
 * @type keytype
 * @brief 发送用户消息或者房间消息的结果
 */
export enum MessageSendResultCode {
  /**
   * @brief 用户P2P消息发送成功
   */
  MESSAGE_CODE_SUCCESS = 0,
  /**
   * @brief 房间Broadcast消息发送成功
   */
  MESSAGE_CODE_ROOM_SUCCESS = 200,
  /**
   * @brief 发送超时，没有发送
   */
  MESSAGE_CODE_ERROR_TIMEOUT = 1,
  /**
   * @brief 通道断开，没有发送
   */
  MESSAGE_CODE_ERROR_BROKEN = 2,
  /**
   * @brief 找不到接收方
   */
  MESSAGE_CODE_ERROR_NOT_RECEIVER = 3,
  /**
   * @brief 没有加入房间
   */
  MESSAGE_CODE_ERROR_NOT_JOIN = 100,
  /**
   * @brief 没有可用的数据传输通道连接
   */
  MESSAGE_CODE_ERROR_NO_CONNECTION = 102,
  /**
   * @brief 消息超过最大长度，当前为64KB
   */
  MESSAGE_CODE_ERROR_EXCEED_MAX_LENGTH = 103,
  /**
   * @brief 用户id为空
   */
  MESSAGE_CODE_ERROR_EMPTY_USER = 104,
  /**
   * @brief 未知错误
   */
  MESSAGE_CODE_ERROR_UNKNOWN = 1000,
};

/**
 * @type keytype
 * @brief 音频混音文件播放状态。
 */
 export enum AudioMixingState {
  /**
   * @brief 混音已加载
   */
  kAudioMixingStatePreloaded = 0,
  /**
   * @brief 混音正在播放
   */
  kAudioMixingStatePlaying,
  /**
   * @brief 混音暂停
   */
  kAudioMixingStatePaused,
  /**
   * @brief 混音停止
   */
  kAudioMixingStateStopped,
  /**
   * @brief 混音播放失败
   */
  kAudioMixingStateFailed,
  /**
   * @brief 混音播放结束
   */
  kAudioMixingStateFinished
};

/**
 * @type keytype
 * @brief 音频混音文件播放错误码。
 */
export enum AudioMixingError {
  /**
   * @brief 混音错误码，正常
   */
  kAudioMixingErrorOk = 0,
  /**
   * @brief 预加载失败，找不到混音文件或者文件长度超出 20s
   */
  kAudioMixingErrorPreloadFailed,
  /**
   * @brief 混音开启失败，找不到混音文件或者混音文件打开失败
   */
  kAudioMixingErrorStartFailed,
  /**
   * @brief 混音 ID 异常
   */
  kAudioMixingErrorIdNotFound,
  /**
   * @brief 设置混音文件的播放位置出错
   */
  kAudioMixingErrorSetPositionFailed,
  /**
   * @brief 音量参数不合法，仅支持设置的音量值为[0 400]
   */
  kAudioMixingErrorInValidVolume,
  /**
   * @brief 播放的文件与预加载的文件不一致，请先使用 UnloadAudioMixing{@link #UnloadAudioMixing} 卸载文件
   */
  kAudioMixingErrorLoadConflict,
  /**
   * @hidden
   * @deprecated
   * @brief 混音错误码，失败，已废弃
   */
  kAudioMixingErrorCanNotOpen = 701,
};
/** {zh}
 * @detail 85534
 * @brief 回调警告码。警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。
 */
 export enum WarningCode {
/**
   * @hidden
   */
  kWarningCodeGetRoomFailed = -2000,
  /**
  * @brief 进房失败。  <br>
  *        当你调用初次加入房间或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
  */
  kWarningCodeJoinRoomFailed = -2001,
  /**
  * @brief 发布音视频流失败。  <br>
  *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
  */
  kWarningCodePublishStreamFailed = -2002,
  /**
  * @brief 订阅音视频流失败。  <br>
  *        当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。
  */
  kWarningCodeSubscribeStreamFailed404 = -2003,
  /**
  * @brief 订阅音视频流失败。  <br>
  *        当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
  */
  kWarningCodeSubscribeStreamFailed5xx = -2004,
  /**
  * @hidden
  * @brief 函数调用顺序错误。
  */
  kWarningCodeInvokeError = -2005,
  /**
  * @hidden
  * @brief 调度异常，服务器返回的媒体服务器地址不可用。
  */
  kWarningCodeInvalidExpectMediaServerAddress = -2007,
  /**
   * @brief 当调用 SetUserVisibility{@link 85532#SetUserVisibility} 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  
   */
  kWarningCodePublishStreamForbiden = -2009,
  /**
   * @hidden
   * @brief 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br>你需在进房时关闭自动订阅模式，再调用 SubscribeStream{@link 85532#SubscribeStream} 方法手动订阅音视频流。
   */
  kWarningCodeSubscribeStreamForbiden = -2010,
  /**
  * @brief 发送自定义广播消息失败，当前你未在房间中。
  */
  kWarningCodeSendCustomMessage = -2011,
  /**
  * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 OnUserJoined{@link #IRTCRoomEventHandler#OnUserJoined} 和 OnUserLeave{@link #IRTCRoomEventHandler#OnUserLeave} 回调，并通过广播提示房间内所有用户。
  */
  kWarningCodeUserNotifyStop = -2013,
  /**
  * @brief 摄像头权限异常，当前应用没有获取摄像头权限。
  */
  kWarningCodeNoCameraPermission = -5001,
  /**
  * @brief 麦克风权限异常，当前应用没有获取麦克风权限。
  */
  kWarningCodeNoMicrophonePermission = -5002,
/**
  * @brief 音频采集设备启动失败，当前设备可能被其他应用占用。
  */
  kWarningCodeRecodingDeviceStartFailed = -5003,
  /**
  * @brief 音频播放设备启动失败警告，可能由于系统资源不足，或参数错误。
  */
  kWarningCodePlayoutDeviceStartFailed = -5004,
  /**
  * @brief 无可用音频采集设备，请插入可用的音频采集设备。
  */
  kWarningCodeNoRecordingDevice = -5005,
  /**
  * @brief 无可用音频播放设备，请插入可用的音频播放设备。
  */
  kWarningCodeNoPlayoutDevice = -5006,
  /**
  * @brief 当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。
  */
  kWarningCodeRecordingSilence = -5007,
  /**
  * @brief 媒体设备误操作警告。  <br>
  *        使用自定义采集时，不可调用内部采集开关，调用时将触发此警告。
  */
  kWarningCodeMediaDeviceOperationDenied = -5008,

  /**
   * @hidden
   * @brief 不支持在 publishScreen{@link 85532#PublishScreen} 之后设置屏幕音频采集类型
   *        setScreenAudioSourceType{@link 85532#SetScreenAudioSourceType}，请在 PublishScreen 之前设置
   */
  kWarningCodeSetScreenAudioSourceTypeFailed = -5009,

  /**
   * @brief 不支持在 publishScreen{@link 85532#PublishScreen} 之后，
   *        通过 setScreenAudioStreamIndex{@link 85532#SetScreenAudioStreamIndex} 设置屏幕共享时的音频采集方式。
   */
  kWarningCodeSetScreenAudioStreamIndexFailed = -5010,


  /**
  * @brief 指定的内部渲染画布句柄无效。  <br> 当你调用 setupLocalVideo{@link 85532#setupLocalVideo} 或 setupRemoteVideo{@link 85532#setupRemoteVideo} 时指定了无效的画布句柄，触发此回调。
  */
  kWarningCodeInvalidCanvasHandle = -6001
};

/**
 * @type keytype
 * @brief App 使用的 cpu 和内存信息。  <br>
 *        信息由 SDK 周期性（2s）地通过 OnSysStats{@link 85533#OnSysStats} 回调通知给用户。
 */
export interface SysStats {
  /**
   * @brief 当前系统 CPU 核数
   */
  cpu_cores: number;
  /**
   * @brief 当前应用的 cpu 使用率，取值范围为 [0, 1]。
   */
  cpu_app_usage: number
  /**
   * @brief 当前系统的 cpu 使用率，取值范围为 [0, 1]。
   */
  cpu_total_usage: number;
  /**
   * @brief 当前应用的内存使用量（单位 MB）
   */
  memory_usage: number;
  /**
   * @brief 全量内存（单位字节）
   */
  full_memory: number;
  /**
   * @brief 系统已使用内存（单位字节）
   */
  total_memory_usage: number;
  /**
   * @brief 空闲可分配内存（单位字节）
   */
  free_memory: number;
  /**
   * @brief 当前应用的内存使用率（单位 %）
   */
  memory_ratio: number;
  /**
   * @brief 系统内存使用率（单位 %）
   */
  total_memory_ratio: number;
};

/**
 * @detail 85534
 * @brief 回调错误码。  <br>SDK 内部遇到不可恢复的错误时，会通过 OnError{@link 85533#OnError} 回调通知用户。
 */
 export enum ErrorCode {
  /**
   * @brief Token 无效。<br>调用 joinRoom{@link 85532#JoinRoom} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用 UpdateToken{@link #UpdateToken} 方法更新 Token。
   */
  kErrorCodeInvalidToken = -1000,
  /**
   * @brief 加入房间错误。<br>调用 joinRoom{@link 85532#JoinRoom} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
   */
  kErrorCodeJoinRoom = -1001,
  /**
   * @brief 没有发布音视频流权限。<br>用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。
   */
  kErrorCodeNoPublishPermission = -1002,
  /**
   * @brief 没有订阅音视频流权限。<br>用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。
   */
  kErrorCodeNoSubscribePermission = -1003,
  /**
   * @brief 用户重复登录。<br>本地用户所在房间中有相同用户 ID 的用户加入房间，导致本地用户被踢出房间。
   */
  kErrorCodeDuplicateLogin = -1004,

  /**
   * @brief 用户被踢出房间。<br> 本端用户被主动踢出所在房间时，回调此错误。
   */
  kBrerrKickedOut = -1006,

  /**
   * @brief 订阅音视频流失败，订阅音视频流总数超过上限。<br>游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。
   */
  kErrorCodeOverStreamSubscribeLimit = -1070,
  /**
   * @brief 发布流失败，发布流总数超过上限。<br> RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
   */
  kErrorCodeOverStreamPublishLimit = -1080,
  /**
   * @brief 发布屏幕流失败，发布流总数超过上限。<br>RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
   */
  kErrorCodeOverScreenPublishLimit = -1081,
  /**
   * @brief 发布视频流总数超过上限。<br>RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。
   */
  kErrorCodeOverVideoPublishLimit = -1082,
};

/** {zh}
 * @type keytype
 * @brief SDK 网络连接类型。
 */
export enum NetworkType {
  /**
   * @brief 网络连接类型未知。
   */
  kNetworkTypeUnknown = -1,
  /**
   * @brief 网络连接已断开。
   */
  kNetworkTypeDisconnected = 0,
  /**
   * @brief 网络连接类型为 LAN 。
   */
  kNetworkTypeLAN = 1,
  /**
   * @brief 网络连接类型为 Wi-Fi（包含热点）。
   */
  kNetworkTypeWIFI = 2,
  /**
   * @brief 网络连接类型为 2G 移动网络。
   */
  kNetworkTypeMobile2G = 3,
  /**
   * @brief 网络连接类型为 3G 移动网络。
   */
  kNetworkTypeMobile3G = 4,
  /**
   * @brief 网络连接类型为 4G 移动网络。
   */
  kNetworkTypeMobile4G = 5,
  /**
   * @brief 网络连接类型为 5G 移动网络。
   */
  kNetworkTypeMobile5G = 6,
};

/**
 * @type keytype
 * @brief 是否开启发布性能回退
 */
 export enum PerformanceAlarmMode {
  /**
   * @brief 未开启发布性能回退
   */
  kPerformanceAlarmModeNormal = 0,
  /**
   * @brief 已开启发布性能回退
   */
  kPerformanceAlarmModeSimulcast = 1,
};

/** {zh}
 * @type keytype
 * @brief OnPerformanceAlarms{@link 85533#OnPerformanceAlarms} 告警的原因
 */
 export enum PerformanceAlarmReason {
  /**
   * @brief 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。
   */
  kPerformanceAlarmReasonBandwidthFallbacked = 0,
  /**
   * @brief 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。
   */
  kPerformanceAlarmReasonBandwidthResumed = 1,
  /**
   * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足；<br>如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。
   */
  kPerformanceAlarmReasonPerformanceFallbacked = 2,
  /**
   * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复；<br> 如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。
   */
  kPerformanceAlarmReasonPerformanceResumed = 3,
};

/**
 * @type keytype
 * @brief 媒体设备错误类型
 */
 export enum MediaDeviceError {
  /**
   *@brief 媒体设备正常
   */
  kMediaDeviceErrorOK = 0,
  /**
   *@brief 没有权限启动媒体设备
   */
  kMediaDeviceErrorDeviceNoPermission = 1,
  /**
   *@brief 媒体设备已经在使用中
   */
  kMediaDeviceErrorDeviceBusy = 2,
  /**
   *@brief 媒体设备错误
   */
  kMediaDeviceErrorDeviceFailure = 3,
  /**
   *@brief 未找到指定的媒体设备
   */
  kMediaDeviceErrorDeviceNotFound = 4,
  /**
   *@brief 媒体设备被移除
   */
  kMediaDeviceErrorDeviceDisconnected = 5,
};

/**
 * @type keytype
 * @brief 用户加入房间的类型。  
 */
 export enum JoinRoomType {
  /**
   * @brief 首次加入房间。用户手动调用 joinRoom{@link 85532#JoinRoom}，收到加入成功。  
   */
  kJoinRoomTypeFirst = 0,
  /**
   * @brief 重新加入房间。用户网络较差，失去与服务器的连接，进行重连时收到加入成功。  
   */
  kJoinRoomTypeReconnected = 1,
};

/**
 * @type keytype
 * @brief 本地音频流统计信息，统计周期为 2s 。  <br>本地用户发布音频流成功后，SDK 会周期性地通过 OnLocalStreamStats{@link 85533#OnLocalStreamStats}<br>通知用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>
 */
 export interface  LocalAudioStats {
  /**
   * @brief 音频丢包率。此次统计周期内的音频上行丢包率，单位为 % ，取值范围为 [0, 1]。  
   */
  audio_loss_rate:number;
  /**
   * @brief 发送码率。此次统计周期内的音频发送码率，单位为 kbps 。  
   */
  send_kbitrate: number;
  /**
   * @brief 采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  
   */
  record_sample_rate: number;
  /**
   * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  
   * @notes 此字段用于设置回调的统计周期，默认设置为 2s 。
   */
  stats_interval: number;
  /**
   * @brief 往返时延。单位为 ms 。  
   */
  rtt: number;
  /**
   * @brief 音频声道数。  
   */
  num_channels: number;
  /**
   * @brief 音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。  
   */
  sent_sample_rate: number;
};

/**
 * @type keytype
 * @brief 本地视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性地通过 OnLocalStreamStats{@link 85533#OnLocalStreamStats}<br>通知用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  
 */
 export interface LocalVideoStats {
  /**
   * @brief 发送码率。此次统计周期内的视频发送码率，单位为 kbps 。
   */
  sent_kbitrate: number;
  /**
   * @brief 采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。
   */
  input_frame_rate: number;
  /**
   * @brief 发送帧率。此次统计周期内的视频发送帧率，单位为 fps 。
   */
  sent_frame_rate: number;
  /**
   * @brief 编码器输出帧率。当前编码器在此次统计周期内的输出帧率，单位为 fps 。
   */
  encoder_output_frame_rate: number;
  /**
   * @brief 本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。
   */
  renderer_output_frame_rate: number;
  /**
   * @brief 目标发送码率。此次统计周期内的视频目标发送码率，单位为 kbps 。
   */
  target_kbitrate: number;
  /**
   * @brief 目标发送帧率。当前编码器在此次统计周期内的目标发送帧率，单位为 fps 。
   */
  target_frame_rate: number;
  /**
   * @brief 统计间隔，单位为 ms 。
   * @notes 此字段用于设置回调的统计周期，默认设置为 2s 。
   */
  stats_interval: number;
  /**
   * @brief 视频丢包率。此次统计周期内的视频上行丢包率，取值范围为 [0，1] 。
   */
  video_loss_rate: number;
  /**
   * @brief 往返时延，单位为 ms 。
   */
  rtt: number;
  /**
   * @brief 视频编码码率。此次统计周期内的视频编码码率，单位为 kbps 。
   */
  encoded_bitrate: number;
  /**
   * @brief 视频编码宽度，单位为 px 。
   */
  encoded_frame_width: number;
  /**
   * @brief 视频编码高度，单位为 px 。
   */
  encoded_frame_height: number;
  /**
   * @brief 此次统计周期内发送的视频帧总数。
   */
  encoded_frame_count: number;
  /**
   * @brief 视频的编码类型，具体参考 VideoCodecType{@link #VideoCodecType} 。
   */
  codec_type:VideoCodecType ;
  /**
   * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
   */
  is_screen: boolean;
};

export interface LocalStreamStats {
  /**
   * @brief 本地设备发送音频流的统计信息，详见 LocalAudioStats{@link #LocalAudioStats}
   */
  audio_stats: LocalAudioStats;
  /**
   * @brief 本地设备发送视频流的统计信息，详见 LocalVideoStats{@link #LocalVideoStats}
   */
  video_stats:LocalVideoStats;
  /**
   * @brief 所属用户的媒体流上行网络质量，详见 NetworkQuality{@link #NetworkQuality}
   */
   local_tx_quality:NetworkQuality;
  /**
   * @brief 所属用户的媒体流下行网络质量，详见 NetworkQuality{@link #NetworkQuality}
   */
   local_rx_quality:NetworkQuality;
  /**
   * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
   */
   is_screen: boolean;
};

/**
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 OnRemoteStreamStats{@link #OnRemoteStreamStats} 通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
 export interface RemoteAudioStats {
  /**
   * @brief 音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  
   */
  audio_loss_rate:number;
  /**
   * @brief 接收码率。统计周期内的音频接收码率，单位为 kbps 。  
   */
  received_kbitrate: number;
  /**
   * @brief 音频卡顿次数。统计周期内的卡顿次数。  
   */
  stall_count: number;
  /**
   * @brief 音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  
   */
  stall_duration: number;
  /**
   *@brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  
   */
  e2e_delay: number;
  /**
   * @brief 播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  
   */
  playout_sample_rate: number;
  /**
   * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  
   */
  stats_interval: number;
  /**
   * @brief 客户端到服务端数据传输的往返时延，单位为 ms。 
   */
  rtt: number;
  /**
   * @brief 发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  
   */
  total_rtt: number;
  /**
   * @brief 远端用户发送的音频流质量。值含义参考 NetworkQuality{@link #NetworkQuality} 。  
   */
  quality: number;
  /**
   * @brief 因引入 jitter buffer 机制导致的延时。单位为 ms 。  
   */
  jitter_buffer_delay: number;
  /**
   * @brief 音频声道数。  
   */
  num_channels: number;
  /**
   * @brief 音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  
   */
  received_sample_rate: number;
  /**
   * @brief 远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。
   */
  frozen_rate: number;
  /**
   * @brief 音频 PLC 样点总个数。  
   */
  concealed_samples: number;
  /**
   * @brief PLC 累计次数。  
   */
  concealment_event: number;
  /**
   * @brief 音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  
   */
  dec_sample_rate: number;
  /**
   * @brief 解码时长。对此次统计周期内接收的远端音频流进行解码的总耗时，单位为 s 。  
   */
  dec_duration: number;
};

/**
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 OnRemoteStreamStats{@link 85533#OnRemoteStreamStats}
 *        通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
 export interface RemoteVideoStats {
  /**
   * @brief 视频宽度
   */
  width: number;
  /**
   * @brief 视频高度
   */
  height: number;
  /**
   * @brief 视频丢包率。统计周期内的视频下行丢包率，单位为 % ，取值范围：[0，1] 。
   */
  video_loss_rate: number;
  /**
   * @brief 接收码率。统计周期内的视频接收码率，单位为 kbps 。
   */
  received_kbitrate: number;
  /**
   * @brief 解码器输出帧率。统计周期内的视频解码器输出帧率，单位 fps 。
   */
  decoder_output_frame_rate: number;
  /**
   * @brief 渲染帧率。统计周期内的视频渲染帧率，单位 fps 。
   */
  renderer_output_frame_rate: number;
  /**
   * @brief 卡顿次数。统计周期内的卡顿次数。
   */
  stall_count: number;
  /**
   * @brief 卡顿时长。统计周期内的视频卡顿总时长。单位 ms 。
   */
  stall_duration: number;
  /**
   * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。
   */
  e2e_delay: number;
  /**
   * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前数据来自主流还是屏幕流。
   */
  is_screen: number;
  /**
   * @brief 统计间隔，此次统计周期的间隔，单位为 ms 。  
   * @notes 此字段用于设置回调的统计周期，目前设置为 2s 。
   */
  stats_interval: number;
  /**
   * @brief 往返时延，单位为 ms 。
   */
  rtt: number;
  /**
   * @brief 远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。
   */
  frozen_rate: number;
  /**
   * @brief 对应多种分辨率的流的下标，详见 VideoSolutionDescription{@link #VideoSolutionDescription}
   */
  video_index: number;
};

/**
 * @type keytype
 * @brief 用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 OnRemoteStreamStats{@link 85533#OnRemoteStreamStats}
 *        通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  
 */
 export interface RemoteStreamStats {
  /**
   * @brief 用户 ID 。音频来源的远端用户 ID 。  
   */
  uid: String;
  /**
   * @brief 远端音频流的统计信息，详见 RemoteAudioStats{@link #RemoteAudioStats}
   */
  audio_stats: RemoteAudioStats;
  /**
   * @brief 远端视频流的统计信息，详见 RemoteVideoStats{@link #RemoteVideoStats}
   */
   video_stats: RemoteVideoStats ;
  /**
   * @brief 所属用户的媒体流上行网络质量，详见 NetworkQuality{@link #NetworkQuality}
   */
   remote_tx_quality: NetworkQuality ;
  /**
   * @brief 所属用户的媒体流下行网络质量，详见 NetworkQuality{@link #NetworkQuality}
   */
   remote_rx_quality: NetworkQuality ;
  /**
   * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
   */
   is_screen: boolean;
};

/**
 * @type keytype
 * @brief 停止/启动发送音/视频流的状态
 */
 export enum MuteState {
  /**
   * @brief 启动发送音/视频流的状态
   */
  kMuteStateOff = 0,
  /**
   * @brief 停止发送音/视频流的状态
   */
  kMuteStateOn = 1,
};

/**
 * @type keytype
 * @brief 流属性
 */
 export enum StreamIndex {
  /**
   * @brief 主流。<br>
   *        包括：<br>
   *        + 通过默认摄像头/麦克风采集到的视频/音频; <br>
   *        + 通过自定义设备采集到的视频/音频。
   */
  kStreamIndexMain = 0,
  /**
   * @brief 屏幕流。 <br>
   *        屏幕共享时共享的视频流，或来自声卡的本地播放音频流。
   */
  kStreamIndexScreen = 1,
};

/**
 *@brief 合流事件事件类型
 */
 export enum StreamMixingEvent {
  /**
   * @hidden
   */ 
  kStreamMixingBase = 0,
  /**
   * @brief 合流开始
   */
  kStreamMixingStart = 1,
  /**
   * @brief 合流启动成功
   */
  kStreamMixingStartSuccess = 2,
  /**
   * @brief 合流启动失败
   */
  kStreamMixingStartFailed = 3,
  /**
   * @brief 更新合流
   */
  kStreamMixingUpdate = 4,
  /**
   * @brief 合流结束
   */
  kStreamMixingStop = 5,
  /**
   * @brief 服务端合流/端云一体合流
   */
  kStreamMixingChangeMixType = 6,
  /**
   * @brief 收到客户端合流音频首帧
   */
  kStreamMixingFirstAudioFrameByClientMix = 7,
  /**
   * @brief 收到客户端合流视频首帧
   */
  kStreamMixingFirstVideoFrameByClientMix = 8,
  /**
   * @brief 停止服务端合流超时
   */
  kStreamMixingStopTimeoutByServer = 9,
  /**
   * @brief 更新合流超时
   */
  kStreamMixingUpdateTimeout = 10,
  /**
  * @brief 合流布局参数错误
  */
  kStreamMixingRequestParamError = 11,
  /**
   * @hidden
   */
  kStreamMixingMax = 15,
};

/**
 *@brief 合流类型
 */
 export enum StreamMixingType {
  /**
   * @brief 服务端合流
   */
  kStreamMixingTypeByServer = 0,
  /**
   * @brief 客户端合流
   */
  kStreamMixingTypeByClient = 1,
};

/**
 * @type keytype
 * @brief 远端流信息
 */
 export interface RemoteStreamKey {
  /**
   * @brief 房间 ID
   */
  room_id: String;
  /**
   * @brief 用户 ID
   */
  user_id: String;
  /**
   * @brief 流属性，主流或屏幕流。参看 StreamIndex{@link #StreamIndex}
   */
   stream_index: StreamIndex;
};

/**
 * @type keytype
 * @brief 本地录制参数配置
 */
 export interface RecordingConfig {
  /**
   * @brief 录制文件保存的绝对路径。你需要指定一个有读写权限的合法路径。
   */
  dir_path: String;
  /**
   * @brief 录制存储文件格式
   * aac : 0
   * mp4 : 1
   */
  file_type: Number;
  /**
   * @brief 录制媒体类型
   * 只录制音频 ： 0
   * 只录制视频 ： 1
   * 同时录制音频和视频： 2
   */
  recording_type: Number;
};

/**
 * @type keytype
 * @brief 使用自动语音识别服务所需校验信息
 */
export interface RTCASRConfig {
  /**
     * @brief 应用 ID
     */
   app_id: String;
   /**
    * @brief 用户 ID
    */
   user_id: String;
   /**
    * @brief 鉴权方式，参看 ASRAuthorizationType{@link #ASRAuthorizationType}
    */
   authorization_type: number;
   /**
    * @brief 访问令牌
    */
   access_token: String;
   /**
    * @brief 私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#uh8x72)
    */
   secret_key: String;
   /**
    * @brief 场景信息，参看[业务集群](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#aI4WCt)
    */
   cluster: String;
};

/**
 * @type keytype
 * @brief 房间内远端流被移除的原因。  
 */
 export enum StreamRemoveReason {
  /**
   * @brief 远端用户停止发布流。  
   */
  kStreamRemoveReasonUnpublish = 0,
  /**
   * @brief 远端用户发布流失败。  
   */
  kStreamRemoveReasonPublishFailed = 1,
  /**
   * @brief 保活失败。  
   */
  kStreamRemoveReasonKeepLiveFailed = 2,
  /**
   * @brief 远端用户断网。  
   */
  kStreamRemoveReasonClientDisconnected = 3,
  /**
   * @brief 远端用户重新发布流。  
   */
  kStreamRemoveReasonRepublish = 4,
  /**
   * @brief 其他原因。  
   */
  kStreamRemoveReasonOther = 5,
};

/**
 * @type keytype
 * @brief 远端订阅流发生回退或恢复的原因
 */
 export enum FallbackOrRecoverReason {
  /**
   * @brief 其他原因，非带宽和性能原因引起的回退或恢复。默认值
   */
  kFallbackOrRecoverReasonUnknown = -1,
  /**
   * @brief 由带宽不足导致的订阅端音视频流回退。
   */
  kFallbackOrRecoverReasonSubscribeFallbackByBandwidth = 0,
  /**
   * @brief 由性能不足导致的订阅端音视频流回退。
   */
  kFallbackOrRecoverReasonSubscribeFallbackByPerformance = 1,
  /**
   * @brief 由带宽恢复导致的订阅端音视频流恢复。
   */
  kFallbackOrRecoverReasonSubscribeRecoverByBandwidth = 2,
  /**
   * @brief 由性能恢复导致的订阅端音视频流恢复。
   */
  kFallbackOrRecoverReasonSubscribeRecoverByPerformance = 3,
  /**
   * @brief 由带宽不足导致的发布端音视频流回退。
   */
  kFallbackOrRecoverReasonPublishFallbackByBandwidth = 4,
  /**
   * @brief 由性能不足导致的发布端音视频流回退。
   */
  kFallbackOrRecoverReasonPublishFallbackByPerformance = 5,
  /**
   * @brief 由带宽恢复导致的发布端音视频流恢复。
   */
  kFallbackOrRecoverReasonPublishRecoverByBandwidth = 6,
  /**
   * @brief 由性能恢复导致的发布端音视频流恢复。
   */
  kFallbackOrRecoverReasonPublishRecoverByPerformance = 7,
};

/**
 * @type keytype
 * @brief 流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。
 */
 export interface RemoteStreamSwitch {
  /**
   * @brief 订阅的音视频流的发布者的用户 ID。
   */
  uid: String;
  /**
   * @brief 是否是屏幕流。
   */
  is_screen: boolean;
  /**
   * @brief 流切换前本地用户订阅的视频流的分辨率对应的索引。
   */
  before_video_index: number;
  /**
   * @brief 流切换后本地用户订阅的视频流的分辨率对应的索引。
   */
  after_video_index: number;
  /**
   * @brief 流切换前是否有视频流。
   */
  before_enable: boolean;
  /**
   * @brief 流切换后是否有视频流。
   */
  after_enable: boolean;
  /**
   * @brief 触发流回退的原因，详见类型 FallbackOrRecoverReason{@link #FallbackOrRecoverReason} 。
   */
  reason: FallbackOrRecoverReason;
};

/**
* @type keytype
* @brief 视频帧旋转角度
*/
export enum VideoRotation {
  /**
   * @brief 顺时针旋转 0 度
  */
  kVideoRotation0 = 0,
  /**
   * @brief 顺时针旋转 90 度
  */
  kVideoRotation90 = 90,
  /**
   * @brief 顺时针旋转 180 度
  */
  kVideoRotation180 = 180,
  /**
   * @brief 顺时针旋转 270 度
  */
  kVideoRotation270 = 270
};

export interface VideoFrameInfo {
  /**
   * @brief 宽（像素）
   */
  width: number;
  /**
   * @brief 高（像素）
   */
  height: number;
  /**
   * @brief 视频帧顺时针旋转角度。参看 VideoRotation{@link #VideoRotation}。
   */
   rotation:VideoRotation;
};

/** {zh}
 * @type keytype
 * @brief 本地音频流状态。<br>
 *        SDK 通过 OnLocalAudioStateChanged{@link 85533#OnLocalAudioStateChanged} 回调本地音频流状态
 */
 export enum LocalAudioStreamState {
  /**
   * @brief 本地音频默认初始状态。
   *        麦克风停止工作时回调该状态，对应错误码 kLocalAudioStreamErrorOk
   */
  kLocalAudioStreamStateStopped = 0,

  /**
   * @brief 本地音频录制设备启动成功。
   *        采集到音频首帧时回调该状态，对应错误码 kLocalAudioStreamErrorOk
   */
  kLocalAudioStreamStateRecording,

  /**
   * @brief 本地音频首帧编码成功。
   *        音频首帧编码成功时回调该状态，对应错误码 kLocalAudioStreamErrorOk
   */
  kLocalAudioStreamStateEncoding,

  /**
   * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
   *       + 本地录音设备启动失败，对应错误码 kLocalAudioStreamErrorRecordFailure <br>
   *       + 检测到没有录音设备权限，对应错误码 kLocalAudioStreamErrorDeviceNoPermission  <br>
   *       + 音频编码失败，对应错误码 kLocalAudioStreamErrorEncodeFailure
   */
  kLocalAudioStreamStateFailed,
};

/**
 * @detail 85534
 * @brief 本地音频流状态改变时的错误码。
 *        SDK 通过 OnLocalAudioStateChanged{@link 85533#OnLocalAudioStateChanged} 回调该错误码。
 */
 export enum LocalAudioStreamError {
  /**
   * @brief 本地音频状态正常
   */
  kLocalAudioStreamErrorOk = 0,
  /**
   * @brief 本地音频出错原因未知
   */
  kLocalAudioStreamErrorFailure,
  /**
   * @brief 没有权限启动本地音频录制设备
   */
  kLocalAudioStreamErrorDeviceNoPermission,
  /**
   * @brief 本地音频录制设备已经在使用中
   * @notes 该错误码暂未使用
   */
  kLocalAudioStreamErrorDeviceBusy,
  /**
   * @brief 本地音频录制失败，建议你检查录制设备是否正常工作
   */
  kLocalAudioStreamErrorRecordFailure,
  /**
   * @brief 本地音频编码失败
   */
  kLocalAudioStreamErrorEncodeFailure,
  /**
   *@brief 没有可用的音频录制设备
   */
  kLocalAudioStreamErrorNoRecordingDevice
};

/**
 * @type keytype
 * @brief 远端音频流状态。<br>
 *        用户可以通过 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged} 了解该状态。
 */
 export enum RemoteAudioState {
  /**
   * @brief  不接收远端音频流。 <br>
   *         以下情况下会触发回调 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged}：  <br>
   *       + 本地用户停止接收远端音频流，对应原因是： kRemoteAudioStateChangeReasonLocalMuted  <br>
   *       + 远端用户停止发送音频流，对应原因是： kRemoteAudioStateChangeReasonRemoteMuted  <br>
   *       + 远端用户离开房间，对应原因是： kRemoteAudioStateChangeReasonRemoteOffline  <br>
   */
  kRemoteAudioStateStopped = 0,
  /**
   * @brief 开始接收远端音频流首包。<br>
   *        刚收到远端音频流首包会触发回调 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged}，
   *        对应原因是： kRemoteAudioStateChangeReasonLocalUnmuted。
   */
  kRemoteAudioStateStarting,
  /**
   * @brief  远端音频流正在解码，正常播放。 <br>
   *         以下情况下会触发回调 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged}：  <br>
   *       + 成功解码远端音频首帧，对应原因是： kRemoteAudioStateChangeReasonLocalUnmuted
   *       + 网络由阻塞恢复正常，对应原因是： kRemoteAudioStateChangeReasonNetworkRecovery
   *       + 本地用户恢复接收远端音频流，对应原因是： kRemoteAudioStateChangeReasonLocalUnmuted
   *       + 远端用户恢复发送音频流，对应原因是： kRemoteAudioStateChangeReasonRemoteUnmuted
   */
  kRemoteAudioStateDecoding,
  /**
   * @brief 远端音频流卡顿。<br>
   *        网络阻塞、丢包率大于 40% 时，会触发回调 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged}，
   *        对应原因是： kRemoteAudioStateChangeReasonNetworkCongestion
   */
  kRemoteAudioStateFrozen,
  /**
   * @hidden
   * @brief 远端音频流播放失败
   * @notes 该错误码暂未使用
   */
  kRemoteAudioStateFailed,
};

/**
* @type keytype
* @brief 接收远端音频流状态改变的原因。  <br>
*        用户可以通过 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged} 了解该原因。
*/
export enum RemoteAudioStateChangeReason {
  /**
   * @brief 内部原因
   */
  kRemoteAudioStateChangeReasonInternal = 0,
  /**
   * @brief 网络阻塞
   */
  kRemoteAudioStateChangeReasonNetworkCongestion,
  /**
   * @brief 网络恢复正常
   */
  kRemoteAudioStateChangeReasonNetworkRecovery,
  /**
   * @brief 本地用户停止接收远端音频流
   */
  kRemoteAudioStateChangeReasonLocalMuted,
  /**
   * @brief 本地用户恢复接收远端音频流
   */
  kRemoteAudioStateChangeReasonLocalUnmuted,
  /**
   * @brief 远端用户停止发送音频流
   */
  kRemoteAudioStateChangeReasonRemoteMuted,
  /**
   * @brief 远端用户恢复发送音频流
   */
  kRemoteAudioStateChangeReasonRemoteUnmuted,
  /**
   * @brief 远端用户离开房间
   */
  kRemoteAudioStateChangeReasonRemoteOffline,
};

/**
 * @type keytype
 * @brief 本地视频流状态
 */
 export enum LocalVideoStreamState {
  /**
   * @brief 本地视频采集停止状态
   */
  kLocalVideoStreamStateStopped = 0,
  /**
   * @brief 本地视频采集设备启动成功
   */
  kLocalVideoStreamStateRecording,
  /**
   * @brief 本地视频采集后，首帧编码成功
   */
  kLocalVideoStreamStateEncoding,
  /**
   * @brief 本地视频采集设备启动失败
   */
  kLocalVideoStreamStateFailed,
};

/**
* @errorcodes
* @brief 本地视频状态改变时的错误码
*/
/** {en}
* @errorcodes
* @brief Error Codes for the local video state changed
*/
export enum LocalVideoStreamError {
  /**
   * @brief 状态正常
   */
  /** {en}
   * @brief Normal
   */
  kLocalVideoStreamErrorOk = 0,
  /**
   * @brief 本地视频流发布失败
   */
  kLocalVideoStreamErrorFailure,
  /**
   * @brief 没有权限启动本地视频采集设备
   */
  kLocalVideoStreamErrorDeviceNoPermission,
  /**
   * @brief 本地视频采集设备被占用
   */
  kLocalVideoStreamErrorDeviceBusy,
  /**
   * @brief 本地视频采集设备不存在
   */
  kLocalVideoStreamErrorDeviceNotFound,
  /**
   * @brief 本地视频采集失败，建议检查采集设备是否正常工作
   */
  kLocalVideoStreamErrorCaptureFailure,
  /**
   * @brief 本地视频编码失败
   */
  kLocalVideoStreamErrorEncodeFailure,
  /**
   * @brief 本地视频采集设备被移除
   */
  kLocalVideoStreamErrorDeviceDisconnected
};

/**
 * @type keytype
 * @brief 远端视频流状态。状态改变时，会收到回调： OnRemoteVideoStateChanged{@link 85533#OnRemoteVideoStateChanged}
 */
 export enum RemoteVideoState {
  /**
   * @brief 远端视频流默认初始状态，视频尚未开始播放。
   */
  kRemoteVideoStateStopped = 0,
  /**
   * @brief 本地用户已接收远端视频流首包。
   */
  kRemoteVideoStateStarting,
  /**
   * @brief 远端视频流正在解码，正常播放。
   */
  kRemoteVideoStateDecoding,
  /**
   * @brief 远端视频流卡顿，可能有网络等原因。
   */
  kRemoteVideoStateFrozen,
  /**
   * @brief 远端视频流播放失败。
   */
  kRemoteVideoStateFailed,
};

/**
* @type keytype
* @brief 远端视频流状态改变的原因
*/
export enum RemoteVideoStateChangeReason {
  /**
   * @brief 内部原因
   */
  kRemoteVideoStateChangeReasonInternal = 0,
  /**
   * @brief 网络阻塞
   */
  kRemoteVideoStateChangeReasonNetworkCongestion,
  /**
   * @brief 网络恢复正常
   */
  kRemoteVideoStateChangeReasonNetworkRecovery,
  /**
   * @brief 本地用户停止接收远端视频流或本地用户禁用视频模块
   */
  kRemoteVideoStateChangeReasonLocalMuted,
  /**
   * @brief 本地用户恢复接收远端视频流或本地用户启用视频模块
   */
  kRemoteVideoStateChangeReasonLocalUnmuted,
  /**
   * @brief 远端用户停止发送视频流或远端用户禁用视频模块
   */
  kRemoteVideoStateChangeReasonRemoteMuted,
  /**
   * @brief 远端用户恢复发送视频流或远端用户启用视频模块
   */
  kRemoteVideoStateChangeReasonRemoteUnmuted,
  /**
   * @brief 远端用户离开频道。
   *        状态转换参考 OnStreamRemove{@link 85533#OnStreamRemove}
   */
  kRemoteVideoStateChangeReasonRemoteOffline,
};

/**
 * @type keytype
 * @brief 本地录制的详细信息
 */
 export interface RecordingInfo {
  /**
   * @brief 录制文件的绝对路径，包含文件名和文件后缀
   */
  file_path: String;
  /**
   * @brief 录制文件的视频编码类型，参看 VideoCodecType{@link #VideoCodecType}
   */
  video_codec_type:VideoCodecType ;
  /**
   * @brief 录制视频的宽，单位：像素。纯音频录制请忽略该字段
   */
  width: number;
  /**
   * @brief 录制视频的高，单位：像素。纯音频录制请忽略该字段
   */
  height: number;
};


/**
 * @type keytype
 * @brief 本地录制进度
 */
 export interface RecordingProgress {
  /**
   * @brief 当前文件的累计录制时长，单位：毫秒
   */
  duration: number;
  /**
   * @brief 当前录制文件的大小，单位：byte
   */
  file_size: number;
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 用户信息
 */
 export interface RtcUser {
  /**
   * 用户 id
   */
  user_id: String;
  /**
   * 元数据
   */
  meta_data: String;
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 首帧发送状态
 */
 export enum FirstFrameSendState {
  /**
   * @brief 发送中
   */
  kFirstFrameSendStateSending = 0,
  /**
   * @brief 发送成功
   */
  kFirstFrameSendStateSent = 1,
  /**
   * @brief 发送失败
   */
  kFirstFrameSendStateEnd = 2,
};

/**
* @type keytype
* @region 房间管理
* @brief 首帧播放状态
*/
export enum FirstFramePlayState {
  /**
   * @brief 播放中
   */
  kFirstFramePlayStatePlaying = 0,
  /**
   * @brief 播放成功
   */
  kFirstFramePlayStatePlayed = 1,
  /**
   * @brief 播放失败
   */
  kFirstFramePlayStateEnd = 2,
};

/**
 * @type keytype
 * @brief 屏幕共享参数
 */
export interface ScreenParameters
{
  frame_rate: number;
  kbitrate: number;
}

/**
 * @brief 混音播放类型
 */
export  enum AudioMixingType {
  /**
   * @brief 仅本地播放
   */
  kAudioMixingTypePlayout,
  /**
   * @brief 仅远端播放
   */
  kAudioMixingTypePublish,
  /**
   * @brief 本地和远端同时播放
   */
  kAudioMixingTypePlayoutAndPublish
};

export enum PublishFallbackOption {
  /**
   * @brief 关闭发送视频流时的性能回退功能，默认值
   */
  kPublishFallbackOptionDisabled = 0,
  /**
   * @brief 开启在网络情况不佳或设备性能不足时只发送小流的功能
   */
  kPublishFallbackOptionSimulcast = 1,
};

/**
 * @type keytype
 * @brief 房间模式
 */
 export enum RoomProfileType {
  /**
   * @brief 普通音视频通话模式。<br>
   *        你应在 1V1 音视频通话时，使用此设置。<br>
   *        此设置下，弱网抗性较好。
   */
  kRoomProfileTypeCommunication = 0,
  /**
   * @brief 直播模式。<br>
   *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
   *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
   */
  kRoomProfileTypeLiveBroadcasting = 1,
  /**
   * @brief 游戏语音模式。此模式下延时较低。<br>
   *        低端机在此模式下运行时，进行了额外的性能优化：<br>
   *            + 采集播放采用 16kHz 单通道采样 <br>
   *            + 部分低端机型配置编码帧长 40/60 <br>
   *            + 部分低端机型关闭软件 3A 音频处理 <br>
   *        增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。
   */
  kRoomProfileTypeGame = 2,
  /**
   * @brief 云游戏模式。<br>
   *        如果你需要低延迟、高码率的设置时，你可以使用此设置。<br>
   *        此设置下，弱网抗性较差。
   */
  kRoomProfileTypeCloudGame = 3,
  /**
   * @brief 低时延模式。SDK 会使用低延时设置。  <br>
   *        当你的场景非游戏或云游戏场景，又需要极低延时的体验时，可以使用该模式。 <br>
   *        该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br>
   *        在使用此模式前，强烈建议咨询技术支持同学。
   */
  kRoomProfileTypeLowLatency = 4,
};

/**
 * @type keytype
 * @brief 订阅回退选项
 */
 export enum SubscribeFallbackOption {
  /**
   * @brief 下行网络较弱时，关闭订阅音视频流时的性能回退功能，默认值
   */
  kSubscribeFallbackOptionDisable = 0,
  /**
   * @brief 下行网络较弱时，只接收视频小流
   */
  kSubscribeFallbackOptionVideoStreamLow = 1,
  /**
   * @brief 下行网络较弱时，先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流
   */
  kSubscribeFallbackOptionAudioOnly = 2,
};

/**
 * @type keytype
 * 房间参数配置
 */
 export interface RTCRoomConfig {
  /**
   * @brief 房间模式，参看 RoomProfileType{@link #RoomProfileType}，默认为普通音视频通话模式，进房后不可更改。
   */    
   room_profile_type:RoomProfileType;
  /**
   * @brief 是否自动发布音视频流，默认为自动发布。 <br>
   *        若调用 setUserVisibility{@link 85532#SetUserVisibility} 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。
   */ 
   is_auto_publish:boolean;
  /**
   * @brief 是否自动订阅音频流，默认为自动订阅。  <br>
   *        进房后，你可以调用 subscribeUserStream{@link 85532#SubscribeUserStream} 修改订阅设置。
   */ 
  is_auto_subscribe_audio:boolean;
  /**
   * @brief 是否自动订阅主视频流，默认为自动订阅。  <br>
   *        进房后，你可以调用 subscribeUserStream{@link 85532#SubscribeUserStream} 修改订阅设置。  <br>屏幕流始终自动订阅，不受该方法影响。
   */ 
  is_auto_subscribe_video :boolean;
};

/**
 * @type keytype
 * @brief 视频订阅配置信息
 */
 export interface SubscribeVideoConfig {
  /**
   * @brief 订阅的视频流分辨率下标。  <br>
   *        当远端用户通过调用 SetVideoEncoderConfig{@link 85532#SetVideoEncoderConfig} 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
   *        默认值为 0，即订阅第一路流。  <br> 
   *        如果不想更改之前的设置，可以输入 -1。  <br>
   */
  video_index:number;
  /**
   * @brief 远端用户优先级，参看 RemoteUserPriority{@link #RemoteUserPriority}，默认值为 0。
   */
  priority:number;
};

/**
 * @type keytype
 * @brief 是否开启镜像模式
 */
 export enum MirrorMode {
  /**
   * @brief 不开启
   */
  kMirrorModeOff = 0,
  /**
   * @brief 开启
   */
  kMirrorModeOn = 1,
};

/**
 * @type keytype
 * @brief 暂停/恢复接收远端的媒体流类型。
 */
 export enum PauseResumeControlMediaType {
  /**
   * @brief 只控制音频，不影响视频
   */
  kRTCPauseResumeControlMediaTypeAudio = 0,
  /**
   * @brief 只控制视频，不影响音频
   */
  kRTCPauseResumeControlMediaTypeVideo = 1,
  /**
   * @brief 同时控制音频和视频
   */
  kRTCPauseResumeControlMediaTypeVideoAndAudio = 2
};

/**
 * @module
 * @type keytype
 * @brief 混音配置
 */
 export interface AudioMixingConfig {
  /**
   * @brief 混音播放类型，详见 AudioMixingType{@link #AudioMixingType}
   */
   type:AudioMixingType;
  /**
   * @brief 混音播放次数，
   * @notes  <br>
   *       + play_count <= 0: 无限循环  <br>
   *       + play_count == 1: 播放一次（默认）  <br>
   *       + play_count > 1: 播放 play_count 次
   */
  play_count:number;
};

/**
 * @type keytype
 * @region 屏幕共享
 * @brief 内部采集屏幕视频流时，是否采集鼠标信息
 */
 export enum MouseCursorCaptureState {
  /**
   * @brief 采集鼠标信息
   */
  kMouseCursorCaptureStateOn,
  /**
   * @brief 不采集鼠标信息
   */
  kMouseCursorCaptureStateOff,
};

/**
 * @type keytype
 * @brief 屏幕共享时，内部采集参数配置
 */
 export interface ScreenCaptureParameters {
  /**
   * @brief 采集区域，参看 Rectangle{@link #Rectangle}
   */
   region_rect:Rectangle;
  /**
   * @brief 是否采集鼠标状态，参看 MouseCursorCaptureState{@link #MouseCursorCaptureState}
   */
   capture_mouse_cursor:MouseCursorCaptureState ;
  /**
   * @brief 屏幕过滤设置，参看 ScreenFilterConfig{@link #ScreenFilterConfig}
   */
   filter_config:number[] ;
  /**
   * @brief 采集区域的边框高亮设置，参看 HighlightConfig{@link #HighlightConfig}
   */
   highlight_config:HighlightConfig;
};