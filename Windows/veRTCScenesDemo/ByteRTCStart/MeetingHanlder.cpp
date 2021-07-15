//
//  BDRateWnd.h
//
//  Copyright 2020. All rights reserved.
//
#include "BDMainContainerFrame.h"
#include "ByteMessage.h"

class PrivateFunction {
public:
    static PrivateFunction* CreateFunc(std::function<void()> func) {
        return new PrivateFunction(func);
    }

    void Release() {
        delete this;
    }

    void execute() {
        m_func();
    }

private:
    PrivateFunction(std::function<void()> func):m_func(func){}
    ~PrivateFunction(){}
    PrivateFunction& operator = (const PrivateFunction& other) = delete;

    std::function<void()> m_func;
};

void SendFunction(HWND handler, std::function<void()>&& func) {
    ::SendMessage(handler, WM_NOTIFY_FUNCTION_EXECUTE, (WPARAM)PrivateFunction::CreateFunc(func), 0);
}

void PostFunction(HWND handler, std::function<void()>&& func) {
    ::PostMessage(handler, WM_NOTIFY_FUNCTION_EXECUTE, (WPARAM)PrivateFunction::CreateFunc(func), 0);
}

LRESULT BDMainContainerFrame::OnFunctionExec(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    auto func = (PrivateFunction*)wParam;
    if (func) {
        func->execute();
        func->Release();
        func = nullptr;
    }

    return 0;
}

void BDMainContainerFrame::onUserMicStateChange(const std::string& userId, bool on) {
    auto func = [this, &userId, &on]() {
        auto pos = std::find_if(m_users.begin(), m_users.end(), [&userId](const UserAttr& ua)->bool {
            return ua.m_user_id == userId;
        });

        if (pos != m_users.end()) {
            pos->m_bAudio = on;
            UserLayoutFresh();
        }
    };

    ::SendFunction(m_hWnd, func);
}

void BDMainContainerFrame::onUserCameraStateChange(const std::string& userId, bool on) {
    auto func = [this, &userId, &on]() {
        auto pos = std::find_if(m_users.begin(), m_users.end(), [&userId](const UserAttr& ua)->bool {
            return ua.m_user_id == userId;
        });

        if (pos != m_users.end()) {
            pos->m_bVideo = on;
            if (pos->m_view) {
                pos->m_view->MuteVideo(!on);
            }

            UserLayoutFresh();
        }
    };

    Sleep(200);
    ::SendFunction(m_hWnd, func);
}

void BDMainContainerFrame::HostMuteRemoteUserAudio(const UserAttr& user) {
    if (user.m_bAudio) {
        MeetingManager::GetInstance()->muteUserMic(user.m_user_id, [](int code) {
            assert(code == 200);
        });
    }
    else {
        MeetingManager::GetInstance()->askUserMacOn(user.m_user_id, [this, user](int code) {
            if (code == 200) {
                BDString inf;
                inf.Format(L"请求%s打开麦克风已发送", user.m_name);
                ShowBubbleTip(inf);
            }
            else {
                // Abnormal prompt
                BDString inf;
                inf.Format(L"请求%s打开麦克风失败，错误码：%d", user.m_name, code);
                ShowBubbleTip(inf);
            }
        });
    }
}

void BDMainContainerFrame::onMuteUser(const std::string& userId) {
    ::SendFunction(m_hWnd, [this]() {
        if (!EngineWrapper::GetInstance()->m_bMuteAudio) {
            BDString inf;
            inf.Format(L"你已被主持人静音");
            ShowBubbleTip(inf);
        }

        EngineWrapper::GetInstance()->m_bMuteAudio = true;
        if (m_controlWnd) {
            m_controlWnd->UpdateAudio();
        }
    });
}

//  Hand over the host
void BDMainContainerFrame::HostTransferHost(const UserAttr& user) {
    RECT rc;
    ::GetWindowRect(m_hWnd, &rc);
    m_messageWnd.MoveWindow(rc.left + m_width / 2 - MESSAGE_WND_WIDTH / 2,
        rc.top + m_height / 2 - MESSAGE_WND_HEIGHT / 2,
        MESSAGE_WND_WIDTH,
        MESSAGE_WND_HEIGHT);

    m_messageWnd.SetMessage(L"是否将主持人移交给：" + user.m_name);
    m_messageWnd.SetMessageHander("确定", [this, user]() {
        m_messageWnd.ShowWindow(SW_HIDE);
        MeetingManager::GetInstance()->changeHost(user.m_user_id, [this](int code) {
            assert(code == 200);
            if (code != 200) {
                //Abnormal prompt
                BDString inf;
                inf.Format(L"移交主持人失败，请重试");
                ShowBubbleTip(inf);
            }
            else {
                BDString inf;
                inf.Format(L"移交主持人成功");
                ShowBubbleTip(inf);
            }
        });
    },
    "取消", [this]() {
        m_messageWnd.ShowWindow(SW_HIDE);
    });

    m_messageWnd.ShowWindow(SW_SHOW);
    m_messageWnd.BringWindowToTop();
}

