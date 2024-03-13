/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Audio Mixing Manager
*/

#pragma once

#include "bytertc_audio_frame.h"

namespace bytertc {
/**
 * @locale zh
 * @hidden(Linux)
 * @type callback
 * @brief 本地音频文件混音的音频帧观察者。<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @hidden(Linux)
 * @type callback
 * @brief The observer for the audio frames during local audio file mixing.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IAudioFileFrameObserver {
public:
    /**
     * @hidden constructor/destructor
     */
    virtual ~IAudioFileFrameObserver(){}
    /**
     * @locale zh
     * @type callback
     * @brief 当本地音频文件混音时，回调播放的音频帧。
     * @param mix_id 混音 ID。
     * @param audio_frame 参看 IAudioFrame{@link #IAudioFrame}。
     */
    /**
     * @locale en
     * @type callback
     * @brief The callback for the audio frames during local audio file mixing.
     * @param mix_id Mixing ID.
     * @param audio_frame See IAudioFrame{@link #IAudioFrame}.
     */
    virtual void onAudioFileFrame(int mix_id, const IAudioFrame& audio_frame) = 0;
};

/**
 * @locale zh
 * @deprecated since 353. Use IAudioEffectPlayer{@link #IAudioEffectPlayer} and IMediaPlayer{@link #IMediaPlayer} instead.
 * @type api
 * @brief 混音管理类
 */
/**
 * @locale en
 * @deprecated since 353. Use IAudioEffectPlayer{@link #IAudioEffectPlayer} and IMediaPlayer{@link #IMediaPlayer} instead.
 * @type api
 * @brief Mixing management class
 */
