/*
 * Copyright (c) 2023 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Audio Effect Player
*/
#pragma once

#ifndef BYTE_RTC_MEDIA_PLAYER_H__
#define BYTE_RTC_MEDIA_PLAYER_H__
#include "bytertc_audio_frame.h"

namespace bytertc {
/** 
 * @type callback
 * @brief 本地音频文件混音的音频帧观察者。
 */
class IMediaPlayerAudioFrameObserver {
public:
    /** 
     * @type callback
     * @brief 当本地音频文件混音时，回调播放的音频帧。
     * @param player_id
     * @param audioFrame 参看 IAudioFrame{@link #IAudioFrame}。
     */
    virtual void onFrame(int player_id, const IAudioFrame& frame) = 0;
    /** 
     * @hidden constructor
     */
    virtual ~IMediaPlayerAudioFrameObserver() {
    }
};
/**  
 * @type keytype
 * @brief 自定义音频源模式
 */
enum MediaPlayerCustomSourceMode{
    /**  
     * @brief 当播放来自本地的 PCM 数据时，使用此选项。
     */
    kMediaPlayerCustomSourceModePush = 0,
    /**  
     * @brief 当播放来自内存的音频数据时，使用此选项。
     */
    kMediaPlayerCustomSourceModePull,
};

/** 
 * @type keytype
 * @brief 音频数据的起始读取位置。
 */
 enum MediaPlayerCustomSourceSeekWhence{
    /** 
     * @brief 从音频数据的头开始读取，读取的实际偏移量为参数 offset 的值。
     */
    kMediaPlayerCustomSourceSeekWhenceSet = 0,
    /** 
     * @brief 从音频数据的某一位置开始读取，读取的实际偏移量为音频数据当前的读取位置位置加上参数 offset 的值。 
     */
    kMediaPlayerCustomSourceSeekWhenceCur = 1,
    /** 
     * @brief 从音频数据的尾开始读取，读取的实际数据偏移量为用户传入的音频数据大小加上参数 offset 的值。 
     */
    kMediaPlayerCustomSourceSeekWhenceEnd = 2,
    /** 
     * @brief 返回音频数据的大小。
     */
    kMediaPlayerCustomSourceSeekWhenceSize = 3,
};
/**  
 * @type keytype
 * @brief 自定义音频流类型
 */
enum MediaPlayerCustomSourceStreamType{
    /**  
     * @brief 当播放来自本地的 PCM 数据时，使用此选项。
     */
    kMediaPlayerCustomSourceStreamTypeRaw = 0,
    /**  
     * @brief 当播放来自内存的音频数据时，使用此选项。
     */
    kMediaPlayerCustomSourceStreamTypeEncoded,
};

/** 
 * @type callback
 * @brief 内存播放数据源回调
 */
class IMediaPlayerCustomSourceProvider {
public:
    /** 
     * @valid since 3.53
     * @type callback
     * @region 音乐播放器
     * @brief 调用 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 接口播放用户传入的内存音频数据时，会触发此回调，用户需要写入音频数据。
     * @param [in] *buffer 内存地址。在该地址中写入音频数据，写入音频数据的大小不超过 bufferSize 中填入的数值。 <br>
     * @param [in] bufferSize 音频数据大小，单位为字节。如果你想停止播放内存音频数据，可在 bufferSize 中填入小于或等于 0 的数，此时 SDK 会停止调用此接口。 
     * @return 返回实际读取的音频数据大小。
     * @notes 若 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 接口调用失败，请在 buffer 和 bufferSize 两个参数中填入 0。 此时 SDK 会停止调用此接口。
     */
    virtual int onReadData(uint8_t *buffer, int bufferSize) = 0;
    /** 
     * @valid since 3.53
     * @type callback
     * @region 音乐播放器
     * @brief 根据设置好的内存音频数据的读取位置和读取偏移量对音频数据进行偏移，以便 SDK 读取和分析音频数据。 <br>
     *        在调用 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 接口传入内存音频数据，或者调用 setPosition{@link #IMediaPlayer#setPosition} 设置了音频数据的起始播放位置后，SDK 会对音频数据进行读取和分析，此时会触发该回调，你需要根据参数中设置的起始读取位置和偏移量进行操作。
     * @param [in] offset 音频数据读取偏移量，单位为字节，取值可正可负。  <br>
     * @param [in] whence 音频数据的起始读取位置。参看 MediaPlayerCustomSourceSeekWhence{@link #MediaPlayerCustomSourceSeekWhence}
     * @return <br>
     *         定位成功，返回偏移后的位置信息，或返回音频数据的大小。<br>
     *         定位失败，返回 -1。         
     */
    virtual int64_t onSeek(int64_t offset, MediaPlayerCustomSourceSeekWhence whence) = 0;
    
