#pragma once
#include <windows.h>
#include <sstream>
#include <QString>
#include <QFont>
#include "model.h"
#include "bytertc_video.h"

namespace utils {

std::string getOsInfo();

QString elideText(const QFont& font, const QString& str, int width);

VideoKbpsHint getVideoKpbsHit(int w, int h);
VideoKbpsHint getVideoKpbsHit(const VideoResolution& resolution);
int getIdxFromResolution(const VideoResolution& resolution);


int getVideoCaptureDevices(bytertc::IRTCVideo* rtc_video, std::vector<RtcDevice>& devices);
int setVideoCaptureDevice(bytertc::IRTCVideo* rtc_video,const std::string device_id);

int getShareList(bytertc::IRTCVideo* rtc_video, std::vector<SnapshotAttr>& list);
QPixmap getThumbnail(bytertc::IRTCVideo* rtc_video,
                     SnapshotAttr::SnapshotType type, void* source_id,
                     int max_width, int max_height);

int setScreenProfile(bytertc::IRTCVideo* rtc_video, int width, int height,
                     int fps, int kbps);
int setVideoProfile(bytertc::IRTCVideo* rtc_video, int width, int height,
                    int fps, int kbps);

void StartScreenCapture(bytertc::IRTCVideo* rtc_video, bytertc::IRTCRoom* rtc_room, void* source_id);
void StartWindowCapture(bytertc::IRTCVideo* rtc_video, bytertc::IRTCRoom* rtc_room, void* source_id);

void StopScreenCapture(bytertc::IRTCVideo* rtc_video, bytertc::IRTCRoom* rtc_room);

void StartScreenAudioCapture(bytertc::IRTCVideo* rtc_video);
void StopScreenAudioCapture(bytertc::IRTCVideo* rtc_video);
}  // namespace utils
