#include "listworkflowsmodel.h"

WorkflowsModel::WorkflowsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant WorkflowsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

bool WorkflowsModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int WorkflowsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_workflows.size();
}

QVariant WorkflowsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == TitleRole)
        return m_workflows[index.row()].first;
    if (role == IdRole)
        return m_workflows[index.row()].second;
    return QVariant();
}

bool WorkflowsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == TitleRole)
            m_workflows[index.row()].first = value.toString();
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags WorkflowsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool WorkflowsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    // request to insert Cards
    beginInsertRows(parent, row, row + count - 1);
    QPair<QString, int> newCard{"", -1};
    m_workflows.insert(row, count, newCard);
    endInsertRows();
    return /*response is true*/count < rowCount();
}

bool WorkflowsModel::append(QString text)
{
    insertRows(rowCount(), 1);
    setData(createIndex(rowCount() - 1, 0), text, TitleRole);
    return true;
}

bool WorkflowsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    // request to remove Cards
    beginRemoveRows(parent, row, row + count - 1);
    m_workflows.remove(row, count);
    endRemoveRows();
    return /*response is true*/count < rowCount() || row < rowCount();
}

QHash<int, QByteArray> WorkflowsModel::roleNames() const
{
    QHash<int, QByteArray> roleName;
    roleName[TitleRole] = "title";
    roleName[IdRole] = "idWorkflow";
    return  roleName;
}