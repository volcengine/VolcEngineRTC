/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Video Defines
*/

#import "ByteRTCAudioDefines.h"
/** 
 * @type keytype
 * @brief 图片或视频流的缩放模式。
 */
typedef NS_ENUM(NSUInteger, ByteRTCRenderMode) {
    /** 
     * @brief 视窗填满优先，默认值。
     *        视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    ByteRTCRenderModeHidden = 1,
    /** 
     * @brief 视频帧内容全部显示优先。
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。
     */
    ByteRTCRenderModeFit = 2,
    /** 
     * @brief 视频帧自适应画布。
     *        视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
    ByteRTCRenderModeFill = 3,
};

/** 
 * @type keytype
 * @brief 合流输出内容类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCTranscoderContentControlType) {
    /** 
     * @brief 输出的混流包含音频和视频
     */
    ByteRTCTranscoderContentControlTypeHasAudioAndVideo = 0,
    /** 
     * @brief 输出的混流只包含音频
     */
    ByteRTCTranscoderContentControlTypeHasAudioOnly = 1,
    /** 
     * @brief 输出的混流只包含视频
     */
    ByteRTCTranscoderContentControlTypeHasVideoOnly = 2,
};

/** 
 * @type keytype
 * @brief 合流布局区域类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCTranscoderLayoutRegionType) {

    /** 
     * @brief 合流布局区域类型为视频。
     */
    ByteRTCTranscoderLayoutRegionTypeVideoStream = 0,

    /** 
     * @brief 合流布局区域类型为图片。
     */
    ByteRTCTranscoderLayoutRegionTypeImage = 1,
};


/** 
 * @type keytype
 * @brief 视频流类型
 *      目前C++ SDK 只支持 ByteRTCVideoStreamTypeHigh 类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamType) {
    /** 
     * @brief 高分辨率视频流
     */
    ByteRTCVideoStreamTypeHigh = 0,
    /** 
     * @brief 低分辨率视频
     */
    ByteRTCVideoStreamTypeLow = 1,
};

/** 
 * @type keytype
 * @brief 设置本地视频属性的返回状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamState) {
    /** 
     * @brief 设置本地视频属性成功
    */
   ByteRTCVideoStreamStateSuccess                 = 0,
    /** 
     * @brief 本地视频属性参数不合法
    */
   ByteRTCVideoStreamStateInvalid                 = -2,
};

/** 
 * @type keytype
 * @brief 视频输出方向模式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoOutputOrientationMode) {
    /** 
     * @brief 自适应布局
     */
    ByteRTCVideoOutputOrientationModeAdaptative = 0,
    /** 
     * @brief 横屏布局
     */
    ByteRTCVideoOutputOrientationModeFixedLandscape = 1,
    /** 
     * @brief 竖屏布局
     */
    ByteRTCVideoOutputOrientationModeFixedPortrait = 2,
};

/** 
 * @type keytype
 * @brief 视频帧朝向
 */
typedef NS_ENUM(NSUInteger, ByteRTCVideoOrientation) {
    /** 
    * @brief （默认）使用相机输出的原始视频帧的角度，不对视频帧进行额外旋转。
    */
    ByteRTCVideoOrientationAdaptive = 0,
    /** 
    * @brief 固定为竖屏，将相机采集到的视频帧转换为竖屏，在整个 RTC 链路中传递竖屏帧。
    */
    ByteRTCVideoOrientationPortrait = 1,
    /** 
    * @brief 固定为横屏，将相机采集到的视频帧转换为横屏，在整个 RTC 链路中传递横屏帧。
    */
    ByteRTCVideoOrientationLandscape = 2
};

/** 
 * @hidden
 * @type keytype
 * @deprecated since 3.29 and will be deleted in 3.51, use ByteRTCMirrorType{@link #ByteRTCMirrorType} instead.
 * @brief 是否开启镜像模式
 */
typedef NS_ENUM(NSUInteger, ByteRTCMirrorMode) {
    /** 
     *  @brief 不开启
     */
    ByteRTCMirrorModeOff = 0,
    /** 
     *  @brief 开启
     */
    ByteRTCMirrorModeOn = 1,
};

/** 
 * @type keytype
 * @brief 镜像类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCMirrorType) {
    /** 
     * @brief 本地预览和编码传输时均无镜像效果
     */
    ByteRTCMirrorTypeNone = 0,
    /** 
     * @brief 本地预览时有镜像效果，编码传输时无镜像效果
     */
    ByteRTCMirrorTypeRender = 1,
    /** 
     * @brief 本地预览和编码传输时均有镜像效果
     */
    ByteRTCMirrorTypeRenderAndEncoder = 3,
};

/** 
 * @type keytype
 * @brief 基础美颜模式
 */
typedef NS_ENUM(NSUInteger, ByteRTCEffectBeautyMode) {
    /** 
     * @brief 美白
     */
    ByteRTCEffectWhiteMode = 0,
    /** 
     * @brief 磨皮
     */
    ByteRTCEffectSmoothMode = 1,
    /** 
     * @brief 锐化
     */
    ByteRTCEffectSharpenMode = 2,
};

/** 
 * @type keytype
 * @brief 视频旋转信息，枚举类型，定义了以 90 度为间隔的四种旋转模式。
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoRotation) {
    /** 
     * @brief 视频不做旋转
     */
    ByteRTCVideoRotation0 = 0,
    /** 
     * @brief 视频顺时针旋转 90 度
     */
    ByteRTCVideoRotation90 = 90,
    /** 
     * @brief 视频顺时针旋转 180 度
     */
    ByteRTCVideoRotation180 = 180,
    /** 
     * @brief 视频顺时针旋转 270 度
     */
    ByteRTCVideoRotation270 = 270,
};

/** 
 * @type keytype
 * @brief 视频内容类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoContentType) {
    /** 
     * @brief 普通视频
     */
    ByteRTCVideoContentTypeNormalFrame = 0,
    /** 
     * @brief 黑帧视频
     */
    ByteRTCVideoContentTypeBlackFrame = 1,
};

/** 
 * @type keytype
 * @brief 视频帧缩放模式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamScaleMode) {
    /** 
     * @brief 自动缩放模式，默认设置为 ByteRTCVideoStreamScaleModeFitWithCropping。
     */
    ByteRTCVideoStreamScaleModeAuto            = 0,
    /** 
     * @brief 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。
     */
    ByteRTCVideoStreamScaleModeStretch         = 1,
    /** 
     * @brief 视窗填满优先。  <br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    ByteRTCVideoStreamScaleModeFitWithCropping = 2,
    /** 
     * @brief 视频帧内容全部显示优先。  <br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。保持纵横比来缩放图像，填充短边
     */
    ByteRTCVideoStreamScaleModeFitWithFilling  = 3,
};

/** 
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 视频编码模式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecMode) {
    /** 
     * @brief 自动选择
    */
   ByteRTCVideoCodecModeAuto     = 0,
    /** 
     * @brief 硬编码
    */
   ByteRTCVideoCodecModeHardware = 1,
    /** 
     * @brief 软编码
    */
   ByteRTCVideoCodecModeSoftware = 2
};

/** 
 * @type keytype
 * @brief 编码帧类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPictureType) {
    /** 
     * @brief 未知类型
     */
    ByteRTCVideoPictureTypeUnknown = 0,
    /** 
     * @brief I帧，关键帧，编解码不需要参考其他视频帧
     */
    ByteRTCVideoPictureTypeI = 1,
    /** 
     * @brief P帧，向前参考帧，编解码需要参考前一帧视频帧
     */
    ByteRTCVideoPictureTypeP = 2,
    /** 
     * @brief B帧，前后参考帧，编解码需要参考前后两帧视频帧
     */
    ByteRTCVideoPictureTypeB = 3,
};

/** 
 * @type keytype
 * @brief 编码策略偏好。
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoEncoderPreference) {
    /** 
     * @brief 无偏好。不降低帧率和分辨率。
     */
    ByteRTCVideoEncoderPreferenceDisabled          = 0,
    /** 
     * @brief （默认值）帧率优先。
     */
    ByteRTCVideoEncoderPreferenceMaintainFramerate = 1,
    /** 
     * @brief 分辨率优先。
     */
    ByteRTCVideoEncoderPreferenceMaintainQuality   = 2,
    /** 
     * @brief 平衡帧率与分辨率。
     */
    ByteRTCVideoEncoderPreferenceBalance           = 3,
};

/** 
 * @type keytype
 * @brief 屏幕流编码模式。默认采用清晰模式。若在 macOS 平台采集时调用 updateScreenCaptureFilterConfig:{@link #ByteRTCVideo#updateScreenCaptureFilterConfig:} 排除指定窗口，共享视频时帧率无法达到 30fps。
 */
typedef NS_ENUM(NSInteger, ByteRTCScreenVideoEncoderPreference) {
    /** 
     * @hidden(iOS)
     * @brief 智能模式。根据屏幕内容智能决策选择流畅模式或清晰模式。
     */
    ByteRTCScreenVideoEncodePreferenceAuto   = 0,
    /** 
     * @brief 流畅模式，优先保障帧率。适用于共享游戏、视频等动态画面。
     */
    ByteRTCScreenVideoEncodePreferenceFramerate = 1,
    /** 
     * @brief 清晰模式，优先保障分辨率。适用于共享PPT、文档、图片等静态画面。
     */
    ByteRTCScreenVideoEncodePreferenceQuality   = 2,
};


/** 
 * @hidden
 * @deprecated since 3.32 and will be deleted in 3.51, use ByteRTCVirtualBackgroundSourceType{@link #ByteRTCVirtualBackgroundSourceType} instead.
 * @type keytype
 * @brief 背景模式设置。
 */
typedef NS_ENUM(NSUInteger, ByteRTCBackgroundMode) {
    /** 
     * @brief 无
     */
    ByteRTCBackgroundModeNone = 0,
    /** 
     * @brief 虚化
     */
    ByteRTCBackgroundModeBlur = 1,
    /** 
     * @brief 背景 1
     */
    ByteRTCBackgroundModeA = 2,
    /** 
     * @brief 背景 2
     */
    ByteRTCBackgroundModeB = 3,
};

/** 
 * @hidden
 * @deprecated since 3.32 and will be deleted in 3.51.
 * @type keytype
 * @brief 分割模型设置。
 */
typedef NS_ENUM(NSUInteger, ByteRTCDivideModel) {
    /** 
     * @brief 自研
     */
    ByteRTCDivideModelDefault = 0,
    /**
     * @brief effect
     */
    ByteRTCDivideModelEffect = 1,
};

/** 
 * @type keytype
 * @brief 数据类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCDataFrameType) {
    /** 
     * @brief SEI 数据
     */
    ByteRTCDataFrameTypeSei = 0,
    /** 
     * @brief 人脸识别数据
     */
    ByteRTCDataFrameTypeRoi = 1,
    /** 
     * @brief 其他数据帧类型
     */
    ByteRTCDataFrameTypeOther = 2,
};

/** 
 * @type keytype
 * @brief 视频采集模式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCapturePreference) {
   /** 
    * @brief （默认）自动设置采集参数。
    *        SDK在开启采集时根据服务端下发的采集配置结合编码参数设置最佳采集参数。
    */
   ByteRTCVideoCapturePreferenceAuto = 0,
   /** 
    * @brief 手动设置采集参数，包括采集分辨率、帧率。
    */
   ByteRTCVideoCapturePreferenceMannal = 1,
   /** 
    * @brief 采集参数与编码参数一致
    */
   ByteRTCVideoCapturePreferenceAutoPerformance = 2,
};

/** 
 * @type keytype
 * @brief 视频帧类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoFrameType) {
    /** 
     * @brief 视频帧类型：内存数据
     */
    ByteRTCVideoFrameTypeRawMemory = 0,
    /** 
     * @brief 视频帧类型：CVPixelBuffer
     */
    ByteRTCVideoFrameTypePixelBuffer,
};

/** 
 * @type keytype
 * @brief 视频帧格式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPixelFormat) {
    /** 
     * @brief 未知格式
     */
    ByteRTCVideoPixelFormatUnknown = 0,
    /** 
     * @brief I420
     */
    ByteRTCVideoPixelFormatI420 = 1,
    /** 
     * @brief BGRA
     */
    ByteRTCVideoPixelFormatBGRA = 2,
    /** 
     * @brief NV21
     */
    ByteRTCVideoPixelFormatNV21 = 3,
    /** 
     * @brief RGBA
     */
    ByteRTCVideoPixelFormatRGBA = 4,
    /** 
     * @brief IMC2
     */
    ByteRTCVideoPixelFormatIMC2 = 5,
    /** 
     * @brief ARGB
     */
    ByteRTCVideoPixelFormatARGB = 7,
    /** 
     * @brief NV12
     */
    ByteRTCVideoPixelFormatNV12 = 8,
    /** 
     * @brief Opengl Texture2D纹理
     */
    ByteRTCVideoPixelFormatGLTexture2D = 10,
    /** 
     * @brief Opengl OES纹理
     */
    ByteRTCVideoPixelFormatGLTextureOES = 11,
    /** 
     * @brief CVPixelBuffer
     */
    ByteRTCVideoPixelFormatCVPixelBuffer = 12
};

