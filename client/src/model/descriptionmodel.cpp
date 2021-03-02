#include "descriptionmodel.h"

DescriptionModel::DescriptionModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant DescriptionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

bool DescriptionModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int DescriptionModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant DescriptionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == TaskTitleRole)
        return m_taskTitle;
    if (role == TaskDescriptionRole)
        return m_taskDescription;
    if (role == TaskPointCheckRole)
        return m_data[index.row()].first;
    if (role == TaskPointDescriptionRole)
        return m_data[index.row()].second;
    if (role == TaskIdRole)
        return m_taskId;
    return QVariant();
}

bool DescriptionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == TaskTitleRole)
            m_taskTitle = value.toString();
        if (role == TaskDescriptionRole)
            m_taskDescription = value.toString();
        if (role == TaskPointCheckRole)
            m_data[index.row()].first = value.toBool();
        if (role == TaskPointDescriptionRole)
            m_data[index.row()].second = value.toString();
        if (role == TaskIdRole)
            m_taskId = value.toInt();
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags DescriptionModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool DescriptionModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    m_data.insert(row, count, {false, ""});
    endInsertRows();
    return true;
}

void DescriptionModel::insert(const QString &pointDescription) {
    insertRows(m_data.size(), 1);
    setData(createIndex(m_data.size() - 1, 0), pointDescription, TaskPointDescriptionRole);
}

void DescriptionModel::insert(const QPair<bool, QString> &pair) {
    insertRows(m_data.size(), 1);
    setData(createIndex(m_data.size() - 1, 0), pair.first, TaskPointCheckRole);
    setData(createIndex(m_data.size() - 1, 0), pair.second, TaskPointDescriptionRole);
}

bool DescriptionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();
    return true;
}

void DescriptionModel::clearAllData() {
    m_taskTitle = "";
    m_taskDescription = "";
    m_taskId = -1;
    m_data.clear();
}

QHash<int, QByteArray> DescriptionModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[TaskTitleRole] = "taskTitle";
    roles[TaskDescriptionRole] = "taskDescription";
    roles[TaskPointCheckRole] = "pointCheck";
    roles[TaskPointDescriptionRole] = "pointDescription";
    roles[TaskIdRole] = "taskId";

    return roles;
}

void DescriptionModel::append() {
    insertRows(m_data.size(), 1);
}

QMap<QString, bool> DescriptionModel::toMap() {
    QMap<QString, bool> map;
    for(const auto &point : m_data) {
        map[point.second] = point.first;
    }
    return map;
}
