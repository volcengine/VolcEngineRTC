#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();

    MainWindow w;

    w.show();

    return app.exec();
}
