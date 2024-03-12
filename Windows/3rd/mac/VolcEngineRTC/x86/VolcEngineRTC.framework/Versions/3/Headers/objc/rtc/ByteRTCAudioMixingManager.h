/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCAudioMixingManager
*/

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"
/**
 * @locale zh
 * @type callback
 * @brief 本地音频文件混音的音频帧观察者。<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief The observer for the audio frames during local audio file mixing.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCAudioFileFrameObserver <NSObject>
/**
 * @locale zh
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @type callback
 * @brief 当本地音频文件混音时，回调播放的音频帧。
 * @param mixID 混音 ID。
 * @param audioFrame 参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 */
/**
 * @locale en
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @type callback
 * @brief The callback for the audio frames during local audio file mixing.
 * @param mixID Mixing ID.
 * @param audioFrame See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 */
- (void)onAudioFileFrame:(int)mixID audioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

@end

/**
 * @locale zh
 * @deprecated since 353. Use ByteRTCAudioEffectPlayer{@link #ByteRTCAudioEffectPlayer} and ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer} instead.
 * @type api
 * @region 混音
 * @note 使用混音功能时，你必须通过 [setActive:withOptions:error:](https://developer.apple.com/documentation/avfaudio/avaudiosession/1616627-setactive?language=objc) 激活应用的 audio session。直到彻底退出混音功能后，才可以关闭 audio session。
 */
/**
 * @locale en
 * @deprecated since 353. Use ByteRTCAudioEffectPlayer{@link #ByteRTCAudioEffectPlayer} and ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer} instead.
 * @type api
 * @region Audio Mixing
 * @note When using audio mixing function, you must call [setActive:withOptions:error:](https://developer.apple.com/documentation/avfaudio/avaudiosession/1616627-setactive?language=objc) to activate the app's audio session. You can deactivate the audio session after quitting audio mixing scenario.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioMixingManager : NSObject
/**
 * @locale zh
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead
 * @type api
 * @region 混音
 * @brief 开始播放音频文件。<br>
 *        可以通过传入不同的 mixId 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。
 * @param mixId 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br>
 *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，SDK 会使用 `onAudioMixingStateChanged` 回调通知前一次混音已停止。
 * @param filePath 用于混音文件路径。<br>
 *        支持在线文件的 URL 和本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。<br>
 *        推荐的音频文件采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。<br>
 *        不同平台支持的本地音频文件格式:<br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *           <tr><td>Linux</td><td></td><td></td><td></td><td></td><td></td><td>Y</td><td></td><td></td><td></td></tr>
 *        </table>
 *        不同平台支持的在线音频文件格式:<br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @param config 混音配置  <br>
 *        可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig}
 * @note  
 *       + 如果已经通过 preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} 将文件加载至内存，确保此处的 ID 与预加载时设置的 ID 相同。  <br>
 *       + 调用本方法播放音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  <br>
 *       + 开始播放音频文件后，可以调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 方法停止播放音频文件。  <br>
 *       + 本方法的混音数据来源于外部文件，而 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 的混音数据来源于外部缓存且音频格式为 PCM，这两种混音方式可以共存。
 */
/**
 * @locale en
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead
 * @type api
 * @region Audio Mixing
 * @brief  Start mixing audio files.<br>
 *         To mixing multiple audio files at the same time, you can call this method with different mixIDs.
 * @param mixId Mix ID. Used to identify the mixing task. <br>
 *         If this method is repeatedly called with the same ID, the previous mixing task will be stopped and a new task will start. When the previous task is stopped, you will receive `onAudioMixingStateChanged`.
 * @param filePath The path of the mixing audio file.<br>
 *        You can use the URL of the online file, and the absolute path of the local file. For the URL of the online file, only https protocol is supported.<br>
 *        Recommended audio sample rates: 8KHz, 16KHz, 22.05KHz, 44.1KHz, 48KHz.<br>
 *        Local audio file formats supported by different platforms: <br>
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
 *         You can set the number of times the file is played, whether the file is played locally or remotely. See ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig}.
 * @note   
 *        + If you have already loaded the file in memory with preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:}, ensure that the mixID is the same.  <br>
 *        + After calling this method, you will receive `onAudioMixingStateChanged` about the current mixing status. <br>
 *        + Call stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} to stop the mixing task. <br>
 *        + The mixing data of this API comes from an audio file, while the mixing data of enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} comes from the PCM data from memory. The two mixing APIs do not affect each other.
 */
