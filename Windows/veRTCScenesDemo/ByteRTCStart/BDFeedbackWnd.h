//
//  BDFeedbackWnd.h
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
#include "byte_rtc_engine_defines.h"

#define DEFAULT_CONTENT L"  最多可输入500个字符"

class BDFeedbackWnd : public BDWndImpl<BDFeedbackWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDFeedbackWnd")
    BDFeedbackWnd()
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
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CTLCOLOREDIT(OnCtlColorEdit)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
        COMMAND_ID_HANDLER(DUID_FEEDBACK_AKA, onClickAKA)
        COMMAND_ID_HANDLER(DUID_FEEDBACK_VKA, onClickVKA)
        COMMAND_ID_HANDLER(DUID_FEEDBACK_SKA, onClickSKA)
        COMMAND_ID_HANDLER(DUID_FEEDBACK_CRASH, onClickCRASH)
        COMMAND_ID_HANDLER(DUID_FEEDBACK_OK, onClickOK)
        COMMAND_ID_HANDLER(DUID_FEEDBACK_CLOSE, onClickClose)
        COMMAND_HANDLER(DUID_FEEDBACK_EDIT, EN_SETFOCUS, FocusHandler)
        COMMAND_HANDLER(DUID_FEEDBACK_EDIT, EN_CHANGE, ChangeHandler)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_labelFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_bkBrush = CreateSolidBrush(RGB(255, 255, 255));
        m_contentFont = CreateFont(12, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");

        BDHMenu m;
        BDRect rtips(32, 32, 32 + 100, 32 + 22);
        m_tips.Create(m_hWnd, rtips, m, 0, WS_VISIBLE | WS_CHILD);
        m_tips.SetWindowText(L"具体问题反馈");
        m_tips.SetFont(m_labelFont);

        BDRect rOther(32, 126, 32 + 100, 126 + 22);
        m_other_static.Create(m_hWnd, rOther, m, 0, WS_VISIBLE | WS_CHILD);
        m_other_static.SetWindowText(L"其他反馈问题");
        m_other_static.SetFont(m_labelFont);

        BDRect r0(32, 70, 32 + 80, 70 + 32);
        m_reason[0].Create(m_hWnd, r0, BDHMenu(DUID_FEEDBACK_VKA), L"视频卡顿", WS_CHILD | WS_VISIBLE, 0);
        m_reason[0].SetID(DUID_FEEDBACK_VKA);
        m_reason[0].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        m_reason[0].SetBackgroundColor(m_contentFont,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29));
        m_bs[0] = false;

        BDRect r1(128, 70, 128 + 80, 70 + 32);
        m_reason[1].Create(m_hWnd, r1, BDHMenu(DUID_FEEDBACK_SKA), L"共享内容故障", WS_CHILD | WS_VISIBLE, 0);
        m_reason[1].SetID(DUID_FEEDBACK_SKA);
        m_reason[1].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        m_reason[1].SetBackgroundColor(m_contentFont,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29));
        m_bs[1] = false;

        BDRect r2(248, 70, 248 + 80, 70 + 32);
        m_reason[2].Create(m_hWnd, r2, BDHMenu(DUID_FEEDBACK_AKA), L"音频卡顿", WS_CHILD | WS_VISIBLE, 0);
        m_reason[2].SetID(DUID_FEEDBACK_AKA);
        m_reason[2].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        m_reason[2].SetBackgroundColor(m_contentFont,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29));
        m_bs[2] = false;

        BDRect r3(344, 70, 344 + 80, 70 + 32);
        m_reason[3].Create(m_hWnd, r3, BDHMenu(DUID_FEEDBACK_CRASH), L"其他问题", WS_CHILD | WS_VISIBLE, 0);
        m_reason[3].SetID(DUID_FEEDBACK_CRASH);
        m_reason[3].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        m_reason[3].SetBackgroundColor(m_contentFont,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xE8, 0xF3, 0xFF), RGB(0x16, 0x5D, 0xFF),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29));
        m_bs[3] = false;

        BDRect r6(246, 242, 246 + 56, 242 + 32);
        m_ok.Create(m_hWnd, r6, BDHMenu(DUID_FEEDBACK_OK), L"提交", WS_CHILD | WS_VISIBLE, 0);
        m_ok.SetID(DUID_FEEDBACK_OK);
        m_ok.SetBackgroundColor(m_contentFont,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF));
        m_ok.SetState(BDTxtButton::BUTTON_STATE_DISABLE);
       
        BDRect r7(178, 242, 178 + 56, 242 + 32);
        m_cancel.Create(m_hWnd, r7, BDHMenu(DUID_FEEDBACK_CLOSE), L"取消", WS_CHILD | WS_VISIBLE, 0);
        m_cancel.SetID(DUID_FEEDBACK_CLOSE);
        m_cancel.SetBackgroundColor(m_contentFont,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29));
        m_cancel.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);

        BDRect r5(32, 164 - 4, 32 + 416, 164 + 30);
        m_other.Create(m_hWnd, r5, BDHMenu(DUID_FEEDBACK_EDIT), 0, ES_AUTOVSCROLL | ES_MULTILINE | WS_CHILD | WS_VISIBLE /*| WS_VSCROLL*/);
        m_other.SendMessage(EM_LIMITTEXT, 500, 0);
        m_other.SetWindowText(DEFAULT_CONTENT);
        m_other.SetFont(m_contentFont);

        RECT rect;
        m_other.GetClientRect(&rect);
        //设置内容的,左边距与上边距
        ::OffsetRect(&rect, 0, 10);
        ::SendMessage(m_other.m_hWnd, EM_SETRECT, 0, (LPARAM)&rect);

        BDRect r4(32, 194, 32 + 416, 194 + 24);
        m_statistic.Create(m_hWnd, r4, m, 0, WS_VISIBLE | WS_CHILD | SS_RIGHT | SS_CENTERIMAGE);
        m_statistic.SetWindowText(L"0/500  ");
        m_statistic.SetFont(m_contentFont);

        BDRect r(360, 10, 20, 20);
        m_close.Create(m_hWnd, r, BDHMenu(DUID_FEEDBACK_CLOSE), L"", WS_CHILD | WS_VISIBLE);
        m_close.SetNormal(IDB_WCLOSE);
        m_close.SetHover(IDB_WCLOSE);
        m_close.SetID(DUID_FEEDBACK_CLOSE);
        
        return 0;
    }

    LRESULT OnCtlColorEdit(HDC hDc, HWND handler) {
        BDString str = m_other.GetWindowText();
        ::SetTextColor(hDc, str == DEFAULT_CONTENT ? RGB(0x86, 0x90, 0x9C) : RGB(0, 0, 0));
        ::SetBkMode(hDc, OPAQUE);
        ::SetBkColor(hDc, RGB(0xF2, 0xF3, 0xF8));
        return (INT_PTR)CreateSolidBrush(RGB(0xF2, 0xF3, 0xF8));//返回背景色的画刷
    }

    void Reset() {
        for (int i = 0; i < 4; i++)
        {
            m_reason[i].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
            m_bs[i] = false;
        }

        m_other.SetWindowText(DEFAULT_CONTENT);
        m_ok.SetFocus();
    }

    void SetMessageHander(HWND handler) {
        m_messageHander = handler;
    }

    void OthersKillFocus() {
        BDString str = m_other.GetWindowText();
        if (str.GetLength() == 0) {
            m_other.SetWindowText(DEFAULT_CONTENT);
        }

        m_ok.SetFocus();
    }

    LRESULT FocusHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (hWndCtl == (HWND)m_other)
        {
            BDString str = m_other.GetWindowText();
            if (str == DEFAULT_CONTENT) {
                m_other.SetWindowText(L"");
            }
        }
        return 0;
    }

    LRESULT ChangeHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (hWndCtl == (HWND)m_other)
        {
            UpdateOKButton();
        }
        return 0;
    }

    void UpdateOKButton() {
        BDString str = m_other.GetWindowText();
        if (str.GetLength() > 0 && str != DEFAULT_CONTENT) {
            m_ok.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
            str = rtcutil::ConvertUTF8ToBDString(std::to_string(str.GetLength())) + L"/500 ";
            m_statistic.SetWindowText(str);
        }
        else
        {
            m_statistic.SetWindowText(L"0/500 ");
            if (m_bs[0] || m_bs[1] || m_bs[2] || m_bs[3])
            {
                m_ok.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
            }
            else {
                m_ok.SetState(BDTxtButton::BUTTON_STATE_DISABLE);
            }
        }
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_tips) {
            dc.SetBkColor(RGB(255, 255, 255));
            dc.SetTextColor(RGB(0, 0, 0));
        }
        else if (wndStatic == m_statistic) {
            dc.SetBkColor(RGB(0xF2, 0xF3, 0xF8));
            dc.SetTextColor(RGB(0x86, 0x90, 0x9c));

            return (HBRUSH)CreateSolidBrush(RGB(0xF2, 0xF3, 0xF8));//返回背景色的画刷
        }

        return (HBRUSH)m_bkBrush;
    }

    void OnSize(UINT nType, BDSize size) {
        const int width = 80;
        const int hight = 32;
        const int y = 70;
        int delta = (size.cx - 4 * width) / 5;

        for (int i = 0; i < 4; ++i) {
            m_reason[i].MoveWindow(delta + (delta + width) * i, y, width, hight);
        }

        m_close.MoveWindow(size.cx - 24 - 20, 24, 20, 20);
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        return 0;
    }

    LRESULT onClickAKA(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        m_bs[2] = !m_bs[2];
        if (m_bs[2]) {
            m_reason[2].SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
        }
        else {
            m_reason[2].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        }

        OthersKillFocus();
        UpdateOKButton();
        return 0;
    }

    LRESULT onClickVKA(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        m_bs[0] = !m_bs[0];
        if (m_bs[0]) {
            m_reason[0].SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
            m_ok.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
        }
        else {
            m_reason[0].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        }

        OthersKillFocus();
        UpdateOKButton();
        return 0;
    }

    LRESULT onClickSKA(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        m_bs[1] = !m_bs[1];
        if (m_bs[1]) {
            m_reason[1].SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
            m_ok.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
        }
        else {
            m_reason[1].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        }

        OthersKillFocus();
        UpdateOKButton();
        return 0;
    }

    LRESULT onClickCRASH(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        m_bs[3] = !m_bs[3];
        if (m_bs[3]) {
            m_reason[3].SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
            m_ok.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);
        }
        else {
            m_reason[3].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
        }

        OthersKillFocus();
        UpdateOKButton();
        return 0;
    }

    LRESULT onClickOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        int type = 0;
        BDString final;
        if (m_bs[0]) {
            final += L"[视频卡顿]";
            type = type | bytertc::PROBLEM_AUDIO_LAGGING | bytertc::PROBLEM_NO_VIDEO;
        }
        if (m_bs[1]) {
            final += L"[共享内容故障]";
            type = type| bytertc::PROBLEM_NO_VIDEO;
        }
        if (m_bs[2]) {
            final += L"[音频卡顿]";
            type = type | bytertc::PROBLEM_AUDIO_LAGGING;
        }
        if (m_bs[3]) {
            final += L"[其他问题]";
            type = type | bytertc::PROBLEM_OTHER_MSG;
        }

        BDString str = m_other.GetWindowText();
        if (str.GetLength() > 0) final += str;
        string finalstr = rtcutil::ConvertBDStringToUTF8(final);
        ::SendMessage(m_messageHander, WM_FEEDBACK, (WPARAM)finalstr.c_str(), type);
        return 0;
    }

    LRESULT onClickClose(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::SendMessage(m_messageHander, WM_FEEDBACK, (WPARAM)"", 0);
        return 0;
    }

    void OnFrameShow(BOOL show, int lParam) {
        if (show) {
            for (int i = 0; i < 4; ++i) {
                m_bs[i] = false;
                m_reason[i].SetState(BDTxtButton::BUTTON_STATE_DISABLE);
            }

            m_other.SetWindowText(DEFAULT_CONTENT);
        }
    }

    HWND m_messageHander = nullptr;
    BDFont m_labelFont;
    BDFont m_contentFont;
    BDBrush m_bkBrush;
    BDStatic m_tips;
    BDStatic m_statistic;
    BDStatic m_other_static;
    BDBmpButton m_close;
    BDTxtButton m_reason[4];
    BDEdit m_other;
    BDTxtButton m_ok;
    BDTxtButton m_cancel;

    bool m_bs[4];
};

