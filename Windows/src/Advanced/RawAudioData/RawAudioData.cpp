#include "RawAudioData.h"
#include "ui_RawAudioData.h"

#include "bytertc_room.h"
#include "bytertc_video.h"
#include "Config.h"
#include "Utils.h"
#include "UserWidget.h"
#include "Resources.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QApplication>
#include <QDateTime>

#include <sstream>



/**
* 功能名称： VolcEngineRTC 原始音频数据
* 功能简单描述：通过注册回调接口，获取原始的指定类型的音频数据
* 参考文档：https://www.volcengine.com/docs/6348/1178324
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
*
*     getAudioDeviceManager 获取音频设备
*     registerAudioFrameObserver  注册音频数据回调观察者
*     enableAudioFrameCallback  设置并开启指定的音频数据帧回调
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*     
*     onRecordAudioFrame 返回麦克风录制的音频数据
*     onPlaybackAudioFrame 返回订阅的所有远端用户混音后的音频数据
*     onRemoteUserAudioFrame 返回远端单个用户的音频数据
*     onMixedAudioFrame  返回本地麦克风录制和订阅的所有远端用户混音后的音频数据
*     onRecordScreenAudioFrame  返回本地屏幕录制的音频数据
*
* Demo实现时的逻辑
*    本Demo演示功能：获取原始音频数据的代码实现流程
*    IAudioFrameObserver 回调的数据无法修改后发送到远端
*    如果想在发送音频前进行处理且处理效果发送到远端，请使用 自定义音频处理 接口，参考文档：https://www.volcengine.com/docs/6348/80635
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/



RawAudioData::RawAudioData(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::RawAudioData)
{
    ui->setupUi(this);


    initUI();
    initConnections();
    initRTCVideo();
}

RawAudioData::~RawAudioData()
{
    cleanRTCVideo();
    delete ui;
}

void RawAudioData::initConnections()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &RawAudioData::onBtnJoinClicked);
    connect(ui->comboBox_device, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboDeviceIndexChanged(int)));
    connect(ui->checkBox_record, &QCheckBox::stateChanged, this, &RawAudioData::onCheckRecordChanged);
    connect(ui->checkBox_playback, &QCheckBox::stateChanged, this, &RawAudioData::onCheckPlaybackChanged);
    connect(ui->checkBox_mixed, &QCheckBox::stateChanged, this, &RawAudioData::onCheckMixedChanged);
    connect(ui->checkBox_remote, &QCheckBox::stateChanged, this, &RawAudioData::onCheckRemoteUserChanged);
}

void RawAudioData::initRTCVideo()
{
    int ret = 0;
    m_handler.reset(new ByteRTCEventHandler());
    connect(m_handler.get(), &ByteRTCEventHandler::sigAudioDeviceWarning, this, &RawAudioData::onSigAudioDeviceWarning);
    connect(m_handler.get(), &ByteRTCEventHandler::sigAudioDeviceStateChanged, this, &RawAudioData::onSigAudioDeviceStateChanged);
    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
    m_audio = m_video->getAudioDeviceManager();
    updateAudioCaptureList();

    m_observer = new RawAudioDataObserver();
    connect(m_observer, &RawAudioDataObserver::showCallbackLog, this, [this](QString str) {
        appendCallback(str);
        });
    ret = m_video->registerAudioFrameObserver(m_observer);
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("registerAudioFrameObserver error"), QMessageBox::Ok);
        box.exec();
        return;
    }

    QStringList list = {"createRTCVideo", "getAudioDeviceManager", "registerAudioFrameObserver", "enableAudioFrameCallback", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);
}

void RawAudioData::cleanRTCVideo()
{
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
        }
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        m_video->registerAudioFrameObserver(nullptr);
        bytertc::destroyRTCVideo();
        m_video = nullptr;
    }
    if (m_observer) {
        delete m_observer;
        m_observer = nullptr;
    }

    QStringList list = {"leaveRoom", "setRTCRoomEventHandler", "destroy", "stopAudioCapture", "stopVideoCapture", "registerAudioFrameObserver", "destroyRTCVideo"};
    appendAPI(list);
}

std::unique_ptr<ByteRTCRoomHandler> RawAudioData::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &RawAudioData::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigLeaveRoom, this, &RawAudioData::onSigLeaveRoom);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &RawAudioData::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &RawAudioData::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &RawAudioData::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &RawAudioData::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });

    return roomH;
}

void RawAudioData::updateAudioCaptureList()
{
    if (m_audio == nullptr) return;
    bytertc::IAudioDeviceCollection *collection = m_audio->enumerateAudioCaptureDevices();
    if (collection == nullptr) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("enumerateAudioCaptureDevices is error"), QMessageBox::Ok);
        box.exec();
        return;
    }

    int count = collection->getCount();
    int default_index = 0;

    ui->comboBox_device->blockSignals(true);
    ui->comboBox_device->clear();
    for (int i = 0; i < count; i++) {
        bytertc::AudioDeviceInfo info;
        collection->getDevice(i, &info);
        if (info.is_system_default) {
            default_index = i;
        }
        ui->comboBox_device->addItem(info.device_name, QVariant(info.device_id));
        qDebug() << Q_FUNC_INFO <<  "index:" << i << ",name:" << info.device_name << ",id:" << info.device_id
                 << ",test:" << ui->comboBox_device->itemData(i).toString();
    }
    collection->release();
    ui->comboBox_device->setCurrentIndex(default_index);
    ui->comboBox_device->blockSignals(false);

    appendAPI("enumerateAudioCaptureDevices");
}

void RawAudioData::initUI()
{
    QList<QWidget*> childWidgets = this->findChildren<QWidget*>();
    // 遍历子控件并设置样式表
    foreach(QWidget * childWidget, childWidgets) {
        QLabel* label = qobject_cast<QLabel*>(childWidget);
        if (label) {
            if (label->objectName() != "label_user_id") {
                label->setStyleSheet(APIDemo::str_qss_label);
            } else {
                label->setStyleSheet(APIDemo::str_qss_label_user_info);
            }
        }
        QLineEdit* edit = qobject_cast<QLineEdit*>(childWidget);
        if (edit) {
            edit->setStyleSheet(APIDemo::str_qss_text);
        }
    };

    ui->btn_join->setStyleSheet(APIDemo::str_qss_btn1);
    ui->lineEdit_room->setStyleSheet(APIDemo::str_qss_text);
    ui->lineEdit_uid->setStyleSheet(APIDemo::str_qss_text);
    ui->label_title->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->comboBox_device->setStyleSheet(APIDemo::str_qss_combobox);
    ui->label_t1->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t2->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->comboBox_device->setStyleSheet(APIDemo::str_qss_combobox);
    ui->checkBox_mixed->setStyleSheet(APIDemo::str_qss_checkbox);
    ui->checkBox_playback->setStyleSheet(APIDemo::str_qss_checkbox);
    ui->checkBox_record->setStyleSheet(APIDemo::str_qss_checkbox);
    ui->checkBox_remote->setStyleSheet(APIDemo::str_qss_checkbox);
}

void RawAudioData::onBtnJoinClicked()
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
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "uid error " + qstr_error, QMessageBox::Ok);
            box.exec();
            return;

        }

        if (!Utils::checkIDValid(QString::fromStdString(str_room), QStringLiteral("房间号"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "roomid error " + qstr_error, QMessageBox::Ok);
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

        m_video->startAudioCapture();
        m_video->startVideoCapture();

        bytertc::VideoCanvas cas;
        cas.view = ui->widget->getWinId();
        cas.background_color = 0;
        cas.render_mode = bytertc::kRenderModeHidden;
        m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cas);
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

        QStringList list = {"createRTCRoom", "setRTCRoomEventHandler", "joinRoom"};
        appendAPI(list);
    } else {
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
        }
        ui->btn_join->setText(QStringLiteral("进房"));
        QStringList list = {"leaveRoom", "destroy"};
        appendAPI(list);
    }
}

void RawAudioData::onComboDeviceIndexChanged(int index)
{
    if (m_audio == nullptr) return;
    std::string id = ui->comboBox_device->itemData(index).toString().toStdString();
    m_audio->followSystemCaptureDevice(false);
    m_audio->setAudioCaptureDevice(id.c_str());
    appendAPI("setAudioCaptureDevice,id:" + QString::fromStdString(id));
}

void RawAudioData::onCheckRecordChanged(int)
{
    if (m_video == nullptr) return;
    if (ui->checkBox_record->checkState() == Qt::Checked) {
        bytertc::AudioFormat format;
        format.channel = bytertc::kAudioChannelStereo;
        format.sample_rate = bytertc::kAudioSampleRate48000;
        format.samples_per_call = 480;
        int ret = m_video->enableAudioFrameCallback(bytertc::AudioFrameCallbackMethod::kRecord, format); //麦克风
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("enableAudioFrameCallback error:") + QString::number(ret), QMessageBox::Ok);
            box.exec();
        }
        appendAPI("enableAudioFrameCallback");
    } else {
        m_video->disableAudioFrameCallback(bytertc::AudioFrameCallbackMethod::kRecord);
        appendAPI("disableAudioFrameCallback");
    }
}

void RawAudioData::onCheckPlaybackChanged(int)
{
    if (m_video == nullptr) return;
    if (ui->checkBox_playback->checkState() == Qt::Checked) {
        bytertc::AudioFormat format;
        format.channel = bytertc::kAudioChannelStereo;
        format.sample_rate = bytertc::kAudioSampleRate48000;
        format.samples_per_call = 480;
        int ret = m_video->enableAudioFrameCallback(bytertc::AudioFrameCallbackMethod::kPlayback, format);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("enableAudioFrameCallback error:") + QString::number(ret), QMessageBox::Ok);
            box.exec();
        }
        appendAPI("enableAudioFrameCallback");
    } else {
        m_video->disableAudioFrameCallback(bytertc::AudioFrameCallbackMethod::kPlayback);
        appendAPI("disableAudioFrameCallback");
    }
}

void RawAudioData::onCheckMixedChanged(int)
{
    if (m_video == nullptr) return;
    if (ui->checkBox_mixed->checkState() == Qt::Checked) {
        bytertc::AudioFormat format;
        format.channel = bytertc::kAudioChannelStereo;
        format.sample_rate = bytertc::kAudioSampleRate48000;
        format.samples_per_call = 480;
        int ret = m_video->enableAudioFrameCallback(bytertc::AudioFrameCallbackMethod::kMixed, format); //麦克风
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("enableAudioFrameCallback error:") + QString::number(ret), QMessageBox::Ok);
            box.exec();
        }
        appendAPI("enableAudioFrameCallback");
    } else {
        m_video->disableAudioFrameCallback(bytertc::AudioFrameCallbackMethod::kMixed);
        appendAPI("disableAudioFrameCallback");
    }
}

void RawAudioData::onCheckRemoteUserChanged(int)
{
    if (m_video == nullptr) return;
    if (ui->checkBox_remote->checkState() == Qt::Checked) {
        bytertc::AudioFormat format;
        format.channel = bytertc::kAudioChannelAuto;
        format.sample_rate = bytertc::kAudioSampleRateAuto;

        int ret = m_video->enableAudioFrameCallback(bytertc::AudioFrameCallbackMethod::kRemoteUser, format); //麦克风
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("enableAudioFrameCallback error:") + QString::number(ret), QMessageBox::Ok);
            box.exec();
        }
        appendAPI("enableAudioFrameCallback");
    } else {
        m_video->disableAudioFrameCallback(bytertc::AudioFrameCallbackMethod::kRemoteUser);
        appendAPI("disableAudioFrameCallback");
    }
}


void RawAudioData::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);
    appendCallback(log_str);
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

void RawAudioData::onSigAudioDeviceWarning(std::string device_id, bytertc::RTCAudioDeviceType device_type, bytertc::MediaDeviceWarning device_warning)
{
    QString str = "onAudioDeviceWarning, deviceid:" + QString::fromStdString(device_id) + ",device_type:" + QString::number(device_type) + ",warning:" + QString::number(device_warning);
    appendCallback(str);
}

void RawAudioData::onSigAudioDeviceStateChanged(std::string device_id, bytertc::RTCAudioDeviceType device_type, bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error)
{
    QString str = "onAudioDeviceStateChanged, deviceid:" + QString::fromStdString(device_id) + ",device_type:" + QString::number(device_type) + ",state:" + QString::number(device_state) + ",error:" + QString::number(device_error);
    appendCallback(str);

    std::string cur_id = ui->comboBox_device->currentData().toString().toStdString();

    if (device_state == bytertc::kMediaDeviceStateRemoved || device_state == bytertc::kMediaDeviceStateAdded) {
        updateAudioCaptureList(); //设备被拔出 或 有新设备插入时，更新设备列表
    }
}

void RawAudioData::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType)
{
    QString str = "onUserPublishStream, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);

}

void RawAudioData::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason)
{
    QString str = "onUserUnPublishStream, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);

}

void RawAudioData::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int)
{
    QString str = "onUserJoined, roomid:" + QString::fromStdString(info.roomid)
             + ",uid:" + QString::fromStdString(info.uid);
    appendCallback(str);

}

void RawAudioData::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);

}

void RawAudioData::onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats)
{
    QString str = "onLeaveRoom, roomid:" + QString::fromStdString(roomid)
             + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);
    ui->btn_join->setText(QStringLiteral("进房"));

}

RawAudioDataObserver::RawAudioDataObserver() {
#ifdef WRITE_PCM
    m_file = new QFile(QApplication::applicationDirPath() + "/audio_" + QDateTime::currentDateTime().toString("yyyy_MM_dd-h-mm-ss") + ".pcm");
    m_file->open(QIODevice::WriteOnly);
#endif
}

RawAudioDataObserver::~RawAudioDataObserver() {
#ifdef WRITE_PCM
    if (m_file) {
        m_file->close();
        m_file->deleteLater();
        m_file = nullptr;
    }
#endif
}
void RawAudioDataObserver::onRecordAudioFrameOriginal(const bytertc::IAudioFrame& audio_frame)
{

}

void RawAudioDataObserver::onRecordAudioFrame(const bytertc::IAudioFrame& audio_frame) {

    //返回麦克风录制的音频数据,本端开启音频采集且注册音频回调 kAudioFrameCallbackRecord 类型后即可收到该回调
    // 回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃
    // 你可以使用采集的麦克风数据进行 音频录制，由于该数据是只读数据，因此无法修改，如果需要对音频数据进行自定义处理，请使用 registerAudioProcessor 接口
#ifdef WRITE_PCM
    if (!m_file) return;
    m_file->write((const char*)audio_frame.data(), audio_frame.dataSize());
#endif

    static long long num = 0;
    if (num % 100 == 0) {
        //该信号只用于界面中显示日志
        emit showCallbackLog("onRecordAudioFrame, channel=" + QString::number(audio_frame.channel()) + ",sample_rate=" + QString::number(audio_frame.sampleRate()));
    }
    num++;
}

void RawAudioDataObserver::onPlaybackAudioFrame(const bytertc::IAudioFrame& audio_frame) 
{
    // 返回订阅的所有远端用户混音后的音频数据。本端开启音频采集且注册音频回调 kAudioFrameCallbackPlayback 类型后即可收到该回调
    static long long num = 0;
    if (num % 100 == 0) {
        //该信号只用于界面中显示日志
        emit showCallbackLog("onPlaybackAudioFrame, channel=" + QString::number(audio_frame.channel()) + ",sample_rate=" + QString::number(audio_frame.sampleRate()));
    }
    num++;
}

void RawAudioDataObserver::onRemoteUserAudioFrame(const bytertc::RemoteStreamKey& stream_info, const bytertc::IAudioFrame& audio_frame) 
{
    // 返回远端单个用户的音频数据.本端开启音频采集且注册音频回调 kAudioFrameCallbackRemoteUser 类型后即可收到该回调
    static long long num = 0;
    if (num % 100 == 0) {
        //该信号只用于界面中显示日志
        emit showCallbackLog("onRemoteUserAudioFrame, channel=" + QString::number(audio_frame.channel()) + ",sample_rate=" + QString::number(audio_frame.sampleRate()));
    }
    num++;
}

void RawAudioDataObserver::onMixedAudioFrame(const bytertc::IAudioFrame& audio_frame) 
{
    //返回本地麦克风录制和订阅的所有远端用户混音后的音频数据。本端开启音频采集且注册音频回调 kAudioFrameCallbackMixed 类型后即可收到该回调
    static long long num = 0;
    if (num % 100 == 0) {
        //该信号只用于界面中显示日志
        emit showCallbackLog("onMixedAudioFrame, channel=" + QString::number(audio_frame.channel()) + ",sample_rate=" + QString::number(audio_frame.sampleRate()));
    }
    num++;
}

void RawAudioDataObserver::onRecordScreenAudioFrame(const bytertc::IAudioFrame& audio_frame) 
{
    //返回本地屏幕录制的音频数据.本端开启音频采集且注册音频回调 kAudioFrameCallbackRecordScreen 类型后即可收到该回调
    static long long num = 0;
    if (num % 100 == 0) {
        //该信号只用于界面中显示日志
        emit showCallbackLog("onRecordScreenAudioFrame, channel=" + QString::number(audio_frame.channel()) + ",sample_rate=" + QString::number(audio_frame.sampleRate()));
    }
    num++;
}

