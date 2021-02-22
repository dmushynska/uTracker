#pragma once

#include <QTcpServer>
#include <QThreadPool>
#include <QVector>
#include <QMap>
#include <QSslKey>

#include "runnable.h"

#define MAX_THREAD_COUNT 5

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(quint16 _port, QObject* parent = nullptr);
    ~Server() override;
    bool startServer();

protected:
    void incomingConnection(qintptr handle) override;

signals:


public slots:
    void link();
    void connectSuccess();
//    void setNewTask(Connection *ptr);
    void setNewTask2(Connection* ptr);
//    void deleteConnection(Connection *ptr);
    void deleteConnection(qintptr id);

private:
    quint16 m_port;
    QMutex* m_mutex;
    QSslKey key;
    QSslCertificate cert;
    QThreadPool* m_pool;

    QMap<quint16, Connection*> m_map_connections;
    std::shared_ptr<QSslConfiguration> m_config;

    bool setSsslConfig();
    bool setSocket(std::shared_ptr<QSslSocket> m_ssl_socket);
};
