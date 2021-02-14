#include "responsehandler.h"

AbstractResponseHandler::AbstractResponseHandler(QTcpSocket *socket) : m_socket(socket) {
    connect(this, &AbstractResponseHandler::handleInited, &AbstractResponseHandler::responseHandle);
}

QString AbstractResponseHandler::getToken() {
    return m_token;
}
///////////////////////////////////////////////////////////////////////////////////////
SignUpResponse::SignUpResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void SignUpResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
        m_token = itemObject["token"].toString();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SignInResponse::SignInResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void SignInResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
        m_token = itemObject["token"].toString();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SignInWithGoogleResponse::SignInWithGoogleResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void SignInWithGoogleResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
        m_token = itemObject["token"].toString();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
AutoSignInResponse::AutoSignInResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void AutoSignInResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
        qDebug() << "token :" << itemObject["token"].toString();
        m_token = itemObject["token"].toString();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
LogOutResponse::LogOutResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void LogOutResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
CreatedWorkflowResponse::CreatedWorkflowResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void CreatedWorkflowResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
UpdateWorkflowResponse::UpdateWorkflowResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void UpdateWorkflowResponse::responseHandle(QJsonObject itemObject) {
    if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
InvitedToWorkflowResponse::InvitedToWorkflowResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void InvitedToWorkflowResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
AllWorkflowsResponse::AllWorkflowsResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void AllWorkflowsResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SingleWorkflowDataResponse::SingleWorkflowDataResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void SingleWorkflowDataResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SendStatistics::SendStatistics(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void SendStatistics::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SendProfileResponse::SendProfileResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void SendProfileResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToUpdateProfileResponse::ToUpdateProfileResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void ToUpdateProfileResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToCreateListResponse::ToCreateListResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void ToCreateListResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToRemoveListResponse::ToRemoveListResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void ToRemoveListResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToCreateTaskResponse::ToCreateTaskResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void ToCreateTaskResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToUpdateTaskResponse::ToUpdateTaskResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void ToUpdateTaskResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToMoveTaskResponse::ToMoveTaskResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void ToMoveTaskResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
ToRemoveTaskResponse::ToRemoveTaskResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void ToRemoveTaskResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////
SendTaskDataResponse::SendTaskDataResponse(QTcpSocket *socket) :  AbstractResponseHandler(socket){}

void SendTaskDataResponse::responseHandle(QJsonObject itemObject) {
        if (itemObject["Error"].toInt() == 1)
        qDebug() << "Error message :" << itemObject["message"].toString() << "\n";
    else {
        qDebug() << "message :" << itemObject["message"].toString() << "\n";
    }
}