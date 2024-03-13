#pragma once

#include "bytertc_ktv_defines.h"
namespace bytertc {

/**
 * @locale zh
 * @type callback
 * @brief KTV 事件回调接口。<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief KTV manager event handler.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IKTVManagerEventHandler {

public:
    /**
     * @hidden Constructor/Destructor
     * @brief Destructor
     */
    virtual ~IKTVManagerEventHandler() {
    }

    /**
     * @locale zh
     * @type callback
     * @brief 歌曲列表回调。
     * @param music_infos 歌曲数据数组，参看 MusicInfo{@link #MusicInfo}。
     * @param music_count 当前查询的数据条目数。
     * @param total_musics_size 数据条目总数。
     * @param error_code 错误码，成功时返回 0，其余值参看 KTVErrorCode{@link #KTVErrorCode}。
     */
    /**
     * @locale en
     * @type callback
     * @brief The music list callback.
     * @param music_infos Array of the music information. See MusicInfo{@link #MusicInfo}.
     * @param music_count The size of the requested music list.
     * @param total_musics_size The total size of the music list.
     * @param error_code Error code. The value 0 indicates success. For the indications of other values, see KTVErrorCode{@link #KTVErrorCode}.
     */
    virtual void onMusicListResult(MusicInfo* music_infos, int music_count, int total_musics_size, KTVErrorCode error_code) {
        (void)music_infos;
        (void)music_count;
        (void)total_musics_size;
        (void)error_code;
    }

    /**
     * @locale zh
     * @type callback
     * @brief 搜索歌曲结果回调。
     * @param music_infos 歌曲数据数组，参看 MusicInfo{@link #MusicInfo}。
     * @param music_count 当前查询的数据条目数。
     * @param total_musics_size 数据条目总数。
     * @param error_code 错误码，成功时返回 0，其余值参看 KTVErrorCode{@link #KTVErrorCode}。
     */
    /**
     * @locale en
     * @type callback
     * @brief The search music callback.
     * @param music_infos Array of the music information. See MusicInfo{@link #MusicInfo}.
     * @param music_count The size of the requested music list.
     * @param total_musics_size The total size of the music list.
     * @param error_code Error code. The value 0 indicates success. For the indications of other values, see KTVErrorCode{@link #KTVErrorCode}.
     */
    virtual void onSearchMusicResult(MusicInfo* music_infos, int music_count, int total_musics_size, KTVErrorCode error_code) {
        (void)music_infos;
        (void)music_count;
        (void)total_musics_size;
        (void)error_code;
    }

    /**
     * @locale zh
     * @type callback
     * @brief 热榜歌曲结果回调。
     * @param hot_infos 热榜歌曲数据数组，参看 HotMusicInfo{@link #HotMusicInfo}。
     * @param hot_count 当前查询的热榜歌曲数据条目数。
     * @param error_code 错误码，成功时返回 0，其余值参看 KTVErrorCode{@link #KTVErrorCode}。
     */
    /**
     * @locale en
     * @type callback
     * @brief The hot music callback.
     * @param hot_infos Array of the hot music information. See HotMusicInfo{@link #HotMusicInfo}.
     * @param hot_count The size of the requested hot music list.
     * @param error_code Error code. The value 0 indicates success. For the indications of other values, see KTVErrorCode{@link #KTVErrorCode}.
     */
    virtual void onHotMusicResult(HotMusicInfo* hot_infos, int hot_count, KTVErrorCode error_code) {
        (void)hot_infos;
        (void)hot_count;
        (void)error_code;
    }

    /**
     * @locale zh
     * @type callback
     * @brief 歌曲详细信息回调。
     * @param music_info 歌曲数据，参看 MusicInfo{@link #MusicInfo}。
     * @param error_code 错误码，成功时返回 0，其余值参看 KTVErrorCode{@link #KTVErrorCode}。<br>

     */
    /**
     * @locale en
     * @type callback
     * @brief The music detail callback.
     * @param music_info Music information. See MusicInfo{@link #MusicInfo}.
     * @param error_code Error code. The value 0 indicates success. For the indications of other values, see KTVErrorCode{@link #KTVErrorCode}.
     */
    virtual void onMusicDetailResult(MusicInfo* music_info, KTVErrorCode error_code) {
        (void)music_info;
        (void)error_code;        
    }

