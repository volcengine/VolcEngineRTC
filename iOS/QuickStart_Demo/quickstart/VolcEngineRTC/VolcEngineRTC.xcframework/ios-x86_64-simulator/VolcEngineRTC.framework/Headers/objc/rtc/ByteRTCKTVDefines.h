/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCRtsDefines
*/

#import "ByteRTCRtsDefines.h"

/** 
 * @type keytype
 * @brief 歌曲过滤方式。
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCKTVMusicFilterType) {
    /** 
     * @brief 不过滤。
     */
    ByteRTCKTVMusicFilterTypeNone                 = 0,
    /** 
     * @brief 过滤没有歌词的歌曲。
     */
    ByteRTCKTVMusicFilterTypeWithoutLyric         = 1 << 0,
    /** 
     * @brief 过滤不支持打分的歌曲。
     */
    ByteRTCKTVMusicFilterTypeUnsupportedScore     = 1 << 1,
    /** 
     * @brief 过滤不支持伴唱切换的歌曲。
     */
    ByteRTCKTVMusicFilterTypeUnsupportedAccopmay  = 1 << 2,
    /** 
     * @brief 过滤没有高潮片段的歌曲。
     */
    ByteRTCKTVMusicFilterTypeUnsupportedClimx     = 1 << 3,
};

/** 
 * @type keytype
 * @brief 榜单类别。
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCKTVMusicHotType) {
    /** 
     * @brief 火山内容中心热歌榜。
     */
    ByteRTCKTVMusicHotTypeContentCenter   = 1 << 0,
    /** 
     * @brief 项目热歌榜。
     */
    ByteRTCKTVMusicHotTypeProject         = 1 << 1,
    
};

/** 
 * @type keytype
 * @brief 音乐播放状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVPlayState) {
    /** 
     * @brief 播放中。
     */
    ByteRTCKTVPlayStatePlaying    = 1,
    /** 
     * @brief 暂停中。
     */
    ByteRTCKTVPlayStatePaused     = 2,
    /** 
     * @brief 已停止。
     */
    ByteRTCKTVPlayStateStoped     = 3,
    /** 
     * @brief 播放失败。
     */
    ByteRTCKTVPlayStateFailed     = 4,
    /** 
     * @brief 播放结束。
     */
    ByteRTCKTVPlayStateFinished   = 5,
};

/** 
 * @type keytype
 * @brief 原唱伴唱类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVAudioTrackType) {
    /** 
     * @brief 播放原唱。
     */
    ByteRTCKTVAudioTrackTypeOriginal    = 1,
    /** 
     * @brief 播放伴唱。
     */
    ByteRTCKTVAudioTrackTypeAccompy     = 2,
};

/** 
 * @type keytype
 * @brief 音乐播放类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVAudioPlayType) {
    /** 
     * @brief 仅本地播放。
     */
    ByteRTCKTVAudioPlayTypeLocal            = 0,
    /** 
     * @brief 仅远端播放。
     */
    ByteRTCKTVAudioPlayTypeRemote           = 1,
    /** 
     * @brief 本地、远端同时播放。
     */
    ByteRTCKTVAudioPlayTypeLocalAndRemote   = 2,
};

/** 
 * @type keytype
 * @brief 歌词格式类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVLyricStatus) {
    /** 
     * @brief 无歌词。
     */
    ByteRTCKTVLyricStatusNone         = 0,
    /** 
     * @brief KRC 歌词。
     */
    ByteRTCKTVLyricStatusKRC          = 1,
    /** 
     * @brief LRC 歌词。
     */
    ByteRTCKTVLyricStatusLRC          = 2,
    /** 
     * @brief KRC 歌词和 LRC 歌词均有。
     */
    ByteRTCKTVLyricStatusKRCAndLRC    = 3,
};

/** 
 * @type keytype
 * @brief 下载文件类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVDownloadFileType) {
    /** 
     * @brief 音频文件。
     */
    ByteRTCKTVDownloadFileTypeMusic     = 1,
    /** 
     * @brief KRC 歌词文件。
     */
    ByteRTCKTVDownloadFileTypeKRC       = 2,
    /** 
     * @brief LRC 歌词文件。
     */
    ByteRTCKTVDownloadFileTypeLRC       = 3,
    /** 
     * @brief MIDI 文件。
     */
    ByteRTCKTVDownloadFileTypeMIDI      = 4,
};

/** 
 * @type keytype
 * @brief 歌词文件类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVDownloadLyricType) {
    /** 
     * @brief KRC 歌词文件。
     */
    ByteRTCKTVDownloadLyricTypeKRC = 0,
    /** 
     * @brief LRC 歌词文件。
     */
    ByteRTCKTVDownloadLyricTypeLRC = 1,
};

/** 
 * @type keytype
 * @brief KTV 错误码。
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVError) {
    /** 
     * @brief 成功。
     */
    ByteRTCKTVErrorOK = 0,
    /** 
     * @brief AppID 异常。
     */
    ByteRTCKTVErrorAppidInValid = -3000,
    /** 
     * @brief 非法参数，传入的参数不正确。
     */
    ByteRTCKTVErrorParasInValid = -3001,
    /** 
     * @brief 获取歌曲资源失败。
     */
    ByteRTCKTVErrorGetMusicFailed = -3002,
    /** 
     * @brief 获取歌词失败。
     */
    ByteRTCKTVErrorGetLyricFailed = -3003,
    /** 
     * @brief 歌曲下架。
     */
    ByteRTCKTVErrorMusicTakedown = -3004,
    /** 
     * @brief 歌曲文件下载失败。
     */
    ByteRTCKTVErrorMusicDownload = -3005,
    /** 
     * @brief MIDI 文件下载失败。
     */
    ByteRTCKTVErrorMidiDownloadFailed = -3006,
    /** 
     * @brief 系统繁忙。
     */
    ByteRTCKTVErrorSystemBusy = -3007,
    /** 
     * @brief 网络异常。
     */
    ByteRTCKTVErrorNetwork = -3008,
    /** 
     * @brief KTV 功能未加入房间。
     */
    ByteRTCKTVErrorNotJoinRoom = -3009,
    /** 
     * @brief 解析数据失败。
     */
    ByteRTCKTVErrorParseData = -3010,
    /** 
     * @brief 下载失败。
     */
    ByteRTCKTVErrorDownload = -3011,
    /** 
     * @brief 已在下载中。
     */
    ByteRTCKTVErrorDownloading = -3012,
    /** 
     * @brief 内部错误，联系技术支持人员。
     */
    ByteRTCKTVErrorInternal = -3013
};

