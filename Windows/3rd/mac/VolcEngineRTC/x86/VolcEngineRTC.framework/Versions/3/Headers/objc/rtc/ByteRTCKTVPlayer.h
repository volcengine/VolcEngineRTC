/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCKTVPlayer
*/

#import <Foundation/Foundation.h>
#import "ByteRTCKTVDefines.h"
@class ByteRTCKTVPlayer;

NS_ASSUME_NONNULL_BEGIN
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
@protocol ByteRTCKTVPlayerDelegate <NSObject>

/**
 * @locale zh
 * @type callback
 * @brief 音乐播放进度回调。
 * @param ktvPlayer 当前 ktvPlayer 对象，参看 ByteRTCKTVPlayer{@link #ByteRTCKTVPlayer}。
 * @param musicId 音乐 ID。
 * @param progress 音乐播放进度，单位为毫秒。
 */
/**
 * @locale en
 * @type callback
 * @brief Music playing progress callback.
 * @param ktvPlayer Current ktvPlayer. See ByteRTCKTVPlayer{@link #ByteRTCKTVPlayer}.
 * @param musicId Music ID.
 * @param progress Music playing progress in milliseconds.
 */
- (void)ktvPlayer:(ByteRTCKTVPlayer *)ktvPlayer onPlayProgress:(NSString *)musicId progress:(int64_t)progress;

/**
 * @locale zh
 * @type callback
 * @brief 音乐播放状态改变回调。
 * @param ktvPlayer 当前 ktvPlayer 对象，参看 ByteRTCKTVPlayer{@link #ByteRTCKTVPlayer}。
 * @param musicId 音乐 ID。
 * @param state 音乐播放状态，参看 ByteRTCPlayState{@link #ByteRTCPlayState}。
 * @param error 错误码，参看 ByteRTCKTVPlayerErrorCode{@link #ByteRTCKTVPlayerErrorCode}。
 * @note 
 *       此回调被触发的时机汇总如下：<br>
 *       + 调用 playMusic:audioTrackType:audioPlayType:{@link #ByteRTCKTVPlayer#playMusic:audioTrackType:audioPlayType:} 成功后，会触发 playState 值为 ByteRTCPlayStatePlaying 的回调；否则会触发 playState 值为 ByteRTCPlayStateFailed 的回调。<br>
 *       + 使用相同的音乐 ID 重复调用 playMusic:audioTrackType:audioPlayType:{@link #ByteRTCKTVPlayer#playMusic:audioTrackType:audioPlayType:} 后，后一次播放会覆盖前一次，且会触发 playState 值为 ByteRTCPlayStatePlaying 的回调，表示后一次音乐播放已开始。<br>
 *       + 调用 pauseMusic:{@link #ByteRTCKTVPlayer#pauseMusic:} 方法暂停播放成功后，会触发 playState 值为 ByteRTCPlayStatePaused 的回调；否则触发 playState 值为 ByteRTCPlayStateFailed 的回调。<br>
 *       + 调用 resumeMusic:{@link #ByteRTCKTVPlayer#resumeMusic:} 方法恢复播放成功后，会触发 playState 值为 ByteRTCPlayStatePlaying 的回调；否则触发 playState 值为 ByteRTCPlayStateFailed 的回调。<br>
 *       + 调用 stopMusic:{@link #ByteRTCKTVPlayer#stopMusic:} 方法停止播放成功后，会触发 playState 值为 ByteRTCPlayStateStoped 的回调；否则触发 playState 值为 ByteRTCPlayStateFailed 的回调。<br>
 *       + 音乐播放结束会触发 playState 值为 ByteRTCPlayStateFinished 的回调。
 */
/**
 * @locale en
 * @type callback
 * @brief Music playing state changed callback.
 * @param ktvPlayer Current ktvPlayer. See ByteRTCKTVPlayer{@link #ByteRTCKTVPlayer}.
 * @param musicId Music ID.
 * @param state Music playing status. See ByteRTCPlayState{@link #ByteRTCPlayState}.
 * @param error Error code. See ByteRTCKTVPlayerErrorCode{@link #ByteRTCKTVPlayerErrorCode}.
 * @note 
 *       You will receive this callback on following events.<br>
 *       + When you successfully start playing music by calling playMusic:audioTrackType:audioPlayType:{@link #ByteRTCKTVPlayer#playMusic:audioTrackType:audioPlayType:}, you will receive this callback with `ByteRTCPlayStatePlaying` playState. Otherwise the playState will be `ByteRTCPlayStateFailed`.<br>
 *       + If the music with the same music ID is playing when you call playMusic:audioTrackType:audioPlayType:{@link #ByteRTCKTVPlayer#playMusic:audioTrackType:audioPlayType:} again, the music will restart from the starting position, and you will receive this callback with `ByteRTCPlayStatePlaying` playState to inform the latter music has started.<br>
 *       + When you successfully pause the music by calling pauseMusic:{@link #ByteRTCKTVPlayer#pauseMusic:}, you will receive this callback with `ByteRTCPlayStatePaused` playState. Otherwise the playState will be `ByteRTCPlayStateFailed`.<br>
 *       + When you successfully resume the music by calling resumeMusic:{@link #ByteRTCKTVPlayer#resumeMusic:}, you will receive this callback with `ByteRTCPlayStatePlaying` playState. Otherwise the playState will be `ByteRTCPlayStateFailed`.<br>
 *       + When you successfully stop the music by calling stopMusic:{@link #ByteRTCKTVPlayer#stopMusic:}, you will receive this callback with `ByteRTCPlayStateStoped` playState. Otherwise the playState will be `ByteRTCPlayStateFailed`.<br>
 *       + When the music ends, you will receive this callback with `ByteRTCPlayStateFinished` playState.
 */