    /**
     * @locale zh
     * @type callback
     * @brief 下载成功回调。
     * @param download_id 下载任务 ID。
     * @param download_info 下载信息，参看 DownloadResult{@link #DownloadResult}。
     */
    /**
     * @locale en
     * @type callback
     * @brief Download success callback.
     * @param download_id Download task ID.
     * @param download_info Download result. See DownloadResult{@link #DownloadResult}.
     */
    virtual void onDownloadSuccess(int download_id, DownloadResult* download_info) {
        (void)download_id;
        (void)download_info; 
    }

    /**
     * @locale zh
     * @type callback
     * @brief 下载失败回调。
     * @param download_id 下载任务 ID。
     * @param error_code 错误码，参看 KTVErrorCode{@link #KTVErrorCode}。
     */
    /**
     * @locale en
     * @type callback
     * @brief Download failure callback.
     * @param download_id Download task ID.
     * @param error_code Error code. See KTVErrorCode{@link #KTVErrorCode}.
     */
    virtual void onDownloadFailed(int download_id, KTVErrorCode error_code) {
        (void)download_id;
        (void)error_code; 
    }

    /**
     * @locale zh
     * @type callback
     * @brief 歌曲文件下载进度回调。
     * @param download_id 下载任务 ID。
     * @param download_percentage 下载进度百分比，取值范围 [0,100]。
     */
    /**
     * @locale en
     * @type callback
     * @brief Music file download progress callback.
     * @param download_id Download task ID.
     * @param download_percentage The percentage of download progress, in the range of [0,100].
     */
    virtual void onDownloadMusicProgress(int download_id, int download_percentage) {
        (void)download_id;
        (void)download_percentage;
    }
    /**
     * @locale zh
     * @type callback
     * @brief 清理文件缓存结果回调。
     * @param error_code 错误码，非0为失败，参看 KTVErrorCode{@link #KTVErrorCode}。
     */
    /**
     * @locale en
     * @type callback
     * @brief Clear Cache result callback.
     * @param error_code Error code. See KTVErrorCode{@link #KTVErrorCode}.
     */
    virtual void onClearCacheResult(KTVErrorCode error_code) {
        (void)error_code;
    }
};

