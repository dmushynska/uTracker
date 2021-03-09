#ifndef CARDLISTSMODEL_H
#define CARDLISTSMODEL_H

#include <QAbstractListModel>
#include "model/cardsmodel.h"
#include <memory>

#define PARENT_CAST(parent, x) qobject_cast<parent *>(x)

class CardListsModel : public QAbstractListModel
{
    Q_OBJECT
    
    struct Kanban {
        QString title;
        int id;
        std::shared_ptr<CardsModel> model;
        Card *findTaskById(int id, int *indx = nullptr);
    };
public:

    enum CardListsRole {
        TitleRole = Qt::UserRole,
        ModelsRole,
        IdRole
    };
    explicit CardListsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = TitleRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = TitleRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = TitleRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;



    Q_INVOKABLE bool append(const QString &title, int id, const std::shared_ptr<CardsModel> &model = nullptr);

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    int indexById(int id) const;

    QModelIndex createCustomIndex(int row) { return QAbstractListModel::createIndex(row, 0); }
    
    QHash<int, QByteArray> roleNames() const override;

    void clearAllLists();

    Kanban* getKanbById(int listId) {
        for (int i = 0; i < m_kanb.size(); i++)
            if (m_kanb[i].id == listId)
                return &(m_kanb[i]);
        throw "nothing";
    }
    Kanban* operator[](int listId) {
        return getKanbById(listId);
    }


private:
    QVector<Kanban> m_kanb;
};

#endif // CARDLISTSMODEL_H
