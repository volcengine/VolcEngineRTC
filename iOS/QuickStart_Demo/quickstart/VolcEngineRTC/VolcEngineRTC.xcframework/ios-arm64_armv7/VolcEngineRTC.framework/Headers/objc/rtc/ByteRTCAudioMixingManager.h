/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCAudioMixingManager
*/

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"
/** 
 * @type callback
 * @brief 本地音频文件混音的音频帧观察者。
 */
@protocol ByteRTCAudioFileFrameObserver <NSObject>
/** 
 * @type callback
 * @brief 当本地音频文件混音时，回调播放的音频帧。
 * @param mix_id 混音 ID。
 * @param audio_frame 参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 */
- (void)onAudioFileFrame:(int)mix_id
                    audioFrame:(ByteRTCAudioFrame * _Nonnull)audio_frame;

@end

/** 
 * @type api
 * @region 混音
 * @notes 使用混音功能时，你必须通过 [setActive:withOptions:error:](https://developer.apple.com/documentation/avfaudio/avaudiosession/1616627-setactive?language=objc) 激活应用的 audio session。直到彻底退出混音功能后，才可以关闭 audio session。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioMixingManager :NSObject
/** 
 * @type api
 * @region 混音
 * @brief 开始播放音频文件。
 *        可以通过传入不同的 mixId 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。
 * @param mixId 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br>
 *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，SDK 会使用 `onAudioMixingStateChanged` 回调通知前一次混音已停止。
 * @param filePath 用于混音文件路径。
 *        支持在线文件的 URL、和本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。
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
 *        可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig}
 * @notes  <br>
 *       + 如果已经通过 preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} 将文件加载至内存，确保此处的 ID 与预加载时设置的 ID 相同。  <br>
 *       + 调用本方法播放音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  <br>
 *       + 开始播放音频文件后，可以调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 方法停止播放音频文件。  <br>
 *       + 本方法的混音数据来源于外部文件，而 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 的混音数据来源于外部缓存且音频格式为 PCM，这两种混音方式可以共存。
 */
-(void)startAudioMixing:(int)mixId filePath:(NSString * _Nullable)filePath config:(ByteRTCAudioMixingConfig * _Nullable)config;

/** 
 * @type api
 * @region 混音
 * @brief 停止播放音频文件及混音。
 * @param mixId  <br>
 *        混音 ID
 * @notes  <br>
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音频文件及混音后，可以调用本方法停止播放音频文件及混音。  <br>
 *       + 调用本方法停止播放音频文件后，SDK 会向本地回调通知已停止混音，见 `onAudioMixingStateChanged`。  <br>
 *       + 调用本方法停止播放音频文件后，该音频文件会被自动卸载。
 */
-(void)stopAudioMixing:(int)mixId;
/** 
 * @type api
 * @region 混音
 * @brief 停止播放所有音频文件。
 * @notes  <br>
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音频文件后，可以调用本方法停止播放所有音频文件。  <br>
 *       + 调用本方法停止播放所有音频文件后，会收到 `onAudioMixingStateChanged` 回调，通知已停止播放。  <br>
 *       + 调用本方法停止播放所有音频文件后，该音频文件会被自动卸载。
 */
-(void)stopAllAudioMixing;

/** 
 * @type api
 * @region 混音
 * @brief 暂停播放音频文件及混音。
 * @param mixId  <br>
 *        混音 ID
 * @notes  <br>
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音频文件及混音后，可以通过调用该方法暂停播放音频文件。  <br>
 *       + 调用本方法暂停播放音频文件后，可调用 resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} 方法恢复播放及混音。  <br>
 *       + 调用本方法暂停播放音频文件后，SDK 会向本地回调通知已暂停混音，见 `onAudioMixingStateChanged`。
 */
-(void)pauseAudioMixing:(int)mixId;
/** 
 * @type api
 * @region 混音
 * @brief 暂停播放所有音频文件。
 * @notes  <br>
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}方法开始播放音频文件后，可以通过调用本方法暂停播放所有音频文件。  <br>
 *       + 调用本方法暂停播放所有音频文件后，可调用 resumeAllAudioMixing{@link #ByteRTCAudioMixingManager#resumeAllAudioMixing} 方法恢复所有播放。  <br>
 *       + 调用本方法暂停播放所有音频文件后，会收到 `onAudioMixingStateChanged` 回调，通知已暂停播放。
 */
-(void)pauseAllAudioMixing;

/** 
 * @type api
 * @region 混音
 * @brief 恢复播放音频文件及混音。
 * @param mixId  <br>
 *        混音 ID
 * @notes  <br>
 *       + 调用 pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} 方法暂停播放音频文件后，可以通过调用本方法恢复播放及混音。  <br>
 *       + 调用本方法恢复播放音频文件后，SDK 会向本地回调通知音频文件正在播放中，见 `onAudioMixingStateChanged`。
 */
