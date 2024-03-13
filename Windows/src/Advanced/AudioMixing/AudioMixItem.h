#ifndef AUDIOMIXITEM_H
#define AUDIOMIXITEM_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>


namespace Ui {
class AudioMixItem;
}

class QButtonGroup;
class AudioMixItem : public QWidget
{
    Q_OBJECT

public:
    explicit AudioMixItem(QWidget *parent = nullptr);
    ~AudioMixItem();

private slots:
    void onBtnPlayClicked();
    void pnBtnStopClicked();
    void onBTnPauseClicked();
    void onBtnResumeClicked();
    void onSpinTimeChanged(int );
    void onSpinVolumeChanged(int);

private:
    void paintEvent(QPaintEvent *);

public:
    QLabel* getID();
    QLabel* getState();
    QPushButton* getPlayBtn();
    QPushButton* getStopBtn();
    QPushButton* getPauseBtn();
    QPushButton* getResumeBtn();
    QSpinBox* getTimeSpin();
    QSpinBox* getVolumeSpin();
    QLabel* getDuration();

signals:
    void sigBtnPlayClicked(int, int play_type);
    void sigBtnStopClicked(int);
    void sigBtnPauseClicked(int);
    void sigBtnResumeClicked(int);
    void sigSpinTimeChanged(int, int);
    void sigSpinVolumeChanged(int, int);

private:
    Ui::AudioMixItem *ui;
    QButtonGroup *m_group_button = nullptr;
};

#endif // AUDIOMIXITEM_H
