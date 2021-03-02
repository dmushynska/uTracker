#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <QObject>

#include "model/cardlistsmodel.h"
#include "model/listworkflowsmodel.h"
#include "model/descriptionmodel.h"
#include "requests.h"

#define PARENT_CAST(parent, x) qobject_cast<parent *>(x)

class Workflow final : public QObject
{
    Q_OBJECT

    struct MoveData {
        int cardId = -1;
        int listId = -1;
        int toCardIndex = -1;
        int toListId = -1;
        bool toOtherList;
    };
public:
    explicit Workflow(QObject *parent = nullptr);
    ~Workflow();

    //*     Workflows    *//
    Q_INVOKABLE void getAllListWorkflow() const;
    Q_INVOKABLE void createWorkflow(QString title);

    //*     Lists       *//
    Q_INVOKABLE void appendLists(QString title);

    //*     Tasks       *//
    Q_INVOKABLE void appendTask(QString title, int id);
    Q_INVOKABLE void renameTask(int id, QString name){}    ///////////////// Is not implemented
    Q_INVOKABLE void openDescription(int id);
    Q_INVOKABLE void saveDescription();

    //*     Move    *//
        Q_INVOKABLE void moveSetCardId(int id);
        Q_INVOKABLE void moveSetToListId(int id);
        Q_INVOKABLE void moveSetCurrListId(int id);
        Q_INVOKABLE void moveRequest(bool toOtherList, int index = -1);
    Q_INVOKABLE void removeRequest(int id);



    CardListsModel *getCardListModel();
    WorkflowsModel *getWorkflowsModel();
    DescriptionModel *getDescriptionModel();

    void setRequest(AbstractRequest *request);

    Q_INVOKABLE void getWorkflowsModelById(int id);

    void printStr(QString str);

signals:        // Model Signals
    void gotTaskData();

private slots:  // Model Slots
//    void appendListRequest(const QString &title);

signals:        // Server Response Signals
    void serverAllListWorkflowsResponse(QJsonArray array);
    void serverCreateWorkflowResponse(QString title, int id);
    void serverWorkflowListsResponse(QJsonObject array);
    void serverCreatedListResponse(const QString &title, int id);
    void serverCreateTaskResponse(const QString &title, int id, int listId);
    void serverGetTasksResponse(QJsonObject array);
    void serverMoveTaskResponse(const QString &msg);
    void serverRemoveTaskResponse(const QString &msg, int listId, int taskId);
    void serverGetTaskDataResponse(const QString &msg, const QString &descr, QJsonArray array, QJsonObject obj);
private slots:  // Server Response Slots
    void parseAllListWorkflows(QJsonArray array);

    void parseCreatedWorkflow(QString title, int id);
    void parseLists(QJsonObject array);
    void parseCreatedList(const QString &title, int id);
    void parseCreateTask(const QString &title, int id, int listId);
    void parseGetTasks(QJsonObject array);
    void parseMoveTask(const QString &msg);
    void parseRemoveTask(const QString &msg, int listId, int taskId);
    void parseGetTaskData(const QString &msg, const QString &descr, QJsonArray array, QJsonObject obg);

private:
    WorkflowsModel *m_workflowsModel;
    CardListsModel *m_currCardListModel;
    AbstractRequest *m_request;
    DescriptionModel *m_descriptionModel;
    MoveData m_move;
    int m_idCurrentWorkflow;
};

#endif // WORKFLOW_H
