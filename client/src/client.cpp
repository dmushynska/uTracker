#include <QSslConfiguration>
#include <QFile>
#include <QSslKey>

#include "client.h"
#include "loggingcategories.h"

class AES;

Client::Client(char* host, int port, QObject* parent) :QObject(parent), m_host(host), m_port(port)
{
    qDebug(logDebug()) << "client constructor start";
    m_ssl_socket = std::make_shared<QSslSocket>();
    m_request = std::make_shared<AbstractRequest>(m_ssl_socket);

    m_manager = new UserManager(this);
    m_manager->getAuthor()->setRequest(m_request.get());
    m_manager->getWorkflow()->setRequest(m_request.get());
    initResponses();

    connect(m_ssl_socket.get(), &QSslSocket::encrypted, this, &Client::connectSuccess);
    connect(m_ssl_socket.get(), &QSslSocket::readyRead, this, &Client::readyRead);
    connect(m_ssl_socket.get(), &QSslSocket::disconnected, this, &Client::disconnected);
    connect(m_ssl_socket.get(), SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
    configSSL();
    qDebug(logDebug()) << "client constructor end";
}

void Client::initResponses() {
    m_signUp = std::make_shared<SignUpResponse>(this, m_ssl_socket);
    m_signIn = std::make_shared<SignInResponse>(this, m_ssl_socket);
    m_autoSignIn = std::make_shared<AutoSignInResponse>(this, m_ssl_socket);
    m_googleSignIn = std::make_shared<SignInWithGoogleResponse>(this, m_ssl_socket);
    m_logOut = std::make_shared<LogOutResponse>(this, m_ssl_socket);
    m_createdWorkflow = std::make_shared<CreatedWorkflowResponse>(this, m_ssl_socket);
    m_updateWorkflow = std::make_shared<UpdateWorkflowResponse>(this, m_ssl_socket);
    m_inviteToWorkflow = std::make_shared<InvitedToWorkflowResponse>(this, m_ssl_socket);
    m_removeFromWorkflow = std::make_shared<RemovedFromWorkflowResponse>(this, m_ssl_socket);
    m_getUsersFromWorkflow = std::make_shared<GetUsersFromWorkflowResponse>(this, m_ssl_socket);
    m_allWorkflow = std::make_shared<AllWorkflowsResponse>(this, m_ssl_socket);
    m_singleWorkflow = std::make_shared<SingleWorkflowDataResponse>(this, m_ssl_socket);
    m_sendStat = std::make_shared<SendStatistics>(this, m_ssl_socket);
    m_sendProfile = std::make_shared<SendProfileResponse>(this, m_ssl_socket);
    m_updateProfile = std::make_shared<ToUpdateProfileResponse>(this, m_ssl_socket);
    m_createListResponse = std::make_shared<ToCreateListResponse>(this, m_ssl_socket);
    m_getListsResponse = std::make_shared<ToGetListsResponse>(this, m_ssl_socket);
    m_removeListResponse = std::make_shared<ToRemoveListResponse>(this, m_ssl_socket);
    m_createTaskResponse = std::make_shared<ToCreateTaskResponse>(this, m_ssl_socket);
    m_updateTaskResponse = std::make_shared<ToUpdateTaskResponse>(this, m_ssl_socket);
    m_getTasksResponse = std::make_shared<ToGetTasksResponse>(this, m_ssl_socket);
    m_moveTaskResponse = std::make_shared<ToMoveTaskResponse>(this, m_ssl_socket);
    m_removeTaskResponse = std::make_shared<ToRemoveTaskResponse>(this, m_ssl_socket);
    m_sendTaskDataResponse = std::make_shared<SendTaskDataResponse>(this, m_ssl_socket);
}

Client::~Client() {
    qDebug(logDebug) << "Client destructor";
    m_ssl_socket->abort();
//    m_ssl_socket->abort();
//    delete m_ssl_socket;
}

void Client::doConnect() {
    qDebug(logDebug()) << "doConnect to host " << m_host;
    m_ssl_socket->connectToHostEncrypted(m_host, m_port);
    // start a secure connection, starts an immediate SSL handshake
    // once the connection has been established.

    //  which will block the calling thread until an encrypted connection has been established.
    if (m_ssl_socket->waitForEncrypted(50000)) {

        m_ssl_socket->write("new client connected \n");
        qDebug() << " connected to server mode =" << m_ssl_socket->mode();
    }
    else {
        qDebug(logDebug()) << "error connection to server :" << m_ssl_socket->errorString();
        exit(1);
    }
}

bool Client::configSSL()
{
    qDebug(logDebug) << "Client::configSSL";

    QSslConfiguration config;
    QByteArray key;
    QByteArray root;
    QByteArray cert;

    QFile file_key("./CA/client.key");
    if (file_key.open(QIODevice::ReadOnly)) {
        key = file_key.readAll();
        file_key.close();
    }
    else {
        qDebug() << "error key " << file_key.errorString();
        return false;
    }

    QFile file_cert("./CA/client.pem");
    if (file_cert.open(QIODevice::ReadOnly)) {
        cert = file_cert.readAll();
        file_cert.close();
    }
    else {
        qDebug() << "error cert " << file_cert.errorString();
        return false;
    }

    QFile file_root_cert("./CA/root.pem");
    if (file_root_cert.open(QIODevice::ReadOnly)) {
        root = file_root_cert.readAll();
        file_root_cert.close();
    }
    else {
        qDebug() << "root cert " << file_cert.errorString();
        return false;
    }

    QSslKey ssl_key(key, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
    QSslCertificate ssl_cert(cert, QSsl::Pem);
    QSslCertificate root_cert(root, QSsl::Pem);
    config.setLocalCertificate(ssl_cert);
    config.setPrivateKey(ssl_key);
    config.addCaCertificate(root_cert);
    config.setProtocol(QSsl::TlsV1_2);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_ssl_socket->setSslConfiguration(config);
    return true;
}

void Client::testConnect() const
{
    qDebug(logDebug) << "Client::testConnect";
//    QString input;
//    input << "ddd"
    m_ssl_socket->write("hello");
    qDebug(logDebug()) << "testConnect, socket mode =" << m_ssl_socket->mode();
}

void Client::testRequestLoop() {
    qDebug(logDebug()) << "Client::testRequestLoop";

    //  m_request->m_token = mx_hash("const QString& pass", "salt");
////            ////auth sector
    m_request->signUp("ndykyy", "21453#gs8kFSdfD1F244iuSn1", "Nazar", "Dykyy", "NazarDykyy@gmail.com");
      m_request->signIn("NazarDykyy1@gmail.com", "ndykyy", "21453#gs8kFSdfD1F244iuSn1");
     m_request->autoSignIn();//-
     m_request->autoSignInWithGoogle();//-
     m_request->logOut(1);//+

////            ////workdflow (desk) sector
      m_request->createWorkflow("EL TITLE", "EL DESCRIPTION", 1);
      m_request->updateWorkflow("QString title", "QString description", 1);
//      m_request->inviteToWorkflow(1, 1);
//        m_request->getAllWorkflows(0);
//         m_request->getSingleWorkflowData(1);

     m_request->getStatistics();//-
    //// // profile sector
      m_request->getProfile(1);
      m_request->updateProfile(1, "Nazar", "Dykyy");

            ////list sector
     m_request->createList("ListName", 1);
     m_request->removeList(1);
            ////task sector
     m_request->createTask("Task name", 1);
    m_request->updateTask(1, "description", {{"One",true}, {"Two", true}, {"Three", false}});
//     m_request->moveTask(1, 2);
//     m_request->removeTask(1);
//        m_request->getTaskData(1);
}

void Client::parseJSON(QJsonDocument itemDoc) {
    QJsonObject itemObject = itemDoc.object();

    QVector<std::shared_ptr<AbstractResponseHandler>> funcList;

    funcList.append({m_signUp, m_signIn, m_autoSignIn, m_googleSignIn, m_logOut, m_createdWorkflow});
    funcList.append({m_updateWorkflow, m_inviteToWorkflow, m_removeFromWorkflow, m_getUsersFromWorkflow});
    funcList.append({m_allWorkflow, m_singleWorkflow, m_sendStat, m_sendProfile, m_updateProfile});
    funcList.append({m_createListResponse, m_getListsResponse, m_removeListResponse, m_createTaskResponse, m_getTasksResponse});
    funcList.append({m_updateTaskResponse, m_moveTaskResponse, m_removeTaskResponse, m_sendTaskDataResponse});

    QVector<RequestType> types;
    types.append(RequestType::SIGN_UP);
    types.append(RequestType::SIGN_IN);
    types.append(RequestType::AUTO_AUTH);
    types.append(RequestType::AUTO_OAUTH);
    types.append(RequestType::LOG_OUT);
    types.append(RequestType::CREATE_WORKFLOW);
    types.append(RequestType::UPDATE_WORKFLOW);
    types.append(RequestType::INVITE_TO_WORKFLOW);
    types.append(RequestType::REMOVE_FROM_WORKFLOW);
    types.append(RequestType::GET_USERS_FROM_WORKFLOW);
    types.append(RequestType::GET_ALL_WORKFLOWS);
    types.append(RequestType::GET_SINGLE_WORKFLOW_DATA);
    types.append(RequestType::GET_STATISTICS);
    types.append(RequestType::GET_PROFILE);
    types.append(RequestType::UPDATE_PROFILE);
    types.append(RequestType::CREATE_LIST);
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
    qDebug(logDebug()) << "server::disconnected";
//    reconnect();
}

void Client::readyRead() {
    qDebug(logDebug()) << "Client::readyRead";
    while (!m_ssl_socket->atEnd()) {
        QByteArray size = m_ssl_socket->readLine();
        // qDebug() << m_ssl_socket->read(size.toInt());
       QJsonDocument itemDoc = QJsonDocument::fromJson(m_ssl_socket->read(size.toInt()));
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

void Client::connectSuccess()
{
    qInfo(logInfo()) << " signal encrypted - handshake success, state = " << m_ssl_socket->state();
//    qInfo(logInfo()) << m_ssl_socket->;

    m_ssl_socket->write("send from client !!!");
}

void Client::sslErrors(const QList<QSslError>& errors)
{
    foreach (const QSslError& error, errors)
    qDebug() << error.errorString();
}