-(void)startAudioMixing:(int)mixId filePath:(NSString * _Nullable)filePath config:(ByteRTCAudioMixingConfig * _Nullable)config
    __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead");

/**
 * @locale zh
 * @type api
 * @region 混音
 * @brief 停止播放音频文件及混音。
 * @param mixId  <br>
 *        混音 ID
 * @note  
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音频文件及混音后，可以调用本方法停止播放音频文件及混音。  <br>
 *       + 调用本方法停止播放音频文件后，SDK 会向本地回调通知已停止混音，见 `onAudioMixingStateChanged`。  <br>
 *       + 调用本方法停止播放音频文件后，该音频文件会被自动卸载。
 */
/**
 * @locale en
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead
 * @type api
 * @region  Mix
 * @brief  Stop playing and mixing audio files and
 * @param mixId   <br>
 *         Mix ID
 * @note   
 *        + Call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} After the method starts playing audio files and mixes, you can call this method to stop playing audio files and mixes. <br>
 *        + After calling this method to stop playing the audio file, the SDK will notify the local callback that the mixing has been stopped. See `onAudioMixingStateChanged`. <br>
 *        + After calling this method to stop playing the audio file, the audio file will be automatically uninstalled.
 */
- (void)stopAudioMixing:(int)mixId __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead");
/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region 混音
 * @brief 停止播放所有音频文件及混音。
 * @note  
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音频文件及混音后，可以调用本方法停止播放所有音频文件及混音。  <br>
 *       + 调用本方法停止播放所有音频文件及混音后，会收到 `onAudioMixingStateChanged` 回调，通知已停止播放和混音。  <br>
 *       + 调用本方法停止播放所有音频文件及混音后，该音频文件会被自动卸载。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region Mix
 * @brief Stop playing all audio files and mixes.
 * @note  
 *       + After calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play audio files and mixes, you can call this api to stop playing all the files. <br>
 *       + After calling this api to stop playing all audio and mixes, you will receive `onAudioMixingStateChanged` callback to inform you that the playing and mixing has been stopped.  <br>
 *       + After you call this api to stop playing all audio and mixes, the files will be automatically uninstalled.
 */
-(void)stopAllAudioMixing __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead");;

/**
 * @locale zh
 * @type api
 * @region 混音
 * @brief 暂停播放音频文件及混音。
 * @param mixId  <br>
 *        混音 ID
 * @note  
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音频文件及混音后，可以通过调用该方法暂停播放音频文件。  <br>
 *       + 调用本方法暂停播放音频文件后，可调用 resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} 方法恢复播放及混音。  <br>
 *       + 调用本方法暂停播放音频文件后，SDK 会向本地回调通知已暂停混音，见 `onAudioMixingStateChanged`。
 */
/**
 * @locale en
 * @type api
 * @region  Mix
 * @brief  Pause playing audio files
 * @param mixId   <br>
 *         Mix ID
 * @note   
 *        + After calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} method to start playing audio files and mixing, you can pause playing audio files by calling this method. <br>
 *        + After calling this method to pause playing audio files, you can call the resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} method to resume playing and mixing. <br>
 *        + After calling this method to pause playing audio files, the SDK will notify the local callback that the mixing has been suspended. See `onAudioMixingStateChanged`.
 */
