#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <QObject>

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <cstdint>
#include <thread>
#include <mutex>

extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
}

class VideoDecoder : public QObject
{
    Q_OBJECT
public:
    explicit VideoDecoder(QObject *parent = nullptr);
    ~VideoDecoder();

    bool LoadVideoFile(const std::string& file_path);

    std::vector<uint8_t>& NextFrame(bool&is_key_frame);
    size_t Height() const;
    size_t Width() const;
    size_t GetFramerate();
    std::vector<uint8_t>& GetKeyFrame();

protected:
    void clear_();
    std::vector<uint8_t>& ReadAvccCovertAnnexb(bool&is_key_frame);
    std::vector<uint8_t>& ReadAnnexb(bool&is_key_frame);
protected:
    std::string video_file_;
    size_t width_ = 0;
    size_t height_ = 0;
    size_t fps_ = 0;

    AVFormatContext * p_fmt_ctx_ = nullptr;
    AVCodecContext *p_codec_ctx_ = nullptr;
    AVFrame *p_frame_ = nullptr;
    AVFrame *p_frame_yuv_ = nullptr;
    uint8_t *out_buffer_ = nullptr;
    AVPacket *p_packet_ = nullptr;

    SwsContext *p_swsctx_ = nullptr;
    int video_index_ = -1;

    std::vector<uint8_t> result_;
    std::vector<uint8_t> key_result_;

    AVPacket sps_pkt_  ;
    AVPacket pps_pkt  ;
    bool set_sps_pps_ = false;
    int sps_len_ = 0;
    int pps_len_ = 0;

    //FILE *test_fp_;

    std::mutex mtx_;
    bool loop_ = false;

    int video_frame_count = 0;
    int current_pts_ = 0;

};


#endif // VIDEODECODER_H
