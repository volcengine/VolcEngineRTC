/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCAudioMixingManager
*/

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"
/**
 * @locale zh
 * @type callback
 * @brief K 歌评分事件回调类。<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief Karaoke scoring event handler.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCSingScoringDelegate<NSObject>
@required
/**
 * @locale zh
 * @type callback
 * @brief 实时评分信息回调。调用 startSingScoring:scoringInfoInterval:{@link #ByteRTCSingScoringManager#startSingScoring:scoringInfoInterval:} 后，会收到该回调。
 * @param info 实时评分信息。详见 ByteRTCSingScoringRealtimeInfo{@link #ByteRTCSingScoringRealtimeInfo}。
 */
/**
 * @locale en
 * @type callback
 * @brief The callback for real-time scoring data. This callback is triggered after startSingScoring:scoringInfoInterval:{@link #ByteRTCSingScoringManager#startSingScoring:scoringInfoInterval:} is called.
 * @param info Real-time scoring data. See ByteRTCSingScoringRealtimeInfo{@link #ByteRTCSingScoringRealtimeInfo}.
 */
- (void)onCurrentScoringInfo:(ByteRTCSingScoringRealtimeInfo * _Nullable)info;
@end
/**
 * @locale zh
 * @type api
 * @brief K 歌评分管理接口。
 */
/**
 * @locale en
 * @type api
 * @brief Karaoke scoring management interface.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSingScoringManager :NSObject
/**
 * @locale zh
 * @type api
 * @brief 初始化 K 歌评分。
 * @param singScoringAppkey K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。
 * @param singScoringToken K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。
 * @param delegate K 歌评分事件回调类，详见 ByteRTCSingScoringDelegate{@link #ByteRTCSingScoringDelegate}。
 * @note 输入正确的鉴权信息才可以使用 K 歌评分相关的功能，鉴权方式为离线鉴权，根据包名（bundleID）绑定 Appkey 及 Token，K 歌评分密钥请联系技术支持人员申请。
 * @return  
 *        + 0：配置成功。<br>
 *        + -1：接口调用失败。<br>
 *        + -2：未集成 K 歌评分模块。<br>
 *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。  
 */
/**
 * @locale en
 * @type api
 * @brief Initialize karaoke scoring feature.
 * @param singScoringAppkey The key for karaoke scoring, used to authenticate whether the karaoke scoring is enabled.
 * @param singScoringToken The key for karaoke scoring, used to authenticate whether the karaoke scoring is enabled.
 * @param delegate Karaoke scoring event handler，see ByteRTCSingScoringDelegate{@link #ByteRTCSingScoringDelegate}.
 * @note Enter two keys to enable karaoke scoring. Authentication is done offline, bind the Appkey and Token according to the package name (bundleID). Please contact technical support to apply for the key.
 * @return  
 *        + 0：Success.<br>
 *        + -1：Interface call failed.<br>
 *        + -2： Karaoke scoring module not integrated.<br>
 *        + >0： Other error. For details, see[Error code].
 */
-(int)initSingScoring:(NSString * _Nullable)singScoringAppkey
     singScoringToken:(NSString * _Nullable)singScoringToken
             delegate:(id<ByteRTCSingScoringDelegate> _Nullable)delegate;
/**
 * @locale zh
 * @type api
 * @brief 设置 K 歌评分参数。
 * @param config K 歌评分的各项参数，详见 ByteRTCSingScoringConfig{@link #ByteRTCSingScoringConfig}。
 * @return  
 *        + 0：配置成功。<br>
 *        + -1：接口调用失败。<br>
 *        + -2：未集成K歌评分模块。<br>
 *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。 
 */
/**
 * @locale en
 * @type api
 * @brief Set the configuration of karaoke scoring.
 * @param config The parameters of karaoke scoring. See ByteRTCSingScoringConfig{@link #ByteRTCSingScoringConfig}.
 * @return  
 *        + 0：Success.<br>
 *        + -1：Interface call failed.<br>
 *        + -2： Karaoke scoring module not integrated.<br>
 *        + >0： Other error. For details, see[Error code].
 */
-(int)setSingScoringConfig:(ByteRTCSingScoringConfig * _Nullable)config;
/**
 * @locale zh
 * @type api
 * @brief 获取标准音高数据。
 * @param midiFilepath 歌曲 midi 文件路径。
 * @return ByteRTCStandardPitchInfo{@link #ByteRTCStandardPitchInfo} 标准音高数据数组。
 * @note  
 *        + 请保证此接口传入的 midi 文件路径与 setSingScoringConfig:{@link #ByteRTCSingScoringManager#setSingScoringConfig:} 接口中传入的路径一致。
 */
/**
 * @locale en
 * @type api
 * @brief Get standard pitch. 
 * @param midiFilepath Midi file path of the song.
 * @return ByteRTCStandardPitchInfo{@link #ByteRTCStandardPitchInfo} Standard pitch data array.
 * @note 
 *        + Please make sure the same midi file path is passed in this API and setSingScoringConfig:{@link #ByteRTCSingScoringManager#setSingScoringConfig:}.
 */
