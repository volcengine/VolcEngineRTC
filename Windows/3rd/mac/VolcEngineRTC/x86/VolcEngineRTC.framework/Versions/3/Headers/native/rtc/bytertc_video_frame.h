/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Video Frame
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <memory>
#include <cstring>
#include "bytertc_media_defines.h"
#ifdef BYTERTC_ANDROID
#include <jni.h>
#endif

namespace bytertc {

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
enum VideoPictureType {
    /**
     * @locale zh
     * @brief 未知类型
     */
    /**
     * @locale en
     * @brief Unknown type
     */
    kVideoPictureTypeUnknown = 0,
    /**
     * @locale zh
     * @brief I帧，关键帧，编解码不需要参考其他视频帧
     */
    /**
     * @locale en
     * @brief I-frames, key frames which are coded without reference to any other frame.
     */
    kVideoPictureTypeI,
    /**
     * @locale zh
     * @brief P帧，向前参考帧，编解码需要参考前一帧视频帧
     */
    /**
     * @locale en
     * @brief P-frames, forward-predicted frames which are coded by a forward predictive coding method.
     */
    kVideoPictureTypeP,
    /**
     * @locale zh
     * @brief B帧，前后参考帧，编解码需要参考前后两帧视频帧
     */
    /**
     * @locale en
     * @brief  B-frames, bi-directionally predicted frames which are coded by both forward and backward predictive coding method.
     */
    kVideoPictureTypeB
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
enum VideoRotation {
    /**
     * @locale zh
     * @brief 不旋转
    */
   /**
     * @locale en
     * @brief Not to rotate.
    */
    kVideoRotation0 = 0,
    /**
     * @locale zh
     * @brief 顺时针旋转 90 度
    */
   /**
     * @locale en
     * @brief Rotate 90 degrees clockwise.
    */
    kVideoRotation90 = 90,
    /**
     * @locale zh
     * @brief 顺时针旋转 180 度
    */
   /**
     * @locale en
     * @brief Rotate 180 degrees clockwise.
    */
    kVideoRotation180 = 180,
    /**
     * @locale zh
     * @brief 顺时针旋转 270 度
    */
   /**
     * @locale en
     * @brief Rotate 270 degrees clockwise.
    */
    kVideoRotation270 = 270
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧缩放模式，默认值为 FitWithCropping。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video frame scale mode
 */
enum VideoStreamScaleMode {
    /**
     * @locale zh
     * @brief 自动模式
     */
    /**
     * @locale en
     * @brief Auto mode, default to FitWithCropping.
     */
    kVideoStreamScaleModeAuto = 0,
    /**
     * @locale zh
     * @brief 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。
     */
    /**
     * @locale en
     * @brief Stretch the video frame until the video frame and the window have the same resolution. The video frame's aspect ratio can be changed as it is automatically stretched to fill the window, but the whole image is visible.
     */
    kVideoStreamScaleModeStretch = 1,
    /**
     * @locale zh
     * @brief 视窗填满优先。<br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    /**
     * @locale en
     * @brief  Fit the window with cropping <br>
     *         Scale the video frame uniformly until the window is filled. If the video frame's aspect ratio is different from that of the window, the extra part of the video frame will be cropped. <br>
     *         After the scaling process is completed, the width or height of the video frame will be consistent with that of the window, and the other dimension will be greater than or equal to that of the window.
     */
    kVideoStreamScaleModeFitWithCropping = 2,
    /**
     * @locale zh
     * @brief 视频帧内容全部显示优先。<br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
     */
    /**
     * @locale en
     * @brief  Fit the window with filling <br>
     *         Scale the video frame uniformly until its width or height reaches the boundary of the window. If the video frame's aspect ratio is different from that of the window, the area that is not filled will be black. <br>
     *         After the scaling process is completed, the width or height of the video frame will be consistent with that of the window, and the other dimension will be less than or equal to that of the window.
     */
    kVideoStreamScaleModeFitWithFilling = 3,
};


/**
 * @locale zh
 * @type keytype
 * @brief 视频编码模式
 */
/**
 * @locale en
 * @type keytype
 * @brief  Video encoding mode
 */
enum VideoCodecMode {
    /**
     * @locale zh
     * @brief 自动选择
     */
    /**
     * @locale en
     * @brief Automatic selection
     */
    kVideoCodecModeAuto = 0,
    /**
     * @locale zh
     * @brief 硬编码
     */
    /**
     * @locale en
     * @brief Hardcoding
     */
    kVideoCodecModeHardware,
    /**
     * @locale zh
     * @brief 软编码
     */
    /**
     * @locale en
     * @brief Softcoding
     */
    kVideoCodecModeSoftware,
};

/**
 * @locale zh
 * @type keytype
 * @brief 编码策略偏好。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Encoder preference.
 */
enum VideoEncodePreference {
    /**
     * @locale zh
     * @brief 无偏好。不降低帧率和分辨率。
     */
    /**
     * @locale en
     * @brief No preference. The frame rate and the resolution will not be adjusted.
     */
    kVideoEncodePreferenceDisabled = 0,
    /**
     * @locale zh
     * @brief （默认值）帧率优先。分辨率不变。
     */
    /**
     * @locale en
     * @brief (Default) Frame rate first. The resolution will not be changed.
     */
    kVideoEncodePreferenceFramerate,
    /**
     * @locale zh
     * @brief 分辨率优先。
     */
    /**
     * @locale en
     * @brief Resolution first.
     */
    kVideoEncodePreferenceQuality,
    /**
     * @locale zh
     * @brief 平衡帧率与分辨率。
     */
    /**
     * @locale en
     * @brief Balancing resolution and frame rate.
     */
    kVideoEncodePreferenceBalance,
};

/**
 * @locale zh
 * @type keytype
 * @brief 摄像头。
 */
/**
 * @locale en
 * @type keytype
 * @brief  camera.
 */
enum CameraID {
    /**
     * @locale zh
     *@brief 移动端前置摄像头，PC端内置摄像头
     */
    /**
     * @locale en
     *@brief Front-facing camera for mobile, build-in camera for PC
     */
    kCameraIDFront = 0,
    /**
     * @locale zh
     *@brief 移动端后置摄像头，PC端无定义
     */
    /**
     * @locale en
     *@brief Postconditioning camera for mobile, PC is undefined for camera 1
     */
    kCameraIDBack = 1,
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
    kCameraIDExternal = 2,
    /**
     * @locale zh
     *@brief 无效值
     */
    /**
     * @locale en
     *@brief Invalid value
     */
    kCameraIDInvalid = 3
};


#define SEND_KBPS_AUTO_CALCULATE -1
#define SEND_KBPS_DISABLE_VIDEO_SEND 0

/**
 * @locale zh
 * @deprecated since 3.36 along with setVideoEncoderConfig(StreamIndex index, const VideoSolution* solutions, int solution_num) = 0;
 * @type keytype
 * @brief 视频流参数
 */
/**
 * @locale en
 * @deprecated since 3.45 along with setVideoEncoderConfig(StreamIndex index, const VideoSolution* solutions, int solution_num) = 0;
 * @type keytype
 * @brief Video stream parameters
 */
struct VideoSolution {
    /**
     * @locale zh
     * @brief 视频宽度，单位：像素
     */
    /**
     * @locale en
     * @brief Width (pixels)
     */
    int width;
    /**
     * @locale zh
     * @brief 视频高度，单位：像素
     */
    /**
     * @locale en
     * @brief Height (pixels)
     */
    int height;
    /**
     * @locale zh
     * @brief 视频帧率
     */
    /**
     * @locale en
     * @brief Video frame rate
     */
    int fps;
    /**
     * @locale zh
     * @brief 最大发送编码码率（kbps），建议使用默认的自动码率。<li>-1: 自动码率</li><li>0: 不开启上限</li><li>>0: 填写预估码率<li>
     */
    /**
     * @locale en
     * @brief Set maximum bitrate in kbps <br>
     *        We recommend the default setting: `SEND_KBPS_AUTO_CALCULATE(-1)`<br>
     *        `SEND_KBPS_DISABLE_VIDEO_SEND(0)` for no limitation for the sending bitrate
     */
    int max_send_kbps = SEND_KBPS_AUTO_CALCULATE;
    int min_send_kbps = 0;
    /**
     * @locale zh
     * @brief 视频编码质量策略，参看 VideoEncodePreference{@link #VideoEncodePreference}
     */
    /**
     * @locale en
     * @brief ncoder preference. See VideoEncodePreference{@link #VideoEncodePreference}.
     */
    VideoEncodePreference encode_preference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
};

/**
 * @locale zh
 * @hidden for internal use only on Windows and Android
 * @type keytype
 * @brief 视野范围（Fov）内的视频帧信息<br>
 *        Tile 是 全景视频的基本单位。<br>
 *        视野范围内的视频又分为高清视野和低清背景，均包含了多个 Tile。<br>
 *        视频帧信息为发送端使用 `setVideoEncoderConfig(const VideoEncoderConfig& encoderConfig, const char* parameters)` 接口进行设置。
 */
/**
 * @locale en
 * @hidden for internal use only on Windows and Android
 * @type keytype
 * @brief Information of video frames within the FoV (Field of View). <br>
 *        Tile is the unit of a video within Fov.<br>
 *        A video within Fov includes HD view and LD background each of which consists of multiple Tiles.<br>
 *        The information of the video frames within the Fov is set by calling `setVideoEncoderConfig(const VideoEncoderConfig& encoderConfig, const char* parameters)` on the sender side.
 */
struct FovVideoTileInfo {
    /**
     * @locale zh
     * @brief 高清视野宽度
     */
    /**
     * @locale en
     * @brief Width of the HD view.
     */
    uint32_t hd_width = 0;
    /**
     * @locale zh
     * @brief 高清视野高度
     */
    /**
     * @locale en
     * @brief Height of the HD view
     */
    uint32_t hd_height = 0;
    /**
     * @locale zh
     * @brief 低清背景宽度
     */
    /**
     * @locale en
     * @brief Width of the LD background
     */
    uint32_t ld_width = 0;
    /**
     * @locale zh
     * @brief 低清背景高度
     */
    /**
     * @locale en
     * @brief Height of the LD background
     */
    uint32_t ld_height = 0;
    /**
     * @locale zh
     * @brief Tile 宽度
     */
    /**
     * @locale en
     * @brief Width of a Tile
     */
    uint32_t tile_width = 0;
    /**
     * @locale zh
     * @brief Tile 高度
     */
    /**
     * @locale en
     * @brief Height of a Tile
     */
    uint32_t tile_height = 0;
    /**
     * @locale zh
     * @brief 高清视野中的 Tile 行数
     */
    /**
     * @locale en
     * @brief Number of Tile rows in the HD view
     */
    uint32_t hd_row = 0;
    /**
     * @locale zh
     * @brief 高清视野中的 Tile 列数
     */
    /**
     * @locale en
     * @brief Number of Tile columns in the HD view
     */
    uint32_t hd_column = 0;
    /**
     * @locale zh
     * @brief 低清背景中的 Tile 行数
     */
    /**
     * @locale en
     * @brief Number of Tile rows in the LD background
     */
    uint32_t ld_row = 0;
    /**
     * @locale zh
     * @brief 低清背景中的 Tile 列数
     */
    /**
     * @locale en
     * @brief Number of Tile columns in the LD background
     */
    uint32_t ld_column = 0;
    /**
     * @locale zh
     * @brief 视野范围中的 Tile 行数
     */
    /**
     * @locale en
     * @brief Number of tile rows within the FoV
     */
    uint32_t dest_row = 0;
    /**
     * @locale zh
     * @brief 视野范围中的 Tile 列数
     */
    /**
     * @locale en
     * @brief Number of tile columns within the FoV
     */
    uint32_t dest_column = 0;
    /**
     * @locale zh
     * @brief Tile 位置映射表
     */
    /**
     * @locale en
     * @brief Position map of the Tiles
     */
    uint8_t* tile_map = nullptr;
    /**
     * @locale zh
     * @brief Tile 数量
     */
    /**
     * @locale en
     * @brief Number of the Tiles
     */
    uint32_t tile_size = 0;
};
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
struct VideoEncoderConfig {
    /**
     * @locale zh
     * @brief 视频宽度，单位：像素
     */
    /**
     * @locale en
     * @brief Width of the video frame in px
     */
    int width;
    /**
     * @locale zh
     * @brief 视频高度，单位：像素
     */
    /**
     * @locale en
     * @brief Height of the video frame in px
     */
    int height;
    /**
     * @locale zh
     * @brief 视频帧率，单位：fps
     */
    /**
     * @locale en
     * @brief Video frame rate in fps
     */
    int frame_rate;
    /**
     * @locale zh
     * @brief 最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。  <br>
     *        内部采集模式下默认值为 -1，即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。 <br>
     *        设为 0 则不对视频流进行编码发送。
     */
    /**
     * @locale en
     * @brief Maximum bit rate in kbps. Optional for internal capturing while mandatory for custom capturing.  <br>
     *        The default value is -1 in internal capturing mode, SDK will automatically calculate the applicable bit rate based on the input resolution and frame rate.  <br>
     *        No stream will be encoded and published if you set this parameter to 0.
     */
    int max_bitrate = SEND_KBPS_AUTO_CALCULATE;
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
     *         In the following circumstance, the assignment to this variable has no effect:<br>
     *        + When `maxBitrate` = `0`, the video encoding is disabled.<br>
     *        + When `maxBitrate` < `0`, the bitrate is self-adapted.
     */
    int min_bitrate = 0;
    /**
     * @locale zh
     * @brief 编码策略偏好，默认为帧率优先。参看 VideoEncodePreference{@link #VideoEncodePreference}。
     */
    /**
     * @locale en
     * @brief Encoding preference. The default value is kVideoEncodePreferenceFramerate. See VideoEncodePreference{@link #VideoEncodePreference}.
     */
    VideoEncodePreference encoder_preference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
};

/**
 * @locale zh
 * @deprecated since 3.36 along with onUserUnPublishStream and onUserUnPublishScreen, and will be deleted in 3.51.
 * @type keytype
 * @brief 视频属性
 */
/**
 * @locale en
 * @deprecated since 3.45 along with onUserUnPublishStream and onUserUnPublishScreen, and will be deleted in 3.51.
 * @type keytype
 * @brief Video attribute
 */
struct VideoSolutionDescription {
    /**
     * @locale zh
     * @brief 宽（像素）<br>
     *        默认值为 `1920` <br>
     *        为 `0` 时，保持源的宽。
     */
    /**
     * @locale en
     * @brief Width in pixels <br>
     *        The default value is `1920`<br>
     *        `0` for remaining the width of the source.
     */
    int width;
    /**
     * @locale zh
     * @brief 高（像素）<br>
     *        默认值为 `1080` <br>
     *        为 `0` 时，保持源的高。
     */
    /**
     * @locale en
     * @brief High in pixels <br>
     *        The default value is `1080`<br>
     *        `0` for remaining the height of the source.
     */
    int height;
    /**
     * @locale zh
     * @brief 视频帧率(fps)，默认为 15 fps
     */
    /**
     * @locale en
     * @brief Video frame rate in fps. The default value is 15 fps.
     */
    int fps;
    /**
     * @locale zh
     * @brief 最大发送速率（千比特每秒）。<br>
     *        默认为 `-1`，适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率
     */
    /**
     * @locale en
     * @brief Maximum transmission rate in Kbps<br>
     *        The default value is `-1`, Adaptive mode in which RTC will set the bitrate to a value which is calculated according to the target resolution and the frame rate.
     */
    int max_send_kbps;
    int min_send_kbps;
    /**
     * @locale zh
     * @brief 缩放模式。参看 VideoStreamScaleMode{@link #VideoStreamScaleMode}
     */
    /**
     * @locale en
     * @brief Zoom mode. See VideoStreamScaleMode{@link #VideoStreamScaleMode}
     */
    VideoStreamScaleMode scale_mode = VideoStreamScaleMode::kVideoStreamScaleModeAuto;
    /**
     * @locale zh
     * @brief 视频的编码类型。参看 VideoCodecType{@link #VideoCodecType}
     */
    /**
     * @locale en
     * @brief The encoding type of the video. See VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType codec_name = VideoCodecType::kVideoCodecTypeUnknown;
    /**
     * @locale zh
     * @brief 视频的编码模式。参看 VideoCodecMode{@link #VideoCodecMode}
     */
    /**
     * @locale en
     * @brief The encoding mode of the video. See VideoCodecMode{@link #VideoCodecMode}
     */
    VideoCodecMode codec_mode = VideoCodecMode::kVideoCodecModeAuto;
    /**
     * @locale zh
     * @brief 视频编码质量偏好策略。参看 VideoEncodePreference{@link #VideoEncodePreference}
     */
    /**
     * @locale en
     * @brief Video coding quality preference strategy. See VideoEncodePreference{@link #VideoEncodePreference}
     */
    VideoEncodePreference encode_preference = VideoEncodePreference::kVideoEncodePreferenceFramerate;

