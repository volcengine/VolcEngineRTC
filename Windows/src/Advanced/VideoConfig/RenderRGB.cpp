#include "RenderRGB.h"
#include <QPainter>
#include <QDebug>

RenderRGB::RenderRGB(QWidget *parent)
    : QWidget{parent}
{

}

void RenderRGB::setImage(const QImage &img)
{
    m_img = img;
    update();
}

void RenderRGB::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (!m_img.isNull()){
        p.drawImage(rect(), m_img);
    }
}
