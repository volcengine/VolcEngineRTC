//
//  BDVScrollWnd.h
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
#include "BDUserFocusWnd.h"
#include <list>
#include <algorithm>
#include <mutex>

#define CAPTION_HEIGHT 50

class BDUsersVScrollWnd : public BDWndImpl<BDUsersVScrollWnd>
{
public:
    DECLARE_BDWND_CLASS(L"BDVUsersScrollWnd")
    BDUsersVScrollWnd()
    {
        BDWndClassInfo& wci = GetWndClassInfo();
        wci.m_wc.hbrBackground = CreateSolidBrush(RGB(0x10, 0x13, 0x19));
        if (!wci.m_atom)
        {
            wci.m_wc.hIcon = LoadIcon(BDWinApp::GetResInstance(), MAKEINTRESOURCE(IDI_BYTERTCSTART));
        }
    }

    BEGIN_MSG_MAP(BDVScrollWnd)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_SIZE(OnSize)
        MSG_WM_SHOWWINDOW(OnFrameShow)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_MOUSEWHEEL(OnMouseWheel)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_CTLCOLORSTATIC(onStaticColor)
    END_MSG_MAP()

    int OnCreate(LPCREATESTRUCT lpCreateStruct)
    {
        m_blackBrush.CreateSolidBrush(RGB(0x00, 0x00, 0x00));
        m_barBrush.CreateSolidBrush(RGB(0x4E, 0x59, 0x69));
        allBk.CreateSolidBrush(RGB(0x10, 0x13, 0x19));

        m_audio.LoadBitmap(IDB_USER_VOICE_ENABLE);
        m_audio_highlight.LoadBitmap(IDB_AUDIO_ACTIVE);
        m_audioDisable.LoadBitmap(IDB_USER_VOICE_DISABLE);
        m_video.LoadBitmap(IDB_USER_VIDEO_ENABLE);
        m_videoDisable.LoadBitmap(IDB_USER_VIDEO_DISABLE);

        m_host.LoadBitmap(IDB_HOST);
        m_userShare.LoadBitmap(IDB_USER_SHARE);

        m_nameFont = CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");
        m_abbreviationFont = CreateFont(14, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"PingFang SC");

        BDHMenu m;
        BDRect r(0, 0, 216, CAPTION_HEIGHT);
        m_userFocusWnd.Create(m_hWnd, &r, m, 0, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN);
        m_userFocusWnd.ShowWindow(SW_HIDE);
        
        rtcutil::LoadFile(L"resource\\highlight_circular.png", m_highlight_circular);
        rtcutil::LoadFile(L"resource\\head_speaker_shared.png", m_head);
        return 0;
    }

