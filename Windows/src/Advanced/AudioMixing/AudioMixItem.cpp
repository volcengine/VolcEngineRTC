#include "AudioMixItem.h"
#include "ui_AudioMixItem.h"

#include <QSpinBox>
#include <QPainter>

#include <QButtonGroup>
#include "Resources.h"

AudioMixItem::AudioMixItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioMixItem)
{
    ui->setupUi(this);

    m_group_button = new QButtonGroup(this);
    m_group_button->addButton(ui->radioButton_both);
    m_group_button->addButton(ui->radioButton_local);
    m_group_button->addButton(ui->radioButton_remote);
    m_group_button->setExclusive(true);
    ui->radioButton_both->setChecked(true);
    connect(ui->btn_start, &QPushButton::clicked, this, &AudioMixItem::onBtnPlayClicked);
    connect(ui->btn_stop, &QPushButton::clicked, this, &AudioMixItem::pnBtnStopClicked);
    connect(ui->btn_pause, &QPushButton::clicked, this, &AudioMixItem::onBTnPauseClicked);
    connect(ui->btn_resume, &QPushButton::clicked, this, &AudioMixItem::onBtnResumeClicked);
    connect(ui->spinBox_volume, SIGNAL(valueChanged(int)), this, SLOT(onSpinVolumeChanged(int)));
    connect(ui->spinBox_time, SIGNAL(valueChanged(int)), this, SLOT(onSpinTimeChanged(int)));

    QList<QWidget *> childWidgets = this->findChildren<QWidget *>();
    // 遍历子控件并设置样式表
    foreach (QWidget *childWidget, childWidgets) {
        QLabel *label = qobject_cast<QLabel *>(childWidget);
        if (label) {
            label->setStyleSheet(APIDemo::str_qss_label);
        }
    }

    ui->label_state->setStyleSheet("QLabel{color:#0C0D0E;font-family: PingFang SC;font-size: 14px;}");
    ui->label_id->setStyleSheet("QLabel{color:#737A87;font-family: PingFang SC;font-size: 16px;}");
    ui->btn_stop->setStyleSheet(APIDemo::str_qss_btn4);
    ui->btn_pause->setStyleSheet(APIDemo::str_qss_btn4);
    ui->btn_resume->setStyleSheet(APIDemo::str_qss_btn4);
    ui->btn_start->setStyleSheet(APIDemo::str_qss_btn4);
    ui->spinBox_time->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->spinBox_volume->setStyleSheet(APIDemo::str_qss_spinbox);
}

AudioMixItem::~AudioMixItem()
{
    delete ui;
}

void AudioMixItem::onBtnPlayClicked()
{
    int play_type = 0;
    int id = ui->label_id->text().toInt();
    QRadioButton *radio = dynamic_cast<QRadioButton*>(m_group_button->checkedButton());
    if (radio == ui->radioButton_local) {
        play_type = 0;
    } else if (radio == ui->radioButton_remote) {
        play_type = 1;
    } else {
        play_type = 2;
    }
    emit sigBtnPlayClicked(id, play_type);
}

void AudioMixItem::pnBtnStopClicked()
{
    int id = ui->label_id->text().toInt();
    emit sigBtnStopClicked(id);
}

void AudioMixItem::onBTnPauseClicked()
{
    int id = ui->label_id->text().toInt();
    emit sigBtnPauseClicked(id);
}

void AudioMixItem::onBtnResumeClicked()
{
    int id = ui->label_id->text().toInt();
    emit sigBtnResumeClicked(id);
}

void AudioMixItem::onSpinTimeChanged(int)
{
    int id = ui->label_id->text().toInt();
    int time = ui->spinBox_time->value();
    emit sigSpinTimeChanged(id, time);
}

void AudioMixItem::onSpinVolumeChanged(int)
{
    int id = ui->label_id->text().toInt();
    int volume = ui->spinBox_volume->value();
    emit sigSpinVolumeChanged(id, volume);
}

void AudioMixItem::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), QBrush(QColor("#fcfdfe")));
    p.setPen(QPen(QBrush("#EAEDF1"), 2));
    p.drawRect(rect());
}

QLabel* AudioMixItem::getID() 
{ return ui->label_id; }

QLabel* AudioMixItem::getState() {
    return ui->label_state;
}

QPushButton* AudioMixItem::getPlayBtn()
{
    return ui->btn_start;;
}

QPushButton* AudioMixItem::getStopBtn()
{
    return ui->btn_stop;
}

QPushButton* AudioMixItem::getPauseBtn()
{
    return ui->btn_pause;
}

QPushButton* AudioMixItem::getResumeBtn()
{
    return ui->btn_resume;
}

QSpinBox* AudioMixItem::getTimeSpin()
{
    return ui->spinBox_time;
}

QSpinBox* AudioMixItem::getVolumeSpin()
{
    return ui->spinBox_volume;
}

QLabel* AudioMixItem::getDuration()
{
    return ui->label_duration;
}
