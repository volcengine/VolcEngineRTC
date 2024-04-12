#include "BeautySettingWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include "RoomMainWidget.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QMessageAuthenticationCode>
#include "http.h"
#include <QFile>
#include "Constants.h"

//algorith mode path
const QString strAlgoModelPath = "cvlab/ModelResource.bundle";
//filter path
const QString strFilterPath = "cvlab/FilterResource.bundle/Filter";
//stiker path
const QString strStickerPath = "cvlab/StickerResource.bundle/stickers";
//beauty path
const QString strBeautyPath = "cvlab/ComposeMakeup.bundle/ComposeMakeup/beauty_Android_live";
//reshape path
const QString strReshapePath = "cvlab/ComposeMakeup.bundle/ComposeMakeup/reshape_live";

//license url
const QString strGetLicenseUrl = "https://cv-tob.bytedance.com/v1/api/sdk/tob_license/getlicense";

//beauty parameters
//美白
std::string strWhiteValueKey = "whiten";
//锐化
std::string strSharpValueKey = "sharp";
//磨皮
std::string strSkinGrindingValueKey = "smooth";

//reshape parameters
//大眼
std::string strBigEyesKey = "Internal_Deform_Eye";
//瘦脸 
std::string strThinFaceValueKey = "Internal_Deform_CutFace";

//license
const QString strLicenseFileName = "effect.lic";

BeautySettingWidget::BeautySettingWidget(RoomMainWidget *parent)
        : QWidget(parent) {
	m_roomMainWidget = parent;
    ui.setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    parent->installEventFilter(this);

	initData();
	initUI();
}

bool BeautySettingWidget::eventFilter(QObject *watched, QEvent *event) {
    if (watched == parent()) {
        auto parentWindow = dynamic_cast<QWidget *>(parent());
        if (parentWindow == nullptr) {
            return false;
        }
        if (event->type() == QEvent::Resize || event->type() == QEvent::Move) {
            //update login geometry
            auto selfRect = this->rect();
            auto parentGem = parentWindow->geometry();

            int nleft = parentGem.left() + (parentGem.width() - selfRect.width()) / 2;
            int nTop = parentGem.bottom() - 30 - selfRect.height();

            setGeometry(nleft, nTop, selfRect.width(), selfRect.height());
        }
    }
    return false;
}

void BeautySettingWidget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QBrush b("#FFFFFF");
    p.setBrush(b);
    QPen pen(Qt::transparent);
    p.setPen(pen);

    p.drawRoundedRect(this->rect(), 10, 10);
}

void BeautySettingWidget::initUI() {
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

	m_beautyBtnGroup->addButton(ui.whiteBtn, kWhiteKeyType);
	m_beautyBtnGroup->addButton(ui.gridThinBtn, kSkinGrindingKeyType);
	m_beautyBtnGroup->addButton(ui.bigEyeBtn, kBigEyeKeyType);
	m_beautyBtnGroup->addButton(ui.thinFaceBtn, kThinFaceKeyType);

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

	m_stickerBtnGroup->addButton(ui.stickerBtn_1,kBlackCatGlassStickerType);
	m_stickerBtnGroup->addButton(ui.stickerBtn_2,kMakeMoneyCatStickerType);
	m_stickerBtnGroup->addButton(ui.stickerBtn_3,kKidMakeupStickerType);
	m_stickerBtnGroup->addButton(ui.stickerBtn_4,kLovelyPigStickerType);
	m_stickerBtnGroup->addButton(ui.stickerBtn_5,kMuchMoneyStickerType);
	m_stickerBtnGroup->addButton(ui.stickerBtn_6,kQixigaobaiStickerType);
	m_stickerBtnGroup->addButton(ui.stickerBtn_7,kPigHeadPigEarStickerType);
	m_stickerBtnGroup->addButton(ui.stickerBtn_8,kHappyRabbitStickerType);

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

	m_colorFilterBtnGroup->addButton(ui.filterBtn_1, kPeachColorFilter);
	m_colorFilterBtnGroup->addButton(ui.filterBtn_2, kClearColorFIlter);
	m_colorFilterBtnGroup->addButton(ui.filterBtn_3, kNightColorFilter);
	m_colorFilterBtnGroup->addButton(ui.filterBtn_4, kColdOxygenColorFilter);
}

