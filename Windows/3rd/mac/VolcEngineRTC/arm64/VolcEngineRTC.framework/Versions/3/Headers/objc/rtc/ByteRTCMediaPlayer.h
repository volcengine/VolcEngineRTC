/*
 * Copyright (c) 2023 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCMediaPlayer
*/

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"
/**
 * @locale zh
 * @type callback
 * @brief 本地音频文件混音的音频帧观察者。
 */
/**
 * @locale en
 * @type callback
 * @brief observer for the audio frames during local audio file mixing.
 */
@protocol ByteRTCMediaPlayerAudioFrameObserver <NSObject>
/**
 * @locale zh
 * @type callback
 * @brief 当本地音频文件混音时，回调播放的音频帧。
 * @param playerId
 * @param audioFrame 参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 */
/**
 * @locale en
 * @type callback
 * @brief The callback for the audio frames during local audio file mixing.
 * @param playerId
 * @param audioFrame See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 */
- (void)onFrame:(int)playerId audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;

@end
/**
 * @locale zh
 * @type callback
 * @brief ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer} 对应的回调句柄。你必须调用 setEventHandler:{@link #ByteRTCMediaPlayer#setEventHandler:} 完成设置后，才能收到对应回调。
 */
/**
 * @locale en
 * @type callback
 * @brief Event handler for ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer}. You must call setEventHandler:{@link #ByteRTCMediaPlayer#setEventHandler:} to set the corresponding event handler to get the events.
 */
@protocol ByteRTCMediaPlayerEventHandler <NSObject>
/**
* @locale zh
* @type callback
* @brief 播放状态改变时回调。
* @param playerId ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer} 的 ID。通过 getMediaPlayer:{@link #ByteRTCVideo#getMediaPlayer:} 设置。
* @param state 混音状态。参考 ByteRTCPlayerState{@link #ByteRTCPlayerState}。
* @param error 错误码。参考 ByteRTCPlayerError{@link #ByteRTCPlayerError}。
*/
/**
* @locale en
* @type callback
* @brief Callback for audio mixing status change.
* @param playerId The ID of ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer}. Set by getMediaPlayer:{@link #ByteRTCVideo#getMediaPlayer:}.
* @param state See ByteRTCPlayerState{@link #ByteRTCPlayerState}.
* @param error See ByteRTCPlayerError{@link #ByteRTCPlayerError}.
*/
-(void)onMediaPlayerStateChanged:(int)playerId state:(ByteRTCPlayerState)state error:(ByteRTCPlayerError)error;
/**
* @locale zh
* @type callback
* @brief 播放进度周期性回调。回调周期通过 setProgressInterval:{@link #ByteRTCMediaPlayer#setProgressInterval:} 设置。
* @param playerId ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer} 的 ID。通过 getMediaPlayer:{@link #ByteRTCVideo#getMediaPlayer:} 设置。
* @param progress 进度。单位 ms。
*/
/**
* @locale en
* @type callback
* @brief Periodic callback for audio mixing progress. The period is set by setProgressInterval:{@link #ByteRTCMediaPlayer#setProgressInterval:}.
* @param playerId The ID of ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer}. Set by getMediaPlayer:{@link #ByteRTCVideo#getMediaPlayer:}.
* @param progress Mixing progress in ms.
*/
-(void)onMediaPlayerPlayingProgress:(int)playerId progress:(int64_t)progress;

@end
/**
 * @locale zh
 * @valid since 3.53
 * @type api
 * @brief 音乐播放器<br>
 *        调用 setEventHandler:{@link #ByteRTCMediaPlayer#setEventHandler:} 设置回调句柄以获取相关回调。
 */
