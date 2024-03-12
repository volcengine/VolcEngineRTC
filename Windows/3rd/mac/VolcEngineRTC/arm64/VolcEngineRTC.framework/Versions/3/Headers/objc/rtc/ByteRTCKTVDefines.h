/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCRtsDefines
*/

#import "ByteRTCRtsDefines.h"

/**
 * @locale zh
 * @type keytype
 * @brief 歌曲过滤方式。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief The filter type of the music list.
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCMusicFilterType) {
    /**
     * @locale zh
     * @brief 不过滤。
     */
    /**
     * @locale en
     * @brief No filter.
     */
    ByteRTCMusicFilterTypeNone                 = 0,
    /**
     * @locale zh
     * @brief 过滤没有歌词的歌曲。
     */
    /**
     * @locale en
     * @brief Remove music that does not have lyrics.
     */
    ByteRTCMusicFilterTypeWithoutLyric         = 1 << 0,
    /**
     * @locale zh
     * @brief 过滤不支持打分的歌曲。
     */
    /**
     * @locale en
     * @brief Remove music that does not support scoring.
     */
    ByteRTCMusicFilterTypeUnsupportedScore     = 1 << 1,
    /**
     * @locale zh
     * @brief 过滤不支持伴唱切换的歌曲。
     */
    /**
     * @locale en
     * @brief Remove music that does not support accompany mode.
     */
    ByteRTCMusicFilterTypeUnsupportedAccopmay  = 1 << 2,
    /**
     * @locale zh
     * @brief 过滤没有高潮片段的歌曲。
     */
    /**
     * @locale en
     * @brief Remove music that does not have a climax part.
     */
    ByteRTCMusicFilterTypeUnsupportedClimx     = 1 << 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 榜单类别。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Hot music type.
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCMusicHotType) {
    /**
     * @locale zh
     * @brief 火山内容中心热歌榜。
     */
    /**
     * @locale en
     * @brief Hot music in the content center.
     */
    ByteRTCMusicHotTypeContentCenter   = 1 << 0,
    /**
     * @locale zh
     * @brief 项目热歌榜。
     */
    /**
     * @locale en
     * @brief Hot music of the project.
     */
    ByteRTCMusicHotTypeProject         = 1 << 1,
    
};

/**
 * @locale zh
 * @type keytype
 * @brief 音乐播放状态。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Music playing status.
 */
typedef NS_ENUM(NSInteger, ByteRTCPlayState) {
    /**
     * @locale zh
     * @brief 播放中。
     */
    /**
     * @locale en
     * @brief Playing.
     */
    ByteRTCPlayStatePlaying    = 1,
    /**
     * @locale zh
     * @brief 暂停中。
     */
    /**
     * @locale en
     * @brief Paused.
     */
    ByteRTCPlayStatePaused     = 2,
    /**
     * @locale zh
     * @brief 已停止。
     */
    /**
     * @locale en
     * @brief Stopped.
     */
    ByteRTCPlayStateStoped     = 3,
    /**
     * @locale zh
     * @brief 播放失败。
     */
    /**
     * @locale en
     * @brief Failed to play.
     */
    ByteRTCPlayStateFailed     = 4,
    /**
     * @locale zh
     * @brief 播放结束。
     */
    /**
     * @locale en
     * @brief Finished.
     */
    ByteRTCPlayStateFinished   = 5,
};

