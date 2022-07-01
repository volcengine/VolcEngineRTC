#ifndef MEETING_SEETING_H
#define MEETING_SEETING_H

#include <QDialog>
#include "model.h"

namespace Ui {
class Setting;
}

class Setting : public QDialog {
  Q_OBJECT

 public:
  explicit Setting(QWidget* parent = nullptr);
  ~Setting();

  void initView(
      const SettingModel& model,const std::vector<RtcDevice>& camera_devices);

 protected:
  void showEvent(QShowEvent* e) override;
  bool eventFilter(QObject* o, QEvent* e) override;
  void closeEvent(QCloseEvent *e)override;


  signals:
  void sigSettingChanged(SettingModel model);

 public slots:
  void onConfirm();
  void onClose();
  void onCancel();

 private:
  int getFpsCmbIdxFromFps(int fps);
  void initConnect();

 private:
  QDialog::DialogCode code_;
  SettingModel setting_;
  Ui::Setting* ui;
};

#endif  // MEETING_SEETING_H
