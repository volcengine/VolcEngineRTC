//
//  BDRateWnd.h
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


class BDRateWnd : public BDWndImpl<BDRateWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDRateWnd")
    BDRateWnd()
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
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
        COMMAND_ID_HANDLER(DUID_RATE_CLOSE, onClickClose)
        COMMAND_ID_HANDLER(DUID_RATE_GOOD, onClickGood)
        COMMAND_ID_HANDLER(DUID_RATE_BAD, onClickBad)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        m_font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_bkBrush = CreateSolidBrush(RGB(255, 255, 255));
        m_grayPen = CreatePen(PS_SOLID, 1, RGB(202, 202, 202));

        BDHMenu m;
        BDRect rtips(24, 24, 126 + 24, 22 + 24);
        m_tips.Create(m_hWnd, rtips, m, 0, WS_VISIBLE | WS_CHILD);
        m_tips.SetWindowText(L"本次通话体验如何？");
        m_tips.SetFont(m_font);

        BDRect rGood(80, 62, 80 + 40, 62 + 40);
        m_good.Create(m_hWnd, rGood, BDHMenu(DUID_RATE_GOOD), L"", WS_CHILD | WS_VISIBLE);
        m_good.SetNormal(IDB_GOOD_NORMAL);
        m_good.SetHover(IDB_GOOD_HOVER);
        m_good.SetID(DUID_RATE_GOOD);

        BDRect rBad(201, 62, 201 + 40, 62 + 40);
        m_bad.Create(m_hWnd, rBad, BDHMenu(DUID_RATE_BAD), L"", WS_CHILD | WS_VISIBLE);
        m_bad.SetNormal(IDB_BAD_NORMAL);
        m_bad.SetHover(IDB_BAD_HOVER);
        m_bad.SetID(DUID_RATE_BAD);

        BDRect r(276, 24, 276 + 20, 24 + 20);
        m_close.Create(m_hWnd, r, BDHMenu(DUID_RATE_CLOSE), L"", WS_CHILD | WS_VISIBLE);
        m_close.SetNormal(IDB_WCLOSE);
        m_close.SetHover(IDB_WCLOSE);
        m_close.SetID(DUID_RATE_CLOSE);
        return 0;
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_tips) {
            dc.SetBkColor(RGB(255, 255, 255));
            dc.SetTextColor(RGB(0, 0, 0));
        }
        return (HBRUSH)m_bkBrush;
    }

    void OnSize(UINT nType, BDSize size) {

    }

    LRESULT onClickClose(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::SendMessage(m_messageHander, WM_RATE, 3, 0);
        return 0;
    }

    LRESULT onClickGood(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::SendMessage(m_messageHander, WM_RATE, 5, 0);
        return 0;
    }

    LRESULT onClickBad(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::SendMessage(m_messageHander, WM_RATE, 1, 0);
        return 0;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);
        dc.SelectPen((HPEN)m_grayPen);

        RECT rect;
        GetClientRect(&rect);

        int x0 = rect.right / 2;
        int y0 = 66;
        int x1 = x0;
        int y1 = y0 + 32;

        dc.MoveTo(x0, y0);
        dc.LineTo(x1, y1);

        return 0;
    }

    void SetMessageHander(HWND hander) {
        m_messageHander = hander;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        return 0;
    }

    BDFont m_font;
    BDBrush m_bkBrush;
    BDPen m_grayPen;
    BDStatic m_tips;

    BDBmpButton m_good;
    BDBmpButton m_bad;

    BDBmpButton m_close;
    HWND m_messageHander = nullptr;
};

