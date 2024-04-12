#include "utils.h"
#include <QFontMetrics>
#include <QPixmap>

namespace utils {

    std::string getOsInfo() {
  // get os name according to version number
  OSVERSIONINFO osver = {sizeof(OSVERSIONINFO)};
  GetVersionEx(&osver);
  std::string os_name;
  if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)
    os_name = "Windows 2000";
  else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
    os_name = "Windows XP";
  else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
    os_name = "Windows 2003";
  else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
    os_name = "windows vista";
  else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
    os_name = "windows 7";
  else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)
    os_name = "windows 10";

  std::ostringstream res;
  res << os_name << " " << osver.dwMajorVersion << '.' << osver.dwMinorVersion;
  return res.str();
}

QString elideText(const QFont& font, const QString& str, int width) {
  QFontMetrics mf(font);
  QString res = str;
  if (mf.horizontalAdvance(str) > width) {
    res = mf.elidedText(str, Qt::TextElideMode::ElideRight, width);
  }
  return res;
}

static std::vector<std::tuple<VideoResolution, VideoKbpsHint>> g_video_kbps = {
    {{160, 160}, {40, 150}},    {{320, 180}, {80, 350}},
    {{320, 240}, {100, 400}},   {{640, 360}, {200, 1000}},
    {{480, 480}, {200, 1000}},  {{640, 480}, {250, 1000}},
    {{960, 540}, {400, 1600}},  {{1280, 720}, {500, 2000}},
    {{1920, 1080}, {800, 3000}} };

VideoKbpsHint getVideoKpbsHit(int w, int h) {
    VideoKbpsHint hint;
    for (const auto& iter : g_video_kbps) {
        if (w == std::get<0>(iter).width && h == std::get<0>(iter).height) {
            hint.min_kbps = std::get<1>(iter).min_kbps;
            hint.max_kbps = std::get<1>(iter).max_kbps;
            break;
        }
    }

    return hint;
}

VideoKbpsHint getVideoKpbsHit(const VideoResolution& resolution) {
    return getVideoKpbsHit(resolution.width, resolution.height);
}

int getIdxFromResolution(const VideoResolution& resolution) {
    int idx = -1;
    for (const auto& iter : g_video_kbps) {
        idx++;
        if (resolution.width == std::get<0>(iter).width &&
            resolution.height == std::get<0>(iter).height)
            return idx;
    }
    return idx;
}


int getVideoCaptureDevices(bytertc::IRTCVideo* rtc_video, std::vector<RtcDevice>& devices) {
    std::string strSelectedDeviceId;
    char szName[512], szId[512];
    int devIdx = 0;

    // enum video capture devices
    auto video_device_manager = rtc_video->getVideoDeviceManager();

    bytertc::IDeviceCollection* pVideoRecordCollection =
        video_device_manager->enumerateVideoCaptureDevices();
    if (pVideoRecordCollection) {
        memset(szName, 0, sizeof(szName));
        memset(szId, 0, sizeof(szId));
        devIdx = 0;

        // get selected device id
        video_device_manager->getVideoCaptureDevice(szId);
        strSelectedDeviceId = szId;

        int nVideoCaptureNum = pVideoRecordCollection->getCount();
        if (nVideoCaptureNum > 0) {
            for (int i = 0; i < nVideoCaptureNum; ++i) {
                memset(szName, 0, sizeof(szName));
                memset(szId, 0, sizeof(szId));

                if (pVideoRecordCollection->getDevice(i, szName, szId) == 0) {
                    if (strSelectedDeviceId == szId) {
                    }

                    RtcDevice device;
                    device.name = szName;
                    device.device_id = szId;

                    devices.push_back(device);
                }
            }
        }

        pVideoRecordCollection->release();
        pVideoRecordCollection = nullptr;
    }
    return 0;
}

int setVideoCaptureDevice(bytertc::IRTCVideo* rtc_video, const std::string device_id)
{
    auto video_device_manager = rtc_video->getVideoDeviceManager();
    video_device_manager->setVideoCaptureDevice(device_id.c_str());
    return 0;
}

int setVideoCaptureDevice(bytertc::IRTCVideo* rtc_video, const std::string & device_id) {
    auto video_device_manager = rtc_video->getVideoDeviceManager();
    return video_device_manager->setVideoCaptureDevice(device_id.c_str());
}

static int SetVideoEncoderConfig(bytertc::IRTCVideo* rtc_video,bytertc::StreamIndex index, int width, int height, int fps, int kbps) {
    bytertc::VideoSolution video_solution;
    video_solution.fps = fps;
    video_solution.width = width;
    video_solution.height = height;
    video_solution.max_send_kbps = kbps;
    return rtc_video->setVideoEncoderConfig(index,
        &video_solution, 1);
}

