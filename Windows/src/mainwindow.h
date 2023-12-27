#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class QListWidgetItem;
class LogWidget;
class BaseWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    LogWidget *getLogWidget();



private:
    void initUI();
    void initListViews();
    QListWidgetItem *createListItem(int type, QListWidget *&w);
    BaseWidget* createFunctionWidget(int type, QWidget* parent = nullptr);

private:
    Ui::MainWindow *ui;
    QWidget     *m_currentItem = nullptr;
    QString     m_currentText;
    QListWidgetItem *m_lastWidget = nullptr;

};

extern MainWindow * g_mainWindow;
#endif // MAINWINDOW_H
