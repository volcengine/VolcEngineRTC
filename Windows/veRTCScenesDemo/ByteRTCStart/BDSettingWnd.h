//
//  BDSettingWnd.h
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
#include "Utils.h"
#include "BDComboxEx.h"
#include "meeting-manager/MeetingManager.h"
#include <tuple>
#include <shellapi.h>
#include <sstream>
#include <iomanip>
#include <algorithm>

class BDSettingWnd : public BDWndImpl<BDSettingWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDSettingWnd")
    BDSettingWnd() {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDSettingWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_HSCROLL(OnHScroll)
        MSG_WM_SIZE(OnSize)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        //MSG_WM_NCHITTEST(OnNcHitTest)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
        COMMAND_ID_HANDLER(DUID_CLOSE_SETTING, OnClickClose)
        COMMAND_ID_HANDLER(DUID_CANCEL, OnClickCancel)
        COMMAND_ID_HANDLER(DUID_OK, OnClickOk)
        COMMAND_ID_HANDLER(DUID_SHOW_INFO, OnClickShowInfo)
        COMMAND_HANDLER(DUID_INPUT, CBN_SELCHANGE, OnInputSel)
        COMMAND_HANDLER(DUID_VIDEO_CAPTURE, CBN_SELCHANGE, OnInputSel)
        COMMAND_HANDLER(DUID_RESOLUTION, CBN_SELCHANGE, OnInputSel)
        COMMAND_HANDLER(DUID_SCREEN_RESOLUTION, CBN_SELCHANGE, OnInputSel)
        COMMAND_HANDLER(DUID_FPS, CBN_SELCHANGE, OnInputSel)
        COMMAND_HANDLER(DUID_SCREEN_FPS, CBN_SELCHANGE, OnInputSel)
        COMMAND_HANDLER(DUID_HISTORY, CBN_SELCHANGE, OnInputSel)
        COMMAND_HANDLER(DUID_INPUT, CBN_DROPDOWN, OnInputDropdown)
        COMMAND_HANDLER(DUID_VIDEO_CAPTURE, CBN_DROPDOWN, OnCameraDropdown)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        allBk.CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        bitrateBk.CreateSolidBrush(RGB(0xF2, 0xF3, 0xF8));
        m_grayPen = CreatePen(PS_SOLID, 1, RGB(0xE5, 0xE8, 0xEF));

        BDRect r(0, 0, 24, 24);
        m_close.Create(m_hWnd, r, BDHMenu(DUID_CLOSE_SETTING), L"X", WS_CHILD | WS_VISIBLE);
        m_close.SetNormal(IDB_SCLOSE);
        m_close.SetHover(IDB_SCLOSE);
        m_close.SetID(DUID_CLOSE_SETTING);

        m_font = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang S");
        m_bitrate_font = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang S");

        BDHMenu m;
        BDRect r1(0, 0, 100, 20);
        m_title.Create(m_hWnd, r1, m, L"会议设置", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title.SetFont(CreateFont(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC"));

        m_title_solution.Create(m_hWnd, r1, m, L"分辨率", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_solution.SetFont(m_font);

        m_title_screen_solution.Create(m_hWnd, r1, m, L"屏幕共享分辨率", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_screen_solution.SetFont(m_font);

        BDRect r2(0, 0, 100, 20);
        m_title_frames.Create(m_hWnd, r2, m, L"帧率", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_frames.SetFont(m_font);

        m_title_screen_frames.Create(m_hWnd, r2, m, L"屏幕共享帧率", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_screen_frames.SetFont(m_font);

        BDRect r3(0, 0, 100, 20);
        m_title_bitrate.Create(m_hWnd, r3, m, L"码率", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_bitrate.SetFont(m_font);

        m_title_screen_bitrate.Create(m_hWnd, r3, m, L"屏幕共享码率", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_screen_bitrate.SetFont(m_font);

        BDRect r4(0, 0, 100, 20);
        m_title_input.Create(m_hWnd, r4, m, L"麦克风", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_input.SetFont(m_font);

        m_title_camera.Create(m_hWnd, r4, m, L"摄像头", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_camera.SetFont(m_font);

        BDRect r5(0, 0, 100, 20);
        m_title_history.Create(m_hWnd, r5, m, L"查看历史会议", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_history.SetFont(m_font);

        m_title_my_videos.Create(m_hWnd, r5, m, L"我的云录制", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_my_videos.SetFont(m_font);

        BDRect r6(0, 0, 100, 20);
        m_title_avinfo.Create(m_hWnd, r5, m, L"实时视频参数", WS_CHILD | WS_VISIBLE | SS_RIGHT | SS_CENTERIMAGE);
        m_title_avinfo.SetFont(m_font);;

        BDRect re1(140, 35, 340, 75);
        m_solutions.Create(m_hWnd, re1 , NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, NULL, DUID_RESOLUTION);

        m_solutions.InsertString(0, L"160*160");
        m_solutions.InsertString(1, L"320*180");
        m_solutions.InsertString(2, L"320*240");
        m_solutions.InsertString(3, L"640*360");
        m_solutions.InsertString(4, L"480*480");
        m_solutions.InsertString(5, L"640*480");
        m_solutions.InsertString(6, L"960*540");
        m_solutions.InsertString(7, L"1280*720");
        m_solutions.InsertString(8, L"1920*1080");

        m_solutions.SetCurSel(5);

        m_screen_solutions.Create(m_hWnd, re1, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, NULL, DUID_SCREEN_RESOLUTION);

        m_screen_solutions.InsertString(0, L"160*160");
        m_screen_solutions.InsertString(1, L"320*180");
        m_screen_solutions.InsertString(2, L"320*240");
        m_screen_solutions.InsertString(3, L"640*360");
        m_screen_solutions.InsertString(4, L"480*480");
        m_screen_solutions.InsertString(5, L"640*480");
        m_screen_solutions.InsertString(6, L"960*540");
        m_screen_solutions.InsertString(7, L"1280*720");
        m_screen_solutions.InsertString(8, L"1920*1080");

        m_screen_solutions.SetCurSel(8);

        m_video_profiles.push_back({ 160, 160, 40, 150 });
        m_video_profiles.push_back({ 320, 180, 80, 350 });
        m_video_profiles.push_back({ 320, 240, 100, 400 });
        m_video_profiles.push_back({ 640, 360, 200, 1000 });
        m_video_profiles.push_back({ 480, 480, 200, 1000 });
        m_video_profiles.push_back({ 640, 480, 250, 1000 });
        m_video_profiles.push_back({ 960, 540, 400, 1600 });
        m_video_profiles.push_back({ 1280, 720, 500, 2000 });
        m_video_profiles.push_back({ 1920, 1080, 800, 3000 });

        BDRect re2(140, 35, 340, 75);
        m_frames.Create(m_hWnd, re2, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, NULL, DUID_FPS);
        m_frames.InsertString(0, L"15 fps");
        m_frames.InsertString(1, L"20 fps");
        m_frames.InsertString(2, L"24 fps");
        m_frames.SetCurSel(0);

        m_screen_frames.Create(m_hWnd, re2, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, NULL, DUID_SCREEN_FPS);
        m_screen_frames.InsertString(0, L"15 fps");
        m_screen_frames.InsertString(1, L"20 fps");
        m_screen_frames.InsertString(2, L"24 fps");
        m_screen_frames.SetCurSel(0);

        m_fps_vec = { 15, 20, 24 };

        BDRect re3(140, 35, 340, 55);
        m_bitrate.Create(m_hWnd, re3, NULL, WS_VISIBLE | WS_CHILD, 0, DUID_SETTING_BITRATE);
        m_bitrate.SetScrollRange(250, 1000);
        m_bitrate.SetScrollPos(600);
        BDRect r7(340, 35, 380, 40);
        m_bitrate_value_str.Create(m_hWnd, r7, m, L"600", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE);
        m_bitrate_value_str.SetFont(m_bitrate_font);

        m_bitrate_value_unit.Create(m_hWnd, r7, m, L"kbps", WS_CHILD | WS_VISIBLE);
        m_bitrate_value_unit.SetFont(m_bitrate_font);

        m_screen_bitrate.Create(m_hWnd, re3, NULL, WS_VISIBLE | WS_CHILD, 0, DUID_SETTING_BITRATE);
        m_screen_bitrate.SetScrollRange(800, 3000);
        m_screen_bitrate.SetScrollPos(2000);
        m_screen_bitrate_value_str.Create(m_hWnd, r7, m, L"2000", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE);
        m_screen_bitrate_value_str.SetFont(m_bitrate_font);

        m_screen_bitrate_value_unit.Create(m_hWnd, r7, m, L"kbps", WS_CHILD | WS_VISIBLE);
        m_screen_bitrate_value_unit.SetFont(m_bitrate_font);

        BDRect re4(140, 35, 340, 75);
        m_input.Create(m_hWnd, re4, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, NULL, DUID_INPUT);
        m_input.SetFont(m_font);
        m_input.SetCurSel(0);

        BDRect reCamera(140, 35, 340, 75);
        m_cameras.Create(m_hWnd, reCamera, NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, NULL, DUID_VIDEO_CAPTURE);
        m_cameras.SetFont(m_font);
        m_cameras.SetCurSel(0);

        m_history.Create(m_hWnd, &re4, m, 0, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN);
        m_history.SetMessage(L"选择历史会议点击链接查看");
        m_history.SetSelectHandler(std::bind(&BDSettingWnd::OnBrowseVideoRecord, this, std::placeholders::_1));

        m_my_videos.Create(m_hWnd, &re4, m, 0, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN);
        m_my_videos.SetMessage(L"会议录制者有权在此处查看和删除录像");
        m_my_videos.SetDeleteHanlder(std::bind(&BDSettingWnd::OnDeleteVideoRecord, this, std::placeholders::_1));
        m_my_videos.SetSelectHandler(std::bind(&BDSettingWnd::OnBrowseVideoRecord, this, std::placeholders::_1));

        //std::list<ItemAttr> items;
        //for (int i = 0; i < 7; ++i) {
        //    ItemAttr item;
        //    item.data = std::to_string(i);
        //    item.title = "2021/4/12 14:10:0" + std::to_string(i);
        //    items.push_back(item);
        //}

        //m_my_videos.AddAllItems(items);

        BDRect re6(240, 35, 280, 59);
        m_showInfo.Create(m_hWnd, re6, BDHMenu(DUID_SHOW_INFO), NULL, WS_VISIBLE | WS_CHILD);
        m_showInfo.SetNormal(IDB_CHECK);
        m_showInfo.SetHover(IDB_CHECK);
        m_showInfo.SetDisable(IDB_CHECK2);
        m_showInfo.SetID(DUID_SHOW_INFO);
        m_showInfo.SetState(BUTTON_STATE_DISABLE);

        BDRect rButton(0, 0, 56, 32);
        m_cancel.Create(m_hWnd, rButton, BDHMenu(DUID_CANCEL), L"取消", WS_CHILD | WS_VISIBLE, 0);
        m_cancel.SetID(DUID_CANCEL);
        //m_cancel.SetFont(m_bitrate_font);
        m_cancel.SetBackgroundColor(m_bitrate_font,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29),
            RGB(0xF2, 0xF3, 0xF8), RGB(0x1D, 0x21, 0x29));
        m_cancel.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);

        m_ok.Create(m_hWnd, rButton, BDHMenu(DUID_OK), L"完成", WS_CHILD | WS_VISIBLE, 0);
        m_ok.SetID(DUID_OK);
        //m_ok.SetFont(m_bitrate_font);
        m_ok.SetBackgroundColor(m_bitrate_font,
            RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF),
            RGB(0x16, 0x64, 0xFF), RGB(0xFF, 0xFF, 0xFF));
        m_ok.SetState(BDTxtButton::BUTTON_STATE_DEFAULT);

        return 0;
    }

    void OnFrameShow(BOOL show, int lParam) {
        if (show) {
            MeetingManager::GetInstance()->getHistoryMeetingRecord([this](int code, const std::list<RecordInfo>& records) {
                if (code == 200) {
                    SetRecordList(records);
                }
            });

            // audio setting
            char guid[256];
            memset(guid, 0x00, sizeof(guid));
            EngineWrapper::GetInstance()->GetAudioInputDevice(guid);
            UpdateAudioDevice(guid);
            // video setting
            memset(guid, 0x00, sizeof(guid));
            EngineWrapper::GetInstance()->GetVideoCaptureDevice(guid);
            UpdateVideoDevice(guid);

            SaveState();
        }
    }

    void OnSize(UINT nType, BDSize size) {
        m_title.MoveWindow(332, 12, 100, 22);
        m_close.MoveWindow(size.cx - 24 - 24, 16, 24, 24);

        m_title_solution.MoveWindow(0, 73, 100, 20);
        m_solutions.MoveWindow(120, 67, 160, 32);

        m_title_screen_solution.MoveWindow(364, 73, 84, 20);
        m_screen_solutions.MoveWindow(464, 67, 160, 32);

        m_title_frames.MoveWindow(0, 125, 100, 20);
        m_frames.MoveWindow(120, 119, 160, 32);

        m_title_screen_frames.MoveWindow(364, 125, 84, 20);
        m_screen_frames.MoveWindow(464, 119, 160, 32);

        m_title_bitrate.MoveWindow(0, 178, 100, 20);
        m_bitrate.MoveWindow(120, 180, 96, 20);
        m_bitrate_value_str.MoveWindow(224, 175, 56, 32);
        m_bitrate_value_unit.MoveWindow(288, 184, 28, 20);

        m_title_screen_bitrate.MoveWindow(364, 178, 84, 20);
        m_screen_bitrate.MoveWindow(464, 180, 96, 20);
        m_screen_bitrate_value_str.MoveWindow(568, 175, 56, 32);
        m_screen_bitrate_value_unit.MoveWindow(632, 184, 28, 20);

        m_title_input.MoveWindow(0, 229, 100, 20);
        m_input.MoveWindow(120, 226, 160, 32);

        m_title_camera.MoveWindow(0, 275, 100, 20);
        m_cameras.MoveWindow(120, 275, 160, 32);

        m_title_history.MoveWindow(0, 333, 100, 20);
        m_history.MoveWindow(120, 327, 320, 32);

        m_title_my_videos.MoveWindow(0, 385, 100, 20);
        m_my_videos.MoveWindow(120, 379, 320, 32);

        m_title_avinfo.MoveWindow(0, 433, 100, 20);
        m_showInfo.MoveWindow(108, 431, 40, 24);

        m_cancel.MoveWindow(576, 492, 56, 32);
        m_ok.MoveWindow(644, 492, 56, 32);

        m_title.SetFocus();
    }

    void OnHScroll(UINT nSBCode, UINT nPos, BDScrollBar pScrollBar) {
        BDString str;

        switch (nSBCode) {
        case SB_THUMBPOSITION:{
            pScrollBar.SetScrollPos(nPos);
            str.Format(L"%d", nPos);
            break;
        }
        case SB_LINERIGHT: {
            int minPos = 0, maxPos = 0;
            pScrollBar.GetScrollRange(&minPos, &maxPos);
            int pos = pScrollBar.GetScrollPos();
            pos += (maxPos - minPos) / 100;
            pos = pos <= maxPos ? pos : maxPos;

            pScrollBar.SetScrollPos(pos);
            str.Format(L"%d", pos);
            break;
        }
        case SB_LINELEFT:{
            int minPos = 0, maxPos = 0;
            pScrollBar.GetScrollRange(&minPos, &maxPos);
            int pos = pScrollBar.GetScrollPos();
            pos -= (maxPos - minPos) / 100;
            pos = pos >= minPos ? pos : minPos;

            pScrollBar.SetScrollPos(pos);
            str.Format(L"%d", pos);
            break;
        }
        default:
            return;
        }

        if (pScrollBar == m_bitrate) {
            m_bitrate_value_str.SetWindowText(str);
        }
        else if (pScrollBar == m_screen_bitrate) {
            m_screen_bitrate_value_str.SetWindowText(str);
        }
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        if (wndStatic == m_title) {
            dc.SetBkColor(RGB(0xFF, 0xFF, 0xFF));
            dc.SetTextColor(RGB(0x1D, 0x21, 0x29));
        } 
        else if (wndStatic == m_title_solution
            || wndStatic ==  m_title_screen_solution
            || wndStatic == m_title_frames
            || wndStatic == m_title_screen_frames
            || wndStatic == m_title_bitrate
            || wndStatic == m_title_input
            || wndStatic == m_title_camera
            || wndStatic == m_title_history
            || wndStatic == m_title_my_videos
            || wndStatic == m_title_avinfo)
        {
            dc.SetBkColor(RGB(0xFF, 0xFF, 0xFF));
            dc.SetTextColor(RGB(0x4E, 0x59, 0x69));
        }
        else if (wndStatic == m_bitrate_value_str
            || wndStatic == m_screen_bitrate_value_str) {
            dc.SetBkColor(RGB(0xF2, 0xF3, 0xF8));
            dc.SetTextColor(RGB(0x4E, 0x59, 0x69));
            return bitrateBk;
        }
        return allBk;
    }

    LRESULT OnClickClose(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        return OnClickCancel(wNotifyCode, wID, hWndCtl, bHandled);
    }

    LRESULT OnClickOk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        SetProfile();

        ShowWindow(SW_HIDE);
        ::SendMessage(m_message_handler, WM_NOTIFY_CLOSE_SETTING, 0, 0);
        return 0;
    }

    LRESULT OnClickCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        RecoveryState();

        ShowWindow(SW_HIDE);
        ::SendMessage(m_message_handler, WM_NOTIFY_CLOSE_SETTING, 0, 0);
        return 0;
    }

    LRESULT OnInputSel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        m_title.SetFocus();
        if (wID == DUID_RESOLUTION) {
            const VideoProfile& videoProfile = m_video_profiles[m_solutions.GetCurSel()];
            m_bitrate.SetScrollRange(videoProfile.minBitrate, videoProfile.maxBitrate);

            double value = videoProfile.maxBitrate / 2.5;
            m_bitrate.SetScrollPos(value);

            BDString str;
            str.Format(L"%d", (int)value);
            m_bitrate_value_str.SetWindowText(str);
        }
        else if (wID == DUID_SCREEN_RESOLUTION) {
            const VideoProfile& videoProfile = m_video_profiles[m_screen_solutions.GetCurSel()];
            m_screen_bitrate.SetScrollRange(videoProfile.minBitrate, videoProfile.maxBitrate);

            double value = videoProfile.maxBitrate / 2.5;
            m_screen_bitrate.SetScrollPos(value);

            BDString str;
            str.Format(L"%d", (int)value);
            m_screen_bitrate_value_str.SetWindowText(str);
        }

        return 0;
    }

    LRESULT OnClickShowInfo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (m_showInfo.m_state == BUTTON_STATE_DISABLE)
        {
            m_showInfo.SetState(BUTTON_STATE_NORMAL);
            //::SendMessage(GetParent(), WM_NOTIFY_AVINFO_ON, 1, 0);
        }
        else
        {
            m_showInfo.SetState(BUTTON_STATE_DISABLE);
            //::SendMessage(GetParent(), WM_NOTIFY_AVINFO_ON, 0, 0);
        }

        return 0;
    }

    UINT OnNcHitTest(BDPoint point)
    {
        ScreenToClient(&point);
        BDRect rc;
        GetClientRect(&rc);
        rc.bottom = 40;
        if (rc.PtInRect(point))
        {
            return HTCAPTION;
        }
        else
        {
            return HTCLIENT;
        }
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        dc.SelectBrush(allBk);
        BDRect rect;
        GetClientRect(&rect);
        dc.FillRect(&rect, allBk);
        dc.SelectPen((HPEN)m_grayPen);

        int x0 = 0;
        int y0 = 46;
        int x1 = rect.right;
        int y1 = 46;

        dc.MoveTo(x0, y0);
        dc.LineTo(x1, y1);

        x0 = 0;
        y0 = rect.bottom - 64;
        x1 = rect.right;
        y1 = rect.bottom - 64;

        dc.MoveTo(x0, y0);
        dc.LineTo(x1, y1);

        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
    {
        return 0;
    }

    void SetRecordList(const std::list<RecordInfo>& records) {
        m_history.Clear();
        m_my_videos.Clear();

        std::vector<RecordInfo> r(records.begin(), records.end());
        std::sort(r.begin(), r.end(), [](const RecordInfo& left, const RecordInfo& right)->bool {
            return left.meeting_start_time > right.meeting_start_time;
        });

        m_records.swap(r);
        for (int i = 0; i < m_records.size(); ++i) {
            auto& record = m_records[i];
            time_t second = record.meeting_start_time / 1000000000;
            struct tm * timeinfo = localtime(&second);
            timeinfo->tm_year += 1900;

            std::ostringstream out;
            out << timeinfo->tm_year << "/" << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_mday << " ";
            out << std::setfill('0') << std::setw(2) << timeinfo->tm_hour << ":"
                << std::setfill('0') << std::setw(2) << timeinfo->tm_min << ":"
                << std::setfill('0') << std::setw(2) << timeinfo->tm_sec;
            
            ItemAttr item;
            item.title = out.str();
            item.data = (void*)&record;

            if (record.video_holder) {
                m_my_videos.AddItem(item);
            }
            else {
                m_history.AddItem(item);
            }
        }
    }

    bool IsAVInfoShow() {
        return m_showInfo.m_state == BUTTON_STATE_NORMAL;
    }

    LRESULT OnCameraDropdown(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (!m_video_devices.empty()) {
            std::string device = m_video_devices[m_cameras.GetCurSel()].guid;
            UpdateVideoDevice(device);
        }
        return 0;
    }

    // video device state change，Update current list
    int OnVideoDeviceStateChange(const std::string& did, bytertc::MediaDeviceNotification event) {
        std::string device;

        switch (event) {
        case bytertc::kMediaDeviceNotificationActive: // New device insertion
            device = did;
            break;
        case bytertc::kMediaDeviceNotificationUnplugged: // Device pull out
            if (did != m_current_video_guid) {
                device = m_current_video_guid;
            }
            else {
                m_current_video_guid = "";
            }

            break;
        default:
            break;
        }

        UpdateVideoDevice(device);

        if (!m_video_devices.empty()) {
            if (m_current_video_guid != m_video_devices[m_cameras.GetCurSel()].guid) {
                EngineWrapper::GetInstance()->SetVideoCaptureDevice(m_cameras.GetCurSel());
                m_current_video_guid = m_video_devices[m_cameras.GetCurSel()].guid;
            }
        }

        return m_video_devices.size();
    }

    LRESULT OnInputDropdown(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        if (!m_audio_devices.empty()) {
            std::string device = m_audio_devices[m_input.GetCurSel()].guid;
            UpdateAudioDevice(device);
        }
        return 0;
    }

    // audio device state change，Update current list
    int OnAudioDeviceStateChange(const std::string& did, bytertc::MediaDeviceNotification event) {
        std::string device;

        switch (event) {
        case bytertc::kMediaDeviceNotificationActive: // New device insertion
            device = did;
            break;
        case bytertc::kMediaDeviceNotificationNotPresent: // Device pull out
            if (did != m_current_audio_guid) {
                device = m_current_audio_guid;
            }
            else {
                m_current_audio_guid = "";
            }

            break;
        default:
            break;
        }

        UpdateAudioDevice(device);

        if (!m_audio_devices.empty()) {
            if (m_current_audio_guid != m_audio_devices[m_input.GetCurSel()].guid) {
                EngineWrapper::GetInstance()->SetAudioInputDevice(m_input.GetCurSel());
                m_current_audio_guid = m_audio_devices[m_input.GetCurSel()].guid;
            }
        }

        return m_audio_devices.size();
    }

    void OnEngineCreate() {
        if (this->IsWindowVisible()) {
            OnFrameShow(true, 0);
        }
    }

    void SetMessageHander(HWND handler) {
        m_message_handler = handler;
    }

private:
    void UpdateAudioDevice(const std::string& select_device) {
        int count = m_input.GetCount();
        for (int i = count - 1; i >= 0; --i) {
            m_input.DeleteString(i);
        }

        int index = 0;
        m_audio_devices = EngineWrapper::GetInstance()->GetAudioInputDevices();
        for (int i = 0; i < (int)m_audio_devices.size(); i++) {
            BDString str = rtcutil::ConvertUTF8ToBDString(m_audio_devices[i].name);
            m_input.InsertString(i, str);

            if (m_audio_devices[i].guid == select_device) {
                index = i;
            }
        }
        m_input.SetCurSel(index);
    }

    void UpdateVideoDevice(const std::string& select_device) {
        auto count = m_cameras.GetCount();
        for (int i = count - 1; i >= 0; --i) {
            m_cameras.DeleteString(i);
        }

        int index = 0;
        m_video_devices = EngineWrapper::GetInstance()->GetVideoCaptureDevices();
        for (int i = 0; i < (int)m_video_devices.size(); i++)
        {
            BDString str = rtcutil::ConvertUTF8ToBDString(m_video_devices[i].name);
            m_cameras.InsertString(i, str);

            if (m_video_devices[i].guid == select_device) {
                index = i;
            }
        }
        m_cameras.SetCurSel(index);
    }

    void SetProfile() {
        if (m_solutions_index != m_solutions.GetCurSel()
            || m_frame_rate_index != m_frames.GetCurSel()
            || m_bitrate_value != m_bitrate.GetScrollPos()) {
            bytertc::VideoSolution vs;
            vs.width = m_video_profiles[m_solutions.GetCurSel()].width;
            vs.height = m_video_profiles[m_solutions.GetCurSel()].height;
            vs.fps = m_fps_vec[m_frames.GetCurSel()];
            vs.max_send_kbps = m_bitrate.GetScrollPos();
            EngineWrapper::GetInstance()->setVideoProfiles(&vs, 1);
        }

        if (m_screen_solutions_index != m_screen_solutions.GetCurSel()
            || m_screen_frame_rate_index != m_screen_frames.GetCurSel()
            || m_screen_bitrate_value != m_screen_bitrate.GetScrollPos()) {
            bytertc::VideoSolution vs;
            vs.width = m_video_profiles[m_screen_solutions.GetCurSel()].width;
            vs.height = m_video_profiles[m_screen_solutions.GetCurSel()].height;
            vs.fps = m_fps_vec[m_screen_frames.GetCurSel()];
            vs.max_send_kbps = m_screen_bitrate.GetScrollPos();
            EngineWrapper::GetInstance()->setScreenProfiles(vs);
        }

        if (!m_audio_devices.empty() && m_current_audio_guid != m_audio_devices[m_input.GetCurSel()].guid) {
            EngineWrapper::GetInstance()->SetAudioInputDevice(m_input.GetCurSel());
        }

        if (!m_video_devices.empty() && m_current_video_guid != m_video_devices[m_cameras.GetCurSel()].guid) {
            EngineWrapper::GetInstance()->SetVideoCaptureDevice(m_cameras.GetCurSel());
        }

        if (m_showInfo_state != m_showInfo.m_state) {
            ::PostMessage(m_message_handler, WM_NOTIFY_AVINFO_ON, m_showInfo.m_state == BUTTON_STATE_NORMAL ? 1 : 0, 0);
        }
    };

    void SaveState() {
        m_solutions_index = m_solutions.GetCurSel();
        m_frame_rate_index = m_frames.GetCurSel();

        m_screen_solutions_index = m_screen_solutions.GetCurSel();
        m_screen_frame_rate_index = m_screen_frames.GetCurSel();

        m_bitrate.GetScrollRange(&m_bitrate_range_min, &m_bitrate_range_max);
        m_bitrate_value = m_bitrate.GetScrollPos();

        m_screen_bitrate.GetScrollRange(&m_screen_bitrate_range_min, &m_screen_bitrate_range_max);
        m_screen_bitrate_value = m_screen_bitrate.GetScrollPos();

        if (!m_audio_devices.empty()) {
            m_current_audio_guid = m_audio_devices[m_input.GetCurSel()].guid;
        }

        if (!m_video_devices.empty()) {
            m_current_video_guid = m_video_devices[m_cameras.GetCurSel()].guid;
        }

        m_showInfo_state = m_showInfo.m_state;
    }

    void RecoveryState() {
        m_solutions.SetCurSel(m_solutions_index);
        m_frames.SetCurSel(m_frame_rate_index);

        m_screen_solutions.SetCurSel(m_screen_solutions_index);
        m_screen_frames.SetCurSel(m_screen_frame_rate_index);

        m_bitrate.SetScrollRange(m_bitrate_range_min, m_bitrate_range_max);
        m_bitrate.SetScrollPos(m_bitrate_value);
        BDString str;
        str.Format(L"%d", m_bitrate_value);
        m_bitrate_value_str.SetWindowText(str);

        m_screen_bitrate.SetScrollRange(m_screen_bitrate_range_min, m_screen_bitrate_range_max);
        m_screen_bitrate.SetScrollPos(m_screen_bitrate_value);
        str.Format(L"%d", m_screen_bitrate_value);
        m_screen_bitrate_value_str.SetWindowText(str);

        m_showInfo.m_state = m_showInfo_state;
    }

    void OnDeleteVideoRecord(const ItemAttr& item) {
        auto record = (RecordInfo*)item.data;
        m_my_videos.DeleteItem(item.title);
        MeetingManager::GetInstance()->deleteVideoRecord(record->vid, [](int code) {
            assert(code == 200);
        });
    }

    void OnBrowseVideoRecord(const ItemAttr& item) {
        auto record = (RecordInfo*)item.data;
        BDString url = rtcutil::ConvertUTF8ToBDString(record->url);
        ShellExecute(0, L"open", url, L"", L"", 0);
    }

private:
    struct VideoProfile {
        int width;
        int height;
        int minBitrate;
        int maxBitrate;
    };

    BDFont m_font;
    BDFont m_bitrate_font;
    BDBrush allBk;
    BDBrush bitrateBk;
    BDPen m_grayPen;

    BDStatic m_title;
    BDStatic m_title_solution;
    BDStatic m_title_screen_solution;
    BDStatic m_title_frames;
    BDStatic m_title_screen_frames;
    BDStatic m_title_bitrate;
    BDStatic m_title_input;
    BDStatic m_title_camera;
    BDStatic m_title_history;
    BDStatic m_title_my_videos;
    BDStatic m_title_avinfo;
    BDStatic m_bitrate_value_str;
    BDStatic m_bitrate_value_unit;

    BDStatic m_title_screen_bitrate;
    BDStatic m_screen_bitrate_value_str;
    BDStatic m_screen_bitrate_value_unit;

    BDBmpButton m_close;
    BDTxtButton m_cancel;
    BDTxtButton m_ok;

    BDComboBox m_solutions;
    BDComboBox m_screen_solutions;
    BDComboBox m_frames;
    BDComboBox m_screen_frames;
    BDScrollBar m_bitrate;
    BDScrollBar m_screen_bitrate;
    BDComboBox m_input;
    BDComboBox m_cameras;
    BDComboxEx m_history;
    BDComboxEx m_my_videos;
    BDBmpButton m_showInfo;

    std::vector<int> m_fps_vec;
    std::vector<VideoProfile> m_video_profiles;
    std::vector<RecordInfo> m_records;

    int m_solutions_index = -1;
    int m_frame_rate_index = 0;

    int m_screen_solutions_index = -1;
    int m_screen_frame_rate_index = 0;

    int m_bitrate_range_min = 0;
    int m_bitrate_range_max = 0;
    int m_bitrate_value = 0;

    int m_screen_bitrate_range_min = 0;
    int m_screen_bitrate_range_max = 0;
    int m_screen_bitrate_value = 0;

    int m_showInfo_state = -1;

    std::string m_current_audio_guid;
    std::string m_current_video_guid;
    std::vector<RtcDevice> m_video_devices;
    std::vector<RtcDevice> m_audio_devices;

    HWND m_message_handler = nullptr;
};

