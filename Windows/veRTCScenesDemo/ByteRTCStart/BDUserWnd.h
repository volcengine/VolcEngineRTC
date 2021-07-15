//
//  BDUserWnd.h
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
#include "BDUsersVScrollWnd.h"

#define CAPTION_HEIGHT 50

class BDUserWnd : public BDWndImpl<BDUserWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDUserWnd")
    BDUserWnd()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x10, 0x13, 0x19));
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDUserWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        //MSG_WM_NCHITTEST(OnNcHitTest)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
        COMMAND_ID_HANDLER(DUID_CLOSE_USER, OnClickClose)
        COMMAND_ID_HANDLER(DUID_ALL_MUTE_USER, OnClickMuteAllRemoteUsers)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        memset(&m_rect, 0x00, sizeof(m_rect));
        allBk.CreateSolidBrush(RGB(0x10, 0x13, 0x19));

        m_muteAllFont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_font = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        BDHMenu m;
        BDRect r2(16, 16, 100, 40);
        m_title.Create(m_hWnd, r2, m, L"  参会人", WS_CHILD | WS_VISIBLE);
        m_title.SetFont(m_font);

        BDRect r(0, 0, 20, 20);
        m_close.Create(m_hWnd, r, BDHMenu(DUID_CLOSE_USER), L"", WS_CHILD | WS_VISIBLE);
        m_close.SetNormal(IDB_CLOSE);
        m_close.SetHover(IDB_CLOSE);
        m_close.SetID(DUID_CLOSE_USER);

        BDRect rAllMute(0, 0, 184, 32);
        m_allMute.Create(m_hWnd, r, BDHMenu(DUID_ALL_MUTE_USER), L"", WS_CHILD | WS_VISIBLE);
        //m_allMute.SetBackgroundColor(m_muteAllFont, RGB(0x27, 0x2E, 0x3B), RGB(0xFF, 0xFF, 0xFF), RGB(0x27, 0x2E, 0x3B), RGB(0xFF, 0xFF, 0xFF));
        m_allMute.SetNormal(IDB_ALL_MUTE);
        m_allMute.SetHover(IDB_ALL_MUTE);
        m_allMute.SetDisable(IDB_ALL_MUTE);
        m_allMute.SetID(DUID_ALL_MUTE_USER);
        m_allMute.ShowWindow(SW_HIDE);

        BDRect r3(0, 0, 216, 800);
        m_vscrollWnd.Create(m_hWnd, r3, m, L"", WS_CHILD | WS_VISIBLE | WS_OVERLAPPED);

        return 0;
    }

    void OnFrameShow(BOOL show, int lParam) {
        m_vscrollWnd.OnFrameShow(show, lParam);
    }

    LRESULT OnClickClose(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        ShowWindow(SW_HIDE);
        ::SendMessage(GetParent(), WM_NOTIFY_CLOSE_USER, 0, 0);
        return 0;
    }

    LRESULT OnClickMuteAllRemoteUsers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        if (m_muteAllRemoteUsers) {
            m_muteAllRemoteUsers();
        }
        return 0;
    }

    void OnSize(UINT nType, BDSize size) {
        m_title.MoveWindow(16, 16, 300, 40);
        m_close.MoveWindow(size.cx - 20 - 16, 16, 20, 20);
        m_vscrollWnd.MoveWindow(0, 50, size.cx, size.cy - 50 - 32 - 16);
        m_allMute.MoveWindow((size.cx - 248) / 2, size.cy - 32 - 16, 248, 32);
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_title) {
            dc.SetBkColor(RGB(0x10, 0x13, 0x19));
            dc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
        }
        return allBk;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        dc.SelectBrush(allBk);

        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, allBk);

        return 0;
    }

    UINT OnNcHitTest(BDPoint point)
    {
        ScreenToClient(&point);
        BDRect rc;
        GetClientRect(&rc);
        rc.bottom = 60;
        if (rc.PtInRect(point))
        {
            return HTCAPTION;
        }
        else
        {
            return HTCLIENT;
        }
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
    {
        return 0;
    }
    // only update share attribute
    void UpdateUser(const UserAttr& user) {
        if (m_vscrollWnd.IsMember(user.m_user_id)) {
            m_vscrollWnd.UpdateItem(user);
        }
        m_close.Invalidate();
    }

    void UpdateAllUsers(const std::list<UserAttr>& users) {
        m_vscrollWnd.UpdateAllUsers(users);
        if (!users.empty() && users.begin()->m_isHost) {
            m_allMute.ShowWindow(users.begin()->m_type == UserType::LOCAL_USER ? SW_SHOW : SW_HIDE);
        }
        m_close.Invalidate();
        BDString des;
        des.Format(L"  参会人（%d）", m_vscrollWnd.GetUserCount());
        m_title.SetWindowTextW(des);
    }

    void Clear() {
        m_vscrollWnd.Clear();
        BDString des;
        des.Format(L"  参会人（%d）", m_vscrollWnd.GetUserCount());
        m_title.SetWindowTextW(des);
    }

    void SetAudioMuteHanlder(std::function<void(const UserAttr&)> callback) {
        m_vscrollWnd.SetAudioMuteHanlder(callback);
    }

    void SetHostTranferHanlder(std::function<void(const UserAttr&)> callback) {
        m_vscrollWnd.SetHostTranferHanlder(callback);
    }

    void SetMuteAllRemoteUsers(std::function<void()> callback) {
        m_muteAllRemoteUsers = callback;
    }

    BOOL MoveWindowEx(int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE) {
        if (m_rect.left == x && m_rect.top == y
            && m_rect.right == nWidth && m_rect.bottom == nHeight) {
            return false;
        }

        m_rect.left = x;
        m_rect.top = y;
        m_rect.right = nWidth;
        m_rect.bottom = nHeight;

        return MoveWindow(x, y, nWidth, nHeight, bRepaint);
    }

private:
    BDUsersVScrollWnd m_vscrollWnd;

    BDFont m_muteAllFont;
    BDFont m_font;
    BDStatic m_title;
    BDBmpButton m_close;
    BDBmpButton m_allMute;
    RECT m_rect;

    BDBrush allBk;
    std::function<void()> m_muteAllRemoteUsers;
};

