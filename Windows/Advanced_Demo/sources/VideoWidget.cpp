#include "VideoWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QFontMetrics>

VideoWidget::VideoWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    hideVideo();
}

void VideoWidget::showVideo(const QString &uid) {
	m_uid = uid;
	ui.label->show();
	m_bActive = true;
	auto fm = ui.label->fontMetrics();
	auto elideText = fm.elidedText(uid, Qt::ElideRight, 150);
	ui.label->setToolTip(uid);
	ui.label->setText(elideText);
	ui.videoCanvas->setStyleSheet("background-color: #333333");
	QTimer::singleShot(100, this, [=] {
		ui.videoCanvas->setUpdatesEnabled(false);
	});
}

void VideoWidget::hideVideo() {
	m_uid.clear();
	ui.label->hide();
	m_bActive = false;
	ui.videoCanvas->setStyleSheet("");
	ui.videoCanvas->setUpdatesEnabled(true);
	QTimer::singleShot(100, this, [=] {
		ui.videoCanvas->update();
	});
}

void VideoWidget::setVideoStreamType(const VideoStreamType& type) {
	m_type = type;
}

QString VideoWidget::getUserId() {
    return m_uid;
}

VideoStreamType VideoWidget::getVideoStreamType() {
	return m_type;
}

QWidget *VideoWidget::getVideoWidget() {
    return ui.videoCanvas;
}

bool VideoWidget::isActive() {
    return m_bActive;
}