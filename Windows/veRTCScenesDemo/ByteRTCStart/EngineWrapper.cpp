#include "EngineWrapper.h"
#include "ByteMessage.h"
#include "ByteAppConfig.h"
#include "byte_rtc_engine_advance.h"
#include "byte_rtc_engine_defines.h"
#include "Utils.h"
#include <algorithm>
#include <map>

EngineWrapper* g_pEngine = NULL;

EngineWrapper* EngineWrapper::GetInstance() {
    if (g_pEngine == NULL) {
        g_pEngine = new EngineWrapper();
    }
    return g_pEngine;
}

void EngineWrapper::setEventHandler(HWND hwnd) {
    m_desktop = hwnd;
}

void EngineWrapper::createEngine(const std::string& appid) {
    m_screen_param.max_width = 1920;
    m_screen_param.max_height = 1080;
    m_screen_param.frame_rate = 15;
    m_screen_param.bitrate = 2000;

    m_bMuteAudio = false;
    m_bMuteVideo = false;
    bytertc::SetEnv(bytertc::kEnvTest);

    m_pEngine = bytertc::CreateByteRtcEngine(appid.c_str(), this);
    if (m_pEngine) {
        m_pEngine->EnableAutoSubscribe(bytertc::kAutoSubscribeMode, bytertc::kManualSubscribeMode);
        m_pEngine->EnableLocalVideo(true);
        m_pEngine->MuteLocalVideo(bytertc::MuteState::kMuteStateOff);
        m_pEngine->MuteAllRemoteVideo(bytertc::MuteState::kMuteStateOff);
        m_pEngine->SetLocalVideoMirrorMode(bytertc::MirrorMode::kMirrorModeOn);
        m_pEngine->SetSubscribeFallbackOption(bytertc::kStreamFallbackOptionAudioOnly);
    }

    SetVideoDefaultProfile();
}

void EngineWrapper::destroyEngine() {
    if (m_pEngine) {
        bytertc::DestroyByteRtcEngine(m_pEngine);
        m_pEngine = NULL;
    }
}

const char* EngineWrapper::getVersion() {
    if (m_pEngine) {
        int build = 0;
        return m_pEngine->GetVersion(&build);
    }
    return "unknown";
}

void EngineWrapper::SubscribeVideoStream(const char* user_id, const SubscribeConfig& info) {
    if (m_pEngine) {
        bytertc::SubscribeConfig subConfig;
        subConfig.is_screen = info.is_screen;
        subConfig.sub_video = info.sub_video;
        subConfig.sub_audio = true;
        subConfig.video_index = 0;

        m_pEngine->SubscribeStream(user_id, subConfig);
    }
}

void EngineWrapper::UnsubscribeVideoStream(const char* user_id, bool screen) {
    if (m_pEngine) {
        m_pEngine->Unsubscribe(user_id, screen);
    }
}

void EngineWrapper::preview() {
    if (m_pEngine) {
        //bytertc::VideoCanvas canvas;
        //canvas.uid = "001";
        //canvas.render_mode = bytertc::RENDER_MODE_HIDDEN;
        //canvas.view = handler;
        //m_pEngine->SetupLocalVideo(canvas);
        m_pEngine->EnableLocalVideo(true);
        m_pEngine->StartPreview();
    }
}

void EngineWrapper::feedback(const char* message) {
    //bytertc::Feedback(message);
}

void EngineWrapper::stopPreview() {
    if (m_pEngine) {
        //bytertc::VideoCanvas canvas;
        //canvas.uid = "001";
        //canvas.render_mode = bytertc::RENDER_MODE_HIDDEN;
        //canvas.view = nullptr;
        //m_pEngine->SetupLocalVideo(canvas);
        m_pEngine->EnableLocalVideo(false);
        m_pEngine->StopPreview();
    }
}

void EngineWrapper::muteLocalAudio(bool bMute) {
    if (m_pEngine) {
        m_pEngine->MuteLocalAudio(bMute ? bytertc::MuteState::kMuteStateOn : bytertc::MuteState::kMuteStateOff);
        m_pEngine->EnableLocalAudio(!bMute);
    }
}

