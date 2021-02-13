#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QTcpSocket>

#include <QDataStream>

#include <iostream>

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

class AbstractRequest {

public:
    AbstractRequest(QTcpSocket *socket);

    void createJSON(QMap<QString, QVariant> map);

    //auth sector
    void signUp(const QString& login, const QString& pass, const QString& name, const QString& surname, const QString& email);
    void signIn(const QString& email, const QString&  login, const QString& pass);
    void autoSignInWithGoogle(const QString& token);
    void autoSignIn(const QString& token);
    void logOut(int userId);

    //workdflow (desk) sector
    void createWorkflow(const QString& title, const QString& deadline, int ownerId);
    void updateWorkflow(const QString& title, const QString& deadline, int workflowId);
    void inviteToWorkflow(int userId, int workflowId);
    void getAllWorkflows(int userId);
    void getSingleWorkflowData(int workflowId);

    void getStatistics();

    //profile sector
    void getProfile(int userId);
    void updateProfile(int userId, const QString& name, const QString& surname);

    //list sector
    void createList(const QString& title, int workflowId);
    void removeList(int listId);
    //task sector
    void createTask(const QString& title, int listId);
    void updateTask(int taskId, const QString& description, const QStringList& checkList);
    void moveTask(int taskId, int listId);
    void removeTask(int taskId);
    void getTaskData(int taskId);

protected:
    QTcpSocket *m_socket;
};

class JsonFormat {

};