class IAudioMixingManager {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 构造函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Constructor
     */
    IAudioMixingManager() {
    }
    /**
     * @locale zh
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer or IAudioEffectPlayer instead
     * @type api
     * @region 混音
     * @brief 开始播放音频文件。<br>
     *        可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。
     * @param mix_id 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br>
     *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，SDK 会使用 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调通知前一次混音已停止。
     * @param file_path 用于混音文件路径。<br>
     *        支持在线文件的 URL 和本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。<br>
     *        推荐的音频文件采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。<br>
     *        不同平台支持的本地音频文件格式:<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     *        不同平台支持的在线音频文件格式:<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @param config 混音配置  <br>
     *        可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 AudioMixingConfig{@link #AudioMixingConfig}。
     * @note  
     *       + 如果已经通过 preloadAudioMixing{@link #IAudioMixingManager#preloadAudioMixing} 将文件加载至内存，确保此处的 ID 与预加载时设置的 ID 相同。  <br>
     *       + 调用本方法播放音频文件后，关于当前的混音状态，会收到回调 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}。  <br>
     *       + 开始播放音频文件后，可以调用 stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} 方法停止播放音频文件。  <br>
     *       + 本方法的混音数据来源于外部文件，而 enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} 的混音数据来源于外部缓存且音频格式为 PCM，这两种混音方式可以共存。
     */
    /**
     * @locale en
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer or IAudioEffectPlayer instead
     * @type api
     * @region Audio Mixing
     * @brief  Start mixing audio files.<br>
     *         To mixing multiple audio files at the same time, you can call this method with different mixIDs.
     * @param mix_id Mix ID. Used to identify the mixing task. <br>
     *         If this method is repeatedly called with the same ID, the previous mixing task will be stopped and a new task will start. When the previous task is stopped, you will receive onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}.
     * @param file_path The path of the mixing audio file.<br>
     *        You can use the URL of the online file, and the absolute path of the local file. For the URL of the online file, only https protocol is supported.<br>
     *        Recommended audio sample rates: 8KHz, 16KHz, 22.05KHz, 44.1KHz, 48KHz.<br>
     *        Local audio file formats supported by different platforms:<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *           <tr><td>Linux</td><td></td><td></td><td></td><td></td><td></td><td>Y</td><td></td><td></td><td></td></tr>
     *        </table>
     *        Online audio file formats supported by different platforms:<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @param config Mixing configuration <br>
     *         You can set the number of times the file is played, whether the file is played locally or remotely. See AudioMixingConfig{@link #AudioMixingConfig}.
     * @note   
     *        + If you have already loaded the file in memory with preloadAudioMixing{@link #IAudioMixingManager#preloadAudioMixing}, ensure that the mixID is the same.  <br>
     *        + After calling this method, you will receive onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} about the current mixing status. <br>
     *        + Call stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} to stop the mixing task. <br>
     *        + The mixing data of this API comes from an audio file, while the mixing data of enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} comes from the PCM data from memory. The two mixing APIs do not affect each other.
     */
    virtual void startAudioMixing(int mix_id, const char * file_path, const AudioMixingConfig& config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 停止播放音频文件及混音。
     * @param mix_id  <br>
     *        混音 ID
     * @note  
     *       + 调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 方法开始播放音频文件及混音后，可以调用本方法停止播放音频文件及混音。  <br>
     *       + 调用本方法停止播放音频文件后，SDK 会向本地回调通知已停止混音，见 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}。  <br>
     *       + 调用本方法停止播放音频文件后，该音乐文件会被自动卸载。
     */
    /**
     * @locale en
     * @type api
     * @region  Mix
     * @brief Stops the specified mixing task
     * @param mix_id <br>
     *         Mix ID
     * @note   
     *        + After calling the startAudioMixing{@link #IAudioMixingManager#startAudioMixing} method to start playing music files and mixes, you can call this method to stop playing music files and mixes. <br>
     *        + After calling this method to stop playing the music file, the SDK notifies the local callback that the mixing has been stopped. See onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}. <br>
     *        + After calling this method to stop playing the music file, the music file will be automatically uninstalled.
     */
    virtual void stopAudioMixing(int mix_id) = 0;
    /**
     * @locale zh
     * @type api
     * @hidden(Linux)
     * @region 混音
     * @brief 停止播放所有音频文件及混音。
     * @note  
     *       + 调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 方法开始播放音频文件及混音后，可以调用本方法停止播放所有音频文件及混音。  <br>
     *       + 调用本方法停止播放所有音频文件及混音后，会收到 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调，通知已停止播放和混音。  <br>
     *       + 调用本方法停止播放所有音频文件及混音后，该音频文件会被自动卸载。
     */
    /**
     * @locale en
     * @type api
     * @hidden(Linux)
     * @region Mix
     * @brief Stop playing all audio files and mixes.
     * @note  
     *       + After calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to play audio files and mixes, you can call this api to stop playing all the files. <br>
     *       + After calling this api to stop playing all audio and mixes, you will receive onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} callback to inform you that the playing and mixing has been stopped.  <br>
     *       + After you call this api to stop playing all audio and mixes, the files will be automatically uninstalled.
     */
    virtual void stopAllAudioMixing() = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 暂停播放音频文件及混音。
     * @param mix_id  <br>
     *        混音 ID
     * @note  
     *       + 调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 方法开始播放音频文件及混音后，可以通过调用本方法暂停播放音频文件及混音。  <br>
     *       + 调用本方法暂停播放音频文件及混音后，可调用 resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} 方法恢复播放及混音。  <br>
     *       + 调用本方法暂停播放音频文件后，SDK 会向本地回调通知已暂停混音，见 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}。
     */
    /**
     * @locale en
     * @type api
     * @region  Mix
     * @brief  Pause playing music files and mixes
     * @param mix_id <br>
     *         Mix ID
     * @note   
     *        + After calling the startAudioMixing{@link #IAudioMixingManager#startAudioMixing} method to start playing music files and mixes, you can call this method to pause playing music files and mixes. <br>
     *        + After calling this method to pause playing music files and mixing, you can call the resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} method to resume playing and mixing. <br>
     *        + After calling this method to pause playing the music file, the SDK will notify the local callback that the mixing has been suspended. See onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}.
     */
    virtual void pauseAudioMixing(int mix_id) = 0;
    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IAudioEffectPlayer instead
     * @hidden(Linux)
     * @region 混音
     * @brief 暂停播放所有音频文件及混音。
     * @note  
     *       + 调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 方法开始播放音频文件及混音后，可以通过调用本方法暂停播放所有音频文件及混音。  <br>
     *       + 调用本方法暂停播放所有音频文件及混音后，可调用 resumeAllAudioMixing{@link #IAudioMixingManager#resumeAllAudioMixing} 方法恢复所有播放及混音。  <br>
     *       + 调用本方法暂停播放所有音频文件及混音后，会收到 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调，通知已暂停播放和混音。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IAudioEffectPlayer instead
     * @hidden(Linux)
     * @region Mix
     * @brief Pause all audio files and mixes.
     * @note  
     *       + After calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing}  to play audio files and mixes, you can call this api to pause all the files. <br>
     *       + After calling this api to pause all audio and mixes, you can call resumeAllAudioMixing{@link #IAudioMixingManager#resumeAllAudioMixing} to resume the playing and mixing.   <br>
     *       + After calling this api to pause all audio and mixes, you will receive onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} callback to inform you that the playing and mixing has been paused.
     */
    virtual void pauseAllAudioMixing() = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 恢复播放音频文件及混音。
     * @param mix_id  <br>
     *        混音 ID
     * @note  
     *       + 调用 pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} 方法暂停播放音频文件及混音后，可以通过调用本方法恢复播放及混音。  <br>
     *       + 调用本方法恢复播放音频文件及混音后，SDK 会向本地回调通知音乐文件正在播放中，见 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}。
     */
    /**
     * @locale en
     * @type api
     * @region  Mixing
     * @brief Resumes playing music files and mixing.
     * @param mix_id <br>
     *         ID of the mixing task
     * @note   
     *        + After calling the pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} method to pause playing music files and mixing, you can resume playing and mixing by calling this method. <br>
     *        + After calling this method to resume playing the music file and mixing, the SDK will notify the local callback that the music file is playing. See onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}.
     */
    virtual void resumeAudioMixing(int mix_id) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IAudioEffectPlayer instead
     * @hidden(Linux)
     * @region 混音
     * @brief 恢复播放所有音频文件及混音。
     * @note  
     *       + 调用 pauseAllAudioMixing{@link #IAudioMixingManager#pauseAllAudioMixing} 方法暂停所有正在播放音频文件及混音后，可以通过调用本方法恢复播放及混音。  <br>
     *       + 调用本方法恢复播放所有音频文件及混音后，会收到 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调，通知已恢复播放和混音。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IAudioEffectPlayer instead
     * @hidden(Linux)
     * @region Mix
     * @brief Resume playing all audio files and mixes.
     * @note  
     *       + After calling pauseAllAudioMixing{@link #IAudioMixingManager#pauseAllAudioMixing} , you can call this api to resume playing all the files. <br>
     *       + After calling this api to resume all audio and mixes, you will receive onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} callback to inform you that the playing and mixing has been resumed.
     */
    virtual void resumeAllAudioMixing() = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。
     * @param mix_id 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br>
     *        如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br>
     *        如果先调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing}，再使用相同的 ID 调用本方法 ，会先回调 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 通知上一个混音停止，然后加载后一个混音。  <br>
     *        调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 播放 B.mp3，请先调用 unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} 卸载 A.mp3。
     * @param file_path 混音文件路径。仅支持本地文件的绝对路径。预加载的文件长度不得超过 20s。<br>
     *        不同平台支持的音频文件格式：<br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @note  
     *       + 本方法只是预加载指定音频文件，只有调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 方法才开始播放指定音频文件。 <br>
     *       + 调用本方法预加载音频文件后，关于当前的混音状态，会收到回调 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}。  <br>
     *       + 调用本方法预加载的指定音频文件可以通过 unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} 卸载。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Mixing
     * @brief Preloads the audio file into memory to minimize the loading cost of playing repeatedly.
     * @param mix_id Mix ID. Used to identify the mixing task. <br>
     *        If this method is repeatedly called with the same ID, the previous file will be unloaded and the new file will be loaded. <br>
     *        If you call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} and then call this method with the same ID, the previous mixing task will be stopped, and then the next file will be loaded. <br>
     *        After calling this method to preload A.mp3, if you need to call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to play B.mp3 with the same ID, call unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} to unload A.mp3 first.
     * @param file_path The absolute path of the local file to preload. You can only preload the audio file of length less than 20s.<br>
     *         Audio file formats supported by different platforms: <br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @note   
     *        + After preloaded, call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to play the audio file. <br>
     *        + After calling this method, you will receive onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} about the current mixing status. <br>
     *        + Unload the preloaded file with unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing}.
     */
    virtual void preloadAudioMixing(int mix_id, const char* file_path) = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 卸载指定音乐文件。
     * @param mix_id  <br>
     *        混音 ID
     * @note 不论音乐文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Mixing
     * @brief Uninstalls the specified music file.
     * @param mix_id <br>
     *        Mix ID
     * @note Whether the music file is playing or not, after calling this method to uninstall the file, the SDK will call back to notify that the mix has stopped. See onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged}.
     */
    virtual void unloadAudioMixing(int mix_id) = 0;

    /**
     * @locale zh
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IAudioEffectPlayer instead
     * @region 混音
     * @brief 设置默认的混音音量大小，包括音频文件混音和 PCM 混音。
     * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
     *        + 0：静音  <br>
     *        + 100：原始音量（默认值）  <br>
     *        + 400: 最大可调音量 (自带溢出保护)
     * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 AudioMixingType{@link #AudioMixingType}。
     * @note 
     *        + 该功能适用于移动端。<br>
     *        + 该接口的优先级低于 setAudioMixingVolume{@link #IAudioMixingManager#setAudioMixingVolume}，即通过 setAudioMixingVolume{@link #IAudioMixingManager#setAudioMixingVolume} 单独设置了音量的混音 ID，不受该接口设置的影响。
     */
    /**
     * @locale en
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IAudioEffectPlayer instead
     * @region Audio Mixing
     * @brief Sets the default volume during audio mixing, which works for both audio file mixing and PCM mixing.
     * @param volume The ratio of the mixing volume to the original volume. The range is `[0, 400]`. The recommended range is `[0, 100]`. <br>
     *         + 0: Mute <br>
     *         + 100: Original volume <br>
     *         + 400: Maximum volume (with overflow protection)
     * @param type See AudioMixingType{@link #AudioMixingType}.
     * @note 
     *        + This feature is available for mobile apps.<br>
     *        + This API does not work for the mixing ID for which the volume has been set specifically by setAudioMixingVolume{@link #IAudioMixingManager#setAudioMixingVolume}.
     */
    virtual void setAllAudioMixingVolume(int volume, AudioMixingType type) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 混音
     * @brief 调节指定混音的音量大小，包括音频文件混音和 PCM 混音。
     * @param mix_id 需调节音量的混音 ID
     * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
     *        + 0：静音  <br>
     *        + 100：原始音量（默认值）  <br>
     *        + 400: 最大可调音量 (自带溢出保护)
     * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 AudioMixingType{@link #AudioMixingType}。
     * @note 该方法仅对指定混音 ID 生效。移动端提供 `setAllAudioMixingVolume` 接口调节全部混音文件播放音量。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Audio Mixing
     * @brief Adjust the volume of audio mixing, including audio files and PCM data.
     * @param mix_id ID of the mixing task
     * @param volume The ratio of the mixing volume to the original volume. The range is `[0, 400]`. The recommended range is `[0, 100]`. <br>
     *         + 0: Mute <br>
     *         + 100: Original volume <br>
     *         + 400: Maximum volume (with overflow protection)
     * @param type See AudioMixingType{@link #AudioMixingType}.
     * @note This API works only for the specified mix ID. Call `setAllAudioMixingVolume` if you want to set the default volume for all the audio mixing tasks, which is for mobile apps only.
     */
    virtual void setAudioMixingVolume(int mix_id, int volume, AudioMixingType type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 获取音频文件时长。
     * @param mix_id  <br>
     *        混音 ID
     * @return  
     *        + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
     *        + < 0: 失败
     * @note 调用本方法获取音乐文件时长前，需要先调用 preloadAudioMixing{@link #preloadAudioMixing} 或 startAudioMixing{@link #IAudioMixingManager#startAudioMixing}。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Mixing
     * @brief Gets the duration of the music file.
     * @param mix_id <br>
     *        Mix ID
     * @return   
     *         + > 0: Success, the duration of the music file, in milliseconds. <br>
     *         + < 0: Failed
     * @note  Before calling this method to get the length of the music file, you need to call preloadAudioMixing{@link #preloadAudioMixing} or startAudioMixing{@link #IAudioMixingManager#startAudioMixing}.
     */
    virtual int getAudioMixingDuration(int mix_id) = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 获取音频文件播放进度。
     * @param mix_id  <br>
     *        混音 ID
     * @return  
     *        + >0: 成功, 音乐文件播放进度，单位为毫秒。  <br>
     *        + < 0: 失败
     * @note 调用本方法获取音乐文件播放进度前，需要先调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音乐文件。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Mixing
     * @brief Gets the music file playback progress.
     * @param mix_id <br>
     *        Mix ID
     * @return   
     *         + > 0: Success, the music file playback progress, in milliseconds. <br>
     *         + < 0: Failed
     * @note  Before calling this method to get the progress of music file playback, you need to call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing music files.
     */
    virtual int getAudioMixingCurrentPosition(int mix_id) = 0;

    /**
     * @locale zh
     * @hidden(Linux,macOS)
     * @type api
     * @region 混音
     * @brief 获取混音音频文件的实际播放时长（单位：毫秒）。
     * @param mix_id 混音 ID。
     * @return  
     *        + >0: 实际播放时长。 <br>
     *        + < 0: 失败。
     * @note 
     *        + 实际播放时长指的是歌曲不受停止、跳转、倍速、卡顿影响的播放时长。例如，若歌曲正常播放到 1:30 时停止播放 30s 或跳转进度到 2:00, 随后继续正常播放 2分钟，则实际播放时长为 3分30秒。  <br>
     *        + 调用本接口前，需要先调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放指定音频文件。
     */
    /**
     * @locale en
     * @hidden(Linux,macOS)
     * @type api
     * @region Audio Mixing
     * @brief Get the actual time played of the audio file.
     * @param mix_id The audio mixing ID.
     * @return   
     *         + > 0: The actual time played(in millisecond). <br>
     *         + < 0: Failure.
     * @note  
     *        + The actual time played excludes the time when the file is paused, sped up, rewound, and fast-forwarded. For example, if a song plays 1:30 minutes and plays another 2 minutes after being paused for 30 seconds or fast-forwarded to 2:00,the actual time played will be 3.5 minutes.<br>
     *        + Before calling this API, you must call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to play the audio file.
     */
    virtual int getAudioMixingPlaybackDuration(int mix_id) = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 设置音频文件的起始播放位置
     * @param mix_id 混音 ID
     * @param position 音频文件起始播放位置，单位为毫秒。  <br>
     *        你可以通过 getAudioMixingDuration{@link #IAudioMixingManager#getAudioMixingDuration} 获取音频文件总时长，position 的值应小于音频文件总时长。
     * @note 在播放在线文件时，调用此接口可能造成播放延迟的现象。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Mixing
     * @brief Sets the starting position of the audio file for audio mixing.
     * @param mix_id ID of the mixing task.
     * @param position The starting position in ms. <br>
     *        You can get the length of the file with getAudioMixingDuration{@link #IAudioMixingManager#getAudioMixingDuration}. The value of the position must be less than the length of the file.
     * @note When mixing online files, calling this API may cause mixing delay.
     */
    virtual void setAudioMixingPosition(int mix_id, int position) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region 混音
     * @brief 设置当前音频文件的声道模式
     * @param mix_id 混音 ID
     * @param mode 声道模式。默认的声道模式和源文件一致，详见 AudioMixingDualMonoMode{@link #AudioMixingDualMonoMode}。
     * @note 
     *        + 调用本方法设置音频文件的声道模式前，需要先调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件。<br>
     *        + 此方法对 enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} 播放的音乐无效。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region  Mix
     * @brief Sets the channel mode of the current audio file
     * @param mix_id Mix ID
     * @param mode Channel mode. The default channel mode is the same as the source file. See AudioMixingDualMonoMode{@link #AudioMixingDualMonoMode}.
     * @note  
     *         + Before calling this method to set the channel mode of the audio file, you need to call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file. <br>
     *         + This method is invalid for music played by enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame}.
     */
    virtual void setAudioMixingDualMonoMode(int mix_id, AudioMixingDualMonoMode mode) = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br>
     *        使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。
     * @param mix_id 混音 ID
     * @param pitch 相对于音乐文件原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
     *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
     *        超出取值范围则设置失败，并且会触发 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调，提示 AudioMixingState{@link #AudioMixingState} 状态为 `AUDIO_MIXING_STATE_FAILED` 混音播放失败，AudioMixingError{@link #AudioMixingError} 错误码为 `AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH` 设置混音文件音调不合法。
     * @note 本方法需要在调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件后、调用 stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} 停止播放音频文件前使用，否则会触发 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调报错
     */
    /**
     * @locale en
     * @type api
     * @region Audio Mixing
     * @brief Enables local playback of music files in a different key, mostly used in Karaoke scenarios.  <br>
     *        You can adjust the pitch of locally played music files such as ascending or descending with this method.
     * @param mix_id ID of the mixing task
     * @param pitch The value that is higher or lower than the original pitch of the audio file within a range from -12 to 12. The default value is 0, i.e. No adjustment is made.  <br>
     *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
     *        Out of the value range, the setting fails and triggers the onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} callback, indicating `AUDIO_MIXING_STATE_FAILED` for playback failure with AudioMixingState{@link # AudioMixingState}, and `AUDIO_MIXING_ERROR_ID_TYPE_ INVALID_PITCH` for invalid value setting with AudioMixingError{@link #AudioMixingError}.
     * @note This method needs to be used after calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file and before calling stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} to stop playing the audio file, otherwise the onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} callback will be triggered.
     */
    virtual void setAudioMixingPitch(int mix_id, int pitch) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region 混音
     * @brief 设置混音时音频文件的播放速度
     * @param mix_id 混音 ID
     * @param speed 播放速度与原始文件速度的比例，单位：%，取值范围为 [50,200]，默认值为 100。  <br>
     *        超出取值范围则设置失败，你会收到 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调，提示 AudioMixingState{@link #AudioMixingState} 状态为 `kAudioMixingStateFailed` 混音播放失败，AudioMixingError{@link #AudioMixingError} 错误码为 `kAudioMixingErrorInValidPlaybackSpeed` 设置混音文件的播放速度不合法。
     * @note   
     *        + 暂不支持对 PCM 音频数据进行变速调整。  <br>
     *        + 你需要在调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始混音，并且收到onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调提示 AudioMixingState{@link #AudioMixingState} 状态为 `kAudioMixingStatePlaying`，AudioMixingError{@link #AudioMixingError} 错误码为 `kAudioMixingErrorOk` 之后调用该方法。  <br>
     *        + 在 stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} 停止混音或 unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} 卸载音频文件后调用该 API，会收到状态为 `kAudioMixingStateFailed` 错误码为 `kAudioMixingErrorIdNotFound` 的 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region Audio Mixing
     * @brief Sets the playback speed of the current audio file.
     * @param mix_id Audio mixing task ID
     * @param speed Ratio of playback speed to original speed in percentage. The range is [50,200], the default value is 100.  <br>
     *        If the value you set is out of range, the setting fails, and you will receive an onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} callback, in which the AudioMixingState{@link #AudioMixingState} is `kAudioMixingStateFailed` and the AudioMixingError{@link #AudioMixingError} is `kAudioMixingErrorInValidPlaybackSpeed`.
     * @note   
     *        + This API can not be used on setting playback speed for PCM audio data.  <br>
     *        + You should call this API after calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} and receiving an onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} callback indicating that the AudioMixingState{@link #AudioMixingState} is `kAudioMixingStatePlaying` and the AudioMixingError{@link #AudioMixingError} is `kAudioMixingErrorOk`.  <br>
     *        + If you call this API after calling stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} or unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing}, you will receive an onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} callback indicating that the AudioMixingState{@link #AudioMixingState} is `kAudioMixingStateFailed` and the AudioMixingError{@link #AudioMixingError} is `kAudioMixingErrorIdNotFound`.
     */
    virtual int setAudioMixingPlaybackSpeed(int mix_id, int speed) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer  instead
     * @region 混音
     * @brief 设置混音时音频文件播放进度回调的间隔
     * @param mix_id 混音 ID  <br>
     *        可以通过多次调用本接口传入不同的 ID 对多个 ID 进行间隔设置。
     * @param interval 音频文件播放进度回调的时间间隔，单位毫秒。  <br>
     *       + interval 的值为大于 0 的 10 的倍数，当设置的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。设置完成后 SDK 将会按照设置的时间间隔触发 `onAudioMixingPlayingProgress` 回调。  <br>
     *       + interval 的值小于等于 0 时，不会触发进度回调。  
     * @note 本方法需要在调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件后、调用 stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} 停止播放音频文件前使用，否则会触发 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 回调报错。  <br>
     *        若想在音乐文件开始播放前设置播放进度回调间隔，你需调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 在 AudioMixingConfig{@link #AudioMixingConfig} 中设置时间间隔，开始播放后可以通过此接口更新回调间隔。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer  instead
     * @region Audio Mixing
     * @brief Sets the interval of audio file playback progress callbacks during audio mixing.
     * @param mix_id ID of the mixing task.<br>
     *        You can set the interval for multiple IDs by calling this method multiple times and passing in different IDs.
     * @param interval The time interval (ms) of the audio file playback progress callback in milliseconds.  <br>
     *       + The value of interval is a multiple of 10 greater than 0. When the value set is not divisible by 10, the default is rounded up by 10. For example, if the value is set to 52ms, it will be automatically adjusted to 60ms, then the SDK will trigger `onAudioMixingPlayingProgress` callback at the set interval.  <br>
     *       + If the value is less than or equals to 0, the callback will not be triggered.  
     * @note This method needs to be used after calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file, and before calling stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} to stop playing the audio file, otherwise an error callback onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} will be triggered.  <br>
     *        If you want to set the interval of playback progress callbacks before the music file starts playing, you need to call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to set the interval in AudioMixingConfig{@link #AudioMixingConfig}, and you can update the callback interval through this method after the audio file starts playing.
     */
    virtual void setAudioMixingProgressInterval(int mix_id, int64_t interval) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region 混音
     * @brief 如果你需要使用 `enableVocalInstrumentBalance` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。
     * @param mix_id 混音 ID
     * @param loudness 原始响度，单位：lufs，取值范围为 [-70.0, 0.0]。  <br>
     *        当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音均衡处理。默认值为 1.0lufs，即不做处理。
     * @note 建议在 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件之前调用该接口，以免播放过程中的音量突变导致听感体验下降。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region Audio Mixing
     * @brief If you need to call `enableVocalInstrumentBalance` to adjust the volume of the audio file or PCM data used for audio mixing, you must import the original loudness value of the audio file or PCM data via this API.
     * @param mix_id ID of the mixing task
     * @param loudness Original loudness of the audio file in lufs. The range is [-70.0, 0.0].  <br>
     *        If the value is set to be less than -70.0lufs, it is automatically adjusted to -70.0lufs. If the value is set to be greater than 0.0lufs, SDK will not equalize the loudness. The default value is 1.0lufs, i.e. No loudness equalization effect.
     * @note To avoid sudden volume changes during audio file playback, we recommend that you call this API before starting to play the audio file with startAudioMixing{@link #IAudioMixingManager#startAudioMixing}.
     */
    virtual void setAudioMixingLoudness(int mix_id, float loudness) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region 混音
     * @brief 启动 PCM 音频数据混音。<br>
     *        要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 mix_id。
     * @param mix_id 混音 ID，用于标识混音，保证混音 ID 唯一性。  <br>
     *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，会收到 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} 通知前一次混音已停止。
     * @param type 混音播放类型  <br>
     *        是否本地播放、以及是否发送到远端，详见 AudioMixingType{@link #AudioMixingType}。
     * @note  
     *       + 必须先调用本方法启动 PCM 音频数据混音，随后调用 pushAudioMixingFrame{@link #pushAudioMixingFrame} 方法，才会开始混音。 <br>
     *       + 如要结束 PCM 音频数据混音，使用 disableAudioMixingFrame{@link #IAudioMixingManager#disableAudioMixingFrame}。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region Audio Mixing
     * @brief Starts PCM mixing. <br>
     *        To mix multiple PCM audio data, call this API multiple times with different mix_ids.
     * @param mix_id ID of the mixing task. Used to identify the mixing. Ensure it is unique. <br>
     *        If this API is called repeatedly with the same mix_id, the previous mixing will stop, and the next mixing will start, and you will receive onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onaudiomixingstatechanged} notification that the previous mixing has stopped.
     * @param type Mixing type <br>
     *        Whether the PCM data is mixed locally and sent to the remotes. See AudioMixingType{@link #AudioMixingType}.
     * @note   
     *        + After this API, you must call pushAudioMixingFrame{@link #pushAudioMixingFrame} to start mixing. <br>
     *        + To end PCM mixing, use disableAudioMixingFrame{@link #IAudioMixingManager#disableAudioMixingFrame}.
     */
    virtual void enableAudioMixingFrame(int mix_id, AudioMixingType type) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region 混音
     * @brief 关闭 PCM 混音
     * @param mix_id 混音 ID。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region Audio Mixing
     * @brief End PCM mixing.
     * @param mix_id ID of the mixing task.
     */
    virtual void disableAudioMixingFrame(int mix_id) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region 混音
     * @brief 推送 PCM 音频帧数据用于混音
     * @param mix_id 混音 ID。
     * @param audio_frame 音频帧，详见 IAudioFrame{@link #IAudioFrame}。
     * @return  
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @note
     *      + 调用该方法前，须通过 enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} 启动外部音频流混音。  <br>
     *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 100 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。要暂停播放，暂停推送即可。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region Audio Mixing
     * @brief Push PCM audio frame data for mixing
     * @param mix_id ID of the mixing task.
     * @param audio_frame See IAudioFrame{@link #IAudioFrame}.
     * @return   
     *        + 0: Success <br>
     *        + < 0: Failure
     * @note
     *       + Before calling this method, you must start the external audio stream mixing through enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame}. <br>
     *       + Use reference suggestions: For the first time to push data, please cache certain data (such as 100 milliseconds) on the application side, and then push it at once; after that, the push operation is timed to be once in 10 milliseconds, and the amount of audio data each time is 10 milliseconds. To pause PCM mixing, pause pushing PCM data.
     */
    virtual int pushAudioMixingFrame(int mix_id, IAudioFrame* audio_frame) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region 混音
     * @brief 获取当前音频文件的音轨索引
     * @param mix_id 混音 ID
     * @return 方法调用结果 <br>
     *        + ≥ 0：成功，返回当前音频文件的音轨索引  <br>
     *        + < 0：方法调用失败
     * @note  
     *       + 调用本方法获取音频文件的音轨前，需要先调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件。<br>
     *       + 此方法对 enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} 播放的音频无效。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region Audio Mixing
     * @brief Gets the track index of the current audio file
     * @param mix_id Mixding ID
     * @return  
     *        + >= 0: Succeeded, the SDK will return the track index of the current audio file.  <br>
     *        + < 0: Failed
     * @note  
     *       + Before using this method, you should call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file. <br>
     *       + This method is invalid for music played using enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame}.
     */
    virtual int getAudioTrackCount(int mix_id) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region 混音
     * @brief 指定当前音频文件的播放音轨
     * @param mix_id 混音 ID
     * @param audio_track_index 指定的播放音轨  <br>
     *        设置的参数值需要小于或等于 getAudioTrackCount{@link #IAudioMixingManager#getAudioTrackCount} 的返回值
     * @note  
     *       + 调用本方法设置音频文件的音轨前，需要先调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件。<br>
     *       + 此方法对 enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} 播放的音乐无效。
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @region Audio Mixing
     * @brief Specifies the playback track of the current audio file.
     * @param mix_id ID of the mixing task.
     * @param audio_track_index The specified playback track.  <br>
     *        The set parameter value needs to be less than or equal to the return value of getAudioTrackCount{@link #IAudioMixingManager#getAudioTrackCount}.
     * @note  
     *       + Before using this method, you should call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file. <br>
     *       + This method is invalid for music played using enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame}.
     */
    virtual void selectAudioTrack(int mix_id, int audio_track_index) = 0;
    /**
     * @locale zh
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @hidden(Linux)
     * @type api
     * @brief 注册本地音频文件混音的音频帧观察者。<br>
     *        当本地音频文件混音时，会收到相关回调。
     * @param observer 参看 IAudioFileFrameObserver{@link #IAudioFileFrameObserver}。
     */
    /**
     * @locale en
     * @deprecated since 353.1, will be deleted in 359, use IMediaPlayer instead
     * @hidden(Linux)
     * @type api
     * @brief Register the observer for the audio frames during local audio file mixing.
     * @param observer See IAudioFileFrameObserver{@link #IAudioFileFrameObserver}。
     */
    virtual void registerAudioFileFrameObserver(IAudioFileFrameObserver* observer) = 0;

    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IAudioMixingManager() {
    }
};

}  // namespace bytertc
