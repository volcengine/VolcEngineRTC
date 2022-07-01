/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Audio Mixing Manager
*/

#pragma once

#ifndef BYTE_RTC_AUDIO_MIXING_MANAGER_H__
#define BYTE_RTC_AUDIO_MIXING_MANAGER_H__
#include "bytertc_audio_frame.h"

namespace bytertc {

/** 
 * @type api
 * @brief 混音管理类
 */
class IAudioMixingManager {
public:
    /** 
     * @hidden
     * @brief 构造函数
     */
    IAudioMixingManager() {
    }
    /** 
     * @type api
     * @region 混音
     * @brief 开始播放音频文件。<br>
     *        可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。
     * @param [in] mix_id 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br>
     *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，SDK 会使用 `OnAudioMixingStateChanged` 回调通知前一次混音已停止。
     * @param [in] file_path 用于混音文件路径。<br>
     *        支持在线文件的 URL、和本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。<br>
     *        不同平台支持的音频文件格式: <br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @param [in] config 混音配置  <br>
     *        可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 AudioMixingConfig{@link #AudioMixingConfig}。
     * @notes  <br>
     *       + 如果已经通过 PreloadAudioMixing{@link #IAudioMixingManager#PreloadAudioMixing} 将文件加载至内存，确保此处的 ID 与预加载时设置的 ID 相同。  <br>
     *       + 调用本方法播放音频文件后，关于当前的混音状态，会收到回调 `OnAudioMixingStateChanged`。  <br>
     *       + 开始播放音频文件后，可以调用 StopAudioMixing{@link #IAudioMixingManager#StopAudioMixing} 方法停止播放音频文件。  <br>
     *       + 本方法的混音数据来源于外部文件，而 EnableAudioMixingFrame{@link #IAudioMixingManager#EnableAudioMixingFrame} 的混音数据来源于外部缓存且音频格式为 PCM，这两种混音方式可以共存。
     */
    virtual void StartAudioMixing(int mix_id, const char * file_path, const AudioMixingConfig& config) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 停止播放音乐文件及混音
     * @param [in] mix_id  <br>
     *        混音 ID
     * @notes  <br>
     *       + 调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 方法开始播放音乐文件及混音后，可以调用本方法停止播放音乐文件及混音。  <br>
     *       + 调用本方法停止播放音乐文件后，SDK 会向本地回调通知已停止混音，见 `OnAudioMixingStateChanged`。  <br>
     *       + 调用本方法停止播放音乐文件后，该音乐文件会被自动卸载。
     */
    virtual void StopAudioMixing(int mix_id) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 暂停播放音乐文件及混音
     * @param [in] mix_id  <br>
     *        混音 ID
     * @notes  <br>
     *       + 调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 方法开始播放音乐文件及混音后，可以通过调用本方法暂停播放音乐文件及混音。  <br>
     *       + 调用本方法暂停播放音乐文件及混音后，可调用 ResumeAudioMixing{@link #IAudioMixingManager#ResumeAudioMixing} 方法恢复播放及混音。  <br>
     *       + 调用本方法暂停播放音乐文件后，SDK 会向本地回调通知已暂停混音，见 `OnAudioMixingStateChanged`。
     */
    virtual void PauseAudioMixing(int mix_id) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 恢复播放音乐文件及混音
     * @param [in] mix_id  <br>
     *        混音 ID
     * @notes  <br>
     *       + 调用 PauseAudioMixing{@link #IAudioMixingManager#PauseAudioMixing} 方法暂停播放音乐文件及混音后，可以通过调用本方法恢复播放及混音。  <br>
     *       + 调用本方法恢复播放音乐文件及混音后，SDK 会向本地回调通知音乐文件正在播放中，见 `OnAudioMixingStateChanged`。
     */
    virtual void ResumeAudioMixing(int mix_id) = 0;
    /** 
     * @type api
     * @region 混音
     * @brief 预加载指定音频文件到内存中，以避免频繁播放时的重复加载。
     * @param [in] mix_id 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br>
     *        如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br>
     *        如果先调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing}，再使用相同的 ID 调用本方法 ，会先回调 `OnAudioMixingStateChanged` 通知上一个混音停止，然后加载后一个混音。  <br>
     *        使用一个 ID 调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 播放 B.mp3，请先调用 UnloadAudioMixing{@link #IAudioMixingManager#UnloadAudioMixing} 卸载 A.mp3。
     * @param [in] file_path 混音文件路径。<br>
     *        支持在线文件的 URL，和本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。预加载的文件长度不得超过 20s。<br>
     *        不同平台支持的音频文件格式: <br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @notes  <br>
     *       + 本方法只是预加载指定音频文件，只有调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 方法才开始播放指定音频文件。 <br>
     *       + 调用本方法预加载音频文件后，关于当前的混音状态，会收到回调 `OnAudioMixingStateChanged`。  <br>
     *       + 调用本方法预加载的指定音频文件可以通过 UnloadAudioMixing{@link #IAudioMixingManager#UnloadAudioMixing} 卸载。
     */
    virtual void PreloadAudioMixing(int mix_id, const char* file_path) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 卸载指定音乐文件
     * @param [in] mix_id  <br>
     *        混音 ID
     * @notes 不论音乐文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 `OnAudioMixingStateChanged`。
     */
    virtual void UnloadAudioMixing(int mix_id) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 调节混音的音量大小，包括音频文件混音和 PCM 混音。
     * @param mix_id 混音 ID
     * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
     *        + 0：静音  <br>
     *        + 100：原始音量（默认值）  <br>
     *        + 400: 最大可调音量 (自带溢出保护)
     * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 AudioMixingType{@link #AudioMixingType}。
     */
    virtual void SetAudioMixingVolume(int mix_id, int volume, AudioMixingType type) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 获取音乐文件时长
     * @param [in] mix_id  <br>
     *        混音 ID
     * @return  <br>
     *        + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
     *        + < 0: 失败
     * @notes 调用本方法获取音乐文件时长前，需要先调用 PreloadAudioMixing{@link #PreloadAudioMixing} 或 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing}。
     */
    virtual int GetAudioMixingDuration(int mix_id) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 获取音乐文件播放进度
     * @param [in] mix_id  <br>
     *        混音 ID
     * @return  <br>
     *        + >0: 成功, 音乐文件播放进度，单位为毫秒。  <br>
     *        + < 0: 失败
     * @notes 调用本方法获取音乐文件播放进度前，需要先调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 开始播放音乐文件。
     */
    virtual int GetAudioMixingCurrentPosition(int mix_id) = 0;
    /** 
     * @type api
     * @region 混音
     * @brief 设置音频文件的起始播放位置
     * @param [in] mix_id 混音 ID
     * @param [in] position 音频文件起始播放位置，单位为毫秒。  <br>
     *        你可以通过 GetAudioMixingDuration{@link #IAudioMixingManager#GetAudioMixingDuration} 获取音频文件总时长，position 的值应小于音频文件总时长。
     * @notes 在播放在线文件时，调用此接口可能造成播放延迟的现象。
     */
    virtual void SetAudioMixingPosition(int mix_id, int position) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 设置当前音频文件的声道模式
     * @param [in] mix_id 混音 ID
     * @param [in] mode 声道模式。默认的声道模式和源文件一致，详见 AudioMixingDualMonoMode{@link #AudioMixingDualMonoMode}。
     * @notes <br>
     *        + 调用本方法设置音频文件的声道模式前，需要先调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 开始播放音频文件。<br>
     *        + 此方法对 EnableAudioMixingFrame{@link #IAudioMixingManager#EnableAudioMixingFrame} 播放的音乐无效。
     */
    virtual void SetAudioMixingDualMonoMode(int mix_id, AudioMixingDualMonoMode mode) = 0;
    
    /** 
     * @type api
     * @region 混音
     * @brief 开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br>
     *        使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。
     * @param [in] mix_id 混音 ID
     * @param [in] pitch 相对于音乐文件原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
     *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
     *        超出取值范围则设置失败，并且会触发 `OnAudioMixingStateChanged` 回调，提示 AudioMixingState{@link #AudioMixingState} 状态为 `AUDIO_MIXING_STATE_FAILED` 混音播放失败，AudioMixingError{@link #AudioMixingError} 错误码为 `AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH` 设置混音文件音调不合法。
     * @notes 本方法需要在调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 开始播放音频文件后、调用 StopAudioMixing{@link #IAudioMixingManager#StopAudioMixing} 停止播放音频文件前使用，否则会触发 `OnAudioMixingStateChanged` 回调报错
     */
    virtual void SetAudioMixingPitch(int mix_id, int pitch) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 设置混音时音频文件的播放速度
     * @param [in] mix_id 混音 ID
     * @param [in] speed 播放速度与原始文件速度的比例，单位：%，取值范围为 [50,200]，默认值为 100。  <br>
     *        超出取值范围则设置失败，你会收到 `OnAudioMixingStateChanged` 回调，提示 AudioMixingState{@link #AudioMixingState} 状态为 `kAudioMixingStateFailed` 混音播放失败，AudioMixingError{@link #AudioMixingError} 错误码为 `kAudioMixingErrorInValidPlaybackSpeed` 设置混音文件的播放速度不合法。
     * @notes   <br>
     *        + 暂不支持对 PCM 音频数据进行变速调整。  <br>
     *        + 你需要在调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 开始混音，并且收到`OnAudioMixingStateChanged` 回调提示 AudioMixingState{@link #AudioMixingState} 状态为 `kAudioMixingStatePlaying`，AudioMixingError{@link #AudioMixingError} 错误码为 `kAudioMixingErrorOk` 之后调用该方法。  <br>
     *        + 在 StopAudioMixing{@link #IAudioMixingManager#StopAudioMixing} 停止混音或 UnloadAudioMixing{@link #IAudioMixingManager#UnloadAudioMixing} 卸载音频文件后调用该 API，会收到状态为 `kAudioMixingStateFailed` 错误码为 `kAudioMixingErrorIdNotFound` 的 `OnAudioMixingStateChanged` 回调。
     */
    virtual int SetAudioMixingPlaybackSpeed(int mix_id, int speed) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 设置混音时音频文件播放进度回调的间隔
     * @param [in] mix_id 混音 ID  <br>
     *        可以通过多次调用本接口传入不同的 ID 对多个 ID 进行间隔设置。
     * @param [in] interval 音频文件播放进度回调的时间间隔，单位毫秒。  <br>
     *       + interval 的值为大于 0 的 10 的倍数，当设置的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。设置完成后 SDK 将会按照设置的时间间隔触发 `OnAudioMixingPlayingProgress` 回调。  <br>
     *       + interval 的值小于等于 0 时，不会触发进度回调。  <br>
     * @notes 本方法需要在调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 开始播放音频文件后、调用 StopAudioMixing{@link #IAudioMixingManager#StopAudioMixing} 停止播放音频文件前使用，否则会触发 `OnAudioMixingStateChanged` 回调报错。  <br>
     *        若想在音乐文件开始播放前设置播放进度回调间隔，你需调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 在 AudioMixingConfig{@link #AudioMixingConfig} 中设置时间间隔，开始播放后可以通过此接口更新回调间隔。
     */
    virtual void SetAudioMixingProgressInterval(int mix_id, int64_t interval) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 如果你需要使用 `EnableVocalInstrumentBalance` 对混音使音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。
     * @param [in] mixId 混音 ID
     * @param [in] loudness 原始响度，单位：lufs，取值范围为 [-70.0, 0.0]。  <br>
     *        当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音均衡处理。默认值为 1.0lufs，即不做处理。
     * @notes 建议在 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 开始播放音频文件之前调用该接口，以免播放过程中的音量突变导致听感体验下降。
     */
    virtual void SetAudioMixingLoudness(int mix_id, float loudness) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 启动外部音频流混音
     * @param [in] mix_id 混音 ID，用于标识混音，保证混音 ID 唯一性。  <br>
     *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，会收到 `OnAudioMixingStateChanged` 通知前一次混音已停止。
     * @param [in] type 混音播放类型  <br>
     *        是否本地播放、以及是否发送到远端，详见 AudioMixingType{@link #AudioMixingType}。
     * @brief 启动 PCM 音频数据混音。<br>
     *        要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 mix_id。
     * @notes  <br>
     *       + 必须先调用本方法启动 PCM 音频数据混音，随后调用 PushAudioMixingFrame{@link #PushAudioMixingFrame} 方法，才会开始混音。 <br>
     *       + 如要结束 PCM 音频数据混音，使用 DisableAudioMixingFrame{@link #IAudioMixingManager#DisableAudioMixingFrame}。
     */
    virtual void EnableAudioMixingFrame(int mix_id, AudioMixingType type) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 关闭 PCM 混音
     * @param mix_id 混音 ID。
     */
    virtual void DisableAudioMixingFrame(int mix_id) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 推送 PCM 音频帧数据用于混音
     * @param mix_id 混音 ID。
     * @param audioFrame 音频帧，详见 IAudioFrame{@link #IAudioFrame}。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes
     *      + 调用该方法前，须通过 EnableAudioMixingFrame{@link #IAudioMixingManager#EnableAudioMixingFrame} 启动外部音频流混音。  <br>
     *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 100 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。要暂停播放，暂停推送即可。
     */
    virtual int PushAudioMixingFrame(int mix_id, IAudioFrame* audio_frame) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 获取当前音频文件的音轨索引
     * @param [in] mix_id 混音 ID
     * @return 方法调用结果 <br>
     *        + ≥ 0：成功，返回当前音频文件的音轨索引  <br>
     *        + < 0：方法调用失败
     * @notes  <br>
     *       + 调用本方法获取音频文件的音轨前，需要先调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 开始播放音频文件。<br>
     *       + 此方法对 EnableAudioMixingFrame{@link #IAudioMixingManager#EnableAudioMixingFrame} 播放的音频无效。
     */
    virtual int GetAudioTrackCount(int mix_id) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 指定当前音频文件的播放音轨
     * @param [in] mix_id 混音 ID
     * @param [in] audio_track_index 指定的播放音轨  <br>
     *        设置的参数值需要小于或等于 GetAudioTrackCount{@link #IAudioMixingManager#GetAudioTrackCount} 的返回值
     * @notes  <br>
     *       + 调用本方法设置音频文件的音轨前，需要先调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 开始播放音频文件。<br>
     *       + 此方法对 EnableAudioMixingFrame{@link #IAudioMixingManager#EnableAudioMixingFrame} 播放的音乐无效。
     */
    virtual void SelectAudioTrack(int mix_id, int audio_track_index) = 0;

    /**  
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioMixingManager() {
    }
};

}  // namespace bytertc

#endif // BYTE_RTC_AUDIO_MIXING_MANAGER_H__
