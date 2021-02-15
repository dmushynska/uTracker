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
    query.exec("create table IF NOT EXISTS KanbanPanels (id integer primary key AUTOINCREMENT, workflow_id integer, title varchar)");
    query.exec("create table IF NOT EXISTS Tasks (id integer primary key AUTOINCREMENT, list_id int, panel_id int, title varchar, creation_time datetime, deadline_time datetime, creator_id int, description varchar, checklist json, files blob)");
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

bool DataBase::isValidToken(const QString &token) {
    //    Q_UNUSED(itemObject);
    QSqlQuery query;

    query.exec("select * from UsersCredential where auth_token = '" + token + "';");
    if (!token.isEmpty() && query.first()) {
        return true;
    }
    return false;
}

void DataBase::sendData(Connection *m_connection, int type, const QVariantMap &map) {
    QVariantMap result;
    // qDebug() << isValidToken(mx_hash(map.value("password").toString(), map.value("email").toString()));
    switch (static_cast<RequestType>(type)) {
        case RequestType::AUTO_AUTH:
            break;
        case RequestType::SIGN_UP:
            result = createUser(map.value("email").toString(),
                                map.value("password").toString(),
                                map.value("name").toString(),
                                map.value("surname").toString());
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
            break;
        case RequestType::UPDATE_WORKFLOW:
            result = updateWorkflow(map.value("workflowId").toInt(),
                                    map.value("title").toString(),
                                    map.value("deadline").toString());
            break;
        case RequestType::INVITE_TO_WORKFLOW:
            result = inviteToWorkflow(map.value("userId").toInt(),
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
                                map.value("checkList").toStringList());
            break;
        case RequestType::MOVE_TASK:
            result = moveTask(map.value("taskId").toInt(),
                              map.value("listId").toInt());
            break;
        case RequestType::REMOVE_TASK:
            result = removeTask(map.value("taskId").toInt());
            break;
        case RequestType::GET_TASK_DATA:
            result = getTaskData(map.value("taskId").toInt());
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
        query1.exec("select auth_token from UsersCredential where id = " + query.value(0).toString());
        if (query1.first()) {
            map["token"] = query1.value(0).toString();
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
                     const QString &surname) {
    QSqlQuery query;
    QString hash = mx_hash(password, login);
    query.prepare(
        "INSERT INTO UsersCredential (login, password, first_name, last_name, auth_token) "
        "VALUES (:login, :password, :first_name, :last_name, :auth_token);");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":first_name", name);
    query.bindValue(":last_name", surname);
    query.bindValue(":auth_token", hash);

    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::SIGN_UP);
    if (!query.exec()) {
        map["error"] = 1;
        map["message"] = "User with such login already exist";
    } else {
        map["token"] = hash;
        map["userId"] = query.lastInsertId().toInt();
        map["message"] = "User successfully created";
    }
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
    bool is_ok = false;
    if (!title.isEmpty() && !deadline.isEmpty()) {
        is_ok = update("WorkFlows", "title = '" + title + "', deadline = '" + deadline + "'", "id = " + QString::number(workflow_id));
    } else if (deadline.isEmpty()) {
        is_ok = update("WorkFlows", "title = '" + title + "'", "id = " + QString::number(workflow_id));
    } else if (title.isEmpty()) {
        is_ok = update("WorkFlows", "deadline = '" + deadline + "'", "id = " + QString::number(workflow_id));
    }
    QVariantMap map;
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
DataBase::inviteToWorkflow(int user_id, int workflow_id) {
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    if (insert("WF_connector", "workflow_id, user_id", QString::number(workflow_id) + ", " + QString::number(user_id))) {
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

    //    qDebug() << "user_id is " << user_id;
    //    qDebug() << query.value(0).toInt();
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
    // query.prepare("select * from WorkFlows where id = :workflow_id;");
    // query.bindValue(":workflow_id", workflow_id);
    // query.exec();
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
        map["message"] = "External error in GET_WORKFLOW";  // не міняй ніхуя поки що а то коли я дебажу я не ебу що за помилка
    }
    return map;
}

QVariantMap DataBase::getProfile(int user_id) {
    QSqlQuery query;
    query.exec("SELECT login, first_name, last_name FROM usersCredential where id = \"" + QString::number(user_id) + "\";");
    //    QSqlQuery query = select("usersCredential", "login, first_name, last_name", "id = " + QString::number(user_id) + ";");
    // query.exec("select first_name, last_name from WorkFlows where id = " + QString::number(user_id) + ";");
    // QMap<QString, QVariant> map;

    qDebug() << "login : " << query.value(0).toString();
    QMap<QString, QVariant> map;

    if (query.first()) {
        map["type"] = static_cast<int>(RequestType::GET_PROFILE);
        map["login"] = query.value(0).toString();
        map["first_name"] = query.value(1).toString();
        map["last_name"] = query.value(2).toString();
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
    // map["message"] = "List created";
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
    Q_UNUSED(listId);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::REMOVE_LIST);
    map["message"] = "List removed";
    QSqlQuery query;
    if (query.exec("DELETE from Lists where id = " + QString::number(listId) + ";")) {
        query.exec("DELETE from Tasks where list_id = " + QString::number(listId) + ";");
        map["message"] = "List removed";
    } else {
        map["message"] = "List wasn't removed";
        map["error"] = 1;
    }
    //додать до бд і поставить перевірки типу
    //if(видалилось == тру)
    //map["message"] = "List removed";
    //else {
    //map["message"] = "List wasn't removed";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::createTask(const QString &title, int listId) {
    Q_UNUSED(listId);
    Q_UNUSED(title);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::CREATE_TASK);
    // map["message"] = "Task created";
    int lastid;
    if (insert("Tasks", "title, list_id", "'" + title + "', " + QString::number(listId), lastid)) {
        map["message"] = "Task created";
        map["taskId"] = lastid;
    } else {
        map["message"] = "Task wasn't created";
        map["error"] = 1;
    }
    //додать до бд і поставить перевірки типу
    //if(створилось == тру)
    //map["message"] = "Task created";
    //else {
    //map["message"] = "Task wasn't created";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::updateTask(int taskId, const QString &description, const QStringList &checkList) {
    Q_UNUSED(taskId);
    Q_UNUSED(description);
    Q_UNUSED(checkList);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::UPDATE_TASK);
    QSqlQuery query;
    query.prepare("UPDATE Tasks SET description = :description, checklist = :checklist WHERE id = " + QString::number(taskId) + ";");
    query.bindValue(":description", description);
    query.bindValue(":checklist", checkList);
    if (query.exec()) {
        map["message"] = "Task updated";
    } else {
        map["message"] = "Task wasn't updated";
        map["error"] = 1;
    }
    //додать до бд // поки що я ебу як додать чек лист( там має бути типа масив даних в парі (булевське значення і інфа(стрінг))) тому поки що передаю чисто стрінгліст із інфою і буль поки не даю
    //поставить перевірки типу
    //if(оновились дані  == тру)
    //map["message"] = "Task updated";
    //else {
    //map["message"] = "Task wasn't updated";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::moveTask(int taskId, int listId) {
    Q_UNUSED(taskId);
    Q_UNUSED(listId);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::MOVE_TASK);
    if (update("Tasks", "list_id = " + QString::number(listId), "id = " + QString::number(taskId))) {
        map["message"] = "Task moved";
    } else {
        map["message"] = "Task wasn't moved";
        map["error"] = 1;
    }
    //додать до бд і поставить перевірки типу
    //if(змінила приналежність таски з листа попередньго айді на нове лістІд  == тру)
    //map["message"] = "Task moved";
    //else {
    //map["message"] = "Task wasn't moved";
    //map["error"] = 1;
    //}
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
    //додать до бд і поставить перевірки типу
    //if(видалила таску  == тру)
    //map["message"] = "Task removed";
    //else {
    //map["message"] = "Task wasn't removed";
    //map["error"] = 1;
    //}
    return map;
}

QVariantMap DataBase::getTaskData(int taskId) {
    Q_UNUSED(taskId);
    QVariantMap map;
    map["type"] = static_cast<int>(RequestType::GET_TASK_DATA);
    QSqlQuery query;
    if (query.exec("select description, checklist from Tasks where id = " + QString::number(taskId))) {
        map["message"] = "Take your task data bitch";
        query.first();
        map["description"] = query.value(0).toString();
        map["checkList"] = query.value(1).toJsonObject();
    } else {
        map["message"] = "i dont now wtf";
        map["error"] = 1;
    }
    //витягнуть дані з бд і поставить перевірки типу
    //if(видалила таску  == тру) {
    //map["description"] = //витягни з бд, якщо пусто то відправляй пусте;
    //map["checkList"] = //витягни з бд, якщо пусто то відправляй пусте;
    //}
    //else {
    //map["message"] = "i dont now wtf";
    //map["error"] = 1;
    //}
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
    // qDebug() << exec << query.lastError() << "INSERT INTO " + table + " (" + insert + ") VALUES (" + values + ");";
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
//qDebug() << "CHECK_LIST :\n";
//for(int i = 0; i < array.count(); i++)
//qDebug() << array.at(i).toString();
//qDebug() << "\n";