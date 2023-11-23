#include "LogWidget.h"
#include "ui_LogWidget.h"

#include <QDateTime>

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
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
