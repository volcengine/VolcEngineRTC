#include "VideoDecoder.h"

#include <vector>

#include <QFile>
#include <QDebug>

VideoDecoder::VideoDecoder(QObject *parent)
    : QObject{parent}
{
    avformat_network_init();
}

VideoDecoder::~VideoDecoder()
{
    clear_();
}



bool VideoDecoder::LoadVideoFile(const std::string& file_path)
{
    if (!QFile::exists(QString::fromStdString(file_path))) {
        qWarning() << Q_FUNC_INFO << "file not exits, path:" << QString::fromStdString(file_path);
        return false;
    }
    video_file_ = file_path;
    bool _prepared = true;
    do {

        p_fmt_ctx_ = avformat_alloc_context();

        if (avformat_open_input(&p_fmt_ctx_, video_file_.c_str(), NULL, NULL) != 0) {
            std::cerr << "Couldn't open input stream." << std::endl;
            _prepared = false;
            break;
        }

        if (avformat_find_stream_info(p_fmt_ctx_, NULL) < 0) {
            std::cerr << "Couldn't find stream information." << std::endl;
            _prepared = false;
            break;
        }

        for (unsigned int i = 0; i < p_fmt_ctx_->nb_streams; ++i) {
            if (p_fmt_ctx_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                video_index_ = i;
                break;
            }
        }

        if (video_index_ == -1) {
            std::cerr << "Didn't find a video stream." << std::endl;
            _prepared = false;
            break;
        }

        p_codec_ctx_ = avcodec_alloc_context3(NULL);
        if (avcodec_parameters_to_context(p_codec_ctx_, p_fmt_ctx_->streams[video_index_]->codecpar) < 0) {
            std::cerr << "Didn't parameters to contex." << std::endl;
            _prepared = false;
            break;
        }
        const AVCodec* pCodec = avcodec_find_decoder(p_codec_ctx_->codec_id);
        if (pCodec == NULL) {
            std::cerr << "Codec not found." << std::endl;
            _prepared = false;
            break;
        }
        if (avcodec_open2(p_codec_ctx_, pCodec, NULL) < 0) {
            std::cerr << "Could not open codec." << std::endl;
            _prepared = false;
            break;
        }
        width_ = p_codec_ctx_->width;
        height_ = p_codec_ctx_->height;
        fps_ = p_fmt_ctx_->streams[video_index_]->avg_frame_rate.num / p_fmt_ctx_->streams[video_index_]->avg_frame_rate.den;


        p_frame_ = av_frame_alloc();
        p_frame_yuv_ = av_frame_alloc();


        out_buffer_ = (uint8_t*)av_malloc(
            av_image_get_buffer_size(
                AV_PIX_FMT_YUV420P, p_codec_ctx_->width, p_codec_ctx_->height, 1
            ) * sizeof(uint8_t));
        p_packet_ = av_packet_alloc();


        av_image_fill_arrays(
            p_frame_yuv_->data,
            p_frame_yuv_->linesize,
            out_buffer_,
            AV_PIX_FMT_YUV420P,
            p_codec_ctx_->width,
            p_codec_ctx_->height,
            1);

        p_swsctx_ = sws_getContext(p_codec_ctx_->width, p_codec_ctx_->height, p_codec_ctx_->pix_fmt,
            p_codec_ctx_->width, p_codec_ctx_->height, AV_PIX_FMT_YUV420P, 0, NULL, NULL, NULL);

    } while (false);

    if (!_prepared) {
        this->clear_();
        return false;
    }
    return true;
}

std::vector<uint8_t>& VideoDecoder::NextFrame(bool& is_key_frame)
{
    if (!p_fmt_ctx_ || !p_codec_ctx_) {
        return result_;
    }
    if (p_fmt_ctx_->streams[video_index_]->codecpar->extradata &&
        p_fmt_ctx_->streams[video_index_]->codecpar->extradata[0] == 1) { //avcctoannexb 
        return ReadAvccCovertAnnexb(is_key_frame);
    }
    else {//annexb
        return ReadAnnexb(is_key_frame);
    }

    return result_;
}

size_t VideoDecoder::Height() const { return height_; }

size_t VideoDecoder::Width() const { return width_; }

size_t VideoDecoder::GetFramerate() { return fps_; }

std::vector<uint8_t>& VideoDecoder::GetKeyFrame()
{
    std::lock_guard<std::mutex> lock_(mtx_);
    return key_result_;
}

void VideoDecoder::clear_()
{
    if (p_swsctx_ != NULL) {
        sws_freeContext(p_swsctx_);
    }
    p_swsctx_ = nullptr;
    if (out_buffer_ != nullptr) {
        av_free(out_buffer_);
    }
    out_buffer_ = nullptr;
    if (p_frame_yuv_ != nullptr) {
        av_frame_free(&p_frame_yuv_);
    }
    p_frame_yuv_ = nullptr;
    if (p_frame_ != nullptr) {
        av_frame_free(&p_frame_);
    }
    p_frame_ = nullptr;
    if (p_codec_ctx_ != nullptr) {
        avcodec_close(p_codec_ctx_);
    }
    p_codec_ctx_ = nullptr;
    if (p_fmt_ctx_ != nullptr) {
        avformat_close_input(&p_fmt_ctx_);
    }
    p_fmt_ctx_ = nullptr;
    video_index_ = -1;
}

