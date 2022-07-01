#pragma once

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

template <class T>
class SideListWidgetWrap : public QWidget {
  // Q_OBJECT

 public:
  explicit SideListWidgetWrap(QWidget* parent = nullptr) : QWidget(parent) {
    setMouseTracking(true);
    setStyleSheet("background:#101319; border:none;");
    area_ = new QScrollArea(this);
    layout_ = new QVBoxLayout();
    layout_->setAlignment(Qt::AlignTop);
    content_ = new QWidget(this);
    setLayout(new QVBoxLayout());
    setContentsMargins(0, 0, 0, 0);
    content_->setStyleSheet("background:#101319;");
    area_->setWidget(content_);
    content_->setLayout(layout_);
    content_->setContentsMargins(0, 0, 0, 0);
    layout_->setContentsMargins(0, 0, 0, 0);
    layout_->setSpacing(0);
    layout()->addWidget(area_);
    area_->setContentsMargins(0, 0, 0, 0);
    area_->setLayout(new QVBoxLayout());
    area_->setWidgetResizable(true);
    area_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    items_.resize(1000);
  }

  void addWidget(int idx, T* widget) {
    layout_->addWidget(widget);
    items_[idx] = widget;
    items_[idx]->show();
    cnt_ = idx + 1;
    QApplication::processEvents();
  }

  void removeWidget(int idx) {
    layout_->removeWidget(items_[idx]);
    items_[idx]->hide();
  }

  T* widget(int index) { return items_[index]; }

  void resetCount(size_t cnt, std::function<void(T*, int index)>&& doFunc) {
    size_t old_cnt = cnt_;

    if (cnt > items_.size()) {
      items_.resize(items_.size() * 2);
    }
    if (cnt > old_cnt) {
      for (size_t i = old_cnt; i < cnt; ++i) {
        auto ptr = new T(this);
        addWidget(i, ptr);
      }
    } else {
      for (size_t i = cnt; i < old_cnt; ++i) removeWidget(i);
      cnt_ = cnt;
    }
    for (size_t i = 0; i < cnt; i++) {
      doFunc(items_[i], i);
    }
  }

 private:
  std::vector<T*> items_;
  QScrollArea* area_;
  QWidget* content_;
  QVBoxLayout* layout_;
  int cnt_ = 0;
};
