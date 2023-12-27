#include "LogWidget.h"
#include "ui_LogWidget.h"

#include <QDateTime>
#include <QScrollBar>
#include "Resources.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
    ui->textEdit->verticalScrollBar()->setStyleSheet(APIDemo::str_qss_scrollstyle);
    //color: var(--text-color-text-2, #42464E);font-family: Menlo;font-size: 12px;font-style: normal;font-weight: 400;line-height: 150%;
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::appendCallback(const QString &str)
{
    ui->textEdit->append("Callback:" + str);
}

void LogWidget::appendAPI(const QString& str)
{
    ui->textEdit->append("API:" + str);
}

void LogWidget::appendAPI(const QStringList list)
{
    for (int i = 0; i < list.size(); i++) {
        ui->textEdit->append("API:" + list[i]);
    }
}
