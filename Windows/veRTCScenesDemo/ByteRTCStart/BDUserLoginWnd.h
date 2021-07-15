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
#include "BDMainContainerFrame.h"
#include "Utils.h"
#include <fstream>
#include <string>
#include <direct.h>
#include <stdio.h>
#include "BDMaskWnd.h"
#include "BDMessageWnd.h"
#include "BDMaskWnd.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")
const int EDIT_WIDTH = 320;
const int EDIT_HEIGHT = 48;
const int LOGIN_WIDTH = 320;
const int LOGIN_HEIGHT = 48;

#define LOGIN_LOGO L"resource\\login_logo.png"
#define LOGIN_BUTTON_DEFAULT L"resource\\login_button_defualt.png"
#define LOGIN_BUTTON_HOVER L"resource\\login_button_hover.png"
#define LOGIN_BUTTON_ACTIVE L"resource\\login_button_active.png"
#define LOGIN_BUTTON_DISABLE L"resource\\login_button_disable.png"
#define EDIT_STATE_NORMAL L"resource\\edit_normal.png"
#define EDIT_STATE_FOCUS L"resource\\edit_focus.png"
#define EDIT_STATE_ERROR L"resource\\edit_error.png"
#define LOGIN_LOGIN L"resource\\login.png"

class BDUserLoginWnd : public BDWndImpl<BDUserLoginWnd>, public IMeetingNotification {
public:
    DECLARE_BDWND_CLASS(L"BDLoginWnd")
    BDUserLoginWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_APP_LOGO));
            wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x27, 0x2E, 0x3B));
        }
    }

    BEGIN_MSG_MAP(BDLoginWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_MOVE(OnMove)
        MSG_WM_TIMER(OnTimer)
        MSG_WM_CLOSE(OnClose)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_GETMINMAXINFO(OnMinMaxInfo)
        MSG_WM_CTLCOLOREDIT(OnCtlColorEdit)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_NOTIFY_UPDATE_APP, OnUpdateApp)
        MESSAGE_HANDLER(WM_NOTIFY_CHECK_TOKEN, OnCheckToken)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_NOTIFY_SHOW_MEETING_LOGIN, ShowMeetingLoginFrame)
        COMMAND_ID_HANDLER(DUID_LOGIN, OnClickLogin)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
        COMMAND_HANDLER(DUID_PHONE_NUMBER, EN_SETFOCUS, FocusHandler)
        COMMAND_HANDLER(DUID_PHONE_NUMBER, EN_KILLFOCUS, KillFocusHandler)
        COMMAND_HANDLER(DUID_PHONE_NUMBER, EN_CHANGE, ChangeHandler)
        COMMAND_HANDLER(DUID_PHONE_NUMBER, EN_MAXTEXT, ChangeHandler)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        m_font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_blueBk = CreateSolidBrush(RGB(0x27, 0x2E, 0x3B));

        BDHMenu m;
        BDRect r(50, 30, 150, 100);

        BDRect r3(0, 0, 0, 0);
        m_login.Create(m_hWnd, r3, BDHMenu(DUID_LOGIN), L"登录", WS_CHILD | WS_VISIBLE | WS_TABSTOP, WS_EX_CONTROLPARENT);
        m_login.SetBackgroundColor(m_font,
            RGB(0x27, 0x2E, 0x3B),
            LOGIN_BUTTON_DEFAULT, RGB(0xFF, 0xFF, 0xFF),
            LOGIN_BUTTON_HOVER, RGB(0xFF, 0xFF, 0xFF),
            LOGIN_BUTTON_ACTIVE, RGB(0xFF, 0xFF, 0xFF),
            LOGIN_BUTTON_DISABLE, RGB(103, 108, 117));
        m_login.SetState(BDTxtPngButton::BUTTON_STATE_DISABLE);
        m_login.SetID(DUID_LOGIN);

        BDRect r1(0, 0, 0, 0);
        m_user_name.Create(m_hWnd, r1, BDHMenu(DUID_PHONE_NUMBER), 0, WS_CHILD | WS_VISIBLE | WS_TABSTOP, WS_EX_CONTROLPARENT);
        m_user_name.SendMessage(EM_LIMITTEXT, 18, 0);
        m_user_name.SetCueBannerText(L"输入用户名");
        m_user_name.SetFont(m_font);

        m_name_error_hint.Create(m_hWnd, r, m, L"仅支持中文、字母、数字，1-18位", WS_CHILD | SS_LEFT);
        m_name_error_hint.SetFont(m_font);

        BDRect rKickoff(0, 0, KICKOFF_WND_WIDTH + 20, KICKOFF_WND_HEIGHT);
        m_bubbleTipWnd.Create(m_hWnd, &rKickoff, m, 0, WS_CHILD | WS_CLIPCHILDREN);
        HRGN bubbleRgn = ::CreateRoundRectRgn(0, 0, KICKOFF_WND_WIDTH + 20, KICKOFF_WND_HEIGHT, 10, 10);
        m_bubbleTipWnd.SetWindowRgn(bubbleRgn);

        BDRect r2(0, 0, 0, 0);
        m_mask.Create(m_hWnd, &r2, m, 0, WS_POPUP);
        BDRect rMessage(0, 0, MESSAGE_WND_WIDTH, MESSAGE_WND_HEIGHT);
        m_messageWnd.Create(m_mask.m_hWnd, &rMessage, m, 0, WS_POPUP);

        rtcutil::LoadFile(LOGIN_LOGO, m_login_logo);
        rtcutil::LoadFile(EDIT_STATE_NORMAL, m_edit_normal);
        rtcutil::LoadFile(EDIT_STATE_FOCUS, m_edit_focus);
        rtcutil::LoadFile(EDIT_STATE_ERROR, m_edit_error);

        m_states[0] = m_edit_normal;
        m_states[1] =  m_edit_focus;
        m_states[2] =  m_edit_error;
        m_states[3] = m_edit_error;

        MeetingManager::GetInstance()->registerNotification(this);
        MeetingManager::GetInstance()->startConnect();
        m_created = true;
        return 0;
    }

    void OnFrameShow(BOOL show, int lParam) {
        CheckUpdateApp(show);
    }

    void CheckUpdateApp(bool show) {
        bool check = APPConfig::Instance()->IsCheckUpdate();
        if (show && !check && m_connection) {
            MeetingManager::GetInstance()->getAuditState(VERSION, [this](int code, const AuditState& state) {
                if (code == 200 && state.state) {
                    SendMessage(WM_NOTIFY_UPDATE_APP, (WPARAM)state.url.c_str(), 0);
                }
            });
        }
        Invalidate();
    }

    LRESULT OnUpdateApp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        bool show = IsWindowVisible();
        if (show) {
            std::string url((const char*)wParam);
            m_mask.ShowWindow(SW_SHOW);
            m_messageWnd.SetMessage(L"应用有更新，立刻下载最新版本？");
            m_messageWnd.SetMessageHander("确定", [this, url]() {
                    m_messageWnd.ShowWindow(SW_HIDE);
                    m_mask.ShowWindow(SW_HIDE);

                    BDString address = rtcutil::ConvertUTF8ToBDString(url);
                    ShellExecute(0, L"open", address, L"", L"", 0);
                },
                "取消", [this]() {
                    m_messageWnd.ShowWindow(SW_HIDE);
                    m_mask.ShowWindow(SW_HIDE);
            });

            m_messageWnd.ShowWindow(SW_SHOW);
            APPConfig::Instance()->SetCheckUpdate();
        }
        return 0;
    }

    void OnTimer(UINT_PTR time_id) {
        if (time_id == 3) {
            KillTimer(3);
            // 超时进入会议登录页面
            PostMessage(WM_NOTIFY_SHOW_MEETING_LOGIN, 0, 0);
        }
        else if (time_id == 1) {
            KillTimer(1);
            
            BDString str1 = m_user_name.GetWindowText();
            auto statue = m_user_name_statue == ES_FOCUS_ERROR || m_user_name_statue == ES_FOCUS ? ES_FOCUS : ES_NORMAL;
            if (!rtcutil::IsValidUserString(str1)) {
                statue = statue == ES_FOCUS ? ES_FOCUS_ERROR : ES_KILLFOCUS_ERROR;
            }

            if (m_user_name_statue != statue) {
                m_user_name_statue = statue;
                RECT rc;
                GetClientRect(&rc);
                RECT rect = { 0, 320, rc.right, 320 + 72 };
                InvalidateRect(&rect);
            }

            if (m_user_name_statue == ES_NORMAL || m_user_name_statue == ES_FOCUS) {
                m_login.SetState(BDTxtPngButton::BUTTON_STATE_DEFAULT);
            }
            else {
                m_login.SetState(BDTxtPngButton::BUTTON_STATE_DISABLE);
            }
        }
    }

    void OnClose() {
        PostQuitMessage(0);
    }

    void OnMinMaxInfo(LPMINMAXINFO info) {
        RECT r = { 0, 0, 800, 584 };
        AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
        info->ptMinTrackSize.x = r.right - r.left;
        info->ptMinTrackSize.y = r.bottom - r.top;
        info->ptMaxTrackSize.x = r.right - r.left;
        info->ptMaxTrackSize.y = r.bottom - r.top;
    }

    LRESULT OnCtlColorEdit(HDC hDc, HWND handler) {
        ::SetTextColor(hDc, RGB(0xFF, 0xFF, 0xFF));
        ::SetBkMode(hDc, OPAQUE);
        ::SetBkColor(hDc, RGB(0x1C, 0x22, 0x2C));
        return (INT_PTR)CreateSolidBrush(RGB(0x1C, 0x22, 0x2C));
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_name_error_hint) {
            dc.SetBkMode(TRANSPARENT);
            dc.SetTextColor(RGB(0xF5, 0x3F, 0x3F));
            dc.SetBkColor(RGB(0x27, 0x2E, 0x3B));
            return (HBRUSH)CreateSolidBrush(RGB(0x27, 0x2E, 0x3B));
        }

        return (HBRUSH)::GetStockObject(WHITE_BRUSH);
    }

    LRESULT ChangeHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        auto checkState = [this, wNotifyCode](BDEdit& content, EditStatus& statue)->bool {
            auto new_statue = ES_FOCUS;
            if (wNotifyCode == EN_MAXTEXT) {
                new_statue = ES_FOCUS_ERROR;
                SetTimer(1, 2000);
            }
            else if (wNotifyCode == EN_CHANGE) {
                BDString str = content.GetWindowText();
                if (!rtcutil::IsValidUserString(str)) {
                    new_statue = ES_FOCUS_ERROR;
                }
            }

            bool res = false;
            if (statue != new_statue) {
                statue = new_statue;
                res = true;
            }

            return res;
        };

        bool invalid = false;
        if (hWndCtl == (HWND)m_user_name) {
            invalid = checkState(m_user_name, m_user_name_statue);
        }

        if (m_user_name_statue == ES_NORMAL || m_user_name_statue == ES_FOCUS) {
            m_login.SetState(BDTxtPngButton::BUTTON_STATE_DEFAULT);
        }
        else {
            m_login.SetState(BDTxtPngButton::BUTTON_STATE_DISABLE);
        }

        if (invalid) {
            RECT rc;
            GetClientRect(&rc);
            RECT rect = { 0, 320, rc.right, 320 + 72 };
            InvalidateRect(&rect);
        }

        return 0;
    }

    LRESULT KillFocusHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        RECT rc;
        GetClientRect(&rc);

        if (hWndCtl == (HWND)m_user_name) {
            if (m_user_name_statue == ES_FOCUS) {
                m_user_name_statue = ES_NORMAL;
            }
            else if (m_user_name_statue == ES_FOCUS_ERROR) {
                m_user_name_statue = ES_KILLFOCUS_ERROR;
            }
        }

        RECT rect = { 0, 320, rc.right, 320 + 72 };
        InvalidateRect(&rect);
        return 0;
    }

    LRESULT FocusHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (wNotifyCode != EN_SETFOCUS) return 0;

        RECT rc;
        GetClientRect(&rc);

        if (hWndCtl == (HWND)m_user_name) {
            if (m_user_name_statue == ES_NORMAL) {
                m_user_name_statue = ES_FOCUS;
            }
        }

        RECT rect = { 0, 320, rc.right, 320 + 72 };
        InvalidateRect(&rect);
        return 0;
    }
    //348,620
    void OnSize(UINT nType, BDSize size) {
        const int delta = 16;
        m_user_name.MoveWindow((size.cx - EDIT_WIDTH) / 2 + delta, 320 + delta, EDIT_WIDTH - delta * 2, EDIT_HEIGHT - delta - 2);
        m_login.MoveWindow((size.cx - LOGIN_WIDTH) / 2, 416, LOGIN_WIDTH, LOGIN_HEIGHT);

        RECT bubbleRc;
        m_bubbleTipWnd.GetClientRect(&bubbleRc);
        m_bubbleTipWnd.MoveWindow((size.cx - bubbleRc.right) / 2, 8,
            (size.cx + bubbleRc.right) / 2, KICKOFF_WND_HEIGHT);

        OnMove(0, 0);
    }

    void OnMove(int x, int y) {
        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);

        m_mask.MoveWindow(rc.left + 10,
            rc.top,
            rc.right - rc.left - 20,
            rc.bottom - rc.top - 10);

        m_messageWnd.MoveWindow((rc.right + rc.left - MESSAGE_WND_WIDTH) / 2,
            (rc.bottom + rc.top - MESSAGE_WND_HEIGHT) / 2,
            MESSAGE_WND_WIDTH, MESSAGE_WND_HEIGHT);

    }

    LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        m_user_name.SetFocus();
        return 0;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);

        RECT rc;
        GetClientRect(&rc);
        BDDC localDc = ::CreateCompatibleDC(dc); // Double buffering
        auto hBitmap = ::CreateCompatibleBitmap(dc, rc.right, rc.bottom);
        ::SelectObject(localDc, hBitmap);

        localDc.FillRect(&rc, m_blueBk);

        if (m_login_logo) {
            int w = m_login_logo->GetWidth();
            int h = m_login_logo->GetHeight();
            rtcutil::DrawImage(localDc.m_hDC, m_login_logo,
                (rc.right - w) / 2,
                120,
                w,
                h);
        }

        if (m_states[m_user_name_statue]) {
            Gdiplus::Image* state = m_states[m_user_name_statue];
            int w = state->GetWidth();
            int h = state->GetHeight();
            rtcutil::DrawImage(localDc.m_hDC, state,
                (rc.right - w) / 2,
                320,
                w,
                h);

            if (m_user_name_statue == ES_FOCUS_ERROR
                || m_user_name_statue == ES_KILLFOCUS_ERROR) {
                RECT rect = { (rc.right - w) / 2, 320 + 54, (rc.right + w) / 2, 400 };
                m_name_error_hint.MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
                m_name_error_hint.ShowWindow(SW_SHOW);
            }
            else {
                m_name_error_hint.ShowWindow(SW_HIDE);
            }
        }

        dc.BitBlt(0, 0, rc.right, rc.bottom, localDc, 0, 0, SRCCOPY);
        DeleteObject(hBitmap);
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        EngineWrapper::GetInstance()->destroyEngine();
        return 0;
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        m_login.SetFocus();
        RECT rc;
        GetClientRect(&rc);

        auto phone_number_statue = m_user_name_statue;
        if (m_user_name_statue == ES_FOCUS) {
            phone_number_statue = ES_NORMAL;
        }

        if (m_states[m_user_name_statue]) {
            Gdiplus::Image* state = m_states[m_user_name_statue];
            int w = state->GetWidth();
            int h = state->GetHeight();
            RECT rect = { (rc.right - w) / 2, 320, (rc.right + w) / 2, 320 + h };
            if (PtInRect(&rect, point) && phone_number_statue != ES_FOCUS_ERROR && phone_number_statue != ES_KILLFOCUS_ERROR) {
                phone_number_statue = ES_FOCUS;
            }
        }

        bool change = false;
        if (m_user_name_statue != phone_number_statue) {
            change = true;
            m_user_name_statue = phone_number_statue;
            if (m_user_name_statue == ES_FOCUS) {
                m_user_name.SetFocus();
            }
        }

        if (change) {
            RECT rc;
            GetClientRect(&rc);

            RECT rect = { 0, 320, rc.right, 320 + 72 };
            InvalidateRect(&rect);
        }
    }

    LRESULT OnClickLogin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        OnLButtonUp(0, BDPoint(0, 0));
        if (m_login.m_state == BDTxtPngButton::BUTTON_STATE_DISABLE) {
            return 0;
        }

        BDString name = m_user_name.GetWindowText();
        MeetingManager::GetInstance()->passwordFreeLogin(rtcutil::ConvertBDStringToUTF8(name),
            [this](int code, const VerifySms& sms) {
                if (code == 440) {
                    ShowBubbleTip("验证码过期，请重新发送验证码");
                } else if (code == 441) {
                    ShowBubbleTip("验证码不正确，请重新发送验证码");
                }
                else if (code == 200) {
                    m_sms = sms;
                    PostMessage(WM_NOTIFY_SHOW_MEETING_LOGIN, 0, 0);
                }
        });

        return 0;
    }

    void ShowMeetingFrame(const VerifySms& sms) {
        m_sms = sms;
        SetTimer(3, 500);
        VerifySmsInfo();
    }

    LRESULT OnCheckToken(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        KillTimer(3);
        bool invalid = (bool)wParam;
        bool show = !m_main_wnd.m_hWnd || !m_main_wnd.IsWindowVisible();
        if (invalid && show) {
            PostMessage(WM_NOTIFY_SHOW_MEETING_LOGIN, 0, 0);
        }
        else if(!invalid){
            m_user_name.SetWindowTextW(L"");
            m_user_name_statue = ES_NORMAL;

            ShowWindow(SW_SHOW);
        }

        return 0;
    }
 
    LRESULT ShowMeetingLoginFrame(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        MeetingManager::GetInstance()->setMeetingToken(m_sms.login_token);
        APPConfig::Instance()->SetLoginUserId(m_sms.user_id);
        APPConfig::Instance()->SetLoginUserName(rtcutil::ConvertBDStringToUTF8(m_sms.user_name));
        APPConfig::Instance()->SetLoginToken(m_sms.login_token);

        if (m_user_name_statue == ES_NORMAL || m_user_name_statue == ES_FOCUS) {
            m_login.SetState(BDTxtPngButton::BUTTON_STATE_DEFAULT);
        }

        RECT display;
        GetWindowRect(&display);
        ShowWindow(SW_HIDE);
        display.left = (display.left + display.right) / 2;
        display.top = (display.top + display.bottom) / 2;

        auto hInstance = BDWinApp::GetAppInstance();
        HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_BYTERTCSTART));

        std::vector<RECT> displayList;
        rtcutil::GetDisplayList(displayList);
        for (auto& screen : displayList) {
            if (screen.left <= display.left && screen.top <= display.top
                && screen.right >= display.left && screen.bottom >= display.top) {
                display = screen;
                break;
            }
        }

        auto delta_x = 0;
        auto delta_y = 0;
        if (display.right - display.left > 1280) {
            delta_x = (display.right - display.left - 1280) / 2;
        }

        if (display.bottom - display.top > 720) {
            delta_y = (display.bottom - display.top - 720) / 2;
        }

        RECT r = { display.left + delta_x, display.top + delta_y, display.left + delta_x + 1280, display.top + delta_y + 720 };
        AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
        BDHMenu menu;
        m_main_wnd.SetVerifySms(m_sms);
        if (m_main_wnd.m_hWnd) {
            m_main_wnd.MoveWindow(r.left, r.top, r.right - r.left, r.bottom - r.top);
        }
        else {
            m_main_wnd.Create(NULL, &r, menu, L"veRTC", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, hMenu);
        }

        m_main_wnd.ShowWindow(SW_SHOW);
        if (m_connection) {
            m_main_wnd.onWebsocketConnected();
        }

        return 0;
    }

    enum EditStatus {
        ES_NORMAL = 0,
        ES_FOCUS,
        ES_FOCUS_ERROR,
        ES_KILLFOCUS_ERROR
    };

