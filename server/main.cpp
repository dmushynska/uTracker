#include "server.h"
#include "database.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    DataBase::getInstance();

    if (argc != 2) {
        qDebug() << "usage ./uTracker_server [port]";
        return 1;
    }

    Server server;
    server.startServer(QString(argv[1]).toInt());

    return a.exec();
}