void BDMainContainerFrame::onHostChange(const std::string& formerHostId, const std::string& hostId) {
    auto func = [this, &formerHostId, &hostId]() {
        auto formerHostPos = std::find_if(m_users.begin(), m_users.end(), [&formerHostId](const UserAttr& ua)->bool {
            return ua.m_isHost;
        });

        if (formerHostPos != m_users.end()) {
            formerHostPos->m_isHost = false;
            if (formerHostPos->m_view) {
                formerHostPos->m_view->SetHost(false);
            }
        }

        auto hostPos = std::find_if(m_users.begin(), m_users.end(), [&hostId](const UserAttr& ua)->bool {
            return ua.m_user_id == hostId;
        });

        if (hostPos != m_users.end()) {
            hostPos->m_isHost = true;
            if (hostPos->m_view) {
                hostPos->m_view->SetHost(true);
            }

            UserLayoutFresh();
        }

        if (hostId == m_sms.user_id) {
            BDString inf;
            inf.Format(L"您已经被指定为新的主持人！");
            ShowBubbleTip(inf);
        }
    };

    ::SendFunction(m_hWnd, func);
}

// New users join
void BDMainContainerFrame::onUserJoinMeeting(const User& userId) {
    auto func = [this, &userId]() {
        if (userId.uid == m_sms.user_id) { // self, return
            auto pos = std::find_if(m_users.begin(), m_users.end(), [](const UserAttr& ua)->bool {
                return ua.m_type == UserType::LOCAL_USER;
            });

            if (pos != m_users.end()) {
                pos->m_user_uniform_id = userId.user_uniform_id;
            }
            return;
        }

        auto pos = std::find_if(m_users.begin(), m_users.end(), [&userId](const UserAttr& ua)->bool {
            return ua.m_user_id == userId.uid;
        });

        if (pos != m_users.end()) {
            return;
        }

        UserAttr ua;
        ua.m_user_id = userId.uid;
        ua.m_user_uniform_id = userId.user_uniform_id;
        ua.m_name = rtcutil::ConvertUTF8ToBDString(userId.user_name);
        ua.m_type = UserType::REMOTE_USER;

        ua.timeOfJoining = userId.time_of_joining;
        ua.m_isHost = userId.is_host;
        ua.m_shared = userId.is_screen_shared;
        ua.m_bAudio = userId.is_mic_on;
        ua.m_bVideo = userId.is_camera_on;

        if (ua.m_isHost) {
            auto local = m_users.begin();
            local->m_isHost = false;
            if (local->m_view) {
                local->m_view->SetHost(false);
            }

            m_users.push_front(ua);
        }
        else {
            m_users.push_back(ua);
        }

        auto layout = m_view_style == SPEAKER_STYLE || m_view_style == LOCAL_SHARE_STYLE ? m_view_style : VIEW_UNKNOW_STYLE;
        if (userId.is_screen_shared && m_view_style != SPEAKER_STYLE) {
            layout = SPEAKER_STYLE;
        }

        ::SendMessage(m_hWnd, WM_NOTIFY_VIEW_ATTACH, true, layout);
    };

    ::SendFunction(m_hWnd, func);
}

void BDMainContainerFrame::onUserLeaveMeeting(const std::string& userId) {
    auto func = [this, &userId]() {
        if (userId == m_sms.user_id) {
            return;
        }

        auto pos = std::find_if(m_users.begin(), m_users.end(), [&userId](const UserAttr& ua)->bool {
            return ua.m_user_id == userId;
        });

        if (pos != m_users.end()) {
            FreeVideoView(pos->m_view);
            pos->m_view = nullptr;

            FreeVideoView(pos->m_screen_view);
            pos->m_screen_view = nullptr;

            bool shared = pos->m_shared;
            m_users.erase(pos);

            ::SendMessage(m_hWnd, WM_NOTIFY_VIEW_ATTACH, true,
                !shared && (m_view_style == SPEAKER_STYLE || m_view_style == LOCAL_SHARE_STYLE) ? m_view_style : VIEW_UNKNOW_STYLE);
        }
    };

    ::SendFunction(m_hWnd, func);
}

