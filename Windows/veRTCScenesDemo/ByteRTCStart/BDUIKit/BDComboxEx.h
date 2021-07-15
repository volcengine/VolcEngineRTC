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
#include "BDCtrl.h"
#include "BDWnd.h"
#include "Utils.h"
#include <gdiplus.h>
#include <functional>
#include <algorithm>
#include <list>

#define COMBOX_ARROW L"resource\\combox_arrow.png"
#define COMBOX_DELETE L"resource\\combox_delete.png"

struct ItemAttr {
    std::string title;
    void* data;
private:
    friend class BDComboxExDrop;
    int m_delta = 0;
};

#define ITEM_HEIGHT 36

class BDComboxExItemFocus : public BDWndImpl<BDComboxExItemFocus>
{
public:
    DECLARE_BDWND_CLASS(L"BDComboxExItemFocus")
    BDComboxExItemFocus()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
            wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0xF2, 0xF3, 0xF8));
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
        m_nameFont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Inter");
        m_bkBrush = CreateSolidBrush(RGB(0xF2, 0xF3, 0xF8));
        rtcutil::LoadFile(COMBOX_DELETE, m_delete);

        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {
    }

    void OnMouseMove(UINT w, BDPoint point) {
        m_mouse_captured = true;

        if (m_delete) {
            SIZE size;
            size.cx = m_delete->GetWidth();
            size.cy = m_delete->GetHeight();

            RECT rect;
            GetClientRect(&rect);
            RECT m_delete_rect{ rect.right - size.cx - 10, (rect.bottom - size.cy) / 2, rect.right - 10, (rect.bottom + size.cy) / 2 };

            m_delete_hover = false;

            if (point.x >= m_delete_rect.left && point.x <= m_delete_rect.right
                && point.y >= m_delete_rect.top && point.y <= m_delete_rect.bottom) {
                m_delete_hover = true;
            }

            SetClassLong(GCL_HCURSOR, (LONG)LoadCursor(NULL, m_delete_hover ? IDC_HAND : IDC_ARROW));
        }

        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = m_hWnd;

        ::TrackMouseEvent(&tme);
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        if (m_delete_hover && m_deleteCallback) {
            m_deleteCallback(m_item);
        }
        else if (m_selectCallback) {
            m_selectCallback(m_item);
        }

        ::ShowWindow(GetParent(), SW_HIDE);
    }

    void OnMouseLeave() {
        m_mouse_captured = false;
        m_delete_hover = false;
        ShowWindow(SW_HIDE);
    }

    bool IsMouseCaptured() {
        return m_mouse_captured;
    }

    void SetDeleteHanlder(std::function<void(const ItemAttr&)> callback) {
        m_deleteCallback = callback;
    }

    void SetSelectHandler(std::function<void(const ItemAttr&)> callback) {
        m_selectCallback = callback;
    }

    void SetItemInfo(const ItemAttr& item) {
        m_item = item;
        Invalidate();
    }

    const ItemAttr& GetUserInf() const {
        return m_item;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rect;
        GetClientRect(&rect);
        dc.FillRect(&rect, m_bkBrush);

        //Draw Name
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(0x1D, 0x21, 0x29));
        dc.SelectFont(m_nameFont);

        RECT rText = { 12, 8, rect.right, rect.bottom};
        ::DrawTextA(dc.m_hDC, m_item.title.c_str(), m_item.title.size(), &rText, DT_LEFT | DT_VCENTER);

        if (m_deleteCallback && m_delete) {
            auto w = m_delete->GetWidth();
            auto h = m_delete->GetHeight();
            rtcutil::DrawImage(dc.m_hDC, m_delete, rect.right - 10 - w, (rect.bottom - h) / 2, w, h);
        }

        return 0;
    }

protected:
    BDFont m_nameFont;
    BDBrush m_bkBrush;
    bool m_delete_hover = false;
    bool m_mouse_captured = false;
    Gdiplus::Image* m_delete = nullptr;
    ItemAttr m_item;
    std::function<void(const ItemAttr&)> m_deleteCallback;
    std::function<void(const ItemAttr&)> m_selectCallback;
};

