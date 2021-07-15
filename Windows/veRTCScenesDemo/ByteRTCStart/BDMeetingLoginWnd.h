//
//  BDLoginWnd.h
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
#include "BDPngButton.h"
#include "ByteAppConfig.h"
#include "BDWarningWnd.h"
#include "Utils.h"
#include <fstream>
#include <string>
#include <direct.h>
#include <stdio.h>
#include "BDMaskWnd.h"
#include "meeting-manager/MeetingManager.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")
const unsigned int ROOMIDWARNINGID = 0;
const unsigned int USERIDWARNINGID = 1;

#define IMAGE_PNG_DEFAULT L"resource\\login_default.png"
#define IMAGE_PNG_HOVER L"resource\\login_hover.png"
#define IMAGE_PNG_ACTIVE L"resource\\login_active.png"
#define IMAGE_PNG_AUDIO_ENABLE L"resource\\login_audio_enable.png"
#define IMAGE_PNG_AUDIO_DISABLE L"resource\\login_audio_disable.png"
#define IMAGE_PNG_VIDEO_ENABLE L"resource\\login_video_enable.png"
#define IMAGE_PNG_VIDEO_DISABLE L"resource\\login_video_disable.png"
#define IMAGE_PNG_SETTING L"resource\\login_setting.png"