    void OnFrameShow(BOOL show, int lParam) {
        m_vscroll_pos = 0;
        m_vscroll_range = -1;
        m_userFocusWnd.ShowWindow(SW_HIDE);

        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    void OnSize(UINT nType, BDSize size)
    {
        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    LRESULT OnMouseWheel(UINT nFlags, short zDelta, BDPoint point) {
        int times = zDelta / WHEEL_DELTA;
        auto dy = - times * CAPTION_HEIGHT;
        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(dy, rect, false);

        OnMouseMove(0, point);
        return 0;
    }

    void OnMouseLeave() {
        if (!m_userFocusWnd.IsMouseCaptured()) {
            m_userFocusWnd.ShowWindow(SW_HIDE);
        }
    }

    void OnMouseMove(UINT w, BDPoint point) {
        RECT client_rect;
        GetClientRect(&client_rect);

        auto host = std::find_if(m_users.begin(), m_users.end(), [](const UserAttr& user) {
            return user.m_isHost;
        });
        if (host == m_users.end() || host->m_type == UserType::REMOTE_USER) {
            return;
        }

        bool find = false;
        for (auto& item : m_users) {
            if (item.m_delta + CAPTION_HEIGHT < 0 || item.m_type == UserType::LOCAL_USER) {
                continue;
            }
            else if (item.m_delta > client_rect.bottom) {
                break;
            }

            if ((point.y > item.m_delta && point.y < item.m_delta + CAPTION_HEIGHT)) {
                m_userFocusWnd.MoveWindow(0, item.m_delta, client_rect.right, CAPTION_HEIGHT);
                m_userFocusWnd.SetUserInfo(item);

                if (!m_userFocusWnd.IsWindowVisible()) {
                    m_userFocusWnd.ShowWindow(SW_SHOW);
                    find = true;
                }
            }
        }

        if (!find) {
            m_userFocusWnd.ShowWindow(SW_HIDE);
        }

        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        tme.hwndTrack = m_hWnd;

        ::TrackMouseEvent(&tme);
    }

    HBRUSH onStaticColor(BDDCHandle dc, BDStatic wndStatic) {
        return allBk;
    }

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        RECT rect;
        GetClientRect(&rect);

        BDPaintDC dc(m_hWnd);

        BDDC localDc = ::CreateCompatibleDC(dc);
        auto hBitmap = ::CreateCompatibleBitmap(dc, rect.right, rect.bottom);//rt为RECT变量
        ::SelectObject(localDc, hBitmap);

        localDc.SelectBrush(allBk);
        localDc.FillRect(&rect, allBk);

        if (m_vscroll_range > 0) {
            localDc.SelectBrush(m_blackBrush);

            RECT rect_scroll = rect;
            rect_scroll.right -= 8;
            rect_scroll.left = rect.right - 4;
            rect_scroll.top += 8;
            rect_scroll.bottom -= 8;

            localDc.RoundRect(rect_scroll.left, rect_scroll.top, rect_scroll.right, rect_scroll.bottom, 2, 2);

            int scroll_height = rect_scroll.bottom - rect_scroll.top;
            int frame_height = rect.bottom;
            int scrollbar_height = frame_height * scroll_height / (frame_height + m_vscroll_range);
            int top = m_vscroll_pos * (scroll_height - scrollbar_height) / m_vscroll_range;
            RECT rect_bar;
            rect_bar.left = rect_scroll.left;
            rect_bar.right = rect_scroll.right;
            rect_bar.top = rect_scroll.top + top;
            rect_bar.bottom = rect_bar.top + scrollbar_height;

            localDc.SelectBrush(m_barBrush);
            localDc.RoundRect(rect_bar.left, rect_bar.top, rect_bar.right, rect_bar.bottom, 2, 2);
        }

        localDc.SelectBrush(allBk);
        BDDC mydc = ::CreateCompatibleDC(localDc);

        for (auto& item : m_users) {
            if (item.m_delta + CAPTION_HEIGHT > 0 && item.m_delta < rect.bottom) {
                //Draw Head
                //mydc.SelectBitmap(m_head);
                //localDc.BitBlt(16, item.m_delta + 10, 28, 28, mydc, 0, 0, SRCCOPY);

                int delta = 0;
                if (item.m_highlight) {
                    delta = 2;
                    rtcutil::DrawImage(localDc.m_hDC, m_highlight_circular,
                        16,
                        item.m_delta + 10,
                        28,
                        28);
                }

                rtcutil::DrawImage(localDc.m_hDC, m_head,
                    16 + delta,
                    item.m_delta + 10 + delta,
                    28 - 2 * delta,
                    28 - 2 * delta);

                //Draw Name
                localDc.SetBkMode(TRANSPARENT);
                localDc.SetTextColor(RGB(0xFF, 0xFF, 0xFF));
                // abbreviation
                localDc.SelectFont(m_abbreviationFont);
                char n = item.m_name[0];
                if (isalpha(n)) {
                    n = toupper(n);
                }
                SIZE size;
                ::GetTextExtentPoint32A(localDc.m_hDC, &n, 1, &size);

                RECT rText = { 
                        16,
                        item.m_delta + 10 + (28 - size.cy) / 2,
                        16 + 28,
                        item.m_delta + 1028
                };
                ::DrawTextA(localDc.m_hDC, &n, 1, &rText, DT_CENTER | DT_VCENTER);
                // name
                localDc.SelectFont(m_nameFont);
                rText = {52, item.m_delta + 18 , 134 + 52, item.m_delta + 50 };

                if (item.m_isHost) {
                    rText = { 52, item.m_delta + 10 , 134 + 52, item.m_delta + 50 };
                    mydc.SelectBitmap(m_host);
                    localDc.BitBlt(52, item.m_delta + 26, 44, 16, mydc, 0, 0, SRCCOPY);
                }

                auto name = item.m_name;
                if (name.size() > 12) {
                    name = name.substr(0, 12);
                    name += "...";
                }

                ::DrawTextA(localDc.m_hDC, name.c_str(), name.size(), &rText, DT_LEFT | DT_VCENTER);
                ::GetTextExtentPoint32A(localDc.m_hDC, name.c_str(), name.size(), &size);

                if(item.m_shared){
                    mydc.SelectBitmap(m_userShare);
                    localDc.BitBlt(52 + 6 + size.cx, item.m_delta + 8 + (item.m_isHost ? 0 : 8), 16, 16, mydc, 0, 0, SRCCOPY);
                }

                //Draw Audio
                if (item.m_bAudio) {
                    mydc.SelectBitmap(item.m_highlight ? m_audio_highlight : m_audio);
                    localDc.BitBlt(rect.right - 16 - 16 - 16 - 16, item.m_delta + 18, 16, 16, mydc, 0, 0, SRCCOPY);
                }
                else {
                    mydc.SelectBitmap(m_audioDisable);
                    localDc.BitBlt(rect.right - 16 - 16 - 16 - 16, item.m_delta + 18, 16, 16, mydc, 0, 0, SRCCOPY);
                }

                //Draw Video
                if (item.m_bVideo) {
                    mydc.SelectBitmap(m_video);
                    localDc.BitBlt(rect.right - 16 - 16, item.m_delta + 18, 16, 16, mydc, 0, 0, SRCCOPY);
                }
                else {
                    mydc.SelectBitmap(m_videoDisable);
                    localDc.BitBlt(rect.right - 16 - 16, item.m_delta + 18, 16, 16, mydc, 0, 0, SRCCOPY);
                }
            }
            else if (item.m_delta >= rect.bottom) {
                break;
            }
        }

        dc.BitBlt(0, 0, rect.right, rect.bottom, localDc, 0, 0, SRCCOPY);

        DeleteObject(hBitmap);
        return 0;
    }

    LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
    {
        return 0;
    }

    void AddItem(const UserAttr& user) {
        std::list<UserAttr> local(m_users.begin(), m_users.end());
        local.push_back(user);
       
        auto host = std::find_if(local.begin(), local.end(), [](const UserAttr& user)->bool {
            return user.m_isHost;
        });

        bool find = false;
        UserAttr hostUser;
        if (host != local.end()) {
            hostUser = *host;
            local.erase(host);
            find = true;
        }

        local.sort([](const UserAttr& left, const UserAttr& right)->bool {
            return left.m_name < right.m_name;
        });

        if (find) {
            local.push_front(hostUser);
        }

        m_users.swap(local);
        m_vscroll_pos = 0;

        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    void RemoveItem(const UserAttr& user) {
        auto pos = std::find_if(m_users.begin(), m_users.end(), [user](const UserAttr& other)->bool {
            return user.m_name == other.m_name;
        });

        if (pos != m_users.end()) {
            int delta = pos->m_delta;
            m_users.erase(pos);

            RECT rect;
            GetClientRect(&rect);
            rect.top = delta > rect.bottom ? rect.bottom : delta;
            rect.top = rect.top < 0 ? 0 : rect.top;
            RecalculationScroll(0, rect);
        }
    }

    void UpdateItem(const UserAttr& user) {
        auto pos = std::find_if(m_users.begin(), m_users.end(), [user](const UserAttr& other)->bool {
            return user.m_name == other.m_name;
        });

        bool hostChange = false;

        if (pos != m_users.end()) {
            hostChange = pos->m_isHost != user.m_isHost;

            pos->m_bAudio = user.m_bAudio;
            pos->m_bVideo = user.m_bVideo;
            pos->m_name = user.m_name;
            pos->m_isHost = user.m_isHost;
            pos->m_shared = user.m_shared;
            //pos->m_highlight = user.m_highlight;
            pos->m_type = user.m_type;
            //pos->m_audioLevel = user.m_audioLevel;

            UserAttr;
            if (m_userFocusWnd.IsWindowVisible() && m_userFocusWnd.GetUserInf().m_name == user.m_name) {
                m_userFocusWnd.SetUserInfo(user);
            }
        }

        RECT rect;
        GetClientRect(&rect);
        // When the host change, the order needs to be changed
        if (hostChange) {
            auto host = std::find_if(m_users.begin(), m_users.end(), [](const UserAttr& user)->bool {
                return user.m_isHost;
            });

            bool find = false;
            UserAttr hostUser;
            if (host != m_users.end()) {
                hostUser = *host;
                m_users.erase(host);
                find = true;
            }

            m_users.sort([](const UserAttr& left, const UserAttr& right)->bool {
                return left.m_name < right.m_name;
            });

            if (find) {
                m_users.push_front(hostUser);
            }
            m_vscroll_pos = 0;
            RecalculationScroll(0, rect);
        }
        else {
            rect.top = pos->m_delta;
            rect.bottom = rect.top + CAPTION_HEIGHT;
            InvalidateRect(&rect);
        }
    }

    bool IsMember(const std::string& name) {
        auto pos = std::find_if(m_users.begin(), m_users.end(), [name](const UserAttr& user)->bool {
            return user.m_name == name;
        });
        return pos != m_users.end();
    }

    void Clear() {
        m_users.clear();
        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    // users are sorted by volume
    void UpdateAllAudioLevel(const std::list<UserAttr>& users) {
        for (auto& user : m_users) {
            user.m_audioLevel = 0;
        }

        // New highlights
        for (const auto& user : users) {
            const std::string name = user.m_name;
            auto pos = std::find_if(m_users.begin(), m_users.end(), [name](const UserAttr& user)->bool {
                return user.m_name == name;
            });

            if (pos != m_users.end()) {
                pos->m_audioLevel = user.m_audioLevel;

                if (!pos->m_highlight && pos->m_audioLevel > 5) {
                    pos->m_highlight = true;

                    RECT rect;
                    GetClientRect(&rect);
                    rect.top = pos->m_delta;
                    rect.bottom = rect.top + CAPTION_HEIGHT;
                    InvalidateRect(&rect);
                }
            }
        }

        // Clear old invalid highlights
        for (auto& user : m_users) {
            if (user.m_audioLevel < 5 && user.m_highlight) {
                user.m_highlight = false;

                RECT rect;
                GetClientRect(&rect);
                rect.top = user.m_delta;
                rect.bottom = rect.top + CAPTION_HEIGHT;
                InvalidateRect(&rect);
            }
        }
    }

    void OnAudioMuteAll() {
        for (auto& user : m_users) {
            if (!user.m_isHost) {
                user.m_bAudio = false;
            }
        }

        RECT rect;
        GetClientRect(&rect);
        RecalculationScroll(0, rect);
    }

    void SetAudioMuteHanlder(std::function<void(const UserAttr&)> callback) {
        m_userFocusWnd.SetAudioMuteHanlder(callback);
    }

    void SetHostTranferHanlder(std::function<void(const UserAttr&)> callback) {
        m_userFocusWnd.SetHostTranferHanlder(callback);
    }

    int GetUserCount() {
        return m_users.size();
    }

protected:
    void RecalculationScroll(int dy, const RECT& invalid, bool force = true){
        RECT rect0;
        GetClientRect(&rect0);

        int totalNeedHight = m_users.size() * CAPTION_HEIGHT;
        auto vscroll_range = max(0, totalNeedHight - rect0.bottom);
        auto vscroll_pos = min(vscroll_range, max(0, m_vscroll_pos + dy));
        if (m_vscroll_range != vscroll_range || m_vscroll_pos != vscroll_pos) {
            m_vscroll_range = vscroll_range;
            m_vscroll_pos = vscroll_pos;

            RECT rect = rect0;
            rect.right -= 8;
            rect.left = rect.right - 4;
            rect.top += 8;
            rect.bottom -= 8;
            InvalidateRect(&rect);
        }
        else if(!force){
            return;
        }

        int index = 0;
        for (auto& item : m_users) {
            item.m_delta = index * CAPTION_HEIGHT - m_vscroll_pos;
            ++index;
        }

        InvalidateRect(&invalid);
    }

private:
    int m_vscroll_pos = 0;
    int m_vscroll_range = -1;

    std::list<UserAttr> m_users;

    BDBrush m_blackBrush;
    BDBrush m_barBrush;
    BDBrush allBk;
    BDFont m_nameFont;
    BDFont m_abbreviationFont;
    Gdiplus::Image* m_head = nullptr;
    BDBitmap m_m_head_highlight;
    BDBitmap m_audio;
    BDBitmap m_audio_highlight;
    BDBitmap m_audioDisable;
    BDBitmap m_video;
    BDBitmap m_videoDisable;
    BDBitmap m_host;
    BDBitmap m_userShare;
    BDUserFocusWnd m_userFocusWnd;

    Gdiplus::Image* m_highlight_circular = nullptr;
};

