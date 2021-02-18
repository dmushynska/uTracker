#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

#include "responsehandler.h"
#include "usermanager.h"
#include "hash.h"


class Client: public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client() override;

    void doConnect(char *ip, int port);
    void testRequestLoop();
    void parseJSON(QJsonDocument itemDoc);

    UserManager *getManager();
    UserManager *m_manager;

public slots:
    void disconnected();
    void readyRead();

private:
    void initResponses();

    QTcpSocket *m_socket;

    std::shared_ptr<AbstractRequest> m_request;

    std::shared_ptr<AbstractResponseHandler> m_signUp;
    std::shared_ptr<AbstractResponseHandler> m_signIn;
    std::shared_ptr<AbstractResponseHandler> m_autoSignIn;
    std::shared_ptr<AbstractResponseHandler> m_googleSignIn;
    std::shared_ptr<AbstractResponseHandler> m_logOut;
    std::shared_ptr<AbstractResponseHandler> m_createdWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_updateWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_inviteToWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_allWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_singleWorkflow;
    std::shared_ptr<AbstractResponseHandler> m_sendStat;
    std::shared_ptr<AbstractResponseHandler> m_sendProfile;
    std::shared_ptr<AbstractResponseHandler> m_updateProfile;
    std::shared_ptr<AbstractResponseHandler> m_createListResponse;
    std::shared_ptr<AbstractResponseHandler> m_removeListResponse;
    std::shared_ptr<AbstractResponseHandler> m_createTaskResponse;
    std::shared_ptr<AbstractResponseHandler> m_updateTaskResponse;
    std::shared_ptr<AbstractResponseHandler> m_moveTaskResponse;
    std::shared_ptr<AbstractResponseHandler> m_removeTaskResponse;
    std::shared_ptr<AbstractResponseHandler> m_sendTaskDataResponse;


};