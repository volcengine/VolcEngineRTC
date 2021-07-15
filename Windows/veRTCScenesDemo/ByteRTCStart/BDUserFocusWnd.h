//
//  BDWarningWnd.h
//
//  Copyright 2021. All rights reserved.
//

#pragma once

#include "resource.h"
#include "BDWinApp.h"
#include "BDWnd.h"
#include "BDCrack.h"
#include "BDGDI.h"
#include "BDCtrl.h"
#include "ByteMessage.h"
#include "BDTipsWnd.h"
#include "Utils.h"
#include <functional>

#define TIPSWIDTH 84
#define TIPSHIGHT 38

class BDUserFocusWnd : public BDWndImpl<BDUserFocusWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDUserFocusWnd")
    BDUserFocusWnd()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
            wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        }
    }

    BEGIN_MSG_MAP(BDUserFocusWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_nameFont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_bkBrush = CreateSolidBrush(RGB(0x27, 0x2E, 0x3B));

        rtcutil::LoadFile(L"resource\\head_speaker_shared.png", m_head);
        m_hostTransfer.LoadBitmap(IDB_HOST_TRANSFER);

        rtcutil::LoadFile(L"resource\\audio_enable.png", m_audio);
        rtcutil::LoadFile(L"resource\\audio_disable.png", m_audioDisable);

        BDHMenu m;
        BDRect r(0, 0, TIPSWIDTH, TIPSHIGHT);
        m_tipsWnd.Create(m_hWnd, &r, m, 0, WS_POPUP);
        POINT p[7] = { {0, 0}, {TIPSWIDTH , 0}, {TIPSWIDTH, TIPSHIGHT - 8},{TIPSWIDTH * 3 / 4 + 8, TIPSHIGHT - 8}, {TIPSWIDTH *3 / 4 , TIPSHIGHT}, {TIPSWIDTH *3 / 4 - 8, TIPSHIGHT - 8}, {0 , TIPSHIGHT - 8} };
        HRGN hrgn = ::CreatePolygonRgn(p, 7, 1);
        m_tipsWnd.SetWindowRgn(hrgn);

        m_tipsWnd.SetInfo(m_nameFont, RGB(0x1D, 0x21, 0x29), RGB(0xFF, 0xFF, 0xFF));
        m_tipsWnd.SetHint("移交主持人");

        m_abbreviationFont = CreateFont(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {
    }

    void OnMouseMove(UINT w, BDPoint point) {
        m_mouse_captured = true;

        RECT rect;
        GetClientRect(&rect);
        RECT m_audio_rect{ rect.right - 64, 18, rect.right - 64 + 16, 18 + 16 };
        RECT m_transfer_rect{ rect.right - 40, 14, rect.right - 40 + 24, 14 + 24 };

        bool last_audio_hover = m_audio_hover;
        bool last_transfer_hover = m_transfer_hover;
        m_audio_hover = false;
        m_transfer_hover = false;

        if (point.x >= m_audio_rect.left && point.x <= m_audio_rect.right
            && point.y >= m_audio_rect.top && point.y <= m_audio_rect.bottom) {
            m_audio_hover = true;
        }

        if (point.x >= m_transfer_rect.left && point.x <= m_transfer_rect.right
            && point.y >= m_transfer_rect.top && point.y <= m_transfer_rect.bottom) {
            m_transfer_hover = true;

            RECT rc;
            ::GetWindowRect(m_hWnd, &rc);
            m_tipsWnd.MoveWindow(rc.right - TIPSWIDTH - 9,
                rc.top - TIPSHIGHT,
                TIPSWIDTH, TIPSHIGHT);
            m_tipsWnd.ShowWindow(SW_SHOW);
            m_tipsWnd.BringWindowToTop();
        }

        if (m_audio_hover || m_transfer_hover) {
            SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_HAND));
        }
        else {
            SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
            m_tipsWnd.ShowWindow(SW_HIDE);
        }

        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = m_hWnd;

        ::TrackMouseEvent(&tme);
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        UserAttr user = m_user;
        if (m_audio_hover && m_auidoMuteCallback) {
            m_auidoMuteCallback(user);
        }

        if (m_transfer_hover && m_hostTranferCallback) {
            m_hostTranferCallback(user);
        }
    }

    void OnMouseLeave() {
        m_mouse_captured = false;
        m_audio_hover = false;
        m_transfer_hover = false;
        ShowWindow(SW_HIDE);
    }

    bool IsMouseCaptured() {
        return m_mouse_captured;
    }

    void SetAudioMuteHanlder(std::function<void(const UserAttr&)> callback) {
        m_auidoMuteCallback = callback;
    }

    void SetHostTranferHanlder(std::function<void(const UserAttr&)> callback) {
        m_hostTranferCallback = callback;
    }

    void SetUserInfo(const UserAttr& user) {
        bool change = m_user.m_bAudio != user.m_bAudio
            || m_user.m_name != user.m_name;
        m_user = user;
        if (change) {
            RECT rect;
            GetClientRect(&rect);
            RECT audio_rect{ rect.right - 64, 18, rect.right - 64 + 16, 18 + 16 };
            InvalidateRect(&audio_rect);
        }
    }

    const UserAttr& GetUserInf() const {
        return m_user;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rect;
        GetClientRect(&rect);
        dc.FillRect(&rect, m_bkBrush);

        //Draw Head
        rtcutil::DrawImage(dc.m_hDC, m_head,
            16,
            10,
            28,
            28);

        dc.SelectFont(m_abbreviationFont);
        wchar_t n = m_user.m_name[0];
        if (iswalpha(n)) {
            n = towupper(n);
        }
        SIZE size;
        ::GetTextExtentPoint(dc.m_hDC, &n, 1, &size);

        RECT rText = {
                16,
                10 + (28 - size.cy) / 2,
                16 + 28,
                1028
        };
        ::DrawText(dc.m_hDC, &n, 1, &rText, DT_CENTER | DT_VCENTER);

        //Draw Name
        auto name = m_user.m_name;
        if (name.GetLength() > 12) {
            name = name.Left(12);
            name += L"...";
        }

        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
        dc.SelectFont(m_nameFont);
        rText = { 52, 18, 160, 50 };
        ::DrawText(dc.m_hDC, name, name.GetLength(), &rText, DT_LEFT | DT_VCENTER);

        rtcutil::DrawImage(dc.m_hDC, m_user.m_bAudio ? m_audio : m_audioDisable, rect.right - 16 - 16 - 16 - 16, 18, 16, 16);

        //Draw transfer
        BDDC mydc = ::CreateCompatibleDC(dc);
        mydc.SelectBitmap(m_hostTransfer);
        dc.BitBlt(rect.right - 16 - 24, 14, 24, 24, mydc, 0, 0, SRCCOPY);

        return 0;
    }

protected:
    BDFont m_nameFont;
    BDFont m_abbreviationFont;
    BDBrush m_bkBrush;

    Gdiplus::Image* m_head = nullptr;
    BDBitmap m_hostTransfer;
    BDTipsWnd m_tipsWnd;

    bool m_mouse_captured = false;

    bool m_bAudio = true;

    bool m_audio_hover = false;
    bool m_transfer_hover = false;

    Gdiplus::Image* m_audio = nullptr;
    Gdiplus::Image* m_audioDisable = nullptr;

    UserAttr m_user;
    std::function<void(const UserAttr&)> m_auidoMuteCallback;
    std::function<void(const UserAttr&)>  m_hostTranferCallback;
};