/**
 * @locale en
 * @valid since 3.53
 * @type api
 * @brief Media player<br>
 *        Call setEventHandler:{@link #ByteRTCMediaPlayer#setEventHandler:} to set the callback handler to receive related callbacks.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMediaPlayer :NSObject
/**
 * @locale zh
 * @type api
 * @brief 打开音乐文件。<br>
 *        一个播放器实例仅能够同时打开一个音乐文件。如果需要同时打开多个音乐文件，请创建多个音乐播放器实例。<br>
 *        要播放 PCM 格式的音频数据，参看 openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:}。`openWithCustomSource` 和此 API 互斥。
 * @param filePath 音乐文件路径。<br>
 *        支持在线文件的 URL、本地文件的 URI、或本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。<br>
 *        推荐的采样率：8KHz、16KHz、22.05KHz、44.1KHz、48KHz。<br>
 *        不同平台支持的本地文件格式:<br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS/macOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 *        不同平台支持的在线文件格式:<br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>iOS/macOS</td><td>Y</td><td></td><td>Y</td><td>Y</td><td></td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td></td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @param config 详见 ByteRTCMediaPlayerConfig{@link #ByteRTCMediaPlayerConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @type api
 * @brief Open the audio file. <br>
 *        You can only open one audio file with one player instance at the same time. For multiple audio files at the same time, create multiple player instances.<br>
 *        For audio file in PCM format, see openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:}. `openWithCustomSource` and this API are mutually exclusive.
 * @param filePath Audio file paths.<br>
 *        URL of online file, URI of local file, or full path to local file are supported. For URL of online file, only the https protocol is supported.<br>
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
 * @param config See ByteRTCMediaPlayerConfig{@link #ByteRTCMediaPlayerConfig}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 */
- (int)open:(NSString *_Nullable)filePath config:(ByteRTCMediaPlayerConfig *_Nullable)config;
/**
 * @locale zh
 * @type api
 * @brief 播放音乐。你仅需要在调用 open:config:{@link #ByteRTCMediaPlayer#open:config:}，且未开启自动播放时，调用此方法。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 * + 要播放 PCM 格式的音频数据，参看 openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:}。`openWithCustomSource` 和此 API 互斥。<br>
 * + 调用本方法播放音频文件后，可调用 stop{@link #ByteRTCMediaPlayer#stop} 方法暂停播放。
 */
/**
 * @locale en
 * @type api
 * @brief Start playing the audio. Call this API when you call open:config:{@link #ByteRTCMediaPlayer#open:config:} and set `AutoPlay=False`.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note  
 * + For audio file in PCM format, see openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:}. `openWithCustomSource` and this API are mutually exclusive.<br>
 * + After calling this API, call stop{@link #ByteRTCMediaPlayer#stop} to stop playing the audio file.
 */
- (int)start;
/**
 * @locale zh
 * @type api
 * @brief 启动音频裸数据混音。<br>
 *        要播放音乐文件，参看 open:config:{@link #ByteRTCMediaPlayer#open:config:}。`open` 与此 API 互斥。
 * @param source 数据源，详见 ByteRTCMediaPlayerCustomSource{@link #ByteRTCMediaPlayerCustomSource}
 * @param config 详见 ByteRTCMediaPlayerConfig{@link #ByteRTCMediaPlayerConfig}
 * @note  
 *       + 调用本方法启动后，再调用 pushExternalAudioFrame:{@link #ByteRTCMediaPlayer#pushExternalAudioFrame:} 推送音频数据，才会开始混音。<br>
 *       + 如要结束 PCM 音频数据混音，调用 stop{@link #ByteRTCMediaPlayer#stop}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @type api
 * @brief Enable audio mixing with audio raw data.<br>
 *        To open the audio file, see open:config:{@link #ByteRTCMediaPlayer#open:config:}. `open` and this API are mutually exclusive.
 * @param source See ByteRTCMediaPlayerCustomSource{@link #ByteRTCMediaPlayerCustomSource}.
 * @param config See ByteRTCMediaPlayerConfig{@link #ByteRTCMediaPlayerConfig}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note  
 *       + After calling this API, you must call pushExternalAudioFrame:{@link #ByteRTCMediaPlayer#pushExternalAudioFrame:} to push audio data and start the audio mixing.<br>
 *       + To stop the raw data audio mixing, call stop{@link #ByteRTCMediaPlayer#stop}.
 */
