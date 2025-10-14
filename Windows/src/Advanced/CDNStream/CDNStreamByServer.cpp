#include "CDNStreamByServer.h"
#include "ui_CDNStreamByServer.h"

#include "bytertc_room.h"
#include "bytertc_engine.h"

#include <QMessageBox>
#include <QDebug>
#include <QColorDialog>

#include "Utils.h"
#include "Config.h"
#include "Resources.h"
#include "md5.h"

#include <sstream>

/**
* 功能名称： VolcEngineRTC 推流到CDN
* 功能简单描述：对于一个音视频通话，你可以将其中的多路音视频流合为一路，并将合并得到的音视频流推送到指定的推流地址（通常是 CDN 地址）
* 参考文档：https://www.volcengine.com/docs/6348/69817
*
* 此功能涉及的API及回调：
*     createRTCEngine 创建引擎
*     destroyRTCEngine 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*
*     startPushMixedStreamToCDN 开始合流转推
*     updatePushMixedStreamToCDN 更新合流转推参数
*     stopPushStreamToCDN 停止合流转推
*
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*     onMixingEvent 合流转推事件

*
* Demo实现时的逻辑
*    本Demo演示功能：合流转推，
*       当房间内只有1个人时，推向CDN的流只有一路，为了展示背景色，Demo设置了流长度为0.8，宽度为0.8
*       当房间内有2个人时，推向CDN的流是横向一排2路路流，第1路流宽度为0.4，高度为0.8，第2路流宽度为0.4，高度为0.8
*       当房间内有3个或4个人时， 推向CDN的流是4宫格流，宽度和高度分别为：0.4,0.4
*       房间内最多展示4路流
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/

CDNStreamByServer::CDNStreamByServer(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CDNStreamByServer)
{
    ui->setupUi(this);
    initRTCVideo();
    initConnects();
    initData();
    updateBtns(true, false, false);
}

CDNStreamByServer::~CDNStreamByServer()
{
    cleanRTCVideo();
    delete ui;

}

void CDNStreamByServer::initRTCVideo()
{

    //isSupportClientPushStream
    //return false: 告诉SDK，使用服务端合流方式，即由RTCSDK推到CDN
    //return true:  告诉SDK，使用业务层转推RTMP能力，需要业务层具备转推到CDN的能力
    // 本功能展示的是 如何使用RTCSDK 服务器合流，业务层不支持转推CDN，因此需要return false;


    m_handler.reset(new ByteRTCEventHandler());
    m_handler->setIsSupportClientPushStream(false); //本Demo使用RTC服务器推流，因此isSupportClientPushStream返回false
    connect(m_handler.get(), &ByteRTCEventHandler::sigMixingEvent, this, &CDNStreamByServer::onSigMixingEvent);
    bytertc::EngineConfig conf;
    conf.app_id = g_appid.c_str();
    conf.parameters = Utils::getParameters();
    m_video = bytertc::IRTCEngine::createRTCEngine(conf, m_handler.get());
    m_video->startAudioCapture();
    m_video->startVideoCapture();

    QStringList list = {"createRTCEngine", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);
}

void CDNStreamByServer::cleanRTCVideo()
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
        bytertc::IRTCEngine::destroyRTCEngine();

        m_video = nullptr;
        list = list + QStringList{ "stopAudioCapture", "stopVideoCapture", "destroyRTCEngine" };
        appendAPI(list);
    }
    
}

void CDNStreamByServer::initConnects()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &CDNStreamByServer::on_btnjoinroom_clicked);
	connect(ui->btn_start, &QPushButton::clicked, this, &CDNStreamByServer::on_start_clicked);
	connect(ui->btn_update, &QPushButton::clicked, this, &CDNStreamByServer::on_update_clicked);
	connect(ui->btn_stop, &QPushButton::clicked, this, &CDNStreamByServer::on_stop_clicked);
}

void CDNStreamByServer::on_btnjoinroom_clicked()
{

    std::lock_guard<std::recursive_mutex> locker(m_mutex);
    if (ui->btn_join->text() == QStringLiteral("进房")) {
		QString qstr_user_name = ui->lineEdit_uid->text();
		QString qstr_room = ui->lineEdit_room->text();
		QString qstr_error;

        m_localid = qstr_user_name.toStdString();
        m_roomid = qstr_room.toStdString();

		if (!Utils::checkIDValid(qstr_user_name, QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "uid error " + qstr_error, QMessageBox::Ok);
			box.exec();
			return;

		}

		if (!Utils::checkIDValid(qstr_room, QStringLiteral("房间号"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "roomid error " + qstr_error, QMessageBox::Ok);
			box.exec();
			return;
		}

        m_room = m_video->createRTCRoom(m_roomid.c_str());
		if (m_room == nullptr) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error, please check"), QMessageBox::Ok);
			box.exec();
			return;
		}

        bytertc::VideoCanvas cas;

        cas.view = (void*)ui->widget1->getWinId();
        ui->widget1->setUserInfo(m_roomid, m_localid);
        m_video->setLocalVideoCanvas(cas);

        m_roomHandler = createRoomHandler(m_roomid, m_localid);
        m_room->setRTCRoomEventHandler(m_roomHandler.get());
        std::string token = Utils::generateToken(m_roomid, m_localid);
		bytertc::UserInfo userinfo;
        userinfo.uid = m_localid.c_str();
		bytertc::RTCRoomConfig config;
        config.is_auto_publish_audio = true;
        config.is_auto_publish_video = true;
		config.is_auto_subscribe_audio = true;
		config.is_auto_subscribe_video = true;

		int ret = m_room->joinRoom(token.c_str(), userinfo, true, config);
		if (ret != 0) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error, please check"), QMessageBox::Ok);
			box.exec();
			return;
		}
        QStringList list = { "createRTCRoom", "setLocalVideoCanvas", "setRTCRoomEventHandler", "joinRoom" };
        appendAPI(list);

    }else {
        // 首先停止推流
        stop_push_cdn();

        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
        }

        initData();
        updateBtns(true, false, false);
        m_rendered_users.clear();
        m_unrender_users.clear();
        
        ui->btn_join->setText(QStringLiteral("进房"));
        QStringList list = { "leaveRoom", "destroy"};
        appendAPI(list);
    }
}

void CDNStreamByServer::resetRTCVideo()
{
    std::lock_guard<std::recursive_mutex> locker(m_mutex);
    QStringList list = { "stopAudioCapture", "stopVideoCapture", "destroyRTCEngine" };
	if (m_video) {
		if (m_room) {
			m_room->leaveRoom();
			m_room->destroy();
			m_room = nullptr;
            list = QStringList{ "leaveRoom", "destroy" };
		}
		m_video->stopAudioCapture();
		m_video->stopVideoCapture();
        bytertc::IRTCEngine::destroyRTCEngine();
        m_video = nullptr;
	}
    appendAPI(list);
}

void CDNStreamByServer::initData()
{
    m_widgets.push_back(ui->widget2);
    m_widgets.push_back(ui->widget3);
    m_widgets.push_back(ui->widget4);

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

    ui->lineEdit_room->setStyleSheet(APIDemo::str_qss_text);
    ui->lineEdit_uid->setStyleSheet(APIDemo::str_qss_text);
    ui->lineEdit_url->setStyleSheet(APIDemo::str_qss_text);
    ui->lineEdit_v_h->setStyleSheet(APIDemo::str_qss_text);
    ui->lineEdit_v_w->setStyleSheet(APIDemo::str_qss_text);
    ui->btn_join->setStyleSheet(APIDemo::str_qss_btn1);
    ui->btn_start->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_stop->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_update->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->comboBox_a_code1->setStyleSheet(APIDemo::str_qss_combobox);
    ui->comboBox_a_code2->setStyleSheet(APIDemo::str_qss_combobox);
    ui->comboBox_channel->setStyleSheet(APIDemo::str_qss_combobox);
    ui->comboBox_samplerate->setStyleSheet(APIDemo::str_qss_combobox);
    ui->comboBox_v_code->setStyleSheet(APIDemo::str_qss_combobox);
    ui->label_title->setStyleSheet(APIDemo::str_qss_label_ttile);

    ui->spinBox_a_bitrate->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->spinBox_v_bitrate->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->spinBox_v_fps->setStyleSheet(APIDemo::str_qss_spinbox);
    ui->label_t1->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t2->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t3->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t4->setStyleSheet(APIDemo::str_qss_label_ttile);
}

void CDNStreamByServer::updateBtns(bool btn1, bool btn2, bool btn3)
{
    ui->btn_start->setEnabled(btn1);
    ui->btn_stop->setEnabled(btn2);
    ui->btn_update->setEnabled(btn3);
}

UserWidget *CDNStreamByServer::getWidget()
{
    UserWidget *w = nullptr;
    if (m_widgets.size() > 0) {
        w = m_widgets.at(0);
        m_widgets.erase(m_widgets.begin());
    }
    return w;
}

bytertc::IMixedStreamConfig* CDNStreamByServer::getMixedStreamConfig()
{
    // audio
    bytertc::MixedStreamAudioConfig audioParam;
    audioParam.audio_codec = bytertc::MixedStreamAudioCodecType::kMixedStreamAudioCodecTypeAAC;
    audioParam.channels = ui->comboBox_channel->currentText().toInt();
    audioParam.bitrate = ui->spinBox_a_bitrate->value();
    audioParam.sample_rate = ui->comboBox_samplerate->currentText().toInt();

    audioParam.audio_profile = bytertc::MixedStreamAudioProfile::kMixedStreamAudioProfileLC;

    // video
    bytertc::MixedStreamVideoConfig videoParam;
    videoParam.bitrate = ui->spinBox_v_bitrate->value();
    videoParam.fps = ui->spinBox_v_fps->value();
    videoParam.gop = 2;
    videoParam.width = (ui->lineEdit_v_w->text()).toInt();
    videoParam.height = (ui->lineEdit_v_h->text()).toInt();
    videoParam.enable_bframe = false;
    if (ui->comboBox_v_code->currentText().contains("264")) {
        videoParam.video_codec = bytertc::kMixedStreamVideoCodecTypeH264; //本参数不支持过程中更新
    }
    else {
        videoParam.video_codec = bytertc::kMixedStreamVideoCodecTypeByteVC1;
    }


    // layout
    bytertc::MixedStreamLayoutRegionConfig* layouts = new bytertc::MixedStreamLayoutRegionConfig[m_rendered_users.size()];
    int i = 0;
    std::map<std::string, UserWidget*>::iterator ite;

    for (ite = m_rendered_users.begin(); ite != m_rendered_users.end(); ite++) {
        bytertc::MixedStreamLayoutRegionConfig lay;
        lay.user_id = ite->first.c_str();
        lay.room_id = m_roomid.c_str();

        lay.location_x = (i % 2) * 0.5 * videoParam.width; //确定每个流的位置
        lay.location_y = (i / 2) * 0.5 *  videoParam.height;

        lay.width = 0.5 * videoParam.width;
        lay.height = 0.5* videoParam.height;

        if (ite->first == m_localid) {
            lay.is_local_user = true;
        }
        else {
            lay.is_local_user = false;
        }

        lay.alpha = 1.0f;
        lay.z_order = 0;

        lay.render_mode = bytertc::MixedStreamRenderMode::kMixedStreamRenderModeHidden;
        lay.stream_type = bytertc::MixedStreamVideoType::kMixedStreamVideoTypeMain;
        lay.media_type = bytertc::MixedStreamMediaType::kMixedStreamMediaTypeAudioAndVideo;
        lay.apply_spatial_audio = false;
        layouts[i++] = lay;
    }

    std::string url = ui->lineEdit_url->text().toStdString();

    bytertc::IMixedStreamConfig* mixed_stream_param = bytertc::IMixedStreamConfig::createMixedStreamConfig();
    mixed_stream_param->setAudioConfig(audioParam);
    mixed_stream_param->setVideoConfig(videoParam);
    mixed_stream_param->setLayoutConfig(layouts, m_rendered_users.size());
    mixed_stream_param->setRoomID(m_roomid.c_str());
    mixed_stream_param->setUserID(m_localid.c_str());

    delete[]layouts;
    return mixed_stream_param;

    QStringList list = {"setAudioConfig", "setVideoConfig", "setLayoutConfig", "setExpectedMixingType", "setPushURL", "setRoomID", "setUserID", "setClientMixConfig"};
    appendAPI(list);
}

std::unique_ptr<ByteRTCRoomHandler> CDNStreamByServer::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &CDNStreamByServer::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStreamVideo, this, &CDNStreamByServer::onSigUserPublishStreamVideo);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStreamAudio, this, &CDNStreamByServer::onSigUserPublishStreamAudio);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &CDNStreamByServer::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &CDNStreamByServer::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigLeaveRoom, this, &CDNStreamByServer::onSigLeaveRoom);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
    });
    return roomH;
}

void CDNStreamByServer::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    std::stringstream log_str;
    log_str << std::string("onRoomStateChanged,roomid:")
        << roomid
        << ",uid:" << uid
        << ",state:" << std::to_string(state)
        << ",extra:" << extra_info;
    appendCallback(QString::fromStdString(log_str.str()));
    if (state == 0) {
        ui->btn_join->setText(QStringLiteral("离房"));
    }

    m_rendered_users[uid] = ui->widget1;
}

void CDNStreamByServer::onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamVideo")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);
    appendCallback(log_str);

    if (m_rendered_users.count(uid) > 0) {
        return; //已经渲染了
    } else {
        UserWidget *w = getWidget();
        if (w == nullptr) {//已经渲染满了
            m_unrender_users[uid] = nullptr; //存起来
        } else { //渲染该用户

            bytertc::RemoteStreamKey key;
            bytertc::VideoCanvas cas;
            key.stream_index = bytertc::kStreamIndexMain;
            key.room_id = roomid.c_str();
            key.user_id = uid.c_str();
            cas.view = nullptr;
            m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);

            cas.view = (void*)w->getWinId();
            m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
            m_rendered_users[uid] = w;
            w->setUserInfo(roomid, uid);

            appendAPI("setRemoteVideoCanvas");
        }
    }

}

void CDNStreamByServer::onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamAudio")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);
    appendCallback(log_str);

    if (m_rendered_users.count(uid) > 0) { //正在渲染的用户离开了
        //停止渲染原来用户
        bytertc::VideoCanvas cas;
        bytertc::RemoteStreamKey key;

        key.stream_index = bytertc::kStreamIndexMain;
        key.room_id = roomid.c_str();
        key.user_id = uid.c_str();
        cas.view = nullptr;
        m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
        m_rendered_users[uid]->setUserInfo("", "");
        m_rendered_users[uid]->update();
        m_widgets.push_back(m_rendered_users[uid]);
        m_rendered_users.erase(uid);

        //找新用户
        if (m_unrender_users.size() > 0) { //有新用户
            std::string new_id = m_unrender_users.begin()->first;
            UserWidget *w = getWidget();
            if (w) {

                key.room_id = roomid.c_str();
                key.user_id = new_id.c_str();
                cas.view = (void*)w->getWinId();
                m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
                m_unrender_users.erase(new_id);
            }
        }
        appendAPI("setRemoteVideoCanvas");

    } else {
        if (m_unrender_users.count(uid) > 0) { //未渲染的用户离开了
            m_unrender_users.erase(uid);
        }
    }
}

void CDNStreamByServer::onSigMixingEvent(ByteRTCEventHandler::MixedStreamTaskInfo info, bytertc::MixedStreamTaskEvent event, bytertc::MixedStreamTaskErrorCode error_code)
{
    qDebug() << Q_FUNC_INFO << QString::fromStdString(info.task_id) << info.push_target_type << event << error_code;
    QString str = "onMixedStreamEvent, event:" + QString::number(event) + ",taskid:" + QString::fromStdString(info.task_id)
                  + ",error:" + QString::number(error_code) + ",type:" + QString::number(info.push_target_type);
    appendCallback(str);
}

void CDNStreamByServer::onSigUserJoined(ByteRTCRoomHandler::UserInfo info)
{
    QString str = "onUserJoined, uid:" + QString::fromStdString(info.uid) + ",roomid:" + QString::fromStdString(info.roomid);
    appendCallback(str);
}

void CDNStreamByServer::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, uid:" + QString::fromStdString(uid) + ",roomid:" + QString::fromStdString(roomid);
    appendCallback(str);
}

void CDNStreamByServer::onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats)
{
    QString str = "onLeaveRoom, uid:" + QString::fromStdString(uid) + ",roomid:" + QString::fromStdString(roomid);
    appendCallback(str);
}

// 获得最终要推流的地址
// 如果用户不指定URL（文本框设为空），那就推流到默认地址
// 如果用户指定URL，那就推流到用户指定的URL
std::string CDNStreamByServer::get_final_url(const std::string& surl, const std::string& taskId, const std::string& roomId) {
    if (surl.empty()) {
        std::time_t timeStamp = std::time(nullptr);
        int expire = timeStamp + 7200;
        std::string path = "/rtc_test/pushcdn" + (ui->lineEdit_room->text()).toStdString() + taskId;
        std::string authKey = "Uq8e962ghCCY2pBUB9Me2Fwy";
        std::string keyStr = path + authKey + std::to_string(expire);
        std::string sign = md5::calculate(keyStr);
        return "rtmp://fcdn-test-hl.uplive.ixigua.com/rtc_test/pushcdn" + roomId + taskId + "?sign=" + sign + "&expire=" + std::to_string(expire);
    } else {
        return surl;
    }
}

// 停止cdn推流
void CDNStreamByServer::stop_push_cdn() {
    std::lock_guard<std::recursive_mutex> locker(m_mutex);
    if (m_video == nullptr) return;

    int ret = m_video->stopClientMixedStream(m_task.c_str());
    if (ret != 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("stopPushStreamToCDN error，Error code: " + QString::number(ret)), QMessageBox::Ok);
        box.exec();
        return;
    }
    updateBtns(true, false, false);
    ui->comboBox_v_code->setEnabled(true);
    appendAPI("stopPushStreamToCDN");
}

//开始cdn推流
void CDNStreamByServer::on_start_clicked()
{
    m_task = "task1";

    // 如果用户不指定URL，程序不会报错，而是会自动计算一个合法的URL。参见get_final_url()方法
    /*
    if (ui->lineEdit_url->text().isEmpty()) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("url is empty"), QMessageBox::Ok);
        box.exec();
        return;
    }
    */

    std::string surl = ui->lineEdit_url->text().toStdString();
    std::lock_guard<std::recursive_mutex> locker(m_mutex);
    if (m_video == nullptr) return;

    std::string final_url = get_final_url(surl, m_task, m_roomid);
    ui->lineEdit_url->setText(QString::fromStdString(final_url));

    bytertc::IMixedStreamConfig* mixed_stream_param = getMixedStreamConfig();
    bytertc::MixedStreamPushTargetConfig cf;
    cf.push_cdn_url = final_url.c_str();
    appendAPI(("The URL of the CDN stream: " + final_url).c_str());

    int ret = m_video->startPushMixedStream(m_task.c_str(), cf, mixed_stream_param);

    if (ret != 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("startPushMixedStreamToCDN error. Error code: " + QString::number(ret)), QMessageBox::Ok);
        box.exec();
        return;
    }

    appendAPI("startPushMixedStreamToCDN");
    updateBtns(false, true, true);
    ui->comboBox_v_code->setEnabled(false);
}

void CDNStreamByServer::on_update_clicked()
{
    m_task = "task1";

    std::lock_guard<std::recursive_mutex> locker(m_mutex);
    if (m_video == nullptr) return;
    std::string surl = ui->lineEdit_url->text().toStdString();
    std::string final_url = get_final_url(surl, m_task, m_roomid);
    ui->lineEdit_url->setText(QString::fromStdString(final_url));

    bytertc::MixedStreamPushTargetConfig cf;
    cf.push_cdn_url = final_url.c_str();

    bytertc::IMixedStreamConfig* config = getMixedStreamConfig();
    int ret = m_video->updatePushMixedStream(m_task.c_str(), cf, config);
    if (ret != 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("updatePushMixedStreamToCDN error. Error code: " + QString::number(ret)), QMessageBox::Ok);
        box.exec();
        return;
    }
    appendAPI("updatePushMixedStreamToCDN");
}

void CDNStreamByServer::on_stop_clicked()
{
    stop_push_cdn();
}