void BDMainContainerFrame::JoinMeeting(const std::string& room_id, const std::string& user_name, const std::string& user_id) {
    MeetingManager::GetInstance()->joinMeeting(user_name,
        user_id,
        room_id,
        !EngineWrapper::GetInstance()->m_bMuteAudio,
        !EngineWrapper::GetInstance()->m_bMuteVideo,
        std::bind(&BDMainContainerFrame::onJoinMeetingsuccessfully, this, std::placeholders::_1, std::placeholders::_2));
}

void BDMainContainerFrame::onJoinMeetingsuccessfully(int code, const std::string& token) {
    if (code == 200) {
        ::SendMessage(m_hWnd, WM_NOTIFY_JOIN_OK, (WPARAM)token.c_str(), 0);

        MeetingManager::GetInstance()->getMeetingParticipantsInfo([this](int code, const std::list<User>& users) {
            if (code == 200) {
                for (auto& user : users) {
                    onUserJoinMeeting(user);
                }
            }
            else {
                // Abnormal prompt
                BDString inf;
                inf.Format(L"获取参会者信息错误，错误码：%d", code);
                ShowBubbleTip(inf);
            }
        });

        MeetingManager::GetInstance()->getMeetingInfo([this](int code, const Room& roomInfo) {
            auto func = [this, code, roomInfo]() {
                if (code == 200) {
                    if (roomInfo.is_recording) {
                        if (m_controlWnd) {
                            m_controlWnd->ResetRecordingState(true);
                        }
                        m_topbarWnd.RecordShow(true);
                    }

                    // Time calibration
                    m_topbarWnd.TimeSynchronization(roomInfo.meeting_start_time, roomInfo.now);
                }
                else {
                    // Abnormal prompt
                    BDString inf;
                    inf.Format(L"获取 room 信息错误，错误码：%d", code);
                    ShowBubbleTip(inf);
                }
            };

            ::SendFunction(m_hWnd, func);
        });
    }
    else if (code == 406) {
        // Abnormal prompt
        BDString inf;
        inf.Format(L"会议房间已满员");
        ShowBubbleTip(inf);

        m_loginWnd.ResetLogin();
    }
    else if (code == 702) {
        BDString inf;
        inf.Format(L"服务端Token生成失败，请重试");
        ShowBubbleTip(inf);

        m_loginWnd.ResetLogin();
    }
    else {
        //Abnormal prompt
        BDString inf;
        inf.Format(L"加入会议失败，错误码：%d", code);
        ShowBubbleTip(inf);

        m_loginWnd.ResetLogin();
    }
}

void BDMainContainerFrame::StartScreenShare(const SnapshotAttr& shared, const SnapshotAttr& excluded) {
    MeetingManager::GetInstance()->startScreenShare([this, shared, excluded](int code) {
        auto func = [this, shared, excluded, code]() {
            if (code != 200) {
                BDString inf;
                inf.Format(L"屏幕共享失败");
                ShowBubbleTip(inf);
            } else if (code == 412) {

            } else {
                DestroyControl();
                if (!m_controlWnd) {
                    ReCreateControl(m_hWnd, true);
                }

                switch (shared.m_type) {
                case SnapshotAttr::SNAPSHOT_SCREEN: {
                    std::vector<HWND> excluded;
                    if (m_controlWnd) {
                        excluded.push_back(m_controlWnd->m_hWnd);
                        excluded.push_back(m_controlWnd->GetTipHandler());
                    }
                    excluded.push_back(m_bubbleTipWnd.m_hWnd);
                    excluded.push_back(m_leaveWnd.m_hWnd);
                    EngineWrapper::GetInstance()->startScreenCapture(shared.source_id, excluded);
                    break;
                }
                case SnapshotAttr::SNAPSHOT_WINDOW:
                    EngineWrapper::GetInstance()->startScreenCaptureByWindowId((HWND)shared.source_id);
                    break;
                default:
                    break;
                }
            }
        };

        ::SendFunction(m_hWnd, func);
    });
}