-(void)pauseAudioMixing:(int)mixId __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead");
/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region 混音
 * @brief 暂停播放所有音频文件及混音。
 * @note  
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}方法开始播放音频文件及混音后，可以通过调用本方法暂停播放所有音频文件及混音。  <br>
 *       + 调用本方法暂停播放所有音频文件及混音后，可调用 resumeAllAudioMixing{@link #ByteRTCAudioMixingManager#resumeAllAudioMixing} 方法恢复所有播放及混音。  <br>
 *       + 调用本方法暂停播放所有音频文件及混音后，会收到 `onAudioMixingStateChanged` 回调，通知已暂停播放和混音。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region Mix
 * @brief Pause all audio files and mixes.
 * @note  
 *       + After calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play audio files and mixes, you can call this api to pause all the files. <br>
 *       + After calling this api to pause all audio and mixes, you can call resumeAllAudioMixing{@link #ByteRTCAudioMixingManager#resumeAllAudioMixing} to resume the playing and mixing.   <br>
 *       + After calling this api to pause all audio and mixes, you will receive `onAudioMixingStateChanged` callback to inform you that the playing and mixing has been paused.  
 */
-(void)pauseAllAudioMixing __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead");

/**
 * @locale zh
 * @type api
 * @region 混音
 * @brief 恢复播放音频文件及混音。
 * @param mixId  <br>
 *        混音 ID
 * @note  
 *       + 调用 pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} 方法暂停播放音频文件后，可以通过调用本方法恢复播放及混音。  <br>
 *       + 调用本方法恢复播放音频文件后，SDK 会向本地回调通知音频文件正在播放中，见 `onAudioMixingStateChanged`。
 */
/**
 * @locale en
 * @type api
 * @region  mixing
 * @brief Resumes playing audio files.
 * @param mixId   <br>
 *         ID of the mixing task
 * @note   
 *        + After calling pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} method, you can resume playing and mixing by calling this method. <br>
 *        + After calling this method to resume playing the audio file, the SDK will notify the local callback that the audio file is playing. See `onAudioMixingStateChanged`.
 */
-(void)resumeAudioMixing:(int)mixId __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead");
/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region 混音
 * @brief 恢复播放所有音频文件及混音。
 * @note  
 *       + 调用 pauseAllAudioMixing{@link #ByteRTCAudioMixingManager#pauseAllAudioMixing} 方法暂停所有正在播放音频文件及混音后，可以通过调用本方法恢复播放及混音。  <br>
 *       + 调用本方法恢复播放所有音频文件及混音后，会收到 `onAudioMixingStateChanged` 回调，通知已恢复播放和混音。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region Mix
 * @brief Resume playing all audio files and mixes.
 * @note  
 *       + After calling pauseAllAudioMixing{@link #ByteRTCAudioMixingManager#pauseAllAudioMixing}, you can call this api to resume playing all the files. <br>
 *       + After calling this api to resume all audio and mixes, you will receive `onAudioMixingStateChanged` callback to inform you that the playing and mixing has been resumed.
 */
-(void)resumeAllAudioMixing __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead");

/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region 混音
 * @brief 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。
 * @param mixId 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br>
 *        如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br>
 *        如果先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}，再使用相同的 ID 调用本方法 ，会先回调 `onAudioMixingStateChanged` 通知上一个混音停止，然后加载后一个混音。  <br>
 *        调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 播放 B.mp3，请先调用 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载 A.mp3。
 * @param filePath 混音文件路径。仅支持本地文件的绝对路径。预加载的文件长度不得超过 20s。<br>
 *        不同平台支持的音频文件格式：<br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @note  
 *       + 本方法只是预加载指定音频文件，只有调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法才开始播放指定音频文件。 <br>
 *       + 调用本方法预加载音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  <br>
 *       + 调用本方法预加载的指定音频文件可以通过 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region Audio Mixing
 * @brief Preload the audio file into memory to minimize the loading cost of playing repeatedly.
 * @param mixId Mix ID. Used to identify the mixing task. <br>
 *        If this method is repeatedly called with the same ID, the previous file will be unloaded and the new file will be loaded. <br>
 *         If you call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} and then call this method with the same ID, the previous mixing task will be stopped, and then the next file will be loaded. <br>
 *         After calling this method to preload A.mp3, if you need to call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play B.mp3 with the same ID, call unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} to unload A.mp3 first.
 * @param filePath The absolute path of the local file to preload. You can only preload the audio file of length less than 20s.<br>
 *         Audio file formats supported by different platforms: <br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @note   
 *        + After preload, call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play the audio file. <br>
 *        + After calling this method, you will receive `onAudioMixingStateChanged` about the current mixing status. <br>
 *        + Unload the preloaded file with unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:}.
 */
- (void)preloadAudioMixing:(int)mixId filePath:(NSString *_Nullable)filePath __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead");


/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region 混音
 * @brief 卸载指定音乐文件。
 * @param mixId  <br>
 *        混音 ID
 * @note 不论音频文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 `onAudioMixingStateChanged`。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region Audio Mixing
 * @brief Uninstalls the specified music file.
 * @param mixId   <br>
 *        Mix ID
 * @note Whether the audio file is playing or not, after calling this method to uninstall the file, the SDK will call back to notify that the mix has stopped. See `onAudioMixingStateChanged`.
 */
