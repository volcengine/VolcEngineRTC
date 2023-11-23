#include "AudioMixItem.h"
#include "ui_AudioMixItem.h"

#include <QSpinBox>
#include <QButtonGroup>

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
