#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();

    MainWindow w;
    w.resize(screen->availableSize().width()*0.6, screen->availableSize().height()*0.8);
    w.show();

    return app.exec();
}
