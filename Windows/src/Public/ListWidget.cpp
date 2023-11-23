#include "ListWidget.h"

ListWidget::ListWidget(QWidget *parent)
{

}

void ListWidget::setItemHeight(int height)
{
    m_itemHeight = height;
    if (m_itemHeight <= 0) {
        m_itemHeight = 20;
    }
}

void ListWidget::autoAdjustHeight()
{
    int count = this->count();
    this->setFixedHeight(count * m_itemHeight + 10);
}
