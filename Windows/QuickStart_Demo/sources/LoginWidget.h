#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LoginWidget.h"

class LoginWidget : public QWidget {
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = Q_NULLPTR);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    //void paintEvent(QPaintEvent *event)override;
private
    slots:
            void on_enterRoomBtn_clicked();
    signals:
            void sigEnterRoom(const QString &, const QString &);
private:
    Ui::LoginForm ui;
};
