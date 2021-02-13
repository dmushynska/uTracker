#include "client.h"
#include "requests.h"

AbstractRequest::AbstractRequest(QTcpSocket *socket) : m_socket(socket) {}

void AbstractRequest::createJSON(QMap<QString, QVariant> map) {

    QJsonObject jsonObject =  QJsonObject::fromVariantMap(map);
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    qDebug() << json;

    QByteArray buffer;
    m_socket->write(buffer.setNum(json.size()));
    m_socket->write("\n" + json);
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
    mapa["login"] = login;
    mapa["password"] = pass;
    mapa["email"] = email;
    createJSON(mapa);
}
void AbstractRequest::autoSignInWithGoogle(const QString& token) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::AUTO_OAUTH);
    mapa["token"] = token;
    createJSON(mapa);
}
void AbstractRequest::autoSignIn(const QString& token) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::AUTO_AUTH);
    mapa["token"] = token;
    createJSON(mapa);
}
void AbstractRequest::logOut(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::LOG_OUT);
    mapa["userId"] = userId;
    createJSON(mapa);
}

////workdflow (desk) sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::createWorkflow(const QString& title, const QString& deadline, int ownerId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::CREATE_WORKFLOW);
    mapa["ownerId"] = ownerId;
    mapa["title"] = title;
    mapa["deadline"] = deadline;
    createJSON(mapa);
}

void AbstractRequest::updateWorkflow(const QString& title, const QString& deadline, int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    mapa["title"] = title;
    mapa["deadline"] = deadline;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}
void AbstractRequest::inviteToWorkflow(int userId, int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::INVITE_TO_WORKFLOW);
    mapa["userId"] = userId;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}

void AbstractRequest::getAllWorkflows(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_ALL_WORKFLOWS);
    mapa["userId"] = userId;
    createJSON(mapa);
}

void AbstractRequest::getSingleWorkflowData(int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}


void AbstractRequest::getStatistics() {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_STATISTICS);
    createJSON(mapa);
}

////profile sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::getProfile(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_PROFILE);
    mapa["userId"] = userId;
    createJSON(mapa);
}

void AbstractRequest::updateProfile(int userId, const QString& name, const QString& surname) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::UPDATE_PROFILE);
    mapa["userId"] = userId;
    mapa["name"] = name;
    mapa["surname"] = surname;
    createJSON(mapa);
}
////list sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::createList(const QString& title, int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::CREATE_LIST);
    mapa["title"] = title;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}

void AbstractRequest::removeList(int listId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::REMOVE_LIST);
    mapa["listId"] = listId;
    createJSON(mapa);
}


////task sector/////////////////////////////////////////////////////////////////////////
void AbstractRequest::createTask(const QString& title, int listId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::CREATE_TASK);
    mapa["title"] = title;
    mapa["listId"] = listId;
    createJSON(mapa);
}

void AbstractRequest::updateTask(int taskId, const QString& description, const QStringList& checkList) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::UPDATE_TASK);
    mapa["taskId"] = taskId;
    mapa["description"] = description;
    mapa["checkList"] = checkList;
    createJSON(mapa);
}

void AbstractRequest::moveTask(int taskId, int listId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::MOVE_TASK);
    mapa["listId"] = listId;
    mapa["taskId"] = taskId;
    createJSON(mapa);
}

void AbstractRequest::removeTask(int taskId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::REMOVE_TASK);
    mapa["taskId"] = taskId;
    createJSON(mapa);
}

void AbstractRequest::getTaskData(int taskId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_TASK_DATA);
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