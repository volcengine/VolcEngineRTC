#include "SoundEffectsWidget.h"
#include "ui_SoundEffectsWidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>


#include "bytertc_room.h"
#include "bytertc_video.h"

#include "Config.h"
#include "Utils.h"
#include "ByteRTCEventHandler.h"
#include "Resources.h"


/**
* 功能名称： VolcEngineRTC 美声与音效
* 功能简单描述：该功能展示了混响、变声、降噪等功能
* 参考文档：https://www.volcengine.com/docs/6348/1178327
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
*     setRuntimeParameters 初始化Sami库
*
*     setVoiceReverbType 设置混响特效类型
*     setVoiceChangerType 设置变声特效类型
*     setLocalVoicePitch 开启本地语音变调功能
*     enableLocalVoiceReverb 开启本地音效混响效果
*     setLocalVoiceReverbParam 设置本地采集音频的混响效果
*     setAnsMode  设置通话中的音频降噪模式
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*

*
* Demo实现时的逻辑
*    本Demo演示功能：美声与音效，演示了各种声音处理特效，使用该功能前请咨询技术人员，其中Windows端变声需要申请付费账号，
*    申请好后将 sami_key 和 sami_token 填写在config.h中
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/

//变声特效
const QString str_VoiceChangerTypeOriginal = QStringLiteral("原声");
const QString str_VoiceChangerTypeGiant = QStringLiteral("巨人");
const QString str_VoiceChangerTypeChipmunk = QStringLiteral("黄粟鼠");
const QString str_VoiceChangerTypeMinionst = QStringLiteral("小黄人");
const QString str_VoiceChangerTypeVibrato = QStringLiteral("颤音");
const QString str_VoiceChangerTypeRobot = QStringLiteral("机器人");

//混响特效
const QString str_VoiceReverbTypeOriginal = QStringLiteral("原声");
const QString str_VoiceReverbTypeEcho = QStringLiteral("回声");
const QString str_VoiceReverbTypeConcert = QStringLiteral("演唱会");
const QString str_VoiceReverbTypeEthereal = QStringLiteral("空灵");
const QString str_VoiceReverbTypeKTV = QStringLiteral("KTV");
const QString str_VoiceReverbTypeStudio = QStringLiteral("录音棚");
const QString str_VoiceReverbTypeVirtualStereo = QStringLiteral("虚拟立体声");
const QString str_VoiceReverbTypeSpacious = QStringLiteral("空旷");
const QString str_VoiceReverbType3D = QStringLiteral("3D人声");



SoundEffectsWidget::SoundEffectsWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::SoundEffectsWidget)
{
    ui->setupUi(this);
    initUI();
    connect(ui->btn_joinroom, &QPushButton::clicked, this, &SoundEffectsWidget::onBtnJoinClicked);
    connect(ui->comboBox_hunxiang, &QComboBox::currentTextChanged, this, &SoundEffectsWidget::onComboxHXTextChanged);
    connect(ui->comboBox_biansheng, &QComboBox::currentTextChanged, this, &SoundEffectsWidget::onComboxBSTextChanged);
    connect(ui->horizontalSlider_biandiao, &QSlider::valueChanged, this, &SoundEffectsWidget::onSliderPitchValueChanged);
    connect(ui->btn_changeVoiceReverbPara, &QPushButton::clicked, this, &SoundEffectsWidget::onBtnChangeVoiceReverbParaClicked);
    connect(ui->comboBox_ans, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboxAnsIndexChanged(int)));
    initRTCVideo();
}

SoundEffectsWidget::~SoundEffectsWidget()
{
    cleanRTCVideo();
    delete ui;   
}

void SoundEffectsWidget::initRTCVideo()
{
    QStringList list = {"createRTCVideo"};
    m_handler = new ByteRTCEventHandler();
    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler, nullptr);

#ifdef  Q_OS_WINDOWS
    QJsonObject obj;
    QString sami_path = QApplication::applicationDirPath() + "/Resources/sami_effect";
    obj.insert("rtc.sami_app_key", QString::fromStdString(g_sami_key));
    obj.insert("rtc.sami_resource_path", sami_path);
    obj.insert("rtc.sami_token", QString::fromStdString(g_sami_token));

    QJsonDocument doc(obj);
    QString str = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    std::string str_sami = str.toStdString();
    int ret = m_video->setRuntimeParameters(str_sami.c_str());
    list.append("setRuntimeParameters");

#endif //  Q_OS_WINDOWS

    m_video->startAudioCapture();
    m_video->startVideoCapture();
    list = list + QStringList{"startAudioCapture", "startVideoCapture"};
    appendAPI(list);
}

void SoundEffectsWidget::cleanRTCVideo()
{
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
        }
        m_video->stopAudioCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
    }
    QStringList list = {"leaveRoom", "setRTCRoomEventHandler", "destroy", "stopAudioCapture", "destroyRTCVideo"};
    appendAPI(list);
}

void SoundEffectsWidget::initUI() {

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
    ui->btn_joinroom->setStyleSheet(APIDemo::str_qss_btn1);
    ui->lineEdit_room->setStyleSheet(APIDemo::str_qss_text);
    ui->lineEdit_uid->setStyleSheet(APIDemo::str_qss_text);
    ui->comboBox_ans->setStyleSheet(APIDemo::str_qss_combobox);
    ui->comboBox_biansheng->setStyleSheet(APIDemo::str_qss_combobox);
    ui->comboBox_hunxiang->setStyleSheet(APIDemo::str_qss_combobox);
    ui->btn_changeVoiceReverbPara->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_changeVoiceReverbPara->setFixedHeight(32);
    ui->label_title->setStyleSheet(APIDemo::str_qss_label_ttile);

    QStringList list = {str_VoiceChangerTypeOriginal,
                        str_VoiceChangerTypeGiant,
                        str_VoiceChangerTypeChipmunk,
                        str_VoiceChangerTypeMinionst,
                        str_VoiceChangerTypeVibrato,
                        str_VoiceChangerTypeRobot};
    ui->comboBox_biansheng->addItems(list);

    list.clear();
    list = QStringList{str_VoiceReverbTypeOriginal,
                       str_VoiceReverbTypeEcho,
                       str_VoiceReverbTypeConcert,
                       str_VoiceReverbTypeEthereal ,
                       str_VoiceReverbTypeKTV,
                       str_VoiceReverbTypeStudio,
                       str_VoiceReverbTypeVirtualStereo ,
                       str_VoiceReverbTypeSpacious,
                       str_VoiceReverbType3D};

    ui->comboBox_hunxiang->addItems(list);
    ui->spinBox_delay->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->spinBox_o_qiangdu->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->spinBox_qiangdu->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->spinBox_room->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->spinBox_tuowei->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->spinBox_zuni->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->label_t1->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t2->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t3->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t4->setStyleSheet(APIDemo::str_qss_label_ttile);

}

void SoundEffectsWidget::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info) {

    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid) 
        + ",uid:" + QString::fromStdString(uid) 
        + ",state:" + QString::number(state) 
        + ",extra:" + QString::fromStdString(extra_info);
    appendCallback(log_str);

    if (state == 0) {
        ui->btn_joinroom->setText(QStringLiteral("离房"));
        //ui->widget->setUserInfo(roomid, uid);
    } else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged:") + QString::number(state), QMessageBox::Ok);
        box.exec();
    }
}

void SoundEffectsWidget::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type)
{
    QString log_str = QString("onUserPublishStream,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(type);
    appendCallback(log_str);
}

void SoundEffectsWidget::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)
{
    QString log_str = QString("onUserUnPublishStream,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(type)
        + ",reason:" + QString::number(reason);
    appendCallback(log_str);
}


void SoundEffectsWidget::onBtnJoinClicked() {

    QStringList list;
    if (ui->btn_joinroom->text() == QStringLiteral("进房")) {
        std::string roomid, uid, token;
        QString qstr_error;
        roomid = ui->lineEdit_room->text().toStdString();
        uid = ui->lineEdit_uid->text().toStdString();


        if (!Utils::checkIDValid(QString::fromStdString(uid), QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "uid error" + qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        if (!Utils::checkIDValid(QString::fromStdString(roomid), QStringLiteral("房间号"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "roomid error " + qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room = m_video->createRTCRoom(roomid.c_str());
        if (m_room == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }

        auto roomH = createRoomHandler(roomid, uid);
        m_room->setRTCRoomEventHandler(roomH);

        bytertc::VideoCanvas cas;
        cas.view = (void*)ui->widget_user->getWinId();
        m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cas);
        ui->widget_user->setUserInfo(roomid, uid);

        token = Utils::generateToken(roomid, uid);
        bytertc::UserInfo info;
        bytertc::RTCRoomConfig config;
        info.uid = uid.c_str();
        config.is_auto_publish = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;
        config.room_profile_type = bytertc::kRoomProfileTypeCommunication;
        int ret = m_room->joinRoom(token.c_str(), info, config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        list = QStringList{"createRTCRoom", "setRTCRoomEventHandler", "setLocalVideoCanvas", "joinRoom"};
       
    }
    else {
        ui->widget_user->setUserInfo("", "");
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
        }
        ui->btn_joinroom->setText(QStringLiteral("进房"));
        list = QStringList{"leaveRoom", "destroy"};
    }
    appendAPI(list);
}

bytertc::VoiceReverbType getVoiceReverType(const QString &text) {
    bytertc::VoiceReverbType type = bytertc::kVoiceReverbTypeOriginal;
    if (text == str_VoiceReverbTypeOriginal) {
        type = bytertc::kVoiceReverbTypeOriginal;
    }
    else if (text == str_VoiceReverbTypeEcho) {
       type = bytertc::kVoiceReverbTypeEcho;
    }
    else if (text == str_VoiceReverbTypeConcert) {
       type = bytertc::kVoiceReverbTypeConcert;
    }
    else if (text == str_VoiceReverbTypeEthereal) {
       type = bytertc::kVoiceReverbTypeEthereal;
    }
    else if (text == str_VoiceReverbTypeKTV) {
       type = bytertc::kVoiceReverbTypeKTV;
    }
    else if (text == str_VoiceReverbTypeStudio) {
       type = bytertc::kVoiceReverbTypeStudio;
    }
    else if (text == str_VoiceReverbTypeVirtualStereo) {
       type = bytertc::kVoiceReverbTypeVirtualStereo;
    }
    else if (text == str_VoiceReverbTypeSpacious) {
       type = bytertc::kVoiceReverbTypeSpacious;
    }
    else if (text == str_VoiceReverbType3D) {
       type = bytertc::kVoiceReverbType3D;
    }

    return type;
}

bytertc::VoiceChangerType getVoiceChangerType(const QString &text) {
    bytertc::VoiceChangerType type;
    if (text == str_VoiceChangerTypeGiant) {
       type = bytertc::kVoiceChangerTypeGiant;
    } else if (text == str_VoiceChangerTypeChipmunk) {
       type = bytertc::kVoiceChangerTypeChipmunk;
    } else if (text == str_VoiceChangerTypeMinionst) {
       type = bytertc::kVoiceChangerTypeMinionst;
    } else if (text == str_VoiceChangerTypeVibrato) {
       type = bytertc::kVoiceChangerTypeVibrato;
    } else if (text == str_VoiceChangerTypeRobot) {
       type = bytertc::kVoiceChangerTypeRobot;
    } else {
       type = bytertc::kVoiceChangerTypeOriginal;
    }
    return type;
}

bytertc::VoiceEqualizationBandFrequency getBandFrequency(const QString &text){
    bytertc::VoiceEqualizationBandFrequency type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency31;
    if (text.contains("62Hz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency62;
    } else if (text.contains("125Hz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency125;
    } else if (text.contains("250Hz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency250;
    } else if (text.contains("500Hz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency500;
    }else if (text.contains("1kHz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency1k;
    }else if (text.contains("2kHz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency2k;
    }else if (text.contains("4kHz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency4k;
    }else if (text.contains("8kHz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency8k;
    }else if (text.contains("16kHz")) {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency16k;
    } else {
       type = bytertc::VoiceEqualizationBandFrequency::kVoiceEqualizationBandFrequency31;
    }

    return type;
}

void SoundEffectsWidget::onComboxHXTextChanged(const QString& text)
{
    if (m_video == nullptr) return;
    bytertc::VoiceReverbType type = getVoiceReverType(text);
    int ret = m_video->setVoiceReverbType(type);
    
    if (ret < 0) {
       QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"),
            QString("setVoiceReverbType error"), QMessageBox::Ok);
       return;
    }
    appendAPI("setVoiceReverbType");
}

void SoundEffectsWidget::onComboxBSTextChanged(const QString& text)
{
    
    if (m_video == nullptr) return;
    bytertc::VoiceChangerType type = getVoiceChangerType(text);
    int ret = m_video->setVoiceChangerType(type);
    if (ret < 0) {
       QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"),
            QString("setVoiceChangerType error"), QMessageBox::Ok);
       return;
    }
    appendAPI("setVoiceChangerType");
}

void SoundEffectsWidget::onSliderPitchValueChanged(int value)
{
    if (m_video == nullptr) return;
    ui->label_pitch->setText(QString::number(value));
    int ret = m_video->setLocalVoicePitch(value);
    if (ret < 0) {
       QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"),
            QString("setLocalVoicePitch error"), QMessageBox::Ok);
       return;
    }
    appendAPI("setLocalVoicePitch");
}

void SoundEffectsWidget::onBtnChangeVoiceReverbParaClicked()
{
    if (m_video == nullptr) return;
    bytertc::VoiceReverbConfig config;
    config.room_size = ui->spinBox_room->value();
    config.decay_time = ui->spinBox_tuowei->value();
    config.damping = ui->spinBox_zuni->value();
    config.wet_gain = ui->spinBox_qiangdu->value();
    config.dry_gain = ui->spinBox_o_qiangdu->value();
    config.pre_delay = ui->spinBox_delay->value();
    m_video->enableLocalVoiceReverb(true);
    int ret = m_video->setLocalVoiceReverbParam(config);
    if (ret < 0) {
       QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"),
            QString("setLocalVoiceReverbParam error"), QMessageBox::Ok);
       return;
    }
    appendAPI("setLocalVoiceReverbParam");
}

bytertc::AnsMode getAnsMode(int value) {
    bytertc::AnsMode mode = bytertc::kAnsModeDisable;
    switch (value) {
    case 1:
       break;
       mode = bytertc::kAnsModeLow;
       break;
    case 2:
       mode = bytertc::kAnsModeMedium;
       break;
    case 3:
       mode = bytertc::kAnsModeHigh;
       break;
    case 4:
       mode = bytertc::kAnsModeAutomatic;
       break;

    default:
       mode = bytertc::kAnsModeDisable;
       break;
    }

    return mode;
}

void SoundEffectsWidget::onComboxAnsIndexChanged(int value)
{
    if (m_video == nullptr) return;
    bytertc::AnsMode mode = getAnsMode(value);
    int ret = m_video->setAnsMode(mode);
    appendAPI("setAnsMode");
    if (ret < 0) {
       QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"),
            QString("setAnsMode error"), QMessageBox::Ok);
       return;
    }
}

ByteRTCRoomHandler* SoundEffectsWidget::createRoomHandler(std::string roomid, std::string uid)
{
    auto roomH = new ByteRTCRoomHandler(roomid, uid);
    connect(roomH, &ByteRTCRoomHandler::sigRoomStateChanged, this, &SoundEffectsWidget::onSigRoomStateChanged);
    connect(roomH, &ByteRTCRoomHandler::sigUserPublishStream, this, &SoundEffectsWidget::onSigUserPublishStream);
    connect(roomH, &ByteRTCRoomHandler::sigUserUnPublishStream, this, &SoundEffectsWidget::onSigUserUnPublishStream);
    connect(roomH, &ByteRTCRoomHandler::sigUserJoined, this, &SoundEffectsWidget::onSigUserJoined);
    connect(roomH, &ByteRTCRoomHandler::sigUserLeave, this, &SoundEffectsWidget::onSigUserLeave);

    return roomH;
}
void SoundEffectsWidget::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason reason) 
{
    QString str = "onUserLeave: roomid:" + QString::fromStdString(roomid) 
        + ",uid:" + QString::fromStdString(uid) + ",reason:" + QString::number(reason);
    appendCallback(str);
}

void SoundEffectsWidget::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int elapsed)
{
    QString str = "onUserJoined: roomid:" + QString::fromStdString(info.roomid)
        + ",uid:" + QString::fromStdString(info.uid) + ",elapsed:" + QString::number(elapsed);
    appendCallback(str);
}