void BeautySettingWidget::initData() {
	auto applicationDir = qApp->applicationDirPath() + "/";
	m_videoEffectType2Path.insert(kBeautyPath,applicationDir+strBeautyPath);
	m_videoEffectType2Path.insert(kReshapePath,applicationDir+strReshapePath);
	m_videoEffectType2Path.insert(kStickerpath,applicationDir+strStickerPath);
	m_videoEffectType2Path.insert(kColorFilterPath,applicationDir+strFilterPath);
	m_videoEffectType2Path.insert(kAlgoModelPath,applicationDir+strAlgoModelPath);

	resetBeautyValueInfo();

	m_stickerType2Name.insert(kBlackCatGlassStickerType,"heimaoyanjing");
	m_stickerType2Name.insert(kMakeMoneyCatStickerType,"zhaocaimao");
	m_stickerType2Name.insert(kKidMakeupStickerType,"kidmakup");
	m_stickerType2Name.insert(kLovelyPigStickerType,"keaizhu");
	m_stickerType2Name.insert(kMuchMoneyStickerType,"qianduoduo");
	m_stickerType2Name.insert(kQixigaobaiStickerType,"biaobaiqixi");
	m_stickerType2Name.insert(kPigHeadPigEarStickerType,"zhutouzhuer");
	m_stickerType2Name.insert(kHappyRabbitStickerType,"huanletuchiluobo");

	m_colorFilerType2Name.insert(kPeachColorFilter,"Filter_06_03");
	m_colorFilerType2Name.insert(kClearColorFIlter,"Filter_37_L5");
	m_colorFilerType2Name.insert(kNightColorFilter,"Filter_35_L3");
	m_colorFilerType2Name.insert(kColdOxygenColorFilter,"Filter_30_Po8");
}

void BeautySettingWidget::resetBeautyValueInfo(){
	m_beautyKey2ValueInfo.clear();
	m_beautyKey2ValueInfo.insert(kWhiteKeyType, { strWhiteValueKey,0.0f });
	m_beautyKey2ValueInfo.insert(kSkinGrindingKeyType, { strSkinGrindingValueKey,0.0f });
	m_beautyKey2ValueInfo.insert(kBigEyeKeyType, { strBigEyesKey,0.0f });
	m_beautyKey2ValueInfo.insert(kThinFaceKeyType, { strThinFaceValueKey,0.0f });
}

void BeautySettingWidget::updateColorFilter() {
	auto effectPtr = m_roomMainWidget->GetIVideoEffectPtr();
	if (effectPtr == nullptr){
		qDebug() << "video effect ptr is nullptr";
		return;
	}
	if (m_currentVideoEffectStatus & kColorFilterPath) {   
		QString colorFIlterPath =m_videoEffectType2Path[kColorFilterPath] + "/" + m_currentColorFilter;
		std::string strColorFilter = colorFIlterPath.toStdString();
		effectPtr->setColorFilter(strColorFilter.c_str());
		effectPtr->setColorFilterIntensity(getColorValue());
	}else {
		effectPtr->setColorFilter(nullptr);
	}
}

void BeautySettingWidget::updateEffectNodes(){
	//set  effect node
	auto effectPtr = m_roomMainWidget->GetIVideoEffectPtr();
	if (effectPtr == nullptr){
		qDebug() << "video effect ptr is nullptr";
		return;
	}

	const char* effectNodeArray[4] = { 0,0,0,0 };
	int  i = 0;
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
	
	effectPtr->setEffectNodes(effectNodeArray, i);

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
		auto nRet = effectPtr->updateNode(path.c_str(),info.keyName.c_str(),info.value);
	}

	//free memory
	for (int j = 0; j < i; j++){
		delete effectNodeArray[j];
	}
}

float BeautySettingWidget::getEffectValue(){
	return ui.beautyValueSlider->value()*1.0f / ui.beautyValueSlider->maximum();
}

void BeautySettingWidget::updateEffectSliderValue()
{
	auto maxValue = ui.beautyValueSlider->maximum();
	int nValue = maxValue * m_beautyKey2ValueInfo[m_currentBeautyKeyType].value;
	ui.beautyValueSlider->blockSignals(true);
	ui.beautyValueSlider->setValue(nValue);
	ui.beautyValueSlider->blockSignals(false);
}

float BeautySettingWidget::getColorValue(){
	return ui.filterValueSlider->value()*1.0f / ui.filterValueSlider->maximum();
}

void BeautySettingWidget::on_closeBtn_clicked() {
	hide();
}

void BeautySettingWidget::startCheckLicense() {
	resetUI();
	auto licensePath = getLicenseFilePath();
	if (!QFile::exists(licensePath))
	{
		setCheckLicenseResultText(kRuqestLicense, QStringLiteral("正在请求鉴权。。。"));
		requestLicense();
		return;
	}
	//check local is exist
	checkLicense();
}