class BDComboxExDrop : public BDWndImpl<BDComboxExDrop>
{
public:
    DECLARE_BDWND_CLASS(L"BDComboxExDrop")
    BDComboxExDrop()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDVScrollWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_MOUSEWHEEL(OnMouseWheel)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_grayPen = CreatePen(PS_SOLID, 1, RGB(0xE5, 0xE8, 0xEF));
        m_blackBrush.CreateSolidBrush(RGB(200, 200, 200));
        m_barBrush.CreateSolidBrush(RGB(104, 104, 104));
        allBk.CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));

        m_nameFont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Inter");

        BDHMenu m;
        BDRect r(0, 0, 216, ITEM_HEIGHT);
        m_itemFocusWnd.Create(m_hWnd, &r, m, 0, WS_CHILD | WS_CLIPCHILDREN);
        return 0;
    }

    void OnFrameShow(BOOL show, int lParam) {
        m_vscroll_pos = 0;
        m_vscroll_range = -1;
        m_itemFocusWnd.ShowWindow(SW_HIDE);

        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    void OnSize(UINT nType, BDSize size)
    {
        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    LRESULT OnMouseWheel(UINT nFlags, short zDelta, BDPoint point) {
        int times = zDelta / WHEEL_DELTA;
        auto dy = -times * ITEM_HEIGHT;
        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(dy, rect, false);

        OnMouseMove(0, point);
        return 0;
    }

    void OnMouseLeave() {
        if (!m_itemFocusWnd.IsMouseCaptured()) {
            m_itemFocusWnd.ShowWindow(SW_HIDE);
        }
    }

    LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (!m_parent_hover) {
            ShowWindow(SW_HIDE);
            m_itemFocusWnd.ShowWindow(SW_HIDE);
        }
        return 0;
    }

    void SetParentHover(bool hover) {
        m_parent_hover = hover;
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        return allBk;
    }

    void OnMouseMove(UINT w, BDPoint point) {
        RECT client_rect;
        GetClientRect(&client_rect);

        bool find = false;
        for (auto& item : m_items) {
            if (item.m_delta + ITEM_HEIGHT < 0) {
                continue;
            }
            else if (item.m_delta > client_rect.bottom) {
                break;
            }

            if ((point.y > item.m_delta && point.y < item.m_delta + ITEM_HEIGHT)) {
                m_itemFocusWnd.MoveWindow(0, item.m_delta, client_rect.right - (m_vscroll_range ? 10 : 0), ITEM_HEIGHT);
                m_itemFocusWnd.SetItemInfo(item);

                if (!m_itemFocusWnd.IsWindowVisible()) {
                    m_itemFocusWnd.ShowWindow(SW_SHOW);
                    find = true;
                }
            }
        }

        if (!find) {
            m_itemFocusWnd.ShowWindow(SW_HIDE);
        }

        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = m_hWnd;

        ::TrackMouseEvent(&tme);
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);

        RECT rect;
        GetClientRect(&rect);
        BDDC localDc = ::CreateCompatibleDC(dc);
        auto hBitmap = ::CreateCompatibleBitmap(dc, rect.right, rect.bottom);//rt为RECT变量
        ::SelectObject(localDc, hBitmap);

        localDc.SelectBrush(allBk);
        localDc.FillRect(&rect, allBk);

        if (m_vscroll_range > 0) {
            localDc.SelectBrush(m_blackBrush);

            RECT rect_scroll = rect;
            rect_scroll.right -= 8;
            rect_scroll.left = rect.right - 4;
            rect_scroll.top += 8;
            rect_scroll.bottom -= 8;

            localDc.RoundRect(rect_scroll.left, rect_scroll.top, rect_scroll.right, rect_scroll.bottom, 2, 2);

            int scroll_height = rect_scroll.bottom - rect_scroll.top;
            int frame_height = rect.bottom;
            int scrollbar_height = frame_height * scroll_height / (frame_height + m_vscroll_range);
            int top = m_vscroll_pos * (scroll_height - scrollbar_height) / m_vscroll_range;
            RECT rect_bar;
            rect_bar.left = rect_scroll.left;
            rect_bar.right = rect_scroll.right;
            rect_bar.top = rect_scroll.top + top;
            rect_bar.bottom = rect_bar.top + scrollbar_height;

            localDc.SelectBrush(m_barBrush);
            localDc.RoundRect(rect_bar.left, rect_bar.top, rect_bar.right, rect_bar.bottom, 2, 2);
        }

        localDc.SelectBrush(allBk);
        BDDC mydc = ::CreateCompatibleDC(localDc);

        for (auto& item : m_items) {
            if (item.m_delta + ITEM_HEIGHT > 0 && item.m_delta < rect.bottom) {
                //Draw Titile
                localDc.SetBkMode(TRANSPARENT);
                localDc.SetTextColor(RGB(0x1D, 0x21, 0x29));
                // name
                localDc.SelectFont(m_nameFont);
                RECT rText = { 12, item.m_delta + 8 , rect.right, item.m_delta + ITEM_HEIGHT};

                ::DrawTextA(localDc.m_hDC, item.title.c_str(), item.title.size(), &rText, DT_LEFT | DT_VCENTER);
            }
            else if (item.m_delta >= rect.bottom) {
                break;
            }
        }

        // border
        localDc.SelectPen((HPEN)m_grayPen);
        POINT points[4] = { {0, 0}, {rect.right - 1, 0}, {rect.right - 1, rect.bottom - 1}, {0, rect.bottom - 1} };
        for (int i = 0; i < 4; ++i) {
            localDc.MoveTo(points[i].x, points[i].y);
            localDc.LineTo(points[(i + 1) % 4].x, points[(i + 1) % 4].y);
        }

        dc.BitBlt(0, 0, rect.right, rect.bottom, localDc, 0, 0, SRCCOPY);
        DeleteObject(hBitmap);
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        return 0;
    }

    // update all users attribute
    void AddItem(const ItemAttr& item) {
        m_items.push_back(item);

        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    void DeleteItem(const std::string& title) {
        auto pos = std::find_if(m_items.begin(), m_items.end(), [title](const ItemAttr& item) {
            return item.title == title;
        });

        if (pos != m_items.end()) {
            int delta = pos->m_delta;
            m_items.erase(pos);

            RECT rect;
            GetClientRect(&rect);
            if (delta + ITEM_HEIGHT > 0 && delta < rect.bottom) {
                rect.top = delta;
                RecalculationScroll(0, rect);
            }
        }
    }

    void Clear() {
        m_items.clear();
        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    int GetCount() {
        return m_items.size();
    }

    void SetDeleteHanlder(std::function<void(const ItemAttr&)> callback) {
        m_itemFocusWnd.SetDeleteHanlder(callback);
    }

    void SetSelectHandler(std::function<void(const ItemAttr&)> callback) {
        m_itemFocusWnd.SetSelectHandler(callback);
    }

protected:
    void RecalculationScroll(int dy, const RECT& invalid, bool force = true) {
        RECT rect0;
        GetClientRect(&rect0);

        int totalNeedHight = m_items.size() * ITEM_HEIGHT;
        auto vscroll_range = max(0, totalNeedHight - rect0.bottom);
        auto vscroll_pos = min(vscroll_range, max(0, m_vscroll_pos + dy));
        if (m_vscroll_range != vscroll_range || m_vscroll_pos != vscroll_pos) {
            m_vscroll_range = vscroll_range;
            m_vscroll_pos = vscroll_pos;

            RECT rect = rect0;
            rect.right -= 8;
            rect.left = rect.right - 4;
            rect.top += 8;
            rect.bottom -= 8;
            InvalidateRect(&rect);
        }
        else if (!force) {
            return;
        }

        int index = 0;
        for (auto& item : m_items) {
            item.m_delta = index * ITEM_HEIGHT - m_vscroll_pos;
            ++index;
        }

        InvalidateRect(&invalid);
    }

private:
    int m_vscroll_pos = 0;
    int m_vscroll_range = -1;

    std::list<ItemAttr> m_items;

    BDPen m_grayPen;
    BDBrush m_blackBrush;
    BDBrush m_barBrush;
    BDBrush allBk;
    BDFont m_nameFont;
    BDComboxExItemFocus m_itemFocusWnd;
    bool m_parent_hover = false;
};

class BDComboxEx : public BDWndImpl<BDComboxEx>
{
public:
    DECLARE_BDWND_CLASS(L"BDComboxEx")
    BDComboxEx() {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = nullptr;
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDComboxEx)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_SETFOCUS, OnFocus)
        MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        m_bkBrush = CreateSolidBrush(RGB(0xF2, 0xF3, 0xF8));
        m_textColor = RGB(0x86, 0x90, 0x9C);
        m_txtfont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        rtcutil::LoadFile(COMBOX_ARROW, m_arrow_img);

        BDHMenu m;
        BDRect rect(0, 0, 100, 100);
        m_drop.Create(m_hWnd, &rect, m, 0, WS_POPUP);
        return 0;
    }

    void OnSize(UINT nType, BDSize size) {

    }

    void OnMouseMove(UINT nFlags, BDPoint point) {
        m_drop.SetParentHover(true);

        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = m_hWnd;

        ::TrackMouseEvent(&tme);
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        bool show = m_drop.IsWindowVisible();
        if (!show) {
            int items_count = m_drop.GetCount();
            int h = (items_count > 6 ? 6 : items_count) * ITEM_HEIGHT;
            if (h <= 0) {
                h = ITEM_HEIGHT;
            }

            RECT rect;
            GetWindowRect(&rect);

            m_drop.MoveWindow(rect.left, rect.bottom + 4, rect.right - rect.left, h);
            m_drop.ShowWindow(SW_SHOW);
        }
        else {
            m_drop.ShowWindow(SW_HIDE);
        }
    }

    void OnLButtonDown(UINT nFlags, BDPoint point) {
    }

    void OnMouseLeave() {
        m_drop.SetParentHover(false);
    }

    void SetFont(HFONT font) {
        m_txtfont = font;
        Invalidate();
    }

    void SetMessage(const BDString& msg) {
        m_msg = msg;
        Invalidate();
    }

    void AddItem(const ItemAttr& item) {
        m_drop.AddItem(item);
    }

    void DeleteItem(const std::string& title) {
        m_drop.DeleteItem(title);
    }

    LRESULT OnFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        return 0;
    }

    LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        //m_drop.ShowWindow(SW_HIDE);
        return 0;
    }
    
    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rect;
        GetClientRect(&rect);
        dc.FillRect(&rect, m_bkBrush);

        if (m_arrow_img) {
            auto w = m_arrow_img->GetWidth();
            auto h = m_arrow_img->GetHeight();

            rtcutil::DrawImage(dc.m_hDC, m_arrow_img, rect.right - 10 - w, (rect.bottom - h) / 2, w, h);
        }
        
        dc.SetBkMode(TRANSPARENT);
        dc.SelectFont(m_txtfont);
        dc.SetTextColor(m_textColor);

        SIZE text_size;
        dc.GetTextExtent(m_msg, m_msg.GetLength(), &text_size);
        rect.left = 12;
        rect.top = (rect.bottom - text_size.cy) / 2;

        dc.DrawText((LPTSTR)(LPCTSTR)m_msg, m_msg.GetLength(), &rect, DT_LEFT | DT_SINGLELINE | DT_TOP);
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return 0;
    }

    void SetDeleteHanlder(std::function<void(const ItemAttr&)> callback) {
        m_drop.SetDeleteHanlder(callback);
    }

    void SetSelectHandler(std::function<void(const ItemAttr&)> callback) {
        m_drop.SetSelectHandler(callback);
    }

    void Clear() {
        m_drop.ShowWindow(SW_HIDE);
        m_drop.Clear();
    }

private:
    Gdiplus::Image* m_arrow_img = nullptr;
    BDString m_msg;
    COLORREF m_textColor;
    BDBrush m_bkBrush;
    BDFont m_txtfont;

    BDComboxExDrop m_drop;
};