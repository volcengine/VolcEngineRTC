#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *);

signals:

};

#endif // BASEWIDGET_H
