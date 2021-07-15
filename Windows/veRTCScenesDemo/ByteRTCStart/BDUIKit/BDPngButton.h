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

class BDTxtPngButton : public BDWndImpl<BDTxtPngButton>
{
public:
    enum State {
        BUTTON_STATE_DEFAULT = 0,
        BUTTON_STATE_HOVER,
        BUTTON_STATE_ACTIVE,
        BUTTON_STATE_DISABLE,
    };

    DECLARE_BDWND_CLASS(L"BDTxtPngButton")
    BDTxtPngButton() {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = nullptr; // CreateSolidBrush(RGB(0x27, 0x2E, 0x3B));
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
        m_state = BUTTON_STATE_DEFAULT;
    }

    BEGIN_MSG_MAP(BDTxtButton)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_SETFOCUS, OnFocus)
        MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
        MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        m_bkBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        m_defaultTextColor = RGB(255, 255, 255);
        m_hoverTextColor = RGB(255, 255, 255);
        m_disableTextColor = RGB(255, 255, 255);
        m_txtfont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        ShowHandCursor();
        return 0;
    }

    void OnSize(UINT nType, BDSize size) {

    }

    void OnMouseMove(UINT nFlags, BDPoint point) {
        if (m_state != BUTTON_STATE_DISABLE && m_state != BUTTON_STATE_ACTIVE) {
            SetState(BUTTON_STATE_HOVER);

            TRACKMOUSEEVENT trmouse;
            trmouse.cbSize = sizeof(TRACKMOUSEEVENT);
            trmouse.dwFlags = TME_LEAVE;
            trmouse.dwHoverTime = 2000;
            trmouse.hwndTrack = m_hWnd;
            if (!_TrackMouseEvent(&trmouse))
                return;
        }
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        ::SendMessage(GetParent(), WM_COMMAND, m_id, 0);
        if (m_state != BUTTON_STATE_DISABLE) {
            SetState(BUTTON_STATE_HOVER);
        }
    }

    void OnLButtonDown(UINT nFlags, BDPoint point) {
        if (m_state != BUTTON_STATE_DISABLE) {
            SetState(BUTTON_STATE_ACTIVE);
        }
    }

    void OnMouseLeave() {
        if (m_state != BUTTON_STATE_DISABLE) {
            SetState(BUTTON_STATE_DEFAULT);
        }
    }

    void SetBackgroundColor(HFONT font,
        COLORREF backgroundColor,
        const BDString& default_image_path, COLORREF defaultTextColor,
        const BDString& hover_image_path, COLORREF hoverTextColor,
        const BDString& active_image_path, COLORREF activeTextColor,
        const BDString& disable_image_path, COLORREF disableTextColor) {
        if (!m_bkBrush.IsNull()) {
            m_bkBrush.DeleteObject();
        }

        m_bkBrush = CreateSolidBrush(backgroundColor);

        auto reloadImage = [this](Gdiplus::Image*& image, const BDString& path) {
            if (image) {
                delete image;
                image = nullptr;
            }

            rtcutil::LoadFile(path, image);
        };

        reloadImage(m_default_img, default_image_path);
        reloadImage(m_hover_img, hover_image_path);
        reloadImage(m_active_img, active_image_path);
        reloadImage(m_disable_img, disable_image_path);

        m_defaultTextColor = defaultTextColor;
        m_hoverTextColor = hoverTextColor;
        m_activeTextColor = activeTextColor;
        m_disableTextColor = disableTextColor;

        m_txtfont = font;
        Invalidate();
    }

    void ShowHandCursor() {
        SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_HAND));
        SetCursor(LoadCursor(NULL, IDC_HAND));
    }

    void ShowArrowCursor() {
        SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
        SetCursor(LoadCursor(NULL, IDC_ARROW));
    }

    LRESULT OnFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (m_state != BUTTON_STATE_DISABLE && m_state != BUTTON_STATE_ACTIVE) {
            SetState(BUTTON_STATE_HOVER);
        }
        return 0;
    }

    LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (m_state != BUTTON_STATE_DISABLE) {
            SetState(BUTTON_STATE_DEFAULT);
            Invalidate();
        }
        return 0;
    }

    LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (wParam == VK_RETURN) {
            OnLButtonUp(0, BDPoint());
        }
        return 0;
    }
    
    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rect;
        GetClientRect(&rect);

        auto drawBackground = [this](BDPaintDC& dc, Gdiplus::Image* image, COLORREF textColor, RECT& rect) {
            //if (m_last_draw_img == image) return;
            //m_last_draw_img = image;

            dc.FillRect(&rect, m_bkBrush);
            rtcutil::DrawImage(dc.m_hDC, image, rect.left, rect.top, rect.right, rect.bottom);

            dc.SetBkMode(TRANSPARENT);
            dc.SelectFont(m_txtfont);
            dc.SetTextColor(textColor);
            BDString title;
            GetWindowText(title);
            dc.DrawText((LPTSTR)(LPCTSTR)title, title.GetLength(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        };

        if (m_state != BDTxtPngButton::BUTTON_STATE_DISABLE && GetFocus() == m_hWnd) {
            drawBackground(dc, m_hover_img, m_hoverTextColor, rect);
        } else {
            switch (m_state)
            {
            case BDTxtPngButton::BUTTON_STATE_DEFAULT:
                drawBackground(dc, m_default_img, m_defaultTextColor, rect);
                break;
            case BDTxtPngButton::BUTTON_STATE_HOVER:
                drawBackground(dc, m_hover_img, m_hoverTextColor, rect);
                break;
            case BDTxtPngButton::BUTTON_STATE_ACTIVE:
                drawBackground(dc, m_active_img, m_hoverTextColor, rect);
                break;
            case BDTxtPngButton::BUTTON_STATE_DISABLE:
                drawBackground(dc, m_disable_img, m_disableTextColor, rect);
                break;
            default:
                break;
            }
        }
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return 0;
    }

    void SetState(State state) {
        if (m_state != state){
            m_state = state;
            if (m_state != BUTTON_STATE_DISABLE) {
                ShowHandCursor();
            }
            else {
                ShowArrowCursor();
            }
            Invalidate();
        }
    }

    void SetID(int id) {
        m_id = id;
    }

    int m_id;

    Gdiplus::Image* m_default_img = nullptr;
    Gdiplus::Image* m_hover_img = nullptr;
    Gdiplus::Image* m_active_img = nullptr;
    Gdiplus::Image* m_disable_img = nullptr;
    Gdiplus::Image* m_last_draw_img = nullptr;

    COLORREF m_defaultTextColor;
    COLORREF m_hoverTextColor;
    COLORREF m_activeTextColor;
    COLORREF m_disableTextColor;
    BDBrush m_bkBrush;
    BDFont m_txtfont;

    State m_state = BUTTON_STATE_DEFAULT;
};