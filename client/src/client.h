#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QSslSocket>

#include "responsehandler.h"
#include "usermanager.h"
#include "hash.h"

class Client : public QObject {
Q_OBJECT
public:
    explicit Client(char* host, int port, QObject* parent = nullptr);
    ~Client() override;

    void doConnect();
    void testConnect() const;
    void testRequestLoop();
    void parseJSON(QJsonDocument itemDoc);

    UserManager* getManager();
    std::shared_ptr<AbstractRequest> getRequest();

public

slots:
    void readyRead();
    void disconnected();
    void connectSuccess();
    void sslErrors(const QList<QSslError>& errors);
//    void encrypted();
//    void connected();
//    void socketError(QAbstractSocket::SocketError error);
//    void socketSslErrors(const QList &list);

private:

    UserManager* m_manager;
    void initResponses();

    char* m_host;
    quint16 m_port;
    std::shared_ptr<QSslSocket> m_ssl_socket;

//    QTcpSocket* m_socket;
    std::shared_ptr<AbstractRequest> m_request;
    std::shared_ptr<AbstractResponseHandler> m_signUp;
    std::shared_ptr<AbstractResponseHandler> m_signIn;
    std::shared_ptr<AbstractResponseHandler> m_autoSignIn;
    std::shared_ptr<AbstractResponseHandler> m_googleSignIn;
    std::shared_ptr<AbstractResponseHandler> m_logOut;
    std::shared_ptr<AbstractResponseHandler> m_createdWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_updateWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_inviteToWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_removeFromWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_getUsersFromWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_allWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_singleWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_sendStat;
    std::shared_ptr<AbstractResponseHandler> m_sendProfile;
    std::shared_ptr<AbstractResponseHandler> m_updateProfile;
    std::shared_ptr<AbstractResponseHandler> m_createListResponse;
    std::shared_ptr<AbstractResponseHandler> m_getListsResponse;
    std::shared_ptr<AbstractResponseHandler> m_removeListResponse;
    std::shared_ptr<AbstractResponseHandler> m_createTaskResponse;
    std::shared_ptr<AbstractResponseHandler> m_getTasksResponse;
    std::shared_ptr<AbstractResponseHandler> m_updateTaskResponse;
    std::shared_ptr<AbstractResponseHandler> m_moveTaskResponse;
    std::shared_ptr<AbstractResponseHandler> m_removeTaskResponse;
    std::shared_ptr<AbstractResponseHandler> m_sendTaskDataResponse;

    bool configSSL();
    void reconnect();  // implement reconnection when break
};