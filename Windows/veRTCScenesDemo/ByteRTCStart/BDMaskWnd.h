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

class BDMaskWnd : public BDWndImpl<BDMaskWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDMaskWnd")
    BDMaskWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
            wci.m_wc.hbrBackground = ::CreateSolidBrush(RGB(0, 0, 0));
        }
    }

    BEGIN_MSG_MAP(BDAVInfoWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        // TODO:  Add additional initialization here
        auto lExStyle = GetExStyle();
        auto res = ModifyStyleEx(0, WS_EX_LAYERED);
        lExStyle = GetExStyle();
        SetLayeredWindowAttributes(0, 100, LWA_ALPHA);

        return 0;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, (HBRUSH)::CreateSolidBrush(RGB(0, 0, 0)));

        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        return 0;
    }

    void SetMessageHander(HWND handler) {
        m_message_handler = handler;
    }

    void OnLButtonUp(UINT nFlags, BDPoint point) {
        ::PostMessage(m_message_handler, WM_MASK_CLICK, 0, 0);
    }

private:
    HWND m_message_handler = nullptr;
};