-(void)resumeAudioMixing:(int)mixId;
/** 
 * @type api
 * @region 混音
 * @brief 恢复播放所有音频文件。
 * @notes  <br>
 *       + 调用 pauseAllAudioMixing{@link #ByteRTCAudioMixingManager#pauseAllAudioMixing} 方法暂停所有正在播放音频文件后，可以通过调用本方法恢复播放。  <br>
 *       + 调用本方法恢复播放所有音频文件后，会收到 `onAudioMixingStateChanged` 回调，通知已恢复播放。
 */
-(void)resumeAllAudioMixing;

/** 
 * @type api
 * @region 混音
 * @brief 预加载指定音乐文件到内存中，以避免频繁播放同一文件时的重复加载，减少 CPU 占用。
 * @param mixId 混音 ID。用于标识混音，请保证混音 ID 唯一性。  <br>
 *        如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br>
 *        如果先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}，再使用相同的 ID 调用本方法 ，会先回调 `onAudioMixingStateChanged` 通知上一个混音停止，然后加载后一个混音。  <br>
 *        调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 播放 B.mp3，请先调用 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载 A.mp3。
 * @param filePath 混音文件路径。<br>
 *        支持在线文件的 URL、和本地文件的绝对路径。对于在线文件的 URL，仅支持 https 协议。预加载的文件长度不得超过 20s。<br>
 *        不同平台支持的音频文件格式: <br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @notes  <br>
 *       + 本方法只是预加载指定音频文件，只有调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法才开始播放指定音频文件。 <br>
 *       + 调用本方法预加载音频文件后，关于当前的混音状态，会收到回调 `onAudioMixingStateChanged`。  <br>
 *       + 调用本方法预加载的指定音频文件可以通过 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载。
 */
-(void)preloadAudioMixing:(int)mixId filePath:(NSString * _Nullable)filePath;

/** 
 * @type api
 * @region 混音
 * @brief 卸载指定音乐文件。
 * @param mixId  <br>
 *        混音 ID
 * @notes 不论音频文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 `onAudioMixingStateChanged`。
 */
-(void)unloadAudioMixing:(int)mixId;

/** 
 * @hidden(macOS)
 * @type api
 * @region 混音
 * @brief 设置默认的混音音量大小，包括音频文件混音和 PCM 混音。
 * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量（默认值）  <br>
 *        + 400: 最大可调音量 (自带溢出保护)
 * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @notes 该接口的优先级低于 setAudioMixingVolume:volume:type:{@link #ByteRTCAudioMixingManager#setAudioMixingVolume:volume:type:}，即通过 setAudioMixingVolume:volume:type:{@link #ByteRTCAudioMixingManager#setAudioMixingVolume:volume:type:} 单独设置了音量的混音 ID，不受该接口设置的影响。
 */
-(void)setAllAudioMixingVolume:(int)volume type:(ByteRTCAudioMixingType)type;

/** 
 * @type api
 * @region 混音
 * @brief 调节指定混音的音量大小，包括音频文件混音和 PCM 混音。
 * @param mixId 需调节音量的混音 ID
 * @param volume 混音音量相对原音量的比值。范围为 `[0, 400]`，建议范围是 `[0, 100]`。  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量（默认值）  <br>
 *        + 400: 最大可调音量 (自带溢出保护)
 * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @notes 该方法仅对指定混音 ID 生效。iOS 端提供 setAllAudioMixingVolume:type:{@link #ByteRTCAudioMixingManager#setAllAudioMixingVolume:type:} 接口调节全部混音文件播放音量。
 */
-(void)setAudioMixingVolume:(int)mixId volume:(int)volume type:(ByteRTCAudioMixingType)type;

/** 
 * @type api
 * @region 混音
 * @brief 获取音频文件时长。
 * @param mixId  <br>
 *        混音 ID
 * @return  <br>
 *       + >0: 成功, 音频文件时长，单位为毫秒。  <br>
 *       + < 0: 失败
 * @notes 调用本方法获取音频文件时长前，需要先调用 preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} 或 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}。
 */
-(int)getAudioMixingDuration:(int)mixId;

/** 
 * @type api
 * @region 混音
 * @brief 获取音频文件播放进度。
 * @param mixId  <br>
 *        混音 ID
 * @return  <br>
 *        + >0: 成功, 音频文件播放进度，单位为毫秒。  <br>
 *        + < 0: 失败
 * @notes 调用本方法获取音频文件播放进度前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件。
 */
