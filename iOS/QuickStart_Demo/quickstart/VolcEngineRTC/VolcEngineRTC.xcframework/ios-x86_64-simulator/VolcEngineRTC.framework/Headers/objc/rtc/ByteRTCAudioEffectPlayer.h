/*
 * Copyright (c) 2023 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCAudioEffectPlayer
*/

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"

@protocol ByteRTCAudioEffectPlayerEventHandler <NSObject>
/** 
 * @type callback
 * @brief 音效播放器播放状态改变时回调
 * @param effectId  <br>
 *        音效ID  <br>
 *        使用ByteRTCAudioEffectPlayer相关API时传入的对应ID
 * @param state  <br>
 *        混音状态  <br>
 *        其混音状态可参考：ByteRTCPlayerState{@link #ByteRTCPlayerState}。
 * @param error  <br>
 *        错误码  <br>
 *        详见 ByteRTCPlayerError{@link #ByteRTCPlayerError}。
 */
-(void)onAudioEffectPlayerStateChanged:(int)effectId state:(ByteRTCPlayerState)state error:(ByteRTCPlayerError)error;

@end
/** 
 * @type api
 * @region 音效播放器
 * @notes 使用混音功能时，你必须通过 [setActive:withOptions:error:](https://developer.apple.com/documentation/avfaudio/avaudiosession/1616627-setactive?language=objc) 激活应用的 audio session。直到彻底退出混音功能后，才可以关闭 audio session。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioEffectPlayer :NSObject
/** 
 * @type api
 * @region 音效播放器
 * @brief 开始播放音频文件。<br>
 *        可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。
 * @param effectId 音效 ID。用于标识混音，请保证音效 ID 唯一性。  <br>
 *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，SDK 会使用 `onAudioEffectPlayerStateChanged` 回调通知前一次混音已停止。
 * @param filePath 用于混音文件路径。
 *        支持在线文件的 URL、本地文件的 URI、本地文件的绝对路径或以 `/assets/` 开头的本地文件路径。对于在线文件的 URL，仅支持 https 协议。
 *        推荐的音频文件采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。
 *        不同平台支持的本地音频文件格式:
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *           <tr><td>Linux</td><td></td><td></td><td></td><td></td><td></td><td>Y</td><td></td><td></td><td></td></tr>
 *        </table>
 *        不同平台支持的在线音频文件格式:
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @param config 混音配置  <br>
 *        可以设置混音的播放次数、起始播放位置、音调值、是否本地播放混音、以及是否将混音发送至远端，详见 ByteRTCAudioEffectPlayerConfig{@link #ByteRTCAudioEffectPlayerConfig}
 * @notes  <br>
 *       + 如果已经通过 preload{@link #IAudioEffectPlayer#preload} 将文件加载至内存，确保此处的 ID 与 preload{@link #IAudioEffectPlayer#preload} 设置的 ID 相同。  <br>
 *       + 调用本方法播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到回调 `onAudioEffectPlayerStateChanged`。  <br>
 *       + 开始播放音频文件后，可以调用 stop{@link #IAudioEffectPlayer#stop} 方法停止播放音频文件。  <br>
 */
-(int)start:(int)effectId filePath:(NSString * _Nullable)filePath config:(ByteRTCAudioEffectPlayerConfig * _Nullable)config;
/** 
 * @type api
 * @region 音效播放器
 * @brief 停止播放音频文件及混音。
 * @param effectId 音效 ID
 * @notes  <br>
 *       + 调用 start{@link #IAudioEffectPlayer#start} 方法开始播放音频文件后，可以调用本方法停止播放音频文件。  <br>
 *       + 调用本方法停止播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到回调 `onAudioEffectPlayerStateChanged`。  <br>
 *       + 调用本方法停止播放音频文件后，该音频文件会被自动卸载。
 */
-(int)stop:(int)effectId;
/** 
 * @type api
 * @region 音效播放器
 * @brief 停止播放所有音频文件及混音。
 * @notes  <br>
 *       + 调用 start{@link #IAudioEffectPlayer#start} 方法开始播放音频文件及混音后，可以调用本方法停止播放所有音频文件及混音。  <br>
 *       + 调用本方法停止播放所有音频文件及混音后，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到 `onAusdioMixingStateChanged` 回调，通知已停止播放和混音。  <br>
 *       + 调用本方法停止播放所有音频文件及混音后，该音频文件会被自动卸载。
 */
