#pragma once
#include <windows.h>
#include <sstream>
#include <QString>
#include <QFont>
#include "model.h"
#include "bytertc_engine_interface.h"

namespace utils {

std::string getOsInfo();

QString elideText(const QFont& font, const QString& str, int width);

VideoKbpsHint getVideoKpbsHit(int w, int h);
VideoKbpsHint getVideoKpbsHit(const VideoResolution& resolution);
int getIdxFromResolution(const VideoResolution& resolution);


int getVideoCaptureDevices(bytertc::IRtcEngine* engine, std::vector<RtcDevice>& devices);
int setVideoCaptureDevice(bytertc::IRtcEngine* engine,const std::string device_id);

int getShareList(bytertc::IRtcEngine* engine, std::vector<SnapshotAttr>& list);
QPixmap getThumbnail(bytertc::IRtcEngine* engine,
                     SnapshotAttr::SnapshotType type, void* source_id,
                     int max_width, int max_height);

int setScreenProfile(bytertc::IRtcEngine* engine, int width, int height,
                     int fps, int kbps);
int setVideoProfile(bytertc::IRtcEngine* engine, int width, int height,
                    int fps, int kbps);

void StartScreenCapture(bytertc::IRtcEngine* engine, void* source_id);
void StartWindowCapture(bytertc::IRtcEngine* engine, void* source_id);

void StopScreenCapture(bytertc::IRtcEngine* engine);

void StartScreenAudioCapture(bytertc::IRtcEngine* engine);
void StopScreenAudioCapture(bytertc::IRtcEngine* engine);
}  // namespace utils
