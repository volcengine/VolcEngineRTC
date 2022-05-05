#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VideoWidget.h"

class VideoWidget : public QWidget {
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = Q_NULLPTR);

    QWidget *getVideoWidget();

    void showVideo(const QString &uid);

    void hideVideo();

    QString getUserId();

    bool isActive();

private:
    Ui::VideoForm ui;
    QString m_uid;
    bool m_bActive = false;
};
