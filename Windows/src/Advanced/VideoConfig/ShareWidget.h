#ifndef SHARE_WIDGET_H
#define SHARE_WIDGET_H

#include <QDialog>
#include "bytertc_engine.h"
#include "ScreenShare.h"


namespace Ui {
class ShareWidget;
}


class ShareWidget : public QDialog {
  Q_OBJECT

 public:

  explicit ShareWidget(QWidget *parent = nullptr);
  ~ShareWidget();

  void updateData(bytertc::IRTCEngine* rtc_video,const std::vector<SnapshotAttr>& vec);

  private slots:
      void onBtnOKClicked();
      void onItemClicked(SnapshotAttr attr);

  private:
      void initConnections();
      void initUI();


 signals:
  void sigScreenShare(SnapshotAttr attr);
  void sigClose();

 private:
  Ui::ShareWidget *ui;

     SnapshotAttr  m_attr;
};

#endif  // SHARE_WIDGET_H
