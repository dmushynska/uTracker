#include "client.h"


class AES;

Client::Client(QObject *parent) : QObject(parent) {
    m_socket = new QTcpSocket();
    m_request = std::make_shared<AbstractRequest>(m_socket);
    m_manager = new UserManager(this);
    m_manager->getAuthor()->setRequest(m_request.get());
    m_manager->getWorkflow()->setRequest(m_request.get());
    initResponses();
}

void Client::initResponses() {
    m_signUp = std::make_shared<SignUpResponse>(this, m_socket);
    m_signIn = std::make_shared<SignInResponse>(this, m_socket);
    m_autoSignIn = std::make_shared<AutoSignInResponse>(this, m_socket);
    m_googleSignIn = std::make_shared<SignInWithGoogleResponse>(this, m_socket);
    m_logOut = std::make_shared<LogOutResponse>(this, m_socket);
    m_createdWorkflow = std::make_shared<CreatedWorkflowResponse>(this, m_socket);
    m_updateWorkflow = std::make_shared<UpdateWorkflowResponse>(this, m_socket);
    m_archieveWorkflow = std::make_shared<ArchieveWorkflowResponse>(this, m_socket);
    m_inviteToWorkflow = std::make_shared<InvitedToWorkflowResponse>(this, m_socket);
    m_removeFromWorkflow = std::make_shared<RemovedFromWorkflowResponse>(this, m_socket);
    m_getUsersFromWorkflow = std::make_shared<GetUsersFromWorkflowResponse>(this, m_socket);
    m_allWorkflow = std::make_shared<AllWorkflowsResponse>(this, m_socket);
    m_singleWorkflow = std::make_shared<SingleWorkflowDataResponse>(this, m_socket);
    m_sendStat = std::make_shared<SendStatistics>(this, m_socket);
    m_sendProfile = std::make_shared<SendProfileResponse>(this, m_socket);
    m_updateProfile = std::make_shared<ToUpdateProfileResponse>(this, m_socket);
    m_createListResponse = std::make_shared<ToCreateListResponse>(this, m_socket);
    m_renameListResponse = std::make_shared<ToRenameListResponse>(this, m_socket);
    m_getListsResponse = std::make_shared<ToGetListsResponse>(this, m_socket);
    m_removeListResponse = std::make_shared<ToRemoveListResponse>(this, m_socket);
    m_createTaskResponse = std::make_shared<ToCreateTaskResponse>(this, m_socket);
    m_getTasksResponse = std::make_shared<ToGetTasksResponse>(this, m_socket);
    m_updateTaskResponse = std::make_shared<ToUpdateTaskResponse>(this, m_socket);
    m_moveTaskResponse = std::make_shared<ToMoveTaskResponse>(this, m_socket);
    m_removeTaskResponse = std::make_shared<ToRemoveTaskResponse>(this, m_socket);
    m_sendTaskDataResponse = std::make_shared<SendTaskDataResponse>(this, m_socket);
}

Client::~Client() {
    m_socket->abort();
    delete m_socket;
}

void Client::doConnect(char *ip, int port) {
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(this, &Client::connectionRefused, m_manager->getAuthor(), &Authorization::connectionRefused);

    m_socket->connectToHost(ip, port);
    if (!m_socket->waitForConnected(5000)) {
        emit connectionRefused();
        qDebug() << "Error: " << m_socket->errorString();
    }
}

void Client::parseJSON(QJsonDocument itemDoc) {
    QJsonObject itemObject = itemDoc.object();

    QVector<std::shared_ptr<AbstractResponseHandler>> funcList;
    funcList.append({m_signUp, m_signIn, m_autoSignIn, m_googleSignIn, m_logOut, m_createdWorkflow});
    funcList.append({m_updateWorkflow, m_archieveWorkflow, m_inviteToWorkflow, m_removeFromWorkflow, m_getUsersFromWorkflow});
    funcList.append({m_allWorkflow, m_singleWorkflow, m_sendStat, m_sendProfile, m_updateProfile});
    funcList.append({m_createListResponse, m_renameListResponse, m_getListsResponse, m_removeListResponse, m_createTaskResponse});
    funcList.append({m_getTasksResponse, m_updateTaskResponse, m_moveTaskResponse, m_removeTaskResponse, m_sendTaskDataResponse});

    QVector<RequestType> types;
    types.append(RequestType::SIGN_UP);
    types.append(RequestType::SIGN_IN);
    types.append(RequestType::AUTO_AUTH);
    types.append(RequestType::AUTO_OAUTH);
    types.append(RequestType::LOG_OUT);
    types.append(RequestType::CREATE_WORKFLOW);
    types.append(RequestType::UPDATE_WORKFLOW);
    types.append(RequestType::ARCHIVE_WORKFLOW);
    types.append(RequestType::INVITE_TO_WORKFLOW);
    types.append(RequestType::REMOVE_FROM_WORKFLOW);
    types.append(RequestType::GET_USERS_FROM_WORKFLOW);
    types.append(RequestType::GET_ALL_WORKFLOWS);
    types.append(RequestType::GET_SINGLE_WORKFLOW_DATA);
    types.append(RequestType::GET_STATISTICS);
    types.append(RequestType::GET_PROFILE);
    types.append(RequestType::UPDATE_PROFILE);
    types.append(RequestType::CREATE_LIST);
    types.append(RequestType::RENAME_LIST);
    types.append(RequestType::GET_LISTS);
    types.append(RequestType::REMOVE_LIST);
    types.append(RequestType::CREATE_TASK);
    types.append(RequestType::GET_TASKS);
    types.append(RequestType::UPDATE_TASK);
    types.append(RequestType::MOVE_TASK);
    types.append(RequestType::REMOVE_TASK);
    types.append(RequestType::GET_TASK_DATA);
    for (auto i : types)
        if (static_cast<int>(i) == itemObject["type"].toInt())
                emit funcList[types.indexOf(i)]->handleInited(itemObject);
}

void Client::disconnected() {
    // do something when disconnection happens
}

void Client::readyRead() {
    while (!m_socket->atEnd()) {
        QByteArray size = m_socket->readLine();
       QJsonDocument itemDoc = QJsonDocument::fromJson(m_socket->read(size.toInt()));
       if (!itemDoc.isNull())
           parseJSON(itemDoc);
    }
}

UserManager *Client::getManager() {
    return m_manager;
}

std::shared_ptr<AbstractRequest> Client::getRequest() {
    return m_request;
}