-(void)unloadAudioMixing:(int)mixId  __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead");

/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region 混音
 * @brief 设置默认的混音音量大小，包括音频文件混音和 PCM 混音。
 * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量（默认值）  <br>
 *        + 400: 最大可调音量 (自带溢出保护)
 * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @note 该接口的优先级低于 setAudioMixingVolume:volume:type:{@link #ByteRTCAudioMixingManager#setAudioMixingVolume:volume:type:}，即通过 setAudioMixingVolume:volume:type:{@link #ByteRTCAudioMixingManager#setAudioMixingVolume:volume:type:} 单独设置了音量的混音 ID，不受该接口设置的影响。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCAudioEffectPlayer instead
 * @region Audio Mixing
 * @brief Sets the default volume during audio mixing, which works for both audio file mixing and PCM mixing.
 * @param volume The ratio of the mixing volume to the original volume. The range is `[0, 400]`. The recommended range is `[0, 100]`. <br>
 *         + 0: Mute <br>
 *         + 100: Original volume <br>
 *         + 400: Maximum volume (with overflow protection)
 * @param type See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}.
 * @note This API does not work for the mixing ID for which the volume has been set specifically by setAudioMixingVolume:volume:type:{@link #ByteRTCAudioMixingManager#setAudioMixingVolume:volume:type:}.
 */
- (void)setAllAudioMixingVolume:(int)volume type:(ByteRTCAudioMixingType)type __deprecated_msg("deprecated since 353.1, will be deleted in 359, use  ByteRTCAudioEffectPlayer instead");

/**
 * @locale zh
 * @type api
 * @region 混音
 * @brief 调节指定混音的音量大小，包括音频文件混音和 PCM 混音。
 * @param mixId 需调节音量的混音 ID
 * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量（默认值）  <br>
 *        + 400: 最大可调音量 (自带溢出保护)
 * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @note 该方法仅对指定混音 ID 生效。iOS 端提供 setAllAudioMixingVolume:type:{@link #ByteRTCAudioMixingManager#setAllAudioMixingVolume:type:} 接口调节全部混音文件播放音量。
 */
/**
 * @locale en
 * @type api
 * @region Audio Mixing
 * @brief Adjust the volume of audio mixing, including audio files and PCM data.
 * @param mixId ID of the mixing task
 * @param volume The ratio of the mixing volume to the original volume. The range is `[0, 400]`. The recommended range is `[0, 100]`. <br>
 *         + 0: Mute <br>
 *         + 100: Original volume <br>
 *         + 400: Maximum volume (with overflow protection)
 * @param type See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}.
 * @note This API works only for the specified mix ID. Call setAllAudioMixingVolume:type:{@link #ByteRTCAudioMixingManager#setAllAudioMixingVolume:type:} if you want to set the default volume for all the audio mixing tasks, which is for iOS apps only.
 */
- (void)setAudioMixingVolume:(int)mixId
                      volume:(int)volume
                        type:(ByteRTCAudioMixingType)type
    __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead");

/**
 * @locale zh
 * @type api
 * @region 混音
 * @brief 获取音频文件时长。
 * @param mixId  <br>
 *        混音 ID
 * @return  
 *       + >0: 成功, 音频文件时长，单位为毫秒。  <br>
 *       + < 0: 失败
 * @note 调用本方法获取音频文件时长前，需要先调用 preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} 或 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}。
 */
/**
 * @locale en
 * @type api
 * @region  mix
 * @brief Gets audio file duration.
 * @param mixId   <br>
 *         Mix ID
 * @return   
 *        + > 0: Success, audio file duration, in milliseconds. <br>
 *        + < 0: Failed
 * @note  Before calling this method to get the audio file duration, you need to call preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} or startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}.
 */
-(int)getAudioMixingDuration:(int)mixId __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead");


/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 获取音频文件播放进度。
 * @param mixId  <br>
 *        混音 ID
 * @return  
 *        + >0: 成功, 音频文件播放进度，单位为毫秒。  <br>
 *        + < 0: 失败
 * @note 调用本方法获取音频文件播放进度前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region  mix
 * @brief Gets audio file playback progress.
 * @param mixId   <br>
 *         Mix ID
 * @return   
 *         + > 0: Success, audio file playback progress, in milliseconds. <br>
 *         + < 0: Failed
 * @note Before calling this method to get the audio file playback progress, you need to call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} first to start playing the audio file.
 */
