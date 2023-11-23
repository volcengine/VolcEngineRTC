#include "ByteBeautyWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QMessageAuthenticationCode>
#include <QMessageBox>
#include <QFile>
#include <QNetworkReply>

#include <string>
#include <sstream>

#include "Public/http/http.h"
#include "bytertc_video.h"
#include "bytertc_room.h"
#include "Config.h"
#include "Utils.h"

/**
* 功能名称： VolcEngineRTC 美颜功能
* 功能简单描述：通过视频自定义处理实现视频帧的美颜、美白、滤镜、贴纸等效果
* 参考文档：https://www.volcengine.com/docs/6348/114717
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
*     getVideoEffectInterface 获取视频特效接口
*     setColorFilter 设置颜色滤镜
*     setColorFilterIntensity 设置已启用颜色滤镜的强度
*     setEffectNodes 设置视频特效素材包
*     updateNode 设置特效强度
*     getAuthMessage 从特效 SDK 获取授权消息，用于获取在线许可证
*     freeAuthMessage 释放授权信息
*     checkLicense 视频特效许可证检查
*     setAlgoModelPath 设置视频特效算法模型路径
*     enableEffect 开启关闭视频特效
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
*
* 火山美颜集成参考：https://www.volcengine.com/docs/6348/114717
* 本功能需付费使用，请联系美颜技术支持团队获取 v4.4.2+ 的 Standard/Lite 版本特效 SDK 及符合业务功能需求的 License 和素材资源包。
* 申请付费使用后：
* 1. 修改demo Config.h 中 g_byte_beauty_key 和 g_byte_beauty_secret 为您开通的美颜 key 和 secret
* 2. windows 将资源模型放在 Windows\3rd\Windows\VolcEngineRTC\ 目录中
* 3. macos 将资源模型放在  Windows\3rd\mac\VolcEngineRTC\ 目录中
* 
* Demo实现时的逻辑
*    本Demo演示功能：字节美颜
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/

//algorith mode path
#ifdef Q_OS_MAC
const QString strAlgoModelPath = "cvlab/ModelResource.bundle";
//filter path
const QString strFilterPath = "cvlab/FilterResource.bundle/Filter";
//stiker path
const QString strStickerPath = "cvlab/StickerResource.bundle/stickers";
//beauty path
const QString strBeautyPath = "cvlab/ComposeMakeup.bundle/ComposeMakeup/beauty_Android_standard";
//reshape path
const QString strReshapePath = "cvlab/ComposeMakeup.bundle/ComposeMakeup/reshape_standard";
#else
const QString strAlgoModelPath = "cvlab/model";
//filter path
const QString strFilterPath = "cvlab/Filter";
//stiker path
const QString strStickerPath = "cvlab/stickers_resource/stickers";
//beauty path
const QString strBeautyPath = "cvlab/ComposeMakeup/beauty_Android_standard";
//reshape path
const QString strReshapePath = "cvlab/ComposeMakeup/reshape_standard";
#endif

//license url
const QString strGetLicenseUrl = "https://cv-tob.bytedance.com/v1/api/sdk/tob_license/getlicense";

// 素材key对应说明：https://www.volcengine.com/docs/6705/102041 

//beauty parameters
//美白
std::string strWhiteValueKey = "whiten";

//磨皮
std::string strSkinGrindingValueKey = "smooth";

//reshape parameters
//大眼
std::string strBigEyesKey = "Internal_Deform_Eye";
//瘦脸 
std::string strThinFaceValueKey = "Internal_Deform_CutFace";

//license
const QString strLicenseFileName = "effect.lic";

ByteBeautyWidget::ByteBeautyWidget(QWidget *parent)
        : BaseWidget(parent)
    , ui(new Ui::ByteBeautyWidget)
{
    ui->setupUi(this);
	initData();
	initUI();
    initRTCVideo();
}

ByteBeautyWidget::~ByteBeautyWidget()
{
    cleanRTCVideo();
    delete ui;
}

void ByteBeautyWidget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QBrush b("#FFFFFF");
    p.setBrush(b);
    QPen pen(Qt::transparent);
    p.setPen(pen);

    p.drawRoundedRect(this->rect(), 10, 10);
}

void ByteBeautyWidget::initUI() {
	//beauty group
	m_beautyBtnGroup = new QButtonGroup(this);
	auto beautyButtonClickedHander = [=](int beautyType) {
		m_beautyKey2ValueInfo[m_currentBeautyKeyType].value = getEffectValue();
		m_currentBeautyKeyType = static_cast<BeautyKeyType> (beautyType);
		updateEffectSliderValue();
	};

#if (QT_VERSION >= QT_VERSION_CHECK(5,15,0))
	connect(m_beautyBtnGroup, &QButtonGroup::idClicked, this, beautyButtonClickedHander);
#else
	connect(m_beautyBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, beautyButtonClickedHander);
#endif

    m_beautyBtnGroup->addButton(ui->whiteBtn, kWhiteKeyType);
    m_beautyBtnGroup->addButton(ui->gridThinBtn, kSkinGrindingKeyType);
    m_beautyBtnGroup->addButton(ui->bigEyeBtn, kBigEyeKeyType);
    m_beautyBtnGroup->addButton(ui->thinFaceBtn, kThinFaceKeyType);
    connect(ui->btn_check, &QPushButton::clicked, this, &ByteBeautyWidget::on_checkBtn_clicked);
    connect(ui->btn_joinRoom, &QPushButton::clicked, this, &ByteBeautyWidget::on_joinRoom_clicked);

	//sticker type
	m_stickerBtnGroup = new QButtonGroup(this);
	auto stickerBtnClickedHander = [=](int stickerType) {
		auto currentStickerName = m_stickerType2Name[stickerType];
		if (currentStickerName == m_currentStickerName) {
			m_currentVideoEffectStatus &= ~kStickerpath;
			m_stickerBtnGroup->blockSignals(true);
			m_stickerBtnGroup->setExclusive(false);
			auto btn = m_stickerBtnGroup->checkedButton();
			if (btn) {
				btn->setChecked(false);
				btn->clicked(false);
			}
			m_stickerBtnGroup->setExclusive(true);
			m_stickerBtnGroup->blockSignals(false);
			m_currentStickerName.clear();
		}
		else {
			m_currentVideoEffectStatus |= kStickerpath;
			m_currentStickerName = currentStickerName;
		}
		updateEffectNodes();
	};

#if (QT_VERSION >= QT_VERSION_CHECK(5,15,0))
	connect(m_stickerBtnGroup, &QButtonGroup::idClicked, this, stickerBtnClickedHander);
#else
	connect(m_stickerBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, stickerBtnClickedHander);
#endif

    m_stickerBtnGroup->addButton(ui->stickerBtn_1,kBlackCatGlassStickerType);
    m_stickerBtnGroup->addButton(ui->stickerBtn_2,kMakeMoneyCatStickerType);
    m_stickerBtnGroup->addButton(ui->stickerBtn_3,kKidMakeupStickerType);
    m_stickerBtnGroup->addButton(ui->stickerBtn_4,kLovelyPigStickerType);
    m_stickerBtnGroup->addButton(ui->stickerBtn_5,kMuchMoneyStickerType);
    m_stickerBtnGroup->addButton(ui->stickerBtn_6,kQixigaobaiStickerType);
    m_stickerBtnGroup->addButton(ui->stickerBtn_7,kPigHeadPigEarStickerType);
    m_stickerBtnGroup->addButton(ui->stickerBtn_8,kHappyRabbitStickerType);

	// color filter
	m_colorFilterBtnGroup = new QButtonGroup(this);
	auto colorFilterBtnClickedHander = [=](int colorFilterType) {
		m_currentVideoEffectStatus |= kColorFilterPath;
		m_currentColorFilter = m_colorFilerType2Name[colorFilterType];
		updateColorFilter();
	};

#if (QT_VERSION >= QT_VERSION_CHECK(5,15,0))
	connect(m_colorFilterBtnGroup, &QButtonGroup::idClicked, this, colorFilterBtnClickedHander);
#else
	connect(m_colorFilterBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, colorFilterBtnClickedHander);
#endif

    m_colorFilterBtnGroup->addButton(ui->filterBtn_1, kPeachColorFilter);
    m_colorFilterBtnGroup->addButton(ui->filterBtn_2, kClearColorFIlter);
    m_colorFilterBtnGroup->addButton(ui->filterBtn_3, kNightColorFilter);
    m_colorFilterBtnGroup->addButton(ui->filterBtn_4, kColdOxygenColorFilter);
}

void ByteBeautyWidget::initData() {
	auto applicationDir = QApplication::applicationDirPath() + "/Resources/";
	m_videoEffectType2Path.insert(kBeautyPath,applicationDir+strBeautyPath);
	m_videoEffectType2Path.insert(kReshapePath,applicationDir+strReshapePath);
	m_videoEffectType2Path.insert(kStickerpath,applicationDir+strStickerPath);
	m_videoEffectType2Path.insert(kColorFilterPath,applicationDir+strFilterPath);
	m_videoEffectType2Path.insert(kAlgoModelPath,applicationDir+strAlgoModelPath);

	resetBeautyValueInfo();

	m_stickerType2Name.insert(kBlackCatGlassStickerType,"heimaoyanjing");
	m_stickerType2Name.insert(kMakeMoneyCatStickerType,"zhaocaimao");
	m_stickerType2Name.insert(kKidMakeupStickerType,"kidmakup");
	m_stickerType2Name.insert(kLovelyPigStickerType,"chitushaonv");
	m_stickerType2Name.insert(kMuchMoneyStickerType,"qianduoduo");
	m_stickerType2Name.insert(kQixigaobaiStickerType,"biaobaiqixi");
	m_stickerType2Name.insert(kPigHeadPigEarStickerType,"zhutouzhuer");
	m_stickerType2Name.insert(kHappyRabbitStickerType,"huanletuchiluobo");

	m_colorFilerType2Name.insert(kPeachColorFilter,"Filter_06_03");
	m_colorFilerType2Name.insert(kClearColorFIlter,"Filter_37_L5");
	m_colorFilerType2Name.insert(kNightColorFilter,"Filter_35_L3");
	m_colorFilerType2Name.insert(kColdOxygenColorFilter,"Filter_30_Po8");
}

void ByteBeautyWidget::resetBeautyValueInfo(){
	m_beautyKey2ValueInfo.clear();
	m_beautyKey2ValueInfo.insert(kWhiteKeyType, { strWhiteValueKey,0.0f });
	m_beautyKey2ValueInfo.insert(kSkinGrindingKeyType, { strSkinGrindingValueKey,0.0f });
	m_beautyKey2ValueInfo.insert(kBigEyeKeyType, { strBigEyesKey,0.0f });
	m_beautyKey2ValueInfo.insert(kThinFaceKeyType, { strThinFaceValueKey,0.0f });
}

void ByteBeautyWidget::updateColorFilter() {
	bytertc::IVideoEffect* effectPtr = m_video->getVideoEffectInterface();
	if (effectPtr == nullptr){
		qDebug() << "video effect ptr is nullptr";
		return;
	}
	QStringList list;
    if (m_currentVideoEffectStatus & kColorFilterPath) {
        int ret1 = 0, ret2 = 0;
		QString colorFIlterPath =m_videoEffectType2Path[kColorFilterPath] + "/" + m_currentColorFilter;
		std::string strColorFilter = colorFIlterPath.toStdString();
		ret1 = effectPtr->setColorFilter(strColorFilter.c_str());
		ret2 = effectPtr->setColorFilterIntensity(getColorValue());

		list = QStringList{"setColorFilter", "setColorFilterIntensity"};
		if (ret1 != 0 || ret2 != 0) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "setColorFilter error:" + QString::number(ret1) + "," +QString::number(ret2), QMessageBox::Ok);
			box.exec();
			return;
		}
	}else {
		effectPtr->setColorFilter(nullptr);
		list = QStringList{"setColorFilter"};
	}
	ui->widget_log->appendAPI(list);
}

void ByteBeautyWidget::updateEffectNodes(){
	//set  effect node
	if (m_video == nullptr) return;
	bytertc::IVideoEffect* effectPtr = m_video->getVideoEffectInterface();
	if (effectPtr == nullptr){
		qDebug() << "video effect ptr is nullptr";
		return;
	}

	const char* effectNodeArray[4] = { 0,0,0,0 };
	int  i = 0;
	int ret = 0;
	auto appendNode = [&](const QString &path){
		
			std::string strBeautyPath = path.toStdString();
			char *strBeauty = new char[strBeautyPath.size() + 1];
			strcpy(strBeauty, strBeautyPath.c_str());
			effectNodeArray[i++] = strBeauty;
	};

	appendNode(m_videoEffectType2Path[kBeautyPath]);
	appendNode(m_videoEffectType2Path[kReshapePath]);
	if (m_currentVideoEffectStatus & kStickerpath) {
		appendNode(m_videoEffectType2Path[kStickerpath] + "/" + m_currentStickerName);
	}
	
	ret = effectPtr->setEffectNodes(effectNodeArray, i);
	ui->widget_log->appendAPI("setEffectNodes");
	if (ret != 0) {
		QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "setEffectNodes error:" + QString::number(ret), QMessageBox::Ok);
		box.exec();
		return;
	}

	std::string path;
	path = m_videoEffectType2Path[kBeautyPath].toStdString();
	
	for (int i = kWhiteKeyType; i <= kThinFaceKeyType; i++) {
		BeautyValueInfo & info = m_beautyKey2ValueInfo[i];
		std::string path;
		if (i <= kSkinGrindingKeyType) {
			path = m_videoEffectType2Path[kBeautyPath].toStdString();
		}
		else {
			path = m_videoEffectType2Path[kReshapePath].toStdString();
		}
        ret = effectPtr->updateEffectNode(path.c_str(),info.keyName.c_str(),info.value);
		ui->widget_log->appendAPI("updateEffectNode");
        if (ret != 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "updateEffectNode error:" + QString::number(ret), QMessageBox::Ok);
            box.exec();
            return;
        }
    }

	//free memory
	for (int j = 0; j < i; j++){
		delete effectNodeArray[j];
	}
}

float ByteBeautyWidget::getEffectValue(){
    return ui->beautyValueSlider->value()*1.0f / ui->beautyValueSlider->maximum();
}

void ByteBeautyWidget::updateEffectSliderValue()
{
    auto maxValue = ui->beautyValueSlider->maximum();
	int nValue = maxValue * m_beautyKey2ValueInfo[m_currentBeautyKeyType].value;
    ui->beautyValueSlider->blockSignals(true);
    ui->beautyValueSlider->setValue(nValue);
    ui->beautyValueSlider->blockSignals(false);
}

float ByteBeautyWidget::getColorValue(){
    return ui->filterValueSlider->value()*1.0f / ui->filterValueSlider->maximum();
}

void ByteBeautyWidget::startCheckLicense() {
	resetUI();
	auto licensePath = getLicenseFilePath();
    qDebug() << Q_FUNC_INFO << "license file=" << licensePath;
	if (!QFile::exists(licensePath))
	{
		setCheckLicenseResultText(kRuqestLicense, QStringLiteral("正在请求鉴权。。。"));
		requestLicense();
		return;
	}
	//check local is exist
	checkLicense();
}

QString ByteBeautyWidget::getLicenseFilePath()
{
	QString licenseFilePath = qApp->applicationDirPath() + "/" + strLicenseFileName;
	return licenseFilePath;
}

void ByteBeautyWidget::requestLicense()
{
	if (g_byte_beauty_key.empty() || g_byte_beauty_secret.empty()) {
		qWarning() << Q_FUNC_INFO << "byte beauty key or secret is empty";
		return;
	}
	if (m_video == nullptr) {
		qWarning() << Q_FUNC_INFO << "not createRTCVideo ";
		return;
	}

	//set  effect node
	bytertc::IVideoEffect* effectPtr = m_video->getVideoEffectInterface();
	if (effectPtr == nullptr) {
		qDebug() << "video effect ptr is nullptr";
		return;
	}

    QString key = QString::fromStdString(g_byte_beauty_key);
    QString secret = QString::fromStdString(g_byte_beauty_secret);

    if (key.isEmpty() || secret.isEmpty()) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "请填写字节美颜key+secret:", QMessageBox::Ok);
        box.exec();
        return;
    }

	QJsonObject postDataObj;
	//key
	postDataObj["key"] = key;

	//authMsg
	char *pMsg = nullptr;
	int len = 0;
	effectPtr->getAuthMessage(&pMsg, &len);
	ui->widget_log->appendAPI("getAuthMessage");
	if (pMsg == NULL) 
	{
		setCheckLicenseResultText(kLicenseError, QStringLiteral("获取授权消息失败"));
		return;
	}
	QString authMsg = pMsg;
	postDataObj["authMsg"] = authMsg;
	effectPtr->freeAuthMessage(pMsg);
	ui->widget_log->appendAPI("freeAuthMessage");
	qint64 nonceNum = QRandomGenerator::global()->generate64() % 99999999;  //随机生成0到9的随机数
	postDataObj["nonce"] = nonceNum;

	//timestamp
	qint64 curUtcSeconds = QDateTime::currentSecsSinceEpoch();
	postDataObj["timestamp"] = curUtcSeconds;

	//digest
	QString digestData = key;
	digestData += QString::number(nonceNum);
	digestData += QString::number(curUtcSeconds);
	digestData += authMsg;
	QString sign = QMessageAuthenticationCode::hash(digestData.toUtf8(), secret.toUtf8(), QCryptographicHash::Sha256).toHex();
	sign = sign.toUpper();
	postDataObj["digest"] = sign;

	QJsonDocument doc(postDataObj);
	auto body = doc.toJson();
	auto &httpInstance = Http::instance();

	auto reply = httpInstance.post(QUrl(strGetLicenseUrl), body, "application/json");
	connect(reply, &HttpReply::finished, this, [=](auto &reply)
	{

        qDebug() << Q_FUNC_INFO << __LINE__ << "reply finished,is successful:" << reply.isSuccessful();
		if (reply.isSuccessful()) {
			qDebug() << "Feel the bytes!" << reply.body();

			QJsonParseError error;
			QJsonDocument doc = QJsonDocument::fromJson(reply.body(), &error);
			if (error.error != QJsonParseError::NoError)
			{
				setCheckLicenseResultText(kLicenseError, QStringLiteral("json解析错误"));
				return;
			}
			auto obj = doc.object();
			auto data = obj["data"].toString().toUtf8();
			auto statusCode = obj["status_code"].toInt();
			if (statusCode != 0)
			{
				setCheckLicenseResultText(kLicenseError, QStringLiteral("请求失败 status_code = ") + QString::number(statusCode));
				return;
			}
			auto digest = obj["digest"].toString();
			auto dataContent = data.fromBase64(data);
			QString sign = QMessageAuthenticationCode::hash(data, secret.toUtf8(), QCryptographicHash::Sha256).toHex();
			sign = sign.toUpper();
			if (sign != digest)
			{
				setCheckLicenseResultText(kLicenseError, QStringLiteral("校验失败"));
				return;
			}
			saveLicenseFile(dataContent);
			QString strFilePath = getLicenseFilePath();
			if (strFilePath.isEmpty())
			{
				setCheckLicenseResultText(kLicenseError, QStringLiteral("视频特效证书保存失败"));
				return;
			}
			checkLicense();
		}
		else
		{
			qDebug() << "Something's wrong here" << reply.statusCode() << reply.reasonPhrase();
			setCheckLicenseResultText(kLicenseError, QStringLiteral("网络错误：") + reply.reasonPhrase() + QStringLiteral("错误码：") + QString::number(reply.statusCode()));
		}
	});
}

void ByteBeautyWidget::setCheckLicenseResultText(CheckLicenseStatus status, const QString &text) {
    if (status == kRuqestLicense) {
        ui->checkLicenseStatusLabel->setStyleSheet("color:black");
	}
    else if (status == kLicenseError) {
        ui->checkLicenseStatusLabel->setStyleSheet("color:red");
	}
    else {
        ui->checkLicenseStatusLabel->setStyleSheet("color:green");
    }
    ui->checkLicenseStatusLabel->setText(text);
	m_checkStatus = status;
}

void ByteBeautyWidget::saveLicenseFile(const QByteArray &data)
{
	QString licenseFilePath = getLicenseFilePath();
	QFile f(licenseFilePath);
	if (f.open(QIODevice::WriteOnly))
	{
		f.write(data);
		f.close();
	}
}

void ByteBeautyWidget::checkLicense() {

	QStringList list;
	if (m_video == nullptr) return;
	bytertc::IVideoEffect* effectPtr = m_video->getVideoEffectInterface();
	if (effectPtr == nullptr) {
		qDebug() << "video effect ptr is nullptr";
		return;
	}
    std::string algoModelPath = m_videoEffectType2Path[kAlgoModelPath].toStdString();

	auto licensePath = getLicenseFilePath().toStdString();
	QString strResultText = QStringLiteral("检测结果：");
    auto nRet = effectPtr->initCVResource(licensePath.c_str(), algoModelPath.c_str());

    if (nRet == 0) {
        nRet = effectPtr->enableVideoEffect();
		if (nRet != 0) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "enableVideoEffect error:" + QString::number(nRet), QMessageBox::Ok);
			box.exec();
			return;
		}
		list = QStringList{"getVideoEffectInterface", "initCVResource", "enableVideoEffect"};
		ui->widget_log->appendAPI(list);
		QFile::remove(licensePath.c_str());
		updateEffectNodes();
		updateColorFilter();
		strResultText += QStringLiteral("成功");
		setCheckLicenseResultText(kLicenseOk, strResultText);
	}
	else{
        strResultText += QStringLiteral("失败(错误码：") + QString::number(nRet) + QStringLiteral(")");
        setCheckLicenseResultText(kLicenseError, strResultText);
        qDebug() << Q_FUNC_INFO << "licensePath=" << QString::fromStdString(licensePath);
    }
}

void ByteBeautyWidget::on_beautyValueSlider_valueChanged(int){
	m_beautyKey2ValueInfo[m_currentBeautyKeyType].value = getEffectValue();
	updateEffectNodes();
}

void ByteBeautyWidget::on_filterValueSlider_valueChanged(int){
    updateColorFilter();
}

void ByteBeautyWidget::on_checkBtn_clicked()
{
	if (m_checkStatus == CheckLicenseStatus::kRuqestLicense) {
		
		startCheckLicense();
	}
	else {
		return;
	}
	
}

void ByteBeautyWidget::on_joinRoom_clicked()
{
	QStringList list;
    if (ui->btn_joinRoom->text() == QStringLiteral("进房")) {
		QString qstr_user_name = ui->lineEdit_user->text();
		QString qstr_room = ui->lineEdit_room->text();
		QString qstr_error;

		std::string str_user_name = qstr_user_name.toStdString();
		std::string str_room = qstr_room.toStdString();

		if (!Utils::checkIDValid(qstr_user_name, QStringLiteral("用户名"), qstr_error)) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), qstr_error, QMessageBox::Ok);
			box.exec();
			return;

		}

		if (!Utils::checkIDValid(qstr_room, QStringLiteral("房间号"), qstr_error)) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), qstr_error, QMessageBox::Ok);
			box.exec();
			return;
		}

		bytertc::VideoCanvas canvas((void*)ui->widget->getWinId(), bytertc::RenderMode::kRenderModeHidden, 0);
		m_video->setLocalVideoCanvas(bytertc::StreamIndex::kStreamIndexMain, canvas);

		m_room = m_video->createRTCRoom(qstr_room.toStdString().c_str());
		if (m_room == nullptr) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error, please check"), QMessageBox::Ok);
			box.exec();
			return;
		}

		m_room_handler = createRoomHandler(str_room, str_user_name);
		m_room->setRTCRoomEventHandler(m_room_handler.get());
		std::string token = Utils::generateToken(str_room, str_user_name);
		bytertc::UserInfo userinfo;
		userinfo.uid = str_user_name.c_str();
		bytertc::RTCRoomConfig config;
		config.is_auto_publish = true;
		config.is_auto_subscribe_audio = true;
		config.is_auto_subscribe_video = true;
		
		int ret = m_room->joinRoom(token.c_str(), userinfo, config);
		if (ret != 0) {
			QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error, please check"), QMessageBox::Ok);
			box.exec();
			return;
		}

		list = QStringList{"setLocalVideoCanvas", "createRTCRoom", "setRTCRoomEventHandler", "joinRoom"};
    } else {
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
        }
		list = QStringList{ "leaveRoom", "destroy"};
        ui->btn_joinRoom->setText(QStringLiteral("进房"));
    }
	ui->widget_log->appendAPI(list);
}

void ByteBeautyWidget::resetUI() {

	m_currentVideoEffectStatus = 0;

	resetBeautyValueInfo();
	m_beautyBtnGroup->blockSignals(true);
    ui->whiteBtn->setChecked(true);
    ui->whiteBtn->clicked(true);
	m_currentBeautyKeyType = kWhiteKeyType;
	m_currentVideoEffectStatus |= kBeautyPath;
	m_currentVideoEffectStatus |= kReshapePath;
	m_beautyBtnGroup->blockSignals(false);

	m_colorFilterBtnGroup->blockSignals(true);
    ui->filterBtn_1->setChecked(true);
    ui->filterBtn_1->clicked(true);
	m_currentVideoEffectStatus |= kColorFilterPath;
	m_currentColorFilter = m_colorFilerType2Name[kPeachColorFilter];
	m_colorFilterBtnGroup->blockSignals(false);

	m_currentStickerName.clear();
	m_stickerBtnGroup->blockSignals(true);
	m_stickerBtnGroup->setExclusive(false);
	auto btn = m_stickerBtnGroup->checkedButton();
	if (btn) {
		btn->setChecked(false);
		btn->clicked(false);
	}
	m_stickerBtnGroup->setExclusive(true);
	m_stickerBtnGroup->blockSignals(false);

    ui->beautyValueSlider->blockSignals(true);
    ui->beautyValueSlider->setValue(0);
    ui->beautyValueSlider->blockSignals(false);

    ui->filterValueSlider->blockSignals(true);
    ui->filterValueSlider->setValue(0);
    ui->filterValueSlider->blockSignals(false);
}

void ByteBeautyWidget::initRTCVideo()
{
    m_handler = std::make_unique<ByteRTCEventHandler>();
    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
    m_video->startAudioCapture();
    m_video->startVideoCapture();
	QStringList list = { "createRTCVideo","startAudioCapture","startVideoCapture", };
	ui->widget_log->appendAPI(list);
}

void ByteBeautyWidget::cleanRTCVideo()
{
	QStringList list;
	
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
			list = QStringList{ "leaveRoom","setRTCRoomEventHandler","startVidedestroyoCapture" };
        }
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
		list = list + QStringList{"stopAudioCapture", "stopVideoCapture", "destroyRTCVideo"};
    }
	ui->widget_log->appendAPI(list);
}

std::unique_ptr<ByteRTCRoomHandler> ByteBeautyWidget::createRoomHandler(std::string roomid, std::string uid)
{
	std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &ByteBeautyWidget::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &ByteBeautyWidget::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &ByteBeautyWidget::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &ByteBeautyWidget::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &ByteBeautyWidget::onSigUserLeave);
	connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
		QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
		box.exec();
		});
    return roomH;
}

void ByteBeautyWidget::onRoomStateChanged(const char* room_id, const char* uid, int state, const char* extra_info)
{
	if (room_id == nullptr || uid == nullptr) {
		return;
    }
    ui->widget_log->appendCallback("onRoomStateChanged: roomid" + QString::fromStdString(room_id) + ",uid:" + QString::fromStdString(uid) + ",state:" + QString::number(state));

}

void ByteBeautyWidget::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    std::stringstream log_str;
    log_str << std::string("onRoomStateChanged,roomid:")
        << roomid
        << ",uid:" << uid
        << ",state:" << std::to_string(state)
        << ",extra:" << extra_info;
    ui->widget_log->appendCallback(QString::fromStdString(log_str.str()));
    if (state == 0) {
        ui->btn_joinRoom->setText(QStringLiteral("离房"));
    }

}

void ByteBeautyWidget::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type)
{
    QString log_str = QString("onUserPublishStream,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",type:" + QString::number(type);
    ui->widget_log->appendCallback(log_str);
}

void ByteBeautyWidget::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type , bytertc::StreamRemoveReason)
{
    QString log_str = QString("onUserUnPublishStream,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",type:" + QString::number(type);
    ui->widget_log->appendCallback(log_str);
}

void ByteBeautyWidget::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int)
{
    QString str = "onUserJoined, uid:" + QString::fromStdString(info.uid) + ",roomid:" + QString::fromStdString(info.roomid);
    ui->widget_log->appendCallback(str);
}

void ByteBeautyWidget::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, uid:" + QString::fromStdString(uid) + ",roomid:" + QString::fromStdString(roomid);
    ui->widget_log->appendCallback(str);
}
