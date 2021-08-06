//
//  byte_rtc_engine_lite.cc
//  bytertc
//
//  Created by valley on 2020/7/17.
//
#ifndef BYTE_RTC_ENGINE_LITE
#define BYTE_RTC_ENGINE_LITE
#include <memory>
#include <rtc/media/audio_effect.h>
#include "byte_rtc_engine_lite_interface.h"
#include "rtc/media/desktop_capturer_interface.h"
#include "rtc/signaling/signaling_manager.h"
#include "rtc/media/room_manager.h"
#include "rtc/engine/byte_rtc_handler_manager.h"

#include "rtc/util/byte_rtc_message_bus_config.h"
#include "rtc/util/net_reachability/net_reachability_interface.h"
#include "rtc/engine/byte_rtc_audio_frame_observer_decorator.h"
#include "rtc/engine/engine_internal_event_handler.h"

#include "modules/rtc_media/manager/rtc_media_manager.h"

#include "rtc/media/pc_factory_wrapper.h"
#include "rtc/media/rtc_media_bridge.h"
#include "byte_rtc_engine_internal.h"

#include "test/engine/byte_rtc_engine_lite_unittest.h"
#include "rtc/engine/engine_description_defines.h"
#include "test/api/base_friends.h"
#include "rtc/media/audio_device_manager.h"
#include "rtc/media/video_device_manager.h"

