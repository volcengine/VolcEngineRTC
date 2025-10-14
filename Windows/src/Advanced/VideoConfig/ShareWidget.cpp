#include "ShareWidget.h"
#include "ui_ShareWidget.h"

#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

#include "Resources.h"
#include "Utils.h"

ShareWidget::ShareWidget(QWidget* parent)
    : QDialog(parent), ui(new Ui::ShareWidget) {
    ui->setupUi(this);
    initConnections();
    initUI();
}

ShareWidget::~ShareWidget() {
    delete ui;
}

void ShareWidget::updateData(bytertc::IRTCEngine* rtc_video, const std::vector<SnapshotAttr>& vec) {
	ui->screen_views->clear();
	ui->window_views->clear();
	for (auto& attr : vec) {
        qDebug() << Q_FUNC_INFO << "size:" << attr.img.size();
		if (attr.type == SnapshotAttr::kScreen) {
			ui->screen_views->addItem(attr);
		}
		else {
			ui->window_views->addItem(attr);
        }
    }

}

void ShareWidget::onBtnOKClicked()
{
    emit sigScreenShare(m_attr);
    this->accept();
}

void ShareWidget::onItemClicked(SnapshotAttr attr)
{
    m_attr = std::move(attr);
}

void ShareWidget::initConnections()
{
    connect(ui->btn_ok, &QPushButton::clicked, this, &ShareWidget::onBtnOKClicked);
    connect(ui->btn_cancel, &QPushButton::clicked, this, [=] { this->reject(); });
    connect(ui->screen_views, &ShareViewContainer::sigItemPressed, this, &ShareWidget::onItemClicked);
    connect(ui->window_views, &ShareViewContainer::sigItemPressed, this, &ShareWidget::onItemClicked);
}

void ShareWidget::initUI()
{
    setWindowTitle(QStringLiteral("选择要共享的桌面或窗体"));
    QList<QWidget*> childWidgets = this->findChildren<QWidget*>();
    // 遍历子控件并设置样式表
    foreach(QWidget * childWidget, childWidgets) {
        QLabel* label = qobject_cast<QLabel*>(childWidget);
        if (label) {
            label->setStyleSheet(APIDemo::str_qss_label_ttile);
        }
//        QLineEdit* edit = qobject_cast<QLineEdit*>(childWidget);
//        if (edit) {
//            edit->setStyleSheet(APIDemo::str_qss_text);
        }

    ui->btn_cancel->setStyleSheet(APIDemo::str_qss_btn1);
    ui->btn_ok->setStyleSheet(APIDemo::str_qss_btn1);
    ui->btn_cancel->setFixedSize(116,28);
    ui->btn_ok->setFixedSize(116, 28);

}
