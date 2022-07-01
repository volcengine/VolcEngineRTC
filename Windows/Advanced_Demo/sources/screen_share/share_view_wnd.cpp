#include "share_view_wnd.h"

#include <QPainter>

#include "utils.h"
static constexpr int kBorderSize = 4;
static constexpr int kViewWidth = 160;
static constexpr int kViewHegith = 90;
static constexpr int kFontSize = 14;
static constexpr int kSpacing = 8;
static constexpr int kFontHeight = 22;

ShareViewWnd::ShareViewWnd(QWidget* parent) : QWidget(parent) {
  setFixedSize(kBorderSize * 2 + kViewWidth,
               kBorderSize * 2 + kViewHegith + kSpacing + kFontHeight);
  // setMouseTracking(true);
  font_ = QFont("Microsoft YaHei", kFontSize);
  hover_ = false;
}

void ShareViewWnd::setNameColor(const QColor& color) { font_color_ = color; }

void ShareViewWnd::setName(const QString& str) { name_ = str; }

QFont ShareViewWnd::getFont() { return font_; }

void ShareViewWnd::setPixMap(const QPixmap& pixmap) { pixmap_ = pixmap; }

void ShareViewWnd::mousePressEvent(QMouseEvent*) { emit sigSelected(); }

void ShareViewWnd::enterEvent(QEvent*) {
  hover_ = true;
  update();
}

void ShareViewWnd::leaveEvent(QEvent*) {
  hover_ = false;
  update();
}

void ShareViewWnd::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.setPen(Qt::NoPen);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setBrush(QBrush(QColor(0xff, 0xff, 0xff)));
  painter.drawRect(0, 0, kViewWidth + 2 * kBorderSize,
                   kViewHegith + 2 * kBorderSize);
  painter.drawPixmap(QPoint(kBorderSize, kBorderSize), pixmap_);
  painter.setFont(font_);
  if (hover_) {
    painter.setBrush(QColor(0, 0, 0, 128));
    painter.drawRect(kBorderSize, kBorderSize, kViewWidth, kViewHegith);
    painter.setPen(Qt::white);
    painter.drawText(QRect(kBorderSize, kBorderSize, kViewWidth, kViewHegith),
                     "点击开始共享", QTextOption(Qt::AlignCenter));
  }
  painter.setPen(QPen(font_color_));
  constexpr QRect rc = QRect(0, kViewHegith + 2 * kBorderSize + kSpacing,
                             kViewWidth + 2 * kBorderSize, kFontHeight);
  painter.drawText(rc, utils::elideText(font_, name_, rc.width()),
                   QTextOption(Qt::AlignCenter));
}