- (int)openWithCustomSource:(ByteRTCMediaPlayerCustomSource *_Nullable)source config:(ByteRTCMediaPlayerConfig *_Nullable)config;
/**
 * @locale zh
 * @type api
 * @brief 调用 open:config:{@link #ByteRTCMediaPlayer#open:config:}, start{@link #ByteRTCMediaPlayer#start}, 或 openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} 开始播放后，可以调用本方法停止。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @type api
 * @brief After calling open:config:{@link #ByteRTCMediaPlayer#open:config:}, start{@link #ByteRTCMediaPlayer#start}, or openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} to start audio mixing, call this method to stop audio mixing.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 */
- (int)stop;
/**
 * @locale zh
 * @type api
 * @brief 调用 open:config:{@link #ByteRTCMediaPlayer#open:config:}，或 start{@link #ByteRTCMediaPlayer#start} 开始播放音频文件后，调用本方法暂停播放。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 * + 调用本方法暂停播放后，可调用 resume{@link #ByteRTCMediaPlayer#resume} 恢复播放。<br>
 * + 此接口仅支持音频文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief After calling open:config:{@link #ByteRTCMediaPlayer#open:config:}, or start{@link #ByteRTCMediaPlayer#start} to start audio mixing, call this API to pause audio mixing.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note  
 * + After calling this API to pause audio mixing, call resume{@link #ByteRTCMediaPlayer#resume} to resume audio mixing.<br>
 * + The API is valid for audio file, not PCM data.
 */
- (int)pause;
/**
 * @locale zh
 * @type api
 * @brief 调用 pause{@link #ByteRTCMediaPlayer#pause} 暂停音频播放后，调用本方法恢复播放。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        此接口仅支持音频文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief After calling pause{@link #ByteRTCMediaPlayer#pause} to pause audio mixing, call this API to resume audio mixing.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *        The API is valid for audio file, not PCM data.
 */
- (int)resume;
/**
 * @locale zh
 * @type api
 * @brief 调节指定混音的音量大小，包括音乐文件混音和 PCM 混音。
 * @param volume 播放音量相对原音量的比值。单位为 %。范围为 `[0, 400]`，建议范围是 `[0, 100]`。带溢出保护。
 * @param type 详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 仅在音频播放进行状态时，调用此方法。
 */
 /**
 * @locale en
 * @type api
 * @brief Adjusts the volume of the specified audio mixing, including media file mixing and PCM mixing.
 * @param volume The ratio of the volume to the original volume in % with overflow protection. The range is `[0, 400]` and the recommended range is `[0, 100]`.
 * @param type See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note Call this API only when audio is mixing.
 */
- (int)setVolume:(int)volume type:(ByteRTCAudioMixingType)type;
/**
 * @locale zh
 * @type api
 * @brief 获取当前音量
 * @param type 详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @return  
 *        + >0: 成功, 当前音量值。  <br>
 *        + < 0: 失败
 * @note 仅在音频播放进行状态时，调用此方法。包括音乐文件混音和 PCM 混音。
 */
/**
 * @locale en
 * @type api
 * @brief Gets the current volume.
 * @param type See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}.
 * @return  
 *        + >0: Success, the current volume. <br>
 *        + < 0: Failed.
 * @note Call this API only when audio is mixing, including media file mixing and PCM mixing.
 */
- (int)getVolume:(ByteRTCAudioMixingType)type;
/**
 * @locale zh
 * @type api
 * @brief 获取音乐文件时长。
 * @return  
 *        + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
 *        + < 0: 失败
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 此接口仅支持音频文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Gets the duration of the media file.
 * @return  
 *        + >0: Success, the duration of the media file in milliseconds.  <br>
 *        + < 0: Failed.
 * @note 
 *        + Call this API only when audio is mixing.<br>
 *        + The API is valid for audio file, not PCM data.
 */
