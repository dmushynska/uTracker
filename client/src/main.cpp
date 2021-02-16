#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "usermanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    UserManager manager(nullptr);
//    qmlRegisterType<Authorization>("Authorization", 1, 0, "Authorization");

    return app.exec();
}
