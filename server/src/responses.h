#pragma once

#include <QTcpSocket>
#include <QAbstractSocket>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QObject>

#include "connection.h"

enum class RequestType {
    SIGN_UP = 0,
    SIGN_IN = 1,
    AUTO_AUTH = 2,
    AUTO_OAUTH = 3,
    LOG_OUT = 4,
    CREATE_WORKFLOW = 5,
    UPDATE_WORKFLOW = 6,
    INVITE_TO_WORKFLOW = 7,
    GET_ALL_WORKFLOWS = 8,
    GET_SINGLE_WORKFLOW_DATA = 9,
    GET_STATISTICS = 10,
    GET_PROFILE = 11,
    UPDATE_PROFILE = 12,
    CREATE_LIST = 13,
    REMOVE_LIST = 14,
    CREATE_TASK = 15,
    UPDATE_TASK = 16,
    MOVE_TASK = 17,
    REMOVE_TASK = 18,
    GET_TASK_DATA = 19
};

class AbstractRequestHandler : public QObject{
    Q_OBJECT
public:
    AbstractRequestHandler(Connection *connection);

    virtual bool isValid(QJsonObject itemObject) = 0;
    bool isValidToken(QJsonObject itemObject);

    signals:
    void responseInited(QJsonObject itemObject);

    public slots:
    void responseSend(QJsonObject itemObject);

protected:
    Connection *m_connection;
    QByteArray m_json;
};

////auth sector/////////////////////////////////////
class ToSignUp : public AbstractRequestHandler {
    Q_OBJECT
public:
    ToSignUp(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToSignIn : public AbstractRequestHandler {
Q_OBJECT
public:
    ToSignIn(Connection *socket);
    bool isValid(QJsonObject itemObject);
};


class ToSignInWithGoogle : public AbstractRequestHandler {
Q_OBJECT
public:
    ToSignInWithGoogle(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToAutoSignIn : public AbstractRequestHandler {
Q_OBJECT
public:
    ToAutoSignIn(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToLogOut : public AbstractRequestHandler {
Q_OBJECT
public:
    ToLogOut(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

////workflow (desk) sector/////////////////////////////////////
class ToCreatedWorkflow : public AbstractRequestHandler {
Q_OBJECT
public:
    ToCreatedWorkflow(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToUpdateWorkflow : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToUpdateWorkflow(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToInvitedToWorkflow : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToInvitedToWorkflow(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class SendAllWorkflows : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendAllWorkflows(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class SendSingleWorkflowData : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendSingleWorkflowData(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

////statistic sector//////////////////////////////////////////
class SendStatistics : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendStatistics(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

////profile sector//////////////////////////////////////////
class SendProfile : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendProfile(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToUpdateProfile : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToUpdateProfile(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

////list sector//////////////////////////////////////////
class ToCreateList : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToCreateList(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToRemoveList : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToRemoveList(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

////task sector//////////////////////////////////////////
class ToCreateTask : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToCreateTask(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToUpdateTask : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToUpdateTask(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToMoveTask : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToMoveTask(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToRemoveTask : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToRemoveTask(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class SendTaskData : public AbstractRequestHandler  {
Q_OBJECT
public:
    SendTaskData(Connection *socket);
    bool isValid(QJsonObject itemObject);
};
