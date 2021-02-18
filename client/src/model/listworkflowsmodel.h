#ifndef LISTWORKFLOWSMODEL_H
#define LISTWORKFLOWSMODEL_H

#include <QAbstractListModel>
#include <Components/src/card.h>

class WorkflowsModel : public QAbstractListModel
{
    Q_OBJECT

    enum CardsRole {
        TitleRole,
        IdRole
    };

public:
    explicit WorkflowsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = TitleRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE bool append(QString text);

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<QPair<QString, int>> m_workflows;

};

#endif // LISTWORKFLOWSMODEL_H