void BDMainContainerFrame::StopScreenShare() {
    assert(m_view_style == LOCAL_SHARE_STYLE);
    MeetingManager::GetInstance()->stopScreenShare([this](int code) {
        auto func = [this, code]() {
            if (code != 200) {
                BDString inf;
                inf.Format(L"停止共享屏幕失败");
                ShowBubbleTip(inf);
            }

            ShowWindow(SW_SHOW);
            if (m_controlWnd) {
                m_controlWnd->ResetScreenSharedState(false);
            }
            EngineWrapper::GetInstance()->stopScreenCapture();
        };

        ::SendFunction(m_hWnd, func);
    });
}

void BDMainContainerFrame::onScreenShareStateChanged(const std::string& userId, bool state) {
    auto func = [this, &userId, &state]() {
        auto pos = std::find_if(m_users.begin(), m_users.end(), [&](const UserAttr& userAttr)->bool {
            return userAttr.m_user_id == userId;
        });

        if (pos == m_users.end()) {
            return;
        }

        pos->m_shared = state;
        m_userWnd.UpdateUser(*pos);

        if (pos->m_view) {
            pos->m_view->SetShare(state);
        }

        if (state) {
            if (!pos->m_screen_view) {
                pos->m_screen_view = AllocVideoView(*pos, true);
            }

            if (m_remoteStream.user_id == pos->m_user_id) {
                pos->m_screen_view->OnStreamAdd();
            }

            m_snapshotWnd.ShowWindow(SW_HIDE);
        }
        else if(pos->m_screen_view) {
            FreeVideoView(pos->m_screen_view);
            pos->m_screen_view = nullptr;
        }

        UserType type = pos->m_type;
        if (state) {
            if (type == UserType::LOCAL_USER) {
                ShowWindow(SW_HIDE);
            }
            ::SendMessage(m_hWnd, WM_NOTIFY_VIEEW_RELAYOUT, false, type == UserType::LOCAL_USER ? LOCAL_SHARE_STYLE : SPEAKER_STYLE);
        }
        else {
            if (m_controlWnd) {
                m_controlWnd->ResetScreenSharedState(false);
            }
            ::SendMessage(m_hWnd, WM_NOTIFY_VIEEW_RELAYOUT, false, VIEW_UNKNOW_STYLE);
        }
    };

    ::SendFunction(m_hWnd, func);
}

LRESULT BDMainContainerFrame::onStartShareScreen(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    if (m_view_style == LOCAL_SHARE_STYLE) {
        StopScreenShare();
    } else if (m_view_style == SPEAKER_STYLE) {
        //Abnormal prompt
        BDString inf;
        inf.Format(L"屏幕共享发起失败，请提示前一位参会者结束共享");
        ShowBubbleTip(inf);
    }
    else if (m_snapshotWnd.IsWindowVisible()) {
        assert(false); // It should not be enforced
        m_snapshotWnd.ShowWindow(SW_HIDE);
        m_main_mask.ShowWindow(SW_HIDE);
        if (m_controlWnd) {
            m_controlWnd->ResetScreenSharedState(false);
        }
    } else if (!m_snapshotWnd.IsWindowVisible()) {
        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);
        m_main_mask.MoveWindow(rc.left + 10,
            rc.top,
            rc.right - rc.left - 20,
            rc.bottom - rc.top - 10);
        m_main_mask.ShowWindow(SW_SHOW);

        m_snapshotWnd.MoveWindow(rc.left + m_width / 2 - SNAPSHOT_WND_WIDTH / 2,
            rc.bottom - SNAPSHOT_WND_HEIGHT - 96,
            SNAPSHOT_WND_WIDTH,
            SNAPSHOT_WND_HEIGHT);
        m_snapshotWnd.ShowWindow(SW_SHOW);

        m_snapshotWnd.SetOnSharedClick(std::bind(&BDMainContainerFrame::StartScreenShare, this, std::placeholders::_1, std::placeholders::_2));
    }

    return 0;
}

LRESULT BDMainContainerFrame::onCloseShareScreen(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    if (m_snapshotWnd.IsWindowVisible()) {
        m_snapshotWnd.ShowWindow(SW_HIDE);
        m_main_mask.ShowWindow(SW_HIDE);
        if (m_controlWnd) {
            m_controlWnd->ResetScreenSharedState(false);
        }
    }
    return 0;
}

void BDMainContainerFrame::onStartMeetingRecord() {
    ::SendFunction(m_hWnd, [this]() {
        if (m_controlWnd) {
            m_controlWnd->ResetRecordingState(true);
        }
        m_topbarWnd.RecordShow(true);
    });
}

