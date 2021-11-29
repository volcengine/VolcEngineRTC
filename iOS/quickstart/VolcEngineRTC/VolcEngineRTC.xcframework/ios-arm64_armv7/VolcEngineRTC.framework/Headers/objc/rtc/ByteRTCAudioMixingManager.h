/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCAudioMixingManager
*/

#import <Foundation/Foundation.h>
#import "ByteRTCDefines.h"

/**
 * @type api
 * @region 混音
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioMixingManager :NSObject

/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 开始播放音乐文件及混音
 * @param id  <br>
 *        混音 ID  <br>
 *        混音 ID 用于标识混音，请保证混音 ID 唯一性。  <br>
 *        如果已经通过 preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} 将音效加载至内存，确保此处的 ID 与 preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} 设置的 ID 相同。  <br>
 *        使用相同的 ID 重复调用该方法后，前一次混音会停止，后一次混音开始，且 SDK 会使用 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:} 回调通知前一次混音已停止。
 * @param filePath  <br>
 *        指定需要混音的本地文件的绝对路径，支持音频文件格式有: mp3，aac，m4a，3gp，wav。  <br>
 *        可以通过传入不同的 ID 和 filepath 多次调用本方法，以实现同时播放多个混音文件，实现混音叠加。
 * @param config  <br>
 *        混音配置 <br>
 *        可以设置混音的播放次数、是否本地播放、以及是否将混音发送至远端，详见 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig}。
 * @notes  <br>
 *       + 调用本方法播放音乐文件后，SDK 会向本地回调当前的混音状态，见 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}。  <br>
 *       + 开始播放音乐文件及混音后，可以调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 方法停止播放音乐文件。  <br>
 *       + 本方法混音数据来源于外部文件，而 enableAudioMixingFrame:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:} 混音的数据来源外部缓存且音频格式为 PCM，这两种混音方式可以共存。  <br>
 */
-(void)startAudioMixing:(int)id filePath:(NSString * _Nullable)filePath config:(ByteRTCAudioMixingConfig * _Nullable)config;

/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 停止播放音乐文件及混音
 * @param id  <br>
 *        混音 ID
 * @notes  <br>
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音乐文件及混音后，可以调用本方法停止播放音乐文件及混音。  <br>
 *       + 调用本方法停止播放音乐文件后，SDK 会向本地回调通知已停止混音，见 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}。  <br>
 *       + 调用本方法停止播放音乐文件后，该音乐文件会被自动卸载。
 */
-(void)stopAudioMixing:(int)id;

/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 暂停播放音乐文件
 * @param id  <br>
 *        混音 ID
 * @notes  <br>
 *       + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音乐文件及混音后，可以通过调用该方法暂停播放音乐文件。  <br>
 *       + 调用本方法暂停播放音乐文件后，可调用 resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} 方法恢复播放及混音。  <br>
 *       + 调用本方法暂停播放音乐文件后，SDK 会向本地回调通知已暂停混音，见 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}。
 */
-(void)pauseAudioMixing:(int)id;

/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 恢复播放音乐文件
 * @param id  <br>
 *        混音 ID
 * @notes  <br>
 *       + 调用 pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} 方法暂停播放音乐文件后，可以通过调用本方法恢复播放及混音。  <br>
 *       + 调用本方法恢复播放音乐文件后，SDK 会向本地回调通知音乐文件正在播放中，见 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}。
 */
-(void)resumeAudioMixing:(int)id;


/**
 * @type api
 * @region 混音
 * @brief 预加载指定音乐文件到内存中
 * @param id  <br>
 *        混音 ID  <br>
 *        应用调用者维护，请保证唯一性。 <br>
 *        如果使用相同的 ID 重复调用本方法，后一次会覆盖前一次。  <br>
 *        如果先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}，再使用相同的 ID 调用本方法 ，会先回调 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:} 上一个混音停止，然后加载后一个混音。  <br>
 *        使用一个 ID 调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 播放 B.mp3，请先调用 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载 A.mp3 ，否则会报错 ByteRTCAudioMixingErrorLoadConflict。
 * @param filePath  <br>
 *        指定需要混音的本地文件的绝对路径，支持音频文件格式有: mp3，aac，m4a，3gp，wav。  <br>
 *        如果音乐文件长度超过 20s，会回调加载失败，见 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}。
 * @notes  <br>
 *       + 需要频繁播放某个音乐文件的时候，调用本方法预加载该文件，在播放的时候可以只加载一次该文件，减少 CPU 占用。  <br>
 *       + 本方法只是预加载播放指定音乐文件，只有调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法才开始播放指定音乐文件。 <br>
 *       + 调用本方法预加载音乐文件后，SDK 会回调通知音乐文件已加载，见 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}。  <br>
 *       + 调用本方法预加载的指定音乐文件可以通过 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载。
 */
