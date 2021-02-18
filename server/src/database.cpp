#include "database.h"

#include <QSqlError>
#include <QSqlQueryModel>

#include "hash.h"

DataBase *DataBase::m_pInstance = nullptr;
DataBase *DataBase::getInstance() {
    if (m_pInstance == nullptr)
        m_pInstance = new DataBase();
    return m_pInstance;
}
DataBase::DataBase() : m_db(QSqlDatabase::addDatabase("QSQLITE")) {
    m_db.setDatabaseName("myDb.db");
    m_db.open();
    create_tables();
    connect(this, &DataBase::getData, this, &DataBase::sendData);
}

DataBase::~DataBase() {
    m_db.close();
}

void DataBase::create_tables() {
    //const std ::lock_guard<std ::mutex> lock(g_i_mutex);
    QSqlQuery query;
    query.exec(
        "create table IF NOT EXISTS UsersCredential ("
        "id integer primary key AUTOINCREMENT,"
        "login varchar UNIQUE,"
        "password varchar,"
        "auth_token varchar UNIQUE,"
        "first_name varchar,"
        "last_name varchar,"
        "photo blob,"
        "google_token varchar,"
        "github_token varchar)");
    query.exec("create table IF NOT EXISTS WorkFlows (id integer primary key AUTOINCREMENT, owner_id int, title varchar, deadline datetime)");
    // query.exec("create table IF NOT EXISTS KanbanPanels (id integer primary key AUTOINCREMENT, workflow_id integer, title varchar)");
    query.exec("create table IF NOT EXISTS Tasks (id integer primary key AUTOINCREMENT, list_id int, index_id int, title varchar, creation_time datetime, deadline_time datetime, creator_id int, description varchar, checklist varchar, files blob)");
    query.exec(
        "create table IF NOT EXISTS T_connector ("
        "id integer primary key AUTOINCREMENT,"
        "task_id int,"
        "worker_id int"
        "FOREIGN KEY(task_id) REFERENCES Tasks(id),"
        "FOREIGN KEY(worker_id) REFERENCES UsersCredential(id)\")");
    query.exec(
        "create table IF NOT EXISTS WF_connector ("
        "id integer primary key AUTOINCREMENT,"
        "workflow_id int,"
        "user_id int,"
        "FOREIGN KEY(workflow_id) REFERENCES WorkFlows(id),"
        "FOREIGN KEY(user_id) REFERENCES UsersCredential(id))");
    query.exec("create table IF NOT EXISTS Lists (id integer primary key AUTOINCREMENT, title varchar, workflow_id int)");
}

bool DataBase::isValidToken(const QString &token, int type) {
    QSqlQuery query;
    query.exec("select * from UsersCredential where auth_token = '" + token + "';");
    if (type == static_cast<int>(RequestType::SIGN_UP) || (!token.isEmpty() && query.first()))
        return true;
    return false;
}

