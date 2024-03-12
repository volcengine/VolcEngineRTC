/*
 * Copyright (c) 2023 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Audio Effect Player
*/
#pragma once

#include "bytertc_audio_frame.h"

namespace bytertc {
/**
 * @locale zh
 * @type callback
 * @brief IAudioEffectPlayer{@link #IAudioEffectPlayer} 对应的回调句柄。你必须调用 setEventHandler{@link #IAudioEffectPlayer#setEventHandler} 完成设置后，才能收到对应回调。
 */
/**
 * @locale en
 * @type callback
 * @brief Event handler for IAudioEffectPlayer{@link #IAudioEffectPlayer}. You must call setEventHandler{@link #IAudioEffectPlayer#setEventHandler} to set the corresponding event handler to get the events.
 */
class IAudioEffectPlayerEventHandler {
public:
    virtual ~IAudioEffectPlayerEventHandler() {}
    /**
    * @locale zh
    * @type callback
    * @brief 播放状态改变时回调。
    * @param effect_id IAudioEffectPlayer{@link #IAudioEffectPlayer} 的 ID。通过 getAudioEffectPlayer{@link #IRTCVideo#getAudioEffectPlayer} 设置。
    * @param state 混音状态。参考 PlayerState{@link #PlayerState}。
    * @param error 错误码。参考 PlayerError{@link #PlayerError}。
    */
    /**
    * @locale en
    * @type callback
    * @brief Callback for audio mixing status change.
    * @param effect_id The ID of IAudioEffectPlayer{@link #IAudioEffectPlayer}. Set by getAudioEffectPlayer{@link #IRTCVideo#getAudioEffectPlayer}.
    * @param state See PlayerState{@link #PlayerState}.
    * @param error See PlayerError{@link #PlayerError}.
    */
    virtual void onAudioEffectPlayerStateChanged(int effect_id, PlayerState state, PlayerError error) = 0;
};
/**
 * @locale zh
 * @valid since 3.53
 * @type api
 * @brief 音效播放器<br>
 *        调用 setEventHandler{@link #IAudioEffectPlayer#setEventHandler} 设置回调句柄以获取相关回调。
 */
/**
 * @locale en
 * @valid since 3.53
 * @type api
 * @brief Audio effect player<br>
 *        Call setEventHandler{@link #IAudioEffectPlayer#setEventHandler} to set the callback handler to receive related callbacks.
 */
class IAudioEffectPlayer {
public:
    IAudioEffectPlayer(){}
    virtual ~IAudioEffectPlayer() {}
    /**
     * @locale zh
     * @type api
     * @brief 开始播放音效文件。<br>
     *        可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个音效文件，实现音效叠加。
     * @param effect_id 音效 ID。用于标识音效，请保证音效 ID 唯一性。  <br>
     *        如果使用相同的 ID 重复调用本方法后，上一个音效会停止，下一个音效开始，并收到 onAudioEffectPlayerStateChanged{@link #IAudioEffectPlayerEventHandler#onAudioEffectPlayerStateChanged}。
     * @param file_path 音效文件路径。<br>
     *        支持在线文件的 URL、本地文件的 URI、或本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。<br>
     *        推荐的音效文件采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。<br>
     *        不同平台支持的本地音效文件格式:<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     *        不同平台支持的在线音效文件格式:<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @param config 音效配置，详见 AudioEffectPlayerConfig{@link #AudioEffectPlayerConfig}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 如果已经通过 preload{@link #IAudioEffectPlayer#preload} 将文件加载至内存，确保此处的 ID 与 preload{@link #IAudioEffectPlayer#preload} 设置的 ID 相同。<br>
     *       + 开始播放音效文件后，可以调用 stop{@link #IAudioEffectPlayer#stop} 方法停止播放音效文件。
     */
    /**
     * @locale en
     * @type api
     * @brief Starts to play the audio effect file. <br>
     *        This API can be called multiple times with different IDs and filepaths for multiple effects at the same time.
     * @param effect_id Audio effect ID. Used for identifying the audio effect, please ensure that the audio effect ID is unique.  <br>
     *        If this API is called repeatedly with the same ID, the previous effect will stop and the next effect will start, and you'll receive onAudioEffectPlayerStateChanged{@link #IAudioEffectPlayerEventHandler#onAudioEffectPlayerStateChanged}.
     * @param file_path Audio effect file paths.<br>
     *        URL of online file, URI of local file, or full path to the local file are supported. For URL of online file, only the https protocol is supported.<br>
     *        Recommended sample rate for audio effect files: 8KHz、16KHz、22.05KHz、44.1KHz、48KHz.<br>
     *        Local audio effect file formats supported by different platforms:<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     *        Online audio effect file formats supported by different platforms.<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @param config See AudioEffectPlayerConfig{@link #AudioEffectPlayerConfig}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note  
     *       + If the file has been loaded into memory via preload{@link #IAudioEffectPlayer#preload}, make sure that the ID here is the same as the ID set by preload{@link #IAudioEffectPlayer#preload}.<br>
     *       + After starting to play an audio effect file, you can call the stop{@link #IAudioEffectPlayer#stop} API to stop playing the audio effect file.
     */
    virtual int start(int effect_id, const char* file_path, const AudioEffectPlayerConfig& config) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 停止播放音效文件。
     * @param effect_id 音效 ID
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用 start{@link #IAudioEffectPlayer#start} 方法开始播放音效文件后，可以调用本方法停止播放音效文件。<br>
     *       + 调用本方法停止播放音效文件后，该音效文件会被自动卸载。
     */
    /**
     * @locale en
     * @type api
     * @brief Stops the playback of audio effect files.
     * @param effect_id Audio effect ID
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note  
     *       + After calling the start{@link #IAudioEffectPlayer#start} API to start playing the audio effect file, you can call this API to stop playing the audio effect file.<br>
     *       + After calling this API to stop playing an audio effect file, the audio effect file will be unloaded automatically.
     */
    virtual int stop(int effect_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 停止播放所有音效文件。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用 start{@link #IAudioEffectPlayer#start} 方法开始播放音效文件后，可以调用本方法停止播放所有音效文件。<br>
     *       + 调用本方法停止播放所有音效文件后，该音效文件会被自动卸载。
     */
    /**
     * @locale en
     * @type api
     * @brief Stops playback of all audio effect files.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note  
     *       + After calling start{@link #IAudioEffectPlayer#start} to start playing audio effect files, you can call this API to stop playing all audio effect files.<br>
     *       + After calling this API to stop playing all audio effect files, the audio effect files will be unloaded automatically.
     */
    virtual int stopAll() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。
     * @param effect_id 音效 ID。用于标识音效，请保证音效 ID 唯一性。  <br>
     *        如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br>
     *        如果先调用 start{@link #IAudioEffectPlayer#start}，再使用相同的 ID 调用本方法 ，会收到回调 onAudioEffectPlayerStateChanged{@link #IAudioEffectPlayerEventHandler#onAudioEffectPlayerStateChanged} ，通知前一个音效停止，然后加载下一个音效。  <br>
     *        调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 start{@link #IAudioEffectPlayer#start} 播放 B.mp3，请先调用 unload{@link #IAudioEffectPlayer#unload} 卸载 A.mp3 ，否则会报错 AUDIO_MIXING_ERROR_LOAD_CONFLICT。
     * @param file_path 音效文件路径。支持本地文件的 URI。<br>
     *                 预加载的文件长度不得超过 20s。<br>
     *                 不同平台支持的音效文件格式和 start{@link #IAudioEffectPlayer#start} 一致。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 本方法只是预加载指定音效文件，只有调用 start{@link #IAudioEffectPlayer#start} 方法才开始播放指定音效文件。<br>
     *       + 调用本方法预加载的指定音效文件可以通过 unload{@link #IAudioEffectPlayer#unload} 卸载。
     */
    /**
     * @locale en
     * @type api
     * @brief Preloads specified music files into memory to avoid repeated loading when playing the same file frequently and reduce CPU usage.
     * @param effect_id Audio effect ID。Used for identifying the audio effect. Please ensure that the audio effect ID is unique.<br>
     *        If this API is called repeatedly with the same ID, the later one will overwrite the previous one.<br>
     *        If you call start{@link #IAudioEffectPlayer#start} first and then call this API with the same ID, the SDK will stop the previous effect and then load the next one, and you will receive onAudioEffectPlayerStateChanged{@link #IAudioEffectPlayerEventHandler#onAudioEffectPlayerStateChanged}.<br>
     *        After calling this API to preload A.mp3, if you need to call start{@link #IAudioEffectPlayer#start} to play B.mp3 with the same ID, please call unload{@link #IAudioEffectPlayer#unload} to unload A.mp3 first, otherwise SDK will report an error AUDIO_MIXING_ERROR_LOAD_CONFLICT.
     * @param file_path The filepath of effect file. URI of local file, or full path to local file.<br>
     *        The length of the pre-loaded file must not exceed 20s.<br>
     *        Audio effect file formats supported are the same as start{@link #IAudioEffectPlayer#start}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note  
     *       + This API just preloads the specified audio effect file, and only calls the start{@link #IAudioEffectPlayer#start} API to start playing the specified audio effect file.<br>
     *       + The specified audio effect file preloaded by calling this API can be unloaded by unload{@link #IAudioEffectPlayer#unload}.
     */
    virtual int preload(int effect_id, const char* file_path) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 卸载指定音效文件。
     * @param effect_id 音效 ID
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 仅在调用 start{@link #IAudioEffectPlayer#start} 或 preload{@link #IAudioEffectPlayer#preload} 后调用此接口。
     */
    /**
     * @locale en
     * @type api
     * @brief Unloads the specified audio effect file.
     * @param effect_id Audio effect ID
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note Call this API after start{@link #IAudioEffectPlayer#start} or preload{@link #IAudioEffectPlayer#preload}.
     */
    virtual int unload(int effect_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 卸载所有音效文件。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @type api
     * @brief Unloads all audio effect files.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     */
    virtual int unloadAll() = 0;
   /**
     * @locale zh
     * @type api
     * @brief 暂停播放音效文件。
     * @param effect_id 音效 ID
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用 start{@link #IAudioEffectPlayer#start} 方法开始播放音效文件后，可以通过调用本方法暂停播放音效文件。<br>
     *       + 调用本方法暂停播放音效文件后，可调用 resume{@link #IAudioEffectPlayer#resume} 方法恢复播放。
     */
    /**
     * @locale en
     * @type api
     * @brief Pauses the playback of audio effect files.
     * @param effect_id Audio effect ID
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note
     *       + After calling the start{@link #IAudioEffectPlayer#start} API to start playing the audio effect file, you can pause the audio effect file by calling this API.<br>
     *       + After calling this API to pause the audio effect file, you can call the resume{@link #IAudioEffectPlayer#resume} API to resume playback.
     */
    virtual int pause(int effect_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 暂停播放所有音效文件。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note
     *       + 调用 start{@link #IAudioEffectPlayer#start} 方法开始播放音效文件后，可以通过调用本方法暂停播放所有音效文件。<br>
     *       + 调用本方法暂停播放所有音效文件后，可调用 resumeAll{@link #IAudioEffectPlayer#resumeAll} 方法恢复所有播放。
     */
    /**
     * @locale en
     * @type api
     * @brief Pauses the Playback of all audio effect files.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note
     *       + After calling the start{@link #IAudioEffectPlayer#start} API to start playing audio effect files, you can pause playing all audio effect files by calling this API.<br>
     *       + After calling this API to pause the playback of all audio effect files, you can call the resumeAll{@link #IAudioEffectPlayer#resumeAll} API to resume all playback.
     */
    virtual int pauseAll() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 恢复播放音效文件。
     * @param effect_id 音效 ID
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 调用 pause{@link #IAudioEffectPlayer#pause} 方法暂停播放音效文件后，可以通过调用本方法恢复播放。
     */
    /**
     * @locale en
     * @type api
     * @brief Resumes the playback of audio effect files.
     * @param effect_id Audio effect ID
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note After calling the pause{@link #IAudioEffectPlayer#pause} API to pause the audio effect file, you can resume playback by calling this API.
     */
    virtual int resume(int effect_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 恢复播放所有音效文件。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 调用 pauseAll{@link #IAudioEffectPlayer#pauseAll} 方法暂停所有正在播放音效文件后，可以通过调用本方法恢复播放。
     */
    /**
     * @locale en
     * @type api
     * @brief Resumes the playback of all audio effect files.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note After calling the pauseAll{@link #IAudioEffectPlayer#pauseAll} API to pause all the audio effect files being played, you can resume playback by calling this API.
     */
    virtual int resumeAll() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置音效文件的起始播放位置。
     * @param effect_id 音效 ID
     * @param pos 音效文件起始播放位置，单位为毫秒。<br>
     *        你可以通过 getDuration{@link #IAudioEffectPlayer#getDuration} 获取音效文件总时长，pos 的值应小于音效文件总时长。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 在播放在线文件时，调用此接口可能造成播放延迟的现象。<br>
     *        + 仅在调用 start{@link #IAudioEffectPlayer#start} 后调用此接口。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the start position of the audio effect file.
     * @param effect_id Audio effect ID
     * @param pos The starting playback position of the audio effect file in milliseconds.<br>
     *        You can get the total duration of the audio effect file by calling getDuration{@link #IAudioEffectPlayer#getDuration}, the value of pos should be less than the total duration of the audio effect file.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note 
     *        + When playing online files, calling this API may cause a delay in playback.<br>
     *        + Call this API after start{@link #IAudioEffectPlayer#start}.
     */
    virtual int setPosition(int effect_id, int pos) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取音效文件播放进度。
     * @param effect_id  音效 ID
     * @return  
     *        + >0: 成功, 音效文件播放进度，单位为毫秒。<br>
     *        + < 0: 失败
     * @note 
     *        + 在播放在线文件时，调用此接口可能造成播放延迟的现象。<br>
     *        + 仅在调用 start{@link #IAudioEffectPlayer#start} 后调用此接口。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the current position of audio effect file playback.
     * @param effect_id  Audio effect ID
     * @return  
     *        + >0: Success, the current progress of audio effect file playback in milliseconds.<br>
     *        + < 0: Failure.
     * @note 
     *        + When playing online files, calling this API may cause a delay in playback.<br>
     *        + Call this API after start{@link #IAudioEffectPlayer#start}.
     */
    virtual int getPosition(int effect_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 调节指定音效的音量大小，包括音效文件和 PCM 音频。
     * @param effect_id 音效 ID
     * @param volume 播放音量相对原音量的比值。单位为 %。范围为 `[0, 400]`，建议范围是 `[0, 100]`。带溢出保护。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 仅在调用 start{@link #IAudioEffectPlayer#start} 后调用此接口。
     */
    /**
     * @locale en
     * @type api
     * @brief Adjusts the volume level of a specified audio effect, including audio effect file and PCM effect.
     * @param effect_id Audio effect ID
     * @param volume The ratio of the volume to the original volume in % with overflow protection. The range is `[0, 400]` and the recommended range is `[0, 100]`.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note Call this API after start{@link #IAudioEffectPlayer#start}.
     */
    virtual int setVolume(int effect_id, int volume) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置所有音效的音量大小，包括音效文件和 PCM 音效。
     * @param volume 播放音量相对原音量的比值。单位为 %。范围为 `[0, 400]`，建议范围是 `[0, 100]`。带溢出保护。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该接口的优先级低于 setVolume{@link #IAudioEffectPlayer#setVolume}，即通过 setVolume{@link #IAudioEffectPlayer#setVolume} 单独设置了音量的音效 ID，不受该接口设置的影响。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the volume of all audio effect, including audio effect files and PCM effects.
     * @param volume The ratio of the volume to the original volume in % with overflow protection. The range is `[0, 400]` and the recommended range is `[0, 100]`.  
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note This API has a lower priority than setVolume{@link #IAudioEffectPlayer#setVolume}, i.e. the volume of the audio effect set by setVolume{@link #IAudioEffectPlayer#setVolume} is not affected by this API.
     */
    virtual int setVolumeAll(int volume) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取当前音量。
     * @param effect_id  音效 ID
     * @return  
     *        + >0: 成功, 当前音量值。  <br>
     *        + < 0: 失败
     * @note 仅在调用 start{@link #IAudioEffectPlayer#start} 后调用此接口。
     */
    /**
     * @locale en
     * @type api
     * @brief Gets the current volume.
     * @param effect_id  Audio effect ID
     * @return  
     *        + >0: Success, the current volume value.  <br>
     *        + < 0: Failed.
     * @note Call this API after start{@link #IAudioEffectPlayer#start}.
     */
    virtual int getVolume(int effect_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取音效文件时长。
     * @param effect_id  音效 ID
     * @return  
     *        + >0: 成功, 音效文件时长，单位为毫秒。  <br>
     *        + < 0: 失败
     * @note 仅在调用 start{@link #IAudioEffectPlayer#start} 后调用此接口。
     */
    /**
     * @locale en
     * @type api
     * @brief Get the duration of the audio effect file.
     * @param effect_id  Audio effect ID
     * @return  
     *        + >0: Success, the duration of the audio effect file in milliseconds.  <br>
     *        + < 0: failed.
     * @note Call this API after start{@link #IAudioEffectPlayer#start}.
     */
    virtual int getDuration(int effect_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置回调句柄。
     * @param handler 参看 IAudioEffectPlayerEventHandler{@link #IAudioEffectPlayerEventHandler}。
     * @return  
     *        + 0: 成功。  <br>
     *        + < 0: 失败。
     */
    /**
     * @locale en
     * @type api
     * @brief Set the event handler.
     * @param handler See IAudioEffectPlayerEventHandler{@link #IAudioEffectPlayerEventHandler}.
     * @return  
     *        + 0: Success.  <br>
     *        + < 0: Failed.
     */
    virtual int setEventHandler(IAudioEffectPlayerEventHandler* handler) = 0;
};

}