- (int)getTotalDuration;
/**
 * @locale zh
 * @type api
 * @brief 获取混音音乐文件的实际播放时长，单位为毫秒。
 * @return  
 *        + >0: 实际播放时长。<br>
 *        + < 0: 失败。
 * @note 
 *        + 实际播放时长指的是歌曲不受停止、跳转、倍速、卡顿影响的播放时长。例如，若歌曲正常播放到 1:30 时停止播放 30s 或跳转进度到 2:00, 随后继续正常播放 2分钟，则实际播放时长为 3分30秒。<br>
 *        + 仅在音频播放进行状态，且 setProgressInterval:{@link #ByteRTCMediaPlayer#setProgressInterval:} 设置间隔大于 `0` 时，调用此方法。<br>
 *        + 此接口仅支持音频文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Gets the actual playback duration of the mixed media file, in milliseconds.
 * @return  
 *        + >0: Success, the actual playback time.<br>
 *        + < 0: Failed.
 * @note 
 *        + The actual playback time refers to the playback time of the song without being affected by stop, jump, double speed, and freeze. For example, if the song stops playing for 30 seconds at 1:30 or skips to 2:00, and then continues to play normally for 2 minutes, the actual playing time is 3 minutes and 30 seconds.<br>
 *        + Call this API only when audio is mixing and the interval set by setProgressInterval:{@link #ByteRTCMediaPlayer#setProgressInterval:} is above `0`.<br>
 *        + The API is valid for audio file, not PCM data.
 */
- (int)getPlaybackDuration;
/**
 * @locale zh
 * @type api
 * @brief 获取音乐文件播放进度。
 * @return  
 *        + >0: 成功, 音乐文件播放进度，单位为毫秒。<br>
 *        + < 0: 失败
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 此接口仅支持音频文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Gets the playback progress of the media file.
 * @return  
 *        + >0: Success, the playback progress of media file in ms.<br>
 *        + < 0: Failed.
 * @note 
 *        + Call this API only when audio is mixing.<br>
 *        + The API is valid for audio file, not PCM data.
 */
- (int)getPosition;
/**
 * @locale zh
 * @type api
 * @brief 开启变调功能，多用于 K 歌场景。
 * @param pitch 与音乐文件原始音调相比的升高/降低值，取值范围为 `[-12，12]`，默认值为 0。每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 仅支持音乐文件混音，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Set the pitch of the local audio file mixing. Usually used in karaoke scenes.
 * @param pitch The increase or decrease value compared with the original pitch of the music file. The range is `[-12, 12]`. The default value is 0. The pitch distance between two adjacent values is half a step. A positive value indicates a rising pitch, and a negative value indicates a falling pitch.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *        + Call this API only when audio is mixing.<br>
 *        + Support audio file only and not PCM data.
 */
- (int)setAudioPitch:(int)pitch;
/**
 * @locale zh
 * @type api
 * @brief 设置音乐文件的起始播放位置。
 * @param position 音乐文件起始播放位置，单位为毫秒。  <br>
 *        你可以通过 getTotalDuration{@link #ByteRTCMediaPlayer#getTotalDuration} 获取音乐文件总时长，position 的值应小于音乐文件总时长。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 此接口仅支持音频文件，不支持 PCM 数据。<br>
 *        + 在播放在线文件时，调用此接口可能造成播放延迟的现象。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the starting playback position of the media file.
 * @param position The starting position of the media file in milliseconds.<br>
 *        You can get the total duration of the media file through getTotalDuration{@link #ByteRTCMediaPlayer#getTotalDuration}. The value of position should be less than the total duration of the media file.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *        + The API is valid for audio file, not PCM data.<br>
 *        + When playing online files, calling this API may cause playback delay.
 */
