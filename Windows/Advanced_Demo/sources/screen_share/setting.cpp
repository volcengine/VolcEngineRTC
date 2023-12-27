#include "setting.h"

#include <QCloseEvent>
#include <QDateTime>
#include <QDesktopServices>
#include <QItemDelegate>
#include <QListView>
#include <QPainter>
#include <QTimer>

#include "ui_setting.h"
#include "utils.h"

static constexpr char kQss[] =
    "QListView{"
    "background:#fff;"
    "border:1px solid #E5E6EB;"
    "border-radius : 4px;"
    "padding:5px;"
    "color:#1D2129"
    "}"
    "QListView::item{ "
    "color:#1D2129;"
    " height : 32px;"
    "}"
    "QListView::item:hover{"
    "color:#1D2129;"
    "background:#F2F3F8;"
    "}"
    "QListView::item:selected{"
    "color:#1D2129;"
    "background:#F2F3F8;"
    "}";

Q_DECLARE_METATYPE(VideoResolution)

Setting::Setting(QWidget* parent)
    : QDialog(parent), ui(new Ui::Setting) {
  ui->setupUi(this);
  setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
  auto set_combobox = [](QComboBox* cmb) {
    auto list_view = new QListView(cmb);
    list_view->setStyleSheet(kQss);
    cmb->setView(list_view);
    cmb->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint |
                                          Qt::NoDropShadowWindowHint);
    cmb->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
  };
  set_combobox(ui->cmb_camera);
  set_combobox(ui->cmb_fps);
  set_combobox(ui->cmb_resolution);
  set_combobox(ui->cmb_screen_fps);
  set_combobox(ui->cmb_screen_resolution);

  auto set_resoultion_data = [](QComboBox* cmb) {
    std::vector<VideoResolution> resolutions{
        {160, 160}, {320, 180}, {320, 240},  {640, 360},  {480, 480},
        {640, 480}, {960, 540}, {1280, 720}, {1920, 1080}};
    for (auto item : resolutions) {
      QVariant var;
      var.setValue(item);
      cmb->addItem(QString("%1*%2").arg(item.width).arg(item.height), var);
    }
  };

  auto set_fps_data = [](QComboBox* cmb) {
    std::vector<int> vec_fps{15, 20, 24};
    for (auto item : vec_fps) {
      QVariant var;
      var.setValue(item);
      cmb->addItem(QString("%1 fps").arg(item).arg(item), var);
    }
  };

  set_resoultion_data(ui->cmb_resolution);
  set_resoultion_data(ui->cmb_screen_resolution);
  set_fps_data(ui->cmb_fps);
  set_fps_data(ui->cmb_screen_fps);
  initConnect();
}



void Setting::onConfirm() {
  setting_.camera_idx = ui->cmb_camera->currentIndex();
  emit sigSettingChanged(setting_);
  code_ = QDialog::Accepted;
  close();
}

void Setting::onClose() {
  code_ = QDialog::Rejected;
  close();
}

void Setting::onCancel() {
  code_ = QDialog::Rejected;
  close();
}

int Setting::getFpsCmbIdxFromFps(int fps) {
  static std::map<int, int> fps_map{{15, 0}, {20, 1}, {24, 2}};
  auto iter = fps_map.find(fps);
  if (iter != fps_map.end()) return fps_map[fps];
  return 0;
}