    /**
     * @hidden constructor/destructor
     */
    bool operator==(const VideoSolutionDescription& config) const {
        bool result = width == config.width && height == config.height && fps == config.fps
                             && max_send_kbps == config.max_send_kbps && min_send_kbps == config.min_send_kbps
                             && scale_mode == config.scale_mode && codec_name == config.codec_name
                             && codec_mode == config.codec_mode && encode_preference == config.encode_preference;
        return result;
    }

    /**
     * @hidden constructor/destructor
     */
    bool operator!=(const VideoSolutionDescription& config) const {
        bool result = (*this == config);
        return !result;
    }
};


/**
 * @locale zh
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @region 视频管理
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @region video management
 */
typedef VideoSolutionDescription VideoProfile;

/**
 * @locale zh
 * @type keytype
 * @brief 视频帧颜色编码格式
 */
/**
 * @locale en
 * @type keytype
 * @brief Encoding format for video frame color
 */
enum VideoPixelFormat {
    /**
     * @locale zh
     * @brief 未知的颜色编码格式
     */
    /**
     * @locale en
     * @brief Unknown format
     */
    kVideoPixelFormatUnknown = 0,
    /**
     * @locale zh
     * @brief YUV I420 格式
     */
    /**
     * @locale en
     * @brief YUV I420
     */
    kVideoPixelFormatI420,
    /**
     * @locale zh
     * @brief YUV NV12 格式
     */
    /**
     * @locale en
     * @brief YUV NV12
     */
    kVideoPixelFormatNV12,
    /**
     * @locale zh
     * @brief YUV NV21 格式
     */
    /**
     * @locale en
     * @brief YUV NV21
     */
    kVideoPixelFormatNV21,
    /**
     * @locale zh
     * @brief RGB 24bit格式，
     */
    /**
     * @locale en
     * @brief RGB 24bit
     */
    kVideoPixelFormatRGB24,
    /**
     * @locale zh
     * @brief RGBA 编码格式
     */
    /**
     * @locale en
     * @brief RGBA
     */
    kVideoPixelFormatRGBA,
    /**
     * @locale zh
     * @brief ARGB 编码格式
     */
    /**
     * @locale en
     * @brief ARGB
     */
    kVideoPixelFormatARGB,
    /**
     * @locale zh
     * @brief BGRA 编码格式
     */
    /**
     * @locale en
     * @brief BGRA
     */
    kVideoPixelFormatBGRA,
    /**
     * @locale zh
     * @brief Texture2D格式
     */
    /**
     * @locale en
     * @brief Texture2D
     */
    kVideoPixelFormatTexture2D = 0x0DE1,
    /**
     * @locale zh
     * @brief TextureOES格式
     */
    /**
     * @locale en
     * @brief TextureOES
     */
    kVideoPixelFormatTextureOES = 0x8D65,
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
enum VideoContentType {
    /**
     * @locale zh
     * @brief 普通视频
     */
    /**
     * @locale en
     * @brief Normal video
     */
    kVideoContentTypeNormalFrame = 0,
    /**
     * @locale zh
     * @brief 黑帧视频
     */
    /**
     * @locale en
     * @brief Black frame video
     */
    kVideoContentTypeBlackFrame,
};

/**
 * @locale zh
 * @type keytype
 * @region 视频管理
 * @brief 视频YUV格式颜色空间
 */
/**
 * @locale en
 * @type keytype
 * @region  video management
 * @brief  Video YUV format color space
 */
enum ColorSpace {
    /**
     * @locale zh<br>
     * 未知的颜色空间，默认使用kColorSpaceYCbCrBT601LimitedRange颜色空间
     */
    /**
     * @locale en<br>
     * Unknown color space, default kColorSpaceYCbCrBT601LimitedRange color space
     */
    kColorSpaceUnknown = 0,
    /**
     * @locale zh
     * @brief BT.601数字编码标准，颜色空间[16-235]
     */
    /**
     * @locale en
     * @brief BT.601 Digital Coding Standard, Color Space [16-235]
     */
    kColorSpaceYCbCrBT601LimitedRange,
    /**
     * @locale zh
     *  @brief BT.601数字编码标准，颜色空间[0-255]
     */
    /**
     * @locale en
     *  @brief BT.601 Digital Coding Standard, Color Space [0-255]
     */
    kColorSpaceYCbCrBT601FullRange,
    /**
     * @locale zh
     * @brief BT.7091数字编码标准，颜色空间[16-235]
     */
    /**
     * @locale en
     * @brief BT.7091 Digital Coding Standard, Color Space [16-235]
     */
    kColorSpaceYCbCrBT709LimitedRange,
    /**
     * @locale zh
     * @brief BT.7091数字编码标准，颜色空间[0-255]
     */
    /**
     * @locale en
     * @brief BT.7091 Digital Coding Standard, Color Space [0-255]
     */
    kColorSpaceYCbCrBT709FullRange,
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
enum VideoFrameType {
    /**
     * @locale zh
     * @brief 原始数据格式，按照内存存储
     */
    /**
     * @locale en
     * @brief Original format, stored as memory
     */
    kVideoFrameTypeRawMemory,
    /**
     * @locale zh
     * @brief CVPixelBufferRef类型，支持 iOS and macOS 平台
     */
    /**
     * @locale en
     * @brief CVPixelBufferRef (for iOS and macOS)
     */
    kVideoFrameTypeCVPixelBuffer,
    /**
     * @locale zh
     * @brief open gl 纹理数据类型
     */
    /**
     * @locale en
     * @brief Open gl texture
     */
    kVideoFrameTypeGLTexture,
    /**
     * @locale zh
     * @brief cuda 数据类型
     */
    /**
     * @locale en
     * @brief Cuda
     */
    kVideoFrameTypeCuda,
    /**
     * @locale zh
     * @brief direct3d 11 数据格式
     */
    /**
     * @locale en
     * @brief Direct3d 11
     */
    kVideoFrameTypeD3D11,
    /**
     * @locale zh
     * @brief direct3d 9 数据格式
     */
    /**
     * @locale en
     * @brief Direct3d 9
     */
    kVideoFrameTypeD3D9,
    /**
     * @locale zh
     * @brief Java的VideoFrame 数据格式
     */
    /**
     * @locale en
     * @brief VideoFrame used in Java
     */
    kVideoFrameTypeJavaFrame,
    /**
     * @locale zh
     * @brief vaapi 数据格式
     */
    /**
     * @locale en
     * @brief Vaapi
     */
    kVideoFrameTypeVAAPI,
	/**
     * @locale zh
     * @hidden(Windows)
     * @brief nvidia jetson dma 数据格式
     */
    /**
     * @locale en
     * @hidden(Windows)
     * @brief nvidia jetson dma
     */
    kVideoFrameTypeNvidiaJetsonDma,
};

/**
 * @locale zh
 * @type keytype
 * @brief 自定义内存释放器
 */
/**
 * @locale en
 * @type keytype
 * @brief  Custom Memory Release
 */
struct ManagedMemory {
    /**
     * @locale zh
     * @deprecated since 3.21 and will be deleted in 3.51.
     * @brief 内存数据数据类型，默认为 cpu 内存，详见 VideoFrameType:{@link #VideoFrameType}
     * @note 该字段不可用，目前只有 cpu 内存
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51.
     * @brief Memory data data type, the default is cpu memory. See VideoFrameType:{@link #VideoFrameType}
     * @note Not available any more and will be removed soon.
     */
    VideoFrameType type = kVideoFrameTypeRawMemory;
    /**
     * @locale zh
     * @brief 内存数据地址
     */
    /**
     * @locale en
     * @brief Memory data address
     */
    uint8_t* data = nullptr;
    /**
     * @locale zh
     * @brief 内存空间的大小
     */
    /**
     * @locale en
     * @brief Size of memory space
     */
    int size = 0;
    /**
     * @locale zh
     * @brief 用户自定义数据
     */
    /**
     * @locale en
     * @brief User-defined data
     */
    void* user_opaque = nullptr;
    /**
     * @locale zh
     * @brief 自定义内存释放方法指针，如果指针不为空，方法会被调用，用来释放内存空间。<br>
     *        函数传入的参数分别是本结构体内 data、size、user_opaque 3个字段。
     */
    /**
     * @locale en
     * @brief Custom memory free method pointer, if the pointer is not empty, the method will be called to free memory space. The parameters passed in by the<br>
     *         Function are data, size, user_opaque 3 fields in this structure.
     */
    int (*memory_deleter)(uint8_t* data, int size, void* user_opaque) = nullptr;
};

/**
 * @locale zh
 * @type keytype
 * @region 视频管理
 * @brief 视频帧构建类
 */
/**
 * @locale en
 * @type keytype
 * @region Video Management
 * @brief Video frame construction object
 */
typedef struct VideoFrameBuilder {
#define ByteRTCNumDataPointers 4
    /**
     * @locale zh
     * @brief 内存数据数据类型，默认为 cpu 内存，详见 VideoFrameType{@link #VideoFrameType}
     */
    /**
     * @locale en
     * @brief Memory data type, the default value is cpu memory. See VideoFrameType{@link #VideoFrameType}
     */
    VideoFrameType frame_type = kVideoFrameTypeRawMemory;
    /**
     * @locale zh
     * @brief 视频帧像素格式，详见 VideoPixelFormat{@link #VideoPixelFormat}
     */
    /**
     * @locale en
     * @brief Video frame pixel format. See VideoPixelFormat{@link #VideoPixelFormat}
     */
    VideoPixelFormat pixel_fmt = kVideoPixelFormatUnknown;
    /**
     * @locale zh
     * @brief 视频帧颜色空间，参看 ColorSpace{@link #ColorSpace}
     */
    /**
     * @locale en
     * @brief Video frame color space, see ColorSpace{@link #ColorSpace}
     */
    ColorSpace color_space = kColorSpaceUnknown;
    /**
     * @locale zh
     * @brief 视频帧数据平面指针数组
     */
    /**
     * @locale en
     * @brief Array of video frame data plane pointer
     */
    uint8_t* data[ByteRTCNumDataPointers] = { 0 };
    /**
     * @locale zh
     * @brief 视频帧数据平面行长度
     */
    /**
     * @locale en
     * @brief Line length of video frame data plane
     */
    int linesize[ByteRTCNumDataPointers] = { 0 };
    /**
     * @locale zh
     * @brief SEI 数据地址
     */
    /**
     * @locale en
     * @brief SEI data address
     */
    uint8_t* extra_data = nullptr;
    /**
     * @locale zh
     * @brief SEI 数据大小
     */
    /**
     * @locale en
     * @brief SEI data size
     */
    int extra_data_size = 0;
    /**
     * @locale zh
     * @brief 补充数据地址
     */
    /**
     * @locale en
     * @brief Address of supplementary data
     */
    uint8_t* supplementary_info = nullptr;
    /**
     * @locale zh
     * @brief 补充数据大小
     */
    /**
     * @locale en
     * @brief Size of supplementary data
     */
    int supplementary_info_size = 0;
    /**
     * @locale zh
     * @brief 视频帧内存空间大小
     */
    /**
     * @locale en
     * @brief Video frame memory space size
     */
    int size = 0;
    /**
     * @locale zh
     * @brief 视频帧宽度
     */
    /**
     * @locale en
     * @brief Video frame width
     */
    int width = 0;
    /**
     * @locale zh
     * @brief 视频帧高度
     */
    /**
     * @locale en
     * @brief Video frame height
     */
    int height = 0;
    /**
     * @locale zh
     * @brief 视频旋转角度，参看 VideoRotation{@link #VideoRotation}。<br>
     *        当视频接收端使用 RTC SDK 内部渲染时，引擎会根据设定的 rotation 处理旋转角度后再行渲染；<br>
     *        当视频接收端使用自定义渲染时，此处设置的 rotation 无效，可以通过 IVideoFrame::rotation() 接口获取 rotation 信息。
     */
    /**
     * @locale en
     * @brief Video rotation angle, see VideoRotation{@link #VideoRotation}.<br>
     *        If the video is rendered on the receiver side using internal rendering of the SDK, the engine processes the rotation angle according to the rotation set here before rendering.<br>
     *        If the video receiver uses custom rendering, the rotation set here does not take effect. The rotation information can be get from IVideoFrame::rotation().
     */
    VideoRotation rotation = kVideoRotation0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 镜像参数
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Mirror parameter
     */
    bool flip = false;
    /**
     * @locale zh
     * @brief 硬件加速缓冲区指针
     */
    /**
     * @locale en
     * @brief Hardware acceleration buffer pointer
     */
    void* hwaccel_buffer = nullptr;
    /**
     * @locale zh
     * @brief 用户私有数据指针
     */
    /**
     * @locale en
     * @brief Private data pointer
     */
    void* user_opaque = nullptr;
    /**
     * @locale zh
     * @brief 视频帧时间戳
     */
    /**
     * @locale en
     * @brief Video frame timestamp
     */
    int64_t timestamp_us = 0;
    /**
    * @locale zh
    * @brief 硬件加速Context对象(AKA Opengl Context, Vulkan Context)
    */
    /**
     * @locale en
     * @brief Hardware accelerate context(AKA Opengl Context, Vulkan Context)
     */
    void* hwaccel_context = nullptr;
#ifdef __ANDROID__
    /**
     * @locale zh
     * @brief 硬件加速Context的Java对象(Only for Android, AKA Opengl Context)
     */
    /**
     * @locale en
     * @brief Hardware accelerate context's java object(Only for Android, AKA Opengl Context)
     */
    jobject android_hwaccel_context = nullptr;
#endif
    /**
     * @locale zh
     * @brief 纹理矩阵(仅针对纹理类型的frame生效)
     */
    /**
     * @locale en
     * @brief Texture matrix (only for texture type frame)
     */
    float tex_matrix[16] = { };
    /**
     * @locale zh
     * @brief 纹理ID(仅针对纹理类型的frame生效)
     */
    /**
     * @locale en
     * @brief Texture ID (only for texture type frame)
     */
    uint32_t texture_id = 0;
    /**
     * @locale zh
     * @brief 用户定义的视频帧释放回调函数指针，如果指针不为空，方法会被调用用来释放内存空间
     */
    /**
     * @locale en
     * @brief User-defined pointer used for release the memory space, if the pointer is not empty.
     */
    int (*memory_deleter)(struct VideoFrameBuilder* builder) = nullptr;
} VideoFrameBuilder;

/**
 * @locale zh
 * @type keytype
 * @brief 设置视频帧
 */
/**
 * @locale en
 * @type keytype
 * @brief Sets the video frame
 */
class IVideoFrame {
public:
    /**
     * @locale zh
     * @brief 获取视频帧类型，参看 VideoFrameType{@link #VideoFrameType}
     */
    /**
     * @locale en
     * @brief Gets video frame type, see VideoFrameType{@link #VideoFrameType}
     */
    virtual VideoFrameType frameType() const = 0;
    /**
     * @locale zh
     * @brief 获取视频帧格式，参看 VideoPixelFormat{@link #VideoPixelFormat}
     */
    /**
     * @locale en
     * @brief Gets video frame format, see VideoPixelFormat{@link #VideoPixelFormat}
     */
    virtual VideoPixelFormat pixelFormat() const = 0;
    /**
     * @locale zh
     * @brief 获取视频内容类型，参看 VideoContentType{@link #VideoContentType}。
     */
    /**
     * @locale en
     * @brief Gets video content type, see VideoContentType{@link #VideoContentType}.
     */
    virtual VideoContentType videoContentType() const = 0;

