#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include "BDMisc.h"

#define WM_LOGIN                WM_USER + 100
#define WM_NOTIFY_JOIN_OK        WM_USER + 200
#define WM_NOTIFY_REMOTE_SCREEN_FIRST_VIDEO        WM_USER + 201
#define WM_NOTIFY_REMOTE_FIRST_VIDEO        WM_USER + 202
#define WM_NOTIFY_USER_ADD        WM_USER + 203
#define WM_NOTIFY_USER_LEAVE    WM_USER + 204
#define WM_NOTIFY_LEAVE            WM_USER + 205
#define WM_NOTIFY_SHOW_USER        WM_USER + 206
#define WM_NOTIFY_SHOW_SETTING    WM_USER + 207
#define WM_NOTIFY_ENABLE_AUDIO    WM_USER + 208
#define WM_NOTIFY_ENABLE_VIDEO    WM_USER + 209
#define WM_NOTIFY_CLOSE_USER    WM_USER + 210
#define WM_NOTIFY_CLOSE_SETTING    WM_USER + 211
#define WM_NOTIFY_MUTE_CHANGE    WM_USER + 212
#define WM_NOTIFY_KICK_OFF        WM_USER + 213
#define WM_LOG                    WM_USER + 214
#define WM_RATE                    WM_USER + 215
#define WM_FEEDBACK                WM_USER + 216
#define WM_LOCAL_AUDIO            WM_USER + 217
#define WM_LOCAL_VIDEO            WM_USER + 218
#define WM_NOTIFY_MUTE_VIDEO      WM_USER + 219
#define WM_NOTIFY_AVINFO_ON        WM_USER + 220

#define WM_NOTIFY_RTC_STATS                 WM_USER + 221
#define WM_NOTIFY_LOCAL_VIDEO_STATS         WM_USER + 222
#define WM_NOTIFY_LOCAL_AUDIO_STATS         WM_USER + 223
#define WM_NOTIFY_REMOTE_VIDEO_STATS        WM_USER + 224
#define WM_NOTIFY_REMOTE_AUDIO_STATS        WM_USER + 225

#define WM_NOTIFY_VIEW_ATTACH     WM_USER + 226
#define WM_NOTIFY_VIEEW_RELAYOUT     WM_USER + 227
#define WM_NOTIFY_INVALID_TOKEN    WM_USER + 228
#define WM_NOTIFY_LEAVE_SUCCEED    WM_USER + 229
#define WM_NOTIFY_WARNING         WM_USER + 230
#define WM_NOTIFY_VIDEO_PREVIEW   WM_USER + 231
#define WM_NOTIFY_SCREEN_SHARE    WM_USER + 232
#define WM_NOTIFY_RECORD_VIDEO    WM_USER + 233
#define WM_NOTIFY_CLOSE_SHARE    WM_USER + 234
#define WM_NOTIFY_AUDIO_VOLUME   WM_USER + 235
#define WM_NOTIFY_LOGIN_CLICK    WM_USER + 236
#define WM_NOTIFY_STREAMS_ADD     WM_USER + 237
#define WM_NOTIFY_STREAMS_REMOVE   WM_USER + 238

#define WM_NOTIFY_AUDIO_DEVICE_EVENT     WM_USER + 239
#define WM_NOTIFY_VIDEO_DEVICE_EVENT   WM_USER + 240
#define WM_NOTIFY_INVALID_DEVICE     WM_USER + 241
#define WM_VIDEO_DEVICE_STATE_CHANGE   WM_USER + 242
#define WM_AUDIO_DEVICE_STATE_CHANGE   WM_USER + 243

#define WM_MASK_CLICK   WM_USER + 244

#define WM_NOTIFY_USER_LEAVE_SUCCEED   WM_USER + 245
#define WM_NOTIFY_CHANNEL_LEAVE_SUCCEED    WM_USER + 246
#define WM_NOTIFY_VIDEO        WM_USER + 247
#define WM_NOTIFY_UPDATE_APP   WM_USER + 248
#define WM_NOTIFY_SHOW_MEETING_LOGIN WM_USER + 249

#define WM_NOTIFY_MODIFY_NICKNAME_CALLBACK WM_USER + 250
#define WM_NOTIFY_MODIFY_NICKNAME_ERROR WM_USER + 251
#define WM_NOTIFY_CHECK_TOKEN    WM_USER + 252