void DataBase::sendData(Connection *m_connection, int type, const QVariantMap &map) {
    QVariantMap result;
    if (isValidToken(map.value("token").toString(),
                     map.value("type").toInt())) {
        switch (static_cast<RequestType>(type)) {
            case RequestType::AUTO_AUTH:
                break;
            case RequestType::SIGN_UP:
                result = createUser(map.value("email").toString(),
                                    map.value("password").toString(),
                                    map.value("name").toString(),
                                    map.value("surname").toString(),
                                    map.value("email").toString());
                break;
            case RequestType::SIGN_IN:
                result = containsUser(map.value("email").toString(),
                                      map.value("password").toString());
                break;
            case RequestType::AUTO_OAUTH:
                break;
            case RequestType::LOG_OUT:
                break;
            case RequestType::CREATE_WORKFLOW:
                result = createWorkflow(map.value("userId").toInt(),
                                        map.value("title").toString(),
                                        map.value("deadline").toString());
                break;
            case RequestType::ARCHIVE_WORKFLOW:
                result = removeWorkflow(map.value("workflowId").toInt());
                break;
            case RequestType::UPDATE_WORKFLOW:
                result = updateWorkflow(map.value("workflowId").toInt(),
                                        map.value("title").toString(),
                                        map.value("deadline").toString());
                break;
            case RequestType::INVITE_TO_WORKFLOW:
                result = inviteToWorkflow(map.value("login").toString(),
                                          map.value("workflowId").toInt());
                break;
            case RequestType::GET_ALL_WORKFLOWS:
                result = getWorkflows(map.value("userId").toInt());
                break;
            case RequestType::GET_SINGLE_WORKFLOW_DATA:
                result = getWorkflow(map.value("workflowId").toInt());
                break;
            case RequestType::GET_STATISTICS:
                break;
            case RequestType::GET_PROFILE:
                result = getProfile(map.value("userId").toInt());
                break;
            case RequestType::UPDATE_PROFILE:
                result = updateProfile(map.value("userId").toInt(),
                                       map.value("name").toString(),
                                       map.value("surname").toString());
                break;
            case RequestType::CREATE_LIST:
                result = createList(map.value("title").toString(),
                                    map.value("workdlowId").toInt());
                break;
            case RequestType::REMOVE_LIST:
                result = removeList(map.value("listId").toInt());
                break;
            case RequestType::CREATE_TASK:
                result = createTask(map.value("title").toString(),
                                    map.value("listId").toInt());
                break;
            case RequestType::UPDATE_TASK:
                result = updateTask(map.value("taskId").toInt(),
                                    map.value("description").toString(),
                                    map.value("checkList"));
                break;
            case RequestType::MOVE_TASK:
                result = moveTask(map.value("taskId").toInt(), 
                                  map.value("listId").toInt(),
                                  map.value("indexId").toInt());
                break;
            case RequestType::REMOVE_TASK:
                result = removeTask(map.value("taskId").toInt());
                break;
            case RequestType::GET_TASK_DATA:
                result = getTaskData(map.value("taskId").toInt());
        }
    } else {
        result["type"] = map.value("type").toInt();
        result["error"] = 1;
        result["message"] = "Invalid token";
    }
    if (!result.isEmpty()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(result);
        QJsonDocument jsonDoc = QJsonDocument(jsonObject);
        emit m_connection->sendResponse(jsonDoc.toJson());
    }
}

QVariantMap DataBase::containsUser(const QString &login, const QString &password) {
    QSqlQuery query;
    query.exec("SELECT id, password FROM UsersCredential where login = \"" + login + "\";");

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_IN);

    //    if (query.first())
    //        qDebug() << "userFound";
    if (query.first() && (query.value(1).toString() == password)) {
        map["userId"] = query.value(0);
        map["message"] = "Successfully authorized";
        QSqlQuery query1;
        query1.exec("select auth_token, first_name, last_name, email from UsersCredential where id = " + query.value(0).toString());
        if (query1.first()) {
            map["userId"] = query.value(0).toString();  //userId
            map["token"] = query1.value(0).toString();  //token
            map["login"] = login;
            map["email"] = query1.value(3).toString();
            ;
            map["name"] = query1.value(1).toString();
            ;
            map["surname"] = query1.value(2).toString();
            ;
        }
    } else {
        map["error"] = 1;
        map["message"] = "Invalid email or password";
    }
    return map;
}

QVariantMap
DataBase::createUser(const QString &login,
                     const QString &password,
                     const QString &name,
                     const QString &surname,
                     const QString &email) {
    QSqlQuery query;
    QString hash = mx_hash(password, login);
    query.prepare(
        "INSERT INTO UsersCredential (login, password, first_name, last_name, auth_token, email) "
        "VALUES (:login, :password, :first_name, :last_name, :auth_token, :email);");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":first_name", name);
    query.bindValue(":last_name", surname);
    query.bindValue(":auth_token", hash);
    query.bindValue(":email", email);

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_UP);
//    if (!query.exec()) {
//        map["error"] = 1;
//        map["message"] = "User with such login already exist";
//    } else {
        map["token"] = hash;
        map["userId"] = query.lastInsertId().toInt();
        map["message"] = "User successfully created";
//    }
    return map;
}

QVariantMap
DataBase::createWorkflow(int owner_id, const QString &title, const QString &deadline) {
    QSqlQuery query;
    auto res = query.exec(QString("INSERT INTO WorkFlows (owner_id, title, deadline) VALUES(%1, '%2', '%3');")
                              .arg(owner_id)
                              .arg(title)
                              .arg(deadline));

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::CREATE_WORKFLOW);
    if (res) {
        auto workflowId = query.lastInsertId().toInt();
        map["workflowId"] = workflowId;
        // map["title"] = title;
        // map["deadline"] = deadline;
        map["message"] = "Workflow has been created";
        query.exec(QString("INSERT INTO WF_connector (workflow_id, user_id) VALUES(%1, '%2');")
                       .arg(workflowId)
                       .arg(owner_id));
    } else {
        map["error"] = 1;
        map["message"] = "Unfortunately, workflow hasn't been created";
    }

    return map;
}

