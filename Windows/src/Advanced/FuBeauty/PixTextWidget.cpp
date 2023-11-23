#include "PixTextWidget.h"
#include "ui_PixTextWidget.h"

#include <QPainter>

PixTextWidget::PixTextWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PixTextWidget)
{
    ui->setupUi(this);
    m_txtVisible = true;
    m_pressed = false;
    setAutoFillBackground(true);
}

PixTextWidget::~PixTextWidget()
{
    delete ui;
}

void PixTextWidget::setText(const QString &txt)
{
    if (txt.isEmpty()) {
        m_txtVisible = false;
    }
    else {
        m_txtVisible = true;
    }
    m_text = txt;
    update();
}

void PixTextWidget::setTextVisuable(bool visual)
{
    m_txtVisible = visual;
}

void PixTextWidget::setPixUrl(const QString &url)
{
    m_pixUrl = url;
    update();
}

void PixTextWidget::setUnClicked()
{
    m_pressed = false;
    update();
}

const QString PixTextWidget::getText()
{
    return m_text;
}

const QString PixTextWidget::getPixmapUrl()
{
    return m_pixUrl;
}

void PixTextWidget::mousePressEvent(QMouseEvent *)
{
    m_pressed = true;
    emit clicked();
    update();
}

void PixTextWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBackgroundMode(Qt::TransparentMode);
    QPixmap pix(m_pixUrl);
    int width = this->width();
    int height = this->height();


    if (m_pressed) {
        p.setBrush(QBrush(QColor("#7fbbe8")));
        p.setPen((QColor("#7fbbe8")));
        p.drawRect(QRect(0, 0, this->width(), this->height()));
    } else {
        p.setBrush(QBrush(QColor("#ffffff")));
        p.setPen(QColor("#ffffff"));
        p.drawRect(QRect(0, 0, this->width(), this->height()));
    }

    if (m_txtVisible) { //有文字
        height = height - 30;
        p.setPen(Qt::black);
        p.drawText(0, height, width, 30, Qt::AlignHCenter, m_text);
    }
    int minv = qMin(width, height);
    pix = pix.scaled(minv, minv);
    p.drawPixmap(QRect((width - minv)/2, (height-minv)/2, minv, minv), pix);


}
