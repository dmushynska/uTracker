#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <QObject>

#include "model/cardlistsmodel.h"
#include "model/listworkflowsmodel.h"
#include "requests.h"


class Workflow : public QObject
{
    Q_OBJECT

public:
    explicit Workflow(QObject *parent = nullptr);
    ~Workflow() = default;

    Q_INVOKABLE void getAllListWorkflow() const;
    Q_INVOKABLE void signInHandler(QString ident, QString password);

    CardListsModel *getcardListModel();

    void setRequest(AbstractRequest *request);

    void printStr(QString str);

signals:
    void serverAllListWorkflowsResponse(QJsonArray array);
    void serverResponseSignUp(int err, QString strErr);

private slots:
    void parseAllListWorkflows(QJsonArray array);

private:
    void doServerRequest();
private:
    AbstractRequest *m_request;
    WorkflowsModel *m_workflows;
    CardListsModel *m_currCardListModel;
    int idCurrentForkflow;
};

#endif // WORKFLOW_H