void BDMainContainerFrame::MuteAllRemoteUsers() {
    auto pos = m_users.begin();
    if (pos->m_isHost && pos->m_type == UserType::LOCAL_USER) {
        MeetingManager::GetInstance()->muteAllUserMic([this](int code) {
            if (code != 200) {
                // Prompt error
                BDString inf;
                inf.Format(L"全体静音失败，请重试");
                ShowBubbleTip(inf);
            }
            else {
                BDString inf;
                inf.Format(L"全体静音已发送");
                ShowBubbleTip(inf);

                onMuteAllMic();
            }
        });
    }
}

void BDMainContainerFrame::onMuteAllMic() {
    auto func = [this]() {
        for (auto& user : m_users) {
            if (!user.m_isHost) {
                user.m_bAudio = false;
            }
        }

        UserLayoutFresh();

        if (m_users.begin()->m_type == UserType::REMOTE_USER) {
            onMuteUser("");
        }
    };

    ::SendFunction(m_hWnd, func);
}

void BDMainContainerFrame::onAskingMicOn(const std::string& userId) {
    auto func = [this]() {
        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);
        m_messageWnd.MoveWindow(rc.left + m_width / 2 - MESSAGE_WND_WIDTH / 2,
            rc.top + m_height / 2 - MESSAGE_WND_HEIGHT / 2,
            MESSAGE_WND_WIDTH,
            MESSAGE_WND_HEIGHT);

        m_messageWnd.SetMessage(L"主持人邀请你打开麦克风");
        m_messageWnd.SetMessageHander("确定", [this]() {
                EngineWrapper::GetInstance()->m_bMuteAudio = false;
                if (m_controlWnd) {
                    m_controlWnd->UpdateAudio();
                }
                m_messageWnd.ShowWindow(SW_HIDE);
            },
            "取消", [this]() {
                m_messageWnd.ShowWindow(SW_HIDE);
        });

        m_messageWnd.ShowWindow(SW_SHOW);
        m_messageWnd.BringWindowToTop();
    };

    ::SendFunction(m_hWnd, func);
}

void BDMainContainerFrame::onAskingCameraOn(const std::string& userId) {
    auto func = [this]() {
        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);
        m_messageWnd.MoveWindow(rc.left + m_width / 2 - MESSAGE_WND_WIDTH / 2,
            rc.top + m_height / 2 - MESSAGE_WND_HEIGHT / 2,
            MESSAGE_WND_WIDTH,
            MESSAGE_WND_HEIGHT);

        m_messageWnd.SetMessage(L"主持人请求您打开摄像头");
        m_messageWnd.SetMessageHander("确定", [this]() {
                EngineWrapper::GetInstance()->m_bMuteVideo = false;
                if (m_controlWnd) {
                    m_controlWnd->UpdateVideo();
                }
                m_messageWnd.ShowWindow(SW_HIDE);
            },
            "取消", [this]() {
                m_messageWnd.ShowWindow(SW_HIDE);
        });

        m_messageWnd.ShowWindow(SW_SHOW);
        m_messageWnd.BringWindowToTop();
    };

    ::SendFunction(m_hWnd, func);
}

// Network reconnection or socket connected event
void BDMainContainerFrame::onWebsocketConnected() {
    ::SendFunction(m_hWnd, [this]() {
        KillTimer(2);
        m_websocket_connection = true;

        if (m_bubbleTipWnd.IsWindowVisible()) {
            m_bubbleTipWnd.ShowWindow(SW_HIDE);
        }
        m_loginWnd.OnConnection();
        CheckUpdateApp(IsWindowVisible());
    });

    if (m_room_id.empty()) {
        // get app id
        MeetingManager::GetInstance()->getAppId([this](int code, const std::string& res) {
            if (code == 200) {
                EngineWrapper::GetInstance()->destroyEngine();
                EngineWrapper::GetInstance()->createEngine(res);
                EngineWrapper::GetInstance()->RegisterVideoFrameObserver(this);
                m_login_local_view.SetupLocal(true);
                EngineWrapper::GetInstance()->preview();
                m_topbarWnd.ShowVersionInfo();
                m_loginWnd.OnEngineCreate();
                m_settingWnd.OnEngineCreate();
            }
            else {
                // Prompt error
                BDString inf;
                inf.Format(L"获取 appid 失败，错误码：%d", code);
                ShowBubbleTip(inf);
            }
        });

        MeetingManager::GetInstance()->getHistoryMeetingRecord([this](int code, const std::list<RecordInfo>& records) {
            if (code == 200) {
                m_settingWnd.SetRecordList(records);
            }
            else {
                BDString inf;
                inf.Format(L"录制会议历史记录失败，错误码: %d", code);
                ShowBubbleTip(inf);
            }
        });
    }
    else {
        RejoinMeeting();
    }
}