void EngineWrapper::muteLocalVideo(bool bMute) {
    if (m_pEngine) {
        m_pEngine->EnableLocalVideo(!bMute);
    }
}

void EngineWrapper::muteAllRemoteVideo(bool mute) {
    if (m_pEngine) {
        m_pEngine->MuteAllRemoteVideo(mute ? bytertc::MuteState::kMuteStateOn : bytertc::MuteState::kMuteStateOff);
    }
}

void EngineWrapper::EnableAudioVolumeIndication(int interval, int smooth) {
    if (m_pEngine) {
        m_pEngine->SetAudioVolumeIndicationInterval(interval);
    }
}

void EngineWrapper::setupLocal(HWND hwnd, const char* uid) {
    if (m_pEngine) {
        bytertc::VideoCanvas canvas;
        canvas.uid = uid;
        canvas.render_mode = bytertc::RENDER_MODE_HIDDEN;
        canvas.view = hwnd;

        m_pEngine->SetLocalVideoCanvas(bytertc::StreamIndex::kStreamIndexMain, canvas);
    }
}

void EngineWrapper::setupRemote(HWND hwnd, const char* uid) {
    bytertc::VideoCanvas canvas;
    canvas.uid = uid;
    canvas.render_mode = bytertc::RENDER_MODE_HIDDEN;
    canvas.view = hwnd;

    m_pEngine->SetRemoteVideoCanvas(uid, bytertc::StreamIndex::kStreamIndexMain, canvas);
}

void EngineWrapper::setScreenProfiles(const bytertc::VideoSolution& solution) {
    m_screen_param.max_width = solution.width;
    m_screen_param.max_height = solution.height;
    m_screen_param.frame_rate = solution.fps;
    m_screen_param.bitrate = solution.max_send_kbps;
}

int EngineWrapper::startScreenCapture(void* source_id, const std::vector<HWND>& excluded) {
    if (m_pEngine) {
        if (!excluded.empty()) {
            m_screen_param.excluded_window_list = (bytertc::view_t*)excluded.data();
            m_screen_param.excluded_window_num = excluded.size();
        }

        m_pEngine->StartScreenCaptureByDisplayId((unsigned int)source_id, bytertc::Rectangle(), m_screen_param);
    }
    return 0;
}

int EngineWrapper::startScreenCaptureByWindowId(HWND window_id) {
    if (m_pEngine) {
        m_pEngine->StartScreenCaptureByWindowId(window_id, bytertc::Rectangle(), m_screen_param);
    }
    return 0;
}

int EngineWrapper::setupRemoteScreenRender(std::string& uid, const HWND render) {
    bytertc::VideoCanvas canvas;
    canvas.uid = uid.c_str();
    canvas.render_mode = bytertc::RENDER_MODE_FIT;
    canvas.view = render;

    m_pEngine->SetRemoteVideoCanvas(uid.c_str(), bytertc::StreamIndex::kStreamIndexScreen, canvas);

    return 0;
}

void EngineWrapper::stopScreenCapture() {
    if (m_pEngine) {
        m_pEngine->StopScreenCapture();
    }
}

bool EngineWrapper::getShareList(std::list<SnapshotAttr>& list) {
    if (!m_pEngine) return false;

    const BDString capital_figures[] = {"桌面 一", "桌面 二", "桌面 三",
                                     "桌面 四", "桌面 五", "桌面 六",
                                     "桌面 七", "桌面 八", "桌面 九"};

    int display_index = 0;
    SnapshotAttr snapshot;
    auto sourcelist = m_pEngine->GetScreenCaptureSourceList();
    int count = sourcelist->GetCount();
    for (int i = 0; i < count; ++i) {
        auto source = sourcelist->GetSourceInfo(i);
        snapshot.m_name = source.source_name;
        snapshot.source_id = source.source_id;
        switch (source.type)
        {
        case bytertc::kScreenCaptureSourceTypeScreen: {
            snapshot.m_type = SnapshotAttr::SNAPSHOT_SCREEN;
            auto pos = std::find_if(list.begin(), list.end(), [](const SnapshotAttr& s) {
                return s.m_type == SnapshotAttr::SNAPSHOT_WINDOW;
            });

            snapshot.m_name = rtcutil::ConvertBDStringToUTF8(capital_figures[display_index]);
            ++display_index;

            if (pos != list.end()) {
                list.insert(pos, snapshot);
            }
            else {
                list.push_back(snapshot);
            }
            break;
        }
        case bytertc::kScreenCaptureSourceTypeWindow:
            snapshot.m_type = SnapshotAttr::SNAPSHOT_WINDOW;
            list.push_back(snapshot);
            break;
        default:
            break;
        }
    }

    sourcelist->Release();

    return 0;
}

