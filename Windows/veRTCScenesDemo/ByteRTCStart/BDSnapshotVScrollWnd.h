//
//  BDVScrollWnd.h
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
#include <list>
#include <algorithm>
#include "BDSnapshotFocusWnd.h"
#include "EngineWrapper.h"

#define SNAPSHOT_WIDTH 160
#define SNAPSHOT_HEIGHT 90
#define FONT_HEIGHT 30
#define SCROLL_ITEM_HEIGHT (FONT_HEIGHT + SNAPSHOT_HEIGHT)
#define MAX_COLUMN_ITEM 4
#define MAX_ROW_ITEM 3
#define BORDER_WIDTH 4

class BDSnapshotVScrollWnd : public BDWndImpl<BDSnapshotVScrollWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDSnapshotVScrollWnd")
    BDSnapshotVScrollWnd()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDVScrollWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_MOUSEWHEEL(OnMouseWheel)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_allBackground.CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        m_blackBrush.CreateSolidBrush(RGB(0x00, 0x00, 0x00));
        m_barBrush.CreateSolidBrush(RGB(0x4E, 0x59, 0x69));
        m_namefont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");

        BDHMenu m;
        BDRect rSnapshot(0, 0, SNAPSHOT_WIDTH, SNAPSHOT_HEIGHT);
        m_snapshotFocusWnd.Create(m_hWnd, &rSnapshot, m, 0, WS_POPUP);
        m_snapshotFocusWnd.ShowWindow(SW_HIDE);

        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {
        RecalculationScroll(0);
    }

    void OnFrameShow(BOOL show, int lParam) {
        if (show) {
            m_vscroll_pos = 0;
            m_vscroll_range = -1;
            m_snapshots.clear();
            EngineWrapper::GetInstance()->getShareList(m_snapshots);

            auto pos = std::find_if(m_snapshots.begin(), m_snapshots.end(), [](const SnapshotAttr& shot) {
                return shot.m_name == "ByteRTC SDK Quick Start for Windows";
            });

            if (pos != m_snapshots.end()) {
                m_local_view = *pos;
                m_snapshots.erase(pos);
            }

            RecalculationScroll(0);
        }
        else {
            m_snapshotFocusWnd.ShowWindow(SW_HIDE);
        }
    }

    void OnMouseLeave() {
        //if (!m_snapshotFocusWnd.m_mouse_captured) {
        //    m_snapshotFocusWnd.ShowWindow(SW_HIDE);
        //}
    }

    void OnMouseMove(UINT w, BDPoint point) {
        RECT windows_rc;
        ::GetWindowRect(m_hWnd, &windows_rc);

        RECT client_rect;
        GetClientRect(&client_rect);

        bool snapshot_hiden = true;
        for (auto& item : m_snapshots) {
            if (item.y + SNAPSHOT_HEIGHT < 0) {
                continue;
            }
            else if (item.y > client_rect.bottom) {
                break;
            }

            if ((point.x > item.x && point.x < item.x + SNAPSHOT_WIDTH)
                && (point.y > item.y && point.y < item.y + SNAPSHOT_HEIGHT)) {
                m_snapshotFocusWnd.MoveWindow(item.x + windows_rc.left, item.y + windows_rc.top, SNAPSHOT_WIDTH, SNAPSHOT_HEIGHT);

                if (!m_snapshotFocusWnd.IsWindowVisible()) {
                    m_snapshotFocusWnd.ShowWindow(SW_SHOW);
                }
                snapshot_hiden = false;
                m_snapshotFocusWnd.SetFocus(item);
            }
        }

        if (snapshot_hiden) {
            m_snapshotFocusWnd.ShowWindow(SW_HIDE);
        }
 
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = m_hWnd;

        ::TrackMouseEvent(&tme);
    }

    LRESULT OnMouseWheel(UINT nFlags, short zDelta, BDPoint point) {
        RECT rect;
        GetClientRect(&rect);
        int rSpace = (rect.bottom - SCROLL_ITEM_HEIGHT * MAX_ROW_ITEM) / MAX_ROW_ITEM;

        int times = zDelta / WHEEL_DELTA;
        auto dy = - times * (SCROLL_ITEM_HEIGHT + rSpace);
        RecalculationScroll(dy);
        return 0;
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        return m_allBackground;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        RECT rect;
        GetClientRect(&rect);

        BDPaintDC dc(m_hWnd);
        dc.SelectBrush(m_allBackground);
        dc.FillRect(&rect, m_allBackground);

        if (m_vscroll_range > 0) {
            dc.SelectBrush(m_blackBrush);

            RECT rect_scroll = rect;
            rect_scroll.right -= 8;
            rect_scroll.left = rect.right - 4;
            rect_scroll.top += 8;
            rect_scroll.bottom -= 24;

            dc.RoundRect(rect_scroll.left, rect_scroll.top, rect_scroll.right, rect_scroll.bottom, 2, 2);

            int scroll_height = rect_scroll.bottom - rect_scroll.top;
            int frame_height = rect.bottom;
            int scrollbar_height = frame_height * scroll_height / (frame_height + m_vscroll_range);
            int top = m_vscroll_pos * (scroll_height - scrollbar_height) / m_vscroll_range;
            RECT rect_bar;
            rect_bar.left = rect_scroll.left;
            rect_bar.right = rect_scroll.right;
            rect_bar.top = rect_scroll.top + top;
            rect_bar.bottom = rect_bar.top + scrollbar_height;

            dc.SelectBrush(m_barBrush);
            dc.RoundRect(rect_bar.left, rect_bar.top, rect_bar.right, rect_bar.bottom, 2, 2);
        }

        dc.SelectBrush(m_allBackground);
        int rSpace = (rect.bottom - SCROLL_ITEM_HEIGHT * MAX_ROW_ITEM) / MAX_ROW_ITEM;
        int cSpace = (rect.right - SNAPSHOT_WIDTH * MAX_COLUMN_ITEM) / (MAX_COLUMN_ITEM + 1);

        BDDC mydc = ::CreateCompatibleDC(dc);
        for (auto& item : m_snapshots) {
            if (item.y + SNAPSHOT_HEIGHT < 0) {
                continue;
            }
            else if(item.y > rect.bottom){
                break;
            }

            auto image = EngineWrapper::GetInstance()->GetThumbnail(item.m_type, item.source_id, SNAPSHOT_WIDTH, SNAPSHOT_HEIGHT);
            if (!image) return 0;

            auto format = image->pixel_format();
            int planes = image->number_of_planes();
            int w = image->width();
            int h = image->height();
            void* data = image->get_plane_data(0);

            BDBitmap thumb;
            thumb.CreateBitmap(w, h, 1, 32, data);

            BDDC mydc = ::CreateCompatibleDC(dc);
            mydc.SelectBitmap(thumb);
            dc.BitBlt(item.x + (SNAPSHOT_WIDTH - w) / 2, item.y + (SNAPSHOT_HEIGHT - h) / 2, w, h, mydc, 0, 0, SRCCOPY);

            //Draw Name
            dc.SetBkMode(TRANSPARENT);
            dc.SetTextColor(item.m_type == SnapshotAttr::SNAPSHOT_SCREEN ? RGB(0x40, 0x80, 0xFF) : RGB(0xFF, 0xFF, 0xFF));
            dc.SelectFont(m_namefont);
            RECT rText = { item.x, item.y + SNAPSHOT_HEIGHT + 8, item.x + SNAPSHOT_WIDTH, item.y + SNAPSHOT_HEIGHT + 8 + 22 };

            BDString name = rtcutil::ConvertUTF8ToBDString(item.m_name);
            if (name.GetLength() > 11) {
                name = name.Left(11) + L"...";
            }

            ::DrawText(dc.m_hDC, name, name.GetLength(), &rText, DT_CENTER | DT_VCENTER);
        }

        return 0;
    }

    void SetOnSharedClick(std::function<void(const SnapshotAttr&, const SnapshotAttr&)> callback) {
        m_snapshotFocusWnd.SetOnSharedClick(std::bind(callback, std::placeholders::_1, m_local_view));
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
    {
        return 0;
    }

protected:
    void RecalculationScroll(int dy) {
        if (m_snapshots.empty()) return;

        int index = -1;
        auto last_type = m_snapshots.begin()->m_type;
        for (auto& item : m_snapshots) {
            if (last_type != item.m_type) {
                index = index | 0x03;
                last_type = item.m_type;
            }
                
            ++index;
            item.index = index;
        }

        RECT rect;
        GetClientRect(&rect);

        int rSpace = (rect.bottom - SCROLL_ITEM_HEIGHT * MAX_ROW_ITEM) / MAX_ROW_ITEM;
        int cSpace = (rect.right - SNAPSHOT_WIDTH * MAX_COLUMN_ITEM) / (MAX_COLUMN_ITEM + 1);
        int totalNeedHight = (index / MAX_COLUMN_ITEM + 1) * (SCROLL_ITEM_HEIGHT + rSpace);

        auto vscroll_range = max(0, totalNeedHight - rect.bottom);
        auto vscroll_pos = min(vscroll_range, max(0, m_vscroll_pos + dy));
        if (vscroll_range == m_vscroll_range && vscroll_pos == m_vscroll_pos) {
            return;
        }

        m_vscroll_range = vscroll_range;
        m_vscroll_pos = vscroll_pos;

        for (auto& item : m_snapshots) {
            int r = item.index / MAX_COLUMN_ITEM;
            int c = item.index % MAX_COLUMN_ITEM;

            item.x = cSpace + (SNAPSHOT_WIDTH + cSpace) * c;
            item.y = (rSpace + SCROLL_ITEM_HEIGHT) * r - m_vscroll_pos;
        }

        Invalidate();
    }

private:
    int m_vscroll_pos = 0;
    int m_vscroll_range = -1;

    std::list<SnapshotAttr> m_snapshots;
    SnapshotAttr m_local_view;

    BDBrush m_allBackground;
    BDBrush m_blackBrush;
    BDBrush m_barBrush;
    BDFont m_namefont;
    BDSnapshotFocusWnd m_snapshotFocusWnd;
};

