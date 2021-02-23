#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <QObject>

#include "model/cardlistsmodel.h"
#include "model/listworkflowsmodel.h"
#include "requests.h"

#define PARENT_CAST(parent, x) qobject_cast<parent *>(x)

class Workflow final : public QObject
{
    Q_OBJECT

public:
    explicit Workflow(QObject *parent = nullptr);
    ~Workflow() = default;

    //*     Workflows    *//
    Q_INVOKABLE void getAllListWorkflow() const;
    Q_INVOKABLE void createWorkflow(QString title);

    //*     Lists       *//
    Q_INVOKABLE void appendLists(QString title);

    //*     Tasks       *//
    Q_INVOKABLE void appendTask(QString title, int id);

    CardListsModel *getCardListModel();
    WorkflowsModel *getWorkflowsModel();

    void setRequest(AbstractRequest *request);

    Q_INVOKABLE void getWorkflowsModelById(int id);

    void printStr(QString str);

signals:        // Model Signals
//    void appendListSignal(const QString &title);

private slots:  // Model Slots
//    void appendListRequest(const QString &title);

signals:        // Server Response Signals
    void serverAllListWorkflowsResponse(QJsonArray array);
    void serverCreateWorkflowResponse(QString title, int id);
    void serverWorkflowListsResponse();
    void serverCreatedListResponse(const QString &title, int id);
    void serverCreateTaskResponse(const QString &title, int id);

private slots:  // Server Response Slots
    void parseAllListWorkflows(QJsonArray array);
    void parseCreatedWorkflow(QString title, int id);
    void parseLists() {
        m_currCardListModel->clearAllLists();
    }
    void parseCreatedList(const QString &title, int id);
    void parseCreateTask(const QString &title, int id);

private:
    WorkflowsModel *m_workflowsModel;
    CardListsModel *m_currCardListModel;
    AbstractRequest *m_request;
    int m_idCurrentWorkflow;
};

#endif // WORKFLOW_H