/**
 * @locale zh
 * @type keytype
 * @brief 原唱伴唱类型。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Audio track type of the KTV player.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioTrackType) {
    /**
     * @locale zh
     * @brief 播放原唱。
     */
    /**
     * @locale en
     * @brief Play the original music with vocals.
     */
    ByteRTCAudioTrackTypeOriginal    = 1,
    /**
     * @locale zh
     * @brief 播放伴唱。
     */
    /**
     * @locale en
     * @brief Play the instrumental music without vocals.
     */
    ByteRTCAudioTrackTypeAccompy     = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音乐播放类型。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Audio play type.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioPlayType) {
    /**
     * @locale zh
     * @brief 仅本地播放。
     */
    /**
     * @locale en
     * @brief Only play on the local side.
     */
    ByteRTCAudioPlayTypeLocal            = 0,
    /**
     * @locale zh
     * @brief 仅远端播放。
     */
    /**
     * @locale en
     * @brief Only play on the remote side.
     */
    ByteRTCAudioPlayTypeRemote           = 1,
    /**
     * @locale zh
     * @brief 本地、远端同时播放。
     */
    /**
     * @locale en
     * @brief Play on the local and remote side.
     */
    ByteRTCAudioPlayTypeLocalAndRemote   = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 歌词格式类型。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief The lyrics type.
 */
typedef NS_ENUM(NSInteger, ByteRTCLyricStatus) {
    /**
     * @locale zh
     * @brief 无歌词。
     */
    /**
     * @locale en
     * @brief No lyrics.
     */
    ByteRTCLyricStatusNone         = 0,
    /**
     * @locale zh
     * @brief KRC 歌词。
     */
    /**
     * @locale en
     * @brief KRC lyrics.
     */
    ByteRTCLyricStatusKRC          = 1,
    /**
     * @locale zh
     * @brief LRC 歌词。
     */
    /**
     * @locale en
     * @brief LRC lyrics.
     */
    ByteRTCLyricStatusLRC          = 2,
    /**
     * @locale zh
     * @brief KRC 歌词和 LRC 歌词均有。
     */
    /**
     * @locale en
     * @brief KRC and LRC lyrics.
     */
    ByteRTCLyricStatusKRCAndLRC    = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 下载文件类型。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Download file type.
 */
typedef NS_ENUM(NSInteger, ByteRTCDownloadFileType) {
    /**
     * @locale zh
     * @brief 音频文件。
     */
    /**
     * @locale en
     * @brief Audio file.
     */
    ByteRTCDownloadFileTypeMusic     = 1,
    /**
     * @locale zh
     * @brief KRC 歌词文件。
     */
    /**
     * @locale en
     * @brief KRC lyrics file.
     */
    ByteRTCDownloadFileTypeKRC       = 2,
    /**
     * @locale zh
     * @brief LRC 歌词文件。
     */
    /**
     * @locale en
     * @brief LRC lyrics file.
     */
    ByteRTCDownloadFileTypeLRC       = 3,
    /**
     * @locale zh
     * @brief MIDI 文件。
     */
    /**
     * @locale en
     * @brief MIDI file.
     */
    ByteRTCDownloadFileTypeMIDI      = 4,
};

/**
 * @locale zh
 * @type keytype
 * @brief 歌词文件类型。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief The lyrics file's format.
 */
typedef NS_ENUM(NSInteger, ByteRTCDownloadLyricType) {
    /**
     * @locale zh
     * @brief KRC 歌词文件。
     */
    /**
     * @locale en
     * @brief KRC lyrics file.
     */
    ByteRTCDownloadLyricTypeKRC = 0,
    /**
     * @locale zh
     * @brief LRC 歌词文件。
     */
    /**
     * @locale en
     * @brief LRC lyrics file.
     */
    ByteRTCDownloadLyricTypeLRC = 1,
};

/**
 * @locale zh
 * @type errorcode
 * @brief KTV 错误码。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type errorcode
 * @brief KTV error code.
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVErrorCode) {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief Success.
     */
    ByteRTCKTVErrorCodeOK = 0,
    /**
     * @locale zh
     * @brief AppID 异常。
     */
    /**
     * @locale en
     * @brief Invalid AppID.
     */
    ByteRTCKTVErrorCodeAppidInValid = -3000,
    /**
     * @locale zh
     * @brief 非法参数，传入的参数不正确。
     */
    /**
     * @locale en
     * @brief Invalid parameter.
     */
    ByteRTCKTVErrorCodeParasInValid = -3001,
    /**
     * @locale zh
     * @brief 获取歌曲资源失败。
     */
    /**
     * @locale en
     * @brief Failed to get music resources.
     */
    ByteRTCKTVErrorCodeGetMusicFailed = -3002,
    /**
     * @locale zh
     * @brief 获取歌词失败。
     */
    /**
     * @locale en
     * @brief Failed to get lyrics.
     */
    ByteRTCKTVErrorCodeGetLyricFailed = -3003,
    /**
     * @locale zh
     * @brief 歌曲下架。
     */
    /**
     * @locale en
     * @brief The music is removed.
     */
    ByteRTCKTVErrorCodeMusicTakedown = -3004,
    /**
     * @locale zh
     * @brief 歌曲文件下载失败。
     */
    /**
     * @locale en
     * @brief Failed to download the music file.
     */
    ByteRTCKTVErrorCodeMusicDownload = -3005,
    /**
     * @locale zh
     * @brief MIDI 文件下载失败。
     */
    /**
     * @locale en
     * @brief Failed to download the MIDI file.
     */
    ByteRTCKTVErrorCodeMidiDownloadFailed = -3006,
    /**
     * @locale zh
     * @brief 系统繁忙。
     */
    /**
     * @locale en
     * @brief The system is busy.
     */
    ByteRTCKTVErrorCodeSystemBusy = -3007,
    /**
     * @locale zh
     * @brief 网络异常。
     */
    /**
     * @locale en
     * @brief Network anomaly.
     */
    ByteRTCKTVErrorCodeNetwork = -3008,
    /**
     * @locale zh
     * @brief KTV 功能未加入房间。
     */
    /**
     * @locale en
     * @brief The KTV feature is not added to the room.
     */
    ByteRTCKTVErrorCodeNotJoinRoom = -3009,
    /**
     * @locale zh
     * @brief 解析数据失败。
     */
    /**
     * @locale en
     * @brief Failed to parse data.
     */
    ByteRTCKTVErrorCodeParseData = -3010,
    /**
     * @locale zh
     * @hidden
     * @deprecated 从353开始
     * @brief 下载失败。
     */
    /**
     * @locale en
     * @hidden
     * @deprecated since 353.
     * @brief Failed to download.
     */
    ByteRTCKTVErrorCodeDownload = -3011,
    /**
     * @locale zh
     * @brief 已在下载中。
     */
    /**
     * @locale en
     * @brief Already downloading.
     */
    ByteRTCKTVErrorCodeDownloading = -3012,
    /**
     * @locale zh
     * @brief 内部错误，联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Internal error. Contact the technical support representatives for help.
     */
    ByteRTCKTVErrorCodeInternal = -3013,
    /**
     * @locale zh
     * @brief 下载失败，磁盘空间不足。清除缓存后重试。
     */
    /**
     * @locale en
     * @brief Failed to download because of insufficient disk space. Please retry after clearing cache.
     */
    ByteRTCKTVErrorCodeInsufficientDiskSpace = -3014,
    /**
     * @locale zh
     * @brief 下载失败，音乐文件解密失败，联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Failed to download because of music decryption failed. Contact the technical support representatives for help.
     */
    ByteRTCKTVErrorCodeMusicDecryptionFailed = -3015,
    /**
     * @locale zh
     * @brief 下载失败，音乐文件重命名失败，请重试。
     */
    /**
     * @locale en
     * @brief Failed to download because of music rename failed. Please retry.
     */
    ByteRTCKTVErrorCodeFileRenameFailed = -3016,
    /**
     * @locale zh
     * @brief 下载失败，下载超时，请重试。
     */
    /**
     * @locale en
     * @brief Failed to download because of network failure. Please retry.
     */
    ByteRTCKTVErrorCodeDownloadTimeOut = -3017,
    /**
     * @locale zh
     * @brief 清除缓存失败，可能原因是文件被占用或者系统异常，请重试。
     */
    /**
     * @locale en
     * @brief Failed to clear cache because the file is occupied or the system is abnormal. Please retry.
     */
    ByteRTCKTVErrorCodeClearCacheFailed = -3018,
    /**
     * @locale zh
     * @brief 取消下载。
     */
    /**
     * @locale en
     * @brief Cancel download task.
     */
    ByteRTCKTVErrorCodeDownloadCanceled = -3019
};

/**
 * @locale zh
 * @type keytype
 * @brief KTV 播放器错误码。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief KTV player error code.
 */
typedef NS_ENUM(NSInteger, ByteRTCKTVPlayerErrorCode) {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief Success.
     */
    ByteRTCKTVPlayerErrorCodeOK = 0,
    /**
     * @locale zh
     * @brief 播放错误，请下载后播放。
     */
    /**
     * @locale en
     * @brief Failed to play the music. Download first.
     */
    ByteRTCKTVPlayerErrorCodeFileNotExist = -3020,
    /**
     * @locale zh
     * @brief 播放错误，请确认文件播放格式。
     */
    /**
     * @locale en
     * @brief Failed to play the music. Check the file's format.
     */
    ByteRTCKTVPlayerErrorCodeFileError = -3021,
    /**
     * @locale zh
     * @brief 播放错误，未进入房间。
     */
    /**
     * @locale en
     * @brief Failed to play the music. Join a room first.
     */
    ByteRTCKTVPlayerErrorCodeNotJoinRoom = -3022,
    /**
     * @locale zh
     * @brief 参数错误。
     */
    /**
     * @locale en
     * @brief Invalid parameter.
     */
    ByteRTCKTVPlayerErrorCodeParam = -3023,
    /**
     * @locale zh
     * @brief 播放失败，找不到文件或文件打开失败。
     */
    /**
     * @locale en
     * @brief Failed to play the music. Invalid path or failed to open the file.
     */
    ByteRTCKTVPlayerErrorCodeStartError = -3024,
    /**
     * @locale zh
     * @brief 混音 ID 异常。
     */
    /**
     * @locale en
     * @brief Invalid mixing ID.
     */
    ByteRTCKTVPlayerErrorCodeMixIdError = -3025,
    /**
     * @locale zh
     * @brief 设置播放位置出错。
     */
    /**
     * @locale en
     * @brief Invalid position.
     */
    ByteRTCKTVPlayerErrorCodePositionError = -3026,
    /**
     * @locale zh
     * @brief 音量参数不合法，可设置的取值范围为 [0,400]。
     */
    /**
     * @locale en
     * @brief Invalid volume.
     */
    ByteRTCKTVPlayerErrorCodeAudioVolumeError = -3027,
    /**
     * @locale zh
     * @brief 不支持此混音类型。
     */
    /**
     * @locale en
     * @brief Do not support the mix type.
     */
    ByteRTCKTVPlayerErrorCodeTypeError = -3028,
    /**
     * @locale zh
     * @brief 音调文件不合法。
     */
    /**
     * @locale en
     * @brief Invalid pitch.
     */
    ByteRTCKTVPlayerErrorCodePitchError = -3029,
    /**
     * @locale zh
     * @brief 音轨不合法。
     */
    /**
     * @locale en
     * @brief Invalid audio track.
     */
    ByteRTCKTVPlayerErrorCodeAudioTrackError = -3030,
    /**
     * @locale zh
     * @brief 混音启动中。
     */
    /**
     * @locale en
     * @brief Mixing in process.
     */
    ByteRTCKTVPlayerErrorCodeStartingError = -3031,
};

/**
 * @locale zh
 * @type keytype
 * @brief 歌曲数据。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Music information.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMusicInfo : NSObject
/**
 * @locale zh
 * @brief 音乐 ID。
 */
/**
 * @locale en
 * @brief Music ID.
 */
@property (nonatomic, copy) NSString * _Nonnull musicId;
/**
 * @locale zh
 * @brief 音乐名称。
 */
/**
 * @locale en
 * @brief Music name.
 */
@property (nonatomic, copy) NSString * _Nonnull musicName;
/**
 * @locale zh
 * @brief 歌手。
 */
/**
 * @locale en
 * @brief Singer.
 */
@property (nonatomic, copy) NSString * _Nonnull singer;
/**
 * @locale zh
 * @brief 版权商 ID。
 */
/**
 * @locale en
 * @brief Vendor ID.
 */
@property (nonatomic, copy) NSString * _Nonnull vendorId;
/**
 * @locale zh
 * @brief 版权商名称。
 */
/**
 * @locale en
 * @brief Vendor name.
 */
@property (nonatomic, copy) NSString * _Nonnull vendorName;
/**
 * @locale zh
 * @brief 最新更新时间戳，单位为毫秒。
 */
/**
 * @locale en
 * @brief Latest update timestamp in milliseconds.
 */
@property (nonatomic, assign) int64_t updateTimestamp;
/**
 * @locale zh
 * @brief 封面地址。
 */
/**
 * @locale en
 * @brief The URL of the music cover.
 */
@property (nonatomic, copy) NSString * _Nonnull posterUrl;
/**
 * @locale zh
 * @brief 歌词格式类型，参看 ByteRTCLyricStatus{@link #ByteRTCLyricStatus}。
 */
/**
 * @locale en
 * @brief The lyrics type. See ByteRTCLyricStatus{@link #ByteRTCLyricStatus}.
 */
@property (nonatomic, assign) ByteRTCLyricStatus lyricStatus;
/**
 * @locale zh
 * @brief 歌曲长度，单位为毫秒。
 */
/**
 * @locale en
 * @brief The length of the song in milliseconds.
 */
@property (nonatomic, assign) int duration;
/**
 * @locale zh
 * @brief 歌曲是否支持打分。
 */
/**
 * @locale en
 * @brief Whether the song supports scoring.
 */
@property (nonatomic, assign) BOOL enableScore;
/**
 * @locale zh
 * @brief 歌曲高潮片段开始时间，单位为毫秒。
 */
/**
 * @locale en
 * @brief The starting time of the climax part in milliseconds.
 */
@property (nonatomic, assign) int climaxStartTime;
/**
 * @locale zh
 * @brief 歌曲高潮片段停止时间，单位为毫秒。
 */
/**
 * @locale en
 * @brief The ending time of the climax part in milliseconds.
 */
@property (nonatomic, assign) int climaxEndTime;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 热榜歌曲数据。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Hot music information.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCHotMusicInfo : NSObject
/**
 * @locale zh
 * @brief 榜单类别，参看 ByteRTCMusicHotType{@link #ByteRTCMusicHotType}。
 */
/**
 * @locale en
 * @brief Hot music type. See ByteRTCMusicHotType{@link #ByteRTCMusicHotType}.
 */
@property (nonatomic, assign) ByteRTCMusicHotType hotType;
/**
 * @locale zh
 * @brief 热榜名称。
 */
/**
 * @locale en
 * @brief Hot list name.
 */
@property (nonatomic, copy) NSString * _Nullable hotName;
/**
 * @locale zh
 * @brief 歌曲数据，参看 ByteRTCMusicInfo{@link #ByteRTCMusicInfo}。
 */
/**
 * @locale en
 * @brief Music information. See ByteRTCMusicInfo{@link #ByteRTCMusicInfo}.
 */
@property (nonatomic, copy) NSArray<ByteRTCMusicInfo *> * _Nullable musics;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 歌曲下载信息。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Download music information.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCDownloadResult : NSObject
/**
 * @locale zh
 * @brief 音乐 ID。
 */
/**
 * @locale en
 * @brief Music ID.
 */
@property (nonatomic, copy) NSString * _Nonnull musicId;
/**
 * @locale zh
 * @brief 下载文件类型，参看 ByteRTCDownloadFileType{@link #ByteRTCDownloadFileType}。
 */
/**
 * @locale en
 * @brief Download file type. See ByteRTCDownloadFileType{@link #ByteRTCDownloadFileType}.
 */
@property (nonatomic, assign) ByteRTCDownloadFileType fileType;
/**
 * @locale zh
 * @brief 文件存放路径。
 */
/**
 * @locale en
 * @brief Download file path.
 */
@property (nonatomic, copy) NSString * _Nullable filePath;

@end

