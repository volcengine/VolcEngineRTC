#pragma once
#include <QWidget>
#include <QGridLayout>

#include "share_view_wnd.h"
#include "ScreenShare.h"

class ShareViewContainer : public QWidget {
  Q_OBJECT
 public:
  explicit ShareViewContainer(QWidget* parent = nullptr);
  ~ShareViewContainer();

  void addItem(const SnapshotAttr& item);
  void clear();

 signals:
  void sigItemPressed(SnapshotAttr item);

 private:
  void paintEvent(QPaintEvent*) override;

 private:
  QGridLayout* lay_;
  int item_count_ = 0;
  std::vector<std::pair<ShareViewWnd*, SnapshotAttr>> share_wnds_;
};
