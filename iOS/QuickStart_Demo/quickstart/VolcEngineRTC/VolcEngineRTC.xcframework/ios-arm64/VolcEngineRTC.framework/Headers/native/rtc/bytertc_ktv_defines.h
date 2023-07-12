#ifndef BYTERTC_KTV_DEFINES_H
#define BYTERTC_KTV_DEFINES_H
#include <string>

namespace bytertc {

/** 
 * @type keytype
 * @brief 歌曲过滤方式。
 */
enum MusicFilterType {
    /** 
     * @brief 不过滤。
     */
    kFilterNone = 0,
    /** 
     * @brief 过滤没有歌词的歌曲。
     */
    kFilterWithoutLyric     = 1 << 0,
    /** 
     * @brief 过滤不支持打分的歌曲。
     */
    kFilterUnsupportedScore     = 1 << 1,
    /** 
     * @brief 过滤不支持伴唱切换的歌曲。
     */
    kFilterUnsupportedAccopmay  = 1 << 2,
    /** 
     * @brief 过滤没有高潮片段的歌曲。
     */
    kFilterUnsupportedClimx     = 1 << 3,
};

/** 
 * @type keytype
 * @brief 榜单类别。
 */
enum MusicHotType {
    /** 
     * @brief 火山内容中心热歌榜。
     */
    kHotContentCenter       = 1 << 0,
    /** 
     * @brief 项目热歌榜。
     */
    kHotProject          = 1 << 1,
};

/** 
 * @type keytype
 * @brief 原唱伴唱类型。
 */
enum class AudioTrackType {
    /** 
     * @brief 播放原唱。
     */
    kAudioTrackTypeOriginal = 1,
    /** 
     * @brief 播放伴唱。
     */
    kAudioTrackTypeAccompy = 2
};

/** 
 * @type keytype
 * @brief 音乐播放类型。
 */
enum class AudioPlayType {
    /** 
     * @brief 仅本地播放。
     */
    kAudioPlayTypeLocal,
    /** 
     * @brief 仅远端播放。
     */
    kAudioPlayTypeRemote,
    /** 
     * @brief 本地、远端同时播放。
     */
    kAudioPlayTypeLocalAndRemote
};

/** 
 * @type keytype
 * @brief 音乐播放状态。
 */
enum class PlayState {
    /** 
     * @brief 播放中。
     */
    kPlayStatePlaying = 1,
    /** 
     * @brief 暂停中。
     */
    kPlayStatePaused = 2,
    /** 
     * @brief 已停止。
     */
    kPlayStateStoped = 3,
    /** 
     * @brief 播放失败。
     */
    kPlayStateFailed = 4,
    /** 
     * @brief 播放结束。
     */
    kPlayStateFinished = 5,
};

/** 
 * @type keytype
 * @brief 歌词格式类型。
 */
enum class LyricStatus {
    /** 
     * @brief 无歌词。
     */
    kLyricStatusNone = 0,
    /** 
     * @brief KRC 歌词。
     */
    kLyricStatusKRC = 1,
    /** 
     * @brief LRC 歌词。
     */
    kLyricStatusLRC = 2,
    /** 
     * @brief KRC 歌词和 LRC 歌词均有。
     */
    kLyricStatusKRCAndLRC = 3
};

/** 
 * @type keytype
 * @brief 歌词文件类型。
 */
enum class DownloadLyricType {
    /** 
     * @brief KRC 歌词文件。
     */
    kDownKrc,
    /** 
     * @brief LRC 歌词文件。
     */
    kDownLrc
};



/** 
 * @type keytype
 * @brief 歌曲数据。
 */
struct MusicInfo
{
    /** 
     * @brief 音乐 ID。
     */
    const char*  music_id;
    /** 
     * @brief 音乐名称。
     */
    const char*  music_name;
    /** 
     * @brief 歌手。
     */
    const char*  singer;
    /** 
     * @brief 版权商 ID。
     */
    const char*  vendor_id;
    /** 
     * @brief 版权商名称。
     */
    const char* vendor_name;
    /** 
     * @brief 最新更新时间戳，单位为毫秒。
     */
    int64_t update_timestamp;
    /** 
     * @brief 封面地址。
     */
    const char*  poster_url;
    /** 
     * @brief 歌词格式类型，参看 LyricStatus{@link #LyricStatus}。
     */
    LyricStatus lyric_status;
    /** 
     * @brief 歌曲长度，单位为毫秒。
     */
    int duration;
    /** 
     * @brief 歌曲是否支持打分。
     */
    bool enable_score;
    /** 
     * @brief 歌曲高潮片段开始时间，单位为毫秒。
     */
    int climax_start_time;
    /** 
     * @brief 歌曲高潮片段停止时间，单位为毫秒。
     */
    int climax_stop_time;

};

/** 
 * @type keytype
 * @brief 热榜歌曲数据。
 */
struct HotMusicInfo {
    /** 
     * @brief 榜单类别，参看 MusicHotType{@link #MusicHotType}。
     */
    MusicHotType hot_type;
    /** 
     * @brief 热榜名称。
     */
    const char* hot_name;
    /** 
     * @brief 歌曲数据，参看 MusicInfo{@link #MusicInfo}。
     */
    MusicInfo* musics;
    /** 
     * @brief 歌曲列表的数量。
     */
    int music_count;
};

/** 
 * @type keytype
 * @brief 下载文件类型。
 */
enum DownloadFileType {
    /** 
     * @brief 音频文件。
     */
    kDownloadMusic = 1,
    /** 
     * @brief KRC 歌词文件。
     */
    kDownloadKRC = 2,
    /** 
     * @brief LRC 歌词文件。
     */
    kDownloadLRC = 3,
    /** 
     * @brief MIDI 文件。
     */
    kDownloadMIDI = 4

} ;

/** 
 * @type keytype
 * @brief 歌曲下载信息。
 */
struct DownloadResult {
    /** 
     * @brief 文件存放路径。
     */
    const char* local_file_path;
    /** 
     * @brief 音乐 ID。
     */
    const char* music_id;
    /** 
     * @brief 下载文件类型，参看 DownloadFileType{@link #DownloadFileType}。
     */
    DownloadFileType type;
};


/** 
 * @type keytype
 * @brief KTV 错误码。
 */
enum KTVErrorCode {
    /** 
     * @brief 成功。
     */
    kErrorCodeKTVOK = 0,
    /** 
     * @brief AppID 异常。
     */
    kErrorCodeKTVAppidInValid = -3000,
    /** 
     * @brief 非法参数，传入的参数不正确。
     */
    kErrorCodeKTVParasInValid = -3001,
    /** 
     * @brief 获取歌曲资源失败。
     */
    kErrorCodeKTVGetMusicFailed = -3002,
    /** 
     * @brief 获取歌词失败。
     */
    kErrorCodeKTVGetLyricFailed = -3003,
    /** 
     * @brief 歌曲下架。
     */
    kErrorCodeKTVMusicTakedown = -3004,
    /** 
     * @brief 歌曲文件下载失败。
     */
    kErrorCodeKTVMusicDownload = -3005,
    /** 
     * @brief MIDI 文件下载失败。
     */
    kErrorCodeKTVMidiDownloadFailed = -3006,
    /** 
     * @brief 系统繁忙。
     */
    kErrorCodeKTVSystemBusy = -3007,
    /** 
     * @brief 网络异常。
     */
    kErrorCodeKTVNetwork = -3008,
    /** 
     * @brief KTV 功能未加入房间。
     */
    kErrorCodeKTVNotJoinRoom = -3009,
    /** 
     * @brief 解析数据失败。
     */
    kErrorCodeKTVParseData = -3010,
    /** 
     * @brief 下载失败。
     */
    kErrorCodeKTVDownload = -3011,
    /** 
     * @brief 已在下载中。
     */
    kErrorCodeKTVDownloading = -3012,
    /** 
     * @brief 内部错误，联系技术支持人员。
     */
    kErrorCodeKTVInternalDomain = -3013
};

/** 
 * @type keytype
 * @brief KTV 播放器错误码。
 */
enum KTVPlayerErrorCode {
    /** 
     * @brief 成功。
     */
    kErrorCodeKTVPlayOK = 0,
    /** 
     * @brief 播放错误，请下载后播放。
     */
    kErrorCodeKTVPlayFileNotExist = -3020,
    /** 
     * @brief 播放错误，请确认文件播放格式。
     */
    kErrorCodeKTVPlayFileError = -3021,
    /** 
     * @brief 播放错误，未进入房间。
     */
    kErrorCodeKTVPlayNotJoinRoom = -3022,
    /** 
     * @brief 参数错误。
     */
    kErrorCodeKTVPlayParam = -3023,
    /** 
     * @brief 播放失败，找不到文件或文件打开失败。
     */
    kErrorCodeKTVPlayStartError = -3024,
    /** 
     * @brief 混音 ID 异常。
     */
    kErrorCodeKTVPlayMixIdError = -3025,
    /** 
     * @brief 设置播放位置出错。
     */
    kErrorCodeKTVPlayPositionError = -3026,
    /** 
     * @brief 音量参数不合法，可设置的取值范围为 [0,400]。
     */
    kErrorCodeKTVPlayAudioVolumeError = -3027,
    /** 
     * @brief 不支持此混音类型。
     */
    kErrorCodeKTVPlayTypeError = -3028,
    /** 
     * @brief 音调文件不合法。
     */
    kErrorCodeKTVPlayPitchError = -3029,
    /** 
     * @brief 音轨不合法。
     */
    kErrorCodeKTVPlayAudioTrackError = -3030,
    /** 
     * @brief 混音启动中。
     */
    kErrorCodeKTVPlayStartingError = -3031
};


} // namespace bytertc
#endif // BYTERTC_KTV_DEFINES_H
