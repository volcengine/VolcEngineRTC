//
//  BDMainFrame.h
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
#include "BDMeetingLoginWnd.h"
#include "BDUserWnd.h"
#include "BDControlWnd.h"
#include "BDUserVideoViewWnd.h"
#include "BDSettingWnd.h"
#include "BDTopBarWnd.h"
#include "BDFeedbackWnd.h"
#include "BDBubbleTipWnd.h"
#include "BDRateWnd.h"
#include "ByteMessage.h"
#include "BDAVInfoWnd.h"
#include "BDSnapshotWnd.h"
#include "BDLeaveWnd.h"
#include "BDMaskWnd.h"
#include "meeting-manager/IMeetingNotification.h"
#include "meeting-manager/MeetingManager.h"
#include "BDMessageWnd.h"
#include "json/json.h"
#include <mutex>
#include <list>
#include <string>

class User;

#define LOGIN_WND_WIDTH  736
#define LOGIN_WND_HEIGHT 80

#define WARNING_WND_WIDTH  240
#define WARNING_WND_HEIGHT 131

#define AVINFO_WND_WIDTH  180
#define AVINFO_WND_HEIGHT 348

#define TOPBAR_WND_HEIGHT 50

#define KICKOFF_WND_WIDTH 250
#define KICKOFF_WND_HEIGHT 40

#define CONTROL_WND_WIDTH 401
#define CONTROL_WND_HEIGHT 48

#define SETTING_WND_WIDTH 720
#define SETTING_WND_HEIGHT 540

#define HOST_LEAVE_WND_WIDTH 400
#define HOST_LEAVE_WND_HEIGHT 258

#define CLIENT_LEAVE_WND_WIDTH 400
#define CLIENT_LEAVE_WND_HEIGHT 202

#define SNAPSHOT_WND_WIDTH 800
#define SNAPSHOT_WND_HEIGHT 504

#define USER_WND_WIDTH 280
#define USER_WND_HEIGHT 500

#define MESSAGE_WND_WIDTH 300
#define MESSAGE_WND_HEIGHT 140

#define VIDEO_VIEW_WND_WIDTH  160
#define VIDEO_VIEW_WND_HEIGHT 92
#define VIDEO_VIEW_WND_SPACE  12

#define RATE_WND_WIDTH 320
#define RATE_WND_HEIGHT 126

#define FEEDBACK_WND_WIDTH 480
#define FEEDBACK_WND_HEIGHT 306

//#define MAX_USER_VIDEO_VIEW_COUNT 9

#define LOCAL_VIDEO_MUTE_MAIN L"resource\\head_local.png"
#define HEAD_SHARE L"resource\\head_speaker_shared.png"
#define HEAD_2_4 L"resource\\head_two_four.png"
#define HEAD_9 L"resource\\head_nine.png"
#define HEAD_ONER L"resource\\local_oner.png"

/**
*  UI layout Style
*/
enum ViewLayoutStyle
{
    VIEW_UNKNOW_STYLE = -1, // Unknown layout
    GALLERY_ONER_STYLE = 0, // Layout of a room with only one person, gallery Mode
    GALLERY_TWO_STYLE,      // Layout of a room with two persons, gallery Mode
    GALLERY_FOUR_STYLE,     // Layout when there are 3-4 people in the room, gallery Mode
    GALLERY_SIX_STYLE,     // Layout when there are 5-6 people in the room, gallery Mode
    GALLERY_NINE_STYLE,     // Layout of a room with 7 persons or more, gallery Mode
    SPEAKER_STYLE,          // Layout for remote screen sharing, speaker mode
    LOCAL_SHARE_STYLE,      // Layout for local screen sharing
    LOGIN_STYLE             // Layout at login
};

