#include "ListWidget.h"

ListWidget::ListWidget(QWidget *parent)
{
    m_parent = parent;
}


void ListWidget::autoAdjustHeight()
{
    int count = this->count();
    int new_height = count*m_itemHeight;
    this->setFixedHeight(new_height);
}
