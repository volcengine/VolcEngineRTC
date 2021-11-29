/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Audio Mixing Manager
*/

#pragma once

#ifndef BYTE_RTC_AUDIO_MIXING_MANAGER_H__
#define BYTE_RTC_AUDIO_MIXING_MANAGER_H__
#include "bytertc_audio_frame.h"
#include "bytertc_defines.h"

namespace bytertc {

/**
 * @type api
 * @brief 混音管理类
 */
class IAudioMixingManager {
public:
    /**
     * @hidden
     * @brief 构造函数
     */
    IAudioMixingManager() {
    }

    /**
     * @type api
     * @region 混音
     * @brief 开始播放音乐文件及混音
     * @param [in] id  <br>
     *        混音 ID  <br>   
     *        混音 ID 用于标识混音，请保证混音 ID 唯一性。  <br>
     *        如果已经通过 PreloadAudioMixing{@link #PreloadAudioMixing} 将音效加载至内存，确保此处的 ID 与 PreloadAudioMixing{@link #PreloadAudioMixing} 设置的 ID 相同。  <br>
     *        如果使用相同的 ID 重复调用本方法，前一次混音会停止，后一次混音开始，且 SDK 会使用 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged} 回调通知前一次混音已停止。
     * @param [in] file_path  <br>
     *        指定需要混音的本地文件的绝对路径，支持音频文件格式有: mp3，aac，m4a，3gp，wav。  <br>
     *       可以通过传入不同的 ID 和 file_path 多次调用本方法，以实现同时播放多个音乐文件，实现混音叠加。
     * @param [in] config  <br>
     *        混音配置  <br>
     *        可以设置混音的播放次数、是否本地播放混音、以及是否将混音发送至远端，详见 AudioMixingConfig{@link #AudioMixingConfig}
     * @notes  <br>
     *       + 调用本方法成功播放音乐文件后，SDK 会向本地回调当前的混音状态，见 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged}。  <br>
     *       + 开始播放音乐文件及混音后，可以调用 StopAudioMixing{@link #StopAudioMixing} 方法停止播放音乐文件。  <br>
     *       + 本方法混音数据来源于外部文件，而 EnableAudioMixingFrame{@link #EnableAudioMixingFrame} 的混音数据来源于外部缓存且音频格式为 PCM；这两种混音方式可以共存。
     */
    virtual void StartAudioMixing(int id, const char * file_path, const AudioMixingConfig& config) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 停止播放音乐文件及混音
     * @param [in] id  <br>
     *        混音 ID 
     * @notes  <br>
     *       + 调用 StartAudioMixing{@link #StartAudioMixing} 方法开始播放音乐文件及混音后，可以调用本方法停止播放音乐文件及混音。  <br>
     *       + 调用本方法停止播放音乐文件后，SDK 会向本地回调通知已停止混音，见 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged}。  <br>
     *       + 调用本方法停止播放音乐文件后，该音乐文件会被自动卸载。
     */
    virtual void StopAudioMixing(int id) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 暂停播放音乐文件及混音
     * @param [in] id  <br>
     *        混音 ID  
     * @notes  <br>
     *       + 调用 StartAudioMixing{@link #StartAudioMixing} 方法开始播放音乐文件及混音后，可以通过调用本方法暂停播放音乐文件及混音。  <br>
     *       + 调用本方法暂停播放音乐文件及混音后，可调用 ResumeAudioMixing{@link #ResumeAudioMixing} 方法恢复播放及混音。  <br>
     *       + 调用本方法暂停播放音乐文件后，SDK 会向本地回调通知已暂停混音，见 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged}。 
     */
    virtual void PauseAudioMixing(int id) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 恢复播放音乐文件及混音
     * @param [in] id  <br>
     *        混音 ID 
     * @notes  <br>
     *       + 调用 PauseAudioMixing{@link #PauseAudioMixing} 方法暂停播放音乐文件及混音后，可以通过调用本方法恢复播放及混音。  <br>
     *       + 调用本方法恢复播放音乐文件及混音后，SDK 会向本地回调通知音乐文件正在播放中，见 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged}。 
     */
    virtual void ResumeAudioMixing(int id) = 0;


    /**
     * @type api
     * @region 混音
     * @brief 预加载指定音乐文件到内存中
     * @param [in] id  <br>
     *        混音 ID  <br>
     *        应用调用者维护，请保证唯一性。  <br>
     *        如果使用相同的 ID 调用本方法，后一次会覆盖前一次。 <br>
     *        如果先调用 StartAudioMixing{@link #StartAudioMixing} ，再使用相同的 ID 调用本方法 ，会先回调 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged} 上一个混音停止，然后加载后一个混音。  <br>
     *        使用一个 ID 调用本方法预加载 A.mp3 后，如果需要使用相同的 ID 调用 StartAudioMixing{@link #StartAudioMixing} 播放 B.mp3，请先调用 UnloadAudioMixing{@link #UnloadAudioMixing} 卸载 A.mp3 ，否则会报错 kAudioMixingErrorLoadConflict。
     * @param [in] file_path  <br>
     *        指定需要混音的本地文件的绝对路径，支持音频文件格式有: mp3，aac，m4a，3gp，wav。  <br>
     *        如果音乐文件长度超过 20s，会回调加载失败，见 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged}。 
     * @notes  <br>
     *       + 需要频繁播放某个音乐文件的时候，调用本方法预加载该文件，在播放的时候可以只加载一次该文件，减少 CPU 占用。  <br>
     *       + 本方法只是预加载指定音乐文件，只有调用 StartAudioMixing{@link #StartAudioMixing} 方法才开始播放指定音乐文件。 <br>
     *       + 调用本方法预加载音乐文件后，SDK 会回调通知音乐文件已加载，见 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged}。  <br>
     *       + 调用本方法预加载的指定音乐文件可以通过 UnloadAudioMixing{@link #UnloadAudioMixing} 卸载。  
     */
    virtual void PreloadAudioMixing(int id, const char* file_path) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 卸载指定音乐文件
     * @param [in] id  <br>
     *        混音 ID 
     * @notes 不论音乐文件是否播放，调用本方法卸载该文件后，SDK 会回调通知混音已停止，见 OnAudioMixingStateChanged{@link #OnAudioMixingStateChanged}。
     */
    virtual void UnloadAudioMixing(int id) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 调节音乐文件在本地和远端播放的音量大小
     * @param [in] id  <br>
     *        混音 ID 
     * @param [in] volume  <br>
     *        音乐文件播放音量范围为 0~400。  <br>
     *        + 0：静音  <br>
     *        + 100：原始音量  <br>
     *        + 400: 最大可调音量 (自带溢出保护)
     * @param [in] type  <br>
     *        混音播放类型  <br>
     *        设置音乐文件是否本地播放、以及是否发送到远端，由此控制音乐文件本地或远端播放的音量，详见 AudioMixingType{@link #AudioMixingType}。
     * @notes  <br>
     *       + 调用本方法设置音量前，请先调用 PreloadAudioMixing{@link #PreloadAudioMixing} 或 StartAudioMixing{@link #StartAudioMixing}。  <br>     
     *       + 为保证更好的音质，建议将 volume 值设为 [0,100]。 
     */
    virtual void SetAudioMixingVolume(int id, int volume, AudioMixingType type) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 获取音乐文件时长
     * @param [in] id  <br>
     *        混音 ID
     * @return  <br>
     *        + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
     *        + <0: 失败
     * @notes 调用本方法获取音乐文件时长前，需要先调用 PreloadAudioMixing{@link #PreloadAudioMixing} 或 StartAudioMixing{@link #StartAudioMixing}。
     */
    virtual int GetAudioMixingDuration(int id) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 获取音乐文件播放进度
     * @param [in] id  <br>
     *        混音 ID
     * @return  <br>
     *        + >0: 成功, 音乐文件播放进度，单位为毫秒。  <br>
     *        + <0: 失败
     * @notes 调用本方法获取音乐文件播放进度前，需要先调用 StartAudioMixing{@link #StartAudioMixing} 开始播放音乐文件。
     */
    virtual int GetAudioMixingCurrentPosition(int id) = 0;
    /**
     * @type api
     * @region 混音
     * @brief 设置音乐文件的播放位置
     * @param [in] id  <br>
     *        混音 ID
     * @param [in] position  <br>
     *        进度条位置  <br>
     *        参数为整数，单位为毫秒。
     * @notes  <br> 
     *       + 本方法可以设置音乐文件的播放位置，这样你可以根据实际情况从指定的位置播放音乐文件，无需从头到尾完整播放一个音乐文件。  <br>
     *       + 调用本方法设置音乐文件的播放位置前，需要先调用 StartAudioMixing{@link #StartAudioMixing} 开始播放音乐文件。
     */
    virtual void SetAudioMixingPosition(int id, int position) = 0;

    /**
     * @type api
     * @region 混音
     * @brief 启动外部音频流混音
     * @param [in] type  <br>
     *        混音播放类型  <br>
     *        设置外部音频流是否本地播放、以及是否发送到远端，详见 AudioMixingType{@link #AudioMixingType}。
     * @notes  <br>
     *       + 必须先调用本方法启动外部音频流混音，随后调用 PushAudioMixingFrame{@link #PushAudioMixingFrame} 方法，才能向 SDK 推送外部音频帧数据。 <br>
     *       + 本方法的混音数据来源于外部缓存且音频格式为 PCM；而 StartAudioMixing{@link #StartAudioMixing} 的混音数据来源于外部文件，支持的文件格式有: mp3，aac，m4a，3gp，wav；这两种混音方式可以共存。  <br>
     *       + 该方法启动的外部音频流混音不支持音量调节，暂停，暂停恢复操作。  <br>
     *       + 如要关闭外部音频流混音，请使用 DisableAudioMixingFrame{@link #DisableAudioMixingFrame}。
     */
    virtual void EnableAudioMixingFrame(AudioMixingType type) = 0;
    
    /**
     * @type api
     * @region 混音
     * @brief 关闭外部音频流混音
     * @notes 使用 EnableAudioMixingFrame{@link #EnableAudioMixingFrame} 开启外部音频流混音后，请使用本方法关闭该混音。
     */
    virtual void DisableAudioMixingFrame() = 0;

    /**
     * @type api
     * @region 混音
     * @brief 向 SDK 推送外部音频帧数据
     * @param [in] audioFrame  <br>
     *        音频帧  <br>
     *        详见 IAudioFrame{@link #IAudioFrame}。 
     * @return  <br>
     *       + 0: 设置成功  <br>
     *       + <0: 设置失败
     * @notes
     *      + 调用该方法前，须通过 EnableAudioMixingFrame{@link #EnableAudioMixingFrame} 启动外部音频流混音。  <br>
     *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 100 毫秒），然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     */  
    virtual int PushAudioMixingFrame(IAudioFrame* audio_frame) = 0;

    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioMixingManager() {
    }
};

}  // namespace bytertc

#endif // BYTE_RTC_AUDIO_MIXING_MANAGER_H__
