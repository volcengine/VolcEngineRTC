#include "UserWidget.h"
#include "ui_UserWidget.h"

#include <QPainter>
#include <QPen>

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
    setUserInfo("room", "uid");
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::setUserInfo(std::string roomid, std::string uid)
{
    m_roomid = roomid;
    m_uid = uid;
    ui->label->setText(QString::fromStdString(m_roomid) + ":" + QString::fromStdString(m_uid));
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

void UserWidget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    QPen pen(QBrush(Qt::black), 1);
    p.setPen(pen);
    p.drawRect(this->rect());
}