-(int)stopAll;
/** 
 * @type api
 * @region 音效播放器
 * @brief 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。
 * @param effectId 音效 ID。用于标识混音，请保证音效 ID 唯一性。  <br>
 *        如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br>
 *        如果先调用 start{@link #IAudioEffectPlayer#start}，再使用相同的 ID 调用本方法 ，会先回调 `onAudioEffectPlayerStateChanged`  上一个混音停止，然后加载后一个混音。  <br>
 *        调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 start{@link #IAudioEffectPlayer#start} 播放 B.mp3，请先调用 unload{@link #IAudioEffectPlayer#unload} 卸载 A.mp3 ，否则会报错 AUDIO_MIXING_ERROR_LOAD_CONFLICT。
 * @param filePath 混音文件路径。<br>
 *        支持在线文件的 URL、本地文件的 URI、本地文件的绝对路径或以 `/assets/` 开头的本地文件路径。对于在线文件的 URL，仅支持 https 协议。预加载的文件长度不得超过 20s。<br>
 *        不同平台支持的音频文件格式: <br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @notes  <br>
 *       + 本方法只是预加载指定音频文件，只有调用 start{@link #IAudioEffectPlayer#start} 方法才开始播放指定音频文件。 <br>
 *       + 调用本方法预加载音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到回调 `onAudioEffectPlayerStateChanged`。  <br>
 *       + 调用本方法预加载的指定音频文件可以通过 unload{@link #IAudioEffectPlayer#unload} 卸载。
 */
-(int)preload:(int)effectId filePath:(NSString * _Nullable)filePath;
/** 
 * @type api
 * @region 音效播放器
 * @brief 卸载指定音乐文件。
 * @param effectId 音效 ID
 * @notes 调用本方法卸载该文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到回调 `onAudioEffectPlayerStateChanged`。
 */
-(int)unload:(int)effectId;
/** 
 * @type api
 * @region 音效播放器
 * @brief 卸载所有音乐文件。
 * @notes 调用本方法卸载该文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到回调 `onAudioEffectPlayerStateChanged`。
 */
-(int)unloadAll;
/** 
 * @type api
 * @region 音效播放器
 * @brief 暂停播放音频文件及混音。
 * @param effectId 音效 ID
 * @notes  <br>
 *       + 调用 start{@link #IAudioEffectPlayer#start} 方法开始播放音频文件后，可以通过调用本方法暂停播放音频文件。  <br>
 *       + 调用本方法暂停播放音频文件后，可调用 resume{@link #IAudioEffectPlayer#resume} 方法恢复播放及混音。  <br>
 *       + 调用本方法暂停播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到回调 `onAudioEffectPlayerStateChanged`。
 */
-(int)pause:(int)effectId;
/** 
 * @type api
 * @region 音效播放器
 * @brief 暂停播放所有音频文件及混音。
 * @notes  <br>
 *       + 调用 start{@link #IAudioEffectPlayer#start} 方法开始播放音频文件及混音后，可以通过调用本方法暂停播放所有音频文件及混音。  <br>
 *       + 调用本方法暂停播放所有音频文件及混音后，可调用 resumeAll{@link #IAudioEffectPlayer#resumeAll} 方法恢复所有播放及混音。  <br>
 *       + 调用本方法暂停播放所有音频文件及混音后，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到 `onAudioEffectPlayerStateChanged` 回调，通知已暂停播放和混音。
 */
-(int)pauseAll;
 /** 
 * @type api
 * @region 音效播放器
 * @brief 恢复播放音频文件及混音。
 * @param effectId 音效 ID
 * @notes  <br>
 *       + 调用 pause{@link #IAudioEffectPlayer#pause} 方法暂停播放音频文件后，可以通过调用本方法恢复播放及混音。  <br>
 *       + 调用本方法恢复播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IAudioEffectPlayer#setEventHandler}，会收到回调 `onAudioEffectPlayerStateChanged`。
 */
