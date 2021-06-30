//
//  BDWarningWnd.h
//
//  Copyright 2021. All rights reserved.
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


class BDWarningWnd : public BDWndImpl<BDWarningWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDWarningWnd")
    BDWarningWnd()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
            wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        }
    }

    BEGIN_MSG_MAP(BDWarningWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_font = CreateFont(20, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"微软雅黑");
        m_bkBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));

        BDHMenu m;
        BDRect rtips(16, 5, 86, 27);
        m_tips.Create(m_hWnd, rtips, m, 0, WS_VISIBLE|WS_CHILD);
        m_tips.SetWindowText(L"非法输入，输入规则如下：");
        m_tips.SetFont(m_font);

        BDRect r5(40, 170, 360, 220);
        m_content.Create(m_hWnd, r5, BDHMenu(DUID_FEEDBACK_EDIT), 0, ES_AUTOVSCROLL | ES_MULTILINE | WS_CHILD | WS_VISIBLE);
        m_content.AppendText(L"1.26个大写字母 A ~ Z\r\n");
        m_content.AppendText(L"2.26个小写字母 a ~ z\r\n");
        m_content.AppendText(L"3.10个数字0 - 9\r\n");
        m_content.AppendText(L"4.下划线\"_\", at符\"@\",减号 \"-\"\r\n");
        m_content.SetFont(m_font);
        m_content.SetReadOnly(TRUE);

        return 0;
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_tips) {
            dc.SetBkColor(RGB(0xFF, 0xFF, 0xFF));
            dc.SetTextColor(RGB(0xF5, 0x3F, 0x3F));
        }

        return (HBRUSH)m_bkBrush;
    }

    void OnSize(UINT nType, BDSize size)
    {
        m_tips.MoveWindow(16, 16, size.cx - 16, 20);
        m_content.MoveWindow(16, 40, size.cx - 16, size.cy - 40);
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);

        return 0;
    }

    BDFont m_font;
    BDBrush m_bkBrush;
    BDStatic m_tips;
    BDEdit m_content;
};