/**
 * @locale zh
 * @type callback
 * @brief KTV 播放器回调接口。<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief KTV player event handler.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IKTVPlayerEventHandler {
public:
    /**
     * @hidden Constructor/Destructor
     * @brief Destructor
     */
    virtual ~IKTVPlayerEventHandler() {
    }
    
    /**
     * @locale zh
     * @type callback
     * @brief 音乐播放进度回调。
     * @param music_id 音乐 ID。
     * @param progress 音乐播放进度，单位为毫秒。
     */
    /**
     * @locale en
     * @type callback
     * @brief Music playing progress callback.
     * @param music_id Music ID.
     * @param progress Music playing progress in milliseconds.
     */
    virtual void onPlayProgress(const char *music_id, int64_t progress) {
        (void)music_id;
        (void)progress;
    }
    
    /**
     * @locale zh
     * @type callback
     * @brief 音乐播放状态改变回调。
     * @param music_id 音乐 ID。
     * @param play_state 音乐播放状态，参看 PlayState{@link #PlayState}。
     * @param error_code 错误码，参看 KTVPlayerErrorCode{@link #KTVPlayerErrorCode}。
     * @note 
     *       此回调被触发的时机汇总如下：<br>
     *       + 调用 playMusic{@link #IKTVPlayer#playMusic} 成功后，会触发 playState 值为 PlayStatePlaying 的回调；否则会触发 playState 值为 PlayStateFailed 的回调。<br>
     *       + 使用相同的音乐 ID 重复调用 playMusic{@link #IKTVPlayer#playMusic} 后，后一次播放会覆盖前一次，且会触发 playState 值为 PlayStatePlaying 的回调，表示后一次音乐播放已开始。<br>
     *       + 调用 pauseMusic{@link #IKTVPlayer#pauseMusic} 方法暂停播放成功后，会触发 playState 值为 PlayStatePaused 的回调；否则触发 playState 值为 PlayStateFailed 的回调。<br>
     *       + 调用 resumeMusic{@link #IKTVPlayer#resumeMusic} 方法恢复播放成功后，会触发 playState 值为 PlayStatePlaying 的回调；否则触发 playState 值为 PlayStateFailed 的回调。<br>
     *       + 调用 stopMusic{@link #IKTVPlayer#stopMusic} 方法停止播放成功后，会触发 playState 值为 PlayStateStoped 的回调；否则触发 playState 值为 PlayStateFailed 的回调。<br>
     *       + 音乐播放结束会触发 playState 值为 PlayStateFinished 的回调。
     */
    /**
     * @locale en
     * @type callback
     * @brief Music playing state changed callback.
     * @param music_id Music ID.
     * @param play_state Music playing status. See PlayState{@link #PlayState}.
     * @param error_code Error code. See KTVPlayerErrorCode{@link #KTVPlayerErrorCode}.
     * @note 
     *       You will receive this callback on following events.<br>
     *       + When you successfully start playing music by calling playMusic{@link #IKTVPlayer#playMusic}, you will receive this callback with `PlayStatePlaying` playState. Otherwise the playState will be `PlayStateFailed`.<br>
     *       + If the music with the same music ID is playing when you call playMusic{@link #IKTVPlayer#playMusic} again, the music will restart from the starting position, and you will receive this callback with `PlayStatePlaying` playState to inform the latter music has started.<br>
     *       + When you successfully pause the music by calling pauseMusic{@link #IKTVPlayer#pauseMusic}, you will receive this callback with `PlayStatePaused` playState. Otherwise the playState will be `PlayStateFailed`.<br>
     *       + When you successfully resume the music by calling resumeMusic{@link #IKTVPlayer#resumeMusic}, you will receive this callback with `PlayStatePlaying` playState. Otherwise the playState will be `PlayStateFailed`.<br>
     *       + When you successfully stop the music by calling stopMusic{@link #IKTVPlayer#stopMusic}, you will receive this callback with `PlayStateStoped` playState. Otherwise the playState will be `PlayStateFailed`.<br>
     *       + When the music ends, you will receive this callback with `PlayStateFinished` playState.
     */
    virtual void onPlayStateChanged(const char* music_id, PlayState play_state, bytertc::KTVPlayerErrorCode error_code) {
        (void)music_id;
        (void)play_state;
        (void)error_code;
    }
};

/**
 * @locale zh
 * @type api
 * @brief KTV 播放器接口。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type api
 * @brief KTV player interfaces.
 */
class IKTVPlayer {
public:
    /**
     * @hidden Constructor/Destructor
     * @brief Destructor
     */
    virtual ~IKTVPlayer() = default;
    