class BDMainContainerFrame : public BDWndImpl<BDMainContainerFrame>, public IMeetingNotification, public bytertc::IVideoFrameObserver
{
public:
    DECLARE_BDWND_CLASS(L"BDMainContainerFrame")
    BDMainContainerFrame():m_main_view_container(true), m_login_local_view(true) {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x1D, 0x21, 0x29));
        if (!wci.m_atom) {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_APP_LOGO));
        }
    }

    void SetVerifySms(const VerifySms& sms) {
        m_sms = sms;
    }

    BEGIN_MSG_MAP(BDMainFrame)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_GETMINMAXINFO(OnMinMaxInfo)
        MSG_WM_SIZE(OnSize)
        MSG_WM_MOVE(OnMove)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MSG_WM_CLOSE(OnClose)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_TIMER(OnTimer)
        MESSAGE_HANDLER(WM_NOTIFY_MODIFY_NICKNAME_ERROR, ModifyUserNicknameError)
        MESSAGE_HANDLER(WM_NOTIFY_VIEW_ATTACH, OnViewAttach)
        MESSAGE_HANDLER(WM_NOTIFY_VIEEW_RELAYOUT, OnRemoteViewRelayout)
        MESSAGE_HANDLER(WM_NOTIFY_INVALID_TOKEN, OnInvalidToken)
        MESSAGE_HANDLER(WM_NOTIFY_JOIN_OK, OnJoinOK)
        MESSAGE_HANDLER(WM_NOTIFY_REMOTE_SCREEN_FIRST_VIDEO, OnFirstRemoteScreenVideo)
        MESSAGE_HANDLER(WM_NOTIFY_REMOTE_FIRST_VIDEO, OnFirstRemoteVideo)
        MESSAGE_HANDLER(WM_NOTIFY_LEAVE, OnLeaveClick)
        MESSAGE_HANDLER(WM_NOTIFY_LEAVE_SUCCEED, OnLeaveSucceed)
        MESSAGE_HANDLER(WM_NOTIFY_AUDIO_VOLUME, OnAudioVolumeIndication)
        MESSAGE_HANDLER(WM_NOTIFY_WARNING, OnLoginWarning)
        MESSAGE_HANDLER(WM_NOTIFY_SHOW_USER, OnShowUser)
        MESSAGE_HANDLER(WM_NOTIFY_SHOW_SETTING, OnShowSetting)
        MESSAGE_HANDLER(WM_NOTIFY_LOGIN_CLICK, OnLoginClick)
        MESSAGE_HANDLER(WM_NOTIFY_AUDIO_DEVICE_EVENT, OnAudioStateChange)
        MESSAGE_HANDLER(WM_NOTIFY_VIDEO_DEVICE_EVENT, OnVideoStateChange)
        MESSAGE_HANDLER(WM_NOTIFY_INVALID_DEVICE, OnInvalidDevice)
        MESSAGE_HANDLER(WM_VIDEO_DEVICE_STATE_CHANGE, OnLocalVideoStateChanged)
        MESSAGE_HANDLER(WM_AUDIO_DEVICE_STATE_CHANGE, OnLocalAudioStateChanged)
        MESSAGE_HANDLER(DUID_MEETING_END, OnMeetingEnd)
        MESSAGE_HANDLER(DUID_MEETING_LEAVE, OnMeetingLeave)
        MESSAGE_HANDLER(DUID_MEETING_CANCEL, OnMeetingCancel)
        MESSAGE_HANDLER(WM_NOTIFY_VIDEO_PREVIEW, OnLocalVideoPreview)
        MESSAGE_HANDLER(WM_NOTIFY_CLOSE_USER, OnCloseUser)
        MESSAGE_HANDLER(WM_NOTIFY_SCREEN_SHARE, onStartShareScreen)
        MESSAGE_HANDLER(WM_NOTIFY_CLOSE_SHARE, onCloseShareScreen)
        MESSAGE_HANDLER(WM_MASK_CLICK, onCloseShareScreen)
        MESSAGE_HANDLER(WM_NOTIFY_RECORD_VIDEO, onRecordVideo)
        MESSAGE_HANDLER(WM_NOTIFY_CLOSE_SETTING, OnCloseSetting)
        MESSAGE_HANDLER(WM_NOTIFY_AVINFO_ON, OnAVInfoSetting)
        MESSAGE_HANDLER(WM_NOTIFY_MUTE_CHANGE, OnMuteChange)
        //MESSAGE_HANDLER(WM_NOTIFY_KICK_OFF, OnKickOff)
        MESSAGE_HANDLER(WM_LOG, OnLogReport)

        MESSAGE_HANDLER(WM_NOTIFY_RTC_STATS, OnRtcStats)
        MESSAGE_HANDLER(WM_NOTIFY_LOCAL_VIDEO_STATS, OnLocalVideoStats)
        MESSAGE_HANDLER(WM_NOTIFY_LOCAL_AUDIO_STATS, OnLocalAudioStats)
        MESSAGE_HANDLER(WM_NOTIFY_REMOTE_VIDEO_STATS, OnRemoteVideoStats)
        MESSAGE_HANDLER(WM_NOTIFY_REMOTE_AUDIO_STATS, OnRemoteAudioStats)

        MESSAGE_HANDLER(WM_RATE, OnRate)
        MESSAGE_HANDLER(WM_FEEDBACK, OnFeedback)
        MESSAGE_HANDLER(WM_LOCAL_AUDIO, OnFirstLocalAudio)
        MESSAGE_HANDLER(WM_LOCAL_VIDEO, OnFirstLocalVideo)
        MESSAGE_HANDLER(WM_NOTIFY_STREAMS_ADD, OnStreamsAdd)
        MESSAGE_HANDLER(WM_NOTIFY_STREAMS_REMOVE, OnStreamsRemove)

        MESSAGE_HANDLER(WM_NOTIFY_CHANNEL_LEAVE_SUCCEED, OnSDKLeaveChannelSucceed)
        MESSAGE_HANDLER(WM_NOTIFY_USER_LEAVE_SUCCEED, OnSDKUserOfflineSucceed)

        MESSAGE_HANDLER(WM_NOTIFY_FUNCTION_EXECUTE, OnFunctionExec)
    END_MSG_MAP()

    /**
    *  Create UI windows
    */
    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        EngineWrapper::GetInstance()->setEventHandler(m_hWnd);

        BDHMenu m;
        BDRect r1(0, TOPBAR_WND_HEIGHT, 1080, 720);
        m_main_view_container.Create(m_hWnd, &r1, m, 0, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN);
        m_login_local_view.Create(m_main_view_container.m_hWnd, &r1, m, 0, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN);
        m_login_local_view.SetHeader(LOCAL_VIDEO_MUTE_MAIN, 36);

        BDRect rLogin(0, TOPBAR_WND_HEIGHT, LOGIN_WND_WIDTH, TOPBAR_WND_HEIGHT + LOGIN_WND_HEIGHT);
        m_loginWnd.SetUserNickname(m_sms.user_name);
        m_loginWnd.Create(m_login_local_view.m_hWnd, &rLogin, m, 0, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN);
        HRGN hLoginRgn = ::CreateRoundRectRgn(0, 0, LOGIN_WND_WIDTH, LOGIN_WND_HEIGHT, LOGIN_WND_HEIGHT, LOGIN_WND_HEIGHT);
        m_loginWnd.SetWindowRgn(hLoginRgn);
        m_loginWnd.SetMessageHandler(m_hWnd);

        BDRect rWarning(0, TOPBAR_WND_HEIGHT, WARNING_WND_WIDTH, TOPBAR_WND_HEIGHT + WARNING_WND_HEIGHT);
        m_login_warning.Create(m_login_local_view.m_hWnd, &rWarning, m, 0, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN);
        HRGN hWarningRgn = ::CreateRoundRectRgn(0, 0, WARNING_WND_WIDTH, WARNING_WND_HEIGHT, 2, 2);
        m_login_warning.SetWindowRgn(hWarningRgn);
        m_login_warning.ShowWindow(SW_HIDE);

        BDRect rTopbar(0, 0, 600, TOPBAR_WND_HEIGHT);
        m_topbarWnd.Create(m_hWnd, &rTopbar, m, 0, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN);

        //BDRect rControl(0, TOPBAR_WND_HEIGHT, CONTROL_WND_WIDTH, TOPBAR_WND_HEIGHT + CONTROL_WND_HEIGHT);
        //m_controlWnd.Create(m_main_view_container.m_hWnd, &rControl, m, 0, WS_POPUP);
        //HRGN hControlRgn = ::CreateRoundRectRgn(0, 0, CONTROL_WND_WIDTH, CONTROL_WND_HEIGHT, CONTROL_WND_HEIGHT, CONTROL_WND_HEIGHT);
        //m_controlWnd.SetWindowRgn(hControlRgn);
        //m_controlWnd.SetMessageHandler(m_hWnd);

        m_main_mask.Create(m_hWnd, &rWarning, m, 0, WS_POPUP);
        m_main_mask.SetMessageHander(m_hWnd);

        BDRect rUser(0, TOPBAR_WND_HEIGHT, USER_WND_WIDTH, TOPBAR_WND_HEIGHT + USER_WND_HEIGHT);
        m_userWnd.Create(m_hWnd, &rUser, m, 0, WS_CHILD | WS_CLIPCHILDREN);

        BDRect rSetting(0, TOPBAR_WND_HEIGHT, SETTING_WND_WIDTH, TOPBAR_WND_HEIGHT + SETTING_WND_HEIGHT);
        m_settingWnd.Create(m_main_mask.m_hWnd, &rSetting, m, 0, WS_POPUP);
        HRGN hSettingRgn = ::CreateRoundRectRgn(0, 0, SETTING_WND_WIDTH, SETTING_WND_HEIGHT, 4, 4);
        m_settingWnd.SetWindowRgn(hSettingRgn);
        m_settingWnd.SetMessageHander(m_hWnd);

        BDRect rMessage(0, TOPBAR_WND_HEIGHT, MESSAGE_WND_WIDTH, TOPBAR_WND_HEIGHT + MESSAGE_WND_HEIGHT);
        m_messageWnd.Create(m_main_mask.m_hWnd, &rMessage, m, 0, WS_POPUP);
        HRGN hMessageRgn = ::CreateRoundRectRgn(0, 0, MESSAGE_WND_WIDTH, MESSAGE_WND_HEIGHT, 4, 4);
        m_messageWnd.SetWindowRgn(hMessageRgn);

        BDRect rKickoff(0, 0, KICKOFF_WND_WIDTH + 100, KICKOFF_WND_HEIGHT);
        m_bubbleTipWnd.Create(m_hWnd, &rKickoff, m, 0, WS_POPUP);
        HRGN bubbleRgn = ::CreateRoundRectRgn(0, 0, KICKOFF_WND_WIDTH + 100, KICKOFF_WND_HEIGHT, 10, 10);
        m_bubbleTipWnd.SetWindowRgn(bubbleRgn);

        BDRect rleave(0, HOST_LEAVE_WND_HEIGHT, HOST_LEAVE_WND_WIDTH, TOPBAR_WND_HEIGHT + HOST_LEAVE_WND_HEIGHT);
        m_leaveWnd.Create(m_main_mask.m_hWnd, &rleave, m, 0, WS_POPUP);
        HRGN hLeaveRgn = ::CreateRoundRectRgn(0, 0, HOST_LEAVE_WND_WIDTH, HOST_LEAVE_WND_HEIGHT, 4, 4);
        m_leaveWnd.SetWindowRgn(hLeaveRgn);
        m_leaveWnd.ShowWindow(SW_HIDE);
        m_leaveWnd.SetMessageHander(m_hWnd);

        BDRect rRate(0, 0, RATE_WND_WIDTH, RATE_WND_HEIGHT);
        m_rateWnd.Create(m_main_mask.m_hWnd, &rRate, m, 0, WS_POPUP);
        HRGN hRateRgn = ::CreateRoundRectRgn(0, 0, RATE_WND_WIDTH, RATE_WND_HEIGHT, 4, 4);
        m_rateWnd.SetWindowRgn(hRateRgn);
        m_rateWnd.SetMessageHander(m_hWnd);

        BDRect rFeedback(0, 0, FEEDBACK_WND_WIDTH, FEEDBACK_WND_HEIGHT);
        m_feedbackWnd.Create(m_main_mask.m_hWnd, &rFeedback, m, 0, WS_POPUP);
        HRGN hFeedbackRgn = ::CreateRoundRectRgn(0, 0, FEEDBACK_WND_WIDTH, FEEDBACK_WND_HEIGHT, 4, 4);
        m_feedbackWnd.SetWindowRgn(hFeedbackRgn);
        m_feedbackWnd.SetMessageHander(m_hWnd);

        BDRect rSnapshot(0, TOPBAR_WND_HEIGHT, SNAPSHOT_WND_WIDTH, TOPBAR_WND_HEIGHT + SNAPSHOT_WND_HEIGHT);
        m_snapshotWnd.Create(m_main_mask.m_hWnd, &rSnapshot, m, 0, WS_POPUP);
        HRGN hSnapshotRgn = ::CreateRoundRectRgn(0, 0, SNAPSHOT_WND_WIDTH, SNAPSHOT_WND_HEIGHT, 4, 4);
        m_snapshotWnd.SetWindowRgn(hSnapshotRgn);
        m_snapshotWnd.SetMessageHandler(m_hWnd);

        BDRect rAVinfo(0, TOPBAR_WND_HEIGHT, AVINFO_WND_WIDTH, TOPBAR_WND_HEIGHT + AVINFO_WND_HEIGHT);
        m_avInfoWnd.Create(m_hWnd, &rAVinfo, m, 0, WS_POPUP);

        MeetingManager::GetInstance()->registerNotification(this);
        //MeetingManager::GetInstance()->startConnect();
        return 0;
    }

    void OnMinMaxInfo(LPMINMAXINFO info) {
        RECT r = {0, 0, 960, 720};
        AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);

        info->ptMinTrackSize.x = r.right - r.left;
        info->ptMinTrackSize.y = r.bottom - r.top;
    }

    // 深度优化
    void OnSize(UINT nType, BDSize size) {
        if (size.cx <= 0 || size.cy <= 0) {
            return;
        }

        bool change = m_width != size.cx || m_height != size.cy;
        m_width = size.cx;
        m_height = size.cy;

        int userViewWidth = 0;
        if (m_userWnd.IsWindowVisible()) {
            userViewWidth = USER_WND_WIDTH;
            m_userWnd.MoveWindowEx(m_width - USER_WND_WIDTH, 0, USER_WND_WIDTH, m_height);
        }

        m_topbarWnd.MoveWindowEx(0, 0, m_width, TOPBAR_WND_HEIGHT);
        HRGN rgn = ::CreateRoundRectRgn(0, 0, m_width - userViewWidth, TOPBAR_WND_HEIGHT, 0, 0);
        m_topbarWnd.SetWindowRgn(rgn);

        m_main_view_container.Highlight(false);
        m_main_view_container.MoveWindowEx(0, TOPBAR_WND_HEIGHT, m_width, m_height - TOPBAR_WND_HEIGHT);
        rgn = ::CreateRoundRectRgn(0, 0, m_width - userViewWidth, m_height - TOPBAR_WND_HEIGHT, 0, 0);
        m_main_view_container.SetWindowRgn(rgn);

        if (!change && !userViewWidth) {
            for (auto& user : m_users) {
                if (!user.m_view) continue;

                if ( user.m_view->IsWindowVisible()) {
                    user.m_view->TitleFresh();
                } else {
                    break;
                }
            }

            m_topbarWnd.Invalidate();
        }

        if (change) {
            SetViewLayout(m_view_style);
            OnMove(0, 0);
        }

        m_main_view_container.Invalidate();
    }

    void OnMove(int x, int y) {
        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);

        if (m_main_mask.IsWindowVisible()) {
            m_main_mask.MoveWindow(rc.left + 10,
                rc.top,
                rc.right - rc.left - 20,
                rc.bottom - rc.top - 10);
        }

        if (m_settingWnd.IsWindowVisible()) {
            m_settingWnd.MoveWindow((rc.right + rc.left) / 2 - SETTING_WND_WIDTH / 2,
                (rc.top + rc.bottom ) / 2 - SETTING_WND_HEIGHT / 2,
                SETTING_WND_WIDTH,
                SETTING_WND_HEIGHT);
            m_settingWnd.BringWindowToTop();
        }

        if (m_messageWnd.IsWindowVisible()) {
            m_messageWnd.MoveWindow(rc.left + m_width / 2 - MESSAGE_WND_WIDTH / 2,
                rc.top + m_height / 2 - MESSAGE_WND_HEIGHT / 2,
                MESSAGE_WND_WIDTH,
                MESSAGE_WND_HEIGHT);
            m_messageWnd.BringWindowToTop();
        }

        if (m_bubbleTipWnd.IsWindowVisible()) {
            RECT bubbleRc;
            m_bubbleTipWnd.GetClientRect(&bubbleRc);
            m_bubbleTipWnd.MoveWindow(rc.left + (m_width - bubbleRc.right) / 2, rc.top + 100,
                bubbleRc.right, KICKOFF_WND_HEIGHT);
            m_bubbleTipWnd.BringWindowToTop();
        }

        if (m_snapshotWnd.IsWindowVisible()) {
            m_snapshotWnd.MoveWindow(rc.left + m_width / 2 - SNAPSHOT_WND_WIDTH / 2,
                rc.bottom - SNAPSHOT_WND_HEIGHT - 96,
                SNAPSHOT_WND_WIDTH,
                SNAPSHOT_WND_HEIGHT);
            m_snapshotWnd.BringWindowToTop();
        }

        if (m_avInfoWnd.IsWindowVisible()) {
            m_avInfoWnd.MoveWindow(rc.left + 12, rc.bottom - AVINFO_WND_HEIGHT - 12,
                AVINFO_WND_WIDTH, AVINFO_WND_HEIGHT);
        }

        if (m_rateWnd.IsWindowVisible()) {
            m_rateWnd.MoveWindow(rc.left + (rc.right - rc.left - RATE_WND_WIDTH) / 2, rc.top + (rc.bottom - rc.top - RATE_WND_HEIGHT) / 2,
                RATE_WND_WIDTH, RATE_WND_HEIGHT);
        }

        if (m_feedbackWnd.IsWindowVisible()) {
            m_feedbackWnd.MoveWindow(rc.left + (rc.right - rc.left - FEEDBACK_WND_WIDTH) / 2, rc.bottom - FEEDBACK_WND_HEIGHT - 247,
                FEEDBACK_WND_WIDTH, FEEDBACK_WND_HEIGHT);
        }

        if (!m_users.empty() && m_leaveWnd.IsWindowVisible()) {
            auto host = m_users.begin();
            if (host->m_isHost && host->m_type == UserType::LOCAL_USER) {
                m_leaveWnd.MoveWindow(rc.left + (m_width - HOST_LEAVE_WND_WIDTH) / 2, rc.top + (m_height - HOST_LEAVE_WND_HEIGHT) / 2,
                    HOST_LEAVE_WND_WIDTH, HOST_LEAVE_WND_HEIGHT, FALSE);
            }
            else {
                m_leaveWnd.MoveWindow(rc.left + (m_width - CLIENT_LEAVE_WND_WIDTH) / 2, rc.top + (m_height - CLIENT_LEAVE_WND_HEIGHT) / 2,
                    CLIENT_LEAVE_WND_WIDTH, CLIENT_LEAVE_WND_HEIGHT, FALSE);
            }
        }
    }

    void OnFrameShow(BOOL show, int lParam) {
        CheckUpdateApp(show);

        if (show) {
            SetViewLayout(m_view_style);
        } else {
            for (auto& user : m_users) {
                if (user.m_view) {
                    user.m_view->ShowWindow(SW_HIDE);
                }
            }
        }

        if (m_room_id.empty()) {
            m_loginWnd.ShowWindow(show ? SW_SHOW : SW_HIDE);
        }

        if (show) {
            OnMove(0, 0);
        }

        if (m_view_style == LOCAL_SHARE_STYLE && show) { // Prevention of accidents
            ShowWindow(SW_HIDE);
        }
    }

    void SetViewLayout(ViewLayoutStyle style) {
        if (style != LOCAL_SHARE_STYLE  && m_view_style != style) { // when m_view_style == LOCAL_SHARE_STYLE, it need special treatment
            DestroyControl();
        }

        bool change = m_view_style != style;
        m_view_style = style;
        switch (m_view_style) {
        case GALLERY_ONER_STYLE:
            ViewLayoutOner();
            break;
        case GALLERY_TWO_STYLE:
            ViewLayoutTwo();
            break;
        case GALLERY_FOUR_STYLE:
            ViewLayoutFour();
            break;
        case GALLERY_SIX_STYLE:
            ViewLayoutSix();
            break;
        case GALLERY_NINE_STYLE:
            ViewLayoutNine();
            break;
        case SPEAKER_STYLE:
            ViewLayoutSpeaker(change);
            break;
        case LOCAL_SHARE_STYLE:
            ViewLayoutLocalShare(change);
            break;
        case LOGIN_STYLE:
            ViewLayoutLogin();
            break;
        default:
            break;
        }

        if (change) {
            UpdateRecordVideoLayout([this](int code) {
                if (code != 200) {
                    BDString inf;
                    inf.Format(L"更新录制布局失败，错误码: %d", code);
                    ShowBubbleTip(inf);
                }
            });
        }
    }

    void ViewLayoutOner() {
        assert(m_users.size() <= 1);
        m_topbarWnd.ListShow(false, IDB_LISTHIDEN);

        RECT rc;
        m_main_view_container.GetClientRect(&rc);
        int delta = 2;
        RECT view_rc;

        for (auto& user : m_users) {
            if (user.m_view && user.m_type == UserType::LOCAL_USER) {
                if (user.m_view->MoveWindowEx(delta - 1, delta - 1, rc.right - 2 * delta - 2, rc.bottom - 2 * delta)) {
                    HRGN hRgn = ::CreateRoundRectRgn(delta - 1, delta - 1, rc.right - 2 * delta - 2, rc.bottom - 2 * delta, 2, 2);
                    user.m_view->SetWindowRgn(hRgn);
                    user.m_view->SetHeader(HEAD_ONER, 80);
                }

                user.m_view->ShowWindow(SW_SHOW);
                user.m_view->BringWindowToTop();
                user.m_view->SetupLocal(true);
                
                user.m_view->GetClientRect(&view_rc);
                if (!m_controlWnd) {
                    ReCreateControl(user.m_view->m_hWnd);
                }
            } else if(user.m_view){
                user.m_view->ShowWindow(SW_HIDE);
            }
        }

        if (m_show_av_info && m_settingWnd.IsAVInfoShow()) {
            AVInfoShow(true);
        }

        if (m_controlWnd) {
            m_controlWnd->MoveWindow((view_rc.right - CONTROL_WND_WIDTH) / 2, view_rc.bottom - 18 - CONTROL_WND_HEIGHT, CONTROL_WND_WIDTH, CONTROL_WND_HEIGHT);
            m_controlWnd->SetMobile(false);
            if (!m_controlWnd->IsWindowVisible()) {
                m_controlWnd->ShowWindow(SW_SHOW);
            }
        }
    }

    void ViewLayoutTwo() {
        assert(m_users.size() == 2);

        m_topbarWnd.ListShow(false, IDB_LISTHIDEN);
        if (m_show_av_info && m_settingWnd.IsAVInfoShow()) {
            AVInfoShow(true);
        }
        m_main_view_container.Highlight(false);

        const int row = 1;
        const int column = 2;
        LayoutGallery(row, column, HEAD_2_4, 36);
    }

    void ViewLayoutFour() {
        assert(m_users.size() >= 3 && m_users.size() <= 4);

        m_topbarWnd.ListShow(false, IDB_LISTHIDEN);
        if (m_show_av_info && m_settingWnd.IsAVInfoShow()) {
            AVInfoShow(true);
        }
        m_main_view_container.Highlight(false);

        const int row = 2;
        const int column = 2;
        LayoutGallery(row, column, HEAD_2_4, 36);
    }

    void ViewLayoutSix() {
        assert(m_users.size() >= 5 && m_users.size() <= 6);

        m_topbarWnd.ListShow(false, IDB_LISTHIDEN);
        if (m_show_av_info && m_settingWnd.IsAVInfoShow()) {
            AVInfoShow(true);
        }
        m_main_view_container.Highlight(false);

        const int row = 2;
        const int column = 3;
        LayoutGallery(row, column, HEAD_2_4, 36);
    }

    void ViewLayoutNine() {
        assert(m_users.size() >= 7);

        m_topbarWnd.ListShow(false, IDB_LISTHIDEN);
        if (m_show_av_info && m_settingWnd.IsAVInfoShow()) {
            AVInfoShow(true);
        }
        m_main_view_container.Highlight(false);

        const int row = 3;
        const int column = 3;
        LayoutGallery(row, column, HEAD_9, 24);
    }

    void ViewLayoutSpeaker(bool updata_position) {
        assert(m_view_style == SPEAKER_STYLE);
        assert(!m_users.empty());

        m_topbarWnd.ListShow(true, m_speakerListShow ? IDB_LISTHIDEN : IDB_LISTSHOW);
        if (m_show_av_info && m_settingWnd.IsAVInfoShow()) {
            AVInfoShow(true);
        }
        m_main_view_container.Highlight(false);

        ViewLayoutSpeakerUsers(updata_position);
    }

    void ViewLayoutSpeakerUsers(bool updata_position) {
        RECT rc;
        m_main_view_container.GetClientRect(&rc);
        int count = 0; // default SPEAKER_HIDE_STYLE
        int space_left = 0;
        int delta_x = 0;
        int delta_y = 0;

        if (m_speakerListShow) {
            count = (rc.right - VIDEO_VIEW_WND_SPACE) / (VIDEO_VIEW_WND_WIDTH + VIDEO_VIEW_WND_SPACE);
            if (count > 8) {
                count = 8;
            }

            if (count > m_users.size()) {
                count = m_users.size();
            }

            space_left = (rc.right - VIDEO_VIEW_WND_WIDTH * count - VIDEO_VIEW_WND_SPACE * (count - 1)) / 2;
            delta_y = VIDEO_VIEW_WND_HEIGHT + 8;
        }

        RECT screen_rc = rc;
        auto posUser = m_users.begin();
        for (int i = 0; posUser != m_users.end(); ++i, ++posUser) {
            BDUserVideoViewWnd* view = posUser->m_view;

            if (view) {
                if (view->MoveWindowEx(space_left + (VIDEO_VIEW_WND_WIDTH + VIDEO_VIEW_WND_SPACE) * i, 2, VIDEO_VIEW_WND_WIDTH, VIDEO_VIEW_WND_HEIGHT)) {
                    HRGN hRgn = ::CreateRoundRectRgn(0, 0, VIDEO_VIEW_WND_WIDTH, VIDEO_VIEW_WND_HEIGHT, 2, 2);
                    view->SetWindowRgn(hRgn);
                    view->SetHeader(HEAD_SHARE, 20);
                }

                if (view->IsWindowVisible() != (i < count)) {
                    view->ShowWindow(i < count ? SW_SHOW : SW_HIDE);
                    view->BringWindowToTop();
                }
            }

            if (posUser->m_shared && posUser->m_screen_view) { // Shared screen window
                posUser->m_screen_view->MoveWindowEx(0, delta_y, rc.right, rc.bottom - delta_y);
                if (!posUser->m_screen_view->IsWindowVisible()) {
                    posUser->m_screen_view->ShowWindow(SW_SHOW);
                }

                posUser->m_screen_view->GetClientRect(&screen_rc);
                if (!m_controlWnd) {
                    ReCreateControl(posUser->m_screen_view->m_hWnd);
                }
            }
        }

        if (m_controlWnd) {
            if (updata_position) {
                m_controlWnd->MoveWindow((screen_rc.right - CONTROL_WND_WIDTH) / 2, screen_rc.bottom - 18 - CONTROL_WND_HEIGHT, CONTROL_WND_WIDTH, CONTROL_WND_HEIGHT);
            }
            m_controlWnd->ResetScreenSharedState(true);
            m_controlWnd->SetMobile(true);
            m_controlWnd->ShowWindow(SW_SHOW);
        }
    }

    // Layout when sharing screens locally
    void ViewLayoutLocalShare(bool updata_position) {
        m_main_mask.ShowWindow(SW_HIDE);
        m_snapshotWnd.ShowWindow(SW_HIDE);
        AVInfoShow(false);
        m_main_view_container.Highlight(false);

        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);

        RECT display;
        std::vector<RECT> displayList;
        rtcutil::GetDisplayList(displayList);
        for (auto& screen : displayList) {
            if (screen.left < (rc.left + rc.right) / 2 && screen.right > (rc.left + rc.right) / 2
                && screen.top < (rc.top + rc.bottom) / 2 && screen.bottom > (rc.top + rc.bottom) / 2) {
                display = screen;
            }
        }

        BDRect rControl(display.left + (display.right - display.left - CONTROL_WND_WIDTH) / 2,
            display.bottom  - CONTROL_WND_HEIGHT - 100,
            display.left + (display.right - display.left - CONTROL_WND_WIDTH) / 2 + CONTROL_WND_WIDTH,
            display.bottom - 100);

        //if (!m_controlWnd) {
        //    ReCreateControl(m_hWnd, true);
        //}
        if (m_controlWnd) {
            if (updata_position) {
                m_controlWnd->SetWindowPos(HWND_TOPMOST, rControl.left, rControl.top, rControl.right - rControl.left, rControl.bottom - rControl.top, SWP_SHOWWINDOW);
            }
            m_controlWnd->ResetScreenSharedState(true);
            m_controlWnd->SetMobile(true);
        }
    }

    // Gallery layout
    void LayoutGallery(const int row, const int column, const BDString& icon, int font_size) {
        const int GAP = row >= 3 ? 8 : 24;

        RECT rc;
        m_main_view_container.GetClientRect(&rc);
        double w = double(rc.right - (column + 1) * GAP) / column;
        double h = double(rc.bottom - 2 * 8 - CONTROL_WND_HEIGHT  - (row + 1) * GAP) / row;
        int rowGap = GAP;
        int columGap = GAP;

        if (w > 2 * h) {
            w = 2 * h;
            columGap = (rc.right - w * column) / (column + 1);
        }
        else {
            h = w / 2;
            rowGap = (rc.bottom - 2 * 8 - CONTROL_WND_HEIGHT  - h * row) / (row + 1);
        }

        auto posUser = m_users.begin();
        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < column; ++c) {
                BDUserVideoViewWnd* view = nullptr;
                if (posUser != m_users.end()) {
                    view = posUser->m_view;
                    ++posUser;

                    if (view) {
                        if (view->MoveWindowEx(columGap + c * (columGap + w), rowGap + r * (rowGap + h), w, h)) {
                            HRGN hRgn = ::CreateRoundRectRgn(0, 0, w, h, 2, 2);
                            view->SetWindowRgn(hRgn);
                            view->SetHeader(icon, font_size);
                        }

                        if (!view->IsWindowVisible()) {
                            view->ShowWindow(SW_SHOW);
                            view->BringWindowToTop();
                        }
                    }
                    else {
                        break;
                    }
                }
            }
        }

        // Others have to hide
        for (;  posUser != m_users.end(); ++posUser) {
            if (posUser->m_view && posUser->m_view->IsWindowVisible()) {
                posUser->m_view->ShowWindow(SW_HIDE);
            }
        }

        if (!m_controlWnd) {
            ReCreateControl(m_main_view_container.m_hWnd);
        }

        if (m_controlWnd) {
            m_controlWnd->MoveWindow((rc.right - CONTROL_WND_WIDTH) / 2, rc.bottom - 18 - CONTROL_WND_HEIGHT, CONTROL_WND_WIDTH, CONTROL_WND_HEIGHT);
            m_controlWnd->SetMobile(false);
            if (!m_controlWnd->IsWindowVisible()) {
                m_controlWnd->ShowWindow(SW_SHOW);
            }
        }
    }

    void ViewLayoutLogin() {
        m_userWnd.ShowWindow(SW_HIDE);
        m_topbarWnd.ShowVersionInfo();
        m_topbarWnd.MoveWindow(0, 0, m_width, TOPBAR_WND_HEIGHT);
        m_leaveWnd.ShowWindow(SW_HIDE);
        m_snapshotWnd.ShowWindow(SW_HIDE);
        m_userWnd.ShowWindow(SW_HIDE);

        AVInfoShow(false);
        m_show_av_info = false;

        RECT rc;
        m_main_view_container.MoveWindowEx(0, TOPBAR_WND_HEIGHT, m_width, m_height - TOPBAR_WND_HEIGHT);
        m_main_view_container.GetClientRect(&rc);
        m_login_local_view.MoveWindow(0, 0, rc.right, rc.bottom);
        m_login_local_view.ShowWindow(SW_SHOW);
        m_login_local_view.BringWindowToTop();
        m_login_local_view.SetupLocal(true);

        m_loginWnd.MoveWindow(rc.left + (m_width - LOGIN_WND_WIDTH) / 2, rc.bottom - LOGIN_WND_HEIGHT - 80,
            LOGIN_WND_WIDTH, LOGIN_WND_HEIGHT);

        m_login_warning.MoveWindow((m_width - WARNING_WND_WIDTH) / 2, (m_height - WARNING_WND_HEIGHT) / 2,
            WARNING_WND_WIDTH, WARNING_WND_HEIGHT, FALSE);

        m_main_view_container.Highlight(false);
        DestroyControl();
    }

    void ResortUsersList() {
        // save old view layout
        std::vector<std::string> old_view_laytou;
        std::string old_screen_uid;
        GetRecordUsersInfo(old_view_laytou, old_screen_uid);

        auto pos = std::find_if(m_users.begin(), m_users.end(), [](const UserAttr& user) {
            return !user.m_isHost && user.m_type == UserType::REMOTE_USER;
        });

        auto max_audio_pos = pos;
        for (; pos != m_users.end(); ++pos) {
            if (pos->m_audioLevel > max_audio_pos->m_audioLevel + 5) {
                max_audio_pos = pos;
            }
        }

        UserAttr max_audio_user;
        if (max_audio_pos != m_users.end()) {
            max_audio_user = *max_audio_pos;
            m_users.erase(max_audio_pos);
        }

        m_users.sort([](const UserAttr& left, const UserAttr& right)->bool {
            if (left.m_isHost != right.m_isHost) {
                return left.m_isHost;
            }

            if (left.m_type == UserType::LOCAL_USER || right.m_type == UserType::LOCAL_USER) {
                return left.m_type == UserType::LOCAL_USER;
            }

            if (left.m_bAudio && right.m_bAudio) { // both have audio
                if (left.m_bVideo != right.m_bVideo) {
                    return left.m_bVideo;
                }
                else {
                    return left.m_user_uniform_id < right.m_user_uniform_id;
                }
            }else if (left.m_bAudio || right.m_bAudio) { // one has audio
                return left.m_bAudio;
            } else { // Neither has audio
                if (left.m_bVideo != right.m_bVideo) {
                    return left.m_bVideo;
                }
                else {
                    return left.m_user_uniform_id < right.m_user_uniform_id;
                }
            }
        });

        if (!max_audio_user.m_user_id.empty()) {
            pos = std::find_if(m_users.begin(), m_users.end(), [](const UserAttr& user) {
                return !user.m_isHost && user.m_type == UserType::REMOTE_USER;
            });
            m_users.insert(pos, max_audio_user);
        }

        m_userWnd.UpdateAllUsers(m_users);

        std::vector<std::string> view_laytou;
        std::string screen_uid;
        GetRecordUsersInfo(view_laytou, screen_uid);
        if (old_view_laytou != view_laytou || old_screen_uid != screen_uid) {
            UpdateRecordVideoLayout([this](int code) {
                if (code != 200) {
                    BDString inf;
                    inf.Format(L"更新录制布局失败，错误码: %d", code);
                    ShowBubbleTip(inf);
                }
            });
        }
    }

    void UserLayoutFresh() {
        ResortUsersList();
        // Refresh layout
        SetViewLayout(m_view_style);

        // Highest volume highlight
        const int max_search = 4;
        auto pos = m_users.begin();
        auto pos_max = pos;
        for (int i = 0; i < max_search && pos != m_users.end(); ++i, ++pos) {
            if (pos->m_audioLevel > pos_max->m_audioLevel) {
                pos_max = pos;
            }
        }

        if (pos_max->m_view) {
            pos_max->m_view->Highlight(pos_max->m_audioLevel > 5);
        }

        if (pos_max->m_bVideo && pos_max->m_view) {
            bool showBackground = pos_max->m_bVideo && pos_max->m_audioLevel > 5;
            RECT rect;

            pos_max->m_view->GetWindowRect(&rect);
            int w = rect.right - rect.left;
            int h = rect.bottom - rect.top;

            RECT rect_parent;
            m_main_view_container.GetWindowRect(&rect_parent);
            int left = rect.left - rect_parent.left;
            int top = rect.top - rect_parent.top;

            rect.left = left - 2;
            rect.top = top - 2;
            rect.right = w + 3;
            rect.bottom = h + 3;
            m_main_view_container.HighlightRectangle(rect, showBackground);
        }
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDPaintDC dc(m_hWnd);
        return 0;
    }

    virtual void OnFinalMessage(HWND /*hWnd*/) {
        PostQuitMessage(0);
    }

    void OnTimer(UINT_PTR time_id) {
        if (time_id == 2) {
            KillTimer(2);
            ShowBubbleTip("网络链接已断开，请检查设置");

            if (!m_room_id.empty()) {
                EngineWrapper::GetInstance()->logout();
                ::SendMessage(this->m_hWnd, WM_NOTIFY_LEAVE_SUCCEED, USER_OFFLINE_NORMAL, 0);
            }
        }
    }

    LRESULT OnInvalidToken(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        ShowBubbleTip("服务端Token生成失败，请重试");
        EngineWrapper::GetInstance()->logout();
        m_loginWnd.ResetLogin();
        return 0;
    }

    BDUserVideoViewWnd* AllocVideoView(const UserAttr& user, bool isScreenTag) {
        BDHMenu m;

        BDUserVideoViewWnd *view = AllocFromPrueQueue(user, isScreenTag);
        if (!view) {
            view = new BDUserVideoViewWnd(false);
            BDRect r1(0, TOPBAR_WND_HEIGHT, VIDEO_VIEW_WND_WIDTH, VIDEO_VIEW_WND_HEIGHT);
            view->Create(m_main_view_container.m_hWnd, &r1, m, 0, WS_CHILD | WS_CLIPCHILDREN);
            view->SetBackBrushColor(RGB(0x27, 0x2E, 0x3B));
            view->ShowWindow(SW_HIDE);
        }

        view->SetUserId(user.m_user_id);
        view->SetName(user.m_name);
        view->MuteVideo(!user.m_bVideo);
        view->SetHost(user.m_isHost);
        view->SetShare(user.m_shared);
        view->SetUserType(user.m_type);

        if (isScreenTag) {
            view->SetScreenViewTag();
        }

        return view;
    }

    BDUserVideoViewWnd* AllocFromPrueQueue(const UserAttr& user, bool isScreenTag) {
        BDUserVideoViewWnd *view = nullptr;

        auto pos = std::find_if(m_prue_views.begin(), m_prue_views.end(), [&user, &isScreenTag](const BDUserVideoViewWnd* view)-> bool {
            return view && view->GetUserId() == user.m_user_id && view->GetScreenViewTag() == isScreenTag;
        });

        if (pos != m_prue_views.end()) {
            view = *pos;
            m_prue_views.erase(pos);
        }

        if (view) {
            view->Reset();
        }

        return view;
    }

    void FreeVideoView(BDUserVideoViewWnd* view) {
        if (view) {
            view->ShowWindow(SW_HIDE);
            m_prue_views.push_back(view);
            //view->DestroyWindow();
            //delete view;
            //view = nullptr;
        }
    }

    LRESULT ModifyUserNicknameError(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        int code = (int)wParam;
        BDString inf;
        if (code == 430) {
            inf.Format(L"输入内容包含敏感词，请重新输入");
        }
        else if (code == 500) {
            inf.Format(L"系统繁忙，请稍后重试");
        }
        else {
            inf.Format(L"修改昵称失败, 请换个昵称重试");
        }

        ShowBubbleTip(inf);
        return 0;
    }

    LRESULT OnLoginClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto roomID = m_loginWnd.GetRoomId();
        auto nickname = m_loginWnd.GetUserNickname();
        auto room_id = rtcutil::ConvertBDStringToUTF8(roomID);

        // Reclaim last login data
        for (const auto& user : m_users) {
            FreeVideoView(user.m_view);
            FreeVideoView(user.m_screen_view);
        }
        m_users.clear();

        //Join myself
        UserAttr usLocal;
        usLocal.m_user_id = m_sms.user_id;
        usLocal.m_name = nickname;
        usLocal.m_bAudio = !EngineWrapper::GetInstance()->m_bMuteAudio;
        usLocal.m_bVideo = !EngineWrapper::GetInstance()->m_bMuteVideo;
        usLocal.m_isHost = true;
        usLocal.m_type = UserType::LOCAL_USER;
        usLocal.m_view = AllocVideoView(usLocal, false);

        m_users.push_back(usLocal);
        UserLayoutFresh();

        m_userWnd.SetAudioMuteHanlder(std::bind(&BDMainContainerFrame::HostMuteRemoteUserAudio, this, std::placeholders::_1));
        m_userWnd.SetHostTranferHanlder(std::bind(&BDMainContainerFrame::HostTransferHost, this, std::placeholders::_1));
        m_userWnd.SetMuteAllRemoteUsers(std::bind(&BDMainContainerFrame::MuteAllRemoteUsers, this));

        m_topbarWnd.OnListShowClick(std::bind(&BDMainContainerFrame::OnListShowClick, this));

        m_rateWnd.ShowWindow(SW_HIDE);
        m_feedbackWnd.ShowWindow(SW_HIDE);
        m_settingWnd.ShowWindow(SW_HIDE);

        JoinMeeting(room_id, rtcutil::ConvertBDStringToUTF8(nickname), m_sms.user_id);
        return 0;
    }

    void OnListShowClick() {
        m_speakerListShow = !m_speakerListShow;
        ::SendMessage(m_hWnd, WM_NOTIFY_VIEEW_RELAYOUT, true, SPEAKER_STYLE);
    }

    LRESULT OnJoinOK(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        m_login_local_view.SetupLocal(true);
        m_login_local_view.ShowWindow(SW_HIDE);
        m_loginWnd.ShowWindow(SW_HIDE);
        m_login_warning.ShowWindow(SW_HIDE);
   
        auto roomID = m_loginWnd.GetRoomId();
        auto nickname = m_loginWnd.GetUserNickname();
        m_room_id = rtcutil::ConvertBDStringToUTF8(roomID);

        m_topbarWnd.ShowRoomInfo(roomID, nickname);
        m_feedbackWnd.Reset();

        if (m_settingWnd.IsAVInfoShow()) {
            m_show_av_info = true;
            AVInfoShow(true);
        }

        auto token = (const char*)wParam;
        EngineWrapper::GetInstance()->login(m_room_id.c_str(), m_sms.user_id.c_str(), token);
        EngineWrapper::GetInstance()->EnableAudioVolumeIndication(1000, 8);

        m_view_style = GALLERY_ONER_STYLE;
        SetViewLayout(m_view_style);

        return 0;
    }

    LRESULT OnLocalVideoPreview(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BOOL preview = (BOOL)wParam;
        if (preview) {
            m_login_local_view.SetupLocal(true);
            EngineWrapper::GetInstance()->preview();
            m_login_local_view.MuteVideo(false);
        }
        else {
            m_login_local_view.SetupLocal(false);
            EngineWrapper::GetInstance()->stopPreview();
            Sleep(100);
            m_login_local_view.MuteVideo(true);
            m_login_local_view.Invalidate();
        }

        return 0;
    }

    LRESULT OnStreamsAdd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto streams = (RemoteStream*)wParam;
        int size = (int)lParam;

        for (int i = 0; i < size; ++i) {
            auto& stream = streams[i];
            auto pos = std::find_if(m_users.begin(), m_users.end(), [&stream](const UserAttr& user) {
                return stream.user_id == user.m_user_id;
            });

            if (stream.is_screen) {
                if (stream.user_id != m_sms.user_id) {
                    m_remoteStream = stream;
                    if (pos != m_users.end() && pos->m_screen_view) {
                        pos->m_screen_view->OnStreamAdd();
                    }
                }
            }
            else {
                m_remoteStreams[stream.user_id] = stream;
                if (pos != m_users.end() && pos->m_view) {
                    pos->m_view->OnStreamAdd();
                }
            }
        }

        return 0;
    }

    LRESULT OnStreamsRemove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto streams = (RemoteStream*)wParam;
        int size = (int)lParam;

        for (int i = 0; i < size; ++i) {
            auto& stream = streams[i];
            auto pos = std::find_if(m_users.begin(), m_users.end(), [&stream](const UserAttr& user) {
                return stream.user_id == user.m_user_id;
            });

            if (stream.is_screen) {
                if (stream.user_id == m_remoteStream.user_id) {
                    m_remoteStream.user_id.clear();
                }

                if (pos != m_users.end() && pos->m_screen_view) {
                    pos->m_screen_view->OnStreamRemove();
                }
            }
            else {
                auto pos_stream = m_remoteStreams.find(stream.user_id);
                if (pos_stream != m_remoteStreams.end()) {
                    m_remoteStreams.erase(pos_stream);
                }

                if (pos != m_users.end() && pos->m_view) {
                    pos->m_view->OnStreamRemove();
                }
            }
        }

        return 0;
    }

    LRESULT OnViewAttach(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        for (auto& user : m_users) {
            if (!user.m_view) {
                user.m_view = AllocVideoView(user, false);

                auto pos = m_remoteStreams.find(user.m_user_id);
                if (pos != m_remoteStreams.end()) {
                    user.m_view->OnStreamAdd();
                }
            }

            if (user.m_shared) {
                if (!user.m_screen_view) {
                    user.m_screen_view = AllocVideoView(user, true);

                    if (m_remoteStream.user_id == user.m_user_id) {
                        user.m_screen_view->OnStreamAdd();
                    }
                }
            }
        }

        ResortUsersList();
        // Update layout
        ::SendMessage(m_hWnd, WM_NOTIFY_VIEEW_RELAYOUT, wParam, lParam);
        return 0;
    }

    LRESULT OnFirstRemoteScreenVideo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        //std::string uid((char const*)wParam);
        //if (uid != m_user_id) {
        //    auto pos = std::find_if(m_users.begin(), m_users.end(), [&uid](const UserAttr& attr)->bool {
        //          return attr.m_user_id == uid;
        //    });

        //    if (pos != m_users.end() && pos->m_screen_view) {
        //        pos->m_screen_view->OnFirstVideoFrame();
        //    }
        //}
        return 0;
    }

    LRESULT OnFirstRemoteVideo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        //std::string user((const char*)wParam);
        //auto pos = std::find_if(m_users.begin(), m_users.end(), [&](const UserAttr& attr)->bool {
        //    return attr.m_user_id == user;
        //});

        //if (pos != m_users.end() && pos->m_view) {
        //    pos->m_view->OnFirstVideoFrame();
        //}
        return 0;
    }

    LRESULT OnRemoteViewRelayout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        bool forceRelayout = (bool)wParam; //Force layout update
        ViewLayoutStyle Style = (ViewLayoutStyle)lParam;

        if (Style == VIEW_UNKNOW_STYLE) {
            switch (m_users.size())
            {
            case 1: // I'm the only one left in the room
                if (forceRelayout || m_view_style != GALLERY_ONER_STYLE) {
                    SetViewLayout(GALLERY_ONER_STYLE);
                }
                break;
            case 2: // 2-cell layout when there is only one user at the far end
                if (forceRelayout || m_view_style != GALLERY_TWO_STYLE) {
                    SetViewLayout(GALLERY_TWO_STYLE);
                }
                break;
            case 3: // 4-grid layout with 2-3 users at the far end
            case 4:
                if (forceRelayout || m_view_style != GALLERY_FOUR_STYLE) {
                    SetViewLayout(GALLERY_FOUR_STYLE);
                }
                break;
            case 5:
            case 6:
                if (forceRelayout || m_view_style != GALLERY_SIX_STYLE) {
                    SetViewLayout(GALLERY_SIX_STYLE);
                }
                break;
            default: // 9-grid layout when there are more than 3 remote users
                if (forceRelayout || m_view_style != GALLERY_NINE_STYLE) {
                    SetViewLayout(GALLERY_NINE_STYLE);
                }
                break;
            }
        }
        else if (forceRelayout || m_view_style != Style) {
            SetViewLayout(Style);
        }

        return 0;
    }

    LRESULT OnAudioVolumeIndication(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (m_view_style == VIEW_UNKNOW_STYLE
            || m_view_style == LOCAL_SHARE_STYLE || m_room_id.empty()) {
            return 0;
        }
        // Clearing
        for (auto& user : m_users) {
            user.m_audioLevel = 0;
            user.m_view->Highlight(false);
        }

        AudioVolumeInfo* AudioVolumeInfos = (AudioVolumeInfo*)wParam;
        int size = (int)lParam;

        for (int i = 0; i < size; ++i) {
            auto& audioVolumeInfo = AudioVolumeInfos[i];
            auto iter = std::find_if(m_users.begin(), m_users.end(), [&](const UserAttr& userAttr)->bool {
                return audioVolumeInfo.uid == userAttr.m_user_id; // This search algorithm may be the bottleneck
            });
        
            if (iter != m_users.end()) {
                iter->m_audioLevel = audioVolumeInfo.volume > 5 ? audioVolumeInfo.volume : 0;
            }
        }

        UserLayoutFresh(); // view attach
        return 0;
    }

    LRESULT OnShowUser(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (m_view_style == LOCAL_SHARE_STYLE) {
            BDString inf;
            inf.Format(L"停止屏幕共享后可查看参会者列表");
            ShowBubbleTip(inf);
            return 0;
        }

        if (m_userWnd.IsWindowVisible()) {
            m_userWnd.ShowWindow(SW_HIDE);
            if(m_controlWnd)
                m_controlWnd->ResetUserListState(false);

            for (auto& user : m_users) {
                if (!user.m_view) continue;
                if (user.m_view->IsWindowVisible()) {
                    if (!user.m_bVideo) {
                        user.m_view->Invalidate();
                    }
                }
                else {
                    break;
                }
            }

        } else {
            m_userWnd.MoveWindowEx(m_width - USER_WND_WIDTH, 0, USER_WND_WIDTH, m_height);
            m_userWnd.ShowWindow(SW_SHOW);
            if(m_controlWnd) m_controlWnd->ResetUserListState(true);
        }

        OnSize(0, BDSize(m_width, m_height));
        return 0;
    }

    LRESULT OnShowSetting(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (m_view_style == LOCAL_SHARE_STYLE) {
            BDString inf;
            inf.Format(L"停止屏幕共享后可进入会议设置页");
            ShowBubbleTip(inf);
            return 0 ;
        }

        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);
        m_settingWnd.MoveWindow((rc.right + rc.left) / 2 - SETTING_WND_WIDTH / 2,
            (rc.top + rc.bottom) / 2 - SETTING_WND_HEIGHT / 2,
            SETTING_WND_WIDTH,
            SETTING_WND_HEIGHT);
        m_settingWnd.ShowWindow(SW_SHOW);

        m_main_mask.MoveWindow(rc.left + 10,
            rc.top,
            rc.right - rc.left - 20,
            rc.bottom - rc.top - 10);
        m_main_mask.ShowWindow(SW_SHOW);

        if(m_controlWnd)
            m_controlWnd->ResetSettingState(true);

        return 0;
    }

    LRESULT OnCloseUser(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        OnSize(0, BDSize(m_width, m_height));
        if (m_controlWnd)
            m_controlWnd->ResetUserListState(false);

        for (auto& user : m_users) {
            if (!user.m_view) continue;
            if (user.m_view->IsWindowVisible()) {
                if (!user.m_bVideo) {
                    user.m_view->Invalidate();
                }
            }
            else {
                break;
            }
        }
        return 0;
    }

    LRESULT OnCloseSetting(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        m_main_mask.ShowWindow(SW_HIDE);
        if (m_controlWnd) m_controlWnd->ResetSettingState(false);
        BringWindowToTop();
        return 0;
    }

    LRESULT OnAVInfoSetting(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (!m_room_id.empty()) {
            m_show_av_info = (BOOL)wParam;
            AVInfoShow(m_show_av_info);
            m_avInfoWnd.Invalidate();
        }
        return 0;
    }

    LRESULT OnMuteChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto pos = std::find_if(m_users.begin(), m_users.end(), [](const UserAttr& ua)->bool {
            return ua.m_type == UserType::LOCAL_USER;
        });

        assert(pos != m_users.end());

        pos->m_bAudio = !EngineWrapper::GetInstance()->m_bMuteAudio;
        pos->m_bVideo = !EngineWrapper::GetInstance()->m_bMuteVideo;
        
        int tag = (int)wParam;
        switch (tag) {
        case VIDEOTAG: {
            MeetingManager::GetInstance()->toggleCameraState(pos->m_bVideo, [](int code) {
                int res = code;
            });

            if (pos->m_view) {
                pos->m_view->MuteVideo(EngineWrapper::GetInstance()->m_bMuteVideo);
                Sleep(100);
                pos->m_view->Invalidate();
            }
            break;
        }
        case AUDIOTAG: {
            MeetingManager::GetInstance()->toggleMicState(pos->m_bAudio, [](int code) {
                int res = code;
            });

            if (!pos->m_bAudio && pos->m_view) {
                pos->m_view->Highlight(false);
            }
            break;
        }
        default:
            break;
        }

        if (m_view_style == GALLERY_ONER_STYLE) {
            if (!pos->m_bAudio || !pos->m_bVideo) {
                m_main_view_container.Highlight(false);
            }
        }

        Invalidate();
        return 0;
    }

    LRESULT OnLogReport(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        return 0;
    }

    LRESULT OnRtcStats(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto stats = (const bytertc::RtcStats*)wParam;
        m_avInfoWnd.OnRtcStats(*stats);
        return 0;
    }

    LRESULT OnLocalVideoStats(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto stats = (const bytertc::LocalVideoStats*)wParam;
        m_avInfoWnd.OnLocalVideoStats(*stats);
        return 0;
    }

    LRESULT OnLocalAudioStats(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto stats = (const bytertc::LocalAudioStats*)wParam;
        m_avInfoWnd.OnLocalAudioStats(*stats);
        return 0;
    }

    LRESULT OnRemoteVideoStats(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto stats = (const bytertc::RemoteVideoStats*)wParam;
        m_avInfoWnd.OnRemoteVideoStats(*stats);
        return 0;
    }

    LRESULT OnRemoteAudioStats(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto stats = (const bytertc::RemoteAudioStats*)wParam;
        m_avInfoWnd.OnRemoteAudioStats(*stats);
        return 0;
    }

    LRESULT OnRate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        m_rateWnd.ShowWindow(SW_HIDE);
        m_rate = (int)wParam;
        if (m_rate == 1) {
            RECT rc;
            ::GetWindowRect(m_hWnd, &rc);
            m_feedbackWnd.MoveWindow(rc.left + (rc.right - rc.left - FEEDBACK_WND_WIDTH) / 2, rc.bottom - FEEDBACK_WND_HEIGHT - 247,
                FEEDBACK_WND_WIDTH, FEEDBACK_WND_HEIGHT);
            m_feedbackWnd.ShowWindow(SW_SHOW);
        }
        else {
            m_main_mask.ShowWindow(SW_HIDE);
            BringWindowToTop();
        }

        return 0;
    }

    LRESULT OnFeedback(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        if (lParam) {
            Json::Value feed;
            feed["grade"] = m_rate;
            feed["type"] = (int)lParam;
            feed["problem_desc"] = (const char*)wParam;
            feed["os_version"] = rtcutil::GetOsInfo();
            feed["network_type"] = "UNKNON";

            Json::StreamWriterBuilder builder;
            const std::string json_value = Json::writeString(builder, feed);
            EngineWrapper::GetInstance()->feedback(json_value.c_str());
        }

        m_main_mask.ShowWindow(SW_HIDE);
        m_feedbackWnd.ShowWindow(SW_HIDE);
        BringWindowToTop();
        return 0;
    }

    LRESULT OnFirstLocalAudio(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        return 0;
    }

    LRESULT OnFirstLocalVideo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        //m_login_local_view.OnFirstVideoFrame();
        return 0;
    }

    LRESULT OnLoginWarning(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        BDMeetingLoginWnd::EditStatus state = (BDMeetingLoginWnd::EditStatus)wParam;
        switch (state)
        {
        case BDMeetingLoginWnd::ES_MAXTEXT: {
            BDString inf;
            inf.Format(L"输入长度超过18位字符");
            ShowBubbleTip(inf);
            break;
        }
        case BDMeetingLoginWnd::ES_INVALID: {
            BOOL show = (BOOL)lParam;
            m_login_warning.ShowWindow(show ? SW_SHOW : SW_HIDE);
            break;
        }
        default:
            break;
        }

        return 0;
    }

    LRESULT OnLeaveClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);
        auto host = m_users.begin();
        bool is_host = host->m_isHost && host->m_type == UserType::LOCAL_USER;
        m_leaveWnd.SetHost(is_host);
        if (is_host) {
            m_leaveWnd.MoveWindow(rc.left +  (m_width - HOST_LEAVE_WND_WIDTH) / 2, rc.top + (m_height - HOST_LEAVE_WND_HEIGHT) / 2,
                HOST_LEAVE_WND_WIDTH, HOST_LEAVE_WND_HEIGHT, FALSE);
        }
        else {
            m_leaveWnd.MoveWindow(rc.left +  (m_width - CLIENT_LEAVE_WND_WIDTH) / 2, rc.top + (m_height - CLIENT_LEAVE_WND_HEIGHT) / 2,
                CLIENT_LEAVE_WND_WIDTH, CLIENT_LEAVE_WND_HEIGHT, FALSE);
        }

        m_messageWnd.ShowWindow(SW_HIDE);
        m_leaveWnd.ShowWindow(SW_SHOW);
        m_settingWnd.ShowWindow(SW_HIDE);
        if (m_controlWnd) m_controlWnd->ResetSettingState(false);

        if (m_snapshotWnd.IsWindowVisible()) {
            onStartShareScreen(0, 0, 0, bHandled);
        }

        if (m_view_style != LOCAL_SHARE_STYLE) {
            m_main_mask.MoveWindow(rc.left + 10,
                rc.top,
                rc.right - rc.left - 20,
                rc.bottom - rc.top - 10);
            m_main_mask.ShowWindow(SW_SHOW);
        }
        return FALSE;
    }

    LRESULT OnLeaveSucceed(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        bool silence = (bool)lParam;
        KillTimer(0);
        KillTimer(2);

        ShowWindow(silence ? SW_HIDE : SW_SHOW);
        for (auto it = m_users.begin(); it != m_users.end(); it++) {
            FreeVideoView(it->m_view);
            FreeVideoView(it->m_screen_view);
        }

        m_users.clear();
        m_userWnd.Clear();
        m_room_id.clear();
        m_remoteStream.user_id.clear();
        m_remoteStreams.clear();

        m_view_style = LOGIN_STYLE;
        ViewLayoutLogin();
        OnSize(0, BDSize(m_width, m_height));

        RECT rc;
        ::GetWindowRect(m_hWnd, &rc);
        m_main_mask.MoveWindow(rc.left + 10,
            rc.top,
            rc.right - rc.left - 20,
            rc.bottom - rc.top - 10);
        m_main_mask.ShowWindow(silence ? SW_HIDE : SW_SHOW);

        m_leaveWnd.ShowWindow(SW_HIDE);
        m_messageWnd.ShowWindow(SW_HIDE);
        m_settingWnd.ShowWindow(SW_HIDE);

        m_rateWnd.ShowWindow(silence ? SW_HIDE : SW_SHOW);
        m_loginWnd.Reset();
        m_loginWnd.ShowWindow(silence ? SW_HIDE : SW_SHOW);

        if (m_snapshotWnd.IsWindowVisible()) {
            onStartShareScreen(0, 0, 0, bHandled);
        }
        if (m_controlWnd) m_controlWnd->ResetSettingState(false);
        m_rateWnd.MoveWindow(rc.left + (rc.right - rc.left - RATE_WND_WIDTH) / 2, rc.top + (rc.bottom - rc.top - RATE_WND_HEIGHT) / 2,
            RATE_WND_WIDTH, RATE_WND_HEIGHT);

        UserOfflineType type = (UserOfflineType)wParam;
        if (type == USER_OFFLINE_REPEAT_LOGIN) {
            ShowBubbleTip("相同ID用户已登录，您已被强制下线");
        }

        Invalidate();
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        return 0;
    }

    void ShowBubbleTip(const BDString& message, bool auto_disappear = true) {
        if (!m_bubbleTipWnd.IsWindowVisible()) {
            RECT rc;
            ::GetWindowRect(m_hWnd, &rc);
            m_bubbleTipWnd.SetTipMessage(message);

            BDPaintDC dc(m_bubbleTipWnd.m_hWnd);
            SIZE text_size;
            dc.GetTextExtent(message, message.GetLength(), &text_size);
            const int width = text_size.cx + 90;

            if (m_view_style == LOCAL_SHARE_STYLE) {
                RECT display;
                std::vector<RECT> displayList;
                rtcutil::GetDisplayList(displayList);
                for (auto& screen : displayList) {
                    if (screen.left < rc.left && screen.right > rc.left
                        && screen.top < rc.top && screen.bottom > rc.top) {
                        display = screen;
                    }
                }

                m_bubbleTipWnd.MoveWindow(display.left + (display.right - display.left - width) / 2, display.top + 100,
                    width, KICKOFF_WND_HEIGHT);
            }
            else {
                m_bubbleTipWnd.MoveWindow(rc.left + (m_width - width) / 2, rc.top + 100,
                    width, KICKOFF_WND_HEIGHT);
            }

            HRGN bubbleRgn = ::CreateRoundRectRgn(0, 0, width, KICKOFF_WND_HEIGHT, 10, 10);
            m_bubbleTipWnd.SetWindowRgn(bubbleRgn);
            m_bubbleTipWnd.AutoDisappear(auto_disappear);
            m_bubbleTipWnd.ShowWindow(SW_SHOW);
            m_bubbleTipWnd.BringWindowToTop();
        }
    }

    LRESULT OnVideoStateChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        std::string did((const char*)wParam);
        auto event = (bytertc::MediaDeviceNotification)lParam;
        int count = m_settingWnd.OnVideoDeviceStateChange(did, event);

        if (count == 0 && !EngineWrapper::GetInstance()->m_bMuteVideo) {
            EngineWrapper::GetInstance()->m_bMuteVideo = true;
            EngineWrapper::GetInstance()->muteLocalVideo(true);
            if (!m_room_id.empty() && m_controlWnd) {
                m_controlWnd->UpdateVideo();
            }
            m_loginWnd.OnVideoDeviceDisconection();
        }
        else if (!EngineWrapper::GetInstance()->m_bMuteVideo) {
            EngineWrapper::GetInstance()->muteLocalVideo(EngineWrapper::GetInstance()->m_bMuteVideo);
        }

        BDString inf;
        switch (event) {
        case bytertc::kMediaDeviceNotificationActive: // Insert a new device
            inf.Format(L"有新录像设备插入");
            ShowBubbleTip(inf);
            break;
        case bytertc::kMediaDeviceNotificationUnplugged: // Pull out the device
            inf.Format(L"录像设备被拔出");
            ShowBubbleTip(inf);
            break;
        default:
            break;
        }

        return 0;
    }

    LRESULT OnAudioStateChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        std::string did((const char*)wParam);
        auto event = (bytertc::MediaDeviceNotification)lParam;
        int count = m_settingWnd.OnAudioDeviceStateChange(did, event);

        if (count == 0 && !EngineWrapper::GetInstance()->m_bMuteAudio) {
            EngineWrapper::GetInstance()->m_bMuteAudio = true;
            EngineWrapper::GetInstance()->muteLocalAudio(true);
            if (!m_room_id.empty() && m_controlWnd) {
                m_controlWnd->UpdateAudio();
            }
            m_loginWnd.OnAudioDeviceDisconection();
        }
        else if(!EngineWrapper::GetInstance()->m_bMuteAudio){
            EngineWrapper::GetInstance()->muteLocalAudio(EngineWrapper::GetInstance()->m_bMuteAudio);
        }

        BDString inf;
        switch (event) {
        case bytertc::kMediaDeviceNotificationActive: // Insert a new device
            inf.Format(L"有新麦克风设备插入");
            ShowBubbleTip(inf);
            break;
        case bytertc::kMediaDeviceNotificationNotPresent: // Pull out the device
            inf.Format(L"麦克风设备被拔出");
            ShowBubbleTip(inf);
            break;
        default:
            break;
        }

        return 0;
    }

    LRESULT OnInvalidDevice(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        int tag = (int)wParam;
        if (tag == AUDIOTAG) {
            BDString inf;
            inf.Format(L"麦克风打开失败，请检查设备");
            ShowBubbleTip(inf);
        }
        else if (tag == VIDEOTAG) {
            BDString inf;
            inf.Format(L"摄像头打开失败，请检查设备");
            ShowBubbleTip(inf);
        }
        return 0;
    }

    LRESULT OnLocalVideoStateChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        auto state = (bytertc::LocalVideoStreamState)wParam;
        auto error = (bytertc::LocalVideoStreamError)lParam;

        if (state == bytertc::kLocalVideoStreamStateFailed
            && (error == bytertc::kLocalVideoStreamErrorDeviceNoPermission  // SDK Forbidden authority before entering the room，Call back the event after entering the room, localVideoState=3, error=2
                || error == bytertc::kLocalVideoStreamErrorCaptureFailure
                || error == bytertc::kLocalVideoStreamErrorDeviceBusy)) {    // Equipment is occupied, when state = 3, error=4

            if (!EngineWrapper::GetInstance()->m_bMuteVideo) {
                EngineWrapper::GetInstance()->m_bMuteVideo = true;
                EngineWrapper::GetInstance()->muteLocalVideo(true);

                BDString inf;
                inf.Format(L"摄像头打开失败，请检查设备");
                ShowBubbleTip(inf);
            }

            if (!m_room_id.empty() && m_controlWnd) {
                m_controlWnd->UpdateVideo();
            }
            m_loginWnd.OnVideoDeviceDisconection();
        }

        return 0;
    }

    LRESULT OnLocalAudioStateChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        // Forbidden authority before entering the room, call startpriview Call startpriview has no callback
        // sdk Forbidden authority before entering the room, Call back the event after entering the room,localAudioState=3, error=2
        // sdk have permission before you enter the house，Forbidden authority after entering the room, localAudioState=3, error=4
        auto state = (bytertc::LocalAudioStreamState)wParam;
        auto error = (bytertc::LocalAudioStreamError)lParam;
        if (state == bytertc::kLocalAudioStreamStateFailed
            &&(error == bytertc::kLocalAudioStreamErrorDeviceNoPermission
                || bytertc::kLocalAudioStreamErrorRecordFailure)) {
            BDString inf;
            inf.Format(L"麦克风打开失败，请检查设备");
            ShowBubbleTip(inf);

            if (!EngineWrapper::GetInstance()->m_bMuteAudio) {
                EngineWrapper::GetInstance()->m_bMuteAudio = true;
                EngineWrapper::GetInstance()->muteLocalAudio(true);
            }

            if (!m_room_id.empty() && m_controlWnd) {
                m_controlWnd->UpdateAudio();
            }
            m_loginWnd.OnAudioDeviceDisconection();
        }

        return 0;
    }

    void RealFreeVideoView(BDUserVideoViewWnd* view) {
        if (view) {
            view->DestroyWindow();
            delete view;
            view = nullptr;
        }
    }

    LRESULT OnSDKLeaveChannelSucceed(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        for (auto& view : m_prue_views) {
            RealFreeVideoView(view);
        }
        m_prue_views.clear();

        for (auto it = m_users.begin(); it != m_users.end(); it++) {
            RealFreeVideoView(it->m_view);
            it->m_view = nullptr;

            RealFreeVideoView(it->m_screen_view);
            it->m_screen_view = nullptr;
        }

        return 0;
    }

    LRESULT OnSDKUserOfflineSucceed(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        std::string uid((const char*)wParam);

        for (auto pos = m_prue_views.begin(); pos != m_prue_views.end(); ) {
            if ((*pos) && (*pos)->GetUserId() == uid) {
                RealFreeVideoView(*pos);
                pos = m_prue_views.erase(pos);
            }
            else if (!(*pos)) {
                pos = m_prue_views.erase(pos);
            }
            else {
                ++pos;
            }
        }

        for (auto it = m_users.begin(); it != m_users.end(); it++) {
            if (it->m_user_id == uid) {
                RealFreeVideoView(it->m_view);
                it->m_view = nullptr;

                RealFreeVideoView(it->m_screen_view);
                it->m_screen_view = nullptr;

                break;
            }
        }

        return 0;
    }

    void AVInfoShow(bool show) {
        if (show) {
            RECT rc;
            ::GetWindowRect(m_hWnd, &rc);
            m_avInfoWnd.MoveWindowEx(rc.left + 12, rc.bottom - AVINFO_WND_HEIGHT - 12,
                AVINFO_WND_WIDTH, AVINFO_WND_HEIGHT);
        }

        if (m_avInfoWnd.IsWindowVisible() != show) {
            m_avInfoWnd.ShowWindow(show ? SW_SHOW : SW_HIDE);
        }
    }

