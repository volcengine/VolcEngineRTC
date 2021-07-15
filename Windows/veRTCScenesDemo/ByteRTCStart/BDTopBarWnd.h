//
//  BDTopBarWnd.h
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
#include "Utils.h"

class BDTopBarWnd : public BDWndImpl<BDTopBarWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDTopBarWnd")
    BDTopBarWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDTopBarWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_TIMER(OnTimer)
        COMMAND_ID_HANDLER(DUID_TOPBAR_LIST, OnClickListShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        memset(&m_rect, 0x00, sizeof(m_rect));
        auto font = CreateFont(12, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_shotfont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_bkBrush = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        m_grayPen = CreatePen(PS_SOLID, 1, RGB(0x4E, 0x59, 0x69));

        BDHMenu m;
        BDRect r(300, 20, 550, 60);
        BDString version = BDString(L"SDK版本 v") + rtcutil::ConvertUTF8ToBDString(VERSION);
        m_version.Create(m_hWnd, r, m, version, WS_CHILD | WS_VISIBLE | SS_RIGHT);
        m_version.SetFont(font);

        m_room.Create(m_hWnd, r, m, L"", WS_CHILD | SS_RIGHT);
        m_room.SetFont(font);
        m_user.Create(m_hWnd, r, m, L"", WS_CHILD);
        m_user.SetFont(font);
        m_time.Create(m_hWnd, r, m, L"", WS_CHILD | SS_LEFT);
        m_time.SetFont(font);

        BDRect rList(0, 0, 64, 20);
        m_list_show.Create(m_hWnd, rList, BDHMenu(DUID_TOPBAR_LIST), L"", WS_CHILD | WS_VISIBLE);
        m_list_show.SetNormal(IDB_LISTSHOW);
        m_list_show.SetHover(IDB_LISTHIDEN);
        m_list_show.SetDisable(IDB_LISTHIDEN);
        m_list_show.SetID(DUID_TOPBAR_LIST);

        BDRect rRecording(0, 0, 41, 20);
        m_recording.Create(m_hWnd, rRecording, BDHMenu(), L"", WS_CHILD | WS_VISIBLE);
        m_recording.SetNormal(IDB_RECORDING);
        m_recording.SetHover(IDB_RECORDING);

        m_list_show.ShowWindow(SW_HIDE);
        m_recording.ShowWindow(SW_HIDE);

        rtcutil::LoadFile(L"resource\\topbar_head.png", m_head);
        m_frame_title.LoadBitmap(IDB_FFRAME_TITLE);
        return 0;
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic)
    {
        if (wndStatic == m_version)
        {
            dc.SetBkColor(RGB(0x1D, 0x21, 0x29));
            dc.SetTextColor(RGB(0x86, 0x90, 0x9c));
        }
        else if (wndStatic == m_user
            || wndStatic == m_room
            || wndStatic == m_time)
        {
            dc.SetBkColor(RGB(0x1D, 0x21, 0x29));
            dc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
        }
        return (HBRUSH)m_bkBrush;
    }

    void OnSize(UINT nType, BDSize size)
    {
        m_version.MoveWindow(200, 15, size.cx - 200 - 24, 40);
        m_user.MoveWindow(size.cx - m_user_name_extent_len - 24, 18, m_user_name_extent_len, 40);
        m_room.MoveWindow(30 + 156, 20, size.cx / 2 - 8 - (30 + 156), 40);
        m_time.MoveWindow(size.cx / 2 + 8, 20, 56, 40);
        m_list_show.MoveWindow(size.cx / 2 + 8 + 56, 15, 64, 20);
        m_recording.MoveWindow(size.cx / 2 + 8 + 56 + 64 + 24, 15, 41, 20);
    }

    void ShowRoomInfo(BDString strRoomName, BDString strUserName) {
        m_version.ShowWindow(SW_HIDE);
        m_room.ShowWindow(SW_SHOW);
        m_time.ShowWindow(SW_SHOW);
        //m_list_show.ShowWindow(SW_SHOW);
        //m_recording.ShowWindow(SW_SHOW);
        m_user.ShowWindow(SW_SHOW);
        m_showHeadIcon = true;
        m_room.SetWindowText(L"房间ID: " + strRoomName);
        m_user.SetWindowText(strUserName);
        m_user_name = strUserName;

        SIZE size;
        BDPaintDC dc(m_user.m_hWnd);
        dc.GetTextExtent(strUserName, strUserName.GetLength(), &size);
        m_user_name_extent_len = size.cx;

        RECT rc;
        GetClientRect(&rc);
        m_user.MoveWindow(rc.right - m_user_name_extent_len - 24, 18, m_user_name_extent_len, 40);
       
        m_time.SetWindowTextW(L"00:00");
        m_second_tick = rtcutil::GetTimestamp();

        SetTimer(0, 1000);
        Invalidate();
    }

    void ShowVersionInfo() {
        m_version.ShowWindow(SW_SHOW);
        m_room.ShowWindow(SW_HIDE);
        m_time.ShowWindow(SW_HIDE);
        m_list_show.ShowWindow(SW_HIDE);
        m_recording.ShowWindow(SW_HIDE);
        m_user.ShowWindow(SW_HIDE);
        m_showHeadIcon = false;

        const char* version = EngineWrapper::GetInstance()->getVersion();
        BDString str;
        str.Format(L"Demo版本 v%s / SDK版本 %s",
            rtcutil::ConvertUTF8ToBDString(VERSION),
            rtcutil::ConvertUTF8ToBDString(version));
        m_version.SetWindowText(str);

        KillTimer(0);
        Invalidate();
    }

    LRESULT OnClickListShow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (m_list_Show_click) {
            m_list_Show_click();
        }
        return 0;
    }

    void ListShow(bool show, int icon) {
        if (m_list_show.IsWindowVisible() != show) {
            m_list_show.SetNormal(icon);
            m_list_show.SetHover(icon);
            m_list_show.ShowWindow(show ? SW_SHOW : SW_HIDE);
        }
    }

    void RecordShow(bool show) {
        m_recording.ShowWindow(show ? SW_SHOW : SW_HIDE);
    }

    bool IsVideoRecording() {
        return m_recording.IsWindowVisible();
    }

    void TimeSynchronization(int64_t meeting_start_time, int64_t server_now) {
        m_time_syn_delta = (server_now - meeting_start_time) / 1000000000;
        OnTimer(0);
    }

    void OnListShowClick(std::function<void()> action) {
        m_list_Show_click = action;
    }

    void OnTimer(UINT_PTR time_id) {
        auto distance = rtcutil::GetTimestamp() - m_second_tick + m_time_syn_delta;
        int minute = distance / 60;
        int second = distance % 60;
        int hour = minute / 60;

        BDString time;
        if (hour <= 0) {
            time.Format(L"%02d:%02d", minute, second);
        }
        else {
            time.Format(L"%d:%02d:%02d", hour, minute, second);
        }
        m_time.SetWindowTextW(time);
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);

        BDDC mydc = ::CreateCompatibleDC(dc);
        mydc.SelectBitmap(m_frame_title);
        dc.BitBlt(30, (rc.bottom - 20) /2, 156, 20, mydc, 0, 0, SRCCOPY);

        if (m_showHeadIcon)
        {
            //draw line
            dc.SelectPen((HPEN)m_grayPen);
            int x0 = rc.right / 2;
            int y0 = 19;
            int x1 = rc.right / 2;
            int y1 = rc.bottom - 19;

            dc.MoveTo(x0, y0);
            dc.LineTo(x1, y1);

            SIZE size = {0, 0};
            if (m_head) {
                size.cx = m_head->GetWidth();
                size.cy = m_head->GetHeight();

                rtcutil::DrawImage(dc.m_hDC, m_head,
                    rc.right - m_user_name_extent_len - size.cx - 24 - 8,
                    12,
                    size.cx,
                    size.cy);
            }

            if (m_user_name.GetLength()) {
                dc.SetBkMode(TRANSPARENT);
                dc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
                dc.SetBkColor(RGB(0x4E, 0x59, 0x69));
                dc.SelectFont(m_shotfont);

                wchar_t c = m_user_name[0];
                if (iswalpha(c)) {
                    c = towupper(c);
                }

                SIZE t_size;
                dc.GetTextExtent(&c, 1, &t_size);

                RECT rText = { rc.right - m_user_name_extent_len - size.cx - 24 - 8 + (size.cx - t_size.cx) / 2,
                12 + +(size.cy - t_size.cy) / 2,
                rc.right - m_user_name_extent_len - size.cx - 24 - 8 + (size.cx + t_size.cx) / 2,
                12 + +(size.cy + t_size.cy) / 2 };
                ::DrawText(dc.m_hDC, &c, 1, &rText, DT_CENTER | DT_TOP);
            }
        }

        m_user.Invalidate();
        return 0;
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

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
    {
        return 0;
    }

    BDPen m_grayPen;
    BDBrush m_bkBrush;
    BDStatic m_version;

    BDFont m_shotfont;
    BDFont m_roomfont;
    BDFont m_userfont;
    BDStatic m_room;
    BDStatic m_user;
    BDStatic m_time;

    BDBmpButton m_list_show;
    BDBmpButton m_recording;

    Gdiplus::Image* m_head = nullptr;
    BDBitmap m_frame_title;
    bool m_showHeadIcon = false;

    UINT m_second_tick = 0;
    int m_user_name_extent_len = 80;
    BDString m_user_name;

    std::function<void()> m_list_Show_click;
    int m_time_syn_delta = 0;
    RECT m_rect;
};

