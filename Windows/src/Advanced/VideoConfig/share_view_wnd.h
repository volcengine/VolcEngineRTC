#pragma once
#include <QWidget>


class ShareViewWnd : public QWidget {
  Q_OBJECT
 public:
  ShareViewWnd(QWidget* parent = nullptr);
  ~ShareViewWnd() = default;

  void setNameColor(const QColor& color);
  void setName(const QString& name);
  QFont getFont();
  void setPixMap(const QPixmap& pixmap);
  void setUnPressed();

 protected:
  void mousePressEvent(QMouseEvent*) override;
  void enterEvent(
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
	 QEnterEvent* event
#else
	  QEvent* event
#endif
) override;
  
  void leaveEvent(QEvent*) override;


 signals:
  void sigSelected();

 protected:
  void paintEvent(QPaintEvent*)override;
 private:
  bool      hover_ = false;
  QPixmap   pixmap_;
  QString   name_;
  QFont     font_;
  QColor    font_color_;
  bool      m_pressed = false;
};
