#include "share_view_container.h"

#include "model.h"
ShareViewContainer::ShareViewContainer(QWidget* parent) : QWidget(parent) {
  lay_ = new FlowLayout(this, 0, 24, 24);
  lay_->setContentsMargins(24, 0, 0, 24);
  setLayout(lay_);

}

ShareViewContainer::~ShareViewContainer() {}

void ShareViewContainer::addItem(const SnapshotAttr& item, QPixmap&& map) {
  auto w = new ShareViewWnd(this);
  w->setName(item.name.c_str());
  if (item.type == SnapshotAttr::kScreen)
    w->setNameColor(QColor(0x40, 0x80, 0xff));
  else
    w->setNameColor(Qt::white);
  w->setPixMap(map);
  share_wnds_.push_back(std::make_pair(w, item));
  connect(w, &ShareViewWnd::sigSelected, this,
          [=, idx = share_wnds_.size() - 1] {
            emit sigItemPressed(share_wnds_[idx].second);
          });
  lay_->addWidget(w);
  int height = lay_->heightForWidth(width());
  setMinimumHeight(height);
  setMaximumHeight(height);
}

void ShareViewContainer::clear() {
  for (auto& pair : share_wnds_) {
    lay_->removeWidget(pair.first);
    pair.first->deleteLater();
  }
}
