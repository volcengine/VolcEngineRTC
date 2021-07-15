#ifndef BYTE_RTC_VIDEO_FRAME_H
#define BYTE_RTC_VIDEO_FRAME_H

#include <stdint.h>
#include <stddef.h>
#include <memory>

namespace bytertc {

  /**
   * @type keytype
   * @brief 视频帧旋转角度
   */
  enum VideoRotation {
      /**
       * @brief 顺时针旋转0度
       */
      VideoRotation_0 = 0,
      /**
       * @brief 顺时针旋转90度
       */
      VideoRotation_90 = 90,
      /**
       * @brief 顺时针旋转180度
       */
      VideoRotation_180 = 180,
      /**
       * @brief 顺时针旋转270度
       */
      VideoRotation_270 = 270
  };

/**
 * @type keytype
 * @brief 视频帧类型
 */
enum VIDEO_FRAME_TYPE {
    /**
     * @brief 无格式
     */
    FORMAT_TYPE_NONE = -1,
    /**
     * @brief I420格式的视频帧
     */
    FORMAT_TYPE_I420 = 0
};

/**
 * @type keytype
 * @brief 视频帧缩放模式
 */
enum ScaleMode {
    /**
     * @brief 自动模式，默认值为 FitWithCropping。
     */
    Auto = 0,
    /**
     * @brief 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。
     */
    Stretch = 1,
    /**
     * @brief 视窗填满优先。<br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    FitWithCropping = 2,
    /**
     * @brief 视频帧内容全部显示优先。<br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
     */
    FitWithFilling = 3,
};

/**
 * @type keytype
 * @brief 视频编码模式
 */
enum CodecMode {
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
 * @brief 视频的编码类型
 */
enum VideoCodecType {
    /**
     * @hidden
     * @brief 未知类型
     */
    kVideoCodecUnknown = 0,
    /**
     * @brief 标准 H264 编码器
     */
    kVideoCodecH264 = 1,
    /**
     * @brief 标准 ByteVC1 编码器
     */
    kVideoCodecByteVC1 = 2,
};

/**
 * @type keytype
 * @brief 网络不好时的视频编码降级策略
 */
enum EncodePreference {
    /**
     * @brief 不降级
     */
    EncodePreferenceDisabled = 0,
    /**
     * @brief 优先保证帧率，以保证视频流畅度
     */
    EncodePreferenceFramerate,
    /**
     * @brief 优先保证画质
     */
    EncodePreferenceQuality,
    /**
     * @brief 平衡模式
     */
    EncodePreferenceBalance,
};

#define SEND_KBPS_AUTO_CALCULATE -1
#define SEND_KBPS_DISABLE_VIDEO_SEND 0

/**
 * @type keytype
 * @brief 视频参数
 */
struct VideoSolution {
    /**
     * @brief 宽（像素）
     */
    int width;
    /**
     * @brief 高（像素）
     */
    int height;
    /**
     * @brief 视频帧率
     */
    int fps;
    /**
     * @brief 最高编码码率（千比特每秒）<br>
     *        建议使用预估值。
     */
    int max_send_kbps = SEND_KBPS_AUTO_CALCULATE;
    /**
     * @brief 视频帧缩放模式。你可以设置缩放以适应视窗，参见 ScaleMode{@link #ScaleMode}
     */
    ScaleMode scale_mode = ScaleMode::Auto;
    /**
     * @brief 视频编码质量策略，参见 EncodePreference{@link #EncodePreference}
     */
    EncodePreference encode_preference = EncodePreference::EncodePreferenceFramerate;
};

/**
 * @type keytype
 * @brief 视频属性
 */
struct VideoSolutionDescription {
    /**
     * @brief 宽（像素）
     */
    int width;
    /**
     * @brief 高（像素）
     */
    int height;
    /**
     * @brief 视频帧率
     */
    int fps;
    /**
     * @brief 最大发送速率（千比特每秒）
     */
    int max_send_kbps;
    /**
     * @brief 缩放模式。参看 ScaleMode{@link #ScaleMode}
     */
    ScaleMode scale_mode = ScaleMode::Auto;
    /**
     * @brief 视频的编码类型。参看 VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType codec_name = VideoCodecType::kVideoCodecUnknown;
    /**
     * @brief 视频的编码模式，详见 CodecMode{@link #CodecMode}
     */
    CodecMode codec_mode = CodecMode::AutoMode;
    /**
     * @brief 视频编码质量偏好策略，详见 EncodePreference{@link #EncodePreference}
     */
    EncodePreference encode_preference = EncodePreference::EncodePreferenceFramerate;
};

/**
 * @hidden
 * @type keytype
 * @region 视频管理
 */
typedef VideoSolutionDescription VideoProfile;

/**
 * @type keytype
 * @region 视频管理
 * @brief 视频帧颜色编码格式
 */
enum ByteVideoPixelFormat {
    /**
     * @brief 未知的颜色编码格式
     */
    kByteVideoPixelFormatUnknown = 0,
    /**
     * @brief YUV I420 格式
     */
    kByteVideoPixelFormatI420,
    /**
     * @brief YUV NV12 格式
     */
    kByteVideoPixelFormatNV12,
    /**
     * @brief YUV NV21 格式
     */
    kByteVideoPixelFormatNV21,
    /**
     * @brief RGB 24bit格式，
     */
    kByteVideoPixelFormatRGB24,
    /**
     * @brief RGBA 编码格式
     */
    kByteVideoPixelFormatRGBA,
    /**
     * @brief ARGB 编码格式
     */
    kByteVideoPixelFormatARGB,
    /**
     * @brief BGRA 编码格式
     */
    kByteVideoPixelFormatBGRA,
};

/**
 * @hidden
 * @type keytype
 * @region 视频管理
 * @brief 视频YUV格式颜色空间
 */
enum ByteColorSpace {
    /**
     * 未知的颜色空间，默认使用kColorSpaceYCbCrBT601LimitedRange颜色空间
     */
    kByteColorSpaceUnknown = 0,
    /**
     * @brief BT.601数字编码标准，颜色空间[16-235]
     */
    kByteColorSpaceYCbCrBT601LimitedRange,
    /**
     *  @brief BT.601数字编码标准，颜色空间[0-255]
     */
    kByteColorSpaceYCbCrBT601FullRange,
    /**
     * @brief BT.7091数字编码标准，颜色空间[16-235]
     */
    kByteColorSpaceYCbCrBT709LimitedRange,
    /**
     * @brief BT.7091数字编码标准，颜色空间[0-255]
     */
    kByteColorSpaceYCbCrBT709FullRange,
};

/**
 * @type keytype
 * @region 视频管理
 * @brief 视频帧格式
 */
enum ByteVideoFrameType {
    /**
     * @brief 原始数据格式，按照内存存储
     */
    kByteVideoFrameTypeRawMemory,
    /**
     * @brief CVPixelBufferRef类型，支持 iOS and macOS 平台
     */
    kByteVideoFrameTypeCVPixelBuffer,
    /**
     * @brief open gl 纹理数据类型
     */
    kByteVideoFrameTypeGLTexture,
    /**
     * @brief cuda 数据类型
     */
    kByteVideoFrameTypeCuda,
    /**
     * @brief direct3d 11 数据格式
     */
    kByteVideoFrameTypeD3D11,
    /**
     * @brief direct3d 9 数据格式
     */
    kByteVideoFrameTypeD3D9,
    /**
     * @brief Java的VideoFrame 数据格式
     */
    kByteVideoFrameTypeJavaFrame,
    /**
     * @brief vaapi 数据格式
     */
    kByteVideoFrameTypeVAAPI,
};

/**
 * @type keytype
 * @brief 自定义内存释放器
 */
struct ByteManagedMemory {
    /**
     * @hidden
     * @brief 内存数据数据类型，默认为 cpu 内存,详见 ByteVideoFrameType:{@link #ByteVideoFrameType}
     * @notes 这个字段用不到了，后续会删除，目前只有cpu内存
     */
    ByteVideoFrameType type = kByteVideoFrameTypeRawMemory;