-(int)getAudioMixingCurrentPosition:(int)mixId __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

/**
 * @locale zh
 * @type api
 * @region 混音
 * @brief 设置音频文件的起始播放位置
 * @param mixId 混音 ID
 * @param position 音频文件起始播放位置，单位为毫秒。  <br>
 *        你可以通过 getAudioMixingDuration:{@link #ByteRTCAudioMixingManager#getAudioMixingDuration:} 获取音频文件总时长，position 的值不得大于音频文件总时长。
 * @note 在播放在线文件时，调用此接口可能造成播放延迟的现象。
 */
/**
 * @locale en
 * @type api
 * @region Audio Mixing
 * @brief Set the starting playback position of the audio file
 * @param mixId ID of the mixing task
 * @param position The starting playback position of the audio file in milliseconds.  <br>
 *        You can get the total duration of the audio file with getAudioMixingDuration:{@link #ByteRTCAudioMixingManager#getAudioMixingDuration:}, the value of position set using this method must not be greater than the total duration of the audio file.
 * @note When mixing online files, calling this API may cause mixing delay.
 */
- (void)setAudioMixingPosition:(int)mixId
                      position:(int)position __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead");


/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 设置当前音频文件的声道模式
 * @param mixId 混音 ID
 * @param mode 声道模式。默认的声道模式和源文件一致，详见 ByteRTCAudioMixingDualMonoMode{@link #ByteRTCAudioMixingDualMonoMode}。
 * @note 
 *        + 调用本方法设置音频文件的声道模式前，需要先调用 startAudioMixing:filePath:config:{@link #startAudioMixing:filePath:config:} 开始播放音频文件。<br>
 *        + 此方法对 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 播放的音乐无效。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region  mix
 * @brief  Set the channel mode of the current audio file
 * @param mixId  Mix ID
 * @param mode  Channel mode. The default channel mode is the same as the source file. See ByteRTCAudioMixingDualMonoMode{@link #ByteRTCAudioMixingDualMonoMode}.
 * @note  
 *         + Before calling this method to set the channel mode of the audio file, you need to call startAudioMixing:filePath:config:{@link #startAudioMixing:filePath:config:} to start playing the audio file. <br>
 *         + This method is invalid for music played by enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:}.
 */
- (void)setAudioMixingDualMonoMode:(int)mixId
                              mode:(ByteRTCAudioMixingDualMonoMode)mode
        __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

/**
 * @locale zh
 * @type api
 * @region 混音
 * @brief 开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br>
 *        使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。
 * @param mixId 混音 ID
 * @param pitch 相对于音乐文件原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
 *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
 *        超出取值范围则设置失败，并且会触发 `onAudioMixingStateChanged` 回调，提示 ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} 状态为 `AUDIO_MIXING_STATE_FAILED` 混音播放失败，ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} 错误码为 `AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH` 设置混音文件音调不合法。
 * @note 本方法需要在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件后、调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错
 */
/**
 * @locale en
 * @type api
 * @region Audio Mixing
 * @brief Enables local playback of music files in a different key, mostly used in Karaoke scenarios.  <br>
 *        You can adjust the pitch of locally played music files such as ascending or descending with this method.
 * @param mixId ID of the mixing task
 * @param pitch The value that is higher or lower than the original pitch of the audio file within a range from -12 to 12. The default value is 0, i.e. No adjustment is made.  <br>
 *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
 *        Out of the value range, the setting fails and triggers the `onAudioMixingStateChanged` callback, indicating `AUDIO_MIXING_STATE_FAILED` for playback failure with ByteRTCAudioMixingState{@link # ByteRTCAudioMixingState}, and `AUDIO_MIXING_ERROR_ID_TYPE_ INVALID_PITCH` for invalid value setting with ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError}.
 * @note This method needs to be used after calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the audio file and before calling stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} to stop playing the audio file, otherwise the `onAudioMixingStateChanged` callback will be triggered.
 */
-(void)setAudioMixingPitch:(int)mixId pitch:(int)pitch __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer or ByteRTCAudioEffectPlayer instead");

/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 设置混音时音频文件的播放速度
 * @param mixId 混音 ID
 * @param speed 播放速度与原始文件速度的比例，单位：%，取值范围为 [50,200]，默认值为 100。  <br>
 *        超出取值范围则设置失败，你会收到 `onAudioMixingStateChanged` 回调，提示 ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} 状态为 `ByteRTCAudioMixingStateFailed` 混音播放失败，ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} 错误码为 `ByteRTCAudioMixingErrorInValidPlaybackSpeed` 设置混音文件的播放速度不合法。
 * @note   
 *        + 暂不支持对 PCM 音频数据进行变速调整。  <br>
 *        + 你需要在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始混音，并且收到`onAudioMixingStateChanged` 回调提示 ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} 状态为 `ByteRTCAudioMixingStatePlaying`，ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} 错误码为 `AUDIO_MIXING_ERROR_OK` 之后调用该方法。  <br>
 *        + 在 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 停止混音或 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载音频文件后调用该 API，会收到状态为 `ByteRTCAudioMixingStateFailed` 错误码为 `ByteRTCAudioMixingErrorIdNotFound` 的 `onAudioMixingStateChanged` 回调。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region Audio Mixing
 * @brief Sets the playback speed of the current audio file.
 * @param mixId Audio mixing task ID
 * @param speed Ratio of playback speed to original speed in percentage. The range is [50,200], the default value is 100.  <br>
 *        If the value you set is out of range, the setting fails, and you will receive an `onAudioMixingStateChanged` callback, in which the ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} is `ByteRTCAudioMixingStateFailed` and the ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} is `ByteRTCAudioMixingErrorInValidPlaybackSpeed`.
 * @note   
 *        + This API can not be used on setting playback speed for PCM audio data.  <br>
 *        + You should call this API after calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} and receiving an `onAudioMixingStateChanged` callback indicating that the ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} is `ByteRTCAudioMixingStatePlaying` and the ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} is `AUDIO_MIXING_ERROR_OK`.  <br>
 *        + If you call this API after calling stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} or unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:}, you will receive an `onAudioMixingStateChanged` callback indicating that the ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} is `ByteRTCAudioMixingStateFailed` and the ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} is `ByteRTCAudioMixingErrorIdNotFound`.
 */
