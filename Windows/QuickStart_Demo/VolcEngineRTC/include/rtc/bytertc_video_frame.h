/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Video Frame
 */

#pragma once

#ifndef BYTE_RTC_VIDEO_FRAME_H__
#define BYTE_RTC_VIDEO_FRAME_H__

#include <stdint.h>
#include <stddef.h>
#include <memory>
#include "bytertc_common_defines.h"
#ifdef BYTERTC_ANDROID
#include <jni.h>
#endif

namespace bytertc {

/** 
 * @type keytype
 * @brief 编码帧类型
 */
enum VideoPictureType {
    /** 
     * @brief 未知类型
     */
    kVideoPictureTypeUnknown = 0,
    /** 
     * @brief I帧，关键帧，编解码不需要参考其他视频帧
     */
    kVideoPictureTypeI,
    /** 
     * @brief P帧，向前参考帧，编解码需要参考前一帧视频帧
     */
    kVideoPictureTypeP,
    /** 
     * @brief B帧，前后参考帧，编解码需要参考前后两帧视频帧
     */
    kVideoPictureTypeB
};

/** 
 * @type keytype
 * @brief 视频帧旋转角度
 */
enum VideoRotation {
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

/** 
 * @type keytype
 * @brief 视频帧缩放模式，默认值为 FitWithCropping。
 */
enum VideoStreamScaleMode {
    /** 
     * @brief 自动模式
     */
    kVideoStreamScaleModeAuto = 0,
    /** 
     * @brief 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。
     */
    kVideoStreamScaleModeStretch = 1,
    /** 
     * @brief 视窗填满优先。<br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    kVideoStreamScaleModeFitWithCropping = 2,
    /** 
     * @brief 视频帧内容全部显示优先。<br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
     */
    kVideoStreamScaleModeFitWithFilling = 3,
};


/** 
 * @type keytype
 * @brief 视频编码模式
 */
enum VideoCodecMode {
    /** 
     * @brief 自动选择
     */
    kCodecModeAuto = 0,
    /** 
     * @brief 硬编码
     */
    kCodecModeHardware,
    /** 
     * @brief 软编码
     */
    kCodecModeSoftware,
};

/** 
 * @type keytype
 * @brief 编码策略偏好
 */
enum VideoEncodePreference {
    /** 
     * @brief 无偏好
     */
    kVideoEncodePreferenceDisabled = 0,
    /** 
     * @brief 帧率优先
     */
    kVideoEncodePreferenceFramerate,
    /** 
     * @brief 质量优先
     */
    kVideoEncodePreferenceQuality,
    /** 
     * @brief 平衡质量与帧率
     */
    kVideoEncodePreferenceBalance,
};

/** 
 * @type keytype
 * @brief 摄像头。
 */
enum CameraID {
    /** 
     *@brief 移动端前置摄像头，PC端内置摄像头
     */
    kCameraIDFront = 0,
    /** 
     *@brief 移动端后置摄像头，PC端无定义
     */
    kCameraIDBack = 1,
    /** 
     *@brief 外接摄像头
     */
    kCameraIDExternal = 2,
    /** 
     *@brief 无效值
     */
    kCameraIDInvalid = 3
};


#define SEND_KBPS_AUTO_CALCULATE -1
#define SEND_KBPS_DISABLE_VIDEO_SEND 0

/** 
 * @type keytype
 * @brief 视频流参数
 */
struct VideoSolution {
    /** 
     * @brief 视频宽度，单位：像素
     */
    int width;
    /** 
     * @brief 视频高度，单位：像素
     */
    int height;
    /** 
     * @brief 视频帧率
     */
    int fps;
    /** 
     * @brief 最大发送编码码率（kbps），建议使用默认的自动码率。<li>-1: 自动码率</li><li>0: 不开启上限</li><li>>0: 填写预估码率<li>
     */
    int max_send_kbps = SEND_KBPS_AUTO_CALCULATE;
    /** 
     * @brief 视频编码质量策略，参看 VideoEncodePreference{@link #VideoEncodePreference}
     */
    VideoEncodePreference encode_preference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
};
/**  
 * @type keytype
 * @brief 视频编码配置。参考 [设置视频发布参数](https://www.volcengine.com/docs/6348/70122)
 */
struct VideoEncoderConfig {
    /** 
     * @brief 视频宽度，单位：像素
     */
    int width;
    /** 
     * @brief 视频高度，单位：像素
     */
    int height;
    /** 
     * @brief 视频帧率，单位：fps
     */
    int frameRate;
    /** 
     * @brief 最大编码码率，使用 SDK 内部采集时可选设置，自定义采集时必须设置，单位：kbps。  <br>
     *        内部采集模式下默认值为 -1，即适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率。 <br>
     *        设为 0 则不对视频流进行编码发送。
     */
    int maxBitrate = SEND_KBPS_AUTO_CALCULATE;
    /** 
     * @brief 视频编码质量策略，默认质量优先，参看 VideoEncodePreference{@link #VideoEncodePreference}
     */
    VideoEncodePreference encoderPreference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
};

/** 
 * @type keytype
 * @brief 视频属性
 */
struct VideoSolutionDescription {
    /** 
     * @brief 宽（像素）<br>
     *        默认值为 `1920` <br>
     *        为 `0` 时，保持源的宽。
     */
    int width;
    /** 
     * @brief 高（像素）<br>
     *        默认值为 `1080` <br>
     *        为 `0` 时，保持源的高。
     */
    int height;
    /** 
     * @brief 视频帧率(fps)，默认为 15 fps
     */
    int fps;
    /** 
     * @brief 最大发送速率（千比特每秒）。<br>
     *        默认为 `-1`，适配码率模式，系统将根据输入的分辨率和帧率自动计算适用的码率
     */
    int max_send_kbps;
    /** 
     * @brief 缩放模式。参看 VideoStreamScaleMode{@link #VideoStreamScaleMode}
     */
    VideoStreamScaleMode scale_mode = VideoStreamScaleMode::kVideoStreamScaleModeAuto;
    /** 
     * @brief 视频的编码类型。参看 VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType codec_name = VideoCodecType::kVideoCodecTypeUnknown;
    /** 
     * @brief 视频的编码模式。参看 VideoCodecMode{@link #VideoCodecMode}
     */
    VideoCodecMode codec_mode = VideoCodecMode::kCodecModeAuto;
    /** 
     * @brief 视频编码质量偏好策略。参看 VideoEncodePreference{@link #VideoEncodePreference}
     */
    VideoEncodePreference encode_preference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
};


/** 
 * @hidden
 * @type keytype
 * @region 视频管理
 */
typedef VideoSolutionDescription VideoProfile;

/** 
 * @type keytype
 * @brief 视频帧颜色编码格式
 */
enum VideoPixelFormat {
    /** 
     * @brief 未知的颜色编码格式
     */
    kVideoPixelFormatUnknown = 0,
    /** 
     * @brief YUV I420 格式
     */
    kVideoPixelFormatI420,
    /** 
     * @brief YUV NV12 格式
     */
    kVideoPixelFormatNV12,
    /** 
     * @brief YUV NV21 格式
     */
    kVideoPixelFormatNV21,
    /** 
     * @brief RGB 24bit格式，
     */
    kVideoPixelFormatRGB24,
    /** 
     * @brief RGBA 编码格式
     */
    kVideoPixelFormatRGBA,
    /** 
     * @brief ARGB 编码格式
     */
    kVideoPixelFormatARGB,
    /** 
     * @brief BGRA 编码格式
     */
    kVideoPixelFormatBGRA,
    /** 
     * @brief Texture2D格式
     */
    kVideoPixelFormatTexture2D = 0x0DE1,
    /** 
     * @brief TextureOES格式
     */
    kVideoPixelFormatTextureOES = 0x8D65,
};

/** 
 * @type keytype
 * @brief 视频内容类型
 */
enum VideoContentType {
    /** 
     * @brief 普通视频
     */
    kVideoContentTypeNormalFrame = 0,
    /** 
     * @brief 黑帧视频
     */
    kVideoContentTypeBlackFrame,
};

/** 
 * @type keytype
 * @region 视频管理
 * @brief 视频YUV格式颜色空间
 */
enum ColorSpace {
    /** 
     * 未知的颜色空间，默认使用kColorSpaceYCbCrBT601LimitedRange颜色空间
     */
    kColorSpaceUnknown = 0,
    /** 
     * @brief BT.601数字编码标准，颜色空间[16-235]
     */
    kColorSpaceYCbCrBT601LimitedRange,
    /** 
     *  @brief BT.601数字编码标准，颜色空间[0-255]
     */
    kColorSpaceYCbCrBT601FullRange,
    /** 
     * @brief BT.7091数字编码标准，颜色空间[16-235]
     */
    kColorSpaceYCbCrBT709LimitedRange,
    /** 
     * @brief BT.7091数字编码标准，颜色空间[0-255]
     */
    kColorSpaceYCbCrBT709FullRange,
};

/** 
 * @type keytype
 * @brief 视频帧格式
 */
enum VideoFrameType {
    /** 
     * @brief 原始数据格式，按照内存存储
     */
    kVideoFrameTypeRawMemory,
    /** 
     * @brief CVPixelBufferRef类型，支持 iOS and macOS 平台
     */
    kVideoFrameTypeCVPixelBuffer,
    /** 
     * @brief open gl 纹理数据类型
     */
    kVideoFrameTypeGLTexture,
    /** 
     * @brief cuda 数据类型
     */
    kVideoFrameTypeCuda,
    /** 
     * @brief direct3d 11 数据格式
     */
    kVideoFrameTypeD3D11,
    /** 
     * @brief direct3d 9 数据格式
     */
    kVideoFrameTypeD3D9,
    /** 
     * @brief Java的VideoFrame 数据格式
     */
    kVideoFrameTypeJavaFrame,
    /** 
     * @brief vaapi 数据格式
     */
    kVideoFrameTypeVAAPI,
};

/** 
 * @type keytype
 * @brief 自定义内存释放器
 */
struct ManagedMemory {
    /** 
     * @hidden
     * @brief 内存数据数据类型，默认为 cpu 内存,详见 VideoFrameType:{@link #VideoFrameType}
     * @notes 这个字段用不到了，后续会删除，目前只有 cpu 内存
     */
    VideoFrameType type = kVideoFrameTypeRawMemory;
    /** 
     * @brief 内存数据地址
     */
    uint8_t* data = nullptr;
    /** 
     * @brief 内存空间的大小
     */
    int size = 0;
    /** 
     * @brief 用户自定义数据
     */
    void* user_opaque = nullptr;
    /** 
     * @brief 自定义内存释放方法指针，如果指针不为空，方法会被调用，用来释放内存空间。
     *        函数传入的参数分别是本结构体内 data、size、user_opaque 3个字段。
     */
    int (*memory_deleter)(uint8_t* data, int size, void* user_opaque) = nullptr;
};

/** 
 * @type keytype
 * @region 视频管理
 * @brief 视频帧构建类
 */
typedef struct VideoFrameBuilder {
#define ByteRTCNumDataPointers 4
    /** 
     * @hidden
     * @brief 内存数据数据类型，默认为 cpu 内存，详见 VideoFrameType{@link #VideoFrameType}
     */
    VideoFrameType frame_type = kVideoFrameTypeRawMemory;
    /** 
     * @hidden
     * @brief 视频帧像素格式，详见 VideoPixelFormat{@link #VideoPixelFormat}
     */
    VideoPixelFormat pixel_fmt = kVideoPixelFormatUnknown;
    /** 
     * @hidden
     * @brief 视频帧颜色空间，参看 ColorSpace{@link #ColorSpace}
     */
    ColorSpace color_space = kColorSpaceUnknown;
    /** 
     * @brief 视频帧数据平面指针数组
     */
    uint8_t* data[ByteRTCNumDataPointers] = { 0 };
    /** 
     * @brief 视频帧数据平面行长度
     */
    int linesize[ByteRTCNumDataPointers] = { 0 };
    /** 
     * @brief SEI 数据地址
     */
    uint8_t* extra_data = nullptr;
    /** 
     * @brief SEI 数据大小
     */
    int extra_data_size = 0;
    /** 
     * @brief 补充数据地址
     */
    uint8_t* supplementary_info = nullptr;
    /** 
     * @brief 补充数据大小
     */
    int supplementary_info_size = 0;
    /** 
     * @brief 视频帧内存空间大小
     */
    int size = 0;
    /** 
     * @brief 视频帧宽度
     */
    int width = 0;
    /** 
     * @brief 视频帧高度
     */
    int height = 0;
    /** 
     * @brief 视频旋转角度，参看 VideoRotation{@link #VideoRotation}
     */
    VideoRotation rotation = kVideoRotation0;
    /** 
     * @hidden
     * @brief 镜像参数
     */
    bool flip = false;
    /** 
     * @brief 硬件加速缓冲区指针
     */
    void* hwaccel_buffer = nullptr;
    /** 
     * @brief 用户私有数据指针
     */
    void* user_opaque = nullptr;
    /** 
     * @brief 视频帧时间戳
     */
    int64_t timestamp_us = 0;
    /** 
    * @brief 硬件加速Context对象(AKA Opengl Context, Vulkan Context)
    */
    void* hwaccel_context = nullptr;
#ifdef __ANDROID__
    /** 
     * @brief 硬件加速Context的Java对象(Only for Android, AKA Opengl Context)
     */
    jobject android_hwaccel_context = nullptr;
#endif
    /** 
     * @brief 纹理矩阵(仅针对纹理类型的frame生效)
     */
    float tex_matrix[16] = { };
    /** 
     * @brief 纹理ID(仅针对纹理类型的frame生效)
     */
    uint32_t texture_id = 0;

    /** 
     * @brief 用户定义的视频帧释放回调函数指针，如果指针不为空，方法会被调用用来释放内存空间
     */
    int (*memory_deleter)(struct VideoFrameBuilder* builder) = nullptr;
} VideoFrameBuilder;

/** 
 * @type keytype
 * @brief 设置视频帧
 */
class IVideoFrame {
public:
    /** 
     * @brief 获取视频帧类型，参看 VideoFrameType{@link #VideoFrameType}
     */
    virtual VideoFrameType frameType() const = 0;
    /** 
     * @brief 获取视频帧格式，参看 VideoPixelFormat{@link #VideoPixelFormat}
     */
    virtual VideoPixelFormat pixelFormat() const = 0;
    /** 
     * @brief 获取视频内容类型，参看 VideoContentType{@link #VideoContentType}。
     */
    virtual VideoContentType videoContentType() const = 0;

