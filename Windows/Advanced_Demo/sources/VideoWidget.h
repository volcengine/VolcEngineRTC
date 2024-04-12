#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VideoWidget.h"

enum class VideoStreamType {
    /** 
     * @brief 视频流
     */
    kVideoStream = 0,
    /** 
     * @brief 屏幕流。屏幕共享时共享的视频流.
     */
    kScreenStream = 1,
};

class VideoWidget : public QWidget {
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = Q_NULLPTR);

    QWidget *getVideoWidget();

    void showVideo(const QString &uid);

    void hideVideo();

    void setVideoStreamType(const VideoStreamType& type);

    QString getUserId();
    
    VideoStreamType getVideoStreamType();

    bool isActive();

private:
    Ui::VideoForm ui;
    QString m_uid;
    VideoStreamType m_type{ VideoStreamType::kVideoStream };
    bool m_bActive = false;
};