- (int)setAudioMixingPlaybackSpeed:(int)mixId speed:(int)speed __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 如果你需要使用 `enableVocalInstrumentBalance:` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。
 * @param mixId 混音 ID
 * @param loudness 原始响度，单位：lufs，取值范围为 [-70.0, 0.0]。  <br>
 *        当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音均衡处理。默认值为 1.0lufs，即不做处理。
 * @note 建议在 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件之前调用该接口，以免播放过程中的音量突变导致听感体验下降。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region Audio Mixing
 * @brief If you need to call `enableVocalInstrumentBalance` to adjust the volume of the audio file or PCM data used for audio mixing, you must import the original loudness value of the audio file or PCM data via this API.
 * @param mixId ID of the mixing task
 * @param loudness Original loudness of the audio file in lufs. The range is [-70.0, 0.0].  <br>
 *        If the value is set to be less than -70.0lufs, it is automatically adjusted to -70.0lufs. If the value is set to be greater than 0.0lufs, SDK will not equalize the loudness. The default value is 1.0lufs, i.e. No loudness equalization effect.
 * @note To avoid sudden volume changes during audio file playback, we recommend that you call this API before starting to play the audio file with startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}.
 */
-(void)setAudioMixingLoudness:(int)mixId loudness:(float)loudness __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 设置混音时音频文件播放进度回调的间隔
 * @param mixId 混音 ID  <br>
 *        可以通过多次调用本接口传入不同的 ID 对多个 ID 进行间隔设置。
 * @param interval 音频文件播放进度回调的时间间隔，单位毫秒。  <br>
 *       + interval 的值为大于 0 的 10 的倍数，当设置的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。设置完成后 SDK 将会按照设置的时间间隔触发 `onAudioMixingPlayingProgress` 回调。  <br>
 *       + interval 的值小于等于 0 时，不会触发进度回调。  
 * @note 本方法需要在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件后、调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错。  <br>
 *        若想在音乐文件开始播放前设置播放进度回调间隔，你需调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 在 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} 中设置时间间隔，开始播放后可以通过此接口更新回调间隔。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region Audio Mixing
 * @brief Set the interval of audio file playback progress callbacks during audio mixing
 * @param mixId ID of the mixing task  <br>
 *        You can set the interval for multiple IDs by calling this method multiple times and passing in different IDs.
 * @param interval The time interval (ms) of the audio file playback progress callback in milliseconds.  <br>
 *       + The value of interval is a multiple of 10 greater than 0. When the value set is not divisible by 10, the default is rounded up by 10. For example, if the value is set to 52ms, it will be automatically adjusted to 60ms, then the SDK will trigger `onAudioMixingPlayingProgress` callback at the set interval.  <br>
 *       + If the value is less than or equals to 0, the callback will not be triggered.  
 * @note This method needs to be used after calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the audio file, and before calling stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} to stop playing the audio file, otherwise an error callback `onAudioMixingStateChanged` will be triggered.  <br>
 *        If you want to set the interval of playback progress callbacks before the music file starts playing, you need to call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to set the interval in ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig}, and you can update the callback interval through this method after the audio file starts playing.
 */
