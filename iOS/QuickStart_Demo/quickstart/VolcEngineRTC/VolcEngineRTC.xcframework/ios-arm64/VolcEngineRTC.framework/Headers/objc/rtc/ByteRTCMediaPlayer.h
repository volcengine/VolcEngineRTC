/*
 * Copyright (c) 2023 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCMediaPlayer
*/

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"

@protocol ByteRTCMediaPlayerAudioFrameObserver <NSObject>
/** 
 * @type callback
 * @brief 当本地音频文件混音时，回调播放的音频帧。
 * @param audioFrame 参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 */
- (void)onFrame:(int)playerId audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;

@end

@protocol ByteRTCMediaPlayerEventHandler <NSObject>
/** 
 * @type callback
 * @brief 音乐播放器播放状态改变时回调
 * @param playerId  <br>
 *        当前 音乐播放器 ID  <br>
 *        使用 getMediaPlayer{@link #getMediaPlayer}时传入的唯一 ID。
 * @param state  <br>
 *        混音状态  <br>
 *        其混音状态可参考：ByteRTCPlayerState{@link #ByteRTCPlayerState}。
 * @param error  <br>
 *        错误码  <br>
 *        详见 ByteRTCPlayerError{@link #ByteRTCPlayerError}。
 */
-(void)onMediaPlayerStateChanged:(int)playerId state:(ByteRTCPlayerState)state error:(ByteRTCPlayerError)error;
/** 
 * @type callback
 * @brief 混音播放进度回调
 * @param playerId  <br>
 *        当前 音乐播放器 ID  <br>
 *        使用 getMediaPlayer{@link #getMediaPlayer}时传入的唯一 ID。
 * @param progress  当前混音音频文件播放进度，单位毫秒
 */
-(void)onMediaPlayerPlayingProgress:(int)playerId progress:(int64_t)progress;

@end

/** 
 * @type api
 * @region 音乐播放器类
 * @notes 使用混音功能时，你必须通过 [setActive:withOptions:error:](https://developer.apple.com/documentation/avfaudio/avaudiosession/1616627-setactive?language=objc) 激活应用的 audio session。直到彻底退出混音功能后，才可以关闭 audio session。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMediaPlayer :NSObject

/** 
 * @type api
 * @region 音乐播放器
 * @brief 开始播放音频文件。<br>
 *        如果需要同时播放多个混音文件，请通过getMediaPlayer 获取新的音乐播放器实例进行播放。
 * @param file_path 用于混音文件路径。
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
 *        可以设置混音的播放次数、起始播放位置、是否本地播放混音、以及是否将混音发送至远端，详见 ByteRTCMediaPlayerConfig{@link #ByteRTCMediaPlayerConfig}
 * @notes  <br>
 *       + 调用本方法播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IMediaPlayer#setEventHandler}，会收到回调 `onMediaPlayerStateChanged`。  <br>
 *       + 开始播放音频文件后，可以调用 stop{@link #IMediaPlayer#stop} 方法停止播放音频文件。  <br>
 *       + 设置的config 中参数auto_play 为false时，需要调用 start{@link #IMediaPlayer#start}方法才能播放音频文件
 *       + 本方法的混音数据来源于外部文件，而 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 的混音数据来源于外部缓存且音频格式为裸数据，二者不可共存，后调用的API会覆盖前者。
 */