    /** 
     * @brief 获取视频帧时间戳，单位：微秒
     */
    virtual int64_t timestampUs() const = 0;
    /** 
     * @brief 获取视频帧宽度，单位：px
     */
    virtual int width() const = 0;
    /** 
     * @brief 获取视频帧高度，单位：px
     */
    virtual int height() const = 0;
    /** 
     * @brief 获取视频帧旋转角度，参看 VideoRotation{@link #VideoRotation}
     */
    virtual VideoRotation rotation() const = 0;
    /** 
     * @deprecated
     * @hidden
     * @brief 获取镜像信息
     * @return 是否需要镜像
     *        + True: 是  <br>
     *        + False: 否
     */
    virtual bool flip() const = 0;
    /** 
     * @brief 获取视频帧颜色空间，参看 ColorSpace{@link #ColorSpace}
     */
    virtual ColorSpace colorSpace() const = 0;
    /** 
     * @brief 视频帧颜色 plane 数量
     * @notes yuv 数据存储格式分为打包（packed）存储格式和平面（planar）存储格式，planar 格式中 Y、U、V 分平面存储，packed 格式中 Y、U、V 交叉存储
     */
    virtual int numberOfPlanes() const = 0;
    /** 
     * @brief 获取 plane 数据指针
     * @param [in] plane_index plane 数据索引
     */
    virtual uint8_t* getPlaneData(int plane_index) = 0;
    /** 
     * @brief 获取 plane 中数据行的长度
     * @param [in] plane_index plane 数据索引
     */
    virtual int getPlaneStride(int plane_index) = 0;
    /** 
     * @brief 获取扩展数据指针
     * @param [in] size 扩展数据字节数
     */
    virtual uint8_t* getExtraDataInfo(int& size) const = 0;  // NOLINT
    /** 
     * @brief 获取补充数据指针
     * @param [in] size 补充数据字节数
     */
    virtual uint8_t* getSupplementaryInfo(int& size) const = 0;  // NOLINT
    /** 
     * @brief 获取本地缓冲区指针
     */
    virtual void* getHwaccelBuffer() = 0;
    /** 
     * @brief 获取硬件加速Context对象(AKA Opengl Context, Vulkan Context)
     */
    virtual void* getHwaccelContext() = 0;
#ifdef __ANDROID__
    /** 
     * @brief 获取硬件加速Context的Java对象(Only for Android, AKA Opengl Context)
     * @return 返回JavaLocalRef, 当不再使用时，需要手动执行DeleteLocalRef(env, jobject)方法释放该对象
     */
    virtual jobject getAndroidHwaccelContext() = 0;
#endif
    /** 
     * @brief 获取纹理矩阵(仅针对纹理类型的frame生效)
     */
    virtual void getTexMatrix(float matrix[16]) = 0;
    /** 
     * @brief 获取纹理ID(仅针对纹理类型的frame生效)
     */
    virtual uint32_t getTextureId() = 0;
    /** 
     * @brief 浅拷贝视频帧并返回指针
     */
    virtual IVideoFrame* shallowCopy() = 0;
    /** 
     * @brief 释放视频帧
     */
    virtual void release() = 0;
    /** 
     * @brief 转换为i420格式的视频帧
     */
    virtual void toI420() = 0;
    /** 
     * @brief 获取视频帧的摄像头信息，参看 CameraID{@link #CameraID}
     */
    virtual CameraID getCameraId() const = 0;
/**
 * @hidden
 */
protected:
    /** 
     * @brief 析构函数
     */
    virtual ~IVideoFrame() = default;
};

/** 
 * @type keytype
 * @region 视频管理
 * @brief 视频帧参数
 */
typedef struct EncodedVideoFrameBuilder {
    /** 
     * @brief 视频帧编码格式，参看 VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType codec_type = kVideoCodecTypeUnknown;
    /** 
     * @brief 视频帧编码类型，参看 VideoPictureType{@link #VideoPictureType}
     */
    VideoPictureType picture_type = kVideoPictureTypeUnknown;
    /** 
     * @brief 视频帧旋转角度，参看 VideoRotation{@link #VideoRotation}
     */
    VideoRotation rotation = kVideoRotation0;
    /** 
     * @brief 视频帧数据指针
     * @notes IEncodedVideoFrame 会获取数据的所有权
     */
    uint8_t* data = nullptr;
    /** 
     * @brief 视频帧数据大小
     */
    int size = 0;
    /** 
     * @brief 视频帧宽度，单位：px
     */
    int width = 0;
    /** 
     * @brief 视频帧高度，单位：px
     */
    int height = 0;
    /** 
     * @brief 视频采集时间戳，单位：微秒
     */
    int64_t timestamp_us = 0;
    /** 
     * @brief 视频编码时间戳，单位：微秒
     */
    int64_t timestamp_dts_us = 0;
    /** 
     * @brief 用户定义的视频帧释放回调函数指针，如果指针不为空，方法会被调用用来释放内存空间
     */
    int (*memory_deleter)(uint8_t* data, int size, void* user_opaque) = nullptr;
} EncodedVideoFrameBuilder;
/** 
 * @type keytype
 * @brief 视频帧信息
 */
class IEncodedVideoFrame {
public:
    /** 
     * @type api
     * @brief 获取视频编码类型
     * @return 视频编码类型，参看 VideoCodecType{@link #VideoCodecType}
     */
    virtual VideoCodecType codecType() const = 0;
    /** 
     * @type api
     * @brief 获取视频采集时间戳
     * @return 视频采集时间戳，单位：微秒
     */
    virtual int64_t timestampUs() const = 0;
    /** 
     * @type api
     * @brief 获取视频编码时间戳
     * @return 视频编码时间戳，单位：微秒
     */
    virtual int64_t timestampDtsUs() const = 0;
    /** 
     * @type api
     * @brief 获取视频帧宽度
     * @return 视频帧宽度，单位：px
     */
    virtual int width() const = 0;
    /** 
     * @type api
     * @brief 获取视频帧高度
     * @return 视频帧高度，单位：px
     */
    virtual int height() const = 0;
    /** 
     * @type api
     * @brief 获取视频编码帧类型
     * @return 视频编码帧类型，参看 VideoPictureType{@link #VideoPictureType}
     */
    virtual VideoPictureType pictureType() const = 0;
    /** 
     * @type api
     * @brief 获取视频帧旋转角度
     * @return 视频帧旋转角度，参看 VideoRotation{@link #VideoRotation}
     */
    virtual VideoRotation rotation() const = 0;
    /** 
     * @type api
     * @brief 获取视频帧数据指针地址
     * @return 视频帧数据指针地址
     */
    virtual uint8_t* data() const = 0;
    /** 
     * @type api
     * @brief 获取视频帧数据大小
     * @return 视频帧数据大小
     */
    virtual int dataSize() const = 0;
    /** 
     * @type api
     * @brief 浅拷贝视频帧并返回指针
     */
    virtual IEncodedVideoFrame* shallowCopy() const = 0;
    /** 
     * @type api
     * @brief 释放视频帧
     */
    virtual void release() = 0;
    /** 
     * @type api
     * @brief 根据视频帧参数创建视频帧并返回指针
     * @param [in] builder 视频帧参数，参看 EncodedVideoFrameBuilder{@link #EncodedVideoFrameBuilder}
     * @return IEncodedVideoFrame 创建的视频帧的指针
     */
    static IEncodedVideoFrame* buildEncodedVideoFrame(const EncodedVideoFrameBuilder& builder);
    /**
     * @hidden
     */
protected:
    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IEncodedVideoFrame() = default;
};

}  // namespace bytertc

#endif // BYTE_RTC_VIDEO_FRAME_H__
