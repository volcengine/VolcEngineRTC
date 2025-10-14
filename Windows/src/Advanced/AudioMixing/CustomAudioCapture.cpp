#include "CustomAudioCapture.h"
#include "ui_CustomAudioCapture.h"

#include "Config.h"
#include "Utils.h"
#include "Resources.h"

#include "bytertc_engine.h"
#include "bytertc_room.h"

#include <QMessageBox>
#include <QDebug>

const QString qstr_pcm_file_path = "/Resources/audio/16k-mono-speech_fft_32s.pcm";


CustomAudioCapture::CustomAudioCapture(QWidget* parent) :
	BaseWidget(parent),
	ui(new Ui::CustomAudioCapture)
{
	ui->setupUi(this);
	initConnections();
	initRTCVideo();
	initUI();
}

CustomAudioCapture::~CustomAudioCapture()
{
	cleanRTCVideo();
	delete ui;
}

void CustomAudioCapture::initConnections()
{
	connect(ui->btn_start, &QPushButton::clicked, this, &CustomAudioCapture::onBtnStartClicked);
	connect(ui->btn_stop, &QPushButton::clicked, this, &CustomAudioCapture::onBtnStopClicked);
	connect(ui->btn_join, &QPushButton::clicked, this, &CustomAudioCapture::onBtnJoinRoomClicked);
	connect(&m_timer, &QTimer::timeout, this, &CustomAudioCapture::onPushDataTimer);
}

void CustomAudioCapture::initRTCVideo()
{
	m_handler.reset(new ByteRTCEventHandler());
    bytertc::EngineConfig conf;
    conf.app_id = g_appid.c_str();
	conf.parameters = Utils::getParameters();
    m_video = bytertc::IRTCEngine::createRTCEngine(conf, m_handler.get());
	m_video->startVideoCapture();

    QStringList list = { "createRTCEngine", "startVideoCapture" };
	appendAPI(list);

}

void CustomAudioCapture::cleanRTCVideo()
{
	if (m_video) {
		if (m_room) {
			m_room->leaveRoom();
			m_room->setRTCRoomEventHandler(nullptr);
			m_room->destroy();
			m_room = nullptr;
		}

		m_video->stopVideoCapture();
		bytertc::IRTCEngine::destroyRTCEngine();
		m_video = nullptr;
	}
    QStringList list = { "leaveRoom", "setRTCRoomEventHandler", "destroy", "stopVideoCapture", "destroyRTCEngine" };
	appendAPI(list);

}

void CustomAudioCapture::initUI()
{
	QList<QWidget*> childWidgets = this->findChildren<QWidget*>();
	// 遍历子控件并设置样式表
	foreach(QWidget * childWidget, childWidgets) {
		QLabel* label = qobject_cast<QLabel*>(childWidget);
		if (label) {
			if (label->objectName() != "label_user_id") {
				label->setStyleSheet(APIDemo::str_qss_label);
			}
			else {
				label->setStyleSheet(APIDemo::str_qss_label_user_info);
			}
		}
		QLineEdit* edit = qobject_cast<QLineEdit*>(childWidget);
		if (edit) {
			edit->setStyleSheet(APIDemo::str_qss_text);
		}
	};
    ui->btn_join->setStyleSheet(APIDemo::str_qss_btn1);
    ui->btn_start->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_stop->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->comboBox->setStyleSheet(APIDemo::str_qss_combobox);

}

ByteRTCRoomHandler* CustomAudioCapture::createRoomHandler(std::string roomid, std::string uid)
{
	auto roomH = new ByteRTCRoomHandler(roomid, uid);
    connect(roomH, &ByteRTCRoomHandler::sigRoomStateChanged, this, &CustomAudioCapture::onSigRoomStateChanged);
    connect(roomH, &ByteRTCRoomHandler::sigUserPublishStreamVideo, this, &CustomAudioCapture::onSigUserPublishStreamVideo);
    connect(roomH, &ByteRTCRoomHandler::sigUserPublishStreamAudio, this, &CustomAudioCapture::onSigUserPublishStreamAudio);

    return roomH;
}

void CustomAudioCapture::cleanFile()
{
    if (m_pcm_file) {
        m_pcm_file->close();
        delete m_pcm_file;
        m_pcm_file = nullptr;
    }
}

void CustomAudioCapture::onBtnStartClicked()
{
	if (m_pcm_file == nullptr) {
        QString path = QApplication::applicationDirPath() + qstr_pcm_file_path;
        m_pcm_file = new QFile(path);
        if (!m_pcm_file->open(QIODevice::ReadOnly)) {
            qWarning() << Q_FUNC_INFO << "open pcm file error";
            cleanFile();
            return;
        }
	}

    m_timer.start(10);
    m_pcm_file->seek(0);
}