protected:
    LRESULT OnFunctionExec(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
    void JoinMeeting(const std::string& room_id, const std::string& user_name, const std::string& user_id);
    LRESULT OnMeetingEnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMeetingLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMeetingCancel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT onRecordVideo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT onStartShareScreen(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT onCloseShareScreen(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    void StartScreenShare(const SnapshotAttr& shared, const SnapshotAttr& excluded);
    void StopScreenShare();

    void MuteAllRemoteUsers();
    void UpdateRecordVideoLayout(std::function<void(int)> callback);
    bool GetRecordUsersInfo(std::vector<std::string>& users, std::string& screen_uid);

    void HostMuteRemoteUserAudio(const UserAttr& user);
    void HostTransferHost(const UserAttr& user);

    void OnClose();
    void Logout(bool silence);
    void RejoinMeeting();

    void ReCreateControl(HWND parent, bool popup = false) {
        assert(!m_controlWnd);

        BDHMenu m;
        BDRect rControl(0, TOPBAR_WND_HEIGHT, CONTROL_WND_WIDTH, TOPBAR_WND_HEIGHT + CONTROL_WND_HEIGHT);
        m_controlWnd = new BDControlWnd();
        m_controlWnd->Create(parent, &rControl, m, 0, popup ? WS_POPUP : WS_CHILD | WS_CLIPCHILDREN);
        HRGN hControlRgn = ::CreateRoundRectRgn(0, 0, CONTROL_WND_WIDTH, CONTROL_WND_HEIGHT, CONTROL_WND_HEIGHT, CONTROL_WND_HEIGHT);
        m_controlWnd->SetWindowRgn(hControlRgn);
        m_controlWnd->SetMessageHandler(m_hWnd);

        m_controlWnd->ResetAudioState();
        m_controlWnd->ResetVideoState();
        m_controlWnd->ResetSettingState(m_settingWnd.IsWindowVisible());
        m_controlWnd->ResetRecordingState(m_topbarWnd.IsVideoRecording());
        m_controlWnd->ResetUserListState(m_userWnd.IsWindowVisible());
        m_controlWnd->ResetScreenSharedState(m_view_style == SPEAKER_STYLE || m_view_style == LOCAL_SHARE_STYLE);
    }

    void DestroyControl() {
        if (m_controlWnd) {
            m_controlWnd->DestroyWindow();
            delete m_controlWnd;
            m_controlWnd = nullptr;
        }
    }

    void CheckUpdateApp(bool show);
protected:

    void onUserMicStateChange(const std::string& userId, bool on) override;
    void onUserCameraStateChange(const std::string& userId, bool on) override;
    void onHostChange(const std::string& formerHostId, const std::string& hostId) override;
    void onUserJoinMeeting(const User& userId) override;
    void onUserLeaveMeeting(const std::string& userId) override;
    void onScreenShareStateChanged(const std::string& userId, bool state) override;
    void onStartMeetingRecord() override;
    void onMeetingClose() override;
    void onMuteAllMic() override;
    void onMuteUser(const std::string& userId) override;
    void onAskingMicOn(const std::string& userId) override;
    void onAskingCameraOn(const std::string& userId) override;
    void onUserKickedOff() override;
    void onJoinMeetingsuccessfully(int code, const std::string& token);
    void onInvaildToken(int code) override;

public:
    void onWebsocketConnected() override;
    void onWebsocketConnecting() override;

protected:
    bool OnLocalScreenFrame(bytertc::IByteVideoFrame* videoFrame) override;
    bool OnLocalVideoFrame(bytertc::IByteVideoFrame* videoFrame) override;
    bool OnRemoteScreenFrame(const char* roomid, const char* uid, bytertc::IByteVideoFrame* videoFrame) override;
    bool OnRemoteVideoFrame(const char* roomid, const char* uid, bytertc::IByteVideoFrame* videoFrame) override;

private:
    BDMeetingLoginWnd m_loginWnd;       // login ui window
    BDTopBarWnd m_topbarWnd;     // Toolbar
    BDControlWnd* m_controlWnd = nullptr;   // Control bar
    BDUserWnd   m_userWnd;       // User list window
    BDWarningWnd m_login_warning; // Login error window
    BDSettingWnd m_settingWnd;    // setting window
    BDSnapshotWnd m_snapshotWnd;  // Screen sharing selection window
    BDLeaveWnd m_leaveWnd;        // User leaving room confirmation and prompt window
    BDRateWnd m_rateWnd;          // Conference experience scoring window
    BDFeedbackWnd m_feedbackWnd;  // Feedback window
    BDAVInfoWnd m_avInfoWnd;      // Audio and video statistical information display window
    BDMessageWnd m_messageWnd;    // Confirmation window
    BDBubbleTipWnd m_bubbleTipWnd; // Pop up prompt window

    std::list<UserAttr> m_users; // List of participants

    BDUserVideoViewWnd m_main_view_container; // Layout container
    BDUserVideoViewWnd m_login_local_view;        //Login interface, local video rendering window

    std::vector<BDUserVideoViewWnd*> m_prue_views; // 反复共享没有回收资源

    ViewLayoutStyle m_view_style = LOGIN_STYLE;

    int m_width;    // main window width
    int m_height;   // main window height
    int m_rate = 0; // experience score
    bool m_speakerListShow = true; // Whether to hide remote users in speaker mode
    bool m_websocket_connection = false; // Whether websocket is in the connection state

    std::string m_room_id;  // room id
    VerifySms m_sms;
    //std::string m_user_id;  // local user name

    std::map<std::string, RemoteStream> m_remoteStreams; // Remote video streams information
    RemoteStream m_remoteStream; // Remote screen sharing stream info
    BDMaskWnd m_main_mask; // main mask window
    bool m_show_av_info = false;
};