-(int)getAudioMixingCurrentPosition:(int)mixId;
/** 
 * @type api
 * @region 混音
 * @brief 设置音频文件的起始播放位置
 * @param mixId 混音 ID
 * @param position 音频文件起始播放位置，单位为毫秒。  <br>
 *        你可以通过 getAudioMixingDuration:{@link #ByteRTCAudioMixingManager#getAudioMixingDuration:} 获取音频文件总时长，position 的值不得大于音频文件总时长。
 * @notes 在播放在线文件时，调用此接口可能造成播放延迟的现象。
 */
-(void)setAudioMixingPosition:(int)mixId position:(int)position;

/** 
 * @type api
 * @region 混音
 * @brief 设置当前音频文件的声道模式
 * @param mixId 混音 ID
 * @param mode 声道模式。默认的声道模式和源文件一致，详见 ByteRTCAudioMixingDualMonoMode{@link #ByteRTCAudioMixingDualMonoMode}。
 * @notes <br>
 *        + 调用本方法设置音频文件的声道模式前，需要先调用 startAudioMixing:filePath:config:{@link #startAudioMixing:filePath:config:} 开始播放音频文件。<br>
 *        + 此方法对 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 播放的音乐无效。
 */
-(void) setAudioMixingDualMonoMode:(int)mixId mode:(ByteRTCAudioMixingDualMonoMode)mode;

/** 
 * @type api
 * @region 混音
 * @brief 开启本地播放音乐文件变调功能，多用于 K 歌场景。  <br>
 *        使用该方法，你可以对本地播放音乐文件的音调进行升调或降调等调整。
 * @param mixId 混音 ID
 * @param pitch 相对于音乐文件原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
 *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
 *        超出取值范围则设置失败，并且会触发 `onAudioMixingStateChanged` 回调，提示 ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} 状态为 `AUDIO_MIXING_STATE_FAILED` 混音播放失败，ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} 错误码为 `AUDIO_MIXING_ERROR_ID_TYPE_INVALID_PITCH` 设置混音文件音调不合法。
 * @notes 本方法需要在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件后、调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错
 */
-(void)setAudioMixingPitch:(int)mixId pitch:(int)pitch;

/** 
 * @type api
 * @region 混音
 * @brief 设置混音时音频文件的播放速度
 * @param mixId 混音 ID
 * @param speed 播放速度与原始文件速度的比例，单位：%，取值范围为 [50,200]，默认值为 100。  <br>
 *        超出取值范围则设置失败，你会收到 `onAudioMixingStateChanged` 回调，提示 ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} 状态为 `ByteRTCAudioMixingStateFailed` 混音播放失败，ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} 错误码为 `ByteRTCAudioMixingErrorInValidPlaybackSpeed` 设置混音文件的播放速度不合法。
 * @notes   <br>
 *        + 暂不支持对 PCM 音频数据进行变速调整。  <br>
 *        + 你需要在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始混音，并且收到`onAudioMixingStateChanged` 回调提示 ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} 状态为 `ByteRTCAudioMixingStatePlaying`，ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} 错误码为 `AUDIO_MIXING_ERROR_OK` 之后调用该方法。  <br>
 *        + 在 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 停止混音或 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载音频文件后调用该 API，会收到状态为 `ByteRTCAudioMixingStateFailed` 错误码为 `ByteRTCAudioMixingErrorIdNotFound` 的 `onAudioMixingStateChanged` 回调。
 */
- (int)setAudioMixingPlaybackSpeed:(int)mixId speed:(int)speed;

/** 
 * @type api
 * @region 混音
 * @brief 如果你需要使用 `enableVocalInstrumentBalance:` 对混音音频文件/PCM 音频数据进行音量调整，你必须通过此接口传入其原始响度。
 * @param mixId 混音 ID
 * @param loudness 原始响度，单位：lufs，取值范围为 [-70.0, 0.0]。  <br>
 *        当设置的值小于 -70.0lufs 时，则默认调整为 -70.0lufs，大于 0.0lufs 时，则不对该响度做音均衡处理。默认值为 1.0lufs，即不做处理。
 * @notes 建议在 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件之前调用该接口，以免播放过程中的音量突变导致听感体验下降。
 */
-(void)setAudioMixingLoudness:(int)mixId loudness:(float)loudness;

