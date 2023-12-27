#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidget>

class ListWidget : public QListWidget
{
public:
    ListWidget(QWidget* parent = nullptr);
    void autoAdjustHeight();

private:
    int m_itemHeight = 34;
};

#endif // LISTWIDGET_H
