#pragma once

#include <QTcpServer>
#include <QThreadPool>
#include <QVector>

#include "runnable.h"

#define MAX_THREAD_COUNT 5

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server() override;

    void startServer(quint16 port = 0);

protected:
    void incomingConnection(qintptr handle) override;

signals:

public slots:
    void deleteConnection(Connection *ptr);
    void setNewTask(Connection *ptr);

private:
    QMutex *m_mutex;
    QThreadPool *m_pool;
    QVector<Connection *> m_connections;
};
