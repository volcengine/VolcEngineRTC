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
			emit sigScreenShare(attr);
			this->accept();
		});

	connect(ui->window_views, &ShareViewContainer::sigItemPressed, this,
		[=](SnapshotAttr attr) {
			emit sigWndShare(attr);
			this->accept();
		});

	connect(ui->btn_close, &QPushButton::clicked, this, [=] {
		emit sigClose();
		});
}

ShareScreenWidget::~ShareScreenWidget() { delete ui; }

void ShareScreenWidget::updateData(bytertc::IRTCVideo* rtc_video, const std::vector<SnapshotAttr>& vec) {
	ui->screen_views->clear();
	ui->window_views->clear();
	for (auto& attr : vec) {
		if (attr.type == SnapshotAttr::kScreen) {
			ui->screen_views->addItem(attr,
				std::move(utils::getThumbnail(rtc_video,
					attr.type, attr.source_id, 160, 90)));
		}
		else {
			ui->window_views->addItem(attr,
				std::move(utils::getThumbnail(rtc_video,
					attr.type, attr.source_id, 160, 90)));
		}
	}
}
