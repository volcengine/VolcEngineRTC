/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Video Defines
*/

#import "ByteRTCCommonDefines.h"
#import "ByteRTCAudioDefines.h"
/** 
 * @type keytype
 * @brief 视频帧渲染设置
 */
typedef NS_ENUM(NSUInteger, ByteRTCRenderMode) {
    /** 
     * @brief 视窗填满优先。  <br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    ByteRTCRenderModeHidden = 1,
    /** 
     * @brief 视频帧内容全部显示优先。  <br>
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
     */
    ByteRTCRenderModeFit = 2,
    /** 
     *  @brief 视频帧自适应画布 <br>
     *         视频帧非等比缩放，直至画布被填满。在此过程中，视频帧的长宽比例可能会发生变化。
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
 * @hidden
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
 * @hidden
 * @type keytype
 * @deprecated since 329.1 use ByteRTCMirrorType instead
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
 * @brief 编码策略偏好
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoEncoderPreference) {
    /** 
     * @brief 无偏好
     */
    ByteRTCVideoEncoderPreferenceDisabled          = 0,
    /** 
     * @brief 帧率优先
     */
    ByteRTCVideoEncoderPreferenceMaintainFramerate = 1,
    /** 
     * @brief 质量优先
     */
    ByteRTCVideoEncoderPreferenceMaintainQuality   = 2,
    /** 
     * @brief 平衡质量与帧率
     */
    ByteRTCVideoEncoderPreferenceBalance           = 3,
};

/** 
 * @hidden
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
     * @hidden
     */
    ByteRTCStreamMixingEventBase = 0,
    /** 
     *  请求发起转推直播任务
     */
    ByteRTCStreamMixingEventStart = 1,
    /** 
     *  发起转推直播任务成功
     */
    ByteRTCStreamMixingEventStartSuccess = 2,
    /** 
     *  发起转推直播任务失败
     */
    ByteRTCStreamMixingEventStartFailed = 3,
    /** 
     *  请求更新转推直播任务配置
     */
    ByteRTCStreamMixingEventUpdate = 4,
    /** 
     *  成功更新转推直播任务配置
     */
    ByteRTCStreamMixingEventUpdateSuccess = 5,
    /** 
     *  更新转推直播任务配置失败
     */
    ByteRTCStreamMixingEventUpdateFailed = 6,
    /** 
     *  请求结束转推直播任务
     */
    ByteRTCStreamMixingEventStop = 7,
    /** 
     *  结束转推直播任务成功
     */
    ByteRTCStreamMixingEventStopSuccess = 8,
    /** 
     *  结束转推直播任务失败
     */
    ByteRTCStreamMixingEventStopFailed = 9,
    /** 
     *  更新转推直播任务配置的请求超时
     */
    ByteRTCStreamMixingEventChangeMixType = 10,
    /** 
     *  得到客户端合流音频首帧
     */
    ByteRTCStreamMixingEventFirstAudioFrameByClientMixer = 11,
    /** 
     *  收到客户端合流视频首帧
     */
    ByteRTCStreamMixingEventFirstVideoFrameByClientMixer = 12,
    /** 
     *  更新转推直播任务配置超时
     */
    ByteRTCStreamMixingEventUpdateTimeout = 13,
    /** 
     *  发起转推直播任务配置超时
     */
    ByteRTCStreamMixingEventStartTimeout = 14,
    /** 
     *  合流布局参数错误
     */
    ByteRTCStreamMixingEventRequestParamError = 15,
    /** 
    * @hidden
    *  合流加图片
    */
    ByteRTCStreamMixingEventMixImage = 16,
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
 * @deprecated
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
     *        此设置仅切换至内部采集，你需继续调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 开启内部采集。
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
     * @brief 使用自定义图片背景替换视频原有背景。
     */
    ByteRTCVirtualBackgroundSourceTypeImage = 1
};

