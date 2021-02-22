#include <QSslConfiguration>
#include <QFile>
#include "connection.h"
#include "server.h"
#include "loggingcategories.h"
#include "database.h"

Connection::Connection(qintptr socket_id, std::shared_ptr<QSslSocket> ssl_socket, QObject* parent) :QObject(
        parent), m_socket_id(socket_id), m_ssl_socket(ssl_socket)
{
    qDebug(logDebug()) << "Connection constructor";
    connect(m_ssl_socket.get(), &QSslSocket::encrypted, this, &Connection::read_from_socket);
//        connect(m_ssl_socket.get(), &QSslSocket::modeChanged, this, &Connection::modeChanged);
//        connect(m_ssl_socket.get(), &QSslSocket::peerVerifyError, this, &Connection::printError);
    connect(m_ssl_socket.get(), QOverload<const QList<QSslError>&>::of(&QSslSocket::sslErrors),
            [=](const QList<QSslError>& errors) {
              for (auto err : errors) {
                  qDebug(logDebug()) << err.errorString();
              }
            });
    connect(m_ssl_socket.get(), &QSslSocket::disconnected, this, &Connection::disconnected);
    connect(this, &Connection::sendResponse, this, &Connection::write_to_socket);
}

Connection::~Connection()
{
//    qobject_cast<Server *>(m_parent)->deleteConnection(this);
}

void Connection::write_to_socket(const QByteArray& data)
{
    qDebug(logDebug()) << "Connection::writeToSocket";

    QByteArray buffer;
    m_ssl_socket->write(buffer.setNum(data.size()));
    m_ssl_socket->write("\n" + data);
}

void Connection::disconnected()
{
    qDebug("Client Disconnected from Connection");
    emit disconnectSocket(m_socket_id);
//    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
//    clientSocket->deleteLater();
}

void Connection::read_from_socket()
{
    /*
     * need read all json, parse and send to task
     */
    qInfo(logInfo()) << " Connection::Read -  from client";

    while (!m_ssl_socket->atEnd()) {
        QByteArray size = m_ssl_socket->readLine();
        m_task = m_ssl_socket->read(size.toInt());
        if (!m_task.isNull()) {
            qDebug(logDebug()) << "new line \t\n" << m_task.toStdString().data();
        }
    }
    qDebug(logDebug()) << "====================";
//    qobject_cast<Server *>(m_parent)->setNewTask(this);
    emit new_task(this);

/*
 * +++
    while (clientSocket->canReadLine()) {
//        qDebug(logDebug) << "read while";
        char buf[1024];
        qint64 lineLength = clientSocket->readLine(buf, sizeof(buf));
        if (lineLength != -1) {
           qDebug(logDebug()) << buf;
        }
*/
}

void Connection::print_errors(QList<QSslError> errors) const
{
    qDebug(logDebug()) << "printErrors" << m_ssl_socket->errorString();

    for (auto error : errors) {
        qDebug(logDebug()) << error.errorString() << "\n";
    }
}
void Connection::print_error(const QSslError& error) const
{
    qDebug(logDebug()) << "error peer " << error;
}
void Connection::mode_changed(QSslSocket::SslMode mode)
{
    qDebug(logDebug()) << "ssl mode  " << mode;
    m_ssl_socket->startServerEncryption();  // initiates the SSL handshake
    print_errors(m_ssl_socket->sslHandshakeErrors());
}


/*
Connection::Connection(QObject *parent) : QObject(parent) {
    m_parent = parent;
    m_socket = new QTcpSocket(this);
}

Connection::~Connection() {
    m_socket->abort();
    delete m_socket;
    qobject_cast<Server *>(m_parent)->deleteConnection(this);
}

void Connection::doConnect(qintptr handle) {
    m_socket->setSocketDescriptor(handle);

    connect(m_socket, &QTcpSocket::disconnected,this, &Connection::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Connection::readyRead);
    connect(this, &Connection::sendResponse, this, &Connection::writeToSocket);
}

QByteArray Connection::getTask() const {
    return m_task;
}

void Connection::writeToSocket(const QByteArray &data) {
    QByteArray buffer;
    m_socket->write(buffer.setNum(data.size()));
    m_socket->write("\n" + data);
}

void Connection::disconnected() {
    this->deleteLater();
}

void Connection::readyRead() {
    while (!m_socket->atEnd()) {
        QByteArray size = m_socket->readLine();
        m_task = m_socket->read(size.toInt());
        qobject_cast<Server *>(m_parent)->setNewTask(this);
    }
}

 */