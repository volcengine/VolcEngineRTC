//
//  BDButton.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once

#include "resource.h"
#include "BDCrack.h"
#include "BDMisc.h"
#include "BDWinApp.h"
#include "BDGDI.h"
#include "BDWnd.h"
#include "Utils.h"
#include <gdiplus.h>
#include <functional>

class BDPngButton : public BDWndImpl<BDPngButton>
{
    enum State{
        BUTTON_STATE_DEFAULT = 0,
        BUTTON_STATE_HOVER,
        BUTTON_STATE_ACTIVE
    };
public:
    DECLARE_BDWND_CLASS(L"BDPngButton")
    BDPngButton()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }

        m_state = BUTTON_STATE_DEFAULT;
    }

    ~BDPngButton() {
        if (m_bkDefaultImage)
        {
            delete m_bkDefaultImage;
            m_bkDefaultImage = nullptr;
        }

        if (m_bkHoverImage)
        {
            delete m_bkHoverImage;
            m_bkHoverImage = nullptr;
        }

        if (m_bkActiveImage)
        {
            delete m_bkActiveImage;
            m_bkActiveImage = nullptr;
        }

        if (m_bkImage)
        {
            delete m_bkImage;
            m_bkImage = nullptr;
        }
    }

    BEGIN_MSG_MAP(BDBmpButton)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_HAND));
        ShowCursor(TRUE);
        m_bkBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));

        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {

    }

    void OnMouseMove(UINT nFlags, BDPoint point) {
        if (m_state == BUTTON_STATE_DEFAULT) {
            m_state = BUTTON_STATE_HOVER;

            TRACKMOUSEEVENT trmouse;
            trmouse.cbSize = sizeof(TRACKMOUSEEVENT);
            trmouse.dwFlags = TME_LEAVE;
            trmouse.dwHoverTime = 2000;
            trmouse.hwndTrack = m_hWnd;
            if (!_TrackMouseEvent(&trmouse))
                return;

            Invalidate();
        }
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        m_state = BUTTON_STATE_HOVER;
        ::SendMessage(GetParent(), WM_COMMAND, m_id, 0);
        Invalidate();
    }

    void OnLButtonDown(UINT nFlags, BDPoint point) {
        m_state = BUTTON_STATE_ACTIVE;
        Invalidate();
    }

    void OnMouseLeave() {
        m_state = BUTTON_STATE_DEFAULT;
        Invalidate();
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);

        auto drawImage = [](BDPaintDC& dc, Gdiplus::Image* back, Gdiplus::Image* image, const RECT& rc) {
            rtcutil::DrawImage(dc.m_hDC, back, rc.left, rc.top, rc.right, rc.bottom);

            if (image) {
                INT w = image->GetWidth();
                INT h = image->GetHeight();

                rtcutil::DrawImage(dc.m_hDC, image,
                    (rc.right - w) / 2,
                    (rc.bottom - h) / 2,
                    w,
                    h);
            }
        };

        switch (m_state)
        {
        case BUTTON_STATE_DEFAULT:
            drawImage(dc, m_bkDefaultImage, m_bkImage, rc);
            break;
        case BUTTON_STATE_HOVER:
            drawImage(dc, m_bkHoverImage, m_bkImage, rc);
            break;
        case BUTTON_STATE_ACTIVE:
            drawImage(dc, m_bkActiveImage, m_bkImage, rc);
            break;
        default:
            break;
        }

        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return 0;
    }

    void SetDefault(const BDString& path) {
        if (m_bkDefaultImage)
        {
            delete m_bkDefaultImage;
            m_bkDefaultImage = nullptr;
        }

        rtcutil::LoadFile(path, m_bkDefaultImage);
        Invalidate();
    }

    void SetHover(const BDString& path) {
        if (m_bkHoverImage)
        {
            delete m_bkHoverImage;
            m_bkHoverImage = nullptr;
        }

        rtcutil::LoadFile(path, m_bkHoverImage);
        Invalidate();
    }

    void SetActive(const BDString& path) {
        if (m_bkActiveImage)
        {
            delete m_bkActiveImage;
            m_bkActiveImage = nullptr;
        }

        rtcutil::LoadFile(path, m_bkActiveImage);
        Invalidate();
    }

    void SetCenterImage(const BDString& path) {
        if (m_bkImage)
        {
            delete m_bkImage;
            m_bkImage = nullptr;
        }

        rtcutil::LoadFile(path, m_bkImage);
        Invalidate();
    }

    void SetID(int id) {
        m_id = id;
    }

    BDBitmap m_normal;
    BDBitmap m_hover;
    BDBitmap m_disable;
    int m_state;
    int m_id;
    HBRUSH m_bkBrush;

    Gdiplus::Image* m_bkDefaultImage = nullptr;
    Gdiplus::Image* m_bkHoverImage = nullptr;
    Gdiplus::Image* m_bkActiveImage = nullptr;
    Gdiplus::Image* m_bkImage = nullptr;
};