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
#include "EngineWrapper.h"

class BDAVInfoWnd : public BDWndImpl<BDAVInfoWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDAVInfoWnd")
    BDAVInfoWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = nullptr;
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDAVInfoWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_TIMER(OnTimer)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        // TODO:  Add additional initialization here
        memset(&m_rect, 0x00, sizeof(m_rect));

        auto lExStyle = GetExStyle();
        auto res = ModifyStyleEx(0, WS_EX_LAYERED);
        lExStyle = GetExStyle();
        SetLayeredWindowAttributes(0, 130, LWA_ALPHA);

        m_font = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Nunito Sans");
        return 0;
    }

    void OnFrameShow(BOOL show, int lParam) {
        if (show) {
            SetTimer(0, 1000);
        } else {
            KillTimer(0);
        }
    }

    void OnSize(UINT nType, BDSize size) {
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        RECT rc;
        GetClientRect(&rc);

        BDDC localDc = ::CreateCompatibleDC(dc);
        auto hBitmap = ::CreateCompatibleBitmap(dc, rc.right, rc.bottom);
        ::SelectObject(localDc, hBitmap);

        localDc.FillRect(&rc, (HBRUSH)::CreateSolidBrush(RGB(0, 0, 0)));

        localDc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
        localDc.SetBkColor(RGB(0, 0, 0));
        localDc.SelectFont(m_font);

        int index = 0;

        RECT rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        std::string tmp = "[LOCAL]";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "RES: " + std::to_string(m_local_width) + "*" + std::to_string(m_local_height);
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "FPS: " + std::to_string(m_local_fps);
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "BIT(VIDEO): " + std::to_string(m_local_video_bandwidth) + "kbps";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "BIT(AUDIO): " + std::to_string(m_local_audio_bandwidth) + "kbps";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;
        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "[REMOTE]";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "RTT(VIDEO): " + std::to_string(m_remote_video_rtt) + "ms";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "RTT(AUDIO): " + std::to_string(m_remote_audio_rtt) + "ms";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "CPU: 0%|0%";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "BIT(VIDEO): " + std::to_string(m_remote_video_bandwidth) + "kbps";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "BIT(AUDIO): " + std::to_string(m_remote_audio_bandwidth) + "kbps";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "RES: " + std::to_string(m_remote_min_video_width == INT_MAX ? 0 : m_remote_min_video_width)
            + "*" + std::to_string(m_remote_min_video_height == INT_MAX ? 0 : m_remote_min_video_height);
        tmp += "-" + std::to_string(m_remote_max_video_width) + "*" + std::to_string(m_remote_max_video_height);
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "FPS: " + std::to_string(m_remote_min_video_fps == INT_MAX ? 0 : m_remote_min_video_fps)
            + "-" + std::to_string(m_remote_max_video_fps == INT_MAX ? 0 : m_remote_max_video_fps);
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "LOSS(VIDEO): " + std::to_string(m_remote_video_loss) + "%";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        ++index;

        rText = rText = { 20, 30 + index * 18, rc.right, 30 + (index + 1) * 18 };
        tmp = "LOSS(AUDIO): " + std::to_string(m_remote_audio_loss) + "%";
        ::DrawTextA(localDc.m_hDC, tmp.c_str(), tmp.size(), &rText, DT_LEFT | DT_TOP);

        dc.BitBlt(0, 0, rc.right, rc.bottom, localDc, 0, 0, SRCCOPY);
        DeleteObject(hBitmap);
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return 0;
    }

    void OnRtcStats(const bytertc::RtcStats& stats) {
        m_remote_audio_bandwidth = stats.rx_audio_kbitrate;
        m_remote_video_bandwidth = stats.rx_video_kbitrate;
    }

    void OnLocalVideoStats(const bytertc::LocalVideoStats& stats) {
        m_local_width = stats.encoded_frame_width;
        m_local_height = stats.encoded_frame_height;
        m_local_fps = stats.sent_frame_rate;
        m_local_video_bandwidth = stats.sent_kbitrate;
    }

    void OnLocalAudioStats(const bytertc::LocalAudioStats& stats) {
        m_local_audio_bandwidth = stats.send_kbitrate;
    }

    void OnRemoteVideoStats(const  bytertc::RemoteVideoStats& stats) {
        m_remote_video_rtt  = stats.rtt;
        m_remote_video_loss  = stats.video_loss_rate;

        if (m_remote_min_video_fps > stats.renderer_output_frame_rate && stats.renderer_output_frame_rate > 0) {
            m_remote_min_video_fps = stats.renderer_output_frame_rate;
        }

        if (m_remote_max_video_fps < stats.renderer_output_frame_rate) {
            m_remote_max_video_fps = stats.renderer_output_frame_rate;
        }

        if (stats.width < m_remote_min_video_width && stats.height < m_remote_min_video_height
            && stats.width > 0 && stats.height > 0) {
            m_remote_min_video_width = stats.width;
            m_remote_min_video_height = stats.height;
        }

        if (stats.width > m_remote_max_video_width  && stats.height > m_remote_max_video_height) {
            m_remote_max_video_width = stats.width;
            m_remote_max_video_height = stats.height;
        }
    }

    void OnRemoteAudioStats(const bytertc::RemoteAudioStats& stats) {
        m_remote_audio_rtt = stats.rtt * 100;
        m_remote_audio_loss = stats.audio_loss_rate * 100;
    }

    void OnTimer(UINT_PTR time_id) {
        Invalidate();
    }

    BOOL MoveWindowEx(int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE) {
        if (m_rect.left == x && m_rect.top == y
            && m_rect.right == nWidth && m_rect.bottom == nHeight) {
            return false;
        }

        m_rect.left = x;
        m_rect.top = y;
        m_rect.right = nWidth;
        m_rect.bottom = nHeight;

        return MoveWindow(x, y, nWidth, nHeight, bRepaint);
    }

public:
    BDFont m_font;
    // local
    int m_local_width = 0;
    int m_local_height = 0;
    int m_local_fps = 0;
    int m_local_video_bandwidth = 0;
    int m_local_audio_bandwidth = 0;

    // remote
    int m_remote_video_rtt = 0;
    int m_remote_audio_rtt = 0;

    double m_cpu = 0;
    int m_remote_video_bandwidth = 0;
    int m_remote_audio_bandwidth = 0;

    int m_remote_min_video_width = INT_MAX;
    int m_remote_min_video_height = INT_MAX;
    int m_remote_max_video_width = 0;
    int m_remote_max_video_height = 0;

    int m_remote_min_video_fps = INT_MAX;
    int m_remote_max_video_fps = 0;

    int m_remote_video_loss = 0;
    int m_remote_audio_loss = 0;

    RECT m_rect;
};

