//
//  BDKickoffWnd.h
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
#include <functional>


class BDBubbleTipWnd : public BDWndImpl<BDBubbleTipWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDBubbleTipWnd")
    BDBubbleTipWnd()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
            wci.m_wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
        }
    }

    BEGIN_MSG_MAP(BDTopBarWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_TIMER(OnTimer)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
        COMMAND_ID_HANDLER(DUID_TIP_CLOSE, onClickClose)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_font = CreateFont(20, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"微软雅黑");
        m_bkBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        m_warn.LoadBitmap(IDB_WARN);

        BDHMenu m;
        BDRect rtips(40, 10, 340, 35);
        m_tips.Create(m_hWnd, rtips, m, 0, WS_VISIBLE|WS_CHILD);
        m_tips.SetFont(m_font);

        BDRect rClose(310, 8, 334, 32);
        m_close.Create(m_hWnd, rClose, BDHMenu(DUID_TIP_CLOSE), L"", WS_CHILD | WS_VISIBLE);
        m_close.SetNormal(IDB_SCLOSE);
        m_close.SetHover(IDB_SCLOSE);
        m_close.SetID(DUID_TIP_CLOSE);
        return 0;
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_tips) {
            dc.SetBkColor(RGB(0xFF, 0xFF, 0xFF));
            dc.SetTextColor(RGB(0, 0, 0));
        }
        return (HBRUSH)m_bkBrush;
    }

    void OnSize(UINT nType, BDSize size)
    {
        m_close.MoveWindow(size.cx - 24 - 8, 8, 24, 24);
        m_tips.MoveWindow(40, 10, size.cx - 40 - 30 - 8 - 10, 20);
    }

    void OnTimer(UINT_PTR time_id) {
        KillTimer(0);
        ShowWindow(SW_HIDE);
    }

    void OnFrameShow(BOOL show, int lParam) {
        if (show && m_disappear) {
            SetTimer(0, 2000);
        }
    }

    void SetTipMessage(const BDString& message) {
        m_tips.SetWindowText(message);
    }

    LRESULT onClickClose(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ShowWindow(SW_HIDE);
        return 0;
    }

    void AutoDisappear(bool disappear) {
        m_disappear = disappear;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);

        BDDC mydc = ::CreateCompatibleDC(dc);
        BDBitmap old = mydc.SelectBitmap(m_warn);
        dc.BitBlt(10, (rc.bottom - 18) / 2, 18, 18, mydc, 0, 0, SRCCOPY);
        mydc.SelectBitmap(old);

        return 0;
    }

    BDFont m_font;
    BDBrush m_bkBrush;
    BDBitmap m_warn;
    BDStatic m_tips;
    BDBmpButton m_close;
    bool m_disappear = false;
};