bytertc::IByteVideoFrame* EngineWrapper::GetThumbnail(
    SnapshotAttr::SnapshotType type, void* source_id, int max_width, int max_height) {
    if (!m_pEngine) return nullptr;
    auto s_type = bytertc::kScreenCaptureSourceTypeUnknown;
    switch (type)
    {
    case SnapshotAttr::SNAPSHOT_SCREEN:
        s_type = bytertc::kScreenCaptureSourceTypeScreen;
        break;
    case SnapshotAttr::SNAPSHOT_WINDOW:
        s_type = bytertc::kScreenCaptureSourceTypeWindow;
        break;
    default:
        break;
    }
    return m_pEngine->GetThumbnail(s_type, source_id, max_width, max_height);
}

void EngineWrapper::RegisterVideoFrameObserver(bytertc::IVideoFrameObserver* obs) {
    if (m_pEngine) {
        m_pEngine->RegisterVideoFrameObserver(obs);
    }
}

void EngineWrapper::login(const char* roomid, const char* uid, const char* token) {
    if (m_pEngine) {
        m_pEngine->EnableAutoSubscribe(bytertc::kAutoSubscribeMode, bytertc::kManualSubscribeMode);
        m_pEngine->JoinChannel(token, roomid, uid, "");

        m_room_id = roomid;
        m_user_id = uid;
    }
}

bool EngineWrapper::logout() {
    if (m_pEngine) {
        stopScreenCapture();
        m_pEngine->LeaveChannel();
    }

    return true;
}

void EngineWrapper::OnJoinChannelSuccess(const char* channel, const char* uid, int elapsed) {
    //::SendMessage(m_desktop, WM_NOTIFY_JOIN_OK, (WPARAM)uid, 0);
}

void EngineWrapper::OnRejoinChannelSuccess(const char* channel, const char* uid, int elapsed) {

}

void EngineWrapper::OnRtcStats(const bytertc::RtcStats& stats) {
    ::SendMessage(m_desktop, WM_NOTIFY_RTC_STATS, (WPARAM)&stats, 0);
}

void EngineWrapper::OnLocalVideoStats(const bytertc::LocalVideoStats& stats) {
    ::SendMessage(m_desktop, WM_NOTIFY_LOCAL_VIDEO_STATS, (WPARAM)&stats, 0);
}

void EngineWrapper::OnLocalAudioStats(const bytertc::LocalAudioStats& stats) {
    ::SendMessage(m_desktop, WM_NOTIFY_LOCAL_AUDIO_STATS, (WPARAM)&stats, 0);
}

void EngineWrapper::OnRemoteVideoStats(const  bytertc::RemoteVideoStats& stats) {
    ::SendMessage(m_desktop, WM_NOTIFY_REMOTE_VIDEO_STATS, (WPARAM)&stats, 0);
}

void EngineWrapper::OnRemoteAudioStats(const bytertc::RemoteAudioStats& stats) {
    ::SendMessage(m_desktop, WM_NOTIFY_REMOTE_AUDIO_STATS, (WPARAM)&stats, 0);
}

void EngineWrapper::OnWarning(int warn) {

}

void EngineWrapper::OnError(int err) {
    // Users are kicked off the line
    if (err == -1004) {
        ::SendMessage(m_desktop, WM_NOTIFY_KICK_OFF, 0, 0);
    }
    else if (err == bytertc::BRERR_INVALID_TOKEN) {
        ::PostMessage(m_desktop, WM_NOTIFY_INVALID_TOKEN, 0, 0);
    }
}

void EngineWrapper::SetVideoDefaultProfile() {
    bytertc::VideoSolution vs;
    vs.width = 640;
    vs.height = 480;
    vs.fps = 15;
    vs.max_send_kbps = 600;

    if (m_pEngine) {
        m_pEngine->SetVideoEncoderConfig(&vs, 1);
    }
}