- (int)setPosition:(int)position;
/**
 * @locale zh
 * @type api
 * @brief 设置当前音乐文件的声道模式
 * @param mode 声道模式。默认的声道模式和源文件一致，详见 ByteRTCAudioMixingDualMonoMode{@link #ByteRTCAudioMixingDualMonoMode}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 仅支持音频文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the channel mode of the mixing of the media file.
 * @param mode The mode of channel. The default channel mode is the same as the source file. See ByteRTCAudioMixingDualMonoMode{@link #ByteRTCAudioMixingDualMonoMode}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *       + Call this API only when audio is mixing.<br>
 *       + Audio file is supported, but not PCM data.
 */
- (int)setAudioDualMonoMode:(ByteRTCAudioMixingDualMonoMode)mode;
/**
 * @locale zh
 * @type api
 * @brief 获取当前音乐文件的音轨数
 * @return + >= 0：成功，返回当前音乐文件的音轨数<br>
 *         + < 0：方法调用失败
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 此方法仅支持音乐文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Gets the track count of the current media file.
 * @return + >= 0：Success. Return the track count of the current media file.<br>
 *         + < 0：Failed.
 * @note 
 *       + Call this API only when audio is mixing.<br>
 *       + This API is valid for audio file, not PCM data.
 */
- (int)getAudioTrackCount;
/**
 * @locale zh
 * @type api
 * @brief 指定当前音乐文件的播放音轨
 * @param index 指定的播放音轨，从 0 开始，取值范围为 `[0, getAudioTrackCount()-1]`。<br>
 *        设置的参数值需要小于 getAudioTrackCount{@link #ByteRTCMediaPlayer#getAudioTrackCount} 的返回值
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 此方法仅支持音乐文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Specifies the playback track of the current media file.
 * @param index The specified playback audio track, starting from 0, and the range is `[0, getAudioTrackCount()-1]`. The value must be less than the return value of getAudioTrackCount{@link #ByteRTCMediaPlayer#getAudioTrackCount}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *       + Call this API only when audio is mixing.<br>
 *       + This API is valid for audio file, not PCM data.
 */
- (int)selectAudioTrack:(int)index;
/**
 * @locale zh
 * @type api
 * @brief 设置播放速度
 * @param speed 播放速度与原始文件速度的比例，单位：%，取值范围为 `[50,200]`，默认值为 100。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 此方法对音频文件可用，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Set the playback speed of the audio file.
 * @param speed The ratio of the actual playback speed than that of the original speed of the audio file in %. The range is `[50,200]`. The default value is 100.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *       + Call this API only when audio is mixing.<br>
 *       + The API is valid for audio file and not PCM data.
 */
- (int)setPlaybackSpeed:(int)speed;
/**
 * @locale zh
 * @type api
 * @brief 设置音频文件混音时，收到 onMediaPlayerPlayingProgress:progress:{@link #ByteRTCMediaPlayerEventHandler#onMediaPlayerPlayingProgress:progress:} 的间隔。
 * @param interval 时间间隔，单位毫秒。<br>
 *       + interval > 0 时，触发回调。实际间隔为 10 的倍数。如果输入数值不能被 10 整除，将自动向上取整。例如传入 `52`，实际间隔为 60 ms。<br>
 *       + interval <= 0 时，不会触发回调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 此方法仅支持音频文件，不支持 PCM 数据。
 */
 /**
 * @locale en
 * @type api
 * @brief Set the interval of the periodic callback onMediaPlayerPlayingProgress:progress:{@link #ByteRTCMediaPlayerEventHandler#onMediaPlayerPlayingProgress:progress:} during audio mixing.
 * @param interval interval in ms.<br>
 *       + interval > 0: The callback is enabled. The actual interval is `10*(mod(10)+1)`.<br>
 *       + interval <= 0: The callback is disabled.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *       + Call this API only when audio is mixing.<br>
 *       + This API is valid for audio file, not PCM data.
 */
