#pragma once
#include <unordered_map>
#include <vector>

struct VideoResolution {
  int width = 160;
  int height = 160;
};

struct VideoKbpsHint {
  int min_kbps = 40;
  int max_kbps = 150;
};

struct VideoConfiger {
  VideoResolution resolution;
  VideoKbpsHint kbpsRange;
  int fps = 15;
  int kbps = 60;
};

struct SettingModel {
  VideoConfiger camera{{640, 480}, {250, 1000}, 15, 500};
  VideoConfiger screen{{1920, 1080}, {800, 3000}, 15, 1500};
  int camera_idx = -1;
  int mic_idx = -1;
  bool enable_show_info = false;
};

struct UserInfo {
  std::string uid;
};


struct SnapshotAttr {
    enum SnapshotType  // thumbnails type
    {
        kUnkonw = 0,
        kScreen,  // display screen share
        kWindow   // window share
    };

    std::string name;  // thumbnail name
    SnapshotType type = kUnkonw;
    void* source_id;  // share source id
    int index = 0;    // thumbnail index
};


struct RtcDevice {
    std::string name;
    std::string device_id;
};


