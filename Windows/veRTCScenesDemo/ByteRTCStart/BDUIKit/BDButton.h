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
#include <functional>

#ifdef _WIN64
#define GCL_HCURSOR         (-12)
#endif // _WIN64

enum {
    BUTTON_STATE_NORMAL,
    BUTTON_STATE_DISABLE
};

class BDBmpButton : public BDWndImpl<BDBmpButton>
{
public:
    DECLARE_BDWND_CLASS(L"BDBmpButton")
    BDBmpButton()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
        m_bHover = false;
        m_state = BUTTON_STATE_NORMAL;
    }

    BEGIN_MSG_MAP(BDBmpButton)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_LBUTTONUP(OnLButtonUp)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_HAND));
        ShowCursor(TRUE);
        m_bkBrush = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {

    }

    void OnMouseMove(UINT nFlags, BDPoint point) {
        if (!m_bHover) {
            m_bHover = true;
            if (m_hover_callback) {
                m_hover_callback(true, m_state);
            }

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
        ::SendMessage(GetParent(), WM_COMMAND, m_id, 0);
    }

    void OnMouseLeave() {
        m_bHover = false;
        if (m_hover_callback) {
            m_hover_callback(false, m_state);
        }
        Invalidate();
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);

        BDDC mydc = ::CreateCompatibleDC(dc);
        if (m_state == BUTTON_STATE_DISABLE) {
            BDBitmap old = mydc.SelectBitmap(m_disable);
            SIZE bsize;
            m_disable.GetSize(bsize);
            dc.BitBlt((rc.right - bsize.cx) / 2, (rc.bottom - bsize.cy)/2 , bsize.cx, bsize.cy, mydc, 0, 0, SRCCOPY);
            mydc.SelectBitmap(old);
        }
        else if (!m_normal.IsNull()) {
            if (m_bHover) {
                SIZE bsize;
                m_hover.GetSize(bsize);
                BDBitmap old = mydc.SelectBitmap(m_hover);
                dc.BitBlt((rc.right - bsize.cx) / 2, (rc.bottom - bsize.cy) / 2, bsize.cx, bsize.cy, mydc, 0, 0, SRCCOPY);
                mydc.SelectBitmap(old);
            }
            else {
                SIZE bsize;
                m_normal.GetSize(bsize);
                BDBitmap old = mydc.SelectBitmap(m_normal);
                dc.BitBlt((rc.right - bsize.cx) / 2, (rc.bottom - bsize.cy) / 2, bsize.cx, bsize.cy, mydc, 0, 0, SRCCOPY);
                mydc.SelectBitmap(old);
            }
        }
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return 0;
    }

    void SetNormal(int res) {
        if (m_normal.m_hBitmap != NULL)
        {
            m_normal.DeleteObject();
        }
        m_normal.LoadBitmap(res);
        Invalidate();
    }

    void SetHover(int res) {
        if (m_hover.m_hBitmap != NULL)
        {
            m_hover.DeleteObject();
        }
        m_hover.LoadBitmap(res);
        Invalidate();
    }

    void OnHover(std::function<void(bool, int)> callback) {
        m_hover_callback = callback;
    }

    void SetDisable(int res) {
        if (m_disable.m_hBitmap != NULL)
        {
            m_disable.DeleteObject();
        }
        m_disable.LoadBitmap(res);
        Invalidate();
    }

    void SetState(int state) {
        m_state = state;
        Invalidate();
    }

    void SetID(int id) {
        m_id = id;
    }

    bool m_bHover;
    BDBitmap m_normal;
    BDBitmap m_hover;
    BDBitmap m_disable;
    int m_state;
    int m_id;
    HBRUSH m_bkBrush;

    std::function<void(bool, int)> m_hover_callback;
};

class BDTxtButton : public BDWndImpl<BDTxtButton>
{
public:
    enum State {
        BUTTON_STATE_DEFAULT = 0,
        BUTTON_STATE_HOVER,
        BUTTON_STATE_ACTIVE,
        BUTTON_STATE_DISABLE,
    };

