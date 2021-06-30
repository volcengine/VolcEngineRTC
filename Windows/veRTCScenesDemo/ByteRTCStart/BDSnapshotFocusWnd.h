//
//  BDAVInfoWnd.h
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

class BDSnapshotFocusWnd : public BDWndImpl<BDSnapshotFocusWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDSnapshotFocusWnd")
    BDSnapshotFocusWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDSnapshotFocusWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        // TODO:  Add additional initialization here
        auto lExStyle = GetExStyle();
        auto res = ModifyStyleEx(0, WS_EX_LAYERED);
        lExStyle = GetExStyle();
        SetLayeredWindowAttributes(0, 130, LWA_ALPHA);

        m_font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {
    }

    void OnMouseMove(UINT w, BDPoint point) {
        m_mouse_captured = true;

        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = m_hWnd;

        ::TrackMouseEvent(&tme);
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        if (m_shared_click) {
            m_shared_click(m_focus_shot);
        }
    }

    void OnMouseLeave() {
        m_mouse_captured = false;
        ShowWindow(SW_HIDE);
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, (HBRUSH)::CreateSolidBrush(RGB(0, 0, 0)));

        dc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
        dc.SetBkColor(RGB(0, 0, 0));
        dc.SelectFont(m_font);

        rc.top = rc.bottom / 2 - 8;
        std::string tmp = "点击开始共享";
        ::DrawTextA(dc.m_hDC, tmp.c_str(), tmp.size(), &rc, DT_CENTER | DT_VCENTER);

        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return 0;
    }

    void SetFocus(const SnapshotAttr& shot) {
        m_focus_shot = shot;
    }

    void SetOnSharedClick(std::function<void(const SnapshotAttr&)> callback) {
        m_shared_click = callback;
    }

public:
    BDFont m_font;
    bool m_mouse_captured = false;

    SnapshotAttr m_focus_shot;
    std::function<void(const SnapshotAttr&)> m_shared_click;
};