void EngineWrapper::setVideoProfiles(const bytertc::VideoSolution* solutions, int solution_num) {
    if (m_pEngine) {
        m_pEngine->SetVideoEncoderConfig(solutions, solution_num);
    }
}

std::vector<RtcDevice> EngineWrapper::GetAudioInputDevices()
{
    if (!m_pEngine) {
        return std::vector<RtcDevice>();
    }
    std::string strSelectedDeviceId;
    char szName[512], szId[512];
    int devIdx = 0;

    // enum audio recording devices
    m_lstAudioCaptureDevices.clear();

    bytertc::IAudioDeviceManager *pAudioDeviceManager = m_pEngine->GetAudioDeviceManager();
    if (pAudioDeviceManager) {
        bytertc::IAudioDeviceCollection* pAudioRecordCollection = pAudioDeviceManager->EnumerateRecordingDevices();
        if (pAudioRecordCollection) {
            memset(szName, 0, sizeof(szName));
            memset(szId, 0, sizeof(szId));
            devIdx = 0;

            // get selected device id
            pAudioDeviceManager->GetRecordingDeviceInfo(szId, szName);
            strSelectedDeviceId = szId;

            int nAudioRecNum = pAudioRecordCollection->GetCount();
            if (nAudioRecNum > 0) {
                m_nSelectedAudioCaptureDev = 0;
                for (int i = 0; i < nAudioRecNum; ++i) {
                    memset(szName, 0, sizeof(szName));
                    memset(szId, 0, sizeof(szId));

                    if (pAudioRecordCollection->GetDevice(i, szName, szId) == 0) {
                        if (strSelectedDeviceId == szId) {
                            m_nSelectedAudioCaptureDev = i;
                        }

                        RtcDevice device;
                        device.type = RtcDeviceTypeAudioRecord;
                        device.name = szName;
                        device.guid = szId;

                        m_lstAudioCaptureDevices.push_back(device);
                    }
                }
            }

            pAudioRecordCollection->Release();
            pAudioRecordCollection = nullptr;
        }
    }
    return m_lstAudioCaptureDevices;
}

void EngineWrapper::SetAudioInputDevice(int index)
{
    if (m_lstAudioCaptureDevices.size() > 0) {
        bytertc::IAudioDeviceManager* pAudioDeviceManager = m_pEngine->GetAudioDeviceManager();
        if (pAudioDeviceManager) {
            pAudioDeviceManager->SetRecordingDevice(m_lstAudioCaptureDevices[index].guid.c_str());
        }
    }
}

void EngineWrapper::GetAudioInputDevice(char* guid) {
    if (m_lstAudioCaptureDevices.size() > 0) {
        bytertc::IAudioDeviceManager* pAudioDeviceManager = m_pEngine->GetAudioDeviceManager();
        if (pAudioDeviceManager) {
            pAudioDeviceManager->GetRecordingDevice(guid);
        }
    }
}

std::vector<RtcDevice> EngineWrapper::GetAudioOutputDevices() {
    std::string strSelectedDeviceId;
    char szName[512], szId[512];
    int devIdx = 0;

    // enum playout devices
    m_lstPlayoutDevices.clear();
    if(!m_pEngine) return m_lstPlayoutDevices;

    bytertc::IAudioDeviceManager *pAudioDeviceManager = m_pEngine->GetAudioDeviceManager();
    if (pAudioDeviceManager) {
        bytertc::IAudioDeviceCollection* pAudioPlayoutCollection = pAudioDeviceManager->EnumeratePlaybackDevices();
        if (pAudioPlayoutCollection) {
            memset(szName, 0, sizeof(szName));
            memset(szId, 0, sizeof(szId));
            devIdx = 0;

            // get selected device id
            pAudioDeviceManager->GetPlaybackDeviceInfo(szId, szName);
            strSelectedDeviceId = szId;

            int nAudioRecNum = pAudioPlayoutCollection->GetCount();
            if (nAudioRecNum > 0) {
                m_nSelectedPlayoutDev = 0;
                for (int i = 0; i < nAudioRecNum; ++i) {
                    memset(szName, 0, sizeof(szName));
                    memset(szId, 0, sizeof(szId));

                    if (pAudioPlayoutCollection->GetDevice(i, szName, szId) == 0) {
                        if (strSelectedDeviceId == szId) {
                            m_nSelectedPlayoutDev = i;
                        }

                        RtcDevice device;
                        device.type = RtcDeviceTypeAudioPlayout;
                        device.name = szName;
                        device.guid = szId;

                        m_lstPlayoutDevices.push_back(device);
                    }
                }
            }

            pAudioPlayoutCollection->Release();
            pAudioPlayoutCollection = nullptr;
        }
    }
    return m_lstPlayoutDevices;
}