class BDMeetingLoginWnd : public BDWndImpl<BDMeetingLoginWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDLoginWnd")
    BDMeetingLoginWnd()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
            wci.m_wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
        }
    }

    BEGIN_MSG_MAP(BDMeetingLoginWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_TIMER(OnTimer)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MSG_WM_CTLCOLOREDIT(OnCtlColorEdit)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_NOTIFY_MODIFY_NICKNAME_CALLBACK, OnModifyUserNicknameBack)
        COMMAND_ID_HANDLER(DUID_LOGIN, OnClickLogin)
        COMMAND_ID_HANDLER(DUID_AUDIO, OnClickAudio)
        COMMAND_ID_HANDLER(DUID_VIDEO, OnClickVideo)
        COMMAND_ID_HANDLER(DUID_SHOW_SETTING_LOGIN, onShowSetting)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
        COMMAND_HANDLER(DUID_ROOMID, EN_CHANGE, ChangeHandler)
        COMMAND_HANDLER(DUID_USERID, EN_CHANGE, ChangeHandler)
        COMMAND_HANDLER(DUID_ROOMID, EN_MAXTEXT, ChangeHandler)
        COMMAND_HANDLER(DUID_USERID, EN_MAXTEXT, ChangeHandler)
    END_MSG_MAP()


    void OnFrameShow(BOOL show, int lParam) {
        if (!m_show_alert) {
            SetTimer(0, 200);
        }
    }

    void OnTimer(UINT_PTR time_id) {
        if (!m_show_alert) {
            m_show_alert = true;
            KillTimer(0);
            ::MessageBox(m_hWnd, L"本产品仅用于功能体验，单次会议时长不超过10分钟", L"", MB_OK | MB_ICONWARNING);
        }
    }

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        m_font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_titlefont = CreateFont(16, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_whiteBk = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFE));
        m_greyBk = CreateSolidBrush(RGB(0xF2, 0xF3, 0xF5));
        m_pinkBk = CreateSolidBrush(RGB(0xFF, 0xEC, 0xE8));

        BDHMenu m;
        BDRect r(50, 30, 150, 100);
        m_title.Create(m_hWnd, r, m, L"登录", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE);
        m_title.SetFont(m_titlefont);

        m_roomBackgroud.Create(m_hWnd, r, m, L"", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE);
        m_userBackgroud.Create(m_hWnd, r, m, L"", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE);

        BDRect r3(120, 180, 240, 210);
        m_login.Create(m_hWnd, r3, BDHMenu(DUID_LOGIN), L"进入房间", WS_CHILD | WS_VISIBLE | WS_TABSTOP, WS_EX_CONTROLPARENT);
        m_login.SetBackgroundColor(m_font,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x40, 0x80, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x0E, 0x42, 0xD2), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x94, 0xBF, 0xFF), RGB(0xFF, 0xFF, 0xFF));
        m_login.SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        m_login.SetID(DUID_LOGIN);

        BDRect r1(120, 100, 240, 130);
        m_roomID.Create(m_hWnd, r1, BDHMenu(DUID_ROOMID), 0, WS_CHILD | WS_VISIBLE | WS_TABSTOP, WS_EX_CONTROLPARENT);
        m_roomID.SendMessage(EM_LIMITTEXT, 18, 0);
        m_roomID.SetCueBannerText(L"  房间ID");
        m_roomID.SetFont(m_font);
        
        BDRect r2(120, 150, 240, 180);
        m_user_nickname.Create(m_hWnd, r2, BDHMenu(DUID_USERID), 0, WS_CHILD | WS_VISIBLE | WS_TABSTOP, WS_EX_CONTROLPARENT);
        m_user_nickname.SendMessage(EM_LIMITTEXT, 18, 0);
        m_user_nickname.SetCueBannerText(L"  用户昵称");
        m_user_nickname.SetFont(m_font);
        m_user_nickname.SetWindowTextW(m_nickname);
        if (!m_nickname.IsEmpty()) {
            m_user_statue = ES_NORMAL;
        }

        BDRect r4(0, 0, 32, 32);
        m_audio.Create(m_hWnd, r4, BDHMenu(DUID_AUDIO), L"audio", WS_CHILD | WS_VISIBLE, 0);
        m_audio.SetDefault(IMAGE_PNG_DEFAULT);
        m_audio.SetHover(IMAGE_PNG_HOVER);
        m_audio.SetActive(IMAGE_PNG_ACTIVE);
        m_audio.SetCenterImage(IMAGE_PNG_AUDIO_ENABLE);
        m_audio.SetID(DUID_AUDIO);

        BDRect r5(0, 0, 32, 32);
        m_video.Create(m_hWnd, r5, BDHMenu(DUID_VIDEO), L"video", WS_CHILD | WS_VISIBLE, 0);
        m_video.SetDefault(IMAGE_PNG_DEFAULT);
        m_video.SetHover(IMAGE_PNG_HOVER);
        m_video.SetActive(IMAGE_PNG_ACTIVE);
        m_video.SetCenterImage(IMAGE_PNG_VIDEO_ENABLE);
        m_video.SetID(DUID_VIDEO);

        BDRect r6(0, 0, 32, 32);
        m_showSettings.Create(m_hWnd, r6, BDHMenu(DUID_SHOW_SETTING_LOGIN), L"SST", WS_CHILD | WS_VISIBLE);
        m_showSettings.SetDefault(IMAGE_PNG_DEFAULT);
        m_showSettings.SetHover(IMAGE_PNG_HOVER);
        m_showSettings.SetActive(IMAGE_PNG_ACTIVE);
        m_showSettings.SetCenterImage(IMAGE_PNG_SETTING);
        m_showSettings.SetID(DUID_SHOW_SETTING_LOGIN);
        m_error.LoadBitmap(IDB_ERROR);

        m_created = true;
        return 0;
    }

    BDString GetRoomId() {
        return m_roomID.GetWindowText();
    }

    BDString GetUserNickname() {
        return m_nickname;
    }

    void SetUserNickname(const BDString& name) {
        m_nickname = name;
    }

    void SetMessageHandler(HWND handler) {
        m_notify_handler = handler;
    }

    void Reset()
    {
        UpdateAudioButton();
        UpdateVideoButton();
        m_login.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
    }

    void ResetLogin() {
        m_login.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
    }

    void ResetRoomEdit() {
        m_roomID.SetWindowTextW(L"");
    }

    LRESULT OnCtlColorEdit(HDC hDc, HWND handler) {
        EditStatus status = (handler == m_roomID.m_hWnd ? m_room_statue : m_user_statue);
        m_roomBackgroud.RedrawWindow();
        m_userBackgroud.RedrawWindow();

        if (status == ES_INVALID) {
            ::SetTextColor(hDc, RGB(0, 0, 0));
            ::SetBkMode(hDc, OPAQUE);
            ::SetBkColor(hDc, RGB(0xFF, 0xEC, 0xE8));
            return (INT_PTR)CreateSolidBrush(RGB(0xFF, 0xEC, 0xE8));//返回背景色的画刷
        }
        else {
            ::SetTextColor(hDc, RGB(0, 0, 0));
            ::SetBkMode(hDc, OPAQUE);
            ::SetBkColor(hDc, RGB(0xF2, 0xF3, 0xF5));
            return (INT_PTR)CreateSolidBrush(RGB(0xF2, 0xF3, 0xF5));//返回背景色的画刷
        }
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic)
    {
        if (wndStatic == m_title)
        {
            dc.SetBkColor(RGB(255, 255, 255));
            dc.SetTextColor(RGB(0, 0, 0));
        }
        else if (wndStatic == m_roomBackgroud || wndStatic == m_userBackgroud) {
            EditStatus status = (wndStatic == m_roomBackgroud ? m_room_statue : m_user_statue);
            if (status == ES_INVALID) {
                dc.SetTextColor(RGB(0, 0, 0));
                dc.SetBkMode(OPAQUE);
                dc.SetBkColor(RGB(0xFF, 0xEC, 0xE8));
                return (HBRUSH)CreateSolidBrush(RGB(0xFF, 0xEC, 0xE8));//返回背景色的画刷
            }
            else {
                dc.SetTextColor(RGB(0, 0, 0));
                dc.SetBkMode(OPAQUE);
                dc.SetBkColor(RGB(0xF2, 0xF3, 0xF5));
                return (HBRUSH)CreateSolidBrush(RGB(0xF2, 0xF3, 0xF5));//返回背景色的画刷
            }

        }
        return (HBRUSH)::GetStockObject(WHITE_BRUSH);
    }

    LRESULT ChangeHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (!m_created) {
            return 0;
        }

        auto showHint = [wNotifyCode, this](BDEdit& content, EditStatus& status, std::function<bool(const BDString&)> func) {
            if (wNotifyCode == EN_MAXTEXT) {
                if (status != ES_INVALID) {
                    status = ES_MAXTEXT;
                }
                ::PostMessage(m_notify_handler, WM_NOTIFY_WARNING, ES_MAXTEXT, 0);
            } else if (wNotifyCode == EN_CHANGE) {
                BDString str = content.GetWindowText();
                int len = str.GetLength();

                if (!func(str)) {
                    status = ES_INVALID;
                } else if (str.IsEmpty()) {
                    status = ES_EMPTY;
                } else {
                    status = ES_NORMAL;
                }
            }

            content.RedrawWindow();
            content.Invalidate();
            content.UpdateWindow();
        };

        auto lastRoomState = m_room_statue;
        auto lastUserState = m_user_statue;

        if (hWndCtl == (HWND)m_roomID) {
            showHint(m_roomID, m_room_statue, rtcutil::IsValidRoomString);
        }
        else if (hWndCtl == (HWND)m_user_nickname) {
            showHint(m_user_nickname, m_user_statue, rtcutil::IsValidUserString);
        }

        if ((m_room_statue == ES_MAXTEXT || m_room_statue == ES_NORMAL)
            && (m_user_statue == ES_MAXTEXT || m_user_statue == ES_NORMAL)
            && m_connedtion) {
            m_login.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
        }
        else {
            m_login.SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        }

        if (m_room_statue == ES_INVALID || m_user_statue == ES_INVALID) {
            ::PostMessage(m_notify_handler, WM_NOTIFY_WARNING, ES_INVALID, 1);
        }
        else {
            ::PostMessage(m_notify_handler, WM_NOTIFY_WARNING, ES_INVALID, 0);
        }

        InvalidateErrorInfo(lastRoomState != m_room_statue, lastUserState != m_user_statue);
        return 0;
    }
    //348,620
    void OnSize(UINT nType, BDSize size) {
        m_title.MoveWindow(40, (size.cy - 24) / 2, 32, 24);
        m_roomBackgroud.MoveWindow(96, (size.cy - 32) / 2, 128, 8);
        m_roomID.MoveWindow(96, (size.cy - 32) / 2 + 8, 128, 32 - 8);

        m_userBackgroud.MoveWindow(272, (size.cy - 32) / 2, 128, 8);
        m_user_nickname.MoveWindow(272, (size.cy - 32) / 2 + 8, 128, 32 - 8);
        m_login.MoveWindow(448, (size.cy - 32) / 2, 88, 32);
        m_audio.MoveWindow(568, (size.cy - 32) / 2, 32, 32);
        m_video.MoveWindow(616, (size.cy - 32) / 2, 32, 32);
        m_showSettings.MoveWindow(664, (size.cy - 32) / 2, 32, 32);
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_whiteBk);

        RECT room_error;
        room_error.left = 96 + 128;
        room_error.right = room_error.left + 32;
        room_error.top = (rc.bottom - 32) / 2;
        room_error.bottom = room_error.top + 32;

        BDDC mydc = ::CreateCompatibleDC(dc);
        //Draw Head
        mydc.SelectBitmap(m_error);
        if (m_room_statue == ES_INVALID) {
            dc.FillRect(&room_error, m_pinkBk);
            dc.BitBlt(room_error.left + 9, room_error.top + 9, 14, 14, mydc, 0, 0, SRCCOPY);
        }
        else {
            dc.FillRect(&room_error, m_greyBk);
        }

        RECT user_error;
        user_error.left = 272 + 128;
        user_error.right = user_error.left + 32;
        user_error.top = (rc.bottom - 32) / 2;
        user_error.bottom = user_error.top + 32;

        if (m_user_statue == ES_INVALID) {
            dc.FillRect(&user_error, m_pinkBk);
            dc.BitBlt(user_error.left + 9, user_error.top + 9, 14, 14, mydc, 0, 0, SRCCOPY);
        }
        else {
            dc.FillRect(&user_error, m_greyBk);
        }

        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
    {
        EngineWrapper::GetInstance()->destroyEngine();
        return 0;
    }

    void ModifyUserNickname(const BDString& nickname) {
        MeetingManager::GetInstance()->changeUserName(rtcutil::ConvertBDStringToUTF8(nickname),
            [this](int code) {
            ::PostMessage(m_hWnd, WM_NOTIFY_MODIFY_NICKNAME_CALLBACK, code, 0);
        });
    }

    LRESULT OnModifyUserNicknameBack(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        int code = (int)wParam;
        if (code = 200) {
            m_nickname = m_user_nickname.GetWindowText();
            APPConfig::Instance()->SetLoginUserName(rtcutil::ConvertBDStringToUTF8(m_nickname));
            m_login.SetState(BDTxtButton::BUTTON_STATE_DISABLE);
            ::PostMessage(m_notify_handler, WM_NOTIFY_LOGIN_CLICK, 0, 0);
        }
        else {
            ::PostMessage(m_notify_handler, WM_NOTIFY_MODIFY_NICKNAME_ERROR, code, 0);
        }
        return 0;
    }

    LRESULT OnClickLogin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (m_login.m_state == BDTxtButton::BUTTON_STATE_DISABLE || !m_connedtion) {
            return 0;
        }

        auto nickname = m_user_nickname.GetWindowText();
        if (nickname != m_nickname) {
            ModifyUserNickname(nickname);
        }
        else {
            m_login.SetState(BDTxtButton::BUTTON_STATE_DISABLE);
            ::PostMessage(m_notify_handler, WM_NOTIFY_LOGIN_CLICK, 0, 0);
        }

        return 0;
    }

    LRESULT onShowSetting(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::SendMessage(m_notify_handler, WM_NOTIFY_SHOW_SETTING, 0, 0);
        return 0;
    }

    LRESULT OnClickAudio(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        auto audio_devices = EngineWrapper::GetInstance()->GetAudioInputDevices();
        if (audio_devices.empty() || !EngineWrapper::GetInstance()->AudioRecordDevicesTest()) {
            ::PostMessage(m_notify_handler, WM_NOTIFY_INVALID_DEVICE, AUDIOTAG, 0);
            return 0;
        }

        EngineWrapper::GetInstance()->m_bMuteAudio = !EngineWrapper::GetInstance()->m_bMuteAudio;
        UpdateAudioButton();
        return 0;
    }

    void UpdateAudioButton() {
        m_audio.SetFocus();
        if (EngineWrapper::GetInstance()->m_bMuteAudio) {
            m_audio.SetCenterImage(IMAGE_PNG_AUDIO_DISABLE);
        } else {
            m_audio.SetCenterImage(IMAGE_PNG_AUDIO_ENABLE);
        }

        EngineWrapper::GetInstance()->muteLocalAudio(EngineWrapper::GetInstance()->m_bMuteAudio);
    }

    LRESULT OnClickVideo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        auto video_devices = EngineWrapper::GetInstance()->GetVideoCaptureDevices();
        if (video_devices.empty()) {
            ::PostMessage(m_notify_handler, WM_NOTIFY_INVALID_DEVICE, VIDEOTAG, 0);
            return 0;
        }

        EngineWrapper::GetInstance()->m_bMuteVideo = !EngineWrapper::GetInstance()->m_bMuteVideo;
        UpdateVideoButton();
        return 0;
    }

    void UpdateVideoButton() {
        m_video.SetFocus();
        if (EngineWrapper::GetInstance()->m_bMuteVideo) {
            m_video.SetCenterImage(IMAGE_PNG_VIDEO_DISABLE);
            ::PostMessage(m_notify_handler, WM_NOTIFY_VIDEO_PREVIEW, 0, 0);
        } else {
            m_video.SetCenterImage(IMAGE_PNG_VIDEO_ENABLE);
            ::PostMessage(m_notify_handler, WM_NOTIFY_VIDEO_PREVIEW, 1, 0);
        }

        EngineWrapper::GetInstance()->muteLocalVideo(EngineWrapper::GetInstance()->m_bMuteVideo);
    }

    void OnConnection() {
        m_connedtion = true;
    }

    void OnDisconnection() {
        m_connedtion = false;
    }

    void OnVideoDeviceDisconection() {
        EngineWrapper::GetInstance()->m_bMuteVideo = true;
        UpdateVideoButton();
    }

    void OnAudioDeviceDisconection() {
        EngineWrapper::GetInstance()->m_bMuteAudio = true;
        UpdateAudioButton();
    }

    void OnEngineCreate() {
        auto video_devices = EngineWrapper::GetInstance()->GetVideoCaptureDevices();
        auto audio_devices = EngineWrapper::GetInstance()->GetAudioInputDevices();

        if (video_devices.empty()) {
            EngineWrapper::GetInstance()->m_bMuteVideo = true;
            UpdateVideoButton();
        }

        if (audio_devices.empty()) {
            EngineWrapper::GetInstance()->m_bMuteAudio = true;
            UpdateAudioButton();
        }
    }

    enum EditStatus
    {
        ES_NORMAL = 0,
        ES_EMPTY,
        ES_MAXTEXT,
        ES_INVALID,
    };

