#include "BaseWidget.h"

#include <QPainter>

BaseWidget::BaseWidget(QWidget *parent)
    : QWidget{parent}
{

}

void BaseWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBrush(Qt::white);
    p.setPen(Qt::white);
    p.drawRect(this->rect());
}