QVariantMap
DataBase::updateWorkflow(int workflow_id, const QString &title, const QString &deadline) {
    QVariantMap map;
    bool is_ok = false;
    if (!title.isEmpty() && !deadline.isEmpty()) {
        is_ok = update("WorkFlows", "title = '" + title + "', deadline = '" + deadline + "'", "id = " + QString::number(workflow_id));
        map["title"] = title;
        map["deadline"] = deadline;
    } else if (deadline.isEmpty()) {
        is_ok = update("WorkFlows", "title = '" + title + "'", "id = " + QString::number(workflow_id));
        map["title"] = title;
    } else if (title.isEmpty()) {
        is_ok = update("WorkFlows", "deadline = '" + deadline + "'", "id = " + QString::number(workflow_id));
        map["deadline"] = deadline;
    }

    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    if (is_ok)
        map["message"] = "Workflow successfully updated";
    else {
        map["error"] = 1;
        map["message"] = "User isn't in database";
    }
    return map;
}

QVariantMap
DataBase::inviteToWorkflow(const QString &login, int workflow_id) {
    Q_UNUSED(login);
    Q_UNUSED(workflow_id);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    QSqlQuery query;
    query.exec(QString("select id from UsersCredential where login = '%1';").arg(login));
    if (query.first() && insert("WF_connector", "workflow_id, login", QString::number(workflow_id) + ", " + query.value(0).toString())) {
        map["message"] = "User succesfully invited to Workflow";
    } else {
        map["error"] = 1;
        map["message"] = "Invite canceled";
    }
    return map;
}

QVariantMap DataBase::getWorkflows(int user_id) {  // треба норм дописать мапу яку повертаю з ерорами
    QJsonArray workflows;
    QSqlQuery query;
    query.exec(QString("select workflow_id from WF_connector where user_id = %1;").arg(user_id));
    QMap<QString, QVariant> map;

    map["type"] = static_cast<int>(RequestType::GET_ALL_WORKFLOWS);
    if (query.first()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(getWorkflow(query.value(0).toInt()));
        workflows.append(jsonObject);
    } else {
        map["error"] = 1;
        map["message"] = "Workflows don't exist";
    }
    while (query.next()) {
        QJsonObject jsonObject = QJsonObject::fromVariantMap(getWorkflow(query.value(0).toInt()));
        workflows.append(jsonObject);
    }

    if (!map.contains("error")) {
        map["workflows"] = workflows;
        map["message"] = "Workflows successfully have gotten";
    }
    return map;
}

