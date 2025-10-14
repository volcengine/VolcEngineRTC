#include "share_view_container.h"

#include <QDebug>
#include <QPainter>

ShareViewContainer::ShareViewContainer(QWidget* parent) : QWidget(parent) {
    lay_ = new QGridLayout(this);
    lay_->setContentsMargins(12, 12, 12, 12);
    lay_->setAlignment(Qt::AlignCenter);
    lay_->setVerticalSpacing(2);
    setLayout(lay_);
}

ShareViewContainer::~ShareViewContainer() {}

void ShareViewContainer::addItem(const SnapshotAttr& item) {
    auto w = new ShareViewWnd(this);
    w->setName(item.name.c_str());
    if (item.type == SnapshotAttr::kScreen) {
        w->setNameColor(QColor(0x40, 0x80, 0xff));
    }
    else {
        w->setNameColor(Qt::white);
    }
    w->setPixMap(QPixmap::fromImage(item.img));

    share_wnds_.push_back(std::make_pair(w, item));
    connect(w, &ShareViewWnd::sigSelected, this,
        [=, idx = share_wnds_.size() - 1]{
        emit sigItemPressed(share_wnds_[idx].second);
        w->setNameColor(Qt::blue);

        for (auto m : share_wnds_) {
            if (m.first != w) {
                m.first->setUnPressed();
            }
        }
        });

    
    lay_->addWidget(w, item_count_ / 4,  item_count_ % 4);
    ++item_count_;
}

void ShareViewContainer::clear() {
    for (auto& pair : share_wnds_) {
        lay_->removeWidget(pair.first);
        pair.first->deleteLater();
    }
}

void ShareViewContainer::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBrush(Qt::blue);
    p.fillRect(this->rect(), QColor("#F0F0F0"));
}
