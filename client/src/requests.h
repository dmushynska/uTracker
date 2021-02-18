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
    ARCHIVE_WORKFLOW = 6,
    UPDATE_WORKFLOW = 7,
    INVITE_TO_WORKFLOW = 8,
    GET_ALL_WORKFLOWS = 9,
    GET_SINGLE_WORKFLOW_DATA = 10,
    GET_STATISTICS = 11,
    GET_PROFILE = 12,
    UPDATE_PROFILE = 13,
    CREATE_LIST = 14,
    REMOVE_LIST = 15,
    CREATE_TASK = 16,
    UPDATE_TASK = 17,
    MOVE_TASK = 18,
    REMOVE_TASK = 19,
    GET_TASK_DATA = 20
};

class AbstractRequest {

public:
    AbstractRequest(QTcpSocket *socket);

    void createJSON(QMap<QString, QVariant> map);

    void setToken(const QString& token);

    //auth sector
    void signUp(const QString& login, const QString& pass, const QString& name, const QString& surname, const QString& email);
    void signIn(const QString& email, const QString&  login, const QString& pass);
    void autoSignInWithGoogle();
    void autoSignIn();
    void logOut(int userId);

    //workdflow (desk) sector
    void createWorkflow(const QString& title, const QString& deadline, int ownerId);
    void updateWorkflow(const QString& title, const QString& deadline, int workflowId);
    void archieveWorkflow(int workflowId);
    void inviteToWorkflow(const QString& login, int workflowId);
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
    void updateTask(int taskId, const QString& description, const QMap<QString, bool>& checkList);
    void moveTask(int taskId, int listId, int indexId);
    void removeTask(int taskId);
    void getTaskData(int taskId);

protected:
    QTcpSocket *m_socket;
    QString m_token;
};