- (void)ktvPlayer:(ByteRTCKTVPlayer *)ktvPlayer onPlayStateChanged:(NSString *)musicId state:(ByteRTCPlayState)state error:(ByteRTCKTVPlayerErrorCode)error;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCKTVPlayer : NSObject

@property(nonatomic, weak) id<ByteRTCKTVPlayerDelegate> delegate;

#pragma mark - Core Methods
/**
 * @locale zh
 * @type api
 * @brief 播放歌曲。
 * @param musicId 音乐 ID。<br>
 *        若同一 musicId 的歌曲正在播放，再次调用接口会从开始位置重新播放。若 musicId 对应的音频文件不存在会触发报错。
 * @param trackType 原唱伴唱类型，参看 ByteRTCAudioTrackType{@link #ByteRTCAudioTrackType}。
 * @param playType 音乐播放类型。参看 ByteRTCAudioPlayType{@link #ByteRTCAudioPlayType}。
 * @note  
 *        + 调用接口后，你会收到 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调歌曲播放状态。<br>
 *        + 若音乐 ID 错误，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3023，playState 为 4。<br>
 *        + 若未进房，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3022，playState 为 4。<br>
 *        + 若音乐文件不存在，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3020，playState 为 4。
 */
/**
 * @locale en
 * @type api
 * @brief Plays the music.
 * @param musicId Music ID.<br>
 *        If the song with the same musicId is playing when you call this API, the music will restart from the starting position. An error will be triggered if the audio file corresponding to musicId does not exist.
 * @param trackType Audio track type of the KTV player. See ByteRTCAudioTrackType{@link #ByteRTCAudioTrackType}.
 * @param playType Audio play type. See ByteRTCAudioPlayType{@link #ByteRTCAudioPlayType}.
 * @note  
 *       + After calling this API, you will receive the music play state through ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback.<br>
 *       + If the music ID is invalid, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3023 and a playState of 4.<br>
 *       + If you didn't join the room, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3022 and a playState of 4.<br>
 *       + If the music file does not exist, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3020 and a playState of 4.
 */
- (void)playMusic:(NSString * _Nonnull)musicId audioTrackType:(ByteRTCAudioTrackType)trackType audioPlayType:(ByteRTCAudioPlayType)playType;

/**
 * @locale zh
 * @type api
 * @brief 暂停播放歌曲。
 * @param musicId 音乐 ID。
 * @note  
 *        + 调用接口后，你会收到 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调歌曲播放状态。<br>
 *        + 若音乐 ID 错误，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3023，playState 为 4。<br>
 *        + 若未进房，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3022，playState 为 4。
 */
/**
 * @locale en
 * @type api
 * @brief Pauses the music.
 * @param musicId Music ID.
 * @note  
 *       + After calling this API, you will receive the music play state through ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback.<br>
 *       + If the music ID is invalid, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3023 and a playState of 4.<br>
 *       + If you didn't join the room, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3022 and a playState of 4.
 */
- (void)pauseMusic:(NSString * _Nonnull)musicId;

/**
 * @locale zh
 * @type api
 * @brief 继续播放歌曲。
 * @param musicId 音乐 ID。
 * @note  
 *        + 调用接口后，你会收到 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调歌曲播放状态。<br>
 *        + 若音乐 ID 错误，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3023，playState 为 4。<br>
 *        + 若未进房，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3022，playState 为 4。
 */
/**
 * @locale en
 * @type api
 * @brief Resumes playing the music.
 * @param musicId Music ID.
 * @note  
 *       + After calling this API, you will receive the music play state through ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback.<br>
 *       + If the music ID is invalid, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3023 and a playState of 4.<br>
 *       + If you didn't join the room, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3022 and a playState of 4.
 */
- (void)resumeMusic:(NSString * _Nonnull)musicId;

/**
 * @locale zh
 * @type api
 * @brief 停止播放歌曲。
 * @param musicId 音乐 ID。
 * @note  
 *        + 调用接口后，你会收到 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调歌曲播放状态。<br>
 *        + 若音乐 ID 错误，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3023，playState 为 4。<br>
 *        + 若未进房，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3022，playState 为 4。
 */
/**
 * @locale en
 * @type api
 * @brief Stops playing the music.
 * @param musicId Music ID.
 * @note  
 *       + After calling this API, you will receive the music play state through ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback.<br>
 *       + If the music ID is invalid, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3023 and a playState of 4.<br>
 *       + If you didn't join the room, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3022 and a playState of 4.
 */