-(void) setAudioMixingProgressInterval:(int)mixId interval:(int64_t) interval __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

 /**
  * @locale zh
  * @type api
  * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
  * @region 混音
  * @brief 启动 PCM 音频数据混音。<br>
  *        要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 id。
  * @param mixId 混音 ID。用于标识混音，保证混音 ID 唯一性。  <br>
  *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，会收到 `onAudioMixingStateChanged` 通知前一次混音已停止。
  * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
  * @note  
  *       + 必须先调用本方法启动 PCM 音频数据混音，随后调用 pushAudioMixingFrame:audioFrame:{@link #pushAudioMixingFrame:audioFrame:} 方法，才会开始混音。 <br>
  *       + 如要结束 PCM 音频数据混音，使用 disableAudioMixingFrame:{@link #disableAudioMixingFrame:}。
  */
 /**
  * @locale en
  * @type api
  * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
  * @region Audio Mixing
  * @brief Starts PCM mixing. <br>
  *        To mix multiple PCM audio data, call this API multiple times with different ids.
  * @param mixId ID of the mixing task. Used to identify the mixing. Ensure it is unique. <br>
  *        If this API is called repeatedly with the same ID, the previous mixing will stop, and the next mixing will start, and you will receive `onAudioMixingStateChanged` notification that the previous mixing has stopped.
  * @param type Mixing type <br>
  *        Whether the PCM data is mixed locally and sent to the remotes. See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}.
  * @note   
  *        + After this API, you must call pushAudioMixingFrame:audioFrame:{@link #pushAudioMixingFrame:audioFrame:} to start mixing. <br>
  *        + To end PCM mixing, use disableAudioMixingFrame:{@link #disableAudioMixingFrame:}.
  */
-(void)enableAudioMixingFrame:(int)mixId type:(ByteRTCAudioMixingType)type __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 关闭 PCM 混音
 * @param mixId 混音 ID。
 */
/**
 * @locale en
 * @type api
 * @region Audio Mixing
 * @brief End PCM mixing.
 * @param mixId ID of the mixing task.
 */
-(void)disableAudioMixingFrame:(int)mixId __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 推送 PCM 音频帧数据用于混音
 * @param mixId 混音 ID。
 * @param audioFrame 音频帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @return  
 *       + 0: 成功  <br>
 *       + < 0: 失败
 * @note
 *      + 调用该方法前，须通过 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 启动外部音频流混音。  <br>
 *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。要暂停播放，暂停推送即可。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region Audio Mixing
 * @brief Push PCM audio frame data for mixing
 * @param mixId ID of the mixing task.
 * @param audioFrame See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @return   
 *        + 0: Success <br>
 *        + < 0: Failure
 * @note
 *       + Before calling this method, you must start the external audio stream mixing through enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:}. <br>
 *       + Use reference suggestions: For the first time to push data, please cache certain data (such as 200 milliseconds) on the application side, and then push it all at once; after that, the push operation is timed once in 10 milliseconds, and the amount of audio data each time is 10 milliseconds. To pause PCM mixing, pause pushing PCM data.
 */
