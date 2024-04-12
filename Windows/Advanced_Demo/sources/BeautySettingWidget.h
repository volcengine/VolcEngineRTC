﻿#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BeautySettingWidget.h"
#include <QButtonGroup>

class RoomMainWidget;

class BeautySettingWidget : public QWidget {
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

    BeautySettingWidget(RoomMainWidget *parent = Q_NULLPTR);
	void startCheckLicense();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
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
private slots:
	void on_closeBtn_clicked();
	void on_beautyValueSlider_valueChanged(int);
	void on_filterValueSlider_valueChanged(int);
private:
    Ui::BeautySettingForm ui;
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
	RoomMainWidget *		m_roomMainWidget = nullptr;
};