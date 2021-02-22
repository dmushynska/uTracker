#include "client.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "usermanager.h"
#include <QFile>
#include <loggingcategories.h>

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

QScopedPointer<QFile> m_logFile;

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
//    UserManager manager(nullptr);

    QFile::remove("./client_log.txt");
    m_logFile.reset(new QFile("./client_log.txt"));  // run from Clion
    m_logFile.data()->open(QFile::Append | QFile::Text);
// Устанавливаем обработчик. To restore the message handler, call qInstallMessageHandler(0).
//    qInstallMessageHandler(messageHandler);
    qInfo(logInfo()) << "macOS version" << QSysInfo::macVersion();

    if (argc != 3) {
        qDebug() << "usage ./uTracker [ip] [port]";
        return 1;
    }
    Client client(argv[1], QString(argv[2]).toInt());
    client.doConnect();
    client.testRequestLoop();

//    return 0;
    return app.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QTextStream out(m_logFile.data());

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    QByteArray localMsg = msg.toLocal8Bit();
    const char* file = context.file ? context.file : "";
    const char* function = context.function ? context.function : "";

    switch (type) {
        case QtDebugMsg:out
                    << QString(" Debug: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(
                            function);
            break;
        case QtInfoMsg:out
                    << QString(" Info: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(
                            function);
//            out << QString(" Info: %1)\n").arg(localMsg.constData());
            break;
        case QtWarningMsg:out
                    << QString(" Warning: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(
                            function);
            break;
        case QtCriticalMsg:out
                    << QString(" Critical: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(
                            function);
            break;
        case QtFatalMsg:out
                    << QString(" Fatal: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(
                            function);
            break;
    }
    out.flush();    // Очищаем буферизированные данные
}