void EngineWrapper::SetAudioOutputDevice(int index) {
    if (m_lstPlayoutDevices.size() > 0) {
        bytertc::IAudioDeviceManager* pAudioDeviceManager = m_pEngine->GetAudioDeviceManager();
        if (pAudioDeviceManager) {
            pAudioDeviceManager->SetPlaybackDevice(m_lstPlayoutDevices[index].guid.c_str());
        }
    }
}

bool EngineWrapper::AudioRecordDevicesTest() {
    // enum playout devices
    if (!m_pEngine) return false;

    bool res = false;
    char szName[512];
    char szId[512];
    bytertc::IAudioDeviceManager *pAudioDeviceManager = m_pEngine->GetAudioDeviceManager();
    if (pAudioDeviceManager) {
        bytertc::IAudioDeviceCollection* pAudioRecordCollection = pAudioDeviceManager->EnumerateRecordingDevices();
        if (pAudioRecordCollection) {
            memset(szName, 0, sizeof(szName));
            memset(szId, 0, sizeof(szId));

            int nAudioRecNum = pAudioRecordCollection->GetCount();
            if (nAudioRecNum > 0) {
                m_nSelectedPlayoutDev = 0;
                for (int i = 0; i < nAudioRecNum; ++i) {
                    memset(szName, 0, sizeof(szName));

                    if (pAudioRecordCollection->GetDevice(i, szName, szId) == 0) {
                        auto code = pAudioDeviceManager->InitRecordingDeviceForTest(szId);
                        if (code == 0 ) {
                            res = true;
                        }
                    }
                }
            }

            pAudioRecordCollection->Release();
            pAudioRecordCollection = nullptr;
        }
    }

    return res;
}

void EngineWrapper::GetAudioOutputDevice(char* guid) {
    if (m_lstPlayoutDevices.size() > 0) {
        bytertc::IAudioDeviceManager* pAudioDeviceManager = m_pEngine->GetAudioDeviceManager();
        if (pAudioDeviceManager) {
            pAudioDeviceManager->GetPlaybackDevice(guid);
        }
    }
}

std::vector<RtcDevice> EngineWrapper::GetVideoCaptureDevices() {
    std::string strSelectedDeviceId;
    char szName[512], szId[512];
    int devIdx = 0;

    // enum video capture devices
    m_lstVideoCaptureDevices.clear();

    if(!m_pEngine) return m_lstVideoCaptureDevices;

    bytertc::IVideoDeviceManager *pVideoDeviceManager = m_pEngine->GetVideoDeviceManager();
    if (pVideoDeviceManager) {
        bytertc::IVideoDeviceCollection* pVideoRecordCollection = pVideoDeviceManager->EnumerateVideoDevices();
        if (pVideoRecordCollection) {
            memset(szName, 0, sizeof(szName));
            memset(szId, 0, sizeof(szId));
            devIdx = 0;

            // get selected device id
            pVideoDeviceManager->GetDevice(szId);
            strSelectedDeviceId = szId;

            int nVideoCaptureNum = pVideoRecordCollection->GetCount();
            if (nVideoCaptureNum > 0) {
                m_nSelectedVideoCaptureDev = 0;
                for (int i = 0; i < nVideoCaptureNum; ++i) {
                    memset(szName, 0, sizeof(szName));
                    memset(szId, 0, sizeof(szId));

                    if (pVideoRecordCollection->GetDevice(i, szName, szId) == 0) {
                        if (strSelectedDeviceId == szId) {
                            m_nSelectedVideoCaptureDev = i;
                        }

                        RtcDevice device;
                        device.type = RtcDeviceTypeVideoCapture;
                        device.name = szName;
                        device.guid = szId;

                        m_lstVideoCaptureDevices.push_back(device);
                    }
                }
            }

            pVideoRecordCollection->Release();
            pVideoRecordCollection = nullptr;
        }

        pVideoDeviceManager->Release();
        pVideoDeviceManager = nullptr;
    }
    return m_lstVideoCaptureDevices;
}