void CustomAudioCapture::onBtnStopClicked()
{
    m_timer.stop();
}

void CustomAudioCapture::onBtnJoinRoomClicked()
{
	std::string str_room = ui->lineEdit_room->text().toStdString();
	std::string str_uid = ui->lineEdit_uid->text().toStdString();
	std::string str_token;
	QString qstr_error;
	QStringList list;
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

		bytertc::VideoCanvas cavs;
		cavs.view = (void*)ui->widget->getWinId();
        cavs.render_mode = bytertc::kRenderModeHidden;
		cavs.background_color = 0x00000000;
		m_video->setLocalVideoCanvas(cavs);
		ui->widget->setUserInfo(str_room, str_uid);

		m_video->startAudioCapture();

		auto handler = createRoomHandler(str_room, str_uid);
		m_room->setRTCRoomEventHandler(handler);

		bytertc::UserInfo info;
		bytertc::RTCRoomConfig config;

		info.uid = str_uid.c_str();
        config.is_auto_publish_audio = true;
        config.is_auto_publish_video = true;
		config.is_auto_subscribe_audio = true;
		config.is_auto_subscribe_video = true;
		config.room_profile_type = bytertc::kRoomProfileTypeCommunication;
		str_token = Utils::generateToken(str_room, str_uid);
		int ret = m_room->joinRoom(str_token.c_str(), info, true, config);
		if (ret < 0) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error"), QMessageBox::Ok);
			box.exec();
			return;
		}

		m_video->setAudioSourceType(bytertc::kAudioSourceTypeExternal);
		list = QStringList{ "createRTCRoom", "setLocalVideoCanvas", "setRTCRoomEventHandler", "joinRoom", "setAudioSourceType"};
	}
	else {
		if (m_room) {
			m_room->leaveRoom();
			m_room->destroy();
			m_room = nullptr;
		}
		ui->btn_join->setText(QStringLiteral("进房"));
		list = QStringList{ "leaveRoom", "destroy" };
	}
	appendAPI(list);

}

void CustomAudioCapture::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
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
		//ui->widget->setUserInfo(roomid, uid);
	}
	else {
		QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged:") + QString::number(state), QMessageBox::Ok);
		box.exec();
	}

}

void CustomAudioCapture::onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
	QString log_str = QString("onUserPublishStreamVideo")
		+ ",stream_id:" + QString::fromStdString(stream_id)
		+ ",roomid:" + QString::fromStdString(roomid)
		+ ",uid:" + QString::fromStdString(uid)
		+ ",pub:" + QString::number(pub);
	appendCallback(log_str);

	if (m_video == nullptr) return;
    if (pub) {
		m_remote_uids.insert(uid);
        //bytertc::RemoteStreamKey key;
        bytertc::VideoCanvas cas;
        //key.room_id = roomid.c_str();
        //key.user_id = uid.c_str();
        //key.stream_index = bytertc::StreamIndex::kStreamIndexMain;
        cas.render_mode = bytertc::kRenderModeFit;
        cas.view = (void*)ui->widget_2->getWinId();
        m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
        m_rendering = uid;
        ui->widget_2->setUserInfo(roomid, uid);
        appendAPI("setRemoteVideoCanvas");
	}
}

void CustomAudioCapture::onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
	QString log_str = QString("onUserPublishStreamAudio")
		+ ",stream_id:" + QString::fromStdString(stream_id)
		+ ",roomid:" + QString::fromStdString(roomid)
		+ ",uid:" + QString::fromStdString(uid)
		+ ",pub:" + QString::number(pub);

	appendCallback(log_str);
}

void CustomAudioCapture::onPushDataTimer()
{
    if (m_video == nullptr || m_pcm_file == nullptr) return;

    int size = 160 * 1 * 2; //每10ms的数据大小=采样数*声道数*每个采样占字节数， 该pcm文件是16000采样率，单声道，每个样本占2个字节
    QByteArray data = m_pcm_file->read(size);
    if (data.size() == 0) {
        qWarning() << Q_FUNC_INFO << "read error";
        onBtnStopClicked();
        return;
    }
    bytertc::AudioFrameBuilder builder;
    builder.channel = bytertc::kAudioChannelMono;
    builder.sample_rate = bytertc::kAudioSampleRate16000;
    builder.data = (uint8_t*)data.data();
    builder.data_size = size;
    auto frame = bytertc::buildAudioFrame(builder);

    int ret = m_video->pushExternalAudioFrame(frame);
	if (ret < 0) {
		qWarning() << Q_FUNC_INFO << "pushExternalAudioFrame failed :" << ret;
	}
}