    virtual ~IMediaPlayerCustomSourceProvider() {}
};
/** 
 * @type keytype
 * @brief 音频源
 */
struct MediaPlayerCustomSource {
    /** 
     * @brief 仅在使用内存播放时，传入对应的 IMediaPlayerCustomSourceProvider{@link #IMediaPlayerCustomSourceProvider} 实例。
     */
    IMediaPlayerCustomSourceProvider* provider = nullptr;
    /**  
     * @type keytype
     * @brief 数据源模式，详见 MediaPlayerCustomSourceMode{@link #MediaPlayerCustomSourceMode}。
     */
    MediaPlayerCustomSourceMode mode = kMediaPlayerCustomSourceModePush;
    /**  
     * @type keytype
     * @brief 数据源类型，详见 MediaPlayerCustomSourceStreamType{@link #MediaPlayerCustomSourceStreamType}
     */
    MediaPlayerCustomSourceStreamType type = kMediaPlayerCustomSourceStreamTypeRaw;
};
/** 
 * @type callback
 * @brief IMediaPlayer{@link #IMediaPlayer} 对应的回调句柄。你必须调用 setEventHandler{@link #IMediaPlayer#setEventHandler} 完成设置后，才能收到对应回调。
 */
class IMediaPlayerEventHandler {
public:
    virtual ~IMediaPlayerEventHandler() {}
    /** 
    * @type callback
    * @brief 播放状态改变时回调。
    * @param playerId IMediaPlayer{@link #IMediaPlayer} 的 ID。通过 getMediaPlayer{@link #IRTCVideo#getMediaPlayer} 设置。
    * @param state 混音状态。参考 PlayerState{@link #PlayerState}。
    * @param error 错误码。参考 PlayerError{@link #PlayerError}。
    */
    virtual void onMediaPlayerStateChanged(int playerId, PlayerState state, PlayerError error) = 0;
   /** 
    * @type callback
    * @brief 播放进度周期性回调。回调周期通过 setProgressInterval{@link #IMediaPlayer#setProgressInterval} 设置。
    * @param playerId IMediaPlayer{@link #IMediaPlayer} 的 ID。通过 getMediaPlayer{@link #IRTCVideo#getMediaPlayer} 设置。
    * @param progress 进度。单位 ms。
    */
    virtual void onMediaPlayerPlayingProgress(int playerId, int64_t progress) = 0;
};
/** 
 * @type api
 * @brief 音乐播放器
 * @valid since 3.53
 * @notes 调用 setEventHandler{@link #IMediaPlayer#setEventHandler} 设置回调句柄以获取相关回调。
 */
class IMediaPlayer {
public:
    IMediaPlayer(){}
    virtual ~IMediaPlayer() {}
    /** 
     * @type api
     * @brief 打开音乐文件。
     *        一个播放器实例仅能够同时打开一个音乐文件。如果需要同时打开多个音乐文件，请创建多个音乐播放器实例。
     *        要播放 PCM 格式的音频数据，参看 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource}。`openWithCustomSource` 和此 API 互斥。
     * @param file_path 音乐文件路径。
     *        支持在线文件的 URL、本地文件的 URI、或本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。
     *        推荐的采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。
     *        不同平台支持的本地文件格式:
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     *        不同平台支持的在线文件格式:
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @param config 详见 AudioEffectPlayerConfig{@link #AudioEffectPlayerConfig}。
     */
    virtual int open(const char* file_path, const MediaPlayerConfig& config) = 0;
    /** 
     * @type api
     * @brief 播放音乐。你仅需要在调用 open{@link #IMediaPlayer#open}，且未开启自动播放时，调用此方法。
     * @notes 调用本方法播放音频文件后，可调用 stop{@link #IMediaPlayer#stop} 方法暂停播放。
     */
    virtual int start() = 0;
    /** 
     * @type api
     * @brief 启动音频裸数据混音。
     *        要播放音乐文件，参看 open{@link #IMediaPlayer#open}。`open` 与此 API 互斥。
     * @param source 数据源，详见 MediaPlayerCustomSource{@link #MediaPlayerCustomSource}
     * @param config 详见 MediaPlayerConfig{@link #MediaPlayerConfig}
     * @notes  <br>
     *       + 调用本方法启动后，再调用 pushExternalAudioFrame{@link #IMediaPlayer#pushExternalAudioFrame} 推送音频数据，才会开始混音。
     *       + 如要结束 PCM 音频数据混音，调用 stop{@link #IMediaPlayer#stop}。
     */
    virtual int openWithCustomSource(const MediaPlayerCustomSource& source, const MediaPlayerConfig& config) = 0;
    /** 
     * @type api
     * @brief 调用 open{@link #IMediaPlayer#open}, start{@link #IMediaPlayer#start}, 或 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 开始播放后，可以调用本方法停止。
     */
    virtual int stop() = 0;
    /** 
     * @type api
     * @brief 调用 open{@link #IMediaPlayer#open}，或 start{@link #IMediaPlayer#start} 开始播放音频文件后，调用本方法暂停播放。
     * @notes 调用本方法暂停播放后，可调用 resume{@link #IMediaPlayer#resume} 恢复播放。
     */
    virtual int pause() = 0;
    /** 
     * @type api
     * @brief 调用 pause{@link #IMediaPlayer#pause} 暂停音频播放后，调用本方法恢复播放。
     */
    virtual int resume() = 0;
    /** 
     * @type api
     * @brief 调节指定混音的音量大小，包括音乐文件混音和 PCM 混音。
     * @param volume 播放音量相对原音量的比值。单位为 %。范围为 `[0, 400]`，建议范围是 `[0, 100]`。带溢出保护。
     * @param type 详见 AudioMixingType{@link #AudioMixingType}。
     * @notes 仅在音频播放进行状态时，调用此方法。
     */
     virtual int setVolume(int volume, AudioMixingType type) = 0;
    /** 
     * @type api
     * @brief 获取当前音量
     * @param type 详见 AudioMixingType{@link #AudioMixingType}。
     * @return  <br>
     *        + >0: 成功, 当前音量值。  <br>
     *        + < 0: 失败
     * @notes 仅在音频播放进行状态时，调用此方法。包括音乐文件混音和 PCM 混音。
     */
    virtual int getVolume(AudioMixingType type) = 0;
    /** 
     * @type api
     * @brief 获取音乐文件时长。
     * @return  <br>
     *        + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
     *        + < 0: 失败
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 此接口仅支持音频文件，不支持 PCM 数据。
     */
    virtual int getTotalDuration() = 0;
    /** 
     * @type api
     * @brief 获取混音音乐文件的实际播放时长，单位为毫秒。
     * @return  <br>
     *        + >0: 实际播放时长。
     *        + < 0: 失败。
     * @notes <br>
     *        + 实际播放时长指的是歌曲不受停止、跳转、倍速、卡顿影响的播放时长。例如，若歌曲正常播放到 1:30 时停止播放 30s 或跳转进度到 2:00, 随后继续正常播放 2分钟，则实际播放时长为 3分30秒。
     *        + 仅在音频播放进行状态时，调用此方法。
     *        + 此接口仅支持音频文件，不支持 PCM 数据。
     */
    virtual int getPlaybackDuration() = 0;
    /** 
     * @type api
     * @brief 获取音乐文件播放进度。
     * @return  <br>
     *        + >0: 成功, 音乐文件播放进度，单位为毫秒。
     *        + < 0: 失败
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 此接口仅支持音频文件，不支持 PCM 数据。
     */
    virtual int getPosition() = 0;
    /** 
     * @type api
     * @brief 开启变调功能，多用于 K 歌场景。
     * @param pitch 与音乐文件原始音调相比的升高/降低值，取值范围为 `[-12，12]`，默认值为 0。每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调。
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 支持音乐文件混音和 PCM 混音。
     */
    virtual int setAudioPitch(int pitch) = 0;
    /** 
     * @type api
     * @brief 设置音乐文件的起始播放位置。
     * @param position 音乐文件起始播放位置，单位为毫秒。  <br>
     *        你可以通过 getTotalDuration{@link #IMediaPlayer#getTotalDuration} 获取音乐文件总时长，position 的值应小于音乐文件总时长。
     * @notes 在播放在线文件时，调用此接口可能造成播放延迟的现象。
     */
    virtual int setPosition(int position) = 0;
    /** 
     * @type api
     * @brief 设置当前音乐文件的声道模式
     * @param mode 声道模式。默认的声道模式和源文件一致，详见 AudioMixingDualMonoMode{@link #AudioMixingDualMonoMode}。
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 仅支持音频文件，不支持 PCM 数据。
     */
    virtual int setAudioDualMonoMode(AudioMixingDualMonoMode mode) = 0;
    /** 
     * @type api
     * @brief 获取当前音乐文件的音轨数
     * @return + >= 0：成功，返回当前音乐文件的音轨数
     *         + < 0：方法调用失败
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 此方法仅支持音乐文件，不支持 PCM 数据。
     */
    virtual int getAudioTrackCount() = 0;
    /** 
     * @type api
     * @brief 指定当前音乐文件的播放音轨
     * @param index 指定的播放音轨，从 0 开始，取值范围为 `[0, getAudioTrackCount()-1]`。
     *        设置的参数值需要小于 getAudioTrackCount{@link #IMediaPlayer#getAudioTrackCount} 的返回值
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 此方法仅支持音乐文件，不支持 PCM 数据。
     */
    virtual int selectAudioTrack(int index) = 0;
    /** 
     * @type api
     * @brief 设置播放速度
     * @param speed 播放速度与原始文件速度的比例，单位：%，取值范围为 `[50,200]`，默认值为 100。
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 此方法对音频文件和音频裸数据播放都可用。
     */
    virtual int setPlaybackSpeed(int speed) = 0;
    /** 
     * @type api
     * @brief 设置音频文件混音时，收到 onMediaPlayerPlayingProgress{@link #IMediaPlayerEventHandler#onMediaPlayerPlayingProgress} 的间隔。
     * @param interval 时间间隔，单位毫秒。
     *       + interval > 0 时，触发回调。实际间隔是 `10*(mod(10)+1)`。
     *       + interval <= 0 时，不会触发回调。
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 此方法仅支持音频文件，不支持 PCM 数据。
     */
     virtual int setProgressInterval(int64_t interval) = 0;
    /** 
     * @type api
     * @brief 如果你需要使用 enableVocalInstrumentBalance{@link #IRTCVideo#enableVocalInstrumentBalance} 对音频文件/PCM 音频数据设置音量均衡，你必须通过此接口传入其原始响度。
     * @param loudness 原始响度，单位：lufs，取值范围为 `[-70.0, 0.0]`。
     *        当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音量均衡处理。默认值为 1.0lufs，即不做处理。
     * @notes + 仅在音频播放进行状态时，调用此方法。
     *        + 此方法对音频文件和音频裸数据播放都可用。
     */
    virtual int setLoudness(float loudness) = 0;
    /** 
     * @type api
     * @brief 注册回调句柄以在本地音乐文件混音时，收到相关回调。
     * @param observer 参看 IMediaPlayerAudioFrameObserver{@link #IMediaPlayerAudioFrameObserver}。
     */
    virtual int registerAudioFrameObserver(IMediaPlayerAudioFrameObserver* observer) = 0;
    /** 
     * @type api
     * @brief 推送用于混音的 PCM 音频帧数据
     * @param audio_frame 音频帧，详见 IAudioFrame{@link #IAudioFrame}。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes
     *      + 调用该方法前，须通过 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 启动外部音频流混音。
     *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     *。    + 如果要暂停播放，暂停推送即可。
     */
    virtual int pushExternalAudioFrame(IAudioFrame* audio_frame) = 0;
    /** 
     * @type api
     * @brief 设置回调句柄。
     * @param handler 参看 IMediaPlayerEventHandler{@link #IMediaPlayerEventHandler}。
     * @return  <br>
     *        + 0: 成功。  <br>
     *        + < 0: 失败。
     */
    virtual int setEventHandler(IMediaPlayerEventHandler* handler) = 0;
 };


}
#endif
