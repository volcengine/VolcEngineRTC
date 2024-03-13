#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include "LogWidget.h"

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);

    void appendCallback(const QString &str);
    void appendAPI(const QString &str);
    void appendAPI(const QStringList list);


signals:

private:
    LogWidget *m_logwidget = nullptr;

};

#endif // BASEWIDGET_H