-(NSArray<ByteRTCStandardPitchInfo* > * _Nullable)getStandardPitchInfo:(NSString* _Nullable)midiFilepath;
/**
 * @locale zh
 * @type api
 * @brief 开始 K 歌评分。
 * @param position 开始评分时，音乐的播放进度，单位：ms。
 * @param scoringInfoInterval 实时回调的时间间隔，单位：ms；默认 50 ms。最低间隔为 20 ms。
 * @return  
 *        + 0：配置成功。<br>
 *        + -1：接口调用失败。<br>
 *        + -2：未集成K歌评分模块。<br>
 *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。 
 * @note  
 *        + 在调用 initSingScoring:singScoringToken:delegate:{@link #ByteRTCSingScoringManager#initSingScoring:singScoringToken:delegate:} 初始化 K 歌评分功能后调用该接口。<br>
 *        + 调用该接口后，将会根据设置的回调时间间隔，收到评分结果 onCurrentScoringInfo:{@link #ByteRTCSingScoringDelegate#onCurrentScoringInfo:} 回调。<br>
 *        + 如果调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 接口播放音频文件，请在收到 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}(ByteRTCAudioMixingStatePlaying) 之后调用此接口。
 */
/**
 * @locale en
 * @type api
 * @brief Start karaoke scoring. 
 * @param position You can get the playback position where you start karaoke scoring. Unit: ms.
 * @param scoringInfoInterval Time interval between two real-time callbacks. Unit: ms; Default interval: 50 ms. Minimum interval: 20 ms.
 * @return  
 *        + 0：Success.<br>
 *        + -1：Interface call failed.<br>
 *        + -2： Karaoke scoring module not integrated.<br>
 *        + >0： Other error. For details, see[Error code].
 * @note 
 *        + You can call this API after calling initSingScoring:singScoringToken:delegate:{@link #ByteRTCSingScoringManager#initSingScoring:singScoringToken:delegate:} to initialize karaoke scoring.<br>
 *        + After this interface is called, you will receive the scoring result onCurrentScoringInfo:{@link #ByteRTCSingScoringDelegate#onCurrentScoringInfo:} at set interval.<br>
 *        + If you call the startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play an audio file, call this interface after you receive rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}(ByteRTCAudioMixingStatePlaying).
 */
-(int)startSingScoring:(int)position
   scoringInfoInterval:(int)scoringInfoInterval;
/**
 * @locale zh
 * @type api
 * @brief 停止 K 歌评分。
 * @return  
 *        + 0：成功。<br>
 *        + <0：失败。
 */
/**
 * @locale en
 * @type api
 * @brief Stop karaoke scoring. 
 * @return  
 *        + 0：Success.<br>
 *        + <0：Failure.
 */
-(int)stopSingScoring;
/**
 * @locale zh
 * @type api
 * @brief 获取上一句的演唱评分。调用 startSingScoring:scoringInfoInterval:{@link #ByteRTCSingScoringManager#startSingScoring:scoringInfoInterval:} 开始评分后可以调用该接口。
 * @return  
 *        + <0：获取评分失败。<br>
 *        + >=0：上一句歌词的演唱评分。
 */
/**
 * @locale en
 * @type api
 * @brief Get the score for the previous lyric. You can call this API after startSingScoring:scoringInfoInterval:{@link #ByteRTCSingScoringManager#startSingScoring:scoringInfoInterval:} is called.
 * @return  
 *        + <0：Failed to get the score for the previous lyric.<br>
 *        + >=0：The score for the previous lyric.
 */
-(int)getLastSentenceScore;
/**
 * @locale zh
 * @type api
 * @brief 获取当前演唱总分。调用 startSingScoring:scoringInfoInterval:{@link #ByteRTCSingScoringManager#startSingScoring:scoringInfoInterval:} 开始评分后可以调用该接口。
 * @return  
 *        + <0：获取总分失败。<br>
 *        + >=0：当前演唱总分。
 */
/**
 * @locale en
 * @type api
 * @brief Get the total score for the user's current performance. You can call this API after startSingScoring:scoringInfoInterval:{@link #ByteRTCSingScoringManager#startSingScoring:scoringInfoInterval:} is called.
 * @return  
 *        + <0：Failed to get the total score.<br>
 *        + >=0：The current total score.
 */
-(int)getTotalScore;
/**
 * @locale zh
 * @type api
 * @brief 获取当前演唱歌曲的平均分。
 * @return  
 *        + <0：获取平均分失败。<br>
 *        + >=0：当前演唱平均分。
 */
/**
 * @locale en
 * @type api
 * @brief Get the average score for the user's current performance.
 * @return  
 *        + <0：Failed to get the average score.<br>
 *        + >=0：The average score.
 */
-(int)getAverageScore;
@end
