#include "LoginWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>

/**
 * VolcEngineRTC 音视频通话入口页面
 *
 * 包含如下简单功能：
 * - 该页面用来跳转至音视频通话主页面
 * - 校验房间名和用户名
 * - 展示当前 SDK 使用的版本号 {@link RTCEngine#getSdkVersion()}
 *
 * 有以下常见的注意事项：
 * 1.SDK 对房间名、用户名的限制是：非空且最大长度不超过128位的数字、大小写字母、@ . _  -
 */

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	setAttribute(Qt::WA_StyledBackground);
	parent->installEventFilter(this);

	connect(this, SIGNAL(sigEnterRoom(const QString &, const QString &)), parent, SLOT(slotOnEnterRoom(const QString &, const QString &)));
}

bool LoginWidget::eventFilter(QObject *watched, QEvent *event) 
{
	if (watched == parent())
	{
		auto parentWindow = dynamic_cast<QWidget*>(parent());
		if (parentWindow == nullptr) 
		{
			return false;
		}
		if (event->type() == QEvent::Resize) 
		{	
			//update login geometry
			auto selfRect = this->rect();
			auto parentGem = parentWindow->rect();
			selfRect.moveCenter(parentGem.center());
			setGeometry(selfRect);
		}
	}
	return false;
}

void LoginWidget::on_enterRoomBtn_clicked() 
{
	
	auto checkStr = [=](const QString &typeName, const QString &str)->bool
	{
		if (str.isEmpty()) 
		{
			QMessageBox::warning(this, QStringLiteral(u"提示"), typeName+ QStringLiteral(u"不能为空！"),QStringLiteral(u"确定"));
			return false;
		}

		if (str.size() > 128) 
		{
			QMessageBox::warning(this, QStringLiteral(u"提示"), typeName + QStringLiteral(u"不能超过128个字符！"), QStringLiteral(u"确定"));
			return false;
		}

		QRegExp re("^[a-zA-Z0-9@._-]{1,128}$");
		if (re.exactMatch(str))
		{
			return true;
		}
		else
		{
			QMessageBox::warning(this, QStringLiteral(u"输入不合法"),
				QStringLiteral(u"只支持数字、大小写字母、@._-"),
				QStringLiteral(u"确定"));
			return false;
		}
	};

	if (!checkStr(QStringLiteral(u"房间号"),ui.roomIDLineEdit->text()))
	{
		return;
	}

	if (!checkStr(QStringLiteral(u"用户ID"), ui.userIDLineEdit->text()))
	{
		return;
	}

	emit sigEnterRoom(ui.roomIDLineEdit->text(),ui.userIDLineEdit->text());
}