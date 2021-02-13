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
    bool insert(const QString &table, const QString &insert, const QString &values);
    bool update(const QString &table, const QString &update, const QString &where);
    QSqlQuery select(const QString &table, const QString &select, const QString &where);
    QVariantMap createUser(const QString &login, const QString &password, const QString &name, const QString &surname);
    QVariantMap containsUser(const QString &user, const QString &password);
    QVariantMap createWorkflow(int owner_id, const QString &title, const QString &description);
    QVariantMap updateWorkflow(int workflow_id, const QString &title, const QString &description);
    QVariantMap inviteToWorkflow(int user_id, int workflow_id);

    QVariantMap getWorkflows(int user_id);
    QVariantMap getWorkflow(int workflow_id);
    QVariantMap getProfile(int user_id);
    QVariantMap updateProfile(int user_id, const QString &name, const QString &surname);

//    QVariantMap CREATE_LIST
//    QVariantMap REMOVE_LIST
//    QVariantMap CREATE_TASK
//    QVariantMap UPDATE_TASK
//    QVariantMap MOVE_TASK
//    QVariantMap REMOVE_TASK
//    QVariantMap GET_TASK_DATA

public:
    static DataBase *getInstance();
    void create_tables();

    //    int get_int_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    //    QString get_qstring_from_bd(const QString &table, const QString &column, const QString &namestring, const QString &string);
    //
    //    void set_string(const QString &table, const QString &column, const QString &string);
    //    void update_string(const QString &table, const QString &column, const QString &string, const QString &columnchanged, const QString &newstring);
    //
    //    void set_two_string(const QString &table, const QString &namestr1, const QString &str1, const QString &namestr2, const QString &str2);
    // void update_two_string(const QString &table, const QString &namestr1, const QString &str1, const QString &namestr2, const QString &str2, const QString &column, const QString &string);
    // void set_two_int(const QString &table, const QString &namestr1, int str1, const QString &namestr2, int str2);

    void sendData(Connection *m_connection, int type, const QMap<QString, QVariant> &map);

signals:
    void getData(Connection *m_connection, int type, const QMap<QString, QVariant> &map);
};
