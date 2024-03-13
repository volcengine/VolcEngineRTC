#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = nullptr);
    ~LogWidget();
    void appendCallback(const QString &str);
    void appendAPI(const QString &str);
    void appendAPI(const QStringList list);

private slots:
    void onBtnClearClicked();

private:
    Ui::LogWidget *ui;
};

#endif // LOGWIDGET_H
