#include "AudioMixingEffect.h"
#include "ui_AudioMixingEffect.h"

#include "bytertc_video.h"
#include "Config.h"
#include "Utils.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "AudioMixItem.h"

#include <sstream>

/**
* 功能名称： VolcEngineRTC 音效混音
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
*     getAudioEffectPlayer 获取音效播放功能实例
*
*     IAudioEffectPlayer API:
*     setEventHandler 设置回调句柄
*     preload 预加载音效
*     start 开始播放音效文件
*     stop 停止播放音效文件
*     stopAll 停止播放所有音效文件
*     pauseAll 暂停播放所有音效文件
*     resumeAll 恢复播放所有音效文件
*     getDuration 获取音效文件时长 setPosition 设置播放位置
*     getVolume 获取播放音量  setVolumeAll 设置所有音效的音量大小  setVolume调节指定音效的音量大小
* 
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
* 
*     onAudioEffectPlayerStateChanged 播放状态回调
*

*
* Demo实现时的逻辑
*    本Demo演示功能：音效混音功能，添加到列表：设置好地址的音效文件放在待播放队列中
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/


AudioMixingEffect::AudioMixingEffect(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::AudioMixingEffect)
{
    ui->setupUi(this);

    initConnections();
    initRTCVideo();
}

AudioMixingEffect::~AudioMixingEffect()
{
    cleanRTCVideo();
    delete ui;
}

void AudioMixingEffect::initConnections()
{
    
    connect(ui->btn_join, &QPushButton::clicked, this, &AudioMixingEffect::onBtnJoinClicked);
    connect(ui->btn_broswer, &QPushButton::clicked, this, &AudioMixingEffect::onBtnBrowserClicked);
    connect(ui->btn_add, &QPushButton::clicked, this, &AudioMixingEffect::onBtnAddClicked); //添加到播放列表中
    connect(ui->btnPauseAll, &QPushButton::clicked, this, &AudioMixingEffect::onBtnPuaseAllClicked); //
    connect(ui->btnResumeAll, &QPushButton::clicked, this, &AudioMixingEffect::onBtnResumeAllClicked); //
    connect(ui->btnStopAll, &QPushButton::clicked, this, &AudioMixingEffect::onBtnStopAllClicked); //
    connect(ui->spinBox_volume, SIGNAL(valueChanged(int)), this, SLOT(onSpinVolumeChanged(int)));
}

void AudioMixingEffect::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    connect(m_handler.get(), &ByteRTCEventHandler::sigAudioEffectPlayerStateChanged, this, &AudioMixingEffect::onSigAudioEffectPlayerStateChanged);
    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
    m_video->startAudioCapture();
    m_video->startVideoCapture();

    m_player = m_video->getAudioEffectPlayer();
    m_player->setEventHandler(m_handler.get());

    QStringList list = {"createRTCVideo", "startAudioCapture", "startVideoCapture", "getAudioEffectPlayer", "setEventHandler"};
    ui->widget_log->appendAPI(list);
}

void AudioMixingEffect::cleanRTCVideo()
{
    QStringList list ;
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
            list = QStringList{ "leaveRoom", "setRTCRoomEventHandler", "destroy" };
        }
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
    }

    list = list + QStringList{ "stopAudioCapture", "stopVideoCapture", "destroyRTCVideo" };
    ui->widget_log->appendAPI(list);
}

std::unique_ptr<ByteRTCRoomHandler> AudioMixingEffect::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &AudioMixingEffect::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigLeaveRoom, this, &AudioMixingEffect::onSigLeaveRoom);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &AudioMixingEffect::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &AudioMixingEffect::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &AudioMixingEffect::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &AudioMixingEffect::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });

    return roomH;
}

void AudioMixingEffect::onBtnJoinClicked() {
    std::string str_room = ui->lineEdit_roomid->text().toStdString();
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

        bytertc::VideoCanvas cavs;
        cavs.view = (void*)ui->widget->winId();
        cavs.render_mode = bytertc::kRenderModeHidden;

        m_room_handler = createRoomHandler(str_room, str_uid);
        m_room->setRTCRoomEventHandler(m_room_handler.get());

        bytertc::VideoCanvas cas;
        cas.view = (void*)ui->widget->getWinId();
        ui->widget->setUserInfo(str_room, str_uid);
        m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cas);

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

        QStringList list = {"createRTCRoom", "setRTCRoomEventHandler", "setLocalVideoCanvas", "joinRoom"};
        ui->widget_log->appendAPI(list);
    }
    else {
        if (m_room) {
            m_room->leaveRoom(); 
        }
        ui->widget_log->appendAPI("leaveRoom");
    }
}

void AudioMixingEffect::onBtnBrowserClicked() {

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

        ui->lineEdit->setText(file_path);
    }
    else { //未选中任何一个文件
        return;
    }
}

void AudioMixingEffect::onBtnAddClicked()
{
    
    if (ui->lineEdit->text().isEmpty()) {
        return;
    }

    addItem();
}

void AudioMixingEffect::addItem() {

    if (m_video == nullptr || m_player == nullptr) return;
    
    int size = m_infos.size();
    int new_id = size + 1;
    m_infos[new_id].path = ui->lineEdit->text().toStdString();
    
    AudioMixItem* item = new AudioMixItem(this);
    m_infos[new_id].widget = item;
    item->getID()->setText(QString::number(new_id));
    connect(item, &AudioMixItem::sigBtnPlayClicked, this, &AudioMixingEffect::onItemBtnStartClicked);
    connect(item, &AudioMixItem::sigBtnStopClicked, this, &AudioMixingEffect::onItemBtnStopClicked);
    connect(item, &AudioMixItem::sigBtnPauseClicked, this, &AudioMixingEffect::onItemBtnPauseClicked);
    connect(item, &AudioMixItem::sigBtnResumeClicked, this, &AudioMixingEffect::onItemBtnResumeClicked);
    connect(item, &AudioMixItem::sigSpinTimeChanged, this, &AudioMixingEffect::onItemSpinPosChanged);
    connect(item, &AudioMixItem::sigSpinVolumeChanged, this, &AudioMixingEffect::onItemSpinVolumeChanged);
    ui->verticalLayout_list->removeItem(ui->verticalSpacer);
    ui->verticalLayout_list->addWidget(item);
    ui->verticalLayout_list->addItem(ui->verticalSpacer);
}


void AudioMixingEffect::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info) {
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);
    ui->widget_log->appendCallback(log_str);
    m_roomid = roomid;

    if (state == 0) {
        ui->btn_join->setText(QStringLiteral("离房"));
        ui->widget->setUserInfo(roomid, uid);
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged:") + QString::number(state), QMessageBox::Ok);
        box.exec();

    }
}

void AudioMixingEffect::onBtnStopAllClicked()
{
    if (m_player == nullptr) return;
    int ret = m_player->stopAll();
    ui->widget_log->appendAPI("stopAll");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("stopAll error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingEffect::onBtnPuaseAllClicked()
{
    int ret = m_player->pauseAll();
    ui->widget_log->appendAPI("pauseAll");
    if (m_player == nullptr) return;
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("stopAll error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingEffect::onItemBtnStartClicked(int id, int type)
{
    if (m_player == nullptr) return;
    if (m_infos.count(id) == 0) return;

    bytertc::AudioEffectPlayerConfig config;
    config.pitch = 0;
    config.play_count = 1;
    config.start_pos = 0;
    config.type = static_cast<bytertc::AudioMixingType>(type);
    //注意：
    //1. 如果你需要经常播放同一个本地文件，可以使用preload 进行预加载，避免内存多次申请释放
    //2. 建议 start 后不要马上调用 getDuration getVolume 等 get 类接口， 内部 start 是异步执行，get 是同步执行，同时调用无法保证前后执行顺序
    //   应该在收到 start 对应的回调后再执行get接口
    int ret = m_player->start(id, m_infos[id].path.c_str(), config);
    ui->widget_log->appendAPI("start");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("start error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingEffect::onItemBtnPauseClicked(int id)
{
    if (m_player == nullptr) return;
    if (m_infos.count(id) == 0) return;
    int ret = m_player->pause(id);
    ui->widget_log->appendAPI("pause");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("pause error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingEffect::onItemBtnResumeClicked(int id)
{
    if (m_player == nullptr) return;
    if (m_infos.count(id) == 0) return;
    int ret = m_player->resume(id);
    ui->widget_log->appendAPI("resume");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("resume error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingEffect::onItemSpinVolumeChanged(int id, int volume)
{
    if (m_player == nullptr) return;
    if (m_infos.count(id) == 0) return;
    int ret = m_player->setVolume(id, volume);
    ui->widget_log->appendAPI("setVolume");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setVolume error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingEffect::onItemSpinPosChanged(int id, int pos)
{
    if (m_player == nullptr) return;
    if (m_infos.count(id) == 0) return;
    int ret = m_player->setPosition(id, pos);
    ui->widget_log->appendAPI("setPosition");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setPosition error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingEffect::onItemBtnStopClicked(int id)
{
    if (m_player == nullptr) return;
    if (m_infos.count(id) == 0) return;
    int ret = m_player->stop(id);
    ui->widget_log->appendAPI("stop");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("stop error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void AudioMixingEffect::onBtnResumeAllClicked()
{
    if (m_player == nullptr) return;
    int ret = m_player->resumeAll();
    ui->widget_log->appendAPI("resumeAll");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("resumeAll error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}


void AudioMixingEffect::onSigAudioEffectPlayerStateChanged(int effect_id, bytertc::PlayerState state, bytertc::PlayerError error) {

    std::stringstream stream;
    stream << "onAudioEffectPlayerStateChanged, id:" << effect_id << ",state:" << state << ",error:" << error;
    ui->widget_log->appendCallback(QString::fromStdString(stream.str()));

    if (m_infos.count(effect_id) > 0) {
        m_infos[effect_id].widget->getState()->setText("state:" + QString::number(state) + ",err:" + QString::number(error));
        if (state == bytertc::kPlayerStatePlaying) {
            int ret = m_player->getDuration(effect_id);
            ui->widget_log->appendAPI("getDuration");
            m_infos[effect_id].widget->getDuration()->setText(QString::number(ret));
            if (ret < 0) {
                QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("getDuration error:") + QString::number(ret), QMessageBox::Ok);
                box.exec();
            }

            ret = m_player->getVolume(effect_id);
            ui->widget_log->appendAPI("getVolume");
            m_infos[effect_id].widget->getVolumeSpin()->blockSignals(true);
            m_infos[effect_id].widget->getVolumeSpin()->setValue(ret);
            m_infos[effect_id].widget->getVolumeSpin()->blockSignals(false);
            if (ret < 0) {
                QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("getVolume error:") + QString::number(ret), QMessageBox::Ok);
                box.exec();
            }
        }

    }
}

void AudioMixingEffect::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType)
{
    QString str = "onUserPublishStream, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);
}

void AudioMixingEffect::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason)
{
    QString str = "onUserUnPublishStream, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);

}

void AudioMixingEffect::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int)
{
    QString str = "onUserJoined, roomid:" + QString::fromStdString(info.roomid)
             + ",uid:" + QString::fromStdString(info.uid);
    ui->widget_log->appendCallback(str);

}

void AudioMixingEffect::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);

}

void AudioMixingEffect::onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats)
{
    QString str = "onLeaveRoom, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);
    ui->btn_join->setText(QStringLiteral("进房"));

}

void AudioMixingEffect::onSpinVolumeChanged(int value)
{
    if (m_player == nullptr) return;
    int ret = m_player->setVolumeAll(value);
    ui->widget_log->appendAPI("setVolumeAll");
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("resumeAll error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
}
