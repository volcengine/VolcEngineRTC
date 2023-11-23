#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class QListWidgetItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    void initUI();
    void initListViews();
    QListWidgetItem *createListItem(int type, QListWidget *&w);

private:
    Ui::MainWindow *ui;
    QWidget     *m_currentItem = nullptr;
    QString     m_currentText;

};
#endif // MAINWINDOW_H
