//
//  BDUserViewWnd.h
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
#include "BDUserTitleWnd.h"

#include <gdiplus.h>

class BDUserVideoViewWnd : public BDWndImpl<BDUserVideoViewWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDRemoteWnd")
    BDUserVideoViewWnd(bool mask) : m_mask(mask){
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = nullptr;// CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDUserViewWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_TIMER(OnTimer)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_NOTIFY_VIDEO, OnVideoFrame)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        memset(&m_invalidataRect, 0x00, sizeof(m_invalidataRect));
        memset(&m_rect, 0x00, sizeof(m_rect));

        rtcutil::LoadFile(L"resource\\highlight_circular.png", m_highlight_circular);
        rtcutil::LoadFile(L"resource\\highlight_rectangle.png", m_highlight_rectangle);
        m_bkColor = RGB(0x1D, 0x21, 0x29);
        m_bkBrush = ::CreateSolidBrush(m_bkColor);

        BDHMenu m;
        BDRect r(0, 0, 134, 20);
        m_userTitleWnd.Create(m_hWnd, &r, m, 0, WS_CHILD | WS_CLIPCHILDREN);

        m_host_image.LoadBitmap(IDB_HOST);
        m_share_image.LoadBitmap(IDB_USER_SHARE);
        m_namefont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_shotfont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        return 0;
    }

    void OnDestroy() { // when destroy, it need Unsubscribe
        m_userTitleWnd.DestroyWindow();
        m_have_stream = false;
        SubScribeStream(false);
        UnboundView();
    }

    void OnFrameShow(BOOL show, int lParam) {
        ResetUserTitle(show);
        SubScribeStream(show);
        FreshTimer(show);
        FreshFirstVideoFrameTimer(show);
        Invalidate();
    }

    void OnSize(UINT nType, BDSize size) {
        bool show = IsWindowVisible();
        ResetUserTitle(show);
        FreshFirstVideoFrameTimer(show);
    }

    void SetBackBrushColor(COLORREF color) {
        if (m_bkColor != color) {
            if (!m_bkBrush.IsNull()) {
                m_bkBrush.DeleteObject();
            }

            m_bkColor = color;
            m_bkBrush = ::CreateSolidBrush(color);
        }
    }

    void SetHeader(const BDString& icon, int font_size) {
        if (m_head) {
            delete m_head;
            m_head = nullptr;
        }

        if (icon.GetLength()) {
            rtcutil::LoadFile(icon, m_head);
        }

        if (!m_shotfont.IsNull()) {
            m_shotfont.DeleteObject();
        }
        m_shotfont = CreateFont(font_size, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");

        Invalidate();
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        if ((m_mask && (!m_showHeader && !m_highlight) && m_first_video_frame)
            || (!m_mask && !m_showHeader && !m_show_fresh)) {
            return 0;
        }

        m_show_fresh = false;

        RECT rc;
        GetClientRect(&rc);
        BDDC localDc = ::CreateCompatibleDC(dc); // Double buffering
        auto hBitmap = ::CreateCompatibleBitmap(dc, rc.right, rc.bottom);
        ::SelectObject(localDc, hBitmap);

        localDc.FillRect(&rc, m_bkBrush);
        if (m_showHeader && m_head) {
            SIZE size;
            size.cx = m_head->GetWidth();
            size.cy = m_head->GetHeight();

            localDc.SetBkMode(TRANSPARENT);
            localDc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
            localDc.SetBkColor(m_bkColor);
            localDc.SelectFont(m_namefont);

            SIZE text_size;
            ::GetTextExtentPoint(localDc.m_hDC, m_name, m_name.GetLength(), &text_size);
            RECT rText = { (rc.right - text_size.cx) / 2,
                (rc.bottom - size.cy) / 2 + size.cy - 4,
                (rc.right + text_size.cx) / 2,
                rc.bottom };

            BDDC mydc = ::CreateCompatibleDC(localDc);
            if (m_share && m_name.GetLength()) {
                SIZE image;
                m_share_image.GetSize(image);
                rText.left = max(8 + image.cx + 8, rText.left);

                mydc.SelectBitmap(m_share_image);
                localDc.BitBlt(rText.left - 8 - image.cx, rText.top, image.cx, image.cy, mydc, 0, 0, SRCCOPY);
            }

            if (m_host && m_name.GetLength()) {
                SIZE image;
                m_host_image.GetSize(image);
                rText.right = min(rc.right - 8 - image.cx - 8, rText.right);

                mydc.SelectBitmap(m_host_image);
                localDc.BitBlt(rText.right + 8, rText.top, image.cx, image.cy, mydc, 0, 0, SRCCOPY);
            }

            ::DrawText(localDc.m_hDC, m_name, m_name.GetLength(), &rText, DT_LEFT | DT_TOP);

            int delta = 0;
            if (m_highlight) {
                delta = 2;
                rtcutil::DrawImage(localDc.m_hDC, m_highlight_circular,
                    (rc.right - size.cx) / 2,
                    (rc.bottom - size.cy) / 2 - size.cy / 3 + 4,
                    size.cx,
                    size.cy);
            }

            rtcutil::DrawImage(localDc.m_hDC, m_head,
                (rc.right - size.cx) / 2 + delta,
                (rc.bottom - size.cy) / 2 - size.cy / 3 + delta + 4,
                size.cx - 2 * delta,
                size.cy - 2 * delta);

            if (m_name.GetLength()) {
                localDc.SetBkMode(TRANSPARENT);
                localDc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
                localDc.SetBkColor(RGB(0x4E, 0x59, 0x69));
                localDc.SelectFont(m_shotfont);

                wchar_t c = m_name[0];
                if (iswalpha(c)) {
                    c = towupper(c);
                }

                SIZE t_size;
                ::GetTextExtentPoint(localDc.m_hDC, &c, 1, &t_size);

                RECT rText = { (rc.right - size.cx) / 2 + (size.cx - t_size.cx )/ 2,
                (rc.bottom - size.cy) / 2 - size.cy / 3 + (size.cy - t_size.cy) / 2 + 4,
                (rc.right - size.cx) / 2 + size.cx,
                (rc.bottom - size.cy) / 2 + size.cy * 2 / 3 };
                ::DrawText(localDc.m_hDC, &c, 1, &rText, DT_LEFT | DT_TOP);
            }
        }
        else if (m_highlight) {
            rtcutil::DrawImage(localDc.m_hDC, m_highlight_rectangle,
                m_invalidataRect.left,
                m_invalidataRect.top,
                m_invalidataRect.right,
                m_invalidataRect.bottom);
        }

        dc.BitBlt(0, 0, rc.right, rc.bottom, localDc, 0, 0, SRCCOPY);
        DeleteObject(hBitmap);
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
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

    void MuteVideo(bool mute) {
        if (m_showHeader != mute) {
            m_showHeader = mute;
            bool show = IsWindowVisible();
            ResetUserTitle(show);
            SubScribeStream(show);

            FreshTimer(show);
            Invalidate();
        }
    }

    void SetHost(bool host) {
        if (m_host != host) {
            m_host = host;
            bool show = IsWindowVisible();
            ResetUserTitle(show);
        }
    }

    void SetShare(bool share) {
        if (m_share != share) {
            m_share = share;
            bool show = IsWindowVisible();
            ResetUserTitle(show);
        }
    }

    void SetName(const BDString& name) {
        if (m_name != name) {
            m_name = name;
            bool show = IsWindowVisible();
            ResetUserTitle(show);
            Invalidate();
        }
    }

    void SetUserId(const std::string& id) {
        m_user_id = id;
    }

    const std::string& GetUserId() const {
        return m_user_id;
    }

    void TitleFresh() {
        m_userTitleWnd.Invalidate();
    }

    void SetUserType(UserType type) {
        m_type = type;
    }

    void Highlight(bool on) {
        if (m_highlight != on) {
            m_highlight = on;
            if (m_showHeader || m_mask) {
                Invalidate();
            }
        }
    }

    bool IsHightlight() {
        return m_highlight;
    }

    void HighlightRectangle(const RECT& rect, bool on) {
        if (m_invalidataRect.left != rect.left
            || m_invalidataRect.top != rect.top
            || m_invalidataRect.right != rect.right
            || m_invalidataRect.bottom != rect.bottom
            || m_highlight != on) {

            m_highlight = on;
            m_invalidataRect = rect;
            Invalidate();
        }
    }
 
    void OnStreamAdd() {
        m_have_stream = true;
        bool show = IsWindowVisible();
        SubScribeStream(show);
        FreshFirstVideoFrameTimer(show);
    }

    void OnStreamRemove() {
        m_have_stream = false;
        m_first_video_frame = false;
        bool show = IsWindowVisible();
        SubScribeStream(show);
    }

    void SetupLocal(bool show) {
         EngineWrapper::GetInstance()->setupLocal(show ? m_hWnd : nullptr, m_user_id.c_str());
    }

    void SetScreenViewTag() {
        m_screen_view = true;
    }

    const bool GetScreenViewTag() const {
        return m_screen_view;
    }

    void Reset() {
        m_showHeader = false;
        m_have_stream = false;
        m_highlight = false;
        m_first_video_frame = false;
        FreshFirstVideoFrameTimer(false);
    }

private:
    void SubScribeStream(bool show) {
        if (!m_user_id.empty() && m_type == REMOTE_USER) {
            bool subVideo = (m_screen_view || !m_showHeader) && m_have_stream && show;
            if (subVideo) {
                EngineWrapper::GetInstance()->SubscribeVideoStream(m_user_id.c_str(), { m_screen_view, subVideo });
            } else {
                EngineWrapper::GetInstance()->UnsubscribeVideoStream(m_user_id.c_str(), m_screen_view);
                m_first_video_frame = false;
                FreshFirstVideoFrameTimer(show);
            }
        }
    }

    // The first frame event cannot be received after reconnection
    LRESULT OnVideoFrame(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (!m_first_video_frame) {
            m_first_video_frame = true;
            bool show = IsWindowVisible();
            FreshFirstVideoFrameTimer(show);

            if (!m_user_id.empty() && m_type == REMOTE_USER) {
                if (m_screen_view) {
                    EngineWrapper::GetInstance()->setupRemoteScreenRender(m_user_id, m_hWnd);
                }
                else {
                    EngineWrapper::GetInstance()->setupRemote(m_hWnd, m_user_id.c_str());
                }
            }
        }

        SetTimer(2, 1000);
        return 0;
    }

    void UnboundView() {
        if (!m_user_id.empty()) {
            if (m_type == REMOTE_USER) {
                if (m_screen_view) {
                    EngineWrapper::GetInstance()->setupRemoteScreenRender(m_user_id, nullptr);
                }
                else {
                    EngineWrapper::GetInstance()->setupRemote(nullptr, m_user_id.c_str());
                }
            }
            else {
                //EngineWrapper::GetInstance()->setupLocal(nullptr, m_user_id.c_str());
            }
        }
    }

    void ResetUserTitle(bool show) {
        BDFont namefont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");

        BDPaintDC dc(m_hWnd);
        dc.SelectFont(namefont);

        SIZE text_size;
        ::GetTextExtentPoint(dc.m_hDC, m_name, m_name.GetLength(), &text_size);

        RECT rect;
        GetClientRect(&rect);
        int total_width = text_size.cx;
        if (m_share) {
            SIZE image;
            m_share_image.GetSize(image);
            total_width += image.cx;
        }

        if (m_host) {
            SIZE image;
            m_host_image.GetSize(image);
            total_width += image.cx;
        }

        if (total_width < 134) {
            total_width = 134;
        }

        if (total_width > rect.right) {
            total_width = rect.right;
        }
        m_userTitleWnd.MoveWindow(rect.right - total_width, rect.bottom - 22, total_width, 22);

        m_userTitleWnd.SetHost(m_host);
        m_userTitleWnd.SetShare(m_share);
        m_userTitleWnd.SetName(m_name);

        m_userTitleWnd.ShowWindow(m_name.GetLength() && !m_screen_view && !m_showHeader && show ? SW_SHOW : SW_HIDE);
        m_userTitleWnd.Invalidate();
    }

    void FreshTimer(bool show) {
        if (show && m_showHeader && !m_screen_view) {
            SetTimer(0, 2000);
        } else {
            KillTimer(0);
        }
    }

    void FreshFirstVideoFrameTimer(bool show) {
        if (!m_mask && show && !m_showHeader && !m_first_video_frame) {
            m_show_fresh = true;
            Invalidate();
            SetTimer(1, 500);
        }
        else {
            KillTimer(1);
        }

        if (m_showHeader || !show) {
            KillTimer(2);
        }
    }

    void OnTimer(UINT_PTR time_id) {
        if(time_id == 0){
            bool show = IsWindowVisible();
            if (show && m_showHeader) {
                Invalidate();
                KillTimer(0);
            }
        }
        else if (time_id == 1 || time_id == 2) {
            m_show_fresh = true;
            Invalidate();
        }
    }

    std::string m_user_id;
    BDString m_name;
    bool m_showHeader = false;
    bool m_highlight = false;
    bool m_host = false;
    bool m_share = false;
    bool m_mask;
    bool m_screen_view = false;
    bool m_have_stream = false;

    RECT m_invalidataRect;
    UserType m_type = REMOTE_USER;
    BDFont m_namefont;
    BDFont m_shotfont;
    BDBrush m_bkBrush;
    COLORREF m_bkColor;
    Gdiplus::Image* m_head = nullptr;
    Gdiplus::Image* m_highlight_circular = nullptr;
    Gdiplus::Image* m_highlight_rectangle = nullptr;

    BDUserTitleWnd m_userTitleWnd;
    BDBitmap m_host_image;
    BDBitmap m_share_image;

    RECT m_rect;
    bool m_show_fresh = false;
    bool m_first_video_frame = false;
};

