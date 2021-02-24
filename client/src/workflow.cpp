//#include "workflow.h"
#include "usermanager.h"
#include "workflow.h"

#include <iostream>

Workflow::Workflow(QObject *parent) : QObject(parent) {
    m_workflowsModel = new WorkflowsModel(this);
    m_currCardListModel = new CardListsModel(this);

    connect(this, &Workflow::serverAllListWorkflowsResponse, &Workflow::parseAllListWorkflows);
    connect(this, &Workflow::serverCreateWorkflowResponse, &Workflow::parseCreatedWorkflow);
    connect(this, &Workflow::serverWorkflowListsResponse, &Workflow::parseLists);
    connect(this, &Workflow::serverCreatedListResponse, &Workflow::parseCreatedList);
    connect(this, &Workflow::serverCreateTaskResponse, &Workflow::parseCreateTask);
    connect(this, &Workflow::serverGetTasksResponse, &Workflow::parseGetTasks);
}

void Workflow::setRequest(AbstractRequest *request) {
    m_request = request;
}

void Workflow::getAllListWorkflow() const
{
    qDebug() << "USER -------- ID -------- " << PARENT_CAST(UserManager, parent())->getUser()->getUserId();
    m_request->getAllWorkflows(PARENT_CAST(UserManager, parent())->getUser()->getUserId());
}

void Workflow::printStr(QString str) {
    qDebug() << str;
}

CardListsModel *Workflow::getCardListModel() {
    return m_currCardListModel;
}

void Workflow::parseAllListWorkflows(QJsonArray array) {
//    if (array.size() != m_workflowsModel->rowCount())
        m_workflowsModel->clear();
    for(int i = 0; i < array.count(); i++) {
//        QModelIndex index = m_workflowsModel->createModelIndex(i);
        m_workflowsModel->append(array.at(i)["title"].toString(), array.at(i)["workflowId"].toInt());
//        m_workflowsModel->setData(index, array.at(i)["title"].toString(), WorkflowsModel::WorkflowRole::TitleRole);
//        m_workflowsModel->setData(index, array.at(i)["workflowId"].toInt(), WorkflowsModel::WorkflowRole::IdRole);
    }
}



WorkflowsModel *Workflow::getWorkflowsModel() {
    return m_workflowsModel;
}

void Workflow::createWorkflow(QString title) {
    qDebug() << "REQUEST CREATE ----------- WF ----------- USER ID" <<  PARENT_CAST(UserManager, parent())->getUser()->getUserId();
    m_request->createWorkflow(title, "", PARENT_CAST(UserManager, parent())->getUser()->getUserId());
}

void Workflow::parseCreatedWorkflow(QString title, int id) {
    m_workflowsModel->append(title, id);
}

void Workflow::getWorkflowsModelById(int id) {
    m_idCurrentWorkflow = id;
    m_request->getLists(m_idCurrentWorkflow);
}

//void Workflow::appendListRequest(const QString &title) {
//    m_request->createList(title, m_idCurrentWorkflow);
//}

void Workflow::parseCreatedList(const QString &title, int id) {
    m_currCardListModel->append(title, id);
}

void Workflow::appendLists(QString title) {
    m_request->createList(title, m_idCurrentWorkflow);
}

void Workflow::parseCreateTask(const QString &title, int id, int listId) {
//    m_request->getLists(m_idCurrentWorkflow);
    qDebug() << "PARSE CREATE ----------- TK ----------- ID" << title << id;
    try {
        (*m_currCardListModel)[listId]->model->append(title, id);
    } catch (QString err) {
        qDebug() << "<<<ERROR>>>";
    }
}

void Workflow::appendTask(QString title, int id) {
    qDebug() << "REQUEST CREATE ----------- TK ----------- USER ID" <<  title;
    m_request->createTask(title, id);
}

void Workflow::parseLists(QJsonObject array) {
    m_currCardListModel->clearAllLists();
    if (array["error"] != 1) {
        qDebug() << "Some problem";
    }
    QJsonArray lists = array["lists"].toArray();
    for (auto l : lists) {
        auto list = l.toObject();
//    qDebug() << list["title"].toString();
        auto model = CardsModel::creatCardsModel(list);
        m_currCardListModel->append(list["title"].toString(), list["listId"].toInt(), model);
    }
}

void Workflow::parseGetTasks(QJsonObject array) {
    int listId = array["listId"].toInt();
//    m_currCardListModel
}