- (int)open:(NSString *_Nullable)filePath config:(ByteRTCMediaPlayerConfig *_Nullable)config;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 混音开始播放。
 * @notes  <br>
 *       + 调用 open{@link #IMediaPlayer#open} 方法，其中 ByteRTCMediaPlayerConfig 参数auto_play 为false时，需要调用本方法才能播放音频文件。  <br>
 *       + 调用本方法播放音频文件后，可调用 stop{@link #IMediaPlayer#stop} 方法暂停播放及混音。  <br>
 *       + 调用本方法开始播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IMediaPlayer#setEventHandler}，会收到回调 `onMediaPlayerStateChanged`。
 */
- (int)start;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 启动 音频裸数据混音。<br>
 * @param source 数据源配置  <br>
 *        可以设置数据源类型、模式等，详见 ByteRTCMediaPlayerCustomSource{@link #ByteRTCMediaPlayerCustomSource}
 * @param config 混音配置  <br>
 *        可以设置混音的播放次数、起始播放位置、是否本地播放混音、以及是否将混音发送至远端，详见 ByteRTCMediaPlayerConfig{@link #ByteRTCMediaPlayerConfig}
 * @notes  <br>
 *       + 必须先调用本方法启动 PCM 音频数据混音，随后调用 pushExternalAudioFrame{@link #pushExternalAudioFrame} 方法，才会开始混音。 <br>
 *       + 如要结束 PCM 音频数据混音，使用 stop{@link #stop}。
 */
- (int)openWithCustomSource:(ByteRTCMediaPlayerCustomSource *_Nullable)source config:(ByteRTCMediaPlayerConfig *_Nullable)config;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 停止播放音频文件及混音。
 * @notes  <br>
 *       + 调用 open{@link #IMediaPlayer#open}/start{@link #IMediaPlayer#start}/ openWithCustomSource{@link #IMediaPlayer#openWithCustomSource}方法开始播放音频文件后，可以调用本方法停止播放音频文件。  <br>
 *       + 调用本方法停止播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IMediaPlayer#setEventHandler}，会收到回调 `onMediaPlayerStateChanged`。  <br>
 *       + 调用本方法停止播放音频文件后，该音频文件会被自动卸载。
 */
- (int)stop;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 暂停播放音频文件及混音。
 * @notes  <br>
 *       + 调用 open{@link #IMediaPlayer#open}/start{@link #IMediaPlayer#start} 方法开始播放音频文件后，可以通过调用本方法暂停播放音频文件。  <br>
 *       + 调用本方法暂停播放音频文件后，可调用 resume{@link #IMediaPlayer#resume} 方法恢复播放及混音。  <br>
 *       + 调用本方法暂停播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IMediaPlayer#setEventHandler}，会收到回调 `onMediaPlayerStateChanged`。
 */
- (int)pause;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 恢复播放音频文件及混音。
 * @notes  <br>
 *       + 调用 pause{@link #IMediaPlayer#pause} 方法暂停播放音频文件后，可以通过调用本方法恢复播放及混音。  <br>
 *       + 调用本方法恢复播放音频文件后，关于当前的混音状态，如果设置了 setEventHandler{@link #IMediaPlayer#setEventHandler}，会收到回调 `onMediaPlayerStateChanged`。
 */
- (int)resume;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 调节指定混音的音量大小，包括音频文件混音和 PCM 混音。
 * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量（默认值）  <br>
 *        + 400: 最大可调音量 (自带溢出保护)
 * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 */
- (int)setVolume:(int)volume type:(ByteRTCAudioMixingType)type;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 获取当前音量
 * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @return  <br>
 *        + >0: 成功, 当前音量值。  <br>
 *        + < 0: 失败
 * @notes 调用本方法获取当前音量前，需要先调用start{@link #IMediaPlayer#start}。
 */
- (int)getVolume:(ByteRTCAudioMixingType)type;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 获取音频文件时长。
 * @return  <br>
 *        + >0: 成功, 音频文件时长，单位为毫秒。  <br>
 *        + < 0: 失败
 * @notes 调用本方法获取音频文件时长前，需要先调用 start{@link #IMediaPlayer#start}。
 */
- (int)getTotalDuration;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 获取混音音频文件的实际播放时长（单位：毫秒）。
 * @return  <br>
 *        + >0: 实际播放时长。 <br>
 *        + < 0: 失败。
 * @notes <br>
 *        + 实际播放时长指的是歌曲不受停止、跳转、倍速、卡顿影响的播放时长。例如，若歌曲正常播放到 1:30 时停止播放 30s 或跳转进度到 2:00, 随后继续正常播放 2分钟，则实际播放时长为 3分30秒。  <br>
 *        + 调用本接口前，需要先调用 start{@link #IMediaPlayer#start} 开始播放指定音频文件。
 */
- (int)getPlaybackDuration;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 获取音频文件播放进度。
 * @return  <br>
 *        + >0: 成功, 音频文件播放进度，单位为毫秒。  <br>
 *        + < 0: 失败
 * @notes 调用本方法获取音频文件播放进度前，需要先调用 start{@link #IMediaPlayer#start} 开始播放音频文件。
 */
- (int)getPosition;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br>
 *        使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。
 * @param pitch 相对于音乐文件原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
 *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
 *        超出取值范围则设置失败，并且会触发 `onMediaPlayerStateChanged` 回调，提示 ByteRTCPlayerState{@link #ByteRTCPlayerState} 状态为 `ByteRTCPlayerStateFailed` 混音播放失败，ByteRTCPlayerError{@link #ByteRTCPlayerError} 错误码为 `ByteRTCPlayerErrorInvalidPitch` 设置混音文件音调不合法。
 * @notes 本方法需要在调用 start{@link #IMediaPlayer#start} 开始播放音频文件后、调用 stop{@link #IMediaPlayer#stop} 停止播放音频文件前使用，否则会触发 `onMediaPlayerStateChanged` 回调报错
 */
- (int)setAudioPitch:(int)pitch;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 设置音频文件的起始播放位置。
 * @param position 音频文件起始播放位置，单位为毫秒。  <br>
 *        你可以通过 getDuration{@link #IMediaPlayer#getDuration} 获取音频文件总时长，position 的值应小于音频文件总时长。
 * @notes 在播放在线文件时，调用此接口可能造成播放延迟的现象。
 */
- (int)setPosition:(int)position /*in ms*/;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 设置当前音频文件的声道模式
 * @param mode 声道模式。默认的声道模式和源文件一致，详见 ByteRTCAudioMixingDualMonoMode{@link #ByteRTCAudioMixingDualMonoMode}。
 * @notes <br>
 *        + 调用本方法设置音频文件的声道模式前，需要先调用 start{@link #IMediaPlayer#start} 开始播放音频文件。<br>
 *        + 此方法对 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 播放的音乐无效。
 */
- (int)setAudioDualMonoMode:(ByteRTCAudioMixingDualMonoMode)mode;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 获取当前音频文件的音轨索引
 * @return 方法调用结果 <br>
 *        + ≥ 0：成功，返回当前音频文件的音轨索引  <br>
 *        + < 0：方法调用失败
 * @notes  <br>
 *       + 调用本方法获取音频文件的音轨前，需要先调用 start{@link #IMediaPlayer#start} 开始播放音频文件。<br>
 *       + 此方法对 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 播放的音频无效。
 */
- (int)getAudioTrackCount;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 指定当前音频文件的播放音轨
 * @param index 指定的播放音轨,从0开始，取值范围为 [0,getAudioTrackCount()-1]  <br>
 *        设置的参数值需要小于getAudioTrackCount{@link #IMediaPlayer#getAudioTrackCount} 的返回值
 * @notes  <br>
 *       + 调用本方法设置音频文件的音轨前，需要先调用 start{@link #IMediaPlayer#start} 开始播放音频文件。<br>
 *       + 此方法对 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 使用外部音频流混音播放的音乐无效。
 */
- (int)selectAudioTrack:(int)index;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 设置混音时音频文件的播放速度
 * @param speed 播放速度与原始文件速度的比例，单位：%，取值范围为 [50,200]，默认值为 100。  <br>
 *        超出取值范围则设置失败，你会收到 `onMediaPlayerStateChanged` 回调，提示 ByteRTCPlayerState{@link #ByteRTCPlayerState} 状态为 `ByteRTCPlayerStateFailed` 混音播放失败，ByteRTCPlayerError{@link #ByteRTCPlayerError} 错误码为 `ByteRTCPlayerErrorInvalidPlaybackSpeed` 设置混音文件的播放速度不合法。
 * @notes   <br>
 *        + 暂不支持对 PCM 音频数据进行变速调整。  <br>
 *        + 你需要在调用 start{@link #IMediaPlayer#start} 开始混音，并且收到`onMediaPlayerStateChanged` 回调提示 ByteRTCPlayerState{@link #ByteRTCPlayerState} 状态为 `ByteRTCPlayerStatePlaying`，ByteRTCPlayerError{@link #ByteRTCPlayerError} 错误码为 `ByteRTCPlayerErrorOK` 之后调用该方法。  <br>
 *        + 在 stop{@link #IMediaPlayer#stop} 停止混音或 unload{@link #IMediaPlayer#unload} 卸载音频文件后调用该 API，会收到状态为 `ByteRTCPlayerStateFailed` 错误码为 `ByteRTCPlayerErrorInvalidState` 的 `onMediaPlayerStateChanged` 回调。
 */
- (int)setPlaybackSpeed:(int)speed;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 设置混音时音频文件播放进度回调的间隔
 * @param interval 音频文件播放进度回调的时间间隔，单位毫秒。  <br>
 *       + interval 的值为大于 0 的 10 的倍数，当设置的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。设置完成后 SDK 将会按照设置的时间间隔触发 `onMediaPlayerPlayingProgress` 回调。  <br>
 *       + interval 的值小于等于 0 时，不会触发进度回调。  <br>
 * @notes 本方法需要在调用 start{@link #IMediaPlayer#start} 开始播放音频文件后、调用 stop{@link #IMediaPlayer#stop} 停止播放音频文件前使用，否则会触发 `onMediaPlayerStateChanged` 回调报错。  <br>
 *        若想在音乐文件开始播放前设置播放进度回调间隔，你需调用 start{@link #IMediaPlayer#start} 在 ByteRTCMediaPlayerConfig{@link #ByteRTCMediaPlayerConfig} 中设置时间间隔，开始播放后可以通过此接口更新回调间隔。
 */
- (int)setProgressInterval:(int64_t)interval;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 如果你需要使用 `enableVocalInstrumentBalance` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。
 * @param loudness 原始响度，单位：lufs，取值范围为 [-70.0, 0.0]。  <br>
 *        当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音均衡处理。默认值为 1.0lufs，即不做处理。
 * @notes 建议在 start{@link #IMediaPlayer#start} 开始播放音频文件之前调用该接口，以免播放过程中的音量突变导致听感体验下降。
 */
- (int)setLoudness:(float)loudness;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 注册本地音频文件混音的音频帧观察者。
 *        当本地音频文件混音时，会收到相关回调。
 * @param observer 参看 ByteRTCMediaPlayerAudioFrameObserver{@link #ByteRTCMediaPlayerAudioFrameObserver}。
 */
- (int)registerAudioFrameObserver:(_Nullable id<ByteRTCMediaPlayerAudioFrameObserver>)observer;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 推送 PCM 音频帧数据用于混音
 * @param audioFrame 音频帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @return  <br>
 *       + 0: 成功  <br>
 *       + < 0: 失败
 * @notes
 *      + 调用该方法前，须通过 openWithCustomSource{@link #IMediaPlayer#openWithCustomSource} 启动外部音频流混音。  <br>
 *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。要暂停播放，暂停推送即可。
 */
- (int)pushExternalAudioFrame:(ByteRTCAudioFrame *_Nullable)audioFrame;
/** 
 * @type api
 * @region 音乐播放器
 * @brief 设置事件回调，设置回调以后，可以收到 onMediaPlayerStateChanged 状态回调
 * @return  <br>
 *        + 0: 成功。  <br>
 *        + < 0: 失败
 */
- (int)setEventHandler:(_Nullable id<ByteRTCMediaPlayerEventHandler>)handler;
@end