    /**
     * @locale zh
     * @type api
     * @brief 设置 KTV 播放器进度及状态回调接口。
     * @param handler KTV 播放器回调类，参看 IKTVPlayerEventHandler{@link #IKTVPlayerEventHandler}。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the KTV player event handler.
     * @param handler KTV player event handler. See IKTVPlayerEventHandler{@link #IKTVPlayerEventHandler}.
     */
    virtual void setPlayerEventHandler(IKTVPlayerEventHandler *handler) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 播放歌曲。
     * @param music_id 音乐 ID。<br>
     *        若同一 music_id 的歌曲正在播放，再次调用接口会从开始位置重新播放。若 music_id 对应的音频文件不存在会触发报错。
     * @param track_type 原唱伴唱类型，参看 AudioTrackType{@link #AudioTrackType}。
     * @param play_type 音乐播放类型。参看 AudioPlayType{@link #AudioPlayType}。
     * @note  
     *        + 调用接口后，你会收到 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调歌曲播放状态。<br>
     *        + 若音乐 ID 错误，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3023，play_state 为 4。<br>
     *        + 若未进房，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3022，play_state 为 4。<br>
     *        + 若音乐文件不存在，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3020，play_state 为 4。
     */
    /**
     * @locale en
     * @type api
     * @brief Plays the music.
     * @param music_id Music ID.<br>
     *        If the song with the same music_id is playing when you call this API, the music will restart from the starting position. An error will be triggered if the audio file corresponding to music_id does not exist.
     * @param track_type Audio track type of the KTV player. See AudioTrackType{@link #AudioTrackType}.
     * @param play_type Audio play type. See AudioPlayType{@link #AudioPlayType}.
     * @note  
     *       + After calling this API, you will receive the music play state through onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback.<br>
     *       + If the music ID is invalid, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3023 and a play_state of 4.<br>
     *       + If you didn't join the room, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3022 and a play_state of 4.<br>
     *       + If the music file does not exist, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3020 and a play_state of 4.
     */
    virtual void playMusic(const char* music_id, AudioTrackType track_type, AudioPlayType play_type) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 暂停播放歌曲。
     * @param music_id 音乐 ID。
     * @note  
     *        + 调用接口后，你会收到 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调歌曲播放状态。<br>
     *        + 若音乐 ID 错误，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3023，play_state 为 4。<br>
     *        + 若未进房，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3022，play_state 为 4。
     */
    /**
     * @locale en
     * @type api
     * @brief Pauses the music.
     * @param music_id Music ID.
     * @note  
     *       + After calling this API, you will receive the music play state through onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback.<br>
     *       + If the music ID is invalid, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3023 and a play_state of 4.<br>
     *       + If you didn't join the room, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3022 and a play_state of 4.
     */
    virtual void pauseMusic(const char *music_id) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 继续播放歌曲。
     * @param music_id 音乐 ID。
     * @note  
     *        + 调用接口后，你会收到 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调歌曲播放状态。<br>
     *        + 若音乐 ID 错误，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3023，play_state 为 4。<br>
     *        + 若未进房，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3022，play_state 为 4。
     */
    /**
     * @locale en
     * @type api
     * @brief Resumes playing the music.
     * @param music_id Music ID.
     * @note  
     *       + After calling this API, you will receive the music play state through onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback.<br>
     *       + If the music ID is invalid, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3023 and a play_state of 4.<br>
     *       + If you didn't join the room, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3022 and a play_state of 4.
     */
    virtual void resumeMusic(const char *music_id) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 停止播放歌曲。
     * @param music_id 音乐 ID。
     * @note  
     *        + 调用接口后，你会收到 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调歌曲播放状态。<br>
     *        + 若音乐 ID 错误，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3023，play_state 为 4。<br>
     *        + 若未进房，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3022，play_state 为 4。
     */
    /**
     * @locale en
     * @type api
     * @brief Stops playing the music.
     * @param music_id Music ID.
     * @note  
     *       + After calling this API, you will receive the music play state through onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback.<br>
     *       + If the music ID is invalid, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3023 and a play_state of 4.<br>
     *       + If you didn't join the room, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3022 and a play_state of 4.
     */
    virtual void stopMusic(const char *music_id) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 设置音乐文件的起始播放位置。
     * @param music_id 音乐 ID。
     * @param position 音乐起始位置，单位为毫秒，取值小于音乐文件总时长。
     * @note 
     *        + 调用本接口时音乐必须处于播放中状态。<br>
     *        + 调用接口后，你会收到 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调歌曲播放状态。<br>
     *        + 若音乐 ID 错误，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3023，play_state 为 4。<br>
     *        + 若未进房，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3022，play_state 为 4。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the starting position of the music file.
     * @param music_id Music ID.
     * @param position The starting position of the music file in milliseconds. The value must be less than the total length of the music.
     * @note  
     *       + The music must be playing when you call this API.<br>
     *       + After calling this API, you will receive the music play state through onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback.<br>
     *       + If the music ID is invalid, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3023 and a play_state of 4.<br>
     *       + If you didn't join the room, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3022 and a play_state of 4.
     */
    virtual void seekMusic(const char *music_id, int position) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 设置歌曲播放音量，只能在开始播放后进行设置。
     * @param music_id 音乐 ID。
     * @param volume 歌曲播放音量，调节范围：[0,400]。<br>
     *        + 0：静音。<br>
     *        + 100：原始音量。 <br>
     *        + 400: 原始音量的 4 倍(自带溢出保护)。
     * @note 
     *        + 调用本接口时音乐必须处于播放中状态。<br>
     *        + 若设置的音量大于 400，则按最大值 400 进行调整；若设置的音量小于 0，则按最小值 0 进行调整。<br>
     *        + 若音乐 ID 错误，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3023，play_state 为 4。<br>
     *        + 若未进房，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3022，play_state 为 4。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the volume of the playing music. The music must be playing when you set the volume.
     * @param music_id Music ID.
     * @param volume Volume. Adjustment range: [0,400].<br>
     *         + 0: Mute.<br>
     *         + 100: Original volume.<br>
     *         + 400: 4 times the original volume (with overflow protection).
     * @note  
     *       + The music must be playing when you call this API.<br>
     *       + If the set volume is greater than 400, it will be adjusted by the maximum value of 400; if the set volume is less than 0, it will be adjusted by the minimum value of 0.<br>
     *       + If the music ID is invalid, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3023 and a play_state of 4.<br>
     *       + If you didn't join the room, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3022 and a play_state of 4.
     */
    virtual void setMusicVolume(const char *music_id, int volume) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 切换歌曲原唱伴唱。
     * @param music_id 音乐 ID。
     * @note 调用本接口时音乐必须处于播放中状态。
     */
    /**
     * @locale en
     * @type api
     * @brief Switches the audio track type between the original track and the instrumental track.
     * @param music_id Music ID.
     * @note The music must be playing when you call this API.
     */
    virtual void switchAudioTrackType(const char *music_id) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 对播放中的音乐设置升降调信息。
     * @param music_id 音乐 ID。
     * @param pitch 相对于音乐文件原始音调的升高/降低值，取值范围 [-12，12]，默认值为 0，即不做调整。<br>
     *              取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。
     * @note 
     *        + 调用本接口时音乐必须处于播放中状态。<br>
     *        + 若设置的 pitch 大于 12，则按最大值 12 进行调整；若设置的 pitch 小于 –12，，则按最小值 –12 进行调整。<br>
     *        + 若音乐 ID 错误，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3023，play_state 为 4。<br>
     *        + 若未进房，会触发 onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} 回调，error_code 为 –3022，play_state 为 4。
     */
    /**
     * @locale en
     * @type api
     * @brief Transposes up/down the music being played.
     * @param music_id Music ID.
     * @param pitch The pitch up/down value relative to the original pitch, in the range of [-12, 12], with the default value of 0.<br>
     *              The difference in pitch between two adjacent values is a semitone. A positive value indicates an increase in pitch, and a negative value indicates a decrease in pitch. A larger absolute value means more pitch increase or decrease.
     * @note 
     *       + The music must be in the playing when you call this API.<br>
     *       + If the set pitch is greater than 12, it will be adjusted by the maximum value of 12; if the set pitch is less than –12, it will be adjusted by the minimum value of –12.<br>
     *       + If the music ID is invalid, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3023 and a play_state of 4.<br>
     *       + If you didn't join the room, you will receive the onPlayStateChanged{@link #IKTVPlayerEventHandler#onPlayStateChanged} callback, with an error_code of -3022 and a play_state of 4.
     */
    virtual void setMusicPitch(const char* music_id, int pitch) = 0;

};

/**
 * @locale zh
 * @type api
 * @brief KTV 管理接口。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type api
 * @brief KTV manager interfaces.
 */
class IKTVManager {
public:
    /**
     * @hidden Constructor/Destructor
     * @brief Destructor
     */
    virtual ~IKTVManager() = default;
    
