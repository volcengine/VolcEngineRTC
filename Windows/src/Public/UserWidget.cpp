#include "UserWidget.h"
#include "ui_UserWidget.h"

#include <QPainter>
#include <QPen>
#include <QPalette>
#include <QVBoxLayout>

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::setUserInfo(std::string roomid, std::string uid)
{
    m_roomid = roomid;
    m_uid = uid;
    ui->label_user_id->setText("room:" + QString::fromStdString(m_roomid) + ",uid:" + QString::fromStdString(m_uid));
}

const std::string UserWidget::getUid()
{
    return m_uid;
}

const std::string UserWidget::getRoomid()
{
    return m_roomid;
}

void *UserWidget::getWinId()
{
    return (void*)ui->widget->winId();
}