void EngineWrapper::SetVideoCaptureDevice(int index) {
    if (m_lstVideoCaptureDevices.size() > 0) {
        bytertc::IVideoDeviceManager* pVideoDeviceManager = m_pEngine->GetVideoDeviceManager();
        if (pVideoDeviceManager) {
            pVideoDeviceManager->SetDevice(m_lstVideoCaptureDevices[index].guid.c_str());
        }
    }
}

void EngineWrapper::GetVideoCaptureDevice(char* guid) {
    if (m_lstVideoCaptureDevices.size() > 0) {
        bytertc::IVideoDeviceManager* pVideoDeviceManager = m_pEngine->GetVideoDeviceManager();
        if (pVideoDeviceManager) {
            pVideoDeviceManager->GetDevice(guid);
        }
    }
}

void EngineWrapper::OnAudioVolumeIndication(const bytertc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) {
    std::map<std::string, AudioVolumeInfo> audioVolumeMapInfos;
    for (int i = 0; i < speakerNumber; ++i) {
        std::string uid = speakers[i].uid;
        audioVolumeMapInfos[uid].uid = speakers[i].uid;
        audioVolumeMapInfos[uid].volume += speakers[i].volume;
    };

    std::vector<AudioVolumeInfo> audioVolumeInfos;
    for (const auto& info : audioVolumeMapInfos) {
        audioVolumeInfos.push_back(info.second);
    }

    int size = audioVolumeInfos.size();
    if (size > 9) { // the first nine maximum values
        std::sort(audioVolumeInfos.begin(), audioVolumeInfos.end(), [](const AudioVolumeInfo& left, const AudioVolumeInfo& right)->bool {
            return left.volume > right.volume;
        });

        size = 9;
    }

    ::SendMessage(m_desktop, WM_NOTIFY_AUDIO_VOLUME, (WPARAM)audioVolumeInfos.data(), (LPARAM)size);
}

void EngineWrapper::OnLeaveChannel(const bytertc::RtcStats& stats) {
    ::SendMessage(m_desktop, WM_NOTIFY_CHANNEL_LEAVE_SUCCEED, 0, 0);
}

void EngineWrapper::OnUserJoined(const char* uid, const char* team_id, const bytertc::RangeAudioMode send_mode, int elapsed) {
}

void EngineWrapper::OnUserOffline(const char* uid, bytertc::USER_OFFLINE_REASON_TYPE reason) {
    if (reason != bytertc::USER_OFFLINE_QUIT) return;

    ::SendMessage(m_desktop, WM_NOTIFY_USER_LEAVE_SUCCEED, (WPARAM)uid, 0);
}

void EngineWrapper::OnUserMuteAudio(const char* user_id, bytertc::MuteState mute_state) {
    ::SendMessage(m_desktop, WM_NOTIFY_ENABLE_AUDIO, (WPARAM)user_id, (LPARAM)(mute_state == bytertc::MuteState::kMuteStateOff));
}

void EngineWrapper::OnUserEnableLocalAudio(const char* uid, bool enabled) {
    ::SendMessage(m_desktop, WM_NOTIFY_ENABLE_AUDIO, (WPARAM)uid, (LPARAM)enabled);
}

void EngineWrapper::OnFirstLocalAudioFrame(bytertc::StreamIndex index) {
    if (bytertc::StreamIndex::kStreamIndexMain == index) {
        ::SendMessage(m_desktop, WM_LOCAL_AUDIO, 0, 0);
    }
}

void EngineWrapper::OnLogReport(const char* log_type, const char* log_content) {
    //::SendMessage(m_desktop, WM_LOG, (WPARAM)log_type, (LPARAM)log_content);
}