QString BeautySettingWidget::getLicenseFilePath()
{
	QString licenseFilePath = qApp->applicationDirPath() + "/" + strLicenseFileName;
	return licenseFilePath;
}

void BeautySettingWidget::requestLicense()
{
	//set  effect node
	auto effectPtr = m_roomMainWidget->GetIVideoEffectPtr();
	if (effectPtr == nullptr) {
		qDebug() << "video effect ptr is nullptr";
		return;
	}

	QString key = Constants::BEAUTY_KEY.c_str();
	QString secret = Constants::BEAUTY_SECRET.c_str();

	QJsonObject postDataObj;
	//key
	postDataObj["key"] = key;

	//authMsg
	char *pMsg = nullptr;
	int len = 0;
	effectPtr->getAuthMessage(&pMsg, &len);
	if (pMsg == NULL) 
	{
		setCheckLicenseResultText(kLicenseError, QStringLiteral("获取授权消息失败"));
		return;
	}
	QString authMsg = pMsg;
	postDataObj["authMsg"] = authMsg;
	effectPtr->freeAuthMessage(pMsg);
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

void BeautySettingWidget::setCheckLicenseResultText(CheckLicenseStatus status, const QString &text) {
	if (status == kRuqestLicense) {
		ui.checkLicenseStatusLabel->setStyleSheet("color:black");
	}
	else if (status == kLicenseError) {
		ui.checkLicenseStatusLabel->setStyleSheet("color:red");
	}
	else {
		ui.checkLicenseStatusLabel->setStyleSheet("color:green");
	}
	ui.checkLicenseStatusLabel->setText(text);
}

void BeautySettingWidget::saveLicenseFile(const QByteArray &data)
{
	QString licenseFilePath = getLicenseFilePath();
	QFile f(licenseFilePath);
	if (f.open(QIODevice::WriteOnly))
	{
		f.write(data);
		f.close();
	}
}

void BeautySettingWidget::checkLicense() {

	auto effectPtr = m_roomMainWidget->GetIVideoEffectPtr();
	if (effectPtr == nullptr) {
		qDebug() << "video effect ptr is nullptr";
		return;
	}
	auto licensePath = getLicenseFilePath().toStdString();
	QString strResultText = QStringLiteral("检测结果：");
	auto nRet = effectPtr->checkLicense(nullptr, nullptr, licensePath.c_str());

	if (nRet == 0){
		std::string algoModelPath = m_videoEffectType2Path[kAlgoModelPath].toStdString();
		qDebug() << algoModelPath.c_str();
		effectPtr->setAlgoModelPath(algoModelPath.c_str());
		nRet = effectPtr->enableEffect(true);
		QFile::remove(licensePath.c_str());
		updateEffectNodes();
		updateColorFilter();
		strResultText += QStringLiteral("成功");
		setCheckLicenseResultText(kLicenseOk, strResultText);
	}
	else{
		strResultText += QStringLiteral("失败(错误码：") + QString::number(nRet) + QStringLiteral(")");
		setCheckLicenseResultText(kLicenseError, strResultText);
	}
}

void BeautySettingWidget::on_beautyValueSlider_valueChanged(int){
	m_beautyKey2ValueInfo[m_currentBeautyKeyType].value = getEffectValue();
	updateEffectNodes();
}

void BeautySettingWidget::on_filterValueSlider_valueChanged(int){
	updateColorFilter();
}

void BeautySettingWidget::resetUI() {

	m_currentVideoEffectStatus = 0;

	resetBeautyValueInfo();
	m_beautyBtnGroup->blockSignals(true);
	ui.whiteBtn->setChecked(true);
	ui.whiteBtn->clicked(true);
	m_currentBeautyKeyType = kWhiteKeyType;
	m_currentVideoEffectStatus |= kBeautyPath;
	m_currentVideoEffectStatus |= kReshapePath;
	m_beautyBtnGroup->blockSignals(false);

	m_colorFilterBtnGroup->blockSignals(true);
	ui.filterBtn_1->setChecked(true);
	ui.filterBtn_1->clicked(true);
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

	ui.beautyValueSlider->blockSignals(true);
	ui.beautyValueSlider->setValue(0);
	ui.beautyValueSlider->blockSignals(false);

	ui.filterValueSlider->blockSignals(true);
	ui.filterValueSlider->setValue(0);
	ui.filterValueSlider->blockSignals(false);
}