QVariantMap DataBase::getWorkflow(int workflow_id) {
    QSqlQuery query = select("WorkFlows", "owner_id, title, deadline", "id = " + QString::number(workflow_id));
    QMap<QString, QVariant> map;
    if (query.first()) {
        map["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
        map["workflowId"] = workflow_id;
        map["owner_id"] = query.value(0).toInt();
        map["title"] = query.value(1).toString();
        map["deadline"] = query.value(2).toString();
        map["message"] = "Workflow successfully has gotten";
    } else {
        map["error"] = 1;
        map["message"] = "External error in GET_WORKFLOW";
    }
    return map;
}

QVariantMap DataBase::removeWorkflow(int workflow_id) {
    QMap<QString, QVariant> map;
    QSqlQuery query;
    if (query.exec("DELETE from WF_connector where id = " + QString::number(workflow_id) + ";")) {
        query.exec("DELETE from WorkFlows where id = " + QString::number(workflow_id) + ";");
        query.exec("DELETE from Lists where id = " + QString::number(workflow_id) + ";");
        map["message"] = "WorkFlow removed";
    } else {
        map["message"] = "WorkFlow wasn't removed";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::getProfile(int user_id) {
    QSqlQuery query;
    query.exec("SELECT login, first_name, last_name FROM UsersCredential where id = \"" + QString::number(user_id) + "\";");
    //    QSqlQuery query = select("usersCredential", "login, first_name, last_name", "id = " + QString::number(user_id) + ";");
    // query.exec("select first_name, last_name from WorkFlows where id = " + QString::number(user_id) + ";");
    // QMap<QString, QVariant> map;
    // query.first();
    // qDebug() << "login : " << query.value(0).toString();
    QMap<QString, QVariant> map;

    if (query.first()) {
        map["type"] = static_cast<int>(RequestType::GET_PROFILE);
        map["login"] = query.value(0).toString();
        map["name"] = query.value(1).toString();
        map["surname"] = query.value(2).toString();
        map["message"] = "Profile data has successfully gotten";
    } else {
        map["error"] = 1;
        map["message"] = "User doesn't exist in database";
    }
    //    QString email
    //    QString password
    //    QString auth_token
    //    QString first_name
    //    QString last_name
    //    byte photo
    //    QString google_token
    //    QString github_token varchar
    return map;
}

QVariantMap DataBase::updateProfile(int user_id, const QString &name, const QString &surname) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    if (update("UsersCredential", "first_name = '" + name + "', last_name = '" + surname + "'", "id = " + QString::number(user_id))) {
        map["message"] = "Profile was succesfully updated";
        map["name"] = name;
        map["surname"] = surname;
    } else {
        map["error"] = 1;
        map["message"] = "Profile hasn't beed updated";
    }
    return map;
}

QVariantMap DataBase::createList(const QString &title, int workflowId) {
    Q_UNUSED(workflowId);
    Q_UNUSED(title);
    QVariantMap map;
    int lastId;
    map["type"] = static_cast<int>(RequestType::CREATE_LIST);
    if (insert("Lists", "workflow_id, title", QString::number(workflowId) + ", '" + title + "'", lastId)) {
        map["message"] = "List created";
        map["listId"] = lastId;
    } else {
        map["message"] = "List wasn't created";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::removeList(int listId) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::REMOVE_LIST);
    QSqlQuery query;
    if (query.exec("DELETE from Lists where id = " + QString::number(listId) + ";")) {
        query.exec("DELETE from Tasks where list_id = " + QString::number(listId) + ";");
        map["message"] = "List removed";
    } else {
        map["message"] = "List wasn't removed";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::createTask(const QString &title, int listId) {
    QSqlQuery query;
    int index_id = 1;
    query.exec("select index_id from Tasks where list_id = " + QString::number(listId) + " order by index_id DESC limit 1");
    if (query.first()) {
        index_id = query.value(0).toInt() + 1;
    }
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::CREATE_TASK);
    int lastid;
    if (insert("Tasks", "title, list_id, index_id", "'" + title + "', " + QString::number(listId) + ", " + QString::number(index_id), lastid)) {
        map["message"] = "Task created";
        map["taskId"] = lastid;
    } else {
        map["message"] = "Task wasn't created";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::updateTask(int taskId, const QString &description, const QVariant &checkList) {
    QJsonObject obj{
        {"array", checkList.toJsonArray()}};
    QJsonDocument *jsonDoc = new QJsonDocument(obj);
    QByteArray json = jsonDoc->toJson();

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_TASK);
    QSqlQuery query;
    query.prepare("UPDATE Tasks SET description = :description, checklist = :checklist WHERE id = " + QString::number(taskId) + ";");
    query.bindValue(":description", description);
    query.bindValue(":checklist", json);
    // qDebug() << obj;
    // QJsonArray ll = checkList.toJsonArray();
    // qDebug() << "CHECK_LIST :\n";
    // for(int i = 0; i < ll.count(); i++) {
    //     qDebug() << ll.at(i)["str"].toString();
    //     qDebug() << ll.at(i)["isDone"].toBool();
    // }
    if (query.exec()) {
        map["message"] = "Task updated";
        map["description"] = description;
        map["checkList"] = checkList;
    } else {
        map["message"] = "Task wasn't updated";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::moveTask(int taskId, int newListId, int newIndexId) {
    Q_UNUSED(taskId);
    Q_UNUSED(newListId);
    Q_UNUSED(newIndexId);
    QVariantMap map;
    QSqlQuery query;
    query.exec("select list_id, index_id from Tasks where id = " + QString::number(taskId));
    if (query.first()) {
        int listId = query.value(0).toInt();
        int indexId = query.value(1).toInt();
        query.exec("select index_id from Tasks where list_id = " + QString::number(newListId) + " and index_id > " + QString::number(newIndexId - 1) + " order by index_id desc");
        if (query.first()) {
            update("Tasks", "index_id = " + QString::number(query.value(0).toInt() + 1), "list_id = " + QString::number(newListId) + " and index_id = " + QString::number(query.value(0).toInt()));
            while (query.next()) {
                update("Tasks", "index_id = " + QString::number(query.value(0).toInt() + 1), "list_id = " + QString::number(newListId) + " and index_id = " + QString::number(query.value(0).toInt()));
            }
        }
        query.exec("select index_id from Tasks where list_id = " + QString::number(listId) + " and index_id > " + QString::number(indexId) + " order by index_id asc");
        if (query.first()) {
            update("Tasks", "index_id = " + QString::number(query.value(0).toInt() - 1), "list_id = " + QString::number(listId) + " and index_id = " + QString::number(query.value(0).toInt()));
            while (query.next()) {
                update("Tasks", "index_id = " + QString::number(query.value(0).toInt() - 1), "list_id = " + QString::number(listId) + " and index_id = " + QString::number(query.value(0).toInt()));
            }
        }
    }
    map["type"] = static_cast<int>(RequestType::MOVE_TASK);
    if (update("Tasks", "list_id = " + QString::number(newListId) + ", index_id = " + QString::number(newIndexId), "id = " + QString::number(taskId))) {
        map["message"] = "Task moved";
    } else {
        map["message"] = "Task wasn't moved";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::removeTask(int taskId) {
    Q_UNUSED(taskId);
    QVariantMap map;
    QSqlQuery query;
    map["type"] = static_cast<int>(RequestType::REMOVE_TASK);
    if (query.exec("DELETE from Tasks where id = " + QString::number(taskId))) {
        map["message"] = "Task removed";
    } else {
        map["message"] = "Task wasn't removed";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::getTaskData(int taskId) {  //я подивлюся
                                                 //    Q_UNUSED(taskId);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::GET_TASK_DATA);
    QSqlQuery query;
    if (query.exec("select description, checklist from Tasks where id = " + QString::number(taskId))) {
        map["message"] = "Take your task data bitch";
        query.first();
        map["description"] = query.value(0).toString();
        map["checkList"] = query.value(1).toString();
    } else {
        map["message"] = "i dont now wtf";
        map["error"] = 1;
    }
    return map;
}

QVariantMap DataBase::getUsersFromWorkFlow(int workflow_id) {
    QJsonArray Users;
    QSqlQuery query;
    QVariantMap map;
    qDebug() << query.exec("select first_name, last_name, id from UsersCredential where id in (select user_id from WF_connector where workflow_id = " + QString::number(workflow_id) + ");");
    if (query.first()) {
        map["name"] = query.value(0).toString();
        map["surname"] = query.value(1).toString();
        Users.append(QJsonObject::fromVariantMap(map));
    } else {
        map["error"] = 1;
        map["message"] = "Workflows don't exist";
    }
    while (query.next()) {
        map["name"] = query.value(0).toString();
        map["surname"] = query.value(1).toString();
        Users.append(QJsonObject::fromVariantMap(map));
    }
    if (!map.contains("error")) {
        map["users"] = Users;
        map["message"] = "Users successfully have gotten";
    }
    return map;
}

bool DataBase::insert(const QString &table, const QString &insert, const QString &values) {
    QSqlQuery query;
    return query.exec("INSERT INTO " + table + " (" + insert + ") VALUES (" + values + ");");
}
bool DataBase::insert(const QString &table, const QString &insert, const QString &values, int &lastInsert) {
    QSqlQuery query;
    bool exec = query.exec("INSERT INTO " + table + " (" + insert + ") VALUES (" + values + ");");
    lastInsert = query.lastInsertId().toInt();
    return exec;
}
bool DataBase::update(const QString &table, const QString &update, const QString &where) {
    QSqlQuery query;
    return query.exec("UPDATE " + table + " SET " + update + " WHERE " + where + ";");
}
QSqlQuery DataBase::select(const QString &table, const QString &select, const QString &where) {
    QSqlQuery query;
    query.exec("SELECT " + select + " FROM " + table + " WHERE " + where + ";");
    return query;
}

// //QJsonArray npcArray;
// //QVector<int> vitya = {1, 2, 3, 4, 5};
// //for (auto item : vitya) {
// //QJsonObject npcObject {
// //        {"num", item}
// //};
// //npcArray.append(npcObject);
// //}

//QJsonArray array = itemObject["checkList"].toArray();
// qDebug() << "CHECK_LIST :\n";
// for(int i = 0; i < checkList.count(); i++) {
// qDebug() << checkList.at(i)["str"].toString();
// qDebug() << checkList.at(i)["isDone"].toBool();
// }