#include "cardlistsmodel.h"
#include "workflow.h"

Q_DECLARE_SMART_POINTER_METATYPE(std::shared_ptr)

CardListsModel::CardListsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant CardListsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
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
    if (role == IdRole)
        return m_kanb[index.row()].id;
    if (role == ModelsRole)
        return QVariant::fromValue(m_kanb[index.row()].model.get());
    return QVariant();
}

bool CardListsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == TitleRole)
            m_kanb[index.row()].title = value.toString();
        if (role == IdRole) {
            m_kanb[index.row()].id = value.toInt();
            m_kanb[index.row()].model->setParentId(value.toInt());
        }
        if (role == ModelsRole) {
            m_kanb[index.row()].model = qvariant_cast<std::shared_ptr<CardsModel>>(value);
            m_kanb[index.row()].model->setParentId(m_kanb[index.row()].id);
        }
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
        m_kanb.insert(i, {"", -1, std::make_shared<CardsModel>()});
    }
    endInsertRows();
    return true;
}

bool CardListsModel::append(const QString &title, int id, const std::shared_ptr<CardsModel> &model)
{
//    emit PARENT_CAST(Workflow, parent())->appendListSignal(title);
    insertRows(rowCount(), 1);
    setData(createIndex(rowCount() - 1, 0), title, TitleRole);
    if (model != nullptr)
        setData(createIndex(rowCount() - 1, 0), QVariant::fromValue<std::shared_ptr<CardsModel>>(model), ModelsRole);
    setData(createIndex(rowCount() - 1, 0), id, IdRole);
    return true;
}

bool CardListsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_kanb.remove(row, count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> CardListsModel::roleNames() const
{
    QHash<int, QByteArray> roleName;
    roleName[TitleRole] = "titleD";
    roleName[ModelsRole] = "modelD";
    roleName[IdRole] = "idD";
    return  roleName;
}

void CardListsModel::clearAllLists() {
    removeRows(0, rowCount());
}
