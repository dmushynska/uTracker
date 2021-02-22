#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QObject>

#include "usermanager.h"

class Client;

class AbstractResponseHandler : public QObject{
Q_OBJECT
public:
    AbstractResponseHandler(std::shared_ptr<QSslSocket> socket);

    QString getToken();

signals:
    void handleInited(QJsonObject itemObject);

public slots:
    virtual void responseHandle(QJsonObject itemObject) = 0;

protected:
    std::shared_ptr<QSslSocket> m_socket;
    QByteArray m_json;
    QString m_token;
    Client *m_parent;
};

class SignUpResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SignUpResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SignInResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SignInResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SignInWithGoogleResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SignInWithGoogleResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class AutoSignInResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    AutoSignInResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class LogOutResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    LogOutResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class CreatedWorkflowResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    CreatedWorkflowResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class RemovedFromWorkflowResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    RemovedFromWorkflowResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class GetUsersFromWorkflowResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    GetUsersFromWorkflowResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ArchieveWorkflowResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    ArchieveWorkflowResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class UpdateWorkflowResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    UpdateWorkflowResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class InvitedToWorkflowResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    InvitedToWorkflowResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class AllWorkflowsResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    AllWorkflowsResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SingleWorkflowDataResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    SingleWorkflowDataResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SendStatistics : public AbstractResponseHandler{
Q_OBJECT
public:
    SendStatistics(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SendProfileResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    SendProfileResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToUpdateProfileResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    ToUpdateProfileResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

////list sector//////////////////////////////////////////
class ToCreateListResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToCreateListResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToGetListsResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToGetListsResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToRemoveListResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToRemoveListResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

////task sector//////////////////////////////////////////
class ToCreateTaskResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToCreateTaskResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToGetTasksResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToGetTasksResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToUpdateTaskResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToUpdateTaskResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToMoveTaskResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToMoveTaskResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToRemoveTaskResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToRemoveTaskResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SendTaskDataResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    SendTaskDataResponse(Client *parent, std::shared_ptr<QSslSocket> socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

