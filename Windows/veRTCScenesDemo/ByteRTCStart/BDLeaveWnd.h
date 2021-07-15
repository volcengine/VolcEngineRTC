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


class BDLeaveWnd : public BDWndImpl<BDLeaveWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDLeaveWnd")
    BDLeaveWnd()
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
        COMMAND_ID_HANDLER(DUID_MEETING_END, OnClickEnd)
        COMMAND_ID_HANDLER(DUID_MEETING_LEAVE, OnClickLeave)
        COMMAND_ID_HANDLER(DUID_MEETING_CANCEL, OnClickCancel)
        
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_font = CreateFont(14, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_bkBrush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        m_warn.LoadBitmap(IDB_WARN);

        BDHMenu m;
        BDRect rtips(0, 0, 266, 22);
        m_tips.Create(m_hWnd, rtips, m, 0, WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE);
        m_tips.SetWindowText(L"请移交主持人给指定参会者，方能离开会议");
        m_tips.SetFont(m_font);

        BDRect r(0, 0, 240, 36);
        m_endMeeting.Create(m_hWnd, r, BDHMenu(DUID_MEETING_END), L"结束全部会议", WS_CHILD | WS_VISIBLE, 0);
        m_endMeeting.SetBackgroundColor(m_font,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF5, 0x3F, 0x3F), RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF5, 0x3F, 0x3F), RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF5, 0x3F, 0x3F), RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF5, 0x3F, 0x3F), RGB(0xFF, 0xFF, 0xFF));
        m_endMeeting.SetID(DUID_MEETING_END);
        m_endMeeting.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);

        m_leaveMeeting.Create(m_hWnd, r, BDHMenu(DUID_MEETING_LEAVE), L"离开会议", WS_CHILD | WS_VISIBLE, 0);
        m_leaveMeeting.SetBackgroundColor(m_font,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF5, 0x3F, 0x3F), RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF5, 0x3F, 0x3F), RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF5, 0x3F, 0x3F), RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF7, 0xF8, 0xFA), RGB(0xC9, 0xCD, 0xD4));
        m_leaveMeeting.SetID(DUID_MEETING_LEAVE);
        m_leaveMeeting.SetState(BDTxtButton::BUTTON_STATE_DISABLE);

        m_CancleMeeting.Create(m_hWnd, r, BDHMenu(DUID_MEETING_CANCEL), L"取消", WS_CHILD | WS_VISIBLE, 0);
        m_CancleMeeting.SetBackgroundColor(m_font,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF2, 0xF3, 0xF5), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF5), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF5), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF5), RGB(0x1D, 0x21, 0x29));
        m_CancleMeeting.SetID(DUID_MEETING_CANCEL);
        m_CancleMeeting.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);

        return 0;
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_tips) {
            dc.SetBkColor(RGB(0xFF, 0xFF, 0xFF));
            dc.SetTextColor(RGB(0x1D, 0x21, 0x29));
        }

        return (HBRUSH)m_bkBrush;
    }

    void OnSize(UINT nType, BDSize size)
    {
        if (m_isHost) {
            m_tips.MoveWindow(81, 32, 266, 22);
            m_endMeeting.MoveWindow(80, 78, 240, 36);
            m_leaveMeeting.MoveWindow(80, 134, 240, 36);
            m_CancleMeeting.MoveWindow(80, 190, 240, 36);
        }
        else {
            m_tips.MoveWindow(123, 32, 182, 22);
            m_leaveMeeting.MoveWindow(80, 78, 240, 36);
            m_CancleMeeting.MoveWindow(80, 134, 240, 36);
        }
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);

        BDDC mydc = ::CreateCompatibleDC(dc);
        BDBitmap old = mydc.SelectBitmap(m_warn);
        dc.BitBlt(m_isHost ? 50 : 90, 36, 18, 18, mydc, 0, 0, SRCCOPY);
        mydc.SelectBitmap(old);

        return 0;
    }

    void SetMessageHander(HWND handler) {
        m_message_handler = handler;
    }

    void SetHost(bool host) {
        m_isHost = host;
        if (m_isHost) {
            m_tips.SetWindowText(L"请移交主持人给指定参会者，方能离开会议");
            m_tips.MoveWindow(81, 32, 266, 22);
            m_endMeeting.MoveWindow(80, 78, 240, 36);
            m_leaveMeeting.MoveWindow(80, 134, 240, 36);
            m_CancleMeeting.MoveWindow(80, 190, 240, 36);

            m_endMeeting.ShowWindow(SW_SHOW);
            m_leaveMeeting.SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        }
        else {
            m_tips.SetWindowText(L"请再次确认是否要离开会议?");
            m_tips.MoveWindow(123, 32, 182, 22);
            m_leaveMeeting.MoveWindow(80, 78, 240, 36);
            m_CancleMeeting.MoveWindow(80, 134, 240, 36);
            m_endMeeting.ShowWindow(SW_HIDE);
            m_leaveMeeting.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
        }
    }

    LRESULT OnClickEnd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (m_endMeeting.m_state != BDTxtButton::BUTTON_STATE_DISABLE) {
            ShowWindow(SW_HIDE);
            ::PostMessage(m_message_handler, DUID_MEETING_END, 0, 0);
        }
        return 0;
    }

    LRESULT OnClickLeave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (m_leaveMeeting.m_state != BDTxtButton::BUTTON_STATE_DISABLE) {
            ::PostMessage(m_message_handler, DUID_MEETING_LEAVE, 0, 0);
            ShowWindow(SW_HIDE);
        }
        return 0;
    }

    LRESULT OnClickCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::PostMessage(m_message_handler, DUID_MEETING_CANCEL, 0, 0);
        ShowWindow(SW_HIDE);
        return 0;
    }

    BDFont m_font;
    BDBrush m_bkBrush;
    BDStatic m_tips;
    BDBitmap m_warn;
    BDTxtButton m_endMeeting;
    BDTxtButton m_leaveMeeting;
    BDTxtButton m_CancleMeeting;

    HWND m_message_handler = nullptr;

    bool m_isHost = true;
};