/** 
 * @type keytype
 * @brief 视频帧编码格式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSinkPixelFormat) {
    /** 
     * @brief 原始视频帧格式
     */
    ByteRTCVideoSinkPixelFormatOriginal = 0,
    /** 
     * @brief YUV I420 格式
     */
    ByteRTCVideoSinkPixelFormatI420 = 1,
    /** 
     * @brief BGRA 格式
     */
    ByteRTCVideoSinkPixelFormatBGRA = 2,
    /** 
     * @brief YUV NV21 格式
     */
    ByteRTCVideoSinkPixelFormatNV12 = 8
};

/** 
 * @type keytype
 * @hidden for internal use only
 * @brief 超分状态改变原因。
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSuperResolutionModeChangedReason) {
    /** 
     * @brief 调用 setRemoteVideoSuperResolution:withMode:{@link #ByteRTCVideo#setRemoteVideoSuperResolution:withMode:} 成功关闭超分。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonAPIOff = 0,
    /** 
     * @brief 调用 setRemoteVideoSuperResolution:withMode:{@link #ByteRTCVideo#setRemoteVideoSuperResolution:withMode:} 成功开启超分。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonAPIOn = 1,
    /** 
     * @brief 开启超分失败，远端视频流的原始视频分辨率超过 640 × 360 px。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonResolutionExceed = 2,
    /** 
     * @brief 开启超分失败，已对一路远端流开启超分。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonOverUse = 3,
    /** 
     * @brief 设备不支持使用超分辨率。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonDeviceNotSupport = 4,
    /** 
     * @brief 当前设备性能存在风险，已动态关闭
     */
    ByteRTCVideoSuperResolutionModeChangedReasonDynamicClose = 5,
    /** 
     * @brief 超分因其他原因关闭。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonOtherSettingDisabled = 6,
    /** 
     * @brief 超分因其他原因开启。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonOtherSettingEnabled = 7,
    /** 
     * @brief SDK 没有编译超分组件。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonNoComponent = 8,
    /** 
     * @brief 远端流不存在。房间 ID 或用户 ID 无效，或对方没有发布流。
     */
    ByteRTCVideoSuperResolutionModeChangedReasonStreamNotExist = 9,
};

/** 
 * @type errorcode
 * @brief 转推直播功能错误码。
 */
typedef NS_ENUM(NSInteger, ByteRTCTranscodingError) {
    /** 
     * @brief 推流成功。
     */
    ByteRTCTranscodingErrorOK = 0,
    /** 
     * @brief 推流参数错误。你必须更新合流参数并重试。
     */
    ByteRTCTranscodingErrorInvalidArgument = 1,
    /** 
     * @brief 和 RTC 服务端建立连接失败。会自动重连
     */
    ByteRTCTranscodingErrorSubscribe = 2,
    /** 
     * @brief 合流服务中间过程存在错误，建议重试。
     */
    ByteRTCTranscodingErrorProcessing = 3,
    /** 
     * @brief 推流失败，可以等待服务端重新推流。
     */
    ByteRTCTranscodingErrorPublish = 4,
};

/** 
 * @type keytype
 * @brief 合流方式
 */
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingType) {
    /** 
     * @brief 通过服务端转推
     */
    ByteRTCStreamMixingTypeByServer = 0,
    /** 
     * @brief 端云一体转推
     */
    ByteRTCStreamMixingTypeByClient = 1,
};
/** 
 * @type keytype
 * @brief 转推直播事件
 */
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingEvent) {
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamMixingEventBase = 0,
    /** 
     * @brief 请求发起转推直播任务
     */
    ByteRTCStreamMixingEventStart = 1,
    /** 
     * @brief 发起转推直播任务成功
     */
    ByteRTCStreamMixingEventStartSuccess = 2,
    /** 
     * @brief 发起转推直播任务失败
     */
    ByteRTCStreamMixingEventStartFailed = 3,
    /** 
     * @brief 请求更新转推直播任务配置
     */
    ByteRTCStreamMixingEventUpdate = 4,
    /** 
     * @brief 成功更新转推直播任务配置
     */
    ByteRTCStreamMixingEventUpdateSuccess = 5,
    /** 
     * @brief 更新转推直播任务配置失败
     */
    ByteRTCStreamMixingEventUpdateFailed = 6,
    /** 
     * @brief 请求结束转推直播任务
     */
    ByteRTCStreamMixingEventStop = 7,
    /** 
     * @brief 结束转推直播任务成功
     */
    ByteRTCStreamMixingEventStopSuccess = 8,
    /** 
     * @brief 结束转推直播任务失败
     */
    ByteRTCStreamMixingEventStopFailed = 9,
    /** 
     * @brief 更新转推直播任务配置的请求超时
     */
    ByteRTCStreamMixingEventChangeMixType = 10,
    /** 
     * @brief 得到客户端合流音频首帧
     */
    ByteRTCStreamMixingEventFirstAudioFrameByClientMixer = 11,
    /** 
     * @brief 收到客户端合流视频首帧
     */
    ByteRTCStreamMixingEventFirstVideoFrameByClientMixer = 12,
    /** 
     * @brief 更新转推直播任务配置超时
     */
    ByteRTCStreamMixingEventUpdateTimeout = 13,
    /** 
     * @brief 发起转推直播任务配置超时
     */
    ByteRTCStreamMixingEventStartTimeout = 14,
    /** 
     * @brief 合流布局参数错误
     */
    ByteRTCStreamMixingEventRequestParamError = 15,
    /** 
     * @brief 合流加图片
     */
    ByteRTCStreamMixingEventMixImage = 16,
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @brief 单通合唱事件
     */
    ByteRTCStreamMixingEventSingleWayChorus = 17,
};
/** 
 * @type keytype
 * @brief 客户端合流回调视频格式。设置为系统不支持的格式时，自动回调系统默认格式。
 */
typedef NS_ENUM(NSUInteger, ByteRTCClientMixVideoFormat) {
    /** 
     * @brief YUV I420。Android、Windows 默认回调格式。支持系统：Android、Windows。
     */
    ByteRTCClientMixVideoFormatI420 = 0,
    /** 
     * @brief OpenGL GL_TEXTURE_2D 格式纹理。支持系统：安卓。
     */
    ByteRTCClientMixVideoFormatTexture2D = 1,
    /** 
     * @brief CVPixelBuffer BGRA。iOS 默认回调格式。支持系统: iOS。
     */
    ByteRTCClientMixVideoFormatCVPixelBufferBGRA = 2,
    /** 
     * @brief YUV NV12。macOS 默认回调格式。支持系统: macOS。
     */
    /**
     * {en}
     * @brief YUV NV12 format. The default format for macOS. Supported system: macOS.
     */
    ByteRTCClientMixVideoFormatNV12 = 3,
};

/** 
 * @type keytype
 * @brief 视频编码格式。
 */
typedef NS_ENUM(NSUInteger, ByteRTCTranscodingVideoCodec) {
    /** 
     * @brief H.264 格式，默认值。
     */
    ByteRTCTranscodingVideoCodecH264 = 0,
    /** 
     * @brief ByteVC1 格式。
     */
    ByteRTCTranscodingVideoCodecH265 = 1,
};

/** 
 * @type errorcode
 * @brief 单流转推直播错误码
 */
typedef NS_ENUM(NSUInteger, ByteRTCSingleStreamPushEvent) {
    /**
     * @hidden for internal use only
     */
    ByteRTCSingleStreamPushEventBase = 0,
    /** 
    * @brief 开始推流。
    */
   ByteRTCSingleStreamPushEventStart = 1,
    /** 
    * @brief 推流成功。
    */
   ByteRTCSingleStreamPushEventStartSuccess = 2,
    /** 
    * @brief 推流失败。
    */
   ByteRTCSingleStreamPushEventStartFailed = 3,
    /** 
     * @brief 停止推流。
     */
    ByteRTCSingleStreamPushEventStop = 4,
    /** 
    * @brief 单流转推直播任务处理超时，请检查网络状态并重试。
    */
   ByteRTCSingleStreamPushEventTimeout = 5,
    /** 
     * @brief 参数错误。
     */
    ByteRTCSingleStreamPushEventParamError = 6,
};

/** 
 * @type keytype
 * @brief 订阅媒体的类型
 */
typedef NS_ENUM(NSInteger, ByteRTCSubscribeMediaType) {
    /** 
     * @brief 既不订阅音频，也不订阅视频
     */
    ByteRTCSubscribeMediaTypeNone = 0,
    /** 
     * @brief 只订阅音频，不订阅视频
     */
    ByteRTCSubscribeMediaTypeAudioOnly = 1,
    /** 
     * @brief 只订阅视频，不订阅音频
     */
    ByteRTCSubscribeMediaTypeVideoOnly = 2,
    /** 
     * @brief 同时订阅音频和视频
     */
    ByteRTCSubscribeMediaTypeAudioAndVideo = 3,
};

/** 
 * @type keytype
 * @brief 暂停/恢复接收远端的媒体流类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCPauseResumControlMediaType) {
    /** 
     * @brief 只控制音频，不影响视频
     */
    ByteRTCControlMediaTypeAudio = 0,
    /** 
     * @brief 只控制视频，不影响音频
     */
    ByteRtcControlMediaTypeVideo = 1,
    /** 
     * @brief 同时控制音频和视频
     */
    ByteRtcControlMediaTypeAudioAndVideo = 2,
};

/** 
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 视频输入类型
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaInputType) {
    /** 
     * @brief 自定义采集。  <br>
     *        设置完成后方可直接向 SDK 推送视频帧。
     */
    ByteRTCMediaInputTypeExternal = 0,
    /** 
     * @brief 内部 SDK 采集。  <br>
     *        此设置仅切换至内部采集，你需继续调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 开启内部采集。
     */
    ByteRTCMediaInputTypeInternal = 1
};

/** 
 * @type keytype
 * @brief 视频输入源类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSourceType) {
    /** 
     * @brief 自定义采集视频源
     */
    ByteRTCVideoSourceTypeExternal = 0,
    /** 
     * @brief 内部采集视频源
     */
    ByteRTCVideoSourceTypeInternal = 1,
    /** 
     * @brief 自定义编码视频源。  <br>
     *        SDK 不会自动生成多路流，你需要自行生成并推送多路流
     */
    ByteRTCVideoSourceTypeEncodedManualSimulcast = 2,
    /** 
     * @brief 自定义编码视频源。  <br>
     *        你仅需推送分辨率最大的一路编码后视频流，SDK 将自动转码生成多路小流
     */
    ByteRTCVideoSourceTypeEncodedAutoSimulcast = 3
};

/** 
 * @type keytype
 * @brief 视频解码方式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDecoderConfig) {
    /** 
     * @brief 开启 SDK 内部解码，只回调解码后的数据
     */
    ByteRTCVideoDecoderConfigRaw = 0,
    /** 
     * @brief 开启自定义解码，只回调解码前数据
     */
    ByteRTCVideoDecoderConfigEncode = 1,
    /** 
     * @brief 开启 SDK 内部解码，同时回调解码前和解码后的数据
     */
    ByteRTCVideoDecoderConfigBoth = 2
};

/** 
 * @type keytype
 * @brief 虚拟背景类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCVirtualBackgroundSourceType){
    /** 
     * @brief 使用纯色背景替换视频原有背景。
     */
    ByteRTCVirtualBackgroundSourceTypeColor = 0,
    /** 
     * @brief 使用自定义图片替换视频原有背景。
     */
    ByteRTCVirtualBackgroundSourceTypeImage = 1
};

/** 
 * @type keytype
 * @brief 摄像头类型
 */
typedef NS_ENUM(NSInteger, ByteRTCCameraID) {
    /** 
     * @brief 前置摄像头
     */
    ByteRTCCameraIDFront = 0,
    /** 
     * @brief 后置摄像头
     */
    ByteRTCCameraIDBack = 1,
    /** 
     * @brief 外接摄像头
     */
    ByteRTCCameraIDExternal = 2,
    /** 
     * @brief 无效值
     */
    ByteRTCCameraIDInvalid = 3,
};
/** 
 * @type errorcode
 * @brief 转推直播错误码
 */
typedef NS_ENUM(NSInteger, ByteRtcTranscoderErrorCode) {
    /** 
     * @brief 推流成功。
     */
    ByteRtcTranscoderErrorCodeOK = 0,
    /** 
     * @brief 未定义的合流错误
     */
    ByteRtcTranscoderErrorCodeBase = 1090,
    /** 
     * @brief 客户端 SDK 检测到无效推流参数。
     */
    ByteRtcTranscoderErrorCodeInvalidParam = 1091,
    /** 
     * @brief 状态错误，需要在状态机正常状态下发起操作
     */
    ByteRtcTranscoderErrorCodeInvalidState = 1092,
    /** 
     * @brief 无效操作
     */
    ByteRtcTranscoderErrorCodeInvalidOperator = 1093,
    /** 
     * @brief 转推直播任务处理超时，请检查网络状态并重试
     */
    ByteRtcTranscoderErrorCodeTimeOut = 1094,
    /** 
     * @brief 服务端检测到错误的推流参数
     */
    ByteRtcTranscoderErrorCodeInvalidParamByServer = 1095,
    /** 
     * @brief 对流的订阅超时
     */
    ByteRtcTranscoderErrorCodeSubTimeoutByServer = 1096,
    /** 
     * @brief 合流服务端内部错误。
     */
    ByteRtcTranscoderErrorCodeInvalidStateByServer = 1097,
    /** 
     * @brief 合流服务端推 CDN 失败。
     */
    ByteRtcTranscoderErrorCodeAuthenticationByCDN = 1098,
    /** 
     * @brief 服务端接收信令超时，请检查网络状态并重试。
     */
    ByteRtcTranscoderErrorCodeTimeoutBySignaling = 1099,
    /** 
     * @brief 图片合流失败。
     */
    ByteRtcTranscoderErrorCodeMixImageFail = 1100,
    /** 
     * @brief 服务端未知错误。
     */
    ByteRtcTranscoderErrorCodeUnKnownErrorByServer = 1101,
    /** 
     * @hidden internal use only
     * @valid since 3.50
     * @brief 缓存未同步。
     */
    ByteRtcTranscoderErrorCodeCacheSyncWorse = 1102,
    /**
     * @hidden for internal use only
     */
    ByteRtcTranscoderErrorCodeMax = 1199,
};

