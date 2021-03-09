#include "responsehandler.h"
#include "client.h"

#define WORKFLOW m_parent->getManager()->getWorkflow()

AbstractResponseHandler::AbstractResponseHandler(QTcpSocket *socket) : m_socket(socket) {
    connect(this, &AbstractResponseHandler::handleInited, &AbstractResponseHandler::responseHandle);
}

QString AbstractResponseHandler::getToken() {
    return m_token;
}
///////////////////////////////////////////////////////////////////////////////////////
SignUpResponse::SignUpResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void SignUpResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1) {
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
        emit m_parent->getManager()->getAuthor()->serverResponseSignUp(1, itemObject["message"].toString());
    }
    else {
        qDebug() << "SIGN UP message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
        qDebug() << "userId :" << itemObject["userId"].toString();
        emit m_parent->getManager()->getAuthor()->serverResponseSignUp(0, "");
        m_token = itemObject["token"].toString();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SignInResponse::SignInResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void SignInResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1) {
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
        emit m_parent->getManager()->getAuthor()->serverResponseSignIn(false);
    }
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
        qDebug() << "userId :" << itemObject["userId"].toInt();
        qDebug() << "login :" << itemObject["login"].toString();
        qDebug() << "email :" << itemObject["email"].toString();
        qDebug() << "name :" << itemObject["name"].toString();
        qDebug() << "surname :" << itemObject["surname"].toString();
        m_token = itemObject["token"].toString();
        m_parent->getManager()->getUser()->setUserId(itemObject["userId"].toInt());
        qDebug() << "COME USER -------- ID -------- " <<itemObject["userId"].toInt();
        WORKFLOW->getAllListWorkflow();
        emit m_parent->getManager()->getAuthor()->serverResponseSignIn(true);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SignInWithGoogleResponse::SignInWithGoogleResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void SignInWithGoogleResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
        m_token = itemObject["token"].toString();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
AutoSignInResponse::AutoSignInResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void AutoSignInResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
        m_token = itemObject["token"].toString();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
LogOutResponse::LogOutResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void LogOutResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
CreatedWorkflowResponse::CreatedWorkflowResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void CreatedWorkflowResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "workflowId :" << itemObject["workflowId"].toInt() << "\n";
        emit WORKFLOW->serverCreateWorkflowResponse(itemObject["title"].toString(),
                                                                            itemObject["workflowId"].toInt());
    }
}
////////////////////////////////////////////////////////////////////////////////////////
RemovedFromWorkflowResponse::RemovedFromWorkflowResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void RemovedFromWorkflowResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "REMOVE from workflow :" << itemObject << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
GetUsersFromWorkflowResponse::GetUsersFromWorkflowResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void GetUsersFromWorkflowResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "GET USERS :" << itemObject << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ArchieveWorkflowResponse::ArchieveWorkflowResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ArchieveWorkflowResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
UpdateWorkflowResponse::UpdateWorkflowResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void UpdateWorkflowResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "title :" << itemObject["title"].toString() << "\n";
        qDebug() << "deadline :" << itemObject["deadline"].toString() << "\n";
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
InvitedToWorkflowResponse::InvitedToWorkflowResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void InvitedToWorkflowResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
AllWorkflowsResponse::AllWorkflowsResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void AllWorkflowsResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        QJsonArray arr = itemObject["workflows"].toArray();//ne testiv
        emit WORKFLOW->serverAllListWorkflowsResponse(arr);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SingleWorkflowDataResponse::SingleWorkflowDataResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void SingleWorkflowDataResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "workflowId" << itemObject["workflowId"].toInt();
        qDebug() << "ownerId :" << itemObject["ownerId"].toInt() << "\n";
        qDebug() << "title :" << itemObject["title"].toString() << "\n";
        qDebug() << "deadline :" << itemObject["deadline"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SendStatistics::SendStatistics(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void SendStatistics::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SendProfileResponse::SendProfileResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void SendProfileResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "login :" << itemObject["login"].toString() << "\n";
        qDebug() << "name :" << itemObject["name"].toString() << "\n";
        qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToUpdateProfileResponse::ToUpdateProfileResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToUpdateProfileResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "name :" << itemObject["name"].toString() << "\n";
        qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToCreateListResponse::ToCreateListResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToCreateListResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "listId :" << itemObject["listId"].toInt() << "\n";
        emit WORKFLOW->serverCreatedListResponse(itemObject["title"].toString(), itemObject["listId"].toInt());
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToRenameListResponse::ToRenameListResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToRenameListResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "title :" << itemObject["listId"].toInt() << "\n";

        emit WORKFLOW->serverRenameListResponse(itemObject["message"].toString(), itemObject["listId"].toInt(), itemObject["title"].toString());
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToGetListsResponse::ToGetListsResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToGetListsResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "ToGetListsResponse :" << itemObject["lists"] << "\n";
    }
    emit WORKFLOW->serverWorkflowListsResponse(itemObject);
}
////////////////////////////////////////////////////////////////////////////////////////
ToRemoveListResponse::ToRemoveListResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToRemoveListResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "listId :" << itemObject["listId"].toInt() << "\n";
        emit WORKFLOW->serverRemoveListResponse(itemObject["message"].toString(), itemObject["listId"].toInt());
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToCreateTaskResponse::ToCreateTaskResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToCreateTaskResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "taskId :" << itemObject["taskId"].toInt() << "\n";
        emit WORKFLOW->serverCreateTaskResponse(itemObject["message"].toString(), itemObject["taskId"].toInt(), itemObject["listId"].toInt());
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToGetTasksResponse::ToGetTasksResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToGetTasksResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "ToGetListsResponse :" << itemObject["listId"]<< "\n";
    }
    emit WORKFLOW->serverGetTasksResponse(itemObject);
}
////////////////////////////////////////////////////////////////////////////////////////
ToUpdateTaskResponse::ToUpdateTaskResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToUpdateTaskResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else if (itemObject.contains("title")) {
        qDebug() << "title :" << itemObject["title"].toString() << "\n";

    }
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "description :" << itemObject["description"].toString() << "\n";
        qDebug() << "checkList :" << itemObject["checkList"].toString() << "\n";
        
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToMoveTaskResponse::ToMoveTaskResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToMoveTaskResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        emit WORKFLOW->serverMoveTaskResponse(itemObject["message"].toString());
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToRemoveTaskResponse::ToRemoveTaskResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToRemoveTaskResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        emit WORKFLOW->serverRemoveTaskResponse(itemObject["message"].toString(), itemObject["listId"].toInt(), itemObject["taskId"].toInt());
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SendTaskDataResponse::SendTaskDataResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void SendTaskDataResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "description :" << itemObject["description"].toString() << "\n";
        QJsonDocument itemDoc = QJsonDocument::fromJson(itemObject["checkList"].toString().toUtf8());
        QJsonObject object = itemDoc.object();
        QJsonArray arr = object["array"].toArray();
        qDebug() << "CHECK_LIST :\n";
        for(int i = 0; i < arr.count(); i++) {
            qDebug() << arr.at(i)["str"].toString();
            qDebug() << arr.at(i)["isDone"].toBool();
        }
        emit WORKFLOW->serverGetTaskDataResponse(itemObject["message"].toString(), itemObject["description"].toString(), arr, itemObject);
    }
}