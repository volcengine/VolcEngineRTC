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
#include "BDButton.h"
#include "BDGDI.h"
#include "BDCtrl.h"
#include "EngineWrapper.h"
#include "ByteMessage.h"
#include <functional>


class BDMessageWnd : public BDWndImpl<BDMessageWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDMessageWnd")
    BDMessageWnd() {
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
        COMMAND_ID_HANDLER(DUID_MESSAGE_AGREE, OnClickAgree)
        COMMAND_ID_HANDLER(DUID_MEETING_REFUSE, OnClickRefuse)
        
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        m_font = CreateFont(14, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_bkBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        m_warn.LoadBitmap(IDB_WARN);

        BDHMenu m;
        BDRect rtips(0, 0, 266, 22);
        m_tips.Create(m_hWnd, rtips, m, 0, WS_VISIBLE | WS_CHILD | SS_LEFT | SS_CENTERIMAGE);
        m_tips.SetWindowText(L"");
        m_tips.SetFont(m_font);

        BDRect r(0, 0, 240, 36);
        m_ok.Create(m_hWnd, r, BDHMenu(DUID_MESSAGE_AGREE), L"ok", WS_CHILD | WS_VISIBLE, 0);
        m_ok.SetBackgroundColor(m_font,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF));
        m_ok.SetID(DUID_MESSAGE_AGREE);
        m_ok.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);

        m_cancel.Create(m_hWnd, r, BDHMenu(DUID_MEETING_REFUSE), L"cancel", WS_CHILD | WS_VISIBLE, 0);
        m_cancel.SetBackgroundColor(m_font,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF2, 0xF3, 0xF5), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF5), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF5), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF5), RGB(0x1D, 0x21, 0x29));
        m_cancel.SetID(DUID_MEETING_REFUSE);
        m_cancel.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);

        return 0;
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_tips) {
            dc.SetBkColor(RGB(0xFF, 0xFF, 0xFF));
            dc.SetTextColor(RGB(0x00, 0x00, 0x00));
        }

        return (HBRUSH)m_bkBrush;
    }

    void OnSize(UINT nType, BDSize size) {
        m_tips.MoveWindow(60, 32, 266, 22);

        int gap = (size.cx - 2 * 80) / 3;
        m_cancel.MoveWindow(gap, size.cy - 24 - 36, 80, 36);
        m_ok.MoveWindow(2 * gap + 80, size.cy - 24 - 36, 80, 36);
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);

        BDDC mydc = ::CreateCompatibleDC(dc);
        BDBitmap old = mydc.SelectBitmap(m_warn);
        dc.BitBlt(30, 30, 18, 18, mydc, 0, 0, SRCCOPY);
        mydc.SelectBitmap(old);

        return 0;
    }

    void SetMessage(const BDString& message) {
        m_tips.SetWindowText(message);
    }

    void SetMessageHander(const BDString& ok_str, std::function<void()> agree_callback, const BDString& cancel_str, std::function<void()> refuse_callback) {
        m_ok.SetWindowText(ok_str);
        m_cancel.SetWindowText(cancel_str);

        m_okCallback = agree_callback;
        m_cancelCallback = refuse_callback;
    }

    LRESULT OnClickAgree(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (m_okCallback) {
            m_okCallback();
        }
        return 0;
    }

    LRESULT OnClickRefuse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (m_cancelCallback) {
            m_cancelCallback();
        }
        return 0;
    }

private:
    BDFont m_font;
    BDBrush m_bkBrush;
    BDStatic m_tips;
    BDBitmap m_warn;

    BDTxtButton m_ok;
    BDTxtButton m_cancel;

    HWND m_message_handler = nullptr;

    std::function<void()> m_okCallback;
    std::function<void()> m_cancelCallback;
};

