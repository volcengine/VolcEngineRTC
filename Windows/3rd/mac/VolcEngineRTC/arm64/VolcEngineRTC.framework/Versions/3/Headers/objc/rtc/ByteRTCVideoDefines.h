/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Video Defines
*/

#import "ByteRTCAudioDefines.h"
/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamRenderMode{@link #ByteRTCMixedStreamRenderMode} instead.
 * @type keytype
 * @brief 图片或视频流的缩放模式。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamRenderMode{@link #ByteRTCMixedStreamRenderMode} instead.
 * @type keytype
 * @brief The render mode.
 */
typedef NS_ENUM(NSUInteger, ByteRTCRenderMode) {
    /**
     * @locale zh
     * @brief 视窗填满优先，默认值。<br>
     *        视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    /**
     * @locale en
     * @brief (Default) Fill and Crop.<br>
     *        The video frame is scaled with fixed aspect ratio, until it completely fills the canvas. The region of the video exceeding the canvas will be cropped.
     */
    ByteRTCRenderModeHidden = 1,
    /**
     * @locale zh
     * @brief 视频帧内容全部显示优先。<br>
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。
     */
    /**
     * @locale en
     * @brief Fit.<br>
     *        The video frame is scaled with fixed aspect ratio, until it fits just within the canvas. Other part of the canvas is filled with the background color.
     */
    ByteRTCRenderModeFit = 2,
    /**
     * @locale zh
     * @brief 视频帧自适应画布。<br>
     *        视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
    /**
     * @locale en
     * @brief Fill the canvas.<br>
     *        The video frame is scaled to fill the canvas. During the process, the aspect ratio may change.
     */
    ByteRTCRenderModeFill = 3,
};

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamMediaType{@link #ByteRTCMixedStreamMediaType} instead.
 * @type keytype
 * @brief 合流输出内容类型
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamMediaType{@link #ByteRTCMixedStreamMediaType} instead.
 * @type keytype
 * @brief Stream mixing content type
 */
typedef NS_ENUM(NSUInteger, ByteRTCTranscoderContentControlType) {
    /**
     * @locale zh
     * @brief 输出的混流包含音频和视频
     */
    /**
     * @locale en
     * @brief The mixed stream contains audio and video.
     */
    ByteRTCTranscoderContentControlTypeHasAudioAndVideo = 0,
    /**
     * @locale zh
     * @brief 输出的混流只包含音频
     */
    /**
     * @locale en
     * @brief The mixed stream only contains audio.
     */
    ByteRTCTranscoderContentControlTypeHasAudioOnly = 1,
    /**
     * @locale zh
     * @brief 输出的混流只包含视频
     */
    /**
     * @locale en
     * @brief The mixed stream only contains video.
     */
    ByteRTCTranscoderContentControlTypeHasVideoOnly = 2,
};

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamLayoutRegionType{@link #ByteRTCMixedStreamLayoutRegionType} instead.
 * @type keytype
 * @brief 合流布局区域类型。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamLayoutRegionType{@link #ByteRTCMixedStreamLayoutRegionType} instead.
 * @type keytype
 * @brief Stream mixing region type.
 */
typedef NS_ENUM(NSUInteger, ByteRTCTranscoderLayoutRegionType) {

    /**
     * @locale zh
     * @brief 合流布局区域类型为视频。
     */
    /**
     * @locale en
     * @brief The region type is a video stream.
     */
    ByteRTCTranscoderLayoutRegionTypeVideoStream = 0,

    /**
     * @locale zh
     * @brief 合流布局区域类型为图片。
     */
    /**
     * @locale en
     * @brief The region type is an image.
     */
    ByteRTCTranscoderLayoutRegionTypeImage = 1,
};


/**
 * @locale zh
 * @type keytype
 * @brief 视频流类型<br>
 *      目前C++ SDK 只支持 ByteRTCVideoStreamTypeHigh 类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video Stream Type<br>
 *       Currently C++ SDK only supports ByteRTCVideoStreamTypeHigh type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamType) {
    /**
     * @locale zh
     * @brief 高分辨率视频流
     */
    /**
     * @locale en
     * @brief High Resolution Video Streaming
     */
    ByteRTCVideoStreamTypeHigh = 0,
    /**
     * @locale zh
     * @brief 低分辨率视频
     */
    /**
     * @locale en
     * @brief Low Resolution Video
     */
    ByteRTCVideoStreamTypeLow = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 设置本地视频属性的返回状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Sets the return state of the local video property.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamState) {
    /**
     * @locale zh
     * @brief 设置本地视频属性成功
    */
   /**
     * @locale en
     * @brief Set local video properties successfully
    */
    ByteRTCVideoStreamStateSuccess                 = 0,
    /**
     * @locale zh
     * @brief 本地视频属性参数不合法
    */
   /**
     * @locale en
     * @brief Local video attribute parameter is invalid
    */
    ByteRTCVideoStreamStateInvalid                 = -2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频输出方向模式
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video output direction mode
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoOutputOrientationMode) {
    /**
     * @locale zh
     * @brief 自适应布局
     */
    /**
     * @locale en
     * @brief Self-adaptation layout
     */
    ByteRTCVideoOutputOrientationModeAdaptative = 0,
    /**
     * @locale zh
     * @brief 横屏布局
     */
    /**
     * @locale en
     * @brief Landscape layout
     */
    ByteRTCVideoOutputOrientationModeFixedLandscape = 1,
    /**
     * @locale zh
     * @brief 竖屏布局
     */
    /**
     * @locale en
     * @brief Vertical screen layout
     */
    ByteRTCVideoOutputOrientationModeFixedPortrait = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧朝向
 */
/**
 * @locale en
 * @type keytype
 * @brief Orientation of the video frame.
 */
typedef NS_ENUM(NSUInteger, ByteRTCVideoOrientation) {
    /**
    * @locale zh
    * @brief （默认）使用相机输出的原始视频帧的角度，不对视频帧进行额外旋转。
    */
    /**
    * @locale en
    * @brief (Default) The original orientation of the captured video frame.
    */
    ByteRTCVideoOrientationAdaptive = 0,
    /**
    * @locale zh
    * @brief 固定为竖屏，将相机采集到的视频帧转换为竖屏，在整个 RTC 链路中传递竖屏帧。
    */
    /**
    * @locale en
    * @brief Portrait mode. Adjust the captured video frame to vertical layout in RTC SDK.
    */
    ByteRTCVideoOrientationPortrait = 1,
    /**
    * @locale zh
    * @brief 固定为横屏，将相机采集到的视频帧转换为横屏，在整个 RTC 链路中传递横屏帧。
    */
    /**
    * @locale en
    * @brief Landscape mode. Adjust the captured video frame to horizontal layout in RTC SDK.
    */
    ByteRTCVideoOrientationLandscape = 2
};

/**
 * @locale zh
 * @hidden
 * @type keytype
 * @deprecated since 3.29 and will be deleted in 3.51, use ByteRTCMirrorType{@link #ByteRTCMirrorType} instead.
 * @brief 是否开启镜像模式
 */
/**
 * @locale en
 * @hidden
 * @type keytype
 * @deprecated since 3.45 and will be deleted in 3.51, use ByteRTCMirrorType{@link #ByteRTCMirrorType} instead.
 * @brief Whether to turn on mirror mode
 */
typedef NS_ENUM(NSUInteger, ByteRTCMirrorMode) {
    /**
     * @locale zh
     *  @brief 不开启
     */
    /**
     * @locale en
     *  @brief Not open
     */
    ByteRTCMirrorModeOff = 0,
    /**
     * @locale zh
     *  @brief 开启
     */
    /**
     * @locale en
     *  @brief Open
     */
    ByteRTCMirrorModeOn = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 镜像类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Mirror type
 */
typedef NS_ENUM(NSUInteger, ByteRTCMirrorType) {
    /**
     * @locale zh
     * @brief 本地预览和编码传输时均无镜像效果
     */
    /**
     * @locale en
     * @brief The preview and the published video stream are not mirrored.
     */
    ByteRTCMirrorTypeNone = 0,
    /**
     * @locale zh
     * @brief 本地预览时有镜像效果，编码传输时无镜像效果
     */
    /**
     * @locale en
     * @brief The preview is mirrored. The published video stream is not mirrored.
     */
    ByteRTCMirrorTypeRender = 1,
    /**
     * @locale zh
     * @brief 本地预览和编码传输时均有镜像效果
     */
    /**
     * @locale en
     * @brief The preview and the published video stream are mirrored.
     */
    ByteRTCMirrorTypeRenderAndEncoder = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端流的镜像类型。
 */
/**
 * @locale en
 * @type keytype
 * @brief Mirroring type for remote stream.
 */
typedef NS_ENUM(NSUInteger, ByteRTCRemoteMirrorType) {
    /**
     * @locale zh
     * @brief （默认值）远端视频渲染无镜像效果。
     */
    /**
     * @locale en
     * @brief (Default) No mirroring effect.
     */
    ByteRTCRemoteMirrorTypeNone = 0,
    /**
     * @locale zh
     * @brief 远端视频渲染有镜像效果。
     */
    /**
     * @locale en
     * @brief Enable mirroring effect.
     */
    ByteRTCRemoteMirrorTypeRender = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 基础美颜模式。
 */
/**
 * @locale en
 * @type keytype
 * @brief Basic beauty effect.
 */
typedef NS_ENUM(NSUInteger, ByteRTCEffectBeautyMode) {
    /**
     * @locale zh
     * @brief 美白。
     */
    /**
     * @locale en
     * @brief Brightening.
     */
    ByteRTCEffectBeautyModeWhite = 0,
    /**
     * @locale zh
     * @brief 磨皮。
     */
    /**
     * @locale en
     * @brief Smoothing.
     */
    ByteRTCEffectBeautyModeSmooth = 1,
    /**
     * @locale zh
     * @brief 锐化。
     */
    /**
     * @locale en
     * @brief Sharpening.
     */
    ByteRTCEffectBeautyModeSharpen = 2,
    /**
     * @locale zh
     * @valid since 3.55
     * @brief 清晰，需集成 v4.4.2+ 版本的特效 SDK。
     */
    /**
     * @locale en
     * @valid since 3.55
     * @brief Clarity. Integrating Effects SDK v4.4.2+ is required for this sub-item.
     */ 
    ByteRTCEffectBeautyModeClear = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧旋转信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Video frame rotation
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoRotation) {
    /**
     * @locale zh
     * @brief 不旋转
     */
    /**
     * @locale en
     * @brief Not to rotate.
     */
    ByteRTCVideoRotation0 = 0,
    /**
     * @locale zh
     * @brief 顺时针旋转 90 度
     */
    /**
     * @locale en
     * @brief Rotate 90 degrees clockwise.
     */
    ByteRTCVideoRotation90 = 90,
    /**
     * @locale zh
     * @brief 顺时针旋转 180 度
     */
    /**
     * @locale en
     * @brief Rotate 180 degrees clockwise.
     */
    ByteRTCVideoRotation180 = 180,
    /**
     * @locale zh
     * @brief 顺时针旋转 270 度
     */
    /**
     * @locale en
     * @brief Rotate 270 degrees clockwise.
     */
    ByteRTCVideoRotation270 = 270,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频内容类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Video content type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoContentType) {
    /**
     * @locale zh
     * @brief 普通视频
     */
    /**
     * @locale en
     * @brief Normal video
     */
    ByteRTCVideoContentTypeNormalFrame = 0,
    /**
     * @locale zh
     * @brief 黑帧视频
     */
    /**
     * @locale en
     * @brief Black frame video
     */
    ByteRTCVideoContentTypeBlackFrame = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧缩放模式
 */
/**
 * @locale en
 * @type keytype
 * @brief Video frame scale mode
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamScaleMode) {
    /**
     * @locale zh
     * @brief 自动缩放模式，默认设置为 ByteRTCVideoStreamScaleModeFitWithCropping。
     */
    /**
     * @locale en
     * @brief Auto mode, default to ByteRTCVideoStreamScaleModeFitWithCropping.
     */
    ByteRTCVideoStreamScaleModeAuto            = 0,
    /**
     * @locale zh
     * @brief 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。
     */
    /**
     * @locale en
     * @brief Stretch the video frame until the video frame and the window have the same resolution. The video frame's aspect ratio can be changed as it is automatically stretched to fill the window, but the whole image is visible.
     */
    ByteRTCVideoStreamScaleModeStretch         = 1,
    /**
     * @locale zh
     * @brief 视窗填满优先。  <br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    /**
     * @locale en
     * @brief  Fit the window with cropping   <br>
     *         Scale the video frame uniformly until the window is filled. If the video frame's aspect ratio is different from that of the window, the extra part of the video frame will be cropped. <br>
     *         After the scaling process is completed, the width or height of the video frame will be consistent with that of the window, and the other dimension will be greater than or equal to that of the window.
     */
    ByteRTCVideoStreamScaleModeFitWithCropping = 2,
    /**
     * @locale zh
     * @brief 视频帧内容全部显示优先。  <br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。保持纵横比来缩放图像，填充短边
     */
    /**
     * @locale en
     * @brief  Fit the window with filling   <br>
     *         Scale the video frame uniformly until its width or height reaches the boundary of the window. If the video frame's aspect ratio is different from that of the window, the area that is not filled will be black. <br>
     *         After the scaling process is completed, the width or height of the video frame will be consistent with that of the window, and the other dimension will be less than or equal to that of the window.
     */
    ByteRTCVideoStreamScaleModeFitWithFilling  = 3,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 视频编码模式
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief  Video encoding mode
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecMode) {
    /**
     * @locale zh
     * @brief 自动选择
    */
   /**
     * @locale en
     * @brief Automatic selection
    */
    ByteRTCVideoCodecModeAuto     = 0,
    /**
     * @locale zh
     * @brief 硬编码
    */
   /**
     * @locale en
     * @brief Hardcoding
    */
    ByteRTCVideoCodecModeHardware = 1,
    /**
     * @locale zh
     * @brief 软编码
    */
   /**
     * @locale en
     * @brief Softcoding
    */
    ByteRTCVideoCodecModeSoftware = 2
};

/**
 * @locale zh
 * @type keytype
 * @brief 编码帧类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Video compression picture type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPictureType) {
    /**
     * @locale zh
     * @brief 未知类型
     */
    /**
     * @locale en
     * @brief Unknown type
     */
    ByteRTCVideoPictureTypeUnknown = 0,
    /**
     * @locale zh
     * @brief I帧，关键帧，编解码不需要参考其他视频帧
     */
    /**
     * @locale en
     * @brief I-frames, key frames which are coded without reference to any other frame.
     */
    ByteRTCVideoPictureTypeI = 1,
    /**
     * @locale zh
     * @brief P帧，向前参考帧，编解码需要参考前一帧视频帧
     */
    /**
     * @locale en
     * @brief P-frames, forward-predicted frames which are coded by a forward predictive coding method.
     */
    ByteRTCVideoPictureTypeP = 2,
    /**
     * @locale zh
     * @brief B帧，前后参考帧，编解码需要参考前后两帧视频帧
     */
    /**
     * @locale en
     * @brief B-frames, bi-directionally predicted frames which are coded by both forward and backward predictive coding method.
     */
    ByteRTCVideoPictureTypeB = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 编码策略偏好。
 */
/**
 * @locale en
 * @type keytype
 * @brief Encoder preference.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoEncoderPreference) {
    /**
     * @locale zh
     * @brief 无偏好。不降低帧率和分辨率。
     */
    /**
     * @locale en
     * @brief No preference. The frame rate and the resolution will not be adjusted.
     */
    ByteRTCVideoEncoderPreferenceDisabled          = 0,
    /**
     * @locale zh
     * @brief （默认值）帧率优先。分辨率不变。
     */
    /**
     * @locale en
     * @brief (Default) Frame rate first. The resolution will not be changed.
     */
    ByteRTCVideoEncoderPreferenceMaintainFramerate = 1,
    /**
     * @locale zh
     * @brief 分辨率优先。
     */
    /**
     * @locale en
     * @brief Resolution first.
     */
    ByteRTCVideoEncoderPreferenceMaintainQuality   = 2,
    /**
     * @locale zh
     * @brief 平衡帧率与分辨率。
     */
    /**
     * @locale en
     * @brief Balancing resolution and frame rate.
     */
    ByteRTCVideoEncoderPreferenceBalance           = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 屏幕流编码模式，默认采用清晰模式。
 */
/**
 * @locale en
 * @type keytype
 * @brief The encoding modes for shared-screen streams. The default mode is the high-resolution mode.
 */
typedef NS_ENUM(NSInteger, ByteRTCScreenVideoEncoderPreference) {
    /**
     * @locale zh
     * @hidden(iOS)
     * @brief 智能模式。根据屏幕内容智能决策选择流畅模式或清晰模式。
     */
    /**
     * @locale en
     * @hidden(iOS)
     * @brief The automatic mode. The encoding mode is dynamically determined by RTC based on the content.
     */
    ByteRTCScreenVideoEncodePreferenceAuto   = 0,
    /**
     * @locale zh
     * @brief 流畅模式，优先保障帧率。适用于共享游戏、视频等动态画面。
     */
    /**
     * @locale en
     * @brief The high frame rate mode. Ensure the highest framerate possible under challenging network conditions. This mode is designed to share audiovisual content, including games and videos.
     */
    ByteRTCScreenVideoEncodePreferenceFramerate = 1,
    /**
     * @locale zh
     * @brief 清晰模式，优先保障分辨率。适用于共享PPT、文档、图片等静态画面。
     */
    /**
     * @locale en
     * @brief The high-resolution mode. Ensure the highest resolution possible under challenging network conditions. This mode is designed to share micro-detailed content, including slides, documents, images, illustrations, or graphics.
     */
    ByteRTCScreenVideoEncodePreferenceQuality   = 2,
};


/**
 * @locale zh
 * @hidden
 * @deprecated since 3.32 and will be deleted in 3.51, use ByteRTCVirtualBackgroundSourceType{@link #ByteRTCVirtualBackgroundSourceType} instead.
 * @type keytype
 * @brief 背景模式设置。
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51, use ByteRTCVirtualBackgroundSourceType{@link #ByteRTCVirtualBackgroundSourceType} instead.
 * @type keytype
 * @brief Background mode setting.
 */
typedef NS_ENUM(NSUInteger, ByteRTCBackgroundMode) {
    /**
     * @locale zh
     * @brief 无
     */
    /**
     * @locale en
     * @brief No
     */
    ByteRTCBackgroundModeNone = 0,
    /**
     * @locale zh
     * @brief 虚化
     */
    /**
     * @locale en
     * @brief Virtualization
     */
    ByteRTCBackgroundModeBlur = 1,
    /**
     * @locale zh
     * @brief 背景 1
     */
    /**
     * @locale en
     * @brief Background 1
     */
    ByteRTCBackgroundModeA = 2,
    /**
     * @locale zh
     * @brief 背景 2
     */
    /**
     * @locale en
     * @brief Background 2
     */
    ByteRTCBackgroundModeB = 3,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.32 and will be deleted in 3.51.
 * @type keytype
 * @brief 分割模型设置。
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief Split model settings.
 */
typedef NS_ENUM(NSUInteger, ByteRTCDivideModel) {
    /**
     * @locale zh
     * @brief 自研
     */
    /**
     * @locale en
     * @brief Self-research
     */
    ByteRTCDivideModelDefault = 0,
    /**
     * @brief effect
     */
    ByteRTCDivideModelEffect = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 数据类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Data type
 */
typedef NS_ENUM(NSUInteger, ByteRTCDataFrameType) {
    /**
     * @locale zh
     * @brief SEI 数据
     */
    /**
     * @locale en
     * @brief SEI data
     */
    ByteRTCDataFrameTypeSei = 0,
    /**
     * @locale zh
     * @brief 人脸识别数据
     */
    /**
     * @locale en
     * @brief Facial recognition data
     */
    ByteRTCDataFrameTypeRoi = 1,
    /**
     * @locale zh
     * @brief 其他数据帧类型
     */
    /**
     * @locale en
     * @brief Other data frame type
     */
    ByteRTCDataFrameTypeOther = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频采集模式
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video capture preference
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCapturePreference) {
   /**
    * @locale zh
    * @brief （默认）自动设置采集参数。<br>
    *        SDK在开启采集时根据服务端下发的采集配置结合编码参数设置最佳采集参数。
    */
   /**
    * @locale en
    * @brief (Default) Video capture preference: auto <br>
    *        SDK determines the best video capture parameters referring to the camera output parameters and the encoder configuration.
    */
    ByteRTCVideoCapturePreferenceAuto = 0,
   /**
    * @locale zh
    * @brief 手动设置采集参数，包括采集分辨率、帧率。
    */
   /**
    * @locale en
    * @brief Video capture preference: manual <br>
    *        Set the resolution and the frame rate manually.
    */
    ByteRTCVideoCapturePreferenceMannal = 1,
   /**
    * @locale zh
    * @brief 采集参数与编码参数一致
    */
   /**
    * @locale en
    * @brief Video capture preference: encoder configuration
    */
    ByteRTCVideoCapturePreferenceAutoPerformance = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video frame type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoFrameType) {
    /**
     * @locale zh
     * @brief 视频帧类型：内存数据
     */
    /**
     * @locale en
     * @brief Video frame type: memory data
     */
    ByteRTCVideoFrameTypeRawMemory = 0,
    /**
     * @locale zh
     * @brief 视频帧类型：CVPixelBuffer
     */
    /**
     * @locale en
     * @brief Video frame type: CVPixelBuffer
     */
    ByteRTCVideoFrameTypePixelBuffer,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧格式
 */
/**
 * @locale en
 * @type keytype
 * @brief Video frame format
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPixelFormat) {
    /**
     * @locale zh
     * @brief 未知格式
     */
    /**
     * @locale en
     * @brief Unknown format
     */
    ByteRTCVideoPixelFormatUnknown = 0,
    /**
     * @locale zh
     * @brief I420
     */
    /**
     * @locale en
     * @brief I420
     */
    ByteRTCVideoPixelFormatI420 = 1,
    /**
     * @locale zh
     * @brief BGRA
     */
    /**
     * @locale en
     * @brief BGRA
     */
    ByteRTCVideoPixelFormatBGRA = 2,
    /**
     * @locale zh
     * @brief NV21
     */
    /**
     * @locale en
     * @brief NV21
     */
    ByteRTCVideoPixelFormatNV21 = 3,
    /**
     * @locale zh
     * @brief RGBA
     */
    /**
     * @locale en
     * @brief RGBA
     */
    ByteRTCVideoPixelFormatRGBA = 4,
    /**
     * @locale zh
     * @brief IMC2
     */
    /**
     * @locale en
     * @brief IMC2
     */
    ByteRTCVideoPixelFormatIMC2 = 5,
    /**
     * @locale zh
     * @brief ARGB
     */
    /**
     * @locale en
     * @brief ARGB
     */
    ByteRTCVideoPixelFormatARGB = 7,
    /**
     * @locale zh
     * @brief NV12
     */
    /**
     * @locale en
     * @brief NV12
     */
    ByteRTCVideoPixelFormatNV12 = 8,
    /**
     * @locale zh
     * @brief Opengl Texture2D纹理
     */
    /**
     * @locale en
     * @brief Opengl Texture2D
     */
    ByteRTCVideoPixelFormatGLTexture2D = 10,
    /**
     * @locale zh
     * @brief Opengl OES纹理
     */
    /**
     * @locale en
     * @brief Opengl OES
     */
    ByteRTCVideoPixelFormatGLTextureOES = 11,
    /**
     * @locale zh
     * @brief CVPixelBuffer
     */
    /**
     * @locale en
     * @brief CVPixelBuffer
     */
    ByteRTCVideoPixelFormatCVPixelBuffer = 12
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地视频帧回调位置。
 */
/**
 * @locale en
 * @type keytype
 * @brief The position of the local video frame.
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoRenderPosition) {
    /**
     * @locale zh
     * @brief 采集后。
     */
    /**
     * @locale en
     * @brief After capturing.
     */
    ByteRTCLocalVideoRenderPositionAfterCapture = 0,
    /**
     * @locale zh
     * @brief （默认值）前处理后。
     */
    /**
     * @locale en
     * @brief (Default) After preprocessing.
     */
    ByteRTCLocalVideoRenderPositionAfterPreprocess = 1
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端视频帧回调位置。
 */
/**
 * @locale en
 * @type keytype
 * @brief The position of the remote video frame.
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoRenderPosition) {
    /**
     * @locale zh
     * @brief 解码后。
     */
    /**
     * @locale en
     * @brief After decoding.
     */
    ByteRTCRemoteVideoRenderPositionAfterDecoder = 0,
    /**
     * @locale zh
     * @brief （默认值）后处理后。
     */
    /**
     * @locale en
     * @brief (Default) After processing.
     */
    ByteRTCRemoteVideoRenderPositionAfterPostprocess = 1
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧编码格式
 */
/**
 * @locale en
 * @type keytype
 * @brief Video frame encoding format
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSinkPixelFormat) {
    /**
     * @locale zh
     * @brief 原始视频帧格式
     */
    /**
     * @locale en
     * @brief Original format
     */
    ByteRTCVideoSinkPixelFormatOriginal = 0,
    /**
     * @locale zh
     * @brief YUV I420 格式
     */
    /**
     * @locale en
     * @brief YUV I420
     */
    ByteRTCVideoSinkPixelFormatI420 = 1,
    /**
     * @locale zh
     * @brief BGRA 格式
     */
    /**
     * @locale en
     * @brief BGRA
     */
    ByteRTCVideoSinkPixelFormatBGRA = 2,
    /**
     * @locale zh
     * @brief RGBA 格式, 字节序为 R8 G8 B8 A8
     */
    /**
     * @locale en
     * @brief RGBA format
     */
    ByteRTCVideoSinkPixelFormatRGBA = 5,
    /**
     * @locale zh
     * @brief YUV NV21 格式
     */
    /**
     * @locale en
     * @brief YUV NV12
     */
    ByteRTCVideoSinkPixelFormatNV12 = 8
};

/**
 * @locale zh
 * @type keytype
 * @brief 是否将视频帧自动转正。
 */
/**
 * @locale en
 * @type keytype
 * @brief Whether the video frame needs to be automatically rotate.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoApplyRotation) {
    /**
     * @locale zh
     * @brief （默认值）不旋转。
     */
    /**
     * @locale en
     * @brief (Default) No rotation.
     */
    ByteRTCVideoApplyRotationDefault = -1,
    /**
     * @locale zh
     * @brief 自动转正视频，即根据视频帧的旋转角信息将视频帧旋转到 0 度。
     */
    /**
     * @locale en
     * @brief Automatic rotation, which rotates video frames to 0 degree based on the rotation angle information.
     */
    ByteRTCVideoApplyRotation0 = 0
};

/**
 * @locale zh
 * @type keytype
 * @brief 是否将视频帧镜像。
 */
/**
 * @locale en
 * @type keytype
 * @brief Whether the video frame needs to be mirrored.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoRenderMirrorType) {
    /**
     * @locale zh
     * @brief 开启镜像。
     */
    /**
     * @locale en
     * @brief Enable mirroring effect.
     */
    ByteRTCVideoRenderMirrorTypeOn = 1,
    /**
     * @locale zh
     * @brief （默认值）不开启镜像。
     */
    /**
     * @locale en
     * @brief (Default) No mirroring effect.
     */
    ByteRTCVideoRenderMirrorTypeOff = 2,
};

/**
 * @locale zh
 * @hidden(macOS)
 * @type keytype
 * @brief 超分状态改变原因。
 */
/**
 * @locale en
 * @hidden not available
 * @type keytype
 * @brief The reason for the change in super resolution mode.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSuperResolutionModeChangedReason) {
    /**
     * @locale zh
     * @brief 调用 setRemoteVideoSuperResolution:withMode:{@link #ByteRTCVideo#setRemoteVideoSuperResolution:withMode:} 成功关闭超分。
     */
    /**
     * @locale en
     * @brief Successfully turned off the super resolution mode by calling setRemoteVideoSuperResolution:withMode:{@link #ByteRTCVideo#setRemoteVideoSuperResolution:withMode:}.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonAPIOff = 0,
    /**
     * @locale zh
     * @brief 调用 setRemoteVideoSuperResolution:withMode:{@link #ByteRTCVideo#setRemoteVideoSuperResolution:withMode:} 成功开启超分。
     */
    /**
     * @locale en
     * @brief Successfully turned on the super resolution mode by calling setRemoteVideoSuperResolution:withMode:{@link #ByteRTCVideo#setRemoteVideoSuperResolution:withMode:}.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonAPIOn = 1,
    /**
     * @locale zh
     * @brief 开启超分失败，远端视频流的原始视频分辨率超过 640 × 360 px。
     */
    /**
     * @locale en
     * @brief Failed to turn on super-resolution mode. The original resolution of the remote video stream should not exceed 640 × 360 pixels.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonResolutionExceed = 2,
    /**
     * @locale zh
     * @brief 开启超分失败，已对一路远端流开启超分。
     */
    /**
     * @locale en
     * @brief Failed to turn on super-resolution mode. You can only turn on super-resolution mode for one stream.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonOverUse = 3,
    /**
     * @locale zh
     * @brief 设备不支持使用超分辨率。
     */
    /**
     * @locale en
     * @brief Incompatible device for super resolution.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonDeviceNotSupport = 4,
    /**
     * @locale zh
     * @brief 当前设备性能存在风险，已动态关闭
     */
    /**
     * @locale en
     * @brief the device performance is not enough, VideoSuperResolution is closed dynamically
     */
    ByteRTCVideoSuperResolutionModeChangedReasonDynamicClose = 5,
    /**
     * @locale zh
     * @brief 超分因其他原因关闭。
     */
    /**
     * @locale en
     * @brief The super-resolution mode is turned off for other reasons.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonOtherSettingDisabled = 6,
    /**
     * @locale zh
     * @brief 超分因其他原因开启。
     */
    /**
     * @locale en
     * @brief The super-resolution mode is turned on for other reasons.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonOtherSettingEnabled = 7,
    /**
     * @locale zh
     * @brief SDK 没有编译超分组件。
     */
    /**
     * @locale en
     * @brief The super-resolution mode is not compiled in the SDK.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonNoComponent = 8,
    /**
     * @locale zh
     * @brief 远端流不存在。房间 ID 或用户 ID 无效，或对方没有发布流。
     */
    /**
     * @locale en
     * @brief The remote stream does not exist. Reasons include invalid room ID, user ID, or the stream is not published.
     */
    ByteRTCVideoSuperResolutionModeChangedReasonStreamNotExist = 9,
};

/**
 * @locale zh
 * @hidden(macOS)
 * @type keytype
 * @brief 视频降噪模式状态改变原因。
 */
/**
 * @locale en
 * @hidden not available
 * @type keytype
 * @brief The reasons for the change in the video noise reduction mode.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDenoiseModeChangedReason) {
    /**
     * @locale zh
     * @brief 未知原因导致视频降噪状态改变。
     */
    /**
     * @locale en
     * @brief Video noise reduction mode changed due to unknown reasons.
     */
    ByteRTCVideoDenoiseModeChangedReasonNull = -1,
    /**
     * @locale zh
     * @brief 通过调用 setVideoDenoiser:{@link #ByteRTCVideo#setVideoDenoiser:} 成功关闭视频降噪。
     */
    /**
     * @locale en
     * @brief Successfully turned off video noise reduction by calling setVideoDenoiser:{@link #ByteRTCVideo#setVideoDenoiser:}.
     */
    ByteRTCVideoDenoiseModeChangedReasonApiOff = 0,
    /**
     * @locale zh
     * @brief 通过调用 setVideoDenoiser:{@link #ByteRTCVideo#setVideoDenoiser:} 成功开启视频降噪。
     */
    /**
     * @locale en
     * @brief Successfully turned on the video noise reduction mode by calling setVideoDenoiser:{@link #ByteRTCVideo#setVideoDenoiser:}.
     */
    ByteRTCVideoDenoiseModeChangedReasonApiOn = 1,
    /**
     * @locale zh
     * @brief 后台未配置视频降噪，视频降噪开启失败，请联系技术人员解决。
     */
    /**
     * @locale en
     * @brief Video noise reduction disabled by configuration.
     */
    ByteRTCVideoDenoiseModeChangedReasonConfigDisabled = 2,
    /**
     * @locale zh
     * @brief 后台配置开启了视频降噪。
     */
    /**
     * @locale en
     * @brief Video noise reduction enabled by configuration.
     */
    ByteRTCVideoDenoiseModeChangedReasonConfigEnabled = 3,
    /**
     * @locale zh
     * @brief 由于内部发生了异常，视频降噪关闭。
     */
    /**
     * @locale en
     * @brief Video noise reduction turned off due to internal exceptions.
     */
    ByteRTCVideoDenoiseModeChangedReasonInternalException = 4,
    /**
     * @locale zh
     * @brief 当前设备性能过载，已动态关闭视频降噪。
     */
    /**
     * @locale en
     * @brief Video noise reduction turned off due to hardware performance stress.
     */
    ByteRTCVideoDenoiseModeChangedReasonDynamicClose = 5,
    /**
     * @locale zh
     * @brief 当前设备性能裕量充足，已动态开启视频降噪。
     */
    /**
     * @locale en
     * @brief Device hardware capacity is sufficient, video noise reduction turned on.
     */
    ByteRTCVideoDenoiseModeChangedReasonDynamicOpen = 6,
    /**
     * @locale zh
     * @brief 分辨率导致视频降噪状态发生改变。分辨率过高会导致性能消耗过大，从而导致视频降噪关闭。如若希望继续使用视频降噪，可选择降低分辨率。
     */
    /**
     * @locale en
     * @brief Video noise reduction mode changed due to video resolution. High resolution leads to high hardware utilization. Reduce the resolution to recover video noise reduction.
     */
    ByteRTCVideoDenoiseModeChangedReasonResolution = 7,
};

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamType instead.
 * @type keytype
 * @brief 合流方式
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamType{@link #ByteRTCMixedStreamType} instead.
 * @type keytype
 * @brief Stream mixing type
 */
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingType) {
    /**
     * @locale zh
     * @brief 服务端合流
     */
    /**
     * @locale en
     * @brief Mix media streams on the server side.
     */
    ByteRTCStreamMixingTypeByServer = 0,
    /**
     * @locale zh
     * @brief 端云一体合流。SDK 智能决策在客户端或服务端完成合流。
     */
    /**
     * @locale en
     * @brief Intelligent stream mixing. The SDK will intelligently decide that a stream mixing task would be done on the client or the server side.
     */
    ByteRTCStreamMixingTypeByClient = 1,
};
/**
 * @locale zh
 * @type keytype
 * @brief 转推直播事件
 */
/**
 * @locale en
 * @type keytype
 * @brief Events during pushing streams to CDN
 */
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingEvent) {
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamMixingEventBase = 0,
    /**
     * @locale zh
     * @brief 请求发起转推直播任务
     */
    /**
     * @locale en
     * @brief Request to start the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStart = 1,
    /**
     * @locale zh
     * @brief 发起转推直播任务成功
     */
    /**
     * @locale en
     * @brief The task to push streams to CDN started
     */
    ByteRTCStreamMixingEventStartSuccess = 2,
    /**
     * @locale zh
     * @brief 发起转推直播任务失败
     */
    /**
     * @locale en
     * @brief Failed to start the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStartFailed = 3,
    /**
     * @locale zh
     * @brief 请求更新转推直播任务配置
     */
    /**
     * @locale en
     * @brief Request to update the configuration for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventUpdate = 4,
    /**
     * @locale zh
     * @brief 成功更新转推直播任务配置
     */
    /**
     * @locale en
     * @brief Successfully update the configuration for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventUpdateSuccess = 5,
    /**
     * @locale zh
     * @brief 更新转推直播任务配置失败
     */
    /**
     * @locale en
     * @brief Failed to update the configuration for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventUpdateFailed = 6,
    /**
     * @locale zh
     * @brief 请求结束转推直播任务
     */
    /**
     * @locale en
     * @brief Request to stop the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStop = 7,
    /**
     * @locale zh
     * @brief 结束转推直播任务成功
     */
    /**
     * @locale en
     * @brief The task to push streams to CDN stopped
     */
    ByteRTCStreamMixingEventStopSuccess = 8,
    /**
     * @locale zh
     * @brief 结束转推直播任务失败
     */
    /**
     * @locale en
     * @brief Failed to stop the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStopFailed = 9,
    /**
     * @locale zh
     * @brief 更新转推直播任务配置的请求超时
     */
    /**
     * @locale en
     * @brief Timeout for the request to update the configuration for the task to push streams to CDN.
     */
    ByteRTCStreamMixingEventChangeMixType = 10,
    /**
     * @locale zh
     * @brief 得到客户端合流音频首帧
     */
    /**
     * @locale en
     * @brief Got the first frame of the mixed audio stream by client.
     */
    ByteRTCStreamMixingEventFirstAudioFrameByClientMixer = 11,
    /**
     * @locale zh
     * @brief 收到客户端合流视频首帧
     */
    /**
     * @locale en
     * @brief Got the first frame of the mixed video stream by client.
     */
    ByteRTCStreamMixingEventFirstVideoFrameByClientMixer = 12,
    /**
     * @locale zh
     * @brief 更新转推直播任务配置超时
     */
    /**
     * @locale en
     * @brief Timeout for the request to update the configuration for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventUpdateTimeout = 13,
    /**
     * @locale zh
     * @brief 发起转推直播任务配置超时
     */
    /**
     * @locale en
     * @brief Timeout for the request to start the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStartTimeout = 14,
    /**
     * @locale zh
     * @brief 合流布局参数错误
     */
    /**
     * @locale en
     * @brief Error in the parameters of the request for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventRequestParamError = 15,
    /**
     * @locale zh
     * @brief 合流加图片
     */
    /**
     * @locale en
     * @brief Mixing image.
     */
    ByteRTCStreamMixingEventMixImage = 16,
    /**
     * @locale zh
     * @hidden internal use only
     * @valid since 3.50
     * @brief 单通合唱事件
     */
    /**
     * @locale en
     * @hidden internal use only
     * @hidden currently not available
     * @brief Simplex chorus event
     */
    ByteRTCStreamMixingEventSingleWayChorus = 17,
};
/**
 * @locale zh
 * @type keytype
 * @brief 合流方式。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream mixing type.(New)
 */
typedef NS_ENUM(NSUInteger, ByteRTCMixedStreamType) {
    /**
     * @locale zh
     * @brief 通过服务端合流
     */
    /**
     * @locale en
     * @brief Mix media streams on the server side.
     */
    ByteRTCMixedStreamByServer = 0,
    /**
     * @locale zh
     * @brief 端云一体合流。SDK 智能决策在客户端或服务端完成合流。<br>
     *        使用前，请联系技术支持同学开通，否则不生效。
     */
    /**
     * @locale en
     * @brief Intelligent stream mixing. The SDK will intelligently decide that a stream mixing task would be done on the client or the server side.<br>
     *        Before using the option, please contact the technical support. Otherwise, the option does not take effect.
     */
    ByteRTCMixedStreamByClient = 1,
};
/**
 * @locale zh
 * @type keytype
 * @brief 客户端合流回调视频格式。(新)<br>
 *        设置为系统不支持的格式时，自动回调系统默认格式。
 */
/**
 * @locale en
 * @type keytype
 * @brief The video format for client stream mixing callback.(New)<br>
 *        If the format you set is not adaptable to the system, the format will be set as the default value.
 */
typedef NS_ENUM(NSUInteger, ByteRTCMixedStreamClientMixVideoFormat) {
    /**
     * @locale zh
     * @brief YUV I420。Android、Windows 默认回调格式。支持系统：Android、Windows。
     */
    /**
     * @locale en
     * @brief YUV I420 format. The default format for Android and Windows. Supported system: Android, Windows.
     */
    ByteRTCMixedStreamClientMixVideoFormatI420 = 0,
    /**
     * @locale zh
     * @brief OpenGL GL_TEXTURE_2D 格式纹理。支持系统：安卓。
     */
    /**
     * @locale en
     * @brief OpenGL GL_TEXTURE_2D format. Supported system: Android.
     */
    ByteRTCMixedStreamClientMixVideoFormatTexture2D = 1,
    /**
     * @locale zh
     * @brief CVPixelBuffer BGRA。iOS 默认回调格式。支持系统: iOS。
     */
    /**
     * @locale en
     * @brief CVPixelBuffer BGRA format. The default format for iOS. support system: iOS.
     */
    ByteRTCMixedStreamClientMixVideoFormatCVPixelBufferBGRA = 2,
    /**
     * @locale zh
     * @brief YUV NV12。macOS 默认回调格式。支持系统: macOS。
     */
    /**
     * {en}
     * @brief YUV NV12 format. The default format for macOS. Supported system: macOS.
     */
    ByteRTCMixedStreamClientMixVideoFormatNV12 = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频编码格式。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief The video codec.(New)
 */
typedef NS_ENUM(NSUInteger, ByteRTCMixedStreamVideoCodecType) {
    /**
     * @locale zh
     * @brief H.264 格式，默认值。
     */
    /**
     * @locale en
     * @brief (Default) H.264 format.
     */
    ByteRTCMixedStreamVideoCodecTypeH264 = 0,
    /**
     * @locale zh
     * @brief ByteVC1 格式。
     */
    /**
     * @locale en
     * @brief ByteVC1 format.
     */
    ByteRTCMixedStreamVideoCodecTypeByteVC1 = 1,
};
/**
 * @locale zh
 * @type keytype
 * @brief 合流输出内容类型。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream mixing content type.(New)
 */
typedef NS_ENUM(NSUInteger, ByteRTCMixedStreamMediaType) {
    /**
     * @locale zh
     * @brief 输出的混流包含音频和视频
     */
    /**
     * @locale en
     * @brief The mixed stream contains audio and video.
     */
    ByteRTCMixedStreamMediaTypeAudioAndVideo = 0,
    /**
     * @locale zh
     * @brief 输出的混流只包含音频
     */
    /**
     * @locale en
     * @brief The mixed stream only contains audio.
     */
    ByteRTCMixedStreamMediaTypeAudioOnly = 1,
    /**
     * @locale zh
     * @brief 输出的混流只包含视频
     */
    /**
     * @locale en
     * @brief The mixed stream only contains video.
     */
    ByteRTCMixedStreamMediaTypeVideoOnly = 2,
};
/**
 * @locale zh
 * @type keytype
 * @brief 图片或视频流的缩放模式。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief The render mode.(New)
 */
typedef NS_ENUM(NSUInteger, ByteRTCMixedStreamRenderMode) {
    /**
     * @locale zh
     * @brief 视窗填满优先，默认值。<br>
     *        视频尺寸等比缩放，直至视窗被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    /**
     * @locale en
     * @brief (Default) Fill and Crop.<br>
     *        The video frame is scaled with fixed aspect ratio, until it completely fills the canvas. The region of the video exceeding the canvas will be cropped.
     */
    ByteRTCMixedStreamRenderModeHidden = 1,
    /**
     * @locale zh
     * @brief 视频帧内容全部显示优先。<br>
     *        视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成背景颜色。
     */
    /**
     * @locale en
     * @brief Fit.<br>
     *        The video frame is scaled with fixed aspect ratio, until it fits just within the canvas. Other part of the canvas is filled with the background color.
     */
    ByteRTCMixedStreamRenderModeFit = 2,
    /**
     * @locale zh
     * @brief 视频帧自适应画布。<br>
     *        视频尺寸非等比例缩放，把窗口充满。在此过程中，视频帧的长宽比例可能会发生变化。
     */
    /**
     * @locale en
     * @brief Fill the canvas.<br>
     *        The video frame is scaled to fill the canvas. During the process, the aspect ratio may change.
     */
    ByteRTCMixedStreamRenderModeAdaptive = 3,
};
/**
 * @locale zh
 * @type keytype
 * @brief 合流布局区域类型。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief  Stream mixing region type.(New)
 */
typedef NS_ENUM(NSUInteger, ByteRTCMixedStreamLayoutRegionType) {

    /**
     * @locale zh
     * @brief 合流布局区域类型为视频。
     */
    /**
     * @locale en
     * @brief The region type is a video stream.
     */
    ByteRTCMixedStreamLayoutRegionTypeVideoStream = 0,

    /**
     * @locale zh
     * @brief 合流布局区域类型为图片。
     */
    /**
     * @locale en
     * @brief The region type is an image.
     */
    ByteRTCMixedStreamLayoutRegionTypeImage = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 合流同步策略
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream mixing sync strategy.
 */
typedef NS_ENUM(NSUInteger, ByteRTCMixedStreamSyncStrategy) {
    /**
     * @locale zh
     * @brief 不使用同步策略
     */
    /**
     * @locale en
     * @brief Stream mixing no sync strategy.
     */
    ByteRTCMixedStreamSyncStrategyNoSync = 0,
    /**
     * @locale zh
     * @brief 使用音频精准同步策略
     */
    /**
     * @locale en
     * @brief Stream mixing use audio precise sync strategy.
     */
    ByteRTCMixedStreamSyncStrategyAudioPreciseSync = 1,
    /**
     * @locale zh
     * @brief 使用单通模式同步策略
     */
    /**
     * @locale en
     * @brief Stream mixing use simplex mode sync strategy.
     */
    ByteRTCMixedStreamSyncStrategySimplexModeSync = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief region 中流的类型属性
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream type in the region
 */
typedef NS_ENUM(NSUInteger, ByteRTCMixedStreamVideoType) {
    /**
     * @locale zh
     * @brief 主流。包括：<br>
     *        + 由摄像头/麦克风通过内部采集机制，采集到的流<br>
     *        + 通过自定义采集，采集到的流。
     */
    /**
     * @locale en
     * @brief Mainstream, including: <br>
     *       + Video/audio captured by the the camera/microphone using internal capturing; <br>
     *       + Video/audio captured by custom method.
     */
    ByteRTCMixedStreamVideoTypeMain = 0,

    /**
     * @locale zh
     * @brief 屏幕流。
     */
    /**
     * @locale en
     * @brief Screen-sharing stream.
     */
    ByteRTCMixedStreamVideoTypeScreen = 1,
};
/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamClientMixVideoFormat{@link #ByteRTCMixedStreamClientMixVideoFormat} instead.
 * @type keytype
 * @brief 客户端合流回调视频格式。设置为系统不支持的格式时，自动回调系统默认格式。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamClientMixVideoFormat{@link #ByteRTCMixedStreamClientMixVideoFormat} instead.
 * @type keytype
 * @brief The video format for client stream mixing callback. If the format you set is not adaptable to the system, the format will be set as the default value.
 */
typedef NS_ENUM(NSUInteger, ByteRTCClientMixVideoFormat) {
    /**
     * @locale zh
     * @brief YUV I420。Android、Windows 默认回调格式。支持系统：Android、Windows。
     */
    /**
     * @locale en
     * @brief YUV I420 format. The default format for Android and Windows. Supported system: Android, Windows.
     */
    ByteRTCClientMixVideoFormatI420 = 0,
    /**
     * @locale zh
     * @brief OpenGL GL_TEXTURE_2D 格式纹理。支持系统：安卓。
     */
    /**
     * @locale en
     * @brief OpenGL GL_TEXTURE_2D format. Supported system: Android.
     */
    ByteRTCClientMixVideoFormatTexture2D = 1,
    /**
     * @locale zh
     * @brief CVPixelBuffer BGRA。iOS 默认回调格式。支持系统: iOS。
     */
    /**
     * @locale en
     * @brief CVPixelBuffer BGRA format. The default format for iOS. support system: iOS.
     */
    ByteRTCClientMixVideoFormatCVPixelBufferBGRA = 2,
    /**
     * @locale zh
     * @brief YUV NV12。macOS 默认回调格式。支持系统: macOS。
     */
    /**
     * @locale en
     * @brief YUV NV12 format. The default format for macOS. Supported system: macOS.
     */
    ByteRTCClientMixVideoFormatNV12 = 3,
};

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamVideoCodecType{@link #ByteRTCMixedStreamVideoCodecType} instead.
 * @type keytype
 * @brief 视频编码格式。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamVideoCodecType{@link #ByteRTCMixedStreamVideoCodecType} instead.
 * @type keytype
 * @brief The video codec.
 */
typedef NS_ENUM(NSUInteger, ByteRTCTranscodingVideoCodec) {
    /**
     * @locale zh
     * @brief H.264 格式，默认值。
     */
    /**
     * @locale en
     * @brief (Default) H.264 format.
     */
    ByteRTCTranscodingVideoCodecH264 = 0,
    /**
     * @locale zh
     * @brief ByteVC1 格式。
     */
    /**
     * @locale en
     * @brief ByteVC1 format.
     */
    ByteRTCTranscodingVideoCodecH265 = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 服务端合流转推 SEI 内容。
 */
/**
 * @locale en
 * @type keytype
 * @brief Content of SEI sent while pushing mixed stream to CDN.
 */
typedef NS_ENUM(NSInteger, ByteRTCMixedStreamSEIContentMode) {
    /**
     * @locale zh
     * @brief 视频流中包含全部的 SEI 信息。默认设置。
     */
    /**
     * @locale en
     * @brief The video stream contains all the SEI information. Default value.
     */
    ByteRTCMixedStreamSEIContentModeDefault = 0,
    /**
     * @locale zh
     * @brief 随非关键帧传输的 SEI 数据中仅包含音量信息。<br>
     *        当设置 `ByteRTCMixedStreamServerControlConfig.enableVolumeIndication` 为 True 时，此参数设置生效。
     */
    /**
     * @locale en
     * @brief The SEI data transmitted with non-key frames contains volume information only.<br>
     *        This parameter only takes effect after you set `ByteRTCMixedStreamServerControlConfig.enableVolumeIndication` to "True".
     */
    ByteRTCMixedStreamSEIContentModeEnableVolumeIndication = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 服务端合流转推发起模式。
 */
/**
 * @locale en
 * @type keytype
 * @brief The initiation mode for pushing the stream mixed on the server side to CDN.
 */
typedef NS_ENUM(NSInteger, ByteRTCMixedStreamPushMode) {
    /**
     * @locale zh
     * @brief 无用户发布媒体流时，发起合流任务无效。默认设置。<br>
     *        当有用户发布媒体流时，才能发起合流任务。
     */
    /**
     * @locale en
     * @brief The initiation of a stream mixing task is dependent on a user actively publishing media streams.
     */
    ByteRTCMixedStreamPushModeOnStream = 0,
    /**
     * @locale zh
     * @brief 无用户发布媒体流时，可以使用占位图发起合流任务。<br>
     *        占位图设置参看 alternateImageUrl{@link #ByteRTCMixedStreamLayoutRegionConfig#alternateImageUrl} 和 alternateImageFillMode{@link #ByteRTCMixedStreamLayoutRegionConfig#alternateImageFillMode}
     */
    /**
     * @locale en
     * @brief Even if no user is actively publishing media streams, it is still possible to initiate a stream mixing task using a placeholder image.<br>
     *        See alternateImageUrl{@link #ByteRTCMixedStreamLayoutRegionConfig#alternateImageUrl} and alternateImageFillMode{@link #ByteRTCMixedStreamLayoutRegionConfig#alternateImageFillMode} for setting a placeholder image.
     */
    ByteRTCMixedStreamPushModeOnStartRequest = 1,
};
/**
 * @locale zh
 * @type keytype
 * @brief 服务端合流占位图填充模式。
 */
/**
 * @locale en
 * @type keytype
 * @brief The fill mode of the placeholder image.
 */
typedef NS_ENUM(NSInteger, ByteRTCMixedStreamAlternateImageFillMode) {
    /**
     * @locale zh
     * @brief 占位图跟随用户原始视频帧相同的比例缩放。默认设置。
     */
    /**
     * @locale en
     * @brief The placeholder image is scaled with the same aspect ratio as the user's original video frame. Default setting.
     */
    ByteRTCMixedStreamAlternateImageFillModeFit = 0,
    /**
     * @locale zh
     * @brief 占位图不跟随用户原始视频帧相同的比例缩放，保持图片原有比例。
     */
    /**
     * @locale en
     * @brief The placeholder image is not scaled with the same aspect ratio as the user's original video frame. It maintains the original aspect ratio.
     */
    ByteRTCMixedStreamAlternateImageFillModeFill = 1,
};
/**
 * @locale zh
 * @type errorcode
 * @brief 单流转推直播错误码
 */
/**
 * @locale en
 * @type errorcode
 * @brief Errors occurring during pushing a single stream to CDN
 */
typedef NS_ENUM(NSUInteger, ByteRTCSingleStreamPushEvent) {
    /**
     * @hidden for internal use only
     */
    ByteRTCSingleStreamPushEventBase = 0,
    /**
    * @locale zh
    * @brief 开始推流。
    */
   /**
    * @locale en
    * @brief Starting pushing a single stream to CDN.
    */
    ByteRTCSingleStreamPushEventStart = 1,
    /**
    * @locale zh
    * @brief 推流成功。
    */
   /**
    * @locale en
    * @brief Successfully pushed a single stream to CDN.
    */
    ByteRTCSingleStreamPushEventStartSuccess = 2,
    /**
    * @locale zh
    * @brief 推流失败。
    */
   /**
    * @locale en
    * @brief Failed to push a single stream to CDN.
    */
    ByteRTCSingleStreamPushEventStartFailed = 3,
    /**
     * @locale zh
     * @brief 停止推流。
     */
    /**
     * @locale en
     * @brief Stop pushing a single stream to CDN.
     */
    ByteRTCSingleStreamPushEventStop = 4,
    /**
    * @locale zh
    * @brief 单流转推直播任务处理超时，请检查网络状态并重试。
    */
   /**
    * @locale en
    * @brief Request timed out. Please check network status and retry.
    */
    ByteRTCSingleStreamPushEventTimeout = 5,
    /**
     * @locale zh
     * @brief 参数错误。
     */
    /**
     * @locale en
     * @brief Request failed due to invalid parameter.
     */
    ByteRTCSingleStreamPushEventParamError = 6,
};

/**
 * @locale zh
 * @type keytype
 * @brief 订阅媒体的类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Type of the media stream subscribed to
 */
typedef NS_ENUM(NSInteger, ByteRTCSubscribeMediaType) {
    /**
     * @locale zh
     * @brief 既不订阅音频，也不订阅视频
     */
    /**
     * @locale en
     * @brief Neither audio nor video
     */
    ByteRTCSubscribeMediaTypeNone = 0,
    /**
     * @locale zh
     * @brief 只订阅音频，不订阅视频
     */
    /**
     * @locale en
     * @brief Audio only
     */
    ByteRTCSubscribeMediaTypeAudioOnly = 1,
    /**
     * @locale zh
     * @brief 只订阅视频，不订阅音频
     */
    /**
     * @locale en
     * @brief Video only
     */
    ByteRTCSubscribeMediaTypeVideoOnly = 2,
    /**
     * @locale zh
     * @brief 同时订阅音频和视频
     */
    /**
     * @locale en
     * @brief Both audio and video
     */
    ByteRTCSubscribeMediaTypeAudioAndVideo = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 暂停/恢复接收远端的媒体流类型。
 */
/**
 * @locale en
 * @type keytype
 * @brief Type of the stream to be paused/resumed
 */
typedef NS_ENUM(NSInteger, ByteRTCPauseResumControlMediaType) {
    /**
     * @locale zh
     * @brief 只控制音频，不影响视频
     */
    /**
     * @locale en
     * @brief Only control audio, not affect video
     */
    ByteRTCControlMediaTypeAudio = 0,
    /**
     * @locale zh
     * @brief 只控制视频，不影响音频
     */
    /**
     * @locale en
     * @brief Only control video, not affect audio
     */
    ByteRtcControlMediaTypeVideo = 1,
    /**
     * @locale zh
     * @brief 同时控制音频和视频
     */
    /**
     * @locale en
     * @brief Simultaneous control of audio and video
     */
    ByteRtcControlMediaTypeAudioAndVideo = 2,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 视频输入类型
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief Video input type
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaInputType) {
    /**
     * @locale zh
     * @brief 自定义采集。  <br>
     *        设置完成后方可直接向 SDK 推送视频帧。
     */
    /**
     * @locale en
     * @brief Custom collection.   <br>
     *         After setting, you can push video frames directly to the SDK.
     */
    ByteRTCMediaInputTypeExternal = 0,
    /**
     * @locale zh
     * @brief 内部 SDK 采集。  <br>
     *        此设置仅切换至内部采集，你需继续调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 开启内部采集。
     */
    /**
     * @locale en
     * @brief Internal SDK acquisition. <br>
     *         This setting only switches to internal collection. You need to continue to call startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to open internal collection.
     */
    ByteRTCMediaInputTypeInternal = 1
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频输入源类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Video source type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSourceType) {
    /**
     * @locale zh
     * @brief 自定义采集视频源
     */
    /**
     * @locale en
     * @brief Custom video source
     */
    ByteRTCVideoSourceTypeExternal = 0,
    /**
     * @locale zh
     * @brief 内部采集视频源
     */
    /**
     * @locale en
     * @brief Internal video capture
     */
    ByteRTCVideoSourceTypeInternal = 1,
    /**
     * @locale zh
     * @brief 自定义编码视频源。  <br>
     *        你仅需推送分辨率最大的一路编码后视频流，SDK 将自动转码生成多路小流
     */
    /**
     * @locale en
     * @brief Custom encoded video source.   <br>
     *         Push the encoded video stream with the largest resolution, and the SDK will automatically transcode to generate multiple lower-quality streams for Simulcast.
     */
    ByteRTCVideoSourceTypeEncodedAutoSimulcast = 2,
    /**
     * @locale zh
     * @brief 自定义编码视频源。  <br>
     *        SDK 不会自动生成多路流，你需要自行生成并推送多路流
     */
    /**
     * @locale en
     * @brief Custom encoded video source.   <br>
     *         The SDK does not automatically generate multiple streams for Simulcast, you need to generate and push streams of different qualities.
     */
    ByteRTCVideoSourceTypeEncodedManualSimulcast = 3
};

/**
 * @locale zh
 * @type keytype
 * @brief Alpha 通道相对于 RGB 通道数据的排列位置。
 */
typedef NS_ENUM(NSInteger, ByteRTCAlphaLayout) {
    /**
     * @locale zh
     * @brief Alpha 数据置于 RGB 数据上方。
     */
    ByteRTCAlphaLayoutTop = 0,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief Alpha 数据置于 RGB 数据下方。
     */
    ByteRTCAlphaLayoutBottom = 1,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief Alpha 数据置于 RGB 数据左方。
     */
    ByteRTCAlphaLayoutLeft = 2,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief Alpha 数据置于 RGB 数据右方。
     */
    ByteRTCAlphaLayoutRight = 3,
};

/** {zh}
 * @type keytype
 * @brief 数码变焦参数类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Digital Zoom type
 */
typedef NS_ENUM(NSInteger, ByteRTCZoomConfigType) {
    /**
     * @locale zh
     * @brief 设置缩放系数
     */
    /**
     * @locale en
     * @brief set ZoomIn/ZoomOut config
     */
    ByteRTCZoomConfigTypeFocusOffset = 0,
    /**
     * @locale zh
     * @brief 设置移动步长
     */
    /**
     * @locale en
     * @brief set move config
     */
    ByteRTCZoomConfigTypeMoveOffset = 1
};

/**
 * @locale zh
 * @type keytype
 * @brief 数字变焦操作类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Action of the digital zoom control
 */
typedef NS_ENUM(NSInteger, ByteRTCZoomDirectionType) {
    /**
     * @locale zh
     * @brief 相机向左移动
     */
    /**
     * @locale en
     * @brief Move to the left.
     */
    ByteRTCZoomDirectionTypeMoveLeft = 0,
    /**
     * @locale zh
     * @brief 相机向右移动
     */
    /**
     * @locale en
     * @brief Move to the right.
     */
    ByteRTCZoomDirectionTypeMoveRight = 1,
    /**
     * @locale zh
     * @brief 相机向上移动
     */
    /**
     * @locale en
     * @brief Move upwards.
     */
    ByteRTCZoomDirectionTypeMoveUp = 2,
    /**
     * @locale zh
     * @brief 相机向下移动
     */
    /**
     * @locale en
     * @brief Move downwards.
     */
    ByteRTCZoomDirectionTypeMoveDown = 3,
    /**
     * @locale zh
     * @brief 相机缩小焦距
     */
    /**
     * @locale en
     * @brief Zoom out.
     */
    ByteRTCZoomDirectionTypeZoomOut = 4,
    /**
     * @locale zh
     * @brief 相机放大焦距
     */
    /**
     * @locale en
     * @brief Zoom in.
     */
    ByteRTCZoomDirectionTypeZoomIn = 5,
    /**
     * @locale zh
     * @brief 恢复到原始画面
     */
    /**
     * @locale en
     * @brief Reset digital zoom.
     */
    ByteRTCZoomDirectionTypeReset = 6
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频解码方式
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video decoding method
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDecoderConfig) {
    /**
     * @locale zh
     * @brief 开启 SDK 内部解码，只回调解码后的数据。回调为renderPixelBuffer:rotation:contentType:extendedData:{@link #ByteRTCVideoSinkDelegate#renderPixelBuffer:rotation:contentType:extendedData:}
     */
    /**
     * @locale en
     * @brief Enable SDK internal decoding, only callback the decoded data
     */
    ByteRTCVideoDecoderConfigRaw = 0,
    /**
     * @locale zh
     * @brief 开启自定义解码，只回调解码前数据。回调为onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:}。
     */
    /**
     * @locale en
     * @brief Turn on custom decoding, only callback the data before decoding
     */
    ByteRTCVideoDecoderConfigEncode = 1,
    /**
     * @locale zh
     * @brief 开启 SDK 内部解码，同时回调解码前和解码后的数据
     */
    /**
     * @locale en
     * @brief Enable SDK internal decoding, and call back the data before and after decoding at the same time
     */
    ByteRTCVideoDecoderConfigBoth = 2
};

/**
 * @locale zh
 * @type keytype
 * @brief 虚拟背景类型。
 */
/**
 * @locale en
 * @type keytype
 * @brief Virtual background type.
 */
typedef NS_ENUM(NSInteger, ByteRTCVirtualBackgroundSourceType){
    /**
     * @locale zh
     * @brief 使用纯色背景替换视频原有背景。
     */
    /**
     * @locale en
     * @brief Replace the original background with a solid color.
     */
    ByteRTCVirtualBackgroundSourceTypeColor = 0,
    /**
     * @locale zh
     * @brief 使用自定义图片替换视频原有背景。
     */
    /**
     * @locale en
     * @brief Replace the original background with the specified image.
     */
    ByteRTCVirtualBackgroundSourceTypeImage = 1
};

/**
 * @locale zh
 * @type keytype
 * @brief 摄像头类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Camera type
 */
typedef NS_ENUM(NSInteger, ByteRTCCameraID) {
    /**
     * @locale zh
     * @brief 前置摄像头
     */
    /**
     * @locale en
     * @brief Front-facing camera
     */
    ByteRTCCameraIDFront = 0,
    /**
     * @locale zh
     * @brief 后置摄像头
     */
    /**
     * @locale en
     * @brief Back-facing camera
     */
    ByteRTCCameraIDBack = 1,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 外接摄像头
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief External camera
     */
    ByteRTCCameraIDExternal = 2,
    /**
     * @locale zh
     * @brief 无效值
     */
    /**
     * @locale en
     * @brief Invalid value
     */
    ByteRTCCameraIDInvalid = 3,
};
/**
 * @locale zh
 * @type errorcode
 * @brief 转推直播错误码
 */
/**
 * @locale en
 * @type errorcode
 * @brief Errors occuring during pushing streams to CDN
 */
typedef NS_ENUM(NSInteger, ByteRtcTranscoderErrorCode) {
    /**
     * @locale zh
     * @brief 推流成功。
     */
    /**
     * @locale en
     * @brief Successfully pushed streams to target CDN.
     */
    ByteRtcTranscoderErrorCodeOK = 0,
    /**
     * @locale zh
     * @brief 未定义的合流错误
     */
    /**
     * @locale en
     * @brief Undefined error
     */
    ByteRtcTranscoderErrorCodeBase = 1090,
    /**
     * @locale zh
     * @brief 客户端 SDK 检测到无效推流参数。
     */
    /**
     * @locale en
     * @brief Invalid parameters detected by client SDK.
     */
    ByteRtcTranscoderErrorCodeInvalidParam = 1091,
    /**
     * @locale zh
     * @brief 状态错误，需要在状态机正常状态下发起操作
     */
    /**
     * @locale en
     * @brief Program runs with an error, the state machine is in abnormal condition.
     */
    ByteRtcTranscoderErrorCodeInvalidState = 1092,
    /**
     * @locale zh
     * @brief 无效操作
     */
    /**
     * @locale en
     * @brief Invalid operation
     */
    ByteRtcTranscoderErrorCodeInvalidOperator = 1093,
    /**
     * @locale zh
     * @brief 转推直播任务处理超时，请检查网络状态并重试
     */
    /**
     * @locale en
     * @brief Request timed out. Please check network status and retry.
     */
    ByteRtcTranscoderErrorCodeTimeOut = 1094,
    /**
     * @locale zh
     * @brief 服务端检测到错误的推流参数
     */
    /**
     * @locale en
     * @brief Invalid parameters detected by the server.
     */
    ByteRtcTranscoderErrorCodeInvalidParamByServer = 1095,
    /**
     * @locale zh
     * @brief 对流的订阅超时
     */
    /**
     * @locale en
     * @brief Subscription to the stream has expired.
     */
    ByteRtcTranscoderErrorCodeSubTimeoutByServer = 1096,
    /**
     * @locale zh
     * @brief 合流服务端内部错误。
     */
    /**
     * @locale en
     * @brief Internal server error.
     */
    ByteRtcTranscoderErrorCodeInvalidStateByServer = 1097,
    /**
     * @locale zh
     * @brief 合流服务端推 CDN 失败。
     */
    /**
     * @locale en
     * @brief The server failed to push streams to CDN.
     */
    ByteRtcTranscoderErrorCodeAuthenticationByCDN = 1098,
    /**
     * @locale zh
     * @brief 服务端接收信令超时，请检查网络状态并重试。
     */
    /**
     * @locale en
     * @brief Signaling connection timeout error. Please check network status and retry.
     */
    ByteRtcTranscoderErrorCodeTimeoutBySignaling = 1099,
    /**
     * @locale zh
     * @brief 图片合流失败。
     */
    /**
     * @locale en
     * @brief Fail to mix image.
     */
    ByteRtcTranscoderErrorCodeMixImageFail = 1100,
    /**
     * @locale zh
     * @brief 服务端未知错误。
     */
    /**
     * @locale en
     * @brief Unknown error from server.
     */
    ByteRtcTranscoderErrorCodeUnKnownErrorByServer = 1101,
    /**
     * @locale zh
     * @hidden internal use only
     * @valid since 3.50
     * @brief 缓存未同步。
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief The cache is not synchronized.
     */
    ByteRtcTranscoderErrorCodeCacheSyncWorse = 1102,
    /**
     * @hidden for internal use only
     */
    ByteRtcTranscoderErrorCodeMax = 1199,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 转推直播错误码。(新)
 */
/**
 * @locale en
 * @type errorcode
 * @brief Errors occurring during pushing streams to CDN.(New)
 */
typedef NS_ENUM(NSInteger, ByteRTCStreamMixingErrorCode) {
    /**
     * @locale zh
     * @brief 推流成功。
     */
    /**
     * @locale en
     * @brief Successfully pushed streams to target CDN.
     */
    ByteRTCStreamMixingErrorCodeOK = 0,
    /**
     * @locale zh
     * @brief 未定义的合流错误
     */
    /**
     * @locale en
     * @brief Undefined error
     */
    ByteRTCStreamMixingErrorCodeBase = 1090,
    /**
     * @locale zh
     * @brief 客户端 SDK 检测到无效推流参数。
     */
    /**
     * @locale en
     * @brief Invalid parameters detected by client SDK.
     */
    ByteRTCStreamMixingErrorCodeInvalidParam = 1091,
    /**
     * @locale zh
     * @brief 状态错误，需要在状态机正常状态下发起操作
     */
    /**
     * @locale en
     * @brief Program runs with an error, the state machine is in abnormal condition.
     */
    ByteRTCStreamMixingErrorCodeInvalidState = 1092,
    /**
     * @locale zh
     * @brief 无效操作
     */
    /**
     * @locale en
     * @brief Invalid operation
     */
    ByteRTCStreamMixingErrorCodeInvalidOperator = 1093,
    /**
     * @locale zh
     * @brief 转推直播任务处理超时，请检查网络状态并重试
     */
    /**
     * @locale en
     * @brief Request timed out. Please check network status and retry.
     */
    ByteRTCStreamMixingErrorCodeTimeOut = 1094,
    /**
     * @locale zh
     * @brief 服务端检测到错误的推流参数
     */
    /**
     * @locale en
     * @brief Invalid parameters detected by the server.
     */
    ByteRTCStreamMixingErrorCodeInvalidParamByServer = 1095,
    /**
     * @locale zh
     * @brief 对流的订阅超时
     */
    /**
     * @locale en
     * @brief Subscription to the stream has expired.
     */
    ByteRTCStreamMixingErrorCodeSubTimeoutByServer = 1096,
    /**
     * @locale zh
     * @brief 合流服务端内部错误。
     */
    /**
     * @locale en
     * @brief Internal server error.
     */
    ByteRTCStreamMixingErrorCodeInvalidStateByServer = 1097,
    /**
     * @locale zh
     * @brief 合流服务端推 CDN 失败。
     */
    /**
     * @locale en
     * @brief The server failed to push streams to CDN.
     */
    ByteRTCStreamMixingErrorCodeAuthenticationByCDN = 1098,
    /**
     * @locale zh
     * @brief 服务端接收信令超时，请检查网络状态并重试。
     */
    /**
     * @locale en
     * @brief Signaling connection timeout error. Please check network status and retry.
     */
    ByteRTCStreamMixingErrorCodeTimeoutBySignaling = 1099,
    /**
     * @locale zh
     * @brief 图片合流失败。
     */
    /**
     * @locale en
     * @brief Fail to mix image.
     */
    ByteRTCStreamMixingErrorCodeMixImageFail = 1100,
    /**
     * @locale zh
     * @brief 服务端未知错误。
     */
    /**
     * @locale en
     * @brief Unknown error from server.
     */
    ByteRTCStreamMixingErrorCodeUnKnownErrorByServer = 1101,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 缓存未同步。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief The cache is not synchronize.
     */
    ByteRTCStreamMixingErrorCodeCacheSyncWorse = 1102,
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamMixingErrorCodeMax = 1199,
};
/**
 * @locale zh
 * @type keytype
 * @brief 本地录制的媒体类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Locally recorded media type
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingType) {
    /**
     * @locale zh
     * @brief 只录制音频
     */
    /**
     * @locale en
     * @brief Audio only
     */
    ByteRTCRecordingTypeAudioOnly = 0,
    /**
     * @locale zh
     * @brief 只录制视频
     */
    /**
     * @locale en
     * @brief Video only
     */
    ByteRTCRecordingTypeVideoOnly = 1,
    /**
     * @locale zh
     * @brief 同时录制音频和视频
     */
    /**
     * @locale en
     * @brief Record audio and video simultaneously
     */
    ByteRTCRecordingTypeVideoAndAudio = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 屏幕采集媒体类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Screen media type
 */
typedef NS_ENUM(NSInteger, ByteRTCScreenMediaType) {
    /**
     * @locale zh
     *@brief 只采集视频数据
     */
    /**
     * @locale en
     *@brief only capture video data
     */
    ByteRTCScreenMediaTypeVideoOnly = 0,
    /**
     * @locale zh
     *@brief 只采集音频数据
     */
    /**
     * @locale en
     *@brief only capture audio data
     */
    ByteRTCScreenMediaTypeAudioOnly = 1,
    /**
     * @locale zh
     *@brief 音视频数据都采集
     */
    /**
     * @locale en
     *@brief capture video && audio data
     */
    ByteRTCScreenMediaTypeVideoAndAudio = 2
};

/**
 * @locale zh
 * @type keytype
 * @brief 屏幕采集对象的类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Type of the screen capture object
 */
typedef NS_ENUM(NSUInteger, ByteRTCScreenCaptureSourceType) {
    /**
     * @locale zh
     * @brief 类型未知
     */
    /**
     * @locale en
     * @brief Type unknown
     */
    ByteRTCScreenCaptureSourceTypeUnknown = 0,
    /**
     * @locale zh
     * @brief 应用程序的窗口
     */
    /**
     * @locale en
     * @brief Application window
     */
    ByteRTCScreenCaptureSourceTypeWindow = 1,
    /**
     * @locale zh
     * @brief 桌面
     */
    /**
     * @locale en
     * @brief Desktop
     */
    ByteRTCScreenCaptureSourceTypeScreen = 2
};
/**
 * @locale zh
 * @type keytype
 * @region 屏幕共享
 * @brief 内部采集屏幕视频流时，是否采集鼠标信息。
 */
/**
 * @locale en
 * @type keytype
 * @region Screen sharing
 * @brief Whether to capture the mouse cursor when capturing screen streams by RTC.
 */
typedef NS_ENUM(NSUInteger, ByteRTCMouseCursorCaptureState) {
    /**
     * @locale zh
     * @brief 采集鼠标信息。
     */
    /**
     * @locale en
     * @brief  Yes.
     */
    ByteRTCMouseCursorCaptureStateOn,
    /**
     * @locale zh
     * @brief 不采集鼠标信息。
     */
    /**
     * @locale en
     * @brief No.
     */
    ByteRTCMouseCursorCaptureStateOff,
};
/**
 * @locale zh
 * @type keytype
 * @brief 屏幕共享时的边框高亮设置。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Configure how a border is highlighted when you share your screen.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCHighlightConfig: NSObject
/**
 * @locale zh
 * @brief 是否显示高亮边框，默认显示。
 */
/**
 * @locale en
 * @brief Whether to display a highlighted border. A border is highlighted by default.
 */
@property (assign, nonatomic) BOOL enableHighlight;
/**
 * @locale zh
 * @brief 边框的颜色, 颜色格式为十六进制 ARGB: 0xAARRGGB。
 */
/**
 * @locale en
 * @brief Color(ARGB format: 0xAARRGGBB).
 */
@property (assign, nonatomic) uint32_t borderColor;
/**
 * @locale zh
 * @brief 边框的宽度，单位：像素。
 */
/**
 * @locale en
 * @brief Width(in pixel).
 */
@property (assign, nonatomic) int borderWidth;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 相机补光灯状态
 */
/**
 * @locale en
 * @type keytype
 * @brief Torch status
 */
typedef NS_ENUM(NSInteger, ByteRTCTorchState) {
    /**
     * @locale zh
     * @brief 相机补光灯关闭
     */
    /**
     * @locale en
     * @brief Torch off
     */
    ByteRTCTorchStateOff = 0,
    /**
     * @locale zh
     * @brief 相机补光灯打开
     */
    /**
     * @locale en
     * @brief Torch on
     */
    ByteRTCTorchStateOn = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 当前视频设备类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Current audio device type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDeviceType) {
    /**
     * @locale zh
     * @brief 未知视频设备
     */
    /**
     * @locale en
     * @brief Unknow video device
     */
    ByteRTCVideoDeviceTypeUnknown = -1,
    /**
     * @locale zh
     * @brief 视频渲染设备类型
     */
    /**
     * @locale en
     * @brief Video Rendering Device Type
     */
    ByteRTCVideoDeviceTypeRenderDevice = 0,
    /**
     * @locale zh
     * @brief 视频采集设备类型
     */
    /**
     * @locale en
     * @brief Video Acquisition Device Type
     */
    ByteRTCVideoDeviceTypeCaptureDevice = 1,
    /**
     * @locale zh
     * @brief 屏幕流视频设备
     */
    /**
     * @locale en
     *@brief Screen Capture Device Type
     */
    ByteRTCVideoDeviceTypeScreenCaptureDevice = 2
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体流类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Media stream type
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCMediaStreamType) {
    /**
     * @locale zh
     * @brief 只控制音频
     */
    /**
     * @locale en
     * @brief Controls audio only
     */
    ByteRTCMediaStreamTypeAudio = (1 << 0),
    /**
     * @locale zh
     * @brief 只控制视频
     */
    /**
     * @locale en
     * @brief Controls video only
     */
    ByteRTCMediaStreamTypeVideo = (1 << 1),
    /**
     * @locale zh
     * @brief 同时控制音频和视频
     */
    /**
     * @locale en
     * @brief Controls both audio and video
     */
    ByteRTCMediaStreamTypeBoth = ByteRTCMediaStreamTypeAudio | ByteRTCMediaStreamTypeVideo,
};

/**
 * @locale zh
 * @type keytype
 * @brief 占发布端原始帧率的比例
 */
/**
 * @locale en
 * @type keytype
 * @brief Ratio to the original video frame rate of the publisher
 */
typedef NS_ENUM(NSUInteger, ByteRTCFrameRateRatio) {
    /**
     * @locale zh
     * @brief 100%
     */
    /**
     * @locale en
     * @brief 100%
     */
    ByteRTCFrameRateRatioOrigin = 0,
    /**
     * @locale zh
     * @brief 50%
     */
    /**
     * @locale en
     * @brief 50%
     */
    ByteRTCFrameRateRatioHalf = 1,
    /**
     * @locale zh
     * @brief 25%
     */
    /**
     * @locale en
     * @brief 25%
     */
    ByteRTCFrameRateRatioQuater = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频旋转模式
 */
/**
 * @locale en
 * @type keytype
 * @brief Video orientation
 */
typedef NS_ENUM(NSUInteger, ByteRTCVideoRotationMode) {
    /**
     * @locale zh
     * @brief App 方向
     */
    /**
     * @locale en
     * @brief The orientation of the App
     */
    ByteRTCVideoRotationModeFollowApp = 0,
    /**
     * @locale zh
     * @brief 重力方向
     */
    /**
     * @locale en
     * @brief Gravity
     */
    ByteRTCVideoRotationModeFollowGSensor = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 弱光适应类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Low light adjusted type
 */
typedef NS_ENUM(NSUInteger, ByteRTCVideoEnhancementMode) {
    /**
     * @locale zh
     * @brief 关闭弱光适应
     */
    /**
     * @locale en
     * @brief Turn off low light adaptation
     */
    ByteRTCVideoEnhancementModeDisabled = 0,

    /**
     * @locale zh
     * @brief 开启弱光适应
     */
    /**
     * @locale en
     * @brief Turn on low light adaptation auto
     */
    ByteRTCVideoEnhancementModeAuto = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 人像属性检测参数
 */
/**
 * @locale en
 * @type keytype
 * @brief Expression detection configuration
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectConfig : NSObject
/**
 * @locale zh
 * @brief 是否开启年龄检测。
 */
/**
 * @locale en
 * @brief Whether to enable age detection.
 */
@property (assign, nonatomic) BOOL enableAgeDetect;
/**
 * @locale zh
 * @brief 是否开启性别检测。
 */
/**
 * @locale en
 * @brief Whether to enable gender detection.
 */
@property (assign, nonatomic) BOOL enableGenderDetect;
/**
 * @locale zh
 * @brief 是否开启表情检测。
 */
/**
 * @locale en
 * @brief Whether to enable emotion detection.
 */
@property (assign, nonatomic) BOOL enableEmotionDetect;
/**
 * @locale zh
 * @brief 是否开启吸引力检测。
 */
/**
 * @locale en
 * @brief Whether to enable attractiveness detection.
 */
@property (assign, nonatomic) BOOL enableAttractivenessDetect;
/**
 * @locale zh
 * @brief 是否开启开心程度检测。
 */
/**
 * @locale en
 * @brief Whether to enable happiness detection.
 */
@property (assign, nonatomic) BOOL enableHappinessDetect;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 人像属性检测信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Expression detect information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectInfo : NSObject
/**
* @locale zh
* @brief 预测年龄，取值范围 (0, 100)。
*/
/**
* @locale en
* @brief The estimated age in range of (0, 100).
*/
@property (assign, nonatomic) float age;
/**
* @locale zh
* @brief 预测为男性的概率，取值范围 (0.0, 1.0)。
*/
/**
* @locale en
* @brief The estimated probability of being a male in range of (0.0, 1.0).
*/
@property (assign, nonatomic) float boyProb;
/**
* @locale zh
* @brief 预测的吸引力分数，取值范围 (0, 100)。
*/
/**
* @locale en
* @brief The estimated attractiveness in range of (0, 100).
*/
@property (assign, nonatomic) float attractive;
/**
* @locale zh
* @brief 预测的微笑程度，取值范围 (0, 100)。
*/
/**
* @locale en
* @brief The estimated happy score in range of (0, 100).
*/
@property (assign, nonatomic) float happyScore;
/**
* @locale zh
* @brief 预测的伤心程度，取值范围 (0, 100)。
*/
/**
* @locale en
* @brief The estimated sad score in range of (0, 100).
*/
@property (assign, nonatomic) float sadScore;
/**
* @locale zh
* @brief 预测的生气程度，取值范围 (0, 100)。
*/
/**
* @locale en
* @brief The estimated angry score in range of (0, 100).
*/
@property (assign, nonatomic) float angryScore;
/**
* @locale zh
* @brief 预测的吃惊程度，取值范围 (0, 100)。
*/
/**
* @locale en
* @brief The estimated surprise score in range of (0, 100).
*/
@property (assign, nonatomic) float surpriseScore;
/**
* @locale zh
* @brief 预测的情绪激动程度，取值范围 (0, 100)。
*/
/**
* @locale en
* @brief The estimated emotional arousal in range of (0, 100).
*/
@property (assign, nonatomic) float arousal;
/**
* @locale zh
* @brief 预测的情绪正负程度，取值范围 (-100, 100)。
*/
/**
* @locale en
* @brief The estimated emotional valence in range of (-100, 100).
*/
@property (assign, nonatomic) float valence;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 人像属性检测结果
 */
/**
 * @locale en
 * @type keytype
 * @brief Expression Detection Result
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectResult : NSObject
/**
 * @locale zh
 * @brief 特征识别结果 <br>
 *        + 0：识别成功 <br>
 *        + !0：识别失败 
 */
/**
 * @locale en
 * @brief Expression detection result <br>
 *        + 0: Success <br>
 *        + !0: Failure 
 */
@property (assign, nonatomic) int detectResult;
/**
 * @locale zh
 * @brief 识别到的人脸数量。
 */
/**
 * @locale en
 * @brief The number of detected faces.
 */
@property (assign, nonatomic) int faceCount;

/**
 * @locale zh
 * @brief 特征识别信息。数组的长度和检测到的人脸数量一致。参看 ByteRTCExpressionDetectInfo{@link #ByteRTCExpressionDetectInfo}。
 */
/**
 * @locale en
 * @brief Expression detection information. The length of the array is the same as the number of detected faces. See ByteRTCExpressionDetectInfo{@link #ByteRTCExpressionDetectInfo}.
 */
@property (nonatomic, copy) NSArray<ByteRTCExpressionDetectInfo *> * _Nonnull detectInfo;

@end

/**
 * @locale zh
 * @type keytype
 * @brief 矩形区域，用于指定屏幕区域。
 */
/**
 * @locale en
 * @type keytype
 * @brief  A rectangle that you can move around and re-size to share just the portion of the screen defined by that rectangle.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRectangle : NSObject
/**
 * @locale zh
 * @brief 矩形区域左上角的 x 坐标。
 */
/**
 * @locale en
 * @brief The upper-left X coordinates of the rectangular.
 */
@property(assign, nonatomic) int x;
/**
 * @locale zh
 * @brief 矩形区域左上角的 y 坐标。
 */
/**
 * @locale en
 * @brief The upper-left Y coordinates of the rectangular.
 */
@property(assign, nonatomic) int y;
/**
 * @locale zh
 * @brief 矩形宽度，单位：px。
 */
/**
 * @locale en
 * @brief Width(in px).
 */
@property(assign, nonatomic) int width;
/**
 * @locale zh
 * @brief 矩形高度，单位：px。
 */
/**
 * @locale en
 * @brief Height(in px).
 */
@property(assign, nonatomic) int height;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 人脸检测结果
 */
/**
 * @locale en
 * @type keytype
 * @brief Face Detection Result
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFaceDetectionResult : NSObject
/**
 * @locale zh
 * @brief 人脸检测结果 <br>
 *        + 0：检测成功 <br>
 *        + !0：检测失败。详见[错误码](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @brief Face Detection Result <br>
 *        + 0: Success <br>
 *        + !0: Failure. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 */
@property(assign, nonatomic) int detectResult;
/**
 * @locale zh
 * @brief 原始图片宽度(px)
 */
/**
 * @locale en
 * @brief Width of the original image (px)
 */
@property(assign, nonatomic) int imageWidth;
/**
 * @locale zh
 * @brief 原始图片高度(px)
 */
/**
 * @locale en
 * @brief Height of the original image (px)
 */
@property(assign, nonatomic) int imageHeight;
/**
 * @locale zh
 * @brief 识别到人脸的矩形框。数组的长度和检测到的人脸数量一致。参看 ByteRTCRectangle{@link #ByteRTCRectangle}。
 */
/**
 * @locale en
 * @brief The face recognition rectangles. The length of the array is the same as the number of detected faces. See ByteRTCRectangle{@link #ByteRTCRectangle}.
 */
@property(nonatomic, copy) NSArray<ByteRTCRectangle *> * _Nullable faces;
/**
 * @locale zh
 * @brief 进行人脸识别的视频帧的时间戳。
 */
/**
 * @locale en
 * @brief The time stamp of the video frame using face detection.
 */
@property(assign, nonatomic) CMTime frameTimestamp;

@end
/**
 * @locale zh
 * @type keytype
 * @brief 视频帧渲染设置
 */
/**
 * @locale en
 * @type keytype
 * @brief Video rendering mode
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCanvas : NSObject
/**
 * @locale zh
 * @brief 本地视图句柄
 */
/**
 * @locale en
 * @brief Local view handle
 */
@property(strong, nonatomic) ByteRTCView* _Nullable view;
/**
 * @locale zh
 * @brief 渲染模式，参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}
 */
/**
 * @locale en
 * @brief See ByteRTCRenderMode{@link #ByteRTCRenderMode}
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/**
 * @locale zh
 * @brief 用于填充画布空白部分的背景颜色。取值范围是 `[0x00000000, 0xFFFFFFFF]`,格式为 BGR。默认值是 `0x00000000`。其中，透明度设置无效。
 */
/**
 * @locale en
 * @brief Set the background color of the canvas which is not filled with video frame. The range is `[0x00000000, 0xFFFFFFFF]`. The default is `0x00000000`. The Alpha index is ignored.
 */
@property(assign, nonatomic) NSInteger backgroundColor;
/**
 * @locale zh
 * @brief 视频帧旋转角度。参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}。默认为 0 度，即不做旋转处理。<br>
 *        该设置仅对远端视频有效，对本地视频设置不生效。
 */
/**
 * @locale en
 * @brief Video frame rotation angle. See ByteRTCVideoRotation{@link #ByteRTCVideoRotation}. The default value is 0, which means no rotation is applied.<br>
 *        This parameter only applies to remote video and does not affect local video settings.
 */
@property(assign, nonatomic) ByteRTCVideoRotation renderRotation;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 远端视频帧渲染设置
 */
/**
 * @locale en
 * @type keytype
 * @brief Remote video rendering configuration.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoRenderConfig : NSObject
/**
 * @locale zh
 * @brief 渲染模式，参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}
 */
/**
 * @locale en
 * @brief See ByteRTCRenderMode{@link #ByteRTCRenderMode}
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/**
 * @locale zh
 * @brief 用于填充画布空白部分的背景颜色。取值范围是 `[0x00000000, 0xFFFFFFFF]`,格式为 BGR。默认值是 `0x00000000`。其中，透明度设置无效。
 */
/**
 * @locale en
 * @brief Set the background color of the canvas which is not filled with video frame. The range is `[0x00000000, 0xFFFFFFFF]`. The default is `0x00000000`. The Alpha index is ignored.
 */
@property(assign, nonatomic) NSInteger backgroundColor;
/**
 * @locale zh
 * @brief 视频帧旋转角度。参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}。默认为 0 度，即不做旋转处理。
 */
/**
 * @locale en
 * @brief Video frame rotation angle. See ByteRTCVideoRotation{@link #ByteRTCVideoRotation}. The default value is 0, which means no rotation is applied.
 */
@property(assign, nonatomic) ByteRTCVideoRotation renderRotation;
@end


/**
 * @locale zh
 * @type keytype
 * @brief 视频帧附加的数据,视频解码后获得的附加数据
 */
/**
 * @locale en
 * @type keytype
 * @brief Attached data obtained after video decoding
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFrameExtendedData : NSObject
/**
 * @locale zh
 * @brief 数据类型，详见 ByteRTCDataFrameType{@link #ByteRTCDataFrameType}。
 */
/**
 * @locale en
 * @brief Data type. See ByteRTCDataFrameType{@link #ByteRTCDataFrameType}.
 */
@property(assign, nonatomic) ByteRTCDataFrameType frameType;
/**
 * @locale zh
 * @brief 附加数据
 */
/**
 * @locale en
 * @brief Attached data
 */
@property(strong, nonatomic) NSData * _Nullable extendedData;
/**
 * @locale zh
 * @brief 附加数据长度
 */
/**
 * @locale en
 * @brief Data length
 */
@property(assign, nonatomic) NSInteger extendedDataLen;
@end

NS_ASSUME_NONNULL_BEGIN

/**
 * @locale zh
 * @type keytype
 * @brief 视频流参数
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video stream parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoSolution: NSObject
/**
 * @locale zh
 * @brief 视频分辨率
 */
/**
 * @locale en
 * @brief Video resolution
 */
@property(nonatomic, assign) CGSize videoSize;
/**
 * @locale zh
 * @brief 视频预设帧率
 */
/**
 * @locale en
 * @brief Video frame rate
 */
@property(nonatomic, assign) NSInteger frameRate;
/**
 * @locale zh
 * @brief 最高编码码率（千比特每秒）。建议使用 `-1`，SDK 会自动根据分辨率和帧率适配合适的码率。
 */
/**
 * @locale en
 * @brief Maximum bitrate (kbps). You can use `-1` to use the self-adaptive bitrate based on the resolution and framerate.
 */
@property(nonatomic, assign) NSInteger maxKbps;
/**
 * @locale zh
 * @brief 最低编码码率（千比特每秒）
 */
/**
 * @locale en
 * @brief Minimum bitrate (kbps).
 */
@property(nonatomic, assign) NSInteger minKbps;
/**
 * @locale zh
 * @brief 视频编码质量策略，参见 ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
 */
/**
 * @locale en
 * @brief Encoder preference. See ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
 */
@property(nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 视频采集参数
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video acquisition parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCaptureConfig: NSObject
/**
 * @locale zh
 * @brief 视频采集模式，参看 ByteRTCVideoCapturePreference{@link #ByteRTCVideoCapturePreference}
 */
/**
 * @locale en
 * @brief Video capture preference. See ByteRTCVideoCapturePreference{@link #ByteRTCVideoCapturePreference}
 */
@property(nonatomic, assign) ByteRTCVideoCapturePreference preference;

/**
 * @locale zh
 * @brief 视频采集分辨率
 */
/**
 * @locale en
 * @brief Video capture resolution
 */
@property(nonatomic, assign) CGSize videoSize;
/**
 * @locale zh
 * @brief 视频采集帧率，单位：fps。
 */
/**
 * @locale en
 * @brief Video capture frame rate in fps.
 */
@property(nonatomic, assign) NSInteger frameRate;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 流属性。
 */
/**
 * @locale en
 * @type keytype
 * @brief Flow property.
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCStream <NSObject>
/**
 * @locale zh
 * @brief 发布此流的用户 ID 。  
 */
/**
 * @locale en
 * @brief The user ID that published this stream. 
 */
@property(nonatomic, copy, readonly) NSString * userId;
/**
 * @locale zh
 * @brief 此流是否为共享屏幕流。  
 */
/**
 * @locale en
 * @brief Whether this stream is a shared screen stream.   
 */
@property(nonatomic, assign, readonly) BOOL isScreen;
/**
 * @locale zh
 * @brief 此流是否包括视频流。  
 */
/**
 * @locale en
 * @brief Whether this stream includes a video stream.   
 */
@property(nonatomic, assign, readonly) BOOL hasVideo;
/**
 * @locale zh
 * @brief 流是否包括音频流。  
 */
/**
 * @locale en
 * @brief Whether the stream includes an audio stream.   
 */
@property(nonatomic, assign, readonly) BOOL hasAudio;
/**
 * @locale zh
 * @brief 视频流的分辨率信息。  <br>
 *         当远端用户调用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} 方法发布多个配置的视频流时，此处会包含该用户发布的所有视频流的属性信息。  <br>
 *         参看 ByteRTCVideoSolution{@link #ByteRTCVideoSolution}。  
 */
/**
 * @locale en
 * @brief Resolution information of the video stream.   <br>
 *         When a remote user calls setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} method to publish multiple configured video streams, this will contain attribute information for all video streams published by the user. <br>
 *          See ByteRTCVideoSolution{@link #ByteRTCVideoSolution}. 
 */
@property(nonatomic, copy, readonly) NSArray<ByteRTCVideoSolution *> * videoStreamDescriptions;
/**
 * @locale zh
 * @brief 视频流最大分辨率，在开启多分辨率发布订阅时，回调发布端能支持的最大发布分辨率。
 */
/**
 * @locale en
 * @brief The maximum resolution of the video stream, the maximum publish resolution that can be supported by the callback publisher when multi-resolution publish subscription is enabled.
 */
@property(nonatomic, retain, readonly) ByteRTCVideoSolution *maxVideoStreamDescription;


@property(nonatomic, assign) ByteRTCStreamIndex index;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 流信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream Information
 */
@interface ByteRTCStreamEx : NSObject <ByteRTCStream>
/**
 * @locale zh
 * @brief 用户ID
 */
/**
 * @locale en
 * @brief User ID
 */
@property(nonatomic, copy, nullable) NSString *userId;
/**
 * @locale zh
 * @brief 流是否为共享屏幕流。
 */
/**
 * @locale en
 * @brief Whether the stream is a shared screen stream.
 */
@property(nonatomic, assign) BOOL isScreen;
/**
 * @locale zh
 * @brief 该路流中是否包含视频
 */
/**
 * @locale en
 * @brief Does the path contain video
 */
@property(nonatomic, assign) BOOL hasVideo;
/**
 * @locale zh
 * @brief 该路流中是否包含音频
 */
/**
 * @locale en
 * @brief Does this stream contain audio?
 */
@property(nonatomic, assign) BOOL hasAudio;
/**
 * @locale zh
 * @brief 视频流的分辨率信息，详见 ByteRTCVideoSolution{@link #ByteRTCVideoSolution} 类。<br>
 *         用户可以通过调用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中所有分辨率的相关信息。
 */
/**
 * @locale en
 * @brief For resolution information of the video stream. See ByteRTCVideoSolution{@link #ByteRTCVideoSolution} class.<br>
 *         Users can publish multiple different video resolutions in a stream by calling the setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} method. This parameter is information about all resolutions in the stream.
 */
@property(nonatomic, copy, nullable) NSArray<ByteRTCVideoSolution *> *videoStreamDescriptions;
/**
 * @locale zh
 * @brief 视频流最大分辨率，在开启多分辨率发布订阅时，回调发布端能支持的最大发布分辨率。
 */
/**
 * @locale en
 * @brief The maximum resolution of the video stream, the maximum publish resolution that can be supported by the callback publisher when multi-resolution publish subscription is enabled.
 */
@property(nonatomic, retain, nullable) ByteRTCVideoSolution *maxVideoStreamDescription;

@property(nonatomic, assign) ByteRTCStreamIndex index;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 订阅流的参数配置。用户手动订阅一路音视频流所使用的订阅配置参数。  <br>
 *         用户关闭自动订阅功能，使用手动订阅模式时，通过调用 `subscribeStream` 方法订阅音视频流，调用时传入的参数即为此数据类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief  The parameter configuration of the subscription flow. Subscription configuration parameters user manually subscribes to all the audio & video streams used.   <br>
 *         When the user turns off the automatic subscription function, when using the manual subscription mode, he subscribes to the audio & video stream by calling the `subscribeStream`, and the incoming parameters are for this data type. 
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeConfig: NSObject
/**
 * @locale zh
 * @brief 是否是屏幕流。  <br>
 *         用户通过设置此参数，订阅该远端用户发布的屏幕共享流或非屏幕共享流。 YES 为订阅屏幕共享流，NO 为订阅非屏幕共享流，默认值为 YES 。  
 */
/**
 * @locale en
 * @brief Whether it is a screen stream.   <br>
 *         By setting this parameter, the user subscribes to the screen share stream or non-screen share stream published by the remote user. YES is a subscription screen share flow, NO is a subscription non-screen share flow, the default value is YES. 
 */
@property(nonatomic, assign) BOOL isScreen;
/**
 * @locale zh
 * @brief 是否订阅视频。  <br>
 *         用户通过设置此参数，选择是否订阅远端流中的视频。 YES 为订阅视频，NO 为不订阅视频，默认值为 YES 。  
 */
/**
 * @locale en
 * @brief Whether to subscribe to videos.   <br>
 *         The user selects whether to subscribe to videos in the remote stream by setting this parameter. YES is a subscription video, NO is a non-subscription video, the default value is YES. 
 */
@property(nonatomic, assign) BOOL subscribeVideo;
/**
 * @locale zh
 * @brief 是否订阅音频。  <br>
 *         用户通过设置此参数，选择是否订阅远端流中的音频。YES 为订阅音频，NO 为不订阅音频，默认值为 YES 。  
 */
/**
 * @locale en
 * @brief Whether to subscribe to audio.   <br>
 *         The user selects whether to subscribe to audio in the remote stream by setting this parameter. YES is subscribed audio, NO is not subscribed audio, the default value is YES. 
 */
@property(nonatomic, assign) BOOL subscribeAudio;
/**
 * @locale zh
 * @brief 订阅的视频流分辨率下标。  <br>
 *         用户可以通过调用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} 方法发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  
 */
/**
 * @locale en
 * @brief Subscribed video stream resolution subscript.   <br>
 *         Users can publish multiple videos streams of different resolutions by calling the setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} method. Therefore, when subscribing to a stream, you need to specify the specific resolution of the subscription. This parameter is used to specify the subscript of the resolution to be subscribed to, and the default value is 0. 
 */
@property(nonatomic, assign) NSInteger videoIndex;
/**
 * @locale zh
 * @brief 订阅的视频流时域分层，默认值为 0。  
 */
/**
 * @locale en
 * @brief Time domain hierarchy of the subscribed video stream, default value is 0.  
 */
@property(nonatomic, assign) NSInteger svcLayer;
/**
 * @locale zh
 * @brief 订阅的宽度信息，单位：px，默认值为 0。 
 */
/**
 * @locale en
 * @brief The width in px of the subscription, the default value is 0. 
 */
@property(nonatomic, assign) NSInteger width;
/**
 * @locale zh
 * @brief 订阅的高度信息，单位：px， 默认值为0。
 */
/**
 * @locale en
 * @brief The height in px of the subscription, the default value is 0.
 */
@property(nonatomic, assign) NSInteger height;
/**
 * @hidden for internal use only
 */
@property(nonatomic, assign) NSInteger subVideoIndex;
/**
 * @locale zh
 * @brief 期望订阅的最高帧率，单位：fps，默认值为 0，设为大于 0 的值时开始生效。  <br>
 *        当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
 *        仅码流支持 SVC 分级编码特性时方可生效。
 */
/**
 * @locale en
 * @brief Expected maximum frame rate of the subscribed stream in px. The default value is 0, values greater than 10 are valid.  <br>
 *        If the frame rate of the stream published is lower than the value you set, or if your subscribed stream falls back under limited network conditions, the frame rate you set will drop accordingly.  <br>
 *        Only valid if the stream is coded with SVC technique.
 */
@property (nonatomic, assign) NSInteger framerate;


@end

NS_ASSUME_NONNULL_END

/**
 * @locale zh
 * @type keytype
 * @brief 待 SDK 编码的视频数据
 */
/**
 * @locale en
 * @type keytype
 * @brief Video data to be encoded by SDK
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrame : NSObject
/**
 * @locale zh
 * @brief 视频帧格式，参考 ByteRTCVideoPixelFormat {@link #ByteRTCVideoPixelFormat}
 */
/**
 * @locale en
 * @brief Video frame format, see ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}
 */
@property(assign, nonatomic) int format;
/**
 * @locale zh
 * @brief 获取视频内容类型，参看 ByteRTCVideoContentType{@link #ByteRTCVideoContentType}
 */
/**
 * @locale en
 * @brief Gets video content type, see ByteRTCVideoContentType{@link #ByteRTCVideoContentType}.
 */
@property(assign, nonatomic) ByteRTCVideoContentType contentType;
/**
 * @locale zh
 * @brief 当前帧的时间戳信息
 */
/**
 * @locale en
 * @brief The timestamp information of the current frame
 */
@property(assign, nonatomic) CMTime time;
/**
 * @locale zh
 * @deprecated since 3.45 and will be deleted in 3.51, use strideInPixels instead.
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use strideInPixels instead.
 */
@property(assign, nonatomic) int stride DEPRECATED_MSG_ATTRIBUTE("use strideInPixels instead");
/**
 * @locale zh
 * @brief 每一行像素占用的字节数
 */
/**
 * @locale en
 * @brief Number of bytes per pixel line
 */
@property(assign, nonatomic) int strideInPixels;
/**
 * @locale zh
 * @brief 视频帧宽度
 */
/**
 * @locale en
 * @brief Video frame width
 */
@property(assign, nonatomic) int width;
/**
 * @locale zh
 * @brief 视频帧高度
 */
/**
 * @locale en
 * @brief Video frame height
 */
@property(assign, nonatomic) int height;
/**
 * @locale zh
 * @brief CVPixelBufferRef 类型的数据，当 format 为 kPixelFormatCVPixelBuffer 时有效
 */
/**
 * @locale en
 * @brief Data of CVPixelBufferRef type, valid when format is kPixelFormatCVPixelBuffer
 */
@property(assign, nonatomic) CVPixelBufferRef _Nullable textureBuf;
/**
 * @locale zh
 * @brief 视频帧内存块首地址
 */
/**
 * @locale en
 * @brief The first address in video frame memory
 */
@property(strong, nonatomic) NSData * _Nullable dataBuf;
/**
 * @locale zh
 * @brief 视频帧旋转角度：0, 90, 180, 270
 */
/**
 * @locale en
 * @brief Video frame rotation angle, the value must be 0,  90, 180, or 270
 */
@property(assign, nonatomic) ByteRTCVideoRotation rotation;
/**
 * @locale zh
 * @hidden for internal use only
 * @brief 视频镜像信息
 */
/**
 * @locale en
 * @hidden for internal use only
 * @brief Video mirroring information
 */
@property(assign, nonatomic) int flip;
/**
 * @locale zh
 * @brief 颜色空间
 */
/**
 * @locale en
 * @brief Video frame colorspace
 */
@property(assign, nonatomic) ByteRTCColorSpace colorSpace;
/**
 * @locale zh
 * @brief 视频帧的摄像头信息，参考 ByteRTCCameraID{@link #ByteRTCCameraID}
 */
/**
 * @locale en
 * @brief the cameraId of the video frame, see ByteRTCCameraID{@link #ByteRTCCameraID}
 */
@property(assign, nonatomic) ByteRTCCameraID cameraId;
/**
 * @locale zh
 * @brief 视频帧附加的sei数据
 */
/**
 * @locale en
 * @brief Data attached to the video frame
 */
@property(strong, nonatomic) NSData * _Nullable extendedData;

/**
 * @locale zh
 * @brief 视频帧附加的roi数据
 */
@property(strong, nonatomic) NSData * _Nonnull supplementaryInfo;

/**
 * @locale zh
 * @brief 视频帧颜色 plane 数量; 当 textureBuf 有值时, 该值无意义。<br>
 *        yuv 数据存储格式分为打包（packed）存储格式和平面（planar）存储格式，planar 格式中 Y、U、V 分平面存储，packed 格式中 Y、U、V 交叉存储
 */
/**
 * @locale en
 * @brief Video frame color plane number.<br>
 *        YUV formats are categorized into planar format and packed format.  <br>
 *        In a planar format, the Y, U, and V components are stored separately as three planes, while in a packed format, the Y, U, and V components are stored in a single array. <br>
 *        When textureBuf has a value, the value is meaningless
 */
@property (assign, nonatomic) int numberOfPlanes;

/**
 * @locale zh
 * @brief 获取 plane 数据指针, 数组长度与 numberOfPlanes 一致, 元素类型为 NSData*; 当 textureBuf 有值时, 该值无意义
 * @param plane_index plane 数据索引
 */
/**
 * @locale en
 * @brief Gets plane data pointer, the length of array equals numberOfPlanes, and the type of element is NSData*
 * @param plane_index Plane data index; When textureBuf has a value, the value is meaningless
 */
@property (strong, nonatomic) NSArray * _Nullable planeDatas;

/**
 * @locale zh
 * @brief 获取 plane 中数据行的长度,  数组长度与 numberOfPlanes 一致, 元素类型为 NSNumber*; 当 textureBuf 有值时, 该值无意义
 * @param plane_index plane 数据索引
 */
/**
 * @locale en
 * @brief Gets the length of the data line in the plane
 * @param plane_index Plane data index, the length of array equals numberOfPlanes, and the type of element is NSNumber*; When textureBuf has a value, the value is meaningless
 */
@property (strong, nonatomic) NSArray * _Nullable planeStrides;

@end

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Information about video frames
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCEncodedVideoFrame : NSObject
/**
 * @locale zh
 * @brief 视频编码类型。参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
/**
 * @locale en
 * @brief Video encoding type. See ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
@property(assign, nonatomic) ByteRTCVideoCodecType codecType;
/**
 * @locale zh
 * @brief 视频帧类型。参看 ByteRTCVideoPictureType{@link #ByteRTCVideoPictureType}
 */
/**
 * @locale en
 * @brief Video compression picture type. See ByteRTCVideoPictureType{@link #ByteRTCVideoPictureType}
 */
@property(assign, nonatomic) ByteRTCVideoPictureType pictureType;
/**
 * @locale zh
 * @brief 视频采集时间戳，单位：微秒
 */
/**
 * @locale en
 * @brief Video capture timestamp in microseconds
 */
@property(assign, nonatomic) SInt64 timestampUs;
/**
 * @locale zh
 * @brief 视频编码时间戳，单位：微秒
 */
/**
 * @locale en
 * @brief Video encoding timestamp in microseconds
 */
@property(assign, nonatomic) SInt64 timestampDtsUs;
/**
 * @locale zh
 * @brief 视频帧宽，单位：px
 */
/**
 * @locale en
 * @brief Video frame width in px
 */
@property(assign, nonatomic) int width;
/**
 * @locale zh
 * @brief 视频帧高，单位：px
 */
/**
 * @locale en
 * @brief Video frame height in px
 */
@property(assign, nonatomic) int height;
/**
 * @locale zh
 * @brief 视频帧旋转角度。参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 */
/**
 * @locale en
 * @brief Video frame rotation angle. See ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 */
@property(nonatomic, assign) ByteRTCVideoRotation rotation;
/**
 * @locale zh
 * @brief 视频帧数据指针地址
 */
/**
 * @locale en
 * @brief The pointer to the video frame
 */
@property(strong, nonatomic) NSData * _Nonnull data;

@end
/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig{@link #ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig} instead.
 * @type keytype
 * @brief 图片合流相关参数
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig{@link #ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig} instead.
 * @type keytype
 * @brief Image parameters for stream mixing
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscoderLayoutRegionDataParam : NSObject
/**
 * @locale zh
 * @brief 原始图片的宽度，单位为 px。
 */
/**
 * @locale en
 * @brief Width of the original image in px.
 */
@property (assign, nonatomic) NSInteger imageWidth;
/**
 * @locale zh
 * @brief 原始图片的高度，单位为 px。
 */
/**
 * @locale en
 * @brief Height of the original image in px.
 */
@property (assign, nonatomic) NSInteger imageHeight;
@end

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamLayoutRegionConfig{@link #ByteRTCMixedStreamLayoutRegionConfig} instead.
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息。<br>
 *        开启转推直播功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 * @note  
 *         + 视频流对应区域左上角的实际坐标是通过画面尺寸和归一化比例相乘，并四舍五入取整得到的。假如：Canvas.Width = 1920, Region.LocationX = 0.33，那么该画布左上角的横坐标为 634（1920×0.33=633.6，四舍五入取整）。<br>
 *         + 视频流对应区域宽度和高度的像素值是通过画面尺寸和归一化比例相乘，四舍五入取整，并向上转换为偶数得到的。假如：Canvas.Width = 1920, Region.WidthProportion = 0.21，那么该画布横向宽度为 404px（1920x0.21=403.2，四舍五入取整后，再向上转换为偶数）。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamLayoutRegionConfig{@link #ByteRTCMixedStreamLayoutRegionConfig} instead.
 * @type keytype
 * @brief Layout information for one of the video streams or image to be mixed.<br>
 *        After starting to push streams to CDN and mixing multiple video streams, you can set the layout information for each of them.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingRegion : NSObject
/**
 * @locale zh
 * @brief 视频流发布用户的用户 ID 。必填。
 */
/**
 * @locale en
 * @brief The user ID of the user who publishes the video stream. Required.
 */
@property(copy, nonatomic) NSString * _Nonnull uid;
/**
 * @locale zh
 * @brief 图片或视频流所在房间的房间 ID。必填。<br>
 *        如果此图片或视频流是通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
 */
/**
 * @locale en
 * @brief The room ID of the media stream. Required.<br>
 *        If the media stream is the stream forwarded by startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}, you must set the roomID to the room ID of the target room. 
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/**
 * @locale zh
 * @brief 视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
 */
/**
 * @locale en
 * @brief The normalized horizontal coordinate value of the top left end vertex of the user's view, ranging within [0.0, 1.0). The default value is 0.0.
 */
@property(assign, nonatomic) CGFloat x;
/**
 * @locale zh
 * @brief 视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。默认值为 0.0。
 */
/**
 * @locale en
 * @brief The normalized vertical coordinate value of the top left end vertex of the user's view, ranging within [0.0, 1.0). The default value is 0.0.
 */
@property(assign, nonatomic) CGFloat y;
/**
 * @locale zh
 * @brief 视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
 */
/**
 * @locale en
 * @brief The normalized width of the user's view, ranging within [0.0, 1.0]. The default value is 1.0.
 */
@property(assign, nonatomic) CGFloat width;
/**
 * @locale zh
 * @brief 视频流对应区域高度相对整体画面的归一化比例，取值的范围为 [0.0, 1.0]。默认值为 1.0。
 */
/**
 * @locale en
 * @brief The normalized height of the user's view, ranging within [0.0, 1.0]. The default value is 1.0.
 */
@property(assign, nonatomic) CGFloat height;
/**
 * @locale zh
 * @brief 用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。
 */
/**
 * @locale en
 * @brief The layer on which the video is rendered. The range is [0, 100]. 0 for the bottom layer, and 100 for the top layer. The default value is 0.
 */
@property(assign, nonatomic) NSInteger zOrder;
/**
 * @locale zh
 *  @brief 是否为本地用户
 */
/**
 * @locale en
 *  @brief Whether the source user of the stream is a local user.
 */
 @property(assign, nonatomic) BOOL localUser;
/**
 * @locale zh
 *  @brief （仅服务端合流支持合屏幕流）是否为屏幕流，默认为 NO
 */
/**
 * @locale en
 *  @brief (Only server-side stream mixing can set this parameter to YES.) Whether the stream comes from screen sharing, the default value is No.
 */
 @property(assign, nonatomic) BOOL screenStream;
/**
 * @locale zh
 * @brief （仅服务端合流支持设置）透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。
 */
/**
 * @locale en
 * @brief (Only server-side stream mixing can set this parameter.) The opacity in range of (0.0, 1.0]. The lower value, the more transparent. The default value is 1.0.
 */
@property(assign, nonatomic) CGFloat alpha;
/**
 * @locale zh
 * @brief （仅服务端合流支持设置）圆角半径相对画布宽度的比例。默认值为 `0.0`。<br>
 *         做范围判定时，首先根据画布的宽高，将 `width`，`height`，和 `cornerRadius` 分别转换为像素值：`width_px`，`height_px`，和 `cornerRadius_px`。然后判定是否满足 `cornerRadius_px < min(width_px/2, height_px/2)`：若满足，则设置成功；若不满足，则将 `cornerRadius_px` 设定为 `min(width_px/2, height_px/2)`，然后将 `cornerRadius` 设定为 `cornerRadius_px` 相对画布宽度的比例值。
 */
/**
 * @locale en
 * @brief (Only server-side stream mixing can set this parameter.) The proportion of the radius to the width of the canvas. The default value is 0.0.<br>
 *        After you set the value, `width_px`, `height_px`, and `cornerRadius_px` are calculated based on `width`, `height`, `cornerRadius`, and the width of the canvas. If `cornerRadius_px < min(width_px/2, height_px/2)` is met, the value of `cornerRadius` is set valid; if not, `cornerRadius_px` is set to `min(width_px/2, height_px/2)`, and `cornerRadius` is set to the proportion of `cornerRadius_px` to the width of the canvas.
 */
@property(assign, nonatomic) CGFloat cornerRadius;
/**
 * @locale zh
 * @brief （仅服务端合流支持设置）合流内容控制。默认值为 `ByteRTCTranscoderContentControlTypeHasAudioAndVideo`，参看 ByteRTCTranscoderContentControlType{@link #ByteRTCTranscoderContentControlType} 。
 */
/**
 * @locale en
 * @brief (Only server-side stream mixing can set this parameter.) The stream mixing content type. The default value is `ByteRTCTranscoderContentControlTypeHasAudioAndVideo`. See ByteRTCTranscoderContentControlType{@link #ByteRTCTranscoderContentControlType}.
 */
@property (assign, nonatomic) ByteRTCTranscoderContentControlType contentControl;
/**
 * @locale zh
 * @brief 图片或视频流的缩放模式，参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}。默认值为 1。
 */
/**
 * @locale en
 * @brief The render mode. See ByteRTCRenderMode{@link #ByteRTCRenderMode}. The default value is 1.
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/**
 * @locale zh
 * @brief 合流布局区域类型。参看 ByteRTCTranscoderLayoutRegionType{@link #ByteRTCTranscoderLayoutRegionType}。
 */
/**
 * @locale en
 * @brief Stream mixing region type. See ByteRTCTranscoderLayoutRegionType{@link #ByteRTCTranscoderLayoutRegionType}.
 */
@property (assign, nonatomic) ByteRTCTranscoderLayoutRegionType type;
/**
 * @locale zh
 * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
 */
/**
 * @locale en
 * @brief   The RGBA data of the mixing image. Put in null when mixing video streams.
 */
@property (strong, nonatomic) NSData * _Nullable data;
/**
 * @locale zh
 * @type keytype
 * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 ByteRTCTranscoderLayoutRegionDataParam{@link #ByteRTCTranscoderLayoutRegionDataParam}。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Image parameters for stream mixing. See ByteRTCTranscoderLayoutRegionDataParam{@link #ByteRTCTranscoderLayoutRegionDataParam}. Put in null when mixing video streams.
 */
@property (strong, nonatomic) ByteRTCTranscoderLayoutRegionDataParam * _Nullable dataParam;
/**
 * @locale zh
 * @type keytype
 * @brief 空间位置。参看 ByteRTCPosition{@link #ByteRTCPosition}。
 */
/**
 * @locale en
 * @type keytype
 * @brief spatial position. See ByteRTCPosition{@link #ByteRTCPosition}.
 */
@property (strong, nonatomic) ByteRTCPosition * _Nullable spatialPosition;
/**
 * @locale zh
 * @brief 设置某用户是否应用空间音频效果：<br>
 *        + Yes：启用（默认值）<br>
 *        + No：禁用
 */ 
/**
 * @locale en
 * @brief Sets whether a user applies spatial audio effects:<br>
 *        + Yes: Yes (default setting)<br>
 *        + No: No
 */
@property(assign, nonatomic) BOOL applySpatialAudio;

@end

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamLayoutConfig{@link #ByteRTCMixedStreamLayoutConfig} instead.
 * @type keytype
 * @brief 视频流合流整体布局信息。<br>
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamLayoutConfig{@link #ByteRTCMixedStreamLayoutConfig} instead.
 * @type keytype
 * @brief The overall video layout of the mixed stream.<br>
 *        After starting to push streams to CDN, you can set the layout of each video stream, the background information of the mixed stream, etc.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingLayout : NSObject
/**
 * @locale zh
 * @brief 合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。<br>
 *        值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @brief Background-color of the mixed stream in hexadecimal values such as #FFFFFF and #000000. The default value is #000000 (black).<br>
 *        With invalid or empty input, the configurations will be set as the default values.
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/**
 * @locale zh
 * @brief 用户布局信息列表。每条流的具体布局参看 ByteRTCVideoCompositingRegion{@link #ByteRTCVideoCompositingRegion}。<br>
 *        值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @brief List of user's video layout information. The specific layout of each stream is detailed in ByteRTCVideoCompositingRegion{@link #ByteRTCVideoCompositingRegion}.<br>
 *        With invalid or empty input, the configurations will be set as the default values.
 */
@property(copy, nonatomic) NSArray<ByteRTCVideoCompositingRegion *> * _Nonnull regions;
/**
 * @locale zh
 * @brief 透传的 App 数据，长度不超过 4KB。
 */
/**
 * @locale en
 * @brief Data passed through from the App, up to 4KB in length.
 */
@property(copy, nonatomic) NSString *_Nonnull appData;
@end

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamVideoConfig{@link #ByteRTCMixedStreamVideoConfig} instead.
 * @type keytype
 * @brief 视频转码配置参数。值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamVideoConfig{@link #ByteRTCMixedStreamVideoConfig} instead.
 * @type keytype
 * @brief Video transcoding configurations. With invalid or empty input, the configurations will be set as the default values.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingVideoConfig : NSObject
/**
 * @locale zh
 * @brief 视频编码格式，参看 ByteRTCTranscodingVideoCodec{@link #ByteRTCTranscodingVideoCodec}。默认值为 `0`。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The video codec. See ByteRTCTranscodingVideoCodec{@link #ByteRTCTranscodingVideoCodec}. The default value is `0`.<br>
 *        These parameters cannot be updated while pushing stream to the CDN.
 */
@property(assign, nonatomic) ByteRTCTranscodingVideoCodec codec;
/**
 * @locale zh
 * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。<br>
 *        设置值为非偶数时，自动向上取偶数。
 */
/**
 * @locale en
 * @brief The width (pixels) to be set. The range is [2, 1920], and must be an even number. The default value is 640 pixels.<br>
 *        If an odd number is set, the width will be adjusted to the next larger even number.
 */
@property(assign, nonatomic) NSInteger width;
/**
 * @locale zh
 * @brief 合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。<br>
 *        设置值为非偶数时，自动向上取偶数。
 */
/**
 * @locale en
 * @brief The height (pixels) to be set. The range is [2, 1920], and must be an even number. The default value is 360 pixels.<br>
 *        If an odd number is set, the height will be adjusted to the next larger even number.
 */
@property(assign, nonatomic) NSInteger height;
/**
 * @locale zh
 * @brief 合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。
 */
/**
 * @locale en
 * @brief The frame rate (FPS) in range of [1, 60]. The default value is 15 FPS.
 */
@property(assign, nonatomic) NSInteger fps;
/**
 * @locale zh
 * @brief 视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The time interval between I-frames (second) in range of [1, 5]. The default value is 2 seconds.<br>
 *        These parameters cannot be updated while pushing stream to the CDN.
 */
@property(assign, nonatomic) NSInteger gop;
/**
 * @locale zh
 * @brief 合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。
 */
/**
 * @locale en
 * @brief The bitrate (Kbps) in range of [1, 10000]. The default value is self-adaptive.
 */
@property(assign, nonatomic) NSInteger kBitRate;
/**
 * @locale zh
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @brief 是否使用低延时特性。
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @brief Whether to push streams with low latency.
 */
@property(assign, nonatomic) BOOL lowLatency;
/**
 * @locale zh
 * @brief 是否在合流中开启B帧，仅服务端合流支持.
 */
/**
 * @locale en
 * @brief Whether to push streams with B frame, only support by server mix.
 */
@property(assign, nonatomic) BOOL bFrame;
@end

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamAudioConfig{@link #ByteRTCMixedStreamAudioConfig} instead.
 * @type keytype
 * @brief 音频转码配置参数。值不合法或未设置时，自动使用默认值。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamAudioConfig{@link #ByteRTCMixedStreamAudioConfig} instead.
 * @type keytype
 * @brief Audio transcoding configurations. With invalid or empty input, the configurations will be set as the default values.<br>
 *        These parameters cannot be updated while pushing stream to the CDN.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingAudioConfig : NSObject
/**
 * @locale zh
 * @brief 音频编码格式。
 * @param codec 音频编码格式，参看 ByteRTCTranscodingAudioCodec{@link #ByteRTCTranscodingAudioCodec}。默认值为 `0`。
 */
/**
 * @locale en
 * @brief The audio codec.
 * @param codec The audio codec. See ByteRTCTranscodingAudioCodec{@link #ByteRTCTranscodingAudioCodec}. Defaults to `0`.
 */
@property(assign, nonatomic) ByteRTCTranscodingAudioCodec codec;
/**
 * @locale zh
 * @brief 音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。
 */
/**
 * @locale en
 * @brief The sample rate (Hz). Supported sample rates: 32,000 Hz, 44,100 Hz, 48,000 Hz. Defaults to 48,000 Hz.
 */
@property(assign, nonatomic) NSInteger sampleRate;
/**
 * @locale zh
 * @brief 音频声道数。可取 1（单声道）、2（双声道），默认值为 2。
 */
/**
 * @locale en
 * @brief The number of channels. Supported channels: 1 (single channel), 2 (dual channel).  Defaults to 2.
 */
@property(assign, nonatomic) NSInteger channels;
/**
 * @locale zh
 * @brief 音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。
 */
/**
 * @locale en
 * @brief The bitrate (Kbps) in range of [32, 192]. Defaults to 64 Kbps.
 */
@property(assign, nonatomic) NSInteger kBitRate;
/**
 * @locale zh
 * @brief AAC 编码规格，参看 ByteRTCAACProfile{@link #ByteRTCAACProfile}。默认值为 `0`。
 */
/**
 * @locale en
 * @brief AAC profile. See ByteRTCAACProfile{@link #ByteRTCAACProfile}. Defaults to `0`.
 */
@property(assign, nonatomic) ByteRTCAACProfile profile;
/**
 * @locale zh
 * @deprecated since 3.45 and will be deleted in 3.51.
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51.
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteRTCAACProfile) aacProfile;
@end

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamSpatialAudioConfig{@link #ByteRTCMixedStreamSpatialAudioConfig} instead.
 * @type keytype
 * @brief 推流 CDN 的空间音频参数。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamSpatialAudioConfig{@link #ByteRTCMixedStreamSpatialAudioConfig} instead.
 * @type keytype
 * @brief Spatial audio config when pushing to CDN.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingSpatialConfig : NSObject
/**
 * @locale zh
 * @brief 是否开启推流 CDN 时的空间音频效果。<br>
 *        当你启用此效果时，你需要设定推流中各个 ByteRTCTranscodingSpatialConfig{@link #ByteRTCTranscodingSpatialConfig} 的 `spatialPosition` 值，实现空间音频效果。
 */
/**
 * @locale en
 * @brief Whether to enable the spatial audio effect when pushing to CDN.<br>
 *        when you enable the feature, set the `spatialPosition` of each ByteRTCTranscodingSpatialConfig{@link #ByteRTCTranscodingSpatialConfig} for spatial audio effect.
 */
@property(assign, nonatomic) BOOL enableSpatialRender;
/**
 * @locale zh
 * @brief 听众的空间位置。参看 ByteRTCPosition{@link #ByteRTCPosition}。<br>
 *        听众指收听来自 CDN 的音频流的用户。
 */
/**
 * @locale en
 * @brief The spatial position of the audience. See ByteRTCPosition{@link #ByteRTCPosition}. <br>
 *        The audience is the users who receive the audio stream from CDN.
 */
@property (strong, nonatomic) ByteRTCPosition * _Nullable audienceSpatialPosition;
/**
 * @locale zh
 * @brief 听众的空间朝向。参看 ByteRTCHumanOrientation{@link #ByteRTCHumanOrientation}。<br>
 *        听众指收听来自 CDN 的音频流的用户。
 */
/**
 * @locale en
 * @brief The orientation of the audience. See ByteRTCHumanOrientation{@link #ByteRTCHumanOrientation}. <br>
 *        The audience is the users who receive the audio stream from CDN.
 */
@property(strong, nonatomic) ByteRTCHumanOrientation * _Nullable audienceSpatialOrientation;

@end
/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamClientMixConfig{@link #ByteRTCMixedStreamClientMixConfig} instead.
 * @type keytype
 * @brief 客户端合流参数。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamClientMixConfig{@link #ByteRTCMixedStreamClientMixConfig} instead.
 * @type keytype
 * @brief Configurations for mixing and pushing to CDN at client side.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingClientMixParam : NSObject
/**
 * @locale zh
 * @brief 是否使用原始视频帧。默认为 False。
 */
/**
 * @locale en
 * @brief Whether to use original video frames. False by default.
 */
@property(assign, nonatomic) BOOL clientMixUseOriginalFrame;
/**
 * @locale zh
 * @brief 客户端合流是否使用音频混音，默认为 true。
 */
/**
 * @locale en
 * @brief Whether to use audio mixing. True by default.
 */
@property(assign, nonatomic) BOOL clientMixUseAudioMixer;
/**
 * @locale zh
 * @brief 客户端合流回调视频格式，参看 ByteRTCClientMixVideoFormat{@link #ByteRTCClientMixVideoFormat}。
 */
/**
 * @locale en
 * @brief The video format to be set. See ByteRTCClientMixVideoFormat{@link #ByteRTCClientMixVideoFormat}.
 */
@property(assign, nonatomic) ByteRTCClientMixVideoFormat clientMixVideoFormat;
@end
/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamSyncControlConfig instead.
 * @hidden internal use only
 * @valid since 3.50
 * @type keytype
 * @brief 转推直播单通同步参数。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamSyncControlConfig instead.
 * @hidden internal use only
 * @valid since 3.50
 * @type keytype
 * @brief Parameters of simplex mode and synchronization when pushing to CDN.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingSyncControlParam : NSObject
/**
 * @locale zh
 * @brief 是否在转推直播时，启用单通模式。默认为 false，不启用。<br>
 *        启用单通模式时，RTC SDK 会对指定的多个用户的媒体流进行同步处理，再合流后推送到 CDN，但基准流所属用户不会播放来自其他用户的媒体流。你需要设定以下参数。<br>
 *        非单通模式时，RTC SDK 不会对媒体流进行同步处理，只是简单合流后推送到 CDN。以下参数设定无效。
 */
/**
 * @locale en
 * @brief Whether to enable simplex mode during pushing to CDN. False(duplex mode) by default.<br>
 *        When simplex mode is enabled, RTC SDK synchronizes and transcodes the media streams from the local user and several remote users, and pushing the mixed stream to CDN. `syncBaseUser` does not play the streams from the remote users. You must set the following parameters.<br>
 *        When duplex mode is enabled, RTC SDK transcodes the media streams from the local user and several remote users without synchronization, and pushing the mixed stream to CDN. The following parameters are not effective.
 */
@property(assign, nonatomic) BOOL syncStream;
/**
 * @locale zh
 * @brief 在进行同步处理时，基准流所属用户的 ID。默认为空。
 */
/**
 * @locale en
 * @brief User ID of the base stream during syncing. Null by default.
 */
@property(copy, nonatomic) NSString * _Nullable syncBaseUser;
/**
 * @locale zh
 * @brief 在进行同步处理时，缓存音视频流的最大长度。单位为毫秒。默认值为 0。<br>
 *        参与转推直播的这些媒体流延迟越高，应该将此值设置的越大。但此值越大，因缓存媒体流造成的内存占用也会更大。推荐值为 `2000`。
 */
/**
 * @locale en
 * @brief The max length of the cached stream in milliseconds. 0 by default.<br>
 *        Set the value based on the stall of the media streams. Higher the value, bigger the memory usage. The recommended value is `2000`.
 */
@property(assign, nonatomic) NSInteger syncQueueLengthMs;
/**
 * @locale zh
 * @brief 是否通过 RTC SDK 进行转推直播。默认为 True。<br>
 *        如果选择 `False`，你会通过 onCacheSyncVideo:withDataFrame:withUids:taskId:{@link #LiveTranscodingDelegate#onCacheSyncVideo:withDataFrame:withUids:taskId:} 收到同步的帧，你可以使用此视频帧，自行实现合流转推。
 */
/**
 * @locale en
 * @brief Whether to use RTC SDK to push to CDN. True by default.<br>
 *        If `False`, you can get the media frames by onCacheSyncVideo:withDataFrame:withUids:taskId:{@link #LiveTranscodingDelegate#onCacheSyncVideo:withDataFrame:withUids:taskId:} and manually push them to CDN.
 */
@property(assign, nonatomic) BOOL syncClientVideoNeedMix;
/**
 * @locale zh
 * @brief 是否只开启时间戳发送而不做对齐和媒体数据回调。默认为 False。<br>
 *        在单通合唱双人场景下，主唱应设置为 False，副唱应设置为 True。<br>
 *        在单通合唱多人场景下，主唱和所有副唱都应设置为 False。
 */
/**
 * @locale en
 * @brief Whether only send cache sync pts and not start sync and callback data. False by default.<br>
 *        In the simplex chorus scene of two people, the lead singer should set to False, and the sub-singer should set to True.<br>
 *        In the duplex chorus scene of two people, all the singers should set to False.
 */
@property(assign, nonatomic) BOOL syncOnlySendPts;
@end

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamConfig{@link #ByteRTCMixedStreamConfig} instead.
 * @type keytype
 * @brief 转推直播配置参数。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamConfig{@link #ByteRTCMixedStreamConfig} instead.
 * @type keytype
 * @brief Configurations to be set when pushing media streams to CDN.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLiveTranscoding : NSObject
/**
 * @locale zh
 * @brief 合流类型，详见 ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType} 数据类型。<br>
 * 本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief Stream mixing type. See ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType}.<br>
 * This parameter cannot be updated while pushing stream to the CDN.
 */
@property(assign, nonatomic) ByteRTCStreamMixingType expectedMixingType;
/**
 * @locale zh
 * @brief 视频流合流整体布局信息。<br>
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。详见 ByteRTCVideoCompositingLayout{@link #ByteRTCVideoCompositingLayout} 数据类型。
 */
/**
 * @locale en
 * @brief The overall video layout of the mixed stream.<br>
 *        After starting to push streams to CDN, you can set the layout of each video stream, the background information of the mixed stream, etc. See ByteRTCVideoCompositingLayout{@link #ByteRTCVideoCompositingLayout} for details.
 */
@property(strong, nonatomic) ByteRTCVideoCompositingLayout * _Nonnull layout;
/**
 * @locale zh
 * @brief 视频转码配置参数。详见 ByteRTCTranscodingVideoConfig{@link #ByteRTCTranscodingVideoConfig} 数据类型。
 */
/**
 * @locale en
 * @brief Video transcoding related configurations. See ByteRTCTranscodingVideoConfig{@link #ByteRTCTranscodingVideoConfig}.
 */
@property(strong, nonatomic) ByteRTCTranscodingVideoConfig * _Nonnull video;
/**
 * @locale zh
 * @brief 音频转码配置参数，参看 ByteRTCTranscodingAudioConfig{@link #ByteRTCTranscodingAudioConfig}。
 */
/**
 * @locale en
 * @brief Audio transcoding related configurations. See ByteRTCTranscodingAudioConfig{@link #ByteRTCTranscodingAudioConfig} for data types.
 */
@property(strong, nonatomic) ByteRTCTranscodingAudioConfig * _Nonnull audio;
/**
 * @locale zh
 * @brief 客户端合流配置。详见 ByteRTCTranscodingClientMixParam{@link #ByteRTCTranscodingClientMixParam} 。
 */
/**
 * @locale en
 * @brief client mix param. See ByteRTCTranscodingClientMixParam{@link #ByteRTCTranscodingClientMixParam} for detail.
 */
@property(strong, nonatomic) ByteRTCTranscodingClientMixParam * _Nullable clientMixParam;
/**
 * @locale zh
 * @hidden for internal use only
 * @brief 转推同步配置。详见 ByteRTCTranscodingSyncControlParam{@link #ByteRTCTranscodingSyncControlParam} 。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @brief client mix param. See ByteRTCTranscodingSyncControlParam{@link #ByteRTCTranscodingSyncControlParam} for detail.
 */
@property(strong, nonatomic) ByteRTCTranscodingSyncControlParam * _Nullable syncControlParam;
/**
 * @locale zh
 * @hidden(macOS)
 * @brief 转推 CDN 空间音频配置。详见 ByteRTCTranscodingSpatialConfig{@link #ByteRTCTranscodingSpatialConfig} 。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @brief The spatial audio config when pushing to CDN. See ByteRTCTranscodingSpatialConfig{@link #ByteRTCTranscodingSpatialConfig} for detail.
 */
@property(strong, nonatomic) ByteRTCTranscodingSpatialConfig * _Nonnull spatialConfig;

/**
 * @locale zh
 * @hidden for internal use only
 * @brief 动态扩展自定义参数。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @brief Custom parameter
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/**
 * @locale zh
 * @hidden for internal use only
 * @brief 业务透传鉴权信息
 */
/**
 * @locale en
 * @hidden for internal use only
 * @brief Authentication information passed through from the App
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable authInfo;
/**
 * @locale zh
 * @brief 推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The URL for live transcoding. Only supports live transcoding via RTMP. The URL should match the regular expression `/^rtmps?:\/\//`.<br>
 *        This parameter cannot be updated while pushing stream to the CDN.
 */
@property(copy, nonatomic) NSString * _Nullable url;
/**
 * @locale zh
 * @brief 推流房间 ID。`roomId` 和 `userId` 长度相加不得超过 126 字节。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The room ID for live transcoding. The sum length of `roomId` and `userId` should not exceed 126 bytes.<br>
 *        This parameter cannot be updated while pushing stream to the CDN.
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/**
 * @locale zh
 * @brief 推流用户 ID。`roomId` 和 `userId` 长度相加不得超过 126 字节。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The user ID for live transcoding. The sum length of `roomId` and `userId` should not exceed 126 bytes.<br>
 *        This parameter cannot be updated while pushing stream to the CDN.
 */
@property(copy, nonatomic) NSString * _Nonnull userId;
/**
 * @locale zh
 * @brief 获取默认转推直播配置参数。
 * @return 转推直播配置参数，参看 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}。
 */
/**
 * @locale en
 * @brief Gets the default configurations for pushing streams to CDN.
 * @return Configurations for pushing streams to CDN. See ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}.
 */
+ (instancetype _Nonnull)defaultTranscoding;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 图片合流相关参数。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief  Image parameters for stream mixing.(New)
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig : NSObject
/**
 * @locale zh
 * @brief 原始图片的宽度，单位为 px。
 */
/**
 * @locale en
 * @brief Width of the original image in px.
 */
@property (assign, nonatomic) NSInteger imageWidth;
/**
 * @locale zh
 * @brief 原始图片的高度，单位为 px。
 */
/**
 * @locale en
 * @brief Height of the original image in px.
 */
@property (assign, nonatomic) NSInteger imageHeight;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 单个图片或视频流在合流中的布局信息。(新)<br>
 *        开启合流功能后，在多路图片或视频流合流时，你可以设置其中一路流在合流中的预设布局信息。
 */
/**
 * @locale en
 * @type keytype
 * @brief Layout information for one of the video streams to be mixed.(New)<br>
 *        After starting to push streams to CDN and mixing multiple video streams, you can set the layout information for each of them.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamLayoutRegionConfig : NSObject
/**
 * @locale zh
 * @brief 视频流发布用户的用户 ID 。建议设置。
 */
/**
 * @locale en
 * @brief The user ID of the user who publishes the video stream. It's recommended to be set.
 */
@property(copy, nonatomic) NSString * _Nonnull userID;
/**
 * @locale zh
 * @brief 图片或视频流所在房间的房间 ID。建议设置。<br>
 *        如果此图片或视频流是通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
 */
/**
 * @locale en
 * @brief The room ID of the media stream. It's recommended to be set.<br>
 *        If the media stream is the stream forwarded by startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}, you must set the roomID to the room ID of the target room. 
 */
@property(copy, nonatomic) NSString * _Nonnull roomID;
/**
 * @locale zh
 * @brief 单个用户画面左上角在整个画布坐标系中的 X 坐标（pixel），即以画布左上角为原点，用户画面左上角相对于原点的横向位移。<br>
 *        取值范围为 [0, 整体画布宽度)。默认值为 0。
 */
/**
 * @locale en
 * @brief The X-coordinate in pixels of the upper-left corner of the user's frame in the entire canvas coordinate system, where the origin is at the upper-left corner of the canvas. It represents the horizontal displacement of the upper-left corner of the user's frame relative to the origin.<br>
 *        The value range is [0, the width of the canvas). The default value is 0.
 */
@property(assign, nonatomic) NSInteger locationX;
/**
 * @locale zh
 * @brief 单个用户画面左上角在整个画布坐标系中的 Y 坐标（pixel），即以画布左上角为原点，用户画面左上角相对于原点的纵向位移。<br>
 *        取值范围为 [0, 整体画布高度)。默认值为 0。
 */
/**
 * @locale en
 * @brief The Y-coordinate in pixels of the upper-left corner of the user's frame in the entire canvas coordinate system, where the origin is at the upper-left corner of the canvas. It represents the vertical displacement of the upper-left corner of the user's frame relative to the origin.<br>
 *        The value range is [0, the height of the canvas). The default value is 0.
 */
@property(assign, nonatomic) NSInteger locationY;
/**
 * @locale zh
 * @brief 单个用户画面的宽度。取值范围为 [0, 整体画布宽度]，默认值为 360。
 */
/**
 * @locale en
 * @brief The width of the user's frame in pixels. The value range is [0, the width of the canvas]. The default value is 360.
 */
@property(assign, nonatomic) NSInteger width;
/**
 * @locale zh
 * @brief 单个用户画面的高度。取值范围为 [0, 整体画布高度]，默认值为 640。
 */
/**
 * @locale en
 * @brief The heigh of the user's frame in pixels. The value range is [0, the height of the canvas]. The default value is 640.
 */
@property(assign, nonatomic) NSInteger height;
/**
 * @locale zh
 * @brief 用户视频布局在画布中的层级。取值范围为 [0 - 100]，0 为底层，值越大越上层。默认值为 0。建议设置。
 */
/**
 * @locale en
 * @brief The layer on which the video is rendered. The range is [0, 100]. 0 for the bottom layer, and 100 for the top layer. The default value is 0. It's recommended to be set.
 */
@property(assign, nonatomic) NSInteger zOrder;
/**
 * @locale zh
 *  @brief 是否为本地用户
 */
/**
 * @locale en
 *  @brief Whether the source user of the stream is a local user.
 */
@property(assign, nonatomic) BOOL isLocalUser;
/**
 * @locale zh
 *  @brief 流类型，默认为主流
 */
/**
 * @locale en
 *  @brief The mixed stream type, the default value is Main.
 */
@property(assign, nonatomic) ByteRTCMixedStreamVideoType streamType;
/**
 * @locale zh
 * @brief 透明度，可选范围为 (0.0, 1.0]，0.0 为全透明。默认值为 1.0。
 */
/**
 * @locale en
 * @brief The opacity in range of (0.0, 1.0]. The lower value, the more transparent. The default value is 1.0.
 */
@property(assign, nonatomic) CGFloat alpha;
/**
 * @locale zh
 * @brief 圆角半径相对画布宽度的比例。默认值为 `0.0`。<br>
 *        做范围判定时，首先根据画布的宽高，将 `width`，`height`，和 `cornerRadius` 分别转换为像素值：`width_px`，`height_px`，和 `cornerRadius_px`。然后判定是否满足 `cornerRadius_px < min(width_px/2, height_px/2)`：若满足，则设置成功；若不满足，则将 `cornerRadius_px` 设定为 `min(width_px/2, height_px/2)`，然后将 `cornerRadius` 设定为 `cornerRadius_px` 相对画布宽度的比例值。
 */
/**
 * @locale en
 * @brief The proportion of the radius to the width of the canvas. `0.0` by default.<br>
 *        After you set the value, `width_px`, `height_px`, and `cornerRadius_px` are calculated based on `width`, `height`, `cornerRadius`, and the width of the canvas. If `cornerRadius_px < min(width_px/2, height_px/2)` is met, the value of `cornerRadius` is set valid; if not, `cornerRadius_px` is set to `min(width_px/2, height_px/2)`, and `cornerRadius` is set to the proportion of `cornerRadius_px` to the width of the canvas.
 */
@property(assign, nonatomic) CGFloat cornerRadius;
/**
 * @locale zh
 * @brief 合流内容控制。默认值为 `ByteRTCTranscoderContentControlTypeHasAudioAndVideo`，参看 ByteRTCMixedStreamMediaType{@link #ByteRTCMixedStreamMediaType} 。
 */
/**
 * @locale en
 * @brief The stream mixing content type. The default value is `ByteRTCTranscoderContentControlTypeHasAudioAndVideo`. See ByteRTCMixedStreamMediaType{@link #ByteRTCMixedStreamMediaType}.
 */
@property (assign, nonatomic) ByteRTCMixedStreamMediaType mediaType;
/**
 * @locale zh
 * @brief 图片或视频流的缩放模式，参看 ByteRTCMixedStreamRenderMode{@link #ByteRTCMixedStreamRenderMode}。默认值为 1。
 */
/**
 * @locale en
 * @brief The render mode. See ByteRTCMixedStreamRenderMode{@link #ByteRTCMixedStreamRenderMode}. The default value is 1.
 */
@property(assign, nonatomic) ByteRTCMixedStreamRenderMode renderMode;
/**
 * @locale zh
 * @brief 合流布局区域类型。参看 ByteRTCMixedStreamLayoutRegionType{@link #ByteRTCMixedStreamLayoutRegionType}。建议设置。
 */
/**
 * @locale en
 * @brief Stream mixing region type. See ByteRTCMixedStreamLayoutRegionType{@link #ByteRTCMixedStreamLayoutRegionType}. It's recommended to be set.
 */
@property (assign, nonatomic) ByteRTCMixedStreamLayoutRegionType regionContentType;
/**
 * @locale zh
 * @brief 图片合流布局区域类型对应的数据。类型为图片时传入图片 RGBA 数据，当类型为视频流时传空。
 */
/**
 * @locale en
 * @brief   The RGBA data of the mixing image. Put in null when mixing video streams.
 */
@property (strong, nonatomic) NSData * _Nullable imageWaterMark;
/**
 * @locale zh
 * @brief 合流布局区域数据的对应参数。当类型为视频流时传空，类型为图片时传入对应图片的参数，参看 ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig{@link #ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig}。
 */
/**
 * @locale en
 * @brief  Image parameters for stream mixing. See ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig{@link #ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig}. Put in null when mixing video streams.
 */
@property (strong, nonatomic) ByteRTCMixedStreamLayoutRegionImageWaterMarkConfig * _Nullable imageWaterMarkConfig;
/**
 * @locale zh
 * @brief 空间位置。参看 ByteRTCPosition{@link #ByteRTCPosition}。
 */
/**
 * @locale en
 * @brief spatial position. See ByteRTCPosition{@link #ByteRTCPosition}.
 */
@property (strong, nonatomic) ByteRTCPosition * _Nullable spatialPosition;
/**
 * @locale zh
 * @brief 设置某用户是否应用空间音频效果：<br>
 *        + Yes：启用（默认值）<br>
 *        + No：禁用
 */ 
/**
 * @locale en
 * @brief Sets whether a user applies spatial audio effects:<br>
 *        + Yes: Yes (default setting)<br>
 *        + No: No
 */
@property(assign, nonatomic) BOOL applySpatialAudio;
/**
 * @locale zh
 * @valid since 3.57
 * @brief 设置占位图的填充模式。<br>
 *        该参数用来控制当用户停止发布视频流，画面恢复为占位图后，此时占位图的填充模式。参看 ByteRTCMixedStreamAlternateImageFillMode{@link #ByteRTCMixedStreamAlternateImageFillMode}。
 */
/**
 * @locale en
 * @brief Sets the fill mode of the placeholder image.<br>
 *        This parameter is used to control the fill mode of the placeholder image after the user stops publishing video streams and the screen reverts to the placeholder image. See ByteRTCMixedStreamAlternateImageFillMode{@link #ByteRTCMixedStreamAlternateImageFillMode}.
 */
@property (assign, nonatomic)ByteRTCMixedStreamAlternateImageFillMode alternateImageFillMode;
/**
 * @locale zh
 * @valid since 3.57
 * @brief 设置占位图的 URL，长度小于 1024 字符.
 */
/**
 * @locale en
 * @brief Sets the URL of the placeholder image, limited to a maximum of 1024 characters.
 */
@property(copy, nonatomic)NSString * alternateImageUrl;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 视频流合流整体布局信息。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief The overall video layout of the mixed stream.(New)
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamLayoutConfig : NSObject
/**
 * @locale zh
 * @brief 合流背景颜色，用十六进制颜色码（HEX）表示。例如，#FFFFFF 表示纯白，#000000 表示纯黑。默认值为 #000000。建议设置。<br>
 *        值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @brief Background-color of the mixed stream in hexadecimal values such as #FFFFFF and #000000. The default value is #000000 (black). It's recommended to be set.<br>
 *        With invalid or empty input, the configurations will be set as the default values.
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/**
 * @locale zh
 * @brief 用户布局信息列表。每条流的具体布局参看 ByteRTCMixedStreamLayoutRegionConfig{@link #ByteRTCMixedStreamLayoutRegionConfig}。建议设置。<br>
 *        值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @brief List of user's video layout information. The specific layout of each stream is detailed in ByteRTCMixedStreamLayoutRegionConfig{@link #ByteRTCMixedStreamLayoutRegionConfig}. It's recommended to be set.<br>
 *        With invalid or empty input, the configurations will be set as the default values.
 */
@property(copy, nonatomic) NSArray<ByteRTCMixedStreamLayoutRegionConfig *> * _Nonnull regions;
/**
 * @locale zh
 * @brief 用户透传的额外数据。
 */
/**
 * @locale en
 * @brief Info passed through from the user.
 */
@property(copy, nonatomic) NSString *_Nonnull userConfigExtraInfo;
/**
 * @locale zh
 * @valid since 3.57
 * @brief 设置合流后整体画布的背景图片 URL，长度最大为 1024 bytes。<br>
 *        支持的图片格式包括：JPG, JPEG, PNG。如果背景图片的宽高和整体屏幕的宽高不一致，背景图片会缩放到铺满屏幕。
 */
/**
 * @locale en
 * @valid since 3.57
 * @brief Sets the URL of the background image for the canvas that renders the mixed stream, with a maximum length of 1024 bytes.<br>
 *        You can input images in the following supported formats: JPG, JPEG, PNG.<br>
 *        If the width and height of the background image are different from the screen dimensions, the background image will be scaled to fill the screen.
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundImageUrl;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 视频转码配置参数。(新)<br>
 *        值不合法或未设置时，自动使用默认值。
 */
/**
 * @locale en
 * @type keytype
 * @brief Video transcoding configurations.(New)<br>
 *        With invalid or empty input, the configurations will be set as the default values.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamVideoConfig : NSObject
/**
 * @locale zh
 * @brief 视频编码格式，参看 ByteRTCMixedStreamVideoCodecType{@link #ByteRTCMixedStreamVideoCodecType}。默认值为 `0`。建议设置。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The video codec. See ByteRTCMixedStreamVideoCodecType{@link #ByteRTCMixedStreamVideoCodecType}. The default value is `0`. It's recommended to be set.<br>
 *        These parameters cannot be updated while pushing stream to the CDN.
 */
@property(assign, nonatomic) ByteRTCMixedStreamVideoCodecType videoCodec;
/**
 * @locale zh
 * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640 px。建议设置。<br>
 *        设置值为非偶数时，自动向上取偶数。
 */
/**
 * @locale en
 * @brief The width (pixels) to be set. The range is [2, 1920], and must be an even number. The default value is 640 pixels. It's recommended to be set.<br>
 *        If an odd number is set, the width will be adjusted to the next larger even number.
 */
@property(assign, nonatomic) NSInteger width;
/**
 * @locale zh
 * @brief 合流视频高度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 360 px。建议设置。<br>
 *        设置值为非偶数时，自动向上取偶数。
 */
/**
 * @locale en
 * @brief The height (pixels) to be set. The range is [2, 1920], and must be an even number. The default value is 360 pixels. It's recommended to be set.<br>
 *        If an odd number is set, the height will be adjusted to the next larger even number.
 */
@property(assign, nonatomic) NSInteger height;
/**
 * @locale zh
 * @brief 合流视频帧率。单位为 FPS，取值范围为 [1,60]，默认值为 15 FPS。建议设置。
 */
/**
 * @locale en
 * @brief The frame rate (FPS) in range of [1, 60]. The default value is 15 FPS. It's recommended to be set.
 */
@property(assign, nonatomic) NSInteger fps;
/**
 * @locale zh
 * @brief 视频 I 帧时间间隔。单位为秒，取值范围为 [1, 5]，默认值为 2 秒。建议设置。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The time interval between I-frames (second) in range of [1, 5]. The default value is 2 seconds. It's recommended to be set.<br>
 *        These parameters cannot be updated while pushing stream to the CDN.
 */
@property(assign, nonatomic) NSInteger gop;
/**
 * @locale zh
 * @brief 合流视频码率。单位为 Kbps，取值范围为 [1,10000]，默认值为自适应模式。建议设置。
 */
/**
 * @locale en
 * @brief The bitrate (Kbps) in range of [1, 10000]. The default value is self-adaptive. It's recommended to be set.
 */
@property(assign, nonatomic) NSInteger bitrate;
/**
 * @locale zh
 * @brief 是否在合流中开启B帧，仅服务端合流支持.
 */
/**
 * @locale en
 * @brief Whether to push streams with B frame, only support by server mix.
 */
@property(assign, nonatomic) BOOL enableBFrame;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 音频转码配置参数。(新)<br>
 *        值不合法或未设置时，自动使用默认值。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio transcoding configurations.(New)<br>
 *        With invalid or empty input, the configurations will be set as the default values.<br>
 *        These parameters cannot be updated while pushing stream to the CDN.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamAudioConfig : NSObject
/**
 * @locale zh
 * @brief 音频编码格式。
 * @param codec 音频编码格式，参看 ByteRTCMixedStreamAudioCodecType{@link #ByteRTCMixedStreamAudioCodecType}。默认值为 `0`。建议设置。
 */
/**
 * @locale en
 * @brief The audio codec.
 * @param codec The audio codec. See ByteRTCMixedStreamAudioCodecType{@link #ByteRTCMixedStreamAudioCodecType}. Defaults to `0`. It's recommended to be set.
 */
@property(assign, nonatomic) ByteRTCMixedStreamAudioCodecType audioCodec;
/**
 * @locale zh
 * @brief 音频采样率，单位 Hz。可取 32000 Hz、44100 Hz、48000 Hz，默认值为 48000 Hz。建议设置。
 */
/**
 * @locale en
 * @brief The sample rate (Hz). Supported sample rates: 32,000 Hz, 44,100 Hz, 48,000 Hz. Defaults to 48,000 Hz. It's recommended to be set.
 */
@property(assign, nonatomic) NSInteger sampleRate;
/**
 * @locale zh
 * @brief 音频声道数。可取 1（单声道）、2（双声道），默认值为 2。建议设置。
 */
/**
 * @locale en
 * @brief The number of channels. Supported channels: 1 (single channel), 2 (dual channel).  Defaults to 2. It's recommended to be set.
 */
@property(assign, nonatomic) NSInteger channels;
/**
 * @locale zh
 * @brief 音频码率，单位 Kbps。可取范围 [32, 192]，默认值为 64 Kbps。建议设置。
 */
/**
 * @locale en
 * @brief The bitrate (Kbps) in range of [32, 192]. Defaults to 64 Kbps. It's recommended to be set.
 */
@property(assign, nonatomic) NSInteger bitrate;
/**
 * @locale zh
 * @brief AAC 编码规格，参看 ByteRTCMixedStreamAudioProfile{@link #ByteRTCMixedStreamAudioProfile}。默认值为 `0`。建议设置。
 */
/**
 * @locale en
 * @brief AAC profile. See ByteRTCMixedStreamAudioProfile{@link #ByteRTCMixedStreamAudioProfile}. Defaults to `0`. It's recommended to be set.
 */
@property(assign, nonatomic) ByteRTCMixedStreamAudioProfile audioProfile;
/**
 * @hidden
 * @deprecated
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteRTCMixedStreamAudioProfile) aacProfile;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 推流 CDN 的空间音频参数。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Spatial audio config when pushing to CDN.(New)
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamSpatialAudioConfig : NSObject
/**
 * @locale zh
 * @brief 是否开启推流 CDN 时的空间音频效果。<br>
 *        当你启用此效果时，你需要设定推流中各个 ByteRTCMixedStreamLayoutRegionConfig{@link #ByteRTCMixedStreamLayoutRegionConfig} 的 `spatialPosition` 值，实现空间音频效果。
 */
/**
 * @locale en
 * @brief Whether to enable the spatial audio effect when pushing to CDN.<br>
 *        when you enable the feature, set the `spatialPosition` of each ByteRTCMixedStreamLayoutRegionConfig{@link #ByteRTCMixedStreamLayoutRegionConfig} for spatial audio effect.
 */
@property(assign, nonatomic) BOOL enableSpatialRender;
/**
 * @locale zh
 * @brief 听众的空间位置。参看 ByteRTCPosition{@link #ByteRTCPosition}。<br>
 *        听众指收听来自 CDN 的音频流的用户。
 */
/**
 * @locale en
 * @brief The spatial position of the audience. See ByteRTCPosition{@link #ByteRTCPosition}. <br>
 *        The audience is the users who receive the audio stream from CDN.
 */
@property (strong, nonatomic) ByteRTCPosition * _Nullable audienceSpatialPosition;
/**
 * @locale zh
 * @brief 听众的空间朝向。参看 ByteRTCHumanOrientation{@link #ByteRTCHumanOrientation}。<br>
 *        听众指收听来自 CDN 的音频流的用户。
 */
/**
 * @locale en
 * @brief The orientation of the audience. See ByteRTCHumanOrientation{@link #ByteRTCHumanOrientation}. <br>
 *        The audience is the users who receive the audio stream from CDN.
 */
@property(strong, nonatomic) ByteRTCHumanOrientation * _Nullable audienceSpatialOrientation;

@end

/**
 * @locale zh
 * @type keytype
 * @brief 客户端合流参数。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Client mixing parameters.(New)
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamClientMixConfig : NSObject
/**
 * @locale zh
 * @brief 客户端合流是否使用混音，默认为 true。
 */
/**
 * @locale en
 * @brief Whether to use audio mixing. Default is true.
 */
@property(assign, nonatomic) BOOL useAudioMixer;
/**
 * @locale zh
 * @brief 客户端合流回调视频格式，参看 ByteRTCMixedStreamClientMixVideoFormat{@link #ByteRTCMixedStreamClientMixVideoFormat}。
 */
/**
 * @locale en
 * @brief The video format to be set. See ByteRTCMixedStreamClientMixVideoFormat{@link #ByteRTCMixedStreamClientMixVideoFormat}.
 */
@property(assign, nonatomic) ByteRTCMixedStreamClientMixVideoFormat videoFormat;
@end

/**
 * @locale zh
 * @hidden internal use only
 * @valid since 3.52
 * @type keytype
 * @brief 转推直播单通同步参数。(新)
 */
/**
 * @locale en
 * @hidden internal use only
 * @valid since 3.52
 * @type keytype
 * @brief Mixed Stream sync control parameters.(New)
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamSyncControlConfig : NSObject
/**
 * @locale zh
 * @brief 同步策略
 */
@property(assign, nonatomic)ByteRTCMixedStreamSyncStrategy syncStrategy;
/**
 * @locale zh
 * @brief 在进行同步处理时，基准流所属用户的 ID。默认为空。
 */
/**
 * @locale en
 * @brief User ID of the base stream during syncing. Null by default.
 */
@property(copy, nonatomic) NSString * _Nullable baseUserID;
/**
 * @locale zh
 * @brief 在进行同步处理时，缓存音视频流的最大长度。单位为毫秒。默认值为 2000。<br>
 *        参与转推直播的这些媒体流延迟越高，应该将此值设置的越大。但此值越大，因缓存媒体流造成的内存占用也会更大。推荐值为 `2000`。
 */
/**
 * @locale en
 * @brief The max length of the cached stream in milliseconds. 2000 by default.<br>
 *        Set the value based on the stall of the media streams. Higher the value, bigger the memory usage. The recommended value is `2000`.
 */
@property(assign, nonatomic) NSInteger maxCacheTimeMs;
/**
 * @locale zh
 * @brief 是否通过 RTC SDK 进行转推直播。默认为 True。<br>
 *        如果选择 `False`，你会通过 onCacheSyncVideo:withDataFrame:withUids:taskId:{@link #LiveTranscodingDelegate#onCacheSyncVideo:withDataFrame:withUids:taskId:} 收到同步的帧，你可以使用此视频帧，自行实现合流转推。
 */
/**
 * @locale en
 * @brief Whether to use RTC SDK to push to CDN. True by default.<br>
 *        If `False`, you can get the media frames by onCacheSyncVideo:withDataFrame:withUids:taskId:{@link #LiveTranscodingDelegate#onCacheSyncVideo:withDataFrame:withUids:taskId:} and manually push them to CDN.
 */
@property(assign, nonatomic) BOOL videoNeedSdkMix;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 服务端合流控制参数
 */
/**
 * @locale en
 * @type keytype
 * @brief Configurations to be set while mixing streams on the server side.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamServerControlConfig : NSObject
/**
 * @locale zh
 * @valid since 3.56
 * @brief 是否开启单独发送声音提示 SEI 的功能：<br>
 *        + True：开启；<br>
 *        + False：关闭。（默认值）<br>
 *        开启后，你可以通过 `ByteRTCMixedStreamServerControlConfig.seiContentMode` 控制 SEI 的内容是否只携带声音信息。
 */
/**
 * @locale en
 * @valid since 3.56
 * @brief Sets whether to enable the function of separately sending sound indication SEI:<br>
 *        + True: Enable.<br>
 *        + False: Disable. Default setting.<br>
 *        After setting this parameter to "true", you can choose whether to send sound indication SEI only through `ByteRTCMixedStreamServerControlConfig.seiContentMode`.
 */
@property(assign, nonatomic) BOOL enableVolumeIndication;
/**
 * @locale zh
 * @valid since 3.56
 * @brief 声音提示间隔，单位为秒，取值范围为 [0.3,+∞)，默认值为 2。<br>
 *        此值仅取整百毫秒。若传入两位及以上小数，则四舍五入取第一位小数的值。例如，若传入 0.36，则取 0.4。
 */
/**
 * @locale en
 * @valid since 3.56
 * @brief Sound indication interval in s. The range is [0.3,+∞). The default value is 2.<br>
 *        If a decimal with two or more decimal places is passed in, it will be rounded to the value of the first decimal place. For example, if you pass in 0.36, it will be automatically adjusted to 0.4.
 */
@property(assign, nonatomic) CGFloat volumeIndicationInterval;
/**
 * @locale zh
 * @valid since 3.56
 * @brief 有效音量大小，取值范围为 [0, 255]，默认值为 0。<br>
 *        超出取值范围则自动调整为默认值，即 0。
 */
/**
 * @locale en
 * @valid since 3.56
 * @brief Effective volume within the range of [0, 255]. The default value is 0.<br>
 *        If the value is set beyond the range, it will be automatically adjusted to the default value 0.
 */
@property(assign, nonatomic) NSInteger talkVolume;
/**
 * @locale zh
 * @valid since 3.56
 * @brief 声音信息 SEI 是否包含音量值：<br>
 *        + True：是；<br>
 *        + False：否，默认值。
 */
/**
 * @locale en
 * @valid since 3.56
 * @brief Sets whether volume value is contained in the sound indication SEI:<br>
 *        + True: Yes.<br>
 *        + False: No. Default setting.
 */
@property(assign, nonatomic) BOOL isAddVolumeValue;
/**
 * @locale zh
 * @valid since 3.56
 * @brief 设置 SEI 内容。参看 ByteRTCMixedStreamSEIContentMode{@link #ByteRTCMixedStreamSEIContentMode}。
 */
/**
 * @locale en
 * @valid since 3.56
 * @brief Sets SEI content. See ByteRTCMixedStreamSEIContentMode{@link #ByteRTCMixedStreamSEIContentMode}.
 */
@property(assign, nonatomic) ByteRTCMixedStreamSEIContentMode seiContentMode;
/**
 * @locale zh
 * @valid since 3.56
 * @brief SEI 信息的 payload type。<br>
 *        默认值为 `100`，只支持设置 `5` 和 `100`。<br>
 *        在转推直播的过程中，该参数不支持变更。  
 */
/**
 * @locale en
 * @valid since 3.56
 * @brief SEI payload type.<br>
 *        The default value is `100`, and the value supported is `5` and `100`.<br>
 *        During the process of pushing streams to CDN, you cannot change the parameter. 
 */
@property(assign, nonatomic) NSInteger seiPayloadType;
/**
 * @locale zh
 * @valid since 3.56
 * @brief SEI 信息的 payload UUID。
 * @note PayloadType 为 `5` 时，必须填写 PayloadUUID，否则会收到错误回调，错误码为1091。  <br>
 *         PayloadType 不是 `5` 时，不需要填写 PayloadUUID，如果填写会被后端忽略。   <br>
 *         该参数长度需为32位，否则会收到错误码为1091的回调。  <br>
 *         该参数每个字符的范围需为 [0, 9] [a, f] [A, F] <br>
 *         该参数不应带有`-`字符，如系统自动生成的 UUID 中带有`-`，则应删去。<br>
 *         在转推直播的过程中，该参数不支持变更。       
 */
/**
 * @locale en
 * @valid since 3.56
 * @brief SEI payload UUID.
 * @note When PayloadType is `5`, you must set PayloadUUID, or you will receive a callback indicating parameter error. The error code is 1091.  <br>
 *         When PayloadType is not `5`, it is not required to set PayloadUUID. If filled, it will be ignored by the backend. <br>
 *         The length of PayloadUUID should be 32 bits, or you will receive an error code of 1091.   <br>
 *         Each character of the parameter should be within the range of [0, 9] [a, f] [A, F].  <br>
 *         The PayloadUUID should not contain `-`. If the automatically generated UUID contains `-`, you should delete it. <br>
 *         During the process of pushing streams to CDN, you cannot change the parameter.  
 */
@property(copy, nonatomic) NSString *seiPayloadUUID;
/**
 * @locale zh
 * @valid since 3.57
 * @brief 设置合流推到 CDN 时输出的媒体流类型。参看 ByteRTCMixedStreamMediaType{@link #ByteRTCMixedStreamMediaType}。<br>
 *        默认输出音视频流。支持输出纯音频流，但暂不支持输出纯视频流。
 */
/**
 * @locale en
 * @brief Sets the type of media stream pushed to CDN after being mixed. ByteRTCMixedStreamMediaType{@link #ByteRTCMixedStreamMediaType}.<br>
 *        The default value is 0，which means pushing both audio and video.<br>
 *        Pushing video only is not supported currently.
 */
@property(assign, nonatomic) ByteRTCMixedStreamMediaType mediaType;
/**
 * @locale zh
 * @valid since 3.57
 * @brief 设置是否在没有用户发布流的情况下发起转推直播。具体参看 ByteRTCMixedStreamPushMode{@link #ByteRTCMixedStreamPushMode}。<br>
 *        该参数在发起合流任务后的转推直播过程中不支持动态变更。
 */
/**
 * @locale en
 * @brief Sets whether to initiate a stream mixing task in the absence of any users publishing streams. See ByteRTCMixedStreamPushMode{@link #ByteRTCMixedStreamPushMode}.<br>
 *        Once the stream mixing task is initiated, this parameter can not be updated any more.
 */
@property(assign, nonatomic) ByteRTCMixedStreamPushMode pushStreamMode;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 转推直播配置参数。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief Configurations to be set while pushing media streams to CDN.(New)
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMixedStreamConfig : NSObject
/**
 * @locale zh
 * @brief 合流类型，详见 ByteRTCMixedStreamType{@link #ByteRTCMixedStreamType} 数据类型。建议设置。
 */
/**
 * @locale en
 * @brief Stream mixing type. See ByteRTCMixedStreamType{@link #ByteRTCMixedStreamType}. It's recommended to be set.
 */
@property(assign, nonatomic) ByteRTCMixedStreamType expectedMixingType;
/**
 * @locale zh
 * @brief 视频流合流整体布局信息。<br>
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。详见 ByteRTCMixedStreamLayoutConfig{@link #ByteRTCMixedStreamLayoutConfig} 数据类型。
 */
/**
 * @locale en
 * @brief The overall video layout of the mixed stream.<br>
 *        After starting to push streams to CDN, you can set the layout of each video stream, the background information of the mixed stream, etc. See ByteRTCMixedStreamLayoutConfig{@link #ByteRTCMixedStreamLayoutConfig} for details.
 */
@property(strong, nonatomic) ByteRTCMixedStreamLayoutConfig * _Nonnull layoutConfig;
/**
 * @locale zh
 * @brief 视频转码配置参数。详见 ByteRTCMixedStreamVideoConfig{@link #ByteRTCMixedStreamVideoConfig} 数据类型。建议设置。
 */
/**
 * @locale en
 * @brief Video transcoding related configurations. See ByteRTCMixedStreamVideoConfig{@link #ByteRTCMixedStreamVideoConfig}. It's recommended to be set.
 */
@property(strong, nonatomic) ByteRTCMixedStreamVideoConfig * _Nonnull videoConfig;
/**
 * @locale zh
 * @brief 音频合流配置参数，参看 ByteRTCMixedStreamAudioConfig{@link #ByteRTCMixedStreamAudioConfig}。建议设置。
 */
/**
 * @locale en
 * @brief Audio mixed related configurations. See ByteRTCMixedStreamAudioConfig{@link #ByteRTCMixedStreamAudioConfig} for data types. It's recommended to be set.
 */
@property(strong, nonatomic) ByteRTCMixedStreamAudioConfig * _Nonnull audioConfig;
/**
 * @locale zh
 * @brief 客户端合流配置。详见 ByteRTCMixedStreamClientMixConfig{@link #ByteRTCMixedStreamClientMixConfig} 。建议设置。
 */
/**
 * @locale en
 * @brief client mix param. See ByteRTCMixedStreamClientMixConfig{@link #ByteRTCMixedStreamClientMixConfig} for detail. It's recommended to be set.
 */
@property(strong, nonatomic) ByteRTCMixedStreamClientMixConfig * _Nullable clientMixConfig;
/**
 * @locale zh
 * @hidden for internal use only
 * @brief 转推同步配置。详见 ByteRTCMixedStreamSyncControlConfig{@link #ByteRTCMixedStreamSyncControlConfig} 。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @brief client mix param. See ByteRTCMixedStreamSyncControlConfig{@link #ByteRTCMixedStreamSyncControlConfig} for detail.
 */
@property(strong, nonatomic) ByteRTCMixedStreamSyncControlConfig * _Nullable syncControlConfig;
/**
 * @locale zh
 * @hidden(macOS)
 * @brief 转推 CDN 空间音频配置。详见 ByteRTCMixedStreamSpatialAudioConfig{@link #ByteRTCMixedStreamSpatialAudioConfig} 。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @brief The spatial audio config when pushing to CDN. See ByteRTCMixedStreamSpatialAudioConfig{@link #ByteRTCMixedStreamSpatialAudioConfig} for detail.
 */
@property(strong, nonatomic) ByteRTCMixedStreamSpatialAudioConfig * _Nonnull spatialAudioConfig;
/**
 * @locale zh
 * @brief 服务端合流控制参数。详见 ByteRTCMixedStreamServerControlConfig{@link #ByteRTCMixedStreamServerControlConfig} 。
 */
/**
 * @locale en
 * @brief Server mix Control config. See ByteRTCMixedStreamServerControlConfig{@link #ByteRTCMixedStreamServerControlConfig} for detail.
 */
@property(strong, nonatomic) ByteRTCMixedStreamServerControlConfig * _Nonnull serverControlConfig;
/**
 * @locale zh
 * @hidden for internal use only
 * @brief 动态扩展自定义参数。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @brief Custom parameter
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/**
 * @locale zh
 * @hidden for internal use only
 * @brief 业务透传鉴权信息
 */
/**
 * @locale en
 * @hidden for internal use only
 * @brief Authentication information passed through from the App
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable authInfo;
/**
 * @locale zh
 * @brief 推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。建议设置。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The URL for live transcoding. Only supports live transcoding via RTMP. The URL should match the regular expression `/^rtmps?:\/\//`. It's recommended to be set.<br>
 *        This parameter cannot be updated while pushing stream to the CDN.
 */
@property(copy, nonatomic) NSString * _Nullable pushURL;
/**
 * @locale zh
 * @brief 推流房间 ID。`roomID` 和 `userID` 长度相加不得超过 126 字节。建议设置。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The room ID for live transcoding. The sum length of `roomID` and `userID` should not exceed 126 bytes. It's recommended to be set.<br>
 *        This parameter cannot be updated while pushing stream to the CDN.
 */
@property(copy, nonatomic) NSString * _Nonnull roomID;
/**
 * @locale zh
 * @brief 推流用户 ID。`roomID` 和 `userID` 长度相加不得超过 126 字节。建议设置。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The user ID for live transcoding. The sum length of `roomID` and `userID` should not exceed 126 bytes. It's recommended to be set.<br>
 *        This parameter cannot be updated while pushing stream to the CDN.
 */
@property(copy, nonatomic) NSString * _Nonnull userID;
/**
 * @locale zh
 * @brief 获取默认转推直播配置参数。
 * @return 转推直播配置参数，参看 ByteRTCMixedStreamConfig{@link #ByteRTCMixedStreamConfig}。
 */
/**
 * @locale en
 * @brief Gets the default configurations for pushing streams to CDN.
 * @return Configurations for pushing streams to CDN. See ByteRTCMixedStreamConfig{@link #ByteRTCMixedStreamConfig}.
 */
+ (instancetype _Nonnull)defaultMixedStreamConfig;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 单流转推直播配置参数。
 */
/**
 * @locale en
 * @type keytype
 * @brief Configurations for pushing a single media stream to CDN.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPushSingleStreamParam : NSObject
/**
 * @locale zh
 * @brief 推流 CDN 地址。仅支持 RTMP 协议，Url 必须满足正则 `/^rtmps?:\/\//`。<br>
 *        本参数不支持过程中更新。
 */
/**
 * @locale en
 * @brief The URL for live transcoding. Only supports live transcoding via RTMP. The URL should match the regular expression `/^rtmps?:\/\//`.<br>
 *        This parameter cannot be updated while pushing stream to the CDN.
 */
@property(copy, nonatomic) NSString * _Nullable url;
/**
 * @locale zh
 * @brief 媒体流所在的房间 ID
 */
/**
 * @locale en
 * @brief The room ID of the media stream
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/**
 * @locale zh
 * @brief 媒体流所属的用户 ID
 */
/**
 * @locale en
 * @brief The user ID of the media stream
 */
@property(copy, nonatomic) NSString * _Nullable userId;
/**
 * @locale zh
 * @brief 媒体流是否为屏幕流。
 */
/**
 * @locale en
 * @brief Whether the media stream is a screen-sharing stream.
 */
@property(nonatomic, assign) BOOL isScreen;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 视频订阅配置信息
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video subscription configuration information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeVideoConfig : NSObject
/**
 * @locale zh
 * @brief 订阅的视频流分辨率下标。  <br>
 *        当远端用户通过调用 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
 *        默认值为 0，即订阅第一路流。  <br>
 *        如果不想更改之前的设置，可以输入 -1。  
 */
/**
 * @locale en
 * @brief Subscribed video stream resolution subscript.   <br>
 *        Quality level of the video stream subscribed to. <br>
 *        In Simulcast mode, use a number to specify the expected quality of the video stream to be subscribed to.  In Simulcast mode, a video has a diversity of encoded qualities that ranking from 0 to 3. Call enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} to enable Simulcast mode on the publisher's clients.  <br>
 *         Ranging from -1 to 3<br>
 *         0 (Default): The best quality <br>
 *         -1: Use the previous settings. 
 */
@property(assign, nonatomic) NSInteger videoIndex;
/**
 * @locale zh
 * @brief 远端用户优先级，参看 ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}，默认值为 0。
 */
/**
 * @locale en
 * @brief Remote user priority. See ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}, the default value is 0.
 */
@property(assign, nonatomic) NSInteger priority;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 性能回退相关数据
 */
/**
 * @locale en
 * @type keytype
 * @brief  Performance fallback related data
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSourceWantedData : NSObject
/**
 * @locale zh
 * @brief 推荐视频输入宽
 */
/**
 * @locale en
 * @brief Recommended video input width
 */
@property(nonatomic, assign) NSInteger width;
/**
 * @locale zh
 * @brief 推荐视频输入高
 */
/**
 * @locale en
 * @brief Recommended video input high
 */
@property(nonatomic, assign) NSInteger height;
/**
 * @locale zh
 * @brief 推荐视频输入帧率
 */
/**
 * @locale en
 * @brief Recommended video input frame rate
 */
@property(nonatomic, assign) NSInteger frameRate;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。
 */
/**
 * @locale en
 * @type keytype
 * @brief Information of stream switching due to a Fallback
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamSwitchEvent : NSObject
/**
 * @locale zh
 * @brief 订阅的音视频流的发布者的用户 ID。
 */
/**
 * @locale en
 * @brief User ID of the publisher of the subscribed media stream
 */
@property(nonatomic, copy) NSString * _Nonnull uid;
/**
 * @locale zh
 * @brief 流是否是屏幕流
 */
/**
 * @locale en
 * @brief Whether it is a screen-sharing stream
 */
@property(nonatomic, assign) BOOL isScreen;
/**
 * @locale zh
 * @brief 流切换前订阅视频流的分辨率对应的索引
 */
/**
 * @locale en
 * @brief The quality index of the subscribed stream before the stream switching
 */
@property(nonatomic, assign) NSInteger beforeVideoIndex;
/**
 * @locale zh
 * @brief 流切换后订阅视频流的分辨率对应的索引
 */
/**
 * @locale en
 * @brief The quality index of the subscribed stream after the stream switching
 */
@property(nonatomic, assign) NSInteger afterVideoIndex;
/**
 * @locale zh
 * @brief 流切换前是否有视频流
 */
/**
 * @locale en
 * @brief Whether a video stream before the stream switching
 */
@property(nonatomic, assign) BOOL beforeVideoEnabled;
/**
 * @locale zh
 * @brief 流切换后是否有视频流
 */
/**
 * @locale en
 * @brief Whether a video stream after the stream switching
 */
@property(nonatomic, assign) BOOL afterVideoEnabled;
/**
 * @locale zh
 * @brief 流切换原因，详见 ByteRTCFallbackOrRecoverReason{@link #ByteRTCFallbackOrRecoverReason}。
 */
/**
 * @locale en
 * @brief Refer to ByteRTCFallbackOrRecoverReason{@link #ByteRTCFallbackOrRecoverReason} for the reason of the Fallback or reverting from the Fallback of the subscribed stream.
 */
@property(nonatomic, assign) ByteRTCFallbackOrRecoverReason reason;
@end

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51, use ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate} instead.
 * @type callback
 * @brief 自定义的视频渲染
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51, use ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate} instead.
 * @type callback
 * @brief Custom video rendering
 */
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate")
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkProtocol <NSObject>
@required
/**
 * @locale zh
 * @type callback
 * @brief 初始化渲染器
 * @return  
 *         + YES: 自定义的渲染器初始化完成  <br>
 *         + NO: 自定义的渲染器初始化失败，不继续往下运行  
 * @note 初始化渲染器的时候会回调这个方法
 */
/**
 * @locale en
 * @type callback
 * @brief Initialize the renderer
 * @return   
 *          + YES: Custom renderer initialization completed <br>
 *          + NO: Custom renderer initialization failed, do not continue to run 
 * @note Initialize the renderer when this method will be called back
 */
- (BOOL)shouldInitialize DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");;

/**
 * @locale zh
 * @type callback
 * @brief 启动渲染器
 * @note 在开启渲染功能的时候会回调这个方法
 */
/**
 * @locale en
 * @type callback
 * @brief Start the renderer
 * @note This method will be called back when the rendering function is turned on
 */
- (void)shouldStart DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/**
 * @locale zh
 * @type callback
 * @brief 停止渲染器
 * @note 在停止渲染功能的时候会回调这个方法
 */
/**
 * @locale en
 * @type callback
 * @brief Stop the renderer
 * @note This method will be called back when the rendering function is stopped
 */
- (void)shouldStop DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/**
 * @locale zh
 * @type callback
 * @brief 释放渲染器
 * @note 渲染器即将被废弃的时候会回调这个方法
 */
/**
 * @locale en
 * @type callback
 * @brief Release the renderer
 * @note This method will be called back when the renderer is about to be abandoned
 */
- (void)shouldDispose DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/**
 * @locale zh
 * @type callback
 * @brief 获取PixelFormat格式
 * @return Buffer 类型，{@link #ByteRTCVideoSinkPixelFormat}
 * @note 通过该方法的返回值，告知 SDK PixelFormat 的格式
 */
/**
 * @locale en
 * @type callback
 * @brief  Gets the PixelFormat format
 * @return Buffer  type, {@link #ByteRTCVideoSinkPixelFormat}
 * @note  Tells SDK the format of PixelFormat through the return value of this method
 */
- (ByteRTCVideoPixelFormat)pixelFormat DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/**
 * @locale zh
 * @type callback
 * @brief 输出视频的 PixelBuffer
 * @param pixelBuffer 视频的 PixelBuffer
 * @param rotation 视频旋转角度，{@link #ByteRTCVideoRotation}
 * @param cameraId 视频的相机Id, {@link #ByteRTCCameraID}
 * @param extendedData 视频帧附加的数据,视频解码后获得的附加数据
 * @note 通过该方法获取视频的 PixelBuffer
 */
/**
 * @locale en
 * @type callback
 * @brief Output video PixelBuffer
 * @param pixelBuffer Video PixelBuffer
 * @param rotation Video rotation angle, {@link #ByteRTCVideoRotation}
 * @param cameraId Video camera id, {@link #ByteRTCCameraID}
 * @param extendedData Video frame additional data, additional data obtained after video decoding
 * @note Get video PixelBuffer through this method
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
                 cameraId:(ByteRTCCameraID) cameraId
             extendedData:(NSData * _Nullable)extendedData DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/**
 * @hidden
 */
- (int)getRenderElapse;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 自定义视频渲染器
 */
/**
 * @locale en
 * @type keytype
 * @brief Custom video renderer
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkDelegate <NSObject>
@optional
/**
 * @locale zh
 * @deprecated since 3.54, use onFrame: instead
 * @type api
 * @brief 输出视频的 PixelBuffer
 * @param pixelBuffer 视频的 PixelBuffer
 * @param rotation 视频旋转角度，参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 * @param contentType 视频内部类型 参看 ByteRTCVideoContentType{@link #ByteRTCVideoContentType}
 * @param extendedData 视频解码后获得的附加数据
 */
/**
 * @locale en
 * @deprecated since 3.54, use onFrame: instead
 * @type api
 * @brief Outputs video PixelBuffer
 * @param pixelBuffer Video PixelBuffer
 * @param rotation Video rotation angle. See ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 * @param contentType Video content type. See ByteRTCVideoContentType{@link #ByteRTCVideoContentType}
 * @param extendedData Additional data obtained after video is decoded.
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
                 contentType:(ByteRTCVideoContentType)contentType
             extendedData:(NSData * _Nullable)extendedData;
/**
 * @hidden
 */
- (int)getRenderElapse;

@required
/**
 * @locale zh
 * @type api
 * @brief 输出视频的 PixelBuffer
 * @param videoFrame 视频帧
 */
/**
 * @locale en
 * @type api
 * @brief Outputs video PixelBuffer
 * @param videoFrame video frame
 */
- (void)onFrame:(ByteRTCVideoFrame * _Nonnull)videoFrame;

@end

/**
 * @locale zh
 * @hidden for internal use only
 * @type callback
 * @brief 外部渲染数据的消费接口
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type callback
 * @brief Consumption interface for external rendering data
 */
@protocol ByteRTCVideoFrameConsumerObserver <NSObject>
/**
 * @locale zh
 * @brief 输出 yuv420 数据
 * @param ocFrame 数据 Buffer
 * @param width 视频宽度
 * @param rotation 视频旋转角度
 * @param timestamp 时间戳
 */
/**
 * @locale en
 * @brief Output yuv420 data
 * @param ocFrame  Data Buffer
 * @param width  Video width
 * @param rotation  Video rotation angle
 * @param timestamp  Timestamp
 */
- (void)consumeYUV420Buffer:(CVPixelBufferRef _Nullable)ocFrame
    width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
/**
 * @locale zh
 * @brief 输出 RGBA 数据
 * @param ocFrame 数据 Buffer
 * @param width 视频宽度
 * @param rotation 视频旋转角度
 * @param timestamp 时间戳
 */
/**
 * @locale en
 * @brief Output RGBA data
 * @param ocFrame Data Buffer
 * @param width Video width
 * @param rotation Video rotation angle
 * @param timestamp Timestamp
 */
- (void)consumeRGBABuffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width
    rotation:(NSInteger)rotation timestamp:(long)timestamp;
@end

/**
 * @locale zh
 * @hidden
 * @deprecated
 * @type callback
 * @region 视频管理
 */
/**
 * @locale en
 * @hidden
 * @deprecated
 * @type callback
 * @region  Video Management
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoFrameObserver <NSObject>
/**
 * @locale zh
 * @brief 本地屏幕流的视频帧数据回调
 * @param frame 本地屏幕视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
/**
 * @locale en
 * @brief Callback of video frame data for local screen stream
 * @param frame Local screen video frame data, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
- (void)onLocalScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame;
/**
 * @locale zh
 * @brief 本地视频流的视频帧数据回调
 * @param frame 本地视频流的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
/**
 * @locale en
 * @brief Callback of video frame data for local video stream
 * @param frame Video frame data for local video stream, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
- (void)onLocalVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

/**
 * @locale zh
 * @brief 远端屏幕流的视频帧数据回调
 * @param frame 远端屏幕的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid 远端屏幕共享用户ID
 * @param room 对应流的房间 id
 */
/**
 * @locale en
 * @brief Video frame data callback for the remote screen stream
 * @param frame Video frame data for the remote screen, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid Remote screen sharing user ID
 * @param room Room id for the corresponding stream
 */
- (void)onRemoteScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid
    room:(NSString * _Nullable)room;
/**
 * @locale zh
 * @brief 远端视频流的视频帧数据回调
 * @param frame 远端视频流的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid 远端屏幕共享用户ID
 * @param room 对应流的房间 id
 */
/**
 * @locale en
 * @brief Callback of video frame data of remote video stream
 * @param frame Video frame data of remote video stream, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid Remote screen sharing user ID
 * @param room Room id of corresponding stream
 */
- (void)onRemoteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid
    room:(NSString * _Nullable)room;

/**
 * @hidden for internal use only
 */
- (void)OnMergeFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;

@end

/**
 * @locale zh
 * @type keytype
 * @brief 本地视频帧回调配置。
 */
/**
 * @locale en
 * @type keytype
 * @brief Local video frame callback config.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalVideoSinkConfig : NSObject
/**
 * @locale zh
 * @brief 本地视频帧回调位置，参看 ByteRTCLocalVideoRenderPosition{@link #ByteRTCLocalVideoRenderPosition}，默认回调前处理后的视频帧。
 */
/**
 * @locale en
 * @brief The position of the local video frame. See ByteRTCLocalVideoRenderPosition{@link #ByteRTCLocalVideoRenderPosition}.
 */
@property(nonatomic, assign) ByteRTCLocalVideoRenderPosition position;
/**
 * @locale zh
 * @brief 本地视频帧回调格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}，默认值为 0。
 */
/**
 * @locale en
 * @brief The pixel format of the local video frame. See ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}. The default value is 0.
 */
@property(nonatomic, assign) ByteRTCVideoSinkPixelFormat requiredPixelFormat;

@end

/**
 * @locale zh
 * @type keytype
 * @brief 远端视频帧回调配置。
 */
/**
 * @locale en
 * @type keytype
 * @brief Remote video frame callback configurations.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoSinkConfig : NSObject
/**
 * @locale zh
 * @brief 远端视频帧回调位置，参看 ByteRTCLocalVideoRenderPosition{@link #ByteRTCLocalVideoRenderPosition}，默认回调后处理后的视频帧。
 */
/**
 * @locale en
 * @brief The position of the remote video frame. See ByteRTCLocalVideoRenderPosition{@link #ByteRTCLocalVideoRenderPosition}. The default position is after processing.
 */
@property(nonatomic, assign) ByteRTCRemoteVideoRenderPosition position;
/**
 * @locale zh
 * @brief 远端视频帧回调格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}，默认值为 0。
 */
/**
 * @locale en
 * @brief The pixel format of the remote video frame. See ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}. The default value is 0.
 */
@property(nonatomic, assign) ByteRTCVideoSinkPixelFormat requiredPixelFormat;
/**
 * @locale zh
 * @brief 是否将视频帧自动转正，参看 ByteRTCVideoApplyRotation{@link #ByteRTCVideoApplyRotation}，默认为不旋转。
 */
/**
 * @locale en
 * @brief Whether the video frame needs to be automatically rotate. See ByteRTCVideoApplyRotation{@link #ByteRTCVideoApplyRotation}. The default value is no rotate.
 */
@property(nonatomic, assign) ByteRTCVideoApplyRotation applyRotation;
/**
 * @locale zh
 * @brief 是否将视频帧镜像。参看 ByteRTCVideoRenderMirrorType{@link #ByteRTCVideoRenderMirrorType}，默认为不镜像。<br>
 *        本设置与 setRemoteVideoMirrorType:withMirrorType:{@link #ByteRTCVideo#setRemoteVideoMirrorType:withMirrorType:} （适用于内部渲染）相互独立。
 */
/**
 * @locale en
 * @brief Whether the video frame needs to be mirrored. See ByteRTCVideoRenderMirrorType{@link #ByteRTCVideoRenderMirrorType}. The default value is no mirroring effect.
 */
@property(nonatomic, assign) ByteRTCVideoRenderMirrorType mirrorType;

@end

/**
 * @locale zh
 * @type keytype
 * @brief 视频处理配置参数
 */
/**
 * @locale en
 * @type keytype
 * @brief Video processing configuration parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoPreprocessorConfig : NSObject
/**
 * @locale zh
 * @brief 视频帧的像素格式，参看 ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}。<br>
 *        当前仅支持 `ByteRTCVideoPixelFormatI420` 和 `ByteRTCVideoPixelFormatUnknown` 格式。
 */
/**
 * @locale en
 * @brief For the pixel format of the video frame. See ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}.<br>
 *        Only `ByteRTCVideoPixelFormatI420` and `ByteRTCVideoPixelFormatUnknown` are supported.
 */
@property(nonatomic, assign) ByteRTCVideoPixelFormat requiredPixelFormat;

@end

/**
  * @locale zh
  * @type callback
  * @region 视频处理
  * @brief 视频处理回调接口类<br>
  * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
  */
 /**
  * @locale en
  * @type callback
  * @region  video processing
  * @brief video processing callback interface<br>
  * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
  */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoProcessorDelegate <NSObject>

/**
 * @locale zh
 * @type api
 * @region 视频处理
 * @brief 获取 RTC SDK 采集得到的视频帧，根据 registerLocalVideoProcessor:withConfig:{@link #ByteRTCVideo#registerLocalVideoProcessor:withConfig:} 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。
 * @param srcFrame RTC SDK 采集得到的视频帧，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return 经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @note 如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。
 */
/**
 * @locale en
 * @type api
 * @region  video processing
 * @brief  Get RTC SDK acquired video frames, according to registerLocalVideoProcessor:withConfig:{@link #ByteRTCVideo#registerLocalVideoProcessor:withConfig:} set the video preprocessor, video preprocessing, and finally the processed video frames to the RTC SDK for encoding transmission.
 * @param srcFrame RTC SDK captured video frames, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return  After video preprocessing video frames, returned to the RTC SDK for encoding and transmission, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @note  If you need to cancel the video preprocessing, you can set the video preprocessor to nullptr.
 */
- (ByteRTCVideoFrame* _Nullable)processVideoFrame:(ByteRTCVideoFrame* _Nonnull)srcFrame;

@end
/**
 * @locale zh
 * @type keytype
 * @region 视频管理
 * @brief 屏幕采集设置参数
 */
/**
 * @locale en
 * @type keytype
 * @region  video management
 * @brief  Screen capture setting parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureParam : NSObject
/**
 * @locale zh
 * @brief 屏幕采集宽度
 */
/**
 * @locale en
 * @brief Screen capture width
 */
@property(nonatomic, assign) NSInteger width;
/**
 * @locale zh
 * @brief 屏幕采集高度
 */
/**
 * @locale en
 * @brief Screen capture height
 */
@property(nonatomic, assign) NSInteger height;
/**
 * @locale zh
 * @brief 屏幕采集帧率，单位 fps
 */
/**
 * @locale en
 * @brief Screen capture frame rate in fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/**
 * @locale zh
 * @brief 发送屏幕采集码率，单位 kbps
 */
/**
 * @locale en
 * @brief Screen capture bitrate rate in kbps
 */
@property(nonatomic, assign) NSInteger bitrate;
/**
 * @locale zh
 * @brief 视频最小编码码率, 单位 kbps。编码码率不会低于 `minBitrate`。<br>
 *        默认值为 `0`。<br>
 *        范围：[0, bitrate)，当 `bitrate` < `minBitrate` 时，为适配码率模式。<br>
 *        以下情况，设置本参数无效：<br>
 *        + 当 `bitrate` 为 `0` 时，不对视频流进行编码发送。<br>
 *        + 当 `bitrate` < `0` 时，适配码率模式。
 */
/**
 * @locale en
 * @brief Minimum video encoding bitrate in kbps. The encoding bitrate will not be lower than the `minBitrate`.<br>
 *        It defaults to `0`. <br>
 *        It ranges within [0, bitrate). When `bitrate` < `minBitrate`, the bitrate is self-adpapted.<br>
 *        In the following circumstance, the assignment to this variable has no effect:<br>
 *        + When `bitrate` = `0`, the video encoding is disabled.<br>
 *        + When `bitrate` < `0`, the bitrate is self-adapted.
 */
@property(nonatomic, assign) NSInteger minBitrate;
/**
 * @locale zh
 * @brief 采集区域
 */
/**
 * @locale en
 * @brief Screen capture area.
 */
@property(nonatomic, assign) CGRect regionRect;
/**
 * @locale zh
 * @brief 是否采集鼠标
 */
/**
 * @locale en
 * @brief Whether to capture the mouse
 */
@property(nonatomic, assign) ByteRTCMouseCursorCaptureState mouseCursorCaptureState;
/**
 * @locale zh
 * @brief 屏幕过滤设置
 */
/**
 * @locale en
 * @brief The list of excluded windows.
 */
@property (strong, nonatomic) NSArray<NSNumber *> * _Nullable excludedWindowList;
/**
 * @locale zh
 * @brief 采集区域的边框高亮设置，参看 ByteRTCHighlightConfig{@link #ByteRTCHighlightConfig}。
 */
/**
 * @locale en
 * @brief Settings for highlighting borders of the sharing region. See ByteRTCHighlightConfig{@link #ByteRTCHighlightConfig}.
 */
@property (strong, nonatomic) ByteRTCHighlightConfig * _Nonnull highlightConfig;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 屏幕采集对象的具体信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Screen capture object information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureSourceInfo : NSObject
/**
 * @locale zh
 * @brief 屏幕分享时，共享对象的类型，参看 ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}
 */
/**
 * @locale en
 * @brief The type of the sharing screen. See ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}.
 */
@property (assign, nonatomic) ByteRTCScreenCaptureSourceType sourceType;
/**
 * @locale zh
 * @brief 屏幕分享时，共享对象的 ID。
 */
/**
 * @locale en
 * @brief ID of the sharing object
 */
@property (assign, nonatomic) intptr_t sourceId;
/**
 * @locale zh
 * @brief 屏幕分享时共享对象的名称。
 */
/**
 * @locale en
 * @brief Name of the sharing screen
 */
@property (copy, nonatomic) NSString * _Nullable sourceName;
/**
 * @locale zh
 * @brief 共享的应用窗体所属应用的名称<br>
 *        当共享对象为应用窗体时有效 
 */
/**
 * @locale en
 * @brief The title of the application to be shared.<br>
 *        Only available if the sharing object is an application widnows.
 */
@property (copy, nonatomic) NSString * _Nullable application;
/**
 * @locale zh
 * @brief 共享的应用窗体所属应用进程的 pid<br>
 *        当共享对象为应用窗体时有效 
 */
 /**
 * @locale en
 * @brief Process pid of the application to be shared.<br>
 *        Only available if the sharing object is an application windows.
 */
@property (assign, nonatomic) int pid;
/**
 * @locale zh
 * @brief 共享的屏幕是否为主屏。<br>
 *        当共享对象为屏幕时有效 
 */
 /**
 * @locale en
 * @brief Tag for the screen to be shared identifying whether it is the primary screen<br>
 *        Only available when the screen-sharing object is a screen. 
 */
@property (assign, nonatomic) BOOL primaryMonitor;
/**
 * @locale zh
 * @brief 屏幕共享对象的坐标。多显示器的场景下，屏幕坐标系统以主屏左上角为原点 (0, 0)，向右向下扩展。
 */
/**
 * @locale en
 * @brief Coordinate of the screen-sharing object. (0, 0), the origin is the top left on the main screen for clients with multiple screens.
 */
@property (assign, nonatomic) CGRect regionRect;

@end

/**
 * @locale zh
 * @type keytype
 * @region 视频管理
 * @brief 屏幕采集设置参数
 */
/**
 * @locale en
 * @type keytype
 * @region  video management
 * @brief  Screen capture setting parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenParam : NSObject
/**
 * @locale zh
 * @brief 编码帧率,单位为 fps
 */
/**
 * @locale en
 * @brief Encoded frame rate in fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/**
 * @locale zh
 * @brief 编码码率，小于 0 时 SDK 会根据高宽自适应码率, 单位 kbps
 */
/**
 * @locale en
 * @brief Encoding rate, when less than 0, the SDK will be based on the high and wide self-adaptation rate, in kbps
 */
@property(nonatomic, assign) NSInteger bitrate;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 虚拟背景对象。
 */
/**
 * @locale en
 * @type keytype
 * @brief Virtual background object
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVirtualBackgroundSource: NSObject
/**
 * @locale zh
 * @brief 虚拟背景类型，详见 ByteRTCVirtualBackgroundSourceType{@link #ByteRTCVirtualBackgroundSourceType} 。
 */
/**
 * @locale en
 * @brief See ByteRTCVirtualBackgroundSourceType{@link #ByteRTCVirtualBackgroundSourceType} 。
 */
@property(nonatomic, assign) ByteRTCVirtualBackgroundSourceType sourceType;
/**
 * @locale zh
 * @brief 纯色背景使用的颜色。<br>
 *        格式为 0xAARRGGBB 。
 */
/**
 * @locale en
 * @brief The solid color of the background. <br>
 *        The format is 0xAARRGGBB. 
 */
@property int sourceColor;
/**
 * @locale zh
 * @brief 自定义背景图片的绝对路径。<br>
 *       + 支持的格式为 jpg、jpeg、png。  <br>
 *       + 图片分辨率超过 1080P 时，图片会被等比缩放至和视频一致。  <br>
 *       + 图片和视频宽高比一致时，图片会被直接缩放至和视频一致。  <br>
 *       + 图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。  <br>
 *       + 自定义图片带有局部透明效果时，透明部分由黑色代替。
 */
/**
 * @locale en
 * @brief The absolute path of the specified image.<br>
 *       + You can upload a .JPG, .PNG, or .JPEG file.  <br>
 *       + The image with a resolution higher than 1080p(Full HD) will be rescaled proportionally to fit in the video.  <br>
 *       + If the image's aspect ratio matches the video's, the image will be rescaled proportionally to fit in the video.  <br>
 *       + If the image’s aspect ratio doesn't match the video's, the shortest side (either height or width) of the image will be stretched proportionally to match the video. Then the image will be cropped to fill in the video.  <br>
 *       + The transparent area in the image will be filled with black.
 */
@property(nonatomic) NSString* _Nullable sourcePath;
@end

/**
 * @locale zh
 * @type callback
 * @region 视频数据回调
 * @brief 本地视频帧监测器<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @region Video Data Callback
 * @brief Local video frame observer<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCLocalEncodedVideoFrameObserver<NSObject>
 @optional
/**
 * @locale zh
 * @type callback
 * @region 视频数据回调
 * @brief 调用 registerLocalEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerLocalEncodedVideoFrameObserver:} 后，SDK 每次使用内部采集，采集到一帧视频帧，或收到一帧外部视频帧时，都会回调该事件。
 * @param streamIndex 本地视频帧类型，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frame 本地视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 */
/**
 * @locale en
 * @type callback
 * @region Video Data Callback
 * @brief After calling registerLocalEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerLocalEncodedVideoFrameObserver:}, SDK will trigger this callback when it receives local video frames.
 * @param streamIndex Type of the local video frame. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param frame Information about the local video frame. See ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}.
 */
- (void)onLocalEncodedVideoFrame:(ByteRTCStreamIndex) streamIndex
    Frame:(ByteRTCEncodedVideoFrame * _Null_unspecified)frame;
@end

#pragma mark - ByteRTCEngineExternalVideoEncoderEventHandler

/**
 * @locale zh
 * @type callback
 * @brief 自定义编码帧回调类<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief  Custom coded frame callback class
 * @brief  Custom coded frame callback class.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCExternalVideoEncoderEventHandler<NSObject>
@required
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 提示自定义编码帧可以开始推送的回调。  <br>
 *        收到该回调后，你即可调用 pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:{@link #ByteRTCVideo#pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:} 向 SDK 推送自定义编码视频帧
 * @param streamIndex 可以推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief Prompt custom encoded frames to start pushing callbacks.   <br>
 *         After receiving this callback, you can call pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:{@link #ByteRTCVideo#pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:} Push custom encoded video frames to the SDK
 * @param streamIndex  Properties of the encoded stream that can be pushed. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStart:(ByteRTCStreamIndex)streamIndex;
@required
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧
 * @param streamIndex 需停止推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief When receiving the callback, you need to stop pushing custom encoded video frames to the SDK
 * @param streamIndex The properties of the encoded stream that need to stop pushing. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStop:(ByteRTCStreamIndex)streamIndex;
@required
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 当自定义编码流的帧率或码率发生变化时，触发该回调
 * @param streamIndex 发生变化的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex 对应编码流的下标
 * @param fps 变化后的帧率，单位：fps
 * @param bitRateKps 变化后的码率，单位：kbps
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief When the frame rate or bit rate of a custom encoded stream changes, the callback is triggered
 * @param streamIndex The properties of the changed encoded stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex Corresponding to the subscript of the encoded stream
 * @param fps Changed frame rate, unit: fps
 * @param bitRateKps Changed bit rate, unit: kbps
 */
- (void)onRateUpdate:(ByteRTCStreamIndex)streamIndex
      withVideoIndex:(NSInteger)videoIndex
             withFps:(NSInteger)fps
         withBitRate:(NSInteger)bitRateKps;
@required
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 提示流发布端需重新生成关键帧的回调
 * @param streamIndex 远端编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex 对应编码流的下标
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief This callback is used to inform the stream publisher that a keyframe needs to be regenerated.
 * @param streamIndex Properties of the remote encoded stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex The subscript of the corresponding encoded stream
 */
- (void)onRequestKeyFrame:(ByteRTCStreamIndex)streamIndex
           withVideoIndex:(NSInteger)videoIndex;
@required
/**
 * @locale zh
 * @valid since 3.56
 * @type callback
 * @brief 作为自定义编码视频流的发送端，你会在视频流可发送状态发生变化时，收到此回调。<br>
 *        你可以根据此回调的提示，仅对可发送的视频流进行编码，以降低本端视频编码性能消耗。此回调会根据多个因素综合判断触发，包括：本端设备性能和本端网络性能，以及按需订阅场景下，远端用户是否订阅。
 * @param streamIndex 远端编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param videoIndex 对应编码流的下标
 * @param active 该路流可发送状态
 * @note 要收到此回调，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 设置视频源是自定义编码，且通过 setExternalVideoEncoderEventHandler:{@link #ByteRTCVideo#setExternalVideoEncoderEventHandler:} 设置了回调句柄。
 */
/**
 * @locale en
 * @valid since 3.56
 * @type callback
 * @brief As the sender of a external encoded video stream, you will receive this callback at certain moments. <br>
 *        Based on the hints of this callback, you can selectively encode the video stream that is ready for transmission, in order to reduce the performance impact of video encoding on the local device. This callback is triggered based on a combination of factors, including  the performance of the local device, the local network, and whether the stream is subscribed by the remote user.
 * @param streamIndex See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param videoIndex Subscript of the corresponding encoded stream.
 * @param active The active state of the corresponding encoded stream.
 * @note To receive the callback, call setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} to set the input video source to custom encoded video and call setExternalVideoEncoderEventHandler:{@link #ByteRTCVideo#setExternalVideoEncoderEventHandler:} to set the callback handler.
 */
- (void)onActiveVideoLayer:(ByteRTCStreamIndex)streamIndex
            withVideoIndex:(NSInteger)videoIndex
                withActive:(BOOL)active;
@end

#pragma mark - ByteRTCEngineRemoteEncodedVideoFrameObserver

/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 远端编码后视频数据监测器<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @region  video management
 * @brief  Remote encoded video data monitor
 * @brief  Custom coded frame callback class.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCRemoteEncodedVideoFrameObserver<NSObject>
@required
/**
 * @locale zh
 * @type callback
 * @region 视频数据回调
 * @brief 调用 registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerRemoteEncodedVideoFrameObserver:} 后，SDK 监测到远端编码后视频数据时，触发该回调
 * @param streamKey 收到的远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoFrame 收到的远端视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 */
/**
 * @locale en
 * @type callback
 * @region Video data callback
 * @brief Call registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerRemoteEncodedVideoFrameObserver:} After the SDK detects the remote encoded video data, the callback is triggered
 * @param streamKey Received remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoFrame Received remote video frame information. See ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 */
- (void)onRemoteEncodedVideoFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                   withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧基础信息
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video frame basic information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrameInfo : NSObject
/**
 * @locale zh
 * @brief 视频帧的宽度（像素）
 */
/**
 * @locale en
 * @brief Width of video frame (pixels)
 */
@property(nonatomic, assign) NSInteger width;
/**
 * @locale zh
 * @brief 视频帧的高度（像素）
 */
/**
 * @locale en
 * @brief Height of video frame (pixels)
 */
@property(nonatomic, assign) NSInteger height;
/**
 * @locale zh
 * @brief 视频帧顺时针旋转角度。参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}。
 */
/**
 * @locale en
 * @brief Video frame clockwise rotation angle. See ByteRTCVideoRotation{@link #ByteRTCVideoRotation}.
 */
@property(nonatomic, assign) ByteRTCVideoRotation rotation;
@end

#pragma mark - LiveTranscodingDelegate

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamObserver{@link #ByteRTCMixedStreamObserver} instead.
 * @type callback
 * @region 转推直播
 * @brief 转推直播观察者。  <br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamObserver{@link #ByteRTCMixedStreamObserver} instead.
 * @type callback
 * @region Push to CDN
 * @brief Register this observer to receive stream mixing related callbacks from the SDK.   <br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol LiveTranscodingDelegate <NSObject>
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 是否具有推流能力。  <br>
 *       + false：不具备推流能力（默认值）  <br>
 *       + true：具备推流能力
 * @note 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Whether your App has the ability to push streams to CDN:   <br>
 *        + true: Yes  <br>
 *        + false: No (default value)
 * @note If you need to use the function of intelligently pushing streams to CDN, you should ensure that your App contains librtmp and has the ability to push streams out. If so, set the callback to True.
 */
 - (BOOL)isSupportClientPushStream;
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 转推直播状态回调
 * @param event 转推直播任务状态，参看 ByteRTCStreamMixingEvent{@link #ByteRTCStreamMixingEvent}。
 * @param taskId 转推直播任务 ID。
 * @param Code 转推直播错误码，参看 ByteRtcTranscoderErrorCode{@link #ByteRtcTranscoderErrorCode}。
 * @param mixType 转推直播类型，参看 ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType}。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Used for reporting events during pushing streams to CDN
 * @param event Stream mixing and pushing status, see ByteRTCStreamMixingEvent{@link #ByteRTCStreamMixingEvent}.
 * @param taskId Task ID.
 * @param Code Errors occuring during the pushing process. See ByteRtcTranscoderErrorCode{@link #ByteRtcTranscoderErrorCode}.
 * @param mixType Stream mixing and pushing type. See ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType}.
 */
 - (void)onStreamMixingEvent:(ByteRTCStreamMixingEvent)event
                  taskId:(NSString *_Nonnull)taskId
                      error:(ByteRtcTranscoderErrorCode)Code
                    mixType:(ByteRTCStreamMixingType)mixType;

@optional
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流音频 PCM 回调
 * @param audioFrame PCM 编码的合流音频数据帧，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @param timeStamp 时间戳，单位毫秒。
 * @param taskId 转推直播任务 ID。
 * @note 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Callback with audio data in PCM after intelligent stream mixing.
 * @param audioFrame Audio data frame in PCM. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @param timeStamp The timeStamp in ms.
 * @param taskId Task ID.
 * @note You will receive the callback every 10 milliseconds. Each callback carries data collected in the last 10 milliseconds.
 */
- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame timestamp:(int64_t)timeStamp taskId:(NSString *_Nonnull)taskId;

/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流视频 YUV 回调
 * @param videoFrame YUV 合流视频数据帧，参看 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}。
 * @param taskId 转推直播任务 ID。
 * @note 收到该回调的周期取决于视频的帧率。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Callback with video data in YUV after intelligent stream mixing.
 * @param videoFrame Video data frame in YUV, see ByteRTCVideoFrame{@link #ByteRTCVideoFrame}.
 * @param taskId Task ID.
 * @note The interval between callbacks is the same with that between video frames.
 */
- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame taskId:(NSString *_Nonnull)taskId;
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流视频 SEI 数据
 * @param dataFrame SEI 数据，详见 ByteRTCFrameExtendedData {@link #ByteRTCFrameExtendedData}。
 * @param taskId 转推直播任务 ID。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief This callback carries SEI data
 * @param dataFrame SEI Data. See ByteRTCFrameExtendedData{@link #ByteRTCFrameExtendedData}
 * @param taskId Task ID.
 */
- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame taskId:(NSString *_Nonnull)taskId;
/**
 * @locale zh
 * @hidden for internal use only
 * @type callback
 * @valid since 3.50
 * @brief 同步视频帧回调。仅在通过 ByteRTCTranscodingSyncControlParam{@link #ByteRTCTranscodingSyncControlParam} 设置启用单通模式，且其中 `syncClientVideoNeedMix=False` 时收到此回调。
 * @param videoFrame 同步视频帧数组，与 uids 对应。参看 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}。
 * @param dataFrame SEI 数据。参看 ByteRTCFrameExtendedData{@link #ByteRTCFrameExtendedData}。
 * @param uids 同步视频帧对应的 uid 数组。
 * @param taskID 转推直播任务 ID。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type callback
 * @valid since 3.50
 * @brief Synchronized video frame callback. Receive this callback when you enable simplex chorus mode by setting ByteRTCTranscodingSyncControlParam{@link #ByteRTCTranscodingSyncControlParam} and `syncClientVideoNeedMix=False`.
 * @param videoFrame Array of synchronized video frames. See ByteRTCVideoFrame{@link #ByteRTCVideoFrame}.
 * @param dataFrame SEI data. See ByteRTCFrameExtendedData{@link #ByteRTCFrameExtendedData}.
 * @param uids Array of uids corresponding to the video frames.
 * @param taskID Task ID.
 */
- (void)onCacheSyncVideo:(NSArray<ByteRTCVideoFrame *> *_Nonnull)videoFrames
           withDataFrame:(NSArray<ByteRTCFrameExtendedData*> *_Nonnull)dataFrames
                withUids:(NSArray<NSString*>*_Nonnull)uids
                  taskId:(NSString *_Nonnull)taskID;
@end

#pragma mark - ByteRTCPushMixedStreamToCDNObserver

/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 转推直播观察者。(Valid from 352.1)<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Register this observer to receive stream mixing related callbacks from the SDK. (Valid from 352.1)<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCMixedStreamObserver <NSObject>
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 是否具有推流能力。  <br>
 *       + false：不具备推流能力（默认值）  <br>
 *       + true：具备推流能力
 * @note  
 *         + 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Whether your App has the ability to push streams to CDN:   <br>
 *        + True: Yes  <br>
 *        + False: No (default value)
 * @note  
 *          + If you need to use the function of intelligently pushing streams to CDN, you should ensure that your App contains librtmp and has the ability to push streams out. If so, set the callback to True.
 */
 - (BOOL)isSupportClientPushStream;
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 转推直播状态回调
 * @param event 转推直播任务状态，参看 ByteRTCStreamMixingEvent{@link #ByteRTCStreamMixingEvent}。
 * @param taskId 转推直播任务 ID。
 * @param errorCode 转推直播错误码，参看 ByteRTCStreamMixingErrorCode{@link #ByteRTCStreamMixingErrorCode} 和 ByteRTCStreamMixingErrorCode{@link #ByteRTCStreamMixingErrorCode}。
 * @param mixType 转推直播类型，参看 ByteRTCMixedStreamType{@link #ByteRTCMixedStreamType}。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Used for reporting events during pushing streams to CDN
 * @param event Stream mixing and pushing status, see ByteRTCStreamMixingEvent{@link #ByteRTCStreamMixingEvent}.
 * @param taskId Task ID.
 * @param errorCode Errors occuring during the pushing process. See ByteRTCStreamMixingErrorCode{@link #ByteRTCStreamMixingErrorCode} and ByteRTCStreamMixingErrorCode{@link #ByteRTCStreamMixingErrorCode}.
 * @param mixType Stream mixing and pushing type. See ByteRTCMixedStreamType{@link #ByteRTCMixedStreamType}.
 */
 - (void)onMixingEvent:(ByteRTCStreamMixingEvent)event
                  taskId:(NSString *_Nonnull)taskId
                      error:(ByteRTCStreamMixingErrorCode)errorCode
                    mixType:(ByteRTCMixedStreamType)mixType;

@optional
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流音频 PCM 回调
 * @param audioFrame PCM 编码的合流音频数据帧，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @param timeStamp 时间戳，单位毫秒。
 * @param taskId 转推直播任务 ID。
 * @note 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Callback with audio data in PCM after intelligent stream mixing.
 * @param audioFrame Audio data frame in PCM. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @param timeStamp The timeStamp in ms.
 * @param taskId Task ID.
 * @note You will receive the callback every 10 milliseconds. Each callback carries data collected in the last 10 milliseconds.
 */
- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame timestamp:(int64_t)timeStamp taskId:(NSString *_Nonnull)taskId;

/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流视频 YUV 回调
 * @param videoFrame YUV 合流视频数据帧，参看 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}。
 * @param taskId 转推直播任务 ID。
 * @note 收到该回调的周期取决于视频的帧率。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Callback with video data in YUV after intelligent stream mixing.
 * @param videoFrame Video data frame in YUV, see ByteRTCVideoFrame{@link #ByteRTCVideoFrame}.
 * @param taskId Task ID.
 * @note The interval between callbacks is the same with that between video frames.
 */
- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame taskId:(NSString *_Nonnull)taskId;
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流视频 SEI 数据
 * @param dataFrame SEI 数据，详见 ByteRTCFrameExtendedData {@link #ByteRTCFrameExtendedData}。
 * @param taskId 转推直播任务 ID。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief This callback carries SEI data
 * @param dataFrame SEI Data. See ByteRTCFrameExtendedData{@link #ByteRTCFrameExtendedData}
 * @param taskId Task ID.
 */
- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame taskId:(NSString *_Nonnull)taskId;

/**
 * @locale zh
 * @hidden for internal use only
 * @type callback
 * @region 转推直播
 * @brief 同步视频帧回调。
 * @param videoFrame 同步视频帧数组，与 uids 对应。
 * @param dataFrame SEI 数据。
 * @param uids 同步视频帧对应的 uid 数组。
 * @param task_id 转推直播任务 ID。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type callback
 * @region Push to CDN
 * @brief Synchronized video frame callback.
 * @param videoFrame Array of synchronized video frames corresponding to uids.
 * @param dataFrame SEI data.
 * @param uids Array of synchronized video frames corresponding to uids.
 * @param task_id Task ID.
 */
- (void)onCacheSyncVideo:(NSArray<ByteRTCVideoFrame *> *_Nonnull)videoFrames withDataFrame:(NSArray<ByteRTCFrameExtendedData*> *_Nonnull)dataFrames
                 withUids:(NSArray<NSString*>*_Nonnull)uids taskId:(NSString *_Nonnull)task_id;
@end
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 单流转推直播观察者。  <br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Register this observer to receive the callbacks about pushing a single stream to CDN.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCPushSingleStreamToCDNObserver <NSObject>
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 单流转推直播状态回调
 * @param event 任务状态, 参看 ByteRTCSingleStreamPushEvent{@link #ByteRTCSingleStreamPushEvent}.
 * @param taskID 任务 ID
 * @param errorCode 错误码，参看 ByteRtcTranscoderErrorCode{@link #ByteRtcTranscoderErrorCode}。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Used for reporting events during pushing a single stream to CDN.
 * @param event Task status, see ByteRTCSingleStreamPushEvent{@link #ByteRTCSingleStreamPushEvent}.
 * @param taskID Task ID
 * @param errorCode Errors occurring during the pushing process. See ByteRtcTranscoderErrorCode{@link #ByteRtcTranscoderErrorCode}.
 */
 - (void)onStreamPushEvent:(ByteRTCSingleStreamPushEvent)event
                  taskId:(NSString *_Nonnull)taskID
                      error:(NSInteger)errorCode;

@end

/**
 * @locale zh
 * @type callback
 * @region 视频特效
 * @brief 人脸检测结果回调观察者<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @region Video Effect
 * @brief Face detection observer<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCFaceDetectionObserver <NSObject>
/**
 * @locale zh
 * @type callback
 * @region 视频特效
 * @brief 特效 SDK 进行人脸检测结果的回调。 <br>
 *        调用 enableFaceDetection:withInterval:withModelPath:{@link #ByteRTCVideoEffect#enableFaceDetection:withInterval:withModelPath:} 注册了 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver} ，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。
 * @param result 人脸检测结果, 参看 ByteRTCFaceDetectionResult{@link #ByteRTCFaceDetectionResult}。
 */
/**
 * @locale en
 * @type callback
 * @region Video Effect
 * @brief Callback of the result of face detection with Effect SDK. <br>
 *        After calling enableFaceDetection:withInterval:withModelPath:{@link #ByteRTCVideoEffect#enableFaceDetection:withInterval:withModelPath:} and using the Effect SDK integrated in the RTC SDK, you will receive this callback.
 * @param result Face detection result. See ByteRTCFaceDetectionResult{@link #ByteRTCFaceDetectionResult}.
*/
- (void)onFaceDetectResult:(ByteRTCFaceDetectionResult * _Nonnull)result;
/**
 * @locale zh
 * @hidden for intrnal use only
 * @type callback
 * @region 视频特效
 * @brief 特效 SDK 进行人像属性检测结果的回调。 <br>
 *        调用 registerFaceDetectionObserver:withInterval:{@link #ByteRTCVideoEffect#registerFaceDetectionObserver:withInterval:} 注册了 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}，并调用 setVideoEffectExpressionDetect:{@link #ByteRTCVideo#setVideoEffectExpressionDetect:} 开启人像属性检测后，你会收到此回调。
 * @param result 人像属性检测结果, 参看 ByteRTCExpressionDetectResult{@link #ByteRTCExpressionDetectResult}。
 */
/**
 * @locale en
 * @hidden for intrnal use only
 * @type callback
 * @region Video Effect
 * @brief Callback of the result of face detection with Effect SDK. <br>
 *        After calling registerFaceDetectionObserver:withInterval:{@link #ByteRTCVideoEffect#registerFaceDetectionObserver:withInterval:} and setVideoEffectExpressionDetect:{@link #ByteRTCVideo#setVideoEffectExpressionDetect:}, you will receive this callback.
 * @param result Expression detection result. See ExpressionDetectResult{@link #ExpressionDetectResult}.
*/
- (void)onExpressionDetectResult:(ByteRTCExpressionDetectResult * _Nonnull)result;
@end

#pragma mark - ByteRTCEngineMediaMetadataObserver

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.26 and will be deleted in 3.51, use sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} instead.
 * @type callback
 * @brief 使用内部源视频采集时,配置和获取附加数据接口
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51, use sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} instead.
 * @type callback
 * @brief Configure and obtain additional data interfaces when using internal source video capture
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCMediaMetadataObserver <NSObject>
@required
/**
 * @locale zh
 * @type callback
 * @region 视频数据回调
 * @brief 当 SDK 准备发送一个视频帧时，会回调该接口，以确定是否需要在该视频帧中添加 metadata
 * @param timestamp 待添加 metadata 视频帧的时间戳，单位微秒
 * @return 待发送的数据，大小不能超过 1024bytes
 * @note  
 *       + 返回 null 代表不需要添加 metadata  <br>
 *       + 回调中不能做长时间逻辑处理，以免影响视频卡顿  
 */
/**
 * @locale en
 * @type callback
 * @region Video data callback
 * @brief When the SDK is ready to send a video frame, the interface will be called back to determine whether metadata
 * @param timestamp The timestamp of the metadata video frame to be added, in microseconds
 * @return The data to be sent cannot exceed the size 1024bytes
 * @note   
 *        + Returning null means that no metadata needs to be added <br>
 *        + Long-term logical processing cannot be done in the callback to avoid affecting the video card 
 */
- (NSData *_Nullable)videoFrameMediaMetaDataAtTime:(NSTimeInterval)timestamp;

@optional
/**
 * @locale zh
 * @type callback
 * @region 视频数据回调
 * @brief 当 SDK 收到的视频帧包含 medatada 时，会回调该接口
 * @param uid 当前帧所属的用户ID
 * @param extendedData metadata
 * @param timestamp 包含 metadata 视频帧的时间戳，单位为微秒
 * @note 回调中不能做长时间逻辑处理，以免影响视频卡顿
 */
/**
 * @locale en
 * @type callback
 * @region Video data callback
 * @brief When the video frame received by the SDK contains medatada, the interface will be called back
 * @param uid The user ID to which the current frame belongs
 * @param extendedData Metadata
 * @param timestamp The timestamp containing the metadata video frame is in microseconds
 * @note Long-term logical processing cannot be done in the callback to avoid affecting the video card
 */
- (void)receiveVideoFrameFromUID:(NSString * _Nonnull)uid
    withExtendedData:(NSData* _Nullable)extendedData atTimestamp:(NSTimeInterval)timestamp;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 视频编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video encoding configuration. Refer to [Setting Video Encoder Configuration](https://docs.byteplus.com/byteplus-rtc/docs/70122) to learn more.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoEncoderConfig: NSObject
/**
 * @locale zh
 * @brief 视频宽度，单位：px
 */
/**
 * @locale en
 * @brief Width of the video frame in px
 */
@property(nonatomic, assign) NSInteger width;
/**
 * @locale zh
 * @brief 视频高度，单位：px
 */
/**
 * @locale en
 * @brief Height of the video frame in px
 */
@property(nonatomic, assign) NSInteger height;
/**
 * @locale zh
 * @brief 视频帧率，单位：fps
 */
/**
 * @locale en
 * @brief Video frame rate in fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/**
 * @locale zh
 * @brief 最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。  <br>
 *        设为 -1 即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。 <br>
 *        设为 0 则不对视频流进行编码发送。<br>
 *        344 及以上版本，内部采集时默认值为 -1，344 以前版本无默认值，需手动设置。
 */
/**
 * @locale en
 * @brief Maximum bit rate in kbps. Optional for internal capturing while mandatory for custom capturing.  <br>
 *        If you set this value to -1, SDK will automatically calculate the applicable bit rate based on the input resolution and frame rate.  <br>
 *        No stream will be encoded and published if you set this value to 0.  <br>
 *        In 344 and later versions, the default value is -1 for internal capturing, but no default value in versions earlier than 344.
 */
@property(nonatomic, assign) NSInteger maxBitrate;
/**
 * @locale zh
 * @brief 视频最小编码码率, 单位 kbps。编码码率不会低于 `minBitrate`。<br>
 *        默认值为 `0`。<br>
 *        范围：[0, maxBitrate)，当 `maxBitrate` < `minBitrate` 时，为适配码率模式。<br>
 *        以下情况，设置本参数无效：<br>
 *        + 当 `maxBitrate` 为 `0` 时，不对视频流进行编码发送。<br>
 *        + 当 `maxBitrate` < `0` 时，适配码率模式。
 */
/**
 * @locale en
 * @brief Minimum video encoding bitrate in kbps. The encoding bitrate will not be lower than the `minBitrate`.<br>
 *        It defaults to `0`. <br>
 *        It ranges within [0, maxBitrate). When `maxBitrate` < `minBitrate`, the bitrate is self-adpapted.<br>
 *        In the following circumstance, the assignment to this variable has no effect:<br>
 *        + When `maxBitrate` = `0`, the video encoding is disabled.<br>
 *        + When `maxBitrate` < `0`, the bitrate is self-adapted.
 */
@property(nonatomic, assign) NSInteger minBitrate;
/**
 * @locale zh
 * @brief 编码策略偏好，默认为帧率优先。参看 ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}。
 */
/**
 * @locale en
 * @brief Encoding preference. The default value is ByteRTCVideoEncoderPreferenceMaintainFramerate(1). See ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}.
 */
@property(nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 屏幕流编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)。
 */
/**
 * @locale en
 * @type keytype
 * @brief  The encoding configuration for shared-screen streams. See [Setting Video Encoder Configuraion](https://docs.byteplus.com/byteplus-rtc/docs/70122).
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenVideoEncoderConfig: NSObject
/**
 * @locale zh
 * @brief 屏幕帧宽度，单位：px。
 */
/**
 * @locale en
 * @brief Width(in px).
 */
@property(nonatomic, assign) NSInteger width;
/**
 * @locale zh
 * @brief 屏幕帧高度，单位：px。
 */
/**
 * @locale en
 * @brief Height(in px).
 */
@property(nonatomic, assign) NSInteger height;
/**
 * @locale zh
 * @brief 屏幕流帧率，单位：fps。
 */
/**
 * @locale en
 * @brief The frame rate(in fps).
 */
@property(nonatomic, assign) NSInteger frameRate;
/**
 * @locale zh
 * @brief 最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。<br>
 *        设为 -1 即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。<br>
 *        设为 0 则不对视频流进行编码发送。<br>
 *        3.44 及以上版本，内部采集时默认值为 -1，3.44 以前版本无默认值，需手动设置。
 */
/**
 * @locale en
 * @brief The maximum bitrate(in kbps). Optional for internal capture while mandatory for custom capture.<br>
 *        If you set this value to -1, RTC will automatically recommend the bitrate based on the input resolution and frame rate.<br>
 *        If you set this value to 0, the streams will not be encoded and published.<br>
 *        On Version 3.44 or later, the default value for internal capture is -1. On versions earlier than 3.44, you must set the maximum bit rate because there is no default value.
 */
@property(nonatomic, assign) NSInteger maxBitrate;
/**
 * @locale zh
 * @brief 最小编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。<br>
 *        最小编码码率必须小于或等于最大编码，否则不对视频流进行编码发送。
 */
/**
 * @locale en
 * @brief The minimum bitrate(in kbps).Optional for internal capture while mandatory for custom capture.<br>
 *        The minimum bitrate must be set lower than the maximum bitrate. Otherwise, the streams will not be encoded and published.
 */
@property(nonatomic, assign) NSInteger minBitrate;
/**
 * @locale zh
 * @brief 屏幕流编码模式。参见 ByteRTCScreenVideoEncoderPreference{@link #ByteRTCScreenVideoEncoderPreference}。
 */
/**
 * @locale en
 * @brief The encoding modes for shared-screen streams. See ByteRTCScreenVideoEncoderPreference{@link #ByteRTCScreenVideoEncoderPreference}.
 */
@property(nonatomic, assign) ByteRTCScreenVideoEncoderPreference encoderPreference;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 远端视频帧信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Information on remote video frame
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoConfig : NSObject
/**
 * @locale zh
 * @brief 期望订阅的最高帧率，单位：fps，默认值为 0 即满帧订阅，设为大于 0 的值时开始生效。  <br>
 *        当发布端帧率低于设定帧率，或订阅端开启性能回退后下行弱网，则帧率会相应下降。  <br>
 *        仅码流支持 SVC 分级编码特性时方可生效。
 */
/**
 * @locale en
 * @brief Expected maximum frame rate of the subscribed stream in px. The default value is 0, which represents full-frame-rate, values greater than 0 are valid.  <br>
 *        If the frame rate of the stream published is lower than the value you set, or if your subscribed stream falls back under limited network conditions, the frame rate you set will drop accordingly.  <br>
 *        Only valid if the stream is coded with SVC technique.
 */
@property (nonatomic, assign) int framerate;
/**
 * @locale zh
 * @brief 视频宽度，单位：px
 */
/**
 * @locale en
 * @brief Width of the video frame in px
 */
@property(nonatomic, assign) int  width;
/**
 * @locale zh
 * @brief 视频高度，单位：px
 */
/**
 * @locale en
 * @brief Height of the video frame in px
 */
@property(nonatomic, assign) int   height;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 房间参数配置
 */
/**
 * @locale en
 * @type keytype
 * @brief  Room configuration
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomConfig : NSObject
/**
 * @locale zh
 * @brief 房间模式，参看 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}，默认为普通音视频通话模式，进房后不可更改。
 */
/**
 * @locale en
 * @brief Room profile. See ByteRTCRoomProfile{@link #ByteRTCRoomProfile}. The default is `ByteRTCRoomProfileCommunication`. The setting cannot be changed after joining the room.
 */
@property(nonatomic) ByteRTCRoomProfile profile;
/**
 * @locale zh
 * @brief 是否自动发布音视频流，默认为自动发布。 <br>
 *        创建和加入多房间时，只能将其中一个房间设置为自动发布。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。<br>
 *        若调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。
 */
/**
* @locale en
* @brief Whether to publish media streams automatically. The default is automatic publishing.  <br>
 *       Only one of the rooms the user joined can be set to auto-publish. If no settings are made in each room, the stream is automatically published in the first room joined by default.<br>
 *       If you call setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} to set your own visibility to false, you will not publish media streams regardless of the value of `isAutoPublish`.
 */
@property(assign, nonatomic) BOOL isAutoPublish;
/**
 * @locale zh
 * @brief 是否自动订阅音频流，默认为自动订阅。<br>
 *        包含主流和屏幕流。
 */
/**
 * @locale en
 * @brief Whether to automatically subscribe to the audio stream. The default is automatic subscription.<br>
 *        This setting affects both the main stream and the screen-sharing stream.
 */
@property(assign, nonatomic) BOOL isAutoSubscribeAudio;
/**
 * @locale zh
 * @brief 是否自动订阅主视频流，默认为自动订阅。<br>
 *        包含主流和屏幕流。
 */
/**
 * @locale en
 * @brief Whether to automatically subscribe to the video stream. The default is automatic subscription.<br>
 *        This setting affects both the main stream and the screen-sharing stream.
 */
@property(assign, nonatomic) BOOL isAutoSubscribeVideo;
/**
 * @locale zh
 * @brief 远端视频流参数，参看 ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}
 */
/**
 * @locale en
 * @brief Expected configuration of remote video stream, see ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}.
 */
@property(nonatomic, strong) ByteRTCRemoteVideoConfig * _Nonnull remoteVideoConfig;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 公共流裁剪信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Crop configuration of the public stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSourceCropInfo : NSObject
/**
 * @locale zh
 * @brief 裁剪后得到的视频帧左上角横坐标相对于裁剪前整体画面的比例，取值范围[0.0, 1.0)
 */
/**
 * @locale en
 * @brief The normalized scale of the upper-left corner of the cropped video frame relative to the overall frame before cropping, in the range [0.0, 1.0)
 */
@property(assign, nonatomic) CGFloat locationX;
/**
 * @locale zh
 * @brief 裁剪后得到的视频帧左上角纵坐标相对于裁剪前整体画面的比例，取值范围[0.0, 1.0)
 */
/**
 * @locale en
 * @brief The normalized scale of the upper-left corner of the cropped video frame relative to the overall frame before cropping, in the range [0.0, 1.0)
 */
@property(assign, nonatomic) CGFloat locationY;
/**
 * @locale zh
 * @brief 裁剪后得到的视频帧宽度相对于裁剪前整体画面的比例，取值范围(0.0, 1.0]
 */
/**
 * @locale en
 * @brief The normalized ratio of the width of the video frame obtained after cropping to the overall frame before cropping, in the range (0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat widthProportion;
/**
 * @locale zh
 * @brief 裁剪后得到的视频帧高度相对于裁剪前整体画面的比例，取值范围(0.0, 1.0]
 */
/**
 * @locale en
 * @brief The normalized ratio of the height of the obtained video frame after cropping to the overall frame before cropping, in the range (0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat heightProportion;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 合成公共流的每条流的布局信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Layout of each stream to be mixed into the public stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamRegion : NSObject
/**
 * @locale zh
 * @brief 用户 ID。必填。  <br>
 * 服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。
 */
/**
 * @locale en
 * @brief User ID. Required. <br>
*         The server will identify the stream per the userId and roomId.<br>

 */
@property(copy, nonatomic) NSString * _Nonnull userId;
/**
 * @locale zh
 * @brief 房间 ID。必填。  <br>
 *        服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。
 */
/**
 * @locale en
 * @brief Room ID. Required. <br>
*         The server will identify the stream per the userId and roomId.
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/**
 * @locale zh
 * @brief 背景图片地址
 */
/**
 * @locale en
 * @brief Address of the background picture
 */
@property(copy, nonatomic) NSString * _Nonnull alternateImage;
/**
 * @locale zh
 * @brief 用户视频布局相对画布左侧的偏移量， 相对值。范围[0.0 - 1.0]
 */
/**
 * @locale en
 * @brief Offset of the user video layout relative to the left side of the canvas, relative value. Range [0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat x;
/**
 * @locale zh
 * @brief 用户视频布局相对画布顶端的偏移量， 相对值。范围[0.0 - 1.0]
 */
/**
 * @locale en
 * @brief Offset of the user video layout relative to the top of the canvas, relative value. Range [0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat y;
/**
 * @locale zh
 * @brief 用户视频宽度相对用户原始视频宽度的比例，相对值。范围[0.0 - 1.0]
 */
/**
 * @locale en
 * @brief The ratio of the user video width relative to the user's original video width, relative value. Range [0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat width;
/**
 * @locale zh
 * @brief 用户视频高度相对用户原始视频高度的比例，相对值。范围[0.0 - 1.0]
 */
/**
 * @locale en
 * @brief The ratio of the user video height relative to the user's original video height, relative value. Range [0.0 - 1.0].
 */
@property(assign, nonatomic) CGFloat height;
/**
 * @locale zh
 * @brief 用户视频布局在画布中的层级，0为底层，值越大越上层。范围[0 - 100]
 */
/**
 * @locale en
 * @brief The level of the user video layout in the canvas, 0 is the bottom level, the larger the value the higher the level. Range [0 - 100]
 */
@property(assign, nonatomic) NSInteger zOrder;
/**
 * @locale zh
 * @brief 透明度，必填。可选范围为 [0.0, 1.0]。
 */
/**
 * @locale en
 * @brief Required. Transparency, the range is [0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat alpha;
/**
 * @locale zh
 * @brief 推流内容控制。默认为0。<br>
 *      0: 输出的混流包含音视频<br>
 *      1: 只包含音频<br>
 *      2: 表示只包含视频
 */
/**
 * @locale en
 * @brief Push stream content control. Default value is 0.<br>
 *      0: The output mix contains audio and video<br>
 *      1: Audio only<br>
 *      2: Video only
 */
@property(assign, nonatomic) NSInteger mediaType;
/**
 * @locale zh
 * @brief 推流媒体类型<br>
 *        0：普通音视频流<br>
 *        1: 屏幕流
 */
/**
 * @locale en
 * @brief Media type of pushes stream<br>
 *        0：Media stream captured by camera/microphone<br>
 *        1: Screen sharing media stream
 */
@property(assign, nonatomic) NSInteger streamType;
/**
 * @locale zh
 * @brief 视频显示模式。详见 ByteRTCRenderMode{@link #ByteRTCRenderMode} 数据类型。  
 */
/**
 * @locale en
 * @brief Video rendering mode. See ByteRTCRenderMode{@link #ByteRTCRenderMode} for data types.
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/**
 * @locale zh
 * @brief 视频裁剪信息。 详见 ByteRTCSourceCropInfo{@link #ByteRTCSourceCropInfo}。
 */
/**
 * @locale en
 * @brief Video cropping information. Refer to ByteRTCSourceCropInfo{@link #ByteRTCSourceCropInfo} for details.
 */
@property(strong, nonatomic) ByteRTCSourceCropInfo * _Nonnull sourceCrop;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 公共流的合流布局。必填
 */
/**
 * @locale en
 * @type keytype
 * @brief Required. Layout of streams mixed in the public stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamLayout : NSObject
/**
 * @locale zh
 * @brief 布局模式。可选：<br>
 *        + `0`: 自动布局。默认值 <br>
 *        + `2`: 自定义布局。
 */
/**
 * @locale en
 * @brief Layout mode. The optional values: <br>
 *        + `0`: Auto layout. The default value. <br>
 *        + `2`: Custom mode.
 */
@property(assign, nonatomic) NSInteger layoutMode;
/**
 * @locale zh
 * @brief 插帧模式。<br>
 *         + `0`: 补最后一帧<br>
 *         + `1`: 补背景图片，如果没有设置背景图片则补黑帧
 */
/**
 * @locale en
 * @brief Interpolation mode<br>
 *         + `0`: Insert with the last frame<br>
 *         + `1`: Insert with the background image. RTC will insert frames of black if no background image has been set.
 */
@property(assign, nonatomic) NSInteger interpolationMode;
/**
 * @locale zh
 * @brief 画布的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色
 */
/**
 * @locale en
 * @brief Background color of the canvas,in RGB hex value. For example, #FFB6C1 represents light pink. The default value is #000000 (black).
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/**
 * @locale zh
 * @brief 背景图片地址
 */
/**
 * @locale en
 * @brief Address of the background picture
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundImage;
/**
 * @locale zh
 * @brief 用户布局信息列表。每一个该类型对象为一路单独的视频流的布局信息。
 */
/**
 * @locale en
 * @brief User layout information list.
 */
@property(copy, nonatomic) NSArray<ByteRTCPublicStreamRegion *> * _Nonnull regions;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 公共流的视频编码参数
 */
/**
 * @locale en
 * @type keytype
 * @brief Encoding properties of the public video stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamVideoConfig : NSObject
/**
 * @locale zh
 * @brief 公共流视频宽度，必填。单位为 px，范围为 [2, 1920]，必须是偶数。
 */
/**
 * @locale en
 * @brief Required. Width of the video frame. Unit: px. Range: [16, 1920], even value is effective.
 */
@property(assign, nonatomic) NSInteger width;
/**
 * @locale zh
 * @brief 公共流视频高度，必填。单位为 px，范围为 [16, 1280]，必须是偶数。
 */
/**
 * @locale en
 * @brief Required. Width of the video frame. Unit: px. Range: [16, 1280], even value is effective.
 */
@property(assign, nonatomic) NSInteger height;
/**
 * @locale zh
 * @brief 公共流视频帧率。必填<br>
 *        范围：[1, 60] 
 */
/**
 * @locale en
 * @brief Required. Frame rate in fps<br>
 *        Range: [1, 60]
 */
@property(assign, nonatomic) NSInteger fps;
/**
 * @locale zh
 * @brief 视频码率，必填<br>
 *        范围：[1,10000000]<br>
 *        单位为 bps
 */
/**
 * @locale en
 * @brief Required. Bitrate in bps <br>
 *          Range: [1,10000000]
 */
@property(assign, nonatomic) NSInteger bitrate;
@end

/**
 * @locale zh
 * @hidden currently not available
 * @type keytype
 * @brief 公共流的音频编码参数
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Encoding properties of the public audio stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamAudioConfig : NSObject
/**
 * @locale zh
 * @brief 音频采样率，必填。单位为 Hz。可选取值：16000, 32000, 44100 和 48000
 */
/**
 * @locale en
 * @brief Required. Audio sample rate in Hz. Options: 16000, 32000, 44100, or 48000
 */
@property(assign, nonatomic) NSInteger sampleRate;
/**
 * @locale zh
 * @brief 音频声道数，必填。<br>
 * + 1: 单声道<br>
 * + 2: 双声道
 */
/**
 * @locale en
 * @brief Required. Number of the audio channels. <br>
 * + 1: Mono<br>
 * + 2: Dual
 */
@property(assign, nonatomic) NSInteger channels;
/**
 * @locale zh
 * @brief 音频码率，必填。单位为 kbps。<br>
 * 正整数，可选取值：16, 32, 64。
 */
/**
 * @locale en
 * @brief Required. Audio bitrate in kbps.<br>
 * Positive integer in kbps. Options: 16, 32, or 64
 */
@property(assign, nonatomic) NSInteger bitrate;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 水印图片相对视频流的位置和大小。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Watermark's scaled coordinates and size, relative to the video stream.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoByteWatermark: NSObject
/**
 * @locale zh
 * @brief 水印图片相对视频流左上角的横向偏移与视频流宽度的比值，取值范围为 [0,1)。
 */
/**
 * @locale en
 * @brief The watermark's horizontal offset from the upper left corner of the video stream to the video stream's width in range of [0,1).
 */
@property(assign, nonatomic) float x;
/**
 * @locale zh
 * @brief 水印图片相对视频流左上角的纵向偏移与视频流高度的比值，取值范围为 [0,1)。
 */
/**
 * @locale en
 * @brief The watermark's vertical offset from the upper left corner of the video stream to the video stream's height in range of [0,1).
 */
@property(assign, nonatomic) float y;
/**
 * @locale zh
 * @brief 水印图片宽度与视频流宽度的比值，取值范围 [0,1)。
 */
/**
 * @locale en
 * @brief The watermark's width to the video stream's width in range of [0,1).
 */
@property(assign, nonatomic) float width;
/**
 * @locale zh
 * @brief 水印图片高度与视频流高度的比值，取值范围为 [0,1)。
 */
/**
 * @locale en
 * @brief The watermark height to the video stream's height in range of [0,1).
 */
@property(assign, nonatomic) float height;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 水印参数
 */
/**
 * @locale en
 * @type keytype
 * @brief  Watermark configurations
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoWatermarkConfig: NSObject
/**
 * @locale zh
 * @brief 水印是否在视频预览中可见，默认可见。
 */
/**
 * @locale en
 * @brief Whether the watermark is visible in preview. Its default value is `true`.
 */
@property(nonatomic, assign) BOOL visibleInPreview;
/**
 * @locale zh
 * @brief 横屏时的水印位置和大小，参看 ByteRTCVideoByteWatermark{@link #ByteRTCVideoByteWatermark}。
 */
/**
 * @locale en
 * @brief Watermark's coordinates and size in landscape mode. See ByteRTCVideoByteWatermark{@link #ByteRTCVideoByteWatermark}.
 */
@property(strong, nonatomic) ByteRTCVideoByteWatermark * _Nonnull positionInLandscapeMode;
/**
 * @locale zh
 * @brief 竖屏时的水印位置和大小，参看 ByteRTCVideoByteWatermark{@link #ByteRTCVideoByteWatermark}。
 */
/**
 * @locale en
 * @brief Watermark's coordinates and size in portrait mode. See ByteRTCVideoByteWatermark{@link #ByteRTCVideoByteWatermark}.
 */
@property(strong, nonatomic) ByteRTCVideoByteWatermark * _Nonnull positionInPortraitMode;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 公共流参数
 */
/**
 * @locale en
 * @type keytype
 * @brief Properties of the public stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreaming : NSObject
/**
 * @locale zh
 * @brief 视频流公共流整体布局参数，必填。详见 ByteRTCPublicStreamLayout{@link #ByteRTCPublicStreamLayout}
 */
/**
 * @locale en
 * @brief Required. Layout configuration of the public stream. Refer to ByteRTCPublicStreamLayout{@link #ByteRTCPublicStreamLayout} for details.
 */
@property(strong, nonatomic) ByteRTCPublicStreamLayout * _Nonnull layout;
/**
 * @locale zh
 * @brief 公共流视频编码参数。详见 ByteRTCPublicStreamVideoConfig{@link #ByteRTCPublicStreamVideoConfig}。
 */
/**
 * @locale en
 * @brief Encoding properties of the public video stream. Refer to ByteRTCPublicStreamVideoConfig{@link #ByteRTCPublicStreamVideoConfig} for details.
 */
@property(strong, nonatomic) ByteRTCPublicStreamVideoConfig * _Nonnull video;
/**
 * @locale zh
 * @hidden currently not available
 * @brief 公共流音频编码参数。详见 ByteRTCPublicStreamAudioConfig{@link #ByteRTCPublicStreamAudioConfig}
 */
/**
 * @locale en
 * @hidden currently not available
 * @brief Encoding properties of the public audio stream. Refer to ByteRTCPublicStreamAudioConfig{@link #ByteRTCPublicStreamAudioConfig} for details.
 */
@property(strong, nonatomic) ByteRTCPublicStreamAudioConfig * _Nonnull audio;
/**
 * @locale zh
 * @hidden currently not available
 * @brief 设置媒体流所在房间的房间 ID。服务端将通过用户 ID 和 房间 ID，找到需要合成到公共流中的媒体流。必填。
 */
/**
 * @locale en
 * @hidden currently not available
 * @brief Required. The server will identify the stream per the userId and roomId.
 */
@property(copy, nonatomic) NSString * _Nullable roomId;
/**
 * @locale zh
 * @brief 获取默认的公共流转码配置属性。
 * @return 包含默认配置的 ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming} 结构体
 */
/**
 * @locale en
 * @brief Get the default setting of a public stream.
 * @return ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming} struct with default values.
 */
+ (instancetype _Nonnull)defaultPublicStreaming;
@end
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 视频设备管理
 * @brief 主要用于枚举、设置视频采集设备
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region Video Device Management
 * @brief Mainly used to enumerate and set up video capture devices
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoDeviceManager : NSObject
/**
 * @locale zh
 * @type api
 * @region 视频设备管理
 * @brief 获取视频采集设备列表。
 * @return 包含系统中所有视频采集设备的列表，参看 ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}。<br>
 * 等待超时后会返回空列表。超时时间默认为 10 s。建议通过 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 监听到 `ByteRTCMediaDeviceListUpdated` 后，再次调用本接口获取。
 * @note 你可以在收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 了解设备变更后，重新调用本接口以获得新的设备列表。
 */
/**
 * @locale en
 * @type api
 * @region  Video Device Management
 * @brief  Get the list of video capture devices.
 * @return Contains a list of all video capture devices in the system. See ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}. <br>
 * If a time-out occurs, it returns an empty list. By default, the time-out duration is set to 10 seconds. We recommend to call this API once you get notification of `ByteRTCMediaDeviceListUpdated` via rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:}.
 * @note When receiving rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} for device change, you can call this API to get the latest list of audio playback devices.
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateVideoCaptureDevices;
/**
 * @locale zh
 * @type api
 * @region 视频设备管理
 * @brief 获取当前 SDK 正在使用的视频采集设备信息
 * @param deviceID 视频设备 ID
 * @return  
 *        + 0：方法调用成功  <br>
 *        + !0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Video Device Management
 * @brief Get the currently-using video capture device
 * @param  deviceID video device ID
 * @return   
 *         + 0: Success. <br>
 *         +! 0: failure 
 */
- (int)getVideoCaptureDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/**
 * @locale zh
 * @type api
 * @region 视频设备管理
 * @brief 设置当前视频采集设备
 * @param deviceID 视频设备 ID。调用 enumerateVideoCaptureDevices{@link #ByteRTCVideoDeviceManager#enumerateVideoCaptureDevices} 获取全量视频设备。
 * @return  
 *        + 0：方法调用成功  <br>
 *        + !0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region  Video Device Management
 * @brief  Set the current video capture device
 * @param  deviceID Video device ID. Get all video devices by calling  which can be obtained through enumerateVideoCaptureDevices{@link #ByteRTCVideoDeviceManager#enumerateVideoCaptureDevices}
 * @return   
 *         + 0: Success. <br>
 *         +! 0: failure 
 */
- (int)setVideoCaptureDevice:(NSString* _Nonnull)deviceID;
@end
/**
 * @locale zh
 * @type callback
 * @brief 截取视频画面回调类<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief  Screenshot-taking callback class.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSnapshotCallbackDelegate <NSObject>
@required
/**
 * @locale zh
 * @type callback
 * @brief 调用 takeLocalSnapshot:callback:{@link #ByteRTCVideo#takeLocalSnapshot:callback:} 截取视频画面时，收到此回调。
 * @param taskId 本地截图任务的编号。和 takeLocalSnapshot:callback:{@link #ByteRTCVideo#takeLocalSnapshot:callback:} 的返回值一致。
 * @param streamIndex 截图的视频流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param image 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。
 * @param errorCode 截图错误码：<br>
 *        + 0: 成功 <br>
 *        + -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br>
 *        + -2: 截图错误。流无效。<br>
 *        + -3: 截图错误。截图超时,超时时间1秒。
 */
/**
 * @locale en
 * @type callback
 * @brief Receives the callback after calling takeLocalSnapshot:callback:{@link #ByteRTCVideo#takeLocalSnapshot:callback:}.
 * @param taskId The index for the snapshot, the same as the return value of takeLocalSnapshot:callback:{@link #ByteRTCVideo#takeLocalSnapshot:callback:}.
 * @param streamIndex See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param image The snapshot image. If the snapshot task fails, the value is `null`.
 * @param errorCode Error code: <br>
 *        + 0: Success. <br>
 *        + -1: Failure. Fails to generate the image. <br>
 *        + -2: Failure. The stream is invalid.<br>
 *        + -3: Failure. snapshot timeout, default 1s.
 */
- (void)onTakeLocalSnapshotResult:(NSInteger) taskId
                      streamIndex:(ByteRTCStreamIndex)streamIndex
                            image:(ByteRTCImage * _Nullable)image
                        errorCode:(NSInteger)errorCode;
/**
 * @locale zh
 * @type callback
 * @brief 调用 takeRemoteSnapshot:callback:{@link #ByteRTCVideo#takeRemoteSnapshot:callback:} 截取视频画面时，收到此回调。
 * @param taskId 远端截图任务的编号。和 takeRemoteSnapshot:callback:{@link #ByteRTCVideo#takeRemoteSnapshot:callback:} 的返回值一致。
 * @param streamKey 截图的视频流，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param image 截图。你可以保存为文件，或对其进行二次处理。截图失败时，为空。
 * @param errorCode 截图错误码：<br>
 *        + 0: 成功 <br>
 *        + -1: 截图错误。生成图片数据失败或 RGBA 编码失败 <br>
 *        + -2: 截图错误。流无效。<br>
 *        + -3: 截图错误。截图超时,超时时间1秒。
 */
/**
 * @locale en
 * @type callback
 * @brief Receives the callback after calling takeRemoteSnapshot:callback:{@link #ByteRTCVideo#takeRemoteSnapshot:callback:}.
 * @param taskId The index for the remote snapshot, the same as the return value of takeRemoteSnapshot:callback:{@link #ByteRTCVideo#takeRemoteSnapshot:callback:}.
 * @param streamKey See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param image The snapshot image. If the snapshot task fails, the value is `null`.
 * @param errorCode Error code: <br>
 *        + 0: Success. <br>
 *        + -1: Failure. Fails to generate the image. <br>
 *        + -2: Failure. The stream is invalid.<br>
 *        + -3: Failure. snapshot timeout, default 1s.
 */
- (void)onTakeRemoteSnapshotResult:(NSInteger)taskId
                         streamKey:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                             image:(ByteRTCImage * _Nullable)image
                         errorCode:(NSInteger)errorCode;
@end

/**
 * @locale zh
 * @type api
 * @region 音视频处理
 * @brief 高级视频特效，参看[集成指南](https://www.volcengine.com/docs/6348/114717)。
 */
/**
 * @locale en
 * @type api
 * @region Audio & Video Processing
 * @brief Advanced video effects. See [integration guide](https://docs.byteplus.com/byteplus-rtc/docs/114717).
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoEffect : NSObject

/**
 * @locale zh
 * @hidden for internal use only
 * @type api
 * @brief 设置视频特效算法模型地址，并初始化特效模块。
 * @param finder ResourceFinder 地址
 * @param deleter ResourceDeleter 地址
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type api
 * @brief  Sets the video effects resource finder path and initializes video effects.
 * @param finder ResourceFinder path
 * @param deleter ResourceDeleter path
 * @return  
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 */
- (int) setAlgoModelResourceFinder:(void*_Nonnull)finder deleter:(void*_Nonnull)deteter;

#if BYTERTC_TARGET_MAC
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 视频特效
 * @brief 从特效 SDK 获取授权消息，用于获取在线许可证。
 * @param ppmsg 授权消息字符串地址
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 
 *        + 使用视频特效的功能前，你必须获取特效 SDK 的在线许可证。  <br>
 *        + 通过此接口获取授权消息后，参考 [在线授权说明](https://www.volcengine.com/docs/6705/102012)，自行实现获取在线许可证的业务逻辑。获取许可证后，你必须调用 initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} 确认许可证有效。然后，你才可以使用 CV 功能。  
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region Video Effects
 * @brief Get authorization messages from the Effect SDK for the online license.
 * @param ppmsg Authorization message string address
 * @return   
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table) for specific instructions.
 * @note  
 *         + You must get an online license for the Effect SDK before using the CV functions. <br>
 *         + After getting authorization messages with this API, implement the code of getting the online license with [Online License Guide](https://docs.byteplus.com/en/effects/docs/windows-license-guide). Then call initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} to validate the license. After that, you can use the CV function. 
 */
- (int)getAuthMessage:(NSString *_Nullable*_Nullable)ppmsg;
#endif

/**
 * @locale zh
 * @type api
 * @brief 检查视频特效证书，设置算法模型路径，并初始化特效模块。
 * @param licenseFile 证书文件的绝对路径，用于鉴权。
 * @param algoModelDir 算法模型绝对路径，即存放特效 SDK 所有算法模型的目录。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @type api
 * @brief Checks video effect license, sets the video effect resource model path, and initializes video effect.
 * @param licenseFile The absolute path of the license file for authorization.
 * @param algoModelDir The absolute path of the Effects SDK's models file.
 * @return  
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 */
- (int) initCVResource:(NSString* _Nonnull)licenseFile
            withAlgoModelDir: (NSString* _Nonnull)algoModelDir;

/**
 * @locale zh
 * @type api
 * @brief 开启高级美颜、滤镜等视频特效。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note  
 *      + 调用本方法前，必须先调用 initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} 进行初始化。<br>
 *      + 调用该方法后，特效不直接生效，你还需调用 setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} 设置视频特效素材包或调用 setColorFilter:{@link #ByteRTCVideoEffect#setColorFilter:} 设置滤镜。<br>
 *      + 调用 disableVideoEffect{@link #ByteRTCVideoEffect#disableVideoEffect} 关闭视频特效。
 */
/**
 * @locale en
 * @type api
 * @brief Enables video effects including beauty and color filters.
 * @return  
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 * @note  
 *      + You must call initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} before calling this API.<br>
 *      + This API does not turn on video effects directly, you must call setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} or setColorFilter:{@link #ByteRTCVideoEffect#setColorFilter:} next.<br>
 *      + Call disableVideoEffect{@link #ByteRTCVideoEffect#disableVideoEffect} to turn off video effects.
 */
- (int) enableVideoEffect;

/**
 * @locale zh
 * @type api
 * @brief 关闭视频特效。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 调用 enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} 开启视频特效。
 */
/**
 * @locale en
 * @type api
 * @brief Disables video effects.
 * @return  
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 * @note Call enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} to enable video effects.
 */
- (int) disableVideoEffect;

/**
 * @locale zh
 * @hidden for internal use only
 * @type api
 * @region 视频特效
 * @brief 返回视频特效句柄。私有接口。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type api
 * @region Video Effects
 * @brief Return video effect handle. Private method
 */
- (void* _Nullable)getVideoEffectHandle;

/**
 * @locale zh
 * @hidden for internal use only
 * @type api
 * @region 视频特效
 * @brief 私有接口<br>
 * 设置视频特效素材包
 * @param stickerPath 特效素材包绝对路径。<br>
 *        要取消当前视频特效，将此参数设置为 null。
 * @return  
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 * @note 在调用这个方法之前，你须先调用 enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:} 。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type api
 * @region Video Effects
 * @brief Private method<br>
 * Set video effects material package.
 * @param stickerPath effect material package path. <br>
 *        To remove the current video effect, set it to null.
 * @return   
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 * @note Before calling this method, you must first call enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:}.
 */
- (int) applyStickerEffect:(NSString* _Nullable)stickerPath;

/**
 * @locale zh
 * @type api
 * @brief 设置视频特效素材包。
 * @param effectNodes 特效素材包绝对路径数组。<br>
 *        要取消当前视频特效，将此参数设置为 null。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 调用本方法前，必须先调用 enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect}。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the video effects material package.
 * @param effectNodes Array of effect material package paths. <br>
 *        To remove the current video effect, set it to null.
 * @return   
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 * @note You must call enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} before calling this API.
 */
- (int) setEffectNodes:(NSArray<NSString*>*_Nonnull)effectNodes;

/**
 * @locale zh
 * @hidden for internal use only
 * @type api
 * @brief  叠加视频特效素材包。
 * @param effectNodes 特效素材包路径数组。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 该接口会在 setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} 设置的特效基础上叠加特效。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type api
 * @brief  Appends video effects material package.
 * @param effectNodes Array of effect material package paths.
 * @return  
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 * @note This API adds new video effect to the video effect you set with setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:}.
 */
- (int) appendEffectNodes:(NSArray<NSString*>*_Nonnull)effectNodes;

/**
 * @locale zh
 * @hidden for internal use only
 * @type api
 * @brief  移除指定的视频特效资源。
 * @param effectNodes 特效素材包路径数组。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 移除 setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} 或 appendEffectNodes:{@link #ByteRTCVideoEffect#appendEffectNodes:} 设置的视频特效资源。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type api
 * @brief  Removes the designated video effects material package.
 * @param effectNodes Array of effect material package paths.
 * @return  
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 * @note Removes the designated video effects in setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} or appendEffectNodes:{@link #ByteRTCVideoEffect#appendEffectNodes:}.
 */
- (int) removeEffectNodes:(NSArray<NSString*>*_Nonnull)effectNodes;

/**
 * @locale zh
 * @type api
 * @brief 设置特效强度。
 * @param node 特效素材包绝对路径，参考[素材包结构说明](https://www.volcengine.com/docs/6705/102039)。
 * @param key 需要设置的素材 key 名称，参考[素材 key 对应说明](https://www.volcengine.com/docs/6705/102041)。
 * @param value 特效强度值，取值范围 [0,1]，超出范围时设置无效。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the intensity of video effects.
 * @param node The absolute path of the effects resource package, see [Resource Package Structure](https://docs.byteplus.com/effects/docs/resource-package-structure-v421-and-later).
 * @param key The name of the material key to be set, see [Functions of Resource Keys](https://docs.byteplus.com/effects/docs/functions-of-resource-keys-v421-and-later) for the value.
 * @param value The intensity value that needs to be set, the value range [0,1], and the setting is invalid when it exceeds the range.
 * @return   
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 */
- (int) updateEffectNode:(NSString* _Nonnull)node
                key:(NSString* _Nonnull)key value:(float) value;

/**
 * @locale zh
 * @type api
 * @brief 设置颜色滤镜。
 * @param filterRes 滤镜资源包绝对路径。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 调用 setColorFilterIntensity:{@link #ByteRTCVideoEffect#setColorFilterIntensity:} 设置已启用颜色滤镜的强度。设置强度为 0 时即关闭颜色滤镜。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the color filter.
 * @param filterRes Filter effects package absolute path.
 * @return   
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 * @note Call setColorFilterIntensity:{@link #ByteRTCVideoEffect#setColorFilterIntensity:} to set the intensity of the color filter enabled. Set the intensity to 0 to turn off color filter.
 */
- (int) setColorFilter:(NSString* _Nonnull)filterRes;

/**
 * @locale zh
 * @type api
 * @brief 设置已启用颜色滤镜的强度。
 * @param intensity 滤镜强度。取值范围 [0,1]，超出范围时设置无效。<br>
 *                  当设置滤镜强度为 0 时即关闭颜色滤镜。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the intensity of the color filter enabled.
 * @param intensity Filter intensity. The value range [0,1] is set to be invalid when the range is exceeded.<br>
 *                  Set the intensity to 0 to turn off color filter.
 * @return   
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 */
- (int) setColorFilterIntensity:(float) intensity;

/**
 * @locale zh
 * @type api
 * @brief 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
 * @param backgroundStickerPath 背景贴纸特效素材绝对路径。
 * @param source 背景贴纸对象，参看 ByteRTCVirtualBackgroundSource{@link #ByteRTCVirtualBackgroundSource}。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 
 *      + 调用本方法前，必须先调用 initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} 进行初始化。<br>
 *      + 调用 disableVirtualBackground{@link #ByteRTCVideoEffect#disableVirtualBackground} 关闭虚拟背景。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the original background to a specified image or a solid color.
 * @param backgroundStickerPath The absolute path of virtual background effects.
 * @param source Virtual background source. See ByteRTCVirtualBackgroundSource{@link #ByteRTCVirtualBackgroundSource}.
 * @return  
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 * @note 
 *      + You must call initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} before calling this API.<br>
 *      + Call disableVirtualBackground{@link #ByteRTCVideoEffect#disableVirtualBackground} to turn off the virtual background.
 */
- (int) enableVirtualBackground:(NSString* _Nonnull)backgroundStickerPath
                withSource:(ByteRTCVirtualBackgroundSource* _Nonnull)source;

/**
 * @locale zh
 * @type api
 * @brief 关闭虚拟背景。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 调用 enableVirtualBackground:withSource:{@link #ByteRTCVideoEffect#enableVirtualBackground:withSource:} 开启虚拟背景后，可以调用此接口关闭虚拟背景。
 */
/**
 * @locale en
 * @type api
 * @brief Turns off the virtual background.
 * @return   
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 * @note After calling enableVirtualBackground:withSource:{@link #ByteRTCVideoEffect#enableVirtualBackground:withSource:} to enable the virtual background function, you can call this API to turn it off.
 */
- (int) disableVirtualBackground;

/**
 * @locale zh
 * @hidden for internal use only
 * @type api
 * @brief 开启人像属性检测。
 * @param config 人像属性检测参数，参看 ByteRTCExpressionDetectConfig{@link #ByteRTCExpressionDetectConfig}。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type api
 * @brief  Sets the configuration for video effects expression detection.
 * @param config Expression detection configuration. See ByteRTCExpressionDetectConfig{@link #ByteRTCExpressionDetectConfig}.
 * @return  
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 */
- (int) setVideoEffectExpressionDetect:(ByteRTCExpressionDetectConfig* _Nonnull)config;

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use enableFaceDetection:withInterval:withModelPath:{@link #ByteRTCVideoEffect#enableFaceDetection:withInterval:withModelPath:} and disableFaceDetection{@link #ByteRTCVideoEffect#disableFaceDetection} instead.
 * @type api
 * @brief 注册人脸检测结果回调观察者。<br>
 *        注册此观察者后，你会周期性收到 onFaceDetectResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectResult:} 回调。
 * @param observer 人脸检测结果回调观察者，参看 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}。
 * @param interval 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval+视频采集帧间隔`。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use enableFaceDetection:withInterval:withModelPath:{@link #ByteRTCVideoEffect#enableFaceDetection:withInterval:withModelPath:} and disableFaceDetection{@link #ByteRTCVideoEffect#disableFaceDetection} instead.
 * @type api
 * @brief  Register the observer for the result of face detection.<br>
 *        With this observer, you will receive onFaceDetectResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectResult:} periodically.
 * @param observer See ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}.
 * @param interval Time interval in ms. The value should be greater than 0. The actual time interval of receiving callbacks is between `interval` and `interval+the time slot of a captured video frame`.
 * @return 
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 */
- (int) registerFaceDetectionObserver:(_Nullable id<ByteRTCFaceDetectionObserver>) observer
                withInterval:(NSInteger)interval __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @type api
 * @brief 开启人脸识别功能，并设置人脸检测结果回调观察者。<br>
 *        此观察者后，你会周期性收到 onFaceDetectResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectResult:} 回调。
 * @param observer 人脸检测结果回调观察者，参看 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}。
 * @param interval 两次回调之间的最小时间间隔，必须大于 0，单位为毫秒。实际收到回调的时间间隔大于 interval，小于 interval+视频采集帧间隔。
 * @param path 人脸检测算法模型文件路径，一般为 ttfacemodel 文件夹中 tt_face_vXXX.model 文件的绝对路径。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + -1004: 初始化中，初始化完成后启动此功能。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @type api
 * @brief Starts face detection and registers the observer for the result.<br>
 *        With this observer, you will receive onFaceDetectResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectResult:} periodically.
 * @param observer See ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}.
 * @param interval The minimum time interval between two callbacks in milliseconds. The value should be greater than 0. The actual time interval is between interval and interval+the time slot of a captured video frame.
 * @param path The absolute path of the face detection algorithm file. Typically it is the tt_face_vXXX.model file in the ttfacemodel folder.
 * @return 
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + -1004: Initializing. This function will be available when the initialization is completed.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 */
- (int) enableFaceDetection:(_Nullable id<ByteRTCFaceDetectionObserver>) observer
               withInterval:(NSUInteger)interval
              withModelPath:(NSString* _Nonnull)path;

/**
 * @locale zh
 * @type api
 * @brief 关闭人脸识别功能。
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 */
/**
 * @locale en
 * @type api
 * @brief Stops face detection.
 * @return 
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
 */
- (int) disableFaceDetection;
@end


/**
 * @locale zh
 * @type keytype
 * @brief RTC 智能决策后得到的帧率和分辨率积（宽*高）。
 */
/**
 * @locale en
 * @type keytype
 * @brief  The recommended pixel and framerate by RTC.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFrameUpdateInfo : NSObject
/**
 * @locale zh
 * @brief 分辨率积（宽*高）。
 */
/**
 * @locale en
 * @brief Pixel (width * height).
 */
@property(assign, nonatomic) int pixel;
/**
 * @locale zh
 * @brief 帧率。
 */
/**
 * @locale en
 * @brief The frame rate.
 */
@property(assign, nonatomic) int framerate;
@end
/**
 * @locale zh
 * @hidden(macOS)
 * @type keytype
 * @brief 蜂窝网络辅助增强应用的媒体模式
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type keytype
 * @brief Media type for cellular assisted Enhancement
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMediaTypeEnhancementConfig: NSObject
/**
 * @locale zh
 * @brief 对信令消息，是否启用蜂窝网络辅助增强。默认不启用。
 */
/**
 * @locale en
 * @brief Apply to signaling or not. Not by default.
 */
@property (assign, nonatomic) BOOL enhanceSignaling;
/**
 * @locale zh
 * @brief 对屏幕共享以外的其他音频，是否启用蜂窝网络辅助增强。默认不启用。
 */
/**
 * @locale en
 * @brief Apply to audio stream (Screen-sharing audio not included) or not. Not by default.
 */
@property (assign, nonatomic) BOOL enhanceAudio;
/**
 * @locale zh
 * @brief 对屏幕共享视频以外的其他视频，是否启用蜂窝网络辅助增强。默认不启用。
 */
/**
 * @locale en
 * @brief Apply to video (Screen-sharing video not included) or not. Not by default.
 */
@property (assign, nonatomic) BOOL enhanceVideo;
/**
 * @locale zh
 * @brief 对屏幕共享音频，是否启用蜂窝网络辅助增强。默认不启用。
 */
/**
 * @locale en
 * @brief Apply to screen sharing audio or not. Not by default.
 */
@property (assign, nonatomic) BOOL enhanceScreenAudio;
/**
 * @locale zh
 * @brief 对屏幕共享视频，是否启用蜂窝网络辅助增强。默认不启用。
 */
/**
 * @locale en
 * @brief Apply to screen sharing video or not. Not by default.
 */
@property (assign, nonatomic) BOOL enhanceScreenVideo;
@end

/**
* @locale zh
* @hidden internal use only
* @type keytype
* @brief 缓存同步模式。
*/
/**
* @locale en
* @hidden internal use only
* @type keytype
*/
typedef NS_ENUM(NSUInteger, ByteRTCChorusCacheSyncMode) {
    /**
     * @locale zh
     * @brief 合唱场景下，主唱应采用此模式，以发送带时间戳信息的媒体数据。
     */
    /**
     * @locale en
     * @brief Under chorus scenarios, the lead singer uses the mode to send the media data with timestamp attached.
     */
    ByteRTCChorusCacheSyncModeProducer= 0,
    /**
     * @locale zh
     * @brief 合唱场景下，副唱应采用此模式。<br>
     *        此模式下，副唱收到来自主唱的带时间戳的媒体数据。副唱发送的媒体数据中带有来自主唱的时间戳。
     */
    /**
     * @locale en
     * @brief Under chorus scenarios, the sub singer uses the mode.<br>
     *        In this mode, the sub singer receives the media data from the lead singer with timestamp attached. The sub singer sends the media data with the lead singer's timestamp attached.
     */
    ByteRTCChorusCacheSyncModeRetransmitter= 1,
    /**
     * @locale zh
     * @brief 合唱场景下，听众应采用此模式。<br>
     *        此模式下，听众收到来自主唱的时间戳，并据此对齐来自主唱和副唱的媒体数据，以获得良好的合唱播放效果。
     */
    /**
     * @locale en
     * @brief Under chorus scenarios, the audience uses the mode.<br>
     *        In this mode, the audience receives the lead singer's timestamp. The audience aligns and renders the media data from lead and sub singers, and gets good chorus experience.
     */
    ByteRTCChorusCacheSyncModeConsumer = 2
};

/**
 * @locale zh
 * @type keytype
 * @hidden for internal use
 * @brief 合唱缓存同步事件。
 */
/**
 * @locale en
 * @type keytype
 * @hidden for internal use
 * @brief Chorus cache synchronization event.
 */
typedef NS_ENUM(NSUInteger, ByteRTCChorusCacheSyncEvent) {
    /**
    * @locale zh
    * @brief 成功。
    */
   /**
    * @locale en
    * @brief Success.
    */
    ByteRTCChorusCacheSyncEventStartSuccess = 0,
    /**
    * @locale zh
    * @brief 失败。
    */
   /**
    * @locale en
    * @brief Failed.
    */
    ByteRTCChorusCacheSyncEventStartFailed = 1,
};

/**
 * @locale zh
 * @hidden for internal use only
 * @type errorcode
 * @brief 缓存同步错误码。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type errorcode
 * @brief Chorus cache synchronization error.
 */  
typedef NS_ENUM(NSUInteger, ByteRTCChorusCacheSyncError) {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief OK
     */
    ByteRTCChorusCacheSyncErrorOK = 0,
    /**
     * @locale zh
     * @brief 失败。推送至 CDN 时，应进行以下设置：<br>
     *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.enable_sync = true`；<br>
     *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.base_user_id = {uid of producer}`。
     */
    /**
     * @locale en
     * @type Failure. Check if the config of pushing mixed streams to CDN is as follows:<br>
     *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.enable_sync = true`；<br>
     *        + `IMixedStreamConfig.MixedStreamSyncControlConfig.base_user_id = {uid of producer}`。
     */
    ByteRTCChorusCacheSyncErrorWrongState = 1,
    /**
     * @locale zh
     * @brief 缓存同步功能已启动，不需要重复开启。
     */
    /**
     * @locale en
     * @type Already running. Do not enable the feature repeatedly.
     */
    ByteRTCChorusCacheSyncErrorAlreadyRunning = 2
};

/**
 * @locale zh
 * @hidden for internal use only
 * @type keytype
 * @brief 缓存同步配置。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type keytype
 * @brief Chorus cache synchronization configuration.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCChorusCacheSyncConfig: NSObject
/**
 * @locale zh
 * @brief 最大媒体缓存时长（ms）。<br>
 *        取值范围是 `[500, 2500]`，默认值是 `2000`。<br>
 *        值越大，同步效果越好，但会造成占用内存较大。如果参与缓存同步的各路媒体流之间的时间差超过此值，会造成丢帧。
 */
/**
 * @locale en
 * @brief Maximum duration of media data cached in ms.<br>
 *        `2000` by default. The range is `[500, 2500]`. <br>
 *        Use higher value for better syncing effect. If the time difference between media streams in cache synchronization exceeds this value, frame loss will occur.
 */
@property(assign, nonatomic) int maxCacheTimeMs;
/**
 * @locale zh
 * @brief 模式。参看 ByteRTCChorusCacheSyncMode{@link #ByteRTCChorusCacheSyncMode}. 默认值是 `retransmitter`。  
 */
/**
 * @locale en
 * @brief Mode. See ByteRTCChorusCacheSyncMode{@link #ByteRTCChorusCacheSyncMode}. `retransmitter` by default.
 */
@property (assign, nonatomic) ByteRTCChorusCacheSyncMode mode;
/**
 * @locale zh
 * @brief 收到 onSyncedVideoFrames:withUids:{@link #ByteRTCChorusCacheSyncObserver#onSyncedVideoFrames:withUids:} 的频率。<br>
 *        默认值是 `15`。此值通常应小于等于原始视频帧率；如果大于原始视频帧率，可能会收到重复帧。
 */
/**
 * @locale en
 * @brief The frequency of receiving onSyncedVideoFrames:withUids:{@link #ByteRTCChorusCacheSyncObserver#onSyncedVideoFrames:withUids:}.<br>
 *        `15` by default. The value is smaller than that of the original video fps usually; if the value is bagger than that, you may receive duplicated video frame.
 */
@property(assign, nonatomic) int videoFps;
@end

/**
 * @locale zh
 * @hidden for internal use only
 * @type callback
 * @brief 缓存同步 Observer
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type callback
 * @brief Chorus cache synchronization observer.
 */
@protocol ByteRTCChorusCacheSyncObserver <NSObject>
/**
 * @locale zh
 * @type callback
 * @brief 调用 startChorusCacheSync:observer:{@link #ByteRTCVideo#startChorusCacheSync:observer:}，并设置为 `consumer` 的用户会通过此回调获取经缓存同步后的视频帧。获取频率通过启动同步时的 `fps` 进行设置。
 * @param videoFrames 对应 `uids` 的视频帧。参看 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}。
 * @param uids 参与合唱缓存同步的 `producer` 和 `retransmitter` 的列表，不包括参与但未发送媒体数据的用户。
 */
/**
 * @locale en
 * @type callback
 * @brief The user who calls startChorusCacheSync{@link #RTCVideo#startChorusCacheSync} as `consumer` receives the callback with synced video frames. The interval of receiving the callback is set by `fps`.
 * @param count length of `uids`
 * @param uids The list of participants as `producer` and `retransmitter`. The participants not sending media data are excluded.
 * @param videoFrames Video data frame corresponding to `uids`. See ByteRTCVideoFrame{@link #ByteRTCVideoFrame}.
 */
- (void)onSyncedVideoFrames:(NSArray<ByteRTCVideoFrame*>*)videoFrames withUids:(NSArray<NSString*>*)uids;
/**
 * @locale zh
 * @type callback
 * @brief 参与合唱缓存同步的 `producer` 和 `retransmitter` 发生变化时，收到此回调。
 * @param uids  当前的参与者列表
 * @note 有以下情况可能造成参与者发生变化：<br>
 *        + 用户主动调用 startChorusCacheSync:observer:{@link #ByteRTCVideo#startChorusCacheSync:observer:} 或 stopChorusCacheSync{@link #ByteRTCVideo#stopChorusCacheSync};<br>
 *        + 原本参与缓存同步的用户发生异常退出。
 */
/**
 * @locale en
 * @type callback
 * @brief Receives the callback when the `producer` or `retransmitter` changes.
 * @param uids Current list of the participants
 * @note You may receive the callback is the following cases:<br>
 *        + The user calls startChorusCacheSync:observer:{@link #ByteRTCVideo#startChorusCacheSync:observer:} or stopChorusCacheSync{@link #ByteRTCVideo#stopChorusCacheSync};<br>
 *        + The cache syncing participant quits abnormally. 
 */
- (void)onSyncedUsersChanged:(NSArray<NSString*>*)uids;
/**
 * @locale zh
 * @type callback
 * @brief 缓存同步事件回调
 * @param event 事件，参看 ByteRTCChorusCacheSyncEvent{@link #ByteRTCChorusCacheSyncEvent}。
 * @param error 错误码，参看 ByteRTCChorusCacheSyncError{@link #ByteRTCChorusCacheSyncError}。
 */
/**
 * @locale en
 * @type callback
 * @brief Chorus cache sync event callback
 * @param event See ByteRTCChorusCacheSyncEvent{@link #ByteRTCChorusCacheSyncEvent}.
 * @param error See ByteRTCChorusCacheSyncError{@link #ByteRTCChorusCacheSyncError}.
 */
- (void)onSyncEvent:(ByteRTCChorusCacheSyncEvent)event withError:(ByteRTCChorusCacheSyncError)error;
@end