void BDMainContainerFrame::RejoinMeeting() { // when rejoin, There will be no stream add event, search from m_remoteStreams
    // User reconnection
    MeetingManager::GetInstance()->userReconnect([this](int code) {
        if (code == 200) {
            auto func = [this]() {
                for (auto it = m_users.begin(); it != m_users.end(); it++) {
                    FreeVideoView(it->m_view);
                    FreeVideoView(it->m_screen_view);
                }

                m_users.clear();
                m_userWnd.Clear();

                // self join
                UserAttr usLocal;
                usLocal.m_user_id = m_sms.user_id;
                usLocal.m_name = m_sms.user_name;
                usLocal.m_bAudio = !EngineWrapper::GetInstance()->m_bMuteAudio;
                usLocal.m_bVideo = !EngineWrapper::GetInstance()->m_bMuteVideo;
                usLocal.m_isHost = true;
                usLocal.m_type = UserType::LOCAL_USER;
                usLocal.m_view = AllocVideoView(usLocal, false);
                usLocal.m_view->SetupLocal(true);

                m_users.push_back(usLocal);
                UserLayoutFresh();

                ::SendMessage(m_hWnd, WM_NOTIFY_VIEEW_RELAYOUT, false, m_view_style == LOCAL_SHARE_STYLE ? LOCAL_SHARE_STYLE : VIEW_UNKNOW_STYLE);

                MeetingManager::GetInstance()->getMeetingParticipantsInfo([this](int code, const std::list<User>& users) {
                    if (code == 200) {
                        for (auto& user : users) {
                            onUserJoinMeeting(user);
                        }
                    }
                    else {
                        //Abnormal prompt
                        BDString inf;
                        inf.Format(L"获取参会者信息错误，错误码：%d", code);
                        ShowBubbleTip(inf);
                    }
                });

                MeetingManager::GetInstance()->getMeetingInfo([this](int code, const Room& roomInfo) {
                    auto func = [this, code, roomInfo]() {
                        if (code == 200) {
                            if (roomInfo.is_recording) {
                                if (m_controlWnd) {
                                    m_controlWnd->ResetRecordingState(true);
                                }
                                m_topbarWnd.RecordShow(true);
                            }
                        }
                        else {
                            //Abnormal prompt
                            BDString inf;
                            inf.Format(L"获取 room 信息错误，错误码：%d", code);
                            ShowBubbleTip(inf);
                        }
                    };

                    ::SendFunction(m_hWnd, func);
                });

                MeetingManager::GetInstance()->toggleCameraState(!EngineWrapper::GetInstance()->m_bMuteVideo, [](int code) {
                    int res = code;
                });

                MeetingManager::GetInstance()->toggleMicState(!EngineWrapper::GetInstance()->m_bMuteAudio, [](int code) {
                    int res = code;
                });
            };

            ::SendFunction(m_hWnd, func);
        }
        else if (code >= 400 && code < 500) {
            auto func = [this]() {
                ShowBubbleTip("网络链接已断开，请检查设置");

                if (m_view_style == LOCAL_SHARE_STYLE) {
                    StopScreenShare();
                }
                EngineWrapper::GetInstance()->logout();
                ::SendMessage(this->m_hWnd, WM_NOTIFY_LEAVE_SUCCEED, USER_OFFLINE_NORMAL, 0);
            };

            ::SendFunction(m_hWnd, func);
        }
    });
}

// Notify users of network outage events
void BDMainContainerFrame::onWebsocketConnecting() {
    ::SendFunction(m_hWnd, [this]() {
        ShowBubbleTip("网络链接已断开，请检查设置", false);
        m_loginWnd.OnDisconnection();
        if (m_websocket_connection) {
            SetTimer(2, 60 * 1000);
        }

        m_websocket_connection = false;
    });
}

