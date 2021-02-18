#pragma once

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <mutex>
#include <thread>

#include "connection.h"
#include "responses.h"

class DataBase : public QObject {
    Q_OBJECT
    QSqlDatabase m_db;
    static DataBase *m_pInstance;
    explicit DataBase();
    ~DataBase();
    DataBase(const DataBase &cs) = delete;
    DataBase &operator=(const DataBase &cs) = delete;
    std::mutex g_i_mutex;

public:
    bool insert(const QString &table, const QString &insert, const QString &values, int &lastInsert);
    bool insert(const QString &table, const QString &insert, const QString &values);
    bool update(const QString &table, const QString &update, const QString &where);
    QSqlQuery select(const QString &table, const QString &select, const QString &where);
    QVariantMap createUser(const QString &login, const QString &password, const QString &name, const QString &surname, const QString &email);
    QVariantMap containsUser(const QString &user, const QString &password);
    QVariantMap createWorkflow(int owner_id, const QString &title, const QString &deadline);
    QVariantMap updateWorkflow(int workflow_id, const QString &title, const QString &deadline);
    QVariantMap inviteToWorkflow(int user_id, int workflow_id);

    QVariantMap getWorkflows(int user_id);
    QVariantMap getWorkflow(int workflow_id);
    QVariantMap getUsersFromWorkFlow(int workflow_id);
    QVariantMap getProfile(int user_id);
    QVariantMap updateProfile(int user_id, const QString &name, const QString &surname);
    QVariantMap removeWorkflow(int workflow_id);

    QVariantMap createList(const QString& title, int workflowId);
    QVariantMap removeList(int listId);
    QVariantMap createTask(const QString& title, int listId);
    QVariantMap updateTask(int taskId, const QString& description, const QVariant& checkList);
    QVariantMap moveTask(int taskId, int newListId, int newIndexId);
    QVariantMap removeTask(int taskId);
    QVariantMap getTaskData(int taskId);

public:
    static DataBase *getInstance();
    void create_tables();
    bool isValidToken(const QString &token, int type) ;


    void sendData(Connection *m_connection, int type, const QMap<QString, QVariant> &map);

signals:
    void getData(Connection *m_connection, int type, const QMap<QString, QVariant> &map);
};