namespace bytertc {

class ByteRtcEngine;
class ByteRtcEngineLite : public IRtcEngineLite,
                          public DesktopCapturerCallback,
                          public basic::WeakHandler<ByteRtcEngineLite> {
public:
    void InvokeWorkerUninterruptibly(std::function<void()> runnable);

    void LeaveChannelOnThread();
    void Startup();
    void Shutdown();

    ByteRtcEngineLite(const std::string& app_id);
    ~ByteRtcEngineLite();

    const char* GetVersion(int* build) override;
    void SetRecordingVolume(const int volume) override;
    void SetPlaybackVolume(const int volume) override;
    void StartMixScreenAudioToMainStream() override;
    void StopMixScreenAudioToMainStream() override;
    void SetScreenAudioVolumeBeforeMixing(int volume) override;
    int EnableLocalAudio(bool enable) override;
    void MuteLocalAudio(MuteState state) override;
    void SetAudioScenario(AudioScenarioType scenario) override;
    void SetExternalAudioSource(
            bool enable, int sample_rate, unsigned int record_channels, unsigned int playout_channels) override;
    void SetAudioDeviceObserver(IAudioDeviceObserver* obs) override;
    bool PushExternalAudioFrame(int8_t* data, int samples) override;
    bool PullExternalAudioFrame(int8_t* data, int samples) override;
    int StartAudioMixing(const char* file_path, bool loopback, bool replace, int cycle) override;
    void StopAudioMixing() override;
    int PauseAudioMixing() override;
    int ResumeAudioMixing() override;
    int AdjustAudioMixingVolume(int volume) override;
    int AdjustAudioMixingPlayoutVolume(int volume) override;
    int AdjustAudioMixingPublishVolume(int volume) override;
    int GetAudioMixingDuration() override;
    int GetAudioMixingCurrentPosition() override;
    int SetAudioMixingPosition(int pos) override;
    int GetEffectVolume(int sound_id) override;
    int SetVolumeOfEffect(int sound_id, int volume) override;
    int PlayEffect(int sound_id, const char* file_path, bool loopback, int cycle, int volume) override;
    int PreloadEffect(int sound_id, const char* file_path) override;
    int UnloadEffect(int sound_id) override;
    int StopEffect(int sound_id) override;
    int PauseEffect(int sound_id) override;
    int ResumeEffect(int sound_id) override;
    void SetEffectsVolume(int volume) override;
    void StopAllEffects() override;
    void PauseAllEffects() override;
    void ResumeAllEffects() override;
    void UnloadAllEffects() override;
    void SetAudioPlayoutMixStream(bool enable, int sample_rate, int channel_num) override;
    int GetAudioMixingStreamCachedFrameNum() override;
    bool PushAudioMixingStreamData(int8_t* audio_frame, int frame_num) override;
    int ReplaceBackground(BACKGROUND_MODE mode, DIVIDE_MODEL divide_model) override;
    void DisableBackground() override;
    static const char* GetErrorDescription(int code);
#ifndef BYTERTC_AUDIO_ONLY
    int EnableLocalVideo(bool enable) override;
    int SetVideoEncoderConfig(const VideoSolution* solutions, int solution_num) override;
    int SetLocalVideoCanvas(StreamIndex index, const VideoCanvas& canvas) override;
    int SetLocalVideoRender(IVideoSink* render) override;
    int SetLocalScreenRender(IVideoSink* sink) override;
    int MuteLocalVideo(MuteState muteState) override;
    int StartPreview() override;
    int StopPreview() override;
    int SwitchCamera() override;
    bool PushScreenFrame(IByteVideoFrame* frame) override;
    int StartScreenCaptureByWindowId(
            view_t window_id, const Rectangle& region_rect, const DesktopCaptureParameters& capture_params) override;
    int StartScreenCaptureByScreenRect(const Rectangle& screen_rect, const Rectangle& region_rect,
            const DesktopCaptureParameters& capture_params) override;
    int StartScreenCaptureByDisplayId(unsigned int display_id, const Rectangle& region_rect,
            const DesktopCaptureParameters& capture_params) override;
    int StartScreenCapture(
            void* context, const char* group_id, const DesktopCaptureParameters& capture_params) override;
    int UpdateScreenCaptureRegion(const Rectangle& region_rect) override;
    int UpdateScreenCaptureParameters(const DesktopCaptureParameters& capture_params) override;

    void StopScreenCapture() override;
    IScreenCaptureSourceList* GetScreenCaptureSourceList() override;
    IByteVideoFrame* GetThumbnail(
            ScreenCaptureSourceType type, view_t source_id, int max_width, int max_height) override;

    void SetExternalVideoSource(bool enable) override;
    bool PushExternalVideoFrame(IByteVideoFrame* frame) override;
#endif  // BYTERTC_AUDIO_ONLY
    void SetEnableSpeakerphone(bool enable) override;
    IRtcRoom* CreateRtcRoom(const char* room_id) override;
    int SetPublishFallbackOption(int option) override;
    int SetSubscribeFallbackOption(SubscribeFallbackOptions option) override;
    int SetRemoteUserPriority(const char* user_id, RemoteUserPriority priority) override;
    int SetBusinessId(const char* business_id) override;
    void SetLocalVideoMirrorMode(MirrorMode mirrorMode) override;
    bool GetLocalVideoMirrorMode() override;
    IVideoEffect* GetVideoEffectInterface() override;

    void SetRecordingAudioFrameParameters(int sample_rate, int channels) override;
    void SetPlaybackAudioFrameParameters(int sample_rate, int channels) override;
    void SetMixedAudioFrameParameters(int sample_rate, int channels) override;
    void RegisterAudioFrameObserver(IAudioFrameObserver* observer) override;
    void RegisterMetadataObserver(IMetadataObserver* observer) override;
    void RegisterVideoFrameObserver(IVideoFrameObserver* observer) override;
    void EnableAutoPublish(bool auto_pub) override;
    IVideoDeviceManager* GetVideoDeviceManager() override;
    IAudioDeviceManager* GetAudioDeviceManager() override;
    void RegisterRemoteAudioFrameObserver(IRemoteAudioFrameObserver* observer) override;
    // 高级接口 转发调用自 byte_rtc_engine_advance.h 修改请保证顺序

#ifndef BYTERTC_AUDIO_ONLY
#endif
    static void HttpClientCallback(int callback_id, int client_id, int code, std::string data);
    static void SetHttpClient(bool is_upper_impl);
    // void SetLogReportContext(const char* project_key, const char* device_id);
    static int SetParameters(const char* parameters);
    // void SetSdkContext(const char* rtc_sdk_version, const char* rtc_sdk_git_commit);
    void SetVideoSourceHWDeviceContext(realx::RXHWDeviceContext* hw_context);
    void RegisterAudioStreamObserver(IAudioStreamObserver* observer);
    void RegisterVideoStreamObserver(IVideoStreamObserver* observer);
    bool PushExternalAudioStream(IByteAudioStream* audio_stream);
    bool PushExternalVideoStream(IByteVideoStream* video_stream);
    void SetupEngineMediaIo(const MediaIoOption& option);

    // 内部接口 转发调用自 byte_rtc_engine_internal.h 请保证修改顺序
    void SetNetworkType(NetworkType type);
    void RegisterInteranlEventHandler(IEngineInternalEventHandler* handler);

    // for game
    int SetUserTeamId(const char* team_id);
    int SetAudioGameSendMode(RangeAudioMode range_audio_mode);
    int SetAudioGameRecvdMode(RangeAudioMode range_audio_mode);
    int SendLocalUserPos(const int& x, const int& y, const int& z);
    int SendAudioRecvRange(int min_range, int max_range);
    int SetEnableRangeAudio(bool enable);

    // DesktopCapturerCallback
    void OnDesktopCaptureResult(IByteVideoFrame* frame) override;
    void OnDesktopCapturerError(int code) override;

    // 以下接口 调用自 AudioDeviceManager
    int IsMuteLocalAudioStream(bool* mute);

    IRtcRoom* CreateRtcRoom(ByteRtcEngine* engine);

    void SetAudioPerformanceProfile(AudioPerformanceProfile profile) override;

    void SetEncryptInfo(ByteEngineEncryptType encrypt_type, const char* key, int key_size) override;
    void SetCustomizeEncryptHandler(IByteEngineEncryptHandler* handler) override;
    // 运行时，业务方上报参数
    void SetRuntimeParameters(const char * json_string) override;
    
private:
    RTCSDK_FRIEND_BYTERTCENGINELITE_TEST
    basic::Instanced ins_;

    // 内部函数
    void WebrtcInit();
    void ClearInteranlEventHandler();
    void InitSignalingManager();
    SignalingEnv ByteEnvToSignalingEnv(ByteRtcEnv byteEnv);

    //成员变量
    TaskThread rtc_worker_thread_;
    // Declare this variable at topmost to ensure the destruct orders
    PeerConnectionFactoryWrapper::SignalingThreadGuard signaling_thread_guard_;
    std::unique_ptr<rtc::Thread> network_thread_;

    std::string app_id_;
    std::string business_id_;
    // for pre ice
    SignalingManager signaling_manager_;
    RtcMediaManager media_manager_;
    RtcMediaBridge media_bridge_;

    RTCRoomManager room_manager_;

    std::mutex audio_frame_observer_mutex_;
    std::unique_ptr<ByteAudioFrameObserverDecorator> audio_frame_observer_decorator_;
    std::unique_ptr<IDesktopCapturer> desktop_capture_;
    std::unique_ptr<INetReachability> net_reachability_;
    EngineInternalEventHandler* internal_event_handler_ = nullptr;
#if defined(BYTERTC_MAC) || defined(BYTERTC_WIN)
    std::unique_ptr<ScreenCaptureSourceEnumerator> screen_capture_source_enum_ = nullptr;
#endif
    VideoDeviceManager video_device_manager_;
    AudioDeviceManager audio_device_manager_;
    RTCSDK_FRIEND_MOCK_LOG_REPORT_TEST
    RTCSDK_FRIEND_BASE_API_TEST
};
}  // namespace bytertc
#endif
