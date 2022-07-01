#include "slider_wrap.h"
#include <qpainter.h>
#include <QMouseEvent>
SliderWrap::SliderWrap(QWidget* parent) : QWidget(parent) {
  show();
  m_curPoint = QPoint(11, 0);
  m_circleBorderSize = 2;
  m_circleRadious = (this->height() - 2 * m_circleBorderSize) / 5;
  m_circleBorderColor = QColor(0x00, 0x73, 0xFF);
  m_circleColor = QColor(0xff, 0xff, 0xff);
  m_frontColor = QColor(0xE5, 0xE8, 0xEF);
  m_bkColor = QColor(0x16, 0x64, 0xff);
  m_maxValue = 100;
  m_minValue = 0;
}

SliderWrap::~SliderWrap() {}

void SliderWrap::setMaxValue(qreal value) {
  m_maxValue = value;
}

void SliderWrap::setMinValue(qreal value) {
  m_minValue = value;
}

void SliderWrap::setValue(qreal value) {
  if (m_curValue != value)
    emit sigPositonChange(value);
  m_curValue = value;
  int posX = (this->width() - (m_circleBorderSize + m_circleRadious) * 2) *
                 (m_curValue - m_minValue) / (m_maxValue - m_minValue) +
             m_circleRadious + m_circleBorderSize;
  m_curPoint = QPoint(posX, 0);
  update();
}

void SliderWrap::setBkColor(QColor color) {
  m_bkColor = color;
}

void SliderWrap::setFrontColor(QColor color) {
  m_frontColor = color;
}

void SliderWrap::setCircleColor(QColor color) {
  m_circleColor = color;
}

void SliderWrap::setCircleBorder(int size, QColor color) {
  m_circleBorderSize = size;
  m_circleBorderColor = color;
}

qreal SliderWrap::getCurValue() const {
  return m_curValue;
}

qreal SliderWrap::getMinValue() const {
  return m_minValue;
}

qreal SliderWrap::getMaxValue() const {
  return m_maxValue;
}

void SliderWrap::paintEvent(QPaintEvent* e) {
  QPainter painter(this);
  painter.setBrush(m_bkColor);
  painter.setPen(Qt::NoPen);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.drawRoundedRect(
      QRect(m_circleRadious + m_circleBorderSize,
            this->height() / 2 - m_circleBorderSize,
            m_curPoint.x() - m_circleRadious + m_circleBorderSize,
            this->height() / 5),
      1, 1);
  painter.setBrush(m_frontColor);
  painter.drawRoundedRect(
      QRect(
          m_curPoint.x(), this->height() / 2 - m_circleBorderSize,
          this->width() - m_curPoint.x() - m_circleRadious - m_circleBorderSize,
          this->height() / 5),
      1, 1);
  painter.setBrush(m_circleBorderColor);
  painter.drawEllipse(QPointF(m_curPoint.x(), (this->height()) / 2),
                      m_circleRadious + m_circleBorderSize,
                      m_circleRadious + m_circleBorderSize);
  painter.setBrush(m_circleColor);
  painter.drawEllipse(QPointF(m_curPoint.x(), (this->height()) / 2),
                      m_circleRadious, m_circleRadious);
}

void SliderWrap::mousePressEvent(QMouseEvent* event) {
  getCurPoint(event);
}

void SliderWrap::mouseMoveEvent(QMouseEvent* event) {
  getCurPoint(event);
}

void SliderWrap::getCurPoint(QMouseEvent* event) {
  if (event->pos().x() < m_circleRadious + m_circleBorderSize) {
    m_curPoint = QPoint(m_circleRadious + m_circleBorderSize, 0);
  } else if (event->pos().x() >
             this->width() - m_circleRadious - m_circleBorderSize) {
    m_curPoint =
        QPoint(this->width() - m_circleRadious - m_circleBorderSize, 0);
  } else {
    m_curPoint = event->pos();
  }
  update();
  m_curValue =
      (qreal)(m_curPoint.x() - m_circleRadious - m_circleBorderSize) /
          (this->width() - 2 * (m_circleRadious + m_circleBorderSize)) *
          (m_maxValue - m_minValue) +
      m_minValue;
  emit sigPositonChange(m_curValue);
}