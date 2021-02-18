#include "client.h"
#include "requests.h"

AbstractRequest::AbstractRequest(QTcpSocket *socket) : m_socket(socket) {}

void AbstractRequest::createJSON(QMap<QString, QVariant> map) {

    QJsonObject jsonObject =  QJsonObject::fromVariantMap(map);
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    // qDebug() << json;

    QByteArray buffer;
    m_socket->write(buffer.setNum(json.size()));
    m_socket->write("\n" + json);
}

void AbstractRequest::setToken(const QString& token) {
    m_token = token;
}

////auth sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::signUp(const QString& login,
                             const QString& pass,
                             const QString& name,
                             const QString& surname,
                             const QString& email) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::SIGN_UP);
    mapa["login"] = login;
    mapa["password"] = pass;
    mapa["email"] = email;
    mapa["name"] = name;
    mapa["surname"] = surname;
    createJSON(mapa);
}
void AbstractRequest::signIn(const QString& email,
                             const QString& login,
                             const QString& pass) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::SIGN_IN);
    mapa["token"] = m_token;
    mapa["login"] = login;
    mapa["password"] = pass;
    mapa["email"] = email;
    createJSON(mapa);
}
void AbstractRequest::autoSignInWithGoogle() {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::AUTO_OAUTH);
    mapa["token"] = m_token;
    createJSON(mapa);
}
void AbstractRequest::autoSignIn() {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::AUTO_AUTH);
    mapa["token"] = m_token;
    createJSON(mapa);
}
void AbstractRequest::logOut(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::LOG_OUT);
    mapa["token"] = m_token;
    mapa["userId"] = userId;
    createJSON(mapa);
}

////workdflow (desk) sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::createWorkflow(const QString& title, const QString& deadline, int ownerId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::CREATE_WORKFLOW);
    mapa["token"] = m_token;
    mapa["ownerId"] = ownerId;
    mapa["title"] = title;
    mapa["deadline"] = deadline;
    createJSON(mapa);
}

void AbstractRequest::updateWorkflow(const QString& title, const QString& deadline, int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    mapa["token"] = m_token;
    mapa["title"] = title;
    mapa["deadline"] = deadline;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}

void AbstractRequest::archieveWorkflow(int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::ARCHIVE_WORKFLOW);
    mapa["token"] = m_token;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}

void AbstractRequest::inviteToWorkflow(const QString& login, int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::INVITE_TO_WORKFLOW);
    mapa["token"] = m_token;
    mapa["login"] = login;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}

void AbstractRequest::getAllWorkflows(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_ALL_WORKFLOWS);
    mapa["token"] = m_token;
    mapa["userId"] = userId;
    createJSON(mapa);
}

void AbstractRequest::getSingleWorkflowData(int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
    mapa["token"] = m_token;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}


void AbstractRequest::getStatistics() {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_STATISTICS);
    mapa["token"] = m_token;
    createJSON(mapa);
}

////profile sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::getProfile(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_PROFILE);
    mapa["token"] = m_token;
    mapa["userId"] = userId;
    createJSON(mapa);
}

void AbstractRequest::updateProfile(int userId, const QString& name, const QString& surname) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::UPDATE_PROFILE);
    mapa["token"] = m_token;
    mapa["userId"] = userId;
    mapa["name"] = name;
    mapa["surname"] = surname;
    createJSON(mapa);
}
////list sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::createList(const QString& title, int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::CREATE_LIST);
    mapa["token"] = m_token;
    mapa["title"] = title;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}

void AbstractRequest::removeList(int listId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::REMOVE_LIST);
    mapa["token"] = m_token;
    mapa["listId"] = listId;
    createJSON(mapa);
}


////task sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::createTask(const QString& title, int listId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::CREATE_TASK);
    mapa["token"] = m_token;
    mapa["title"] = title;
    mapa["listId"] = listId;
    createJSON(mapa);
}

void AbstractRequest::updateTask(int taskId, const QString& description, const QMap<QString, bool>& checkList) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::UPDATE_TASK);
    mapa["token"] = m_token;
    mapa["taskId"] = taskId;
    mapa["description"] = description;
    QJsonArray array;
//    for (auto item : checkList) {
    for (auto item = checkList.begin(); item != checkList.end(); item++) {
        QJsonObject npcObject {
            {"str", item.key()},
            {"isDone", item.value()}
        };
        array.append(npcObject);
    }
    mapa["checkList"] = array;
    createJSON(mapa);
}

void AbstractRequest::moveTask(int taskId, int listId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::MOVE_TASK);
    mapa["token"] = m_token;
    mapa["listId"] = listId;
    mapa["taskId"] = taskId;
    createJSON(mapa);
}

void AbstractRequest::removeTask(int taskId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::REMOVE_TASK);
    mapa["token"] = m_token;
    mapa["taskId"] = taskId;
    createJSON(mapa);
}

void AbstractRequest::getTaskData(int taskId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_TASK_DATA);
    mapa["token"] = m_token;
    mapa["taskId"] = taskId;
    createJSON(mapa);
}


// //EXAMPLE
// //creating json
// //QString login = "ND";
// //QString pass = "12345678";
// //QJsonArray npcArray;
// //QVector<int> vitya = {1, 2, 3, 4, 5};
// //for (auto item : vitya) {
// //QJsonObject npcObject {
// //        {"num", item}
// //};
// //npcArray.append(npcObject);
// //}
// //QJsonObject jsonObject {
// //        {"type", "signup"},
// //        {"login", login},
// //        {"password", pass},
// //        {"array", npcArray}
// //};
// //QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
// //QByteArray json = jsonDoc->toJson();
// //qDebug() << "WANNA SIGNUP !";
// //m_socket->write(json);