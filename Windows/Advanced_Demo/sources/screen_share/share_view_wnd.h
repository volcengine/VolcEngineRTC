#pragma once
#include <QWidget>

#include "model.h"

class ShareViewWnd : public QWidget {
  Q_OBJECT
 public:
  ShareViewWnd(QWidget* parent = nullptr);
  ~ShareViewWnd() = default;

  void setNameColor(const QColor& color);
  void setName(const QString& name);
  QFont getFont();
  void setPixMap(const QPixmap& pixmap);

 protected:
  void mousePressEvent(QMouseEvent*) override;
  void enterEvent(QEvent*) override;
  void leaveEvent(QEvent*) override;
 signals:
  void sigSelected();

 protected:
  void paintEvent(QPaintEvent*)override;
 private:
  bool hover_;
  QPixmap pixmap_;
  QString name_;
  QFont font_;
  QColor font_color_;
};