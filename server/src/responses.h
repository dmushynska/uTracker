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
    ARCHIVE_WORKFLOW = 6,
    UPDATE_WORKFLOW = 7,
    INVITE_TO_WORKFLOW = 8,
    REMOVE_FROM_WORKFLOW = 9,
    GET_USERS_FROM_WORKFLOW = 10,
    GET_ALL_WORKFLOWS = 11,
    GET_SINGLE_WORKFLOW_DATA = 12,
    GET_STATISTICS = 13,
    GET_PROFILE = 14,
    UPDATE_PROFILE = 15,
    CREATE_LIST = 16,
    RENAME_LIST = 17,
    GET_LISTS = 18,
    REMOVE_LIST = 19,
    CREATE_TASK = 20,
    GET_TASKS = 21,
    UPDATE_TASK = 22,
    MOVE_TASK = 23,
    REMOVE_TASK = 24,
    GET_TASK_DATA = 25
};

class AbstractRequestHandler : public QObject{
    Q_OBJECT
public:
    AbstractRequestHandler(Connection *connection);

    virtual bool isValid(QJsonObject itemObject) = 0;

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

class toArchieveWorkflow : public AbstractRequestHandler {
Q_OBJECT
public:
    toArchieveWorkflow(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToInvitedToWorkflow : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToInvitedToWorkflow(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToRemoveFromWorkflow : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToRemoveFromWorkflow(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToGetUsersFromWorkflow : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToGetUsersFromWorkflow(Connection *socket);
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

class ToRenameList : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToRenameList(Connection *socket);
    bool isValid(QJsonObject itemObject);
};

class ToGetLists : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToGetLists(Connection *socket);
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

class ToGetTasks : public AbstractRequestHandler  {
Q_OBJECT
public:
    ToGetTasks(Connection *socket);
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
