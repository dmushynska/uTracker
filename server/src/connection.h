#pragma once

#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QByteArray>
#include <QMutex>
#include <QSslSocket>

class Connection : public QObject {
Q_OBJECT
public:
    explicit Connection(qintptr socket_id, std::shared_ptr<QSslSocket> ssl_socket, QObject* parent = nullptr);
    ~Connection() override;

    QByteArray getTask() const { return m_task; }
//    void parseJSON(QJsonDocument itemDoc);
    QString get_login() const {
        return m_login;
    }

    QString get_mail() const {
        return m_mail;
    }
    void set_login(QString login) { m_login = login; }
    void set_mail(QString mail) { m_mail = mail; }

public slots:
    void write_to_socket(const QByteArray& data);
    void disconnected();
    void read_from_socket();
    void print_errors(QList<QSslError> errors) const;
    void print_error(const QSslError& error) const;
    void mode_changed(QSslSocket::SslMode mode);


signals:
    void disconnectSocket(qintptr id);
    void sendResponse(const QByteArray& data);
    void new_task(Connection* ptr);

private:
    qintptr m_socket_id;  // TCP socket descriptor
    std::shared_ptr<QSslSocket> m_ssl_socket;
    QString m_login{};
    QString m_mail{};
    QByteArray m_task;
    QObject* m_parent;
};

/*
class Connection : public QObject {
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);
    ~Connection() override;

    void doConnect(qintptr handle);
    QByteArray getTask() const;

signals:
    void sendResponse(const QByteArray &data);

public slots:
    void writeToSocket(const QByteArray &data);
    void disconnected();
    void readyRead();

private:
    QByteArray m_task;
    QTcpSocket *m_socket;
    QObject *m_parent;
};
*/