void Setting::initConnect() {
  connect(ui->btn_close, &QPushButton::clicked, this, [=] { onClose();
      });

  connect(ui->btn_cancel, &QPushButton::clicked, this, [=] { onCancel(); });

  connect(ui->btn_confirm, &QPushButton::clicked, this, [=] { onConfirm(); });

  connect(ui->sldr_kbps, &SliderWrap::sigPositonChange, this, [=](qreal real) {
    ui->edt_kbps->setText(QString("%1").arg(int(real)));
    setting_.camera.kbps = int(real);
  });
  connect(ui->sldr_screen_kbps, &SliderWrap::sigPositonChange, this,
          [=](qreal real) {
            ui->edt_screen_kbps->setText(QString("%1").arg(int(real)));
            setting_.screen.kbps = int(real);
          });
  connect(
      ui->cmb_resolution, QOverload<int>::of(&QComboBox::currentIndexChanged),
      this, [=](int idx) {
        qreal v =
            qreal(ui->sldr_kbps->getCurValue() - ui->sldr_kbps->getMinValue()) /
            (ui->sldr_kbps->getMaxValue() - ui->sldr_kbps->getMinValue());
        setting_.camera.resolution =
            ui->cmb_resolution->currentData().value<VideoResolution>();
        setting_.camera.kbpsRange =
            utils::getVideoKpbsHit(setting_.camera.resolution);

        ui->sldr_kbps->setMinValue(setting_.camera.kbpsRange.min_kbps);
        ui->sldr_kbps->setMaxValue(setting_.camera.kbpsRange.max_kbps);
        ui->sldr_kbps->setValue(
            int(v * (qlonglong(setting_.camera.kbpsRange.max_kbps) -
                     setting_.camera.kbpsRange.min_kbps) +
                setting_.camera.kbpsRange.min_kbps));
      });

  connect(
      ui->cmb_screen_resolution,
      QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int idx) {
        qreal v = qreal(ui->sldr_screen_kbps->getCurValue() -
                        ui->sldr_screen_kbps->getMinValue()) /
                  (ui->sldr_screen_kbps->getMaxValue() -
                   ui->sldr_screen_kbps->getMinValue());
        setting_.screen.resolution =
            ui->cmb_screen_resolution->currentData().value<VideoResolution>();
        setting_.screen.kbpsRange =
            utils::getVideoKpbsHit(setting_.screen.resolution);
        ui->sldr_screen_kbps->setMinValue(setting_.screen.kbpsRange.min_kbps);
        ui->sldr_screen_kbps->setMaxValue(setting_.screen.kbpsRange.max_kbps);
        ui->sldr_screen_kbps->setValue(
            int(v * (qlonglong(setting_.screen.kbpsRange.max_kbps) -
                     setting_.screen.kbpsRange.min_kbps) +
                setting_.screen.kbpsRange.min_kbps));
      });

  connect(ui->cmb_fps, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, [=](int idx) {
            setting_.camera.fps = ui->cmb_fps->currentData().toInt();
          });

  connect(ui->cmb_screen_fps,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [=](int idx) {
            setting_.screen.fps = ui->cmb_screen_fps->currentData().toInt();
          });

}

void Setting::initView(const SettingModel& model,
                              const std::vector<RtcDevice>& camera_devices) {
  setting_ = model;
  ui->cmb_fps->setCurrentIndex(getFpsCmbIdxFromFps(setting_.camera.fps));
  ui->sldr_kbps->setMinValue(setting_.camera.kbpsRange.min_kbps);
  ui->sldr_kbps->setMaxValue(setting_.camera.kbpsRange.max_kbps);
  ui->sldr_kbps->setValue(setting_.camera.kbps);
  ui->sldr_screen_kbps->setMinValue(setting_.screen.kbpsRange.min_kbps);
  ui->sldr_screen_kbps->setMaxValue(setting_.screen.kbpsRange.max_kbps);
  ui->sldr_screen_kbps->setValue(setting_.screen.kbps);
  ui->cmb_resolution->setCurrentIndex(
      utils::getIdxFromResolution(setting_.camera.resolution));
  ui->cmb_screen_resolution->setCurrentIndex(
      utils::getIdxFromResolution(setting_.screen.resolution));
  ui->cmb_screen_fps->setCurrentIndex(getFpsCmbIdxFromFps(setting_.screen.fps));
  
  ui->cmb_camera->clear();
  int idx = 0;
  for (auto& dc : camera_devices) {
      ui->cmb_camera->addItem(dc.name.c_str());
      ui->cmb_camera->setItemData(idx, QVariant::fromValue(idx),
          Qt::UserRole + 1);
      idx++;
  }

  if (camera_devices.empty()) {
      setting_.camera_idx = -1;
  }
  else if (setting_.camera_idx == -1) {
      ui->cmb_camera->setCurrentIndex(0);
      setting_.camera_idx = 0;
  }
  else {
      ui->cmb_camera->blockSignals(true);
      ui->cmb_camera->setCurrentIndex(setting_.camera_idx);
      ui->cmb_camera->blockSignals(false);
  }
}


Setting::~Setting() { delete ui; }

void Setting::showEvent(QShowEvent* e) {}

bool Setting::eventFilter(QObject* o, QEvent* e) { return false; }

void Setting::closeEvent(QCloseEvent* e) {
  e->ignore();
  if (code_ == QDialog::Accepted) {
    this->accept();
  } else {
    reject();
  }
}