/** 
 * @type keytype
 * @brief 本地录制的媒体类型
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingType) {
    /** 
     * @brief 只录制音频
     */
    RecordAudioOnly = 0,
    /** 
     * @brief 只录制视频
     */
    RecordVideoOnly = 1,
    /** 
     * @brief 同时录制音频和视频
     */
    RecordVideoAndAudio = 2,
};

/** 
 * @type keytype
 * @brief 屏幕采集媒体类型
 */
typedef NS_ENUM(NSInteger, ByteRTCScreenMediaType) {
    /** 
     *@brief 只采集视频数据
     */
    ByteRTCScreenMediaTypeVideoOnly = 0,
    /** 
     *@brief 只采集音频数据
     */
    ByteRTCScreenMediaTypeAudioOnly = 1,
    /** 
     *@brief 音视频数据都采集
     */
    ByteRTCScreenMediaTypeVideoAndAudio = 2
};

/** 
 * @type keytype
 * @brief 屏幕采集对象的类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCScreenCaptureSourceType) {
    /** 
     * @brief 类型未知
     */
    ByteRTCScreenCaptureSourceTypeUnknown = 0,
    /** 
     * @brief 应用程序的窗口
     */
    ByteRTCScreenCaptureSourceTypeWindow = 1,
    /** 
     * @brief 桌面
     */
    ByteRTCScreenCaptureSourceTypeScreen = 2
};
/** 
 * @type keytype
 * @region 屏幕共享
 * @brief 内部采集屏幕视频流时，是否采集鼠标信息。
 */
typedef NS_ENUM(NSUInteger, ByteRTCMouseCursorCaptureState) {
    /** 
     * @brief 采集鼠标信息。
     */
    ByteRTCMouseCursorCaptureStateOn,
    /** 
     * @brief 不采集鼠标信息。
     */
    ByteRTCMouseCursorCaptureStateOff,
};
/** 
 * @type keytype
 * @brief 屏幕共享时的边框高亮设置。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCHighlightConfig: NSObject
/** 
 * @brief 是否显示高亮边框，默认显示。
 */
@property (assign, nonatomic) BOOL enableHighlight;
/** 
 * @brief 边框的颜色, 颜色格式为十六进制 ARGB: 0xAARRGGB。
 */
@property (assign, nonatomic) uint32_t borderColor;
/** 
 * @brief 边框的宽度，单位：像素。
 */
@property (assign, nonatomic) int borderWidth;
@end

/** 
 * @type keytype
 * @brief 相机补光灯状态
 */
typedef NS_ENUM(NSInteger, ByteRTCTorchState) {
    /** 
     * @brief 相机补光灯关闭
     */
    ByteRTCTorchStateOff = 0,
    /** 
     * @brief 相机补光灯打开
     */
    ByteRTCTorchStateOn = 1,
};

/** 
 * @type keytype
 * @brief 当前视频设备类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDeviceType) {
    /** 
     * @brief 未知视频设备
     */
    ByteRTCVideoDeviceTypeUnknown = -1,
    /** 
     * @brief 视频渲染设备类型
     */
    ByteRTCVideoDeviceTypeRenderDevice = 0,
    /** 
     * @brief 视频采集设备类型
     */
    ByteRTCVideoDeviceTypeCaptureDevice = 1,
    /** 
     * @brief 屏幕流视频设备
     */
    ByteRTCVideoDeviceTypeScreenCaptureDevice = 2
};

/** 
 * @type keytype
 * @brief 媒体流类型
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCMediaStreamType) {
    /** 
     * @brief 只控制音频
     */
    ByteRTCMediaStreamTypeAudio = (1 << 0),
    /** 
     * @brief 只控制视频
     */
    ByteRTCMediaStreamTypeVideo = (1 << 1),
    /** 
     * @brief 同时控制音频和视频
     */
    ByteRTCMediaStreamTypeBoth = ByteRTCMediaStreamTypeAudio | ByteRTCMediaStreamTypeVideo,
};

/** 
 * @type keytype
 * @brief 占发布端原始帧率的比例
 */
typedef NS_ENUM(NSUInteger, ByteRTCFrameRateRatio) {
    /** 
     * @brief 100%
     */
    ByteRTCFrameRateRatioOrigin = 0,
    /** 
     * @brief 50%
     */
    ByteRTCFrameRateRatioHalf = 1,
    /** 
     * @brief 25%
     */
    ByteRTCFrameRateRatioQuater = 2,
};

/** 
 * @type keytype
 * @brief 视频旋转模式
 */
typedef NS_ENUM(NSUInteger, ByteRTCVideoRotationMode) {
    /** 
     * @brief App 方向
     */
    ByteRTCVideoRotationModeFollowApp = 0,
    /** 
     * @brief 重力方向
     */
    ByteRTCVideoRotationModeFollowGSensor = 1,
};

/** 
 * @type keytype
 * @brief 人像属性检测参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectConfig : NSObject
/** 
 * @brief 是否开启年龄检测。
 */
@property (assign, nonatomic) BOOL enableAgeDetect;
/** 
 * @brief 是否开启性别检测。
 */
@property (assign, nonatomic) BOOL enableGenderDetect;
/** 
 * @brief 是否开启表情检测。
 */
@property (assign, nonatomic) BOOL enableEmotionDetect;
/** 
 * @brief 是否开启吸引力检测。
 */
@property (assign, nonatomic) BOOL enableAttractivenessDetect;
/** 
 * @brief 是否开启开心程度检测。
 */
@property (assign, nonatomic) BOOL enableHappinessDetect;
@end

/** 
 * @type keytype
 * @brief 人像属性检测信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectInfo : NSObject
/** 
* @brief 预测年龄，取值范围 (0, 100)。
*/
@property (assign, nonatomic) float age;
/** 
* @brief 预测为男性的概率，取值范围 (0.0, 1.0)。
*/
@property (assign, nonatomic) float boyProb;
/** 
* @brief 预测的吸引力分数，取值范围 (0, 100)。
*/
@property (assign, nonatomic) float attractive;
/** 
* @brief 预测的微笑程度，取值范围 (0, 100)。
*/
@property (assign, nonatomic) float happyScore;
/** 
* @brief 预测的伤心程度，取值范围 (0, 100)。
*/
@property (assign, nonatomic) float sadScore;
/** 
* @brief 预测的生气程度，取值范围 (0, 100)。
*/
@property (assign, nonatomic) float angryScore;
/** 
* @brief 预测的吃惊程度，取值范围 (0, 100)。
*/
@property (assign, nonatomic) float surpriseScore;
/** 
* @brief 预测的情绪激动程度，取值范围 (0, 100)。
*/
@property (assign, nonatomic) float arousal;
/** 
* @brief 预测的情绪正负程度，取值范围 (-100, 100)。
*/
@property (assign, nonatomic) float valence;
@end

/** 
 * @type keytype
 * @brief 人像属性检测结果
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectResult : NSObject
/** 
 * @brief 特征识别结果 <br>
 *        + 0：识别成功 <br>
 *        + !0：识别失败 <br>
 */
@property (assign, nonatomic) int detectResult;
/** 
 * @brief 识别到的人脸数量。
 */
@property (assign, nonatomic) int faceCount;

/** 
 * @brief 特征识别信息。数组的长度和检测到的人脸数量一致。参看 ByteRTCExpressionDetectInfo{@link #ByteRTCExpressionDetectInfo}。
 */
@property (nonatomic, copy) NSArray<ByteRTCExpressionDetectInfo *> * _Nonnull detectInfo;

@end

/** 
 * @type keytype
 * @brief 矩形区域，用于指定屏幕区域。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRectangle : NSObject
/** 
 * @brief 矩形区域左上角的 x 坐标。
 */
@property(assign, nonatomic) int x;
/** 
 * @brief 矩形区域左上角的 y 坐标。
 */
@property(assign, nonatomic) int y;
/** 
 * @brief 矩形宽度，单位：px。
 */
@property(assign, nonatomic) int width;
/** 
 * @brief 矩形高度，单位：px。
 */
@property(assign, nonatomic) int height;
@end
/** 
 * @type keytype
 * @brief 人脸检测结果
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFaceDetectionResult : NSObject
/** 
 * @brief 人脸检测结果 <br>
 *        + 0：检测成功 <br>
 *        + !0：检测失败。详见[错误码](https://www.volcengine.com/docs/6705/102042)。
 */
@property(assign, nonatomic) int detectResult;
/** 
 * @brief 原始图片宽度(px)
 */
@property(assign, nonatomic) int imageWidth;
/** 
 * @brief 原始图片高度(px)
 */
@property(assign, nonatomic) int imageHeight;
/** 
 * @brief 识别到人脸的矩形框。数组的长度和检测到的人脸数量一致。参看 ByteRTCRectangle{@link #ByteRTCRectangle}。
 */
@property(nonatomic, copy) NSArray<ByteRTCRectangle *> * _Nullable faces;
/** 
 * @brief 进行人脸识别的视频帧的时间戳。
 */
@property(assign, nonatomic) CMTime frameTimestamp;

@end
/** 
 * @type keytype
 * @brief 视频帧渲染设置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCanvas : NSObject
/** 
 * @brief 本地视图句柄
 */
@property(strong, nonatomic) ByteRTCView* _Nullable view;
/** 
 * @brief 渲染模式，参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @brief 用于填充画布空白部分的背景颜色。取值范围是 `[0x00000000, 0xFFFFFFFF]`,格式为 BGR。默认值是 `0x00000000`。其中，透明度设置无效。
 */
@property(assign, nonatomic) NSInteger backgroundColor;
@end

/** 
 * @type keytype
 * @brief 视频帧附加的数据,视频解码后获得的附加数据
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFrameExtendedData : NSObject
/** 
 * @brief 数据类型，详见 ByteRTCDataFrameType{@link #ByteRTCDataFrameType}。
 */
@property(assign, nonatomic) ByteRTCDataFrameType frameType;
/** 
 * @brief 附加数据
 */
@property(strong, nonatomic) NSData * _Nullable extendedData;
/** 
 * @brief 附加数据长度
 */
@property(assign, nonatomic) NSInteger extendedDataLen;
@end

NS_ASSUME_NONNULL_BEGIN

/** 
 * @type keytype
 * @brief 视频流参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoSolution: NSObject
/** 
 * @brief 视频分辨率
 */
@property(nonatomic, assign) CGSize videoSize;
/** 
 * @brief 视频预设帧率
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief 最高编码码率（千比特每秒）。建议使用 `-1`，SDK 会自动根据分辨率和帧率适配合适的码率。
 */
@property(nonatomic, assign) NSInteger maxKbps;
/** 
 * @brief 最低编码码率（千比特每秒）
 */
@property(nonatomic, assign) NSInteger minKbps;
/** 
 * @brief 视频编码质量策略，参见 ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
 */