    /**
     * @locale zh
     * @brief 获取视频帧时间戳，单位：微秒
     */
    /**
     * @locale en
     * @brief Gets video frame timestamp in microseconds
     */
    virtual int64_t timestampUs() const = 0;
    /**
     * @locale zh
     * @brief 获取视频帧宽度，单位：px
     */
    /**
     * @locale en
     * @brief Gets video frame width in px
     */
    virtual int width() const = 0;
    /**
     * @locale zh
     * @brief 获取视频帧高度，单位：px
     */
    /**
     * @locale en
     * @brief Gets video frame height in px
     */
    virtual int height() const = 0;
    /**
     * @locale zh
     * @brief 获取视频帧旋转角度，参看 VideoRotation{@link #VideoRotation}
     */
    /**
     * @locale en
     * @brief Gets the video frame rotation angle, see VideoRotation{@link #VideoRotation}
     */
    virtual VideoRotation rotation() const = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 获取镜像信息
     * @return 是否需要镜像<br>
     *        + True: 是  <br>
     *        + False: 否
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Gets mirror information
     * @return Is there a need to mirror the video:  <br>
     *        + True: Yes  <br>
     *        + False: No
     */
    virtual bool flip() const = 0;
    /**
     * @locale zh
     * @brief 获取视频帧颜色空间，参看 ColorSpace{@link #ColorSpace}
     */
    /**
     * @locale en
     * @brief Gets video frame color space, see ColorSpace{@link #ColorSpace}
     */
    virtual ColorSpace colorSpace() const = 0;
    /**
     * @locale zh
     * @brief 视频帧颜色 plane 数量
     * @note yuv 数据存储格式分为打包（packed）存储格式和平面（planar）存储格式，planar 格式中 Y、U、V 分平面存储，packed 格式中 Y、U、V 交叉存储
     */
    /**
     * @locale en
     * @brief Video frame color plane number
     * @note YUV formats are categorized into planar format and packed format.  <br>
     *        In a planar format, the Y, U, and V components are stored separately as three planes, while in a packed format, the Y, U, and V components are stored in a single array.
     */
    virtual int numberOfPlanes() const = 0;
    /**
     * @locale zh
     * @brief 获取 plane 数据指针
     * @param plane_index plane 数据索引
     */
    /**
     * @locale en
     * @brief Gets plane data pointer
     * @param plane_index Plane data index
     */
    virtual uint8_t* getPlaneData(int plane_index) = 0;
    /**
     * @locale zh
     * @brief 获取 plane 中数据行的长度
     * @param plane_index plane 数据索引
     */
    /**
     * @locale en
     * @brief Gets the length of the data line in the plane
     * @param plane_index Plane data index
     */
    virtual int getPlaneStride(int plane_index) = 0;
    /**
     * @locale zh
     * @brief 获取扩展数据指针
     * @param size 扩展数据字节数
     */
    /**
     * @locale en
     * @brief Gets extended data pointer
     * @param size Size of extended data in bytes
     */
    virtual uint8_t* getExtraDataInfo(int& size) const = 0;  // NOLINT
    /**
     * @locale zh
     * @brief 获取补充数据指针
     * @param size 补充数据字节数
     */
    /**
     * @locale en
     * @brief Gets supplementary data pointer
     * @param size Size of supplementary data in bytes
     */
    virtual uint8_t* getSupplementaryInfo(int& size) const = 0;  // NOLINT
    /**
     * @locale zh
     * @brief 获取本地缓冲区指针
     */
    /**
     * @locale en
     * @brief Gets local buffer pointer
     */
    virtual void* getHwaccelBuffer() = 0;
    /**
     * @locale zh
     * @brief 获取硬件加速Context对象(AKA Opengl Context, Vulkan Context)
     */
    /**
     * @locale en
     * @brief Get hardware accelerate context(AKA Opengl Context, Vulkan Context)
     */
    virtual void* getHwaccelContext() = 0;
#ifdef __ANDROID__
    /**
     * @locale zh
     * @brief 获取硬件加速Context的Java对象(Only for Android, AKA Opengl Context)
     * @return 返回JavaLocalRef, 当不再使用时，需要手动执行DeleteLocalRef(env, jobject)方法释放该对象
     */
    /**
     * @locale en
     * @brief Get hardware accelerate context's java object(Only for Android, AKA Opengl Context)
     * @return return JavaLocalRef, need delete manually by use DeleteLocalRef(env, jobject)
     */
    virtual jobject getAndroidHwaccelContext() = 0;
#endif
    /**
     * @locale zh
     * @brief 获取纹理矩阵(仅针对纹理类型的frame生效)
     */
    /**
     * @locale en
     * @brief Get Texture matrix (only for texture type frame)
     */
    virtual void getTexMatrix(float matrix[16]) = 0;
    /**
     * @locale zh
     * @brief 获取纹理ID(仅针对纹理类型的frame生效)
     */
    /**
     * @locale en
     * @brief Get Texture ID (only for texture type frame)
     */
    virtual uint32_t getTextureId() = 0;
    /**
     * @locale zh
     * @brief 浅拷贝视频帧并返回指针
     */
    /**
     * @locale en
     * @brief Makes shallow copies of video frame and return pointer
     */
    virtual IVideoFrame* shallowCopy() = 0;
    /**
     * @locale zh
     * @brief 释放视频帧
     * @note 调用 pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} 推送视频帧后，你不需要再调用此方法释放资源。
     */
    /**
     * @locale en
     * @brief Releases video frame
     * @note After calling pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} to push the video frame, you must not call this API to release the resource.
     */
    virtual void release() = 0;
    /**
     * @locale zh
     * @brief 转换为i420格式的视频帧
     */
    /**
     * @locale en
     * @brief Converts video frames to i420 format
     */
    virtual void toI420() = 0;
    /**
     * @locale zh
     * @brief 获取视频帧的摄像头信息，参看 CameraID{@link #CameraID}
     */
    /**
     * @locale en
     * @brief Get cameraId of the frame, see CameraID{@link #CameraID}
     */
    virtual CameraID getCameraId() const = 0;
    /**
     * @locale zh
     * @hidden for internal use only on Windows and Android
     * @type api
     * @brief 获取全景视频的 Tile 信息
     * @return FoV（可视范围）随本端的头位姿实时更新获取到的视频帧，包括高清视野和低清背景。参见 FovVideoTileInfo{@link #FovVideoTileInfo}。
     */
    /**
     * @locale en
     * @hidden for internal use only on Windows and Android
     * @type api
     * @brief Get Tile information from the panoramic video frames to enable the FoV (Field of View).
     * @return Video frames in the FoV(filed of view) accroding to the head pose. Refer to FovVideoTileInfo{@link #FovVideoTileInfo} for more details.
     */
    virtual FovVideoTileInfo getFovTile() = 0;
/**
 * @hidden constructor/destructor
 */
protected:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IVideoFrame() = default;
};

/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 创建 IVideoFrame
 * @param builder 视频帧构建实例，参看 VideoFrameBuilder{@link #VideoFrameBuilder}
 * @return IVideoFrame{@link #IVideoFrame} 实例
 */
/**
 * @locale en
 * @type api
 * @region  video management
 * @brief  Create IVideoFrame
 * @param builder Video frame build instance. See VideoFrameBuilder{@link #VideoFrameBuilder}
 * @return IVideoFrame{@link #IVideoFrame} instance
 */
BYTERTC_API IVideoFrame* buildVideoFrame(const VideoFrameBuilder& builder);

/**
 * @locale zh
 * @type keytype
 * @region 视频管理
 * @brief 视频帧参数
 */
/**
 * @locale en
 * @type keytype
 * @region  video management
 * @brief  Video frame parameters
 */
typedef struct EncodedVideoFrameBuilder {
    /**
     * @locale zh
     * @brief 视频帧编码格式，参看 VideoCodecType{@link #VideoCodecType}
     */
    /**
     * @locale en
     * @brief Video frame encoding format. See VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType codec_type = kVideoCodecTypeUnknown;
    /**
     * @locale zh
     * @brief 视频帧编码类型，参看 VideoPictureType{@link #VideoPictureType}
     */
    /**
     * @locale en
     * @brief Video frame encoding type. See VideoPictureType{@link #VideoPictureType}
     */
    VideoPictureType picture_type = kVideoPictureTypeUnknown;
    /**
     * @locale zh
     * @brief 视频帧旋转角度，参看 VideoRotation{@link #VideoRotation}
     */
    /**
     * @locale en
     * @brief Video frame rotation angle. See VideoRotation{@link #VideoRotation}
     */
    VideoRotation rotation = kVideoRotation0;
    /**
     * @locale zh
     * @brief 视频帧数据指针
     * @note IEncodedVideoFrame 会获取数据的所有权
     */
    /**
     * @locale en
     * @brief Video frame data pointer
     * @note IEncodedVideoFrame  takes ownership of the data
     */
    uint8_t* data = nullptr;
    /**
     * @locale zh
     * @brief 视频帧数据大小
     */
    /**
     * @locale en
     * @brief Video frame data size
     */
    int size = 0;
    /**
     * @locale zh
     * @brief 视频帧宽度，单位：px
     */
    /**
     * @locale en
     * @brief Video frame width in px
     */
    int width = 0;
    /**
     * @locale zh
     * @brief 视频帧高度，单位：px
     */
    /**
     * @locale en
     * @brief Video frame height in px
     */
    int height = 0;
    /**
     * @locale zh
     * @brief 视频采集时间戳，单位：微秒
     */
    /**
     * @locale en
     * @brief Video capture timestamp in microseconds
     */
    int64_t timestamp_us = 0;
    /**
     * @locale zh
     * @brief 视频编码时间戳，单位：微秒
     */
    /**
     * @locale en
     * @brief Video encoding timestamp in microseconds
     */
    int64_t timestamp_dts_us = 0;
    /**
     * @locale zh
     * @brief 用户定义的视频帧释放回调函数指针，如果指针不为空，方法会被调用用来释放内存空间
     */
    /**
     * @locale en
     * @brief The user-defined video frame releases the callback function pointer. If the pointer is not empty, the method will be called to free memory space
     */
    int (*memory_deleter)(uint8_t* data, int size, void* user_opaque) = nullptr;
} EncodedVideoFrameBuilder;
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
class IEncodedVideoFrame {
public:
    /**
     * @locale zh
     * @type api
     * @brief 获取视频编码类型
     * @return 视频编码类型，参看 VideoCodecType{@link #VideoCodecType}
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the video encoding type
     * @return Video encoding type. See VideoCodecType{@link #VideoCodecType}
     */
    virtual VideoCodecType codecType() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取视频采集时间戳
     * @return 视频采集时间戳，单位：微秒
     */
    /**
     * @locale en
     * @type api
     * @brief Gets video capture timestamp
     * @return Video capture timestamp in microseconds
     */
    virtual int64_t timestampUs() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取视频编码时间戳
     * @return 视频编码时间戳，单位：微秒
     */
    /**
     * @locale en
     * @type api
     * @brief Gets video encoding timestamp
     * @return Video encoding timestamp in microseconds
     */
    virtual int64_t timestampDtsUs() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取视频帧宽度
     * @return 视频帧宽度，单位：px
     */
    /**
     * @locale en
     * @type api
     * @brief Get videos frame width
     * @return Video frame width in px
     */
    virtual int width() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取视频帧高度
     * @return 视频帧高度，单位：px
     */
    /**
     * @locale en
     * @type api
     * @brief Gets video frame height
     * @return Video frame height in px
     */
    virtual int height() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取视频编码帧类型
     * @return 视频编码帧类型，参看 VideoPictureType{@link #VideoPictureType}
     */
    /**
     * @locale en
     * @type api
     * @brief Gets video compression picture type.
     * @return Video compression picture type.See VideoPictureType{@link #VideoPictureType}
     */
    virtual VideoPictureType pictureType() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取视频帧旋转角度
     * @return 视频帧旋转角度，参看 VideoRotation{@link #VideoRotation}
     */
    /**
     * @locale en
     * @type api
     * @brief Gets video frame rotation angle
     * @return Video frame rotation angle. See VideoRotation{@link #VideoRotation}
     */
    virtual VideoRotation rotation() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取视频帧数据指针地址
     * @return 视频帧数据指针地址
     */
    /**
     * @locale en
     * @type api
     * @brief Get the pointer to the video frame
     * @return The pointer to the video frame
     */
    virtual uint8_t* data() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取视频帧数据大小
     * @return 视频帧数据大小
     */
    /**
     * @locale en
     * @type api
     * @brief Gets video frame data size
     * @return Video frame data size
     */
    virtual int dataSize() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 浅拷贝视频帧并返回指针
     */
    /**
     * @locale en
     * @type api
     * @brief Makes shallow copies of video frame and return pointer
     */
    virtual IEncodedVideoFrame* shallowCopy() const = 0;
    /**
     * @locale zh
     * @type api
     * @brief 释放视频帧
     */
    /**
     * @locale en
     * @type api
     * @brief Releases video frame
     */
    virtual void release() = 0;
    /**
     * @hidden constructor/destructor
     */
protected:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IEncodedVideoFrame() = default;
};

/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 创建 IEncodedVideoFrame
 * @param builder 编码后的视频帧构建实例，参看 EncodedVideoFrameBuilder{@link #EncodedVideoFrameBuilder}
 * @return IEncodedVideoFrame{@link #IEncodedVideoFrame} 实例
 */
/**
 * @locale en
 * @type api
 * @region  video management
 * @brief  Create IEncodedVideoFrame
 * @param builder Encoded video frame build instance. See EncodedVideoFrameBuilder{@link #EncodedVideoFrameBuilder}
 * @return IEncodedVideoFrame{@link #IEncodedVideoFrame} instance
 */
BYTERTC_API IEncodedVideoFrame* buildEncodedVideoFrame(const EncodedVideoFrameBuilder& builder);


/**
 * @locale zh
 * @hidden(Linux,Android,iOS)
 * @type keytype
 * @brief RTC 智能决策后得到的帧率和分辨率积（宽*高）。
 */
/**
 * @locale en
 * @hidden(Linux,Android,iOS)
 * @type keytype
 * @brief  The recommended pixel and framerate by RTC.
 */
struct FrameUpdateInfo {
    /**
     * @locale zh
     * @brief 分辨率积（宽*高）。
     */
    /**
     * @locale en
     * @brief Pixel (width * height).
     */
    int pixel;
    /**
     * @locale zh
     * @brief 帧率。
     */
    /**
     * @locale en
     * @brief The frame rate.
     */
    int framerate;
};


/**
 * @locale zh
 * @type keytype
 * @brief 屏幕流编码模式。默认采用清晰模式。若在采集时设置 ScreenFilterConfig{@link #ScreenFilterConfig} 排除指定窗口，共享视频时帧率无法达到 30fps。
 */
/**
 * @locale en
 * @type keytype
 * @brief The encoding modes for shared-screen streams. The default mode is the high-resolution mode. If you exclude specific windows by setting ScreenFilterConfig{@link #ScreenFilterConfig}, the frame rate of the shared-screen stream will be slower than 30fps。
 */
enum ScreenVideoEncodePreference {
    /**
     * @locale zh
     * @hidden(Linux,Android,iOS)
     * @brief 智能模式。根据屏幕内容智能决策选择流畅模式或清晰模式。
     */
    /**
     * @locale en
     * @hidden(Linux,Android,iOS)
     * @brief The automatic mode. The encoding mode is dynamically determined by RTC based on the content.
     */
    kScreenVideoEncodePreferenceAuto = 0,
    /**
     * @locale zh
     * @brief 流畅模式，优先保障帧率。适用于共享游戏、视频等动态画面。
     */
    /**
     * @locale en
     * @brief The high frame rate mode. Ensure the highest framerate possible under challenging network conditions. This mode is designed to share audiovisual content, including games and videos.
     */
    kScreenVideoEncodePreferenceFramerate,
    /**
     * @locale zh
     * @brief 清晰模式，优先保障分辨率。适用于共享PPT、文档、图片等静态画面。
     */
    /**
     * @locale en
     * @brief The high-resolution mode. Ensure the highest resolution possible under challenging network conditions. This mode is designed to share micro-detailed content, including slides, documents, images, illustrations, or graphics.
     */
    kScreenVideoEncodePreferenceQuality,

};

/**
 * @locale zh
 * @type keytype
 * @brief 屏幕编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)。
 */
/**
 * @locale en
 * @type keytype
 * @brief The encoding configuration for shared-screen streams. See [Setting Video Encoder Configuration](https://docs.byteplus.com/byteplus-rtc/docs/70122).
 */
struct ScreenVideoEncoderConfig {
    /**
     * @locale zh
     * @brief 视频宽度，单位：像素。
     */
    /**
     * @locale en
     * @brief Width(in px).
     */
    int width;
    /**
     * @locale zh
     * @brief 视频高度，单位：像素。
     */
    /**
     * @locale en
     * @brief Height(in px).
     */
    int height;
    /**
     * @locale zh
     * @brief 视频帧率，单位：fps。
     */
    /**
     * @locale en
     * @brief The frame rate(in fps).
     */
    int frame_rate;
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
     *        If you set this value to 0, streams will not be encoded and published.<br>
     *        On Version 3.44 or later, the default value for internal capture is -1. On versions earlier than 3.44, you must set the maximum bit rate because there is no default value.
     */
    int max_bitrate = SEND_KBPS_AUTO_CALCULATE;
    /**
     * @locale zh
     * @brief 最小编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。<br>
     *        最小编码码率必须小于或等于最大编码，否则不对视频流进行编码发送。
     */
    /**
     * @locale en
     * @brief The minimum bitrate(in kbps).Optional for internal capture while mandatory for custom capture.<br>
     *        The minimum bitrate must be set lower than the maximum bitrate. Otherwise, streams will not be encoded and published.
     */
    int min_bitrate = 0;
    /**
     * @locale zh
     * @brief 屏幕流编码模式。参见 ScreenVideoEncodePreference{@link #ScreenVideoEncodePreference}。
     */
    /**
     * @locale en
     * @brief The encoding modes for shared-screen streams.See ScreenVideoEncodePreference{@link #ScreenVideoEncodePreference}.
     */
    ScreenVideoEncodePreference encoder_preference = ScreenVideoEncodePreference::kScreenVideoEncodePreferenceQuality;
};


}  // namespace bytertc
