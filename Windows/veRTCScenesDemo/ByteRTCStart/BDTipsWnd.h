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
#include "Utils.h"

class BDTipsWnd : public BDWndImpl<BDTipsWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDTipsWnd")
    BDTipsWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
            wci.m_wc.hbrBackground = ::CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        }
    }

    BEGIN_MSG_MAP(BDAVInfoWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_font = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_brush = ::CreateSolidBrush(RGB(0, 0, 0));
        m_textColor = RGB(0xFF, 0xFF, 0xFF);
        m_backgroundColor = RGB(0x1D, 0x21, 0x29);
        return 0;
    }

    void OnSize(UINT nType, BDSize size)
    {
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_brush);

        dc.SetTextColor(m_textColor);
        dc.SetBkColor(m_backgroundColor);
        dc.SelectFont(m_font);
        rc.bottom -= 10;

        SIZE size;
        dc.GetTextExtent(rtcutil::ConvertUTF8ToBDString(m_info), m_info.size(), &size);
        rc.top = (rc.bottom - size.cy) / 2;
        ::DrawTextA(dc.m_hDC, m_info.c_str(), m_info.size(), &rc, DT_CENTER | DT_VCENTER);

        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return 0;
    }

    void SetInfo(HFONT font, COLORREF brushColor, COLORREF textColor) {
        m_brush = CreateSolidBrush(brushColor);
        m_backgroundColor = brushColor;
        m_textColor = textColor;
        m_font = font;
    }

    void SetHint(const std::string& info) {
        m_info = info;
        Invalidate();
    }

private:
    std::string m_info;
    BDFont m_font;
    HBRUSH m_brush;
    COLORREF m_textColor;
    COLORREF m_backgroundColor;
};