- (int)setProgressInterval:(int64_t)interval;
/**
 * @locale zh
 * @type api
 * @brief 如果你需要使用 enableVocalInstrumentBalance:{@link #ByteRTCVideo#enableVocalInstrumentBalance:} 对音频文件/PCM 音频数据设置音量均衡，你必须通过此接口传入其原始响度。
 * @param loudness 原始响度，单位：lufs，取值范围为 `[-70.0, 0.0]`。<br>
 *        当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音量均衡处理。默认值为 1.0lufs，即不做处理。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 仅在音频播放进行状态时，调用此方法。<br>
 *        + 此方法对音频文件和音频裸数据播放都可用。
 */
/**
 * @locale en
 * @type api
 * @brief To call enableVocalInstrumentBalance:{@link #ByteRTCVideo#enableVocalInstrumentBalance:} to adjust the volume of the mixed media file or the PCM audio data, you must pass in its original loudness through this API.
 * @param loudness Original loudness in lufs. The range is `[-70.0, 0.0]`.<br>
 *       When the value is less than -70.0lufs, it will be adjusted to -70.0lufs by default, and if it is more than 0.0lufs, the loudness will not be equalized. The default value is 1.0lufs, which means no processing.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *       + Call this API only when audio is mixing.<br>
 *       + The API is valid for audio file and PCM data.
 */
- (int)setLoudness:(float)loudness;
/**
 * @locale zh
 * @type api
 * @brief 注册回调句柄以在本地音乐文件混音时，收到相关回调。
 * @param observer 参看 ByteRTCMediaPlayerAudioFrameObserver{@link #ByteRTCMediaPlayerAudioFrameObserver}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        此接口仅支持音频文件，不支持 PCM 数据。
 */
/**
 * @locale en
 * @type api
 * @brief Register an observer to receive related callbacks when the local media file is mixing.
 * @param observer See ByteRTCMediaPlayerAudioFrameObserver{@link #ByteRTCMediaPlayerAudioFrameObserver}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *        The API is valid for audio file, not PCM data.
 */
- (int)registerAudioFrameObserver:(_Nullable id<ByteRTCMediaPlayerAudioFrameObserver>)observer;
/**
 * @locale zh
 * @type api
 * @brief 推送用于混音的 PCM 音频帧数据
 * @param audioFrame 音频帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。<br>
 *        + 音频采样格式必须为 S16。音频缓冲区内的数据格式必须为 PCM，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。<br>
 *        + 必须指定具体的采样率和声道数，不支持设置为自动。
 * @return  
 *       + 0: 成功  <br>
 *       + < 0: 失败
 * @note
 *      + 调用该方法前，须通过 openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} 启动外部音频流混音。<br>
 *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。<br>
 *      + 如果要暂停播放，暂停推送即可。
 */
/**
 * @locale en
 * @type api
 * @brief Push PCM audio frame data for mixing.
 * @param audioFrame See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @return  
 *       + 0: Success.  <br>
 *       + < 0: Failed.
 * @note
 *      + Before calling this method, the raw audio data mixing must be enabled through openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:}.<br>
 *      + Suggestions: Before pushing data for the first time, please cache a certain amount of data (like 200 ms) on the application side, and then push it at once. Schedule subsequent push operation every 10 ms with audio data of 10 ms.<br>
 *      + To pause the playback, just pause the push.
 */
- (int)pushExternalAudioFrame:(ByteRTCAudioFrame *_Nullable)audioFrame;
/**
 * @locale zh
 * @type api
 * @brief 设置回调句柄。
 * @param handler 参看 ByteRTCMediaPlayerEventHandler{@link #ByteRTCMediaPlayerEventHandler}。
 * @return  
 *        + 0: 成功。  <br>
 *        + < 0: 失败。
 */
/**
 * @locale en
 * @type api
 * @brief Set the event handler.
 * @param handler See ByteRTCMediaPlayerEventHandler{@link #ByteRTCMediaPlayerEventHandler}.
 * @return  
 *        + 0: Success.  <br>
 *        + < 0: Failed.
 */
- (int)setEventHandler:(_Nullable id<ByteRTCMediaPlayerEventHandler>)handler;
@end
