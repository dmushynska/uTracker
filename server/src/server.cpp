#include <QFile>
#include <QSslConfiguration>

#include "server.h"
#include "loggingcategories.h"

Server::Server(quint16 _port, QObject* parent) :QTcpServer(parent), m_port(_port)
{
    m_mutex = new QMutex();
    m_pool = new QThreadPool(this);
    m_pool->setMaxThreadCount(MAX_THREAD_COUNT);
    if (!setSsslConfig()) {
        exit(1);
    }
}

Server::~Server()
{
    m_mutex->unlock();
    delete m_pool;
    delete m_mutex;
//    m_connections.clear();
}

bool Server::startServer()
{
    qInfo(logInfo()) << "Server::startServer";
    if (!listen(QHostAddress::LocalHost, m_port)) {
        qWarning(logWarning) << "Server did not start!";
        return false;
    }
    connect(this, &Server::newConnection, this, &Server::link);
    return true;
}

//void Server::incomingConnection(qintptr handle)
//{
//    Connection* newConnection = new Connection(this);
//    newConnection->doConnect(handle);
//
//    m_connections.insert(newConnection, nullptr);
//}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qInfo(logInfo()) << "new incomingConnection socketDescriptor = " << socketDescriptor;

    std::shared_ptr<QSslSocket> sslSocket = std::make_shared<QSslSocket>();
    if (sslSocket->setSocketDescriptor(socketDescriptor)) {
        setSocket(sslSocket);

        Connection* newConnection = new Connection(socketDescriptor, sslSocket);
        connect(sslSocket.get(), &QSslSocket::encrypted, this, &Server::connectSuccess);
        connect(newConnection, &Connection::disconnectSocket, this, &Server::deleteConnection);
        connect(newConnection, &Connection::new_task, this, &Server::setNewTask2);
        m_map_connections[socketDescriptor] = newConnection;
        sslSocket->startServerEncryption();
        addPendingConnection(sslSocket.get());
    }
    else {
        qDebug(logDebug()) << "setSocketDescriptor  -  false";
    }
}

void Server::deleteConnection(qintptr id)
{
//    m_connections.erase(m_connections.find(ptr));
    m_map_connections.remove(id);
    qDebug(logDebug()) << "remove id " << id;
}

void Server::link()
{
    qDebug(logDebug()) << "void Server::link";
    QTcpSocket* clientSocket;

    clientSocket = nextPendingConnection();
    qDebug(logDebug()) << "nextPendingConnection = " << clientSocket->socketDescriptor();
    auto connection = m_map_connections[clientSocket->socketDescriptor()];
    connect(clientSocket, &QSslSocket::readyRead, connection, &Connection::read_from_socket);
//    connect(clientSocket, &QTcpSocket::readyRead, clientSocket, &Connection::Read);
//    connect(clientSocket, &QTcpSocket::disconnected, this, &SslServer::disconnected);
}


//void Server::setNewTask(Connection* ptr)
//{
//    Runnable* task = new Runnable(ptr);
//
//    task->setAutoDelete(true);
//    task->setMutex(m_mutex);
//    task->setTask(ptr->getTask());
//    task->setMap(&m_connections);
//    m_pool->start(task);
//}

void Server::setNewTask2(Connection* ptr)
{
    qDebug(logDebug()) << "Server::setNewTask";
    Runnable* task = new Runnable(ptr);
    task->setAutoDelete(true);
    task->setMutex(m_mutex);
    task->setTask(ptr->getTask());
//    task->setMap(&m_connections);
    m_pool->start(task);
}

/*
 * Apply config to income sockets
 * */

bool Server::setSocket(std::shared_ptr<QSslSocket> m_ssl_socket)
{
    m_ssl_socket->setSocketOption(QAbstractSocket::KeepAliveOption, true);
    m_ssl_socket->setSslConfiguration(*m_config);
    qDebug(logDebug) << "set setSslConfiguration true";
    return true;
}

/*
 * Create ssl config
 * */

bool Server::setSsslConfig()
{
    qInfo(logInfo()) << " Server::setSsslConfig";
    QByteArray key;
    QByteArray cert;
    QByteArray root;
    QSslConfiguration config;

    QFile file_key("./CA/server.key");
    if (file_key.open(QIODevice::ReadOnly)) {
        key = file_key.readAll();
        file_key.close();
    }
    else {
        qDebug() << "error key " << file_key.errorString();
        return false;
    }

    QFile file_cert("./CA/server.pem");
    if (file_cert.open(QIODevice::ReadOnly)) {
        cert = file_cert.readAll();
        file_cert.close();
    }
    else {
        qDebug() << "error cert " << file_cert.errorString();
        return false;
    }
    QFile file_root_cert("./CA/root.pem");
    if (file_root_cert.open(QIODevice::ReadOnly)) {
        root = file_root_cert.readAll();
        file_root_cert.close();
    }
    else {
        qDebug() << "root cert " << file_cert.errorString();
        return false;
    }
    QSslKey ssl_key(key, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
//    QSslKey ssl_key(key, QSsl::Rsa,QSsl::Pem,QSsl::PrivateKey,"localhost");

    QSslCertificate ssl_cert(cert, QSsl::Pem);
    QSslCertificate root_cert(root, QSsl::Pem);

    config.setLocalCertificate(ssl_cert);
    config.setPrivateKey(ssl_key);
    config.addCaCertificate(root_cert);

    config.setProtocol(QSsl::TlsV1_2);
    config.setPeerVerifyMode(QSslSocket::VerifyPeer);
    m_config = std::make_shared<QSslConfiguration>(config);
    return true;
}

void Server::connectSuccess()
{
    QSslSocket* clientSocket = qobject_cast<QSslSocket*>(sender());
    qInfo(logInfo()) << " signal encrypted - handshake success, state = " << clientSocket->state();
}
