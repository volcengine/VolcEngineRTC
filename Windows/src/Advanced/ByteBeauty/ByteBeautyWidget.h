#pragma once
#include <QMainWindow>
#include "ui_ByteBeautyWidget.h"
#include <QButtonGroup>
#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"

namespace bytertc {
	class IRTCVideo;
	class IRTCRoom;
};

namespace Ui {
class ByteBeautyWidget;
}

class ByteBeautyWidget : public BaseWidget
{
    Q_OBJECT
public:
	enum VideoEffectPathType{
		kBeautyPath  = 0x00000001,
		kReshapePath = 0x00000002,
		kStickerpath = 0x00000004,
		kColorFilterPath = 0x00000008,
		kAlgoModelPath =   0x00000010,
	};

	enum BeautyKeyType {
		kWhiteKeyType,
		kSkinGrindingKeyType,
		kBigEyeKeyType,
		kThinFaceKeyType
	};

	enum StickerType{
		kBlackCatGlassStickerType,
		kMakeMoneyCatStickerType,
		kKidMakeupStickerType,
		kLovelyPigStickerType,
		kMuchMoneyStickerType,
		kQixigaobaiStickerType,
		kPigHeadPigEarStickerType,
		kHappyRabbitStickerType
	};

	enum ColorFilterType {
		kPeachColorFilter,
		kClearColorFIlter,
		kNightColorFilter,
		kColdOxygenColorFilter,
	};

	enum CheckLicenseStatus {
		kRuqestLicense,
		kLicenseOk,
		kLicenseError
	};

	struct BeautyValueInfo{
		std::string keyName;
		float value;
	};

	ByteBeautyWidget(QWidget *parent = Q_NULLPTR);
	~ByteBeautyWidget();
	void startCheckLicense();
protected:
    //bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
	void initUI();
	void initData();
	void resetBeautyValueInfo();
	void updateColorFilter();
	void updateEffectNodes();
	float getEffectValue();
	void updateEffectSliderValue();
	float getColorValue();
	QString getLicenseFilePath();
	void requestLicense();
	void setCheckLicenseResultText(CheckLicenseStatus status, const QString &text);
	void saveLicenseFile(const QByteArray &data);
	void checkLicense();
	void resetUI();

    void initRTCVideo();
    void cleanRTCVideo();
	std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);

private:
	void onRoomStateChanged(
        const char* room_id, const char* uid, int state, const char* extra_info);

    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo, int);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);

private slots:
	void on_beautyValueSlider_valueChanged(int);
	void on_filterValueSlider_valueChanged(int);
    void on_checkBtn_clicked(); //请求鉴权
	void on_joinRoom_clicked(); //进房
private:
    Ui::ByteBeautyWidget *ui;
	QButtonGroup          *m_beautyBtnGroup = nullptr;
	QButtonGroup          *m_stickerBtnGroup = nullptr;
	QButtonGroup		  *m_colorFilterBtnGroup = nullptr;
	int					  m_currentVideoEffectStatus = 0;

	QMap<int, QString>      m_videoEffectType2Path;
	QMap<int, BeautyValueInfo>      m_beautyKey2ValueInfo;
	QMap<int, QString>      m_stickerType2Name;
	QMap<int, QString>      m_colorFilerType2Name;
	BeautyKeyType			m_currentBeautyKeyType = kWhiteKeyType;
	QString				    m_currentStickerName;
	QString				    m_currentColorFilter;
	bytertc::IRTCVideo* m_video = nullptr;
	bytertc::IRTCRoom* m_room = nullptr;
	CheckLicenseStatus      m_checkStatus = kRuqestLicense;
	std::unique_ptr<ByteRTCEventHandler> m_handler;
	std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
};
