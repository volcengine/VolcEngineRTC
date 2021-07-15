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
#include "ByteMessage.h"


class BDUserTitleWnd : public BDWndImpl<BDUserTitleWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDUserTitleWnd")
    BDUserTitleWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
            wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        }
    }

    BEGIN_MSG_MAP(BDUserFocusWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        m_nameFont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_bkBrush = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));

        m_host_image.LoadBitmap(IDB_HOST);
        m_share_image.LoadBitmap(IDB_USER_SHARE);

        return 0;
    }

    void OnSize(UINT nType, BDSize size) {   
    }

    void SetHost(bool host) {
        m_host = host;
    }

    void SetShare(bool share) {
        m_share = share;
    }

    void SetName(const BDString& name) {
        m_name = name;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);
        dc.FillRect(&rc, m_bkBrush);
        dc.SelectFont(m_nameFont);

        SIZE text_size;
        ::GetTextExtentPoint(dc.m_hDC, m_name, m_name.GetLength(), &text_size);
        RECT rText = {0,
            0,
            rc.right,
            rc.bottom};

        BDDC mydc = ::CreateCompatibleDC(dc);
        if (m_share) {
            SIZE image;
            m_share_image.GetSize(image);
            rText.left = max(4 + image.cx + 4, rText.left);

            mydc.SelectBitmap(m_share_image);
            dc.BitBlt(rText.left - 4 - image.cx, rText.top + 3, image.cx, image.cy, mydc, 0, 0, SRCCOPY);
        }

        if (m_host) {
            SIZE image;
            m_host_image.GetSize(image);
            rText.right = min(rc.right - image.cx - 4, rText.right);

            mydc.SelectBitmap(m_host_image);
            dc.BitBlt(rText.right, rText.top + 3, image.cx, image.cy, mydc, 0, 0, SRCCOPY);
        }

        if (rText.right - rText.left >= text_size.cx) {
            rText.left += (rText.right - rText.left - text_size.cx) / 2;
        }
        else {
            m_name = m_name.Left(12);
            m_name += "...";
        }

        rText.top = (rc.bottom - text_size.cy) / 2;

        dc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
        dc.SetBkColor(RGB(0x1D, 0x21, 0x29));
        ::DrawText(dc.m_hDC, m_name, m_name.GetLength(), &rText, DT_LEFT | DT_VCENTER);

        return 0;
    }

    BDFont m_nameFont;
    BDBrush m_bkBrush;

    BDBitmap m_host_image;
    BDBitmap m_share_image;

    BDString m_name;
    bool m_host = false;
    bool m_share = false;
};