int setScreenProfile(bytertc::IRTCVideo* rtc_video,int width,int height,int fps,int kbps) {
  return SetVideoEncoderConfig(rtc_video, bytertc::StreamIndex::kStreamIndexScreen, width, height, fps, kbps);
}

int setVideoProfile(bytertc::IRTCVideo* rtc_video, int width, int height,
                     int fps, int kbps) {
    return SetVideoEncoderConfig(rtc_video, bytertc::StreamIndex::kStreamIndexMain, width, height, fps, kbps);
}

int getShareList(bytertc::IRTCVideo* rtc_video, std::vector<SnapshotAttr>& list) {

    int display_index = 0;
    SnapshotAttr snapshot;
    static std::string desktop_names[] = {
        "桌面一", "桌面二", "桌面三", "桌面四", "桌面五",
        "桌面六", "桌面七", "桌面八", "桌面九", "桌面十",
    };

    auto sourcelist = rtc_video->getScreenCaptureSourceList();
    int count = sourcelist->getCount();
    for (int i = 0; i < count; ++i) {
        auto source = sourcelist->getSourceInfo(i);
        snapshot.name = source.source_name;
        snapshot.source_id = source.source_id;
        switch (source.type) {
        case bytertc::kScreenCaptureSourceTypeScreen: {
            snapshot.type = SnapshotAttr::kScreen;
            auto pos =
                std::find_if(list.begin(), list.end(), [](const SnapshotAttr& s) {
                return s.type == SnapshotAttr::kWindow;
                    });

            snapshot.name = desktop_names[display_index];
            ++display_index;

            if (pos != list.end()) {
                list.insert(pos, snapshot);
            }
            else {
                list.push_back(snapshot);
            }
            break;
        }
        case bytertc::kScreenCaptureSourceTypeWindow:
            snapshot.type = SnapshotAttr::kWindow;
            list.push_back(snapshot);
            break;
        default:
            break;
        }
    }

    sourcelist->release();
    return 0;
}

QPixmap getThumbnail(bytertc::IRTCVideo* rtc_video,
                     SnapshotAttr::SnapshotType type,
    void* source_id, int max_width,
    int max_height) {
    QPixmap pix_map;

    auto s_type = bytertc::kScreenCaptureSourceTypeUnknown;
    switch (type) {
    case SnapshotAttr::kScreen:
        s_type = bytertc::kScreenCaptureSourceTypeScreen;
        break;
    case SnapshotAttr::kWindow:
        s_type = bytertc::kScreenCaptureSourceTypeWindow;
        break;
    default:
        break;
    }
    auto p = rtc_video->getThumbnail(s_type, source_id, max_width, max_height);

    QImage img(reinterpret_cast<uchar*>(p->getPlaneData(0)), p->width(),
        p->height(), QImage::Format::Format_RGB32);
    return QPixmap::fromImage(img);
}

void StartScreenAudioCapture(bytertc::IRTCVideo* rtc_video) {
    rtc_video->startScreenAudioCapture();
}

void StopScreenAudioCapture(bytertc::IRTCVideo* rtc_video) {
    rtc_video->stopScreenAudioCapture();
}


static void StartScreenVideoCapture(bytertc::IRTCVideo* rtc_video, bytertc::IRTCRoom* rtc_room, bytertc::ScreenCaptureSourceType type, void* source_id)
{
    bytertc::ScreenCaptureSourceInfo info;
    bytertc::ScreenCaptureParameters param;
    info.type = type;
    info.source_id = source_id;
    param.capture_mouse_cursor = bytertc::MouseCursorCaptureState::kMouseCursorCaptureStateOn;
    int ret = rtc_video->startScreenVideoCapture(info, param);
    rtc_room->publishScreen(bytertc::MediaStreamType::kMediaStreamTypeBoth);
}


void StartScreenCapture(bytertc::IRTCVideo* rtc_video, bytertc::IRTCRoom* rtc_room, void * source_id) {
    StartScreenVideoCapture(rtc_video, rtc_room,  bytertc::ScreenCaptureSourceType::kScreenCaptureSourceTypeScreen,source_id);
    
}

void StartWindowCapture(bytertc::IRTCVideo* rtc_video, bytertc::IRTCRoom* rtc_room, void* source_id)
{
    StartScreenVideoCapture(rtc_video, rtc_room, bytertc::ScreenCaptureSourceType::kScreenCaptureSourceTypeWindow, source_id);
}

void StopScreenCapture(bytertc::IRTCVideo* rtc_video, bytertc::IRTCRoom* rtc_room) {
    rtc_room->unpublishScreen(bytertc::MediaStreamType::kMediaStreamTypeBoth);
    rtc_video->stopScreenVideoCapture();
}

}  // namespace utils