#include "AudioMixingMedia.h"
#include "ui_AudioMixingMedia.h"

#include "bytertc_video.h"
#include "bytertc_room.h"
#include "rtc/bytertc_media_player.h"
#include "ByteRTCEventHandler.h"
#include "Config.h"
#include "Utils.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include <sstream>
#include <QTimer>

/**
* 功能名称： VolcEngineRTC 音乐混音
* 功能简单描述：如果需要在通话过程中播放音效或音乐文件等，而且让房间内的其他成员也听到声音，需要使用混音功能。混音功能可以将麦克风采集的音频数据与音频文件、PCM 音频数据等合并为一路音频流后，发布到房间内
* 参考文档：https://www.volcengine.com/docs/6348/70141
*
* 此功能涉及的API及回调：
*     createRTCVideo 创建引擎
*     destroyRTCVideo 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*     getMediaPlayer 获取音乐播放功能实例
*
*     IMediaPlayer API:
*     setEventHandler 设置回调句柄
*     open 打开音乐文件
*     getTotalDuration  获取音乐文件时长
*     getAudioTrackCount  获取当前音乐文件的音轨数
*     getVolume  setVolume 获取/设置播放音量
*     pause  resume stop 暂停 恢复 停止
*     setAudioPitch 变调
*     setPosition getPosition 设置/获取播放位置
*     setAudioDualMonoMode selectAudioTrack 设置声道模式
*     pushExternalAudioFrame 推送PCM数据
*     openWithCustomSource 打开PCM文件
*      
*
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*     onMediaPlayerStateChanged 播放状态改变时回调
*     onMediaPlayerStateChanged 播放进度周期性回调
*
*
*
*
*
* Demo实现时的逻辑
*    本Demo演示功能：音乐混音功能，仅展示播放音乐和播放PCM两个实例；
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/


const int id_player_audio = 0; //播放非PCM文件
const int id_player_pcm = 1;   //播放PCM文件

AudioMixingMedia::AudioMixingMedia(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::AudioMixingMedia)
{
    ui->setupUi(this);
    initConnections();
    initRTCVideo();
    initFile();
}

AudioMixingMedia::~AudioMixingMedia()
{
    cleanRTCVideo();
    cleanFile();
    delete ui;
}
void AudioMixingMedia::initConnections()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &AudioMixingMedia::onBtnJoinClicked);

    connect(ui->btn_browser, &QPushButton::clicked, this, &AudioMixingMedia::onBtnBrowserClicked);
    connect(ui->btn_play, &QPushButton::clicked, this, &AudioMixingMedia::onBtnPlayClicked);
    connect(ui->btn_pause, &QPushButton::clicked, this, &AudioMixingMedia::onBtnPauseClicked);
    connect(ui->btn_resume, &QPushButton::clicked, this, &AudioMixingMedia::onBtnResumeClicked);
    connect(ui->btn_stop, &QPushButton::clicked, this, &AudioMixingMedia::onBtnStopClicked);

    connect(ui->btn_setTrack, &QPushButton::clicked, this, &AudioMixingMedia::onBtnSetTrackClicked);
    connect(ui->btn_getTime, &QPushButton::clicked, this, &AudioMixingMedia::onBtnGetTimeClicked);
    connect(ui->comboBox_mode, &QComboBox::currentTextChanged, this, &AudioMixingMedia::onComboModeChanged);

    connect(ui->spinBox_pitch, SIGNAL(valueChanged(int)), this, SLOT(onSpinPitchValueChanged(int)));
    connect(ui->spinBox_pos, SIGNAL(valueChanged(int)), this, SLOT(onSpinPostionValueChanged(int)));
    connect(ui->spinBox_speed, SIGNAL(valueChanged(int)), this, SLOT(onSpinSpeedChanged(int)));
    connect(ui->spinBox_volume, SIGNAL(valueChanged(int)), this, SLOT(onSpinVolueChanged(int)));

    connect(ui->btn_pcm_start, &QPushButton::clicked, this, &AudioMixingMedia::onBtnPcmStartClicked);
    connect(ui->btn_pcm_stop, &QPushButton::clicked, this, &AudioMixingMedia::onBtnPcmStopClicked);
    connect(ui->spinBox_pcm_volume, SIGNAL(valueChanged(int)), this, SLOT(onSpinPcmVolumeChanged(int)));

    connect(&m_timer, &QTimer::timeout, this, &AudioMixingMedia::onPushDataTimer);
}
void AudioMixingMedia::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    connect(m_handler.get(), &ByteRTCEventHandler::sigMediaPlayerPlayingProgress, this, &AudioMixingMedia::onSigMediaPlayerPlayingProgress);
    connect(m_handler.get(), &ByteRTCEventHandler::sigMediaPlayerStateChanged, this, &AudioMixingMedia::onSigMediaPlayerStateChanged);

    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
    m_video->startAudioCapture();
    m_video->startVideoCapture();

    bytertc::IMediaPlayer *player_audio = nullptr, *player_pcm = nullptr;

    player_audio = m_video->getMediaPlayer(id_player_audio);
    player_pcm =  m_video->getMediaPlayer(id_player_pcm);

    if (player_audio == nullptr || player_pcm == nullptr) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("getMediaPlayer return nullptr"), QMessageBox::Ok);
        box.exec();
        return;
    }

    m_infos[id_player_audio] = player_audio;
    m_infos[id_player_pcm] = player_pcm;
    m_infos[id_player_audio]->setEventHandler(m_handler.get());
    m_infos[id_player_pcm]->setEventHandler(m_handler.get());

    QStringList list = {"createRTCVideo", "startAudioCapture", "startVideoCapture", "getMediaPlayer", "setEventHandler"};
    ui->widget_log->appendAPI(list);
}

void AudioMixingMedia::initFile() {
    
    QString name = QApplication::applicationDirPath() + "/Resources/audio/16k-mono-speech_fft_32s.pcm";
    m_pcm_file = new QFile(name);
    bool ret = m_pcm_file->exists() && m_pcm_file->open(QIODevice::ReadOnly);
    if (!ret) {
        cleanFile();
    }
}

void AudioMixingMedia::cleanFile() {
    if (m_pcm_file) {
        m_pcm_file->close();
        delete m_pcm_file;
        m_pcm_file = nullptr;
    }
}
void AudioMixingMedia::cleanRTCVideo()
{
    QStringList list;
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
            list = QStringList{"leaveRoom", "setRTCRoomEventHandler", "destroy"};
        }
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
        list = list + QStringList{"stopAudioCapture", "stopVideoCapture", "destroyRTCVideo"};
        ui->widget_log->appendAPI(list);
    }

    
}

std::unique_ptr<ByteRTCRoomHandler> AudioMixingMedia::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &AudioMixingMedia::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigLeaveRoom, this, &AudioMixingMedia::onSigLeaveRoom);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &AudioMixingMedia::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &AudioMixingMedia::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &AudioMixingMedia::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &AudioMixingMedia::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });

    return roomH;
}

void AudioMixingMedia::onBtnJoinClicked()
{
    std::string str_room = ui->lineEdit_room->text().toStdString();
    std::string str_uid = ui->lineEdit_uid->text().toStdString();
    std::string str_token;
    QString qstr_error;
    if (m_video == nullptr) {
        qWarning() << Q_FUNC_INFO << "m_video = nullptr";
        return;
    }

    if (ui->btn_join->text() == QStringLiteral("进房")) {
        if (!Utils::checkIDValid(QString::fromStdString(str_uid), QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), qstr_error, QMessageBox::Ok);
            box.exec();
            return;

        }

        if (!Utils::checkIDValid(QString::fromStdString(str_room), QStringLiteral("房间号"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room = m_video->createRTCRoom(str_room.c_str());
        if (m_room == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room_handler = createRoomHandler(str_room, str_uid);
        m_room->setRTCRoomEventHandler(m_room_handler.get());

        bytertc::VideoCanvas cavs;
        cavs.view = (void*)ui->widget->getWinId();
        cavs.render_mode = bytertc::kRenderModeHidden;
        m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cavs);
        ui->widget->setUserInfo(str_room, str_uid);

        bytertc::UserInfo info;
        bytertc::RTCRoomConfig config;

        info.uid = str_uid.c_str();
        config.is_auto_publish = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;

        str_token = Utils::generateToken(str_room, str_uid);
        int ret = m_room->joinRoom(str_token.c_str(), info, config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }

        QStringList list = QStringList{"createRTCRoom", "setRTCRoomEventHandler", "setLocalVideoCanvas", "joinRoom"};
        ui->widget_log->appendAPI(list);
    } else { //离房
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
            ui->btn_join->setText(QStringLiteral("进房"));
            QStringList list = {"leaveRoom", "destroy"};
            ui->widget_log->appendAPI(list);
        }
    }
}

void AudioMixingMedia::onBtnBrowserClicked()
{
    if (m_video == nullptr) return;
    QString exe_path = QApplication::applicationDirPath() + "/Resources/audio";
    QFileDialog dlg(this, "open audio effect file", exe_path, "(*.mp3 *.mp4 *.aac *.m4a *.3gp *.wav *.ogg *.ts *.wma)");
    QString file_path;
    if (dlg.exec() == QDialog::Accepted) {
        QStringList list = dlg.selectedFiles();
        if (list.size() > 0) {
            file_path = list.first();
        }
        if (file_path.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "not select a file";
            return;
        }

        ui->lineEdit_url->setText(file_path);
    }
    else { //未选中任何一个文件
        return;
    }
}

void AudioMixingMedia::onBtnPlayClicked()
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    std::string url = ui->lineEdit_url->text().toStdString();
    if (url.empty()) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("play url is empty:"), QMessageBox::Ok);
        box.exec();
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    bytertc::MediaPlayerConfig config;
    config.auto_play = true; // auto_play=true时自动播放，无需再调用start接口， auto_play=false时，不自动播放，需要调用start接口
    config.callback_on_progress_interval = 500;
    config.play_count = 1;
    config.start_pos = 0;
    config.sync_progress_to_record_frame = true; //TODO 参数确认
    config.type = bytertc::kAudioMixingTypePlayoutAndPublish;
    int ret = player->open(url.c_str(), config);
    ui->widget_log->appendAPI("open");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("open error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onBtnPauseClicked()
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    int ret = player->pause();
    ui->widget_log->appendAPI("pause");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("pause error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onBtnResumeClicked()
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    int ret = player->resume();
    ui->widget_log->appendAPI("resume");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("resume error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onBtnStopClicked()
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    int ret = player->stop();
    ui->widget_log->appendAPI("stop");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("stop error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onSpinVolueChanged(int value)
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    int ret = player->setVolume(value, bytertc::AudioMixingType::kAudioMixingTypePlayoutAndPublish);
    ui->widget_log->appendAPI("setVolume");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setVolume error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onSpinPitchValueChanged(int value)
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    int ret = player->setAudioPitch(value);
    ui->widget_log->appendAPI("setAudioPitch");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setAudioPitch error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onSpinPostionValueChanged(int pos)
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    int ret = player->setPosition(pos);
    ui->widget_log->appendAPI("setPosition");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setPosition error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onComboModeChanged(const QString& text)
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    bytertc::AudioMixingDualMonoMode mode = getAudioDualMode();
    int ret = player->setAudioDualMonoMode(mode);
    ui->widget_log->appendAPI("setAudioDualMonoMode");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setAudioDualMonoMode error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onBtnSetTrackClicked()
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    int index = ui->spinBox_track->value();
    int ret = player->selectAudioTrack(index);
    ui->widget_log->appendAPI("selectAudioTrack");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("selectAudioTrack error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onSpinSpeedChanged(int)
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    int speed = ui->spinBox_speed->value();
    int ret = player->setPlaybackSpeed(speed);
    ui->widget_log->appendAPI("setPlaybackSpeed");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setPlaybackSpeed error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onBtnGetTimeClicked()
{
    if (m_infos.count(id_player_audio) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    bytertc::IMediaPlayer* player = m_infos[id_player_audio];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    

    int ret = player->getPosition();
    ui->widget_log->appendAPI("getPosition");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setPlaybackSpeed error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
    ui->label_time->setText(QString::number(ret));
}

void AudioMixingMedia::onBtnPcmStopClicked()
{
    if (m_infos.count(id_player_pcm) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_pcm];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    m_timer.stop();
    int ret = player->stop();
    ui->widget_log->appendAPI("stop");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("stop error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingMedia::onSpinPcmVolumeChanged(int volume)
{
    if (m_infos.count(id_player_pcm) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }
    bytertc::IMediaPlayer* player = m_infos[id_player_pcm];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    int ret = player->setVolume(volume, bytertc::kAudioMixingTypePlayoutAndPublish);
    ui->widget_log->appendAPI("setVolume");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setVolume error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}


void AudioMixingMedia::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info) {
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);
    ui->widget_log->appendCallback(log_str);

    if (state == 0) {
        ui->btn_join->setText(QStringLiteral("离房"));
        ui->widget->setUserInfo(roomid, uid);
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged:") + QString::number(state), QMessageBox::Ok);
        box.exec();

    }
}

void AudioMixingMedia::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType)
{
    QString str = "onUserPublishStream, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);

}

void AudioMixingMedia::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason)
{
    QString str = "onUserUnPublishStream, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);

}

void AudioMixingMedia::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int)
{
    QString str = "onUserJoined, roomid:" + QString::fromStdString(info.roomid)
             + ",uid:" + QString::fromStdString(info.uid);
    ui->widget_log->appendCallback(str);

}

void AudioMixingMedia::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);

}

void AudioMixingMedia::onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats)
{
    QString str = "onLeaveRoom, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);
    ui->btn_join->setText(QStringLiteral("进房"));

}

void AudioMixingMedia::onSigMediaPlayerStateChanged(int playerId, bytertc::PlayerState state, bytertc::PlayerError error)
{
    QString str = "onMediaPlayerStateChanged, id=" + QString::number(playerId)
                  + ",state=" + QString::number(state) + ",error=" + QString::number(error);
    ui->widget_log->appendCallback(str);

    if (state == bytertc::kPlayerStatePlaying) {
        int ret = 0;
        if (m_infos.count(playerId) > 0) {
            bytertc::IMediaPlayer *player = m_infos[playerId];
            if (playerId == id_player_audio) {
                ret = player->getTotalDuration();
                ui->label_duration->setText(QString::number(ret));
                ret = player->getAudioTrackCount();
                ui->label_track->setText(QString::number(ret));
                ret = player->getVolume(bytertc::kAudioMixingTypePlayoutAndPublish);
                ui->spinBox_volume->setValue(ret);
            } else {
                ret = player->getVolume(bytertc::kAudioMixingTypePlayoutAndPublish);
                ui->spinBox_pcm_volume->setValue(ret);
            }
        }
    }
}

void AudioMixingMedia::onSigMediaPlayerPlayingProgress(int playerId, int64_t progress)
{
    QString str = "onMediaPlayerPlayingProgress, id=" + QString::number(playerId)
                  + ",progress=" + QString::number(progress);
    ui->widget_log->appendCallback(str);

}

void AudioMixingMedia::onPushDataTimer()
{
    if (m_video == nullptr || m_infos[id_player_pcm] == nullptr) return;

    int size = 160 * 1 * 2; //每10ms的数据大小=采样数*声道数*每个采样占字节数， 该pcm文件是16000采样率，单声道，每个样本占2个字节
    if (m_first_push) {
        size = 20 * size; //建议第一次时传入200ms的缓冲数据，避免噪音
        m_first_push = false;
    }

    if (m_pcm_file) {
        QByteArray data = m_pcm_file->read(size);
        if (data.size() == 0) {
            qWarning() << Q_FUNC_INFO << "read error";
            onBtnPcmStopClicked();
            return;
        }
        bytertc::AudioFrameBuilder builder;
        builder.channel = bytertc::kAudioChannelMono;
        builder.sample_rate = bytertc::kAudioSampleRate16000;
        builder.data = (uint8_t*)data.data();
        builder.data_size = size;
        auto frame = bytertc::buildAudioFrame(builder);

        int ret = m_infos[id_player_pcm]->pushExternalAudioFrame(frame);
        if(ret < 0) {
            qWarning() << Q_FUNC_INFO << "pushExternalAudioFrame error, ret=" << ret;
            return;
        }
    }
}

bytertc::AudioMixingDualMonoMode AudioMixingMedia::getAudioDualMode()
{
    bytertc::AudioMixingDualMonoMode mode = bytertc::AudioMixingDualMonoMode::kAudioMixingDualMonoModeAuto;

    QString text = ui->comboBox_mode->currentText();
    if (text.contains("Auto")) {
        mode = bytertc::kAudioMixingDualMonoModeAuto;
    }
    else if (text.contains("Left")) {
        mode = bytertc::kAudioMixingDualMonoModeL;
    }
    else if (text.contains("Right")) {
        mode = bytertc::kAudioMixingDualMonoModeR;
    }
    else {
        mode = bytertc::kAudioMixingDualMonoModeMix;
    }
    return mode;
}

void AudioMixingMedia::onBtnPcmStartClicked()
{
    if (m_infos.count(id_player_pcm) == 0) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    bytertc::IMediaPlayer* player = m_infos[id_player_pcm];
    if (player == nullptr) {
        qWarning() << Q_FUNC_INFO << "IMediaPlayer is nullptr";
        return;
    }

    if (m_pcm_file == nullptr) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("PCM 文件打开失败"), QMessageBox::Ok);
        box.exec();
        return;
    }

    bytertc::MediaPlayerCustomSource source;
    source.mode = bytertc::kMediaPlayerCustomSourceModePush;
    source.provider = nullptr;
    source.type = bytertc::kMediaPlayerCustomSourceStreamTypeRaw;
    bytertc::MediaPlayerConfig config;
    config.auto_play = true; // auto_play=true时自动播放，无需再调用start接口， auto_play=false时，不自动播放，需要调用start接口
    config.callback_on_progress_interval = 1000;
    config.play_count = 1;
    config.start_pos = 0;
    config.sync_progress_to_record_frame = true;
    config.type = bytertc::kAudioMixingTypePlayoutAndPublish;

    int ret = player->openWithCustomSource(source, config);
    ui->widget_log->appendAPI("openWithCustomSource");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("openWithCustomSource error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }

    m_pcm_file->seek(0);
    m_timer.start(10);
}
