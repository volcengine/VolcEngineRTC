#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screen_size = screen->geometry().size();

    MainWindow w;
    int width = screen_size.width() * 0.8;
    int height = screen_size.height() * 0.85;
    w.resize(width, height);
    w.move(screen->geometry().topLeft());
    w.show();

    return app.exec();
}