/** 
 * @type keytype
 * @brief 移动端摄像头
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
     *  推流成功。
     */
    ByteRtcTranscoderErrorCodeOK = 0,
    /** 
     * 未定义的合流错误
     */
    ByteRtcTranscoderErrorCodeBase = 1090,
    /** 
     *  客户端 SDK 检测到无效推流参数。
     */
    ByteRtcTranscoderErrorCodeInvalidParam = 1091,
    /** 
     *  状态错误，需要在状态机正常状态下发起操作
     */
    ByteRtcTranscoderErrorCodeInvalidState = 1092,
    /** 
     *  无效操作
     */
    ByteRtcTranscoderErrorCodeInvalidOperator = 1093,
    /** 
     *  转推直播任务处理超时，请检查网络状态并重试
     */
    ByteRtcTranscoderErrorCodeTimeOut = 1094,
    /** 
     * 服务端检测到错误的推流参数
     */
    ByteRtcTranscoderErrorCodeInvalidParamByServer = 1095,
    /** 
     *  对流的订阅超时
     */
    ByteRtcTranscoderErrorCodeSubTimeoutByServer = 1096,
    /** 
     *  合流服务端内部错误。
     */
    ByteRtcTranscoderErrorCodeInvalidStateByServer = 1097,
    /** 
     *  合流服务端推 CDN 失败。
     */
    ByteRtcTranscoderErrorCodeAuthenticationByCDN = 1098,
    /** 
     *  服务端接收信令超时，请检查网络状态并重试。
     */
    ByteRtcTranscoderErrorCodeTimeoutBySignaling = 1099,
    /** 
     *  图片合流失败。
     */
    ByteRtcTranscoderErrorCodeMixImageFail = 1100,
    /** 
     *  服务端未知错误。
     */
    ByteRtcTranscoderErrorCodeUnKnownErrorByServer = 1101,
    /**
     * @hidden
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
 * @author liyi.000
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
 * @brief 内部采集屏幕视频流时，是否采集鼠标信息
 */
typedef NS_ENUM(NSUInteger, ByteRTCMouseCursorCaptureState) {
    /** 
     * @brief 采集鼠标信息
     */
    ByteRTCMouseCursorCaptureStateOn,
    /** 
     * @brief 不采集鼠标信息
     */
    ByteRTCMouseCursorCaptureStateOff,
};
/** 
 * @type keytype
 * @brief 屏幕共享时的边框高亮设置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCHighlightConfig: NSObject
/** 
 * @brief 是否显示高亮边框，默认显示。
 */
@property (assign, nonatomic) BOOL enableHighlight;
/** 
 * @brief 边框的颜色, 颜色格式为十六进制 ARGB:  0xAARRGGBB
 */
@property (assign, nonatomic) uint32_t borderColor;
/** 
 * @brief 边框的宽度，单位：像素
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
 * @hidden
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
 * @hidden
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
 * @hidden
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
 * @brief 矩形区域
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRectangle : NSObject
/** 
 * @brief 矩形区域左上角的 x 坐标
 */
@property(assign, nonatomic) int x;
/** 
 * @brief 矩形区域左上角的 y 坐标
 */
@property(assign, nonatomic) int y;
/** 
 * @brief 矩形宽度 (px)
 */
@property(assign, nonatomic) int width;
/** 
 * @brief 矩形高度(px)
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
 *        + !0：检测失败。详见[CV 错误码](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
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
 * @brief 房间 ID
 */
@property(strong, nonatomic) NSString* _Nullable roomId;
/** 
 * @brief 用户 ID
 */
@property(strong, nonatomic) NSString* _Nullable uid;
/** 
 * @brief 用于填充画布空白部分的背景颜色。取值范围是 `[0x0000000, 0xFFFFFFFF]`。默认值是 `0x00000000`。其中，透明度设置无效。
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
 * @brief 视频帧缩放模式。你可以设置缩放以适应视窗，参见 ByteRTCVideoStreamScaleMode{@link #ByteRTCVideoStreamScaleMode}
 */
