#include "share_screen_widget.h"
#include "ui_share_screen_widget.h"
#include "utils.h"

ShareScreenWidget::ShareScreenWidget(QWidget* parent)
	: QDialog(parent), ui(new Ui::ShareScreenWidget) {
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	ui->screen_views->setMinimumWidth(width());
	ui->window_views->setMinimumWidth(width());
	ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	connect(ui->btn_close, &QPushButton::clicked, this, [=] { this->reject(); });
	connect(ui->screen_views, &ShareViewContainer::sigItemPressed, this,
		[=](SnapshotAttr attr) {
			/*vrd::MeetingSession::instance().startScreenShare([=](int code) {
			  if (code != 200) {
				WarningTips::showTips(
					QString("屏幕共享失败err:%1").arg(code), TipsType::kWarning,
					meeting::PageManager::currentWidget(), 2000);
				return;
			  }
			  auto r = meeting::DataMgr::instance().room();
			  r.screen_shared_uid = meeting::DataMgr::instance().user_id();
			  meeting::DataMgr::instance().setRoom(std::move(r));
			  std::vector<void*> excluded;
			  MeetingRtcEngineWrap::instance().startScreenCapture(
				  attr.source_id, excluded);
			});*/
			emit sigScreenShare(attr);
			this->accept();
		});

	connect(ui->window_views, &ShareViewContainer::sigItemPressed, this,
		[=](SnapshotAttr attr) {
			/*vrd::MeetingSession::instance().startScreenShare([=](int code) {
			  if (code != 200) {
				WarningTips::showTips(
					QString("屏幕共享失败err:%1").arg(code), TipsType::kWarning,
					meeting::PageManager::currentWidget(), 2000);
				return;
			  }
			  auto r = meeting::DataMgr::instance().room();
			  r.screen_shared_uid = meeting::DataMgr::instance().user_id();
			  meeting::DataMgr::instance().setRoom(std::move(r));
			  MeetingRtcEngineWrap::instance().startScreenCaptureByWindowId(
				  attr.source_id);
			});*/
			emit sigWndShare(attr);
			this->accept();
		});

	connect(ui->btn_close, &QPushButton::clicked, this, [=] {
		emit sigClose();
		});
}

ShareScreenWidget::~ShareScreenWidget() { delete ui; }

void ShareScreenWidget::updateData(bytertc::IRtcEngine* engine, const std::vector<SnapshotAttr>& vec) {
	ui->screen_views->clear();
	ui->window_views->clear();
	for (auto& attr : vec) {
		if (attr.type == SnapshotAttr::kScreen) {
			ui->screen_views->addItem(attr,
				std::move(utils::getThumbnail(engine,
					attr.type, attr.source_id, 160, 90)));
		}
		else {
			ui->window_views->addItem(attr,
				std::move(utils::getThumbnail(engine,
					attr.type, attr.source_id, 160, 90)));
		}
	}
}
