#include "client.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "usermanager.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    if (argc != 3) {
        qDebug() << "usage ./uTracker [ip] [port]";
        return 1;
    }

    Client client;
    client.doConnect(argv[1], QString(argv[2]).toInt());

    return app.exec();
}
