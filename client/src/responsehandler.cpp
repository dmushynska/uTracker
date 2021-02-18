#include "responsehandler.h"
#include "client.h"

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
    qDebug() << itemObject["error"].toInt();
    if (itemObject["error"].toInt() == 1) {
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
        emit m_parent->getManager()->getAuthor()->serverResponseSignUp(1, itemObject["message"].toString());
    }
    else {
        qDebug() << "SIGN UP message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
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
        m_token = itemObject["token"].toString();
//        qDebug() << "FUCKING TOKEN"
        emit m_parent->getManager()->getAuthor()->serverResponseSignIn(true);
        m_parent->getManager()->getUser()->setUserId(itemObject["userId"].toInt());
        m_parent->getManager()->getWorkflow()->getAllListWorkflow();
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
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        QJsonArray arr = itemObject["workflows"].toArray();
        emit m_parent->getManager()->getWorkflow()->serverAllListWorkflowsResponse(arr);
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
        qDebug() << "ownerId :" << itemObject["owner_id"].toInt() << "\n";
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
    }
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
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToUpdateTaskResponse::ToUpdateTaskResponse(Client *parent, QTcpSocket *socket) :  AbstractResponseHandler(socket) {
    m_parent = parent;
}

void ToUpdateTaskResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["error"].toInt() == 1)
        qDebug() << "error message :" << itemObject["message"].toString() << "\n";
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
        QJsonObject itemObject = itemDoc.object();
        QJsonArray arr = itemObject["array"].toArray();
        qDebug() << "CHECK_LIST :\n";
        for(int i = 0; i < arr.count(); i++) {
            qDebug() << arr.at(i)["str"].toString();
            qDebug() << arr.at(i)["isDone"].toBool();
        }
    }
}