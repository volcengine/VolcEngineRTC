#include "OperateWidget.h"
#include <QMouseEvent>
#include <QPainter>

OperateWidget::OperateWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    parent->installEventFilter(this);

    connect(this, SIGNAL(sigHangup()), parent, SLOT(slotOnHangup()));
    connect(ui.settingBtn, &QPushButton::clicked, this, [=] {emit sigSetting(); });
    connect(ui.shareScreenBtn, &QPushButton::clicked, this, [=] {emit sigShareScreen(ui.shareScreenBtn->isChecked()); });
}

bool OperateWidget::eventFilter(QObject *watched, QEvent *event) {
    if (watched == parent()) {
        auto parentWindow = dynamic_cast<QWidget *>(parent());
        if (parentWindow == nullptr) {
            return false;
        }
        if (event->type() == QEvent::Resize || event->type() == QEvent::Move) {
            //update login geometry
            auto selfRect = this->rect();
            auto parentGem = parentWindow->geometry();

            int nleft = parentGem.left() + (parentGem.width() - selfRect.width()) / 2;
            int nTop = parentGem.bottom() - 30 - selfRect.height();

            setGeometry(nleft, nTop, selfRect.width(), selfRect.height());
        }
    }
    return false;
}

void OperateWidget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QBrush b("#36393F");
    p.setBrush(b);
    QPen pen(Qt::transparent);
    p.setPen(pen);

    p.drawRoundedRect(this->rect(), 30, 30);
}

void OperateWidget::on_hangupBtn_clicked() {
    emit sigHangup();
}

void OperateWidget::on_muteAudioBtn_clicked() {
    emit sigMuteAudio(ui.muteAudioBtn->isChecked());
}

void OperateWidget::on_muteVideoBtn_clicked() {
    emit sigMuteVideo(ui.muteVideoBtn->isChecked());
}

void OperateWidget::setScreen(bool state)
{
    ui.shareScreenBtn->blockSignals(true);
    ui.shareScreenBtn->clicked(state);
    ui.shareScreenBtn->setChecked(!state);
    ui.shareScreenBtn->blockSignals(false);
}

void OperateWidget::reset()
{
	ui.muteAudioBtn->blockSignals(true);
	ui.muteAudioBtn->clicked(false);
	ui.muteAudioBtn->setChecked(false);
	ui.muteAudioBtn->blockSignals(false);

	ui.muteVideoBtn->blockSignals(true);
	ui.muteVideoBtn->clicked(false);
	ui.muteVideoBtn->setChecked(false);
	ui.muteVideoBtn->blockSignals(false);

    ui.shareScreenBtn->blockSignals(true);
    ui.shareScreenBtn->clicked(false);
    ui.shareScreenBtn->setChecked(false);
    ui.shareScreenBtn->blockSignals(false);

}

void OperateWidget::on_beautyBtn_clicked()
{
	emit sigBeautySettingBtn();
}