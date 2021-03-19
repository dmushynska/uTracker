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
        emit m_parent->getManager()->getAuthor()->serverResponseSignUp(1, itemObject["message"].toString());
    }
    else {
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
        emit m_parent->getManager()->getAuthor()->serverResponseSignIn(false);
    }
    else {
        m_token = itemObject["token"].toString();
        m_parent->getManager()->getUser()->setUserId(itemObject["userId"].toInt());
        WORKFLOW->getAllListWorkflow();
        emit m_parent->getManager()->getAuthor()->serverResponseSignIn(true, itemObject["login"].toString(), itemObject["email"].toString(), itemObject["userId"].toInt());
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SignInWithGoogleResponse::SignInWithGoogleResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void SignInWithGoogleResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() != 1){
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

}
////////////////////////////////////////////////////////////////////////////////////////
CreatedWorkflowResponse::CreatedWorkflowResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void CreatedWorkflowResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else {
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
        emit WORKFLOW->serverRemoveWorkflowResponse(itemObject["workflowId"].toInt());
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
        emit WORKFLOW->serverCreateTaskResponse(itemObject["title"].toString(), itemObject["taskId"].toInt(), itemObject["listId"].toInt());
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
    }
    emit WORKFLOW->serverGetTasksResponse(itemObject);
}
////////////////////////////////////////////////////////////////////////////////////////
ToUpdateTaskResponse::ToUpdateTaskResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToUpdateTaskResponse::responseHandle(QJsonObject itemObject) {
    qDebug() << "message :" << itemObject["message"].toString() << "\n";
    if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
    else if (itemObject.contains("title")) {
        emit WORKFLOW->serverRenameTaskResponse(itemObject["message"].toString(), itemObject["listId"].toInt(), itemObject["taskId"].toInt(), itemObject["title"].toString());
    }
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
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
        QJsonDocument itemDoc = QJsonDocument::fromJson(itemObject["checkList"].toString().toUtf8());
        QJsonObject object = itemDoc.object();
        QJsonArray arr = object["array"].toArray();
        for(int i = 0; i < arr.count(); i++) {
            qDebug() << arr.at(i)["str"].toString();
            qDebug() << arr.at(i)["isDone"].toBool();
        }
        emit WORKFLOW->serverGetTaskDataResponse(itemObject["message"].toString(), itemObject["description"].toString(), arr, itemObject);
    }
}