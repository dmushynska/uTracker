#include "usermanager.h"
#include "workflow.h"

#include <iostream>

Workflow::Workflow(QObject *parent) : QObject(parent) {
    m_workflowsModel = new WorkflowsModel(this);
    m_currCardListModel = new CardListsModel(this);
    m_descriptionModel = new DescriptionModel(this);

    connect(this, &Workflow::serverAllListWorkflowsResponse, &Workflow::parseAllListWorkflows);
    connect(this, &Workflow::serverCreateWorkflowResponse, &Workflow::parseCreatedWorkflow);
    connect(this, &Workflow::serverWorkflowListsResponse, &Workflow::parseLists);
    connect(this, &Workflow::serverCreatedListResponse, &Workflow::parseCreatedList);
    connect(this, &Workflow::serverCreateTaskResponse, &Workflow::parseCreateTask);
    connect(this, &Workflow::serverGetTasksResponse, &Workflow::parseGetTasks);
    connect(this, &Workflow::serverMoveTaskResponse, &Workflow::parseMoveTask);
    connect(this, &Workflow::serverRemoveTaskResponse, &Workflow::parseRemoveTask);
    connect(this, &Workflow::serverGetTaskDataResponse, &Workflow::parseGetTaskData);
    connect(this, &Workflow::serverRemoveListResponse, &Workflow::parseRemoveList);
    connect(this, &Workflow::serverRenameListResponse, &Workflow::parseRenameList);
    connect(this, &Workflow::serverRenameTaskResponse, &Workflow::parseRenameTask);
    connect(this, &Workflow::serverRemoveWorkflowResponse, &Workflow::parseRemoveWorkflow);
}

Workflow::~Workflow() {
    delete m_workflowsModel;
    delete m_currCardListModel;
    delete m_descriptionModel;
}

void Workflow::setRequest(AbstractRequest *request) {
    m_request = request;
}

void Workflow::getAllListWorkflow() const
{
    m_request->getAllWorkflows(PARENT_CAST(UserManager, parent())->getUser()->getUserId());
}

void Workflow::printStr(QString str) {
}

CardListsModel *Workflow::getCardListModel() {
    return m_currCardListModel;
}



void Workflow::parseAllListWorkflows(QJsonArray array) {
//    if (array.size() != m_workflowsModel->rowCount())
        m_workflowsModel->clear();
    for(int i = 0; i < array.count(); i++) {
        m_workflowsModel->append(array.at(i)["title"].toString(), array.at(i)["workflowId"].toInt());
    }
}

WorkflowsModel *Workflow::getWorkflowsModel() {
    return m_workflowsModel;
}

void Workflow::createWorkflow(QString title) {
    m_request->createWorkflow(title, "", PARENT_CAST(UserManager, parent())->getUser()->getUserId());
}

void Workflow::parseCreatedWorkflow(QString title, int id) {
    m_workflowsModel->append(title, id);
}

void Workflow::getWorkflowsModelById(int id) {
    m_idCurrentWorkflow = id;
    m_request->getLists(m_idCurrentWorkflow);
}

//}

void Workflow::parseCreatedList(const QString &title, int id) {
    m_currCardListModel->append(title, id);
}

void Workflow::appendLists(QString title) {
    m_request->createList(title, m_idCurrentWorkflow);
}

void Workflow::parseCreateTask(const QString &title, int id, int listId) {
//    m_request->getLists(m_idCurrentWorkflow);
    try {
        (*m_currCardListModel)[listId]->model->append(title, id, listId, 0, 0);
    } catch (QString err) {
    }
}

void Workflow::appendTask(QString title, int id) {
    m_request->createTask(title, id);
}

void Workflow::parseLists(QJsonObject array) {
    m_currCardListModel->clearAllLists();
    if (array["error"] != 1) {
    }
    QJsonArray lists = array["lists"].toArray();
    for (auto l : lists) {
        auto list = l.toObject();
        auto model = CardsModel::creatCardsModel(list, nullptr, list["listId"].toInt());
        m_currCardListModel->append(list["title"].toString(), list["listId"].toInt(), model);
    }
}

void Workflow::parseGetTasks(QJsonObject array) {
    int listId = array["listId"].toInt();
//    m_currCardListModel
}

void Workflow::moveSetCardId(int id) {
    m_move.cardId = id;
}

void Workflow::moveSetToListId(int id) {
    m_move.toListId = id;
}