-(int)resume:(int)effectId;
/** 
 * @type api
 * @region 音效播放器
 * @brief 恢复播放所有音频文件及混音。
 * @notes  <br>
 *       + 调用 pauseAll{@link #IAudioEffectPlayer#pauseAll} 方法暂停所有正在播放音频文件及混音后，可以通过调用本方法恢复播放及混音。  <br>
 *       + 调用本方法恢复播放所有音频文件及混音后，会收到 `onAudioEffectPlayerStateChanged` 回调，通知已恢复播放和混音。
 */
-(int)resumeAll;
/** 
 * @type api
 * @region 音效播放器
 * @brief 设置音频文件的起始播放位置。
 * @param effectId 音效 ID
 * @param position 音频文件起始播放位置，单位为毫秒。  <br>
 *        你可以通过 getDuration{@link #IAudioEffectPlayer#getDuration} 获取音频文件总时长，position 的值应小于音频文件总时长。
 * @notes 在播放在线文件时，调用此接口可能造成播放延迟的现象。
 */
-(int)setPosition:(int)effectId position:(int)position;
 /** 
 * @type api
 * @region 音效播放器
 * @brief 获取音频文件播放进度。
 * @param effectId  音效 ID
 * @return  <br>
 *        + >0: 成功, 音频文件播放进度，单位为毫秒。  <br>
 *        + < 0: 失败
 * @notes 调用本方法获取音频文件播放进度前，需要先调用 start{@link #IAudioEffectPlayer#start} 开始播放音频文件。
 */
-(int)getPosition:(int)effectId;
/** 
 * @type api
 * @region 音效播放器
 * @brief 调节指定混音的音量大小，包括音频文件混音和 PCM 混音。
 * @param effectId 需调节音量的音效 ID
 * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量（默认值）  <br>
 *        + 400: 最大可调音量 (自带溢出保护)
 * @notes 该方法仅对指定音效 ID 生效，若想调节全部混音文件播放音量，则需调用 setVolumeAll{@link #IAudioEffectPlayer#setVolumeAll}。该方法默认调节start{@link #IAudioEffectPlayer#start}时设置的AudioMixingType{@link #AudioMixingType}类型音量。
 */
-(int)setVolume:(int)effectId volume:(int)volume;
/** 
 * @type api
 * @region 音效播放器
 * @brief 设置默认的混音音量大小，包括音频文件混音和 PCM 混音。
 * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量（默认值）  <br>
 *        + 400: 最大可调音量 (自带溢出保护)
 * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 AudioMixingType{@link #AudioMixingType}。
 * @notes 该接口的优先级低于 setVolume{@link #IAudioEffectPlayer#setVolume}，即通过 setVolume{@link #IAudioEffectPlayer#setVolume} 单独设置了音量的音效 ID，不受该接口设置的影响。
 *        该方法针对所有AudioMixingType{@link #AudioMixingType}类型音量进行调节
 */
-(int)setVolumeAll:(int)volume;
 /** 
 * @type api
 * @region 音效播放器
 * @brief 获取当前音量
 * @param effectId  音效 ID
 * @return  <br>
 *        + >0: 成功, 当前音量值。  <br>
 *        + < 0: 失败
 * @notes 调用本方法获取当前音量前，需要先调用start{@link #IAudioEffectPlayer#start}。
 */
-(int)getVolume:(int)effectId;
/** 
 * @type api
 * @region 音效播放器
 * @brief 获取音频文件时长。
 * @param effectId  音效 ID
 * @return  <br>
 *        + >0: 成功, 音频文件时长，单位为毫秒。  <br>
 *        + < 0: 失败
 * @notes 调用本方法获取音频文件时长前，需要先调用 preload{@link #preload} 或 start{@link #IAudioEffectPlayer#start}。
 */
-(int)getDuration:(int)effectId;
/** 
 * @type api
 * @region 音效播放器
 * @brief 设置事件回调，设置回调以后，可以收到 onAudioEffectPlayerStateChanged 状态回调
 * @param effectId  音效 ID
 * @return  <br>
 *        + 0: 成功。  <br>
 *        + < 0: 失败
 */
-(int)setEventHandler:(_Nullable id<ByteRTCAudioEffectPlayerEventHandler>)handler;
@end
