//
//  BDUserWnd.h
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
#include "BDSnapshotVScrollWnd.h"

#define CAPTION_HEIGHT 50

class BDSnapshotWnd : public BDWndImpl<BDSnapshotWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDUserWnd")
    BDSnapshotWnd()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDUserWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
        COMMAND_ID_HANDLER(DUID_CLOSE_USER, OnClickClose)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        allBk.CreateSolidBrush(RGB(0x1D, 0x21, 0x29));

        m_font = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        BDHMenu m;
        BDRect r2(32, 24, 128, 48);
        m_title.Create(m_hWnd, r2, m, L"选择共享内容", WS_CHILD | WS_VISIBLE);
        m_title.SetFont(m_font);

        BDRect r(0, 0, 20, 20);
        m_close.Create(m_hWnd, r, BDHMenu(DUID_CLOSE_USER), L"", WS_CHILD | WS_VISIBLE);
        m_close.SetNormal(IDB_SHARE_CLOSE);
        m_close.SetHover(IDB_SHARE_CLOSE);
        m_close.SetID(DUID_CLOSE_USER);

        BDRect r3(32, 72, 800, 500);
        m_vscrollWnd.Create(m_hWnd, r3, m, L"", WS_CHILD | WS_VISIBLE | WS_OVERLAPPED);

        return 0;
    }

    void OnFrameShow(BOOL show, int lParam) {
        m_vscrollWnd.OnFrameShow(show, lParam);
    }

    LRESULT OnClickClose(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        ::PostMessage(m_notify_handler, WM_NOTIFY_CLOSE_SHARE, 0, 0);
        return 0;
    }

    void OnSize(UINT nType, BDSize size) {
        m_title.MoveWindow(32, 24, 96, 24);
        m_close.MoveWindow(size.cx - 32 - 20, 24, 20, 20);
        m_vscrollWnd.MoveWindow(0, 72, size.cx, size.cy - 72);
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_title) {
            dc.SetBkColor(RGB(0x1D, 0x21, 0x29));
            dc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
        }
        return allBk;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        RECT rect;
        GetClientRect(&rect);

        BDPaintDC dc(m_hWnd);
        dc.SelectBrush(allBk);
        dc.FillRect(&rect, allBk);
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        return 0;
    }

    void SetOnSharedClick(std::function<void(const SnapshotAttr&, const SnapshotAttr&)> callback) {
        m_vscrollWnd.SetOnSharedClick(callback);
    }

    void SetMessageHandler(HWND handler) {
        m_notify_handler = handler;
    }

private:
    BDSnapshotVScrollWnd m_vscrollWnd;

    BDFont m_font;
    BDStatic m_title;
    BDBmpButton m_close;

    BDBrush allBk;
    HWND m_notify_handler = nullptr;
};

