//
//  BDControlWnd.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once

#include "resource.h"
#include "BDWinApp.h"
#include "BDWnd.h"
#include "BDCrack.h"
#include "BDGDI.h"
#include "BDCtrl.h"
#include "EngineWrapper.h"
#include "ByteMessage.h"
#include "BDButton.h"
#include "BDTipsWnd.h"

const int ICON_SQUARE = 36;
const double COUNT = 7.5;

class BDControlWnd : public BDWndImpl<BDControlWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDControlWnd")
    BDControlWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDControlWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_NCHITTEST(OnNcHitTest)
        MSG_WM_DESTROY(OnDestroy)
        COMMAND_ID_HANDLER(DUID_MUTE_AUDIO, onMuteAudio)
        COMMAND_ID_HANDLER(DUID_MUTE_VIDEO, onMuteVideo)
        COMMAND_ID_HANDLER(DUID_SHARE_SCREEN, onShareScreen)
        COMMAND_ID_HANDLER(DUID_VIDEO_RECORDING, onRecordVideo)
        COMMAND_ID_HANDLER(DUID_SHOW_USER, onShowUser)
        COMMAND_ID_HANDLER(DUID_SHOW_SETTING, onShowSetting)
        COMMAND_ID_HANDLER(DUID_LEAVE, onLeave)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        m_blueBk = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        m_grayPen = CreatePen(PS_SOLID, 1, RGB(0x4E, 0x59, 0x69));
        m_nameFont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");

        BDRect r(0, 0, 36, 36);
        m_muteAudio.Create(m_hWnd, r, BDHMenu(DUID_MUTE_AUDIO), L"MA", WS_CHILD | WS_VISIBLE);
        m_muteAudio.SetNormal(IDB_VOICE);
        m_muteAudio.SetHover(IDB_VOICE_HOVER);
        m_muteAudio.SetDisable(IDB_VOICE_DISABLE);
        m_muteAudio.SetID(DUID_MUTE_AUDIO);

        m_muteVideo.Create(m_hWnd, r, BDHMenu(DUID_MUTE_VIDEO), L"MV", WS_CHILD | WS_VISIBLE);
        m_muteVideo.SetNormal(IDB_VIDEO);
        m_muteVideo.SetHover(IDB_VIDEO_HOVER);
        m_muteVideo.SetDisable(IDB_VIDEO_DISABLE);
        m_muteVideo.SetID(DUID_MUTE_VIDEO);

        m_share_screen.Create(m_hWnd, r, BDHMenu(DUID_SHARE_SCREEN), L"SS", WS_CHILD | WS_VISIBLE);
        m_share_screen.SetNormal(IDB_SHARE);
        m_share_screen.SetHover(IDB_SHARE_HOVER);
        m_share_screen.SetDisable(IDB_SHARE_ACTIVE);
        m_share_screen.SetID(DUID_SHARE_SCREEN);

        m_video_recording.Create(m_hWnd, r, BDHMenu(DUID_VIDEO_RECORDING), L"VR", WS_CHILD | WS_VISIBLE);
        m_video_recording.SetNormal(IDB_RECORD);
        m_video_recording.SetHover(IDB_RECORD_HOVER);
        m_video_recording.SetDisable(IDB_RECORD_ACTIVE);
        m_video_recording.SetID(DUID_VIDEO_RECORDING);

        m_showUsers.Create(m_hWnd, r, BDHMenu(DUID_SHOW_USER), L"SU", WS_CHILD | WS_VISIBLE);
        m_showUsers.SetNormal(IDB_USER);
        m_showUsers.SetHover(IDB_USER_HOVER);
        m_showUsers.SetDisable(IDB_USER_ACTIVE);
        m_showUsers.SetID(DUID_SHOW_USER);

        m_showSettings.Create(m_hWnd, r, BDHMenu(DUID_SHOW_SETTING), L"SS", WS_CHILD | WS_VISIBLE);
        m_showSettings.SetNormal(IDB_SETTING);
        m_showSettings.SetHover(IDB_SETTING_HOVER);
        m_showSettings.SetDisable(IDB_SETTING_ACTIVE);
        m_showSettings.SetID(DUID_SHOW_SETTING);

        m_leaveButton.Create(m_hWnd, r, BDHMenu(DUID_LEAVE), L"LV", WS_CHILD | WS_VISIBLE);
        m_leaveButton.SetNormal(IDB_LEAVE);
        m_leaveButton.SetHover(IDB_LEAVE_HOVER);
        m_leaveButton.SetDisable(IDB_LEAVE_ACTIVE);
        m_leaveButton.SetID(DUID_LEAVE);

        BDHMenu m;
        BDRect rTips(0, 0, TIPSWIDTH, TIPSHIGHT);
        m_tipsWnd.Create(m_hWnd, &rTips, m, 0, WS_POPUP);
        POINT p[7] = { {0, 0}, {TIPSWIDTH , 0}, {TIPSWIDTH, TIPSHIGHT - 4},{TIPSWIDTH / 2 + 8, TIPSHIGHT - 4}, {TIPSWIDTH / 2 , TIPSHIGHT}, {TIPSWIDTH / 2 - 8, TIPSHIGHT - 4}, {0 , TIPSHIGHT - 4} };
        HRGN hrgn = ::CreatePolygonRgn(p, 7, 1);
        m_tipsWnd.SetWindowRgn(hrgn);
        return 0;
    }

    void OnSize(UINT nType, BDSize size) {
        int interval = (size.cx - ICON_SQUARE * COUNT) / (COUNT + 1);
        int delta = interval + ICON_SQUARE;

        m_muteAudio.MoveWindow(interval, (size.cy - ICON_SQUARE) / 2, ICON_SQUARE, ICON_SQUARE);
        m_muteVideo.MoveWindow(interval + delta, (size.cy - ICON_SQUARE) / 2, ICON_SQUARE, ICON_SQUARE);
        m_share_screen.MoveWindow(interval + delta * 2, (size.cy - ICON_SQUARE) / 2, ICON_SQUARE, ICON_SQUARE);
        m_video_recording.MoveWindow(interval + delta * 3, (size.cy - ICON_SQUARE) / 2, ICON_SQUARE, ICON_SQUARE);
        m_showUsers.MoveWindow(interval + delta * 4, (size.cy - ICON_SQUARE) / 2, ICON_SQUARE, ICON_SQUARE);
        m_showSettings.MoveWindow(interval + delta * 5, (size.cy - ICON_SQUARE) / 2, ICON_SQUARE, ICON_SQUARE);
        m_leaveButton.MoveWindow(interval + delta * 6.5, (size.cy - ICON_SQUARE) / 2, ICON_SQUARE, ICON_SQUARE);

        //RECT rect;
        //m_muteAudio.GetWindowRect(&rect);
        m_muteAudio.OnHover(std::bind(&BDControlWnd::OnButtonHover, this, std::placeholders::_1, std::placeholders::_2, interval, "麦克风", "麦克风"));
        //m_muteVideo.GetWindowRect(&rect);
        m_muteVideo.OnHover(std::bind(&BDControlWnd::OnButtonHover, this, std::placeholders::_1, std::placeholders::_2, interval + delta, "摄像头", "摄像头"));
        //m_share_screen.GetWindowRect(&rect);
        m_share_screen.OnHover(std::bind(&BDControlWnd::OnButtonHover, this, std::placeholders::_1, std::placeholders::_2, interval + delta * 2, "屏幕共享", "屏幕共享"));
        //m_video_recording.GetWindowRect(&rect);
        m_video_recording.OnHover(std::bind(&BDControlWnd::OnButtonHover, this, std::placeholders::_1, std::placeholders::_2, interval + delta * 3, "开启录制", "开启录制"));
        //m_showUsers.GetWindowRect(&rect);
        m_showUsers.OnHover(std::bind(&BDControlWnd::OnButtonHover, this, std::placeholders::_1, std::placeholders::_2, interval + delta * 4, "参会人列表", "参会人列表"));
        //m_showSettings.GetWindowRect(&rect);
        m_showSettings.OnHover(std::bind(&BDControlWnd::OnButtonHover, this, std::placeholders::_1, std::placeholders::_2, interval + delta * 5, "设置", "设置"));
        //m_leaveButton.GetWindowRect(&rect);
        m_leaveButton.OnHover(std::bind(&BDControlWnd::OnButtonHover, this, std::placeholders::_1, std::placeholders::_2, interval + delta * 6.5, "结束通话", "结束通话"));
    }

    void SetMuteValue() {
        UpdateAudio();
        UpdateVideo();
    }

    void SetMessageHandler(HWND handler) {
        m_notify_handler = handler;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_blueBk);

        dc.SelectPen((HPEN)m_grayPen);

        int interval = (rc.right - ICON_SQUARE * COUNT) / (COUNT + 1);
        int delta = interval + ICON_SQUARE;

        int x0 = interval + delta * 6.1;
        int y0 = rc.bottom / 4;
        int x1 = x0;
        int y1 = rc.bottom * 3 / 4;

        dc.MoveTo(x0, y0);
        dc.LineTo(x1, y1);
        return 0;
    }

    LRESULT onMuteAudio(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        auto audio_devices = EngineWrapper::GetInstance()->GetAudioInputDevices();
        if (audio_devices.empty()) {
            ::PostMessage(m_notify_handler, WM_NOTIFY_INVALID_DEVICE, AUDIOTAG, 0);
            return 0;
        }

        EngineWrapper::GetInstance()->m_bMuteAudio = !EngineWrapper::GetInstance()->m_bMuteAudio;
        UpdateAudio();
        return 0;
    }

    void UpdateAudio() {
        EngineWrapper::GetInstance()->muteLocalAudio(EngineWrapper::GetInstance()->m_bMuteAudio);
        ResetAudioState();
        ::PostMessage(m_notify_handler, WM_NOTIFY_MUTE_CHANGE, AUDIOTAG, 0);
    }

    LRESULT onMuteVideo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        auto video_devices = EngineWrapper::GetInstance()->GetVideoCaptureDevices();
        if (video_devices.empty()) {
            ::PostMessage(m_notify_handler, WM_NOTIFY_INVALID_DEVICE, VIDEOTAG, 0);
            return 0;
        }

        EngineWrapper::GetInstance()->m_bMuteVideo = !EngineWrapper::GetInstance()->m_bMuteVideo;
        UpdateVideo();
        return 0;
    }

    void UpdateVideo() {
        EngineWrapper::GetInstance()->muteLocalVideo(EngineWrapper::GetInstance()->m_bMuteVideo);
        ResetVideoState();
        ::PostMessage(m_notify_handler, WM_NOTIFY_MUTE_CHANGE, VIDEOTAG, 0);
    }

    LRESULT onShareScreen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::PostMessage(m_notify_handler, WM_NOTIFY_SCREEN_SHARE, 0, 0);
        return 0;
    }

    LRESULT onRecordVideo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::PostMessage(m_notify_handler, WM_NOTIFY_RECORD_VIDEO, 0, 0);
        //m_tipsWnd.ShowWindow(SW_HIDE);
        return 0;
    }

    LRESULT onShowUser(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::SendMessage(m_notify_handler, WM_NOTIFY_SHOW_USER, 0, 0);
        return 0;
    }

    LRESULT onShowSetting(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::SendMessage(m_notify_handler, WM_NOTIFY_SHOW_SETTING, 0, 0);
        return 0;
    }

    LRESULT onLeave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::SendMessage(m_notify_handler, WM_NOTIFY_LEAVE, 0, 0);
        return 0;
    }

    UINT OnNcHitTest(BDPoint point) {
        return m_move_enable ? HTCAPTION : HTCLIENT;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        return 0;
    }

    void OnButtonHover(bool hover, int state, int left, const std::string& enable_hint, const std::string& disable_hint) {
        if (hover != m_tipsWnd.IsWindowVisible()) {
            RECT rect;
            GetWindowRect(&rect);

            m_tipsWnd.MoveWindow(rect.left + left - (TIPSWIDTH - ICON_SQUARE) / 2,
                rect.top - TIPSHIGHT,
                TIPSWIDTH, TIPSHIGHT);

            m_tipsWnd.SetInfo(m_nameFont,
                RGB(0x27, 0x2E, 0x3B),
                RGB(0xFF, 0xFF, 0xFF));
            m_tipsWnd.SetHint(state == BUTTON_STATE_NORMAL ? enable_hint : disable_hint);
            m_tipsWnd.ShowWindow(hover ? SW_SHOW : SW_HIDE);
            m_tipsWnd.BringWindowToTop();
        }
    }

    void SetMobile(bool enable) {
        m_move_enable = enable;
    }

    HWND GetTipHandler() {
        return m_tipsWnd.m_hWnd;
    }

    void OnDestroy() {
        if (m_tipsWnd.m_hWnd) {
            m_tipsWnd.DestroyWindow();
        }
        m_muteAudio.DestroyWindow();
        m_muteVideo.DestroyWindow();
        m_share_screen.DestroyWindow();
        m_video_recording.DestroyWindow();

        m_showUsers.DestroyWindow();
        m_showSettings.DestroyWindow();
        m_leaveButton.DestroyWindow();
    }
    //=========================
    void ResetAudioState() {
        if (EngineWrapper::GetInstance()->m_bMuteAudio) {
            m_muteAudio.SetState(BUTTON_STATE_DISABLE);
        }
        else {
            m_muteAudio.SetState(BUTTON_STATE_NORMAL);
        }
    }

    void ResetVideoState() {
        if (EngineWrapper::GetInstance()->m_bMuteVideo) {
            m_muteVideo.SetState(BUTTON_STATE_DISABLE);
        }
        else {
            m_muteVideo.SetState(BUTTON_STATE_NORMAL);
        }
    }

    void ResetSettingState(bool active) {
        m_showSettings.SetNormal(active ? IDB_SETTING_HOVER : IDB_SETTING);
    }

    void ResetRecordingState(bool recording) {
        m_video_recording.SetState(recording ? BUTTON_STATE_DISABLE : BUTTON_STATE_NORMAL);
    }

    void ResetUserListState(bool user_list_show) {
        m_showUsers.SetState(user_list_show ? BUTTON_STATE_DISABLE : BUTTON_STATE_NORMAL);
    }

    void ResetScreenSharedState(bool shared) {
        m_share_screen.SetState(shared ? BUTTON_STATE_DISABLE : BUTTON_STATE_NORMAL);
    }

private:
    BDTipsWnd m_tipsWnd;
    BDBmpButton m_muteAudio;
    BDBmpButton m_muteVideo;
    BDBmpButton m_share_screen;
    BDBmpButton m_video_recording;

    BDBmpButton m_showUsers;
    BDBmpButton m_showSettings;
    BDBmpButton m_leaveButton;

    BDBrush m_blueBk;
    BDPen m_grayPen;
    BDFont m_nameFont;

    HWND m_notify_handler = nullptr;
    bool m_move_enable = false;
};

