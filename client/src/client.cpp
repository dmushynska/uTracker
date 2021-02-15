#include "client.h"


class AES;

Client::Client(QObject *parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);
    m_request = std::make_shared<AbstractRequest>(m_socket);
    m_signUp = std::make_shared<SignUpResponse>(m_socket);
    m_signIn = std::make_shared<SignInResponse>(m_socket);
    m_autoSignIn = std::make_shared<AutoSignInResponse>(m_socket);
    m_googleSignIn = std::make_shared<SignInWithGoogleResponse>(m_socket);
    m_logOut = std::make_shared<LogOutResponse>(m_socket);
    m_createdWorkflow = std::make_shared<CreatedWorkflowResponse>(m_socket);
    m_updateWorkflow = std::make_shared<UpdateWorkflowResponse>(m_socket);
    m_inviteToWorkflow = std::make_shared<InvitedToWorkflowResponse>(m_socket);
    m_allWorkflow = std::make_shared<AllWorkflowsResponse>(m_socket);
    m_singleWorkflow = std::make_shared<SingleWorkflowDataResponse>(m_socket);
    m_sendStat = std::make_shared<SendStatistics>(m_socket);
    m_sendProfile = std::make_shared<SendProfileResponse>(m_socket);
    m_updateProfile = std::make_shared<ToUpdateProfileResponse>(m_socket);
    m_createListResponse = std::make_shared<ToCreateListResponse>(m_socket);
    m_removeListResponse = std::make_shared<ToRemoveListResponse>(m_socket);
    m_createTaskResponse = std::make_shared<ToCreateTaskResponse>(m_socket);
    m_updateTaskResponse = std::make_shared<ToUpdateTaskResponse>(m_socket);
    m_moveTaskResponse = std::make_shared<ToMoveTaskResponse>(m_socket);
    m_removeTaskResponse = std::make_shared<ToRemoveTaskResponse>(m_socket);
    m_sendTaskDataResponse = std::make_shared<SendTaskDataResponse>(m_socket);
}

Client::~Client() {
    m_socket->abort();
    delete m_socket;
}

void Client::doConnect(char *ip, int port) {
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    m_socket->connectToHost(ip, port);
    if (!m_socket->waitForConnected(5000))
        qDebug() << "Error: " << m_socket->errorString();
}

void Client::testRequestLoop() {
    //  m_request->m_token = mx_hash("const QString& pass", "salt");
////            ////auth sector
    //  m_request->signUp("ndykyy1", "21453#gs8kFSdfD1F244iuSn1", "Nazar1", "Dykyy1", "NazarDykyy1@gmail.com");
    //  m_request->signIn("NazarDykyy1@gmail.com", "ndykyy", "21453#gs8kFSdfD1F244iuSn1");
     //m_request->autoSignIn();//-
     //m_request->autoSignInWithGoogle();//-
     //m_request->logOut(1);//+

//            ////workdflow (desk) sector
    //  m_request->createWorkflow("EL TITLE", "EL DESCRIPTION", 1);
    //  m_request->updateWorkflow("QString title", "QString description", 1);
    //  m_request->inviteToWorkflow(1, 1);
    //  m_request->getAllWorkflows(1);
    //  m_request->getSingleWorkflowData(1);

     //m_request->getStatistics();//-

//            ////profile sector
    //  m_request->getProfile(1);
    //  m_request->updateProfile(1, "Nazar", "Dykyy");

            ////list sector
    // m_request->createList("ListName", 1);
    // m_request->removeList(1);
            ////task sector
    // m_request->createTask("Task name", 1);
    // m_request->updateTask(1, "description", {"One", "Two", "Three"});
    // m_request->moveTask(1, 1);
    // m_request->removeTask(1);
    // m_request->getTaskData(1);
}

void Client::parseJSON(QJsonDocument itemDoc) {
    QJsonObject itemObject = itemDoc.object();

    QVector<std::shared_ptr<AbstractResponseHandler>> funcList;

    funcList.append({m_signIn, m_signUp, m_autoSignIn, m_googleSignIn, m_logOut, m_createdWorkflow});
    funcList.append({m_updateWorkflow, m_inviteToWorkflow, m_allWorkflow, m_singleWorkflow});
    funcList.append({m_sendStat, m_sendProfile, m_updateProfile, m_createListResponse});
    funcList.append({m_removeListResponse, m_createTaskResponse, m_updateTaskResponse});
    funcList.append({m_moveTaskResponse, m_removeTaskResponse, m_sendTaskDataResponse});

    QVector<RequestType> types;
    types.append(RequestType::SIGN_UP);
    types.append(RequestType::SIGN_IN);
    types.append(RequestType::AUTO_AUTH);
    types.append(RequestType::AUTO_OAUTH);
    types.append(RequestType::LOG_OUT);
    types.append(RequestType::CREATE_WORKFLOW);
    types.append(RequestType::UPDATE_WORKFLOW);
    types.append(RequestType::INVITE_TO_WORKFLOW);
    types.append(RequestType::GET_ALL_WORKFLOWS);
    types.append(RequestType::GET_SINGLE_WORKFLOW_DATA);
    types.append(RequestType::GET_STATISTICS);
    types.append(RequestType::GET_PROFILE);
    types.append(RequestType::UPDATE_PROFILE);
    types.append(RequestType::CREATE_LIST);
    types.append(RequestType::REMOVE_LIST);
    types.append(RequestType::CREATE_TASK);
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
//        qDebug() << m_socket->read(size.toInt());
        QJsonDocument itemDoc = QJsonDocument::fromJson(m_socket->read(size.toInt()));
        if (!itemDoc.isNull())
            parseJSON(itemDoc);
    }
}