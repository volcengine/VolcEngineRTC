#include "BaseWidget.h"

#include <QPainter>
#include "mainwindow.h"


BaseWidget::BaseWidget(QWidget *parent)
    : QWidget{parent}
{
    m_logwidget = g_mainWindow->getLogWidget();
}

void BaseWidget::appendCallback(const QString &str)
{
    if (m_logwidget) {
        m_logwidget->appendCallback(str);
    }
}

void BaseWidget::appendAPI(const QString &str)
{
    if (m_logwidget) {
        m_logwidget->appendAPI(str);
    }
}

void BaseWidget::appendAPI(const QStringList list)
{
    if (m_logwidget) {
        m_logwidget->appendAPI(list);
    }
}