- (void)stopMusic:(NSString * _Nonnull)musicId;

/**
 * @locale zh
 * @type api
 * @brief 设置音乐文件的起始播放位置。
 * @param musicId 音乐 ID。
 * @param position 音乐起始位置，单位为毫秒，取值小于音乐文件总时长。
 * @note 
 *        + 调用本接口时音乐必须处于播放中状态。<br>
 *        + 调用接口后，你会收到 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调歌曲播放状态。<br>
 *        + 若音乐 ID 错误，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3023，playState 为 4。<br>
 *        + 若未进房，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3022，playState 为 4。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the starting position of the music file.
 * @param musicId Music ID.
 * @param position The starting position of the music file in milliseconds. The value must be less than the total length of the music.
 * @note  
 *       + The music must be playing when you call this API.<br>
 *       + After calling this API, you will receive the music play state through ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback.<br>
 *       + If the music ID is invalid, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3023 and a playState of 4.<br>
 *       + If you didn't join the room, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3022 and a playState of 4.
 */
- (void)seekMusic:(NSString * _Nonnull)musicId position:(int)position;

/**
 * @locale zh
 * @type api
 * @brief 设置歌曲播放音量，只能在开始播放后进行设置。
 * @param musicId 音乐 ID。
 * @param volume 歌曲播放音量，调节范围：[0,400]。<br>
 *        + 0：静音。<br>
 *        + 100：原始音量。 <br>
 *        + 400: 原始音量的 4 倍(自带溢出保护)。
 * @note 
 *        + 调用本接口时音乐必须处于播放中状态。<br>
 *        + 若设置的音量大于 400，则按最大值 400 进行调整；若设置的音量小于 0，则按最小值 0 进行调整。<br>
 *        + 若音乐 ID 错误，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3023，playState 为 4。<br>
 *        + 若未进房，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3022，playState 为 4。
 */
/**
 * @locale en
 * @type api
 * @brief Sets the volume of the playing music. The music must be playing when you set the volume.
 * @param musicId Music ID.
 * @param volume Volume. Adjustment range: [0,400].<br>
 *         + 0: Mute.<br>
 *         + 100: Original volume.<br>
 *         + 400: 4 times the original volume (with overflow protection).
 * @note  
 *       + The music must be playing when you call this API.<br>
 *       + If the set volume is greater than 400, it will be adjusted by the maximum value of 400; if the set volume is less than 0, it will be adjusted by the minimum value of 0.<br>
 *       + If the music ID is invalid, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3023 and a playState of 4.<br>
 *       + If you didn't join the room, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3022 and a playState of 4.
 */
- (void)setMusicVolume:(NSString * _Nonnull)musicId volume:(int)volume;

/**
 * @locale zh
 * @type api
 * @brief 切换歌曲原唱伴唱。
 * @param musicId 音乐 ID。
 * @note 调用本接口时音乐必须处于播放中状态。
 */
/**
 * @locale en
 * @type api
 * @brief Switches the audio track type between the original track and the instrumental track.
 * @param musicId Music ID.
 * @note The music must be playing when you call this API.
 */
- (void)switchAudioTrackType:(NSString * _Nonnull)musicId;

/**
 * @locale zh
 * @type api
 * @brief 对播放中的音乐设置升降调信息。
 * @param musicId 音乐 ID。
 * @param pitch 相对于音乐文件原始音调的升高/降低值，取值范围 [-12，12]，默认值为 0，即不做调整。<br>
 *              取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。
 * @note 
 *        + 调用本接口时音乐必须处于播放中状态。<br>
 *        + 若设置的 pitch 大于 12，则按最大值 12 进行调整；若设置的 pitch 小于 –12，，则按最小值 –12 进行调整。<br>
 *        + 若音乐 ID 错误，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3023，playState 为 4。<br>
 *        + 若未进房，会触发 ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} 回调，errorCode 为 –3022，playState 为 4。
 */
/**
 * @locale en
 * @type api
 * @brief Transposes up/down the music being played.
 * @param musicId Music ID.
 * @param pitch The pitch up/down value relative to the original pitch, in the range of [-12, 12], with the default value of 0.<br>
 *              The difference in pitch between two adjacent values is a semitone. A positive value indicates an increase in pitch, and a negative value indicates a decrease in pitch. A larger absolute value means more pitch increase or decrease.
 * @note 
 *       + The music must be in the playing when you call this API.<br>
 *       + If the set pitch is greater than 12, it will be adjusted by the maximum value of 12; if the set pitch is less than –12, it will be adjusted by the minimum value of –12.<br>
 *       + If the music ID is invalid, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3023 and a playState of 4.<br>
 *       + If you didn't join the room, you will receive the ktvPlayer:onPlayStateChanged:state:error:{@link #ByteRTCKTVPlayerDelegate#ktvPlayer:onPlayStateChanged:state:error:} callback, with an errorCode of -3022 and a playState of 4.
 */
- (void)setMusicPitch:(NSString * _Nonnull)musicId pitch:(int)pitch;

@end

NS_ASSUME_NONNULL_END