    /**
     * @locale zh
     * @type api
     * @brief 设置歌曲文件最大占用的本地缓存。
     * @param max_cache_size_mb 本地缓存，单位 MB。<br>
     *        设置值小于等于 0 时，使用默认值 1024 MB。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the maximum cache for storing music files.
     * @param max_cache_size_mb The maximum cache to be set in MB.<br>
     *        If the setting value is less than or equal to 0, it will be adjusted to 1,024 MB.
     */
    virtual void setMaxCacheSize(int max_cache_size_mb) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 设置 KTV 回调接口。
     * @param ktv_manager_event_handler KTV 回调类，参看 IKTVManagerEventHandler{@link #IKTVManagerEventHandler}。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the KTV event handler.
     * @param ktv_manager_event_handler KTV event handler. See IKTVManagerEventHandler{@link #IKTVManagerEventHandler}.
     */
    virtual void setKTVManagerEventHandler(IKTVManagerEventHandler *ktv_manager_event_handler) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 获取歌曲列表。
     * @param page_num 页码，默认从 1 开始。
     * @param page_size 每页显示歌曲的最大数量，取值范围 [1,99]。
     * @param filters 歌曲过滤方式，参看 MusicFilterType{@link #MusicFilterType}。
     * @note 调用接口后，你会收到 onMusicListResult{@link #IKTVManagerEventHandler#onMusicListResult} 回调歌曲列表。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the music list.
     * @param page_num Page number. The default value is 1.
     * @param page_size The number of the music that displays on one page.
     * @param filters The filter type of the music list. See MusicFilterType{@link #MusicFilterType}.
     * @note After calling this API, you will receive the music list through onMusicListResult{@link #IKTVManagerEventHandler#onMusicListResult} callback.
     */
    virtual void getMusicList(int page_num, int page_size,  int filters) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 根据关键词搜索歌曲。
     * @param key_word 关键词，字符串长度最大为 20 个字符。
     * @param page_num 页码，默认从 1 开始。
     * @param page_size 每页显示歌曲的最大数量，取值范围 [1,99]。
     * @param filters 歌曲过滤方式，参看 MusicFilterType{@link #MusicFilterType}。
     * @note 调用接口后，你会收到 onSearchMusicResult{@link #IKTVManagerEventHandler#onSearchMusicResult} 回调歌曲列表。
     */
    /**
     * @locale en
     * @type api
     * @brief Search music by keywords.
     * @param key_word Keyword. The string should be no more than 20 characters.
     * @param page_num Page number. The default value is 1.
     * @param page_size The number of the music that displays on one page.
     * @param filters The filter type of the music list. See MusicFilterType{@link #MusicFilterType}.
     * @note After calling this API, you will receive the music list through onSearchMusicResult{@link #IKTVManagerEventHandler#onSearchMusicResult} callback.
     */
    virtual void searchMusic(const char* key_word, int page_num, int page_size, int filters) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 根据榜单类别获取每个榜单的歌曲列表。
     * @param hot_types 榜单类别，参看 MusicHotType{@link #MusicHotType}。
     * @param filters 歌曲过滤方式，参看 MusicFilterType{@link #MusicFilterType}。
     * @note 调用接口后，你会收到 onHotMusicResult{@link #IKTVManagerEventHandler#onHotMusicResult} 回调歌曲列表。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets hot music according to music types.
     * @param hot_types Hot music type. See MusicHotType{@link #MusicHotType}.
     * @param filters The filter type of the music list. See MusicFilterType{@link #MusicFilterType}.
     * @note After calling this API, you will receive the music list through onHotMusicResult{@link #IKTVManagerEventHandler#onHotMusicResult} callback.
     */
    virtual void getHotMusic(int hot_types, int filters) = 0;


    /**
     * @locale zh
     * @type api
     * @brief 获取音乐详细信息。
     * @param music_id 音乐 ID。
     * @note 调用接口后，你会收到 onMusicDetailResult{@link #IKTVManagerEventHandler#onMusicDetailResult} 回调。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets music detail.
     * @param music_id Music ID.
     * @note After calling this API, you will receive the music detail through onMusicDetailResult{@link #IKTVManagerEventHandler#onMusicDetailResult} callback.
     */
    virtual void getMusicDetail(const char* music_id) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 下载音乐。
     * @param music_id 音乐 ID。
     * @return 下载任务 ID。
     * @note  
     *       + 若音乐下载成功，你会收到 onDownloadSuccess{@link #IKTVManagerEventHandler#onDownloadSuccess} 回调。<br>
     *       + 若音乐下载失败，你会收到 onDownloadFailed{@link #IKTVManagerEventHandler#onDownloadFailed} 回调。<br>
     *       + 音乐下载进度更新时，你会收到 onDownloadMusicProgress{@link #IKTVManagerEventHandler#onDownloadMusicProgress} 回调。
     */
    /**
     * @locale en
     * @type api
     * @brief Download music.
     * @param music_id Music ID.
     * @return Download task ID.
     * @note  
     *       + If the music is successfully downloaded, you will receive onDownloadSuccess{@link #IKTVManagerEventHandler#onDownloadSuccess}.<br>
     *       + If the music fails to download, you will receive onDownloadFailed{@link #IKTVManagerEventHandler#onDownloadFailed}.<br>
     *       + When the music download progress is updated, you will receive onDownloadMusicProgress{@link #IKTVManagerEventHandler#onDownloadMusicProgress}.
     */
    virtual int downloadMusic(const char* music_id) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 下载歌词。
     * @param music_id 音乐 ID。
     * @param type 歌词文件类型，参看 DownloadLyricType{@link #DownloadLyricType}。
     * @return 下载任务 ID。
     * @note  
     *       + 若歌词下载成功，你会收到 onDownloadSuccess{@link #IKTVManagerEventHandler#onDownloadSuccess} 回调。<br>
     *       + 若歌词下载失败，你会收到 onDownloadFailed{@link #IKTVManagerEventHandler#onDownloadFailed} 回调。
     */
    /**
     * @locale en
     * @type api
     * @brief Download lyrics.
     * @param music_id Music ID.
     * @param type The lyrics file's format. See DownloadLyricType{@link #DownloadLyricType}.
     * @return Download task ID.
     * @note  
     *       + If the lyrics are successfully downloaded, you will receive onDownloadSuccess{@link #IKTVManagerEventHandler#onDownloadSuccess}.<br>
     *       + If the lyrics fail to download, you will receive onDownloadFailed{@link #IKTVManagerEventHandler#onDownloadFailed}.
     */
    virtual int downloadLyric(const char* music_id, DownloadLyricType type) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 下载 MIDI 文件。
     * @param music_id 音乐 ID。
     * @return 下载任务 ID。
     * @note  
     *       + 若文件下载成功，你会收到 onDownloadSuccess{@link #IKTVManagerEventHandler#onDownloadSuccess} 回调。<br>
     *       + 若文件下载失败，你会收到 onDownloadFailed{@link #IKTVManagerEventHandler#onDownloadFailed} 回调。
     */
    /**
     * @locale en
     * @type api
     * @brief Download MIDI files.
     * @param music_id Music ID.
     * @return Download task ID.
     * @note  
     *       + If the file is successfully downloaded, you will receive onDownloadSuccess{@link #IKTVManagerEventHandler#onDownloadSuccess}.<br>
     *       + If the file fails to download, you will receive onDownloadFailed{@link #IKTVManagerEventHandler#onDownloadFailed}.
     */
    virtual int downloadMidi(const char* music_id) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 取消下载任务。
     * @param download_id 下载任务 ID。
     */
    /**
     * @locale en
     * @type api
     * @brief Cancels download task.
     * @param download_id Download task ID.
     */
    virtual void cancelDownload(int download_id) = 0;


    /**
     * @locale zh
     * @type api
     * @brief 清除当前音乐缓存文件，包括音乐音频和歌词。
     */
    /**
     * @locale en
     * @type api
     * @brief Clear music cache, including music and lyrics.
     */
    virtual void clearCache() = 0;

    /**
     * @locale zh
     * @type api
     * @brief 获取 KTV 播放器。
     * @return KTV 播放器接口，参看 IKTVPlayer{@link #IKTVPlayer}。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the KTV player.
     * @return KTV player interfaces. See IKTVPlayer{@link #IKTVPlayer}.
     */
    virtual IKTVPlayer *getKTVPlayer() = 0;

};

} // namespace bytertc