- (int)pushAudioMixingFrame:(int)mixId
                 audioFrame:(ByteRTCAudioFrame *_Nullable)audioFrame __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");
/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 获取当前音频文件的音轨索引。
 * @param mixId 混音 ID
 * @return 方法调用结果 <br>
 *        + ≥ 0：成功，返回当前音频文件的音轨索引。  <br>
 *        + < 0：方法调用失败。
 * @note  
 *       + 调用本方法获取音频文件的音轨前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件。<br>
 *       + 此方法对 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 播放的音频无效。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region Audio Mixing
 * @brief Gets the track index of the current audio file.
 * @param mixId Mixding ID
 * @return  
 *        + >=0: Succeeded, the SDK will return the track index of the current audio file.  <br>
 *        + < 0: Failed.
 * @note  
 *       + Before using this method, you should call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the audio file. <br>
 *       + This method is invalid for music played using enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:}.
 */
-(int)getAudioTrackCount:(int)mixId __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");
/**
 * @locale zh
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region 混音
 * @brief 指定当前音频文件的播放音轨。
 * @param mixId 混音 ID
 * @param audioTrackIndex 指定的播放音轨。  <br>
 *        设置的参数值需要小于或等于 getAudioTrackCount:{@link #ByteRTCAudioMixingManager#getAudioTrackCount:} 的返回值
 * @note  
 *       + 调用本方法设置音频文件的音轨前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件。<br>
 *       + 此方法对 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 播放的音乐无效。
 */
/**
 * @locale en
 * @type api
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @region Audio Mixing
 * @brief Specify the playback track of the current audio file.
 * @param mixId ID of the mixing task.
 * @param audioTrackIndex The specified playback track.  <br>
 *        The set parameter value needs to be less than or equal to the return value of getAudioTrackCount:{@link #ByteRTCAudioMixingManager#getAudioTrackCount:}.
 * @note  
 *       + Before using this method, you should call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the audio file. <br>
 *       + This method is invalid for music played using enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:}.
 */
-(void)selectAudioTrack:(int)mixId audioTrackIndex:(int)audioTrackIndex __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");
/**
 * @locale zh
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @type api
 * @brief 注册本地音频文件混音的音频帧观察者。<br>
 *        当本地音频文件混音时，会收到相关回调。
 * @param observer 参看 ByteRTCAudioFileFrameObserver{@link #ByteRTCAudioFileFrameObserver}。
 */
/**
 * @locale en
 * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
 * @type api
 * @brief Register the observer for the audio frames during local audio file mixing.
 * @param observer See ByteRTCAudioFileFrameObserver{@link #ByteRTCAudioFileFrameObserver}。
 */
- (void)registerAudioFileFrameObserver:(_Nullable id<ByteRTCAudioFileFrameObserver>) observer __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");

/**
  * @locale zh
  * @hidden(macOS)
  * @type api
  * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
  * @region 混音
  * @brief 获取混音音频文件的实际播放时长（单位：毫秒）。
  * @param mixId 混音ID。
  * @return  
  *        + >0: 实际播放时长。 <br>
  *        + < 0: 失败。
  * @note 
  *        + 实际播放时长指的是歌曲不受停止、跳转、倍速、卡顿影响的播放时长。例如，若歌曲正常播放到 1:30 时停止播放 30s 或跳转进度到 2:00, 随后继续正常播放 2分钟，则实际播放时长为 3分30秒。  <br>
  *        + 调用本接口前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放指定音频文件。
  */
 /**
  * @locale en
  * @hidden(macOS)
  * @type api
  * @deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead
  * @region audio mixing
  * @brief Get the actual time played of the audio file.
  * @param mixId The audio mixing ID.
  * @return   
  *         + > 0: The actual time played(in millisecond). <br>
  *         + < 0: Failure.
  * @note  
  *        + The actual time played excludes the time when the file is paused, sped up, rewound, and fast-forwarded. For example, if a song plays 1:30 minutes and plays another 2 minutes after being paused for 30 seconds or fast-forwarded to 2:00,the actual time played will be 3.5 minutes.<br>
  *        + Before calling this API, you must call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play the audio file.
  */
-(int)getAudioMixingPlaybackDuration:(int)mixId __deprecated_msg("deprecated since 353.1, will be deleted in 359, use ByteRTCMediaPlayer instead");
@end