void EngineWrapper::OnStreamRemove(const bytertc::ByteStream& stream, bytertc::RtcStreamRemoveReason reason) {
    std::vector<RemoteStream> streams;
    RemoteStream r_stream;

    r_stream.user_id = stream.user_id;
    r_stream.is_screen = stream.is_screen;
    streams.push_back(r_stream);

    ::SendMessage(m_desktop, WM_NOTIFY_STREAMS_REMOVE, (WPARAM)streams.data(), 1);
}

void EngineWrapper::OnStreamAdd(const bytertc::ByteStream& stream) {
    std::vector<RemoteStream> streams;
    RemoteStream r_stream;

    r_stream.user_id = stream.user_id;
    r_stream.is_screen = stream.is_screen;
    streams.push_back(r_stream);

    ::SendMessage(m_desktop, WM_NOTIFY_STREAMS_ADD, (WPARAM)streams.data(), 1);
}

void EngineWrapper::OnStreamSubscribed(bytertc::SUBSCRIBE_STATE stateCode, const char* stream_id, const bytertc::SubscribeConfig& info) {

}

void EngineWrapper::OnStreamPublishSucceed(const char* user_id, bool is_screen) {

}

void EngineWrapper::OnAudioRouteChanged(int routing) {

}

void EngineWrapper::OnFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) {
    if (bytertc::StreamIndex::kStreamIndexMain == index) {
        ::SendMessage(m_desktop, WM_LOCAL_VIDEO, 0, 0);
    }
}

void EngineWrapper::OnFirstRemoteVideoFrameRendered(const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info) {
    if (key.stream_index == bytertc::StreamIndex::kStreamIndexMain) {
        ::SendMessage(m_desktop, WM_NOTIFY_REMOTE_FIRST_VIDEO, (WPARAM)key.user_id, 0);
    }
    else if (key.stream_index == bytertc::StreamIndex::kStreamIndexScreen) {
        ::SendMessage(m_desktop, WM_NOTIFY_REMOTE_SCREEN_FIRST_VIDEO, (WPARAM)key.user_id, 0);
    }
}

void EngineWrapper::OnUserMuteVideo(const char* uid, bytertc::MuteState mute) {
    ::SendMessage(m_desktop, WM_NOTIFY_MUTE_VIDEO, (WPARAM)uid, (LPARAM)(mute == bytertc::MuteState::kMuteStateOn));
}

void EngineWrapper::OnUserEnableLocalVideo(const char* uid, bool enabled) {
    ::SendMessage(m_desktop, WM_NOTIFY_ENABLE_VIDEO, (WPARAM)uid, (LPARAM)enabled);
}

void EngineWrapper::OnMediaDeviceNotification(const char* device_id, bytertc::MediaDeviceType device_type,
    bytertc::MediaDeviceNotification notification_type) {
    bool is_video_device = false;

    switch (device_type) {
    case bytertc::kAudioRecordingDevice:
        is_video_device = false;
        break;
    case bytertc::kVideoCaptureDevice:
        is_video_device = true;
        break;
    default:
        return;
    }

    switch (notification_type) {
    case bytertc::kMediaDeviceNotificationActive:
    case bytertc::kMediaDeviceNotificationUnplugged:
    case bytertc::kMediaDeviceNotificationNotPresent:
        break;
    default:
        return;
    }

    ::SendMessage(m_desktop, is_video_device ? WM_NOTIFY_VIDEO_DEVICE_EVENT :WM_NOTIFY_AUDIO_DEVICE_EVENT,
        (WPARAM)device_id,
        (LPARAM)notification_type);
}

void EngineWrapper::OnLocalVideoStateChanged(bytertc::StreamIndex index, bytertc::LocalVideoStreamState state, bytertc::LocalVideoStreamError error) {
    if (index == bytertc::StreamIndex::kStreamIndexMain) {
        ::SendMessage(m_desktop, WM_VIDEO_DEVICE_STATE_CHANGE,
            (WPARAM)state,
            (LPARAM)error);
    }
}

void EngineWrapper::OnLocalAudioStateChanged(bytertc::LocalAudioStreamState state, bytertc::LocalAudioStreamError error) {
    ::SendMessage(m_desktop, WM_AUDIO_DEVICE_STATE_CHANGE,
        (WPARAM)state,
        (LPARAM)error);
}
