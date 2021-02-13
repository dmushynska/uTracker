#include "connection.h"
#include "server.h"
#include "database.h"


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