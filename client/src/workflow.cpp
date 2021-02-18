//#include "workflow.h"
#include "usermanager.h"
#include "workflow.h"

#include <iostream>

Workflow::Workflow(QObject *parent) : QObject(parent) {
    m_workflows = new WorkflowsModel(this);
    m_currCardListModel = new CardListsModel(this);

    connect(this, &Workflow::serverAllListWorkflowsResponse, &Workflow::parseAllListWorkflows);
}

void Workflow::setRequest(AbstractRequest *request) {
    m_request = request;
}

void Workflow::getAllListWorkflow() const
{
    m_request->getAllWorkflows(qobject_cast<UserManager *>(parent())->getUser()->getUserId());
}

void Workflow::signInHandler(QString ident, QString password) {
    m_request->signIn(ident, ident, password);
}

void Workflow::printStr(QString str) {
    qDebug() << str;
}

CardListsModel *Workflow::getcardListModel() {
    return m_currCardListModel;
}

void Workflow::parseAllListWorkflows(QJsonArray array) {
    for(int i = 0; i < array.count(); i++) {
        qDebug() << array.at(i)["owner_id"].toInt();
        qDebug() << array.at(i)["title"].toString();
        qDebug() << array.at(i)["deadline"].toString();
        qDebug() << array.at(i)["workflowId"].toInt();
    }
}

