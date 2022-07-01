#ifndef SHARE_SCREEN_WIDGET_H
#define SHARE_SCREEN_WIDGET_H

#include <QDialog>
#include "model.h"
#include "bytertc_engine_interface.h"

namespace Ui {
class ShareScreenWidget;
}

class ShareScreenWidget : public QDialog {
  Q_OBJECT

 public:
  explicit ShareScreenWidget(QWidget *parent = nullptr);
  ~ShareScreenWidget();

  void updateData(bytertc::IRtcEngine* engine,const std::vector<SnapshotAttr>& vec);
 signals:
  void sigScreenShare(SnapshotAttr attr);
  void sigWndShare(SnapshotAttr attr);
  void sigClose();

 private:
  Ui::ShareScreenWidget *ui;
};

#endif  // SHARE_SCREEN_WIDGET_H
