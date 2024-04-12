#pragma once
#include <QWidget>
#include <QColor>
class SliderWrap: public QWidget {
 public:
  Q_OBJECT

 public:
  SliderWrap(QWidget* parent);
  virtual ~SliderWrap();
  void setMaxValue(qreal value);
  void setMinValue(qreal value);
  void setValue(qreal value);

  void setBkColor(QColor color);
  void setFrontColor(QColor color);
  void setCircleColor(QColor color);
  void setCircleBorder(int size,QColor color);
  qreal getCurValue() const;
  qreal getMinValue() const;
  qreal getMaxValue() const;


 protected:
  void paintEvent(QPaintEvent *e);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

 private:
  void getCurPoint(QMouseEvent *event);

 signals:
  void sigPositonChange(qreal curValue);

 private:
  int m_circleRadious;
  QColor m_bkColor;
  QColor m_circleColor;
  QColor m_frontColor;
  QColor m_circleBorderColor;

  QPoint m_curPoint;
  qreal m_maxValue;
  qreal m_circleBorderSize;
  qreal m_minValue;
  qreal m_curValue;
};