void BDMainContainerFrame::Logout(bool silence) {
    if (!m_room_id.empty()) {
        if (m_view_style == LOCAL_SHARE_STYLE) {
            StopScreenShare();
        }

        EngineWrapper::GetInstance()->logout();
        ::SendMessage(this->m_hWnd, WM_NOTIFY_LEAVE_SUCCEED, USER_OFFLINE_NORMAL, silence);
        Invalidate();
    }
}

// Receive the notice from the meeting control system that the meeting is over
void BDMainContainerFrame::onMeetingClose() {
    auto func = [this]() {
        Logout(false);
    };

    ::SendFunction(m_hWnd, func);
}

// The moderator concluded the meeting
LRESULT BDMainContainerFrame::OnMeetingEnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    m_main_mask.ShowWindow(SW_HIDE);

    MeetingManager::GetInstance()->closeMeeting([this](int code) {
        if (code != 200) {
            ShowBubbleTip("会议结束失败");
        }
    });

    Logout(false);
    return 0;
}

// The participant left the meeting
LRESULT BDMainContainerFrame::OnMeetingLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    m_main_mask.ShowWindow(SW_HIDE);

    MeetingManager::GetInstance()->leaveMeeting([this](int code) {
        assert(code == 200);
    });

    Logout(false);
    return 0;
}

// Cancel leave
LRESULT BDMainContainerFrame::OnMeetingCancel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    m_main_mask.ShowWindow(SW_HIDE);
    return 0;
}

// When the window is closed
void BDMainContainerFrame::OnClose() {
    if (m_room_id.empty()) {
        PostQuitMessage(0);
        return;
    }

    BOOL res = false;
    OnLeaveClick(0, 0, 0, res);
}

void BDMainContainerFrame::onUserKickedOff() {
    auto func = [this](){
        if (m_view_style == LOCAL_SHARE_STYLE) {
            StopScreenShare();
        }
        EngineWrapper::GetInstance()->logout();
        ::SendMessage(this->m_hWnd, WM_NOTIFY_LEAVE_SUCCEED, USER_OFFLINE_REPEAT_LOGIN, 0);
        Invalidate();
    };

    ::SendFunction(m_hWnd, func);
}

LRESULT BDMainContainerFrame::onRecordVideo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    if (m_topbarWnd.IsVideoRecording()) {
        BDString inf;
        inf.Format(L"已经在录制中");
        ShowBubbleTip(inf);
        return 0;
    }

    std::vector<std::string> users;
    std::string screen_uid;

    if (!GetRecordUsersInfo(users, screen_uid)) {
        BDString inf;
        inf.Format(L"如需录制会议，请提醒主持人开启录制");
        ShowBubbleTip(inf);
    }
    else {
        MeetingManager::GetInstance()->startMeetingRecord(users, screen_uid, [this](int code) {
            auto func = [this, code]() {
                if (code == 200) {
                    if (m_controlWnd) {
                        m_controlWnd->ResetRecordingState(true);
                    }
                    m_topbarWnd.RecordShow(true);
                    BDString inf;
                    inf.Format(L"录制会议开始");
                    ShowBubbleTip(inf);
                }
                else {
                    BDString inf;
                    inf.Format(L"录制会议失败，错误码: %d", code);
                    ShowBubbleTip(inf);
                }
            };

            ::SendFunction(m_hWnd, func);
        });
    }

    return 0;
}

bool BDMainContainerFrame::GetRecordUsersInfo(std::vector<std::string>& users, std::string& screen_uid) {
    auto pos = std::find_if(m_users.begin(), m_users.end(), [](const UserAttr& user) {
        return user.m_isHost;
    });

    if (pos == m_users.end() || pos->m_type == UserType::REMOTE_USER) {
        return false;
    }

    for (auto& user : m_users) {
        if (user.m_view && user.m_view->IsWindowVisible()) {
            users.push_back(user.m_user_id);
        }
        else {
            break;
        }
    }

    if (m_view_style == SPEAKER_STYLE || m_view_style == LOCAL_SHARE_STYLE) {
        auto pos = std::find_if(m_users.begin(), m_users.end(), [](const UserAttr& user) {
            return user.m_shared;
        });

        if (pos != m_users.end()) {
            screen_uid = pos->m_user_id;
        }
    }

    return true;
}
// Repeated optimization
void BDMainContainerFrame::UpdateRecordVideoLayout(std::function<void(int)> callback) {
    if (m_topbarWnd.IsVideoRecording()) {
        std::vector<std::string> users;
        std::string screen_uid;

        if (GetRecordUsersInfo(users, screen_uid)) {
            MeetingManager::GetInstance()->updateRecordLayout(users, screen_uid, [this, callback](int code) {
                ::SendFunction(m_hWnd, [callback, code]() {
                    callback(code);
                });
            });
        }
    }
}

