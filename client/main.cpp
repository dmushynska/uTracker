#include "client.h"

#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    if (argc != 3) {
        qDebug() << "usage ./uTracker [ip] [port]";
        return 1;
    }
    Client client;
    client.doConnect(argv[1], QString(argv[2]).toInt());
    client.testRequestLoop();

    return a.exec();
}