std::vector<uint8_t>& VideoDecoder::ReadAvccCovertAnnexb(bool& is_key_frame)
{
    AVPacket tmp_pkt;
    static uint8_t start_code[4] = { 0x00, 0x00, 0x00, 0x01 };

    int ret = 0;
    while (!ret) {
        ret = av_read_frame(p_fmt_ctx_, p_packet_);
        if (ret == AVERROR_EOF) {
            if (loop_) {
                av_seek_frame(p_fmt_ctx_, video_index_, 0, AVSEEK_FLAG_BACKWARD);
                av_packet_unref(p_packet_);
                continue;;
            }
            break;
        }
        if (p_packet_->stream_index == video_index_) {
            result_.clear();
            int frame_len = 0;
            if (!set_sps_pps_) {
                uint8_t* ex_data = p_fmt_ctx_->streams[video_index_]->codecpar->extradata;
                if (!ex_data) {
                    av_packet_unref(p_packet_);
                    continue;
                }
                sps_len_ = (ex_data[6] << 8) | ex_data[7];
                pps_len_ = (ex_data[8 + sps_len_ + 1] << 8) | ex_data[8 + sps_len_ + 2];
                av_new_packet(&sps_pkt_, sps_len_ + 4);
                av_new_packet(&pps_pkt, pps_len_ + 4);

                //sps
                memcpy(sps_pkt_.data, start_code, 4);
                memcpy(sps_pkt_.data + 4, ex_data + 8, sps_len_);
                sps_pkt_.size = sps_len_ + 4;
                frame_len = sps_len_ + 4;
                result_.reserve(frame_len);
                result_.insert(result_.end(), sps_pkt_.data, sps_pkt_.data + sps_pkt_.size);


                //pps
                memcpy(pps_pkt.data, start_code, 4);
                memcpy(pps_pkt.data + 4, ex_data + 8 + sps_len_ + 2 + 1, pps_len_);
                pps_pkt.size = pps_len_ + 4;
                frame_len += pps_len_ + 4;
                result_.reserve(frame_len);
                result_.insert(result_.end(), pps_pkt.data, pps_pkt.data + pps_pkt.size);

                set_sps_pps_ = true;
            }

            //nal
            int nal_len = 0;
            uint8_t* data = p_packet_->data;
            while (data < p_packet_->data + p_packet_->size)
            {
                //default nal len is 4, todo parse NALULengthSizeMinusOne    
                /*
                05| FF          NAL size:  4�ֽ�
                06| E1          SPS num:   1
                07| 00 1F       SPS size:  31�ֽ�
                09| 67          NAL type:  SPS
                40| 01          PPS num:   1
                41| 00 05       PPS size:  5�ֽ�
                42| 68          NAL type:  PPS
                */
                nal_len = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
                if (nal_len > 0) {
                    int nal_type = (data[4] & 0x1f);
                    if (0x07 == nal_type || nal_type == 0x08) {
                        data = data + 4 + nal_len;
                        continue;
                    }
                    memcpy(data, start_code, 4);
                    tmp_pkt = *p_packet_;
                    tmp_pkt.data = p_packet_->data;
                    tmp_pkt.size = p_packet_->size + 4;

                    frame_len += 4 + nal_len;
                    result_.reserve(frame_len);
                    result_.insert(result_.end(), tmp_pkt.data, tmp_pkt.data + tmp_pkt.size);
                    data = data + 4 + nal_len;
                }
            }

            if (p_packet_->flags & AV_PKT_FLAG_KEY) { //I帧
                std::lock_guard<std::mutex> lock_(mtx_);
                key_result_.clear();
                key_result_.reserve(result_.size());
                key_result_.insert(key_result_.end(), result_.begin(), result_.end());
                is_key_frame = true;
            }
            
            

            if (result_.size() > 0) {
                video_frame_count++;
                current_pts_ = p_packet_->pts;
                //fwrite((void*)result_.data(), 1, result_.size(), test_fp_);
                break;
            }
            else {
                av_packet_unref(p_packet_);
            }
        }
    }
    av_packet_unref(p_packet_);
    return result_;
}

std::vector<uint8_t>& VideoDecoder::ReadAnnexb(bool& is_key_frame)
{
    int ret = 0;
    while (!ret) {
        ret = av_read_frame(p_fmt_ctx_, p_packet_);
        if (ret == AVERROR_EOF) {
            if (loop_) {
                av_seek_frame(p_fmt_ctx_, video_index_, 0, AVSEEK_FLAG_BACKWARD);
                av_packet_unref(p_packet_);
                continue;
            }
            break;
        }
        if (p_packet_->stream_index == video_index_) {
            result_.clear();
            int frame_len = p_packet_->size;

            result_.reserve(frame_len);
            result_.insert(result_.end(), p_packet_->data, p_packet_->data + p_packet_->size);

            if (p_packet_->flags & AV_PKT_FLAG_KEY) {
                std::lock_guard<std::mutex> lock_(mtx_);
                key_result_.clear();
                key_result_.reserve(result_.size());
                key_result_.insert(key_result_.end(), result_.begin(), result_.end());
                is_key_frame = true;
            }

            if (result_.size() > 0) {
                video_frame_count++;
                current_pts_ = p_packet_->pts;
                //fwrite((void*)result_.data(), 1, result_.size(), test_fp_);
                break;
            }
            else {
                av_packet_unref(p_packet_);
            }
        }
    }
    av_packet_unref(p_packet_);
    return result_;
}