/** 
 * @type keytype
 * @brief KTV 播放器错误码。
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVPlayerError) {
    /** 
     * @brief 成功。
     */
    ByteRTCKTVPlayerErrorOK = 0,
    /** 
     * @brief 播放错误，请下载后播放。
     */
    ByteRTCKTVPlayerErrorFileNotExist = -3020,
    /** 
     * @brief 播放错误，请确认文件播放格式。
     */
    ByteRTCKTVPlayerErrorFileError = -3021,
    /** 
     * @brief 播放错误，未进入房间。
     */
    ByteRTCKTVPlayerErrorNotJoinRoom = -3022,
    /** 
     * @brief 参数错误。
     */
    ByteRTCKTVPlayerErrorParam = -3023,
    /** 
     * @brief 播放失败，找不到文件或文件打开失败。
     */
    ByteRTCKTVPlayerErrorStartError = -3024,
    /** 
     * @brief 混音 ID 异常。
     */
    ByteRTCKTVPlayerErrorMixIdError = -3025,
    /** 
     * @brief 设置播放位置出错。
     */
    ByteRTCKTVPlayerErrorPositionError = -3026,
    /** 
     * @brief 音量参数不合法，可设置的取值范围为 [0,400]。
     */
    ByteRTCKTVPlayerErrorAudioVolumeError = -3027,
    /** 
     * @brief 不支持此混音类型。
     */
    ByteRTCKTVPlayerErrorTypeError = -3028,
    /** 
     * @brief 音调文件不合法。
     */
    ByteRTCKTVPlayerErrorPitchError = -3029,
    /** 
     * @brief 音轨不合法。
     */
    ByteRTCKTVPlayerErrorAudioTrackError = -3030,
    /** 
     * @brief 混音启动中。
     */
    ByteRTCKTVPlayerErrorStartingError = -3031,
};

/** 
 * @type keytype
 * @brief 歌曲数据。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCKTVMusic : NSObject
/** 
 * @brief 音乐 ID。
 */
@property (nonatomic, copy) NSString * _Nonnull musicId;
/** 
 * @brief 音乐名称。
 */
@property (nonatomic, copy) NSString * _Nonnull musicName;
/** 
 * @brief 歌手。
 */
@property (nonatomic, copy) NSString * _Nonnull singer;
/** 
 * @brief 版权商 ID。
 */
@property (nonatomic, copy) NSString * _Nonnull vendorId;
/** 
 * @brief 版权商名称。
 */
@property (nonatomic, copy) NSString * _Nonnull vendorName;
/** 
 * @brief 最新更新时间戳，单位为毫秒。
 */
@property (nonatomic, assign) int64_t updateTimestamp;
/** 
 * @brief 封面地址。
 */
@property (nonatomic, copy) NSString * _Nonnull posterUrl;
/** 
 * @brief 歌词格式类型，参看 ByteRTCKTVLyricStatus{@link #ByteRTCKTVLyricStatus}。
 */
@property (nonatomic, assign) ByteRTCKTVLyricStatus lyricStatus;
/** 
 * @brief 歌曲长度，单位为毫秒。
 */
@property (nonatomic, assign) int duration;
/** 
 * @brief 歌曲是否支持打分。
 */
@property (nonatomic, assign) BOOL enableScore;
/** 
 * @brief 歌曲高潮片段开始时间，单位为毫秒。
 */
@property (nonatomic, assign) int climaxStartTime;
/** 
 * @brief 歌曲高潮片段停止时间，单位为毫秒。
 */
@property (nonatomic, assign) int climaxEndTime;
@end

/** 
 * @type keytype
 * @brief 热榜歌曲数据。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCKTVHotMusicInfo : NSObject
/** 
 * @brief 榜单类别，参看 ByteRTCKTVMusicHotType{@link #ByteRTCKTVMusicHotType}。
 */
@property (nonatomic, assign) ByteRTCKTVMusicHotType hotType;
/** 
 * @brief 热榜名称。
 */
@property (nonatomic, copy) NSString * _Nullable hotName;
/** 
 * @brief 歌曲数据，参看 ByteRTCKTVMusic{@link #ByteRTCKTVMusic}。
 */
@property (nonatomic, copy) NSArray<ByteRTCKTVMusic *> * _Nullable musics;
@end

/** 
 * @type keytype
 * @brief 歌曲下载信息。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCKTVDownloadResult : NSObject
/** 
 * @brief 音乐 ID。
 */
@property (nonatomic, copy) NSString * _Nonnull musicId;
/** 
 * @brief 下载文件类型，参看 ByteRTCKTVDownloadFileType{@link #ByteRTCKTVDownloadFileType}。
 */
@property (nonatomic, assign) ByteRTCKTVDownloadFileType fileType;
/** 
 * @brief 文件存放路径。
 */
@property (nonatomic, copy) NSString * _Nullable filePath;

@end