@property(nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end

/** 
 * @type keytype
 * @brief 视频采集参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCaptureConfig: NSObject
/** 
 * @brief 视频采集模式，参看 ByteRTCVideoCapturePreference{@link #ByteRTCVideoCapturePreference}
 */
@property(nonatomic, assign) ByteRTCVideoCapturePreference preference;

/** 
 * @brief 视频采集分辨率
 */
@property(nonatomic, assign) CGSize videoSize;
/** 
 * @brief 视频采集帧率，单位：fps。
 */
@property(nonatomic, assign) NSInteger frameRate;
@end

/** 
 * @type keytype
 * @brief 流属性。
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCStream <NSObject>
/** 
 * @brief 发布此流的用户 ID 。  <br>
 */
@property(nonatomic, copy, readonly) NSString * userId;
/** 
 * @brief 此流是否为共享屏幕流。  <br>
 */
@property(nonatomic, assign, readonly) BOOL isScreen;
/** 
 * @brief 此流是否包括视频流。  <br>
 */
@property(nonatomic, assign, readonly) BOOL hasVideo;
/** 
 * @brief 流是否包括音频流。  <br>
 */
@property(nonatomic, assign, readonly) BOOL hasAudio;
/** 
 * @brief 视频流的分辨率信息。  <br>
 *         当远端用户调用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} 方法发布多个配置的视频流时，此处会包含该用户发布的所有视频流的属性信息。  <br>
 *         参看 ByteRTCVideoSolution{@link #ByteRTCVideoSolution}。  <br>
 */
@property(nonatomic, copy, readonly) NSArray<ByteRTCVideoSolution *> * videoStreamDescriptions;
/** 
 * @brief 视频流最大分辨率，在开启多分辨率发布订阅时，回调发布端能支持的最大发布分辨率。
 */
@property(nonatomic, retain, readonly) ByteRTCVideoSolution *maxVideoStreamDescription;
@end

/** 
 * @type keytype
 * @brief 流信息
 */
@interface ByteRTCStreamEx : NSObject <ByteRTCStream>
/** 
 * @brief 用户ID
 */
@property(nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief 流是否为共享屏幕流。
 */
@property(nonatomic, assign) BOOL isScreen;
/** 
 * @brief 该路流中是否包含视频
 */
@property(nonatomic, assign) BOOL hasVideo;
/** 
 * @brief 该路流中是否包含音频
 */
@property(nonatomic, assign) BOOL hasAudio;
/** 
 * @brief 视频流的分辨率信息，详见 ByteRTCVideoSolution{@link #ByteRTCVideoSolution} 类。
 *         用户可以通过调用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中所有分辨率的相关信息。
 */
@property(nonatomic, copy, nullable) NSArray<ByteRTCVideoSolution *> *videoStreamDescriptions;
/** 
 * @brief 视频流最大分辨率，在开启多分辨率发布订阅时，回调发布端能支持的最大发布分辨率。
 */
@property(nonatomic, retain, nullable) ByteRTCVideoSolution *maxVideoStreamDescription;
@end

/** 
 * @type keytype
 * @brief 订阅流的参数配置。用户手动订阅一路音视频流所使用的订阅配置参数。  <br>
 *         用户关闭自动订阅功能，使用手动订阅模式时，通过调用 `subscribeStream` 方法订阅音视频流，调用时传入的参数即为此数据类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeConfig: NSObject
/** 
 * @brief 是否是屏幕流。  <br>
 *         用户通过设置此参数，订阅该远端用户发布的屏幕共享流或非屏幕共享流。 YES 为订阅屏幕共享流，NO 为订阅非屏幕共享流，默认值为 YES 。  <br>
 */
@property(nonatomic, assign) BOOL isScreen;
/** 
 * @brief 是否订阅视频。  <br>
 *         用户通过设置此参数，选择是否订阅远端流中的视频。 YES 为订阅视频，NO 为不订阅视频，默认值为 YES 。  <br>
 */
@property(nonatomic, assign) BOOL subscribeVideo;
/** 
 * @brief 是否订阅音频。  <br>
 *         用户通过设置此参数，选择是否订阅远端流中的音频。YES 为订阅音频，NO 为不订阅音频，默认值为 YES 。  <br>
 */
@property(nonatomic, assign) BOOL subscribeAudio;
/** 
 * @brief 订阅的视频流分辨率下标。  <br>
 *         用户可以通过调用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} 方法发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>
 */
@property(nonatomic, assign) NSInteger videoIndex;
/** 
 * @brief 订阅的视频流时域分层，默认值为 0。  <br>
 */
@property(nonatomic, assign) NSInteger svcLayer;
/** 
 * @brief 订阅的宽度信息，单位：px，默认值为 0。 <br>
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief 订阅的高度信息，单位：px， 默认值为0。
 */
@property(nonatomic, assign) NSInteger height;
/**
 * @hidden for internal use only
 */
@property(nonatomic, assign) NSInteger subVideoIndex;
/** 
 * @brief 期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。  <br>
 *        当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
 *        仅码流支持 SVC 分级编码特性时方可生效。
 */
@property (nonatomic, assign) NSInteger framerate;


@end

NS_ASSUME_NONNULL_END

/** 
 * @type keytype
 * @brief 待 SDK 编码的视频数据
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrame : NSObject
/** 
 * @brief 视频帧格式，参考 ByteRTCVideoPixelFormat {@link #ByteRTCVideoPixelFormat}
 */
@property(assign, nonatomic) int format;
/** 
 * @brief 获取视频内容类型，参看 ByteRTCVideoContentType{@link #ByteRTCVideoContentType}
 */
@property(assign, nonatomic) ByteRTCVideoContentType contentType;
/** 
 * @brief 当前帧的时间戳信息
 */
@property(assign, nonatomic) CMTime time;
/** 
 * @deprecated since 3.45 and will be deleted in 3.51, use strideInPixels instead.
 */
@property(assign, nonatomic) int stride DEPRECATED_MSG_ATTRIBUTE("use strideInPixels instead");
/** 
 * @brief 每一行像素占用的字节数
 */
@property(assign, nonatomic) int strideInPixels;
/** 
 * @brief 视频帧宽度
 */
@property(assign, nonatomic) int width;
/** 
 * @brief 视频帧高度
 */
@property(assign, nonatomic) int height;
/** 
 * @brief CVPixelBufferRef 类型的数据，当 format 为 kPixelFormatCVPixelBuffer 时有效
 */
@property(assign, nonatomic) CVPixelBufferRef _Nullable textureBuf;
/** 
 * @brief 视频帧内存块首地址
 */
@property(strong, nonatomic) NSData * _Nullable dataBuf;
/** 
 * @brief 视频帧左侧被裁剪的尺寸（像素）
 */
@property(assign, nonatomic) int cropLeft;
/** 
 * @brief 视频帧上部被裁剪的尺寸（像素）
 */
@property(assign, nonatomic) int cropTop;
/** 
 * @brief 视频帧右侧被裁剪的尺寸（像素）
 */
@property(assign, nonatomic) int cropRight;
/** 
 * @brief 视频帧底部被裁剪的尺寸（像素）
 */
@property(assign, nonatomic) int cropBottom;
/** 
 * @brief 视频帧旋转角度：0, 90, 180, 270
 */
@property(assign, nonatomic) ByteRTCVideoRotation rotation;
/** 
 * @hidden for internal use only
 * @brief 视频镜像信息
 */
@property(assign, nonatomic) int flip;
/** 
 * @brief 颜色空间
 */
@property(assign, nonatomic) ByteRTCColorSpace colorSpace;
/** 
 * @brief 视频帧的摄像头信息，参考 ByteRTCCameraID{@link #ByteRTCCameraID}
 */
@property(assign, nonatomic) ByteRTCCameraID cameraId;
/** 
 * @brief 视频帧附加的sei数据
 */
@property(strong, nonatomic) NSData * _Nullable extendedData;

/** 
 * @brief 视频帧附加的roi数据
 */
@property(strong, nonatomic) NSData * _Nonnull supplementaryInfo;
@end

/** 
 * @type keytype
 * @brief 视频帧信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCEncodedVideoFrame : NSObject
/** 
 * @brief 视频编码类型。参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
@property(assign, nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief 视频帧类型。参看 ByteRTCVideoPictureType{@link #ByteRTCVideoPictureType}
 */
@property(assign, nonatomic) ByteRTCVideoPictureType pictureType;
/** 
 * @brief 视频采集时间戳，单位：微秒
 */
@property(assign, nonatomic) SInt64 timestampUs;
/** 
 * @brief 视频编码时间戳，单位：微秒
 */
@property(assign, nonatomic) SInt64 timestampDtsUs;
/** 
 * @brief 视频帧宽，单位：px
 */
@property(assign, nonatomic) int width;
/** 
 * @brief 视频帧高，单位：px
 */
@property(assign, nonatomic) int height;
/** 
 * @brief 视频帧旋转角度。参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 */
@property(nonatomic, assign) ByteRTCVideoRotation rotation;
/** 
 * @brief 视频帧数据指针地址
 */
@property(strong, nonatomic) NSData * _Nonnull data;

@end
/** 
 * @type keytype
 * @brief 图片合流相关参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscoderLayoutRegionDataParam : NSObject
/** 
 * @brief 原始图片的宽度，单位为 px。
 */
@property (assign, nonatomic) NSInteger imageWidth;
/** 
 * @brief 原始图片的高度，单位为 px。
 */
@property (assign, nonatomic) NSInteger imageHeight;
@end

/** 
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息。
 *        开启转推直播功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 * @notes  <br>
 *         + 视频流对应区域左上角的实际坐标是通过画面尺寸和归一化比例相乘，并四舍五入取整得到的。假如：Canvas.Width = 1920, Region.LocationX = 0.33，那么该画布左上角的横坐标为 634（1920×0.33=633.6，四舍五入取整）。
 *         + 视频流对应区域宽度和高度的像素值是通过画面尺寸和归一化比例相乘，四舍五入取整，并向上转换为偶数得到的。假如：Canvas.Width = 1920, Region.WidthProportion = 0.21，那么该画布横向宽度为 404px（1920x0.21=403.2，四舍五入取整后，再向上转换为偶数）。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingRegion : NSObject
/** 
 * @brief 视频流发布用户的用户 ID 。必填。
 */
@property(copy, nonatomic) NSString * _Nonnull uid;
/** 
 * @brief 图片或视频流所在房间的房间 ID。必填。
 *        如果此图片或视频流是通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief 视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
 */
@property(assign, nonatomic) CGFloat x;
/** 
 * @brief 视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
 */
@property(assign, nonatomic) CGFloat y;
/** 
 * @brief 视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
 */
@property(assign, nonatomic) CGFloat width;
/** 
 * @brief 视频流对应区域高度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
 */
@property(assign, nonatomic) CGFloat height;
/** 
 * @brief 用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。
 */
@property(assign, nonatomic) NSInteger zOrder;
/** 
 *  @brief 是否为本地用户
 */
@property(assign, nonatomic) BOOL localUser;
/** 
 *  @brief 是否为屏幕流，默认为NO
 */
@property(assign, nonatomic) BOOL screenStream;
/** 
 * @brief 透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。
 */
@property(assign, nonatomic) CGFloat alpha;
/** 
 * @brief 圆角半径相对画布宽度的比例。默认值为 `0.0`。
 * @notes 做范围判定时，首先根据画布的宽高，将 `width`，`height`，和 `cornerRadius` 分别转换为像素值：`width_px`，`height_px`，和 `cornerRadius_px`。然后判定是否满足 `cornerRadius_px < min(width_px/2, height_px/2)`：若满足，则设置成功；若不满足，则将 `cornerRadius_px` 设定为 `min(width_px/2, height_px/2)`，然后将 `cornerRadius` 设定为 `cornerRadius_px` 相对画布宽度的比例值。
 */
@property(assign, nonatomic) CGFloat cornerRadius;
/** 
 * @brief 合流内容控制。默认值为 `ByteRTCTranscoderContentControlTypeHasAudioAndVideo`，参看 ByteRTCTranscoderContentControlType{@link #ByteRTCTranscoderContentControlType} 。
 */
@property (assign, nonatomic) ByteRTCTranscoderContentControlType contentControl;
/** 
 * @brief 图片或视频流的缩放模式，参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}。默认值为 1。
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @brief 合流布局区域类型。参看 ByteRTCTranscoderLayoutRegionType{@link #ByteRTCTranscoderLayoutRegionType}。
 */
@property (assign, nonatomic) ByteRTCTranscoderLayoutRegionType type;
/** 
 * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
 */
@property (strong, nonatomic) NSData * _Nullable data;
/** 
 * @type keytype
 * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 ByteRTCTranscoderLayoutRegionDataParam{@link #ByteRTCTranscoderLayoutRegionDataParam}。
 */
@property (strong, nonatomic) ByteRTCTranscoderLayoutRegionDataParam * _Nullable dataParam;
/** 
 * @type keytype
 * @brief 空间位置。参看 Position{@link #Position}。
 */
@property (strong, nonatomic) Position * _Nullable spatialPosition;

@end

/** 
 * @type keytype
 * @brief 视频流合流整体布局信息。
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingLayout : NSObject
/** 
 * @brief 合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。
 *        值不合法或未设置时，自动使用默认值。
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/** 
 * @brief 用户布局信息列表。每条流的具体布局参看 ByteRTCVideoCompositingRegion{@link #ByteRTCVideoCompositingRegion}。
 *        值不合法或未设置时，自动使用默认值。
 */
@property(copy, nonatomic) NSArray<ByteRTCVideoCompositingRegion *> * _Nonnull regions;
/** 
 * @brief 透传的 App 数据，长度不超过 4KB。
 */
@property(copy, nonatomic) NSString *_Nonnull appData;
@end

/** 
 * @type keytype
 * @brief 视频转码配置参数。值不合法或未设置时，自动使用默认值。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingVideoConfig : NSObject
/** 
 * @brief 视频编码格式，参看 ByteRTCTranscodingVideoCodec{@link #ByteRTCTranscodingVideoCodec}。默认值为 `0`。
 *        本参数不支持过程中更新。
 */
@property(assign, nonatomic) ByteRTCTranscodingVideoCodec codec;
/** 
 * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。
 *        设置值为非偶数时，自动向上取偶数。
 */
@property(assign, nonatomic) NSInteger width;
/** 
 * @brief 合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。
 *        设置值为非偶数时，自动向上取偶数。
 */
@property(assign, nonatomic) NSInteger height;
/** 
 * @brief 合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。
 */
@property(assign, nonatomic) NSInteger fps;
/** 
 * @brief 视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。
 *        本参数不支持过程中更新。
 */
@property(assign, nonatomic) NSInteger gop;
/** 
 * @brief 合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。
 */
@property(assign, nonatomic) NSInteger kBitRate;
/** 
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @brief 是否使用低延时特性。
 */
@property(assign, nonatomic) BOOL lowLatency;
/** 
 * @brief 是否在合流中开启B帧，仅服务端合流支持.
 */
@property(assign, nonatomic) BOOL bFrame;
@end

/** 
 * @type keytype
 * @brief 音频转码配置参数。值不合法或未设置时，自动使用默认值。
 *        本参数不支持过程中更新。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingAudioConfig : NSObject
/** 
 * @brief 音频编码格式。
 * @param codec 音频编码格式，参看 ByteRTCTranscodingAudioCodec{@link #ByteRTCTranscodingAudioCodec}。默认值为 `0`。
 */
@property(assign, nonatomic) ByteRTCTranscodingAudioCodec codec;
/** 
 * @brief 音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。
 */
@property(assign, nonatomic) NSInteger sampleRate;
/** 
 * @brief 音频声道数。可取 1（单声道）、2（双声道），默认值为 2。
 */
@property(assign, nonatomic) NSInteger channels;
/** 
 * @brief 音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。
 */
@property(assign, nonatomic) NSInteger kBitRate;
/** 
 * @brief AAC 编码规格，参看 ByteRTCAACProfile{@link #ByteRTCAACProfile}。默认值为 `0`。
 */
@property(assign, nonatomic) ByteRTCAACProfile profile;
/** 
 * @deprecated since 3.45 and will be deleted in 3.51.
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteRTCAACProfile) aacProfile;
@end

/** 
 * @type keytype
 * @brief 推流 CDN 的空间音频参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingSpatialConfig : NSObject
/** 
 * @brief 是否开启推流 CDN 时的空间音频效果。
 * @notes 当你启用此效果时，你需要设定推流中各个 ByteRTCTranscodingSpatialConfig{@link #ByteRTCTranscodingSpatialConfig} 的 `spatialPosition` 值，实现空间音频效果。
 */
@property(assign, nonatomic) BOOL enableSpatialRender;
/** 
 * @brief 听众的空间位置。参看 Position{@link #Position}。<br>
 *        听众指收听来自 CDN 的音频流的用户。
 */
@property (strong, nonatomic) Position * _Nullable audienceSpatialPosition;
/** 
 * @brief 听众的空间朝向。参看 HumanOrientation{@link #HumanOrientation}。<br>
 *        听众指收听来自 CDN 的音频流的用户。
 */
@property(strong, nonatomic) HumanOrientation * _Nullable audienceSpatialOrientation;

@end
/** 
 * @type keytype
 * @brief 客户端合流参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingClientMixParam : NSObject
/** 
 * @brief 是否使用原始视频帧。默认为 False。
 */
@property(assign, nonatomic) BOOL clientMixUseOriginalFrame;
/** 
 * @brief 客户端合流是否使用音频混音，默认为 true。
 */
@property(assign, nonatomic) BOOL clientMixUseAudioMixer;
/** 
 * @brief 客户端合流回调视频格式，参看 ByteRTCClientMixVideoFormat{@link #ByteRTCClientMixVideoFormat}。
 */
@property(assign, nonatomic) ByteRTCClientMixVideoFormat clientMixVideoFormat;
@end
/** 
 * @hidden internal use only
 * @valid since 3.50
 * @type keytype
 * @brief 转推直播单通同步参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingSyncControlParam : NSObject
/** 
 * @brief 是否在转推直播时，启用单通模式。默认为 false，不启用。
 *        启用单通模式时，RTC SDK 会对指定的多个用户的媒体流进行同步处理，再合流后推送到 CDN，但基准流所属用户不会播放来自其他用户的媒体流。你需要设定以下参数。
 *        非单通模式时，RTC SDK 不会对媒体流进行同步处理，只是简单合流后推送到 CDN。以下参数设定无效。
 */
@property(assign, nonatomic) BOOL syncStream;
/** 
 * @brief 在进行同步处理时，基准流所属用户的 ID。默认为空。
 */
@property(copy, nonatomic) NSString * _Nullable syncBaseUser;
/** 
 * @brief 在进行同步处理时，缓存音视频流的最大长度。单位为毫秒。默认值为 0。
 * @notes 参与转推直播的这些媒体流延迟越高，应该将此值设置的越大。但此值越大，因缓存媒体流造成的内存占用也会更大。推荐值为 `2000`。
 */
@property(assign, nonatomic) NSInteger syncQueueLengthMs;
/** 
 * @brief 是否通过 RTC SDK 进行转推直播。默认为 True。
 *        如果选择 `False`，你会通过 onCacheSyncVideo:withDataFrame:withUids:taskId:{@link #LiveTranscodingDelegate#onCacheSyncVideo:withDataFrame:withUids:taskId:} 收到同步的帧，你可以使用此视频帧，自行实现合流转推。
 */
@property(assign, nonatomic) BOOL syncClientVideoNeedMix;
/** 
 * @brief 是否只开启时间戳发送而不做对齐和媒体数据回调。默认为 False。
 *        在单通合唱双人场景下，主唱应设置为 False，副唱应设置为 True。
 *        在单通合唱多人场景下，主唱和所有副唱都应设置为 False。
 */
@property(assign, nonatomic) BOOL syncOnlySendPts;
@end

/** 
 * @type keytype
 * @brief 转推直播配置参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLiveTranscoding : NSObject
/** 
 * @brief 合流类型，详见 ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType} 数据类型。
 * 本参数不支持过程中更新。
 */
@property(assign, nonatomic) ByteRTCStreamMixingType expectedMixingType;
/** 
 * @brief 视频流合流整体布局信息。
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。详见 ByteRTCVideoCompositingLayout{@link #ByteRTCVideoCompositingLayout} 数据类型。
 */
@property(strong, nonatomic) ByteRTCVideoCompositingLayout * _Nonnull layout;
/** 
 * @brief 视频转码配置参数。详见 ByteRTCTranscodingVideoConfig{@link #ByteRTCTranscodingVideoConfig} 数据类型。
 */
@property(strong, nonatomic) ByteRTCTranscodingVideoConfig * _Nonnull video;
/** 
 * @brief 音频转码配置参数，参看 ByteRTCTranscodingAudioConfig{@link #ByteRTCTranscodingAudioConfig}。
 */
@property(strong, nonatomic) ByteRTCTranscodingAudioConfig * _Nonnull audio;
/** 
 * @brief 客户端合流配置。详见 ByteRTCTranscodingClientMixParam{@link #ByteRTCTranscodingClientMixParam} 。
 */
@property(strong, nonatomic) ByteRTCTranscodingClientMixParam * _Nullable clientMixParam;
/** 
 * @hidden for internal use only
 * @brief 转推同步配置。详见 ByteRTCTranscodingSyncControlParam{@link #ByteRTCTranscodingSyncControlParam} 。
 */
@property(strong, nonatomic) ByteRTCTranscodingSyncControlParam * _Nullable syncControlParam;
/** 
 * @hidden(macOS)
 * @brief 转推 CDN 空间音频配置。详见 ByteRTCTranscodingSpatialConfig{@link #ByteRTCTranscodingSpatialConfig} 。
 */
@property(strong, nonatomic) ByteRTCTranscodingSpatialConfig * _Nonnull spatialConfig;

/** 
 * @hidden for internal use only
 * @brief 动态扩展自定义参数。
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/** 
 * @hidden for internal use only
 * @brief 业务透传鉴权信息
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable authInfo;
/** 
 * @brief 推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。
 *        本参数不支持过程中更新。
 */
@property(copy, nonatomic) NSString * _Nullable url;
/** 
 * @brief 推流房间 ID。`roomId` 和 `userId` 长度相加不得超过 126 字节。
 *        本参数不支持过程中更新。
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief 推流用户 ID。`roomId` 和 `userId` 长度相加不得超过 126 字节。
 *        本参数不支持过程中更新。
 */
@property(copy, nonatomic) NSString * _Nonnull userId;
/** 
 * @brief 获取默认转推直播配置参数。
 * @return 转推直播配置参数，参看 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}。
 */
+ (instancetype _Nonnull)defaultTranscoding;
@end
/** 
 * @type keytype
 * @brief 单流转推直播配置参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPushSingleStreamParam : NSObject
/** 
 * @brief 推流地址
 */
@property(copy, nonatomic) NSString * _Nullable url;
/** 
 * @brief 媒体流所在的房间 ID
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief 媒体流所属的用户 ID
 */
@property(copy, nonatomic) NSString * _Nullable userId;
/** 
 * @brief 媒体流是否为屏幕流。
 */
@property(nonatomic, assign) BOOL isScreen;
@end

/** 
 * @type keytype
 * @brief 视频订阅配置信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeVideoConfig : NSObject
/** 
 * @brief 订阅的视频流分辨率下标。  <br>
 *        当远端用户通过调用 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
 *        默认值为 0，即订阅第一路流。  <br>
 *        如果不想更改之前的设置，可以输入 -1。  <br>
 */
@property(assign, nonatomic) NSInteger videoIndex;
/** 
 * @brief 远端用户优先级，参看 ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}，默认值为 0。
 */
@property(assign, nonatomic) NSInteger priority;
@end

/** 
 * @type keytype
 * @brief 性能回退相关数据
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSourceWantedData : NSObject
/** 
 * @brief 推荐视频输入宽
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief 推荐视频输入高
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief 推荐视频输入帧率
 */
@property(nonatomic, assign) NSInteger frameRate;
@end

/** 
 * @type keytype
 * @brief 流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamSwitchEvent : NSObject
/** 
 * @brief 订阅的音视频流的发布者的用户 ID。
 */
@property(nonatomic, copy) NSString * _Nonnull uid;
/** 
 * @brief 流是否是屏幕流
 */
@property(nonatomic, assign) BOOL isScreen;
/** 
 * @brief 流切换前订阅视频流的分辨率对应的索引
 */
@property(nonatomic, assign) NSInteger beforeVideoIndex;
/** 
 * @brief 流切换后订阅视频流的分辨率对应的索引
 */
@property(nonatomic, assign) NSInteger afterVideoIndex;
/** 
 * @brief 流切换前是否有视频流
 */
@property(nonatomic, assign) BOOL beforeVideoEnabled;
/** 
 * @brief 流切换后是否有视频流
 */
@property(nonatomic, assign) BOOL afterVideoEnabled;
/** 
 * @brief 流切换原因，详见 ByteRTCFallbackOrRecoverReason{@link #ByteRTCFallbackOrRecoverReason}。
 */
@property(nonatomic, assign) ByteRTCFallbackOrRecoverReason reason;
@end

/** 
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51, use ByteVideoSinkDelegate{@link #ByteVideoSinkDelegate} instead.
 * @type callback
 * @brief 自定义的视频渲染
 */
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate")
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkProtocol <NSObject>
@required
/** 
 * @type callback
 * @brief 初始化渲染器
 * @return  <br>
 *         + YES: 自定义的渲染器初始化完成  <br>
 *         + NO: 自定义的渲染器初始化失败，不继续往下运行  <br>
 * @notes 初始化渲染器的时候会回调这个方法
 */
- (BOOL)shouldInitialize DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");;

/** 
 * @type callback
 * @brief 启动渲染器
 * @notes 在开启渲染功能的时候会回调这个方法
 */
- (void)shouldStart DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @type callback
 * @brief 停止渲染器
 * @notes 在停止渲染功能的时候会回调这个方法
 */
- (void)shouldStop DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @type callback
 * @brief 释放渲染器
 * @notes 渲染器即将被废弃的时候会回调这个方法
 */
- (void)shouldDispose DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @type callback
 * @brief 获取PixelFormat格式
 * @return Buffer 类型，{@link #ByteRTCVideoSinkPixelFormat}
 * @notes 通过该方法的返回值，告知 SDK PixelFormat 的格式
 */
- (ByteRTCVideoPixelFormat)pixelFormat DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @type callback
 * @brief 输出视频的 PixelBuffer
 * @param pixelBuffer 视频的 PixelBuffer
 * @param rotation 视频旋转角度，{@link #ByteRTCVideoRotation}
 * @param cameraId 视频的相机Id, {@link #ByteRTCCameraID}
 * @param extendedData 视频帧附加的数据,视频解码后获得的附加数据
 * @notes 通过该方法获取视频的 PixelBuffer
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
                 cameraId:(ByteRTCCameraID) cameraId
             extendedData:(NSData * _Nullable)extendedData DEPRECATED_MSG_ATTRIBUTE("Please use ByteVideoSinkDelegate");

/**
 * @hidden
 */
- (int)getRenderElapse;
@end

/** 
 * @type keytype
 * @brief 自定义视频渲染器
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkDelegate <NSObject>
@required
/** 
 * @type api
 * @brief 输出视频的 PixelBuffer
 * @param pixelBuffer 视频的 PixelBuffer
 * @param rotation 视频旋转角度，参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 * @param contentType 视频内部类型 参看 ByteRTCVideoContentType{@link #ByteRTCVideoContentType}
 * @param extendedData 视频解码后获得的附加数据
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
                 contentType:(ByteRTCVideoContentType)contentType
             extendedData:(NSData * _Nullable)extendedData;
/**
 * @hidden
 */
- (int)getRenderElapse;
@end

/** 
 * @hidden for internal use only
 * @type callback
 * @brief 外部渲染数据的消费接口
 */
@protocol ByteRTCVideoFrameConsumerObserver <NSObject>
/** 
 * @brief 输出 yuv420 数据
 * @param ocFrame 数据 Buffer
 * @param width 视频宽度
 * @param rotation 视频旋转角度
 * @param timestamp 时间戳
 */
- (void)consumeYUV420Buffer:(CVPixelBufferRef _Nullable)ocFrame
    width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
/** 
 * @brief 输出 RGBA 数据
 * @param ocFrame 数据 Buffer
 * @param width 视频宽度
 * @param rotation 视频旋转角度
 * @param timestamp 时间戳
 */
- (void)consumeRGBABuffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width
    rotation:(NSInteger)rotation timestamp:(long)timestamp;
@end

/** 
 * @type callback
 * @region 视频管理
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoFrameObserver <NSObject>
/** 
 * @brief 本地屏幕流的视频帧数据回调
 * @param frame 本地屏幕视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
- (void)onLocalScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame;
/** 
 * @brief 本地视频流的视频帧数据回调
 * @param frame 本地视频流的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
- (void)onLocalVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

/** 
 * @brief 远端屏幕流的视频帧数据回调
 * @param frame 远端屏幕的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid 远端屏幕共享用户ID
 * @param room 对应流的房间 id
 */
- (void)onRemoteScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid
    room:(NSString * _Nullable)room;
/** 
 * @brief 远端视频流的视频帧数据回调
 * @param frame 远端视频流的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid 远端屏幕共享用户ID
 * @param room 对应流的房间 id
 */
- (void)onRemoteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid
    room:(NSString * _Nullable)room;

/**
 * @hidden for internal use only
 */
- (void)OnMergeFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;

@end

/** 
 * @type keytype
 * @brief 视频处理配置参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoPreprocessorConfig : NSObject
/** 
 * @brief 视频帧的像素格式，参看 ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}。
 */
@property(nonatomic, assign) ByteRTCVideoPixelFormat required_pixel_format;

@end

/** 
  * @type callback
  * @region 视频处理
  */
 BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoProcessorDelegate <NSObject>

/** 
 * @type api
 * @region 视频处理
 * @brief 获取 RTC SDK 采集得到的视频帧，根据 registerLocalVideoProcessor:withConfig:{@link #ByteRTCVideo#registerLocalVideoProcessor:withConfig:} 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。
 * @param src_frame RTC SDK 采集得到的视频帧，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return 经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @notes 如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。
 */
- (ByteRTCVideoFrame* _Nullable)processVideoFrame:(ByteRTCVideoFrame* _Nonnull)src_frame;

@end
/** 
 * @type keytype
 * @region 视频管理
 * @brief 屏幕采集设置参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureParam : NSObject
/** 
 * @brief 屏幕采集宽度
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief 屏幕采集高度
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief 屏幕采集帧率，单位 fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief 发送屏幕采集码率，单位 kbps
 */
@property(nonatomic, assign) NSInteger bitrate;
/** 
 * @brief 视频最小编码码率, 单位 kbps。编码码率不会低于 `minBitrate`。<br>
 *        默认值为 `0`。<br>
 *        范围：[0, bitrate)，当 `bitrate` < `minBitrate` 时，为适配码率模式。<br>
 *        以下情况，设置本参数无效：<br>
 *        + 当 `bitrate` 为 `0` 时，不对视频流进行编码发送。<br>
 *        + 当 `bitrate` < `0` 时，适配码率模式。
 */
@property(nonatomic, assign) NSInteger minBitrate;
/** 
 * @brief 采集区域
 */
@property(nonatomic, assign) CGRect regionRect;
/** 
 * @brief 是否采集鼠标
 */
@property(nonatomic, assign) ByteRTCMouseCursorCaptureState mouseCursorCaptureState;
/** 
 * @brief 屏幕过滤设置
 */
@property (strong, nonatomic) NSArray<NSNumber *> * _Nullable excludedWindowList;
/** 
 * @brief 采集区域的边框高亮设置，参看 ByteRTCHighlightConfig{@link #ByteRTCHighlightConfig}。
 */
@property (strong, nonatomic) ByteRTCHighlightConfig * _Nonnull highlightConfig;
@end
/** 
 * @type keytype
 * @brief 屏幕采集对象的具体信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureSourceInfo : NSObject
/** 
 * @brief 屏幕分享时，共享对象的类型，参看 ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}
 */
@property (assign, nonatomic) ByteRTCScreenCaptureSourceType sourceType;
/** 
 * @brief 屏幕分享时，共享对象的 ID。
 */
@property (assign, nonatomic) intptr_t sourceId;
/** 
 * @brief 屏幕分享时共享对象的名称。<br>
 */
@property (copy, nonatomic) NSString * _Nullable sourceName;
/** 
 * @brief 共享的应用窗体所属应用的名称<br>
 *        当共享对象为应用窗体时有效 <br>
 */
@property (copy, nonatomic) NSString * _Nullable application;
/** 
 * @brief 共享的应用窗体所属应用进程的 pid<br>
 *        当共享对象为应用窗体时有效 <br>
 */
 @property (assign, nonatomic) int pid;
/** 
 * @brief 共享的屏幕是否为主屏。<br>
 *        当共享对象为屏幕时有效 <br>
 */
 @property (assign, nonatomic) BOOL primaryMonitor;
/** 
 * @brief 屏幕共享对象的坐标。多显示器的场景下，屏幕坐标系统以主屏左上角为原点 (0, 0)，向右向下扩展。
 */
@property (assign, nonatomic) CGRect regionRect;

@end

/** 
 * @type keytype
 * @region 视频管理
 * @brief 屏幕采集设置参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenParam : NSObject
/** 
 * @brief 编码帧率,单位为 fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief 编码码率，小于 0 时 SDK 会根据高宽自适应码率, 单位 kbps
 */
@property(nonatomic, assign) NSInteger bitrate;
@end

/** 
 * @type keytype
 * @brief 虚拟背景对象。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVirtualBackgroundSource: NSObject
/** 
 * @brief 虚拟背景类型，详见 ByteRTCVirtualBackgroundSourceType{@link #ByteRTCVirtualBackgroundSourceType} 。
 */
@property(nonatomic, assign) ByteRTCVirtualBackgroundSourceType sourceType;
/** 
 * @brief 纯色背景使用的颜色。<br>
 *        格式为 0xAARRGGBB 。
 */
@property int sourceColor;
/** 
 * @brief 自定义背景图片的绝对路径。
 *       + 支持的格式为 jpg、jpeg、png。  <br>
 *       + 图片分辨率超过 1080P 时，图片会被等比缩放至和视频一致。  <br>
 *       + 图片和视频宽高比一致时，图片会被直接缩放至和视频一致。  <br>
 *       + 图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。  <br>
 *       + 自定义图片带有局部透明效果时，透明部分由黑色代替。
 */
@property(nonatomic) NSString* _Nullable sourcePath;
@end

/** 
 * @type callback
 * @region 视频数据回调
 * @brief 本地视频帧监测器
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCLocalEncodedVideoFrameObserver<NSObject>
 @optional
/** 
 * @type callback
 * @region 视频数据回调
 * @brief 调用 registerLocalEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerLocalEncodedVideoFrameObserver:} 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。
 * @param streamIndex 本地视频帧类型，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frame 本地视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 */
- (void)onLocalEncodedVideoFrame:(ByteRTCStreamIndex) streamIndex
    Frame:(ByteRTCEncodedVideoFrame * _Null_unspecified)frame;
@end

#pragma mark - ByteRTCEngineExternalVideoEncoderEventHandler

/** 
 * @type callback
 * @brief 自定义编码帧回调类
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCExternalVideoEncoderEventHandler<NSObject>
@required
/** 
 * @type callback
 * @region 视频管理
 * @brief 提示自定义编码帧可以开始推送的回调。  <br>
 *        收到该回调后，你即可调用 pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:{@link #ByteRTCVideo#pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:} 向 SDK 推送自定义编码视频帧
 * @param streamIndex 可以推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStart:(ByteRTCStreamIndex)streamIndex;
@required
/** 
 * @type callback
 * @region 视频管理
 * @brief 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧
 * @param streamIndex 需停止推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStop:(ByteRTCStreamIndex)streamIndex;
@required
/** 
 * @type callback
 * @region 视频管理
 * @brief 当自定义编码流的帧率或码率发生变化时，触发该回调
 * @param streamIndex 发生变化的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex 对应编码流的下标
 * @param fps 变化后的帧率，单位：fps
 * @param bitRateKps 变化后的码率，单位：kbps
 */
- (void)onRateUpdate:(ByteRTCStreamIndex)streamIndex
      withVideoIndex:(NSInteger)videoIndex
             withFps:(NSInteger)fps
         withBitRate:(NSInteger)bitRateKps;
@required
/** 
 * @type callback
 * @region 视频管理
 * @brief 提示流发布端需重新生成关键帧的回调
 * @param streamIndex 远端编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex 对应编码流的下标
 */
- (void)onRequestKeyFrame:(ByteRTCStreamIndex)streamIndex
           withVideoIndex:(NSInteger)videoIndex;
@end

#pragma mark - ByteRTCEngineRemoteEncodedVideoFrameObserver

/** 
 * @type callback
 * @region 视频管理
 * @brief 远端编码后视频数据监测器
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCRemoteEncodedVideoFrameObserver<NSObject>
@required
/** 
 * @type callback
 * @region 视频数据回调
 * @brief 调用 registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerRemoteEncodedVideoFrameObserver:} 后，SDK 监测到远端编码后视频数据时，触发该回调
 * @param streamKey 收到的远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoFrame 收到的远端视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 */
- (void)onRemoteEncodedVideoFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                   withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;
@end

/** 
 * @type keytype
 * @brief 视频帧基础信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrameInfo : NSObject
/** 
 * @brief 视频帧的宽度（像素）
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief 视频帧的高度（像素）
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief 视频帧顺时针旋转角度。参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}。
 */
@property(nonatomic, assign) ByteRTCVideoRotation rotation;
@end

#pragma mark - LiveTranscodingDelegate

/** 
 * @type callback
 * @region 转推直播
 * @brief 转推直播观察者。  <br>
 */
@protocol LiveTranscodingDelegate <NSObject>
/** 
 * @type callback
 * @region 转推直播
 * @brief 是否具有推流能力。  <br>
 *       + false：不具备推流能力（默认值）  <br>
 *       + true：具备推流能力
 * @notes 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。
 */
- (BOOL)isSupportClientPushStream;
/** 
 * @type callback
 * @region 转推直播
 * @brief 转推直播状态回调
 * @param event 转推直播任务状态，参看 ByteRTCStreamMixingEvent{@link #ByteRTCStreamMixingEvent}。
 * @param taskId 转推直播任务 ID。
 * @param Code 转推直播错误码，参看 ByteRtcTranscoderErrorCode{@link #ByteRtcTranscoderErrorCode} 和 ByteRTCTranscodingError{@link #ByteRTCTranscodingError}。
 * @param mixType 转推直播类型，参看 ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType}。
 */
- (void)onStreamMixingEvent:(ByteRTCStreamMixingEvent)event
                  taskId:(NSString *_Nonnull)taskId
                      error:(ByteRtcTranscoderErrorCode)Code
                    mixType:(ByteRTCStreamMixingType)mixType;

@optional
/** 
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流音频 PCM 回调
 * @param audioFrame PCM 编码的合流音频数据帧，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @param timeStamp 时间戳，单位毫秒。
 * @param taskId 转推直播任务 ID。
 * @notes 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
 */
- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame timestamp:(int64_t)timeStamp taskId:(NSString *_Nonnull)taskId;

/** 
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流视频 YUV 回调
 * @param videoFrame YUV 合流视频数据帧，参看 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}。
 * @param taskId 转推直播任务 ID。
 * @notes 收到该回调的周期取决于视频的帧率。
 */
- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame taskId:(NSString *_Nonnull)taskId;
/** 
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流视频 SEI 数据
 * @param dataFrame SEI 数据，详见 ByteRTCFrameExtendedData {@link #ByteRTCFrameExtendedData}。
 * @param taskId 转推直播任务 ID。
 */
- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame taskId:(NSString *_Nonnull)taskId;
/** 
 * @hidden for internal use only
 * @type callback
 * @valid since 3.50
 * @brief 同步视频帧回调。仅在通过 ByteRTCTranscodingSyncControlParam{@link #ByteRTCTranscodingSyncControlParam} 设置启用单通模式，且其中 `syncClientVideoNeedMix=False` 时收到此回调。
 * @param videoFrame 同步视频帧数组，与 uids 对应。参看 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}。
 * @param dataFrame SEI 数据。参看 ByteRTCFrameExtendedData{@link #ByteRTCFrameExtendedData}。
 * @param uids 同步视频帧对应的 uid 数组。
 * @param task_id 转推直播任务 ID。
 */
- (void)onCacheSyncVideo:(NSArray<ByteRTCVideoFrame *> *_Nonnull)videoFrames 
           withDataFrame:(NSArray<ByteRTCFrameExtendedData*> *_Nonnull)dataFrames
                withUids:(NSArray<NSString*>*_Nonnull)uids 
                  taskId:(NSString *_Nonnull)task_id;
@end
/** 
 * @type callback
 * @region 转推直播
 * @brief 单流转推直播观察者。  <br>
 */
@protocol ByteRTCPushSingleStreamToCDNObserver <NSObject>
/** 
 * @type callback
 * @region 转推直播
 * @brief 单流转推直播状态回调
 * @param event 任务状态, 参看 ByteRTCSingleStreamPushEvent{@link #ByteRTCSingleStreamPushEvent}.
 * @param taskId 任务 ID
 * @param Code 错误码，参看 ByteRtcTranscoderErrorCode{@link #ByteRtcTranscoderErrorCode}。
 */
- (void)onStreamPushEvent:(ByteRTCSingleStreamPushEvent)event
                  taskId:(NSString *_Nonnull)taskId
                      error:(NSInteger)Code;

@end

/** 
 * @type callback
 * @region 视频特效
 * @brief 人脸检测结果回调观察者
 */
@protocol ByteRTCFaceDetectionObserver <NSObject>
/** 
 * @type callback
 * @region 视频特效
 * @brief 特效 SDK 进行人脸检测结果的回调。 <br>
 *        调用 enableFaceDetection:withInterval:withModelPath:{@link #ByteRTCVideoEffect#enableFaceDetection:withInterval:withModelPath:} 注册了 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver} ，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。
 * @param result 人脸检测结果, 参看 ByteRTCFaceDetectionResult{@link #ByteRTCFaceDetectionResult}。
 */
- (void)onFaceDetectResult:(ByteRTCFaceDetectionResult * _Nonnull)result;
/** 
 * @hidden for intrnal use only
 * @type callback
 * @region 视频特效
 * @brief 特效 SDK 进行人像属性检测结果的回调。 <br>
 *        调用 registerFaceDetectionObserver:withInterval:{@link #ByteRTCVideoEffect#registerFaceDetectionObserver:withInterval:} 注册了 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}，并调用 setVideoEffectExpressionDetect:{@link #ByteRTCVideo#setVideoEffectExpressionDetect:} 开启人像属性检测后，你会收到此回调。
 * @param result 人像属性检测结果, 参看 ByteRTCExpressionDetectResult{@link #ByteRTCExpressionDetectResult}。
 */
- (void)onExpressionDetectResult:(ByteRTCExpressionDetectResult * _Nonnull)result;
@end

#pragma mark - ByteRTCEngineMediaMetadataObserver

/** 
 * @hidden
 * @deprecated since 3.26 and will be deleted in 3.51, use sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} instead.
 * @type callback
 * @brief 使用内部源视频采集时,配置和获取附加数据接口
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCMediaMetadataObserver <NSObject>
@required
/** 
 * @type callback
 * @region 视频数据回调
 * @brief 当 SDK 准备发送一个视频帧时，会回调该接口，以确定是否需要在该视频帧中添加 metadata
 * @param timestamp 待添加 metadata 视频帧的时间戳，单位微秒
 * @return 待发送的数据，大小不能超过 1024bytes
 * @notes  <br>
 *       + 返回 null 代表不需要添加 metadata  <br>
 *       + 回调中不能做长时间逻辑处理，以免影响视频卡顿  <br>
 */
- (NSData *_Nullable)videoFrameMediaMetaDataAtTime:(NSTimeInterval)timestamp;

@optional
/** 
 * @type callback
 * @region 视频数据回调
 * @brief 当 SDK 收到的视频帧包含 medatada 时，会回调该接口
 * @param uid 当前帧所属的用户ID
 * @param extendedData metadata
 * @param timestamp 包含 metadata 视频帧的时间戳，单位为微秒
 * @notes 回调中不能做长时间逻辑处理，以免影响视频卡顿
 */
- (void)receiveVideoFrameFromUID:(NSString * _Nonnull)uid
    withExtendedData:(NSData* _Nullable)extendedData atTimestamp:(NSTimeInterval)timestamp;
@end
/** 
 * @type keytype
 * @brief 视频编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoEncoderConfig: NSObject
/** 
 * @brief 视频宽度，单位：px
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief 视频高度，单位：px
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief 视频帧率，单位：fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief 最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。  <br>
 *        设为 -1 即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。 <br>
 *        设为 0 则不对视频流进行编码发送。<br>
 *        344 及以上版本，内部采集时默认值为 -1，344 以前版本无默认值，需手动设置。
 */
@property(nonatomic, assign) NSInteger maxBitrate;
/** 
 * @brief 视频最小编码码率, 单位 kbps。编码码率不会低于 `minBitrate`。<br>
 *        默认值为 `0`。<br>
 *        范围：[0, maxBitrate)，当 `maxBitrate` < `minBitrate` 时，为适配码率模式。<br>
 *        以下情况，设置本参数无效：<br>
 *        + 当 `maxBitrate` 为 `0` 时，不对视频流进行编码发送。<br>
 *        + 当 `maxBitrate` < `0` 时，适配码率模式。
 */
@property(nonatomic, assign) NSInteger minBitrate;
/** 
 * @brief 编码策略偏好，默认为帧率优先。参看 ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}。
 */
@property(nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end

/** 
 * @type keytype
 * @brief 屏幕流编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenVideoEncoderConfig: NSObject
/** 
 * @brief 屏幕帧宽度，单位：px。
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief 屏幕帧高度，单位：px。
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief 屏幕流帧率，单位：fps。
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief 最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。
 *        设为 -1 即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。
 *        设为 0 则不对视频流进行编码发送。
 *        3.44 及以上版本，内部采集时默认值为 -1，3.44 以前版本无默认值，需手动设置。
 */
@property(nonatomic, assign) NSInteger maxBitrate;
/** 
 * @brief 最小编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。
 *        最小编码码率必须小于或等于最大编码，否则不对视频流进行编码发送。
 */
@property(nonatomic, assign) NSInteger minBitrate;
/** 
 * @brief 屏幕流编码模式。参见 ByteRTCScreenVideoEncoderPreference{@link #ByteRTCScreenVideoEncoderPreference}。
 */
@property(nonatomic, assign) ByteRTCScreenVideoEncoderPreference encoderPreference;
@end

/** 
 * @type keytype
 * @brief 远端视频帧信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoConfig : NSObject
/** 
 * @brief 期望订阅的最高帧率，单位：fps，默认值为 0 即满帧订阅，设为大于 0 的值时开始生效。  <br>
 *        当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
 *        仅码流支持 SVC 分级编码特性时方可生效。
 */
@property (nonatomic, assign) int framerate;
/** 
 * @brief 视频宽度，单位：px
 */
@property(nonatomic, assign) int  width;
/** 
 * @brief 视频高度，单位：px
 */
@property(nonatomic, assign) int   height;
@end
/** 
 * @type keytype
 * @brief 房间参数配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomConfig : NSObject
/** 
 * @brief 房间模式，参看 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}，默认为普通音视频通话模式，进房后不可更改。
 */
@property(nonatomic) ByteRTCRoomProfile profile;
/** 
 * @brief 是否自动发布音视频流，默认为自动发布。 <br>
 *        创建和加入多房间时，只能将其中一个房间设置为自动发布。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。<br>
 *        若调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。
 */
@property(assign, nonatomic) BOOL isAutoPublish;
/** 
 * @brief 是否自动订阅音频流，默认为自动订阅。<br>
 *        包含主流和屏幕流。
 */
@property(assign, nonatomic) BOOL isAutoSubscribeAudio;
/** 
 * @brief 是否自动订阅主视频流，默认为自动订阅。<br>
 *        包含主流和屏幕流。
 */
@property(assign, nonatomic) BOOL isAutoSubscribeVideo;
/** 
 * @brief 远端视频流参数，参看 ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}
 */
@property(nonatomic, strong) ByteRTCRemoteVideoConfig * _Nonnull remoteVideoConfig;
@end
/** 
 * @type keytype
 * @brief 公共流裁剪信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSourceCropInfo : NSObject
/** 
 * @brief 裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的比例，取值范围[0.0, 1.0)
 */
@property(assign, nonatomic) CGFloat LocationX;
/** 
 * @brief 裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的比例，取值范围[0.0, 1.0)
 */
@property(assign, nonatomic) CGFloat LocationY;
/** 
 * @brief 裁剪后得到的视频帧宽度相对于裁剪前整体画面的比例，取值范围(0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat WidthProportion;
/** 
 * @brief 裁剪后得到的视频帧高度相对于裁剪前整体画面的比例，取值范围(0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat HeightProportion;
@end
/** 
 * @type keytype
 * @brief 合成公共流的每条流的布局信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamRegion : NSObject
/** 
 * @brief 用户 ID。必填。  <br>
 * 服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。
 */
@property(copy, nonatomic) NSString * _Nonnull userId;
/** 
 * @brief 房间 ID。必填。  <br>
 *        服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief 背景图片地址
 */
@property(copy, nonatomic) NSString * _Nonnull alternateImage;
/** 
 * @brief 用户视频布局相对画布左侧的偏移量， 相对值。范围[0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat x;
/** 
 * @brief 用户视频布局相对画布顶端的偏移量， 相对值。范围[0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat y;
/** 
 * @brief 用户视频宽度相对用户原始视频宽度的比例，相对值。范围[0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat width;
/** 
 * @brief 用户视频高度相对用户原始视频高度的比例，相对值。范围[0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat height;
/** 
 * @brief 用户视频布局在画布中的层级，0为底层，值越大越上层。范围[0 - 100]
 */
@property(assign, nonatomic) NSInteger zOrder;
/** 
 * @brief 透明度，必填。可选范围为 [0.0, 1.0]。
 */
@property(assign, nonatomic) CGFloat alpha;
/** 
 * @brief 推流内容控制。默认为0。<br>
 *      0: 输出的混流包含音视频<br>
 *      1: 只包含音频<br>
 *      2: 表示只包含视频
 */
@property(assign, nonatomic) NSInteger mediaType;
/** 
 * @brief 推流媒体类型<br>
 *        0：普通音视频流<br>
 *        1: 屏幕流
 */
@property(assign, nonatomic) NSInteger streamType;
/** 
 * @brief 视频显示模式。详见 ByteRTCRenderMode{@link #ByteRTCRenderMode} 数据类型。  <br>
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @brief 视频裁剪信息。 详见 ByteRTCSourceCropInfo{@link #ByteRTCSourceCropInfo}。
 */
@property(strong, nonatomic) ByteRTCSourceCropInfo * _Nonnull sourceCrop;
@end

/** 
 * @type keytype
 * @brief 公共流的合流布局。必填
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamLayout : NSObject
/** 
 * @brief 布局模式。可选：<br>
 *        + `0`: 自动布局。默认值 <br>
 *        + `2`: 自定义布局。
 */
@property(assign, nonatomic) NSInteger layoutMode;
/** 
 * @brief 插帧模式。<br>
 *         + `0`: 补最后一帧<br>
 *         + `1`: 补背景图片，如果没有设置背景图片则补黑帧
 */
@property(assign, nonatomic) NSInteger interpolationMode;
/** 
 * @brief 画布的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/** 
 * @brief 背景图片地址
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundImage;
/** 
 * @brief 用户布局信息列表。每一个该类型对象为一路单独的视频流的布局信息。
 */
@property(copy, nonatomic) NSArray<ByteRTCPublicStreamRegion *> * _Nonnull regions;
@end

/** 
 * @type keytype
 * @brief 公共流的视频编码参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamVideoConfig : NSObject
/** 
 * @brief 公共流视频宽度，必填。单位为 px，范围为 [2, 1920]，必须是偶数。
 */
@property(assign, nonatomic) NSInteger width;
/** 
 * @brief 公共流视频高度，必填。单位为 px，范围为 [16, 1280]，必须是偶数。
 */
@property(assign, nonatomic) NSInteger height;
/** 
 * @brief 公共流视频帧率。必填<br>
 *        范围：[1, 60] <br>
 */
@property(assign, nonatomic) NSInteger fps;
/** 
 * @brief 视频码率，必填<br>
 *        范围：[1,10000000]
 *        单位为 bps
 */
@property(assign, nonatomic) NSInteger bitrate;
@end

/** 
 * @hidden currently not available
 * @type keytype
 * @brief 公共流的音频编码参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamAudioConfig : NSObject
/** 
 * @brief 音频采样率，必填。单位为 Hz。可选取值：16000, 32000, 44100 和 48000
 */
@property(assign, nonatomic) NSInteger sampleRate;
/** 
 * @brief 音频声道数，必填。<br>
 * + 1: 单声道<br>
 * + 2: 双声道
 */
@property(assign, nonatomic) NSInteger channels;
/** 
 * @brief 音频码率，必填。单位为 kbps。<br>
 * 正整数，可选取值：16, 32, 64。
 */
@property(assign, nonatomic) NSInteger bitrate;
@end

/** 
 * @type keytype
 * @brief 水印图片相对视频流的位置和大小。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoByteWatermark: NSObject
/** 
 * @brief 水印图片相对视频流左上角的横向偏移与视频流宽度的比值，取值范围为 [0,1)。
 */
@property(assign, nonatomic) float x;
/** 
 * @brief 水印图片相对视频流左上角的纵向偏移与视频流高度的比值，取值范围为 [0,1)。
 */
@property(assign, nonatomic) float y;
/** 
 * @brief 水印图片宽度与视频流宽度的比值，取值范围 [0,1)。
 */
@property(assign, nonatomic) float width;
/** 
 * @brief 水印图片高度与视频流高度的比值，取值范围为 [0,1)。
 */
@property(assign, nonatomic) float height;
@end

/** 
 * @type keytype
 * @brief 水印参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoWatermarkConfig: NSObject
/** 
 * @brief 水印是否在视频预览中可见，默认可见。
 */
@property(nonatomic, assign) BOOL visibleInPreview;
/** 
 * @brief 横屏时的水印位置和大小，参看 ByteRTCVideoByteWatermark{@link #ByteRTCVideoByteWatermark}。
 */
@property(strong, nonatomic) ByteRTCVideoByteWatermark * _Nonnull positionInLandscapeMode;
/** 
 * @brief 竖屏时的水印位置和大小，参看 ByteRTCVideoByteWatermark{@link #ByteRTCVideoByteWatermark}。
 */
@property(strong, nonatomic) ByteRTCVideoByteWatermark * _Nonnull positionInPortraitMode;
@end

/** 
 * @type keytype
 * @brief 公共流参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreaming : NSObject
/** 
 * @brief 视频流公共流整体布局参数，必填。详见 ByteRTCPublicStreamLayout{@link #ByteRTCPublicStreamLayout}
 */
@property(strong, nonatomic) ByteRTCPublicStreamLayout * _Nonnull layout;
/** 
 * @brief 公共流视频编码参数。详见 ByteRTCPublicStreamVideoConfig{@link #ByteRTCPublicStreamVideoConfig}。
 */
@property(strong, nonatomic) ByteRTCPublicStreamVideoConfig * _Nonnull video;
/** 
 * @hidden currently not available
 * @brief 公共流音频编码参数。详见 ByteRTCPublicStreamAudioConfig{@link #ByteRTCPublicStreamAudioConfig}
 */
@property(strong, nonatomic) ByteRTCPublicStreamAudioConfig * _Nonnull audio;
/** 
 * @hidden currently not available
 * @brief 设置媒体流所在房间的房间 ID。服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。必填。
 */
@property(copy, nonatomic) NSString * _Nullable roomId;
/** 
 * @brief 获取默认的公共流转码配置属性。
 * @return 包含默认配置的 ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming} 结构体
 */
+ (instancetype _Nonnull)defaultPublicStreaming;
@end
/** 
 * @type api
 * @hidden(iOS)
 * @region 视频设备管理
 * @brief 主要用于枚举、设置视频采集设备
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoDeviceManager : NSObject
/** 
 * @type api
 * @region 视频设备管理
 * @brief 获取视频采集设备列表。
 * @return ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateVideoCaptureDevices;
/** 
 * @type api
 * @region 视频设备管理
 * @brief 获取当前 SDK 正在使用的视频采集设备信息
 * @param deviceID 视频设备 ID
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + !0：方法调用失败  <br>
 */
- (int)getVideoCaptureDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/** 
 * @type api
 * @region 视频设备管理
 * @brief 设置当前视频采集设备
 * @param deviceID 视频设备 ID。调用 enumerateVideoCaptureDevices{@link #ByteRTCVideoDeviceManager#enumerateVideoCaptureDevices} 获取全量视频设备。
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + !0：方法调用失败  <br>
 */
- (int)setVideoCaptureDevice:(NSString* _Nonnull)deviceID;
@end
/** 
 * @type callback
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSnapshotCallbackDelegate <NSObject>
@required
/** 
 * @type callback
 * @brief 调用 takeLocalSnapshot:callback:{@link #ByteRTCVideo#takeLocalSnapshot:callback:} 截取视频画面时，收到此回调。
 * @param taskId 本地截图任务的编号。和 takeLocalSnapshot:callback:{@link #ByteRTCVideo#takeLocalSnapshot:callback:} 的返回值一致。
 * @param streamIndex 截图的视频流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param image 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。
 * @param errorCode 截图错误码：<br>
 *        + 0: 成功 <br>
 *        + -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br>
 *        + -2: 截图错误。流无效。
 */
- (void)onTakeLocalSnapshotResult:(NSInteger) taskId
                      streamIndex:(ByteRTCStreamIndex)streamIndex
                            image:(ByteRTCImage * _Nullable)image
                        errorCode:(NSInteger)errorCode;
/** 
 * @type callback
 * @brief 调用 takeRemoteSnapshot:callback:{@link #ByteRTCVideo#takeRemoteSnapshot:callback:} 截取视频画面时，收到此回调。
 * @param taskId 远端截图任务的编号。和 takeRemoteSnapshot:callback:{@link #ByteRTCVideo#takeRemoteSnapshot:callback:} 的返回值一致。
 * @param streamKey 截图的视频流，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param image 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。
 * @param errorCode 截图错误码：<br>
 *        + 0: 成功 <br>
 *        + -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br>
 *        + -2: 截图错误。流无效。
 */
- (void)onTakeRemoteSnapshotResult:(NSInteger)taskId
                         streamKey:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                             image:(ByteRTCImage * _Nullable)image
                         errorCode:(NSInteger)errorCode;
@end

/** 
 * @type api
 * @region 音视频处理
 * @brief 高级视频特效。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoEffect : NSObject

/** 
 * @hidden for internal use only
 * @type api
 * @brief 设置视频特效算法模型地址，并初始化特效模块。
 * @param finder ResourceFinder 地址
 * @param deleter ResourceDeleter 地址
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
- (int) setAlgoModelResourceFinder:(void*_Nonnull)finder deleter:(void*_Nonnull)deteter;

/** 
 * @type api
 * @brief 检查视频特效证书，设置算法模型路径，并初始化特效模块。
 * @param license_file 证书文件的绝对路径，用于鉴权。
 * @param algo_model_dir 算法模型绝对路径，即存放特效 SDK 所有算法模型的目录。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
- (int) initCVResource:(NSString* _Nonnull)license_file
            withAlgoModelDir: (NSString* _Nonnull)algo_model_dir;

/** 
 * @type api
 * @brief 开启高级美颜、滤镜等视频特效。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @notes  <br>
 *      + 调用本方法前，必须先调用 initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} 进行初始化。
 *      + 调用该方法后，特效不直接生效，你还需调用 setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} 设置视频特效素材包或调用调用 setColorFilter:{@link #ByteRTCVideoEffect#setColorFilter:} 设置滤镜。
 *      + 调用 disableVideoEffect{@link #ByteRTCVideoEffect#disableVideoEffect} 关闭视频特效。
 */
- (int) enableVideoEffect;

/** 
 * @type api
 * @brief 关闭视频特效。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @notes 调用 enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} 开启视频特效。
 */
- (int) disableVideoEffect;

/** 
 * @hidden for internal use only
 * @type api
 * @region 视频特效
 * @brief 返回视频特效句柄。私有接口。
 */
- (void* _Nullable)getVideoEffectHandle;

/** 
 * @hidden for internal use only
 * @type api
 * @region 视频特效
 * @brief 私有接口
 * 设置视频特效素材包
 * @param [in] stickerPath 特效素材包绝对路径。
 *        要取消当前视频特效，将此参数设置为 null。
 * @return  <br>
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  <br>
 * @notes 在调用这个方法之前，你须先调用 enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:} 。
 */
- (int) applyStickerEffect:(NSString* _Nullable)stickerPath;

/** 
 * @type api
 * @brief 设置视频特效素材包。
 * @param effect_nodes 特效素材包绝对路径数组。
 *        要取消当前视频特效，将此参数设置为 null。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @notes 调用本方法前，必须先调用 enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect}。
 */
- (int) setEffectNodes:(NSArray<NSString*>*_Nonnull)effect_nodes;

/** 
 * @hidden for internal use only
 * @type api
 * @brief  叠加视频特效素材包。
 * @param effect_nodes 特效素材包路径数组。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @notes 该接口会在 setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} 设置的特效基础上叠加特效。
 */
- (int) appendEffectNodes:(NSArray<NSString*>*_Nonnull)effect_nodes;

/** 
 * @hidden for internal use only
 * @type api
 * @brief  移除指定的视频特效资源。
 * @param effect_nodes 特效素材包路径数组。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @notes 移除 setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} 或 appendEffectNodes{@link #ByteRTCVideoEffect#appendEffectNodes} 设置的视频特效资源。
 */
- (int) removeEffectNodes:(NSArray<NSString*>*_Nonnull)effect_nodes;

/** 
 * @type api
 * @brief 设置特效强度。
 * @param node 特效素材包绝对路径，参考[素材包结构说明](https://www.volcengine.com/docs/6705/102039)。
 * @param key 需要设置的素材 key 名称，参考[素材 key 对应说明](https://www.volcengine.com/docs/6705/102041)。
 * @param value 特效强度值，取值范围 [0,1]，超出范围时设置无效。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
- (int) updateEffectNode:(NSString* _Nonnull)node
                key:(NSString* _Nonnull)key value:(float) value;

/** 
 * @type api
 * @brief 设置颜色滤镜。
 * @param filter_res 滤镜资源包绝对路径。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @notes 调用 setColorFilterIntensity:{@link #ByteRTCVideoEffect#setColorFilterIntensity:} 设置已启用颜色滤镜的强度。设置强度为 0 时即关闭颜色滤镜。
 */
- (int) setColorFilter:(NSString* _Nonnull)filter_res;

/** 
 * @type api
 * @brief 设置已启用颜色滤镜的强度。
 * @param intensity 滤镜强度。取值范围 [0,1]，超出范围时设置无效。
 *                  当设置滤镜强度为 0 时即关闭颜色滤镜。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
- (int) setColorFilterIntensity:(float) intensity;

/** 
 * @type api
 * @brief 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
 * @param bg_sticker_path 背景贴纸特效素材绝对路径。
 * @param source 背景贴纸对象，参看 ByteRTCVirtualBackgroundSource{@link #ByteRTCVirtualBackgroundSource}。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @notes <br>
 *      + 调用本方法前，必须先调用 initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} 进行初始化。
 *      + 调用 disableVirtualBackground{@link #ByteRTCVideoEffect#disableVirtualBackground} 关闭虚拟背景。
 */
- (int) enableVirtualBackground:(NSString* _Nonnull)bg_sticker_path
                withSource:(ByteRTCVirtualBackgroundSource* _Nonnull)source;

/** 
 * @type api
 * @brief 关闭虚拟背景。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @notes 调用 enableVirtualBackground:withSource:{@link #ByteRTCVideoEffect#enableVirtualBackground:withSource:} 开启虚拟背景后，可以调用此接口关闭虚拟背景。
 */
- (int) disableVirtualBackground;

/** 
 * @hidden for internal use only
 * @type api
 * @brief 开启人像属性检测。
 * @param config 人像属性检测参数，参看 ByteRTCExpressionDetectConfig{@link #ByteRTCExpressionDetectConfig}。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
- (int) setVideoEffectExpressionDetect:(ByteRTCExpressionDetectConfig* _Nonnull)config;

/** 
 * @deprecated since 3.50 and will be deleted in 3.55, use enableFaceDetection:withInterval:withModelPath:{@link #ByteRTCVideoEffect#enableFaceDetection:withInterval:withModelPath:} and disableFaceDetection{@link #ByteRTCVideoEffect#disableFaceDetection} instead.
 * @type api
 * @brief 注册人脸检测结果回调观察者。
 *        注册此观察者后，你会周期性收到 onFaceDetectResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectResult:} 回调。
 * @param observer 人脸检测结果回调观察者，参看 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}。
 * @param interval 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval+视频采集帧间隔`。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
- (int) registerFaceDetectionObserver:(_Nullable id<ByteRTCFaceDetectionObserver>) observer
                withInterval:(NSInteger)interval;

/** 
 * @type api
 * @brief 开启人脸识别功能，并设置人脸检测结果回调观察者。
 *        此观察者后，你会周期性收到 onFaceDetectResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectResult:} 回调。
 * @param observer 人脸检测结果回调观察者，参看 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}。
 * @param interval 两次回调之间的最小时间间隔，必须大于 0，单位为毫秒。实际收到回调的时间间隔大于 interval，小于 interval+视频采集帧间隔。
 * @param path 人脸检测算法模型文件路径，一般为 ttfacemodel 文件夹中 tt_face_vXXX.model 文件的绝对路径。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + -1004: 初始化中，初始化完成后启动此功能。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
- (int) enableFaceDetection:(_Nullable id<ByteRTCFaceDetectionObserver>) observer
               withInterval:(NSUInteger)interval
              withModelPath:(NSString* _Nonnull)path;

/** 
 * @type api
 * @brief 关闭人脸识别功能。
 * @return  <br>
 *      + 0: 调用成功。
 *      + –1000: 未集成特效 SDK。
 *      + –1001: 特效 SDK 不支持该功能。
 *      + –1002: 特效 SDK 版本不兼容。
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
- (int) disableFaceDetection;
@end


/** 
 * @type keytype
 * @brief RTC 智能决策后得到的帧率和分辨率积（宽*高）。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFrameUpdateInfo : NSObject
/** 
 * @brief 分辨率积（宽*高）。
 */
@property(assign, nonatomic) int pixel;
/** 
 * @brief 帧率。
 */
@property(assign, nonatomic) int framerate;
@end
