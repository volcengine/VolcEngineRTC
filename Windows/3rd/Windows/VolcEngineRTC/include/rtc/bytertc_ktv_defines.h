#pragma once

#include <string>

namespace bytertc {

/**
 * @locale zh
 * @type keytype
 * @brief 歌曲过滤方式。
 */
/**
 * @locale en
 * @hidden currently not available currently not available
 * @type keytype
 * @brief The filter type of the music list.
 */
enum MusicFilterType {
    /**
     * @locale zh
     * @brief 不过滤。
     */
    /**
     * @locale en
     * @brief No filter.
     */
    kMusicFilterTypeNone = 0,
    /**
     * @locale zh
     * @brief 过滤没有歌词的歌曲。
     */
    /**
     * @locale en
     * @brief Remove music that does not have lyrics.
     */
    kMusicFilterTypeWithoutLyric     = 1 << 0,
    /**
     * @locale zh
     * @brief 过滤不支持打分的歌曲。
     */
    /**
     * @locale en
     * @brief Remove music that does not support scoring.
     */
    kMusicFilterTypeUnsupportedScore     = 1 << 1,
    /**
     * @locale zh
     * @brief 过滤不支持伴唱切换的歌曲。
     */
    /**
     * @locale en
     * @brief Remove music that does not support accompany mode.
     */
    kMusicFilterTypeUnsupportedAccopmay  = 1 << 2,
    /**
     * @locale zh
     * @brief 过滤没有高潮片段的歌曲。
     */
    /**
     * @locale en
     * @brief Remove music that does not have a climax part.
     */
    kMusicFilterTypeUnsupportedClimx     = 1 << 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 榜单类别。
 */
/**
 * @locale en
 * @hidden currently not available currently not available
 * @type keytype
 * @brief Hot music type.
 */
enum MusicHotType {
    /**
     * @locale zh
     * @brief 火山内容中心热歌榜。
     */
    /**
     * @locale en
     * @brief Hot music in the content center.
     */
    kMusicHotTypeContentCenter       = 1 << 0,
    /**
     * @locale zh
     * @brief 项目热歌榜。
     */
    /**
     * @locale en
     * @brief Hot music of the project.
     */
    kMusicHotTypeProject          = 1 << 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 原唱伴唱类型。
 */
/**
 * @locale en
 * @hidden currently not available currently not available
 * @type keytype
 * @brief Audio track type of the KTV player.
 */
enum class AudioTrackType {
    /**
     * @locale zh
     * @brief 播放原唱。
     */
    /**
     * @locale en
     * @brief Play the original music with vocals.
     */
    kOriginal = 1,
    /**
     * @locale zh
     * @brief 播放伴唱。
     */
    /**
     * @locale en
     * @brief Play the instrumental music without vocals.
     */
    kAccompy = 2
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
enum class AudioPlayType {
    /**
     * @locale zh
     * @brief 仅本地播放。
     */
    /**
     * @locale en
     * @brief Only play on the local side.
     */
    kLocal,
    /**
     * @locale zh
     * @brief 仅远端播放。
     */
    /**
     * @locale en
     * @brief Only play on the remote side.
     */
    kRemote,
    /**
     * @locale zh
     * @brief 本地、远端同时播放。
     */
    /**
     * @locale en
     * @brief Play on the local and remote side.
     */
    kLocalAndRemote
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
enum class PlayState {
    /**
     * @locale zh
     * @brief 播放中。
     */
    /**
     * @locale en
     * @brief Playing.
     */
    kPlaying = 1,
    /**
     * @locale zh
     * @brief 暂停中。
     */
    /**
     * @locale en
     * @brief Paused.
     */
    kPaused = 2,
    /**
     * @locale zh
     * @brief 已停止。
     */
    /**
     * @locale en
     * @brief Stopped.
     */
    kStoped = 3,
    /**
     * @locale zh
     * @brief 播放失败。
     */
    /**
     * @locale en
     * @brief Failed to play.
     */
    kFailed = 4,
    /**
     * @locale zh
     * @brief 播放结束。
     */
    /**
     * @locale en
     * @brief Finished.
     */
    kFinished = 5,
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
enum class LyricStatus {
    /**
     * @locale zh
     * @brief 无歌词。
     */
    /**
     * @locale en
     * @brief No lyrics.
     */
    kNone = 0,
    /**
     * @locale zh
     * @brief KRC 歌词。
     */
    /**
     * @locale en
     * @brief KRC lyrics.
     */
    kKRC = 1,
    /**
     * @locale zh
     * @brief LRC 歌词。
     */
    /**
     * @locale en
     * @brief LRC lyrics.
     */
    kLRC = 2,
    /**
     * @locale zh
     * @brief KRC 歌词和 LRC 歌词均有。
     */
    /**
     * @locale en
     * @brief KRC and LRC lyrics.
     */
    kKRCAndLRC = 3
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
enum class DownloadLyricType {
    /**
     * @locale zh
     * @brief KRC 歌词文件。
     */
    /**
     * @locale en
     * @brief KRC lyrics file.
     */
    kKRC,
    /**
     * @locale zh
     * @brief LRC 歌词文件。
     */
    /**
     * @locale en
     * @brief LRC lyrics file.
     */
    kLRC
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
struct MusicInfo
{
    /**
     * @locale zh
     * @brief 音乐 ID。
     */
    /**
     * @locale en
     * @brief Music ID.
     */
    const char*  music_id;
    /**
     * @locale zh
     * @brief 音乐名称。
     */
    /**
     * @locale en
     * @brief Music name.
     */
    const char*  music_name;
    /**
     * @locale zh
     * @brief 歌手。
     */
    /**
     * @locale en
     * @brief Singer.
     */
    const char*  singer;
    /**
     * @locale zh
     * @brief 版权商 ID。
     */
    /**
     * @locale en
     * @brief Vendor ID.
     */
    const char*  vendor_id;
    /**
     * @locale zh
     * @brief 版权商名称。
     */
    /**
     * @locale en
     * @brief Vendor name.
     */
    const char* vendor_name;
    /**
     * @locale zh
     * @brief 最新更新时间戳，单位为毫秒。
     */
    /**
     * @locale en
     * @brief Latest update timestamp in milliseconds.
     */
    int64_t update_timestamp;
    /**
     * @locale zh
     * @brief 封面地址。
     */
    /**
     * @locale en
     * @brief The URL of the music cover.
     */
    const char*  poster_url;
    /**
     * @locale zh
     * @brief 歌词格式类型，参看 LyricStatus{@link #LyricStatus}。
     */
    /**
     * @locale en
     * @brief The lyrics type. See LyricStatus{@link #LyricStatus}.
     */
    LyricStatus lyric_status;
    /**
     * @locale zh
     * @brief 歌曲长度，单位为毫秒。
     */
    /**
     * @locale en
     * @brief The length of the song in milliseconds.
     */
    int duration;
    /**
     * @locale zh
     * @brief 歌曲是否支持打分。
     */
    /**
     * @locale en
     * @brief Whether the song supports scoring.
     */
    bool enable_score;
    /**
     * @locale zh
     * @brief 歌曲高潮片段开始时间，单位为毫秒。
     */
    /**
     * @locale en
     * @brief The starting time of the climax part in milliseconds.
     */
    int climax_start_time;
    /**
     * @locale zh
     * @brief 歌曲高潮片段停止时间，单位为毫秒。
     */
    /**
     * @locale en
     * @brief The ending time of the climax part in milliseconds.
     */
     int climax_stop_time;

};

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
struct HotMusicInfo {
    /**
     * @locale zh
     * @brief 榜单类别，参看 MusicHotType{@link #MusicHotType}。
     */
    /**
     * @locale en
     * @brief Hot music type. See MusicHotType{@link #MusicHotType}.
     */
    MusicHotType hot_type;
    /**
     * @locale zh
     * @brief 热榜名称。
     */
    /**
     * @locale en
     * @brief Hot list name.
     */
    const char* hot_name;
    /**
     * @locale zh
     * @brief 歌曲数据，参看 MusicInfo{@link #MusicInfo}。
     */
    /**
     * @locale en
     * @brief Music information. See MusicInfo{@link #MusicInfo}.
     */
    MusicInfo* musics;
    /**
     * @locale zh
     * @brief 歌曲列表的数量。
     */
    /**
     * @locale en
     * @brief The number of music in the list.
     */
    int music_count;
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
enum DownloadFileType {
    /**
     * @locale zh
     * @brief 音频文件。
     */
    /**
     * @locale en
     * @brief Audio file.
     */
    kDownloadFileTypeMusic = 1,
    /**
     * @locale zh
     * @brief KRC 歌词文件。
     */
    /**
     * @locale en
     * @brief KRC lyrics file.
     */
    kDownloadFileTypeKRC = 2,
    /**
     * @locale zh
     * @brief LRC 歌词文件。
     */
    /**
     * @locale en
     * @brief LRC lyrics file.
     */
    kDownloadFileTypeLRC = 3,
    /**
     * @locale zh
     * @brief MIDI 文件。
     */
    /**
     * @locale en
     * @brief MIDI file.
     */
    kDownloadFileTypeMIDI = 4

} ;

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
struct DownloadResult {
    /**
     * @locale zh
     * @brief 文件存放路径。
     */
    /**
     * @locale en
     * @brief Download file path.
     */
    const char* local_file_path;
    /**
     * @locale zh
     * @brief 音乐 ID。
     */
    /**
     * @locale en
     * @brief Music ID.
     */
    const char* music_id;
    /**
     * @locale zh
     * @brief 下载文件类型，参看 DownloadFileType{@link #DownloadFileType}。
     */
    /**
     * @locale en
     * @brief Download file type. See DownloadFileType{@link #DownloadFileType}.
     */
    DownloadFileType type;
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
enum KTVErrorCode {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief Success.
     */
    kKTVErrorCodeOK = 0,
    /**
     * @locale zh
     * @brief AppID 异常。
     */
    /**
     * @locale en
     * @brief Invalid AppID.
     */
    kKTVErrorCodeAppidInValid = -3000,
    /**
     * @locale zh
     * @brief 非法参数，传入的参数不正确。
     */
    /**
     * @locale en
     * @brief Invalid parameter.
     */
    kKTVErrorCodeParasInValid = -3001,
    /**
     * @locale zh
     * @brief 获取歌曲资源失败。
     */
    /**
     * @locale en
     * @brief Failed to get music resources.
     */
    kKTVErrorCodeGetMusicFailed = -3002,
    /**
     * @locale zh
     * @brief 获取歌词失败。
     */
    /**
     * @locale en
     * @brief Failed to get lyrics.
     */
    kKTVErrorCodeGetLyricFailed = -3003,
    /**
     * @locale zh
     * @brief 歌曲下架。
     */
    /**
     * @locale en
     * @brief The music is removed.
     */
    kKTVErrorCodeMusicTakedown = -3004,
    /**
     * @locale zh
     * @brief 歌曲文件下载失败。
     */
    /**
     * @locale en
     * @brief Failed to download the music file.
     */
    kKTVErrorCodeMusicDownload = -3005,
    /**
     * @locale zh
     * @brief MIDI 文件下载失败。
     */
    /**
     * @locale en
     * @brief Failed to download the MIDI file.
     */
    kKTVErrorCodeMidiDownloadFailed = -3006,
    /**
     * @locale zh
     * @brief 系统繁忙。
     */
    /**
     * @locale en
     * @brief The system is busy.
     */
    kKTVErrorCodeSystemBusy = -3007,
    /**
     * @locale zh
     * @brief 网络异常。
     */
    /**
     * @locale en
     * @brief Network anomaly.
     */
    kKTVErrorCodeNetwork = -3008,
    /**
     * @locale zh
     * @brief KTV 功能未加入房间。
     */
    /**
     * @locale en
     * @brief The KTV feature is not added to the room.
     */
    kKTVErrorCodeNotJoinRoom = -3009,
    /**
     * @locale zh
     * @brief 解析数据失败。
     */
    /**
     * @locale en
     * @brief Failed to parse data.
     */
    kKTVErrorCodeParseData = -3010,
    /**
     * @locale zh
     * @hidden
     * @deprecated 从353开始。
     * @brief 下载失败。
     */
    /**
     * @locale en
     * @hidden
     * @deprecated since 353.
     * @brief Failed to download.
     */
    kKTVErrorCodeDownload = -3011,
    /**
     * @locale zh
     * @brief 已在下载中。
     */
    /**
     * @locale en
     * @brief Already downloading.
     */
    kKTVErrorCodeDownloading = -3012,
    /**
     * @locale zh
     * @brief 内部错误，联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Internal error. Contact the technical support representatives for help.
     */
    kKTVErrorCodeInternalDomain = -3013,
    /**
     * @locale zh
     * @brief 下载失败，磁盘空间不足。清除缓存后重试。
     */
    /**
     * @locale en
     * @brief Failed to download because of insufficient disk space. Please retry after clearing cache.
     */
    kKTVErrorCodeInsufficientDiskSpace = -3014,
    /**
     * @locale zh
     * @brief 下载失败，音乐文件解密失败，联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Failed to download because of music decryption failed. Contact the technical support representatives for help.
     */
    kKTVErrorCodeMusicDecryptionFailed = -3015,
    /**
     * @locale zh
     * @brief 下载失败，音乐文件重命名失败，请重试。
     */
    /**
     * @locale en
     * @brief Failed to download because of music rename failed. Please retry.
     */
    kKTVErrorCodeFileRenameFailed = -3016,
    /**
     * @locale zh
     * @brief 下载失败，下载超时，请重试。
     */
    /**
     * @locale en
     * @brief Failed to download because of network failure. Please retry.
     */
    kKTVErrorCodeDownloadTimeOut = -3017,
    /**
     * @locale zh
     * @brief 清除缓存失败，可能原因是文件被占用或者系统异常，请重试。
     */
    /**
     * @locale en
     * @brief Failed to clear cache because the file is occupied or the system is abnormal. Please retry.
     */
    kKTVErrorCodeClearCacheFailed = -3018,
    /**
     * @locale zh
     * @brief 取消下载。
     */
    /**
     * @locale en
     * @brief Cancel download task.
     */
    kKTVErrorCodeDownloadCanceled = -3019
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
enum KTVPlayerErrorCode {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief Success.
     */
    kKTVPlayerErrorCodeOK = 0,
    /**
     * @locale zh
     * @brief 播放错误，请下载后播放。
     */
    /**
     * @locale en
     * @brief Failed to play the music. Download first.
     */
    kKTVPlayerErrorCodeFileNotExist = -3020,
    /**
     * @locale zh
     * @brief 播放错误，请确认文件播放格式。
     */
    /**
     * @locale en
     * @brief Failed to play the music. Check the file's format.
     */
    kKTVPlayerErrorCodeFileError = -3021,
    /**
     * @locale zh
     * @brief 播放错误，未进入房间。
     */
    /**
     * @locale en
     * @brief Failed to play the music. Join a room first.
     */
    kKTVPlayerErrorCodeNotJoinRoom = -3022,
    /**
     * @locale zh
     * @brief 参数错误。
     */
    /**
     * @locale en
     * @brief Invalid parameter.
     */
    kKTVPlayerErrorCodeParam = -3023,
    /**
     * @locale zh
     * @brief 播放失败，找不到文件或文件打开失败。
     */
    /**
     * @locale en
     * @brief Failed to play the music. Invalid path or failed to open the file.
     */
    kKTVPlayerErrorCodeStartError = -3024,
    /**
     * @locale zh
     * @brief 混音 ID 异常。
     */
    /**
     * @locale en
     * @brief Invalid mixing ID.
     */
    kKTVPlayerErrorCodeMixIdError = -3025,
    /**
     * @locale zh
     * @brief 设置播放位置出错。
     */
    /**
     * @locale en
     * @brief Invalid position.
     */
    kKTVPlayerErrorCodePositionError = -3026,
    /**
     * @locale zh
     * @brief 音量参数不合法，可设置的取值范围为 [0,400]。
     */
    /**
     * @locale en
     * @brief Invalid volume.
     */
    kKTVPlayerErrorCodeAudioVolumeError = -3027,
    /**
     * @locale zh
     * @brief 不支持此混音类型。
     */
    /**
     * @locale en
     * @brief Do not support the mix type.
     */
    kKTVPlayerErrorCodeTypeError = -3028,
    /**
     * @locale zh
     * @brief 音调文件不合法。
     */
    /**
     * @locale en
     * @brief Invalid pitch.
     */
    kKTVPlayerErrorCodePitchError = -3029,
    /**
     * @locale zh
     * @brief 音轨不合法。
     */
    /**
     * @locale en
     * @brief Invalid audio track.
     */
    kKTVPlayerErrorCodeAudioTrackError = -3030,
    /**
     * @locale zh
     * @brief 混音启动中。
     */
    /**
     * @locale en
     * @brief Mixing in process.
     */
    kKTVPlayerErrorCodeStartingError = -3031
};


} // namespace bytertc
