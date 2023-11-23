#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();
    void setUserInfo(std::string roomid, std::string uid);
    const std::string getUid();
    const std::string getRoomid();


    void *getWinId();

private:
    void paintEvent(QPaintEvent* event);

private:
    Ui::UserWidget *ui;

    std::string m_uid, m_roomid;
};

#endif // USERWIDGET_H
