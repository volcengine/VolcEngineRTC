#include "ListWidget.h"

ListWidget::ListWidget(QWidget *parent)
{

}


void ListWidget::autoAdjustHeight()
{
    int count = this->count();
    this->setFixedHeight(count * m_itemHeight);
}
