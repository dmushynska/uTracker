#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QObject>


class AbstractResponseHandler : public QObject{
Q_OBJECT
public:
    AbstractResponseHandler(QTcpSocket *socket);

signals:
    void handleInited(QJsonObject itemObject);

public slots:
    virtual void responseHandle(QJsonObject itemObject) = 0;

protected:
    QTcpSocket *m_socket;
    QByteArray m_json;
};

class SignUpResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SignUpResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SignInResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SignInResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SignInWithGoogleResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    SignInWithGoogleResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class AutoSignInResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    AutoSignInResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class LogOutResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    LogOutResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class CreatedWorkflowResponse : public AbstractResponseHandler {
Q_OBJECT
public:
    CreatedWorkflowResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class UpdateWorkflowResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    UpdateWorkflowResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class InvitedToWorkflowResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    InvitedToWorkflowResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class AllWorkflowsResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    AllWorkflowsResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SingleWorkflowDataResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    SingleWorkflowDataResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SendStatistics : public AbstractResponseHandler{
Q_OBJECT
public:
    SendStatistics(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SendProfileResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    SendProfileResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToUpdateProfileResponse : public AbstractResponseHandler{
Q_OBJECT
public:
    ToUpdateProfileResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

////list sector//////////////////////////////////////////
class ToCreateListResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToCreateListResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToRemoveListResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToRemoveListResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

////task sector//////////////////////////////////////////
class ToCreateTaskResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToCreateTaskResponse(QTcpSocket *socket);
    public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToUpdateTaskResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToUpdateTaskResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToMoveTaskResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToMoveTaskResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class ToRemoveTaskResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    ToRemoveTaskResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};

class SendTaskDataResponse : public AbstractResponseHandler  {
Q_OBJECT
public:
    SendTaskDataResponse(QTcpSocket *socket);
public slots:
    void responseHandle(QJsonObject itemObject);
};