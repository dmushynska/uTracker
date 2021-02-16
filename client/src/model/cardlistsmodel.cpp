#include "cardlistsmodel.h"

CardListsModel::CardListsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant CardListsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
}

bool CardListsModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int CardListsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_kanb.size();
}

QVariant CardListsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == TitleRole)
        return m_kanb[index.row()].title;
    if (role == ModelsRole)
        return QVariant::fromValue(m_kanb[index.row()].model);
    return QVariant();
}

bool CardListsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == TitleRole)
            m_kanb[index.row()].title = value.toString();
        if (role == ModelsRole)
            m_kanb[index.row()].model = qvariant_cast<CardsModel *>(value);
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CardListsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

bool CardListsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++) {
        Kanban newKanb {"", new CardsModel};
        m_kanb.insert(i, newKanb);
    }
    endInsertRows();
    return true;
}

bool CardListsModel::append(QString title)
{
    insertRows(rowCount(), 1);
    setData(createIndex(rowCount() - 1, 0), title, TitleRole);
    return true;
}

bool CardListsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++) {
        delete m_kanb[row].model;
    }
    m_kanb.remove(row, count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> CardListsModel::roleNames() const
{
    QHash<int, QByteArray> roleName;
    roleName[TitleRole] = "titleD";
    roleName[ModelsRole] = "modelD";
    return  roleName;
}