bool BDMainContainerFrame::OnLocalScreenFrame(bytertc::IByteVideoFrame* videoFrame) {
    return true;
}

bool BDMainContainerFrame::OnLocalVideoFrame(bytertc::IByteVideoFrame* videoFrame) {
    auto func = [this, videoFrame]() {
        for (auto& user : m_users) {
            if (user.m_type == LOCAL_USER && user.m_view
                && user.m_view->IsWindowVisible()) {
                ::PostMessage(user.m_view->m_hWnd, WM_NOTIFY_VIDEO, 0, 0);
                break;
            }
        }
    };

    ::PostFunction(m_hWnd, func);
    return true;
}

bool BDMainContainerFrame::OnRemoteScreenFrame(const char* roomid, const char* uid, bytertc::IByteVideoFrame* videoFrame) {
    auto func = [this, uid, videoFrame]() {
        for (auto& user : m_users) {
            if (user.m_user_id == uid && user.m_screen_view
                && user.m_screen_view->IsWindowVisible()) {
                ::PostMessage(user.m_screen_view->m_hWnd, WM_NOTIFY_VIDEO, 0, 0);
                break;
            }
        }
    };

    ::PostFunction(m_hWnd, func);
    return true;
}

bool BDMainContainerFrame::OnRemoteVideoFrame(const char* roomid, const char* uid, bytertc::IByteVideoFrame* videoFrame) {
    auto func = [this, uid, videoFrame]() {
        for (auto& user : m_users) {
            if (user.m_user_id == uid && user.m_view
                && user.m_view->IsWindowVisible()) {
                ::PostMessage(user.m_view->m_hWnd, WM_NOTIFY_VIDEO, 0, 0);
                break;
            }
        }
    };

    ::PostFunction(m_hWnd, func);
    return true;
}

void BDMainContainerFrame::onInvaildToken(int code) {
    auto func = [this]() {
        ShowWindow(SW_HIDE);
        Logout(true);
        m_loginWnd.ResetRoomEdit();
        EngineWrapper::GetInstance()->m_bMuteAudio = false;
        EngineWrapper::GetInstance()->m_bMuteVideo = false;
        m_loginWnd.Reset();
        ShowWindow(SW_HIDE);
    };

    ::PostFunction(m_hWnd, func);
}

void BDMainContainerFrame::CheckUpdateApp(bool show) {
    bool check = APPConfig::Instance()->IsCheckUpdate();
    if (show && !check && m_websocket_connection) {
        MeetingManager::GetInstance()->getAuditState(VERSION, [this](int code, const AuditState& state) {
            if (code != 200 || !state.state) return;
            ::SendFunction(m_hWnd, [this, code, state]() {
                APPConfig::Instance()->SetCheckUpdate();

                RECT rc;
                ::GetWindowRect(m_hWnd, &rc);
                m_main_mask.MoveWindow(rc.left + 10,
                    rc.top,
                    rc.right - rc.left - 20,
                    rc.bottom - rc.top - 10);
                m_main_mask.ShowWindow(SW_SHOW);

                m_main_mask.ShowWindow(SW_SHOW);
                m_messageWnd.SetMessage(L"应用有更新，立刻下载最新版本？");
                m_messageWnd.SetMessageHander("确定", [this, state]() {
                        m_messageWnd.ShowWindow(SW_HIDE);
                        m_main_mask.ShowWindow(SW_HIDE);

                        BDString address = rtcutil::ConvertUTF8ToBDString(state.url);
                        ShellExecute(0, L"open", address, L"", L"", 0);
                    },
                    "取消", [this]() {
                        m_messageWnd.ShowWindow(SW_HIDE);
                        m_main_mask.ShowWindow(SW_HIDE);
                });

                m_messageWnd.MoveWindow(rc.left + m_width / 2 - MESSAGE_WND_WIDTH / 2,
                    rc.top + m_height / 2 - MESSAGE_WND_HEIGHT / 2,
                    MESSAGE_WND_WIDTH,
                    MESSAGE_WND_HEIGHT);
                m_messageWnd.ShowWindow(SW_SHOW);
            });
        });
    }
    Invalidate();
}