void Workflow::moveSetCurrListId(int id) {
    m_move.listId = id;
}

void Workflow::moveRequest(bool toOtherList, int index) {
    m_move.toOtherList = toOtherList;
    if (toOtherList)
        m_request->moveTask(m_move.cardId, m_move.toListId, index == -1 ? 0 : index);
    else
        m_request->moveTask(m_move.cardId, m_move.listId, index == -1 ? 0 : index);
}

void Workflow::parseMoveTask(const QString &msg) {
    if (m_move.toOtherList) { // implement finding tasks by id & use it here
        try {
            auto *from = m_currCardListModel->getKanbById(m_move.listId);
            auto *to = m_currCardListModel->getKanbById(m_move.toListId);
            int index = 0;
            Card *movableTask = from->findTaskById(m_move.cardId, &index);
            if (movableTask) {
                Card card = *movableTask;
                card.setListId(m_move.toListId);
                to->model->append(card);
                if (index != -1)
                    from->model->removeRows(index, 1);
            }
        } catch (...) { return; }
    }
}

void Workflow::parseRemoveTask(const QString &msg, int listId, int taskId) {
    if (listId == 0)
        return;
    try {
        auto *from = m_currCardListModel->getKanbById(listId);
        int index = 0;
        Card *movableTask = from->findTaskById(taskId, &index);
        if (movableTask) {
            if (index != -1)
                from->model->removeRows(index, 1);
        }
    } catch (const QString &ex) {  return; }
}

void Workflow::removeTask(int id) {
    m_request->removeTask(id);
}

DescriptionModel *Workflow::getDescriptionModel() {
    return m_descriptionModel;
}

void Workflow::openDescription(int id) {
    m_request->getTaskData(id);
}

void Workflow::parseGetTaskData(const QString &msg, const QString &descr, QJsonArray array, QJsonObject obg) {
    m_descriptionModel->clearAllData();
    m_descriptionModel->setTaskDescription(descr);
    m_descriptionModel->setTaskTitle(obg["title"].toString());
    m_descriptionModel->setTaskId(obg["taskId"].toInt());
    m_descriptionModel->setListId(obg["listId"].toInt());
    for(int i = 0; i < array.count(); i++) {
        m_descriptionModel->insert({array.at(i)["isDone"].toBool(), array.at(i)["str"].toString()});
    }
    emit gotTaskData();
}

void Workflow::saveDescription() {
    m_request->updateTask(m_descriptionModel->getTaskId(), "", m_descriptionModel->toMap());
    int indx = 0;
    auto kanb = m_currCardListModel->getKanbById(m_descriptionModel->getListId());
    kanb->findTaskById(m_descriptionModel->getTaskId(), &indx);
    kanb->model->setData(kanb->model->index(indx), m_descriptionModel->getStatus().first, CardsModel::StatusRole);
    kanb->model->setData(kanb->model->index(indx), m_descriptionModel->getStatus().second, CardsModel::CountRole);
}

void Workflow::removeList(int id) {
    if (id > -1)
      m_request->removeList(id);
}

void Workflow::renameList(int id, QString name) {
    if (id > -1)
        m_request->renameList(name, id);
}

void Workflow::renameTask(int id, QString name) {
    if (id > 0) {
        m_request->renameTask(name, id);
    }
}

void Workflow::parseRemoveList(const QString &msg, int listId) {
    int index = m_currCardListModel->indexById(listId);
    if (index > -1)
        m_currCardListModel->removeRows(index, 1);
}

void Workflow::parseRenameList(const QString &msg, int listId, const QString &name) {
    int index = m_currCardListModel->indexById(listId);

    if (index < 0) {
        return;
    }
    m_currCardListModel->setData(m_currCardListModel->createCustomIndex(index), name, CardListsModel::TitleRole);
}

void Workflow::parseRenameTask(const QString &msg, int listId, int taskId, const QString &name) {
    if (listId > 0) {
        auto model = m_currCardListModel->getKanbById(listId)->model;
        auto index = 0;
        model->findById(taskId, &index);
        model->setData(model->index(index), name, CardsModel::TitleRole);
    }
}

void Workflow::removeWorkflow(int id) {
    if (id > 0)
        m_request->archieveWorkflow(id);
}

void Workflow::parseRemoveWorkflow(int id) {
    m_workflowsModel->removeById(id);
}
