#pragma once

#include <Windows.h>
#include <list>
#include <string>
#include <functional>
#include "byte_rtc_engine_interface.h"
#include "byte_rtc_video_frame.h"
#include "ByteMessage.h"
using namespace std;

enum {
    RtcDeviceTypeVideoCapture = 0,
    RtcDeviceTypeAudioRecord,
    RtcDeviceTypeAudioPlayout,
};

enum UserOfflineType {
    USER_OFFLINE_NORMAL,
    USER_OFFLINE_REPEAT_LOGIN,
    USER_OFFLINE_JOIN_FAILD,
};

enum SubscribeMode {
    AutoSubscribeMode = 0,
    ManualSubscribeMode = 1,
};

struct SubscribeConfig{
    bool is_screen = false;
    bool sub_video = false;
};

struct RemoteStream {
    std::string user_id;
    bool is_screen;
};

struct RtcDevice {
    std::string name;
    std::string guid;
    int type;
};

class EngineWrapper : public bytertc::IRtcEngineEventHandler
{
public:
    static EngineWrapper* GetInstance();

    void setEventHandler(HWND hwnd);
    void createEngine(const std::string& appid);
    void destroyEngine();

    const char* getVersion();

    void preview();
    void stopPreview();

    void SubscribeVideoStream(const char* user_id, const SubscribeConfig& info);
    void UnsubscribeVideoStream(const char* user_id, bool screen);

    void muteLocalAudio(bool bMute);
    void muteLocalVideo(bool bMute);

    void setupLocal(HWND hwnd, const char* uid);
    void setupRemote(HWND hwnd, const char* uid);

    void login(const char* roomid, const char* uid, const char* token);
    bool logout();

    void muteAllRemoteVideo(bool mute);

    void EnableAudioVolumeIndication(int interval, int smooth);
    bool AudioRecordDevicesTest();

    /*@param[in] data  <br>
    *        反馈数据为 JSON 格式，必须包含以下 5 个上报项，缺少则上报失败。  <br>
    *        1. grade： 分值，[1, 5]的整数闭区间，分值越大越好。  <br>
    *        2. type： 反馈问题类型，参考 PROBLEM_FEEDBACK{ @link #PROBLEM_FEEDBACK } 。  <br>
    *        3. problem_desc： 问题描述。  <br>
    *        4. os_version： 操作系统版本，参考{ Windows_10 | Windows_8 | Windows_7 | Windows_XP | UNKNOWN } 。  <br>
    *        5. network_type： 当前的网络类型，参考{ WIFI｜5G｜4G｜3G｜2G｜UNKNON } 。
    */
    void feedback(const char* message);

    void setVideoProfiles(const bytertc::VideoSolution* solutions, int solution_num);
    void setScreenProfiles(const bytertc::VideoSolution& solution);

    std::vector<RtcDevice> GetAudioInputDevices();
    void SetAudioInputDevice(int index);
    void GetAudioInputDevice(char* guid);

    std::vector<RtcDevice> GetAudioOutputDevices();
    void SetAudioOutputDevice(int index);
    void GetAudioOutputDevice(char* guid);

    std::vector<RtcDevice> GetVideoCaptureDevices();
    void SetVideoCaptureDevice(int index);
    void GetVideoCaptureDevice(char* guid);

    int setupRemoteScreenRender(std::string& uid, const HWND render);
    int startScreenCapture(void* source_id, const std::vector<HWND>& excluded);
    int startScreenCaptureByWindowId(HWND window_id);
    void stopScreenCapture();
    bool getShareList(std::list<SnapshotAttr>& list);
    bytertc::IByteVideoFrame* GetThumbnail(
        SnapshotAttr::SnapshotType type, void* source_id, int max_width, int max_height);
    void RegisterVideoFrameObserver(bytertc::IVideoFrameObserver* obs);

private:
    void SetVideoDefaultProfile();

private:
    int m_nSelectedAudioCaptureDev;
    std::vector<RtcDevice> m_lstAudioCaptureDevices;

    int m_nSelectedPlayoutDev;
    std::vector<RtcDevice> m_lstPlayoutDevices;

    int m_nSelectedVideoCaptureDev;
    std::vector<RtcDevice> m_lstVideoCaptureDevices;

    bytertc::DesktopCaptureParameters m_screen_param;

public:
    void OnJoinChannelSuccess(const char* channel, const char* uid, int elapsed) override;
    void OnRejoinChannelSuccess(const char* channel, const char* uid, int elapsed) override;
    void OnRtcStats(const bytertc::RtcStats& stats) override;
    void OnLocalVideoStats(const bytertc::LocalVideoStats& stats) override;
    void OnLocalAudioStats(const bytertc::LocalAudioStats& stats) override;
    void OnRemoteVideoStats(const  bytertc::RemoteVideoStats& stats) override;
    void OnRemoteAudioStats(const bytertc::RemoteAudioStats& stats) override;
    void OnWarning(int warn) override;
    void OnError(int err) override;
    void OnAudioVolumeIndication(const bytertc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;
    void OnLeaveChannel(const bytertc::RtcStats& stats) override;
    //void OnUserJoined(const bytertc::ByteUser* users_list, int user_number) override;
    //void OnUserOffline(const bytertc::ByteUserOfflineInfo* users_list, int user_number) override;
    void OnUserJoined(const char* uid, const char* team_id, const bytertc::RangeAudioMode send_mode, int elapsed) override;
    void OnUserOffline(const char* uid, bytertc::USER_OFFLINE_REASON_TYPE reason) override;
    void OnUserMuteAudio(const char* user_id, bytertc::MuteState mute_state) override;
    void OnUserEnableLocalAudio(const char* uid, bool enabled) override;

    void OnFirstLocalAudioFrame(bytertc::StreamIndex index) override;
    //void OnStreamRemove(const bytertc::ByteStreamRemovedInfo* streams_list, int stream_number) override;
    void OnStreamRemove(const bytertc::ByteStream& stream, bytertc::RtcStreamRemoveReason reason) override;
    void OnLogReport(const char* log_type, const char* log_content) override;
    void OnStreamAdd(const bytertc::ByteStream& stream) override;
    //void OnStreamAdd(const bytertc::ByteStream* streams_list, int stream_number) override;
    void OnStreamSubscribed(bytertc::SUBSCRIBE_STATE stateCode, const char* stream_id, const bytertc::SubscribeConfig& info) override;
    void OnStreamPublishSucceed(const char* user_id, bool is_screen) override;
    void OnAudioRouteChanged(int routing) override;
    void OnFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) override;
    void OnFirstRemoteVideoFrameRendered(const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info) override;
    void OnUserMuteVideo(const char* uid, bytertc::MuteState mute) override;

    void OnUserEnableLocalVideo(const char* uid, bool enabled) override;
    void OnMediaDeviceNotification(const char* device_id, bytertc::MediaDeviceType device_type,
        bytertc::MediaDeviceNotification notification_type) override;
    void OnLocalVideoStateChanged(bytertc::StreamIndex index, bytertc::LocalVideoStreamState state, bytertc::LocalVideoStreamError error) override;
    void OnLocalAudioStateChanged(bytertc::LocalAudioStreamState state, bytertc::LocalAudioStreamError error) override;

public:
    bytertc::IRtcEngine* m_pEngine;
    HWND m_desktop;

    std::string m_room_id;
    std::string m_user_id;

public:
    bool m_bMuteAudio;
    bool m_bMuteVideo;
};