-(void)preloadAudioMixing:(int)id filePath:(NSString * _Nullable)filePath;

/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 卸载指定音乐文件
 * @param id  <br>
 *        混音 ID
 * @notes 不论音乐文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 rtcEngine:onAudioMixingStateChanged:state:error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingStateChanged:state:error:}。
 */
-(void)unloadAudioMixing:(int)id;

/**
 * @type api
 * @region 混音
 * @brief 调节音乐文件在本地和远端播放的音量大小
 * @param id  <br>
 *        混音 ID
 * @param volume  <br>
 *        音乐文件播放音量范围为 0~400。  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量  <br>
 *        + 400: 最大可调音量 (自带溢出保护)
 * @param type  <br>
 *        混音播放类型  <br>
 *        设置音乐文件是否本地播放、以及是否发送到远端，由此控制音乐文件本地或远端播放的音量，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @notes  <br>
 *       + 调用本方法设置音量前，请先调用 preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} 或 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}。  <br>
 *       + 为保证更好的音质，建议将 volume 值设为 [0,100]。
 */
-(void)setAudioMixingVolume:(int)id volume:(int)volume type:(ByteRTCAudioMixingType)type;

/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 获取音乐文件时长
 * @param id  <br>
 *        混音 ID
 * @return  <br>
 *       + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
 *       + <0: 失败
 * @notes 调用本方法获取音乐文件时长前，需要先调用 preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} 或 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}。
 */
-(int)getAudioMixingDuration:(int)id;

/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 获取音乐文件播放进度
 * @param id  <br>
 *        混音 ID
 * @return  <br>
 *        + >0: 成功, 音乐文件播放进度，单位为毫秒。  <br>
 *        + <0: 失败
 * @notes 调用本方法获取音乐文件播放进度前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音乐文件。
 */
-(int)getAudioMixingCurrentPosition:(int)id;

/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 设置音乐文件的播放位置
 * @param id  <br>
 *        混音 ID
 * @param position  <br>
 *        进度条位置  <br>
 *        参数为整数，单位为毫秒。
 * @notes  <br>
 *       + 该方法可以设置音乐文件的播放位置，这样你可以根据实际情况从指定的位置播放音乐文件，无需从头到尾完整播放一个音乐文件。  <br>
 *       + 调用本方法设置音乐文件的播放位置前，需要先调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音乐文件。
 */
-(void)setAudioMixingPosition:(int)id position:(int)position;

/**
 * @type api
 * @region 混音
 * @brief 启动外部音频流混音
 * @param type  <br>
 *        混音播放类型  <br>
 *        设置外部音频流是否本地播放、以及是否发送到远端，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}。
 * @notes  <br>
 *       + 必须先调用本方法启动外部音频流混音，随后调用 pushAudioMixingFrame:{@link #ByteRTCAudioMixingManager#pushAudioMixingFrame:} 方法，才能向 SDK 推送外部音频帧数据。 <br>
 *       + 本方法的混音数据来源于外部缓存且音频格式为 PCM；而 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 的混音数据来源于外部文件，支持的文件格式有: mp3，aac，m4a，3gp，wav；这两种混音方式可以共存。  <br>
 *       + 该方法启动的外部音频流混音不支持音量调节，暂停，暂停恢复操作。  <br>
 *       + 如要关闭外部音频流混音，请使用 disableAudioMixingFrame{@link #ByteRTCAudioMixingManager#disableAudioMixingFrame}。
 */
-(void)enableAudioMixingFrame:(ByteRTCAudioMixingType)type;
/**
 * @type api
 * @region 混音
 * @brief 关闭外部音频流混音
 * @notes 使用 enableAudioMixingFrame:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:} 开启外部音频流混音后，请使用本方法关闭该混音。
 */
-(void)disableAudioMixingFrame;
/**
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 向 SDK 推送外部音频帧数据
 * @param audioFrame  <br>
 *        音频帧  <br>
 *        详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  <br>
 *       + 0: 设置成功  <br>
 *       + <0: 设置失败
 * @notes
 *      + 调用该方法前，须通过 enableAudioMixingFrame:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:} 启动外部音频流混音。  <br>
 *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
 */
-(int)pushAudioMixingFrame:(ByteRTCAudioFrame* _Nullable)audioFrame;
@end