@property(nonatomic, assign) ByteRTCVideoStreamScaleMode mode;

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
 *         当远端用户调用 SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:} 方法发布多个配置的视频流时，此处会包含该用户发布的所有视频流的属性信息。  <br>
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
 *         用户可以通过调用 SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中所有分辨率的相关信息。
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
 *         用户可以通过调用 SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:} 方法发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>
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
 * @hidden
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
 * @hidden
 * @type api
 * @brief 获取视频内容类型
 * @return 视频内容类型，参看 ByteRTCVideoContentType{@link #ByteRTCVideoContentType}。
 */
@property(assign, nonatomic) ByteRTCVideoContentType contentType;
/** 
 * @brief 当前帧的时间戳信息
 */
@property(assign, nonatomic) CMTime time;
/**
 * @hidden
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
 * @hidden
 * @brief 视频镜像信息
 */
@property(assign, nonatomic) int flip;
/** 
 * @brief 视频帧的摄像头信息，参考 ByteRTCCameraID{@link #ByteRTCCameraID}
 */
@property(assign, nonatomic) ByteRTCCameraID cameraId;
/** 
 * @brief 视频帧附加的数据
 */
@property(strong, nonatomic) ByteRTCFrameExtendedData * _Nullable extendedData;
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
 * @hidden
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
 * @brief 单个视频流在合流中的布局信息。  <br>
 *        开启转推直播功能后，在多路视频流合流时，你可以设置其中一路视频流在合流中的预设布局信息。
 * @notes  <br>
 *         + 视频流对应区域左上角的实际坐标是通过画面尺寸和归一化比例相乘，并四舍五入取整得到的。假如：Canvas.Width = 1920, Region.LocationX = 0.33，那么该画布左上角的横坐标为 634（1920×0.33=633.6，四舍五入取整）。  <br>
 *         + 视频流对应区域宽度和高度的像素值是通过画面尺寸和归一化比例相乘，四舍五入取整，并向上转换为偶数得到的。假如：Canvas.Width = 1920, Region.WidthProportion = 0.21，那么该画布横向宽度为 404px（1920x0.21=403.2，四舍五入取整后，再向上转换为偶数）。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingRegion : NSObject
/** 
 * @brief 视频流发布用户的用户 ID 。必填。
 */
@property(copy, nonatomic) NSString * _Nonnull uid;
/** 
 * @brief 媒体流所在房间的房间 ID。<br>
 *        如果此媒体流是通过 startForwardStreamToRooms:{@link #ByteRTCEngineKit#startForwardStreamToRooms:} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief 视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。
 */
@property(assign, nonatomic) CGFloat x;
/** 
 * @brief 视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。
 */
@property(assign, nonatomic) CGFloat y;
/** 
 * @brief 视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。
 */
@property(assign, nonatomic) CGFloat width;
/** 
 * @brief 视频流对应区域高度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。
 */
@property(assign, nonatomic) CGFloat height;
/** 
 * @brief 用户视频布局在画布中的层级。0为底层，值越大越上层，范围为[0 - 100]。
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
 * @brief 透明度，可选范围为 [0.0, 1.0]，0.0 为全透明。
 */
@property(assign, nonatomic) CGFloat alpha;
/** 
 * @brief 合流内容控制。默认值为 `ByteRTCTranscoderContentControlTypeHasAudioAndVideo`，参看 ByteRTCTranscoderContentControlType{@link #ByteRTCTranscoderContentControlType} 。
 */
@property (assign, nonatomic) ByteRTCTranscoderContentControlType contentControl;

/** 
 * @brief 视频显示模式。详见 ByteRTCRenderMode{@link #ByteRTCRenderMode} 数据类型。  <br>
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @hidden
 * @brief 合流布局区域类型。参看 ByteRTCTranscoderLayoutRegionType{@link #ByteRTCTranscoderLayoutRegionType}。
 */
@property (assign, nonatomic) ByteRTCTranscoderLayoutRegionType type;
/** 
 * @hidden
 * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
 */
@property (strong, nonatomic) NSData * _Nullable data;
/** 
 * @hidden
 * @type keytype
 * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 ByteRTCTranscoderLayoutRegionDataParam{@link #ByteRTCTranscoderLayoutRegionDataParam}。
 */
@property (strong, nonatomic) ByteRTCTranscoderLayoutRegionDataParam * _Nullable dataParam;
@end

/** 
 * @type keytype
 * @brief 视频流合流整体布局信息。  <br>
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingLayout : NSObject
/** 
 * @brief 画布的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/** 
 * @brief 用户布局信息列表。每条流的具体布局详见 ByteRTCVideoCompositingRegion{@link #ByteRTCVideoCompositingRegion} 数据类型。
 */
@property(copy, nonatomic) NSArray<ByteRTCVideoCompositingRegion *> * _Nonnull regions;
/** 
 * @brief 透传的 App 数据。
 */
@property(copy, nonatomic) NSString *_Nonnull appData;
@end

/** 
 * @type keytype
 * @brief 视频转码配置参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingVideoConfig : NSObject
/** 
 * @brief codec 编码器。默认值为 `0`。 <br>
 *        + 值为 `0` 时，使用 H.264； <br>
 *        + 值为 `1` 时，使用 byteVC1。此时，你必须指明 ByteRTCTranscodingVideoConfig{@link #ByteRTCTranscodingVideoConfig} 的视频码率。
 */
@property(copy, nonatomic) NSString * _Nonnull codec;
/** 
 * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640。
 */
@property(assign, nonatomic) NSInteger width;
/** 
 * @brief 合流视频高度。单位为 px，范围为 [2, 1080]，必须是偶数。默认值为 480。
 */
@property(assign, nonatomic) NSInteger height;
/** 
 * @brief 合流的视频帧率。默认值为 `15`，取值范围是 `[1, 60]`。值不合法时，自动调整为默认值。
 */
@property(assign, nonatomic) NSInteger fps;
/** 
 * @brief I 帧间隔。默认值为 `4`，取值范围为 `[1, 5]`，单位为秒。值不合法时，自动调整为默认值。
 */
@property(assign, nonatomic) NSInteger gop;
/** 
 * @brief 合流视频码率。单位为 kbps，取值范围为 `[1,10000]`，默认值为自适应。值不合法时，自动调整为默认值。
 */
@property(assign, nonatomic) NSInteger kBitRate;
/** 
 * @brief 是否使用低延时特性。
 */
@property(assign, nonatomic) BOOL lowLatency;
@end

/** 
 * @type keytype
 * @brief 音频转码配置参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingAudioConfig : NSObject
/** 
 * @brief 音频编码格式，仅支持`AAC`编码格式。
 */
@property(copy, nonatomic) NSString * _Nonnull codec;
/** 
 * @brief 音频采样率，单位 kHz。可取 32Khz、44.1Khz、48Khz，默认值为 48Khz。
 */
@property(assign, nonatomic) NSInteger sampleRate;
/** 
 * @brief 音频声道数。可取 1、2，默认值为 2。
 */
@property(assign, nonatomic) NSInteger channels;
/** 
 * @brief 音频码率，单位 Kbps。可取范围 [32Kbps, 192Kbps]，默认值为 64Kbps。
 */
@property(assign, nonatomic) NSInteger kBitRate;
/** 
 * @brief AAC 等级，参看 ByteRTCAACProfile{@link #ByteRTCAACProfile}。默认值为 `0`。
 */
@property(assign, nonatomic) ByteRTCAACProfile profile;
/**
 * @hidden
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteRTCAACProfile) aacProfile;
@end

/** 
 * @type keytype
 * @brief 转推直播配置参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLiveTranscoding : NSObject
/** 
 * @brief 合流类型，详见 ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType} 数据类型。
 */
@property(assign, nonatomic) ByteRTCStreamMixingType expectedMixingType;
/** 
 * @brief 视频流合流整体布局信息。  <br>
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。详见 ByteRTCVideoCompositingLayout{@link #ByteRTCVideoCompositingLayout} 数据类型。
 */
@property(strong, nonatomic) ByteRTCVideoCompositingLayout * _Nonnull layout;
/** 
 * @brief 视频转码配置参数。详见 ByteRTCTranscodingVideoConfig{@link #ByteRTCTranscodingVideoConfig} 数据类型。
 */
@property(strong, nonatomic) ByteRTCTranscodingVideoConfig * _Nonnull video;
/** 
 * @brief 音频转码配置参数。详见 ByteRTCTranscodingAudioConfig{@link #ByteRTCTranscodingAudioConfig} 数据类型。
 */
@property(strong, nonatomic) ByteRTCTranscodingAudioConfig * _Nonnull audio;
/** 
 * @hidden
 * @brief 动态扩展自定义参数。
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/** 
 * @brief 业务透传鉴权信息
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable authInfo;
/** 
 * @brief 推流 CDN 地址。
 */
@property(copy, nonatomic) NSString * _Nullable url;
/** 
 * @brief 推流房间 ID，必填。
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief 推流用户 ID。
 */
@property(copy, nonatomic) NSString * _Nullable userId;
/** 
 * @brief 获取默认转推直播配置参数。
 * @return 转推直播配置参数，参看 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}。
 */
+ (instancetype _Nonnull)defaultTranscoding;
@end

/** 
 * @type keytype
 * @brief 视频订阅配置信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeVideoConfig : NSObject
/** 
 * @brief 订阅的视频流分辨率下标。  <br>
 *        当远端用户通过调用 enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:} 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
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
 * @deprecated Please use ByteVideoSinkDelegate
 * @type callback
 * @brief 自定义的视频渲染
 */
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate")
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkProtocol <NSObject>
@required
/** 
 * @hidden
 * @type callback
 * @brief 初始化渲染器
 * @return  <br>
 *         + YES: 自定义的渲染器初始化完成  <br>
 *         + NO: 自定义的渲染器初始化失败，不继续往下运行  <br>
 * @notes 初始化渲染器的时候会回调这个方法
 */
- (BOOL)shouldInitialize DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");;

/** 
 * @hidden
 * @type callback
 * @brief 启动渲染器
 * @notes 在开启渲染功能的时候会回调这个方法
 */
- (void)shouldStart DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief 停止渲染器
 * @notes 在停止渲染功能的时候会回调这个方法
 */
- (void)shouldStop DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief 释放渲染器
 * @notes 渲染器即将被废弃的时候会回调这个方法
 */
- (void)shouldDispose DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief 获取PixelFormat格式
 * @return Buffer 类型，{@link #ByteRTCVideoSinkPixelFormat}
 * @notes 通过该方法的返回值，告知 SDK PixelFormat 的格式
 */
- (ByteRTCVideoPixelFormat)pixelFormat DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
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
 * @hidden
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
 * @param pixelBuffer 数据 Buffer
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
 * @hidden
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
 * @author zhushufan.ref
 * @brief 获取 RTC SDK 采集得到的视频帧，根据 registerLocalVideoProcessor:withConfig:{@link #ByteRTCEngineKit#registerLocalVideoProcessor:withConfig:} 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。
 * @param src_frame RTC SDK 采集得到的视频帧，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return 经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @notes 如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。
 */
- (ByteRTCVideoFrame* _Nullable) processVideoFrame:(ByteRTCVideoFrame* _Nonnull)src_frame;

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
 * @author liyi.000
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
 * @brief 自定义图片背景使用的图片的绝对路径。
 * @notes  <br>
 *       + 支持的格式为 jpg、jpeg、和 png。<br>
 *       + 分辨率超过 1080P 时，图片会被等比缩放。背景图片和视频分辨率不一致时，图片会被裁剪缩放。<br>
 *       + 若使用工程中传入的 png 格式图片作为背景，并开启了 png 压缩，则需要在 xcode 右侧界面的文件视图中，将需要的 png 图片的文件类型指定为 Data 类型，阻止此文件被压缩，否则会导致图片解码失败。
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
 * @brief 调用 registerLocalEncodedVideoFrameObserver:{@link #ByteRTCEngineKit#registerLocalEncodedVideoFrameObserver:} 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。
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
 * @author wangzhanqiang
 * @brief 提示自定义编码帧可以开始推送的回调。  <br>
 *        收到该回调后，你即可调用 pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:{@link #ByteRTCEngineKit#pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:} 向 SDK 推送自定义编码视频帧
 * @param streamIndex 可以推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStart:(ByteRTCStreamIndex)streamIndex;
@required
/** 
 * @type callback
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧
 * @param streamIndex 需停止推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStop:(ByteRTCStreamIndex)streamIndex;
@required
/** 
 * @type callback
 * @region 视频管理
 * @author wangzhanqiang
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
 * @author wangzhanqiang
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
 * @author wangzhanqiang
 * @brief 调用 registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCEngineKit#registerRemoteEncodedVideoFrameObserver:} 后，SDK 监测到远端编码后视频数据时，触发该回调
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
 * @notes  <br>
 *         + 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。
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
 * @param taskId 转推直播任务 ID。
 * @notes 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
 */
- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame taskId:(NSString *_Nonnull)taskId;

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

@end

/** 
 * @type callback
 * @region 视频特效
 * @author wangjunlin.3182
 * @brief 人脸检测结果回调观察者
 */
@protocol ByteRTCFaceDetectionObserver <NSObject>
/** 
 * @type callback
 * @region 视频特效
 * @author wangjunlin.3182
 * @brief 特效 SDK 进行人脸检测结果的回调。 <br>
 *        调用 registerFaceDetectionObserver:withInterval:{@link #ByteRTCEngineKit#registerFaceDetectionObserver:withInterval:} 注册了 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver} ，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。
 * @param result 人脸检测结果, 参看 ByteRTCFaceDetectionResult{@link #ByteRTCFaceDetectionResult}。
 */
- (void)onFaceDetectionResult:(ByteRTCFaceDetectionResult * _Nonnull)result;
/** 
 * @hidden
 * @type callback
 * @region 视频特效
 * @author liqi.ritchie
 * @brief 特效 SDK 进行人像属性检测结果的回调。 <br>
 *        调用 registerFaceDetectionObserver:withInterval:{@link #ByteRTCEngineKit#registerFaceDetectionObserver:withInterval:} 注册了 IFaceDetectionObserver{@link #IFaceDetectionObserver}，并调用 setVideoEffectExpressionDetect:{@link #ByteRTCEngineKit#setVideoEffectExpressionDetect:} 开启人像属性检测后，你会收到此回调。
 * @param result 人像属性检测结果, 参看 ExpressionDetectResult{@link #ExpressionDetectResult}。
 */
- (void)onExpressionDetectResult:(ByteRTCExpressionDetectResult * _Nonnull)result;
@end

#pragma mark - ByteRTCEngineMediaMetadataObserver

/** 
 * @hidden
 * @deprecated since 326.1, use sendSEIMessage instead
 * @type callback
 * @brief 使用内部源视频采集时,配置和获取附加数据接口
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCMediaMetadataObserver <NSObject>
@required
/** 
 * @type callback
 * @region 视频数据回调
 * @author wangjunlin.3182
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
 * @author wangjunlin.3182
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
 * @brief 视频参数
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
 *        内部采集模式下默认值为 -1，即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。 <br>
 *        设为 0 则不对视频流进行编码发送。
 */
@property(nonatomic, assign) NSInteger maxBitrate;
/** 
 * @brief 视频帧缩放模式。你可以设置缩放以适应视窗，参见 ByteRTCVideoStreamScaleMode{@link #ByteRTCVideoStreamScaleMode}
 */
@property(nonatomic, assign) ByteRTCVideoStreamScaleMode scaleMode;
/** 
 * @brief 视频编码质量策略，参见 ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
 */
@property(nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end
/** 
 * @type keytype
 * @brief 远端视频帧信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoConfig : NSObject
/** 
 * @brief 期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。  <br>
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
 * @author shenpengliang
 * @brief 房间参数配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomConfig : NSObject
/** 
 * @brief 房间模式，参看 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}，默认为普通音视频通话模式，进房后不可更改。
 */
@property(nonatomic) ByteRTCRoomProfile profile;
/** 
 * @brief 是否自动发布音视频流，默认为自动发布。 <br>
 *        若调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。
 */
@property(assign, nonatomic) BOOL isAutoPublish;
/** 
 * @brief 是否自动订阅音频流，默认为自动订阅。
 */
@property(assign, nonatomic) BOOL isAutoSubscribeAudio;
/** 
 * @brief 是否自动订阅主视频流，默认为自动订阅。  <br>
 *        屏幕流始终自动订阅，不受该方法影响。
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
 * @brief 裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)
 */
@property(assign, nonatomic) CGFloat LocationX;
/** 
 * @brief 裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的归一化比例，取值范围[0.0, 1.0)
 */
@property(assign, nonatomic) CGFloat LocationY;
/** 
 * @brief 裁剪后得到的视频帧宽度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat WidthProportion;
/** 
 * @brief 裁剪后得到的视频帧高度相对于裁剪前整体画面的归一化比例，取值范围(0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat HeightProportion;
@end
/** 
 * @type keytype
 * @brief 合成公共流的每条流的布局信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamRegion : NSObject
/** 
 * @brief 用户 ID
 */
@property(copy, nonatomic) NSString * _Nonnull userId;
/** 
 * @brief 房间 ID
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
 * @brief 透明度，范围 [0.0, 1.0]
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
 *        1:   屏幕流
 */
@property(assign, nonatomic) NSInteger streamType;
/** 
 * @brief 视频显示模式
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @brief 视频裁剪信息
 */
@property(strong, nonatomic) ByteRTCSourceCropInfo * _Nonnull sourceCrop;
@end

/** 
 * @type keytype
 * @brief 公共流的合流布局
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamLayout : NSObject
/** 
 * @brief 布局模式，目前只支持用户自定义模式，值为 `2`
 */
@property(assign, nonatomic) NSInteger layoutMode;
/** 
 * @brief 插帧模式。0: 插入上一帧，!0: 插黑帧
 */
@property(assign, nonatomic) NSInteger interpolationMode;
/** 
 * @brief 背景颜色
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/** 
 * @brief 背景图片地址
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundImage;
/** 
 * @brief 用户布局信息列表
 */
@property(copy, nonatomic) NSArray<ByteRTCPublicStreamRegion *> * _Nonnull regions;
@end

/** 
 * @type keytype
 * @brief 公共流的视频参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamVideoConfig : NSObject
/** 
 * @brief 视频宽度
 */
@property(assign, nonatomic) NSInteger width;
/** 
 * @brief 视频高度
 */
@property(assign, nonatomic) NSInteger height;
/** 
 * @brief 视频帧率
 */
@property(assign, nonatomic) NSInteger fps;
/** 
 * @brief 视频码率(kbps)
 */
@property(assign, nonatomic) NSInteger bitrate;
@end

/** 
 * @type keytype
 * @brief 公共流视频参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamAudioConfig : NSObject
/** 
 * @brief 音频采样率；  16k, 32k, 44.1k, 48k
 */
@property(assign, nonatomic) NSInteger sampleRate;
/** 
 * @brief 声道数
 */
@property(assign, nonatomic) NSInteger channels;
/** 
 * @brief 音频码率(kbps); 16kbsp, 32kbps, 64kbps
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
 * @brief 用户布局信息，参看 ByteRTCPublicStreamLayout{@link #ByteRTCPublicStreamLayout}
 */
@property(strong, nonatomic) ByteRTCPublicStreamLayout * _Nonnull layout;
/** 
 * @brief 视频参数。详见 ByteRTCPublicStreamVideoConfig{@link #ByteRTCPublicStreamVideoConfig}。
 */
@property(strong, nonatomic) ByteRTCPublicStreamVideoConfig * _Nonnull video;
/** 
 * @brief 音频参数。详见 ByteRTCPublicStreamAudioConfig{@link #ByteRTCPublicStreamAudioConfig}
 */
@property(strong, nonatomic) ByteRTCPublicStreamAudioConfig * _Nonnull audio;
/** 
 * @brief 推公共流的房间ID
 */
@property(copy, nonatomic) NSString * _Nullable roomId;
/** 
 * @brief 获取默认合流参数
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
 * @hidden(iOS)
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 获取视频采集设备列表。
 * @return ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateVideoCaptureDevices;
/** 
 * @type api
 * @hidden(iOS)
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 获取当前 SDK 正在使用的视频采集设备信息
 * @param deviceID 视频设备 ID
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + !0：方法调用失败  <br>
 */
- (int)getVideoCaptureDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/** 
 * @type api
 * @hidden(iOS)
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 设置当前视频采集设备
 * @param deviceID 视频设备 ID。调用 enumerateVideoCaptureDevices{@link #ByteRTCVideoDeviceManager#enumerateVideoCaptureDevices} 获取全量视频设备。
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + !0：方法调用失败  <br>
 */
- (int)setVideoCaptureDevice:(NSString* _Nonnull)deviceID;
@end