/** 
 * @type api
 * @region 混音
 * @brief 设置混音时音频文件播放进度回调的间隔
 * @param mixId 混音 ID  <br>
 *        可以通过多次调用本接口传入不同的 ID 对多个 ID 进行间隔设置。
 * @param interval 音频文件播放进度回调的时间间隔，单位毫秒。  <br>
 *       + interval 的值为大于 0 的 10 的倍数，当设置的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。设置完成后 SDK 将会按照设置的时间间隔触发 `onAudioMixingPlayingProgress` 回调。  <br>
 *       + interval 的值小于等于 0 时，不会触发进度回调。  <br>
 * @notes 本方法需要在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件后、调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 停止播放音频文件前使用，否则会触发 `onAudioMixingStateChanged` 回调报错。  <br>
 *        若想在音乐文件开始播放前设置播放进度回调间隔，你需调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 在 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} 中设置时间间隔，开始播放后可以通过此接口更新回调间隔。
 */
-(void) setAudioMixingProgressInterval:(int)mixId interval:(int64_t) interval;

 /** 
  * @type api
  * @region 混音
  * @brief 启动 PCM 音频数据混音。<br>
  *        要实现多个 PCM 音频数据混音，多次调用本方法，并传入不同的 id。
  * @param mixId 混音 ID。用于标识混音，保证混音 ID 唯一性。  <br>
  *        如果使用相同的 ID 重复调用本方法后，前一次混音会停止，后一次混音开始，会收到 `onAudioMixingStateChanged` 通知前一次混音已停止。
  * @param type 混音类型。是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
  * @notes  <br>
  *       + 必须先调用本方法启动 PCM 音频数据混音，随后调用 pushAudioMixingFrame:audioFrame:{@link #pushAudioMixingFrame:audioFrame:} 方法，才会开始混音。 <br>
  *       + 如要结束 PCM 音频数据混音，使用 disableAudioMixingFrame:{@link #disableAudioMixingFrame:}。
  */
 -(void)enableAudioMixingFrame:(int)mixId type:(ByteRTCAudioMixingType)type;

/** 
 * @type api
 * @region 混音
 * @brief 关闭 PCM 混音
 * @param mixId 混音 ID。
 */
-(void)disableAudioMixingFrame:(int)mixId;

/** 
 * @type api
 * @region 混音
 * @brief 推送 PCM 音频帧数据用于混音
 * @param mixId 混音 ID。
 * @param audioFrame 音频帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @return  <br>
 *       + 0: 成功  <br>
 *       + < 0: 失败
 * @notes
 *      + 调用该方法前，须通过 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 启动外部音频流混音。  <br>
 *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。要暂停播放，暂停推送即可。
 */
- (int)pushAudioMixingFrame:(int)mixId audioFrame:(ByteRTCAudioFrame* _Nullable)audioFrame;
/** 
 * @type api
 * @region 混音
 * @brief 获取当前音频文件的音轨索引。
 * @param mixId 混音 ID
 * @return 方法调用结果 <br>
 *        + ≥ 0：成功，返回当前音频文件的音轨索引。  <br>
 *        + < 0：方法调用失败。
 * @notes  <br>
 *       + 调用本方法获取音频文件的音轨前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件。<br>
 *       + 此方法对 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 播放的音频无效。
 */
-(int)getAudioTrackCount:(int)mixId;
/** 
 * @type api
 * @region 混音
 * @brief 指定当前音频文件的播放音轨。
 * @param mixId 混音 ID
 * @param audioTrackIndex 指定的播放音轨。  <br>
 *        设置的参数值需要小于或等于 getAudioTrackCount:{@link #ByteRTCAudioMixingManager#getAudioTrackCount:} 的返回值
 * @notes  <br>
 *       + 调用本方法设置音频文件的音轨前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件。<br>
 *       + 此方法对 enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} 播放的音乐无效。
 */
-(void)selectAudioTrack:(int)mixId audioTrackIndex:(int)audioTrackIndex;
/** 
 * @type api
 * @brief 注册本地音频文件混音的音频帧观察者。
 *        当本地音频文件混音时，会收到相关回调。
 * @param observer 参看 ByteRTCAudioFileFrameObserver{@link #ByteRTCAudioFileFrameObserver}。
 */
- (void)registerAudioFileFrameObserver:(_Nullable id<ByteRTCAudioFileFrameObserver>) observer;

/** 
  * @hidden(macOS)
  * @type api
  * @region 混音
  * @brief 获取混音音频文件的实际播放时长（单位：毫秒）。
  * @param mixId 混音ID。
  * @return  <br>
  *        + >0: 实际播放时长。 <br>
  *        + < 0: 失败。
  * @notes <br>
  *        + 实际播放时长指的是歌曲不受停止、跳转、倍速、卡顿影响的播放时长。例如，若歌曲正常播放到 1:30 时停止播放 30s 或跳转进度到 2:00, 随后继续正常播放 2分钟，则实际播放时长为 3分30秒。  <br>
  *        + 调用本接口前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放指定音频文件。
  */
 -(int)getAudioMixingPlaybackDuration:(int)mixId;
@end