private:
    void InvalidateErrorInfo(bool refresh_room, bool refresh_user) {
        RECT rc;
        GetClientRect(&rc);

        if (refresh_room) {
            RECT room_error;
            room_error.left = 96 + 128;
            room_error.right = room_error.left + 32;
            room_error.top = (rc.bottom - 32) / 2;
            room_error.bottom = room_error.top + 32;

            InvalidateRect(&room_error);
        }

        if (refresh_user) {
            RECT user_error;
            user_error.left = 272 + 128;
            user_error.right = user_error.left + 32;
            user_error.top = (rc.bottom - 32) / 2;
            user_error.bottom = user_error.top + 32;

            InvalidateRect(&user_error);
        }
    }

    BDStatic m_title;
    
    BDFont m_font;
    BDFont m_titlefont;

    BDStatic m_roomBackgroud;
    BDEdit m_roomID;
    EditStatus m_room_statue = ES_NORMAL;

    BDStatic m_userBackgroud;
    BDEdit m_user_nickname;
    EditStatus m_user_statue = ES_EMPTY;

    BDTxtButton m_login;
    BDPngButton m_audio;
    BDPngButton m_video;
    BDPngButton m_showSettings;

    HWND m_notify_handler = nullptr;
    BDBrush m_whiteBk;
    BDBrush m_greyBk;
    BDBrush m_pinkBk;
    BDBitmap m_error;

    bool m_created = false;
    bool m_connedtion = false;
    bool m_show_alert = false;

    BDString m_nickname;
};

