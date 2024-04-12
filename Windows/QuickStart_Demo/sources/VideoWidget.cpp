#include "VideoWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFontMetrics>

VideoWidget::VideoWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    hideVideo();
}

void VideoWidget::showVideo(const QString &uid) {

	m_uid = uid;
    ui.label->show();
    ui.videoCanvas->show();
    m_bActive = true;
	auto fm = ui.label->fontMetrics();
	auto elideText = fm.elidedText(uid, Qt::ElideRight, 150);
	ui.label->setToolTip(uid);
    ui.label->setText(elideText);
}

void VideoWidget::hideVideo() {
    m_uid.clear();
    ui.label->hide();
    ui.videoCanvas->hide();
    m_bActive = false;
}

QString VideoWidget::getUserId() {
    return m_uid;
}

QWidget *VideoWidget::getVideoWidget() {
    return ui.videoCanvas;
}

bool VideoWidget::isActive() {
    return m_bActive;
}