    /**
     * @brief 内存数据地址
     * @notes  <br>
     *      + 数据类型类是 cpu 内存时，地址是内存数据地址  <br>
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
typedef struct ByteVideoFrameBuilder {
#define kByteNumDataPointers 4
    /**
     * @hidden
     * @brief 内存数据数据类型，默认为 cpu 内存,详见 ByteVideoFrameType:{@link #ByteVideoFrameType}
     */
    ByteVideoFrameType frame_type = kByteVideoFrameTypeRawMemory;
    /**
     * @hidden
     * @brief 视频帧像素格式，详见 ByteVideoPixelFormat:{@link #ByteVideoPixelFormat}
     */
    ByteVideoPixelFormat pixel_fmt = kByteVideoPixelFormatUnknown;
    /**
     * @hidden
     * @brief 视频帧颜色空间
     */
    ByteColorSpace color_space = kByteColorSpaceUnknown;
    /**
     * @brief 视频帧数据平面指针数组
     */
    uint8_t* data[kByteNumDataPointers];
    /**
     * @brief 视频帧数据平面行长度
     */
    int linesize[kByteNumDataPointers];
    /**
     * @brief sei 数据地址
     */
    uint8_t* extra_data = nullptr;
    /**
     * @brief sei 数据大小
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
     * @brief 视频旋转角度
     * @notes 目前支持 0,90,180，270 几种旋转角度
     */
    VideoRotation rotation = VideoRotation_0;
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
     * @brief 用户定义的视频帧释放回调函数指针，如果指针不为空，方法会被调用用来释放内存空间
     */
    int (*memory_deleter)(struct ByteVideoFrameBuilder* builder) = nullptr;
} ByteVideoFrameBuilder;

/**
 * @type api
 * @region 视频管理
 * @brief 视频帧
 */
class IByteVideoFrame {
public:
    /**
     * @type api
     * @region 视频管理
     * @brief 获取视频帧类型
     * @return 视频帧类型
     */
    virtual int frame_type() const = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取视频帧格式
     * @return 视频帧格式
     */
    virtual int pixel_format() const = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取视频帧时间戳
     * @return 视频帧时间戳,单位:微妙
     */
    virtual int64_t timestamp_us() const = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取视频帧宽度
     * @return 视频帧宽度
     */
    virtual int width() const = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取视频帧高度
     * @return 视频帧高度
     */
    virtual int height() const = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取视频帧旋转角度
     * @return 视频帧旋转角度
     */
    virtual int rotation() const = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取视频帧颜色空间
     * @return 视频帧颜色空间
     */
    virtual int color_space() const = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 视频帧颜色 plane 数量
     * @return 视频帧颜色 plane 数量
     * @notes yuv数据存储格式分为 plane 存储格式和pack存储格式，plane 格式中有 y，u，v 分开存储，pack 中 yuv 数据
     */
    virtual int number_of_planes() const = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取 plane 数据指针
     * @param [in] plane_index plane
     *        数据索引
     */
    virtual uint8_t* get_plane_data(int plane_index) = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取 plane 中数据行的长度
     * @param [in] plane_index plane
     *        数据索引
     */
    virtual int get_plane_line_size(int plane_index) = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 获取扩展数据指针
     * @param [in] size
     *        扩展数据字节数
     * @return 扩展数据的指针
     */
    virtual uint8_t* get_extra_data_info(int& size) const = 0;  // NOLINT
    /**
     * @type api
     * @region 视频管理
     * @brief 获取补充数据指针
     * @param [in] size
     *        补充数据字节数
     * @return 补充数据的指针
     */
    virtual uint8_t* get_supplementary_info(int& size) const = 0;  // NOLINT
    /**
     * @type api
     * @region 视频管理
     * @brief 获取本地缓冲区指针
     * @return 本地缓冲区指针
     */
    virtual void* get_hwaccel_buffer() = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 浅拷贝视频帧并返回指针
     * @return 浅拷贝的视频帧的指针
     */
    virtual IByteVideoFrame* shallow_copy() = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 释放视频帧
     */
    virtual void release() = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 视频帧数据转为 YUV I420 格式
     */
    virtual void to_i420() = 0;
    /**
     * @type api
     * @region 视频管理
     * @brief 根据视频帧参数创建视频帧并返回指针
     * @param ByteVideoFrameBuilder 视频帧创建类对象，详见 ByteVideoFrameBuilder：{@link #ByteVideoFrameBuilder}
     * @return 返回后的视频帧指针
     */
    static IByteVideoFrame* build_video_frame(const ByteVideoFrameBuilder& builder);

protected:
    /**
     * @brief 析构函数
     */
    virtual ~IByteVideoFrame() = default;
};

}  // namespace bytertc
#endif