    DECLARE_BDWND_CLASS(L"BDTxtButton")
    BDTxtButton()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
        wci.m_wc.hbrBackground = nullptr;
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

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_backgroundBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        m_defaultBrush = CreateSolidBrush(RGB(47, 136, 255));
        m_hoverBrush = CreateSolidBrush(RGB(47, 136, 255));
        m_disableBrush = CreateSolidBrush(RGB(200, 200, 200));
        m_defaultTextColor = RGB(255, 255, 255);
        m_hoverTextColor = RGB(255, 255, 255);
        m_disableTextColor = RGB(255, 255, 255);
        m_txtfont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        ShowHandCursor();
        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {

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

            Invalidate();
        }
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        ::SendMessage(GetParent(), WM_COMMAND, m_id, 0);
        if (m_state != BUTTON_STATE_DISABLE) {
            SetState(BUTTON_STATE_HOVER);
            Invalidate();
        }
    }

    void OnLButtonDown(UINT nFlags, BDPoint point) {
        if (m_state != BUTTON_STATE_DISABLE) {
            SetState(BUTTON_STATE_ACTIVE);
            Invalidate();
        }
    }

    void OnMouseLeave() {
        if (m_state != BUTTON_STATE_DISABLE) {
            SetState(BUTTON_STATE_DEFAULT);
        }
    }

    LRESULT OnFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (m_state != BUTTON_STATE_DISABLE && m_state != BUTTON_STATE_ACTIVE) {
            SetState(BUTTON_STATE_HOVER);
        }
        return 0;
    }

    LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (m_state != BUTTON_STATE_DISABLE) {
            SetState(BUTTON_STATE_HOVER);
            SetState(BUTTON_STATE_DEFAULT);
        }
        return 0;
    }

    LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (wParam == VK_RETURN) {
            OnLButtonUp(0, BDPoint());
        }
        return 0;
    }

    void SetBackgroundColor(HFONT font,
        COLORREF backgroundColor,
        COLORREF defaultBrushColor, COLORREF defaultTextColor,
        COLORREF hoverBrushColor, COLORREF hoverTextColor,
        COLORREF activeBrushColor, COLORREF activeTextColor,
        COLORREF disableBrushColor, COLORREF disableTextColor) {
        m_defaultBrush = CreateSolidBrush(defaultBrushColor);
        m_hoverBrush = CreateSolidBrush(hoverBrushColor);
        m_activeBrush = CreateSolidBrush(activeBrushColor);
        m_disableBrush = CreateSolidBrush(disableBrushColor);
        m_defaultTextColor = defaultTextColor;
        m_hoverTextColor = hoverTextColor;
        m_activeTextColor = activeTextColor;
        m_disableTextColor = disableTextColor;

        m_txtfont = font;
        if (!m_backgroundBrush.IsNull()) {
            m_backgroundBrush.DeleteObject();
        }

        m_backgroundBrush = CreateSolidBrush(backgroundColor);
    }

    void ShowHandCursor() {
        SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_HAND));
        SetCursor(LoadCursor(NULL, IDC_HAND));
    }

    void ShowArrowCursor() {
        SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
        SetCursor(LoadCursor(NULL, IDC_ARROW));
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rect;
        GetClientRect(&rect);

        auto drawBackground = [this](BDPaintDC& dc, BDBrush& bkBrush, COLORREF textColor, RECT& rect) {
            //if (m_last_brush == &bkBrush) return;
            //m_last_brush = &bkBrush;

            dc.FillRect(&rect, m_backgroundBrush);

            dc.SelectPen((HPEN)GetStockObject(NULL_PEN));
            dc.SelectBrush((HBRUSH)bkBrush);
            dc.RoundRect(0, 0, rect.right - rect.left, rect.bottom - rect.top, 4, 4);
            dc.SetBkMode(TRANSPARENT);
            dc.SelectFont(m_txtfont);
            dc.SetTextColor(textColor);
            BDString title;
            GetWindowText(title);
            dc.DrawText((LPTSTR)(LPCTSTR)title, title.GetLength(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        };

        if (m_state != BDTxtButton::BUTTON_STATE_DISABLE && GetFocus() == m_hWnd) {
            drawBackground(dc, m_hoverBrush, m_hoverTextColor, rect);
        }
        else {
            switch (m_state)
            {
            case BDTxtButton::BUTTON_STATE_DEFAULT:
                drawBackground(dc, m_defaultBrush, m_defaultTextColor, rect);
                break;
            case BDTxtButton::BUTTON_STATE_HOVER:
                drawBackground(dc, m_hoverBrush, m_hoverTextColor, rect);
                break;
            case BDTxtButton::BUTTON_STATE_ACTIVE:
                drawBackground(dc, m_activeBrush, m_hoverTextColor, rect);
                break;
            case BDTxtButton::BUTTON_STATE_DISABLE:
                drawBackground(dc, m_disableBrush, m_disableTextColor, rect);
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
        m_state = state;
        if (m_state != BUTTON_STATE_DISABLE) {
            ShowHandCursor();
        }
        else {
            ShowArrowCursor();
        }
        Invalidate();
    }

    void SetID(int id) {
        m_id = id;
    }

    int m_id;

    BDBrush m_backgroundBrush;
    BDBrush m_defaultBrush;
    BDBrush m_hoverBrush;
    BDBrush m_activeBrush;
    BDBrush m_disableBrush;


    COLORREF m_defaultTextColor;
    COLORREF m_hoverTextColor;
    COLORREF m_activeTextColor;
    COLORREF m_disableTextColor;

    BDFont m_txtfont;

    State m_state = BUTTON_STATE_DEFAULT;
    BDBrush* m_last_brush = nullptr;
};

class BDTxtBorderButton : public BDWndImpl<BDTxtBorderButton>
{
public:
    DECLARE_BDWND_CLASS(L"BDTxtBorderButton")
    BDTxtBorderButton()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
        m_state = BUTTON_STATE_NORMAL;
    }

    BEGIN_MSG_MAP(BDTxtBorderButton)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_LBUTTONUP(OnLButtonUp)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_enableBrush = CreateSolidBrush(RGB(226, 234, 253));
        m_normalPen = CreatePen(PS_SOLID, 1, RGB(141, 173, 249));
        m_disableBrush = CreateSolidBrush(RGB(255, 255, 255));
        m_grayPen = CreatePen(PS_SOLID, 1, RGB(202, 202, 202));
        m_enableTextColor = RGB(141, 173, 249);
        m_disableTextColor = RGB(202, 202, 202);
        m_txtfont = CreateFont(18, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        ShowHandCursor();
        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {

    }

    void SetBackgroundColor(HFONT font, COLORREF enableBrushColor, COLORREF enableTextColor, COLORREF disableBrushColor, COLORREF disableTextColor) {
        m_enableBrush = CreateSolidBrush(enableBrushColor);
        m_disableBrush = CreateSolidBrush(disableBrushColor);
        m_enableTextColor = enableTextColor;
        m_disableTextColor = disableTextColor;

        m_txtfont = font;
    }

    void ShowHandCursor() {
        SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_HAND));
        SetCursor(LoadCursor(NULL, IDC_HAND));
    }

    void ShowArrowCursor() {
        SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
        SetCursor(LoadCursor(NULL, IDC_ARROW));
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        ::SendMessage(GetParent(), WM_COMMAND, m_id, 0);
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rect;
        GetClientRect(&rect);
        if (m_state == BUTTON_STATE_DISABLE) {
            dc.SelectPen((HPEN)m_grayPen);
            dc.SelectBrush((HBRUSH)m_disableBrush);
            dc.RoundRect(0, 0, rect.right - rect.left, rect.bottom - rect.top, 4, 4);
            dc.SetBkMode(TRANSPARENT);
            dc.SelectFont(m_txtfont);
            dc.SetTextColor(m_disableTextColor);
            BDString title;
            GetWindowText(title);
            dc.DrawText((LPTSTR)(LPCTSTR)title, title.GetLength(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        }
        else {
            dc.SelectPen((HPEN)m_normalPen);
            dc.SelectBrush((HBRUSH)m_enableBrush);
            dc.RoundRect(0, 0, rect.right - rect.left, rect.bottom - rect.top, 4, 4);
            dc.SetBkMode(TRANSPARENT);
            dc.SelectFont(m_txtfont);
            dc.SetTextColor(m_enableTextColor);
            BDString title;
            GetWindowText(title);
            dc.DrawText((LPTSTR)(LPCTSTR)title, title.GetLength(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        }
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return 0;
    }

    void SetState(int state) {
        m_state = state;
        Invalidate();
    }

    int GetState()
    {
        return m_state;
    }

    void SetID(int id) {
        m_id = id;
    }

    int m_state;
    int m_id;

    BDBrush m_enableBrush;
    BDBrush m_disableBrush;
    BDPen m_normalPen;
    BDPen m_grayPen;
    BDFont m_txtfont;
    COLORREF m_enableTextColor;
    COLORREF m_disableTextColor;
};