#define WM_NOTIFY_FUNCTION_EXECUTE     WM_USER + 1000

#define DUID_LOGIN                1001
#define DUID_AUDIO                1002
#define DUID_VIDEO                1003
#define DUID_ROOMID               1004
#define DUID_USERID               1005
#define DUID_PHONE_NUMBER         1006
#define DUID_VERIFICATION         1007
#define DUID_GET_VERIFICATION     1008
#define DUID_SHOW_SETTING_LOGIN   1009

#define DUID_MEETING_END       1100
#define DUID_MEETING_LEAVE     1101
#define DUID_MEETING_CANCEL     1102

#define DUID_TOPBAR_LIST     1103

#define DUID_MESSAGE_AGREE       1103
#define DUID_MEETING_REFUSE     1104

#define DUID_MUTE_AUDIO        2001
#define DUID_MUTE_VIDEO        2002
#define DUID_SHARE_SCREEN      2003
#define DUID_VIDEO_RECORDING   2004
#define DUID_SHOW_USER        2005
#define DUID_SHOW_SETTING    2006
#define DUID_LEAVE            2007

#define DUID_CLOSE_USER        2008
#define DUID_CLOSE_SETTING     2009
#define DUID_ALL_MUTE_USER     2010

#define DUID_SHOW_INFO        2011
#define DUID_INPUT            2012
#define DUID_OUTPUT            2013
#define DUID_VIDEO_CAPTURE    2014
#define DUID_RESOLUTION        2015
#define DUID_SCREEN_RESOLUTION        2016
#define DUID_FPS            2017
#define DUID_SCREEN_FPS            2018
#define DUID_HISTORY        2019
#define DUID_MY_VIDEOS        2020


#define DUID_TIP_CLOSE        2021

#define DUID_RATE_CLOSE        2022
#define DUID_RATE_GOOD        2023
#define DUID_RATE_BAD        2024

#define DUID_FEEDBACK_AKA    2025
#define DUID_FEEDBACK_VKA    2026
#define DUID_FEEDBACK_SKA    2027
#define DUID_FEEDBACK_CRASH    2028
#define DUID_FEEDBACK_NOV    2029
#define DUID_FEEDBACK_OK    2030
#define DUID_FEEDBACK_EDIT    2031
#define DUID_FEEDBACK_CLOSE    2032

#define DUID_SETTING_BITRATE 2033

#define DUID_OK                2034
#define DUID_CANCEL            2035

const int VIDEOTAG = 0;
const int AUDIOTAG = 1;

class BDUserVideoViewWnd;

/**
 * @brief customer type 
*/
enum UserType {
    REMOTE_USER = 0, // remote user
    LOCAL_USER,      // local user
};
/**
 * @brief User attribute data structure
*/
struct UserAttr{
    std::string m_user_id;   // user name
    BDString m_name;
    std::string m_user_uniform_id;
    UserType m_type;      // customer type
    int64_t timeOfJoining; // Time to join the meeting
    unsigned int m_audioLevel = 0;   // audio level
    int m_delta = INT_MAX;         // windows ui position
    bool m_bAudio = false;   // have audio stream
    bool m_bVideo = false;   // have video stream
    bool m_isHost = false;   // Host or not
    bool m_shared = false;   // share screen or not
    BDUserVideoViewWnd* m_view = nullptr; //Video rendering window, Never destroy
    BDUserVideoViewWnd* m_screen_view = nullptr; //screen rendering windows, Never destroy
};

/**
 * @brief Volume Info
*/
struct AudioVolumeInfo {
    unsigned int volume = 0; // Volume value
    const char* uid = nullptr; // user name
};

/**
 * @brief Screen share thumbnails
*/
struct SnapshotAttr {
    enum SnapshotType   // thumbnails type
    {
        SNAPSHOT_UNKNOW = 0,
        SNAPSHOT_SCREEN,   // display screen share
        SNAPSHOT_WINDOW    // window share
    };

    std::string m_name;    // thumbnail name
    SnapshotType m_type = SNAPSHOT_UNKNOW;
    void* source_id;       // share source id

    int x = 0;             // The position of the thumbnail on the window
    int y = 0;             // The position of the thumbnail on the window
    int index = 0;         // thumbnail index
};