private:
    void ShowBubbleTip(const BDString& message, bool auto_disapper = true) {
            HRGN bubbleRgn = ::CreateRoundRectRgn(0, 0, KICKOFF_WND_WIDTH + 20, KICKOFF_WND_HEIGHT, 10, 10);
            m_bubbleTipWnd.SetWindowRgn(bubbleRgn);
            m_bubbleTipWnd.AutoDisappear(auto_disapper);
            m_bubbleTipWnd.SetTipMessage(message);
            m_bubbleTipWnd.ShowWindow(SW_SHOW);
            m_bubbleTipWnd.BringWindowToTop();
    }

    void VerifySmsInfo() {
        if (m_connection && !m_sms.login_token.empty()) {
            MeetingManager::GetInstance()->verifyLoginToken(m_sms.login_token, [this](int code) {
                PostMessage(WM_NOTIFY_CHECK_TOKEN, code == 200, 0);
            });
        }
    }

    void onWebsocketConnected() override {
        m_connection = true;
        if (m_bubbleTipWnd.IsWindowVisible()) {
            m_bubbleTipWnd.ShowWindow(SW_HIDE);
        }

        VerifySmsInfo();

        bool show = m_hWnd && IsWindowVisible();
        CheckUpdateApp(show);
    }

    void onWebsocketConnecting() override {
        m_connection = false;
        ShowBubbleTip("网络链接已断开，请检查设置", false);
    }

    void onInvaildToken(int code) override {
        ShowWindow(SW_SHOW);
        if (code == 450) {
            ShowBubbleTip("token已经过期，请重新登录", false);
        } else if(code == 451) {
            ShowBubbleTip("token为空，请重新登录", false);
        }
    }

private:
    BDFont m_font;
    BDBrush m_blueBk;

    BDEdit m_user_name;
    EditStatus m_user_name_statue = ES_NORMAL;
    BDStatic m_name_error_hint;

    BDTxtPngButton m_login;
    BDMainContainerFrame m_main_wnd;
    BDBubbleTipWnd m_bubbleTipWnd; // Pop up prompt window

    BDMaskWnd m_mask; // main mask window
    BDMessageWnd m_messageWnd;    // Confirmation window

    Gdiplus::Image* m_states[4];
    Gdiplus::Image* m_login_logo = nullptr;
    Gdiplus::Image* m_edit_normal = nullptr;
    Gdiplus::Image* m_edit_focus = nullptr;
    Gdiplus::Image* m_edit_error = nullptr;

    bool m_created = false;
    int m_time_tick = 60;
    bool m_count_down = false;
    bool m_connection = false;

    VerifySms m_sms;
};

