#include "server.h"
#include "database.h"
#include <QCoreApplication>
#include <QDebug>


#include <QFile>
#include <loggingcategories.h>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

QScopedPointer<QFile>   m_logFile;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    DataBase::getInstance();

    QFile::remove("./server_log.txt");
    m_logFile.reset(new QFile("./server_log.txt"));  // run from Clion
    m_logFile.data()->open(QFile::Append | QFile::Text);
// Устанавливаем обработчик. To restore the message handler, call qInstallMessageHandler(0).
//    qInstallMessageHandler(messageHandler);
    qInfo(logInfo()) << "macOS version" << QSysInfo::macVersion();


    if (argc != 2) {
        qDebug() << "usage ./uTracker_server [port]";
        return 1;
    }

    Server server(QString(argv[1]).toInt());
    if (!server.startServer()) {
        exit(EXIT_FAILURE);
    }

    return a.exec();
}


void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(m_logFile.data());

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    switch (type) {
        case QtDebugMsg:
            out << QString(" Debug: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
        case QtInfoMsg:
            out << QString(" Info: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
//            out << QString(" Info: %1)\n").arg(localMsg.constData());
            break;
        case QtWarningMsg:
            out << QString(" Warning: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
        case QtCriticalMsg:
            out << QString(" Critical: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
        case QtFatalMsg:
            out << QString(" Fatal: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
    }
    out.flush();    // Очищаем буферизированные данные
}
